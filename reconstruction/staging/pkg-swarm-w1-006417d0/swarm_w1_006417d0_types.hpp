// PKG-SWARM-W1-006417D0 -- VA 0x006417d0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_006417d0 @ 0x006417d0. The complete body is
// 23 instructions, 0x006417d0..0x00641809 inclusive, 60 bytes:
//
//   006417d0  56                 push   esi
//   006417d1  8b f1              mov    esi,ecx
//   006417d3  8b 4e 1c           mov    ecx,DWORD PTR [esi+0x1c]
//   006417d6  85 c9              test   ecx,ecx
//   006417d8  74 2c              je     0x641806
//   006417da  e8 c1 ef f0 ff     call   0x5507a0
//   006417df  83 38 ff           cmp    DWORD PTR [eax],0xffffffff
//   006417e2  75 06              jne    0x6417ea
//   006417e4  83 78 04 ff        cmp    DWORD PTR [eax+0x4],0xffffffff
//   006417e8  74 1c              je     0x641806
//   006417ea  8b 4e 1c           mov    ecx,DWORD PTR [esi+0x1c]
//   006417ed  e8 ae ef f0 ff     call   0x5507a0
//   006417f2  8b 10              mov    edx,DWORD PTR [eax]
//   006417f4  8b 4c 24 08        mov    ecx,DWORD PTR [esp+0x8]
//   006417f8  89 11              mov    DWORD PTR [ecx],edx
//   006417fa  8b 40 04           mov    eax,DWORD PTR [eax+0x4]
//   006417fd  89 41 04           mov    DWORD PTR [ecx+0x4],eax
//   00641800  b0 01              mov    al,0x1
//   00641802  5e                 pop    esi
//   00641803  c2 04 00           ret    0x4
//   00641806  32 c0              xor    al,al
//   00641808  5e                 pop    esi
//   00641809  c2 04 00           ret    0x4
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM. Every offset
// below is read out of the lines above, re-derived from the image bytes for this
// package (objdump -d -M intel over 0x6417c0..0x641810) and checked against the
// committed Ghidra listing instruction for instruction. Nothing is imported from a
// decompilation, from a sibling package, or from an SDK header.
//
//  * The receiver's only word this body touches is at +0x1c. 0x006417d3 and
//    0x006417ea are the only two receiver reads, they are the same displacement,
//    and they are a LOAD of a word that is then handed to 0x005507a0 as its
//    receiver after a 32-bit zero test. A word read that way is a pointer, and it
//    is declared as one. Nothing else about the receiver is read and nothing is
//    written on it: the 23 instructions contain no store whose destination is
//    ESI-relative, so 0x00..0x1b and 0x20.. are an opaque run.
//
//    THE RECEIVER CARRIES NO MEMBER NAMES AT ALL, and that is the point rather
//    than an omission. The machine-derived receiver record for this target is
//    `bounds_only`: it states where the body was seen reaching (offsets [0x1c],
//    max_offset 0x1c, register ECX, shape R-ALIAS) and carries no member names,
//    so it can neither confirm nor refute WHICH member lives at a displacement --
//    only that +0x1c is a displacement the body reaches. A `field_*` name would
//    therefore be an identity claim no machine evidence here can support, so the
//    type is a single opaque byte run and every read of it goes through
//    `load_word` / `inner_word_at` at a named displacement. What the listing
//    grounds is the DISPLACEMENT; the name is not asserted at all. See
//    reconstruction/evidence/006417d0/evidence.json abi_derived.receiver.
//
//    The dispatch word at +0x00 is NOT named, even though the body IS installed
//    in six tables (see VTABLE SLOT below). This body contains no LEA, no ADD and
//    no displacement-free read of the receiver's leading word, so nothing here
//    reads a vptr and naming one would be a member story the listing does not
//    carry. The 0x1c opaque bytes are what make the receiver-offset decoys in the
//    model test meaningful: the test plants live observer addresses at +0x00,
//    +0x04, +0x18 and +0x20 inside a larger raw block.
//
//  * 0x005507a0 is seventeen bytes and its complete body was re-read for this
//    package: `PUSH EBP; MOV EBP,ESP; PUSH ECX; MOV [EBP-4],ECX;
//    MOV EAX,[EBP-0x4]; ADD EAX,0x18; MOV ESP,EBP; POP EBP; RET` (bytes
//    55 8b ec 51 89 4d fc 8b 45 fc 83 c0 18 8b e5 5d c3). It is a pure
//    __thiscall accessor returning its receiver plus 0x18: it has no stack
//    argument (the terminator is the one-byte C3 with no immediate), it preserves
//    ECX and EBP, and it forwards no part of the receiver. So the object the body
//    reads is `inner + 0x18` where `inner` is the word at receiver+0x1c, and the
//    displacement 0x18 belongs to the CALLEE, not to this body. This body adds
//    nothing to the returned pointer; the model test proves that by having the
//    observer return a scripted record that is NOT at inner+0x18 and by planting
//    poison at inner+0x18 itself.
//
//  * The two dwords the body reads are at +0x00 and +0x04 of that returned object
//    (0x006417df `CMP [EAX],-1`, 0x006417e4 `CMP [EAX+0x4],-1`, 0x006417f2
//    `MOV EDX,[EAX]`, 0x006417fa `MOV EAX,[EAX+0x4]`), and the two dwords it
//    writes are at +0x00 and +0x04 of the caller's out record (0x006417f8
//    `MOV [ECX],EDX`, 0x006417fd `MOV [ECX+0x4],EAX`). Both are 8-byte records of
//    two opaque words. No name is given to either word.
//
//  * The sentinel is the exact 32-bit pattern 0xffffffff, in BOTH words, and the
//    rejection is a conjunction: 0x006417df/0x006417e2 branches AROUND the second
//    compare when the first word is anything but 0xffffffff, so the second compare
//    is reached only on the first-word-is-sentinel path, and 0x006417e8 rejects
//    only when the second word is also 0xffffffff. A disjunction (reject when
//    either is the sentinel) and a first-word-only test are both killed by the
//    model test. The compare is 32-bit equality, so there is no signed/unsigned
//    question at this compare: 0x80000000 and 0xfffffffe are ordinary
//    non-sentinel values and the model test drives them.
//
//  * The out record is written ONLY on the path that reaches 0x006417f8. The two
//    false exits (0x006417d8 and 0x006417e8, both to 0x00641806) store nothing
//    anywhere, and the model test asserts that byte for byte by poisoning the
//    caller's buffer before every run.
//
//  * The return value is a BYTE, not a word. 0x00641800 is `MOV AL,0x1` (bytes
//    B0 01) and 0x00641806 is `XOR AL,AL` (bytes 32 C0). Neither writes the upper
//    three bytes of EAX, and on the true path EAX still holds the second dword the
//    body just copied (0x006417fa), while on the false path it holds whatever the
//    caller left there (0x006417d8) or `inner+0x18` masked (0x006417e8). Nothing
//    in this image calls the body -- all seven references are data references
//    from .rdata -- so no caller constrains the upper bytes and they are not
//    modelled. The declared return type is std::uint8_t for that reason, and the
//    model test asserts the type at compile time so a widening back to uint32_t
//    cannot pass.
//
//  * The stack argument. The only stack effect in the body is `PUSH ESI` at
//    0x006417d0 and the two matching POP ESI. 0x006417f4 reads `[ESP+0x8]` with
//    ESP at entry-4, which resolves to entry+4: the single ordinary argument, the
//    out-record pointer. Both returns are `RET 0x4` (bytes C2 04 00 at 0x00641803
//    and 0x00641809), so the CALLEE drops that word: the machine-derived ABI
//    record agrees (stack_cleanup_bytes 4, side "callee", ret_form "RET 0x4").
//    The model test measures the cleanup rather than assuming it.
//
//  * The name. Ghidra has no SDK name for this VA: it is `FUN_006417d0`, and it
//    is absent from the ten-member SDK-derived set of
//    Sporepedia::cSPAssetDataOTDB (GetAssetID 0x006417c0, GetAuthorID 0x00641820,
//    GetAuthorName 0x00641810, GetImageKey 0x006414d0, GetTags 0x00641850,
//    GetTimeCreated 0x00641860, HasName 0x00641770, IsEditable 0x00641400,
//    func3Ch 0x006417b0, func7Ch 0x00641460). The SDK-imported label
//    `GetAssetID` sits on 0x006417c0, whose live bytes are
//    `FLD DWORD PTR [0x013eb1bc]; RET` -- an x87 constant, not this contract --
//    and this body's shape (byte-sized bool in AL, one out pointer, RET 4) is
//    what the SDK signature `bool GetAssetID(uint64_t&)` describes. That is a
//    labelled OBSERVATION about a name, not a fact, and the export name used
//    here is the canonical VA-embedding form re_006417d0. See the sidecar's
// unresolved_questions.
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-006417d0 requires an x86-32 target"
#endif

// PKG_SWARM_W1_006417D0_THISCALL is asserted by the body, not chosen for
// convenience. The receiver arrives in ECX and is aliased into ESI at 0x006417d1;
// the single ordinary stack argument is the out-record pointer read at
// 0x006417f4; and both return sites are `RET 0x4`, so the callee -- this body --
// drops the argument word. The machine-derived ABI record agrees
// (abi_derived.abis: calling_convention "__thiscall", hidden_this true,
// hidden_this_register "ECX", return_register "EAX", stack_cleanup_bytes 4,
// stack_cleanup_owner "callee", saved_registers ["ESI"], ret_form "RET 0x4").
#if defined(_MSC_VER)
#define PKG_SWARM_W1_006417D0_THISCALL __thiscall
#define PKG_SWARM_W1_006417D0_CDECL __cdecl
#else
#define PKG_SWARM_W1_006417D0_THISCALL __attribute__((thiscall))
#define PKG_SWARM_W1_006417D0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_006417d0 {

using Word = std::uint32_t;

// -- the machine displacements, as values ------------------------------------
//
// Every constant below is a DISPLACEMENT or a bit pattern the listing prints, and
// every one of them is named for the instruction it is read from. None of them is a
// member name, and none is used as one: the receiver and the 8-byte records are
// opaque byte runs, and the model reaches them only at one of these values -- the
// out record through `word_at`, the receiver word through the 0x1c the span spells
// out and through `inner_word_at` below. The .cpp pins each constant with a
// `static_assert` whose message names the instruction address, so an edit to a value
// here breaks the build instead of silently changing what the model claims.
//
// kReceiverWordDisplacement is 0x1c, read twice: 0x006417d3 MOV ECX,[ESI+0x1c]
// and 0x006417ea MOV ECX,[ESI+0x1c]. They are two independent loads with a CALL
// between them, and the model keeps them as two loads rather than one value.
//
// kRecordFirstDisplacement / kRecordSecondDisplacement are 0x00 and 0x04, the two
// displacements this body uses on the object 0x005507a0 returned (0x006417df,
// 0x006417e4, 0x006417f2, 0x006417fa) AND on the caller's out record (0x006417f8,
// 0x006417fd). The two records have the same shape and the same displacements; that
// is a fact about the instructions, not a claim that they are the same type.
//
// kAccessorAddend is 0x18 and belongs to the CALLEE 0x005507a0, whose own seventeen
// bytes end in `ADD EAX,0x18`. It is carried here only so the model test can place
// a poison record at the address a wrong reconstruction would read; the model
// itself never adds it.
constexpr std::size_t kReceiverWordDisplacement = 0x1c;
constexpr std::size_t kRecordFirstDisplacement = 0x00;
constexpr std::size_t kRecordSecondDisplacement = 0x04;
constexpr std::size_t kAccessorAddend = 0x18;

// The 8-byte records. Both this body reads (through 0x005507a0) and this body writes
// (the caller's out record) are exactly two 4-byte words, and the displacements the
// listing prints for them are the same pair, so one bound is enough for both.
constexpr std::size_t kRecordSize = 0x08;

// kSentinelWord is the exact bit pattern both compares carry:
// 0x006417df is `CMP DWORD PTR [EAX],0xffffffff` (bytes 83 38 ff) and 0x006417e4
// is `CMP DWORD PTR [eax+0x4],0xffffffff` (bytes 83 78 04 ff). It is 32-bit
// equality, not a signed test and not a range test.
constexpr Word kSentinelWord = 0xffffffffu;

// VTABLE SLOT. 0x006417d0 is installed at SEVEN addresses in this image. An
// exhaustive search of .rdata and .data for the little-endian dword 0x006417d0
// returns exactly these and nothing else:
//
//   0x013ff6d8   0x013ff6ac + 0x2c  -> dword index 11
//   0x014627e8   0x014627bc + 0x2c  -> dword index 11
//   0x0147ca88   (ambiguous, see below)
//   0x0147cb50   (ambiguous, see below)
//   0x0147cc40   0x0147cc14 + 0x2c  -> dword index 11
//   0x01489120   0x014890f4 + 0x2c  -> dword index 11
//   0x01489440   0x01489414 + 0x2c  -> dword index 11
//
// The +0x2c / index-11 reading is the one that holds for five of the seven against the
// smallest candidate base. The two 0x0147c... addresses sit in a dense cluster of five
// candidate tables that overlap within 0x120 bytes of each other, and this body alone
// cannot decide which of them each address belongs to. The sidecar lists every
// candidate.
//
// This is the table the body is INSTALLED in, which is a different fact from the table
// it will be CALLED through at run time. Nothing in the 23 instructions reads either:
// there is no LEA, no ADD and no displacement-free read of the receiver's leading word.
// So no Vtable type and no slot constant appear in this model, and the numbers below
// are an observation recorded so it is not lost -- not a modelling input.
constexpr std::size_t kInstalledSlotIndex = 11;              // the consistent reading
constexpr std::size_t kInstalledSlotByteDisplacement = 0x2c; // the consistent reading
constexpr std::size_t kInstallationCount = 7;                // exact, from the search

// -- displacement accessors --------------------------------------------------
//
// Every byte this model reads or writes goes through one of these, at a named
// displacement. They take the base the way the machine holds it: a register this body
// received or a pointer a call returned, never a declared member of a declared struct.

inline Word load_word(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(static_cast<const std::uint8_t*>(base) + displacement);
}

inline void store_word(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(static_cast<std::uint8_t*>(base) + displacement) = value;
}

// The 8-byte record. Two words and NO member names: the body reads both on the probe
// object and writes both on the out record, the listing prints only the displacements
// (0x00 and 0x04) and nothing this pack carries says what a word is FOR. A name for
// either word would be an identity claim that the machine-derived receiver record --
// `bounds_only`, displacements only -- can neither confirm nor refute, so the record
// is an opaque run and `word_at` is how a displacement reaches it.
//
// The two-argument constructor is the ONLY way a caller builds one positionally, and
// it writes through `store_word` at the two named displacements, so `WordPair{a, b}`
// means the same thing here as the two member stores it replaces did.
struct alignas(4) WordPair {
  std::array<Word, 2> opaque_00_07;

  WordPair() = default;
  WordPair(Word first, Word second) {
    store_word(this, kRecordFirstDisplacement, first);
    store_word(this, kRecordSecondDisplacement, second);
  }
};
static_assert(sizeof(WordPair) == kRecordSize,
              "0x006417df/0x006417e4/0x006417fa and 0x006417f8/0x006417fd touch 8 bytes "
              "and no more");
static_assert(kRecordSecondDisplacement + sizeof(Word) <= sizeof(WordPair),
              "0x006417e4 CMP [EAX+0x4] / 0x006417fa MOV EAX,[EAX+0x4] read a word that "
              "the modelled record has to contain");

struct InnerData;

// The receiver: an opaque byte run and nothing else. The size is this body's own
// bound -- the highest receiver displacement the listing prints is 0x1c, and a word
// is read there, so the object has to be at least 0x20 bytes to exist. The 0x28 below
// is the run the model test hands the model; nothing in the 23 instructions justifies
// a larger one and nothing smaller is safe.
//
// NOT NAMED ON PURPOSE, and the reason is the machine record rather than taste: the
// receiver record for this target is `bounds_only` (offsets [0x1c], max_offset 0x1c,
// register ECX, shape R-ALIAS) and carries no member names, so it establishes that
// +0x1c is reached and nothing about WHICH member lives there. Naming one would put
// an identity claim into the source that no machine evidence in this pack can
// settle. The 0x1c opaque bytes include what a vptr would live in: the body is
// installed at slot 11 of six tables, and it still never reads one.
struct alignas(4) AssetData {
  std::array<std::uint8_t, 0x28> opaque_00_27;
};
static_assert(sizeof(AssetData) == 0x28, "modelled receiver run is 0x28 bytes");
static_assert(kReceiverWordDisplacement + sizeof(Word) <= sizeof(AssetData),
              "0x006417d3 and 0x006417ea are MOV ECX,[ESI+0x1c]: the word they read has "
              "to lie inside the modelled run");

// The object the receiver's +0x1c word points at, as far as this body is concerned.
// 0x005507a0 returns receiver+0x18 of THIS object, and the body reads 8 bytes there.
// The model declares the region at +0x18 and no more: 0x00..0x17 is opaque because
// nothing in this body reads it, and 0x20.. is not modelled at all because nothing
// in this body has any reason to have it.
//
// `pair_18` keeps a name, and it is the one name in this header that is a real
// layout assertion rather than a claim about the receiver: the seventeen bytes of
// 0x005507a0 ADD 0x18 to the pointer it was handed, so the sub-object this body reads
// really does begin at +0x18 of THIS object, and the `offsetof` below is a genuine
// check of that rather than of a name. The receiver gets no such name because nothing
// in the machine fixes one.
struct alignas(4) InnerData {
  std::array<std::uint8_t, kAccessorAddend> opaque_00_17;  // never touched here
  WordPair pair_18;                                        // what 0x005507a0 returns
};
static_assert(offsetof(InnerData, pair_18) == kAccessorAddend,
              "0x005507a0 is `MOV EAX,[EBP-0x4]; ADD EAX,0x18`");
static_assert(sizeof(InnerData) == 0x20, "0x18 + the 8 bytes this body reads");

// Read the receiver's inner-pointer word the way the machine does: a LOAD of the
// word at receiver+0x1c, returning the pointer it holds. Named as a helper so the
// displacement and the one-level shape are stated once and the model cannot quietly
// become two-level. A two-level reading would be
// `*reinterpret_cast<InnerData**>(self + 0x1c)`, which would yield the word at
// inner+0x00 rather than `inner`; the model test plants decoy words at inner+0x00 so
// that mistake cannot survive.
inline InnerData* inner_word_at(const void* receiver) {
  return *reinterpret_cast<InnerData* const*>(
      static_cast<const std::uint8_t*>(receiver) + kReceiverWordDisplacement);
}

// Read a word of a record the way the machine does, at a stated displacement. Both
// overloads are the same read; the second returns a reference so the two STORES at
// 0x006417f8/0x006417fd can be spelled the same way the two LOADS at
// 0x006417df/0x006417e4 are. Neither names a member of the record, and neither takes
// one: the record is an opaque run and the displacement is the whole claim.
inline Word word_at(const WordPair* record, std::size_t displacement) {
  return load_word(record, displacement);
}
inline Word& word_at(WordPair* record, std::size_t displacement) {
  return *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(record) + displacement);
}

// -- the one direct callee ---------------------------------------------------
// Declared here and NOT defined here: the model test defines it, as an assembly
// trampoline plus a C++ body, so the test observes every transfer this body makes.
//
// 0x005507a0, called at 0x006417da and 0x006417ed. Convention fixed by the callee's
// own seventeen bytes, not by its (absent) decompilation: `PUSH EBP; MOV EBP,ESP;
// PUSH ECX; MOV [EBP-0x4],ECX; MOV EAX,[EBP-0x4]; ADD EAX,0x18; MOV ESP,EBP;
// POP EBP; RET`. The terminator is the one-byte C3 with no immediate, so the callee
// owns no stack argument -- and this body pushes none, which the model test measures
// rather than assumes. ECX carries the inner object and comes back unchanged, which
// is why 0x006417ea reloads it from the receiver instead of trusting the register.
//
// The return type is a POINTER to the callee's own +0x18 sub-object. The body
// indexes that pointer at +0x00 and +0x04 and never dereferences it twice, so
// WordPair* is the correct depth and WordPair** would be a two-level bug.
extern "C" WordPair* PKG_SWARM_W1_006417D0_THISCALL inner_pair_accessor_005507a0(
    InnerData* inner);

// A cdecl probe, declared so the model test can show its ABI measurement is
// SENSITIVE. The model test calls this with one stack argument and measures that
// the caller's ESP comes back 4 bytes LOWER than it went in. re_006417d0 measured
// the same way comes back level, which is what makes "the callee drops its own
// argument" a measurement and not a convention. This symbol is never referenced by
// the model; it exists only in the test.
extern "C" Word PKG_SWARM_W1_006417D0_CDECL w16_cdecl_stack_probe_005507a0(
    Word value);

// -- model instrumentation ---------------------------------------------------
// Not machine globals. Each is a value a specific pair of instructions produces,
// exposed so the model test can observe what a C++ return value cannot express.
//
// A WORD ON WHY THERE IS NO REAL-REGISTER PROBE FOR ESI. The obvious way to test
// 0x006417d0 PUSH ESI / 0x00641802 POP ESI / 0x00641808 POP ESI is to read and
// write ESI through inline asm, and it does not work on this toolchain: the
// prescribed build (`g++ -m32 -std=c++17 -Wall -Wextra -Werror`, no -fno-pie)
// produces a PIE, and GCC's i386 PIE sequence for this translation unit is
// `call __x86.get_pc_thunk.si; addl $_GLOBAL_OFFSET_TABLE_,%esi`, so ESI holds the
// GOT base for the whole body. A read of ESI there returns the module's own address
// rather than the caller's ESI, and a write destroys the GOT base the compiler is
// about to use. The ESI facts are therefore carried as values, each poisoned before
// every run so that a model which restores ESI on one return path and not the other
// is visible. The limitation is stated in the model test rather than papered over.
//
// The value the body treats as the caller's incoming ESI at 0x006417d0. The test
// sets it before a call; the body parks it in the frame word.
Word model_esi_at_entry();
void model_set_esi_at_entry(Word value);

// The 4-byte word 0x006417d0 PUSH ESI parks, and the separate word each POP ESI
// writes back. They are distinct words on purpose: with a single word, a model that
// restored ESI on the true path (0x00641802) but not on the false path (0x00641808)
// would look correct, because the true path's value would still be sitting in it.
Word saved_esi_frame_word();
Word restored_esi_word();
void model_reset_esi_probes();

// -- the reconstructed body --------------------------------------------------
//
// __thiscall, receiver in ECX, ONE ordinary stack argument (the out-record pointer
// at entry+4), `RET 0x4` on both return sites so this body drops that word.
// Return type is a BYTE: 1 when the pair was copied out, 0 when it was not.
//
// Meaning, as far as the 23 instructions support one: if the object at
// receiver+0x1c is non-null and the 8 bytes that 0x005507a0 returns from it are not
// the two-word all-0xffffffff sentinel, copy those 8 bytes into the caller's record
// and return 1; otherwise leave the caller's record alone and return 0. The probe is
// taken from the FIRST call to 0x005507a0 and the copy from the SECOND, which the
// body re-resolves from receiver+0x1c rather than reusing.
extern "C" std::uint8_t PKG_SWARM_W1_006417D0_THISCALL re_006417d0(
    AssetData* receiver, WordPair* out);

}  // namespace openspore::reconstruction::pkg_swarm_w1_006417d0
