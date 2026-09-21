# REPLACEMENT-DIFF — `MovePlayerToMousePosition`: replacement vs decompilation reference

Obj36C/36D differential result. Driver: `src/replace/tests/diff_test.cpp`
(ctest `replace_diff_test`); reference: `src/replace/Reference.cpp`;
replacement: `src/replace/Replace.cpp`.

## Evidence boundary (read first)

- The reference is a **line-by-line transcription of the DECOMPILER output**
  (Ghidra 12.1.2 capture, `tools/re/data/decompiled/MovePlayerToMousePosition.c`,
  SporeApp.exe 3.1.0.22). It is **EVIDENCE-NOT-TRUTH**: cast types are the
  decompiler's guesses, and environment-dependent calls (per-frame update,
  camera-mode read, UI selection gate) are omitted — none of them write the
  fields compared below.
- **There is NO live cell-mode runtime available headless — cell mode is
  unreachable in this environment.** This differential is therefore NOT a
  live-runtime verification. A green run only proves the replacement
  reproduces the decompilation reference within tolerance.
- Field offsets (VERIFIED from decompilation), field meanings (INFERRED),
  plane constant values (APPROXIMATION, never read), quaternion layout
  (INFERRED stand-in) — see `docs/REPLACEMENT-ABI.md` and
  `src/replace/CellGameView.hpp`.

## Method

8 deterministic cases × 8 output fields (`pos_x/y/z`, `orient_qx/qy/qz/qw`,
`moving`) = **64 comparisons**. Floats compared with tolerance `1e-6`
(float32); `moving` exact. Both sides receive byte-identical state buffers
(low-4-GiB `MAP_32BIT` allocations so the 32-bit `playerRef` stand-in is a
valid address) and identical camera/plane inputs. The decompiled ray-plane
guards are used verbatim (`denom == 0.0` → no hit; `t < 0.0` → no hit), not
the sim helper's 1e-6 parallel epsilon.

## Results (ctest `replace_diff_test`, 2026-09-21, host build)

| case | field | ref value | replacement value | match? | tolerance |
|---|---|---|---|---|---|
| `normal_hit_center` (ray ↓ at origin, t=12) | pos_x | 0 | 0 | MATCH | 1e-6 |
| | pos_y | 0 | 0 | MATCH | 1e-6 |
| | pos_z | 0 | 0 | MATCH | 1e-6 |
| | orient_qx | 0 | 0 | MATCH | 1e-6 |
| | orient_qy | 0.948683262 | 0.948683262 | MATCH | 1e-6 |
| | orient_qz | 0 | 0 | MATCH | 1e-6 |
| | orient_qw | 0.316227794 | 0.316227794 | MATCH | 1e-6 |
| | moving | 1 | 1 | MATCH | exact |
| `hit_offset_plus_x` (mouse offset → +X hit) | pos_x | 1.27272701 | 1.27272701 | MATCH | 1e-6 |
| | pos_y | 0 | 0 | MATCH | 1e-6 |
| | pos_z | -6 | -6 | MATCH | 1e-6 |
| | orient_qx | 0 | 0 | MATCH | 1e-6 |
| | orient_qy | -0.216930449 | -0.216930449 | MATCH | 1e-6 |
| | orient_qz | 0 | 0 | MATCH | 1e-6 |
| | orient_qw | 0.97618705 | 0.97618705 | MATCH | 1e-6 |
| | moving | 1 | 1 | MATCH | exact |
| `hit_offset_minus_x` (mirror, hit → -X) | pos_x | -1.27272701 | -1.27272701 | MATCH | 1e-6 |
| | pos_y | 0 | 0 | MATCH | 1e-6 |
| | pos_z | -6 | -6 | MATCH | 1e-6 |
| | orient_qx | 0 | 0 | MATCH | 1e-6 |
| | orient_qy | 0.216930449 | 0.216930449 | MATCH | 1e-6 |
| | orient_qz | 0 | 0 | MATCH | 1e-6 |
| | orient_qw | 0.97618705 | 0.97618705 | MATCH | 1e-6 |
| | moving | 1 | 1 | MATCH | exact |
| `hit_nontrivial_plane` (z=2 wall, oblique ray) | pos_x | 1 | 1 | MATCH | 1e-6 |
| | pos_y | 1.24999976 | 1.24999976 | MATCH | 1e-6 |
| | pos_z | 2 | 2 | MATCH | 1e-6 |
| | orient_qx | 0 | 0 | MATCH | 1e-6 |
| | orient_qy | -0.973249018 | -0.973249018 | MATCH | 1e-6 |
| | orient_qz | 0 | 0 | MATCH | 1e-6 |
| | orient_qw | 0.229752883 | 0.229752883 | MATCH | 1e-6 |
| | moving | 1 | 1 | MATCH | exact |
| `ray_parallel_to_plane` (denom = 0 → no hit) | pos_x | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_y | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_z | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qx | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qy | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qz | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qw | 1 | 1 | MATCH (no write) | 1e-6 |
| | moving | 0 | 0 | MATCH (no write) | exact |
| `ray_behind_origin` (t < 0 → no hit) | pos_x | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_y | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_z | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qx | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qy | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qz | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qw | 1 | 1 | MATCH (no write) | 1e-6 |
| | moving | 0 | 0 | MATCH (no write) | exact |
| `lock_set` (sCellGame+0x5158 = 1 → early return) | pos_x | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_y | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_z | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qx | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qy | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qz | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qw | 1 | 1 | MATCH (no write) | 1e-6 |
| | moving | 0 | 0 | MATCH (no write) | exact |
| `player_null` (pool lookup → 0 → early return) | pos_x | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_y | 0 | 0 | MATCH (no write) | 1e-6 |
| | pos_z | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qx | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qy | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qz | 0 | 0 | MATCH (no write) | 1e-6 |
| | orient_qw | 1 | 1 | MATCH (no write) | 1e-6 |
| | moving | 0 | 0 | MATCH (no write) | exact |

## Verdict

**64/64 field comparisons MATCH; 0 mismatches.** No field required an
explanation — the replacement and the transcription use identical formulas,
guards, and store order, so even float32 rounding agrees at the displayed
precision.

The replacement reproduces the decompilation reference **within tolerance
(1e-6 / exact)**. This is **NOT a live-runtime verification** (cell mode is
unreachable headless — no Wine cell-mode trace exists): status is
**replaced-approx**, pending a Wine cell-mode trace to promote the INFERRED
field offsets and APPROXIMATION plane constants to VERIFIED.
