// PKG-SWARM-W2-005A2ED0 -- VA 0x005a2ed0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_005a2ed0 @ 0x005a2ed0.
//
// HONESTY NOTE ON WHERE EVERY OFFSET AND EVERY CONSTANT IN THIS HEADER COMES FROM.
// The split matters, because this body stores three .rdata words into a receiver
// and then reads a word out of a second object through a pointer it loaded from
// a third; almost every plausible misreading of it is a pointer-level error, and
// a header that blurs the levels would hide exactly the thing that is at stake.
//
//  * The six immediates are read straight out of the image bytes. The listing
//    was re-derived for this package with
//    `objdump -D -b binary -m i386 -M intel --adjust-vma=0x005a2ed0` over the 79
//    bytes at this VA's file offset (0x005a2ed0 - 0x401000 + 0x400 = 0x1a22d0),
//    and it reproduces the committed 22 instructions at the same addresses with
//    the same lengths and the same displacements. Nothing here depends on the
//    difference, because the committed parse record is not degraded:
//
//      005a2ed0  56                    push   esi
//      005a2ed1  8b f1                 mov    esi,ecx
//      005a2ed3  c7 06 c8 69 3f 01     mov    DWORD PTR [esi],0x13f69c8
//      005a2ed9  c7 46 04 b8 69 3f 01  mov    DWORD PTR [esi+0x4],0x13f69b8
//      005a2ee0  c7 46 08 b4 69 3f 01  mov    DWORD PTR [esi+0x8],0x13f69b4
//      005a2ee7  8b 4e 10              mov    ecx,DWORD PTR [esi+0x10]
//      005a2eea  85 c9                 test   ecx,ecx
//      005a2eec  74 07                 je     0x5a2ef5
//      005a2eee  8b 01                 mov    eax,DWORD PTR [ecx]
//      005a2ef0  8b 50 04              mov    edx,DWORD PTR [eax+0x4]
//      005a2ef3  ff d2                 call   edx
//      005a2ef5  f6 44 24 08 01        test   BYTE PTR [esp+0x8],0x1
//      005a2efa  c7 46 08 94 f0 3e 01  mov    DWORD PTR [esi+0x8],0x13ef094
//      005a2f01  c7 46 04 94 b3 3e 01  mov    DWORD PTR [esi+0x4],0x13eb394
//      005a2f08  c7 06 38 b9 3e 01     mov    DWORD PTR [esi],0x13eb938
//      005a2f0e  74 09                 je     0x5a2f19
//      005a2f10  56                    push   esi
//      005a2f11  e8 6a 44 9a 00        call   0xf47380
//      005a2f16  83 c4 04              add    esp,0x4
//      005a2f19  8b c6                 mov    eax,esi
//      005a2f1b  5e                    pop    esi
//      005a2f1c  c2 04 00              ret    0x4
//
//  * The two sets of three are DISTINCT triples of .rdata addresses and the body
//    stores them in a fixed order, first the +0x00/+0x04/+0x08 triple in
//    ascending displacement, then the +0x08/+0x04/+0x00 triple in DESCENDING
//    displacement. Both orders are machine facts and both are asserted by the
//    model test; the descending second triple is the single easiest thing in
//    this body to get backwards and it is invisible in the final state, because
//    after the last store each of the three words holds its own triple's value
//    whichever order the stores were made in.
//
//  * What the addresses ARE is not claimed. The record associates this body
//    with one vtable, vtable:0x013f69b4, and 0x013f69b4 is one of the six
//    immediates (the third store of the first triple). That corroborates the
//    word at +0x08 being a dispatch word of some kind; it does not identify a
//    class, and SporeApp.exe carries no MSVC RTTI (AGENTS.md), so nothing here
//    says what the other five addresses are. They are named for the displacement
//    they land in and for which triple they belong to, and nothing more.
//
//  * NO MEMBER IS NAMED. The machine-derived receiver record for this VA
//    enumerates offsets [0, 4, 8, 16] through ECX with shape R-ALIAS and
//    bounds_only true, and the body reaches all four through the ESI alias
//    instead (see the alias note in the .cpp). bounds_only says where the body
//    was SEEN reaching and not which member is which, so this type declares no
//    member at all: calling +0x00 a "vtable pointer", +0x04 a "second vtable
//    pointer" and +0x10 an "observer" or a "child" is a story this body's
//    twenty-two instructions do not tell. What the bytes fix is the WIDTH and
//    the DISPLACEMENT of each access, and that is all the model uses.
//
//  * The +0x10 word is a POINTER, and everything the body does through it is
//    two dereferences deep. `8b 4e 10` loads the word; `8b 01` reads the first
//    word OF THE OBJECT THAT WORD NAMES (the object's dispatch word); `8b 50
//    04` reads the dword at that table's displacement 0x04. So the callee is
//    reached at displacement 0x04 of a table reached through a pointer stored at
//    receiver+0x10, and the callee's own receiver is the POINTEE -- ECX still
//    holds the loaded word at 0x005a2ef3 because nothing between 0x005a2ee7 and
//    the CALL rewrites it. Passing receiver+0x10 itself, or the receiver, is a
//    different machine, and the model test plants decoys that make each of those
//    two wrong readings call a different function.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-005a2ed0 requires an x86-32 target"
#endif

// The calling conventions below are spelled per toolchain. GCC 16 rejects the
// bare MSVC keywords outright, so the x86-32 attribute form is the portable
// spelling and the keyword form is kept for MSVC.
//
//   SWARM_W2_005A2ED0_THISCALL  the body under reconstruction and the indirect
//     callee it reaches through the table word at receiver+0x10.
//
//     Both are fixed by machine facts rather than chosen:
//
//     * the body under reconstruction: ECX is dereferenced before any write to
//       it (0x005a2ee7 loads a word at a displacement of the receiver through
//       the ESI copy of it), the receiver arrives in ECX, and the terminator is
//       `c2 04 00` (RET 0x4) which pops four bytes of stack argument -- a
//       callee-cleaned one-stack-word convention, which is __thiscall and not
//       cdecl. The machine-derived record agrees
//       (abi_derived.conventions.calling_convention "__thiscall", confidence
//       INFERRED, stack_cleanup_bytes 4, stack_cleanup_owner "callee", evidence
//       "ret 0x4").
//     * the indirect callee: ECX still holds the word loaded from receiver+0x10
//       at the moment of the CALL at 0x005a2ef3, the body pushes nothing and
//       performs no stack adjustment afterwards, so the callee is entered with
//       that word in ECX and with the stack exactly as the body found it. The
//       callee's own body is not in this package and its arguments beyond the
//       receiver are NOT claimed: the listing shows only that the body
//       establishes no stack word for it.
#if defined(_MSC_VER)
#define SWARM_W2_005A2ED0_THISCALL __thiscall
#define SWARM_W2_005A2ED0_CDECL __cdecl
#else
#define SWARM_W2_005A2ED0_THISCALL __attribute__((thiscall))
#define SWARM_W2_005A2ED0_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_005a2ed0 {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// The six .rdata immediates, as values, named for where they land and which of
// the two triples they belong to. No name here says what the addresses are.
// ---------------------------------------------------------------------------

// The first triple: stored at receiver+0x00, +0x04 and +0x08, in that order,
// BEFORE the guarded call through the word at receiver+0x10.
constexpr Word kFirstTripleHeadAt00 = 0x013f69c8;  // 005a2ed3
constexpr Word kFirstTripleHeadAt04 = 0x013f69b8;  // 005a2ed9
constexpr Word kFirstTripleHeadAt08 = 0x013f69b4;  // 005a2ee0

// The second triple: stored at receiver+0x08, +0x04 and +0x00, in that DESCENDING
// order, AFTER the flag test at 0x005a2ef5 and BEFORE the branch at 0x005a2f0e.
constexpr Word kSecondTripleHeadAt08 = 0x013ef094;  // 005a2efa
constexpr Word kSecondTripleHeadAt04 = 0x013eb394;  // 005a2f01
constexpr Word kSecondTripleHeadAt00 = 0x013eb938;  // 005a2f08

// The three receiver displacements the body writes, as values. The order they
// are listed in is the order the body uses them in, which is NOT ascending.
constexpr std::size_t kReceiverWrite00 = 0x00;  // 005a2ed3, then 005a2f08
constexpr std::size_t kReceiverWrite04 = 0x04;  // 005a2ed9, then 005a2f01
constexpr std::size_t kReceiverWrite08 = 0x08;  // 005a2ee0, then 005a2efa

// The one receiver displacement the body only READS. `8b 4e 10` is a 32-bit
// load, so the word occupies +0x10..+0x13 and the receiver is at least 0x14
// bytes; nothing in this body reads or writes past that.
constexpr std::size_t kReceiverRead10 = 0x10;  // 005a2ee7

// The displacement of the table slot the indirect CALL reads: `8b 50 04` is
// `mov edx,[eax+0x4]`, i.e. the dword at offset 0x04 of the table EAX names.
// 0x04 is the second dword of that table, so the callee is at slot index 1 --
// and index 1 is the ONLY slot this body can name.
constexpr std::size_t kDispatchSlotDisplacement = 0x04;

// The displacement of the object word the indirect call reads BEFORE it reads
// the table: `8b 01` is `mov eax,[ecx]` with no displacement, so the table
// pointer is the object's own +0x00.
constexpr std::size_t kPointeeDispatchWord = 0x00;

// The flag mask and the slot the flag is read from. `f6 44 24 08 01` is
// `test byte ptr [esp+0x8],0x1`.
//
// The 0x8 is NOT an ordinary displacement: exactly one word is on the stack at
// that instruction, the return address, because the body's only PUSH is the
// prologue's `push esi` at 0x005a2ed0 and its matching POP is at 0x005a2f1b.
// So entry_ESP - 4 == [esp] holds the saved ESI, entry_ESP - 0 holds the return
// address and [esp + 0x8] == entry_ESP + 0x4 is the first ordinary stack
// argument -- the one the terminator `ret 0x4` pops. That is the same slot the
// machine-derived record names ("entry_ESP+0x4", key 4, size 1, obs-0011), and
// the two agree independently.
constexpr std::size_t kDeletingFlagStackDisplacement = 0x08;
constexpr Word kDeletingFlagMask = 0x01;

// The receiver. Opaque on purpose: see the header note. 0x14 bytes, because the
// highest displacement the body touches is the +0x10 word and that word is four
// bytes wide.
struct alignas(4) SwarmW2005a2ed0Receiver {
  std::array<std::uint8_t, 0x14> opaque;
};
static_assert(sizeof(SwarmW2005a2ed0Receiver) == 0x14,
              "0x10 + 4 is the last byte the body touches on the receiver");
static_assert(kReceiverRead10 + sizeof(Word) == sizeof(SwarmW2005a2ed0Receiver),
              "the word read at +0x10 ends the modelled receiver");

// The object the +0x10 word points at. The body reads exactly ONE word of it --
// the dword at its own +0x00, which is then used as a table pointer -- so its
// extent is NOT observable from this body and none is declared. Naming it a
// "subobject", a "child" or an "observer" would be a story; what is fixed is
// that the body dereferences the loaded word exactly once before treating what
// it reads as a table.
//
// Its dispatch word is stored at its own displacement 0x00, which is a machine
// fact (`8b 01` carries no displacement). It is declared as a member here
// because this type is NOT the receiver: the FIELDS/OFFSETS dimension is about
// the receiver record, and this offset is witnessed by the listing at a
// displacement of the pointee, not at one of the receiver's four.
struct alignas(4) DispatchedObject {
  void** dispatch_word;  // the object's own +0x00, read once at 005a2eee
};
static_assert(offsetof(DispatchedObject, dispatch_word) == kPointeeDispatchWord,
              "the dispatch word is the pointee's own +0x00");

// Slot 0x04 of that table: the pointee in ECX, no stack word established by
// this body. `void` because this body never reads what comes back -- the
// instruction after the CALL is the flag test at 0x005a2ef5, and EAX is
// overwritten by `mov eax,esi` at 0x005a2f19 before the RET on both paths.
using DispatchSlot = void(SWARM_W2_005A2ED0_THISCALL*)(DispatchedObject*);

// The only way the body touches the receiver: a word at a stated displacement.
// A member access would assert an identity the machine-derived record cannot
// corroborate, so displacement-named accessors are what the model uses.
inline std::uint32_t* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint32_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                         displacement);
}

inline const std::uint32_t* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// Reading the +0x10 word AS A POINTER, which is what the body does with it and
// not what a "member" reading would do. Separate from word_at on purpose: the
// two-level mistake this body turns on is calling the dword at +0x10 a value
// rather than a pointer, or passing +0x10 itself where the pointee belongs.
inline void* pointer_at(void* base, std::size_t displacement) {
  return *reinterpret_cast<void**>(word_at(base, displacement));
}

// Reading slot `displacement` of a table. The displacement is the machine's,
// not an index: `8b 50 04` reads offset 0x04, which is dword index 1.
inline DispatchSlot slot_at(void* const* table, std::size_t displacement) {
  return reinterpret_cast<DispatchSlot>(table[displacement / sizeof(void*)]);
}

// -- the one direct callee --------------------------------------------------
// 0x00f47380, called at 0x005a2f11 with the receiver pushed immediately before
// at 0x005a2f10. cdecl, and that is fixed by the callee's OWN bytes, not by
// this body's habit: the callee's whole body is seven instructions ending in a
// BARE `c3` with no immediate --
//
//   00f47380  8b 44 24 04        mov eax,DWORD PTR [esp+0x4]
//   00f47384  85 c0              test eax,eax
//   00f47386  74 0c              je   0x00f47394
//   00f47388  a1 44 8b 16 01     mov eax,DWORD PTR [0x016c8b44]
//   00f4738e  50                 push eax
//   00f4738f  e8 2c 03 00 00     call 0x009276c0
//   00f47394  c3                 ret
//
// -- so it pops nothing but the return address, and this body drops the pushed
// word itself with `add esp,0x4` at 0x005a2f16. Its own first instruction reads
// the pushed word at [esp+0x4] with no push outstanding, which fixes the
// argument order (one word, the receiver) and the width (32-bit).
//
// `void` because the body discards EAX: the instruction after the call is
// `add esp,0x4` and then `mov eax,esi` overwrites the return register before the
// RET. A reconstruction that returned the callee's value would be a different
// body.
extern "C" void SWARM_W2_005A2ED0_CDECL deallocate_00f47380(void* pointer);

// -- model instrumentation ---------------------------------------------------
// The six 32-bit stores the body makes to the receiver, in the order it makes
// them. All six encodings are visible in the listing (`c7 06` and `c7 46 04`
// and `c7 46 08`, twice each) and they are six separate instructions writing
// six separate values, so a reconstruction that writes five, or writes them in
// a different order, is a different machine.
//
// Four of the six are invisible to any observer outside the body: the window
// between consecutive stores contains no call, no branch target and no exit, so
// nothing outside can sample a transient value. Rather than pretend otherwise,
// the model records the ordered sequence in a file-scope log so the test can
// assert the count, the displacements, the values and their order.
//
// This is INSTRUMENTATION, not a machine global. Nothing in the twenty-two
// instructions names a global address: the only absolute operands are the six
// .rdata immediates and the direct call target, and the xref export carries
// data_reference_count 0 for this VA. It is declared in this header only so the
// test can reach it.
struct ReceiverStoreLog {
  std::uint32_t count;             // 6 on every path: the body stores on all of them
  std::uint32_t displacement[8];   // the displacement of each store, in order
  std::uint32_t value[8];          // the value each store wrote, in order
};
ReceiverStoreLog receiver_store_log();

// The single ordinary stack argument's ADDRESS, exported so the test can drive
// the deleting flag through the body itself and can observe WHEN the body reads
// it. The body reads that byte exactly once, at 0x005a2ef5, and the test's
// dispatch observer overwrites it from inside the call; whether the body then
// acts on the modified byte is a machine fact about the order of the read and
// the call, and it is asserted.
//
// This is instrumentation for the same reason the store log is: the body reads
// the flag out of the caller's frame slot, so the model materialises that slot
// as a real argument and publishes its address. Nothing in the body writes it.
std::uint8_t* deleting_flag_address();

// The receiver's argument ADDRESS, published for the same reason. The body
// passes this pointer to 0x00f47380 and passes the POINTEE to the dispatch
// slot, and the test measures which of the two each callee actually receives.
void* receiver_address();

// The pointer the body loaded from receiver+0x10 on its last load, i.e. the
// value the dispatch slot is reached through. Published so the test can assert
// that the dispatch used the POINTEE and neither the address of the word nor
// the receiver, and so it can plant a different pointee between two calls.
void* last_dispatched_pointee();

// How many times the guarded call through the +0x10 word was taken. The body
// makes it at most once per call and exactly once when the word is non-null.
std::uint32_t dispatch_call_count();

// -- the body ----------------------------------------------------------------
// FUN_005a2ed0 @ 0x005a2ed0.
//
// __thiscall, receiver in ECX, exactly ONE ordinary stack argument (a byte at
// entry_ESP+0x4, read at 0x005a2ef5 and popped by `ret 0x4`), terminator
// `C2 04 00`. Neither the argument count nor the convention is a guess: the body
// contains no other [esp+...] operand, the flag byte is the only stack slot it
// reads, and the callee-cleaned four bytes are the ones its own terminator
// names.
//
// RETURN TYPE. The body returns the receiver pointer: `mov eax,esi` at
// 0x005a2f19 is the last write to EAX before the sole RET at 0x005a2f1c, it is
// unconditional, and ESI has not been rewritten since 0x005a2ed1, so EAX holds
// the receiver on BOTH paths -- including the path on which 0x00f47380 has just
// run and may have done anything at all to memory. That is what the declared
// type says.
//
// This is NOT the machine record's token, and the disagreement is recorded
// rather than papered over. abi_derived.return is
// {register EAX, register_class "aggregate_unknown", type null, void_possible
// false} and the envelope's return_semantics is the machine phrase
// "unclassified_in_EAX" -- a phrase no C++ type can equal, so the validator's
// string comparison against it cannot succeed whatever is written here. The
// declared type is the one the LISTING fixes, not one chosen to win that
// comparison; see the sidecar's return_semantics note.
extern "C" SwarmW2005a2ed0Receiver* SWARM_W2_005A2ED0_THISCALL re_005a2ed0(
    SwarmW2005a2ed0Receiver* receiver, std::uint8_t deleting_flag);

}  // namespace openspore::reconstruction::pkg_swarm_w2_005a2ed0
