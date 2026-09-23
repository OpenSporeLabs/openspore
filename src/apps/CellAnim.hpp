// CS-31: cell animation blend state machine + event->effect mapping.
//
// Clean-room reimplementation of two Simulator::Cell behaviors, from static
// evidence only:
//   - PlayAnimation @ 00e6d200 (317 B): sets the animation blend in/out times
//     from (currentAnim, targetAnim) with the observed special cases, scales
//     them by the cell's animation-time factor, then plays the target anim.
//   - cCellGFX::InstanceEffectOnCell @ 00e66840 (314 B): instantiates a visual
//     effect for a cell from an effect-map param record (DAT_016b3dac, 9 dwords)
//     + the current swim-plane point, placed at the cell transform.
//   - cCellGFX::LoadEffectMap @ 00e63560 (1,114 B): the 3-slot effect-map
//     selection (the switch on the per-record type word).
//
// The RW4 keyframe decode diff against the CS-04 oracle is the existing
// rw4_test (CS-04 landed); this module only consumes it.
//
// Deterministic: no time(), no rand() — the same (anim, anim, scale) always
// yields the same blend params, and the same (event, map) always yields the
// same effect instance.
#pragma once

#include <cstdint>

namespace openspore::apps {

// CellAnimations indices referenced by PlayAnimation (SDK enum names). Only
// the values the blend state machine reads are named; the rest are inert.
enum class CellAnim : int {
  kIdle = 0,
  kSwimForward,
  kEat,
  kIdleBig,
  kIdleBlink1Big,
  kEatProbRetractTrgt,
  kTakeDmgElecNpc,
  kTakeDmgPoisonNpc,
};

// The blend times PlayAnimation computes (seconds), before scaling. The
// decompiled defaults are 0.2/0.2 with the observed current/target-anim
// overrides.
struct AnimBlend {
  float in = 0.2F;
  float out = 0.2F;
};

// PlayAnimation blend state machine (the deterministic core of 00e6d200).
//   base in = out = 0.2
//   if current in {IdleBig, IdleBlink1Big}            -> out = 0.1
//   if current in {EatProbRetractTrgt, TakeDmgElecNpc,
//                  TakeDmgPoisonNpc}                  -> out = 0.0
//   if target  == EatProbRetractTrgt                  -> in  = 0.0
//   then both times are scaled by `scale` (the cell's animation-time factor,
//   the decompiled FUN_00e563e0(cell)).
// scale 1.0 reproduces the unscaled decompiled values exactly.
AnimBlend animBlend(CellAnim current, CellAnim target, float scale);

// One instantiated cell effect (the deterministic core of
// InstanceEffectOnCell @ 00e66840). params[9] is the effect-map param record
// (DAT_016b3dac, 9 dwords); pos[3] is the placement (the cell transform);
// active mirrors the effect's live flag.
struct EffectInstance {
  uint32_t effectID = 0;
  float params[9] = {0.0F};
  float pos[3] = {0.0F};
  bool active = true;
};

// The 3-slot effect-map selection from LoadEffectMap @ 00e63560: the switch on
// the per-record type word picks one of the three persistent effect objects
// (sCellGFX+0x161c8 / 0x161bc / 0x161b4). type word 0/2 -> slot 0, 1/3 ->
// slot 1, 4 -> slot 2; anything else -> -1 (no slot).
int selectEffectMapSlot(int recordType);

// event -> effect ID. The contract's SimEvents ("eat" / "flee") select which
// cell effect to instantiate: "eat" -> the eat effect, "flee" (or "death") ->
// the damage effect. Unknown events -> 0 (no effect).
uint32_t effectIDForEvent(const char *event);

// Builds an effect instance: copies the 9-dword map param record, overrides the
// first three words with the current swim-plane point (the decompiled
// DAT_016b3c28/c2c/c30 read — the per-world plane point, CS-01), sets the
// fourth word to the decompiled 1.0f (0x3f800000) sentinel, and places it at
// cellPos (the cell transform).
EffectInstance instanceEffect(uint32_t effectID, const float *mapParams,
                              const float *planePoint, const float *cellPos);

} // namespace openspore::apps
