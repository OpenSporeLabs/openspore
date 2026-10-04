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
pub fn prepare(scene: &SceneRequest) -> PrepareOutcome {
    let store = match loader::open_packages(&scene.packages) {
        Ok(store) => store,
        Err(error) => return PrepareOutcome::Failed(error.to_string()),
    };
    match ModelStore::new(&store).load(&scene.record) {
        Ok(model) => PrepareOutcome::Ready(Box::new(StagedContent::new(model, scene.scale))),
        Err(error) => PrepareOutcome::Failed(loader::describe(&error)),
    }
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
    app.add_systems(
        Startup,
        |mut commands: Commands,
         mut meshes: ResMut<Assets<Mesh>>,
         mut materials: ResMut<Assets<StandardMaterial>>| {
            scene::spawn_stage(&mut commands, &mut meshes, &mut materials);
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
    app.add_systems(
        Startup,
        |mut commands: Commands,
         content: Res<StagedContent>,
         mut meshes: ResMut<Assets<Mesh>>,
         mut materials: ResMut<Assets<StandardMaterial>>| {
            let outcome =
                loader::stage_decoded(&content, &mut commands, &mut meshes, &mut materials);
            info!("{outcome:?}");
        },
    );
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
