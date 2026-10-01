// PKG-SWARM-W2-00577310 -- VA 0x00577310
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, frame geometry, offsets and call-boundary declarations for FUN_00577310,
// the last-but-five entry of the 24-word code-pointer table at 0x013f57f8.
//
// THE COMPLETE BODY: 147 instructions, 0x00577310..0x005774e8 inclusive, 473
// bytes (ghidra_function.body_start 0x00577310, body_end 0x005774e8,
// body_span_bytes 473). Re-derived for this package with
// `objdump -D -b binary -m i386 -M intel --adjust-vma=0x00577310` over the 0x1d9
// bytes at the file offset for this VA: it reproduces the committed Ghidra
// listing instruction for instruction, at the same addresses and with the same
// lengths, so nothing in this model rests on a re-parse. The full listing is
// quoted in the .cpp.
//
// HONESTY NOTE ON WHERE EVERY NUMBER IN THIS HEADER COMES FROM. The target is 147
// instructions, so the split between "this body's own listing" and "some other
// body's listing" is short enough to state in full.
//
// 1. FROM THIS BODY'S OWN 147-INSTRUCTION LISTING, and nothing else:
//
//   * the frame: `SUB ESP,0x28` at 0x00577310 (40 bytes) then `PUSH EBX` /
//     `PUSH ESI` / `PUSH EDI` (12 bytes), so entry_ESP-0x34 is the base every
//     `[ESP+k]` in the body is read against, and `ADD ESP,0x28` + `RET 0x4` at
//     0x005774e3/0x005774e6 closes it;
//   * the two receiver displacements 0x308 and 0x30c, both read and both written
//     (the machine-derived receiver record agrees exactly: offsets [776, 780],
//     max_offset 780, register ECX, shape R-ALIAS, written_through 2,
//     bounds_only true);
//   * the four frame displacements the body addresses as a base: 0x0c, 0x10,
//     0x1c, 0x28 and 0x38;
//   * the three record ids 0x8104e4b0, 0x9d1fcc2f, 0x7d708f46 and the two words
//     every record shares, 0x510a95b and 0x40464100;
//   * the factory's two non-zero arguments 0x34 and 0x13eb430, and the four zero
//     arguments;
//   * the sentinel the incoming argument is compared against, 0xffffffff;
//   * the two data-segment addresses 0x0150cdd4 and (through 0x0067de30's own
//     bytes) 0x015fd8a8;
//   * the query key 0x700ed5e1;
//   * the three slot displacements 0x0, 0x4 and 0x2c;
//   * the two cdecl argument counts, six words and three words, fixed by the two
//     `ADD ESP` instructions this body itself owns.
//
// 2. FROM THE TABLE AT 0x013f57f8 (0x60 bytes read at that address and walked as
//    24 little-endian words). This is what licenses the word "table" and fixes
//    the slot this body occupies:
//
//      +0x00 0x005b2490  +0x04 0x005ba0d0  +0x08 0x0057d6f0  +0x0c 0x00b1fbf0
//      +0x10 0x00584300  +0x14 0x00576c50  +0x18 0x0058e6d0  +0x1c 0x00587a20
//      +0x20 0x005774f0  +0x24 0x0058ac10  +0x28 0x00585890  +0x2c 0x00588570
//      +0x30 0x0058b650  +0x34 0x005737d0  +0x38 0x00585d10  +0x3c 0x0058be50
//      +0x40 0x00574a50  +0x44 0x005723d0  +0x48 0x00577310  +0x4c 0x005732f0
//      +0x50 0x00586700  +0x54 0x00580cb0  +0x58 0x00580df0  +0x5c 0x007f30d0
//
//    So the xref from 0x013f5840 -- the only reference to this VA in the binary
//    -- is this body's own entry point stored at slot +0x48 of that table. The
//    six analogue records the briefing carries agree independently: they name
//    this same table (match_basis "shared_vtable:vtable:0x013f57f8") for
//    0x005737d0 (its +0x34), 0x00585890 (+0x28), 0x00585d10 (+0x38),
//    0x00588570 (+0x2c), 0x0058ac10 (+0x24) and 0x0058b650 (+0x30), and every
//    one of those six addresses is a word of the run above.
//
//    NONE of this is modelled as a member access. The body itself never reads the
//    receiver's +0x00; it dispatches through the tables of OTHER objects (the one
//    the factory returns, and the one the global accessor returns). So the only
//    slot boundary this package declares is on those other objects' tables, and
//    the model's `vtable_word_at` is reached exclusively with a pointer the
//    listing produced two instructions earlier. See unresolved_questions.
//
// 3. FROM THE DIRECT CALLEES' OWN BYTES, read from the image. Each convention
//    below is fixed by the callee's own terminator, and two of them are load-
//    bearing for the frame:
//
//   * 0x007b1e90 (173 bytes, 0x007b1e90..0x007b1f3c) ends `C2 04 00`, i.e.
//     RET 0x4: it pops its own single stack word. That is the DECISIVE fact for
//     this body's frame, and it is not a guess -- see the frame note in the .cpp.
//     Its own 0x007b1ea7 `MOV EBX,[ESP+0x18]` (five prologue pushes, so
//     entry_ESP+0x4) shows that the word it pops is a POINTER to a 12-byte
//     record, and its 0x007b1ead `MOV EDI,[EBX+0x8]` / 0x007b1eb4
//     `CMP EDI,0x40464100` shows the record's third word is compared against the
//     same 0x40464100 this body writes at 0x00577399, 0x005773b9, 0x005773d9 and
//     0x005774c4. Its 0x007b1ef1 `MOV EDX,[EBX]` and 0x007b1efc `PUSH EDX` show
//     the record's FIRST word is the value it forwards.
//   * 0x007b07e0 (130 bytes, 0x007b07e0..0x007b0861) ends `C2 04 00` and its
//     0x007b0852 `MOV EAX,ESI` shows it returns its own receiver. It is __thiscall
//     with one stack word.
//   * 0x0067de30 is SIX BYTES: `A1 A8 D8 5F 01  C3`, i.e.
//     `MOV EAX,DWORD PTR DS:0x015fd8a8` / `RET`. It takes no argument at all, in
//     no register, and cannot touch any caller's frame. It is a global accessor,
//     and it is the reason the block at 0x00577406..0x00577413 is unreachable in
//     this body (see the .cpp).
//   * 0x006a12a0 (59 bytes, 0x006a12a0..0x006a12da) ends `C3` with no immediate,
//     so it is cdecl and this body's own `ADD ESP,0xc` at 0x005774a6 drops its
//     three words. It reads arg1 at [ESP+0x4], passes arg2 and &arg1 to the
//     object's slot +0x24, and on success writes the instance id to
//     [ESP+0xc] = its THIRD argument (0x006a12cf) and returns true in AL.
//   * 0x00f473a0 ends in a tail call, so no callee-side cleanup exists, and this
//     body drops its six words itself with `ADD ESP,0x18` at 0x00577339 and
//     0x005774447 -- 0x18 = 6*4, which is the cdecl argument count.
//
// 4. READ FROM THE IMAGE AT TWO NAMED ADDRESSES, and cited here rather than
//    modelled:
//
//   * 0x013eb430 is the ASCII string "Editor" (seven bytes, NUL-padded, followed
//     by "Baker system management."). It is this body's second factory argument
//     at 0x0057732d and 0x0057743b, and it is why the triage cluster calls the
//     cluster editor-core. No claim is made that 0x34 (the first argument) is a
//     size, a count or a flag: nothing in any body read here says.
//   * the word at 0x0150cdd4 is 0x3f800000, which is the IEEE-754 single 1.0f.
//     This body pushes the ADDRESS of that global (0x00577415 `MOV EDX,[0x0150cdd4]`)
//     as the second argument of the slot +0x2c call, so the callee reads the
//     float itself. The model passes the ADDRESS, because that is what the bytes
//     do; the value is recorded here and asserted nowhere.
//
// 5. NOT CLAIMED, ANYWHERE, BY THIS HEADER:
//
//   * a class name for the receiver. The subsystem says "Editor" and the cluster
//     says "editor-core", but no MSVC RTTI survives in this binary and no record
//     names the class. The type below is called EditorReceiver for readability
//     and for nothing else.
//   * the receiver's size beyond what the body touches: 0x30c + 4 == 0x310 is the
//     last byte this body can write, and the run is rounded to exactly that.
//   * what the 12-byte record's SECOND word, 0x510a95b, means. 0x007b1e90 reads
//     only the first and the third word of the record it is handed, so the
//     middle word is written by this body and not read by the one callee whose
//     body was read. It is modelled as an opaque word.
//   * what 0x0067de30's global, 0x015fd8a8, holds at runtime. The committed
//     image has it zero, because it is a .data cell filled in by start-up code
//     that is not in this repository.
//   * that the three records are three DIFFERENT properties. They are three
//     different 32-bit ids passed to the same callee on the same object; nothing
//     read here maps any of the three to a name.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00577310 requires an x86-32 target"
#endif

// Two conventions are needed, and both are fixed by machine bytes rather than
// chosen for convenience:
//
//   W2_00577310_THISCALL  this body (terminator C2 04 00 = RET 0x4 at
//                         0x005774e6, receiver copied out of ECX at 0x00577315
//                         and dereferenced through ESI at 0x00577317 before any
//                         definite write to it) and its two callees that pop
//                         their own stack words: 0x007b07e0 (RET 0x4 at
//                         0x007b0860) and 0x007b1e90 (RET 0x4 at 0x007b1f3b).
//
//   W2_00577310_CDECL    0x00f473a0 (ends in a tail call; this body drops its six
//                         words at 0x00577339 and 0x00577447), 0x0067de30 (six
//                         bytes, a bare RET) and 0x006a12a0 (bare RET at
//                         0x006a12da; this body drops its three words at
//                         0x005774a6).
#if defined(_MSC_VER)
#define W2_00577310_THISCALL __thiscall
#define W2_00577310_CDECL
#else
#define W2_00577310_THISCALL __attribute__((thiscall))
#define W2_00577310_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00577310 {

using Word = std::uint32_t;

// -- the frame -----------------------------------------------------------------
// Every `[ESP+k]` in the body is written below with ESP at entry_ESP-0x34: the
// prologue's `SUB ESP,0x28` (40 bytes) plus the three saved-register pushes
// (12 bytes). 0x005774e3 `ADD ESP,0x28` after the three POPs lands back on
// entry_ESP, and 0x005774e6 `RET 0x4` then drops the argument word.
//
// The frame's own 40 bytes therefore start at +0x0c (entry_ESP-0x28) and end at
// +0x33 (entry_ESP-0x1). 0x0c..0x0b is the argument word, which is the CALLER's
// slot at entry_ESP+0x4, not the callee's: the body clears it in place at
// 0x005773ef and then hands its own address to the slot +0x2c call as an
// out-parameter at 0x00577420/0x00577424. That aliasing is load-bearing, so the
// model keeps the word in a local of its own and passes that local's address.
constexpr std::size_t kFrameBytes = 0x28u;                  // SUB ESP,0x28
constexpr std::size_t kSavedRegisterBytes = 0x0cu;          // PUSH EBX/ESI/EDI
constexpr std::size_t kFrameBaseToEntry = 0x34u;           // 0x28 + 0x0c
constexpr std::size_t kFrameLookupOutDisplacement = 0x0cu;  // LEA ECX,[ESP+0xc]
constexpr std::size_t kFrameRecordOneDisplacement = 0x10u;  // LEA EAX,[ESP+0x10]
constexpr std::size_t kFrameRecordTwoDisplacement = 0x1cu;  // LEA ECX,[ESP+0x1c]
constexpr std::size_t kFrameRecordThreeDisplacement = 0x28u;// LEA EDX,[ESP+0x28]
constexpr std::size_t kFrameRecordFourDisplacement = 0x28u; // LEA EAX,[ESP+0x28]
constexpr std::size_t kFrameArgumentDisplacement = 0x38u;   // MOV EBX,[ESP+0x38]
constexpr std::size_t kRecordWords = 3u;                    // 12 bytes, three calls

// The array a model allocates for the frame covers exactly the forty bytes the
// prologue reserved, i.e. the words at base+0x0c .. base+0x33. Every
// displacement above is the one the LISTING uses -- relative to the base -- so it
// is translated once, here, rather than at each of the eleven uses. A
// reconstruction that forgot the translation would write one word past the array
// and the model test's sanitizer build would say so.
constexpr std::size_t kFrameFirstDisplacement = kFrameLookupOutDisplacement;
constexpr std::size_t kFrameLastDisplacement = kFrameRecordThreeDisplacement +
                                               (kRecordWords - 1u) * sizeof(Word);
static_assert(kFrameLastDisplacement + sizeof(Word) == kFrameBytes + kFrameFirstDisplacement,
              "the three records end exactly at the top of the reserved frame");
// The fourth registration reuses the third record's displacement, which is why
// these two are the same number. Two names, one value, on purpose.
static_assert(kFrameRecordFourDisplacement == kFrameRecordThreeDisplacement,
              "0x005774b7 forms the same address as 0x005773c8: the fourth "
              "registration overwrites the third record in place");

// -- the receiver's two displacements ------------------------------------------
// Read AND written by this body, so both are the machine-derived receiver
// record's two offsets and nothing else. They are reached through the
// displacement accessors below and never as members, because that record is
// bounds_only: it says where the body was seen reaching, not which member is
// which, and naming a member would declare an identity the machine does not fix.
constexpr std::size_t kReceiverToolMemberDisplacement = 0x308u;   // read 0x00577317
constexpr std::size_t kReceiverTargetMemberDisplacement = 0x30cu; // read 0x0057745d

// -- the 12-byte record --------------------------------------------------------
// word 0 is the id this body varies; words 1 and 2 are the same on all three
// registration records. 0x007b1e90's own 0x007b1ead `MOV EDI,[EBX+0x8]` and
// 0x007b1eb4 `CMP EDI,0x40464100` read word 2 and compare it against the same
// constant, so the callee corroborates the layout and the tail value.
constexpr std::size_t kRecordIdDisplacement = 0x00u;    // MOV EDX,[EBX] in the callee
constexpr std::size_t kRecordMiddleDisplacement = 0x04u; // read by no body here
constexpr std::size_t kRecordTailDisplacement = 0x08u;   // CMP EDI,0x40464100
constexpr Word kRecordIdOne = 0x8104e4b0u;
constexpr Word kRecordIdTwo = 0x9d1fcc2fu;
constexpr Word kRecordIdThree = 0x7d708f46u;
constexpr Word kRecordMiddleWord = 0x510a95bu;
constexpr Word kRecordTailWord = 0x40464100u;

// The record is declared here so the model test can build one readably; the .cpp
// fills its three words through `word_at` and never names a member, because a
// `field_00` access in the body would declare a field identity the receiver
// record cannot corroborate and the 12-byte record is not the receiver anyway.
struct PropertyRecord {
  Word field_00;
  Word field_04;
  Word field_08;
};
static_assert(sizeof(PropertyRecord) == 0x0cu,
              "three words, read and written by 0x007b1e90 through one pointer");

// -- the receiver --------------------------------------------------------------
// An opaque run with NO members, on purpose. 0x30c is the largest displacement
// this body writes and each store is one dword, so 0x30c + 4 == 0x310 is the
// last byte it can possibly touch.
struct alignas(4) EditorReceiver {
  std::array<std::uint8_t, 0x310u> opaque_00{};
};
static_assert(sizeof(EditorReceiver) == 0x310u,
              "0x30c plus one dword is the last byte this body can write");

// -- the two table-word displacements this body dispatches through -------------
// The table pointer is read from the dispatched object's +0x00 and the entry
// from the table at the named displacement. The evidence for each is the
// listing's own two-step load, quoted per call site in the .cpp; the
// classification the tooling reaches independently reads the same three
// displacements (0x0, 0x4, 0x2c) as slot offsets.
constexpr std::size_t kTablePointerDisplacement = 0x00u;
constexpr std::size_t kSlotAcquireDisplacement = 0x00u;   // 0x0057735f / 0x0057746d
constexpr std::size_t kSlotReleaseDisplacement = 0x04u;   // 0x00577371 / 0x0057747f
constexpr std::size_t kSlotQueryDisplacement = 0x2cu;     // 0x0057741d

// -- the factory pair ----------------------------------------------------------
// 0x00f473a0 is given six words and 0x007b07e0 one; the second factory argument
// is the address of the ASCII string "Editor" at 0x013eb430, and the
// constructor's word is the all-ones sentinel 0xffffffff (printed `PUSH -0x1`).
constexpr Word kFactoryFirstArgument = 0x34u;
constexpr std::size_t kFactoryClassNameAddress = 0x013eb430u;
constexpr Word kSentinelWord = 0xffffffffu;
constexpr Word kConstructorArgument = 0xffffffffu;
constexpr std::size_t kFactoryArgumentWords = 6u;  // ADD ESP,0x18 == 0x18/4
constexpr std::size_t kLookupArgumentWords = 3u;   // ADD ESP,0xc  == 0xc/4
constexpr Word kLookupKey = 0x700ed5e1u;

// -- the data-segment cells ---------------------------------------------------
// 0x0150cdd4 is READ BY THIS BODY at 0x00577415 with `MOV EDX,DWORD PTR
// DS:0x0150cdd4` and 0x00577425 pushes EDX. That is a LOAD of the cell's
// contents, not an address-of: the slot +0x2c call's second argument is the WORD
// the cell holds. In the committed image the cell holds 0x3f800000, which is the
// IEEE-754 single 1.0f -- and that value is fixed by the image, not by this
// body, so it is a constant of the binary rather than of the reconstruction.
//
// The cell lives in the original program's .data at an address no model process
// can map, so the model holds it in this package-scope word and the test
// overwrites it. That is instrumentation and is declared as such: the model
// forwards whatever the word holds, which is what the two instructions say, and
// the test drives it with a value that is not the image's so that a
// reconstruction which hard-codes 0x3f800000 instead of forwarding the cell is
// caught.
extern Word g_query_weight_cell;

// 0x015fd8a8 is not named by this body at all. It is named by 0x0067de30's own
// two instructions (`MOV EAX,DWORD PTR DS:0x015fd8a8` / `RET`), which is why
// this package records the address and models nothing for it: the value is
// whatever the original program's start-up code put there.
constexpr std::size_t kGlobalObjectCellAddress = 0x015fd8a8u;
constexpr Word kQueryWeightCellImageValue = 0x3f800000u;

// -- displacement accessors ----------------------------------------------------
inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                          displacement);
}

inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                       displacement);
}

// A word of the model's frame, addressed by the displacement the LISTING uses
// (relative to the base entry_ESP-0x34), translated into the array's own index.
inline Word* frame_word_at(void* frame, std::size_t displacement) {
  return word_at(frame, displacement - kFrameFirstDisplacement);
}

// The machine's own two-level load, kept as two named steps so the model test
// can decoy each level separately -- a wrong base object, a wrong table word, a
// wrong slot displacement and a one-level load all land differently here.
// This is the ONLY place in the package where a table is addressed, and it is
// reached exclusively with a pointer this body's own listing produced.
inline Word vtable_word_at(void* object, std::size_t slot_displacement) {
  const Word table_word = *word_at(object, kTablePointerDisplacement);
  void* const table = reinterpret_cast<void*>(static_cast<std::uintptr_t>(table_word));
  return *word_at(table, slot_displacement);
}

// The three dispatch shapes this body makes, as the machine makes them: a code
// word is read out of a table and called with the object in the receiver
// register. Each is called at most once per object per site pair, and the
// release shape is the one this body uses to drop the two swapped-out members
// and the query's out-parameter.
using AcquireSlot = void (*)(void* object);
using ReleaseSlot = void (*)(void* object);
using QuerySlot = bool (*)(void* object, Word subject, Word weight, Word* out_parameter);

// -- the five direct callees ---------------------------------------------------
// Declared here and NOT defined here: this package's own model test defines each
// one as an observer, which is how the test sees every transfer, with which
// arguments, in which order, and gets to decide what it does to memory.
//
// None of the five is named by a persisted record except 0x006a12a0, which
// Ghidra calls App::Property::GetKeyInstanceID. That name is kept, with the
// address appended, because inventing a competing name for a symbol the
// analysis already has would create two names for one address. The other four
// names are this package's and are derived from the callees' own instruction
// bytes, quoted above.

// 0x00f473a0, called twice (0x00577334 and 0x00577442) with the SAME six words.
// cdecl: the body drops them itself with ADD ESP,0x18. Its return value is a
// pointer or null (0x0057733c / 0x0057744a `TEST EAX,EAX`), and it becomes the
// receiver of 0x007b07e0 -- or, when null, the body skips the constructor and
// the member stays null, which the model reproduces.
extern "C" Word W2_00577310_CDECL factory_lookup_00f473a0(Word first_argument,
                                                        const char* class_name,
                                                        Word third_argument,
                                                        Word fourth_argument,
                                                        Word fifth_argument,
                                                        Word sixth_argument);

// 0x007b07e0, called twice (0x00577344 and 0x00577452) with ECX = the factory's
// return and one stack word, 0xffffffff. __thiscall: its own terminator is
// `C2 04 00`. Its 0x007b0852 `MOV EAX,ESI` shows it returns its receiver, which
// is what the model relies on when the factory returned non-null.
extern "C" void* W2_00577310_THISCALL construct_in_place_007b07e0(
    void* instance, Word argument);

// 0x007b1e90, called FOUR times (0x0057739d, 0x005773bd, 0x005773dd on the
// receiver's 0x308 word, and 0x005774cc on its 0x30c word), each time with ECX =
// the member word re-read from the frame and one stack word: the ADDRESS of a
// 12-byte record. __thiscall: `C2 04 00` at 0x007b1f3b, and that terminator is
// also what fixes this body's own frame -- see the .cpp.
//
// Return type is void on purpose. This body never reads EAX after any of the
// four calls: 0x005773a2, 0x005773c2, 0x005773c8 and 0x005774d1 all overwrite
// it from the frame or from memory before anything can observe it, and inside
// the callee EAX holds whatever its last internal call left (0x007b1eff's AL
// possibly clobbered by the 0x007b1f11 call and by the release at 0x007b1f2b).
// A return type is therefore not established by any byte, and declaring one
// would be an invention.
extern "C" void W2_00577310_THISCALL record_register_007b1e90(
    void* receiver, const PropertyRecord* record);

// 0x0067de30, called once (0x005773f7) with no argument in any register and
// none on the stack. Its whole body is `MOV EAX,[0x015fd8a8]` / `RET`, so it
// returns a cell's value and nothing else. cdecl.
extern "C" void* W2_00577310_CDECL global_object_0067de30(void);

// 0x006a12a0, called once (0x0057749d) with three words: the query's out-pointer
// (0x0057748a / 0x0057748e), the constant key 0x700ed5e1 (0x0057748f) and the
// query's out-parameter word read back from the frame (0x00577486 / 0x00577494)
// -- in that push order, so the LAST-pushed is the FIRST argument. cdecl: bare
// `RET` at 0x006a12da, and the body drops the three words at 0x005774a6.
//
// The name is Ghidra's: App::Property::GetKeyInstanceID. Its own body writes
// the instance id into its THIRD argument (0x006a12cf `MOV EDX,[ESP+0xc]` with
// the stack already balanced by the inner __thiscall at 0x006a12b7) and returns
// a bool in AL -- and THIS BODY DISCARDS that bool, reloading EAX from the
// out-parameter at 0x005774a2 before testing it at 0x005774a9. The test drives
// a case where the two disagree, which is what makes that discard falsifiable.
extern "C" bool W2_00577310_CDECL instance_id_lookup_006a12a0(
    void* object, Word key, Word* out_parameter);

// -- the body under reconstruction ---------------------------------------------
//
// __thiscall: receiver in ECX, copied into ESI at 0x00577315 and addressed
// through ESI on every access, which is why the machine-derived receiver record
// names ECX with shape R-ALIAS. Exactly ONE ordinary stack argument, the word at
// entry_ESP+0x4, read at 0x005773e2 as `MOV EBX,[ESP+0x38]` with ESP at
// entry_ESP-0x34 -- and read on a path that never pushed an argument, which is
// the cleanest possible proof that the slot is the caller's. `RET 0x4` at
// 0x005774e6 (bytes C2 04 00) proves the callee owns the cleanup, which rules out
// cdecl and fastcall.
//
// RETURN TYPE: void, and the disagreement is recorded rather than papered over.
// The machine-derived record says `return_semantics: unclassified_in_EAX` and
// the persisted Ghidra record says `return_type: undefined`; neither is a type.
// The listing is what decides it, and the listing produces no value: the three
// paths that reach the epilogue leave EAX holding three different incidental
// words -- the receiver's 0x308 member on the sentinel path (0x005773c2, or
// 0x00577378 on the arm that skipped the cold block), the query's own AL on the
// false path (0x0057742b), and the release's return on the tail path
// (0x005774de). A function that returned a pointer on one arm, a byte on another
// and nothing on a third is not returning anything, so `void` is declared and
// the model asserts nothing about EAX. See the sidecar's return_semantics block.
extern "C" void W2_00577310_THISCALL re_00577310(EditorReceiver* receiver,
                                                  Word argument);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00577310
