#include "persistence_boundary.hpp"

#include <algorithm>
#include <cstring>

namespace openspore::reconstruction::pkg20_persistence_boundary {

namespace {

template <typename Value>
Value load_field(const void* object, std::uintptr_t offset) {
  Value value;
  std::memcpy(&value, static_cast<const std::uint8_t*>(object) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_field(void* object, std::uintptr_t offset, Value value) {
  std::memcpy(static_cast<std::uint8_t*>(object) + offset, &value,
              sizeof(value));
}

OpaquePaintJobHandle current_job(OpaqueEditor& editor) {
  return load_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                          kEditorCurrentPaintJobOffset);
}

void set_current_job(OpaqueEditor& editor, OpaquePaintJobHandle job) {
  store_field<OpaquePaintJobHandle>(editor.bytes.data(),
                                    kEditorCurrentPaintJobOffset, job);
}

void replace_job(OpaqueEditor& editor, OpaquePaintJobHandle job,
                 PaintBoundaryServices& services) {
  const auto previous = current_job(editor);
  set_current_job(editor, job);
  if (previous != kInvalidPaintJobHandle) {
    services.release_paint_job(previous);
  }
}

void clear_job(OpaqueEditor& editor, PaintBoundaryServices& services) {
  const auto job = current_job(editor);
  set_current_job(editor, kInvalidPaintJobHandle);
  if (job != kInvalidPaintJobHandle) {
    services.release_paint_job(job);
  }
}

void cancel_reusable_job(OpaqueEditor& editor,
                         PaintBoundaryServices& services) {
  const auto job_handle = current_job(editor);
  if (job_handle == kInvalidPaintJobHandle) {
    return;
  }

  auto* job = services.resolve_paint_job(job_handle);
  const auto first = load_field<std::uint8_t>(job, 0x6b);
  const auto second = load_field<std::uint8_t>(job, 0x6c);
  if (first != 0 || second != 0) {
    return;
  }

  services.notify_paint_system_cancel(job_handle);
  store_field<std::uint8_t>(job, 0x6b, 1);
  set_current_job(editor, kInvalidPaintJobHandle);
  services.release_paint_job(job_handle);
}

void attach_source(OpaqueEditor& editor, OpaquePaintJob* job,
                   PaintBoundaryServices& services) {
  const auto source = load_field<OpaqueReferenceHandle>(editor.bytes.data(),
                                                        kEditorSourceOffset);
  const auto previous = load_field<OpaqueReferenceHandle>(job, 0x08);
  if (source != kInvalidReferenceHandle) {
    services.retain_reference(source);
  }
  store_field<OpaqueReferenceHandle>(job, 0x08, source);
  if (previous != kInvalidReferenceHandle) {
    services.release_reference(previous);
  }
}

void configure_job(OpaqueEditor& editor, OpaquePaintJob* job,
                   const PaintRequest& request,
                   PaintBoundaryServices& services) {
  store_field<std::uint32_t>(
      job, 0x0c,
      load_field<std::uint32_t>(editor.bytes.data(), kEditorResourceAOffset));
  store_field<std::uint32_t>(
      job, 0x10,
      load_field<std::uint32_t>(editor.bytes.data(), kEditorResourceBOffset));
  store_field<std::uint32_t>(
      job, 0x14,
      load_field<std::uint32_t>(editor.bytes.data(), kEditorResourceCOffset));

  const auto configured = services.get_uint32_property(kPaintQualityProperty);
  store_field<std::uint32_t>(job, 0x5c,
                             std::max(configured, kMinimumPaintLimit));
  store_field<std::uint32_t>(job, 0x60, 0xffffffff);

  auto feature_enabled = request.field_0x10 != kDisableFeatureModelType;
  if (feature_enabled) {
    feature_enabled = services.get_bool_property(kPaintFeatureProperty);
  }
  store_field<std::uint8_t>(job, 0x65, feature_enabled ? 1 : 0);
  store_field<std::uint8_t>(
      job, 0x66,
      request.field_0x10 != kDisableChannelOverrideModelType ? 1 : 0);
  store_field<std::uint8_t>(job, 0x67, 1);
  store_field<std::uint8_t>(job, 0x68, 0);
  store_field<std::uint8_t>(job, 0x69, 0);
  store_field<std::uint8_t>(job, 0x6a, 1);

  for (std::size_t channel = 0; channel < 3; ++channel) {
    for (std::size_t word = 0; word < 3; ++word) {
      store_field<std::uint32_t>(job, 0x38 + channel * 0x0c + word * 4,
                                 request.field_0xa4[channel][word]);
    }
    store_field<std::uint32_t>(job, 0x18 + channel * 4,
                               request.field_0x8c[channel]);
    store_field<std::uint32_t>(job, 0x28 + channel * 4,
                               request.field_0x98[channel]);
  }
}

void apply_model_type_overrides(OpaquePaintJob* job, std::uint32_t model_type) {
  if (model_type == kSingleModelType) {
    store_field<std::uint32_t>(job, 0x24, 0xd723b947);
  }
  if (model_type == kDisableFeatureModelType) {
    store_field<std::uint32_t>(job, 0x24, 0);
    store_field<std::uint32_t>(job, 0x20, 0);
    store_field<std::uint32_t>(job, 0x1c, 0);
  }
}

void apply_property_list(OpaquePropertyListHandle property_list,
                         OpaquePaintJob* job, PaintBoundaryServices& services) {
  if (!services.query_property_list()) {
    return;
  }

  std::array<std::uint32_t, 3> values{};
  const auto count = services.get_uint32_array(
      property_list, kChannelFallbackProperty, values);
  const auto limit = std::min<std::size_t>(3, count);
  for (std::size_t channel = 0; channel < limit; ++channel) {
    const auto current = load_field<std::uint32_t>(job, 0x18 + channel * 4);
    if (current == 0) {
      store_field<std::uint32_t>(job, 0x18 + channel * 4, values[channel]);
    }
  }
}

bool path_is_empty(const ProfilePersistenceRequest& request) {
  return request.path == nullptr || request.path[0] == u'\0';
}

bool is_live_mode(std::uint32_t mode) {
  return std::find(kLiveProfileModes.begin(), kLiveProfileModes.end(), mode) !=
         kLiveProfileModes.end();
}

void apply_mode_candidate(std::uint32_t mode,
                          ProfilePersistenceCandidateServices& services) {
  if (mode != 0x1654c02u && mode != 0x1654c04u) {
    return;
  }

  auto* target = services.replace_mode_target();
  services.bind_mode_target(target);
  services.configure_mode_target(target);
  services.run_mode_target_cleanup(target);
}

}
PaintPersistenceBoundary::PaintPersistenceBoundary(
    PaintBoundaryServices& services)
    : services_(services) {}

bool PaintPersistenceBoundary::submit(OpaqueEditor& editor,
                                      const PaintRequest& request) {
  if (load_field<std::uint8_t>(editor.bytes.data(), kEditorStateFlagOffset) ==
      0) {
    return false;
  }

  cancel_reusable_job(editor, services_);
  const auto resource_a =
      load_field<std::uint32_t>(editor.bytes.data(), kEditorResourceAOffset);
  const auto resource_c =
      load_field<std::uint32_t>(editor.bytes.data(), kEditorResourceCOffset);
  services_.prepare_paint_resource(resource_a, resource_c,
                                   request.field_0xa4[0]);

  const auto job_handle = services_.allocate_paint_job();
  if (job_handle != kInvalidPaintJobHandle) {
    services_.construct_paint_job(job_handle);
  }
  replace_job(editor, job_handle, services_);
  if (job_handle == kInvalidPaintJobHandle) {
    return false;
  }
  auto* job = services_.resolve_paint_job(job_handle);
  attach_source(editor, job, services_);
  configure_job(editor, job, request, services_);

  const auto property_list =
      services_.resolve_property_list(request.field_0x58);
  apply_property_list(property_list, job, services_);
  apply_model_type_overrides(job, request.field_0x10);

  const auto accepted = services_.submit_bake(job_handle);
  if (!accepted) {
    clear_job(editor, services_);
  }
  if (property_list != kInvalidPropertyListHandle) {
    services_.release_property_list(property_list);
  }
  return accepted;
}

ProfilePersistenceBoundary::ProfilePersistenceBoundary(
    ProfilePersistenceCandidateServices& services)
    : services_(services) {}

void ProfilePersistenceBoundary::run_candidate(
    const ProfilePersistenceRequest& request) {
  if (path_is_empty(request)) {
    return;
  }

  services_.initialize_candidate();
  auto* species = services_.acquire_species_context();
  if (request.candidate_marker != 0 && services_.can_load_primary_candidate()) {
    auto* target = services_.load_primary_candidate();
    if (target == nullptr) {
      target = services_.load_secondary_candidate();
    }
    if (species != nullptr) {
      services_.apply_species_context(species);
    }

    const auto mode = services_.read_mode();
    if (is_live_mode(mode)) {
      services_.set_mode(mode);
      services_.write_mode(mode);
    }
    apply_mode_candidate(mode, services_);
    services_.set_profile_path(target, request.path);
    if (target != nullptr) {
      services_.release_profile_target(target);
    }
  }

  services_.build_profile_context(request.path);
  services_.run_temporary_profile(request.path);
  services_.replace_temporary_profile(request.path);
  if (request.candidate_marker != 0) {
    const auto alternate = services_.read_completion_path();
    services_.run_completion_path(alternate);
  }
  services_.finalize_candidate();
}

}