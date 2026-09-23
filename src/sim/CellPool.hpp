// cObjectPool<T> — clean-room re-implementation of Spore's free-list object
// pool (SDK struct cObjectPool<cCellObjectData>, 28 B, 7 fields):
//
//   void*  mpData                  preallocated buffer of mNumObjects objects
//   int    mNextAvailableIndex     head of the free list (object index)
//   int    mObjectPoolIdentifier   pool id
//   int    mNumObjects             capacity
//   int    mNumAllocatedObjects    live object count
//   int    mObjectSize             sizeof(T)
//   int    field_18
//
// Each object's FIRST word (mObjectPoolIndex) doubles as the free-list "next"
// link while free and the object's own index while allocated — the classic
// Spore/EA free-list pool. VERIFIED capacity 4,096 (0x1000) for the main cell
// pool (cCellGame::Initialize allocation, docs/analysis/dossiers).
#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::sim {

// Re-layout of SDK cCellObjectData (SIZE 0x398 = 920 B) at its true offsets,
// with padding to reproduce the exact element size (the pool allocates
// sizeof(cCellObjectData) per object). Named fields are the ones the cell
// stage reads/writes (CS-15/16/17/18); the rest are opaque padding blocks.
//   mTargetSize(0xb4) field_B8(0xb8) field_BC(0xbc)  <- field_BC holds the
//   computed cellSize (CreateCellObject line 125: puVar6[0x2d]=cellSize).
//   field_AC(0xac)=10.0, mOpacity(0xa0)/mTargetOpacity(0xa4)=1.0.
//   mModelKey(0xfc), mRelativeElevation(0x80), mScaleLevel(0x358).
struct cCellObjectData {
  uint32_t mObjectPoolIndex = 0xFFFFFFFFu;  // 0x00  own index / free-list next
  uint8_t mIsIdle = 1;                      // 0x04
  float mTargetPosition[3] = {0.0F, 0.0F, 0.0F};  // 0x08
  float mTargetOrientation[4] = {0.0F, 0.0F, 0.0F, 1.0F};  // 0x14
  uint8_t _pad_24[0x48 - 0x24];            // 0x24 field_24/30/3C/40/44
  uint8_t mTransform[0x38];                // 0x48 Transform (56 B)
  float mRelativeElevation = 0.0F;         // 0x80
  float field_84[3] = {0.0F, 0.0F, 0.0F};  // 0x84
  float field_90[3] = {0.0F, 0.0F, 0.0F};  // 0x90
  int32_t field_9C = 0;                    // 0x9c
  float mOpacity = 1.0F;                   // 0xa0
  float mTargetOpacity = 1.0F;             // 0xa4
  float field_A8 = 0.0F;                   // 0xa8
  float field_AC = 0.0F;                   // 0xac  (10.0 after create)
  int32_t field_B0 = 0;                    // 0xb0
  float mTargetSize = 1.0F;                // 0xb4
  float field_B8 = 0.0F;                   // 0xb8
  float field_BC = 0.0F;                   // 0xbc  computed cellSize
  uint8_t _pad_c0[0xfc - 0xc0];           // 0xc0 field_C0 (Transform 56) + field_F8
  uint32_t mModelKey[3] = {0, 0, 0};      // 0xfc ResourceKey {group,type,instance}
  uint8_t _pad_108[0x358 - 0x108];        // 0x108 mCellResource + bools + int fields
  int32_t mScaleLevel = -1;               // 0x358 CellStageScale
  uint8_t _pad_end[0x398 - 0x35c];        // 0x35c
};
static_assert(sizeof(cCellObjectData) == 0x398, "cCellObjectData is 920 B");
static_assert(offsetof(cCellObjectData, mTargetPosition) == 0x08, "");
static_assert(offsetof(cCellObjectData, mTargetOrientation) == 0x14, "");
static_assert(offsetof(cCellObjectData, mRelativeElevation) == 0x80, "");
static_assert(offsetof(cCellObjectData, mOpacity) == 0xa0, "");
static_assert(offsetof(cCellObjectData, mTargetSize) == 0xb4, "");
static_assert(offsetof(cCellObjectData, field_BC) == 0xbc, "");
static_assert(offsetof(cCellObjectData, mModelKey) == 0xfc, "");
static_assert(offsetof(cCellObjectData, mScaleLevel) == 0x358, "");

template <typename T>
class cObjectPool {
public:
  static constexpr uint32_t kInvalidIndex = 0xFFFFFFFFu;

  // SDK cObjectPool fields (see header comment).
  void *mpData = nullptr;
  int32_t mNextAvailableIndex = 0;
  int32_t mObjectPoolIdentifier = 0;
  int32_t mNumObjects = 0;
  int32_t mNumAllocatedObjects = 0;
  int32_t mObjectSize = 0;
  int32_t field_18 = 0;

  cObjectPool() = default;
  ~cObjectPool() { release(); }

  cObjectPool(const cObjectPool &) = delete;
  cObjectPool &operator=(const cObjectPool &) = delete;

  // Preallocate `capacity` zeroed objects and build the free list: object i
  // links to i+1, the last to kInvalidIndex, head at index 0.
  void initialize(uint32_t capacity, int32_t id = 0) {
    release();
    mObjectSize = static_cast<int32_t>(sizeof(T));
    mNumObjects = static_cast<int32_t>(capacity);
    mObjectPoolIdentifier = id;
    mNumAllocatedObjects = 0;
    if (capacity == 0) {
      mNextAvailableIndex = static_cast<int32_t>(kInvalidIndex);
      return;
    }
    mpData = new uint8_t[static_cast<size_t>(capacity) * sizeof(T)]();
    T *buf = reinterpret_cast<T *>(mpData);
    for (uint32_t i = 0; i < capacity; ++i) {
      buf[i].mObjectPoolIndex =
          (i + 1 < capacity) ? i + 1 : static_cast<uint32_t>(kInvalidIndex);
      buf[i].mIsIdle = true;
    }
    mNextAvailableIndex = 0;
  }

  // Pop the free-list head. Returns nullptr on exhaustion (pool full).
  T *allocate() {
    if (mNextAvailableIndex < 0 ||
        mNextAvailableIndex == static_cast<int32_t>(kInvalidIndex)) {
      return nullptr;
    }
    T *buf = reinterpret_cast<T *>(mpData);
    uint32_t obj = static_cast<uint32_t>(mNextAvailableIndex);
    int32_t next = static_cast<int32_t>(buf[obj].mObjectPoolIndex);
    buf[obj].mObjectPoolIndex = obj;  // now allocated: own index
    buf[obj].mIsIdle = false;
    mNextAvailableIndex = next;
    ++mNumAllocatedObjects;
    return buf + obj;
  }

  // Push `obj` back onto the free-list head.
  void deallocate(T *obj) {
    if (!obj) {
      return;
    }
    uint32_t i = index(obj);
    if (i >= static_cast<uint32_t>(mNumObjects)) {
      return;
    }
    T *buf = reinterpret_cast<T *>(mpData);
    buf[i].mIsIdle = true;
    buf[i].mObjectPoolIndex = static_cast<uint32_t>(mNextAvailableIndex);
    mNextAvailableIndex = static_cast<int32_t>(i);
    --mNumAllocatedObjects;
  }

  uint32_t index(const T *obj) const {
    const T *buf = reinterpret_cast<const T *>(mpData);
    return static_cast<uint32_t>(obj - buf);
  }
  T *at(uint32_t i) const {
    return i < static_cast<uint32_t>(mNumObjects)
               ? reinterpret_cast<T *>(mpData) + i
               : nullptr;
  }
  bool isAllocated(const T *obj) const {
    uint32_t i = index(obj);
    return i < static_cast<uint32_t>(mNumObjects) &&
           obj->mObjectPoolIndex == i;
  }

private:
  void release() {
    if (mpData) {
      delete[] static_cast<uint8_t *>(mpData);
      mpData = nullptr;
    }
  }
};

} // namespace openspore::sim
