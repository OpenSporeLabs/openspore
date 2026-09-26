#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <type_traits>
#include <vector>

#include "skinner_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __thiscall
#define PKG_SKINNER_SAFE_WAVE10_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_SKINNER_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#define PKG_SKINNER_SAFE_WAVE10_CDECL __attribute__((cdecl))
#else
#error "PKG-SKINNER-SAFE-WAVE10 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_skinner_safe_wave10 {

struct alignas(4) OpaqueLayerFactory {
  std::uint32_t word00;
};

struct alignas(4) OpaqueTexturePainter {
  std::uint32_t word00;
};

namespace {

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    ++g_failures;
    std::printf("FAIL %s\n", what);
  }
}

constexpr std::size_t kTraceLimit = 64;
constexpr std::size_t kStepScriptLimit = 16;
constexpr std::uint8_t kByteFill = 0xa5u;

enum class EventKind : std::uint8_t {
  kAcquire,
  kCreate,
  kQuery,
  kStep,
};

struct Event {
  EventKind kind;
  std::uint32_t slot;
  std::uint32_t arg0;
  std::uint32_t arg1;
  std::uint32_t arg2;
  std::uint32_t arg3;
  std::uint32_t arg4;
  std::uint32_t arg5;
  std::uint32_t receiver;
  std::uint32_t result;
};

struct Trace {
  std::vector<Event> events;
  std::uint32_t acquire_calls;
  std::uint32_t create_calls;
  std::uint32_t query_calls;
  std::uint32_t step_calls;
  std::uint32_t probe_calls;
  std::uint32_t fault_calls;
  std::uint32_t acquire_tag;
  std::uint32_t acquire_name;
  std::uint32_t acquire_zero_tail;
  std::uint32_t create_arg0;
  std::uint32_t create_arg1;
  std::uint32_t query_receiver;
  std::uint32_t step_receiver;
  std::uint32_t create_result_base;
  std::uint8_t acquire_null_bits;
  std::uint8_t query_result;
  bool probe_null;
  std::int32_t step_script[kStepScriptLimit];
  std::size_t step_script_length;
  std::size_t step_set_pass_index;
  std::int32_t step_set_pass;
  OpaqueSkinPainterState* observed_state;
  std::uint32_t observed_slot_010;
  std::uint32_t observed_slot_014;
  std::uint32_t observed_slot_018;

  void reset() {
    events.clear();
    acquire_calls = 0;
    create_calls = 0;
    query_calls = 0;
    step_calls = 0;
    probe_calls = 0;
    fault_calls = 0;
    acquire_tag = 0;
    acquire_name = 0;
    acquire_zero_tail = 0;
    create_arg0 = 0;
    create_arg1 = 0;
    query_receiver = 0;
    step_receiver = 0;
    create_result_base = 0x1000;
    acquire_null_bits = 0;
    query_result = 0;
    probe_null = false;
    step_script_length = 0;
    step_set_pass_index = kStepScriptLimit;
    step_set_pass = 0;
    observed_state = nullptr;
    observed_slot_010 = 0;
    observed_slot_014 = 0;
    observed_slot_018 = 0;
  }
};

Trace g_trace;

OpaqueLayerFactory g_factory_pool[4];
OpaqueTexturePainter g_painter_pool[4];

std::uint8_t g_vtable_bytes[0x48];

std::uint32_t as_word(const void* pointer) {
  std::uint32_t value = 0;
  std::memcpy(&value, pointer, sizeof(value));
  return value;
}

void set_word(void* pointer, std::uint32_t value) {
  std::memcpy(pointer, &value, sizeof(value));
}

std::uint32_t ptr_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

std::uint32_t painter_word(std::size_t index) {
  return ptr_word(&g_painter_pool[index]);
}

template <typename Fn>
std::uint32_t fn_word(Fn pointer) {
  static_assert(sizeof(Fn) == 4, "target function pointers are 32-bit");
  std::uint32_t value = 0;
  std::memcpy(&value, &pointer, sizeof(value));
  return value;
}

void record(EventKind kind, std::uint32_t slot, std::uint32_t arg0,
            std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3,
            std::uint32_t arg4, std::uint32_t arg5, std::uint32_t receiver,
            std::uint32_t result) {
  if (g_trace.events.size() >= kTraceLimit) {
    return;
  }
  Event event;
  event.kind = kind;
  event.slot = slot;
  event.arg0 = arg0;
  event.arg1 = arg1;
  event.arg2 = arg2;
  event.arg3 = arg3;
  event.arg4 = arg4;
  event.arg5 = arg5;
  event.receiver = receiver;
  event.result = result;
  g_trace.events.push_back(event);
}

std::uint8_t PKG_SKINNER_SAFE_WAVE10_THISCALL query_thunk(void* self) {
  ++g_trace.query_calls;
  g_trace.query_receiver = ptr_word(self);
  record(EventKind::kQuery, 0, 0, 0, 0, 0, 0, 0, ptr_word(self),
         g_trace.query_result);
  return g_trace.query_result;
}

std::uint8_t PKG_SKINNER_SAFE_WAVE10_THISCALL fault_thunk(void* self) {
  ++g_trace.fault_calls;
  return ptr_word(self) == 0u ? 1u : 0u;
}

struct Harness {
  OpaqueGraphicsProbeVTable probe_vtable;
  OpaqueGraphicsProbe probe;
  OpaquePainterJob job;
  OpaqueSkinPainterState state;
  std::uint8_t guard_038[8];
  std::uint32_t canary_010;
  std::uint32_t canary_020;

  void reset() {
    std::memset(&probe_vtable, 0, sizeof(probe_vtable));
    std::memset(&probe, 0, sizeof(probe));
    std::memset(&job, 0, sizeof(job));
    std::memset(&state, 0, sizeof(state));
    std::memset(guard_038, kByteFill, sizeof(guard_038));
    canary_010 = 0x12345678u;
    canary_020 = 0x9abcdef0u;
    probe_vtable.query_044 = &query_thunk;
    probe.vtable_000 = &probe_vtable;
    g_trace.probe_null = false;
  }
};

Harness g_harness;

void install_raw_vtable() {
  std::memset(g_vtable_bytes, 0xcc, sizeof(g_vtable_bytes));
  const std::uint32_t fault = fn_word(&fault_thunk);
  const std::uint32_t query = fn_word(&query_thunk);
  std::memcpy(g_vtable_bytes + 0x40, &fault, sizeof(fault));
  std::memcpy(g_vtable_bytes + 0x44, &query, sizeof(query));
  g_harness.probe.vtable_000 =
      reinterpret_cast<OpaqueGraphicsProbeVTable*>(g_vtable_bytes);
}

}

extern "C" OpaqueLayerFactory* PKG_SKINNER_SAFE_WAVE10_CDECL
unresolved_00f473a0(std::uint32_t tag, std::uint32_t name, std::uint32_t zero3,
                    std::uint32_t zero4, std::uint32_t zero5,
                    std::uint32_t zero6) {
  const std::uint32_t index = g_trace.acquire_calls;
  ++g_trace.acquire_calls;
  g_trace.acquire_tag = tag;
  g_trace.acquire_name = name;
  g_trace.acquire_zero_tail = zero3 | zero4 | zero5 | zero6;
  record(EventKind::kAcquire, index, tag, name, zero3, zero4, zero5, zero6, 0,
         g_trace.acquire_null_bits);
  if ((g_trace.acquire_null_bits & (1u << index)) != 0u) {
    return nullptr;
  }
  if (index >= 4u) {
    return nullptr;
  }
  return &g_factory_pool[index];
}

extern "C" OpaqueTexturePainter* PKG_SKINNER_SAFE_WAVE10_THISCALL
unresolved_005288f0(OpaqueLayerFactory* factory, std::uint32_t arg0,
                    std::uint32_t arg1) {
  const std::uint32_t index = g_trace.create_calls;
  ++g_trace.create_calls;
  g_trace.create_arg0 = arg0;
  g_trace.create_arg1 = arg1;
  record(EventKind::kCreate, index, ptr_word(factory), arg0, arg1, 0, 0, 0,
         ptr_word(factory), g_trace.create_result_base + index);
  if (g_trace.observed_state != nullptr) {
    if (index == 1u) {
      g_trace.observed_slot_010 =
          as_word(&g_trace.observed_state->texture_painter_010);
    } else if (index == 2u) {
      g_trace.observed_slot_014 =
          as_word(&g_trace.observed_state->texture_painter_014);
    } else if (index == 3u) {
      g_trace.observed_slot_018 =
          as_word(&g_trace.observed_state->texture_painter_018);
    }
  }
  if (index >= 4u) {
    return nullptr;
  }
  return &g_painter_pool[index];
}

extern "C" OpaqueGraphicsProbe* PKG_SKINNER_SAFE_WAVE10_CDECL
unresolved_0067dd00() {
  ++g_trace.probe_calls;
  if (g_trace.probe_null) {
    return nullptr;
  }
  return &g_harness.probe;
}

extern "C" std::uint32_t PKG_SKINNER_SAFE_WAVE10_THISCALL
unresolved_00517430(OpaquePainterJob* job) {
  const std::uint32_t index = g_trace.step_calls;
  ++g_trace.step_calls;
  g_trace.step_receiver = ptr_word(job);
  std::uint32_t result = 0;
  if (index < g_trace.step_script_length) {
    result = static_cast<std::uint32_t>(g_trace.step_script[index]);
  }
  if (index == g_trace.step_set_pass_index && job != nullptr) {
    job->pass_014 = g_trace.step_set_pass;
  }
  record(EventKind::kStep, index, 0, 0, 0, 0, 0, 0, ptr_word(job), result);
  return result;
}

namespace {

void set_steps(std::initializer_list<std::int32_t> steps) {
  g_trace.step_script_length = 0;
  for (std::int32_t step : steps) {
    if (g_trace.step_script_length >= kStepScriptLimit) {
      break;
    }
    g_trace.step_script[g_trace.step_script_length] = step;
    ++g_trace.step_script_length;
  }
}

void set_steps_filling(std::size_t count, std::int32_t value) {
  g_trace.step_script_length = 0;
  for (std::size_t index = 0; index < count; ++index) {
    if (g_trace.step_script_length >= kStepScriptLimit) {
      break;
    }
    g_trace.step_script[g_trace.step_script_length] = value;
    ++g_trace.step_script_length;
  }
}

void paint_canaries() {
  set_word(&g_harness.state.texture_painter_010, g_harness.canary_010);
  set_word(&g_harness.state.texture_painter_014, g_harness.canary_010);
  set_word(&g_harness.state.texture_painter_018, g_harness.canary_010);
  set_word(&g_harness.state.source_01c, g_harness.canary_010);
  std::memset(&g_harness.state.scale_020, 0, sizeof(float) * 5u);
  std::memset(g_harness.guard_038, kByteFill, sizeof(g_harness.guard_038));
  set_word(&g_harness.state.opaque_000[0], g_harness.canary_020);
  set_word(&g_harness.state.secondary_00c, g_harness.canary_020);
  g_trace.observed_state = nullptr;
  g_trace.observed_slot_010 = 0;
  g_trace.observed_slot_014 = 0;
  g_trace.observed_slot_018 = 0;
}

bool head_untouched() {
  for (std::size_t index = 0; index < sizeof(g_harness.guard_038); ++index) {
    if (g_harness.guard_038[index] != kByteFill) {
      return false;
    }
  }
  if (as_word(&g_harness.state.opaque_000[0]) != g_harness.canary_020) {
    return false;
  }
  return as_word(&g_harness.state.secondary_00c) == g_harness.canary_020;
}

void reset_brush() {
  std::memset(&g_harness.job, 0, sizeof(g_harness.job));
  set_word(&g_harness.job.opaque_000[0], g_harness.canary_010);
  set_word(&g_harness.job.opaque_000[4], g_harness.canary_010);
  set_word(&g_harness.job.opaque_000[8], g_harness.canary_010);
  set_word(&g_harness.job.opaque_000[12], g_harness.canary_010);
  set_word(&g_harness.job.opaque_018[0], g_harness.canary_010);
  set_word(&g_harness.job.opaque_018[4], g_harness.canary_010);
  set_word(&g_harness.job.opaque_018[8], g_harness.canary_010);
  set_word(&g_harness.job.opaque_018[12], g_harness.canary_010);
}

bool brush_fields_untouched() {
  return as_word(&g_harness.job.opaque_000[0]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_000[4]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_000[8]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_000[12]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_018[0]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_018[4]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_018[8]) == g_harness.canary_010 &&
         as_word(&g_harness.job.opaque_018[12]) == g_harness.canary_010;
}

void test_setup_acquire_constants() {
  check(kAcquireTag == 0x00000064u, "setup_acquire_constants_tag");
  check(kAcquireName == 0x013f116cu, "setup_acquire_constants_name");
  check(kAcquireZero3 == 0u && kAcquireZero4 == 0u && kAcquireZero5 == 0u &&
            kAcquireZero6 == 0u,
        "setup_acquire_constants_zero_tail");
}

void test_setup_acquire_arguments() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 0x11223344u);
  check(g_trace.acquire_calls == 3u, "setup_acquire_arguments_call_count");
  check(g_trace.acquire_tag == 0x00000064u, "setup_acquire_arguments_tag");
  check(g_trace.acquire_name == 0x013f116cu, "setup_acquire_arguments_name");
  check(g_trace.acquire_zero_tail == 0u, "setup_acquire_arguments_zero_tail");
  check(g_trace.events.size() == 6u, "setup_acquire_arguments_event_count");
  const EventKind order[6] = {EventKind::kAcquire, EventKind::kCreate,
                              EventKind::kAcquire, EventKind::kCreate,
                              EventKind::kAcquire, EventKind::kCreate};
  for (std::size_t index = 0; index < 6u; ++index) {
    if (g_trace.events[index].kind != order[index]) {
      check(false, "setup_acquire_arguments_call_order");
      return;
    }
  }
  check(true, "setup_acquire_arguments_call_order");
}

void test_setup_create_arguments() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 0x0badc0deu);
  check(g_trace.create_calls == 3u, "setup_create_arguments_call_count");
  check(
      g_trace.create_arg0 == 0x0badc0deu && g_trace.create_arg1 == 0x0badc0deu,
      "setup_create_arguments_source_passed_twice");
}

void test_setup_create_factory_identity() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 1u);
  check(g_trace.events[1].receiver == ptr_word(&g_factory_pool[0]),
        "setup_create_factory_identity_first");
  check(g_trace.events[3].receiver == ptr_word(&g_factory_pool[1]),
        "setup_create_factory_identity_second");
  check(g_trace.events[5].receiver == ptr_word(&g_factory_pool[2]),
        "setup_create_factory_identity_third");
}

void test_setup_painter_slots() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 7u);
  check(as_word(&g_harness.state.texture_painter_010) == painter_word(0),
        "setup_painter_slots_first");
  check(as_word(&g_harness.state.texture_painter_014) == painter_word(1),
        "setup_painter_slots_second");
  check(as_word(&g_harness.state.texture_painter_018) == painter_word(2),
        "setup_painter_slots_third");
}

void test_setup_source_field() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 0xfedcba98u);
  check(g_harness.state.source_01c == 0xfedcba98u, "setup_source_field_value");
}

void test_setup_store_interleaves() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  g_trace.observed_state = &g_harness.state;
  skin_painter_state_setup_00506590(&g_harness.state, 5u);
  check(g_trace.observed_slot_010 == painter_word(0),
        "setup_store_interleaves_first_slot_stored_before_second_acquire");
  check(g_trace.observed_slot_014 == painter_word(1),
        "setup_store_interleaves_second_slot_stored_before_third_acquire");
  check(as_word(&g_harness.state.texture_painter_018) == painter_word(2),
        "setup_store_interleaves_third_slot_stored");
}

void test_setup_null_factory_clears_slots() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  g_trace.acquire_null_bits = 0x07u;
  skin_painter_state_setup_00506590(&g_harness.state, 3u);
  check(g_trace.acquire_calls == 3u, "setup_null_factory_acquire_count");
  check(g_trace.create_calls == 0u, "setup_null_factory_create_skipped");
  check(g_harness.state.texture_painter_010 == nullptr,
        "setup_null_factory_first_slot");
  check(g_harness.state.texture_painter_014 == nullptr,
        "setup_null_factory_second_slot");
  check(g_harness.state.texture_painter_018 == nullptr,
        "setup_null_factory_third_slot");
  check(g_harness.state.source_01c == 3u,
        "setup_null_factory_source_still_written");
}

void test_setup_partial_factory_results() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  g_trace.acquire_null_bits = 0x01u;
  skin_painter_state_setup_00506590(&g_harness.state, 4u);
  check(g_harness.state.texture_painter_010 == nullptr,
        "setup_partial_factory_first_slot_null");
  check(as_word(&g_harness.state.texture_painter_014) == painter_word(0),
        "setup_partial_factory_second_slot_created");
  check(as_word(&g_harness.state.texture_painter_018) == painter_word(1),
        "setup_partial_factory_third_slot_created");
  check(g_trace.create_calls == 2u, "setup_partial_factory_create_count");
}

void test_setup_scale_field_mapping() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  g_float_01471064 = 0.125F;
  g_float_01485720 = 0.25F;
  g_float_013eecd8 = 0.5F;
  skin_painter_state_setup_00506590(&g_harness.state, 0u);
  check(as_word(&g_harness.state.scale_020) == 0x3e000000u,
        "setup_scale_field_mapping_020");
  check(as_word(&g_harness.state.scale_024) == 0x3e800000u,
        "setup_scale_field_mapping_024");
  check(as_word(&g_harness.state.scale_028) == 0x3f000000u,
        "setup_scale_field_mapping_028");
  check(as_word(&g_harness.state.scale_02c) == 0x3e800000u,
        "setup_scale_field_mapping_02c");
  check(as_word(&g_harness.state.scale_030) == 0x3e800000u,
        "setup_scale_field_mapping_030");
  g_float_01471064 = 0.5F;
  g_float_01485720 = 1.0F;
  g_float_013eecd8 = 20.0F;
}

void test_setup_scale_defaults() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 0u);
  check(as_word(&g_harness.state.scale_020) == 0x3f000000u,
        "setup_scale_defaults_020");
  check(as_word(&g_harness.state.scale_024) == 0x3f800000u,
        "setup_scale_defaults_024");
  check(as_word(&g_harness.state.scale_028) == 0x41a00000u,
        "setup_scale_defaults_028");
  check(as_word(&g_harness.state.scale_02c) == 0x3f800000u,
        "setup_scale_defaults_02c");
  check(as_word(&g_harness.state.scale_030) == 0x3f800000u,
        "setup_scale_defaults_030");
}

void test_setup_scale_bit_exact() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  const std::uint32_t negative_zero = 0x80000000u;
  const std::uint32_t denormal = 0x00000001u;
  const std::uint32_t quiet_nan = 0x7fc00000u;
  g_float_01471064 = 0.0F;
  g_float_01485720 = 0.0F;
  g_float_013eecd8 = 0.0F;
  set_word(&g_float_01471064, negative_zero);
  set_word(&g_float_01485720, denormal);
  set_word(&g_float_013eecd8, quiet_nan);
  skin_painter_state_setup_00506590(&g_harness.state, 0u);
  check(as_word(&g_harness.state.scale_020) == negative_zero,
        "setup_scale_bit_exact_020");
  check(as_word(&g_harness.state.scale_024) == denormal,
        "setup_scale_bit_exact_024");
  check(as_word(&g_harness.state.scale_028) == quiet_nan,
        "setup_scale_bit_exact_028");
  check(as_word(&g_harness.state.scale_02c) == denormal,
        "setup_scale_bit_exact_02c");
  check(as_word(&g_harness.state.scale_030) == denormal,
        "setup_scale_bit_exact_030");
  g_float_01471064 = 0.5F;
  g_float_01485720 = 1.0F;
  g_float_013eecd8 = 20.0F;
}

void test_setup_global_address_constants() {
  check(kScaleSlot020 == 0x01471064u, "setup_global_address_020");
  check(kScaleSlot024 == 0x01485720u, "setup_global_address_024");
  check(kScaleSlot028 == 0x013eecd8u, "setup_global_address_028");
  check(kScaleSlot02c == 0x01485720u, "setup_global_address_02c");
  check(kScaleSlot030 == 0x01485720u, "setup_global_address_030");
  check(kProbeQuerySlotIndex == 17u, "setup_global_address_probe_slot");
}

void test_setup_leaves_head_untouched() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 0u);
  check(head_untouched(), "setup_leaves_head_untouched");
}

void test_setup_repeated_calls_are_fresh() {
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 1u);
  const std::uint32_t first = as_word(&g_harness.state.texture_painter_010);
  g_trace.reset();
  g_harness.reset();
  paint_canaries();
  skin_painter_state_setup_00506590(&g_harness.state, 1u);
  check(g_trace.acquire_calls == 3u, "setup_repeated_calls_acquire_count");
  check(as_word(&g_harness.state.texture_painter_010) == first,
        "setup_repeated_calls_are_fresh");
}

void test_signatures() {
  static_assert(sizeof(std::uint32_t) == 4, "signature_word_width");
  static_assert(
      std::is_same<decltype(&skin_painter_state_setup_00506590),
                   void(PKG_SKINNER_SAFE_WAVE10_THISCALL*)(
                       OpaqueSkinPainterState*, std::uint32_t)>::value,
      "signature_setup_prototype");
  static_assert(std::is_same<decltype(&skin_painter_job_brush_pass_005182f0),
                             std::uint32_t(PKG_SKINNER_SAFE_WAVE10_THISCALL*)(
                                 OpaquePainterJob*)>::value,
                "signature_brush_pass_prototype");
  static_assert(
      std::is_same<decltype(&unresolved_00f473a0), AcquireLayerFactory>::value,
      "signature_acquire_port");
  static_assert(
      std::is_same<decltype(&unresolved_005288f0), CreateTexturePainter>::value,
      "signature_create_port");
  static_assert(
      std::is_same<decltype(&unresolved_0067dd00), GetGraphicsProbe>::value,
      "signature_probe_port");
  static_assert(
      std::is_same<decltype(&unresolved_00517430), AdvancePainterJob>::value,
      "signature_advance_port");
  static_assert(std::is_same<decltype(&query_thunk), GraphicsQuerySlot>::value,
                "signature_probe_slot");
  static_assert(std::is_same<decltype(&fault_thunk), GraphicsQuerySlot>::value,
                "signature_probe_slot_tripwire");
  check(kProbeQuerySlotIndex == 17u, "signature_probe_slot_index");
  check(sizeof(GraphicsQuerySlot) == 4, "signature_probe_slot_width");
  check(sizeof(AcquireLayerFactory) == 4, "signature_acquire_width");
  check(sizeof(AdvancePainterJob) == 4, "signature_advance_width");
}

void test_brush_probe_fetched_once() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 1u;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_probe_fetched_once_result");
  check(g_trace.probe_calls == 1u, "brush_probe_fetched_once_probe_calls");
  check(g_trace.query_calls == 1u, "brush_probe_fetched_once_query_calls");
  check(g_trace.query_receiver == ptr_word(&g_harness.probe),
        "brush_probe_fetched_once_query_receiver");
  check(g_trace.step_receiver == ptr_word(&g_harness.job),
        "brush_probe_fetched_once_step_receiver");
}

void test_brush_only_query_slot_is_called() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  install_raw_vtable();
  g_trace.query_result = 1u;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_only_query_slot_is_called_result");
  check(g_trace.fault_calls == 0u, "brush_only_query_slot_is_called_tripwire");
  check(g_trace.query_calls == 1u, "brush_only_query_slot_is_called_single");
  check(g_vtable_bytes[0x3f] == 0xccu,
        "brush_only_query_slot_is_called_untouched");
  g_harness.probe.vtable_000 = &g_harness.probe_vtable;
}

void test_brush_query_true_first_step_completes() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 1u;
  set_steps({0, 0, 1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_true_first_step_completes_result");
  check(g_trace.step_calls == 3u,
        "brush_query_true_first_step_completes_calls");
}

void test_brush_query_true_attempt_limit() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 1u;
  set_steps({});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(kAttemptLimit == 12, "brush_query_true_attempt_limit_constant");
  check(result == 0u, "brush_query_true_attempt_limit_result");
  check(g_trace.step_calls == 12u, "brush_query_true_attempt_limit_call_count");
}

void test_brush_query_true_guard_rereads_pass() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 1u;
  set_steps_filling(kStepScriptLimit, 0);
  g_trace.step_script[kStepScriptLimit - 1u] = 1;
  g_trace.step_set_pass_index = 0;
  g_trace.step_set_pass = 1;
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_true_guard_rereads_pass_result");
  check(g_trace.step_calls == 16u, "brush_query_true_guard_rereads_pass_calls");
  check(g_harness.job.pass_014 == 1,
        "brush_query_true_guard_rereads_pass_value");
}

void test_brush_query_true_pass_nonzero_never_aborts() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 1u;
  g_harness.job.pass_014 = 1;
  set_steps_filling(13, 0);
  g_trace.step_script[12] = 1;
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_true_pass_nonzero_never_aborts_result");
  check(g_trace.step_calls == 13u,
        "brush_query_true_pass_nonzero_never_aborts_calls");
}

void test_brush_query_false_pass_zero() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_false_pass_zero_result");
  check(g_trace.step_calls == 1u, "brush_query_false_pass_zero_call_count");
}

void test_brush_query_false_pass_zero_falls_through() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  set_steps({0, static_cast<std::int32_t>(0x1234abcdu)});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 0x1234abcdu,
        "brush_query_false_pass_zero_falls_through_result");
  check(g_trace.step_calls == 2u,
        "brush_query_false_pass_zero_falls_through_call_count");
}

void test_brush_query_false_pass_two() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  g_harness.job.pass_014 = 2;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_false_pass_two_result");
  check(g_trace.step_calls == 1u, "brush_query_false_pass_two_call_count");
}

void test_brush_query_false_pass_three() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  g_harness.job.pass_014 = 3;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_false_pass_three_result");
  check(g_trace.step_calls == 1u, "brush_query_false_pass_three_call_count");
}

void test_brush_query_false_other_pass() {
  const std::int32_t passes[6] = {1, 4, 5, -1, -2147483647 - 1, 2147483647};
  for (std::int32_t pass : passes) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 0u;
    g_harness.job.pass_014 = pass;
    set_steps({1});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == 1u, "brush_query_false_other_pass_raw_result");
    check(g_trace.step_calls == 1u, "brush_query_false_other_pass_call_count");
  }
}

void test_brush_query_false_pass_two_zero_step() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  g_harness.job.pass_014 = 2;
  set_steps({0, 0x00000055});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 0x00000055u, "brush_query_false_pass_two_zero_step_result");
  check(g_trace.step_calls == 2u, "brush_query_false_pass_two_zero_step_calls");
}

void test_brush_low_byte_truthiness() {
  const std::uint32_t not_done[3] = {0x00000100u, 0x0000ab00u, 0xff000000u};
  for (std::uint32_t word : not_done) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 0u;
    set_steps(
        {static_cast<std::int32_t>(word), static_cast<std::int32_t>(word)});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == word, "brush_low_byte_truthiness_not_done");
    check(g_trace.step_calls == 2u, "brush_low_byte_truthiness_not_done_calls");
  }

  const std::uint32_t done[3] = {0x00000001u, 0x000000ffu, 0x0000ab01u};
  for (std::uint32_t word : done) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 0u;
    set_steps({static_cast<std::int32_t>(word)});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == 1u, "brush_low_byte_truthiness_done");
    check(g_trace.step_calls == 1u, "brush_low_byte_truthiness_done_calls");
  }
}

void test_brush_query_true_low_byte_truthiness() {
  const std::uint32_t not_done[3] = {0x00000100u, 0xff00ab00u, 0x0000ab00u};
  for (std::uint32_t word : not_done) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 1u;
    set_steps({static_cast<std::int32_t>(word)});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == 0u, "brush_query_true_low_byte_truthiness_not_done");
    check(g_trace.step_calls == 12u,
          "brush_query_true_low_byte_truthiness_not_done_calls");
  }

  const std::uint32_t done[2] = {0x00000001u, 0x0000ab01u};
  for (std::uint32_t word : done) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 1u;
    set_steps({static_cast<std::int32_t>(word)});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == 1u, "brush_query_true_low_byte_truthiness_done");
    check(g_trace.step_calls == 1u,
          "brush_query_true_low_byte_truthiness_done_calls");
  }
}

void test_brush_return_width_is_32_bit() {
  const std::uint32_t words[3] = {0x80000001u, 0xdeadbeefu, 0x00010001u};
  for (std::uint32_t word : words) {
    g_trace.reset();
    g_harness.reset();
    reset_brush();
    g_trace.query_result = 0u;
    g_harness.job.pass_014 = 7;
    set_steps({static_cast<std::int32_t>(word)});
    const std::uint32_t result =
        skin_painter_job_brush_pass_005182f0(&g_harness.job);
    check(result == word, "brush_return_width_is_32_bit");
  }
}

void test_brush_query_nonzero_low_byte_only() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0x80u;
  set_steps({1});
  const std::uint32_t result =
      skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(result == 1u, "brush_query_nonzero_low_byte_only_result");
  check(g_trace.step_calls == 1u, "brush_query_nonzero_low_byte_only_calls");
}

void test_brush_leaves_other_fields_untouched() {
  g_trace.reset();
  g_harness.reset();
  reset_brush();
  g_trace.query_result = 0u;
  set_steps({1});
  skin_painter_job_brush_pass_005182f0(&g_harness.job);
  check(brush_fields_untouched(), "brush_leaves_other_fields_untouched");
  check(g_harness.job.pass_014 == 0, "brush_leaves_pass_unchanged");
}

void test_brush_dispatch_table_shape() {
  check(kProbeQuerySlotIndex == 17u, "dispatch_table_shape_index");
  check(offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44,
        "dispatch_table_shape_offset");
  check(sizeof(OpaqueGraphicsProbeVTable) == 0x48, "dispatch_table_shape_size");
  check(sizeof(OpaqueGraphicsProbe) == 4, "dispatch_table_shape_probe_size");
}

void run_all() {
  test_setup_acquire_constants();
  test_setup_acquire_arguments();
  test_setup_create_arguments();
  test_setup_create_factory_identity();
  test_setup_painter_slots();
  test_setup_source_field();
  test_setup_store_interleaves();
  test_setup_null_factory_clears_slots();
  test_setup_partial_factory_results();
  test_setup_scale_field_mapping();
  test_setup_scale_defaults();
  test_setup_scale_bit_exact();
  test_setup_global_address_constants();
  test_setup_leaves_head_untouched();
  test_setup_repeated_calls_are_fresh();
  test_signatures();
  test_brush_probe_fetched_once();
  test_brush_only_query_slot_is_called();
  test_brush_query_true_first_step_completes();
  test_brush_query_true_attempt_limit();
  test_brush_query_true_guard_rereads_pass();
  test_brush_query_true_pass_nonzero_never_aborts();
  test_brush_query_false_pass_zero();
  test_brush_query_false_pass_zero_falls_through();
  test_brush_query_false_pass_two();
  test_brush_query_false_pass_three();
  test_brush_query_false_other_pass();
  test_brush_query_false_pass_two_zero_step();
  test_brush_low_byte_truthiness();
  test_brush_query_true_low_byte_truthiness();
  test_brush_return_width_is_32_bit();
  test_brush_query_nonzero_low_byte_only();
  test_brush_leaves_other_fields_untouched();
  test_brush_dispatch_table_shape();
}

int report() {
  if (g_failures != 0) {
    std::printf("pkg-skinner-safe-wave10: %d failure(s)\n", g_failures);
    return 1;
  }
  std::printf("pkg-skinner-safe-wave10: all checks passed\n");
  return 0;
}

}

}

int main() {
  openspore::reconstruction::pkg_skinner_safe_wave10::run_all();
  return openspore::reconstruction::pkg_skinner_safe_wave10::report();
}
