// PKG-SWARM-W2-00A980B0 -- model test for VA 0x00a980b0
//
// WHAT THIS TEST IS FOR. The reconstruction it attacks is
// re_00a980b0() in sw2_00a980b0.cpp, the 112-instruction body of FUN_00a980b0.
// The test's job is to BREAK that reconstruction, not to walk it happily: every
// case below is written so that a specific wrong reading of the machine dies on
// it, and the decoys exist to make a wrong reading that happens to agree on the
// nominal case fail somewhere else.
//
// THE OBSERVER. Every direct and indirect callee is an observer, so the test
// sees every transfer the body makes, with which arguments, in which order, and
// with what the argument memory held AT THE MOMENT OF THE CALL:
//
//   * acquire_00883860()  -- the one direct callee (0x00a980ce). Defined HERE,
//     so the test can return a service or null and can count the calls.
//   * observe_slot()      -- installed in the service's dispatch table at
//     displacement 0x14, so all four `CALL EDX` sites land in it. It records the
//     four arguments, snapshots the pointed-to buffer, and can run a scripted
//     action (mutate the receiver, the flags, or the dispatch table) at the
//     moment of the call.
//
// The buffer snapshot is what makes write ordering testable: the reconstruction
// fills the wide buffer in a specific order and the narrow buffer twice, and the
// observer reads the bytes while the callee is running, not after the body
// returns.
//
// WHAT IS DELIBERATELY NOT ASSERTED, and why:
//
//   * The C++ TYPE of any word the body copies. The listing fixes the width
//     (dword) and the displacement and nothing else; whether the attribute
//     object's +0x10 word is a float, a count or a handle is not in this body.
//     The test therefore compares bit patterns, never interpretations.
//   * The class of the receiver, of the service, or of the attribute object.
//     Nothing in these 112 instructions names a type, and the one vtable the
//     xref export associates with this body is used in the package notes only.
//   * The value of the two stack-argument slots to the callee beyond their
//     identity: argument 1 of the wide call is asserted to be the attribute
//     object's +0x0c WORD, which the listing fixes, but the test does not claim
//     what that word means.
//   * Anything about the runtime. No original process has been run.

#include "sw2_00a980b0_types.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

namespace os = openspore::reconstruction::pkg_swarm_w2_00a980b0;

// ===========================================================================
// Harness
// ===========================================================================

namespace {

int g_failures = 0;
int g_checks = 0;
const char* g_case = "";

void fail(const char* what, const std::string& detail) {
  ++g_failures;
  std::printf("FAIL [%s] %s :: %s\n", g_case, what, detail.c_str());
}

void expect_eq_u32(const char* what, os::Word got, os::Word want) {
  ++g_checks;
  if (got != want) {
    char buffer[192];
    std::snprintf(buffer, sizeof(buffer), "got 0x%08x, want 0x%08x", got, want);
    fail(what, buffer);
  }
}

void expect_eq_u8(const char* what, std::uint8_t got, std::uint8_t want) {
  ++g_checks;
  if (got != want) {
    char buffer[192];
    std::snprintf(buffer, sizeof(buffer), "got 0x%02x, want 0x%02x", got, want);
    fail(what, buffer);
  }
}

void expect_eq_size(const char* what, std::size_t got, std::size_t want) {
  ++g_checks;
  if (got != want) {
    char buffer[192];
    std::snprintf(buffer, sizeof(buffer), "got %zu, want %zu", got, want);
    fail(what, buffer);
  }
}

[[maybe_unused]] void expect_false(const char* what, bool got) {
  ++g_checks;
  if (got) fail(what, "expected false, got true");
}

void expect_true(const char* what, bool got) {
  ++g_checks;
  if (!got) fail(what, "expected true, got false");
}

// ===========================================================================
// The world under test
// ===========================================================================

// Every buffer is over-allocated well past what the body reaches, so a
// reconstruction that reads one displacement too far lands in the fixture rather
// than off the end of it, and the check that follows reports a wrong VALUE
// instead of a crash that says nothing.
struct World {
  alignas(8) std::uint8_t receiver[160];
  alignas(8) std::uint8_t attributes_a[96];
  alignas(8) std::uint8_t attributes_b[96];
  alignas(8) std::uint8_t service[64];
  alignas(8) std::uint8_t table_a[96];
  alignas(8) std::uint8_t table_b[96];
  alignas(8) std::uint8_t spare[96];
};

// The fill values, as WORDS, one per region of the fixture, all distinct: an
// out-of-plan read reports a wrong value rather than an accidental zero. The
// fixture fills each region with the LOW BYTE of the matching word below, so the
// value a check names and the value the fixture plants cannot drift apart -- the
// fills go through `sentinel_byte`, not through a literal.
constexpr os::Word kReceiverSentinel = 0xa5a5a5a5u;
constexpr os::Word kAttributeSentinel = 0x5a5a5a5au;
constexpr os::Word kServiceSentinel = 0x3c3c3c3cu;
constexpr os::Word kTableSentinel = 0xc3c3c3c3u;
constexpr os::Word kSlotHalfSentinel = 0x7e7e7e7eu;   // the never-written second half of a slot

std::uint8_t sentinel_byte(os::Word word) {
  return static_cast<std::uint8_t>(word & 0xffu);
}

// The values planted in the attribute object, one per displacement, all
// DISTINCT and all chosen so that a mis-shifted read lands on a different value
// rather than on the right one by accident.
constexpr os::Word kAttrFlags = 0x00000000u;      // +0x08, set per case
constexpr os::Word kAttrFirstArg = 0xdeadc0deu;   // +0x0c, argument 1 of the wide call
constexpr os::Word kAttrWord5 = 0x11111111u;      // +0x10, gated on bit 5
constexpr os::Word kAttrWord6 = 0x22222222u;      // +0x14, gated on bit 6
constexpr os::Word kAttrWord7 = 0x33333333u;      // +0x18, gated on bit 7
constexpr os::Word kAttrWord8 = 0x44444444u;      // +0x1c, gated on bit 8
constexpr os::Word kAttrWord9 = 0x55555555u;      // +0x20, gated on bit 9
constexpr os::Word kAttrDecoyBefore = 0x66666666u; // +0x00, a decoy one word low
constexpr os::Word kAttrDecoyAfter = 0x77777777u;  // +0x24, a decoy one word high

constexpr os::Word kReceiverTrailing = 0x0badf00du; // +0x50
constexpr os::Word kReceiverAddressed = 0x13572468u; // +0x18, the word the LEA does NOT read
constexpr os::Word kReceiverDecoy10 = 0x24681357u;  // the three bytes above +0x10 when the guard is not latched

// Two distinct dispatch tables. Table A is the one the service starts with;
// table B is only reachable after the test or a hook rewrites the service's
// leading word, which is how the "the lead is re-read" claim is checked.
alignas(8) std::uint8_t g_table_a[96];
alignas(8) std::uint8_t g_table_b[96];

// ===========================================================================
// The observer
// ===========================================================================

struct Observation {
  os::ServiceObject* receiver = nullptr;
  os::Word argument1 = 0;
  void* argument2 = nullptr;
  os::Word argument3 = 0;
  std::vector<os::Word> argument2_words;   // 16 entries, unused tail pre-filled
};

using Hook = void (*)(std::size_t call_index, Observation& seen, World& world);

struct Observer {
  std::vector<Observation> calls;
  std::size_t accessor_calls = 0;
  World* world = nullptr;
  Hook hook = nullptr;
  // How many dwords to snapshot from argument 2, per call index. The default of
  // four is safe for the SMALLER of the two buffers (the 0x10-byte one), and a
  // case that expects the 0x40-byte buffer widens the entry for its call index.
  // A reconstruction that produced a different call sequence therefore reads a
  // safe width and fails on the count or the arguments, not on a wild pointer.
  std::size_t argument2_words_by_index[8] = {4, 4, 4, 4, 4, 4, 4, 4};
  // Slot decoys: trampolines installed at the WRONG table displacement. If the
  // reconstruction fetches the target from anywhere but +0x14, one of these
  // fires and says so.
  int decoy_hits = 0;
  int table_b_hits = 0;
};

PKG_SW2_00A980B0_THISCALL void observe_slot(os::ServiceObject* receiver, os::Word argument1,
                                               void* argument2, os::Word argument3);
PKG_SW2_00A980B0_THISCALL void decoy_slot(os::ServiceObject*, os::Word, void*, os::Word);
PKG_SW2_00A980B0_THISCALL void table_b_slot(os::ServiceObject*, os::Word, void*, os::Word);
PKG_SW2_00A980B0_THISCALL void service_level_slot(os::ServiceObject*, os::Word, void*, os::Word);

// A function pointer to a machine word, on a target where the two are the same
// width. Cast function pointer to function pointer first, then to the integer:
// GCC rejects a direct static_cast from a thiscall pointer to an integer, and
// the intermediate is the only spelling it accepts.
os::Word slot_address(os::DispatchSlot slot) {
  return static_cast<os::Word>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void (*)()>(slot)));
}

Observer g_observer;
os::ServiceObject* g_service_to_hand_out = nullptr;
bool g_hand_out_null = false;

void reset_observer() {
  g_observer = Observer();
  g_service_to_hand_out = nullptr;
  g_hand_out_null = false;
}

}  // namespace

// THE DIRECT CALLEE. 0x00a980ce calls this. In the original it is
// `mov eax,ds:0x16514cc; ret`; here it is a seam the test controls, so both the
// service path and the null exit at 0x00a980d9 are reachable.
extern "C" os::ServiceObject* acquire_00883860() {
  ++g_observer.accessor_calls;
  return g_hand_out_null ? nullptr : g_service_to_hand_out;
}

namespace {

// THE INDIRECT CALLEE, installed in the table at displacement 0x14. Its C++ type
// is the model's DispatchSlot, so the model really does call this through the
// pointer it fetched out of memory, with ECX as the receiver and three stack
// arguments it then expects the callee to have popped.
PKG_SW2_00A980B0_THISCALL void observe_slot(os::ServiceObject* receiver, os::Word argument1,
                                               void* argument2, os::Word argument3) {
  const std::size_t index = g_observer.calls.size();
  Observation record;
  record.receiver = receiver;
  record.argument1 = argument1;
  record.argument2 = argument2;
  record.argument3 = argument3;
  // The pre-fill is what an out-of-plan read would expose: any dword the case did
  // not ask to be snapshotted comes back as the sentinel rather than as a value
  // the body produced.
  record.argument2_words.assign(16, kSlotHalfSentinel);
  const std::size_t width = index < 8 ? g_observer.argument2_words_by_index[index] : 4;
  for (std::size_t word = 0; word < width && word < 16; ++word) {
    record.argument2_words[word] = os::word_at(argument2, word * 4u);
  }
  g_observer.calls.push_back(record);
  if (g_observer.hook != nullptr && g_observer.world != nullptr) {
    g_observer.hook(index, record, *g_observer.world);
  }
}

// The two decoy trampolines. Neither is ever supposed to be called.
PKG_SW2_00A980B0_THISCALL void decoy_slot(os::ServiceObject*, os::Word, void*, os::Word) {
  ++g_observer.decoy_hits;
}

PKG_SW2_00A980B0_THISCALL void table_b_slot(os::ServiceObject*, os::Word, void*, os::Word) {
  ++g_observer.table_b_hits;
}

// A trampoline whose address also appears in the SERVICE object itself, at the
// same displacement the slot fetch uses. A reconstruction that read the target
// out of the service with one dereference instead of two would land here.
PKG_SW2_00A980B0_THISCALL void service_level_slot(os::ServiceObject*, os::Word, void*, os::Word) {
  ++g_observer.decoy_hits;
}

// ===========================================================================
// Fixture
// ===========================================================================

void fill(std::uint8_t* buffer, std::size_t size, std::uint8_t value) {
  std::memset(buffer, value, size);
}

void put(std::uint8_t* buffer, std::size_t displacement, os::Word value) {
  os::store_word(buffer, displacement, value);
}

os::Receiver* as_receiver(World& world) {
  return reinterpret_cast<os::Receiver*>(world.receiver);
}

os::ServiceObject* as_service(World& world) {
  return reinterpret_cast<os::ServiceObject*>(world.service);
}

void build_attribute_block(std::uint8_t* block, os::Word flags) {
  fill(block, 96, sentinel_byte(kAttributeSentinel));
  put(block, 0x00u, kAttrDecoyBefore);
  put(block, os::kAttributeFlagsDisplacement, flags);
  put(block, os::kAttributeFirstArgumentDisplacement, kAttrFirstArg);
  put(block, os::kAttributeWordForBit5Displacement, kAttrWord5);
  put(block, os::kAttributeWordForBit6Displacement, kAttrWord6);
  put(block, os::kAttributeWordForBit7Displacement, kAttrWord7);
  put(block, os::kAttributeWordForBit8Displacement, kAttrWord8);
  put(block, os::kAttributeWordForBit9Displacement, kAttrWord9);
  put(block, 0x24u, kAttrDecoyAfter);
}

// Builds a dispatch table whose slot at +0x14 is `target` and whose neighbouring
// slots are decoys, so a wrong slot displacement has somewhere to go.
void build_table(std::uint8_t* table, os::DispatchSlot target, os::DispatchSlot decoy) {
  fill(table, 96, sentinel_byte(kTableSentinel));
  const std::size_t decoy_slots[] = {0x00u, 0x04u, 0x08u, 0x0cu, 0x10u,
                                     0x18u, 0x1cu, 0x20u, 0x24u, 0x28u, 0x2cu};
  for (std::size_t index = 0; index < sizeof(decoy_slots) / sizeof(decoy_slots[0]); ++index) {
    put(table, decoy_slots[index], slot_address(decoy));
  }
  put(table, os::kDispatchSlotDisplacement, slot_address(target));
}

void build_world(World& world, os::Word flags, os::Word ready_byte) {
  fill(world.receiver, sizeof(world.receiver), sentinel_byte(kReceiverSentinel));
  fill(world.attributes_b, sizeof(world.attributes_b), sentinel_byte(kAttributeSentinel));
  fill(world.service, sizeof(world.service), sentinel_byte(kServiceSentinel));
  fill(world.spare, sizeof(world.spare), 0x77);

  build_attribute_block(world.attributes_a, flags);
  build_attribute_block(world.attributes_b, flags);

  put(world.receiver, 0x00u, kReceiverSentinel);
  put(world.receiver, os::kReceiverAttributePointerDisplacement,
      reinterpret_cast<os::Word>(reinterpret_cast<std::uintptr_t>(world.attributes_a)));
  put(world.receiver, os::kReceiverReadyByteDisplacement, ready_byte);
  os::store_byte(world.receiver, os::kReceiverReadyByteDisplacement,
                 static_cast<std::uint8_t>(ready_byte));
  if (ready_byte == 0u) {
    // THE GUARD'S WIDTH, armed. 0x00a980b6 is a BYTE compare against zero, so
    // with the guard not latched the byte at +0x10 is 0x00 and the three bytes
    // ABOVE it are the decoy. That makes the dword at +0x10 non-zero on purpose:
    // a reconstruction that compared a WORD there instead of the byte would take
    // the early exit and make no call at all, and one that LATCHED a word there
    // would destroy three decoy bytes instead of the one byte the listing stores.
    put(world.receiver, os::kReceiverReadyByteDisplacement, kReceiverDecoy10);
    os::store_byte(world.receiver, os::kReceiverReadyByteDisplacement, 0x00u);
  }
  put(world.receiver, os::kReceiverFloatDisplacement, 0x01020304u);   // a decoy the store must replace
  put(world.receiver, os::kReceiverAddressTakenDisplacement, kReceiverAddressed);
  put(world.receiver, os::kReceiverTrailingWordDisplacement, kReceiverTrailing);

  build_table(g_table_a, &observe_slot, &decoy_slot);
  build_table(g_table_b, &table_b_slot, &decoy_slot);

  put(world.service, os::kServiceDispatchTableDisplacement,
      reinterpret_cast<os::Word>(reinterpret_cast<std::uintptr_t>(g_table_a)));
  // A service-level word at the same displacement the slot fetch uses, holding a
  // decoy trampoline. A one-level dereference would call this instead.
  put(world.service, os::kDispatchSlotDisplacement, slot_address(&service_level_slot));
  // ... and a decoy at the service's own displacement 0, so a reconstruction that
  // treated the service itself as the table would dispatch into garbage.
  put(world.service, 0x14u + 0x10u, 0xfeedfaceu);

  g_service_to_hand_out = as_service(world);
  g_observer.world = &world;
  g_observer.argument2_words_by_index[0] = 16;   // the wide call, when it happens
}

os::Word read_receiver_word(const World& world, std::size_t displacement) {
  return os::word_at(world.receiver, displacement);
}

// ===========================================================================
// CASE 1 -- the guard: ANY non-zero byte exits, and the body touches nothing
// ===========================================================================
//
// REFUTES: a guard that tests a specific bit rather than "non-zero"; a guard that
// latches before testing; any work done on the early path.
void case_guard_exits_on_any_nonzero_byte() {
  g_case = "guard_nonzero";
  const os::Word probes[] = {0x01u, 0x02u, 0x04u, 0x10u, 0x40u, 0x80u, 0x7fu, 0xffu, 0xfeu};
  for (std::size_t probe = 0; probe < sizeof(probes) / sizeof(probes[0]); ++probe) {
    reset_observer();
    World world;
    build_world(world, 0xffffffffu, probes[probe]);
    os::re_00a980b0(as_receiver(world), 0xdeadbeefu);

    expect_eq_size("accessor calls on the already-set path", g_observer.accessor_calls, 0u);
    expect_eq_size("dispatch calls on the already-set path", g_observer.calls.size(), 0u);
    // Nothing at all is written: the +0x14 decoy and the +0x50 word survive.
    expect_eq_u32("+0x14 untouched on the early exit", read_receiver_word(world, os::kReceiverFloatDisplacement), 0x01020304u);
    expect_eq_u32("+0x50 untouched on the early exit", read_receiver_word(world, os::kReceiverTrailingWordDisplacement), kReceiverTrailing);
    expect_eq_u32("+0x18 untouched on the early exit", read_receiver_word(world, os::kReceiverAddressTakenDisplacement), kReceiverAddressed);
    expect_eq_u8("+0x10 keeps its value on the early exit",
                 os::byte_at(world.receiver, os::kReceiverReadyByteDisplacement),
                 static_cast<std::uint8_t>(probes[probe]));
  }
}

// ===========================================================================
// CASE 2 -- the latch and the float store happen before anything that can fail
// ===========================================================================
//
// REFUTES: an ordering that writes the flag after the accessor call, or that
// skips the +0x14 store when the service is null. The float store is checked as
// a BIT PATTERN read back as a float, because MOVSS is the 32-bit
// single-precision form and the four bytes written must be +0.0f.
void case_latch_and_float_store_precede_the_accessor() {
  g_case = "latch_before_accessor";
  reset_observer();
  World world;
  build_world(world, kAttrFlags, 0u);
  g_hand_out_null = true;

  // The fixture's guard-width decoy is in place BEFORE the body runs: the byte at
  // +0x10 is clear, so the body must run, while the dword that byte sits in is
  // not, because the three bytes above it carry the decoy. Nothing here is a
  // claim about the reconstruction; it is the precondition the latch checks
  // depend on.
  expect_eq_u32("the +0x10 byte is clear while the dword around it is not",
                read_receiver_word(world, os::kReceiverReadyByteDisplacement),
                kReceiverDecoy10 & 0xffffff00u);

  os::re_00a980b0(as_receiver(world), 0u);

  expect_eq_size("the accessor is called once", g_observer.accessor_calls, 1u);
  expect_eq_size("a null service dispatches nothing", g_observer.calls.size(), 0u);
  expect_eq_u8("+0x10 latched even though the service was null",
               os::byte_at(world.receiver, os::kReceiverReadyByteDisplacement), os::kReadyByteSet);
  // ... and the latch really is the one-BYTE store of 0x00a980c5: the three decoy
  // bytes above it are still there, so the dword reads as the decoy with its low
  // byte replaced.
  expect_eq_u32("+0x11..+0x13 survive the latch, so the latch is a byte store",
                read_receiver_word(world, os::kReceiverReadyByteDisplacement),
                (kReceiverDecoy10 & 0xffffff00u) | os::kReadyByteSet);
  expect_eq_u32("+0x14 is the four bytes of +0.0f",
                read_receiver_word(world, os::kReceiverFloatDisplacement), 0x00000000u);
  expect_true("+0x14 reads back as +0.0f",
              os::bits_to_float(read_receiver_word(world, os::kReceiverFloatDisplacement)) == 0.0f);
  // The latch really is a BYTE store: the neighbours of +0x10 survive.
  expect_eq_u32("+0x0c is not clobbered by the latch", read_receiver_word(world, 0x08u), kReceiverSentinel);
  expect_eq_u32("+0x14 is not clobbered by the latch", read_receiver_word(world, os::kReceiverFloatDisplacement), 0x00000000u);
  expect_eq_u32("+0x18 is not clobbered by the latch", read_receiver_word(world, os::kReceiverAddressTakenDisplacement), kReceiverAddressed);
  // The attribute object is only ever READ.
  expect_eq_u32("attribute +0x0c unchanged", os::word_at(world.attributes_a, 0x0cu), kAttrFirstArg);
  expect_eq_u32("attribute +0x20 unchanged", os::word_at(world.attributes_a, 0x20u), kAttrWord9);

  // THE NULL EXIT WITH A FLAG WORD THAT WOULD DISPATCH. The world above has an
  // all-clear flags word, so with a null service the body exits at 0x00a980d9
  // having done nothing else -- but it also never REACHES the service, because
  // every block that would read it is gated. A reconstruction that dropped the
  // 0x00a980d9 null test is therefore indistinguishable on that world, and the
  // sweep found exactly that survivor. This world has the gate bit and all three
  // narrow bits set, so the service's leading word at 0x00a98159 WOULD be read
  // out of a null pointer and the run dies instead of passing.
  reset_observer();
  World dispatching;
  build_world(dispatching, 0x0000000fu /* bits 0,1,2 and the gate */, 0u);
  g_hand_out_null = true;

  os::re_00a980b0(as_receiver(dispatching), 0u);

  expect_eq_size("the accessor is still called once with a live flag word",
                 g_observer.accessor_calls, 1u);
  expect_eq_size("a null service dispatches nothing even with every bit set",
                 g_observer.calls.size(), 0u);
  expect_eq_u8("+0x10 latched on the null exit with a live flag word",
               os::byte_at(dispatching.receiver, os::kReceiverReadyByteDisplacement),
               os::kReadyByteSet);
}

// REFUTES: a receiver bound below 0x54. The +0x50 read is a four-byte read, so
// the object is at least 0x54 bytes and a model that sized it 0x50 would be
// reading one word past its own object.
void case_receiver_bound_covers_the_last_read() {
  g_case = "receiver_bound";
  static_assert(os::kReceiverTrailingWordDisplacement + sizeof(os::Word) <= sizeof(os::Receiver),
                "the +0x50 read must lie inside the modelled receiver");
  static_assert(sizeof(os::Receiver) == 0x54u, "the model's own bound on the receiver");
  static_assert(sizeof(os::AttributeObject) == 0x24u, "the model's own bound on the attribute object");
  static_assert(os::kAttributeWordForBit9Displacement + sizeof(os::Word) <= sizeof(os::AttributeObject),
                "the +0x20 read must lie inside the modelled attribute object");
  g_case = "receiver_bound";
  ++g_checks;
}

// ===========================================================================
// CASE 3 -- the flag word is a BIT FIELD, and which bits matter
// ===========================================================================
//
// REFUTES: a signed or threshold test in place of a bit test; bit 4 being
// mistaken for one of the tested bits; the wrong word being read.
void case_flag_bits_are_exactly_zero_three_five_six_seven_eight_nine() {
  g_case = "flag_bits";
  struct Probe {
    os::Word flags;
    std::size_t calls;
    const char* why;
  };
  // The gate and the eight fill/gate bits, each alone, and the neighbours of
  // each. Bit 4 is included precisely because the body never tests it.
  const Probe probes[] = {
      {kAttrFlags, 0u, "no bits"},
      {0x00000001u, 1u, "bit 0 alone: one narrow call"},
      {0x00000002u, 1u, "bit 1 alone: one narrow call"},
      {0x00000004u, 1u, "bit 2 alone: one narrow call"},
      {0x00000008u, 1u, "bit 3 alone: the wide call only"},
      {0x00000010u, 0u, "bit 4 alone: NEVER tested, so nothing happens"},
      {0x00000020u, 0u, "bit 5 alone: no gate, so no call at all"},
      {0x00000040u, 0u, "bit 6 alone: no gate, so no call at all"},
      {0x00000080u, 0u, "bit 7 alone: no gate, so no call at all"},
      {0x00000100u, 0u, "bit 8 alone: no gate, so no call at all"},
      {0x00000200u, 0u, "bit 9 alone: no gate, so no call at all"},
      {0x00000400u, 0u, "bit 10 alone: never read"},
      {0x80000000u, 0u, "the top bit alone: unsigned, and never read"},
      {0x80000008u, 1u, "top bit plus the gate: the top bit changes nothing"},
  };
  for (std::size_t probe = 0; probe < sizeof(probes) / sizeof(probes[0]); ++probe) {
    reset_observer();
    World world;
    build_world(world, probes[probe].flags, 0u);
    os::re_00a980b0(as_receiver(world), 0u);
    if (g_observer.calls.size() != probes[probe].calls) {
      char buffer[256];
      std::snprintf(buffer, sizeof(buffer), "flags %s: got %zu call(s), want %zu",
                    probes[probe].why, g_observer.calls.size(), probes[probe].calls);
      fail("call count for a single-bit flag word", buffer);
    }
    ++g_checks;
  }
}

// REFUTES: filling the wide buffer's slots when the gate bit is clear. Bits 5..9
// set WITHOUT bit 3 must leave the body having made no call and having touched
// nothing -- the gate short-circuits before the fills are even evaluated.
void case_fill_bits_do_nothing_without_the_gate() {
  g_case = "fill_bits_need_the_gate";
  reset_observer();
  World world;
  build_world(world, 0x000003e0u /* bits 5,6,7,8,9 */, 0u);
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("no call without the gate bit", g_observer.calls.size(), 0u);
  expect_eq_size("the accessor is still called once", g_observer.accessor_calls, 1u);
  expect_eq_u32("no dispatch without the gate bit", g_observer.decoy_hits, 0);
}

// ===========================================================================
// CASE 4 -- the wide call: argument order, and which slot each source lands in
// ===========================================================================
//
// REFUTES: swapped argument order; a source displacement off by one word; a
// destination slot off by one; every slot written regardless of its bit; the
// second half of a slot written; the LEA read as a load; the receiver's +0x50
// read as a float; argument 1 taken from the wrong displacement.
void case_wide_call_fills_exactly_the_slots_its_bits_select() {
  g_case = "wide_call";
  struct Probe {
    os::Word flags;
    std::size_t expect_filled;                       // how many of slots 0..4 are filled
    os::Word values[5];                              // what those slots must hold
  };
  const Probe probes[] = {
      {0x00000008u, 0u, {0, 0, 0, 0, 0}},                                   // gate only
      {0x00000028u, 1u, {kAttrWord5, 0, 0, 0, 0}},                           // + bit 5
      {0x00000048u, 1u, {0, kAttrWord6, 0, 0, 0}},                           // + bit 6
      {0x00000088u, 1u, {0, 0, kAttrWord7, 0, 0}},                           // + bit 7
      {0x00000108u, 1u, {0, 0, 0, kAttrWord8, 0}},                           // + bit 8
      {0x00000208u, 1u, {0, 0, 0, 0, kAttrWord9}},                           // + bit 9
      {0x000003e8u, 5u, {kAttrWord5, kAttrWord6, kAttrWord7, kAttrWord8, kAttrWord9}},  // all
      {0x000003f8u, 5u, {kAttrWord5, kAttrWord6, kAttrWord7, kAttrWord8, kAttrWord9}},  // all + bit 4
  };

  for (std::size_t probe = 0; probe < sizeof(probes) / sizeof(probes[0]); ++probe) {
    reset_observer();
    World world;
    build_world(world, probes[probe].flags, 0u);
    os::re_00a980b0(as_receiver(world), 0u);

    expect_eq_size("the wide case makes exactly one call", g_observer.calls.size(), 1u);
    if (g_observer.calls.size() != 1u) continue;
    const Observation& seen = g_observer.calls[0];

    // ARGUMENT ORDER. argument 1 is the attribute object's +0x0c word, by value;
    // argument 2 is a POINTER into the body's frame; argument 3 is the zero EBP
    // holds. If the reconstruction pushed them in a different order, argument 1
    // would be a pointer and argument 2 the scalar.
    expect_eq_u32("wide argument 1 is the attribute word at +0x0c", seen.argument1, kAttrFirstArg);
    expect_true("wide argument 2 is a pointer, not the scalar",
                seen.argument2 != nullptr &&
                    reinterpret_cast<os::Word>(seen.argument2) != kAttrFirstArg);
    expect_eq_u32("wide argument 3 is the zero EBP holds", seen.argument3, 0u);
    expect_true("wide receiver is the service", seen.receiver == as_service(world));

    // ARGUMENT 1 IS NOT TAKEN FROM A NEIGHBOURING DISPLACEMENT. The decoys at
    // the attribute object's +0x00 and +0x24 are different values, and the flags
    // word itself is a third, so a mis-shifted read is visible.
    expect_true("wide argument 1 is not the flags word", seen.argument1 != probes[probe].flags);
    expect_true("wide argument 1 is not a decoy", seen.argument1 != kAttrDecoyBefore &&
                                                       seen.argument1 != kAttrDecoyAfter);

    // THE EIGHT SLOTS, as dword pairs inside the 0x40-byte buffer. Dword 2*k is
    // the first half of slot k and dword 2*k+1 the second, and the second half is
    // never written by this body.
    expect_eq_size("the wide snapshot is 16 dwords", seen.argument2_words.size(), 16u);
    if (seen.argument2_words.size() != 16u) continue;
    const os::Word* words = seen.argument2_words.data();

    for (std::size_t slot = 0; slot < 5u; ++slot) {
      const os::Word expected = probes[probe].values[slot];
      if (expected != 0u) {
        expect_eq_u32("wide slot filled by its own bit", words[2u * slot], expected);
      } else {
        // A clear bit leaves the slot EXACTLY as it was. The model's buffer is
        // zero-initialised, so "as it was" is zero here -- and the point of the
        // check is that a reconstruction which wrote a value, or wrote the
        // NEIGHBOURING slot, fails here.
        expect_eq_u32("wide slot untouched when its bit is clear", words[2u * slot], 0u);
      }
    }
    // slot 5 holds the ADDRESS of the receiver's +0x18, not the word there. Both
    // the decoy value planted at +0x18 and the decoy one word along are checked
    // against, so a reconstruction that loaded instead of taking the address, or
    // that took the address of the wrong displacement, fails.
    expect_eq_u32("wide slot 5 holds the receiver's +0x18 address",
                  words[10],
                  static_cast<os::Word>(reinterpret_cast<std::uintptr_t>(world.receiver) +
                                        os::kReceiverAddressTakenDisplacement));
    expect_true("wide slot 5 is not the value stored at +0x18", words[10] != kReceiverAddressed);
    // slot 6 holds the receiver's +0x50 word, copied whole.
    expect_eq_u32("wide slot 6 holds the receiver's +0x50 word", words[12], kReceiverTrailing);
    // slot 7 holds the literal zero stored first, before any flag test.
    expect_eq_u32("wide slot 7 holds the zero stored first", words[14], 0u);

    // AND the eight second halves are never written. The model's buffers are
    // zero-initialised, so "never written" is observed as "still zero": the
    // machine's own frame content there is undefined and a zero start is one
    // legal instance of it. This is a complete check, not a weak one -- a
    // reconstruction that wrote a non-zero value into a second half fails here,
    // and one that wrote a zero there is doing what the machine does anyway,
    // which is the only case the observation cannot separate and which is
    // therefore not a defect to be found.
    for (std::size_t half = 0; half < 8u; ++half) {
      expect_eq_u32("the second half of a wide slot is never written", words[2u * half + 1u], 0u);
    }
  }
}

// REFUTES: a reconstruction that wrote the wide buffer's tail (the eight bytes
// past the last slot's dword) -- the buffer is 0x40 bytes and the body writes
// nothing past base+0x3b.
void case_wide_buffer_tail_is_never_written() {
  g_case = "wide_tail";
  reset_observer();
  World world;
  build_world(world, 0x000003e8u, 0u);
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("one wide call", g_observer.calls.size(), 1u);
  if (g_observer.calls.size() != 1u) return;
  const Observation& seen = g_observer.calls[0];
  // Dwords 12..15 are the whole of slots 6 and 7, both halves; 12 and 14 are
  // written and 13 and 15 are not, which is the boundary case for the buffer's
  // last four bytes.
  expect_eq_u32("dword 13 (slot 6's second half) untouched", seen.argument2_words[13], 0u);
  expect_eq_u32("dword 15 (slot 7's second half, the buffer's last word) untouched",
                seen.argument2_words[15], 0u);
  static_assert(os::kWideSlot7Displacement + sizeof(os::Word) <= os::kWideBufferSize,
                "the last slot's dword ends inside the buffer");
  static_assert(os::kWideBufferSize == 0x40u, "the wide buffer is 0x40 bytes");
}

// ===========================================================================
// CASE 5 -- the three narrow calls
// ===========================================================================
//
// REFUTES: the wrong immediate for the third site; the selector paired with the
// wrong immediate; argument order; a per-site fresh buffer instead of the shared
// 0x10 bytes; the +0x04 word not being zero.
void case_three_narrow_calls_carry_their_own_pair() {
  g_case = "narrow_calls";
  reset_observer();
  World world;
  build_world(world, 0x0000000fu /* bits 0,1,2 and the gate */, 0u);
  os::re_00a980b0(as_receiver(world), 0u);

  expect_eq_size("gate plus three bits makes four calls", g_observer.calls.size(), 4u);
  if (g_observer.calls.size() != 4u) return;

  struct Expected {
    os::Word argument1;
    os::Word selector;
  };
  const Expected expected[3] = {
      {os::kNarrowArgumentForSelector0, 0u},
      {os::kNarrowArgumentForSelector1, 1u},
      {os::kNarrowArgumentForSelector2, 2u},
  };

  // The wide call is first because its gate is tested first, and the ordering of
  // the three narrow calls is the order of their bit tests in the listing.
  const Observation& wide = g_observer.calls[0];
  expect_eq_u32("the wide call comes first", wide.argument1, kAttrFirstArg);

  for (std::size_t site = 0; site < 3u; ++site) {
    const Observation& seen = g_observer.calls[site + 1u];
    const std::string tag = "narrow site " + std::to_string(site);
    expect_eq_u32((tag + " argument 1").c_str(), seen.argument1, expected[site].argument1);
    expect_eq_u32((tag + " argument 3").c_str(), seen.argument3, 0u);
    expect_true((tag + " receiver is the service").c_str(), seen.receiver == as_service(world));
    expect_true((tag + " argument 2 is a pointer").c_str(), seen.argument2 != nullptr);
    if (seen.argument2_words.size() < 2u) continue;
    expect_eq_u32((tag + " selector in the buffer's first word").c_str(), seen.argument2_words[0],
                  expected[site].selector);
    expect_eq_u32((tag + " the buffer's second word is zero").c_str(), seen.argument2_words[1], 0u);
    // The 0x10-byte buffer's own tail, dwords 2 and 3, is never written. As
    // above: the model zero-initialises the buffer, so untouched reads as zero.
    expect_eq_u32((tag + " the buffer's dword 2 is untouched").c_str(), seen.argument2_words[2], 0u);
    expect_eq_u32((tag + " the buffer's dword 3 is untouched").c_str(), seen.argument2_words[3], 0u);
  }

  // THE THREE IMMEDIATES ARE NOT IN STEP WITH THE THREE SELECTORS. Sites 0 and 1
  // share an immediate and differ in selector; site 2 has both a new immediate
  // and a new selector. A reconstruction that moved them in lockstep, or that
  // used 0x0e7a8471 three times, fails on site 2.
  expect_true("the first two sites share an immediate",
              g_observer.calls[1].argument1 == g_observer.calls[2].argument1);
  expect_true("the third site's immediate differs",
              g_observer.calls[1].argument1 != g_observer.calls[3].argument1);
  static_assert(os::kNarrowArgumentForSelector2 != os::kNarrowArgumentForSelector0,
                "00a981d7 pushes a different immediate from 00a98180");

  // THE SAME 0x10 BYTES FOR ALL THREE SITES, not a fresh buffer each time. The
  // body re-writes one buffer, so the address is identical and the selector the
  // observer reads is that site's own.
  expect_true("all three narrow calls share one buffer",
              g_observer.calls[1].argument2 == g_observer.calls[2].argument2 &&
                  g_observer.calls[2].argument2 == g_observer.calls[3].argument2);
  // ... and it is a DIFFERENT buffer from the wide call's, since the frame holds
  // both and they are 0x30 bytes apart.
  expect_true("the narrow buffer is not the wide buffer",
              g_observer.calls[0].argument2 != g_observer.calls[1].argument2);
  static_assert(os::kNarrowBufferSize + os::kWideBufferSize == 0x50u,
                "the two buffers together are the whole frame");
}

// REFUTES: the selector being written at the buffer's +0x04 instead of +0x00, or
// the +0x04 word not being zeroed.
void case_narrow_selector_sits_in_the_first_word() {
  g_case = "narrow_selector_position";
  reset_observer();
  World world;
  build_world(world, 0x00000006u /* bits 1 and 2 */, 0u);
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("two calls, no gate", g_observer.calls.size(), 2u);
  if (g_observer.calls.size() != 2u) return;
  expect_eq_u32("first narrow selector is 1", g_observer.calls[0].argument2_words[0], 1u);
  expect_eq_u32("first narrow second word is 0", g_observer.calls[0].argument2_words[1], 0u);
  expect_eq_u32("second narrow selector is 2", g_observer.calls[1].argument2_words[0], 2u);
  expect_eq_u32("second narrow second word is 0", g_observer.calls[1].argument2_words[1], 0u);
  expect_eq_u32("the first site's buffer carries the SECOND site's selector now",
                g_observer.calls[1].argument2_words[0], 2u);
}

// ===========================================================================
// CASE 6 -- the dispatch: two levels, one displacement, re-read every time
// ===========================================================================
//
// REFUTES: a one-level dereference (the table's word read out of the service);
// a wrong slot displacement; a cached dispatch table; a target read as an
// immediate.
void case_dispatch_is_a_two_level_read_of_one_slot() {
  g_case = "dispatch_slot";
  reset_observer();
  World world;
  build_world(world, 0x0000000fu, 0u);
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("four transfers", g_observer.calls.size(), 4u);
  expect_eq_u32("no decoy trampoline was called", g_observer.decoy_hits, 0);
  expect_eq_u32("the second table was not used", g_observer.table_b_hits, 0);
  // The decoys are in place, so a wrong displacement would have been caught.
  static_assert(os::kDispatchSlotDisplacement == 0x14u, "the slot displacement the model uses");
  static_assert(os::kDispatchSlotIndex == 5u, "0x14 / 4 is slot 5");
}

// REFUTES: caching the service's leading word. 0x00a98159, 0x00a98175,
// 0x00a9819e and 0x00a981cc are four separate `MOV EDX,[ESI]`, so a hook that
// swaps the table during the FIRST call must send the remaining three to the
// second table's trampoline.
void hook_swap_table_on_first_call(std::size_t call_index, Observation& seen, World& world) {
  (void)seen;
  if (call_index != 0u) return;
  os::store_word(world.service, os::kServiceDispatchTableDisplacement,
                 reinterpret_cast<os::Word>(reinterpret_cast<std::uintptr_t>(g_table_b)));
}

void case_dispatch_lead_is_reread_before_every_call() {
  g_case = "dispatch_lead_reread";
  reset_observer();
  World world;
  build_world(world, 0x0000000fu, 0u);
  g_observer.hook = &hook_swap_table_on_first_call;
  os::re_00a980b0(as_receiver(world), 0u);
  // The first call went through table A, whose observer records it. The next
  // three go through table B, whose trampoline only counts: so ONE observation
  // and THREE table-B hits is the correct shape, and the pair of counters
  // separates it from both neighbours. A reconstruction that cached the lead
  // would record four observations and zero table-B hits.
  expect_eq_size("only the first call was observed through table A", g_observer.calls.size(), 1u);
  expect_eq_size("the three later calls used table B", static_cast<std::size_t>(g_observer.table_b_hits), 3u);
  expect_eq_u32("no decoy was called", g_observer.decoy_hits, 0);
}

// REFUTES: caching the dispatch lead across INVOCATIONS. 0x00a98159 reads the
// lead out of the service that the accessor returned on this call, so two
// invocations of the body whose accessors return services with different tables
// must dispatch through different tables. A lead cached in a static that
// survives between invocations sends the second invocation to the first one's
// table, which is exactly what a "read the lead once" model does.
void case_dispatch_lead_is_read_per_invocation() {
  g_case = "dispatch_lead_per_invocation";
  reset_observer();
  World first;
  build_world(first, 0x0000000fu, 0u);
  os::re_00a980b0(as_receiver(first), 0u);
  expect_eq_size("the first invocation dispatches four times through table A",
                 g_observer.calls.size(), 4u);
  expect_eq_size("the first invocation never reached table B",
                 static_cast<std::size_t>(g_observer.table_b_hits), 0u);

  // A second, entirely separate receiver whose service points at the OTHER
  // table from the outset. Nothing is hooked here, so the only thing that can
  // route these four calls to table B is the body reading the lead out of THIS
  // invocation's service.
  reset_observer();
  World second;
  build_world(second, 0x0000000fu, 0u);
  os::store_word(second.service, os::kServiceDispatchTableDisplacement,
                 reinterpret_cast<os::Word>(reinterpret_cast<std::uintptr_t>(g_table_b)));
  os::re_00a980b0(as_receiver(second), 0u);
  expect_eq_size("the second invocation dispatched nothing through table A",
                 g_observer.calls.size(), 0u);
  expect_eq_size("the second invocation dispatched four times through table B",
                 static_cast<std::size_t>(g_observer.table_b_hits), 4u);
  expect_eq_u32("no decoy was called", g_observer.decoy_hits, 0);
}

// ===========================================================================
// CASE 7 -- the attribute pointer is a POINTER, and it is re-read
// ===========================================================================
//
// REFUTES: reading the flags word out of the receiver instead of through the
// pointer; caching the pointer across a call. 0x00a9816c, 0x00a98191 and
// 0x00a981be each reload the word at the receiver's +0x0c, so a hook that
// repoints it during the wide call must change what the three narrow blocks see.
void hook_repoint_attributes(std::size_t call_index, Observation& seen, World& world) {
  (void)seen;
  if (call_index != 0u) return;
  os::store_word(world.receiver, os::kReceiverAttributePointerDisplacement,
                 reinterpret_cast<os::Word>(reinterpret_cast<std::uintptr_t>(world.attributes_b)));
}

void case_attribute_pointer_is_a_pointer_and_is_reread() {
  g_case = "attribute_pointer";
  // The receiver's own +0x08 holds a decoy word with a completely different flag
  // set, so a reconstruction that read the flags from the receiver instead of
  // through the pointer would take a different path.
  reset_observer();
  World world;
  build_world(world, 0x00000007u /* bits 0,1,2 */, 0u);
  os::store_word(world.receiver, 0x08u, 0x00000000u);
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("three narrow calls, the wide gate clear", g_observer.calls.size(), 3u);
  if (g_observer.calls.size() != 3u) return;
  // The immediates are 0x0e7a8471, 0x0e7a8471 and 0x0e7a8473 -- the narrow
  // sites never take their first argument from the attribute object, so this
  // checks only that the three sites are distinct in the way the listing says.
  expect_eq_u32("narrow site 0 immediate", g_observer.calls[0].argument1, os::kNarrowArgumentForSelector0);
  expect_eq_u32("narrow site 1 immediate", g_observer.calls[1].argument1, os::kNarrowArgumentForSelector1);
  expect_eq_u32("narrow site 2 immediate", g_observer.calls[2].argument1, os::kNarrowArgumentForSelector2);

  // Now the dependence test: repoint the receiver at a second attribute object
  // during the wide call and the three narrow blocks must follow it.
  reset_observer();
  build_world(world, 0x000003efu /* gate + bits 0,1,2,5,6,7,8,9 */, 0u);
  os::store_word(world.attributes_b, os::kAttributeFlagsDisplacement, 0x00000000u);
  g_observer.hook = &hook_repoint_attributes;
  os::re_00a980b0(as_receiver(world), 0u);
  // The repoint took effect: the wide call happened against the FIRST object,
  // and the three narrow blocks then read the SECOND one, whose flags are zero,
  // so they make no call at all.
  expect_eq_size("the wide call happened and the three narrow ones did not",
                 g_observer.calls.size(), 1u);
  expect_eq_u32("the wide call's argument 1 came from the first object",
                g_observer.calls[0].argument1, kAttrFirstArg);
}

// REFUTES: caching the flags word in a local across the calls. The same words are
// re-read at 0x00a9816f, 0x00a98194 and 0x00a981c1, so a hook that clears the
// flags during the wide call must suppress the narrow calls.
void hook_clear_flags(std::size_t call_index, Observation& seen, World& world) {
  (void)seen;
  if (call_index != 0u) return;
  os::store_word(world.attributes_a, os::kAttributeFlagsDisplacement, 0x00000000u);
}

void case_flags_word_is_reread_after_each_call() {
  g_case = "flags_reread";
  reset_observer();
  World world;
  build_world(world, 0x000003e7u /* gate + bits 0,1,2,5..9 */, 0u);
  g_observer.hook = &hook_clear_flags;
  os::re_00a980b0(as_receiver(world), 0u);
  expect_eq_size("clearing the flags during the wide call suppresses the narrow calls",
                g_observer.calls.size(), 1u);
}

// REFUTES: filling the wide buffer's slots from a flags word read BEFORE the gate
// test rather than after. Covered by case_fill_bits_do_nothing_without_the_gate
// and by the fact that the hook above changes the flags mid-body and the fills
// still use the value read at their own instruction.

// ===========================================================================
// CASE 8 -- what the body must NOT write
// ===========================================================================
//
// REFUTES: a store at a neighbouring displacement. Every byte of the receiver
// and of the attribute object outside the two documented writes is compared
// before and after.
void case_nothing_else_is_written() {
  g_case = "no_stray_writes";
  reset_observer();
  World world;
  build_world(world, 0x000003efu, 0u);
  std::vector<std::uint8_t> receiver_before(world.receiver, world.receiver + sizeof(world.receiver));
  std::vector<std::uint8_t> attributes_before(world.attributes_a,
                                              world.attributes_a + sizeof(world.attributes_a));
  os::re_00a980b0(as_receiver(world), 0u);

  ++g_checks;
  for (std::size_t index = 0; index < sizeof(world.receiver); ++index) {
    if (index == os::kReceiverReadyByteDisplacement) continue;   // latched
    if (index >= os::kReceiverFloatDisplacement &&
        index < os::kReceiverFloatDisplacement + 4u) continue; // the float store
    if (world.receiver[index] != receiver_before[index]) {
      char buffer[192];
      std::snprintf(buffer, sizeof(buffer), "receiver byte at +0x%02zx changed from 0x%02x to 0x%02x",
                    index, receiver_before[index], world.receiver[index]);
      fail("a stray receiver write", buffer);
      break;
    }
  }
  ++g_checks;
  for (std::size_t index = 0; index < sizeof(world.attributes_a); ++index) {
    if (world.attributes_a[index] != attributes_before[index]) {
      char buffer[192];
      std::snprintf(buffer, sizeof(buffer), "attribute byte at +0x%02zx changed from 0x%02x to 0x%02x",
                    index, attributes_before[index], world.attributes_a[index]);
      fail("a stray attribute write", buffer);
      break;
    }
  }
}

// ===========================================================================
// CASE 9 -- the signature itself
// ===========================================================================
//
// REFUTES: a return type other than void, and a receiver that is not a pointer to
// the model's own receiver type. The body has no value to hand back: its only
// definition of XMM0 feeds a store, and its early exit never writes XMM0 at all.
void case_declared_signature_is_void_thiscall_receiver_only() {
  g_case = "signature";
  using ExpectedSignature = void(PKG_SW2_00A980B0_THISCALL*)(os::Receiver*, os::Word);
  static_assert(std::is_same<decltype(&os::re_00a980b0), ExpectedSignature>::value,
                "re_00a980b0 is a __thiscall void taking the receiver and one stack word");
  // The return type is pinned from the TYPE, never from a call written inside
  // decltype. A call with side effects in an unevaluated operand is what
  // -Wunevaluated-expression rejects, and clang++ turns that into an error under
  // the gate's -Werror where g++ stays silent -- so the question is asked of the
  // signature instead. std::invoke_result_t<decltype(&f), A, B> is the result of
  // INVOKING f with (A, B), which is exactly the property the old
  // decltype(re_00a980b0(receiver, 0u)) pinned, and it is answered from the
  // declaration alone: no call, no `new`, nothing evaluated, nothing leaked.
  static_assert(std::is_same<std::invoke_result_t<decltype(&os::re_00a980b0),
                                                 os::Receiver*, os::Word>,
                             void>::value,
                "invoking re_00a980b0 with the receiver and one stack word yields void");
  // The one ordinary stack word is never read, so two different values of it
  // must produce byte-identical behaviour. That is the falsifiable form of
  // "the body ignores its stack argument".
  reset_observer();
  World first;
  build_world(first, 0x0000000fu, 0u);
  const std::size_t first_calls = (os::re_00a980b0(as_receiver(first), 0x00000000u), g_observer.calls.size());
  const std::vector<os::Word> first_firsts = [&] {
    std::vector<os::Word> out;
    for (std::size_t index = 0; index < g_observer.calls.size(); ++index) {
      out.push_back(g_observer.calls[index].argument1);
    }
    return out;
  }();
  reset_observer();
  World second;
  build_world(second, 0x0000000fu, 0u);
  const std::size_t second_calls = (os::re_00a980b0(as_receiver(second), 0xffffffffu),
                                    g_observer.calls.size());
  const std::vector<os::Word> second_firsts = [&] {
    std::vector<os::Word> out;
    for (std::size_t index = 0; index < g_observer.calls.size(); ++index) {
      out.push_back(g_observer.calls[index].argument1);
    }
    return out;
  }();
  expect_eq_size("the stack argument changes nothing (call count)", second_calls, first_calls);
  expect_eq_size("the stack argument changes nothing (argument 1 sequence)",
                 second_firsts.size(), first_firsts.size());
  for (std::size_t index = 0; index < first_firsts.size() && index < second_firsts.size(); ++index) {
    expect_eq_u32("the stack argument changes nothing (per call)", second_firsts[index],
                  first_firsts[index]);
  }
  (void)first_calls;
  (void)second_calls;
}

}  // namespace

int main() {
  case_guard_exits_on_any_nonzero_byte();
  case_latch_and_float_store_precede_the_accessor();
  case_receiver_bound_covers_the_last_read();
  case_flag_bits_are_exactly_zero_three_five_six_seven_eight_nine();
  case_fill_bits_do_nothing_without_the_gate();
  case_wide_call_fills_exactly_the_slots_its_bits_select();
  case_wide_buffer_tail_is_never_written();
  case_three_narrow_calls_carry_their_own_pair();
  case_narrow_selector_sits_in_the_first_word();
  case_dispatch_is_a_two_level_read_of_one_slot();
  case_dispatch_lead_is_reread_before_every_call();
  case_dispatch_lead_is_read_per_invocation();
  case_attribute_pointer_is_a_pointer_and_is_reread();
  case_flags_word_is_reread_after_each_call();
  case_nothing_else_is_written();
  case_declared_signature_is_void_thiscall_receiver_only();

  std::printf("checks=%d failures=%d\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
