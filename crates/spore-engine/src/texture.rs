//! Bridging resolved Spore textures into Bevy GPU images.
//!
//! `spore-material` produces an 8-bit RGBA image. Bevy wants an
//! [`Image`] in a GPU texture format. This module is the whole of that gap, and
//! it is small on purpose: one function, one decision, one test.
//!
//! # The one decision: sRGB or linear
//!
//! DXT5 in Spore carries **unpremultiplied, non-linear** colour bytes, so the
//! image is uploaded as `Rgba8UnormSrgb` and the sampler is linear. Getting
//! that backwards is the classic texture bug -- too dark, too contrasty, and
//! only in the lighting, so it reads as "wrong lighting" rather than "wrong
//! texture".
//!
//! Alpha is *not* premultiplied, and `spore-texture`'s DXT5 decoder
//! deliberately reproduces an oracle whose alpha channel is often a mask rather
//! than coverage. See `spore_texture::claims` and the `dxt5_spec_deviations`
//! entry: the alpha interpretation is **VERIFIED against the oracle and not
//! understood**. This module therefore does not assume coverage semantics; it
//! carries the bytes and lets the material decide.

use bevy::asset::RenderAssetUsages;
use bevy::image::{Image, ImageSampler};
use bevy::prelude::*;
use bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};

use spore_material::ResolvedTexture;

/// Uploads a resolved Spore texture into `images` and returns its handle.
///
/// The handle is only meaningful once the image is in the collection, so this
/// takes `&mut Assets<Image>` rather than returning a handle into thin air: a
/// `Handle` whose image was never added renders as the default white texture,
/// which looks like a material bug.
pub fn to_bevy_image(texture: &ResolvedTexture, images: &mut Assets<Image>) -> Handle<Image> {
    let mip = &texture.image;
    let mut image = Image::new_fill(
        Extent3d {
            width: mip.width.max(1),
            height: mip.height.max(1),
            depth_or_array_layers: 1,
        },
        TextureDimension::D2,
        &mip.pixels,
        TextureFormat::Rgba8UnormSrgb,
        RenderAssetUsages::default(),
    );
    // Linear filtering. Spore's rasters carry a mip chain, but only the base
    // level is uploaded here, so mipmap selection is off by construction and
    // asking for it would be asking for something not present.
    image.sampler = ImageSampler::linear();
    images.add(image)
}

/// A neutral mid-grey, used when a texture is requested but none resolved.
///
/// This exists so "no texture" is a *visible* state rather than a black one: a
/// model that silently turns black looks like a decode bug, and diagnosing that
/// costs more than showing grey.
pub const MISSING_TEXTURE_TINT: Color = Color::srgb(0.35, 0.35, 0.38);

/// How many textures a model resolved, for the report line.
pub fn resolved_count(
    results: &[Result<spore_material::ResolvedTexture, spore_material::MaterialError>],
) -> usize {
    results.iter().filter(|r| r.is_ok()).count()
}
