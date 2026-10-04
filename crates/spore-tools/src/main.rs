//! `osptool`: a thin shim so every piece of the tool's logic stays in the
//! library, where it can be tested without a subprocess.
//!
//! The exit code is the library's decision. `main_with` maps a `ToolError` onto
//! the process exit code documented in [`spore_tools::usage`]; this file adds
//! nothing but the standard streams.

fn main() -> std::process::ExitCode {
    let args: Vec<String> = std::env::args().skip(1).collect();
    spore_tools::exit_code(
        args,
        &mut std::io::stdout().lock(),
        &mut std::io::stderr().lock(),
    )
}
