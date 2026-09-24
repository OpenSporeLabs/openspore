// Advect system (GetCurrentAdvectInfo @ 00e58ef0, GetNextAdvectID @ 00e58e30).
//
// The world carries a table of cAdvectEntry records (SDK 61863, 24 B). A scale
// value (the current player/world scale) is mapped to a discrete "bucket key"
// via a fixed threshold table (DAT_01483c14, VERIFIED from SporeApp.exe):
//   key(S) = clamp(floor(S/100) + 1, 1, 10)   (S==1000 -> 10, the _1K bucket).
//
// GetCurrentAdvectInfo: find the entry whose playerSize == key -> return its
//   (scaleLevel, strength, variance, period, advectID). If none matches, the
//   playerSize == -1 "default" entry is used; if neither, None (scaleLevel 0).
//
// GetNextAdvectID: find the entry whose playerSize == key + 1 -> return its
//   advectID; else the default entry's advectID; else 0.
//
// cAdvectEntry (SDK SIZE 0x18 = 24 B, VERIFIED offsets):
//   field_0   CellStageScale 0x00  (scale level this record is authored at)
//   playerSize CellStageScale 0x04 (bucket key; -1 == default/wildcard)
//   strength  float          0x08
//   variance  float          0x0c
//   period    float          0x10
//   advectID  uint32_t       0x14
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

namespace openspore::sim {

struct AdvectEntry {
  int32_t field_0 = 0;      // 0x00 scale level authored at
  int32_t playerSize = -1;  // 0x04 bucket key; -1 == default
  float strength = 0.0F;    // 0x08
  float variance = 0.0F;    // 0x0c
  float period = 0.0F;      // 0x10
  uint32_t advectID = 0;    // 0x14
};
static_assert(sizeof(AdvectEntry) == 0x18, "cAdvectEntry is 24 B");

struct AdvectInfo {
  int32_t scaleLevel = 0;  // None if nothing matched
  float strength = 0.0F;
  float variance = 0.0F;
  float period = 0.0F;
  uint32_t value = 0;  // the matched entry's advectID
};

enum class AdvectStatus { success, unsupported, failure };

struct AdvectSelectionResult {
  AdvectStatus status = AdvectStatus::success;
  bool matched = false;
  AdvectInfo info;

  explicit operator bool() const { return status == AdvectStatus::success; }
};

// The scale -> bucket-key mapping (matches the DAT_01483c14 table, VERIFIED).
inline int32_t bucketKeyForScale(int32_t scale) {
  if (scale >= 1000) {
    return 10;  // the _1K bucket (the ==1000 special case)
  }
  int32_t key = 1;
  if (scale > 0) {
    key = scale / 100 + 1;
  }
  if (key < 1) {
    key = 1;
  }
  if (key > 10) {
    key = 10;
  }
  return key;
}

// GetCurrentAdvectInfo: the advect record active at `scale`.
inline AdvectInfo getCurrentAdvectInfo(const std::vector<AdvectEntry>& entries,
                                       int32_t scale) {
  AdvectInfo info;
  const int32_t key = bucketKeyForScale(scale);
  for (const AdvectEntry& e : entries) {
    if (e.playerSize == key) {
      info.scaleLevel = e.field_0;
      info.strength = e.strength;
      info.variance = e.variance;
      info.period = e.period;
      info.value = e.advectID;
      return info;  // exact match: return immediately
    }
    if (e.playerSize == -1) {
      info.scaleLevel = e.field_0;
      info.strength = e.strength;
      info.variance = e.variance;
      info.period = e.period;
      info.value = e.advectID;  // remember the default
    }
  }
  return info;
}

// GetNextAdvectID: the advect ID one bucket ahead (key + 1).
inline uint32_t getNextAdvectID(const std::vector<AdvectEntry>& entries,
                                int32_t scale) {
  uint32_t id = 0;
  const int32_t key = bucketKeyForScale(scale);
  for (const AdvectEntry& e : entries) {
    if (e.playerSize == key + 1) {
      return e.advectID;
    }
    if (e.playerSize == -1) {
      id = e.advectID;
    }
  }
  return id;
}

inline AdvectSelectionResult getCurrentAdvectInfoResult(
    const std::vector<AdvectEntry>& entries, int32_t scale) {
  AdvectSelectionResult result;
  const int32_t key = bucketKeyForScale(scale);
  const AdvectEntry* fallback = nullptr;
  for (const AdvectEntry& entry : entries) {
    if (entry.playerSize == key) {
      result.matched = true;
      result.info = {entry.field_0, entry.strength, entry.variance,
                     entry.period, entry.advectID};
      return result;
    }
    if (entry.playerSize == -1) {
      fallback = &entry;
    }
  }
  if (fallback != nullptr) {
    result.matched = true;
    result.info = {fallback->field_0, fallback->strength, fallback->variance,
                   fallback->period, fallback->advectID};
  }
  return result;
}

inline AdvectSelectionResult getNextAdvectInfoResult(
    const std::vector<AdvectEntry>& entries, int32_t scale) {
  AdvectSelectionResult result;
  const int32_t key = bucketKeyForScale(scale) + 1;
  const AdvectEntry* fallback = nullptr;
  for (const AdvectEntry& entry : entries) {
    if (entry.playerSize == key) {
      result.matched = true;
      result.info = {entry.field_0, entry.strength, entry.variance,
                     entry.period, entry.advectID};
      return result;
    }
    if (entry.playerSize == -1) {
      fallback = &entry;
    }
  }
  if (fallback != nullptr) {
    result.matched = true;
    result.info = {fallback->field_0, fallback->strength, fallback->variance,
                   fallback->period, fallback->advectID};
  }
  return result;
}

class AdvectState {
 public:
  AdvectState() = default;
  explicit AdvectState(std::vector<AdvectEntry> entries)
      : entries_(std::move(entries)) {}

  void setEntries(std::vector<AdvectEntry> entries) {
    entries_ = std::move(entries);
  }

  AdvectSelectionResult current(int32_t scale) const {
    return getCurrentAdvectInfoResult(entries_, scale);
  }

  AdvectSelectionResult next(int32_t scale) const {
    return getNextAdvectInfoResult(entries_, scale);
  }

  const std::vector<AdvectEntry>& entries() const { return entries_; }

 private:
  std::vector<AdvectEntry> entries_;
};

}  // namespace openspore::sim
