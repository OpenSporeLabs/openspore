#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "CellResource.hpp"
#include "ResourceKey.hpp"
#include "ResourceStore.hpp"

namespace openspore::assets {

using CellContentValue =
    std::variant<CellGlobals, CellEffectMap, CellBackgroundMap, CellStructure,
                 CellWorld, CellRandomCreature, CellPowers, CellLookTable,
                 CellLookAlgorithm, CellLootTable, CellPopulate, CellCell>;

bool isSupportedCellContentType(uint32_t typeId) noexcept;

class CellContentRecord final {
 public:
  CellContentRecord(ResourceKey key, CellContentValue value);

  const ResourceKey& key() const noexcept;
  uint32_t type() const noexcept;
  const CellContentValue& value() const noexcept;

  template <typename T>
  const T* as() const {
    return std::get_if<T>(&value_);
  }

 private:
  const ResourceKey key_;
  const CellContentValue value_;
};

enum class CellContentErrorCode {
  ok,
  invalid_key,
  unsupported_type,
  invalid_input,
  not_found,
  provider_failure,
  decode_failed,
  malformed_record,
  duplicate_record,
  invalid_reference,
  reference_source_mismatch,
  reference_type_mismatch,
  reference_not_found,
  ambiguous_reference,
};

struct CellContentLoadResult {
  CellContentErrorCode code = CellContentErrorCode::ok;
  std::shared_ptr<const CellContentRecord> record;
  std::string error;

  explicit operator bool() const { return code == CellContentErrorCode::ok; }
};

struct CellContentAddResult {
  CellContentErrorCode code = CellContentErrorCode::ok;
  std::string error;

  explicit operator bool() const { return code == CellContentErrorCode::ok; }
};

class ICellContentCatalog {
 public:
  virtual ~ICellContentCatalog() = default;

  virtual const std::vector<std::shared_ptr<const CellContentRecord>>& records(
      uint32_t typeId) const = 0;
};

class CellContentCatalog final : public ICellContentCatalog {
 public:
  CellContentCatalog() = default;

  CellContentAddResult add(const CellContentRecord& record);
  CellContentAddResult add(const CellContentLoadResult& loaded);

  const std::vector<std::shared_ptr<const CellContentRecord>>& records(
      uint32_t typeId) const override;

  std::shared_ptr<const CellContentRecord> find(const ResourceKey& key) const;
  size_t size() const noexcept;

 private:
  CellContentAddResult addRecord(
      const std::shared_ptr<const CellContentRecord>& record);

  std::map<ResourceKey, std::shared_ptr<const CellContentRecord>> byKey_;
  std::map<uint32_t, std::vector<std::shared_ptr<const CellContentRecord>>>
      byType_;
};

class ICellContentLoader {
 public:
  virtual ~ICellContentLoader() = default;

  virtual CellContentLoadResult load(const ResourceKey& key) const = 0;
};

class CellContentLoader final : public ICellContentLoader {
 public:
  explicit CellContentLoader(const IContentStore& store);

  CellContentLoadResult load(const ResourceKey& key) const override;

 private:
  const IContentStore* store_ = nullptr;
};

enum class CellReferenceField {
  none,
  globals_world,
  globals_effect_map,
  globals_background_map,
  globals_cell,
  globals_look_algorithm,
  cell_structure,
  cell_break,
  cell_pieces,
  cell_leak,
  cell_expel,
  cell_explosion_table,
  cell_loot,
  cell_poison,
  cell_ai_spawn_output,
  cell_ai_digestion_output,
  world_populate,
  world_advect,
  populate_distribute_cell,
  populate_cluster_cell,
  look_table,
  loot_cell,
  loot_table,
  structure_header_effect,
  structure_attachment_structure,
  structure_attachment_random_creature,
  structure_attachment_effect,
};

struct CellReference {
  ResourceKey source;
  ResourceKey target;
  CellReferenceField field = CellReferenceField::none;
  size_t index = 0;
};

struct CellReferenceResolution {
  ResourceKey key;
  uint32_t type = 0;
  CellReferenceField field = CellReferenceField::none;
  size_t index = 0;
  std::shared_ptr<const CellContentRecord> record;

  explicit operator bool() const { return record != nullptr; }
};

struct CellReferenceResult {
  CellContentErrorCode code = CellContentErrorCode::ok;
  CellReferenceResolution value;
  std::string error;

  explicit operator bool() const { return code == CellContentErrorCode::ok; }
};

class ICellReferenceResolver {
 public:
  virtual ~ICellReferenceResolver() = default;

  virtual CellReferenceResult resolve(const CellContentRecord& record,
                                      const CellReference& reference) const = 0;
};

class CellReferenceResolver final : public ICellReferenceResolver {
 public:
  explicit CellReferenceResolver(const ICellContentCatalog& catalog);

  CellReferenceResult resolve(const CellContentRecord& record,
                              const CellReference& reference) const override;

  std::vector<CellReference> references(const CellContentRecord& record) const;

 private:
  const ICellContentCatalog* catalog_ = nullptr;
};

}  // namespace openspore::assets
