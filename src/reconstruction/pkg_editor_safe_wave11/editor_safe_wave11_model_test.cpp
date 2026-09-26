#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "editor_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __thiscall
#define PKG_EDITOR_SAFE_WAVE11_CDECL __cdecl
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __stdcall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#define PKG_EDITOR_SAFE_WAVE11_CDECL __attribute__((cdecl))
#define PKG_EDITOR_SAFE_WAVE11_STDCALL __attribute__((stdcall))
#else
#error "PKG-EDITOR-SAFE-WAVE11 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave11 {

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

namespace {

struct PortState {
  unsigned notify_calls;
  Word notify_first;
  Word notify_second;

  bool probe_00526430;
  unsigned probe_00526430_calls;
  void* probe_00526430_arg;

  unsigned range_004b1cc0_calls;
  void* range_004b1cc0_self;
  const void* range_004b1cc0_first;
  const void* range_004b1cc0_second;
  Byte range_004b1cc0_third;

  unsigned size_004aff80_calls;
  Signed size_004aff80_count;

  OpaqueRecord build_0044ae00_seed;
  unsigned build_0044ae00_calls;
  void* build_0044ae00_self;
  Word build_0044ae00_arg1;
  Word build_0044ae00_arg2;
  Word build_0044ae00_arg3;

  unsigned offset_0041dba0_calls;
  void* offset_0041dba0_first[2];
  Real offset_0041dba0_value;

  OpaqueBox init_00409930_seed;
  unsigned init_00409930_calls;

  OpaqueBox apply_00409dd0_seed;
  unsigned apply_00409dd0_calls;
  void* apply_00409dd0_first;

  bool budget_004bf0a0;
  unsigned budget_004bf0a0_calls;
  void* budget_004bf0a0_first;
  void* budget_004bf0a0_second;
  Word budget_004bf0a0_third;

  bool pick_004ccae0_result[4];
  Real pick_004ccae0_value[4];
  OpaqueWords3 pick_004ccae0_first[4];
  OpaqueWords3 pick_004ccae0_second[4];
  void* pick_004ccae0_self[4];
  OpaqueFloats3 pick_004ccae0_low[4];
  OpaqueFloats3 pick_004ccae0_high[4];
  Word pick_004ccae0_flag[4];
  unsigned pick_004ccae0_calls;

  bool build_004da3a0;
};

PortState g_port;

void reset_ports() {
  std::memset(&g_port, 0, sizeof g_port);
  g_port.probe_00526430 = true;
  g_port.budget_004bf0a0 = true;
  for (std::size_t i = 0; i < 4; ++i) {
    g_port.pick_004ccae0_result[i] = true;
  }
  g_real_013ef54c = 1.1F;
}

OpaqueNotifyTable g_notify_table;
OpaquePaintNode g_notify_node;
OpaquePaintNode g_peer_node;
OpaquePaintNode g_first_node;

}  // namespace

extern "C" void PKG_EDITOR_SAFE_WAVE11_STDCALL model_notify_028(Word first,
                                                                Word second) {
  ++g_port.notify_calls;
  g_port.notify_first = first;
  g_port.notify_second = second;
}

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_00526430(OpaqueWords3* self) {
  ++g_port.probe_00526430_calls;
  g_port.probe_00526430_arg = self;
  return g_port.probe_00526430;
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_004b1cc0(void* self, OpaqueWords3* first, void* second, Byte third) {
  ++g_port.range_004b1cc0_calls;
  g_port.range_004b1cc0_self = self;
  g_port.range_004b1cc0_first = first;
  g_port.range_004b1cc0_second = second;
  g_port.range_004b1cc0_third = third;
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_004aff80(void* self, Signed count) {
  (void)self;
  ++g_port.size_004aff80_calls;
  g_port.size_004aff80_count = count;
}

extern "C" const OpaqueRecord* PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_0044ae00(void* self, OpaqueRecord* out, Word arg1, Word arg2,
                    Word arg3) {
  ++g_port.build_0044ae00_calls;
  g_port.build_0044ae00_self = self;
  g_port.build_0044ae00_arg1 = arg1;
  g_port.build_0044ae00_arg2 = arg2;
  g_port.build_0044ae00_arg3 = arg3;
  std::memcpy(out, &g_port.build_0044ae00_seed,
              sizeof g_port.build_0044ae00_seed);
  return out;
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_CDECL
unresolved_0041dba0(void* first, const Real* second) {
  if (g_port.offset_0041dba0_calls < 2u) {
    g_port.offset_0041dba0_first[g_port.offset_0041dba0_calls] = first;
  }
  ++g_port.offset_0041dba0_calls;
  g_port.offset_0041dba0_value = *second;
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_00409930(OpaqueBox* self) {
  ++g_port.init_00409930_calls;
  std::memcpy(self, &g_port.init_00409930_seed,
              sizeof g_port.init_00409930_seed);
}

extern "C" void PKG_EDITOR_SAFE_WAVE11_THISCALL
unresolved_00409dd0(OpaqueRecord* first, const OpaqueBox* second) {
  ++g_port.apply_00409dd0_calls;
  g_port.apply_00409dd0_first = first;
  std::memcpy(&g_port.apply_00409dd0_seed, second,
              sizeof g_port.apply_00409dd0_seed);
}

extern "C" bool PKG_EDITOR_SAFE_WAVE11_CDECL unresolved_004bf0a0(void* first,
                                                                 void* second,
                                                                 Word third) {
  ++g_port.budget_004bf0a0_calls;
  g_port.budget_004bf0a0_first = first;
  g_port.budget_004bf0a0_second = second;
  g_port.budget_004bf0a0_third = third;
  return g_port.budget_004bf0a0;
}

extern "C" bool PKG_EDITOR_SAFE_WAVE11_THISCALL unresolved_004ccae0(
    void* self, OpaqueFloats3 low, OpaqueFloats3 high, OpaqueWords3* first,
    OpaqueWords3* second, Real* value, Word flag) {
  const std::size_t index =
      g_port.pick_004ccae0_calls < 4u ? g_port.pick_004ccae0_calls : 3u;
  ++g_port.pick_004ccae0_calls;
  g_port.pick_004ccae0_self[index] = self;
  g_port.pick_004ccae0_low[index] = low;
  g_port.pick_004ccae0_high[index] = high;
  g_port.pick_004ccae0_flag[index] = flag;
  *first = g_port.pick_004ccae0_first[index];
  *second = g_port.pick_004ccae0_second[index];
  *value = g_port.pick_004ccae0_value[index];
  return g_port.pick_004ccae0_result[index];
}

namespace {

OpaquePaintState g_state;

void setup_paint() {
  std::memset(&g_notify_table, 0, sizeof g_notify_table);
  g_notify_table.notify_028 = model_notify_028;
  std::memset(&g_notify_node, 0, sizeof g_notify_node);
  std::memset(&g_peer_node, 0, sizeof g_peer_node);
  std::memset(&g_first_node, 0, sizeof g_first_node);
  std::memset(&g_state, 0, sizeof g_state);
  g_notify_node.slot_000 = &g_notify_table;
  g_state.node_3ec = &g_notify_node;
  g_state.node_3f0 = &g_peer_node;
  g_state.node_010 = &g_first_node;
}

}  // namespace

void test_paint_early_return() {
  reset_ports();
  setup_paint();
  g_state.pair_038.mark_00 = 0x11u;
  g_state.pair_038.tag_01 = 0x22u;
  g_state.word_040 = 0x2211u;
  g_state.applied_044 = 5u;
  check(!editor_paint_commit_0043ac40(&g_state, 5u, 0u, 0u),
        "0043ac40 returns false when the mirror already matches");
  check(g_port.notify_calls == 0u, "0043ac40 early return does not notify");
  check(g_notify_node.word_004 == 0u, "0043ac40 early return leaves the mask");
  check(g_state.value_03c == 5u, "0043ac40 still stores the new value");
}

void test_paint_quiet_forces_commit() {
  reset_ports();
  setup_paint();
  g_state.applied_044 = 0u;
  g_state.value_03c = 0u;
  check(editor_paint_commit_0043ac40(&g_state, 0u, 0u, 1u),
        "0043ac40 honours the quiet override");
  check(g_port.notify_calls == 1u, "0043ac40 notifies once on the override");
  check(g_port.notify_first == 0u && g_port.notify_second == 10u,
        "0043ac40 case zero with both marks clear notifies zero then ten");
  check(g_peer_node.word_004 == 0u, "0043ac40 clears the peer mask");
  check(g_first_node.word_004 == kMask003, "0043ac40 raises the first mask");
  check(g_first_node.code_05c == 10u, "0043ac40 first code is ten");
}

void test_paint_case_five_raises() {
  reset_ports();
  setup_paint();
  g_peer_node.word_004 = kMask003;
  g_first_node.word_004 = 0u;
  check(editor_paint_commit_0043ac40(&g_state, 5u, 0u, 1u),
        "0043ac40 case five returns true");
  check(g_port.notify_calls == 1u, "0043ac40 case five notifies once");
  check(g_port.notify_second == 12u,
        "0043ac40 case five notifies one then twelve");
  check(g_peer_node.word_004 == kMask003,
        "0043ac40 case five leaves the peer mask already raised");
  check(g_first_node.word_004 == kMask003,
        "0043ac40 case five raises the first mask through the live OR arm");
  check(g_peer_node.code_05c == 12u && g_first_node.code_05c == 12u,
        "0043ac40 case five writes twelve to both codes");
}

void test_paint_case_five_keeps_other_bits() {
  reset_ports();
  setup_paint();
  g_peer_node.word_004 = 0xfffffff0u;
  g_first_node.word_004 = 0x00000001u;
  check(editor_paint_commit_0043ac40(&g_state, 5u, 0u, 1u),
        "0043ac40 case five returns true with a populated mask");
  check(g_peer_node.word_004 == 0xfffffff8u,
        "0043ac40 case five never clears the peer mask");
  check(g_first_node.word_004 == 0x00000009u,
        "0043ac40 case five only sets bit three on the first mask");
}

void test_paint_case_one_two_four() {
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 1u, 0u, 1u),
        "0043ac40 case one returns true");
  check(g_port.notify_first == 1u && g_port.notify_second == 6u,
        "0043ac40 case one notifies one then six");
  check(g_peer_node.code_05c == 6u && g_first_node.code_05c == 6u,
        "0043ac40 case one writes six to both codes");
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 2u, 0u, 1u),
        "0043ac40 case two returns true");
  check(g_port.notify_second == 9u, "0043ac40 case two notifies one then nine");
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 4u, 0u, 1u),
        "0043ac40 case four returns true");
  check(g_port.notify_second == 11u,
        "0043ac40 case four notifies one then eleven");
  check(g_peer_node.code_05c == 11u && g_first_node.code_05c == 11u,
        "0043ac40 case four writes eleven to both codes");
}

void test_paint_case_zero_arms() {
  reset_ports();
  setup_paint();
  g_state.pair_038.mark_00 = 1u;
  g_state.pair_038.tag_01 = 1u;
  check(editor_paint_commit_0043ac40(&g_state, 0u, 0u, 1u),
        "0043ac40 case zero with both marks returns true");
  check(g_port.notify_first == 1u && g_port.notify_second == 8u,
        "0043ac40 case zero with both marks notifies one then eight");
  check(g_peer_node.word_004 == 0u,
        "0043ac40 case zero with both marks leaves the peer alone");
  check(g_first_node.word_004 == kMask003,
        "0043ac40 case zero with both marks raises only the first");
  reset_ports();
  setup_paint();
  g_state.pair_038.tag_01 = 1u;
  check(editor_paint_commit_0043ac40(&g_state, 0u, 0u, 1u),
        "0043ac40 case zero with the tag only returns true");
  check(g_port.notify_second == 7u,
        "0043ac40 case zero with the tag only notifies one then seven");
  check(g_peer_node.word_004 == kMask003 && g_first_node.word_004 == kMask003,
        "0043ac40 case zero with the tag only raises both");
  reset_ports();
  setup_paint();
  g_state.pair_038.mark_00 = 1u;
  check(editor_paint_commit_0043ac40(&g_state, 0u, 0u, 1u),
        "0043ac40 case zero with the mark only returns true");
  check(g_port.notify_second == 5u,
        "0043ac40 case zero with the mark only notifies one then five");
  check(g_peer_node.code_05c == 5u && g_first_node.code_05c == 5u,
        "0043ac40 case zero with the mark only writes five to both");
}

void test_paint_case_three_and_default() {
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 3u, 0u, 1u),
        "0043ac40 case three returns true");
  check(g_port.notify_calls == 0u,
        "0043ac40 case three performs no side effect");
  check(g_state.applied_044 == 3u,
        "0043ac40 case three still mirrors before the switch");
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 9u, 0u, 1u),
        "0043ac40 default returns true");
  check(g_port.notify_calls == 0u, "0043ac40 default performs no side effect");
  reset_ports();
  setup_paint();
  check(editor_paint_commit_0043ac40(&g_state, 6u, 0u, 1u),
        "0043ac40 a value above the switch range returns true");
  check(g_port.notify_calls == 0u,
        "0043ac40 a value above the switch range performs no side effect");
}

void test_paint_absent_targets() {
  reset_ports();
  setup_paint();
  g_state.node_3ec = nullptr;
  check(editor_paint_commit_0043ac40(&g_state, 1u, 0u, 1u),
        "0043ac40 tolerates a null notify target");
  check(g_port.notify_calls == 0u, "0043ac40 skips the null notify target");
  check(g_peer_node.word_004 == kMask003,
        "0043ac40 still raises the peer when the target is null");
  reset_ports();
  setup_paint();
  g_state.node_3f0 = nullptr;
  g_state.node_010 = nullptr;
  check(editor_paint_commit_0043ac40(&g_state, 1u, 0u, 1u),
        "0043ac40 tolerates null state nodes");
  check(g_port.notify_calls == 1u, "0043ac40 notifies before the null nodes");
}

namespace {

OpaqueEntryElement g_entry;
OpaqueEntryElement* g_entry_slots[2];
OpaqueEntryList g_list;
alignas(4) OpaqueRecord g_records[4];

void setup_list() {
  std::memset(&g_entry, 0, sizeof g_entry);
  std::memset(&g_list, 0, sizeof g_list);
  std::memset(g_records, 0, sizeof g_records);
  g_entry.seed_048[0] = 0x3f800000u;
  g_entry.seed_048[1] = 0x40000000u;
  g_entry.seed_048[2] = 0x40400000u;
  for (std::size_t i = 0; i < 9; ++i) {
    g_entry.basis_060[i] = 0x3f000000u;
  }
  g_entry.span_1d8 = 12.5F;
  g_entry_slots[0] = &g_entry;
  g_entry_slots[1] = nullptr;
  g_list.begin_018 = g_entry_slots;
  g_list.end_01c = g_entry_slots + 1;
}

}  // namespace

void test_entry_fallback_branch() {
  reset_ports();
  setup_list();
  g_port.probe_00526430 = false;
  g_list.tail_0d4.tail_03 = 0xffu;
  editor_entry_expand_004ad6f0(&g_list, g_records);
  check(g_port.probe_00526430_calls == 1u, "004ad6f0 probes the range once");
  check(g_port.probe_00526430_arg == &g_list.range_0c8,
        "004ad6f0 probes the range field itself");
  check(g_port.range_004b1cc0_calls == 1u,
        "004ad6f0 fallback calls the range port");
  check(g_port.range_004b1cc0_self == g_records,
        "004ad6f0 fallback passes the records as the receiver");
  check(g_port.range_004b1cc0_first == &g_list.range_0c8,
        "004ad6f0 fallback passes the range as the first argument");
  check(g_port.range_004b1cc0_second == &g_list.range_0c8.word_04,
        "004ad6f0 fallback passes self+0xcc as the second argument");
  check(g_port.range_004b1cc0_third == kUninitialisedFallbackByte,
        "004ad6f0 fallback passes the unwritten frame byte as the third");
  check(g_port.range_004b1cc0_third != g_list.tail_0d4.tail_03,
        "004ad6f0 fallback never reads the tail block at self+0xd4");
  check(g_port.size_004aff80_calls == 0u,
        "004ad6f0 fallback never sizes the rows");
  check(g_port.build_0044ae00_calls == 0u,
        "004ad6f0 fallback never enters the loop");
}

void test_entry_expand_branch() {
  reset_ports();
  setup_list();
  for (std::size_t i = 0; i < 0x18; ++i) {
    g_port.build_0044ae00_seed.opaque_00[i] = static_cast<Byte>(i + 1u);
  }
  g_port.init_00409930_seed.code_00 = 0x0010u;
  g_port.init_00409930_seed.count_02 = 0u;
  editor_entry_expand_004ad6f0(&g_list, g_records);
  check(g_port.size_004aff80_calls == 1u, "004ad6f0 sizes the rows once");
  check(g_port.size_004aff80_count == 1, "004ad6f0 passes the element count");
  check(g_port.build_0044ae00_calls == 1u, "004ad6f0 builds one row");
  check(g_port.build_0044ae00_arg1 == 2u && g_port.build_0044ae00_arg2 == 1u &&
            g_port.build_0044ae00_arg3 == 0u,
        "004ad6f0 passes the build constants two, one and zero");
  check(g_port.build_0044ae00_self == &g_entry,
        "004ad6f0 builds from the list element");
  check(g_port.offset_0041dba0_calls == 0u,
        "004ad6f0 skips the offset port when the mark bit is clear");
  check(g_port.init_00409930_calls == 1u, "004ad6f0 initialises the box once");
  check(g_port.apply_00409dd0_calls == 1u, "004ad6f0 applies the box once");
  check(g_port.apply_00409dd0_first == g_records,
        "004ad6f0 applies the box to the row base");
  check(g_port.apply_00409dd0_seed.code_00 == 0x0016u,
        "004ad6f0 raises the box code with four then two");
  check(g_port.apply_00409dd0_seed.count_02 == 3u,
        "004ad6f0 bumps the box count three times");
  check(g_port.apply_00409dd0_seed.span_04[0] == 0x3f800000u &&
            g_port.apply_00409dd0_seed.span_04[1] == 0x40000000u &&
            g_port.apply_00409dd0_seed.span_04[2] == 0x40400000u,
        "004ad6f0 copies the element seed words into the box");
  bool basis_same = true;
  for (std::size_t lane = 0; lane < 9; ++lane) {
    if (g_port.apply_00409dd0_seed.basis_14[lane] != g_entry.basis_060[lane]) {
      basis_same = false;
    }
  }
  check(basis_same, "004ad6f0 copies the whole element basis into the box");
  check(g_port.apply_00409dd0_seed.extra_10 == 12.5F,
        "004ad6f0 copies the element span last");
  bool same = true;
  for (std::size_t i = 0; i < 0x18; ++i) {
    if (g_records[0].opaque_00[i] != static_cast<Byte>(i + 1u)) {
      same = false;
    }
  }
  check(same, "004ad6f0 copies the whole twenty four byte row");
}

void test_entry_marked_offsets() {
  reset_ports();
  setup_list();
  g_entry.marks_0dc8 = 0x00000400u;
  editor_entry_expand_004ad6f0(&g_list, g_records);
  check(g_port.offset_0041dba0_calls == 2u,
        "004ad6f0 calls the offset port twice when the mark bit is set");
  check(g_port.offset_0041dba0_first[0] == g_records,
        "004ad6f0 offsets the row base first");
  check(static_cast<const Byte*>(g_port.offset_0041dba0_first[1]) ==
            g_records[0].opaque_00 + 0x0c,
        "004ad6f0 offsets the second half of the row second");
  check(g_port.offset_0041dba0_value == 1.1F,
        "004ad6f0 offsets with the shared scalar");
}

namespace {

bool g_gate_result[16];
unsigned g_gate_calls;
void* g_gate_first[16];
Word g_gate_second[16];

bool PKG_EDITOR_SAFE_WAVE11_STDCALL model_gate(const void* first, Word second) {
  const std::size_t index = g_gate_calls < 16u ? g_gate_calls : 15u;
  g_gate_first[index] = const_cast<void*>(first);
  g_gate_second[index] = second;
  ++g_gate_calls;
  return g_gate_result[index];
}

OpaqueProbeTable g_gate_table;
OpaqueProbeOwner g_gate_owner;
OpaqueBakeRow g_row;
alignas(4) Word g_row_pool[1024];

void setup_row() {
  std::memset(&g_gate_table, 0, sizeof g_gate_table);
  g_gate_table.slot_038 = model_gate;
  std::memset(&g_gate_owner, 0, sizeof g_gate_owner);
  g_gate_owner.table_000 = &g_gate_table;
  std::memset(&g_row, 0, sizeof g_row);
  std::memset(g_row_pool, 0, sizeof g_row_pool);
  for (std::size_t i = 0; i < 16; ++i) {
    g_gate_result[i] = true;
  }
  g_gate_calls = 0u;
  g_row.block_098.begin_00 = g_row_pool;
  g_row.block_098.end_04 = g_row_pool + kProbeStride;
  g_row.block_0ac.begin_00 = g_row_pool + 0x100;
  g_row.block_0ac.end_04 = g_row_pool + 0x104;
  g_row.block_0e8.begin_00 = g_row_pool + 0x200;
  g_row.block_0e8.end_04 = g_row_pool + 0x204;
  g_row.block_114.begin_00 = g_row_pool + 0x300;
  g_row.block_114.end_04 = g_row_pool + 0x300 + kSeatStride;
  g_row.keys_0c0 = g_row_pool + 0x10;
  g_row.marks_0d4 = g_row_pool + 0x18;
  g_row.weights_0fc = g_row_pool + 0x20;
}

}  // namespace

void test_probe_success_order() {
  reset_ports();
  setup_row();
  check(editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 returns true when every gate passes");
  check(g_gate_calls == 10u, "004bf770 dispatches ten gate slots");
  check(g_port.budget_004bf0a0_calls == 1u,
        "004bf770 calls the budget gate once");
  check(g_port.budget_004bf0a0_first == &g_gate_owner,
        "004bf770 passes the owner to the budget gate");
  check(g_port.budget_004bf0a0_second == g_row.opaque_018,
        "004bf770 passes the row payload base to the budget gate");
  check(g_port.budget_004bf0a0_third == 0x80u,
        "004bf770 passes the fixed probe budget");
  check(g_gate_first[0] != nullptr && g_gate_second[0] == 8u,
        "004bf770 first gate passes the descriptor and eight");
  check(g_gate_second[1] == 0x10u, "004bf770 second gate passes sixteen");
  check(g_gate_first[2] == g_row.block_098.begin_00 &&
            g_gate_second[2] == kProbeStride,
        "004bf770 third gate passes the group block and its byte size");
  check(g_gate_first[3] == g_row.block_0ac.begin_00 && g_gate_second[3] == 4u,
        "004bf770 fourth gate passes the span block and its byte size");
  check(g_gate_first[4] == g_row.keys_0c0 && g_gate_second[4] == 1u,
        "004bf770 fifth gate passes the key table and the span count");
  check(g_gate_first[5] == g_row.marks_0d4 && g_gate_second[5] == 4u,
        "004bf770 sixth gate passes the mark table and its byte size");
  check(g_gate_first[6] == g_row.block_0e8.begin_00 && g_gate_second[6] == 4u,
        "004bf770 seventh gate passes the link block and its byte size");
  check(g_gate_first[7] == g_row.weights_0fc && g_gate_second[7] == 4u,
        "004bf770 eighth gate passes the weight table and its byte size");
  check(g_gate_first[8] == &g_row.head_110 && g_gate_second[8] == 4u,
        "004bf770 ninth gate passes the head field and four");
  check(g_gate_first[9] == g_row.block_114.begin_00 &&
            g_gate_second[9] == kSeatStride,
        "004bf770 tenth gate passes the seat block and its byte size");
}

void test_probe_short_circuits() {
  reset_ports();
  setup_row();
  g_gate_result[0] = false;
  check(!editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 fails when the first gate fails");
  check(g_gate_calls == 1u, "004bf770 stops at the first failing gate");
  check(g_port.budget_004bf0a0_calls == 0u,
        "004bf770 skips the budget gate after the first failure");
  reset_ports();
  setup_row();
  g_gate_result[1] = false;
  check(!editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 fails when the second gate fails");
  check(g_gate_calls == 2u, "004bf770 stops at the second failing gate");
  reset_ports();
  setup_row();
  g_port.budget_004bf0a0 = false;
  check(!editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 fails when the budget gate fails");
  check(g_gate_calls == 2u, "004bf770 stops after the budget gate fails");
  reset_ports();
  setup_row();
  g_gate_result[3] = false;
  check(!editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 fails when a middle gate fails");
  check(g_gate_calls == 4u, "004bf770 stops at the failing middle gate");
  reset_ports();
  setup_row();
  g_gate_result[9] = false;
  check(!editor_bake_probe_004bf770(&g_gate_owner, &g_row),
        "004bf770 fails when the last gate fails");
  check(g_gate_calls == 10u, "004bf770 reaches the last gate");
}

namespace {

OpaqueBakeEntryPair g_pairs[3];
OpaqueBakeRoot g_root;
alignas(4) Word g_root_pool[8];

void setup_root() {
  std::memset(g_pairs, 0, sizeof g_pairs);
  std::memset(&g_root, 0, sizeof g_root);
  std::memset(g_root_pool, 0, sizeof g_root_pool);
  for (std::size_t i = 0; i < 4; ++i) {
    g_port.pick_004ccae0_result[i] = true;
  }
  g_root.primary_018 = g_root_pool;
  g_root.secondary_01c = g_root_pool + 1;
  g_root.entries_048.begin_00 = g_pairs;
  g_root.entries_048.end_04 = g_pairs + 3;
  g_pairs[0].first_00 = g_root_pool + 2;
  g_pairs[0].second_04 = g_root_pool + 3;
  g_pairs[1].first_00 = nullptr;
  g_pairs[1].second_04 = g_root_pool + 4;
  g_pairs[2].first_00 = g_root_pool + 5;
  g_pairs[2].second_04 = g_root_pool + 6;
}

}  // namespace

void test_select_mode_passthrough() {
  reset_ports();
  setup_root();
  Word first[3] = {0u, 0u, 0u};
  Word second[3] = {0u, 0u, 0u};
  Real value = 0.0F;
  g_port.pick_004ccae0_first[0] = OpaqueWords3{7u, 8u, 9u};
  check(editor_bake_select_004c4a30(&g_root, 0, 1.0F, 2.0F, 3.0F, 4.0F, 5.0F,
                                    6.0F, first, second, &value, 3u),
        "004c4a30 mode zero returns the primary result");
  check(g_port.pick_004ccae0_calls == 1u, "004c4a30 mode zero dispatches once");
  check(g_port.pick_004ccae0_self[0] == g_root.primary_018,
        "004c4a30 mode zero selects the primary receiver");
  check(g_port.pick_004ccae0_low[0].x_00 == 1.0F &&
            g_port.pick_004ccae0_low[0].z_08 == 3.0F,
        "004c4a30 mode zero forwards the low triple");
  check(g_port.pick_004ccae0_high[0].x_00 == 4.0F &&
            g_port.pick_004ccae0_high[0].z_08 == 6.0F,
        "004c4a30 mode zero forwards the high triple");
  check(g_port.pick_004ccae0_flag[0] == 3u,
        "004c4a30 mode zero zero extends the flag byte");
  check(first[0] == 7u && first[2] == 9u,
        "004c4a30 mode zero writes through the first out");
  check(value == 0.0F, "004c4a30 mode zero writes the scalar out");
  reset_ports();
  setup_root();
  g_port.pick_004ccae0_result[0] = false;
  check(!editor_bake_select_004c4a30(&g_root, 1, 0u, 0u, 0u, 0u, 0u, 0u, first,
                                     second, &value, 0u),
        "004c4a30 mode one forwards a false result");
  check(g_port.pick_004ccae0_self[0] == g_root.secondary_01c,
        "004c4a30 mode one selects the secondary receiver");
}

void test_select_unknown_mode() {
  reset_ports();
  setup_root();
  Word first[3] = {0u, 0u, 0u};
  Word second[3] = {0u, 0u, 0u};
  Real value = 0.0F;
  check(!editor_bake_select_004c4a30(&g_root, 3, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                     0.0F, first, second, &value, 0u),
        "004c4a30 rejects an unknown mode");
  check(g_port.pick_004ccae0_calls == 0u,
        "004c4a30 dispatches nothing for an unknown mode");
  check(!editor_bake_select_004c4a30(&g_root, -1, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                     0.0F, first, second, &value, 0u),
        "004c4a30 rejects a negative mode");
  check(g_port.pick_004ccae0_calls == 0u,
        "004c4a30 dispatches nothing for a negative mode");
}

void test_select_scan_picks_smallest() {
  reset_ports();
  setup_root();
  Word first[3] = {0u, 0u, 0u};
  Word second[3] = {0u, 0u, 0u};
  Real value = 0.0F;
  g_port.pick_004ccae0_value[0] = 5.0F;
  g_port.pick_004ccae0_first[0] = OpaqueWords3{1u, 2u, 3u};
  g_port.pick_004ccae0_second[0] = OpaqueWords3{4u, 5u, 6u};
  g_port.pick_004ccae0_value[1] = 2.0F;
  g_port.pick_004ccae0_first[1] = OpaqueWords3{7u, 8u, 9u};
  g_port.pick_004ccae0_second[1] = OpaqueWords3{10u, 11u, 12u};
  g_port.pick_004ccae0_value[2] = 9.0F;
  check(editor_bake_select_004c4a30(&g_root, 2, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                    0.0F, first, second, &value, 1u),
        "004c4a30 mode two returns true when a slot answers");
  check(g_port.pick_004ccae0_calls == 2u,
        "004c4a30 mode two skips the null pair and stops after the winner");
  check(g_port.pick_004ccae0_self[0] == g_pairs[0].second_04,
        "004c4a30 mode two uses the first non null pair");
  check(first[0] == 7u && first[1] == 8u && first[2] == 9u,
        "004c4a30 mode two publishes the winning first block");
  check(second[0] == 10u && second[2] == 12u,
        "004c4a30 mode two publishes the winning second block");
  check(value == 2.0F, "004c4a30 mode two publishes the winning scalar");
}

void test_select_scan_keeps_first_on_tie() {
  reset_ports();
  setup_root();
  Word first[3] = {0u, 0u, 0u};
  Word second[3] = {0u, 0u, 0u};
  Real value = 0.0F;
  g_port.pick_004ccae0_value[0] = 4.0F;
  g_port.pick_004ccae0_first[0] = OpaqueWords3{1u, 0u, 0u};
  g_port.pick_004ccae0_value[1] = 4.0F;
  g_port.pick_004ccae0_first[1] = OpaqueWords3{2u, 0u, 0u};
  check(editor_bake_select_004c4a30(&g_root, 2, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                    0.0F, first, second, &value, 0u),
        "004c4a30 mode two succeeds on a tie");
  check(first[0] == 1u, "004c4a30 mode two keeps the earlier slot on a tie");
  check(g_port.pick_004ccae0_calls == 2u,
        "004c4a30 mode two visits both tied slots");
}

void test_select_scan_no_answer() {
  reset_ports();
  setup_root();
  Word first[3] = {0u, 0u, 0u};
  Word second[3] = {0u, 0u, 0u};
  Real value = 0.0F;
  g_port.pick_004ccae0_result[0] = false;
  g_port.pick_004ccae0_result[1] = false;
  check(!editor_bake_select_004c4a30(&g_root, 2, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
                                     0.0F, first, second, &value, 0u),
        "004c4a30 mode two fails when nothing answers");
  check(g_port.pick_004ccae0_calls == 2u,
        "004c4a30 mode two visits every pair");
  check(first[0] == 0u && second[0] == 0u && value == 0.0F,
        "004c4a30 mode two leaves the outs untouched when nothing answers");
}

}  // namespace openspore::reconstruction::pkg_editor_safe_wave11

int main() {
  namespace ns = openspore::reconstruction::pkg_editor_safe_wave11;
  ns::test_paint_early_return();
  ns::test_paint_quiet_forces_commit();
  ns::test_paint_case_five_raises();
  ns::test_paint_case_five_keeps_other_bits();
  ns::test_paint_case_one_two_four();
  ns::test_paint_case_zero_arms();
  ns::test_paint_case_three_and_default();
  ns::test_paint_absent_targets();
  ns::test_entry_fallback_branch();
  ns::test_entry_expand_branch();
  ns::test_entry_marked_offsets();
  ns::test_probe_success_order();
  ns::test_probe_short_circuits();
  ns::test_select_mode_passthrough();
  ns::test_select_unknown_mode();
  ns::test_select_scan_picks_smallest();
  ns::test_select_scan_keeps_first_on_tie();
  ns::test_select_scan_no_answer();
  std::printf("%s\n", ns::g_failures == 0
                          ? "pkg-editor-safe-wave11: all checks passed"
                          : "pkg-editor-safe-wave11: model test FAILED");
  return ns::g_failures == 0 ? 0 : 1;
}
