// CS-31: cell animation blend state machine + event->effect mapping.
// Implementation of CellAnim.hpp — see the header for the evidence mapping.
#include "CellAnim.hpp"

namespace openspore::apps {

AnimBlend animBlend(CellAnim current, CellAnim target, float scale) {
  AnimBlend b; // in = out = 0.2 (decompiled defaults)
  if (current == CellAnim::kIdleBig || current == CellAnim::kIdleBlink1Big) {
    b.out = 0.1F;
  }
  if (current == CellAnim::kEatProbRetractTrgt ||
      current == CellAnim::kTakeDmgElecNpc ||
      current == CellAnim::kTakeDmgPoisonNpc) {
    b.out = 0.0F;
  }
  if (target == CellAnim::kEatProbRetractTrgt) {
    b.in = 0.0F;
  }
  b.in *= scale;
  b.out *= scale;
  return b;
}

int selectEffectMapSlot(int recordType) {
  // LoadEffectMap @ 00e63560 switch on the per-record type word:
  //   case 0, case 2 -> sCellGFX+0x161c8 (slot 0)
  //   case 1, case 3 -> sCellGFX+0x161bc (slot 1)
  //   case 4         -> sCellGFX+0x161b4 (slot 2)
  switch (recordType) {
  case 0:
  case 2:
    return 0;
  case 1:
  case 3:
    return 1;
  case 4:
    return 2;
  default:
    return -1;
  }
}

uint32_t effectIDForEvent(const char *event) {
  if (event == nullptr) {
    return 0;
  }
  // The contract's SimEvents (docs/CELL-CONTRACT.md): "eat" / "flee".
  if (event[0] == 'e' && event[1] == 'a' && event[2] == 't' &&
      event[3] == '\0') {
    return 1; // the eat effect
  }
  if (event[0] == 'f' && event[1] == 'l' && event[2] == 'e' &&
      event[3] == 'e' && event[4] == '\0') {
    return 2; // the damage / flee effect
  }
  if (event[0] == 'd' && event[1] == 'e' && event[2] == 'a' &&
      event[3] == 't' && event[4] == 'h' && event[5] == '\0') {
    return 2;
  }
  return 0;
}

EffectInstance instanceEffect(uint32_t effectID, const float *mapParams,
                              const float *planePoint, const float *cellPos) {
  EffectInstance inst;
  inst.effectID = effectID;
  for (int i = 0; i < 9; ++i) {
    inst.params[i] = mapParams[i];
  }
  // DAT_016b3c28/c2c/c30 (the per-world swim-plane point, CS-01) overrides the
  // first three record words (decompiled local_60[0..2]).
  inst.params[0] = planePoint[0];
  inst.params[1] = planePoint[1];
  inst.params[2] = planePoint[2];
  // 0x3f800000 = 1.0f sentinel (decompiled local_60[3]).
  inst.params[3] = 1.0F;
  for (int i = 0; i < 3; ++i) {
    inst.pos[i] = cellPos[i];
  }
  inst.active = true;
  return inst;
}

} // namespace openspore::apps
