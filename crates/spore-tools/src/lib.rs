//! # spore-tools — `osptool`, an offline inspector for Spore data.
//!
//! `osptool` answers questions about a DBPF package without loading it into an
//! engine: what records does it hold, which one is this identity, what does this
//! record decode to, what does the whole type census look like, and is this
//! package internally consistent.
//!
//! ```text
//!   .package on disk
//!     -> spore_dbpf     index rows, QFS, record extraction   (no Bevy)
//!     -> spore_gmdl     gmdl walk + mesh extraction
//!     -> spore_rw4      RW4 section directory
//!     -> spore_texture  raster envelope + DXT5
//!     -> spore_assets   package priority, canonical manifest
//!     -> spore_tools    <-- THIS CRATE: argument parsing, dispatch, reporting
//! ```
//!
//! Everything is a library here and the binary is a shim, so every command can
//! be driven from a test with an in-memory `Vec<u8>` sink instead of a
//! subprocess and a temporary file. That is the difference between a tool whose
//! output is checked and one whose output is eyeballed.
//!
//! # The one rule every human-readable line obeys
//!
//! **A statement about a record is either `decoded` or `type-level`, and it says
//! which.** "This build has a decoder family for `gmdl`" is a fact about the
//! *type table*; "this record decoded to one mesh of 50 vertices" is a fact about
//! 1 266 bytes. Collapsing them is how an asset tool reports a decoder's
//! *existence* as if it had reported a record's *contents*, and every command
//! here labels its output accordingly — see [`commands`].
//!
//! # Determinism
//!
//! `list`, `find`, `describe`, `manifest` and `types` are byte-for-byte
//! reproducible for the same input. `manifest` is the load-bearing case and the
//! test suite asserts it directly, because the reference tool
//! (`tools/spore/manifest/manifest.py`) is built around the same property: a
//! report that reorders itself between runs cannot be diffed, and a report that
//! cannot be diffed cannot be used to review a change.
//!
//! # Clean-room boundary
//!
//! No EA or Maxis data is linked, vendored or embedded. The Python oracles under
//! `tools/spore/` are OpenSpore's own; where this crate and an oracle disagree,
//! the divergence is reported in the crate docs of the crate that owns the
//! format, never papered over here.

#![deny(unsafe_code)]
#![warn(missing_debug_implementations)]

pub mod commands;
pub mod json;

use std::io::Write;
use std::path::PathBuf;

use spore_assets::AssetError;
use spore_core::ResourceKey;

/// Everything succeeded.
pub const EXIT_OK: i32 = 0;
/// The command line could not be parsed, or a flag value was unusable.
///
/// Matches the `argparse` convention the repository's Python tools already use
/// and `spore_engine::cli::EXIT_USAGE`, so one broken-argument exit code means
/// the same thing in every tool in the workspace.
pub const EXIT_USAGE: i32 = 2;
/// A record identity was not present in any loaded package, or no package was
/// loaded at all.
pub const EXIT_NOT_FOUND: i32 = 3;
/// A record or a package was found but the container layer refused it.
pub const EXIT_DECODE: i32 = 4;
/// A file could not be opened, created or written.
pub const EXIT_IO: i32 = 5;

/// `list`: enumerate a package's index rows.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ListRequest {
    /// Package path.
    pub package: PathBuf,
    /// Restrict to one record type id.
    pub type_id: Option<u32>,
    /// Restrict to one group id.
    pub group_id: Option<u32>,
    /// Maximum rows to print. `0` means "no limit".
    pub limit: usize,
    /// Emit a JSON array instead of the column table.
    pub json: bool,
    /// Include the canonical type/group name columns.
    pub names: bool,
}

/// `find`: resolve one identity across one package.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct FindRequest {
    /// Package path.
    pub package: PathBuf,
    /// The identity to resolve.
    pub key: ResourceKey,
    /// Emit a JSON object instead of the report block.
    pub json: bool,
}

/// `describe` and `extract` both take exactly one identity in one package.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RecordRequest {
    /// Package path.
    pub package: PathBuf,
    /// The identity to act on.
    pub key: ResourceKey,
}

/// `extract`: write one record's decoded bytes into a directory.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ExtractRequest {
    /// Package path.
    pub package: PathBuf,
    /// The identity to extract.
    pub key: ResourceKey,
    /// Destination directory. Validated by [`commands::extract::validate_out_dir`].
    pub out_dir: PathBuf,
}

/// `manifest`: the canonical one-row-per-record report over several packages.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ManifestRequest {
    /// Package paths, in resolution order. Earlier wins on a duplicate identity.
    pub packages: Vec<PathBuf>,
    /// Write JSON Lines here instead of to stdout.
    pub out_file: Option<PathBuf>,
    /// Emit a JSON array of rows on stdout.
    pub json: bool,
    /// Print the coverage summary.
    pub stats: bool,
}

/// `verify`: walk every record of a type and count what happened to it.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct VerifyRequest {
    /// Package path.
    pub package: PathBuf,
    /// Restrict the walk to one record type id.
    pub type_id: Option<u32>,
}

/// `types`: print the canonical type/group tables and a package histogram.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TypesRequest {
    /// Print the canonical group table as well.
    pub group: bool,
    /// Additionally print a per-package type histogram.
    pub package: Option<PathBuf>,
}

/// What a command line asks for.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Request {
    /// Print [`usage`] and exit [`EXIT_OK`].
    Help,
    /// See [`ListRequest`].
    List(ListRequest),
    /// See [`FindRequest`].
    Find(FindRequest),
    /// See [`RecordRequest`].
    Describe(RecordRequest),
    /// See [`ExtractRequest`].
    Extract(ExtractRequest),
    /// See [`ManifestRequest`].
    Manifest(ManifestRequest),
    /// See [`VerifyRequest`].
    Verify(VerifyRequest),
    /// See [`TypesRequest`].
    Types(TypesRequest),
}

/// Every way a command line can be wrong.
///
/// Each variant names what was expected, because a bare "bad argument" makes the
/// user guess which of six flags was at fault.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum CliError {
    /// No subcommand was given.
    NoCommand,
    /// The first argument is not one of the subcommands.
    UnknownCommand(String),
    /// A flag that takes a value was given none.
    MissingValue {
        /// The flag as typed.
        flag: String,
    },
    /// A flag value could not be read as the type that flag documents.
    BadValue {
        /// The flag as typed.
        flag: String,
        /// What the user typed.
        value: String,
        /// What it had to be.
        expected: &'static str,
    },
    /// A flag that takes no value was given one.
    UnexpectedValue {
        /// The flag as typed.
        flag: String,
        /// The stray value.
        value: String,
    },
    /// A single-valued flag was given twice with the last one silently winning.
    ///
    /// Last-wins is how a shell script that builds a flag list by appending
    /// usually *wants* to behave, so this is only raised where two different
    /// answers would make the command's output depend on argument order.
    Repeated {
        /// The flag as typed.
        flag: String,
    },
    /// A flag this subcommand does not accept.
    UnknownFlag {
        /// The subcommand it was given to.
        command: &'static str,
        /// The flag as typed.
        flag: String,
    },
    /// A subcommand's positional arguments are missing or surplus.
    Positional {
        /// The subcommand.
        command: &'static str,
        /// Its `USAGE` line, for the message.
        synopsis: &'static str,
        /// What the user supplied.
        given: usize,
    },
    /// `--out` for `extract` names a directory this tool refuses to write into.
    UnsafeOutDir(String),
}

/// The subcommand that was being parsed, for error messages.
pub type CommandName = &'static str;

/// The one-line synopsis of each subcommand, **without** the command name.
///
/// Excludes the name because both of its consumers already supply it: `usage()`
/// writes `osptool <name> <synopsis>` and a parse error writes
/// `` `<name>` takes <synopsis> ``. Spelling the name inside the string too would
/// print `extract extract <package> ...`, which reads like a mistake because it
/// is one.
const SYNOPSIS_LIST: &str = "<package> [--type 0x..] [--group 0x..] [--limit N] [--json] [--names]";
const SYNOPSIS_FIND: &str = "<package> <T:G:I> [--json]";
const SYNOPSIS_DESCRIBE: &str = "<package> <T:G:I>";
const SYNOPSIS_EXTRACT: &str = "<package> <T:G:I> --out <dir>";
const SYNOPSIS_MANIFEST: &str = "<package...> [--out <file>] [--json] [--stats]";
const SYNOPSIS_VERIFY: &str = "<package> [--type 0x..]";
const SYNOPSIS_TYPES: &str = "[--group] [--package <p>]";

/// The default `list` row cap, and the value `0` replaces.
pub const DEFAULT_LIST_LIMIT: usize = 50;

impl std::fmt::Display for CliError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::NoCommand => f.write_str(
                "no subcommand given; try `osptool --help`, or one of: list, find, describe, extract, manifest, verify, types",
            ),
            Self::UnknownCommand(name) => write!(
                f,
                "unknown subcommand `{name}`; expected one of: list, find, describe, extract, manifest, verify, types"
            ),
            Self::MissingValue { flag } => write!(f, "`{flag}` needs a value"),
            Self::BadValue {
                flag,
                value,
                expected,
            } => write!(f, "`{flag}` got `{value}`, expected {expected}"),
            Self::UnexpectedValue { flag, value } => {
                write!(f, "`{flag}` takes no value, but `{value}` followed it")
            }
            Self::Repeated { flag } => write!(f, "`{flag}` was given more than once"),
            Self::UnknownFlag { command, flag } => {
                write!(f, "`{command}` has no flag `{flag}`")
            }
            Self::Positional {
                command,
                synopsis,
                given,
            } => write!(
                f,
                "`{command}` takes {synopsis}, but {given} positional argument(s) were given"
            ),
            Self::UnsafeOutDir(raw) => write!(
                f,
                "`--out {raw}` is refused: it is the filesystem root, `.`, or ends in a `..` component"
            ),
        }
    }
}

impl std::error::Error for CliError {}

/// The usage text. Printed by `--help` and after a command-line error.
///
/// The exit codes are documented here because they are part of the tool's
/// contract: a script that wraps `osptool` needs to tell "you typed it wrong"
/// apart from "the game is not installed".
pub fn usage() -> String {
    format!(
        "osptool - inspect Spore DBPF packages offline\n\
         \n\
         USAGE:\n\
         \x20   osptool <SUBCOMMAND> [ARGS]\n\
         \n\
         SUBCOMMANDS:\n\
         \x20   list {SYNOPSIS_LIST}\n\
         \x20        Index rows in DBPF file order. `--limit` defaults to {DEFAULT_LIST_LIMIT}; 0 means unlimited.\n\
         \x20        `--names` adds the canonical type and group name columns.\n\
         \x20   find {SYNOPSIS_FIND}\n\
         \x20        Resolve one identity: which package answered, its extent, and whether it decodes.\n\
         \x20   describe {SYNOPSIS_DESCRIBE}\n\
         \x20        Decode a record according to its type id and print a structural summary.\n\
         \x20        A type with no decoder prints the index extent and says so; it never prints a summary\n\
         \x20        that looks decoded.\n\
         \x20   extract {SYNOPSIS_EXTRACT}\n\
         \x20        Write one record's bytes to <dir>/<sanitised name>. The package is only ever read.\n\
         \x20   manifest {SYNOPSIS_MANIFEST}\n\
         \x20        Canonical manifest over one or more packages, rows ascending by (type, group, instance).\n\
         \x20        Two runs over the same inputs are byte-identical. `--out` writes JSON Lines and reports\n\
         \x20        the write on stderr, so stdout carries only the document `--json` asked for.\n\
         \x20   verify {SYNOPSIS_VERIFY}\n\
         \x20        Walk every record and count decoded / container / failed / no-decoder.\n\
         \x20        Streams: one record is decoded at a time and nothing accumulates. Progress goes to\n\
         \x20        stderr every 10000 records, and only when stderr is a terminal.\n\
         \x20   types {SYNOPSIS_TYPES}\n\
         \x20        Print the canonical type table; `--group` (a flag, no value) adds the canonical group\n\
         \x20        table; `--package <p>` adds a per-package histogram merged with that package's own\n\
         \x20        0x01C7AC81:0x01C7AC81 prop directory, which maps TYPE IDS TO NAMES.\n\
         \x20   -h, --help           Print this text\n\
         \n\
         EXIT CODES:\n\
         \x20   {EXIT_OK}  ok\n\
         \x20   {EXIT_USAGE}  bad command line\n\
         \x20   {EXIT_NOT_FOUND}  record not found, or no package loaded\n\
         \x20   {EXIT_DECODE}  a record or package was found but the container layer refused it\n\
         \x20   {EXIT_IO}  an I/O failure\n\
         \n\
         NOTES:\n\
         \x20   A type with no decoder in this build exits {EXIT_OK} from `describe`: the record was found and\n\
         \x20   its extent read, which is a complete answer to the question asked. `verify` also exits\n\
         \x20   {EXIT_OK} when records fail, because it is a measurement: the failures are its output.\n\
         \x20   `find` exits {EXIT_OK} when the record was located even if the record does not decode; the verdict\n\
         \x20   is printed. Use `describe` when a decode failure should be fatal.\n\
         \x20   Every id field in a `--json` document is a 0x-prefixed hex string, so a value copied out of\n\
         \x20   one is directly usable as a `T:G:I` argument.\n"
    )
}

/// Parses arguments, **excluding** the program name.
///
/// Pure: no filesystem, no environment, no clock. Every failure is a
/// [`CliError`] naming the flag at fault.
pub fn parse<I, S>(args: I) -> Result<Request, CliError>
where
    I: IntoIterator<Item = S>,
    S: AsRef<str>,
{
    let args: Vec<String> = args.into_iter().map(|a| a.as_ref().to_owned()).collect();
    let mut cursor = Lexer::new(args);
    let Some(first) = cursor.next_token() else {
        return Err(CliError::NoCommand);
    };
    let command = match first {
        Token::Positional(command) => command,
        // `--help` before any subcommand is the documented spelling, and there
        // is no default subcommand to invent for any other flag.
        Token::Flag(flag) if flag == "--help" => return Ok(Request::Help),
        Token::Flag(flag) => return Err(CliError::UnknownCommand(flag)),
    };

    match command.as_str() {
        "list" => parse_list(&mut cursor).map(Request::List),
        "find" => parse_find(&mut cursor).map(Request::Find),
        "describe" => parse_describe(&mut cursor).map(Request::Describe),
        "extract" => parse_extract(&mut cursor).map(Request::Extract),
        "manifest" => parse_manifest(&mut cursor).map(Request::Manifest),
        "verify" => parse_verify(&mut cursor).map(Request::Verify),
        "types" => parse_types(&mut cursor).map(Request::Types),
        "help" => Ok(Request::Help),
        _ => Err(CliError::UnknownCommand(command)),
    }
}

fn parse_list(cursor: &mut Lexer) -> Result<ListRequest, CliError> {
    let mut package = None;
    let mut type_id = None;
    let mut group_id = None;
    let mut limit = DEFAULT_LIST_LIMIT;
    let mut json = false;
    let mut names = false;
    let mut positional = 0usize;

    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => {
                positional += 1;
                if positional > 1 {
                    return Err(positional_error("list", SYNOPSIS_LIST, positional));
                }
                package = Some(PathBuf::from(value));
            }
            Token::Flag(flag) => match flag.as_str() {
                "--type" => type_id = Some(cursor.hex_flag("--type", "a type id like 0x00e6bce5")?),
                "--group" => {
                    group_id = Some(cursor.hex_flag("--group", "a group id like 0x40616201")?)
                }
                "--limit" => {
                    let raw = cursor.value("--limit")?;
                    limit = raw.parse::<usize>().map_err(|_| CliError::BadValue {
                        flag: "--limit".to_owned(),
                        value: raw,
                        expected: "a non-negative count (0 means unlimited)",
                    })?;
                }
                "--json" => json = true,
                "--names" => names = true,
                other => return Err(unknown_flag("list", other)),
            },
        }
    }

    Ok(ListRequest {
        package: require_package("list", SYNOPSIS_LIST, positional, package)?,
        type_id,
        group_id,
        limit,
        json,
        names,
    })
}

fn parse_find(cursor: &mut Lexer) -> Result<FindRequest, CliError> {
    let mut package = None;
    let mut key = None;
    let mut json = false;
    let mut positional = 0usize;

    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => {
                positional += 1;
                match positional {
                    1 => package = Some(PathBuf::from(value)),
                    2 => key = Some(cursor.tgi(value)?),
                    _ => return Err(positional_error("find", SYNOPSIS_FIND, positional)),
                }
            }
            Token::Flag(flag) => match flag.as_str() {
                "--json" => json = true,
                other => return Err(unknown_flag("find", other)),
            },
        }
    }

    Ok(FindRequest {
        package: require_package("find", SYNOPSIS_FIND, positional, package)?,
        key: require_key("find", SYNOPSIS_FIND, positional, key)?,
        json,
    })
}

fn parse_describe(cursor: &mut Lexer) -> Result<RecordRequest, CliError> {
    let (package, key) = parse_record_args(cursor, "describe", SYNOPSIS_DESCRIBE)?;
    Ok(RecordRequest { package, key })
}

fn parse_extract(cursor: &mut Lexer) -> Result<ExtractRequest, CliError> {
    let mut package = None;
    let mut key = None;
    let mut out_dir = None;
    let mut positional = 0usize;

    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => {
                positional += 1;
                match positional {
                    1 => package = Some(PathBuf::from(value)),
                    2 => key = Some(cursor.tgi(value)?),
                    _ => return Err(positional_error("extract", SYNOPSIS_EXTRACT, positional)),
                }
            }
            Token::Flag(flag) => match flag.as_str() {
                "--out" => {
                    let raw = cursor.value("--out")?;
                    out_dir = Some(commands::extract::validate_out_dir(&raw)?);
                }
                other => return Err(unknown_flag("extract", other)),
            },
        }
    }

    Ok(ExtractRequest {
        package: require_package("extract", SYNOPSIS_EXTRACT, positional, package)?,
        key: require_key("extract", SYNOPSIS_EXTRACT, positional, key)?,
        out_dir: out_dir.ok_or(CliError::MissingValue {
            flag: "--out".to_owned(),
        })?,
    })
}

fn parse_manifest(cursor: &mut Lexer) -> Result<ManifestRequest, CliError> {
    let mut packages = Vec::new();
    let mut out_file = None;
    let mut json = false;
    let mut stats = false;

    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => packages.push(PathBuf::from(value)),
            Token::Flag(flag) => match flag.as_str() {
                "--out" => out_file = Some(PathBuf::from(cursor.value("--out")?)),
                "--json" => json = true,
                "--stats" => stats = true,
                other => return Err(unknown_flag("manifest", other)),
            },
        }
    }

    if packages.is_empty() {
        return Err(positional_error("manifest", SYNOPSIS_MANIFEST, 0));
    }
    Ok(ManifestRequest {
        packages,
        out_file,
        json,
        stats,
    })
}

fn parse_verify(cursor: &mut Lexer) -> Result<VerifyRequest, CliError> {
    let mut package = None;
    let mut type_id = None;
    let mut positional = 0usize;

    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => {
                positional += 1;
                if positional > 1 {
                    return Err(positional_error("verify", SYNOPSIS_VERIFY, positional));
                }
                package = Some(PathBuf::from(value));
            }
            Token::Flag(flag) => match flag.as_str() {
                "--type" => type_id = Some(cursor.hex_flag("--type", "a type id like 0x00e6bce5")?),
                other => return Err(unknown_flag("verify", other)),
            },
        }
    }

    Ok(VerifyRequest {
        package: require_package("verify", SYNOPSIS_VERIFY, positional, package)?,
        type_id,
    })
}

fn parse_types(cursor: &mut Lexer) -> Result<TypesRequest, CliError> {
    let mut group = false;
    let mut package = None;

    while let Some(token) = cursor.next_token() {
        match token {
            // `types` takes no positional arguments at all, and the message
            // must name the one that was supplied so the user can see it.
            Token::Positional(_) => {
                return Err(positional_error("types", SYNOPSIS_TYPES, 1));
            }
            Token::Flag(flag) => match flag.as_str() {
                "--group" => group = true,
                "--package" => {
                    if package.is_some() {
                        return Err(CliError::Repeated {
                            flag: "--package".into(),
                        });
                    }
                    package = Some(PathBuf::from(cursor.value("--package")?));
                }
                other => return Err(unknown_flag("types", other)),
            },
        }
    }

    Ok(TypesRequest { group, package })
}

/// `describe` and any future single-identity reader share this shape.
fn parse_record_args(
    cursor: &mut Lexer,
    command: CommandName,
    synopsis: &'static str,
) -> Result<(PathBuf, ResourceKey), CliError> {
    let mut package = None;
    let mut key = None;
    let mut positional = 0usize;
    while let Some(token) = cursor.next_token() {
        match token {
            Token::Positional(value) => {
                positional += 1;
                match positional {
                    1 => package = Some(PathBuf::from(value)),
                    2 => key = Some(cursor.tgi(value)?),
                    _ => return Err(positional_error(command, synopsis, positional)),
                }
            }
            Token::Flag(flag) => return Err(unknown_flag(command, &flag)),
        }
    }
    Ok((
        require_package(command, synopsis, positional, package)?,
        require_key(command, synopsis, positional, key)?,
    ))
}

fn positional_error(command: CommandName, synopsis: &'static str, given: usize) -> CliError {
    CliError::Positional {
        command,
        synopsis,
        given,
    }
}

fn unknown_flag(command: CommandName, flag: &str) -> CliError {
    CliError::UnknownFlag {
        command,
        flag: flag.to_owned(),
    }
}

fn require_package(
    command: CommandName,
    synopsis: &'static str,
    positional: usize,
    package: Option<PathBuf>,
) -> Result<PathBuf, CliError> {
    package.ok_or_else(|| positional_error(command, synopsis, positional))
}

fn require_key(
    command: CommandName,
    synopsis: &'static str,
    positional: usize,
    key: Option<ResourceKey>,
) -> Result<ResourceKey, CliError> {
    key.ok_or_else(|| positional_error(command, synopsis, positional))
}

/// One command-line token.
#[derive(Debug, Clone, PartialEq, Eq)]
enum Token {
    /// A bare word.
    Positional(String),
    /// A `--flag`, kept exactly as typed so error messages quote what the user
    /// wrote. `-h` is normalised to `--help` on the way in.
    Flag(String),
}

/// A one-pass token cursor with the flag-arity rules the subcommands share.
///
/// Arity is checked in exactly one place, so "a flag that needs a value takes
/// the next token, and only then" is not re-implemented seven times.
#[derive(Debug)]
struct Lexer {
    args: Vec<String>,
    index: usize,
}

impl Lexer {
    fn new(args: Vec<String>) -> Self {
        Self { args, index: 0 }
    }

    fn next_token(&mut self) -> Option<Token> {
        let raw = self.args.get(self.index)?.clone();
        self.index += 1;
        if raw == "-h" {
            return Some(Token::Flag("--help".to_owned()));
        }
        if raw.starts_with("--") {
            return Some(Token::Flag(raw));
        }
        Some(Token::Positional(raw))
    }

    /// Consumes the next token as this flag's value.
    ///
    /// A value that *looks* like a flag is still consumed: `--out --json` is a
    /// user who meant to write that filename, and reporting "missing value"
    /// would send them looking for a bug that is not there.
    fn value(&mut self, flag: &str) -> Result<String, CliError> {
        let next = self.args.get(self.index).cloned();
        match next {
            Some(value) => {
                self.index += 1;
                Ok(value)
            }
            None => Err(CliError::MissingValue {
                flag: flag.to_owned(),
            }),
        }
    }

    /// Reads a `u32` id, accepting `0x`-prefixed hex and decimal.
    fn hex_flag(&mut self, flag: &str, expected: &'static str) -> Result<u32, CliError> {
        let raw = self.value(flag)?;
        parse_id(&raw).ok_or_else(|| CliError::BadValue {
            flag: flag.to_owned(),
            value: raw,
            expected,
        })
    }

    /// Parses a positional `T:G:I` spec.
    fn tgi(&self, raw: String) -> Result<ResourceKey, CliError> {
        ResourceKey::parse_tgi(&raw).map_err(|_| CliError::BadValue {
            flag: "<T:G:I>".to_owned(),
            value: raw,
            expected: "a T:G:I triple such as 0x00e6bce5:0x40637e03:0x067a07f0",
        })
    }
}

/// Parses one id component: `0x`-prefixed hexadecimal or plain decimal.
///
/// The same rule `spore_core::ResourceKey` applies to a triple's components, so
/// `--type 15121637` and `--type 0x00e6bce5` name the same type. An empty string
/// and an overflowing value are both rejected rather than wrapped.
pub fn parse_id(text: &str) -> Option<u32> {
    let trimmed = text.trim();
    if trimmed.is_empty() {
        return None;
    }
    let (digits, radix) = match trimmed
        .strip_prefix("0x")
        .or_else(|| trimmed.strip_prefix("0X"))
    {
        Some(rest) => (rest, 16),
        None => (trimmed, 10),
    };
    if digits.is_empty() || !digits.chars().all(|c| c.is_ascii_hexdigit()) {
        return None;
    }
    u32::from_str_radix(digits, radix).ok()
}

/// Everything a command can fail with, in a form that carries its exit code.
///
/// The mapping from [`AssetError`] is one function ([`ToolError::from`]) so the
/// table in [`usage`] is checkable rather than asserted: a new asset error
/// variant has to be classified deliberately, and the test suite pins the result.
#[derive(Debug)]
pub enum ToolError {
    /// The command line was unusable. Exit [`EXIT_USAGE`].
    Usage(CliError),
    /// The identity or package was absent. Exit [`EXIT_NOT_FOUND`].
    NotFound(String),
    /// Found, but the container layer refused it. Exit [`EXIT_DECODE`].
    Decode(String),
    /// I/O failed. Exit [`EXIT_IO`].
    Io(String),
}

impl ToolError {
    /// The process exit code for this failure.
    pub const fn code(&self) -> i32 {
        match self {
            Self::Usage(_) => EXIT_USAGE,
            Self::NotFound(_) => EXIT_NOT_FOUND,
            Self::Decode(_) => EXIT_DECODE,
            Self::Io(_) => EXIT_IO,
        }
    }
}

impl From<CliError> for ToolError {
    fn from(value: CliError) -> Self {
        Self::Usage(value)
    }
}

impl From<std::io::Error> for ToolError {
    fn from(value: std::io::Error) -> Self {
        Self::Io(value.to_string())
    }
}

impl From<AssetError> for ToolError {
    /// Classifies an asset-layer failure into an exit code.
    ///
    /// The two interesting judgements:
    ///
    /// * [`AssetError::Open`] is **I/O**, not a decode failure: the file was
    ///   not readable, which is a missing game install or a wrong path, and
    ///   conflating it with "the container refused this record" would send an
    ///   operator looking for a decoder bug instead of a missing file.
    /// * [`AssetError::Dbpf`] is a **decode** failure: the file opened and its
    ///   bytes could not be read as a package, which is exactly what
    ///   `verify` exists to measure.
    ///
    /// [`AssetError::EmptyStore`] is "no package", which the tool's own exit
    /// table calls [`EXIT_NOT_FOUND`].
    fn from(value: AssetError) -> Self {
        match value {
            AssetError::Open { path, source } => Self::Io(format!("{path}: {source}")),
            AssetError::EmptyStore => {
                Self::NotFound("no package was loaded, so nothing can be resolved".to_owned())
            }
            AssetError::NotFound {
                key,
                searched,
                candidates,
            } => Self::NotFound(render_not_found(&key, searched, &candidates)),
            other => Self::Decode(other.to_string()),
        }
    }
}

/// Renders a miss: the library's message, then the near-miss candidates it
/// already computed.
///
/// The candidate list is *not* recomputed here. `ContentStore::find` collects it
/// and `spore_assets` owns that policy (which package contributes, how many);
/// a second implementation in this crate would be a second answer to the same
/// question. Note that `AssetError`'s `Display` does **not** include the
/// candidates even though the field is carried on the variant, so a caller that
/// only printed `{error}` silently dropped the one hint that makes a miss
/// actionable — hence this function exists.
fn render_not_found(key: &ResourceKey, searched: usize, candidates: &[ResourceKey]) -> String {
    let mut message = format!("no record `{key}` in any of the {searched} loaded package(s)");
    if candidates.is_empty() {
        // An empty list means "no suggestion was possible" -- typically an
        // unknown *type*, for which no near miss can exist. Saying so beats
        // printing an empty section.
        message.push_str(
            "\nno near-miss candidates: this build has no record of that type to suggest from",
        );
        return message;
    }
    message.push_str("\nnear-miss candidates:");
    for candidate in candidates {
        message.push_str(&format!("\n  {candidate}"));
    }
    message
}

impl std::fmt::Display for ToolError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::Usage(inner) => write!(f, "{inner}"),
            Self::NotFound(message) | Self::Decode(message) | Self::Io(message) => {
                f.write_str(message)
            }
        }
    }
}

impl std::error::Error for ToolError {}

/// Runs one parsed-or-parsed command, writing results to `out` and diagnostics
/// to `err`.
///
/// Both sinks are parameters so a test can drive a command with in-memory
/// buffers. `err` is also what `verify` writes progress to, and it is the sink
/// that decides whether progress is shown at all — see
/// [`commands::verify::progress_is_terminal`].
pub fn run<I, S>(args: I, out: &mut dyn Write, err: &mut dyn Write) -> Result<(), ToolError>
where
    I: IntoIterator<Item = S>,
    S: AsRef<str>,
{
    match parse(args)? {
        Request::Help => {
            write!(out, "{}", usage())?;
            Ok(())
        }
        Request::List(request) => commands::list::run(&request, out),
        Request::Find(request) => commands::find::run(&request, out),
        Request::Describe(request) => commands::describe::run(&request, out),
        Request::Extract(request) => commands::extract::run(&request, out),
        Request::Manifest(request) => commands::manifest::run(&request, out, err),
        Request::Verify(request) => {
            // The terminal check lives in the command, which owns the progress
            // policy; `run` has no business asking about `stderr`.
            let progress = commands::verify::stderr_is_terminal();
            commands::verify::run(&request, out, err, progress)
        }
        Request::Types(request) => commands::types::run(&request, out),
    }
}

/// Runs a command line and returns its exit code.
///
/// This is what the binary calls. It exists so that `main` is three lines, so
/// that a test can assert on an exit code without pattern-matching an error, and
/// so that the usage text is printed in exactly one place.
///
/// Usage text goes to `err` alongside a command-line error and to `out` for
/// `--help`, which is the convention the rest of this repository follows.
pub fn main_with(args: Vec<String>, out: &mut dyn Write, err: &mut dyn Write) -> i32 {
    match run(args, out, err) {
        Ok(()) => EXIT_OK,
        Err(error) => {
            if matches!(error, ToolError::Usage(_)) {
                let _ = write!(err, "\n{}", usage());
            }
            let _ = writeln!(err, "osptool: {error}");
            error.code()
        }
    }
}

/// [`main_with`] as a `std::process::ExitCode`, for `fn main`.
pub fn exit_code(
    args: Vec<String>,
    out: &mut dyn Write,
    err: &mut dyn Write,
) -> std::process::ExitCode {
    std::process::ExitCode::from(main_with(args, out, err) as u8)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn args(list: &[&str]) -> Vec<String> {
        list.iter().map(|s| (*s).to_owned()).collect()
    }

    #[test]
    fn no_arguments_is_a_usage_error_not_a_default_command() {
        assert_eq!(
            parse(Vec::<String>::new()).unwrap_err(),
            CliError::NoCommand
        );
        assert_eq!(
            main_with(Vec::new(), &mut Vec::new(), &mut Vec::new()),
            EXIT_USAGE
        );
    }

    #[test]
    fn an_unknown_subcommand_is_named() {
        assert_eq!(
            parse(args(&["frobnicate"])).unwrap_err(),
            CliError::UnknownCommand("frobnicate".into())
        );
    }

    #[test]
    fn a_leading_flag_is_not_mistaken_for_a_subcommand() {
        assert_eq!(
            parse(args(&["--json", "list", "p.package"])).unwrap_err(),
            CliError::UnknownCommand("--json".into())
        );
    }

    #[test]
    fn help_is_a_request_from_both_spellings() {
        assert_eq!(parse(args(&["-h"])).unwrap(), Request::Help);
        assert_eq!(parse(args(&["--help"])).unwrap(), Request::Help);
        assert_eq!(
            main_with(args(&["--help"]), &mut Vec::new(), &mut Vec::new()),
            EXIT_OK
        );
    }

    #[test]
    fn list_defaults_are_the_documented_ones() {
        let Request::List(req) = parse(args(&["list", "p.package"])).unwrap() else {
            panic!("expected a list request")
        };
        assert_eq!(req.package, PathBuf::from("p.package"));
        assert_eq!(req.limit, DEFAULT_LIST_LIMIT);
        assert_eq!(req.limit, 50);
        assert!(!req.json);
        assert!(!req.names);
        assert_eq!(req.type_id, None);
        assert_eq!(req.group_id, None);
    }

    #[test]
    fn list_accepts_every_flag_in_any_order() {
        let Request::List(req) = parse(args(&[
            "list",
            "--names",
            "--json",
            "--limit",
            "0",
            "--type",
            "0x00e6bce5",
            "--group",
            "0x40616201",
            "p.package",
        ]))
        .unwrap() else {
            panic!("expected a list request")
        };
        assert!(req.json && req.names);
        assert_eq!(req.limit, 0, "0 must survive as the unlimited sentinel");
        assert_eq!(req.type_id, Some(0x00e6_bce5));
        assert_eq!(req.group_id, Some(0x4061_6201));
        assert_eq!(req.package, PathBuf::from("p.package"));
    }

    #[test]
    fn list_rejects_a_missing_package_a_bad_limit_and_a_stray_flag() {
        assert!(matches!(
            parse(args(&["list"])).unwrap_err(),
            CliError::Positional { given: 0, .. }
        ));
        assert!(matches!(
            parse(args(&["list", "p", "--limit", "many"])).unwrap_err(),
            CliError::BadValue { flag, expected, .. } if flag == "--limit"
                && expected.contains("0 means unlimited")
        ));
        assert!(matches!(
            parse(args(&["list", "p", "--limit", "-1"])).unwrap_err(),
            CliError::BadValue { .. }
        ));
        assert_eq!(
            parse(args(&["list", "p", "--turbo"])).unwrap_err(),
            CliError::UnknownFlag {
                command: "list",
                flag: "--turbo".into()
            }
        );
        assert_eq!(
            parse(args(&["list", "a", "b"])).unwrap_err(),
            CliError::Positional {
                command: "list",
                synopsis: SYNOPSIS_LIST,
                given: 2
            }
        );
    }

    #[test]
    fn list_rejects_a_flag_with_no_value_and_names_it() {
        assert_eq!(
            parse(args(&["list", "p", "--type"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--type".into()
            }
        );
        assert_eq!(
            parse(args(&["list", "p", "--limit"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--limit".into()
            }
        );
    }

    #[test]
    fn id_flags_accept_hex_and_decimal_alike() {
        // One spelling of a number must not mean two ids.
        assert_eq!(parse_id("0x00e6bce5"), Some(0x00e6_bce5));
        assert_eq!(parse_id("15121637"), Some(0x00e6_bce5));
        assert_eq!(parse_id("0X00E6BCE5"), Some(0x00e6_bce5));
        assert_eq!(parse_id("  0x1 "), Some(1));
        assert_eq!(parse_id(""), None);
        assert_eq!(parse_id("0x"), None);
        assert_eq!(parse_id("-1"), None);
        assert_eq!(parse_id("0xzz"), None);
        assert_eq!(parse_id("0x1_0000_0000"), None, "overflow must not wrap");
        assert_eq!(parse_id("0x100000000"), None, "one bit too wide");
    }

    #[test]
    fn find_takes_a_package_and_a_triple() {
        let Request::Find(req) = parse(args(&[
            "find",
            "p.package",
            "0x00e6bce5:0x40637e03:0x067a07f0",
        ]))
        .unwrap() else {
            panic!("expected a find request")
        };
        assert_eq!(req.key.type_id, 0x00e6_bce5);
        assert_eq!(req.key.group_id, 0x4063_7e03);
        assert_eq!(req.key.instance_id, 0x067a_07f0);
        assert!(!req.json);

        let Request::Find(req) = parse(args(&["find", "p", "1:2:3", "--json"])).unwrap() else {
            panic!("expected a find request")
        };
        assert!(req.json, "--json is orthogonal to the identity");
    }

    #[test]
    fn find_and_describe_refuse_a_malformed_triple_with_the_expectation() {
        for command in ["find", "describe", "extract"] {
            let err = parse(args(&[command, "p", "not-a-triple"])).unwrap_err();
            assert!(
                matches!(&err, CliError::BadValue { value, expected, .. }
                    if value == "not-a-triple" && expected.contains("T:G:I")),
                "{command}: {err}"
            );
            assert_eq!(
                parse(args(&[command, "p"])).unwrap_err(),
                positional_error_for(command, 1),
                "{command} with a package but no identity"
            );
            assert_eq!(
                parse(args(&[command])).unwrap_err(),
                positional_error_for(command, 0),
                "{command} with neither"
            );
        }
    }

    /// The error `find`/`describe`/`extract` produce for the number of
    /// positionals the sub-parsers were actually given.
    fn positional_error_for(command: &'static str, given: usize) -> CliError {
        let synopsis = match command {
            "find" => SYNOPSIS_FIND,
            "describe" => SYNOPSIS_DESCRIBE,
            _ => SYNOPSIS_EXTRACT,
        };
        CliError::Positional {
            command,
            synopsis,
            given,
        }
    }

    #[test]
    fn describe_takes_no_flags_at_all() {
        assert_eq!(
            parse(args(&["describe", "p", "1:2:3", "--json"])).unwrap_err(),
            CliError::UnknownFlag {
                command: "describe",
                flag: "--json".into()
            }
        );
        assert!(matches!(
            parse(args(&["describe", "p", "1:2:3"])).unwrap(),
            Request::Describe(_)
        ));
    }

    #[test]
    fn extract_requires_a_safe_out_dir() {
        let Request::Extract(req) =
            parse(args(&["extract", "p", "1:2:3", "--out", "/tmp/out"])).unwrap()
        else {
            panic!("expected an extract request")
        };
        assert_eq!(req.out_dir, PathBuf::from("/tmp/out"));

        assert_eq!(
            parse(args(&["extract", "p", "1:2:3"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--out".into()
            }
        );
        assert_eq!(
            parse(args(&["extract", "p", "1:2:3", "--out"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--out".into()
            }
        );
        for refused in ["/", ".", "..", "out/..", "/tmp/.."] {
            assert!(
                matches!(
                    parse(args(&["extract", "p", "1:2:3", "--out", refused])).unwrap_err(),
                    CliError::UnsafeOutDir(_)
                ),
                "`--out {refused}` must be refused"
            );
        }
    }

    #[test]
    fn manifest_takes_many_packages_and_at_least_one() {
        let Request::Manifest(req) = parse(args(&[
            "manifest",
            "a.package",
            "b.package",
            "--stats",
            "--out",
            "m.jsonl",
        ]))
        .unwrap() else {
            panic!("expected a manifest request")
        };
        assert_eq!(
            req.packages,
            vec![PathBuf::from("a.package"), PathBuf::from("b.package")],
            "package order is resolution order and must be preserved"
        );
        assert!(req.stats);
        assert_eq!(req.out_file, Some(PathBuf::from("m.jsonl")));

        assert_eq!(
            parse(args(&["manifest"])).unwrap_err(),
            CliError::Positional {
                command: "manifest",
                synopsis: SYNOPSIS_MANIFEST,
                given: 0
            }
        );
        assert_eq!(
            parse(args(&["manifest", "a", "--out"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--out".into()
            }
        );
    }

    #[test]
    fn verify_takes_one_package_and_an_optional_type() {
        let Request::Verify(req) = parse(args(&["verify", "p", "--type", "0x2f4e681c"])).unwrap()
        else {
            panic!("expected a verify request")
        };
        assert_eq!(req.type_id, Some(0x2f4e_681c));

        let Request::Verify(req) = parse(args(&["verify", "p"])).unwrap() else {
            panic!("expected a verify request")
        };
        assert_eq!(req.type_id, None, "no --type means walk every record");

        assert!(matches!(
            parse(args(&["verify"])).unwrap_err(),
            CliError::Positional { given: 0, .. }
        ));
    }

    #[test]
    fn types_flags_are_boolean_and_package_takes_a_path() {
        let Request::Types(req) = parse(args(&["types"])).unwrap() else {
            panic!("expected a types request")
        };
        assert!(!req.group);
        assert_eq!(req.package, None);

        let Request::Types(req) =
            parse(args(&["types", "--group", "--package", "p.package"])).unwrap()
        else {
            panic!("expected a types request")
        };
        assert!(req.group);
        assert_eq!(req.package, Some(PathBuf::from("p.package")));

        // `--group` takes no value; a stray one is reported, not swallowed.
        assert_eq!(
            parse(args(&["types", "--group", "0x40616201"])).unwrap_err(),
            CliError::Positional {
                command: "types",
                synopsis: SYNOPSIS_TYPES,
                given: 1
            }
        );
        assert_eq!(
            parse(args(&["types", "--package"])).unwrap_err(),
            CliError::MissingValue {
                flag: "--package".into()
            }
        );
    }

    #[test]
    fn a_value_that_looks_like_a_flag_is_still_a_value() {
        // `--out --json` is a user who typed a filename, not a missing value.
        let Request::Manifest(req) = parse(args(&["manifest", "a", "--out", "--json"])).unwrap()
        else {
            panic!("expected a manifest request")
        };
        assert_eq!(req.out_file, Some(PathBuf::from("--json")));
        assert!(
            !req.json,
            "the flag-looking value was consumed as the value"
        );
    }

    #[test]
    fn usage_documents_every_subcommand_flag_and_exit_code() {
        let text = usage();
        for token in [
            "list",
            "find",
            "describe",
            "extract",
            "manifest",
            "verify",
            "types",
            "--type",
            "--group",
            "--limit",
            "--json",
            "--names",
            "--out",
            "--stats",
            "--package",
            "--help",
        ] {
            assert!(text.contains(token), "usage must document {token}");
        }
        for code in [EXIT_OK, EXIT_USAGE, EXIT_NOT_FOUND, EXIT_DECODE, EXIT_IO] {
            assert!(
                text.contains(&format!("{code}  ")),
                "usage must document exit code {code}"
            );
        }
    }

    #[test]
    fn the_exit_code_of_every_error_kind_is_pinned() {
        assert_eq!(ToolError::Usage(CliError::NoCommand).code(), EXIT_USAGE);
        assert_eq!(ToolError::NotFound(String::new()).code(), EXIT_NOT_FOUND);
        assert_eq!(ToolError::Decode(String::new()).code(), EXIT_DECODE);
        assert_eq!(ToolError::Io(String::new()).code(), EXIT_IO);
        // And through the process-facing entry point.
        assert_eq!(
            main_with(
                args(&["describe", "/nonexistent/x.package", "1:2:3"]),
                &mut Vec::new(),
                &mut Vec::new(),
            ),
            EXIT_IO,
            "a missing file is an I/O failure, not a decode failure"
        );
    }

    #[test]
    fn an_asset_error_maps_to_the_documented_exit_code() {
        let not_found = AssetError::NotFound {
            key: ResourceKey::new(1, 2, 3),
            searched: 1,
            candidates: Vec::new(),
        };
        assert_eq!(ToolError::from(not_found).code(), EXIT_NOT_FOUND);

        assert_eq!(
            ToolError::from(AssetError::EmptyStore).code(),
            EXIT_NOT_FOUND
        );

        let open = AssetError::Open {
            path: "x".to_owned(),
            source: std::io::Error::new(std::io::ErrorKind::NotFound, "nope"),
        };
        assert_eq!(ToolError::from(open).code(), EXIT_IO);

        let dbpf = AssetError::Dbpf {
            package: "p".to_owned(),
            source: spore_dbpf::DbpfError::ImageTooShort {
                len: 3,
                expected: spore_dbpf::HEADER_SIZE,
            },
        };
        assert_eq!(ToolError::from(dbpf).code(), EXIT_DECODE);
    }

    #[test]
    fn a_miss_renders_the_library_message_and_the_candidates() {
        let key = ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801);
        let message = render_not_found(
            &key,
            2,
            &[
                ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0802),
                ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0803),
            ],
        );
        assert!(message.contains("no record `0x00e6bce5:0x40616201:0x067a0801`"));
        assert!(message.contains("2 loaded package(s)"));
        assert!(message.contains("0x067a0802") && message.contains("0x067a0803"));
    }

    #[test]
    fn an_empty_candidate_list_says_why_rather_than_printing_nothing() {
        let key = ResourceKey::new(0xdead_beef, 1, 2);
        let message = render_not_found(&key, 1, &[]);
        assert!(message.contains("no near-miss candidates"));
        assert!(message.contains("0xdeadbeef"));
    }

    #[test]
    fn every_exit_code_is_in_the_documented_range_and_non_zero_for_failures() {
        for code in [EXIT_USAGE, EXIT_NOT_FOUND, EXIT_DECODE, EXIT_IO] {
            assert!((2..=5).contains(&code), "{code} must be 2..=5");
        }
        assert_eq!(EXIT_OK, 0);
    }
}
