// PKG-SWARM-W1-00F9B7F0 -- VA 0x00f9b7f0
// Falsification test for re_00f9b7f0.
//
// WHAT THIS TEST IS. It defines every transfer the reconstructed body makes --
// the five direct callees and the three table entries -- as an OBSERVER, so the
// reconstruction has to get every argument, every argument order, every
// receiver and every dispatch displacement right or the observations do not
// match. Each observer also snapshots the 0x18 bytes of the frame object and the
// 0x818 bytes of the receiver at the instant it is entered, which is what makes
// a wrong-write-ordering or a wrong-receiver fault visible instead of
// invisible.
//
// It then tries to BREAK the reconstruction. The groups:
//
//   A  frame facts           -- the derived frame constants, asserted as data
//   B  the happy path        -- call order, arguments, argument order, receivers
//   C  branch polarity       -- each of the four conditional edges, both ways
//   D  pointer level         -- the two-level read, decoys at the wrong depth
//   E  displacements         -- decoy words and decoy slots at every neighbour
//   F  constants             -- every literal, observed rather than assumed
//   G  equality vs ordering  -- values that separate CMP/JZ from a comparison
//   H  the resolve result    -- it is dereferenced, not used as the candidate
//   I  write ordering        -- what each callee can see when it is entered
//   J  receiver immutability -- no byte of the receiver is written
//   K  cleanups              -- the net cleanup of each call, summed both ways
//
// WHAT THIS TEST DELIBERATELY DOES NOT ASSERT, and why:
//
//  * Nothing about what the type code 0x0a, the property id 0x03ad556a, the tag
//    0x031389b5 or the flags bit 0x04 MEAN. No listing in this set says, the
//    reconstruction claims no more, and a test that guessed would be asserting
//    something the binary does not fix.
//  * Nothing about the shape of the reconstruction's C++ control flow. It
//    asserts the set and order of observable effects, which is what a
//    reconstruction can be held to.
//  * Nothing about the identity of the three table entries, of the object at
//    receiver+0x28, or of the receiver's word at +0x814. Those are open
//    questions in the sidecar.
//  * That the frame CLOSES. It asserts the arithmetic that makes it close, plus
//    the residual explicitly, so the single self-consistent reading of the
//    listing is pinned rather than assumed.
//
// No framework, no external dependency, plain int main(); non-zero exit on any
// failure.

#include "sw1_00f9b7f0_types.hpp"

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace recon = openspore::reconstruction::pkg_swarm_w1_00f9b7f0;
using recon::DispatchObject;
using recon::DispatchSlot014;
using recon::DispatchSlot024;
using recon::LocalProbe;
using recon::Receiver;
using recon::ReceiverSlot080;
using recon::ValueRecord;
using recon::Word;

namespace {

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const char* what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what);
  }
}

void check_eq_u32(unsigned long long got, unsigned long long want, const char* what) {
  ++g_checks;
  if (got != want) {
    ++g_failures;
    std::printf("FAIL: %s (got 0x%llx, want 0x%llx)\n", what, got, want);
  }
}

// ---------------------------------------------------------------------------
// fixture
// ---------------------------------------------------------------------------

// A table with a slot at every displacement the body dispatches through, plus
// room for the decoy slots the E group installs at the neighbouring offsets.
struct FakeTable {
  void* raw[0x84 / sizeof(void*)];
  void set(std::size_t displacement, void* entry) {
    raw[displacement / sizeof(void*)] = entry;
  }
};
static_assert(sizeof(FakeTable) == 0x84, "the +0x80 slot must be addressable");
static_assert(sizeof(void*) == 4, "x86-32 only");

// Defined below; declared here because setup() installs them as decoy slots.
void PKG_SW1_00F9B7F0_THISCALL decoy_slot080(Receiver* receiver);
std::uint8_t PKG_SW1_00F9B7F0_THISCALL decoy_slot024(
    DispatchObject* object, Word property_id, LocalProbe* out);
void PKG_SW1_00F9B7F0_THISCALL decoy_slot014(
    DispatchObject* object, Word property_id, ValueRecord* out);

struct Fixture {
  alignas(4) std::array<unsigned char, 0x818> receiver_bytes{};
  alignas(4) std::array<unsigned char, 0x40> object_bytes{};
  alignas(4) std::array<unsigned char, 0x40> object2_bytes{};
  FakeTable table{};
  FakeTable table2{};
  alignas(4) std::array<unsigned char, sizeof(ValueRecord)> held_bytes{};
  alignas(4) std::array<unsigned char, sizeof(ValueRecord)> held2_bytes{};
  alignas(4) std::array<unsigned char, 0x18> spare{};

  Receiver* receiver() { return reinterpret_cast<Receiver*>(receiver_bytes.data()); }
  DispatchObject* object() {
    return reinterpret_cast<DispatchObject*>(object_bytes.data());
  }
  DispatchObject* object2() {
    return reinterpret_cast<DispatchObject*>(object2_bytes.data());
  }
  ValueRecord* held() { return reinterpret_cast<ValueRecord*>(held_bytes.data()); }
  ValueRecord* held2() { return reinterpret_cast<ValueRecord*>(held2_bytes.data()); }
};

Fixture g_fix;
LocalProbe* g_frame_watch = nullptr;   // the frame object, captured from the first dispatch
ValueRecord* g_held = nullptr;          // what the frame's leading word points at

// ---------------------------------------------------------------------------
// observation plumbing
// ---------------------------------------------------------------------------

struct Observation {
  std::string what;
  const void* ecx;
  Word arg0;
  Word arg1;
  Word arg2;
  unsigned char frame[0x18];
  unsigned char receiver[0x818];
  unsigned char held[sizeof(ValueRecord)];
  bool have_frame;
};

std::vector<Observation> g_trace;

void record(const char* what, const void* ecx, Word a0 = 0, Word a1 = 0, Word a2 = 0) {
  Observation o{};
  o.what = what;
  o.ecx = ecx;
  o.arg0 = a0;
  o.arg1 = a1;
  o.arg2 = a2;
  o.have_frame = (g_frame_watch != nullptr);
  if (o.have_frame) {
    std::memcpy(o.frame, g_frame_watch, sizeof(o.frame));
  } else {
    std::memset(o.frame, 0, sizeof(o.frame));
  }
  std::memcpy(o.receiver, g_fix.receiver_bytes.data(), sizeof(o.receiver));
  if (g_held != nullptr) {
    std::memcpy(o.held, g_held, sizeof(o.held));
  } else {
    std::memset(o.held, 0, sizeof(o.held));
  }
  g_trace.push_back(o);
}

// -- observer behaviour, all resettable -------------------------------------

bool g_probe_answers_yes = true;      // 0x00f9b815: the +0x24 dispatch's return byte
bool g_probe_fills_held = true;       // whether it publishes the held pointer
Word g_probe_held_value = 0;          // value it puts in the frame's leading dword
Word g_frame12_decoy = 0;             // extra decoy it puts at frame+0x12
bool g_slot080_swaps_object = false;   // 0x00f9b844 re-points receiver+0x28
std::uint8_t g_refill_frame10 = 0;    // what the +0x14 dispatch puts at record+0x10 (frame+0x14)
std::uint8_t g_refill_frame0c = 0;    // decoy at record+0x0c, the wrong depth
std::uint8_t g_refill_frame0e = 0;    // decoy at record+0x0e, inside the type word
bool g_refill_touches_frame04 = true; // whether it also stamps frame+0x04
Word g_resolve_mode = 0;              // 0 -> return g_held, 1 -> return &g_held's leading dword
Word g_factory_args[3] = {0, 0, 0};
Word g_factory_result = 0xa5a5a5a5u;
std::uint8_t g_bind_result = 0;

// -- the three indirect transfers -------------------------------------------

void PKG_SW1_00F9B7F0_THISCALL observe_slot080(Receiver* receiver) {
  record("slot+0x80", receiver);
  if (g_slot080_swaps_object) {
    // The decoy for a model that caches the gate word instead of re-reading it
    // at 0x00f9b846 and 0x00f9b88c. A DIFFERENT object, not a null one: a null
    // would fault the dispatch the listing performs, and the point of the case
    // is which pointer the body carries forward, not what happens on a crash.
    *recon::word_at(receiver, recon::kReceiverObjectDisplacement) =
        static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_fix.object2()));
  }
}

std::uint8_t PKG_SW1_00F9B7F0_THISCALL observe_slot024(
    DispatchObject* object, Word property_id, LocalProbe* out) {
  record("slot+0x24", object, property_id,
         static_cast<Word>(reinterpret_cast<std::uintptr_t>(out)));
  if (g_frame_watch == nullptr) {
    g_frame_watch = out;  // the frame object, for every later snapshot
  }
  g_held = reinterpret_cast<ValueRecord*>(g_probe_held_value);
  if (g_probe_fills_held) {
    *recon::word_at(out, recon::kRecordLeadingDisplacement) = g_probe_held_value;
  }
  *recon::halfword_at(out, 0x12) = static_cast<std::uint16_t>(g_frame12_decoy);
  return g_probe_answers_yes ? 1u : 0u;
}

void PKG_SW1_00F9B7F0_THISCALL observe_slot014_alt(
    DispatchObject* object, Word property_id, ValueRecord* out) {
  record("slot+0x14[alt]", object, property_id,
         static_cast<Word>(reinterpret_cast<std::uintptr_t>(out)));
  if (out != nullptr) {
    *(reinterpret_cast<std::uint8_t*>(out) + recon::kGuardRecordOffset) =
        g_refill_frame10;
  }
}

void PKG_SW1_00F9B7F0_THISCALL observe_slot014(
    DispatchObject* object, Word property_id, ValueRecord* out) {
  record("slot+0x14", object, property_id,
         static_cast<Word>(reinterpret_cast<std::uintptr_t>(out)));
  if (g_frame_watch != nullptr) {
    std::uint8_t* const record_base = static_cast<std::uint8_t*>(
        recon::interior(g_frame_watch, recon::kRecordOffsetInsideFrame));
    *(record_base + recon::kGuardRecordOffset) = g_refill_frame10;
    // Wrong-depth decoy, four bytes below the flags word the body tests.
    *(record_base + recon::kGuardRecordOffset - 4) = g_refill_frame0c;
  }
  if (out != nullptr) {
    // The wrong-depth decoy, four bytes up from the byte the body must test.
    *(reinterpret_cast<std::uint8_t*>(out) + recon::kFlagsStoreRecordOffset - 2) =
        g_refill_frame0e;
    if (g_refill_touches_frame04) {
      *recon::word_at(out, recon::kRecordLeadingDisplacement) = 0xfeedfaceu;
    }
  }
}

// -- decoy entries installed at the neighbouring slots (group E) -------------

void PKG_SW1_00F9B7F0_THISCALL decoy_slot080(Receiver* r) {
  (void)r;
  record("decoy", nullptr);
}
std::uint8_t PKG_SW1_00F9B7F0_THISCALL decoy_slot024(
    DispatchObject* o, Word p, LocalProbe* out) {
  (void)o;
  (void)p;
  (void)out;
  record("decoy", nullptr);
  return 0;
}
void PKG_SW1_00F9B7F0_THISCALL decoy_slot014(
    DispatchObject* o, Word p, ValueRecord* out) {
  (void)o;
  (void)p;
  (void)out;
  record("decoy", nullptr);
}

// -- the five direct callees, all observers --------------------------------

extern "C" void* PKG_SW1_00F9B7F0_THISCALL value_resolve_0041ea00(
    ValueRecord* receiver) {
  record("value_resolve_0041ea00", receiver);
  // mode 0: 0x0041ea00's own `return this` shape (0x0041ea47).
  // mode 1: its `return *(dword*)this` shape (0x0041ea30) -- which is what makes
  //         the caller's MOV EDI,[EAX] load the record's own leading word.
  // mode 2: a DIFFERENT record, so "used the return value" and "loaded through
  //         the return value" produce different candidates. This is the only
  //         mode that can tell the two apart, because modes 0 and 1 agree.
  if (g_resolve_mode == 0) return static_cast<void*>(g_held);
  if (g_resolve_mode == 1) {
    return recon::interior(g_held, recon::kRecordLeadingDisplacement);
  }
  return static_cast<void*>(g_fix.held2());
}

extern "C" ValueRecord* PKG_SW1_00F9B7F0_THISCALL value_assign_00427fd0(
    ValueRecord* destination, const Word* source) {
  record("value_assign_00427fd0", destination,
         static_cast<Word>(reinterpret_cast<std::uintptr_t>(source)));
  // Mirror the callee's own documented effect so later snapshots look right. The
  // three displacements are the ones its own listing prints (0x00428016 writes the
  // leading dword, 0x00428020 the word at +0x12, 0x0042802b/0x00428031 the word at
  // +0x10), so the mirror reaches them by name rather than by a member.
  *recon::word_at(destination, recon::kRecordLeadingDisplacement) = *source;
  *recon::halfword_at(destination, recon::kRecordTypeDisplacement) = 0x000a;
  *recon::halfword_at(destination, recon::kRecordFlagsDisplacement) =
      static_cast<std::uint16_t>(
          *recon::halfword_at(destination, recon::kRecordFlagsDisplacement) & 0x2u);
  return destination;
}

extern "C" void PKG_SW1_00F9B7F0_THISCALL editor_query_clear_flags_0093db80(
    ValueRecord* receiver, std::uint8_t argument) {
  record("editor_query_clear_flags_0093db80", receiver, argument);
}

extern "C" Word PKG_SW1_00F9B7F0_CDECL factory_lookup_006b1f90(
    Word property_id, Word second, Word third) {
  record("factory_lookup_006b1f90", nullptr, property_id, second, third);
  g_factory_args[0] = property_id;
  g_factory_args[1] = second;
  g_factory_args[2] = third;
  return g_factory_result;
}

extern "C" std::uint8_t PKG_SW1_00F9B7F0_CDECL object_bind_006b4b60(
    Word token, DispatchObject* object) {
  record("object_bind_006b4b60", object, token);
  return g_bind_result;
}

// ---------------------------------------------------------------------------
// fixture setup
// ---------------------------------------------------------------------------

// `object_at_28` selects whether the receiver's +0x28 word is the fixture's
// object or null; `word_at_814` is the receiver's own +0x814 word; `hold_type`
// is the halfword at held+0x12 and `hold_first` the dword at held+0x00.
struct Setup {
  bool object_at_28 = true;
  Word word_at_814 = 0x11111111u;
  std::uint16_t hold_type = 0x000a;
  Word hold_first = 0xdeadbeefu;
  Word hold2_first = 0x5a5a5a5au;  // what a SECOND record behind the resolve return holds
  bool install_decoy_slots = false;
};

void setup(const Setup& s) {
  g_trace.clear();
  g_frame_watch = nullptr;
  g_held = nullptr;

  g_probe_answers_yes = true;
  g_probe_fills_held = true;
  g_slot080_swaps_object = false;
  g_probe_held_value = 0;
  g_frame12_decoy = 0;
  g_slot080_swaps_object = false;
  g_refill_frame10 = 0;
  g_refill_frame0c = 0;
  g_refill_frame0e = 0;
  g_refill_touches_frame04 = true;
  g_resolve_mode = 0;
  g_factory_result = 0xa5a5a5a5u;
  g_bind_result = 0;

  g_fix.receiver_bytes.fill(0);
  g_fix.object_bytes.fill(0);
  g_fix.object2_bytes.fill(0);
  g_fix.held_bytes.fill(0);
  g_fix.held2_bytes.fill(0);
  g_fix.spare.fill(0);
  std::memset(&g_fix.table, 0, sizeof(g_fix.table));
  std::memset(&g_fix.table2, 0, sizeof(g_fix.table2));
  // The second object's table answers the +0x14 slot with a distinguishable
  // observer, so "which object did the body carry forward" is observable.
  g_fix.table2.set(0x14, reinterpret_cast<void*>(observe_slot014_alt));
  g_fix.table2.set(0x24, reinterpret_cast<void*>(decoy_slot024));
  g_fix.table2.set(0x80, reinterpret_cast<void*>(decoy_slot080));

  g_fix.table.set(0x24, reinterpret_cast<void*>(observe_slot024));
  g_fix.table.set(0x14, reinterpret_cast<void*>(observe_slot014));
  g_fix.table.set(0x80, reinterpret_cast<void*>(observe_slot080));
  if (s.install_decoy_slots) {
    // Neighbouring slots. None of them may ever be entered.
    g_fix.table.set(0x20, reinterpret_cast<void*>(decoy_slot024));
    g_fix.table.set(0x28, reinterpret_cast<void*>(decoy_slot024));
    g_fix.table.set(0x10, reinterpret_cast<void*>(decoy_slot014));
    g_fix.table.set(0x18, reinterpret_cast<void*>(decoy_slot014));
    g_fix.table.set(0x7c, reinterpret_cast<void*>(decoy_slot080));
    g_fix.table.set(0x84, reinterpret_cast<void*>(decoy_slot080));
  }

  *recon::word_at(g_fix.receiver_bytes.data(), 0x00) =
      reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_fix.table));
  *recon::word_at(g_fix.object_bytes.data(), 0x00) =
      reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_fix.table));
  *recon::word_at(g_fix.object2_bytes.data(), 0x00) =
      reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(&g_fix.table2));
  *recon::word_at(g_fix.receiver_bytes.data(), 0x28) =
      s.object_at_28 ? reinterpret_cast<Word>(
                           reinterpret_cast<std::uintptr_t>(g_fix.object_bytes.data()))
                     : 0u;
  *recon::word_at(g_fix.receiver_bytes.data(), 0x814) = s.word_at_814;
  // Decoys at the neighbouring receiver displacements, all distinct and all
  // different from the two the body must use.
  *recon::word_at(g_fix.receiver_bytes.data(), 0x24) = 0xdead0024u;
  *recon::word_at(g_fix.receiver_bytes.data(), 0x2c) = 0xdead002cu;
  *recon::word_at(g_fix.receiver_bytes.data(), 0x810) = 0xdead0810u;
  // The modelled receiver ends at +0x817, so there is no +0x818 to decoy: the
  // bytes immediately after it are the fixture's own second object, and that is
  // where the E7 re-point decoy lives instead.
  // Bytes above the modelled receiver, so an over-read would be visible.
  g_fix.spare.fill(0x5a);

  g_held = g_fix.held();
  *recon::halfword_at(g_held, recon::kRecordTypeDisplacement) = s.hold_type;
  *recon::word_at(g_held, recon::kRecordLeadingDisplacement) = s.hold_first;
  *recon::halfword_at(g_fix.held2(), recon::kRecordTypeDisplacement) = 0x000a;
  *recon::word_at(g_fix.held2(), recon::kRecordLeadingDisplacement) = s.hold2_first;
  g_resolve_mode = 0;
  g_probe_held_value =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_held));
}

void run() { recon::re_00f9b7f0(g_fix.receiver()); }

// ---------------------------------------------------------------------------
// helpers over the trace
// ---------------------------------------------------------------------------

std::size_t count(const char* what) {
  std::size_t n = 0;
  for (const auto& o : g_trace) {
    if (o.what == what) ++n;
  }
  return n;
}

const Observation* find(const char* what) {
  for (const auto& o : g_trace) {
    if (o.what == what) return &o;
  }
  return nullptr;
}

bool any_decoy() { return count("decoy") != 0; }

std::uint16_t frame_half(const Observation& o, std::size_t d) {
  std::uint16_t v = 0;
  std::memcpy(&v, o.frame + d, sizeof(v));
  return v;
}
std::uint8_t frame_byte(const Observation& o, std::size_t d) { return o.frame[d]; }
Word frame_word(const Observation& o, std::size_t d) {
  Word v = 0;
  std::memcpy(&v, o.frame + d, sizeof(v));
  return v;
}
std::string joined() {
  std::string s;
  for (std::size_t i = 0; i < g_trace.size(); ++i) {
    if (i != 0) s += ",";
    s += g_trace[i].what;
  }
  return s.empty() ? std::string("<none>") : s;
}

// ---------------------------------------------------------------------------
// A -- frame facts
// ---------------------------------------------------------------------------

void test_frame_facts() {
  check_eq_u32(sizeof(ValueRecord), 0x14, "A: ValueRecord is 0x14 bytes");
  check_eq_u32(sizeof(LocalProbe), 0x18, "A: LocalProbe is 0x18 bytes");
  check_eq_u32(sizeof(Receiver), 0x818, "A: Receiver is 0x818 bytes");
  check_eq_u32(recon::kLocalDisplacement, 0x18, "A: frame object at entry-0x18");
  check_eq_u32(recon::kSavedEsiDisplacement, 0x1c, "A: saved ESI at entry-0x1c");
  check_eq_u32(recon::kSavedEdiDisplacement, 0x20, "A: saved EDI at entry-0x20");
  check_eq_u32(recon::kSavedEbxDisplacement, 0x24, "A: saved EBX at entry-0x24");
  check_eq_u32(recon::kFrameTotalDisplacement, 0x24, "A: epilogue consumes 0x24");

  check_eq_u32(recon::kAssignReceiverFrameOffset, 0x04,
               "A: 0x00427fd0 gets frame+0x04 = entry-0x14");
  check_eq_u32(recon::kQueryReceiverFrameOffset, 0x04,
               "A: 0x0093db80 gets the SAME frame+0x04 record as 0x00427fd0");
  check_eq_u32(recon::kRefillOutFrameOffset, 0x04,
               "A: the +0x14 dispatch's out argument is frame+0x04 = entry-0x14");
  check_eq_u32(recon::kLoadedPointerFrameOffset, 0x00,
               "A: the loaded word is the frame's leading dword");
  check_eq_u32(recon::kFlagsStoreFrameOffset, 0x14, "A: 0x02 lands at frame+0x14");
  check_eq_u32(recon::kTypeStoreFrameOffset, 0x16, "A: 0x0a lands at frame+0x16");
  check_eq_u32(recon::kGuardByteFrameOffset, 0x14, "A: guard byte is frame+0x14");
  check_eq_u32(recon::kAssignReceiverEntryOffset, 0x14, "A: 0x00427fd0 at entry-0x14");
  check_eq_u32(recon::kQueryReceiverEntryOffset, 0x14, "A: 0x0093db80 at entry-0x14");
  check_eq_u32(recon::kLoadedPointerEntryOffset, 0x18, "A: the loaded word is at entry-0x18");
  check_eq_u32(recon::kRefillOutEntryOffset, 0x14, "A: the +0x14 out argument is at entry-0x14");
  check_eq_u32(recon::kFlagsStoreEntryOffset, 0x04, "A: the 0x02 store is at entry-0x04");
  check_eq_u32(recon::kTypeStoreEntryOffset, 0x02, "A: the 0x0a store is at entry-0x02");
  check_eq_u32(recon::kGuardByteEntryOffset, 0x04, "A: the guard byte is at entry-0x04");
  check_eq_u32(recon::kGuardRecordOffset, 0x10, "A: the guard byte is record+0x10");
  check_eq_u32(recon::kFlagsStoreRecordOffset, 0x10, "A: the 0x02 store is record+0x10");
  check_eq_u32(recon::kTypeStoreRecordOffset, 0x12, "A: the 0x0a store is record+0x12");
  check(recon::kGuardRecordOffset == recon::kFlagsStoreRecordOffset,
        "A: the guard byte and the 0x02 store are the SAME word");

  check_eq_u32(recon::kReceiverDispatchDisplacement, 0x00, "A: receiver dispatch word at +0x00");
  check_eq_u32(recon::kReceiverObjectDisplacement, 0x28, "A: gate word at +0x28");
  check_eq_u32(recon::kReceiverWordDisplacement, 0x814, "A: compared word at +0x814");
  check_eq_u32(recon::kDispatchSlot024, 0x24, "A: first dispatch slot +0x24");
  check_eq_u32(recon::kDispatchSlot014, 0x14, "A: second dispatch slot +0x14");
  check_eq_u32(recon::kReceiverSlot080, 0x80, "A: receiver slot +0x80");

  check_eq_u32(recon::kPropertyIdA, 0x03ad556au, "A: property id literal");
  check_eq_u32(recon::kFactoryTagB, 0x031389b5u, "A: factory tag literal");
  check_eq_u32(recon::kTypeCodeTen, 0x0au, "A: type code literal");
  check_eq_u32(recon::kFlagsWordTwo, 0x0002u, "A: flags literal");
  check_eq_u32(recon::kGuardMaskFour, 0x04u, "A: guard mask literal");

  // K -- the cleanup arithmetic, summed both ways so the single self-consistent
  // reading is pinned rather than assumed.
  check_eq_u32(recon::kCleanupDispatch024, 8, "K: 0x00f9b813 removes 8");
  check_eq_u32(recon::kCleanupHelper41ea00, 0, "K: 0x0041ea00 removes 0 (ends C3)");
  check_eq_u32(recon::kCleanupValueAssign, 4, "K: 0x00427fd0 removes 4 (RET 0x4)");
  check_eq_u32(recon::kCleanupDispatch014, 8, "K: 0x00f9b878 removes 8");
  check_eq_u32(recon::kCleanupEditorQuery, 4, "K: 0x0093db80 removes 4 (RET 0x4)");
  check_eq_u32(recon::kCleanupFactoryLookup, 0, "K: 0x006b1f90 removes 0 (ends C3)");
  check_eq_u32(recon::kCleanupDispatch080, 0, "K: 0x00f9b844 removes 0");

  // Edge 1: 0x00f9b7fb -> 0x00f9b8ac. SUB 0x18 + PUSH ESI = 0x1c, and the
  // epilogue gives back 4 + 0x18.
  check_eq_u32(recon::kLocalDisplacement + 4, 0x1c, "K: entry edge arrives at 0x1c");
  // Edge 2: 0x00f9b813 contributes 0x28 - x, then 0x00f9b831 adds the fourth
  // saved word, and 0x00f9b8aa pops three: 0x28 - 8 + 4 = 0x24.
  check_eq_u32(0x28 - recon::kCleanupDispatch024 + 4, recon::kFrameTotalDisplacement,
               "K: the early-exit edge arrives at 0x24");
  // Edge 2b: the same edge through the type test, which calls 0x0041ea00 and
  // pushes nothing, so its 0 cleanup must not move the frame.
  check_eq_u32(recon::kCleanupHelper41ea00, 0, "K: 0x0041ea00 moves nothing");
  // Edge 3: the block 0x00f9b83a..0x00f9b8a7 pushes 36 bytes and retires 20 of
  // them itself, so its five callees must remove the other 16. The block also
  // leaves the frame 0x04 deeper than 0x00f9b838 found it, which POP EBX then
  // gives back -- the arithmetic is closed either way and the test pins the
  // numbers rather than the story.
  const int pushed = 4 /*EBX*/ + 8 /*slot +0x14*/ + 4 /*0x0093db80*/ +
                     12 /*0x006b1f90*/ + 8 /*0x006b4b60*/;
  const int retired = 4 /*ADD ESP,0x4*/ + 16 /*ADD ESP,0x10*/;
  const int removed = recon::kCleanupValueAssign + recon::kCleanupDispatch014 +
                      recon::kCleanupEditorQuery + recon::kCleanupFactoryLookup +
                      recon::kCleanupDispatch080;
  check_eq_u32(static_cast<unsigned>(pushed), 36u, "K: the slow block pushes 36");
  check_eq_u32(static_cast<unsigned>(retired), 20u, "K: the two ADDs retire 20");
  check_eq_u32(static_cast<unsigned>(pushed - retired), 16u,
               "K: 36 - 20 leaves 16 for the callees");
  check_eq_u32(static_cast<unsigned>(pushed - retired), static_cast<unsigned>(removed),
               "K: the five callees in the slow block remove exactly 16");
  check_eq_u32(static_cast<unsigned>(recon::kFrameTotalDisplacement + pushed - retired -
                                     removed),
               recon::kFrameTotalDisplacement,
               "K: the slow path arrives back at 0x24 with no residual");
}

// ---------------------------------------------------------------------------
// B -- the happy path
// ---------------------------------------------------------------------------

void test_happy_path() {
  Setup s;
  s.word_at_814 = 0x11111111u;
  s.hold_type = 0x000a;
  s.hold_first = 0xdeadbeefu;
  s.install_decoy_slots = true;
  setup(s);
  g_refill_frame10 = 0x04;  // the guard bit the body must find
  run();

  check(joined() == "slot+0x24,value_resolve_0041ea00,slot+0x80,value_assign_00427fd0,"
                    "slot+0x14,editor_query_clear_flags_0093db80,factory_lookup_006b1f90,"
                    "object_bind_006b4b60",
        ("B: call order, got " + joined()).c_str());
  check(!any_decoy(), "B: no neighbouring dispatch slot was entered");

  const Observation* probe = find("slot+0x24");
  check(probe != nullptr, "B: the +0x24 dispatch ran");
  if (probe != nullptr) {
    check(probe->ecx == static_cast<const void*>(g_fix.object()),
          "B: +0x24 ECX is the object at receiver+0x28");
    check_eq_u32(probe->arg0, 0x03ad556au, "B: +0x24 first argument is 0x03ad556a");
    check(probe->arg1 == static_cast<Word>(
                            reinterpret_cast<std::uintptr_t>(g_frame_watch)),
          "B: +0x24 second argument is the frame object itself");
  }

  const Observation* resolve = find("value_resolve_0041ea00");
  check(resolve != nullptr, "B: 0x0041ea00 ran");
  if (resolve != nullptr) {
    check(resolve->ecx == static_cast<const void*>(g_held),
          "B: 0x0041ea00 ECX is the word the dispatch published, dereferenced once");
    check(resolve->arg0 == 0 && resolve->arg1 == 0,
          "B: 0x0041ea00 was handed no stack words (ECX only)");
  }

  const Observation* v80 = find("slot+0x80");
  check(v80 != nullptr, "B: the receiver's +0x80 entry ran");
  if (v80 != nullptr) {
    check(v80->ecx == static_cast<const void*>(g_fix.receiver()),
          "B: +0x80 ECX is the receiver, not the object");
    check(frame_word(*v80, 0x14) != 2u,
          "B: the flags word is NOT yet 2 when the +0x80 entry is entered");
  }

  const Observation* assign = find("value_assign_00427fd0");
  check(assign != nullptr, "B: 0x00427fd0 ran");
  if (assign != nullptr) {
    check(reinterpret_cast<std::uintptr_t>(assign->ecx) ==
              reinterpret_cast<std::uintptr_t>(g_frame_watch) +
                  recon::kAssignReceiverFrameOffset,
          "B: 0x00427fd0 ECX is the frame object + 0x04, not the frame object");
    check(assign->arg0 == static_cast<Word>(
                             reinterpret_cast<std::uintptr_t>(
                                 recon::word_at(g_fix.receiver_bytes.data(), 0x814))),
          "B: 0x00427fd0's argument is the ADDRESS of receiver+0x814");
    check_eq_u32(frame_half(*assign, 0x16), 0x0au,
                 "B: record+0x12 is already 0x0a when 0x00427fd0 is entered");
    check_eq_u32(frame_half(*assign, 0x14), 0x2u,
                 "B: record+0x10 is already 0x0002 when 0x00427fd0 is entered");
    check_eq_u32(frame_word(*assign, 0x04), 0u,
                 "B: record+0x00 is still 0 when 0x00427fd0 is entered");
  }

  const Observation* refill = find("slot+0x14");
  check(refill != nullptr, "B: the +0x14 dispatch ran");
  if (refill != nullptr) {
    check(refill->ecx == static_cast<const void*>(g_fix.object()),
          "B: +0x14 ECX is the object at receiver+0x28");
    check_eq_u32(refill->arg0, 0x03ad556au,
                 "B: +0x14 first argument is the same 0x03ad556a");
    check(refill->arg1 ==
              static_cast<Word>(reinterpret_cast<std::uintptr_t>(g_frame_watch) +
                                recon::kAssignReceiverFrameOffset),
          "B: +0x14 second argument is the frame object + 0x04");
  }

  const Observation* query = find("editor_query_clear_flags_0093db80");
  check(query != nullptr, "B: 0x0093db80 ran under the guard");
  if (query != nullptr) {
    check(reinterpret_cast<std::uintptr_t>(query->ecx) ==
              reinterpret_cast<std::uintptr_t>(g_frame_watch) +
                  recon::kQueryReceiverFrameOffset,
          "B: 0x0093db80 ECX is the frame's +0x04 record, the one 0x00427fd0 got");
    check_eq_u32(query->arg0, 0u, "B: 0x0093db80's argument is the literal 0");
    check_eq_u32(frame_byte(*query, 0x14), 0x04u,
                 "B: the guard byte the body tested is still 0x04 at frame+0x14");
  }

  const Observation* factory = find("factory_lookup_006b1f90");
  check(factory != nullptr, "B: 0x006b1f90 ran");
  if (factory != nullptr) {
    check_eq_u32(factory->arg0, 0x031389b5u, "B: 0x006b1f90 first argument");
    check_eq_u32(factory->arg1, 0u, "B: 0x006b1f90 second argument is 0");
    check_eq_u32(factory->arg2, 0u, "B: 0x006b1f90 third argument is 0");
  }

  const Observation* bind = find("object_bind_006b4b60");
  check(bind != nullptr, "B: 0x006b4b60 ran");
  if (bind != nullptr) {
    check(bind->ecx == static_cast<const void*>(g_fix.object()),
          "B: 0x006b4b60's second argument is the object at receiver+0x28");
    check_eq_u32(bind->arg0, 0xa5a5a5a5u,
                 "B: 0x006b4b60's FIRST argument is 0x006b1f90's return, not the object");
  }
}

// ---------------------------------------------------------------------------
// C -- branch polarity, each edge both ways
// ---------------------------------------------------------------------------

void test_branch_polarity() {
  {  // C1: the +0x24 dispatch reports "no", and the receiver's +0x814 word is 0,
    // so the zeroed candidate matches and the body returns. Two facts at once:
    // the false return skips the type test, and the candidate really is 0 on
    // that path.
    Setup s;
    s.word_at_814 = 0u;
    setup(s);
    g_probe_answers_yes = false;
    run();
    check(joined() == "slot+0x24",
          ("C1: only the probe ran, got " + joined()).c_str());
  }
  {  // C1b: same, but +0x814 is NOT 0, so the zeroed candidate does not match
    // and the body carries on -- which is what a model that ignored the dispatch
    // answer would also do, so the pair C1/C1b is the real discriminator.
    Setup s;
    s.word_at_814 = 0x11111111u;
    setup(s);
    g_probe_answers_yes = false;
    run();
    check(count("value_resolve_0041ea00") == 0,
          "C1b: a false dispatch answer skips 0x0041ea00");
    check(count("slot+0x80") == 1,
          "C1b: the zeroed candidate 0 != 0x11111111, so the body continues");
  }
  {  // C2: the dispatch says yes but the type is not 0x0a, and +0x814 is 0.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_type = 0x000b;
    setup(s);
    run();
    check(joined() == "slot+0x24",
          ("C2: a non-0x0a type skips the resolve, got " + joined()).c_str());
  }
  {  // C2b: 0x0a one byte higher -- an off-by-one on the immediate.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_type = 0x0a00;
    setup(s);
    run();
    check(joined() == "slot+0x24",
          ("C2b: 0x0a00 is not 0x000a, got " + joined()).c_str());
  }
  {  // C2c: 0x0a with the low bit clear vs set is not the question, but 0x0a vs
    // 0x0b is, and so is the sign of the 16-bit compare: 0x800a is not 0x000a.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_type = 0x800a;
    setup(s);
    run();
    check(joined() == "slot+0x24",
          ("C2c: 0x800a != 0x000a under a plain 16-bit equality, got " + joined()).c_str());
  }
  {  // C3: the resolve result's member equals the receiver's +0x814 word.
    Setup s;
    s.word_at_814 = 0xdeadbeefu;
    s.hold_first = 0xdeadbeefu;
    setup(s);
    g_resolve_mode = 1;  // the callee returns the address of the held record's leading dword
    run();
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("C3: an equal candidate returns early, got " + joined()).c_str());
  }
  {  // C4: the gate word is null.
    Setup s;
    s.object_at_28 = false;
    setup(s);
    run();
    check(joined() == "<none>", ("C4: a null gate makes no call, got " + joined()).c_str());
  }
  {  // C5a: the guard bit is clear.
    Setup s;
    setup(s);
    g_refill_frame10 = 0x00;
    run();
    check(count("editor_query_clear_flags_0093db80") == 0,
          "C5a: a clear guard byte skips 0x0093db80");
  }
  {  // C5b: a DIFFERENT bit is set. The mask is 0x04 exactly, so this must skip.
    Setup s;
    setup(s);
    g_refill_frame10 = 0x02;
    run();
    check(count("editor_query_clear_flags_0093db80") == 0,
          "C5b: bit 0x0002 alone does not satisfy a mask of 0x04");
  }
  {  // C5c: the mask bit plus another bit.
    Setup s;
    setup(s);
    g_refill_frame10 = 0x06;
    run();
    check(count("editor_query_clear_flags_0093db80") == 1,
          "C5c: 0x06 contains 0x04 and does satisfy the mask");
  }
}

// ---------------------------------------------------------------------------
// D -- pointer level
// ---------------------------------------------------------------------------

void test_pointer_level() {
  {  // D1: the frame's OWN +0x12 is wrong but the held record's is 0x0a. The
    // body must still take the branch, which it cannot do by reading frame+0x12.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_first = 0u;  // so the candidate the resolve produces is 0 and matches
    s.hold_type = 0x000a;
    setup(s);
    g_frame12_decoy = 0x7777;  // planted at frame+0x12 by the dispatch
    run();
    check(count("value_resolve_0041ea00") == 1,
          "D1: the type word is read from the published pointer, not from frame+0x12");
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("D1: and then the zeroed candidate matches, got " + joined()).c_str());
  }
  {  // D2: the frame's own +0x12 IS 0x0a but the held record's is not. The body
    // must NOT take the branch: this is the one-level reading being refuted.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_type = 0x000b;
    setup(s);
    g_frame12_decoy = 0x000a;
    run();
    check(count("value_resolve_0041ea00") == 0,
          "D2: a 0x000a at frame+0x12 must not stand in for the held record's");
    check(joined() == "slot+0x24", ("D2: nothing else ran, got " + joined()).c_str());
  }
  {  // D3: two distinct records, so a model that confuses the published pointer
    // with the frame address or with the dispatch's own table cannot pass.
    Setup s;
    s.word_at_814 = 0u;
    s.hold_type = 0x0010;  // the other type code 0x0041ea00 knows
    setup(s);
    run();
    check(count("value_resolve_0041ea00") == 0,
          "D3: type 0x0010 is not 0x000a even though the callee accepts it");
    check(joined() == "slot+0x24", ("D3: nothing else ran, got " + joined()).c_str());
  }
  {  // D4: the published pointer is the exact address the resolve observer saw.
    Setup s;
    setup(s);
    run();
    const Observation* resolve = find("value_resolve_0041ea00");
    check(resolve != nullptr && resolve->ecx == static_cast<const void*>(g_held),
          "D4: the resolve receiver is the published word itself");
  }
}

// ---------------------------------------------------------------------------
// E -- displacements, with decoys planted at every neighbour
// ---------------------------------------------------------------------------

void test_displacements() {
  {  // E1: the compare is against +0x814 and not its neighbours.
    Setup s;
    s.word_at_814 = 0x11111111u;
    s.hold_first = 0xdead0810u;  // equals the +0x810 decoy
    setup(s);
    g_resolve_mode = 1;
    run();
    check(joined() != "slot+0x24,value_resolve_0041ea00",
          "E1: a candidate equal to the +0x810 decoy does not return early");
    check(count("slot+0x80") == 1, "E1: the +0x814 compare missed the decoy at +0x810");
  }
  {  // E2: the gate is +0x28, not +0x24 or +0x2c.
    Setup s;
    s.object_at_28 = true;
    setup(s);
    run();
    check(count("slot+0x24") == 1, "E2: the gate word really is at +0x28");
  }
  {  // E3: a null +0x28 with a live +0x24 decoy must return immediately.
    Setup s;
    s.object_at_28 = false;
    setup(s);
    run();
    check(joined() == "<none>",
          ("E3: the +0x24 receiver decoy is not a fallback, got " + joined()).c_str());
  }
  {  // E4: the guard byte is the record's flags word at +0x10. The +0x14
    // dispatch plants 0x04 in the WRONG places -- +0x0c and +0x0e, the latter
    // being frame+0x12, where a model that measured from the frame object rather
    // than from the record would look -- and clears the right one.
    Setup s;
    setup(s);
    g_refill_frame10 = 0x00;
    g_refill_frame0c = 0x04;
    g_refill_frame0e = 0x04;
    run();
    check(count("editor_query_clear_flags_0093db80") == 0,
          "E4: 0x04 at record+0x0c and record+0x0e does not satisfy a test of record+0x10");
    check(count("slot+0x14") == 1, "E4: the +0x14 dispatch did run");
  }
  {  // E5: and the converse.
    Setup s;
    setup(s);
    g_refill_frame10 = 0x04;
    g_refill_frame0c = 0x00;
    g_refill_frame0e = 0x00;
    run();
    check(count("editor_query_clear_flags_0093db80") == 1,
          "E5: 0x04 at record+0x10 does satisfy the test");
  }
  {  // E6: the two dispatches write DIFFERENT places. The +0x24 dispatch fills
    // the frame's leading word; the +0x14 dispatch fills frame+0x04.
    Setup s;
    setup(s);
    g_refill_touches_frame04 = true;
    run();
    const Observation* refill = find("slot+0x14");
    check(refill != nullptr && frame_word(*refill, 0x04) == s.word_at_814,
          "E6: record+0x00 already holds the receiver's +0x814 word, copied by 0x00427fd0");
  }
  {  // E7: the gate word is RE-READ after the +0x80 entry, twice. The decoy
    // entry re-points receiver+0x28 at a second object whose +0x14 slot is a
    // different observer, so a model that cached the first word is caught.
    // A null is deliberately NOT used as the decoy: the listing dereferences the
    // re-read word immediately, so a null would fault, and the point of the case
    // is which pointer the body carries forward, not what happens on a crash.
    Setup s;
    setup(s);
    g_slot080_swaps_object = true;
    g_refill_frame10 = 0x04;
    run();
    check(count("slot+0x14") == 0,
          "E7: the first object's +0x14 entry was not used after the re-point");
    const Observation* alt = find("slot+0x14[alt]");
    const Observation* bind = find("object_bind_006b4b60");
    check(alt != nullptr, "E7: the RE-READ object answered the +0x14 dispatch");
    if (alt != nullptr) {
      check(alt->ecx == static_cast<const void*>(g_fix.object2()),
            "E7: the +0x14 dispatch received the re-read gate word");
      check_eq_u32(alt->arg0, 0x03ad556au, "E7: the literal is unchanged by the re-read");
    }
    check(bind != nullptr && bind->ecx == static_cast<const void*>(g_fix.object2()),
          "E7: 0x006b4b60 also received the re-read gate word");
    check(!any_decoy(), "E7: no neighbouring slot of the second table was entered");
  }
}

// ---------------------------------------------------------------------------
// F -- constants
// ---------------------------------------------------------------------------

void test_constants() {
  Setup s;
  setup(s);
  g_refill_frame10 = 0x04;
  run();
  const Observation* probe = find("slot+0x24");
  const Observation* refill = find("slot+0x14");
  const Observation* factory = find("factory_lookup_006b1f90");
  check(probe != nullptr && refill != nullptr && factory != nullptr,
        "F: the three argument-carrying transfers all ran");
  if (probe != nullptr && refill != nullptr && factory != nullptr) {
    check_eq_u32(probe->arg0, 0x03ad556au, "F: 0x03ad556a, not 0x03ad556b");
    check_eq_u32(refill->arg0, probe->arg0, "F: both dispatches carry the SAME literal");
    check_eq_u32(factory->arg0, 0x031389b5u, "F: 0x031389b5, not 0x031389b4");
  }
  const Observation* assign = find("value_assign_00427fd0");
  check(assign != nullptr && frame_half(*assign, 0x16) == 0x0au &&
            frame_half(*assign, 0x14) == 0x2u,
        "F: the two pre-stores are 0x0a at record+0x12 and 0x0002 at record+0x10");
}

// ---------------------------------------------------------------------------
// G -- equality, not ordering, and not signedness
// ---------------------------------------------------------------------------

void test_equality_not_ordering() {
  {  // G1: signed-negative against signed-positive. A model that used `<` or a
    // signed compare would return early here; CMP/JZ cannot.
    Setup s;
    s.hold_first = 0x80000000u;
    s.word_at_814 = 0x7fffffffu;
    setup(s);
    g_resolve_mode = 1;
    run();
    check(count("slot+0x80") == 1,
          "G1: 0x80000000 != 0x7fffffff, so the body does not return early");
  }
  {  // G2: the mirror image.
    Setup s;
    s.hold_first = 0x7fffffffu;
    s.word_at_814 = 0x80000000u;
    setup(s);
    g_resolve_mode = 1;
    run();
    check(count("slot+0x80") == 1, "G2: the mirror case also continues");
  }
  {  // G3: bit-identical patterns DO return early, signed or not.
    Setup s;
    s.hold_first = 0xffffffffu;
    s.word_at_814 = 0xffffffffu;
    setup(s);
    g_resolve_mode = 1;
    run();
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("G3: 0xffffffff == 0xffffffff returns early, got " + joined()).c_str());
  }
}

// ---------------------------------------------------------------------------
// H -- the resolve result is dereferenced, not used
// ---------------------------------------------------------------------------

void test_resolve_result_is_dereferenced() {
  {  // Mode 0: 0x0041ea00 returns the record itself, so the candidate is the
    // record's leading word. Matching +0x814 with THAT value returns early.
    Setup s;
    s.hold_first = 0xaaaaaaaau;
    s.word_at_814 = 0xaaaaaaaau;
    setup(s);
    g_resolve_mode = 0;
    run();
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("H0: the candidate is the record's leading word, got " + joined()).c_str());
  }
  {  // Mode 1: the same record, but the callee returns the address OF that word
    // (0x0041ea00's `return *(dword*)this` shape). The candidate is the same
    // value, which is exactly why this mode cannot discriminate -- the
    // reconstruction is right to treat 0x0041ea00's two shapes as equivalent
    // here, and the test says so rather than pretending otherwise.
    Setup s;
    s.hold_first = 0xaaaaaaaau;
    s.word_at_814 = 0xaaaaaaaau;
    setup(s);
    g_resolve_mode = 1;
    run();
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("H1: both of 0x0041ea00's shapes give the same candidate, got " + joined()).c_str());
  }
  {  // Mode 2: the callee returns a DIFFERENT record. If the body USED the return
    // value as the candidate it would compare the record's address against
    // +0x814 and not match; because it LOADS through the return value it
    // compares that record's leading word. Setting +0x814 to the second record's
    // leading word therefore returns early -- and only a load-through model does.
    Setup s;
    s.hold_first = 0xaaaaaaaau;
    s.hold2_first = 0xaaaaaaaau;
    s.word_at_814 = 0xaaaaaaaau;
    setup(s);
    g_resolve_mode = 2;
    run();
    check(joined() == "slot+0x24,value_resolve_0041ea00",
          ("H2: the return value is dereferenced, not used, got " + joined()).c_str());
    const Observation* resolve = find("value_resolve_0041ea00");
    check(resolve != nullptr && resolve->ecx == static_cast<const void*>(g_held),
          "H2: the resolve receiver was still the PUBLISHED record, not the returned one");
  }
  {  // Mode 2b: the same, but +0x814 holds the first record's leading word, which
    // the second record does not carry. A load-through model must continue.
    Setup s;
    s.hold_first = 0xaaaaaaaau;
    s.hold2_first = 0xbbbbbbbbu;
    s.word_at_814 = 0xaaaaaaaau;
    setup(s);
    g_resolve_mode = 2;
    run();
    check(count("slot+0x80") == 1,
          "H2b: a candidate from the returned record does not match the first record's word");
  }
}

// ---------------------------------------------------------------------------
// I -- write ordering, observed from inside each callee
// ---------------------------------------------------------------------------

void test_write_ordering() {
  Setup s;
  setup(s);
  g_refill_frame10 = 0x04;
  run();

  const Observation* assign = find("value_assign_00427fd0");
  const Observation* refill = find("slot+0x14");
  const Observation* query = find("editor_query_clear_flags_0093db80");
  const Observation* bind = find("object_bind_006b4b60");
  check(assign != nullptr && refill != nullptr && query != nullptr && bind != nullptr,
        "I: the four orderable transfers all ran");
  if (assign == nullptr || refill == nullptr || query == nullptr || bind == nullptr) {
    return;
  }
  check_eq_u32(frame_word(*assign, 0x04), 0u,
               "I: record+0x00 is unwritten when 0x00427fd0 is entered");
  check_eq_u32(frame_word(*refill, 0x04), s.word_at_814,
               "I: 0x00427fd0's store of the receiver's +0x814 word is visible to the +0x14 dispatch");
  check_eq_u32(frame_byte(*query, 0x14), 0x04u,
               "I: the +0x14 dispatch's flags byte is visible to 0x0093db80");
  check_eq_u32(frame_byte(*bind, 0x14), 0x04u,
               "I: and still visible at 0x006b4b60");
  check_eq_u32(frame_half(*bind, 0x16), 0x0au,
               "I: 0x00427fd0's type store is visible at 0x006b4b60");
  check_eq_u32(frame_word(*bind, 0x04), 0xfeedfaceu,
               "I: the +0x14 dispatch overwrote record+0x00, and that is what the tail sees");
}

// ---------------------------------------------------------------------------
// J -- the receiver is never written
// ---------------------------------------------------------------------------

void test_receiver_immutable() {
  Setup s;
  setup(s);
  g_refill_frame10 = 0x04;
  const std::array<unsigned char, 0x818> before = g_fix.receiver_bytes;
  run();
  bool identical = std::memcmp(before.data(), g_fix.receiver_bytes.data(), before.size()) == 0;
  check(identical, "J: not one byte of the receiver changed on the full path");
  if (!identical) {
    for (std::size_t i = 0; i < before.size(); ++i) {
      if (before[i] != g_fix.receiver_bytes[i]) {
        std::printf("      first difference at +0x%zx: 0x%02x -> 0x%02x\n", i,
                    before[i], g_fix.receiver_bytes[i]);
        break;
      }
    }
  }
  // And the snapshots the observers took agree with that.
  for (const auto& o : g_trace) {
    if (!o.have_frame) continue;
    check(std::memcmp(before.data(), o.receiver, before.size()) == 0,
          "J: the receiver was already untouched when an observer was entered");
  }
}

}  // namespace

int main() {
  test_frame_facts();
  test_happy_path();
  test_branch_polarity();
  test_pointer_level();
  test_displacements();
  test_constants();
  test_equality_not_ordering();
  test_resolve_result_is_dereferenced();
  test_write_ordering();
  test_receiver_immutable();

  std::printf("%d checks, %d failures\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
