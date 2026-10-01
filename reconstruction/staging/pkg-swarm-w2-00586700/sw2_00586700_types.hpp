// PKG-SWARM-W2-00586700 -- VA 0x00586700
// FUN_00586700 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000,
// sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// Types, displacements and call-boundary declarations for the body at
// 0x00586700. The complete body is 89 instructions, 0x00586700..0x005867f3
// inclusive, 244 bytes; the listing is reproduced instruction for instruction
// in the .cpp, and it was re-derived from the image bytes for this package
// (objdump -D -b binary -m i386 -M intel over the 0xf4 bytes at this VA's file
// offset, 0x586700 - 0x401000 + 0x400 = 0x185b00). The re-derivation agrees
// with the committed Ghidra listing at every address and every length, so
// nothing in this model rests on a re-parse. 0x005867f3 is the last byte of the
// body (C3) and the committed record is NOT truncated.
//
// (0) THE FRAME, RESOLVED FROM THE BYTES RATHER THAN FROM THE ABSTENTION.
//     The machine ABI envelope abstained on this target with three reasons,
//     and the third is the load-bearing one:
//
//       "frame_pointer_untrusted: push ebp without mov ebp,esp, and EBP is
//        loaded from a register or used as a memory base, so it is a general
//        register"
//
//     Every clause of that is correct and the conclusion it draws is wrong,
//     because the premise names the instruction that settles it. The listing
//     has 0x00586705 MOV EBP,ECX. EBP is not an uncalibrated frame pointer at
//     all: it is the RECEIVER, copied out of ECX, and 0x00586704 PUSH EBP is
//     there to preserve the caller's EBP (it is popped back at 0x005867ee),
//     which is what a callee-saved register is pushed for. So every "untrusted
//     frame" displacement in the record -- [EBP+0x4d8], [EBP+0x4ec], [EBP+0x4f0],
//     [EBP+0x50c], [EBP], [EBP-0x4] -- is a receiver displacement, and the
//     machine's own receiver record agrees: register ECX, shape R-ALIAS,
//     offsets [1240, 1260, 1288, 1292] = {0x4d8, 0x4ec, 0x508, 0x50c},
//     max_offset 1292, written_through 2. R-ALIAS is precisely the shape that
//     says "the body reached the receiver through a register that was loaded
//     from ECX", which is what MOV EBP,ECX does.
//
//     The stack frame resolves the same way. With entry ESP = E:
//
//       0x00586700  SUB ESP,0xc            E-12
//       0x00586703  PUSH EBX                E-16
//       0x00586704  PUSH EBP                E-20
//       0x0058670d  PUSH ESI                E-24
//       0x00586714  PUSH EDI                E-28      <- steady state, 4 saves
//
//       flag byte  observed as [ESP+0x13] at 0x00586721 (ESP=E-28 -> E-9)
//                  and as [ESP+0x1f] at 0x0058672f (ESP=E-40 -> E-9)
//       cursor     observed as [ESP+0x14] at 0x00586770, 0x00586782, 0x005867dd
//                  (ESP=E-28 -> E-8)
//       counter    observed as [ESP+0x18] at 0x0058677a, 0x005867e5
//                  (ESP=E-28 -> E-4)
//
//     All three land inside the twelve bytes SUB ESP,0xc reserved at E-12..
//     E-1, and the two observations of the flag byte agree on E-9 from two
//     different ESP values four pushes apart, which is the cross-check that
//     makes the frame arithmetic certain rather than assumed. The envelope's
//     first abstention reason ("the linear ESP walk ends at +24, so the listing
//     is not one path") is the same fact seen from the other side: three of the
//     four pushes are callee-saves that stay outstanding across every path, and
//     the call arms push three more argument words on top of them. The frame is
//     twelve bytes plus four saved registers plus, transiently, three argument
//     words. local_extent 4 in the parse record is the machine's own count of
//     the local run and is consistent with all of it.
//
// (1) NO STRUCT MEMBERS ARE DECLARED ANYWHERE IN THIS PACKAGE, and that is a
//     requirement of the evidence rather than a stylistic choice.
//     abi_derived.value.receiver.bounds_only is TRUE, with confidence
//     SUPPORTED. bounds_only says of itself that it records where the body was
//     SEEN reaching and is not an enumeration of the receiver: it lists four
//     displacements and the body plainly touches more (0x4f0 among them). So a
//     named member would be a claim the machine record cannot ground and the
//     body does not establish. The receiver is therefore an opaque byte run and
//     every access goes through a displacement-named accessor. What the
//     displacement names mean is stated in the .cpp as a reading of the
//     listing, never as a field identity.
//
// (2) WHY SOME DISPLACEMENTS APPEAR AS LITERALS IN THE BODY AND OTHERS DO
//     NOT. The four displacements the receiver record enumerates are
//     {0x4d8, 0x4ec, 0x508, 0x50c} and they are the only ones written as hex
//     literals at their use sites, because they are the only four the machine
//     saw the body reach. The rest -- 0x4f0, 0x14, 0x23, 0x04, 0x06, 0x0c,
//     0x13, 0x1f, 0x18 -- are named constexprs carrying the address of the
//     instruction each came from. 0x4f0 in particular is a displacement the
//     body demonstrably uses (0x00586760 LEA EDX,[EBP + 0x4f0]) and is NOT in
//     the record's four, because that LEA's result is written through a
//     register at 0x00586786 rather than through EBP, so the record's own
//     operand scan could not see it. Naming it `kSlotBase` records the
//     evidence without turning an enumeration-incomplete record into a
//     contradiction.
//
// (3) THE TWO DIRECT CALLEES, AND WHAT EACH ONE'S OWN BYTES FIX.
//
//     0x005151b0, called twice (0x00586734 and 0x005867b1), 295 instructions,
//     a REAL frame (0x005151b0 PUSH EBP; 0x005151b1 MOV EBP,ESP; 0x005151b3
//     SUB ESP,0xe4) and 0x005155ed RET 0xc, so it is __thiscall with a
//     receiver in ECX and exactly THREE callee-owned stack words. Its own bytes
//     fix the argument surface without any guessing:
//
//       0x005151ba  MOV [EBP-0xd8],ECX            the receiver is saved at once
//       0x005151cc  MOV EDX,[EAX + 0x8]           this+0x08
//       0x005151cf  SUB EDX,[ECX + 0x4]           this+0x04
//       0x005151d2  CMP dword ptr [EBP + 0xc],EDX argument 2 against
//                                                (this+0x08) - (this+0x04)
//       0x005151e5  MOV EAX,[EBP + 0x10]          argument 3 is a POINTER
//       0x005151e8  MOV CL,byte ptr [EAX]         ...to a byte
//       0x005151f3  MOV EAX,[EDX + 0x4]           this+0x04
//       0x005151f6  SUB EAX,[EBP + 0x8]           ...minus argument 1
//       0x005152c9  MOV ECX,[EBP + 0x8]           argument 1 used as a
//       0x005152d8  MOV EAX,[EBP + 0x8]           DESTINATION of the fill
//       0x005152d2  PUSH ECX                      ...with argument 2 as the
//       0x005152d7  PUSH EDX                      ...count and [EBP-5] as the
//       0x005152dc  CALL 0x011e073e                ...byte value
//
//     So the three words at this+0x00 / +0x04 / +0x08 are an address triple
//     read together, argument 1 is an ADDRESS, argument 2 is a LENGTH, and
//     argument 3 points at the byte used as the fill value. The grow path
//     (0x005153ec onward) doubles this+0x04 minus this+0x00 or uses 1 when that
//     difference is zero, takes the larger of that and size+argument 2, calls
//     0x0042dee0 with (this+0x0c, capacity, 1, 0), copies, and finally stores
//     the new triple at 0x005155cc / 0x005155d7 / 0x005155e6. THAT is what
//     licenses the word "buffer" below: a start address, a current address, a
//     capacity address, and an allocator at +0x0c, grown geometrically. This
//     package models the CALL BOUNDARY only. What 0x005151b0 does inside is
//     not reconstructed here and nothing in the .cpp claims it is.
//
//     0x011e0744, called twice (0x00586745 and 0x005867c2). The xref export
//     types this edge "thunk" and the committed Ghidra callee list names it
//     "memcpy". Its call shape fixes the convention independently of that
//     name: three words are pushed at 0x00586742/43/44 (count, source,
//     destination, in that push order) and 0x0058674c ADD ESP,0xc pops them,
//     so it is __cdecl with caller-owned cleanup and the argument order is
//     (destination, source, count). Both call sites pass a count of 0 --
//     0x0058673e MOV EAX,EDI; 0x00586740 SUB EAX,EDI -- so this thunk copies
//     nothing on either path, and the model reproduces that rather than
//     replacing it with a no-op, so the test can measure the call.
//
// (4) THE FRAME-POINTER VTABLE SLOT IS RECORDED, AND NO CLASS IS NAMED. The
//     only reference to this VA in the whole binary is a DATA reference from
//     0x013f5848, and reading the image there shows a 29-word run of code
//     pointers at 0x013f57f8 whose word index 20 (byte offset 0x50) is
//     0x00586700. Six of the other slots are named independently by this
//     target's own analogue record as sharing the same run (0x005737d0,
//     0x00585890, 0x00585d10, 0x00588570, 0x0058ac10, 0x0058b650), which
//     confirms the run is a class dispatch table and not incidental code. The
//     30th word at 0x013f586c is the ASCII "Casu", so the run ends there. NO
//     class name, no slot meaning and no member identity is claimed: this body
//     contains no indirect transfer at all (0x00586734, 0x00586745, 0x005867b1
//     and 0x005867c2 are every transfer, and all four are direct), and
//     abi_derived.dispatch records indirect_calls 0, call_offsets [] and
//     vtable_shaped_loads 0. The slot index is recorded as a fact about where
//     the entry point lives; it is not modelled as dispatch.
//
// (5) WHAT IS NOT CLAIMED. The dword at self+0x4ec and the six dwords at
//     self+0x4f0+4k are zeroed by this body and never read by it (0x00586766,
//     0x00586786 and 0x005867dd are the only instructions that touch them and
//     the loop that zeroes them ends at 0x005867ea). What they are is not
//     established. Neither is the real size of the object: the highest byte
//     this body writes is self+0x570 (the last walker's end word, 0x50c + 5*20
//     + 4), and the walker's begin word at self+0x508 is read but never
//     written, so 0x571 is this package's lower bound on the object and not a
//     claim about its real extent. FUN_005151b0 additionally reads self+0x4e0
//     and self+0x4e4 (its this+0x08 and this+0x0c) and self+0x510+20k, which
//     is why the modeled receiver in the test is larger than what this body
//     alone touches.

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-SWARM-W2-00586700 is an x86-32 reconstruction; compile it with -m32."
#endif

#if defined(_MSC_VER)
#define SW2_00586700_THISCALL __thiscall
#else
#define SW2_00586700_THISCALL __attribute__((thiscall))
#endif

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg_swarm_w2_00586700 {

// The machine's own word size, and the width of every value this body moves
// between the receiver, the callees and EAX.
using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Frame displacements. The frame is twelve bytes (see note (0)); these are the
// three slots inside it, as the listing observes them from a steady-state ESP
// of entry_ESP-28.
// ---------------------------------------------------------------------------

// 0x00586700 SUB ESP,0xc
constexpr std::size_t kFrameBytes = 0x0c;

// 0x00586721 LEA EDX,[ESP + 0x13] and 0x0058679e LEA EDX,[ESP + 0x13]; the
// byte handed to 0x005151b0 as its value argument and written by 0x0058672f /
// 0x005867ac MOV byte ptr [ESP + 0x1f],0x0 (the same address from two ESP
// values four pushes apart).
constexpr std::size_t kFrameFlagOffset = 0x13;
// 0x0058672f / 0x005867ac, observed with three argument words pushed.
constexpr std::size_t kFrameFlagPushedOffset = 0x1f;
// 0x00586770 MOV dword ptr [ESP + 0x14],EDX -- the zeroing-slot cursor, read
// back at 0x00586782 and advanced at 0x005867dd.
constexpr std::size_t kFrameCursorOffset = 0x14;
// 0x0058677a MOV dword ptr [ESP + 0x18],0x6 -- the trip counter, decremented
// at 0x005867e5.
constexpr std::size_t kFrameCounterOffset = 0x18;
// 0x0058670c the value 6 stored into the counter slot.
constexpr Word kTripCount = 0x06;

// ---------------------------------------------------------------------------
// The one length constant in the body. It appears five times and always as the
// same number: 0x0058671c CMP ECX,0x23 (arm 1), 0x00586728 ADD EAX,0x23 (arm
// 1 shortfall), 0x0058673b LEA EBX,[EAX + 0x23] (arm 1 destination),
// 0x0058675b CMP EAX,0x23 (arm 1 zeroing trip count), and the five
// instructions from 0x00586799 to 0x005867db that repeat all four inside the
// loop. 35 BYTES, zero-filled, seven times over: once for the block at
// self+0x4d8 and once for each of the six loop elements.
// ---------------------------------------------------------------------------
constexpr Word kBufBytes = 0x23;

// ---------------------------------------------------------------------------
// Receiver displacements. The four in the first group are the four the
// machine-derived receiver record enumerates and are the only ones written as
// literals at their use sites in the .cpp (see note (2)).
// ---------------------------------------------------------------------------

// 0x00586707 MOV EAX,[EBP + 0x4d8] and 0x0058670e LEA ESI,[EBP + 0x4d8]:
// the start of the one buffer this body handles outside the loop. The word at
// this displacement is the buffer's start address; the word one dword above it
// is its current address (0x00586715 MOV EDI,[ESI + 0x4]).
constexpr std::size_t kHeadSlot = 0x4d8;
// 0x00586715 MOV EDI,[ESI + 0x4] -- the stride from the start word to the
// current word. Expressed as bytes because that is what the displacement is;
// kEndWordIndex below is the same fact as a subscript.
constexpr std::size_t kWordBytes = 0x04;
// The subscript form of kWordBytes, for indexing the word array the receiver
// block is. 0x00586715 is the instruction that fixes it.
constexpr std::size_t kEndWordIndex = 0x04 / 0x04;

// 0x00586766 MOV dword ptr [EBP + 0x4ec],0x0 -- the ONE dword this body zeroes
// and never reads (see note (5)). Not in the loop, not in a buffer.
constexpr std::size_t kCountSlot = 0x4ec;

// 0x00586760 LEA EDX,[EBP + 0x4f0] -- the cursor the loop zeroes six dwords
// through, advanced by 0x005867dd ADD dword ptr [ESP + 0x14],0x4. Present in
// the listing and absent from the receiver record's four; see note (2).
constexpr std::size_t kSlotBase = 0x4f0;
// 0x005867dd ADD dword ptr [ESP + 0x14],0x4.
constexpr std::size_t kSlotStrideBytes = 0x04;
constexpr std::size_t kSlotStrideWords = kSlotStrideBytes / kWordBytes;

// 0x00586774 ADD EBP,0x14 -- the walker's start, and 0x005867e2 ADD EBP,0x14
// its per-iteration step. The walker addresses the CURRENT word of a loop
// element; the START word of the same element is the one dword below it
// (0x0058678f MOV EAX,[EBP + -0x4] and 0x00586792 LEA EDI,[EBP + -0x4]), so
// the element's first word is 0x50c - 0x04 = 0x508, which is the fourth
// displacement in the receiver record. The callee's own this+0x0c read
// (0x00515461 LEA EAX,[EAX + 0xc]) puts a floor of sixteen bytes under the
// element's size; the listing fixes only the stride.
constexpr std::size_t kWalkEnd = 0x50c;
constexpr std::size_t kWalkStrideBytes = 0x14;
constexpr std::size_t kWalkStrideWords = kWalkStrideBytes / kWordBytes;

// ---------------------------------------------------------------------------
// The count the zeroing calls carry, and the count the thunk is given.
// ---------------------------------------------------------------------------

// 0x0058673e MOV EAX,EDI; 0x00586740 SUB EAX,EDI -- the memcpy thunk's third
// argument on the fast arm, and 0x005867bb/0x005867bd the same two
// instructions inside the loop. It is identically zero on both paths, which is
// what makes the fast arm a pure pointer bump.
constexpr std::size_t kEmptyCopy = 0x00;

// ---------------------------------------------------------------------------
// Opaque receiver accessors. The receiver is a byte run: no member is named
// (note (1)) and every access is by displacement (note (2)).
// ---------------------------------------------------------------------------

inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return static_cast<std::uint8_t*>(base) + displacement;
}

inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return static_cast<const std::uint8_t*>(base) + displacement;
}

inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(byte_at(base, displacement));
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(byte_at(base, displacement));
}

// The word block at `block`, where `block` is a BYTE ADDRESS already computed
// inside the receiver. `word_block(self + 0x4d8)` is exactly
// 0x00586707 `MOV EAX,dword ptr [EBP + 0x4d8]` and 0x0058670e
// `LEA ESI,[EBP + 0x4d8]`, and the body's uses spell the displacement at the
// point of use for that reason. It takes the address rather than a receiver and
// a displacement so the two can never be added twice.
inline Word* word_block(std::uint8_t* block) {
  return reinterpret_cast<Word*>(block);
}

// The buffer words hold ADDRESSES, not values: 0x00586756 MOV byte ptr
// [EAX + ECX * 1],0x0 uses the loaded word as a base address with no
// displacement added, and 0x00586744 PUSH EBX pushes one straight into
// memcpy's destination slot. `at` is the one place that conversion happens.
inline std::uint8_t* at(Word address) {
  return reinterpret_cast<std::uint8_t*>(static_cast<std::uintptr_t>(address));
}

inline const std::uint8_t* at_const(Word address) {
  return reinterpret_cast<const std::uint8_t*>(static_cast<std::uintptr_t>(address));
}

// The address of `pointer` as the machine would hold it in a word.
template <typename T>
inline Word address_of(T* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// ---------------------------------------------------------------------------
// Direct callees. Declared here and DEFINED in this package's own model test,
// as observers, so the test sees every transfer with its arguments. Neither is
// declared with a body.
//
// 0x005151b0: receiver in ECX (0x0058672d MOV ECX,ESI and 0x005867aa MOV
// ECX,EDI), three stack words pushed right-to-left at 0x00586727/0x0058672b/
// 0x0058672c and 0x005867a4/0x005867a8/0x005867a9. So the first stack word is
// the CURRENT address, the second is the shortfall, the third is the pointer to
// the value byte. Note (3) quotes the callee's own bytes for all four claims.
// NOTE ON CLEANUP: the original is 0x005155ed RET 0xc, i.e. callee-owned
// twelve bytes. The GCC spelling of __thiscall below is caller-owned, so the
// model's call boundary reproduces the RECEIVER REGISTER and the ARGUMENT
// ORDER and not which side pops; that difference is stated here rather than
// papered over, and the test measures the cdecl thunk's balance instead.
// ---------------------------------------------------------------------------
extern "C" void SW2_00586700_THISCALL growable_buffer_fill_005151b0(
    void* buffer, void* current_address, Word shortfall, const std::uint8_t* value_byte);

// 0x011e0744: __cdecl, three arguments, caller-owned cleanup (0x0058674c and
// 0x005867c9 ADD ESP,0xc). Declared with the plain C convention on purpose --
// the listing fixes the convention for this one, so there is nothing to
// approximate. Note (3).
extern "C" void* memcpy_thunk_011e0744(void* destination, const void* source,
                                       std::size_t count);

// ---------------------------------------------------------------------------
// The body under reconstruction.
//
// The return type is `int` and the value is kBufBytes, and BOTH are claims
// about the bytes rather than about intent. The listing's last write to EAX on
// every one of the six-plus-one paths is 0x005867d7 INC EAX inside the loop
// 0x005867cf..0x005867db, whose exit condition 0x005867d8 CMP EAX,0x23 /
// 0x005867db JL leaves EAX at 0x23; nothing between 0x005867dd and the
// 0x005867f3 RET touches EAX. The machine's own return must-analysis over the
// complete 89-instruction listing agrees and independently computes
// WIDTH_4_IN_EAX with one reachable exit, determinate at four bytes.
//
// The value is a compiler byproduct of the last loop's counter and carries no
// meaning: the body is a reset that produces nothing for its caller, and the
// honest statement of intent is `void`. `int` is declared because the bytes do
// produce a four-byte value in EAX and a `void` declaration would be a
// statement the machine contradicts -- but the disagreement with the ABI
// record is recorded in the metadata sidecar's unresolved_questions and in
// return_semantics, not smoothed over here.
// ---------------------------------------------------------------------------
extern "C" int SW2_00586700_THISCALL re_00586700(void* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00586700
