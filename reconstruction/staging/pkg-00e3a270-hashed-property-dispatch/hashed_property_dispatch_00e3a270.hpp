// PKG-00E3A270-HASHED-PROPERTY-DISPATCH -- VA 0x00e3a270
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, offsets and the call-boundary declaration for FUN_00e3a270 -- the
// hashed-property dispatcher whose Ghidra body runs 0x00e3a270..0x00e3a56a
// inclusive, 763 bytes, 172 instructions. This worker's target is that
// function's own ENTRY address, so the span claimed here is the whole body.
//
// EVERY NUMBER IN THIS HEADER COMES FROM THE LISTING. The 172 instructions were
// read back from the committed Ghidra program (disassemble_function on
// 0x00e3a270, which returned 172 instructions at those addresses), and the two
// load-bearing facts below were additionally confirmed against raw image bytes
// rather than against Ghidra's mnemonic rendering. Nothing here is inferred from
// a symbol, a class name or a caller.
//
// 1. THE SELECTOR: TWENTY-SEVEN 32-BIT IDS. Twenty-seven `CMP EAX,<imm32>` and
//    no other 32-bit immediate in the dispatch. They are the values the body
//    matches against; this repository holds no table that inverts any of them, so
//    none is named beyond its own literal value and NO arm is named for a
//    property. Which arm each id reaches is stated per id in the .cpp, and that
//    mapping is not a guess: every id is reached through a chain of JG / JZ /
//    JNE whose operands and targets all lie inside this body.
//
// 2. THE DISPATCH IS SIGNED. This is the most fragile fact in the body and it
//    is confirmed from bytes, not from a mnemonic. Every ordering branch is JG:
//    `0F 8F rel32` at 0x00e3a279, 0x00e3a28a, 0x00e3a297, 0x00e3a3a8,
//    0x00e3a3b9 and 0x00e3a4c3, and the short form `7F rel8` at 0x00e3a33c
//    (bytes read back from the image: 32 d8 7f 4c 0f 84 d3 01 00 00, i.e.
//    `CMP EAX,0xd832b059` / `JG +0x1d3`). JG is a SIGNED greater-than.
//
//    Fifteen of the twenty-seven selector values have the high bit set and are
//    therefore NEGATIVE read as int32 (0x8133fb2e, 0x980e43f2, 0x99f0d1da,
//    0x9f792b4c, 0xa0973374, 0xa6cb4c9f, 0xaaf6aaac, 0xade76cce, 0xcdb3696f,
//    0xd536c91d, 0xd832b059, 0xdca976d0, 0xe0bc9d45, 0xf278934a, 0xf967827c)
//    and twelve are positive. A C++ `>` on a std::uint32_t is UNSIGNED, and the
//    two readings agree only where both operands share a sign bit.
//
//    The consequence is exact and it is why signed_greater() exists below. The
//    root pivot is 0xf278934a, itself negative. The fifteen negative selectors
//    therefore compare against it identically under either reading and are
//    routed correctly even by a wrong reconstruction. The twelve POSITIVE
//    selectors do not: signed they are ABOVE the root pivot and belong to the
//    high half; unsigned they are BELOW it and fall into the low half -- whose
//    seven leaf tests (0xaaf6aaac, 0x9f792b4c, 0x8133fb2e, 0x980e43f2,
//    0x99f0d1da, 0xa0973374, 0xa6cb4c9f) are ALL negative values, so under the
//    wrong reading all twelve selectors match no case at all, write nothing,
//    call nothing, and leave EAX holding the selector. The .cpp spells every
//    ordering compare signed_greater() and the model test drives all twenty-seven
//    selectors specifically to separate the two readings.
//
// 3. THE RECEIVER DISPLACEMENTS: NINETEEN. Nothing is read or written through
//    any other base at any other offset in the 172 instructions. Sixteen appear
//    as memory operands under ECX and account for every store the body makes;
//    the remaining three (0x29c, 0x2b4, 0x2c0) are produced by `ADD ECX,<disp>`
//    and then PUSHed, so the listing shows no memory operand under them:
//
//      +0x29c +0x2b4 +0x2c0            three call destinations, never stored to
//                                      by THIS body -- only by the callee
//      +0x2a8 +0x2ac +0x2b0 +0x2cc +0x2d0 +0x2d4   six single words
//      +0x308 +0x30c +0x310            three single words
//      +0x314 +0x318 +0x31c +0x320 +0x324 +0x328   three pairs
//      +0x32c                         one word, the tag word
//
//    The largest displacement this body can touch is +0x32c and every access
//    there is a dword, so 0x32c + 4 == 0x330 is the last byte it can reach and
//    the modelled object is exactly that size. That is a LOWER BOUND derived
//    from this body's own accesses, not a measurement of the real object.
//
// 4. THE SECOND ORDINARY STACK ARGUMENT: A POINTER, read at [ESP+0x8] in ten
//    places, from which exactly one word is ever read: +0x0c. That word is
//    used as a BASE, not as a value. The body computes q = record[+0x0c] and
//    then reads q[+0x08], q[+0x0c], q[+0x10] and q[+0x14] -- two levels of
//    indirection, never one, and never a member of the record itself. The
//    callee at 0x00e39420 reads the same +0x0c as a base and indexes it the same
//    way, so the shape is corroborated from outside this body.
//
// 5. THE ONE DIRECT CALLEE: 0x00e39420, called from three sites (0x00e3a2da,
//    0x00e3a4fe, 0x00e3a560), always as (record, 0x3, self + {0x2c0, 0x2b4,
//    0x29c}) in that push order. 47 bytes, decompiled independently for this
//    package: it null-checks its first argument, reads [record+0xc] as a base,
//    and writes dest[+0x4] = q[index], dest[+0x0] = q[index+1],
//    dest[+0x8] = q[index+2] -- a rotation, not a straight copy. Its last write
//    to EAX is `MOV EAX,[EAX+0xc]`, so it RETURNS the value-block pointer, and
//    this body FORWARDS that: nothing but `ADD ESP,0xc` and `RET 0x8` follows
//    any of the three calls. Each call is followed by `ADD ESP,0xc`, so the
//    callee is cdecl.
//
// 6. NOT CLAIMED ANYWHERE BY THIS HEADER:
//    * a class name. The triage subsystem says "Simulator", but SporeApp.exe
//      carries no MSVC RTTI, no persisted symbol names this address, and no
//      record in this repository associates a type with it. The type below is
//      called Simulator for readability and for nothing else.
//    * what any of the nineteen receiver words MEANS. Three are 12-byte
//      destinations handed to a helper; 0x2a8/0x2ac/0x2b0 and 0x2cc/0x2d0/0x2d4
//      are triples each written by one arm; 0x314/0x318, 0x31c/0x320 and
//      0x324/0x328 are pairs whose secondary is stored unconditionally and whose
//      primary is stored only while the primary is still zero; and 0x32c takes
//      five of six consecutive immediates. NONE of that is named as a member,
//      because no machine record anywhere in this repository names a member at
//      any displacement. The displacement accessors below are used INSTEAD of
//      declared members, which is what keeps every store falsifiable: a wrong
//      displacement lands on a decoy the test planted.
//    * what the immediates 0x1654c00..0x1654c05 ARE. They are five of six
//      consecutive 32-bit values written to the same receiver word, four behind
//      a `CMP DWORD PTR [ECX+0x32c],0xffffffff` / JNZ guard and one
//      (0x1654c00) written unconditionally. The guard and the values are
//      reproduced; the meaning is not claimed. Note that 0x1654c03 never
//      appears anywhere in the body.
//    * the preimages of the twenty-seven selector hashes.
//    * what the returned value means. See the declaration at the bottom.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-00e3a270-hashed-property-dispatch requires an x86-32 target"
#endif

// The one convention, fixed by machine bytes rather than chosen for
// convenience. ECX is the receiver: it is dereferenced at all nineteen
// displacements and is never written through any other register. The
// terminator is `C2 08 00`, RET 0x8, at thirteen separate sites (0x00e3a2e2,
// 0x00e3a31b, 0x00e3a334, 0x00e3a361, 0x00e3a387, 0x00e3a3a0, 0x00e3a416,
// 0x00e3a44f, 0x00e3a49e, 0x00e3a4bb, 0x00e3a506, 0x00e3a543, 0x00e3a568),
// so the callee pops its own eight bytes of stack arguments. That rules out
// cdecl, which would need an ADD ESP in the body and a bare RET, and it rules
// out fastcall, which would place the first ordinary argument in EDX.
#if defined(_MSC_VER)
#define PKG_00E3A270_THISCALL __thiscall
#else
#define PKG_00E3A270_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00e3a270_dispatch {

using Word = std::uint32_t;

// -- the signed comparison the dispatch actually performs --------------------
// The body's ordering branches are all JG (0x0F 8F, and 0x7F in its short
// form), which is a SIGNED above. Fifteen of the twenty-seven selector values
// have the high bit set and are negative read signed, so a C++ `>` on a
// std::uint32_t -- UNSIGNED -- silently re-routes twelve of them into a half
// whose leaf tests are all negative, making them all no-ops. The cast is the
// honest spelling of what the opcode says: the two's-complement
// reinterpretation of a value above 0x7fffffff is what the JG does.
inline bool signed_greater(Word left, Word right) {
  return static_cast<std::int32_t>(left) > static_cast<std::int32_t>(right);
}

// -- the twenty-seven selector immediates ------------------------------------
// One per `CMP EAX,<imm32>` in the dispatch, named for their own value and for
// nothing else. 0xf278934a is the ROOT PIVOT because the body's first compare is
// against it (0x00e3a274); the other four pivots are 0xaaf6aaac, 0x9f792b4c on
// the low side and 0x3e2a3040, 0x279c4e55, 0x6cd9ec7b, 0xd832b059 on the high
// side. Every remaining constant is a leaf test, not a pivot.
constexpr Word kSelector_13df9c1c = 0x13df9c1cu;
constexpr Word kSelector_25ca9233 = 0x25ca9233u;
constexpr Word kSelector_279c4e55 = 0x279c4e55u;
constexpr Word kSelector_2cfa39dd = 0x2cfa39ddu;
constexpr Word kSelector_3b38f92a = 0x3b38f92au;
constexpr Word kSelector_3e2a3040 = 0x3e2a3040u;
constexpr Word kSelector_5c51063f = 0x5c51063fu;
constexpr Word kSelector_5fcf28d0 = 0x5fcf28d0u;
constexpr Word kSelector_6a9f2620 = 0x6a9f2620u;
constexpr Word kSelector_6cd9ec7b = 0x6cd9ec7bu;
constexpr Word kSelector_7115ede5 = 0x7115ede5u;
constexpr Word kSelector_7bceaa86 = 0x7bceaa86u;
constexpr Word kSelector_8133fb2e = 0x8133fb2eu;
constexpr Word kSelector_980e43f2 = 0x980e43f2u;
constexpr Word kSelector_99f0d1da = 0x99f0d1dau;
constexpr Word kSelector_9f792b4c = 0x9f792b4cu;
constexpr Word kSelector_a0973374 = 0xa0973374u;
constexpr Word kSelector_a6cb4c9f = 0xa6cb4c9fu;
constexpr Word kSelector_aaf6aaac = 0xaaf6aaacu;
constexpr Word kSelector_ade76cce = 0xade76cceu;
constexpr Word kSelector_cdb3696f = 0xcdb3696fu;
constexpr Word kSelector_d536c91d = 0xd536c91du;
constexpr Word kSelector_d832b059 = 0xd832b059u;
constexpr Word kSelector_dca976d0 = 0xdca976d0u;
constexpr Word kSelector_e0bc9d45 = 0xe0bc9d45u;
constexpr Word kSelector_f278934a = 0xf278934au;
constexpr Word kSelector_f967827c = 0xf967827cu;

// The five tag immediates written to the receiver word at +0x32c. FOUR are
// behind a `CMP DWORD PTR [ECX+0x32c],0xffffffff` / JNZ guard and ONE
// (0x1654c00) is not. The model reproduces which is which and names neither.
// 0x1654c03 is absent from the entire body and is deliberately not declared.
constexpr Word kTag_1654c00 = 0x1654c00u;
constexpr Word kTag_1654c01 = 0x1654c01u;
constexpr Word kTag_1654c02 = 0x1654c02u;
constexpr Word kTag_1654c04 = 0x1654c04u;
constexpr Word kTag_1654c05 = 0x1654c05u;

// What the four guarded tag tests are compared against. The listing spells it
// `-0x1`, which is 0xffffffff as a word. This is a comparison against -1 and
// NOT a truth test: a receiver whose +0x32c already holds 0 is left alone by
// those four arms, because 0 is not -1.
constexpr Word kTagUnset = 0xffffffffu;

// The index the one direct callee is always given: `PUSH 0x3` at 0x00e3a2d7,
// 0x00e3a4fb and 0x00e3a55d.
constexpr Word kCopyIndex = 0x3u;

// -- the receiver ------------------------------------------------------------
// An opaque byte run with NO declared members, on purpose. The nineteen
// displacements are the whole of what this body reaches, the machine-derived
// receiver record in the evidence pack is bounds_only and enumerates a single
// one of them, and no machine record anywhere in this repository names a member
// at any displacement. Declaring a member would state an identity claim the
// evidence cannot make.
struct alignas(4) Simulator {
  std::array<std::uint8_t, 0x330> opaque_00{};
};

static_assert(sizeof(Simulator) == 0x330u,
              "0x32c is the largest displacement and every access there is a "
              "dword, so 0x330 is the last byte this body can touch");

// What the record's +0x0c points at. This body reads four consecutive dwords of
// it -- +0x08, +0x0c, +0x10, +0x14 -- and never writes any of them. The callee
// at 0x00e39420 reads three of the same four and writes them to ITS
// destination, not here. +0x00..+0x07 are never touched by either body.
struct PropertyValueBlock {
  std::array<std::uint8_t, 0x08> opaque_00{};
  Word word_08;
  Word word_0c;
  Word word_10;
  Word word_14;
};

static_assert(sizeof(PropertyValueBlock) == 0x18u,
              "0x14 is the largest displacement read and every access is a dword");

// -- the second ordinary stack argument --------------------------------------
// A pointer to a 12+4 byte record. The body reads exactly one word of it, at
// +0x0c, and that word is a POINTER, not a value: everything this body stores
// is read through it. +0x00..+0x0b are never touched by this body or by its
// callee, so they are an opaque run.
struct PropertyRecord {
  std::array<std::uint8_t, 0x0c> opaque_00{};
  const PropertyValueBlock* value;
};

static_assert(sizeof(PropertyRecord) == 0x10u,
              "0x0c is the only displacement read, and it is a dword");

// Displacement accessors, used INSTEAD of named members. That choice is what
// keeps every receiver store falsifiable: a wrong displacement in the .cpp lands
// a write on a byte the test planted a decoy in.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                 displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// A POINTER stored at `displacement`, not the address of that word. This is the
// whole of the second level of indirection the body has: `MOV EDX,[EAX+0xc]`
// loads a pointer, and every value the body stores is read through it. Returning
// the address instead -- the obvious slip -- makes the body read one object
// past the record, and the model test plants a decoy block to catch exactly
// that.
inline void* pointer_at(void* base, std::size_t displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
      *word_at(base, displacement)));
}

inline const void* pointer_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const void*>(static_cast<std::uintptr_t>(
      *word_at(base, displacement)));
}

// The 32 bits EAX holds when a `MOV EAX,<memory>` is the last thing that
// touched it. Used only where the listing leaves a POINTER in EAX, so this is
// the register's own 32 bits and asserts nothing about the pointed-to object.
inline Word address_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// -- the one direct callee ----------------------------------------------------
// Declared here and NOT defined here. This package's model test defines it as
// an observer, which is the only way the test can see the transfer, the three
// arguments in their push order, the receiver's memory state at the instant of
// the call, and the value that comes back.
//
// 0x00e39420, 47 bytes. Its shape as read for this package:
//
//   null first argument -> writes nothing at all, returns immediately
//   else q = [record + 0xc]
//        dest[+0x4] = q[index]
//        dest[+0x0] = q[index + 1]
//        dest[+0x8] = q[index + 2]
//        returns q            (its last write to EAX is `MOV EAX,[EAX+0xc]`)
//        bare RET             (cdecl -- the caller does `ADD ESP,0xc`)
//
// The three facts the .cpp relies on are the ROTATION (dest[+0] takes
// q[index+1], so the three 12-byte destinations are not plain copies), the
// cdecl terminator (which is why all three call sites are followed by ADD
// ESP,0xc), and the q return (which is why the body forwards it untouched).
extern "C" Word simulator_copy_block3_00e39420(const PropertyRecord* record,
                                               Word index, void* destination);

// -- the body under reconstruction --------------------------------------------
//
// __thiscall: the receiver arrives in ECX and is the only register the body
// writes through a memory operand; there are exactly TWO ordinary stack
// arguments, the 32-bit selector at entry_ESP+0x4 and the record pointer at
// entry_ESP+0x8 -- and the body performs no PUSH other than the three argument
// pushes before the calls, no POP, no SUB ESP and no frame setup at all, so
// those two slots are the only stack words it can name; and every one of the
// thirteen terminators is `C2 08 00`, RET 0x8, proving the callee owns the
// eight bytes of cleanup.
//
// RETURN TYPE is Word -- four bytes in EAX -- and the reason is stated rather
// than assumed. The machine ABI envelope names EAX as the return register and
// classifies its content as unclassified_in_EAX with void_possible FALSE, and
// the body genuinely writes EAX on essentially every path. What that content
// MEANS is fixed by nothing here: the .cpp reproduces the register's content
// per path because the listing fixes it exactly, and the fact that the arms
// DISAGREE (some leave a pointer, some leave a data word, some leave the
// selector untouched, the three calling arms leave the callee's result) is
// itself a machine fact and not a modelling choice. No claim is made that any
// caller consumes it; the single caller in this binary, at 0x00e3fc73, does not
// read EAX after its call.
extern "C" Word PKG_00E3A270_THISCALL hashed_property_dispatch_00e3a270(
    Simulator* receiver, Word selector, const PropertyRecord* record);

}  // namespace openspore::reconstruction::pkg_00e3a270_dispatch
