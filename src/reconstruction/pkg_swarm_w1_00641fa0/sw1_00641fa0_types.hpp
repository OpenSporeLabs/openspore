// PKG-SWARM-W1-00641FA0 -- VA 0x00641fa0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00641fa0, the unnamed boolean predicate that
// Ghidra records at VA 0x00641fa0 in the Sporepedia cluster.
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM, because this
// body is 22 instructions and every claim below is a claim about a displacement:
//
//  * 0x00, 0x04 and 0x1c on the receiver, and 0x68 on the dispatch table, are
//    read straight out of this body's own listing. The listing was re-derived
//    from the 46 image bytes at 0x00641fa0..0x00641fcd for this package and
//    matches the committed record instruction for instruction:
//
//      00641fa0  56                PUSH ESI
//      00641fa1  8b f1             MOV ESI,ECX
//      00641fa3  83 7e 1c 00       CMP dword ptr [ESI+0x1c],0x0
//      00641fa7  74 21             JZ  0x00641fca
//      00641fa9  8d 46 04          LEA EAX,[ESI+0x4]
//      00641fac  50                PUSH EAX
//      00641fad  e8 4e f9 ff ff    CALL 0x00641900
//      00641fb2  83 c4 04          ADD ESP,0x4
//      00641fb5  84 c0             TEST AL,AL
//      00641fb7  74 11             JZ  0x00641fca
//      00641fb9  8b 16             MOV EDX,dword ptr [ESI]
//      00641fbb  8b 42 68          MOV EAX,dword ptr [EDX+0x68]
//      00641fbe  8b ce             MOV ECX,ESI
//      00641fc0  ff d0             CALL EAX
//      00641fc2  84 c0             TEST AL,AL
//      00641fc4  74 04             JZ  0x00641fca
//      00641fc6  b0 01             MOV AL,0x1
//      00641fc8  5e                POP ESI
//      00641fc9  c3                RET
//      00641fca  32 c0             XOR AL,AL
//      00641fcc  5e                POP ESI
//      00641fcd  c3                RET
//
//    Those 46 bytes decode to exactly these 22 instructions and stop on
//    0x00641fcd + 1, which is what fixes the body extent independently of the
//    committed record (body_start 0x00641fa0, body_end 0x00641fcd,
//    body_span_bytes 46, size_bytes 46 -- all four agree).
//
//  * The layout of the 0x0c-byte sub-object at receiver+0x04 is NOT shown by this
//    body, which only takes its address. It is read off the ONE direct callee,
//    0x00641900, whose 88-instruction listing was re-read for this package:
//      0064192a  MOV EAX,dword ptr [ESP+0x18]   loads its own argument
//      0064192e  MOV ECX,dword ptr [EAX]         reads argument + 0x00
//      00641930  MOV EDX,dword ptr [EAX + 0x8]   reads argument + 0x08
//    so the callee observes two dwords of that sub-object and nothing else in
//    the 88 instructions. The run between them is left opaque.
//
//  * The layout of the table at +0x68 is NOT shown by this body either, which
//    reads one word out of it. The package therefore gives that table NO type and
//    NO members: it is reached as the two displacement steps the listing performs
//    (word_at(self, 0x00) at 0x00641fb9, then load_slot(that word, 0x68) at
//    0x00641fbb), and the 30-slot extent that exists only so the slot index can
//    be MEASURED lives in the model test's own byte-run fixture. Nothing says
//    what the other slots are or what their targets do.
//
//  * No member of the receiver is named, and no member of the dispatch table is
//    named either -- the receiver is an opaque byte run and every access to it is
//    a displacement through `word_at` or `address_at`. The one sub-object below
//    that does spell members spells them field_<hex offset>, which states where
//    they live and nothing about what they are for, and its layout is read off
//    0x00641900's own listing rather than this body's. The class name
//    SporepediaAssetDataOtdb is INFERRED, not machine-fixed: this target's own
//    record carries name "FUN_00641fa0" and class_type null, and the name comes
//    from vtable co-membership -- the data-side xrefs place this body at +0x0c of
//    the table at 0x013ff6ac and 0x013ff648, the same two tables the record lists
//    as the match basis for the reconstructed neighbours 0x00641400, 0x00641460,
//    0x00641770, 0x006417b0, 0x006417c0, 0x00641810, 0x00641820 and 0x00641850,
//    every one of which the repository research queue names
//    Sporepedia::cSPAssetDataOTDB::*. A type name is not a member claim and no
//    offset anywhere in this package is grounded on it.
//
//  * The dword at receiver+0x1c is tested against zero by CMP/JZ and is NEVER
//    dereferenced by this body. It is modelled as a plain word, not as a
//    pointer, and the model test drives a nonzero-pointer-to-a-zero-word case
//    precisely to keep that distinction falsifiable.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00641fa0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC rejects the bare
// MSVC keywords outright on this target, so the x86-32 attribute form is the
// portable spelling and the keyword form is kept for MSVC. Both are asserted by
// machine facts, not chosen for convenience:
//
//   PKG_SW1_00641FA0_THISCALL  this body. 0x00641fa1 `MOV ESI,ECX` takes the
//     receiver out of ECX, every receiver access in the body is through ESI, and
//     0x00641fbe `MOV ECX,ESI` puts the SAME object back in ECX for the indirect
//     call at 0x00641fc0 -- a static function with a pointer argument would have
//     to pass that pointer some other way, and there is no other way. The
//     terminator is a bare `RET` (0x00641fc9 and 0x00641fcd, bytes c3) with no
//     immediate, and the body takes no ordinary stack argument, so the cleanup
//     side is 0 bytes either way.
//   PKG_SW1_00641FA0_CDECL  0x00641900, the one direct callee. This body drops
//     the pushed word itself with `ADD ESP,0x4` at 0x00641fb2, and 0x00641900's
//     own epilogue is `POP ESI; ADD ESP,0x10; RET` (0x006419bb, 0x006419bc,
//     0x006419be) with no immediate -- it consumes no argument word, so the
//     caller owns the cleanup and the convention is cdecl.
#if defined(_MSC_VER)
#define PKG_SW1_00641FA0_THISCALL __thiscall
#define PKG_SW1_00641FA0_CDECL __cdecl
#else
#define PKG_SW1_00641FA0_THISCALL __attribute__((thiscall))
#define PKG_SW1_00641FA0_CDECL __attribute__((cdecl))
#endif

// The displacement accessors below are spelled `always_inline` rather than merely
// `inline` for a reason that is a machine fact, not a style preference. This
// package's model test reads the ESP each callee was entered with, out of a naked
// probe, to assert that the argument word the body pushes for 0x00641900 has
// already been dropped by 0x00641fb2 `ADD ESP,0x4` before the dispatch at
// 0x00641fc0 runs. At -O0 -- which is how the package's own compile gate builds it
// -- a merely `inline` accessor is emitted as an out-of-line call, so a model
// whose every field access goes through `word_at` would put an accessor frame of
// its own between the argument push and the dispatch, and the measured stack depth
// would then be the accessor's, not the body's. Forcing the inline keeps the frame
// the probes sample the frame the SOURCE states.
#if defined(_MSC_VER)
#define PKG_SW1_00641FA0_ACCESSOR __forceinline
#else
#define PKG_SW1_00641FA0_ACCESSOR inline __attribute__((always_inline))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00641fa0 {

using Word = std::uint32_t;

// The 0x0c-byte sub-object at receiver+0x04. This body never dereferences it --
// it only forms its address (0x00641fa9 `LEA EAX,[ESI+0x4]`) and hands it to
// 0x00641900. The two words below are the ones that callee reads, and the run
// between them is untouched by both bodies.
struct alignas(4) AssetDataSubObject04 {
  Word field_00;               // 0x0064192e reads it
  std::array<std::uint8_t, 4> field_04_07;  // read by nothing in this set
  Word field_08;               // 0x00641930 reads it
};
static_assert(offsetof(AssetDataSubObject04, field_08) == 0x08,
              "0x00641930 reads the second word at its own +0x08");
static_assert(sizeof(AssetDataSubObject04) == 0x0c,
              "the second read ends at +0x0b");

// -- the receiver --------------------------------------------------------------
//
// An opaque byte run and nothing else. The size is this body's own bound: the
// dword compared at 0x00641fa3 ends at +0x1f, so 0x20 bytes is what the body
// needs in order to exist.
//
// NO member of it is named, and there is no table type either. The machine-derived
// receiver record enumerates offsets [0, 28] with register ECX and carries
// bounds_only, i.e. it states where the body was seen reaching and not which
// member is which -- so every access below is a DISPLACEMENT through
// `word_at` / `address_at`, and 0x08..0x1b, 0x20 and beyond are never read or
// written here. Calling any of them a handle, a counter, a cache or a flag would
// be a member story this body's evidence does not carry.
struct alignas(4) SporepediaAssetDataOtdb {
  std::array<std::uint8_t, 0x20> opaque_00_1f;  // 0x00..0x1f
};

// -- every displacement this body states, and the instruction it comes from -----
//
// None of these is a member name; they are the numbers the listing prints. The
// middle column is the single instruction in this body's 22 that fixes the number.
// The `static_assert`s further down then pin each one: the three receiver
// displacements against the opaque run they must lie inside, and the slot
// displacement against the index arithmetic that 0x68 / 4 == 26 spells out.
//
//   name                          byte  instruction that states it
//   kReceiverTableDisplacement     0x00  0x00641fb9  MOV EDX,dword ptr [ESI]
//   kReceiverSubObjectDisplacement 0x04  0x00641fa9  LEA  EAX,[ESI + 0x4]
//   kReceiverGateWordDisplacement  0x1c  0x00641fa3  CMP  dword ptr [ESI + 0x1c],0x0
//   kDispatchSlotDisplacement      0x68  0x00641fbb  MOV  EAX,dword ptr [EDX + 0x68]
constexpr std::size_t kReceiverTableDisplacement = 0x00u;
constexpr std::size_t kReceiverSubObjectDisplacement = 0x04u;
constexpr std::size_t kReceiverGateWordDisplacement = 0x1cu;
constexpr std::size_t kDispatchSlotDisplacement = 0x68u;

// The slot displacement as an INDEX, i.e. divided by the four-byte slot width.
// This is an arithmetic identity, not a second piece of evidence: 0x68 / 4 == 26.
// It is named so a reader counting slots in a table need not redo the division.
constexpr std::size_t kDispatchSlotIndex = kDispatchSlotDisplacement / sizeof(Word);  // 26

// 0x68 on the table is the slot displacement at 0x00641fbb. In the three tables
// this body is xref'd into that also carry a slot at 0x68, that index holds a
// DIFFERENT function from the index this body itself sits at (25 in 0x01462764, 28
// in 0x01489090, 3 in 0x013ff6ac), which is the concrete proof that the two are
// not the same index.

// -- accessors -----------------------------------------------------------------
//
// One machine shape each, all taking the base the way the machine holds it.
//
// `word_at` / `address_at` take a POINTER because the listings that use them hold
// a register the body received: the receiver (ESI, from ECX at 0x00641fa1).
// `word_at` is a LOAD (`CMP`/`MOV dword ptr`) and `address_at` is a LEA -- the
// body's 0x00641fa9 forms an address without reading the word that lives there,
// and the two are kept apart so that distinction cannot be written away.
//
// `load_slot` takes its base as a `Word` because 0x00641fb9 holds the table
// pointer in EDX as a plain value and 0x00641fbb then uses it as an address. That
// is what keeps the body's two-level chase from being collapsed into a
// one-level dereference by accident: the receiver's own leading word has to be
// read first, and only the word it yields is a base for the slot read.
PKG_SW1_00641FA0_ACCESSOR Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<const std::uint8_t*>(base) +
                                        displacement);
}

PKG_SW1_00641FA0_ACCESSOR void* address_at(void* base, std::size_t displacement) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uint8_t*>(base) + displacement);
}

PKG_SW1_00641FA0_ACCESSOR Word load_slot(Word base_word, std::size_t slot_displacement) {
  return *reinterpret_cast<const Word*>(static_cast<std::uintptr_t>(base_word) +
                                        slot_displacement);
}

// -- the indirect callee -------------------------------------------------------
//
// The slot the body dispatches through: a receiver-only member function whose
// return value is examined with TEST AL,AL, so a byte return is what the machine
// fixes. Its declaring class is NOT fixed by this body -- the concrete targets
// seen in the two tables this body is xref'd into are 0x00b1fbf0 (table
// 0x01462764, read at 0x014627cc) and 0x006418b0 (table 0x01489090, read at
// 0x014890f8) -- so the slot's own signature is taken from the CALL SITE, which
// is what the machine does fix: ECX = the receiver (0x00641fbe MOV ECX,ESI), no
// stack word, AL tested at 0x00641fc2.
//
// 0x68 is the whole of what this body establishes about the table it dispatches
// through. The table gets NO type and NO declared members: the model reads one
// word out of it by displacement, and the 30-slot width lives in the model test,
// which plants a distinct observer in every slot and so measures which index the
// reconstruction calls.
using DispatchSlot68 =
    std::uint8_t(PKG_SW1_00641FA0_THISCALL*)(SporepediaAssetDataOtdb*);

PKG_SW1_00641FA0_ACCESSOR std::uint8_t invoke_dispatch_slot(
    Word slot_target, SporepediaAssetDataOtdb* receiver) {
  return reinterpret_cast<DispatchSlot68>(static_cast<std::uintptr_t>(slot_target))(receiver);
}

static_assert(sizeof(void*) == 4, "this package is 32-bit pointer model");
static_assert(sizeof(DispatchSlot68) == 4, "a slot is one address");
static_assert(sizeof(Word) == 4, "words are 32-bit");
static_assert(sizeof(SporepediaAssetDataOtdb) == 0x20,
              "0x1c + 4 is the last byte the body touches on the receiver");
// The displacements reach inside the run the body is known to touch, and each is
// the one the instruction named above states.
static_assert(kReceiverTableDisplacement + sizeof(Word) <= sizeof(SporepediaAssetDataOtdb),
              "the table-pointer word at 0x00641fb9 lies inside the receiver run");
static_assert(kReceiverGateWordDisplacement + sizeof(Word) <= sizeof(SporepediaAssetDataOtdb),
              "the dword compared at 0x00641fa3 ends at the last byte of the run");
static_assert(kReceiverSubObjectDisplacement <= sizeof(SporepediaAssetDataOtdb),
              "the address formed at 0x00641fa9 lies inside the receiver run");
static_assert(kDispatchSlotIndex * sizeof(Word) == kDispatchSlotDisplacement,
              "index 26 is displacement 0x68, the value 0x00641fbb prints");

// -- the one direct callee --------------------------------------------------
// Declared here, not defined here: the model test defines it as an observer.
//
// 0x00641900, called once at 0x00641fad with the address of the receiver's own
// +0x04 sub-object. cdecl, one stack word, cleaned by this body at 0x00641fb2.
// Its return value is examined as a BYTE (`TEST AL,AL` at 0x00641fb5), not
// compared with 1, so the declared return type is uint8_t and the model test
// drives it with 0x80 to keep an `== 1` reconstruction falsifiable.
extern "C" std::uint8_t PKG_SW1_00641FA0_CDECL asset_data_sub_predicate_00641900(
    AssetDataSubObject04* sub_object);

// FUN_00641fa0 @ 0x00641fa0.
//
// __thiscall, receiver in ECX, NO ordinary stack argument, bare `RET` on both
// exits, and exactly one byte of meaning in the result: 0 or 1. Both exits set
// AL explicitly -- `MOV AL,0x1` at 0x00641fc6 and `XOR AL,AL` at 0x00641fca --
// so the observable return is normalised even when the dispatch target returns
// some other nonzero byte. The upper three bytes of EAX are the dispatch
// target's leftovers and are not modelled.
extern "C" std::uint8_t PKG_SW1_00641FA0_THISCALL sporepedia_predicate_00641fa0(
    SporepediaAssetDataOtdb* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641fa0
