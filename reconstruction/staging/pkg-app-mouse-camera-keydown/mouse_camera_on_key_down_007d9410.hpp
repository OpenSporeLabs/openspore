#pragma once

// Target 0x007d9410 - App::cMouseCamera::OnKeyDown
// SporeApp.exe 3.1.0.22, image base 0x00400000, x86-32.
//
// MACHINE EVIDENCE (this package reconstructs the entry point only)
// -----------------------------------------------------------------
// The complete listing collected for this target is two instructions, eight
// bytes, body span 0x007d9410..0x007d9417 (Ghidra body_start/body_end, size 8,
// classification "stub"):
//
//   007d9410  83 e9 04              SUB ECX,0x4
//   007d9413  e9 98 07 00 00        JMP 0x007d9bb0
//
// The machine-parse record is complete: declared_count 2, degraded false,
// unparsed 0, flow_complete true, local_extent 0, and the frame record shows
// push_ebp false, mov_ebp_esp false, and no ESP adjustment of any kind. The
// derived ABI record classifies this as a tail transfer (tail_call.present
// true, form "jmp", after_frame_setup false) and abstains from naming a
// receiver register (receiver.present false, register null) while still
// recording the adjustor delta it observed: -4. The dispatch record counts 0
// indirect calls, the listing contains no conditional branch, no memory operand
// through any register, and no data-segment address.
//
// What that establishes, and all this model claims:
//   1. exactly one arithmetic operation on the incoming receiver word: -4;
//   2. exactly one control transfer, unconditional and direct, to 0x007d9bb0;
//   3. no stack frame of its own (nothing pushed, nothing popped, no RET);
//   4. no field access, no global access, no branch, no indirect dispatch;
//   5. the word in the return register when control leaves the image is
//      whatever the transfer target leaves there - this body never writes it.
//
// WHAT IS *NOT* CLAIMED HERE, and why
// -----------------------------------
// 0x007d9bb0's body is outside this target's evidence. The persisted ABI record
// states that it ends in `POP ESI` / `RET 0x4` and that this entry therefore
// performs no stack cleanup of its own, and the record notes that the tail
// target drops one four-byte ordinary argument; nothing in this package's
// evidence describes what 0x007d9bb0 computes. It is therefore modelled as an
// opaque boundary reached through a port, and no behaviour is attributed to it.
//
// The persisted ABI record interprets the -4 as an MSVC adjustor thunk: ECX
// points at the subobject that carries the OnKeyDown virtual and the entry
// rewinds it to the cMouseCamera start. The derived record declines to call
// ECX a receiver at all, because the body only ever writes it. Both readings
// are compatible with two instructions and neither is established by them, so
// the model carries the arithmetic (which is observed) and treats the pointer's
// meaning as open.
//
// The SDK/Ghidra prototype stored on this symbol declares two four-byte
// ordinary stack slots, (int virtualKey, KeyModifiers modifiers). The machine
// for this entry shows one word being dropped. The model therefore forwards
// exactly the one word it is given and does not invent a preceding argument.
//
// Ghidra records exactly one data reference to this entry, from the word at
// 0x01412894, and the classifier associates the vtable words 0x007d93a0,
// 0x01412890 and 0x01412894 with this target. The binary carries no MSVC RTTI,
// so no class name, slot number or interface identity is claimed for any of
// them, and none of those addresses appears in the reconstructed code.
//
// The persisted decompilation
// (.spore-analysis/ghidra-exports/decompiled_sdk/App__cMouseCamera__OnKeyDown.c)
// reads the same body as `bVar1 = (bool)FUN_007d9bb0(); return bVar1;` - the
// target's result narrowed to bool and returned - which is the return handling
// modelled here. It also prints `/* WARNING: Unknown calling convention */` on
// this symbol and declares two ordinary stack parameters it never uses, and the
// live decompile of this address did not complete. Neither machine path can
// settle the convention, which is why the structural ABI check cannot reach
// PASS for this target however the source is written.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-app-mouse-camera-keydown requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_MCKD_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_MCKD_THISCALL __attribute__((thiscall))
#else
#error "pkg-app-mouse-camera-keydown requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_app_mouse_camera_keydown {

static_assert(sizeof(void*) == 4,
              "x86-32 target: pointers are 32-bit words");

// A machine word. The entry neither declares nor consumes any narrower type:
// the only word it produces is a register's worth of bits.
using OpaqueWord = std::uint32_t;
static_assert(sizeof(OpaqueWord) == 4, "target machine words are 32-bit");

// 0x007d9bb0 - the single direct transfer target named by the complete listing
// (`JMP 0x007d9bb0` at 0x007d9413) and by the xref export's one outgoing edge.
constexpr OpaqueWord kTailTargetVa = 0x007d9bb0u;

// The adjustor delta the machine records for this entry: `SUB ECX,0x4`. The
// entry's body spells the same value inline so the literal stands next to the
// instruction it came from; this constant is the same number for the boundary
// and for the model test to check against.
constexpr OpaqueWord kReceiverAdjustorBytes = 0x00000004u;
static_assert(kReceiverAdjustorBytes == 0x4u, "adjustor delta is four bytes");

// The view of the incoming receiver. The machine sees one word in the
// hidden-receiver register and this entry only ever subtracts from it, so the
// boundary type carries that word and nothing else: no member is read and no
// member is written anywhere in this package.
struct alignas(4) OpaqueListenerSubobject {
  OpaqueWord word;
};

// What the transfer target is handed. The entry states the receiver it rewound
// and the caller's own argument, and states that it pushed no frame of its own
// (a real target reached by a tail jump finds ESP exactly where its caller left
// it). It reads back the word the target leaves in the return register.
struct TailTransferBoundary {
  OpaqueWord receiver;          // word forwarded in the receiver register
  OpaqueWord argument;          // the caller's ordinary argument, verbatim
  OpaqueWord entry_frame_words; // words the entry pushed: zero, by evidence
  OpaqueWord eax;               // word the target leaves in the return register
};

// The boundary standing in for 0x007d9bb0. Its body is not this package's
// evidence, so the model calls a port and adopts whatever the port leaves in
// the return register. A null port models a target that is not reachable; the
// machine bytes do not exclude that and this model does not claim otherwise.
using TailTargetPort = void (*)(TailTransferBoundary* boundary);
extern TailTargetPort g_tail_target_007d9bb0;

// The observable shape of one execution of the entry.
struct EntryTrace {
  unsigned transfers;       // direct transfers out of the entry
  OpaqueWord target_va;     // where the single transfer went
  OpaqueWord receiver;      // receiver word the boundary saw
  OpaqueWord argument;      // argument word the boundary saw
  OpaqueWord entry_frame_words; // words the entry itself pushed
  OpaqueWord observed_eax;  // return word the caller observes
  bool branched;            // conditional control flow taken in the entry
  bool completed;           // the entry ran to its single successor
};
extern EntryTrace g_entry_trace_007d9410;

// `SUB ECX,0x4` as a word operation: the entry rewinds the receiver word it was
// given by four bytes, unconditionally, with no input special-cased. It is
// exposed separately because the pointer the entry receives is only ever a
// carrier for the word, and the word-level contract is the part a caller of the
// model can pin down over its whole range.
OpaqueWord rewind_receiver_007d9410(OpaqueWord receiver);

// 0x007d9410 - the assigned target. `SUB ECX,0x4` then `JMP 0x007d9bb0`.
// The declaration-site return type is bool, per the persisted ABI record and the
// SDK/Ghidra prototype; the value observed in the return register is the one
// the transfer target leaves there, which this body never writes.
extern "C" bool PKG_MCKD_THISCALL on_key_down_007d9410(
    OpaqueListenerSubobject* listener, OpaqueWord argument);

}  // namespace openspore::reconstruction::pkg_app_mouse_camera_keydown

#undef PKG_MCKD_THISCALL
