#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>
#include <vector>

#include "app_safe_wave11.hpp"

namespace openspore::reconstruction::pkg_app_safe_wave11 {
namespace {

static_assert(std::is_same<decltype(property_record_assign_pair_004279d0(
                               static_cast<OpaquePropertyRecord*>(nullptr),
                               static_cast<void*>(nullptr))),
                           OpaquePropertyRecord*>::value,
              "004279d0 returns the receiver pointer");
static_assert(std::is_same<decltype(property_record_assign_scalar_00428060(
                               static_cast<OpaquePropertyRecord*>(nullptr),
                               static_cast<const TargetFloat*>(nullptr))),
                           OpaquePropertyRecord*>::value,
              "00428060 returns the receiver pointer");
static_assert(std::is_void<decltype(model_parts_apply_properties_00447150(
                  static_cast<OpaquePartList*>(nullptr),
                  static_cast<OpaqueVtableHolder*>(nullptr)))>::value,
              "00447150 returns no value");
static_assert(std::is_void<decltype(pair_vector_insert_004786e0(
                  static_cast<OpaqueSlotVector*>(nullptr), TargetWord{0},
                  static_cast<const TargetWord*>(nullptr)))>::value,
              "004786e0 returns no value");
static_assert(std::is_same<decltype(pair_vector_construct_004b62a0(
                               static_cast<OpaquePairVector*>(nullptr),
                               static_cast<const TargetWord*>(nullptr))),
                           OpaquePairVector*>::value,
              "004b62a0 returns the receiver pointer");
static_assert(std::is_same<decltype(stream_probe_dispatch_004bc540(
                               static_cast<OpaqueVtableHolder*>(nullptr),
                               static_cast<OpaqueVtableHolder*>(nullptr),
                               static_cast<OpaqueVtableHolder*>(nullptr),
                               TargetWord{0}, TargetWord{0})),
                           TargetByte>::value,
              "004bc540 returns a single byte");
static_assert(sizeof(stream_probe_dispatch_004bc540(
                  static_cast<OpaqueVtableHolder*>(nullptr),
                  static_cast<OpaqueVtableHolder*>(nullptr),
                  static_cast<OpaqueVtableHolder*>(nullptr), TargetWord{0},
                  TargetWord{0})) == 1,
              "004bc540 return width is one byte");
static_assert(std::is_same<decltype(sar_shift(-8, 1)), TargetSigned>::value,
              "sar_shift returns a signed word");
static_assert(sar_shift(-1, 31) == -1, "sar_shift is arithmetic");
static_assert(sar_shift(-8, 2) == -2, "sar_shift shifts negatives");
static_assert(sar_count(-8, 2) == 0xfffffffEu, "sar_count keeps the sign bits");
static_assert(array_mask(0x0030u) == 0x0030u, "array mask keeps 0x30");
static_assert(array_mask(0x0002u) == 0u, "array mask drops other bits");
static_assert(kPairStride == 8u, "pair stride");

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

TargetWord address(const void* pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

TargetWord load(const void* pointer) {
  TargetWord value = 0u;
  std::memcpy(&value, pointer, sizeof(value));
  return value;
}

void store(void* pointer, TargetWord value) {
  std::memcpy(pointer, &value, sizeof(value));
}

TargetFloat load_float(const void* pointer) {
  TargetFloat value = 0.0f;
  std::memcpy(&value, pointer, sizeof(value));
  return value;
}

struct PropertyTrace {
  std::uint32_t notify_calls;
  std::uintptr_t notify_receiver;
  TargetByte notify_flag;
  std::uint32_t store_calls;
  std::uintptr_t store_receiver;
  TargetSigned store_kind;
  TargetWord store_field;
  std::uintptr_t store_source;
  TargetSigned store_size;
  TargetSigned store_count;
  std::uint32_t insert_calls;
  TargetWord find_root;
  TargetSigned find_key[3];
  std::uint32_t reserve_calls;
  TargetWord reserve_count;
  std::uint32_t pair_insert_calls;
  TargetWord pair_insert_slot;
  TargetWord pair_insert_begin;
  TargetWord pair_insert_end;
  std::uint32_t assoc_reserve_calls;
  TargetWord assoc_reserve_count;
  std::uint32_t slot_calls;
  TargetWord slot_key;
  std::uint32_t tree_calls;
  std::uintptr_t tree_receiver;
  TargetWord tree_key;
  OpaqueWordPair tree_pair;
  TargetWord tree_first_key;
  OpaqueWordPair tree_first_pair;
  std::uint32_t append_calls;
  std::uintptr_t append_receiver;
  std::uint32_t array_bool_calls;
  void* array_bool_list;
  TargetWord array_bool_code;
  std::size_t array_bool_span;
  const TargetByte* array_bool_values;
  std::uint32_t release_calls;
  std::uintptr_t release_vector;
  std::uint32_t find_calls;
  std::uint32_t has_calls;
  OpaqueVtableHolder* has_receiver;
  TargetWord has_first_code;
  TargetWord has_code;
  const OpaquePropertyRecord* get_result;
  std::uint32_t get_calls;
  TargetWord get_code;
  std::array<std::pair<TargetWord, const OpaquePropertyRecord*>, 8> published;
  std::size_t published_count;
};

PropertyTrace g_property;

struct SlotTrace {
  std::uint32_t allocate_calls;
  TargetWord allocate_arena;
  TargetWord allocate_size;
  TargetWord allocate_align;
  TargetWord allocate_fill;
  std::uint32_t release_calls;
  std::vector<TargetWord> release_order;
  std::uint32_t push_calls;
  std::uintptr_t push_receiver;
  TargetWord push_begin;
  TargetWord push_end;
  TargetByte push_tag;
  std::vector<std::vector<TargetWord>> blocks;
  std::vector<TargetWord*> owned;
};

SlotTrace g_slot;

struct StreamTrace {
  std::uint32_t lookup_calls;
  TargetWord lookup_input;
  TargetWord lookup_result;
  std::uint32_t read_calls;
  TargetWord read_first;
  TargetWord read_second;
  TargetWord read_result;
  std::uint32_t apply_calls;
  TargetWord apply_first;
  TargetWord apply_second;
  TargetWord apply_third;
  TargetByte apply_result;
  std::uint32_t report_calls;
  TargetWord report_first;
  TargetWord report_second;
  std::uint32_t probe_calls;
  std::uintptr_t probe_receiver;
  TargetWord probe_result;
  std::uint32_t resolve_calls;
  std::uintptr_t resolve_receiver;
  TargetWord resolve_input;
  TargetWord resolve_result;
};

StreamTrace g_stream;

void reset_property() {
  std::memset(static_cast<void*>(&g_property), 0, sizeof(g_property));
  g_property.published_count = 0u;
}

void reset_slot() {
  g_slot.allocate_calls = 0u;
  g_slot.allocate_arena = 0u;
  g_slot.allocate_size = 0u;
  g_slot.allocate_align = 0u;
  g_slot.allocate_fill = 0u;
  g_slot.release_calls = 0u;
  g_slot.release_order.clear();
  g_slot.push_calls = 0u;
  g_slot.push_receiver = 0u;
  g_slot.push_begin = 0u;
  g_slot.push_end = 0u;
  g_slot.push_tag = 0u;
  g_slot.blocks.clear();
  g_slot.owned.clear();
}

void reset_stream() {
  std::memset(&g_stream, 0, sizeof(g_stream));
  g_stream.lookup_result = 0u;
  g_stream.read_result = 0u;
  g_stream.apply_result = 0u;
  g_stream.probe_result = 0u;
  g_stream.resolve_result = 0u;
}

void PKG_APP_SAFE_WAVE11_THISCALL
trace_notify_0093db80(OpaquePropertyRecord* receiver, TargetByte flag) {
  ++g_property.notify_calls;
  g_property.notify_receiver = address(receiver);
  g_property.notify_flag = flag;
}

TargetByte PKG_APP_SAFE_WAVE11_THISCALL trace_store_0093dd80(
    OpaquePropertyRecord* receiver, TargetSigned kind, TargetWord field,
    void* source, TargetSigned size, TargetSigned count) {
  ++g_property.store_calls;
  g_property.store_receiver = address(receiver);
  g_property.store_kind = kind;
  g_property.store_field = field;
  g_property.store_source = address(source);
  g_property.store_size = size;
  g_property.store_count = count;
  return 1u;
}

OpaquePropertyRecord* PKG_APP_SAFE_WAVE11_THISCALL
trace_insert_00423650(OpaquePropertyRecord* receiver, void*, TargetWord) {
  ++g_property.insert_calls;
  return receiver;
}

TargetWord PKG_APP_SAFE_WAVE11_FASTCALL
trace_find_root_0043c0a0(const OpaquePartList*) {
  return g_property.find_root;
}

TargetSigned PKG_APP_SAFE_WAVE11_THISCALL
trace_find_key_0043c120(const OpaquePartList*, TargetWord) {
  const std::uint32_t index = g_property.find_calls;
  ++g_property.find_calls;
  return g_property.find_key[index < 3u ? index : 2u];
}

void PKG_APP_SAFE_WAVE11_THISCALL
trace_reserve_00454b80(OpaqueWordVector* vector, TargetWord count) {
  ++g_property.reserve_calls;
  g_property.reserve_count = count;
  vector->last = vector->first + count * sizeof(TargetWord);
}

OpaqueWordVector* PKG_APP_SAFE_WAVE11_THISCALL
trace_pair_insert_00454cb0(TargetWord slot, TargetWord begin, TargetWord end) {
  ++g_property.pair_insert_calls;
  g_property.pair_insert_slot = slot;
  g_property.pair_insert_begin = begin;
  g_property.pair_insert_end = end;
  return reinterpret_cast<OpaqueWordVector*>(static_cast<std::uintptr_t>(slot));
}

void PKG_APP_SAFE_WAVE11_THISCALL
trace_pair_reserve_00454640(OpaqueAssocBlob*, TargetWord count) {
  ++g_property.assoc_reserve_calls;
  g_property.assoc_reserve_count = count;
}

TargetWord* PKG_APP_SAFE_WAVE11_THISCALL
trace_pair_slot_00454750(OpaqueAssocBlob* blob, const TargetWord* key) {
  ++g_property.slot_calls;
  g_property.slot_key = *key;
  return reinterpret_cast<TargetWord*>(blob->opaque_00_9b.data()) +
         (*key & 0x3u);
}

OpaqueTreeBlob* PKG_APP_SAFE_WAVE11_THISCALL trace_tree_insert_004544d0(
    OpaqueTreeBlob* tree, const TargetWord* key, const OpaqueWordPair* pair) {
  if (g_property.tree_calls == 0u) {
    g_property.tree_first_key = *key;
    g_property.tree_first_pair = *pair;
  }
  ++g_property.tree_calls;
  g_property.tree_receiver = address(tree);
  g_property.tree_key = *key;
  g_property.tree_pair = *pair;
  return tree;
}

void PKG_APP_SAFE_WAVE11_THISCALL
trace_node_append_005402c0(OpaqueTreeBlob* node) {
  ++g_property.append_calls;
  g_property.append_receiver = address(node);
}

void PKG_APP_SAFE_WAVE11_FASTCALL
trace_release_004c0b80(OpaqueWordVector* vector) {
  ++g_property.release_calls;
  g_property.release_vector = address(vector);
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL
trace_array_bool_006a0760(void* list, TargetWord code, std::size_t* count,
                          const TargetByte** values) {
  ++g_property.array_bool_calls;
  g_property.array_bool_list = list;
  g_property.array_bool_code = code;
  *count = g_property.array_bool_span;
  *values = g_property.array_bool_values;
  return 0u;
}

TargetByte PKG_APP_SAFE_WAVE11_THISCALL
trace_has_property_00447150(OpaqueVtableHolder* service, TargetWord code) {
  if (g_property.has_calls == 0u) {
    g_property.has_first_code = code;
  }
  ++g_property.has_calls;
  g_property.has_receiver = service;
  g_property.has_code = code;
  for (std::size_t i = 0u; i < g_property.published_count; ++i) {
    if (g_property.published[i].first == code) {
      return 1u;
    }
  }
  return 0u;
}

const OpaquePropertyRecord* PKG_APP_SAFE_WAVE11_THISCALL
trace_get_property_00447150(OpaqueVtableHolder*, TargetWord code) {
  ++g_property.get_calls;
  g_property.get_code = code;
  for (std::size_t i = 0u; i < g_property.published_count; ++i) {
    if (g_property.published[i].first == code) {
      return g_property.published[i].second;
    }
  }
  return nullptr;
}

void publish(TargetWord code, const OpaquePropertyRecord* record) {
  g_property.published[g_property.published_count].first = code;
  g_property.published[g_property.published_count].second = record;
  ++g_property.published_count;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL trace_global_key_a_015d(void) {
  return 0x0000a001u;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL trace_global_key_b_015d(void) {
  return 0x0000b002u;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL trace_global_key_c_015d(void) {
  return 0x0000c003u;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL trace_allocate_0042dee0(TargetWord arena,
                                                             TargetWord size,
                                                             TargetWord align,
                                                             TargetWord fill) {
  ++g_slot.allocate_calls;
  g_slot.allocate_arena = arena;
  g_slot.allocate_size = size;
  g_slot.allocate_align = align;
  g_slot.allocate_fill = fill;
  std::vector<TargetWord> block(static_cast<std::size_t>(size / 4u) + 2u, 0u);
  block[0] = 1u;
  if (fill != 0u) {
    std::memset(block.data() + 1, static_cast<int>(fill), size);
  }
  g_slot.blocks.push_back(block);
  TargetWord* const owned = g_slot.blocks.back().data() + 1;
  g_slot.owned.push_back(owned);
  if (align != 0u) {
    (void)align;
  }
  return address(owned);
}

void PKG_APP_SAFE_WAVE11_CDECL trace_release_00f47380(TargetWord pointer) {
  ++g_slot.release_calls;
  g_slot.release_order.push_back(pointer);
  TargetWord* const owner = reinterpret_cast<TargetWord*>(
      static_cast<std::uintptr_t>(pointer) - sizeof(TargetWord));
  *owner = 0u;
}

void PKG_APP_SAFE_WAVE11_THISCALL
trace_push_004b7290(OpaquePairVector* receiver, TargetWord begin,
                    TargetWord end, TargetByte tag) {
  ++g_slot.push_calls;
  g_slot.push_receiver = address(receiver);
  g_slot.push_begin = begin;
  g_slot.push_end = end;
  g_slot.push_tag = tag;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL
trace_stream_lookup_004c0500(TargetWord input) {
  ++g_stream.lookup_calls;
  g_stream.lookup_input = input;
  return g_stream.lookup_result;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL
trace_stream_read_004bf430(TargetWord first, TargetWord second) {
  ++g_stream.read_calls;
  g_stream.read_first = first;
  g_stream.read_second = second;
  return g_stream.read_result;
}

TargetByte PKG_APP_SAFE_WAVE11_CDECL trace_stream_apply_004bc6d0(
    TargetWord first, TargetWord second, TargetWord third) {
  ++g_stream.apply_calls;
  g_stream.apply_first = first;
  g_stream.apply_second = second;
  g_stream.apply_third = third;
  return g_stream.apply_result;
}

TargetWord PKG_APP_SAFE_WAVE11_CDECL
trace_stream_report_006ac0a0(TargetWord first, TargetWord second) {
  ++g_stream.report_calls;
  g_stream.report_first = first;
  g_stream.report_second = second;
  return 0u;
}

TargetWord PKG_APP_SAFE_WAVE11_THISCALL
trace_holder_probe_004bc540(OpaqueVtableHolder* receiver) {
  ++g_stream.probe_calls;
  g_stream.probe_receiver = address(receiver);
  return g_stream.probe_result;
}

TargetWord PKG_APP_SAFE_WAVE11_THISCALL
trace_holder_resolve_004bc540(OpaqueVtableHolder* receiver, TargetWord input) {
  ++g_stream.resolve_calls;
  g_stream.resolve_receiver = address(receiver);
  g_stream.resolve_input = input;
  return g_stream.resolve_result;
}

template <typename Ports>
struct PortScope {
  Ports saved;
  PortScope() : saved(property_runtime().ports) {
    const OpaquePropertyPorts& defaults = property_runtime().ports;
    OpaquePropertyPorts& ports = property_runtime().ports;
    ports = defaults;
    ports.notify_0093db80 = trace_notify_0093db80;
    ports.store_0093dd80 = trace_store_0093dd80;
    ports.insert_00423650 = trace_insert_00423650;
    ports.find_root_0043c0a0 = trace_find_root_0043c0a0;
    ports.find_key_0043c120 = trace_find_key_0043c120;
    ports.reserve_00454b80 = trace_reserve_00454b80;
    ports.pair_insert_00454cb0 = trace_pair_insert_00454cb0;
    ports.pair_reserve_00454640 = trace_pair_reserve_00454640;
    ports.pair_slot_00454750 = trace_pair_slot_00454750;
    ports.tree_insert_004544d0 = trace_tree_insert_004544d0;
    ports.node_append_005402c0 = trace_node_append_005402c0;
    ports.release_004c0b80 = trace_release_004c0b80;
    ports.array_bool_006a0760 = trace_array_bool_006a0760;
    ports.has_property_00447150 = trace_has_property_00447150;
    ports.get_property_00447150 = trace_get_property_00447150;
    ports.global_key_015d25b0 = trace_global_key_a_015d;
    ports.global_key_015d2180 = trace_global_key_b_015d;
    ports.global_key_015d22a4 = trace_global_key_c_015d;
    OpaqueSlotPorts& slots = slot_runtime().ports;
    slots.allocate_0042dee0 = trace_allocate_0042dee0;
    slots.release_00f47380 = trace_release_00f47380;
    slots.push_004b7290 = trace_push_004b7290;
    OpaqueStreamPorts& stream = stream_runtime().ports;
    stream.lookup_004c0500 = trace_stream_lookup_004c0500;
    stream.read_004bf430 = trace_stream_read_004bf430;
    stream.apply_004bc6d0 = trace_stream_apply_004bc6d0;
    stream.report_006ac0a0 = trace_stream_report_006ac0a0;
    stream.probe_004bc540 = trace_holder_probe_004bc540;
    stream.resolve_004bc540 = trace_holder_resolve_004bc540;
  }
  ~PortScope() { property_runtime().ports = saved; }
  PortScope(const PortScope&) = delete;
  PortScope& operator=(const PortScope&) = delete;
};

void reset_all() {
  reset_property();
  reset_slot();
  reset_stream();
}

OpaquePropertyRecord make_array(const std::vector<TargetWord>& data,
                                TargetWord count) {
  OpaquePropertyRecord record;
  std::memset(&record, 0, sizeof(record));
  record.slot_00 = address(data.data());
  record.slot_08 = count;
  record.flags_10 = kFlagArrayMask;
  record.kind_12 = 0u;
  return record;
}

OpaquePropertyRecord make_inline(TargetWord first, TargetWord second,
                                 TargetWord third) {
  OpaquePropertyRecord record;
  std::memset(&record, 0, sizeof(record));
  record.slot_00 = first;
  record.slot_04 = second;
  record.slot_08 = third;
  record.flags_10 = 0u;
  record.kind_12 = 0x0042u;
  return record;
}

struct PartFixture {
  OpaquePartList list;
  std::vector<OpaquePartEntry> entries;
  std::vector<TargetWord> slots;
  OpaqueVtableHolder service;

  PartFixture(std::size_t count, const std::vector<TargetWord>& keys)
      : entries(count), slots(count, 0u) {
    std::memset(&list, 0, sizeof(list));
    std::memset(&entries.front(), 0, sizeof(OpaquePartEntry) * count);
    for (std::size_t i = 0u; i < count; ++i) {
      entries[i].key_8c = keys[i];
      slots[i] = address(&entries[i]);
    }
    list.elements_first_6cc = address(slots.data());
    list.elements_last_6d0 =
        address(slots.data()) + static_cast<TargetWord>(slots.size() * 4u);
    service.table = nullptr;
  }

  TargetWord at(std::size_t index) const { return slots[index]; }
};

struct SlotFixture {
  OpaqueSlotVector vector;
  std::vector<TargetWord> storage;
  std::size_t base_index;

  explicit SlotFixture(std::size_t capacity, std::size_t lead = 2u)
      : storage(capacity + lead + 3u, 0u), base_index(lead + 1u) {
    std::memset(&vector, 0, sizeof(vector));
    storage[base_index - 1u] = 1u;
    vector.first =
        address(storage.data()) + static_cast<TargetWord>(base_index * 4u);
    vector.last = vector.first;
    vector.limit =
        vector.first + static_cast<TargetWord>(capacity * kPairStride);
    vector.arena = 0u;
  }

  void push(TargetWord first, TargetWord second) {
    store(reinterpret_cast<void*>(vector.last), first);
    store(reinterpret_cast<void*>(vector.last + sizeof(TargetWord)), second);
    vector.last += kPairStride;
  }

  std::size_t count() const {
    return static_cast<std::size_t>((vector.last - vector.first) / kPairStride);
  }

  std::size_t capacity() const {
    return static_cast<std::size_t>((vector.limit - vector.first) /
                                    kPairStride);
  }

  TargetWord slot(std::size_t index) const {
    return vector.first + static_cast<TargetWord>(index * kPairStride);
  }

  TargetWord lead_slot(std::size_t index) const {
    return vector.first - static_cast<TargetWord>((index + 1u) * kPairStride);
  }

  TargetWord word(std::size_t index, std::size_t half) const {
    return load(reinterpret_cast<const void*>(
        slot(index) + static_cast<TargetWord>(half * sizeof(TargetWord))));
  }
};

void test_assign_pair_notify_gate() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaquePropertyRecord record;
  std::memset(&record, 0, sizeof(record));
  record.flags_10 = 0x0004u;
  std::array<TargetByte, 0x10> source{};
  OpaquePropertyRecord* const returned =
      property_record_assign_pair_004279d0(&record, source.data());
  check(returned == &record, "004279d0 returns the receiver");
  check(g_property.notify_calls == 1u, "004279d0 notifies once when locked");
  check(g_property.notify_receiver == address(&record),
        "004279d0 notifies with the receiver");
  check(g_property.notify_flag == 1u, "004279d0 notifies with flag one");
  check(g_property.store_calls == 1u, "004279d0 stores once");
  check(g_property.store_kind == 0x13, "004279d0 passes type 0x13");
  check(g_property.store_field == 9u, "004279d0 passes field nine");
  check(g_property.store_source == address(source.data()),
        "004279d0 passes the source");
  check(g_property.store_size == 0x10, "004279d0 passes size 0x10");
  check(g_property.store_count == 1, "004279d0 passes count one");
  check(g_property.insert_calls == 0u,
        "004279d0 never reaches the inline insert path");
  record.flags_10 = 0x0000u;
  reset_property();
  property_record_assign_pair_004279d0(&record, source.data());
  check(g_property.notify_calls == 0u, "004279d0 skips notify when unlocked");
  check(g_property.store_calls == 1u, "004279d0 still stores when unlocked");
}

void test_assign_scalar_inline_paths() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaquePropertyRecord record;
  std::memset(&record, 0, sizeof(record));
  record.flags_10 = 0x0004u;
  const TargetFloat source = 2.5f;
  OpaquePropertyRecord* const returned =
      property_record_assign_scalar_00428060(&record, &source);
  check(returned == &record, "00428060 returns the receiver");
  check(g_property.notify_calls == 1u, "00428060 notifies once when locked");
  check(g_property.store_calls == 0u,
        "00428060 stores inline when the live bit is clear");
  check(load_float(&record.slot_00) == 2.5f,
        "00428060 copies the source float");
  check(record.kind_12 == 0x000du, "00428060 forces kind 0x0d");
  check(record.flags_10 == 0x0000u, "00428060 keeps only the live bit");
  record.flags_10 = 0x0006u;
  record.kind_12 = 0x000du;
  reset_property();
  const TargetFloat again = -0.5f;
  property_record_assign_scalar_00428060(&record, &again);
  check(g_property.store_calls == 0u,
        "00428060 stores inline when the kind already matches");
  check(load_float(&record.slot_00) == -0.5f,
        "00428060 copies the second source float");
  check(record.flags_10 == 0x0002u, "00428060 masks the flags to the live bit");
  check(record.kind_12 == 0x000du, "00428060 keeps the forced kind");
}

void test_assign_scalar_port_path() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaquePropertyRecord record;
  std::memset(&record, 0, sizeof(record));
  record.flags_10 = 0x0002u;
  record.kind_12 = 0x0007u;
  record.slot_00 = 0xdeadbeefu;
  const TargetFloat source = 1.5f;
  OpaquePropertyRecord* const returned =
      property_record_assign_scalar_00428060(&record, &source);
  check(returned == &record, "00428060 returns the receiver on the port path");
  check(g_property.notify_calls == 0u,
        "00428060 does not notify when unlocked");
  check(g_property.store_calls == 1u, "00428060 delegates a live foreign kind");
  check(g_property.store_kind == 0x0d, "00428060 passes type 0x0d");
  check(g_property.store_field == 0u, "00428060 passes field zero");
  check(g_property.store_size == 4, "00428060 passes size four");
  check(g_property.store_count == 1, "00428060 passes count one");
  check(record.slot_00 == 0xdeadbeefu, "00428060 leaves the slot untouched");
  check(record.kind_12 == 0x0007u, "00428060 leaves a foreign kind untouched");
  check(record.flags_10 == 0x0002u, "00428060 leaves the flags untouched");
}

void test_pair_vector_not_full_front() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(6u);
  fixture.push(0x11u, 0x12u);
  fixture.push(0x21u, 0x22u);
  const TargetWord value[2] = {0x31u, 0x32u};
  pair_vector_insert_004786e0(&fixture.vector, fixture.vector.first, value);
  check(fixture.count() == 3u, "004786e0 grows the count on the inline path");
  check(fixture.word(0u, 0u) == 0x31u,
        "004786e0 writes the value argument into the first slot");
  check(fixture.word(0u, 1u) == 0x32u,
        "004786e0 writes the value argument tail into the first slot");
  check(fixture.word(1u, 0u) == 0x11u, "004786e0 shifts the first head down");
  check(fixture.word(2u, 0u) == 0x21u, "004786e0 shifts the second head down");
  check(fixture.word(2u, 1u) == 0x22u,
        "004786e0 keeps the duplicated tail half");
  check(fixture.vector.first == address(fixture.storage.data()) +
                                    static_cast<TargetWord>(fixture.base_index *
                                                            sizeof(TargetWord)),
        "004786e0 keeps the buffer on the inline path");
  check(g_slot.allocate_calls == 0u,
        "004786e0 does not allocate when not full");
  check(g_slot.release_calls == 0u, "004786e0 does not release when not full");
}

void test_pair_vector_insert_before() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(6u);
  fixture.push(0xa0u, 0xa1u);
  fixture.push(0xb0u, 0xb1u);
  fixture.push(0xc0u, 0xc1u);
  const TargetWord value[2] = {0xd0u, 0xd1u};
  pair_vector_insert_004786e0(&fixture.vector, fixture.slot(1u), value);
  check(fixture.count() == 4u, "004786e0 grows the slot count by one");
  check(fixture.word(0u, 0u) == 0xa0u, "004786e0 keeps the leading slot");
  check(fixture.word(1u, 0u) == 0xd0u,
        "004786e0 writes the value argument into the middle slot");
  check(fixture.word(1u, 1u) == 0xd1u,
        "004786e0 writes the value argument tail into the middle slot");
  check(fixture.word(2u, 0u) == 0xb0u, "004786e0 shifts the successor in");
  check(fixture.word(3u, 0u) == 0xc0u, "004786e0 shifts the last element");
  check(fixture.word(3u, 1u) == 0xc1u, "004786e0 shifts the last tail");
}

void test_pair_vector_aliasing_source() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(6u);
  fixture.push(0xa0u, 0xa1u);
  fixture.push(0xb0u, 0xb1u);
  const TargetWord* const inside = reinterpret_cast<const TargetWord*>(
      static_cast<std::uintptr_t>(fixture.slot(1u)));
  pair_vector_insert_004786e0(&fixture.vector, fixture.slot(0u), inside);
  check(fixture.count() == 3u,
        "004786e0 keeps the count for an aliasing insert");
  check(fixture.word(0u, 0u) == 0xb0u,
        "004786e0 reads an in range value argument one slot further on");
  check(fixture.word(0u, 1u) == 0xb1u,
        "004786e0 reads an in range value argument tail one slot further on");
  check(fixture.word(1u, 0u) == 0xa0u, "004786e0 shifts the aliased head up");
  check(fixture.word(2u, 0u) == 0xb0u,
        "004786e0 keeps the scratch copy of the aliased slot");
}

void test_pair_vector_not_full_middle() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(6u);
  fixture.push(0x01u, 0x02u);
  fixture.push(0x11u, 0x12u);
  fixture.push(0x21u, 0x22u);
  const TargetWord value[2] = {0xf0u, 0xf1u};
  pair_vector_insert_004786e0(&fixture.vector, fixture.slot(1u), value);
  check(fixture.count() == 4u, "004786e0 grows on a middle insert");
  check(fixture.word(0u, 0u) == 0x01u, "004786e0 keeps the leading slot");
  check(fixture.word(1u, 0u) == 0xf0u,
        "004786e0 writes the value argument into the middle slot");
  check(fixture.word(2u, 0u) == 0x11u,
        "004786e0 shifts the successor into place");
  check(fixture.word(3u, 0u) == 0x21u, "004786e0 shifts the trailing element");
  check(g_slot.allocate_calls == 0u, "004786e0 stays on the inline path");
}

void test_pair_vector_position_below_first() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(6u);
  fixture.push(0x11u, 0x12u);
  fixture.push(0x13u, 0x14u);
  const TargetWord below = fixture.lead_slot(0u);
  store(reinterpret_cast<void*>(below), 0x99u);
  store(reinterpret_cast<void*>(below + 4u), 0x98u);
  const TargetWord value[2] = {0xabu, 0xacu};
  pair_vector_insert_004786e0(&fixture.vector, below, value);
  check(fixture.count() == 3u, "004786e0 grows for a position below the first");
  check(load(reinterpret_cast<const void*>(below)) == 0xabu,
        "004786e0 still writes the value argument at a below range position");
  check(load(reinterpret_cast<const void*>(below + 4u)) == 0xacu,
        "004786e0 still writes the value argument tail below the first");
  check(fixture.word(0u, 0u) == 0x99u,
        "004786e0 shifts the scratch word into the first slot");
  check(fixture.word(1u, 0u) == 0x11u, "004786e0 shifts the first slot up");
  check(fixture.word(2u, 0u) == 0x13u, "004786e0 shifts the second slot up");
}

void test_pair_vector_growth() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(2u);
  fixture.push(0x10u, 0x11u);
  fixture.push(0x20u, 0x21u);
  const TargetWord position = fixture.vector.last;
  const TargetWord value[2] = {0x30u, 0x31u};
  pair_vector_insert_004786e0(&fixture.vector, position, value);
  check(g_slot.allocate_calls == 1u, "004786e0 allocates once when full");
  check(g_slot.allocate_arena == address(&fixture.vector.arena),
        "004786e0 passes the arena address");
  check(g_slot.allocate_size == 4u * kPairStride,
        "004786e0 doubles the slot capacity");
  check(g_slot.allocate_align == kPairStride,
        "004786e0 requests eight byte slot");
  check(g_slot.allocate_fill == 0u, "004786e0 requests an unfilled block");
  check(g_slot.release_calls == 1u, "004786e0 releases the old buffer once");
  check(g_slot.release_order.size() == 1u, "004786e0 releases exactly once");
  check(fixture.count() == 3u, "004786e0 appends across the growth path");
  check(fixture.capacity() == 4u, "004786e0 installs the doubled limit");
  check(fixture.word(0u, 0u) == 0x10u, "004786e0 growth keeps the head");
  check(fixture.word(1u, 0u) == 0x20u, "004786e0 growth keeps the second");
  check(fixture.word(2u, 0u) == 0x30u, "004786e0 growth writes the new slot");
  check(fixture.word(2u, 1u) == 0x31u, "004786e0 growth writes the new tail");
  check(g_slot.owned.size() == 1u, "004786e0 keeps one owned block");
  check(fixture.vector.first == address(g_slot.owned.front()),
        "004786e0 installs the fresh buffer");
}

void test_pair_vector_growth_from_empty() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(0u);
  const TargetWord value[2] = {0x77u, 0x78u};
  pair_vector_insert_004786e0(&fixture.vector, fixture.vector.last, value);
  check(g_slot.allocate_calls == 1u, "004786e0 allocates for an empty vector");
  check(g_slot.allocate_size == kPairStride,
        "004786e0 empty growth requests one slot");
  check(fixture.count() == 1u, "004786e0 empty growth stores one slot");
  check(fixture.capacity() == 1u,
        "004786e0 empty growth sets a one slot limit");
  check(fixture.word(0u, 0u) == 0x77u, "004786e0 empty growth writes the head");
}

void test_pair_vector_growth_middle() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  SlotFixture fixture(2u);
  fixture.push(0x01u, 0x02u);
  fixture.push(0x03u, 0x04u);
  const TargetWord value[2] = {0x09u, 0x0au};
  pair_vector_insert_004786e0(&fixture.vector, fixture.slot(1u), value);
  check(g_slot.allocate_calls == 1u, "004786e0 grows on a middle insert");
  check(fixture.count() == 3u, "004786e0 middle growth adds one slot");
  check(fixture.word(0u, 0u) == 0x01u, "004786e0 middle growth keeps the head");
  check(fixture.word(1u, 0u) == 0x09u,
        "004786e0 middle growth writes the slot");
  check(fixture.word(2u, 0u) == 0x03u,
        "004786e0 middle growth shifts the tail");
  check(fixture.word(2u, 1u) == 0x04u,
        "004786e0 middle growth shifts the tail pair");
  check(fixture.word(3u, 0u) == 0u,
        "004786e0 middle growth leaves no extra slot");
}

void test_pair_vector_construct() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaquePairVector vector;
  std::memset(&vector, 0, sizeof(vector));
  vector.first = 0xdeadbeefu;
  vector.last = 0xcafebabeu;
  vector.limit = 0x12345678u;
  vector.arena = 0x9abcdef0u;
  std::array<TargetWord, 2> source{0x11110000u, 0x22220000u};
  OpaquePairVector* const returned =
      pair_vector_construct_004b62a0(&vector, source.data());
  check(returned == &vector, "004b62a0 returns the receiver");
  const TargetWord inline_base = address(vector.payload_18.data());
  check(vector.first == inline_base, "004b62a0 installs the inline base");
  check(vector.last == inline_base, "004b62a0 sets last to the inline base");
  check(vector.limit == inline_base + 0x100u,
        "004b62a0 sets a 0x100 byte inline limit");
  check(vector.arena == inline_base, "004b62a0 points the arena at the buffer");
  check(vector.inline_sentinel == 0u,
        "004b62a0 leaves the inline sentinel word clear");
  check(g_slot.push_calls == 1u, "004b62a0 pushes exactly once");
  check(g_slot.push_receiver == address(&vector),
        "004b62a0 pushes with the receiver");
  check(g_slot.push_begin == source[0], "004b62a0 forwards the source head");
  check(g_slot.push_end == source[1], "004b62a0 forwards the source tail");
  check(g_slot.push_tag == 0u, "004b62a0 forwards the stale stack tag");
}

void test_model_find_indices() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u, 0x30u};
  PartFixture fixture(3u, keys);
  g_property.find_root = 2u;
  g_property.find_key[0] = 0;
  g_property.find_key[1] = 2;
  g_property.find_key[2] = -1;
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.list.find_root_1b0 == 2u,
        "00447150 stores the found root index");
  check(fixture.list.find_key_a_1b4 == 0u,
        "00447150 stores the first key index");
  check(fixture.list.find_key_b_1b8 == 2u,
        "00447150 stores the second key index");
  check(fixture.list.find_key_c_1bc == 0xffffffffu,
        "00447150 stores the sentinel for a missing key");
  check(fixture.entries[0].flag_1d5 == 1u, "00447150 marks the first match");
  check(fixture.entries[2].flag_1d5 == 1u, "00447150 marks the second match");
  check(g_property.get_calls == 0u,
        "00447150 reads no property when none is published");
  check(g_property.reserve_calls == 0u,
        "00447150 reserves nothing without the resolve property");
  check(g_property.release_calls == 1u, "00447150 releases the resolved array");
}

void test_model_resolve_block() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u, 0x30u, 0x10u};
  PartFixture fixture(4u, keys);
  const std::vector<TargetWord> data{0x20u, 0u, 0u, 0x10u, 0u, 0u,
                                     0x99u, 0u, 0u, 0x30u, 0u, 0u};
  const OpaquePropertyRecord record = make_array(data, 4u);
  publish(0x8ecb344au, &record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.has_first_code == 0x8ecb344au,
        "00447150 opens with the resolve property");
  check(g_property.reserve_calls == 1u, "00447150 reserves the resolved array");
  check(g_property.reserve_count == 4u, "00447150 reserves the property count");
  check(g_property.pair_insert_calls == 0u,
        "00447150 skips block B for an absent property");
  check(g_property.release_calls == 1u, "00447150 releases exactly once");
}

void test_model_range_block() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u, 0x30u};
  PartFixture fixture(3u, keys);
  const std::vector<TargetWord> resolve{0x20u, 0u, 0u};
  const OpaquePropertyRecord resolve_record = make_array(resolve, 1u);
  std::vector<TargetWord> ranges(4u, 0u);
  ranges[0] = 0x90000001u;
  ranges[1] = 0x90000009u;
  OpaquePropertyRecord plain_record = make_array(ranges, 1u);
  plain_record.kind_12 = kKindPairArray;
  OpaquePropertyRecord aligned_record = make_array(ranges, 1u);
  aligned_record.kind_12 = kKindPairArray;
  aligned_record.slot_00 = fixture.at(1u) + 0x11cu;
  publish(0x8ecb344au, &resolve_record);
  publish(0x3644a2c5u, &plain_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.reserve_count == 1u, "00447150 resolves one element");
  check(g_property.pair_insert_calls == 1u, "00447150 inserts one byte range");
  check(g_property.pair_insert_slot == fixture.at(1u) + 0x11cu,
        "00447150 inserts at the entry offset 0x11c");
  check(g_property.pair_insert_begin == ranges[0],
        "00447150 forwards the range head");
  check(g_property.pair_insert_end == ranges[1],
        "00447150 forwards the range tail");
  reset_property();
  publish(0x8ecb344au, &resolve_record);
  publish(0x3644a2c5u, &aligned_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.pair_insert_calls == 0u,
        "00447150 skips a range aliased with the destination slot");
  reset_property();
  plain_record.kind_12 = 0x0099u;
  publish(0x8ecb344au, &resolve_record);
  publish(0x3644a2c5u, &plain_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.pair_insert_calls == 0u,
        "00447150 skips the range block for a mismatched kind");
  reset_property();
  plain_record.kind_12 = kKindPairArray;
  plain_record.flags_10 = 0u;
  plain_record.slot_08 = 0u;
  plain_record.slot_00 = 0u;
  publish(0x3644a2c5u, &plain_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.pair_insert_calls == 0u,
        "00447150 skips a range payload with no count");
}

void test_model_bool_block() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u};
  PartFixture fixture(2u, keys);
  const std::vector<TargetWord> resolve{0x10u, 0u, 0u, 0x20u, 0u, 0u};
  const OpaquePropertyRecord resolve_record = make_array(resolve, 2u);
  const OpaquePropertyRecord bool_record =
      make_array(std::vector<TargetWord>(), 0u);
  publish(0x8ecb344au, &resolve_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[0].flag_1d4 == 0u,
        "00447150 leaves the bool flag clear when the array is empty");
  static const std::array<TargetByte, 2> values{0xa5u, 0x5au};
  publish(0x04604b04u, &bool_record);
  g_property.array_bool_span = 2u;
  g_property.array_bool_values = values.data();
  fixture.list.property_list = reinterpret_cast<void*>(0x00c0ffeeu);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.array_bool_calls == 1u,
        "00447150 queries the bool array once");
  check(g_property.array_bool_list == fixture.list.property_list,
        "00447150 forwards the receiver property list");
  check(g_property.array_bool_code == 0x04604b04u,
        "00447150 forwards the bool property code");
  check(fixture.entries[0].flag_1d4 == 0xa5u,
        "00447150 writes the first bool flag");
  check(fixture.entries[1].flag_1d4 == 0x5au,
        "00447150 writes the second bool flag");
  g_property.array_bool_span = 4u;
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[0].flag_1d4 == 0xa5u,
        "00447150 keeps the first flag for an over long array");
}

void test_model_link_blocks() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u, 0x30u};
  PartFixture fixture(3u, keys);
  const std::vector<TargetWord> pairs{0x10u, 0u, 0x20u, 0x30u, 0u, 0x20u};
  const OpaquePropertyRecord link_record = make_array(pairs, 2u);
  publish(0x87fe8a14u, &link_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[0].link_b4 == fixture.at(1u),
        "00447150 links the first pair head to tail");
  check(fixture.entries[2].link_b4 == fixture.at(1u),
        "00447150 links the second pair head to tail");
  check(fixture.entries[1].link_b4 == fixture.at(2u),
        "00447150 overwrites a shared link with the later pair");
  check(fixture.entries[0].link_b4 == fixture.at(1u),
        "00447150 leaves the unshared link from the first pair");
  const std::vector<TargetWord> detach{0x2ca33bdbu, 0u, 0x20u,
                                       0x99u,       0u, 0x20u};
  const OpaquePropertyRecord detach_record = make_array(detach, 2u);
  publish(0x45101f3eu, &detach_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[1].link_b4 == 0u, "00447150 detaches the flagged pair");
  const std::vector<TargetWord> present{0x10u, 0u, 0x20u, 0x20u, 0u, 0x99u};
  const OpaquePropertyRecord present_record = make_array(present, 2u);
  publish(0x45101f3eu, &present_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[0].link_b4 == fixture.at(1u),
        "00447150 links when both keys resolve");
  const std::vector<TargetWord> missing{0x77u, 0u, 0x20u, 0x88u, 0u, 0x99u};
  const OpaquePropertyRecord missing_record = make_array(missing, 2u);
  publish(0x45101f3eu, &missing_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[1].link_b4 == 0u,
        "00447150 leaves the link clear when the head is missing");
}

void test_model_link_value_blocks() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u};
  PartFixture fixture(2u, keys);
  const std::vector<TargetWord> values{0xaaaaaaaau,        0xbbbbbbbbu, 0x20u,
                                       kLinkValueSentinel, 0xccccccccu, 0x10u};
  const OpaquePropertyRecord value_record = make_array(values, 2u);
  publish(0x3b58c554u, &value_record);
  publish(0x23fc767eu, &value_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[1].link_value_ac == 0xaaaaaaaau,
        "00447150 writes the link value from the first triple");
  check(fixture.entries[1].link_value_b0 == 0u,
        "00447150 leaves the sentinel word clear for a plain value");
  check(fixture.entries[0].link_value_ac == kLinkValueSentinel,
        "00447150 writes the link value from the second triple");
  check(fixture.entries[0].link_value_b0 == 0xccccccccu,
        "00447150 writes the sentinel word for the sentinel value");
  reset_property();
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(fixture.entries[0].link_value_ac == kLinkValueSentinel,
        "00447150 keeps the link value when the property is absent");
  PartFixture plain(2u, keys);
  const OpaquePropertyRecord inline_record =
      make_inline(0x77777777u, 0x9e6e561cu, 0x10u);
  publish(0x3b58c554u, &inline_record);
  model_parts_apply_properties_00447150(&plain.list, &plain.service);
  check(plain.entries[0].link_value_ac == 0x77777777u,
        "00447150 reads an inline link value from the record head");
  check(plain.entries[0].link_value_b0 == 0u,
        "00447150 skips the inline middle word for a plain value");
  PartFixture sentinel(2u, keys);
  const OpaquePropertyRecord inline_sentinel =
      make_inline(kLinkValueSentinel, 0x0badf00du, 0x10u);
  reset_property();
  publish(0x3b58c554u, &inline_sentinel);
  model_parts_apply_properties_00447150(&sentinel.list, &sentinel.service);
  check(sentinel.entries[0].link_value_ac == kLinkValueSentinel,
        "00447150 accepts an inline sentinel head");
  check(sentinel.entries[0].link_value_b0 == 0x0badf00du,
        "00447150 reads an inline sentinel from the record middle");
  const OpaquePropertyRecord empty_record = make_inline(0u, 0u, 0u);
  reset_property();
  publish(0x3b58c554u, &empty_record);
  model_parts_apply_properties_00447150(&plain.list, &plain.service);
  check(plain.entries[0].link_value_ac == 0x77777777u,
        "00447150 keeps the link value for a zero kind record");
}

void test_model_assoc_and_tree_blocks() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  const std::vector<TargetWord> keys{0x10u, 0x20u};
  PartFixture fixture(2u, keys);
  const std::vector<TargetWord> assoc{0x1111u, 0u, 2u, 0x2222u, 0u, 3u};
  const OpaquePropertyRecord assoc_record = make_array(assoc, 2u);
  publish(0xb75fd502u, &assoc_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.assoc_reserve_calls == 1u,
        "00447150 reserves the assoc blob");
  check(g_property.assoc_reserve_count == 2u,
        "00447150 reserves the assoc property count");
  check(g_property.slot_calls == 2u, "00447150 writes two assoc slots");
  check(g_property.slot_key == 3u, "00447150 forwards the last assoc key");
  TargetWord* const slots =
      reinterpret_cast<TargetWord*>(fixture.list.assoc_630.opaque_00_9b.data());
  check(slots[2] == 0x1111u, "00447150 stores the first assoc value");
  check(slots[3] == 0x2222u, "00447150 stores the second assoc value");
  const std::vector<TargetWord> tree{0xdeadu, 0x20u, 0x10u,
                                     0xfeedu, 0x77u, 0x99u};
  const OpaquePropertyRecord tree_record = make_array(tree, 2u);
  publish(0x41f72519u, &tree_record);
  model_parts_apply_properties_00447150(&fixture.list, &fixture.service);
  check(g_property.tree_calls == 2u, "00447150 inserts two tree pairs");
  check(g_property.tree_receiver == address(&fixture.list.tree_614),
        "00447150 inserts into the receiver tree blob");
  check(g_property.tree_first_key == 0x10u,
        "00447150 forwards the first tree key");
  check(g_property.tree_first_pair.first == 0xdeadu,
        "00447150 forwards the first tree head");
  check(g_property.tree_first_pair.second == fixture.at(1u),
        "00447150 forwards the resolved tree tail");
  check(g_property.append_calls == 2u, "00447150 appends two tree nodes");
  check(g_property.append_receiver == address(&fixture.list.tree_614),
        "00447150 appends into the inserted node");
  check(g_property.append_calls == 2u,
        "00447150 reaches the argumentless append port exactly twice");
}

void test_stream_primary_branch() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaqueVtableHolder holder_08;
  OpaqueVtableHolder holder_0c;
  holder_08.table = reinterpret_cast<TargetWord*>(0x0000a001u);
  holder_0c.table = reinterpret_cast<TargetWord*>(0x0000b002u);
  g_stream.lookup_result = 0x00500000u;
  g_stream.resolve_result = 0x00600000u;
  g_stream.read_result = 0u;
  const TargetByte denied = stream_probe_dispatch_004bc540(
      &holder_08, &holder_08, &holder_0c, 0u, kProbePrimary);
  check(denied == 0u, "004bc540 denies when the probe reports zero");
  check(g_stream.lookup_calls == 1u, "004bc540 performs one lookup");
  check(g_stream.lookup_input == address(&holder_0c),
        "004bc540 looks up with the second holder");
  check(g_stream.resolve_input == 0x00500000u,
        "004bc540 resolves with the lookup result");
  check(g_stream.resolve_receiver == address(&holder_08),
        "004bc540 resolves on the first holder");
  check(g_stream.read_first == 0x00600000u,
        "004bc540 reads the resolved object");
  check(g_stream.read_second == 0x00500000u,
        "004bc540 reads the lookup result");
  check(g_stream.report_calls == 1u, "004bc540 reports exactly once");
  check(g_stream.report_first == kProbeReport, "004bc540 reports code 0x0b");
  check(g_stream.report_second == address(&holder_0c),
        "004bc540 reports the second holder");
  g_stream.read_result = 0x00000101u;
  const TargetByte set_low = stream_probe_dispatch_004bc540(
      &holder_08, &holder_08, &holder_0c, 0u, kProbePrimary);
  check(set_low == 1u, "004bc540 accepts a set low byte");
  g_stream.read_result = 0x00000100u;
  const TargetByte high = stream_probe_dispatch_004bc540(
      &holder_08, &holder_08, &holder_0c, 0u, kProbePrimary);
  check(high == 0u, "004bc540 tests only the low byte");
  g_stream.lookup_result = 0u;
  reset_stream();
  const TargetByte absent = stream_probe_dispatch_004bc540(
      &holder_08, &holder_08, &holder_0c, 0u, kProbePrimary);
  check(absent == 0u, "004bc540 denies for a missing lookup");
  check(g_stream.resolve_calls == 0u, "004bc540 skips the resolve when absent");
  check(g_stream.report_calls == 1u, "004bc540 still reports when absent");
}

void test_stream_class_branches() {
  PortScope<OpaquePropertyPorts> scope;
  reset_all();
  OpaqueVtableHolder holder_08;
  OpaqueVtableHolder holder_0c;
  holder_08.table = reinterpret_cast<TargetWord*>(0x0000a001u);
  holder_0c.table = reinterpret_cast<TargetWord*>(0x0000b002u);
  std::array<TargetWord, 2> tag_storage{0x11111111u, 0x22222222u};
  g_stream.probe_result = address(tag_storage.data());
  g_stream.resolve_result = 0x00700000u;
  g_stream.apply_result = 0x5au;
  const TargetWord codes[6] = {kProbeClassA, kProbeClassB, kProbeClassC,
                               kProbeClassD, kProbeClassE, kProbeClassF};
  for (std::size_t i = 0u; i < 6u; ++i) {
    reset_stream();
    g_stream.probe_result = address(tag_storage.data());
    g_stream.resolve_result = 0x00700000u;
    g_stream.apply_result = 0x5au;
    const TargetByte verdict = stream_probe_dispatch_004bc540(
        &holder_08, &holder_08, &holder_0c, 0u, codes[i]);
    check(verdict == 0x5au,
          "004bc540 returns the apply result for a class code");
    check(g_stream.probe_calls == 1u, "004bc540 probes the first holder once");
    check(g_stream.probe_receiver == address(&holder_08),
          "004bc540 probes the first holder");
    check(g_stream.apply_first == 0x00700000u,
          "004bc540 applies with the resolved object");
    check(g_stream.apply_second == address(&holder_0c),
          "004bc540 applies with the second holder");
    check(g_stream.apply_third == 0x22222222u,
          "004bc540 applies with the second word of the probe result");
    check(g_stream.resolve_input == address(&holder_0c),
          "004bc540 resolves with the second holder address");
  }
  reset_stream();
  const TargetByte unknown = stream_probe_dispatch_004bc540(
      &holder_08, &holder_08, &holder_0c, 0u, 0x12345678u);
  check(unknown == 0u, "004bc540 denies an unlisted code");
  check(g_stream.probe_calls == 0u,
        "004bc540 skips the probe for an unlisted code");
  check(g_stream.apply_calls == 0u,
        "004bc540 skips the apply for an unlisted code");
  check(g_stream.report_calls == 0u,
        "004bc540 skips the report for an unlisted code");
}

}  // namespace

}  // namespace openspore::reconstruction::pkg_app_safe_wave11

int main() {
  using namespace openspore::reconstruction::pkg_app_safe_wave11;
  test_assign_pair_notify_gate();
  test_assign_scalar_inline_paths();
  test_assign_scalar_port_path();
  test_pair_vector_not_full_front();
  test_pair_vector_insert_before();
  test_pair_vector_aliasing_source();
  test_pair_vector_not_full_middle();
  test_pair_vector_position_below_first();
  test_pair_vector_growth();
  test_pair_vector_growth_from_empty();
  test_pair_vector_growth_middle();
  test_pair_vector_construct();
  test_model_find_indices();
  test_model_resolve_block();
  test_model_range_block();
  test_model_bool_block();
  test_model_link_blocks();
  test_model_link_value_blocks();
  test_model_assoc_and_tree_blocks();
  test_stream_primary_branch();
  test_stream_class_branches();
  if (g_failures != 0) {
    std::printf("pkg-app-safe-wave11: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("pkg-app-safe-wave11: all checks passed\n");
  return 0;
}
