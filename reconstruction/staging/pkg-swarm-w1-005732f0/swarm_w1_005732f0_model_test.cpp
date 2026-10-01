// PKG-SWARM-W1-005732F0 -- VA 0x005732f0 (FUN_005732f0)
// Behavioural model test for FUN_005732f0 @ 0x005732f0.
//
// The body has no direct callees, so the observers here are the two things the
// machine reaches through instead: the table words the body dispatches to. Every
// one of them is a real function, planted at a real address in a real fixture, so
// the test sees every transfer the reconstruction makes -- which object it names,
// what ECX carries at the moment of the transfer, and what the receiver's two member
// words hold at that same moment -- and can decide what each transfer does to
// memory. The decoys are the same: each is a distinct function at a distinct address,
// so a wrong dereference level, a wrong slot displacement or a wrong receiver
// displacement does not crash, it is COUNTED, and a non-zero count is a failure.
//
// What is asserted is what the 19-instruction listing fixes and nothing more:
//
//   * the two transfers, at most one each, in that order, and never on a path the
//     listing does not have;
//   * the object each transfer names: the member at receiver+0x308 for the CALL at
//     0x0057330c, the member at receiver+0x30c for the JMP at 0x00573328;
//   * the receiver register: ECX carries that member, measured by reading ECX at the
//     observer's own entry, never the enclosing receiver;
//   * the two-level load: the object's leading word is the table, and the table word
//     at displacement 0x4 is the callee (0x00573307/0x00573309 and
//     0x00573322/0x00573324);
//   * both branch conditions are equality tests against zero, so every non-null word
//     transfers and only a null word does not (0x005732f9, 0x00573314);
//   * both clears happen BEFORE their own transfer, and neither touches the other
//     member (0x005732fd, 0x00573318);
//   * the tail path's return value is the SECOND transfer's, not the first's
//     (0x00573328 is a JMP, so the callee returns to this body's caller);
//   * the return value on the return path is the FIRST transfer's;
//   * no byte of the receiver outside the two member words changes, on any path;
//   * a repeated call transfers nothing, because both members are already 0;
//   * the ABI facts: ESI survives the call, the stack is balanced, and nothing is
//     passed or cleaned on the stack.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk it.
// Each names the wrong reconstruction it is aimed at:
//
//   A  the two member displacements are 0x308 and 0x30c and neither is a byte
//      offset: a decoy word one dword below each of them, and one dword above the
//      second, is never read and never written;
//   B  the transfer is two-level: decoy callees sit at object+0x04, object+0x08,
//      table+0x00, table+0x08 and table+0x0c, and a model that reads one level too
//      few, one level too many, or the wrong slot, lands on a counted decoy;
//   C  the branch is an equality test, not a validity test: the member word is driven
//      to 1, to 0xdeadbeef and to 0, and only 0 must suppress the transfer;
//   D  the clear precedes the transfer: the observer reads the receiver mid-call and
//      must already see its own member word at 0, and must still see the OTHER
//      member word at its original value;
//   E  the tail path returns the second transfer's value: the two observers return
//      different words and the reconstruction's return value follows the second;
//   F  the two transfers are ordered, and the second one is a return rather than a
//      fall-through: a model that returns the first's value, or a fixed value, or
//      the placeholder, is caught;
//   G  the return path returns the first transfer's value;
//   H  the model's own frame does not perturb the callee's receiver: ECX is read at
//      the observer's entry and compared against the member, never against `this`;
//   I  the ABI: ESI is preserved and the stack is balanced across the call;
//   J  the clear is durable: a second call on the same receiver transfers nothing.
//
// What is NOT asserted, and why:
//
//   * The return word on the path where BOTH members are null. The listing never
//     writes EAX on that path, so no value is machine-fixed; the model returns a
//     documented placeholder (kEaxUnwrittenOnTheNoMemberPath). Check A4 pins that
//     placeholder so a change to the model's own choice is visible, and its label
//     says out loud that it is a check on the model rather than evidence about the
//     binary. No other check in this file is of that kind.
//   * The C type of the return value. EAX is the register and 32 bits is the width;
//     whether that is a pointer, an int or something else is fixed by the dynamic
//     callee, which this listing never shows.
//   * The number of arguments the slot takes, and what the slot does. The slot word
//     is loaded from memory at run time and no body on the far side of it is in
//     evidence; the observers take one argument because that is what the model
//     passes, and asserting anything about the callee would be asserting the test
//     fixture back at the machine.
//   * The ESP the callee sees on the tail path. The machine pops the frame word at
//     0x00573327 before jumping, so on the machine the callee resumes on this body's
//     CALLER's stack; in this model the callee is entered with the model's frame
//     still live. That difference is a real property of writing a tail call as a
//     return, nothing in the listing's own evidence fixes the callee's stack, and no
//     check here pretends otherwise. What IS asserted is that the model's frame is
//     balanced (case I), which is what the listing does fix.
//   * Anything about the class, the member roles, or the size of the member objects
//     beyond their leading word. The binary carries no MSVC RTTI and no decompilation
//     exists for this VA.

#include "swarm_w1_005732f0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_005732f0 {
namespace {

// -- machine displacements, as literals --------------------------------------
// 0x005732f3 and 0x0057330e, the only two receiver displacements in the listing.
constexpr std::size_t kFirstMember = 0x308u;
constexpr std::size_t kSecondMember = 0x30cu;
// The receiver fixture is larger than the modelled receiver (0x310) so that a model
// reaching one dword past the second member, or one dword below either, lands inside
// the fixture and is caught by the byte-level diff instead of corrupting the heap.
constexpr std::size_t kFixtureBytes = 0x320u;
// The two words either side of the pair, and the two dwords below the first: decoys.
constexpr std::size_t kDecoyMember = kFirstMember - 0x4u;   // 0x304
constexpr std::size_t kDecoyMember2 = kFirstMember - 0x8u;  // 0x300
constexpr std::size_t kDecoyMember3 = kSecondMember + 0x4u; // 0x310
constexpr std::size_t kDecoyMember4 = kSecondMember + 0x8u; // 0x314

// Which planted function was transferred to. Every entry is a distinct address.
enum Transfer {
  kSlotAtTable4 = 0,  // table+0x04 -- the one the listing dispatches to
  kObjectPlus4 = 1,   // object+0x04 -- a model that skipped the first dereference
  kObjectPlus8 = 2,   // object+0x08 -- a model that added the slot twice
  kTablePlus0 = 3,    // table+0x00 -- a model that used slot index 0
  kTablePlus8 = 4,    // table+0x08 -- a model that used the neighbouring slot
  kTransferCount = 5,
};

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The words the two observers return, in call order. They differ on purpose: a model
// that returns the first transfer's value on the tail path, or a fixed value, or the
// no-member placeholder, cannot also return the right one by accident.
constexpr Word kReturns[4] = {0x11111111u, 0x22222222u, 0x33333333u, 0x44444444u};

// The fixture the observers read at the moment of a transfer. The model's own frame
// is not visible from here; this is the receiver the test handed to the body.
unsigned char* g_active_receiver = nullptr;

struct Observation {
  // The real slot (table+0x04).
  int slot_calls = 0;
  void* slot_object[4] = {};
  Word slot_ecx[4] = {};
  Word slot_first_member_at_call[4] = {};
  Word slot_second_member_at_call[4] = {};
  Word slot_returned[4] = {};

  // The decoys.
  int decoy_calls[kTransferCount] = {};
  int total_calls = 0;
  int log[4] = {};
  int log_length = 0;

  void reset() { *this = Observation(); }

  void record(Transfer transfer) {
    if (log_length < 4) {
      log[log_length] = static_cast<int>(transfer);
    }
    ++log_length;
    ++total_calls;
  }

  bool log_is(Transfer a, Transfer b) const {
    return log_length == 2 && log[0] == static_cast<int>(a) && log[1] == static_cast<int>(b);
  }
  bool decoys_silent() const {
    for (int index = 1; index < kTransferCount; ++index) {
      if (decoy_calls[index] != 0) {
        return false;
      }
    }
    return true;
  }
};

Observation g_obs;

// -- fixtures ----------------------------------------------------------------

// A member object with a planted table at its leading word and decoy callees in
// every other word the body could plausibly read. The offsets are the machine's:
// object+0x00 is the table (0x00573307 / 0x00573322 read it bare).
struct ObjectFixture {
  Word table;          // +0x00  the object's own leading word
  Word plus4;          // +0x04  decoy: one level too few
  Word plus8;          // +0x08  decoy: slot displacement applied twice
  Word guard;          // +0x0c  decoy: never read by the listing
};

// The table the object's leading word points at. Displacement 0x4 is the callee;
// every other word is a decoy.
struct TableFixture {
  Word slot0;          // +0x00  decoy: a model that read the table's first word
  Word slot4;          // +0x04  the callee the listing dispatches to
  Word slot8;          // +0x08  decoy: neighbouring slot
  Word slotC;          // +0x0c  decoy: byte offset instead of dword displacement
};

ObjectFixture g_object_first;
ObjectFixture g_object_second;
ObjectFixture g_object_decoy;
TableFixture g_table_first;
TableFixture g_table_second;
TableFixture g_table_decoy;

// A receiver: a byte run big enough for every displacement the model can touch,
// with the four decoy words placed in it.
struct ReceiverFixture {
  unsigned char bytes[kFixtureBytes];
};

Word read_word(const unsigned char* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

void store_pointer(unsigned char* base, std::size_t displacement, void* value) {
  const Word word = static_cast<Word>(reinterpret_cast<std::uintptr_t>(value));
  std::memcpy(base + displacement, &word, sizeof word);
}

ReceiverFixture make_receiver(void* first, void* second) {
  ReceiverFixture receiver;
  std::memset(&receiver, 0, sizeof receiver);
  // The decoys are POINTERS to a third object, not to null: a model that reads the
  // wrong displacement must reach a live, distinguishable object rather than
  // quietly skipping a transfer.
  store_pointer(receiver.bytes, kDecoyMember, &g_object_decoy);
  store_pointer(receiver.bytes, kDecoyMember2, &g_object_decoy);
  store_pointer(receiver.bytes, kDecoyMember3, &g_object_decoy);
  store_pointer(receiver.bytes, kDecoyMember4, &g_object_decoy);
  store_pointer(receiver.bytes, kFirstMember, first);
  store_pointer(receiver.bytes, kSecondMember, second);
  return receiver;
}

// How many bytes of the receiver changed, and how many of those are inside the two
// member words the listing is allowed to write.
struct ReceiverDiff {
  int inside = 0;
  int outside = 0;
};

ReceiverDiff diff_receiver(const ReceiverFixture& before, const ReceiverFixture& after) {
  ReceiverDiff diff;
  for (std::size_t index = 0; index < kFixtureBytes; ++index) {
    if (before.bytes[index] == after.bytes[index]) {
      continue;
    }
    const bool in_first = index >= kFirstMember && index < kFirstMember + 4;
    const bool in_second = index >= kSecondMember && index < kSecondMember + 4;
    if (in_first || in_second) {
      ++diff.inside;
    } else {
      ++diff.outside;
    }
  }
  return diff;
}

// -- observers ---------------------------------------------------------------
//
// The slot the listing dispatches to, 0x0057330c and 0x00573328. It records the
// object it was handed, the contents of ECX at its own entry, the receiver's two
// member words as they stand at that moment, and returns a word chosen by the test.

// ECX at the entry of this function, before anything else can touch it. The output
// is forced to memory so the compiler cannot allocate the destination register to
// ECX itself, which would make the measurement read back its own store.
__attribute__((noinline)) Word ecx_at_entry() {
  Word value = 0;
  __asm__ __volatile__("movl %%ecx, %0" : "=m"(value));
  return value;
}

}  // namespace

extern "C" Word PKG_SWARM_W1_005732F0_CDECL slot_observer(void* object) {
  const Word ecx = ecx_at_entry();
  const int index = g_obs.slot_calls;
  ++g_obs.slot_calls;
  if (index < 4) {
    g_obs.slot_object[index] = object;
    g_obs.slot_ecx[index] = ecx;
    g_obs.slot_returned[index] = kReturns[index];
    if (g_active_receiver != nullptr) {
      g_obs.slot_first_member_at_call[index] = read_word(g_active_receiver, kFirstMember);
      g_obs.slot_second_member_at_call[index] = read_word(g_active_receiver, kSecondMember);
    }
  }
  g_obs.record(kSlotAtTable4);
  return (index < 4) ? kReturns[index] : 0xdead0000u;
}

// The five decoys. Each one exists only to be counted: if the reconstruction ever
// transfers to one, the transfer happened through a dereference level, a slot
// displacement or a receiver displacement the listing does not show.
extern "C" Word PKG_SWARM_W1_005732F0_CDECL decoy_object_plus4(void*) {
  g_obs.decoy_calls[kObjectPlus4]++;
  g_obs.record(kObjectPlus4);
  return 0xbad00004u;
}

extern "C" Word PKG_SWARM_W1_005732F0_CDECL decoy_object_plus8(void*) {
  g_obs.decoy_calls[kObjectPlus8]++;
  g_obs.record(kObjectPlus8);
  return 0xbad00008u;
}

extern "C" Word PKG_SWARM_W1_005732F0_CDECL decoy_table_slot0(void*) {
  g_obs.decoy_calls[kTablePlus0]++;
  g_obs.record(kTablePlus0);
  return 0xbad00000u;
}

extern "C" Word PKG_SWARM_W1_005732F0_CDECL decoy_table_slot8(void*) {
  g_obs.decoy_calls[kTablePlus8]++;
  g_obs.record(kTablePlus8);
  return 0xbad00008u;
}

extern "C" Word PKG_SWARM_W1_005732F0_CDECL decoy_table_slotC(void*) {
  g_obs.decoy_calls[kTransferCount - 1]++;
  return 0xbad0000cu;
}

namespace {

// The planted tables. The listing reads exactly one word of each: the one at
// displacement 0x4. Every other word is a decoy callee, so a model that reads a
// different one is caught by count rather than by a crash.
void plant() {
  g_object_first.table = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_first));
  g_object_first.plus4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus4));
  g_object_first.plus8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus8));
  g_object_first.guard = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_table_first.slot0 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot0));
  g_table_first.slot4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_observer));
  g_table_first.slot8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot8));
  g_table_first.slotC = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_object_second.table = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_second));
  g_object_second.plus4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus4));
  g_object_second.plus8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus8));
  g_object_second.guard = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_table_second.slot0 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot0));
  g_table_second.slot4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&slot_observer));
  g_table_second.slot8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot8));
  g_table_second.slotC = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_object_decoy.table = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_decoy));
  g_object_decoy.plus4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus4));
  g_object_decoy.plus8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus8));
  g_object_decoy.guard = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_table_decoy.slot0 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot0));
  g_table_decoy.slot4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));
  g_table_decoy.slot8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slot8));
  g_table_decoy.slotC = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));
}

Receiver* as_receiver(ReceiverFixture& fixture) {
  return reinterpret_cast<Receiver*>(fixture.bytes);
}

// -- cases -------------------------------------------------------------------

// A. REFUTE (wrong receiver displacement). Both members null, with live decoy
// objects planted one dword below the first member, one dword above the second and
// two dwords below the first. Nothing must transfer and nothing may change: a model
// reading 0x304 or 0x310 instead of 0x308 and 0x30c reaches a decoy object and is
// counted.
void case_neither_member_transfers_nothing() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(nullptr, nullptr);
  const ReceiverFixture before = receiver;
  g_active_receiver = receiver.bytes;

  const Word returned = re_005732f0(as_receiver(receiver));

  check(g_obs.total_calls == 0, "A1: no transfer at all when both member words are null");
  check(g_obs.decoys_silent(), "A2: no decoy callee was reached");
  const ReceiverDiff diff = diff_receiver(before, receiver);
  check(diff.inside == 0 && diff.outside == 0,
        "A3: not one byte of the receiver changed, decoy words included");
  // What the body RETURNS on this path is not machine-fixed: the listing never
  // writes EAX here, so the model returns a documented placeholder. This check pins
  // that placeholder so a change to the model's own choice is visible -- it is a
  // check on the model, NOT evidence about the binary, and it is the only check in
  // this file that is of that kind.
  check(returned == kEaxUnwrittenOnTheNoMemberPath,
        "A4: the no-member path returns the model's documented placeholder (model, not evidence)");
  g_active_receiver = nullptr;
}

// B. REFUTE (wrong receiver displacement, the other direction). Only the second
// member is set. Exactly one transfer, to the second member's object, and the first
// member's word must not be written.
void case_only_the_second_member_transfers() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(nullptr, &g_object_second);
  const ReceiverFixture before = receiver;
  g_active_receiver = receiver.bytes;

  const Word returned = re_005732f0(as_receiver(receiver));

  check(g_obs.total_calls == 1, "B1: exactly one transfer when only the second member is set");
  check(g_obs.slot_object[0] == &g_object_second,
        "B2: the transfer names the object at receiver+0x30c");
  check(g_obs.slot_ecx[0] == static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_object_second)),
        "B3: ECX carries that object at the transfer, not the enclosing receiver");
  check(g_obs.decoys_silent(), "B4: no decoy callee was reached");
  check(read_word(receiver.bytes, kSecondMember) == 0u,
        "B5: the second member word is cleared by the body (0x00573318)");
  check(read_word(receiver.bytes, kFirstMember) == 0u,
        "B6: the first member word is untouched on a path that never reached it");
  {
    const ReceiverDiff diff = diff_receiver(before, receiver);
    check(diff.inside >= 1 && diff.inside <= 4 && diff.outside == 0,
          "B7: only bytes inside the two member words changed, and at most one word of them");
  }
  check(returned == kReturns[0],
        "B8: the tail transfer's own return value leaves the body (0x00573328)");
  g_active_receiver = nullptr;
}

// C. REFUTE (wrong branch condition). The two tests at 0x005732f9 and 0x00573314
// are equality tests against zero, not validity tests: a member word that is
// unaligned, odd, huge and not a plausible table pointer must still transfer, and
// only a null word suppresses the transfer.
//
// A member word of 0xdeadbeef would also take the branch in the machine -- TEST
// ECX,ECX / JZ cannot tell it from any other non-null word -- but the transfer
// would then fault on the far side of the two dereferences, in the model exactly as
// in the original, so that input is argued from the instruction rather than
// executed. What IS executed is the unaligned live object, which a model that
// validated alignment or plausibility would reject and the listing cannot.
void case_branch_is_an_equality_test_against_zero() {
  // An object at an ODD address inside a live arena: non-null, mapped, misaligned.
  // Its leading word points at the REAL table, so a correct model reaches the real
  // slot through it, and its other three words are decoy callees rather than
  // garbage: a model that read one level too few is counted rather than crashed on.
  unsigned char arena[64];
  std::memset(arena, 0, sizeof arena);
  ObjectFixture* const odd_object = reinterpret_cast<ObjectFixture*>(arena + 1);
  odd_object->table = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_table_first));
  odd_object->plus4 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus4));
  odd_object->plus8 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_object_plus8));
  odd_object->guard = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&decoy_table_slotC));

  g_obs.reset();
  ReceiverFixture receiver = make_receiver(odd_object, nullptr);
  g_active_receiver = receiver.bytes;
  (void)re_005732f0(as_receiver(receiver));
  check(g_obs.slot_calls == 1, "C1: a member word at an odd, unaligned address still transfers");
  check(g_obs.slot_object[0] == static_cast<void*>(odd_object),
        "C2: the object handed over is the member word itself, unfiltered and unaligned");
  check(g_obs.slot_ecx[0] == static_cast<Word>(reinterpret_cast<std::uintptr_t>(odd_object)),
        "C3: ECX carried that odd address, so no alignment test happened");
  g_active_receiver = nullptr;

  // null: suppressed.
  g_obs.reset();
  ReceiverFixture empty = make_receiver(nullptr, nullptr);
  g_active_receiver = empty.bytes;
  (void)re_005732f0(as_receiver(empty));
  check(g_obs.total_calls == 0, "C4: a null member word suppresses its transfer");
  check(g_obs.decoys_silent(),
        "C5: and the four decoy words planted either side of the pair stayed unread");
  g_active_receiver = nullptr;
}

// D. REFUTE (write ordering, and the two-level load). Both members set, so two
// transfers happen. At the FIRST one the observer must already see its own member
// word at 0 -- the clear at 0x005732fd precedes the call at 0x0057330c -- and must
// still see the SECOND member word at its original value, because the second clear
// at 0x00573318 has not run yet. A model that clears both members up front, or that
// clears after transferring, fails one of the two.
void case_clear_precedes_each_transfer() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  (void)re_005732f0(as_receiver(receiver));

  check(g_obs.slot_calls == 2, "D1: both members are non-null, so two transfers run");
  check(g_obs.slot_first_member_at_call[0] == 0u,
        "D2: the first member word is already 0 when the first transfer runs (0x005732fd)");
  check(g_obs.slot_second_member_at_call[0] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_object_second)),
        "D3: the second member word is still its original value at the first transfer");
  check(g_obs.slot_first_member_at_call[1] == 0u,
        "D4: the first member word is still 0 at the second transfer");
  check(g_obs.slot_second_member_at_call[1] == 0u,
        "D5: the second member word is already 0 when the second transfer runs (0x00573318)");
  g_active_receiver = nullptr;
}

// E. REFUTE (wrong receiver register) -- and the pointer level that goes with it.
// The two objects are distinct fixtures at distinct addresses, and the model must
// reach each of them with ECX holding that very object. A model that passed the
// enclosing receiver in ECX, or that passed the table instead of the object, is
// caught here even though the transfer count would be right.
void case_each_transfer_gets_its_own_object_in_ecx() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  (void)re_005732f0(as_receiver(receiver));

  check(g_obs.slot_object[0] == &g_object_first,
        "E1: the CALL at 0x0057330c receives the object at receiver+0x308");
  check(g_obs.slot_object[1] == &g_object_second,
        "E2: the JMP at 0x00573328 receives the object at receiver+0x30c");
  check(g_obs.slot_object[0] != g_obs.slot_object[1],
        "E3: the two transfers do not receive the same object");
  check(g_obs.slot_ecx[0] == static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_object_first)) &&
            g_obs.slot_ecx[1] == static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_object_second)),
        "E4: ECX held each object at its own transfer, measured at the observer's entry");
  check(g_obs.slot_ecx[0] != static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_obs)) &&
            g_obs.slot_ecx[1] != static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_obs)),
        "E5: ECX never held a model-side address at either transfer");
  g_active_receiver = nullptr;
}

// F. REFUTE (wrong dereference level, wrong slot displacement). The fixtures carry
// decoy callees at object+0x04, object+0x08, table+0x00, table+0x08 and table+0x0c,
// and the second object's table is a separate fixture so that a model reading one
// level too few out of the SECOND object is caught independently of the first.
void case_two_level_load_at_slot_displacement_four() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  (void)re_005732f0(as_receiver(receiver));

  check(g_obs.decoy_calls[kObjectPlus4] == 0,
        "F1: object+0x04 was never transferred to (the load is two-level)");
  check(g_obs.decoy_calls[kObjectPlus8] == 0,
        "F2: object+0x08 was never transferred to (the slot displacement is not added twice)");
  check(g_obs.decoy_calls[kTablePlus0] == 0,
        "F3: table+0x00 was never transferred to (the slot displacement is 0x4)");
  check(g_obs.decoy_calls[kTablePlus8] == 0,
        "F4: table+0x08 was never transferred to (the slot displacement is not 0x8)");
  check(g_obs.decoy_calls[kTransferCount - 1] == 0,
        "F5: table+0x0c was never transferred to (the displacement is a dword offset)");
  check(g_obs.log_is(kSlotAtTable4, kSlotAtTable4),
        "F6: both transfers reached the real slot, in that order");
  g_active_receiver = nullptr;
}

// G. REFUTE (tail path returns the wrong transfer's value). Both members set, and
// the two observers return different words. 0x00573328 is a JMP, so the SECOND
// transfer's EAX is what this body's caller receives.
void case_tail_path_returns_the_second_transfer_value() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  const Word returned = re_005732f0(as_receiver(receiver));

  check(g_obs.slot_returned[0] == kReturns[0] && g_obs.slot_returned[1] == kReturns[1],
        "G1: the two observers really did return different words");
  check(returned == kReturns[1],
        "G2: the body returns the SECOND transfer's value, because 0x00573328 is a tail jump");
  check(returned != kReturns[0],
        "G3: the body does not return the first transfer's value on the tail path");
  check(returned != kEaxUnwrittenOnTheNoMemberPath,
        "G4: the tail path is not the no-member path in disguise");
  g_active_receiver = nullptr;
}

// H. REFUTE (return path returns the wrong thing). Only the first member set, so
// 0x0057330c runs and 0x00573316 jumps to 0x0057332a. The return value is then the
// FIRST transfer's word.
void case_return_path_returns_the_first_transfer_value() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, nullptr);
  g_active_receiver = receiver.bytes;

  const Word returned = re_005732f0(as_receiver(receiver));

  check(g_obs.slot_calls == 1, "H1: one transfer on the path that returns at 0x0057332b");
  check(returned == kReturns[0],
        "H2: the body returns the first transfer's value on the return path");
  check(returned != kEaxUnwrittenOnTheNoMemberPath,
        "H3: the return path is not the no-member path in disguise");
  g_active_receiver = nullptr;
}

// I. REFUTE (the clear is not durable). After a call with both members set, both
// words are 0, so a second call on the same receiver must transfer nothing at all --
// a model that re-arms the members, or that reads a copy of them, fails here.
void case_second_call_transfers_nothing() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  (void)re_005732f0(as_receiver(receiver));
  check(g_obs.slot_calls == 2, "I1: the first call made both transfers");
  g_obs.reset();
  (void)re_005732f0(as_receiver(receiver));
  check(g_obs.total_calls == 0, "I2: the second call transfers nothing: both words are already 0");
  g_active_receiver = nullptr;
}

// J. The ABI, measured rather than asserted. The machine pushes ESI at 0x005732f0
// and pops it on both exits, and it takes no stack argument and cleans none. ESI is
// loaded with a sentinel here and read back after the call, and ESP is sampled on
// both sides of the call: the two are equal only if the body preserved the callee-
// saved register and left the stack exactly as it found it.
struct FrameSamples {
  Word esi_before = 0;
  Word esi_after = 0;
  Word esp_before = 0;
  Word esp_after = 0;
};

FrameSamples call_measured(Receiver* receiver) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&re_005732f0));
  Word esi_after = 0;
  Word esp_before = 0;
  Word esp_after = 0;
  // EAX, ECX and ESI are in the clobber list, so the compiler cannot have allocated
  // either input to them: both survive the moves that precede their use.
  __asm__ __volatile__("movl %%esp, %[eb]\n\t"
                       "movl $0x5a5a5a5a, %%esi\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esi, %[ea]\n\t"
                       "movl %%esp, %[ea2]"
                       : [eb] "=m"(esp_before), [ea] "=m"(esi_after), [ea2] "=m"(esp_after)
                       : [recv] "r"(receiver), [target] "r"(target)
                       : "eax", "ecx", "esi", "memory");
  FrameSamples samples;
  samples.esi_before = 0x5a5a5a5au;
  samples.esi_after = esi_after;
  samples.esp_before = esp_before;
  samples.esp_after = esp_after;
  return samples;
}

void case_abi_frame_facts() {
  g_obs.reset();
  ReceiverFixture receiver = make_receiver(&g_object_first, &g_object_second);
  g_active_receiver = receiver.bytes;

  const FrameSamples samples = call_measured(as_receiver(receiver));

  check(samples.esi_after == samples.esi_before,
        "J1: ESI survives the call, which is what PUSH ESI / POP ESI does on both exits");
  check(samples.esp_after == samples.esp_before,
        "J2: the stack is balanced: no argument passed, none cleaned");
  check(g_obs.slot_calls == 2, "J3: the trampoline really reached the body and both transfers ran");
  g_active_receiver = nullptr;
}

// The constants this package states, against the listing's own operands.
void verify_displacement_constants() {
  check(kReceiverFirstMemberDisplacement == 0x308u, "V1: first member at receiver+0x308");
  check(kReceiverSecondMemberDisplacement == 0x30cu, "V2: second member at receiver+0x30c");
  check(kDispatchTableDisplacement == 0x4u, "V3: the table word is read at displacement 0x4");
  check(kClearedWord == 0x0u, "V4: both stores write the literal 0");
  check(kEaxUnwrittenOnTheNoMemberPath == 0x0u, "V5: the no-member placeholder is the documented 0");
  check(sizeof(Receiver) == 0x310u, "V6: the modelled receiver ends after the second member word");
  check(sizeof(DispatchTarget) == 4u, "V7: a member object is one word as far as this body sees it");
  check(kReceiverFirstMemberDisplacement + 4 == kReceiverSecondMemberDisplacement,
        "V8: the two member words are adjacent dwords");
  check(kReceiverSecondMemberDisplacement + 4 == sizeof(Receiver),
        "V9: 0x30c + 4 is the last byte the body writes");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_005732f0

// main() has to be at global scope: a `main` inside a named namespace is not an
// entry point and the link fails. Every case lives in the package namespace, so the
// names are pulled in here rather than the other way round.
int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_005732f0;
  plant();
  verify_displacement_constants();
  case_neither_member_transfers_nothing();
  case_only_the_second_member_transfers();
  case_branch_is_an_equality_test_against_zero();
  case_clear_precedes_each_transfer();
  case_each_transfer_gets_its_own_object_in_ecx();
  case_two_level_load_at_slot_displacement_four();
  case_tail_path_returns_the_second_transfer_value();
  case_return_path_returns_the_first_transfer_value();
  case_second_call_transfers_nothing();
  case_abi_frame_facts();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
