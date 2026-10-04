//! The classification cross-check: `verify`'s per-record view against
//! `spore-assets`' type-level one.
//!
//! `verify` transcribes `spore-assets`' private `CONTAINER_TYPE_IDS` list
//! because it is not public. A transcription is a promise that it stays equal, so
//! this file proves it over every canonical type id rather than trusting the
//! copy.
//!
//! It also proves the manifest and the loader **agree** about which types are
//! decodable. They used to disagree about five of them, and every disagreement
//! was a bug in the manifest rather than an interesting fact -- see the comment
//! on `the_manifest_and_the_loader_agree_on_every_type`.

mod common;

use spore_assets::DecodeStatus;
use spore_assets::{ContentStore, ManifestBuilder, Package};
use spore_dbpf::PackageIndex;
use spore_tools::commands::verify::CONTAINER_TYPE_IDS;
use spore_tools::commands::verify::{classify, is_container_type, RecordClass};

/// A package holding one record of every canonical type id, plus every container
/// id `verify` knows, plus a couple of ids neither table has.
fn census_package() -> Vec<u8> {
    let mut ids: Vec<u32> = spore_core::record::TYPE_NAMES
        .iter()
        .map(|(id, _)| *id)
        .collect();
    ids.extend_from_slice(CONTAINER_TYPE_IDS);
    ids.push(0xdead_beef);
    ids.sort_unstable();
    ids.dedup();
    common::package_of(
        &ids.iter()
            .enumerate()
            .map(|(index, id)| common::Row::new(*id, 1, index as u32, vec![0u8; 8]))
            .collect::<Vec<_>>(),
    )
}

/// What `spore-assets`' manifest calls a type, derived the only way it can be:
/// by asking it.
fn manifest_status(image: &[u8], type_id: u32) -> spore_assets::DecodeStatus {
    let mut store = ContentStore::new();
    store.push(Package::from_vec("census", image.to_vec()).expect("a valid package"));
    let builder = ManifestBuilder::from_store(&store);
    let status = builder
        .rows()
        .find(|row| row.key.type_id == type_id)
        .unwrap_or_else(|| panic!("no row for 0x{type_id:08x}"))
        .decode_status;
    status
}

#[test]
fn the_container_transcription_is_exactly_the_manifests_container_set() {
    let image = census_package();
    for (id, _) in spore_core::record::TYPE_NAMES.iter() {
        let status = manifest_status(&image, *id);
        let mine = is_container_type(*id);
        if status == DecodeStatus::ContainerUndecoded {
            assert!(
                mine,
                "0x{id:08x} is a container for the manifest but not for verify"
            );
        } else {
            assert!(
                !mine,
                "0x{id:08x} is a container for verify but not for the manifest"
            );
        }
    }
    assert_eq!(
        CONTAINER_TYPE_IDS.len(),
        7,
        "the set is pinned by size as well"
    );
}

#[test]
fn the_container_set_is_a_set_and_holds_only_container_statuses() {
    let image = census_package();
    let mut seen = std::collections::HashSet::new();
    for id in CONTAINER_TYPE_IDS {
        assert!(seen.insert(*id), "0x{id:08x} appears twice");
        assert_eq!(
            manifest_status(&image, *id),
            DecodeStatus::ContainerUndecoded,
            "0x{id:08x} is not a container for the manifest"
        );
    }
}

/// The divergences, in **both** directions.
/// The manifest's classification answers "does this build have a per-record
/// decoder for this type". `verify`'s answers "did this record decode".
///
/// # These used to disagree, and the disagreement was a bug
///
/// An earlier revision of `spore_assets::classify_decode_status` read `Ok` as
/// "a decoder *family* exists", which produced five contradictions:
///
/// * `png` (`0x2F7D0004`) and `jpeg` (`0x2F7D0002`) were listed as decodable
///   **and described as RW4 containers**. Measured across every installed
///   package they are raw PNG/JPEG: 10 487 of 10 487 carry the PNG magic, and
///   none carry `RW4w32`. They are a different type id from `rw4`
///   (`0x2F4E681B`) and mean something else entirely.
/// * `rw4` (`0x2F4E681B`) was *absent* from the manifest's list while
///   `spore-rw4` decoded all 1131 real records and `ModelStore::load` accepted
///   the type -- so the manifest labelled every RW4 record `undecoded`.
/// * `gmsh` (`0x01C135DA`), a RenderWare mesh *section* rather than a gmdl,
///   was listed as decodable; routing it to `spore-gmdl` would refuse it.
/// * `plt` (`0x011989B7`) was listed as decodable; no palette decoder exists.
///
/// `Ok` now means exactly "a per-record decoder exists in this workspace", the
/// list is exactly `{gmdl, raster, rw4}`, and it agrees with the loader by
/// construction. The tests below assert the divergence set is **empty** -- an
/// assertion that fails the moment somebody widens the list again.
#[test]
fn the_manifest_and_the_loader_agree_on_every_type() {
    let image = census_package();
    let mut disagreements: Vec<(u32, &'static str, DecodeStatus, RecordClass)> = Vec::new();
    for (id, name) in spore_core::record::TYPE_NAMES.iter() {
        let manifest = manifest_status(&image, *id);
        let mine = classify(*id);
        let agree = matches!(
            (manifest, mine),
            (DecodeStatus::ContainerUndecoded, RecordClass::Container)
                | (DecodeStatus::Undecoded, RecordClass::NoDecoder)
                | (
                    DecodeStatus::Ok,
                    RecordClass::Gmdl | RecordClass::Rw4 | RecordClass::Raster
                )
        );
        if !agree {
            disagreements.push((*id, name, manifest, mine));
        }
    }
    assert!(
        disagreements.is_empty(),
        "manifest and loader disagree about which types are decodable: {disagreements:?}"
    );
}

/// The four ids that were wrong, pinned individually so a regression names which
/// one moved back.
#[test]
fn the_four_previously_wrong_ids_are_now_classified_honestly() {
    let image = census_package();
    for (id, name, expected) in [
        (
            spore_core::record::type_id::PNG,
            "png",
            "raw PNG, nothing decodes it",
        ),
        (
            spore_core::record::type_id::JPEG,
            "jpeg",
            "raw JPEG, nothing decodes it",
        ),
        (
            0x01C1_35DAu32,
            "gmsh",
            "a RenderWare mesh section, not a gmdl",
        ),
        (
            spore_core::record::type_id::PLT,
            "plt",
            "no palette decoder exists",
        ),
    ] {
        assert_eq!(
            manifest_status(&image, id),
            DecodeStatus::Undecoded,
            "{name}: {expected}"
        );
        assert_eq!(classify(id), RecordClass::NoDecoder, "{name}: {expected}");
    }
    // And the one that was missing is present.
    assert_eq!(
        manifest_status(&image, spore_rw4::RW4_TYPE),
        DecodeStatus::Ok
    );
    assert_eq!(classify(spore_rw4::RW4_TYPE), RecordClass::Rw4);
    assert!(spore_rw4::parse(&common::read_fixture("mini_rw4.rw4")).is_ok());
}

#[test]
fn an_unknown_id_is_undecoded_in_both_views() {
    let image = census_package();
    assert_eq!(
        manifest_status(&image, 0xdead_beef),
        DecodeStatus::Undecoded
    );
    assert_eq!(classify(0xdead_beef), RecordClass::NoDecoder);
}

#[test]
fn the_package_index_agrees_with_the_classifier_about_every_row() {
    // A last, independent angle: the index is what the walk iterates, so its
    // rows must classify the same way the census says they do.
    let image = census_package();
    let index = PackageIndex::parse(&image).expect("the census package parses");
    assert_eq!(index.len(), {
        let mut ids: Vec<u32> = spore_core::record::TYPE_NAMES
            .iter()
            .map(|(id, _)| *id)
            .collect();
        ids.extend_from_slice(CONTAINER_TYPE_IDS);
        ids.push(0xdead_beef);
        ids.sort_unstable();
        ids.dedup();
        ids.len()
    });
    for entry in index.entries() {
        assert_eq!(
            is_container_type(entry.type_id),
            classify(entry.type_id) == RecordClass::Container,
            "0x{:08x}",
            entry.type_id
        );
    }
}
