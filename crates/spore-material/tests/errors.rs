//! Typed failures: a missing record names its key, a refused fourcc names its
//! word, and every variant has an asserted message.

mod support;

use spore_assets::AssetError;
use spore_core::ResourceKey;
use spore_gmdl::{GmdlError, GmdlTextureRef};
use spore_material::{
    claims, inspect_envelope, resolve_model_record, resolve_texture, MaterialError,
};
use spore_texture::{TextureError, DXT5_FOURCC, RASTER_TYPE};
use support::*;

/// The reference the documented asset's first texture uses.
fn first_reference() -> GmdlTextureRef {
    documented_texture_refs()[0]
}

#[test]
fn a_missing_record_yields_a_typed_error_naming_the_key() {
    // A store with one record, asked for a different instance.
    let store = store_over(&[(
        raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        two_layer_raster(),
    )]);
    let absent = GmdlTextureRef {
        instance_id: 0x067A_07FF,
        group_id: 0x4063_2900,
    };
    let error = resolve_texture(&store, absent, RASTER_TYPE).unwrap_err();

    let MaterialError::Lookup { key, source } = &error else {
        panic!("expected Lookup, got {error:?}");
    };
    assert_eq!(
        *key,
        ResourceKey::new(RASTER_TYPE, 0x4063_2900, 0x067A_07FF)
    );
    let AssetError::NotFound {
        key: reported,
        searched,
        candidates,
    } = source
    else {
        panic!("expected NotFound, got {source:?}");
    };
    assert_eq!(*reported, *key, "the store and this crate report one key");
    assert_eq!(*searched, 1);
    assert_eq!(
        candidates,
        &vec![raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID)],
        "the near-miss record is suggested, so the miss is diagnosable"
    );
    assert_eq!(
        error.key(),
        Some(ResourceKey::new(RASTER_TYPE, 0x4063_2900, 0x067A_07FF))
    );

    // The message names the key in full and the type word that was assumed.
    let text = error.to_string();
    assert!(text.contains("0x2f4e681c:0x40632900:0x067a07ff"), "{text}");
    // The underlying store error is preserved in the source chain rather than
    // flattened into prose, so a caller can match on `AssetError::NotFound`
    // itself and read the near-miss list off it (the Display carries the key and
    // the package count, not the candidates).
    let source = std::error::Error::source(&error).expect("the store error is the source");
    assert_eq!(
        source.to_string(),
        AssetError::NotFound {
            key: ResourceKey::new(RASTER_TYPE, 0x4063_2900, 0x067A_07FF),
            searched: 1,
            candidates: vec![raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID)],
        }
        .to_string()
    );
}

#[test]
fn an_empty_store_says_so_rather_than_reporting_a_missing_record() {
    let store = spore_assets::ContentStore::new();
    let error = resolve_texture(&store, first_reference(), RASTER_TYPE).unwrap_err();
    assert_eq!(
        error,
        MaterialError::Lookup {
            key: raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
            source: AssetError::EmptyStore,
        }
    );
    assert!(error.to_string().contains("no packages"), "{}", error);
}

#[test]
fn a_luminance_fourcc_yields_a_typed_error_naming_the_fourcc_not_an_empty_image() {
    let store = store_over(&[(
        raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        luminance_raster(16, 16),
    )]);
    let error = resolve_texture(&store, first_reference(), RASTER_TYPE).unwrap_err();

    assert_eq!(
        error,
        MaterialError::UnsupportedFourcc {
            key: raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
            fourcc: LUMINANCE_FOURCC,
        },
        "the refusal is a distinct variant, not a decode failure and not a blank image"
    );
    assert!(error.is_unsupported_format());
    assert!(!matches!(error, MaterialError::Decode { .. }));

    let text = error.to_string();
    assert!(
        text.contains("0x00000015"),
        "the fourcc must be named: {text}"
    );
    assert!(
        text.contains("luminance"),
        "the family must be named: {text}"
    );
    assert!(text.contains("0x35545844"), "the wanted fourcc: {text}");

    // The refusal is flattened on purpose: this variant carries the fourcc
    // itself rather than wrapping spore-texture's error, because the whole point
    // of the split is that a caller can match "not our format" without also
    // matching on a downstream error type. Asserted, not assumed.
    assert!(
        std::error::Error::source(&error).is_none(),
        "UnsupportedFourcc is self-contained, so its message must carry every fact"
    );

    // And no empty image was produced instead: a refusal returns nothing at all,
    // so an `Err` can never be mistaken for "a zero-byte texture". Note that
    // `inspect_envelope` still succeeds here, because reading a 32-byte header
    // is not decoding a format -- and the two entry points therefore cannot be
    // confused for one another.
    assert!(
        resolve_texture(&store, first_reference(), RASTER_TYPE).is_err(),
        "decoding the luminance record is refused"
    );
    let header = inspect_envelope(&store, first_reference(), RASTER_TYPE).expect("a header reads");
    assert!(!header.pixels_decoded());
}

#[test]
fn every_other_texture_refusal_arrives_as_a_decode_error_with_its_own_reason() {
    let key = raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID);
    let store = store_over(&[(key, two_layer_raster())]);

    // A truncated record: the envelope does not fit.
    let truncated = store_over(&[(key, vec![0u8; 8])]);
    let error = resolve_texture(&truncated, first_reference(), RASTER_TYPE).unwrap_err();
    assert_eq!(
        error,
        MaterialError::Decode {
            key,
            source: TextureError::TruncatedEnvelope { available: 8 },
        }
    );
    assert!(error.to_string().contains("32-byte raster envelope"));

    // A payload that does not divide by the layer stride.
    let mut misaligned = two_layer_raster();
    misaligned.push(0);
    let misaligned_store = store_over(&[(key, misaligned)]);
    let error = resolve_texture(&misaligned_store, first_reference(), RASTER_TYPE).unwrap_err();
    assert!(matches!(
        error,
        MaterialError::Decode {
            source: TextureError::PayloadNotMultiple { .. },
            ..
        }
    ));
    assert!(error.to_string().contains("layer stride"));

    // A zero dimension is refused rather than turned into an empty image.
    let zero = store_over(&[(key, raster_record(0, 8, 2, DXT5_FOURCC, 1))]);
    let error = resolve_texture(&zero, first_reference(), RASTER_TYPE).unwrap_err();
    assert!(matches!(
        error,
        MaterialError::Decode {
            source: TextureError::ZeroDimension { .. },
            ..
        }
    ));

    // ...and the happy path still works in the same store, so these refusals are
    // about the records and not about the fixture.
    assert!(resolve_texture(&store, first_reference(), RASTER_TYPE).is_ok());
}

#[test]
fn a_truncated_record_is_refused_by_the_cheap_entry_point_too() {
    let key = raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID);
    for bytes in [vec![], vec![0u8; 1], vec![0xFF; 31]] {
        let store = store_over(&[(key, bytes.clone())]);
        let error = inspect_envelope(&store, first_reference(), RASTER_TYPE).unwrap_err();
        assert_eq!(
            error,
            MaterialError::Decode {
                key,
                source: TextureError::TruncatedEnvelope {
                    available: bytes.len()
                },
            }
        );
    }
}

#[test]
fn every_error_variant_has_an_asserted_message() {
    let key = raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID);
    let cases: Vec<(MaterialError, &str)> = vec![
        (
            MaterialError::Lookup {
                key,
                source: AssetError::NotFound {
                    key,
                    searched: 3,
                    candidates: Vec::new(),
                },
            },
            "no record",
        ),
        (
            MaterialError::AssumedTypeNotDecodable {
                key,
                assumed_type: PNG_TYPE,
                name: String::from("png"),
            },
            "png",
        ),
        (
            MaterialError::UnsupportedFourcc {
                key,
                fourcc: LUMINANCE_FOURCC,
            },
            "0x00000015",
        ),
        (
            MaterialError::Decode {
                key,
                source: TextureError::ZeroMipCount,
            },
            "mipCount is 0",
        ),
        (
            MaterialError::ModelDecode {
                key,
                source: GmdlError::UndocumentedShaderDataId { id: 0x218 },
            },
            "0x218",
        ),
        (
            MaterialError::IncompleteReference {
                reference: GmdlTextureRef {
                    instance_id: spore_core::WILDCARD,
                    group_id: 0x4063_2900,
                },
                component: "instance",
            },
            "0xFFFFFFFF",
        ),
        (MaterialError::EmptyImage { key }, "no base image"),
    ];

    for (error, needle) in &cases {
        let text = error.to_string();
        assert!(
            text.contains(needle),
            "message {text:?} does not mention {needle:?}"
        );
    }
    // 7 variants are constructed above; the enum must not grow without this test
    // being extended, because an unmentioned variant has an unasserted message.
    assert_eq!(
        cases.len(),
        7,
        "a new MaterialError variant needs a message case here"
    );
}

#[test]
fn the_defensive_empty_image_variant_is_constructed_directly() {
    // Unreachable through the decoders below it, which is exactly why it needs a
    // direct construction: an arm nothing can reach has no other coverage.
    let key = raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID);
    let error = MaterialError::EmptyImage { key };
    assert_eq!(error.key(), Some(key));
    assert!(error
        .to_string()
        .contains("0x2f4e681c:0x40632900:0x067a07f0"));
    assert!(!error.is_unsupported_format());
    assert!(
        std::error::Error::source(&error).is_none(),
        "there is no underlying error to point at"
    );
}

#[test]
fn a_wildcard_reference_message_names_which_component_was_wild() {
    let store = store_over(&[(
        raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        two_layer_raster(),
    )]);
    let wildcard_instance = GmdlTextureRef {
        instance_id: spore_core::WILDCARD,
        group_id: 0x4063_2900,
    };
    let error = resolve_texture(&store, wildcard_instance, RASTER_TYPE).unwrap_err();
    let text = error.to_string();
    assert!(text.contains("instance"), "{text}");
    assert!(text.contains("0x40632900"), "{text}");

    let wildcard_group = GmdlTextureRef {
        instance_id: DOCUMENTED_INSTANCE_ID,
        group_id: spore_core::WILDCARD,
    };
    let error = resolve_texture(&store, wildcard_group, RASTER_TYPE).unwrap_err();
    let text = error.to_string();
    assert!(text.contains("group"), "{text}");
    assert!(text.contains("0x067a07f0"), "{text}");
}

#[test]
fn the_claims_table_and_the_error_variants_agree_on_the_luminance_wording() {
    // One vocabulary for one fact: the claim subject, the reason code and the
    // error message all describe the same refusal.
    let spec = claims::spec_of(claims::LUMINANCE_FOURCC_FAMILY).expect("subject");
    assert!(spec.kind.reason().is_some());
    let error = MaterialError::UnsupportedFourcc {
        key: raster_key(0x4063_2900, DOCUMENTED_INSTANCE_ID),
        fourcc: LUMINANCE_FOURCC,
    };
    let text = error.to_string();
    assert!(text.contains("luminance"));
    assert!(text.contains(&format!("0x{:08x}", DXT5_FOURCC)));
}

#[test]
fn a_model_record_error_names_the_model_key_and_the_gmdl_reason() {
    let store = store_over(&[(documented_model_key(), undocumented_shader_gmdl())]);
    let error = resolve_model_record(&store, &documented_model_key(), RASTER_TYPE).unwrap_err();
    assert_eq!(error.key(), Some(documented_model_key()));
    let text = error.to_string();
    assert!(text.contains("0x00e6bce5:0x40637e03:0x067a07f0"), "{text}");
    assert!(text.contains("gmdl:"), "{text}");
    assert!(text.contains("undocumented shader-data id 0x218"), "{text}");
}

#[test]
fn a_missing_model_record_is_a_lookup_not_a_decode_failure() {
    let store = store_over(&[(documented_model_key(), documented_gmdl())]);
    let absent = ResourceKey::new(spore_gmdl::GMDL_TYPE, 0x4063_7E03, 0x067A_07FF);
    let error = resolve_model_record(&store, &absent, RASTER_TYPE).unwrap_err();
    let MaterialError::Lookup { key, source } = &error else {
        panic!("expected Lookup, got {error:?}");
    };
    assert_eq!(*key, absent);
    let AssetError::NotFound {
        key: reported,
        candidates,
        ..
    } = source
    else {
        panic!("expected NotFound, got {source:?}");
    };
    assert_eq!(*reported, absent);
    assert_eq!(candidates, &vec![documented_model_key()]);
}
