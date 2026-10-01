// PKG-SWARM-W1-00A85070 -- VA 0x00a85070
// Behavioural model test for FUN_00a85070 @ 0x00a85070.
//
// The body has no direct callee -- both of its transfers are register-indirect
// (0x00a8507c CALL EDX, 0x00a85085 CALL EAX) -- so the observers ARE the slot
// targets. Every word the model can possibly fetch is planted with the address of
// an observer, and every observer logs which slot it was, which receiver it was
// handed, what EAX held when it was entered, and what the receiver's +0x10 slot
// contained at that instant. The test therefore sees every transfer, with which
// argument, in which order, and decides what each callee leaves in EAX.
//
// What is asserted is what the 13-instruction listing fixes and nothing more:
//
//   * two transfers, exactly two, in the order site 1 then site 2;
//   * site 1's receiver is the first argument itself, and site 2's receiver is the
//     word that argument leads with -- one dereference, not two, and not `this`;
//   * site 1's target is read at the dispatch object's +0x20 and site 2's target
//     at the second table's +0x60;
//   * EAX holds *owner at 0x00a8507c (the word 0x00a85077 loaded) and the fetched
//     target at 0x00a85085 (the word 0x00a85082 loaded) -- both sampled INSIDE the
//     observers, i.e. measured rather than assumed;
//   * the one dword written goes to the RECEIVER's +0x10, holds the second call's
//     EAX, and is the value returned; and no other byte of the receiver changes
//     (checked by a full before/after byte comparison, not assumed);
//   * the write happens after both calls return, each observer reading the
//     receiver's +0x10 as it is entered.
//
// The cases marked REFUTE exist to try to BREAK the reconstruction, not to walk
// it. Each names the wrong reconstruction it is aimed at:
//
//   A  the +0x10 store lands on the receiver, not on the dispatch object and not
//      on the dispatch table: the object's +0x20 word and the table's +0x60 word
//      are still the observers after the call;
//   B  wrong slot displacement: the neighbouring slots of BOTH fetches carry decoy
//      observers (0x1c, 0x24, 0x5c, 0x64, 0x68, ...) and none may run;
//   C  wrong pointer level: decoy words sit at the owner's +0x04 and +0x08 and at
//      the dispatch object's +0x04, +0x08, +0x0c, +0x10, +0x14, +0x18 and +0x1c,
//      each pointing at a decoy table that DOES have a live observer at +0x60 and
//      at +0x20, so a model that read one of them would call something rather
//      than crash;
//   D  three-level chase: the second table's +0x00 points at a third table with a
//      live observer at +0x60, for a model that dereferenced one time too often;
//   E  the highest-risk reading in the body -- 0x00a8507e re-reads through the
//      POST-CALL EAX instead of reloading [ECX], so a first callee that writes EAX
//      moves the second dispatch's receiver AND its table base. Driven both ways:
//      the preserving callee must keep the nominal behaviour, and the clobbering
//      callee must make the second dispatch land on the DECOY object and the DECOY
//      table, with the decoy's return value in the receiver's +0x10;
//   F  wrong write ordering: the store is last, after both calls;
//   G  no branch and no filter on the result: the stored/returned word is driven to
//      0, to 0xffffffff, to a code address and to a data word, and the observable
//      outcome must have the same shape every time;
//   H  the second stack word: it exists only because `RET 0xc` pops three words,
//      and running the whole case with a benign word and with a pointer to a
//      poisoned block must produce byte-identical receiver state and an
//      unpoisoned block.
//
// What is NOT asserted, and why:
//
//   * Whether the word at the dispatch object's +0x20 is a VTABLE SLOT or a plain
//     callback word inside an object. 0x00a85079 fetches it and 0x00a8507c calls
//     it with the owner in ECX; whether the dispatch object is the owner's vtable
//     (making this an ordinary virtual call) or a callback holder is a question
//     the three instructions cannot answer, because both readings execute the same
//     bytes. The test pins the ADDRESSES and the RECEIVER, which is all the
//     listing fixes, and says nothing about the classification.
//   * What the two callees DO, beyond the EAX output the body reads. Each
//     observer's memory effects are a test fixture, not a claim; the observers
//     write nothing at all.
//   * That the real first callee preserves EAX. Nothing in this body can show
//     that. Case E drives both behaviours and asserts the model follows the
//     machine in each, which is the whole of what can be claimed here.
//   * Any C++ type, class name or SDK symbol for the owner, the dispatch object or
//     the receiver. No listing in this package names them, so the model spells
//     them as opaque runs and this test never asserts what they are.

#include "sw1_00a85070_types.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <utility>

namespace openspore::reconstruction::pkg_swarm_w1_00a85070 {
namespace {

// Machine displacements, as literals: the two the body fetches a target from and
// the one it stores to. Same values as the header's constants, restated so a
// mutation of either file is caught by the other.
constexpr std::size_t kFirstFetchDisplacement = 0x20u;
constexpr std::size_t kSecondFetchDisplacement = 0x60u;
constexpr std::size_t kResultDisplacement = 0x10u;

// 0xcd is the receiver decoy: the constructor 0x00a853b0 never leaves a byte of
// 0xcd anywhere, and a dword of 0xcdcdcdcd shares no byte with any result the
// observers return, so "the store happened" cannot be confused with "the store was
// a no-op".
constexpr std::uint8_t kReceiverDecoy = 0xcd;
constexpr Word kResultDecoyWord = 0xcdcdcdcdu;

// Every slot the model can possibly fetch, as an identity. The two real ones are
// kSlotFirstSite and kSlotSecondSite; everything else is a decoy planted where a
// wrong displacement, a wrong base or a wrong level would land. One observer per
// identity is what lets a failure say WHICH mistake was made.
enum Slot : int {
  kSlotNone = 0,
  kSlotFirstSite,   // the dispatch object + 0x20    (0x00a85079) -- real site 1
  kSlotSecondSite,  // the second table   + 0x60     (0x00a85082) -- real site 2
  kSlotBase20,      // the decoy table's + 0x20: reached when the FIRST fetch
                    //   picks up one of the decoy words instead of +0x20
  kSlotBase60,      // the decoy table's + 0x60: reached when the SECOND base read
                    //   picks up a decoy word, or when site 1 clobbers EAX
  kSlotDecoyCall,   // the decoy TABLE's + 0x00: reached when a decoy word is
                    //   used as a CALL TARGET, i.e. when the first fetch picked up
                    //   a word that is a table rather than a function
  kSlotTbl5c,       // decoy at the second table + 0x5c (one slot below +0x60)
  kSlotTbl64,       // decoy at + 0x64 (one slot above +0x60)
  kSlotTbl68,       // decoy at + 0x68
  kSlotTbl04,       // decoy at + 0x04
  kSlotTbl10,       // decoy at + 0x10
  kSlotThird60,     // the third table's + 0x60 (reached only by a third level)
  kSlotFill18,      // a FUNCTION pointer planted at the object + 0x18
  kSlotFill1c,      // a FUNCTION pointer planted at the object + 0x1c
  kSlotFill24,      // a FUNCTION pointer planted in the tail, i.e. PAST the 0x24
                    //   object, so a +0x24 or wider first fetch lands on it
  kSlotCount
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void plant(void *base, std::size_t displacement, Word value) {
  *reinterpret_cast<Word *>(reinterpret_cast<std::uintptr_t>(base) + displacement) =
      value;
}

Word read_planted(const void *base, std::size_t displacement) {
  return *reinterpret_cast<const Word *>(
      reinterpret_cast<std::uintptr_t>(base) + displacement);
}

// -- fixtures ----------------------------------------------------------------

// A dispatch object as this body sees it: 0x24 bytes whose only reads are +0x00
// and +0x20, followed by a tail of decoys so that a displacement running past the
// modelled object lands on a live observer instead of on unrelated memory. The
// tail runs to +0x60 so that EVERY plausible near-miss of both 0x20 and 0x60 is
// covered by a live observer rather than by an unwritten zero.
struct SlotFixture {
  SlotObject slot;
  Word tail[16];
};

// A dispatch table: 28 words, so a displacement of 0x6c is still in bounds and a
// near-miss at 0x64 or 0x68 is observable rather than a read past the fixture.
struct TableFixture {
  Word words[28];
};

struct World {
  // The owner, as the body sees it: one word at +0x00, plus decoys at +0x04 and
  // +0x08 that a wrong displacement on 0x00a85077 would pick up.
  Word owner_lead;
  Word owner_04;
  Word owner_08;

  SlotFixture slot;          // the object at owner+0x00 (the "SlotObject")
  SlotFixture wrong_level;   // reached only if EAX is clobbered (case E)
  TableFixture table;        // read at +0x60 for site 2
  TableFixture decoy_table;  // planted at owner+0x04, owner+0x08, slot+0x04 ...
  TableFixture third_table;  // planted at table+0x00, for a third-level chase
  Receiver receiver;
};

// -- observation -------------------------------------------------------------

enum FirstEaxMode { kPreserveEax, kFixedEax };

struct Observation {
  const World *world = nullptr;
  int log[8] = {};
  int log_length = 0;

  int count[kSlotCount] = {};
  void *self[kSlotCount] = {};
  Word eax_in[kSlotCount] = {};
  Word result_seen[kSlotCount] = {};

  FirstEaxMode first_eax_mode = kPreserveEax;
  Word first_eax_fixed = 0;
  Word second_return = 0x0badc0deu;
};

Observation *g_obs = nullptr;

Word decoy_return(Slot which);

// The single place every transfer is observed. `self` is the ECX the call passed,
// eax_register() is the EAX the call site held, and result_seen is the receiver's
// +0x10 read at the moment of the call -- which is how the ORDER of the store is
// measured rather than assumed.
Word observe(Slot which, void *self) {
  Observation &o = *g_obs;
  ++o.count[which];
  o.log[o.log_length] = static_cast<int>(which);
  ++o.log_length;
  o.self[which] = self;
  o.eax_in[which] = eax_register();
  o.result_seen[which] = read_planted(&o.world->receiver, kResultDisplacement);

  if (which == kSlotFirstSite) {
    // The body reads this callee's EAX at 0x00a8507e, so the test gets to decide
    // whether the callee preserved EAX or wrote it.
    return o.first_eax_mode == kPreserveEax ? o.eax_in[which] : o.first_eax_fixed;
  }
  if (which == kSlotSecondSite) {
    return o.second_return;
  }
  return decoy_return(which);
}

// The observers themselves. One per slot identity, so the address planted at a
// word IS the claim about which word was read. They are thiscall because the
// machine's calls are thiscall: one argument in ECX, nothing on the stack.
template <Slot Which>
Word PKG_SW1_00A85070_THISCALL slot_observer(void *self) {
  return observe(Which, self);
}

template <std::size_t... I>
std::array<Word, sizeof...(I)> build_slot_addresses(std::index_sequence<I...>) {
  return {static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(&slot_observer<static_cast<Slot>(I)>))...};
}

const Word *slot_addresses() {
  static const std::array<Word, kSlotCount> table = build_slot_addresses(
      std::make_index_sequence<static_cast<std::size_t>(kSlotCount)>{});
  return table.data();
}

Word slot_address(Slot which) {
  return slot_addresses()[static_cast<int>(which)];
}

// Every decoy returns a VALID address rather than a recognisable word, so a model
// that takes a wrong path keeps dereferencing real memory and dies on an
// ASSERTION that names the mistake, rather than on a segmentation fault. A crash
// is a kill too, but it says nothing about which mistake was made. Each decoy
// gets its own sink object, so the value that reaches the receiver's +0x10 still
// identifies WHICH decoy ran.
SlotFixture g_sinks[kSlotCount];
TableFixture g_sink_tables[kSlotCount];
bool g_sinks_ready = false;

void init_sinks() {
  if (g_sinks_ready) {
    return;
  }
  g_sinks_ready = true;
  for (int i = 0; i < kSlotCount; ++i) {
    plant(&g_sinks[i].slot, 0x00,
          static_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_sink_tables[i])));
    g_sinks[i].slot.field_20 = slot_address(kSlotFill24);
    for (std::size_t j = 0; j < 28; ++j) {
      g_sink_tables[i].words[j] = slot_address(kSlotBase20);
    }
    g_sink_tables[i].words[24] = slot_address(kSlotBase60);
  }
}

Word decoy_return(Slot which) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(
      &g_sinks[static_cast<int>(which)].slot));
}

// -- the planted world -------------------------------------------------------

void setup_nominal(World &w) {
  init_sinks();
  w.receiver.opaque_00.fill(kReceiverDecoy);

  w.owner_lead =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.slot.slot));
  w.owner_04 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.decoy_table));
  w.owner_08 = static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.decoy_table));

  // The dispatch object: the real first site at +0x20, decoys everywhere else the
  // body could have read instead, including one past the modelled object.
  SlotObject &obj = w.slot.slot;
  const Word decoy_table_addr =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.decoy_table));
  // +0x00 is the REAL second dispatch base: 0x00a8507e reads this word and
  // 0x00a85082 indexes +0x60 off it.
  plant(&obj, 0x00, static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.table)));
  // Every other word of the modelled object is planted with a filler chosen for
  // the role a wrong displacement would put it in, so that a mutation is caught by
  // an ASSERTION that names the mistake rather than by a fault:
  //
  //   +0x04 .. +0x14  a pointer to the DECOY TABLE. These are the words a wrong
  //                    second-base read (0x00a8507e) would pick up, and a table
  //                    pointer is readable in that role: the model would then
  //                    fetch the decoy table's live +0x60 slot and be named.
  //   +0x18, +0x1c and every word of the tail (i.e. everything from +0x24 out)
  //                    a FUNCTION pointer. These are the words a wrong FIRST
  //                    target fetch (0x00a85079) would pick up, and a function
  //                    pointer is callable in that role, so the model would call a
  //                    live decoy observer and be named.
  //
  // The decoy table's own two live slots identify which fetch went wrong:
  // kSlotBase20 for the first, kSlotBase60 for the second. A mutation that puts a
  // table pointer where a CALL TARGET belongs (a first fetch that lands on one of
  // the +0x04..+0x14 words) cannot be caught by an assertion at all -- the machine
  // would execute the fixture as code -- so that shape is killed by a fault, and
  // the fact is recorded rather than papered over.
  for (std::size_t off = 0x04; off <= 0x14; off += 0x04) {
    plant(&obj, off, decoy_table_addr);
  }
  plant(&obj, 0x18, slot_address(kSlotFill18));
  plant(&obj, 0x1c, slot_address(kSlotFill1c));
  obj.field_20 = slot_address(kSlotFirstSite);
  for (std::size_t i = 0; i < 16; ++i) {
    w.slot.tail[i] = slot_address(kSlotFill24);
  }

  // The second table: the real site at +0x60, a third table at +0x00 for a
  // one-dereference-too-many model, and decoys either side of the real slot.
  for (std::size_t i = 0; i < 28; ++i) {
    w.table.words[i] = slot_address(kSlotTbl04);
  }
  w.table.words[0] =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.third_table));
  w.table.words[0x04 / 4] = slot_address(kSlotTbl04);
  w.table.words[0x10 / 4] = slot_address(kSlotTbl10);
  w.table.words[0x5c / 4] = slot_address(kSlotTbl5c);
  w.table.words[kSecondFetchDisplacement / 4] = slot_address(kSlotSecondSite);
  w.table.words[0x64 / 4] = slot_address(kSlotTbl64);
  w.table.words[0x68 / 4] = slot_address(kSlotTbl68);

  // The decoy table: reachable only through a wrong base word. Its +0x00 slot is
  // live too, so a decoy word used as a CALL TARGET (a first fetch at a wrong
  // displacement) lands on an observer instead of executing the fixture as code.
  for (std::size_t i = 0; i < 28; ++i) {
    w.decoy_table.words[i] = slot_address(kSlotBase20);
  }
  w.decoy_table.words[0x00 / 4] = slot_address(kSlotDecoyCall);
  w.decoy_table.words[kFirstFetchDisplacement / 4] = slot_address(kSlotBase20);
  w.decoy_table.words[kSecondFetchDisplacement / 4] = slot_address(kSlotBase60);

  // The third table: reachable only through a three-level chase.
  for (std::size_t i = 0; i < 28; ++i) {
    w.third_table.words[i] = slot_address(kSlotBase20);
  }
  w.third_table.words[kSecondFetchDisplacement / 4] = slot_address(kSlotThird60);

  // The object a clobbering first callee hands back instead of the real one.
  plant(&w.wrong_level.slot, 0x00, decoy_table_addr);
  w.wrong_level.slot.field_20 = slot_address(kSlotFill24);
}

// The nominal call, wired to `o`.
Word call_reconstruction(World &w, Observation &o, Word second_stack_word) {
  g_obs = &o;
  o.world = &w;
  const Word result = re_00a85070(
      &w.receiver, reinterpret_cast<OwnerObject *>(&w), second_stack_word);
  g_obs = nullptr;
  return result;
}

void check_no_decoy_ran(const Observation &o) {
  for (int i = 0; i < kSlotCount; ++i) {
    if (i == kSlotFirstSite || i == kSlotSecondSite) {
      continue;
    }
    if (o.count[i] != 0) {
      std::fprintf(stderr, "FAILED: decoy slot %d ran (%d time(s))\n", i,
                   o.count[i]);
      ++g_failures;
    }
  }
}

// Only the dword at the receiver's +0x10 may differ from the snapshot.
void check_only_the_result_word_changed(
    const std::array<std::uint8_t, 0x6c> &before, const Receiver &after,
    Word expected, const char *what) {
  for (std::size_t i = 0; i < before.size(); ++i) {
    const bool in_result = i >= kResultDisplacement &&
                           i < kResultDisplacement + sizeof(Word);
    const std::uint8_t want =
        in_result ? static_cast<std::uint8_t>(
                        (expected >> (8 * (i - kResultDisplacement))) & 0xffu)
                  : before[i];
    if (after.opaque_00[i] != want) {
      std::fprintf(stderr,
                   "FAILED: %s -- receiver byte 0x%02zx is 0x%02x, expected 0x%02x\n",
                   what, i, static_cast<unsigned>(after.opaque_00[i]),
                   static_cast<unsigned>(want));
      ++g_failures;
    }
  }
}

// -- cases -------------------------------------------------------------------

// The walking case: what the 13 instructions fix, asserted directly.
void case_nominal() {
  World w;
  setup_nominal(w);
  const std::array<std::uint8_t, 0x6c> before = w.receiver.opaque_00;
  Observation o;
  o.second_return = 0x00a85070u;  // a code-shaped word, to show no filtering

  const Word result = call_reconstruction(w, o, 0x11112222u);

  check(o.log_length == 2, "exactly two transfers");
  check(o.log_length > 0 && o.log[0] == kSlotFirstSite, "site 1 runs first");
  check(o.log_length > 1 && o.log[1] == kSlotSecondSite, "site 2 runs second");
  check(o.count[kSlotFirstSite] == 1, "site 1 runs exactly once");
  check(o.count[kSlotSecondSite] == 1, "site 2 runs exactly once");

  // 0x00a85073 left the owner in ECX and 0x00a8507c called through EDX: the first
  // receiver is the ARGUMENT, not the object it points at and not `this`.
  check(o.self[kSlotFirstSite] == static_cast<void *>(&w),
        "site 1 receiver is the first argument itself");
  // 0x00a85080 moved EAX (== *owner) into ECX for the second call.
  check(o.self[kSlotSecondSite] == static_cast<void *>(&w.slot.slot),
        "site 2 receiver is the word the owner leads with");

  // The EAX values at the two call sites, sampled inside the observers.
  check(o.eax_in[kSlotFirstSite] ==
            static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.slot.slot)),
        "EAX at 0x00a8507c holds *owner, the word 0x00a85077 loaded");
  check(o.eax_in[kSlotSecondSite] == slot_address(kSlotSecondSite),
        "EAX at 0x00a85085 holds the target 0x00a85082 fetched");

  check_no_decoy_ran(o);

  // The one store, and its value.
  check(read_planted(&w.receiver, kResultDisplacement) == o.second_return,
        "the receiver's +0x10 holds the second call's EAX");
  check(result == o.second_return, "the returned word is the stored word");
  check_only_the_result_word_changed(before, w.receiver, o.second_return,
                                     "only the dword at receiver+0x10 changes");
}

// REFUTE B: wrong slot displacement. Neighbouring slots of both fetches hold live
// decoy observers; a model that read 0x1c or 0x24 instead of 0x20, or 0x5c, 0x64
// or 0x68 instead of 0x60, would call one of them.
void case_slot_displacements() {
  World w;
  setup_nominal(w);
  Observation o;
  call_reconstruction(w, o, 0u);
  check(o.count[kSlotFirstSite] == 1, "the +0x20 fetch hit the real slot");
  check(o.count[kSlotSecondSite] == 1, "the +0x60 fetch hit the real slot");
  // Every neighbouring word of the object, including the ones immediately below
  // and above +0x20, points at the decoy table: a first fetch at 0x1c, 0x24 (or
  // any other near miss) would call the decoy table's +0x20 slot.
  check(o.count[kSlotBase20] == 0, "no near-miss of the +0x20 fetch was called");
  check(o.count[kSlotTbl5c] == 0, "the +0x5c neighbour of +0x60 stayed silent");
  check(o.count[kSlotTbl64] == 0, "the +0x64 neighbour of +0x60 stayed silent");
  check(o.count[kSlotTbl68] == 0, "the +0x68 neighbour of +0x60 stayed silent");
  check_no_decoy_ran(o);
}

// REFUTE C and D: wrong pointer level, and one dereference too many. A live table
// sits at the owner's +0x04 and +0x08 and at the dispatch object's +0x04, +0x10
// and (as observers) +0x08, +0x0c, +0x14, +0x18, +0x1c; the second table's +0x00
// points at a third table that also has a live observer at +0x60.
void case_pointer_levels() {
  World w;
  setup_nominal(w);
  Observation o;
  call_reconstruction(w, o, 0u);
  // A wrong word on the owner's leading read, or on the dispatch object's leading
  // read, lands on the decoy table -- whose +0x60 slot (site 2) and +0x20 slot
  // (site 1) are both live observers, so either mistake is caught by name.
  check(o.count[kSlotBase60] == 0, "no decoy table was used as a dispatch base");
  check(o.count[kSlotBase20] == 0, "no decoy table slot was called");
  check(o.count[kSlotTbl04] == 0, "the second table's +0x04 was not called");
  check(o.count[kSlotTbl10] == 0, "the second table's +0x10 was not called");
  check(o.count[kSlotThird60] == 0, "no third-level chase reached a table");
  check(o.count[kSlotDecoyCall] == 0,
        "no decoy word was used as a call target (a decoy word is a table)");
  // And the one dereference that IS there, measured.
  check(o.self[kSlotSecondSite] == static_cast<void *>(&w.slot.slot),
        "exactly one dereference of the owner before site 2");
}

// REFUTE E: the post-call EAX. 0x00a8507e re-reads through EAX instead of
// reloading [ECX], so a first callee that writes EAX moves site 2's receiver AND
// its table base. This is the case that separates the machine's data flow from the
// "obvious" source-level re-read.
void case_first_callee_clobbers_eax() {
  World w;
  setup_nominal(w);
  Observation o;
  o.first_eax_mode = kFixedEax;
  o.first_eax_fixed =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(&w.wrong_level.slot));

  const Word result = call_reconstruction(w, o, 0u);

  check(o.log_length == 2, "a clobbering first callee still yields two transfers");
  check(o.log_length > 0 && o.log[0] == kSlotFirstSite, "site 1 still runs first");
  // The second dispatch must have followed the DECOY: receiver = the value the
  // first callee left in EAX, table = the word that value leads with.
  check(o.count[kSlotBase60] == 1,
        "site 2's target came from the clobbered EAX's own +0x00 word");
  check(o.count[kSlotSecondSite] == 0,
        "the nominal +0x60 slot was NOT reached after the clobber");
  check(o.self[kSlotBase60] == static_cast<void *>(&w.wrong_level.slot),
        "site 2's receiver is the clobbered EAX, not *owner");
  // And the decoy's return value is what lands in the receiver.
  check(read_planted(&w.receiver, kResultDisplacement) ==
            decoy_return(kSlotBase60),
        "the receiver's +0x10 holds the DECOY callee's EAX");
  check(result == decoy_return(kSlotBase60),
        "the decoy's EAX is the value returned too");
}

// The other direction of the same hypothesis: a first callee that leaves EAX
// alone must reproduce the nominal behaviour exactly.
void case_first_callee_preserves_eax() {
  World w;
  setup_nominal(w);
  Observation o;
  o.first_eax_mode = kPreserveEax;
  const Word result = call_reconstruction(w, o, 0u);
  check(o.count[kSlotSecondSite] == 1,
        "an EAX-preserving callee keeps the real slot");
  check(o.self[kSlotSecondSite] == static_cast<void *>(&w.slot.slot),
        "an EAX-preserving callee keeps *owner as site 2's receiver");
  check(read_planted(&w.receiver, kResultDisplacement) == o.second_return,
        "the nominal result is stored");
  check(result == o.second_return, "the nominal result is returned");
  check_no_decoy_ran(o);
}

// REFUTE A: the store lands on the RECEIVER. The dispatch object and the second
// table are inputs; if the store went to either, the model's own plant words would
// be gone after the call.
void case_store_lands_on_the_receiver() {
  World w;
  setup_nominal(w);
  Observation o;
  const Word obj_word_before = w.slot.slot.field_20;
  const Word table_word_before = w.table.words[kSecondFetchDisplacement / 4];
  const Word obj_base_before = read_planted(&w.slot.slot, 0x00);

  call_reconstruction(w, o, 0u);

  check(w.slot.slot.field_20 == obj_word_before,
        "the dispatch object's +0x20 was not written");
  check(w.table.words[kSecondFetchDisplacement / 4] == table_word_before,
        "the second table's +0x60 slot was not written");
  check(read_planted(&w.slot.slot, 0x00) == obj_base_before,
        "the dispatch object's +0x00 was not written");
  check(read_planted(&w.receiver, kResultDisplacement) == o.second_return,
        "the receiver's +0x10 was written");
}

// REFUTE F: the write is LAST. Each observer reads the receiver's +0x10 as it is
// entered, so an early store would be visible from inside the calls.
void case_write_is_last() {
  World w;
  setup_nominal(w);
  Observation o;
  call_reconstruction(w, o, 0u);
  check(o.result_seen[kSlotFirstSite] == kResultDecoyWord,
        "receiver+0x10 was still the decoy while site 1 ran");
  check(o.result_seen[kSlotSecondSite] == kResultDecoyWord,
        "receiver+0x10 was still the decoy while site 2 ran");
  check(read_planted(&w.receiver, kResultDisplacement) == o.second_return,
        "receiver+0x10 holds the result once both calls have returned");
}

// REFUTE G: no branch, no guard, no filter on the result. The body has zero
// conditional branches, so the stored word must be the callee's word verbatim for
// every value -- including the two a pointer-typed field would tempt a
// reconstruction into special-casing.
void case_result_values_are_passed_through() {
  const Word values[4] = {0x00000000u, 0xffffffffu, 0x00a85070u, 0x0badc0deu};
  for (std::size_t i = 0; i < 4; ++i) {
    World w;
    setup_nominal(w);
    const std::array<std::uint8_t, 0x6c> before = w.receiver.opaque_00;
    Observation o;
    o.second_return = values[i];
    const Word result = call_reconstruction(w, o, 0u);
    char what[112];
    std::snprintf(what, sizeof(what),
                  "result 0x%08x is passed through unchanged", values[i]);
    check(o.log_length == 2, what);
    check(read_planted(&w.receiver, kResultDisplacement) == values[i], what);
    check(result == values[i], what);
    check_only_the_result_word_changed(before, w.receiver, values[i], what);
  }
}

// REFUTE H: the second stack word. `RET 0xc` pops three words, so the slot
// exists, but no instruction reads it. Running the whole case with a benign word
// and with a pointer to a poisoned block must be indistinguishable, and the
// poisoned block must come back untouched.
void case_second_stack_word_is_unused() {
  World a;
  setup_nominal(a);
  Observation oa;
  const Word result_a = call_reconstruction(a, oa, 0u);

  std::array<std::uint8_t, 0x40> poison;
  poison.fill(0xa5);
  const std::array<std::uint8_t, 0x40> poison_before = poison;

  World b;
  setup_nominal(b);
  Observation ob;
  const Word result_b = call_reconstruction(
      b, ob, static_cast<Word>(reinterpret_cast<std::uintptr_t>(poison.data())));

  check(result_a == result_b, "the second stack word does not change the result");
  check(std::memcmp(a.receiver.opaque_00.data(), b.receiver.opaque_00.data(),
                    a.receiver.opaque_00.size()) == 0,
        "the second stack word does not change the receiver state");
  check(std::memcmp(poison.data(), poison_before.data(), poison.size()) == 0,
        "the second stack word is never dereferenced or written");
  check(oa.log_length == 2 && ob.log_length == 2,
        "the second stack word does not change the number of transfers");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_00a85070

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00a85070;
  case_nominal();
  case_slot_displacements();
  case_pointer_levels();
  case_first_callee_clobbers_eax();
  case_first_callee_preserves_eax();
  case_store_lands_on_the_receiver();
  case_write_is_last();
  case_result_values_are_passed_through();
  case_second_stack_word_is_unused();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
