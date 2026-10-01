#pragma once

// Reconstruction of FUN_00d38840 @ 0x00d38840 (SporeApp.exe 3.1.0.22,
// image_base 0x00400000, snapshot 2540f2ca).
//
// EVIDENCE BASIS. Every claim below traces to exactly one of these; nothing
// else is claimed.
//
//  1. Live Ghidra listing of the body - exactly two instructions, complete
//     (2 of 2 parsed, 0 unparsed, `body_status` complete):
//        0x00d38840  a1 94 e2 69 01   MOV EAX,dword ptr [0x0169e294]
//        0x00d38845  c3               RET
//     Raw bytes re-read live at 0x00d38840 (10 bytes):
//        a1 94 e2 69 01 c3 cc cc cc cc
//     The body is therefore 6 bytes, 0x00d38840..0x00d38845, matching
//     `body_start`/`body_end` and `body_span_bytes: 6` in the pack. The four
//     0xcc bytes that follow are INT3 padding between this entry and the next
//     and are NOT part of the body.
//
//  2. The operand is an ABSOLUTE 32-bit address, 0x0169e294, in the `moffs32`
//     form that opcode 0xa1 uses. There is no ModRM byte and no base register
//     at all in this instruction - which is why the ABI record's receiver is
//     absent (`receiver.present: false`, `distinct_offsets: 0`, `register:
//     null`). The access is to a fixed global, not through ECX or any pointer.
//
//  3. Live Ghidra decompilation, consistent with (1) and adding no new claim:
//        undefined4 FUN_00d38840(void) { return App__sCreatureModeStrategy; }
//
//  4. That global is NAMED in the program database. `list_globals` with the
//     substring `CreatureModeStrategy` returns exactly one hit:
//        App::sCreatureModeStrategy @ 0169e294 [Label] (undefined4) xrefs=55
//     So the symbol name below is not invented: it is the Ghidra label for the
//     one address the body names. The label's C++ scope (`App::`) is carried
//     through into the namespace below for the same reason.
//
//  5. THE WRITER IS A CONSTRUCTOR THAT PUBLISHES ITS OWN `THIS` - the witness
//     that makes the returned word an OBJECT POINTER rather than a scalar or a
//     count. `get_function_by_address` puts 0x00d3b9b0 at
//     0x00d3b9b0..0x00d3bab8, and that function decompiles live to a
//     constructor-shaped body: it writes four vtable-ish pointers into the
//     object (`*param_1 = &PTR_FUN_0147ac70` and three more at +4/+8/+0xc),
//     zeroes a long run of fields, then ends with
//        App__sCreatureModeStrategy = param_1;
//        return param_1;
//     Its single store to the global is at 0x00d3baae, read live as
//        0x00d3baae  89 35 94 e2 69 01   MOV dword ptr [0x0169e294], ESI
//        0x00d3bab4  8b c6               MOV EAX,ESI
//        0x00d3bab6  5e                  POP ESI
//        0x00d3bab7  5b                  POP EBX
//        0x00d3bab8  c3                  RET
//     ESI holds `param_1`, the object being constructed. So the global is
//     published as a pointer to a freshly built object, and the value this
//     target hands back is that pointer. See note 8 for why the declared type
//     is still the weaker `void*`.
//
//  6. THE CALLERS USE THE RESULT AS AN ADDRESS, in three independent ways.
//     (a) One caller makes the result the RECEIVER of a member call.
//     `disassemble_function @ 0x00d4c5e0` shows, twice in the same body:
//        0x00d4c624  CALL 0x00d38840
//        0x00d4c629  MOV ECX,EAX            <- result becomes `this`
//        0x00d4c62b  CALL 0x00d39360        <- App::cCreatureModeStrategy::ExecuteAction
//        ...
//        0x00d4c635  CALL 0x00d38840
//        0x00d4c63a  MOV ECX,EAX            <- result becomes `this` again
//        0x00d4c63c  CALL 0x00d3cdc0
//     and 0x00d39360 decompiles with the signature
//        App__cCreatureModeStrategy__ExecuteAction(cCreatureModeStrategy *this, ...)
//     so ECX is that method's `this` parameter.
//     (b) A reader loads THROUGH the global and mutates a field at a positive
//     displacement: at 0x00d395a4, `MOV EAX,[0x0169e294]` is followed by
//     `DEC dword ptr [EAX + 0x24]` / `INC dword ptr [EAX + 0x24]`, and the
//     same function's decompilation spells it
//     `*(int *)(App__sCreatureModeStrategy + 0x24) = ... + 1`. An indexed
//     access through the loaded word is pointer use and nothing else.
//     (c) A third reader takes a field at displacement 0xdc
//     (`*(char *)(App__sCreatureModeStrategy + 0xdc) = ...`, function
//     0x00d2b6e0) and another at 0xb4 (function 0x00d2c280). Both are indexed
//     accesses, not value arithmetic.
//
//  7. THE COMMITTED SIDECARS AGREE WITH THE LIVE DATABASE ON SHAPE.
//     knowledgegraph/triage/xrefs-2540f2ca.tsv records 59 `direct-call` edges
//     into 0x00d38840 from 39 distinct caller functions, 0 edges out of it,
//     and no other reference type. knowledgegraph/triage/datarefs-2540f2ca.tsv
//     records exactly ONE row with 0x00d38840 as referencer - the read of
//     0x0169e294 at callsite 0x00d38840, access mode `read`, segment
//     `.data -wr` - and ZERO rows with 0x00d38840 as target. A function that
//     were reached through a vtable would appear as the target of a data
//     reference from its own table; on this pinned snapshot there is none.
//     (That is a recorded absence, not an exhaustive proof that no table
//     exists.) For the global itself the same file records 47 `read` rows and
//     exactly ONE `write` row - the 0x00d3baae store of note 5 - so the
//     single-writer claim is measured, not assumed.
//
//  8. WHY `void*` AND NOT `cCreatureModeStrategy*`. The evidence in (5) and
//     (6a) is good enough to say the returned word is an object pointer and
//     that at least one callee types it `cCreatureModeStrategy *`. It is NOT
//     enough to assert the pointee's identity from THIS body, for two
//     recorded reasons. First, note (4) gives the GLOBAL's name as
//     `App::sCreatureModeStrategy` while the callee at 0x00d39360 names a TYPE
//     `App::cCreatureModeStrategy`; the pack has no RTTI in this binary (the
//     pack's own `evidence_note` says so) so the relationship between that
//     global's static and that class is an SDK-naming coincidence, not a
//     machine fact. Second, the derived ABI record's `register_class:
//     pointer_like` is `confidence: INFERRED` with `corroboration:
//     not_available`. So the declared return type is `void*` - the weakest C
//     type that states the observed use - and the class identity travels in
//     this comment and in the metadata instead. The declared type is spelled
//     `void*` with no space so the validator's declaration regex binds the
//     span; the machine width (4 bytes) and `void*` (4 bytes on x86-32)
//     agree.
//
//  9. THE DERIVED ABI RECORD, restated. x86-32; NO receiver (nothing in the
//     body is relative to a register, and `receiver.bounds_only: true` with an
//     empty offset list); 0 ordinary stack arguments - the body names no
//     memory operand relative to ESP; bare RET with no imm16, so the callee
//     pops nothing and stack cleanup is 0 bytes owned by the CALLER; the
//     returned value travels in EAX; 0 indirect calls and 0 vtable-shaped loads.
//     The convention therefore cannot be distinguished between __cdecl and
//     __thiscall on this body alone - the record lists all four as candidates
//     and abstains for want of a discriminator. This package declares the
//     entry with NO convention macro at all and types the slot as a plain
//     namespace-scope object, which is what a global accessor is; the ABI
//     typedef below spells it `void* (*)()` with no parameters.
//
// WHAT IS NOT CLAIMED
//  * The identity or layout of the pointee. Nothing here names the class of
//    the object the global points at, and no offset inside it is modelled.
//    The displacements 0x24, 0xb4 and 0xdc in note (6) are recorded as facts
//    about OTHER functions' reach, and they are explicitly NOT used to size
//    anything here.
//  * That the slot is initialised, that it is non-null on any particular call,
//    or that this entry returns a usable object. The body has no branch, no
//    test and no default, so a stored null comes back as a stored null. The
//    .data bytes at 0x0169e294 read live as all zero in the uninitialised
//    image; that says nothing about the running process, which is what the
//    constructor of note (5) exists to publish into it.
//  * That FUN_00d3b9b0 is the ONLY writer in the whole program. The sidecar
//    records one write row on the pinned snapshot (note 7); the live database
//    also reports one write xref. Neither is a proof about unanalysed code.
//  * That the global is immutable after construction, that it is a singleton
//    in any design sense, or that it is thread-safe. "Singleton" appears only
//    in this package's directory slug, as a description of the observed
//    one-writer shape - no synchronisation of any kind is claimed, and the
//    body has no room for a reference call.
//  * Any calling convention beyond the parameterless one the body is
//    compatible with, and any ordinary stack argument.
//  * Any runtime, Wine, trace or differential claim. No runtime evidence
//    exists for this VA: the runtime axis is GATED and unattempted.
//
// A NOTE ON THE TWO SIDE FILES. The single 0xcc that terminates the raw read
// and the four 0xcc bytes after it are the same INT3 padding run; only the
// first is named below, because only the first abuts the body. Neither is
// modelled as body, and the model test checks that the encoding array is
// exactly the six body bytes.

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "FUN_00d38840 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00d38840_global_singleton_getter {

// The unit the body moves: one 32-bit word in, one 32-bit word out. Note this
// alias is NOT the declared return type - the return is spelled `void*` so its
// width is computable from the declaration alone.
using SlotWord = std::uint32_t;

// THE SLOT. This is the model's stand-in for the four bytes of `.data` at
// 0x0169e294 that the body names. It is a plain namespace-scope object rather
// than a field of anything: opcode 0xa1 has no base register, so there is no
// receiver to hang it off, and modelling it as a member would invent one.
//
// It is declared `extern` and defined in the .cpp so that the model test can
// plant and read it without going through the entry - which is what lets the
// test distinguish "the entry returned what is stored" from "the entry wrote
// something first". Note the limit of that arrangement: nothing in the model
// can observe a write that leaves the value unchanged, so the machine-level
// statement "this body does not write the slot" is carried by the opcode
// (0xa1 load / 0xa3 store) rather than by the test's sentinels.
extern SlotWord g_creature_mode_strategy_slot;

// The address the body names, as a VALUE. It is never dereferenced by this
// package - the model cannot mmap the original image - but it is pinned here so
// the reconstruction's central constant is a checkable claim rather than prose,
// and so the encoding bytes of note (1) and this number cannot drift apart.
constexpr std::uint32_t kSlotAddress = 0x0169e294u;

// The width of the word the body moves, and the width of the pointer it
// becomes. These are equal on x86-32, and the model test measures that they
// are.
constexpr std::size_t kSlotWidth = sizeof(SlotWord);

// 0x00d38840..0x00d38845 is six bytes; the 0xcc that follows is INT3 pad
// between this entry and the next and is deliberately not modelled.
constexpr std::size_t kTargetBodyBytes = 6;

// The body's bytes as read from 0x00d38840. Kept in the header so the encoding
// is a claim the model test can check, not a claim only in prose.
constexpr std::uint8_t kTargetEncoding[kTargetBodyBytes] = {
    0xa1,                          // MOV EAX, moffs32 (absolute, no ModRM)
    0x94, 0xe2, 0x69, 0x01,        // moffs32 = 0x0169e294, little endian
    0xc3,                          // RET
};

// The byte at 0x00d38846: INT3 padding, NOT part of the body. Named so the
// model's boundary can be checked against the image.
constexpr std::uint8_t kTargetPadByte = 0xcc;

// The access mode the body makes on the slot, as the committed data-reference
// sidecar records it (note 7): a READ. The body never stores to the slot.
constexpr char kSlotAccessMode = 'r';

// The direct-call edges recorded for this target, from the committed sidecar
// (note 7), and the number of distinct caller functions among them. Recorded
// as counts, because no call site is transcribed here and the counts are the
// part of (7) that a claim could otherwise be checked on.
constexpr std::size_t kRecordedDirectCallEdges = 59;
constexpr std::size_t kRecordedDistinctCallers = 39;
constexpr std::size_t kRecordedOutgoingEdges = 0;

// Data-reference rows recorded for the slot on the pinned snapshot, split by
// access mode (note 7). The single write row is the constructor store of note
// (5); its callsite is named so the test can state that this body is the READ
// and not the write.
constexpr std::size_t kSlotRecordedReadRows = 47;
constexpr std::size_t kSlotRecordedWriteRows = 1;
constexpr std::uint32_t kSlotWriterCallsite = 0x00d3baaeu;
constexpr std::uint32_t kBodyReadCallsite = 0x00d38840u;

// Displacements OTHER functions reach through the slot, recorded as facts about
// THOSE functions' reach and deliberately NOT used to size or type anything in
// this package. (6b) refcounts at +0x24, (6c) a byte at +0xdc and a word at
// +0xb4.
constexpr std::size_t kSampledReaderFieldDisplacement = 0x24;
constexpr std::size_t kSampledByteFieldDisplacement = 0xdc;
constexpr std::size_t kSampledWordFieldDisplacement = 0xb4;

// The call site of the sibling READ that the body shape most resembles: the
// reader at 0x00d395a4 loads the same absolute address inline and then indexes
// through it, rather than calling this entry. Recorded to make the point that
// this accessor and the inline readers are two spellings of one load.
constexpr std::uint32_t kInlineReaderCallsite = 0x00d395a4u;

// The addresses of the two CALL instructions in the sampled caller of note
// (6a), and the member call each result feeds. Recorded because they are what
// makes the result a RECEIVER rather than a value.
constexpr std::uint32_t kSampledCallerFirstCallsite = 0x00d4c624u;
constexpr std::uint32_t kSampledCallerSecondCallsite = 0x00d4c635u;
constexpr std::uint32_t kSampledCalleeExecuteAction = 0x00d39360u;
constexpr std::uint32_t kSampledCalleeSecond = 0x00d3cdc0u;

// Parameterless entry, pointer in EAX, callee pops nothing. Spelled without a
// convention macro (note 9): the body is byte-identical under every candidate
// convention, so the reconstruction does not pick one.
using AbiGlobalSlotGetter00d38840 = void* (*)();

static_assert(sizeof(void*) == 4, "x86-32 target pointers are 32-bit");
static_assert(sizeof(SlotWord) == 4, "the moved word is 32-bit");
static_assert(sizeof(void*) == kSlotWidth,
              "the loaded word and the returned pointer are the same width here");
static_assert(kSlotAddress == 0x0169e294u,
              "the slot address is 0x0169e294, compared as a value not a "
              "spelling");
static_assert(kSlotAddress == 23716500u, "0x0169e294 is the value 23716500");
static_assert((kSlotAddress % kSlotWidth) == 0u,
              "the slot address is 4-byte aligned, as a dword load requires");

static_assert(kTargetEncoding[0] == 0xa1u,
              "0x00d38840 is MOV EAX, moffs32");
static_assert(kTargetEncoding[0] != 0x8bu,
              "0x8b is the register-relative MOV r32,r/m32 form; the observed "
              "opcode takes an absolute address and has no base register");
static_assert(kTargetEncoding[0] != 0xa3u,
              "0xa3 is MOV moffs32, EAX - a STORE; the observed opcode 0xa1 "
              "is the load direction");
static_assert((static_cast<std::uint32_t>(kTargetEncoding[1]) |
               (static_cast<std::uint32_t>(kTargetEncoding[2]) << 8) |
               (static_cast<std::uint32_t>(kTargetEncoding[3]) << 16) |
               (static_cast<std::uint32_t>(kTargetEncoding[4]) << 24)) ==
                  kSlotAddress,
              "the instruction's moffs32 IS the header's slot address");
static_assert(kTargetEncoding[5] == 0xc3u, "0x00d38845 is a bare RET");
static_assert(kTargetEncoding[5] != 0xc2u,
              "RET 0xc2 would be RET imm16; 0xc3 pops nothing");
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the encoding array is exactly the modelled body length");
static_assert(kTargetBodyBytes == 1u + 4u + 1u,
              "the body is one opcode, one moffs32 and one RET");
static_assert(kTargetPadByte == 0xccu, "0x00d38846 is INT3 pad, not body");

static_assert(kRecordedOutgoingEdges == 0u,
              "the sidecar records no edge out of this target");
static_assert(kRecordedDistinctCallers <= kRecordedDirectCallEdges,
              "distinct callers cannot exceed the edges that make them");
static_assert(kRecordedDirectCallEdges > 1u,
              "this is a high fan-in accessor, not a single-caller stub");
static_assert(kSlotRecordedWriteRows == 1u,
              "the sidecar records exactly one writer of the slot");
static_assert(kSlotRecordedReadRows > kSlotRecordedWriteRows,
              "the slot is read far more often than it is written, which is "
              "the accessor shape the body has");
static_assert(kSlotAccessMode == 'r', "the body READS the slot and never "
                                      "writes it");
static_assert(kBodyReadCallsite == 0x00d38840u,
              "the body's read row sits at the body's own entry address");
static_assert(kSlotWriterCallsite != kBodyReadCallsite,
              "the write row belongs to the constructor, not to this body");
static_assert(kSampledReaderFieldDisplacement == 0x24u,
              "a sampled reader refcounts a field at displacement 0x24");
static_assert(kSampledByteFieldDisplacement == 0xdcu,
              "a sampled reader writes a byte at displacement 0xdc");
static_assert(kSampledWordFieldDisplacement == 0xb4u,
              "a sampled reader loads a word at displacement 0xb4");
// Those displacements are facts about other functions' reach. They are all
// POSITIVE and all far below any plausible object size claim, and this
// package makes no size claim at all - which is exactly why none of them is
// allowed to size anything here.
static_assert(kSampledReaderFieldDisplacement != kSlotAddress,
              "a displacement inside the pointee is not the slot's own address");
static_assert(kSlotAddress != 0u && kSlotAddress > 0x00400000u,
              "the slot lives in the loaded image, above the image base");

static_assert(std::is_same<AbiGlobalSlotGetter00d38840, void* (*)()>::value,
              "the modelled entry takes no parameter and returns a pointer");

// Entry point under reconstruction. The name embeds the 8-hex target VA so the
// validator can bind this span to 0x00d38840. It is the ONLY definition in
// this package that embeds that token.
void* global_singleton_00d38840();

}