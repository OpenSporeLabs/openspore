#include <cstdint>
#include <cstdio>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "CellContent.hpp"

namespace {

int failures = 0;

void check(bool condition, const char* label) {
  if (condition) {
    std::printf("ok: %s\n", label);
  } else {
    std::printf("FAIL: %s\n", label);
    ++failures;
  }
}

void setU32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  bytes[offset] = static_cast<uint8_t>(value & 0xFFu);
  bytes[offset + 1] = static_cast<uint8_t>((value >> 8u) & 0xFFu);
  bytes[offset + 2] = static_cast<uint8_t>((value >> 16u) & 0xFFu);
  bytes[offset + 3] = static_cast<uint8_t>((value >> 24u) & 0xFFu);
}

std::vector<uint8_t> makeCell() {
  std::vector<uint8_t> bytes(openspore::assets::CellCell::kSize, 0);
  setU32(bytes, 0, 0xABCDu);
  return bytes;
}

std::vector<uint8_t> makePopulate() {
  std::vector<uint8_t> bytes(16 + 76, 0);
  setU32(bytes, 8, 1);
  setU32(bytes, 40, 0x20u);
  setU32(bytes, 44, 0);
  return bytes;
}

std::vector<uint8_t> makeWorldAdvect() {
  std::vector<uint8_t> bytes(16 + 24, 0);
  setU32(bytes, 8, 1);
  setU32(bytes, 36, 0x55u);
  return bytes;
}

std::vector<uint8_t> makeRandomCreature() {
  std::vector<uint8_t> bytes(8 + 28, 0);
  setU32(bytes, 0, 1);
  setU32(bytes, 8, 0x1234u);
  return bytes;
}

struct DirectFixture {
  uint32_t type;
  size_t size;
  size_t variantIndex;
};

const DirectFixture kDirectFixtures[] = {
    {openspore::assets::CellGlobals::kType, 276, 0},
    {openspore::assets::CellEffectMap::kType, 8, 1},
    {openspore::assets::CellBackgroundMap::kType, 8, 2},
    {openspore::assets::CellStructure::kType, 28, 3},
    {openspore::assets::CellWorld::kType, 16, 4},
    {openspore::assets::CellRandomCreature::kType, 8, 5},
    {openspore::assets::CellPowers::kType, 8, 6},
    {openspore::assets::CellLookTable::kType, 8, 7},
    {openspore::assets::CellLookAlgorithm::kType, 8, 8},
    {openspore::assets::CellLootTable::kType, 36, 9},
    {openspore::assets::CellPopulate::kType, 16, 10},
    {openspore::assets::CellCell::kType, 796, 11},
};

struct CountedFixture {
  uint32_t type;
  size_t countOffset;
  size_t headerSize;
  size_t entrySize;
};

const CountedFixture kCountedFixtures[] = {
    {openspore::assets::CellEffectMap::kType, 0, 8, 28},
    {openspore::assets::CellBackgroundMap::kType, 0, 8, 16},
    {openspore::assets::CellStructure::kType, 24, 28, 40},
    {openspore::assets::CellRandomCreature::kType, 0, 8, 28},
    {openspore::assets::CellLookTable::kType, 4, 8, 8},
    {openspore::assets::CellLookAlgorithm::kType, 4, 8, 20},
    {openspore::assets::CellLootTable::kType, 4, 36, 28},
    {openspore::assets::CellPopulate::kType, 8, 16, 76},
};

struct DecodedCounts {
  int first = 0;
  int second = 0;
  size_t entries = 0;
};

DecodedCounts decodedCounts(const openspore::assets::CellContentValue& value) {
  using namespace openspore::assets;
  return std::visit(
      [](const auto& record) {
        using Record = std::decay_t<decltype(record)>;
        if constexpr (std::is_same_v<Record, CellEffectMap>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellBackgroundMap>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellStructure>) {
          return DecodedCounts{record.numAttachments, 0, record.atts.size()};
        } else if constexpr (std::is_same_v<Record, CellWorld>) {
          return DecodedCounts{static_cast<int>(record.numPopulate),
                               static_cast<int>(record.numAdvect),
                               record.populate.size() + record.advect.size()};
        } else if constexpr (std::is_same_v<Record, CellRandomCreature>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellLookTable>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellLookAlgorithm>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellLootTable>) {
          return DecodedCounts{record.numEntries, 0, record.entries.size()};
        } else if constexpr (std::is_same_v<Record, CellPopulate>) {
          return DecodedCounts{static_cast<int>(record.numMarkers), 0,
                               record.markers.size()};
        } else {
          return DecodedCounts{};
        }
      },
      value);
}

bool sameGlobals(const openspore::assets::CellGlobals& left,
                 const openspore::assets::CellGlobals& right) {
  if (left.size != right.size || left.fields.size() != right.fields.size()) {
    return false;
  }
  for (size_t index = 0; index < left.fields.size(); ++index) {
    const openspore::assets::CellField& a = left.fields[index];
    const openspore::assets::CellField& b = right.fields[index];
    if (a.name != b.name || a.offset != b.offset || a.isFloat != b.isFloat ||
        a.u != b.u || a.f != b.f) {
      return false;
    }
  }
  return true;
}

bool sameCellContentValue(const openspore::assets::CellContentValue& left,
                          const openspore::assets::CellContentValue& right) {
  using namespace openspore::assets;
  if (left.index() != right.index()) {
    return false;
  }
  if (const auto* a = std::get_if<CellGlobals>(&left)) {
    return sameGlobals(*a, *std::get_if<CellGlobals>(&right));
  }
  if (const auto* a = std::get_if<CellEffectMap>(&left)) {
    return a->dump() == std::get_if<CellEffectMap>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellBackgroundMap>(&left)) {
    return a->dump() == std::get_if<CellBackgroundMap>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellStructure>(&left)) {
    return a->dump() == std::get_if<CellStructure>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellWorld>(&left)) {
    return a->dump() == std::get_if<CellWorld>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellRandomCreature>(&left)) {
    return a->dump() == std::get_if<CellRandomCreature>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellPowers>(&left)) {
    return a->dump() == std::get_if<CellPowers>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellLookTable>(&left)) {
    return a->dump() == std::get_if<CellLookTable>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellLookAlgorithm>(&left)) {
    return a->dump() == std::get_if<CellLookAlgorithm>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellLootTable>(&left)) {
    return a->dump() == std::get_if<CellLootTable>(&right)->dump();
  }
  if (const auto* a = std::get_if<CellPopulate>(&left)) {
    return a->dump() == std::get_if<CellPopulate>(&right)->dump();
  }
  return std::get<CellCell>(left).dump() == std::get<CellCell>(right).dump();
}

void testDirectParserDependencies() {
  using namespace openspore::assets;
  std::string error;
  CellGlobals globals;
  CellEffectMap effectMap;
  CellBackgroundMap backgroundMap;
  CellStructure structure;
  CellWorld world;
  CellRandomCreature randomCreature;
  CellPowers powers;
  CellLookTable lookTable;
  CellLookAlgorithm lookAlgorithm;
  CellLootTable lootTable;
  CellPopulate populate;
  CellCell cell;
  const std::vector<uint8_t> globalsBytes(276, 0);
  const std::vector<uint8_t> effectMapBytes(8, 0);
  const std::vector<uint8_t> backgroundMapBytes(8, 0);
  const std::vector<uint8_t> structureBytes(28, 0);
  const std::vector<uint8_t> worldBytes(16, 0);
  const std::vector<uint8_t> randomCreatureBytes(8, 0);
  const std::vector<uint8_t> powersBytes(8, 0);
  const std::vector<uint8_t> lookTableBytes(8, 0);
  const std::vector<uint8_t> lookAlgorithmBytes(8, 0);
  const std::vector<uint8_t> lootTableBytes(36, 0);
  const std::vector<uint8_t> populateBytes(16, 0);
  const std::vector<uint8_t> cellBytes(CellCell::kSize, 0);

  check(parseCellGlobals(globalsBytes.data(), globalsBytes.size(), globals,
                         error) &&
            globals.complete(),
        "parser dependency: Globals accepts its fixed direct layout");
  check(parseCellEffectMap(effectMapBytes.data(), effectMapBytes.size(),
                           effectMap, error),
        "parser dependency: EffectMap accepts an empty direct table");
  check(parseCellBackgroundMap(backgroundMapBytes.data(),
                               backgroundMapBytes.size(), backgroundMap, error),
        "parser dependency: BackgroundMap accepts an empty direct table");
  check(parseCellStructure(structureBytes.data(), structureBytes.size(),
                           structure, error),
        "parser dependency: Structure accepts an empty direct table");
  check(parseCellWorld(worldBytes.data(), worldBytes.size(), world, error),
        "parser dependency: World accepts empty direct arrays");
  check(parseCellRandomCreature(randomCreatureBytes.data(),
                                randomCreatureBytes.size(), randomCreature,
                                error),
        "parser dependency: RandomCreature accepts an empty direct table");
  check(parseCellPowers(powersBytes.data(), powersBytes.size(), powers, error),
        "parser dependency: Powers accepts its fixed direct layout");
  check(parseCellLookTable(lookTableBytes.data(), lookTableBytes.size(),
                           lookTable, error),
        "parser dependency: LookTable accepts an empty direct table");
  check(parseCellLookAlgorithm(lookAlgorithmBytes.data(),
                               lookAlgorithmBytes.size(), lookAlgorithm, error),
        "parser dependency: LookAlgorithm accepts an empty direct table");
  check(parseCellLootTable(lootTableBytes.data(), lootTableBytes.size(),
                           lootTable, error),
        "parser dependency: LootTable accepts an empty direct table");
  check(parseCellPopulate(populateBytes.data(), populateBytes.size(), populate,
                          error),
        "parser dependency: Populate accepts empty direct arrays");
  check(parseCellCell(cellBytes.data(), cellBytes.size(), cell, error),
        "parser dependency: Cell accepts its fixed direct layout");
}

class MemoryStore final : public openspore::assets::IContentStore {
 public:
  void put(const openspore::assets::ResourceKey& key,
           std::vector<uint8_t> bytes) {
    records_[key] = std::move(bytes);
  }

  void putReadFailure(const openspore::assets::ResourceKey& key,
                      openspore::assets::ContentErrorCode code,
                      std::string error) {
    readFailures_[key] = {code, {}, std::move(error)};
  }

  openspore::assets::LookupResult lookup(
      const openspore::assets::ResourceKey& key) const override {
    if (!key.isComplete()) {
      return {openspore::assets::ContentErrorCode::invalid_key,
              {},
              "test store: incomplete key"};
    }
    if (records_.find(key) == records_.end()) {
      return {openspore::assets::ContentErrorCode::not_found,
              {},
              "test store: missing key"};
    }
    return {openspore::assets::ContentErrorCode::ok,
            {key, 0, 0, records_.at(key).size(), records_.at(key).size(), 0},
            {}};
  }

  openspore::assets::ReadResult read(
      const openspore::assets::ResourceKey& key) const override {
    if (!key.isComplete()) {
      return {openspore::assets::ContentErrorCode::invalid_key,
              {},
              "test store: incomplete key"};
    }
    const auto failure = readFailures_.find(key);
    if (failure != readFailures_.end()) {
      return failure->second;
    }
    const auto found = records_.find(key);
    if (found == records_.end()) {
      return {openspore::assets::ContentErrorCode::not_found,
              {},
              "test store: missing key"};
    }
    return {openspore::assets::ContentErrorCode::ok, found->second, {}};
  }

 private:
  std::map<openspore::assets::ResourceKey, std::vector<uint8_t>> records_;
  std::map<openspore::assets::ResourceKey, openspore::assets::ReadResult>
      readFailures_;
};

void testLoaderAndCatalog() {
  using namespace openspore::assets;
  MemoryStore store;
  const ResourceKey cellKey{CellCell::kType, 1, 0x20};
  const ResourceKey populateKey{CellPopulate::kType, 1, 0x30};
  const ResourceKey advectWorldKey{CellWorld::kType, 1, 0x40};
  const ResourceKey randomKey{CellRandomCreature::kType, 1, 0x50};
  const ResourceKey badPowersKey{CellPowers::kType, 1, 0x60};
  store.put(cellKey, makeCell());
  store.put(populateKey, makePopulate());
  store.put(advectWorldKey, makeWorldAdvect());
  store.put(randomKey, makeRandomCreature());
  store.put(badPowersKey, {1, 2, 3});

  CellContentLoader loader(store);
  const CellContentLoadResult cell = loader.load(cellKey);
  const CellContentLoadResult populate = loader.load(populateKey);
  const CellContentLoadResult world = loader.load(advectWorldKey);
  const CellContentLoadResult random = loader.load(randomKey);
  check(cell && cell.record->type() == CellCell::kType &&
            cell.record->as<CellCell>() != nullptr,
        "loader: fixed Cell record is typed and immutable");
  check(populate && populate.record->as<CellPopulate>() != nullptr,
        "loader: Populate record is typed");
  check(world && world.record->as<CellWorld>() != nullptr,
        "loader: World record is typed");
  check(random && random.record->as<CellRandomCreature>() != nullptr,
        "loader: RandomCreature record is typed");
  check(loader.load({ResourceKey::kWildcard, 1, 1}).code ==
            CellContentErrorCode::invalid_key,
        "loader: incomplete key rejected");
  check(loader.load({0x12345678u, 1, 1}).code ==
            CellContentErrorCode::unsupported_type,
        "loader: live or unknown type rejected");
  check(loader.load(badPowersKey).code == CellContentErrorCode::decode_failed,
        "loader: malformed direct record rejected");

  CellContentCatalog catalog;
  check(catalog.add(cell) && catalog.add(populate) && catalog.add(world) &&
            catalog.add(random),
        "catalog: supported typed records insert");
  check(catalog.add(cell).code == CellContentErrorCode::duplicate_record,
        "catalog: complete resource key identity rejects duplicate");
  check(catalog.records(CellCell::kType).size() == 1 &&
            catalog.records(CellPopulate::kType).size() == 1 &&
            catalog.records(CellWorld::kType).size() == 1,
        "catalog: records are grouped by type");
  check(catalog.find(cellKey) == cell.record,
        "catalog: exact type group instance lookup");
}

void testAllDirectLoads() {
  using namespace openspore::assets;
  MemoryStore store;
  CellContentLoader loader(store);
  CellContentCatalog catalog;

  for (size_t index = 0;
       index < sizeof(kDirectFixtures) / sizeof(DirectFixture); ++index) {
    const DirectFixture& fixture = kDirectFixtures[index];
    const uint32_t group = static_cast<uint32_t>(0x100u + index);
    const uint32_t instance = static_cast<uint32_t>(0x200u + index);
    const ResourceKey key{fixture.type, group, instance};
    store.put(key, std::vector<uint8_t>(fixture.size, 0));
    const CellContentLoadResult first = loader.load(key);
    const CellContentLoadResult second = loader.load(key);
    check(isSupportedCellContentType(fixture.type) && first && first.record &&
              first.record->key() == key &&
              first.record->type() == fixture.type &&
              first.record->value().index() == fixture.variantIndex,
          "loader: every direct TypeID selects its typed variant");
    check(
        second && second.record &&
            sameCellContentValue(first.record->value(), second.record->value()),
        "loader: repeated direct-record decode is deterministic");
    check(static_cast<bool>(catalog.add(first)),
          "catalog: every direct typed record is accepted");

    const ResourceKey malformedKey{fixture.type, group + 0x1000u,
                                   instance + 0x1000u};
    store.put(malformedKey, std::vector<uint8_t>(fixture.size - 1u, 0));
    check(loader.load(malformedKey).code == CellContentErrorCode::decode_failed,
          "loader: every direct TypeID rejects a truncated payload");
  }

  const ResourceKey missing{CellPowers::kType, 0x700u, 0x800u};
  check(loader.load(missing).code == CellContentErrorCode::not_found,
        "loader: missing content record is explicit");
  const ResourceKey providerFailure{CellPowers::kType, 0x700u, 0x801u};
  store.putReadFailure(providerFailure, ContentErrorCode::unsupported_format,
                       "test store: unsupported package format");
  check(loader.load(providerFailure).code ==
            CellContentErrorCode::provider_failure,
        "loader: provider format failure is not mislabeled as TypeID");

  const ResourceKey highPowers{CellPowers::kType, 3, 0x900u};
  const ResourceKey lowPowers{CellPowers::kType, 1, 0xA00u};
  store.put(highPowers, std::vector<uint8_t>(8, 0));
  store.put(lowPowers, std::vector<uint8_t>(8, 0));
  const CellContentLoadResult high = loader.load(highPowers);
  const CellContentLoadResult low = loader.load(lowPowers);
  check(catalog.add(high) && catalog.add(low),
        "catalog: repeated-type records insert independently");
  const auto& powers = catalog.records(CellPowers::kType);
  check(powers.size() == 3 && powers[0]->key().group == 1 &&
            powers[1]->key().group == 3,
        "catalog: repeated-type records use deterministic key order");
  check(catalog.add(high).code == CellContentErrorCode::duplicate_record &&
            catalog.find(highPowers) == high.record,
        "catalog: duplicate insert preserves the first immutable record");

  const CellContentRecord mismatched({CellPowers::kType, 0xB00u, 0xC00u},
                                     CellGlobals{});
  check(catalog.add(mismatched).code == CellContentErrorCode::malformed_record,
        "catalog: key/value TypeID mismatch is rejected");
  const CellContentLoadResult missingRecord{
      CellContentErrorCode::ok, nullptr, {}};
  check(
      catalog.add(missingRecord).code == CellContentErrorCode::malformed_record,
      "catalog: successful result without a record is rejected");

  const ICellContentLoader& loaderApi = loader;
  const ICellContentCatalog& catalogApi = catalog;
  check(loaderApi.load(missing).code == CellContentErrorCode::not_found &&
            catalogApi.records(CellPowers::kType).size() == 3,
        "API: loader and catalog interfaces expose typed operations");
}

void testCountedRecordExtents() {
  using namespace openspore::assets;
  MemoryStore store;
  CellContentLoader loader(store);

  for (size_t index = 0;
       index < sizeof(kCountedFixtures) / sizeof(CountedFixture); ++index) {
    const CountedFixture& fixture = kCountedFixtures[index];
    const uint32_t group = static_cast<uint32_t>(0x300u + index);
    const ResourceKey key{fixture.type, group,
                          static_cast<uint32_t>(0x400u + index)};
    std::vector<uint8_t> bytes(fixture.headerSize + fixture.entrySize, 0);
    setU32(bytes, fixture.countOffset, 1);
    store.put(key, bytes);

    const CellContentLoadResult first = loader.load(key);
    const DecodedCounts counts =
        first ? decodedCounts(first.record->value()) : DecodedCounts{};
    check(
        first && counts.first == 1 && counts.second == 0 && counts.entries == 1,
        "counted direct record: header count matches decoded extent");

    const ResourceKey trailingKey{fixture.type, group,
                                  static_cast<uint32_t>(0x500u + index)};
    std::vector<uint8_t> trailing = bytes;
    trailing.push_back(0);
    store.put(trailingKey, std::move(trailing));
    check(loader.load(trailingKey).code == CellContentErrorCode::decode_failed,
          "counted direct record: trailing bytes are rejected");

    const ResourceKey shortKey{fixture.type, group,
                               static_cast<uint32_t>(0x600u + index)};
    std::vector<uint8_t> shortBytes = bytes;
    setU32(shortBytes, fixture.countOffset, 2);
    store.put(shortKey, std::move(shortBytes));
    check(loader.load(shortKey).code == CellContentErrorCode::decode_failed,
          "counted direct record: short table is rejected");

    const ResourceKey extremeKey{fixture.type, group,
                                 static_cast<uint32_t>(0x700u + index)};
    std::vector<uint8_t> extremeBytes(fixture.headerSize, 0);
    setU32(extremeBytes, fixture.countOffset, 0xFFFFFFFFu);
    store.put(extremeKey, std::move(extremeBytes));
    check(
        loader.load(extremeKey).code == CellContentErrorCode::decode_failed,
        "counted direct record: extreme count is rejected without wraparound");
  }

  const ResourceKey worldKey{CellWorld::kType, 0x390u, 0x790u};
  std::vector<uint8_t> worldBytes(16 + 12 + 24, 0);
  setU32(worldBytes, 0, 1);
  setU32(worldBytes, 8, 1);
  setU32(worldBytes, 16, 0x31u);
  setU32(worldBytes, 48, 0x41u);
  store.put(worldKey, worldBytes);
  const CellContentLoadResult world = loader.load(worldKey);
  const DecodedCounts worldCounts =
      world ? decodedCounts(world.record->value()) : DecodedCounts{};
  check(world && worldCounts.first == 1 && worldCounts.second == 1 &&
            worldCounts.entries == 2,
        "counted world record: both counts match decoded extents");

  const ResourceKey worldTrailingKey{CellWorld::kType, 0x390u, 0x791u};
  worldBytes.push_back(0);
  store.put(worldTrailingKey, std::move(worldBytes));
  check(
      loader.load(worldTrailingKey).code == CellContentErrorCode::decode_failed,
      "counted world record: trailing bytes are rejected");

  const ResourceKey worldShortKey{CellWorld::kType, 0x390u, 0x792u};
  std::vector<uint8_t> worldShort(16 + 12 + 24, 0);
  setU32(worldShort, 0, 1);
  setU32(worldShort, 8, 2);
  store.put(worldShortKey, std::move(worldShort));
  check(loader.load(worldShortKey).code == CellContentErrorCode::decode_failed,
        "counted world record: short second table is rejected");

  const ResourceKey worldExtremeKey{CellWorld::kType, 0x390u, 0x793u};
  std::vector<uint8_t> worldExtreme(16, 0);
  setU32(worldExtreme, 0, 0xFFFFFFFFu);
  store.put(worldExtremeKey, std::move(worldExtreme));
  check(
      loader.load(worldExtremeKey).code == CellContentErrorCode::decode_failed,
      "counted world record: extreme populate count is rejected");
}

void testResolver() {
  using namespace openspore::assets;
  MemoryStore store;
  const ResourceKey cellKey{CellCell::kType, 1, 0x20};
  const ResourceKey otherCellKey{CellCell::kType, 2, 0x20};
  const ResourceKey populateKey{CellPopulate::kType, 1, 0x30};
  const ResourceKey worldKey{CellWorld::kType, 1, 0x40};
  const ResourceKey randomKey{CellRandomCreature::kType, 1, 0x50};
  store.put(cellKey, makeCell());
  store.put(otherCellKey, makeCell());
  store.put(populateKey, makePopulate());
  store.put(worldKey, makeWorldAdvect());
  store.put(randomKey, makeRandomCreature());

  CellContentLoader loader(store);
  CellContentCatalog catalog;
  const CellContentLoadResult cell = loader.load(cellKey);
  const CellContentLoadResult populate = loader.load(populateKey);
  const CellContentLoadResult world = loader.load(worldKey);
  const CellContentLoadResult random = loader.load(randomKey);
  catalog.add(cell);
  catalog.add(populate);
  catalog.add(world);
  catalog.add(random);
  CellReferenceResolver resolver(catalog);

  const std::vector<CellReference> cellReferences =
      resolver.references(*cell.record);
  const CellContentRecord malformed({CellPowers::kType, 7, 8}, CellGlobals{});
  check(resolver.references(malformed).empty() &&
            resolver.resolve(malformed, cellReferences.front()).code ==
                CellContentErrorCode::malformed_record,
        "resolver: key/value mismatched source record is rejected");
  check(
      cellReferences.size() == 1 &&
          cellReferences.front().field == CellReferenceField::cell_structure &&
          cellReferences.front().target.instance == 0xABCDu,
      "resolver: nullable zero fields are omitted from hard references");
  check(resolver.resolve(*cell.record, cellReferences.front()).code ==
            CellContentErrorCode::reference_not_found,
        "resolver: unresolved nonzero hard reference is a negative result");
  CellReference unsupportedTarget = cellReferences.front();
  unsupportedTarget.target.type = 0x12345678u;
  check(resolver.resolve(*cell.record, unsupportedTarget).code ==
            CellContentErrorCode::unsupported_type,
        "resolver: caller-supplied unsupported target TypeID is explicit");
  CellReference nullable = cellReferences.front();
  nullable.target.instance = 0;
  check(resolver.resolve(*cell.record, nullable).code ==
            CellContentErrorCode::invalid_reference,
        "resolver: synthetic zero reference is distinct from nullable absence");
  CellReference wrongSource = cellReferences.front();
  wrongSource.source.instance = ResourceKey::kWildcard;
  check(resolver.resolve(*cell.record, wrongSource).code ==
            CellContentErrorCode::invalid_key,
        "resolver: incomplete reference source is rejected");
  wrongSource.source = {ResourceKey::kWildcard, ResourceKey::kWildcard,
                        ResourceKey::kWildcard};
  check(resolver.resolve(*cell.record, wrongSource).code ==
            CellContentErrorCode::invalid_key,
        "resolver: wildcard reference source is rejected");
  wrongSource.source = {CellCell::kType, 0x100u, 0xABCDu};
  check(resolver.resolve(*cell.record, wrongSource).code ==
            CellContentErrorCode::reference_source_mismatch,
        "resolver: reference from another record is rejected");

  const std::vector<CellReference> populateReferences =
      resolver.references(*populate.record);
  check(populateReferences.size() == 1,
        "resolver: populate exposes only hard cell reference");
  CellReference cellReference = populateReferences.front();
  cellReference.target.group = 1;
  const CellReferenceResult resolved =
      resolver.resolve(*populate.record, cellReference);
  check(resolved && resolved.value.key == cellKey &&
            resolved.value.record->as<CellCell>() != nullptr,
        "resolver: full ResourceKey identity resolves typed target");
  CellReference wrongType = cellReference;
  wrongType.target.type = CellPowers::kType;
  check(resolver.resolve(*populate.record, wrongType).code ==
            CellContentErrorCode::reference_type_mismatch,
        "resolver: supported but incorrect target TypeID is explicit");
  CellReference wrongField = cellReference;
  wrongField.field = CellReferenceField::loot_cell;
  check(resolver.resolve(*populate.record, wrongField).code ==
            CellContentErrorCode::invalid_reference,
        "resolver: fabricated field identity is rejected");
  CellReference wrongIndex = cellReference;
  wrongIndex.index = 1;
  check(resolver.resolve(*populate.record, wrongIndex).code ==
            CellContentErrorCode::invalid_reference,
        "resolver: fabricated entry index is rejected");
  const ICellReferenceResolver& resolverApi = resolver;
  const CellReferenceResult apiResolved =
      resolverApi.resolve(*populate.record, cellReference);
  check(apiResolved && apiResolved.value.key == resolved.value.key &&
            apiResolved.value.record == resolved.value.record,
        "API: resolver interface returns the typed reference result");

  const CellContentLoadResult otherCell = loader.load(otherCellKey);
  catalog.add(otherCell);
  const CellReferenceResult ambiguous =
      resolver.resolve(*populate.record, populateReferences.front());
  check(ambiguous.code == CellContentErrorCode::ambiguous_reference,
        "resolver: partial identity is rejected when ambiguous");

  CellReference missing = cellReference;
  missing.target.group = 9;
  check(resolver.resolve(*populate.record, missing).code ==
            CellContentErrorCode::reference_not_found,
        "resolver: missing group identity is explicit");

  const std::vector<CellReference> worldReferences =
      resolver.references(*world.record);
  check(worldReferences.size() == 1 &&
            worldReferences.front().target.type == 0x04805684u &&
            resolver.resolve(*world.record, worldReferences.front()).code ==
                CellContentErrorCode::unsupported_type,
        "resolver: unsupported advect target is explicit");

  const std::vector<CellReference> randomReferences =
      resolver.references(*random.record);
  check(randomReferences.empty(),
        "resolver: soft creature ID is not treated as a hard reference");
}

}  // namespace

int main() {
  testDirectParserDependencies();
  testLoaderAndCatalog();
  testAllDirectLoads();
  testCountedRecordExtents();
  testResolver();
  if (failures == 0) {
    std::printf("cell content: ALL PASS\n");
    return 0;
  }
  std::printf("cell content: %d FAILURES\n", failures);
  return 1;
}
