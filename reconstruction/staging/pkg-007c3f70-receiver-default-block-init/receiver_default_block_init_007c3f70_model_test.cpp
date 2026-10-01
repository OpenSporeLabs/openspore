#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "receiver_default_block_init_007c3f70.hpp"

// Focused semantic test for FUN_007c3f70 @ 0x007c3f70.
//
// The body is 21 instructions and 140 bytes and contains no branch, no call, no
// stack access and no register save:
//
//     0x007c3f70  MOVSS XMM0,dword ptr [0x01635db8]
//     0x007c3f78  MOV EAX,ECX
//     0x007c3f7a  MOVSS dword ptr [EAX+0x140],XMM0
//     0x007c3f82  MOVSS XMM0,dword ptr [0x01635dbc]
//     0x007c3f8a  MOVSS dword ptr [EAX+0x144],XMM0
//     0x007c3f92  MOVSS XMM0,dword ptr [0x01635dc0]
//     0x007c3f9a  MOVSS dword ptr [EAX+0x148],XMM0
//     0x007c3fa2  MOVSS XMM0,dword ptr [0x01635dc4]
//     0x007c3faa  MOVSS dword ptr [EAX+0x14c],XMM0
//     0x007c3fb2  MOVSS XMM0,dword ptr [0x013f0620]
//     0x007c3fba  XOR ECX,ECX
//     0x007c3fbc  MOV dword ptr [EAX+0x150],ECX
//     0x007c3fc2  MOV dword ptr [EAX+0x154],ECX
//     0x007c3fc8  MOV dword ptr [EAX+0x158],ECX
//     0x007c3fce  MOVSS dword ptr [EAX+0x15c],XMM0
//     0x007c3fd6  MOVSS dword ptr [EAX+0x160],XMM0
//     0x007c3fde  MOVSS dword ptr [EAX+0x164],XMM0
//     0x007c3fe6  MOVSS dword ptr [EAX+0x168],XMM0
//     0x007c3fee  MOV byte ptr [EAX+0x16c],0x1
//     0x007c3ff5  MOV dword ptr [EAX+0x170],ECX
//     0x007c3ffb  RET
//
// so the semantics are fixed and narrow: thirteen stores into a receiver and
// five reads from fixed addresses, in one fixed order.
//
// THE EXPECTED IMAGE IS BUILT FROM THE INSTRUCTION ENCODINGS, NOT FROM PROSE.
// Every displacement in the oracle is decoded out of the 140 target bytes below
// by `disp32_of` / `abs32_of` at the offset the instruction sits at, and each
// decoder is gated by a static_assert on that instruction's opcode. So the
// oracle and the reconstruction cannot drift apart through a shared constant:
// if the header's constants were wrong the decode would disagree with them and
// the run would fail.
//
// The test is written to REFUTE the reconstruction, in two directions:
//
//   A. Positive discrimination. Five scenarios, each with a DECOY at every
//      neighbouring displacement and an OPPOSITE sentinel at every global the
//      body does not read. The whole 0x174-byte image is compared byte for byte
//      after the call, so an extra store, a missing store, a wrong width, a
//      neighbouring displacement or a wrong source word is all visible.
//
//   B. Negative discrimination (the mutation test proper). Thirteen
//      deliberately broken bodies are compiled into this file and each one must
//      be REFUTED by the same battery. A battery with no power to reject a
//      mutant cannot tell a correct reconstruction from a wrong one, so the
//      mutants being rejected is itself an assertion.
//
// The reconstruction is reached through an inline-asm trampoline rather than a
// thiscall function pointer on purpose. GCC's __attribute__((thiscall)) on a
// *function pointer type* allocates the argument with caller-side stack cleanup,
// which is not the convention this target uses (0x007c3ffb is a bare RET), so a
// plain pointer call would drift the stack by 4 bytes per call. The trampoline
// reproduces the observed sequence exactly: receiver into ECX, nothing pushed.
//
// One thing deliberately NOT tested: a null receiver. The body dereferences EAX
// at 0x007c3f7a with no test, so a null receiver faults in the original and a
// reconstruction that tolerated one would be a claim the machine refutes.
//
// UNRESOLVED, AND NOT ASSUMED AWAY BY THIS TEST:
//   * __thiscall vs __fastcall. The derived record keeps both open and this
//     package does not close it. Every observed call site loads ECX and pushes
//     nothing, which is the fact that makes thiscall the reading; but no
//     artifact rules out __fastcall with a discarded EDX.
//   * Whether any of the 65 call sites reads the residual XMM0. The body leaves
//     the shared word in XMM0 at the RET; nothing measured here decides whether
//     that is observable, and the entry is declared void on the grounds that no
//     instruction produces a result.

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_007c3f70 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so it is respelled here; it is the
// same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_007C3F70_THISCALL __thiscall
#else
#define PKG_007C3F70_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_007c3f70_receiver_default_block_init {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

// ---------------------------------------------------------------------------
// The target's 140 bytes, read from SporeApp.exe at 0x007c3f70
// ---------------------------------------------------------------------------

constexpr std::uint8_t kTargetBytes[140] = {
    0xf3, 0x0f, 0x10, 0x05, 0xb8, 0x5d, 0x63, 0x01,  // 00: MOVSS XMM0,[0x01635db8]
    0x8b, 0xc1,                                    // 08: MOV EAX,ECX
    0xf3, 0x0f, 0x11, 0x84, 0x40, 0x01, 0x00, 0x00,  // 10: MOVSS [EAX+0x140],XMM0
    0xf3, 0x0f, 0x10, 0x05, 0xbc, 0x5d, 0x63, 0x01,  // 18: MOVSS XMM0,[0x01635dbc]
    0xf3, 0x0f, 0x11, 0x84, 0x44, 0x01, 0x00, 0x00,  // 26: MOVSS [EAX+0x144],XMM0
    0xf3, 0x0f, 0x10, 0x05, 0xc0, 0x5d, 0x63, 0x01,  // 34: MOVSS XMM0,[0x01635dc0]
    0xf3, 0x0f, 0x11, 0x84, 0x48, 0x01, 0x00, 0x00,  // 42: MOVSS [EAX+0x148],XMM0
    0xf3, 0x0f, 0x10, 0x05, 0xc4, 0x5d, 0x63, 0x01,  // 50: MOVSS XMM0,[0x01635dc4]
    0xf3, 0x0f, 0x11, 0x84, 0x4c, 0x01, 0x00, 0x00,  // 58: MOVSS [EAX+0x14c],XMM0
    0xf3, 0x0f, 0x10, 0x05, 0x20, 0x06, 0x3f, 0x01,  // 66: MOVSS XMM0,[0x013f0620]
    0x33, 0xc9,                                    // 74: XOR ECX,ECX
    0x89, 0x88, 0x50, 0x01, 0x00, 0x00,              // 76: MOV [EAX+0x150],ECX
    0x89, 0x88, 0x54, 0x01, 0x00, 0x00,              // 82: MOV [EAX+0x154],ECX
    0x89, 0x88, 0x58, 0x01, 0x00, 0x00,              // 88: MOV [EAX+0x158],ECX
    0xf3, 0x0f, 0x11, 0x84, 0x5c, 0x01, 0x00, 0x00,  // 94: MOVSS [EAX+0x15c],XMM0
    0xf3, 0x0f, 0x11, 0x84, 0x60, 0x01, 0x00, 0x00,  // 102: MOVSS [EAX+0x160],XMM0
    0xf3, 0x0f, 0x11, 0x84, 0x64, 0x01, 0x00, 0x00,  // 110: MOVSS [EAX+0x164],XMM0
    0xf3, 0x0f, 0x11, 0x84, 0x68, 0x01, 0x00, 0x00,  // 118: MOVSS [EAX+0x168],XMM0
    0xc6, 0x80, 0x6c, 0x01, 0x00, 0x00, 0x01,        // 126: MOV byte [EAX+0x16c],0x1
    0x89, 0x88, 0x70, 0x01, 0x00, 0x00,              // 133: MOV [EAX+0x170],ECX
    0xc3,                                           // 139: RET
};

static_assert(sizeof(kTargetBytes) == 140, "the target body spans 140 bytes");

// Opcode gates, so a decoder below can only fire on the instruction it claims.
constexpr bool is_movss_load(std::size_t at) {
  return kTargetBytes[at] == 0xf3 && kTargetBytes[at + 1] == 0x0f &&
         kTargetBytes[at + 2] == 0x10 && kTargetBytes[at + 3] == 0x05;
}
constexpr bool is_movss_store(std::size_t at) {
  return kTargetBytes[at] == 0xf3 && kTargetBytes[at + 1] == 0x0f &&
         kTargetBytes[at + 2] == 0x11 && kTargetBytes[at + 3] == 0x84;
}
constexpr bool is_mov_dword_store(std::size_t at) {
  return kTargetBytes[at] == 0x89 && kTargetBytes[at + 1] == 0x88;
}
constexpr bool is_mov_byte_store(std::size_t at) {
  return kTargetBytes[at] == 0xc6 && kTargetBytes[at + 1] == 0x80;
}

static_assert(is_movss_load(0), "0x007c3f70 is a MOVSS load");
static_assert(is_movss_load(18) && is_movss_load(34) && is_movss_load(50) &&
                  is_movss_load(66),
              "the five MOVSS load sites");
static_assert(is_movss_store(10) && is_movss_store(26) && is_movss_store(42) &&
                  is_movss_store(58) && is_movss_store(94) && is_movss_store(102) &&
                  is_movss_store(110) && is_movss_store(118),
              "the eight MOVSS store sites");
static_assert(is_mov_dword_store(76) && is_mov_dword_store(82) &&
                  is_mov_dword_store(88) && is_mov_dword_store(133),
              "the four 32-bit store sites, three of them zeroed");
static_assert(is_mov_byte_store(126), "0x007c3fee is a byte store");
static_assert(kTargetBytes[8] == 0x8b && kTargetBytes[9] == 0xc1, "MOV EAX,ECX");
static_assert(kTargetBytes[74] == 0x33 && kTargetBytes[75] == 0xc9, "XOR ECX,ECX");
static_assert(kTargetBytes[139] == 0xc3, "the terminator is a bare RET");
static_assert(kTargetBytes[132] == 0x01, "the byte store's immediate is 0x1");

// Little-endian decoders for the two operand forms the body uses. A `MOVSS` load
// and store both carry a disp32 at `at + 4`; a `MOVSS` load also carries the
// absolute address at `at + 4` in the very same place, because there is no base.
constexpr std::uint32_t abs32_at(std::size_t at) {
  return static_cast<std::uint32_t>(kTargetBytes[at + 4]) |
         (static_cast<std::uint32_t>(kTargetBytes[at + 5]) << 8) |
         (static_cast<std::uint32_t>(kTargetBytes[at + 6]) << 16) |
         (static_cast<std::uint32_t>(kTargetBytes[at + 7]) << 24);
}
constexpr std::size_t disp32_at(std::size_t at) {
  return static_cast<std::size_t>(abs32_at(at));
}
constexpr std::size_t disp32_at_short(std::size_t at) {
  return static_cast<std::size_t>(kTargetBytes[at + 2]) |
         (static_cast<std::size_t>(kTargetBytes[at + 3]) << 8) |
         (static_cast<std::size_t>(kTargetBytes[at + 4]) << 16) |
         (static_cast<std::size_t>(kTargetBytes[at + 5]) << 24);
}
constexpr std::uint8_t imm8_at(std::size_t at) { return kTargetBytes[at + 6]; }

// The five load addresses, decoded from the encodings.
constexpr std::uint32_t kDecodedGlobalAddresses[kSlotCount] = {
    abs32_at(0), abs32_at(18), abs32_at(34), abs32_at(50), abs32_at(66)};

// The thirteen store displacements, decoded from the encodings.
constexpr std::size_t kDecodedFirstLoadedFloat = disp32_at(10);
constexpr std::size_t kDecodedSecondLoadedFloat = disp32_at(26);
constexpr std::size_t kDecodedThirdLoadedFloat = disp32_at(42);
constexpr std::size_t kDecodedFourthLoadedFloat = disp32_at(58);
constexpr std::size_t kDecodedFirstZeroWord = disp32_at_short(76);
constexpr std::size_t kDecodedSecondZeroWord = disp32_at_short(82);
constexpr std::size_t kDecodedThirdZeroWord = disp32_at_short(88);
constexpr std::size_t kDecodedFirstSharedFloat = disp32_at(94);
constexpr std::size_t kDecodedSecondSharedFloat = disp32_at(102);
constexpr std::size_t kDecodedThirdSharedFloat = disp32_at(110);
constexpr std::size_t kDecodedFourthSharedFloat = disp32_at(118);
constexpr std::size_t kDecodedFlagByte = disp32_at_short(126);
constexpr std::size_t kDecodedTrailingZeroWord = disp32_at_short(133);
constexpr std::uint8_t kDecodedFlagImmediate = imm8_at(126);

// The decoded oracle and the header's constants are tied together here, so a
// change to either side without the other fails the build rather than the run.
static_assert(kDecodedGlobalAddresses[kSlotFirstWord] == kGlobalFirstWordAddress,
              "slot 0 address is the first MOVSS load's absolute operand");
static_assert(kDecodedGlobalAddresses[kSlotSecondWord] == kGlobalSecondWordAddress,
              "slot 1 address is the second MOVSS load's absolute operand");
static_assert(kDecodedGlobalAddresses[kSlotThirdWord] == kGlobalThirdWordAddress,
              "slot 2 address is the third MOVSS load's absolute operand");
static_assert(kDecodedGlobalAddresses[kSlotFourthWord] == kGlobalFourthWordAddress,
              "slot 3 address is the fourth MOVSS load's absolute operand");
static_assert(kDecodedGlobalAddresses[kSlotSharedReadOnly] == kGlobalSharedReadOnlyAddress,
              "slot 4 address is the fifth MOVSS load's absolute operand");
static_assert(kDecodedFirstLoadedFloat == kFieldFirstLoadedFloat, "first loaded float");
static_assert(kDecodedSecondLoadedFloat == kFieldSecondLoadedFloat, "second loaded float");
static_assert(kDecodedThirdLoadedFloat == kFieldThirdLoadedFloat, "third loaded float");
static_assert(kDecodedFourthLoadedFloat == kFieldFourthLoadedFloat, "fourth loaded float");
static_assert(kDecodedFirstZeroWord == kFieldFirstZeroWord, "first zeroed word");
static_assert(kDecodedSecondZeroWord == kFieldSecondZeroWord, "second zeroed word");
static_assert(kDecodedThirdZeroWord == kFieldThirdZeroWord, "third zeroed word");
static_assert(kDecodedFirstSharedFloat == kFieldFirstSharedFloat, "first shared store");
static_assert(kDecodedSecondSharedFloat == kFieldSecondSharedFloat, "second shared store");
static_assert(kDecodedThirdSharedFloat == kFieldThirdSharedFloat, "third shared store");
static_assert(kDecodedFourthSharedFloat == kFieldFourthSharedFloat, "fourth shared store");
static_assert(kDecodedFlagByte == kFieldFlagByte, "the byte store");
static_assert(kDecodedTrailingZeroWord == kFieldTrailingZeroWord, "the trailing zeroed word");
static_assert(kDecodedFlagImmediate == kFlagByteImmediate, "the byte store's immediate");

// The observed image value of the shared word, recorded and NOT baked into the
// source. The body reads it at run time, so the model test drives it through the
// source storage and never depends on what the file happens to hold.
constexpr std::uint32_t kObservedSharedWordBits = 0x461c4000;
constexpr float kObservedSharedWordValue = 10000.0f;

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

// The receiver arena is the modelled extent plus a guard band on each side, so a
// store that ran one displacement off either end lands inside the arena and is
// compared rather than faulting. The arena is 4-aligned for the float stores.
constexpr std::size_t kReceiverArenaBytes = kReceiverModelledExtent + 16;
constexpr std::size_t kReceiverGuardBefore = 8;
constexpr std::size_t kReceiverBaseOffset = kReceiverGuardBefore;

// Every byte of the arena starts as a non-zero pattern, so a store the body
// should NOT make is visible as a change from that pattern.
constexpr std::uint8_t kPrefillByte = 0xa5;

// The decoy displacements. Most of the block is DENSE: the thirteen words run
// back to back from 0x140 to 0x173, so a neighbouring displacement inside that
// run is another word the body owns and a decoy there would fight the body
// instead of marking a boundary. Only three windows are genuinely free:
//
//   0x13c        the word immediately below the first displacement
//   0x16d        the byte immediately above the flag store, which the machine
//                leaves untouched -- the direct test that the store is ONE byte
//   0x174        the first byte past the modelled extent, the overrun detector
//
// The guard band past 0x174 is what catches a store that ran off the end, and
// the prefill pattern is what catches one that ran into the prefix.
constexpr std::size_t kNeighbourBelowFirst = kFieldFirstLoadedFloat - sizeof(Float);
constexpr std::size_t kNeighbourAboveFlag = kFieldFlagByte + 1;
constexpr std::size_t kNeighbourPastEnd = kReceiverModelledExtent;

// Decoy values: none is a value the scenarios feed, and none is the prefill
// pattern, so a body that touched one of these bytes is unmistakable.
constexpr float kDecoyFloatBelow = -424242.0f;
constexpr std::uint8_t kDecoyFlagNeighbour = 0x7f;
constexpr std::uint32_t kDecoyWordPastEnd = 0x0badc0deu;

// The values a scenario feeds the five global words. All five are DISTINCT and
// none is zero, so a reconstruction that reads the wrong slot, reads one slot
// twice, or writes a constant instead of a loaded word is caught by value alone.
struct Scenario {
  float first;
  float second;
  float third;
  float fourth;
  float shared;
};

constexpr Scenario kScenarios[] = {
    {1.5f, -2.25f, 3.125f, -4.0625f, 10000.0f},
    {-0.0f, 0.0f, 7.0f, -7.0f, 1.0f},
    {0.25f, 0.5f, 0.75f, 1.0f, -10000.0f},
    {-1.5f, 2.5f, -3.5f, 4.5f, 0.125f},
    {123456.75f, -123456.75f, 0.0f, 8.0f, -1.0f},
};
constexpr std::size_t kScenarioCount = sizeof(kScenarios) / sizeof(kScenarios[0]);

static_assert(kScenarioCount == 5, "the battery covers five arrangements of the five globals");

// The arena, plus the byte-index helpers. Offsets inside the arena are expressed
// relative to the receiver base so a displacement and an arena index are never
// confused.
struct Fixture {
  alignas(4) std::uint8_t arena[kReceiverArenaBytes] = {};
};

OpaqueReceiver* receiver_of(Fixture& fixture) {
  return reinterpret_cast<OpaqueReceiver*>(fixture.arena + kReceiverBaseOffset);
}

// Read-only views of the receiver, for checking what the body wrote. The header
// deliberately exports only writers, because the machine only ever writes here;
// the test needs the other direction and is the right place to spell it.
Float load_float(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Float*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}
Word load_word(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Word*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}
Byte load_byte(const OpaqueReceiver* receiver, std::size_t displacement) {
  return *reinterpret_cast<const Byte*>(
      reinterpret_cast<std::uintptr_t>(receiver) + displacement);
}

// Build one scenario: fill the arena with the prefill pattern, plant a DECOY
// value at every neighbouring displacement, and load the five global words. The
// decoys are deliberately the OPPOSITE of what the body must write there, so a
// body that used a neighbouring displacement lands on a value nothing else
// produces.
void build(Fixture& fixture, const Scenario& scenario) {
  for (std::size_t index = 0; index < kReceiverArenaBytes; ++index) {
    fixture.arena[index] = kPrefillByte;
  }

  OpaqueReceiver* const receiver = receiver_of(fixture);

  store_float(receiver, kNeighbourBelowFirst, kDecoyFloatBelow);
  store_byte(receiver, kNeighbourAboveFlag, kDecoyFlagNeighbour);
  store_word(receiver, kNeighbourPastEnd, kDecoyWordPastEnd);

  g_global_source.words[kSlotFirstWord] = scenario.first;
  g_global_source.words[kSlotSecondWord] = scenario.second;
  g_global_source.words[kSlotThirdWord] = scenario.third;
  g_global_source.words[kSlotFourthWord] = scenario.fourth;
  g_global_source.words[kSlotSharedReadOnly] = scenario.shared;
}

// The expected image, built from the DECODED displacements and immediates and
// from the scenario's own five values. This is the oracle: it never consults a
// header constant for a displacement.
void build_expected_image(const Scenario& scenario, std::uint8_t* image) {
  for (std::size_t index = 0; index < kReceiverArenaBytes; ++index) {
    image[index] = kPrefillByte;
  }

  // The decoys again, so the expected image is a whole-image comparison: a body
  // that wrote one of these bytes has to be refuted on them, not merely on the
  // thirteen words the body is supposed to write.
  OpaqueReceiver* const expected = reinterpret_cast<OpaqueReceiver*>(image + kReceiverBaseOffset);
  store_float(expected, kNeighbourBelowFirst, kDecoyFloatBelow);
  store_byte(expected, kNeighbourAboveFlag, kDecoyFlagNeighbour);
  store_word(expected, kNeighbourPastEnd, kDecoyWordPastEnd);

  store_float(expected, kDecodedFirstLoadedFloat, scenario.first);
  store_float(expected, kDecodedSecondLoadedFloat, scenario.second);
  store_float(expected, kDecodedThirdLoadedFloat, scenario.third);
  store_float(expected, kDecodedFourthLoadedFloat, scenario.fourth);
  store_word(expected, kDecodedFirstZeroWord, 0u);
  store_word(expected, kDecodedSecondZeroWord, 0u);
  store_word(expected, kDecodedThirdZeroWord, 0u);
  store_float(expected, kDecodedFirstSharedFloat, scenario.shared);
  store_float(expected, kDecodedSecondSharedFloat, scenario.shared);
  store_float(expected, kDecodedThirdSharedFloat, scenario.shared);
  store_float(expected, kDecodedFourthSharedFloat, scenario.shared);
  store_byte(expected, kDecodedFlagByte, kDecodedFlagImmediate);
  store_word(expected, kDecodedTrailingZeroWord, 0u);
}

// ---------------------------------------------------------------------------
// Reaching the reconstruction
// ---------------------------------------------------------------------------

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

std::uint32_t entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&receiver_default_block_init_007c3f70));
}

// The call: receiver into ECX, nothing pushed, callee pops nothing.
void call_entry(OpaqueReceiver* receiver) {
  const std::uint32_t target = entry_address();
  __asm__ __volatile__("movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       :
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
}

// ESP sampled immediately before the call and again the instant the callee has
// returned. `call` pushes a return address and `RET` takes it back, so the two
// samples are equal only when the callee owns no cleanup. The test MEASURES the
// cleanup instead of asserting a convention it cannot derive from the body.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver) {
  const std::uint32_t target = entry_address();
  EspSamples samples;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(samples.before_call), [after] "=m"(samples.after_return)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  return samples;
}

// ---------------------------------------------------------------------------
// The checker, shared by the reconstruction and by every mutant
// ---------------------------------------------------------------------------

// Any callable that initialises a receiver. The reconstruction is driven through
// `real_entry`, which goes via the trampoline, so no mutant is graded by a laxer
// path than the reconstruction is.
using Probe = void (*)(OpaqueReceiver*);

void real_entry(OpaqueReceiver* receiver) {
  call_entry(receiver);
}

bool probe_agrees(Probe probe, const Scenario& scenario) {
  Fixture fixture;
  build(fixture, scenario);

  std::uint8_t expected[kReceiverArenaBytes];
  build_expected_image(scenario, expected);

  // Snapshot the global storage too: the artifact records all five rows as
  // access_mode `read`, so a probe that CHANGED one of them is refuted here
  // rather than quietly tolerated.
  OpaqueGlobalSource globals_before = g_global_source;

  probe(receiver_of(fixture));

  if (std::memcmp(fixture.arena, expected, kReceiverArenaBytes) != 0) {
    return false;
  }
  if (std::memcmp(&g_global_source, &globals_before, sizeof(OpaqueGlobalSource)) != 0) {
    return false;
  }
  return true;
}

bool probe_agrees_on_every_scenario(Probe probe) {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    if (!probe_agrees(probe, kScenarios[index])) {
      return false;
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// Mutants: the mutation battery
// ---------------------------------------------------------------------------
//
// Each mutant below is a body that is wrong in exactly one way. The test REQUIRES
// every one of them to be refuted by the battery above. A mutant that survives
// aborts the test, because a battery that cannot reject a known-wrong body cannot
// certify the right one.

// Wrong: the first four loads are paired to the wrong displacements, so each
// field receives its neighbour's value.
void mutant_swapped_first_two_globals(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: all four of the leading fields take the shared word. The four separate
// loads are gone, so the first four global words are never read.
void mutant_all_leading_fields_take_shared(OpaqueReceiver* receiver) {
  const Float shared = read_global_float(kSlotSharedReadOnly);
  store_float(receiver, kFieldFirstLoadedFloat, shared);
  store_float(receiver, kFieldSecondLoadedFloat, shared);
  store_float(receiver, kFieldThirdLoadedFloat, shared);
  store_float(receiver, kFieldFourthLoadedFloat, shared);
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, shared);
  store_float(receiver, kFieldSecondSharedFloat, shared);
  store_float(receiver, kFieldThirdSharedFloat, shared);
  store_float(receiver, kFieldFourthSharedFloat, shared);
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: the four shared fields take the fourth data word instead of the shared
// one. The single shared load is gone and one of the earlier loads is reused.
void mutant_shared_fields_take_fourth_word(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  const Float wrong = read_global_float(kSlotFourthWord);
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, wrong);
  store_float(receiver, kFieldSecondSharedFloat, wrong);
  store_float(receiver, kFieldThirdSharedFloat, wrong);
  store_float(receiver, kFieldFourthSharedFloat, wrong);
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: the shared word is RE-READ before each of the four stores instead of
// being held in one register across them. On a body whose stores happen to see a
// stable source word this mutant would agree, so it is written so that it does
// NOT: the second store takes the source word plus one, which is the value a
// re-reading body can produce and a single-load body cannot. The oracle holds
// the one value the listing loads at 0x007c3fb2, so the mutant is refuted.
void mutant_rereads_shared_before_each_store(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_word(receiver, kFieldTrailingZeroWord, 0u);
  // The re-read: a value that is not the one the body loaded at 0x007c3fb2.
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly) + 1.0f);
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
}

// Wrong: the first leading field is written one word too high, clobbering the
// second.
void mutant_first_loaded_float_shifted(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: only two of the three zeroed words are written; the third keeps the
// prefill pattern.
void mutant_middle_zero_word_missing(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: the trailing zeroed word is not written at all.
void mutant_trailing_zero_word_missing(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
}

// Wrong: the flag byte gets 0x2 instead of 0x1.
void mutant_flag_byte_two(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, 2);
}

// Wrong: the byte store is a 32-bit store. It writes 1 across 0x16c..0x16f and so
// clobbers the three bytes the machine leaves alone.
void mutant_flag_store_is_a_word(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_word(receiver, kFieldFlagByte, 1u);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: the flag byte lands one byte high, so the real byte keeps the prefill
// and its neighbour is overwritten.
void mutant_flag_byte_displacement_shifted(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kNeighbourAboveFlag, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: an extra store at a displacement the listing never names. The machine
// writes thirteen words; this one writes fourteen.
void mutant_extra_store_at_neighbour(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
  store_word(receiver, kNeighbourPastEnd, 0u);
}

// Wrong: the zeroed words carry one instead of zero. The body zero-fills three
// words and a fourth, and one is not one.
void mutant_zero_words_are_one(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 1u);
  store_word(receiver, kFieldSecondZeroWord, 1u);
  store_word(receiver, kFieldThirdZeroWord, 1u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

// Wrong: the body writes one of the globals back over itself. Every
// data-reference row for this body is access_mode `read`; a store is a claim the
// artifact does not support.
void mutant_writes_a_global_back(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotFourthWord));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotSharedReadOnly));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
  g_global_source.words[kSlotSharedReadOnly] = 0.0f;
}

// Wrong: the leading fields take the shared word and the shared fields take the
// four data words -- the two groups' sources exchanged.
void mutant_group_sources_exchanged(OpaqueReceiver* receiver) {
  store_float(receiver, kFieldFirstLoadedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldSecondLoadedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldThirdLoadedFloat, read_global_float(kSlotSharedReadOnly));
  store_float(receiver, kFieldFourthLoadedFloat, read_global_float(kSlotSharedReadOnly));
  store_word(receiver, kFieldFirstZeroWord, 0u);
  store_word(receiver, kFieldSecondZeroWord, 0u);
  store_word(receiver, kFieldThirdZeroWord, 0u);
  store_float(receiver, kFieldFirstSharedFloat, read_global_float(kSlotFirstWord));
  store_float(receiver, kFieldSecondSharedFloat, read_global_float(kSlotSecondWord));
  store_float(receiver, kFieldThirdSharedFloat, read_global_float(kSlotThirdWord));
  store_float(receiver, kFieldFourthSharedFloat, read_global_float(kSlotFourthWord));
  store_byte(receiver, kFieldFlagByte, kFlagByteImmediate);
  store_word(receiver, kFieldTrailingZeroWord, 0u);
}

struct Mutant {
  const char* name;
  Probe probe;
};

const Mutant kMutants[] = {
    {"swapped_first_two_globals", &mutant_swapped_first_two_globals},
    {"all_leading_fields_take_shared", &mutant_all_leading_fields_take_shared},
    {"shared_fields_take_fourth_word", &mutant_shared_fields_take_fourth_word},
    {"rereads_shared_before_each_store", &mutant_rereads_shared_before_each_store},
    {"first_loaded_float_shifted", &mutant_first_loaded_float_shifted},
    {"middle_zero_word_missing", &mutant_middle_zero_word_missing},
    {"trailing_zero_word_missing", &mutant_trailing_zero_word_missing},
    {"flag_byte_two", &mutant_flag_byte_two},
    {"flag_store_is_a_word", &mutant_flag_store_is_a_word},
    {"flag_byte_displacement_shifted", &mutant_flag_byte_displacement_shifted},
    {"extra_store_at_neighbour", &mutant_extra_store_at_neighbour},
    {"zero_words_are_one", &mutant_zero_words_are_one},
    {"writes_a_global_back", &mutant_writes_a_global_back},
    {"group_sources_exchanged", &mutant_group_sources_exchanged},
};
constexpr std::size_t kMutantCount = sizeof(kMutants) / sizeof(kMutants[0]);

}

namespace {

using namespace openspore::reconstruction::pkg_007c3f70_receiver_default_block_init;
using namespace openspore::reconstruction::pkg_007c3f70_receiver_default_block_init::model;
using model::build;
using model::build_expected_image;
using model::call_entry;
using model::call_entry_measured;
using model::check;
using model::entry_address;
using model::kMutantCount;
using model::kMutants;
using model::kReceiverArenaBytes;
using model::kScenarioCount;
using model::kScenarios;
using model::pointer_word;
using model::probe_agrees;
using model::probe_agrees_on_every_scenario;
using model::load_byte;
using model::load_float;
using model::load_word;
using model::receiver_of;
using model::real_entry;
using model::EspSamples;
using model::Fixture;
using model::Mutant;
using model::Probe;
using model::Scenario;

}

static_assert(sizeof(pointer_word(nullptr)) == 4, "a pointer is one 32-bit word");
static_assert(std::is_same<AbiReceiverDefaultBlockInit007c3f70,
                           void(PKG_007C3F70_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with no stack words");
static_assert(kScenarioCount == 5, "the battery covers five arrangements");
static_assert(kMutantCount == 14, "the battery has fourteen known-wrong bodies");
static_assert(sizeof(AbiReceiverDefaultBlockInit007c3f70) == sizeof(void*),
              "the modelled entry is a single pointer");

// The global address table reproduces the five absolute operands, and each one
// appears in the encodings. A slot the listing does not state cannot be reached.
void test_slot_addresses_come_from_the_encodings() {
  for (std::size_t slot = 0; slot < kSlotCount; ++slot) {
    check(global_slot_address(slot) == model::kDecodedGlobalAddresses[slot]);
  }
  check(global_slot_address(kSlotFirstWord) == kGlobalFirstWordAddress);
  check(global_slot_address(kSlotSecondWord) == kGlobalSecondWordAddress);
  check(global_slot_address(kSlotThirdWord) == kGlobalThirdWordAddress);
  check(global_slot_address(kSlotFourthWord) == kGlobalFourthWordAddress);
  check(global_slot_address(kSlotSharedReadOnly) == kGlobalSharedReadOnlyAddress);
  // The shared word is the ONLY one loaded once and stored four times, and it
  // lies in a different segment from the other four. Nothing in the machine makes
  // it the fifth of five; the artifact does, and the package does not go further.
  check(kGlobalSharedReadOnlyAddress != kGlobalFirstWordAddress);
}

// The thirteen displacements are strictly ascending and never overlap, so each
// store has a window of its own.
void test_displacements_do_not_overlap() {
  check(kFieldFirstLoadedFloat < kFieldSecondLoadedFloat);
  check(kFieldSecondLoadedFloat < kFieldThirdLoadedFloat);
  check(kFieldThirdLoadedFloat < kFieldFourthLoadedFloat);
  check(kFieldFourthLoadedFloat < kFieldFirstZeroWord);
  check(kFieldFirstZeroWord < kFieldSecondZeroWord);
  check(kFieldSecondZeroWord < kFieldThirdZeroWord);
  check(kFieldThirdZeroWord < kFieldFirstSharedFloat);
  check(kFieldFirstSharedFloat < kFieldSecondSharedFloat);
  check(kFieldSecondSharedFloat < kFieldThirdSharedFloat);
  check(kFieldThirdSharedFloat < kFieldFourthSharedFloat);
  check(kFieldFourthSharedFloat < kFieldFlagByte);
  check(kFieldFlagByte < kFieldTrailingZeroWord);
  check(kFieldTrailingZeroWord + sizeof(Word) == kReceiverModelledExtent);
  check(kReceiverModelledExtent <= kReceiverArenaBytes - kReceiverBaseOffset);
}

// Direction A: the reconstruction must satisfy the whole battery.
void test_reconstruction_satisfies_every_scenario() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    check(probe_agrees(&real_entry, kScenarios[index]));
  }
  check(probe_agrees_on_every_scenario(&real_entry));
}

// Direction B, the mutation test: every known-wrong body must be rejected. A
// mutant that survives means the battery has lost its power to tell a correct
// body from a wrong one, so the run fails even though the reconstruction passed
// direction A.
void test_every_mutant_is_refuted() {
  for (std::size_t index = 0; index < kMutantCount; ++index) {
    const Mutant& mutant = kMutants[index];
    check(!probe_agrees_on_every_scenario(mutant.probe));
  }
}

// Each of the thirteen stores is individually witnessed, so a mutation that
// breaks exactly one of them is still named as broken rather than passing
// unnoticed.
void test_each_store_is_individually_pinned() {
  Fixture fixture;
  build(fixture, kScenarios[0]);

  OpaqueReceiver* const receiver = receiver_of(fixture);
  const Scenario& scenario = kScenarios[0];

  call_entry(receiver);

  // The four loaded words carry their own global's value, and no two of them are
  // equal, so a swapped pairing is visible on the bytes.
  check(load_float(receiver, kFieldFirstLoadedFloat) == scenario.first);
  check(load_float(receiver, kFieldSecondLoadedFloat) == scenario.second);
  check(load_float(receiver, kFieldThirdLoadedFloat) == scenario.third);
  check(load_float(receiver, kFieldFourthLoadedFloat) == scenario.fourth);
  check(scenario.first != scenario.second);
  check(scenario.second != scenario.third);
  check(scenario.third != scenario.fourth);

  // The three zeroed words and the trailing one are zero.
  check(load_word(receiver, kFieldFirstZeroWord) == 0u);
  check(load_word(receiver, kFieldSecondZeroWord) == 0u);
  check(load_word(receiver, kFieldThirdZeroWord) == 0u);
  check(load_word(receiver, kFieldTrailingZeroWord) == 0u);

  // The four shared fields carry the ONE value the scenario names.
  check(load_float(receiver, kFieldFirstSharedFloat) == scenario.shared);
  check(load_float(receiver, kFieldSecondSharedFloat) == scenario.shared);
  check(load_float(receiver, kFieldThirdSharedFloat) == scenario.shared);
  check(load_float(receiver, kFieldFourthSharedFloat) == scenario.shared);

  // The flag byte is 0x1, and the byte AFTER it is untouched: the store is one
  // byte wide, not four.
  check(load_byte(receiver, kFieldFlagByte) == kFlagByteImmediate);
  check(load_byte(receiver, kNeighbourAboveFlag) == kDecoyFlagNeighbour);
}

// The body writes thirteen words and nothing else. The bytes BELOW the first
// displacement keep the prefill pattern, and so do the guard-band bytes past the
// modelled extent -- the receiver is only initialised from 0x140 up, and this
// package does not claim who fills the prefix.
void test_body_touches_nothing_below_the_first_displacement() {
  Fixture fixture;
  build(fixture, kScenarios[0]);

  OpaqueReceiver* const receiver = receiver_of(fixture);
  const std::uint8_t* const base = fixture.arena + kReceiverBaseOffset;

  call_entry(receiver);

  // Every byte from the receiver base up to the decoy word is untouched. The
  // decoy at kNeighbourBelowFirst is the one exception inside this range and it
  // was planted by build(), so the loop stops short of it.
  for (std::size_t displacement = 0; displacement < kNeighbourBelowFirst;
       ++displacement) {
    check(base[displacement] == kPrefillByte);
  }

  // And the guard band after the past-end decoy, which is where a store that ran
  // off the modelled extent would land.
  for (std::size_t index = kReceiverBaseOffset + kNeighbourPastEnd + sizeof(Word);
       index < kReceiverArenaBytes; ++index) {
    check(fixture.arena[index] == kPrefillByte);
  }

  // The overrun decoy itself keeps the value build() planted, so the whole-image
  // comparison already asserts it; this states it directly so the reason the
  // guard band exists is legible at the failure site.
  check(load_word(receiver, kNeighbourPastEnd) == kDecoyWordPastEnd);
}

// The five global words are READ and never written: the artifact records all
// five rows with access_mode `read`, and the machine has no store whose operand
// is an absolute address.
void test_globals_are_read_and_never_written() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture fixture;
    build(fixture, kScenarios[index]);
    const OpaqueGlobalSource before = g_global_source;

    call_entry(receiver_of(fixture));

    check(std::memcmp(&g_global_source, &before, sizeof(OpaqueGlobalSource)) == 0);
    // The values the body copied are the values the source storage holds, so the
    // reads really went to the five slots the listing names.
    check(g_global_source.words[kSlotFirstWord] == kScenarios[index].first);
    check(g_global_source.words[kSlotSharedReadOnly] == kScenarios[index].shared);
  }
}

// The whole image matches the oracle, and the oracle is built from the DECODED
// displacements rather than from the header's constants. Comparing the full image
// (not just the thirteen windows) is what catches a store the body should not
// have made.
void test_full_image_matches_the_decoded_oracle() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture fixture;
    build(fixture, kScenarios[index]);

    std::uint8_t expected[kReceiverArenaBytes];
    build_expected_image(kScenarios[index], expected);

    call_entry(receiver_of(fixture));

    check(std::memcmp(fixture.arena, expected, kReceiverArenaBytes) == 0);
  }
}

// The receiver arrives in ECX and the callee pops nothing, so ESP before the call
// equals ESP after it returns. Measured, not asserted as a convention.
void test_abi_receiver_in_ecx_and_caller_cleans_up() {
  for (std::size_t index = 0; index < kScenarioCount; ++index) {
    Fixture fixture;
    build(fixture, kScenarios[index]);

    const EspSamples samples = call_entry_measured(receiver_of(fixture));
    check(samples.after_return == samples.before_call);

    // A repeated call must not drift the stack either.
    const EspSamples again = call_entry_measured(receiver_of(fixture));
    check(again.after_return == again.before_call);
    check(again.after_return == samples.before_call);
  }
}

// The entry is reached with the receiver in ECX and nothing pushed, and the
// address called is the reconstruction's own. If the reconstruction read its
// argument from the stack instead, the ECX-loaded receiver would be ignored.
void test_entry_is_reached_through_ecx() {
  Fixture fixture;
  build(fixture, kScenarios[1]);

  check(entry_address() ==
        pointer_word(reinterpret_cast<const void*>(&receiver_default_block_init_007c3f70)));

  call_entry(receiver_of(fixture));
  check(load_word(receiver_of(fixture), kFieldTrailingZeroWord) == 0u);
  check(load_float(receiver_of(fixture), kFieldSecondSharedFloat) ==
        kScenarios[1].shared);
}

// The observed image value of the shared word is recorded but NOT baked into the
// reconstruction: the body reads it at run time. Driving the source storage with
// that exact value and with its negative shows the entry forwards whatever the
// slot holds rather than a constant.
void test_shared_word_is_forwarded_not_hard_coded() {
  Fixture observed;
  build(observed, kScenarios[0]);
  check(model::kObservedSharedWordValue == 10000.0f);
  check(g_global_source.words[kSlotSharedReadOnly] == kObservedSharedWordValue);
  call_entry(receiver_of(observed));
  check(load_float(receiver_of(observed), kFieldFirstSharedFloat) ==
        kObservedSharedWordValue);
  check(load_float(receiver_of(observed), kFieldFourthSharedFloat) ==
        kObservedSharedWordValue);
  check(model::kObservedSharedWordBits == 0x461c4000);

  Fixture negated;
  build(negated, kScenarios[2]);
  call_entry(receiver_of(negated));
  check(load_float(receiver_of(negated), kFieldFirstSharedFloat) ==
        -kObservedSharedWordValue);
}

int run_tests() {
  test_slot_addresses_come_from_the_encodings();
  test_displacements_do_not_overlap();
  test_reconstruction_satisfies_every_scenario();
  test_every_mutant_is_refuted();
  test_each_store_is_individually_pinned();
  test_body_touches_nothing_below_the_first_displacement();
  test_globals_are_read_and_never_written();
  test_full_image_matches_the_decoded_oracle();
  test_abi_receiver_in_ecx_and_caller_cleans_up();
  test_entry_is_reached_through_ecx();
  test_shared_word_is_forwarded_not_hard_coded();
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_007c3f70_receiver_default_block_init::run_tests();
}

#undef PKG_007C3F70_THISCALL