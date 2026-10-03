//! The DXT5-shaped 8-byte block codec.
//!
//! # What this codec is, and what it is not
//!
//! Spore's raster records store their mip chains as 8-byte blocks that are
//! *shaped* like BC3/DXT5 (two alpha endpoints, two colour endpoints, 16 two-bit
//! texel indices) but whose two endpoints are interpreted differently from the
//! published DXT5 specification. This module reproduces the Spore behaviour
//! byte-for-byte, because the Spore behaviour is what the game's pixels are.
//!
//! The authoritative sources, all of which agree with each other and with this
//! port:
//!
//! * `tools/spore/dxt5/dxt5.py` — the stdlib-only Python oracle;
//! * `src/assets/Dxt5.cpp` / `Dxt5.hpp` — the C++ reference ("must match the
//!   Python oracle byte-for-byte");
//! * `tests/test_textures.py::TestDxt5Synthetic` — hand-computed expected RGBA
//!   values for synthetic blocks, which pin the behaviour below.
//!
//! # Block layout (8 bytes)
//!
//! ```text
//! b[0]        alpha0   u8   first alpha endpoint
//! b[1]        alpha1   u8   second alpha endpoint
//! b[2], b[3]  colour   c0 = b[2] & 0x3F          (6 bits)
//!                       c1 = ((b[2] >> 6) & 0x3) | ((b[3] & 0xF) << 2)
//! b[4..8]     indices  16 two-bit texel codes, row-major left-to-right then
//!                       top-to-bottom; texel i uses byte `b[4 + i / 4]`, shift
//!                       `(i % 4) * 2`, low bit first
//! ```
//!
//! **One** two-bit code per texel drives *both* alpha and colour, exactly as in
//! the oracle. There is no separate alpha index and colour index.
//!
//! # DELIBERATE DEVIATION 1 — colour is inverted from the DXT5 specification
//!
//! The published BC3 rule is `c0 > c1 -> 4-colour palette, else 2 colours`
//! (with half-alpha sentinels in the 2-colour case). Spore's decoder uses the
//! **opposite** test:
//!
//! | condition | palette size | entries |
//! |---|---|---|
//! | `c0 > c1`  | 2 | `rgb5(c0)`, `rgb5(c1)` |
//! | `c0 <= c1` | 4 | `rgb5(c0)`, `rgb5(c1)`, `rgb5((2*c0+c1)/3)`, `rgb5((c0+c1)/2)` |
//!
//! and the channels are read **R5G5B5**, not R6G6B5: `r = (v >> 5) & 0x1F`,
//! `g = (v >> 10) & 0x1F`, `b = (v >> 15) & 0x1F`, each expanded 5 bits to 8 by
//! replication (`x << 3 | x >> 2`).
//!
//! Both halves of that deviation are load-bearing and both are *intended*: a
//! 6-bit input therefore yields **red in {0, 8} only**, with green and blue
//! pinned to 0. The Python oracle's docstring names the result — "the black/red
//! alpha-mask signature" — and it matches what the real records contain: every
//! DXT5 raster sampled in `docs/MATERIALS-DESIGN.md` §6 decodes to a black or
//! dark-red image whose alpha carries the shape. **Do not "fix" this to match
//! the published spec.** Doing so changes every pixel in the game.
//!
//! An index beyond the palette length clamps to `palette[0]` (the oracle's
//! `pal[v] if v < len(pal) else pal[0]`); it is a clamp, not an error and not a
//! wrap.
//!
//! # DELIBERATE DEVIATION 2 — there is no `alpha0 == alpha1` special case
//!
//! The published BC3 rule collapses the 8-value alpha palette when the two
//! endpoints are equal. Spore's decoder has **no such branch**: equal endpoints
//! simply fall through the unreversed path. The absence is reproduced and is
//! deliberate. Concretely, for `alpha0 == alpha1 == v` and a code of 0 or 3 the
//! oracle still yields exactly `v` (because `6v + 2v = 8v`), while codes 1 and 2
//! still yield the 0 and 255 sentinels — so a degenerate block is *not* made
//! constant, and adding the standard collapse would change codes 1 and 2.
//!
//! # DELIBERATE DEVIATION 3 — the endpoint codes are a 6/2 blend, not endpoints
//!
//! Codes 0 and 3 (the "endpoint" codes in the published spec) do not return
//! `alpha0` / `alpha1`. They return a blend, `6*small + 2*large` unreversed or
//! `6*large + 2*small` reversed, divided by 8. This is visible in the pinned
//! golden values: the block `[0, 255, ...]` in `tests/test_textures.py`
//! decodes code 0 to alpha 64 and code 3 to alpha 64, where the spec would give
//! 0 and 255.
//!
//! The division is **half-to-even**, matching Python's `round()` — the oracle
//! is Python and `(6*a + 2*b) / 8` is a float division there. Because the
//! numerator is always even, `num % 8` is one of `{0, 2, 4, 6}` and only the
//! `r == 4` case is a tie. Getting this wrong is a silent 1-LSB error on most
//! texels, so it is implemented and tested explicitly.

use crate::error::TextureError;
use crate::raster::MipImage;

/// Raw bytes in one 4x4 block. BC3's block size, and Spore's.
pub const BLOCK_BYTES: usize = 8;

/// Mip levels at or above this index are charged a single block.
///
/// The shift `w >> mip` is only defined for `mip < 32` in Rust, so every
/// mip at or beyond 32 is treated as 1x1 — which is one 4x4 block, i.e. one
/// 8-byte block. The reference implementations make the same cut.
pub const MIP_FLOOR: u32 = 32;

/// Width of the packed `c0`/`c1` pair, in bits.
const COLOUR_BITS: u32 = 6;

/// Mask for the low 6 bits of `b[2]`, which hold `c0`.
const COLOUR0_MASK: u32 = 0x3F;

/// `c0` is the low six bits of the packed colour word, so its mask is all ones
/// in those six bits and nothing above. Checked at compile time because the two
/// constants are the same fact written twice.
const _: () = assert!(COLOUR0_MASK == (1 << COLOUR_BITS) - 1);

/// Mask for the 2 bits of `c1` that live in `b[2]`'s top.
const COLOUR1_HIGH_MASK: u32 = 0x3;

/// Mask for the 4 bits of `c1` that live in the low nibble of `b[3]`.
const COLOUR1_LOW_MASK: u8 = 0x0F;

/// Shift applied to `b[3]`'s low nibble to place it above `b[2]`'s two bits.
const COLOUR1_LOW_SHIFT: u32 = 2;

/// Mask for one 5-bit colour channel.
const CHANNEL_MASK: u32 = 0x1F;

/// Shift of the red channel inside the packed colour word.
const CHANNEL_R_SHIFT: u32 = 5;

/// Shift of the green channel inside the packed colour word.
const CHANNEL_G_SHIFT: u32 = 10;

/// Shift of the blue channel inside the packed colour word.
const CHANNEL_B_SHIFT: u32 = 15;

/// Bytes per output texel: RGBA8.
const RGBA_BYTES: usize = 4;

/// Texels along one block edge.
const BLOCK_EDGE: u32 = 4;

/// Texels in one block.
const TEXELS_PER_BLOCK: usize = (BLOCK_EDGE * BLOCK_EDGE) as usize;

/// Texel index that selects the `0` sentinel.
const ALPHA_ZERO_CODE: u32 = 1;

/// Texel index that selects the `255` sentinel.
const ALPHA_ONE_CODE: u32 = 2;

/// Largest two-bit texel code.
const CODE_MASK: u32 = 0x3;

/// The heavier of the two alpha-ramp weights, 6.
///
/// It rides with `a0` when the ramp is unreversed and with `a1` when the
/// endpoints were swapped, which is the whole content of the `reversed` flag.
const RAMP_WEIGHT_SIX: u32 = 6;

/// The lighter of the two alpha-ramp weights, 2.
const RAMP_WEIGHT_TWO: u32 = 2;

/// Divisor of the alpha ramp, and therefore the denominator of every tie test.
const RAMP_DIVISOR: u32 = 8;

/// The one remainder that is a rounding tie (half-to-even).
///
/// `6*a + 2*b` is always even, so `num % 8 ∈ {0, 2, 4, 6}`; `4` is the only
/// value where `num / 8` lands exactly on `.5`.
const RAMP_TIE_REMAINDER: u32 = 4;

/// `ceil(n / 4)`, the block count along one axis.
fn ceil_div4(n: u32) -> u32 {
    n / 4 + if n % 4 != 0 { 1 } else { 0 }
}

/// Raw bytes of the mip chain for one mip level of a base size.
///
/// `mip 0` is the base level itself. Every mip at or beyond [`crate::MIP_FLOOR`] is
/// charged a single block, matching both reference implementations.
///
/// All arithmetic saturates: an absurd `width * height` yields [`usize::MAX`]
/// rather than a wrapped small number, which is what a caller must be able to
/// tell apart from "small texture".
pub fn dxt5_mip_size(width: u32, height: u32, mip: u32) -> usize {
    if mip >= MIP_FLOOR {
        return BLOCK_BYTES;
    }
    let w = (width >> mip).max(1);
    let h = (height >> mip).max(1);
    block_chain_bytes(w, h)
}

/// Raw bytes of the whole mip chain of one layer.
///
/// The sum is taken over `min(mip_count, 32)` mips and then charges
/// [`BLOCK_BYTES`] for **each mip beyond 32**.
///
/// That beyond-32 rule is a documented **approximation**, reproduced from the
/// references: it is not a claim about how Spore writes a 33rd mip (no record
/// has one — the largest observed chain is 10 mips), it is a bound that keeps
/// the shift well-defined and the arithmetic finite for a header that claims
/// an absurd mip count. Because `dxt5_mip_size` also charges one block for
/// every `mip >= 32`, this sum stays exactly equal to the sum of the individual
/// mip sizes, which is what makes the per-mip slice walk in
/// [`crate::decode_raster`] terminate at the record end.
///
/// Saturating, like [`dxt5_mip_size`].
pub fn dxt5_chain_size(width: u32, height: u32, mip_count: u32) -> usize {
    let bounded_mips = mip_count.min(MIP_FLOOR);
    let mut total = 0usize;
    for mip in 0..bounded_mips {
        total = total.saturating_add(dxt5_mip_size(width, height, mip));
    }
    if mip_count > bounded_mips {
        let extra_mips = (mip_count - bounded_mips) as usize;
        total = total.saturating_add(extra_mips.saturating_mul(BLOCK_BYTES));
    }
    total
}

/// Decodes one mip's raw block chain into row-major RGBA8.
///
/// `img` must hold at least `dxt5_mip_size(width, height, 0)` bytes; extra
/// trailing bytes are ignored, which is what lets a caller hand over the rest
/// of the record. `width`/`height` are the **mip's own** dimensions, not the
/// base level's.
///
/// Output is exactly `width * height * 4` bytes. Texels of a block that fall
/// outside those bounds are **skipped, not an error**: a 5x3 mip occupies two
/// blocks and the padding texels simply do not exist.
pub fn decode_dxt5_mip(img: &[u8], width: u32, height: u32) -> Result<MipImage, TextureError> {
    if width == 0 || height == 0 {
        return Err(TextureError::ZeroDimension { width, height });
    }

    let needed = dxt5_mip_size(width, height, 0);
    if needed == usize::MAX {
        return Err(TextureError::OutputTooLarge { width, height });
    }
    if img.len() < needed {
        return Err(TextureError::ShortBlockChain {
            available: img.len(),
            needed,
            width,
            height,
        });
    }

    let pixel_count = (width as usize).checked_mul(height as usize);
    let out_len = pixel_count.and_then(|count| count.checked_mul(RGBA_BYTES));
    // `Vec` cannot exceed `isize::MAX` bytes on any supported target, and a
    // request beyond that is a refusal rather than an abort.
    let out_len = match out_len {
        Some(len) if len <= isize::MAX as usize => len,
        _ => return Err(TextureError::OutputTooLarge { width, height }),
    };

    let mut pixels = vec![0u8; out_len];
    let blocks_wide = ceil_div4(width);

    // `block_row` / `block_col` are the *block* indices, so the byte offset of a
    // block is `(block_row * blocks_wide + block_col) * 8`. Iterating block
    // indices rather than texel indices is what makes the addressing correct
    // for widths that are not a multiple of 4: the row stride is in blocks,
    // never in texels.
    for block_row in 0..ceil_div4(height) {
        let row_top = block_row * BLOCK_EDGE;
        for block_col in 0..blocks_wide {
            let col_left = block_col * BLOCK_EDGE;
            let offset = ((block_row as usize) * (blocks_wide as usize) + (block_col as usize))
                * BLOCK_BYTES;
            let bytes = img.get(offset..offset + BLOCK_BYTES);
            write_block(&mut pixels, width, height, col_left, row_top, bytes)?;
        }
    }

    Ok(MipImage {
        width,
        height,
        pixels,
    })
}

/// Bytes one mip's blocks occupy, saturating.
fn block_chain_bytes(w: u32, h: u32) -> usize {
    let blocks = (ceil_div4(w) as usize).saturating_mul(ceil_div4(h) as usize);
    blocks.saturating_mul(BLOCK_BYTES)
}

/// Expands a 5-bit channel to 8 bits by bit replication: `v -> (v << 3) | (v >> 2)`.
///
/// Replication rather than scaling is what the oracle does, and the two are not
/// the same function: the obvious `v * 255 / 31` rounding differs at exactly four
/// of the 32 inputs (`3`, `7`, `24`, `28`), pinned by
/// `expand5_replicates_rather_than_scales`.
const fn expand5(v: u32) -> u8 {
    ((v << 3) | (v >> 2)) as u8
}

/// Reads the oracle's colour word: R5G5B5, **not** the spec's R6G6B5.
///
/// See the module documentation — this is deliberate deviation 1, and it is why
/// every decoded Spore DXT5 texel has red in `{0, 8}` and green/blue of 0.
const fn rgb5(v: u32) -> [u8; 3] {
    let r = (v >> CHANNEL_R_SHIFT) & CHANNEL_MASK;
    let g = (v >> CHANNEL_G_SHIFT) & CHANNEL_MASK;
    let b = (v >> CHANNEL_B_SHIFT) & CHANNEL_MASK;
    [expand5(r), expand5(g), expand5(b)]
}

/// The alpha value of one two-bit texel code.
///
/// See the module documentation for the two deviations this reproduces: there is
/// no `alpha0 == alpha1` collapse, and codes 0 and 3 return a 6/2 blend of the
/// endpoints rather than the endpoints themselves.
fn alpha_value(code: u32, small: u32, large: u32, reversed: bool) -> u8 {
    if code == ALPHA_ZERO_CODE {
        return 0;
    }
    if code == ALPHA_ONE_CODE {
        return 255;
    }
    // `6 * a0 + 2 * a1` unreversed; the swap is what `reversed` means, so the 6
    // follows whichever endpoint is now the large one. The golden block
    // `[255, 0, ...]` (reversed, 6 * 255 / 8 = 191.25 -> 191) pins this.
    let numerator = if reversed {
        RAMP_WEIGHT_SIX * large + RAMP_WEIGHT_TWO * small
    } else {
        RAMP_WEIGHT_SIX * small + RAMP_WEIGHT_TWO * large
    };
    let quotient = numerator / RAMP_DIVISOR;
    let remainder = numerator % RAMP_DIVISOR;
    let rounded = if remainder == RAMP_TIE_REMAINDER {
        // Half-to-even, exactly like Python's round(). Only this remainder is
        // a tie, so this is the only branch where the rounding mode is
        // observable.
        if quotient % 2 == 0 {
            quotient
        } else {
            quotient + 1
        }
    } else if remainder >= 6 {
        quotient + 1
    } else {
        quotient
    };
    // `numerator <= 6*255 + 2*255 = 2040`, so `rounded <= 255`.
    rounded as u8
}

/// Decodes one block and writes its texels that fall inside the image.
///
/// `bytes` is `Option<&[u8]>` rather than `&[u8]` so the caller can slice the
/// chain without indexing it first; `None` yields
/// [`TextureError::ShortBlockChain`] instead of a panic. The size check in
/// [`decode_dxt5_mip`] means that path is unreachable today, and it is kept so
/// that the block reader has no way to read out of bounds.
fn write_block(
    pixels: &mut [u8],
    width: u32,
    height: u32,
    col_left: u32,
    row_top: u32,
    bytes: Option<&[u8]>,
) -> Result<(), TextureError> {
    let short_chain = || TextureError::ShortBlockChain {
        available: bytes.map_or(0, <[u8]>::len),
        needed: BLOCK_BYTES,
        width,
        height,
    };
    let bytes = bytes.ok_or_else(short_chain)?;
    // Destructured by copy out of the slice; the `&` on the pattern is what
    // makes the bindings `u8` rather than `&u8`, and the length is what makes
    // the pattern total.
    let &[alpha0_raw, alpha1_raw, colour_lo, colour_hi, index0, index1, index2, index3] = bytes
    else {
        return Err(short_chain());
    };

    // Endpoints are ordered, never collapsed. The absence of an
    // `alpha0 == alpha1` branch is deliberate deviation 2.
    let (small, large, reversed) = if alpha0_raw > alpha1_raw {
        (alpha1_raw, alpha0_raw, true)
    } else {
        (alpha0_raw, alpha1_raw, false)
    };
    let small = u32::from(small);
    let large = u32::from(large);

    let colour0 = u32::from(colour_lo) & COLOUR0_MASK;
    let colour1 = (u32::from(colour_lo >> 6) & COLOUR1_HIGH_MASK)
        | ((u32::from(colour_hi & COLOUR1_LOW_MASK)) << COLOUR1_LOW_SHIFT);

    let palette = build_palette(colour0, colour1);

    // The 16 two-bit codes, unpacked in texel order. `chunks_exact_mut` keeps
    // this free of indexing: a bug cannot read a neighbouring block's bits.
    let mut codes = [0u32; TEXELS_PER_BLOCK];
    let index_bytes = [index0, index1, index2, index3];
    for (row, byte) in codes.chunks_exact_mut(4).zip(index_bytes) {
        for (cell, position) in row.iter_mut().zip(0u32..) {
            *cell = (u32::from(byte) >> slot_shift(position)) & CODE_MASK;
        }
    }

    // Walk the block's own texels in image order, skipping anything past the
    // right or bottom edge: a 5x3 mip's second block contributes one column of
    // three, not sixteen.
    let mut row_y = row_top;
    for row in codes.chunks_exact(4) {
        for (col, code) in row.iter().copied().enumerate() {
            let texel_x = col_left + col as u32;
            if row_y < height && texel_x < width {
                let pixel = (row_y as usize) * (width as usize) + (texel_x as usize);
                let colour = palette_colour(&palette, code);
                let alpha = alpha_value(code, small, large, reversed);
                // `decode_dxt5_mip` sized the buffer as exactly
                // `width * height * RGBA_BYTES` from these same three values, so
                // the destination is in bounds by construction; the `None` arm is
                // a typed refusal, never a panic, so no arithmetic slip here can
                // become an out-of-bounds write.
                let destination = pixels
                    .get_mut(pixel * RGBA_BYTES..pixel * RGBA_BYTES + RGBA_BYTES)
                    .ok_or(TextureError::OutputInvariant {
                        width,
                        height,
                        texel_x,
                        texel_y: row_y,
                    })?;
                for (slot, value) in destination
                    .iter_mut()
                    .zip([colour[0], colour[1], colour[2], alpha])
                {
                    *slot = value;
                }
            }
        }
        row_y = row_y.saturating_add(1);
    }

    Ok(())
}

/// Bit shift of the `slot`-th code within one index byte.
///
/// The four codes of a byte are packed least-significant-first, so slot `n`
/// sits at bit `2 * n`.
const fn slot_shift(slot: u32) -> u32 {
    (slot % 4) * 2
}

/// The block's colour palette, pre-clamped.
///
/// Slots at or beyond the palette length are filled with slot 0, which is how
/// the oracle's `pal[v] if v < len(pal) else pal[0]` clamp is expressed here:
/// an out-of-range index then resolves through the ordinary lookup instead of
/// needing a bounds decision on every texel.
fn build_palette(colour0: u32, colour1: u32) -> [[u8; 3]; 4] {
    // DELIBERATE DEVIATION 1: the `>` test is inverted relative to the DXT5
    // specification, and the channels are R5G5B5 rather than R6G6B5.
    if colour0 > colour1 {
        // Two colours. The remaining two slots are filled with slot 0 so that
        // an out-of-range index clamps instead of reading an unrelated entry.
        let first = rgb5(colour0);
        [first, rgb5(colour1), first, first]
    } else {
        // Four colours, all slots real. The `2/3` and `1/2` blends use
        // truncating integer division, as the oracle's `//` does.
        [
            rgb5(colour0),
            rgb5(colour1),
            rgb5((2 * colour0 + colour1) / 3),
            rgb5((colour0 + colour1) / 2),
        ]
    }
}

/// Resolves a two-bit code to a colour, clamping out-of-range codes to slot 0.
///
/// The clamped palette means `get` never actually returns `None` for a
/// two-bit code; the fallback exists so this function cannot panic if the
/// palette representation ever changes.
fn palette_colour(palette: &[[u8; 3]; 4], code: u32) -> [u8; 3] {
    match palette.get(code as usize) {
        Some(colour) => *colour,
        None => palette[0],
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn rgb5_is_r5g5b5_not_r6g6b5() {
        // A 6-bit input can only set bit 5, which is the red channel's LSB.
        // That is the black/red signature the oracle's docstring names.
        assert_eq!(rgb5(0), [0, 0, 0]);
        assert_eq!(rgb5(31), [0, 0, 0]);
        assert_eq!(rgb5(32), [8, 0, 0]);
        assert_eq!(rgb5(63), [8, 0, 0]);
        for value in 0..64u32 {
            let [r, g, b] = rgb5(value);
            assert!(g == 0 && b == 0, "value {value} gave green/blue {g}/{b}");
            assert!(r == 0 || r == 8, "value {value} gave red {r}");
        }
    }

    #[test]
    fn expand5_replicates_rather_than_scales() {
        // (v << 3) | (v >> 2), the oracle's exact expansion. It is NOT the same
        // function as the more obvious `v * 255 / 31` rounding: the two differ at
        // exactly four of the 32 inputs, and the oracle's formula is the
        // contract. The differing set is enumerated exhaustively below, so a
        // change to either function that moves a boundary shows up here.
        assert_eq!(expand5(0), 0);
        assert_eq!(expand5(1), 8);
        assert_eq!(expand5(31), 255);
        let differing: Vec<u32> = (0..32)
            .filter(|&v| u32::from(expand5(v)) != ((v * 255) + 15) / 31)
            .collect();
        assert_eq!(differing, [3, 7, 24, 28]);
        assert_eq!(expand5(3), 24, "a scaling expansion would give 25");
        assert_eq!(expand5(7), 57, "a scaling expansion would give 58");
        assert_eq!(expand5(24), 198, "a scaling expansion would give 197");
        assert_eq!(expand5(28), 231, "a scaling expansion would give 230");
    }

    #[test]
    fn alpha_ramp_is_half_to_even_at_the_tie() {
        // unreversed: numerator is 6*small + 2*large.
        // 6*0 + 2*2 = 4 -> 0.5 -> ties to even -> 0.
        assert_eq!(alpha_value(0, 0, 2, false), 0);
        // 6*5 + 2*3 = 36 -> 4.5 -> ties to even -> 4 (NOT 5).
        assert_eq!(alpha_value(0, 5, 3, false), 4);
        // 6*1 + 2*3 = 12 -> 1.5 -> ties to even -> 2.
        assert_eq!(alpha_value(3, 1, 3, false), 2);
        // reversed: numerator is 6*large + 2*small.
        // 6*2 + 2*0 = 12 -> 1.5 -> 2.
        assert_eq!(alpha_value(0, 0, 2, true), 2);
        // 6*3 + 2*1 = 20 -> 2.5 -> ties to even -> 2.
        assert_eq!(alpha_value(3, 1, 3, true), 2);
        // Sentinels bypass the ramp entirely.
        assert_eq!(alpha_value(1, 0, 0, false), 0);
        assert_eq!(alpha_value(2, 0, 0, false), 255);
    }

    /// An independently written reference for the ramp, checked against
    /// [`alpha_value`] for **every** endpoint pair in both directions.
    ///
    /// The reference rounds by comparing the *doubled* remainder with 8 rather
    /// than by testing `remainder == 4`, so the two implementations agree by
    /// construction of different arithmetic, not by sharing a branch. This is the
    /// test that would catch a rounding change on a single endpoint pair out of
    /// 65 536.
    fn reference_alpha(code: u32, small: u32, large: u32, reversed: bool) -> u8 {
        if code == 1 {
            return 0;
        }
        if code == 2 {
            return 255;
        }
        let numerator = if reversed {
            6 * large + 2 * small
        } else {
            6 * small + 2 * large
        };
        let quotient = numerator / 8;
        let doubled_remainder = 2 * (numerator % 8);
        let rounded = match doubled_remainder.cmp(&8) {
            core::cmp::Ordering::Less => quotient,
            core::cmp::Ordering::Greater => quotient + 1,
            // A tie: round to the even neighbour.
            core::cmp::Ordering::Equal if quotient % 2 == 0 => quotient,
            core::cmp::Ordering::Equal => quotient + 1,
        };
        // The ramp's numerator is at most `6*255 + 2*255 = 2040`, so the rounded
        // value is at most 255 and the truncation below is exact.
        rounded as u8
    }

    #[test]
    fn the_alpha_ramp_matches_an_independent_formula_exhaustively() {
        for small in 0..=255u32 {
            for large in 0..=255u32 {
                for reversed in [false, true] {
                    for code in [0u32, 3] {
                        assert_eq!(
                            alpha_value(code, small, large, reversed),
                            reference_alpha(code, small, large, reversed),
                            "code {code}, small {small}, large {large}, reversed {reversed}"
                        );
                    }
                    // The sentinels never consult the ramp.
                    assert_eq!(alpha_value(1, small, large, reversed), 0);
                    assert_eq!(alpha_value(2, small, large, reversed), 255);
                }
            }
        }
    }

    #[test]
    fn palette_branch_is_inverted_from_the_spec() {
        // c0 > c1 must yield TWO colours in Spore's decoder; the DXT5 spec says
        // four here. The clamp fills the unused slots with slot 0.
        let two = build_palette(32, 0);
        assert_eq!(two[0], [8, 0, 0]);
        assert_eq!(two[1], [0, 0, 0]);
        assert_eq!(two[2], two[0], "clamp target");
        assert_eq!(two[3], two[0], "clamp target");

        // c0 <= c1 must yield FOUR colours.
        let four = build_palette(0, 32);
        assert_eq!(four[0], [0, 0, 0]);
        assert_eq!(four[1], [8, 0, 0]);
        assert_eq!(four[2], rgb5(32 / 3));
        assert_eq!(four[3], rgb5(16));
    }

    #[test]
    fn palette_lookup_clamps_instead_of_panicking() {
        // A 2-colour palette plus codes 2 and 3 must resolve to slot 0, which
        // is what the oracle's `pal[v] if v < len(pal) else pal[0]` does.
        let palette = build_palette(32, 0);
        for code in 2..=3u32 {
            assert_eq!(palette_colour(&palette, code), palette[0]);
        }
    }

    #[test]
    fn ceil_div4_rounds_up() {
        assert_eq!(ceil_div4(0), 0);
        assert_eq!(ceil_div4(1), 1);
        assert_eq!(ceil_div4(4), 1);
        assert_eq!(ceil_div4(5), 2);
        assert_eq!(ceil_div4(u32::MAX), 1 << 30);
    }

    #[test]
    fn a_missing_block_is_an_error_and_not_a_panic() {
        // The defensive arm of `write_block`, which `decode_dxt5_mip`'s size
        // check makes unreachable from the public API.
        let mut pixels = [0u8; 4 * 4];
        let result = write_block(&mut pixels, 4, 4, 0, 0, None);
        assert!(matches!(
            result,
            Err(TextureError::ShortBlockChain { needed: 8, .. })
        ));
        let result = write_block(&mut pixels, 4, 4, 0, 0, Some(&[0u8; 7]));
        assert!(matches!(
            result,
            Err(TextureError::ShortBlockChain { needed: 8, .. })
        ));
    }
}
