#pragma once

// Reconstruction of FUN_00970b30 @ 0x00970b30 (SporeApp.exe 3.1.0.22,
// image_base 0x00400000, snapshot 2540f2ca).
//
// EVIDENCE BASIS. Every claim below traces to exactly one of these; nothing
// else is claimed.
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete
//     (`listing_state: complete`, 2 of 2 parsed, 0 unparsed):
//        0x00970b30  8b 81 e8 01 00 00   MOV EAX,dword ptr [ECX + 0x1e8]
//        0x00970b36  c3                  RET
//     Raw bytes re-read live at 0x00970b30: 8b 81 e8 01 00 00 c3 cc. The
//     body is therefore 7 bytes, 0x00970b30..0x00970b36; the trailing 0xcc is
//     INT3 padding between this entry and the next and is NOT part of the body.
//
//  2. Live Ghidra decompilation, consistent with (1) and adding nothing:
//        undefined4 __fastcall FUN_00970b30(int param_1)
//        { return *(undefined4 *)(param_1 + 0x1e8); }
//
//  3. Derived ABI record for this VA (INFERRED, ABI_INFERRED,
//     `core_resolved`): x86-32; ECX is read before any definite write and is
//     dereferenced through the single memory operand, so ECX carries a
//     receiver; bare RET with no imm16 and no stack read, so the callee pops
//     nothing and the caller owns stack cleanup; 0 ordinary stack arguments;
//     the return value travels in EAX; entry slot 0 is not written through a
//     pointer, so no hidden-pointer struct return; 0 indirect calls and 0
//     vtable-shaped loads in the body. Receiver record: register ECX,
//     offsets [488], `max_offset` 488, `bounds_only: true`.
//
//  4. THE ADJACENT ENTRY IS THIS FIELD'S SETTER - the strongest structural
//     witness in the pack, and the reason the return type below is a pointer.
//     Bytes read live at 0x00970b10..0x00970b28 decode as:
//        0x00970b10  8b 54 24 04        MOV EDX,dword ptr [ESP + 0x4]
//        0x00970b14  b8 01 00 00 00     MOV EAX,0x1
//        0x00970b19  89 81 9c 00 00 00  MOV dword ptr [ECX + 0x9c], EAX
//        0x00970b1f  89 91 e8 01 00 00  MOV dword ptr [ECX + 0x1e8], EDX
//        0x00970b25  c2 04 00           RET 0x4
//     That is one stack argument stored into the SAME displacement 0x1e8 this
//     target reads, on the same ECX receiver, with callee cleanup of 4 bytes -
//     the mirror image of this getter. It establishes (a) that 0x1e8 is a
//     WRITABLE slot and not a computed or constant displacement, and (b) the
//     family shape: getter here, setter immediately below it.
//     SCOPE OF THAT WITNESS: 0x00970b10 carries no function in the program
//     database (`get_function_by_address @ 0x00970b10` returns "No function
//     found"), so it is read as DECODED CODE ADJACENT to the target and is not
//     claimed to be a separate reconstructed function. It is cited as context,
//     and nothing in this package's model depends on it.
//
//  5. Committed call-graph sidecar knowledgegraph/triage/xrefs-2540f2ca.tsv
//     records 142 direct-call edges into 0x00970b30 from 69 distinct caller
//     functions, and 0 edges out of it. Every inbound reference type is
//     `direct-call`; there is not one `vtable-ref` row. That is a high-fan-in
//     leaf accessor, and it corroborates the 0-callee, 0-dispatch machine
//     record of (3).
//
//  6. Receiver-negative claim: knowledgegraph/triage/datarefs-2540f2ca.tsv
//     contains ZERO rows for 0x00970b30 - neither as a referencER nor as a
//     referencEE. A function reachable only through a vtable would appear as
//     the target of a data reference from its own table, so on this pinned
//     snapshot this target is not the target of any recorded data reference.
//     Consistent with the 142/142 direct-call edges of (5). This is a recorded
//     absence, not an exhaustive proof that no table exists.
//
//  7. Return-value use, from three sampled callers, decompiled live. ALL THREE
//     treat the result as an ADDRESS: two dereference it at displacement
//     0x13c and one compares it against 0 as a null test:
//        0x00c4b250  iVar3 = FUN_00970b30();
//                    uVar6 = *(undefined4 *)(iVar3 + 0x13c);
//        0x00c4c090  iVar1 = FUN_00970b30();
//                    ... *(undefined4 *)(iVar1 + 0x13c) ...
//        0x00c61070  iVar2 = FUN_00970b30();
//                    if (iVar2 == 0) { iVar2 = 0; }
//                    else { iVar2 = *(int *)(iVar2 + 0x13c); }
//     A load through the result plus an explicit `== 0` test is pointer use and
//     is the reason the declared return type is `void*`. See note 8.
//
//  8. THE DERIVED RECORD'S `pointer_like` CLASS IS CONSISTENT WITH THE CALLERS
//     HERE, AND THAT IS WHY IT IS ADOPTED AS A C TYPE (unlike some sibling
//     packages, where the class was contradicted and a scalar was declared
//     instead). The record's own class is `register_class: pointer_like` with
//     `confidence: INFERRED` and `corroboration: not_available`, and by itself
//     that heuristic cannot tell a loaded word from a computed address - so it
//     is NOT the reason for the type below. The reason is (7): three
//     independently sampled callers load THROUGH the returned value and one
//     null-tests it. `void*` is the weakest C type that states the observed
//     use; it names no pointee type, and the pointee's layout is unknown (the
//     callers reach at least displacement 0x13c of it, which this package does
//     not model).
//     The declared type is spelled `void*` with no space so the validator's
//     declaration regex binds the span; the machine width is 4 bytes and
//     `void*` is 4 bytes on this target, so the two agree.
//
// WHAT IS NOT CLAIMED
//  * The class of the RECEIVER, or any name for the word at +0x1e8. The
//    receiver record is `bounds_only: true` - "where the body was SEEN
//    reaching", not a layout - so no member name appears anywhere below and
//    the displacement is spelled literally. A member name here would be a
//    field-identity assertion with nothing behind it.
//  * The pointee type of the returned pointer, and the pointee's size or
//    layout. The callers of (7) reach at least displacement 0x13c of it; this
//    package models the POINTER and nothing behind it.
//  * Nullability, ownership, AddRef/Release, or thread-safety of the returned
//    pointer or of the receiver. The body has no room for a reference call.
//  * That the setter of note 4 is the ONLY writer, or that the word at +0x1e8
//    is written once at construction. Nothing here is an immutability or
//    publication claim.
//  * Any calling convention other than __thiscall, and any ordinary stack
//    argument. The encoding has a ModRM byte, so a register receiver is
//    admissible; it names no memory operand relative to ESP, so no stack
//    argument is read.
//  * Any runtime, Wine, trace or differential claim. No runtime evidence
//    exists for this VA: the runtime axis is GATED and unattempted.
//
// A NOTE ON RECEIVER EXTENT. kReceiverExtent below is 0x1ec bytes - the prefix
// through the one word the body reads. It is a MODELLING BOUND chosen so the
// reached displacement is addressable, NOT a recovered object size. Note 4
// shows a neighbouring entry writing +0x9c, and the sampled callers reach
// +0x13c on a DIFFERENT object (the returned pointee, not the receiver), so
// nothing here bounds the receiver from above.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00970b30 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00970B30_THISCALL __thiscall
#else
#define PKG_00970B30_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00970b30_slot_1e8_getter {

// The unit the body moves: one 32-bit word in, one 32-bit word out. Note that
// this alias is NOT used as the entry's declared return type - the return is
// spelled `void*` so its width is computable from the declaration alone.
using SlotWord = std::uint32_t;

// Receiver of the target function, modelled at exactly the width the machine
// read and no more: 0x1ec bytes, 4-byte aligned, i.e. the prefix through the
// one word the body reaches. No member is declared - see "what is not claimed".
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x1ec> opaque_bytes{};  // 0x00..0x1eb
};

// The displacement the body was observed reaching on the receiver, taken from
// the ModRM/disp32 pair of `MOV EAX,dword ptr [ECX + 0x1e8]`. It is a value,
// not a member: the receiver record enumerates displacements
// (`offsets: [488]`, `bounds_only: true`) and cannot say which member is which.
constexpr std::size_t kFieldDisplacement = 0x1e8;

// The width of the word the body reads, and the width of the pointer it
// becomes. These are equal on x86-32, and the model test measures that they are.
constexpr std::size_t kFieldWidth = sizeof(SlotWord);

// The receiver word, read by displacement. This is the ONLY way this package
// touches the receiver; naming a member instead would assert an identity no
// witness in the pack supports.
inline SlotWord field_at(const OpaqueReceiver* receiver,
                         std::size_t displacement) {
  return *reinterpret_cast<const SlotWord*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// The displacement is in BYTES, not in 4-byte words. The word this body reads
// therefore sits at word index 122 of the receiver; a model that mistook the
// disp32 for an element COUNT would instead address word 0x1e8, i.e. byte
// 0x7a0, which is past the modelled extent entirely.
constexpr std::size_t kFieldIndexInWords = kFieldDisplacement / kFieldWidth;

// 0x00970b30..0x00970b36 is seven bytes; the 0xcc that follows is INT3 pad
// between this entry and the next and is deliberately not modelled.
constexpr std::size_t kTargetBodyBytes = 7;

// The body's bytes as read from 0x00970b30. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0x8b,                          // MOV r32, r/m32
    0x81,                          // ModRM: mod=10 disp32, reg=EAX, rm=ECX
    0xe8, 0x01, 0x00, 0x00,        // disp32 = 0x000001e8, little endian
    0xc3,                          // RET
};

// The byte at 0x00970b37: INT3 padding, NOT part of the body. Named so the
// model's boundary can be checked against the image.
constexpr std::uint8_t kTargetPadByte = 0xcc;

// The displacement the ADJACENT entry at 0x00970b10 writes (header note 4).
// Recorded so the model test can assert that the getter and the setter named
// here address ONE AND THE SAME byte - the fact that makes 0x1e8 a real slot
// rather than two unrelated displacements. It is not used to size anything.
constexpr std::size_t kNeighbourSetterDisplacement = 0x1e8;

// The one stack argument that neighbouring setter reads from [ESP+4] and its
// callee cleanup, recorded from the same decoding. Neither applies to THIS
// target, which reads no stack word and pops nothing; both are here so the
// test can state that contrast rather than leave it in prose.
constexpr std::size_t kNeighbourSetterStackArgumentBytes = 4;

// The direct-call edges recorded for this target, from the committed sidecar
// (header note 5), and the number of distinct caller functions among them.
// Recorded as counts, because no call site is transcribed here and the counts
// are the part of (5) that a claim could otherwise be checked on.
constexpr std::size_t kRecordedDirectCallEdges = 142;
constexpr std::size_t kRecordedDistinctCallers = 69;
constexpr std::size_t kRecordedOutgoingEdges = 0;

// The displacement at which the sampled callers of note 7 load THROUGH the
// returned pointer. Recorded as a fact about the CALLERS, not a claim about the
// pointee's size or layout, and deliberately not modelled: this package stops
// at the pointer.
constexpr std::size_t kSampledCallerPointeeDisplacement = 0x13c;

// x86-32 thiscall: receiver in ECX, 0 ordinary stack arguments, the callee pops
// nothing (bare RET) so the caller owns stack cleanup, and a 32-bit value comes
// back in EAX.
using AbiPointerSlot1e800970b30 = void*(PKG_00970B30_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(void*) == kFieldWidth,
              "the loaded word and the returned pointer are the same width here");
static_assert(sizeof(OpaqueReceiver) == 0x1ec,
              "modelled receiver extent runs through the reached word");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(kFieldDisplacement + kFieldWidth == sizeof(OpaqueReceiver),
              "the only displacement the body reaches ends the modelled extent");
static_assert(kFieldDisplacement == 0x1e8u,
              "the displacement is 0x1e8, compared semantically not by spelling");
static_assert(kFieldDisplacement == 488u, "0x1e8 is the value 488");
static_assert(kFieldIndexInWords == 122u,
              "0x1e8 is 122 four-byte words past the base");
static_assert((kFieldIndexInWords * kFieldWidth) * kFieldWidth >
                  sizeof(OpaqueReceiver),
              "reading the disp32 as an element count would address byte 0x7a0");
static_assert((kFieldDisplacement % kFieldWidth) == 0u,
              "the displacement is 4-byte aligned, as a word read requires");

// The getter of note 1 and the setter of note 4 name ONE address. If either
// constant were edited the two would drift apart silently, and the whole
// slot claim in the header would become an assertion about two unrelated
// displacements.
static_assert(kNeighbourSetterDisplacement == kFieldDisplacement,
              "the neighbouring setter writes the displacement this body reads");

// The encoding IS the observed one, and its disp32 IS the header's
// displacement, so the two statements cannot drift apart.
static_assert(kTargetEncoding[0] == 0x8bu, "0x00970b30 is MOV r32, r/m32");
static_assert(kTargetEncoding[1] == 0x81u,
              "ModRM 0x81 is mod=10 (disp32) reg=000 (EAX) rm=001 (ECX)");
static_assert((kTargetEncoding[1] >> 6) == 2u, "mod=10 selects a disp32");
static_assert(((kTargetEncoding[1] >> 3) & 7u) == 0u, "reg=000 selects EAX");
static_assert((kTargetEncoding[1] & 7u) == 1u, "rm=001 selects ECX");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[2]) |
               (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)) ==
                  kFieldDisplacement,
              "the instruction's disp32 is the header's displacement");
static_assert(kTargetEncoding[6] == 0xc3u, "0x00970b36 is a bare RET");
static_assert(kTargetEncoding[6] != 0xc2u,
              "RET 0xc2 would be RET imm16; 0xc3 pops nothing");
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the encoding array is exactly the modelled body length");
static_assert(kTargetPadByte == 0xccu, "0x00970b37 is INT3 pad, not body");

static_assert(kRecordedOutgoingEdges == 0u,
              "the sidecar records no edge out of this target");
static_assert(kSampledCallerPointeeDisplacement == 0x13cu,
              "the sampled callers load the pointee at displacement 0x13c");
static_assert(kSampledCallerPointeeDisplacement < kFieldDisplacement,
              "the pointee displacement is the CALLERS' reach, unrelated to "
              "this receiver's slot and deliberately not used to size it");

static_assert(std::is_same<AbiPointerSlot1e800970b30,
                           void*(PKG_00970B30_THISCALL*)(OpaqueReceiver*)>::value,
              "the modelled entry carries the ECX receiver and returns a pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00970b30. It is the ONLY definition in
// this package that embeds that token.
void* PKG_00970B30_THISCALL slot_1e8_00970b30(OpaqueReceiver* receiver);

}

#undef PKG_00970B30_THISCALL