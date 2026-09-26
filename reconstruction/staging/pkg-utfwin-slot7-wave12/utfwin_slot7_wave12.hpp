#pragma once

#include <cstddef>
#include <cstdint>

// The observed body dereferences ECX before any write and terminates with
// "RET 0x8", so the callee pops two 4-byte stack words. That is __thiscall
// receiver-in-ECX with callee-owned stack cleanup; cdecl and fastcall are both
// excluded by the cleanup, and stdcall is excluded by the receiver register.
#if defined(_MSC_VER)
#define PKG_UTFWIN_SLOT7_THISCALL __thiscall
#else
#define PKG_UTFWIN_SLOT7_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_slot7_wave12 {

// Every word below is 4 bytes wide: the target performs two dword stores and
// its vtable siblings load dwords from the same receiver offsets.
using OpaqueWord = std::uint32_t;

// Receiver wire layout for the interface whose vtable slot +0x1c holds
// 0x00fc7e10. Offsets are physical offsets proven by the live disassembly of
// this vtable slot family; they are NOT semantic field names.
//
// Constructor evidence for the field map, read from the unique constructor of
// each of the three vtables that contain this slot:
//   0x00fc7f30 installs vtable 0x01491730 and zeroes +0x04, +0x08, +0x0c,
//               +0x18, +0x1c.
//   0x00fcde83 installs vtable 0x01492140 and additionally zeroes +0x20
//               through +0x38, with +0x2c written as a float.
//   0x00fd92aa CALLs 0x00fc7f30 and then installs vtable 0x01493990, so the
//               0x01493990 class derives from the 0x01491730 class.
// None of the three constructors writes +0x10 or +0x14, even though this
// target writes +0x10 and sibling slot +0x14 (0x00fc7e30) writes +0x14. That
// is an unresolved tension, recorded in the metadata sidecar; it is one reason
// no field name is asserted here.
struct OpaqueSlot7ReceiverWire {
  // +0x00: loaded and then indexed as a virtual table by 0x00fc7e60
  // (MOV EAX,[ESI]; MOV EDX,[EAX+0x3c]) and by 0x00fc7eb0
  // (MOV EAX,[ECX]; MOV EDX,[EAX+0x34]). A dispatch pointer, not a data word,
  // and the slot the three constructors above overwrite with the vtable.
  OpaqueWord dispatch_00 = 0;

  // +0x04: zeroed by all three constructors. No function in this vtable slot
  // family reads or writes it. The SDK-named
  // UTFWin::ImageDrawable::SetTiling at 0x00fd9460 does write this offset, but
  // that address is reachable from a different vtable (0x01493d00) and is
  // therefore NOT attributed to this receiver here.
  OpaqueWord unproven_04 = 0;

  // +0x08: written with the first stack word by 0x00fc7e10 (this target).
  // Zeroed by all three constructors. Read back as a dword by vtable slot
  // +0x20 at 0x0093b6c0 (MOV EAX,dword ptr [ECX + 0x8]; RET), and additionally
  // read by 0x00fc7ec0 at slot +0x48 of vtable 0x01493990, which loads it into
  // ECX and then executes it (MOV ECX,[ESI + 0x8] ... CALL ECX). The value is
  // therefore used as a CALL TARGET, so the first argument is installed as a
  // callable address. It is not named here, because "callable" describes the
  // observed use and not a proven declared type.
  OpaqueWord word_08 = 0;

  // +0x0c: written with the first stack word by vtable slot +0x14 at
  // 0x00fc7e30 and read back as a dword by vtable slot +0x18 at 0x00fc7e50
  // (MOV EAX,dword ptr [ECX + 0xc]; RET). Zeroed by all three constructors.
  // Sibling evidence, not this target.
  OpaqueWord word_0c = 0;

  // +0x10: written with the second stack word by 0x00fc7e10 (this target).
  // Read by 0x00fc7ec0 at slot +0x48, which pushes it and then calls the word
  // stored at +0x08 (MOV EDX,[ESI + 0x10]; PUSH EDX; ... CALL ECX, with
  // "ADD ESP, 0xc" after the call, so the callee takes three stack words and
  // the +0x10 word is the third of them). NOT initialised by any of the three
  // constructors, which is unresolved.
  OpaqueWord word_10 = 0;

  // +0x14: written with the second stack word by 0x00fc7e30 and read by
  // 0x00fc7ec0 at slot +0x48 (MOV ECX,dword ptr [ESI + 0x14]). NOT
  // initialised by any of the three constructors. Sibling evidence.
  OpaqueWord word_14 = 0;

  // +0x18 and +0x1c are used as a pair by 0x00fc7e60
  // (IMUL EAX,[ESI+0x1c]; IMUL EAX,[ESI+0x18]), by 0x00fc7e90
  // (IMUL EAX,[ESI+0x1c]; SHR EAX,0x3) and by 0x00fc7ec0, which compares an
  // incoming word against each in turn. Both are zeroed by all three
  // constructors. Sibling evidence, not this target.
  OpaqueWord word_18 = 0;
  OpaqueWord word_1c = 0;
};

// Reconstruction of 0x00fc7e10.
//
// Machine contract, read from the live x86-32 body (17 bytes, 5 instructions):
//   00fc7e10  8B 44 24 04        MOV EAX, dword ptr [ESP + 0x4]
//   00fc7e14  8B 54 24 08        MOV EDX, dword ptr [ESP + 0x8]
//   00fc7e18  89 41 08           MOV dword ptr [ECX + 0x8], EAX
//   00fc7e1b  89 51 10           MOV dword ptr [ECX + 0x10], EDX
//   00fc7e1e  C2 08 00           RET 0x8
//
// Leaf: no CALL, no conditional or unconditional branch, no read through the
// receiver before the two stores, no absolute address and therefore no global
// reference. The only side effects are the two dword stores.
//
// Reachability: the 4-byte little-endian pattern of 0x00fc7e10 occurs exactly
// three times in the whole image, all of them in .rdata vtable slots (the
// +0x1c slot of 0x01491730, 0x01492140 and 0x01493990). There is no direct
// caller; the function is reached only through virtual dispatch.
//
// Return register: EAX is never loaded with a value the body produces. EAX is
// left holding the first stack word because that word was loaded into EAX for
// the store at +0x08 and the register was then never reused. This model returns
// that word so the observable EAX state on exit is reproduced exactly; the
// evidence does not establish that the original source produced it
// deliberately, so the return remains an open question.
extern "C" OpaqueWord PKG_UTFWIN_SLOT7_THISCALL
re_00fc7e10_UTFWin_ImageDrawable_GetTiling(OpaqueSlot7ReceiverWire *self,
                                           OpaqueWord first_word,
                                           OpaqueWord second_word);

static_assert(sizeof(void *) == 4, "x86-32 pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "opaque receiver words are 32-bit");
static_assert(offsetof(OpaqueSlot7ReceiverWire, dispatch_00) == 0x00,
              "slot-family dispatch pointer offset");
static_assert(offsetof(OpaqueSlot7ReceiverWire, unproven_04) == 0x04,
              "slot-family placeholder offset");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_08) == 0x08,
              "first store target offset observed at 0x00fc7e18");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_0c) == 0x0c,
              "sibling pair first-field offset from 0x00fc7e30/0x00fc7e50");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_10) == 0x10,
              "second store target offset observed at 0x00fc7e1b");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_14) == 0x14,
              "sibling pair second-field offset from 0x00fc7e30");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_18) == 0x18,
              "sibling scaled-field offset from 0x00fc7e60/0x00fc7e90");
static_assert(offsetof(OpaqueSlot7ReceiverWire, word_1c) == 0x1c,
              "sibling scaled-field offset from 0x00fc7e60/0x00fc7e90");
static_assert(sizeof(OpaqueSlot7ReceiverWire) == 0x20,
              "covered prefix is a proven lower bound, not the object size");

}
