// PKG-SWARM-W2-00C33580 -- VA 0x00c33580
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// Types, frame/receiver displacements and call-boundary declarations for
// FUN_00c33580, a 79-instruction Simulator-subsystem body with no ordinary stack
// arguments of its own.
//
// HONESTY NOTE ON WHERE EVERY CONSTANT IN THIS HEADER COMES FROM. The target is
// 79 instructions / 262 bytes and its complete body was re-derived from the
// image for this package with
//
//   dd if=SPORE/SporeBin/SporeApp.exe bs=1 skip=$((0x400 + 0x00c33580 - 0x401000)) count=272
//     | objdump -D -b binary -m i386 -M intel --adjust-vma=0x00c33580
//
// which reproduces the committed Ghidra listing instruction for instruction, at
// the same addresses and with the same lengths (the listing is reprinted in the
// .cpp). ghidra_function records body_start 0x00c33580, body_end 0x00c33685,
// size_bytes 262, 79 instructions; the ABI envelope's parse record agrees
// (declared_count 79, degraded false, unparsed 0, esp_unresolved false,
// local_extent 0, frame.sub 36 == 0x24). The six bytes after the RET at
// 0x00c33685 are INT3 padding, not part of the body.
//
// 1. THE STACK FRAME, WHICH IS THE WHOLE OF THIS BODY'S INTERESTING STATE.
//    The prologue is `SUB ESP,0x24` (0x00c33580) + `PUSH ESI` (0x00c33583) +
//    `MOV ESI,ECX` (0x00c33584) and the epilogue is `POP EDI` (0x00c33680) /
//    `POP ESI` (0x00c33681) / `ADD ESP,0x24` (0x00c33682) / `RET` (0x00c33685).
//    That fixes every displacement in the body without any guesswork, because
//    the epilogue is the oracle:
//
//      * the path that leaves at 0x00c33681 needs ESP == entry_ESP-0x28 there
//        (POP ESI must fetch the saved ESI out of the slot PUSH ESI made, and
//        ADD ESP,0x24 must land exactly on entry_ESP for the RET);
//      * the path that leaves at 0x00c33680 needs ESP == entry_ESP-0x2c there
//        (POP EDI must fetch the EDI saved by the mid-body PUSH EDI at
//        0x00c335ed).
//
//    PUSH EDI at 0x00c335ed is therefore NOT undone until 0x00c33680, so from
//    that instruction to the epilogue ESP sits at entry_ESP-0x2c. With FR =
//    entry_ESP-0x24 (the first byte the SUB creates) every stack operand in the
//    body resolves, and the nine dwords of the 0x24-byte frame account for
//    themselves with no slack:
//
//      FR+0x00  0x00c33646  MOV [ESP+0x10],0x2   (ESP=E-0x34)  the map key = 2
//      FR+0x04  0x00c3363e  LEA EDX,[ESP+0x10]   (ESP=E-0x30)  map-result out slot
//      FR+0x08  0x00c335b1  MOV ECX,[EAX]       -- word 0, HELD IN A REGISTER ONLY
//      FR+0x0c  0x00c335b9  MOV [ESP+0x10],EDX  (ESP=E-0x28)  record word 1
//      FR+0x10  0x00c335bd  MOV [ESP+0x14],EAX  (ESP=E-0x28)  record word 2
//      FR+0x14  0x00c33665  MOV EAX,[ESP+0x1c]  (ESP=E-0x2c)  names[0]  <-- READ,
//                                                                            NEVER
//                                                                            WRITTEN
//      FR+0x18  0x00c33617  MOV [ESP+0x20],EAX  (ESP=E-0x2c)  names[1] = 0x1667bac
//      FR+0x1c  0x00c3361b  MOV [ESP+0x24],EAX  (ESP=E-0x2c)  names[2] = 0x1667bac
//      FR+0x20  0x00c3361f  MOV [ESP+0x28],...   (ESP=E-0x2c)  names[3] = 0x1667bae
//
//    Two of those deserve their own note, because both are places a reading
//    would be wrong by one dword:
//
//    * FR+0x08..FR+0x10 is a TWELVE-BYTE BLOCK, not three independent locals.
//      0x00c33606 hands its BASE to 0x00c32cd0 (`LEA ECX,[ESP+0x10]` with
//      ESP=E-0x2c, i.e. FR+0x08), and 0x00c32cd0's own bytes write three dwords
//      through it (0x00c32cf9 `FSTP DWORD PTR [ECX]`, 0x00c32d01
//      `FSTP DWORD PTR [ECX+0x4]`, and a third store of the same shape), so the
//      block is a 3-float out-parameter that this body pre-seeds with two of its
//      three words. Its first word is never stored by this body: 0x00c335b1
//      leaves it in ECX, where 0x00c335c1 `TEST ECX,ECX` tests it.
//    * FR+0x14 (names[0]) is READ at 0x00c33665 and WRITTEN NOWHERE in the
//      body, and neither callee that is given the block's address
//      (0x004da330 at 0x00c33627, 0x00b6f380 at 0x00c33634) is given its
//      address: 0x004da330's own bytes only READ it (`CMP ECX,[EBP+0x8]` then
//      `MOV EDX,[EAX]` / `CMP EDX,[ECX+0x4]` at 0x00c4da367-0x00c4da36b, i.e.
//      it compares array[0] against array[1] and logs). So on the original the
//      value at FR+0x14 is whatever the caller's frame held. This package does
//      NOT invent a value for it: `stack_residue_word()` below is a one-word
//      injector, and the body reads that word exactly once, at the instruction
//      the machine reads it. See unresolved_questions.
//
// 2. THE RECEIVER. The machine-derived record is `bounds_only` (receiver
//    register ECX, offsets [176], max_offset 176, shape R-ALIAS,
//    written_through 0, confidence INFERRED), so NO MEMBER IS NAMED ANYWHERE in
//    this package: the receiver is an opaque byte run and every access goes
//    through a displacement accessor, so that a wrong displacement in the .cpp
//    lands on a byte the model test planted a decoy in.
//
//    Four displacements are read, three of them only as the BASE ADDRESS of a
//    sub-object that is passed to a callee in ECX (never as a value):
//
//      0xb0  0x00c33586 and 0x00c335c9  MOV EAX,[ESI+0xb0]  -- read TWICE
//      0x0c  0x00c33631  LEA ECX,[ESI+0xc]   -> 0x00b6f380's receiver
//      0x14  0x00c33643  LEA ECX,[ESI+0x14]  -> 0x00e5c780's receiver
//      0x3c  0x00c33659  LEA ECX,[ESI+0x3c]  -> 0x005c3d90's receiver
//
//    A note the alias explains: the record lists only 0xb0 because ECX is
//    copied into ESI at 0x00c33584 and never used as a base register again;
//    the three LEA displacements are still receiver-relative and the body
//    never writes through any of them (written_through 0), which is why the
//    model test diffs the whole object after every run.
//
// 3. THE THREE IMMEDIATES THAT ARE NOT DISPLACEMENTS, each with its
//    instruction:
//
//      0xffffffff  0x00c3358c / 0x00c335cf  CMP EAX,-0x1   (the handle sentinel)
//      0x2          0x00c33646             MOV [ESP+0x10],0x2  (the map key)
//      0xfffffffe   0x00c3366b             AND EDX,0xfffffffe
//      0x2          0x00c3366e             CMP EDX,0x2
//
//    and the two .rdata words this body stores, at 0x00c3360b
//    (`MOV EAX,0x1667bac`, stored twice, at 0x00c33617 and 0x00c3361b) and at
//    0x00c3361f (`MOV [ESP+0x28],0x1667bae`). Both live in .rdata (VMA
//    0x013cc000..0x0152b5ae). This package does not claim to know what the
//    strings at those addresses are; it only claims that those two words are
//    stored, in that order, into the block's elements 1, 2 and 3. That store is
//    a GLOBALS-check blocker by construction: the xref export carries no
//    data-reference edge type, so nothing can corroborate the mode. See
//    unresolved_questions.
//
// 4. THE CALL BOUNDARY, MEASURED FROM THIS BODY'S OWN EPILOGUE. Every one of
//    the pushed calls must pop its own arguments, because the epilogue has a
//    single fixed `ADD ESP,0x24` and no other adjustment except the
//    `ADD ESP,0x4` at 0x00c3367d. Six of the ten callees are corroborated
//    inside their own bytes:
//
//      0x00b3d2a0  6 bytes: MOV EAX,ds:0x167eae4 ; RET      (bare: no arg, no pop)
//      0x00ba6d80  RET 0x4 at 0x00ba6d8e / 0x00ba6d98 / 0x00ba6db5
//      0x00e5c780  RET 0x8 at 0x00e5c7b9 and 0x00e5c7c3
//      0x00c32cd0  RET 0x4 at 0x00c32d16
//      0x004da330  RET 0x4 at 0x004da396
//      0x00b6f380  RET 0x4 at 0x00b6f4a4
//
//    and 0x00f47380 ends in a BARE `RET` at 0x00f47394, which is why the caller
//    cleans up at 0x00c3367d. 0x00bb9b80 (`LEA EAX,[ECX+0x74]; RET`) and
//    0x00bba500 (`... POP ESI; RET` at 0x00bba526) take no stack argument at
//    all, which the body never pushes for them.
//
//    THE ARGUMENT-ORDER CONSEQUENCE, and it is the single most fragile fact in
//    the body: 0x00c33595 pushes the handle and 0x00c33596 then calls
//    0x00b3d2a0, whose bare RET leaves that word on the stack, and
//    0x00c3359d calls 0x00ba6d80, which takes it (`MOV EDX,[ESP+0x4]` at
//    0x00ba6d80, `RET 0x4`). So the handle pushed at 0x00c33595 is 0x00ba6d80's
//    argument, and 0x00b3d2a0's return value is 0x00ba6d80's RECEIVER. The
//    same shape repeats at 0x00c335d8/0x00c335d9/0x00c335e0. The two are not
//    interchangeable and the model test pins both.
//
// 5. NOT CLAIMED, ANYWHERE, BY THIS PACKAGE:
//
//    * a class name. The triage subsystem says "Simulator", but no MSVC RTTI
//      survives in this binary and no record names the class. `SimRecord` is
//      this package's name for the receiver and nothing more.
//    * the size of the receiver. 0x3c is the largest displacement and it is
//      only used as an address, so 0x40 is a floor and not a measurement.
//    * what the handle at 0xb0 MEANS. 0x00ba6d80's own bytes read it as a
//      two-level table index (`SHR EAX,0xc` / `AND EDX,0xfff` at
//      0x00ba6da3/0x00ba6dac) and treat 0 as "the receiver's +0x14c word" and
//      0xffffffff as "none", but that is a fact about the CALLEE, and this
//      package only claims the sentinel comparison and the two-level call.
//    * whether 0x00e5c780's find actually finds key 2 in this map. The
//      reconstruction passes the key; the answer is the callee's business.
//    * the value at FR+0x14 (see note 1) and the meaning of the 12-byte
//      out-parameter. 0x00c32cd0 writes three floats into it (FSTP x3); this
//      body reads none of them back.
//    * the return value. See the RETURN SEMANTICS paragraph in the .cpp.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-swarm-w2-00c33580 requires an x86-32 target"
#endif

// One convention macro per role, each spelled once here so that the body names
// a token the validator can resolve. This body takes its receiver in ECX and
// pops no stack word of its own (bare RET at 0x00c33685), which is __thiscall
// as the ABI record has it (`calling_convention __thiscall`, `hidden_this true`,
// `receiver_register ECX`, `stack_cleanup_bytes 0`, `stack_cleanup_owner
// caller`, `saved_registers [EDI, ESI]`, `conventions.confidence INFERRED`).
// The record also lists __fastcall as a candidate, and on x86-32 a zero-argument
// function cannot be distinguished from a fastcall one at the call boundary;
// __thiscall is chosen because every callee this body makes is itself a
// __thiscall member (ECX receiver plus a callee-cleaned stack word), which is
// the shape MSVC emits for a class method and not for a free function.
#if defined(_MSC_VER)
#define SW2_00C33580_THISCALL __thiscall
#define SW2_00C33580_CDECL __cdecl
#else
#define SW2_00C33580_THISCALL __attribute__((thiscall))
#define SW2_00C33580_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_swarm_w2_00c33580 {

using Word = std::uint32_t;

// -- the receiver -------------------------------------------------------------
// Opaque on purpose (see note 2). 0x3c is the largest displacement the body
// reaches and it is only ever used as an address, so 0x40 is the smallest
// object the body can be reading; the model test keeps a 0x10-byte canary past
// the end and asserts that nothing outside the object is ever written.
struct alignas(4) SimRecord {
  std::array<std::uint8_t, 0x40> opaque_00{};
};

constexpr std::size_t kReceiverHandle = 0xb0;  // 0x00c33586, 0x00c335c9
constexpr std::size_t kReceiverSync = 0x0c;   // 0x00c33631
constexpr std::size_t kReceiverMap = 0x14;    // 0x00c33643
constexpr std::size_t kReceiverEmit = 0x3c;   // 0x00c33659

// -- the stack frame ----------------------------------------------------------
// FR is the first byte the SUB ESP,0x24 at 0x00c33580 creates, i.e.
// entry_ESP-0x24. Offsets are FR-relative and every one of them is justified by
// the instruction quoted beside it in the .cpp.
constexpr std::size_t kFrameBytes = 0x24;    // SUB ESP,0x24 at 0x00c33580
constexpr std::size_t kFrameMapKey = 0x00;   // 0x00c33646  MOV [ESP+0x10],0x2
constexpr std::size_t kFrameMapOut = 0x04;   // 0x00c3363e  LEA EDX,[ESP+0x10]
constexpr std::size_t kFrameBlock = 0x08;    // 0x00c335ff  LEA ECX,[ESP+0x10]
constexpr std::size_t kFrameBlockWord1 = 0x0c;  // 0x00c335b9
constexpr std::size_t kFrameBlockWord2 = 0x10;  // 0x00c335bd
constexpr std::size_t kFrameNames0 = 0x14;   // 0x00c33665  read, never written
constexpr std::size_t kFrameNames1 = 0x18;   // 0x00c33617
constexpr std::size_t kFrameNames2 = 0x1c;   // 0x00c3361b
constexpr std::size_t kFrameNames3 = 0x20;   // 0x00c3361f

// The 12 bytes 0x00c32cd0 writes through the block pointer (three FSTPs).
constexpr std::size_t kFrameBlockBytes = 12;

// The immediates of note 3.
constexpr Word kInvalidHandle = 0xffffffffu;  // CMP EAX,-0x1 at 0x00c3358c
constexpr Word kMapKeyValue = 2u;             // MOV [ESP+0x10],0x2
constexpr Word kEvenMask = 0xfffffffeu;       // AND EDX,0xfffffffe
constexpr Word kRangeThreshold = 2u;          // CMP EDX,0x2
constexpr Word kRdataWordA = 0x1667bacu;      // MOV EAX,0x1667bac
constexpr Word kRdataWordB = 0x1667baeu;      // MOV [ESP+0x28],0x1667bae

// The word 0x00e5c780 writes through its out-parameter and this body then
// dereferences: MOV EAX,[EAX] then MOV ECX,[EAX+0x14] at 0x00c33653/0x00c33655.
// A value the model test can recognise, used to seed the out-slot in the model
// so that the read at 0x00c33653 is defined behaviour even though the machine
// leaves the slot to the callee. The real callee writes it on both of its
// exits (0x00e5c7b6 and 0x00e5c7c0), so the seed is never what the body uses.
constexpr Word kOutSlotSeed = 0xfeedfaceu;

// The twelve-byte block's first word (FR+0x08) is never stored by this body --
// 0x00c335b1 leaves it in ECX for the TEST at 0x00c335c1 -- and 0x00c32cd0 is
// the only writer. The model seeds it so the value the callee sees is defined
// behaviour; on the original it is whatever the caller's frame held.
constexpr Word kBlockFirstWordSeed = 0x0badf00du;

// The three words of the record 0x00bb9b80 points at, in the order the body
// reads them: 0x00c335b1 MOV ECX,[EAX], 0x00c335b3 MOV EDX,[EAX+0x4] and
// 0x00c335b6 MOV EAX,[EAX+0x8]. Word 0 is the one TEST'd; words 1 and 2 are the
// two the body stores into the twelve-byte block. The record's shape is
// corroborated from the other side by 0x00bb9b90, the setter next door, which
// writes the same three words at its receiver's +0x74/+0x78/+0x7c.
constexpr std::size_t kRecordGateWord = 0x00;
constexpr std::size_t kRecordSeedWord1 = 0x04;
constexpr std::size_t kRecordSeedWord2 = 0x08;

// 0x00e5c780's found-node displacement, 0x00c33655 MOV ECX,[EAX+0x14]. The
// word read there is passed straight to 0x005c3d90 as a POINTER: that callee's
// first instruction is 0x005c3d90 `MOV EDX,[ESP+0x4]` and its second is
// 0x005c3d94 `CMP WORD PTR [EDX],0`, i.e. it walks the argument as a
// null-terminated 16-bit string. So the word is a pointer, and this body never
// dereferences it itself.
constexpr std::size_t kNodeTextDisplacement = 0x14;

// -- opaque callee types ------------------------------------------------------
// Every one of these is an incomplete type: the body never reaches through any
// of them, it only passes their address or their address+displacement.
struct LookupObject;    // 0x00ba6d80's receiver
struct GlobalSource;    // 0x00b3d2a0's return value
struct RecordBlock;     // the 3-word / 12-byte frame block
struct ChildHandle;     // 0x00bba500's return value
struct ColorSubject;    // 0x00c32cd0's receiver (this body's own receiver)
struct ArrayTarget;     // 0x004da330's receiver
struct SyncTarget;      // 0x00b6f380's receiver (receiver + 0x0c)
struct OrderedMap;      // 0x00e5c780's receiver (receiver + 0x14)
struct MapNode;         // 0x00e5c780's found node
struct TextSink;        // 0x005c3d90's receiver (receiver + 0x3c)
struct OpaqueWideText;  // what the word at node+0x14 points at

// Displacement accessors. Used INSTEAD of named members: the receiver record is
// bounds_only, so a `->member` access in the body would assert a field NAME that
// no machine evidence in this repository can corroborate, while a wrong
// displacement lands on a planted decoy byte instead of looking plausible.
inline Word* word_at(void* base, std::size_t displacement) {
  return reinterpret_cast<Word*>(reinterpret_cast<std::uintptr_t>(base) +
                                 displacement);
}

inline const Word* word_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

inline std::uint8_t* byte_at(void* base, std::size_t displacement) {
  return reinterpret_cast<std::uint8_t*>(reinterpret_cast<std::uintptr_t>(base) +
                                          displacement);
}

inline const std::uint8_t* byte_at(const void* base, std::size_t displacement) {
  return reinterpret_cast<const std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// A typed out-parameter slot in the frame: the map search writes a node
// POINTER through it (0x00c33653 reads the word back).
template <typename T>
inline T** slot_at(void* base, std::size_t displacement) {
  return reinterpret_cast<T**>(reinterpret_cast<std::uintptr_t>(base) +
                                displacement);
}

// An INTERIOR ADDRESS of the receiver, handed to a callee as its ECX receiver.
// The three uses of this (0x0c, 0x14, 0x3c) are the reason a two-level reading
// of this body is a real failure mode: the machine forms an address and passes
// it, it never loads the word stored there.
template <typename T>
inline T* interior(void* base, std::size_t displacement) {
  return reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(base) +
                               displacement);
}

template <typename T>
inline const T* interior(const void* base, std::size_t displacement) {
  return reinterpret_cast<const T*>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// The one word of stack residue this body reads and never writes (FR+0x14,
// note 1). Declared here and DEFINED by the model test, so that the read is a
// value the test plants rather than an uninitialised local: the machine reads
// whatever the caller's frame held, and the honest model of "whatever the
// caller's frame held" is a single injectable word. This body calls it exactly
// once, at 0x00c33665, and nowhere else.
extern Word w2_00c33580_stack_residue();

// -- the ten direct callees ---------------------------------------------------
// Declared, never defined, here: the model test defines every one of them as an
// observer, which is the only way it can see the transfer, the receiver, the
// argument order and the memory state at the moment of the call. Each name is
// this package's and is derived from the callee's OWN bytes, quoted in note 4
// and beside each declaration; no persisted symbol is used except 0x00e5c780,
// whose Ghidra name is map_int_whatever_find and whose already-committed
// reconstruction (reconstruction/metadata/pkg20-gameglobal/00e5c780.json)
// declares the same two stack arguments this body pushes.

// 0x00b3d2a0, six bytes: `MOV EAX,ds:0x167eae4 ; RET`. A global-word getter: no
// receiver, no stack argument, and it pops nothing -- which is what leaves the
// handle that 0x00c33595 pushed on the stack for 0x00ba6d80.
extern "C" GlobalSource* SW2_00C33580_CDECL global_word_00b3d2a0();

// 0x00ba6d80: `MOV EDX,[ESP+0x4]` (0x00ba6d80) -- the stack word is this
// function's ONE argument; `RET 0x4` (0x00ba6d8e/0x00ba6d98/0x00ba6db5) -- the
// callee pops it, and its ECX receiver is the previous call's return value.
extern "C" LookupObject* SW2_00C33580_THISCALL table_lookup_00ba6d80(
    GlobalSource* source, Word handle);

// 0x00bb9b80, four bytes: `LEA EAX,[ECX+0x74] ; RET`. It returns the ADDRESS of
// a three-word block inside its receiver; the body reads the three words at
// 0x00c335b1/0x00c335b3/0x00c335b6 and dereferences nothing further. (Its
// immediate neighbour 0x00bb9b90 is the matching setter -- it writes the same
// three words at +0x74/+0x78/+0x7c -- which corroborates the three-word shape
// from the other side.)
extern "C" const RecordBlock* SW2_00C33580_THISCALL record_slot_00bb9b80(
    LookupObject* owner);

// 0x00bba500: `PUSH ESI ; MOV ESI,ECX ; ... ; MOV EAX,[ESI+0x80] ; POP ESI ; RET`
// (0x00bba500..0x00bba526). No stack argument; a pointer comes back in EAX and
// the body null-checks it at 0x00c335f7.
extern "C" ChildHandle* SW2_00C33580_THISCALL child_selector_00bba500(
    LookupObject* owner);

// 0x00c32cd0: the receiver is in ECX and the argument is the address of a
// TWELVE-byte out-parameter -- `MOV ECX,[ESP+0x9c]` (0x00c32cf2) then
// `FSTP DWORD PTR [ECX]`, `FSTP DWORD PTR [ECX+0x4]` and a third store of the
// same shape -- ending in `RET 0x4` (0x00c32d16). It returns that same address
// (reconstruction/staging/pkg13-e4-empire-wave3/empire_wave3.cpp asserts the
// identity); THIS BODY NEVER READS THE RETURN, which is why the model declares
// it discarded and the test's observer returns a poison pointer.
extern "C" RecordBlock* SW2_00C33580_THISCALL color_fill_00c32cd0(
    ColorSubject* subject, RecordBlock* out);

// 0x004da330: a real EBP frame, `[EBP+0x8]` is its single argument, and it ends
// in `RET 0x4` (0x004da396). Its own bytes only READ the array it is given:
// `CMP ECX,[EBP+0x8]` (0x004da347) then `MOV EDX,[EAX]` / `CMP EDX,[ECX+0x4]`
// / `SETE AL` (0x004da367..0x004da36b) -- i.e. it compares array[0] with
// array[1] and, on a match, calls 0x0041e050 with the array pointer. Nothing in
// it writes the block, which is why FR+0x14 stays uninitialised in the model.
extern "C" void SW2_00C33580_THISCALL array_check_004da330(
    ArrayTarget* target, const Word* block);

// 0x00b6f380: receiver in ECX, one argument, `RET 0x4` (0x00b6f4a4).
extern "C" void SW2_00C33580_THISCALL list_sync_00b6f380(
    SyncTarget* target, const Word* block);

// 0x00e5c780, Ghidra name map_int_whatever_find. TWO stack words and `RET 0x8`
// (0x00e5c7b9, 0x00e5c7c3). The order is fixed by its own bytes: the FIRST
// stack word is the out-parameter it WRITES (`MOV [EAX],ECX` at 0x00e5c7b6 and
// `MOV [EAX],EDX` at 0x00e5c7c0, with `MOV EAX,[ESP+0x8]` immediately before
// each), and the committed reconstruction of this address declares the same
// order (`OrderedMapEntry **result` then `const std::uint32_t *key`).
//
// Its EAX RETURN is this body's next read: 0x00c33653 `MOV EAX,[EAX]` follows
// the call directly, and 0x00e5c7b2/0x00e5c7bc show the return is the ADDRESS
// of the first stack word. This package therefore declares the return type as
// that address, which is what `MOV EAX,[EAX]` reads, and records the
// disagreement with the `void` in the pkg20 sidecar in unresolved_questions.
extern "C" MapNode** SW2_00C33580_THISCALL map_find_00e5c780(
    OrderedMap* map, MapNode** out, const Word* key);

// 0x005c3d90: `MOV EDX,[ESP+0x4]` (0x005c3d90) is its single argument and it
// dereferences it immediately -- `CMP WORD PTR [EDX],0` (0x005c3d94) then a
// 2-byte walk (0x005c3da0..0x005c3da7) before `RET 0x4` (0x005c3db7). So the
// word this body reads at node+0x14 is a POINTER to a 16-bit string, and this
// body must not dereference it itself.
extern "C" void SW2_00C33580_THISCALL text_emit_005c3d90(
    TextSink* sink, const OpaqueWideText* text);

// 0x00f47380: `MOV EAX,[ESP+0x4]` (0x00f47380), a bare `RET` at 0x00f47394 --
// so the CALLER cleans up, which is the `ADD ESP,0x4` at 0x00c3367d. No ECX
// receiver is set up by the caller.
extern "C" void SW2_00C33580_CDECL buffer_destroy_00f47380(void* buffer);

// -- the body under reconstruction -------------------------------------------
// Return type is void, and the disagreement with the machine record is stated
// rather than papered over. `abi.return_semantics` is the machine-vocabulary
// phrase `unclassified_in_EAX` and `return.void_possible` is false, so NO C++
// return type can agree with that record (and the validator's own
// evidence_returns module defers here precisely because a canonical claim
// exists). What the LISTING fixes is that no path produces a value: EAX holds,
// at the single RET, whichever of these the path last put there --
//
//   0x00c335a4  the table lookup's null result          (EAX == 0)
//   0x00c335c3  record word 2                           (a data word)
//   0x00c335d2  the handle sentinel                     (0xffffffff)
//   0x00c335e7  the second lookup's null result         (EAX == 0)
//   0x00c335f9  the child selector's null result        (EAX == 0)
//   0x00c33671  the found node's first word             (a data word)
//   0x00c33675  0                                        (the begin pointer == 0)
//   fallthrough the begin pointer                       (names[0])
//
// so nothing coherent is ever returned, Ghidra's own decompilation of this VA
// ends every path with a bare `return;`, and `void` is declared as the type
// that is true of the bytes.
extern "C" void SW2_00C33580_THISCALL re_00c33580(SimRecord* receiver);

}  // namespace openspore::reconstruction::pkg_swarm_w2_00c33580
