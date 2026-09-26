#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "app_services_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL __cdecl
#define PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL __thiscall
#define PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE __declspec(noinline)
#else
#define PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL __attribute__((cdecl))
#define PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL __attribute__((thiscall))
#define PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE __attribute__((noinline))
#endif

namespace {

using namespace openspore::reconstruction::pkg_app_services_safe_wave11;

int failures = 0;
int checks = 0;

void expect(bool condition, const char* label) {
  ++checks;
  if (!condition) {
    ++failures;
    std::fprintf(stderr, "FAIL %s\n", label);
  }
}

std::vector<std::string> trace;
std::vector<OpaqueWord> payload;

void note(const char* name) { trace.emplace_back(name); }

void note_arg(const char* name, OpaqueWord value) {
  char buffer[96];
  std::snprintf(buffer, sizeof(buffer), "%s:0x%08x", name, value);
  trace.emplace_back(buffer);
}

std::string label(const char* name, OpaqueWord value) {
  char buffer[96];
  std::snprintf(buffer, sizeof(buffer), "%s:0x%08x", name, value);
  return std::string(buffer);
}

std::size_t count_prefix(const char* name) {
  const std::string prefix(name);
  std::size_t total = 0;
  for (const std::string& entry : trace) {
    if (entry.compare(0, prefix.size(), prefix) == 0) {
      ++total;
    }
  }
  return total;
}

bool contains(const std::string& wanted) {
  for (const std::string& entry : trace) {
    if (entry == wanted) {
      return true;
    }
  }
  return false;
}

std::size_t count(const char* name) {
  std::size_t total = 0;
  for (const std::string& entry : trace) {
    if (entry == name) {
      ++total;
    }
  }
  return total;
}

std::size_t index_of_prefix(const char* name) {
  const std::string prefix(name);
  for (std::size_t i = 0; i < trace.size(); ++i) {
    if (trace[i].compare(0, prefix.size(), prefix) == 0) {
      return i;
    }
  }
  return trace.size();
}

std::size_t index_of(const std::string& wanted) {
  for (std::size_t i = 0; i < trace.size(); ++i) {
    if (trace[i] == wanted) {
      return i;
    }
  }
  return trace.size();
}

OpaqueWord as_word(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

OpaqueWord g_assign_target = 0u;
OpaqueWord g_assign_source = 0u;
OpaqueWord g_copy_target = 0u;
OpaqueWord g_copy_begin = 0u;
OpaqueWord g_copy_end = 0u;
int g_assign_calls = 0;
int g_copy_calls = 0;

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_assign(OpaqueWide* dst, const OpaqueWideField* src) {
  ++g_assign_calls;
  g_assign_target = as_word(dst);
  g_assign_source = as_word(src);
  note_arg("assign", as_word(src));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_copy(OpaqueWide* dst, void* begin, void* end) {
  ++g_copy_calls;
  g_copy_target = as_word(dst);
  g_copy_begin = as_word(begin);
  g_copy_end = as_word(end);
  note("copy");
}

Ports005f9230 g_9230{};

void test_005f9230_dispatch() {
  OpaqueService service{};
  OpaqueWide destination{};
  OpaqueWord cells[4] = {0x1111u, 0x1112u, 0x1113u, 0x1114u};
  OpaqueWord creatures[4] = {0x2221u, 0x2222u, 0x2223u, 0x2224u};
  OpaqueWord buildings[4] = {0x3331u, 0x3332u, 0x3333u, 0x3334u};
  OpaqueWord plants[4] = {0x4441u, 0x4442u, 0x4443u, 0x4444u};
  OpaqueWord vehicles[4] = {0x5551u, 0x5552u, 0x5553u, 0x5554u};
  OpaqueWord ufos[4] = {0x6661u, 0x6662u, 0x6663u, 0x6664u};
  OpaqueWord music[4] = {0x7771u, 0x7772u, 0x7773u, 0x7774u};
  OpaqueWord scenarios[4] = {0x8881u, 0x8882u, 0x8883u, 0x8884u};
  service.path_104.begin = cells;
  service.path_104.end = cells + 4;
  service.path_114.begin = creatures;
  service.path_114.end = creatures + 4;
  service.path_124.begin = buildings;
  service.path_124.end = buildings + 4;
  service.path_134.begin = plants;
  service.path_134.end = plants + 4;
  service.path_144.begin = vehicles;
  service.path_144.end = vehicles + 4;
  service.path_154.begin = ufos;
  service.path_154.end = ufos + 4;
  service.path_164.begin = music;
  service.path_164.end = music + 4;
  service.path_174.begin = scenarios;
  service.path_174.end = scenarios + 4;
  g_ports_005f9230 = &g_9230;
  g_9230.assign_0057cb60 = &stub_assign;
  g_9230.copy_00423650 = &stub_copy;

  struct AssignCase {
    OpaqueWord key;
    OpaqueWord field;
  };
  const AssignCase assigns[] = {
      {OPAQUE_KEY_BUILDINGS, as_word(&service.path_124)},
      {OPAQUE_KEY_CITY_MUSIC, as_word(&service.path_164)},
      {OPAQUE_KEY_VEHICLES, as_word(&service.path_144)},
      {OPAQUE_KEY_CREATURES, as_word(&service.path_114)},
      {OPAQUE_KEY_UFOS, as_word(&service.path_154)},
  };
  for (std::size_t i = 0; i < sizeof(assigns) / sizeof(assigns[0]); ++i) {
    trace.clear();
    g_assign_calls = 0;
    g_copy_calls = 0;
    g_assign_target = 0u;
    g_assign_source = 0u;
    expect(service_005f9230(&service, assigns[i].key, &destination),
           "005f9230 assign key returns true");
    expect(g_assign_calls == 1, "005f9230 assign key calls assign once");
    expect(g_copy_calls == 0, "005f9230 assign key skips the copy port");
    expect(g_assign_target == as_word(&destination),
           "005f9230 assign keeps the destination receiver");
    expect(g_assign_source == assigns[i].field,
           "005f9230 assign selects the mapped field");
  }

  struct CopyCase {
    OpaqueWord key;
    const OpaqueWord* head;
    const OpaqueWord* tail;
  };
  const CopyCase copies[] = {
      {OPAQUE_KEY_SCENARIOS, scenarios, scenarios + 4},
      {OPAQUE_KEY_CELLS, cells, cells + 4},
      {OPAQUE_KEY_PLANTS, plants, plants + 4},
  };
  for (std::size_t i = 0; i < sizeof(copies) / sizeof(copies[0]); ++i) {
    trace.clear();
    g_assign_calls = 0;
    g_copy_calls = 0;
    expect(service_005f9230(&service, copies[i].key, &destination),
           "005f9230 copy key returns true");
    expect(g_copy_calls == 1, "005f9230 copy key calls copy once");
    expect(g_assign_calls == 0, "005f9230 copy key skips the assign port");
    expect(g_copy_target == as_word(&destination),
           "005f9230 copy keeps the destination receiver");
    expect(g_copy_begin == as_word(copies[i].head),
           "005f9230 copy passes the field head");
    expect(g_copy_end == as_word(copies[i].tail),
           "005f9230 copy passes the field tail");
  }

  trace.clear();
  g_assign_calls = 0;
  g_copy_calls = 0;
  expect(service_005f9230(&service, 0x12345678u, &destination),
         "005f9230 unknown key returns true");
  expect(g_assign_calls == 0 && g_copy_calls == 0,
         "005f9230 unknown key touches no port");

  trace.clear();
  g_assign_calls = 0;
  g_copy_calls = 0;
  expect(service_005f9230(&service, OPAQUE_KEY_PLANTS,
                          reinterpret_cast<OpaqueWide*>(&service.path_134)),
         "005f9230 aliased copy destination still returns true");
  expect(g_copy_calls == 0, "005f9230 aliased copy destination skips the copy");
  expect(g_assign_calls == 0,
         "005f9230 aliased copy destination skips the assign");

  trace.clear();
  g_assign_calls = 0;
  g_copy_calls = 0;
  expect(service_005f9230(&service, OPAQUE_KEY_BUILDINGS,
                          reinterpret_cast<OpaqueWide*>(&service.path_124)),
         "005f9230 assign key ignores aliasing");
  expect(g_assign_calls == 1, "005f9230 assign key fires even when aliased");
}

OpaqueWord g_table_id = 0u;
OpaqueWord g_instance = 0u;
OpaqueWord g_literal = 0u;
OpaqueWord g_prepare_key = 0u;
OpaqueWord g_prepare_target = 0u;
OpaqueWord g_prepare_flag = 0u;
OpaqueWord g_append_begin = 0u;
OpaqueWord g_append_end = 0u;
OpaqueWord g_truncate_index = 0u;
OpaqueWord g_truncate_count = 0u;
OpaqueWord g_truncate_fill = 0u;
OpaqueWord g_finalize_input = 0u;
OpaqueWord g_finalize_result = 0u;
int g_9310_emit_calls = 0;
int g_destroy_calls = 0;
int g_truncate_calls = 0;
int g_append_calls = 0;

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_resolve(OpaqueWide* dst, OpaqueWord table, OpaqueWord instance,
                 const void* literal) {
  g_table_id = table;
  g_instance = instance;
  g_literal = as_word(literal);
  dst->begin = dst->end = nullptr;
  note("resolve");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_prepare(OpaqueWord key, OpaqueWide* dst, OpaqueWord flag) {
  g_prepare_key = key;
  g_prepare_target = as_word(dst);
  g_prepare_flag = flag;
  note("prepare");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_append(OpaqueWide* dst, const void* begin, const void* end) {
  (void)dst;
  ++g_append_calls;
  g_append_begin = as_word(begin);
  g_append_end = as_word(end);
  note("append");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL const void*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_emit(OpaqueWide* scratch) {
  (void)scratch;
  ++g_9310_emit_calls;
  note("emit");
  return payload.data();
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_truncate(OpaqueWide* dst, OpaqueWord index, OpaqueWord count,
                  const void* fill) {
  (void)dst;
  ++g_truncate_calls;
  g_truncate_index = index;
  g_truncate_count = count;
  g_truncate_fill = as_word(fill);
  note("truncate");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueByte
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_finalize(const void* input) {
  g_finalize_input = as_word(input);
  note("finalize");
  return static_cast<OpaqueByte>(g_finalize_result);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_destroy(OpaqueWide* scratch) {
  (void)scratch;
  ++g_destroy_calls;
  note("destroy");
}

Ports005f9310 g_9310{};

void install_9310() {
  g_ports_005f9310 = &g_9310;
  g_9310.resolve_006b5770 = &stub_resolve;
  g_9310.prepare_00688830 = &stub_prepare;
  g_9310.append_00429580 = &stub_append;
  g_9310.emit_006b55c0 = &stub_emit;
  g_9310.truncate_005f8f80 = &stub_truncate;
  g_9310.finalize_00932ae0 = &stub_finalize;
  g_9310.destroy_006b5240 = &stub_destroy;
}

void reset_9310() {
  trace.clear();
  g_table_id = 0u;
  g_instance = 0u;
  g_literal = 0u;
  g_prepare_key = 0u;
  g_prepare_target = 0u;
  g_prepare_flag = 0u;
  g_append_begin = 0u;
  g_append_end = 0u;
  g_truncate_index = 0u;
  g_truncate_count = 0u;
  g_truncate_fill = 0u;
  g_finalize_input = 0u;
  g_finalize_result = 0u;
  g_9310_emit_calls = 0;
  g_destroy_calls = 0;
  g_truncate_calls = 0;
  g_append_calls = 0;
}

void test_005f9310() {
  OpaqueService service{};
  OpaqueWide destination{};
  OpaqueWord tail_text[3] = {0x0041u, 0x0042u, 0x0000u};
  OpaqueWord plain[2] = {0x0041u, 0x002fu};
  OpaqueWord tagged[2] = {0x0041u, 0x0ff0fu};
  OpaqueWord bare[1] = {0x0041u};
  auto wide_end = [](OpaqueWord* begin, std::size_t units) {
    return reinterpret_cast<OpaqueWord*>(reinterpret_cast<OpaqueByte*>(begin) +
                                         units * 2u);
  };
  payload.assign(tail_text, tail_text + 3);
  install_9310();

  reset_9310();
  g_finalize_result = 1u;
  destination.begin = plain;
  destination.end = wide_end(plain, 2);
  const OpaqueWord dst_last = plain[1];
  expect(service_005f9310(&service, 0x0000abcdu, &destination,
                          OPAQUE_TABLE_DEFAULT),
         "005f9310 true probe returns true");
  expect(g_table_id == OPAQUE_TABLE_SUBSTITUTE,
         "005f9310 substitutes the default table id");
  expect(g_instance == 0x0000abcdu, "005f9310 forwards the instance id");
  expect(g_literal == as_word(OPAQUE_WIDE_DEFAULT_FOLDER),
         "005f9310 forwards the default folder literal");
  expect(g_prepare_key == OPAQUE_PREPARE_00688830_KEY,
         "005f9310 prepares the observed locale key");
  expect(g_prepare_target == as_word(&destination),
         "005f9310 prepares the caller destination");
  expect(g_prepare_flag == 0u, "005f9310 prepares with a zero flag");
  expect(dst_last == 0x002fu, "005f9310 fixture keeps the trailing slash");
  expect(g_append_calls == 2, "005f9310 appends the folder then the tail");
  expect(g_append_begin == as_word(payload.data()),
         "005f9310 keeps the emitted tail as the last append");
  expect(g_append_end == as_word(payload.data() + 2),
         "005f9310 stops the tail append at the terminator");
  expect(g_9310_emit_calls == 1, "005f9310 asks the emitter exactly once");
  expect(g_destroy_calls == 1, "005f9310 destroys the scratch once");
  expect(index_of(std::string("destroy")) > index_of(std::string("finalize")),
         "005f9310 destroys after the finalize probe");
  expect(g_finalize_input == as_word(&plain[0]),
         "005f9310 finalizes the destination head");

  reset_9310();
  destination.begin = bare;
  destination.end = wide_end(bare, 1);
  g_finalize_result = 1u;
  service_005f9310(&service, 0x0000abcdu, &destination, OPAQUE_TABLE_DEFAULT);
  expect(g_append_calls == 3,
         "005f9310 appends a separator after an unterminated tail");
  expect(g_append_begin == as_word(OPAQUE_WIDE_SLASH),
         "005f9310 appends the slash literal as the separator");
  expect(g_append_end == as_word(OPAQUE_WIDE_SLASH + 1),
         "005f9310 appends exactly one separator unit");

  reset_9310();
  destination.begin = plain;
  destination.end = wide_end(plain, 2);
  g_finalize_result = 0u;
  expect(!service_005f9310(&service, 0x0000abcdu, &destination, 0x1234u),
         "005f9310 false probe returns false");
  expect(g_table_id == 0x1234u, "005f9310 keeps an explicit table id");
  expect(g_destroy_calls == 1, "005f9310 destroys the scratch on failure");

  reset_9310();
  g_finalize_result = 0xffffff00u;
  expect(!service_005f9310(&service, 1u, &destination, 0u),
         "005f9310 reads only the low byte of the probe");

  service.field_184 = 1u;
  reset_9310();
  g_finalize_result = 1u;
  service_005f9310(&service, 1u, &destination, 0u);
  expect(g_append_calls == 1, "005f9310 gate suppresses the folder append");
  expect(g_9310_emit_calls == 1, "005f9310 still emits under the gate");

  service.field_184 = 0xff00u;
  reset_9310();
  g_finalize_result = 1u;
  service_005f9310(&service, 1u, &destination, 0u);
  expect(g_append_calls == 2, "005f9310 gate reads only the low byte");

  service.field_184 = 0x0001u;
  reset_9310();
  g_finalize_result = 1u;
  service_005f9310(&service, 1u, &destination, 0u);
  expect(g_append_calls == 1, "005f9310 gate ignores the high word");

  service.field_184 = 0u;
  destination.begin = tagged;
  destination.end = wide_end(tagged, 2);
  reset_9310();
  g_finalize_result = 1u;
  service_005f9310(&service, 1u, &destination, 0u);
  expect(g_truncate_calls == 1, "005f9310 terminator triggers one truncate");
  expect(g_truncate_index == 1u, "005f9310 truncate drops the terminator");
  expect(g_truncate_count == 1u, "005f9310 truncate removes one unit");
  expect(g_truncate_fill == as_word(OPAQUE_WIDE_SLASH),
         "005f9310 truncate substitutes the slash");
  expect(g_append_calls == 2, "005f9310 terminator skips the separator");

  destination.begin = plain;
  destination.end = wide_end(plain, 2);
  reset_9310();
  g_finalize_result = 1u;
  service_005f9310(&service, 1u, &destination, 0u);
  expect(g_truncate_calls == 0, "005f9310 trailing slash never truncates");
  expect(g_append_calls == 2, "005f9310 trailing slash skips the separator");
}

OpaqueGlobalVTable g_a8d0_global_vtable{};
OpaqueHandleVTable g_a8d0_handle_vtable{};
OpaqueDatabaseVTable g_a8d0_database_vtable{};
OpaqueOwnerVTable g_a8d0_owner_vtable{};
OpaqueGlobal g_a8d0_global{};
OpaqueDatabase g_a8d0_database{};
OpaqueOwner g_a8d0_owner{};
OpaqueHandle g_a8d0_handle{};
Ports005fa8d0 g_a8d0{};

OpaqueWord g_encoder_receiver = 0u;
OpaqueWord g_encoder_planes = 0u;
OpaqueWord g_encoder_facets = 0u;
OpaqueWord g_encoder_depth = 0u;
OpaqueWord g_encoder_png = 0u;
OpaqueWord g_buffer = 0x00c0ffeeu;
OpaqueWord g_fill_result = 1u;
OpaqueWord g_fill_receiver = 0u;
OpaqueWord g_fill_size = 0u;
OpaqueWord g_fill_mip = 0u;
OpaqueWord g_resolve_first = 0u;
OpaqueWord g_resolve_second = 0u;
OpaqueWord g_resolve_third = 0u;
OpaqueWord g_descriptor[3] = {0u, 0u, 0u};
OpaqueWord g_database_out = 0u;
OpaqueWord g_database_mode[4] = {0u, 0u, 0u, 0u};
OpaqueWord g_pending_after = 0u;
OpaqueWord g_tagged[3] = {0u, 0u, 0u};
OpaqueWord g_global_tail = 0u;
OpaqueWord g_owner_size = 0x1234u;
int g_owner_release = 0;
int g_handle_releases = 0;
int g_emit_calls = 0;
bool g_query_ok = true;
bool g_resolve_ok = true;
bool g_database_ok = true;
bool g_open_ok = true;
bool g_write_ok = true;

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_prepare_encoder(OpaqueEncoder70* receiver, OpaqueHalf planes,
                         OpaqueHalf facets, OpaqueByte depth, OpaqueWord png) {
  g_encoder_receiver = as_word(receiver);
  g_encoder_planes = planes;
  g_encoder_facets = facets;
  g_encoder_depth = depth;
  g_encoder_png = png;
  note_arg("prepare_encoder", png);
  return reinterpret_cast<OpaqueWord*>(&g_buffer);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_fill(void* receiver, void* buffer, OpaqueWord size, OpaqueWord mip) {
  (void)buffer;
  g_fill_receiver = as_word(receiver);
  g_fill_size = size;
  g_fill_mip = mip;
  note_arg("fill", size);
  return g_fill_result != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_global_a() {
  note("global");
  return reinterpret_cast<OpaqueWord*>(static_cast<void*>(&g_a8d0_global));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_global_slot_0c(OpaqueGlobal* self, void* first, void* second,
                        OpaqueWord third, OpaqueWord fourth, OpaqueWord fifth,
                        OpaqueWord sixth) {
  (void)self;
  (void)third;
  (void)fourth;
  (void)fifth;
  const OpaqueWord* key = static_cast<const OpaqueWord*>(first);
  g_tagged[0] = key[0];
  g_tagged[1] = key[1];
  g_tagged[2] = key[2];
  g_pending_after = *static_cast<OpaqueWord*>(second);
  g_global_tail = sixth;
  note_arg("global_0c", g_pending_after);
  return g_query_ok;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_resolve2(OpaqueService* self, OpaqueWord first, OpaqueWord second,
                  OpaqueWord third) {
  (void)self;
  g_resolve_first = first;
  g_resolve_second = second;
  g_resolve_third = third;
  note_arg("resolve2", first);
  return g_resolve_ok;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_database_slot_34(OpaqueDatabase* self, void* first, void* second,
                          OpaqueWord a3, OpaqueWord a4, OpaqueWord a5,
                          OpaqueWord a6) {
  (void)self;
  const OpaqueWord* key = static_cast<const OpaqueWord*>(first);
  g_descriptor[0] = key[0];
  g_descriptor[1] = key[1];
  g_descriptor[2] = key[2];
  if (g_database_ok) {
    *static_cast<OpaqueWord*>(second) = as_word(&g_a8d0_owner);
  }
  g_database_out = *static_cast<OpaqueWord*>(second);
  g_database_mode[0] = a3;
  g_database_mode[1] = a4;
  g_database_mode[2] = a5;
  g_database_mode[3] = a6;
  note("database_34");
  return g_database_ok;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_owner_slot_18(OpaqueOwner* self, OpaqueWord flag) {
  (void)self;
  (void)flag;
  note("owner_18");
  return g_owner_size;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_owner_slot_24(OpaqueOwner* self) {
  (void)self;
  ++g_owner_release;
  note("owner_24");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_emit_encoder(OpaqueEncoder70* receiver, OpaqueWord value) {
  (void)receiver;
  ++g_emit_calls;
  note_arg("emit_encoder", value);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_emit_pair(OpaqueEncoder70* receiver, void* first, OpaqueWord second) {
  (void)receiver;
  (void)first;
  (void)second;
  ++g_emit_calls;
  note("emit_pair");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_handle_04(OpaqueHandle* self) {
  (void)self;
  ++g_handle_releases;
  note("handle_04");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_handle_08(OpaqueHandle* self) {
  (void)self;
  ++g_handle_releases;
  note("handle_08");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_owner_slot_08(OpaqueOwner* self) {
  (void)self;
  ++g_handle_releases;
  note("owner_08");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_handle_0c(OpaqueHandle* self, OpaqueWord tag) {
  (void)self;
  note_arg("handle_0c", tag);
  return 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_compose(OpaqueWord receiver, void* first, void* second, OpaqueWord a3,
                 OpaqueWord a4) {
  (void)receiver;
  (void)first;
  (void)second;
  (void)a3;
  (void)a4;
  note("compose");
  return reinterpret_cast<OpaqueWord*>(&g_buffer);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_write(OpaqueService* self, void* handle) {
  (void)self;
  (void)handle;
  note("write");
  return g_write_ok;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_slot(void* receiver, void* source) {
  (void)receiver;
  (void)source;
  note("slot");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_open_slot(void* receiver) {
  (void)receiver;
  note("open_slot");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_open_query(void* receiver, OpaqueWord a1, OpaqueWord a2, OpaqueWord a3,
                    OpaqueWord a4) {
  (void)receiver;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  note_arg("open", g_open_ok ? 1u : 0u);
  return g_open_ok;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_destroy(void* receiver, void* source) {
  (void)receiver;
  (void)source;
  note("destroy");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_release(void* receiver) {
  (void)receiver;
  note("release");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_build(void* receiver, void* source) {
  (void)receiver;
  (void)source;
  note("build");
  return reinterpret_cast<OpaqueWord*>(&g_buffer);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_store(void* receiver, void* value) {
  (void)receiver;
  (void)value;
  note("store");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_insert(OpaqueBlock32* block, void* first, void* second) {
  (void)first;
  (void)second;
  note_arg("insert", as_word(block));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_clear(void* receiver) {
  (void)receiver;
  note("clear");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_select(void* receiver, void* first, void* second) {
  (void)receiver;
  (void)first;
  (void)second;
  note("select");
  return reinterpret_cast<OpaqueWord*>(&g_buffer);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_record(OpaqueBlock32* block, void* first, void* second) {
  (void)first;
  (void)second;
  note_arg("record", as_word(block));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_flush(OpaqueService* self) {
  (void)self;
  note("flush");
}

void install_a8d0() {
  g_ports_005fa8d0 = &g_a8d0;
  g_a8d0.prepare_0068e8f0 = &stub_prepare_encoder;
  g_a8d0.fill_011f0440 = &stub_fill;
  g_a8d0.global_0067dcd0 = &stub_global_a;
  g_a8d0.resolve_005f9920 = &stub_resolve2;
  g_a8d0.write_005f97c0 = &stub_write;
  g_a8d0.compose_00414e10 = &stub_compose;
  g_a8d0.push_00931e10 = &stub_slot;
  g_a8d0.open_009317b0 = &stub_open_slot;
  g_a8d0.open_009318f0 = &stub_open_query;
  g_a8d0.emit_0068e1a0 = &stub_emit_encoder;
  g_a8d0.emit_pair_0068e1a0 = &stub_emit_pair;
  g_a8d0.close_00931a70 = &stub_open_slot;
  g_a8d0.destroy_0056e2d0 = &stub_destroy;
  g_a8d0.release_005f7970 = &stub_release;
  g_a8d0.build_005f9080 = &stub_build;
  g_a8d0.build_005f90c0 = &stub_build;
  g_a8d0.store_005f8320 = &stub_store;
  g_a8d0.store_005f8390 = &stub_store;
  g_a8d0.insert_005fa0a0 = &stub_insert;
  g_a8d0.insert_005fa0d0 = &stub_insert;
  g_a8d0.clear_00933960 = &stub_clear;
  g_a8d0.clear_00931e70 = &stub_clear;
  g_a8d0.clear_005f8d80 = &stub_clear;
  g_a8d0.select_005f7940 = &stub_select;
  g_a8d0.record_005f8ed0 = &stub_record;
  g_a8d0.record_005f8f00 = &stub_record;
  g_a8d0.flush_005f8ad0 = &stub_flush;
  g_a8d0_global_vtable = OpaqueGlobalVTable{};
  g_a8d0_global_vtable.slot_0c = &stub_global_slot_0c;
  g_a8d0_global.vtable = &g_a8d0_global_vtable;
  g_a8d0_handle_vtable = OpaqueHandleVTable{};
  g_a8d0_handle_vtable.slot_04 = &stub_handle_04;
  g_a8d0_handle_vtable.slot_08 = &stub_handle_08;
  g_a8d0_handle_vtable.slot_0c = &stub_handle_0c;
  g_a8d0_handle.vtable = &g_a8d0_handle_vtable;
  g_a8d0_database_vtable = OpaqueDatabaseVTable{};
  g_a8d0_database_vtable.slot_34 = &stub_database_slot_34;
  g_a8d0_database.vtable = &g_a8d0_database_vtable;
  g_a8d0_owner_vtable = OpaqueOwnerVTable{};
  g_a8d0_owner_vtable.slot_08 = &stub_owner_slot_08;
  g_a8d0_owner_vtable.slot_18 = &stub_owner_slot_18;
  g_a8d0_owner_vtable.slot_24 = &stub_owner_slot_24;
  g_a8d0_owner.vtable = &g_a8d0_owner_vtable;
}

void reset_a8d0() {
  trace.clear();
  g_encoder_receiver = 0u;
  g_encoder_planes = 0u;
  g_encoder_facets = 0u;
  g_encoder_depth = 0u;
  g_encoder_png = 0u;
  g_fill_result = 1u;
  g_fill_receiver = 0u;
  g_fill_size = 0u;
  g_fill_mip = 0u;
  g_resolve_first = 0u;
  g_resolve_second = 0u;
  g_resolve_third = 0u;
  g_descriptor[0] = 0u;
  g_descriptor[1] = 0u;
  g_descriptor[2] = 0u;
  g_database_out = 0u;
  g_database_mode[0] = 0u;
  g_database_mode[1] = 0u;
  g_database_mode[2] = 0u;
  g_database_mode[3] = 0u;
  g_pending_after = 0u;
  g_tagged[0] = 0u;
  g_tagged[1] = 0u;
  g_tagged[2] = 0u;
  g_global_tail = 0u;
  g_owner_release = 0;
  g_handle_releases = 0;
  g_emit_calls = 0;
  g_query_ok = true;
  g_resolve_ok = true;
  g_database_ok = true;
  g_open_ok = true;
  g_write_ok = true;
}

void test_005fa8d0() {
  OpaqueService service{};
  OpaqueWord resource[6] = {0u, 0u, 0x1111u, 0x2222u, 0x3333u, 0u};
  OpaqueWord raster[8] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
  raster[0] = OPAQUE_FORMAT_PNG;
  raster[3] = 0x0021u | (0x0006u << 16);
  raster[4] = 0x0010u;
  install_a8d0();

  reset_a8d0();
  expect(
      !service_005fa8d0(&service, resource, nullptr, &g_a8d0_database, 0u, 0u),
      "005fa8d0 rejects a null raster");
  expect(trace.empty(), "005fa8d0 null raster touches no port");
  expect(service.image_0f8.w0 == 0u, "005fa8d0 null raster keeps the key");

  reset_a8d0();
  g_fill_result = 0u;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 rejects a failed raster fill");
  expect(service.image_0f8.w0 == 0u, "005fa8d0 fill failure keeps the key");
  expect(count("global") == 0, "005fa8d0 fill failure stops before the global");

  reset_a8d0();
  expect(service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
         "005fa8d0 accepts the full path");
  expect(service.image_0f8.w0 == 0x1111u, "005fa8d0 stores key word zero");
  expect(service.image_0f8.w1 == 0x2222u, "005fa8d0 stores key word one");
  expect(service.image_0f8.w2 == 0x3333u, "005fa8d0 stores key word two");
  expect(g_encoder_receiver == as_word(&service.encoder_088),
         "005fa8d0 prepares through the embedded encoder");
  expect(g_encoder_planes == 0x0021u, "005fa8d0 reads the raster depth word");
  expect(g_encoder_facets == 0x0006u, "005fa8d0 reads the raster facet word");
  expect(g_encoder_depth == 0x0010u, "005fa8d0 reads the raster size byte");
  expect(g_encoder_png == 1u, "005fa8d0 flags the png raster format");
  expect(g_fill_receiver == as_word(raster), "005fa8d0 fills on the raster");
  expect(g_fill_mip == 0u, "005fa8d0 fills mip level zero");
  expect(g_fill_size == ((0x10u * 0x06u * 0x21u) + 7u) / 8u,
         "005fa8d0 rounds the byte budget up");
  expect(g_tagged[0] == 0x1111u, "005fa8d0 tags the key head");
  expect(g_tagged[1] == OPAQUE_TAG_30bdee3,
         "005fa8d0 swaps in the observed tag word");
  expect(g_tagged[2] == 0x3333u, "005fa8d0 keeps the key tail");
  expect(g_global_tail == 0u, "005fa8d0 passes a zero tail argument");
  expect(g_pending_after == 0u, "005fa8d0 leaves the pending slot zeroed");
  expect(g_resolve_first == 0u,
         "005fa8d0 skips the handle query while pending is null");
  expect(g_resolve_second == as_word(resource),
         "005fa8d0 forwards the resource argument");
  expect(g_resolve_third == 0u, "005fa8d0 forwards the observed tail word");
  expect(g_descriptor[0] == 0x1111u, "005fa8d0 descriptor keeps the key head");
  expect(g_descriptor[1] == OPAQUE_TAG_2f7d0004,
         "005fa8d0 descriptor carries the component word");
  expect(g_descriptor[2] == 0x3333u, "005fa8d0 descriptor keeps the key tail");
  expect(g_database_out == as_word(&g_a8d0_owner),
         "005fa8d0 hands the produced handle back");
  expect(g_database_mode[0] == 2u, "005fa8d0 keeps the first mode word");
  expect(g_database_mode[1] == 6u, "005fa8d0 keeps the second mode word");
  expect(g_database_mode[2] == 1u, "005fa8d0 keeps the third mode word");
  expect(g_database_mode[3] == 0u, "005fa8d0 keeps the fourth mode word");
  expect(g_emit_calls == 2, "005fa8d0 emits into the encoder twice");
  expect(count("flush") == 1, "005fa8d0 flushes exactly once");
  expect(!contains("handle_04"),
         "005fa8d0 never releases the zeroed pending slot");
  expect(contains("owner_08"), "005fa8d0 releases the produced handle");
  expect(g_owner_release == 1, "005fa8d0 releases the owner once");
  expect(contains(label("insert", as_word(&service.block_004))),
         "005fa8d0 inserts into the first block");
  expect(contains(label("insert", as_word(&service.block_024))),
         "005fa8d0 inserts into the second block");
  expect(contains(label("record", as_word(&service.block_048))),
         "005fa8d0 records into the first block");
  expect(contains(label("record", as_word(&service.block_068))),
         "005fa8d0 records into the second block");
  expect(index_of(std::string("flush")) >
             index_of(label("record", as_word(&service.block_068))),
         "005fa8d0 flushes after both records");

  raster[0] = 0x00000010u;
  reset_a8d0();
  expect(service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
         "005fa8d0 accepts a non png raster");
  expect(g_encoder_png == 0u, "005fa8d0 clears the png flag otherwise");

  reset_a8d0();
  g_query_ok = false;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 fails when the global rejects");
  expect(count_prefix("global_0c") == 1,
         "005fa8d0 asks the global exactly once");
  expect(count("resolve2") == 0, "005fa8d0 stops before the resolver");
  expect(g_handle_releases == 0,
         "005fa8d0 early exit never reaches the pending release");

  reset_a8d0();
  g_resolve_ok = false;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 fails when the resolver rejects");
  expect(count("database_34") == 0, "005fa8d0 stops before the database");

  reset_a8d0();
  g_database_ok = false;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 fails when the database rejects");
  expect(count("compose") == 0, "005fa8d0 stops before the composer");

  reset_a8d0();
  g_write_ok = false;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 fails when the writer rejects");
  expect(count("slot") == 0, "005fa8d0 stops before the path push");
  expect(count("clear") == 1, "005fa8d0 clears one temporary on that exit");

  reset_a8d0();
  g_open_ok = false;
  expect(
      !service_005fa8d0(&service, resource, raster, &g_a8d0_database, 0u, 0u),
      "005fa8d0 fails when the open query rejects");
  expect(count("open_slot") == 1,
         "005fa8d0 prepares the stream state before the failed open");
  expect(count("clear") == 2,
         "005fa8d0 clears both temporaries after a failed open");
  expect(index_of(std::string("open_slot")) < index_of(std::string("clear")),
         "005fa8d0 closes the stream before the final clear");
}

OpaqueWord g_probe_flag = 1u;
OpaqueWord g_open_flag = 1u;
OpaqueWord g_found = 0u;
OpaqueWord g_resolve_flag = 0u;
OpaqueWord g_cast_flag = 0u;
OpaqueWord g_gate_handle = 0u;
OpaqueWord g_node_build = 0u;
OpaqueWord g_slot_1c_flag = 1u;
OpaqueWord g_slot_20_flag = 1u;
OpaqueWord g_slot_34_flag = 1u;
OpaqueWord* g_entries = nullptr;
OpaqueWord* g_node_pool = nullptr;
OpaqueKey12 g_lifted_key{};
int g_close_raster = 0;
int g_close_stream = 0;
OpaqueFactoryVTable g_c_factory_vtable{};
OpaqueFactory g_c_factory{};
OpaqueSideVTable g_c_side_vtable{};
OpaqueSide g_c_side{};
OpaqueGateVTable g_c_gate_vtable{};
OpaqueGate g_c_gate{};
OpaqueGlobalVTable g_c_global_vtable{};
OpaqueGlobal g_c_global{};
OpaqueHandleVTable g_c_handle_vtable{};
OpaqueHandle g_c_handle{};
OpaqueOwnerVTable g_c_owner_vtable{};
OpaqueOwner g_c_owner{};
OpaqueWord g_c_allocator[24] = {0u};

struct OpaqueNodeObject {
  OpaqueOwnerVTable* vtable = nullptr;
  OpaqueWord slot_04 = 0u;
  OpaqueWord head = 0u;
  OpaqueWord middle = 0u;
  OpaqueWord tail = 0u;
  OpaqueWord slot_18 = 0u;
};

OpaqueNodeObject g_c_node{};
OpaqueOwnerVTable g_c_node_vtable{};
Ports005fc330 g_c330{};

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_slot(void* receiver, void* source) {
  (void)receiver;
  (void)source;
  note("push");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_open(void* receiver) {
  (void)receiver;
  note("state");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_query(void* receiver, OpaqueWord a1, OpaqueWord a2, OpaqueWord a3,
                 OpaqueWord a4) {
  (void)receiver;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  note_arg("query", g_open_flag);
  return g_open_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_get() {
  note("get");
  return g_c_allocator;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_probe(OpaqueService* self, void* first, void* second, void* third) {
  (void)self;
  (void)first;
  (void)second;
  OpaqueKey12* out = static_cast<OpaqueKey12*>(third);
  out->w0 = 0u;
  out->w1 = 0x7001u;
  out->w2 = 0x7002u;
  note_arg("probe", g_probe_flag);
  return g_probe_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_reset(OpaqueBlock32* block, void* first, void* second) {
  (void)second;
  note_arg("reset", as_word(block));
  *static_cast<OpaqueWord*>(first) = g_found;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_close_raster(void* receiver) {
  (void)receiver;
  ++g_close_raster;
  note("close_raster");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_close_stream(void* receiver) {
  (void)receiver;
  ++g_close_stream;
  note("close_stream");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_close_slot(void* receiver) {
  (void)receiver;
  note("close_slot");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_resolve(void* receiver, OpaqueWord a1, OpaqueWord a2, void* third) {
  (void)receiver;
  (void)a1;
  (void)a2;
  note_arg("resolve", as_word(third));
  if (g_resolve_flag != 0u && third != nullptr) {
    OpaqueKey12* out = static_cast<OpaqueKey12*>(third);
    out->w0 = 0x8001u;
    out->w1 = 0x8002u;
    out->w2 = 0x8003u;
  }
  return g_resolve_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_mark(void* receiver, OpaqueWord a1, OpaqueWord a2, OpaqueWord a3) {
  (void)receiver;
  (void)a1;
  (void)a2;
  (void)a3;
  note("mark");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_lift(void* receiver, OpaqueWord a1, void* second, void* third) {
  (void)receiver;
  (void)a1;
  (void)third;
  note_arg("lift", as_word(second));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_cast(OpaqueFactory* self, void* out) {
  (void)self;
  const OpaqueKey12* key = static_cast<const OpaqueKey12*>(out);
  g_lifted_key.w0 = key->w0;
  g_lifted_key.w1 = key->w1;
  g_lifted_key.w2 = key->w2;
  note_arg("cast", g_cast_flag);
  return g_cast_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_side(OpaqueSide* self, void* first, void* second, OpaqueWord third) {
  (void)self;
  (void)second;
  (void)third;
  note_arg("side", as_word(first));
  return true;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_factory(OpaqueWord a1, OpaqueWord a2, OpaqueWord a3, OpaqueWord a4,
                   OpaqueWord a5, OpaqueWord a6) {
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  note_arg("factory", a1);
  return g_entries;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_build_meta(void* receiver) {
  (void)receiver;
  note("build_meta");
  return reinterpret_cast<OpaqueWord*>(&g_c_owner);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_meta(void* receiver, void* a1, void* a2, void* a3, void* a4,
                void* a5, void* a6, void* a7, void* a8, OpaqueWord a9,
                OpaqueWord a10, OpaqueWord a11, OpaqueWord a12,
                OpaqueWord a13) {
  (void)receiver;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  (void)a7;
  (void)a8;
  (void)a9;
  (void)a10;
  (void)a11;
  (void)a12;
  note_arg("meta", a13);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_seal(void* receiver, OpaqueWord a1, OpaqueWord a2) {
  (void)receiver;
  (void)a1;
  (void)a2;
  note("seal");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_flag(void* receiver, OpaqueWord flag) {
  (void)receiver;
  note_arg("flag", flag);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_drop(void* receiver, OpaqueWord value) {
  (void)receiver;
  note_arg("drop", value);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_resource(OpaqueWord tag) {
  note_arg("resource", tag);
  return reinterpret_cast<OpaqueWord*>(&g_c_gate);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_global() {
  note("global");
  return reinterpret_cast<OpaqueWord*>(&g_c_global);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_side_get() {
  note("side_get");
  return reinterpret_cast<OpaqueWord*>(&g_c_side);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_global_48(OpaqueGlobal* self, void* a1, OpaqueWord a2) {
  (void)self;
  (void)a2;
  if (a1 != nullptr) {
    *static_cast<OpaqueWord*>(a1) = g_gate_handle;
  }
  note_arg("global_48", g_gate_handle);
  return g_gate_handle != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_global_20(OpaqueGlobal* self, OpaqueWord a1, OpaqueWord a2,
                     OpaqueWord a3, OpaqueWord a4, OpaqueWord a5) {
  (void)self;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  note_arg("global_20", a5);
  return g_slot_20_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_global_14(OpaqueGlobal* self, OpaqueWord a1, OpaqueWord a2) {
  (void)self;
  (void)a2;
  note_arg("global_14", a1);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_node(OpaqueWord a1, OpaqueWord a2, OpaqueWord a3, OpaqueWord a4,
                OpaqueWord a5, OpaqueWord a6) {
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  note_arg("node", a1);
  return reinterpret_cast<OpaqueWord*>(&g_c_handle);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_node_build(void* receiver, OpaqueWord a1, OpaqueWord a2, void* a3,
                      OpaqueWord a4) {
  (void)receiver;
  (void)a1;
  (void)a2;
  (void)a4;
  note("node_build");
  *static_cast<OpaqueWord*>(a3) = g_node_build;
  return reinterpret_cast<OpaqueWord*>(&g_c_node);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_toggle_one(void* a1) {
  (void)a1;
  note("toggle_one");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_toggle(void* a1, OpaqueWord a2) {
  (void)a1;
  note_arg("toggle", a2);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_record(OpaqueBlock32* block, OpaqueWord a1, void* a2, void* a3) {
  (void)a1;
  (void)a2;
  (void)a3;
  note_arg("record", as_word(block));
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_emit(OpaqueEncoder70* receiver, OpaqueWord value) {
  (void)receiver;
  note_arg("emit", value);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_gate_1c(OpaqueGate* self, OpaqueWord a1, void* a2, OpaqueWord a3,
                   void* a4) {
  (void)self;
  (void)a1;
  (void)a2;
  (void)a3;
  (void)a4;
  note_arg("gate_1c", g_slot_1c_flag);
  return g_slot_1c_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_gate_34(OpaqueGate* self, void* a1, void* a2, OpaqueWord a3,
                   OpaqueWord a4, OpaqueWord a5, OpaqueWord a6) {
  (void)self;
  (void)a1;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  note_arg("gate_34", as_word(a2));
  return g_slot_34_flag != 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_owner_00(OpaqueOwner* self) {
  (void)self;
  note("owner_00");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_owner_04(OpaqueOwner* self) {
  (void)self;
  note("owner_04");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_owner_08(OpaqueOwner* self) {
  (void)self;
  note("owner_08");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_owner_18(OpaqueOwner* self, OpaqueWord flag) {
  (void)self;
  (void)flag;
  note("owner_18");
  return 0x00abcdefu;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_owner_24(OpaqueOwner* self) {
  (void)self;
  note("owner_24");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_handle_04(OpaqueHandle* self) {
  (void)self;
  note("handle_04");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_c_handle_08(OpaqueHandle* self) {
  (void)self;
  note("handle_08");
}

void install_c330() {
  g_ports_005fc330 = &g_c330;
  g_c330.push_00931e10 = &stub_c_slot;
  g_c330.state_009317b0 = &stub_c_open;
  g_c330.query_009318f0 = &stub_c_query;
  g_c330.get_0067cb30 = &stub_c_get;
  g_c330.probe_005fbb00 = &stub_c_probe;
  g_c330.reset_005f8050 = &stub_c_reset;
  g_c330.close_005f8e40 = &stub_c_close_raster;
  g_c330.close_00931a70 = &stub_c_close_slot;
  g_c330.close_00931e70 = &stub_c_close_stream;
  g_c330.close_005f8d80 = &stub_c_close_slot;
  g_c330.close_00933960 = &stub_c_close_slot;
  g_c330.global_0067dcd0 = &stub_c_global;
  g_c330.global_0067dcc0 = &stub_c_global;
  g_c330.resolve_0054e460 = &stub_c_resolve;
  g_c330.mark_0054ed50 = &stub_c_mark;
  g_c330.lift_0054e250 = &stub_c_lift;
  g_c330.build_006b1f90 = &stub_c_resource;
  g_c330.side_0067de60 = &stub_c_side_get;
  g_c330.factory_00f473a0 = &stub_c_factory;
  g_c330.node_00926020 = &stub_c_node;
  g_c330.build_00550450 = &stub_c_build_meta;
  g_c330.meta_00551620 = &stub_c_meta;
  g_c330.seal_00551b60 = &stub_c_seal;
  g_c330.flag_00550990 = &stub_c_flag;
  g_c330.drop_00550b00 = &stub_c_drop;
  g_c330.toggle_006ad010 = &stub_c_toggle_one;
  g_c330.toggle_006ac0a0 = &stub_c_toggle;
  g_c330.node_008e2380 = &stub_c_node_build;
  g_c330.record_005f8170 = &stub_c_record;
  g_c330.record_005f8240 = &stub_c_record;
  g_c330.emit_0068e1a0 = &stub_c_emit;
  g_c_factory_vtable = OpaqueFactoryVTable{};
  g_c_factory_vtable.slot_58 = &stub_c_cast;
  g_c_factory.vtable = &g_c_factory_vtable;
  g_c_side_vtable = OpaqueSideVTable{};
  g_c_side_vtable.slot_08 = &stub_c_side;
  g_c_side.vtable = &g_c_side_vtable;
  g_c_gate_vtable = OpaqueGateVTable{};
  g_c_gate_vtable.slot_1c = &stub_c_gate_1c;
  g_c_gate_vtable.slot_34 = &stub_c_gate_34;
  g_c_gate.vtable = &g_c_gate_vtable;
  g_c_global_vtable = OpaqueGlobalVTable{};
  g_c_global_vtable.slot_48 = &stub_c_global_48;
  g_c_global_vtable.slot_20 = &stub_c_global_20;
  g_c_global_vtable.slot_14 = &stub_c_global_14;
  g_c_global.vtable = &g_c_global_vtable;
  g_c_handle_vtable = OpaqueHandleVTable{};
  g_c_handle_vtable.slot_04 = &stub_c_handle_04;
  g_c_handle_vtable.slot_08 = &stub_c_handle_08;
  g_c_handle.vtable = &g_c_handle_vtable;
  g_c_owner_vtable = OpaqueOwnerVTable{};
  g_c_owner_vtable.slot_00 = &stub_c_owner_00;
  g_c_owner_vtable.slot_04 = &stub_c_owner_04;
  g_c_owner_vtable.slot_08 = &stub_c_owner_08;
  g_c_owner_vtable.slot_18 = &stub_c_owner_18;
  g_c_owner_vtable.slot_24 = &stub_c_owner_24;
  g_c_owner.vtable = &g_c_owner_vtable;
  g_c_node_vtable = OpaqueOwnerVTable{};
  g_c_node_vtable.slot_04 = &stub_c_owner_04;
  g_c_node_vtable.slot_08 = &stub_c_owner_08;
  g_c_node_vtable.slot_18 = &stub_c_owner_18;
  g_c_node_vtable.slot_24 = &stub_c_owner_24;
  g_c_node.vtable = &g_c_node_vtable;
  g_c_allocator[22] = as_word(&g_c_factory);
}

void reset_c330() {
  trace.clear();
  g_probe_flag = 1u;
  g_open_flag = 1u;
  g_found = 0u;
  g_resolve_flag = 0u;
  g_cast_flag = 0u;
  g_gate_handle = 0u;
  g_node_build = 0u;
  g_slot_1c_flag = 1u;
  g_slot_20_flag = 1u;
  g_slot_34_flag = 1u;
  g_lifted_key = OpaqueKey12{};
  g_close_raster = 0;
  g_close_stream = 0;
}

void test_005fc330() {
  OpaqueService service{};
  OpaqueWord path[4] = {0x0041u, 0x0000u, 0u, 0u};
  OpaqueKey12 destination{};
  OpaqueWord entries[8] = {0u, 0u, 0u, 0x9001u, 0x9002u, 0x9003u, 0u, 0u};
  OpaqueWord node_pool[8] = {0u};
  g_entries = entries;
  g_node_pool = node_pool;
  install_c330();

  reset_c330();
  destination.w0 = 1u;
  destination.w1 = 2u;
  destination.w2 = 3u;
  g_open_flag = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 rejects a failed open query");
  expect(destination.w0 == 0xffffffffu, "005fc330 clears word zero first");
  expect(destination.w1 == 0xffffffffu, "005fc330 clears word one first");
  expect(destination.w2 == 0xffffffffu, "005fc330 clears word two first");
  expect(g_close_raster == 0, "005fc330 open failure skips the raster close");
  expect(g_close_stream == 1, "005fc330 open failure closes the stream");

  reset_c330();
  g_found = as_word(entries);
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 reports the located entry as a failure");
  expect(destination.w0 == 0x9001u, "005fc330 copies the located head");
  expect(destination.w1 == 0x9002u, "005fc330 copies the located middle");
  expect(destination.w2 == 0x9003u, "005fc330 copies the located tail");
  expect(g_close_raster == 1, "005fc330 closes the raster on a hit");
  expect(count_prefix("factory:") == 0,
         "005fc330 never builds metadata on a hit");
  expect(service.image_0f8.w0 == 0u, "005fc330 keeps the stored key on a hit");

  reset_c330();
  g_resolve_flag = 1u;
  g_cast_flag = 1u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 reports the cast entry as a failure");
  expect(destination.w0 == g_lifted_key.w0, "005fc330 copies the lifted head");
  expect(destination.w1 == g_lifted_key.w1,
         "005fc330 copies the lifted middle");
  expect(destination.w2 == g_lifted_key.w2, "005fc330 copies the lifted tail");
  expect(g_close_raster == 1, "005fc330 closes the raster after a cast");

  reset_c330();
  g_probe_flag = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 skips the payload when the probe fails");
  expect(count("side") == 0, "005fc330 probe failure stops before the side");
  expect(g_close_raster == 1, "005fc330 probe failure closes the raster");
  expect(g_close_stream == 1, "005fc330 probe failure closes the stream");

  service.field_044 = 0x77u;
  reset_c330();
  g_gate_handle = as_word(&g_c_gate);
  g_node_build = as_word(&g_c_node);
  expect(service_005fc330(&service, path, &destination),
         "005fc330 succeeds on the full payload");
  expect(count_prefix("side:") == 1, "005fc330 asks the side once");
  expect(count_prefix("factory:") == 1, "005fc330 allocates the metadata once");
  expect(count_prefix("meta:") == 1, "005fc330 writes the metadata once");
  expect(count("node:0x00000024") == 1, "005fc330 allocates the node once");
  expect(count("node_build") == 1, "005fc330 builds the node once");
  expect(count_prefix("gate_1c:") == 1, "005fc330 opens the gate once");
  expect(count_prefix("global_20:") >= 1,
         "005fc330 commits through the global slot");
  expect(count_prefix("gate_34:") == 1, "005fc330 writes the descriptor once");
  expect(!contains("owner_18"),
         "005fc330 skips the dead owner query after the release");
  expect(contains("owner_08"), "005fc330 releases the node before the emit");
  expect(g_c_node.head == g_lifted_key.w0 || g_c_node.head == 0u,
         "005fc330 writes the resolved head into the node");
  expect(g_c_node.middle == g_lifted_key.w1 || g_c_node.middle == 0u,
         "005fc330 writes the resolved middle into the node");
  expect(g_c_node.tail == g_lifted_key.w2 || g_c_node.tail == 0u,
         "005fc330 writes the resolved tail into the node");
  expect(service.image_0f8.w0 == destination.w0,
         "005fc330 stores the destination head on the service");
  expect(service.image_0f8.w1 == destination.w1,
         "005fc330 stores the destination middle on the service");
  expect(service.image_0f8.w2 == destination.w2,
         "005fc330 stores the destination tail on the service");
  expect(contains("global_14:0x05132ed1"), "005fc330 posts the marshal word");
  expect(contains(label("record", as_word(&service.block_048))),
         "005fc330 records into the first block");
  expect(contains(label("record", as_word(&service.block_068))),
         "005fc330 records into the second block");
  expect(g_close_raster == 1, "005fc330 closes the raster once");
  expect(g_close_stream == 1, "005fc330 closes the stream once");

  reset_c330();
  g_gate_handle = as_word(&g_c_gate);
  g_node_build = as_word(&g_c_node);
  g_slot_1c_flag = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 fails when the gate rejects");
  expect(count_prefix("gate_34:") == 0,
         "005fc330 gate failure skips the descriptor");
  expect(!contains("owner_18"), "005fc330 gate failure skips the owner query");
  expect(contains("owner_08"), "005fc330 releases the node on gate failure");

  reset_c330();
  g_gate_handle = as_word(&g_c_gate);
  g_node_build = as_word(&g_c_node);
  g_slot_20_flag = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 fails when the commit rejects");
  expect(count_prefix("gate_34:") == 0,
         "005fc330 commit failure skips the descriptor");

  reset_c330();
  g_gate_handle = as_word(&g_c_gate);
  g_node_build = as_word(&g_c_node);
  g_slot_34_flag = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 fails when the descriptor rejects");
  expect(!contains("owner_18"),
         "005fc330 descriptor failure skips the owner query");

  reset_c330();
  g_gate_handle = 0u;
  expect(!service_005fc330(&service, path, &destination),
         "005fc330 fails when the gate is absent");
  expect(count_prefix("gate_1c:") == 0,
         "005fc330 absent gate skips the gate open");
  expect(!contains("node:0x00000024"),
         "005fc330 absent gate never allocates the node");
}

OpaqueWord g_owner_pair[2] = {0u, 0u};
OpaqueWord g_owner_allocated = 0u;
OpaqueWord g_owner_node = 0u;
OpaqueWord g_owner_handle = 0u;
OpaqueWord g_owner_drop[2] = {0u, 0u};
OpaqueWord g_owner_place = 0u;
int g_owner_retain = 0;
int g_owner_release_count = 0;
int g_owner_grow = 0;
int g_owner_place_calls = 0;
OpaqueOwnerVTable g_e_owner_vtable{};
OpaqueOwner60ee90 g_e_owner{};
Ports0060ee90 g_e90{};

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_global() {
  note("global");
  return reinterpret_cast<OpaqueWord*>(&g_e_owner);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_global_0c(void* self, void* first, void* second, OpaqueWord a3,
                     OpaqueWord a4, OpaqueWord a5, OpaqueWord a6) {
  (void)self;
  (void)first;
  (void)second;
  (void)a3;
  (void)a4;
  (void)a5;
  (void)a6;
  note("global_0c");
  return true;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueBool
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_global_20(void* self, OpaqueWord a1, OpaqueWord a2, OpaqueWord a3) {
  (void)self;
  (void)a1;
  (void)a2;
  (void)a3;
  note("global_20");
  return true;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_global_6c(void* self, OpaqueWord a1, OpaqueWord a2) {
  (void)self;
  (void)a1;
  (void)a2;
  note("global_6c");
  return 0u;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_probe(void* self) {
  (void)self;
  note("probe");
  return g_owner_pair;
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_drop(void* self, OpaqueWord a1, OpaqueWord a2) {
  (void)self;
  g_owner_drop[0] = a1;
  g_owner_drop[1] = a2;
  note("drop");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_owner(void* key) {
  (void)key;
  note("owner");
  return reinterpret_cast<OpaqueWord*>(&g_e_owner);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_compose(void* self) {
  (void)self;
  note("compose");
  return reinterpret_cast<OpaqueWord*>(&g_e_owner);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_CDECL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_factory(OpaqueWord size) {
  note_arg("factory", size);
  return reinterpret_cast<OpaqueWord*>(g_owner_allocated);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL OpaqueWord*
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_build(void* self, OpaqueWord a1, OpaqueWord a2, OpaqueWord a3,
                 OpaqueWord a4, OpaqueWord a5) {
  (void)self;
  (void)a2;
  (void)a3;
  (void)a4;
  (void)a5;
  g_owner_handle = a1;
  note_arg("build", g_owner_node);
  return reinterpret_cast<OpaqueWord*>(g_owner_node);
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_grow(void* self, void* value) {
  (void)self;
  (void)value;
  ++g_owner_grow;
  note("grow");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_place(OpaqueOwner60ee90* self, void* key) {
  (void)self;
  g_owner_place = as_word(key);
  ++g_owner_place_calls;
  note("place");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_slot_04(OpaqueOwner* self) {
  (void)self;
  ++g_owner_retain;
  note("slot_04");
}

PKG_APP_SERVICES_SAFE_WAVE11_T_THISCALL void
    PKG_APP_SERVICES_SAFE_WAVE11_T_NOINLINE
    stub_e_slot_08(OpaqueOwner* self) {
  (void)self;
  ++g_owner_release_count;
  note("slot_08");
}

void reset_e90() {
  trace.clear();
  g_owner_pair[0] = 0u;
  g_owner_pair[1] = 0u;
  g_owner_drop[0] = 0u;
  g_owner_drop[1] = 0u;
  g_owner_place = 0u;
  g_owner_retain = 0;
  g_owner_release_count = 0;
  g_owner_grow = 0;
  g_owner_place_calls = 0;
  g_owner_allocated = as_word(&g_e_owner);
  g_owner_node = as_word(&g_e_owner);
  g_owner_handle = 0u;
}

void test_0060ee90() {
  OpaqueWord storage[16] = {0u};
  OpaqueWord key[3] = {0x01020304u, 0u, 0x05060708u};
  g_ports_0060ee90 = &g_e90;
  g_e90.global_0067dcd0 = &stub_e_global;
  g_e90.global_0c = &stub_e_global_0c;
  g_e90.global_20 = &stub_e_global_20;
  g_e90.global_6c = &stub_e_global_6c;
  g_e90.probe_005507a0 = &stub_e_probe;
  g_e90.drop_00551af0 = &stub_e_drop;
  g_e90.owner_005f7930 = &stub_e_owner;
  g_e90.compose_005fb430 = &stub_e_compose;
  g_e90.factory_00615810 = &stub_e_factory;
  g_e90.build_00615d30 = &stub_e_build;
  g_e90.grow_0060db40 = &stub_e_grow;
  g_e90.place_0060cf30 = &stub_e_place;
  g_e_owner_vtable = OpaqueOwnerVTable{};
  g_e_owner_vtable.slot_04 = &stub_e_slot_04;
  g_e_owner_vtable.slot_08 = &stub_e_slot_08;
  g_e_owner.vtable_000 = &g_e_owner_vtable;
  g_e_owner.base_008 = storage;
  g_e_owner.base_00c = storage + 4;
  g_e_owner.end_010 = storage + 4;
  g_e_owner.capacity_014 = storage + 8;

  reset_e90();
  g_e_owner.slot_060 = 0x1111u;
  g_e_owner.slot_064 = 0x2222u;
  g_e_owner.tag_058 = 0x3333u;
  service_0060ee90(&g_e_owner, key, nullptr, nullptr);
  expect(g_e_owner.slot_060 == 0xffffffffu, "0060ee90 resets the first slot");
  expect(g_e_owner.slot_064 == 0xffffffffu, "0060ee90 resets the second slot");
  expect(contains("factory:0x00000030"), "0060ee90 allocates thirty bytes");
  expect(g_owner_retain == 2, "0060ee90 balances the retain on the node");
  expect(g_owner_release_count == 1, "0060ee90 releases the node once");
  expect(g_owner_grow == 0,
         "0060ee90 pushes without growing when there is room");
  expect(storage[3] == g_owner_node, "0060ee90 pushes the node handle");
  expect(g_e_owner.end_010 == storage + 3, "0060ee90 decrements the end slot");
  expect(g_owner_place_calls == 1, "0060ee90 places exactly once");
  expect(g_owner_place == as_word(key), "0060ee90 forwards the key pointer");
  expect(index_of(std::string("place")) > index_of_prefix("build:"),
         "0060ee90 places after the node is built");
  expect(index_of(std::string("place")) > index_of(std::string("slot_08")),
         "0060ee90 places after the node is released");
  expect(!contains("handle_04"),
         "0060ee90 never releases the zeroed pending slot");
  expect(!contains("drop"),
         "0060ee90 keeps a resolvable handle out of the erase path");

  reset_e90();
  g_owner_pair[0] = 0xffffffffu;
  g_owner_pair[1] = 0xffffffffu;
  g_e_owner.slot_060 = 0x1111u;
  g_e_owner.slot_064 = 0x2222u;
  service_0060ee90(&g_e_owner, key, nullptr, nullptr);
  expect(contains("drop"), "0060ee90 erases an unresolvable handle");
  expect(g_owner_drop[0] == 0x1111u, "0060ee90 erase reads the first slot");
  expect(g_owner_drop[1] == 0x2222u, "0060ee90 erase reads the second slot");
  expect(contains("owner"), "0060ee90 rebuilds the owner after the erase");
  expect(index_of(std::string("owner")) < index_of(std::string("factory")),
         "0060ee90 rebuilds before allocating the node");

  reset_e90();
  g_e_owner.end_010 = g_e_owner.capacity_014;
  service_0060ee90(&g_e_owner, key, nullptr, nullptr);
  expect(g_owner_grow == 1, "0060ee90 grows when the vector is full");
  expect(g_owner_release_count == 1, "0060ee90 releases the node after a grow");
  expect(index_of(std::string("grow")) < index_of(std::string("slot_08")),
         "0060ee90 grows before releasing the node");

  reset_e90();
  g_owner_allocated = 0u;
  service_0060ee90(&g_e_owner, key, nullptr, nullptr);
  expect(g_owner_retain == 0, "0060ee90 skips a failed allocation");
  expect(g_owner_release_count == 0, "0060ee90 skips the release too");
  expect(!contains("build"), "0060ee90 skips the node build");
  expect(!contains("grow"), "0060ee90 skips the vector push");
  expect(g_owner_place_calls == 1, "0060ee90 still places the key");
}

}  // namespace

int main() {
  test_005f9230_dispatch();
  test_005f9310();
  test_005fa8d0();
  test_005fc330();
  test_0060ee90();
  std::printf("pkg-app-services-safe-wave11 model: checks=%d failures=%d\n",
              checks, failures);
  return failures == 0 ? 0 : 1;
}
