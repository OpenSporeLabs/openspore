// Focused semantic test for FUN_00c71e30 @ 0x00c71e30.
//
// The target body is twenty-one instructions with two guards, one indirect
// dispatch and one pushed word, so almost everything a reconstruction of it can
// get wrong is a claim about a NUMBER or about which of four near-identical
// operations produced a value. Each group below names the hypothesis it tries
// to REFUTE:
//
//   1. both guards are real and both converge on ONE null arm - so dropping
//      either, inverting either, or making the compared constant anything other
//      than 5 each fail;
//   2. 0x13c is the word this body reads, and it is a BYTE displacement - so a
//      planted decoy on each side with a value that differs in the word the
//      downstream guard sees catches a one-word slip BY VALUE, not by faulting;
//   3. the delegation hands the word at +0x13c to 0x00b8dab0 as a RECEIVER,
//      and the compared value is the DELEGATED object's word at +0x194 - so a
//      hand-over of this body's own receiver, or a read of the receiver's own
//      +0x194, is a different answer;
//   4. the table word is LOADED and the dispatch's receiver is its ADDRESS -
//      the load/LEA distinction - so passing the stored pointer, or passing this
//      body's own receiver, both fail;
//   5. the slot is the word at table+0x4c, and a wrong index is OBSERVABLE -
//      every word from +0x40 to +0x5c is a callable slot of its own and a
//      sentinel sits immediately past +0x5c, so a slot index off by one, two,
//      three or four calls a DIFFERENT callee that says so, and one further lands
//      on the trap. This is the defect
//      src/reconstruction/pkg_job_continuation_0068f9b0/ was fixed for, where an
//      overrun aliased a neighbouring valid pointer and the test passed anyway;
//   6. the pushed word reaches the LAST callee and is popped by that callee's
//      `RET 0x4` - while `POP ESI` restores the CALLER's ESI - so this is
//      MEASURED off ESP, not asserted;
//   7. the passing arm returns the LAST call's result verbatim, the null arm
//      returns a full 32-bit zero, and the two arms' values are told apart;
//   8. the encoding IS the observed fifty-nine bytes, and every ModRM, opcode,
//      disp and rel8 is decoded - including the `8b`/`8d` pair over one
//      displacement, the `83 f8` sign-extended compare, the `33 c0` full-width
//      zeroing and the two bare RETs.
//
// A NOTE ON MEASUREMENT. Nothing here trusts a comment. The stack facts are
// sampled: ESP is read immediately before the entry is called and again the
// instant it has returned, and the two must agree. That measurement is what a
// reconstruction with a hidden stack argument, or with callee cleanup, fails -
// and because the two modelled callees carry the machine's own interfaces
// (`helper_00b3d2a0` with no argument and a bare RET, `lookup_empire_00ba9370`
// with one stack argument and the `RET 0x4` that i386 `__thiscall` emits for
// it), the four bytes the last callee pops are real in the emitted code rather
// than described in one. The receiver given to the dispatch is likewise observed
// from inside the callee, so "the argument is the ADDRESS and not the stored
// word" is checked by the callee itself and not by reading the fixture back.

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <vector>

#include "empire5_00c71e30.hpp"

#if defined(_MSC_VER)
#define PKG_00C71E30_THISCALL __thiscall
#else
#define PKG_00C71E30_THISCALL __attribute__((thiscall))
#endif

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00c71e30 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00c71e30_empire5 {
namespace model {

// DELIBERATELY NOT INLINED. This is the harness, and it must be opaque to the
// optimizer for the same reason the call trampolines below are: an inlined
// `check` lets the compiler recompute or fold the very expression the assertion
// is about, and it did. Measured, at -O2 and above on both compilers, the only
// difference between a green run and a failing one was whether this function
// was inlinable - and the failure was never a wrong reconstruction, it was the
// ESP balance check reading samples whose storage the optimizer had reallocated
// around the assembly block. An opaque call keeps every condition exactly as
// written, which is the only thing an assertion is entitled to assume.
__attribute__((noinline)) void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

SlotWord pointer_word(const void* pointer) {
  return static_cast<SlotWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The raw encoding is the observed one; the whole of group 8 restates it.
static_assert(sizeof(kTargetEncoding) == kTargetBodyBytes,
              "the raw encoding array is the modelled body length");
static_assert(kTargetEncoding[0] == 86u && kTargetEncoding[13] == 232u &&
                  kTargetEncoding[54] == 195u && kTargetEncoding[58] == 195u,
              "the encoding begins at 0x00c71e30 and both exits are bare RETs");
static_assert(kTargetEncoding[23] == 139u && kTargetEncoding[32] == 141u,
              "0x00c71e47 is 0x8b and 0x00c71e50 is 0x8d over the SAME "
              "displacement - the load/address distinction, in the bytes");
static_assert(kTargetEncoding[23] != kTargetEncoding[32],
              "one displacement, two opcodes: a MOV and a LEA");

// ---------------------------------------------------------------------------
// Tags. Every modelled callee records itself, so a dispatch that reaches the
// wrong one is a stated failure rather than a silent wrong answer. The sentinel
// tag is never a legal record on any path this body can take.
// ---------------------------------------------------------------------------

constexpr std::uint8_t kTagTargetSlot = 0x4c;
constexpr std::uint8_t kTagDecoy40 = 0x40;
constexpr std::uint8_t kTagDecoy44 = 0x44;
constexpr std::uint8_t kTagDecoy48 = 0x48;
constexpr std::uint8_t kTagDecoy50 = 0x50;
constexpr std::uint8_t kTagDecoy54 = 0x54;
constexpr std::uint8_t kTagDecoy58 = 0x58;
constexpr std::uint8_t kTagDecoy5c = 0x5c;
constexpr std::uint8_t kTagSentinel = 0xf0;
constexpr std::uint8_t kTagTrapTable = 0xe0;

// The values the three callees' results are distinguished by. Different on
// purpose: a mutant that swaps two of them is caught by VALUE, not only by the
// order of the log.
constexpr SlotWord kLookupResult = 0x13579bdfu;

// The receiver's own sentinels. Every one differs from every other, so
// "one word too low" and "one word too high" are separate failures rather than
// one.
constexpr SlotWord kReceiverHeadSentinel = 0xfeedfaceu;
constexpr SlotWord kNearHeadSentinel = 0x0badf00du;
constexpr SlotWord kTailSentinel = 0xa5a5f00du;

// The word the delegated object reports. 5 is the ONLY value that lets the
// second guard pass, so a decoy that reports anything else turns a wrong
// displacement into a published zero - caught by value, never by a fault.
constexpr SlotWord kDelegatedReportedScalar = 0x5;
constexpr SlotWord kDecoyReportedScalar = 0x11111111u;

// The value a decoy dispatched object must hand back if the model ever reaches
// it. It is different from kLookupResult so the two are told apart by value.
constexpr SlotWord kDecoySlotResult = 0x2468ace0u;

// The words the two index tokens carry, so the receiver identity checks have a
// value to pair with as well as a pointer to compare.
constexpr SlotWord kGlobalSlotValue = 0x5a5aa5a4u;
constexpr SlotWord kOtherIndexValue = 0x0c0c0c0cu;

constexpr std::size_t kDecoyLowerDisplacement = 0x138;   // one word below 0x13c
constexpr std::size_t kDecoyLowererDisplacement = 0x134; // two words below
constexpr std::size_t kDecoyUpperDisplacement = 0x130;   // three below, in range
constexpr std::size_t kDecoyDispatchLow = 0xd0;          // one word below 0xd4
constexpr std::size_t kDecoyDispatchHigh = 0xd8;         // one word above

// ---------------------------------------------------------------------------
// Fixture.
// ---------------------------------------------------------------------------

// What the fixture's slot hooks saw, recorded from inside the hook. This is how
// "the argument is the ADDRESS of the embedded object, not the word stored
// there, and not the outer receiver" is checked: the callee compares what it was
// given against both candidates itself.
struct DispatchTrace {
  const DispatchedObject* receiver = nullptr;
  SlotWord result = 0;
  std::uint8_t tag = 0;
};

// What the modelled 0x00ba9370 saw, copied out of the header's observation
// channel - which exists so the argument routing is a fact the code reports and
// not a claim the test is told.
//
// THE COPY READS THE CHANNEL THROUGH A `volatile` QUALIFIED LVALUE, and that is
// load-bearing rather than incidental. The only thing standing between the
// entry's return and this read is the calling assembly block's `memory` clobber,
// and that clobber does not order a plain global read against the clobber: at
// -O1 and above, both compilers folded this read back across the boundary, and
// a routing assertion failed on an input whose routing was demonstrably
// correct - the value it saw belonged to the PREVIOUS call. A volatile access
// cannot be hoisted across a `memory` clobber or deleted, so the observation is
// genuinely the one the callee left.
//
// The alternative - copying inside the assembly block - was tried first and is
// worse: the compiler is free to allocate an ordinary `"r"` input to EAX, which
// the call has just overwritten, and the block then reads through the callee's
// return value. That is a silently wrong measurement, and a volatile read has no
// such failure mode.
struct LookupTrace {
  const EmpireIndex* receiver;
  std::uint32_t argument;
  std::uint32_t call_count;
};
static_assert(sizeof(LookupTrace) == 12u, "the copied trace is three dwords");

DispatchTrace g_dispatch_trace;

LookupTrace g_lookup_trace;

void capture_lookup_trace() {
  const volatile LookupObservation& seen = g_lookup_observation;
  g_lookup_trace.receiver = seen.receiver;
  g_lookup_trace.argument = seen.argument;
  g_lookup_trace.call_count = seen.call_count;
}

// What the fixture's slot hooks RETURN. Planted by the test so that the word the
// entry pushes at 0x00c71e58 is something the test chooses, and so that a model
// which pushed a constant instead is caught by value.
SlotWord g_slot_result = 0;

// A tag that no assertion on any path accepts. Every case asserts the log
// carries none of them, so an overrun is reported by NAME.
constexpr std::uint8_t kTagNone = 0x00;

std::vector<std::uint8_t>& log_store() {
  static std::vector<std::uint8_t> store;
  return store;
}

void reset_log() { log_store().clear(); }

void log_tag(std::uint8_t tag) { log_store().push_back(tag); }

bool log_contains(std::uint8_t tag) {
  for (const std::uint8_t entry : log_store()) {
    if (entry == tag) {
      return true;
    }
  }
  return false;
}

// The trap table's tag. NO path of this body may produce it: reaching it means
// the dispatch went through a +0xd4 displacement that is not the one in the
// listing. It is a named failure rather than a crash.
void AssertNoTrapTable() {
  check(!log_contains(kTagTrapTable));
  check(!log_contains(kTagNone));
}

// Everything except the target slot's own tag. Asserted wherever the body is
// supposed to have reached table+0x4c, so a slot index off by one in either
// direction is caught BY NAME: the log then carries that neighbour's tag instead
// and this fails.
void AssertNoDecoySlot() {
  check(!log_contains(kTagDecoy40));
  check(!log_contains(kTagDecoy44));
  check(!log_contains(kTagDecoy48));
  check(!log_contains(kTagDecoy50));
  check(!log_contains(kTagDecoy54));
  check(!log_contains(kTagDecoy58));
  check(!log_contains(kTagDecoy5c));
}

// The whole log is exactly one entry, and it is `tag`. Nothing else is claimed
// here, so this is the form the assertions use when `tag` IS an overrun or a
// decoy - which is what the negative cases are for.
void AssertLogExactly(std::uint8_t tag) {
  check(log_store().size() == 1u);
  check(log_store()[0] == tag);
}

// The dispatch reached table+0x4c and nothing else.
void AssertReachedTargetSlot() {
  AssertLogExactly(kTagTargetSlot);
  AssertNoTrapTable();
  AssertNoDecoySlot();
  check(!log_contains(kTagSentinel));
}

// The dispatch reached a NEIGHBOURING slot, not the one the listing names. The
// neighbour's tag is in the log and the target slot's is not, which is what
// makes "one slot too low" and "one slot too high" separate failures instead of
// one.
void AssertReachedDecoySlot(std::uint8_t tag) {
  AssertLogExactly(tag);
  AssertNoTrapTable();
  check(!log_contains(kTagTargetSlot));
  check(!log_contains(kTagSentinel));
}

// The dispatch read PAST the last modelled slot and landed on the sentinel.
void AssertReachedSentinel() {
  AssertLogExactly(kTagSentinel);
  AssertNoTrapTable();
  AssertNoDecoySlot();
  check(!log_contains(kTagTargetSlot));
}

// ---------------------------------------------------------------------------
// The fixture objects.
//
// Four separate objects, because they are four separate objects in the machine:
// the receiver (0x00c71e30's), the object at receiver+0x13c (0x00b8dab0's), the
// embedded object at receiver+0xd4 (the dispatch callee's), and the token 0x00b3d2a0
// returns (0x00ba9370's). A reconstruction that crossed two of them over could
// not be expressed by this fixture's types.
// ---------------------------------------------------------------------------

struct Fixture {
  OpaqueReceiver receiver;
  DelegatedReceiver delegated;
  DelegatedReceiver decoy_delegated;
  DispatchTable live_table;
  DispatchTable decoy_table;  // every slot traps
  // The embedded object at receiver+0xd4. It is not stored in the fixture as a
  // separate field: in the machine it lives AT receiver+0xd4, and its first word
  // is the table pointer the load reads. `f.dispatched` is a spare copy of that
  // one word, kept so the test can compare the two views of the same address.
  DispatchedObject dispatched;
  EmpireIndex index;
  // A SECOND token, so "the last call's receiver is whatever 0x00b3d2a0
  // returned" can be checked as a change of pointer IDENTITY rather than as a
  // coincidence of numbers. Both are real, aligned objects of the right type:
  // forming a pointer out of a bare constant and handing it to a function of a
  // type with an alignment requirement is undefined behaviour, and at -O2 it is
  // undefined behaviour the optimizer is entitled to act on. The value 0x00b3d2a0
  // really returns is an address read out of a data segment, so the honest way
  // to stand in for it is with an ADDRESS, not with a number.
  EmpireIndex other_index;
};

// The trap table: every word in it points at one callable that records the trap
// tag and returns a value that differs from every legal result. So a wrong
// +0xd4 displacement does not fault and does not alias a live table - it lands
// somewhere that says so.
SlotWord PKG_00C71E30_THISCALL trap_hook(DispatchedObject* self) {
  (void)self;
  log_tag(kTagTrapTable);
  g_dispatch_trace.receiver = self;
  g_dispatch_trace.tag = kTagTrapTable;
  g_dispatch_trace.result = kDecoySlotResult;
  return kDecoySlotResult;
}

void plant_trap_table(DispatchTable& table) {
  table = DispatchTable();
  table.decoy_40 = &trap_hook;
  table.decoy_44 = &trap_hook;
  table.decoy_48 = &trap_hook;
  table.slot_4c = &trap_hook;
  table.decoy_50 = &trap_hook;
  table.decoy_54 = &trap_hook;
  table.decoy_58 = &trap_hook;
  table.decoy_5c = &trap_hook;
  table.sentinel = &trap_hook;
}

// Each modelled slot, told apart by the tag it records. They are ordinary
// thiscall-shaped functions of the dispatched receiver, so an off-by-one in the
// slot arithmetic calls a REAL function that reports itself.
#define PKG_DEFINE_DECOY(NAME, TAG)                                     \
  SlotWord PKG_00C71E30_THISCALL NAME(DispatchedObject* self) {         \
    (void)self;                                                         \
    log_tag(TAG);                                                       \
    g_dispatch_trace.receiver = self;                                   \
    g_dispatch_trace.tag = TAG;                                         \
    g_dispatch_trace.result = kDecoySlotResult;                         \
    return kDecoySlotResult;                                            \
  }

PKG_DEFINE_DECOY(decoy40_hook, kTagDecoy40)
PKG_DEFINE_DECOY(decoy44_hook, kTagDecoy44)
PKG_DEFINE_DECOY(decoy48_hook, kTagDecoy48)
PKG_DEFINE_DECOY(decoy50_hook, kTagDecoy50)
PKG_DEFINE_DECOY(decoy54_hook, kTagDecoy54)
PKG_DEFINE_DECOY(decoy58_hook, kTagDecoy58)
PKG_DEFINE_DECOY(decoy5c_hook, kTagDecoy5c)

#undef PKG_DEFINE_DECOY

// The slot the body actually reads. It records the receiver it was handed and
// returns a planted word - which is how the load/address distinction is judged
// from the callee's side, and how the word the entry pushes is made something
// the test chooses.
SlotWord PKG_00C71E30_THISCALL target_slot_hook(DispatchedObject* self) {
  log_tag(kTagTargetSlot);
  g_dispatch_trace.receiver = self;
  g_dispatch_trace.tag = kTagTargetSlot;
  g_dispatch_trace.result = g_slot_result;
  return g_slot_result;
}

// Reached only by a dispatch that reads a slot PAST +0x5c. It records itself and
// returns a value that differs from every legal one, so the assertion that fails
// is about the LOG and says what was wrong instead of merely faulting.
SlotWord PKG_00C71E30_THISCALL sentinel_hook(DispatchedObject* self) {
  (void)self;
  log_tag(kTagSentinel);
  g_dispatch_trace.tag = kTagSentinel;
  g_dispatch_trace.result = kDecoySlotResult;
  return kDecoySlotResult;
}

// Fill the whole extent with a distinctive non-zero ramp, so a read of ANY part
// of the receiver shows in the value and a write to any part shows in the bytes.
void ramp_receiver(OpaqueReceiver& receiver) {
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index * 7u + 3u);
  }
}

void ramp_delegated(DelegatedReceiver& receiver) {
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index * 11u + 5u);
  }
}

void store_receiver(Fixture& f, std::size_t displacement, SlotWord value) {
  std::memcpy(f.receiver.opaque_bytes.data() + displacement, &value,
              sizeof(value));
}

void store_delegated(DelegatedReceiver& object, std::size_t displacement,
                     SlotWord value) {
  std::memcpy(object.opaque_bytes.data() + displacement, &value,
              sizeof(value));
}

// Build the whole fixture for the PASSING path: both guards satisfied.
void init_passing(Fixture& f) {
  f = Fixture();
  ramp_receiver(f.receiver);
  ramp_delegated(f.delegated);
  ramp_delegated(f.decoy_delegated);

  // Sentinels through the receiver, including the word before it and the last
  // word of the modelled extent. Each differs from the others, so "one word too
  // low" and "one word too high" are separate failures rather than one.
  store_receiver(f, 0x000, kReceiverHeadSentinel);
  store_receiver(f, 0x004, kNearHeadSentinel);
  store_receiver(f, sizeof(OpaqueReceiver) - sizeof(SlotWord), kTailSentinel);

  // The REAL delegated object, reachable at exactly +0x13c, reporting 5.
  store_delegated(f.delegated, kDelegatedTargetDisplacement,
                  kDelegatedReportedScalar);
  store_receiver(f, kDelegatedDisplacement, pointer_word(&f.delegated));

  // The decoy: a perfectly good non-null pointer whose object reports something
  // that is NOT 5. Planted one word below, two words below and three words below
  // 0x13c, so a slip in EITHER direction lands on a real pointer to a populated
  // object - and the second guard then turns it into a published zero. That is
  // a catch BY VALUE: nothing here faults, and nothing here can be mistaken for
  // the passing path.
  store_delegated(f.decoy_delegated, kDelegatedTargetDisplacement,
                  kDecoyReportedScalar);
  store_receiver(f, kDecoyLowererDisplacement, pointer_word(&f.decoy_delegated));
  store_receiver(f, kDecoyLowerDisplacement, pointer_word(&f.decoy_delegated));
  store_receiver(f, kDecoyUpperDisplacement, pointer_word(&f.decoy_delegated));

  // The dispatch. Only +0xd4 names the live table; the words either side name
  // the trap table, so a one-word slip lands on a callable that reports itself.
  plant_trap_table(f.decoy_table);
  f.live_table = DispatchTable();
  f.live_table.decoy_40 = &decoy40_hook;
  f.live_table.decoy_44 = &decoy44_hook;
  f.live_table.decoy_48 = &decoy48_hook;
  f.live_table.slot_4c = &target_slot_hook;
  f.live_table.decoy_50 = &decoy50_hook;
  f.live_table.decoy_54 = &decoy54_hook;
  f.live_table.decoy_58 = &decoy58_hook;
  f.live_table.decoy_5c = &decoy5c_hook;
  f.live_table.sentinel = &sentinel_hook;

  // The embedded object lives AT receiver+0xd4, and its first word is the table
  // pointer, so the receiver's word at +0xd4 names the LIVE table. The words one
  // step either side name the TRAP table, so a one-word slip in either
  // direction lands on a callable that reports itself instead of faulting.
  f.dispatched.table = &f.live_table;
  store_receiver(f, kDispatchedDisplacement, pointer_word(&f.live_table));
  store_receiver(f, kDecoyDispatchLow, pointer_word(&f.decoy_table));
  store_receiver(f, kDecoyDispatchHigh, pointer_word(&f.decoy_table));

  f.index.opaque_word = kGlobalSlotValue;
  f.other_index.opaque_word = kOtherIndexValue;
  g_global_slot_value = pointer_word(&f.index);
  g_lookup_result = kLookupResult;
  g_slot_result = kDecoySlotResult;
  g_lookup_observation = LookupObservation();
  g_lookup_trace = LookupTrace();
  capture_lookup_trace();

  reset_log();
  g_dispatch_trace = DispatchTrace();
}

// Build the fixture for the NULL arm: the word at +0x13c is zero.
void init_null_arm(Fixture& f) {
  init_passing(f);
  store_receiver(f, kDelegatedDisplacement, 0u);
}

Fixture g_fixture;

// The entry, called with the receiver in ECX and nothing pushed. `target` is
// loaded through a variable so the compiler cannot inline the body and destroy
// the very thing being measured.
SlotWord entry_address() {
  return pointer_word(
      reinterpret_cast<const void*>(&empire5_00c71e30));
}

SlotWord call_entry(OpaqueReceiver* receiver) {
  const SlotWord target = entry_address();
  SlotWord result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  capture_lookup_trace();
  return result;
}

// ESP sampled before the call and the instant the entry has returned. `call`
// pushes a return address and `RET` pops it, so the two agree only when the
// entry owned no cleanup - and 0x00c71e66 and 0x00c71e6a are both the bare
// 0xc3, so zero bytes of callee cleanup is what the recording expects. An entry
// that grew a stack argument or a `RET imm16` fails this measurement rather than
// merely being named wrong.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver) {
  const SlotWord target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  capture_lookup_trace();
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// ---------------------------------------------------------------------------
// 1. Both guards are real, both converge on one null arm, and the compared
//    constant is exactly 5.
// ---------------------------------------------------------------------------

void test_both_guards_and_the_constant_five() {
  Fixture& f = g_fixture;

  // The passing path reaches the dispatch and the lookup.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();
  check(g_lookup_trace.call_count == 1u);

  // The last call's receiver is whatever 0x00b3d2a0 returned, overwound into
  // ECX at 0x00c71e5e. `init_passing` makes that a real pointer to the index
  // token, so "the last callee's receiver is the global slot's result" is a
  // statement about pointer IDENTITY and not about a number that matches.
  check(g_lookup_trace.receiver == &f.index);
  check(g_lookup_trace.receiver !=
        reinterpret_cast<const EmpireIndex*>(&f.receiver));
  check(g_lookup_trace.receiver !=
        reinterpret_cast<const EmpireIndex*>(&f.other_index));
  check(g_lookup_trace.receiver->opaque_word == kGlobalSlotValue);

  // Guard one: the word at +0x13c is zero -> published zero, no dispatch, and
  // the lookup is never reached.
  init_null_arm(f);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  check(g_lookup_trace.call_count == 0u);

  // Guard two: the delegated object reports 4, one below the constant.
  init_passing(f);
  store_delegated(f.delegated, kDelegatedTargetDisplacement, 0x4u);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  check(g_lookup_trace.call_count == 0u);

  // ... and 6, one above. The comparison is against exactly 5, in both
  // directions.
  init_passing(f);
  store_delegated(f.delegated, kDelegatedTargetDisplacement, 0x6u);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  check(g_lookup_trace.call_count == 0u);

  // The boundary values either side of 5.
  init_passing(f);
  store_delegated(f.delegated, kDelegatedTargetDisplacement, 0x0u);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  init_passing(f);
  store_delegated(f.delegated, kDelegatedTargetDisplacement, 0xffffffffu);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());

  // And 5 itself is the one value that passes, which pins the comparison as an
  // equality against 5 rather than an ordering against it.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  // Both branches land on the SAME address, so the null arm is one arm reached
  // two ways rather than two arms. A model that gave each guard its own zeroing
  // instruction would be modelling a body with three returns.
  check(kComputedNullArm == kComputedNullArmSecond);
  check(kComputedNullArm == kNullArmAddress);

  // The receiver itself is never tested: a null receiver faults exactly as the
  // machine does, so this package adds no check and the test adds none either.
  check(kAbiReceiverDisplacementCount == 2u);
  check(kAbiSavedRegisterCount == 1u);
}

// ---------------------------------------------------------------------------
// 2. 0x13c is the word this body reads, and it is a BYTE displacement.
// ---------------------------------------------------------------------------

void test_delegated_displacement_is_bytes_and_is_13c() {
  Fixture& f = g_fixture;

  // The planted decoy one word BELOW 0x13c is a perfectly good non-null pointer
  // whose object reports something other than 5. A one-word slip down therefore
  // produces a published zero - caught by VALUE, not by an out-of-bounds fault.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  // Prove the decoy is in fact a non-null pointer to a populated object, so the
  // case above is a real alternative and not a coincidence.
  check(*reinterpret_cast<const std::uint32_t*>(
            f.receiver.opaque_bytes.data() + kDecoyLowerDisplacement) != 0u);
  check(*reinterpret_cast<const std::uint32_t*>(
            f.decoy_delegated.opaque_bytes.data() +
            kDelegatedTargetDisplacement) == kDecoyReportedScalar);
  check(kDecoyReportedScalar != kDelegatedReportedScalar);

  // The word is not the receiver's own base and not the displacement.
  init_passing(f);
  check(call_entry(&f.receiver) != pointer_word(&f.receiver));
  check(call_entry(&f.receiver) != kDelegatedDisplacement);
  check(call_entry(&f.receiver) != 0x13cu);

  // Neighbours either side carry different sentinels and none of them is what
  // the entry returns.
  init_passing(f);
  check(call_entry(&f.receiver) != kNearHeadSentinel);
  check(call_entry(&f.receiver) != kReceiverHeadSentinel);
  check(call_entry(&f.receiver) != kTailSentinel);

  // The displacement is a BYTE offset. Read as a word count it would address
  // byte 0x4f0, which is past the modelled receiver entirely, so no such model
  // could have compiled against this fixture.
  static_assert(kDelegatedDisplacement * sizeof(SlotWord) >
                    sizeof(OpaqueReceiver),
                "0x13c read as an element count would be past the receiver");
  static_assert(kDelegatedIndexInWords == 79u,
                "0x13c is 79 four-byte words past the base");
  check(kDelegatedDisplacement == 0x13cu);
  check(kDelegatedDisplacement == 316u);

  // The header accessor and the entry's own literal are one address.
  init_passing(f);
  check(delegated_word_at(&f.receiver) ==
        pointer_word(&f.delegated));
  const std::uint32_t* literal = reinterpret_cast<const std::uint32_t*>(
      reinterpret_cast<std::uintptr_t>(&f.receiver) + 0x13c);
  check(*literal == delegated_word_at(&f.receiver));
  check(*literal == pointer_word(&f.delegated));
}

// ---------------------------------------------------------------------------
// 3. The delegation hands the word at +0x13c over as a RECEIVER, and the
//    compared value belongs to the DELEGATED object at +0x194.
// ---------------------------------------------------------------------------

void test_delegation_is_a_receiver_handover() {
  Fixture& f = g_fixture;

  // The passing path's value came out of the DELEGATED object, so the word the
  // DELEGATED object reports is what decides guard two. Change only that word
  // and the outcome flips; nothing else in the fixture moves.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  init_passing(f);
  store_delegated(f.decoy_delegated, kDelegatedTargetDisplacement, 0x5u);
  store_receiver(f, kDecoyLowerDisplacement, pointer_word(&f.decoy_delegated));
  store_receiver(f, kDelegatedDisplacement, pointer_word(&f.decoy_delegated));
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  init_passing(f);
  store_receiver(f, kDelegatedDisplacement, pointer_word(&f.decoy_delegated));
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  check(g_lookup_trace.call_count == 0u);

  // The two objects are not one: 0x194 is past this body's own receiver's
  // extent, so the delegated object is strictly the larger and the word that
  // decides guard two cannot be a word of the receiver.
  static_assert(kDelegatedTargetDisplacement > sizeof(OpaqueReceiver),
                "the delegated object reaches past the receiver's extent");
  static_assert(sizeof(DelegatedReceiver) == 0x198,
                "the delegated extent runs through the word 0x00b8dab0 reads");
  static_assert(sizeof(OpaqueReceiver) == 0x140, "the receiver ends at +0x140");
  check(kDelegatedTargetDisplacement == 0x194u);
  check(kDelegatedTargetDisplacement != kDelegatedDisplacement);

  // The chain of ECX, from the bytes: 0x00c71e33 writes ECX with a LOAD whose
  // base is ESI and not ECX, so the incoming receiver is CONSUMED and the loaded
  // word is what a thiscall callee receives. Base and destination differing is
  // the whole mechanism.
  static_assert(((kTargetEncoding[4] >> 3) & 7u) == 1u,
                "0x00c71e33's destination register is ECX");
  static_assert((kTargetEncoding[4] & 7u) == 6u,
                "0x00c71e33's base register is ESI, not ECX");
  static_assert(((kTargetEncoding[4] >> 3) & 7u) != (kTargetEncoding[4] & 7u),
                "destination and base DIFFER, so the load is not in place");
  static_assert((kTargetEncoding[4] >> 6) == 2u,
                "mod=10, so the operand really is a displacement");
  static_assert(kTargetEncoding[3] == 139u,
                "0x00c71e33 is MOV r32,r/m32 - a LOAD, not a LEA");

  // The delegation target's own bytes: it reads through ECX at +0x194 and ends
  // in a bare RET that names no register but EAX - so ESI survives the call and
  // the receiver can still be read at 0x00c71e47.
  static_assert(kDelegateTargetEncoding[6] == 195u,
                "0x00b8dab6 is a bare RET");
  static_assert((kDelegateTargetEncoding[1] & 7u) == 1u,
                "0x00b8dab0's base register is ECX");
  check(kDelegateTargetVa == 0x00b8dab0u);
  check(kRecordedOutgoingDirectCallEdges == 3u);
}

// ---------------------------------------------------------------------------
// 4. The table word is LOADED and the dispatch's receiver is its ADDRESS.
// ---------------------------------------------------------------------------

void test_dispatch_receiver_is_the_address_not_the_word() {
  Fixture& f = g_fixture;

  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  // The callee recorded what it was handed. It must be the ADDRESS of the
  // embedded object at receiver+0xd4 - NOT the table pointer stored there, and
  // NOT this body's own receiver. All three are distinct addresses.
  const DispatchedObject* expected = dispatched_address_at(&f.receiver);
  check(g_dispatch_trace.receiver == expected);
  check(g_dispatch_trace.receiver !=
        reinterpret_cast<const DispatchedObject*>(
            embedded_object_pointer_at(&f.receiver)));
  check(g_dispatch_trace.receiver !=
        reinterpret_cast<const DispatchedObject*>(&f.receiver));
  check(g_dispatch_trace.receiver !=
        reinterpret_cast<const DispatchedObject*>(&f.live_table));

  // The entry's own two reads of the SAME address agree with the header's two
  // accessors, and they disagree with each other exactly as the body does: one
  // is the stored word, the other is the address, and they are two different
  // pointers.
  init_passing(f);
  // The STORED word at +0xd4 is the table pointer, and the table it names is
  // the one whose slot 0x4c is the target.
  check(embedded_object_pointer_at(&f.receiver) ==
        reinterpret_cast<const void*>(&f.live_table));
  check(slot_target_at(embedded_object_pointer_at(&f.receiver), 0x4c) ==
        &target_slot_hook);
  // The ADDRESS of that same place is a different pointer from the word stored
  // there, and the callee was handed the address.
  check(dispatched_address_at(&f.receiver) == expected);
  check(dispatched_address_at(&f.receiver) !=
        reinterpret_cast<DispatchedObject*>(&f.live_table));
  check(pointer_word(dispatched_address_at(&f.receiver)) !=
        pointer_word(embedded_object_pointer_at(&f.receiver)));
  check(pointer_word(dispatched_address_at(&f.receiver)) !=
        pointer_word(&f.receiver));
  // And the object at that address really does begin with the table pointer the
  // load reads, which is what makes the address and the load two views of ONE
  // object rather than two objects with a pointer between them.
  check(expected->table == reinterpret_cast<const void*>(&f.live_table));

  // The load/address distinction, in the bytes: one displacement, two opcodes.
  static_assert(kTargetEncoding[23] == 139u, "0x00c71e47 is MOV r32,r/m32");
  static_assert(kTargetEncoding[32] == 141u, "0x00c71e50 is LEA");
  static_assert(kTargetEncoding[23] != kTargetEncoding[32],
                "the same displacement is loaded at 0x00c71e47 and addressed "
                "at 0x00c71e50, so the two questions are distinguished");
  static_assert((kTargetEncoding[4] >> 6) == 2u && kTargetEncoding[5] == 60u,
                "0x00c71e33 is a MOV with a disp32 of 0x13c");

  // A wrong +0xd4 displacement lands on the TRAP table, which is a callable and
  // says so - not on a fault, and not on the live table by accident.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  check(!log_contains(kTagTrapTable));
  // The trap table really is named by the words either side of +0xd4, so the
  // wrong-displacement case is a real alternative and not a coincidence.
  check(f.dispatched.table == &f.live_table);
  check(*reinterpret_cast<const void* const*>(
            f.receiver.opaque_bytes.data() + kDecoyDispatchLow) ==
        reinterpret_cast<const void*>(&f.decoy_table));
  check(*reinterpret_cast<const void* const*>(
            f.receiver.opaque_bytes.data() + kDecoyDispatchHigh) ==
        reinterpret_cast<const void*>(&f.decoy_table));
  check(slot_target_at(&f.decoy_table, kSlotDisplacement) == &trap_hook);
  check(slot_target_at(&f.live_table, kSlotDisplacement) ==
        &target_slot_hook);
  // Reaching the trap table is named, not merely fatal: every word of it is a
  // callable that records kTagTrapTable and returns a value no legal path
  // returns.
  reset_log();
  check(slot_target_at(&f.decoy_table, kSlotDisplacement)(&f.dispatched) ==
        kDecoySlotResult);
  check(log_contains(kTagTrapTable));
  check(!log_contains(kTagTargetSlot));
  reset_log();

  // The dispatch's own displacements differ, so no swap is equivalent.
  check(kDispatchedDisplacement == 0xd4u);
  check(kDelegatedDisplacement == 0x13cu);
  check(kDispatchedDisplacement != kDelegatedDisplacement);
  check(kDispatchedDisplacement != kSlotDisplacement);
}

// ---------------------------------------------------------------------------
// 5. The slot is the word at table+0x4c, and a wrong index is OBSERVABLE.
// ---------------------------------------------------------------------------

void test_slot_displacement_is_4c_and_wrong_indices_are_observable() {
  Fixture& f = g_fixture;

  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  AssertReachedTargetSlot();

  // Every neighbouring offset is a callable slot of its own, reached through the
  // ONE accessor the entry uses. Reading one of them instead of 0x4c calls a
  // different function that records a different tag.
  const std::size_t neighbours[] = {0x40u, 0x44u, 0x48u, 0x50u,
                                    0x54u, 0x58u, 0x5cu, 0x60u};
  for (const std::size_t offset : neighbours) {
    reset_log();
    g_dispatch_trace = DispatchTrace();
    const SlotFunction reached =
        slot_target_at(reinterpret_cast<const void*>(&f.live_table), offset);
    const SlotWord value = reached(&f.dispatched);
    check(value == kDecoySlotResult);
    check(log_store().size() == 1u);
    check(log_store()[0] != kTagTargetSlot);
    check(log_store()[0] != kTagNone);
    if (offset == 0x60u) {
      AssertReachedSentinel();
    } else {
      AssertReachedDecoySlot(static_cast<std::uint8_t>(offset));
    }
  }

  // And the tag of each is the offset it lives at, so "one too low" and "one too
  // high" are separate named failures.
  reset_log();
  slot_target_at(reinterpret_cast<const void*>(&f.live_table), 0x48u)(
      &f.dispatched);
  AssertReachedDecoySlot(kTagDecoy48);
  reset_log();
  slot_target_at(reinterpret_cast<const void*>(&f.live_table), 0x50u)(
      &f.dispatched);
  AssertReachedDecoySlot(kTagDecoy50);
  reset_log();
  slot_target_at(reinterpret_cast<const void*>(&f.live_table), 0x60u)(
      &f.dispatched);
  AssertReachedSentinel();

  // The sentinel sits immediately past the LAST modelled slot and not anywhere
  // else, which is what makes an overrun a trap rather than somebody else's
  // memory.
  static_assert(offsetof(DispatchTable, decoy_5c) + sizeof(SlotFunction) ==
                    offsetof(DispatchTable, sentinel),
                "the sentinel immediately follows the last modelled slot");
  static_assert(offsetof(DispatchTable, sentinel) == 0x60u,
                "the sentinel is at table+0x60");
  check(offsetof(DispatchTable, slot_4c) == kSlotDisplacement);
  check(kSlotDisplacement == 0x4cu);
  check(kSlotIndex == 19u);
  check((kSlotDisplacement % sizeof(SlotFunction)) == 0u);

  // The slot is NOT slot zero, so a base-relative mix-up is a real possibility
  // and the fixture above is what rules it out.
  check(kSlotIndex != 0u);
  check(kSlotIndex >= 1u);

  // The three bytes at 0x00c71e4d really are a disp8, so 0x4c is a byte and not
  // the low half of a disp32 - which is what a mis-modelled operand class would
  // read.
  static_assert((kTargetEncoding[30] >> 6) == 1u,
                "ModRM 0x50 is mod=01: a disp8 follows");
  static_assert(kTargetEncoding[31] == 76u, "the disp8 byte is 0x4c");
  static_assert((kTargetEncoding[29] >> 6) == 2u,
                "0x00c71e47 is mod=10 with a disp32, and 0x00c71e4d is mod=01 "
                "with a disp8: the two operand classes differ");

  // The transfer itself is register-indirect with no displacement operand, so
  // 0x4c cannot be seen a second time and the slot index is consumed once.
  static_assert(kTargetEncoding[38] == 255u && kTargetEncoding[39] == 210u,
                "0x00c71e56 is ff d2, CALL EDX");
  static_assert((kTargetEncoding[39] >> 6) == 3u,
                "mod=11: a register target, no memory operand");

  // The record's own counts, pinned with the disagreement between them.
  static_assert(kMachineIndirectCallCount == 1u,
                "the record counts one indirect call");
  static_assert(kMachineVtableShapedLoadCount == 0u,
                "and zero vtable-shaped loads beside it - recorded, not "
                "reconciled");
}

// ---------------------------------------------------------------------------
// 6. The pushed word reaches the LAST callee and is popped there; POP ESI
//    restores the CALLER's ESI. Measured, not asserted.
// ---------------------------------------------------------------------------

void test_stack_is_measured_and_the_pushed_word_reaches_the_last_callee() {
  Fixture& f = g_fixture;

  // The entry's own stack effect is zero: ESP is where the caller left it.
  init_passing(f);
  EspSamples passing = call_entry_measured(&f.receiver);
  check(passing.after_return == passing.before_call);

  init_null_arm(f);
  EspSamples null_arm = call_entry_measured(&f.receiver);
  check(null_arm.after_return == null_arm.before_call);

  // The word 0x00c71e58 pushed is the LAST call's argument, not the previous
  // call's. The entry pushes the dispatch's result; 0x00b3d2a0 takes no argument
  // and pops nothing, so the value that survives to 0x00ba9370 is the dispatch's,
  // and the receiver 0x00ba9370 is given is 0x00b3d2a0's RESULT - a different
  // value, overwound into ECX at 0x00c71e5e.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  check(g_lookup_trace.argument == kDecoySlotResult);
  check(g_lookup_trace.argument != kGlobalSlotValue);
  check(g_lookup_trace.receiver == &f.index);
  check(g_lookup_trace.receiver->opaque_word == kGlobalSlotValue);
  check(g_lookup_trace.receiver !=
        reinterpret_cast<const EmpireIndex*>(&f.receiver));

  // Change ONLY what the dispatch returns and the last call's argument follows
  // it: so the pushed word really is the dispatch's, and not a constant.
  init_passing(f);
  g_slot_result = 0x0badcafeu;
  check(call_entry(&f.receiver) == kLookupResult);
  check(g_lookup_trace.argument == 0x0badcafeu);
  check(g_lookup_trace.argument != kGlobalSlotValue);

  // Change ONLY what 0x00b3d2a0 returns and the last call's RECEIVER follows
  // it: so the last receiver is the global slot's result and not this body's
  // receiver.
  init_passing(f);
  g_global_slot_value = pointer_word(&f.other_index);
  check(call_entry(&f.receiver) == kLookupResult);
  check(g_lookup_trace.receiver == &f.other_index);
  check(g_lookup_trace.receiver != &f.index);
  check(g_lookup_trace.receiver->opaque_word == kOtherIndexValue);
  check(g_lookup_trace.receiver !=
        reinterpret_cast<const EmpireIndex*>(&f.receiver));

  // And this body's own receiver never reaches the last call at all.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  check(g_lookup_trace.receiver !=
        reinterpret_cast<const EmpireIndex*>(&f.receiver));
  check(g_lookup_trace.argument != pointer_word(&f.receiver));
  check(g_lookup_trace.argument != pointer_word(&f.index));

  // The two cleanup facts are DIFFERENT, and both are pinned. The last callee's
  // two exits are `RET 0x4`, so the callee pops the pushed word; this body's two
  // exits are the bare 0xc3, so it pops nothing and `POP ESI` restores the
  // caller's ESI.
  static_assert(kLookupCleanupBytes == 4u, "0x00ba9370 pops one stack word");
  static_assert(kEntryCleanupBytes == 0u, "0x00c71e30 pops nothing");
  static_assert(kLookupCleanupBytes != kEntryCleanupBytes,
                "so 'the callee pops the pushed word' and 'POP ESI pops it' "
                "cannot both describe this body");

  // The bytes that make the callee's cleanup real: 0x00b3d2a0's is the bare
  // 0xc3 and its operand is an ABSOLUTE address with no base register, so it
  // takes no receiver and consumes nothing.
  static_assert(sizeof(kGlobalSlotTargetEncoding) == 6u,
                "0x00b3d2a0 is six bytes: five of MOV EAX,moffs32 and one RET");
  static_assert(kGlobalSlotTargetEncoding[0] == 161u,
                "the opcode is 0xa1, MOV EAX,moffs32");
  static_assert(kGlobalSlotTargetEncoding[5] == 195u,
                "0x00b3d2a5 is a bare RET");
  static_assert(kGlobalSlotTargetEncoding[5] != 194u,
                "0xc2 would carry an imm16 and would pop the pushed word here");

  // 0x00c71e5e overwrites ECX with EAX, so nothing has to survive the call that
  // precedes the last one.
  static_assert(((kTargetEncoding[47] >> 3) & 7u) == 1u,
                "0x00c71e5e's destination is ECX");
  static_assert((kTargetEncoding[47] & 7u) == 0u, "and its source is EAX");

  // The entry pops ESI on BOTH exits and the prologue pushed it once, so the
  // caller's ESI is restored on every path.
  static_assert(kTargetEncoding[53] == 94u, "0x00c71e65 is POP ESI");
  static_assert(kTargetEncoding[57] == 94u, "0x00c71e69 is POP ESI");
  static_assert(kTargetEncoding[0] == 86u, "0x00c71e30 is PUSH ESI");
  static_assert(kTargetEncoding[53] != kTargetEncoding[40],
                "the epilogue's POP and the PUSH of the pushed word are "
                "different bytes doing different work");
}

// ---------------------------------------------------------------------------
// 7. Return semantics: verbatim on the passing arm, a full 32-bit zero on the
//    null arm.
// ---------------------------------------------------------------------------

void test_return_semantics_verbatim_and_zero() {
  Fixture& f = g_fixture;

  // The passing arm returns the LAST call's result and nothing else: no mask,
  // no increment, no clamp.
  const SlotWord crossings[] = {0u,
                                1u,
                                5u,
                                0x7fffffffu,
                                0x80000000u,
                                0xfffffffeu,
                                0xffffffffu,
                                0x00c71e30u};
  for (const SlotWord planted : crossings) {
    init_passing(f);
    g_lookup_result = planted;
    const SlotWord result = call_entry(&f.receiver);
    check(result == planted);
    AssertReachedTargetSlot();
  }

  // A 4x4 sweep of the byte pattern, so no masking of any width survives.
  init_passing(f);
  for (std::uint32_t high = 0; high < 4u; ++high) {
    for (std::uint32_t low = 0; low < 4u; ++low) {
      g_lookup_result = (high << 8) | low;
      check(call_entry(&f.receiver) == g_lookup_result);
    }
  }

  // The null arm returns a FULL 32-bit zero on both routes to it. Not the 8-bit
  // form: `33 c0` writes all of EAX, so the top three bytes are zero too and no
  // byte of the return is undefined.
  init_null_arm(f);
  check(call_entry(&f.receiver) == 0u);
  check(call_entry(&f.receiver) != 0x100u);
  init_passing(f);
  store_delegated(f.delegated, kDelegatedTargetDisplacement, 0x7u);
  check(call_entry(&f.receiver) == 0u);

  // The two arms' values are told apart even when the last call returns zero:
  // the passing arm reached the dispatch and the null arm did not.
  init_passing(f);
  g_lookup_result = 0u;
  check(call_entry(&f.receiver) == 0u);
  AssertReachedTargetSlot();
  init_null_arm(f);
  check(call_entry(&f.receiver) == 0u);
  check(log_store().empty());
  check(g_lookup_trace.call_count == 0u);

  // The width, from the bytes: the null arm's zeroing instruction writes all
  // thirty-two bits, and both exits are bare RETs so the entry pops nothing.
  static_assert(kTargetEncoding[55] == 51u && kTargetEncoding[56] == 192u,
                "0x00c71e67 is 33 c0, XOR EAX,EAX");
  static_assert(kTargetEncoding[56] != 200u,
                "0xc8 would be XOR EAX,ECX, leaving EAX dependent on ECX");
  static_assert(sizeof(SlotWord) == 4u, "the dword is 32-bit");
  static_assert(kTargetEncoding[54] == 195u && kTargetEncoding[58] == 195u,
                "both exits are the bare 0xc3");

  // The record's own words, pinned: the verdict, the candidates, the receiver,
  // and the two-oracle disagreement (header notes 9 and 12).
  static_assert(kAbiVerdict[0] == 'A', "the record's verdict is ABI_INFERRED");
  check(std::strcmp(kAbiVerdict, "ABI_INFERRED") == 0);
  check(std::strcmp(kAbiCompleteness, "CORE_RESOLVED") == 0);
  check(std::strcmp(kAbiConventionNamed, "__thiscall") == 0);
  check(std::strcmp(kAbiConventionCandidateA, "__thiscall") == 0);
  check(std::strcmp(kAbiConventionCandidateB, "__fastcall") == 0);
  check(kAbiCandidateConventionCount == 2u);
  check(kMachineIndirectCallCount == 1u);
  check(kMachineVtableShapedLoadCount == 0u);
  check(kAbiReceiverDisplacementCount == 2u);
  check(kAbiSavedRegisterCount == 1u);

  // The modelled interfaces can express neither a stack argument on the entry
  // nor a by-reference return, so a reconstruction that grew one could not be
  // declared against them.
  static_assert(std::is_same<AbiEmpire5_00c71e30,
                             SlotWord(PKG_00C71E30_THISCALL*)(
                                 OpaqueReceiver*)>::value,
                "the entry carries the ECX receiver and returns one dword");
  static_assert(sizeof(AbiEmpire5_00c71e30) == sizeof(void*),
                "the modelled entry is a plain code pointer");
  static_assert(std::is_same<AbiGlobalSlot00b3d2a0,
                             SlotWord(PKG_00C71E30_THISCALL*)()>::value,
                "0x00b3d2a0 takes no receiver and no argument");
  static_assert(std::is_same<AbiLookup00ba9370,
                             SlotWord(PKG_00C71E30_THISCALL*)(EmpireIndex*,
                                                              std::uint32_t)>::value,
                "0x00ba9370 takes a receiver AND one stack argument");
  check(entry_address() != 0u);
}

// ---------------------------------------------------------------------------
// 8. The encoding IS the observed fifty-nine bytes, and the reach is bounded.
// ---------------------------------------------------------------------------

void test_encoding_and_body_bounds() {
  Fixture& f = g_fixture;

  check(kTargetBodyBytes == 59u);
  check(kEntryAddress == 0x00c71e30u);
  check(kNullArmAddress == 0x00c71e67u);
  check(kNextEntryAddress == 0x00c71e70u);
  check(kTargetPadByte == 0xccu);
  check(kTargetPadBytes == 5u);
  check(sizeof(kTargetEncoding) == 59u);

  // The two-level load, spelled as the tool that adjudicates this dimension
  // reads it: a word loaded out of the receiver, a word loaded out of what that
  // word addresses, and a call through the second.
  static_assert(kTargetEncoding[23] == 139u && kTargetEncoding[24] == 134u,
                "0x00c71e47 is MOV EAX,[ESI+0xd4]");
  static_assert(kTargetEncoding[29] == 139u && kTargetEncoding[30] == 80u,
                "0x00c71e4d is MOV EDX,[EAX+0x4c]");
  static_assert(kTargetEncoding[38] == 255u && kTargetEncoding[39] == 210u,
                "0x00c71e56 is CALL EDX");
  static_assert(((kTargetEncoding[30] >> 3) & 7u) == 2u,
                "the slot goes into EDX, which is the transfer's register");
  static_assert((kTargetEncoding[39] & 7u) == 2u,
                "and the transfer reads EDX");

  // The body's reach is bounded: the two displacements it reaches end inside the
  // modelled receiver, and the slot sits inside the modelled table and never on
  // the sentinel.
  check(kDelegatedDisplacement + sizeof(SlotWord) == sizeof(OpaqueReceiver));
  check(kDispatchedDisplacement + sizeof(void*) < sizeof(OpaqueReceiver));
  check(kSlotDisplacement < offsetof(DispatchTable, sentinel));
  check(sizeof(DispatchTable) == 0x64u);
  check(sizeof(DispatchedObject) == sizeof(void*));
  check(offsetof(DispatchedObject, table) == 0u);
  check(offsetof(OpaqueReceiver, opaque_bytes) == 0u);
  check(offsetof(DelegatedReceiver, opaque_bytes) == 0u);

  // The reach is bounded on the STACK side too: the entry's own net
  // displacement is zero, which is the last fact of note 7.
  init_passing(f);
  EspSamples samples = call_entry_measured(&f.receiver);
  check(samples.after_return - samples.before_call ==
        static_cast<std::uint32_t>(kEntryCleanupBytes));

  // The three callees are three different addresses and the three rel32s
  // resolve to them.
  check(kDelegateTargetVa == 0x00b8dab0u);
  check(kGlobalSlotTargetVa == 0x00b3d2a0u);
  check(kLookupTargetVa == 0x00ba9370u);
  check(kDelegateTargetVa != kGlobalSlotTargetVa);
  check(kDelegateTargetVa != kLookupTargetVa);
  check(kGlobalSlotTargetVa != kLookupTargetVa);
  check(kRecordedOutgoingDirectCallEdges == 3u);
  check(kRecordedIncomingDirectCallEdges == 40u);

  // The branch arithmetic, recomputed rather than restated.
  check(kComputedNullArm == 0x00c71e67u);
  check(kComputedNullArmSecond == 0x00c71e67u);
  check(kJzDisplacement == 0x2a);
  check(kJnzDisplacement == 0x20);
  check(static_cast<std::uint8_t>(kTargetEncoding[12]) == 0x2au);
  check(static_cast<std::uint8_t>(kTargetEncoding[22]) == 0x20u);

  // The fixture really does exercise the passing path, so the other cases are
  // not all trivially returning zero.
  init_passing(f);
  check(call_entry(&f.receiver) == kLookupResult);
  check(g_lookup_trace.call_count == 1u);
  check(g_dispatch_trace.tag == kTagTargetSlot);
}

}
}

namespace {

using namespace openspore::reconstruction::pkg_00c71e30_empire5;

int run_tests() {
  model::test_both_guards_and_the_constant_five();
  model::test_delegated_displacement_is_bytes_and_is_13c();
  model::test_delegation_is_a_receiver_handover();
  model::test_dispatch_receiver_is_the_address_not_the_word();
  model::test_slot_displacement_is_4c_and_wrong_indices_are_observable();
  model::test_stack_is_measured_and_the_pushed_word_reaches_the_last_callee();
  model::test_return_semantics_verbatim_and_zero();
  model::test_encoding_and_body_bounds();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00C71E30_THISCALL