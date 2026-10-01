// PKG-SWARM-W1-00641780 -- VA 0x00641780
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00641780 @ 0x00641780. The complete body is
// 19 instructions, 0x00641780..0x006417a5 inclusive, 38 bytes:
//
//   00641780  PUSH ESI
//   00641781  MOV ESI,ECX
//   00641783  MOV EAX,[ESI]
//   00641785  MOV EDX,[EAX + 0x10]
//   00641788  CALL EDX
//   0064178a  TEST EAX,EAX
//   0064178c  JZ 0x006417a2
//   0064178e  MOV EAX,[ESI]
//   00641790  MOV EDX,[EAX + 0xc]
//   00641793  MOV ECX,ESI
//   00641795  CALL EDX
//   00641797  TEST EAX,EAX
//   00641799  JZ 0x006417a2
//   0064179b  MOV EAX,0x1
//   006417a0  POP ESI
//   006417a1  RET
//   006417a2  XOR EAX,EAX
//   006417a4  POP ESI
//   006417a5  RET
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because this is
// the thinnest kind of target there is -- 19 instructions and no direct callee at
// all. Every offset here is read out of the four lines above; nothing is imported
// from a decompilation, from a sibling package, or from an SDK header.
//
//  * The dispatch word is at receiver+0x00. 0x00641783 `MOV EAX,[ESI]` and
//    0x0064178e `MOV EAX,[ESI]`, with ESI = ECX from 0x00641781 and NO LEA, ADD
//    or displacement on ESI anywhere in the body, so the two reads are of the
//    entry receiver's own leading word and of nothing else.
//
//  * The two slot displacements are 0x10 and 0x0c, i.e. dword indices 4 and 3
//    (0x00641785 `MOV EDX,[EAX + 0x10]`, 0x00641790 `MOV EDX,[EAX + 0xc]`).
//    0x10 is read FIRST and 0x0c SECOND: control reaches 0x00641785 before
//    0x00641790 on every path that gets that far, and the 0x0064178c JZ exits
//    before the second read is ever reached.
//
//  * The receiver word is read TWICE, independently. 0x00641788 is a CALL, and
//    this body does nothing between the first read and the second except call
//    through the first result, so the second dispatch is decided by the value
//    the dispatch word holds AFTER the first callee has run. The model keeps the
//    two reads as two separate loads for exactly this reason, and the model test
//    uses a callee that overwrites the dispatch word to prove it.
//
//  * The dispatch is TWO levels deep: the receiver's word is loaded as a pointer
//    and the slot is then read out of THAT. `MOV EAX,[ESI]` followed by
//    `MOV EDX,[EAX + 0x10]` is two dereferences; a one-level reading of the same
//    bytes would be `MOV EDX,[ESI + 0x10]`, which no instruction in the body is.
//
//  * NO STRUCT MEMBER IS NAMED, anywhere in this header, and that is a
//    consequence of the machine evidence rather than a style. The machine-derived
//    receiver record for this target is `bounds_only: true` (abi_derived.value.
//    receiver) with `offsets [0]`, `max_offset 0`, `register ECX`, `shape
//    R-ALIAS`: it states how far the body was seen reaching and nothing more, so
//    a member name would be a layout claim that evidence cannot make. The
//    receiver is therefore an opaque byte run, the object the dispatch word
//    points at is reached as a plain word and indexed by displacement, and every
//    access goes through a displacement-named accessor. What the receiver IS is
//    not claimed here either; `AssetData` is the name of the boundary type and
//    nothing more.
//  * Nothing else about the receiver is known. The body reads no other
//    displacement and writes nothing on the receiver, so the 0x0c bytes after
//    the dispatch word are declared as an opaque run rather than being given
//    member names. The +0x1c sub-object that the two dispatched accessors
//    themselves read (0x00641810 and 0x00641820 both open with
//    `MOV ECX,[ECX + 0x1c]`) is a property of those CALLEES, is not read by this
//    body, and is therefore deliberately not declared here. Naming it would be a
//    member story this body's 19 instructions do not carry.
//
//  * The return value is a full 32-bit 0 or 1, not a low-byte projection:
//    0x0064179b is `MOV EAX,0x1` (bytes B8 01 00 00 00) and 0x006417a2 is
//    `XOR EAX,EAX`. The two tests are `TEST EAX,EAX` / `JZ`, i.e. the WHOLE 32
//    bits of each callee's result must be zero for this body to return zero, and
//    any non-zero pattern -- 0x80000000 and 0xffffffff included -- passes.
//  * The declared return type is `Word`, the alias declared just below, and it is
//    declared as `Word` rather than spelled `std::uint32_t` because that is what
//    the reconstruction's own signature says. The machine-derived ABI record has
//    no better word for EAX: `abi_derived.value.return` is {register EAX,
//    register_class integral, type null, void_possible false}, which classifies
//    the register's content without naming a C type, and the phrase
//    `unclassified_in_EAX` is that classification. It is NOT a type and is not
//    declared as one; see the sidecar, which records it separately. `Word` IS
//    `std::uint32_t`, so the width the declaration asserts is the width the
//    0x0064179b immediate states.
//
//  * The stack is untouched apart from the saved ESI: there is no PUSH of an
//    argument, no ADD ESP and no immediate on either RET (0x006417a1 and
//    0x006417a5 are both `C3`, one byte). So there are zero ordinary stack
//    arguments and the caller owns the stack balance. This is what fixes the
//    slot prototypes below as single-receiver __thiscall.
//
//  * The name. Ghidra has no SDK name for this VA: it is `FUN_00641780`, and it
//    is not in the ten-member SDK-derived set of Sporepedia::cSPAssetDataOTDB
//    (which stops at GetTimeCreated / 0x00641860 and never reaches 0x00641780).
//    The export name used in this package is therefore the canonical
//    VA-embedding form re_00641780 and no descriptive name is asserted as fact.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00641780 requires an x86-32 target"
#endif

// PKG_SWARM_W1_00641780_THISCALL is asserted by the body, not chosen for
// convenience. The receiver arrives in ECX and is used without any stack
// argument: 0x00641781 `MOV ESI,ECX` takes it, 0x00641793 `MOV ECX,ESI` hands it
// back for the second dispatch, and 0x006417a1 / 0x006417a5 are bare `C3`
// returns. The machine-derived ABI record agrees (abi_derived.abis calling
// convention "__thiscall", hidden_this true, hidden_this_register "ECX",
// return_register "EAX", stack_cleanup_bytes 0, saved_registers ["ESI"]).
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00641780_THISCALL __thiscall
#else
#define PKG_SWARM_W1_00641780_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00641780 {

// The one word type this body speaks in. It is the return type of the
// reconstruction, the type of every cell it reads, and the type of the pointer
// the receiver leads with -- and it is `std::uint32_t` because the machine's only
// 32-bit general register on x86-32 is spelled that way. See the honesty note
// above for what the machine record does and does not say about EAX's content.
using Word = std::uint32_t;

// One dword per cell, which is what 0x00641785 and 0x00641790 step by: both are
// `MOV <reg32>,dword ptr [EAX + disp32]`, and nothing in the body narrows either
// read to a byte or a halfword.
constexpr std::size_t kCellWidthBytes = sizeof(Word);

// -- the receiver displacement ------------------------------------------------
//
// The one displacement this body reads on the receiver, and it is the machine's
// own zero: 0x00641783 and 0x0064178e are both `MOV EAX,dword ptr [ESI]` with no
// `+ disp` in the listing, and their encodings (8B 06) carry no displacement byte
// at all. The machine-derived receiver record says the same from the other side:
// abi_derived.value.receiver is bounds_only with offsets [0] and max_offset 0.
//
// It is a named constant rather than a literal at the point of use for two
// reasons. The encoding has no displacement byte, so a `+ 0x0` written into the
// model would be a constant the machine does not contain; and the whole receiver
// access now goes through `word_at`, whose argument is a displacement, so the
// value has to be written down somewhere. It is written down here, once, and the
// static_assert below pins it.
constexpr std::size_t kDispatchWordDisplacement = 0x00u;

// -- the two table displacements ----------------------------------------------
//
// Both are read out of the listing, byte for byte, and neither is a member:
//
//   kSlotCalledFirst   0x10  0x00641785 MOV EDX,dword ptr [EAX + 0x10]
//   kSlotCalledSecond  0x0c  0x00641790 MOV EDX,dword ptr [EAX + 0xc]
//
// 0x10 is dispatched FIRST and 0x0c SECOND, and that order is fixed by control
// flow rather than by convention: control reaches 0x00641785 before 0x00641790 on
// every path that gets that far, and the JZ at 0x0064178c exits before the second
// read is reached. The names say which is CALLED first and which second, which is
// the whole of what the 19 instructions fix about them; they deliberately say
// nothing about what either one means.
//
// The two dword INDICES are carried as indices and the displacements are derived
// from them, so the arithmetic that connects a cell number to a byte offset is
// visible and the static_asserts below can tie the product to the instruction.
// (dword index 4 is 0x10; dword index 3 is 0x0c.) An index is not a claim about
// the table: it is 0x10 / 4 and 0x0c / 4, and the machine record that classifies
// these two dispatches -- abi_derived.value.dispatch, indirect_calls 2,
// call_offsets [], vtable_shaped_loads 0 -- is silent about both, so "slot" here
// names a displacement in a table and not a vtable slot of a known class.
constexpr std::size_t kSlotCalledFirstIndex = 4;
constexpr std::size_t kSlotCalledSecondIndex = 3;
constexpr std::size_t kSlotCalledFirst = kSlotCalledFirstIndex * kCellWidthBytes;
constexpr std::size_t kSlotCalledSecond = kSlotCalledSecondIndex * kCellWidthBytes;

// How much of a table is reachable on the highest displacement this body reads,
// rounded up to the containing cell. 0x10 + 4 is 0x14, so 0x14 bytes must exist
// for 0x00641785 to be a load rather than a read past the end. The wider 0x30
// below is context and not a bound this body needs.
constexpr std::size_t kTableRunBytes = kSlotCalledFirst + kCellWidthBytes;  // 0x14

// The table is modelled as 12 cells wide because 0x00641780 is installed at slot 11
// (byte +0x2c) of the table at 0x013ff648, which is the first of the six tables
// the xref export points at, and because 0x013ff648 is 0x4c bytes of table in
// this image. That is context, not a claim about what this body reads: this body
// reads the cells at +0x0c and +0x10 and nothing else, and the model test plants
// observers in the neighbouring cells (+0x08 and +0x14) to make an off-by-one
// displacement fail loudly.
constexpr std::size_t kTableCellCount = 12;
constexpr std::size_t kTableModelledBytes = kTableCellCount * kCellWidthBytes;

struct AssetData;

// A cell entry, as the model transfers to it. The callee's whole 32-bit EAX is
// the thing this body tests, so the return type is Word and not a bool:
// `TEST EAX,EAX` at 0x0064178a and 0x00641797 consumes all 32 bits, and
// 0x0064179b then produces a fresh 1 instead of forwarding any bit of the
// callee's result. Whether the callee returns a small number or an address is
// not decided here (see the sidecar).
using SlotFn = Word (PKG_SWARM_W1_00641780_THISCALL*)(AssetData* receiver);

// The receiver: an opaque byte run and nothing else. The size is the receiver's
// own requirement and not the table's: the only word this body reads out of the
// receiver is its leading one, and 4 bytes rounded out to a whole number of cells
// is the 0x10 below. (The table needs more -- kTableRunBytes, 0x14 -- but the
// table is not declared here, it is reached as a `Word` and indexed by
// displacement, so it has no size to declare.)
//
// Nothing inside is named, and the struct exists only to give the model and the
// model test one boundary type to pass around. The 0x0c bytes after the dispatch
// word are never read or written by this body, and they are what makes the
// receiver-offset and dereference-depth decoys in the model test meaningful: the
// test plants live observer addresses at +0x0c and +0x10 inside a larger raw
// block, so a model that indexed the receiver itself as though it were the table
// would call them.
struct alignas(kCellWidthBytes) AssetData {
  std::array<std::uint8_t, 0x10> opaque_00_0f{};
};

static_assert(kCellWidthBytes == 4,
              "one dword per cell, which is what 0x00641785 steps by");
static_assert(kDispatchWordDisplacement == 0x00,
              "0x00641783 / 0x0064178e state no displacement byte (8B 06), and "
              "abi_derived.receiver bounds are offsets [0], max_offset 0");
static_assert(kSlotCalledFirst == 0x10,
              "cell 4 is the 0x10 displacement of 0x00641785");
static_assert(kSlotCalledSecond == 0x0c,
              "cell 3 is the 0x0c displacement of 0x00641790");
static_assert(kTableRunBytes == 0x14,
              "0x10 + 4 is the last byte 0x00641785 reads");
static_assert(kTableModelledBytes == 0x30,
              "12 cells of 4 bytes, the width the table at 0x013ff648 implies");
static_assert(sizeof(AssetData) == 0x10,
              "the modelled receiver run is 0x10 bytes, the leading cell plus an "
              "opaque tail this body never touches");
static_assert(kDispatchWordDisplacement + kCellWidthBytes <= sizeof(AssetData),
              "the dispatch word lies inside the modelled receiver run");

// -- accessors ----------------------------------------------------------------
//
// One machine shape each, and each takes the base the way the machine holds it.
//
// `word_at` / `store_word` take a POINTER, because the only register this body
// holds an address in is the receiver itself (ESI, from ECX at 0x00641781). The
// displacement is an argument, not a member, so the access reads as the listing
// reads and a member name is not needed to say which word is meant.
//
// `word_through` / `store_word_through` take the base as a `Word`, because
// 0x00641785 and 0x00641790 hold it in EAX as a plain value that was just loaded
// out of the receiver and is then used as an address. That is what makes the
// dispatch two levels deep and keeps it that way: a one-level reading of the same
// bytes would be `word_at(self, kSlotCalledFirst)`, which is a different call
// with a different argument type, so the collapse is not writable by accident and
// the model test's D2 decoys at receiver+0x0c and receiver+0x10 are still the
// only way it could happen.

inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<const std::uint8_t*>(base) + displacement);
}

inline void store_word(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(base) + displacement) = value;
}

inline Word word_through(Word base_word, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(static_cast<std::uintptr_t>(base_word) + displacement);
}

inline void store_word_through(Word base_word, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(static_cast<std::uintptr_t>(base_word) + displacement) = value;
}

// The two-level chase in one line, written the way the body writes it: the
// receiver's own leading word is a table base, and the target is a displacement
// into THAT. Kept as a named helper so the shape is stated once and cannot quietly
// become one level. `slot_through` was this function's previous name; the name
// changed when the member it indexed went away, because nothing in this package
// declares a slot boundary any more.
inline Word cell_through(const void* receiver, std::size_t displacement) {
  return word_through(word_at(receiver, kDispatchWordDisplacement), displacement);
}

// -- model instrumentation ---------------------------------------------------
// None of these are machine globals. They exist so the model test can observe
// what the machine's four register transfers imply, which a C++ return value
// alone cannot express. Each one is a fact about a specific pair of instructions
// and is documented at its declaration.
//
// A WORD ON WHY THERE IS NO REAL-REGISTER PROBE HERE. The obvious way to test
// 0x00641780 `PUSH ESI` and 0x00641781 `MOV ESI,ECX` is to read and write the
// ESI register through inline asm, and it does not work on this toolchain: the
// prescribed build (`g++ -m32 -std=c++17 -Wall -Wextra -Werror`, no -fno-pie)
// produces a PIE, and GCC's i386 PIE sequence for this function is
// `call __x86.get_pc_thunk.si; addl $_GLOBAL_OFFSET_TABLE_,%esi`. ESI is the GOT
// base, so a read of ESI inside the body returns the module's own address rather
// than the caller's ESI, and a write of ESI inside the body destroys the GOT
// base the compiler is still about to use. The register is therefore not this
// body's to observe, and the ESI facts are carried as values instead, with the
// limitation stated in the model test rather than papered over.
//
// The value the body treats as the caller's incoming ESI at 0x00641780. The
// model test sets it before a call; the body parks it in the frame word.
Word model_esi_at_entry();
void model_set_esi_at_entry(Word value);

// The 4-byte word 0x00641780 PUSH ESI parks, and the separate word each POP ESI
// (0x006417a0 and 0x006417a4) writes back. They are distinct words on purpose:
// with a single word, a model that restored ESI on the true path but not on the
// false path would look correct, because the true path's value would still be
// sitting in it. model_reset_esi_probes() poisons both so that omission is
// visible.
Word saved_esi_frame_word();
Word restored_esi_word();
void model_reset_esi_probes();

// Live ESP immediately before each dispatch, published from inside the same asm
// block that performs the transfer (0x00641788 and 0x00641795). The machine
// pushes nothing, so a callee is entered exactly 4 bytes below the published
// value and the two published values are equal; the model test asserts both
// against assembly trampolines that sample ESP as their first instruction.
Word dispatch_esp_first_call();
Word dispatch_esp_second_call();

// -- the reconstructed body --------------------------------------------------
//
// __thiscall, receiver in ECX, ZERO ordinary stack arguments, bare `RET` on both
// paths. Return type is `Word`, the full 32-bit word 0 or 1, and it is written
// `Word` here and in the definition because that is the alias this translation
// unit declares -- not because `std::uint32_t` would be a different claim about
// the machine, since it would not. The machine's own word for what EAX carries
// is a register classification, `unclassified_in_EAX`, and it is recorded in the
// sidecar as `return_semantics` rather than declared as a type here; see the
// honesty note above.
//
// Meaning, as far as the 19 instructions support one: true iff the callee reached
// at table displacement 0x10 returns a non-zero 32-bit word AND the callee
// reached at table displacement 0x0c, dispatched from the dispatch word as it
// stands after the first call, also returns a non-zero 32-bit word. Which two real
// functions those are depends on the table the object actually carries at run
// time, and is not fixed here.
extern "C" Word PKG_SWARM_W1_00641780_THISCALL re_00641780(AssetData* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641780
