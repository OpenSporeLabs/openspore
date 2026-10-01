// PKG-SWARM-W2-00C33580 -- VA 0x00c33580
// Behavioural model test for FUN_00c33580.
//
// All ten direct callees are defined here as OBSERVERS, so the test sees every
// transfer the reconstruction makes -- which callee, in which order, with which
// ECX receiver, with which stack arguments, and what the memory looks like at
// the moment of the call. Each observer also decides what it does to memory,
// which is what makes the write-ordering and the write-thru-pointer claims
// testable rather than merely asserted.
//
// WHAT IS ASSERTED, and where each claim comes from:
//
//   * the five early exits and the exact call trace of each one
//     (0x00c3358f, 0x00c335a4, 0x00c335c3, 0x00c335d2, 0x00c335e7, 0x00c335f9);
//   * the sentinel: `CMP EAX,-0x1` at 0x00c3358c and 0x00c335cf, so a handle of
//     0xffffffff exits BEFORE any call and a handle of 0 does not;
//   * the argument order of the two-step lookup: the handle pushed at
//     0x00c33595 is 0x00ba6d80's ARGUMENT and 0x00b3d2a0's return is its
//     RECEIVER (0x00b3d2a0 is `mov eax,ds:0x167eae4 ; ret`, which pops
//     nothing; 0x00ba6d80 reads [esp+0x4] and ends in `ret 0x4`);
//   * that the handle is RE-READ at 0x00c335c9 rather than reused: an observer
//     that rewrites receiver+0xb0 during the first lookup must be visible to
//     the second one;
//   * that the gate is the record's FIRST word and is a VALUE: 0x00c335b1 keeps
//     it in ECX and 0x00c335c1 `TEST ECX,ECX` tests the register, and it is
//     never stored -- a pointer-looking gate must be treated as a value, and a
//     non-zero gate must not be dereferenced;
//   * that the two stored words are the record's words 1 and 2, into the
//     twelve-byte block at FR+0x08 whose BASE is what 0x00c32cd0 receives;
//   * that 0x0c, 0x14 and 0x3c are FORMED ADDRESSES, never values stored there;
//   * that the map key slot holds 2 at the moment of the call, and that the
//     out-parameter is the FIRST stack word while the key is the second;
//   * the map result's POINTER LEVEL: the callee returns the address of the
//     out-parameter (0x00e5c7b2) and 0x00c33653 dereferences exactly once;
//   * that the word at node+0x14 is passed AS A POINTER and not dereferenced;
//   * that the range guard is `(end-begin) & 0xfffffffe > 2` compared SIGNED,
//     that `end` is the block's element 2, that `begin` is the element this body
//     never writes, and that the null test comes after the range test;
//   * that nothing is ever written through the receiver (written_through 0).
//
// WHAT IS NOT ASSERTED, and why:
//
//   * the return value. The single RET is reached with EAX holding six
//     different things depending on the path (a null pointer, a data word, the
//     sentinel, a node word, 0, the begin pointer), so there is no coherent
//     value to assert and the model declares none;
//   * that the body's behaviour depends on the twelve-byte block. The callee is
//     an observer, and this body reads the block back nowhere, so the test
//     checks the INDEPENDENCE (a distinctive payload does not change the trace)
//     rather than a value the machine never reads;
//   * what the twelve-byte block MEANS. 0x00c32cd0 writes three floats into it
//     and this body reads none of them;
//   * the value at FR+0x14 on the original. The test plants it; the machine
//     reads whatever the caller's frame held and nothing in this body writes it,
//     so the test pins the READ, never the value;
//   * that 0x00e5c780 really finds key 2. The reconstruction passes the key;
//     whether the map contains it is the callee's business, so the observer
//     decides. No null check on the map result is asserted because the machine
//     has none and driving a null one would be undefined behaviour rather than
//     a refutation.
//
// THE REFUTATION INVENTORY -- each case below is aimed at one named wrong
// reconstruction, and three whole MUTANT bodies at the end are complete copies
// of the reconstruction with exactly one thing wrong, each of which the
// corresponding case is asserted to CATCH.

#include "sw2_00c33580_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w2_00c33580 {
namespace {

// -- call trace ---------------------------------------------------------------
enum CalleeId {
  kGet = 1,
  kLookup,
  kRecordSlot,
  kChild,
  kColor,
  kArrayCheck,
  kListSync,
  kMapFind,
  kTextEmit,
  kDestroy,
  kIdCount
};

struct Call {
  int id;
  const void* ecx;
  Word arg0;
  Word arg1;
};

Call g_calls[kIdCount * 4];
int g_call_count;
int g_lookup_calls;
int g_failures;
bool g_report = true;

void record(int id, const void* ecx, Word arg0, Word arg1) {
  if (g_call_count < static_cast<int>(sizeof(g_calls) / sizeof(g_calls[0]))) {
    g_calls[g_call_count].id = id;
    g_calls[g_call_count].ecx = ecx;
    g_calls[g_call_count].arg0 = arg0;
    g_calls[g_call_count].arg1 = arg1;
  }
  ++g_call_count;
}

void check(bool condition, const char* what) {
  if (!condition) {
    ++g_failures;
    if (g_report) {
      std::fprintf(stderr, "FAIL: %s\n", what);
    }
  }
}

const char* callee_name(int id) {
  switch (id) {
    case kGet: return "0x00b3d2a0";
    case kLookup: return "0x00ba6d80";
    case kRecordSlot: return "0x00bb9b80";
    case kChild: return "0x00bba500";
    case kColor: return "0x00c32cd0";
    case kArrayCheck: return "0x004da330";
    case kListSync: return "0x00b6f380";
    case kMapFind: return "0x00e5c780";
    case kTextEmit: return "0x005c3d90";
    case kDestroy: return "0x00f47380";
    default: return "?";
  }
}

bool trace_is(const int* ids, int count) {
  if (g_call_count != count) {
    if (g_report) {
      std::fprintf(stderr, "  (trace has %d call(s), expected %d)\n", g_call_count,
                   count);
    }
    return false;
  }
  for (int index = 0; index < count; ++index) {
    if (g_calls[index].id != ids[index]) {
      if (g_report) {
        std::fprintf(stderr, "  (step %d is %s, expected %s)\n", index,
                     callee_name(g_calls[index].id), callee_name(ids[index]));
      }
      return false;
    }
  }
  return true;
}

// The VALUE stored at a receiver displacement, as a pointer -- i.e. what a
// reconstruction that read the word instead of forming the address would pass.
const void* decoy_pointer(const std::uint8_t* base, std::size_t displacement) {
  return reinterpret_cast<const void*>(
      static_cast<std::uintptr_t>(*word_at(base, displacement)));
}

int step_of(int id) {
  for (int index = 0; index < g_call_count; ++index) {
    if (g_calls[index].id == id) {
      return index;
    }
  }
  return -1;
}


// -- fixtures -----------------------------------------------------------------
// Every buffer the body can touch is here, and every one of them is filled with
// a byte pattern before a run so that a wrong displacement or a wrong pointer
// level shows up as a value the assertions did not plant.
constexpr std::uint8_t kPattern = 0xa5;
constexpr std::size_t kReceiverSize = 0x40;   // the modelled object
constexpr std::size_t kCanarySize = 0x10;     // past the end of it
constexpr std::size_t kRecordSize = 0x20;     // 0x00bb9b80's three words
constexpr std::size_t kNodeSize = 0x40;       // 0x00e5c780's found node
constexpr std::size_t kDecoyNodeSize = 0x40;  // the wrong-depth node
constexpr std::size_t kTextSize = 0x10;

// Decoy words stored in the receiver at the three interior-address offsets.
// A reconstruction that passed the VALUE instead of the ADDRESS hands one of
// these to the observer, which is how that mistake is caught.
constexpr Word kDecoySync = 0x5c0c0001u;
constexpr Word kDecoyMap = 0x5c140002u;
constexpr Word kDecoyEmit = 0x5c3c0003u;

struct Fixture {
  std::uint8_t receiver[kReceiverSize + kCanarySize];
  std::uint8_t first[kRecordSize * 4];
  std::uint8_t second[kRecordSize * 4];
  std::uint8_t record[kRecordSize];
  std::uint8_t child[kReceiverSize];
  std::uint8_t node[kNodeSize];
  std::uint8_t node_decoy[kDecoyNodeSize];
  std::uint8_t text_a[kTextSize];
  std::uint8_t text_b[kTextSize];
  std::uint8_t text_c[kTextSize];
};

Fixture g_fix;

struct Observer {
  std::uintptr_t global_value;
  LookupObject* lookup_first;
  LookupObject* lookup_second;
  bool lookup_rewrites_handle;
  Word rewritten_handle;
  const RecordBlock* record;
  ChildHandle* child;
  Word block_payload[3];
  MapNode* node;
  bool map_returns_out_slot;
  MapNode** map_decoy_return;
  // sampled at the moment of a call
  Word sampled_names[4];
  Word sampled_key;
  Word sampled_out_seed;
  Word sampled_block[3];
  std::uint8_t* self;
};

Observer g_obs;
Word g_residue;

SimRecord* receiver() { return reinterpret_cast<SimRecord*>(g_fix.receiver); }

void fill(std::uint8_t* buffer, std::size_t size, std::uint8_t value) {
  std::memset(buffer, value, size);
}

void reset_trace() {
  g_call_count = 0;
  std::memset(g_calls, 0, sizeof(g_calls));
}

void reset_fixture(Word handle) {
  fill(g_fix.receiver, sizeof(g_fix.receiver), kPattern);
  fill(g_fix.first, sizeof(g_fix.first), kPattern);
  fill(g_fix.second, sizeof(g_fix.second), kPattern);
  fill(g_fix.record, sizeof(g_fix.record), kPattern);
  fill(g_fix.child, sizeof(g_fix.child), kPattern);
  fill(g_fix.node, sizeof(g_fix.node), kPattern);
  fill(g_fix.node_decoy, sizeof(g_fix.node_decoy), kPattern);
  fill(g_fix.text_a, sizeof(g_fix.text_a), kPattern);
  fill(g_fix.text_b, sizeof(g_fix.text_b), kPattern);
  fill(g_fix.text_c, sizeof(g_fix.text_c), kPattern);

  *word_at(&g_fix.receiver[0], kReceiverHandle) = handle;
  *word_at(&g_fix.receiver[0], kReceiverSync) = kDecoySync;
  *word_at(&g_fix.receiver[0], kReceiverMap) = kDecoyMap;
  *word_at(&g_fix.receiver[0], kReceiverEmit) = kDecoyEmit;

  // the record: word 0 is the gate, words 1 and 2 are the seeded ones
  *word_at(g_fix.record, 0) = 1u;
  *word_at(g_fix.record, 4) = 0x1111u;
  *word_at(g_fix.record, 8) = 0x2222u;

  // the node: a word at +0x00 that is itself a node (the wrong-depth decoy)
  // and a text pointer at +0x14.
  *word_at(g_fix.node, 0) = reinterpret_cast<Word>(g_fix.node_decoy);
  *word_at(g_fix.node, kNodeTextDisplacement) =
      reinterpret_cast<Word>(g_fix.text_b);
  *word_at(g_fix.node_decoy, 0) = reinterpret_cast<Word>(g_fix.text_c);
  *word_at(g_fix.node_decoy, kNodeTextDisplacement) =
      reinterpret_cast<Word>(g_fix.text_c);

  g_obs.global_value = 0x0badf00du;
  g_obs.lookup_first = reinterpret_cast<LookupObject*>(g_fix.first);
  g_obs.lookup_second = reinterpret_cast<LookupObject*>(g_fix.second);
  g_obs.lookup_rewrites_handle = false;
  g_obs.rewritten_handle = 0u;
  g_obs.record = reinterpret_cast<const RecordBlock*>(g_fix.record);
  g_obs.child = reinterpret_cast<ChildHandle*>(g_fix.child);
  g_obs.block_payload[0] = 0xaaaaaaaau;
  g_obs.block_payload[1] = 0xbbbbbbbbu;
  g_obs.block_payload[2] = 0xccccccccu;
  g_obs.node = reinterpret_cast<MapNode*>(g_fix.node);
  g_obs.map_returns_out_slot = true;
  g_obs.map_decoy_return = nullptr;
  g_obs.self = g_fix.receiver;
  std::memset(g_obs.sampled_names, 0, sizeof(g_obs.sampled_names));
  std::memset(g_obs.sampled_block, 0, sizeof(g_obs.sampled_block));
  g_obs.sampled_key = 0u;
  g_obs.sampled_out_seed = 0u;
  g_residue = kRdataWordA;
  g_lookup_calls = 0;
  reset_trace();
}

using Body = void (SW2_00C33580_THISCALL *)(SimRecord*);

void run(Body body) {
  body(receiver());
}

void sample_block(const Word* block) {
  // what 0x004da330's own bytes do: read element 0 and element 1 of the block
  // it is handed (0x00c4da367 / 0x00c4da36b).
  for (int index = 0; index < 4; ++index) {
    g_obs.sampled_names[index] = block[index];
  }
}

void sample_color_block(const void* block) {
  const std::uint8_t* const bytes = static_cast<const std::uint8_t*>(block);
  for (int index = 0; index < 3; ++index) {
    g_obs.sampled_block[index] = *word_at(bytes, 4u * static_cast<std::size_t>(index));
  }
}

}  // namespace

// -- the ten observers --------------------------------------------------------
extern "C" GlobalSource* SW2_00C33580_CDECL global_word_00b3d2a0() {
  // 0x00b3d2a0: MOV EAX,ds:0x167eae4 ; RET -- no argument, no receiver, and it
  // pops nothing, which is why the handle pushed before it survives.
  record(kGet, nullptr, 0u, 0u);
  return reinterpret_cast<GlobalSource*>(static_cast<std::uintptr_t>(g_obs.global_value));
}

extern "C" LookupObject* SW2_00C33580_THISCALL table_lookup_00ba6d80(
    GlobalSource* source, Word handle) {
  // 0x00ba6d80: MOV EDX,[ESP+0x4] is the handle, ECX is the receiver, RET 0x4.
  const int seen = g_lookup_calls++;
  record(kLookup, source, handle, static_cast<Word>(seen));
  if (g_obs.lookup_rewrites_handle && g_obs.self != nullptr) {
    *word_at(g_obs.self, kReceiverHandle) = g_obs.rewritten_handle;
  }
  return seen == 0 ? g_obs.lookup_first : g_obs.lookup_second;
}

extern "C" const RecordBlock* SW2_00C33580_THISCALL record_slot_00bb9b80(
    LookupObject* owner) {
  // 0x00bb9b80: LEA EAX,[ECX+0x74] ; RET -- an ADDRESS, never dereferenced here.
  record(kRecordSlot, owner, 0u, 0u);
  return g_obs.record;
}

extern "C" ChildHandle* SW2_00C33580_THISCALL child_selector_00bba500(
    LookupObject* owner) {
  // 0x00bba500: no stack argument; a pointer comes back in EAX.
  record(kChild, owner, 0u, 0u);
  return g_obs.child;
}

extern "C" RecordBlock* SW2_00C33580_THISCALL color_fill_00c32cd0(
    ColorSubject* subject, RecordBlock* out) {
  // 0x00c32cd0: writes TWELVE bytes through its argument (three FSTPs) and
  // returns that same address. The return is discarded by the body, so this
  // observer returns a poison pointer on purpose.
  record(kColor, subject, reinterpret_cast<Word>(out), 0u);
  sample_color_block(out);
  std::uint8_t* const bytes = reinterpret_cast<std::uint8_t*>(out);
  for (std::size_t index = 0; index < kFrameBlockBytes; ++index) {
    bytes[index] = static_cast<std::uint8_t>(g_obs.block_payload[index / 4]);
  }
  return reinterpret_cast<RecordBlock*>(g_fix.text_a);
}

extern "C" void SW2_00C33580_THISCALL array_check_004da330(
    ArrayTarget* target, const Word* block) {
  // 0x004da330: reads the block it is given, writes nothing.
  record(kArrayCheck, target, reinterpret_cast<Word>(block), 0u);
  sample_block(block);
}

extern "C" void SW2_00C33580_THISCALL list_sync_00b6f380(
    SyncTarget* target, const Word* block) {
  record(kListSync, target, reinterpret_cast<Word>(block), 0u);
  sample_block(block);
}

extern "C" MapNode** SW2_00C33580_THISCALL map_find_00e5c780(
    OrderedMap* map, MapNode** out, const Word* key) {
  // 0x00e5c780: writes the found node through the FIRST stack word and RETURNS
  // the address of that word (0x00e5c7b2 / 0x00e5c7b6, 0x00e5c7c0).
  record(kMapFind, map, reinterpret_cast<Word>(out),
         reinterpret_cast<Word>(key));
  g_obs.sampled_key = *key;
  g_obs.sampled_out_seed = reinterpret_cast<Word>(*out);
  if (g_obs.node != nullptr) {
    *out = g_obs.node;
  }
  return g_obs.map_returns_out_slot ? out : g_obs.map_decoy_return;
}

extern "C" void SW2_00C33580_THISCALL text_emit_005c3d90(
    TextSink* sink, const OpaqueWideText* text) {
  // 0x005c3d90: dereferences its argument immediately (CMP WORD PTR [EDX],0).
  record(kTextEmit, sink, reinterpret_cast<Word>(text), 0u);
}

extern "C" void SW2_00C33580_CDECL buffer_destroy_00f47380(void* buffer) {
  // 0x00f47380: bare RET, so the caller cleans up.
  record(kDestroy, nullptr, reinterpret_cast<Word>(buffer), 0u);
}

Word w2_00c33580_stack_residue() { return g_residue; }

namespace {

// ---------------------------------------------------------------------------
// CASES
// ---------------------------------------------------------------------------

// 0x00c3358f: the sentinel exits before the getter is even called.
void case_sentinel_exits_before_any_call(Body body) {
  reset_fixture(kInvalidHandle);
  std::uint8_t before[sizeof(g_fix.receiver)];
  std::memcpy(before, g_fix.receiver, sizeof(before));
  run(body);
  check(g_call_count == 0, "0x00c3358f: a handle of 0xffffffff makes no call");
  check(std::memcmp(before, g_fix.receiver, sizeof(before)) == 0,
        "the sentinel path writes nothing into the receiver");
}

// REFUTES: "the sentinel is 0", "the sentinel is any non-zero", "the body calls
// the getter before testing".
void case_zero_handle_is_a_live_value(Body body) {
  reset_fixture(0u);
  g_obs.lookup_first = nullptr;
  run(body);
  const int expected[] = {kGet, kLookup};
  check(trace_is(expected, 2),
        "a handle of 0 reaches the lookup (0x00c3358c is CMP -0x1, not TEST)");
  check(g_calls[1].arg0 == 0u, "the lookup receives the handle 0");
}

// REFUTES: "the pushed handle is the getter's argument" and "the getter's
// return is the lookup's argument" -- both are measurable, because the getter's
// return and the handle are given different values on purpose.
void case_lookup_argument_and_receiver(Body body) {
  reset_fixture(0x1234u);
  run(body);
  check(g_call_count >= 2, "the first lookup was made");
  check(g_calls[1].id == kLookup, "0x00c3359d is the second transfer");
  check(g_calls[1].arg0 == 0x1234u,
        "0x00c33595 pushes the handle, and 0x00ba6d80 takes it");
  check(g_calls[1].ecx == reinterpret_cast<const void*>(
                    reinterpret_cast<std::uintptr_t>(g_obs.global_value)),
        "0x00b3d2a0's return is the lookup's ECX receiver");
}

// REFUTES: "the handle is read once and cached". The observer rewrites the
// receiver slot during the first lookup, which the machine's second read at
// 0x00c335c9 would see.
void case_the_handle_is_read_twice(Body body) {
  reset_fixture(0x0000ffffu);
  g_obs.lookup_rewrites_handle = true;
  g_obs.rewritten_handle = kInvalidHandle;
  run(body);
  const int expected[] = {kGet, kLookup, kRecordSlot};
  check(trace_is(expected, 3),
        "the re-read at 0x00c335c9 sees the callee's write and exits");
}

void case_the_second_lookup_uses_the_reread_handle(Body body) {
  reset_fixture(0x0000ffffu);
  g_obs.lookup_rewrites_handle = true;
  g_obs.rewritten_handle = 0x0000abcdu;
  g_obs.child = nullptr;
  run(body);
  const int expected[] = {kGet, kLookup, kRecordSlot, kGet, kLookup, kChild};
  check(trace_is(expected, 6),
        "0x00c335d8/0x00c335d9/0x00c335e0 repeat the pair with the re-read value");
  check(g_calls[4].arg0 == 0x0000abcdu,
        "the second lookup gets the RE-READ handle, not the first one");
  check(g_calls[4].ecx == reinterpret_cast<const void*>(
                    reinterpret_cast<std::uintptr_t>(g_obs.global_value)),
        "the second getter's return is the second lookup's receiver");
}

// 0x00c335a4 / 0x00c335e7 / 0x00c335f9: the three null gates.
void case_null_gates(Body body) {
  reset_fixture(7u);
  g_obs.lookup_first = nullptr;
  run(body);
  {
    const int expected[] = {kGet, kLookup};
    check(trace_is(expected, 2), "0x00c335a4: a null first lookup exits");
  }

  reset_fixture(7u);
  g_obs.lookup_second = nullptr;
  run(body);
  {
    const int expected[] = {kGet, kLookup, kRecordSlot, kGet, kLookup};
    check(trace_is(expected, 5), "0x00c335e7: a null second lookup exits");
  }

  reset_fixture(7u);
  g_obs.child = nullptr;
  run(body);
  {
    const int expected[] = {kGet, kLookup, kRecordSlot, kGet, kLookup, kChild};
    check(trace_is(expected, 6), "0x00c335f9: a null child exits");
  }
}

// REFUTES: "the gate is word 1 or word 2", and "a non-zero word 0 is a pointer
// and gets dereferenced".
void case_the_gate_is_the_records_first_word(Body body) {
  reset_fixture(7u);
  *word_at(g_fix.record, 0) = 0u;
  *word_at(g_fix.record, 4) = 0xffffffffu;
  *word_at(g_fix.record, 8) = 0xffffffffu;
  run(body);
  {
    const int expected[] = {kGet, kLookup, kRecordSlot};
    check(trace_is(expected, 3),
          "0x00c335c1 tests word 0: words 1 and 2 do not gate the tail");
  }

  reset_fixture(7u);
  *word_at(g_fix.record, 0) = 0xdeadbee0u;  // looks exactly like a pointer
  *word_at(g_fix.record, 4) = 0xdeadbee1u;
  *word_at(g_fix.record, 8) = 0xdeadbee2u;
  run(body);
  const int color = step_of(kColor);
  check(color >= 0,
        "a non-zero word 0 is a VALUE: the body goes on to the colour callee");
  if (color >= 0) {
    check(g_calls[color].ecx == static_cast<const void*>(receiver()),
          "0x00c33604 hands the colour callee the RECEIVER, not the record");
  }
}

// REFUTES: "the block's base is the address of word 1", "the body stores word 0
// as well", "the colour write clobbers the names block". The base is identified
// by CONTENT: a model that handed 0x00c32cd0 &frame[word1] would show the
// record's word 1 in the callee's element 0, and its twelve-byte write would
// reach the names block's element 0 and destroy the residue the range guard
// later reads.
void case_the_block_and_its_base(Body body) {
  reset_fixture(7u);
  *word_at(g_fix.record, 4) = 0x1111u;
  *word_at(g_fix.record, 8) = 0x2222u;
  g_residue = 0x00c0ffeeu;
  run(body);
  const int color = step_of(kColor);
  check(color >= 0, "0x00c32cd0 was reached");
  if (color < 0) {
    return;
  }
  check(g_obs.sampled_block[0] == kBlockFirstWordSeed,
        "0x00c335b1 never stores word 0: the block's first word is untouched");
  check(g_obs.sampled_block[1] == 0x1111u,
        "0x00c335b9 stored the record's word 1 into the block");
  check(g_obs.sampled_block[2] == 0x2222u,
        "0x00c335bd stored the record's word 2 into the block");
  const int array = step_of(kArrayCheck);
  check(array >= 0, "0x004da330 was reached");
  if (array >= 0) {
    check(g_obs.sampled_names[0] == g_residue,
          "the colour callee's twelve-byte write does not reach the names block");
  }
  const int sync = step_of(kListSync);
  check(sync >= 0 && array >= 0 &&
            g_calls[sync].arg0 != g_calls[color].arg0 &&
            g_calls[sync].arg0 != g_calls[color].arg0 + 4u &&
            g_calls[sync].arg0 != g_calls[color].arg0 + 8u,
        "the names block pointer is not the colour out-parameter");
}

// REFUTES: "the three .rdata stores happen after the first consumer", "the two
// A words and the B word are swapped", "element 2 is the B word".
void case_the_names_block_is_stored_before_it_is_used(Body body) {
  reset_fixture(7u);
  g_residue = 0x00c0ffeeu;
  run(body);
  int array_step = -1;
  for (int index = 0; index < g_call_count; ++index) {
    if (g_calls[index].id == kArrayCheck) {
      array_step = index;
    }
  }
  check(array_step >= 0, "0x004da330 was called");
  if (array_step < 0) {
    return;
  }
  check(g_obs.sampled_names[0] == g_residue,
        "element 0 is the stack residue: the body never writes it");
  check(g_obs.sampled_names[1] == kRdataWordA,
        "0x00c33617 stored 0x1667bac into element 1");
  check(g_obs.sampled_names[2] == kRdataWordA,
        "0x00c3361b stored 0x1667bac into element 2");
  check(g_obs.sampled_names[3] == kRdataWordB,
        "0x00c3361f stored 0x1667bae into element 3");
}

// REFUTES: "0x0c is the value stored at 0x0c", "0x14 likewise", "0x3c likewise",
// "the block pointer is the base of the twelve-byte block instead of the names
// block", "the colour call receives the record instead of the receiver".
void case_interior_addresses_are_addresses(Body body) {
  reset_fixture(7u);
  g_residue = 0u;  // no release, so the trace is the deterministic prefix
  run(body);
  const int color = step_of(kColor);
  const int array = step_of(kArrayCheck);
  const int sync = step_of(kListSync);
  const int map = step_of(kMapFind);
  const int emit = step_of(kTextEmit);
  check(color >= 0 && array >= 0 && sync >= 0 && map >= 0 && emit >= 0,
        "the six tail callees were all reached");
  if (color < 0 || array < 0 || sync < 0 || map < 0 || emit < 0) {
    return;
  }
  const std::uint8_t* const self = g_fix.receiver;
  check(g_calls[array].ecx == static_cast<const void*>(g_fix.child),
        "0x00c33615 hands 0x004da330 the CHILD, not the receiver");
  check(g_calls[sync].ecx == static_cast<const void*>(self + kReceiverSync),
        "0x00c33631 forms receiver+0x0c and passes the ADDRESS");
  check(g_calls[sync].ecx != decoy_pointer(self, kReceiverSync),
        "0x0c is not passed as the value stored there (decoy 0x5c0c0001)");
  check(g_calls[map].ecx == static_cast<const void*>(self + kReceiverMap),
        "0x00c33643 forms receiver+0x14 and passes the ADDRESS");
  check(g_calls[map].ecx != decoy_pointer(self, kReceiverMap),
        "0x14 is not passed as the value stored there (decoy 0x5c140002)");
  check(g_calls[emit].ecx == static_cast<const void*>(self + kReceiverEmit),
        "0x00c33659 forms receiver+0x3c and passes the ADDRESS");
  check(g_calls[emit].ecx != decoy_pointer(self, kReceiverEmit),
        "0x3c is not passed as the value stored there (decoy 0x5c3c0003)");
  check(g_calls[color].ecx == static_cast<const void*>(self),
        "0x00c33604 hands 0x00c32cd0 the receiver itself");
  check(g_calls[array].arg0 == g_calls[sync].arg0,
        "both consumers are handed the same block pointer");
  check(g_calls[array].arg0 != g_calls[color].arg0,
        "the names block is not the twelve-byte colour block");
  check(reinterpret_cast<const void*>(
            static_cast<std::uintptr_t>(g_calls[array].arg0)) !=
            g_calls[array].ecx,
        "the block pointer is not the child's address");
}

// REFUTES: "the key is passed by value", "the key is 0 or 1", "the out-parameter
// is the second stack word".
void case_the_map_key_is_two_in_the_second_word(Body body) {
  reset_fixture(7u);
  g_residue = 0u;
  run(body);
  const int map = step_of(kMapFind);
  check(map >= 0, "0x00e5c780 was called");
  if (map < 0) {
    return;
  }
  check(g_obs.sampled_key == 2u,
        "0x00c33646 stored 2 into the key slot BEFORE the call");
  check(g_obs.sampled_out_seed == kOutSlotSeed,
        "the out-parameter still holds the model's seed: only the callee fills it");
  check(g_calls[map].arg0 != 0u, "the FIRST stack word is the out-parameter");
  check(g_calls[map].arg1 != 0u, "the SECOND stack word is the key pointer");
  check(g_calls[map].arg0 != 2u && g_calls[map].arg1 != 2u,
        "neither stack word is the key value itself");
}

// REFUTES: "the map result is dereferenced twice", "the out-slot is read
// directly instead of through the address the callee returned".
void case_the_map_result_is_dereferenced_exactly_once(Body body) {
  reset_fixture(7u);
  g_residue = 0u;
  run(body);
  const int emit = step_of(kTextEmit);
  check(emit >= 0, "0x005c3d90 was called");
  if (emit < 0) {
    return;
  }
  check(g_calls[emit].arg0 == reinterpret_cast<Word>(g_fix.text_b),
        "0x00c33653 reads the NODE the callee returned: node[0x14] is used");
  check(g_calls[emit].arg0 != reinterpret_cast<Word>(g_fix.text_c),
        "the word at node[0x00] is not followed: one level of indirection");
  check(g_calls[emit].arg0 != reinterpret_cast<Word>(g_fix.node),
        "the node pointer itself is not passed where its +0x14 word is");
}

// The callee returns an address that is NOT the out-parameter, and the word
// stored there is a different node. This is the only case that can tell "read
// the address the callee returned" (0x00c33653 `MOV EAX,[EAX]`) from "read the
// out-slot", because on every other path the two addresses are the same.
void case_the_returned_address_is_the_one_that_is_read(Body body) {
  static std::uint8_t decoy_node[kNodeSize];
  static std::uint8_t decoy_return_cell[8];
  fill(decoy_node, sizeof(decoy_node), kPattern);
  // word 0 points at a readable buffer, so that a reconstruction which
  // dereferences one level too deep faults HERE rather than inside the harness.
  *word_at(decoy_node, 0) = reinterpret_cast<Word>(g_fix.node_decoy);
  *word_at(decoy_node, kNodeTextDisplacement) =
      reinterpret_cast<Word>(g_fix.text_c);
  *word_at(decoy_return_cell, 0) = reinterpret_cast<Word>(decoy_node);

  reset_fixture(7u);
  g_residue = 0u;
  g_obs.map_returns_out_slot = false;
  g_obs.map_decoy_return = reinterpret_cast<MapNode**>(decoy_return_cell);
  run(body);
  const int emit = step_of(kTextEmit);
  check(emit >= 0, "0x005c3d90 was called");
  if (emit >= 0) {
    check(g_calls[emit].arg0 == reinterpret_cast<Word>(g_fix.text_c),
          "0x00c33653 dereferences the callee's EAX return, not the out-slot");
    check(g_calls[emit].arg0 != reinterpret_cast<Word>(g_fix.text_b),
          "the out-slot's node is not what is read");
  }
  g_obs.map_returns_out_slot = true;
  g_obs.map_decoy_return = nullptr;
}

// REFUTES: "the guard is `end - begin > 2` unsigned", "the AND is missing",
// "the null test comes first".
void case_the_range_guard(Body body) {
  struct Scenario {
    Word residue;
    bool expect_destroy;
    const char* why;
  };
  const Scenario scenarios[] = {
      {kRdataWordA - 8u, true, "an eight-byte span is released"},
      {kRdataWordA - 5u, true, "five rounds down to four, still > 2"},
      {kRdataWordA - 4u, true, "four is the smallest released span"},
      {kRdataWordA - 3u, false, "three rounds down to two: NOT released"},
      {kRdataWordA - 2u, false, "two is not > 2: NOT released"},
      {kRdataWordA - 1u, false, "one rounds down to zero: NOT released"},
      {kRdataWordA, false, "an empty span is not released"},
      {kRdataWordA + 4u, false, "begin above end: SIGNED JLE skips the release"},
      {kRdataWordA + 0x10000u, false,
       "a large unsigned difference is still a negative int32"},
      {0u, false, "a null begin is not released"},
  };
  for (std::size_t index = 0; index < sizeof(scenarios) / sizeof(scenarios[0]);
       ++index) {
    reset_fixture(7u);
    g_residue = scenarios[index].residue;
    run(body);
    int destroy_step = -1;
    for (int step = 0; step < g_call_count; ++step) {
      if (g_calls[step].id == kDestroy) {
        destroy_step = step;
      }
    }
    check((destroy_step >= 0) == scenarios[index].expect_destroy,
          scenarios[index].why);
    if (destroy_step >= 0) {
      check(g_calls[destroy_step].arg0 == scenarios[index].residue,
            "0x00c33677 pushes the BEGIN, i.e. the block's element 0");
    }
  }
}

// REFUTES: "end is element 3" (0x1667bae) or "end is the colour block".
void case_the_end_of_the_range_is_element_two(Body body) {
  // begin = A-2: with end == element 2 (A) the span is 2 and nothing is
  // released; with end == element 3 (B) it would be 4 and something would be.
  reset_fixture(7u);
  g_residue = kRdataWordA - 2u;
  run(body);
  for (int step = 0; step < g_call_count; ++step) {
    check(g_calls[step].id != kDestroy,
          "0x00c33661 reads element 2 as the end, not element 3");
  }
}

// REFUTES: "the body writes the receiver" -- the machine's receiver record says
// written_through 0, and this is checked over the object AND a canary.
void case_the_receiver_is_never_written(Body body) {
  reset_fixture(7u);
  g_residue = kRdataWordA - 0x40u;
  std::uint8_t before[sizeof(g_fix.receiver)];
  std::memcpy(before, g_fix.receiver, sizeof(before));
  run(body);
  check(std::memcmp(before, g_fix.receiver, sizeof(before)) == 0,
        "no byte of the receiver (or of the canary past it) is written");
}

// The body must not depend on the twelve-byte block the colour callee wrote: it
// reads the block back nowhere.
void case_the_colour_payload_does_not_matter(Body body) {
  reset_fixture(7u);
  g_residue = 0u;
  g_obs.block_payload[0] = 0x01010101u;
  g_obs.block_payload[1] = 0x02020202u;
  g_obs.block_payload[2] = 0x03030303u;
  run(body);
  const int count = g_call_count;
  int first_args[kIdCount * 4];
  for (int index = 0; index < count; ++index) {
    first_args[index] = g_calls[index].id;
  }
  Word emitted = 0u;
  for (int index = 0; index < count; ++index) {
    if (g_calls[index].id == kTextEmit) {
      emitted = g_calls[index].arg0;
    }
  }
  reset_fixture(7u);
  g_residue = 0u;
  g_obs.block_payload[0] = 0xdead0001u;
  g_obs.block_payload[1] = 0xdead0002u;
  g_obs.block_payload[2] = 0xdead0003u;
  run(body);
  check(g_call_count == count, "the colour payload does not change the trace");
  Word emitted2 = 0u;
  for (int index = 0; index < g_call_count; ++index) {
    if (g_calls[index].id == kTextEmit) {
      emitted2 = g_calls[index].arg0;
    }
    check(g_calls[index].id == first_args[index], "same callee in the same order");
  }
  check(emitted == emitted2, "the colour payload does not change what is emitted");
}

// ---------------------------------------------------------------------------
// MUTANTS: complete copies of the reconstruction with exactly one thing wrong.
// Each must be CAUGHT by the case named beside it; if a mutant survives, the
// corresponding case is not testing what it claims to.
// ---------------------------------------------------------------------------

// MUTANT 1: the map result is dereferenced twice.
void SW2_00C33580_THISCALL mutant_two_level_map_read(SimRecord* self) {
  alignas(4) std::uint8_t frame[kFrameBytes];
  *word_at(&frame, kFrameNames0) = w2_00c33580_stack_residue();
  *word_at(&frame, kFrameMapOut) = kOutSlotSeed;
  const Word handle = *word_at(self, kReceiverHandle);
  if (handle == kInvalidHandle) {
    return;
  }
  LookupObject* const first = table_lookup_00ba6d80(global_word_00b3d2a0(), handle);
  if (first == nullptr) {
    return;
  }
  const RecordBlock* const record = record_slot_00bb9b80(first);
  const Word gate = *word_at(record, kRecordGateWord);
  *word_at(&frame, kFrameBlockWord1) = *word_at(record, kRecordSeedWord1);
  *word_at(&frame, kFrameBlockWord2) = *word_at(record, kRecordSeedWord2);
  if (gate == 0u) {
    return;
  }
  const Word handle_again = *word_at(self, kReceiverHandle);
  if (handle_again == kInvalidHandle) {
    return;
  }
  LookupObject* const second = table_lookup_00ba6d80(global_word_00b3d2a0(), handle_again);
  if (second == nullptr) {
    return;
  }
  ChildHandle* const child = child_selector_00bba500(second);
  if (child == nullptr) {
    return;
  }
  (void)color_fill_00c32cd0(reinterpret_cast<ColorSubject*>(self),
                            interior<RecordBlock>(&frame, kFrameBlock));
  *word_at(&frame, kFrameNames1) = kRdataWordA;
  *word_at(&frame, kFrameNames2) = kRdataWordA;
  *word_at(&frame, kFrameNames3) = kRdataWordB;
  array_check_004da330(reinterpret_cast<ArrayTarget*>(child),
                       word_at(&frame, kFrameNames0));
  list_sync_00b6f380(interior<SyncTarget>(self, kReceiverSync),
                     word_at(&frame, kFrameNames0));
  *word_at(&frame, kFrameMapKey) = kMapKeyValue;
  MapNode* const node =
      *map_find_00e5c780(interior<OrderedMap>(self, kReceiverMap),
                         slot_at<MapNode>(&frame, kFrameMapOut),
                         word_at(&frame, kFrameMapKey));
  // MUTATION: one extra level.
  const MapNode* const deeper =
      reinterpret_cast<const MapNode*>(*word_at(node, 0x00));
  const OpaqueWideText* const text = reinterpret_cast<const OpaqueWideText*>(
      *word_at(deeper, kNodeTextDisplacement));
  text_emit_005c3d90(interior<TextSink>(self, kReceiverEmit), text);
}

// MUTANT 2: the range guard is compared UNSIGNED and the AND is dropped.
void SW2_00C33580_THISCALL mutant_unsigned_range(SimRecord* self) {
  alignas(4) std::uint8_t frame[kFrameBytes];
  *word_at(&frame, kFrameNames0) = w2_00c33580_stack_residue();
  *word_at(&frame, kFrameMapOut) = kOutSlotSeed;
  const Word handle = *word_at(self, kReceiverHandle);
  if (handle == kInvalidHandle) {
    return;
  }
  LookupObject* const first = table_lookup_00ba6d80(global_word_00b3d2a0(), handle);
  if (first == nullptr) {
    return;
  }
  const RecordBlock* const record = record_slot_00bb9b80(first);
  const Word gate = *word_at(record, kRecordGateWord);
  *word_at(&frame, kFrameBlockWord1) = *word_at(record, kRecordSeedWord1);
  *word_at(&frame, kFrameBlockWord2) = *word_at(record, kRecordSeedWord2);
  if (gate == 0u) {
    return;
  }
  const Word handle_again = *word_at(self, kReceiverHandle);
  if (handle_again == kInvalidHandle) {
    return;
  }
  LookupObject* const second = table_lookup_00ba6d80(global_word_00b3d2a0(), handle_again);
  if (second == nullptr) {
    return;
  }
  ChildHandle* const child = child_selector_00bba500(second);
  if (child == nullptr) {
    return;
  }
  (void)color_fill_00c32cd0(reinterpret_cast<ColorSubject*>(self),
                            interior<RecordBlock>(&frame, kFrameBlock));
  *word_at(&frame, kFrameNames1) = kRdataWordA;
  *word_at(&frame, kFrameNames2) = kRdataWordA;
  *word_at(&frame, kFrameNames3) = kRdataWordB;
  array_check_004da330(reinterpret_cast<ArrayTarget*>(child),
                       word_at(&frame, kFrameNames0));
  list_sync_00b6f380(interior<SyncTarget>(self, kReceiverSync),
                     word_at(&frame, kFrameNames0));
  *word_at(&frame, kFrameMapKey) = kMapKeyValue;
  MapNode* const node =
      *map_find_00e5c780(interior<OrderedMap>(self, kReceiverMap),
                         slot_at<MapNode>(&frame, kFrameMapOut),
                         word_at(&frame, kFrameMapKey));
  const OpaqueWideText* const text = reinterpret_cast<const OpaqueWideText*>(
      *word_at(node, kNodeTextDisplacement));
  text_emit_005c3d90(interior<TextSink>(self, kReceiverEmit), text);
  const auto* const range_end = byte_at(&frame, kFrameNames2);
  const auto* const range_begin = byte_at(&frame, kFrameNames0);
  // MUTATION: no AND, and the compare is UNSIGNED.
  const Word span = static_cast<Word>(reinterpret_cast<std::uintptr_t>(range_end) -
                                      reinterpret_cast<std::uintptr_t>(range_begin));
  if (span > kRangeThreshold) {
    if (range_begin != nullptr) {
      buffer_destroy_00f47380(const_cast<std::uint8_t*>(range_begin));
    }
  }
}

// MUTANT 3: the lookup is given the getter's RETURN as its argument.
void SW2_00C33580_THISCALL mutant_lookup_argument_order(SimRecord* self) {
  alignas(4) std::uint8_t frame[kFrameBytes];
  *word_at(&frame, kFrameNames0) = w2_00c33580_stack_residue();
  *word_at(&frame, kFrameMapOut) = kOutSlotSeed;
  const Word handle = *word_at(self, kReceiverHandle);
  if (handle == kInvalidHandle) {
    return;
  }
  // MUTATION: the pushed handle is the receiver and the getter's word is the
  // argument -- the mirror image of 0x00c33595/0x00c3359d.
  LookupObject* const first = table_lookup_00ba6d80(
      reinterpret_cast<GlobalSource*>(handle),
      reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(
          global_word_00b3d2a0())));
  if (first == nullptr) {
    return;
  }
  const RecordBlock* const record = record_slot_00bb9b80(first);
  const Word gate = *word_at(record, kRecordGateWord);
  *word_at(&frame, kFrameBlockWord1) = *word_at(record, kRecordSeedWord1);
  *word_at(&frame, kFrameBlockWord2) = *word_at(record, kRecordSeedWord2);
  if (gate == 0u) {
    return;
  }
  const Word handle_again = *word_at(self, kReceiverHandle);
  if (handle_again == kInvalidHandle) {
    return;
  }
  LookupObject* const second = table_lookup_00ba6d80(
      reinterpret_cast<GlobalSource*>(handle_again),
      reinterpret_cast<Word>(reinterpret_cast<std::uintptr_t>(
          global_word_00b3d2a0())));
  if (second == nullptr) {
    return;
  }
  ChildHandle* const child = child_selector_00bba500(second);
  if (child == nullptr) {
    return;
  }
  (void)color_fill_00c32cd0(reinterpret_cast<ColorSubject*>(self),
                            interior<RecordBlock>(&frame, kFrameBlock));
  *word_at(&frame, kFrameNames1) = kRdataWordA;
  *word_at(&frame, kFrameNames2) = kRdataWordA;
  *word_at(&frame, kFrameNames3) = kRdataWordB;
  array_check_004da330(reinterpret_cast<ArrayTarget*>(child),
                       word_at(&frame, kFrameNames0));
  list_sync_00b6f380(interior<SyncTarget>(self, kReceiverSync),
                     word_at(&frame, kFrameNames0));
  *word_at(&frame, kFrameMapKey) = kMapKeyValue;
  MapNode* const node =
      *map_find_00e5c780(interior<OrderedMap>(self, kReceiverMap),
                         slot_at<MapNode>(&frame, kFrameMapOut),
                         word_at(&frame, kFrameMapKey));
  const OpaqueWideText* const text = reinterpret_cast<const OpaqueWideText*>(
      *word_at(node, kNodeTextDisplacement));
  text_emit_005c3d90(interior<TextSink>(self, kReceiverEmit), text);
  const auto* const range_end = byte_at(&frame, kFrameNames2);
  const auto* const range_begin = byte_at(&frame, kFrameNames0);
  const Word span =
      static_cast<Word>(reinterpret_cast<std::uintptr_t>(range_end) -
                        reinterpret_cast<std::uintptr_t>(range_begin)) &
      0xfffffffeu;
  if (static_cast<std::int32_t>(span) > static_cast<std::int32_t>(kRangeThreshold)) {
    if (range_begin != nullptr) {
      buffer_destroy_00f47380(const_cast<std::uint8_t*>(range_begin));
    }
  }
}

// A case is a refutation only if it fails for the mutant. Each of these three
// runs a whole case suite against a wrong body and requires it to report a
// failure -- a survivor means the suite is not testing what it claims to.
int failures_of(Body body) {
  const int before = g_failures;
  g_report = false;
  case_lookup_argument_and_receiver(body);
  case_the_map_result_is_dereferenced_exactly_once(body);
  case_the_returned_address_is_the_one_that_is_read(body);
  case_the_range_guard(body);
  case_sentinel_exits_before_any_call(body);
  case_interior_addresses_are_addresses(body);
  case_the_handle_is_read_twice(body);
  case_the_names_block_is_stored_before_it_is_used(body);
  g_report = true;
  const int produced = g_failures - before;
  // A mutant's failures are the POINT of the run, so they are counted and
  // required to be non-zero by the caller, but they are not this suite's
  // failures and must not decide the exit status.
  g_failures = before;
  return produced;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w2_00c33580

// The cases and their fixtures all live in the package namespace, so that the
// test cannot collide with anything in the reconstruction it is testing. main()
// itself must be at global scope, hence the using-directive.
using namespace openspore::reconstruction::pkg_swarm_w2_00c33580;

int main() {
  case_sentinel_exits_before_any_call(re_00c33580);
  case_zero_handle_is_a_live_value(re_00c33580);
  case_lookup_argument_and_receiver(re_00c33580);
  case_the_handle_is_read_twice(re_00c33580);
  case_the_second_lookup_uses_the_reread_handle(re_00c33580);
  case_null_gates(re_00c33580);
  case_the_gate_is_the_records_first_word(re_00c33580);
  case_the_block_and_its_base(re_00c33580);
  case_the_names_block_is_stored_before_it_is_used(re_00c33580);
  case_interior_addresses_are_addresses(re_00c33580);
  case_the_map_key_is_two_in_the_second_word(re_00c33580);
  case_the_map_result_is_dereferenced_exactly_once(re_00c33580);
  case_the_returned_address_is_the_one_that_is_read(re_00c33580);
  case_the_range_guard(re_00c33580);
  case_the_end_of_the_range_is_element_two(re_00c33580);
  case_the_receiver_is_never_written(re_00c33580);
  case_the_colour_payload_does_not_matter(re_00c33580);

  // The suite must reject every mutant. The counts are printed so that a
  // mutant which is caught by exactly one check is still visible.
  const int caught_one = failures_of(mutant_two_level_map_read);
  const int caught_two = failures_of(mutant_unsigned_range);
  const int caught_three = failures_of(mutant_lookup_argument_order);
  std::printf("mutant survivors: two-level map read %d, unsigned range %d, "
              "swapped lookup argument %d (each must be > 0)\n",
              caught_one, caught_two, caught_three);
  check(caught_one > 0, "MUTANT 1 (two-level map read) is caught");
  check(caught_two > 0, "MUTANT 2 (unsigned range compare) is caught");
  check(caught_three > 0, "MUTANT 3 (swapped lookup argument order) is caught");

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  return 0;
}
