//! Typed failures of the raster walk.
//!
//! One variant per failure mode, on purpose. "The texture did not load" throws
//! away the only thing a caller can act on: a record truncated mid-envelope, a
//! record whose `fourcc` is a format this crate deliberately does not decode,
//! and a record whose layer split does not divide are three different problems
//! with three different responses (skip the asset, extend the codec, fix the
//! split rule). Each variant therefore names the section and carries the
//! numbers needed to identify the record in a report.
//!
//! The `texture:` / `dxt5:` prefixes mirror the two reference
//! implementations — `tools/spore/raster/raster.py` and `tools/spore/dxt5/dxt5.py`
//! — so a message can be traced back to the oracle that produced it.
//!
//! Nothing here is ever inferred: no variant reports a value this build guessed.

use thiserror::Error;

use crate::{DXT5_FOURCC, ENVELOPE_SIZE};

/// Every way decoding a Spore raster texture record can fail.
///
/// `decode_raster` never publishes a partially populated [`crate::RasterImage`]:
/// an `Err` means nothing was returned. The variants are ordered to follow the
/// order the walk can produce them.
#[derive(Debug, Clone, PartialEq, Eq, Error)]
pub enum TextureError {
    // ---- envelope ------------------------------------------------------
    /// Fewer than [`ENVELOPE_SIZE`] bytes: not even the envelope fits.
    ///
    /// A raster record is never empty and is never shorter than its own
    /// header, so there is no "zero-length means default" reading to fall back
    /// to.
    #[error("texture: {available} bytes < the {ENVELOPE_SIZE}-byte raster envelope")]
    TruncatedEnvelope {
        /// Bytes actually available.
        available: usize,
    },

    /// The envelope's `fourcc` is not `DXT5`.
    ///
    /// The `0x15xx` family is luminance, not BC3: it is a *different* format,
    /// not an unrecognised one, and this build has no decoder for it (see
    /// `docs/MATERIALS-DESIGN.md` §1). It is rejected by name rather than fed
    /// to the block codec, which would produce plausible-looking garbage.
    #[error(
        "texture: unsupported fourcc 0x{fourcc:08X} (want 0x{DXT5_FOURCC:08X} = 'DXT5'; \
         the 0x15xx luminance family is a different format and is out of scope)"
    )]
    UnsupportedFourcc {
        /// The `fourcc` word as read from the envelope.
        fourcc: u32,
    },

    /// `width` or `height` is zero.
    ///
    /// No observed record does this. The Python oracle does not check it either
    /// and would return an empty image for such a record; the C++ reference
    /// rejects it and so does this port, because an image with no texels has no
    /// meaning to propagate to a renderer.
    #[error("texture: zero-sized image (width={width}, height={height})")]
    ZeroDimension {
        /// Envelope width.
        width: u32,
        /// Envelope height.
        height: u32,
    },

    /// `mip_count` is zero, so the record has no base level.
    ///
    /// A chain of zero mips has a zero-length payload, which would make the
    /// layer split degenerate into "16 bytes per layer" and quietly accept a
    /// record whose real content is something else.
    #[error("texture: mipCount is 0 (a raster record always has a base level)")]
    ZeroMipCount,

    /// The record handed to [`crate::layer_count_for`] is smaller than the
    /// envelope, so there is nothing to split.
    #[error(
        "texture: record of {record_size} bytes is smaller than the {ENVELOPE_SIZE}-byte envelope"
    )]
    RecordShorterThanEnvelope {
        /// The record size that was offered.
        record_size: usize,
    },

    /// The mip chain of one layer does not fit in an addressable `usize`.
    ///
    /// Portability note: with `u32` arguments this arm is **unreachable on a
    /// 64-bit target**, because the largest chain the sizing rules can produce is
    /// `12_297_829_382_473_034_416`, comfortably below `usize::MAX`
    /// (`18_446_744_073_709_551_615`); such an envelope is refused one line later
    /// by [`TextureError::PayloadTooSmall`], naming the impossible stride. On a
    /// 32-bit target the same call *does* saturate, because every one of those
    /// mip terms is larger than a `u32`. The arm is kept for that target and as
    /// the bound on the saturating arithmetic, exactly as the C++ reference keeps
    /// its own `SIZE_MAX` check.
    #[error(
        "texture: layer chain exceeds the addressable size \
         (width={width}, height={height}, mip_count={mip_count})"
    )]
    ChainSizeOverflow {
        /// Envelope width.
        width: u32,
        /// Envelope height.
        height: u32,
        /// Envelope mip count.
        mip_count: u32,
    },

    // ---- layer split ---------------------------------------------------
    /// Fewer payload bytes than one layer needs.
    ///
    /// `available` is `record_size - 32`; `needed` is
    /// `16 + chain_size(width, height, mip_count)`.
    #[error("texture: {available} payload bytes < {needed} for one layer")]
    PayloadTooSmall {
        /// Payload bytes present after the envelope.
        available: usize,
        /// Bytes one layer occupies (16-byte header plus the mip chain).
        needed: usize,
    },

    /// The payload does not divide evenly by the layer stride.
    ///
    /// The layer count is **derived**, never read from a header field, so a
    /// remainder is a hard contradiction rather than something to round. This
    /// is the check that catches a wrong split rule.
    #[error("texture: {available} payload bytes is not a multiple of the {per}-byte layer stride")]
    PayloadNotMultiple {
        /// Payload bytes present after the envelope.
        available: usize,
        /// Bytes one layer occupies.
        per: usize,
    },

    /// A layer's mip slice runs past the end of the record.
    ///
    /// **Currently unreachable through [`crate::decode_raster`]**, and that is
    /// a property worth stating rather than hiding: the derived split guarantees
    /// each layer holds exactly `chain_size` bytes, which is the sum of its
    /// mip sizes, so every slice fits by construction. The check is kept
    /// because it is the bound on the assumption — if the split rule, the
    /// "all headers first" layout or the beyond-32-mip approximation ever
    /// changes, this is the arm that notices. `tests/raster.rs` exercises the
    /// branch directly through the private helper that owns it.
    #[error(
        "texture: layer {layer} mip {mip} needs {size} bytes at offset {offset}, \
         but the record is {record_size} bytes"
    )]
    MipSlicePastRecord {
        /// Layer index the slice belongs to.
        layer: usize,
        /// Mip index within the layer.
        mip: u32,
        /// Byte offset the slice starts at.
        offset: usize,
        /// Bytes the slice needs.
        size: usize,
        /// Bytes in the record.
        record_size: usize,
    },

    // ---- block codec ---------------------------------------------------
    /// The block chain is shorter than the mip's own geometry requires.
    ///
    /// `needed` is `ceil4(w) * ceil4(h) * 8` for the mip's dimensions.
    #[error("dxt5: block chain of {available} bytes < {needed} for {width}x{height}")]
    ShortBlockChain {
        /// Block bytes available.
        available: usize,
        /// Block bytes the mip's dimensions require.
        needed: usize,
        /// Mip width.
        width: u32,
        /// Mip height.
        height: u32,
    },

    /// The requested mip is too large to address, let alone allocate.
    ///
    /// Two distinct bounds, reported as one variant because neither describes a
    /// real record: the `w * h * 4` product must not overflow, and the output
    /// buffer must fit inside `isize::MAX` bytes, which no `Vec` allocation can
    /// exceed on any supported target. The C++ reference checks only the
    /// overflow and would abort the process on a failed allocation; this port
    /// reports the second condition as a typed error instead.
    ///
    /// Reachability, stated plainly: on a 64-bit target **no** `u32` input
    /// reaches either arm — the chain size saturates only where `usize` is 32
    /// bits, and a `w * h * 4` product above `isize::MAX` would first need a
    /// chain longer than `2^60` bytes to get past the length check. Such a call
    /// is refused one line earlier by [`TextureError::ShortBlockChain`], which
    /// names the impossible stride. This variant is the guard against a failed
    /// allocation on an adversarial envelope, written and kept so that widening
    /// the input types later cannot turn an abort into a crash; its message is
    /// pinned by the message test in `tests/dxt5_golden.rs`.
    #[error("dxt5: {width}x{height} exceeds the addressable output size")]
    OutputTooLarge {
        /// Requested width.
        width: u32,
        /// Requested height.
        height: u32,
    },

    /// The destination buffer was not the size the mip's geometry requires.
    ///
    /// **Unreachable through the public API**: the decoder sizes its output as
    /// exactly `width * height * 4` from the same `width`/`height` it then
    /// indexes with, so the destination of every texel write is in bounds by
    /// construction. The variant exists so that the block writer has no path
    /// that can index out of bounds: an arithmetic slip becomes a typed error
    /// rather than a panic or, worse, a write into the wrong memory.
    #[error("dxt5: internal output-size invariant failed at texel ({texel_x}, {texel_y}) of {width}x{height}")]
    OutputInvariant {
        /// Requested width.
        width: u32,
        /// Requested height.
        height: u32,
        /// Texel column the write targeted.
        texel_x: u32,
        /// Texel row the write targeted.
        texel_y: u32,
    },
}
