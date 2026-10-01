#pragma once

#include <cstddef>
#include <cstdint>

// 0x00fd9460 reads its only incoming argument at entry ESP+0x4 into EAX, moves
// ECX into ESI, and returns with "RET 0x4". A nonzero stack adjustment in the
// return form means the callee owns cleanup of the 4-byte stack word, and the
// receiver arrives in a register, so the contract is __thiscall.
#if defined(_MSC_VER)
#define PKG_UTFWIN_SETTILING_THISCALL __thiscall
#define PKG_UTFWIN_SETTILING_CDECL __cdecl
#define PKG_UTFWIN_SETTILING_NOINLINE __declspec(noinline)
#else
#define PKG_UTFWIN_SETTILING_THISCALL __attribute__((thiscall))
#define PKG_UTFWIN_SETTILING_CDECL __attribute__((cdecl))
#define PKG_UTFWIN_SETTILING_NOINLINE __attribute__((noinline))
#endif

namespace openspore::reconstruction::pkg_utfwin_settiling_wave13 {

// Every word below is 4 bytes wide. The target performs two dword stores and
// its accessor callee 0x011e58c0 loads and stores dwords at absolute addresses.
using OpaqueWord = std::uint32_t;

// Receiver wire layout for the class whose vtable is 0x01493d00. Offsets are
// physical offsets read from the live disassembly of the target and of the
// class constructor at 0x00fd95f0; they are NOT semantic field names.
//
// What this struct is, and what it is not. Every member name below is a
// displacement label, and the machine-derived receiver record for 0x00fd9460
// enumerates the two displacements the body was seen using (0x04 and 0x08) with
// `bounds_only` set -- that is, it records where the body reached and says
// nothing about which member occupies each offset. So no member here is a claim
// that the original class has a member of that name or meaning at that offset.
// The struct exists so the model test can observe the receiver byte-exactly
// before and after the call; the reconstructed body in the .cpp addresses the
// receiver by displacement alone and names nothing.
//
// Field-map evidence, and the limits of it:
//   0x00fd95f0 is the class constructor. It executes
//     MOV dword ptr [ESI], 0x1493d00
//   with ESI = ECX, which is what pins the vtable base of this class to
//   0x01493d00 and receiver +0x00 to the dispatch word. It conditionally calls
//   0x00f47380 and returns ESI, and it writes no field beyond +0x00. In
//   particular the constructor does NOT initialise +0x04 or +0x08, the two
//   offsets this target writes. That is recorded as an open tension in the
//   metadata sidecar and is one reason no semantic field name is asserted.
struct OpaqueSetTilingReceiverWire {
  // +0x00: dispatch word. Installed with the class vtable 0x01493d00 by the
  // constructor at 0x00fd95f0, and therefore the vtable pointer.
  OpaqueWord dispatch_00 = 0;

  // +0x04: written by 0x00fd9460 (this target) with the single incoming stack
  // word, stored verbatim. The Spore-ModAPI import names the corresponding
  // argument "tiling" of SDK type ImageTiling, and the store width is 4 bytes,
  // but no mask, range check, comparison or conversion is present in the body,
  // so the declared C++ type is NOT established. It is not named "tiling" here
  // because the import label is a candidate label, not machine evidence.
  OpaqueWord word_04 = 0;

  // +0x08: written by 0x00fd9460 (this target) with the dword returned by
  // 0x011e58c0. That callee is a lazy-initialisation accessor for a
  // process-wide static object, so the value is a pointer to that shared
  // object. The value is used by no other function in this reconstruction, so
  // the pointer's element type is NOT established and no name is asserted
  // beyond the observed origin.
  OpaqueWord shared_object_ptr_08 = 0;
};

// Accessor 0x011e58c0, reproduced for linkage and for the focused test only.
//
// Observed body (9 instructions, plain RET, no arguments, caller-cleanup):
//   011e58c0  8A 0D 08 4B 6F 01   MOV CL, byte ptr [0x016f4b08]
//   011e58c6  B8 01 00 00 00      MOV EAX, 0x1
//   011e58cb  84 C1               TEST AL, CL
//   011e58cd  75 10               JNZ  0x011e58df
//   011e58cf  09 05 08 4B 6F 01   OR   dword ptr [0x016f4b08], EAX
//   011e58d5  B9 04 4B 6F 01      MOV ECX, 0x16f4b04
//   011e58da  E8 90 FF FF FF      CALL 0x011e5870
//   011e58df  A1 F4 4A 6F 01      MOV EAX, dword ptr [0x016f4af4]
//   011e58e4  C3                  RET
//
// The 0x011e5870 it calls performs, per live decompilation:
//   if ((DAT_016f4b00 & 1) == 0) { DAT_016f4b00 |= 1; FUN_011eb950();
//                                 _atexit(FUN_013cb3f0); }
//   if (DAT_016f4af4 == 0) { DAT_016f4af4 = &DAT_016f4afc; }
// and FUN_011eb950 stores &PTR_LAB_014f6f80 into the object, i.e. it installs
// vtable 0x014f6f80 at the static object's first word, while FUN_013cb3f0 ->
// FUN_011eb940 installs vtable 0x0140de80 there at destruction time. The
// pointer slot 0x016f4af4 and the object storage 0x016f4afc are adjacent
// words, which is the layout that lets the atexit thunk find the object.
//
// This model reproduces the observable control flow and the identity of the
// returned pointer. It does not claim the C++ type of the static object.
//
// NOINLINE is required for fidelity, not for the test: in the original the
// accessor is a separate function reached by a real CALL, so inlining it would
// fold the guard bytes and the pointer slot into the target's body and destroy
// the one-instruction call the target actually makes.
extern "C" OpaqueWord PKG_UTFWIN_SETTILING_CDECL PKG_UTFWIN_SETTILING_NOINLINE
utfwin_shared_object_accessor_011e58c0();

// Absolute addresses of the globals the observed accessor body touches, kept
// as named constants so the test can assert the model never invents a store.
inline constexpr OpaqueWord kAccessorInitGuard_016f4b08 = 0x016f4b08u;
inline constexpr OpaqueWord kAccessorSecondGuard_016f4b00 = 0x016f4b00u;
inline constexpr OpaqueWord kAccessorPointerSlot_016f4af4 = 0x016f4af4u;
inline constexpr OpaqueWord kAccessorObjectStorage_016f4afc = 0x016f4afcu;
inline constexpr OpaqueWord kAccessorObjectVTable_014f6f80 = 0x014f6f80u;
inline constexpr OpaqueWord kAccessorObjectBaseVTable_0140de80 = 0x0140de80u;
inline constexpr OpaqueWord kConstructorCallGuard_016f4b10 = 0x016f4b10u;

// Reconstruction of 0x00fd9460 (SDK import name
// UTFWin::ImageDrawable::SetTiling).
//
// Machine contract, read from the live x86-32 body (20 bytes, 8 instructions):
//   00fd9460  8B 44 24 04         MOV EAX, dword ptr [ESP + 0x4]
//   00fd9464  56                   PUSH ESI
//   00fd9465  8B F1                MOV ESI, ECX
//   00fd9467  89 46 04             MOV dword ptr [ESI + 0x4], EAX
//   00fd946a  E8 51 C4 20 00       CALL 0x011e58c0
//   00fd946f  89 46 08             MOV dword ptr [ESI + 0x8], EAX
//   00fd9472  5E                   POP ESI
//   00fd9473  C2 04 00             RET 0x4
// Raw bytes 8b442404568bf1894604e851c420008946085ec2.
//
// Single basic block: no branch, no conditional. One direct call, to
// 0x011e58c0, whose target is encoded as a relative displacement and resolves
// to 0x011e58c0 from the next instruction address 0x00fd946f. No absolute
// address is referenced by the target itself, so it touches no global
// directly; the globals in the list above belong to its callee.
//
// Return: void. EAX holds the callee's result at the moment it is stored to
// receiver +0x08 and is never forwarded to the caller, and the imported
// prototype is void. The target therefore produces no return value.
//
// Reachability: the 4-byte little-endian pattern of 0x00fd9460 occurs exactly
// ONCE in the whole image, at VA 0x01493d68 in .rdata. That is vtable
// 0x01493d00 plus 0x70, so the function has no direct caller and is reached
// only through virtual dispatch.
extern "C" void PKG_UTFWIN_SETTILING_THISCALL
set_tiling_00fd9460(OpaqueSetTilingReceiverWire *self, OpaqueWord tiling);

static_assert(sizeof(void *) == 4, "x86-32 pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "opaque receiver words are 32-bit");
static_assert(offsetof(OpaqueSetTilingReceiverWire, dispatch_00) == 0x00,
              "dispatch word offset from MOV [ESI],0x1493d00 at 0x00fd95f8");
static_assert(offsetof(OpaqueSetTilingReceiverWire, word_04) == 0x04,
              "first store target offset observed at 0x00fd9467");
static_assert(offsetof(OpaqueSetTilingReceiverWire, shared_object_ptr_08) ==
                  0x08,
              "second store target offset observed at 0x00fd946f");
static_assert(sizeof(OpaqueSetTilingReceiverWire) == 0x0c,
              "covered prefix is a proven lower bound, not the object size");

}
