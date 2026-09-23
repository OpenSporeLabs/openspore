// cCellGame state object (Spore-ModAPI SDK struct 61901, 20964 B, 41 fields).
//
// Clean-room re-implementation of the NAMED / meaningful fields of the singleton
// `Simulator::Cell::sCellGame` (VERIFIED address 0x16b3c04). The large
// fixed_vector and cObjectPool backing stores are represented as capacity
// handles (the pool is CS-16), not a byte-exact re-layout of all 20,964 bytes.
//
// Evidence: `Initialize` @ 00e80ba0 (decompiled, docs/analysis/dossiers) sets
// the observable state below. The background-bbox SOURCE constants
// DAT_015a7d3c/40/44 were read from the static binary (SporeApp.exe 3.1.0.22,
// PE .data, VERIFIED). The time-scale field_514C load-time value 0x3f000000
// (= 1.0f) is OBSERVED in the Initialize decompilation.
#pragma once

#include <cstdint>

#include "CellPool.hpp"

namespace openspore::sim {

// CellStageScale (SDK enum, SIZE 4): None + size tiers. A tier value indexes
// the size table DAT_01483bd0 (VERIFIED, SporeApp.exe .rdata):
//   [10, 30, 100, 300, 1000, 3000, 10000, 30000]  for tiers _0.._100 (0..7).
// CreateCellObject: base = (None) ? 1.0 : table[level] * 0.033333335 (= /30).
enum class CellStageScale : int32_t {
  None = -1,  // 0xffffffff
  _0 = 0, _1 = 1, _2 = 2, _4 = 3, _10 = 4, _20 = 5, _40 = 6, _100 = 7,
  _200 = 8, _400 = 9, _1K = 10,
};

// Observable inputs loaded from a cCellCellResource (the resource system loads
// the record; only these fields reach CreateCellObject):
//   size            = the record's size field (FUN_004df2d0 at +0x304)
//   modelKey        = GetModelKeyForCellResource result (0xfc/0x100/0x104)
//   fixedOrientation = record[0xac]==1 → use the fixed identity quaternion
struct CellResourceSpec {
  float size = 1.0F;
  uint32_t modelKey[3] = {0, 0, 0};
  bool fixedOrientation = false;
};

// A non-main pool (query / rollover / linked pools) is kept as a capacity handle
// — only the main object pool (mCells) is the real cObjectPool (CS-16).
struct CellPoolHandle {
  uint32_t capacity = 0;
  uint32_t freeList = 0;
};

// cCellDataReference (structs 61861 / 61881): a reference to a cell world
// resource record.
struct CellDataReference {
  uint32_t id = 0;
};

// The cell-mode state object. Field names follow the SDK where known
// (mpCurrentWorld, mpCurrentWorldBackground, mAvatarCellIndex, mpCellQuery,
// mpCellQueryBackground, mCells, mShowCallMateButtonCountdown, mpSerializableData);
// anonymous SDK fields keep their `field_NNN` / `flag_NNN` names with the SDK
// offset embedded in the name.
struct CellGame {
  // Pool + query (SDK offsets 28 / 16636 / 16640 / 56..196).
  cObjectPool<cCellObjectData> mCells;  // main object pool, capacity 4096
  CellPoolHandle mQueryPool;  // field_38
  CellPoolHandle mQueryBgPool; // field_54
  CellPoolHandle mPool4;      // field_8C
  CellPoolHandle mPool5;      // field_A8
  CellPoolHandle mPool6;      // field_C4
  uint32_t mpCellQuery = 0;         // cCellQueryLinkedPool* @ 16636
  uint32_t mpCellQueryBackground = 0; // cCellQueryLinkedPool* @ 16640

  // Current worlds + avatar cell index (SDK offsets 16660 / 16664 / 16668).
  CellDataReference mpCurrentWorld;
  CellDataReference mpCurrentWorldBackground;
  uint32_t mAvatarCellIndex = 0;  // cObjectPoolIndex

  // ---- fields set by Initialize (00e80ba0), offsets in names ----
  uint32_t field_4124 = 0;  // = 0x14 (20) in Initialize
  float field_514C = 0.0F;  // = 1.0f (0x3f000000) time scale (OBSERVED)
  float field_5150 = 0.0F;  // = copy of field_514C (OBSERVED)
  uint8_t flag_5148 = 0;
  uint8_t flag_5168 = 0;
  uint8_t flag_5169 = 0;
  uint8_t flag_518C = 0;
  uint32_t field_515C = 0;
  uint32_t field_5160 = 0;
  uint32_t field_516C = 0;
  uint32_t field_5194 = 0;
  uint32_t field_5198 = 0;
  uint8_t flag_51DA = 0;  // set to 1 when serializable data is present
  uint32_t field_51B0 = 0;
  uint32_t field_51B4 = 0;  // = 0xffffffff (-1) in Initialize
  uint32_t field_51B8 = 0;
  float field_51BC = 0.0F;  // = FUN_00e52b70() (INFERRED, left 0)
  uint8_t flag_51C0 = 0;
  uint32_t field_51C4 = 0;
  uint32_t field_51C8 = 0;
  uint32_t field_51CC = 0;
  uint32_t field_51D0 = 0;
  uint8_t flag_51DB = 0;
  uint8_t flag_51DC = 0;
  uint32_t field_51E0 = 0;
  float mShowCallMateButtonCountdown = 0.0F;  // @ 20940
  int32_t field_51D4 = 0;
  int32_t field_51D8 = 0;

  // Background visible-bbox (DAT_016b3c8c..016b3c9c), written by Initialize
  // from the read source constants.
  float bgBBoxMin = 0.0F;       // DAT_016b3c8c = DAT_015a7d40 - 7.5
  float bgBBoxZ0 = 0.0F;        // DAT_016b3c90 = DAT_015a7d44
  float bgBBoxMax = 0.0F;       // DAT_016b3c94 = DAT_015a7d3c + 10.0
  float bgVisibleMin = 0.0F;    // sVisibleBackgroundBBox = DAT_015a7d3c - 10.0
  float bgBBoxMax2 = 0.0F;      // DAT_016b3c98 = DAT_015a7d40 + 7.5
  float bgBBoxZ1 = 0.0F;        // DAT_016b3c9c = DAT_015a7d44

  // Read source constants (VERIFIED, SporeApp.exe 3.1.0.22 .data).
  static constexpr float kBBoxSrcX = 6.023681640625F;  // DAT_015a7d3c
  static constexpr float kBBoxSrcY = 3.5216064453125F; // DAT_015a7d40
  static constexpr float kBBoxSrcZ = 3.5372314453125F; // DAT_015a7d44

  // Reproduce the OBSERVABLE cCellGame::Initialize sequence (decompilation):
  // flag resets, time-scale load value, pool alloc (capacity 4096), and the
  // background-bbox writes.
  void initialize();

  // CreateCellObject @ 00e74a20 (1,689 B): pool alloc + fill the new
  // cCellObjectData from the resource, position, elevation, and scale. Returns
  // the pool index, or kInvalidIndex on exhaustion.
  //   cellSize 0 → base * resource.size * sizeFactor, base=(None?1:table/30)
  //   cellSize nonzero → sizeFactor * cellSize
  //   mOpacity=mTargetOpacity=1.0, field_AC=10.0, field_BC=cellSize.
  //   applySize → cellSize pushed into the transform uniform scale (0x58).
  //   targetOrientation nullptr → identity quat (yaw≈0); else copied.
  uint32_t createCellObject(
      const CellResourceSpec &resource,
      const float position[3],
      float elevation,
      CellStageScale scaleLevel,
      float sizeFactor,
      float cellSize,
      bool applySize,
      const float *targetOrientation);
  cCellObjectData *objectAt(uint32_t index) const {
    return mCells.at(index);
  }

  const CellDataReference &currentWorld() const { return mpCurrentWorld; }
  const CellDataReference &currentWorldBackground() const {
    return mpCurrentWorldBackground;
  }
  void setCurrentWorld(uint32_t id) { mpCurrentWorld.id = id; }
  void setCurrentWorldBackground(uint32_t id) {
    mpCurrentWorldBackground.id = id;
  }
  const cObjectPool<cCellObjectData> &cells() const { return mCells; }
};

} // namespace openspore::sim
