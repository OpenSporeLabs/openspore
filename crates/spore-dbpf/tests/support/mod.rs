//! Test-only support code, shared by the integration test binaries.
//!
//! A `tests/support/` directory is a module, not a test target, so everything
//! here is compiled into each `tests/*.rs` that declares `mod support;`.

pub mod qfs_encoder;
