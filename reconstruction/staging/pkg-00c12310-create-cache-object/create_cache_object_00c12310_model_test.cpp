// Focused semantic + mutation test for the reconstruction of FUN_00c12310 @
// 0x00c12310 (SporeApp.exe 3.1.0.22).
//
// WHAT MAKES THIS A REFUTATION AND NOT A WALKTHROUGH. Every case below is
// written to FAIL for a specific wrong reconstruction, and the file ends with
// six complete mutants -- bodies that differ from the real one in exactly one
// way -- each of which a case must catch. A case that no mutant provokes is
// not testing what it claims, so the suite asserts the mutants die rather than
// trusting that they would.
//
// The mutants target the six things this body is most likely to get wrong, and
// each is a real trap in the listing rather than an invented one:
//
//   M1  hoist receiver+0xb54 instead of re-reading it before every dispatch.
//       The listing re-reads it six times (0x00c1235b, 0x00c1236b, 0x00c12384,
//       0x00c12398, 0x00c123a6, 0x00c123b5) and a compiler that proved the
//       pointer invariant would be wrong the moment a callee replaced it.
//   M2  pass the RESOLVED argument to the prototyper's +0x40 instead of the
//       ORIGINAL. 0x00c123b1 pushes EBP, which was loaded at 0x00c12324 BEFORE
//       0x00c0c5b0 got the aliasing out-parameter -- the one place the body
//       deliberately uses the pre-call value.
//   M3  sort the six slot displacements. The listing's order is
//       0x08, 0x0c, [0x14], 0x18, 0x40, 0x3c: 0x40 before 0x3c.
//   M4  invert the manager-result flag test. `CMP byte ptr [EBX+0x1c],0x1` +
//       `JZ` stores for every value EXCEPT 1, not for 1.
//   M5  make the created object's return conditional on the cache store. The
//       listing materialises EAX at 0x00c123e1 on the path BOTH ways.
//   M6  add a guard the body does not have: a null first argument must still
//       run the whole dispatch block.
//   M7  pass a non-zero float to the +0x14 slot. The width would be right and
//   the
//       value wrong, which only a bits-level check can see.
//
// THE THREE DIRECT CALLEES this package does not own (0x00c0c5b0, 0x0067cb20,
// 0x00c10250) are defined HERE as recording observers, so every claim the body
// makes about a call is checked against what the machine listing fixes: the
// order of the transfers, each call's receiver and argument vector, the two
// values of the aliased argument, which bytes of the receiver change, and the
// word every exit returns.
//
// The entry is driven through an inline-asm trampoline rather than a C++ call
// on purpose. The target is `__thiscall` with THREE callee-popped stack words
// (`RET 0xc`), and GCC's `__attribute__((thiscall))` on a *function pointer
// type* allocates the outgoing arguments with caller-side cleanup, so a plain
// pointer call would drift the stack by 12 bytes per call and the case bodies
// would read each other's frames. The trampoline reproduces the observed
// sequence exactly -- receiver in ECX, three words pushed, `call *target` --
// and the cleanup is then MEASURED by sampling ESP either side of the call
// rather than asserted as a convention.

#include "create_cache_object_00c12310.hpp"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "the 0x00c12310 model test requires an x86-32 target"
#endif

namespace openspore_reconstruction_pkg00c12310 {

using namespace openspore::reconstruction::pkg_00c12310_create_cache_object;

int g_failures = 0;
int g_checks = 0;
bool g_report = true;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    if (g_report) {
      std::printf("FAIL: %s\n", what);
    }
  }
}

void check_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    if (g_report) {
      std::printf("FAIL: %s (got 0x%08x, want 0x%08x)\n", what, got, want);
    }
  }
}

// ---------------------------------------------------------------------------
// The target's 87 instruction encodings, as re-read from the live bridge with
// `ghidra_disassemble_bytes 0x00c12310 length=218`. Held here so the test
// states the machine it is a model of, and so a reviewer can check a
// displacement against the bytes that carry it instead of against prose.
// ---------------------------------------------------------------------------
constexpr std::uint8_t kTargetBytes[] = {
    0x53,                                // 00c12310 PUSH EBX
    0x55,                                // 00c12311 PUSH EBP
    0x56,                                // 00c12312 PUSH ESI
    0x57,                                // 00c12313 PUSH EDI
    0x8b, 0xf1,                          // 00c12314 MOV ESI,ECX
    0x33, 0xff,                          // 00c12316 XOR EDI,EDI
    0x39, 0xbe, 0x54, 0x0b, 0x00, 0x00,  // 00c12318 CMP [ESI+0xb54],EDI
    0x0f, 0x84, 0xbd, 0x00, 0x00, 0x00,  // 00c1231e JZ 0x00c123e1
    0x8b, 0x6c, 0x24, 0x14,              // 00c12324 MOV EBP,[ESP+0x14]
    0x8d, 0x44, 0x24, 0x14,              // 00c12328 LEA EAX,[ESP+0x14]
    0x50,                                // 00c1232c PUSH EAX
    0x55,                                // 00c1232d PUSH EBP
    0x56,                                // 00c1232e PUSH ESI
    0x89, 0x6c, 0x24, 0x20,              // 00c1232f MOV [ESP+0x20],EBP
    0xe8, 0x78, 0xa2, 0xff, 0xff,        // 00c12333 CALL 0x00c0c5b0
    0x83, 0xc4, 0x0c,                    // 00c12338 ADD ESP,0xc
    0xe8, 0xe0, 0xa7, 0xa6, 0xff,        // 00c1233b CALL 0x0067cb20
    0x8b, 0x10,                          // 00c12340 MOV EDX,[EAX]
    0x8b, 0x7c, 0x24, 0x14,              // 00c12342 MOV EDI,[ESP+0x14]
    0x8b, 0xc8,                          // 00c12346 MOV ECX,EAX
    0x8b, 0x42, 0x40,                    // 00c12348 MOV EAX,[EDX+0x40]
    0x57,                                // 00c1234b PUSH EDI
    0xff, 0xd0,                          // 00c1234c CALL EAX
    0x8b, 0xd8,                          // 00c1234e MOV EBX,EAX
    0x85, 0xdb,                          // 00c12350 TEST EBX,EBX
    0x75, 0x07,                          // 00c12352 JNZ 0x00c1235b
    0x5f,                                // 00c12354 POP EDI
    0x5e,                                // 00c12355 POP ESI
    0x5d,                                // 00c12356 POP EBP
    0x5b,                                // 00c12357 POP EBX
    0xc2, 0x0c, 0x00,                    // 00c12358 RET 0xc
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c1235b MOV ECX,[ESI+0xb54]
    0x8b, 0x11,                          // 00c12361 MOV EDX,[ECX]
    0x8b, 0x42, 0x08,                    // 00c12363 MOV EAX,[EDX+0x8]
    0x6a, 0x00,                          // 00c12366 PUSH 0x0
    0x57,                                // 00c12368 PUSH EDI
    0xff, 0xd0,                          // 00c12369 CALL EAX
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c1236b MOV ECX,[ESI+0xb54]
    0x8b, 0x11,                          // 00c12371 MOV EDX,[ECX]
    0x8b, 0xf8,                          // 00c12373 MOV EDI,EAX
    0x8b, 0x42, 0x0c,                    // 00c12375 MOV EAX,[EDX+0xc]
    0x6a, 0x01,                          // 00c12378 PUSH 0x1
    0x57,                                // 00c1237a PUSH EDI
    0xff, 0xd0,                          // 00c1237b CALL EAX
    0x80, 0x7c, 0x24, 0x1c, 0x00,        // 00c1237d CMP byte [ESP+0x1c],0
    0x74, 0x14,                          // 00c12382 JZ 0x00c12398
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c12384 MOV ECX,[ESI+0xb54]
    0xd9, 0xee,                          // 00c1238a FLDZ
    0x8b, 0x11,                          // 00c1238c MOV EDX,[ECX]
    0x8b, 0x42, 0x14,                    // 00c1238e MOV EAX,[EDX+0x14]
    0x51,                                // 00c12391 PUSH ECX
    0xd9, 0x1c, 0x24,                    // 00c12392 FSTP float [ESP]
    0x57,                                // 00c12395 PUSH EDI
    0xff, 0xd0,                          // 00c12396 CALL EAX
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c12398 MOV ECX,[ESI+0xb54]
    0x8b, 0x11,                          // 00c1239e MOV EDX,[ECX]
    0x8b, 0x42, 0x18,                    // 00c123a0 MOV EAX,[EDX+0x18]
    0x57,                                // 00c123a3 PUSH EDI
    0xff, 0xd0,                          // 00c123a4 CALL EAX
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c123a6 MOV ECX,[ESI+0xb54]
    0x8b, 0x11,                          // 00c123ac MOV EDX,[ECX]
    0x8b, 0x42, 0x40,                    // 00c123ae MOV EAX,[EDX+0x40]
    0x55,                                // 00c123b1 PUSH EBP
    0x57,                                // 00c123b2 PUSH EDI
    0xff, 0xd0,                          // 00c123b3 CALL EAX
    0x8b, 0x8e, 0x54, 0x0b, 0x00, 0x00,  // 00c123b5 MOV ECX,[ESI+0xb54]
    0x8b, 0x11,                          // 00c123bb MOV EDX,[ECX]
    0x8b, 0x42, 0x3c,                    // 00c123bd MOV EAX,[EDX+0x3c]
    0x6a, 0x00,                          // 00c123c0 PUSH 0x0
    0x57,                                // 00c123c2 PUSH EDI
    0xff, 0xd0,                          // 00c123c3 CALL EAX
    0x8b, 0x4c, 0x24, 0x18,              // 00c123c5 MOV ECX,[ESP+0x18]
    0x53,                                // 00c123c9 PUSH EBX
    0x51,                                // 00c123ca PUSH ECX
    0x57,                                // 00c123cb PUSH EDI
    0x56,                                // 00c123cc PUSH ESI
    0xe8, 0x7e, 0xde, 0xff, 0xff,        // 00c123cd CALL 0x00c10250
    0x83, 0xc4, 0x10,                    // 00c123d2 ADD ESP,0x10
    0x80, 0x7b, 0x1c, 0x01,              // 00c123d5 CMP byte [EBX+0x1c],1
    0x74, 0x06,                          // 00c123d9 JZ 0x00c123e1
    0x89, 0xbe, 0x88, 0x0e, 0x00, 0x00,  // 00c123db MOV [ESI+0xe88],EDI
    0x8b, 0xc7,                          // 00c123e1 MOV EAX,EDI
    0x5f,                                // 00c123e3 POP EDI
    0x5e,                                // 00c123e4 POP ESI
    0x5d,                                // 00c123e5 POP EBP
    0x5b,                                // 00c123e6 POP EBX
    0xc2, 0x0c, 0x00,                    // 00c123e7 RET 0xc
};

// The body is 87 instructions and 218 bytes (ghidra_function size_bytes 218,
// the ABI parse record's declared_count 87).
static_assert(sizeof(kTargetBytes) == 218, "the target body is 218 bytes");

// The byte offsets of the instructions this test reasons about, computed by
// summing the lengths above from 0x00c12310. Each is stated as a literal rather
// than derived, so a change to the table that moved one would fail here rather
// than silently retarget a check.
constexpr std::size_t kAtCmpPrototyper = 8;      // 00c12318 CMP [ESI+0xb54],EDI
constexpr std::size_t kAtMovSlot40Manager = 56;  // 00c12348 MOV EAX,[EDX+0x40]
constexpr std::size_t kAtMovSlot08 = 83;         // 00c12363 MOV EAX,[EDX+0x8]
constexpr std::size_t kAtMovSlot0c = 101;        // 00c12375 MOV EAX,[EDX+0xc]
constexpr std::size_t kAtFldz = 122;             // 00c1238a FLDZ
constexpr std::size_t kAtMovSlot14 = 126;        // 00c1238e MOV EAX,[EDX+0x14]
constexpr std::size_t kAtMovSlot18 = 144;        // 00c123a0 MOV EAX,[EDX+0x18]
constexpr std::size_t kAtMovSlot40 = 158;        // 00c123ae MOV EAX,[EDX+0x40]
constexpr std::size_t kAtMovSlot3c = 173;        // 00c123bd MOV EAX,[EDX+0x3c]
constexpr std::size_t kAtCmpFlag = 197;     // 00c123d5 CMP byte [EBX+0x1c],1
constexpr std::size_t kAtStoreCache = 203;  // 00c123db MOV [ESI+0xe88],EDI
constexpr std::size_t kAtRet = 215;         // 00c123e7 RET 0xc

// The two receiver displacements, read out of the ENCODINGS themselves. Each is
// the little-endian immediate that follows the instruction's opcode and ModRM
// byte, so these tie the header's constants to the machine's own bytes rather
// than to a comment. 0x00c12318 is `39 be` + disp32, and 0x00c123db is `89 be`
// + disp32.
static_assert(kTargetBytes[kAtCmpPrototyper + 2] == 0x54 &&
                  kTargetBytes[kAtCmpPrototyper + 3] == 0x0b &&
                  kTargetBytes[kAtCmpPrototyper + 4] == 0x00 &&
                  kTargetBytes[kAtCmpPrototyper + 5] == 0x00,
              "00c12318's displacement immediate is 0x00000b54");
static_assert(kReceiverPrototyperDisplacement == 0xb54,
              "receiver+0xb54 is the word 00c12318 compares against zero");
static_assert(kTargetBytes[kAtStoreCache + 2] == 0x88 &&
                  kTargetBytes[kAtStoreCache + 3] == 0x0e &&
                  kTargetBytes[kAtStoreCache + 4] == 0x00 &&
                  kTargetBytes[kAtStoreCache + 5] == 0x00,
              "00c123db's displacement immediate is 0x00000e88");
static_assert(kReceiverCachedObjectDisplacement == 0xe88,
              "receiver+0xe88 is the word 00c123db stores into");

// The manager-result flag's displacement: 0x00c123d5 is `80 7b` + disp8.
static_assert(kTargetBytes[kAtCmpFlag + 2] == 0x1c,
              "00c123d5's displacement byte is 0x1c");
static_assert(kManagerResultFlagDisplacement == 0x1c,
              "the flag byte is at manager_result+0x1c");
static_assert(kManagerResultFlagSuppress == 1u, "00c123d5's immediate is 0x01");
static_assert(kTargetBytes[kAtCmpFlag + 3] == 0x01,
              "the CMP immediate really is the byte 0x01");

// The float argument: FLDZ is `d9 ee` and the store that follows the scratch
// push is `FSTP float ptr [ESP]`, `d9 1c 24`. Both are stated so "the argument
// is zero" cannot be satisfied by a model that passes a double or a negative
// zero without the test noticing.
static_assert(kTargetBytes[kAtFldz] == 0xd9 &&
                  kTargetBytes[kAtFldz + 1] == 0xee,
              "00c1238a is FLDZ, which pushes a positive zero");
static_assert(kZeroFloatBits == 0x00000000u,
              "FLDZ clears sign, exponent and mantissa, so the bits are zero");
static_assert(sizeof(float) == 4,
              "FSTP float ptr writes 4 bytes, which is what the argument is");

// The cleanup: `c2 0c 00` is `RET 0xc`, so the callee pops twelve bytes of
// stack argument itself.
static_assert(kTargetBytes[kAtRet] == 0xc2 &&
                  kTargetBytes[kAtRet + 1] == 0x0c &&
                  kTargetBytes[kAtRet + 2] == 0x00,
              "00c123e7 is RET 0xc");
static_assert(kStackCleanupBytes == 0x0c, "twelve bytes of stack argument");
static_assert(kSavedRegisterBytes == 0x10,
              "four PUSHes put ESP at entry_ESP-0x10, so [ESP+0x14] is +0x4");

// The ABI's PARAMETER SHAPE, stated as a type so a change to the entry's
// signature is a compile error rather than a silent disagreement with the
// listing. The convention itself is not comparable across compilers here --
// `__attribute__((thiscall))` on a function-pointer TYPE is part of that type
// in clang and not in GCC -- so the convention is pinned by MEASUREMENT
// instead, in case_stack_cleanup_is_the_callees, which samples ESP either side
// of the call. Three words, and the third is a byte: that is the shape the
// listing's three distinct [ESP+0x14]/[ESP+0x18]/[ESP+0x1c] reads fix.
using AbiEntry00c12310 = OpaqueCreated* (*)(OpaqueOwner*, Word, Word,
                                            std::uint8_t);
using TwoWordsAndAByte = OpaqueCreated* (*)(OpaqueOwner*, Word, Word,
                                            std::uint8_t);
static_assert(std::is_same<AbiEntry00c12310, TwoWordsAndAByte>::value,
              "the entry takes a receiver plus two 32-bit words and one byte");
static_assert(
    sizeof(std::uint8_t) == 1 && sizeof(Word) == 4,
    "the third stack word is a one-byte read and the others are four");

// ---------------------------------------------------------------------------
// Observer state
// ---------------------------------------------------------------------------

enum CallId {
  kResolve = 0,    // 0x00c0c5b0
  kManagerRoot,    // 0x0067cb20
  kManagerSlot40,  // dispatch 1
  kProtoSlot08,    // dispatch 2
  kProtoSlot0c,    // dispatch 3
  kProtoSlot14,    // dispatch 4, conditional
  kProtoSlot18,    // dispatch 5
  kProtoSlot40,    // dispatch 6
  kProtoSlot3c,    // dispatch 7
  kAttach,         // 0x00c10250
  kCallCount
};

const char* const kCallNames[kCallCount] = {
    "resolve_00c0c5b0",   "manager_root_0067cb20", "manager_slot_40",
    "prototyper_slot_08", "prototyper_slot_0c",    "prototyper_slot_14",
    "prototyper_slot_18", "prototyper_slot_40",    "prototyper_slot_3c",
    "attach_00c10250"};

struct Recorded {
  int id = -1;
  const void* receiver = nullptr;
  Word arg0 = 0u;
  Word arg1 = 0u;
  // A fourth word, for the one call in this body that takes four arguments
  // (0x00c10250, 0x00c123c9..0x00c123cc push four words). Kept separate rather
  // than folded into arg1 so a check about the third argument cannot be
  // satisfied by the fourth.
  Word arg2 = 0u;
  float real = 0.0f;
  Word real_bits = 0u;
  bool has_float = false;
};

Recorded g_calls[kCallCount * 4];
int g_call_count = 0;

// The behaviour knobs a case turns.
Word g_resolve_writes = 0u;  // value 0x00c0c5b0 writes through its 3rd arg
bool g_resolve_writes_at_all = false;
bool g_manager_slot40_null = false;
Word g_manager_flag = 0u;                 // the byte at manager_result+0x1c
bool g_swap_prototyper_after_08 = false;  // M1's trigger: replace the pointer
OpaquePrototyper* g_replacement_prototyper = nullptr;
OpaqueCreated* g_created = nullptr;
OpaqueManagerResult* g_manager_result = nullptr;
// The receiver under test, so an observer reached through a slot can perturb
// it exactly the way a real callee could. Set by `arm_owner`.
OpaqueOwner* g_owner_under_test = nullptr;

void reset_observer() {
  g_call_count = 0;
  // Value-initialised rather than memset: `Recorded` has default member
  // initialisers, so it is non-trivial and g++'s -Wclass-memaccess refuses a
  // memset over it. Assigning a default-constructed value clears every field
  // and keeps both compilers quiet for the same reason.
  for (Recorded& entry : g_calls) {
    entry = Recorded();
  }
  g_resolve_writes = 0u;
  g_resolve_writes_at_all = false;
  g_manager_slot40_null = false;
  g_manager_flag = 0u;
  g_swap_prototyper_after_08 = false;
  g_replacement_prototyper = nullptr;
}

void record(int id, const void* receiver, Word arg0, Word arg1) {
  if (g_call_count < static_cast<int>(sizeof(g_calls) / sizeof(g_calls[0]))) {
    g_calls[g_call_count].id = id;
    g_calls[g_call_count].receiver = receiver;
    g_calls[g_call_count].arg0 = arg0;
    g_calls[g_call_count].arg1 = arg1;
  }
  ++g_call_count;
}

int count_of(int id) {
  int total = 0;
  for (int index = 0; index < g_call_count && index < kCallCount * 4; ++index) {
    if (g_calls[index].id == id) {
      ++total;
    }
  }
  return total;
}

int index_of(int id, int occurrence = 0) {
  int seen = 0;
  for (int index = 0; index < g_call_count && index < kCallCount * 4; ++index) {
    if (g_calls[index].id == id) {
      if (seen == occurrence) {
        return index;
      }
      ++seen;
    }
  }
  return -1;
}

// ---------------------------------------------------------------------------
// The seven virtual slots, as recording observers bound into a real table
// object. Each receives ECX (the table owner) and its pushed arguments, exactly
// as the machine's `CALL EAX` sites do, and the table is installed at the
// object's first word so `table_of` reads it the way `MOV EDX,[reg]` does.
// ---------------------------------------------------------------------------
OpaqueManagerResult* PKG_00C12310_THISCALL
observe_manager_slot40(OpaqueManager* self, Word argument) {
  record(kManagerSlot40, self, argument, 0u);
  if (g_manager_slot40_null) {
    return nullptr;
  }
  *byte_at(g_manager_result, 0x1c) = static_cast<std::uint8_t>(g_manager_flag);
  return g_manager_result;
}

OpaqueCreated* PKG_00C12310_THISCALL
observe_proto_slot08(OpaquePrototyper* self, Word argument, Word flag) {
  record(kProtoSlot08, self, argument, flag);
  if (g_swap_prototyper_after_08) {
    g_swap_prototyper_after_08 = false;
    *word_at(g_owner_under_test, 0xb54) =
        pointer_word(g_replacement_prototyper);
  }
  return g_created;
}

void PKG_00C12310_THISCALL observe_proto_slot0c(OpaquePrototyper* self,
                                                OpaqueCreated* created,
                                                Word flag) {
  record(kProtoSlot0c, self, pointer_word(created), flag);
}

void PKG_00C12310_THISCALL observe_proto_slot14(OpaquePrototyper* self,
                                                OpaqueCreated* created,
                                                float value) {
  const int index = g_call_count;
  record(kProtoSlot14, self, pointer_word(created), 0u);
  g_calls[index].has_float = true;
  g_calls[index].real = value;
  std::memcpy(&g_calls[index].real_bits, &value, sizeof(value));
}

void PKG_00C12310_THISCALL observe_proto_slot18(OpaquePrototyper* self,
                                                OpaqueCreated* created) {
  record(kProtoSlot18, self, pointer_word(created), 0u);
}

void PKG_00C12310_THISCALL observe_proto_slot40(OpaquePrototyper* self,
                                                OpaqueCreated* created,
                                                Word argument) {
  record(kProtoSlot40, self, pointer_word(created), argument);
}

void PKG_00C12310_THISCALL observe_proto_slot3c(OpaquePrototyper* self,
                                                OpaqueCreated* created,
                                                Word flag) {
  record(kProtoSlot3c, self, pointer_word(created), flag);
}

OpaqueManagerVTable g_manager_table = {
    {nullptr},
    &observe_manager_slot40,
};

OpaquePrototyperVTable g_proto_table = {
    {nullptr, nullptr},
    &observe_proto_slot08,
    &observe_proto_slot0c,
    nullptr,
    &observe_proto_slot14,
    &observe_proto_slot18,
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    &observe_proto_slot3c,
    &observe_proto_slot40,
};

OpaqueManager g_manager_object = {&g_manager_table};
OpaquePrototyper g_prototyper_object = {&g_proto_table};
OpaquePrototyper g_replacement_prototyper_object = {&g_proto_table};

OpaqueManagerResult g_manager_result_object;
OpaqueCreated g_created_object;

OpaqueManager* const kManagerObject = &g_manager_object;
OpaquePrototyper* const kPrototyperObject = &g_prototyper_object;
OpaquePrototyper* const kReplacementPrototyperObject =
    &g_replacement_prototyper_object;
OpaqueManagerResult* const kManagerResultObject = &g_manager_result_object;
OpaqueCreated* const kCreatedObject = &g_created_object;

// ---------------------------------------------------------------------------
// The three direct callees, defined here.
// ---------------------------------------------------------------------------
extern "C" void PKG_00C12310_CDECL resolve_prototype_00c0c5b0(
    OpaqueOwner* owner, Word argument, Word* argument_out) {
  record(kResolve, owner, argument, pointer_word(argument_out));
  if (g_resolve_writes_at_all) {
    // 0x00c0c5b0 was handed the address of the body's own argument slot
    // (0x00c12328 LEA EAX,[ESP+0x14] over the 0x00c12324 read), so writing
    // here is exactly what the aliasing out-parameter permits.
    *argument_out = g_resolve_writes;
  }
}

extern "C" OpaqueManager* PKG_00C12310_CDECL manager_root_0067cb20() {
  record(kManagerRoot, nullptr, 0u, 0u);
  return kManagerObject;
}

extern "C" void PKG_00C12310_CDECL attach_created_object_00c10250(
    OpaqueOwner* owner, OpaqueCreated* created, Word argument1,
    OpaqueManagerResult* manager_result) {
  // Four arguments, four pushes (0x00c123cc receiver, 0x00c123cb created,
  // 0x00c123ca argument1, 0x00c123c9 manager_result), so the recording uses all
  // four fields: receiver, arg0, arg1 and the new arg2.
  const int slot = g_call_count;
  record(kAttach, owner, pointer_word(created), argument1);
  if (slot >= 0 &&
      slot < static_cast<int>(sizeof(g_calls) / sizeof(g_calls[0]))) {
    g_calls[slot].arg2 = pointer_word(manager_result);
  }
}

// ---------------------------------------------------------------------------
// The driver. The entry is reached the way the listing reaches it: receiver in
// ECX, three words pushed, `call *target`, and the callee pops them.
// ---------------------------------------------------------------------------
OpaqueOwner g_owner_storage;
OpaqueOwner* g_owner = &g_owner_storage;
std::uint8_t g_canary[64];

using Body = OpaqueCreated*(PKG_00C12310_THISCALL*)(OpaqueOwner*, Word, Word,
                                                    std::uint8_t);

struct EspSamples {
  std::uint32_t before = 0u;
  std::uint32_t after = 0u;
};

OpaqueCreated* run(Body body, OpaqueOwner* owner, Word argument0,
                   Word argument1, std::uint8_t flag, EspSamples* samples) {
  // Everything the trampoline needs is staged in ONE local array and the asm
  // block reads it by offset, so the block holds no register operands beyond
  // the two it writes. That is what keeps the constraint set inside the eight
  // x86-32 registers; five `"r"` inputs plus the memory outputs overflowed
  // them.
  //
  // `slot[0]` the target address, `slot[1]` the receiver, `slot[2]` the first
  // word, `slot[3]` the second, `slot[4]` the flag WIDENED to a word. The
  // widening happens HERE ONLY, because an `std::uint8_t` operand would be
  // allocated an 8-bit register and `pushl` cannot take one. The pushed value
  // is the same 32-bit word a real caller pushes: the listing reads only the
  // low byte of it (0x00c1237d `CMP byte ptr [ESP+0x1c],0x0`), and the three
  // pushes are the three words `RET 0xc` pops.
  //
  // The pushes are in REVERSE argument order, because the stack grows down and
  // the LAST push is the FIRST argument: the machine's own caller puts the
  // third word at entry_ESP+0xc, the second at +0x8 and the first at +0x4, and
  // with the four register saves in place the body reads [ESP+0x1c], [ESP+0x18]
  // and [ESP+0x14] respectively. So flag first, then the second word, then the
  // first.
  std::uint32_t slot[5];
  slot[0] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(body));
  slot[1] = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(owner));
  slot[2] = argument0;
  slot[3] = argument1;
  slot[4] = flag;
  std::uint32_t before = 0u;
  std::uint32_t after = 0u;
  std::uint32_t result = 0u;
  __asm__ __volatile__(
      "movl %%esp, %[before]\n\t"
      "movl 4(%[slot]), %%ecx\n\t"  // slot[1], the receiver
      "pushl 16(%[slot])\n\t"       // slot[4], the flag word  -> +0xc
      "pushl 12(%[slot])\n\t"       // slot[3], the second word -> +0x8
      "pushl 8(%[slot])\n\t"        // slot[2], the first word  -> +0x4
      "call *0(%[slot])\n\t"        // slot[0], the entry
      "movl %%esp, %[after]\n\t"
      "movl %%eax, %[result]\n\t"
      : [before] "=m"(before), [after] "=m"(after), [result] "=m"(result)
      : [slot] "r"(slot)
      : "eax", "ecx", "edx", "memory");
  if (samples != nullptr) {
    samples->before = before;
    samples->after = after;
  }
  return reinterpret_cast<OpaqueCreated*>(static_cast<std::uintptr_t>(result));
}

void fill_owner(OpaqueOwner* owner) {
  for (std::size_t index = 0; index < sizeof(owner->opaque_00); ++index) {
    owner->opaque_00[index] = static_cast<std::uint8_t>(index + 1u);
  }
  std::memset(g_canary, 0xa5, sizeof(g_canary));
}

void arm_owner(OpaqueOwner* owner) {
  g_owner_under_test = owner;
  *word_at(owner, 0xb54) = pointer_word(kPrototyperObject);
  *word_at(owner, 0xe88) = 0x5a5a5a5au;
}

OpaqueCreated* run_armed(Word argument0, Word argument1, std::uint8_t flag,
                         EspSamples* samples) {
  return run(&create_cached_object_00c12310, g_owner, argument0, argument1,
             flag, samples);
}

// The body every case exercises. `failures_of` swaps it to a mutant and swaps
// it back, so the cases themselves are written once and are not quietly
// re-pointed at a different entry for the real run.
Body g_body = &create_cached_object_00c12310;

OpaqueCreated* run_current(Word argument0, Word argument1, std::uint8_t flag,
                           EspSamples* samples = nullptr) {
  return run(g_body, g_owner, argument0, argument1, flag, samples);
}

// The values the observers hand back. Every case that reaches the dispatch
// block needs both of these armed, so they are set here rather than repeated:
// `g_manager_result` is what the manager's +0x40 slot returns and the byte the
// body later tests lives in it, and `g_created` is what the prototyper's +0x08
// slot returns.
void arm_callees() {
  g_created = kCreatedObject;
  g_manager_result = kManagerResultObject;
  *byte_at(g_manager_result, 0x1c) = 0u;
}

// ---------------------------------------------------------------------------
// CASES
// ---------------------------------------------------------------------------

// 1. The entry's ABI, MEASURED rather than asserted. `RET 0xc` means the callee
// owns the twelve bytes of stack argument, so ESP either side of the call must
// agree; a caller-cleanup entry would leave the second sample twelve bytes
// lower. Three words are pushed, so a two-argument or four-argument entry would
// not balance either.
void case_stack_cleanup_is_the_callees() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  EspSamples samples{};
  run_current(0x1111u, 0x2222u, 0u, &samples);
  check(samples.after == samples.before,
        "ESP is restored across the call: the callee pops its 12 bytes");
  check(samples.before != 0u, "the ESP sample was taken");
}

// 2. The two early exits take NO call and NO store. The guard is the only thing
// between entry and the first transfer on the null-prototyper path, and the
// +0x40 null check is the only thing between it and the dispatch block on the
// other.
void case_null_prototyper_exits_before_any_call() {
  fill_owner(g_owner);
  *word_at(g_owner, 0xb54) = 0u;
  *word_at(g_owner, 0xe88) = 0x5a5a5a5au;
  reset_observer();
  arm_callees();

  const OpaqueCreated* result = run_current(0x1111u, 0x2222u, 0xffu);
  check(result == nullptr, "a null prototyper returns null");
  check(g_call_count == 0, "a null prototyper makes no call at all");
  check_word(*word_at(g_owner, 0xe88), 0x5a5a5a5au,
             "a null prototyper leaves the cache word alone");
}

void case_null_manager_result_exits_after_two_calls() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_manager_slot40_null = true;

  const OpaqueCreated* result = run_current(0x1111u, 0x2222u, 0xffu);
  check(result == nullptr, "a null manager result returns null");
  check(g_call_count == 3,
        "the null path is exactly resolve, manager_root and the +0x40 slot");
  check(index_of(kResolve) == 0, "resolve is the first transfer");
  check(index_of(kManagerRoot) == 1, "manager_root is the second");
  check(index_of(kManagerSlot40) == 2, "the manager's +0x40 slot is the third");
  check(count_of(kProtoSlot08) == 0, "no prototyper slot is reached");
  check_word(*word_at(g_owner, 0xe88), 0x5a5a5a5au,
             "the null path leaves the cache word alone");
}

// 3. The full call SEQUENCE, which is the claim a per-slot check cannot make.
// The listing's order is resolve, manager_root, manager+0x40, proto+0x08,
// proto+0x0c, [proto+0x14], proto+0x18, proto+0x40, proto+0x3c, attach -- and
// note 0x40 BEFORE 0x3c, which is not sorted order.
void case_call_sequence() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();

  run_current(0x1111u, 0x2222u, 0xffu);
  const int expected[] = {
      kResolve,     kManagerRoot, kManagerSlot40, kProtoSlot08, kProtoSlot0c,
      kProtoSlot14, kProtoSlot18, kProtoSlot40,   kProtoSlot3c, kAttach};
  const int expected_count = static_cast<int>(sizeof(expected) / sizeof(int));
  check(g_call_count == expected_count,
        "the full path makes exactly ten transfers");
  for (int index = 0; index < expected_count; ++index) {
    if (g_call_count <= index || g_calls[index].id != expected[index]) {
      check(false, kCallNames[expected[index]]);
      continue;
    }
    check(true, kCallNames[expected[index]]);
  }
}

// 4. The same sequence with the flag CLEAR, where the +0x14 slot is skipped
// and nothing else changes. 0x00c12382 JZ is the only conditional jump on this
// path besides the two exits.
void case_flag_zero_skips_only_the_float_slot() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();

  run_current(0x1111u, 0x2222u, 0x00u);
  check(g_call_count == 9, "a clear flag makes nine transfers, not ten");
  check(count_of(kProtoSlot14) == 0,
        "a clear flag skips the +0x14 slot and only that slot");
  check(count_of(kProtoSlot3c) == 1,
        "a clear flag still reaches the last slot, +0x3c");
  // Nine transfers, so indices 0..8. The full sequence is resolve,
  // manager_root, manager+0x40, +0x08, +0x0c, [+0x14], +0x18, +0x40, +0x3c,
  // attach; dropping the bracketed +0x14 leaves +0x18 at 5, +0x40 at 6, +0x3c
  // at 7 and attach at 8. That the RELATIVE order of the tail is unchanged is
  // the claim.
  check(index_of(kProtoSlot18) == 5, "+0x18 is the sixth transfer");
  check(index_of(kProtoSlot40) == 6, "+0x40 is the seventh");
  check(index_of(kProtoSlot3c) == 7, "+0x3c is the eighth, still after +0x40");
  check(index_of(kAttach) == 8, "attach is last");
  check(index_of(kProtoSlot3c) < index_of(kAttach),
        "and +0x3c still precedes attach");
}
// 5. The flag is compared as a BYTE against ZERO. 0xff, 0x01 and 0x80 all take
// the branch; 0x00 does not. A word-width test would also pass these, so the
// discriminating case is a value whose HIGH bytes are set and whose low byte is
// not -- the model can only read a byte, so a word read of 0x00000100 would
// take the branch where the machine does not.
void case_flag_is_a_one_byte_test_against_zero() {
  struct FlagCase {
    std::uint8_t flag;
    bool takes_branch;
  };
  const FlagCase cases[] = {
      {0x00u, false}, {0x01u, true}, {0xffu, true},
      {0x80u, true},  {0x7fu, true},
  };
  for (const FlagCase& item : cases) {
    fill_owner(g_owner);
    arm_owner(g_owner);
    reset_observer();
    arm_callees();
    run_current(0x1111u, 0x2222u, item.flag);
    check((count_of(kProtoSlot14) == 1) == item.takes_branch,
          "the one-byte flag test against zero takes the branch exactly when "
          "the low byte is non-zero");
  }
}

// 6. The float argument is the BITS of a positive zero, four bytes wide.
// `FLDZ` clears sign, exponent and mantissa; `FSTP float ptr` writes four
// bytes. The test asserts the bits, not the value, so "+0.0f" and "-0.0f"
// cannot pass for each other.
void case_float_argument_is_four_bytes_of_positive_zero() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();

  run_current(0x1111u, 0x2222u, 0x01u);
  const int index = index_of(kProtoSlot14);
  check(index >= 0, "the +0x14 slot was reached");
  if (index >= 0) {
    check(g_calls[index].has_float, "the +0x14 slot took a float argument");
    check_word(g_calls[index].real_bits, kZeroFloatBits,
               "0x00c1238a/0x00c12392 write the bits 0x00000000");
    check(g_calls[index].real_bits == 0x80000000u ? false : true,
          "and not the sign bit, so it is a positive zero");
  }
}

// 7. Receiver and argument vectors for every transfer, read off the pushes.
// The one that matters most is 0x00c10250, whose THIRD argument the committed
// decompilation renders as the constant 1 while the listing reads it from
// [ESP+0x18] = entry_ESP+0x8.
void case_argument_vectors() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_resolve_writes_at_all = true;
  g_resolve_writes = 0x9999u;  // forces argument0 and resolved to differ

  run_current(0x1111u, 0x2222u, 0x01u);

  const int resolve = index_of(kResolve);
  check(resolve >= 0 && g_calls[resolve].receiver == g_owner,
        "0x00c0c5b0 receives the receiver as its first argument");
  check(resolve >= 0 && g_calls[resolve].arg0 == 0x1111u,
        "0x00c0c5b0 receives the ORIGINAL argument0 second");
  // The third argument is a POINTER into the body's own frame: 0x00c12328 is
  // `LEA EAX,[ESP + 0x14]`, i.e. the address of the first argument slot, and
  // 0x00c1232f stores EBP back through that very slot. So the pointer is NOT
  // the receiver and NOT a static address -- it is a stack address, which in
  // this model is where the `resolved` local lives. What the check can state
  // without claiming a frame layout is that it is non-null, that it is not the
  // receiver, and that writing through it is what changes what the later
  // dispatches see -- which case_the_aliased_argument_is_re_read_not_copied
  // proves directly, and is the substantive claim.
  check(resolve >= 0 && g_calls[resolve].arg1 != 0u,
        "0x00c0c5b0's third argument is a non-null out-parameter pointer");
  check(resolve >= 0 && g_calls[resolve].arg1 != pointer_word(g_owner),
        "and it is not the receiver's own address");
  check(resolve >= 0 && g_calls[resolve].arg1 != pointer_word(kManagerObject) &&
            g_calls[resolve].arg1 != pointer_word(kPrototyperObject),
        "and it is neither of the two objects the body dispatches through");

  const int manager40 = index_of(kManagerSlot40);
  check(manager40 >= 0 && g_calls[manager40].receiver == kManagerObject,
        "the manager's +0x40 slot receives the manager 0x0067cb20 returned");
  check(manager40 >= 0 && g_calls[manager40].arg0 == 0x9999u,
        "the manager's +0x40 slot receives the RESOLVED argument");

  const int proto08 = index_of(kProtoSlot08);
  check(proto08 >= 0 && g_calls[proto08].receiver == kPrototyperObject,
        "the +0x08 slot receives the prototyper at receiver+0xb54");
  check(proto08 >= 0 && g_calls[proto08].arg0 == 0x9999u,
        "the +0x08 slot receives the RESOLVED argument");
  check(proto08 >= 0 && g_calls[proto08].arg1 == 0u,
        "0x00c12366 pushes 0x0 as the +0x08 slot's second argument");

  const int proto0c = index_of(kProtoSlot0c);
  check(proto0c >= 0 && g_calls[proto0c].arg0 == pointer_word(kCreatedObject),
        "the +0x0c slot receives the created object");
  check(proto0c >= 0 && g_calls[proto0c].arg1 == 1u,
        "0x00c12378 pushes 0x1 as the +0x0c slot's second argument");

  const int proto18 = index_of(kProtoSlot18);
  check(proto18 >= 0 && g_calls[proto18].arg0 == pointer_word(kCreatedObject),
        "the +0x18 slot receives the created object");

  const int proto40 = index_of(kProtoSlot40);
  check(proto40 >= 0 && g_calls[proto40].arg0 == pointer_word(kCreatedObject),
        "the prototyper's +0x40 slot receives the created object first");
  check(proto40 >= 0 && g_calls[proto40].arg1 == 0x1111u,
        "the prototyper's +0x40 slot receives the ORIGINAL argument0 second, "
        "from EBP rather than from the re-read EDI");

  const int proto3c = index_of(kProtoSlot3c);
  check(proto3c >= 0 && g_calls[proto3c].arg0 == pointer_word(kCreatedObject),
        "the +0x3c slot receives the created object");
  check(proto3c >= 0 && g_calls[proto3c].arg1 == 0u,
        "0x00c123c0 pushes 0x0 as the +0x3c slot's second argument");

  const int attach = index_of(kAttach);
  check(attach >= 0 && g_calls[attach].receiver == g_owner,
        "0x00c10250 receives the receiver first");
  check(attach >= 0 && g_calls[attach].arg0 == pointer_word(kCreatedObject),
        "0x00c10250 receives the created object second");
  check(attach >= 0 && g_calls[attach].arg1 == 0x2222u,
        "0x00c10250 receives the SECOND stack word third, read at 0x00c123c5");
  check(
      attach >= 0 && g_calls[attach].arg2 == pointer_word(kManagerResultObject),
      "0x00c10250 receives the manager's +0x40 result fourth");
  check(attach >= 0 && g_calls[attach].arg2 != g_calls[attach].arg0,
        "and the fourth argument is not the second, so a check about one "
        "cannot be satisfied by the other");
}

// 8. The aliased out-parameter is a REAL alias, not a copy. The body hands
// 0x00c0c5b0 the address of the same word it read, so a write through it
// changes what the manager's +0x40 and the +0x08 slot see, while the +0x40 slot
// keeps the pre-call value. This is the whole reason the re-read at 0x00c12342
// is not redundant, and it is the only case that can tell the two apart.
void case_the_aliased_argument_is_re_read_not_copied() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_resolve_writes_at_all = true;
  g_resolve_writes = 0x7777u;

  run_current(0x1111u, 0x2222u, 0x01u);

  const int manager40 = index_of(kManagerSlot40);
  const int proto08 = index_of(kProtoSlot08);
  const int proto0c = index_of(kProtoSlot0c);
  const int proto40 = index_of(kProtoSlot40);
  check(manager40 >= 0 && g_calls[manager40].arg0 == 0x7777u,
        "the manager's +0x40 sees the value the helper wrote");
  check(proto08 >= 0 && g_calls[proto08].arg0 == 0x7777u,
        "the +0x08 slot sees the value the helper wrote");
  check(proto0c >= 0, "the +0x0c slot is still reached");
  check(proto40 >= 0 && g_calls[proto40].arg1 == 0x1111u,
        "the prototyper's +0x40 keeps the value from BEFORE the helper ran");
  check(manager40 >= 0 && proto40 >= 0 &&
            g_calls[manager40].arg0 != g_calls[proto40].arg1,
        "the two +0x40 slots are reached with different values, which is only "
        "possible if the out-parameter is an alias");

  // And with no write, they are the same value -- so the difference above is
  // produced by the write and not by the two paths having been written
  // differently.
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_resolve_writes_at_all = false;
  run_current(0x1111u, 0x2222u, 0x01u);
  const int manager40b = index_of(kManagerSlot40);
  const int proto40b = index_of(kProtoSlot40);
  check(manager40b >= 0 && g_calls[manager40b].arg0 == 0x1111u &&
            proto40b >= 0 && g_calls[proto40b].arg1 == 0x1111u,
        "with no write through the out-parameter both slots see one value");
}

// 9. Receiver+0xb54 is RE-READ before every dispatch, not hoisted. The listing
// reads it six times and a callee that replaced the pointer would change which
// table the NEXT call goes through. The observer swaps it during the +0x08
// call, and the following five dispatches must then be observed on the
// replacement. A hoisted reconstruction would keep using the original and fail.
void case_prototyper_is_re_read_before_every_dispatch() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_replacement_prototyper = kReplacementPrototyperObject;
  g_swap_prototyper_after_08 = true;

  run_current(0x1111u, 0x2222u, 0x01u);

  check(index_of(kProtoSlot08) >= 0 &&
            g_calls[index_of(kProtoSlot08)].receiver == kPrototyperObject,
        "the +0x08 slot is reached on the ORIGINAL prototyper");
  const int ids[] = {kProtoSlot0c, kProtoSlot14, kProtoSlot18, kProtoSlot40,
                     kProtoSlot3c};
  for (const int id : ids) {
    const int index = index_of(id);
    check(index >= 0 && g_calls[index].receiver == kReplacementPrototyperObject,
          kCallNames[id]);
  }
  check_word(*word_at(g_owner, 0xb54),
             pointer_word(kReplacementPrototyperObject),
             "the swap the observer performed is visible in the receiver");
}

// 10. The cache store: conditional on the manager result's byte at +0x1c being
// anything EXCEPT one, and conditional on nothing else. The listing's
// `CMP byte ptr [EBX+0x1c],0x1` + `JZ` is the whole condition, so every other
// byte value must store -- including values the flag argument happens to take.
void case_cache_store_is_conditional_on_the_manager_result_byte() {
  const Word flags[] = {0x00u, 0x01u, 0x02u, 0x7fu, 0x80u, 0xffu};
  for (const Word flag : flags) {
    fill_owner(g_owner);
    arm_owner(g_owner);
    reset_observer();
    arm_callees();
    g_manager_flag = flag;

    const OpaqueCreated* result = run_current(0x1111u, 0x2222u, 0x01u);
    const bool should_store = (flag != 1u);
    check_word(*word_at(g_owner, 0xe88),
               should_store ? pointer_word(kCreatedObject) : 0x5a5a5a5au,
               "the +0xe88 store happens for every manager flag except one");
    // The return is UNCONDITIONAL on this path: 0x00c123e1 materialises EAX
    // whether or not the store happened.
    check(result == kCreatedObject,
          "the created object is returned whether or not it was cached");
  }
}

// 11. The byte compared is at manager_result+0x1c and NOT in the receiver. The
// observer plants distinct bytes at the two places and the store must follow
// the manager result's.
void case_the_flag_lives_on_the_manager_result_not_the_receiver() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_manager_flag = 1u;  // suppress
  // A byte of 0xff at the same displacement inside the receiver, which must
  // have no effect at all.
  *byte_at(g_owner, 0x1c) = 0xffu;

  run_current(0x1111u, 0x2222u, 0x01u);
  check_word(*word_at(g_owner, 0xe88), 0x5a5a5a5au,
             "a byte at receiver+0x1c does not drive the store");
  // The body never writes receiver+0x1c, so the byte is still the one planted
  // here. `fill_owner` laid down a pattern first and `arm_owner` touched only
  // +0xb54 and +0xe88, so the three bytes after the planted one are still the
  // pattern's -- reading the whole word is how that is stated, and it also says
  // the body did not disturb the neighbouring bytes.
  const Word expected_word =
      static_cast<Word>(0xffu) |
      (static_cast<Word>(g_owner->opaque_00[0x1d]) << 8) |
      (static_cast<Word>(g_owner->opaque_00[0x1e]) << 16) |
      (static_cast<Word>(g_owner->opaque_00[0x1f]) << 24);
  check_word(*word_at(g_owner, 0x1c), expected_word,
             "the planted byte and the three pattern bytes after it are both "
             "still there: the body wrote nothing at receiver+0x1c");
}

// 12. Nothing outside receiver+0xe88 changes, and receiver+0xb54 is only read.
// The header's `OpaqueOwner` ends at 0xe88+4, and the model test keeps a canary
// past the end; both are diffed after a run.
void case_only_the_cache_word_is_written() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  std::uint8_t before[sizeof(g_owner->opaque_00)];
  std::memcpy(before, g_owner->opaque_00, sizeof(before));
  reset_observer();
  arm_callees();

  run_current(0x1111u, 0x2222u, 0xffu);

  for (std::size_t index = 0; index < sizeof(before); ++index) {
    const bool inside_cache = index >= 0xe88 && index < 0xe88 + sizeof(Word);
    if (inside_cache) {
      continue;  // rewritten by the store, pinned by the case above
    }
    if (g_owner->opaque_00[index] != before[index]) {
      check(false, "a byte outside receiver+0xe88 changed");
      return;
    }
  }
  check(true, "every byte of the receiver outside +0xe88 is untouched");
  check(sizeof(g_owner->opaque_00) == 0xe88 + sizeof(Word),
        "the modelled receiver ends where the store ends");
  bool canary_intact = true;
  for (const std::uint8_t byte : g_canary) {
    if (byte != 0xa5u) {
      canary_intact = false;
    }
  }
  check(canary_intact, "nothing past the end of the receiver was written");
  check_word(*word_at(g_owner, 0xb54), pointer_word(kPrototyperObject),
             "receiver+0xb54 is read, never written");
}

// 13. The three exit words. All three exits are reachable and each is pinned:
// null on entry, null from the manager, the created object otherwise.
void case_every_exit_returns_what_the_listing_says() {
  fill_owner(g_owner);
  *word_at(g_owner, 0xb54) = 0u;
  reset_observer();
  check(run_current(0x1111u, 0x2222u, 0u) == nullptr,
        "exit 1 (0x00c1231e -> 0x00c123e1) returns EAX = 0");

  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_manager_slot40_null = true;
  check(run_current(0x1111u, 0x2222u, 0u) == nullptr,
        "exit 2 (0x00c12354 -> 0x00c12358) returns the null the slot returned");

  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  g_manager_flag = 0u;
  check(run_current(0x1111u, 0x2222u, 0u) == kCreatedObject,
        "exit 3 (0x00c123e1) returns the created object");
}

// 14. The receiver's prototyper word is the ONLY thing the entry guard looks
// at. A non-zero pointer with a null argument, and a zero argument with a
// non-zero pointer, must behave differently -- which rules out a reconstruction
// that tested the argument.
void case_the_guard_tests_the_receiver_pointer_not_the_argument() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();
  // A NULL argument with a live prototyper still runs the whole body.
  const OpaqueCreated* result = run_current(0u, 0u, 0u);
  check(result == kCreatedObject,
        "a null argument does not trigger the entry guard");
  check(
      g_call_count == 9,
      "a null argument still makes all nine transfers of the clear-flag path");
}

// 15. The two table objects are DISTINCT even though both have a +0x40 slot.
// The listing reads one table word out of what 0x0067cb20 returned and the
// other out of receiver+0xb54 (0x00c12340 vs 0x00c123ac), and the two +0x40
// calls are 0x00c1234c and 0x00c123b3. If the reconstruction used one type and
// one object, the +0x40 pair would be indistinguishable.
void case_the_two_slot_40_dispatches_reach_different_receivers() {
  fill_owner(g_owner);
  arm_owner(g_owner);
  reset_observer();
  arm_callees();

  run_current(0x1111u, 0x2222u, 0x01u);
  const int manager40 = index_of(kManagerSlot40);
  const int proto40 = index_of(kProtoSlot40);
  check(manager40 >= 0 && proto40 >= 0, "both +0x40 dispatches are reached");
  check(manager40 >= 0 && proto40 >= 0 &&
            g_calls[manager40].receiver != g_calls[proto40].receiver,
        "the two +0x40 dispatches reach different receivers");
  check(manager40 >= 0 && g_calls[manager40].receiver == kManagerObject,
        "the first is the manager root");
  check(proto40 >= 0 && g_calls[proto40].receiver == kPrototyperObject,
        "the second is the receiver's prototyper");
}

// 16. The six slot displacements the body reaches, and the two tables, are the
// machine's own set. Pinned from the encodings: each `MOV EAX,[EDX+disp]`
// immediate.
void case_the_slot_set_is_the_machines_slot_set() {
  // Each slot load is `8b 42 <disp8>`: opcode 0x8b, ModRM 0x42 (MOV EAX from
  // [EDX+disp8]), then the displacement. The disp8 sits one byte past the
  // ModRM, at the offsets computed above.
  const std::size_t slot_at[] = {
      kAtMovSlot40Manager, kAtMovSlot08, kAtMovSlot0c, kAtMovSlot14,
      kAtMovSlot18,        kAtMovSlot40, kAtMovSlot3c};
  const Word expected[] = {0x40u, 0x08u, 0x0cu, 0x14u, 0x18u, 0x40u, 0x3cu};
  for (std::size_t index = 0; index < 7; ++index) {
    check(kTargetBytes[slot_at[index]] == 0x8b &&
              kTargetBytes[slot_at[index] + 1] == 0x42,
          "the slot load is MOV EAX,dword ptr [EDX+disp8]");
    check_word(kTargetBytes[slot_at[index] + 2], expected[index],
               "the slot displacement the listing reads");
  }
  check(offsetof(OpaqueManagerVTable, slot_40) == 0x40u,
        "the manager table's slot_40 is the machine's slot_40");
  check(offsetof(OpaquePrototyperVTable, slot_08) == 0x08u,
        "the prototyper table's slot_08 is the machine's slot_08");
  check(offsetof(OpaquePrototyperVTable, slot_0c) == 0x0cu,
        "the prototyper table's slot_0c is the machine's slot_0c");
  check(offsetof(OpaquePrototyperVTable, slot_14) == 0x14u,
        "the prototyper table's slot_14 is the machine's slot_14");
  check(offsetof(OpaquePrototyperVTable, slot_18) == 0x18u,
        "the prototyper table's slot_18 is the machine's slot_18");
  check(offsetof(OpaquePrototyperVTable, slot_3c) == 0x3cu,
        "the prototyper table's slot_3c is the machine's slot_3c");
  check(offsetof(OpaquePrototyperVTable, slot_40) == 0x40u,
        "the prototyper table's slot_40 is the machine's slot_40");
}

// ===========================================================================
// MUTANTS: complete bodies differing from the reconstruction in exactly one
// way. Each is caught by the case named beside it; a survivor means that case
// is not testing what it claims.
// ===========================================================================

// M1: hoist receiver+0xb54 into a local, as a compiler proving the pointer
// invariant would. The listing re-reads it six times.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_hoisted_prototyper(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// M2: pass the RESOLVED argument to the prototyper's +0x40. 0x00c123b1 pushes
// EBP, the value read at 0x00c12324 before the aliasing out-parameter existed.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_resolved_at_slot_40(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, resolved);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// M3: sort the slot displacements. Every offset is individually right and the
// sequence is wrong: 0x3c before 0x40, where the listing has 0x40 first.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_sorted_slots(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// M4: invert the manager-result flag test. `CMP byte ptr [EBX+0x1c],0x1` + `JZ`
// stores for every value EXCEPT one; this stores for one only.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_inverted_flag(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) == 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// M5: make the return conditional on the cache store. 0x00c123e1 materialises
// EAX on the path BOTH ways, so a receiver whose manager flag is 1 still gets
// the object back.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_conditional_return(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
    return created;
  }
  return nullptr;
}

// M6: ADD a guard on the first argument on top of the real one. 0x00c12318
// compares `[ESI + 0xb54]` against zero and there is no second test anywhere in
// the body, so a null argument with a live prototyper must run the whole
// dispatch block. Written as an EXTRA test rather than a replacement, because a
// replacement would dereference a null receiver word and take the process down
// instead of failing a check -- a crash is not a refutation this harness can
// count.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_extra_argument_guard(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  if (argument0 == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 0.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// M7: pass a NON-ZERO float to the +0x14 slot. 0x00c1238a is FLDZ and
// 0x00c12392 is `FSTP float ptr [ESP]`, so the argument is the four bytes of a
// positive zero and nothing else. A model that passed 1.0f would be right about
// the width and wrong about the value, and only a bits-level check catches it.
extern "C" PKG_00C12310_THISCALL OpaqueCreated* mutant_nonzero_float(
    OpaqueOwner* self, Word argument0, Word argument1, std::uint8_t flag) {
  if (*word_at(self, 0xb54) == 0u) {
    return nullptr;
  }
  Word resolved = argument0;
  resolve_prototype_00c0c5b0(self, argument0, &resolved);
  OpaqueManager* const manager = manager_root_0067cb20();
  OpaqueManagerResult* const manager_result =
      table_of<OpaqueManagerVTable>(manager)->slot_40(manager, resolved);
  if (manager_result == nullptr) {
    return nullptr;
  }
  OpaquePrototyper* const prototyper =
      reinterpret_cast<OpaquePrototyper*>(*word_at(self, 0xb54));
  OpaqueCreated* const created = table_of<OpaquePrototyperVTable>(prototyper)
                                     ->slot_08(prototyper, resolved, 0u);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_0c(prototyper, created, 1u);
  if (flag != 0u) {
    table_of<OpaquePrototyperVTable>(prototyper)
        ->slot_14(prototyper, created, 1.0f);
  }
  table_of<OpaquePrototyperVTable>(prototyper)->slot_18(prototyper, created);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_40(prototyper, created, argument0);
  table_of<OpaquePrototyperVTable>(prototyper)
      ->slot_3c(prototyper, created, 0u);
  attach_created_object_00c10250(self, created, argument1, manager_result);
  if (*byte_at(manager_result, 0x1c) != 1u) {
    *word_at(self, 0xe88) = pointer_word(created);
  }
  return created;
}

// A case is a refutation only if it fails for the mutant. Each run points the
// suite at a wrong body, executes every case, and REQUIRES a non-zero failure
// count; a survivor means the case is not testing what it claims. The real body
// is restored afterwards so the mutant's failures never decide this run's exit.
int failures_of(Body body) {
  const int before = g_failures;
  g_report = false;
  g_body = body;
  case_stack_cleanup_is_the_callees();
  case_null_prototyper_exits_before_any_call();
  case_null_manager_result_exits_after_two_calls();
  case_call_sequence();
  case_flag_zero_skips_only_the_float_slot();
  case_flag_is_a_one_byte_test_against_zero();
  case_float_argument_is_four_bytes_of_positive_zero();
  case_argument_vectors();
  case_the_aliased_argument_is_re_read_not_copied();
  case_prototyper_is_re_read_before_every_dispatch();
  case_cache_store_is_conditional_on_the_manager_result_byte();
  case_the_flag_lives_on_the_manager_result_not_the_receiver();
  case_only_the_cache_word_is_written();
  case_every_exit_returns_what_the_listing_says();
  case_the_guard_tests_the_receiver_pointer_not_the_argument();
  case_the_two_slot_40_dispatches_reach_different_receivers();
  g_body = &create_cached_object_00c12310;
  g_report = true;
  const int produced = g_failures - before;
  g_failures = before;  // a mutant's failures are the point, not this suite's
  return produced;
}

}  // namespace openspore_reconstruction_pkg00c12310

int main() {
  using namespace openspore_reconstruction_pkg00c12310;

  case_stack_cleanup_is_the_callees();
  case_null_prototyper_exits_before_any_call();
  case_null_manager_result_exits_after_two_calls();
  case_call_sequence();
  case_flag_zero_skips_only_the_float_slot();
  case_flag_is_a_one_byte_test_against_zero();
  case_float_argument_is_four_bytes_of_positive_zero();
  case_argument_vectors();
  case_the_aliased_argument_is_re_read_not_copied();
  case_prototyper_is_re_read_before_every_dispatch();
  case_cache_store_is_conditional_on_the_manager_result_byte();
  case_the_flag_lives_on_the_manager_result_not_the_receiver();
  case_only_the_cache_word_is_written();
  case_every_exit_returns_what_the_listing_says();
  case_the_guard_tests_the_receiver_pointer_not_the_argument();
  case_the_two_slot_40_dispatches_reach_different_receivers();
  case_the_slot_set_is_the_machines_slot_set();

  const int caught[] = {
      failures_of(mutant_hoisted_prototyper),
      failures_of(mutant_resolved_at_slot_40),
      failures_of(mutant_sorted_slots),
      failures_of(mutant_inverted_flag),
      failures_of(mutant_conditional_return),
      failures_of(mutant_extra_argument_guard),
      failures_of(mutant_nonzero_float),
  };
  static_assert(sizeof(caught) / sizeof(caught[0]) == 7, "seven mutants");
  for (std::size_t index = 0; index < 7; ++index) {
    std::printf("mutant %zu caught by %d check(s)\n", index + 1u,
                caught[index]);
    check(caught[index] > 0, "every mutant must be caught");
  }

  std::printf("%d check(s) run, %d failure(s)\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
