// Obj36C — POD views that alias the real 32-bit Spore memory layouts read
// and written by Simulator::Cell::MovePlayerToMousePosition (0x00e5b790).
//
// Evidence (docs/REPLACEMENT-ABI.md, decompilation capture in
// tools/re/data/decompiled/MovePlayerToMousePosition.c):
//   - FIELD OFFSETS: VERIFIED (read straight from the decompilation).
//   - FIELD MEANINGS: INFERRED (decompiler type guesses; SporeApp.exe has no
//     MSVC RTTI, so class structure is vtable-data + SDK structures only;
//     no cell-mode runtime trace exists).
//   - The plane constant VALUES the original reads (DAT_015a7c40/44/48,
//     DAT_016b3c28/2c/30) were never read: APPROXIMATION — see MovementPlane.
//
// These structs exist ONLY to alias those offsets inside a real buffer. They
// are NOT the true class layout; the padding is anonymous by design.
#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::replace {

// The player entity, resolved at runtime from sCellGame+0x411c via the pool
// lookup FUN_00b721d0 (index in the real process). Offsets from the entity:
//   +0x08/0x0c/0x10  target position X/Y/Z (the ray∩plane hit)   INFERRED
//   +0x14..0x20      orientation quaternion (face travel dir)     INFERRED
//   +0x4c/0x50/0x54  current position X/Y/Z                       INFERRED
struct SPlayerView {
  uint32_t pad0[2];     // +0x00 (unobserved)
  float targetPos[3];   // +0x08 INFERRED
  float orient[4];      // +0x14 INFERRED
  uint32_t pad1[10];    // +0x24 (unobserved)
  float currentPos[3];  // +0x4c INFERRED
};

static_assert(offsetof(SPlayerView, targetPos) == 0x08, "targetPos offset");
static_assert(offsetof(SPlayerView, orient) == 0x14, "orient offset");
static_assert(offsetof(SPlayerView, currentPos) == 0x4c, "currentPos offset");
static_assert(sizeof(SPlayerView) == 0x58, "SPlayerView size");

// The global sCellGame (address 0x16b3c04, CONFIRMED via SDK) — ONLY the
// offsets the target touches, so this layout can alias the real buffer.
//   +0x411c   player pool index (INFERRED) — the decompilation passes the
//             4 bytes there to FUN_00b721d0. In the real 32-bit process the
//             installed replacement must run that pool lookup itself; in the
//             clean-room unit those same 4 bytes are a stand-in for the
//             already-resolved entity pointer (documented in Replace.hpp).
//   +0x5158   lock/paused flag; non-zero => early return (INFERRED)
//   +0x5270   "moving" flag; written 1 when a hit registers (INFERRED,
//             the decomp writes sCellGame+0x5190+0xe0)
struct SCellGameView {
  uint32_t padA[4167];  // +0x0000 (unobserved)
  uint32_t playerRef;   // +0x411c INFERRED
  uint32_t padB[1038];  // +0x4120 (unobserved)
  int32_t lockFlag;     // +0x5158 INFERRED
  uint32_t padC[69];    // +0x515C (unobserved)
  int32_t movingFlag;   // +0x5270 INFERRED
};

static_assert(offsetof(SCellGameView, playerRef) == 0x411c, "playerRef offset");
static_assert(offsetof(SCellGameView, lockFlag) == 0x5158, "lockFlag offset");
static_assert(offsetof(SCellGameView, movingFlag) == 0x5270, "movingFlag offset");
static_assert(sizeof(SCellGameView) == 0x5274, "SCellGameView size");

}  // namespace openspore::replace
