#include "persistence_boundary.hpp"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace openspore::reconstruction::pkg20_persistence_boundary {

struct OpaqueSpeciesContext {
  std::uint32_t value = 0;
};

struct OpaqueProfileTarget {
  std::uint32_t value = 0;
};

struct OpaqueModeTarget {
  std::uint32_t value = 0;
};

namespace {

const void* handle_value(std::uint32_t value) {
  return reinterpret_cast<const void*>(static_cast<std::uintptr_t>(value));
}

template <typename Value>
Value load_field(const void* object, std::uintptr_t offset) {
  Value value;
  const auto* bytes = static_cast<const std::uint8_t*>(object) + offset;
  std::memcpy(&value, bytes, sizeof(value));
  return value;
}

template <typename Value>
void store_field(void* object, std::uintptr_t offset, Value value) {
  auto* bytes = static_cast<std::uint8_t*>(object) + offset;
  std::memcpy(bytes, &value, sizeof(value));
}

enum class PaintEventKind : std::uint8_t {
  cancel_notify,
  release_job,
  prepare,
  allocate,
  construct,
  retain,
  release_reference,
  get_uint,
  get_bool,
  resolve,
  query,
  array,
  submit,
  release_property_list,
};

struct PaintEvent {
  PaintEventKind kind = PaintEventKind::cancel_notify;
  const void* first = nullptr;
  std::uint32_t second = 0;

  bool operator==(const PaintEvent& other) const {
    return kind == other.kind && first == other.first && second == other.second;
  }
};

class FakePaintServices final : public PaintBoundaryServices {
 public:
  static constexpr OpaquePaintJobHandle kNewJob = 0x1001;
  static constexpr OpaquePaintJobHandle kExistingJob = 0x2001;
  static constexpr OpaqueReferenceHandle kSource = 0x3001;
  static constexpr OpaquePropertyListHandle kPropertyList = 0x4001;

  std::vector<PaintEvent> events;
  OpaquePaintJob* allocated_job = nullptr;
  OpaquePaintJob* existing_job = nullptr;
  std::uint32_t quality = 0x50;
  bool feature = true;
  bool property_query_result = true;
  bool bake_result = true;
  bool resolve_result = true;
  bool allocation_succeeds = true;
  std::size_t submit_bake_calls = 0;
  std::vector<OpaquePaintJobHandle> resolved_jobs;
  std::array<std::uint32_t, 3> fallback{{0x11, 0x22, 0x33}};

  ~FakePaintServices() override = default;

  void notify_paint_system_cancel(OpaquePaintJobHandle job) override {
    events.push_back({PaintEventKind::cancel_notify, handle_value(job), 0});
  }

  void prepare_paint_resource(
      std::uint32_t resource_a, std::uint32_t resource_c,
      const std::array<std::uint32_t, 3>& record) override {
    assert(resource_a == 0x101);
    assert(resource_c == 0x303);
    assert(record[0] == 1 && record[1] == 2 && record[2] == 3);
    events.push_back({PaintEventKind::prepare, nullptr, resource_a});
  }

  OpaquePaintJobHandle allocate_paint_job() override {
    const auto job = allocation_succeeds ? kNewJob : kInvalidPaintJobHandle;
    if (allocation_succeeds) {
      allocated_job = new OpaquePaintJob{};
    }
    events.push_back({PaintEventKind::allocate, handle_value(job), 0});
    return job;
  }

  void construct_paint_job(OpaquePaintJobHandle job) override {
    assert(job == kNewJob);
    events.push_back({PaintEventKind::construct, handle_value(job), 0});
  }

  OpaquePaintJob* resolve_paint_job(OpaquePaintJobHandle job) override {
    resolved_jobs.push_back(job);
    if (job == kNewJob) {
      return allocated_job;
    }
    if (job == kExistingJob) {
      return existing_job;
    }
    assert(false);
    return nullptr;
  }

  void retain_reference(OpaqueReferenceHandle reference) override {
    events.push_back({PaintEventKind::retain, handle_value(reference), 0});
  }

  void release_reference(OpaqueReferenceHandle reference) override {
    events.push_back(
        {PaintEventKind::release_reference, handle_value(reference), 0});
  }

  void release_paint_job(OpaquePaintJobHandle job) override {
    events.push_back({PaintEventKind::release_job, handle_value(job), 0});
  }

  std::uint32_t get_uint32_property(std::uint32_t property_id) override {
    assert(property_id == kPaintQualityProperty);
    events.push_back({PaintEventKind::get_uint, nullptr, property_id});
    return quality;
  }

  bool get_bool_property(std::uint32_t property_id) override {
    assert(property_id == kPaintFeatureProperty);
    events.push_back({PaintEventKind::get_bool, nullptr, property_id});
    return feature;
  }

  OpaquePropertyListHandle resolve_property_list(
      std::uint32_t source_key) override {
    assert(source_key == 0x401);
    events.push_back({PaintEventKind::resolve, nullptr, source_key});
    return resolve_result ? kPropertyList : kInvalidPropertyListHandle;
  }

  bool query_property_list() override {
    events.push_back({PaintEventKind::query, nullptr, 0});
    return property_query_result;
  }

  std::size_t get_uint32_array(OpaquePropertyListHandle property_list,
                               std::uint32_t property_id,
                               std::array<std::uint32_t, 3>& values) override {
    assert(property_id == kChannelFallbackProperty);
    values = fallback;
    events.push_back(
        {PaintEventKind::array, handle_value(property_list), property_id});
    return 5;
  }

  void release_property_list(OpaquePropertyListHandle property_list) override {
    assert(property_list == kPropertyList);
    events.push_back({PaintEventKind::release_property_list,
                      handle_value(property_list), 0});
  }

  bool submit_bake(OpaquePaintJobHandle job) override {
    ++submit_bake_calls;
    events.push_back({PaintEventKind::submit, handle_value(job), 0});
    return bake_result;
  }
};

PaintRequest make_request() {
  PaintRequest request;
  request.field_0x10 = kDisableChannelOverrideModelType;
  request.field_0x58 = 0x401;
  request.field_0xa4[0] = {{1, 2, 3}};
  return request;
}

void configure_enabled_editor(OpaqueEditor& editor) {
  store_field<std::uint32_t>(editor.bytes.data(), kEditorResourceAOffset,
                             0x101);
  store_field<std::uint32_t>(editor.bytes.data(), kEditorResourceBOffset,
                             0x202);
  store_field<std::uint32_t>(editor.bytes.data(), kEditorResourceCOffset,
                             0x303);
  store_field<std::uint8_t>(editor.bytes.data(), kEditorStateFlagOffset, 1);
}

void test_disabled_paint_state() {
  FakePaintServices services;
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  store_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                    kEditorCurrentPaintJobOffset,
                                    FakePaintServices::kExistingJob);
  store_field<std::uint8_t>(editor.bytes.data(), kEditorStateFlagOffset, 0);

  const auto result = boundary.submit(editor, make_request());

  assert(!result);
  assert(services.events.empty());
  assert(load_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                          kEditorCurrentPaintJobOffset) ==
         FakePaintServices::kExistingJob);
}

void test_invalid_paint_job_handle() {
  FakePaintServices services;
  services.allocation_succeeds = false;
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  configure_enabled_editor(editor);

  const auto result = boundary.submit(editor, make_request());

  assert(!result);
  assert(services.events == (std::vector<PaintEvent>{
                                {PaintEventKind::prepare, nullptr, 0x101},
                                {PaintEventKind::allocate, nullptr, 0},
                            }));
  assert(services.resolved_jobs.empty());
  assert(services.submit_bake_calls == 0);
  assert(load_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                          kEditorCurrentPaintJobOffset) ==
         kInvalidPaintJobHandle);
}

void test_paint_job_creation_order() {
  FakePaintServices services;
  services.existing_job = new OpaquePaintJob{};
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  store_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                    kEditorCurrentPaintJobOffset,
                                    FakePaintServices::kExistingJob);
  store_field<OpaqueReferenceHandle>(editor.bytes.data(), kEditorSourceOffset,
                                     FakePaintServices::kSource);
  configure_enabled_editor(editor);
  store_field<std::uint8_t>(services.existing_job, 0x6b, 0);
  store_field<std::uint8_t>(services.existing_job, 0x6c, 0);

  const auto result = boundary.submit(editor, make_request());

  assert(result);
  assert(load_field<std::uint8_t>(services.existing_job, 0x6b) == 1);
  assert(
      services.events ==
      (std::vector<PaintEvent>{
          {PaintEventKind::cancel_notify,
           handle_value(FakePaintServices::kExistingJob), 0},
          {PaintEventKind::release_job,
           handle_value(FakePaintServices::kExistingJob), 0},
          {PaintEventKind::prepare, nullptr, 0x101},
          {PaintEventKind::allocate, handle_value(FakePaintServices::kNewJob),
           0},
          {PaintEventKind::construct, handle_value(FakePaintServices::kNewJob),
           0},
          {PaintEventKind::retain, handle_value(FakePaintServices::kSource), 0},
          {PaintEventKind::get_uint, nullptr, kPaintQualityProperty},
          {PaintEventKind::get_bool, nullptr, kPaintFeatureProperty},
          {PaintEventKind::resolve, nullptr, 0x401},
          {PaintEventKind::query, nullptr, 0},

          {PaintEventKind::array,
           handle_value(FakePaintServices::kPropertyList),
           kChannelFallbackProperty},
          {PaintEventKind::submit, handle_value(FakePaintServices::kNewJob), 0},
          {PaintEventKind::release_property_list,
           handle_value(FakePaintServices::kPropertyList), 0},
      }));
  assert(services.allocated_job != nullptr);
  assert(load_field<OpaqueReferenceHandle>(services.allocated_job, 0x08) ==
         FakePaintServices::kSource);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x5c) == 0x50);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x60) == 0xffffffff);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x65) == 1);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x66) == 0);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x67) == 1);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x68) == 0);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x69) == 0);
  assert(load_field<std::uint8_t>(services.allocated_job, 0x6a) == 1);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x18) == 0x11);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x1c) == 0x22);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x20) == 0x33);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x38) == 1);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x3c) == 2);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x40) == 3);

  delete services.allocated_job;
  delete services.existing_job;
}

void test_bake_rejection_order() {
  FakePaintServices services;
  services.bake_result = false;
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  configure_enabled_editor(editor);

  const auto result = boundary.submit(editor, make_request());

  assert(!result);
  const auto release_job =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::release_job;
                   });
  const auto release_list =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::release_property_list;
                   });
  assert(release_job != services.events.end());
  assert(release_list != services.events.end());
  assert(std::distance(release_job, release_list) == 1);
  assert(load_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                          kEditorCurrentPaintJobOffset) ==
         kInvalidPaintJobHandle);
  assert(release_job->first == handle_value(FakePaintServices::kNewJob));
  delete services.allocated_job;
}

void test_feature_flag_short_circuit() {
  FakePaintServices services;
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  configure_enabled_editor(editor);
  auto request = make_request();
  request.field_0x10 = kDisableFeatureModelType;

  const auto result = boundary.submit(editor, request);

  assert(result);
  const auto has_bool =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::get_bool;
                   });
  assert(has_bool == services.events.end());
  assert(load_field<std::uint8_t>(services.allocated_job, 0x65) == 0);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x1c) == 0);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x20) == 0);
  assert(load_field<std::uint32_t>(services.allocated_job, 0x24) == 0);
  delete services.allocated_job;
}

enum class ProfileEventKind : std::uint8_t {
  initialize,
  acquire_species,
  can_load_primary,
  load_primary,
  load_secondary,
  apply_species,
  read_mode,
  set_mode,
  write_mode,
  replace_mode,
  bind_mode,
  configure_mode,
  cleanup_mode,
  set_path,
  release_target,
  build_context,
  run_temporary,
  replace_temporary,
  read_completion,
  run_completion,
  finalize,
};

struct ProfileEvent {
  ProfileEventKind kind = ProfileEventKind::initialize;
  const void* first = nullptr;
  std::uint32_t second = 0;

  bool operator==(const ProfileEvent& other) const {
    return kind == other.kind && first == other.first && second == other.second;
  }
};

class FakeProfileServices final : public ProfilePersistenceCandidateServices {
 public:
  std::vector<ProfileEvent> events;
  OpaqueSpeciesContext species{21};
  OpaqueProfileTarget primary{31};
  OpaqueModeTarget mode_target{41};
  bool primary_available = true;
  bool primary_result = false;
  bool secondary_result = true;
  bool mode_target_result = true;
  std::uint32_t mode = 0x1654c04;
  bool alternate = true;
  const char16_t* expected_path = nullptr;

  ~FakeProfileServices() override = default;

  void initialize_candidate() override {
    events.push_back({ProfileEventKind::initialize, nullptr, 0});
  }

  OpaqueSpeciesContext* acquire_species_context() override {
    events.push_back({ProfileEventKind::acquire_species, &species, 0});
    return &species;
  }

  bool can_load_primary_candidate() override {
    events.push_back({ProfileEventKind::can_load_primary, nullptr, 0});
    return primary_available;
  }

  OpaqueProfileTarget* load_primary_candidate() override {
    events.push_back({ProfileEventKind::load_primary, &primary, 0});
    return primary_result ? &primary : nullptr;
  }

  OpaqueProfileTarget* load_secondary_candidate() override {
    events.push_back({ProfileEventKind::load_secondary, &primary, 0});
    return secondary_result ? &primary : nullptr;
  }

  void apply_species_context(OpaqueSpeciesContext* context) override {
    assert(context == &species);
    events.push_back({ProfileEventKind::apply_species, context, 0});
  }

  std::uint32_t read_mode() override {
    events.push_back({ProfileEventKind::read_mode, nullptr, 0});
    return mode;
  }

  void set_mode(std::uint32_t value) override {
    events.push_back({ProfileEventKind::set_mode, nullptr, value});
  }

  void write_mode(std::uint32_t value) override {
    events.push_back({ProfileEventKind::write_mode, nullptr, value});
  }

  OpaqueModeTarget* replace_mode_target() override {
    events.push_back({ProfileEventKind::replace_mode, &mode_target, 0});
    return mode_target_result ? &mode_target : nullptr;
  }

  void bind_mode_target(OpaqueModeTarget* target) override {
    assert(target == (mode_target_result ? &mode_target : nullptr));
    events.push_back({ProfileEventKind::bind_mode, target, 0});
  }

  void configure_mode_target(OpaqueModeTarget* target) override {
    assert(target == (mode_target_result ? &mode_target : nullptr));
    events.push_back({ProfileEventKind::configure_mode, target, 0});
  }

  void run_mode_target_cleanup(OpaqueModeTarget* target) override {
    assert(target == (mode_target_result ? &mode_target : nullptr));
    events.push_back({ProfileEventKind::cleanup_mode, target, 0});
  }

  void set_profile_path(OpaqueProfileTarget* target,
                        const char16_t* path) override {
    assert(target == nullptr || target == &primary);
    assert(path == expected_path);
    events.push_back({ProfileEventKind::set_path, target, 0});
  }

  void release_profile_target(OpaqueProfileTarget* target) override {
    assert(target == &primary);
    events.push_back({ProfileEventKind::release_target, target, 0});
  }

  void build_profile_context(const char16_t* path) override {
    assert(path == expected_path);
    events.push_back({ProfileEventKind::build_context, nullptr, 0});
  }

  void run_temporary_profile(const char16_t* path) override {
    assert(path == expected_path);
    events.push_back({ProfileEventKind::run_temporary, nullptr, 0});
  }

  void replace_temporary_profile(const char16_t* path) override {
    assert(path == expected_path);
    events.push_back({ProfileEventKind::replace_temporary, nullptr, 0});
  }

  bool read_completion_path() override {
    events.push_back({ProfileEventKind::read_completion, nullptr, 0});
    return alternate;
  }

  void run_completion_path(bool value) override {
    events.push_back(
        {ProfileEventKind::run_completion, nullptr, value ? 1U : 0U});
  }

  void finalize_candidate() override {
    events.push_back({ProfileEventKind::finalize, nullptr, 0});
  }
};

bool has_profile_event(const std::vector<ProfileEvent>& events,
                       ProfileEventKind kind) {
  return std::find_if(events.begin(), events.end(),
                      [kind](const ProfileEvent& event) {
                        return event.kind == kind;
                      }) != events.end();
}

void test_profile_candidate_boundary() {
  FakeProfileServices services;
  ProfilePersistenceBoundary boundary(services);
  const char16_t path[] = u"profile.spo";
  services.expected_path = path;
  const ProfilePersistenceRequest request{path, 1};

  boundary.run_candidate(request);

  assert(services.events ==
         (std::vector<ProfileEvent>{
             {ProfileEventKind::initialize, nullptr, 0},
             {ProfileEventKind::acquire_species, &services.species, 0},
             {ProfileEventKind::can_load_primary, nullptr, 0},
             {ProfileEventKind::load_primary, &services.primary, 0},
             {ProfileEventKind::load_secondary, &services.primary, 0},
             {ProfileEventKind::apply_species, &services.species, 0},
             {ProfileEventKind::read_mode, nullptr, 0},
             {ProfileEventKind::set_mode, nullptr, 0x1654c04},
             {ProfileEventKind::write_mode, nullptr, 0x1654c04},
             {ProfileEventKind::replace_mode, &services.mode_target, 0},

             {ProfileEventKind::bind_mode, &services.mode_target, 0},
             {ProfileEventKind::configure_mode, &services.mode_target, 0},
             {ProfileEventKind::cleanup_mode, &services.mode_target, 0},
             {ProfileEventKind::set_path, &services.primary, 0},
             {ProfileEventKind::release_target, &services.primary, 0},
             {ProfileEventKind::build_context, nullptr, 0},
             {ProfileEventKind::run_temporary, nullptr, 0},
             {ProfileEventKind::replace_temporary, nullptr, 0},
             {ProfileEventKind::read_completion, nullptr, 0},
             {ProfileEventKind::run_completion, nullptr, 1},
             {ProfileEventKind::finalize, nullptr, 0},
         }));
  assert(services.events.size() == 21);
}

void test_profile_primary_unavailable() {
  FakeProfileServices services;
  services.primary_available = false;
  ProfilePersistenceBoundary boundary(services);
  const char16_t path[] = u"profile.spo";
  services.expected_path = path;

  boundary.run_candidate({path, 1});

  assert(services.events ==
         (std::vector<ProfileEvent>{
             {ProfileEventKind::initialize, nullptr, 0},
             {ProfileEventKind::acquire_species, &services.species, 0},
             {ProfileEventKind::can_load_primary, nullptr, 0},
             {ProfileEventKind::build_context, nullptr, 0},
             {ProfileEventKind::run_temporary, nullptr, 0},
             {ProfileEventKind::replace_temporary, nullptr, 0},
             {ProfileEventKind::read_completion, nullptr, 0},
             {ProfileEventKind::run_completion, nullptr, 1},
             {ProfileEventKind::finalize, nullptr, 0},
         }));
}

void test_profile_empty_input() {
  FakeProfileServices services;
  ProfilePersistenceBoundary boundary(services);

  boundary.run_candidate({});
  boundary.run_candidate({u"", 1});

  assert(services.events.empty());
}

void test_profile_zero_marker_gates_candidate_and_completion() {
  FakeProfileServices services;
  ProfilePersistenceBoundary boundary(services);
  const char16_t path[] = u"profile.spo";
  services.expected_path = path;

  boundary.run_candidate({path, 0});

  assert(services.events ==
         (std::vector<ProfileEvent>{
             {ProfileEventKind::initialize, nullptr, 0},
             {ProfileEventKind::acquire_species, &services.species, 0},
             {ProfileEventKind::build_context, nullptr, 0},
             {ProfileEventKind::run_temporary, nullptr, 0},
             {ProfileEventKind::replace_temporary, nullptr, 0},
             {ProfileEventKind::finalize, nullptr, 0},
         }));
  assert(
      !has_profile_event(services.events, ProfileEventKind::can_load_primary));
  assert(
      !has_profile_event(services.events, ProfileEventKind::read_completion));
  assert(!has_profile_event(services.events, ProfileEventKind::run_completion));
}

void test_profile_unknown_mode_skips_mode_writes() {
  FakeProfileServices services;
  services.mode = 0x12345678u;
  services.primary_result = true;
  ProfilePersistenceBoundary boundary(services);
  const char16_t path[] = u"profile.spo";
  services.expected_path = path;

  boundary.run_candidate({path, 1});

  assert(has_profile_event(services.events, ProfileEventKind::read_mode));
  assert(!has_profile_event(services.events, ProfileEventKind::set_mode));
  assert(!has_profile_event(services.events, ProfileEventKind::write_mode));
  assert(!has_profile_event(services.events, ProfileEventKind::replace_mode));
  assert(has_profile_event(services.events, ProfileEventKind::set_path));
}

void test_profile_null_mode_target_still_cleans_up() {
  FakeProfileServices services;
  services.mode = 0x1654c02u;
  services.primary_result = false;
  services.secondary_result = false;
  services.mode_target_result = false;
  ProfilePersistenceBoundary boundary(services);
  const char16_t path[] = u"profile.spo";
  services.expected_path = path;

  boundary.run_candidate({path, 1});

  assert(has_profile_event(services.events, ProfileEventKind::set_mode));
  assert(has_profile_event(services.events, ProfileEventKind::write_mode));
  assert(has_profile_event(services.events, ProfileEventKind::replace_mode));
  assert(has_profile_event(services.events, ProfileEventKind::bind_mode));
  assert(has_profile_event(services.events, ProfileEventKind::configure_mode));
  const auto cleanup =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const ProfileEvent& event) {
                     return event.kind == ProfileEventKind::cleanup_mode;
                   });
  assert(cleanup != services.events.end());
  assert(cleanup->first == nullptr);
  assert(has_profile_event(services.events, ProfileEventKind::set_path));
}

void test_property_list_query_ordering_with_zero_handle() {
  FakePaintServices services;
  services.resolve_result = false;
  PaintPersistenceBoundary boundary(services);
  OpaqueEditor editor;
  configure_enabled_editor(editor);
  PaintRequest request = make_request();
  request.field_0x58 = 0x401;

  const auto result = boundary.submit(editor, request);

  assert(result);
  const auto resolve =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::resolve;
                   });
  const auto query =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::query;
                   });
  const auto array =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::array;
                   });
  const auto submit =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::submit;
                   });
  assert(resolve != services.events.end());
  assert(query != services.events.end());
  assert(array != services.events.end());
  assert(submit != services.events.end());
  assert(std::distance(resolve, query) == 1);
  assert(std::distance(query, array) == 1);
  assert(std::distance(array, submit) == 1);
  assert(resolve->second == 0x401);
  assert(array->first == handle_value(kInvalidPropertyListHandle));
  const auto release =
      std::find_if(services.events.begin(), services.events.end(),
                   [](const PaintEvent& event) {
                     return event.kind == PaintEventKind::release_property_list;
                   });
  assert(release == services.events.end());
  delete services.allocated_job;
}

}
}
int main() {
  using namespace openspore::reconstruction::pkg20_persistence_boundary;
  test_disabled_paint_state();
  test_invalid_paint_job_handle();
  test_paint_job_creation_order();
  test_bake_rejection_order();
  test_feature_flag_short_circuit();
  test_profile_candidate_boundary();
  test_profile_primary_unavailable();
  test_profile_empty_input();
  test_profile_zero_marker_gates_candidate_and_completion();
  test_profile_unknown_mode_skips_mode_writes();
  test_profile_null_mode_target_still_cleans_up();
  test_property_list_query_ordering_with_zero_handle();
}
