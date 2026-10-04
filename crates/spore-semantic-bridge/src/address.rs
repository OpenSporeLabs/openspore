//! Virtual addresses and the canonical spelling rule.
//!
//! # One spelling, always
//!
//! Every committed OpenSpore artifact keys on a canonical VA spelled
//! `"0x%08x"`, lowercase, prefix included. `tools/reconstruction_knowledge.py`
//! normalises to it, `tools/spore-semantic/internal/semantic/addr.go`
//! transcribes that normaliser, and this module is the third transcription of
//! the same rule. `format_va` is therefore the *only* way this crate renders an
//! address, and [`Va::parse_canonical`] is the only way it accepts one.
//!
//! # Input tolerance is a different question from output strictness
//!
//! The CLI accepts `925050`, `00925050`, `0x925050`, `dec:9588816` and
//! `rva:00525050` because a human types addresses. A *snapshot* must not: the
//! runtime overlay loader refuses `"925050"` and `"0X00925050"` for exactly the
//! reason [`Va::parse_canonical`] does — if two spellings of one address were
//! both accepted, one address could become two entries.
//!
//! Bare digits are **hex** everywhere in this repository. `925050` is
//! `0x00925050`, not nine hundred thousand. Decimal therefore needs an explicit
//! `dec:`/`0d` prefix and a relative address needs an explicit `rva:` prefix;
//! see [`Va::parse_input`].

use core::fmt;

/// The error a refused address spelling produces.
#[derive(Debug, Clone, PartialEq, Eq, thiserror::Error)]
pub enum AddressError {
    /// The text is not `0x` followed by exactly eight lowercase hex digits.
    #[error("not a canonical VA: {text:?} ({reason})")]
    NotCanonical {
        /// The spelling that was refused, verbatim.
        text: String,
        /// What is wrong with it.
        reason: &'static str,
    },
    /// The text carried no digits at all.
    #[error("empty address")]
    Empty,
    /// The digits are not a number in the requested base.
    #[error("not a number in base {base}: {text:?}")]
    NotANumber {
        /// The digits that were refused, verbatim.
        text: String,
        /// The base they were read in.
        base: u32,
    },
    /// A VA below the image base cannot have an RVA.
    #[error("{va:#010x} is below image base {image_base:#010x}")]
    BelowImageBase {
        /// The address that was refused.
        va: u32,
        /// The snapshot's declared image base.
        image_base: u32,
    },
    /// `rva + image_base` left the 32-bit range.
    #[error("rva {rva:#010x} + image base {image_base:#010x} is outside x86-32")]
    Overflow {
        /// The relative address that was supplied.
        rva: u32,
        /// The snapshot's declared image base.
        image_base: u32,
    },
}

/// A 32-bit virtual address (the exchange format's `x86:LE:32`).
///
/// The number is stored as a `u32` so sorting, bisection and range tests are
/// exact; it is rendered as text only at the JSON boundary.
#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub struct Va(u32);

impl Va {
    /// Wraps an address the caller already resolved as a number.
    pub const fn new(value: u32) -> Self {
        Self(value)
    }

    /// The address as a number.
    pub const fn as_u32(self) -> u32 {
        self.0
    }

    /// Parses the **canonical** spelling and nothing else: `0x` then exactly
    /// eight lowercase hex digits.
    ///
    /// `"0x00925050"` is accepted. `"925050"`, `"00925050"`, `"0x925050"`,
    /// `"0X00925050"`, `"0x0092505"` and `"0x009250500"` are all refused, with
    /// a reason. This is deliberately *stricter* than the Go snapshot loader,
    /// which parses a record's `canonical_va` with the tolerant CLI parser; the
    /// runtime overlay loader applies this rule instead, and a bridge that
    /// accepted both spellings could index one address twice.
    pub fn parse_canonical(text: &str) -> Result<Self, AddressError> {
        let Some(digits) = text.strip_prefix("0x") else {
            return Err(AddressError::NotCanonical {
                text: text.to_owned(),
                reason: "missing the lowercase \"0x\" prefix",
            });
        };
        let bytes = digits.as_bytes();
        if bytes.len() != 8 {
            return Err(AddressError::NotCanonical {
                text: text.to_owned(),
                reason: "not exactly 8 hex digits after the prefix",
            });
        }
        if !bytes
            .iter()
            .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(b))
        {
            return Err(AddressError::NotCanonical {
                text: text.to_owned(),
                reason: "not 8 lowercase hex digits",
            });
        }
        let value = u32::from_str_radix(digits, 16).expect("eight validated hex digits");
        Ok(Self(value))
    }

    /// Parses every spelling the CLI contract promises, for *caller* input.
    ///
    /// This never touches snapshot content; it exists so an engine can accept
    /// `"rva:00525050"` on a command line and then treat the result as a
    /// number. Accepted forms are hex with an optional `0x`, explicit decimal
    /// via `dec:`/`0d`, and explicit relative via `rva:`.
    pub fn parse_input(text: &str, image_base: u32) -> Result<Self, AddressError> {
        let text = text.trim();
        if text.is_empty() {
            return Err(AddressError::Empty);
        }
        let (text, is_rva) = match strip_prefix_fold(text, "rva:") {
            Some(rest) => (rest.trim(), true),
            None => (text, false),
        };
        let (text, base) = if let Some(rest) = strip_prefix_fold(text, "dec:") {
            (rest.trim(), 10)
        } else if let Some(rest) = strip_prefix_fold(text, "0d") {
            (rest.trim(), 10)
        } else if let Some(rest) = strip_prefix_fold(text, "0x") {
            (rest.trim(), 16)
        } else {
            // Bare digits are hex. Reading them as decimal would answer a
            // different question silently.
            (text, 16)
        };
        if text.is_empty() {
            return Err(AddressError::Empty);
        }
        if text.contains([' ', '_', '-']) {
            return Err(AddressError::NotANumber {
                text: text.to_owned(),
                base,
            });
        }
        let value = u64::from_str_radix(text, base).map_err(|_| AddressError::NotANumber {
            text: text.to_owned(),
            base,
        })?;
        if value > u64::from(u32::MAX) {
            return Err(AddressError::NotANumber {
                text: text.to_owned(),
                base,
            });
        }
        let value = value as u32;
        if is_rva {
            let sum = u64::from(value) + u64::from(image_base);
            if sum > u64::from(u32::MAX) {
                return Err(AddressError::Overflow {
                    rva: value,
                    image_base,
                });
            }
            return Ok(Self(sum as u32));
        }
        Ok(Self(value))
    }

    /// The canonical `"0x%08x"` rendering.
    pub fn canonical(self) -> String {
        format_va(self.0)
    }

    /// The bare 8-char lowercase hex spelling used by `functions.tsv`, the
    /// triage JSONL and the xref TSV. The exact inverse of
    /// [`Va::parse_bare`].
    pub fn bare(self) -> String {
        format!("{:08x}", self.0)
    }

    /// Parses the bare 8-char lowercase hex spelling.
    pub fn parse_bare(text: &str) -> Result<Self, AddressError> {
        let text = text.trim();
        if text.len() != 8
            || !text
                .bytes()
                .all(|b| b.is_ascii_digit() || (b'a'..=b'f').contains(&b))
        {
            return Err(AddressError::NotCanonical {
                text: text.to_owned(),
                reason: "not 8 lowercase hex digits",
            });
        }
        Ok(Self(
            u32::from_str_radix(text, 16).expect("eight validated hex digits"),
        ))
    }

    /// `va - image_base`, or [`AddressError::BelowImageBase`].
    ///
    /// The RVA is derived, never accepted silently: a consumer that wants to
    /// check the arithmetic has the image base to check it against.
    pub fn rva(self, image_base: u32) -> Result<u32, AddressError> {
        if self.0 < image_base {
            return Err(AddressError::BelowImageBase {
                va: self.0,
                image_base,
            });
        }
        Ok(self.0 - image_base)
    }
}

impl fmt::Display for Va {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.canonical())
    }
}

impl From<Va> for u32 {
    fn from(va: Va) -> u32 {
        va.0
    }
}

/// The one and only renderer of a canonical VA in this crate.
pub fn format_va(va: u32) -> String {
    format!("0x{va:08x}")
}

fn strip_prefix_fold<'a>(text: &'a str, prefix: &str) -> Option<&'a str> {
    if text.len() < prefix.len() {
        return None;
    }
    if !text[..prefix.len()].eq_ignore_ascii_case(prefix) {
        return None;
    }
    Some(&text[prefix.len()..])
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn canonical_spellings_round_trip() {
        let va = Va::parse_canonical("0x00925050").expect("canonical");
        assert_eq!(va.as_u32(), 0x0092_5050);
        assert_eq!(va.canonical(), "0x00925050");
        assert_eq!(va.bare(), "00925050");
        assert_eq!(format_va(0x00e3_a270), "0x00e3a270");
        assert_eq!(format_va(0), "0x00000000");
        assert_eq!(format_va(u32::MAX), "0xffffffff");
    }

    #[test]
    fn a_non_canonical_spelling_is_refused_with_a_reason() {
        for (text, reason) in [
            ("925050", "missing the lowercase \"0x\" prefix"),
            ("00925050", "missing the lowercase \"0x\" prefix"),
            ("0x925050", "not exactly 8 hex digits after the prefix"),
            ("0X00925050", "missing the lowercase \"0x\" prefix"),
            ("0x0092505", "not exactly 8 hex digits after the prefix"),
            ("0x009250500", "not exactly 8 hex digits after the prefix"),
            ("0x0092505Z", "not 8 lowercase hex digits"),
            ("0x00E3A270", "not 8 lowercase hex digits"),
        ] {
            let err = Va::parse_canonical(text).expect_err("must be refused");
            match err {
                AddressError::NotCanonical {
                    text: got,
                    reason: r,
                } => {
                    assert_eq!(got, text);
                    assert_eq!(r, reason, "for {text}");
                }
                other => panic!("unexpected error for {text}: {other}"),
            }
        }
    }

    #[test]
    fn bare_digits_are_hex_not_decimal() {
        // The whole reason `dec:` exists: 925050 read as decimal is
        // 0x000e1f92, a different function.
        assert_eq!(
            Va::parse_input("925050", 0x0040_0000)
                .expect("hex")
                .as_u32(),
            0x0092_5050
        );
        assert_eq!(
            Va::parse_input("dec:9588816", 0x0040_0000)
                .expect("dec")
                .as_u32(),
            0x0092_5050
        );
        assert_eq!(
            Va::parse_input("0d9588816", 0x0040_0000)
                .expect("0d")
                .as_u32(),
            0x0092_5050
        );
    }

    #[test]
    fn an_rva_is_never_silently_a_va() {
        assert_eq!(
            Va::parse_input("rva:00525050", 0x0040_0000)
                .expect("rva")
                .as_u32(),
            0x0092_5050
        );
        // Without the prefix it is a VA, which is a different address.
        assert_ne!(
            Va::parse_input("00525050", 0x0040_0000)
                .expect("va")
                .as_u32(),
            0x0092_5050
        );
    }

    #[test]
    fn an_rva_needs_the_image_base_and_refuses_underflow() {
        let va = Va::new(0x0092_5050);
        assert_eq!(va.rva(0x0040_0000).expect("rva"), 0x0052_5050);
        assert_eq!(
            va.rva(0x0092_5051),
            Err(AddressError::BelowImageBase {
                va: 0x0092_5050,
                image_base: 0x0092_5051
            })
        );
    }

    #[test]
    fn input_parsing_refuses_junk_without_panicking() {
        for text in ["", "  ", "0x", "rva:", "0x00 25050", "zz", "0x1ffffffff"] {
            assert!(
                Va::parse_input(text, 0x0040_0000).is_err(),
                "{text:?} must be refused"
            );
        }
    }
}
