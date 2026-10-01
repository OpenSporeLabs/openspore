// PKG-SWARM-W1-00EC3BE0 -- VA 0x00ec3be0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, offsets and call-boundary declarations for the Sporepedia-online
// property handler at 0x00ec3be0 (Ghidra: FUN_00ec3be0).
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM. The whole
// target is 58 instructions / 177 bytes, so the split between "this body's own
// listing" and "some other body's listing" is short enough to state in full:
//
// 1. IN THIS BODY'S OWN 58-INSTRUCTION LISTING (complete body span
//    0x00ec3be0..0x00ec3c90 inclusive, 177 bytes; objdump over the raw image
//    bytes reproduces the committed listing instruction for instruction, at the
//    same addresses, with the same lengths -- see the .cpp for the full list):
//
//      0x00ec3be0  56                    PUSH ESI
//      0x00ec3be1  8B 74 24 08           MOV ESI,[ESP+0x8]
//      0x00ec3be5  57                    PUSH EDI
//      0x00ec3be6  56                    PUSH ESI
//      0x00ec3be7  8B F9                 MOV EDI,ECX
//      0x00ec3be9  E8 42 E9 77 FF        CALL 0x00642530
//      0x00ec3bee  8B 06                 MOV EAX,[ESI]
//      0x00ec3bf0  3D A7 84 35 5A        CMP EAX,0x5a3584a7
//      0x00ec3bf5  77 3D                 JA 0x00ec3c34
//      0x00ec3bf7  74 23                 JZ 0x00ec3c1c
//      0x00ec3bf9  3D C8 AF E8 15        CMP EAX,0x15e8afc8
//      0x00ec3bfe  0F 85 88 00 00 00     JNZ 0x00ec3c8c
//      0x00ec3c04  81 7E 04 5D A7 E1 02  CMP [ESI+0x4],0x2e1a75d
//      0x00ec3c0b  75 7F                 JNZ 0x00ec3c8c
//      0x00ec3c0d  83 7E 08 01           CMP [ESI+0x8],0x1
//      0x00ec3c11  0F 94 C0              SETZ AL
//      0x00ec3c14  88 47 78              MOV [EDI+0x78],AL
//      0x00ec3c17  5F 5E C2 04 00        POP EDI; POP ESI; RET 0x4
//      0x00ec3c1c  81 7E 04 5D A7 E1 02  CMP [ESI+0x4],0x2e1a75d        (+0x79)
//      0x00ec3c34  3D 14 BA 1F B9        CMP EAX,0xb91fba14
//      0x00ec3c39  74 3E                 JZ 0x00ec3c79                     (+0x7a)
//      0x00ec3c3b  3D 35 5E 2F D2        CMP EAX,0xd22f5e35
//      0x00ec3c40  74 1F                 JZ 0x00ec3c61                     (+0x7b)
//      0x00ec3c42  3D DD 75 46 DB        CMP EAX,0xdb4675dd
//      0x00ec3c47  75 43                 JNZ 0x00ec3c8c                    (+0x7c)
//      0x00ec3c61  81 7E 04 5D A7 E1 02  CMP [ESI+0x4],0x2e1a75d
//      0x00ec3c79  81 7E 04 5D A7 E1 02  CMP [ESI+0x4],0x2e1a75d
//      0x00ec3c8c  5F 5E C2 04 00        POP EDI; POP ESI; RET 0x4
//
//    From those instructions this header takes, and nothing else:
//
//      * the five receiver byte displacements 0x78, 0x79, 0x7a, 0x7b, 0x7c
//        (the machine-derived receiver record agrees exactly: offsets [120,
//        121, 122, 123, 124], max_offset 124, register ECX, shape R-ALIAS,
//        written_through 5, bounds_only true -- i.e. five WRITES and no read)
//      * the five key-id immediates     0x15e8afc8, 0x5a3584a7, 0xb91fba14,
//                                        0xd22f5e35, 0xdb4675dd
//      * the ONE type-hash immediate    0x2e1a75d, compared against [ESI+0x4]
//      * the ONE value immediate        0x1, compared against [ESI+0x8]
//      * the three key-record displacements 0x00, 0x04, 0x08
//      * the terminator                 RET 0x4, i.e. callee-owned 4-byte
//                                       cleanup of exactly one stack word
//      * the two saved registers        ESI, EDI
//      * the dispatch order             an UNSIGNED `JA` split at 0x5a3584a7,
//                                        then a 2-way test in the low group and
//                                        a 3-way test in the high group
//      * the ONE direct call target     0x00642530
//
// 2. FROM THE IMAGE AT THE TABLE ADDRESS (84 bytes read at 0x014890f4 and
//    walked as 21 little-endian words). This is what licenses the word "table"
//    and fixes the slot:
//
//      0x014890f4 +0x00 = 0x00641400   (+0x04 0x006418b0, +0x08 0x00ec3b60,
//      +0x0c 0x00641fa0, +0x10 0x005c0dd0, +0x14 0x00641460, +0x18 0x00641470,
//      +0x1c 0x00641490, +0x20 0x00ec3b40, +0x24 0x00a649a0, +0x28 0x00642700,
//      +0x2c 0x006417d0, +0x30 0x00641890, +0x34 0x00b7e380, +0x38 0x00641fd0,
//      +0x3c 0x00641380, +0x40 0x00641cd0, +0x44 0x00ec3bc0, +0x48 0x00641e40,
//      +0x4c 0x00642230)
//      0x014890f4 +0x50 = 0x00ec3be0   <-- this body, and the LAST word of the
//                                          run: the next word at 0x01489148 is
//                                          0x726f7053, which is the ASCII
//                                          "Spore" and not code.
//
//    So the xref from 0x01489144 -- the only reference to this VA in the whole
//    binary -- is this body's own entry point sitting at slot +0x50 of a 21-word
//    table. The analogue records agree independently: they name this same table
//    (match_basis "shared_vtable:vtable:0x014890f4") for 0x00641400 (which the
//    image confirms is its +0x00) and for 0x00641460 (its +0x14).
//
//    A third, independent corroboration that these are class tables and not
//    incidental runs of code pointers: reconstruction/metadata/
//    pkg-swarm-w1-006413d0/006413d0.json lists 0x00641cd0, 0x00642230,
//    0x00641890, 0x00641fd0, 0x00641e40, 0x00b7e380 and 0x00ec3bc0 among the
//    per-class target addresses of the tables it read -- and seven of those are
//    words of this table.
//
//    NONE of this is modelled. The body contains no indirect transfer
//    (abi_derived.dispatch: indirect_calls 0, call_offsets [], vtable_shaped_loads
//    0) and it never reads the receiver's +0x00, so no slot boundary is declared
//    anywhere in this package and no member is named at +0x00. See
//    unresolved_questions.
//
// 3. FROM THE ONE DIRECT CALLEE'S OWN BYTES, 0x00642530 (160 bytes read at the
//    image offset for that VA):
//
//      0x00642530  8B 54 24 04           MOV EDX,[ESP+0x4]   its one stack word
//      0x00642534  8B 02                 MOV EAX,[EDX]       -> record +0x00
//      0x00642571  81 7A 04 5D A7 E1 02  CMP [EDX+0x4],0x2e1a75d
//      0x0064257E  8B 42 08              MOV EAX,[EDX+0x8]   -> record +0x08
//      0x00642581  89 41 28              MOV [ECX+0x28],EAX
//      0x00642584  C2 04 00              RET 0x4
//
//    i.e. it takes the SAME pointer-to-record on the stack, reads the SAME three
//    displacements of it, checks the SAME type hash 0x2e1a75d against its +0x04
//    and hands its +0x08 to the receiver -- and its terminator is `C2 04 00`,
//    RET 0x4, so it is __thiscall with the receiver in ECX and callee-owned
//    cleanup. Three facts are therefore corroborated across the two bodies rather
//    than assumed: the record is 12 bytes of "key id, type hash, value", the
//    type hash 0x2e1a75d is a real constant of this property vocabulary rather
//    than a coincidence, and this body's own call at 0x00ec3be9 is a property
//    handler being given the same record.
//
//    It is NOT claimed that 0x00642530 handles the same five keys. Its own
//    dispatch tests 0x429d47e / 0x429d47c / 0x02f05c5f / 0x02dc9d1e /
//    0x02f05c57 / 0x02f05c59 / 0x03fea1a0 and, for the 0x2e1a75d type, more
//    receiver words (it reads +0x2c and writes +0x28, +0x30, +0x34, +0x38), and
//    none of those is one of this body's five. The two bodies are siblings in
//    the same vocabulary, and this one delegates the keys the other owns.
//
// 4. NOT CLAIMED, ANYWHERE, BY THIS HEADER:
//
//      * a class name. The triage cluster says "sporepedia-online" and the
//        subsystem says "Sporepedia", but no MSVC RTTI survives in this binary
//        and no record names the class. The type below is called
//        SporepediaOnlineAsset for readability and nothing more.
//      * the size of the object. This body never reads a receiver byte and
//        never writes past +0x7c, so 0x7d bytes are the most it can be seen to
//        touch and the model rounds that to 0x80. 0x00642530 reads the same
//        receiver as far as +0x38, so the real object is certainly at least as
//        large as 0x80; that is a fact about the CALLEE, and the model test
//        gives its observer room rather than inflating the type.
//      * what the five flag bytes MEAN. They are five consecutive bytes written
//        by five different key ids, and the key ids are 32-bit hashed strings
//        whose preimages this package does not have. No record in this
//        repository maps any of the five to a name, so none is named here.
//      * what the value word at the record's +0x08 means. The body only asks
//        whether it is exactly 1, and the test drives values where "== 1" and
//        "!= 0" disagree.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00ec3be0 requires an x86-32 target"
#endif

// One convention is needed and it is fixed by machine bytes, not chosen for
// convenience:
//
//   SW1_00EC3BE0_THISCALL  this body (terminator C2 04 00 = RET 0x4, receiver
//                          copied out of ECX at 0x00ec3be7 and dereferenced
//                          through EDI) and its one direct callee 0x00642530
//                          (terminator C2 04 00 at 0x00642584, receiver in ECX).
//                          Both pop their own stack arguments, which rules out
//                          cdecl and fastcall.
#if defined(_MSC_VER)
#define SW1_00EC3BE0_THISCALL __thiscall
#else
#define SW1_00EC3BE0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0 {

using Word = std::uint32_t;

// -- the receiver's five written byte displacements ---------------------------
// Read straight out of the five `MOV BYTE PTR [EDI+disp],r8` instructions, one
// per key arm. The machine-derived receiver record enumerates exactly these five
// and reports written_through 5, so every one of them is a WRITE and this body
// reads no receiver byte at all -- which is why they are spelled as displacements
// below and never as members.
constexpr std::size_t kFlagDisplacementForId_15e8afc8 = 0x78u;
constexpr std::size_t kFlagDisplacementForId_5a3584a7 = 0x79u;
constexpr std::size_t kFlagDisplacementForId_b91fba14 = 0x7au;
constexpr std::size_t kFlagDisplacementForId_d22f5e35 = 0x7bu;
constexpr std::size_t kFlagDisplacementForId_db4675dd = 0x7cu;

// The three key-id immediates the low group tests (both below 0x5a3584a7
// unsigned) and the three the high group tests (all with the sign bit set, so
// only an UNSIGNED compare reaches them -- see the .cpp).
constexpr Word kKeyId_15e8afc8 = 0x15e8afc8u;
constexpr Word kKeyId_5a3584a7 = 0x5a3584a7u;
constexpr Word kKeyId_b91fba14 = 0xb91fba14u;
constexpr Word kKeyId_d22f5e35 = 0xd22f5e35u;
constexpr Word kKeyId_db4675dd = 0xdb4675ddu;

// The pivot the first `JA` splits on, and the ONE type hash every arm checks
// against the record's second word.
constexpr Word kPivotId_5a3584a7 = 0x5a3584a7u;
constexpr Word kTypeHash = 0x2e1a75du;

// The record's three displacements, in the order the body reads them.
constexpr std::size_t kRecordIdDisplacement = 0x00u;   // 0x00ec3bee MOV EAX,[ESI]
constexpr std::size_t kRecordTypeDisplacement = 0x04u; // 0x00ec3c04 CMP [ESI+0x4]
constexpr std::size_t kRecordValueDisplacement = 0x08u; // 0x00ec3c0d CMP [ESI+0x8]

// The receiver. Declared as an opaque run with NO members, on purpose.
//
// The five displacements above are the whole of what this body reaches, and the
// receiver record is bounds_only: it says where the body was seen reaching, not
// which member is which. The displacement accessors below are used instead of
// named members precisely so that a wrong displacement in the .cpp lands a store
// somewhere the model test planted a decoy instead of looking like a plausible
// field write.
//
// 0x7c is the largest displacement written and each store is one byte, so 0x7c +
// 1 == 0x7d is the last byte this body can possibly touch; the run is rounded to
// 0x80. The test fills 0x00..0x87 with sentinels and asserts that the only byte
// that ever changes is the one the matched arm names.
struct alignas(4) SporepediaOnlineAsset {
  std::array<std::uint8_t, 0x80> opaque_00{};
};

static_assert(sizeof(SporepediaOnlineAsset) == 0x80u,
              "0x7c + one byte is the last byte this body can write");

// The record the body was handed. A pointer to it is the single ordinary stack
// argument, and the body reads three words of it and writes none. The members
// are named here (outside the reconstructed function's own span) so the model
// test can build records readably; the .cpp deliberately reaches them by
// displacement instead, because a `->field` access in the body would declare a
// field NAME that the machine-derived receiver record cannot corroborate -- the
// key record is not the receiver, and its 0x00/0x04/0x08 are not receiver
// displacements at all.
struct PropertyKeyRecord {
  Word field_00;  // the key id: MOV EAX,[ESI] at 0x00ec3bee
  Word field_04;  // a type hash: CMP [ESI+0x4],0x2e1a75d at 0x00ec3c04
  Word field_08;  // the value word: CMP [ESI+0x8],0x1 at 0x00ec3c0d
};
static_assert(sizeof(PropertyKeyRecord) == 0x0cu,
              "the body reads three words and writes none of them");

// Displacement accessors. Using these instead of named members is what keeps the
// five flag writes falsifiable.
inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                          displacement);
}

inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                 displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// -- the one direct callee ----------------------------------------------------
// Declared here and NOT defined here: this package's own model test defines it
// as an observer, which is how the test sees the transfer, its argument, its
// argument order, and the memory state at the moment of the call.
//
// The name is chosen from 0x00642530's own 160 bytes, quoted above: it is given
// a pointer to a 12-byte key record and, when the record's id is 0x02dc9d1e and
// its type hash is 0x2e1a75d, it stores the record's +0x08 into the receiver's
// +0x28. No record in this repository names this address -- it appears in
// reconstruction/metadata/pkg-swarm-w1-006413d0/006413d0.json only as a per-class
// TABLE ENTRY, at table 0x01462764 slot +0xa8 and again at table 0x0147cbbc slot
// +0xa8 -- so the name below is this package's and is derived from the callee's
// own instruction bytes, not from a persisted symbol.
//
// It is __thiscall: ECX is the receiver (it writes [ECX+0x28] at 0x00642581) and
// its terminator is `C2 04 00` at 0x00642584, so it pops its own single stack
// word. Its return value goes in EAX and THIS BODY NEVER READS IT: the
// instruction after the call is 0x00ec3bee `MOV EAX,[ESI]`, which overwrites it
// without reading. The declaration therefore gives it a return type this body
// ignores, and the test's observer deliberately returns a poison value.
extern "C" Word SW1_00EC3BE0_THISCALL sporepedia_property_apply_00642530(
    SporepediaOnlineAsset* receiver, const PropertyKeyRecord* key);

// The body under reconstruction.
//
// __thiscall: receiver in ECX, copied into EDI at 0x00ec3be7 and addressed
// through EDI on every access; exactly ONE ordinary stack argument, the pointer
// to the key record, occupying the 4-byte slot at entry_ESP+0x4; `RET 0x4`
// (0xC2 04 00 at 0x00ec3c19 and at each of the other four terminators), which
// proves the callee owns the cleanup. That combination rules out cdecl (which
// would need an ADD ESP in the body and a bare RET) and rules out fastcall
// (which would put the first ordinary argument in EDX).
//
// The argument count is not a guess and does not need the flow model the ABI
// inference abstained on: the prologue is three instructions (PUSH ESI; MOV
// ESI,[ESP+0x8]; PUSH EDI) and the machine parse reports local_extent 0 and
// esp_unresolved false, so the ONLY stack word this body ever touches is
// [ESP+0x8] after one push, i.e. entry_ESP+0x4.
//
// Return type is void. Ghidra's own decompilation of this VA is `void
// __thiscall FUN_00ec3be0(int param_1,uint *param_2)` with five bare `return;`
// statements and no value produced on any of them, and the machine agrees: no
// path writes EAX immediately before a terminator for the purpose of returning
// it. What the machine does leave in EAX is incidental and path-dependent --
// 0x00ec3be9's return value where an arm does not match, the compared key id
// where an arm stores through AL, and the same key id unchanged where an arm
// stores through CL or DL. Because the body's return value is void, the model
// declares none and the test asserts nothing about EAX.
extern "C" void SW1_00EC3BE0_THISCALL re_00ec3be0(
    SporepediaOnlineAsset* receiver, const PropertyKeyRecord* key);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00ec3be0
