// PKG-SWARM-W1-00641410 -- VA 0x00641410
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Boundary and opaque types for FUN_00641410 @ 0x00641410. The complete body is
// 31 instructions, 0x00641410..0x00641459 inclusive, 74 bytes
// (ghidra_function.body_start 0x00641410, body_end 0x00641459, size_bytes 74;
// 0x0064145a..0x0064145f are INT3 padding and are NOT part of the body).
//
// The listing this was written against was re-derived from the image bytes for
// this package (objdump -d -M intel over 0x6413f0..0x641470 of
// SPORE/SporeBin/SporeApp.exe) and agrees with the committed Ghidra listing
// instruction for instruction, including the three 2-byte `MOV EDX,[EAX+0x24]`
// re-loads and the one 3-byte one at 0x00641415:
//
//   00641410  56           push   esi
//   00641411  8b f1        mov    esi,ecx
//   00641413  8b 06        mov    eax,DWORD PTR [esi]        ; read #1 of the dispatch word
//   00641415  8b 50 24     mov    edx,DWORD PTR [eax+0x24]   ; slot 9, loaded
//   00641418  ff d2        call   edx
//   0064141a  3d 89 3e d7 bc cmp    eax,0xbcd73e89
//   0064141f  74 35        je     0x641456
//   00641421  8b 06        mov    eax,DWORD PTR [esi]        ; read #2
//   00641423  8b 50 24     mov    edx,DWORD PTR [eax+0x24]   ; slot 9, loaded again
//   00641426  8b ce        mov    ecx,esi
//   00641428  ff d2        call   edx
//   0064142a  3d c9 9e 66 b8 cmp    eax,0xb8669ec9
//   0064142f  74 25        je     0x641456
//   00641431  8b 06        mov    eax,DWORD PTR [esi]        ; read #3
//   00641433  8b 50 24     mov    edx,DWORD PTR [eax+0x24]   ; slot 9, loaded again
//   00641436  8b ce        mov    ecx,esi
//   00641438  ff d2        call   edx
//   0064143a  3d 41 81 14 37 cmp    eax,0x37148141
//   0064143f  74 15        je     0x641456
//   00641441  8b 06        mov    eax,DWORD PTR [esi]        ; read #4
//   00641443  8b 50 24     mov    edx,DWORD PTR [eax+0x24]   ; slot 9, loaded again
//   00641446  8b ce        mov    ecx,esi
//   00641448  ff d2        call   edx
//   0064144a  3d a4 84 f6 04 cmp    eax,0x4f684a4
//   0064144f  74 05        je     0x641456
//   00641451  8a 46 26     mov    al,BYTE PTR [esi+0x26]    ; the semantic result
//   00641454  5e           pop    esi
//   00641455  c3           ret
//   00641456  32 c0        xor    al,al                      ; low byte only
//   00641458  5e           pop    esi
//   00641459  c3           ret
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM, because the
// three highest-risk facts in this body are all easy to get subtly wrong:
//
//  * THE DISPATCH SLOT IS dword index 9, byte displacement 0x24. All four loads
//    are `MOV EDX,[EAX + 0x24]` at 0x00641415, 0x00641423, 0x00641433 and
//    0x00641443. The machine-derived dispatch record is silent on it
//    (abi_derived.dispatch call_offsets [], vtable_shaped_loads 0, indirect_calls
//    4), so the index is taken from the displacement in the instruction and
//    nothing else.
//
//  * THE DISPATCH IS TWO LEVELS DEEP, and all four times. Each call is
//    `MOV EAX,[ESI]` (a POINTER load out of the receiver) followed by
//    `MOV EDX,[EAX + 0x24]` (an index through that pointer). A one-level reading
//    of the same bytes would be `MOV EDX,[ESI + 0x24]`, which is not an
//    instruction in this body. The model loads the pointer and indexes through
//    it, and the model test plants live observer addresses in the receiver's own
//    memory at exactly the offsets a one-level model would read.
//
//  * THE DISPATCH WORD IS READ FOUR TIMES, INDEPENDENTLY. The four `MOV EAX,[ESI]`
//    at 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441 are four separate
//    loads with a CALL between each pair and nothing else, so the target of
//    dispatch N+1 is decided by the value the word holds AFTER callee N returned.
//    The model performs four separate loads rather than caching one pointer, and
//    the model test kills a caching model by having a callee overwrite the word.
//
//  * BOTH RETURN SITES WRITE ONLY AL. 0x00641451 is `MOV AL,BYTE PTR [ESI+0x26]`
//    and 0x00641456 is `XOR AL,AL` (bytes 32 c0, NOT 33 c0). Neither touches the
//    upper 24 bits of EAX, so on both paths EAX keeps the residue of the last
//    callee's own return word with its low byte replaced. This body therefore
//    does NOT return a 32-bit 0, and it does NOT return a zero-extended byte.
//    The four false exits are fully determined, because each of them is reached
//    from a CMP that has just proved EAX equal to a literal:
//      reached from 0x0064141f -> EAX == 0xbcd73e00
//      reached from 0x0064142f -> EAX == 0xb8669e00
//      reached from 0x0064143f -> EAX == 0x37148100
//      reached from 0x0064144f -> EAX == 0x04f68400
//    and the true exit is `(last_callee_return & 0xffffff00) | byte at +0x26`.
//
//    THEREFORE THE C-VISIBLE RETURN TYPE IS ONE BYTE (`std::uint8_t`), which is
//    the width the machine actually produces. The upper 24 bits are a REGISTER
//    ARTEFACT and not a source-level fact: the sole known caller consumes AL only
//    (0x00ec3b9c is a bare `E8` call and 0x00ec3ba1 is `TEST AL,AL`), so nothing
//    in the evidence carries them out of EAX. They are still reproduced and still
//    asserted, through the model-instrumentation word `model_returned_eax()`
//    below -- the residue is a machine fact about the register the body leaves
//    behind, and calling it a 32-bit C return type would claim a source-level
//    meaning the listing does not support. The byte is forwarded RAW and is not a
//    bool: 0x00641451 copies it unchanged, so 0x02, 0x7f and 0x80 all pass
//    through as themselves.
//
//  * THE FOUR LITERALS ARE 0xbcd73e89, 0xb8669ec9, 0x37148141 and 0x04f684a4,
//    each compared with CMP/JZ -- an equality test on all 32 bits. Signedness is
//    therefore irrelevant to the compare itself: two of the four have the sign bit
//    set and a model that treated them as signed magnitudes would still have to
//    match them exactly. What they NAME is not settled by this body and is not
//    claimed: this body contains no string, no import and no call that could
//    resolve them. Two words of context, both reported as context and not as
//    evidence about this body: the adjacent predicate at 0x00ec3b60 dispatches
//    the SAME slot 9 and compares its result against a fifth literal,
//    0x24720859, which is the same shape; and in the table at 0x013ff648 the word
//    at slot 9 is 0x00641770, whose whole body is `MOV EAX,[ECX+0x28]; RET`, i.e.
//    a 32-bit identity word read from the receiver. That is a property of one
//    table, not of this body -- see the sidecar's unresolved_questions.
//
//  * WHICH FUNCTION SLOT 9 DISPATCHES TO IS NOT FIXED BY THIS BODY, and no single
//    answer can be right. The six tables that install 0x00641410 disagree about
//    it (sidecar mechanics.vtable_installations):
//      0x013ff648 slot 9 = 0x00641770   (0x00641410 installed at slot 24)
//      0x01462764 slot 9 = 0x00e31100   (0x00641410 installed at slot 21)
//      0x0147c9e8 slot 9 = 0x00641850   (0x00641410 installed at slot 28)
//      0x0147ca30 slot 9 = 0x00b1e4d0   (0x00641410 installed at slot 60)
//      0x0147cbbc slot 9 = 0x00dd0e10   (0x00641410 installed at slot 21)
//      0x014893b0 slot 9 = 0x00641770   (0x00641410 installed at slot 24)
//    so the dispatched callee is a property of the object the receiver actually
//    points at, and the model deliberately names none of the six.
//
//  * THE RECEIVER. Two displacements are reached and nothing else:
//      +0x00  the dispatch word, read four times (0x00641413/21/31/41)
//      +0x26  a single byte, read once (0x00641451)
//    Nothing is written on the receiver anywhere in the 31 instructions.
//
//    NO MEMBER IS NAMED, for the receiver or for the table. The machine receiver
//    record (abi_derived.receiver) carries `bounds_only: true` with offsets
//    [0, 0x26] and register ECX: it states where the body was SEEN reaching and
//    nothing about which member is which. A displacement is a location claim and
//    that record settles those; a member NAME is an identity claim and it settles
//    none. So both objects are modelled as opaque byte runs and are reached only
//    through the displacement accessors below, each displacement being a named
//    constexpr pinned by a static_assert to the instruction it was read out of.
//    In particular the +0x25 byte that the neighbouring accessor 0x00641460 reads
//    (`MOV AL,[ECX + 0x25]; RET`) and the +0x28 word that the candidate slot-9
//    implementation 0x00641770 reads are deliberately NOT given a name or even a
//    constant: those are facts about OTHER bodies, and naming them here would be
//    a member story this body's evidence does not carry.
//
//  * THE STACK is untouched apart from the saved ESI. The only PUSH in the body is
//    0x00641410 PUSH ESI; there is no PUSH of an argument anywhere, no ADD ESP,
//    and both returns are the one-byte C3 (0x00641455 and 0x00641459). So there
//    are ZERO ordinary stack arguments, the caller owns the stack balance, and
//    the single known call site agrees: 0x00ec3b9c pushes nothing before its
//    `call 0x641410`. The machine-derived ABI record agrees independently
//    (calling_convention "__thiscall", hidden_this true, hidden_this_register
//    "ECX", return_register "EAX", stack_cleanup_bytes 0, side "caller",
//    saved_registers ["ESI"], ret_form "RET").
//
//  * ECX IS RELOADED FOR CALLS 2, 3 AND 4 BUT NOT FOR CALL 1. 0x00641426,
//    0x00641436 and 0x00641446 are `MOV ECX,ESI`, and there is no such
//    instruction before 0x00641418. That is not a different receiver: ESI is the
//    entry ECX (0x00641411 MOV ESI,ECX), nothing between 0x00641411 and
//    0x00641418 writes ECX, and a __thiscall callee is free to destroy ECX --
//    which is exactly why the reloads exist. All four calls receive the same
//    receiver; the difference is only whether the machine bothers to say so.
//
//  * THE NAME. Ghidra has no SDK name for this VA: it is `FUN_00641410`, it
//    carries no namespace, and Ghidra's own prototype is `undefined
//    FUN_00641410(void)` with no parameters and no return type. The export name
//    is therefore the canonical VA-embedding form re_00641410 and no descriptive
//    name is asserted as fact. (Sibling packages in this table family carry SDK
//    names for 0x00641400 and 0x00641460; that is a fact about those VAs and is
//    not borrowed here.)

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w1-00641410 requires an x86-32 target"
#endif

// PKG_SWARM_W1_00641410_THISCALL is asserted by the body, not chosen for
// convenience. The receiver arrives in ECX and is used without any stack
// argument: 0x00641411 `MOV ESI,ECX` takes it, 0x00641426/0x00641436/0x00641446
// hand it back for the later dispatches, and 0x00641455 / 0x00641459 are bare
// `C3` returns. The machine-derived ABI record agrees (see above), and the one
// call site in the image (0x00ec3b9c) sets ECX and calls with a bare `E8`
// relative, which is what a zero-argument __thiscall call looks like from outside.
#if defined(_MSC_VER)
#define PKG_SWARM_W1_00641410_THISCALL __thiscall
#else
#define PKG_SWARM_W1_00641410_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_swarm_w1_00641410 {

using Word = std::uint32_t;

// -- displacement accessors ---------------------------------------------------
//
// Every memory access in the model and in its test goes through one of these, by
// displacement. No member is named for either object, because the machine
// receiver record is `bounds_only: true` and therefore says where the body was
// seen reaching without saying which member is which -- see the header note on
// the receiver. Each call site names the constant that carries the displacement
// the instruction printed.
inline Word word_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline std::uint8_t byte_at(const void* base, std::size_t displacement) {
  return *reinterpret_cast<const std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline void store_word_at(void* base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

inline void store_byte_at(void* base, std::size_t displacement, std::uint8_t value) {
  *reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) + displacement) = value;
}

inline void store_pointer_at(void* base, std::size_t displacement, const void* value) {
  store_word_at(base, displacement, static_cast<Word>(reinterpret_cast<std::uintptr_t>(value)));
}

// -- the one dispatch slot, as this body uses it -------------------------------
//
// kSlotDispatched is dword index 9, byte displacement 0x24, and it is the SAME
// slot on all four dispatches. The name says which slot the body reaches and
// nothing about what it means; the six tables that install this body disagree
// about its contents, so no callee is named here.
constexpr std::size_t kSlotDispatched = 9;

// The byte displacement the four `MOV EDX,[EAX + 0x24]` instructions carry, kept
// as its own constant so the model and its test speak the instruction's own unit
// rather than a slot index they would have to convert. The static_assert below
// ties the two together, so neither can move without the other.
constexpr std::size_t kSlotDispatchedByteDisplacement = 0x24u;

// The table is modelled with 32 slots. 0x00641410 is installed at slot 24 (byte
// +0x60) of the table at 0x013ff648 -- 0x013ff648 + 0x60 = 0x013ff6a8, which is
// one of this VA's seven data xrefs -- so anything under 25 slots would be a
// table too short to hold this function, and 32 is a round modelling choice
// above that floor. This is context, not a claim: this body reads slot 9 and
// nothing else, and the model test plants observers in slots 8 and 10 to make an
// off-by-one slot displacement fail loudly.
constexpr std::size_t kVtableSlotCount = 32;

// The byte size the table is modelled with: one 4-byte slot entry each. This is
// arithmetic over the two facts above, not a claim about the real table.
constexpr std::size_t kVtableByteSize = kVtableSlotCount * sizeof(std::uint32_t);

struct AssetData;

// A slot entry. The callee's WHOLE 32-bit EAX is what the CMP consumes -- it is
// an equality test against a 32-bit literal, not a byte test and not a sign test
// -- so the return type is Word. Whether the callee returns an identity number, a
// hash or an address is not decided here; see the header note on the literals.
using SlotFn = Word (PKG_SWARM_W1_00641410_THISCALL*)(AssetData* receiver);

// The table the receiver's leading word points at. Indexed at 0x00641415,
// 0x00641423, 0x00641433 and 0x00641443, after the two-level load; nothing else
// about it is read. An opaque byte run: the body prints a displacement into it
// and not a member, so none is named.
struct alignas(4) Vtable {
  std::array<std::uint8_t, kVtableByteSize> opaque_00{};
};

// The receiver. Exactly two displacements are reached -- the dispatch word at
// +0x00 (read four times) and one byte at +0x26 (read once) -- and nothing is
// written. Modelled as an opaque byte run for the reason given above. The run is
// what makes the receiver-offset and dereference-depth decoys in the model test
// meaningful: the test plants live observer addresses at +0x04, +0x20, +0x24 and
// +0x28 inside a larger raw block, so a model that indexed the receiver itself as
// though it were the table, or that read the result byte from a neighbouring
// offset, calls one of them or returns the wrong low byte.
//
// The bound is this body's own: the highest displacement it reaches is 0x26 and
// it reads ONE byte there, so the object is at least 0x27 bytes and is modelled
// as 0x28 for 4-byte alignment. Nothing here is borrowed from a neighbouring
// body.
constexpr std::size_t kReceiverSize = 0x28u;
struct alignas(4) AssetData {
  std::array<std::uint8_t, kReceiverSize> opaque_00{};
};
static_assert(sizeof(AssetData) == kReceiverSize,
              "the modelled receiver run is 0x28 bytes: 0x26 + 1 is the last byte "
              "0x00641451 reads, rounded up to 4-byte alignment");

// The two receiver displacements as values, so the model and its test cannot
// drift apart from the instructions. 0x00 is the dispatch word because
// 0x00641413 `MOV EAX,[ESI]` has no displacement on ESI; 0x26 is the byte
// because 0x00641451 is `MOV AL,BYTE PTR [ESI+0x26]`.
constexpr std::size_t kReceiverDispatchWordDisplacement = 0x00;
constexpr std::size_t kReceiverResultByteDisplacement = 0x26u;

// The table reach, as the two instructions state it: 0x00641413 is a POINTER
// load out of the receiver and 0x00641415 is an index through that pointer. Both
// are 4-byte word reads out of memory, neither base is checked, and the second
// one's displacement is the constant above.
inline Word slot_word_at(Word table_word, std::size_t byte_displacement) {
  return *reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(table_word) + byte_displacement);
}

inline SlotFn dispatch_target_at(Word table_word, std::size_t byte_displacement) {
  return reinterpret_cast<SlotFn>(static_cast<std::uintptr_t>(slot_word_at(table_word, byte_displacement)));
}

// The same reach from the other side, for the model test: read and write one slot
// entry of a modelled table. An index is what the table is indexed BY; the
// displacement the instructions print is the static_assert below.
inline SlotFn slot_at(const Vtable* table, std::size_t index) {
  return reinterpret_cast<SlotFn>(static_cast<std::uintptr_t>(word_at(table, index * sizeof(std::uint32_t))));
}

inline void store_slot_at(Vtable* table, std::size_t index, SlotFn target) {
  store_word_at(table, index * sizeof(std::uint32_t),
                static_cast<Word>(reinterpret_cast<std::uintptr_t>(target)));
}

// -- the four literals ---------------------------------------------------------
//
// Each is the immediate of one CMP, and each is compared for full 32-bit
// equality against the value the corresponding call returned. Order matters: the
// first literal is tested against the FIRST call's result, the second against the
// second call's, and so on, so a model that permutes the literals is refuted by
// the short-circuit call counts as well as by the returned words.
constexpr Word kDenyLiteral1 = 0xbcd73e89u;  // CMP at 0x0064141a, JZ at 0x0064141f
constexpr Word kDenyLiteral2 = 0xb8669ec9u;  // CMP at 0x0064142a, JZ at 0x0064142f
constexpr Word kDenyLiteral3 = 0x37148141u;  // CMP at 0x0064143a, JZ at 0x0064143f
constexpr Word kDenyLiteral4 = 0x04f684a4u;  // CMP at 0x0064144a, JZ at 0x0064144f

// Each displacement below is pinned to the instruction it was read out of, so
// neither a slot displacement nor a receiver displacement can be moved without
// breaking an assertion that names the instruction. That is why the constants
// exist at all: the model reaches every byte through one of them, and a literal
// written inline at a use site would be a value no instruction states.
static_assert(kSlotDispatchedByteDisplacement == 0x24u,
              "0x00641415 MOV EDX,[EAX + 0x24] and its three re-loads at 0x00641423,"
              " 0x00641433 and 0x00641443 all print that displacement");
static_assert(kSlotDispatchedByteDisplacement == kSlotDispatched * sizeof(SlotFn),
              "slot 9 is the 0x24 displacement of 0x00641415 and its three re-loads");
static_assert(kVtableSlotCount > 24,
              "0x00641410 is installed at slot 24 of the table at 0x013ff648");
static_assert(sizeof(Vtable) == kVtableByteSize,
              "one dword per slot, which is what the 0x24 displacement steps by");
static_assert(kSlotDispatchedByteDisplacement + sizeof(SlotFn) <= sizeof(Vtable),
              "the slot the body reads ends inside the modelled table");
static_assert(kReceiverDispatchWordDisplacement == 0x00u,
              "0x00641413 MOV EAX,[ESI] prints a BARE [ESI]: the operand has no "
              "displacement field at all, so 0x00 is the record of that absence");
static_assert(kReceiverResultByteDisplacement == 0x26u,
              "0x00641451 MOV AL,BYTE PTR [ESI+0x26] reads that byte");
static_assert(kReceiverDispatchWordDisplacement + sizeof(Word) <= sizeof(AssetData),
              "0x00641413 reads a full word at the receiver's leading displacement");
static_assert(kReceiverResultByteDisplacement + 1u <= sizeof(AssetData),
              "0x00641451 reads ONE byte at 0x26, so the run must contain 0x27");
static_assert(kReceiverResultByteDisplacement + 1u < sizeof(AssetData),
              "the byte 0x00641451 reads is not the last byte of the run, so the "
              "run's tail padding is padding and not a modelled field");

// -- the two byte operations the return sites perform --------------------------
//
// Named once here because they are the two highest-risk operations in the body
// and the two a reconstruction is most likely to "tidy" into something else.
// 0x00641451 `MOV AL,[ESI+0x26]` and 0x00641456 `XOR AL,AL` each write EAX's low
// eight bits and leave the upper 24 alone. A model that returns a plain bool, a
// zero-extended byte, or a `XOR EAX,EAX` gets a different answer from the machine
// in every one of the five exit cases the model test drives.
inline Word with_low_byte_replaced(Word value, std::uint8_t low) {
  return (value & Word{0xffffff00}) | static_cast<Word>(low);
}
inline Word with_low_byte_cleared(Word value) {
  return with_low_byte_replaced(value, static_cast<std::uint8_t>(0));
}

// -- model instrumentation -----------------------------------------------------
// None of these are machine globals. They exist so the model test can observe
// what the machine's register and stack transfers imply, which a C++ return
// value alone cannot express. Each is a fact about a specific pair of
// instructions and is documented at its declaration.
//
// A WORD ON WHY THERE IS NO REAL-ESI PROBE HERE. The obvious way to test
// 0x00641410 `PUSH ESI` and 0x00641411 `MOV ESI,ECX` is to read and write the
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
// The value the body treats as the caller's incoming ESI at 0x00641410. The model
// test sets it before a call; the body parks it in the frame word.
Word model_esi_at_entry();
void model_set_esi_at_entry(Word value);

// The 4-byte word 0x00641410 PUSH ESI parks, and the separate word each POP ESI
// (0x00641454 and 0x00641458) writes back. They are distinct words on purpose:
// with a single word, a model that restored ESI on the true path but not on the
// false path would look correct, because the true path's value would still be
// sitting in it. model_reset_esi_probes() poisons both so that omission is
// visible, and model_esi_poison() publishes that poison so a test can tell
// "never happened" from "happened and happened to look like the poison".
Word saved_esi_frame_word();
Word restored_esi_word();
Word model_esi_poison();
void model_reset_esi_probes();

// Live ESP immediately before each of the four dispatches, published from inside
// the same asm block that performs the transfer (0x00641418, 0x00641428,
// 0x00641438, 0x00641448). The machine pushes nothing, so a callee is entered
// exactly 4 bytes below the published value and all four published values are
// equal; the model test asserts that against an assembly trampoline which samples
// ESP as its first instruction.
Word dispatch_esp_call1();
Word dispatch_esp_call2();
Word dispatch_esp_call3();
Word dispatch_esp_call4();

// The COMPLETE 32-bit EAX the body leaves behind on the return that just
// happened -- not a second return value, and not a machine global, but the one
// piece of the exit the C return type cannot carry.
//
// Both return sites write AL only (0x00641451 `MOV AL,[ESI+0x26]` and 0x00641456
// `XOR AL,AL`), so the C-visible result is a single byte and the upper 24 bits are
// the residue of the last callee's own return word. The residue is a real machine
// fact -- it is fully determined on all five exits, because each false exit is
// reached from a CMP that has just proved EAX equal to a literal -- and it is
// reproduced and asserted through this word. It is NOT a 32-bit C return type:
// nothing in the evidence carries it out of EAX (the one known caller consumes AL
// only), so declaring the return `Word` would assert a source-level width the
// listing does not fix. The model test reads BOTH: the byte through the return
// value and the whole word through here, and asserts that the byte is the word's
// low byte.
Word model_returned_eax();

// -- the reconstructed body ----------------------------------------------------
//
// __thiscall, receiver in ECX, ZERO ordinary stack arguments, bare `RET` on both
// paths. Return type is ONE BYTE, `std::uint8_t`, which is the width the machine
// produces: both exits write AL and neither writes the rest of EAX. The upper 24
// bits of the register are the residue of the last callee's return word and are
// published through model_returned_eax() above rather than declared.
//
// Meaning, as far as the 31 instructions support one: call the receiver's slot-9
// virtual (re-reading the dispatch word before every call, so a callee may
// change the target) up to four times in a row; if any of the four calls returns
// 0xbcd73e89, 0xb8669ec9, 0x37148141 or 0x04f684a4 respectively, stop there and
// produce 0 in the low byte; otherwise produce the receiver's byte at +0x26.
// Which function those four calls reach depends on the table the object carries
// at run time and is not fixed here.
extern "C" std::uint8_t PKG_SWARM_W1_00641410_THISCALL re_00641410(AssetData* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641410
