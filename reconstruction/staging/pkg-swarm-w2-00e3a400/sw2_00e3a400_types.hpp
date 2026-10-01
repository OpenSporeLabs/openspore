// PKG-SWARM-W2-00E3A400 -- VA 0x00e3a400
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, offsets and call-boundary declarations for the hashed-property
// dispatcher whose Ghidra body is FUN_00e3a270. The worker's target address
// 0x00e3a400 is INSIDE that body, not its entry: it is the second byte of the
// ten-byte instruction at 0x00e3a40a (`8B 40 0C  MOV EAX,[EAX+0xc]`), which is
// the fourth of the four stores of the 0x00e3a3e2 arm. The queue names the
// record "Simulator" and counts 172 instructions, and 172 is the length of the
// WHOLE body 0x00e3a270..0x00e3a56a, so the target is that body and this
// package reconstructs all 172 instructions of it.
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM. Every number
// below is read out of the 172-instruction listing, which was re-derived from
// the image bytes for this package and reproduces the committed Ghidra listing
// instruction for instruction, at the same addresses and with the same lengths:
//
//   dd if=SPORE/SporeBin/SporeApp.exe bs=1 skip=$((0xa39670)) count=$((0xe3a56b-0xe3a270)) of=/tmp/body.bin
//   objdump -D -b binary -m i386 -M intel --adjust-vma=0x00e3a270 /tmp/body.bin
//
// (0xa39670 is the file offset of RVA 0xa3a270: .text has section RVA 0x1000 at
// file offset 0x400, so offset = 0x400 + (0xa3a270 - 0x1000).) The committed
// Ghidra record's own extent, body_start 0x00e3a270 / body_end 0x00e3a56a /
// size_bytes 763 / 172 instructions, is therefore NOT truncated and nothing in
// this model rests on a re-parse disagreeing with it. The six bytes after
// 0x00e3a56a are INT3 padding, not part of the body.
//
// 1. THE SELECTOR (the 27 hashed key ids). Twenty-seven `CMP EAX,<imm32>`
//    immediates, and no other 32-bit immediate in the dispatch at all. They are
//    the preimage hashes of property names; this repository holds no table that
//    inverts any of them, so none is named beyond its own value. Which arm each
//    one reaches is stated per id in the .cpp, and the mapping is not a guess:
//    every id is reached through a chain of JG/JZ/JNE whose targets and operands
//    are all inside the body.
//
// 2. THE SIGNEDNESS OF THE DISPATCH. Every ordering branch in the body is JG --
//    opcodes 0x0F 8F at e3a279, e3a28a, e3a297, e3a33c, e3a38a(no), e3a3a8,
//    e3a3b9, e3a4c3 -- and 0x7F at e3a4c3's short form and e3a33c's short form.
//    JG is a SIGNED greater-than. Fifteen of the twenty-seven selector values
//    have the high bit set and are therefore negative when read signed
//    (0x8133fb2e, 0x980e43f2, 0x99f0d1da, 0x9f792b4c, 0xa0973374, 0xa6cb4c9f,
//    0xaaf6aaac, 0xade76cce, 0xcdb3696f, 0xd536c91d, 0xd832b059, 0xdca976d0,
//    0xe0bc9d45, 0xf278934a, 0xf967827c) and twelve are positive. A C++ `>` on
//    a std::uint32_t is UNSIGNED, and the two readings agree only where both
//    operands carry the same sign bit -- so `signed_greater` below exists to
//    keep the signedness explicit and testable rather than accidental.
//
//    This is the single most fragile fact in the body, and the consequence is
//    easy to state exactly. The root pivot 0xf278934a is itself negative. The
//    fifteen negative selectors therefore compare against it identically under
//    both readings and are routed correctly even by a wrong reconstruction.
//    The twelve POSITIVE selectors do not: signed they are above the root pivot
//    and belong to the high half, and unsigned they are below it and belong to
//    the low half -- whose seven leaf tests (0xaaf6aaac, 0x9f792b4c, 0x8133fb2e,
//    0x980e43f2, 0x99f0d1da, 0xa0973374, 0xa6cb4c9f) are ALL negative values. So
//    an unsigned reading makes twelve of the ten arms unreachable and turns
//    twelve selectors into no-ops that write nothing and call nothing.
//
// 3. THE RECEIVER DISPLACEMENTS. Nineteen distinct displacements, all inside
//    the body, and nothing is read or written through any other base at any
//    other offset. Sixteen of the nineteen appear as memory operands under ECX
//    and account for 23 store instructions between them; the remaining three
//    (0x29c, 0x2b4, 0x2c0) are produced by `ADD ECX,<disp>` and pushed, so the
//    listing shows no memory operand under them:
//
//      +0x29c  +0x2a8  +0x2ac  +0x2b0        four words, 0x29c is a call
//      +0x2b4  +0x2c0  +0x2cc  +0x2d0  +0x2d4   destination, the other three are
//                                                 single words
//      +0x308  +0x30c  +0x310  +0x314  +0x318  single words
//      +0x31c  +0x320  +0x324  +0x328  +0x32c
//
//    The +0x29c, +0x2b4 and +0x2c0 destinations are never stored to by this body
//    at all: they are produced by `ADD ECX,<disp>` and then PUSHed, so the three
//    addresses reach the callee as computed values while the listing shows no
//    memory operand under them. Sixteen of the nineteen are read as well as
//    written; the three computed ones are write-only, and only by the callee. The largest displacement this body can touch is
//    +0x32c, and every access there is a dword, so 0x32c + 4 == 0x330 is the
//    last byte it can reach and the modeled object is exactly that size.
//
//    The machine-derived receiver record (abi_derived.value.receiver) names
//    ECX with shape R-DIRECT, max_offset 804, written_through 1 and
//    bounds_only TRUE, and enumerates the single displacement 0x324. That record
//    is a lower bound produced from two observations (obs-0008 at e3a2ca and
//    obs-0009 at e3a2d0) and it is contradicted, not extended, by the complete
//    listing, which shows sixteen under that register. Because bounds_only is true it CANNOT refute
//    a declared member, and because no machine record in this repository names a
//    member at any displacement, this header therefore declares NO members on
//    the receiver at all: it is an opaque byte run reached through the
//    displacement accessors below. See the wave-1 lesson recorded in
//    observed_original_abi.receiver_model in the metadata sidecar.
//
// 4. THE SECOND ORDINARY STACK ARGUMENT. A POINTER, read at [ESP+0x8] in ten
//    places, from which exactly one word is ever read: +0x0c. That word is then
//    used as a BASE, not as a value: the body computes q = record[+0x0c] and
//    then reads q[+0x8], q[+0xc], q[+0x10] and q[+0x14]. Two levels of
//    indirection, never one, and never a member of the record itself. The
//    callee at 0x00e39420 reads the same +0x0c as a base and then indexes it, so
//    the same shape is corroborated from outside this body.
//
// 5. THE ONE DIRECT CALLEE. 0x00e39420, called from three sites (e3a2da,
//    e3a4fe, e3a560), always as (record, 0x3, self + {0x2c0, 0x2b4, 0x29c}) in
//    that push order, always cdecl (bare `C3` at 0x00e3944e; this body does
//    `ADD ESP,0xc` after every one of the three calls), and its EAX return is
//    never overwritten afterwards -- `ADD ESP,0xc` and `RET 0x8` are all that
//    follow each call -- so this body FORWARDS it. See the .cpp.
//
// 6. NOT CLAIMED, ANYWHERE, BY THIS HEADER:
//
//    * a class name. The triage subsystem says "Simulator" and the queue names
//      the record "Simulator", but SporeApp.exe carries no MSVC RTTI, no
//      persisted symbol names this address, and no record in this repository
//      associates a type with it. The type below is called Simulator for
//      readability and for nothing else.
//    * what any of the seventeen receiver words MEANS. Four of them
//      (0x29c, 0x2b4, 0x2c0) are 12-byte destinations handed to a helper that
//      copies three dwords into them; three groups of three or four
//      (0x2a8/0x2ac/0x2b0, 0x2cc/0x2d0/0x2d4, 0x314/0x318, 0x31c/0x320,
//      0x324/0x328) look like a primary/secondary pair per quantity, and 0x32c
//      takes six consecutive values 0x1654c00..0x1654c05. NONE of that is named,
//      because nothing in the evidence names it.
//    * what the 0x1654c00..0x1654c05 immediates ARE. They are six consecutive
//      32-bit values written to the same receiver word, five of them behind a
//      `CMP [ECX+0x32c],-1 / JNZ` guard and one (0x1654c00) written
//      unconditionally. The reconstruction reproduces the guard and the values;
//      it does not name what they denote.
//    * the preimages of the 27 selector hashes, and therefore what any of the
//      twenty-seven arms is "for".
//    * the size of the real object. 0x330 is the smallest size consistent with
//      this body's own accesses and is a lower bound, not a measurement. The
//      only caller in the binary, at 0x00e3fc73, passes its own EBP as the
//      receiver, so the real object is at least as large as whatever EBP points
//      at; nothing here bounds it above.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00e3a400 requires an x86-32 target"
#endif

// One convention is needed for the body itself and it is fixed by machine bytes,
// not chosen for convenience:
//
//   SW2_00E3A400_THISCALL  this body. ECX is the receiver -- it is dereferenced
//                          at nineteen displacements and is never written
//                          anywhere else in the 172 instructions -- and the
//                          terminator is `C2 08 00`, RET 0x8, at thirteen
//                          separate sites (e3a2e2, e3a31b, e3a334, e3a361, e3a387,
//                          e3a3a0, e3a416, e3a44f, e3a49e, e3a4bb, e3a506,
//                          e3a543, e3a568), so the callee pops its own eight
//                          bytes of stack arguments. That rules out cdecl, which
//                          would need an ADD ESP in the body and a bare RET,
//                          and it rules out fastcall, which would put the first
//                          ordinary argument in EDX.
#if defined(_MSC_VER)
#define SW2_00E3A400_THISCALL __thiscall
#else
#define SW2_00E3A400_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00e3a400 {

using Word = std::uint32_t;

// -- the signed comparison the dispatch actually performs --------------------
// The body's ordering branches are all JG (0x0F 8F, and 0x7F in its short
// form), which is a SIGNED above. Fifteen of the twenty-seven selector values
// have the high bit set and are negative when read signed, so a C++ `>` on a
// std::uint32_t -- which is UNSIGNED -- silently re-routes the dispatch. The
// cast is the honest spelling of what the opcode says; the two's-complement
// reinterpretation of a value above 0x7fffffff is what gcc does and what the
// JG does.
inline bool signed_greater(Word left, Word right) {
  return static_cast<std::int32_t>(left) > static_cast<std::int32_t>(right);
}

// -- the twenty-seven selector immediates ------------------------------------
// One per `CMP EAX,<imm32>` in the dispatch, named for their own value only.
// The pivot is 0xf278934a because the FIRST compare of the body is against it
// (e3a274) and it is the root of the tree; every other constant below is a leaf
// test, not a pivot. Values are as the listing spells them.
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

// The six immediates written to the receiver word at +0x32c. Five are behind a
// `CMP DWORD PTR [ECX+0x32c],0xffffffff` / JNZ guard and one is not; the model
// reproduces which is which and names neither.
constexpr Word kTag_1654c00 = 0x1654c00u;
constexpr Word kTag_1654c01 = 0x1654c01u;
constexpr Word kTag_1654c02 = 0x1654c02u;
constexpr Word kTag_1654c04 = 0x1654c04u;
constexpr Word kTag_1654c05 = 0x1654c05u;

// The value the guarded tag tests are compared against: the listing spells it
// `-0x1`, which is 0xffffffff as a word.
constexpr Word kTagUnset = 0xffffffffu;

// The index the one direct callee is always given, `PUSH 0x3` at e3a2d7,
// e3a4fb and e3a55d.
constexpr Word kCopyIndex = 0x3u;

// -- the receiver ------------------------------------------------------------
// An opaque byte run with NO members, on purpose. The seventeen displacements
// are the whole of what this body reaches, the machine-derived receiver record
// is bounds_only and enumerates one of them, and no machine record anywhere in
// this repository names a member. Declaring a member would state an identity
// claim the evidence cannot make; the displacement accessors below keep every
// store falsifiable, because a wrong displacement lands on a decoy the test
// planted rather than on a plausible-looking field.
struct alignas(4) Simulator {
  std::array<std::uint8_t, 0x330> opaque_00{};
};

static_assert(sizeof(Simulator) == 0x330u,
              "0x32c is the largest displacement and every access there is a "
              "dword, so 0x330 is the last byte this body can touch");

// What the record's +0x0c points at. This body reads four consecutive dwords of
// it -- +0x08, +0x0c, +0x10, +0x14 -- and never writes any of them; the callee
// at 0x00e39420 reads the same three of the same four (q[index+0], q[index+1],
// q[index+2] with index 3, i.e. q[+0xc], q[+0x10], q[+0x14]) and writes them to
// its destination, not here. +0x00..+0x07 are never touched by either body.
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

// Displacement accessors. These are used INSTEAD of named members, which is what
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

// A POINTER stored at `displacement`, not the address of that word. The
// distinction is the whole of the second level of indirection this body has:
// `MOV EDX,[EAX+0xc]` loads a pointer, and every value the body stores is read
// through it. Returning the address instead -- the obvious slip, and the one
// this package's own model test caught in its first run -- makes the body read
// one object past the record.
inline void* pointer_at(void* base, std::size_t displacement) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(
      *word_at(base, displacement)));
}

inline const void* pointer_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const void*>(static_cast<std::uintptr_t>(
      *word_at(base, displacement)));
}

// The value EAX holds when a `MOV EAX,<memory>` is the last thing that touched
// it, as a Word. Used only where the listing leaves a POINTER in EAX, so the
// conversion is the register's own 32 bits and asserts nothing about the object.
inline Word address_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// -- the one direct callee ----------------------------------------------------
// Declared here and NOT defined here: this package's own model test defines it
// as an observer, which is the only way the test can see the transfer, its three
// arguments in their push order, and the receiver's memory state at the instant
// of the call.
//
// 0x00e39420, 47 bytes, read from the image:
//
//   e39420  mov eax,[esp+0x4]        its first stack word
//   e39424  test eax,eax
//   e39426  je   e3944e              a null record writes nothing at all
//   e39428  mov edx,[eax+0xc]       the SAME +0x0c this body reads
//   e3942b  mov ecx,[esp+0x8]        its second stack word: the index
//   e3942f  push esi
//   e39430  mov esi,[edx+ecx*4]      q[index]
//   e39433  mov edx,[esp+0x10]       its third stack word: the destination
//   e39437  mov [edx+0x4],esi        dest[+0x4] = q[index]
//   e3943a  mov esi,[eax+0xc]
//   e3943d  mov esi,[esi+ecx*4+0x4]  q[index+1]
//   e39441  mov [edx],esi            dest[+0x00] = q[index+1]
//   e39443  mov eax,[eax+0xc]        <-- the last write to EAX on either path
//   e39446  mov ecx,[eax+ecx*4+0x8]  q[index+2]
//   e3944a  mov [edx+0x8],ecx        dest[+0x08] = q[index+2]
//   e3944d  pop esi
//   e3944e  ret                      C3 -- BARE RET, so it is cdecl
//
// Three facts follow from those bytes and are used by the .cpp: the terminator
// is a bare RET so the CALLER cleans up (which is why all three call sites are
// followed by ADD ESP,0xc and why the declaration below is plain cdecl); the
// three words are written to the destination in the order +0x4, +0x0, +0x8 and
// not in source order, which is why the receiver's three 12-byte destinations
// cannot be described as a plain copy; and the last thing written to EAX is
// `MOV EAX,[EAX+0xc]`, i.e. the record's +0x0c word, so the callee RETURNS the
// value-block pointer -- which is why the body forwards it.
//
// Its return type is Word because those bytes fix a four-byte result in EAX.
// This body never inspects the value beyond forwarding it (the only caller in
// the binary, at 0x00e3fc73, does not read EAX after its call either), so the
// test's observer deliberately returns a poison value and the model test proves
// the forward rather than assuming it.
extern "C" Word simulator_copy_block3_00e39420(const PropertyRecord* record,
                                               Word index, void* destination);

// The body under reconstruction.
//
// __thiscall: the receiver arrives in ECX and is the only register the body
// writes through a memory operand; there are exactly TWO ordinary stack
// arguments, the 32-bit selector at entry_ESP+0x4 and the record pointer at
// entry_ESP+0x8 (the body performs no PUSH, no POP, no SUB ESP and no frame
// setup at all, and the machine parse reports local_extent 0 with
// esp_unresolved false, so those two slots are the only stack words it can
// touch); and every one of the thirteen terminators is `C2 08 00`, RET 0x8,
// which proves the callee owns the eight bytes of cleanup.
//
// Return type is Word -- four bytes in EAX -- and the reason is stated rather
// than assumed. The machine ABI envelope names EAX as the return register
// (return_register EAX, and inference RT1 "the return value is carried in EAX"),
// classifies its content as aggregate_unknown / unclassified_in_EAX, and states
// void_possible FALSE. The body genuinely writes EAX on essentially every path.
// What that content MEANS is not fixed by anything: the .cpp reproduces the
// register's content per path because the listing fixes it exactly, and the
// inconsistency between arms (some leave a pointer, some leave a data word, some
// leave the selector itself, the three call arms leave the callee's result) is
// itself a machine fact and not a modelling choice. No claim is made that any
// caller consumes it, and the only caller in the binary does not.
extern "C" Word SW2_00E3A400_THISCALL re_00e3a400(
    Simulator* receiver, Word selector, const PropertyRecord* record);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00e3a400
