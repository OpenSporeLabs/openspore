#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg_sporepedia_641cd0_wave12 {

// ===========================================================================
// Target: 0x00641cd0, SporeApp.exe 3.1.0.22, image base 0x00400000.
//   117 instructions, 0x00641cd0..0x00641e0a, 315 bytes.
//   Disassembly: GhidraMCP /disassemble_function @ SporeApp.exe.
//   Decompiler output for this function was NOT used: it inverts the branch
//   polarity at 0x00641d0b and mis-sizes the call argument lists.
// ===========================================================================
//
// ABI, as observed:
//   __thiscall, receiver in ECX.
//   One 4-byte stack slot at entry_ESP+4, read as a byte (CMP BYTE PTR
//   [ESP+0x20],0 at 0x00641d02 after the frame is built). Termination is
//   RET 0x4 at 0x00641e08, so the callee pops the argument.
//   EBP/ESI/EDI are saved and restored. EAX carries the return value, which
//   no path in the body inspects and no epilogue instruction sets: the
//   return semantics are unclassified (see unresolved_questions).
//
// EBP IS NOT A FRAME POINTER. 0x00641cd4 is "MOV EBP,ECX" and there is no
// "MOV EBP,ESP" anywhere in the body, so EBP is a general register holding
// the receiver. Every [EBP+N] in this function is therefore a field of the
// receiver, never an entry-relative stack slot. The fields actually read are
// +0x04, +0x08, +0x0C, +0x1C and +0x70.

// ---------------------------------------------------------------------------
// Opaque receiver
// ---------------------------------------------------------------------------

struct SporepediaGameModeManager;
struct SporepediaHandle;
struct SporepediaRefCounted;

// Receiver of 0x00641cd0. Only the five offsets the body touches are named;
// the gaps are placeholders that exist solely to make the observed offsets
// assertable. The receiver's own class is NOT identified by this evidence
// (see unresolved_questions), so no SDK field names are used.
struct SporepediaAssetData {
  std::uint32_t vtable;     // +0x00 never read by this body
  std::uint32_t field_04;   // +0x04 copied into the descriptor w0
  std::uint32_t field_08;   // +0x08 loaded into ECX, provably unused
  std::uint32_t field_0c;   // +0x0C copied into the descriptor w2
  std::uint32_t gap_10[3];  // +0x10..+0x18
  std::uint32_t ref_1c;     // +0x1C intrusive-pointer style field
  std::uint32_t gap_20[20]; // +0x20..+0x6C
  std::uint32_t ref_70;     // +0x70 intrusive-pointer style field
  std::uint32_t field_74;   // +0x74
};

// ---------------------------------------------------------------------------
// Vtable layouts
// ---------------------------------------------------------------------------

// The manager returned by App::IGameModeManager::Get (0x0067dcd0). Its type
// is pinned by the SDK: AddressesApp.cpp declares
//   DefineAddress(Get, SelectAddress(0x67DE30, 0x67DCD0))
// so 0x0067dcd0 is App::IGameModeManager::Get in this build, and
// IGameModeManager.h fixes the slot order used below:
//   +0x00 AddRef, +0x04 Release, +0x08 ~IGameModeManager,
//   +0x0C Initialize, +0x10 Dispose.
// The SDK declares Initialize/Dispose as taking no parameters, so only the
// slot identity is corroborated, never the argument list; the argument lists
// below are read straight off the call sites.
struct SporepediaGameModeManagerVtable {
  void *slot_00;                            // +0x00
  void (*release)(SporepediaGameModeManager *); // +0x04
  void *slot_08;                            // +0x08
  // 0x00641db0, arg2 != 0 branch of the byte test is false: six stack
  // arguments, result tested with TEST AL,AL at 0x00641db2.
  std::uint8_t (*initialize)(SporepediaGameModeManager *, const std::uint32_t *,
                             std::uint32_t *, std::uint32_t, std::uint32_t,
                             std::uint32_t, std::uint32_t); // +0x0C
  // 0x00641d55, byte flag != 0 branch: eight stack arguments, result tested
  // with TEST AL,AL at 0x00641d57.
  std::uint8_t (*dispose)(SporepediaGameModeManager *, const std::uint32_t *,
                          std::uint32_t *, std::uint32_t *, std::uint32_t,
                          std::uint32_t, std::uint32_t, std::uint32_t,
                          std::uint32_t); // +0x10
};

// The object the manager writes into the out-parameter. Only three of its
// slots are reached: +0x04 (released), +0x00 and +0x04 (through the
// out-of-line assign at 0x00b5f950) and +0x0C (the type query).
struct SporepediaHandleVtable {
  void (*add_ref)(SporepediaHandle *);   // +0x00
  void (*release)(SporepediaHandle *);   // +0x04
  void *slot_08;                         // +0x08
  // 0x00641d75 and 0x00641dc8, always with the single argument 0x030bdee3.
  // The result is stored straight into ref_1c and dispatched on for +0x00
  // and +0x04, so it is a ref-counted object.
  SporepediaRefCounted *(*query_by_type)(SporepediaHandle *,
                                         std::uint32_t); // +0x0C
};

// An object whose address lands in ref_1c or ref_70. Only +0x00 and +0x04
// are ever dispatched on it.
struct SporepediaRefCountedVtable {
  void (*add_ref)(SporepediaRefCounted *); // +0x00
  void (*release)(SporepediaRefCounted *); // +0x04
};

struct SporepediaGameModeManager {
  SporepediaGameModeManagerVtable *vtable;
};

struct SporepediaHandle {
  SporepediaHandleVtable *vtable;
};

struct SporepediaRefCounted {
  SporepediaRefCountedVtable *vtable;
};

// ---------------------------------------------------------------------------
// The 16-byte local block built at entry_ESP-0x10
// ---------------------------------------------------------------------------
//
// 0x00641cf5 stores 0 at +0x00, 0x00641ce5 stores self->field_04 at +0x04,
// 0x00641ced stores the constant at +0x08 and 0x00641ce9 stores
// self->field_0c at +0x0C. 0x00641ce0 additionally stores self->field_08
// into +0x08, which 0x00641ced overwrites four instructions later: that store
// is dead, and the surviving value of +0x08 is the constant.
//
// The out handle occupies +0x00 and the descriptor occupies +0x04..+0x0F, so
// both call sites pass two pointers into the same 16 bytes: &block and
// &block.w0, adjacent and non-overlapping in what they write.
struct SporepediaInitBlock {
  std::uint32_t out_handle; // +0x00 written by the manager, read back after
  std::uint32_t w0;         // +0x04 = self->field_04
  std::uint32_t w1;         // +0x08 = 0x030bdee3
  std::uint32_t w2;         // +0x0C = self->field_0c
};

// The descriptor is the 12 bytes at +0x04. Its middle word is
// Pollinator::cAssetMetadata::TYPE, which CommonIDs.h lists as
// pollen_metadata = 0x30BDEE3. The same constant is the sole argument of
// SporepediaHandleVtable::query_by_type.
static const std::uint32_t kPollenMetadataTag = 0x030bdee3u;

// ---------------------------------------------------------------------------
// Observed offsets, asserted only where they are 32-bit facts
// ---------------------------------------------------------------------------

#if defined(__i386__) || defined(_M_IX86)
static_assert(sizeof(void *) == 4, "0x00641cd0 is an x86-32 reconstruction");

static_assert(offsetof(SporepediaAssetData, field_04) == 0x04,
              "0x00641ce5 reads the descriptor w0 from this+0x04");
static_assert(offsetof(SporepediaAssetData, field_08) == 0x08,
              "0x00641cd6 loads this+0x08 into ECX");
static_assert(offsetof(SporepediaAssetData, field_0c) == 0x0C,
              "0x00641ce9 reads the descriptor w2 from this+0x0C");
static_assert(offsetof(SporepediaAssetData, ref_1c) == 0x1C,
              "0x00641d78 and 0x00641dd0 operate on this+0x1C");
static_assert(offsetof(SporepediaAssetData, ref_70) == 0x70,
              "0x00641d22 and 0x00641d25 operate on this+0x70");

static_assert(offsetof(SporepediaGameModeManagerVtable, release) == 0x04,
              "vtable+0x04 is the release slot the body dispatches");
static_assert(offsetof(SporepediaGameModeManagerVtable, initialize) == 0x0C,
              "0x00641d99 reads the vtable+0x0C slot");
static_assert(offsetof(SporepediaGameModeManagerVtable, dispose) == 0x10,
              "0x00641d3b reads the vtable+0x10 slot");
static_assert(offsetof(SporepediaHandleVtable, release) == 0x04,
              "vtable+0x04 is the release slot on the out handle");
static_assert(offsetof(SporepediaHandleVtable, query_by_type) == 0x0C,
              "0x00641d6d and 0x00641dc0 read the vtable+0x0C slot");
static_assert(offsetof(SporepediaRefCountedVtable, add_ref) == 0x00,
              "0x00641ddd reads the vtable+0x00 slot");
static_assert(offsetof(SporepediaRefCountedVtable, release) == 0x04,
              "0x00641dec reads the vtable+0x04 slot");

static_assert(offsetof(SporepediaInitBlock, out_handle) == 0x00,
              "0x00641cf5 zeroes block+0x00");
static_assert(offsetof(SporepediaInitBlock, w0) == 0x04,
              "0x00641ce5 fills block+0x04");
static_assert(offsetof(SporepediaInitBlock, w1) == 0x08,
              "0x00641ced fills block+0x08");
static_assert(offsetof(SporepediaInitBlock, w2) == 0x0C,
              "0x00641ce9 fills block+0x0C");
static_assert(sizeof(SporepediaInitBlock) == 16, "the local block is 16 bytes");
#endif

// ---------------------------------------------------------------------------
// Direct callees, as opaque ports
// ---------------------------------------------------------------------------

// 0x0067dcd0, App::IGameModeManager::Get. Its whole body is
// "return DAT_015fd894", so it consumes neither the ECX the target loads
// (self->field_08, 0x00641ce0 path) nor any stack argument.
extern "C" SporepediaGameModeManager *
sporepedia_0067dcd0_app_igamemodemanager_get();

// 0x00b5f950, the out-of-line intrusive-pointer assignment the target calls
// at 0x00641d7b. Its body:
//   old = *slot; if (value != old) { if (value) value->slot_00();
//   *slot = value; if (old) old->slot_04(); } return slot;
// The target inlines the identical sequence at 0x00641dd0..0x00641df1, which
// is what corroborates the reading of this callee.
extern "C" std::uint32_t *sporepedia_00b5f950_intrusive_ptr_assign(
    std::uint32_t *slot, std::uint32_t value);

// ---------------------------------------------------------------------------
// Ports bundle for the testable model
// ---------------------------------------------------------------------------

struct Sporepedia641cd0Ports {
  using GetManager = SporepediaGameModeManager *(*)();
  using AssignRef = std::uint32_t *(*)(std::uint32_t *, std::uint32_t);
  GetManager get_manager_0067dcd0 = nullptr;
  AssignRef assign_ref_00b5f950 = nullptr;
};

// ---------------------------------------------------------------------------
// The recovered semantics
// ---------------------------------------------------------------------------
//
// Reads self->field_04, self->field_08 and self->field_0c, asks the active
// game mode manager to create or destroy an object described by those fields
// and tagged 0x030bdee3, and refreshes the intrusive-pointer field
// self->ref_1c from the object's +0x0C type query. The byte flag selects the
// direction: non-zero disposes (and first drops self->ref_70), zero
// initialises. On the way out the local out handle is released if the
// manager left it non-null.
void Sporepedia_00641cd0_model(SporepediaAssetData *self, std::uint8_t flag,
                               const Sporepedia641cd0Ports &ports);

// ---------------------------------------------------------------------------
// Byte-exact body
// ---------------------------------------------------------------------------
//
// Naked transcription of the 315 bytes at 0x00641cd0. Both direct calls go
// through the extern "C" ports above so the body links on a host toolchain.
// Original ABI: __thiscall, receiver in ECX, one 4-byte argument at
// entry_ESP+4, RET 0x4.
extern "C" void Sporepedia_00641cd0_raw(SporepediaAssetData *self,
                                        std::uint32_t flag);

// Host bridge, not part of the original body. Linux i386 clang has no
// usable __thiscall, so this entry stages the original frame (receiver in
// ECX, the argument at entry_ESP+4) and transfers into the body above, whose
// own RET 4 balances it.
extern "C" void Sporepedia_00641cd0_host_bridge(SporepediaAssetData *self,
                                                std::uint32_t flag);

// Drives the byte-exact body through the bridge. Original ABI: __thiscall.
void Sporepedia_00641cd0(SporepediaAssetData *self, std::uint8_t flag);

} // namespace openspore::reconstruction::pkg_sporepedia_641cd0_wave12
