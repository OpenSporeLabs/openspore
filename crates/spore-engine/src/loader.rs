//! The asset bridge: a decoded Spore model becomes an entity on screen.
//!
//! This is the one place where `spore-assets` (pure, testable, no GPU) meets
//! Bevy (assets, components, spawn). Everything that can be decided without a
//! renderer *is* decided in `spore-assets` or [`crate::convert`]; what is left
//! here is only the part that genuinely needs an `Assets<Mesh>` handle.
//!
//! # Load strategy, and why it is what it is
//!
//! A `.package` file is memory-mapped and its index parsed once. Both cost real
//! time -- `Spore_Content.package` is ~995 MB and its index holds ~103k rows --
//! so neither happens inside a frame, and neither happens inside a Bevy system:
//! [`crate::prepare`] does it before the app exists. What is left here is a
//! decode result already in hand, which is why this module never reports an
//! error of its own about locating a record.

use std::path::Path;
use std::sync::Arc;

use bevy::app::Plugin;
use bevy::pbr::StandardMaterial;
use bevy::prelude::*;

use spore_assets::{AssetError, ContentStore, LoadedModel, Package};
use spore_core::ResourceKey;

use crate::convert::{self, NormalMode};
use crate::scene::{self, OnStage};

/// Decoded content for one record: geometry, and optionally its textures.
///
/// Not `Clone`: `spore_material::MaterialError` wraps `spore_assets::AssetError`,
/// which wraps `std::io::Error` and therefore cannot be cloned. Sharing the
/// decoded content is done with an [`Arc`] on [`StagedContent`] instead.
///
/// # Textures are resolved here, not at spawn time
///
/// `spore-material` needs a [`ContentStore`], which is a live resource over
/// memory-mapped packages. If textures were resolved inside a spawn system the
/// mapping would have to outlive the app or be re-entered per spawn. Resolving
/// up front -- in [`crate::prepare`], before Bevy exists -- keeps the store a
/// plain local and makes `--info` report texture resolution too, so the headless
/// path and the visible path cannot disagree about what loaded.
#[derive(Debug, Default)]
pub struct DecodedTextures {
    /// One entry per texture the model referenced, in encounter order.
    pub results: Vec<Result<spore_material::ResolvedTexture, spore_material::MaterialError>>,
    /// Whether texture resolution was requested at all.
    pub requested: bool,
}

impl DecodedTextures {
    /// How many references resolved.
    pub fn resolved(&self) -> usize {
        self.results.iter().filter(|r| r.is_ok()).count()
    }

    /// How many were refused, with the reasons.
    pub fn failures(&self) -> Vec<&spore_material::MaterialError> {
        self.results
            .iter()
            .filter_map(|r| r.as_ref().err())
            .collect()
    }
}

/// A decoded model, ready to be turned into entities.
///
/// Holds the model behind an [`Arc`] so inserting it as a Bevy resource is a
/// pointer copy rather than a deep clone of every vertex buffer, and so
/// [`crate::build_scene_app`] can take it by value without duplicating it.
#[derive(Debug, Resource)]
pub struct StagedContent {
    /// What was decoded.
    pub model: Arc<LoadedModel>,
    /// World-space uniform scale to apply.
    pub scale: f32,
    /// Which packages were searched, in resolution order.
    pub packages: Vec<String>,
    /// Textures, when they were requested.
    pub textures: DecodedTextures,
}

impl StagedContent {
    /// Wraps a decoded model, with no textures.
    pub fn new(model: LoadedModel, scale: f32) -> Self {
        Self {
            model: Arc::new(model),
            scale,
            packages: Vec::new(),
            textures: DecodedTextures::default(),
        }
    }

    /// Which packages were searched, in resolution order.
    pub fn with_packages(mut self, packages: Vec<String>) -> Self {
        self.packages = packages;
        self
    }

    /// Attaches resolved textures, in the order the model referenced them.
    pub fn with_textures(
        mut self,
        results: Vec<Result<spore_material::ResolvedTexture, spore_material::MaterialError>>,
    ) -> Self {
        self.textures = DecodedTextures {
            results,
            requested: true,
        };
        self
    }

    /// Total triangles across every mesh.
    pub fn triangles(&self) -> usize {
        self.model.meshes.iter().map(|m| m.indices.len() / 3).sum()
    }

    /// The union of every mesh's bounds, or `None` when there are no meshes.
    pub fn bounds(&self) -> Option<([f32; 3], [f32; 3])> {
        let mut bounds: Option<([f32; 3], [f32; 3])> = None;
        for mesh in &self.model.meshes {
            bounds = Some(match bounds {
                None => (mesh.bounds_min, mesh.bounds_max),
                Some((lo, hi)) => (
                    [
                        lo[0].min(mesh.bounds_min[0]),
                        lo[1].min(mesh.bounds_min[1]),
                        lo[2].min(mesh.bounds_min[2]),
                    ],
                    [
                        hi[0].max(mesh.bounds_max[0]),
                        hi[1].max(mesh.bounds_max[1]),
                        hi[2].max(mesh.bounds_max[2]),
                    ],
                ),
            });
        }
        bounds
    }

    /// The one-line, versioned report the tooling and CI parse.
    ///
    /// The trailing `decode=` field is the important one: a model whose tail
    /// stopped at the material-info table has COMPLETE geometry, and this
    /// report says so rather than letting a consumer infer completeness from
    /// the presence of a mesh.
    ///
    /// Fixed field set and fixed order, because the point of a machine-readable
    /// line is that a consumer can rely on it -- the same discipline as the
    /// repository's existing `CELLSTAGE-MANIFEST v1`.
    ///
    /// The `normals=` field is stated rather than implied, because this engine
    /// *derives* normals from the triangles instead of decoding the record's
    /// `UBYTE4` bytes (see `spore_gmdl::claims::vertex_normal_encoding`). A
    /// reader must not have to know that to know which shading it is looking at.
    pub fn report_line(&self) -> String {
        let (lo, hi) = self.bounds().unwrap_or(([0.0; 3], [0.0; 3]));
        format!(
            "OPENSPORE-STAGED v1 key={} package={} format={} meshes={} triangles={} \
             bounds_min={:.6},{:.6},{:.6} bounds_max={:.6},{:.6},{:.6} normals=derived \
             textures={}/{}",
            self.model.key,
            self.model.package_name,
            self.model.format.as_str(),
            self.model.meshes.len(),
            self.triangles(),
            lo[0],
            lo[1],
            lo[2],
            hi[0],
            hi[1],
            hi[2],
            self.textures.resolved(),
            self.textures.results.len(),
        ) + &format!(
            " decode={decode}",
            decode = self
                .model
                .stop_text()
                .unwrap_or_else(|| "complete".to_owned())
        )
    }
}

/// Opens the packages named by a request, in the order given.
///
/// Reports every failure as a value rather than a panic: a missing game install
/// is an ordinary operating state for a cross-platform engine, not a bug.
pub fn open_packages<P: AsRef<Path>>(paths: &[P]) -> Result<ContentStore, AssetError> {
    let mut store = ContentStore::new();
    for path in paths {
        store.push(Package::open(package_name(path.as_ref()), path.as_ref())?);
    }
    Ok(store)
}

/// The display name for a package path: its file stem.
fn package_name(path: &Path) -> String {
    path.file_stem()
        .map(|s| s.to_string_lossy().into_owned())
        .unwrap_or_else(|| path.display().to_string())
}

/// What happened when content was put on stage.
#[derive(Debug, Clone, PartialEq)]
pub enum StageOutcome {
    /// The content was spawned.
    Staged {
        /// The identity shown.
        key: ResourceKey,
        /// Which package answered.
        package: String,
        /// How many entities were spawned.
        entities: usize,
        /// How many triangles in total.
        triangles: usize,
        /// Where the geometry sits, for camera framing.
        bounds: ([f32; 3], [f32; 3]),
    },
    /// Nothing was spawned, because the content held no meshes.
    NothingToShow {
        /// The identity that was asked for.
        key: ResourceKey,
        /// Why there was nothing to show.
        reason: String,
    },
}

/// Spawns entities for already-decoded content.
///
/// Takes the decode result rather than looking one up, because the lookup
/// already happened outside the render loop; re-doing it here would make the
/// window's contents depend on when it was opened.
pub fn stage_decoded(
    content: &StagedContent,
    commands: &mut Commands,
    meshes: &mut Assets<Mesh>,
    materials: &mut Assets<StandardMaterial>,
    images: &mut Assets<Image>,
) -> StageOutcome {
    // NOTE: the world is spawned by `ScenePlugin`, NOT here. When this call
    // remained alongside the plugin, every run produced two cameras and two
    // lights -- the model rendered from whichever camera Bevy picked, the
    // framing query found "multiple entities", and the result looked like a
    // camera-framing bug rather than a duplicate spawn. Bevy's own
    // "Camera order ambiguities detected" warning is what caught it.
    //
    // `ScenePlugin` owns the world; `SporeAssetPlugin` owns the content. One
    // owner each, so neither can double up.

    if content.model.meshes.is_empty() {
        let reason = format!(
            "record {} decoded as {} but produced no mesh; this container's payloads are not decoded yet",
            content.model.key,
            content.model.format.as_str()
        );
        warn!("{reason}");
        return StageOutcome::NothingToShow {
            key: content.model.key,
            reason,
        };
    }

    let bounds = content.bounds().unwrap_or(([0.0; 3], [0.0; 3]));
    let floor_offset = -bounds.0[1];

    // One texture is applied when one resolved. Which of a model's texture
    // references is the *diffuse* one is NOT known -- the 16 header bytes of a
    // texture-set entry are undecoded, and `spore-material` therefore exposes
    // `SamplerRole::Unresolved` as its only variant. Picking the first resolved
    // reference and saying so is a *stated visual choice*, not a claim about the
    // record; the alternative, refusing to texture anything, would leave the
    // material path untested against real data.
    let first_texture: Option<Handle<Image>> = content
        .textures
        .results
        .iter()
        .find_map(|r| r.as_ref().ok())
        .map(|t| {
            info!(
                "applying texture {} ({}x{}, {} mip(s), {} layer(s)) as the diffuse colour",
                t.key, t.image.width, t.image.height, t.mip_count, t.layer_count
            );
            crate::texture::to_bevy_image(t, images)
        });
    if content.textures.requested && first_texture.is_none() {
        warn!(
            "textures were requested but {} reference(s) all failed; the model will use the flat tint",
            content.textures.results.len()
        );
    }

    for (index, mesh) in content.model.meshes.iter().enumerate() {
        let buffers = convert::to_buffers(mesh);
        let bevy_mesh = convert::to_bevy_mesh(&buffers, NormalMode::Computed);
        let material = materials.add(StandardMaterial {
            base_color: if first_texture.is_some() {
                Color::WHITE
            } else {
                scene::ASSET_TINT
            },
            base_color_texture: first_texture.clone(),
            perceptual_roughness: 0.55,
            metallic: 0.05,
            // Spore geometry carries its own winding convention, which has not
            // been confirmed against a rendered original frame. Culling back
            // faces on a guess would make a model invisible; showing both sides
            // cannot hide geometry. Revisit when a reference frame exists.
            double_sided: true,
            ..default()
        });
        // Lift onto the floor: a model authored around its own origin would
        // otherwise sink below the ground plane. Extra meshes are spread along X
        // so a multi-mesh record does not z-fight with itself.
        let spread = (index as f32) * 6.0;
        commands.spawn((
            Mesh3d(meshes.add(bevy_mesh)),
            MeshMaterial3d(material),
            Transform::from_xyz(spread, floor_offset, 0.0).with_scale(Vec3::splat(content.scale)),
            OnStage,
        ));
    }

    StageOutcome::Staged {
        key: content.model.key,
        package: content.model.package_name.clone(),
        entities: content.model.meshes.len(),
        triangles: content.triangles(),
        bounds,
    }
}

/// Spawns entities for [`StagedContent`] during `Startup`.
///
/// The plugin is the boundary between "a record has been decoded" and "there is
/// something on screen". It is one system over one resource, which is the
/// smallest thing that is still a real seam: a second content source (a
/// procedural creature, a mod-provided asset, a test fixture) becomes a second
/// implementation of "produce `StagedContent`", with no change here.
///
/// The resource must be inserted before the app is built, which
/// [`crate::build_scene_app`] does. That ordering is deliberate: the decode
/// happens outside Bevy so a failure is reportable without a window.
#[derive(Debug, Clone, Copy, Default)]
pub struct SporeAssetPlugin;

impl Plugin for SporeAssetPlugin {
    fn build(&self, app: &mut App) {
        app.add_systems(Startup, spawn_staged_content);
    }
}

fn spawn_staged_content(
    mut commands: Commands,
    content: Res<StagedContent>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<StandardMaterial>>,
    mut images: ResMut<Assets<Image>>,
) {
    // NOTE: there is deliberately NO camera query here. `Commands::spawn` is
    // deferred, so a `Query` in the same system that spawns the camera sees zero
    // cameras -- which would silently leave the camera at its default position.
    // The framing runs in `PostStartup` instead; see `crate::build_scene_app`.
    let outcome = stage_decoded(
        &content,
        &mut commands,
        &mut meshes,
        &mut materials,
        &mut images,
    );
    info!("{outcome:?}");
}

/// Turns a loader failure into something a person can act on.
pub fn describe(error: &AssetError) -> String {
    match error {
        AssetError::NotFound {
            key,
            searched,
            candidates,
        } => {
            let mut message =
                format!("record {key} is not in any of the {searched} package(s) searched");
            if !candidates.is_empty() {
                let list: Vec<String> =
                    candidates.iter().take(5).map(ToString::to_string).collect();
                message.push_str(&format!(
                    "; nearby identities of that type: {}",
                    list.join(", ")
                ));
            }
            message
        }
        AssetError::EmptyStore => {
            "no Spore package was loaded. Pass --package <path> pointing at a .package file."
                .to_owned()
        }
        other => other.to_string(),
    }
}

/// Frames the camera on a bounding box.
///
/// Deliberately simple: fit the box's bounding sphere into the vertical field
/// of view with a margin, from a fixed oblique angle. Spore's own camera
/// behaviour is a separate and much later question, and pretending to know it
/// here would be an invention.
pub fn frame_camera(
    camera: &mut Transform,
    bounds: ([f32; 3], [f32; 3]),
    vertical_fov_degrees: f32,
) {
    let center = Vec3::new(
        (bounds.0[0] + bounds.1[0]) * 0.5,
        (bounds.0[1] + bounds.1[1]) * 0.5,
        (bounds.0[2] + bounds.1[2]) * 0.5,
    );
    let extent = Vec3::new(
        bounds.1[0] - bounds.0[0],
        bounds.1[1] - bounds.0[1],
        bounds.1[2] - bounds.0[2],
    );
    let radius = 0.5 * extent.length().max(1e-3);
    let fov = vertical_fov_degrees.to_radians();
    // distance = radius / sin(fov / 2), with a 1.25 margin so the model never
    // touches the edge of the frame.
    let distance = radius / (fov * 0.5).sin().max(1e-3) * 1.25;
    let direction = Vec3::new(0.0, 0.42, 0.91).normalize();
    *camera =
        Transform::from_translation(center + direction * distance).looking_at(center, Vec3::Y);
}

#[cfg(test)]
mod tests {
    use super::*;
    use spore_assets::Package;
    use spore_gmdl::Mesh;
    use std::path::PathBuf;

    fn fixture_package() -> ContentStore {
        let path = concat!(
            env!("CARGO_MANIFEST_DIR"),
            "/../../tests/fixtures/mini_package.dbpf"
        );
        let mut store = ContentStore::new();
        store.push(Package::from_vec("mini", std::fs::read(path).unwrap()).unwrap());
        store
    }

    fn triangle_mesh() -> Mesh {
        Mesh {
            positions: vec![[0.0, 0.0, 0.0], [1.0, 0.0, 0.0], [0.0, 1.0, 0.0]],
            normals: vec![[1.0, 0.0, 0.0]; 3],
            uvs: vec![[0.0, 0.0], [1.0, 0.0], [0.0, 1.0]],
            indices: vec![0, 1, 2],
            topology: spore_gmdl::Topology::TriangleList,
            bounds_min: [0.0, 0.0, 0.0],
            bounds_max: [1.0, 1.0, 0.0],
            radius: 1.0,
        }
    }

    fn content_with(meshes: Vec<Mesh>) -> StagedContent {
        let key = ResourceKey::new(spore_gmdl::GMDL_TYPE, 1, 2);
        let _ = fixture_package();
        StagedContent {
            model: Arc::new(LoadedModel {
                key,
                package_name: "mini".into(),
                format: spore_assets::ModelFormat::Gmdl,
                gmdl: None,
                rw4: None,
                meshes,
                texture_refs: Vec::new(),
                stopped_at: None,
            }),
            scale: 1.0,
            packages: vec!["mini".into()],
            textures: DecodedTextures::default(),
        }
    }

    #[test]
    fn bounds_are_the_union_of_every_mesh() {
        let mut second = triangle_mesh();
        second.bounds_min = [-5.0, -2.0, -1.0];
        second.bounds_max = [-1.0, 0.0, 0.0];
        let content = content_with(vec![triangle_mesh(), second]);
        let (lo, hi) = content.bounds().unwrap();
        assert_eq!(lo, [-5.0, -2.0, -1.0]);
        assert_eq!(hi, [1.0, 1.0, 0.0]);
    }

    #[test]
    fn triangles_counts_indices_not_indices_over_three() {
        assert_eq!(
            content_with(vec![triangle_mesh(), triangle_mesh()]).triangles(),
            2
        );
        assert_eq!(content_with(Vec::new()).triangles(), 0);
    }

    #[test]
    fn the_report_line_is_versioned_and_carries_the_fixed_field_set() {
        let content = content_with(vec![triangle_mesh()]);
        let line = content.report_line();
        assert!(line.starts_with("OPENSPORE-STAGED v1 "), "{line}");
        for field in [
            "key=",
            "package=",
            "format=",
            "meshes=",
            "triangles=",
            "bounds_min=",
            "bounds_max=",
        ] {
            assert!(
                line.contains(field),
                "the report must carry {field}: {line}"
            );
        }
        assert!(
            line.contains("normals=derived"),
            "the normal policy must be stated, not implied: {line}"
        );
    }

    #[test]
    fn content_with_no_meshes_reports_zero_rather_than_omitting_fields() {
        let line = content_with(Vec::new()).report_line();
        assert!(line.contains("meshes=0"), "{line}");
        assert!(line.contains("triangles=0"), "{line}");
    }

    #[test]
    fn a_record_with_no_meshes_is_reported_as_nothing_to_show() {
        // Constructed here rather than through `stage_decoded` because that
        // function needs an `App` world; the classification logic it depends on
        // is `meshes.is_empty()`, which this pins.
        let content = content_with(Vec::new());
        assert!(content.model.meshes.is_empty());
        assert!(content.bounds().is_none());
    }

    #[test]
    fn not_found_names_the_record_and_offers_alternatives() {
        let error = AssetError::NotFound {
            key: ResourceKey::new(0x00E6_BCE5, 1, 2),
            searched: 3,
            candidates: vec![
                ResourceKey::new(0x00E6_BCE5, 3, 4),
                ResourceKey::new(0x00E6_BCE5, 5, 6),
            ],
        };
        let message = describe(&error);
        assert!(
            message.contains("0x00e6bce5:0x00000001:0x00000002"),
            "{message}"
        );
        assert!(message.contains("3 package"), "{message}");
        assert!(
            message.contains("0x00e6bce5:0x00000003:0x00000004"),
            "{message}"
        );
    }

    #[test]
    fn a_not_found_with_no_candidates_does_not_invent_one() {
        let error = AssetError::NotFound {
            key: ResourceKey::new(1, 2, 3),
            searched: 1,
            candidates: Vec::new(),
        };
        assert!(!describe(&error).contains("nearby"));
    }

    #[test]
    fn an_empty_store_is_reported_with_the_fix_not_a_symptom() {
        assert_eq!(
            describe(&AssetError::EmptyStore),
            "no Spore package was loaded. Pass --package <path> pointing at a .package file."
        );
    }

    #[test]
    fn opening_a_missing_package_is_an_error_naming_the_path() {
        let error = open_packages(&[PathBuf::from("/definitely/not/here.package")]).unwrap_err();
        assert!(
            error.to_string().contains("/definitely/not/here.package"),
            "{error}"
        );
    }

    #[test]
    fn camera_framing_puts_the_box_centre_in_view_and_backs_off_by_its_radius() {
        let mut camera = Transform::default();
        frame_camera(
            &mut camera,
            ([-10.0, -10.0, -10.0], [10.0, 10.0, 10.0]),
            60.0,
        );
        let distance = camera.translation.length();
        assert!(
            distance > 10.0,
            "the camera must be outside the box, got {distance}"
        );
        assert!(
            camera.forward().dot(-camera.translation) > 0.0,
            "camera is not looking at the centre"
        );
    }

    #[test]
    fn camera_framing_survives_a_degenerate_box() {
        let mut camera = Transform::default();
        frame_camera(&mut camera, ([0.0, 0.0, 0.0], [0.0, 0.0, 0.0]), 60.0);
        assert!(
            camera.translation.is_finite(),
            "a zero-extent box must not produce NaN"
        );
    }
}
