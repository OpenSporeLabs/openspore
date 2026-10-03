//! The `openspore` binary: a thin shim so the engine's logic stays in the
//! library where it can be tested.

fn main() -> std::process::ExitCode {
    spore_engine::main()
}
