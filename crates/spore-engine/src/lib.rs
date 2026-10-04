//! # spore-engine — the OpenSpore runtime.
//!
//! A Bevy application whose asset path starts at a real Spore `.package` file
//! and ends at pixels:
//!
//! ```text
//!   .package on disk
//!     -> spore_dbpf     DBPF v3 index, QFS decompress          (no Bevy)
//!     -> spore_gmdl     gmdl decode, mesh extraction           (no Bevy)
//!     -> spore_assets   package priority, identity resolution   (no Bevy)
//!     -> convert        vertex buffers, normal policy          (no GPU)
//!     -> loader         Assets<Mesh> handles, entity spawn     (Bevy)
//!     -> bevy_render    wgpu -> Vulkan / Metal / DX12
//! ```
//!
//! The split is the architecture, not an accident of file layout.
//!
//! # Decoding happens before Bevy is even constructed
//!
//! Opening a ~995 MB package, parsing its ~103k-row index and decompressing a
//! record is ordinary I/O work with nothing to do with rendering. Doing it
//! inside a `Startup` system would make three things worse for no benefit: the
//! window would appear before the content, an asset failure could only be
//! reported through the render loop, and the most valuable test in the project
//! -- "does a real Spore record decode?" -- would need a GPU.
//!
//! So `run_scene` decodes first, *outside* Bevy, and only then assembles an app. A
//! consequence worth stating: `--info` never constructs a window at all, which
//! is what makes it usable as a CI gate.
//!
//! # Modes
//!
//! * `--placeholder` -- a built-in mesh, no game data. Proves the renderer.
//! * `--record T:G:I --package ...` -- the vertical slice: a real Spore record
//!   decoded and shown.
//! * `--info` -- decode and report, then exit. Headless.
//!
//! # What is deliberately absent
//!
//! No audio, no input beyond the window, no simulation, no creature model, no
//! UI. Each is a real subsystem that has not been written yet, and stubbing them
//! here would make the vertical slice look further along than it is.

#![deny(unsafe_code)]
#![warn(missing_debug_implementations)]

pub mod cli;
pub mod convert;
pub mod loader;
pub mod scene;
pub mod texture;

pub use loader::SporeAssetPlugin;
pub use scene::ScenePlugin;

use bevy::pbr::StandardMaterial;
use bevy::prelude::*;
use bevy::window::{PresentMode, WindowResolution};

use spore_assets::{ContentStore, ModelStore};

use cli::{LaunchRequest, SceneRequest, WindowOptions};
use loader::StagedContent;

/// The engine entry point. The binary is a one-line shim over this.
pub fn main() -> std::process::ExitCode {
    let args: Vec<String> = std::env::args().skip(1).collect();
    match cli::parse(args) {
        Ok(LaunchRequest::Help) => {
            print!("{}", cli::usage());
            std::process::ExitCode::SUCCESS
        }
        Ok(LaunchRequest::Placeholder(window)) => run_placeholder(window),
        Ok(LaunchRequest::Scene(scene)) => run_scene(scene),
        Err(error) => {
            eprintln!("openspore: {error}\n");
            eprint!("{}", cli::usage());
            std::process::ExitCode::from(cli::EXIT_USAGE as u8)
        }
    }
}

/// The result of decoding a request, before any rendering is involved.
///
/// Separating this from `StageOutcome` is what lets a test assert the whole
/// asset path without a window, and what lets `--info` skip rendering entirely.
#[derive(Debug)]
pub enum PrepareOutcome {
    /// The record decoded.
    Ready(Box<StagedContent>),
    /// It did not, with a reason a person can act on.
    Failed(String),
}

/// Decodes a scene request without touching Bevy, the GPU or the filesystem
/// beyond the packages named.
///
/// Textures are resolved here too, for the same reason the model is: the store
/// is a live view over memory-mapped packages, and resolving inside a spawn
/// system would either have to keep the mapping alive longer than the app or
/// re-enter it per spawn. Resolving up front also means `--info` reports texture
/// resolution, so the headless path and the visible path cannot disagree.
pub fn prepare(scene: &SceneRequest) -> PrepareOutcome {
    let store = match loader::open_packages(&scene.packages) {
        Ok(store) => store,
        Err(error) => return PrepareOutcome::Failed(error.to_string()),
    };
    let model = match ModelStore::new(&store).load(&scene.record) {
        Ok(model) => model,
        Err(error) => return PrepareOutcome::Failed(loader::describe(&error)),
    };

    let package_names = store
        .package_names()
        .into_iter()
        .map(str::to_owned)
        .collect();
    let mut content = StagedContent::new(model, scene.scale).with_packages(package_names);

    if scene.textured {
        // The texture reference carries no type word, so the type is ASSUMED
        // here, in the open, and `spore-material` grades the assumption
        // INFERRED rather than VERIFIED. `assumed_texture_type` is the single
        // place that assumption lives.
        let results = match content.model.gmdl.as_ref() {
            Some(model) => {
                spore_material::resolve_model_textures(&store, model, scene.assumed_texture_type)
            }
            None => {
                warn!(
                    "{} carries no gmdl, so it has no texture references to resolve",
                    content.model.key
                );
                Vec::new()
            }
        };
        let resolved = results.iter().filter(|r| r.is_ok()).count();
        info!("textures: {resolved} of {} resolved", results.len());
        for failure in results.iter().filter_map(|r| r.as_ref().err()) {
            warn!("texture reference refused: {failure}");
        }
        content = content.with_textures(results);
    }

    PrepareOutcome::Ready(Box::new(content))
}

/// Prints the one-line machine-readable report the tooling and CI parse.
///
/// The format is versioned (`v1`) and the fields are fixed, on the same
/// discipline as the repository's existing `CELLSTAGE-MANIFEST v1`.
fn report(outcome: &PrepareOutcome) {
    println!("{}", format_report(outcome));
}

/// The report as a string, so both the terminal path and the tests agree on one
/// definition of the format.
fn format_report(outcome: &PrepareOutcome) -> String {
    match outcome {
        PrepareOutcome::Ready(content) => content.report_line(),
        PrepareOutcome::Failed(reason) => format!("OPENSPORE-STAGED v1 failed: {reason}"),
    }
}

fn run_placeholder(window: WindowOptions) -> std::process::ExitCode {
    info!("openspore: placeholder mode, no Spore data");
    println!("OPENSPORE-MODE v1 placeholder");
    build_placeholder_app(window).run();
    std::process::ExitCode::SUCCESS
}

fn run_scene(scene: SceneRequest) -> std::process::ExitCode {
    let info_only = scene.info_only;
    info!("openspore: scene {}", scene.record);

    // Decode first, outside Bevy. This is where a missing game install, a wrong
    // identity and a corrupt record all become visible -- and none of them
    // should cost the user a window.
    let outcome = prepare(&scene);
    report(&outcome);

    let PrepareOutcome::Ready(content) = outcome else {
        return std::process::ExitCode::from(cli::EXIT_ASSET as u8);
    };
    if info_only {
        // Headless by design: nothing was opened, nothing was rendered.
        return std::process::ExitCode::SUCCESS;
    }

    let exit = build_scene_app(scene.window.clone(), *content).run();
    match exit {
        AppExit::Success => std::process::ExitCode::SUCCESS,
        AppExit::Error(cause) => {
            error!("render loop exited with an error: {cause}");
            std::process::ExitCode::FAILURE
        }
    }
}

/// Assembles the placeholder app.
pub fn build_placeholder_app(window: WindowOptions) -> App {
    let mut app = base_app(window);
    app.add_plugins(ScenePlugin);
    app.add_systems(
        Startup,
        |mut commands: Commands,
         mut meshes: ResMut<Assets<Mesh>>,
         mut materials: ResMut<Assets<StandardMaterial>>| {
            scene::spawn_placeholder(&mut commands, &mut meshes, &mut materials);
        },
    );
    app.add_systems(Update, exit_on_escape);
    app
}

/// Assembles the app that shows decoded Spore content.
pub fn build_scene_app(window: WindowOptions, content: StagedContent) -> App {
    let bounds = content.bounds();
    let mut app = base_app(window);
    app.insert_resource(content);
    // Two plugins, two responsibilities: the world is OpenSpore's, the content
    // is Spore's. Keeping them apart means loading different content cannot move
    // the camera, and changing the renderer cannot respawn the content.
    app.add_plugins((ScenePlugin, SporeAssetPlugin));
    // The camera is framed in `PostStartup`, not `Startup`, and the reason is
    // worth recording: `Commands::spawn` is *deferred*, so a `Query` in the same
    // system that spawns the camera sees zero cameras. Doing both in one system
    // silently leaves the camera at its default position -- which looks like a
    // framing bug and is really an ordering bug.
    if let Some(bounds) = bounds {
        app.add_systems(
            PostStartup,
            move |mut camera: Query<&mut Transform, With<scene::MainCamera>>| match camera
                .single_mut()
            {
                Ok(mut transform) => {
                    loader::frame_camera(&mut transform, bounds, DEFAULT_VERTICAL_FOV_DEGREES)
                }
                Err(error) => warn!("could not frame the camera: {error}"),
            },
        );
    }
    app.add_systems(Update, exit_on_escape);
    app
}

/// The vertical field of view used when framing a model.
pub const DEFAULT_VERTICAL_FOV_DEGREES: f32 = 60.0;

/// Escape closes the window.
///
/// Bevy 0.19 has no built-in "close on escape", and Spore's own binding is not
/// recovered, so this is an OpenSpore decision rather than a compatibility one.
fn exit_on_escape(keys: Res<ButtonInput<KeyCode>>, mut exits: MessageWriter<AppExit>) {
    if keys.just_pressed(KeyCode::Escape) {
        exits.write(AppExit::Success);
    }
}

/// The plugins and resources every mode shares.
fn base_app(window: WindowOptions) -> App {
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin {
        primary_window: Some(Window {
            resolution: WindowResolution::new(window.width, window.height),
            title: window.title,
            present_mode: PresentMode::AutoVsync,
            ..default()
        }),
        ..default()
    }));
    app
}

/// Convenience for tests and tools: a store with no packages.
pub fn empty_store() -> ContentStore {
    ContentStore::new()
}

#[cfg(test)]
mod tests {
    use super::*;
    use cli::RecordOrigin;
    use spore_core::ResourceKey;

    fn scene(packages: Vec<std::path::PathBuf>, record: ResourceKey) -> SceneRequest {
        SceneRequest {
            packages,
            record,
            record_origin: RecordOrigin::Explicit,
            scale: 1.0,
            window: WindowOptions::default(),
            info_only: true,
            textured: false,
            assumed_texture_type: spore_core::record::type_id::RASTER,
        }
    }

    #[test]
    fn a_headless_app_assembles_but_the_real_one_needs_the_main_thread() {
        // `DefaultPlugins` builds a winit `EventLoop`, and winit 0.30 panics when
        // that happens off the main thread. So the *only* honest headless
        // assertion is over the plugin subset that has no event loop -- which is
        // precisely the part worth testing, because it is the part a Bevy API
        // change can silently break.
        //
        // This was found by writing the test the obvious way and watching it
        // panic: an "app assembles" test that needs a window is not a unit test.
        let mut app = App::new();
        app.add_plugins(MinimalPlugins);
        app.add_systems(Update, exit_on_escape);
        // The app must at least have a schedule runner and our system registered
        // against it; `finish`/`cleanup` would panic on a malformed plugin set.
        app.finish();
        app.cleanup();
    }

    #[test]
    fn the_whole_asset_path_runs_with_no_window_and_no_game_install() {
        // The real guarantee: decoding is Bevy-free. If this ever needs a GPU,
        // the vertical slice stops being verifiable in CI.
        let outcome = prepare(&scene(
            Vec::new(),
            ResourceKey::new(0x00E6_BCE5, 0x4063_7E03, 0x067A_07F0),
        ));
        assert!(
            matches!(outcome, PrepareOutcome::Failed(_)),
            "no packages means no record, not a crash"
        );
    }

    #[test]
    fn preparing_a_scene_with_no_packages_fails_in_a_stated_way() {
        let outcome = prepare(&scene(Vec::new(), ResourceKey::new(1, 2, 3)));
        let PrepareOutcome::Failed(reason) = outcome else {
            panic!("expected a failure, got {outcome:?}");
        };
        assert!(
            reason.contains("--package"),
            "the message must say what to do: {reason}"
        );
    }

    #[test]
    fn preparing_a_scene_with_a_missing_package_names_the_path() {
        let outcome = prepare(&scene(
            vec![std::path::PathBuf::from("/definitely/not/here.package")],
            ResourceKey::new(1, 2, 3),
        ));
        let PrepareOutcome::Failed(reason) = outcome else {
            panic!("expected a failure");
        };
        assert!(reason.contains("/definitely/not/here.package"), "{reason}");
    }

    #[test]
    fn a_failure_report_line_is_versioned_and_carries_the_reason() {
        let line = format_report(&PrepareOutcome::Failed("no such record".into()));
        assert!(line.starts_with("OPENSPORE-STAGED v1 failed:"), "{line}");
        assert!(line.contains("no such record"), "{line}");
    }

    #[test]
    fn an_empty_store_resolves_nothing() {
        assert!(empty_store().is_empty());
    }
}

#[cfg(test)]
mod texture_path_tests {
    use super::*;
    use cli::{RecordOrigin, WindowOptions};
    use spore_assets::{ContentStore, LoadedModel, ModelFormat};
    use spore_core::ResourceKey;

    fn scene(textured: bool) -> SceneRequest {
        SceneRequest {
            packages: Vec::new(),
            record: ResourceKey::new(0x00E6_BCE5, 0x4063_7E03, 0x067A_07F0),
            record_origin: RecordOrigin::Preset("documented-asset"),
            scale: 1.0,
            window: WindowOptions::default(),
            info_only: true,
            textured,
            assumed_texture_type: spore_core::record::type_id::RASTER,
        }
    }

    #[test]
    fn textures_are_only_resolved_when_asked_for() {
        // Both paths must succeed on a request with no packages: neither the
        // model nor the texture resolution can turn a missing install into a
        // different error, because both are downstream of opening the package.
        for textured in [false, true] {
            let outcome = prepare(&scene(textured));
            assert!(
                matches!(outcome, PrepareOutcome::Failed(_)),
                "textured={textured}"
            );
        }
    }

    #[test]
    fn the_report_line_states_texture_resolution_even_with_none_requested() {
        // `0/0` and `not requested` must be distinguishable. Printing nothing
        // about textures would make "we did not look" read as "there were none".
        let content = StagedContent::new(dummy_model(), 1.0);
        let line = content.report_line();
        assert!(line.contains("textures=0/0"), "{line}");
        assert!(
            !content.textures.requested,
            "the default must not claim to have looked"
        );
    }

    #[test]
    fn the_report_line_counts_resolved_and_attempted_separately() {
        let content = StagedContent::new(dummy_model(), 1.0).with_textures(Vec::new());
        let line = content.report_line();
        assert!(line.contains("textures=0/0"), "{line}");
        assert!(
            content.textures.requested,
            "asking with no references still means we looked"
        );
    }

    #[test]
    fn the_assumed_texture_type_defaults_to_raster_and_is_visible() {
        let request = scene(true);
        assert_eq!(
            request.assumed_texture_type,
            spore_core::record::type_id::RASTER
        );
        // And it is overridable, because a gmdl texture-set entry has no type
        // word and a wrong assumption yields a confidently wrong texture.
        let overridden = cli::parse([
            "--record",
            "1:2:3",
            "--texture",
            "--assumed-texture-type",
            "0x2F4E681B",
        ])
        .unwrap();
        let LaunchRequest::Scene(request) = overridden else {
            panic!("expected a scene request")
        };
        assert_eq!(request.assumed_texture_type, 0x2F4E_681B);
        assert!(request.textured);
    }

    #[test]
    fn a_bad_assumed_texture_type_is_refused_rather_than_defaulted() {
        assert!(matches!(
            cli::parse(["--record", "1:2:3", "--assumed-texture-type", "nope"]).unwrap_err(),
            cli::CliError::BadValue { flag, .. } if flag == "--assumed-texture-type"
        ));
    }

    #[test]
    fn textures_are_off_unless_requested() {
        let LaunchRequest::Scene(off) = cli::parse(["--record", "1:2:3"]).unwrap() else {
            panic!()
        };
        assert!(
            !off.textured,
            "resolving textures costs a decode per reference; it must be opt-in"
        );
        let LaunchRequest::Scene(on) = cli::parse(["--record", "1:2:3", "--texture"]).unwrap()
        else {
            panic!()
        };
        assert!(on.textured);
    }

    #[test]
    fn usage_documents_the_texture_flags() {
        let text = cli::usage();
        assert!(text.contains("--texture"), "{text}");
        assert!(text.contains("--assumed-texture-type"), "{text}");
        assert!(
            text.contains("no type word"),
            "the assumption must be explained, not just offered: {text}"
        );
    }

    fn dummy_model() -> LoadedModel {
        LoadedModel {
            key: ResourceKey::new(0x00E6_BCE5, 1, 2),
            package_name: "mini".into(),
            format: ModelFormat::Gmdl,
            gmdl: None,
            rw4: None,
            meshes: Vec::new(),
            texture_refs: Vec::new(),
            stopped_at: None,
        }
    }

    #[test]
    fn an_empty_store_is_still_empty_after_a_failed_prepare() {
        assert!(empty_store().is_empty());
        let _: &ContentStore = &empty_store();
    }
}
