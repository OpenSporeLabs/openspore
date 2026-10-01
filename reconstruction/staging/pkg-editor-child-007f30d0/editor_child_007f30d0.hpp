// PKG-EDITOR-CHILD-007F30D0 -- VA 0x007f30d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body. Eleven bytes, six instructions, no callees, no memory
// read, no memory write, one conditional branch:
//
//   007f30d0  85 C9       TEST ECX,ECX
//   007f30d2  74 04       JZ 0x007f30d8
//   007f30d4  8D 41 04    LEA EAX,[ECX + 0x4]
//   007f30d7  C3          RET
//   007f30d8  33 C0       XOR EAX,EAX
//   007f30da  C3          RET
//
// GhidraMCP /read_memory at 0x007f30d0 returns `85c974048d4104c333c0c3`
// for the first 16 bytes; the five bytes that follow are the inter-function
// pad (0xCC x5) in front of the next body, so nothing in this file reaches
// past 0x007f30da.
//
// WHAT THE BODY IS. A null-checked address computation on the receiver: when
// the receiver is nonzero, EAX receives the receiver's address plus four
// (LEA EAX,[ECX+0x4] -- an address formed, never a word loaded); when the
// receiver is zero, EAX receives zero (XOR EAX,EAX). Both arms terminate in a
// bare RET with no immediate byte, so the callee pops nothing.
//
// ABI. __thiscall, receiver in ECX, zero ordinary stack arguments, caller
// cleans. The convention is not read off the listing alone -- an 11-byte body
// of this shape is byte-identical under several conventions -- it is the
// V1-VFT inference in the evidence pack: 0x007f30d0 is a slot of vptr-backed
// vftables (slot 23 of 0x013f57f8, slot 23 of 0x01446590, slot 4 of
// 0x014086e8, slot 35 of 0x013fdc38; the engine counts five sound tables), so
// it is a non-static virtual member of some class; the callee pops nothing
// and no stack word is read as an argument, so the receiver is not in the
// popped area; ECX is the only register that carries one. The derived record
// agrees: conventions.calling_convention __thiscall, receiver.register ECX,
// stack_arguments.total_bytes 0, cleanup side caller. One direct call site
// corroborates from the caller side: 0x007f4f8b loads ECX from ESI
// immediately before `CALL 0x007f30d0` at 0x007f4f95, and 0x007f4f9a
// consumes EAX as a pointer (MOV EBP,EAX).
//
// CLASS IDENTITY. Not inferred. ICF-folded shared stubs mean this address is
// a virtual member of several classes at once; the evidence fixes the
// mechanic and never the class. The receiver is therefore an opaque byte run
// below and the pointee of the returned pointer is an opaque run too: the
// machine says the value is receiver+4 and says nothing about what lives
// there, so no member name and no pointee layout is asserted anywhere in
// this package.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "editor child 007f30d0 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_editor_child_007f30d0 {

using Word = std::uint32_t;

#if defined(_MSC_VER)
#define PKG_EDITOR_CHILD_007F30D0_THISCALL __thiscall
#else
#define PKG_EDITOR_CHILD_007F30D0_THISCALL __attribute__((thiscall))
#endif

// The receiver, as this body alone fixes it: an opaque byte run, and a name
// for nothing inside it. The machine-derived receiver record for this target
// is `bounds_only` with an empty offset set -- the LEA takes ECX's address
// without any memory access through it, so the record never saw a
// displacement it could enumerate. The run's size is the MODEL's own test
// affordance, not a claim about the real object: the model test plants
// decoy dwords at +0x0, +0x8, +0xc and +0x10 so that a reconstruction
// reading a neighbouring displacement is refuted rather than merely
// unimplemented. This body forms exactly one address, receiver+0x4, and
// reads nothing.
struct OpaqueReceiver {
  std::uint8_t opaque[0x100];
};

// The pointee of the returned pointer. Opaque for the same reason: the body
// computes receiver+4 and returns it; it never loads through it, so the
// pointee's width, layout and even its existence as a distinct object are
// all unevidenced. The name says what the machine says -- "the thing at
// receiver+4" -- and nothing more.
struct OpaqueChild {
  std::uint8_t opaque[0x100];
};

// The one displacement the body states, pinned to the instruction that states
// it. 0x007f30d4 is `8D 41 04`: 8D is LEA r32,r/m32, ModRM 41 is mod=01 (one
// disp8 follows), reg=000 (destination EAX), r/m=001 (address register ECX),
// and the disp8 is 04. This is the only address the function forms.
constexpr std::size_t kChildDisplacement = 0x4u;

static_assert(kChildDisplacement == 0x4u,
              "LEA EAX,[ECX+0x4] at 0x007f30d4 -- the disp8 is 4");
static_assert(sizeof(Word) == 4, "the receiver's word is 32-bit");
static_assert(sizeof(void*) == 4, "pointers are 32-bit on this target");
static_assert(sizeof(OpaqueReceiver) == 0x100,
              "the model test plants its last decoy dword at 0x10..0x13");

// extern "C" so the symbol name is findable verbatim by the model test's
// reinterpret_cast and by any future integration step.
extern "C" OpaqueChild* PKG_EDITOR_CHILD_007F30D0_THISCALL
editor_child_007f30d0(OpaqueReceiver* receiver);

#undef PKG_EDITOR_CHILD_007F30D0_THISCALL

}
