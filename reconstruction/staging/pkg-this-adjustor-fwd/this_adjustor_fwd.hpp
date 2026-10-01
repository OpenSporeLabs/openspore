// pkg-this-adjustor-fwd -- VA 0x00c372b0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Bounded reconstruction of FUN_00c372b0 @ 0x00c372b0: a this-adjustor thunk.
// The complete body is two instructions, 0x00c372b0..0x00c372ba inclusive
// (11 bytes; ghidra_function.body_start 0x00c372b0, body_end 0x00c372ba):
//
//   00c372b0  81 c1 b8 07 00 00   ADD ECX,0x7b8
//   00c372b6  e9 d5 47 3b 00      JMP 0x00feba90
//
// Byte-level confirmation (objdump -d -M intel --start-address=0x00c372b0
// --stop-address=0x00c372b8 on the same binary): the six-byte ADD and the
// five-byte JMP above, followed by int3 padding at 0x00c372bb.
//
// WHAT THE BODY IS, in one paragraph, and the evidence for every clause: it is
// a single ESP-neutral direct jump that adjusts its receiver by +0x7b8 (1976)
// before transferring to 0x00feba90, so the callee operates on a sub-object
// 0x7b8 bytes ABOVE the incoming `this`. The convention and the cleanup are
// FORWARDED from the tail target by the T1-FWD inference recorded in
// abi_derived (conventions.calling_convention "__thiscall", confidence INFERRED,
// corroboration "forwarded_from_tail_target"; cleanup.side "caller", bytes 0).
// The tail target's own listing is `MOV AL,byte ptr [ECX + 0x18] ; RET`
// (0x00feba90..0x00feba93): receiver in ECX, no stack argument, bare RET, one
// byte written to the return register. The receiver's adjustor delta is a
// distinct, evidenced fact: abi_derived.receiver.adjustor_delta is 1976, and
// the source states it as kReceiverAdjustorDelta. The receiver's identity is
// NOT treated as unchanged.
//
// THE CONVENTION SPELLING IS A MACHINE FACT, NOT A PREFERENCE. The thunk's own
// listing is byte-identical under all four x86-32 conventions (it reads no
// stack word and its only register write is the ECX adjust), so the engine's
// top-level verdict for the thunk is ABI_UNKNOWN ("no_terminal_ret: the only
// exit observed is a tail jump"). What resolves it is the forwarding: the
// derived record's conventions sub-record carries "__thiscall" at INFERRED
// confidence, forwarded from 0x00feba90, whose own receiver is in ECX (R-DIRECT
// at offset 0x18) and whose cleanup is caller-side. The source therefore names
// __thiscall, and the sidecar's abi.calling_convention records the same fact
// with its provenance.
//
// NO CLASS NAME IS INFERRED. The machine evidence establishes "a virtual member
// of some class" at best (the tail target 0x00feba90 is a slot of four
// vptr-backed vftables under predicate P -- 0x01416a68+0x18, 0x01453b48+0x10,
// 0x0145c164+0x10, 0x0145c2b8+0x14 -- and a this-adjustor thunk is how MSVC
// reaches a secondary base), but no class identity is claimed anywhere in this
// package. The receiver is an opaque byte run.
//
// THE RETURN TYPE IS FORWARDED, AND ITS WIDTH IS A MACHINE FACT. The thunk's
// own listing writes no return register at all (it has no RET). The tail
// target's listing writes AL only (`MOV AL,byte ptr [ECX + 0x18]`), so the value
// that comes back through the tail call is one byte wide. The source declares
// std::uint8_t, which promises exactly that byte and nothing about the upper
// three, which the machine leaves undefined. The sidecar's abi.return_type
// records the same type with the tail target's listing as its evidence.

#ifndef OPENSPORE_RECONSTRUCTION_PKG_THIS_ADJUSTOR_FWD_HPP
#define OPENSPORE_RECONSTRUCTION_PKG_THIS_ADJUSTOR_FWD_HPP

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-this-adjustor-fwd requires an x86-32 target"
#endif

// The calling convention, spelled per toolchain. GCC rejects the bare MSVC
// keywords, so the x86-32 attribute form is the portable spelling and the
// keyword form is kept for MSVC. Both are asserted by machine facts:
//
//   PKG_THIS_ADJUSTOR_FWD_THISCALL  this body AND its tail target 0x00feba90.
//     The convention is __thiscall, forwarded from the tail target by the T1-FWD
//     inference (abi_derived.conventions: calling_convention "__thiscall",
//     confidence INFERRED, corroboration "forwarded_from_tail_target"). The
//     tail target's own listing reads its receiver through ECX
//     (`MOV AL,byte ptr [ECX + 0x18]`) and ends a bare `RET`, so the receiver
//     arrives in ECX and the callee pops nothing. The thunk itself adjusts ECX
//     in place (`ADD ECX,0x7b8`) and tail-jumps, so the adjusted ECX is what
//     the callee receives.
#if defined(_MSC_VER)
#define PKG_THIS_ADJUSTOR_FWD_THISCALL __thiscall
#else
#define PKG_THIS_ADJUSTOR_FWD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_this_adjustor_fwd {

// The receiver's adjustor delta: `ADD ECX,0x7b8` at 0x00c372b0. The incoming
// receiver is adjusted by +0x7b8 (1976) before the tail jump, so the callee
// operates on a sub-object 0x7b8 bytes ABOVE the incoming `this`. This is a
// distinct, evidenced fact (abi_derived.receiver.adjustor_delta is 1976) and
// is NOT the identity of the receiver: the receiver the callee sees is a
// different object at a higher address. The static_assert ties the constant to
// the instruction address it came from.
constexpr std::size_t kReceiverAdjustorDelta = 0x7b8;
static_assert(kReceiverAdjustorDelta == 0x7b8,
              "ADD ECX,0x7b8 at 0x00c372b0 adjusts the receiver by +0x7b8");

// The tail target, 0x00feba90. Declared here, defined as a test double in the
// model test (and a real function in the image). Its own listing:
//   00feba90  8a 41 18   MOV AL,byte ptr [ECX + 0x18]
//   00feba93  c3         RET
// Zero-argument __thiscall on ECX, caller cleans, one byte in the return
// register. The symbol embeds the callee's VA so the call is recognisable as
// the transfer the xref export records (00c372b0 -> 00feba90, direct-call at
// 0x00c372b6).
extern "C" std::uint8_t PKG_THIS_ADJUSTOR_FWD_THISCALL re_00feba90(void* receiver);

// The reconstructed body.
//
// __thiscall, receiver in ECX, NO ordinary stack argument, bare RET (forwarded
// from the tail target). Ghidra's own record for this VA reports "undefined
// FUN_00c372b0(void)" with ghidra_parameter_count 0, which is its reading of
// an unclassified convention and not a claim about the arguments.
//
// Return type is std::uint8_t and the width is a machine fact forwarded from
// the tail target: the thunk's own listing writes no return register, and the
// tail target's writes AL only, so the value that comes back is one byte wide.
extern "C" std::uint8_t PKG_THIS_ADJUSTOR_FWD_THISCALL re_00c372b0(void* receiver);

}  // namespace openspore::reconstruction::pkg_this_adjustor_fwd

#endif  // OPENSPORE_RECONSTRUCTION_PKG_THIS_ADJUSTOR_FWD_HPP
