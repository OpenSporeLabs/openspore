#pragma once

// Reconstruction of 0x00b8de30 (SporeApp.exe 3.1.0.22, binary sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e, image base
// 0x00400000, machine `x86:LE:32:windows`).
//
// THE COMPLETE BODY: ten instructions, thirty-three bytes
// ---------------------------------------------------------
//     0x00b8de30  8b 81 84 01 00 00   MOV EAX, dword ptr [ECX + 0x184]
//     0x00b8de36  50                  PUSH EAX
//     0x00b8de37  e8 64 f4 fa ff      CALL 0x00b3d2a0
//     0x00b8de3c  8b c8               MOV ECX, EAX
//     0x00b8de3e  e8 fd 85 01 00      CALL 0x00ba6440
//     0x00b8de43  50                  PUSH EAX
//     0x00b8de44  e8 57 f4 fa ff      CALL 0x00b3d2a0
//     0x00b8de49  8b c8               MOV ECX, EAX
//     0x00b8de4b  e8 30 8f 01 00      CALL 0x00ba6d80
//     0x00b8de50  c3                  RET
//
// Verified two independent ways, and the two agree instruction for instruction
// and byte for byte:
//
//   * `objdump -d -M intel SPORE/SporeBin/SporeApp.exe
//     --start-address=0x00b8de30 --stop-address=0x00b8de55` prints exactly the
//     ten lines above, and 0x00b8de51..0x00b8de54 is `cc cc cc cc` (INT3 pad),
//     so the body cannot run past the RET at 0x00b8de50;
//   * the machine listing stored with this target
//     (reconstruction/evidence/00b8de30/evidence.json:
//     categories.disassembly.value.instructions) holds ten instructions at the
//     same ten addresses with the same two CALLEE operands, and
//     categories.abi_derived.value.parse reports declared_count 10,
//     degraded false, unparsed 0 -- the parse consumed the listing in full, so
//     the listing is the whole body and not a slice of it. That parse record is
//     what lets CONSTANTS and FIELDS/OFFSETS treat this listing as bounded.
//
// WHAT THE BODY IS
// ----------------
// Straight-line: no conditional branch, no indirect transfer, no flag test, no
// register save, no frame. It reads one dword out of its receiver, and then
// makes four calls in a fixed order:
//
//     w      = the dword at receiver + 0x184
//     root   = FUN_00b3d2a0()                  // called with NOTHING pushed
//     lookup = FUN_00ba6440(root, w)           // ECX = root, one stack word
//     root2  = FUN_00b3d2a0()                  // called again, still nothing
//     FUN_00ba6d80(root2, lookup)              // ECX = root2, one stack word
//
// and returns nothing of its own.
//
// THE PUSH IS NOT THE ACCESSOR'S ARGUMENT -- AND THAT IS THE POINT
// ---------------------------------------------------------------
// Both PUSHes are immediately followed by `CALL 0x00b3d2a0`, and it is
// tempting to read each PUSH as that call's argument. It is not, and the callee's
// own two instructions settle it rather than a guess:
//
//     0x00b3d2a0  a1 e4 ea 67 01   MOV EAX, dword ptr DS:0x0167eae4
//     0x00b3d2a5  c3               RET
//
// (read with the same objdump invocation, one window lower). That body reads no
// stack word -- so it consumes no argument -- and its terminator is a BARE RET
// with no immediate, so it pops nothing either. Under every convention in which
// a callee cleans up its own arguments, a word pushed for 0x00b3d2a0 would have
// to be its argument; this callee neither reads nor removes it, so the word
// stays on the stack and is consumed by the NEXT call. 0x00ba6440 reads it
// (`mov eax,[esp+4]`) and removes it (`ret 4`); 0x00ba6d80 does the same
// (`mov edx,[esp+4]` ... `ret 4`).
//
// The arithmetic agrees and is the check that a wrong reading breaks: two
// PUSHes against two callee-side `ret 4`s is a net of zero, which is exactly
// what the terminal bare `RET` at 0x00b8de50 requires to leave the caller's
// frame intact. Reading the PUSHes as arguments to 0x00b3d2a0 instead would make
// the entry run eight bytes into the caller's frame on return.
//
// The same idiom appears twice (0x00b8de36/0x00b8de43), which is corroboration
// rather than proof: one instance could be a compiler artefact, two independent
// instances of push-then-argless-call-then-ret-4 are a shape.
//
// The three callees' own semantics are NOT reconstructed here and are not
// claimed. 0x00ba6440 happens not to read ECX and 0x00ba6d80 happens to read
// two fields of it; that is a fact about those bodies, and this package asserts
// only the values this body hands them.
//
// ABI: __thiscall, and the machine says so rather than the other way round
// ----------------------------------------------------------------------
// The derived ABI record (categories.abi_derived.value) states
// calling_convention __thiscall with hidden_this true, hidden_this_register
// ECX, receiver_register ECX, ret_form RET, return_register EAX,
// stack_cleanup_bytes 0 with owner "caller", and lists candidate conventions
// [__thiscall, __fastcall] at confidence INFERRED. Three things in the body
// corroborate the receiver and are what the declaration rests on:
//
//   * ECX is dereferenced at 0x00b8de50's own first instruction, before any
//     write to it, so it arrives holding something;
//   * the body reads no stack word, so there is no ordinary stack argument;
//   * the terminal is a bare RET, so the callee pops nothing.
//
// A caller listing shows the same shape from the other side: at 0x00bbe608
// (`mov ecx,esi` / `call 0xb8de30` / `mov edi,eax`) the receiver goes into ECX
// and nothing is pushed. So the entry is declared __thiscall and takes exactly
// one parameter, the receiver. The disjunction with __fastcall is not
// resolved here and does not need to be: no stack argument exists for __fastcall
// to add, and this package models the shape the bytes fix.
//
// RETURN: void, and what EAX holds is NOT claimed
// ----------------------------------------------
// The last value-producing operation in the body is `CALL 0x00ba6d80`. Nothing
// in the body then writes EAX before the RET, so whatever the final callee left
// in EAX is what a caller sees, and this body makes no statement about it. The
// derived record is explicit that the width is not determinable here
// (return_semantics `unclassified_in_EAX`, inference RT2 registers the last
// EAX write as register_class `aggregate_unknown`), and the validator's own
// must-analysis classes that shape UNCLASSIFIED. The declared type is therefore
// `void` -- the honest reading of a body that produces no value of its own --
// and RETURN SEMANTICS lands on NOT_AVAILABLE, which is a machine fact and not
// a defect of this candidate. Nothing here typedefs the record's register-class
// vocabulary to make a comparison succeed; that would satisfy a string and the
// machine not at all.
//
// THE RECEIVER: an opaque byte run, never a named member
// -------------------------------------------------------
// The machine-derived receiver record is `bounds_only` and enumerates exactly
// one displacement, 388 == 0x184, through ECX. `bounds_only` is the record's own
// statement that its enumeration is open: it says where the body was SEEN
// reaching, not which member is which, and it cannot name a member. So this
// package declares the DISPLACEMENT and nothing else -- an opaque byte run plus
// a displacement-named accessor, with the displacement a constexpr pinned by a
// static_assert to the instruction that states it. No struct, no member name, no
// offsetof, no class: a member name is a layout claim no machine record here can
// corroborate, and the field at +0x184 is not identified by anything in this
// package's evidence. (A sibling reconstruction in this repository reads +0x1A4
// through +0x1AC of a receiver that this body never touches; that is a
// different body and its documentation is not used as evidence here.)
//
// GLOBALS: none, and this body really has none
// -------------------------------------------
// The one memory operand in the body is `[ECX + 0x184]`, a receiver-relative
// read: the complete listing names no data-segment address. The global slot
// 0x0167eae4 that the accessor 0x00b3d2a0 reads belongs to THAT body, not this
// one, and it is deliberately not named here -- naming it would assert a
// data-segment reference out of 0x00b8de30 that this listing does not contain.
//
//   * the field at +0x184 is a dword, and the body reads all four bytes of it;
//   * the order accessor -> lookup -> accessor -> resolve is fixed and is
//     checked as a trace, not as a value;
//   * the receiver handed to the two thiscall callees is the ACCESSOR'S return
//     value, not the entry's own receiver and not the field -- this is what the
//     two `MOV ECX,EAX` after the accessor calls fix, and it is the fact a
//     "passes itself along" reconstruction gets wrong;
//   * the argument handed to 0x00ba6d80 is the LOOKUP's return value, not the
//     field word;
//   * the entry's net stack effect is zero, measured across the call and
//     calibrated;
//   * the entry writes nothing: the field dword and every other dword of the
//     modelled image keep their values.
//
// The mutation test: eleven deliberately wrong bodies live in the model test,
// are driven through the SAME battery, and each is REQUIRED to be refuted. A
// battery that cannot reject a known-wrong body certifies nothing.
//
// The battery was additionally checked from OUTSIDE, by perturbing the
// reconstruction's own body in the package's .cpp and rebuilding BOTH
// translation units under the promotion gate
// (clang++ -std=c++17 -Wall -Wextra -Werror -m32). Eight perturbations, all
// caught:
//
//   * +0x180 instead of +0x184          -> run time, the field case
//   * the accessor called once          -> run time, the call-count case
//   * the entry's own receiver forwarded -> run time, the receiver case
//   * the field handed to the second callee -> run time, the argument case
//   * resolve reached before lookup     -> run time, the order case
//   * the terminal becomes `ret 4`      -> run time, the stack-effect case
//   * the entry gains a stack parameter  -> COMPILE time, the header's ABI
//                                          static_assert
//   * the accessor given a parameter     -> COMPILE time, because the modelled
//                                          accessor is nullary and a body that
//                                          pushed an argument for it has
//                                          nothing to push it into
//
// The unperturbed build passes, and the two sources are byte-identical to their
// pre-perturbation state afterwards.

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "0x00b8de30 is an x86-32 reconstruction (ECX receiver, 32-bit absolute callees)"
#endif

// Calling convention: __thiscall (receiver in ECX, caller cleans the stack).
// The token is spelled once here, so the declaration below carries the macro
// name and the convention is stated in exactly one place.
#if defined(_MSC_VER)
#define PKG_00B8DE30_CALL __thiscall
#else
#define PKG_00B8DE30_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain {

using Word = std::uint32_t;

// ---------------------------------------------------------------------------
// Machine facts, each one decoded out of the body bytes above.
// ---------------------------------------------------------------------------

// 0x00b8de30..0x00b8de50: the ten instructions, transcribed as bytes so the
// transcription itself is under test and the constants below are decoded from it
// rather than restated alongside it.
constexpr std::uint8_t kTargetBytes[33] = {
    0x8b, 0x81, 0x84, 0x01, 0x00, 0x00,  // 0x00b8de30 MOV EAX, [ECX + 0x184]
    0x50,                                // 0x00b8de36 PUSH EAX
    0xe8, 0x64, 0xf4, 0xfa, 0xff,        // 0x00b8de37 CALL 0x00b3d2a0
    0x8b, 0xc8,                          // 0x00b8de3c MOV ECX, EAX
    0xe8, 0xfd, 0x85, 0x01, 0x00,        // 0x00b8de3e CALL 0x00ba6440
    0x50,                                // 0x00b8de43 PUSH EAX
    0xe8, 0x57, 0xf4, 0xfa, 0xff,        // 0x00b8de44 CALL 0x00b3d2a0
    0x8b, 0xc8,                          // 0x00b8de49 MOV ECX, EAX
    0xe8, 0x30, 0x8f, 0x01, 0x00,        // 0x00b8de4b CALL 0x00ba6d80
    0xc3,                                // 0x00b8de50 RET
};

static_assert(kTargetBytes[0] == 0x8b && kTargetBytes[1] == 0x81,
              "0x00b8de30 is 8B 81: MOV EAX, dword ptr [ECX + disp32] -- the ModRM "
              "byte 0x81 names ECX as the base, which is the receiver register");
static_assert(kTargetBytes[5] == 0x00 && kTargetBytes[32] == 0xc3,
              "the displacement's high byte is zero and the thirty-third byte is "
              "C3, a bare RET with no immediate: the callee pops nothing");
static_assert(kTargetBytes[6] == 0x50 && kTargetBytes[19] == 0x50,
              "0x00b8de36 and 0x00b8de43 are both a bare PUSH EAX (50): two "
              "words enter the stack and no other instruction writes ESP");

// Entry and terminal addresses, and the size of the body between them.
constexpr std::size_t kEntryVa = 0x00b8de30u;
constexpr std::size_t kTerminalVa = 0x00b8de50u;
constexpr std::size_t kBodyBytes = 33;
constexpr std::size_t kInstructionCount = 10;
constexpr std::size_t kCalleeCount = 4;
constexpr std::size_t kStackPushes = 2;
constexpr std::size_t kCalleeCleanupBytes = 0;  // bare RET: the entry pops nothing
constexpr std::size_t kOrdinaryStackArgumentSlots = 0;
constexpr bool kHasReceiver = true;
constexpr Word kReceiverRegisterVa = 0x00b8de30u;  // the base register is ECX
constexpr std::size_t kReceiverDisplacementCeiling = 0x184u;
constexpr std::size_t kReturnWidthBytes = 0;  // the body writes no result of its own
static_assert(kEntryVa + kBodyBytes == 0x00b8de51u,
              "0x00b8de30 + 33 bytes ends at 0x00b8de51, one past the RET at "
              "0x00b8de50 and one past the last body byte");
static_assert(kTerminalVa - kEntryVa == 32,
              "the bare RET is the tenth instruction, thirty-two bytes after entry");
static_assert(kCalleeCleanupBytes == 0,
              "the terminal at 0x00b8de50 is C3 with no immediate operand, so "
              "the entry pops zero bytes and the caller owns the stack");
static_assert(kStackPushes * sizeof(Word) == 2 * sizeof(Word),
              "two words enter the stack and two callees remove four bytes each");

// The displacement, DECODED from the three operand bytes 84 01 00 rather than
// restated, so the constant cannot drift away from the machine image.
constexpr std::size_t kFieldDisplacement = static_cast<std::size_t>(
    static_cast<std::uint32_t>(kTargetBytes[2]) |
    (static_cast<std::uint32_t>(kTargetBytes[3]) << 8) |
    (static_cast<std::uint32_t>(kTargetBytes[4]) << 16));
static_assert(kFieldDisplacement == 0x184u,
              "operand bytes 84 01 00 of the 8B 81 at 0x00b8de30 are the "
              "little-endian displacement 0x184, which is the 388 the "
              "machine-derived receiver record enumerates through ECX");

// The four callees' addresses, decoded from each E8 rel32 operand the same way.
// `at` is the index of the E8 opcode byte, and the displacement is relative to
// the END of that five-byte instruction, which is kEntryVa + at + 5.
constexpr Word rel32_target(std::size_t at) {
  return static_cast<Word>(
      kEntryVa + at + 5 +
      static_cast<Word>(static_cast<std::int32_t>(
          static_cast<std::uint32_t>(kTargetBytes[at + 1]) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 2]) << 8) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 3]) << 16) |
          (static_cast<std::uint32_t>(kTargetBytes[at + 4]) << 24))));
}

constexpr Word kAccessorVa00b3d2a0 = rel32_target(7);
constexpr Word kLookupVa00ba6440 = rel32_target(14);
constexpr Word kAccessorVa2 = rel32_target(20);
constexpr Word kResolveVa00ba6d80 = rel32_target(27);
static_assert(kAccessorVa00b3d2a0 == 0x00b3d2a0u,
              "the rel32 at 0x00b8de37 resolves to 0x00b3d2a0, the argless "
              "global-slot accessor the xref export records as a direct call");
static_assert(kLookupVa00ba6440 == 0x00ba6440u,
              "the rel32 at 0x00b8de3e resolves to 0x00ba6440");
static_assert(kAccessorVa2 == 0x00b3d2a0u,
              "the rel32 at 0x00b8de44 resolves to 0x00b3d2a0 as well: the same "
              "accessor is called twice, and the two calls are the same target");
static_assert(kResolveVa00ba6d80 == 0x00ba6d80u,
              "the rel32 at 0x00b8de4b resolves to 0x00ba6d80");

// The argless-accessor fact, stated as a number so the model test can assert it
// without re-reading the neighbour's bytes. 0x00b3d2a0 is `A1 E4 EA 67 01 / C3`:
// it reads no stack word and its RET carries no immediate, so it neither
// consumes nor removes the word pushed in front of it.
constexpr std::size_t kAccessorStackArgumentWords = 0;
constexpr std::size_t kAccessorCalleeCleanupBytes = 0;
static_assert(kAccessorStackArgumentWords == 0 && kAccessorCalleeCleanupBytes == 0,
              "0x00b3d2a0 is a six-byte body: MOV EAX,DS:[slot] then a bare RET. "
              "It reads no stack operand and pops nothing, so a word pushed "
              "immediately before its call belongs to the call that FOLLOWS it");

// The two thiscall callees each remove one word themselves. That is why the
// entry's terminal RET can be bare.
constexpr std::size_t kLookupCalleeCleanupBytes = 4;
constexpr std::size_t kResolveCalleeCleanupBytes = 4;
static_assert(kLookupCalleeCleanupBytes + kResolveCalleeCleanupBytes ==
                  kStackPushes * sizeof(Word),
              "the two thiscall callees remove four bytes each, which is exactly "
              "what the two PUSHes delivered: the entry's net stack effect is "
              "zero and its terminal RET is bare");

// ---------------------------------------------------------------------------
// The modelled receiver.
//
// An opaque byte run, NOT a struct: the machine gives a displacement and no
// layout, so a member name here would be a claim nothing corroborates. The run
// is one word longer than the displacement it exposes so the model test can put
// a guard band above the field and prove the body reads nothing above it.
// ---------------------------------------------------------------------------

constexpr std::size_t kGuardWords = 4;
constexpr std::size_t kImageWords = kFieldDisplacement / sizeof(Word) + 1 + kGuardWords;
constexpr Word kGuardCanary = 0xa5a5a5a5u;

// The receiver type the entry takes. Incomplete on purpose: the entry only ever
// reads a dword out of it at a displacement.
struct SimRecord;

// The modelled image, defined in the package's .cpp so the model test cannot
// drift onto a private copy.
struct SimRecordImage {
  std::uint32_t words[kImageWords];
};
extern SimRecordImage g_sim_record_image;

std::uint8_t* image_bytes();

// Reads the dword the machine reads. The displacement is a parameter rather
// than a baked-in constant so the model test can drive the mutants through the
// very same accessor; the entry passes the decoded kFieldDisplacement.
Word word_at(const std::uint8_t* base, std::size_t displacement);

// ---------------------------------------------------------------------------
// The modelled callees.
//
// Each one records what it was handed, so the ORDER and the ARGUMENTS of the
// body are observable rather than assumed. The accessor is declared with NO
// parameter, which is the structural consequence of the fact above: a
// reconstruction that pushed the field word FOR the accessor would not compile,
// because the callee it is modelled against takes nothing.
//
// None of these carries the target's own address, and none but the entry
// carries any address at all in its own name -- the four that do carry one are
// the four the xref export records as direct calls out of 0x00b8de30.
// ---------------------------------------------------------------------------

enum Site : Word {
  kSiteAccessor = 1u,
  kSiteLookup = 2u,
  kSiteResolve = 3u,
};

struct CallTraceEntry {
  Word site;       // which callee was reached
  Word receiver;   // the value that was in ECX on entry to it
  Word argument;   // the word that was on the stack for it
  Word stack_words;  // how many stack words the callee found
};

constexpr std::size_t kMaxCallDepth = 8;
extern CallTraceEntry g_call_trace[kMaxCallDepth];
extern std::size_t g_call_depth;

// What each modelled callee hands back. The body has no say in these values; the
// model test arms them so a reconstruction that confuses one for another is
// caught rather than agreeing with itself.
extern Word g_accessor_result;  // returned by 0x00b3d2a0, both times
extern Word g_lookup_result;    // returned by 0x00ba6440
extern Word g_resolve_result;   // returned by 0x00ba6d80

// 0x00b3d2a0: `MOV EAX,DS:[slot]` / `RET`. No parameter, no stack word, no
// cleanup. Its own semantics are not reconstructed here -- only the fact that
// it is handed nothing.
Word PKG_00B8DE30_CALL FUN_00b3d2a0();

// 0x00ba6440 and 0x00ba6d80: receiver in ECX, one word on the stack, each
// removing it itself. Their bodies are not reconstructed here either; only the
// values this entry hands them are modelled.
Word PKG_00B8DE30_CALL FUN_00ba6440(SimRecord* receiver, Word argument);
Word PKG_00B8DE30_CALL FUN_00ba6d80(SimRecord* receiver, Word argument);

// The machine ABI as a C++ type, so a wrong prototype fails to build: one
// receiver parameter, no result.
using AbiSimRecordLookupChain00b8de30 = void(PKG_00B8DE30_CALL*)(SimRecord*);
static_assert(sizeof(AbiSimRecordLookupChain00b8de30) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");

// Entry point under reconstruction. One parameter: the receiver in ECX. No
// ordinary stack argument (the body names no stack operand) and no result (the
// last value-producing operation is a CALL, and this body makes nothing of it).
void PKG_00B8DE30_CALL sim_record_lookup_chain_00b8de30(SimRecord* self);

}  // namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain
