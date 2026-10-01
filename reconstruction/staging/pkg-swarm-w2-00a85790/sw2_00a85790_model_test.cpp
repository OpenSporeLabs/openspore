// PKG-SWARM-W2-00A85790 -- VA 0x00a85790
// Falsification model test for re_00a85790.
//
// WHAT THIS TEST IS FOR. It is not a walk-through of the reconstruction. Every
// direct and indirect callee is defined here as an OBSERVER that records, for
// every transfer the reconstruction makes: which callee it was, the receiver it
// was handed, its arguments and their order, the state of the receiver's memory
// and of the model's EDI register AT THE MOMENT OF THE CALL, and what it
// returned. The test then drives inputs chosen to make each high-risk reading
// disagree with the listing, and asserts the reconstruction takes the listing's
// side.
//
// The decoy families, one per hypothesis that a reconstruction could get wrong:
//
//   D1  wrong constant / off-by-one displacement -- every displacement the body
//       uses has a decoy of the same shape one step away, in the receiver, in the
//       source object and in the listener's table.
//   D2  wrong branch polarity -- every one of the nine conditional branches is
//       driven in both states, and each one has a case that can only pass with
//       the listing's polarity.
//   D3  signed vs unsigned at 0x00a85824 -- a word with bit 31 set and no other
//       interesting property is fed in; a signed test skips, an unsigned one
//       calls. The all-ones sentinel the body itself stores is that word.
//   D4  wrong pointer level -- the flag word, the halfword argument and the
//       listener's table are each decoyed at the WRONG depth: the receiver's own
//       +0x08/+0xa8, the source's neighbouring displacements, the source's own
//       leading word, and a full second table sitting at the listener's +0x14,
//       +0x18 and +0x1c (i.e. exactly where a ONE-level dispatch would read).
//   D5  wrong receiver offset -- decoy words at receiver+0x08, +0x60, +0x64 and
//       +0x6c, plus a byte-for-byte memory diff that fails on ANY write outside
//       the two displacements the listing writes.
//   D6  wrong callee / wrong slot / wrong argument order -- five distinct decoy
//       probes sit in the real table's neighbouring slots and three more sit in
//       the three one-level decoy tables; the observers record their arguments
//       positionally and in order, and a decoy that fires fails the case.
//   D7  wrong write ordering -- the slot-0x14 observer reads receiver+0x68 while
//       it is running, and must still see the value the body had on entry: the
//       sentinel store at 0x00a85831 happens after the call returns.
//   D8  wrong callee-saved register handling -- the slot-0x1c observer scribbles
//       on the model's EDI register, and the test asserts the PUSH EDI / POP EDI
//       pair at 0x00a8580f / 0x00a85817 restored it on the arm that has the pair
//       and did NOT touch it on the arm that has none.
//   D9  wrong dependence on a callee's EAX -- observers return distinct poison
//       values and the observable call sequence is asserted to be identical.
//
// WHAT IS DELIBERATELY NOT ASSERTED, and why:
//
//   * The single ordinary stack word the terminator `RET 0x4` pops. No
//     instruction in the 64 reads it (abi_derived inference A1-IMM: "argument
//     slots derived from the terminal immediate alone; no argument read was
//     observed"), so there is no observable for it. The test drives several
//     values through the prototype's unnamed parameter and asserts that no
//     observable changes, which is the strongest statement the evidence allows.
//   * Whether the three table displacements are VTABLE SLOTS or plain callback
//     words in an object. Both execute the same instructions; the model performs
//     the fetch and the call and the test asserts nothing about which it is.
//   * The return value. The reconstruction is void because the four paths into
//     the single return site leave EAX holding three different unrelated values,
//     so there is nothing to observe. See the header's return-type note.
//   * What 0x00a85460 does. It is defined here as an observer, and this package
//     asserts only the callsite's shape: receiver in ECX, no stack argument.
//   * Any field NAME for any displacement. The machine-derived receiver record
//     for this target is bounds_only, so no name is claimed and none is tested.

#include "sw2_00a85790_types.hpp"

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

namespace {

using openspore::reconstruction::pkg_swarm_w2_00a85790::Receiver;
using openspore::reconstruction::pkg_swarm_w2_00a85790::Word;
using openspore::reconstruction::pkg_swarm_w2_00a85790::edi_register;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kArgumentBufferDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kFlagByteDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kListenerPointerDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kPendingIdentifierDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kSentinelIdentifier;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kSourceFlagWordDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kSourceHalfWordDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::kSourcePointerDisplacement;
using openspore::reconstruction::pkg_swarm_w2_00a85790::re_00a85790;
using openspore::reconstruction::pkg_swarm_w2_00a85790::set_edi_register;

// -- the check harness --------------------------------------------------------

int g_failures = 0;
int g_checks = 0;

void expect(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    ++g_failures;
    std::printf("  FAIL  %s\n", what);
  }
}

void expect_eq_word(Word got, Word want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("  FAIL  %s: got 0x%08lx, want 0x%08lx\n", what,
                static_cast<unsigned long>(got), static_cast<unsigned long>(want));
  }
}

void expect_eq_ptr(const void* got, const void* want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("  FAIL  %s: got %p, want %p\n", what, got, want);
  }
}

// -- memory geometry ----------------------------------------------------------
//
// Each object lives in its own guarded, over-sized buffer so that (a) a decoy can
// sit at a displacement the body never uses and (b) the byte-for-byte diff can
// see a write one byte outside the object. The whole buffer -- guards included --
// is poisoned first, and the diff after each call spans the WHOLE buffer, so a
// write anywhere else in it is a failure.

constexpr std::size_t kGuard = 0x40;
constexpr std::size_t kSpan = 0x200;
constexpr std::size_t kStorage = kGuard + kSpan + kGuard;
constexpr std::uint8_t kPoisonByte = 0xc7;

alignas(16) std::uint8_t g_receiver_buffer[kStorage];
alignas(16) std::uint8_t g_source_buffer[kStorage];
alignas(16) std::uint8_t g_decoy_source_buffer[kStorage];
alignas(16) std::uint8_t g_listener_buffer[kStorage];
alignas(16) std::uint8_t g_real_table_buffer[kStorage];
alignas(16) std::uint8_t g_decoy_table_a_buffer[kStorage];
alignas(16) std::uint8_t g_decoy_table_b_buffer[kStorage];
alignas(16) std::uint8_t g_decoy_table_c_buffer[kStorage];

Receiver* g_receiver = nullptr;
std::uint8_t* g_receiver_bytes = nullptr;
std::uint8_t* g_source = nullptr;
std::uint8_t* g_decoy_source = nullptr;
std::uint8_t* g_listener = nullptr;
std::uint8_t* g_real_table = nullptr;
std::uint8_t* g_decoy_table_a = nullptr;
std::uint8_t* g_decoy_table_b = nullptr;
std::uint8_t* g_decoy_table_c = nullptr;

std::uint8_t* base_of(std::uint8_t* buffer) { return buffer + kGuard; }

void poison(std::uint8_t* buffer) { std::memset(buffer, kPoisonByte, kStorage); }

void put_word(std::uint8_t* at, std::size_t displacement, Word value) {
  std::memcpy(at + displacement, &value, sizeof(value));
}

void put_half(std::uint8_t* at, std::size_t displacement, std::uint16_t value) {
  std::memcpy(at + displacement, &value, sizeof(value));
}

Word get_word(const std::uint8_t* at, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, at + displacement, sizeof(value));
  return value;
}

std::uint16_t get_half(const std::uint8_t* at, std::size_t displacement) {
  std::uint16_t value = 0;
  std::memcpy(&value, at + displacement, sizeof(value));
  return value;
}

// The address of a function, as the 4-byte word the machine's table would hold.
template <typename Fn>
Word address_of(Fn fn) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(reinterpret_cast<void*>(fn)));
}

// -- the observer log ---------------------------------------------------------

struct Event {
  const char* name;
  const void* receiver;
  Word first_argument;
  const void* second_argument;
  Word edi_at_call;
  Word pending_at_call;
  Word returned;
};

std::vector<Event> g_events;
int g_decoy_hits_a = 0;
int g_decoy_hits_b = 0;
int g_decoy_hits_c = 0;
int g_decoy_hits_neighbour_low = 0;
int g_decoy_hits_neighbour_high = 0;
int g_decoy_hits_fill = 0;

// What each observer is asked to do, driven per case.
struct Hooks {
  bool direct_mutates_flags = false;
  Word direct_new_flags = 0;
  bool slot18_mutates_flags = false;
  Word slot18_new_flags = 0;
  bool slot18_sets_edi = false;
  Word slot18_edi_value = 0;
  bool slot1c_sets_edi = false;
  Word slot1c_edi_value = 0;
  Word observer_return = 0x0badc0deu;
};

Hooks g_hooks;

void record(const char* name, const void* receiver, Word first_argument,
            const void* second_argument) {
  Event event;
  event.name = name;
  event.receiver = receiver;
  event.first_argument = first_argument;
  event.second_argument = second_argument;
  event.edi_at_call = edi_register();
  event.pending_at_call = get_word(g_receiver_bytes, kPendingIdentifierDisplacement);
  event.returned = g_hooks.observer_return;
  g_events.push_back(event);
}

}  // namespace

// -- the observers ------------------------------------------------------------
//
// The three indirect callees, in the three shapes the header's typedefs declare.
// Each is cdecl-clean only in the sense that the header already told it what the
// machine requires: slot 0x18 takes no stack argument, slot 0x1c takes two words
// the callee pops, slot 0x14 takes one word the callee pops.

extern "C" Word PKG_SW2_00A85790_THISCALL observe_slot14(void* receiver, Word argument) {
  record("slot14", receiver, argument, nullptr);
  if (g_hooks.slot18_sets_edi) {
    set_edi_register(g_hooks.slot18_edi_value);
  }
  return g_hooks.observer_return;
}

extern "C" Word PKG_SW2_00A85790_THISCALL observe_slot18(void* receiver) {
  record("slot18", receiver, 0u, nullptr);
  if (g_hooks.slot18_mutates_flags) {
    put_word(g_source, kSourceFlagWordDisplacement, g_hooks.slot18_new_flags);
  }
  if (g_hooks.slot18_sets_edi) {
    set_edi_register(g_hooks.slot18_edi_value);
  }
  return g_hooks.observer_return;
}

extern "C" Word PKG_SW2_00A85790_THISCALL observe_slot1c(void* receiver, Word first_argument,
                                                        void* second_argument) {
  record("slot1c", receiver, first_argument, second_argument);
  if (g_hooks.slot1c_sets_edi) {
    set_edi_register(g_hooks.slot1c_edi_value);
  }
  return g_hooks.observer_return;
}

// The decoy probes. All three shapes are cdecl, so a reconstruction that reaches
// one of them with the WRONG argument count -- which is exactly what a wrong
// pointer level or a wrong slot would produce -- cannot corrupt the stack before
// the failure is reported.
extern "C" Word decoy_probe_a(void* receiver, Word first_argument, void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_a;
  return 0;
}

extern "C" Word decoy_probe_b(void* receiver, Word first_argument, void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_b;
  return 0;
}

extern "C" Word decoy_probe_c(void* receiver, Word first_argument, void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_c;
  return 0;
}

extern "C" Word decoy_probe_neighbour_low(void* receiver, Word first_argument,
                                          void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_neighbour_low;
  return 0;
}

extern "C" Word decoy_probe_neighbour_high(void* receiver, Word first_argument,
                                           void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_neighbour_high;
  return 0;
}

extern "C" Word decoy_probe_fill(void* receiver, Word first_argument, void* second_argument) {
  (void)receiver;
  (void)first_argument;
  (void)second_argument;
  ++g_decoy_hits_fill;
  return 0;
}

// -- the one direct callee ----------------------------------------------------
//
// The callsite at 0x00a857cb fixes the receiver and the absence of stack
// arguments, and nothing else. This definition is the observer; it does what the
// case asks and nothing more.

extern "C" void PKG_SW2_00A85790_THISCALL FUN_00a85460(Receiver* receiver) {
  record("direct_00a85460", receiver, 0u, nullptr);
  if (g_hooks.direct_mutates_flags) {
    put_word(g_source, kSourceFlagWordDisplacement, g_hooks.direct_new_flags);
  }
}

namespace {

// -- fixture ------------------------------------------------------------------

std::vector<std::uint8_t> g_receiver_before;

void setup() {
  poison(g_receiver_buffer);
  poison(g_source_buffer);
  poison(g_decoy_source_buffer);
  poison(g_listener_buffer);
  poison(g_real_table_buffer);
  poison(g_decoy_table_a_buffer);
  poison(g_decoy_table_b_buffer);
  poison(g_decoy_table_c_buffer);

  g_receiver_bytes = base_of(g_receiver_buffer);
  g_receiver = reinterpret_cast<Receiver*>(g_receiver_bytes);
  g_source = base_of(g_source_buffer);
  g_decoy_source = base_of(g_decoy_source_buffer);
  g_listener = base_of(g_listener_buffer);
  g_real_table = base_of(g_real_table_buffer);
  g_decoy_table_a = base_of(g_decoy_table_a_buffer);
  g_decoy_table_b = base_of(g_decoy_table_b_buffer);
  g_decoy_table_c = base_of(g_decoy_table_c_buffer);

  // -- the receiver, decoyed at every neighbouring displacement (D1, D5) ------
  put_word(g_receiver_bytes, 0x08, address_of(decoy_probe_a));
  put_word(g_receiver_bytes, 0x0c, address_of(g_source));
  put_word(g_receiver_bytes, 0x10, address_of(g_listener));
  g_receiver_bytes[kFlagByteDisplacement] = 0;
  put_word(g_receiver_bytes, 0x60, 0x33333333u);
  put_word(g_receiver_bytes, 0x64, 0x44444444u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, kSentinelIdentifier);
  put_word(g_receiver_bytes, 0x6cu, 0x55555555u);
  // A decoy halfword at the RECEIVER's own +0xa8. 0x00a857f8 reads +0xa8 out of
  // the SOURCE object, two levels down, so this word must never be the argument.
  put_half(g_receiver_bytes, 0xa8, 0xbeef);

  // -- the source object, decoyed at its own neighbours (D1, D4) --------------
  // The leading word is a decoy TABLE, so a reconstruction that read the LISTENER
  // out of the receiver at 0x0c instead of 0x10 would find a table base here and
  // dispatch every one of its four transfers into decoy_table_a.
  put_word(g_source, 0x00, address_of(g_decoy_table_a));
  put_word(g_source, 0x04, 0xccccccccu);
  put_word(g_source, kSourceFlagWordDisplacement, 0u);
  put_half(g_source, kSourceHalfWordDisplacement, 0x0000u);
  put_half(g_source, 0xa4, 0x1111);
  put_half(g_source, 0xac, 0x3333);

  // -- the decoy source, for a reconstruction that read receiver+0x08 (D4) ----
  put_word(g_decoy_source, kSourceFlagWordDisplacement, 0xffffffffu);
  put_half(g_decoy_source, kSourceHalfWordDisplacement, 0x2222);

  // -- the listener, decoyed at every step of the three-step chase (D4, D6) ---
  //
  // +0x00 is the TABLE LEAD: the word the body reads at 0x00a857e1 / 0x00a85808
  // / 0x00a85829. +0x04 is a decoy table base, so a reconstruction that read the
  // lead one dword too high dispatches into decoy_table_b. +0x14, +0x18 and +0x1c
  // hold the decoy probe FUNCTIONS themselves -- not decoy tables -- because the
  // shallowest wrong reading of this body is `*(L + 0x18)` instead of
  // `*(*L + 0x18)`, and that reading fetches the target word directly. Planting a
  // probe there makes that mistake a recorded failure rather than a jump into
  // data.
  put_word(g_listener, 0x00, address_of(g_real_table));
  put_word(g_listener, 0x04, address_of(g_decoy_table_b));
  put_word(g_listener, 0x14, address_of(decoy_probe_a));
  put_word(g_listener, 0x18, address_of(decoy_probe_b));
  put_word(g_listener, 0x1c, address_of(decoy_probe_c));

  // -- the real table: the three slots the listing reads, decoys either side ---
  for (std::size_t index = 0; index < 12; ++index) {
    put_word(g_real_table, index * 4u, address_of(decoy_probe_fill));
  }
  put_word(g_real_table, 0x10, address_of(decoy_probe_neighbour_low));
  put_word(g_real_table, 0x14, address_of(observe_slot14));
  put_word(g_real_table, 0x18, address_of(observe_slot18));
  put_word(g_real_table, 0x1c, address_of(observe_slot1c));
  put_word(g_real_table, 0x20, address_of(decoy_probe_neighbour_high));

  // -- the three one-level decoy tables, filled with their own probe ----------
  for (std::size_t index = 0; index < 12; ++index) {
    put_word(g_decoy_table_a, index * 4u, address_of(decoy_probe_a));
    put_word(g_decoy_table_b, index * 4u, address_of(decoy_probe_b));
    put_word(g_decoy_table_c, index * 4u, address_of(decoy_probe_c));
  }

  g_events.clear();
  g_decoy_hits_a = 0;
  g_decoy_hits_b = 0;
  g_decoy_hits_c = 0;
  g_decoy_hits_neighbour_low = 0;
  g_decoy_hits_neighbour_high = 0;
  g_decoy_hits_fill = 0;
  g_hooks = Hooks();
  set_edi_register(0);
  g_receiver_before.assign(g_receiver_buffer, g_receiver_buffer + kStorage);
}

void arm() { g_receiver_bytes[kFlagByteDisplacement] = 1; }

void set_flags(Word flags) { put_word(g_source, kSourceFlagWordDisplacement, flags); }

void set_source_half(std::uint16_t value) {
  put_half(g_source, kSourceHalfWordDisplacement, value);
}

// The bit the listing shifts by, restated here as the flag word's own bit.
constexpr Word kBit0 = 0x00000001u;
constexpr Word kBit3 = 0x00000008u;
constexpr Word kBit5 = 0x00000020u;
constexpr Word kBit6 = 0x00000040u;
constexpr Word kSignBitOnly = 0x80000000u;

// -- the memory diff (D5) -----------------------------------------------------
//
// Every byte of the receiver's whole guarded buffer, compared before and after.
// The reconstruction is allowed to write exactly two things: the single flag byte
// at +0x14, and the four bytes of the pending-identifier word at +0x68. Anything
// else -- a neighbouring word, a decoy, a guard byte -- is a failure.

void check_writes(const std::vector<std::size_t>& allowed, const char* what) {
  std::size_t changed_count = 0;
  std::size_t unexpected = 0;
  for (std::size_t index = 0; index < kStorage; ++index) {
    if (g_receiver_buffer[index] == g_receiver_before[index]) {
      continue;
    }
    ++changed_count;
    // The diff spans the WHOLE buffer, guards included, so a write outside the
    // object is seen; the comparison is against receiver-relative offsets.
    const std::size_t relative = (index >= kGuard) ? (index - kGuard) : index;
    const bool ok = std::find(allowed.begin(), allowed.end(), relative) != allowed.end();
    if (!ok) {
      ++unexpected;
      if (unexpected <= 4) {
        std::printf("  FAIL  %s: unexpected write at buffer offset 0x%zx (receiver offset "
                    "0x%zx)\n",
                    what, index, relative);
      }
    }
  }
  ++g_checks;
  if (unexpected != 0) {
    ++g_failures;
    std::printf("  FAIL  %s: %zu unexpected write(s)\n", what, unexpected);
  }
  ++g_checks;
  if (changed_count == 0 && !allowed.empty()) {
    ++g_failures;
    std::printf("  FAIL  %s: expected a write and saw none\n", what);
  }
}

std::vector<std::size_t> receiver_offsets() {
  return {kFlagByteDisplacement, kPendingIdentifierDisplacement, kPendingIdentifierDisplacement + 1,
          kPendingIdentifierDisplacement + 2, kPendingIdentifierDisplacement + 3};
}

void check_no_decoy_fired(const char* what) {
  ++g_checks;
  const int total = g_decoy_hits_a + g_decoy_hits_b + g_decoy_hits_c +
                    g_decoy_hits_neighbour_low + g_decoy_hits_neighbour_high + g_decoy_hits_fill;
  if (total != 0) {
    ++g_failures;
    std::printf("  FAIL  %s: %d decoy probe call(s) (a=%d b=%d c=%d low=%d high=%d fill=%d)\n",
                what, total, g_decoy_hits_a, g_decoy_hits_b, g_decoy_hits_c,
                g_decoy_hits_neighbour_low, g_decoy_hits_neighbour_high, g_decoy_hits_fill);
  }
}

// Every entry into the reconstruction goes through here, so the memory diff is
// always taken against the state the CASE set up rather than against the state
// `setup()` left. A case that mutates its own inputs after setup() would
// otherwise see its own writes reported as the reconstruction's.
void invoke(Word stack_word) {
  g_receiver_before.assign(g_receiver_buffer, g_receiver_buffer + kStorage);
  re_00a85790(g_receiver, stack_word);
}

std::vector<std::string> names() {
  std::vector<std::string> result;
  for (std::size_t index = 0; index < g_events.size(); ++index) {
    result.push_back(g_events[index].name);
  }
  return result;
}

void check_sequence(const char* const* expected, std::size_t count, const char* what) {
  ++g_checks;
  if (g_events.size() != count) {
    ++g_failures;
    std::printf("  FAIL  %s: %zu call(s) observed, %zu expected\n", what, g_events.size(), count);
    for (std::size_t index = 0; index < g_events.size(); ++index) {
      std::printf("          [%zu] %s\n", index, g_events[index].name);
    }
    return;
  }
  for (std::size_t index = 0; index < count; ++index) {
    ++g_checks;
    if (g_events[index].name != expected[index]) {
      ++g_failures;
      std::printf("  FAIL  %s: call %zu was %s, expected %s\n", what, index,
                  g_events[index].name, expected[index]);
    }
  }
}

const Event* find_event(const char* name) {
  for (std::size_t index = 0; index < g_events.size(); ++index) {
    if (g_events[index].name == name) {
      return &g_events[index];
    }
  }
  return nullptr;
}

}  // namespace

// =============================================================================
// The cases. Each one is a claim about the listing that a wrong reconstruction
// would fail. `run` labels them.
// =============================================================================

namespace {

void case_01_disarmed_object_is_a_total_no_op() {
  // 00a85793 CMP byte ptr [ESI + 0x14],0x0 / 00a85797 JZ 0x00a85838
  //
  // The flag byte is CLEAR. The whole body must be skipped: no store, no call,
  // and in particular receiver+0x68 must NOT be consumed, because 0x00a85838 is
  // the epilogue and not the 0x00a8581f continuation. A reconstruction that put
  // the pending-identifier half outside the guard would fire all four calls here.
  setup();
  g_receiver_bytes[kFlagByteDisplacement] = 0;
  set_flags(kBit3 | kBit5);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 7u);

  set_edi_register(0x11112222u);
  invoke(0u);

  check_sequence(nullptr, 0u, "a disarmed object makes no call");
  check_no_decoy_fired("a disarmed object");
  check_writes({}, "a disarmed object writes nothing");
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), 7u,
                 "a disarmed object leaves the pending identifier alone");
  expect_eq_word(edi_register(), 0x11112222u, "a disarmed object leaves EDI alone");
}

void case_02_armed_object_clears_its_own_arm() {
  // 00a857a1 MOV byte ptr [ESI + 0x14],0x0
  //
  // The store happens on EVERY armed path, including the one that then returns
  // because the listener is null. If the store were below the JZ the function
  // would stay armed and re-notify on every call.
  setup();
  arm();
  put_word(g_receiver_bytes, kListenerPointerDisplacement, 0u);

  invoke(0u);

  check_sequence(nullptr, 0u, "a null listener makes no call");
  check_writes({kFlagByteDisplacement}, "a null listener clears the arm and nothing else");
  expect_eq_word(g_receiver_bytes[kFlagByteDisplacement], 0u, "the arm byte is cleared");
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), kSentinelIdentifier,
                 "a null listener never reaches the pending-identifier half");
}

void case_03_null_listener_never_dereferences_it() {
  // 00a857e1, 0x00a85808 and 0x00a85829 each read THROUGH the word at
  // receiver+0x10 with no check of their own. 0x00a8579d is the only null check
  // in the body. With the word null, none of the three may execute -- proven here
  // by the absence of any observer and by the decoy tables staying untouched.
  setup();
  arm();
  put_word(g_receiver_bytes, kListenerPointerDisplacement, 0u);
  set_flags(kBit0 | kBit3 | kBit5 | kBit6);
  // Non-negative on purpose: 0x00a8581f is past the guard's block, so a
  // reconstruction without the null check would make a FIFTH transfer here, the
  // one-argument slot at displacement 0x14, and not just the three inside the
  // block. The sentinel is the word the body itself stores at 0x00a85831, so
  // leaving it in place also shows the pending half was not reached.
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 5u);

  invoke(0u);

  check_sequence(nullptr, 0u, "a null listener suppresses all four calls");
  check_no_decoy_fired("a null listener");
  check_writes({kFlagByteDisplacement}, "a null listener writes only the arm byte");
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), 5u,
                 "a null listener leaves a non-negative pending identifier unconsumed");
}

void case_04_gate_is_an_or_of_bit3_and_bit5() {
  // 00a857b9 JNZ (bit 3) and 00a857c3 JZ (bit 5), both into/out of the block.
  //
  // Four inputs, one per combination of the two bits. A reconstruction that
  // required BOTH, or that tested them in the wrong order, or that inverted
  // either, gets a different answer on at least one of these four.
  // Three separate questions, and they have three separate answers: the BLOCK
  // is gated on (bit 3 OR bit 5); inside it the no-argument slot is gated on bit 3
  // ALONE and the two-argument slot on bit 5 ALONE; and the direct call needs
  // bit 0 as well as the block. A reconstruction that made the two inner gates
  // follow the block's OR, or that tested bit 5 for the no-argument slot, is wrong
  // on two of these six rows.
  struct Row {
    Word flags;
    bool expect_block;
    bool expect_slot18;
    bool expect_slot1c;
    bool expect_direct;
    const char* label;
  };
  const Row rows[] = {
      {0u, false, false, false, false, "neither bit set"},
      {kBit3, true, true, false, false, "bit 3 only"},
      {kBit5, true, false, true, false, "bit 5 only"},
      {kBit0, false, false, false, false, "bit 0 alone does not open the block"},
      {kBit3 | kBit0, true, true, false, true, "bit 3 plus bit 0"},
      {kBit5 | kBit0, true, false, true, true, "bit 5 plus bit 0"},
      {kBit3 | kBit5, true, true, true, false, "both bits set"},
      {kBit3 | kBit5 | kBit0, true, true, true, true, "both bits plus bit 0"},
  };
  for (std::size_t index = 0; index < sizeof(rows) / sizeof(rows[0]); ++index) {
    setup();
    arm();
    set_flags(rows[index].flags);
    invoke(0u);
    // The pending identifier is the sentinel, i.e. negative, so the 0x00a8581f
    // half does nothing and the only transfers possible are inside the block.
    const bool saw_block = (find_event("slot18") != nullptr) || (find_event("slot1c") != nullptr) ||
                           (find_event("direct_00a85460") != nullptr);
    const bool saw_slot18 = find_event("slot18") != nullptr;
    const bool saw_slot1c = find_event("slot1c") != nullptr;
    const bool saw_direct = find_event("direct_00a85460") != nullptr;
    struct Claim {
      const char* what;
      bool got;
      bool want;
    };
    const Claim claims[] = {
        {"the notification block is entered", saw_block, rows[index].expect_block},
        {"the no-argument slot runs", saw_slot18, rows[index].expect_slot18},
        {"the two-argument slot runs", saw_slot1c, rows[index].expect_slot1c},
        {"the direct call runs", saw_direct, rows[index].expect_direct},
    };
    for (std::size_t claim_index = 0; claim_index < 4; ++claim_index) {
      ++g_checks;
      if (claims[claim_index].got != claims[claim_index].want) {
        ++g_failures;
        std::printf("  FAIL  gate (%s): %s ran=%d, expected %d\n", rows[index].label,
                    claims[claim_index].what, static_cast<int>(claims[claim_index].got),
                    static_cast<int>(claims[claim_index].want));
      }
    }
  }
}

void case_05_bit0_alone_gates_the_direct_call() {
  // 00a857c5 TEST AL,0x1 / 00a857c7 JZ 0x00a857d0
  //
  // The direct call is INSIDE the block but gated on bit 0 ALONE. So (bit 3, no
  // bit 0) calls slot18 and not the direct callee, and (bit 0 alone, no bit 3 and
  // no bit 5) makes no call at all -- because bit 0 is not one of the two bits the
  // outer gate tests. Both of those catch a reconstruction that tested the wrong
  // bit or hoisted the call out of the block.
  setup();
  arm();
  set_flags(kBit3);
  const char* const only_no_argument[] = {"slot18"};
  invoke(0u);
  check_sequence(only_no_argument, 1u, "bit 3 without bit 5 calls only the no-argument slot");
  const Event* const slot18 = find_event("slot18");
  expect(slot18 != nullptr, "bit 3 without bit 0 still calls the no-argument slot");
  expect(find_event("direct_00a85460") == nullptr, "bit 3 without bit 0 skips the direct call");

  setup();
  arm();
  set_flags(kBit0);
  invoke(0u);
  check_sequence(nullptr, 0u, "bit 0 alone does not enter the block");
  expect(find_event("direct_00a85460") == nullptr, "bit 0 alone does not reach the direct call");
}

void case_06_flag_word_is_reloaded_after_the_direct_call() {
  // 00a857d0 MOV EAX,[ESI + 0xc] / 00a857d3 MOV ECX,[EAX + 0x8]
  //
  // Both halves of the chase are redone after the direct call, so a direct callee
  // that WRITES the flag word changes what the next two tests see.
  //
  // The input has bit 3 CLEAR and bit 5 SET. Bit 5 is what opens the notification
  // block, which is what makes the bit-0-gated direct call reachable at all --
  // the call is inside the block, so a word carrying bit 0 alone never reaches it
  // (case_05 proves that). With bit 3 clear, the no-argument slot would stay shut
  // if the value were carried across the call; the callee sets bit 3 and the
  // reloaded word must open it. A reconstruction that kept the first read fires
  // no slot at all here, and the third reload then sees bit 5 clear, so the
  // two-argument slot stays shut -- which is a second, independent observation
  // that all three reads exist and are in that order.
  setup();
  arm();
  set_flags(kBit0 | kBit5);
  g_hooks.direct_mutates_flags = true;
  g_hooks.direct_new_flags = kBit3;

  const char* const expected[] = {"direct_00a85460", "slot18"};
  invoke(0u);

  check_sequence(expected, 2u, "the reloaded word decides the no-argument slot");
  expect(find_event("slot1c") == nullptr,
         "the third reload sees the mutated word too, so bit 5 is clear and the "
         "two-argument slot stays shut");
  check_no_decoy_fired("a mutating direct callee");
}

void case_07_flag_word_is_reloaded_again_after_slot18() {
  // 00a857e8 MOV EAX,[ESI + 0xc] / 00a857eb MOV ECX,[EAX + 0x8]
  //
  // The THIRD read. The input has bit 3 set and bit 5 clear, so the two-argument
  // slot would stay shut if the value were carried; the no-argument observer sets
  // bit 5 on its way out and the two-argument slot must then fire. This is the
  // only case in the suite where a callee's effect on memory, rather than its
  // EAX, is what the next test observes -- which is precisely what the listing
  // says the reloads are for.
  setup();
  arm();
  set_flags(kBit3);
  g_hooks.slot18_mutates_flags = true;
  g_hooks.slot18_new_flags = kBit5 | kBit6;

  invoke(0u);

  const Event* const slot1c = find_event("slot1c");
  expect(slot1c != nullptr, "the reloaded bit 5 opens the two-argument slot");
  check_no_decoy_fired("a mutating no-argument observer");
}

void case_08_the_two_argument_argument_pair() {
  // 00a8580a MOV EDX,dword ptr [EDX + 0x1c] / 00a8580d JZ 0x00a8581a
  // 00a85813 PUSH EDI / 00a85814 PUSH EAX   (bit 6 set)
  // 00a8581a PUSH 0x0 / 00a8581c PUSH EAX   (bit 6 clear)
  //
  // Two arms, one bit apart, differing ONLY in the second argument, and the
  // pushes are right-to-left so the halfword is argument 1 in both. A
  // reconstruction that swapped the argument order, or that passed the receiver
  // interior pointer on the wrong arm, or that passed the slot address as
  // argument 1, fails one of these two.
  setup();
  arm();
  set_flags(kBit5 | kBit6);
  set_source_half(0x0000abcd);
  invoke(0u);
  {
    const Event* const call = find_event("slot1c");
    expect(call != nullptr, "bit 5 with bit 6 calls the two-argument slot");
    if (call != nullptr) {
      expect_eq_word(call->first_argument, 0x0000abcdu,
                     "argument 1 is the zero-extended halfword");
      expect_eq_ptr(call->second_argument,
                    reinterpret_cast<const std::uint8_t*>(g_receiver) + kArgumentBufferDisplacement,
                    "argument 2 is the receiver interior pointer at +0x28");
    }
  }

  setup();
  arm();
  set_flags(kBit5);
  set_source_half(0x0000abcd);
  invoke(0u);
  {
    const Event* const call = find_event("slot1c");
    expect(call != nullptr, "bit 5 without bit 6 still calls the two-argument slot");
    if (call != nullptr) {
      expect_eq_word(call->first_argument, 0x0000abcdu, "argument 1 is the halfword either way");
      expect_eq_ptr(call->second_argument, nullptr, "a clear bit 6 pushes a real null word");
    }
  }
}

void case_09_the_halfword_is_read_from_the_source_zero_extended() {
  // 00a857f8 MOVZX EAX,word ptr [EAX + 0xa8]
  //
  // MOVZX, so the upper 16 bits of the memory operand are DISCARDED, and the
  // operand is 0xa8 into the SOURCE object -- two levels below the receiver --
  // not 0xa8 into the receiver. The input has 0x1234 in the high half so a
  // 32-bit read would pass 0x1234abcd, and the receiver's own +0xa8 holds 0xbeef
  // so a receiver-relative read would pass 0xbeef. Only 0xabcd is right.
  setup();
  arm();
  set_flags(kBit5 | kBit6);
  // The full DWORD at the source's +0xa8 is 0x1234abcd. The listing's operand is
  // a WORD at that address, so the machine's answer is the low half only.
  put_word(g_source, kSourceHalfWordDisplacement, 0x1234abcdu);
  invoke(0u);
  {
    const Event* const call = find_event("slot1c");
    expect(call != nullptr, "the halfword argument is produced");
    if (call != nullptr) {
      expect_eq_word(call->first_argument, 0x0000abcdu,
                     "MOVZX zero-extends: the high half of the memory operand is dropped");
    }
  }
  // And neither neighbouring halfword is the answer.
  expect_eq_word(get_half(g_source, 0xa4), 0x1111,
                 "the source's lower neighbouring halfword is never read");
  expect_eq_word(get_half(g_source, 0xac), 0x3333,
                 "the source's upper neighbouring halfword is never read");
}

void case_10_dispatch_is_two_levels_deep() {
  // 00a857de/0x00a857e1/0x00a857e3, 0x00a85805/0x00a85808/0x00a8580a and
  // 0x00a85826/0x00a85829/0x00a8582c are each TWO reads: the word at
  // receiver+0x10 is an address, and the word THERE is a table.
  //
  // The chase is THREE loads deep from the receiver's own word: L = *(self+0x10),
  // T = *L, target = T[disp]. Three separate wrong readings are planted:
  //
  //   * one dereference short -- the target read at *(L + disp) instead of
  //     *(*L + disp). The listener's own bytes at +0x14, +0x18 and +0x1c hold a
  //     decoy probe, so that mistake CALLS the decoy instead of jumping into a
  //     table.
  //   * the table lead read one dword high -- T taken from L+0x04 instead of L+0x00,
  //     which is the decoy table B.
  //   * the listener read out of the receiver at +0x0c instead of +0x10, which
  //     lands on the source object whose own leading word is the decoy table A.
  //
  // Every one of those fires a decoy probe, and no correct reading touches a
  // decoy at all.
  setup();
  arm();
  set_flags(kBit0 | kBit3 | kBit5 | kBit6);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0u);
  set_source_half(0x4321);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0u);

  const char* const expected[] = {"direct_00a85460", "slot18", "slot1c", "slot14"};
  invoke(0u);

  check_sequence(expected, 4u, "all four transfers happen, in listing order");
  check_no_decoy_fired("the two-level dispatch");

  // Every one of the four was handed the LISTENER as its receiver: ECX is the
  // word read from receiver+0x10 in all three indirect cases and the receiver in
  // the direct one.
  for (std::size_t index = 0; index < g_events.size(); ++index) {
    const void* const want = (index == 0u) ? static_cast<const void*>(g_receiver)
                                           : static_cast<const void*>(g_listener);
    expect_eq_ptr(g_events[index].receiver, want, "the transfer receiver is the listing's object");
  }
  const Event* const one_argument = find_event("slot14");
  const Event* const no_argument = find_event("slot18");
  expect(one_argument != nullptr, "the one-argument slot is reached");
  expect(no_argument != nullptr, "the no-argument slot is reached");
  if (one_argument != nullptr) {
    expect_eq_ptr(one_argument->second_argument, nullptr,
                  "the one-argument slot is handed exactly one argument");
    expect_eq_word(one_argument->first_argument, 0u,
                   "the one-argument slot receives the pending identifier itself");
  }
  if (no_argument != nullptr) {
    expect_eq_ptr(no_argument->second_argument, nullptr,
                  "the no-argument slot is handed no stack argument");
  }
}

void case_11_pending_identifier_is_a_signed_test() {
  // 00a8581f MOV EAX,[ESI + 0x68] / 00a85822 TEST EAX,EAX / 00a85824 JL 0x00a85838
  //
  // JL is SIGNED. A word with bit 31 set and nothing else interesting about it is
  // negative here and large unsigned, and the all-ones sentinel 0x00a85831 itself
  // stores is exactly that word -- so the mechanism the body uses to make itself
  // idempotent DEPENDS on the test being signed. An unsigned reconstruction would
  // call the slot-0x14 callee on the sentinel on every subsequent invocation.
  setup();
  arm();
  set_flags(0u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, kSignBitOnly);
  invoke(0u);
  check_sequence(nullptr, 0u, "a negative pending identifier is skipped");
  check_writes({kFlagByteDisplacement}, "a negative pending identifier is left in place");
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), kSignBitOnly,
                 "the negative word is not consumed");

  setup();
  arm();
  set_flags(0u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0x7fffffffu);
  invoke(0u);
  {
    const Event* const call = find_event("slot14");
    expect(call != nullptr, "the largest positive word is not negative and is dispatched");
    if (call != nullptr) {
      expect_eq_word(call->first_argument, 0x7fffffffu, "the pending word is argument 1");
    }
  }
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), kSentinelIdentifier,
                 "the sentinel is stored after the call");
}

void case_12_the_sentinel_store_happens_after_the_call() {
  // 00a8582b PUSH EAX / 00a8582c MOV EAX,[EDX + 0x14] / 00a8582f CALL EAX
  // 00a85831 MOV dword ptr [ESI + 0x68],0xffffffff
  //
  // The order is observable: the slot-0x14 observer READS receiver+0x68 while it
  // is running and must still see the value the body had on entry. A
  // reconstruction that hoisted the store above the call fails this case. The
  // PUSH-before-MOV order is observable too: the argument is the pending word and
  // not the slot address, which a 0x00a8582c-first reconstruction would pass.
  setup();
  arm();
  set_flags(0u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0x00001234u);
  invoke(0u);
  const Event* const call = find_event("slot14");
  expect(call != nullptr, "a non-negative pending identifier is dispatched");
  if (call != nullptr) {
    expect_eq_word(call->pending_at_call, 0x00001234u,
                   "the callee still sees the pre-call value of receiver+0x68");
    expect_eq_word(call->first_argument, 0x00001234u,
                   "the pushed argument is the pending word, not the slot address");
  }
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), kSentinelIdentifier,
                 "the sentinel is stored once the callee has returned");
  check_writes(receiver_offsets(), "only the arm byte and the pending word are written");
}

void case_13_the_sentinel_makes_the_second_half_idempotent() {
  // The whole point of storing 0xffffffff: on the next call the signed test at
  // 0x00a85824 rejects it. Calling the entry twice must therefore produce the
  // slot-0x14 transfer exactly ONCE.
  setup();
  arm();
  set_flags(0u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 3u);
  invoke(0u);
  expect(get_word(g_receiver_bytes, kPendingIdentifierDisplacement) == kSentinelIdentifier,
         "the first call stores the sentinel");
  const std::size_t first_count = g_events.size();

  set_edi_register(0u);
  invoke(0u);
  ++g_checks;
  if (g_events.size() != first_count) {
    ++g_failures;
    std::printf("  FAIL  idempotence: the second call made %zu extra transfer(s)\n",
                g_events.size() - first_count);
  }
  expect_eq_word(get_word(g_receiver_bytes, kPendingIdentifierDisplacement), kSentinelIdentifier,
                 "the sentinel survives the second call");
}

void case_14_edi_is_preserved_only_where_the_listing_spills_it() {
  // 00a8580f PUSH EDI / 00a85817 POP EDI, on the bit-6-SET arm only.
  // 00a8581a / 00a8581c, the bit-6-CLEAR arm, has no such pair.
  //
  // The observer scribbles on the model's EDI register while it runs. On the arm
  // with the pair, EDI must come back poisoned-to-a-known-value; on the arm
  // without it, EDI must still hold what the observer wrote. A reconstruction that
  // omitted the restore fails the first; one that restored unconditionally fails
  // the second.
  const Word poison_before = 0x0badc0deu;
  const Word poison_during = 0xdeadbeefu;

  setup();
  arm();
  set_flags(kBit5 | kBit6);
  g_hooks.slot1c_sets_edi = true;
  g_hooks.slot1c_edi_value = poison_during;
  set_edi_register(poison_before);
  invoke(0u);
  const Event* const saved = find_event("slot1c");
  expect(saved != nullptr, "the two-argument slot ran with bit 6 set");
  if (saved != nullptr) {
    expect_eq_word(saved->edi_at_call, poison_before,
                   "EDI still holds its entry value when the callee is entered");
  }
  expect_eq_word(edi_register(), poison_before,
                 "POP EDI at 00a85817 restores the register after the call");

  setup();
  arm();
  set_flags(kBit5);
  g_hooks.slot1c_sets_edi = true;
  g_hooks.slot1c_edi_value = poison_during;
  set_edi_register(poison_before);
  invoke(0u);
  expect_eq_word(edi_register(), poison_during,
                 "the arm with no PUSH EDI / POP EDI pair leaves EDI alone");
}

void case_15_no_callee_return_value_reaches_a_decision() {
  // 0x00a857d0, 0x00a857e8 and 0x00a8581f each reload EAX from the receiver, so
  // every callee's return value is discarded. Three observers return three
  // different poison values and the observable transfer sequence must be the same
  // every time. A reconstruction that let a callee's EAX reach a later test would
  // produce a different sequence for at least one of them.
  const Word poisons[] = {0x00000000u, 0x00000001u, 0xffffffffu, 0x0badc0deu};
  std::size_t reference_count = 0;
  std::vector<std::string> reference;
  for (std::size_t index = 0; index < sizeof(poisons) / sizeof(poisons[0]); ++index) {
    setup();
    arm();
    set_flags(kBit0 | kBit3 | kBit5 | kBit6);
    set_source_half(0x00ff);
    g_hooks.observer_return = poisons[index];
    invoke(0u);
    const std::vector<std::string> got = names();
    if (index == 0u) {
      reference = got;
      reference_count = got.size();
    } else {
      ++g_checks;
      if (got.size() != reference_count) {
        ++g_failures;
        std::printf("  FAIL  EAX independence: poison 0x%08lx produced %zu transfers, first "
                    "poison produced %zu\n",
                    static_cast<unsigned long>(poisons[index]), got.size(), reference_count);
      } else {
        for (std::size_t at = 0; at < got.size(); ++at) {
          ++g_checks;
          if (got[at] != reference[at]) {
            ++g_failures;
            std::printf("  FAIL  EAX independence: poison 0x%08lx changed transfer %zu\n",
                        static_cast<unsigned long>(poisons[index]), at);
          }
        }
      }
    }
  }
}

void case_16_the_unread_stack_word_changes_nothing() {
  // The prototype's second parameter is the word `RET 0x4` pops. No instruction
  // in the 64 reads it (A1-IMM: the slot is derived from the terminator alone).
  // Four different values through it must produce byte-identical receiver state
  // and an identical transfer sequence. This is the strongest statement the
  // evidence permits, and it is deliberately a statement about the absence of an
  // observable rather than about a value.
  std::vector<std::uint8_t> reference_state;
  std::size_t reference_count = 0;
  const Word words[] = {0x00000000u, 0x00000001u, 0xdeadbeefu, 0xffffffffu};
  for (std::size_t index = 0; index < sizeof(words) / sizeof(words[0]); ++index) {
    setup();
    arm();
    set_flags(kBit0 | kBit3 | kBit5 | kBit6);
    set_source_half(0x1357);
    put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0x00000009u);
    invoke(words[index]);
    std::vector<std::uint8_t> state(g_receiver_buffer, g_receiver_buffer + kStorage);
    if (index == 0u) {
      reference_state = state;
      reference_count = g_events.size();
    } else {
      ++g_checks;
      if (state != reference_state) {
        ++g_failures;
        std::printf("  FAIL  stack word: 0x%08lx changed the receiver's bytes\n",
                    static_cast<unsigned long>(words[index]));
      }
      ++g_checks;
      if (g_events.size() != reference_count) {
        ++g_failures;
        std::printf("  FAIL  stack word: 0x%08lx changed the transfer count\n",
                    static_cast<unsigned long>(words[index]));
      }
    }
  }
}

void case_17_neighbouring_displacements_are_never_touched() {
  // Every read and write the body makes on the receiver is at 0x0c, 0x10, 0x14,
  // 0x28 (address only) or 0x68. The decoys at receiver+0x08, +0x60, +0x64 and
  // +0x6c, at the receiver's own +0xa8, and in the guard bytes, must all be
  // exactly as the fixture left them.
  setup();
  arm();
  set_flags(kBit0 | kBit3 | kBit5 | kBit6);
  set_source_half(0x2468);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, 0x0000abcdu);
  invoke(0u);

  const Word expected_08 = address_of(decoy_probe_a);
  expect_eq_word(get_word(g_receiver_bytes, 0x08), expected_08, "receiver+0x08 is only read by a decoy");
  expect_eq_word(get_word(g_receiver_bytes, 0x0c), address_of(g_source), "receiver+0x0c is unchanged");
  expect_eq_word(get_word(g_receiver_bytes, 0x10), address_of(g_listener), "receiver+0x10 is unchanged");
  expect_eq_word(get_word(g_receiver_bytes, 0x60), 0x33333333u, "receiver+0x60 is unchanged");
  expect_eq_word(get_word(g_receiver_bytes, 0x64), 0x44444444u, "receiver+0x64 is unchanged");
  expect_eq_word(get_word(g_receiver_bytes, 0x6cu), 0x55555555u, "receiver+0x6c is unchanged");
  expect_eq_word(static_cast<Word>(get_half(g_receiver_bytes, 0xa8)), 0xbeefu,
                 "the receiver's own +0xa8 is never the halfword argument");
  expect_eq_word(get_half(g_source, 0xa4), 0x1111,
                 "the source's lower neighbouring halfword is intact");
  expect_eq_word(get_half(g_source, 0xac), 0x3333,
                 "the source's upper neighbouring halfword is intact");
  expect_eq_word(get_word(g_decoy_source, kSourceFlagWordDisplacement), 0xffffffffu,
                 "the decoy source is never consulted for the flag word");
  check_writes(receiver_offsets(), "the two written displacements are the only two");
}

void case_18_flag_word_is_read_from_the_source_not_the_receiver() {
  // 00a857ab MOV EAX,[ESI + 0xc] then 00a857ae MOV EAX,[EAX + 0x8].
  //
  // receiver+0x08 holds a decoy word and the decoy source object's +0x08 holds
  // all ones. An all-ones flag word would make every gate fire, so a
  // reconstruction that read either decoy would produce the maximum number of
  // transfers. The correct reading produces none, because the real flag word is
  // zero in this case.
  setup();
  arm();
  set_flags(0u);
  put_word(g_receiver_bytes, kPendingIdentifierDisplacement, kSentinelIdentifier);
  invoke(0u);
  check_sequence(nullptr, 0u, "a zero flag word in the SOURCE object makes no call");
  check_no_decoy_fired("the flag-word pointer level");
}

void case_19_repeated_invocation_is_stable() {
  // Nothing in the body accumulates: the arm byte is the only state it writes
  // besides the sentinel, and both are idempotent. Ten armed invocations with a
  // negative pending identifier must produce exactly one transfer per call (the
  // no-argument slot when bit 3 is set) and must not drift.
  setup();
  for (int round = 0; round < 10; ++round) {
    arm();
    set_flags(kBit3);
    g_hooks.slot18_mutates_flags = false;
    invoke(0u);
  }
  expect_eq_word(static_cast<Word>(g_events.size()), 10u,
                 "ten armed invocations made exactly one transfer each");
  expect_eq_word(g_receiver_bytes[kFlagByteDisplacement], 0u, "the arm byte ends clear");
  check_no_decoy_fired("ten invocations");
}

struct Case {
  const char* label;
  void (*run)();
};

}  // namespace

int main() {
  const Case cases[] = {
      {"01 a disarmed object is a total no-op", case_01_disarmed_object_is_a_total_no_op},
      {"02 an armed object clears its own arm", case_02_armed_object_clears_its_own_arm},
      {"03 a null listener is never dereferenced", case_03_null_listener_never_dereferences_it},
      {"04 the gate is an OR of bit 3 and bit 5", case_04_gate_is_an_or_of_bit3_and_bit5},
      {"05 bit 0 alone gates the direct call", case_05_bit0_alone_gates_the_direct_call},
      {"06 the flag word reloads after the direct call",
       case_06_flag_word_is_reloaded_after_the_direct_call},
      {"07 the flag word reloads again after slot 0x18",
       case_07_flag_word_is_reloaded_again_after_slot18},
      {"08 the two-argument slot's argument pair", case_08_the_two_argument_argument_pair},
      {"09 the halfword argument is zero-extended", case_09_the_halfword_is_read_from_the_source_zero_extended},
      {"10 the dispatch is two levels deep", case_10_dispatch_is_two_levels_deep},
      {"11 the pending identifier is a signed test", case_11_pending_identifier_is_a_signed_test},
      {"12 the sentinel store follows the call", case_12_the_sentinel_store_happens_after_the_call},
      {"13 the sentinel makes the half idempotent", case_13_the_sentinel_makes_the_second_half_idempotent},
      {"14 EDI is spilled only on the arm that spills it", case_14_edi_is_preserved_only_where_the_listing_spills_it},
      {"15 no callee return value reaches a decision", case_15_no_callee_return_value_reaches_a_decision},
      {"16 the unread stack word changes nothing", case_16_the_unread_stack_word_changes_nothing},
      {"17 neighbouring displacements are never touched", case_17_neighbouring_displacements_are_never_touched},
      {"18 the flag word comes from the source object", case_18_flag_word_is_read_from_the_source_not_the_receiver},
      {"19 ten invocations do not drift", case_19_repeated_invocation_is_stable},
  };

  std::setvbuf(stdout, nullptr, _IONBF, 0);
  std::printf("PKG-SWARM-W2-00A85790 model test -- trying to BREAK re_00a85790\n");
  for (std::size_t index = 0; index < sizeof(cases) / sizeof(cases[0]); ++index) {
    const int before = g_failures;
    std::printf("[case %s]\n", cases[index].label);
    cases[index].run();
    if (g_failures == before) {
      std::printf("   ok\n");
    }
  }

  std::printf("\n%d check(s), %d failure(s)\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::printf("MODEL TEST FAILED\n");
    return 1;
  }
  std::printf("MODEL TEST PASSED\n");
  return 0;
}
