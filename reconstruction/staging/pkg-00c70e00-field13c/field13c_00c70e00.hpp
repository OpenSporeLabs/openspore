#pragma once

// Reconstruction of FUN_00c70e00 @ 0x00c70e00 (SporeApp.exe 3.1.0.22,
// snapshot 2540f2ca).
//
// EVIDENCE BASIS (every claim below traces to exactly one of these; nothing
// else is claimed).
//
//  1. Live Ghidra listing of the body - six instructions, complete, and read
//     live from the program database as raw bytes over
//     0x00c70e00..0x00c70e17:
//
//       0x00c70e00  8b 89 3c 01 00 00   MOV ECX,dword ptr [ECX + 0x13c]
//       0x00c70e06  85 c9               TEST ECX,ECX
//       0x00c70e08  74 05               JZ 0x00c70e0f
//       0x00c70e0a  e9 a1 cc f1 ff      JMP 0x00b8dab0
//       0x00c70e0f  b8 01 00 00 00      MOV EAX,0x1
//       0x00c70e14  c3                  RET
//       0x00c70e15  cc cc cc            INT3 padding, NOT part of the body
//
//     Live bytes, verbatim: 8b 89 3c 01 00 00 85 c9 74 05 e9 a1 cc f1 ff
//     b8 01 00 00 00 c3 cc cc cc. The body is therefore 21 bytes,
//     0x00c70e00..0x00c70e14, matching the live `ghidra_function` record's
//     `body_span_bytes: 21`, `body_end: "00c70e14"`. The three 0xcc bytes at
//     0x00c70e15..0x00c70e17 are alignment padding between this entry and the
//     next and are deliberately not modelled.
//
//  2. Live Ghidra decompilation, consistent with (1) and adding nothing:
//
//       undefined4 __fastcall FUN_00c70e00(int param_1)
//       {
//         undefined4 uVar1;
//         if (*(int *)(param_1 + 0x13c) != 0) {
//           uVar1 = FUN_00b8dab0();
//           return uVar1;
//         }
//         return 1;
//       }
//
//     Two things in it are evidence and one is not. That the test is on
//     `*(int *)(param_1 + 0x13c)` and that the false arm returns 1 are
//     evidence, and they are read off the listing above. The `__fastcall`
//     spelling is NOT evidence: the live `ghidra_function` record carries
//     `ghidra_calling_convention: null`,
//     `ghidra_has_calling_convention: false`,
//     `ghidra_calling_convention_signal: "no_information"` and
//     `ghidra_calling_convention_role: "cross-validation-only"`, so
//     `__fastcall` is the decompiler's rendering of an unregistered
//     prototype and weighs nothing against note 4.
//
//  3. The derived ABI record for this VA (`categories.abi_derived`, schema
//     `openspore-abi-inference-1`). Its `abi` block, verbatim:
//
//       architecture          x86-32
//       calling_convention    __thiscall
//       candidate_conventions ["__thiscall", "__fastcall"]
//       receiver              true, register ECX
//       ret_form              RET
//       return_register       EAX  (return_semantics: integral_in_EAX)
//       stack_cleanup_bytes   0    (owner: caller)
//
//     and its surrounding envelope:
//
//       parse                 declared_count 6, unparsed 0, degraded false,
//                             flow_complete true, frame: no EBP frame
//       receiver              present true, register ECX, offsets [316],
//                             max_offset 316, shape R-DIRECT,
//                             written_through 0, bounds_only TRUE
//       cleanup               0 bytes, side caller,
//                             evidence "ret with no immediate, no stack reads"
//       stack_arguments       observed_slots 0, derived_slots 0, total 0
//       dispatch              indirect_calls 0, call_offsets [],
//                             vtable_shaped_loads 0
//       tail_call             present true, target "0x00b8dab0",
//                             form "epilogue_then_jmp", after_frame_setup false
//       return                register EAX, register_class integral,
//                             type null, void_possible false,
//                             bulk_write false
//       sret                  present false, confidence APPROXIMATION
//       variadic              UNKNOWN
//       verdict               ABI_UNKNOWN
//       completeness          PARTIAL
//
//     Every claim the source below makes about shape, register, displacement,
//     arity, cleanup and return register is one of those fields read directly.
//     Its one INFERRED conclusion (C7, "calling convention is __thiscall") is
//     discussed in note 4; its `verdict: ABI_UNKNOWN` is discussed in note 12.
//
//  4. WHAT THE BYTES DO AND DO NOT DISCRIMINATE ABOUT THE CONVENTION.
//     Read straight out of the listing and (3), with nothing added:
//
//       PROVEN, and discriminating:
//         * exactly ONE register argument, and it arrives in ECX. 0x00c70e00
//           reads ECX on entry - it is the base of the only memory operand -
//           and the derived record names `receiver_register: ECX`,
//           `hidden_this_register: ECX`. Four sampled call sites put the
//           receiver in ECX immediately before the call and push nothing
//           (see note 5). This REFUTES __cdecl, under which the receiver would
//           arrive at [ESP+4] and the register-relative read at 0x00c70e00
//           would have no receiver to read through.
//         * ZERO ordinary stack arguments. No instruction in the body names a
//           memory operand relative to ESP; the only memory operand in the
//           whole body is `dword ptr [ECX + 0x13c]`. The derived record
//           agrees (`stack_arguments.observed_slots: 0`,
//           `derived_slots: 0`, `total_bytes: 0`).
//         * ZERO bytes of callee cleanup, owned by the CALLER. 0x00c70e14 is
//           the single byte 0xc3, which carries no imm16; 0xc2 would.
//           With zero stack arguments even a __stdcall would pop nothing, so
//           cleanup is 0 under every candidate convention and discriminates
//           nothing here - it is stated because it is provable, not because it
//           separates the candidates.
//
//       NOT PROVEN, and NOT discriminated by any byte of this body:
//         * __thiscall versus __fastcall. For a function with one register
//           argument and zero stack arguments the two conventions emit
//           IDENTICAL machine code; there is no byte that distinguishes them,
//           and the record says so in its own `candidate_conventions` list.
//           What would distinguish them is a SOURCE-LEVEL fact the evidence
//           does not carry: that the register argument is a C++ `this` on a
//           class rather than an ordinary first parameter. Nothing in this
//           pack names a class for the receiver - `receiver.bounds_only` is
//           true, `class_type` is null, `namespace` is null, `sdk_type` is
//           null, `sdk_name` is null - so the distinction is UNKNOWN.
//
//       The macro below is spelled __thiscall because that is the derived
//       record's own `calling_convention` and this package follows the
//       repository's machine-derived record rather than the decompiler's
//       unregistered-prototype rendering (note 2). It is a NAMING of a shape
//       the record names, not a claim that the bytes chose between two
//       byte-identical encodings, and no argument in this package depends on
//       the difference. `confidence: INFERRED` and
//       `corroboration: not_available` on that record are recorded here
//       rather than glossed: the two-oracle corroboration the record asks for
//       does not exist for this VA, because the persisted ABI layer is an
//       empty object (`categories.abi` -> `record.abi` is `{}`) and the
//       `cross_validation` block reports `agreement: false`,
//       `ghidra: "no_information"`, `persisted: "no_information"`.
//
//  5. Sampled call sites, read live, all four the same shape. In every one the
//     receiver reaches ECX and NOTHING is pushed between that write and the
//     call:
//
//       0x00ba0245  8b 8c 24 44 01 00 00  MOV ECX,dword ptr [ESP + 0x144]
//       0x00ba024c  e8 af 0b 0d 00        CALL 0x00c70e00
//       0x00ba0251  83 f8 05              CMP EAX,0x5
//       0x00ba0254  75 04                 JNZ 0x00ba025a
//
//       0x00be2127  8b c8                 MOV ECX,EAX        (from 0x01021260)
//       0x00be2129  e8 d2 ec 08 00        CALL 0x00c70e00
//       0x00be212e  83 f8 04              CMP EAX,0x4
//       0x00be2131  0f 85 fa 01 00 00     JNZ 0x00be2331
//
//       0x00d56c57  8b c8                 MOV ECX,EAX        (from 0x01021260)
//       0x00d56c59  e8 a2 a1 f1 ff        CALL 0x00c70e00
//       0x00d56c5e  83 f8 04              CMP EAX,0x4
//       0x00d56c61  0f 84 34 0a 00 00     JZ  0x00d5769b
//
//       0x00ff749b  8b 4c 24 14           MOV ECX,dword ptr [ESP + 0x14]
//       0x00ff749f  e8 5c 99 c7 ff        CALL 0x00c70e00
//       0x00ff74a4  83 f8 05              CMP EAX,0x5
//       0x00ff74a7  75 09                 JNZ 0x00ff74b2
//
//     Four of four. That is the observational counterpart of the arity claim
//     in note 4, and it is why the modelled entry takes no stack argument.
//     All four also order the result against a SMALL CONSTANT - 0x4 and 0x5 -
//     and none dereferences it, so the value is used as an ORDERED SCALAR.
//     That is why the modelled return is a scalar and is why the header
//     spells the return type `std::uint32_t`.
//
//  6. THE TAIL TRANSFER, AND THE CHAIN OF ECX. This is the load-bearing fact
//     of the whole body and it is proved from the listing, not assumed:
//
//       * 0x00c70e0a is `JMP 0x00b8dab0`, an unconditional transfer with NO
//         preceding frame teardown - the record calls the form
//         `epilogue_then_jmp` with `after_frame_setup: false`, and the bytes
//         confirm it: there is no POP, no MOV ESP,EBP and no ADD ESP,n
//         anywhere in the 21 bytes. It is a TAIL TRANSFER out of the body.
//       * Its rel32 is `a1 cc f1 ff` = 0xfff1cca1 = -930655, and
//         0x00c70e0a + 5 - 930655 = 0x00b8dab0 exactly.
//       * ECX is NOT REWRITTEN between 0x00c70e00 and 0x00c70e0a. The only
//         instructions in between are 0x00c70e06 (TEST, which writes only
//         EFLAGS) and 0x00c70e08 (JZ, which writes only EFLAGS). So at the
//         moment of the jump ECX still holds the value 0x00c70e00 loaded out
//         of the incoming receiver.
//       * Therefore 0x00b8dab0's own ECX - its receiver - IS the word at
//         incoming-receiver + 0x13c. That is the chain, and it is the reason
//         the shape of 0x00b8dab0 below is not a guess: 0x00b8dab0 was read
//         live for this package and is
//         `8b 81 94 01 00 00 c3` = `MOV EAX,dword ptr [ECX + 0x194]` / `RET`.
//
//  7. The promoted sibling package `pkg-00b8dab0-field194-getter`
//     (src/reconstruction/pkg_00b8dab0_field194_getter/, promoted,
//     runtime GATED) is the reconstruction of that tail target, and its
//     metadata record is reconstruction/metadata/pkg-00b8dab0-field194-getter/
//     00b8dab0.json. Its mechanism is one 32-bit load at displacement 0x194
//     and one return. `field_194_getter_00b8dab0` below reproduces that
//     MECHANISM and is used as this package's tail target so that the
//     transferred receiver can be observed and asserted. It is a local model
//     of the target's mechanism, NOT a second reconstruction of 0x00b8dab0,
//     and it makes no claim about that package's internals beyond the seven
//     bytes read live in note 6. Its 0.198-byte extent is that package's
//     MODELLING BOUND and is used here for the same reason: so the word at
//     0x194 is addressable. It is not a recovered object size.
//
//  8. The committed xref export knowledgegraph/triage/xrefs-2540f2ca.tsv,
//     read whole for this VA: 41 `direct-call` edges INTO 0x00c70e00 from 32
//     distinct caller functions, and exactly ONE edge OUT, read verbatim:
//
//       00c70e00  00b8dab0  direct-call  00c70e0a
//
//     The out-edge's `callsite_va` is 0x00c70e0a - the JMP, not a CALL. The
//     export records a tail transfer as a `direct-call` edge, so the CALLS
//     check has an independent machine oracle for the callee, and this
//     package's source names the callee by suffixing its VA onto the symbol,
//     which is the repository's convention for making the two comparable.
//
//  9. knowledgegraph/triage/datarefs-2540f2ca.tsv contains ZERO rows for
//     0x00c70e00: the body records no data-segment reference. Consistent
//     with (8) - every recorded edge is direct-call - and with the derived
//     dispatch record of (3) at zero indirect calls and zero vtable-shaped
//     loads. This is a recorded absence, not an exhaustive proof that no
//     table exists.
//
// 10. RETURN SEMANTICS, AND WHAT MAY NOT BE CLAIMED ABOUT WIDTH. Two paths,
//     and each one writes all thirty-two bits of EAX:
//
//       * the tail path: EAX is written by 0x00b8dab0's own
//         `MOV EAX,dword ptr [ECX + 0x194]`, a 32-bit load into the full
//         32-bit register. Read live, that is the seven bytes of note 6.
//       * the null path: 0x00c70e0f is `b8 01 00 00 00`, which is
//         `MOV EAX,imm32` - the `b8+r` opcode, a full 32-bit immediate write,
//         not an 8-bit `MOV AL`. The immediate is 1.
//
//     So the claim is exactly this: on BOTH paths EAX receives a full dword,
//     and the register is the return register on both paths. The claim is NOT
//     that the value is 32 bits WIDE in a C sense - no evidence here names a
//     source-level type, the derived record's `return.type` is null, and
//     `sret` is an APPROXIMATION whose own `basis` warns that "entry slot 0 is
//     not written through a pointer" is weak. The claim is NOT signedness -
//     the null path's immediate is unsigned and the tail path copies bits,
//     and the ordered comparisons of note 5 are a property of the CALLERS.
//     What is also unclaimed: whether the two paths' values are meant to
//     occupy one type. The `MOV EAX,0x1` arm yields 1 and the tail arm yields
//     an arbitrary stored word, and nothing in the evidence says they are the
//     same quantity - the sampled callers only ever compare the result with
//     0x4 or 0x5, which is consistent with either. `std::uint32_t` is the
//     widest type both paths provably agree on.
//
// 11. THE DISPLACEMENT IS SPELLED AS A VALUE, NEVER AS A MEMBER. 0x13c is
//     what the body was observed reaching; it is not a field identity. The
//     derived receiver record says this in its own words - `bounds_only:
//     true` means "where the body was SEEN reaching", not a layout - and the
//     pack carries `categories.types: MISSING` and `categories.globals:
//     MISSING` and `categories.vtables: MISSING`. A name here would be a
//     field-identity assertion with nothing behind it, exactly as the promoted
//     sibling package declines to name its 0x194 word. This package names
//     neither the word at +0x13c nor the class of the receiver.
//
// 12. NOTE ON THE DERIVED RECORD'S `verdict: ABI_UNKNOWN`, RECORDED NOT
//     PAPERED OVER. The record abstains, and its `inferences` name the reason
//     as T2 with `confidence: UNKNOWN`: "the function can reach a caller by
//     transferring out of the listing, so the path that actually returns was
//     never observed". That is the tail call of note 6. The observation it
//     rests on is incomplete in a way this body makes obvious: the transfer at
//     0x00c70e0a does NOT leave the return path unobserved, because 0x00c70e0f
//     / 0x00c70e14 is a returning path in the same listing, and the transfer's
//     own target 0x00b8dab0 is a two-instruction body whose `MOV EAX` / `RET`
//     was read live (note 6). This is recorded as a property of the DERIVED
//     RECORD, not as a claim about the reconstruction, and nothing in this
//     package is relaxed to compensate for it: `kAbiVerdictAbstained` below
//     pins the value and the validator's ABI arm is left to adjudicate it.
//
// WHAT IS NOT CLAIMED
//  * Whether the receiver argument is a C++ `this` or an ordinary first
//    parameter - see note 4. The bytes do not discriminate __thiscall from
//    __fastcall, and no class is named for the receiver anywhere in the pack.
//  * Any name for the word at receiver+0x13c, or for the receiver's class.
//    See note 11.
//  * Any nullability, ownership, AddRef/Release, thread-safety or lifetime
//    contract for the receiver or for the value it holds.
//  * Any ordinary stack argument, any variadic behaviour (`variadic:
//    UNKNOWN` in the record), and any callee-side stack cleanup.
//  * Any second definition of 0x00b8dab0 - see note 7. The mechanism is
//    modelled locally so the transferred receiver is observable; the promoted
//    sibling remains the record of that address.
//  * Any runtime, Wine, trace, differential or OBSERVED-behaviour claim. No
//    runtime evidence exists for this VA.

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00c70e00 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_00C70E00_THISCALL __thiscall
#else
#define PKG_00C70E00_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c70e00_field13c {

// The unit both paths are proven to produce: a full 32-bit dword in EAX
// (note 10). Unsigned because the tail path copies bits and the only
// immediate write, at 0x00c70e0f, is an unsigned 32-bit constant; any ordered
// reading of the result belongs to the callers of note 5, not to this body.
using SlotWord = std::uint32_t;

// Receiver of 0x00c70e00, modelled at exactly the width the machine reaches
// and no more: 0x140 bytes, i.e. the prefix through the one word 0x00c70e00
// reads. No member is declared - see note 11. The extent is a MODELLING
// BOUND, not a recovered allocation size, and the derived record states no
// size either.
struct alignas(4) OpaqueReceiver {
  std::array<std::uint8_t, 0x140> opaque_bytes{};  // 0x00..0x13f
};

// Receiver of the TAIL TARGET 0x00b8dab0, a DIFFERENT object from the one
// above: 0x00c70e00 loads a pointer out of its own receiver and hands THAT to
// the tail target (note 6). Sized to 0x198 so the word the tail target reads
// at 0x194 is addressable, which is the same modelling bound the promoted
// sibling package uses and for the same reason (note 7). Declared as its own
// type precisely so the two receivers cannot be confused: a reconstruction
// that passed its own receiver straight through would not compile against
// this signature.
struct alignas(4) OpaqueTailReceiver {
  std::array<std::uint8_t, 0x198> opaque_bytes{};  // 0x00..0x197
};

// The displacement 0x00c70e00 was observed reaching on ITS OWN receiver,
// taken from the disp32 of `MOV ECX,dword ptr [ECX + 0x13c]`. It is a value,
// not a member: the receiver record enumerates displacements
// (`offsets: [316]`, `bounds_only: true`) and cannot say which member is
// which - see note 11.
constexpr std::size_t kFieldDisplacement = 0x13c;

// The width of the word 0x00c70e00 loads. Fixed by the `dword ptr` of the
// operand and by the ModRM/disp32 encoding: 6 bytes, 1 opcode + 1 ModRM +
// 4 disp32, so there is no room for anything narrower.
constexpr std::size_t kFieldWidth = sizeof(SlotWord);

// The displacement is in BYTES, not in 4-byte words. The word this body loads
// sits at word index 79 of its receiver; a model that mistook the disp32 for an
// element COUNT would address word 0x13c, i.e. byte 0x4f0, which is past the
// modelled extent entirely.
constexpr std::size_t kFieldIndexInWords = kFieldDisplacement / kFieldWidth;

// The immediate 0x00c70e0f writes: `b8 01 00 00 00` is MOV EAX,imm32 with
// imm32 = 1. Not a semantic truth and not a "true" value - it is the constant
// the listing carries on the false arm of the branch, and nothing here names
// what it means.
constexpr SlotWord kNullArmReturn = 1;

// The tail target's address, as the record spells it: `tail_call.target`,
// `callees[0].va`, and the one out-edge of the committed xref export (notes 6
// and 8).
constexpr std::uint32_t kTailTargetVa = 0x00b8dab0;

// The JZ at 0x00c70e08: 0x74 + rel8, and the rel8 is 5. That is not
// incidental: the instruction it skips is the five-byte JMP at 0x00c70e0a, so
// the false arm lands exactly on 0x00c70e0f and the whole tail transfer is
// what the guard decides about.
constexpr std::int8_t kJzDisplacement = 5;
constexpr std::size_t kJumpInstructionBytes = 5;

// The JMP at 0x00c70e0a: 0xe9 + rel32. The rel32 is stored here as the
// UNSIGNED 32-bit pattern, because that is the byte order the encoding array
// is checked against; `kJumpTargetVa` below is the address it computes.
constexpr std::uint32_t kJumpEncodedDisplacement = 0xfff1cca1u;

// 0x00c70e00..0x00c70e14 inclusive is twenty-one bytes: 6 (MOV with disp32) +
// 2 (TEST) + 2 (JZ rel8) + 5 (JMP rel32) + 5 (MOV EAX,imm32) + 1 (RET).
constexpr std::size_t kTargetBodyBytes = 21;

// The body's bytes exactly as read from 0x00c70e00 (note 1). Kept here so the
// encoding is a claim the model test can check rather than a claim in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0x8b,                          // 0x00c70e00  MOV r32, r/m32
    0x89,                          // 0x00c70e01  ModRM: mod=10 disp32,
                                  //             reg=001 (ECX), rm=001 (ECX)
    0x3c, 0x01, 0x00, 0x00,        // 0x00c70e02  disp32 = 0x0000013c
    0x85,                          // 0x00c70e06  TEST r/m32, r32
    0xc9,                          // 0x00c70e07  ModRM: reg=001 (ECX), rm=001 (ECX)
    0x74,                          // 0x00c70e08  JZ rel8
    0x05,                          // 0x00c70e09  rel8 = +5
    0xe9,                          // 0x00c70e0a  JMP rel32
    0xa1, 0xcc, 0xf1, 0xff,        // 0x00c70e0b  rel32 = 0xfff1cca1
    0xb8,                          // 0x00c70e0f  MOV r32, imm32 (MOV EAX,imm32)
    0x01, 0x00, 0x00, 0x00,        // 0x00c70e10  imm32 = 1
    0xc3,                          // 0x00c70e14  RET
};

// The byte at 0x00c70e15: INT3 padding, NOT part of the body. Named so the
// model's boundary can be checked against the image.
constexpr std::uint8_t kTargetPadByte = 0xcc;
constexpr std::size_t kTargetPadBytes = 3;

// The seven bytes of the tail target, read live at 0x00b8dab0 for this
// package (note 6): `8b 81 94 01 00 00 c3`. Carried here so the modelled
// transfer's shape is checked against the image and not merely asserted - this
// is what makes "0x00b8dab0 receives the loaded word as its receiver" a
// statement about bytes rather than about a name.
constexpr std::uint8_t kTailTargetEncoding[7] = {
    0x8b,                          // 0x00b8dab0  MOV r32, r/m32
    0x81,                          // 0x00b8dab1  ModRM: mod=10 disp32,
                                  //             reg=000 (EAX), rm=001 (ECX)
    0x94, 0x01, 0x00, 0x00,        // 0x00b8dab2  disp32 = 0x00000194
    0xc3,                          // 0x00b8dab6  RET
};

// The tail target's displacement, 0x194. It belongs to 0x00b8dab0's body, NOT
// to this one - the receiver record for 0x00c70e00 enumerates 0x13c only. See
// notes 6 and 7: this package models the target's mechanism, and this
// displacement is where that mechanism reads.
constexpr std::size_t kTailTargetDisplacement = 0x194;

// The direct-call edges the committed xref export records for this target:
// 41 into it from 32 distinct callers, and exactly 1 out of it, at callsite
// 0x00c70e0a (note 8). Recorded as counts, because no call site is
// transcribed here and the numbers are the part of (8) a claim could
// otherwise be checked on.
constexpr std::size_t kRecordedIncomingDirectCallEdges = 41;
constexpr std::size_t kRecordedDistinctCallers = 32;
constexpr std::size_t kRecordedOutgoingDirectCallEdges = 1;

// The callsite the one outgoing edge names. It is the JMP, which is why the
// export can see this callee at all.
constexpr std::uint32_t kTailTransferCallsite = 0x00c70e0a;

// The false arm's landing address, as the JZ operand spells it.
constexpr std::uint32_t kNullArmAddress = 0x00c70e0f;

// The record's own verdict, pinned so the abstention of note 12 is a
// compile-time fact of this package and not a claim that can be edited away.
constexpr const char* kAbiVerdictAbstained = "ABI_UNKNOWN";

// The receiver of 0x00c70e00, read by displacement. This is the ONLY way this
// package touches that receiver; naming a member instead would assert an
// identity no witness in the pack supports (note 11). The entry performs the
// same arithmetic inline, with the displacement written literally so the
// validator can see the declared offset in the target span; this accessor is
// the same operation in named form and the model test checks that the two
// agree rather than taking either on trust.
inline OpaqueTailReceiver* field_at(OpaqueReceiver* receiver,
                                    std::size_t displacement) {
  return reinterpret_cast<OpaqueTailReceiver*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// The tail target's receiver read by displacement - 0x00b8dab0's own single
// memory operand. Used by `field_194_getter_00b8dab0` and, through it, by the
// model test, so the word the transfer reads is reachable from one place.
inline SlotWord tail_field_at(const OpaqueTailReceiver* receiver,
                              std::size_t displacement) {
  return *reinterpret_cast<const SlotWord*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// x86-32 thiscall: one register argument in ECX, 0 ordinary stack arguments,
// the callee pops nothing (bare RET at 0x00c70e14) so the caller owns stack
// cleanup, and one 32-bit dword comes back in EAX.
using AbiTailTransfer00b8dab0 =
    SlotWord(PKG_00C70E00_THISCALL*)(OpaqueTailReceiver*);
using AbiField13c00c70e00 = SlotWord(PKG_00C70E00_THISCALL*)(OpaqueReceiver*);

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(SlotWord) == 4, "the word both paths produce is 32-bit");
static_assert(sizeof(OpaqueReceiver) == 0x140,
              "modelled receiver extent runs through the loaded word");
static_assert(sizeof(OpaqueTailReceiver) == 0x198,
              "modelled tail extent runs through the word 0x00b8dab0 reads");
static_assert(offsetof(OpaqueReceiver, opaque_bytes) == 0,
              "the receiver's first byte is its base");
static_assert(offsetof(OpaqueTailReceiver, opaque_bytes) == 0,
              "the tail receiver's first byte is its base");
static_assert(kFieldDisplacement + kFieldWidth == sizeof(OpaqueReceiver),
              "the only displacement this body reaches ends the modelled extent");
static_assert(kTailTargetDisplacement + sizeof(SlotWord) ==
                  sizeof(OpaqueTailReceiver),
              "the tail target's displacement ends ITS modelled extent");
static_assert(kFieldDisplacement == 0x13cu,
              "the displacement is 0x13c, compared semantically not by spelling");
static_assert(kFieldDisplacement == 316u, "0x13c is the value 316");
static_assert(kFieldDisplacement != kTailTargetDisplacement,
              "0x13c is this body's displacement and 0x194 is the tail's; they "
              "are different fields of different objects");
static_assert(kFieldIndexInWords == 79u,
              "0x13c is 79 four-byte words past the base");
static_assert((kFieldDisplacement * kFieldWidth) > sizeof(OpaqueReceiver),
              "reading the disp32 as an element count would address byte 0x4f0");
static_assert((kFieldDisplacement % kFieldWidth) == 0u,
              "the displacement is 4-byte aligned, as a dword read requires");

// The tail's displacement is 0x194, which is PAST this body's own receiver
// extent. That is the check that stops the two receivers from being merged:
// 0x194 > 0x140, so no object that is a valid OpaqueReceiver can be a valid
// OpaqueTailReceiver, and the tail cannot be modelled as reading further into
// the receiver this body was handed.
static_assert(kTailTargetDisplacement > sizeof(OpaqueReceiver),
              "the tail receiver is strictly larger than this body's receiver");

// The encoding IS the observed one, and its disp32 IS the header's
// displacement, so the two statements cannot drift apart.
static_assert(kTargetEncoding[0] == 0x8bu, "0x00c70e00 is MOV r32, r/m32");
static_assert(kTargetEncoding[0] != 0x8du,
              "0x8d is LEA; the observed opcode is 0x8b, a LOAD");
static_assert(kTargetEncoding[1] == 0x89u,
              "ModRM 0x89 is mod=10 (disp32) reg=001 (ECX) rm=001 (ECX)");
static_assert((kTargetEncoding[1] >> 6) == 2u, "mod=10 selects a disp32");
static_assert(((kTargetEncoding[1] >> 3) & 7u) == 1u, "reg=001 selects ECX");
static_assert((kTargetEncoding[1] & 7u) == 1u,
              "rm=001 selects ECX, so base and destination are the same "
              "register and the load is in place");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[2]) |
               (static_cast<std::uint32_t>(kTargetEncoding[3]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[4]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[5]) << 24)) ==
                  kFieldDisplacement,
              "the instruction's disp32 is the header's displacement");
static_assert(kTargetEncoding[6] == 0x85u,
              "0x00c70e06 is TEST r/m32, r32 - it writes EFLAGS only");
static_assert(kTargetEncoding[7] == 0xc9u,
              "TEST's ModRM is reg=ECX rm=ECX, so the FLAGS come from the "
              "LOADED word, not from the incoming receiver");
static_assert(kTargetEncoding[8] == 0x74u, "0x00c70e08 is JZ rel8");
static_assert(static_cast<std::int8_t>(kTargetEncoding[9]) == kJzDisplacement,
              "the JZ rel8 is the +5 the listing carries");
static_assert(static_cast<std::size_t>(kJzDisplacement) == kJumpInstructionBytes,
              "the JZ skips exactly the JMP, so its false arm is 0x00c70e0f "
              "and its true arm is the whole tail transfer");
static_assert(kTargetEncoding[10] == 0xe9u, "0x00c70e0a is JMP rel32");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[11]) |
               (static_cast<std::uint32_t>(kTargetEncoding[12]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[13]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[14]) << 24)) ==
                  kJumpEncodedDisplacement,
              "the JMP's rel32 is the encoded pattern the listing carries");
static_assert(kTargetEncoding[15] == 0xb8u,
              "0x00c70e0f is MOV r32,imm32 - opcode b8+r, NOT the 8-bit b0+r "
              "form that would leave the top of EAX undefined");
static_assert(kTargetEncoding[15] != 0xb0u,
              "b0 would be MOV AL,imm8 and the top three bytes of EAX would "
              "then be unproven");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[16]) |
               (static_cast<std::uint32_t>(kTargetEncoding[17]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[18]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[19]) << 24)) ==
                  kNullArmReturn,
              "the false arm's immediate is the constant the header declares");
static_assert(kTargetEncoding[20] == 0xc3u, "0x00c70e14 is a bare RET");
static_assert(kTargetEncoding[20] != 0xc2u,
              "RET 0xc2 would be RET imm16; 0xc3 pops nothing");
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the encoding array is exactly the modelled body length");
static_assert(kTargetBodyBytes == 6u + 2u + 2u + 5u + 5u + 1u,
              "the body is six instructions whose lengths sum to twenty-one");
static_assert(kTargetPadByte == 0xccu, "0x00c70e15 is INT3 pad, not body");
static_assert(kTargetPadBytes == 3u,
              "three pad bytes were read live after the body");

// The two addresses the branch and the jump name, computed from the ENCODED
// operands rather than restated, so a wrong rel32 or a wrong rel8 cannot pass.
constexpr std::uint32_t kJumpSiteAddress = 0x00c70e0a;
// The rel32 is a SIGNED displacement. `kJumpEncodedDisplacement` is the
// unsigned bit pattern as stored; flipping the sign bit and subtracting the sign
// bias is the sign extension, and the addition below wraps modulo 2^32 exactly
// as the hardware's EIP arithmetic does. For this target the stored pattern
// already has its sign bit set, so the sign extension is the identity in
// 32-bit unsigned arithmetic and the two constants compare equal - stated as a
// static_assert so the arithmetic below cannot be read as an unsigned add.
constexpr std::uint32_t kJumpSignedDisplacement =
    (kJumpEncodedDisplacement ^ 0x80000000u) - 0x80000000u;
static_assert(kJumpSignedDisplacement == kJumpEncodedDisplacement,
              "the stored rel32 has its sign bit set, so the sign extension is "
              "the identity and the displacement is a NEGATIVE backward jump");
constexpr std::uint32_t kComputedTailTarget =
    kJumpSiteAddress + static_cast<std::uint32_t>(kJumpInstructionBytes) +
    kJumpSignedDisplacement;
static_assert(kComputedTailTarget == kTailTargetVa,
              "0x00c70e0a + 5 + rel32 is 0x00b8dab0, the record's tail target "
              "and the one out-edge of the xref export");
constexpr std::uint32_t kJumpSiteEntry = 0x00c70e00;
constexpr std::uint32_t kComputedNullArm =
    kJumpSiteEntry + 8u + 2u + static_cast<std::uint32_t>(kJzDisplacement);
static_assert(kComputedNullArm == kNullArmAddress,
              "0x00c70e08 + 2 + 5 is 0x00c70e0f, where the listing's JZ lands "
              "and where MOV EAX,1 sits");
static_assert(kComputedNullArm + 5u + 1u ==
                  kJumpSiteEntry + kTargetBodyBytes,
              "the constant write and the RET are the last five bytes of the "
              "body, so the null arm is the only returning path in the span");

// The tail target's own encoding, and the chain of ECX it proves (note 6).
static_assert(kTailTargetEncoding[0] == 0x8bu,
              "0x00b8dab0 is MOV r32, r/m32");
static_assert(kTailTargetEncoding[1] == 0x81u,
              "ModRM 0x81 is mod=10 (disp32) reg=000 (EAX) rm=001 (ECX)");
static_assert((kTailTargetEncoding[1] >> 6) == 2u, "mod=10 selects a disp32");
static_assert(((kTailTargetEncoding[1] >> 3) & 7u) == 0u, "reg=000 selects EAX");
static_assert((kTailTargetEncoding[1] & 7u) == 1u,
              "rm=001 selects ECX, so the tail target reads through the "
              "register this body left holding the loaded word");
static_assert((static_cast<std::uint32_t>(kTailTargetEncoding[2]) |
               (static_cast<std::uint32_t>(kTailTargetEncoding[3]) << 8) |
               (static_cast<std::uint32_t>(kTailTargetEncoding[4]) << 16) |
               (static_cast<std::uint32_t>(kTailTargetEncoding[5]) << 24)) ==
                  kTailTargetDisplacement,
              "the tail target's disp32 is the displacement the header declares");
static_assert(kTailTargetEncoding[6] == 0xc3u, "0x00b8dab6 is a bare RET");
static_assert(kTailTargetEncoding[6] != 0xc2u,
              "the tail target pops nothing either, so it cannot be "
              "consuming a stack argument this body failed to pass");

static_assert(sizeof(AbiField13c00c70e00) == sizeof(void*),
              "the modelled entry is a plain code pointer");
static_assert(sizeof(AbiTailTransfer00b8dab0) == sizeof(void*),
              "the modelled tail target is a plain code pointer");
static_assert(std::is_same<AbiField13c00c70e00,
                           SlotWord(PKG_00C70E00_THISCALL*)(OpaqueReceiver*)>::value,
              "the modelled entry carries the ECX receiver and returns one word");
static_assert(std::is_same<AbiTailTransfer00b8dab0,
                           SlotWord(PKG_00C70E00_THISCALL*)(
                               OpaqueTailReceiver*)>::value,
              "the modelled tail target carries ITS receiver in ECX and "
              "returns one word");

// The tail target of the JMP at 0x00c70e0a: a LOCAL model of the mechanism of
// 0x00b8dab0, which was read live as `MOV EAX,[ECX + 0x194]` / `RET` (note 6).
// It is modelled separately, and with a distinct receiver type, so the model
// test can observe WHICH object the transfer handed over - see note 7.
SlotWord PKG_00C70E00_THISCALL field_194_getter_00b8dab0(
    OpaqueTailReceiver* receiver);

// Entry point under reconstruction. The name embeds the 8-hex target VA so
// the validator can bind this span to 0x00c70e00.
SlotWord PKG_00C70E00_THISCALL field13c_00c70e00(OpaqueReceiver* receiver);

}

#undef PKG_00C70E00_THISCALL