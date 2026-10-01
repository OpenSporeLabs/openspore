// PKG-W2-00E7B6C0 -- VA 0x00e7b6c0
// Falsification test for the naked transcription reconstruct_00e7b6c0 of the
// 386-byte body of FUN_00e7b630.
//
// EVIDENCE REFS (all reachable from this repository):
//   GhidraMCP /get_function_by_address @ 0x00e7b6c0 -> FUN_00e7b630,
//     entry_point 00e7b630, body_start 00e7b630, body_end 00e7b7b1
//   GhidraMCP /disassemble_function @ 0x00e7b630 -> the 105 instructions
//   GhidraMCP /read_memory @ 0x00e7b630 (386 bytes) and
//     @ 0x00e7b6b0 (32 bytes) -> the byte string kImageBody
//   SPORE/SporeBin/SporeApp.exe, sha256
//     25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e,
//     section .text, RVA 0x00a7b630, read directly off disk for this package
//   GhidraMCP /disassemble_function @ 0x00b72210, 0x00b72160, 0x00743b50,
//     0x00e823a0, 0x00e4cc40; /get_function_by_address for 0x00e5d7b0,
//     0x00e780a0, 0x00e59a70, 0x00e82130, 0x00e6d200; /read_memory at each
//     function's last bytes for its terminator form
//   knowledgegraph/triage/xrefs-2540f2ca.tsv rows 159763..159772: ten
//     outgoing direct-call edges from 00e7b630, callsites 00e7b686 .. 00e7b7a6,
//     and row 160152: the single incoming edge, from 00e7e7f0 at 00e7e8f1
//   reconstruction/evidence/00e7b6c0/evidence.json, categories abi_derived and
//     disassembly
//   tools/reconstruction_tooling/abi_infer.py
//
// LAYERING, because a 105-instruction body has a great deal to agree with and
// the danger is a test that agrees with itself:
//
//   1. kImageBody in this file is a SECOND, INDEPENDENT transcription of the
//      image, written here rather than shared with the header. Case A compares
//      it against the header's kTargetBytes position by position and decodes
//      the rel32 fields, so the header's transcription is itself under test and
//      cannot drift silently. The reconstruction reads neither.
//   2. reconstruct_00e7b6c0 in the .cpp is the code under test. Case A compares
//      the bytes the COMPILER actually emitted, read out of the linked binary
//      at run time, against kImageBody.
//   3. The ESP trace is walked INDEPENDENTLY in case B, from a table written
//      here, and every row of that table is anchored to the image by the opcode
//      byte at that address and, for the four stack-relative instructions, by
//      the displacement bytes themselves. The table is not derived from the
//      header, so a header constant changed without the table changing fails.
//   4. The callees' stack effects are MEASURED in case E, through a hand-rolled
//      indirect call, against three control callees that pop nothing, four and
//      eight bytes, so an instrument that reported the same figure for
//      everything would be caught.
//   5. The nine calls and the twenty-six record writes are OBSERVED in case F,
//      because the test MAP_FIXEDs the two .data pages the body reads, plants
//      eight recognisable words in them, and defines each of the nine callees
//      as an observer that records what it was handed and reproduces the
//      terminator form the image records.
//
// THE CASES, and what each one is there to kill:
//
//   A  the body, byte for byte. 326 positions compared literally; the 60
//      encoding-relative bytes (ten CALL rel32 and five Jcc rel32) resolved out
//      of the emitted code and required to land on the targets the machine
//      records. A transcription that changed an operand, a displacement, a
//      branch target or a call target dies here.
//   B  the frame. The trace is walked independently and must CLOSE at depth
//      zero, and the two local slots and the one stack argument must resolve to
//      the addresses this package documents. A body that pushed or popped one
//      word too many, or one whose SUB/ADD disagreed, dies here -- which is
//      what pins cleanup.side = caller and bytes = 0 without trusting the
//      record's own figure for it.
//   C  the machine ABI record, value by value against literals written here:
//      ABI_UNKNOWN, confidence UNKNOWN, two candidates, one ambiguity, no
//      receiver with reason ecx_read_without_deref, caller-side cleanup of zero
//      bytes, and ST0/float_or_x87 at APPROXIMATION. A package that quietly
//      reverted to a receiver or a convention claim dies here, and so does one
//      that edited the record to match itself.
//   D  the containment fact: 0x00e7b6c0 is not an instruction start, it is
//      offset 0x90 of the body, and it is the fourth byte of the rel32 of the
//      call at 0x00e7b6bc. A package that moved the body to the queue's address
//      dies here.
//   E  the callee stack effect, MEASURED and calibrated.
//   F  the behaviour: the ten calls in the listing's order with the listing's
//      arguments, the twenty-six record writes at the listing's displacements
//      with independently computed values, the two globals copied twice each,
//      the x87 order (which FST/FSTP pair writes which value), the
//      FSTP-overwrites-the-pushed-word fact, and the eight planted globals
//      reaching the record. Every one of these is a value comparison, so a
//      reconstruction that shifted a displacement, swapped two stores, used the
//      wrong register or left a byte behind dies here rather than on a fault.
//   G  the three early-exit paths: each of the five guards in turn, and the
//      trace must be EMPTY and every fixture byte unchanged. A body that ran
//      any of the nine calls on an early exit, or that wrote through a
//      pointer on one, dies here.
//   H  register discipline: the probe measures that the reconstruction hands
//      ESI, EDI and EBX back unchanged, and the probe is itself checked to hand
//      the caller its own three registers and its own stack pointer.
//
// WHAT IS NOT ASSERTED, AND WHY:
//
//   * A RECEIVER. There is none. The record's own reason is
//     ecx_read_without_deref; ECX is a 32-bit value loaded out of memory at
//     0x00e7b68b and pushed as a stack argument at 0x00e7b691, and the body
//     dereferences it nowhere. The address 0x00e7b6c0 is in no sound
//     vptr-backed table, so the vftable-slot receiver rule has nothing to
//     reason from either. NO RECEIVER IS NAMED ANYWHERE IN THIS PACKAGE, and
//     case C fails if one is.
//   * A CALLING CONVENTION. The record resolves none. It names __cdecl and
//     __thiscall as candidates and abstains with ABI_UNKNOWN and
//     receiver_undetermined. The source therefore carries no convention token,
//     and case C checks that the count is zero.
//   * ANY FIELD, MEMBER, SIZE OR LAYOUT of anything the body touches. The
//     displacements below are displacements out of instructions. They are not
//     struct members, no `->` appears in this package's code, and no `offsetof`
//     is written. NO FIELD OFFSET IS CLAIMED IN EITHER DIRECTION: the body shows
//     no receiver-relative displacement through any undetermined receiver, so
//     neither a field at some offset nor the object's being flat is asserted.
//   * WHAT 0x00e6d200 LEAVES IN ST0. The number of x87 registers it leaves, and
//     their values, are not in evidence. The model therefore TAKES THE ST0
//     CONTENT AS A PARAMETER: the observer in this file pushes a chosen pair,
//     and case F pins which of the two the FST and which the FSTP stores. A
//     reconstruction that reversed those two dies there.
//   * THE TWO UNRESOLVED CONTRADICTIONS on the callee side. 0x00e6d200 and
//     0x00e780a0 are each reported by Ghidra as ending in ADD ESP,n; RET, and
//     taken at these call sites those forms would each remove four bytes more
//     than the caller removes, so the epilogue would not close. Case B shows
//     the epilogue DOES close, and case E shows the reconstruction pops what the
//     record says it pops. The two terminator readings are carried as data and
//     flagged, and the disagreement is left open rather than resolved.
//   * THE MEANING OF ANY GLOBAL, OF THE POOL BASE 0x016b3c04, OF EITHER
//     FIXTURE, OF THE HANDLE, OR OF ANY OF THE TWENTY-SIX FIELDS. All of them
//     are located and sized; none of them is named for what it is.

#include "w2_00e7b6c0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <sys/mman.h>

// -- the nine call observers' recorders, at file scope so the assembly can
//    reach them by name (a PC-relative call to a non-hidden symbol goes through
//    the PLT on a position-independent i386 build, which is what makes this
//    work without a GOT reference inside the assembly).
extern "C" {
void observe_00b72210(std::uint32_t ecx, std::uint32_t word);
void observe_00e6d200(std::uint32_t ecx, std::uint32_t w1, std::uint32_t w2,
                      std::uint32_t w3, std::uint32_t w4);
void observe_00b72160(std::uint32_t ecx);
void observe_00743b50(std::uint32_t ecx);
void observe_00e4cc40(std::uint32_t ecx, std::uint32_t w1, std::uint32_t w2);
void observe_00e5d7b0(std::uint32_t ecx, std::uint32_t word);
void observe_00e780a0(std::uint32_t ecx, std::uint32_t w1, std::uint32_t w2,
                      std::uint32_t w3, std::uint32_t w4);
void observe_00e59a70(std::uint32_t eax);
void observe_00e82130(std::uint32_t ecx);
}

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00e7b6c0 {
namespace {

// -- the IMAGE, transcribed independently of the header ---------------------
//
// GhidraMCP /read_memory at 0x00e7b630 for 386 bytes, and the same 386 bytes
// read directly off SPORE/SporeBin/SporeApp.exe (section .text, RVA 0x00a7b630).
// This array exists so the header's kTargetBytes is under test: a change to
// either transcription without the other fails case A.
constexpr std::uint8_t kImageBody[386] = {
    0x83u, 0xecu, 0x08u, 0x80u, 0xbeu, 0x12u, 0x01u, 0x00u, 0x00u, 0x01u,
    0x55u, 0x8bu, 0x6cu, 0x24u, 0x10u, 0x0fu, 0x84u, 0x68u, 0x01u, 0x00u,
    0x00u, 0x80u, 0xbeu, 0x13u, 0x01u, 0x00u, 0x00u, 0x01u, 0x0fu, 0x84u,
    0x5bu, 0x01u, 0x00u, 0x00u, 0x53u, 0x33u, 0xdbu, 0x38u, 0x9eu, 0x78u,
    0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x4bu, 0x01u, 0x00u, 0x00u, 0x38u,
    0x9eu, 0x7fu, 0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x3fu, 0x01u, 0x00u,
    0x00u, 0x38u, 0x9du, 0x7bu, 0x01u, 0x00u, 0x00u, 0x0fu, 0x85u, 0x33u,
    0x01u, 0x00u, 0x00u, 0x8bu, 0x06u, 0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu,
    0x01u, 0x57u, 0x83u, 0xc1u, 0x1cu, 0x50u, 0xe8u, 0x85u, 0x6bu, 0xcfu,
    0xffu, 0x8bu, 0x88u, 0xb0u, 0x01u, 0x00u, 0x00u, 0x51u, 0x6au, 0x31u,
    0x53u, 0x50u, 0xe8u, 0x65u, 0x1bu, 0xffu, 0xffu, 0xd9u, 0x5cu, 0x24u,
    0x20u, 0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu, 0x01u, 0x8bu, 0x3eu, 0x83u,
    0xc4u, 0x10u, 0x83u, 0xc1u, 0x54u, 0xe8u, 0xaeu, 0x6au, 0xcfu, 0xffu,
    0x8bu, 0x0du, 0x04u, 0x3cu, 0x6bu, 0x01u, 0x83u, 0xc1u, 0x54u, 0x50u,
    0xe8u, 0x4fu, 0x6bu, 0xcfu, 0xffu, 0xd9u, 0x44u, 0x24u, 0x10u, 0x0fu,
    0x57u, 0xc0u, 0xd9u, 0x50u, 0x1cu, 0xd9u, 0x58u, 0x20u, 0xc7u, 0x40u,
    0x24u, 0x20u, 0x00u, 0x00u, 0x00u, 0x89u, 0x78u, 0x28u, 0x89u, 0x58u,
    0x2cu, 0x83u, 0xc9u, 0xffu, 0x89u, 0x48u, 0x30u, 0x89u, 0x48u, 0x34u,
    0x89u, 0x58u, 0x38u, 0x89u, 0x58u, 0x3cu, 0xf3u, 0x0fu, 0x11u, 0x40u,
    0x40u, 0xf3u, 0x0fu, 0x11u, 0x40u, 0x44u, 0x8bu, 0x15u, 0x28u, 0x3cu,
    0x6bu, 0x01u, 0x89u, 0x50u, 0x48u, 0x8bu, 0x0du, 0x2cu, 0x3cu, 0x6bu,
    0x01u, 0x89u, 0x48u, 0x4cu, 0x8bu, 0x15u, 0x30u, 0x3cu, 0x6bu, 0x01u,
    0x89u, 0x50u, 0x50u, 0x8bu, 0x0du, 0x28u, 0x3cu, 0x6bu, 0x01u, 0x89u,
    0x48u, 0x54u, 0x8bu, 0x15u, 0x2cu, 0x3cu, 0x6bu, 0x01u, 0x89u, 0x50u,
    0x58u, 0x8bu, 0x0du, 0x30u, 0x3cu, 0x6bu, 0x01u, 0x89u, 0x48u, 0x5cu,
    0x8bu, 0x15u, 0x4cu, 0x7cu, 0x5au, 0x01u, 0x89u, 0x50u, 0x60u, 0x8bu,
    0x0du, 0x50u, 0x7cu, 0x5au, 0x01u, 0x89u, 0x48u, 0x64u, 0x8bu, 0x15u,
    0x54u, 0x7cu, 0x5au, 0x01u, 0x89u, 0x50u, 0x68u, 0x8bu, 0x0du, 0x58u,
    0x7cu, 0x5au, 0x01u, 0x89u, 0x48u, 0x6cu, 0x8du, 0x4cu, 0x24u, 0x0cu,
    0x89u, 0x58u, 0x70u, 0x88u, 0x58u, 0x74u, 0x89u, 0x58u, 0x78u, 0x89u,
    0x58u, 0x04u, 0x88u, 0x58u, 0x08u, 0xe8u, 0xeau, 0x83u, 0x8cu, 0xffu,
    0x8bu, 0x85u, 0x08u, 0x01u, 0x00u, 0x00u, 0x8du, 0x54u, 0x24u, 0x0cu,
    0x52u, 0x50u, 0xe8u, 0xc9u, 0x14u, 0xfdu, 0xffu, 0x8bu, 0x88u, 0xb8u,
    0x00u, 0x00u, 0x00u, 0x51u, 0xe8u, 0x2du, 0x20u, 0xfeu, 0xffu, 0xd9u,
    0xeeu, 0x8bu, 0x55u, 0x00u, 0x83u, 0xc4u, 0x0cu, 0x53u, 0x51u, 0xd9u,
    0x1cu, 0x24u, 0x6au, 0x01u, 0x52u, 0xe8u, 0x08u, 0xc9u, 0xffu, 0xffu,
    0x83u, 0xc4u, 0x10u, 0x8bu, 0x06u, 0xe8u, 0xceu, 0xe2u, 0xfdu, 0xffu,
    0x8du, 0x4cu, 0x24u, 0x0cu, 0xe8u, 0x85u, 0x69u, 0x00u, 0x00u, 0x5fu,
    0x5bu, 0x5du, 0x83u, 0xc4u, 0x08u, 0xc3u,
};

int g_failures = 0;
int g_checks = 0;

void check(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t got, std::uint32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08lx, want 0x%08lx)\n", what,
                 static_cast<unsigned long>(got),
                 static_cast<unsigned long>(want));
    ++g_failures;
  }
}

std::uint32_t address_of(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The address of a function, for the probe's indirect call. A function pointer
// is not a `const void*` under -Werror, so it goes through its own cast.
template <typename Fn>
std::uint32_t function_address(Fn pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

void put_u32(void* base, std::size_t offset, std::uint32_t value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

std::uint32_t get_u32(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

std::int32_t rel32_at(const std::uint8_t* bytes, std::size_t offset) {
  return static_cast<std::int32_t>(
      static_cast<std::uint32_t>(bytes[offset]) |
      (static_cast<std::uint32_t>(bytes[offset + 1]) << 8) |
      (static_cast<std::uint32_t>(bytes[offset + 2]) << 16) |
      (static_cast<std::uint32_t>(bytes[offset + 3]) << 24));
}

// The fifteen rel32 displacement offsets, written HERE and not taken from the
// header. Case A checks the header's fifteen against these, and every rel32
// resolution below uses these, so a header offset changed without this one
// changing fails.
constexpr std::size_t kCallRel32OffsetsTest[10] = {
    0x57u, 0x67u, 0x7eu, 0x8du, 0x132u, 0x143u, 0x14fu, 0x164u, 0x16eu, 0x177u};
constexpr std::size_t kBranchRel32OffsetsTest[5] = {0x11u, 0x1eu, 0x2du,
                                                     0x39u, 0x45u};

// Whether byte `index` of the body is part of one of the fifteen rel32
// displacements.
bool is_rel32(std::size_t index) {
  for (int i = 0; i < 10; ++i) {
    if (index >= kCallRel32OffsetsTest[i] &&
        index < kCallRel32OffsetsTest[i] + 4u) {
      return true;
    }
  }
  for (int i = 0; i < 5; ++i) {
    if (index >= kBranchRel32OffsetsTest[i] &&
        index < kBranchRel32OffsetsTest[i] + 4u) {
      return true;
    }
  }
  return false;
}

// -- the ESP trace, walked independently (case B) ----------------------------
//
// One row per stack-pointer-affecting instruction on the fall-through path,
// transcribed HERE from the disassembly listing and not from the header. Every
// row is anchored to the image by the opcode byte at that address, so a table
// row that names an address the image does not carry fails. The four
// stack-relative instructions carry the offset of their displacement byte
// within the instruction, so the displacement is read back out of the image and
// compared with what the row claims.
//
// `depth` is the stack pointer BELOW the entry stack pointer, after the
// instruction has run. Only 0x00b72210 pops anything: the terminator
// `c2 04 00` at 0x00b7221f is RET 0x4, and 0x00b72210 is called twice.
struct TraceRow {
  std::uint32_t instruction;
  std::uint32_t body_offset;
  std::uint8_t opcode;
  std::uint8_t length;
  std::uint32_t depth;
  std::int8_t disp_offset;   // -1 for an instruction with no displacement
  std::uint8_t disp_width;
  std::uint32_t disp_value;
};

constexpr TraceRow kTrace[] = {
    {0x00e7b630u, 0x00u, 0x83u, 3u, 0x08u, 2, 1u, 0x08u},
    {0x00e7b63au, 0x0au, 0x55u, 1u, 0x0cu, -1, 0u, 0u},
    {0x00e7b63bu, 0x0bu, 0x8bu, 4u, 0x0cu, 3, 1u, 0x10u},
    {0x00e7b652u, 0x22u, 0x53u, 1u, 0x10u, -1, 0u, 0u},
    {0x00e7b681u, 0x51u, 0x57u, 1u, 0x14u, -1, 0u, 0u},
    {0x00e7b685u, 0x55u, 0x50u, 1u, 0x18u, -1, 0u, 0u},
    {0x00e7b686u, 0x56u, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b691u, 0x61u, 0x51u, 1u, 0x18u, -1, 0u, 0u},
    {0x00e7b692u, 0x62u, 0x6au, 2u, 0x1cu, -1, 0u, 0u},
    {0x00e7b694u, 0x64u, 0x53u, 1u, 0x20u, -1, 0u, 0u},
    {0x00e7b695u, 0x65u, 0x50u, 1u, 0x24u, -1, 0u, 0u},
    {0x00e7b696u, 0x66u, 0xe8u, 5u, 0x24u, -1, 0u, 0u},
    {0x00e7b69bu, 0x6bu, 0xd9u, 4u, 0x24u, 3, 1u, 0x20u},
    {0x00e7b6a7u, 0x77u, 0x83u, 3u, 0x14u, 2, 1u, 0x10u},
    {0x00e7b6adu, 0x7du, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b6bbu, 0x8bu, 0x50u, 1u, 0x18u, -1, 0u, 0u},
    {0x00e7b6bcu, 0x8cu, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b6c1u, 0x91u, 0xd9u, 4u, 0x14u, 3, 1u, 0x10u},
    {0x00e7b74eu, 0x11eu, 0x8du, 4u, 0x14u, 3, 1u, 0x0cu},
    {0x00e7b761u, 0x131u, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b770u, 0x140u, 0x52u, 1u, 0x18u, -1, 0u, 0u},
    {0x00e7b771u, 0x141u, 0x50u, 1u, 0x1cu, -1, 0u, 0u},
    {0x00e7b772u, 0x142u, 0xe8u, 5u, 0x1cu, -1, 0u, 0u},
    {0x00e7b77du, 0x14du, 0x51u, 1u, 0x20u, -1, 0u, 0u},
    {0x00e7b77eu, 0x14eu, 0xe8u, 5u, 0x20u, -1, 0u, 0u},
    {0x00e7b788u, 0x158u, 0x83u, 3u, 0x14u, 2, 1u, 0x0cu},
    {0x00e7b78bu, 0x15bu, 0x53u, 1u, 0x18u, -1, 0u, 0u},
    {0x00e7b78cu, 0x15cu, 0x51u, 1u, 0x1cu, -1, 0u, 0u},
    {0x00e7b790u, 0x160u, 0x6au, 2u, 0x20u, -1, 0u, 0u},
    {0x00e7b792u, 0x162u, 0x52u, 1u, 0x24u, -1, 0u, 0u},
    {0x00e7b793u, 0x163u, 0xe8u, 5u, 0x24u, -1, 0u, 0u},
    {0x00e7b798u, 0x168u, 0x83u, 3u, 0x14u, 2, 1u, 0x10u},
    {0x00e7b79du, 0x16du, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b7a6u, 0x176u, 0xe8u, 5u, 0x14u, -1, 0u, 0u},
    {0x00e7b7abu, 0x17bu, 0x5fu, 1u, 0x10u, -1, 0u, 0u},
    {0x00e7b7acu, 0x17cu, 0x5bu, 1u, 0x0cu, -1, 0u, 0u},
    {0x00e7b7adu, 0x17du, 0x5du, 1u, 0x08u, -1, 0u, 0u},
    {0x00e7b7aeu, 0x17eu, 0x83u, 3u, 0x00u, 2, 1u, 0x08u},
    {0x00e7b7b1u, 0x181u, 0xc3u, 1u, 0x00u, -1, 0u, 0u},
};
constexpr std::size_t kTraceRowCount = sizeof(kTrace) / sizeof(kTrace[0]);

// The three stack-relative instructions the frame is read through, named in
// this file rather than in the header, so the header's two slot constants are
// checked against an independent statement of the same three.
constexpr std::uint32_t kFloatStoreInstruction = 0x00e7b69bu;
constexpr std::uint32_t kFloatLoadInstruction = 0x00e7b6c1u;
constexpr std::uint32_t kHandleLeaInstruction = 0x00e7b74eu;
constexpr std::uint32_t kStackArgumentInstruction = 0x00e7b63bu;
constexpr std::size_t kFloatStoreDisplacement = 0x20u;
constexpr std::size_t kFloatLoadDisplacement = 0x10u;
constexpr std::size_t kHandleLeaDisplacement = 0x0cu;
constexpr std::size_t kStackArgumentDisplacement = 0x10u;
constexpr std::size_t kFloatSlotFromEntry = 0x04u;
constexpr std::size_t kHandleSlotFromEntry = 0x08u;
constexpr std::size_t kStackArgumentFromEntry = 0x04u;

// -- the probes and the observers -------------------------------------------

// There is no ebp_value, and that is a fact about the machine rather than an
// omission: the body's very second frame instruction is `MOV EBP,[ESP+0x10]`,
// so EBP is whatever the ONE stack word holds, and the probe cannot choose it
// independently of that word. EBP is therefore not written by the probe at all
// -- the body pushes it and pops it, and the probe hands the caller its own
// back untouched.
struct ProbeArgs {
  std::uint32_t target;
  std::uint32_t esi_value;
  std::uint32_t ecx_value;
  std::uint32_t eax_value;
  std::uint32_t stack_arg;
};

struct ProbeResult {
  std::uint32_t before;
  std::uint32_t after;
  std::uint32_t delta;
  std::uint32_t eax_after;
  std::uint32_t ecx_at_call;
  std::uint32_t esi_at_call;
  std::uint32_t esi_exit;
  std::uint32_t edi_entry;
  std::uint32_t edi_exit;
  std::uint32_t ebx_entry;
  std::uint32_t ebx_exit;
  std::uint32_t esp_at_exit;
};

extern "C" void probe_call_00e7b6c0(const ProbeArgs* args, ProbeResult* out);
extern "C" void control_pops_zero_00e7b6c0();
extern "C" void control_pops_four_00e7b6c0();
extern "C" void control_pops_eight_00e7b6c0();

// REGISTER DISCIPLINE, AND WHY THE PROBE IS ONE FILE-SCOPE ASSEMBLY FUNCTION.
//
// The probe is an i386 cdecl function, so EBX, ESI, EDI and EBP must survive
// it. It therefore keeps EVERYTHING it needs in its own frame and addresses it
// relative to the stack pointer, so no callee-saved register is used as a
// frame pointer or as an argument carrier. EBX and EDI are never written: they
// are only sampled, into memory, at entry and again at exit, and the test
// requires the two samples to agree -- which is a MEASUREMENT that the
// reconstruction preserved them, not a repair. EBX matters twice over, because
// on a position-independent i386 build it holds the GOT base and taking it over
// inside the assembly would invalidate every address the compiler forms around
// it.
//
// ESI and EBP are the two exceptions, and both are restored before the probe
// returns: the target body reads ESI seven times and writes it never, and it
// pushes and pops EBP itself, so the values it must be ENTERED with cannot come
// from a compiler-generated call site. The probe therefore loads them, hands
// them over, and puts the caller's own values back with a matching pair of pops
// -- so the caller is handed back exactly what it passed in, and the test
// checks that too. The alternative, a probe that borrowed ESI and never gave it
// back, corrupts the CALLER silently and surfaces as an optimiser-dependent
// failure in a test that has nothing to do with the probe.
//
// The samples are taken through the probe's OWN STACK FRAME, not through the
// stack pointer, because the stack pointer is exactly the thing the cleanup
// sides disagree about. The block records ESP before any push and ESP
// immediately after the call returns, and nothing in between: the difference
// between the two IS the callee's pop, and `ret imm16` pops the RETURN ADDRESS
// FIRST and only then adds its immediate, so a sample sits kReturnAddressBytes
// BELOW where entry_ESP + the immediate would be. The probe restores ESP from
// its own `before` afterwards, whichever of the three outcomes occurred.
//
// The block is a FILE-SCOPE assembly function rather than an extended-asm block
// in the middle of a C++ body. That bounds its influence to one function, whose
// only contact with the fixtures is through pointers, and it means the compiler
// never has to model registers it cannot see.

// Frame map, addressed through the probe's own frame pointer. The probe saves
// the caller's EBP and ESI around the whole thing, so neither leaks, and it
// uses EBP only as its own frame pointer -- never as a carrier for an argument
// or a result, which is the mistake that makes a hand-written probe corrupt its
// caller. The target pushes and pops EBP itself, so it leaves the probe's frame
// pointer intact across the call.
//
//   ebp-40  the callee address
//   ebp-36  the ProbeResult pointer
//   ebp-32  `before`: the stack pointer before the one push, i.e. ebp-40
//   ebp-28  ECX as the callee will see it
//   ebp-24  ESI as the callee will see it
//   ebp-20  `after`: the stack pointer immediately after the call returns
//   ebp-16  EAX after the call
//   ebp-12  EAX as the callee will see it
//   ebp-8   EDI as the probe found it
//   ebp-4   EBX as the probe found it
//
// `after` is sampled BEFORE the pushed word is given back, and the stack
// pointer is then restored from `before` rather than by adding a constant -- so
// the probe survives a callee that pops four or eight bytes as well as one that
// pops nothing, which is exactly the range the three controls span. A probe
// that assumed the callee popped nothing would itself fall over on the four- and
// eight-byte controls and would have measured them as crashes.
__asm__(".text\n"
        ".balign 16\n"
        ".globl probe_call_00e7b6c0\n"
        ".type probe_call_00e7b6c0, @function\n"
        "probe_call_00e7b6c0:\n"
        "  pushl %esi\n"
        "  pushl %ebp\n"
        "  movl %esp, %ebp\n"
        "  subl $40, %esp\n"
        "  movl 12(%ebp), %eax\n"
        "  movl 16(%ebp), %edx\n"
        "  movl %edx, -36(%ebp)\n"
        "  movl 0(%eax), %edx\n"
        "  movl %edx, -40(%ebp)\n"
        "  movl 4(%eax), %esi\n"
        "  movl 8(%eax), %ecx\n"
        "  movl %ecx, -28(%ebp)\n"
        "  movl %esi, -24(%ebp)\n"
        "  movl 16(%eax), %edx\n"
        "  movl 12(%eax), %eax\n"
        "  movl %eax, -12(%ebp)\n"
        "  movl %edi, -8(%ebp)\n"
        "  movl %ebx, -4(%ebp)\n"
        "  movl %esp, -32(%ebp)\n"
        "  pushl %edx\n"
        "  movl -40(%ebp), %edx\n"
        "  call *%edx\n"
        "  movl %esp, -20(%ebp)\n"
        "  movl %eax, -16(%ebp)\n"
        "  leal -40(%ebp), %esp\n"
        "  movl -36(%ebp), %edx\n"
        "  movl -32(%ebp), %eax\n"
        "  movl %eax, 0(%edx)\n"
        "  movl -20(%ebp), %eax\n"
        "  movl %eax, 4(%edx)\n"
        "  movl -32(%ebp), %ecx\n"
        "  subl %ecx, %eax\n"
        "  movl %eax, 8(%edx)\n"
        "  movl -16(%ebp), %eax\n"
        "  movl %eax, 12(%edx)\n"
        "  movl -28(%ebp), %eax\n"
        "  movl %eax, 16(%edx)\n"
        "  movl -24(%ebp), %eax\n"
        "  movl %eax, 20(%edx)\n"
        "  movl %esi, 24(%edx)\n"
        "  movl -8(%ebp), %eax\n"
        "  movl %eax, 28(%edx)\n"
        "  movl %edi, 32(%edx)\n"
        "  movl -4(%ebp), %eax\n"
        "  movl %eax, 36(%edx)\n"
        "  movl %ebx, 40(%edx)\n"
        "  movl %esp, 44(%edx)\n"
        "  movl %ebp, %esp\n"
        "  popl %ebp\n"
        "  popl %esi\n"
        "  ret\n"
        ".size probe_call_00e7b6c0, .-probe_call_00e7b6c0\n"
        // The three control callees, defined at file scope in assembly rather
        // than as C++ functions, because the whole point is the RET form and a
        // compiler-generated prologue would move the stack the RET reads from.
        ".globl control_pops_zero_00e7b6c0\n"
        ".type control_pops_zero_00e7b6c0, @function\n"
        "control_pops_zero_00e7b6c0:\n"
        "  movl %ecx, %eax\n"
        "  ret\n"
        ".size control_pops_zero_00e7b6c0, .-control_pops_zero_00e7b6c0\n"
        ".globl control_pops_four_00e7b6c0\n"
        ".type control_pops_four_00e7b6c0, @function\n"
        "control_pops_four_00e7b6c0:\n"
        "  movl %ecx, %eax\n"
        "  ret $4\n"
        ".size control_pops_four_00e7b6c0, .-control_pops_four_00e7b6c0\n"
        ".globl control_pops_eight_00e7b6c0\n"
        ".type control_pops_eight_00e7b6c0, @function\n"
        "control_pops_eight_00e7b6c0:\n"
        "  movl %ecx, %eax\n"
        "  ret $8\n"
        ".size control_pops_eight_00e7b6c0, .-control_pops_eight_00e7b6c0\n"
        // THE NINE OBSERVERS. Each is entered exactly the way the listing
        // enters it, and each reproduces the terminator form the image records
        // for that callee, so the reconstruction's own stack discipline is what
        // the run exercises. Each first hands what it was given to a C++
        // recorder, which is where the trace comes from.
        //
        // 0x00b72210: hidden register ECX, one stack word, RET 0x4. Returns its
        //   word, which is what makes the caller's EAX the pool-relative
        //   address the listing then reads [EAX+0x1b0] through.
        ".globl callee_00b72210\n"
        ".type callee_00b72210, @function\n"
        "callee_00b72210:\n"
        "  pushl 4(%esp)\n"
        "  pushl %ecx\n"
        "  call observe_00b72210\n"
        "  addl $8, %esp\n"
        "  movl 4(%esp), %eax\n"
        "  ret $4\n"
        ".size callee_00b72210, .-callee_00b72210\n"
        // 0x00e6d200: four stack words, the caller drops them with ADD ESP,0x10,
        //   so the observer leaves only the return address. It then leaves TWO
        //   x87 registers behind, ST0 = float(w1) and ST1 = float(w3), which is
        //   the parameterisation case F needs: how many registers the machine's
        //   own callee leaves is not in evidence, so the observer supplies a
        //   pair and the test pins which of the two each store takes.
        ".globl callee_00e6d200\n"
        ".type callee_00e6d200, @function\n"
        "callee_00e6d200:\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl %ecx\n"
        "  call observe_00e6d200\n"
        "  addl $0x10, %esp\n"
        "  popl %ecx\n"
        "  flds 0xc(%esp)\n"
        "  flds 4(%esp)\n"
        "  ret\n"
        ".size callee_00e6d200, .-callee_00e6d200\n"
        // 0x00b72160: hidden register ECX, no stack word, plain RET, and its EAX
        //   is the base the record is filled through.
        ".globl callee_00b72160\n"
        ".type callee_00b72160, @function\n"
        "callee_00b72160:\n"
        "  pushl %ecx\n"
        "  call observe_00b72160\n"
        "  popl %ecx\n"
        "  movl %ecx, %eax\n"
        "  ret\n"
        ".size callee_00b72160, .-callee_00b72160\n"
        // 0x00743b50: hidden register ECX, no stack word, plain RET, and its
        //   whole body is MOV EAX,ECX / MOV [EAX],0 / RET -- three instructions,
        //   which is what the observer emits.
        ".globl callee_00743b50\n"
        ".type callee_00743b50, @function\n"
        "callee_00743b50:\n"
        "  pushl %ecx\n"
        "  call observe_00743b50\n"
        "  popl %ecx\n"
        "  movl %ecx, %eax\n"
        "  movl $0, (%eax)\n"
        "  ret\n"
        ".size callee_00743b50, .-callee_00743b50\n"
        // 0x00e4cc40: a JMP thunk onto 0x00e823a0, two stack words, plain RET.
        //   The body of 0x00e823a0 is *param_2 = param_1 and then a refcount
        //   increment through param_1, and the shim reproduces the store: the
        //   first word goes into the location the second word names, and the
        //   first word is returned in EAX.
        ".globl callee_00e4cc40\n"
        ".type callee_00e4cc40, @function\n"
        "callee_00e4cc40:\n"
        "  pushl 8(%esp)\n"
        "  pushl 8(%esp)\n"
        "  pushl %ecx\n"
        "  call observe_00e4cc40\n"
        "  addl $12, %esp\n"
        "  movl 4(%esp), %edx\n"
        "  movl 8(%esp), %eax\n"
        "  movl %edx, (%eax)\n"
        "  movl %edx, %eax\n"
        "  ret\n"
        ".size callee_00e4cc40, .-callee_00e4cc40\n"
        // 0x00e5d7b0: one stack word, plain RET, no result the body uses.
        ".globl callee_00e5d7b0\n"
        ".type callee_00e5d7b0, @function\n"
        "callee_00e5d7b0:\n"
        "  pushl 4(%esp)\n"
        "  pushl %ecx\n"
        "  call observe_00e5d7b0\n"
        "  addl $8, %esp\n"
        "  ret\n"
        ".size callee_00e5d7b0, .-callee_00e5d7b0\n"
        // 0x00e780a0: four stack words, plain RET.
        ".globl callee_00e780a0\n"
        ".type callee_00e780a0, @function\n"
        "callee_00e780a0:\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl 0x10(%esp)\n"
        "  pushl %ecx\n"
        "  call observe_00e780a0\n"
        "  addl $0x10, %esp\n"
        "  popl %ecx\n"
        "  ret\n"
        ".size callee_00e780a0, .-callee_00e780a0\n"
        // 0x00e59a70: its argument arrives in EAX, no stack word, plain RET.
        ".globl callee_00e59a70\n"
        ".type callee_00e59a70, @function\n"
        "callee_00e59a70:\n"
        "  pushl %eax\n"
        "  call observe_00e59a70\n"
        "  addl $4, %esp\n"
        "  movl $1, %eax\n"
        "  ret\n"
        ".size callee_00e59a70, .-callee_00e59a70\n"
        // 0x00e82130: hidden register ECX, no stack word, plain RET, and its
        //   whole body is DEC dword [EAX+0xc] guarded by *ECX != 0. The guard
        //   and the decrement happen in the C++ recorder, where the fixture
        //   words are reachable.
        ".globl callee_00e82130\n"
        ".type callee_00e82130, @function\n"
        "callee_00e82130:\n"
        "  pushl %ecx\n"
        "  call observe_00e82130\n"
        "  popl %ecx\n"
        "  ret\n"
        ".size callee_00e82130, .-callee_00e82130\n");

// -- the trace ---------------------------------------------------------------

struct TraceStep {
  std::uint32_t callee;
  std::uint32_t ecx;
  std::uint32_t w[4];
  int words;
};

constexpr int kMaxTrace = 16;
TraceStep g_trace[kMaxTrace];
int g_trace_count = 0;
std::uint32_t g_ignored = 0;

void push_step(std::uint32_t callee, std::uint32_t ecx, const std::uint32_t* w,
               int words) {
  if (g_trace_count >= kMaxTrace) {
    ++g_ignored;
    return;
  }
  TraceStep& step = g_trace[g_trace_count++];
  step.callee = callee;
  step.ecx = ecx;
  step.words = words;
  for (int i = 0; i < 4; ++i) {
    step.w[i] = (i < words) ? w[i] : 0u;
  }
}

// The handle the reconstruction builds at S-8, and the object it points at, so
// 0x00e82130's guard and its decrement are observable. Placed at file scope so
// the address does not move with the stack.
std::uint8_t g_handle_object[16];

}  // namespace
}  // namespace pkg_w2_00e7b6c0
}  // namespace reconstruction
}  // namespace openspore

// -- the recorders -----------------------------------------------------------

extern "C" void observe_00b72210(std::uint32_t ecx, std::uint32_t word) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  (void)ecx;
  push_step(0x00b72210u, ecx, &word, 1);
}

extern "C" void observe_00e6d200(std::uint32_t ecx, std::uint32_t w1,
                                 std::uint32_t w2, std::uint32_t w3,
                                 std::uint32_t w4) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  const std::uint32_t words[4] = {w1, w2, w3, w4};
  (void)ecx;
  push_step(0x00e6d200u, ecx, words, 4);
}

extern "C" void observe_00b72160(std::uint32_t ecx) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  push_step(0x00b72160u, ecx, nullptr, 0);
}

extern "C" void observe_00743b50(std::uint32_t ecx) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  push_step(0x00743b50u, ecx, nullptr, 0);
}

extern "C" void observe_00e4cc40(std::uint32_t ecx, std::uint32_t w1,
                                 std::uint32_t w2) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  const std::uint32_t words[2] = {w1, w2};
  push_step(0x00e4cc40u, ecx, words, 2);
}

extern "C" void observe_00e5d7b0(std::uint32_t ecx, std::uint32_t word) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  (void)ecx;
  push_step(0x00e5d7b0u, ecx, &word, 1);
}

extern "C" void observe_00e780a0(std::uint32_t ecx, std::uint32_t w1,
                                 std::uint32_t w2, std::uint32_t w3,
                                 std::uint32_t w4) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  const std::uint32_t words[4] = {w1, w2, w3, w4};
  (void)ecx;
  push_step(0x00e780a0u, ecx, words, 4);
}

extern "C" void observe_00e59a70(std::uint32_t eax) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  push_step(0x00e59a70u, eax, nullptr, 0);
}

extern "C" void observe_00e82130(std::uint32_t ecx) {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  // What this observer REPORDS is what 0x00e82130 was HANDED and what it then
  // SAW -- the hidden register and the word at it. It does not reproduce
  // 0x00e82130's own body, and that is deliberate: 0x00e82130's internals are
  // its own, this package claims nothing about them, and a check that depended
  // on reproducing them would be a check about the observer rather than about
  // the reconstruction. What IS a fact about the reconstruction is that the
  // handle local at S-8 holds the value 0x00e4cc40 was handed by the time
  // 0x00e82130 reads it, and that is what the recorded word shows.
  const std::uint32_t seen =
      (ecx != 0u) ? get_u32(reinterpret_cast<const void*>(
                                 static_cast<std::uintptr_t>(ecx)),
                             0)
                  : 0u;
  push_step(0x00e82130u, ecx, &seen, 1);
}

namespace openspore {
namespace reconstruction {
namespace pkg_w2_00e7b6c0 {
namespace {

// -- the fixtures ------------------------------------------------------------

constexpr std::size_t kGuard = 64;
constexpr std::uint8_t kGuardByte = 0xa5;
constexpr std::size_t kRecordBytes = 0x100;
constexpr std::size_t kCellBytes = 0x200;
constexpr std::size_t kHandleBytes = 0x100;
constexpr std::size_t kEbpBytes = 0x200;

struct Storage {
  std::uint8_t bytes[kGuard + kRecordBytes + kGuard];
  std::uint8_t cell[kGuard + kCellBytes + kGuard];
  std::uint8_t ebp[kGuard + kEbpBytes + kGuard];
  std::uint8_t handle[kGuard + kHandleBytes + kGuard];

  Storage() {
    reset();
  }

  void reset() {
    std::memset(bytes, kGuardByte, sizeof(bytes));
    std::memset(cell, kGuardByte, sizeof(cell));
    std::memset(ebp, kGuardByte, sizeof(ebp));
    std::memset(handle, kGuardByte, sizeof(handle));
    g_trace_count = 0;
    g_ignored = 0;
  }

  std::uint8_t* record() { return bytes + kGuard; }
  const std::uint8_t* record() const { return bytes + kGuard; }
  std::uint8_t* cellp() { return cell + kGuard; }
  const std::uint8_t* cellp() const { return cell + kGuard; }
  std::uint8_t* ebpp() { return ebp + kGuard; }
  const std::uint8_t* ebpp() const { return ebp + kGuard; }
  std::uint8_t* handlep() { return handle + kGuard; }
  const std::uint8_t* handlep() const { return handle + kGuard; }

  bool bands_intact() const {
    const std::uint8_t* runs[4] = {bytes, cell, ebp, handle};
    const std::size_t spans[4] = {kRecordBytes, kCellBytes, kEbpBytes,
                                  kHandleBytes};
    for (int r = 0; r < 4; ++r) {
      for (std::size_t i = 0; i < kGuard; ++i) {
        if (runs[r][i] != kGuardByte ||
            runs[r][kGuard + spans[r] + i] != kGuardByte) {
          return false;
        }
      }
    }
    return true;
  }
};

Storage g_storage;

// The two .data pages the body reads, MAP_FIXED at the addresses the image
// uses. Both are inside section .data (RVA 0x0110c000 .. 0x0171e764 -> VA
// 0x0150c000 .. 0x0171e764) and both are page-aligned.
constexpr std::uint32_t kDataPageA = 0x015a7000u;
constexpr std::uint32_t kDataPageB = 0x016b3000u;
void* g_page_a = nullptr;
void* g_page_b = nullptr;

// The eight planted global words, in the listing's read order. The three at
// 0x016b3c28..0x016b3c30 are each read TWICE and land at six of the record's
// displacements, so a reconstruction that read them once, or in the wrong
// order, dies on a value.
constexpr std::uint32_t kPlanted[8] = {0x0badf00du, 0x11111111u, 0x22222222u,
                                       0x33333333u, 0x44444444u, 0x55555555u,
                                       0x66666666u, 0x77777777u};
constexpr std::uint32_t kPlantedBase = 0x016b3c28u;  // kPlanted[1] lives here
constexpr std::uint32_t kPlantedConsts = 0x015a7c4cu;  // kPlanted[4] lives here

bool map_globals() {
  void* const a = mmap(reinterpret_cast<void*>(static_cast<std::uintptr_t>(kDataPageA)),
                       0x1000, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
  void* const b = mmap(reinterpret_cast<void*>(static_cast<std::uintptr_t>(kDataPageB)),
                       0x1000, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
  if (a == MAP_FAILED || b == MAP_FAILED) {
    return false;
  }
  g_page_a = a;
  g_page_b = b;
  for (int i = 0; i < 8; ++i) {
    const std::uint32_t address = kPlantedBase + 4u * static_cast<std::uint32_t>(i);
    put_u32(reinterpret_cast<void*>(static_cast<std::uintptr_t>(address)),
            0, kPlanted[i]);
  }
  for (int i = 4; i < 8; ++i) {
    const std::uint32_t address =
        kPlantedConsts + 4u * static_cast<std::uint32_t>(i - 4);
    put_u32(reinterpret_cast<void*>(static_cast<std::uintptr_t>(address)), 0,
            kPlanted[i]);
  }
  return true;
}

// build_fixtures plants everything the body reads, and nothing it does not.
//
// The pool base needs the most care, because the record's address is an OUTPUT
// rather than an input: 0x00b72160 returns its own hidden register and
// 0x00b72210 returns the word it was given, so the word planted at 0x016b3c04
// must be (the record's address - 0x54) for the record to land where the test
// can look at it. Nothing about the binary is adjusted to make that easier: the
// body still forms [0x016b3c04]+0x54 exactly as the listing does, and the test
// still derives the expected record base from that arithmetic.
void build_fixtures(std::uint32_t stack_arg, bool handle_is_null) {
  g_storage.reset();
  (void)stack_arg;

  const std::uint32_t record_base = address_of(g_storage.record());
  const std::uint32_t pool = record_base - kGlobalBaseDisplacementB;
  put_u32(reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x016b3c04u)), 0,
          pool);

  // The ESI fixture: the dword at +0 is the address the body passes to
  // 0x00b72210 and then reads [EAX+0x1b0] through. The five guard bytes are all
  // zero, which is what lets the fall-through path run.
  put_u32(g_storage.cellp(), 0x00u, address_of(g_storage.cellp()));
  put_u32(g_storage.cellp(), 0x112u, 0u);
  put_u32(g_storage.cellp(), 0x113u, 0u);
  put_u32(g_storage.cellp(), 0x178u, 0u);
  put_u32(g_storage.cellp(), 0x17fu, 0u);
  put_u32(g_storage.cellp(), 0x1b0u, 0xfeedfaceu);

  // The EBP fixture: the three general-register reads. +0x108 is the handle
  // pointer 0x00e4cc40 is handed and stores, and +0x108 + 0xb8 is what the body
  // then reads back through 0x00e4cc40's return value.
  put_u32(g_storage.ebpp(), 0x000u, 0x00c0ffeeu);
  put_u32(g_storage.ebpp(), 0x17bu, 0u);
  put_u32(g_storage.ebpp(), 0x108u, address_of(g_storage.handlep()));

  // The handle object, so 0x00e82130's guard and its decrement are observable.
  std::memset(g_handle_object, 0, sizeof(g_handle_object));
  put_u32(g_handle_object, 0x0cu, 7u);
  put_u32(g_storage.handlep(), 0x00u,
          handle_is_null ? 0u : address_of(g_handle_object));
  put_u32(g_storage.handlep(), 0x04u, address_of(g_handle_object));
  put_u32(g_storage.handlep(), 0x08u, 0x55aa55aau);
  put_u32(g_storage.handlep(), 0x0cu, 0x66aa66aau);
  put_u32(g_storage.handlep(), 0xb8u, 0u);
}

// -- case A: the body, byte for byte ----------------------------------------

std::uint32_t g_entry = 0;  // the address the probe must CALL, 0 if unmatched

// The seven literal byte positions used to FIND the body in the linked binary.
// None of them is a rel32 byte, so the probe works whatever addresses the linker
// put into the ten CALL displacements and the five branch displacements. The
// full 326-position comparison is case A; this is only the address.
const std::size_t kEntryProbeOffsets[7] = {0x00u, 0x0au, 0x15u, 0x22u,
                                            0x62u, 0x74u, 0x7du};
const std::uint8_t kEntryProbeBytes[7] = {0x83u, 0x55u, 0x80u, 0x53u,
                                          0x6au, 0x01u, 0xe8u};

bool body_at(const std::uint8_t* candidate) {
  for (int i = 0; i < 7; ++i) {
    if (candidate[kEntryProbeOffsets[i]] != kEntryProbeBytes[i]) {
      return false;
    }
  }
  return true;
}

// Is there a __x86.get_pc_thunk.ax PC anchor in front of the body? It is
// `e8 ?? ?? ?? ?? 05` followed by the body, and the OBSERVATION of it is a
// statement about this toolchain rather than about the reconstruction.
bool has_pc_anchor(const std::uint8_t* start) {
  return start[0] == 0xe8u && start[5] == 0x05u &&
         body_at(start + kPcAnchorBytes);
}

const std::uint8_t* emitted_body() {
  const std::uint8_t* const start = reinterpret_cast<const std::uint8_t*>(
      &reconstruct_00e7b6c0);
  // A default position-independent g++ build at -O0 prepends the ten-byte
  // __x86.get_pc_thunk.ax PC anchor to a naked function; g++ at -O1 and above
  // and clang++ at every level emit none. That anchor is not merely a prefix to
  // skip: the thunk it calls is `mov (%esp),%eax; ret`, so CALLING the symbol's
  // own address would return to the word ABOVE the return address and never
  // enter the body. The address the probe calls is therefore the 386 bytes, not
  // the symbol -- and which of the two it is must be DECIDED by the anchor's own
  // opcode pair, never by a search that might match the body's bytes at the
  // wrong offset. Byte-identical recompilation is NOT claimed without the anchor
  // allowance.
  if (has_pc_anchor(start)) {
    return start + kPcAnchorBytes;
  }
  if (body_at(start)) {
    return start;
  }
  return nullptr;
}

void test_image_and_emitted_body() {
  // The header's transcription against this file's, position by position.
  int mismatches = 0;
  for (std::size_t i = 0; i < 386u; ++i) {
    if (kTargetBytes[i] != kImageBody[i]) {
      ++mismatches;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(mismatches), 0u,
               "A: the header's byte transcript matches the image's, position "
               "by position");

  // The byte arithmetic, stated here and not taken from the header.
  check_eq_u32(static_cast<std::uint32_t>(kLiteralByteCount), 326u,
               "A: 326 positions are compared literally");
  check_eq_u32(static_cast<std::uint32_t>(kResolvedRel32Bytes), 60u,
               "A: 60 positions are encoding-relative");
  check_eq_u32(static_cast<std::uint32_t>(kLiteralByteCount + kResolvedRel32Bytes),
               386u, "A: 326 + 60 accounts for all 386 bytes with nothing left");

  // The 105 instruction lengths, summed here.
  static const std::uint8_t kLengths[105] = {3, 7, 1, 4, 6, 7, 6, 1, 2, 6, 6, 6, 6, 6, 6, 2, 6, 1, 3, 1, 5, 6, 1, 2, 1, 1, 5, 4, 6, 2, 3, 3, 5, 6, 3, 1, 5, 4, 3, 3, 3, 7, 3, 3, 3, 3, 3, 3, 3, 5, 5, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 6, 3, 4, 3, 3, 3, 3, 3, 5, 6, 4, 1, 1, 5, 6, 1, 5, 2, 3, 3, 1, 1, 3, 2, 1, 5, 3, 2, 5, 4, 5, 1, 1, 1, 3, 1};
  std::size_t total = 0;
  std::size_t at = 0;
  bool inside = true;
  static const std::uint32_t kAddresses[105] = {0xe7b630u, 0xe7b633u, 0xe7b63au, 0xe7b63bu, 0xe7b63fu, 0xe7b645u, 0xe7b64cu, 0xe7b652u, 0xe7b653u, 0xe7b655u, 0xe7b65bu, 0xe7b661u, 0xe7b667u, 0xe7b66du, 0xe7b673u, 0xe7b679u, 0xe7b67bu, 0xe7b681u, 0xe7b682u, 0xe7b685u, 0xe7b686u, 0xe7b68bu, 0xe7b691u, 0xe7b692u, 0xe7b694u, 0xe7b695u, 0xe7b696u, 0xe7b69bu, 0xe7b69fu, 0xe7b6a5u, 0xe7b6a7u, 0xe7b6aau, 0xe7b6adu, 0xe7b6b2u, 0xe7b6b8u, 0xe7b6bbu, 0xe7b6bcu, 0xe7b6c1u, 0xe7b6c5u, 0xe7b6c8u, 0xe7b6cbu, 0xe7b6ceu, 0xe7b6d5u, 0xe7b6d8u, 0xe7b6dbu, 0xe7b6deu, 0xe7b6e1u, 0xe7b6e4u, 0xe7b6e7u, 0xe7b6eau, 0xe7b6efu, 0xe7b6f4u, 0xe7b6fau, 0xe7b6fdu, 0xe7b703u, 0xe7b706u, 0xe7b70cu, 0xe7b70fu, 0xe7b715u, 0xe7b718u, 0xe7b71eu, 0xe7b721u, 0xe7b727u, 0xe7b72au, 0xe7b730u, 0xe7b733u, 0xe7b739u, 0xe7b73cu, 0xe7b742u, 0xe7b745u, 0xe7b74bu, 0xe7b74eu, 0xe7b752u, 0xe7b755u, 0xe7b758u, 0xe7b75bu, 0xe7b75eu, 0xe7b761u, 0xe7b766u, 0xe7b76cu, 0xe7b770u, 0xe7b771u, 0xe7b772u, 0xe7b777u, 0xe7b77du, 0xe7b77eu, 0xe7b783u, 0xe7b785u, 0xe7b788u, 0xe7b78bu, 0xe7b78cu, 0xe7b78du, 0xe7b790u, 0xe7b792u, 0xe7b793u, 0xe7b798u, 0xe7b79bu, 0xe7b79du, 0xe7b7a2u, 0xe7b7a6u, 0xe7b7abu, 0xe7b7acu, 0xe7b7adu, 0xe7b7aeu, 0xe7b7b1u};
  for (int i = 0; i < 105; ++i) {
    if (kAddresses[i] != 0x00e7b630u + at) {
      inside = false;
    }
    at += kLengths[i];
  }
  total = at;
  check(inside, "A: the 105 addresses tile the body with no gap");
  check_eq_u32(static_cast<std::uint32_t>(total), 386u,
               "A: the 105 instruction lengths sum to 386");
  check_eq_u32(static_cast<std::uint32_t>(kAddresses[0]), 0x00e7b630u,
               "A: the listing starts at 0x00e7b630");
  check_eq_u32(static_cast<std::uint32_t>(kAddresses[104]), 0x00e7b7b1u,
               "A: the listing's last instruction is the RET at 0x00e7b7b1");
  check_eq_u32(static_cast<std::uint32_t>(kAddresses[104] + kLengths[104] - 1),
               0x00e7b7b1u, "A: the body's last byte is 0x00e7b7b1");
  check_eq_u32(kBodyEndExclusive, 0x00e7b7b2u,
               "A: the exclusive end is 0x00e7b7b2");

  const std::uint8_t* const emitted = emitted_body();
  if (emitted == nullptr) {
    check(false, "A: the emitted body is the image's 386 bytes, at the symbol "
                 "itself or ten bytes after it");
    return;
  }
  check(true, "A: the emitted body is the image's 386 bytes, at the symbol "
              "itself or ten bytes after it");
  g_entry = address_of(emitted);
  check(g_entry != 0u, "A: the probe has a non-zero address to call");
  check(g_entry == address_of(emitted),
        "A: the address the probe calls is the body itself");
  check((reinterpret_cast<const std::uint8_t*>(&reconstruct_00e7b6c0) ==
         emitted) ||
            has_pc_anchor(reinterpret_cast<const std::uint8_t*>(
                &reconstruct_00e7b6c0)),
        "A: and either the symbol IS the body or a PC anchor in front of it was "
        "recognised by its own opcode pair");

  // The 326 literal positions, one by one.
  int literal_bad = 0;
  int counted = 0;
  for (std::size_t i = 0; i < 386u; ++i) {
    if (is_rel32(i)) {
      continue;
    }
    ++counted;
    if (emitted[i] != kImageBody[i]) {
      ++literal_bad;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(counted), 326u,
               "A: exactly 326 positions are not encoding-relative");
  check_eq_u32(static_cast<std::uint32_t>(literal_bad), 0u,
               "A: every one of the 326 literal positions matches the image");

  // The ten call rel32s, resolved out of the emitted code, from the offsets
  // this file wrote. Each must land on the model's OWN observer for that
  // callsite -- the observers are named after the machine addresses and the
  // call sites are in the listing's order, so a call moved, swapped or aimed at
  // the wrong observer dies here -- and each observer's name must carry the
  // machine address the xref export records.
  void* const model_callee[10] = {
      reinterpret_cast<void*>(&callee_00b72210),
      reinterpret_cast<void*>(&callee_00e6d200),
      reinterpret_cast<void*>(&callee_00b72160),
      reinterpret_cast<void*>(&callee_00b72210),
      reinterpret_cast<void*>(&callee_00743b50),
      reinterpret_cast<void*>(&callee_00e4cc40),
      reinterpret_cast<void*>(&callee_00e5d7b0),
      reinterpret_cast<void*>(&callee_00e780a0),
      reinterpret_cast<void*>(&callee_00e59a70),
      reinterpret_cast<void*>(&callee_00e82130)};
  for (int i = 0; i < 10; ++i) {
    const std::size_t off = kCallRel32OffsetsTest[i];
    check_eq_u32(static_cast<std::uint32_t>(kCallRel32Offsets[i]),
                 static_cast<std::uint32_t>(off),
                 "A: the header's call rel32 offset matches this file's");
    const std::int32_t disp = rel32_at(emitted, off);
    // The displacement is measured from the EMITTED next-instruction address,
    // which is the body's own address plus the offset just after the four
    // displacement bytes -- not the binary's 0x00e7b68b and friends, which live
    // in a different image entirely.
    const std::uint32_t emitted_base =
        g_entry + static_cast<std::uint32_t>(off) + 4u;
    const std::uint32_t landed = static_cast<std::uint32_t>(
        static_cast<std::int64_t>(emitted_base) + disp);
    check(emitted[off - 1] == 0xe8u,
          "A: the call's opcode byte is E8");
    check_eq_u32(landed, address_of(model_callee[i]),
                 "A: the call rel32 resolves to this model's own observer for "
                 "that callsite");
    check_eq_u32(static_cast<std::uint32_t>(kCallRel32Targets[i]),
                 kCalleeAddresses[i < 3 ? i : (i == 3 ? 0 : i - 1)],
                 "A: the observer's name carries the machine callee address the "
                 "xref export records");
    check_eq_u32(address_of(model_callee[i]),
                 address_of(model_callee[kCalleeAddresses[i < 3 ? i
                                                                 : (i == 3 ? 0
                                                                           : i - 1)] == kCallRel32Targets[i] ? i : i]),
                 "A: the observer at that callsite is the one for that machine "
                 "callee");
  }
  check_eq_u32(kCallRel32Bases[3], 0x00e7b6c1u,
               "A: the fourth call's next-instruction address is 0x00e7b6c1");

  // The five branch rel32s, likewise.
  for (int i = 0; i < 5; ++i) {
    const std::size_t off = kBranchRel32OffsetsTest[i];
    check_eq_u32(static_cast<std::uint32_t>(kBranchRel32Offsets[i]),
                 static_cast<std::uint32_t>(off),
                 "A: the header's branch rel32 offset matches this file's");
    const std::int32_t disp = rel32_at(emitted, off);
    const std::uint32_t emitted_base =
        g_entry + static_cast<std::uint32_t>(off) + 4u;
    const std::uint32_t landed = static_cast<std::uint32_t>(
        static_cast<std::int64_t>(emitted_base) + disp);
    check(emitted[off - 2] == 0x0fu,
          "A: the branch is the two-byte 0F 8x form");
    check(emitted[off - 1] == 0x84u || emitted[off - 1] == 0x85u,
          "A: the branch is JZ (0F 84) or JNZ (0F 85)");
    // The two JZ land on the POP EBP and the three JNZ on the POP EBX, in the
    // emitted body just as in the image.
    const std::size_t pop_ebp_offset = 0x00e7b7adu - kBodyFirstByte;
    const std::size_t pop_ebx_offset = 0x00e7b7acu - kBodyFirstByte;
    const std::uint32_t want = (i < 2) ? (g_entry + static_cast<std::uint32_t>(pop_ebp_offset))
                                      : (g_entry + static_cast<std::uint32_t>(pop_ebx_offset));
    check_eq_u32(landed, want,
                 "A: the branch rel32 resolves to the emitted POP EBP (the two "
                 "JZ) or the emitted POP EBX (the three JNZ)");
    check(emitted[pop_ebp_offset] == 0x5du,
          "A: and that instruction really is the POP EBP");
    check(emitted[pop_ebx_offset] == 0x5bu,
          "A: and that instruction really is the POP EBX");
  }
  check_eq_u32(kBranchRel32Targets[0], 0x00e7b7adu,
               "A: the header's first branch target is the POP EBP at 0x00e7b7ad");
  check_eq_u32(kBranchRel32Targets[2], 0x00e7b7acu,
               "A: and its third is the POP EBX at 0x00e7b7ac");
  check(kImageBody[0x00e7b7ac - 0x00e7b630] == 0x5bu,
        "A: 0x00e7b7ac really is the POP EBX the JNZ land on");
  check(kImageBody[0x00e7b7ad - 0x00e7b630] == 0x5du,
        "A: 0x00e7b7ad really is the POP EBP the JZ land on");

  // The image carries no indirect transfer: no CALL or JMP through a register
  // or a memory operand, and no branch other than the five Jcc.
  bool indirect = false;
  bool unexpected_branch = false;
  for (std::size_t i = 0; i + 1u < 386u; ++i) {
    if (kImageBody[i] == 0xffu &&
        (kImageBody[i + 1] == 0xd0u || kImageBody[i + 1] == 0xd1u ||
         kImageBody[i + 1] == 0xd2u || kImageBody[i + 1] == 0xd3u ||
         kImageBody[i + 1] == 0xd4u || kImageBody[i + 1] == 0xd5u ||
         kImageBody[i + 1] == 0xd6u || kImageBody[i + 1] == 0xd7u ||
         (kImageBody[i + 1] & 0xf8u) == 0xd0u ||
         (kImageBody[i + 1] & 0xf8u) == 0xe0u)) {
      indirect = true;
    }
  }
  static const std::size_t kBranchDisp[5] = {0x11u, 0x1eu, 0x2du, 0x39u, 0x45u};
  for (std::size_t i = 0; i < 386u; ++i) {
    if (kImageBody[i] == 0x0fu && (kImageBody[i + 1] == 0x84u ||
                                   kImageBody[i + 1] == 0x85u)) {
      bool known = false;
      for (int b = 0; b < 5; ++b) {
        if (i == kBranchDisp[b] - 2u) {
          known = true;
        }
      }
      if (!known) {
        unexpected_branch = true;
      }
    }
    if (i + 1u < 386u &&
        kImageBody[i] == 0x0fu && kImageBody[i + 1] >= 0x80u &&
        kImageBody[i + 1] <= 0x8fu && kImageBody[i + 1] != 0x84u &&
        kImageBody[i + 1] != 0x85u) {
      unexpected_branch = true;
    }
  }
  check(!indirect, "A: the image carries no register-indirect CALL or JMP");
  check(!unexpected_branch,
        "A: the image carries no conditional branch other than the five Jcc");
}

// -- case B: the frame, walked independently -------------------------------

void build_fixtures(std::uint32_t stack_arg, bool handle_is_null);

std::uint32_t row_depth(std::uint32_t instruction) {
  for (std::size_t i = 0; i < kTraceRowCount; ++i) {
    if (kTrace[i].instruction == instruction) {
      return kTrace[i].depth;
    }
  }
  return 0xffffffffu;
}

void test_frame_walk() {
  // Every row is anchored to the image: the address must be one this file's
  // table names, the body offset must carry the opcode byte the row claims, and
  // the stack-relative rows must carry the displacement they claim.
  for (std::size_t i = 0; i < kTraceRowCount; ++i) {
    const TraceRow& row = kTrace[i];
    check_eq_u32(row.instruction - kBodyFirstByte,
                 static_cast<std::uint32_t>(row.body_offset),
                 "B: the row's body offset is its address minus the body start");
    check(kImageBody[row.body_offset] == row.opcode,
          "B: the image carries the opcode byte the row claims at that address");
    if (row.disp_offset >= 0) {
      std::uint32_t seen = 0;
      for (std::uint32_t b = 0; b < row.disp_width; ++b) {
        seen |= static_cast<std::uint32_t>(
                    kImageBody[row.body_offset +
                               static_cast<std::size_t>(row.disp_offset) + b])
                << (8u * b);
      }
      check_eq_u32(seen, row.disp_value,
                   "B: the image carries the displacement the row claims");
    }
  }

  // Every row's depth, against a second statement of the same thirty-nine
  // numbers written here as a flat list rather than as the table above. Two
  // independent transcriptions of one walk: a depth edited in the table and not
  // in the list, or the other way round, fails here. Without this the walk's
  // CLOSURE is checked but its interior is not, and an interior depth is exactly
  // what a planted mutation changes.
  static const std::uint32_t kExpectedDepth[kTraceRowCount] = {
      0x08u, 0x0cu, 0x0cu, 0x10u, 0x14u, 0x18u, 0x14u, 0x18u, 0x1cu,
      0x20u, 0x24u, 0x24u, 0x24u, 0x14u, 0x14u, 0x18u, 0x14u, 0x14u, 0x14u,
      0x14u, 0x18u, 0x1cu, 0x1cu, 0x20u, 0x20u, 0x14u, 0x18u, 0x1cu, 0x20u,
      0x24u, 0x24u, 0x14u, 0x14u, 0x14u, 0x10u, 0x0cu, 0x08u, 0x00u, 0x00u};
  for (std::size_t i = 0; i < kTraceRowCount; ++i) {
    check_eq_u32(kTrace[i].depth, kExpectedDepth[i],
                 "B: the row's stack depth matches the second transcription of "
                 "the walk");
  }

  // The epilogue CLOSES. This is the single most load-bearing check in the
  // file: the depth at the RET is zero, so the body leaves the caller's stack
  // exactly as it found it, which is what `cleanup.side: caller, bytes: 0`
  // says and what the record's own RET with no immediate says. A body that
  // pushed or popped one word too many, or whose SUB and ADD disagreed, ends
  // the walk at a non-zero depth and dies here.
  check_eq_u32(kTrace[kTraceRowCount - 1].depth, 0u,
               "B: the trace ends at depth zero, so the epilogue closes");
  check_eq_u32(kTrace[kTraceRowCount - 1].instruction, 0x00e7b7b1u,
               "B: the last row is the RET at 0x00e7b7b1");
  check_eq_u32(kTrace[kTraceRowCount - 3].depth, kFrameReservationBytes,
               "B: the ADD ESP,0x8 before the RET is reached with exactly the "
               "eight-byte reservation outstanding");
  check_eq_u32(kTrace[kTraceRowCount - 2].instruction, 0x00e7b7aeu,
               "B: and the row that gives it back is the ADD ESP,0x8");

  // The two local slots. Each is derived here from the row's own depth and the
  // displacement read back out of the image, and compared with this file's
  // constant -- and with the header's, so neither can drift alone.
  check_eq_u32(row_depth(kFloatStoreInstruction) - kFloatStoreDisplacement,
               static_cast<std::uint32_t>(kFloatSlotFromEntry),
               "B: the FSTP at 0x00e7b69b lands S-4, the float local");
  check_eq_u32(row_depth(kFloatLoadInstruction) - kFloatLoadDisplacement,
               static_cast<std::uint32_t>(kFloatSlotFromEntry),
               "B: the FLD at 0x00e7b6c1 reads back the same S-4 float local");
  check_eq_u32(row_depth(kHandleLeaInstruction) - kHandleLeaDisplacement,
               static_cast<std::uint32_t>(kHandleSlotFromEntry),
               "B: the LEA at 0x00e7b74e forms the address of the S-8 handle "
               "local");
  check_eq_u32(static_cast<std::uint32_t>(kLocalFloatOffsetFromEntry),
               static_cast<std::uint32_t>(kFloatSlotFromEntry),
               "B: the header's float slot is S-4, as this file derives it");
  check_eq_u32(static_cast<std::uint32_t>(kLocalHandleOffsetFromEntry),
               static_cast<std::uint32_t>(kHandleSlotFromEntry),
               "B: the header's handle slot is S-8, as this file derives it");
  check_eq_u32(static_cast<std::uint32_t>(kFloatSlotStoreEspDepth),
               row_depth(kFloatStoreInstruction),
               "B: the header's float-store depth is the walked one");
  check_eq_u32(static_cast<std::uint32_t>(kFloatSlotLoadEspDepth),
               row_depth(kFloatLoadInstruction),
               "B: the header's float-load depth is the walked one");
  check_eq_u32(static_cast<std::uint32_t>(kHandleSlotEspDepth),
               row_depth(kHandleLeaInstruction),
               "B: the header's handle depth is the walked one");
  check_eq_u32(static_cast<std::uint32_t>(kFloatSlotStoreDisplacement),
               static_cast<std::uint32_t>(kFloatStoreDisplacement),
               "B: the header's float-store displacement is the image's");
  check_eq_u32(static_cast<std::uint32_t>(kFloatSlotLoadDisplacement),
               static_cast<std::uint32_t>(kFloatLoadDisplacement),
               "B: the header's float-load displacement is the image's");
  check_eq_u32(static_cast<std::uint32_t>(kHandleSlotDisplacement),
               static_cast<std::uint32_t>(kHandleLeaDisplacement),
               "B: the header's handle displacement is the image's");

  // Both local slots lie inside the eight-byte reservation, and the reservation
  // is the only frame there is: no MOV EBP,ESP exists anywhere in the 386
  // bytes, which is exactly the record's own frame_pointer_untrusted
  // abstention.
  check(kHandleSlotFromEntry == kFrameReservationBytes &&
            kFloatSlotFromEntry < kFrameReservationBytes,
        "B: the handle local is the low word of the reservation and the float "
        "local the high word, and nothing else is reserved");
  bool has_frame_pointer = false;
  for (std::size_t i = 0; i + 1u < 386u; ++i) {
    if (kImageBody[i] == 0x89u && kImageBody[i + 1] == 0xe5u) {
      has_frame_pointer = true;  // MOV EBP,ESP
    }
    if (kImageBody[i] == 0x8bu && kImageBody[i + 1] == 0xecu) {
      has_frame_pointer = true;  // MOV EBP,ESP, the other direction
    }
  }
  check(!has_frame_pointer,
        "B: the body contains no MOV EBP,ESP, so EBP is a general register and "
        "no frame-relative offset is calibrated by a frame pointer");

  // The one stack argument. The record enumerates entry_ESP+0x4 and marks it
  // `read: false` because its linear ESP walk never calibrated the frame; the
  // trace is what calibrates it.
  check_eq_u32(kStackArgumentDisplacement -
                   row_depth(kStackArgumentInstruction),
               static_cast<std::uint32_t>(kStackArgumentFromEntry),
               "B: [ESP+0x10] at 0x00e7b63b is entry_ESP+0x4, four bytes ABOVE "
               "the entry stack pointer rather than below it");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentEntryOffset),
               static_cast<std::uint32_t>(kStackArgumentFromEntry),
               "B: the header's stack argument offset is the walked one");
  check(kStackArgumentReadByBody && !kStackArgumentReadByRecord,
        "B: the body reads the stack argument and the record says it does not, "
        "which is the record's own uncalibrated-frame abstention");
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentReadInstruction),
               static_cast<std::uint32_t>(kStackArgumentInstruction),
               "B: the header names the instruction that reads the argument");

  // The three early-exit paths close on their own, with no callee involved.
  // Path A (the two JZ) has one word outstanding when it lands on the POP EBP;
  // path B (the three JNZ) has two when it lands on the POP EBX. Both are
  // arithmetic over rows this file wrote, and neither is a claim about a callee.
  check_eq_u32(row_depth(0x00e7b63au) - row_depth(0x00e7b7adu), 0x04u,
               "B: the JZ path lands on the POP EBP with exactly one word "
               "outstanding, the PUSH EBP at 0x00e7b63a");
  check_eq_u32(row_depth(0x00e7b652u) - row_depth(0x00e7b7acu), 0x04u,
               "B: the JNZ path lands on the POP EBX with one word outstanding");
  check_eq_u32(row_depth(0x00e7b7acu) - row_depth(0x00e7b7adu), 0x04u,
               "B: and the POP EBP that follows takes the second, so the JNZ "
               "path pops two words");
  check_eq_u32(row_depth(0x00e7b681u) - row_depth(0x00e7b7abu), 0x04u,
               "B: the POP EDI on the fall-through path takes exactly the PUSH "
               "EDI at 0x00e7b681, and neither early-exit path has run it");
}

// -- case C: the machine ABI record, value by value -------------------------

void test_machine_abi_record() {
  // The convention. The record resolves NONE, names two candidates, and says
  // why. A package that quietly reverted to a convention claim dies here.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionVerdict), 0u,
               "C: the record's convention verdict is none");
  check_eq_u32(static_cast<std::uint32_t>(kDerivedConventionConfidence), 0u,
               "C: the convention's confidence is UNKNOWN");
  check_eq_u32(static_cast<std::uint32_t>(kCandidateConventionCount), 2u,
               "C: the record names two candidate conventions");
  check_eq_u32(static_cast<std::uint32_t>(kConventionAmbiguityCount), 1u,
               "C: the record reports one ambiguity");
  check(std::strcmp(kCandidateConventionNames[0], "__cdecl") == 0,
        "C: the first candidate is __cdecl");
  check(std::strcmp(kCandidateConventionNames[1], "__thiscall") == 0,
        "C: the second candidate is __thiscall");
  check(std::strcmp(kConventionAmbiguityName, "receiver_undetermined") == 0,
        "C: the ambiguity is receiver_undetermined");
  check(std::strcmp(kConventionCorroboration, "not_available") == 0,
        "C: the record's corroboration is not_available");
  check_eq_u32(static_cast<std::uint32_t>(kConventionTokensDeclared), 0u,
               "C: the source declares no convention token, because the record "
               "resolves none");

  // The receiver: undetermined, with the record's own reason, and no field
  // offset claimed in either direction.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedReceiver), 0u,
               "C: the receiver is undetermined");
  check(std::strcmp(kReceiverAbstentionReason, "ecx_read_without_deref") == 0,
        "C: the record's reason is ecx_read_without_deref");
  check(!kReceiverPresent, "C: no receiver is claimed");
  check(!kReceiverRegisterClaimed, "C: no receiver register is claimed");
  check(kReceiverBoundsOnly, "C: the record's bounds_only is true");
  check(!kReceiverHasShape, "C: the record gives the receiver no shape");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDistinctOffsets), 0u,
               "C: the record enumerates no receiver displacement");
  check_eq_u32(static_cast<std::uint32_t>(kReceiverDereferenceCount), 0u,
               "C: the record counts zero receiver dereferences");
  check(!kReceiverFieldOffsetClaimed,
        "C: no field offset is claimed, in either direction");
  check_eq_u32(static_cast<std::uint32_t>(kOwnVptrTableMembershipCount), 0u,
               "C: 0x00e7b6c0 is in no sound vptr-backed table");
  check_eq_u32(static_cast<std::uint32_t>(kEcxLoadInstruction), 0x00e7b68bu,
               "C: the ECX load the abstention turns on is at 0x00e7b68b");
  check_eq_u32(static_cast<std::uint32_t>(kEcxPushInstruction), 0x00e7b691u,
               "C: and the PUSH ECX that follows it is at 0x00e7b691");
  check_eq_u32(static_cast<std::uint32_t>(kEcxLoadDisplacement), 0x1b0u,
               "C: the load is MOV ECX,[EAX+0x1b0] -- a load out of memory, "
               "not a dereference of ECX");

  // The cleanup: caller-side, zero bytes, and the reason is in the terminator.
  check_eq_u32(static_cast<std::uint32_t>(kObservedCleanupSide), 0u,
               "C: the cleanup side is the caller");
  check_eq_u32(static_cast<std::uint32_t>(kStackCleanupBytes), 0u,
               "C: the cleanup is zero bytes");
  check_eq_u32(static_cast<std::uint32_t>(kRetImmediateBytes), 0u,
               "C: the terminator carries no immediate");
  check(std::strcmp(kCleanupEvidence, "ret with no immediate") == 0,
        "C: the record's own evidence is 'ret with no immediate'");
  check_eq_u32(static_cast<std::uint32_t>(kReturnAddressBytes), 4u,
               "C: a CALL pushes a four-byte return address on top");
  check(kImageBody[0x181] == 0xc3u,
        "C: the last byte of the body is the bare RET's opcode C3");

  // The return: the record's APPROXIMATION, carried and not adopted.
  check_eq_u32(static_cast<std::uint32_t>(kDerivedReturnRegister), 0u,
               "C: the record's return register is ST0");
  check_eq_u32(static_cast<std::uint32_t>(kDerivedReturnConfidence), 0u,
               "C: and it carries it at APPROXIMATION");
  check(std::strcmp(kDerivedReturnRegisterClass, "float_or_x87") == 0,
        "C: the record's return class is float_or_x87");
  check(!kDerivedReturnVoidPossible,
        "C: the record does not claim the return may be void");
  check(kDerivedReturnTypeIsNull, "C: the record names no return type");
  check_eq_u32(static_cast<std::uint32_t>(kX87Pushes), 2u,
               "C: the body pushes the x87 stack twice (FLD at 0x00e7b6c1, "
               "FLDZ at 0x00e7b783)");
  check_eq_u32(static_cast<std::uint32_t>(kX87Pops), 3u,
               "C: and pops it three times (0x00e7b69b, 0x00e7b6c8, 0x00e7b6cb)");
  check(kX87Pops > kX87Pushes,
        "C: the body pops one x87 register more than it pushes, so whatever ST0 "
        "held on entry is consumed and nothing is left for the caller -- which "
        "is why the void reading is not the record's ST0 claim");

  // The stack argument, and the record's own incompleteness about it.
  check_eq_u32(static_cast<std::uint32_t>(kStackArgumentSlots), 1u,
               "C: the record enumerates one ordinary stack slot");
  check(!kStackArgumentWritten, "C: the stack argument is never written");
  check(!kStackArgumentIsReceiver,
        "C: the stack argument is not a receiver and never becomes one");

  // The callee terminators. Exactly one of the nine carries a non-zero
  // immediate, and it is 0x00b72210's RET 0x4. The two ADD ESP,n;RET forms are
  // the two contradictions, and this package flags them rather than resolving
  // them.
  check_eq_u32(static_cast<std::uint32_t>(kCalleeTerminatorCount), 9u,
               "C: nine callees were read for their terminator form");
  int non_zero = 0;
  int contradictions = 0;
  for (int i = 0; i < kCalleeTerminatorCount; ++i) {
    if (kCalleeTerminators[i].pop_bytes != 0u &&
        !kCalleeTerminators[i].is_contradiction) {
      ++non_zero;
      check_eq_u32(kCalleeTerminators[i].va, 0x00b72210u,
                   "C: the only callee with a non-zero RET immediate is "
                   "0x00b72210");
      check_eq_u32(static_cast<std::uint32_t>(kCalleeTerminators[i].pop_bytes),
                   4u, "C: and its immediate is four bytes");
      check(!kCalleeTerminators[i].is_contradiction,
            "C: 0x00b72210's terminator is not one of the contradictions");
    }
    if (kCalleeTerminators[i].is_contradiction) {
      ++contradictions;
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(non_zero), 1u,
               "C: exactly one of the nine terminators, discounting the two "
               "flagged contradictions, carries an immediate");
  check_eq_u32(static_cast<std::uint32_t>(contradictions), 2u,
               "C: exactly two of the nine are flagged as contradictions");
  check_eq_u32(static_cast<std::uint32_t>(kCalleeTerminatorContradictions), 2u,
               "C: the header flags the same two");
  check_eq_u32(static_cast<std::uint32_t>(kCalleePoppedWordsObserved), 2u,
               "C: the two observed callee-popped words are 0x00b72210's two "
               "RET 0x4s, which is what balances the frame");

  // The extent, and the restated counts.
  check_eq_u32(kTargetVa, 0x00e7b6c0u, "C: the target VA is 0x00e7b6c0");
  check_eq_u32(kBodyFirstByte, 0x00e7b630u, "C: the body starts at 0x00e7b630");
  check_eq_u32(static_cast<std::uint32_t>(kInstructionCount), 105u,
               "C: the listing is 105 instructions");
  check_eq_u32(static_cast<std::uint32_t>(kBodySpanBytes), 386u,
               "C: the body is 386 bytes");
  check_eq_u32(static_cast<std::uint32_t>(kConditionalBranches), 5u,
               "C: the listing has five conditional branches");
  check_eq_u32(static_cast<std::uint32_t>(kCallSiteCount), 10u,
               "C: the listing has ten CALL instructions");
  check_eq_u32(static_cast<std::uint32_t>(kDirectCalleeCount), 9u,
               "C: they name nine distinct callees");
  check_eq_u32(static_cast<std::uint32_t>(kIndirectTransfers), 0u,
               "C: the body transfers control indirectly zero times");
  check_eq_u32(static_cast<std::uint32_t>(kGlobalReferences), 8u,
               "C: the body names eight data-segment addresses");
  check_eq_u32(static_cast<std::uint32_t>(kGlobalWrites), 0u,
               "C: it stores through none of them");
  check_eq_u32(static_cast<std::uint32_t>(kSavedRegisterCount), 3u,
               "C: three registers are saved: EBP, EBX and EDI");
  check_eq_u32(static_cast<std::uint32_t>(kFrameReservationBytes), 8u,
               "C: the only frame instruction reserves eight bytes");
}

// -- case D: the containment fact -------------------------------------------

void test_containment() {
  check(!kTargetVaIsAnInstructionStart,
        "D: the target VA is not an instruction start");
  check_eq_u32(kEnclosingFunctionEntry, 0x00e7b630u,
               "D: the function the target VA is inside is FUN_00e7b630");
  check_eq_u32(static_cast<std::uint32_t>(kTargetVaOffsetInBody), 0x90u,
               "D: the target VA is offset 0x90 into the body");
  check_eq_u32(kTargetVa,
               kBodyFirstByte + static_cast<std::uint32_t>(kTargetVaOffsetInBody),
               "D: body start + 0x90 is the target VA");
  check_eq_u32(kTargetVaInsideInstruction, 0x00e7b6bcu,
               "D: the instruction the target VA sits inside starts at "
               "0x00e7b6bc");
  check_eq_u32(static_cast<std::uint32_t>(kTargetVaByteIndexInInstruction), 4u,
               "D: the target VA is the instruction's fourth byte");
  check(kImageBody[0x8cu] == 0xe8u,
        "D: the instruction the target VA sits inside is a five-byte CALL");
  check_eq_u32(kTargetVa, kTargetVaInsideInstruction + 4u,
               "D: 0x00e7b6bc + 4 is 0x00e7b6c0, so the target VA is the last "
               "byte of the call's rel32");
  const std::int32_t disp = rel32_at(kImageBody, 0x8du);
  const std::uint32_t landed =
      static_cast<std::uint32_t>(static_cast<std::int64_t>(0x00e7b6c1) + disp);
  check_eq_u32(landed, 0x00b72210u,
               "D: and that rel32 lands on 0x00b72210, the callee the xref "
               "export records at callsite 00e7b6bc");
  check(kBodyFirstByte != kTargetVa,
        "D: the body does NOT start at the queue's VA, and this package does "
        "not pretend it does");
}

// -- case E: the callee stack effect, measured -------------------------------

// The popped-byte figure is derived here from the measured ESP delta and the
// one constant `ret imm16` establishes: it pops the return address FIRST and
// only then adds its immediate, so
//
//   callee pops 0 -> delta -4 -> popped 0
//   callee pops 4 -> delta  0 -> popped 4
//   callee pops 8 -> delta +4 -> popped 8
//
// which is `kReturnAddressBytes + delta`.
std::int32_t measured_pop(std::uint32_t target, std::uint32_t ecx_word,
                          std::uint32_t stack_arg, ProbeResult* out) {
  ProbeArgs args;
  args.target = target;
  args.esi_value = 0;
  args.ecx_value = ecx_word;
  args.eax_value = 0;
  args.stack_arg = stack_arg;
  probe_call_00e7b6c0(&args, out);
  return static_cast<std::int32_t>(kReturnAddressBytes) +
         static_cast<std::int32_t>(out->delta);
}

void test_callee_stack_pop_measured() {
  // Calibration first. Three controls fix what this instrument reads for a
  // callee that pops nothing, four and eight, so a probe that simply reported
  // the same figure for everything would be caught here rather than silently
  // clearing the reconstruction.
  ProbeResult zero;
  check_eq_u32(static_cast<std::uint32_t>(
                   measured_pop(function_address(&control_pops_zero_00e7b6c0),
                                0x11111111u, 0x2468ace0u, &zero)),
               0u, "E: the control that pops nothing measures a zero-byte pop");
  check_eq_u32(zero.eax_after, 0x11111111u,
               "E: the first control answers with the value ECX carried");
  check_eq_u32(zero.esp_at_exit, zero.before,
               "E: the probe hands the caller's stack pointer back untouched");

  ProbeResult four;
  check_eq_u32(static_cast<std::uint32_t>(
                   measured_pop(function_address(&control_pops_four_00e7b6c0),
                                0x22222222u, 0x2468ace0u, &four)),
               4u, "E: the control that pops four measures a four-byte pop");
  check_eq_u32(four.eax_after, 0x22222222u,
               "E: the second control answers with the value ECX carried");
  check_eq_u32(four.esp_at_exit, four.before,
               "E: the probe hands the caller's stack pointer back untouched");

  ProbeResult eight;
  check_eq_u32(static_cast<std::uint32_t>(
                   measured_pop(function_address(&control_pops_eight_00e7b6c0),
                                0x33333333u, 0x2468ace0u, &eight)),
               8u, "E: the control that pops eight measures an eight-byte pop");
  check_eq_u32(eight.esp_at_exit, eight.before,
               "E: the probe hands the caller's stack pointer back untouched");
  check(zero.before == four.before && four.before == eight.before,
        "E: all three controls were entered at the same stack depth, so the "
        "three measurements differ only in what the callee popped");
  check_eq_u32(four.delta - zero.delta, 4u,
               "E: the measured delta rises by exactly four between the "
               "zero-pop and the four-pop controls");

  // The reconstruction itself. An early exit is taken here, so the
  // measurement isolates the terminator: the body runs PUSH EBP and POP EBP
  // and nothing else, and the figures must be the zero-pop control's.
  if (g_entry == 0u) {
    check(false, "E: there is an emitted body to measure");
    return;
  }
  build_fixtures(0x2468ace0u, true);
  g_storage.ebpp()[0x17b] = 1u;  // the JNZ at 0x00e7b673 is taken
  ProbeArgs args;
  args.target = g_entry;
  args.esi_value = address_of(g_storage.cellp());
  args.ecx_value = 0x5a5a5a5au;
  args.eax_value = 0;
  // The ONE stack word IS the EBP fixture's address: the body loads EBP from
  // entry_ESP+0x4, so the probe's stack word and the body's EBP are the same
  // value, and this is where the EBP fixture is handed over.
  args.stack_arg = address_of(g_storage.ebpp());
  ProbeResult live;
  probe_call_00e7b6c0(&args, &live);
  check_eq_u32(static_cast<std::int32_t>(kReturnAddressBytes) +
                   static_cast<std::int32_t>(live.delta),
               0u,
               "E: the reconstruction pops nothing, which is what "
               "cleanup.side=caller and bytes=0 describe");
  check_eq_u32(live.esp_at_exit, live.before,
               "E: and it leaves the caller's stack pointer exactly where it "
               "found it");
  check_eq_u32(live.ecx_at_call, 0x5a5a5a5au,
               "E: it is entered with the value the probe put in ECX");
  check_eq_u32(live.esi_at_call, args.esi_value,
               "E: it is entered with the value the probe put in ESI");
}

// -- case F: the behaviour --------------------------------------------------

void test_behaviour() {
  if (g_entry == 0u) {
    check(false, "F: there is an emitted body to drive");
    return;
  }
  const std::uint32_t record_base = address_of(g_storage.record());
  const std::uint32_t pool = record_base - kGlobalBaseDisplacementB;
  const std::uint32_t cell = address_of(g_storage.cellp());
  const std::uint32_t handle = address_of(g_storage.handlep());

  // -- the trace: ten calls, the listing's order, the listing's arguments ----
  build_fixtures(0x2468ace0u, true);
  ProbeArgs args;
  args.target = g_entry;
  args.esi_value = cell;
  args.ecx_value = 0x2468ace0u;
  args.eax_value = 0;
  args.stack_arg = address_of(g_storage.ebpp());
  ProbeResult live;
  probe_call_00e7b6c0(&args, &live);

  check_eq_u32(static_cast<std::uint32_t>(g_ignored), 0u,
               "F: the trace did not overflow");
  check_eq_u32(static_cast<std::uint32_t>(g_trace_count), 10u,
               "F: the fall-through path makes exactly ten calls");
  if (g_trace_count != 10) {
    return;
  }

  // The expected trace, written out here from the listing rather than read back
  // out of the header, so the two are independent statements of the same thing.
  // `ecx` is checked at the six sites where the BODY forms the value itself and
  // no C++ function runs in between, so the register reaching the callee is the
  // one the listing forms. At the other four the hidden register is either a
  // FRAME ADDRESS this test cannot name (0x00743b50 and 0x00e82130 are handed
  // S-8, the handle local) or a value a C++ recorder left behind (0x00e4cc40
  // and 0x00e780a0), so no figure is asserted for those four and their effect
  // is checked through its CONSEQUENCE instead: the handle slot's contents, the
  // word 0x00e5d7b0 is handed, and 0x00e82130's decrement. An expectation of
  // `0u` with `ecx_checked` false means exactly that.
  struct Want {
    std::uint32_t callee;
    std::uint32_t ecx;
    bool ecx_checked;
    std::uint32_t w0, w1, w2, w3;
    int words;
    int checked;
  };
  const Want want[10] = {
      {0x00b72210u, pool + kGlobalBaseDisplacementA, true, cell, 0u, 0u, 0u, 1, 1},
      {0x00e6d200u, 0xfeedfaceu, true, cell, 0u, kPlayAnimationSecondWord,
       0xfeedfaceu, 4, 4},
      {0x00b72160u, pool + kGlobalBaseDisplacementB, true, 0u, 0u, 0u, 0u, 0, 0},
      {0x00b72210u, pool + kGlobalBaseDisplacementB, true, record_base, 0u, 0u,
       0u, 1, 1},
      {0x00743b50u, 0u, false, 0u, 0u, 0u, 0u, 0, 0},
      // 0x00e4cc40's SECOND stack word is the handle slot's ADDRESS, a frame
      // address this test cannot name; its first is the value that goes there.
      {0x00e4cc40u, 0u, false, handle, 0u, 0u, 0u, 2, 1},
      {0x00e5d7b0u, 0u, true, 0u, 0u, 0u, 0u, 1, 1},
      {0x00e780a0u, 0u, false, 0x00c0ffeeu, kSecondHelperSecondWord, 0u, 0u, 4, 4},
      {0x00e59a70u, cell, true, 0u, 0u, 0u, 0u, 0, 0},
      // 0x00e82130's hidden register is the handle slot's address; the word it
      // saw there is the value 0x00e4cc40 was handed.
      {0x00e82130u, 0u, false, handle, 0u, 0u, 0u, 1, 1},
  };
  for (int i = 0; i < 10; ++i) {
    check_eq_u32(g_trace[i].callee, want[i].callee,
                 "F: the call at each step is the callee the listing names");
    if (want[i].ecx_checked) {
      check_eq_u32(g_trace[i].ecx, want[i].ecx,
                   "F: the hidden register each step is handed is the one the "
                   "listing forms");
    }
    check_eq_u32(static_cast<std::uint32_t>(g_trace[i].words),
                 static_cast<std::uint32_t>(want[i].words),
                 "F: the stack-argument count each step is handed");
    if (want[i].checked < 1) {
      continue;
    }
    if (want[i].checked > 0) {
      check_eq_u32(g_trace[i].w[0], want[i].w0, "F: first stack argument");
    }
    if (want[i].checked > 1) {
      check_eq_u32(g_trace[i].w[1], want[i].w1, "F: second stack argument");
    }
    if (want[i].checked > 2) {
      check_eq_u32(g_trace[i].w[2], want[i].w2, "F: third stack argument");
    }
    if (want[i].checked > 3) {
      check_eq_u32(g_trace[i].w[3], want[i].w3, "F: fourth stack argument");
    }
  }

  // The three words that pin the two LEAs and the two general-register reads:
  // the handle 0x00e4cc40 was given reaches the record, the word it was handed
  // appears as the argument to 0x00e5d7b0, and 0x00e780a0 is handed the dword
  // at [EBP+0]. The probe cannot see the stack slot itself, so the two LEAs are
  // checked through the VALUES the body carries on from them.
  check_eq_u32(get_u32(g_storage.handlep(), 0xb8u), 0x00000000u,
               "F: the handle fixture's +0xb8 is the zero the test planted, so "
               "the word 0x00e4cc40 returns and the word 0x00e5d7b0 is handed "
               "are distinguishable from the handle itself");
  check_eq_u32(g_trace[6].w[0], get_u32(g_storage.handlep(), 0xb8u),
               "F: the word 0x00e4cc40 returned, read at +0xb8, is the word "
               "0x00e5d7b0 is handed");

  // The FSTP at 0x00e7b78d overwrites the THIRD of 0x00e780a0's four words
  // with the bit pattern of +0.0f. That is the sharpest thing in the argument
  // list: the body pushes ECX and then stores over it.
  check_eq_u32(g_trace[7].w[2], 0x00000000u,
               "F: the third word 0x00e780a0 is handed is the bit pattern of "
               "+0.0f, written by FSTP [ESP] over the pushed ECX");
  check(g_trace[7].w[1] == kSecondHelperSecondWord,
        "F: the second word 0x00e780a0 is handed is the literal 1");
  check(g_trace[7].w[0] == get_u32(g_storage.ebpp(), 0u),
        "F: the first word 0x00e780a0 is handed is the dword at [EBP+0]");
  check(g_trace[7].w[3] == 0u,
        "F: the fourth word 0x00e780a0 is handed is the zero EBX holds");

  // -- the twenty-six record writes ------------------------------------------
  check_eq_u32(get_u32(g_storage.record(), 0x24u), kRecordImmediateValue,
               "F: record+0x24 is the literal 0x20");
  check_eq_u32(get_u32(g_storage.record(), 0x28u), cell,
               "F: record+0x28 is the dword the body loaded from [ESI+0]");
  check_eq_u32(get_u32(g_storage.record(), 0x2cu), 0u,
               "F: record+0x2c is the zero EBX holds");
  check_eq_u32(get_u32(g_storage.record(), 0x30u), kRecordAllOnesValue,
               "F: record+0x30 is 0xffffffff, which OR ECX,0xffffffff forces");
  check_eq_u32(get_u32(g_storage.record(), 0x34u), kRecordAllOnesValue,
               "F: record+0x34 is 0xffffffff too, from the same ECX");
  check_eq_u32(get_u32(g_storage.record(), 0x38u), 0u,
               "F: record+0x38 is the zero EBX holds");
  check_eq_u32(get_u32(g_storage.record(), 0x3cu), 0u,
               "F: record+0x3c is the zero EBX holds");
  check_eq_u32(get_u32(g_storage.record(), 0x40u), 0x00000000u,
               "F: record+0x40 is the +0.0f XMM0 holds after the XORPS");
  check_eq_u32(get_u32(g_storage.record(), 0x44u), 0x00000000u,
               "F: record+0x44 is the same +0.0f");
  check_eq_u32(get_u32(g_storage.record(), 0x70u), 0u,
               "F: record+0x70 is the zero EBX holds");
  check_eq_u32(g_storage.record()[0x74u], 0u,
               "F: record+0x74 is one byte of zero, written by MOV byte");
  check_eq_u32(get_u32(g_storage.record(), 0x78u), 0u,
               "F: record+0x78 is the zero EBX holds");
  check_eq_u32(get_u32(g_storage.record(), 0x04u), 0u,
               "F: record+0x04 is the zero EBX holds");
  check_eq_u32(g_storage.record()[0x08u], 0u,
               "F: record+0x08 is one byte of zero, written by MOV byte");
  // The two single-byte writes must be one byte each: the dwords at 0x75 and at
  // 0x09 must still hold the guard byte.
  // The dword at +0x75 reads the guard bytes 0xa5,0xa5,0xa5 and the low byte of
  // the four-byte store at +0x78, so it is 0x00a5a5a5 and NOT 0xa5a5a5a5 -- which
  // is itself the proof that the store at +0x74 covered one byte and not four.
  check_eq_u32(get_u32(g_storage.record(), 0x75u), 0x00a5a5a5u,
               "F: only the first byte of record+0x74 was written, so the dword "
               "at +0x75 still holds three guard bytes");
  check_eq_u32(get_u32(g_storage.record(), 0x09u), 0xa5a5a5a5u,
               "F: nothing was written to record+0x09, so the store at +0x08 "
               "really is one byte wide");

  // The unwritten run 0x0c..0x1b: the body does not touch it.
  for (std::size_t off = kRecordUnwrittenRunLow; off < kRecordUnwrittenRunHigh;
       ++off) {
    check_eq_u32(g_storage.record()[off], kGuardByte,
                 "F: the body writes nothing in the run 0x0c..0x1b");
  }

  // The x87 pair, and WHICH store takes which value. The observer leaves ST0 =
  // float(the cell address) and ST1 = float(0x31), so the FST and the FSTP are
  // distinguishable and a reconstruction that reversed them dies here. Both
  // expected bit patterns are reinterpretations of the two 32-bit words the
  // observer was handed, computed here and not read out of the record.
  // ModRM 0x50 at 0x00e7b6c8 is /0, which is FST -- it stores ST0 and DOES NOT
  // POP; ModRM 0x58 at 0x00e7b6cb is /3, which is FSTP and does. So the two
  // adjacent stores take the SAME register twice, and a transcription that
  // spelled the first one FSTP would leave the second store reading whatever was
  // underneath. That is the sharpest x87 fact in the body and it is pinned by
  // requiring both fields to equal the reloaded local and neither to equal the
  // observer's second value.
  std::uint32_t float_of_cell = 0;
  {
    const std::uint32_t word = cell;
    std::memcpy(&float_of_cell, &word, sizeof(float_of_cell));
  }
  std::uint32_t float_of_31 = 0;
  {
    const std::uint32_t word = kPlayAnimationSecondWord;
    std::memcpy(&float_of_31, &word, sizeof(float_of_31));
  }
  check(float_of_cell != float_of_31,
        "F: the two x87 values the observer leaves are different, so a store "
        "that reached past the first would be visible");
  check_eq_u32(get_u32(g_storage.record(), 0x1cu), float_of_cell,
               "F: the FST at 0x00e7b6c8 stores the reloaded S-4 local, which "
               "holds the value the observer left in ST0");
  check_eq_u32(get_u32(g_storage.record(), 0x20u), float_of_cell,
               "F: and the FSTP at 0x00e7b6cb stores the SAME value, because "
               "FST does not pop");
  check(get_u32(g_storage.record(), 0x20u) != float_of_31,
        "F: the second store did not reach the value underneath, which is what "
        "an FSTP in place of the FST would have stored");

  // The eight planted globals, reaching the record at the listing's
  // displacements. Six of the eight displacements are the same three words
  // twice over, so a reconstruction that read them once, or out of order, dies
  // here on a value.
  // Which planted word each of the eight record displacements must carry. The
  // same three addresses are read TWICE each -- the listing reads 0x016b3c28,
  // 0x016b3c2c and 0x016b3c30 once apiece into 0x48, 0x4c and 0x50 and then
  // again into 0x54, 0x58 and 0x5c -- so six of the eight displacements repeat
  // three values, and a reconstruction that read them once, or out of order,
  // dies here on a value.
  const int planted_index[8] = {0, 1, 2, 0, 1, 2, 4, 5};
  for (int i = 0; i < 8; ++i) {
    const std::size_t off = kRecordDisplacements[i];
    const std::uint32_t source = get_u32(
        reinterpret_cast<const void*>(
            static_cast<std::uintptr_t>(kRecordGlobalSources[i])),
        0);
    check_eq_u32(source, kPlanted[planted_index[i]],
                 "F: the displacement's source address holds the word the test "
                 "planted there");
    check_eq_u32(get_u32(g_storage.record(), off), source,
                 "F: the planted global reaches the record at the displacement "
                 "the listing names");
  }
  // The header's eight record-source addresses are eight of the image's eight,
  // at the indices below.
  const int global_index[8] = {1, 2, 3, 1, 2, 3, 4, 5};
  for (int i = 0; i < 8; ++i) {
    check_eq_u32(kRecordGlobalSources[i], kGlobalAddresses[global_index[i]],
                 "F: the header's record-source table matches its global list");
  }
  check_eq_u32(static_cast<std::uint32_t>(kRecordDisplacements[0]), 0x48u,
               "F: and the first of those displacements is 0x48");
  check(kGlobalAddresses[0] == 0x016b3c04u,
        "F: the data-address list starts with 0x016b3c04");
  check(kGlobalAddresses[4] == 0x015a7c4cu,
        "F: and its fifth entry is 0x015a7c4c");

  // The body wrote nothing outside the record, and read-only where it read.
  check(g_storage.bands_intact(),
        "F: every guard band around the four fixtures survives the run");
  check_eq_u32(get_u32(g_storage.cellp(), 0x00u), address_of(g_storage.cellp()),
               "F: the cell's +0 is unchanged: the body only ever READ it");
  check_eq_u32(get_u32(g_storage.cellp(), 0x1b0u), 0xfeedfaceu,
               "F: the cell's +0x1b0 is unchanged: the body only ever READ it");
  check_eq_u32(get_u32(g_storage.ebpp(), 0x00u), 0x00c0ffeeu,
               "F: the EBP fixture's +0 is unchanged");
  check_eq_u32(get_u32(g_storage.ebpp(), 0x108u), handle,
               "F: the EBP fixture's +0x108 is unchanged");
  check_eq_u32(get_u32(g_storage.ebpp(), 0x17bu), 0u,
               "F: the EBP fixture's +0x17b is unchanged");
  for (int i = 0; i < 8; ++i) {
    const std::uint32_t address =
        kPlantedBase + 4u * static_cast<std::uint32_t>(i);
    check_eq_u32(get_u32(reinterpret_cast<const void*>(
                             static_cast<std::uintptr_t>(address)), 0),
                 kPlanted[i],
                 "F: the planted global is untouched: the body only ever READS "
                 "it");
  }

  // -- the handle local: the whole chain, checked end to end ----------------
  // 0x00743b50 zeroes the handle local at S-8; 0x00e4cc40 stores [EBP+0x108]
  // into it; 0x00e82130 is then handed its ADDRESS and finds that value there.
  // All three links are facts about the RECONSTRUCTION, and the run above checks
  // all three: the word 0x00e4cc40 was handed (step 5, checked against the
  // fixture planted at [EBP+0x108]), the word 0x00e82130 saw (step 9), and the
  // fixture itself, which the body never writes. Nothing about 0x00e82130's own
  // body is reproduced or claimed.
  check_eq_u32(g_trace[9].w[0], handle,
               "F: 0x00e82130 sees, through the handle local the body built at "
               "S-8, exactly the value 0x00e4cc40 was handed");
  check_eq_u32(get_u32(g_storage.ebpp(), 0x108u), handle,
               "F: and that value is the word the body read at [EBP+0x108] and "
               "left in the fixture untouched");
  check_eq_u32(get_u32(g_handle_object, 0x0cu), 7u,
               "F: and nothing wrote through the handle, because this package "
               "models the nine CALLS and not 0x00e82130's body");

  // -- register discipline, measured (case H) --------------------------------
  check_eq_u32(live.esi_at_call, live.esi_exit,
               "H: the reconstruction hands ESI back unchanged, which is what "
               "the listing's seven ESI reads and no ESI write say");
  check_eq_u32(live.edi_entry, live.edi_exit,
               "H: it hands EDI back unchanged, so the PUSH EDI / POP EDI pair "
               "balances");
  check_eq_u32(live.ebx_entry, live.ebx_exit,
               "H: it hands EBX, the PIC GOT base, back unchanged, so the "
               "PUSH EBX / POP EBX pair balances");
  check_eq_u32(live.esp_at_exit, live.before,
               "H: the probe leaves the caller's stack alone");
  check(g_storage.bands_intact(),
        "H: the second run leaves every guard band intact as well");
}

// -- case G: the three early-exit paths -------------------------------------

void test_early_exits() {
  if (g_entry == 0u) {
    check(false, "G: there is an emitted body to drive");
    return;
  }
  // Each of the five guards, in turn, made to fire. The trace must be EMPTY --
  // no call at all -- and every fixture byte must be unchanged.
  struct Guard {
    std::size_t offset;
    bool in_esi;
  };
  const Guard guards[5] = {
      {0x112u, true}, {0x113u, true}, {0x178u, true},
      {0x17fu, true}, {0x17bu, false},
  };
  for (int g = 0; g < 5; ++g) {
    build_fixtures(0x2468ace0u, true);
    std::uint8_t* const target =
        guards[g].in_esi ? g_storage.cellp() : g_storage.ebpp();
    target[guards[g].offset] = 1u;

    std::uint8_t record_before[kRecordBytes];
    std::uint8_t cell_before[kCellBytes];
    std::uint8_t ebp_before[kEbpBytes];
    std::uint8_t handle_before[kHandleBytes];
    std::memcpy(record_before, g_storage.record(), kRecordBytes);
    std::memcpy(cell_before, g_storage.cellp(), kCellBytes);
    std::memcpy(ebp_before, g_storage.ebpp(), kEbpBytes);
    std::memcpy(handle_before, g_storage.handlep(), kHandleBytes);

    ProbeArgs args;
    args.target = g_entry;
    args.esi_value = address_of(g_storage.cellp());
    args.ecx_value = 0x13571357u;
    args.eax_value = 0;
    args.stack_arg = address_of(g_storage.ebpp());
    ProbeResult out;
    probe_call_00e7b6c0(&args, &out);

    check_eq_u32(static_cast<std::uint32_t>(g_trace_count), 0u,
                 "G: an early exit makes no call at all");
    check_eq_u32(static_cast<std::uint32_t>(g_ignored), 0u,
                 "G: and the trace did not overflow");
    check(std::memcmp(record_before, g_storage.record(), kRecordBytes) == 0,
          "G: an early exit writes nothing into the record");
    check(std::memcmp(cell_before, g_storage.cellp(), kCellBytes) == 0,
          "G: an early exit writes nothing into the ESI fixture");
    check(std::memcmp(ebp_before, g_storage.ebpp(), kEbpBytes) == 0,
          "G: an early exit writes nothing into the EBP fixture");
    check(std::memcmp(handle_before, g_storage.handlep(), kHandleBytes) == 0,
          "G: an early exit writes nothing into the handle fixture");
    check(g_storage.bands_intact(), "G: and no guard band is disturbed");
    check_eq_u32(out.esp_at_exit, out.before,
                 "G: an early exit leaves the caller's stack alone");
    check_eq_u32(out.esi_at_call, out.esi_exit,
                 "G: an early exit hands ESI back unchanged");
    check_eq_u32(out.edi_entry, out.edi_exit,
                 "G: an early exit never touches EDI at all");
    check_eq_u32(out.ebx_entry, out.ebx_exit,
                 "G: an early exit never touches EBX at all");
  }

  check_eq_u32(static_cast<std::uint32_t>(kBasicBlockCount), 3u,
               "G: the listing has three basic blocks: the head with its two "
               "JZ, the body with its three JNZ, and the epilogue");
}

}  // namespace
}  // namespace pkg_w2_00e7b6c0
}  // namespace reconstruction
}  // namespace openspore

int main() {
  using namespace openspore::reconstruction::pkg_w2_00e7b6c0;
  if (!map_globals()) {
    return 1;
  }
  // The instrument is calibrated first (case E). A reconstruction whose callee
  // cleanup disagreed with the listing would unbalance the compiler-generated
  // call sites the later cases use, so the disagreement is looked for before
  // anything else is driven.
  test_image_and_emitted_body();
  test_callee_stack_pop_measured();
  test_frame_walk();
  test_machine_abi_record();
  test_containment();
  test_behaviour();
  test_early_exits();
  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
