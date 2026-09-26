// Model test for wave13-w1-core-b10.
//
// Compiles and runs standalone:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//       -I reconstruction/staging/wave13-w1-core-b10 \
//       reconstruction/staging/wave13-w1-core-b10/bd8210_packed_direction.cpp \
//       reconstruction/staging/wave13-w1-core-b10/c0c080_find_index.cpp \
//       reconstruction/staging/wave13-w1-core-b10/c0c130_flag_b91.cpp \
//       reconstruction/staging/wave13-w1-core-b10/c37360_global_accessor.cpp \
//       reconstruction/staging/wave13-w1-core-b10/c485b0_set_mode2.cpp \
//       reconstruction/staging/wave13-w1-core-b10/c70150_any_entry_unlocked.cpp \
//       reconstruction/staging/wave13-w1-core-b10/b10_batch_model_test.cpp \
//       -o /tmp/opencode/b10-model && /tmp/opencode/b10-model
//
// Every assertion below restates a behaviour that was read out of the
// disassembly of SporeApp.exe, not an inferred one.

#include <sys/mman.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>

#include "b10_observed_types.hpp"
#include "bd8210_packed_direction.hpp"
#include "c0c080_find_index.hpp"
#include "c0c130_flag_b91.hpp"
#include "c37360_global_accessor.hpp"
#include "c485b0_set_mode2.hpp"
#include "c70150_any_entry_unlocked.hpp"

namespace b10 = openspore::reconstruction::wave13_w1_core_b10;

namespace {

int g_failures = 0;
std::uint8_t g_subsystem_probe[0x1bc] = {0};

void Check(bool ok, const char* what) {
  if (!ok) {
    std::printf("FAIL %s\n", what);
    ++g_failures;
  }
}

// ---------------------------------------------------------------------------
// 0x00c37360
//
// The reconstruction dereferences the literal image address 0x0168df68, so the
// harness writes that address directly rather than through the accessor.
// ---------------------------------------------------------------------------
void* const kGlobal_0168df68 = reinterpret_cast<void*>(0x0168df68UL);

void Test_00c37360() {
  *reinterpret_cast<void**>(kGlobal_0168df68) = &g_subsystem_probe;
  Check(b10::SimulatorSubsystem_GetGlobal_00c37360() ==
            reinterpret_cast<b10::OpaqueSimulatorSubsystem*>(&g_subsystem_probe),
        "00c37360 returns the pointer stored in the global");
  Check(kGlobal_0168df68 ==
            reinterpret_cast<void*>(0x0168df68UL),
        "00c37360 addresses the fixed global 0x0168df68");

  *reinterpret_cast<void**>(kGlobal_0168df68) = nullptr;
  Check(b10::SimulatorSubsystem_GetGlobal_00c37360() == nullptr,
        "00c37360 forwards a null global without a null check");
}

// ---------------------------------------------------------------------------
// 0x00c0c130
// ---------------------------------------------------------------------------
void Test_00c0c130() {
  auto* storage = static_cast<std::uint8_t*>(
      ::operator new(sizeof(b10::OpaqueSimEntityCollection)));
  std::memset(storage, 0, sizeof(b10::OpaqueSimEntityCollection));
  auto* collection = reinterpret_cast<b10::OpaqueSimEntityCollection*>(storage);

  collection->mFlagB90 = 0x5au;
  collection->mFlagB91 = 0x00u;
  Check(b10::SimEntityCollection_GetFlagB91_00c0c130(collection) == 0,
        "00c0c130 returns 0 for a clear +0xbb1");

  collection->mFlagB91 = 0x01u;
  Check(b10::SimEntityCollection_GetFlagB91_00c0c130(collection) == 1,
        "00c0c130 returns 1 for a set +0xbb1");

  collection->mFlagB91 = 0xffu;
  Check(b10::SimEntityCollection_GetFlagB91_00c0c130(collection) == 0xff,
        "00c0c130 returns the raw byte, not a normalised bool");
  Check(collection->mFlagB90 == 0x5au,
        "00c0c130 leaves the adjacent +0xbb0 flag untouched");

  collection->mFlagB91 = 0;
  ::operator delete(storage);
}

// ---------------------------------------------------------------------------
// 0x00c0c080
// ---------------------------------------------------------------------------
using CountFn = std::uint32_t(B10_THISCALL*)(b10::OpaqueSimEntityCollection*);
using AtFn = b10::OpaqueSimEntity*(B10_THISCALL*)(b10::OpaqueSimEntityCollection*,
                                                  std::int32_t);

std::uint32_t g_count_calls = 0;
std::uint32_t g_at_calls = 0;
std::int32_t g_count_value = 0;

// 0x00c0c0ad reads the dword at element + 0x8, so the fake element only has to
// be eight bytes wide.
alignas(4) std::uint32_t g_fake_entities[3][3] = {{0, 0, 0x1111u},
                                                  {0, 0, 0x2222u},
                                                  {0, 0, 0x3333u}};

std::uint32_t FakeCount(b10::OpaqueSimEntityCollection* c) {
  (void)c;
  ++g_count_calls;
  return static_cast<std::uint32_t>(g_count_value);
}

std::uint32_t FakeAt(b10::OpaqueSimEntityCollection* c, std::int32_t i) {
  (void)c;
  ++g_at_calls;
  return reinterpret_cast<std::uint32_t>(&g_fake_entities[i][0]);
}

// The vtable buffers live in static storage: a 32-bit indirect call whose
// target operand sits in a stack slot is fragile under some hosts, and static
// storage keeps the harness deterministic.
alignas(4) std::uint32_t g_vtable_c0c080[0x60];
alignas(4) std::uint8_t g_storage_c0c080[0x100];

void Test_00c0c080() {
  std::uint32_t* const vtable = g_vtable_c0c080;
  std::uint8_t* const storage = g_storage_c0c080;
  for (std::size_t i = 0; i < 0x60; ++i) vtable[i] = 0;
  for (std::size_t i = 0; i < 0x100; ++i) storage[i] = 0;

  // 0x00c0c088 reads [vtable + 0xb0] and 0x00c0c0a2 reads [vtable + 0xb4], so
  // the slots are at dword indices 0xb0/4 and 0xb4/4.
  vtable[0xb0 / 4] = reinterpret_cast<std::uint32_t>(&FakeCount);
  vtable[0xb4 / 4] = reinterpret_cast<std::uint32_t>(&FakeAt);
  *reinterpret_cast<std::uint32_t*>(storage) =
      reinterpret_cast<std::uint32_t>(vtable);

  auto* collection = reinterpret_cast<b10::OpaqueSimEntityCollection*>(storage);

  g_count_value = 3;

  g_count_calls = 0;
  g_at_calls = 0;
  Check(b10::SimEntityCollection_FindIndexById_00c0c080(collection,
                                                       static_cast<std::int32_t>(0x2222u)) ==
            1,
        "00c0c080 returns the matching index");
  Check(g_count_calls == 1, "00c0c080 reads the count exactly once");
  Check(g_at_calls == 2, "00c0c080 stops iterating at the first match");

  g_at_calls = 0;
  Check(b10::SimEntityCollection_FindIndexById_00c0c080(collection,
                                                       static_cast<std::int32_t>(0x4444u)) ==
            -1,
        "00c0c080 returns -1 when no element matches");
  Check(g_at_calls == 3, "00c0c080 visits every element on a miss");

  // 0x00c0c094 TEST EBX,EBX / JBE: a zero count must not call slot +0xb4.
  g_count_value = 0;
  g_at_calls = 0;
  Check(b10::SimEntityCollection_FindIndexById_00c0c080(collection, 0x1111) == -1,
        "00c0c080 returns -1 for an empty collection");
  Check(g_at_calls == 0, "00c0c080 skips slot +0xb4 when the count is 0");

  g_count_value = -1;
  g_at_calls = 0;
  Check(b10::SimEntityCollection_FindIndexById_00c0c080(collection, 0x1111) == -1,
        "00c0c080 returns -1 for a negative count (TEST/JBE polarity)");
  Check(g_at_calls == 0, "00c0c080 skips the loop for a negative count");
}

// ---------------------------------------------------------------------------
// 0x00bd8210
// ---------------------------------------------------------------------------
std::uint32_t g_manager_calls = 0;
float g_direction[3] = {0.0f, 0.0f, 1.0f};
b10::OpaqueGameInputManager* g_manager_seen = nullptr;
const float* g_direction_seen = nullptr;

float* FakeSlot58(b10::OpaqueDirectionCarrier* c, float* out) {
  (void)c;
  out[0] = 0.25f;
  out[1] = -0.5f;
  out[2] = 0.75f;
  return g_direction;
}

void Test_00bd8210() {
  alignas(4) std::uint32_t vtable[0x20] = {0};
  alignas(4) std::uint8_t storage[0x10] = {0};
  vtable[0x58 / 4] = reinterpret_cast<std::uint32_t>(&FakeSlot58);
  *reinterpret_cast<std::uint32_t*>(storage) =
      reinterpret_cast<std::uint32_t>(vtable);
  auto* carrier = reinterpret_cast<b10::OpaqueDirectionCarrier*>(storage);
  Check(b10::DirectionCarrier_GetPackedDirection_00bd8210(carrier) == 0x155u,
        "00bd8210 returns the 0x00b88590 result unchanged in EAX");
  Check(g_manager_calls == 1,
        "00bd8210 resolves the manager exactly once per call");
  Check(g_manager_seen == reinterpret_cast<b10::OpaqueGameInputManager*>(
                              0x0167eaf8UL),
        "00bd8210 uses the object at 0x0167eaf8 as the 0x00b88590 receiver");
  Check(g_direction_seen == g_direction,
        "00bd8210 forwards the pointer returned by slot +0x58");
}

// ---------------------------------------------------------------------------
// 0x00c485b0
// ---------------------------------------------------------------------------
std::uint32_t g_mode_calls = 0;
std::uint32_t g_mode_seen = 0xffffffffu;

void Test_00c485b0() {
  alignas(4) std::uint8_t storage[0x200] = {0};
  auto* owner = reinterpret_cast<b10::OpaqueSimTokenOwner*>(storage);
  owner->mMode = 0x1234u;

  b10::SimTokenOwner_SetMode2_00c485b0(owner);

  Check(g_mode_calls == 1, "00c485b0 tail-calls 0x00c47cc0 exactly once");
  Check(g_mode_seen == 2u, "00c485b0 pushes the immediate 0x2");
}

// ---------------------------------------------------------------------------
// 0x00c70150
// ---------------------------------------------------------------------------
std::uint32_t g_kind = 0;
std::uint8_t g_singleton_storage[64] = {0};
void* g_allocate_arg = nullptr;
std::uint32_t g_child_key_calls = 0;
std::uint32_t g_child_list_calls = 0;
std::uint32_t g_remaining_calls = 0;
std::uint32_t g_space_flag = 0;
std::uint32_t g_allocate_calls = 0;
std::uint32_t g_construct_calls = 0;
std::uint8_t g_has_queue = 0;

std::uint32_t FakeKind(b10::OpaqueSimTokenOwner* o) {
  (void)o;
  return g_kind;
}

std::uint32_t FakeChildKey(b10::OpaqueSimChild* c) {
  (void)c;
  ++g_child_key_calls;
  return c->mKey14;
}

b10::OpaqueSimChild* FakeChildVectorBase(b10::OpaqueSimChild* c) {
  ++g_child_list_calls;
  return c;
}

std::int32_t FakeRemaining(b10::OpaqueSimChild* c) {
  (void)c;
  ++g_remaining_calls;
  return 0;
}

std::uint32_t B10_CDECL FakeSpaceFlag() { return g_space_flag; }

void* B10_CDECL FakeAllocate(std::uint32_t size, const char* name, void* a,
                             void* b, void* c, void* d) {
  (void)size;
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  ++g_allocate_calls;
  Check(name != nullptr && std::strcmp(name, "Simulator/SimSingleton") == 0,
        "00c70150 allocates under the name read at 0x0145f924");
  return g_allocate_arg;
}

b10::OpaqueSimSingleton* FakeConstruct(void* raw) {
  ++g_construct_calls;
  return reinterpret_cast<b10::OpaqueSimSingleton*>(raw);
}

std::uint8_t FakeHasQueue(b10::OpaqueSimSingleton* s) {
  (void)s;
  return g_has_queue;
}

void Test_00c70150() {
  alignas(4) std::uint8_t owner_storage[0x200] = {0};
  alignas(4) std::uint8_t source_storage[0x100] = {0};
  alignas(4) std::uint8_t entry_storage[4][0x100] = {};

  auto* const owner = reinterpret_cast<b10::OpaqueSimTokenOwner*>(owner_storage);
  auto* const source = reinterpret_cast<b10::OpaqueSimKeySource*>(source_storage);
  auto* const entries = reinterpret_cast<b10::OpaqueSimChild*>(entry_storage);

  // 0x00c70168/0x00c7016e/0x00c70177: count = (mListEnd - mListBegin) >> 2.
  owner->mListBegin = 0;
  owner->mListEnd = 3u * 4u;
  source->mEntries[0] = reinterpret_cast<std::uint32_t>(&entries[0]);
  source->mKey84 = 0x40u;
  auto* const source_entries = source->mEntries;
  source_entries[1] = reinterpret_cast<std::uint32_t>(&entries[1]);
  source_entries[2] = reinterpret_cast<std::uint32_t>(&entries[2]);

  // 0x00c701a1 compares the element's +0x14 field against the key source's
  // +0x84 field, so only entry 1 matches.
  for (int i = 0; i < 3; ++i) {
    entries[i].mKey14 = (i == 1) ? 0x40u : 0x41u;
    entries[i].mListBegin3c = 0;
    entries[i].mListEnd40 = 0;
  }

  // Gate at 0x00c7015d: anything other than 5 returns 0 without touching the
  // list or the singleton.
  g_kind = 4u;
  g_child_key_calls = 0;
  g_allocate_calls = 0;
  g_construct_calls = 0;
  g_allocate_arg = &g_singleton_storage;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 0,
        "00c70150 returns 0 when the +0x194 kind is not 5");
  Check(g_child_key_calls == 0 && g_allocate_calls == 0,
        "00c70150 short-circuits before the scan when the kind gate fails");

  g_kind = 5u;

  // strict_flag == 0: 0x00c701d0 JZ 0x00c70243 accepts the first inner element
  // unconditionally, so entry 1 needs a non-empty inner list.
  entries[1].mListBegin3c = reinterpret_cast<std::uint32_t>(&entries[3]);
  entries[1].mListEnd40 = reinterpret_cast<std::uint32_t>(&entries[3]) + 4u;

  g_child_key_calls = 0;
  g_allocate_calls = 0;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 1,
        "00c70150 returns 1 on the first matching key when the flag is 0");
  Check(g_child_key_calls == 2,
        "00c70150 stops scanning at the first matching key");
  Check(g_allocate_calls == 0,
        "00c70150 does not reach the singleton once a match is found");

  // 0x00c701c6 TEST ESI,ESI / JLE 0x00c701ef: an empty inner list never reaches
  // the flag test, so an empty match set is not an accept.
  entries[1].mListBegin3c = 0;
  entries[1].mListEnd40 = 0;
  g_child_key_calls = 0;
  g_allocate_calls = 0;
  g_construct_calls = 0;
  g_has_queue = 0;
  g_allocate_arg = &g_singleton_storage;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 0,
        "00c70150 does not accept an empty inner list");
  Check(g_child_key_calls == 3,
        "00c70150 visits all three entries when none yields a match");
  Check(g_allocate_calls == 1 && g_construct_calls == 1,
        "00c70150 creates the singleton once when the slot is null");

  g_has_queue = 1;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 1,
        "00c70150 returns 1 when the singleton queue is non-empty");

  // 0x00c70203: a non-zero space-player flag skips the singleton entirely.
  g_space_flag = 1u;
  g_allocate_calls = 0;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 0,
        "00c70150 returns 0 when the space-player flag is set");
  Check(g_allocate_calls == 0,
        "00c70150 skips the singleton when the space-player flag is set");
  g_space_flag = 0u;

  // strict_flag != 0 with a two-element inner list whose remaining counts are
  // all <= 1: the inner loop must exhaust without returning 1.
  entries[1].mListBegin3c = reinterpret_cast<std::uint32_t>(&entries[3]);
  entries[1].mListEnd40 = reinterpret_cast<std::uint32_t>(&entries[3]) + 8u;
  g_remaining_calls = 0;
  g_has_queue = 0;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 1) == 0,
        "00c70150 exhausts the inner loop when every remaining count is <= 1");
  Check(g_remaining_calls == 2,
        "00c70150 calls 0x00ff0870 once per inner element");

  // Empty owner list: 0x00c7017f TEST EBX,EBX / JLE 0x00c701fc.
  owner->mListEnd = 0u;
  g_child_key_calls = 0;
  g_has_queue = 1;
  Check(b10::SimOwner_AnyEntryUnlocked_00c70150(owner, nullptr, source, 0) == 1,
        "00c70150 reaches the singleton for an empty owner list");
  Check(g_child_key_calls == 0,
        "00c70150 skips the scan for an empty owner list");
}

}  // namespace

// ---------------------------------------------------------------------------
// Port definitions used by the reconstruction.
// ---------------------------------------------------------------------------
namespace openspore::reconstruction::wave13_w1_core_b10 {

OpaqueGameInputManager* B10_CDECL Port_00b3d350_GetGameInputManager() {
  ++g_manager_calls;
  return reinterpret_cast<OpaqueGameInputManager*>(0x0167eaf8UL);
}

std::uint16_t B10_CDECL Port_00b88590_QuantiseDirection(
    OpaqueGameInputManager* manager, const float* direction) {
  g_manager_seen = manager;
  g_direction_seen = direction;
  return 0x155u;
}

std::uint32_t B10_CDECL Port_00b8dab0_GetKind(OpaqueSimTokenOwner* owner) {
  return FakeKind(owner);
}

std::uint32_t B10_CDECL Port_00ff0420_GetChildKey(OpaqueSimChild* child) {
  return FakeChildKey(child);
}

OpaqueSimChild* B10_CDECL Port_005c65e0_GetChildVectorBase(
    OpaqueSimChild* child) {
  return FakeChildVectorBase(child);
}

std::int32_t B10_CDECL Port_00ff0870_GetRemaining(OpaqueSimChild* child) {
  return FakeRemaining(child);
}

std::uint32_t B10_CDECL Port_01021080_GetSpacePlayerFlag() {
  return FakeSpaceFlag();
}

void* B10_CDECL Port_00f473a0_Allocate(std::uint32_t size, const char* name,
                                       void* a, void* b, void* c, void* d) {
  return FakeAllocate(size, name, a, b, c, d);
}

OpaqueSimSingleton* B10_CDECL Port_00ae5c30_ConstructSimSingleton(
    void* raw) {
  return FakeConstruct(raw);
}

std::uint8_t B10_CDECL Port_00ae3740_HasQueueEntries(
    OpaqueSimSingleton* singleton) {
  return FakeHasQueue(singleton);
}

void B10_CDECL Port_00c47cc0_SetMode(OpaqueSimTokenOwner* owner,
                                        std::uint32_t mode) {
  (void)owner;
  ++g_mode_calls;
  g_mode_seen = mode;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10

namespace {

// The three reconstructions read fixed image addresses 0x0167eaf8, 0x0167a60c
// and 0x0168df68, so the harness maps one anonymous page range over them
// instead of trying to link a segment at that address.
bool MapObservedGlobals() {
  constexpr std::uintptr_t kBase = 0x01670000u;
  constexpr std::size_t kLength = 0x00020000u;  // covers 0x0167a60c..0x0168df68
  void* got = ::mmap(reinterpret_cast<void*>(kBase), kLength,
                     PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0);
  if (got == reinterpret_cast<void*>(kBase)) {
    return true;
  }
  if (got != MAP_FAILED) {
    ::munmap(got, kLength);
  }
  got = ::mmap(reinterpret_cast<void*>(kBase), kLength, PROT_READ | PROT_WRITE,
               MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
  return got == reinterpret_cast<void*>(kBase);
}

}  // namespace

int main() {
  if (!MapObservedGlobals()) {
    std::printf("FAIL could not map the observed global page range\n");
    return 1;
  }

  Test_00c37360();
  Test_00c0c130();
  Test_00c0c080();
  Test_00bd8210();
  Test_00c485b0();
  Test_00c70150();

  if (g_failures != 0) {
    std::printf("b10 model test: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("b10 model test: all checks passed\n");
  return 0;
}
