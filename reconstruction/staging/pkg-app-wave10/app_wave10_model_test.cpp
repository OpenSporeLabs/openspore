#include <cstdlib>
#include <cstring>
#include <iterator>

#include "app_wave10.hpp"

namespace openspore::reconstruction::pkg_app_wave10 {
namespace {

#if defined(_MSC_VER)
#define PKG_APP_WAVE10_TEST_THISCALL __thiscall
#else
#define PKG_APP_WAVE10_TEST_THISCALL __attribute__((thiscall))
#endif

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

struct Event {
  TargetWord kind;
  TargetWord first;
  TargetWord second;
  TargetWord third;
};

std::array<Event, 128> events{};
std::size_t event_count = 0;

TargetWord record(TargetWord kind, TargetWord first = 0, TargetWord second = 0,
                  TargetWord third = 0) {
  if (event_count < events.size()) {
    events[event_count] = Event{kind, first, second, third};
  }
  ++event_count;
  return 0;
}

void reset_events() {
  event_count = 0;
  std::memset(events.data(), 0, sizeof(events));
}

void test_vector3_add() {
  OpaqueVector3 left{1.0f, 2.0f, 3.0f};
  OpaqueVector3 right{0.5f, -1.0f, 4.0f};
  OpaqueVector3 out{};

  check(vector3_add(&out, &left, &right) == &out);
  check(out.x == 1.5f);
  check(out.y == 1.0f);
  check(out.z == 7.0f);

  OpaqueVector3 accumulate = right;
  check(vector3_add(&accumulate, &left, &accumulate) == &accumulate);
  check(accumulate.x == 1.5f);
  check(accumulate.y == 1.0f);
  check(accumulate.z == 7.0f);

  OpaqueVector3 target = left;
  check(vector3_add(&target, &target, &right) == &target);
  check(target.x == 1.5f);
  check(target.y == 1.0f);
  check(target.z == 7.0f);

  OpaqueVector3 zero{0.0f, 0.0f, 0.0f};
  OpaqueVector3 negated{-1.0f, -2.0f, -3.0f};
  check(vector3_add(&out, &zero, &negated) == &out);
  check(out.x == -1.0f);
  check(out.y == -2.0f);
  check(out.z == -3.0f);
}

TargetByte stored_marker = 0x5au;

void test_property_value_resolve() {
  check(reinterpret_cast<std::uintptr_t>(property_value_sentinel()) ==
        0x015d115du);

  OpaquePropertyValueSlot slot{};
  const auto* const self = reinterpret_cast<const TargetByte*>(&slot);

  slot.kind = 0x0031u;
  check(property_value_resolve(&slot) == property_value_sentinel());

  slot.kind = 0x0000u;
  check(property_value_resolve(&slot) == property_value_sentinel());

  slot.kind = 0x0001u;
  check(property_value_resolve(&slot) == self);

  slot.kind = 0x0010u;
  check(property_value_resolve(&slot) == self);

  slot.kind = 0x0002u;
  check(property_value_resolve(&slot) == property_value_sentinel());

  slot.kind = 0x0001u;
  slot.flags = 0x0004u;
  check(property_value_resolve(&slot) == self);
  slot.flags = 0x0002u;
  check(property_value_resolve(&slot) == self);
  slot.flags = 0x0100u;
  check(property_value_resolve(&slot) == self);
  slot.flags = 0x0000u;
  check(property_value_resolve(&slot) == self);

  const TargetWord stored =
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(&stored_marker));
  std::memcpy(slot.data.data(), &stored, sizeof(stored));
  const auto* const expected =
      reinterpret_cast<const TargetByte*>(&stored_marker);

  slot.flags = 0x0010u;
  check(property_value_resolve(&slot) == expected);
  slot.flags = 0x0020u;
  check(property_value_resolve(&slot) == expected);
  slot.flags = 0x0030u;
  check(property_value_resolve(&slot) == expected);

  slot.kind = 0x0010u;
  slot.flags = 0x0030u;
  check(property_value_resolve(&slot) == expected);

  std::memset(slot.data.data(), 0, slot.data.size());
  slot.kind = 0x0001u;
  slot.flags = 0x0011u;
  check(property_value_resolve(&slot) ==
        reinterpret_cast<const TargetByte*>(std::uintptr_t{0}));
  slot.flags = 0x0021u;
  check(property_value_resolve(&slot) ==
        reinterpret_cast<const TargetByte*>(std::uintptr_t{0}));
}

TargetWord emitted_elements[8];
TargetWord emitted_arguments[8];
std::size_t emitted_count = 0;
TargetWord emit_result = 0x99u;

TargetWord PKG_APP_WAVE10_TEST_THISCALL capture_emit(void* element,
                                                     TargetWord argument) {
  if (emitted_count < 8) {
    emitted_elements[emitted_count] =
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(element));
    emitted_arguments[emitted_count] = argument;
  }
  ++emitted_count;
  return emit_result;
}

OpaqueCursorBuffer* grown_buffer = nullptr;
TargetWord grown_cursor = 0;
TargetWord grown_argument = 0;
std::size_t grown_count = 0;

void PKG_APP_WAVE10_TEST_THISCALL capture_grow(OpaqueCursorBuffer* buffer,
                                               TargetWord cursor,
                                               TargetWord argument) {
  grown_buffer = buffer;
  grown_cursor = cursor;
  grown_argument = argument;
  ++grown_count;
}

void test_cursor_buffer_emit() {
  CursorRuntime initial = cursor_runtime();
  cursor_runtime().emit_element = capture_emit;
  cursor_runtime().grow_and_emit = capture_grow;

  OpaqueCursorBuffer buffer{};

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0x1000u;
  buffer.limit = 0x2000u;
  cursor_buffer_emit(&buffer, 0x5au);
  check(emitted_count == 1);
  check(emitted_elements[0] == 0x1000u);
  check(emitted_arguments[0] == 0x5au);
  check(buffer.cursor == 0x1018u);
  check(grown_count == 0);

  cursor_buffer_emit(&buffer, 0x5bu);
  check(emitted_count == 2);
  check(emitted_elements[1] == 0x1018u);
  check(emitted_arguments[1] == 0x5bu);
  check(buffer.cursor == 0x1030u);

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0x1ff8u;
  buffer.limit = 0x2000u;
  cursor_buffer_emit(&buffer, 0x11u);
  check(emitted_count == 1);
  check(emitted_elements[0] == 0x1ff8u);
  check(buffer.cursor == 0x2010u);
  check(grown_count == 0);

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0x2000u;
  buffer.limit = 0x2000u;
  cursor_buffer_emit(&buffer, 0x22u);
  check(emitted_count == 0);
  check(grown_count == 1);
  check(grown_buffer == &buffer);
  check(grown_cursor == 0x2000u);
  check(grown_argument == 0x22u);
  check(buffer.cursor == 0x2000u);

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0u;
  buffer.limit = 8u;
  cursor_buffer_emit(&buffer, 0x33u);
  check(emitted_count == 0);
  check(grown_count == 0);
  check(buffer.cursor == 0x18u);

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0xffffffffu;
  buffer.limit = 0u;
  cursor_buffer_emit(&buffer, 0x44u);
  check(emitted_count == 0);
  check(grown_count == 1);
  check(grown_cursor == 0xffffffffu);

  emitted_count = 0;
  grown_count = 0;
  buffer.cursor = 0x8u;
  buffer.limit = 0x8u;
  cursor_buffer_emit(&buffer, 0x55u);
  check(grown_count == 1);

  cursor_runtime() = initial;
}

OpaqueFieldRun field_run{};
OpaqueModelQuery pair_storage[4];
OpaquePairTable pair_table{};

TargetWord count_injection = 0;
TargetWord read_field_slot[32];
std::size_t read_field_calls = 0;
TargetWord read_flag_slot[8];
std::size_t read_flag_calls = 0;
void* prepared_handle = nullptr;
std::size_t prepared_calls = 0;
OpaquePairTable* bound_table = nullptr;
OpaqueModelQuery* bound_first = nullptr;
TargetWord bound_extra = 0;
std::size_t bound_calls = 0;
OpaquePairTable* reserved_table = nullptr;
TargetWord reserved_count = 0;
std::size_t reserved_calls = 0;
void* reserved_source = nullptr;
void* reserved_block = nullptr;
TargetWord reserved_size = 0;
std::size_t reserve_slot_calls = 0;

void capture_read_field(void* source, TargetWord* field, TargetWord second,
                        TargetWord third) {
  if (read_field_calls < 32) {
    read_field_slot[read_field_calls] =
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(field));
  }
  if (read_field_calls == 6u) {
    *field = count_injection;
  }
  ++read_field_calls;
  record(1, second, third,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(source)));
}

void capture_read_flag(void* source, TargetByte* field) {
  if (read_flag_calls < 8) {
    read_flag_slot[read_flag_calls] =
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(field));
  }
  ++read_flag_calls;
  record(2, static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(source)),
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(field)));
}

void capture_prepare_source(void*, void* handle) {
  prepared_handle = handle;
  ++prepared_calls;
  record(3, static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(handle)));
}

void PKG_APP_WAVE10_TEST_THISCALL capture_bind(OpaquePairTable* table,
                                               OpaqueModelQuery* first,
                                               TargetWord extra) {
  bound_table = table;
  bound_first = first;
  bound_extra = extra;
  ++bound_calls;
  record(4, extra,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(first)));
}

void PKG_APP_WAVE10_TEST_THISCALL capture_reserve(OpaquePairTable* table,
                                                  TargetWord count) {
  reserved_table = table;
  reserved_count = count;
  ++reserved_calls;
  record(5, count);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_reserve_slot(void* source,
                                                       void* block,
                                                       TargetWord size) {
  reserved_source = source;
  reserved_block = block;
  reserved_size = size;
  ++reserve_slot_calls;
  record(6, size,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(block)));
}

OpaqueSourceServiceVtable source_vtable{};
OpaqueSourceService source_service{&source_vtable};

void reset_record_counters() {
  read_field_calls = 0;
  read_flag_calls = 0;
  prepared_calls = 0;
  bound_calls = 0;
  reserved_calls = 0;
  reserve_slot_calls = 0;
  prepared_handle = nullptr;
  bound_table = nullptr;
  bound_first = nullptr;
  bound_extra = 0;
  reserved_table = nullptr;
  reserved_count = 0;
  reserved_source = nullptr;
  reserved_block = nullptr;
  reserved_size = 0;
}

void test_record_field_run_load() {
  RecordRuntime initial = record_runtime();
  record_runtime().read_field = capture_read_field;
  record_runtime().read_flag = capture_read_flag;
  record_runtime().prepare_source = capture_prepare_source;
  record_runtime().bind_pair_table = capture_bind;
  record_runtime().reserve_pair_slots = capture_reserve;
  source_vtable.reserve_30 = capture_reserve_slot;

  std::memset(&field_run, 0, sizeof(field_run));
  pair_table.begin = pair_storage;
  pair_table.extra = 0x777u;
  field_run.table = &pair_table;
  field_run.opaque_40_4f[0] = 0x44u;
  field_run.opaque_40_4f[1] = 0x55u;
  field_run.opaque_40_4f[2] = 0x66u;
  field_run.opaque_40_4f[3] = 0x77u;
  field_run.tail = 0x7fu;

  read_field_calls = 0;
  read_flag_calls = 0;
  bound_calls = 0;
  reserved_calls = 0;
  prepared_calls = 0;
  reserve_slot_calls = 0;
  reset_events();

  record_field_run_load(&source_service, &field_run, 1);

  check(prepared_calls == 1);
  check(prepared_handle == &field_run.head);
  check(reserve_slot_calls == 1);
  check(reserved_source == &source_service);
  check(reserved_block == field_run.opaque_30_37.data());
  check(reserved_size == 8u);
  check(read_field_calls == 6);
  for (std::size_t index = 0; index < 6; ++index) {
    check(read_field_slot[index] ==
          static_cast<TargetWord>(
              reinterpret_cast<std::uintptr_t>(&field_run.cells[index])));
  }
  check(read_flag_calls == 4);
  for (std::size_t index = 0; index < 4; ++index) {
    check(read_flag_slot[index] ==
          static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(
              &field_run.opaque_38_3b[index])));
  }
  check(bound_calls == 1);
  check(bound_table == &pair_table);
  check(bound_first == pair_storage);
  check(bound_extra == 0x77665544u);
  check(reserved_calls == 0);
  check(field_run.tail == 0u);

  read_field_calls = 0;
  read_flag_calls = 0;
  bound_calls = 0;
  reserved_calls = 0;
  reserve_slot_calls = 0;
  field_run.tail = 0x7fu;
  reset_events();

  count_injection = 3u;
  record_field_run_load(&source_service, &field_run, 2);

  check(bound_calls == 0);
  check(reserved_calls == 1);
  check(reserved_table == &pair_table);
  check(reserved_count == 3u);
  check(read_field_calls == 13);
  for (std::size_t index = 0; index < 3; ++index) {
    const auto base =
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pair_storage));
    check(read_field_slot[7 + index * 2] == base + index * 8u);
    check(read_field_slot[8 + index * 2] == base + index * 8u + 4u);
  }
  check(read_flag_calls == 5);
  check(read_flag_slot[4] ==
        static_cast<TargetWord>(
            reinterpret_cast<std::uintptr_t>(&field_run.tail)));
  check(field_run.tail == 0x7fu);

  reset_record_counters();
  count_injection = 0u;
  field_run.tail = 0x7fu;
  reset_events();

  record_field_run_load(&source_service, &field_run, 0);
  check(bound_calls == 1);
  check(reserved_calls == 0);
  check(prepared_calls == 1);

  reset_record_counters();
  record_field_run_load(&source_service, &field_run, -1);
  check(bound_calls == 1);
  check(prepared_calls == 1);
  check(read_field_calls == 6);

  reset_record_counters();
  count_injection = 0u;
  reset_events();

  record_field_run_load(&source_service, &field_run, 5);
  check(bound_calls == 0);
  check(prepared_calls == 1);
  check(reserved_calls == 1);
  check(reserved_count == 0u);
  check(read_field_calls == 7);
  check(read_flag_calls == 5);

  record_runtime() = initial;
  source_vtable.reserve_30 = nullptr;
}

constexpr TargetWord kEnumResolve = 0x100u;
constexpr TargetWord kSubmitResolve = 0x200u;
constexpr TargetWord kResolveBool = 0x300u;
constexpr TargetWord kAcquireToken = 0x400u;
constexpr TargetWord kSubmitJob = 0x500u;
constexpr TargetWord kModelGet = 0x600u;
constexpr TargetWord kFactoryGet = 0x700u;
constexpr TargetWord kRenderGet = 0x800u;
constexpr TargetWord kAppGet = 0x900u;
constexpr TargetWord kQueryBc = 0xa00u;
constexpr TargetWord kQueryB8 = 0xa10u;
constexpr TargetWord kQueryB4 = 0xa20u;
constexpr TargetWord kQueryEc = 0xa30u;
constexpr TargetWord kResolve1c = 0xa40u;
constexpr TargetWord kAdopt54 = 0xa50u;
constexpr TargetWord kSubmit5c = 0xa60u;
constexpr TargetWord kDispatch14 = 0xa70u;
constexpr TargetWord kRelease04 = 0xa80u;
constexpr TargetWord kReleaseEntry = 0xa90u;

TargetWord enum_result = 0;
TargetWord enum_seen_resolver = 0;
TargetWord enum_seen_key = 0;
std::size_t enum_calls = 0;
std::size_t model_get_calls = 0;
std::size_t factory_get_calls = 0;
std::size_t render_get_calls = 0;
std::size_t app_get_calls = 0;
TargetWord query_seed = 0;
TargetWord resolve_values[3] = {0x11u, 0x22u, 0x33u};
std::size_t resolve_calls = 0;
TargetWord group_values[3] = {0};
TargetWord group_seen_id[3] = {0};
std::size_t group_calls = 0;
TargetWord handle_value = 0x7000u;
TargetWord submit_seen_source = 0;
TargetWord submit_seen_owner = 0;
TargetWord submit_seen_packed = 0;
std::size_t submit_calls = 0;
TargetWord bool_result = 0;
TargetWord bool_seen_owner = 0;
TargetWord bool_seen_key = 0;
TargetWord token_value = 0x9000u;
TargetWord token_seen_key = 0;
TargetWord token_seen_arg = 0;
TargetWord job_seen_source = 0;
TargetWord job_seen_owner = 0;
TargetWord job_seen_tag = 0;
TargetWord job_seen_packed = 0;
std::size_t job_calls = 0;
TargetWord adopt_seen_handle = 0;
TargetWord adopt_seen_second = 0;
std::size_t adopt_calls = 0;
TargetWord submit5c_seen[4] = {0};
std::size_t submit5c_calls = 0;
TargetWord dispatch_seen_key = 0;
std::size_t dispatch_calls = 0;
OpaqueHolder* release_seen = nullptr;
std::size_t release_calls = 0;
void* release_entry_seen = nullptr;
std::size_t release_entry_calls = 0;

void capture_resolve_enum(TargetWord resolver, TargetWord key,
                          TargetWord* out) {
  enum_seen_resolver = resolver;
  enum_seen_key = key;
  *out = enum_result;
  ++enum_calls;
  record(kEnumResolve, resolver, key,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(out)));
}

bool PKG_APP_WAVE10_TEST_THISCALL capture_resolve_bool(void* owner,
                                                       TargetWord key) {
  bool_seen_owner =
      static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(owner));
  bool_seen_key = key;
  record(kResolveBool, bool_seen_owner, key, 0);
  return bool_result;
}

TargetWord capture_acquire_token(TargetWord key, TargetWord argument) {
  token_seen_key = key;
  token_seen_arg = argument;
  record(kAcquireToken, key, argument, 0);
  return token_value;
}

void capture_submit_resolve(TargetWord source, TargetWord owner,
                            TargetWord packed, TargetWord* out) {
  submit_seen_source = source;
  submit_seen_owner = owner;
  submit_seen_packed = packed;
  *out = handle_value;
  ++submit_calls;
  record(kSubmitResolve, source, owner, packed);
}

TargetByte capture_submit_job(TargetWord source,
                              OpaqueJobDescriptor* descriptor,
                              TargetWord token) {
  job_seen_source = source;
  job_seen_owner = descriptor->owner;
  job_seen_tag = descriptor->tag;
  job_seen_packed = descriptor->packed;
  ++job_calls;
  record(kSubmitJob, source, token,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(descriptor)));
  return 0u;
}

void PKG_APP_WAVE10_TEST_THISCALL capture_release_entry(void* handle) {
  release_entry_seen = handle;
  ++release_entry_calls;
  record(kReleaseEntry,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(handle)));
}

void PKG_APP_WAVE10_TEST_THISCALL capture_query_bc(void* self,
                                                   OpaqueModelQuery* query) {
  query->first = query_seed;
  query->second = query_seed + 1u;
  record(kQueryBc,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)),
         query_seed, query_seed + 1u);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_query_b8(void* self,
                                                   OpaqueModelQuery* query) {
  query->first = query_seed;
  query->second = query_seed + 1u;
  record(kQueryB8,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)),
         query_seed, query_seed + 1u);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_query_b4(void* self,
                                                   OpaqueModelQuery* query) {
  query->first = query_seed;
  query->second = query_seed + 1u;
  record(kQueryB4,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)),
         query_seed, query_seed + 1u);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_query_ec(void* self, TargetWord id,
                                                   OpaqueTriple* group) {
  const std::size_t slot = id == 2u ? 0u : (id == 4u ? 1u : 2u);
  group->slots[0] = group_values[slot];
  group_seen_id[slot] = id;
  ++group_calls;
  record(kQueryEc,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)), id,
         group_values[slot]);
}

TargetWord PKG_APP_WAVE10_TEST_THISCALL capture_resolve_1c(void* self,
                                                           TargetWord first,
                                                           TargetWord second) {
  const std::size_t slot = resolve_calls;
  record(kResolve1c,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)), first,
         second);
  ++resolve_calls;
  return resolve_values[slot < 3u ? slot : 2u];
}

void PKG_APP_WAVE10_TEST_THISCALL capture_adopt_54(void* self,
                                                   TargetWord handle,
                                                   TargetWord second) {
  adopt_seen_handle = handle;
  adopt_seen_second = second;
  ++adopt_calls;
  record(kAdopt54,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)),
         handle, second);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_submit_5c(void* self,
                                                    TargetWord first,
                                                    TargetWord second,
                                                    TargetWord third,
                                                    TargetWord fourth) {
  submit5c_seen[0] = first;
  submit5c_seen[1] = second;
  submit5c_seen[2] = third;
  submit5c_seen[3] = fourth;
  ++submit5c_calls;
  record(kSubmit5c,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)), first,
         second);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_dispatch_14(void* self,
                                                      TargetWord key,
                                                      TargetWord second,
                                                      TargetWord) {
  dispatch_seen_key = key;
  ++dispatch_calls;
  record(kDispatch14,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)), key,
         second);
}

void PKG_APP_WAVE10_TEST_THISCALL capture_release_04(void* self) {
  release_seen = static_cast<OpaqueHolder*>(self);
  ++release_calls;
  record(kRelease04,
         static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(self)));
}

OpaqueModelServiceVtable model_vtable{};
OpaqueModelService model_service{&model_vtable};
OpaqueFactoryServiceVtable factory_vtable{};
OpaqueFactoryService factory_service{&factory_vtable};
OpaqueRenderServiceVtable render_vtable{};
OpaqueRenderService render_service{&render_vtable};
OpaqueAppServiceVtable app_vtable{};
OpaqueAppService app_service{&app_vtable};
OpaqueHolderVtable holder_vtable{};
OpaqueHolder holder{&holder_vtable};

OpaqueModelService* get_model() {
  ++model_get_calls;
  record(kModelGet);
  return &model_service;
}

OpaqueFactoryService* get_factory() {
  ++factory_get_calls;
  record(kFactoryGet);
  return &factory_service;
}

OpaqueRenderService* get_render() {
  ++render_get_calls;
  record(kRenderGet);
  return &render_service;
}

OpaqueAppService* get_app() {
  ++app_get_calls;
  record(kAppGet);
  return &app_service;
}

OpaqueRenderHost host{};
OpaqueSelection selection{};

void reset_render_state() {
  enum_calls = 0;
  model_get_calls = 0;
  factory_get_calls = 0;
  render_get_calls = 0;
  app_get_calls = 0;
  resolve_calls = 0;
  group_calls = 0;
  submit_calls = 0;
  adopt_calls = 0;
  submit5c_calls = 0;
  dispatch_calls = 0;
  release_calls = 0;
  release_entry_calls = 0;
  job_calls = 0;
  bool_result = 0;
  handle_value = 0x7000u;
  bool_seen_owner = 0;
  bool_seen_key = 0;
  enum_seen_resolver = 0;
  release_entry_seen = nullptr;
  reset_events();
}

void test_render_host_select() {
  RenderRuntime initial = render_runtime();
  render_runtime().resolve_enum = capture_resolve_enum;
  render_runtime().resolve_bool = capture_resolve_bool;
  render_runtime().acquire_token = capture_acquire_token;
  render_runtime().submit_resolve = capture_submit_resolve;
  render_runtime().submit_graphics_job = capture_submit_job;
  render_runtime().release_entry = capture_release_entry;
  render_runtime().model_service = get_model;
  render_runtime().factory_service = get_factory;
  render_runtime().render_service = get_render;
  render_runtime().app_service = get_app;

  model_vtable.query_bc = capture_query_bc;
  model_vtable.query_b8 = capture_query_b8;
  model_vtable.query_b4 = capture_query_b4;
  model_vtable.query_ec = capture_query_ec;
  factory_vtable.resolve_1c = capture_resolve_1c;
  render_vtable.adopt_54 = capture_adopt_54;
  render_vtable.submit_5c = capture_submit_5c;
  app_vtable.dispatch_14 = capture_dispatch_14;
  holder_vtable.release_04 = capture_release_04;

  group_values[0] = 0x10u;
  group_values[1] = 0x01u;
  group_values[2] = 0x02u;
  query_seed = 0xa0u;
  resolve_values[0] = 0x11u;
  resolve_values[1] = 0x22u;
  resolve_values[2] = 0x33u;

  std::memset(&host, 0, sizeof(host));
  std::memset(&selection, 0, sizeof(selection));
  host.source_handle = 0x4000u;
  host.owner = 0x5eu;
  host.stamp = 0xaabbccddu;
  host.resolver = 0x6000u;
  host.holder = &holder;

  enum_result = 1u;
  selection.index = 0x10u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(enum_calls == 1);
  check(enum_seen_key == 0x004c6ba3cu);
  check(enum_seen_resolver == 0x6000u);
  check(model_get_calls == 6);
  check(factory_get_calls == 3);
  check(resolve_calls == 3);
  check(group_calls == 3);
  check(group_seen_id[0] == 2u);
  check(group_seen_id[1] == 4u);
  check(group_seen_id[2] == 3u);
  check(submit_calls == 1);
  check(submit_seen_source == 0x400cu);
  check(submit_seen_owner == 0x5eu);
  check(submit_seen_packed == 0xaabb2901u);
  check(bool_seen_owner == 0x015fd918u);
  check(bool_seen_key == 0x026cd3c9u);
  check(adopt_calls == 0);
  check(job_calls == 0);
  check(submit5c_calls == 1);
  check(submit5c_seen[0] == 0x22u);
  check(submit5c_seen[1] == 0u);
  check(submit5c_seen[2] == 1u);
  check(submit5c_seen[3] == 0u);
  check(dispatch_calls == 0);
  check(app_get_calls == 0);
  check(render_get_calls == 1);
  check(release_calls == 1);
  check(release_seen == &holder);
  check(host.holder == nullptr);
  check(release_entry_calls == 1);
  check(release_entry_seen == reinterpret_cast<void*>(0x7000u));

  enum_result = 1u;
  selection.index = 0x10u;
  host.holder = &holder;
  reset_render_state();
  bool_result = 1u;
  check(render_host_select(&host, &selection) == 1u);
  check(job_calls == 1);
  check(job_seen_source ==
        static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(&holder) +
                                0x0cu));
  check(job_seen_owner == 0x5eu);
  check(job_seen_tag == 0x2f4e681cu);
  check(job_seen_packed == 0xaabb2901u);
  check(token_seen_key == 0x011ac1acu);
  check(token_seen_arg == 1u);
  check(adopt_calls == 1);
  check(adopt_seen_handle == 0x7000u);
  check(adopt_seen_second == 0u);
  check(submit5c_calls == 1);
  check(render_get_calls == 2);
  check(release_calls == 1);
  check(host.holder == nullptr);

  enum_result = 2u;
  selection.index = 0x01u;
  host.holder = nullptr;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0xaabb2902u);
  check(submit5c_calls == 1);
  check(submit5c_seen[0] == 0x33u);
  check(dispatch_calls == 0);
  check(release_calls == 0);
  check(release_entry_calls == 1);

  enum_result = 0u;
  selection.index = 0x10u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0xaabb2900u);
  check(submit5c_calls == 0);
  check(dispatch_calls == 1);
  check(dispatch_seen_key == 0x052deb9eu);
  check(app_get_calls == 1);
  check(render_get_calls == 0);

  enum_result = 1u;
  selection.index = 0x01u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit5c_calls == 0);
  check(dispatch_calls == 1);
  check(app_get_calls == 1);

  enum_result = 2u;
  selection.index = 0x02u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit5c_calls == 0);
  check(dispatch_calls == 1);

  enum_result = 2u;
  selection.index = 0x10u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit5c_calls == 1);
  check(submit5c_seen[0] == 0x22u);
  check(dispatch_calls == 0);

  enum_result = 2u;
  selection.index = 0x03u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit5c_calls == 0);
  check(dispatch_calls == 0);
  check(render_get_calls == 0);
  check(app_get_calls == 0);

  enum_result = 9u;
  selection.index = 0x10u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0xaabb2900u);
  check(submit5c_calls == 0);
  check(dispatch_calls == 0);
  check(render_get_calls == 0);
  check(app_get_calls == 0);

  enum_result = 1u;
  selection.index = 0x10u;
  reset_render_state();
  handle_value = 0u;
  check(render_host_select(&host, &selection) == 1u);
  check(release_entry_calls == 0);
  check(bool_seen_key == 0u);
  check(submit5c_calls == 1);
  check(render_get_calls == 1);

  handle_value = 0x7000u;
  host.stamp = 0xffffffffu;
  enum_result = 1u;
  selection.index = 0x10u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0xffff2901u);

  host.stamp = 0x12340000u;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0x12342901u);

  host.stamp = 0x5eu;
  reset_render_state();
  check(render_host_select(&host, &selection) == 1u);
  check(submit_seen_packed == 0x00002901u);

  render_runtime() = initial;
  model_vtable.query_bc = nullptr;
  model_vtable.query_b8 = nullptr;
  model_vtable.query_b4 = nullptr;
  model_vtable.query_ec = nullptr;
  factory_vtable.resolve_1c = nullptr;
  render_vtable.adopt_54 = nullptr;
  render_vtable.submit_5c = nullptr;
  app_vtable.dispatch_14 = nullptr;
  holder_vtable.release_04 = nullptr;
}

void run() {
  const CursorRuntime initial_cursor = cursor_runtime();
  const RecordRuntime initial_record = record_runtime();
  const RenderRuntime initial_render = render_runtime();

  test_vector3_add();
  test_property_value_resolve();
  test_cursor_buffer_emit();
  test_record_field_run_load();
  test_render_host_select();

  cursor_runtime() = initial_cursor;
  record_runtime() = initial_record;
  render_runtime() = initial_render;
}

#undef PKG_APP_WAVE10_TEST_THISCALL

}

}

int main() { openspore::reconstruction::pkg_app_wave10::run(); }
