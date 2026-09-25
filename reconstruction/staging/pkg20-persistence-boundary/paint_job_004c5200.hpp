#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg20_persistence_boundary {

struct OpaqueEditor {
  std::uint8_t bytes[0x88];
};

struct OpaquePaintJob {
  std::uint8_t bytes[0x84];
};

struct OpaqueEditorSkin;
struct OpaqueModel;
struct OpaquePaintSystem;
struct OpaquePropertyService;
struct IBakeManager;

using OpaqueWord = std::uint32_t;
using OpaquePaintJobHandle = OpaqueWord;
using OpaqueReferenceHandle = OpaqueWord;
using OpaquePropertyListHandle = OpaqueWord;

inline constexpr OpaquePaintJobHandle kInvalidPaintJobHandle = 0u;
inline constexpr OpaqueReferenceHandle kInvalidReferenceHandle = 0u;
inline constexpr OpaquePropertyListHandle kInvalidPropertyListHandle = 0u;
inline constexpr std::size_t kPaintJobAllocationSize = 0x84u;
inline constexpr OpaqueWord kPaintQualityProperty = 0xb8864eacu;
inline constexpr OpaqueWord kPaintFeatureProperty = 0x2853e342u;
inline constexpr OpaqueWord kChannelFallbackProperty = 0x05e68c2eu;
inline constexpr OpaqueWord kDisableFeatureModelType = 0x3d97a8e4u;
inline constexpr OpaqueWord kDisableChannelOverrideModelType = 0x438f6347u;
inline constexpr OpaqueWord kSingleModelType = 0x2b978c46u;
inline constexpr OpaqueWord kMinimumPaintLimit = 0x40u;

struct PaintRequest {
  OpaqueWord field_0x10 = 0u;
  OpaqueWord field_0x58 = 0u;
  std::array<OpaqueWord, 3> field_0x8c{};
  std::array<OpaqueWord, 3> field_0x98{};
  std::array<std::array<OpaqueWord, 3>, 3> field_0xa4{};
};

struct PaintJobModelOptions {
  bool guard_invalid_allocation = false;
  bool guard_invalid_job_handle = false;
  bool guard_null_bake_manager = false;
};

class PaintJobServices {
 public:
  virtual ~PaintJobServices() = default;

  virtual bool is_reusable_job(const OpaqueEditor* editor) = 0;
  virtual OpaquePaintSystem* get_paint_system() = 0;
  virtual void cancel_paint_system(OpaquePaintSystem* paint_system,
                                   OpaquePaintJobHandle job) = 0;
  virtual void prepare_paint_resource(
      OpaqueWord resource_a, OpaqueWord resource_c,
      const std::array<OpaqueWord, 3>& record) = 0;
  virtual OpaquePaintJob* allocate_paint_job(std::size_t size,
                                             const char* domain) = 0;
  virtual void construct_paint_job(OpaquePaintJob* job) = 0;
  virtual void retain_paint_job(OpaquePaintJobHandle job) = 0;
  virtual void retain_reference(OpaqueReferenceHandle reference) = 0;
  virtual void release_reference(OpaqueReferenceHandle reference) = 0;
  virtual void release_paint_job(OpaquePaintJobHandle job) = 0;
  virtual OpaqueWord get_uint32_property(OpaqueWord property_id) = 0;
  virtual bool get_bool_property(OpaqueWord property_id) = 0;
  virtual OpaquePropertyService* get_property_service() = 0;
  virtual OpaquePropertyListHandle resolve_property_list(
      OpaqueWord source_key) = 0;
  virtual bool query_property_list(OpaquePropertyService* service) = 0;
  virtual std::size_t get_uint32_array(OpaquePropertyListHandle property_list,
                                       OpaqueWord property_id,
                                       std::array<OpaqueWord, 3>& values) = 0;
  virtual void release_property_list(
      OpaquePropertyListHandle property_list) = 0;
  virtual IBakeManager* get_bake_manager() = 0;
  virtual bool submit_bake(IBakeManager* bake_manager,
                           OpaquePaintJobHandle job) = 0;
  virtual void get_channel_record(const PaintRequest& request,
                                  std::size_t channel,
                                  std::array<OpaqueWord, 3>& record) = 0;
  virtual OpaqueWord get_channel_8c(const PaintRequest& request,
                                    std::size_t channel) = 0;
  virtual OpaqueWord get_channel_98(const PaintRequest& request,
                                    std::size_t channel) = 0;
};

bool paint_job_prepare_and_submit(
    OpaqueEditor& editor, const PaintRequest& request,
    PaintJobServices& services,
    const PaintJobModelOptions* model_options = nullptr);

}

static_assert(
    sizeof(
        openspore::reconstruction::pkg20_persistence_boundary::OpaqueEditor) ==
        0x88,
    "Opaque editor layout must remain 0x88 bytes");
static_assert(sizeof(openspore::reconstruction::pkg20_persistence_boundary::
                         OpaquePaintJob) == 0x84,
              "Opaque paint job layout must remain 0x84 bytes");
