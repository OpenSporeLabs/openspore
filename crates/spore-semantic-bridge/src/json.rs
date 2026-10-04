//! A strict, schema-driven JSON reader for the subset of the exchange format
//! this crate interprets.
//!
//! # Why hand-rolled, and why strict
//!
//! `serde` is not available to this crate, and even if it were, a *permissive*
//! deserialiser would be the wrong tool here. The consumer contract says a
//! record carrying fields this build does not know is refused rather than
//! silently half-read:
//!
//! > a consumer must not read a future schema as if it were today's
//!
//! So the reader is **schema-driven**: every object it expects is declared as a
//! static [`Spec`] of known fields with known shapes, and four things are
//! refused rather than absorbed.
//!
//! 1. **An unknown field** — a key not in the object's declared fields.
//!    Reported as [`JsonErrorKind::Schema`] with the full dotted field path.
//! 2. **A missing required field** — a key the spec marks required. A missing
//!    `identity.canonical_va` would otherwise become `""`, and a zero value
//!    standing in for "not stated" is precisely the substitution the exchange
//!    format forbids.
//! 3. **A repeated key** — two `canonical_va` keys in one record.
//!    `encoding/json` silently keeps the last one; an exchange file whose
//!    identity depends on which duplicate won is a file that can disagree with
//!    itself.
//! 4. **A wrong shape**, including a `null` where a value is required.
//!
//! # The one deliberate hole
//!
//! A few fields of the format are *open* by design — the exporter stores them
//! as raw JSON because their shape is not the format's to fix:
//! `reconstruction.promotion_supersedes` (a full promotion record including
//! compiler logs), `reconstruction.runtime_blocking_reason` (a string for 617
//! records and a list for one), `semantics.value.confidence` (a per-axis map
//! whose values mix rung names with numeric scores),
//! `validation.static_rollup` (mixed counters and a float ratio), and the two
//! raw blobs inside `names.identity_refuted`. Those are captured **verbatim**
//! by [`Shape::Raw`]/[`ObjMode::RawMap`] and surface as [`crate::RawJson`]. Their
//! internal structure is checked for well-formed JSON but not against a schema,
//! because there is no schema: enforcing one would mean inventing a second
//! opinion about an artifact this crate does not own. Everywhere the format is
//! closed, the closure is total.
//!
//! # Robustness
//!
//! Nesting is capped at [`MAX_DEPTH`] and objects at [`MAX_OBJECT_KEYS`], so a
//! hostile or corrupt file cannot exhaust the stack or run an unbounded
//! quadratic duplicate scan. Nothing in this module panics on any input.

use core::fmt;
use std::borrow::Cow;

/// Maximum object nesting accepted before the reader refuses the document.
///
/// The deepest closed shape in the format is
/// `reconstruction.value.validation.coverage.<dimension>`. The cap is generous
/// but finite: recursion on unbounded input is a stack-overflow panic, and "no
/// panics" is a contract this boundary keeps even against a malformed file.
pub(crate) const MAX_DEPTH: usize = 64;

/// Maximum keys accepted in one object.
///
/// The largest closed object in the snapshot is `validation.coverage`, with nine
/// dimensions. The duplicate scan is linear per key, so this bounds it.
pub(crate) const MAX_OBJECT_KEYS: usize = 1024;

/// Why a line was refused.
///
/// The distinction is the format's own: `Syntax` is corruption (the Go CLI's
/// exit 5), `Schema` is a document this build does not implement (exit 6).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub(crate) enum JsonErrorKind {
    /// The text is not well-formed JSON, or violates a structural limit.
    Syntax,
    /// The text is well formed but is not this schema.
    Schema,
}

impl fmt::Display for JsonErrorKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Syntax => f.write_str("corrupt"),
            Self::Schema => f.write_str("unsupported schema"),
        }
    }
}

/// A refusal, carrying the offending field's full dotted path.
#[derive(Debug, Clone, PartialEq, Eq)]
pub(crate) struct JsonError {
    pub kind: JsonErrorKind,
    /// The dotted path of the offending value, e.g. `vtable.value.memberships[3].slot`.
    pub path: String,
    pub message: String,
}

impl JsonError {
    /// Re-labels an accessor error with the path of the field being read.
    pub(crate) fn at(mut self, path: String) -> Self {
        self.path = path;
        self
    }
}

impl fmt::Display for JsonError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let path = if self.path.is_empty() {
            "<record>".to_owned()
        } else {
            self.path.clone()
        };
        write!(f, "{} at {path}: {}", self.kind, self.message)
    }
}

type Result<T> = core::result::Result<T, JsonError>;

/// A parsed JSON value, borrowing from the line it was read from.
#[derive(Debug)]
pub(crate) enum Val<'a> {
    Null,
    Bool(bool),
    Int(i64),
    Str(Cow<'a, str>),
    Array(Vec<Val<'a>>),
    Object(Obj<'a>),
    /// A value captured verbatim because its shape is the source's business.
    Raw(&'a str),
}

impl<'a> Val<'a> {
    pub(crate) fn as_str(&self) -> Result<&str> {
        match self {
            Val::Str(s) => Ok(s.as_ref()),
            other => Err(other.type_error("a string")),
        }
    }

    pub(crate) fn as_bool(&self) -> Result<bool> {
        match self {
            Val::Bool(b) => Ok(*b),
            other => Err(other.type_error("a boolean")),
        }
    }

    pub(crate) fn as_int(&self) -> Result<i64> {
        match self {
            Val::Int(i) => Ok(*i),
            other => Err(other.type_error("an integer")),
        }
    }

    pub(crate) fn as_array(&self) -> Result<&[Val<'a>]> {
        match self {
            Val::Array(items) => Ok(items),
            other => Err(other.type_error("an array")),
        }
    }

    pub(crate) fn as_object(&self) -> Result<&Obj<'a>> {
        match self {
            Val::Object(obj) => Ok(obj),
            other => Err(other.type_error("an object")),
        }
    }

    pub(crate) fn type_error(&self, wanted: &str) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Schema,
            path: String::new(),
            message: format!("expected {wanted}, found {}", self.type_name()),
        }
    }

    fn type_name(&self) -> &'static str {
        match self {
            Val::Null => "null",
            Val::Bool(_) => "a boolean",
            Val::Int(_) => "an integer",
            Val::Str(_) => "a string",
            Val::Array(_) => "an array",
            Val::Object(_) => "an object",
            Val::Raw(_) => "a raw value",
        }
    }
}

/// How an object's keys are interpreted.
#[derive(Clone, Copy)]
pub(crate) enum ObjMode {
    /// Keys must be declared in the field list; an unknown key is refused.
    Closed(&'static [Field]),
    /// Keys are data (upstream `map[string]T`); every value must be an object
    /// matching the spec, and every value is validated in full.
    MapOf(&'static Spec),
    /// Keys are data and every value is captured verbatim.
    RawMap,
}

/// An object whose keys were all recognised by its mode.
#[derive(Debug)]
pub(crate) struct Obj<'a> {
    path: String,
    /// A closed object's keys are the *declared* `&'static str`, so reading an
    /// object costs no key allocation and a key that got this far is guaranteed
    /// to be one this build knows.
    keys: Vec<Cow<'static, str>>,
    vals: Vec<Val<'a>>,
}

impl<'a> Obj<'a> {
    /// Whether the object carries no fields.
    #[allow(dead_code)]
    pub(crate) fn is_empty(&self) -> bool {
        self.vals.is_empty()
    }

    /// The dotted path of one of this object's fields.
    pub(crate) fn child(&self, key: &str) -> String {
        join_path(&self.path, key)
    }

    /// Every key/value pair, in file order.
    ///
    /// Only meaningful for the open-key modes ([`ObjMode::MapOf`] and
    /// [`ObjMode::RawMap`]), where the keys are data rather than schema — which
    /// is exactly where a field has no name to look up by.
    pub(crate) fn iter(&self) -> impl Iterator<Item = (&str, &Val<'a>)> {
        self.keys
            .iter()
            .zip(self.vals.iter())
            .map(|(k, v)| (k.as_ref(), v))
    }

    /// Looks a declared field up.
    pub(crate) fn get(&self, key: &str) -> Option<&Val<'a>> {
        self.keys
            .iter()
            .position(|k| k.as_ref() == key)
            .map(|i| &self.vals[i])
    }

    /// Looks up a field the format always writes.
    pub(crate) fn req(&self, key: &str) -> Result<&Val<'a>> {
        self.get(key).ok_or_else(|| self.missing(key))
    }

    /// Looks up a field the format omits when empty, or writes as `null`.
    pub(crate) fn opt(&self, key: &str) -> Option<&Val<'a>> {
        match self.get(key) {
            None | Some(Val::Null) => None,
            Some(value) => Some(value),
        }
    }

    /// Looks up a field the format always writes as a string.
    pub(crate) fn req_str(&self, key: &str) -> Result<&str> {
        let value = self.req(key)?;
        value.as_str().map_err(|e| e.at(self.child(key)))
    }

    /// Looks up a nullable or `omitempty` string field.
    pub(crate) fn opt_str(&self, key: &str) -> Result<Option<&str>> {
        match self.opt(key) {
            None => Ok(None),
            Some(value) => value.as_str().map(Some).map_err(|e| e.at(self.child(key))),
        }
    }

    /// Looks up a field the format always writes as a boolean.
    pub(crate) fn req_bool(&self, key: &str) -> Result<bool> {
        let value = self.req(key)?;
        value.as_bool().map_err(|e| e.at(self.child(key)))
    }

    /// Looks up a nullable or `omitempty` boolean field.
    pub(crate) fn opt_bool(&self, key: &str) -> Result<Option<bool>> {
        match self.opt(key) {
            None => Ok(None),
            Some(value) => value.as_bool().map(Some).map_err(|e| e.at(self.child(key))),
        }
    }

    /// Looks up a field the format always writes as an integer.
    pub(crate) fn req_int(&self, key: &str) -> Result<i64> {
        let value = self.req(key)?;
        value.as_int().map_err(|e| e.at(self.child(key)))
    }

    /// Looks up a nullable or `omitempty` integer field.
    pub(crate) fn opt_int(&self, key: &str) -> Result<Option<i64>> {
        match self.opt(key) {
            None => Ok(None),
            Some(value) => value.as_int().map(Some).map_err(|e| e.at(self.child(key))),
        }
    }

    /// Looks up a nullable or `omitempty` array of strings.
    pub(crate) fn opt_str_array(&self, key: &str) -> Result<Vec<&str>> {
        match self.opt(key) {
            None => Ok(Vec::new()),
            Some(value) => {
                let path = self.child(key);
                let items = value.as_array().map_err(|e| e.at(path.clone()))?;
                items
                    .iter()
                    .map(|item| item.as_str().map_err(|e| e.at(format!("{path}[]"))))
                    .collect()
            }
        }
    }

    /// Looks up a nullable or `omitempty` array of objects.
    pub(crate) fn opt_object_array(&self, key: &str) -> Result<Vec<&Obj<'a>>> {
        match self.opt(key) {
            None => Ok(Vec::new()),
            Some(value) => {
                let path = self.child(key);
                let items = value.as_array().map_err(|e| e.at(path.clone()))?;
                items
                    .iter()
                    .map(|item| item.as_object().map_err(|e| e.at(format!("{path}[]"))))
                    .collect()
            }
        }
    }

    /// A missing required field. Refused rather than defaulted: see the module
    /// docs for why a zero value is not an acceptable stand-in.
    fn missing(&self, key: &str) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Schema,
            path: self.child(key),
            message: "required field is absent; a missing field would become a zero value, and a zero value standing in for \"not stated\" is the substitution this format forbids".to_owned(),
        }
    }
}

/// A declared object: its dotted path and how its keys are read.
pub(crate) struct Spec {
    /// The dotted path of this object within the record, e.g. `vtable.value`.
    /// The record root is the empty string.
    ///
    /// The reader computes error paths from the traversal, so this field is not
    /// what it navigates by — it is the declaration the coherence test in
    /// `schema.rs` checks, which is how a hand-written path typo is caught.
    pub path: &'static str,
    pub mode: ObjMode,
}

/// One known field of a closed object.
pub(crate) struct Field {
    /// The JSON key, verbatim.
    pub key: &'static str,
    /// Whether the format always writes it. `false` means the exporter used
    /// `omitempty`, so absence is legal and means "not stated".
    pub required: bool,
    pub shape: Shape,
}

/// What a field's value must look like.
#[derive(Clone, Copy)]
pub(crate) enum Shape {
    Bool,
    BoolOrNull,
    Int,
    IntOrNull,
    Str,
    StrOrNull,
    /// The format's own three-valued boolean, spelled as the *strings* `"true"`,
    /// `"false"` and `"null"`. `"null"` is load-bearing in `abi.receiver` and
    /// `reconstruction.promoted`: it means "we looked and it is unknown", which
    /// is not the same as `"false"`.
    TriBool,
    /// An array of strings the format may write as `null`, or omit under
    /// `omitempty`.
    StrArrayOrNull,
    /// An array of objects, which the format may write as `null`.
    ArrayOrNull(&'static Spec),
    Object(&'static Spec),
    ObjectOrNull(&'static Spec),
    /// A value captured verbatim, because the format stores it as raw JSON.
    Raw,
    /// A verbatim value the format may write as `null`.
    RawOrNull,
}

impl Shape {
    fn accepts_null(self) -> bool {
        matches!(
            self,
            Shape::BoolOrNull
                | Shape::IntOrNull
                | Shape::StrOrNull
                | Shape::StrArrayOrNull
                | Shape::ArrayOrNull(_)
                | Shape::ObjectOrNull(_)
                | Shape::RawOrNull
        )
    }
}

/// Shorthand for a field the format always writes.
pub(crate) const fn req(key: &'static str, shape: Shape) -> Field {
    Field {
        key,
        required: true,
        shape,
    }
}

/// Shorthand for a field the exporter omits when empty.
pub(crate) const fn opt(key: &'static str, shape: Shape) -> Field {
    Field {
        key,
        required: false,
        shape,
    }
}

// ---------------------------------------------------------------------------
// The parser
// ---------------------------------------------------------------------------

/// A recursive-descent reader over one line of UTF-8 JSON.
pub(crate) struct Parser<'a> {
    buf: &'a [u8],
    pos: usize,
    depth: usize,
}

impl<'a> Parser<'a> {
    pub(crate) fn new(line: &'a str) -> Self {
        Self {
            buf: line.as_bytes(),
            pos: 0,
            depth: 0,
        }
    }

    /// Reads one complete object of the given spec and refuses trailing bytes.
    pub(crate) fn parse_one(&mut self, spec: &'static Spec) -> Result<Obj<'a>> {
        let root = spec.path.to_owned();
        self.skip_ws();
        let value = self.value(&Shape::Object(spec), &root)?;
        let obj = match value {
            Val::Object(obj) => obj,
            other => return Err(other.type_error("an object").at(root.clone())),
        };
        self.skip_ws();
        if self.pos != self.bytes().len() {
            return Err(self.syntax(&root, "more than one JSON value on this line"));
        }
        Ok(obj)
    }

    fn value(&mut self, shape: &Shape, path: &str) -> Result<Val<'a>> {
        self.skip_ws();
        let byte = self
            .peek()
            .ok_or_else(|| self.syntax(path, "unexpected end of line"))?;
        if byte == b'n' {
            self.expect_null(path)?;
            if shape.accepts_null() {
                return Ok(Val::Null);
            }
            return Err(self.schema(path, "null is not a value this field can hold"));
        }
        match shape {
            Shape::Raw | Shape::RawOrNull => Ok(Val::Raw(self.raw_span(path)?)),
            Shape::Str | Shape::StrOrNull => self.string(path).map(Val::Str),
            Shape::Bool | Shape::BoolOrNull => self.boolean(path).map(Val::Bool),
            Shape::Int | Shape::IntOrNull => self.integer(path).map(Val::Int),
            Shape::TriBool => {
                let text = self.string(path)?;
                match text.as_ref() {
                    "true" | "false" | "null" => Ok(Val::Str(text)),
                    other => Err(self.schema(
                        path,
                        format!(
                            "expected one of the strings \"true\", \"false\", \"null\", found {other:?}"
                        ),
                    )),
                }
            }
            Shape::StrArrayOrNull => {
                let items = self.array(path, |p, at| p.string(at).map(Val::Str))?;
                Ok(Val::Array(items))
            }
            Shape::ArrayOrNull(spec) => {
                let items = self.array(path, |p, at| p.value(&Shape::Object(spec), at))?;
                Ok(Val::Array(items))
            }
            Shape::Object(spec) | Shape::ObjectOrNull(spec) => {
                Ok(Val::Object(self.read_object(spec.mode, path.to_owned())?))
            }
        }
    }

    fn array<F>(&mut self, path: &str, mut item: F) -> Result<Vec<Val<'a>>>
    where
        F: FnMut(&mut Self, &str) -> Result<Val<'a>>,
    {
        self.enter(path)?;
        self.expect_array(path)?;
        let mut out = Vec::new();
        self.skip_ws();
        if self.peek() == Some(b']') {
            self.pos += 1;
            self.depth -= 1;
            return Ok(out);
        }
        loop {
            let at = format!("{path}[{}]", out.len());
            out.push(item(self, &at)?);
            self.skip_ws();
            match self.peek() {
                Some(b',') => {
                    self.pos += 1;
                    self.skip_ws();
                    if self.peek() == Some(b']') {
                        return Err(self.syntax(path, "trailing comma in array"));
                    }
                }
                Some(b']') => {
                    self.pos += 1;
                    break;
                }
                _ => return Err(self.syntax(path, "expected ',' or ']' in array")),
            }
        }
        self.depth -= 1;
        Ok(out)
    }

    /// Reads one object at the dotted path `path`.
    fn read_object(&mut self, mode: ObjMode, path: String) -> Result<Obj<'a>> {
        self.enter(&path)?;
        self.expect_object(&path)?;
        let mut keys: Vec<Cow<'static, str>> = Vec::new();
        let mut vals: Vec<Val<'a>> = Vec::new();
        self.skip_ws();
        if self.peek() == Some(b'}') {
            self.pos += 1;
            self.depth -= 1;
            return self.finish_object(mode, path, keys, vals);
        }
        loop {
            self.skip_ws();
            if self.peek().is_none() {
                return Err(self.syntax(&path, "unterminated object"));
            }
            let key = self.string(&path)?;
            let child = join_path(&path, &key);
            self.skip_ws();
            self.expect(&child, b':')?;
            let value = match mode {
                ObjMode::Closed(fields) => {
                    let Some(field) = find_field(fields, &key) else {
                        return Err(self.unknown_field(&child, &key));
                    };
                    if keys.iter().any(|k| k.as_ref() == field.key) {
                        return Err(self.duplicate(&child, &key));
                    }
                    keys.push(Cow::Borrowed(field.key));
                    self.value(&field.shape, &child)?
                }
                ObjMode::MapOf(spec) => {
                    if keys.iter().any(|k| k.as_ref() == key.as_ref()) {
                        return Err(self.duplicate(&child, &key));
                    }
                    keys.push(Cow::Owned(key.into_owned()));
                    self.value(&Shape::Object(spec), &child)?
                }
                ObjMode::RawMap => {
                    if keys.iter().any(|k| k.as_ref() == key.as_ref()) {
                        return Err(self.duplicate(&child, &key));
                    }
                    keys.push(Cow::Owned(key.into_owned()));
                    self.value(&Shape::Raw, &child)?
                }
            };
            vals.push(value);
            if keys.len() > MAX_OBJECT_KEYS {
                return Err(self.syntax(
                    &path,
                    format!("object has more than {MAX_OBJECT_KEYS} keys"),
                ));
            }
            self.skip_ws();
            match self.peek() {
                Some(b',') => {
                    self.pos += 1;
                    self.skip_ws();
                    if self.peek() == Some(b'}') {
                        return Err(self.syntax(&path, "trailing comma in object"));
                    }
                }
                Some(b'}') => {
                    self.pos += 1;
                    break;
                }
                _ => return Err(self.syntax(&path, "expected ',' or '}' in object")),
            }
        }
        self.depth -= 1;
        self.finish_object(mode, path, keys, vals)
    }

    fn finish_object(
        &self,
        mode: ObjMode,
        path: String,
        keys: Vec<Cow<'static, str>>,
        vals: Vec<Val<'a>>,
    ) -> Result<Obj<'a>> {
        if let ObjMode::Closed(fields) = mode {
            for field in fields {
                if field.required && !keys.iter().any(|k| k.as_ref() == field.key) {
                    return Err(JsonError {
                        kind: JsonErrorKind::Schema,
                        path: join_path(&path, field.key),
                        message: "required field is absent; a missing field would become a zero value, and a zero value standing in for \"not stated\" is the substitution this format forbids".to_owned(),
                    });
                }
            }
        }
        Ok(Obj { path, keys, vals })
    }

    /// Captures a value verbatim, validating that it is well-formed JSON.
    fn raw_span(&mut self, path: &str) -> Result<&'a str> {
        let start = self.pos;
        self.skip_value(path)?;
        core::str::from_utf8(self.bytes()[start..self.pos].as_ref())
            .map_err(|_| self.syntax(path, "value is not valid UTF-8"))
    }

    fn skip_value(&mut self, path: &str) -> Result<()> {
        self.skip_ws();
        match self
            .peek()
            .ok_or_else(|| self.syntax(path, "unexpected end of line"))?
        {
            b'{' => {
                self.enter(path)?;
                self.pos += 1;
                self.skip_ws();
                if self.peek() == Some(b'}') {
                    self.pos += 1;
                    self.depth -= 1;
                    return Ok(());
                }
                loop {
                    self.skip_ws();
                    self.string(path)?;
                    self.skip_ws();
                    self.expect(path, b':')?;
                    self.skip_value(path)?;
                    self.skip_ws();
                    match self.peek() {
                        Some(b',') => self.pos += 1,
                        Some(b'}') => {
                            self.pos += 1;
                            break;
                        }
                        _ => return Err(self.syntax(path, "expected ',' or '}'")),
                    }
                }
                self.depth -= 1;
                Ok(())
            }
            b'[' => {
                self.enter(path)?;
                self.pos += 1;
                self.skip_ws();
                if self.peek() == Some(b']') {
                    self.pos += 1;
                    self.depth -= 1;
                    return Ok(());
                }
                loop {
                    self.skip_value(path)?;
                    self.skip_ws();
                    match self.peek() {
                        Some(b',') => self.pos += 1,
                        Some(b']') => {
                            self.pos += 1;
                            break;
                        }
                        _ => return Err(self.syntax(path, "expected ',' or ']'")),
                    }
                }
                self.depth -= 1;
                Ok(())
            }
            b'"' => {
                self.string(path)?;
                Ok(())
            }
            b't' | b'f' | b'n' | b'-' | b'0'..=b'9' => self.literal(path),
            other => Err(self.syntax(path, format!("unexpected byte {other:#04x}"))),
        }
    }

    fn literal(&mut self, path: &str) -> Result<()> {
        for word in ["true", "false", "null"] {
            if self.bytes()[self.pos..].starts_with(word.as_bytes()) {
                self.pos += word.len();
                return Ok(());
            }
        }
        if self.peek() == Some(b'-') {
            self.pos += 1;
        }
        let digits_start = self.pos;
        while matches!(self.peek(), Some(b'0'..=b'9')) {
            self.pos += 1;
        }
        if self.pos == digits_start {
            return Err(self.syntax(path, "expected a number"));
        }
        // JSON forbids a leading zero, and `01` is the one number a permissive
        // reader accepts and a strict one must not.
        if self.pos - digits_start > 1 && self.bytes()[digits_start] == b'0' {
            return Err(self.syntax(path, "number has a leading zero"));
        }
        if self.peek() == Some(b'.') {
            self.pos += 1;
            let frac_start = self.pos;
            while matches!(self.peek(), Some(b'0'..=b'9')) {
                self.pos += 1;
            }
            if self.pos == frac_start {
                return Err(self.syntax(path, "expected digits after '.'"));
            }
        }
        if matches!(self.peek(), Some(b'e') | Some(b'E')) {
            self.pos += 1;
            if matches!(self.peek(), Some(b'+') | Some(b'-')) {
                self.pos += 1;
            }
            let exp_start = self.pos;
            while matches!(self.peek(), Some(b'0'..=b'9')) {
                self.pos += 1;
            }
            if self.pos == exp_start {
                return Err(self.syntax(path, "expected digits in exponent"));
            }
        }
        Ok(())
    }

    fn integer(&mut self, path: &str) -> Result<i64> {
        let start = self.pos;
        match self.peek() {
            Some(b'-') | Some(b'+') => {
                return Err(self.syntax(path, "expected an integer, found a sign"))
            }
            Some(byte) if !byte.is_ascii_digit() => {
                let found = match byte {
                    b'"' => "a string",
                    b'{' => "an object",
                    b'[' => "an array",
                    b'.' | b'e' | b'E' => "a floating-point number",
                    _ => "a literal",
                };
                return Err(self.schema(path, format!("expected an integer, found {found}")));
            }
            None => return Err(self.syntax(path, "unexpected end of line")),
            Some(_) => {}
        }
        self.literal(path)?;
        let text = core::str::from_utf8(self.bytes()[start..self.pos].as_ref())
            .map_err(|_| self.syntax(path, "number is not valid UTF-8"))?;
        if text.contains(['.', 'e', 'E']) {
            return Err(self.schema(
                path,
                format!("expected an integer, found the floating-point number {text}"),
            ));
        }
        text.parse::<i64>()
            .map_err(|_| self.syntax(path, "integer does not fit in 64 bits"))
    }

    fn boolean(&mut self, path: &str) -> Result<bool> {
        if self.bytes()[self.pos..].starts_with(b"true") {
            self.pos += 4;
            Ok(true)
        } else if self.bytes()[self.pos..].starts_with(b"false") {
            self.pos += 5;
            Ok(false)
        } else {
            Err(self.schema(path, "expected a boolean"))
        }
    }

    fn expect_null(&mut self, path: &str) -> Result<()> {
        if self.bytes()[self.pos..].starts_with(b"null") {
            self.pos += 4;
            Ok(())
        } else {
            Err(self.syntax(path, "expected null"))
        }
    }

    fn string(&mut self, path: &str) -> Result<Cow<'a, str>> {
        self.skip_ws();
        if self.peek() != Some(b'"') {
            return Err(self.wrong_type(path, "a string"));
        }
        self.pos += 1;
        let start = self.pos;
        while let Some(byte) = self.peek() {
            match byte {
                b'"' => {
                    let text = core::str::from_utf8(self.bytes()[start..self.pos].as_ref())
                        .map_err(|_| self.syntax(path, "string is not valid UTF-8"))?;
                    self.pos += 1;
                    return Ok(Cow::Borrowed(text));
                }
                b'\\' => return self.string_escaped(path, start),
                0x00..=0x1f => return Err(self.syntax(path, "unescaped control byte in string")),
                _ => self.pos += 1,
            }
        }
        Err(self.syntax(path, "unterminated string"))
    }

    fn string_escaped(&mut self, path: &str, start: usize) -> Result<Cow<'a, str>> {
        let mut out = String::with_capacity(32);
        out.push_str(
            core::str::from_utf8(self.bytes()[start..self.pos].as_ref())
                .map_err(|_| self.syntax(path, "string is not valid UTF-8"))?,
        );
        while let Some(byte) = self.peek() {
            match byte {
                b'"' => {
                    self.pos += 1;
                    return Ok(Cow::Owned(out));
                }
                b'\\' => {
                    self.pos += 1;
                    let escape = self
                        .peek()
                        .ok_or_else(|| self.syntax(path, "unterminated escape"))?;
                    self.pos += 1;
                    match escape {
                        b'"' => out.push('"'),
                        b'\\' => out.push('\\'),
                        b'/' => out.push('/'),
                        b'b' => out.push('\u{8}'),
                        b'f' => out.push('\u{c}'),
                        b'n' => out.push('\n'),
                        b'r' => out.push('\r'),
                        b't' => out.push('\t'),
                        b'u' => out.push(self.unicode_escape(path)?),
                        other => {
                            return Err(
                                self.syntax(path, format!("unknown escape \\{}", other as char))
                            )
                        }
                    }
                }
                0x00..=0x1f => return Err(self.syntax(path, "unescaped control byte in string")),
                _ => {
                    let from = self.pos;
                    while !matches!(
                        self.peek(),
                        Some(b'"') | Some(b'\\') | Some(0x00..=0x1f) | None
                    ) {
                        self.pos += 1;
                    }
                    out.push_str(
                        core::str::from_utf8(self.bytes()[from..self.pos].as_ref())
                            .map_err(|_| self.syntax(path, "string is not valid UTF-8"))?,
                    );
                }
            }
        }
        Err(self.syntax(path, "unterminated string"))
    }

    fn unicode_escape(&mut self, path: &str) -> Result<char> {
        let first = self.hex4(path)?;
        if (0xd800..0xdc00).contains(&first) {
            if !self.bytes()[self.pos..].starts_with(b"\\u") {
                return Err(self.syntax(path, "lone high surrogate in \\u escape"));
            }
            self.pos += 2;
            let second = self.hex4(path)?;
            if !(0xdc00..0xe000).contains(&second) {
                return Err(self.syntax(path, "high surrogate not followed by a low surrogate"));
            }
            let code = 0x1_0000 + ((first - 0xd800) << 10) + (second - 0xdc00);
            char::from_u32(code)
                .ok_or_else(|| self.syntax(path, "surrogate pair is not a code point"))
        } else {
            char::from_u32(first)
                .ok_or_else(|| self.syntax(path, "\\u escape is not a Unicode scalar value"))
        }
    }

    fn hex4(&mut self, path: &str) -> Result<u32> {
        if self.pos + 4 > self.bytes().len() {
            return Err(self.syntax(path, "truncated \\u escape"));
        }
        let mut value = 0u32;
        for offset in 0..4 {
            let digit = (self.bytes()[self.pos + offset] as char)
                .to_digit(16)
                .ok_or_else(|| self.syntax(path, "non-hex digit in \\u escape"))?;
            value = value * 16 + digit;
        }
        self.pos += 4;
        Ok(value)
    }

    fn enter(&mut self, path: &str) -> Result<()> {
        self.depth += 1;
        if self.depth > MAX_DEPTH {
            return Err(self.syntax(path, format!("nesting deeper than {MAX_DEPTH} levels")));
        }
        Ok(())
    }

    fn expect(&mut self, path: &str, byte: u8) -> Result<()> {
        if self.peek() == Some(byte) {
            self.pos += 1;
            Ok(())
        } else {
            Err(self.syntax(path, format!("expected {:?}", byte as char)))
        }
    }

    /// Opens an object, reporting a *wrong type* as a schema problem rather than
    /// as malformed text: `{"leaf": 7}` is well-formed JSON that is not this
    /// schema, and calling it corruption would collapse the two diagnoses the
    /// exit codes exist to keep apart.
    fn expect_object(&mut self, path: &str) -> Result<()> {
        self.skip_ws();
        match self.peek() {
            Some(b'{') => {
                self.pos += 1;
                Ok(())
            }
            Some(_) => Err(self.wrong_type(path, "an object")),
            None => Err(self.syntax(path, "unexpected end of line")),
        }
    }

    /// Opens an array, with the same typing rule as [`Parser::expect_object`].
    fn expect_array(&mut self, path: &str) -> Result<()> {
        self.skip_ws();
        match self.peek() {
            Some(b'[') => {
                self.pos += 1;
                Ok(())
            }
            Some(_) => Err(self.wrong_type(path, "an array")),
            None => Err(self.syntax(path, "unexpected end of line")),
        }
    }

    /// Classifies the value that is actually there, so the message names what
    /// was found.
    fn wrong_type(&self, path: &str, wanted: &str) -> JsonError {
        let found = match self.peek() {
            Some(b'"') => "a string",
            Some(b'{') => "an object",
            Some(b'[') => "an array",
            Some(b't') | Some(b'f') => "a boolean",
            Some(b'n') => "null",
            Some(b'-') | Some(b'0'..=b'9') => "a number",
            // A byte that cannot begin any JSON value is not the wrong type, it
            // is not JSON: corruption, not a schema this build does not know.
            Some(other) => return self.syntax(path, format!("unexpected byte {other:#04x}")),
            None => return self.syntax(path, "unexpected end of line"),
        };
        self.schema(path, format!("expected {wanted}, found {found}"))
    }

    fn peek(&self) -> Option<u8> {
        self.bytes().get(self.pos).copied()
    }

    /// Reborrows the input with its original lifetime, so a slice of it can be
    /// handed out as `&'a str` rather than as a borrow of `&self`.
    fn bytes(&self) -> &'a [u8] {
        self.buf
    }

    fn skip_ws(&mut self) {
        while matches!(self.peek(), Some(b' ' | b'\t' | b'\n' | b'\r')) {
            self.pos += 1;
        }
    }

    fn unknown_field(&self, path: &str, key: &str) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Schema,
            path: path.to_owned(),
            message: format!(
                "unknown field {key:?}; this build implements only the fields declared for this object, and a record carrying a field it does not know is refused rather than half-read"
            ),
        }
    }

    fn duplicate(&self, path: &str, key: &str) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Schema,
            path: path.to_owned(),
            message: format!(
                "field {key:?} appears more than once; which duplicate wins must not decide a function's identity"
            ),
        }
    }

    fn syntax(&self, path: &str, message: impl Into<String>) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Syntax,
            path: path.to_owned(),
            message: message.into(),
        }
    }

    fn schema(&self, path: &str, message: impl Into<String>) -> JsonError {
        JsonError {
            kind: JsonErrorKind::Schema,
            path: path.to_owned(),
            message: message.into(),
        }
    }
}

fn join_path(parent: &str, key: &str) -> String {
    if parent.is_empty() {
        key.to_owned()
    } else {
        format!("{parent}.{key}")
    }
}

fn find_field(fields: &'static [Field], key: &str) -> Option<&'static Field> {
    fields
        .iter()
        .find(|f| f.key.len() == key.len() && f.key == key)
}

#[cfg(test)]
mod tests {
    use super::*;

    static CHECK: Spec = Spec {
        path: "root.check",
        mode: ObjMode::Closed(&[req("status", Shape::Str)]),
    };

    static MAP: Spec = Spec {
        path: "root.dims",
        mode: ObjMode::MapOf(&CHECK),
    };

    static LEAF: Spec = Spec {
        path: "leaf",
        mode: ObjMode::Closed(&[
            req("a", Shape::Int),
            opt("b", Shape::StrOrNull),
            req("t", Shape::TriBool),
            req("list", Shape::StrArrayOrNull),
        ]),
    };

    static ROOT: Spec = Spec {
        path: "",
        mode: ObjMode::Closed(&[
            req("leaf", Shape::Object(&LEAF)),
            opt("raw", Shape::Raw),
            opt("rawnull", Shape::RawOrNull),
        ]),
    };

    fn parse(line: &str) -> Result<Obj<'_>> {
        Parser::new(line).parse_one(&ROOT)
    }

    #[test]
    fn an_unknown_field_is_refused_with_its_path() {
        let err = parse(r#"{"leaf":{"a":1,"t":"null","list":null,"surprise":2}}"#)
            .expect_err("must be refused");
        assert_eq!(err.kind, JsonErrorKind::Schema);
        assert_eq!(err.path, "leaf.surprise");
        assert!(err.message.contains("unknown field"), "{}", err.message);
    }

    #[test]
    fn an_unknown_field_names_its_full_path_from_the_root() {
        let err = parse(r#"{"leaf":{"a":1,"t":"null","list":null},"trailing":1}"#)
            .expect_err("must be refused");
        assert_eq!(err.kind, JsonErrorKind::Schema);
        assert_eq!(err.path, "trailing");
    }

    #[test]
    fn a_missing_required_field_is_refused() {
        let err = parse(r#"{"leaf":{"t":"true","list":null}}"#).expect_err("must be refused");
        assert_eq!(err.kind, JsonErrorKind::Schema);
        assert_eq!(err.path, "leaf.a");
    }

    #[test]
    fn a_repeated_key_is_refused() {
        let err =
            parse(r#"{"leaf":{"a":1,"a":2,"t":"true","list":null}}"#).expect_err("must be refused");
        assert_eq!(err.kind, JsonErrorKind::Schema);
        assert_eq!(err.path, "leaf.a");
        assert!(err.message.contains("more than once"));
    }

    #[test]
    fn a_null_where_a_value_is_required_is_refused() {
        for text in [
            r#"{"leaf":{"a":null,"t":"true","list":null}}"#,
            r#"{"leaf":{"a":1,"t":null,"list":null}}"#,
            r#"{"leaf":{"a":1,"t":"true"}}"#,
            r#"{"leaf":{"a":1,"t":"true","list":null,"raw":null}}"#,
        ] {
            let err = parse(text).expect_err("must be refused");
            assert_eq!(err.kind, JsonErrorKind::Schema, "{text}");
        }
    }

    #[test]
    fn a_non_object_where_an_object_is_required_is_refused() {
        for text in [
            r#"{"leaf":7}"#,
            r#"{"leaf":"text"}"#,
            r#"{"leaf":[1,2]}"#,
            r#"{"leaf":null}"#,
            r#"{"leaf":{}}"#,
            r#"{"leaf":[]}"#,
            r#"{"leaf":true}"#,
        ] {
            let err = parse(text).expect_err("must be refused");
            assert_eq!(err.kind, JsonErrorKind::Schema, "{text} -> {err}");
        }
    }

    #[test]
    fn a_scalar_where_a_record_is_expected_is_refused() {
        // Well-formed JSON of the wrong shape is a *schema* refusal; only text
        // that is not JSON at all is corruption. The two must not collapse.
        for text in ["7", "\"function\"", "[]", "null", "true", "3.5", "{}"] {
            let err = parse(text).expect_err("must be refused");
            assert_eq!(err.kind, JsonErrorKind::Schema, "{text} -> {err}");
        }
        for text in ["", " ", "{", "{,", "@"] {
            let err = parse(text).expect_err("must be refused");
            assert_eq!(err.kind, JsonErrorKind::Syntax, "{text:?} -> {err}");
        }
    }

    #[test]
    fn trailing_garbage_is_refused() {
        let err = parse(r#"{"leaf":{"a":1,"t":"null","list":null}} {"leaf":{}}"#)
            .expect_err("must be refused");
        assert!(err.message.contains("more than one JSON value"), "{err}");
    }

    #[test]
    fn truncated_documents_are_refused_not_panicked_on() {
        for text in [
            "",
            " ",
            "{",
            "{\"leaf\"",
            "{\"leaf\":",
            "{\"leaf\":{",
            "{\"leaf\":{\"a\":",
            "{\"leaf\":{\"a\":1,",
            r#"{"leaf":{"a":1,"t":"tr"#,
            r#"{"leaf":{"a":1,"t":"tru"#,
            r#"{"leaf":{"a":1,"t":"\uD"#,
            "{\"leaf\":{\"a\":1,\"t\":\"\\",
            r#"{"leaf":{"a":1,"t":"\ud800"}}"#,
            r#"{"leaf":{"a":1,"t":"\ud800x"}}"#,
            r#"{"leaf":{"a":1,"t":"\uzzzz","list":null}}"#,
            r#"{"leaf":{"a":1,"t":"null","list":[1]}}"#,
            r#"{"leaf":{"a":1,"t":"null","list":null,}}"#,
            r#"{"leaf":{"a":01,"t":"null","list":null}}"#,
            r#"{"leaf":{"a":1e5,"t":"null","list":null}}"#,
            r#"{"leaf":{"a":1.5,"t":"null","list":null}}"#,
            r#"{"leaf":{"a":7,"t":"null","list":"x"}}"#,
        ] {
            let err = parse(text).expect_err("must be refused");
            assert!(
                matches!(err.kind, JsonErrorKind::Syntax | JsonErrorKind::Schema),
                "{text:?} -> {err}"
            );
        }
    }

    #[test]
    fn deep_nesting_is_refused_instead_of_overflowing_the_stack() {
        // A raw span is still walked for well-formedness, so 4096 nested arrays
        // is real recursion. The depth cap turns it into an error rather than a
        // stack overflow.
        let deep = format!("{{\"raw\":{}1{}}}", "[".repeat(4096), "]".repeat(4096));
        let err = parse(&deep).expect_err("must be refused");
        assert!(err.message.contains("nesting"), "{err}");
        assert_eq!(err.path, "raw");

        let deep_objects = format!(
            "{{\"raw\":{}{}}}",
            r#"{"x":"#.repeat(2048),
            "1".to_owned() + &"}".repeat(2048)
        );
        let err = parse(&deep_objects).expect_err("must be refused");
        assert!(err.message.contains("nesting"), "{err}");
    }

    #[test]
    fn escapes_and_surrogate_pairs_are_decoded() {
        let obj = parse(r#"{"leaf":{"a":1,"b":"tab\there \"q\" \\ é 😀","t":"false","list":[]}}"#)
            .expect("parses");
        let leaf = obj.vals[0].as_object().expect("object");
        assert_eq!(
            leaf.req_str("b").expect("string"),
            "tab\there \"q\" \\ \u{e9} \u{1f600}"
        );
    }

    #[test]
    fn a_non_canonical_tri_state_string_is_refused() {
        let err = parse(r#"{"leaf":{"a":1,"t":"TRUE","list":null}}"#).expect_err("refused");
        assert!(err.message.contains("\"true\""), "{err}");
    }

    #[test]
    fn a_raw_value_is_captured_verbatim_and_validated() {
        let obj = parse(
            r#"{"leaf":{"a":1,"t":"null","list":null},"raw":{"b":[1,2,{"c":null}],"a":"z"}}"#,
        )
        .expect("parses");
        assert_eq!(
            match &obj.vals[1] {
                Val::Raw(text) => *text,
                other => panic!("expected a raw value, found {}", other.type_name()),
            },
            r#"{"b":[1,2,{"c":null}],"a":"z"}"#
        );

        let err = parse(r#"{"leaf":{"a":1,"t":"null","list":null},"raw":{"b":[1,2}}"#)
            .expect_err("must be refused");
        assert_eq!(err.kind, JsonErrorKind::Syntax);
        assert_eq!(err.path, "raw");
    }

    #[test]
    fn an_open_key_object_validates_every_value() {
        static WITH_MAP: Spec = Spec {
            path: "",
            mode: ObjMode::Closed(&[req("dims", Shape::ObjectOrNull(&MAP))]),
        };
        let good = Parser::new(r#"{"dims":{"ABI":{"status":"PASS"},"CALLS":{"status":"FAIL"}}}"#)
            .parse_one(&WITH_MAP)
            .expect("parses");
        let dims = good.vals[0].as_object().expect("object");
        assert!(dims.get("CALLS").is_some());
        let bad = Parser::new(r#"{"dims":{"ABI":{"status":7}}}"#)
            .parse_one(&WITH_MAP)
            .expect_err("must be refused");
        assert_eq!(bad.kind, JsonErrorKind::Schema);
        assert_eq!(bad.path, "dims.ABI.status");
    }

    #[test]
    fn an_open_raw_map_captures_every_value() {
        static WITH_RAW_MAP: Spec = Spec {
            path: "",
            mode: ObjMode::Closed(&[req("conf", Shape::ObjectOrNull(&RAW_CONF))]),
        };
        static RAW_CONF: Spec = Spec {
            path: "conf",
            mode: ObjMode::RawMap,
        };
        let obj = Parser::new(r#"{"conf":{"mechanics":"SUPPORTED","overall":0.72}}"#)
            .parse_one(&WITH_RAW_MAP)
            .expect("parses");
        let conf = obj.vals[0].as_object().expect("object");
        assert_eq!(
            match conf.get("overall").expect("present") {
                Val::Raw(text) => *text,
                other => panic!("expected raw, found {}", other.type_name()),
            },
            "0.72"
        );
    }
}
