// Cell query (SDK structs 61895/61894/61893) — clean-room re-implementation.
//
// The original keeps a cCellQueryLinkedPool (16 B) over a
// cCellQueryLinkedPoolData (24 B) arena of cCellQueryEntry nodes (28 B each).
// A position query walks the entry list and returns the pool indices of cells
// whose surface reaches the query region. It is consumed by steering (flee:
// find nearby prey) and attack logic.
//
// cCellQueryEntry (SDK SIZE 0x1c = 28 B, VERIFIED offsets):
//   mPosition  Vector3  0x00
//   mCellSize  float    0x0c
//   field_10   int      0x10
//   mpNext     ptr      0x14   (modelled as an arena index; -1 == null)
//   mCellIndex cObjectPoolIndex 0x18
//
// Near predicate (observable contract): a cell at C with size S is inside the
// query at P with radius R iff |C - P| <= S + R (the cell's surface reaches the
// query sphere). Border (touching) counts as in-range.
#pragma once

#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>

namespace openspore::sim {

struct CellQueryEntry {
  float mPosition[3] = {0.0F, 0.0F, 0.0F};  // 0x00
  float mCellSize = 0.0F;                   // 0x0c
  int32_t field_10 = 0;                     // 0x10
  int32_t mpNext = -1;                      // 0x14 (arena index; -1 == null)
  uint32_t mCellIndex = 0xFFFFFFFFu;        // 0x18
};
static_assert(sizeof(CellQueryEntry) == 0x1c, "cCellQueryEntry is 28 B");

enum class CellQueryStatus { success, unsupported, failure };

struct CellQueryResult {
  CellQueryStatus status = CellQueryStatus::success;
  std::vector<uint32_t> indices;

  explicit operator bool() const { return status == CellQueryStatus::success; }
};

class CellQuery {
 public:
  CellQuery() = default;
  ~CellQuery() = default;
  CellQuery(const CellQuery&) = delete;
  CellQuery& operator=(const CellQuery&) = delete;

  void reserve(uint32_t maxObjects) { mEntries.reserve(maxObjects); }

  CellQueryResult addCellResult(uint32_t index, const float position[3],
                                float cellSize) {
    if (position == nullptr || !std::isfinite(position[0]) ||
        !std::isfinite(position[1]) || !std::isfinite(position[2]) ||
        cellSize < 0.0F || !std::isfinite(cellSize) || index == 0xFFFFFFFFu) {
      return {CellQueryStatus::failure, {}};
    }
    CellQueryEntry e;
    e.mPosition[0] = position[0];
    e.mPosition[1] = position[1];
    e.mPosition[2] = position[2];
    e.mCellSize = cellSize;
    e.mCellIndex = index;
    e.mpNext = mHead;
    mHead = static_cast<int32_t>(mEntries.size());
    mEntries.push_back(e);
    return {CellQueryStatus::success, {index}};
  }

  uint32_t addCell(uint32_t index, const float position[3], float cellSize) {
    return addCellResult(index, position, cellSize).status ==
                   CellQueryStatus::success
               ? index
               : 0xFFFFFFFFu;
  }

  uint32_t count() const { return static_cast<uint32_t>(mEntries.size()); }

  void clear() {
    mHead = -1;
    mEntries.clear();
  }

  CellQueryResult queryNearResult(const float position[3], float radius) const {
    if (position == nullptr || radius < 0.0F || !std::isfinite(radius)) {
      return {CellQueryStatus::failure, {}};
    }
    std::vector<uint32_t> out;
    for (int32_t i = mHead; i >= 0; i = mEntries[i].mpNext) {
      const CellQueryEntry& e = mEntries[i];
      float dx = e.mPosition[0] - position[0];
      float dy = e.mPosition[1] - position[1];
      float dz = e.mPosition[2] - position[2];
      float dist = std::sqrt(dx * dx + dy * dy + dz * dz);
      if (dist <= e.mCellSize + radius) {
        out.push_back(e.mCellIndex);
      }
    }
    return {CellQueryStatus::success, std::move(out)};
  }

  std::vector<uint32_t> queryNear(const float position[3], float radius) const {
    return queryNearResult(position, radius).indices;
  }

 private:
  int32_t mHead = -1;
  std::vector<CellQueryEntry> mEntries;
};

}  // namespace openspore::sim
