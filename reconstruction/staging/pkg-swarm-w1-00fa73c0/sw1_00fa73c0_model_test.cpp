// PKG-SWARM-W1-00FA73C0 -- VA 0x00fa73c0
// Behavioural model test for FUN_00fa73c0 @ 0x00fa73c0.
//
// Every transfer the reconstruction makes is defined here as an observer, so the
// test sees each one with its arguments, in its order, and gets to decide what it
// does to memory. There are five transfer points:
//
//   * 0x00f9f770          one direct call, cdecl, three stack words  (0x00fa73d4)
//   * the dispatch target  three indirect calls, thiscall, one stack word each
//                          (0x00fa7408, 0x00fa7417, 0x00fa7426)
//   * 0x00fbaf10          one direct call, thiscall, one stack word   (0x00fa7430)
//   * 0x00fbaf50          one direct call, thiscall, one stack word   (0x00fa743d)
//
// and one arithmetic region, 0x00fa73d9..0x00fa73f2, driven both through the body
// and, over a large part of the 32-bit domain, through the factored helper.
//
// WHAT IS ASSERTED is what the 46-instruction listing fixes:
//
//   * the exact call sequence, once each, in the order 0x00f9f770, dispatch,
//     dispatch, dispatch, 0x00fbaf10, 0x00fbaf50;
//   * the three words 0x00f9f770 receives, by value and by order: arguments 1 and
//     2 are the SAME word, the one at receiver+0x79c, and argument 3 is the word at
//     receiver+0x798 -- all three as they stood BEFORE the snap, which the observer
//     samples out of memory rather than being told;
//   * that 0x00f9f770's return value is dead, proved by running the whole body
//     twice with two different poisoned return values and requiring the resulting
//     receiver bytes to be identical;
//   * the dispatch chain is TWO levels deep and the table word lives at the
//     SUB-object's displacement 0, at table dword index 6 (displacement 0x18), and
//     is re-resolved before every one of the three calls;
//   * the three immediates, in order: 0x0536250c, 0x0536250d, 0x03a23f9a;
//   * the two 0xfbaf* calls take the object at receiver+0x20c -- re-read for the
//     second one -- and the literal 0;
//   * the two words the body writes: receiver+0x79c by the snap amount and
//     receiver+0x814 by exactly +1, and NOTHING ELSE in the 0x818-byte receiver
//     changes, which is asserted by comparing all 0x818 bytes plus a sentinel tail;
//   * the arithmetic identity of 0x00fa73d9..0x00fa73f2, proved over the whole
//     32-bit domain rather than sampled;
//   * the frame ledger, as arithmetic over the instruction sequence.
//
// THE CASES MARKED REFUTE EXIST TO BREAK THE RECONSTRUCTION. Each names a wrong
// reconstruction it is aimed at, and each is driven with a decoy planted at the
// wrong place rather than merely with a different input:
//
//   R1  two-level vs one-level dispatch: a decoy function pointer sits at the
//       SUB-object's own displacement 0x18 and a decoy table sits at the receiver's
//       +0x00, so a model that read the table word out of the receiver, or that
//       indexed the sub-object instead of its dispatch word, calls the decoy;
//   R2  wrong table slot: nine distinct markers at indices 0..8 and only index 6
//       may fire -- an off-by-one-slot reconstruction is caught, in both
//       directions;
//   R3  wrong base object: decoy sub-objects at the receiver's +0x24, +0x2c and
//       +0x30, each with its own table, and only the +0x28 one may be used;
//   R4  cached target vs re-resolved: the first dispatched call re-points the
//       sub-object's dispatch word at a different table, and the second and third
//       calls must then land on the new table's index 6;
//   R5  wrong receiver for the 0xfbaf* pair: decoy objects at +0x204, +0x208 and
//       +0x210, and only the +0x20c one may be passed;
//   R6  re-read vs cached for the 0xfbaf* pair: 0x00fbaf10 re-points the receiver's
//       word at +0x20c and 0x00fbaf50 must see the new object, not the old one;
//   R7  wrong snap field: decoy words at +0x798, +0x7a0, +0x79d and +0x7a4, and a
//       byte-level check that no byte outside the four snap bytes and the four
//       counter bytes moves;
//   R8  floor instead of truncate: delta = +173 must move the word DOWN by 0xac;
//   R9  positive divisor: delta = +172 must move the word down by 0xac onto
//       +0x798, which a `+trunc(delta/172)*172` would get backwards;
//   R10 unsigned instead of signed: delta = -173 must move the word UP by 0xac;
//   R11 wrapping 32-bit arithmetic: deltas whose SUB and whose ADD both overflow,
//       including the two ends of the domain;
//   R12 literal-argument: 0x00fbaf10 and 0x00fbaf50 must receive 0 even when every
//       receiver word is non-zero and distinct;
//   R13 write ordering: the counter must still read its pre-call value inside every
//       observer, and the dispatch observers must see the POST-snap word while the
//       0x00f9f770 observer must see the PRE-snap word;
//   R14 dead return: two full runs with different poisons for 0x00f9f770's result
//       must produce byte-identical receivers.
//
// WHAT IS NOT ASSERTED, AND WHY:
//
//   * EAX. The last thing this body writes to EAX is the third dispatch's target
//     load at 0x00fa741e; the two calls and the INC after it leave whatever
//     0x00fbaf50 returned. Nothing in this package establishes that word as a value
//     for the caller -- the records disagree among themselves about it (see the
//     sidecar) -- so no check here looks at it.
//   * Whether the words at receiver+0x798 and +0x79c are pointers. The body never
//     dereferences them and neither does 0x00f9f770 on this path, so the fixtures
//     plant values that are NOT dereferenceable (small integers) and the test still
//     passes. That is a deliberate check that the reconstruction does not invent a
//     dereference.
//   * What 0x00fbaf10 and 0x00fbaf50 do beyond their own terminators, their
//     receiver words and their receiver. 0x00fbaf10's tail target reads a table at
//     0x016d6d30 and 0x00fbaf50's reads one at 0x016d6d70; both addresses lie
//     outside every section header in this image, so what they would contain is not
//     recoverable here. The observers are free to fabricate everything behind that
//     boundary and the model asserts nothing about it. The one thing the test does
//     assert about them is the receiver word each one touches, because that is in
//     their own bytes and it is what makes them two different operations.
//   * The identity of the class. The table at 0x01490be8 has this body at its
//     displacement +0x70, so that table is one this body is an entry of -- but the
//     model names no class, no member and no slot, and the test plants its own
//     tables rather than trying to reproduce 0x01490be8.
//   * The class-side cleanup of the three dispatched callees is MEASURED, not
//     asserted, and what is measured is the arithmetic requirement: the body
//     executes exactly one `ADD ESP`, 0x00fa7400 `ADD ESP,0xc`, which accounts for
//     0x00f9f770's three words and nothing else, and the three epilogue POPs
//     restore exactly the three prologue PUSHes. A callee that returned with a
//     bare RET would leave the stack 12 bytes short at 0x00fa7448 and the three POPs
//     would read the three immediates instead of the saved registers. The ledger
//     check below computes that walk and requires it to balance, and separately
//     requires the bare-RET variant NOT to balance. It is not a live stack
//     measurement -- the C++ caller's own frame discipline would mask one -- and it
//     is labelled as what it is: a proof about the machine, from the machine's own
//     instruction sequence.

#include "sw1_00fa73c0_types.hpp"

#include <cstddef>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0 {
namespace {

// -- fixtures ----------------------------------------------------------------

// The receiver plus a sentinel tail, so that a write past +0x817 shows up in the
// byte comparison instead of landing in adjacent memory.
constexpr std::size_t kReceiverSize = 0x818u;
constexpr std::size_t kGuardBytes = 16u;

struct Fixture {
  std::uint8_t bytes[kReceiverSize + kGuardBytes];
};

// The object at receiver+0x28. Its word 0 is the dispatch word; everything else is
// decoy, and the decoy at +0x18 is aimed at a reconstruction that skips level 1 and
// indexes the sub-object itself.
struct SubObject {
  void* table;  // the dispatch word: a pointer to the table, exactly as the machine
                 // loads it with `MOV EDX,DWORD PTR [ECX]`
  std::uint32_t pad_04_14[5];
  DwordThunk decoy_at_18;  // a one-level reconstruction would call THIS
  std::uint32_t pad_1c_23[2];
};
static_assert(offsetof(SubObject, decoy_at_18) == 0x18, "decoy at the slot offset");

// Nine markers so that any slot displacement error lands on a distinct identity.
struct Table {
  DwordThunk slots[9];
};
static_assert(kDispatchWordIndex < 9u, "index 6 is inside the marker table");

struct Observation {
  // -- call log
  int log[8];
  int log_length;

  // -- 0x00f9f770
  int range_calls;
  void* range_first;
  void* range_last;
  void* range_parallel;
  Word range_return;  // what the observer hands back, so "dead" is testable
  Word range_snap_seen;     // receiver+0x79c sampled INSIDE the call
  Word range_range_seen;    // receiver+0x798 sampled INSIDE the call
  Word range_dispatch_seen; // receiver+0x28 sampled INSIDE the call
  Word range_counter_seen;  // receiver+0x814 sampled INSIDE the call

  // -- the three dispatches
  int dispatch_calls;
  int dispatch_table[4];   // which table's marker fired, per call
  int dispatch_index[4];   // which index's marker fired, per call
  void* dispatch_receiver[4];
  Word dispatch_word[4];
  Word dispatch_snap_seen[4];
  Word dispatch_counter_seen[4];
  // When >= 0, the firing marker re-points the sub-object's word 0 to
  // replacement_table before returning, which is what makes case R4 decisive.
  int rewire_after;
  void* replacement_table;
  // When set, the firing marker re-points the RECEIVER's own word at
  // kDispatchObjectDisplacement instead, which is the coarser level-0 reload and
  // is what case R4b is aimed at. R4 above only re-points the sub-object's own
  // dispatch word, so it catches a model that caches the resolved FUNCTION but not
  // one that caches the resolved SUB-OBJECT; R4b catches the other half.
  bool rewire_level_zero;
  void* replacement_sub_object;

  // -- 0x00fbaf10
  int select_a_calls;
  void* select_a_receiver;
  Word select_a_argument;
  Word select_a_counter_seen;
  Word select_a_snap_seen;
  // When set, the observer re-points the receiver's word at +0x20c, which is what
  // makes case R6 decisive.
  bool rewire_table_object;
  void* replacement_table_object;

  // -- 0x00fbaf50
  int select_b_calls;
  void* select_b_receiver;
  Word select_b_argument;
  Word select_b_counter_seen;
  Word select_b_snap_seen;

  void reset() { *this = Observation(); }
  void record(int call) {
    if (log_length < 8) {
      log[log_length] = call;
    }
    ++log_length;
  }
};

enum CallId { kCallRange = 0, kCallDispatch = 1, kCallSelectA = 2, kCallSelectB = 3 };

Observation g_obs;
Fixture* g_fixture = nullptr;      // the receiver the observers sample
void* g_sub_object = nullptr;      // the object the body should pass to the dispatches
int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

Word word_of(const std::uint8_t* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

// -- observers ---------------------------------------------------------------

// 0x00f9f770. cdecl, three words, and its real body returns its third argument
// when its first two are equal -- which this caller guarantees. The observer
// returns whatever the case asked for instead, so that a reconstruction which fed
// the result into the snap is caught rather than accidentally agreeing.
extern "C" Word PKG_SWARM_W1_00FA73C0_CDECL for_each_stride_ac_00f9f770(
    void* range_first, void* range_last, void* parallel_first) {
  g_obs.record(kCallRange);
  ++g_obs.range_calls;
  g_obs.range_first = range_first;
  g_obs.range_last = range_last;
  g_obs.range_parallel = parallel_first;
  if (g_fixture != nullptr) {
    const std::uint8_t* base = g_fixture->bytes;
    g_obs.range_snap_seen = word_of(base, kSnapFieldDisplacement);
    g_obs.range_range_seen = word_of(base, kRangeFirstFieldDisplacement);
    g_obs.range_dispatch_seen = word_of(base, kDispatchObjectDisplacement);
    g_obs.range_counter_seen = word_of(base, kCounterDisplacement);
  }
  return g_obs.range_return;
}

// The dispatch markers. Templated on (table, index) so that every one of the
// eighteen combinations has a distinct address, which is what lets the test tell
// "called the right slot of the right table" from "called some other slot".
template <int Table, int Index>
void PKG_SWARM_W1_00FA73C0_THISCALL dispatch_marker(void* receiver, Word word) {
  g_obs.record(kCallDispatch);
  ++g_obs.dispatch_calls;
  if (g_obs.dispatch_calls <= 4) {
    const int n = g_obs.dispatch_calls - 1;
    g_obs.dispatch_table[n] = Table;
    g_obs.dispatch_index[n] = Index;
    g_obs.dispatch_receiver[n] = receiver;
    g_obs.dispatch_word[n] = word;
  }
  if (g_fixture != nullptr) {
    const std::uint8_t* base = g_fixture->bytes;
    if (g_obs.dispatch_calls <= 4) {
      const int n = g_obs.dispatch_calls - 1;
      g_obs.dispatch_snap_seen[n] = word_of(base, kSnapFieldDisplacement);
      g_obs.dispatch_counter_seen[n] = word_of(base, kCounterDisplacement);
    }
  }
  if (g_obs.rewire_after == g_obs.dispatch_calls && g_sub_object != nullptr) {
    // Stand in for a callee that re-points its own sub-object's dispatch word.
    *reinterpret_cast<void**>(g_sub_object) = g_obs.replacement_table;
  }
  if (g_obs.rewire_level_zero && g_obs.dispatch_calls == 1 && g_fixture != nullptr) {
    // Stand in for something that re-points the receiver's own word at +0x28, so
    // that the second and third calls have to re-read the displacement instead of
    // reusing the level-0 pointer the first call resolved.
    std::uint8_t* const base = const_cast<std::uint8_t*>(g_fixture->bytes);
    std::memcpy(base + kDispatchObjectDisplacement, &g_obs.replacement_sub_object,
                sizeof g_obs.replacement_sub_object);
  }
}

// 0x00fbaf10. __thiscall, one stack word, receiver in ECX. It samples the receiver
// the way the real one does -- it writes the identifier to its own receiver word at
// +0x5c0, a displacement this package reads out of its bytes and names.
extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL select_from_table_a_00fbaf10(
    void* receiver, Word identifier) {
  g_obs.record(kCallSelectA);
  ++g_obs.select_a_calls;
  g_obs.select_a_receiver = receiver;
  g_obs.select_a_argument = identifier;
  if (g_fixture != nullptr) {
    const std::uint8_t* base = g_fixture->bytes;
    g_obs.select_a_counter_seen = word_of(base, kCounterDisplacement);
    g_obs.select_a_snap_seen = word_of(base, kSnapFieldDisplacement);
  }
  // The real callee stores the identifier at its receiver's +0x5c0.
  *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(receiver) + 0x5c0) =
      identifier;
  if (g_obs.rewire_table_object && g_fixture != nullptr) {
    Word* const slot = reinterpret_cast<Word*>(
        const_cast<std::uint8_t*>(g_fixture->bytes) + kTableObjectDisplacement);
    *slot = reinterpret_cast<Word>(g_obs.replacement_table_object);
  }
}

// 0x00fbaf50. __thiscall, one stack word, receiver in ECX. It touches a DIFFERENT
// receiver word from its sibling -- +0x5c4 against +0x5c0 -- and the test checks
// that, because folding the two callees into one operation is exactly the kind of
// reconstruction the listing rules out.
extern "C" void PKG_SWARM_W1_00FA73C0_THISCALL select_from_table_b_00fbaf50(
    void* receiver, Word identifier) {
  g_obs.record(kCallSelectB);
  ++g_obs.select_b_calls;
  g_obs.select_b_receiver = receiver;
  g_obs.select_b_argument = identifier;
  if (g_fixture != nullptr) {
    const std::uint8_t* base = g_fixture->bytes;
    g_obs.select_b_counter_seen = word_of(base, kCounterDisplacement);
    g_obs.select_b_snap_seen = word_of(base, kSnapFieldDisplacement);
  }
  *reinterpret_cast<Word*>(reinterpret_cast<std::uint8_t*>(receiver) + 0x5c4) =
      identifier;
}

// -- fixture construction ----------------------------------------------------

struct World {
  Fixture fixture;
  SubObject sub;        // the object at receiver+0x28
  SubObject second_sub; // a replacement for receiver+0x28, used by case R4b
  SubObject decoy_near[3];  // at receiver+0x24, +0x2c, +0x30
  SubObject table_obj;      // the object at receiver+0x20c
  SubObject decoy_table[3]; // at receiver+0x204, +0x208, +0x210
  Table primary;
  Table secondary;
  Table decoy_tables[4];
};

void fill_table(Table* table, int tag) {
  // Nine distinct markers. The dispatch_marker instantiations are spelled out
  // rather than generated so that each address is unique and the compiler has no
  // freedom to merge any two of them.
  if (tag == 0) {
    table->slots[0] = &dispatch_marker<0, 0>;
    table->slots[1] = &dispatch_marker<0, 1>;
    table->slots[2] = &dispatch_marker<0, 2>;
    table->slots[3] = &dispatch_marker<0, 3>;
    table->slots[4] = &dispatch_marker<0, 4>;
    table->slots[5] = &dispatch_marker<0, 5>;
    table->slots[6] = &dispatch_marker<0, 6>;
    table->slots[7] = &dispatch_marker<0, 7>;
    table->slots[8] = &dispatch_marker<0, 8>;
  } else if (tag == 1) {
    table->slots[0] = &dispatch_marker<1, 0>;
    table->slots[1] = &dispatch_marker<1, 1>;
    table->slots[2] = &dispatch_marker<1, 2>;
    table->slots[3] = &dispatch_marker<1, 3>;
    table->slots[4] = &dispatch_marker<1, 4>;
    table->slots[5] = &dispatch_marker<1, 5>;
    table->slots[6] = &dispatch_marker<1, 6>;
    table->slots[7] = &dispatch_marker<1, 7>;
    table->slots[8] = &dispatch_marker<1, 8>;
  } else if (tag == 2) {
    table->slots[0] = &dispatch_marker<2, 0>;
    table->slots[1] = &dispatch_marker<2, 1>;
    table->slots[2] = &dispatch_marker<2, 2>;
    table->slots[3] = &dispatch_marker<2, 3>;
    table->slots[4] = &dispatch_marker<2, 4>;
    table->slots[5] = &dispatch_marker<2, 5>;
    table->slots[6] = &dispatch_marker<2, 6>;
    table->slots[7] = &dispatch_marker<2, 7>;
    table->slots[8] = &dispatch_marker<2, 8>;
  } else {
    table->slots[0] = &dispatch_marker<3, 0>;
    table->slots[1] = &dispatch_marker<3, 1>;
    table->slots[2] = &dispatch_marker<3, 2>;
    table->slots[3] = &dispatch_marker<3, 3>;
    table->slots[4] = &dispatch_marker<3, 4>;
    table->slots[5] = &dispatch_marker<3, 5>;
    table->slots[6] = &dispatch_marker<3, 6>;
    table->slots[7] = &dispatch_marker<3, 7>;
    table->slots[8] = &dispatch_marker<3, 8>;
  }
}

// A decoy function pointer that is never supposed to be called. If it ever is, the
// reconstruction picked the wrong pointer and the test says so.
int g_decoy_hits = 0;
void PKG_SWARM_W1_00FA73C0_THISCALL decoy_marker(void* receiver, Word word) {
  (void)receiver;
  (void)word;
  ++g_decoy_hits;
}

void set_word(std::uint8_t* base, std::size_t displacement, Word value) {
  std::memcpy(base + displacement, &value, sizeof value);
}

World* build(Word range_first, Word cursor, Word counter) {
  World* const world = new World();
  std::memset(world, 0, sizeof *world);

  fill_table(&world->primary, 0);
  fill_table(&world->secondary, 1);
  for (int i = 0; i < 4; ++i) {
    fill_table(&world->decoy_tables[i], 2);
  }

  // The object the body should reach, with its dispatch word at +0x00 and a decoy
  // at its own +0x18.
  world->sub.table = &world->primary;
  world->sub.decoy_at_18 = &decoy_marker;
  world->second_sub.table = &world->secondary;
  world->second_sub.decoy_at_18 = &decoy_marker;
  for (int i = 0; i < 3; ++i) {
    world->decoy_near[i].table = &world->decoy_tables[i];
    world->decoy_near[i].decoy_at_18 = &decoy_marker;
  }
  world->table_obj.table = &world->decoy_tables[0];
  world->table_obj.decoy_at_18 = &decoy_marker;
  for (int i = 0; i < 3; ++i) {
    world->decoy_table[i].table = &world->decoy_tables[1 + (i % 3)];
    world->decoy_table[i].decoy_at_18 = &decoy_marker;
  }

  // A poison word at the receiver's own +0x00, aimed at a reconstruction that read
  // the dispatch word off the receiver instead of off the sub-object.
  set_word(world->fixture.bytes, 0x00, 0xfeedfaceu);

  set_word(world->fixture.bytes, kRangeFirstFieldDisplacement, range_first);
  set_word(world->fixture.bytes, kSnapFieldDisplacement, cursor);
  set_word(world->fixture.bytes, kCounterDisplacement, counter);
  set_word(world->fixture.bytes, kDispatchObjectDisplacement,
           reinterpret_cast<Word>(&world->sub));
  set_word(world->fixture.bytes, kTableObjectDisplacement,
           reinterpret_cast<Word>(&world->table_obj));

  // Neighbouring words around every displacement the body reaches. Nothing here
  // may change.
  set_word(world->fixture.bytes, 0x24, 0x11111111u);
  set_word(world->fixture.bytes, 0x2c, 0x22222222u);
  set_word(world->fixture.bytes, 0x30, 0x33333333u);
  set_word(world->fixture.bytes, 0x204, reinterpret_cast<Word>(&world->decoy_table[0]));
  set_word(world->fixture.bytes, 0x208, reinterpret_cast<Word>(&world->decoy_table[1]));
  set_word(world->fixture.bytes, 0x210, reinterpret_cast<Word>(&world->decoy_table[2]));
  set_word(world->fixture.bytes, 0x218, 0x44444444u);
  set_word(world->fixture.bytes, 0x790, 0x55555555u);
  set_word(world->fixture.bytes, 0x794, 0x66666666u);
  set_word(world->fixture.bytes, 0x7a0, 0x77777777u);
  set_word(world->fixture.bytes, 0x7a4, 0x88888888u);
  set_word(world->fixture.bytes, 0x7a8, 0x99999999u);
  set_word(world->fixture.bytes, 0x810, 0xaaaaaaaau);
  set_word(world->fixture.bytes, 0x818, 0xbbbbbbbbu);
  set_word(world->fixture.bytes, 0x81c, 0xccccccccu);

  // Decoy words one byte off each of the two words the body writes, so that a
  // wrong DISPLACEMENT (as opposed to a wrong width) would show up.
  world->fixture.bytes[kSnapFieldDisplacement + 4u] = 0x5a;
  world->fixture.bytes[kCounterDisplacement + 4u] = 0x5b;
  return world;
}

void arm(World* world) {
  g_obs.reset();
  g_fixture = &world->fixture;
  g_sub_object = &world->sub;
  g_decoy_hits = 0;
}

void run(World* world) {
  sw1_snap_and_dispatch_00fa73c0(
      reinterpret_cast<Receiver*>(static_cast<void*>(&world->fixture)));
}

// -- cases -------------------------------------------------------------------

// The independent oracle for the six arithmetic instructions. Deliberately NOT the
// model's code: it is the closed form, so a mistake in the model's magic-number
// emulation cannot hide behind a matching mistake in the oracle.
std::int32_t to_signed(Word value) {
  return (value & 0x80000000u) != 0u
             ? (-1 - static_cast<std::int32_t>(~value))
             : static_cast<std::int32_t>(value);
}

Word oracle_snap(Word range_first, Word cursor) {
  // 0x00fa73d9 is a 32-bit SUB, so the difference WRAPS before it is read as
  // signed. Computing it in 64 bits and only then narrowing would give a different
  // answer for base 0x80000000 / cursor 0 and for base 1 / cursor 0, which is
  // exactly the R11 refutation.
  const Word delta_bits = cursor - range_first;
  const std::int64_t delta = to_signed(delta_bits);
  const std::int64_t blocks = delta / 172;  // C++ signed division truncates toward zero
  const std::int64_t amount = -(blocks * 172);
  return static_cast<Word>(static_cast<std::uint32_t>(static_cast<std::uint64_t>(amount)));
}

void case_frame_ledger() {
  // The walk from the file header, as arithmetic. Entry ESP is 0.
  int esp = 0;
  esp -= 4;   // 0x00fa73c0 PUSH EBX
  esp -= 4;   // 0x00fa73c1 PUSH ESI
  esp -= 4;   // 0x00fa73ca PUSH EDI
  esp -= 4;   // 0x00fa73d1 PUSH EBX
  esp -= 4;   // 0x00fa73d2 PUSH EDI
  esp -= 4;   // 0x00fa73d3 PUSH EDI
  esp -= 4;   // 0x00fa73d4 CALL 0x00f9f770
  esp += 4;   //   the bare RET of 0x00f9f770 pops the return address, and no more
  esp += 12;  // 0x00fa7400 ADD ESP,0xc
  const int after_range = esp;
  check(after_range == -12, "ledger: the range call leaves ESP at entry-12");

  for (int i = 0; i < 3; ++i) {
    esp -= 4;  // PUSH imm
    esp -= 4;  // CALL, which pushes the return address
    esp += 4;  //   the return address
    esp += 4;  //   the RET 4 immediate, so the callee drops its own argument
    check(esp == -12, "ledger: a dispatched call returns ESP to entry-12");
  }
  for (int i = 0; i < 2; ++i) {
    esp -= 4;  // PUSH 0
    esp -= 4;  // CALL 0x00fbaf10 / 0x00fbaf50
    esp += 4;  //   the return address
    esp += 4;  //   the callee's own RET 0x4, read from its bytes
  }
  check(esp == -12, "ledger: the last call leaves ESP at entry-12");
  esp += 4;  // 0x00fa7448 POP EDI
  esp += 4;  // 0x00fa7449 POP ESI
  esp += 4;  // 0x00fa744a POP EBX
  check(esp == 0, "ledger: the epilogue's three POPs land back on the entry ESP");
  esp += 4;  // 0x00fa744b RET
  check(esp == 4, "ledger: the RET leaves the caller's ESP where its CALL found it");

  // The alternative the listing rules out: three bare-RET dispatch targets.
  int bare = -12;
  for (int i = 0; i < 3; ++i) {
    bare -= 4;  // PUSH imm
    bare -= 4;  // CALL
    bare += 4;  //   a bare RET pops the return address and NOTHING else
  }
  bare += 12;  // the three epilogue POPs
  check(bare == -12,
        "ledger: three bare-RET dispatch targets do NOT balance, so each callee "
        "must remove its own word");

  // And zero ordinary argument slots: nothing is pushed for a caller and never
  // dropped for a caller, so the frame cannot hold arguments.
  check(after_range + 12 == 0,
        "ledger: the only ADD ESP in the body accounts for the three words the body "
        "itself pushed, so the frame carries no argument slots");
}

void case_snap_domain() {
  // Exhaustive over a dense window, exhaustive over every multiple of 0xac in the
  // whole domain, and a stride coprime with 0xac across the whole domain. The
  // stride matters: 251 is prime and does not divide 172, so the strided deltas
  // hit every residue class mod 172 many times over.
  std::int64_t checked = 0;
  int failures = 0;

  for (std::int64_t d = -(1 << 20); d <= (1 << 20); ++d) {
    const Word delta = static_cast<Word>(d);
    if (snap_delta_step(0u, delta) != oracle_snap(0u, delta)) {
      if (++failures < 6) {
        std::fprintf(stderr, "FAILED: snap domain, delta=%lld model=0x%08lx oracle=0x%08lx\n",
                     static_cast<long long>(d),
                     static_cast<unsigned long>(snap_delta_step(0u, delta)),
                     static_cast<unsigned long>(oracle_snap(0u, delta)));
      }
    }
    ++checked;
  }
  check(failures == 0, "snap identity holds on every delta in [-2^20, 2^20]");

  failures = 0;
  for (std::int64_t d = -0x80000000ll; d <= 0x7fffffffll; d += 172) {
    const Word delta = static_cast<Word>(d);
    if (snap_delta_step(0u, delta) != oracle_snap(0u, delta)) {
      ++failures;
    }
    ++checked;
  }
  check(failures == 0,
        "snap identity holds on every multiple of 0xac across the signed domain");

  failures = 0;
  for (std::int64_t d = -0x80000000ll; d <= 0x7fffffffll; d += 251) {
    const Word delta = static_cast<Word>(d);
    if (snap_delta_step(0u, delta) != oracle_snap(0u, delta)) {
      ++failures;
    }
    ++checked;
  }
  check(failures == 0,
        "snap identity holds on a stride coprime with 0xac across the signed domain");

  // The value is also independent of the fixed point, because the machine only ever
  // forms the difference.
  failures = 0;
  const Word bases[] = {0u, 1u, 0x7fffffffu, 0x80000000u, 0xdeadbeefu, 0x0000ac00u};
  for (const Word base : bases) {
    for (std::int64_t d = -(1 << 16); d <= (1 << 16); d += 7) {
      const Word cursor = static_cast<Word>(static_cast<std::int64_t>(base) + d);
      if (snap_delta_step(base, cursor) != oracle_snap(base, cursor)) {
        ++failures;
      }
      ++checked;
    }
  }
  check(failures == 0, "snap identity is independent of the fixed point");

  std::fprintf(stderr, "  (snap identity checked over %lld deltas)\n",
               static_cast<long long>(checked));
}

void case_snap_table() {
  // The named refutations of the arithmetic, each a hand-computed expectation.
  struct Row {
    Word cursor;
    Word expected;
    const char* what;
  };
  const Row rows[] = {
      {0u, 0x00000000u, "a zero delta adds zero"},
      {171u, 0x00000000u, "a delta of 171, one below 0xac, adds nothing"},
      {172u, 0xffffff54u, "R9: delta +172 subtracts 0xac (0xffffff54 as a word)"},
      {173u, 0xffffff54u, "R8: delta +173 truncates TOWARD ZERO, so -0xac not +0xac"},
      {344u, 0xfffffea8u, "delta +344 subtracts 2*0xac"},
      {0xffffffffu, 0x00000000u, "delta -1 adds nothing"},
      {0xffffff54u, 0x000000acu, "R10: delta -172 ADDS 0xac -- the delta is signed"},
      {0xffffff53u, 0x000000acu, "R10: delta -173 truncates toward zero and ADDS 0xac"},
      {0x80000000u, 0x7ffffff8u, "R11: the most negative delta wraps and still truncates"},
      {0x7fffffffu, 0x80000008u, "R11: the most positive delta wraps and still truncates"},
  };
  for (const Row& row : rows) {
    check(snap_delta_step(0u, row.cursor) == row.expected, row.what);
  }
  // The two sign-symmetric boundaries spelled out again, so that a typo in the
  // table above cannot hide a sign slip:
  check(snap_delta_step(0u, 172u) == static_cast<Word>(-172),
        "R9: +172 gives -172, i.e. the divisor is effectively negative");
  check(snap_delta_step(0u, static_cast<Word>(-172)) == 172u,
        "R10: -172 gives +172");
}

void case_baseline() {
  // 0x00fa73c0 reads the word at +0x798 as the fixed point and the word at +0x79c as
  // the cursor, and the cursor is 5*0xac + 3 past it, so the snap must move it down
  // by 5*0xac and leave a residue of 3.
  World* const world = build(0x00001000u, 0x00001000u + 5u * 0xacu + 3u, 7u);
  arm(world);
  g_obs.range_return = 0xdeadbeefu;
  run(world);

  check(g_obs.log_length == 6, "baseline: exactly six transfers, none extra");
  check(g_obs.range_calls == 1, "baseline: 0x00f9f770 called once");
  check(g_obs.dispatch_calls == 3, "baseline: the dispatch target called three times");
  check(g_obs.select_a_calls == 1, "baseline: 0x00fbaf10 called once");
  check(g_obs.select_b_calls == 1, "baseline: 0x00fbaf50 called once");
  if (g_obs.log_length == 6) {
    check(g_obs.log[0] == kCallRange, "baseline: transfer 1 is 0x00f9f770");
    check(g_obs.log[1] == kCallDispatch, "baseline: transfer 2 is a dispatch");
    check(g_obs.log[2] == kCallDispatch, "baseline: transfer 3 is a dispatch");
    check(g_obs.log[3] == kCallDispatch, "baseline: transfer 4 is a dispatch");
    check(g_obs.log[4] == kCallSelectA, "baseline: transfer 5 is 0x00fbaf10");
    check(g_obs.log[5] == kCallSelectB, "baseline: transfer 6 is 0x00fbaf50");
  }

  // The three words, by value and in order.
  check(g_obs.range_first ==
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00001000u + 5u * 0xacu + 3u)),
        "baseline: 0x00f9f770 argument 1 is the PRE-snap word at receiver+0x79c");
  check(g_obs.range_last == g_obs.range_first,
        "baseline: 0x00f9f770 argument 2 is the SAME word -- 0x00fa73d2 and "
        "0x00fa73d3 both push EDI");
  check(g_obs.range_parallel ==
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x00001000u)),
        "baseline: 0x00f9f770 argument 3 is the word at receiver+0x798");
  check(g_obs.range_snap_seen == 0x00001000u + 5u * 0xacu + 3u,
        "R13: the snap has NOT happened yet when 0x00f9f770 is called");
  check(g_obs.range_range_seen == 0x00001000u,
        "R13: the fixed point is unmodified when 0x00f9f770 is called");
  check(g_obs.range_dispatch_seen == reinterpret_cast<Word>(&world->sub),
        "baseline: the object at receiver+0x28 is untouched by 0x00f9f770");
  check(g_obs.range_counter_seen == 7u,
        "R13: the counter is not incremented before 0x00f9f770");

  // The dispatches.
  check(g_decoy_hits == 0, "R1: no decoy marker was ever called");
  for (int i = 0; i < 3 && i < g_obs.dispatch_calls; ++i) {
    check(g_obs.dispatch_table[i] == 0, "R2: every dispatch used the primary table");
    check(g_obs.dispatch_index[i] == static_cast<int>(kDispatchWordIndex),
          "R2: every dispatch used table dword index 6, i.e. displacement 0x18");
    check(g_obs.dispatch_receiver[i] == static_cast<void*>(&world->sub),
          "R1/R3: the dispatched receiver is the object at receiver+0x28");
  }
  check(g_obs.dispatch_calls == 3 && g_obs.dispatch_word[0] == 0x0536250cu,
        "baseline: dispatch 1 pushes 0x0536250c");
  check(g_obs.dispatch_calls == 3 && g_obs.dispatch_word[1] == 0x0536250du,
        "baseline: dispatch 2 pushes 0x0536250d");
  check(g_obs.dispatch_calls == 3 && g_obs.dispatch_word[2] == 0x03a23f9au,
        "baseline: dispatch 3 pushes 0x03a23f9a");
  check(g_obs.dispatch_calls == 3 &&
            g_obs.dispatch_snap_seen[0] == 0x00001000u + 3u,
        "R13: the FIRST dispatch already sees the POST-snap word at +0x79c");
  check(g_obs.dispatch_calls == 3 && g_obs.dispatch_counter_seen[0] == 7u,
        "R13: the counter is not incremented before the first dispatch");

  // The 0xfbaf* pair.
  check(g_obs.select_a_receiver == static_cast<void*>(&world->table_obj),
        "R5: 0x00fbaf10 receives the object at receiver+0x20c");
  check(g_obs.select_b_receiver == static_cast<void*>(&world->table_obj),
        "R5/R6: 0x00fbaf50 receives the object at receiver+0x20c as well");
  check(g_obs.select_a_argument == 0u, "R12: 0x00fbaf10 receives the literal 0");
  check(g_obs.select_b_argument == 0u, "R12: 0x00fbaf50 receives the literal 0");
  check(g_obs.select_a_counter_seen == 7u, "R13: no counter change before 0x00fbaf10");
  check(g_obs.select_b_counter_seen == 7u, "R13: no counter change before 0x00fbaf50");
  check(g_obs.select_a_snap_seen == 0x00001000u + 3u,
        "the snap is already in memory when 0x00fbaf10 runs");

  // The two words the body writes, and only those two.
  check(word_of(world->fixture.bytes, kSnapFieldDisplacement) == 0x00001000u + 3u,
        "baseline: the word at +0x79c moved down by 5*0xac and kept the residue 3");
  check(word_of(world->fixture.bytes, kRangeFirstFieldDisplacement) == 0x00001000u,
        "R7: the fixed point at +0x798 is not written");
  check(word_of(world->fixture.bytes, kCounterDisplacement) == 8u,
        "baseline: the word at +0x814 moved by exactly +1");

  // R7 as a byte-level fact: snapshot the receiver, call again, and require that
  // the only differing bytes are inside the two written words.
  std::uint8_t before[kReceiverSize + kGuardBytes];
  std::memcpy(before, world->fixture.bytes, sizeof before);
  arm(world);
  g_obs.range_return = 0xdeadbeefu;
  run(world);
  int moved_outside = 0;
  for (std::size_t i = 0; i < sizeof before; ++i) {
    const bool in_snap = i >= kSnapFieldDisplacement && i < kSnapFieldDisplacement + 4u;
    const bool in_counter =
        i >= kCounterDisplacement && i < kCounterDisplacement + 4u;
    if (!in_snap && !in_counter && before[i] != world->fixture.bytes[i]) {
      ++moved_outside;
    }
  }
  check(moved_outside == 0,
        "R7: no byte outside the two written words changed on a second call");
  check(word_of(world->fixture.bytes, kCounterDisplacement) == 9u,
        "the counter accumulates across calls");
  check(word_of(world->fixture.bytes, kSnapFieldDisplacement) == 0x00001000u + 3u,
        "the snap is idempotent once the cursor is inside one 0xac step");
  delete world;
}

void case_dead_return() {
  // R14: the same body run twice with two different return values for 0x00f9f770
  // must leave byte-identical receivers.
  // One world, run twice from the same starting bytes, so the two receiver images
  // are comparable byte for byte (a second World would differ in the pointer words
  // at +0x28 and +0x20c and the comparison would prove nothing).
  World* const world = build(0x00002000u, 0x00002000u + 3u * 0xacu + 1u, 0u);
  std::uint8_t start[kReceiverSize + kGuardBytes];
  std::uint8_t after_a[kReceiverSize + kGuardBytes];
  std::uint8_t after_b[kReceiverSize + kGuardBytes];
  std::memcpy(start, world->fixture.bytes, sizeof start);

  arm(world);
  g_obs.range_return = 0x00000000u;
  run(world);
  std::memcpy(after_a, world->fixture.bytes, sizeof after_a);

  std::memcpy(world->fixture.bytes, start, sizeof start);
  arm(world);
  g_obs.range_return = 0x7fffffffu;
  run(world);
  std::memcpy(after_b, world->fixture.bytes, sizeof after_b);

  check(std::memcmp(after_a, after_b, kReceiverSize) == 0,
        "R14: 0x00f9f770's return value is dead -- two different results give "
        "byte-identical receivers");
  check(word_of(after_a, kSnapFieldDisplacement) == 0x00002000u + 1u,
        "R14: the snap landed on the fixed point plus the residue");
  check(word_of(after_a, kCounterDisplacement) == 1u,
        "R14: the counter still moved by exactly one");
  delete world;
}

void case_pointer_levels() {
  // R1/R2/R3 in one case: the neighbour decoys at +0x24, +0x2c and +0x30 each hold
  // a sub-object with its own table, and the sub-object itself holds a decoy at its
  // own +0x18. Only the +0x28 object, and only its index 6, may be used.
  World* const world = build(0x00003000u, 0x00003000u + 0xacu + 5u, 1u);
  arm(world);
  g_obs.range_return = 0u;
  run(world);
  check(g_decoy_hits == 0,
        "R1: the decoy at the sub-object's own +0x18 was never called -- the "
        "dispatch word is at the sub-object's +0x00 and the table is indexed at "
        "+0x18, not the other way round");
  check(g_obs.dispatch_calls == 3, "R1: exactly three dispatches");
  for (int i = 0; i < 3 && i < g_obs.dispatch_calls; ++i) {
    check(g_obs.dispatch_table[i] == 0,
          "R3: none of the neighbouring sub-objects at +0x24, +0x2c or +0x30 was "
          "used as the dispatch base");
    check(g_obs.dispatch_receiver[i] == static_cast<void*>(&world->sub),
          "R3: the dispatched receiver is the object at +0x28 and not a neighbour");
  }
  delete world;
}

void case_reload_target() {
  // R4: the first dispatched call re-points the sub-object's dispatch word. The
  // second and third calls must resolve the chain again and land on the NEW table.
  World* const world = build(0x00004000u, 0x00004000u + 0xacu, 0u);
  arm(world);
  g_obs.range_return = 0u;
  g_obs.rewire_after = 1;
  g_obs.replacement_table = &world->secondary;
  run(world);
  check(g_obs.dispatch_calls == 3, "R4: three dispatches");
  if (g_obs.dispatch_calls == 3) {
    check(g_obs.dispatch_table[0] == 0, "R4: the first call used the original table");
    check(g_obs.dispatch_table[1] == 1,
          "R4: the second call RE-RESOLVED the chain and used the new table -- a "
          "cached target would have stayed on table 0");
    check(g_obs.dispatch_table[2] == 1, "R4: the third call re-resolved as well");
    check(g_obs.dispatch_index[0] == 6 && g_obs.dispatch_index[1] == 6 &&
              g_obs.dispatch_index[2] == 6,
          "R2: the re-resolved chain still lands on index 6");
  }
  delete world;
}

void case_reload_level_zero() {
  // R4b: the first dispatched call re-points the RECEIVER's own word at +0x28. The
  // second and third calls must re-read that displacement (0x00fa740a and
  // 0x00fa7419) rather than reuse the level-0 pointer the first call resolved. A
  // reconstruction that cached the sub-object but re-resolved the function would
  // pass case R4 and fail this one; a reconstruction that cached the function would
  // fail R4 and pass this one. Both halves are needed.
  World* const world = build(0x00004500u, 0x00004500u + 0xacu, 0u);
  arm(world);
  g_obs.range_return = 0u;
  g_obs.rewire_level_zero = true;
  g_obs.replacement_sub_object = &world->second_sub;
  run(world);
  check(g_obs.dispatch_calls == 3, "R4b: three dispatches");
  if (g_obs.dispatch_calls == 3) {
    check(g_obs.dispatch_receiver[0] == static_cast<void*>(&world->sub),
          "R4b: the first call received the object the receiver pointed at");
    check(g_obs.dispatch_receiver[1] == static_cast<void*>(&world->second_sub),
          "R4b: the second call received the RE-POINTED object -- 0x00fa740a "
          "re-reads receiver+0x28");
    check(g_obs.dispatch_receiver[2] == static_cast<void*>(&world->second_sub),
          "R4b: the third call re-read receiver+0x28 as well");
    check(g_obs.dispatch_table[0] == 0, "R4b: the first table was the primary one");
    check(g_obs.dispatch_table[1] == 1 && g_obs.dispatch_table[2] == 1,
          "R4b: the re-resolved chain lands on the REPLACEMENT table");
  }
  delete world;
}

void case_reload_table_object() {
  // R6: 0x00fbaf10 re-points the receiver's word at +0x20c. 0x00fbaf50 must see the
  // NEW object, because 0x00fa7435 re-reads the displacement instead of reusing
  // whatever the previous call left in ECX.
  World* const world = build(0x00005000u, 0x00005000u + 0xacu, 0u);
  arm(world);
  g_obs.range_return = 0u;
  g_obs.rewire_table_object = true;
  g_obs.replacement_table_object = &world->decoy_table[1];
  run(world);
  check(g_obs.select_a_calls == 1 && g_obs.select_b_calls == 1,
        "R6: both 0xfbaf* callees ran once");
  check(g_obs.select_a_receiver == static_cast<void*>(&world->table_obj),
        "R6: 0x00fbaf10 received the ORIGINAL object at +0x20c");
  check(g_obs.select_b_receiver == static_cast<void*>(&world->decoy_table[1]),
        "R6: 0x00fbaf50 received the RE-POINTED object -- 0x00fa7435 re-reads "
        "receiver+0x20c rather than reusing the register");
  delete world;
}

void case_negative_and_wrap() {
  // R10/R11: the cursor BELOW the fixed point, and the two ends of the domain.
  struct Row {
    Word base;
    Word cursor;
    const char* what;
  };
  const Row rows[] = {
      {1000u, 1000u - 1u, "a cursor one below the fixed point does not move"},
      {1000u, 1000u - 172u, "a cursor exactly one 0xac below moves up onto it"},
      {1000u, 1000u - 173u, "a cursor 173 below moves up by exactly one 0xac"},
      {0u, 0x80000000u, "the most negative cursor snaps up by whole 0xac steps"},
      {0u, 0x7fffffffu, "the most positive cursor snaps down by whole 0xac steps"},
      {0x80000000u, 0u, "the SUB wraps: base 0x80000000, cursor 0 is delta "
                        "+0x80000000, not -0x80000000"},
      {1u, 0u, "the SUB wraps: base 1, cursor 0 is delta 0xffffffff, not -1"},
  };
  for (const Row& row : rows) {
    World* const world = build(row.base, row.cursor, 0u);
    arm(world);
    g_obs.range_return = 0u;
    run(world);
    const Word expected = static_cast<Word>(row.cursor + oracle_snap(row.base, row.cursor));
    check(word_of(world->fixture.bytes, kSnapFieldDisplacement) == expected,
          row.what);
    if (std::strcmp(row.what, "the SUB wraps: base 1, cursor 0 is delta 0xffffffff, "
                              "not -1") == 0) {
      // A reconstruction that computed the difference in a signed 64-bit register
      // and then narrowed would get -1 here and move the word DOWN instead of UP.
      check(snap_delta_step(1u, 0u) == 0u,
            "R11: delta 0xffffffff adds zero, which only a 32-bit wrap can produce");
    }
    delete world;
  }
}

void case_snap_off_by_one() {
  // R7/R8: the three residues that separate truncation from flooring, driven
  // through the WHOLE body so that the store, not just the helper, is checked.
  struct Row {
    Word delta;
    Word expected_cursor;  // with base 0
    const char* what;
  };
  const Row rows[] = {
      {0u, 0u, "R7: delta 0 leaves the word at 0"},
      {0xabu, 0xabu, "R8: delta 171 is below one step, so the word does not move"},
      {0xacu, 0u, "R8: delta 172 lands the word exactly on the fixed point"},
      {0xadu, 1u, "R8: delta 173 truncates toward zero and leaves residue 1"},
      {0x15du, 5u, "R8: delta 349 = 2*0xac + 5 leaves residue 5"},
      {0xffffffffu, 0xffffffffu, "R10: delta -1 is below one step, no movement"},
      {0xffffff54u, 0u, "R10: delta -172 raises the word onto the fixed point"},
  };
  for (const Row& row : rows) {
    World* const world = build(0u, row.delta, 0u);
    arm(world);
    g_obs.range_return = 0u;
    run(world);
    check(word_of(world->fixture.bytes, kSnapFieldDisplacement) == row.expected_cursor,
          row.what);
    check(word_of(world->fixture.bytes, kRangeFirstFieldDisplacement) == 0u,
          "R7: the fixed point at +0x798 is never written");
    delete world;
  }
  // A flooring reconstruction would have put the cursor at -172 for delta 173 and
  // at -172 for delta 1. Spell those two out so a sign slip in the table is caught.
  World* const floorish = build(0u, 1u, 0u);
  arm(floorish);
  g_obs.range_return = 0u;
  run(floorish);
  check(word_of(floorish->fixture.bytes, kSnapFieldDisplacement) == 1u,
        "R8: delta 1 leaves the word at 1 -- a floor-based shift would have "
        "subtracted 0xac and left 0xfffff955");
  delete floorish;
}

void case_slot_occupancy() {
  // R2 as a standalone check on the model's own view of the table: after a run, the
  // only slot whose marker fired is index 6 of the primary table, and every other
  // slot's marker is still unused. This is what makes an off-by-one-slot
  // reconstruction visible in both directions.
  World* const world = build(0x00006000u, 0x00006000u + 9u, 0u);
  arm(world);
  g_obs.range_return = 0u;
  run(world);
  check(g_obs.dispatch_calls == 3, "R2: three dispatches, three and only three");
  int indices_seen[4] = {-1, -1, -1, -1};
  for (int i = 0; i < 3; ++i) {
    indices_seen[i] = g_obs.dispatch_index[i];
  }
  check(indices_seen[0] == 6 && indices_seen[1] == 6 && indices_seen[2] == 6,
        "R2: index 6 three times, and no other index");
  // A reconstruction that read the word at the sub-object's +0x18 instead of the
  // table's would have called decoy_marker; a reconstruction that read slot 0 or
  // slot 7 would have called a different marker. Both are covered by the identity
  // check above plus g_decoy_hits.
  check(g_decoy_hits == 0, "R1/R2: no marker other than index 6 of the table ran");
  delete world;
}

void case_sibling_callees_differ() {
  // The two 0xfbaf* callees are NOT the same operation: their own bytes put the
  // identifier at their receiver's +0x5c0 and +0x5c4 respectively. The observers
  // write to those two displacements, so this case checks that a reconstruction
  // which had folded them into one call would have lost one of the two stores.
  World* const world = build(0x00007000u, 0x00007000u + 0xacu, 0u);
  arm(world);
  g_obs.range_return = 0u;
  run(world);
  const std::uint8_t* const obj =
      reinterpret_cast<const std::uint8_t*>(&world->table_obj);
  check(word_of(obj, 0x5c0) == 0u,
        "0x00fbaf10's own bytes store the identifier at its receiver's +0x5c0");
  check(word_of(obj, 0x5c4) == 0u,
        "0x00fbaf50's own bytes store the identifier at its receiver's +0x5c4 -- a "
        "DIFFERENT word, so the two calls are not one operation");
  delete world;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00fa73c0;

  case_frame_ledger();
  case_snap_table();
  case_snap_domain();
  case_baseline();
  case_dead_return();
  case_pointer_levels();
  case_reload_target();
  case_reload_level_zero();
  case_reload_table_object();
  case_negative_and_wrap();
  case_snap_off_by_one();
  case_slot_occupancy();
  case_sibling_callees_differ();

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
