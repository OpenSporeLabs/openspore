//! The big-endian `refCount` regression suite.
//!
//! # Why these tests exist at all
//!
//! `refCount` is the only big-endian word in the gmdl format; every other word
//! is little-endian. Reading it little-endian multiplies the count by
//! `0x01000000`, so a record with one referenced file asks for 16 777 216 * 12
//! bytes of file keys and the walk runs off the end of the record. In this
//! repository that bug mis-parsed 1 510 of the 4 209 gmdl records in
//! `Spore_Content.package` (`docs/CELLSTAGE-RECON.md` §2) and it was only found
//! by hand-decoding one 175 KB record.
//!
//! Nothing about a decoder's *structure* prevents it: reading the fourth word as
//! little-endian is the obvious thing to type, and it type-checks, compiles,
//! passes every test on a record with zero references, and fails only on records
//! that actually have references. So the tests below are built around the
//! property that makes the bug observable: **a little-endian read must produce a
//! count that the record cannot possibly satisfy, and this decoder must still
//! succeed.** If someone "simplifies" the read to little-endian, these fail
//! loudly on a record that the format says is valid.

mod common;

use common::{u32_at, Builder, MaterialEntry, TextureEntry};
use spore_gmdl::{parse, GmdlError};

/// A record with two referenced files.
fn two_reference_record() -> Vec<u8> {
    Builder::minimal()
        .refs(vec![
            [0xAAAA_AAAA, 0xBBBB_BBBB, 0xCCCC_CCCC],
            [0x0DDD_DDDD, 0x1234_5678, 0x00E6_BCE5],
        ])
        .build()
}

#[test]
fn the_fourth_word_is_big_endian_on_the_record() {
    let data = two_reference_record();
    // Bytes 4..8 of the record. `01 00 00 02` little-endian is 0x02000001,
    // which is 33 554 433 references; big-endian is 2.
    let word = data.get(4..8).expect("the refCount word");
    assert_eq!(word, &[0x00, 0x00, 0x00, 0x02]);
    assert_eq!(
        u32_at(&data, 4),
        Some(0x0200_0000),
        "a little-endian read of this word"
    );
    let mut be = data.clone();
    be[4..8].copy_from_slice(&2u32.to_be_bytes());
    assert_eq!(
        u32_at(&be, 4),
        Some(0x0200_0000),
        "and the same bytes read big-endian"
    );
}

#[test]
fn a_two_reference_record_parses_and_keeps_both_keys() {
    let data = two_reference_record();
    let model = parse(&data).expect("a record with two referenced files must parse");
    assert_eq!(model.referenced_files.len(), 2);
    assert_eq!(
        model.referenced_files.first().expect("first").to_tgi(),
        "0xcccccccc:0xbbbbbbbb:0xaaaaaaaa"
    );
    assert_eq!(
        model.referenced_files.get(1).expect("second").to_tgi(),
        "0x00e6bce5:0x12345678:0x0ddddddd"
    );
    // The keys were skipped, not consumed: the mesh still decodes.
    assert_eq!(model.mesh_count, 1);
    assert_eq!(model.meshes.len(), 1);
    assert!(model.fully_walked());
}

#[test]
fn a_little_endian_read_would_run_off_the_end_of_this_record() {
    // The regression proper. This record is 92 bytes; a little-endian count of
    // 0x02000000 would demand 0x180000000 bytes of file keys. A decoder that
    // reads the word little-endian therefore cannot return Ok for it, and any
    // test asserting Ok here is asserting the big-endian read.
    let data = two_reference_record();
    assert!(
        data.len() < 400,
        "the record is {} bytes; a LE walk could never fit",
        data.len()
    );
    let little_endian_count = u32_at(&data, 4).expect("word");
    let demanded = u64::from(little_endian_count) * 12;
    assert!(
        demanded > data.len() as u64,
        "LE count demands {demanded} bytes of a {} byte record",
        data.len()
    );
    // ...and this decoder, reading it big-endian, has no trouble at all.
    assert!(
        parse(&data).is_ok(),
        "the BE read is the only one that can succeed here"
    );
}

#[test]
fn the_same_record_with_a_big_endian_count_of_one_also_parses() {
    // Sanity on the other direction: a record whose refCount word happens to be
    // palindromic would parse under either endianness, so the pair of tests
    // above (count 2, distinct from 0x02000000) is what actually pins the
    // endianness rather than the count.
    let one = Builder::minimal()
        .refs(vec![[0x1111_1111, 0x2222_2222, 0x00E6_BCE5]])
        .build();
    assert_eq!(one.get(4..8), Some(&[0x00, 0x00, 0x00, 0x01u8][..]));
    let model = parse(&one).expect("one referenced file");
    assert_eq!(model.referenced_files.len(), 1);
    assert_eq!(
        u32_at(&one, 4),
        Some(0x0100_0000),
        "a LE read of the same word is 16777216"
    );
}

#[test]
fn a_zero_reference_record_is_endianness_agnostic_and_still_parses() {
    // Documented limitation of the regression: a record with no references reads
    // as 0 in either endianness, so it cannot detect the bug. That is precisely
    // why `mini.gmdl` (one reference) and these records (two) exist.
    let data = Builder::minimal().build();
    assert_eq!(u32_at(&data, 4), Some(0));
    let model = parse(&data).expect("no references");
    assert!(model.referenced_files.is_empty());
}

#[test]
fn a_le_shaped_refcount_word_is_refused_rather_than_trusted() {
    // If the bytes at offset 4 really are `01 00 00 02`, the big-endian count is
    // 0x01000002 = 16 777 218 and the record cannot hold that many keys. The
    // decoder must refuse with a truncation error rather than try to read them.
    let mut swapped = two_reference_record();
    if let Some(word) = swapped.get_mut(4..8) {
        word.copy_from_slice(&0x0200_0001u32.to_le_bytes());
    }
    let error = parse(&swapped).expect_err("16 777 218 references cannot fit");
    assert!(
        matches!(
            error,
            GmdlError::TruncatedReferencedFiles {
                count: 0x0100_0002,
                ..
            }
        ),
        "got {error:?}"
    );
    assert!(error
        .to_string()
        .contains("truncated referenced-file table"));
}

#[test]
fn a_reference_table_that_overruns_is_refused_with_the_count_named() {
    // One reference declared, but the record is cut inside the key table.
    let data = two_reference_record();
    let cut = data.get(..20).expect("prefix").to_vec();
    let error = parse(&cut).expect_err("a cut key table is not a record");
    match error {
        GmdlError::TruncatedReferencedFiles {
            count,
            needed,
            available,
        } => {
            assert_eq!(count, 2);
            assert_eq!(needed, 24);
            assert!(available < 24, "available {available}");
        }
        other => panic!("wrong error: {other:?}"),
    }
}

#[test]
fn a_reference_table_with_a_huge_declared_count_never_allocates() {
    // refCount = 0x00FFFFFF (16 777 215) big-endian, with a record that is far too
    // small. The count is checked against the remaining bytes in `u64` before any
    // loop runs, so this is a refusal, not an allocation of 200 MB.
    let mut data = two_reference_record();
    if let Some(word) = data.get_mut(4..8) {
        word.copy_from_slice(&0x00FF_FFFFu32.to_be_bytes());
    }
    let error = parse(&data).expect_err("16M references cannot fit");
    match error {
        GmdlError::TruncatedReferencedFiles { count, needed, .. } => {
            assert_eq!(count, 0x00FF_FFFF);
            assert_eq!(needed, 0x00FF_FFFFu64 * 12);
        }
        other => panic!("wrong error: {other:?}"),
    }
}

#[test]
fn the_committed_fixture_itself_carries_a_big_endian_reference_count() {
    // Finally, the fixture that every other test in this crate decodes: its
    // refCount word is `00 00 00 01`, so it too depends on the big-endian read.
    let data = common::mini_gmdl();
    assert_eq!(data.get(4..8), Some(&[0x00, 0x00, 0x00, 0x01u8][..]));
    let model = parse(&data).expect("fixture");
    assert_eq!(model.referenced_files.len(), 1);
    // A little-endian read would demand 0x01000000 * 12 = 201 326 592 bytes.
    let demanded = u64::from(u32_at(&data, 4).expect("word")) * 12;
    assert_eq!(demanded, 201_326_592);
    assert!(demanded > data.len() as u64);
}

#[test]
fn a_texture_set_and_shader_entries_coexist_in_one_material_block() {
    // Not about endianness, but it belongs beside the other
    // "a length is inferred, not trusted" tests: a `0x20D` texture set followed
    // by shader `0x210` (20 bytes) followed by shader `0x206` (256 bytes). If
    // any of those three lengths were wrong the walk would not land on the
    // record end, which is what `fully_walked` asserts.
    let mixed = Builder::minimal()
        .material_info(vec![vec![
            MaterialEntry::textures(vec![
                TextureEntry::new(0, 0x1111, 0x2222),
                TextureEntry::new(1, 0x3333, 0x4444),
            ]),
            MaterialEntry::Shader(0x210),
            MaterialEntry::Shader(0x206),
        ]])
        .build();
    let model = parse(&mixed).expect("mixed material block");
    assert_eq!(model.texture_refs.len(), 2);
    assert_eq!(
        model
            .texture_refs
            .first()
            .copied()
            .map(|t| (t.instance_id, t.group_id)),
        Some((0x1111, 0x2222))
    );
    assert!(
        model.fully_walked(),
        "the walk must land exactly on the record end"
    );
}
