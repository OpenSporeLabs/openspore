#include "CellContent.hpp"

#include <algorithm>
#include <utility>

namespace openspore::assets {
namespace {

uint32_t valueType(const CellContentValue& value) {
  switch (value.index()) {
    case 0:
      return CellGlobals::kType;
    case 1:
      return CellEffectMap::kType;
    case 2:
      return CellBackgroundMap::kType;
    case 3:
      return CellStructure::kType;
    case 4:
      return CellWorld::kType;
    case 5:
      return CellRandomCreature::kType;
    case 6:
      return CellPowers::kType;
    case 7:
      return CellLookTable::kType;
    case 8:
      return CellLookAlgorithm::kType;
    case 9:
      return CellLootTable::kType;
    case 10:
      return CellPopulate::kType;
    case 11:
      return CellCell::kType;
    default:
      return ResourceKey::kWildcard;
  }
}

CellContentLoadResult failure(CellContentErrorCode code, std::string error) {
  return {code, {}, std::move(error)};
}

CellContentLoadResult success(const ResourceKey& key, CellContentValue value) {
  auto record = std::make_shared<CellContentRecord>(key, std::move(value));
  return {CellContentErrorCode::ok, std::move(record), {}};
}

CellContentErrorCode mapContentError(ContentErrorCode code) {
  switch (code) {
    case ContentErrorCode::ok:
      return CellContentErrorCode::ok;
    case ContentErrorCode::invalid_key:
      return CellContentErrorCode::invalid_key;
    case ContentErrorCode::unsupported_format:
    case ContentErrorCode::unsupported_compression:
    case ContentErrorCode::unsupported_operation:
    case ContentErrorCode::malformed_index:
    case ContentErrorCode::invalid_extent:
    case ContentErrorCode::decompression_failed:
    case ContentErrorCode::size_mismatch:
    case ContentErrorCode::provider_failure:
      return CellContentErrorCode::provider_failure;
    case ContentErrorCode::invalid_input:
      return CellContentErrorCode::invalid_input;
    case ContentErrorCode::not_found:
      return CellContentErrorCode::not_found;
  }
  return CellContentErrorCode::provider_failure;
}

CellContentAddResult addFailure(CellContentErrorCode code, std::string error) {
  return {code, std::move(error)};
}

void appendReference(std::vector<CellReference>& out,
                     const CellContentRecord& record, CellReferenceField field,
                     size_t index, uint32_t type, uint32_t instance) {
  if (instance == 0) {
    return;
  }
  out.push_back(
      {record.key(), {type, ResourceKey::kWildcard, instance}, field, index});
}

void appendGlobalsReferences(std::vector<CellReference>& out,
                             const CellContentRecord& record,
                             const CellGlobals& globals) {
  for (const CellField& field : globals.fields) {
    if (field.u == 0) {
      continue;
    }
    if (field.name == "effectMapEntry") {
      appendReference(out, record, CellReferenceField::globals_effect_map, 0,
                      CellEffectMap::kType, field.u);
    } else if (field.name == "backgroundMapEntry") {
      appendReference(out, record, CellReferenceField::globals_background_map,
                      0, CellBackgroundMap::kType, field.u);
    } else if (field.name == "startCell" || field.name == "startingCellKey") {
      appendReference(out, record, CellReferenceField::globals_cell, 0,
                      CellCell::kType, field.u);
    } else if (field.name == "keyLookAlgorithm") {
      appendReference(out, record, CellReferenceField::globals_look_algorithm,
                      0, CellLookAlgorithm::kType, field.u);
    } else if (field.name == "world_1" || field.name == "world_2" ||
               field.name == "world_3" || field.name == "world_4" ||
               field.name == "world_5" || field.name == "worldBackground_1" ||
               field.name == "worldBackground_2" ||
               field.name == "worldBackground_3" ||
               field.name == "worldBackground_4" ||
               field.name == "worldBackground_5" ||
               field.name == "worldRandom" || field.name == "worldRandomBg") {
      appendReference(out, record, CellReferenceField::globals_world, 0,
                      CellWorld::kType, field.u);
    }
  }
}

void appendCellReferences(std::vector<CellReference>& out,
                          const CellContentRecord& record,
                          const CellCell& cell) {
  appendReference(out, record, CellReferenceField::cell_structure, 0,
                  CellStructure::kType, cell.structure);
  appendReference(out, record, CellReferenceField::cell_break, 0,
                  ResourceKey::kWildcard, cell.break_);
  appendReference(out, record, CellReferenceField::cell_pieces, 0,
                  ResourceKey::kWildcard, cell.pieces);
  appendReference(out, record, CellReferenceField::cell_leak, 0,
                  ResourceKey::kWildcard, cell.leak);
  appendReference(out, record, CellReferenceField::cell_expel, 0,
                  ResourceKey::kWildcard, cell.expel);
  appendReference(out, record, CellReferenceField::cell_explosion_table, 0,
                  ResourceKey::kWildcard, cell.explosionTable);
  appendReference(out, record, CellReferenceField::cell_loot, 0,
                  CellLootTable::kType, cell.loot);
  appendReference(out, record, CellReferenceField::cell_poison, 0,
                  ResourceKey::kWildcard, cell.poison);

  const CellAI* ai[] = {&cell.ai, &cell.aiHard, &cell.aiEasy};
  for (size_t index = 0; index < 3; ++index) {
    appendReference(out, record, CellReferenceField::cell_ai_spawn_output,
                    index, ResourceKey::kWildcard, ai[index]->spawnOutput);
    appendReference(out, record, CellReferenceField::cell_ai_digestion_output,
                    index, ResourceKey::kWildcard, ai[index]->digestionOutput);
  }
}

void appendWorldReferences(std::vector<CellReference>& out,
                           const CellContentRecord& record,
                           const CellWorld& world) {
  for (size_t index = 0; index < world.populate.size(); ++index) {
    appendReference(out, record, CellReferenceField::world_populate, index,
                    CellPopulate::kType, world.populate[index].populate);
  }
  for (size_t index = 0; index < world.advect.size(); ++index) {
    appendReference(out, record, CellReferenceField::world_advect, index,
                    0x04805684u, world.advect[index].advectID);
  }
}

void appendPopulateReferences(std::vector<CellReference>& out,
                              const CellContentRecord& record,
                              const CellPopulate& populate) {
  for (size_t index = 0; index < populate.markers.size(); ++index) {
    appendReference(out, record, CellReferenceField::populate_distribute_cell,
                    index, CellCell::kType,
                    populate.markers[index].distributeCell);
    appendReference(out, record, CellReferenceField::populate_cluster_cell,
                    index, CellCell::kType,
                    populate.markers[index].clusterCell);
  }
}

void appendLookReferences(std::vector<CellReference>& out,
                          const CellContentRecord& record,
                          const CellLookAlgorithm& algorithm) {
  for (size_t index = 0; index < algorithm.entries.size(); ++index) {
    const CellLookAlgoEntry& entry = algorithm.entries[index];
    appendReference(out, record, CellReferenceField::look_table, index * 3u,
                    CellLookTable::kType, entry.player);
    appendReference(out, record, CellReferenceField::look_table,
                    index * 3u + 1u, CellLookTable::kType, entry.npc);
    appendReference(out, record, CellReferenceField::look_table,
                    index * 3u + 2u, CellLookTable::kType, entry.epic);
  }
}

void appendLootReferences(std::vector<CellReference>& out,
                          const CellContentRecord& record,
                          const CellLootTable& table) {
  for (size_t index = 0; index < table.entries.size(); ++index) {
    appendReference(out, record, CellReferenceField::loot_cell, index,
                    CellCell::kType, table.entries[index].cell);
    appendReference(out, record, CellReferenceField::loot_table, index,
                    CellLootTable::kType, table.entries[index].table);
  }
}

void appendStructureReferences(std::vector<CellReference>& out,
                               const CellContentRecord& record,
                               const CellStructure& structure) {
  appendReference(out, record, CellReferenceField::structure_header_effect, 0,
                  ResourceKey::kWildcard, structure.onDeath);
  appendReference(out, record, CellReferenceField::structure_header_effect, 1,
                  ResourceKey::kWildcard, structure.onDeathSmall);
  appendReference(out, record, CellReferenceField::structure_header_effect, 2,
                  ResourceKey::kWildcard, structure.onDeathLarge);
  appendReference(out, record, CellReferenceField::structure_header_effect, 3,
                  ResourceKey::kWildcard, structure.onHatch);
  appendReference(out, record, CellReferenceField::structure_header_effect, 4,
                  ResourceKey::kWildcard, structure.onStartHatch);
  for (size_t index = 0; index < structure.atts.size(); ++index) {
    const CellStructureAtt& attachment = structure.atts[index];
    appendReference(out, record,
                    CellReferenceField::structure_attachment_structure, index,
                    CellStructure::kType, attachment.structure);
    appendReference(
        out, record, CellReferenceField::structure_attachment_random_creature,
        index, CellRandomCreature::kType, attachment.randomCreature);
    appendReference(
        out, record, CellReferenceField::structure_attachment_effect, index,
        ResourceKey::kWildcard, static_cast<uint32_t>(attachment.effectID));
  }
}

CellReferenceResult referenceFailure(CellContentErrorCode code,
                                     std::string error) {
  return {code, {}, std::move(error)};
}

}  // namespace

bool isSupportedCellContentType(uint32_t typeId) noexcept {
  return typeId == CellGlobals::kType || typeId == CellEffectMap::kType ||
         typeId == CellBackgroundMap::kType || typeId == CellStructure::kType ||
         typeId == CellWorld::kType || typeId == CellRandomCreature::kType ||
         typeId == CellPowers::kType || typeId == CellLookTable::kType ||
         typeId == CellLookAlgorithm::kType || typeId == CellLootTable::kType ||
         typeId == CellPopulate::kType || typeId == CellCell::kType;
}

CellContentRecord::CellContentRecord(ResourceKey key, CellContentValue value)
    : key_(key), value_(std::move(value)) {}

const ResourceKey& CellContentRecord::key() const noexcept { return key_; }

uint32_t CellContentRecord::type() const noexcept { return valueType(value_); }

const CellContentValue& CellContentRecord::value() const noexcept {
  return value_;
}

CellContentLoader::CellContentLoader(const IContentStore& store)
    : store_(&store) {}

CellContentLoadResult CellContentLoader::load(const ResourceKey& key) const {
  if (!key.isComplete()) {
    return failure(CellContentErrorCode::invalid_key,
                   "cell content: complete resource key required");
  }
  if (!isSupportedCellContentType(key.type)) {
    return failure(CellContentErrorCode::unsupported_type,
                   "cell content: unsupported record type");
  }
  const ReadResult bytes = store_->read(key);
  if (!bytes) {
    return failure(mapContentError(bytes.code),
                   bytes.error.empty() ? "cell content: provider read failed"
                                       : bytes.error);
  }

  std::string parseError;
  CellContentValue value;
  switch (key.type) {
    case CellGlobals::kType: {
      CellGlobals record;
      if (!parseCellGlobals(bytes.bytes.data(), bytes.bytes.size(), record,
                            parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellEffectMap::kType: {
      CellEffectMap record;
      if (!parseCellEffectMap(bytes.bytes.data(), bytes.bytes.size(), record,
                              parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellBackgroundMap::kType: {
      CellBackgroundMap record;
      if (!parseCellBackgroundMap(bytes.bytes.data(), bytes.bytes.size(),
                                  record, parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellStructure::kType: {
      CellStructure record;
      if (!parseCellStructure(bytes.bytes.data(), bytes.bytes.size(), record,
                              parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellWorld::kType: {
      CellWorld record;
      if (!parseCellWorld(bytes.bytes.data(), bytes.bytes.size(), record,
                          parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellRandomCreature::kType: {
      CellRandomCreature record;
      if (!parseCellRandomCreature(bytes.bytes.data(), bytes.bytes.size(),
                                   record, parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellPowers::kType: {
      CellPowers record;
      if (!parseCellPowers(bytes.bytes.data(), bytes.bytes.size(), record,
                           parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellLookTable::kType: {
      CellLookTable record;
      if (!parseCellLookTable(bytes.bytes.data(), bytes.bytes.size(), record,
                              parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellLookAlgorithm::kType: {
      CellLookAlgorithm record;
      if (!parseCellLookAlgorithm(bytes.bytes.data(), bytes.bytes.size(),
                                  record, parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellLootTable::kType: {
      CellLootTable record;
      if (!parseCellLootTable(bytes.bytes.data(), bytes.bytes.size(), record,
                              parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellPopulate::kType: {
      CellPopulate record;
      if (!parseCellPopulate(bytes.bytes.data(), bytes.bytes.size(), record,
                             parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    case CellCell::kType: {
      CellCell record;
      if (!parseCellCell(bytes.bytes.data(), bytes.bytes.size(), record,
                         parseError)) {
        return failure(CellContentErrorCode::decode_failed, parseError);
      }
      value = std::move(record);
      break;
    }
    default:
      return failure(CellContentErrorCode::unsupported_type,
                     "cell content: unsupported record type");
  }
  return success(key, std::move(value));
}

CellContentAddResult CellContentCatalog::add(const CellContentRecord& record) {
  auto copy = std::make_shared<CellContentRecord>(record.key(), record.value());
  return addRecord(copy);
}

CellContentAddResult CellContentCatalog::add(
    const CellContentLoadResult& loaded) {
  if (!loaded) {
    return addFailure(loaded.code, loaded.error);
  }
  if (!loaded.record) {
    return addFailure(CellContentErrorCode::malformed_record,
                      "cell content: load result has no record");
  }
  return addRecord(loaded.record);
}

CellContentAddResult CellContentCatalog::addRecord(
    const std::shared_ptr<const CellContentRecord>& record) {
  if (!record) {
    return addFailure(CellContentErrorCode::invalid_input,
                      "cell content: null catalog record");
  }
  if (!record->key().isComplete()) {
    return addFailure(CellContentErrorCode::invalid_key,
                      "cell content: catalog record key is incomplete");
  }
  if (!isSupportedCellContentType(record->type()) ||
      record->type() != record->key().type) {
    return addFailure(CellContentErrorCode::malformed_record,
                      "cell content: catalog record type mismatch");
  }
  if (byKey_.find(record->key()) != byKey_.end()) {
    return addFailure(CellContentErrorCode::duplicate_record,
                      "cell content: duplicate resource key");
  }
  byKey_.emplace(record->key(), record);
  auto& typed = byType_[record->type()];
  typed.push_back(record);
  std::sort(typed.begin(), typed.end(),
            [](const std::shared_ptr<const CellContentRecord>& left,
               const std::shared_ptr<const CellContentRecord>& right) {
              return left->key() < right->key();
            });
  return {};
}

const std::vector<std::shared_ptr<const CellContentRecord>>&
CellContentCatalog::records(uint32_t typeId) const {
  static const std::vector<std::shared_ptr<const CellContentRecord>> empty;
  const auto found = byType_.find(typeId);
  return found == byType_.end() ? empty : found->second;
}

std::shared_ptr<const CellContentRecord> CellContentCatalog::find(
    const ResourceKey& key) const {
  if (!key.isComplete()) {
    return {};
  }
  const auto found = byKey_.find(key);
  return found == byKey_.end() ? std::shared_ptr<const CellContentRecord>()
                               : found->second;
}

size_t CellContentCatalog::size() const noexcept { return byKey_.size(); }

CellReferenceResolver::CellReferenceResolver(const ICellContentCatalog& catalog)
    : catalog_(&catalog) {}

std::vector<CellReference> CellReferenceResolver::references(
    const CellContentRecord& record) const {
  std::vector<CellReference> out;
  if (!record.key().isComplete() || record.type() != record.key().type) {
    return out;
  }
  if (const auto* globals = record.as<CellGlobals>()) {
    appendGlobalsReferences(out, record, *globals);
  } else if (const auto* cell = record.as<CellCell>()) {
    appendCellReferences(out, record, *cell);
  } else if (const auto* world = record.as<CellWorld>()) {
    appendWorldReferences(out, record, *world);
  } else if (const auto* populate = record.as<CellPopulate>()) {
    appendPopulateReferences(out, record, *populate);
  } else if (const auto* algorithm = record.as<CellLookAlgorithm>()) {
    appendLookReferences(out, record, *algorithm);
  } else if (const auto* table = record.as<CellLootTable>()) {
    appendLootReferences(out, record, *table);
  } else if (const auto* structure = record.as<CellStructure>()) {
    appendStructureReferences(out, record, *structure);
  }
  return out;
}

CellReferenceResult CellReferenceResolver::resolve(
    const CellContentRecord& record, const CellReference& reference) const {
  if (!record.key().isComplete()) {
    return referenceFailure(CellContentErrorCode::invalid_key,
                            "cell reference: complete source key required");
  }
  if (record.type() != record.key().type) {
    return referenceFailure(CellContentErrorCode::malformed_record,
                            "cell reference: malformed source record");
  }
  if (!reference.source.isComplete()) {
    return referenceFailure(CellContentErrorCode::invalid_key,
                            "cell reference: complete source key required");
  }
  if (reference.source != record.key()) {
    return referenceFailure(CellContentErrorCode::reference_source_mismatch,
                            "cell reference: source key does not match record");
  }
  if (reference.target.instance == ResourceKey::kWildcard) {
    return referenceFailure(CellContentErrorCode::invalid_reference,
                            "cell reference: target instance is missing");
  }
  if (reference.target.type != ResourceKey::kWildcard &&
      !isSupportedCellContentType(reference.target.type)) {
    return referenceFailure(CellContentErrorCode::unsupported_type,
                            "cell reference: target type is not supported");
  }

  const std::vector<CellReference> actual = references(record);
  const CellReference* matched = nullptr;
  for (const CellReference& candidate : actual) {
    if (candidate.field == reference.field &&
        candidate.index == reference.index &&
        candidate.target.instance == reference.target.instance) {
      matched = &candidate;
      break;
    }
  }
  if (matched == nullptr) {
    return referenceFailure(
        CellContentErrorCode::invalid_reference,
        "cell reference: field is not a matching hard reference");
  }
  if (matched->target.type == ResourceKey::kWildcard ||
      !isSupportedCellContentType(matched->target.type)) {
    return referenceFailure(CellContentErrorCode::unsupported_type,
                            "cell reference: target type is not supported");
  }
  if (reference.target.type != ResourceKey::kWildcard &&
      reference.target.type != matched->target.type) {
    return referenceFailure(CellContentErrorCode::reference_type_mismatch,
                            "cell reference: target type does not match field");
  }
  if (matched->target.group != ResourceKey::kWildcard &&
      reference.target.group != ResourceKey::kWildcard &&
      reference.target.group != matched->target.group) {
    return referenceFailure(
        CellContentErrorCode::reference_type_mismatch,
        "cell reference: target group does not match field");
  }

  const auto& typed = catalog_->records(matched->target.type);
  std::shared_ptr<const CellContentRecord> found;
  for (const auto& candidate : typed) {
    if (candidate->key().instance != matched->target.instance) {
      continue;
    }
    if (reference.target.group != ResourceKey::kWildcard &&
        candidate->key().group != reference.target.group) {
      continue;
    }
    if (found) {
      return referenceFailure(CellContentErrorCode::ambiguous_reference,
                              "cell reference: instance is ambiguous");
    }
    found = candidate;
  }
  if (!found) {
    return referenceFailure(CellContentErrorCode::reference_not_found,
                            "cell reference: target record not found");
  }
  return {CellContentErrorCode::ok,
          {found->key(), found->type(), matched->field, matched->index, found},
          {}};
}

}  // namespace openspore::assets
