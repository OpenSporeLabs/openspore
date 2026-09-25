#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "paint_job_004c5200.hpp"

namespace openspore::reconstruction::pkg20_persistence_boundary {

struct OpaquePaintSystem {
  OpaqueWord marker;
};

struct OpaquePropertyService {
  OpaqueWord marker;
};

struct IBakeManager {
  OpaqueWord marker;
};

namespace {

using Job = OpaquePaintJob;
using Handle = OpaquePaintJobHandle;

Handle handle_of(Job* job) { return reinterpret_cast<Handle>(job); }

enum class EventKind : std::uint8_t {
  reusable,
  paint_system,
  cancel,
  prepare,
  allocate,
  construct,
  retain_paint_job,
  retain_reference,
  release_reference,
  release_job,
  get_uint32,
  get_bool,
  property_root,
  resolve,
  query,
  array,
  bake_manager,
  submit,
  release_property_list,
};

struct Event {
  EventKind kind;
  OpaqueWord first;
  OpaqueWord second;
  OpaqueWord third;
};

template <typename Value>
Value load_field(const void* base, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_field(void* base, std::size_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

class FakeServices final : public PaintJobServices {
 public:
  static constexpr OpaqueReferenceHandle kSource = 0x3001u;
  static constexpr OpaquePropertyListHandle kPropertyList = 0x4001u;

  std::vector<Event> events;
  OpaquePaintSystem paint_system{0x01u};
  OpaquePropertyService property_service{0x02u};
  IBakeManager bake_manager{0x03u};
  Job existing_job{};
  Job new_job{};
  OpaqueWord quality = 0x20u;
  bool feature = true;
  bool property_query_result = true;
  bool bake_result = true;
  bool bake_manager_available = true;
  bool allocation_succeeds = true;
  bool return_invalid_job = false;
  OpaquePropertyListHandle property_list_handle = kPropertyList;
  std::size_t fallback_count = 3u;
  std::array<OpaqueWord, 3> fallback{{0x11u, 0x22u, 0x33u}};
  OpaqueWord allocation_size = 0u;
  const char* allocation_domain = nullptr;
  OpaquePaintJob* allocation_result_override = nullptr;

  void record(EventKind kind, OpaqueWord first = 0u, OpaqueWord second = 0u,
              OpaqueWord third = 0u) {
    events.push_back({kind, first, second, third});
  }

  std::size_t index_of(EventKind kind) const {
    for (std::size_t index = 0; index < events.size(); ++index) {
      if (events[index].kind == kind) {
        return index;
      }
    }
    assert(false);
    return events.size();
  }

  bool has_event(EventKind kind) const {
    for (const Event& event : events) {
      if (event.kind == kind) {
        return true;
      }
    }
    return false;
  }

  bool is_reusable_job(const OpaqueEditor* editor) override {
    record(EventKind::reusable);
    const Handle handle = load_field<Handle>(editor->bytes, 0x5cu);
    Job* data = reinterpret_cast<Job*>(handle);
    const Job* job = data == &existing_job || data == &new_job ? data : nullptr;
    if (job == nullptr) {
      return false;
    }
    return load_field<std::uint8_t>(job, 0x6bu) == 0u &&
           load_field<std::uint8_t>(job, 0x6cu) == 0u;
  }

  OpaquePaintSystem* get_paint_system() override {
    record(EventKind::paint_system);
    return &paint_system;
  }

  void cancel_paint_system(OpaquePaintSystem* system, Handle job) override {
    assert(system == &paint_system);
    Job* data = reinterpret_cast<Job*>(job);
    if (data != &existing_job && data != &new_job) {
      data = nullptr;
    }
    if (data != nullptr) {
      store_field<std::uint8_t>(data, 0x6bu, 1u);
    }
    record(EventKind::cancel, job);
  }

  void prepare_paint_resource(
      OpaqueWord resource_a, OpaqueWord resource_c,
      const std::array<OpaqueWord, 3>& record_values) override {
    record(EventKind::prepare, resource_a, resource_c,
           record_values[0] + record_values[1] + record_values[2]);
  }

  OpaquePaintJob* allocate_paint_job(std::size_t size,
                                     const char* domain) override {
    allocation_size = static_cast<OpaqueWord>(size);
    allocation_domain = domain;
    OpaquePaintJob* result = allocation_result_override;
    if (result == nullptr && allocation_succeeds) {
      result =
          return_invalid_job ? reinterpret_cast<OpaquePaintJob*>(1u) : &new_job;
    }
    record(EventKind::allocate, reinterpret_cast<OpaqueWord>(result), size);
    return result;
  }

  void construct_paint_job(OpaquePaintJob* job) override {
    if (job != &new_job) {
      raise(SIGSEGV);
    }
    std::memset(new_job.bytes, 0, sizeof(new_job.bytes));
    record(EventKind::construct, handle_of(job));
  }

  void retain_paint_job(OpaquePaintJobHandle job) override {
    record(EventKind::retain_paint_job, job);
  }

  void retain_reference(OpaqueReferenceHandle reference) override {
    record(EventKind::retain_reference, reference);
  }

  void release_reference(OpaqueReferenceHandle reference) override {
    record(EventKind::release_reference, reference);
  }

  void release_paint_job(Handle job) override {
    record(EventKind::release_job, job);
  }

  OpaqueWord get_uint32_property(OpaqueWord property_id) override {
    record(EventKind::get_uint32, property_id, quality);
    return quality;
  }

  bool get_bool_property(OpaqueWord property_id) override {
    record(EventKind::get_bool, property_id, feature ? 1u : 0u);
    return feature;
  }

  OpaquePropertyService* get_property_service() override {
    record(EventKind::property_root);
    return &property_service;
  }

  OpaquePropertyListHandle resolve_property_list(
      OpaqueWord source_key) override {
    record(EventKind::resolve, source_key, property_list_handle);
    return property_list_handle;
  }

  bool query_property_list(OpaquePropertyService* service) override {
    assert(service == &property_service);
    record(EventKind::query, property_query_result ? 1u : 0u);
    return property_query_result;
  }

  std::size_t get_uint32_array(OpaquePropertyListHandle property_list,
                               OpaqueWord property_id,
                               std::array<OpaqueWord, 3>& values) override {
    record(EventKind::array, property_list, property_id);
    values = fallback;
    return fallback_count;
  }

  void release_property_list(OpaquePropertyListHandle property_list) override {
    record(EventKind::release_property_list, property_list);
  }

  IBakeManager* get_bake_manager() override {
    record(EventKind::bake_manager);
    return bake_manager_available ? &bake_manager : nullptr;
  }

  bool submit_bake(IBakeManager* manager, Handle job) override {
    if (manager == nullptr) {
      raise(SIGSEGV);
    }
    assert(manager == &bake_manager);
    record(EventKind::submit, job, bake_result ? 1u : 0u);
    return bake_result;
  }

  void get_channel_record(const PaintRequest& request, std::size_t channel,
                          std::array<OpaqueWord, 3>& record_values) override {
    record(EventKind::array, static_cast<OpaqueWord>(channel), 0x100u);
    record_values = request.field_0xa4[channel];
  }

  OpaqueWord get_channel_8c(const PaintRequest& request,
                            std::size_t channel) override {
    return request.field_0x8c[channel];
  }

  OpaqueWord get_channel_98(const PaintRequest& request,
                            std::size_t channel) override {
    return request.field_0x98[channel];
  }
};

void configure_editor(OpaqueEditor& editor) {
  store_field<OpaqueReferenceHandle>(editor.bytes, 0x1cu,
                                     FakeServices::kSource);
  store_field<OpaqueWord>(editor.bytes, 0x64u, 0x101u);
  store_field<OpaqueWord>(editor.bytes, 0x68u, 0x202u);
  store_field<OpaqueWord>(editor.bytes, 0x6cu, 0x303u);
  store_field<std::uint8_t>(editor.bytes, 0x84u, 1u);
}

PaintRequest make_request() {
  PaintRequest request;
  request.field_0x10 = kDisableChannelOverrideModelType;
  request.field_0x58 = 0x401u;
  request.field_0xa4[0] = {{1u, 2u, 3u}};
  request.field_0xa4[1] = {{4u, 5u, 6u}};
  request.field_0xa4[2] = {{7u, 8u, 9u}};
  request.field_0x8c = {{0u, 0u, 0u}};
  request.field_0x98 = {{0x41u, 0x42u, 0x43u}};
  return request;
}

void set_reusable(FakeServices& services, OpaqueEditor& editor) {
  store_field<Handle>(editor.bytes, 0x5cu, handle_of(&services.existing_job));
  store_field<std::uint8_t>(services.existing_job.bytes, 0x6bu, 0u);
  store_field<std::uint8_t>(services.existing_job.bytes, 0x6cu, 0u);
}

void expect_signal(void (*body)()) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    body();
    _exit(0);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void test_disabled_state() {
  FakeServices services;
  OpaqueEditor editor{};
  store_field<Handle>(editor.bytes, 0x5cu, handle_of(&services.existing_job));
  store_field<std::uint8_t>(editor.bytes, 0x84u, 0u);
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services);
  assert(!result);
  assert(services.events.empty());
}

void test_reusable_cancellation_and_submission() {
  FakeServices services;
  OpaqueEditor editor{};
  configure_editor(editor);
  set_reusable(services, editor);
  const PaintRequest request = make_request();
  const bool result = paint_job_prepare_and_submit(editor, request, services);

  assert(result);
  assert(load_field<Handle>(editor.bytes, 0x5cu) ==
         handle_of(&services.new_job));
  assert(load_field<std::uint8_t>(services.existing_job.bytes, 0x6bu) == 1u);
  assert(load_field<OpaqueReferenceHandle>(services.new_job.bytes, 0x08u) ==
         FakeServices::kSource);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x0cu) == 0x101u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x10u) == 0x202u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x14u) == 0x303u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x5cu) == 0x40u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x60u) == UINT32_MAX);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x65u) == 1u);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x66u) == 0u);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x67u) == 1u);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x68u) == 0u);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x69u) == 0u);
  assert(load_field<std::uint8_t>(services.new_job.bytes, 0x6au) == 1u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x18u) == 0x11u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x1cu) == 0x22u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x20u) == 0x33u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x38u) == 1u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x3cu) == 2u);
  assert(load_field<OpaqueWord>(services.new_job.bytes, 0x40u) == 3u);
  assert(services.allocation_size == 0x84u);
  assert(std::strcmp(services.allocation_domain, "Editor") == 0);
  std::size_t retain_paint_job_count = 0u;
  std::size_t retain_reference_count = 0u;
  for (const Event& event : services.events) {
    retain_paint_job_count +=
        event.kind == EventKind::retain_paint_job ? 1u : 0u;
    retain_reference_count +=
        event.kind == EventKind::retain_reference ? 1u : 0u;
  }
  assert(retain_paint_job_count == 1u);
  assert(retain_reference_count == 1u);
  assert(
      services.events[services.index_of(EventKind::retain_paint_job)].first ==
      handle_of(&services.new_job));
  assert(
      services.events[services.index_of(EventKind::retain_reference)].first ==
      FakeServices::kSource);
  assert(services.index_of(EventKind::reusable) <
         services.index_of(EventKind::cancel));
  assert(services.index_of(EventKind::cancel) <
         services.index_of(EventKind::release_job));
  assert(services.index_of(EventKind::release_job) <
         services.index_of(EventKind::prepare));
  assert(services.index_of(EventKind::prepare) <
         services.index_of(EventKind::allocate));
  assert(services.index_of(EventKind::allocate) <
         services.index_of(EventKind::construct));
  assert(services.index_of(EventKind::construct) <
         services.index_of(EventKind::retain_paint_job));
  assert(services.index_of(EventKind::retain_paint_job) <
         services.index_of(EventKind::retain_reference));
  assert(services.index_of(EventKind::array) <
         services.index_of(EventKind::property_root));
  assert(services.index_of(EventKind::property_root) <
         services.index_of(EventKind::resolve));
  assert(services.index_of(EventKind::resolve) <
         services.index_of(EventKind::query));
  assert(services.index_of(EventKind::query) <
         services.index_of(EventKind::submit));
  assert(services.index_of(EventKind::submit) <
         services.index_of(EventKind::release_property_list));
}

void test_nonreusable_replacement() {
  FakeServices services;
  OpaqueEditor editor{};
  configure_editor(editor);
  store_field<Handle>(editor.bytes, 0x5cu, handle_of(&services.existing_job));
  store_field<std::uint8_t>(services.existing_job.bytes, 0x6bu, 1u);
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services);
  assert(result);
  assert(!services.has_event(EventKind::cancel));
  assert(services.index_of(EventKind::construct) <
         services.index_of(EventKind::retain_paint_job));
  assert(services.index_of(EventKind::retain_paint_job) <
         services.index_of(EventKind::release_job));
  assert(
      services.events[services.index_of(EventKind::retain_paint_job)].first ==
      handle_of(&services.new_job));
  assert(services.index_of(EventKind::release_job) <
         services.index_of(EventKind::retain_reference));
  assert(services.index_of(EventKind::retain_reference) <
         services.index_of(EventKind::submit));
  assert(load_field<Handle>(editor.bytes, 0x5cu) ==
         handle_of(&services.new_job));
}

void test_same_handle_replacement() {
  FakeServices services;
  services.allocation_result_override = &services.new_job;
  OpaqueEditor editor{};
  configure_editor(editor);
  store_field<Handle>(editor.bytes, 0x5cu, handle_of(&services.new_job));
  store_field<std::uint8_t>(services.new_job.bytes, 0x6bu, 1u);
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services);
  assert(result);
  assert(load_field<Handle>(editor.bytes, 0x5cu) ==
         handle_of(&services.new_job));
  assert(!services.has_event(EventKind::retain_paint_job));
  assert(!services.has_event(EventKind::release_job));
  assert(services.index_of(EventKind::allocate) <
         services.index_of(EventKind::construct));
  assert(services.index_of(EventKind::construct) <
         services.index_of(EventKind::retain_reference));
}

void test_null_allocation_replacement() {
  FakeServices services;
  services.allocation_succeeds = false;
  OpaqueEditor editor{};
  configure_editor(editor);
  store_field<Handle>(editor.bytes, 0x5cu, handle_of(&services.existing_job));
  store_field<std::uint8_t>(services.existing_job.bytes, 0x6bu, 1u);
  PaintJobModelOptions options;
  options.guard_invalid_allocation = true;
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services, &options);
  assert(!result);
  assert(load_field<Handle>(editor.bytes, 0x5cu) == 0u);
  assert(!services.has_event(EventKind::retain_paint_job));
  assert(services.events[services.index_of(EventKind::release_job)].first ==
         handle_of(&services.existing_job));
}

void test_type_overrides_and_property_fallback() {
  {
    FakeServices services;
    OpaqueEditor editor{};
    configure_editor(editor);
    PaintRequest request = make_request();
    request.field_0x10 = kDisableFeatureModelType;
    const bool result = paint_job_prepare_and_submit(editor, request, services);
    assert(result);
    assert(!services.has_event(EventKind::get_bool));
    assert(load_field<std::uint8_t>(services.new_job.bytes, 0x65u) == 0u);
    assert(load_field<OpaqueWord>(services.new_job.bytes, 0x1cu) == 0u);
    assert(load_field<OpaqueWord>(services.new_job.bytes, 0x20u) == 0u);
    assert(load_field<OpaqueWord>(services.new_job.bytes, 0x24u) == 0u);
    assert(services.index_of(EventKind::array) <
           services.index_of(EventKind::submit));
  }
  {
    FakeServices services;
    OpaqueEditor editor{};
    configure_editor(editor);
    PaintRequest request = make_request();
    request.field_0x10 = kSingleModelType;
    const bool result = paint_job_prepare_and_submit(editor, request, services);
    assert(result);
    assert(load_field<OpaqueWord>(services.new_job.bytes, 0x24u) ==
           0xd723b947u);
    assert(load_field<std::uint8_t>(services.new_job.bytes, 0x66u) == 1u);
  }
}

void test_bake_rejection_cleanup() {
  FakeServices services;
  services.bake_result = false;
  OpaqueEditor editor{};
  configure_editor(editor);
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services);
  assert(!result);
  assert(load_field<Handle>(editor.bytes, 0x5cu) == 0u);
  const std::size_t release_job = services.index_of(EventKind::release_job);
  const std::size_t release_list =
      services.index_of(EventKind::release_property_list);
  assert(release_job < release_list);
  assert(services.events[release_job].first == handle_of(&services.new_job));
  assert(services.events[release_list].first == FakeServices::kPropertyList);
}

void test_invalid_property_list() {
  FakeServices services;
  services.property_list_handle = kInvalidPropertyListHandle;
  OpaqueEditor editor{};
  configure_editor(editor);
  const bool result =
      paint_job_prepare_and_submit(editor, make_request(), services);
  assert(result);
  assert(services.index_of(EventKind::array) < services.events.size());
  assert(!services.has_event(EventKind::release_property_list));
}

void test_explicit_guards() {
  {
    FakeServices services;
    services.allocation_succeeds = false;
    OpaqueEditor editor{};
    configure_editor(editor);
    PaintJobModelOptions options;
    options.guard_invalid_allocation = true;
    const bool result = paint_job_prepare_and_submit(editor, make_request(),
                                                     services, &options);
    assert(!result);
    assert(load_field<Handle>(editor.bytes, 0x5cu) == 0u);
    assert(!services.has_event(EventKind::property_root));
  }
  {
    FakeServices services;
    services.return_invalid_job = true;
    OpaqueEditor editor{};
    configure_editor(editor);
    PaintJobModelOptions options;
    options.guard_invalid_job_handle = true;
    const bool result = paint_job_prepare_and_submit(editor, make_request(),
                                                     services, &options);
    assert(!result);
    assert(load_field<Handle>(editor.bytes, 0x5cu) == 0u);
    assert(!services.has_event(EventKind::submit));
  }
  {
    FakeServices services;
    OpaqueEditor editor{};
    configure_editor(editor);
    services.bake_result = true;
    services.bake_manager_available = false;
    services.property_query_result = false;
    PaintJobModelOptions options;
    options.guard_null_bake_manager = true;
    const bool result = paint_job_prepare_and_submit(editor, make_request(),
                                                     services, &options);
    assert(!result);
    assert(!services.has_event(EventKind::submit));
    assert(services.index_of(EventKind::release_property_list) <
           services.events.size());
  }
}

[[noreturn]] void fail_allocation() {
  FakeServices services;
  services.allocation_succeeds = false;
  OpaqueEditor editor{};
  configure_editor(editor);
  paint_job_prepare_and_submit(editor, make_request(), services);
  _exit(0);
}

[[noreturn]] void fail_invalid_handle() {
  FakeServices services;
  services.return_invalid_job = true;
  OpaqueEditor editor{};
  configure_editor(editor);
  paint_job_prepare_and_submit(editor, make_request(), services);
  _exit(0);
}

[[noreturn]] void fail_null_bake_manager() {
  FakeServices services;
  OpaqueEditor editor{};
  configure_editor(editor);
  services.bake_result = false;
  services.bake_manager_available = false;
  services.property_query_result = false;
  paint_job_prepare_and_submit(editor, make_request(), services);
  _exit(0);
}

}

}

using namespace openspore::reconstruction::pkg20_persistence_boundary;

int main() {
  test_disabled_state();
  test_reusable_cancellation_and_submission();
  test_nonreusable_replacement();
  test_same_handle_replacement();
  test_null_allocation_replacement();
  test_type_overrides_and_property_fallback();
  test_bake_rejection_cleanup();
  test_invalid_property_list();
  test_explicit_guards();
  expect_signal(fail_allocation);
  expect_signal(fail_invalid_handle);
  expect_signal(fail_null_bake_manager);
}
