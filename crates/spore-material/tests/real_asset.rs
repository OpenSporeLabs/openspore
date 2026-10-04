//! The documented asset, against real game data.
//!
//! **Ignored by default.** This test needs the git-ignored `SPORE/` tree, so it
//! is excluded from `cargo test -p spore-material` and runs only when asked for
//! on a machine that has the game installed:
//!
//! ```text
//! cargo test -p spore-material --test real_asset -- --ignored
//! ```
//!
//! The package path comes from `OPENSPORE_SPORE_DATA` when set, and otherwise
//! from the repository's own `SPORE/Data/` directory. If neither exists the test
//! still passes — by saying so — because a missing game install is not a
//! failure of this crate.
//!
//! # What it pins
//!
//! The outcome measured with `osptool` on 2026-10-04 and re-measured through
//! this crate's public API: the documented model's three texture references
//! resolve to **two** 512x512 DXT5 images and **one** typed refusal, because
//! `0x2f4e681c:0x40632902:0x067a07f0` is a 1024x1024 luminance record whose
//! envelope `fourcc` is `0x00000015`. A resolver that aborted on the first
//! failure would return nothing at all for this asset.

use spore_assets::ContentStore;
use spore_core::ResourceKey;
use spore_gmdl::GMDL_TYPE;
use spore_material::{claims, resolve_model_record, resolve_texture, MaterialError, SamplerRole};
use spore_texture::RASTER_TYPE;

/// The documented asset.
const DOCUMENTED_ASSET: &str = "0x00e6bce5:0x40637e03:0x067a07f0";

/// The instance id shared by all three of its texture references.
const INSTANCE: u32 = 0x067A_07F0;

/// The group of the reference this build refuses.
const LUMINANCE_GROUP: u32 = 0x4063_2902;

/// Where the content package lives, or `None` when it cannot be found.
fn package_path() -> Option<std::path::PathBuf> {
    if let Ok(path) = std::env::var("OPENSPORE_SPORE_DATA") {
        let path = std::path::PathBuf::from(path);
        if path.is_file() {
            return Some(path);
        }
        return None;
    }
    let path = std::path::Path::new(concat!(
        env!("CARGO_MANIFEST_DIR"),
        "/../../SPORE/Data/Spore_Content.package"
    ));
    path.is_file().then(|| path.to_owned())
}

#[test]
#[ignore = "needs the git-ignored SPORE/ tree; run with --ignored"]
fn the_documented_asset_resolves_two_images_and_one_typed_refusal() {
    let Some(path) = package_path() else {
        eprintln!(
            "skipping: set OPENSPORE_SPORE_DATA to Spore_Content.package \
             (a missing game install is not a failure of this crate)"
        );
        return;
    };
    let mut store = ContentStore::new();
    store.push(spore_assets::Package::open("Spore_Content", &path).expect("opens"));

    let key: ResourceKey = DOCUMENTED_ASSET.parse().expect("a T:G:I spec");
    assert_eq!(key.type_id, GMDL_TYPE);
    let resolved = resolve_model_record(&store, &key, RASTER_TYPE).expect("the model decodes");

    assert_eq!(
        resolved.textures.len(),
        3,
        "the record lists three references"
    );
    assert_eq!(resolved.resolved_count(), 2);

    for (index, entry) in resolved.textures.iter().enumerate().take(2) {
        let texture = entry.as_ref().unwrap_or_else(|error| {
            panic!("reference {index} of the documented asset must resolve: {error}")
        });
        assert_eq!(texture.envelope.fourcc, spore_material::REQUIRED_FOURCC);
        assert_eq!(
            (texture.image.width, texture.image.height),
            (512, 512),
            "the real records are 512x512"
        );
        assert_eq!(texture.mip_count, 10, "the real records carry ten mips");
        assert_eq!(
            texture.layer_count, 2,
            "the derived layer count is 2 on every real 512x512 record"
        );
        assert_eq!(texture.pixel_len(), 512 * 512 * 4);
    }

    // The third reference is the luminance record: a typed refusal naming the
    // fourcc, never an empty image.
    let error = resolved.textures[2].as_ref().unwrap_err();
    assert_eq!(
        error,
        &MaterialError::UnsupportedFourcc {
            key: ResourceKey::new(RASTER_TYPE, LUMINANCE_GROUP, INSTANCE),
            fourcc: 0x0000_0015,
        }
    );

    // One material, unnamed, with four non-findings and three unresolved roles.
    assert_eq!(resolved.materials.len(), 1);
    let material = &resolved.materials[0];
    assert_eq!(material.material_id, 0x407D_FDDB);
    assert_eq!(material.name, None, "no registry names this id");
    assert!(material
        .bindings
        .iter()
        .all(|binding| binding.role == SamplerRole::Unresolved));
    assert_eq!(material.unknowns().count(), 4);
    let material_name = material.claim(claims::MATERIAL_NAME).expect("subject");
    assert!(material_name.fact.is_unavailable());
    assert_eq!(
        material_name.fact.reason(),
        Some(claims::NO_MATERIAL_REGISTRY)
    );

    // And the same record read through the single-reference entry point behaves
    // identically: the type word is still a parameter.
    let texture = resolve_texture(
        &store,
        spore_gmdl::GmdlTextureRef {
            instance_id: INSTANCE,
            group_id: 0x4063_2900,
        },
        RASTER_TYPE,
    )
    .expect("the first reference resolves");
    assert_eq!(texture.image.width, 512);
    assert!(
        texture
            .claim(claims::ASSUMED_RECORD_TYPE)
            .expect("subject")
            .fact
            .is_available(),
        "the assumption is recorded, not buried"
    );
}
