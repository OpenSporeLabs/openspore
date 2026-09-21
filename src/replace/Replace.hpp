// Obj36C — clean-room replacement of Simulator::Cell::MovePlayerToMousePosition
// (linked VA 0x00e5b790, `void (float deltaTime)`, cdecl — CONFIRMED via SDK;
// see docs/REPLACEMENT-ABI.md). The hook seam (5-byte entry, `a1 04 3c 6b 01`)
// and the in-process 0xE9 rel32 patch are proven in tools/replace/synthetic/
// (Obj36A); this header is the replacement that gets jumped to.
//
// Evidence vocabulary (RECON appendix A): OBSERVED / VERIFIED / CONFIRMED /
// SUPPORTED / INFERRED / APPROXIMATION / UNKNOWN. Decompilation is
// EVIDENCE-NOT-TRUTH.
//
// Contract mapping (ABI doc section 5):
//   - The REAL function takes one cdecl `float deltaTime` on the stack; the
//     hook is a `jmp`, so the caller frame (esp/arg layout) is inherited.
//     `deltaTime` is the only real argument — it is consumed by the original's
//     per-frame update call (FUN_00e5b2e0), not by the ray-plane math.
//   - `sCellGame`, `cam`, `plane` are STAND-INS for the globals the original
//     reaches for by address (sCellGame@0x16b3c04, the ILightingWorld camera,
//     the DAT_* plane constants). In the installed 32-bit build they are the
//     real globals; in the clean-room unit they are test buffers.
//
// The function is deterministic and pure w.r.t. its inputs: no globals, no
// wall clock, no rand.
#pragma once

#include "../sim/Sim.hpp"
#include "CellGameView.hpp"

namespace openspore::replace {

// Stand-in for the camera the original resolves via FUN_007c4900 (view origin
// + normalized view ray, obtained through ILightingWorld from the last mouse
// position). The original keeps the mouse NDC internally; we take the
// resolved ray directly so the replacement stays pure.
struct CameraView {
  float origin[3] = {0.0F, 0.0F, 0.0F};
  float dir[3] = {0.0F, -1.0F, 0.0F};  // normalized
};

// Clean-room replacement. Reproducing the OBSERVED behavior (ABI doc section 4):
//   1. lock guard: sCellGame+0x5158 != 0 -> return.
//   2. fetch the player entity from sCellGame+0x411c; null -> return.
//   3. camera ray ∩ movement plane:
//        denom = dir·N;  denom == 0.0 -> no hit      (OBSERVED guard)
//        t = (point − origin)·N / denom;  t < 0.0 -> no hit  (OBSERVED guard)
//   4. on hit: write player target position (player+0x08/0c/10), set the
//      moving flag (sCellGame+0x5270 = 1), compute the travel orientation
//      from delta = −(target − current) (transcribed; the decompiler's sign)
//      and write player+0x14..0x20.
//
// The ray-plane math is identical to Obj33's sim::rayPlaneHit EXCEPT the
// guards use the OBSERVED `denom != 0.0` / `t >= 0.0` exactly (Sim.cpp's
// helper adds a 1e-6 parallel epsilon that the decompilation does not show);
// it is re-implemented here so the replacement matches the observed guards
// rather than the sim's convenience epsilon.
//
// playerRef stand-in: the real 4 bytes at +0x411c are the POOL INDEX that the
// original passes to FUN_00b721d0; the installed replacement must run that
// lookup itself. In this unit those 4 bytes are read as the resolved entity
// pointer (32-bit: index and pointer are both 4 bytes). APPROXIMATION seam,
// documented.
//
// The orientation quaternion LAYOUT (FUN_0069b600's output) is INFERRED: the
// decompilation only shows 4 floats written to player+0x14..0x20. The stand-in
// computes a yaw quaternion around +Y from the horizontal travel delta,
// matching the sim's heading convention (fwd = (sin h, 0, cos h)).
void replacement_MovePlayerToMousePosition(float deltaTime, SCellGameView* sCellGame,
                                           const CameraView* cam, const sim::MovementPlane* plane);

// Obj36D — EVIDENCE-NOT-TRUTH reference. A faithful, line-by-line
// transcription of the DECOMPILED body (tools/re/data/decompiled/
// MovePlayerToMousePosition.c): same guards, same t formula, same store
// pattern, same field offsets. It is "the original's logic" only as far as
// the decompiler tells us — cast types are the decompiler's guesses, and the
// per-frame-update / camera-mode / UI-gating calls (FUN_00e5b2e0, FUN_00743b50,
// FUN_00e4ce40+0xd4, FUN_00e82130, the sCellUI selection gate) are OMITTED:
// they touch environment state, not the fields the differential compares.
// A live-runtime differential against the original is NOT possible headless
// (cell mode is unreachable); see docs/REPLACEMENT-DIFF.md.
void reference_MovePlayerToMousePosition(float deltaTime, SCellGameView* sCellGame,
                                         const CameraView* cam, const sim::MovementPlane* plane);

}  // namespace openspore::replace
