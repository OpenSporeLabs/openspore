//! # spore-material — what a gmdl material id means, and a texture you can sample
//!
//! The vertical slice decodes a `gmdl` record and renders its mesh, but a gmdl
//! record's material section is a list of opaque ids and a list of
//! `{instance, group}` pairs. Nothing turns those into something a renderer can
//! sample. This crate is that step, and it is deliberately the narrowest crate
//! in the workspace: no Bevy, no GPU handle, no image crate, no I/O of its own,
//! and no invented names.
//!
//! ```text
//!   spore-dbpf ┐
//!   spore-gmdl ┼─> spore-material ─> RGBA8 + graded claims ─> spore-engine
//!   spore-texture┤        ▲
//!   spore-assets ┘        └── the (type, group, instance) the lookup used
//! ```
//!
//! # The gap, stated precisely
//!
//! A gmdl record's material info gives two lists and they are both opaque:
//!
//! 1. **`material_ids`** — one 32-bit id per mesh (`0x407DFDDB` on the
//!    documented asset). **What a material id names is not known.** The C++
//!    reference, `src/assets/MaterialRegistry.cpp`, keeps a registry the engine
//!    populates from outside: the reference implementation never learned the
//!    mapping either, which is the strongest evidence available that it is not
//!    in the record.
//! 2. **`texture_refs`** — `{instance_id, group_id}` pairs. **No type word.** A
//!    reference does not even say it is a raster, so the type must be assumed
//!    and the assumption has to be visible.
//!
//! # The API, in one place
//!
//! ```text
//! resolve_texture(store, reference, assumed_type) -> Result<ResolvedTexture, MaterialError>
//! resolve_model_textures(store, &model, assumed_type) -> Vec<Result<ResolvedTexture, ..>>
//! resolve_model_record(store, &key, assumed_type)   -> Result<ModelTextures, MaterialError>
//! inspect_envelope(store, reference, assumed_type)   -> Result<ResolvedTexture, ..>
//! model_materials(&model)                            -> Vec<MaterialModel>
//! ```
//!
//! `assumed_type` is a parameter of **every** entry point, never a default and
//! never a constant buried in the body: it is the thing the gmdl reference does
//! not carry, and a caller who guesses wrong must be able to see that they did.
//!
//! `inspect_envelope` is the cheap question — "how big is this record?" — asked
//! of an atlas that may hold thousands of them. It reads a 32-byte header and
//! stops, which is why its [`ResolvedTexture::pixels_decoded`] is `false`: an
//! empty image that is *marked* as never decoded cannot be confused with a
//! decode that produced nothing, and a refusal never returns an image at all.
//!
//! # The five things this crate will not do
//!
//! Each of these is enforced by a type or a test, not by a comment:
//!
//! | It will not | Because | Enforced by |
//! | --- | --- | --- |
//! | invent a material name from its id | the registry is external to the data | [`MaterialModel::name`] is `None`; `material_name` returns `None` for every id |
//! | call a texture "diffuse" or "normal" | the 16 skipped bytes per texture-set entry are not decoded | [`SamplerRole`] has one variant, [`SamplerRole::Unresolved`] |
//! | bury the type assumption | the reference carries no type word | `assumed_type` is a parameter of every entry point, and [`claims::ASSUMED_RECORD_TYPE`] records it at `INFERRED` |
//! | return an empty image instead of an error | an absent texel and a black texel must not look alike | [`decode_raster`](spore_texture::decode_raster) refusals arrive as typed [`MaterialError`] variants |
//! | decode a `png` or `rw4` record as a raster | they are different containers | [`MaterialError::AssumedTypeNotDecodable`], checked by type id |
//!
//! # `png` and `rw4` are not rasters, and this is measured
//!
//! Verified on `SPORE/Data/Spore_Content.package` with `osptool` (2026-10-04):
//!
//! * a `png`-typed record (`0x2F7D0004`) begins `89 50 4E 47 0D 0A 1A 0A` and
//!   continues straight into an `IHDR` chunk — **raw PNG**;
//! * an `rw4`-typed record (`0x2F4E681B`) begins `52 57 34 77 33 32 00` —
//!   `"RW4w32"`, a **RenderWare** container;
//! * a `raster`-typed record (`0x2F4E681C`) begins the 32-byte envelope, with
//!   `fourcc` `0x35545844` (`DXT5`) or `0x00000015` for the luminance family.
//!
//! Two comments elsewhere in this workspace state that a `png`-named record is
//! "an RW4 blob, **not** raw PNG" (`spore-core`'s `type_id::RW4` doc comment,
//! and `spore-assets`' manifest `DECODABLE` list). The bytes above contradict
//! both. This crate follows the bytes and treats the type word as identity, which
//! is why a `png` assumption is a typed refusal rather than a decode attempt.
//!
//! # The group-name gap
//!
//! The documented asset `0x00e6bce5:0x40637e03:0x067a07f0` references three
//! textures, all with `instance_id = 0x067a07f0` and groups `0x40632900`,
//! `0x40632901`, `0x40632902`. None of those three group ids is in
//! [`spore_core::record::GROUP_NAMES`], so [`claims::RESOLVED_GROUP_NAME`] is a
//! **non-finding** for all three. This crate does not add them: "the group with
//! the lowest index is the colour map" is a guess about a shader nobody here has
//! read, and the canonical table is transcribed from the SDK plus a per-package
//! prop directory, so an entry added without a source would be a fabrication
//! presented as a name.
//!
//! # What the documented asset actually does
//!
//! `osptool describe` on 2026-10-04, which this crate's tests mirror
//! synthetically:
//!
//! | Reference | Result |
//! | --- | --- |
//! | `0x2f4e681c:0x40632900:0x067a07f0` | 512x512, 10 mips, 2 layers, `DXT5` |
//! | `0x2f4e681c:0x40632901:0x067a07f0` | 512x512, 10 mips, 2 layers, `DXT5` |
//! | `0x2f4e681c:0x40632902:0x067a07f0` | 1024x1024 luminance, `fourcc 0x00000015` — **refused** |
//!
//! So [`resolve_model_textures`] on the documented asset yields two images and
//! one typed error, in that order. A resolver that aborted on the first failure
//! would return nothing at all for the one asset this repository documents end to
//! end — which is why the batch returns a `Vec<Result<..>>`.
//!
//! # Testing
//!
//! **No committed raster fixture exists** (the real records live in the
//! git-ignored `SPORE/` tree), so every byte is synthesized: `tests/support/`
//! builds a DBPF v3 image, raster records with a 32-byte envelope and DXT5
//! payloads, and gmdl records whose material section mirrors the documented
//! asset's. Nothing here needs a game installation, a package or a network.
//!
//! # Clean-room
//!
//! Nothing in this crate is derived from EA or Maxis code. The layouts were read
//! out of record bytes, out of the community SDK's type information and out of
//! this repository's own references (`src/assets/MaterialRegistry.cpp`,
//! `docs/MATERIALS-DESIGN.md`, `tools/spore/`).

#![forbid(unsafe_code)]
#![warn(missing_docs, missing_debug_implementations)]

pub mod claims;

mod error;
mod material;
mod resolve;

pub use claims::{grade_of, spec_of, ClaimKind, ClaimSpec, ALL_CLAIMS};
pub use error::MaterialError;
pub use material::{
    material_name, model_materials, BindingScope, MaterialClaim, MaterialModel, SamplerRole,
    TextureBinding,
};
pub use resolve::{
    inspect_envelope, resolve_model_record, resolve_model_textures, resolve_texture, ModelTextures,
    ResolvedTexture, TextureClaim, TextureKind, REQUIRED_FOURCC,
};
