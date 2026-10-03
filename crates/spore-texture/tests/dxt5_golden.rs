//! Block-decode golden tests, sizing goldens, and the codec's edge cases.
//!
//! The expected RGBA values in this file are transcribed **verbatim** from
//! `tests/test_textures.py::TestDxt5Synthetic`, where they are hand-computed,
//! and they were cross-checked there against `tools/spore/dxt5/dxt5.py`. Every
//! one of them is a 4-byte `(R, G, B, A)` tuple in the Python source and a hex
//! string here; where this file says a value, the Python test says the same
//! value for the same block.
//!
//! Where an expected value is *not* from that file it is marked as such, and it
//! was produced by running `tools/spore/dxt5/dxt5.py` over the identical block
//! (recorded in the comment beside it).

mod common;

use common::*;
use spore_texture::{decode_dxt5_mip, dxt5_chain_size, dxt5_mip_size, TextureError, BLOCK_BYTES};

// ---------------------------------------------------------------------------
// 1. Block-decode golden tests
// ---------------------------------------------------------------------------

/// `tests/test_textures.py::test_block_two_color_full_alpha`.
///
/// Block `[255, 0, 0x20, 0x00, 0, 0, 0, 0]` at 4x4: every one of the sixteen
/// texels is `(8, 0, 0, 191)`.
///
/// - `a0=255 > a1=0`, so the endpoints swap and the ramp is reversed;
/// - `c0 = 0x20 & 0x3F = 32`, `c1 = 0x00`, and `c0 > c1` selects the **two**
///   colour palette `[rgb5(32), rgb5(0)]` — note this is inverted from the
///   published DXT5 specification, which would pick four colours here;
/// - `rgb5(32)` is `(8, 0, 0)`: the R5G5B5 read takes red from bit 5, so a
///   6-bit input can only ever give red 0 or 8 and green/blue 0;
/// - every index bit is 0, so the colour is `palette[0]` and the alpha is the
///   reversed ramp `round(6*255/8) = round(191.25) = 191`.
#[test]
fn golden_two_colour_full_alpha_matches_the_hand_computed_oracle() {
    let image = decode_dxt5_mip(&TWO_COLOUR_FULL_ALPHA, 4, 4).expect("a whole block decodes");
    assert_eq!(image.width, 4);
    assert_eq!(image.height, 4);
    assert_eq!(image.pixels.len(), 4 * 4 * 4);
    assert_eq!(image.pixels, [[8u8, 0, 0, 191]; 16].concat());
    for texel in 0..16 {
        let texel_rgba = &image.pixels[texel * 4..texel * 4 + 4];
        assert_eq!(texel_rgba, [8, 0, 0, 191], "texel {texel}");
    }
}

/// `tests/test_textures.py::test_block_four_color_alpha_ramp`.
///
/// Block `[0, 255, 0x00, 0x08, 0xE4, 0xE4, 0xE4, 0xE4]` at 4x4: each row is
/// `(0,0,0,64)`, `(8,0,0,0)`, `(0,0,0,255)`, `(0,0,0,64)`, four rows over.
///
/// - `a0=0 < a1=255`, unreversed, so the ramp is `6*small + 2*large`;
/// - `c0=0`, `c1=0x08<<2 = 32`, and `c0 <= c1` selects the **four** colour
///   palette `(0,0,0)/(8,0,0)/(0,0,0)/(0,0,0)` — the two blends
///   `(2*0+32)/3 = 10` and `(0+32)/2 = 16` both read as `(0,0,0)` under the
///   R5G5B5 layout;
/// - `0xE4 = 0b11_10_01_00` reads as codes 0,1,2,3 across each byte;
/// - the alpha values are `round(2*255/8) = 64` for code 0, `0` for code 1,
///   `255` for code 2 and `64` again for code 3 — code 0 is *not* `a0` and code 3
///   is *not* `a1`, which is the third deliberate deviation.
#[test]
fn golden_four_colour_alpha_ramp_matches_the_hand_computed_oracle() {
    let image = decode_dxt5_mip(&FOUR_COLOUR_ALPHA_RAMP, 4, 4).expect("a whole block decodes");
    assert_eq!(image.pixels, expected_four_colour_ramp());
    let per_texel: Vec<[u8; 4]> = image
        .pixels
        .chunks_exact(4)
        .map(<[u8; 4]>::try_from)
        .collect::<Result<_, _>>()
        .expect("whole texels");
    assert_eq!(per_texel.len(), 16);
    // The Python test asserts exactly this four-element cycle, twice per row.
    let cycle = [[0u8, 0, 0, 64], [8, 0, 0, 0], [0, 0, 0, 255], [0, 0, 0, 64]];
    for texel in 0..16 {
        assert_eq!(per_texel[texel], cycle[texel % 4], "texel {texel}");
    }
}

/// `tests/test_textures.py::test_tail_clamp`.
///
/// Block `[255, 0, 0x3F, 0x0F, 0, 0, 0, 0]` repeated four times over a 6x6
/// image. Two of the four blocks hang off the right and bottom edges; their
/// padding texels must be skipped rather than written, so the output is exactly
/// `6 * 6 * 4 = 144` bytes and texel 0 is `(8, 0, 0, 191)`.
///
/// The block's `c0 = 0x3F` and `c1 = 0x0F<<2 = 60` both read as `(8,0,0)`, so
/// the two-colour palette is uniform; the alpha comes from the reversed ramp.
#[test]
fn golden_tail_clamp_skips_padding_texels_in_a_6x6_image() {
    let chain: Vec<u8> = TAIL_CLAMP.repeat(4);
    let image = decode_dxt5_mip(&chain, 6, 6).expect("four blocks cover a 6x6 mip");
    assert_eq!(image.width, 6);
    assert_eq!(image.height, 6);
    assert_eq!(image.pixels.len(), 6 * 6 * 4);
    assert_eq!(image.pixels, [[8u8, 0, 0, 191]; 36].concat());
    assert_eq!(&image.pixels[0..4], &[8, 0, 0, 191], "texel 0");
}

// ---------------------------------------------------------------------------
// 2. chain_size golden integers
// ---------------------------------------------------------------------------

/// `tests/test_textures.py::test_chain_size`.
///
/// The four asserted values are copied exactly, including the arithmetic the
/// Python test spells out:
///
/// | input | expected | decomposition |
/// |---|---|---|
/// | `(512, 512, 10)` | `174776` | the real 512² record's ten mip levels |
/// | `(1, 1, 1)` | `8` | one block |
/// | `(64, 1, 4)` | `128 + 64 + 32 + 16 = 240` | mips 64,32,16,8 wide -> 16,8,4,2 blocks |
/// | `(10, 10, 4)` | `3*3*8 + 2*2*8 + 8 + 8 = 120` | block counts 3x3, 2x2, 1x1, 1x1 |
#[test]
fn chain_size_matches_the_golden_integers() {
    assert_eq!(dxt5_chain_size(512, 512, 10), 174776);
    assert_eq!(dxt5_chain_size(1, 1, 1), 8);
    assert_eq!(dxt5_chain_size(64, 1, 4), 128 + 64 + 32 + 16);
    assert_eq!(dxt5_chain_size(64, 1, 4), 240);
    assert_eq!(dxt5_chain_size(10, 10, 4), 3 * 3 * 8 + 2 * 2 * 8 + 8 + 8);
    assert_eq!(dxt5_chain_size(10, 10, 4), 120);
}

/// The chain is exactly the sum of its mips, which is what lets the raster walk
/// stop a layer's slices exactly at the next layer's first byte.
#[test]
fn a_chain_is_exactly_the_sum_of_its_mips() {
    for &(width, height, mips) in &[
        (512u32, 512u32, 10u32),
        (8, 8, 2),
        (10, 10, 4),
        (64, 1, 4),
        (5, 3, 3),
        (1, 1, 1),
    ] {
        let sum: usize = (0..mips).map(|m| dxt5_mip_size(width, height, m)).sum();
        assert_eq!(
            dxt5_chain_size(width, height, mips),
            sum,
            "{width}x{height}x{mips}"
        );
    }
}

/// `dxt5_mip_size` is the per-mip rule, including the `mip >= 32` floor.
#[test]
fn mip_sizes_follow_the_block_geometry() {
    assert_eq!(dxt5_mip_size(512, 512, 0), 128 * 128 * 8);
    assert_eq!(dxt5_mip_size(512, 512, 1), 64 * 64 * 8);
    assert_eq!(dxt5_mip_size(1, 1, 0), BLOCK_BYTES);
    assert_eq!(dxt5_mip_size(4, 4, 0), BLOCK_BYTES);
    assert_eq!(
        dxt5_mip_size(5, 3, 0),
        2 * BLOCK_BYTES,
        "ceil4(5) x ceil4(3)"
    );
    assert_eq!(dxt5_mip_size(8, 8, 1), BLOCK_BYTES, "4x4 is one block");
    assert_eq!(
        dxt5_mip_size(3, 3, 1),
        BLOCK_BYTES,
        "max(1, 3 >> 1) is one block"
    );
    // At or beyond 32 every mip is charged one block, because `w >> mip` is not
    // defined and `max(1, ...)` would be 1 anyway.
    assert_eq!(dxt5_mip_size(512, 512, 31), BLOCK_BYTES);
    assert_eq!(dxt5_mip_size(512, 512, 32), BLOCK_BYTES);
    assert_eq!(dxt5_mip_size(512, 512, 64), BLOCK_BYTES);
}

// ---------------------------------------------------------------------------
// 3. Alpha tie rounding (half-to-even)
// ---------------------------------------------------------------------------

/// One texel of a block whose every code is `code`.
fn ramp_texel(alpha0: u8, alpha1: u8, code: u8) -> u8 {
    let block = block(alpha0, alpha1, 0x20, 0x00, [code; 16]);
    let image = decode_dxt5_mip(&block, 4, 4).expect("one whole block decodes");
    let alpha = image.pixels[3];
    // Every texel of these blocks carries the same alpha; assert that first so
    // a failure cannot be a single stray texel.
    for texel in 0..16 {
        assert_eq!(image.pixels[texel * 4 + 3], alpha, "texel {texel}");
    }
    alpha
}

/// The alpha ramp divides by 8 with **half-to-even** rounding, matching Python's
/// `round()` — the oracle computes `(6*a + 2*b) / 8` as a float.
///
/// The numerator `6*small + 2*large` is always even, so `num % 8` is one of
/// `{0, 2, 4, 6}` and only `4` is a tie. Each case below is a hand-picked tie:
///
/// | endpoints | direction | numerator | value | tie | result |
/// |---|---|---|---|---|---|
/// | `a0=0, a1=2` | unreversed | `6*0 + 2*2 = 4` | `0.5` | 0.5 -> 0 | **0** |
/// | `a0=5, a1=3` | unreversed | `6*5 + 2*3 = 36` | `4.5` | 4.5 -> 4 | **4** |
/// | `a0=2, a1=0` | reversed | `6*2 + 2*0 = 12` | `1.5` | 1.5 -> 2 | **2** |
/// | `a0=3, a1=1` | reversed | `6*3 + 2*1 = 20` | `2.5` | 2.5 -> 2 | **2** |
///
/// Note `4.5 -> 4`, not 5: a round-half-up implementation passes every non-tie
/// texel and fails exactly here. `0.5 -> 0` likewise fails a round-half-up.
#[test]
fn alpha_ties_round_half_to_even() {
    // Unreversed: `6 * a0 + 2 * a1`.
    assert_eq!(ramp_texel(0, 2, 0), 0, "0.5 ties down to even 0");
    assert_eq!(ramp_texel(5, 3, 0), 4, "4.5 ties down to even 4, not 5");
    // Reversed: `6 * a1 + 2 * a0`, because the endpoints were swapped.
    assert_eq!(ramp_texel(2, 0, 0), 2, "1.5 ties up to even 2");
    assert_eq!(ramp_texel(3, 1, 0), 2, "2.5 ties down to even 2");
}

/// The non-tie remainders round the ordinary way, so a tie-only bug cannot hide
/// behind them: `10/8 = 1.25 -> 1` (remainder 2) and `14/8 = 1.75 -> 2`
/// (remainder 6, which rounds up).
#[test]
fn alpha_non_ties_round_the_ordinary_way() {
    assert_eq!(ramp_texel(1, 2, 0), 1, "1.25 rounds down");
    assert_eq!(ramp_texel(1, 4, 0), 2, "1.75 rounds up");
    assert_eq!(ramp_texel(0, 1, 0), 0, "0.125 rounds down");
    assert_eq!(ramp_texel(1, 0, 0), 1, "0.75 rounds up");
}

/// Codes 0 and 3 take the same ramp value, and codes 1 and 2 are the sentinels.
///
/// `6*5 + 2*3 = 36 -> 4` for both code 0 and code 3 is the visible proof of the
/// third deliberate deviation: in the published specification these two codes
/// return the endpoints themselves, which here would be 5 and 3.
#[test]
fn alpha_codes_zero_and_three_share_the_ramp_value() {
    assert_eq!(ramp_texel(5, 3, 0), 4);
    assert_eq!(ramp_texel(5, 3, 3), 4);
    assert_eq!(ramp_texel(5, 3, 1), 0);
    assert_eq!(ramp_texel(5, 3, 2), 255);
}

/// There is **no** `alpha0 == alpha1` special case, and that absence is
/// deliberate.
///
/// With equal endpoints the oracle takes the unreversed path with
/// `small == large == 128`, so the ramp numerator is `6*128 + 2*128 = 1024`,
/// `1024 / 8 = 128` exactly: codes 0 and 3 return the endpoints' own value
/// (128), while codes 1 and 2 still return the 0 and 255 sentinels. A
/// specification-conforming decoder would collapse the whole palette to one
/// value and codes 1 and 2 would stop being 0 and 255.
///
/// Every value here was cross-checked against `tools/spore/dxt5/dxt5.py` for the
/// block `[128, 128, 0x20, 0x00, 0xE4 x4]`.
#[test]
fn equal_alpha_endpoints_have_no_special_case() {
    let block = block(
        128,
        128,
        0x20,
        0x00,
        [0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3],
    );
    let image = decode_dxt5_mip(&block, 4, 4).expect("one whole block decodes");
    let cycle = [
        [8u8, 0, 0, 128],
        [0, 0, 0, 0],
        [8, 0, 0, 255],
        [8, 0, 0, 128],
    ];
    for row in 0..4 {
        for (col, expected) in cycle.iter().enumerate() {
            let texel = row * 4 + col;
            let got: [u8; 4] = image.pixels[texel * 4..texel * 4 + 4].try_into().unwrap();
            assert_eq!(&got, expected, "texel {texel}");
        }
    }
}

// ---------------------------------------------------------------------------
// 4. Palette size branches and index clamping
// ---------------------------------------------------------------------------

/// `c0 > c1` selects **two** colours, which is the first deliberate deviation.
///
/// The block uses `c0 = 0x20 = 32` and `c1 = 0x00`, so `palette = [(8,0,0),
/// (0,0,0)]`. Codes 0 and 1 must reach the two real entries; codes 2 and 3 are
/// out of range and clamp to `palette[0] = (8,0,0)`.
///
/// Clamping is observable here and wrapping is not: a decoder that wrapped the
/// index would send code 3 to `palette[1] = (0,0,0)`. The colour is the
/// discriminator, so this test fails for a wrap and passes only for a clamp.
#[test]
fn a_c0_above_c1_block_yields_two_usable_colours_and_clamps_the_rest() {
    let codes = [0u8, 1, 2, 3];
    let block = block(
        0,
        255,
        0x20,
        0x00,
        [0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3],
    );
    let image = decode_dxt5_mip(&block, 4, 4).expect("one whole block decodes");
    let expected: [[u8; 3]; 4] = [[8, 0, 0], [0, 0, 0], [8, 0, 0], [8, 0, 0]];
    for row in 0..4 {
        for (col, code) in codes.iter().copied().enumerate() {
            let texel = row * 4 + col;
            let got = &image.pixels[texel * 4..texel * 4 + 3];
            assert_eq!(got, expected[code as usize], "texel {texel}, code {code}");
        }
    }
    // Alpha follows the same code: code 0 -> round(2*255/8) = 64, code 1 -> 0,
    // codes 2 and 3 are sentinels at 255 and the ramp at 64 respectively.
    let alphas = [64u8, 0, 255, 64];
    for row in 0..4 {
        for col in 0..4 {
            let texel = row * 4 + col;
            assert_eq!(
                image.pixels[texel * 4 + 3],
                alphas[codes[col] as usize],
                "texel {texel}"
            );
        }
    }
}

/// `c0 <= c1` selects **four** colours: the other half of deviation 1.
///
/// With `c0 = 0` and `c1 = 0x08<<2 = 32` the palette is
/// `[rgb5(0), rgb5(32), rgb5(10), rgb5(16)] = [(0,0,0), (8,0,0), (0,0,0),
/// (0,0,0)]`. Two entries are usable-and-distinct (0 and 1); the blends land on
/// the same colour as entry 0 because a 6-bit input can only produce red 0 or 8
/// — the black/red signature. That is the observable consequence of reading
/// R5G5B5 out of a 6-bit field, and it is why this test pins entries 1 and 0
/// separately instead of just "all four exist".
#[test]
fn a_c0_at_or_below_c1_block_yields_four_colours() {
    let block = block(
        0,
        255,
        0x00,
        0x08,
        [0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3],
    );
    let image = decode_dxt5_mip(&block, 4, 4).expect("one whole block decodes");
    let expected: [[u8; 3]; 4] = [[0, 0, 0], [8, 0, 0], [0, 0, 0], [0, 0, 0]];
    for row in 0..4 {
        for (col, code) in [0u8, 1, 2, 3].iter().copied().enumerate() {
            let texel = row * 4 + col;
            assert_eq!(
                &image.pixels[texel * 4..texel * 4 + 3],
                expected[code as usize],
                "texel {texel}, code {code}"
            );
        }
    }
}

/// `c0 == c1` takes the four-colour branch, not the two-colour one.
///
/// The published specification treats equality as the "four colours" case too,
/// so this one branch agrees; it is pinned because it is the boundary the
/// inverted test puts on the other side of the comparison.
#[test]
fn equal_colour_endpoints_take_the_four_colour_branch() {
    let equal = block(
        0,
        255,
        0x00,
        0x00,
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    );
    let below = block(
        0,
        255,
        0x00,
        0x04,
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    );
    let equal_image = decode_dxt5_mip(&equal, 4, 4).expect("one whole block decodes");
    let below_image = decode_dxt5_mip(&below, 4, 4).expect("one whole block decodes");
    assert_eq!(
        equal_image.pixels, below_image.pixels,
        "c0 == c1 behaves as c0 < c1"
    );
}

/// A four-colour block whose two blends are *distinguishable* from the
/// endpoints, so "all four entries exist" is asserted rather than assumed.
///
/// `c0` and `c1` are chosen so that entry 1 is red and entries 0, 2 and 3 are
/// black; the alpha channel then distinguishes code 0 (`64`) from code 3 (`64`
/// as well, since both take the ramp) — which is exactly why this test asserts
/// the *colour* per code and the colour of entry 1 separately.
#[test]
fn every_palette_entry_is_addressable() {
    // c0 = 0, c1 = 63: entry 1 = rgb5(63) = (8,0,0); the blends
    // rgb5((0+63)/3 = 21) = (0,0,0) and rgb5((0+63)/2 = 31) = (0,0,0).
    let block = block(
        0,
        255,
        0x00,
        0x0F,
        [0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3],
    );
    let image = decode_dxt5_mip(&block, 4, 4).expect("one whole block decodes");
    for row in 0..4 {
        for col in 0..4 {
            let texel = (row * 4 + col) * 4;
            match col {
                1 => assert_eq!(&image.pixels[texel..texel + 3], &[8, 0, 0], "palette[1]"),
                _ => assert_eq!(
                    &image.pixels[texel..texel + 3],
                    &[0, 0, 0],
                    "palette[{col}]"
                ),
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 5. Multi-block images and block addressing
// ---------------------------------------------------------------------------

/// A 4x4 mip is exactly one block, and the output is exactly `w * h * 4` bytes.
#[test]
fn a_4x4_mip_is_one_block() {
    let image = decode_dxt5_mip(&TWO_COLOUR_FULL_ALPHA, 4, 4).expect("one whole block decodes");
    assert_eq!(image.pixels.len(), 4 * 4 * 4);
    assert_eq!(image.pixels, [[8u8, 0, 0, 191]; 16].concat());
}

/// An 8x8 mip is four blocks addressed in **block** order, row-major.
///
/// Each of the four blocks is a different 16-bit pattern
/// ([`addressing_block`]), so this is the test that catches the classic
/// addressing bug: taking the row stride in texels instead of blocks, or
/// indexing the block grid by texel coordinate. Either mistake lands a visibly
/// different pattern on screen rather than a plausible one.
///
/// The expected bytes are the output of `tools/spore/dxt5/dxt5.py` for the same
/// four blocks in this order.
#[test]
fn an_8x8_mip_addresses_four_blocks_in_block_row_major_order() {
    let chain = chain(&[
        addressing_block(0),
        addressing_block(1),
        addressing_block(2),
        addressing_block(3),
    ]);
    assert_eq!(chain.len(), 4 * BLOCK_BYTES);
    let image = decode_dxt5_mip(&chain, 8, 8).expect("four blocks cover an 8x8 mip");
    assert_eq!(image.width, 8);
    assert_eq!(image.height, 8);
    assert_eq!(image.pixels.len(), 8 * 8 * 4);
    assert_eq!(image.pixels, expected_addressing_8x8());
}

/// A 5x3 mip is two blocks wide and one block tall: 16 bytes of input for 60
/// bytes of output.
///
/// The left block is the golden reversed-ramp block (alpha 191) and the right
/// block is the unreversed one (alpha 64), so column 4 is distinguishable from
/// columns 0..3 — a decoder that mis-strided would give the wrong alpha to the
/// whole right column. Rows 3 and 4 of the single block row do not exist and must
/// be skipped rather than written: the output is exactly 60 bytes.
#[test]
fn a_5x3_mip_skips_the_padding_texels_of_its_second_block() {
    let right = block(0, 255, 0x20, 0x00, [0; 16]);
    let chain = chain(&[TWO_COLOUR_FULL_ALPHA, right]);
    assert_eq!(chain.len(), 2 * BLOCK_BYTES);
    let image = decode_dxt5_mip(&chain, 5, 3).expect("two blocks cover a 5x3 mip");
    assert_eq!(image.width, 5);
    assert_eq!(image.height, 3);
    assert_eq!(image.pixels.len(), 5 * 3 * 4);
    for y in 0..3u32 {
        for x in 0..5u32 {
            let offset = ((y * 5 + x) * 4) as usize;
            let expected = if x < 4 {
                [8u8, 0, 0, 191]
            } else {
                [8, 0, 0, 64]
            };
            assert_eq!(
                &image.pixels[offset..offset + 4],
                &expected,
                "texel ({x},{y})"
            );
        }
    }
}

/// A 1x1 mip is one block whose first texel is the only texel, and a 1x17 mip is
/// five blocks tall of which only one texel column survives per row.
#[test]
fn degenerate_mip_dimensions_still_address_correctly() {
    let image = decode_dxt5_mip(&TWO_COLOUR_FULL_ALPHA, 1, 1).expect("one block covers 1x1");
    assert_eq!(image.pixels.len(), 4);
    assert_eq!(image.pixels, [8, 0, 0, 191]);

    // 1x17 -> one block wide, ceil4(17) = 5 blocks tall.
    let chain = vec![0u8; 5 * BLOCK_BYTES];
    let image = decode_dxt5_mip(&chain, 1, 17).expect("five blocks cover 1x17");
    assert_eq!(image.pixels.len(), 17 * 4, "1x17 is 17 RGBA8 texels");
    assert_eq!(dxt5_mip_size(1, 17, 0), 5 * BLOCK_BYTES);
}

/// A block chain longer than the mip needs is accepted; the extra bytes are the
/// rest of the record and belong to the next mip or the next layer.
#[test]
fn trailing_bytes_after_the_mip_are_ignored() {
    let mut chain = vec![0u8; BLOCK_BYTES];
    chain.extend_from_slice(&TAIL_CLAMP);
    let image = decode_dxt5_mip(&chain, 4, 4).expect("extra trailing bytes are not an error");
    assert_eq!(image.pixels.len(), 4 * 4 * 4);
    assert_eq!(image.pixels, [[0u8, 0, 0, 0]; 16].concat());
}

// ---------------------------------------------------------------------------
// 6. Rejections and truncation sweeps
// ---------------------------------------------------------------------------

/// Every prefix length of one block: `Ok` only at the full eight bytes, `Err`
/// before, and never a panic at any length including zero.
#[test]
fn every_prefix_length_of_one_block_is_ok_or_err_and_never_panics() {
    let block = block(
        0,
        255,
        0x20,
        0x00,
        [0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0],
    );
    for length in 0..=BLOCK_BYTES {
        let prefix = &block[..length];
        match decode_dxt5_mip(prefix, 4, 4) {
            Ok(image) => {
                assert_eq!(length, BLOCK_BYTES, "a short chain must not decode");
                assert_eq!(image.pixels.len(), 64);
            }
            Err(error) => {
                assert!(
                    matches!(error, TextureError::ShortBlockChain { needed: 8, .. }),
                    "length {length}: unexpected error {error}"
                );
            }
        }
    }
}

/// Zero dimensions are refused by name rather than producing an empty image.
#[test]
fn zero_dimensions_are_refused() {
    for (width, height) in [(0u32, 4u32), (4, 0), (0, 0)] {
        let chain = vec![0u8; BLOCK_BYTES];
        let error = decode_dxt5_mip(&chain, width, height).expect_err("zero dimension");
        assert_eq!(error, TextureError::ZeroDimension { width, height });
    }
}

/// A short chain names the mip's own geometry, so a caller can tell which mip of
/// which layer was short.
#[test]
fn a_short_chain_reports_the_geometry_it_needed() {
    let error = decode_dxt5_mip(&[0u8; 7], 4, 4).expect_err("seven bytes are not a block");
    assert_eq!(
        error,
        TextureError::ShortBlockChain {
            available: 7,
            needed: 8,
            width: 4,
            height: 4
        }
    );
    let error = decode_dxt5_mip(&[0u8; 8], 8, 8).expect_err("one block is not four");
    assert_eq!(
        error,
        TextureError::ShortBlockChain {
            available: 8,
            needed: 32,
            width: 8,
            height: 8
        }
    );
}

/// Sizing neither panics nor wraps to a small plausible number.
///
/// `dxt5_chain_size(u32::MAX, u32::MAX, 64)` is the largest input the sizing
/// rules can be handed. Every one of its 32 bounded mips is a power of two —
/// `ceil4(u32::MAX >> m)` is `2^(30-m)` down to `m = 29`, then 2 and 1 — so the
/// chain is `2^63 + 2^61 + ... + 2^5 + 8 + 8 = 12_297_829_382_473_034_416`,
/// plus `8` for each of the 32 mips past the 32-mip floor.
///
/// That is where a wrapping implementation would show: it would come back as a
/// few hundred bytes, which would then parse as a plausible tiny texture.
///
/// **It does not saturate, and on a 64-bit target it cannot**: `12.3e18` is below
/// `usize::MAX` (`18.4e18`), and no combination of `u32` arguments can exceed
/// that, since the mip terms are bounded by `2^63` each and the extra-mip term by
/// `8 * (2^32 - 32)`. The saturating operators are still what makes the function
/// correct, because the same call on a 32-bit target *does* saturate — every
/// one of those mip terms is larger than a `u32`. So this test pins the exact
/// value, and asserts the property that is portable: never a panic, never a wrap.
#[test]
fn chain_size_never_wraps_to_a_small_number() {
    let chain = dxt5_chain_size(u32::MAX, u32::MAX, 64);
    assert_eq!(chain, 12_297_829_382_473_034_672);
    assert!(
        chain >= (1usize << 63),
        "a u32::MAX square cannot look small"
    );
    // The equality above is the real check: 12_297_829_382_473_034_672 is well
    // below `usize::MAX` (18_446_744_073_709_551_615), so this input does *not*
    // saturate on a 64-bit target. No `u32` argument can make it saturate here,
    // which is why the test asserts the exact value and the absence of a wrap
    // rather than the presence of a clamp.

    // Every mip term is itself a power of two, and the sum is exactly them plus
    // one block per mip past the floor.
    let bounded: usize = (0..32).map(|m| dxt5_mip_size(u32::MAX, u32::MAX, m)).sum();
    assert_eq!(bounded, 12_297_829_382_473_034_416);
    assert_eq!(chain, bounded + 32 * BLOCK_BYTES);
    assert_eq!(dxt5_mip_size(u32::MAX, u32::MAX, 0), 1usize << 63);

    // A large but unremarkable case still sums exactly, with no saturation.
    // 2^20 x 2^20 over four mips: 2^36 blocks at the base level.
    let huge = dxt5_chain_size(1 << 20, 1 << 20, 4);
    // Each mip halves both dimensions, so each term is a quarter of the last.
    assert_eq!(
        huge,
        (1usize << 39) + (1usize << 37) + (1usize << 35) + (1usize << 33)
    );
    assert!(huge < usize::MAX);
}

/// Absurd dimensions are refused by name rather than aborting an allocation.
///
/// `u32::MAX` squared needs a `2^63`-byte block chain, which no caller can
/// supply, so the length check fires and reports the impossible stride it needed.
/// The dimension is still named, so a report identifies the mip that was
/// impossible.
///
/// The `isize::MAX` output guard behind this error is **not reachable from this
/// function**: reaching it needs a chain longer than `2^60` bytes, which is 8
/// exabytes. It exists so that an adversarial envelope is refused rather than
/// aborting the process on a failed allocation — a behaviour the C++ reference
/// does not have. `every_error_message_names_its_section` covers its message.
#[test]
fn absurd_dimensions_are_refused_by_name() {
    assert_eq!(
        decode_dxt5_mip(&[0u8; BLOCK_BYTES], u32::MAX, u32::MAX).expect_err("no such chain"),
        TextureError::ShortBlockChain {
            available: 8,
            needed: 1usize << 63,
            width: u32::MAX,
            height: u32::MAX,
        }
    );
    // A width and height whose product cannot be expressed at all.
    assert_eq!(
        decode_dxt5_mip(&[], 65535, 65535).expect_err("chain cannot be supplied"),
        TextureError::ShortBlockChain {
            available: 0,
            needed: 16384 * 16384 * 8,
            width: 65535,
            height: 65535,
        }
    );
}

/// Error messages name their section and the format that was wanted, so a log
/// line is enough to act on.
#[test]
fn every_error_message_names_its_section() {
    let cases: Vec<(TextureError, &str)> = vec![
        (
            TextureError::TruncatedEnvelope { available: 4 },
            "4 bytes < the 32-byte",
        ),
        (
            TextureError::UnsupportedFourcc {
                fourcc: 0x1500_0000,
            },
            "unsupported fourcc 0x15000000",
        ),
        (
            TextureError::ZeroDimension {
                width: 0,
                height: 4,
            },
            "zero-sized image",
        ),
        (TextureError::ZeroMipCount, "mipCount is 0"),
        (
            TextureError::RecordShorterThanEnvelope { record_size: 8 },
            "smaller than the 32-byte",
        ),
        (
            TextureError::ChainSizeOverflow {
                width: u32::MAX,
                height: u32::MAX,
                mip_count: 1,
            },
            "exceeds the addressable size",
        ),
        (
            TextureError::PayloadTooSmall {
                available: 3,
                needed: 56,
            },
            "3 payload bytes < 56",
        ),
        (
            TextureError::PayloadNotMultiple {
                available: 57,
                per: 56,
            },
            "57 payload bytes is not a multiple of the 56-byte",
        ),
        (
            TextureError::MipSlicePastRecord {
                layer: 1,
                mip: 2,
                offset: 28,
                size: 8,
                record_size: 32,
            },
            "layer 1 mip 2 needs 8 bytes at offset 28",
        ),
        (
            TextureError::ShortBlockChain {
                available: 7,
                needed: 8,
                width: 4,
                height: 4,
            },
            "7 bytes < 8 for 4x4",
        ),
        (
            TextureError::OutputTooLarge {
                width: 1,
                height: 2,
            },
            "exceeds the addressable output",
        ),
        (
            TextureError::OutputInvariant {
                width: 4,
                height: 4,
                texel_x: 5,
                texel_y: 6,
            },
            "internal output-size invariant failed at texel (5, 6)",
        ),
    ];
    for (error, needle) in &cases {
        let text = error.to_string();
        assert!(
            text.contains(needle),
            "message {text:?} does not mention {needle:?}"
        );
        assert!(!text.is_empty());
    }
    // A new variant needs a message case here, or its message is unasserted.
    assert_eq!(
        cases.len(),
        12,
        "a new TextureError variant needs a message case here"
    );
}

// ---------------------------------------------------------------------------
// 9. Oracle cross-check over a pseudo-random corpus
// ---------------------------------------------------------------------------

/// A deterministic pseudo-random block chain, so the corpus test needs no fixture
/// file and no randomness.
///
/// This is the generator `tools/spore/dxt5/dxt5.py` was run against to produce
/// the expected hashes below: an LCG of the kind C standard libraries ship,
/// taking bits 16..23 of each state as one byte.
fn lcg_bytes(count: usize, seed: u32) -> Vec<u8> {
    let mut out = Vec::with_capacity(count);
    let mut state = seed;
    for _ in 0..count {
        state = state.wrapping_mul(1_103_515_245).wrapping_add(12_345);
        out.push(((state >> 16) & 0xFF) as u8);
    }
    out
}

/// FNV-1a over 64 bits. A checksum rather than 4096 hard-coded bytes: it pins
/// the whole output, and a failure points at the mip that broke.
fn fnv1a64(data: &[u8]) -> u64 {
    let mut hash: u64 = 0xcbf2_9ce4_8422_2325;
    for byte in data {
        hash ^= u64::from(*byte);
        hash = hash.wrapping_mul(0x0000_0100_0000_01b3);
    }
    hash
}

/// A 32x32 corpus: 64 blocks of pseudo-random endpoints, indices and colour
/// words, decoded to 4096 bytes of RGBA8.
///
/// Random blocks exercise every combination the hand-written goldens do not: both
/// palette branches, both ramp directions, all four codes, equal endpoints,
/// equal colour endpoints and out-of-range indices, across many alignments. The
/// expected hash was produced by `tools/spore/dxt5/dxt5.py` on exactly this input,
/// so this is a byte-for-byte cross-check of the whole decoder against the
/// independent Python implementation, not a self-consistency check.
#[test]
fn a_pseudo_random_32x32_corpus_matches_the_oracle_hash() {
    let chain = lcg_bytes(64 * BLOCK_BYTES, 123_456_789);
    assert_eq!(chain.len(), 512);
    let image = decode_dxt5_mip(&chain, 32, 32).expect("64 blocks cover a 32x32 mip");
    assert_eq!(image.pixels.len(), 32 * 32 * 4);
    assert_eq!(fnv1a64(&image.pixels), 0x2337_9e35_779d_2ab5);
}

/// The same cross-check at sizes that are not a multiple of four, where the
/// padding texels and the block-row stride are the only things that can go
/// wrong. Each expected hash is the oracle's for the same generator and seed.
#[test]
fn a_pseudo_random_corpus_matches_the_oracle_hash_at_awkward_sizes() {
    for (width, height, blocks, expected) in [
        (5u32, 3u32, 2usize, 0x5e25_a0e8_7661_3ad5u64),
        (13, 7, 8, 0x0747_d796_44f3_0ac8),
        (1, 1, 1, 0x4cfb_78c2_4f7d_0bc3),
        (64, 64, 256, 0x3232_9b4a_e6e9_2e88),
    ] {
        let chain = lcg_bytes(blocks * BLOCK_BYTES, 999);
        let image =
            decode_dxt5_mip(&chain, width, height).expect("the chain covers the mip exactly");
        assert_eq!(
            image.pixels.len(),
            width as usize * height as usize * 4,
            "{width}x{height}"
        );
        assert_eq!(fnv1a64(&image.pixels), expected, "{width}x{height}");
        assert_eq!(
            chain.len(),
            dxt5_mip_size(width, height, 0),
            "{width}x{height}"
        );
    }
}
