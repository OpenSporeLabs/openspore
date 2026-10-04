//! A dependency-free, deliberately tolerant JSON reader and writer.
//!
//! # Why this exists instead of `serde_json`
//!
//! The harness is a *measurement instrument*. Its input is whatever the
//! Python oracles happen to print, produced by `json.dumps` running on a
//! different interpreter version than the one this file was written against.
//! Adding a parser whose first move on unexpected input is to return an error
//! would mean that a formatting difference between two machines is reported as
//! "the comparison failed", which is exactly the wrong conclusion: the
//! comparison has not run at all.
//!
//! So this parser is tolerant **on purpose**, and the tolerance is enumerated
//! rather than accidental:
//!
//! * `NaN`, `Infinity` and `-Infinity` are accepted as numbers. Python's
//!   `json.dumps` emits these bare (they are not valid JSON) for a
//!   non-finite float, and gmdl bounding boxes really do contain them.
//! * Trailing commas are accepted in arrays and objects. Python never emits
//!   them; hand-maintained fixtures sometimes do.
//! * Whitespace is skipped liberally, including newlines inside a value.
//! * Object members are stored in document order and looked up by name, so a
//!   field this crate does not know about is simply never read -- it cannot
//!   turn a semantic result into a parse failure.
//! * A parse failure is a typed error carrying the byte offset, never a panic
//!   and never a silently-defaulted value.
//!
//! What it deliberately does **not** tolerate: unbalanced brackets, unquoted
//! object keys, single-quoted strings, or trailing garbage after the top-level
//! value. Those are transcription errors, and hiding them would produce a
//! report whose numbers cannot be trusted.

use core::fmt;

/// A parsed JSON value.
///
/// Numbers are [`f64`]. Every value this harness reads is at most a `u32` id or
/// an IEEE-754 single-precision float lifted to double precision, so `f64`
/// represents all of them exactly.
#[derive(Debug, Clone, PartialEq)]
pub enum Json {
    /// `null`.
    Null,
    /// `true` / `false`.
    Bool(bool),
    /// Any number, including the non-finite literals Python emits.
    Num(f64),
    /// A string, with escapes already resolved.
    Str(String),
    /// An array, in document order.
    Arr(Vec<Json>),
    /// An object, in document order. Duplicated keys keep every occurrence.
    Obj(Vec<(String, Json)>),
}

impl Json {
    /// The object member named `key`, or `None` for a non-object or a miss.
    ///
    /// A miss is not an error: an unknown field is a field this harness does
    /// not consume, and treating that as a failure would be the opposite of
    /// tolerance.
    #[must_use]
    pub fn get(&self, key: &str) -> Option<&Json> {
        match self {
            Self::Obj(members) => members.iter().find(|(k, _)| k == key).map(|(_, v)| v),
            _ => None,
        }
    }

    /// The array elements, or `None` for a non-array.
    #[must_use]
    pub fn as_array(&self) -> Option<&[Json]> {
        match self {
            Self::Arr(items) => Some(items),
            _ => None,
        }
    }

    /// The string contents, or `None` for a non-string.
    #[must_use]
    pub fn as_str(&self) -> Option<&str> {
        match self {
            Self::Str(text) => Some(text),
            _ => None,
        }
    }

    /// The numeric value, or `None` for a non-number.
    #[must_use]
    pub fn as_f64(&self) -> Option<f64> {
        match self {
            Self::Num(value) => Some(*value),
            _ => None,
        }
    }

    /// The numeric value as a `u32`, or `None` for a non-number, a negative
    /// value, or one that does not fit.
    #[must_use]
    pub fn as_u32(&self) -> Option<u32> {
        let value = self.as_f64()?;
        if value.is_finite() && value >= 0.0 && value <= f64::from(u32::MAX) {
            // `f64 -> u32` is exact for every value in range; the bound above
            // is what makes the truncation well defined.
            Some(value as u32)
        } else {
            None
        }
    }

    /// The boolean value, or `None` for a non-boolean.
    #[must_use]
    pub fn as_bool(&self) -> Option<bool> {
        match self {
            Self::Bool(value) => Some(*value),
            _ => None,
        }
    }

    /// Appends the JSON text of this value to `out`.
    pub fn write(&self, out: &mut String) {
        match self {
            Self::Null => out.push_str("null"),
            Self::Bool(true) => out.push_str("true"),
            Self::Bool(false) => out.push_str("false"),
            Self::Num(value) => write_number(*value, out),
            Self::Str(text) => write_string(text, out),
            Self::Arr(items) => {
                out.push('[');
                for (index, item) in items.iter().enumerate() {
                    if index > 0 {
                        out.push(',');
                    }
                    item.write(out);
                }
                out.push(']');
            }
            Self::Obj(members) => {
                out.push('{');
                for (index, (key, value)) in members.iter().enumerate() {
                    if index > 0 {
                        out.push(',');
                    }
                    write_string(key, out);
                    out.push(':');
                    value.write(out);
                }
                out.push('}');
            }
        }
    }
}

impl fmt::Display for Json {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut text = String::new();
        self.write(&mut text);
        f.write_str(&text)
    }
}

/// A parse failure, with the byte offset where it was detected.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct JsonError {
    /// What went wrong.
    pub message: String,
    /// Byte offset into the input where the parser gave up.
    pub offset: usize,
}

impl fmt::Display for JsonError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "json: {} (at byte {})", self.message, self.offset)
    }
}

impl std::error::Error for JsonError {}

/// Parses one JSON document.
///
/// Trailing whitespace is allowed; trailing content is not, and the error says
/// where it was found.
pub fn parse(text: &str) -> Result<Json, JsonError> {
    let mut parser = Parser {
        bytes: text.as_bytes(),
        text,
        at: 0,
    };
    parser.skip_space();
    let value = parser.value()?;
    parser.skip_space();
    if parser.at != parser.bytes.len() {
        return Err(parser.error("trailing content after the top-level value"));
    }
    Ok(value)
}

/// The JSON text of a string, quoted and escaped. The building block for the
/// small request objects the harness sends to the oracle driver.
#[must_use]
pub fn string(value: &str) -> String {
    let mut out = String::with_capacity(value.len() + 2);
    write_string(value, &mut out);
    out
}

/// Builds an object from `(key, value)` pairs, skipping nothing and preserving
/// order. Convenience for the fixed-shape request envelopes.
#[must_use]
pub fn object(members: Vec<(&str, Json)>) -> Json {
    Json::Obj(
        members
            .into_iter()
            .map(|(key, value)| (key.to_owned(), value))
            .collect(),
    )
}

/// Writes a number in a form Python's `json.loads` accepts.
///
/// Non-finite values become the bare `NaN` / `Infinity` / `-Infinity` tokens
/// Python itself emits, because that is what the oracle driver will receive.
fn write_number(value: f64, out: &mut String) {
    if value.is_nan() {
        out.push_str("NaN");
    } else if value.is_infinite() {
        out.push_str(if value.is_sign_positive() {
            "Infinity"
        } else {
            "-Infinity"
        });
    } else if value == value.trunc() && value.abs() < 1e15 {
        // Rust's `{}` for `1.0` is already "1", which Python reads as an int.
        // Spelling it `1` keeps the two sides' idea of the type aligned.
        out.push_str(&format!("{value}"));
    } else {
        out.push_str(&format!("{value}"));
    }
}

/// Writes a quoted, escaped JSON string.
fn write_string(value: &str, out: &mut String) {
    out.push('"');
    for ch in value.chars() {
        match ch {
            '"' => out.push_str("\\\""),
            '\\' => out.push_str("\\\\"),
            '\n' => out.push_str("\\n"),
            '\r' => out.push_str("\\r"),
            '\t' => out.push_str("\\t"),
            '\u{08}' => out.push_str("\\b"),
            '\u{0C}' => out.push_str("\\f"),
            c if (c as u32) < 0x20 => out.push_str(&format!("\\u{:04x}", c as u32)),
            c => out.push(c),
        }
    }
    out.push('"');
}

struct Parser<'a> {
    bytes: &'a [u8],
    text: &'a str,
    at: usize,
}

impl Parser<'_> {
    fn error(&self, message: &str) -> JsonError {
        JsonError {
            message: message.to_owned(),
            offset: self.at,
        }
    }

    fn skip_space(&mut self) {
        while let Some(byte) = self.bytes.get(self.at) {
            if matches!(byte, b' ' | b'\t' | b'\n' | b'\r') {
                self.at += 1;
            } else {
                break;
            }
        }
    }

    fn peek(&self) -> Option<u8> {
        self.bytes.get(self.at).copied()
    }

    fn eat(&mut self, byte: u8) -> bool {
        if self.peek() == Some(byte) {
            self.at += 1;
            true
        } else {
            false
        }
    }

    /// Consumes `byte` if present, else records an error naming what was found.
    fn expect(&mut self, byte: u8) -> Result<(), JsonError> {
        if self.eat(byte) {
            Ok(())
        } else {
            let found = self
                .peek()
                .map_or_else(|| "end of input".to_owned(), |b| format!("{b:#04x}"));
            Err(self.error(&format!("expected {:?}, found {found}", byte as char)))
        }
    }

    fn literal(&mut self, word: &str) -> bool {
        if self.text[self.at..].starts_with(word) {
            self.at += word.len();
            true
        } else {
            false
        }
    }

    fn value(&mut self) -> Result<Json, JsonError> {
        self.skip_space();
        match self.peek() {
            Some(b'{') => self.object(),
            Some(b'[') => self.array(),
            Some(b'"') => Ok(Json::Str(self.string()?)),
            Some(b't') if self.literal("true") => Ok(Json::Bool(true)),
            Some(b'f') if self.literal("false") => Ok(Json::Bool(false)),
            Some(b'n') if self.literal("null") => Ok(Json::Null),
            // The non-finite literals Python's json module emits for a float
            // that is not finite. Checked before the numeric fallback so
            // `NaN` is not read as the start of a number and misreported.
            Some(b'N') if self.literal("NaN") => Ok(Json::Num(f64::NAN)),
            Some(b'I') if self.literal("Infinity") => Ok(Json::Num(f64::INFINITY)),
            Some(b'N') | Some(b'I') => Err(self.error("unknown literal")),
            Some(b'-') if self.text[self.at..].starts_with("-Infinity") => {
                self.at += "-Infinity".len();
                Ok(Json::Num(f64::NEG_INFINITY))
            }
            Some(byte) if byte == b'-' || byte.is_ascii_digit() => self.number(),
            Some(_) => Err(self.error("unexpected character at the start of a value")),
            None => Err(self.error("expected a value, found end of input")),
        }
    }

    fn object(&mut self) -> Result<Json, JsonError> {
        self.expect(b'{')?;
        let mut members = Vec::new();
        self.skip_space();
        if self.eat(b'}') {
            return Ok(Json::Obj(members));
        }
        loop {
            self.skip_space();
            // Tolerated: a trailing comma before the closing brace.
            if self.peek() == Some(b'}') {
                self.at += 1;
                return Ok(Json::Obj(members));
            }
            let key = self.string()?;
            self.skip_space();
            self.expect(b':')?;
            let value = self.value()?;
            members.push((key, value));
            self.skip_space();
            if self.eat(b',') {
                continue;
            }
            self.expect(b'}')?;
            return Ok(Json::Obj(members));
        }
    }

    fn array(&mut self) -> Result<Json, JsonError> {
        self.expect(b'[')?;
        let mut items = Vec::new();
        self.skip_space();
        if self.eat(b']') {
            return Ok(Json::Arr(items));
        }
        loop {
            self.skip_space();
            if self.peek() == Some(b']') {
                self.at += 1;
                return Ok(Json::Arr(items));
            }
            items.push(self.value()?);
            self.skip_space();
            if self.eat(b',') {
                continue;
            }
            self.expect(b']')?;
            return Ok(Json::Arr(items));
        }
    }

    fn string(&mut self) -> Result<String, JsonError> {
        self.expect(b'"')?;
        let mut out = String::new();
        loop {
            let byte = self
                .peek()
                .ok_or_else(|| self.error("unterminated string"))?;
            self.at += 1;
            match byte {
                b'"' => return Ok(out),
                b'\\' => {
                    let escape = self
                        .peek()
                        .ok_or_else(|| self.error("unterminated escape"))?;
                    self.at += 1;
                    match escape {
                        b'"' => out.push('"'),
                        b'\\' => out.push('\\'),
                        b'/' => out.push('/'),
                        b'b' => out.push('\u{08}'),
                        b'f' => out.push('\u{0C}'),
                        b'n' => out.push('\n'),
                        b'r' => out.push('\r'),
                        b't' => out.push('\t'),
                        b'u' => out.push(self.unicode_escape()?),
                        other => {
                            return Err(self.error(&format!("unknown escape \\{}", other as char)))
                        }
                    }
                }
                _ => {
                    // Multi-byte UTF-8: the input is a `&str`, so the byte just
                    // consumed starts a valid character and copying the whole
                    // remainder's tail one char at a time is correct.
                    let rest = &self.text[self.at - 1..];
                    let ch = rest
                        .chars()
                        .next()
                        .ok_or_else(|| self.error("unterminated string"))?;
                    out.push(ch);
                    self.at += ch.len_utf8() - 1;
                }
            }
        }
    }

    fn hex4(&mut self) -> Result<u32, JsonError> {
        let end = self.at + 4;
        let digits = self
            .text
            .get(self.at..end)
            .ok_or_else(|| self.error("truncated \\u escape"))?;
        let value = u32::from_str_radix(digits, 16)
            .map_err(|_| self.error("\\u escape is not four hex digits"))?;
        self.at = end;
        Ok(value)
    }

    fn unicode_escape(&mut self) -> Result<char, JsonError> {
        let first = self.hex4()?;
        // A high surrogate must be followed by \uDC00..\uDFFF to form a
        // supplementary code point. An unpaired surrogate is reported rather
        // than silently replaced: it would mean the two sides disagree about
        // the text, and that is a finding, not a formatting artefact.
        if (0xD800..0xDC00).contains(&first) {
            if !self.literal("\\u") {
                return Err(self.error("high surrogate not followed by a low surrogate"));
            }
            let second = self.hex4()?;
            if !(0xDC00..0xE000).contains(&second) {
                return Err(self.error("high surrogate not followed by a low surrogate"));
            }
            let code = 0x1_0000 + ((first - 0xD800) << 10) + (second - 0xDC00);
            char::from_u32(code).ok_or_else(|| self.error("surrogate pair is not a code point"))
        } else {
            char::from_u32(first)
                .ok_or_else(|| self.error("lone low surrogate is not a code point"))
        }
    }

    fn number(&mut self) -> Result<Json, JsonError> {
        let start = self.at;
        // A leading `-` is optional; `eat` reports whether it was there and the
        // digits loop below is what decides whether the number is well formed.
        self.eat(b'-');
        let digits_start = self.at;
        while matches!(self.peek(), Some(byte) if byte.is_ascii_digit()) {
            self.at += 1;
        }
        if self.at == digits_start {
            return Err(self.error("a number needs at least one digit"));
        }
        if self.eat(b'.') {
            let frac_start = self.at;
            while matches!(self.peek(), Some(byte) if byte.is_ascii_digit()) {
                self.at += 1;
            }
            if self.at == frac_start {
                return Err(self.error("a fraction needs at least one digit"));
            }
        }
        if matches!(self.peek(), Some(b'e') | Some(b'E')) {
            self.at += 1;
            if matches!(self.peek(), Some(b'+') | Some(b'-')) {
                self.at += 1;
            }
            let exp_start = self.at;
            while matches!(self.peek(), Some(byte) if byte.is_ascii_digit()) {
                self.at += 1;
            }
            if self.at == exp_start {
                return Err(self.error("an exponent needs at least one digit"));
            }
        }
        let slice = &self.text[start..self.at];
        slice.parse::<f64>().map(Json::Num).map_err(|_| JsonError {
            message: format!("{slice:?} is not a representable number"),
            offset: start,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn the_documented_shape_round_trips() {
        let value = object(vec![
            ("ok", Json::Bool(true)),
            ("count", Json::Num(17119.0)),
            ("name", Json::Str("Spore_Content.package".to_owned())),
            ("items", Json::Arr(vec![Json::Num(1.0), Json::Num(2.0)])),
            ("nothing", Json::Null),
        ]);
        let text = value.to_string();
        assert_eq!(parse(&text).unwrap(), value);
    }

    #[test]
    fn pythons_non_finite_floats_are_accepted() {
        // Exactly what json.dumps produces for a gmdl bounding box that holds a
        // NaN. A strict parser would reject the whole document.
        let parsed = parse(r#"{"radius": NaN, "min": -Infinity, "max": Infinity}"#).unwrap();
        assert!(parsed.get("radius").unwrap().as_f64().unwrap().is_nan());
        assert_eq!(parsed.get("min").unwrap().as_f64(), Some(f64::NEG_INFINITY));
        assert_eq!(parsed.get("max").unwrap().as_f64(), Some(f64::INFINITY));
    }

    #[test]
    fn a_trailing_comma_is_tolerated_and_an_unbalanced_brace_is_not() {
        assert!(parse("[1, 2, ]").is_ok());
        assert!(parse(r#"{"a": 1,}"#).is_ok());
        // `[1, 2` -> the `]` is missing, so the parser runs off the end while
        // looking for it. The offset it gives up at is the end of the input.
        let error = parse("[1, 2").unwrap_err();
        assert_eq!(error.offset, 5);
        assert!(error.message.contains("expected ']'"), "{error}");
    }

    #[test]
    fn an_unknown_field_is_never_read_and_never_fails() {
        let parsed = parse(r#"{"known": 1, "future_field": {"deep": [true]}}"#).unwrap();
        assert_eq!(parsed.get("known").and_then(Json::as_u32), Some(1));
        assert!(parsed.get("absent").is_none());
    }

    #[test]
    fn escapes_including_surrogate_pairs_resolve() {
        let parsed = parse(r#""aA😀\n""#).unwrap();
        assert_eq!(parsed.as_str(), Some("aA\u{1f600}\n"));
    }

    #[test]
    fn out_of_range_numbers_decline_rather_than_truncate() {
        assert_eq!(parse("4294967296").unwrap().as_u32(), None);
        assert_eq!(parse("-1").unwrap().as_u32(), None);
        assert_eq!(parse("4294967295").unwrap().as_u32(), Some(u32::MAX));
    }

    #[test]
    fn trailing_content_is_reported_with_its_offset() {
        let error = parse("{} {}").unwrap_err();
        assert!(error.message.contains("trailing content"));
        assert_eq!(error.offset, 3);
    }

    #[test]
    fn a_written_string_is_readable_back_as_the_same_text() {
        for value in ["", "plain", "quote\" backslash\\", "tab\tnl\n", "\u{1}"] {
            assert_eq!(parse(&string(value)).unwrap().as_str(), Some(value));
        }
    }
}
