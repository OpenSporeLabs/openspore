//! The scene: camera, light, ground and the placeholder.
//!
//! Kept apart from the asset bridge so the "is the renderer alive" question and
//! the "can it read a Spore record" question have separate answers. Swapping the
//! contents of the world must not require touching the camera.

use bevy::pbr::StandardMaterial;
use bevy::prelude::*;

/// A soft sky colour behind everything.
pub const BACKDROP: Color = Color::srgb(0.05, 0.06, 0.09);

/// The colour of the reference floor grid.
pub const GROUND: Color = Color::srgb(0.16, 0.17, 0.20);

/// The colour used for a loaded asset that has no usable texture.
pub const ASSET_TINT: Color = Color::srgb(0.86, 0.62, 0.32);

/// The colour used for the placeholder mesh.
pub const PLACEHOLDER_TINT: Color = Color::srgb(0.30, 0.68, 0.86);

/// Marker for the camera, so a scene can be retargeted without a name string.
#[derive(Debug, Clone, Copy, Component, Default)]
pub struct MainCamera;

/// Marker for the asset entity currently on show.
#[derive(Debug, Clone, Copy, Component, Default)]
pub struct OnStage;

/// Spawns the camera, the key light, the ground and the backdrop.
pub fn spawn_stage(
    commands: &mut Commands,
    meshes: &mut Assets<Mesh>,
    materials: &mut Assets<StandardMaterial>,
) {
    commands.insert_resource(ClearColor(Color::BLACK));

    // A 3D camera framed so a model of roughly unit-to-10-unit size lands in
    // view. Spore geometry is authored in its own units (the documented asset's
    // file bounding radius is 13.77), so the distance is a starting point that
    // the camera fit system then corrects per asset.
    commands.spawn((
        Camera3d::default(),
        MainCamera,
        Transform::from_xyz(0.0, 6.0, 34.0).looking_at(Vec3::ZERO, Vec3::Y),
    ));

    commands.spawn((
        DirectionalLight {
            illuminance: 9_000.0,
            shadow_maps_enabled: true,
            ..default()
        },
        Transform::from_xyz(8.0, 14.0, 8.0).looking_at(Vec3::ZERO, Vec3::Y),
    ));

    // A dim fill from the opposite side so an unlit-looking back face still has
    // some shape. Two lights is the smallest rig that reads as a scene.
    commands.spawn((
        DirectionalLight {
            illuminance: 2_500.0,
            shadow_maps_enabled: false,
            contact_shadows_enabled: false,
            ..default()
        },
        Transform::from_xyz(-10.0, 4.0, -6.0).looking_at(Vec3::ZERO, Vec3::Y),
    ));

    commands.spawn((
        Mesh3d(meshes.add(Plane3d::default().mesh().size(400.0, 400.0))),
        MeshMaterial3d(materials.add(StandardMaterial {
            base_color: GROUND,
            perceptual_roughness: 0.95,
            metallic: 0.0,
            ..default()
        })),
        Transform::from_xyz(0.0, -0.01, 0.0),
    ));
}

/// Spawns the built-in placeholder mesh, used by `--placeholder`.
///
/// It exists so "the window opened and something rendered" can be established
/// with no game install at all. If that cannot be demonstrated, every later
/// failure is ambiguous between "the renderer is broken" and "the asset is
/// wrong", and the vertical slice stops being debuggable.
pub fn spawn_placeholder(
    commands: &mut Commands,
    meshes: &mut Assets<Mesh>,
    materials: &mut Assets<StandardMaterial>,
) -> Entity {
    commands
        .spawn((
            Mesh3d(meshes.add(Sphere::new(2.0).mesh().uv(32, 18))),
            MeshMaterial3d(materials.add(StandardMaterial {
                base_color: PLACEHOLDER_TINT,
                perceptual_roughness: 0.35,
                metallic: 0.1,
                ..default()
            })),
            Transform::from_xyz(0.0, 2.0, 0.0),
            OnStage,
        ))
        .id()
}

/// Despawns whatever was on stage, so a scene change never stacks up entities.
pub fn clear_stage(commands: &mut Commands, existing: &mut Query<Entity, With<OnStage>>) {
    for entity in existing.iter() {
        commands.entity(entity).despawn();
    }
}
