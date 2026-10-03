//! Record identity: the `(type, group, instance)` triple.
//!
//! Every Spore container addresses its records this way and no other way. The
//! triple is the primary key of the canonical asset manifest, the join key of
//! the semantic passport exchange, and the lookup key of the content store.

use core::cmp::Ordering;
use core::fmt;

/// The "any"/"unset" value for a [`ResourceKey`] component.
///
/// A key holding this in *all three* components is not a record identity at
/// all; [`ResourceKey::is_complete`] reports that. The same sentinel also
/// legitimately appears in a single component of a *reference* (a world-object
/// record names "some instance of this type, any group"), which is why the
/// wildcard is a plain constant rather than a separate type.
pub const WILDCARD: u32 = 0xFFFF_FFFF;

/// A record identity inside a package: `(type, group, instance)`.
#[derive(Clone, Copy, PartialEq, Eq, Hash, Default)]
pub struct ResourceKey {
    /// Record type id (`typenames.json` maps these to names).
    pub type_id: u32,
    /// Group id — an asset-family bucket, not a folder.
    pub group_id: u32,
    /// Instance id — opaque; the same instance recurs across type/group pairs.
    pub instance_id: u32,
}

impl ResourceKey {
    /// Builds a key from its three components.
    pub const fn new(type_id: u32, group_id: u32, instance_id: u32) -> Self {
        Self {
            type_id,
            group_id,
            instance_id,
        }
    }

    /// Builds a key from a `T:G:I` triple as spelled by the asset tooling.
    ///
    /// Each component is parsed with `str::parse::<u32>()` which accepts both
    /// `0x`-prefixed hexadecimal and plain decimal, matching the Python
    /// resolvers' `int(s, 0)` behaviour.
    pub fn parse_tgi(spec: &str) -> Result<Self, ParseKeyError> {
        let mut parts = spec.split(':');
        let (Some(t), Some(g), Some(i), None) =
            (parts.next(), parts.next(), parts.next(), parts.next())
        else {
            return Err(ParseKeyError::Shape);
        };
        Ok(Self::new(
            parse_component(t)?,
            parse_component(g)?,
            parse_component(i)?,
        ))
    }

    /// A key that matches nothing; [`Self::is_complete`] is `false`.
    pub const fn wildcard() -> Self {
        Self {
            type_id: WILDCARD,
            group_id: WILDCARD,
            instance_id: WILDCARD,
        }
    }

    /// True when no component is [`WILDCARD`], i.e. this names exactly one record.
    pub const fn is_complete(&self) -> bool {
        self.type_id != WILDCARD && self.group_id != WILDCARD && self.instance_id != WILDCARD
    }

    /// True when at least one component is [`WILDCARD`].
    pub const fn is_wildcard(&self) -> bool {
        !self.is_complete()
    }

    /// The stage byte of a group id, `(group_id >> 8) & 0xff`.
    ///
    /// Spore's group ids are structured: the byte at `>> 8` selects a stage
    /// (every observed `0x40 61 62 xx` group shares `stage == 0x62`) and the
    /// byte at `>> 16` selects a category (`0x61` cell, `0x62` creature, ...).
    /// Both are documented structure, not guesses, but neither is a partition
    /// the engine relies on for correctness.
    pub const fn stage_byte(&self) -> u8 {
        ((self.group_id >> 8) & 0xff) as u8
    }

    /// The category byte of a group id, `(group_id >> 16) & 0xff`.
    pub const fn category_byte(&self) -> u8 {
        ((self.group_id >> 16) & 0xff) as u8
    }

    /// Renders the key as the canonical `T:G:I` hexadecimal spec.
    pub fn to_tgi(&self) -> String {
        format!(
            "0x{:08x}:0x{:08x}:0x{:08x}",
            self.type_id, self.group_id, self.instance_id
        )
    }
}

fn parse_component(text: &str) -> Result<u32, ParseKeyError> {
    let text = text.trim();
    if text.is_empty() {
        return Err(ParseKeyError::Component);
    }
    // `str::parse::<u32>` accepts `_` separators but **rejects** a `0x` prefix,
    // so hex has to be peeled off by hand. The Python resolvers use `int(s, 0)`,
    // which accepts `0x`; accepting it here too keeps one address spelling from
    // meaning two things across the two implementations.
    let (digits, radix) = match text.strip_prefix("0x").or_else(|| text.strip_prefix("0X")) {
        Some(rest) => (rest, 16),
        None => (text, 10),
    };
    if digits.is_empty() || !digits.chars().all(|c| c.is_ascii_hexdigit()) {
        return Err(ParseKeyError::Component);
    }
    u32::from_str_radix(digits, radix).map_err(|_| ParseKeyError::Component)
}

impl Ord for ResourceKey {
    /// Strict lexicographic order on `(type, group, instance)`.
    ///
    /// Deterministic ordering is a hard requirement, not a nicety: the asset
    /// manifest is defined to be byte-identical across runs, and that holds
    /// only because row order is a pure function of the keys.
    fn cmp(&self, other: &Self) -> Ordering {
        self.type_id
            .cmp(&other.type_id)
            .then(self.group_id.cmp(&other.group_id))
            .then(self.instance_id.cmp(&other.instance_id))
    }
}

impl PartialOrd for ResourceKey {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl fmt::Debug for ResourceKey {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "ResourceKey({})", self.to_tgi())
    }
}

impl fmt::Display for ResourceKey {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.to_tgi())
    }
}

impl core::str::FromStr for ResourceKey {
    type Err = ParseKeyError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        Self::parse_tgi(s)
    }
}

/// Why a `T:G:I` spec could not be read.
#[derive(Debug, Clone, PartialEq, Eq, thiserror::Error)]
pub enum ParseKeyError {
    /// The spec was not three colon-separated components.
    #[error("expected a `T:G:I` triple, e.g. 0x00e6bce5:0x40616201:0x067a0801")]
    Shape,
    /// One component was not a `u32` in decimal or `0x` hexadecimal.
    #[error("a type, group or instance component was not a u32 (decimal or 0x-prefixed hex)")]
    Component,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parses_hex_and_decimal_components() {
        let key = ResourceKey::parse_tgi("0x00e6bce5:0x40616201:0x067a0801").unwrap();
        assert_eq!(key, ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801));
        // Same three values as decimal (0x067a0801 == 108660737).
        let decimal = ResourceKey::parse_tgi("15121637:1080123905:108660737").unwrap();
        assert_eq!(key, decimal, "0x-hex and decimal must denote the same key");
    }

    #[test]
    fn rejects_malformed_specs() {
        assert_eq!(ResourceKey::parse_tgi("1:2"), Err(ParseKeyError::Shape));
        assert_eq!(ResourceKey::parse_tgi("1:2:3:4"), Err(ParseKeyError::Shape));
        assert_eq!(
            ResourceKey::parse_tgi("1:2:zzz"),
            Err(ParseKeyError::Component)
        );
        assert_eq!(
            ResourceKey::parse_tgi("1::3"),
            Err(ParseKeyError::Component)
        );
    }

    #[test]
    fn completeness_tracks_the_wildcard() {
        assert!(ResourceKey::new(1, 2, 3).is_complete());
        assert!(!ResourceKey::new(1, WILDCARD, 3).is_complete());
        assert!(ResourceKey::new(1, WILDCARD, 3).is_wildcard());
        assert!(!ResourceKey::wildcard().is_complete());
        assert!(ResourceKey::wildcard().is_wildcard());
    }

    #[test]
    fn group_bytes_are_extracted_as_documented() {
        // From tools/spore/types/groupnames.json: CellImages = 0x40616201.
        let key = ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0);
        assert_eq!(key.stage_byte(), 0x62);
        assert_eq!(key.category_byte(), 0x61);
    }

    #[test]
    fn ordering_is_lexicographic_on_type_group_instance() {
        let mut keys = vec![
            ResourceKey::new(2, 0, 0),
            ResourceKey::new(1, 9, 9),
            ResourceKey::new(1, 2, 3),
        ];
        keys.sort();
        assert_eq!(
            keys,
            vec![
                ResourceKey::new(1, 2, 3),
                ResourceKey::new(1, 9, 9),
                ResourceKey::new(2, 0, 0),
            ]
        );
    }

    #[test]
    fn to_tgi_round_trips_through_from_str() {
        let key = ResourceKey::new(0x00e6_bce5, 0x4061_6201, 0x067a_0801);
        assert_eq!(key.to_tgi().parse::<ResourceKey>().unwrap(), key);
    }
}
