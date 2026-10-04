//! Command line parsing.
//!
//! Hand-written rather than pulled from a crate, for two reasons: the flag set
//! is small and stable, and the engine's dependency graph is meant to stay
//! auditable (see the root `Cargo.toml`). Every parse is a pure function from
//! `&[String]` to [`LaunchRequest`], so the whole CLI is unit-testable without
//! spawning a process.
//!
//! # Exit behaviour
//!
//! A malformed command line is a *user error*, so it prints usage to stderr and
//! exits non-zero. A well-formed command line that cannot find its asset is a
//! *data* error, so it exits with [`EXIT_ASSET`] and prints a diagnosis that
//! names the packages searched. Keeping the two apart matters: one is a typo,
//! the other is a missing game install or a wrong record identity.

use std::path::PathBuf;

use spore_core::ResourceKey;

/// Exit code for a malformed command line (matches the `argparse` convention
/// the repository's Python tools already use).
pub const EXIT_USAGE: i32 = 2;

/// Exit code for a well-formed request whose asset could not be loaded.
pub const EXIT_ASSET: i32 = 3;

/// What the engine should do on start-up.
#[derive(Debug, Clone, PartialEq)]
pub enum LaunchRequest {
    /// Open a window with no Spore package, showing a placeholder.
    ///
    /// This is the `cargo run` default: the engine must be provably alive
    /// before any game data is involved, so "no data" is a first-class mode
    /// rather than an error.
    Placeholder(WindowOptions),

    /// Load Spore records and show them.
    Scene(SceneRequest),

    /// Print the usage text and exit successfully.
    Help,
}

/// Window sizing and title.
#[derive(Debug, Clone, PartialEq)]
pub struct WindowOptions {
    /// Physical width in pixels.
    ///
    /// Physical, not logical: Bevy scales a logical resolution by the display's
    /// scale factor, and this engine has no UI density to design for yet.
    pub width: u32,
    /// Physical height in pixels.
    pub height: u32,
    /// Window title.
    pub title: String,
}

impl Default for WindowOptions {
    fn default() -> Self {
        Self {
            width: 1280,
            height: 720,
            title: "OpenSpore".to_owned(),
        }
    }
}

/// A request to show real Spore content.
#[derive(Debug, Clone, PartialEq)]
pub struct SceneRequest {
    /// Packages in resolution order. Earlier wins.
    pub packages: Vec<PathBuf>,
    /// The record to show.
    pub record: ResourceKey,
    /// How the identity was chosen, for the on-screen banner.
    pub record_origin: RecordOrigin,
    /// World-space uniform scale applied to the loaded mesh.
    pub scale: f32,
    /// Window sizing and title.
    pub window: WindowOptions,
    /// Print what was loaded and exit without opening a window.
    pub info_only: bool,
    /// Resolve the model's texture references and apply the first that decodes.
    pub textured: bool,
    /// The record type assumed for a texture reference.
    ///
    /// A gmdl texture-set entry stores `{instance, group}` with **no type
    /// word**, so the type has to come from somewhere. It is a visible,
    /// overridable parameter rather than a constant buried in the resolver,
    /// because a wrong assumption produces a confidently wrong texture instead
    /// of an error.
    pub assumed_texture_type: u32,
}

/// How the record identity was chosen.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RecordOrigin {
    /// Given explicitly on the command line.
    Explicit,
    /// Chosen by a named, documented preset.
    Preset(&'static str),
    /// No packages were given, so nothing can be loaded.
    None,
}

/// The identity of the smallest geometry-bearing `gmdl` in the base content
/// package, and the asset the C++ vertical slice used.
///
/// 1156 bytes decompressed, 32 vertices, 20 triangles. Chosen because it is
/// the smallest record that still yields geometry; see `docs/ASSET-PATH.md`.
pub const PRESET_DOCUMENTED_ASSET: (u32, u32, u32) = (0x00E6_BCE5, 0x4063_7E03, 0x067A_07F0);

/// The largest creature model in the base content package: 2 meshes, 47 016
/// triangles, 1 351 408 bytes decompressed.
///
/// Group `0x40627100` is `CreatureModelsHQ` in
/// `tools/spore/types/groupnames.json`. Note that `CreatureModels`
/// (`0x40626200`) holds **no** gmdl records at all -- it carries traits,
/// summaries, `prop` and `png` previews -- so a creature model has to be
/// looked for in the HQ group. Measured, not assumed.
///
/// This record's material-info tail names shader-data id `0x218`, whose size is
/// unknown, so it decodes COMPLETELY through the mesh table and stops there.
/// Its geometry is fully validated; the report line says `decode=material-info`.
/// It is the milestone asset: the first real creature on screen.
pub const PRESET_CREATURE: (u32, u32, u32) = (0x00E6_BCE5, 0x4062_7100, 0x067C_79D2);

/// The named presets this build knows.
pub const PRESETS: &[(&str, (u32, u32, u32))] = &[
    ("documented-asset", PRESET_DOCUMENTED_ASSET),
    ("creature", PRESET_CREATURE),
];

/// Why a command line was rejected.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum CliError {
    /// A flag that needs a value was given none.
    MissingValue {
        /// The flag as the user typed it.
        flag: String,
    },
    /// A flag was repeated with incompatible values.
    Repeated {
        /// The flag as the user typed it.
        flag: String,
    },
    /// A value could not be parsed.
    BadValue {
        /// The flag as the user typed it.
        flag: String,
        /// What the user typed.
        value: String,
        /// What it should have been.
        expected: &'static str,
    },
    /// An unknown flag.
    UnknownFlag(String),
    /// A preset name that is not in [`PRESETS`].
    UnknownPreset(String),
    /// `--preset` or `--record` was required but absent.
    NoRecordRequested,
}

impl std::fmt::Display for CliError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Self::MissingValue { flag } => write!(f, "`{flag}` needs a value"),
            Self::Repeated { flag } => write!(f, "`{flag}` was given more than once"),
            Self::BadValue { flag, value, expected } => write!(f, "`{flag}` got `{value}`, expected {expected}"),
            Self::UnknownFlag(flag) => write!(f, "unknown flag `{flag}`"),
            Self::UnknownPreset(name) => write!(f, "unknown preset `{name}`"),
            Self::NoRecordRequested => write!(
                f,
                "nothing to load: pass `--record T:G:I`, `--preset {}`, or `--placeholder` for the no-data mode",
                PRESETS.iter().map(|(n, _)| *n).collect::<Vec<_>>().join("|")
            ),
        }
    }
}

impl std::error::Error for CliError {}

/// The usage text, printed on error and by `--help`.
pub fn usage() -> String {
    let presets = PRESETS
        .iter()
        .map(|(name, _)| *name)
        .collect::<Vec<_>>()
        .join(", ");
    format!(
        "openspore - a clean-room Rust + Bevy reimplementation of Spore\n\
         \n\
         USAGE:\n\
         \x20   openspore [OPTIONS]\n\
         \n\
         With --placeholder, opens a window showing a built-in mesh, so the\n\
         engine can be proven alive before any game data is involved.\n\
         \n\
         OPTIONS:\n\
         \x20   --package <PATH>     A Spore .package file. Repeatable. Earlier\n\
         \x20                       packages win when an identity appears in more\n\
         \x20                       than one, so list base content before patches.\n\
         \x20   --record <T:G:I>     The record to show, e.g. 0x00e6bce5:0x40637e03:0x067a07f0\n\
         \x20   --preset <NAME>      A named record. Known: {presets}\n\
         \x20   --scale <F>          Uniform scale applied to the mesh (default 1.0)\n\
         \x20   --width <PX>         Window width (default 1280)\n\
         \x20   --height <PX>        Window height (default 720)\n\
         \x20   --title <TEXT>       Window title\n\
         \x20   --info               Load, report, and exit without a window\n\
         \x20   --texture            Resolve the model's texture references and apply\n\
         \x20                       the first that decodes as the diffuse colour\n\
         \x20   --assumed-texture-type <ID>\n\
         \x20                       The record type assumed for a texture reference,\n\
         \x20                       which carries no type word (default 0x2f4e681c)\n\
         \x20   --placeholder        Show the built-in mesh with no game data at all\n\
         \x20   -h, --help           Print this text\n\
         \n\
         EXIT CODES:\n\
         \x20   0  ok            2  bad command line ({EXIT_USAGE})   3  asset unavailable ({EXIT_ASSET})\n"
    )
}

/// Parses arguments, **excluding** the program name.
pub fn parse<I, S>(args: I) -> Result<LaunchRequest, CliError>
where
    I: IntoIterator<Item = S>,
    S: AsRef<str>,
{
    let args: Vec<String> = args.into_iter().map(|a| a.as_ref().to_owned()).collect();
    parse_vec(&args)
}

fn parse_vec(args: &[String]) -> Result<LaunchRequest, CliError> {
    let mut packages: Vec<PathBuf> = Vec::new();
    let mut record: Option<ResourceKey> = None;
    let mut origin = RecordOrigin::None;
    let mut scale = 1.0f32;
    let mut window = WindowOptions::default();
    let mut info_only = false;
    let mut placeholder = false;
    let mut textured = false;
    let mut assumed_texture_type = spore_core::record::type_id::RASTER;

    let mut index = 0usize;
    while index < args.len() {
        let arg = args[index].as_str();
        let mut value_for = |name: &str| -> Result<String, CliError> {
            index += 1;
            args.get(index)
                .cloned()
                .ok_or_else(|| CliError::MissingValue {
                    flag: name.to_owned(),
                })
        };
        match arg {
            "-h" | "--help" => return Ok(LaunchRequest::Help),
            "--placeholder" => {
                // Explicitly asks for the no-data mode. Reached below via the
                // `record == None` arm, so it must not fall through.
                placeholder = true;
            }
            "--package" => packages.push(PathBuf::from(value_for("--package")?)),
            "--record" => {
                let raw = value_for("--record")?;
                record = Some(raw.parse::<ResourceKey>().map_err(|_| CliError::BadValue {
                    flag: "--record".into(),
                    value: raw,
                    expected: "a T:G:I triple",
                })?);
                origin = RecordOrigin::Explicit;
            }
            "--preset" => {
                let raw = value_for("--preset")?;
                let (name, triple) = PRESETS
                    .iter()
                    .find(|(name, _)| *name == raw)
                    .ok_or_else(|| CliError::UnknownPreset(raw.clone()))?;
                record = Some(ResourceKey::new(triple.0, triple.1, triple.2));
                origin = RecordOrigin::Preset(name);
            }
            "--scale" => {
                let raw = value_for("--scale")?;
                let parsed: f32 = raw.parse().map_err(|_| CliError::BadValue {
                    flag: "--scale".into(),
                    value: raw.clone(),
                    expected: "a number",
                })?;
                if !(parsed.is_finite() && parsed > 0.0) {
                    return Err(CliError::BadValue {
                        flag: "--scale".into(),
                        value: raw,
                        expected: "a finite number greater than zero",
                    });
                }
                scale = parsed;
            }
            "--width" => {
                let raw = value_for("--width")?;
                window.width = raw.parse().map_err(|_| CliError::BadValue {
                    flag: "--width".into(),
                    value: raw,
                    expected: "a pixel count",
                })?;
            }
            "--height" => {
                let raw = value_for("--height")?;
                window.height = raw.parse().map_err(|_| CliError::BadValue {
                    flag: "--height".into(),
                    value: raw,
                    expected: "a pixel count",
                })?;
            }
            "--title" => {
                window.title = value_for("--title")?;
            }
            "--info" => info_only = true,
            "--texture" => textured = true,
            "--assumed-texture-type" => {
                let raw = value_for("--assumed-texture-type")?;
                // `spore_core::parse_id`, not `u32::from_str`: the latter rejects
                // a `0x` prefix, and every other tool here accepts one.
                assumed_texture_type =
                    spore_core::parse_id(&raw).map_err(|_| CliError::BadValue {
                        flag: "--assumed-texture-type".into(),
                        value: raw,
                        expected: "a type id, decimal or 0x-prefixed hex",
                    })?;
            }
            other => return Err(CliError::UnknownFlag(other.to_owned())),
        }
        index += 1;
    }

    match record {
        Some(record) => {
            if window.title == WindowOptions::default().title {
                window.title = format!("OpenSpore - {}", record);
            }
            Ok(LaunchRequest::Scene(SceneRequest {
                packages,
                record,
                record_origin: origin,
                scale,
                window,
                info_only,
                textured,
                assumed_texture_type,
            }))
        }
        // Packages with no record is the ambiguous case: the caller named
        // game data but not what to show. Guessing a "nice" record here would
        // hide a typo behind a plausible picture, so it is a usage error.
        None if placeholder => Ok(LaunchRequest::Placeholder(window)),
        None => Err(CliError::NoRecordRequested),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn no_arguments_is_a_usage_error_not_a_silent_default() {
        // Bare `openspore` must NOT silently invent a record. The placeholder
        // mode is reachable only by asking for it with `--placeholder`, so a
        // bare invocation and a typo are distinguishable.
        assert_eq!(parse(["--help"]).unwrap(), LaunchRequest::Help);
        assert_eq!(
            parse(["--placeholder"]).unwrap(),
            LaunchRequest::Placeholder(WindowOptions::default())
        );
        assert_eq!(
            parse(Vec::<String>::new()).unwrap_err(),
            CliError::NoRecordRequested
        );
    }

    #[test]
    fn packages_without_a_record_are_a_usage_error_not_a_guess() {
        assert_eq!(
            parse(["--package", "/base.package"]).unwrap_err(),
            CliError::NoRecordRequested
        );
    }

    #[test]
    fn a_record_alone_produces_a_scene_request() {
        let LaunchRequest::Scene(req) =
            parse(["--record", "0x00e6bce5:0x40637e03:0x067a07f0"]).unwrap()
        else {
            panic!("expected a scene request");
        };
        assert_eq!(
            req.record,
            ResourceKey::new(0x00E6_BCE5, 0x4063_7E03, 0x067A_07F0)
        );
        assert_eq!(req.record_origin, RecordOrigin::Explicit);
        assert!(req.packages.is_empty());
        assert_eq!(req.scale, 1.0);
    }

    #[test]
    fn the_creature_preset_is_distinct_from_the_documented_asset() {
        let LaunchRequest::Scene(creature) = parse(["--preset", "creature"]).unwrap() else {
            panic!("expected a scene request");
        };
        assert_eq!(
            creature.record,
            ResourceKey::new(0x00E6_BCE5, 0x4062_7100, 0x067C_79D2)
        );
        assert_ne!(
            creature.record,
            ResourceKey::new(
                PRESET_DOCUMENTED_ASSET.0,
                PRESET_DOCUMENTED_ASSET.1,
                PRESET_DOCUMENTED_ASSET.2
            )
        );
    }

    #[test]
    fn a_preset_resolves_to_the_documented_identity() {
        let LaunchRequest::Scene(req) = parse(["--preset", "documented-asset"]).unwrap() else {
            panic!("expected a scene request");
        };
        assert_eq!(
            req.record,
            ResourceKey::new(0x00E6_BCE5, 0x4063_7E03, 0x067A_07F0)
        );
        assert_eq!(req.record_origin, RecordOrigin::Preset("documented-asset"));
    }

    #[test]
    fn an_unknown_preset_is_named_in_the_error() {
        assert_eq!(
            parse(["--preset", "nope"]).unwrap_err(),
            CliError::UnknownPreset("nope".into())
        );
    }

    #[test]
    fn packages_accumulate_in_command_line_order() {
        let LaunchRequest::Scene(req) = parse([
            "--package",
            "/base.package",
            "--package",
            "/patch.package",
            "--record",
            "1:2:3",
        ])
        .unwrap() else {
            panic!("expected a scene request");
        };
        assert_eq!(
            req.packages,
            vec![
                PathBuf::from("/base.package"),
                PathBuf::from("/patch.package")
            ]
        );
    }

    #[test]
    fn a_later_record_or_preset_wins_and_claims_the_origin() {
        let LaunchRequest::Scene(req) =
            parse(["--preset", "documented-asset", "--record", "0x01:0x02:0x03"]).unwrap()
        else {
            panic!("expected a scene request");
        };
        assert_eq!(req.record, ResourceKey::new(1, 2, 3));
        assert_eq!(req.record_origin, RecordOrigin::Explicit);
    }

    #[test]
    fn a_flag_without_its_value_is_reported_by_name() {
        assert_eq!(
            parse(["--record"]).unwrap_err(),
            CliError::MissingValue {
                flag: "--record".into()
            }
        );
        assert_eq!(
            parse(["--package"]).unwrap_err(),
            CliError::MissingValue {
                flag: "--package".into()
            }
        );
    }

    #[test]
    fn an_unknown_flag_is_refused_rather_than_ignored() {
        assert_eq!(
            parse(["--turbo"]).unwrap_err(),
            CliError::UnknownFlag("--turbo".into())
        );
    }

    #[test]
    fn malformed_values_are_refused_with_the_expectation_stated() {
        assert!(matches!(
            parse(["--record", "not-a-key"]).unwrap_err(),
            CliError::BadValue { flag, expected: "a T:G:I triple", .. } if flag == "--record"
        ));
        assert!(matches!(
            parse(["--scale", "0"]).unwrap_err(),
            CliError::BadValue { flag, .. } if flag == "--scale"
        ));
        assert!(matches!(
            parse(["--scale", "-1"]).unwrap_err(),
            CliError::BadValue { flag, .. } if flag == "--scale"
        ));
        assert!(matches!(
            parse(["--scale", "inf"]).unwrap_err(),
            CliError::BadValue { flag, .. } if flag == "--scale"
        ));
    }

    #[test]
    fn info_only_is_orthogonal_to_everything_else() {
        let LaunchRequest::Scene(req) = parse(["--record", "1:2:3", "--info"]).unwrap() else {
            panic!("expected a scene request");
        };
        assert!(req.info_only);
    }

    #[test]
    fn the_window_title_names_the_record_unless_it_was_set() {
        let LaunchRequest::Scene(default_title) = parse(["--record", "1:2:3"]).unwrap() else {
            panic!()
        };
        assert!(default_title.window.title.contains("0x00000001"));

        let LaunchRequest::Scene(custom) = parse(["--record", "1:2:3", "--title", "mine"]).unwrap()
        else {
            panic!()
        };
        assert_eq!(custom.window.title, "mine");
    }

    #[test]
    fn usage_mentions_every_flag_and_preset() {
        let text = usage();
        for flag in [
            "--package",
            "--record",
            "--preset",
            "--scale",
            "--width",
            "--height",
            "--title",
            "--info",
            "--placeholder",
        ] {
            assert!(text.contains(flag), "usage must document {flag}");
        }
        for (name, _) in PRESETS {
            assert!(text.contains(name), "usage must document preset {name}");
        }
    }
}
