#include "paint_job_004c5200.hpp"

#include <algorithm>
#include <cstring>

namespace openspore::reconstruction::pkg20_persistence_boundary {
namespace {

void* field_address(void* base, std::size_t offset) {
  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(base) +
                                 offset);
}

const void* field_address(const void* base, std::size_t offset) {
  return reinterpret_cast<const void*>(reinterpret_cast<std::uintptr_t>(base) +
                                       offset);
}

template <typename Value>
Value load_field(const void* base, std::size_t offset) {
  Value value{};
  std::memcpy(&value, field_address(base, offset), sizeof(value));
  return value;
}

template <typename Value>
void store_field(void* base, std::size_t offset, Value value) {
  std::memcpy(field_address(base, offset), &value, sizeof(value));
}

OpaquePaintJobHandle current_job(const OpaqueEditor& editor) {
  return load_field<OpaquePaintJobHandle>(editor.bytes, 0x5cu);
}

void set_current_job(OpaqueEditor& editor, OpaquePaintJobHandle job) {
  store_field<OpaquePaintJobHandle>(editor.bytes, 0x5cu, job);
}

void clear_job(OpaqueEditor& editor, PaintJobServices& services) {
  const OpaquePaintJobHandle job = current_job(editor);
  set_current_job(editor, kInvalidPaintJobHandle);
  if (job != kInvalidPaintJobHandle) {
    services.release_paint_job(job);
  }
}

void cancel_reusable_job(OpaqueEditor& editor, PaintJobServices& services) {
  const OpaquePaintJobHandle job = current_job(editor);
  if (job == kInvalidPaintJobHandle || !services.is_reusable_job(&editor)) {
    return;
  }

  OpaquePaintSystem* paint_system = services.get_paint_system();
  services.cancel_paint_system(paint_system, job);
  set_current_job(editor, kInvalidPaintJobHandle);
  services.release_paint_job(job);
}

void attach_source(OpaqueEditor& editor, OpaquePaintJob* job,
                   PaintJobServices& services) {
  const OpaqueReferenceHandle source =
      load_field<OpaqueReferenceHandle>(editor.bytes, 0x1cu);
  const OpaqueReferenceHandle previous =
      load_field<OpaqueReferenceHandle>(job, 0x08u);
  if (source != kInvalidReferenceHandle) {
    services.retain_reference(source);
  }
  store_field<OpaqueReferenceHandle>(job, 0x08u, source);
  if (previous != kInvalidReferenceHandle) {
    services.release_reference(previous);
  }
}

void configure_job(OpaqueEditor& editor, OpaquePaintJob* job,
                   const PaintRequest& request, PaintJobServices& services) {
  store_field<OpaqueWord>(job, 0x0cu,
                          load_field<OpaqueWord>(editor.bytes, 0x64u));
  store_field<OpaqueWord>(job, 0x10u,
                          load_field<OpaqueWord>(editor.bytes, 0x68u));
  store_field<OpaqueWord>(job, 0x14u,
                          load_field<OpaqueWord>(editor.bytes, 0x6cu));

  const OpaqueWord quality =
      services.get_uint32_property(kPaintQualityProperty);
  store_field<OpaqueWord>(job, 0x5cu, std::max(quality, kMinimumPaintLimit));
  store_field<OpaqueWord>(job, 0x60u, 0xffffffffu);

  bool feature_enabled = request.field_0x10 != kDisableFeatureModelType;
  if (feature_enabled) {
    feature_enabled = services.get_bool_property(kPaintFeatureProperty);
  }
  store_field<std::uint8_t>(job, 0x65u, feature_enabled ? 1u : 0u);
  store_field<std::uint8_t>(
      job, 0x66u,
      request.field_0x10 != kDisableChannelOverrideModelType ? 1u : 0u);
  store_field<std::uint8_t>(job, 0x67u, 1u);
  store_field<std::uint8_t>(job, 0x68u, 0u);
  store_field<std::uint8_t>(job, 0x69u, 0u);
  store_field<std::uint8_t>(job, 0x6au, 1u);

  for (std::size_t channel = 0; channel < 3u; ++channel) {
    std::array<OpaqueWord, 3> record{};
    services.get_channel_record(request, channel, record);
    for (std::size_t word = 0; word < 3u; ++word) {
      store_field<OpaqueWord>(job, 0x38u + channel * 0x0cu + word * 4u,
                              record[word]);
    }
    store_field<OpaqueWord>(job, 0x18u + channel * 4u,
                            services.get_channel_8c(request, channel));
    store_field<OpaqueWord>(job, 0x28u + channel * 4u,
                            services.get_channel_98(request, channel));
  }
}

void apply_model_type_overrides(OpaquePaintJob* job, OpaqueWord model_type) {
  if (model_type == kSingleModelType) {
    store_field<OpaqueWord>(job, 0x24u, 0xd723b947u);
  }
  if (model_type == kDisableFeatureModelType) {
    store_field<OpaqueWord>(job, 0x24u, 0u);
    store_field<OpaqueWord>(job, 0x20u, 0u);
    store_field<OpaqueWord>(job, 0x1cu, 0u);
  }
}

void apply_property_fallback(OpaquePropertyListHandle property_list,
                             OpaquePaintJob* job, PaintJobServices& services,
                             OpaquePropertyService* property_service) {
  if (!services.query_property_list(property_service)) {
    return;
  }

  std::array<OpaqueWord, 3> values{};
  const std::size_t count = services.get_uint32_array(
      property_list, kChannelFallbackProperty, values);
  const std::size_t limit = std::min<std::size_t>(3u, count);
  for (std::size_t channel = 0; channel < limit; ++channel) {
    if (load_field<OpaqueWord>(job, 0x18u + channel * 4u) == 0u) {
      store_field<OpaqueWord>(job, 0x18u + channel * 4u, values[channel]);
    }
  }
}

}

bool paint_job_prepare_and_submit(OpaqueEditor& editor,
                                  const PaintRequest& request,
                                  PaintJobServices& services,
                                  const PaintJobModelOptions* model_options) {
  if (load_field<std::uint8_t>(editor.bytes, 0x84u) == 0u) {
    return false;
  }

  cancel_reusable_job(editor, services);
  services.prepare_paint_resource(load_field<OpaqueWord>(editor.bytes, 0x64u),
                                  load_field<OpaqueWord>(editor.bytes, 0x6cu),
                                  request.field_0xa4[0]);

  OpaquePaintJob* job =
      services.allocate_paint_job(kPaintJobAllocationSize, "Editor");
  const OpaquePaintJobHandle job_handle =
      reinterpret_cast<OpaquePaintJobHandle>(job);
  if (job != nullptr) {
    if (job_handle == 1u && model_options != nullptr &&
        model_options->guard_invalid_job_handle) {
      return false;
    }
    services.construct_paint_job(job);
  }
  const OpaquePaintJobHandle previous = current_job(editor);
  if (job_handle != previous) {
    if (job_handle != kInvalidPaintJobHandle) {
      services.retain_paint_job(job_handle);
    }
    set_current_job(editor, job_handle);
    if (previous != kInvalidPaintJobHandle) {
      services.release_paint_job(previous);
    }
  }

  if (job == nullptr && model_options != nullptr &&
      model_options->guard_invalid_allocation) {
    return false;
  }

  attach_source(editor, job, services);
  configure_job(editor, job, request, services);

  OpaquePropertyService* property_service = services.get_property_service();
  const OpaquePropertyListHandle property_list =
      services.resolve_property_list(request.field_0x58);
  apply_property_fallback(property_list, job, services, property_service);
  apply_model_type_overrides(job, request.field_0x10);

  IBakeManager* bake_manager = services.get_bake_manager();
  if (bake_manager == nullptr && model_options != nullptr &&
      model_options->guard_null_bake_manager) {
    if (property_list != kInvalidPropertyListHandle) {
      services.release_property_list(property_list);
    }
    return false;
  }

  const bool accepted = services.submit_bake(bake_manager, job_handle);
  if (!accepted) {
    clear_job(editor, services);
  }
  if (property_list != kInvalidPropertyListHandle) {
    services.release_property_list(property_list);
  }
  return accepted;
}

}
