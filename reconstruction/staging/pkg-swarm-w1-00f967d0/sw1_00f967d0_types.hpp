// PKG-SWARM-W1-00F967D0 -- VA 0x00f967d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00f967d0 @ 0x00f967d0.
//
// The whole body is 27 instructions, 0x00f967d0..0x00f96832 inclusive
// (ghidra_function.body_start 0x00f967d0, body_end 0x00f96832, span 99 bytes), and
// every displacement and constant in this header was read out of those 27
// instructions or out of the raw bytes of one of its three callees. Nothing is
// named that the machine does not fix. Specifically:
//
//  * ONE receiver displacement, +0x20c, and it is a POINTER, not a value. It is
//    read three separate times -- 0x00f967d6, 0x00f9680a and 0x00f9681b, each a
//    fresh `MOV ECX,dword ptr [ESI + 0x20c]` -- and each read is immediately
//    moved into ECX as the hidden receiver of the next call. Nothing else on the
//    receiver is read and NOTHING on the receiver is ever written.
//
//  * The three displacements the body reaches THROUGH that pointer are not its
//    own: they belong to the three callees, whose complete bodies are two
//    instructions each and were re-read for this package:
//      - 0x0097ef00  `FLD float ptr [ECX + 0x8]` / `RET`   -> the float at the
//        pointee's +0x08, returned in ST0.
//      - 0x00fb7bb0  `MOV EAX,dword ptr [ECX + 0x5c0]` / `RET` -> the word at
//        the pointee's +0x5c0, returned in EAX.
//      - 0x00fb7bc0  `MOV EAX,dword ptr [ECX + 0x5c4]` / `RET` -> the word at
//        the pointee's +0x5c4, returned in EAX.
//    Each of the three terminators is a bare `RET` with no immediate, so none of
//    the three callees takes an ordinary stack argument and none of them owns
//    any stack cleanup. The body pushes nothing at all: there is no PUSH, no
//    SUB ESP other than the prologue's own frame, and no stack write between a
//    CALL and the instruction that follows it.
//
//  * The pointee is therefore at least 0x5c8 bytes, and the model makes it
//    exactly that plus a four-byte sentinel tail. 0x5c8 is a modelling choice
//    for overrun detection and NOT a claim: the machine fixes that the last
//    byte the body can reach through the pointer is the pointee's +0x5c7, and
//    nothing below says the object is bigger or that it ends there.
//
//  * ONE global, the single word at 0x0140f334, read by the FMUL at 0x00f967e1.
//    Its four bytes in the image are 00 00 80 42, i.e. binary32 64.0f. The body
//    READS memory; it does not embed the constant, so the model reads it too and
//    the test is able to plant a different value and watch the result move.
//
// HONESTY NOTE ON NAMES. No member of the receiver and no member of the pointee
// is named for what it is, because nothing in this body or in the three callees
// says what any of them is for. Every field is spelled field_<hex offset>:
// that states where it lives and nothing more. The three accessors are named
// after their own instruction, not after a role. The receiver is NOT given a
// class name: ghidra_function for this VA carries namespace null and sdk_name
// null, and the only structural fact available is that the body is slot index 30
// of the 40-slot table at 0x01490be8 (xref from 0x01490c60, and 0x01490c60 -
// 0x01490be8 = 0x78 = 30 * 4, confirmed by reading the table's own words).
// A sibling package in the same table records that the table's owner class was
// never established, so no class name is asserted here either.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00f967d0 requires an x86-32 target"
#endif

// The convention is spelled per toolchain. GCC rejects the bare MSVC keywords
// outright, so the x86-32 attribute form is the portable spelling and the keyword
// form is kept for MSVC.
//
//   PKG_SW1_00F967D0_THISCALL
//     the hidden receiver in ECX. Every one of the four functions that carries it
//     proves it from its own bytes, and none of them contradicts it:
//       - 0x00f967d0 takes its receiver in ECX because 0x00f967d4 is
//         `MOV ESI,ECX` and 0x00f967d6 then reads the body through ESI, and it
//         owns its three argument words because its terminator is
//         `C2 0C 00` (RET 0xc).
//       - 0x0097ef00, 0x00fb7bb0 and 0x00fb7bc0 each dereference ECX in their
//         first and only instruction and end in a bare `C3`, so each takes its
//         receiver in ECX and pops nothing.
#if defined(_MSC_VER)
#define PKG_SW1_00F967D0_THISCALL __thiscall
#else
#define PKG_SW1_00F967D0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00f967d0 {

using Word = std::uint32_t;

// The image base this package was derived at, and the one data address the body
// names. Both are constants of the BINARY, not of the model: 0x0140f334 is
// .rdata, and the four bytes there were read out of the image for this package.
constexpr std::size_t kImageBase = 0x00400000u;
constexpr std::size_t kScaleConstantAddress = 0x0140f334u;

// The model's word at 0x0140f334. Returned BY REFERENCE on purpose: the body
// reads that memory, so the test has to be able to plant a different value and
// show the result follows it (that is what refutes a reconstruction that embedded
// 64.0f as a literal). Initialised to the image's own bytes, 00 00 80 42.
float& scale_word_0140f334();

// The receiver. 0x210 bytes is the whole claim: 0x20c is the only displacement
// the body reaches and it is a four-byte read, so 0x20c + 4 is the last byte it
// can touch, and it never writes any of them.
//
// The body is reached as a DISPLACEMENT, not as a member access, for the same
// reason the machine-derived receiver record is bounds_only: the record
// enumerates where the body was seen reaching and not which member is which. The
// single member below is spelled by offset for that reason; nothing here says the
// word at +0x20c is a pointer to a record, only that the body loads it into ECX
// and hands ECX to a callee that dereferences it.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x210> opaque_00_20f;
};

// The pointee, i.e. the object the word at receiver+0x20c names. Only three
// displacements of it are ever reached, and each of them is reached by a callee
// and not by this body:
//
//   +0x08  a 4-byte IEEE-754 single, loaded by 0x0097ef00's FLD
//   +0x5c0  a 4-byte word, loaded by 0x00fb7bb0's MOV EAX,[ECX+0x5c0]
//   +0x5c4  a 4-byte word, loaded by 0x00fb7bc0's MOV EAX,[ECX+0x5c4]
//
// The runs between them are opaque and untouched by anything in this set. The
// trailing four bytes exist so the model test can notice a store past +0x5c7;
// see the honesty note above about 0x5c8.
struct alignas(4) OpaquePointee {
  std::array<std::uint8_t, 0x08> opaque_00_07;  // 0x00..0x07, never reached
  float field_08;                               // 0x0097ef00's FLD operand
  std::array<std::uint8_t, 0x5b4> opaque_0c_5bf;  // 0x0c..0x5bf, never reached
  Word field_5c0;                               // 0x00fb7bb0's MOV operand
  Word field_5c4;                               // 0x00fb7bc0's MOV operand
  std::array<std::uint8_t, 0x04> opaque_5c8_5cb;  // sentinel tail, see above
};
static_assert(offsetof(OpaquePointee, field_08) == 0x08,
              "0x0097ef00 reads the float at the pointee's +0x08");
static_assert(offsetof(OpaquePointee, field_5c0) == 0x5c0,
              "0x00fb7bb0 reads the word at the pointee's +0x5c0");
static_assert(offsetof(OpaquePointee, field_5c4) == 0x5c4,
              "0x00fb7bc0 reads the word at the pointee's +0x5c4");

// The displacement the receiver's only word sits at, and the three displacements
// inside the pointee. Values, not names: nothing in this set says what any of the
// four words is for.
constexpr std::size_t kReceiverPointeeDisplacement = 0x20cu;
constexpr std::size_t kPointeeFloatDisplacement = 0x08u;
constexpr std::size_t kPointeeWord5c0Displacement = 0x5c0u;
constexpr std::size_t kPointeeWord5c4Displacement = 0x5c4u;

// -- the three direct callees ------------------------------------------------
// Each is declared here and defined by the model test as an observer, so the test
// sees every transfer the reconstruction makes. Every signature below is fixed by
// the callee's own two bytes, not by its decompilation (all three fail to
// decompile, which is why their listings were used instead).

// 0x0097ef00, called at 0x00f967dc. `FLD float ptr [ECX + 0x8]` / `RET`: receiver
// in ECX, no stack argument, result in ST0 as a single. No name is claimed for
// what the float means -- the body multiplies it by 64.0f and floors the product,
// and that is the whole of what the listing says.
extern "C" float PKG_SW1_00F967D0_THISCALL record_get_float_0097ef00(
    OpaquePointee* self);

// 0x00fb7bb0, called at 0x00f96810. `MOV EAX,dword ptr [ECX + 0x5c0]` / `RET`:
// receiver in ECX, no stack argument, result in EAX. The body stores EAX through
// its SECOND ordinary argument and never looks at it again.
extern "C" Word PKG_SW1_00F967D0_THISCALL record_get_word_00fb7bb0(
    OpaquePointee* self);

// 0x00fb7bc0, called at 0x00f96821. `MOV EAX,dword ptr [ECX + 0x5c4]` / `RET`:
// receiver in ECX, no stack argument, result in EAX. The body stores EAX through
// its THIRD ordinary argument and never looks at it again.
extern "C" Word PKG_SW1_00F967D0_THISCALL record_get_word_00fb7bc0(
    OpaquePointee* self);

// Model instrumentation, NOT a machine global. The reconstruction samples its own
// stack pointer immediately before each of the three transfers and this reads the
// samples back, so the model test can check that all three calls leave the same
// frame depth -- i.e. that the body pushed nothing for any of its callees.
//
// Why it lives here rather than being sampled inside the callees: an ESP sample
// taken inside a callee also reflects that callee's own prologue, which is the
// test fixture's business and not the reconstruction's. Sampled at the call sites
// inside the reconstruction, the three values are comparable to each other at every
// optimisation level.
//
// The samples are in no machine address space. `call_ordinal` is 0 for
// 0x0097ef00, 1 for 0x00fb7bb0 and 2 for 0x00fb7bc0, and the value is 0 for any
// other ordinal.
std::uint32_t call_site_esp_00f967d0(int call_ordinal);

// FUN_00f967d0 @ 0x00f967d0.
//
// __thiscall, receiver in ECX, three ordinary stack arguments, `RET 0xc` -- the
// bytes C2 0C 00 at 0x00f96830, so the callee owns all twelve bytes. The three
// slots are fixed by the frame, resolved once against the entry ESP E:
//
//   E+0x04  [ESP+0x18] read at 0x00f96804 with ESP at E-0x14, written at
//          0x00f96808. A POINTER: the body loads it into ECX and stores EAX
//          through ECX. Receives the floored scaled float.
//   E+0x08  [ESP+0x1c] read at 0x00f96815, written at 0x00f96819. A POINTER,
//          loaded into EDX. Receives 0x00fb7bb0's word.
//   E+0x0c  [ESP+0x20] read at 0x00f96826, written at 0x00f9682a. A POINTER,
//          loaded into ECX. Receives 0x00fb7bc0's word.
//
// Return type is void, and this is a claim against the machine-derived ABI record
// rather than a copy of it: that record reports return_register ST0 and
// return_semantics "float_or_x87_in_ST0", but the x87 register is not an outgoing
// value here. 0x00f967dc's FLD result is multiplied at 0x00f967e1 and consumed by
// the FSTP at 0x00f967e7, so the x87 stack is empty from 0x00f967e8 onward and
// nothing on any path writes ST0 after that. EAX is dead at the terminator too:
// its last writer is 0x00f9682a's own store, three instructions before the RET.
extern "C" void PKG_SW1_00F967D0_THISCALL re_00f967d0(OpaqueReceiver* receiver,
                                                     std::int32_t* out_scaled,
                                                     Word* out_word_5c0,
                                                     Word* out_word_5c4);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00f967d0
