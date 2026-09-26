#pragma once

#include <cstddef>
#include <cstdint>

// Wave 13 / wave1 / batch b10 — shared opaque types and opaque ports.
//
// Every layout byte in this header was read from SporeApp.exe (sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e) with
// ghidra_disassemble_function / ghidra_read_memory. SporeApp.exe carries no
// MSVC RTTI, so none of the types below carries an SDK class name: only the
// offsets that the disassembly actually touches are declared. Fields outside
// those offsets stay inside the `prefix` padding arrays.

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-core-b10 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave13_w1_core_b10 {

static_assert(sizeof(void*) == 4, "SporeApp.exe is x86-32");

// Modelling note for the whole package.
//
// Every function in this batch is an MSVC __thiscall member in the original:
// the receiver arrives in ECX. clang has no well-defined __thiscall for a free
// function, so the reconstructions and the opaque ports below all spell the
// receiver as an explicit first parameter and are declared cdecl. The observed
// ECX convention, the callee-cleaned stack words and the exact RET form are all
// recorded per target in reconstruction/metadata/wave13-w1-core-b10/.
#if defined(_MSC_VER)
#define B10_THISCALL __thiscall
#define B10_CDECL __cdecl
#else
#define B10_THISCALL __thiscall
#define B10_CDECL
#endif

// ---------------------------------------------------------------------------
// 0x0168df68 — the lazily created "Simulator" app-system instance.
//
// 0x00b61524..0x00b6152e : PUSH 0 ; PUSH 0x13f09b4 ; PUSH 0x1bc ; CALL 0x00f473a0
// 0x013f09b4 holds the ASCII string "Simulator", 0x1bc is the allocation size.
// 0x00b6153c : CALL 0x00c38c50 -> *param_1 = &PTR_FUN_0146bb78 (0x00c38c50:6)
// 0x00b5f5de..0x00b5f5e6 : vtable slot 0 with PUSH 1, then DAT_0168df68 = 0
// The class name is NOT established; only the vtable address and the size are.
// ---------------------------------------------------------------------------
struct OpaqueSimulatorSubsystem {
  std::uint8_t prefix[0x1bc];
};

// Target of the pointer at 0x00c0c0e8 / 0x00c0c180. 0x00c0c0e0 reads the byte
// at +0x388 of it and 0x00c0c100 reads the byte at +0x389. Never dereferenced
// beyond that by any function in this batch.
struct OpaqueSubsystem;

// ---------------------------------------------------------------------------
// 0x00c0c080 / 0x00c0c120 / 0x00c0c130 receiver.
//
// 0x00c0c080: MOV EAX,[EDI] then MOV EDX,[EAX + 0xb0] / MOV EDX,[EAX + 0xb4]
// 0x00c0c120: MOV AL,byte ptr [ECX + 0xbb0]
// 0x00c0c130: MOV AL,byte ptr [ECX + 0xbb1]
// 0x00c0c0d0: MOV EAX,dword ptr [ECX + 0xa60]
// 0x00c0c180: MOV dword ptr [ECX + 0xe84],EAX ; MOV [ECX + 0xe80],[EAX + 0x10]
// 0x00c0c1b0: MOV EAX,dword ptr [ECX + 0xb74]
// The vtable layout past slot +0x00 is not resolved: a positive-controlled scan
// of every dword in .rdata/.data found no vtable slot pointing at 0x00c0c080,
// 0x00c0c120, 0x00c0c130, 0x00c0c180, 0x00c0c1a0 or 0x00c0c0e0.
// ---------------------------------------------------------------------------
struct OpaqueSimEntityCollection {
  std::uint32_t vtable;          // +0x000
  std::uint8_t prefix0x04[0xa5c];
  std::uint32_t mFieldA60;       // +0xa60  0x00c0c0d0 MOV EAX,[ECX + 0xa60]
  std::uint8_t gap0xa64[0xd0];
  std::uint8_t mFieldB34[4];     // +0xb34  0x00c0c1c1 CMP dword ptr [ECX + 0xb34],1
  std::uint8_t gap0xb38[0x3c];
  std::uint32_t mFieldB74;       // +0xb74  0x00c0c1b0
  std::uint8_t gap0xb78[0x38];
  std::uint8_t mFlagB90;         // +0xbb0  0x00c0c120
  std::uint8_t mFlagB91;         // +0xbb1  0x00c0c130
  std::uint8_t gap0xbb2[0x2ce];
  std::uint32_t mFieldE80;       // +0xe80  0x00c0c180
  OpaqueSubsystem* mFieldE84;    // +0xe84  0x00c0c0e0 / 0x00c0c180
  std::uint8_t gap0xe88[0x974];
};

static_assert(offsetof(OpaqueSimEntityCollection, mFieldA60) == 0xa60,
              "0x00c0c0d0 reads [ECX + 0xa60]");
static_assert(offsetof(OpaqueSimEntityCollection, mFieldB34) == 0xb34,
              "0x00c0c1c1 reads [ECX + 0xb34]");
static_assert(offsetof(OpaqueSimEntityCollection, mFieldB74) == 0xb74,
              "0x00c0c1b0 reads [ECX + 0xb74]");
static_assert(offsetof(OpaqueSimEntityCollection, mFlagB90) == 0xbb0,
              "0x00c0c120 reads [ECX + 0xbb0]");
static_assert(offsetof(OpaqueSimEntityCollection, mFlagB91) == 0xbb1,
              "0x00c0c130 reads [ECX + 0xbb1]");
static_assert(offsetof(OpaqueSimEntityCollection, mFieldE80) == 0xe80,
              "0x00c0c180 writes [ECX + 0xe80]");
static_assert(offsetof(OpaqueSimEntityCollection, mFieldE84) == 0xe84,
              "0x00c0c0e0 / 0x00c0c180 touch [ECX + 0xe84]");

// Element yielded by virtual slot +0xb4 of OpaqueSimEntityCollection.
// 0x00c0c0ad: CMP dword ptr [EAX + 0x8],EBP is the only read made of it here.
struct OpaqueSimEntity {
  std::uint32_t vtable;
  std::uint8_t gap0x04[4];
  std::uint32_t mId;  // 0x00c0c0ad: CMP dword ptr [EAX + 0x8],EBP
};

static_assert(offsetof(OpaqueSimEntity, mId) == 0x8,
              "0x00c0c0ad compares the dword at element + 0x8");

// ---------------------------------------------------------------------------
// 0x00bd8210 receiver. Only two virtual slots are read:
//   0x00bd8212 : MOV EAX,dword ptr [EAX + 0x58]  with &local12 as the argument
//   0x00d043cf : MOV EDX,dword ptr [EAX + 0x4c]  no argument
// Nothing else of the receiver is touched, so nothing else is declared.
// ---------------------------------------------------------------------------
struct OpaqueDirectionCarrier {
  std::uint32_t vtable;
};

// ---------------------------------------------------------------------------
// 0x00c70150 argument 1 and 0x00c485b0 receiver share one layout, because
// 0x00c47cc0 and 0x00c70150 both address the same +0x15c/+0x160 pointer pair.
//   0x00c47cd3 : MOV dword ptr [ECX + 0x84],EAX
//   0x00c47ce9 : MOV word ptr [EAX],DX  at [ECX + 0x14c]
//   0x00c47cf2 : MOV dword ptr [ECX + 0x150],EAX
//   0x00c47d08 : MOV word ptr [EAX],DX  at [ECX + 0x15c]
//   0x00c47d11 : MOV dword ptr [ECX + 0x160],EAX
//   0x00c70168 : MOV EBX,dword ptr [ESI + 0x160]
//   0x00c7016e : SUB EBX,dword ptr [ESI + 0x15c]
//   0x00b8dab0 : MOV EAX,dword ptr [ECX + 0x194]
// ---------------------------------------------------------------------------
struct OpaqueSimTokenOwner {
  std::uint8_t prefix[0x84];
  std::uint32_t mMode;  // 0x84, written by 0x00c47cc0
  std::uint8_t gap0x88[0xc4];
  std::uint16_t mInlineBufferC;  // 0x14c, terminated with a 0 wchar
  std::uint8_t gap0x14e[0x2];
  std::uint32_t mInlineBufferC_end;  // 0x150
  std::uint8_t gap0x154[0x8];
  std::uint32_t mListBegin;  // 0x15c
  std::uint32_t mListEnd;    // 0x160
  std::uint8_t gap0x164[0x30];
  std::uint32_t mKind194;  // 0x194, compared against 5 by 0x00c70150
};

static_assert(offsetof(OpaqueSimTokenOwner, mMode) == 0x84,
              "0x00c47cd3 writes [ECX + 0x84]");
static_assert(offsetof(OpaqueSimTokenOwner, mInlineBufferC) == 0x14c,
              "0x00c47ce9 clears the wchar at +0x14c");
static_assert(offsetof(OpaqueSimTokenOwner, mInlineBufferC_end) == 0x150,
              "0x00c47cf2 rewinds +0x150 to +0x14c");
static_assert(offsetof(OpaqueSimTokenOwner, mListBegin) == 0x15c,
              "0x00c47d08 / 0x00c7016e address +0x15c");
static_assert(offsetof(OpaqueSimTokenOwner, mListEnd) == 0x160,
              "0x00c47d11 / 0x00c70168 address +0x160");
static_assert(offsetof(OpaqueSimTokenOwner, mKind194) == 0x194,
              "0x00b8dab0 reads [ECX + 0x194]");

// ---------------------------------------------------------------------------
// 0x00c70150 argument 3. Read as a dword array at offset 0 and as a dword at
// +0x84: 0x00c7019e MOV ESI,[EAX + EBP*0x4] and 0x00c701a1 MOV EDI,[ECX + 0x84]
// ---------------------------------------------------------------------------
struct OpaqueSimKeySource {
  std::uint32_t mEntries[1];
  std::uint8_t gap0x04[0x80];
  std::uint32_t mKey84;
};

// Element reached through 0x005c65e0, which returns param_1 + 0x3c.
// 0x00ff0420 (0x00ff0420:3) reads [param_1 + 0x14].
// 0x00ff0870 reads the dword at +0x24 and the byte at +0x28 and returns
// dword[+0x24] - popcount(byte[+0x28]).
struct OpaqueSimChild {
  std::uint8_t prefix[0x14];
  std::uint32_t mKey14;  // 0x00ff0420
  std::uint8_t gap0x18[0xc];
  std::uint32_t mTotal24;  // 0x00ff0870
  std::uint8_t mUsedMask28;  // 0x00ff0870 (MOVZX EAX,byte ptr [ECX + 0x28])
  std::uint8_t gap0x29[0x13];
  std::uint32_t mListBegin3c;
  std::uint32_t mListEnd40;
};

static_assert(offsetof(OpaqueSimChild, mKey14) == 0x14, "0x00ff0420");
static_assert(offsetof(OpaqueSimChild, mTotal24) == 0x24, "0x00ff0870");
static_assert(offsetof(OpaqueSimChild, mUsedMask28) == 0x28, "0x00ff0870");
static_assert(offsetof(OpaqueSimChild, mListBegin3c) == 0x3c,
              "0x005c65e0 returns param_1 + 0x3c");
static_assert(offsetof(OpaqueSimChild, mListEnd40) == 0x40,
              "0x00c701be SUB ESI,[EBP] / 0x00c701bb");

// 0x00ae3740 reads the pointer pair at +0x28 and returns
// (begin != end) as a byte, i.e. an emptiness predicate.
struct OpaqueSimSingleton {
  std::uint8_t prefix[0x28];
  std::uint32_t mQueueBegin;
  std::uint32_t mQueueEnd;
};

static_assert(offsetof(OpaqueSimSingleton, mQueueBegin) == 0x28,
              "0x00ae3740");

// 0x0167eaf8 holds the object returned by 0x00b3d350, which the SDK symbol
// import names Simulator::cGameInputManager::Get. Only +0x4c and +0x78 are read
// by 0x00b88590; the ModAPI header for cGameInputManager declares neither.
struct OpaqueGameInputManager {
  std::uint32_t vtable;
  std::uint8_t gap0x04[0x48];
  std::uint32_t mDirectionTable4c;  // 0x00b8874d MOV EAX,dword ptr [ESI + 0x4c]
  std::uint8_t gap0x50[0x28];
  std::uint8_t mTableDirty78;  // 0x00b88596 CMP byte ptr [ESI + 0x78],0
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never given invented bodies.
// ---------------------------------------------------------------------------

// 0x00b3d350: MOV EAX,[0x0167eaf8] ; RET. SDK import names it
// Simulator::cGameInputManager::Get. No arguments, no stack cleanup.
OpaqueGameInputManager* B10_CDECL Port_00b3d350_GetGameInputManager();

// 0x00b88590: __thiscall ushort(manager, const float* direction), RET 4.
// 6-face cube quantiser, 10-bit payload. See the body in
// c70150/bd8210 staging notes.
std::uint16_t B10_CDECL Port_00b88590_QuantiseDirection(
    OpaqueGameInputManager* manager, const float* direction);

// 0x00b8dab0: MOV EAX,dword ptr [ECX + 0x194] ; RET
std::uint32_t B10_CDECL Port_00b8dab0_GetKind(OpaqueSimTokenOwner* owner);

// 0x00ff0420: MOV EAX,dword ptr [ECX + 0x14] ; RET
std::uint32_t B10_CDECL Port_00ff0420_GetChildKey(OpaqueSimChild* child);

// 0x005c65e0: MOV EAX, param_1 + 0x3c ; RET. The caller then reads [ret] and
// [ret + 4] (0x00c701bb, 0x00c701be), which are the element's own dwords at
// +0x3c and +0x40, so the port returns the element unchanged.
OpaqueSimChild* B10_CDECL Port_005c65e0_GetChildVectorBase(OpaqueSimChild* child);

// 0x00ff0870: returns dword[+0x24] - popcount(byte[+0x28]) of the receiver.
std::int32_t B10_CDECL Port_00ff0870_GetRemaining(OpaqueSimChild* child);

// 0x01021080: returns dword ptr [Simulator::sSpacePlayerData + 0x10]
std::uint32_t B10_CDECL Port_01021080_GetSpacePlayerFlag();

// 0x00f473a0(size, name, a, b, c, d): 6 stack arguments, cdecl,
// ADD ESP,0x18 at every observed call site. Returns the new object or 0.
void* B10_CDECL Port_00f473a0_Allocate(std::uint32_t size, const char* name,
                                       void* a, void* b, void* c, void* d);

// 0x00ae5c30: constructor; it also writes DAT_0167a60c itself, and its vtable
// writes are PTR_FUN_0145b9ec then PTR_FUN_0145ba98 with PTR_FUN_0145b9c8 /
// PTR_FUN_0145ba74 at +0x8. Returns its own argument.
OpaqueSimSingleton* B10_CDECL Port_00ae5c30_ConstructSimSingleton(void* raw);

// 0x00ae3740: returns (byte)(*(this + 0x28) != this + 0x28)
std::uint8_t B10_CDECL Port_00ae3740_HasQueueEntries(
    OpaqueSimSingleton* singleton);

// 0x00c47cc0: __thiscall, one stack argument, RET 4. Full body in
// 0c4850/b10_c485b0_mode_set.cpp comments; the port keeps only the contract.
void B10_CDECL Port_00c47cc0_SetMode(OpaqueSimTokenOwner* owner,
                                     std::uint32_t mode);

}  // namespace openspore::reconstruction::wave13_w1_core_b10

// B10_THISCALL / B10_CDECL / B10_FASTCALL stay defined for the sibling headers.
