#pragma once

// PKG-DFW-006A1540 -- opaque boundary types for the reconstruction of VA
// 0x006a1540, the 74-instruction body 0x006a1540..0x006a15f5 in
// SPORE/SporeBin/SporeApp.exe 3.1.0.22
// (sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// The knowledge record names this target "App::PropertyList::Write". The binary
// carries no MSVC RTTI (a headless vtable pass was never run, 0 vtable labels)
// and no published SDK structure for the class, so NOTHING here carries a member
// name taken from the demangled symbol. Every word below is identified by the
// machine displacement that fixes it and by the instruction that reads it. Where
// the live Ghidra signature disagrees with the demangled symbol -- it types the
// receiver `DirectPropertyList *` while the record's own name says
// App::PropertyList -- the disagreement is recorded, not resolved, and the model
// claims no class identity at all.
//
// Evidence used for every declaration below:
//   - GhidraMCP /disassemble_function @ 0x006a1540 (74 instructions,
//     0x006a1540..0x006a15f3, last instruction `RET 0x4`)
//   - reconstruction/evidence/006a1540/evidence.json (disassembly, abi,
//     abi_derived, ghidra_function, decompilation categories)
//   - reconstruction/knowledge/index.json record "0x006a1540"
//
// What this body establishes about its receiver, in full:
//   +0x18  a pointer, read four times (0x006a154d, 0x006a1577, 0x006a15a4,
//          0x006a15c4). This body never writes through it.
//   +0x1c  a pointer, read twice (0x006a154a, 0x006a1574). This body never
//          writes through it.
//   Nothing else. The model therefore stops at +0x20. A parent word at +0x30 and
//   a mode byte at +0x2c exist in other reconstructions of the same table, but
//   this body never reaches them, so they are not declared here.

#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-dfw-006a1540 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4, "pkg-dfw-006a1540 requires 32-bit pointers");

namespace openspore::reconstruction::pkg_dfw_006a1540 {

using Word = std::uint32_t;

// The single ordinary stack argument (entry_ESP+0x4), read at 0x006a1543.
//
// This body never dereferences it. Across all 74 instructions the pointer value
// appears only as the FIRST argument of the three direct calls (0x006a156a,
// 0x006a15b3, 0x006a15cf) and nowhere else, so the only thing established here
// is that it is a 4-byte value that is passed on. The live Ghidra signature
// calls it `IStream *`; no record for this target establishes that class, so the
// type stays opaque and is named for the shape the evidence supports: a sink.
struct OpaqueStreamSink;

// One element of the range the body walks.
//
// Established here, and nothing more:
//   +0x00  a 4-byte word, read once per element and handed to the second
//          write-words call: 0x006a15a7 `MOV EAX,dword ptr [EDI + EDX*0x1]`,
//          stored to the spill slot at 0x006a15b4 and passed at 0x006a15b8.
//   +0x04  an address formed and handed to the third call: 0x006a15c4
//          `MOV EAX,dword ptr [ESI + 0x18]` / 0x006a15c7 `ADD EAX,EDI` /
//          0x006a15cb `ADD EAX,0x4` / 0x006a15ce `PUSH EAX`. The body forms
//          the address and never reads or writes through it.
//   stride 0x18, fixed by 0x006a15e2 `ADD EDI,0x18`.
//
// The 0x14 bytes from +0x04 to +0x17 are carried as opaque on purpose. The
// conflict ledger holds TB-FL-006 ("App::Property 4-byte versus 0x14-byte
// layout", resolution_status preserved_alternatives) precisely because a stride
// and a 4-byte entry word do not settle the payload's extent. This body reads
// one word at +0x00 and forms one address at +0x04, so it cannot settle it
// either, and the bytes stay unnamed.
struct alignas(4) OpaquePropertyEntry {
  Word word_00;                     // displacement 0x00, read at 0x006a15a7
  std::uint8_t opaque_04_17[0x14];  // displacement 0x04..0x17, never touched here
};

// The receiver.
//
// Established here, and nothing more:
//   +0x18  the range begin, read at 0x006a154d, 0x006a1577, 0x006a15a4 and
//          0x006a15c4. Re-read on every use; this body never hoists it.
//   +0x1c  the range end, read at 0x006a154a and 0x006a1574.
//
// +0x00..+0x17 is declared as opaque filler so the two pointers land on the
// displacements the listing fixes, and the model stops at +0x20 because +0x1c is
// the last displacement this body reaches.
struct alignas(4) OpaquePropertyList {
  std::uint8_t opaque_00_17[0x18];       // displacement 0x00..0x17, never touched
  OpaquePropertyEntry *range_begin_018;  // displacement 0x18
  OpaquePropertyEntry *range_end_01c;    // displacement 0x1c
};

static_assert(offsetof(OpaquePropertyEntry, word_00) == 0x00,
              "the element word must sit at displacement 0x00 (0x006a15a7)");
static_assert(offsetof(OpaquePropertyEntry, opaque_04_17) == 0x04,
              "the element payload must sit at displacement 0x04 (0x006a15cb)");
static_assert(sizeof(OpaquePropertyEntry) == 0x18,
              "the loop stride at 0x006a15e2 is 0x18 bytes");
static_assert(offsetof(OpaquePropertyList, range_begin_018) == 0x18,
              "the range begin must sit at displacement 0x18 (0x006a154d)");
static_assert(offsetof(OpaquePropertyList, range_end_01c) == 0x1c,
              "the range end must sit at displacement 0x1c (0x006a154a)");
static_assert(sizeof(OpaquePropertyList) == 0x20,
              "the model stops at +0x20; this body reaches no displacement past "
              "+0x1c");

// The machine ABI record (`categories.abi_derived.value.abi`) states
// __thiscall with confidence SUPPORTED, and the body ends in `RET 0x4` at
// 0x006a15f3, which is the terminator that puts the single stack dword under
// callee-pop cleanup and rules out cdecl and fastcall. The receiver arrives in
// ECX and is aliased into ESI at 0x006a1548.
//
// GCC 16 rejects the bare `__thiscall` / `__cdecl` keywords, so the convention
// is spelled per toolchain and referenced by macro at every use site. The GCC
// spelling `__attribute__((thiscall))` implies callee-pops, which is exactly
// what `RET 0x4` does here: this body pops its own single stack argument, so
// the one-argument declaration below is the arity the machine fixes, not a
// guess.
#if defined(_MSC_VER)
#define PKG_DFW_006A1540_THISCALL __thiscall
#define PKG_DFW_006A1540_CDECL __cdecl
#else
#define PKG_DFW_006A1540_THISCALL __attribute__((thiscall))
#define PKG_DFW_006A1540_CDECL __attribute__((cdecl))
#endif

// ---------------------------------------------------------------------------
// The target
// ---------------------------------------------------------------------------
//
// Declaration text, and the reason for every part of it:
//   * one receiver in ECX, aliased into ESI at 0x006a1548;
//   * one ordinary stack dword at entry_ESP+0x4, read at 0x006a1543 and passed
//     on unmodified -- never written, never dereferenced;
//   * `bool` in EAX, fixed by 0x006a15ef `MOV AL,BL` over BL, which is the
//     record's own `types` token ("bool") and the live Ghidra return_type.
extern "C" bool PKG_DFW_006A1540_THISCALL
proplist_write_006a1540(OpaquePropertyList *list, OpaqueStreamSink *sink);

// ---------------------------------------------------------------------------
// Callees this package does not own
// ---------------------------------------------------------------------------
//
// Both are declared, not defined, here; the model test defines each as an
// observer. Neither record for either address states a convention, so what is
// declared is only what this body's own listing fixes: how many words it pushes,
// in which order, and who removes them.

// 0x0093aa70, called at 0x006a156f and again at 0x006a15b8.
//
// Both call sites push four dwords and the body then runs `ADD ESP,0x10` at
// 0x006a158d and 0x006a15bd. Four pushed plus one for the return address is
// five, and four are removed, so this callee pops nothing and ends in a bare
// RET. The argument order is the push order, right to left:
//   0x006a155a PUSH 0x0    fourth argument
//   0x006a155e PUSH 0x1    third argument
//   0x006a1560 LEA ECX,[ESP + 0x14] / 0x006a1567 PUSH ECX   second argument
//   0x006a156a PUSH EBP    first argument, the stack dword
// so the shape is (sink, word pointer, 1, 0) at both sites and only the value
// behind the word pointer differs. The return word is consumed by `MOV BL,AL` at
// 0x006a157a and by `TEST AL,AL` at 0x006a15c0, i.e. this body reads one byte
// of it; the observer returns `bool` for that reason and no other.
extern "C" bool PKG_DFW_006A1540_CDECL
dfw_write_words_0093aa70(OpaqueStreamSink *sink, const Word *words, Word count,
                         Word format);

// 0x00693390, called at 0x006a15d0.
//
// Three dwords are pushed (0x006a15c9 `PUSH 0x0`, 0x006a15ce `PUSH EAX`,
// 0x006a15cf `PUSH EBP`) and the body runs `ADD ESP,0xc` at 0x006a15d5, so this
// callee also pops nothing and ends in a bare RET. The argument order is
// (sink, the address formed at base+offset+0x4, 0). The body forms that address
// and never dereferences it, so the payload is typed as an opaque byte address
// rather than as anything with a known layout. As above, the return word is read
// as one byte (`TEST AL,AL` at 0x006a15d8).
extern "C" bool PKG_DFW_006A1540_CDECL
dfw_write_entry_00693390(OpaqueStreamSink *sink, std::uint8_t *payload,
                         Word format);

// ---------------------------------------------------------------------------
// Accessors, one per machine displacement
// ---------------------------------------------------------------------------
//
// Every displacement this body reaches is named exactly once, here, next to the
// instruction that fixes it. The reconstructed body then states the machine
// operations themselves and nothing else, which is why its only literal is the
// 0x18 stride.

// Reinterpret a 32-bit pattern as a signed value. memcpy rather than a cast, so
// the conversion is defined rather than implementation-defined on the two
// patterns whose top bit is set (every negative count this body can produce).
inline std::int32_t as_signed(Word bits) {
  std::int32_t value = 0;
  std::memcpy(&value, &bits, sizeof value);
  return value;
}

// Reinterpret a signed value as its 32-bit pattern, so the two shifts below
// operate on the same bits the machine's registers hold.
inline Word as_unsigned(std::int32_t value) {
  Word bits = 0;
  std::memcpy(&bits, &value, sizeof bits);
  return bits;
}

// 0x006a1557 SAR EDX,0x2.
//
// The arithmetic shift, spelled out because the sign fill is load-bearing: on a
// negative EDX a logical shift would give a different answer, which is the whole
// reason the compiler emitted SAR for the quotient and SHR only for the sign
// mask. The `shift == 0` arm keeps the shift width out of range.
inline std::int32_t sar32(Word bits, unsigned int shift) {
  const Word fill = shift == 0u ? 0u : (0xffffffffu << (32u - shift));
  const Word sign = (bits >> 31) != 0u ? fill : 0u;
  return as_signed((bits >> shift) | sign);
}

// 0x006a1550 MOV EAX,0x2aaaaaab / 0x006a1555 IMUL ECX / 0x006a1557 SAR EDX,0x2
// 0x006a155c MOV EAX,EDX / 0x006a1564 SHR EAX,0x1f / 0x006a1568 ADD EAX,EDX
//
// The signed division of the byte span by 0x18, reproduced instruction for
// instruction in 32-bit two's-complement arithmetic rather than written as `/`.
// Note the asymmetry the listing fixes: SAR for the quotient (0x006a1557) and
// SHR for the sign mask (0x006a1564), so the mask below is a logical shift and
// yields 0 or 1, not a sign fill.
inline std::int32_t entry_count_for_span(std::int32_t span) {
  const std::uint64_t product =
      0x2aaaaaabu * static_cast<std::uint64_t>(static_cast<std::int64_t>(span));
  const std::int32_t high =
      as_signed(static_cast<Word>(product >> 32));  // EDX:EAX from IMUL ECX
  const std::int32_t quotient = sar32(as_unsigned(high), 2u);  // SAR EDX,0x2
  const std::int32_t bias =
      static_cast<std::int32_t>(as_unsigned(quotient) >> 31);  // SHR EAX,0x1f
  return quotient + bias;                                      // ADD EAX,EDX
}

// 0x006a154a MOV ECX,[ESI+0x1c] / 0x006a154d SUB ECX,[ESI+0x18]
//
// The signed 32-bit byte span. The machine subtracts two 32-bit words, so the
// result is the low 32 bits of the address difference read as signed; the
// truncation is written out rather than left to pointer arithmetic.
inline std::int32_t range_span_bytes(const OpaquePropertyList *list) {
  const std::uintptr_t begin =
      reinterpret_cast<std::uintptr_t>(list->range_begin_018);
  const std::uintptr_t end = reinterpret_cast<std::uintptr_t>(list->range_end_01c);
  return as_signed(static_cast<Word>(end - begin));
}

// 0x006a154a..0x006a1568 and again 0x006a1574..0x006a158b.
//
// The quotient, as the body computes it. It is called twice by the
// reconstruction because the machine evaluates the span, and therefore the
// division, twice, with the first stream call in between; see the body.
inline std::int32_t list_entry_count(const OpaquePropertyList *list) {
  return entry_count_for_span(range_span_bytes(list));
}

// 0x006a154d / 0x006a1577 / 0x006a15a4 `MOV EDX,dword ptr [ESI + 0x18]` and
// 0x006a15c4 `MOV EAX,dword ptr [ESI + 0x18]`.
//
// The range begin, re-read from the receiver at each of those four sites. The
// body keeps the re-read: nothing in it hoists the word, so a receiver whose
// +0x18 changed between two iterations would be followed. Passing a byte offset
// into this accessor is how that is observable in a test.
inline const std::uint8_t *range_begin_at(const OpaquePropertyList *list) {
  return reinterpret_cast<const std::uint8_t *>(list->range_begin_018);
}

// 0x006a15a7 MOV EAX,dword ptr [EDI + EDX*0x1].
//
// The element's 4-byte word at +0x00. memcpy rather than a load, so the model
// makes no alignment claim the machine does not make.
inline Word entry_word_00(const std::uint8_t *entry) {
  Word value = 0;
  std::memcpy(&value, entry, sizeof value);
  return value;
}

// 0x006a15c4 MOV EAX,[ESI+0x18] / 0x006a15c7 ADD EAX,EDI / 0x006a15cb ADD EAX,0x4
// / 0x006a15ce PUSH EAX.
//
// The address of the element's payload, i.e. the element base advanced by 0x4.
// The body forms this address and passes it on; it never dereferences it, which
// is why the return type is a byte address and not a pointer to a known type.
inline std::uint8_t *entry_payload_04(const std::uint8_t *entry) {
  return reinterpret_cast<std::uint8_t *>(
      const_cast<std::uint8_t *>(entry) + 0x4u);
}

} // namespace openspore::reconstruction::pkg_dfw_006a1540
