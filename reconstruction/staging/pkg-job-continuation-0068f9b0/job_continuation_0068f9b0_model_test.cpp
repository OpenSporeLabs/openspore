// Model test for the reconstruction of VA 0x0068f9b0.
//
// The machine body, verbatim:
//
//   0x0068f9b0  PUSH EBX
//   0x0068f9b1  PUSH ESI
//   0x0068f9b2  MOV ESI,[ESP+0x0C]   ; first stack argument
//   0x0068f9b6  MOV EBX,ECX          ; receiver
//   0x0068f9b8  PUSH EDI
//   0x0068f9b9  MOV EDI,[EBX+0x8]    ; stored state
//   0x0068f9bc  CMP ESI,EDI
//   0x0068f9be  JE  0x0068f9dc
//   0x0068f9c0  TEST ESI,ESI
//   0x0068f9c2  JE  0x0068f9cc
//   0x0068f9c4  MOV EAX,[ESI]
//   0x0068f9c6  MOV EDX,[EAX]
//   0x0068f9c8  MOV ECX,ESI
//   0x0068f9ca  CALL EDX
//   0x0068f9cc  MOV [EBX+0x8],ESI
//   0x0068f9cf  TEST EDI,EDI
//   0x0068f9d1  JE  0x0068f9dc
//   0x0068f9d3  MOV EAX,[EDI]
//   0x0068f9d5  MOV EDX,[EAX+0x4]
//   0x0068f9d8  MOV ECX,EDI
//   0x0068f9da  CALL EDX
//   0x0068f9dc  POP EDI
//   0x0068f9dd  POP ESI
//   0x0068f9de  POP EBX
//   0x0068f9df  RET 0x4
//
// The two slot hooks each append a two-byte record to a shared log: the id of
// the object that ran, then a marker describing what the receiver's state field
// held at that instant. The marker is what makes the ORDER of the body
// observable rather than merely the set of callees:
//
//   0x00  the state field was null
//   0x01  the state field was non-null and equal to the running object
//   0x02  the state field was non-null and different from the running object
//
// 0x01 is the marker a mis-ordered body produces and the correct body never
// produces on a transition, which is what makes the ordering assertions below
// discriminating rather than decorative.

#include "job_continuation_0068f9b0.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace {

using openspore::reconstruction::pkg_job_continuation_0068f9b0::ContinuationReceiver;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::kPointerSize;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::kStateFieldOffset;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::kStackBytesCleaned;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::StateSlotFunction;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::StateInterface;
using openspore::reconstruction::pkg_job_continuation_0068f9b0::StateObject;

// A slot records a tag first, so which of the two vtable entries (0x0068f9c6
// vs 0x0068f9d5) was taken is observable and not merely assumed.
constexpr std::uint8_t kTagSlot0 = 0xA0;
constexpr std::uint8_t kTagSlot1 = 0xB0;
// A slot 1 that is distinguishable from the default slot1_hook, used to pin
// WHICH word of the table the body dispatched (see case 9).
constexpr std::uint8_t kTagSlot1Distinct = 0xC0;

// ...then the id of the object it was entered with, which is how the test pins
// WHICH object each slot received rather than just how many calls happened...
// ...then what the receiver's state field held at that instant, which is what
// makes the order of the body observable rather than merely its callee set:
//
//   0x00  the state field was null
//   0x01  the state field was non-null and equal to the running object
//   0x02  the state field was non-null and different from the running object
//
// 0x01 is the marker a mis-ordered body produces and the correct body never
// produces on a transition, which is what makes the ordering assertions below
// discriminating rather than decorative.
constexpr std::uint8_t kFieldNull = 0x00;
constexpr std::uint8_t kFieldIsSelf = 0x01;
constexpr std::uint8_t kFieldOther = 0x02;

// The sentinel tag. Nothing in the machine body dispatches it, so its presence
// in the log means a dispatch read a slot the listing does not have.
constexpr std::uint8_t kTagSentinel = 0xF0;

// ---------------------------------------------------------------------------
// The machine ABI, asserted at compile time
// ---------------------------------------------------------------------------

// `MOV EBX,ECX` at 0x0068f9b6 puts the receiver in ECX and `RET 0x4` at
// 0x0068f9df makes the callee drop the one stack argument: __thiscall with
// exactly one stack parameter. Binding the reconstruction through this pointer
// type means a signature taking the argument elsewhere, adding a second stack
// parameter, or returning a value would not build -- the convention is a
// checked fact here rather than a comment.
using MachineAbi = void(PKG_JOB_CONTINUATION_0068F9B0_THISCALL*)(ContinuationReceiver*,
                                                                 StateObject*);
MachineAbi const kSetState =
    &openspore::reconstruction::pkg_job_continuation_0068f9b0::continuation_set_state_0068f9b0;

static_assert(sizeof(MachineAbi) == kPointerSize, "a code pointer on the 32-bit target");
static_assert(kStackBytesCleaned == kPointerSize,
              "RET 0x4 at 0x0068f9df cleans exactly one pointer-sized argument");

// ---------------------------------------------------------------------------
// Fixtures
// ---------------------------------------------------------------------------

// The state object as the model sees it. The machine reads only offset 0
// (`MOV EAX,[ESI]` at 0x0068f9c4, `MOV EAX,[EDI]` at 0x0068f9d3), so it is
// derived from StateObject -- which is exactly one vptr at offset 0 and
// nothing else -- and everything past that is test instrumentation, with guard
// bands proving the body never wrote any of it.
struct FakeState : StateObject {
  std::uint8_t id;
  std::vector<std::uint8_t>* log;
  ContinuationReceiver* owner;  // lets a slot observe the receiver slot at 0x8
  std::uint8_t lead[kPointerSize];
  std::vector<std::uint8_t> payload;
  std::uint8_t trail[kPointerSize];
};

// The receiver with canary padding on BOTH sides. The body writes exactly one
// dword of it, at +0x8; the lead band catches a store at the wrong offset and
// the trail band catches an overrun past the modelled object.
struct GuardedReceiver {
  std::uint8_t lead[kPointerSize];
  ContinuationReceiver inner;
  std::uint8_t trail[kPointerSize];
};
static_assert(offsetof(GuardedReceiver, inner) == kPointerSize, "guard layout");

// A dispatch table with a callable SENTINEL immediately past its last slot.
//
// The listing reads exactly two slots: table+0x0 (0x0068f9c6) and table+0x4
// (0x0068f9d5). A body that reaches slot 1 by SUBSCRIPTING the table
// (`table[1].slot1`) instead of by slot index advances by
// sizeof(StateInterface) and reads table+0xC. Whether that is caught depends
// entirely on what happens to live there: in a fixture whose two tables are
// adjacent, table+0xC of the first lands on the SECOND table's slot 1, which is
// a perfectly callable pointer, so the wrong dispatch silently succeeds and the
// test passes. That is precisely the bug this fixture failed to catch.
//
// Putting a sentinel that logs `kTagSentinel` directly after slot 1 makes the
// overrun observable at every call site regardless of neighbouring layout: a
// one-slot-too-far dispatch is recorded in the log instead of quietly landing
// on a valid pointer. The sentinel is deliberately a real function, so the
// overrun is detected by an assertion on the log rather than by a crash -- the
// test says WHAT was wrong instead of merely faulting.
struct SentinelTable {
  StateInterface table;
  StateSlotFunction sentinel;
};

// A slot 0 that overwrites the receiver's state field with a third object
// before returning, standing in for any re-entrant or side-effecting acquire.
// `g_clobber_target` is where it writes; the test asserts the body still
// releases the pointer it captured at 0x0068f9b9 and not this impostor.
StateObject* g_clobber_target = nullptr;

std::uint8_t ObserveField(const ContinuationReceiver* owner, const FakeState* self) {
  StateObject* const field = state_slot_at(owner, kStateFieldOffset);
  if (field == nullptr) {
    return kFieldNull;
  }
  return field == static_cast<const StateObject*>(self) ? kFieldIsSelf : kFieldOther;
}

void PKG_JOB_CONTINUATION_0068F9B0_THISCALL slot0_hook(StateObject* self) {
  FakeState* const state = static_cast<FakeState*>(self);
  state->log->push_back(kTagSlot0);
  state->log->push_back(state->id);
  state->log->push_back(ObserveField(state->owner, state));
}

void PKG_JOB_CONTINUATION_0068F9B0_THISCALL slot1_hook(StateObject* self) {
  FakeState* const state = static_cast<FakeState*>(self);
  state->log->push_back(kTagSlot1);
  state->log->push_back(state->id);
  state->log->push_back(ObserveField(state->owner, state));
}

// Slot 1 of the same table, told apart by its tag. See case 9.
void PKG_JOB_CONTINUATION_0068F9B0_THISCALL distinct_slot1_hook(StateObject* self) {
  FakeState* const state = static_cast<FakeState*>(self);
  state->log->push_back(kTagSlot1Distinct);
  state->log->push_back(state->id);
  state->log->push_back(ObserveField(state->owner, state));
}

void PKG_JOB_CONTINUATION_0068F9B0_THISCALL clobber_slot0_hook(StateObject* self) {
  FakeState* const state = static_cast<FakeState*>(self);
  state->log->push_back(kTagSlot0);
  state->log->push_back(state->id);
  state->log->push_back(ObserveField(state->owner, state));
  state_slot_at(state->owner, kStateFieldOffset) = g_clobber_target;  // clobber the field mid-flight
}

// Reached only by a dispatch that reads a slot past table+0x4. It records
// itself and returns without touching the fixture, so the assertion that fails
// is about the LOG rather than about a wild jump.
void PKG_JOB_CONTINUATION_0068F9B0_THISCALL sentinel_hook(StateObject* self) {
  static_cast<FakeState*>(self)->log->push_back(kTagSentinel);
}

struct Fixture {
  // SentinelTable, not a bare StateInterface: `sentinel` occupies the word
  // immediately after slot 1, so the fixture models the table as "two real
  // slots plus one trap" rather than "two slots whose overflow is somebody
  // else's memory".
  SentinelTable plain_vtable;
  SentinelTable clobber_vtable;
  std::vector<std::uint8_t> log;
  GuardedReceiver receiver;
  FakeState a;
  FakeState b;
  FakeState c;
};

void InitState(Fixture& f, FakeState& state, std::uint8_t id) {
  openspore::reconstruction::pkg_job_continuation_0068f9b0::state_table_at(&state, openspore::reconstruction::pkg_job_continuation_0068f9b0::kStateTableOffset) = &f.plain_vtable.table;
  state.id = id;
  state.log = &f.log;
  state.owner = &f.receiver.inner;
  std::memset(state.lead, 0xC3, sizeof(state.lead));
  std::memset(state.trail, 0xC3, sizeof(state.trail));
  state.payload.assign(24, 0xC3);
}
void InitFixture(Fixture& f) {
  std::memset(&f.plain_vtable, 0, sizeof(f.plain_vtable));
  std::memset(&f.clobber_vtable, 0, sizeof(f.clobber_vtable));
  f.plain_vtable.table.slot0 = &slot0_hook;
  f.plain_vtable.table.slot1 = &slot1_hook;
  f.plain_vtable.sentinel = &sentinel_hook;
  f.clobber_vtable.table.slot0 = &clobber_slot0_hook;
  f.clobber_vtable.table.slot1 = &slot1_hook;
  f.clobber_vtable.sentinel = &sentinel_hook;
  f.log.clear();
  std::memset(f.receiver.lead, 0xA5, sizeof(f.receiver.lead));
  std::memset(f.receiver.inner.unobserved, 0xA5, sizeof(f.receiver.inner.unobserved));
  state_slot_at(&f.receiver.inner, kStateFieldOffset) = nullptr;
  std::memset(f.receiver.trail, 0xA5, sizeof(f.receiver.trail));
  InitState(f, f.a, 1u);
  InitState(f, f.b, 2u);
  InitState(f, f.c, 3u);
  g_clobber_target = nullptr;
}

// No record in any log is ever the sentinel tag. Every case asserts this, so a
// dispatch that reads a slot the listing does not have is reported at the call
// site that made it rather than surfacing later as a crash.
void AssertNoSentinel(const Fixture& f) {
  for (std::size_t i = 0; i < f.log.size(); ++i) {
    assert(f.log[i] != kTagSentinel);
  }
}

void AssertReceiverIntact(const Fixture& f) {
  // Bytes 0x0..0x7 are named by no instruction of 0x0068f9b0; the only
  // receiver dword the body may write is the field at +0x8.
  for (std::size_t i = 0; i < kStateFieldOffset; ++i) {
    assert(f.receiver.inner.unobserved[i] == 0xA5);
  }
  // And nothing past the modelled object.
  for (std::size_t i = 0; i < sizeof(f.receiver.trail); ++i) {
    assert(f.receiver.trail[i] == 0xA5);
  }
  for (std::size_t i = 0; i < sizeof(f.receiver.lead); ++i) {
    assert(f.receiver.lead[i] == 0xA5);
  }
}

void AssertStateIntact(const FakeState& s) {
  for (std::size_t i = 0; i < sizeof(s.lead); ++i) {
    assert(s.lead[i] == 0xC3);
  }
  for (std::size_t i = 0; i < sizeof(s.trail); ++i) {
    assert(s.trail[i] == 0xC3);
  }
  for (std::size_t i = 0; i < s.payload.size(); ++i) {
    assert(s.payload[i] == 0xC3);
  }
}

// The byte an object contributes to a log record: its own id. Reading it back
// off the log is how the test proves WHICH object each slot was entered with,
// which is the part of the body a set-of-callees assertion cannot see.
std::uint8_t IdOf(const StateObject* p, const Fixture& f) {
  if (p == &f.a) {
    return 1u;
  }
  if (p == &f.b) {
    return 2u;
  }
  if (p == &f.c) {
    return 3u;
  }
  return 0xFFu;  // an object the fixture does not own
}

}  // namespace

int main() {
  // -----------------------------------------------------------------------
  // 1. Empty receiver, empty argument. `CMP ESI,EDI` at 0x0068f9bc takes the
  //    JE at 0x0068f9be, so the body is a total no-op: neither virtual runs
  //    and the field is not even rewritten, 0x0068f9cc being unreachable.
  //    A body that tested only the argument for null would still store here
  //    and still run nothing, so this case is paired with case 4 to separate
  //    the equality test from the null tests.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    kSetState(&f.receiver.inner, nullptr);
    assert(f.log.empty());
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == nullptr);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
  }

  // -----------------------------------------------------------------------
  // 2. First state into an empty receiver. `TEST ESI,ESI` at 0x0068f9c0
  //    passes so slot 0 runs on the incoming object (0x0068f9ca) and sees
  //    the field still null (kFieldNull -- the store has not happened). The
  //    store at 0x0068f9cc lands, and `TEST EDI,EDI` at 0x0068f9cf fails
  //    because EDI was null, so slot 1 never runs.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    kSetState(&f.receiver.inner, &f.a);
    assert((f.log == std::vector<std::uint8_t>{kTagSlot0, 1u, kFieldNull}));
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.a);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
  }

  // -----------------------------------------------------------------------
  // 3. The full path, and the one the ordering of the body is about.
  //    slot 0 runs on the INCOMING object (id 2) and sees the field still
  //    holding the OLD pointer -- kFieldOther, because a non-null field
  //    differing from the running object is precisely "the store has not run
  //    yet"; it could not be kFieldIsSelf, which is the marker a body that
  //    stored first would produce. Then the store at 0x0068f9cc, then slot 1
  //    on the OUTGOING object (id 1), again seeing kFieldOther, which it
  //    could not see if the store came after 0x0068f9da.
  //    The full 4-byte log therefore pins store-after-slot0 AND
  //    store-before-slot1, and pins which object each slot received.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    state_slot_at(&f.receiver.inner, kStateFieldOffset) = &f.a;
    kSetState(&f.receiver.inner, &f.b);
    assert((f.log == std::vector<std::uint8_t>{kTagSlot0, 2u, kFieldOther, kTagSlot1, 1u, kFieldOther}));
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.b);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
    AssertStateIntact(f.b);
  }

  // -----------------------------------------------------------------------
  // 4. Clearing with a null argument. The JE at 0x0068f9be is not taken
  //    because the stored pointer is non-null, so `TEST ESI,ESI` at
  //    0x0068f9c0 fails and jumps to 0x0068f9cc -- the STORE, not past it.
  //    The field is therefore cleared even though slot 0 never ran. Then
  //    `TEST EDI,EDI` at 0x0068f9cf sees the captured old pointer and slot 1
  //    runs on it, observing the now-null field (kFieldNull).
  //    A body that guarded the store behind the non-null argument test would
  //    leave the field at &f.a and log a different sequence.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    state_slot_at(&f.receiver.inner, kStateFieldOffset) = &f.a;
    kSetState(&f.receiver.inner, nullptr);
    assert((f.log == std::vector<std::uint8_t>{kTagSlot1, 1u, kFieldNull}));
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == nullptr);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
  }

  // -----------------------------------------------------------------------
  // 5. The test at 0x0068f9bc is on the POINTER, not the contents. Handing
  //    back the object already stored runs neither virtual and rewrites
  //    nothing, even though the object is fully live and both its slots are
  //    populated. Reinstalling an object that compares equal in every other
  //    respect still must be free.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    state_slot_at(&f.receiver.inner, kStateFieldOffset) = &f.a;
    kSetState(&f.receiver.inner, &f.a);
    assert(f.log.empty());
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.a);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
  }

  // -----------------------------------------------------------------------
  // 6. The old pointer is captured ONCE, at 0x0068f9b9, before either call.
  //    Here slot 0 deliberately clobbers the field with the impostor &f.c.
  //    EDI still holds the value loaded at entry, so slot 1 must run on that
  //    object (id 1) and NOT on the impostor (id 3); and the store at
  //    0x0068f9cc comes after the clobber, so the field ends at the
  //    argument, not at the impostor.
  //    A body that re-read the receiver slot at 0x0068f9d3 releases id 3 and
  //    fails the id-1 record; a body that stored before calling slot 0 lets
  //    the clobber win and fails the final field assertion.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    FakeState redirected = f.a;
    openspore::reconstruction::pkg_job_continuation_0068f9b0::state_table_at(&redirected, openspore::reconstruction::pkg_job_continuation_0068f9b0::kStateTableOffset) = &f.clobber_vtable.table;
    std::memcpy(redirected.lead, f.a.lead, sizeof(f.a.lead));
    std::memcpy(redirected.trail, f.a.trail, sizeof(f.a.trail));
    redirected.payload = f.a.payload;
    g_clobber_target = &f.c;
    state_slot_at(&f.receiver.inner, kStateFieldOffset) = &redirected;

    kSetState(&f.receiver.inner, &f.b);
    assert((f.log == std::vector<std::uint8_t>{kTagSlot0, 2u, kFieldOther, kTagSlot1, 1u, kFieldOther}));
    // The impostor was never dispatched to.
    for (std::size_t i = 0; i < f.log.size(); i += 3) {
      assert(f.log[i + 1] != 3u);
    }
    // The store at 0x0068f9cc overwrote the clobber, because it is reached
    // after 0x0068f9ca and does not re-read anything.
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.b);
    g_clobber_target = nullptr;
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
  }

  // -----------------------------------------------------------------------
  // 7. Repeated transitions: every full path produces the same 4-byte log and
  //    every identity transition produces an empty one, and the guard bands
  //    survive the lot. A body missing either null guard fails on the first
  //    transition into or out of the null field.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    StateObject* const order[3] = {&f.a, &f.b, &f.c};
    StateObject* current = nullptr;
    for (int round = 0; round < 30; ++round) {
      StateObject* const next = order[round % 3];
      f.log.clear();
      kSetState(&f.receiver.inner, next);
      if (current == next) {
        // 0x0068f9be: identical pointer, nothing happened.
        assert(f.log.empty());
      } else if (current == nullptr) {
        // 0x0068f9cf TEST EDI,EDI skips slot 1: the receiver was empty, so
        // only slot 0 ran and it saw a null field.
        assert((f.log == std::vector<std::uint8_t>{kTagSlot0, IdOf(next, f), kFieldNull}));
      } else {
        // Full path. slot 0 on the incoming object, slot 1 on the outgoing
        // one, and neither ever sees the field equal to itself.
        assert((f.log == std::vector<std::uint8_t>{kTagSlot0, IdOf(next, f), kFieldOther,
                                                   kTagSlot1, IdOf(current, f), kFieldOther}));
        assert(f.log[2] != kFieldIsSelf);
        assert(f.log[5] != kFieldIsSelf);
      }
      assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == next);
      current = next;
    AssertNoSentinel(f);
      AssertReceiverIntact(f);
    }
    AssertStateIntact(f.a);
    AssertStateIntact(f.b);
    AssertStateIntact(f.c);
  }

  // -----------------------------------------------------------------------
  // 8. Repeated cycles through null, so both null arms and the identity arm
  //    are all exercised against a non-empty predecessor.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    for (int round = 0; round < 12; ++round) {
      f.log.clear();
      // null -> &f.a: slot 0 only (0x0068f9cf skips slot 1 on a null old).
      kSetState(&f.receiver.inner, &f.a);
      assert((f.log == std::vector<std::uint8_t>{kTagSlot0, 1u, kFieldNull}));
      assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.a);

      f.log.clear();
      // &f.a -> null: slot 1 only, and it sees the field the store already
      // cleared (0x0068f9c2 jumps to the store, not past it).
      kSetState(&f.receiver.inner, nullptr);
      assert((f.log == std::vector<std::uint8_t>{kTagSlot1, 1u, kFieldNull}));
      assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == nullptr);

      f.log.clear();
      // null -> null: the equality test at 0x0068f9bc, nothing at all.
      kSetState(&f.receiver.inner, nullptr);
      assert(f.log.empty());
    AssertNoSentinel(f);
      AssertReceiverIntact(f);
    }
    AssertStateIntact(f.a);
  }

  // -----------------------------------------------------------------------
  // 9. The slot DISPLACEMENT, pinned directly.
  //    0x0068f9c6 reads table+0x0 and 0x0068f9d5 reads table+0x4 -- two slots
  //    apart by kPointerSize, not by sizeof(StateInterface). The only way to
  //    express that difference in C++ is to reach slot 1 by BYTE offset; a
  //    `table[1]` subscript advances by a whole StateInterface and lands on
  //    table+0xC, a full slot past the one the machine reads.
  //    The two tables here are ADJACENT in the fixture and both carry slot1 ==
  //    &slot1_hook, so table+0xC of the first aliases the second's slot 1 and
  //    the resulting call SUCCEEDS. That alias is exactly what let the defect
  //    survive every case above, so this case removes the alias instead:
  //    slot 1 of the outgoing object is a DIFFERENT hook, tagged differently,
  //    and a callable sentinel sits immediately after it. Reading table+0x4
  //    therefore produces the slot-1 record; reading table+0xC produces the
  //    sentinel record and fails the assertion below by name.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    // Make the outgoing object's slot 1 observably NOT slot1_hook, so the log
    // pins WHICH word the body dispatched.
    f.plain_vtable.table.slot1 = &distinct_slot1_hook;
    f.plain_vtable.sentinel = &sentinel_hook;
    state_slot_at(&f.receiver.inner, kStateFieldOffset) = &f.a;
    kSetState(&f.receiver.inner, &f.b);
    // slot 0 of &f.b (plain table, slot 0) then slot 1 of &f.a, which must be
    // table+0x4 -- distinct_slot1_hook, NOT the sentinel one slot further on.
    assert((f.log == std::vector<std::uint8_t>{kTagSlot0, 2u, kFieldOther,
                                               kTagSlot1Distinct, 1u, kFieldOther}));
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
    AssertStateIntact(f.a);
    AssertStateIntact(f.b);
  }

  // -----------------------------------------------------------------------
  // 10. The frame is balanced. Three pushes (0x0068f9b0, 0x0068f9b1,
  //     0x0068f9b8) against three pops (0x0068f9dc, 0x0068f9dd, 0x0068f9de),
  //     then RET 0x4 removing the one argument: a call through the ABI above
  //     must leave ESP exactly where it started. Taking the address of a local
  //     across the call is a direct read of that claim, and an unbalanced
  //     prologue would corrupt the loop itself rather than merely a value.
  // -----------------------------------------------------------------------
  {
    Fixture f;
    InitFixture(f);
    volatile char anchor = 0;
    char* const before = const_cast<char*>(&anchor);
    for (int i = 0; i < 1000; ++i) {
      kSetState(&f.receiver.inner, (i & 1) != 0 ? &f.a : &f.b);
      assert(&anchor == before);
    }
    // The last iteration is i == 999, which is odd, so the field is left
    // holding the odd-arm object &f.a.
    assert(state_slot_at(&f.receiver.inner, kStateFieldOffset) == &f.a);
    AssertNoSentinel(f);
    AssertReceiverIntact(f);
  }

  return 0;
}
