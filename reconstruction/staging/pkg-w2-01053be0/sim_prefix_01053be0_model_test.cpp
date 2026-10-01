// PKG-W2-01053BE0 -- model test for VA 0x01053be0
//
// WHAT THIS TEST IS, AND WHAT IT DELIBERATELY IS NOT.
//
// It is not a self-comparison. Every assertion is pinned to one of two things
// derived independently of the reconstruction:
//
//   * the IMAGE, through the 288-byte transcript carried in
//     sim_prefix_01053be0.hpp. Cases A1..A13 re-derive every direct CALL target,
//     every displacement, every branch displacement and both float constants
//     FROM THOSE BYTES, with arithmetic written here rather than imported from
//     the header, and compare the results against literals written here. A
//     header constant that drifts from the transcript is caught; a header
//     constant compared with itself would not be.
//
//   * LITERALS written separately in this file, for the behavioural cases. The
//     expected triples are typed out by hand, not recorded from a run.
//
// The observers are defined HERE and nowhere else. The reconstruction names
// them; this file supplies their behaviour. That is what makes the call-sequence
// cases observable: the entry's calls are recorded in order and compared with a
// sequence written out by hand below.
//
// NO BARE ASSEMBLY, AND THEREFORE NO REGISTER CLAIM. The entry is ordinary C++
// and so is this probe, so nothing here writes ESI, EDI, EBX or EBP. The
// machine's save and restore of those four registers is a listing fact recorded
// in the header and is not asserted here, because a compiler is free to
// allocate them inside a C++ function and still restore them.

#include "sim_prefix_01053be0.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>
#include <vector>

namespace os = openspore::reconstruction::pkg_w2_01053be0;

namespace {

using Triple = os::Triple;

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* what, int line) {
  ++g_checks;
  if (condition) {
    return;
  }
  ++g_failures;
  std::printf("FAIL line %d: %s\n", line, what);
}

constexpr int kManagerCallBudget = 8;
constexpr int kTripleCount = 8;
constexpr std::size_t kModelImageBytes = 0x40u;

// The two image words, written here from the GhidraMCP /read_memory result and
// deliberately NOT taken from the header, so A8 can compare the header's floats
// against the image rather than against themselves.
constexpr std::uint32_t kImageFarFloatBits = 0x43480000u;   // 0x01477fbc
constexpr std::uint32_t kImageNearFloatBits = 0x42480000u;  // 0x013f1cac

// One byte image that plays both parts the body reads: it is the receiver (the
// model loads its word 0), and that word is a pointer back to itself, so the
// same bytes are the table the model then reads at +0x24 and at +0x2c. The two
// function pointers are written into it by memcpy, which is exactly what the
// reconstruction reads back out of memory.
struct TableImage {
  std::uint32_t word0;
  std::uint8_t gap_to_probe[0x24u - 4u];
  std::uint32_t probe_call;
  std::uint8_t gap_to_first[0x2cu - 0x24u - 4u];
  std::uint32_t first_call;
};

static_assert(offsetof(TableImage, word0) == 0x00u, "the receiver load is a bare [EDI]");
static_assert(offsetof(TableImage, probe_call) == 0x24u, "MOV EDX,[EAX+0x24] reads this word");
static_assert(offsetof(TableImage, first_call) == 0x2cu, "MOV EAX,[EDX+0x2c] reads this word");

// -- the world the observers read ---------------------------------------------

struct Call {
  const char* name;
  const void* pointer_arg;
  std::uint32_t arg0;
  std::uint32_t arg2;
};

std::vector<Call> g_calls;

struct World {
  void* root = nullptr;
  void* model = nullptr;
  int manager_calls = 0;
  bool manager_available[kManagerCallBudget] = {};
  void* manager_result[kManagerCallBudget] = {};
  Triple project[kTripleCount] = {};
  Triple screen[kTripleCount] = {};
  Triple surface[kTripleCount] = {};
  Triple produced[kTripleCount] = {};
  int probe_not_ready_count = 0;
  // last observed values, so a case can assert the argument shape
  void* probe_self = nullptr;
  std::uint32_t probe_arg0 = 0;
  std::uint32_t probe_arg1_bits = 0;
  std::uint32_t probe_arg2 = 0;
  void* project_self = nullptr;
  Triple project_local_copy[kTripleCount] = {};
  const void* project_cell = nullptr;
  void* screen_self = nullptr;
  const void* screen_cell = nullptr;
};

World g_world;

int g_probe_invocations = 0;

void record(const char* name, const void* pointer_arg, std::uint32_t arg0, std::uint32_t arg2) {
  Call entry;
  entry.name = name;
  entry.pointer_arg = pointer_arg;
  entry.arg0 = arg0;
  entry.arg2 = arg2;
  g_calls.push_back(entry);
}

int count_calls(const char* name) {
  int total = 0;
  for (std::size_t i = 0; i < g_calls.size(); ++i) {
    if (std::strcmp(g_calls[i].name, name) == 0) {
      ++total;
    }
  }
  return total;
}

std::size_t index_of(const char* name) {
  for (std::size_t i = 0; i < g_calls.size(); ++i) {
    if (std::strcmp(g_calls[i].name, name) == 0) {
      return i;
    }
  }
  return g_calls.size();
}

bool all_floats(const Triple* triple, float a, float b, float c) {
  return triple[0] == a && triple[1] == b && triple[2] == c;
}

unsigned char g_token_a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
unsigned char g_token_b[8] = {9, 10, 11, 12, 13, 14, 15, 16};

void* token_a() { return static_cast<void*>(g_token_a); }
void* token_b() { return static_cast<void*>(g_token_b); }

// -- transcript arithmetic, written here, not imported ------------------------

std::uint32_t word32_at(std::size_t offset) {
  return static_cast<std::uint32_t>(os::kTargetBytes[offset]) |
         (static_cast<std::uint32_t>(os::kTargetBytes[offset + 1]) << 8) |
         (static_cast<std::uint32_t>(os::kTargetBytes[offset + 2]) << 16) |
         (static_cast<std::uint32_t>(os::kTargetBytes[offset + 3]) << 24);
}

std::uint32_t call_target_from(std::uint32_t site) {
  const std::size_t offset = static_cast<std::size_t>(site - os::kSpanFirstByte);
  const std::int32_t rel = static_cast<std::int32_t>(word32_at(offset + 1));
  return site + 5u + static_cast<std::uint32_t>(rel);
}

std::uint32_t rel8_target_from(std::uint32_t site) {
  const std::size_t offset = static_cast<std::size_t>(site - os::kSpanFirstByte);
  const std::int32_t rel = static_cast<std::int8_t>(os::kTargetBytes[offset + 1]);
  return site + 2u + static_cast<std::uint32_t>(rel);
}

std::size_t offset_of(std::uint32_t address) {
  return static_cast<std::size_t>(address - os::kSpanFirstByte);
}

// -- A1..A13 ------------------------------------------------------------------

void transcript_cases() {
  // A1 -- every direct CALL site re-derives its own target from the bytes. The
  // expected pairs are written out here from the evidence listing.
  const std::uint32_t sites[10] = {0x01053be9u, 0x01053bf0u, 0x01053c3bu, 0x01053c4eu, 0x01053c55u,
                                   0x01053c6cu, 0x01053c7au, 0x01053c81u, 0x01053cceu, 0x01053cd5u};
  const std::uint32_t targets[10] = {0x00ffbe50u, 0x00a1ad60u, 0x00b3d350u, 0x00b3d350u, 0x00b815a0u,
                                     0x00b3d350u, 0x00b3d350u, 0x00b81720u, 0x00b3d350u, 0x00b81780u};
  for (int i = 0; i < 10; ++i) {
    check(os::kTargetBytes[offset_of(sites[i])] == 0xe8u,
          "every direct call site begins with the e8 opcode", __LINE__);
    const std::uint32_t derived = call_target_from(sites[i]);
    char text[160];
    std::snprintf(text, sizeof text, "call site %08x re-derives 0x%08x from the transcript bytes",
                  sites[i], derived);
    check(derived == targets[i], text, __LINE__);
  }

  // A2 -- the six distinct targets are the header's set, and the count is six.
  int distinct = 0;
  for (int i = 0; i < 10; ++i) {
    bool repeated = false;
    for (int j = 0; j < i; ++j) {
      repeated = repeated || targets[j] == targets[i];
    }
    if (repeated) {
      continue;
    }
    ++distinct;
    bool found = false;
    for (int k = 0; k < os::kDirectCalleeCount; ++k) {
      found = found || os::kDirectCallees[k] == targets[i];
    }
    char text[128];
    std::snprintf(text, sizeof text, "derived callee 0x%08x is in the header's set", targets[i]);
    check(found, text, __LINE__);
  }
  check(distinct == 6, "the span names six distinct direct callees", __LINE__);

  // A3 -- the receiver load carries no displacement; the probe's target load and
  // the model's own two displacements do.
  check(os::kTargetBytes[offset_of(0x01053ca0u)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053ca0u) + 1] == 0x07u,
        "0x01053ca0 is 8b 07, MOV EAX,[EDI], with no displacement byte", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053ca2u)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053ca2u) + 1] == 0x50u &&
            os::kTargetBytes[offset_of(0x01053ca2u) + 2] == 0x24u,
        "0x01053ca2 is 8b 50 24, MOV EDX,[EAX+0x24]", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053c0eu)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053c0eu) + 1] == 0x50u &&
            os::kTargetBytes[offset_of(0x01053c0eu) + 2] == 0x34u,
        "0x01053c0e is 8b 50 34, MOV EDX,[EAX+0x34]", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053c11u)] == 0x83u &&
            os::kTargetBytes[offset_of(0x01053c11u) + 1] == 0xc0u &&
            os::kTargetBytes[offset_of(0x01053c11u) + 2] == 0x34u,
        "0x01053c11 is 83 c0 34, ADD EAX,0x34", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053c16u)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053c16u) + 1] == 0x42u &&
            os::kTargetBytes[offset_of(0x01053c16u) + 2] == 0x2cu,
        "0x01053c16 is 8b 42 2c, MOV EAX,[EDX+0x2c]", __LINE__);

  // A4 -- the immediates the entry relies on.
  check(os::kTargetBytes[offset_of(0x01053ca5u)] == 0x6au &&
            os::kTargetBytes[offset_of(0x01053ca5u) + 1] == 0x01u,
        "0x01053ca5 is PUSH 0x1", __LINE__);
  check(word32_at(offset_of(0x01053cdau) + 2) == 0x3e8u,
        "CMP EBX,0x3e8 at 0x01053cda carries the immediate 1000", __LINE__);
  check(word32_at(offset_of(0x01053cf3u) + 2) == 0x3e8u,
        "CMP EBX,0x3e8 at 0x01053cf3 carries the same immediate 1000", __LINE__);

  // A5 -- the two ESP-relative reads, resolved here against the prologue bytes.
  check(os::kTargetBytes[0] == 0x83u && os::kTargetBytes[1] == 0xecu && os::kTargetBytes[2] == 0x18u,
        "the prologue opens with SUB ESP,0x18 (83 ec 18)", __LINE__);
  check(os::kTargetBytes[3] == 0x53u && os::kTargetBytes[4] == 0x55u &&
            os::kTargetBytes[5] == 0x56u && os::kTargetBytes[6] == 0x57u,
        "the next four bytes are four one-byte pushes", __LINE__);
  // Four PUSH reg instructions are four bytes EACH, so the frame is 0x18 + 16.
  const std::int32_t prologue = -0x18 - 4 * 4;
  check(prologue == -0x28, "SUB ESP,0x18 plus four one-word pushes is entry_ESP-0x28", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053bf5u)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053bf5u) + 1] == 0x74u &&
            os::kTargetBytes[offset_of(0x01053bf5u) + 2] == 0x24u &&
            os::kTargetBytes[offset_of(0x01053bf5u) + 3] == 0x2cu,
        "0x01053bf5 is 8b 74 24 2c, MOV ESI,[ESP+0x2c]", __LINE__);
  check(0x2c + prologue == 0x04, "ESP+0x2c with ESP = entry_ESP-0x28 is entry_ESP+0x4", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053c96u)] == 0x8bu &&
            os::kTargetBytes[offset_of(0x01053c96u) + 1] == 0x6cu &&
            os::kTargetBytes[offset_of(0x01053c96u) + 2] == 0x24u &&
            os::kTargetBytes[offset_of(0x01053c96u) + 3] == 0x30u,
        "0x01053c96 is 8b 6c 24 30, MOV EBP,[ESP+0x30]", __LINE__);
  check(0x30 + prologue == 0x08, "ESP+0x30 with ESP = entry_ESP-0x28 is entry_ESP+0x8", __LINE__);

  // A6 -- the branch graph, re-derived from the rel8 bytes. Five conditional
  // targets are inside the recovered span and one is not; the span's single
  // unconditional direct jump is inside it too.
  const std::uint32_t inside_sites[5] = {0x01053c0cu, 0x01053c42u, 0x01053c73u, 0x01053cb0u,
                                          0x01053cf0u};
  const std::uint32_t inside_targets[5] = {0x01053c6cu, 0x01053c96u, 0x01053c96u, 0x01053cf3u,
                                           0x01053ca0u};
  for (int i = 0; i < 5; ++i) {
    const std::uint32_t derived = rel8_target_from(inside_sites[i]);
    char text[160];
    std::snprintf(text, sizeof text, "branch at %08x re-derives 0x%08x from the transcript bytes",
                  inside_sites[i], derived);
    check(derived == inside_targets[i], text, __LINE__);
    check(derived <= os::kSpanLastByte, "that branch target is inside the recovered span", __LINE__);
  }
  check(rel8_target_from(0x01053cf9u) == 0x01053d3bu,
        "the JLE at 0x01053cf9 re-derives 0x01053d3b, the one branch that leaves the span",
        __LINE__);
  check(0x01053d3bu > os::kSpanLastByte, "0x01053d3b lies outside the 288 recovered bytes", __LINE__);
  check(rel8_target_from(0x01053c6au) == 0x01053c96u,
        "the span's one unconditional direct jump re-derives 0x01053c96", __LINE__);
  check(0x01053c96u <= os::kSpanLastByte,
        "0x01053c96 is inside the recovered span, so that jump is control flow and not a tail hop",
        __LINE__);

  // A7 -- no RET opcode byte anywhere in the 288 bytes.
  int ret_bytes = 0;
  for (std::size_t i = 0; i < os::kSpanBytes; ++i) {
    const std::uint8_t byte = os::kTargetBytes[i];
    ret_bytes += (byte == 0xc2u || byte == 0xc3u) ? 1 : 0;
  }
  check(ret_bytes == 0, "no c2 or c3 byte appears anywhere in the 288-byte transcript", __LINE__);

  // A8 -- the two float constants, against the words read out of the image.
  std::uint32_t encoded = 0;
  std::memcpy(&encoded, &os::kFarStackFloat, sizeof encoded);
  check(encoded == kImageFarFloatBits,
        "the header's far constant re-encodes to 00 00 48 43, the image's own word", __LINE__);
  std::memcpy(&encoded, &os::kNearStackFloat, sizeof encoded);
  check(encoded == kImageNearFloatBits,
        "the header's near constant re-encodes to 00 00 48 42, the image's own word", __LINE__);
  check(word32_at(offset_of(0x01053cb2u) + 2) == 0x01477fbcu,
        "FLD float ptr [0x01477fbc] carries that disp32", __LINE__);
  check(word32_at(offset_of(0x01053cc3u) + 2) == 0x013f1cacu,
        "FLD float ptr [0x013f1cac] carries that disp32", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053cb2u)] == 0xd9u &&
            os::kTargetBytes[offset_of(0x01053cb2u) + 1] == 0x05u,
        "0x01053cb2 is d9 05, FLD dword ptr [disp32]", __LINE__);

  // A9 -- the two computed transfers.
  check(os::kTargetBytes[offset_of(0x01053c19u)] == 0xffu &&
            os::kTargetBytes[offset_of(0x01053c19u) + 1] == 0xd0u,
        "0x01053c19 is ff d0, CALL EAX", __LINE__);
  check(os::kTargetBytes[offset_of(0x01053cacu)] == 0xffu &&
            os::kTargetBytes[offset_of(0x01053cacu) + 1] == 0xd2u,
        "0x01053cac is ff d2, CALL EDX", __LINE__);

  // A10 -- the last recovered instruction, and what follows the span's last byte.
  check(os::kTargetBytes[offset_of(0x01053cfdu)] == 0x8du &&
            os::kTargetBytes[offset_of(0x01053cfdu) + 1] == 0x49u &&
            os::kTargetBytes[offset_of(0x01053cfdu) + 2] == 0x00u,
        "0x01053cfd is 8d 49 00, LEA ECX,[ECX]: three bytes that transfer nothing",
        __LINE__);
  check(offset_of(0x01053cfdu) + 3 == os::kSpanBytes,
        "that instruction ends exactly on the 288th byte, so control runs off the span",
        __LINE__);
  check(os::kSpanEndExclusive == 0x01053d00u, "the span's exclusive end is 0x01053d00", __LINE__);

  // A11 -- the record's ABI data, against literals written here.
  check(os::kDerivedVerdictIsAbiUnknown, "the derived record's verdict is ABI_UNKNOWN", __LINE__);
  check(os::kCandidateConventionCount == 4,
        "the derived record names four candidate conventions", __LINE__);
  check(os::kConventionDetermined == false, "no convention is determined", __LINE__);
  check(os::kCleanupDetermined == false, "the derived record's cleanup is undetermined", __LINE__);
  check(os::kCleanupBytes == 0,
        "cleanup.bytes is null in the record, which is not the same as zero bytes", __LINE__);
  check(os::kCleanupSideKnown == false, "cleanup.side is null in the record", __LINE__);
  check(os::kStructReturnDecided == false,
        "the hidden-struct-return versus out-parameter question is undecided", __LINE__);
  check(os::kStructReturnSlotOffset == 4, "the slot the record flags is entry_ESP+0x4", __LINE__);
  check(os::kReceiverPresent && os::kReceiverRegisterId == 1,
        "a receiver is present and arrives in ECX", __LINE__);
  check(os::kReceiverIsAliased, "the receiver record's shape is R-ALIAS", __LINE__);
  check(os::kReceiverBoundsOnly, "the receiver record is bounds_only", __LINE__);
  check(os::kReceiverOnlyOffset == 0u, "the receiver record enumerates offset zero only", __LINE__);
  check(os::kReceiverMaxOffset == 0, "and its max_offset is zero", __LINE__);
  check(os::kReceiverWrittenThrough == 0, "nothing is written through the receiver", __LINE__);
  check(os::kReceiverDereferenceCount == 1,
        "the body dereferences the receiver once, which is the load A3 found", __LINE__);
  check(os::kReturnWidthDetermined == false && os::kReturnTypeDetermined == false,
        "no return width and no return type are determined by the record", __LINE__);
  check(os::kReturnRegisterClaimedSt0, "the record's return sub-record names ST0", __LINE__);
  check(os::kTailHopPresent == false && os::kTailTargetAsserted == false,
        "no tail hop is present and none is asserted", __LINE__);
  check(os::kTailTargetFieldProvablyWrong,
        "the repository states a pre-existing tail target is provably wrong here", __LINE__);

  // A12 -- the header's displacements, against the literals A3 and A4 read.
  check(os::kReceiverTableOffset == 0u && os::kReceiverCallWordOffset == 0x24u &&
            os::kModelTableWordOffset == 0x34u && os::kModelSelfOffset == 0x34u &&
            os::kTableCallWordOffset == 0x2cu && os::kProbeFirstArgument == 1u &&
            os::kIterationLimit == 1000u,
        "the header's displacements agree with the transcript bytes just checked", __LINE__);

  // A13 -- the header's frame arithmetic, against the same arithmetic done here.
  check(os::kPrologueDelta == -0x28, "the header's prologue delta is -0x28", __LINE__);
  check(os::kFrameSubBytes == 24u && os::kSavedRegisterPushes == 4,
        "the header's frame constants match SUB ESP,0x18 and four pushes", __LINE__);
  check(os::kOutParameterEntryOffset == 0x04 && os::kProbeSecondWordEntryOffset == 0x08,
        "the two incoming stack words the body reads are entry_ESP+0x4 and entry_ESP+0x8", __LINE__);
  check(os::kUntouchedCellEntryOffset == -0x0c,
        "the address both LEA sites hand to 0x00b3d350 is entry_ESP-0x0c", __LINE__);
  check(os::kLocalTripleEntryOffset == -0x18,
        "the local triple the model-present arm fills is at entry_ESP-0x18", __LINE__);
  check(os::kStackSlotReadsInSpan == 2,
        "the span reads the incoming argument area twice, not once", __LINE__);
  check(os::kConditionalBranchCount == 6 && os::kUnconditionalDirectJumpCount == 1,
        "six conditional branches and one unconditional direct jump", __LINE__);
  check(os::kComputedTransferCount == 2, "two computed transfers", __LINE__);
  check(os::kInputManagerCallSiteCount == 5,
        "0x00b3d350 is called five times in the span", __LINE__);
}

// -- B1..B9 -------------------------------------------------------------------

void reset() {
  g_world = World();
  g_calls.clear();
  g_probe_invocations = 0;
}

// -- the two computed transfers -----------------------------------------------

using FirstFn = const Triple* (*)(void*);
using ProbeFn = std::uint32_t (*)(void*, std::uint32_t, Triple*, std::uint32_t);

const Triple* first_target(void* self) {
  record("first_target", self, 0, 0);
  return g_world.produced;
}

std::uint32_t probe_target(void* self, std::uint32_t arg0, Triple* arg1, std::uint32_t arg2) {
  record("probe_target", arg1, arg0, arg2);
  g_world.probe_self = self;
  g_world.probe_arg0 = arg0;
  g_world.probe_arg2 = arg2;
  std::memcpy(&g_world.probe_arg1_bits, &arg1, sizeof arg1);
  ++g_probe_invocations;
  return (g_probe_invocations <= g_world.probe_not_ready_count) ? 0u : 1u;
}

// Builds the byte image: the receiver is the TableImage itself, whose word 0 is
// a pointer back to itself, and whose words at +0x24 and +0x2c are the two
// computed targets. `model` is a 0x40-byte buffer whose word at +0x34 is the
// TableImage's address.
void arm(std::uint32_t* model, TableImage* image) {
  if (model != nullptr) {
    std::memset(model, 0, kModelImageBytes);
  }
  std::memset(image, 0, sizeof *image);
  FirstFn first = &first_target;
  ProbeFn probe = &probe_target;
  std::memcpy(&image->first_call, &first, sizeof first);
  std::memcpy(&image->probe_call, &probe, sizeof probe);
  image->word0 = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(image));
  if (model != nullptr) {
    model[os::kModelTableWordOffset / 4u] =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(image));
  }
}

void behaviour_cases() {
  // B1 -- the model-present arm, with the manager present.
  {
    reset();
    alignas(4) std::uint32_t model[0x10];
    TableImage image;
    arm(model, &image);
    Triple out[os::kTripleWords];

    g_world.root = token_a();
    g_world.model = static_cast<void*>(model);
    g_world.produced[0] = 7.0f;
    g_world.produced[1] = 8.0f;
    g_world.produced[2] = 9.0f;
    g_world.manager_available[0] = true;
    g_world.manager_result[0] = token_a();
    g_world.manager_available[1] = true;
    g_world.manager_result[1] = token_b();
    g_world.project[0] = 11.0f;
    g_world.project[1] = 12.0f;
    g_world.project[2] = 13.0f;
    g_world.probe_not_ready_count = 0;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out,
                             0x5a5a5a5au);

    check(all_floats(out, 11.0f, 12.0f, 13.0f),
          "B1: the model-present arm stores (11,12,13) through the caller's word", __LINE__);
    check(count_calls("callee_00ffbe50") == 1, "B1: 0x00ffbe50 runs once", __LINE__);
    check(count_calls("callee_00a1ad60") == 1, "B1: 0x00a1ad60 runs once", __LINE__);
    check(count_calls("callee_00b3d350") == 2,
          "B1: 0x00b3d350 runs TWICE on this arm, once for the gate and once for the "
          "argument",
          __LINE__);
    check(count_calls("callee_00b815a0") == 1, "B1: 0x00b815a0 runs once", __LINE__);
    check(count_calls("callee_00b81720") == 0, "B1: 0x00b81720 never runs on this arm", __LINE__);
    check(count_calls("first_target") == 1, "B1: the computed call at 0x01053c19 runs once", __LINE__);
    check(count_calls("probe_target") == 1, "B1: the probe runs once when it answers ready", __LINE__);
    check(g_world.project_self == token_b(),
          "B1: 0x00b815a0 receives the SECOND 0x00b3d350 result, not the first", __LINE__);
    check(all_floats(g_world.project_local_copy, 7.0f, 8.0f, 9.0f),
          "B1: 0x00b815a0's first stack word is the local triple (7,8,9)", __LINE__);
    check(g_calls.size() == 7 && std::strcmp(g_calls[0].name, "callee_00ffbe50") == 0 &&
              std::strcmp(g_calls[1].name, "callee_00a1ad60") == 0 &&
              std::strcmp(g_calls[2].name, "first_target") == 0 &&
              std::strcmp(g_calls[3].name, "callee_00b3d350") == 0 &&
              std::strcmp(g_calls[4].name, "callee_00b3d350") == 0 &&
              std::strcmp(g_calls[5].name, "callee_00b815a0") == 0 &&
              std::strcmp(g_calls[6].name, "probe_target") == 0,
          "B1: the whole call sequence is the one the listing spells, in order", __LINE__);
    check(g_world.probe_arg0 == 1u, "B1: the probe's first stack word is the immediate 1", __LINE__);
    check(g_world.probe_arg2 == 0x5a5a5a5au,
          "B1: the probe's third stack word is the caller's second word, 0x5a5a5a5a", __LINE__);
    check(g_world.probe_arg1_bits == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(out)),
          "B1: the probe's second stack word is the caller's out-parameter pointer", __LINE__);
    check(g_world.probe_self == static_cast<void*>(&image),
          "B1: the probe's ECX is the receiver the caller supplied", __LINE__);
  }

  // B2 -- the model-present arm, but the second manager query answers 0.
  {
    reset();
    alignas(4) std::uint32_t model[0x10];
    TableImage image;
    arm(model, &image);
    Triple out[os::kTripleWords];

    g_world.model = static_cast<void*>(model);
    g_world.produced[0] = 7.0f;
    // The gate at 0x01053c42 tests the FIRST 0x00b3d350 result, not the second.
    g_world.manager_available[0] = false;
    g_world.manager_result[0] = nullptr;
    g_world.manager_available[1] = true;
    g_world.manager_result[1] = token_b();

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(all_floats(out, 0.0f, 0.0f, 0.0f),
          "B2: with the gate shut the out word keeps the three zero stores", __LINE__);
    check(count_calls("callee_00b815a0") == 0, "B2: the JZ at 0x01053c42 skips 0x00b815a0", __LINE__);
    check(count_calls("callee_00b3d350") == 1,
          "B2: the gate itself is the one call to 0x00b3d350; the second never happens", __LINE__);
    check(count_calls("first_target") == 1,
          "B2: the computed call at 0x01053c19 still runs before the gate", __LINE__);
    check(count_calls("probe_target") == 1,
          "B2: the loop still runs and the probe is still reached", __LINE__);
  }

  // B3 -- the model-absent arm.
  {
    reset();
    TableImage image;
    arm(nullptr, &image);
    Triple out[os::kTripleWords];

    g_world.model = nullptr;
    g_world.manager_available[0] = true;
    g_world.manager_result[0] = token_a();
    g_world.manager_available[1] = true;
    g_world.manager_result[1] = token_b();
    g_world.screen[0] = 21.0f;
    g_world.screen[1] = 22.0f;
    g_world.screen[2] = 23.0f;
    g_world.probe_not_ready_count = 0;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(all_floats(out, 21.0f, 22.0f, 23.0f),
          "B3: the model-absent arm stores (21,22,23) through the caller's word", __LINE__);
    check(count_calls("callee_00b81720") == 1, "B3: 0x00b81720 runs once on this arm", __LINE__);
    check(count_calls("callee_00b815a0") == 0,
          "B3: 0x00b815a0 never runs when the model word is null", __LINE__);
    check(count_calls("first_target") == 0,
          "B3: the computed call at 0x01053c19 belongs to the model-present arm only", __LINE__);
    check(count_calls("callee_00b3d350") == 2, "B3: 0x00b3d350 runs twice here as well", __LINE__);
    check(g_world.screen_self == token_b(),
          "B3: 0x00b81720 receives the second 0x00b3d350 result", __LINE__);
  }

  // B4 -- the loop answers ready on its 1000th invocation.
  {
    reset();
    TableImage image;
    arm(nullptr, &image);
    Triple out[os::kTripleWords];

    g_world.model = nullptr;
    g_world.manager_available[0] = true;
    g_world.manager_available[1] = true;
    g_world.probe_not_ready_count = 999;
    g_world.surface[0] = 31.0f;
    g_world.surface[1] = 32.0f;
    g_world.surface[2] = 33.0f;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(count_calls("probe_target") == 1000,
          "B4: the probe runs exactly 1000 times before the loop gives up", __LINE__);
    check(count_calls("callee_00b81780") == 999,
          "B4: 0x00b81780 runs on the 999 not-ready iterations and not on the 1000th", __LINE__);
    check(all_floats(out, 31.0f, 32.0f, 33.0f), "B4: the loop's last store wins: (31,32,33)", __LINE__);
  }

  // B5 -- the loop never answers ready: the 1000th iteration still stores.
  {
    reset();
    TableImage image;
    arm(nullptr, &image);
    Triple out[os::kTripleWords];

    g_world.model = nullptr;
    g_world.manager_available[0] = true;
    g_world.manager_available[1] = true;
    g_world.probe_not_ready_count = 1000;
    g_world.surface[0] = 41.0f;
    g_world.surface[1] = 42.0f;
    g_world.surface[2] = 43.0f;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(count_calls("probe_target") == 1000,
          "B5: the probe runs 1000 times when it never answers ready", __LINE__);
    check(count_calls("callee_00b81780") == 1000,
          "B5: the 1000th iteration stores BEFORE the bound is compared", __LINE__);
    check(all_floats(out, 41.0f, 42.0f, 43.0f),
          "B5: the caller's word holds (41,42,43) from the final iteration", __LINE__);
  }

  // B6 -- the model-present arm and the loop together: the loop overwrites the
  // arm's store, and the arm's own twelve zero bytes never come back.
  {
    reset();
    alignas(4) std::uint32_t model[0x10];
    TableImage image;
    arm(model, &image);
    Triple out[os::kTripleWords];

    g_world.model = static_cast<void*>(model);
    g_world.produced[0] = 1.0f;
    g_world.manager_available[0] = true;
    g_world.manager_result[0] = token_a();
    g_world.manager_available[1] = true;
    g_world.manager_result[1] = token_b();
    g_world.project[0] = 51.0f;
    g_world.project[1] = 52.0f;
    g_world.project[2] = 53.0f;
    g_world.probe_not_ready_count = 2;
    g_world.surface[0] = 61.0f;
    g_world.surface[1] = 62.0f;
    g_world.surface[2] = 63.0f;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(all_floats(out, 61.0f, 62.0f, 63.0f),
          "B6: the loop overwrites the arm's (51,52,53) with (61,62,63)", __LINE__);
    check(count_calls("callee_00b815a0") == 1 && count_calls("callee_00b81780") == 2,
          "B6: the arm's callee runs once and the loop's runs twice", __LINE__);
    check(count_calls("probe_target") == 3,
          "B6: two not-ready answers and then one ready", __LINE__);
  }

  // B7 -- neither arm's gate opens and the probe is ready immediately: only the
  // three zero stores survive.
  {
    reset();
    TableImage image;
    arm(nullptr, &image);
    Triple out[os::kTripleWords];

    out[0] = 99.0f;
    out[1] = 98.0f;
    out[2] = 97.0f;
    g_world.model = nullptr;
    g_world.manager_available[0] = false;
    g_world.probe_not_ready_count = 0;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(all_floats(out, 0.0f, 0.0f, 0.0f),
          "B7: with both gates shut the three zero stores are what the caller sees", __LINE__);
    check(count_calls("callee_00b3d350") == 1,
          "B7: on the model-absent arm 0x00b3d350 is called once and gates 0x00b81720", __LINE__);
    check(count_calls("callee_00b81720") == 0, "B7: 0x00b81720 is gated off", __LINE__);
    check(count_calls("probe_target") == 1, "B7: the probe is reached once and answers ready", __LINE__);
  }

  // B8 -- the computed call's ECX is model+0x34, not the model word itself.
  {
    reset();
    alignas(4) std::uint32_t model[0x10];
    TableImage image;
    arm(model, &image);
    Triple out[os::kTripleWords];

    g_world.model = static_cast<void*>(model);
    g_world.produced[0] = 71.0f;
    g_world.manager_available[0] = true;
    g_world.manager_available[1] = true;
    g_world.project[0] = 72.0f;
    g_world.probe_not_ready_count = 0;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    const std::size_t where = index_of("first_target");
    check(where < g_calls.size(), "B8: the computed call ran", __LINE__);
    check(g_calls[where].pointer_arg ==
              reinterpret_cast<const void*>(reinterpret_cast<const unsigned char*>(model) +
                                        os::kModelSelfOffset),
          "B8: ADD EAX,0x34 puts model+0x34 in ECX, not the model word", __LINE__);
    check(g_calls[where].pointer_arg != g_world.model,
          "B8: the computed call's ECX is not the model word the caller supplied", __LINE__);
  }

  // B9 -- the caller's word is the one written, and the untouched cell handed to
  // 0x00b3d350 is not it.
  {
    reset();
    TableImage image;
    arm(nullptr, &image);
    Triple out[os::kTripleWords];
    Triple decoy[os::kTripleWords];

    decoy[0] = -1.0f;
    decoy[1] = -1.0f;
    decoy[2] = -1.0f;
    g_world.model = nullptr;
    g_world.manager_available[0] = true;
    g_world.manager_result[0] = token_a();
    g_world.manager_available[1] = true;
    g_world.manager_result[1] = token_b();
    g_world.screen[0] = 81.0f;
    g_world.screen[1] = 82.0f;
    g_world.screen[2] = 83.0f;
    g_world.probe_not_ready_count = 0;

    os::reconstruct_01053be0(reinterpret_cast<os::Receiver*>(static_cast<void*>(&image)), out, 0u);

    check(all_floats(out, 81.0f, 82.0f, 83.0f), "B9: the caller's word is written", __LINE__);
    check(decoy[0] == -1.0f && decoy[1] == -1.0f && decoy[2] == -1.0f,
          "B9: the harness's own decoy word is untouched, so the entry wrote the caller's "
          "word and not a buffer of its own",
          __LINE__);
    check(g_world.screen_cell != static_cast<const void*>(out),
          "B9: the word 0x00b81720 is handed is the untouched cell, not the out word", __LINE__);
    check(g_world.probe_arg1_bits == static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(out)),
          "B9: the probe's second stack word is still the caller's out word", __LINE__);
  }
}

}  // namespace

namespace openspore::reconstruction::pkg_w2_01053be0 {


void* callee_00ffbe50() {
  record("callee_00ffbe50", nullptr, 0, 0);
  return g_world.root;
}

void* callee_00a1ad60(void* root) {
  record("callee_00a1ad60", root, 0, 0);
  return g_world.model;
}

void* callee_00b3d350() {
  record("callee_00b3d350", nullptr, 0, 0);
  const int index =
      g_world.manager_calls < kManagerCallBudget ? g_world.manager_calls : kManagerCallBudget - 1;
  g_world.manager_calls += 1;
  if (g_world.manager_available[index]) {
    return g_world.manager_result[index];
  }
  return nullptr;
}

const Triple* callee_00b815a0(void* self, const Triple* local, void* cell) {
  record("callee_00b815a0", local, 0, 0);
  g_world.project_self = self;
  g_world.project_cell = cell;
  // The word is copied HERE, while the entry's frame is still live. Reading it
  // after the entry returns would be reading a dead stack slot, which is the
  // reconstruction's local and not the caller's -- the harness must not do that.
  if (local != nullptr) {
    for (std::size_t i = 0; i < os::kTripleWords; ++i) {
      g_world.project_local_copy[i] = local[i];
    }
  }
  return g_world.project;
}

const Triple* callee_00b81720(void* self, void* cell) {
  record("callee_00b81720", cell, 0, 0);
  g_world.screen_self = self;
  g_world.screen_cell = cell;
  return g_world.screen;
}

const Triple* callee_00b81780(void* self, void* scratch) {
  record("callee_00b81780", scratch, 0, 0);
  (void)self;
  return g_world.surface;
}

const Triple* dispatch_first(std::uint32_t call_word, void* self) {
  FirstFn fn = nullptr;
  std::memcpy(&fn, &call_word, sizeof fn);
  if (fn == nullptr) {
    return nullptr;
  }
  return fn(self);
}

std::uint32_t dispatch_probe(std::uint32_t call_word, void* self, std::uint32_t arg0, Triple* arg1,
                             std::uint32_t arg2) {
  ProbeFn fn = nullptr;
  std::memcpy(&fn, &call_word, sizeof fn);
  if (fn == nullptr) {
    return 0u;
  }
  return fn(self, arg0, arg1, arg2);
}

}  // namespace openspore::reconstruction::pkg_w2_01053be0

int main() {
  transcript_cases();
  behaviour_cases();
  std::printf("checks=%d failures=%d\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::printf("MODEL TEST FAILED\n");
    return 1;
  }
  std::printf("MODEL TEST OK\n");
  return 0;
}
