//! Typed model loading: a record identity in, meshes out.
//!
//! Two container families reach this layer:
//!
//! * **GMDL** (`0x00E6BCE5`) -- Spore's own geometry container. Fully decoded.
//! * **RW4** (`0x2F4E681B`) -- a RenderWare 4 container. Only its *section
//!   directory* is understood; no section payload is decoded.
//!
//! Note what is **not** on either path: `png` (`0x2F7D0004`) is a *different*
//! type id and is **raw PNG** -- measured 10 487 of 10 487 across the installed
//! packages. It is not an RW4 container, and nothing here decodes it.
//!
//! An RW4 record is accepted here but produces **no** meshes. That is stated in
//! [`LoadedModel::meshes`] being empty rather than hidden behind a pretend
//! success: the engine can show what has been decoded and cannot show what
//! has not, and the difference stays visible.

use spore_core::ResourceKey;
use spore_gmdl::{GmdlModel, Mesh};
use spore_rw4::Rw4;

use crate::error::AssetError;
use crate::store::ContentStore;

/// Which container a model record turned out to be.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ModelFormat {
    /// Spore's `gmdl`.
    Gmdl,
    /// A RenderWare 4 container.
    Rw4,
}

impl ModelFormat {
    /// The container's name, for messages.
    pub const fn as_str(self) -> &'static str {
        match self {
            Self::Gmdl => "gmdl",
            Self::Rw4 => "rw4",
        }
    }
}

impl core::fmt::Display for ModelFormat {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        f.write_str(self.as_str())
    }
}

/// Everything a model record yielded.
#[derive(Debug)]
pub struct LoadedModel {
    /// The identity that was loaded.
    pub key: ResourceKey,
    /// Which package answered.
    pub package_name: String,
    /// The container it decoded as.
    pub format: ModelFormat,
    /// The decoded GMDL, when `format` is [`ModelFormat::Gmdl`].
    pub gmdl: Option<GmdlModel>,
    /// The decoded RW4 section directory, when `format` is [`ModelFormat::Rw4`].
    pub rw4: Option<Rw4>,
    /// One mesh per `gmdl` mesh entry. Empty for RW4 (payloads undecoded).
    pub meshes: Vec<Mesh>,
    /// Texture identities the material info referenced, in encounter order.
    ///
    /// These are *references the record makes*, not textures that were loaded.
    pub texture_refs: Vec<ResourceKey>,
}

/// Loads models out of a [`ContentStore`].
#[derive(Debug, Clone, Copy)]
pub struct ModelStore<'a> {
    store: &'a ContentStore,
}

impl<'a> ModelStore<'a> {
    /// Borrows a store.
    pub fn new(store: &'a ContentStore) -> Self {
        Self { store }
    }

    /// The store this loader reads from.
    pub fn store(&self) -> &'a ContentStore {
        self.store
    }

    /// Loads and decodes the model at `key`.
    ///
    /// Accepts `gmdl` and `rw4` type ids and refuses anything else by name.
    pub fn load(&self, key: &ResourceKey) -> Result<LoadedModel, AssetError> {
        let found = self.store.find(key)?;
        let bytes = self.store.read(key)?;

        match key.type_id {
            spore_gmdl::GMDL_TYPE => {
                let gmdl = spore_gmdl::parse(&bytes)
                    .map_err(|source| AssetError::Gmdl { key: *key, source })?;
                let mut meshes = Vec::with_capacity(gmdl.mesh_count as usize);
                for index in 0..gmdl.mesh_count {
                    let mesh = spore_gmdl::mesh_from_gmdl(&gmdl, index)
                        .map_err(|source| AssetError::Gmdl { key: *key, source })?;
                    meshes.push(mesh);
                }
                if meshes.is_empty() {
                    return Err(AssetError::EmptyModel {
                        key: *key,
                        format: "gmdl",
                    });
                }
                let texture_refs = gmdl
                    .texture_refs
                    .iter()
                    .map(|t| {
                        ResourceKey::new(
                            spore_core::record::type_id::RASTER,
                            t.group_id,
                            t.instance_id,
                        )
                    })
                    .collect();
                Ok(LoadedModel {
                    key: *key,
                    package_name: found.package_name.to_owned(),
                    format: ModelFormat::Gmdl,
                    gmdl: Some(gmdl),
                    rw4: None,
                    meshes,
                    texture_refs,
                })
            }
            spore_rw4::RW4_TYPE => {
                let rw4 = spore_rw4::parse(&bytes)
                    .map_err(|source| AssetError::Rw4 { key: *key, source })?;
                Ok(LoadedModel {
                    key: *key,
                    package_name: found.package_name.to_owned(),
                    format: ModelFormat::Rw4,
                    gmdl: None,
                    rw4: Some(rw4),
                    // Section payloads are not decoded yet. Empty is the truth.
                    meshes: Vec::new(),
                    texture_refs: Vec::new(),
                })
            }
            other => Err(AssetError::UnsupportedModelType {
                key: *key,
                type_id: other,
            }),
        }
    }

    /// Loads only the first mesh of a `gmdl`, which is what a single-entity
    /// spawn wants.
    pub fn load_first_mesh(&self, key: &ResourceKey) -> Result<(LoadedModel, Mesh), AssetError> {
        let model = self.load(key)?;
        // Clone before moving: `meshes.first()` borrows `model`, and the
        // return value moves it.
        let mesh = model
            .meshes
            .first()
            .cloned()
            .ok_or(AssetError::EmptyModel {
                key: *key,
                format: model.format.as_str(),
            })?;
        Ok((model, mesh))
    }
}

/// A decoded 2-D texture.
#[derive(Debug)]
pub struct LoadedTexture {
    /// The identity that was loaded.
    pub key: ResourceKey,
    /// Which package answered.
    pub package_name: String,
    /// The decoded raster.
    pub image: spore_texture::RasterImage,
}

/// Loads textures out of a [`ContentStore`].
#[derive(Debug, Clone, Copy)]
pub struct TextureStore<'a> {
    store: &'a ContentStore,
}

impl<'a> TextureStore<'a> {
    /// Borrows a store.
    pub fn new(store: &'a ContentStore) -> Self {
        Self { store }
    }

    /// Loads and decodes the `raster` record at `key`.
    pub fn load(&self, key: &ResourceKey) -> Result<LoadedTexture, AssetError> {
        let found = self.store.find(key)?;
        let bytes = self.store.read(key)?;
        let image = spore_texture::decode_raster(&bytes)
            .map_err(|source| AssetError::Texture { key: *key, source })?;
        Ok(LoadedTexture {
            key: *key,
            package_name: found.package_name.to_owned(),
            image,
        })
    }

    /// Loads the largest mip of layer 0, ready for upload as an RGBA8 image.
    ///
    /// Mip 0 is the full-resolution level; the raster's other layers and mips
    /// stay in [`LoadedTexture::image`] for callers that build a mip chain.
    pub fn load_base_level(
        &self,
        key: &ResourceKey,
    ) -> Result<(LoadedTexture, spore_texture::MipImage), AssetError> {
        let loaded = self.load(key)?;
        let base = loaded
            .image
            .layers
            .first()
            .and_then(|layer| layer.first())
            .cloned()
            .ok_or(AssetError::Texture {
                key: *key,
                source: spore_texture::TextureError::OutputInvariant {
                    width: loaded.image.envelope.width,
                    height: loaded.image.envelope.height,
                    texel_x: 0,
                    texel_y: 0,
                },
            })?;
        Ok((loaded, base))
    }
}
