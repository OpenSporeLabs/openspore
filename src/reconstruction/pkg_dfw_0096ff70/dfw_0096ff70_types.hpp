// PKG-DFW-0096FF70 -- VA 0x0096ff70
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22,
//  binary sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Opaque boundary types for the reconstruction of the two-instruction body at
// 0x0096ff70.
//
// Nothing in this header names a class, a base class, a member, a field or a
// dispatch slot, and that is a deliberate abstention rather than an omission:
//
//  * The machine-derived ABI record for this target names no receiver register
//    at all. It records receiver.present = false, register = null,
//    bounds_only = true and distinct_offsets = 0, with the stated basis
//    "ECX is never read in any form". That is literally true of the two
//    instructions at 0x0096ff70 and 0x0096ff73: SUB ECX,0x0C writes ECX and
//    never reads it, and the jump reads nothing at all. A record that observes
//    no memory operand through any register cannot say which member any
//    displacement is, and here there is not even a displacement.
//
//  * The type list the evidence pack does carry for this target
//    ("GlideEffect (UTFWin::GlideEffect, SDK SIZE 0x70, 32-bit)",
//     "GlideEffectVTableRun (pointer run based at 0x01442584, 4 transcribed
//     slots)", "OpaqueVtable (4 opaque slots, ...)", "uint32", "void") is a
//    list of type *names* gathered by the projection. This package does not
//    declare UTFWin::GlideEffect, because nothing in the body reaches inside
//    the object it is handed: the body performs no load and no store, so a
//    layout of the receiver would be decoration attached to no observation.
//
//  * The only reference to 0x0096ff70 in the whole image is a DATA pointer at
//    0x0144258c, byte offset +0x08 of a four-plus-word pointer run based at
//    0x01442584 (read live during this session: 0x00e246c0, 0x00805630,
//    0x0096ff70, 0x0096ff90, 0x0096ff50, ...). Ghidra's vtable detection never
//    ran on this program, so the run is a run and not a proven vftable, and the
//    slot this address occupies is not identified as any particular interface.
//    The run is recorded here as a comment and modelled nowhere in code.
//
// The two pointer types below are therefore distinct and both incomplete. The
// distinction is the one the machine makes: the thunk is handed one pointer,
// rewrites it by -0x0C, and the address the jump reaches is a different
// pointer. Declaring one type for both would assert they are the same object,
// which nothing here supports.

#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-dfw-0096ff70 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_dfw_0096ff70 {

using Word = std::uint32_t;

// The calling conventions below are spelled per toolchain. GCC and clang reject
// the MSVC keywords outright on x86 and only accept the attribute form, so a
// package that hard-codes __thiscall does not build with the compiler this
// repository builds with. PKG_DFW_0096FF70_THISCALL is the convention this
// body is declared with, and the reason is stated rather than assumed:
//
//  * the hidden receiver arrives in a register (ECX), which is what the
//    persisted ABI record calls "thiscall adjustor thunk with one forwarded
//    stack word";
//  * the single ordinary stack word is removed by the frame's only terminal
//    RET, which is RET 0x4 at 0x00970006 inside the tail target, so the
//    callee owns the cleanup. That is callee-cleaned behaviour, which is what
//    distinguishes thiscall and stdcall from cdecl.
//
// The counter-reading is on the record and is not hidden: the machine-derived
// ABI record abstains from naming any convention at all
// (conventions.calling_convention = null, confidence UNKNOWN,
// verdict ABI_UNKNOWN, abstained_because "no_terminal_ret: the only exit
// observed is a tail jump"), and Ghidra's own decompilation of this body
// carries the banner "WARNING: Unknown calling convention". thiscall is
// therefore an inference from the tail target's own listing plus the shape of
// the frame, and it is the best-supported reading rather than a proven one.
#if defined(_MSC_VER)
#define PKG_DFW_0096FF70_THISCALL __thiscall
#define PKG_DFW_0096FF70_CDECL __cdecl
#else
#define PKG_DFW_0096FF70_THISCALL __attribute__((thiscall))
#define PKG_DFW_0096FF70_CDECL __attribute__((cdecl))
#endif

// The immediates the two-instruction listing fixes, transcribed from the live
// disassembly of 0x0096ff70 re-read during this session:
//
//   83 e9 0c          SUB ECX,0x0C
//   e9 58 00 00 00    JMP 0x0096FFD0   (rel32 = 0x58 from the next address)
//
// Nothing else in the body is a constant.

// 0x0096ff70  SUB ECX,0x0C -- the receiver adjustment, in bytes.
inline constexpr std::size_t kReceiverAdjustmentBytes = 0x0cu;

// 0x0096ff73  JMP 0x0096FFD0 -- the one direct transfer out of the body.
inline constexpr Word kTailTargetAddress = 0x0096ffd0u;

// The rel32 displacement of that jump, 0x58. The next address after the
// instruction is 0x0096ff78, and 0x0096ff78 + 0x58 = 0x0096ffd0. The static
// assertion below ties the two transcribed constants to each other, so a
// package that changed either one alone would fail to build rather than model
// a jump the listing does not contain.
inline constexpr std::size_t kTailJumpRel32 = 0x58u;
inline constexpr Word kTailJumpInstructionEnd = 0x0096ff78u;
static_assert(kTailJumpInstructionEnd + kTailJumpRel32 == kTailTargetAddress,
              "the transcribed rel32 must land on the transcribed jump target");

// The extent the bridge reports for the body: 0x0096ff70..0x0096ff77
// inclusive, body_span_bytes 8. The eight bytes are followed by INT3 padding
// (0xcc) through 0x0096ff7f, which is alignment between this body and the next
// thunk at 0x0096ff80 and is not part of this function.
inline constexpr Word kBodyStartAddress = 0x0096ff70u;
inline constexpr Word kBodyEndAddress = 0x0096ff77u;
inline constexpr Word kInt3PaddingEndAddress = 0x0096ff7fu;
static_assert(kBodyEndAddress - kBodyStartAddress == 7u,
              "the body is eight bytes long");
static_assert(kBodyEndAddress < kInt3PaddingEndAddress,
              "the INT3 pad is not part of the body");

static_assert(sizeof(void *) == 4, "this reconstruction is x86-32 only");
static_assert(sizeof(Word) == 4, "the forwarded stack word is 32-bit");

// The pointer the thunk is handed. It arrives in ECX and is only ever written,
// never read, so this package claims nothing about its size, its layout or its
// members -- the type is left incomplete on purpose.
struct ThunkReceiver;

// The pointer the tail target operates on: 0x0C below the one above. Left
// incomplete for the same reason, and deliberately a different type from
// ThunkReceiver so that nothing in the model can treat the two addresses as
// interchangeable.
struct TailTargetObject;

// 0x0096ffd0, the tail target. It is a different reconstruction target, so this
// package declares its contract and does not model its body. What the contract
// states is only what its own live listing shows, re-read during this session
// (15 instructions, body 0x0096ffd0..0x00970008):
//
//   0096ffd0  PUSH ESI
//   0096ffd1  MOV ESI,ECX                      the receiver arrives in ECX
//   0096ffd3  MOV dword ptr [ESI],0x14425d8
//   0096ffd9  MOV dword ptr [ESI + 0x4],0x14425c0
//   0096ffe0  MOV dword ptr [ESI + 0xc],0x1442584
//   0096ffe7  MOV dword ptr [ESI + 0x60],0x13eb938
//   0096ffee  CALL 0x00980420
//   0096fff3  TEST byte ptr [ESP + 0x8],0x1    the forwarded word, low bit
//   0096fff8  JZ 0x00970003
//   0096fffa  PUSH ESI
//   0096fffb  CALL 0x00951330
//   00970000  ADD ESP,0x4
//   00970003  MOV EAX,ESI                      the object, in the return register
//   00970005  POP ESI
//   00970006  RET 0x4                          pops the one forwarded word
//
// Two properties of that listing are the reason this contract is shaped the way
// it is, and both are used by the model below:
//
//  * it reads its ordinary argument at [ESP+0x8], which is the word the caller
//    of 0x0096ff70 pushed, and it pops exactly that word itself (RET 0x4);
//  * it ends by materialising its receiver in EAX (MOV EAX,ESI), so it returns
//    the object pointer. The declared return type below follows that
//    instruction. It is *not* a claim about what 0x0096ff70 returns: the
//    transfer out of 0x0096ff70 is a tail jump, so that EAX belongs to the
//    callee's frame, and the persisted ABI record types this body void.
//
// The receiver is passed here as an explicit first parameter rather than as a
// hidden register parameter, because there is no portable spelling of "hidden
// receiver in ECX that the callee does not pop": __thiscall always makes the
// callee pop, and modelling the tail target as a popping callee would pop the
// frame's only stack word twice against a machine that pops it once. The
// argument values, their order and the net stack effect are identical either
// way; only the shape of the call site in the source differs from the machine,
// and that difference is stated here rather than left implicit.
extern "C" TailTargetObject *PKG_DFW_0096FF70_CDECL
dfw_tail_deleting_0096ffd0(TailTargetObject *object, Word deleting_flag);

// 0x0096ff70 itself. The one ordinary stack word is named deleting_flag
// because the persisted ABI record names it that
// (abi.ordinary_stack_arguments[0]: name "deleting_flag", type uint32,
// entry_offset "ESP+0x08 (as observed inside the tail target 0x0096FFD0)",
// usage "only bit 0 is read, by TEST byte [ESP+0x8],0x1 at 0x0096fff3"). The
// name is the record's; this package does not extend it into a claim about
// what the bit means beyond the fact that the tail target tests it.
extern "C" void PKG_DFW_0096FF70_THISCALL
dfw_func88h_0096ff70(ThunkReceiver *self, Word deleting_flag);

}  // namespace openspore::reconstruction::pkg_dfw_0096ff70
