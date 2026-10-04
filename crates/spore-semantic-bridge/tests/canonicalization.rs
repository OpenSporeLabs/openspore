//! The three known interior addresses, against the committed snapshot.
//!
//! These three are the ground truth. They are recorded in
//! `docs/tooling/semantic-exchange.md` §3.1 and again in the snapshot's own
//! `identity.requested` / `identity_resolution` blocks, so this file checks two
//! independent things at once:
//!
//! 1. that this crate's *computed* canonicalization agrees with the
//!    repository's stated answer, rule and offset; and
//! 2. that it agrees with the *exporters own recorded correction* for the same
//!    addresses, which was made by a different tool from different inputs.
//!
//! And one address that must resolve to nothing at all.

mod support;

use spore_semantic_bridge::{Canonicalization, Snapshot};

/// The three interior resolutions the repository records.
const KNOWN: [(u32, u32, u32); 3] = [
    // (interior address, containing entry, offset)
    (0x00e3_a400, 0x00e3_a270, 400),
    (0x00e7_b6c0, 0x00e7_b630, 144),
    (0x00e7_d2c0, 0x00e7_d070, 592),
];

/// `0x00925050` lies between `FUN_00925000` (ending `0x0092504a`) and
/// `FUN_009250c0`, and `spore-recomp` reached it through a real vtable indirect
/// call. It resolves to nothing, and that is the answer.
const PADDING_VA: u32 = 0x0092_5050;

fn snapshot() -> Option<&'static Snapshot> {
    static ONCE: std::sync::OnceLock<Option<Snapshot>> = std::sync::OnceLock::new();
    let path = support::committed_path()?;
    static PATH: std::sync::OnceLock<std::path::PathBuf> = std::sync::OnceLock::new();
    let _ = PATH.set(path);
    ONCE.get_or_init(|| {
        let path = PATH.get().expect("path was just set");
        Some(
            Snapshot::open(path)
                .unwrap_or_else(|error| panic!("the committed snapshot must open: {error}")),
        )
    })
    .as_ref()
}

/// Skips loudly when the artifact is absent: it is optional by contract, and a
/// test that silently passed without reading anything would be worse than one
/// that reports it did not run.
macro_rules! snapshot_or_skip {
    () => {
        match snapshot() {
            Some(snapshot) => snapshot,
            None => {
                eprintln!(
                    "SKIPPED: knowledge/semantic/function-passport-v1.jsonl is not present; the \
                     artifact is optional and these cases cannot run without it"
                );
                return;
            }
        }
    };
}

#[test]
fn the_three_known_interior_addresses_resolve_to_their_containing_entry() {
    let snapshot = snapshot_or_skip!();
    for (interior, entry, offset) in KNOWN {
        let resolution = snapshot.resolve(interior);
        assert_eq!(
            resolution.rule,
            Canonicalization::ContainingFunctionEntry,
            "0x{interior:08x}"
        );
        assert_eq!(
            resolution.canonical,
            Some(entry),
            "0x{interior:08x} must resolve to 0x{entry:08x}"
        );
        assert_eq!(resolution.offset, Some(offset), "0x{interior:08x}");
        assert_eq!(resolution.requested, interior);
        assert!(resolution.is_resolved());
        assert_eq!(resolution.end, Some(entry + size_of(snapshot, entry)));
    }
}

#[test]
fn the_computed_resolution_agrees_with_the_exporters_own_recorded_correction() {
    // The exporter recorded these three corrections from a different tool and a
    // different input set. Agreement is therefore evidence, not a tautology.
    let snapshot = snapshot_or_skip!();
    for (interior, entry, offset) in KNOWN {
        let computed = snapshot.resolve(interior);
        let passport = snapshot
            .lookup(entry)
            .unwrap_or_else(|error| panic!("0x{entry:08x} must be indexed: {error}"));
        let recorded = passport
            .recorded_identity_resolution()
            .unwrap_or_else(|| panic!("0x{entry:08x} records no identity resolution"));
        assert_eq!(recorded.rule, "containing_function_entry", "0x{entry:08x}");
        assert_eq!(recorded.canonical_va, entry);
        assert_eq!(
            recorded.requested,
            vec![(interior, offset)],
            "0x{entry:08x} moved exactly one address"
        );
        assert_eq!(
            (computed.canonical, computed.offset),
            (Some(recorded.canonical_va), Some(offset)),
            "the computed resolution and the recorded one must agree for 0x{interior:08x}"
        );
        assert_eq!(
            Canonicalization::parse(&recorded.rule),
            Some(computed.rule),
            "the rule names must be the same vocabulary"
        );
    }
}

#[test]
fn an_entry_resolves_to_itself_with_offset_zero() {
    let snapshot = snapshot_or_skip!();
    for (_, entry, _) in KNOWN {
        let resolution = snapshot.resolve(entry);
        assert_eq!(resolution.rule, Canonicalization::FunctionEntry);
        assert_eq!(resolution.canonical, Some(entry));
        assert_eq!(resolution.offset, Some(0));
        assert_eq!(resolution.end, None);
    }
}

#[test]
fn padding_between_two_bodies_resolves_to_nothing_and_is_not_repaired() {
    let snapshot = snapshot_or_skip!();
    let resolution = snapshot.resolve(PADDING_VA);
    assert_eq!(
        resolution.rule,
        Canonicalization::NonFunctionEntity,
        "0x00925050 lies between FUN_00925000 (ending 0x0092504a) and FUN_009250c0"
    );
    assert_eq!(resolution.canonical, None);
    assert_eq!(resolution.offset, None);
    assert_eq!(resolution.end, None);
    assert!(!resolution.is_resolved());
    assert_eq!(resolution.canonical_text(), None);

    // Both neighbours are real entries; the gap between them is not in either.
    assert!(snapshot.contains_entry(0x0092_5000));
    assert!(snapshot.contains_entry(0x0092_50c0));
    assert!(!snapshot.contains_entry(PADDING_VA));

    // And the reader can show *why*: the bisect landed on the first neighbour,
    // whose body stops 6 bytes short of the address.
    let (candidate, size) = snapshot
        .preceding_entry(PADDING_VA)
        .expect("there is a preceding entry");
    assert_eq!(candidate, 0x0092_5000);
    assert_eq!(
        u64::from(candidate) + u64::from(size),
        u64::from(PADDING_VA) - 6,
        "0x0092504a + 1 == 0x0092504b, so 0x00925050 is 5 bytes past the body"
    );
}

#[test]
fn a_padding_address_is_never_mapped_even_though_a_passport_exists_for_its_neighbour() {
    let snapshot = snapshot_or_skip!();
    // `lookup` refuses the padding address outright rather than quietly handing
    // back the nearest entry: the difference between "not here" and "here" is
    // the whole point.
    match snapshot.lookup(PADDING_VA) {
        Err(error) => {
            let text = error.to_string();
            assert!(text.contains("0x00925050"), "{text}");
            assert!(
                text.contains("not inside any known function body"),
                "{text}"
            );
        }
        Ok(passport) => panic!(
            "0x00925050 must not resolve, but it produced {}",
            passport.canonical_va_text()
        ),
    }
}

#[test]
fn an_address_below_the_first_entry_resolves_to_nothing() {
    let snapshot = snapshot_or_skip!();
    let below = snapshot.image_base();
    assert_eq!(
        snapshot.resolve(below).rule,
        Canonicalization::NonFunctionEntity
    );
    assert_eq!(
        snapshot.resolve(0).rule,
        Canonicalization::NonFunctionEntity
    );
    assert_eq!(snapshot.preceding_entry(below), None);
}

#[test]
fn the_last_byte_of_a_body_is_inside_it_and_the_byte_after_is_not() {
    // The exact `start <= a < start + size` test, both sides of the boundary.
    let snapshot = snapshot_or_skip!();
    let (_, entry, _) = KNOWN[0];
    let size = size_of(snapshot, entry);
    let last = entry + size - 1;
    assert_eq!(
        snapshot.resolve(last).rule,
        Canonicalization::ContainingFunctionEntry
    );
    assert_eq!(snapshot.resolve(last).offset, Some(size - 1));
    // The next entry may start exactly there, in which case it is an entry; if
    // not, it is padding. Either way it is never the *previous* function's body.
    let after = entry + size;
    let resolved = snapshot.resolve(after);
    assert_ne!(
        resolved.canonical,
        Some(entry),
        "the exclusive end of a body is not inside it"
    );
}

#[test]
fn an_address_at_the_exclusive_end_of_the_final_body_is_not_claimed_by_it() {
    let snapshot = snapshot_or_skip!();
    // The universe's highest entry, and one byte past it.
    let last = snapshot
        .passports()
        .map(|passport| passport.expect("valid").canonical_va())
        .last()
        .expect("the snapshot holds entries");
    let size = size_of(snapshot, last);
    let past_the_end = last + size;
    let resolution = snapshot.resolve(past_the_end);
    assert_ne!(resolution.canonical, Some(last));
}

fn size_of(snapshot: &Snapshot, entry: u32) -> u32 {
    snapshot
        .lookup(entry)
        .unwrap_or_else(|error| panic!("0x{entry:08x} must be indexed: {error}"))
        .size()
        .unwrap_or_else(|| panic!("0x{entry:08x} states no size"))
}
