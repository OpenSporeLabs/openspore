#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg20_persistence_boundary {

inline constexpr std::uintptr_t kEditorCurrentPaintJobOffset = 0x5c;
inline constexpr std::uintptr_t kEditorSourceOffset = 0x1c;
inline constexpr std::uintptr_t kEditorResourceAOffset = 0x64;
inline constexpr std::uintptr_t kEditorResourceBOffset = 0x68;
inline constexpr std::uintptr_t kEditorResourceCOffset = 0x6c;
inline constexpr std::uintptr_t kEditorStateFlagOffset = 0x84;
inline constexpr std::size_t kOpaqueEditorSize = 0x88;
inline constexpr std::size_t kOpaquePaintJobSize = 0x84;
inline constexpr std::uint32_t kPaintQualityProperty = 0xb8864eac;
inline constexpr std::uint32_t kPaintFeatureProperty = 0x2853e342;
inline constexpr std::uint32_t kChannelFallbackProperty = 0x05e68c2e;
inline constexpr std::uint32_t kDisableFeatureModelType = 0x3d97a8e4;
inline constexpr std::uint32_t kDisableChannelOverrideModelType = 0x438f6347;
inline constexpr std::uint32_t kSingleModelType = 0x2b978c46;
inline constexpr std::uint32_t kMinimumPaintLimit = 0x40;
inline constexpr std::array<std::uint32_t, 5> kLiveProfileModes{
    0x1654c00u, 0x1654c01u, 0x1654c02u, 0x1654c04u, 0x1654c05u};

struct OpaqueEditor {
  std::array<std::uint8_t, kOpaqueEditorSize> bytes{};
};

using OpaquePaintJob = std::array<std::uint8_t, kOpaquePaintJobSize>;
using OpaquePaintJobHandle = std::uint32_t;
using OpaqueReferenceHandle = std::uint32_t;
using OpaquePropertyListHandle = std::uint32_t;

inline constexpr OpaquePaintJobHandle kInvalidPaintJobHandle = 0;
inline constexpr OpaqueReferenceHandle kInvalidReferenceHandle = 0;
inline constexpr OpaquePropertyListHandle kInvalidPropertyListHandle = 0;

struct PaintRequest {
  std::uint32_t field_0x10 = 0;
  std::uint32_t field_0x58 = 0;
  std::array<std::uint32_t, 3> field_0x8c{};
  std::array<std::uint32_t, 3> field_0x98{};
  std::array<std::array<std::uint32_t, 3>, 3> field_0xa4{};
};

class PaintBoundaryServices {
 public:
  virtual ~PaintBoundaryServices() = default;

  virtual void notify_paint_system_cancel(OpaquePaintJobHandle job) = 0;
  virtual void prepare_paint_resource(
      std::uint32_t resource_a, std::uint32_t resource_c,
      const std::array<std::uint32_t, 3>& record) = 0;
  virtual OpaquePaintJobHandle allocate_paint_job() = 0;
  virtual void construct_paint_job(OpaquePaintJobHandle job) = 0;
  virtual OpaquePaintJob* resolve_paint_job(OpaquePaintJobHandle job) = 0;
  virtual void retain_reference(OpaqueReferenceHandle reference) = 0;
  virtual void release_reference(OpaqueReferenceHandle reference) = 0;
  virtual void release_paint_job(OpaquePaintJobHandle job) = 0;
  virtual std::uint32_t get_uint32_property(std::uint32_t property_id) = 0;
  virtual bool get_bool_property(std::uint32_t property_id) = 0;
  virtual OpaquePropertyListHandle resolve_property_list(
      std::uint32_t source_key) = 0;
  virtual bool query_property_list() = 0;
  virtual std::size_t get_uint32_array(
      OpaquePropertyListHandle property_list, std::uint32_t property_id,
      std::array<std::uint32_t, 3>& values) = 0;
  virtual void release_property_list(
      OpaquePropertyListHandle property_list) = 0;
  virtual bool submit_bake(OpaquePaintJobHandle job) = 0;
};

class PaintPersistenceBoundary {
 public:
  explicit PaintPersistenceBoundary(PaintBoundaryServices& services);

  bool submit(OpaqueEditor& editor, const PaintRequest& request);

 private:
  PaintBoundaryServices& services_;
};

struct ProfilePersistenceRequest {
  const char16_t* path = nullptr;
  std::uint32_t candidate_marker = 0;
};

struct OpaqueSpeciesContext;
struct OpaqueProfileTarget;
struct OpaqueModeTarget;

class ProfilePersistenceCandidateServices {
 public:
  virtual ~ProfilePersistenceCandidateServices() = default;

  virtual void initialize_candidate() = 0;
  virtual OpaqueSpeciesContext* acquire_species_context() = 0;
  virtual bool can_load_primary_candidate() = 0;
  virtual OpaqueProfileTarget* load_primary_candidate() = 0;
  virtual OpaqueProfileTarget* load_secondary_candidate() = 0;
  virtual void apply_species_context(OpaqueSpeciesContext* context) = 0;
  virtual std::uint32_t read_mode() = 0;
  virtual void set_mode(std::uint32_t mode) = 0;
  virtual void write_mode(std::uint32_t mode) = 0;
  virtual OpaqueModeTarget* replace_mode_target() = 0;
  virtual void bind_mode_target(OpaqueModeTarget* target) = 0;
  virtual void configure_mode_target(OpaqueModeTarget* target) = 0;
  virtual void run_mode_target_cleanup(OpaqueModeTarget* target) = 0;
  virtual void set_profile_path(OpaqueProfileTarget* target,
                                const char16_t* path) = 0;
  virtual void release_profile_target(OpaqueProfileTarget* target) = 0;
  virtual void build_profile_context(const char16_t* path) = 0;
  virtual void run_temporary_profile(const char16_t* path) = 0;
  virtual void replace_temporary_profile(const char16_t* path) = 0;
  virtual bool read_completion_path() = 0;
  virtual void run_completion_path(bool alternate) = 0;
  virtual void finalize_candidate() = 0;
};

class ProfilePersistenceBoundary {
 public:
  explicit ProfilePersistenceBoundary(
      ProfilePersistenceCandidateServices& services);

  void run_candidate(const ProfilePersistenceRequest& request);

 private:
  ProfilePersistenceCandidateServices& services_;
};

}
