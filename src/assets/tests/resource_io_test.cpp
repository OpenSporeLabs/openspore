#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Dbpf.hpp"
#include "PropertyStore.hpp"
#include "ResourceStore.hpp"
#include "compat/ResourceProvider.hpp"

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

void pushU16(std::vector<uint8_t>& bytes, uint16_t value) {
  bytes.push_back(static_cast<uint8_t>(value & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 8u) & 0xFFu));
}

void pushU32(std::vector<uint8_t>& bytes, uint32_t value) {
  bytes.push_back(static_cast<uint8_t>(value & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 8u) & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 16u) & 0xFFu));
  bytes.push_back(static_cast<uint8_t>((value >> 24u) & 0xFFu));
}

void setU32(std::vector<uint8_t>& bytes, size_t offset, uint32_t value) {
  bytes[offset] = static_cast<uint8_t>(value & 0xFFu);
  bytes[offset + 1] = static_cast<uint8_t>((value >> 8u) & 0xFFu);
  bytes[offset + 2] = static_cast<uint8_t>((value >> 16u) & 0xFFu);
  bytes[offset + 3] = static_cast<uint8_t>((value >> 24u) & 0xFFu);
}

std::vector<uint8_t> buildPackage(uint16_t rawCompression = 0,
                                  uint32_t rawMemorySize = 4,
                                  uint32_t qfsMemorySize = 4) {
  std::vector<uint8_t> bytes;
  bytes.insert(bytes.end(), {'D', 'B', 'P', 'F'});
  pushU32(bytes, 3);
  pushU32(bytes, 0);
  bytes.insert(bytes.end(), 20, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 2);
  pushU32(bytes, 0);
  pushU32(bytes, 56);
  bytes.insert(bytes.end(), 12, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 96);
  bytes.insert(bytes.end(), 28, 0);
  pushU32(bytes, 0);
  const uint32_t rawOffset = 156;
  pushU32(bytes, 0x11111111u);
  pushU32(bytes, 0x22222222u);
  pushU32(bytes, 0x33333333u);
  pushU32(bytes, rawOffset);
  pushU32(bytes, 0x80000004u);
  pushU32(bytes, rawMemorySize);
  pushU16(bytes, rawCompression);
  bytes.push_back(0);
  bytes.push_back(0);
  const uint32_t qfsOffset = rawOffset + 4;
  pushU32(bytes, 0x44444444u);
  pushU32(bytes, 0x55555555u);
  pushU32(bytes, 0x66666666u);
  pushU32(bytes, qfsOffset);
  pushU32(bytes, 10);
  pushU32(bytes, qfsMemorySize);
  pushU16(bytes, 0xFFFFu);
  bytes.push_back(0);
  bytes.push_back(0);
  bytes.insert(bytes.end(), {0xDE, 0xAD, 0xBE, 0xEF});
  bytes.insert(bytes.end(),
               {0x10, 0xFB, 0x00, 0x00, 0x04, 0xE0, 'A', 'B', 'C', 'D'});
  return bytes;
}

std::vector<uint8_t> buildCompactPackage() {
  std::vector<uint8_t> bytes;
  bytes.insert(bytes.end(), {'D', 'B', 'P', 'F'});
  pushU32(bytes, 3);
  pushU32(bytes, 0);
  bytes.insert(bytes.end(), 20, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 2);
  pushU32(bytes, 0);
  pushU32(bytes, 52);
  bytes.insert(bytes.end(), 12, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 96);
  bytes.insert(bytes.end(), 28, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 0xAAAAAAAAu);
  pushU32(bytes, 0xBBBBBBBBu);
  const uint32_t payloadOffset = 148;
  for (uint32_t instance = 1; instance <= 2; ++instance) {
    pushU32(bytes, instance);
    pushU32(bytes, payloadOffset + (instance - 1u) * 4u);
    pushU32(bytes, 4);
    pushU32(bytes, 4);
    pushU16(bytes, 0);
    bytes.push_back(0);
    bytes.push_back(0);
  }
  bytes.insert(bytes.end(), {1, 2, 3, 4, 5, 6, 7, 8});
  return bytes;
}

std::vector<uint8_t> readFile(const std::string& path) {
  std::ifstream input(path, std::ios::binary);
  if (!input) {
    return {};
  }
  return {std::istreambuf_iterator<char>(input),
          std::istreambuf_iterator<char>()};
}

void testResourceKey() {
  using namespace openspore::assets;
  const ResourceKey first{1, 2, 3};
  const ResourceKey same{1, 2, 3};
  const ResourceKey other{1, 2, 4};
  check(first == same && first != other, "resource key: field-aware equality");
  check(first.isComplete(), "resource key: complete TGI accepted");
  check(!(ResourceKey{ResourceKey::kWildcard, 2, 3}.isComplete()),
        "resource key: wildcard rejected for lookup identity");
  check(!(first < first) && first < other && !(other < first),
        "resource key: lexicographic ordering is strict");
}

void testDbpfStore() {
  using namespace openspore::assets;
  const std::vector<uint8_t> package = buildPackage();
  DbpfContentStore store(package.data(), package.size());
  check(store.valid() && store.entryCount() == 2,
        "dbpf store: index parsed once");
  const std::vector<uint8_t> compactPackage = buildCompactPackage();
  DbpfContentStore compactStore(compactPackage.data(), compactPackage.size());
  check(compactStore.valid() && compactStore.entryCount() == 2 &&
            compactStore.read({0xAAAAAAAAu, 0xBBBBBBBBu, 1u}).bytes ==
                std::vector<uint8_t>({1, 2, 3, 4}) &&
            compactStore.read({0xAAAAAAAAu, 0xBBBBBBBBu, 2u}).bytes ==
                std::vector<uint8_t>({5, 6, 7, 8}),
        "dbpf store: shared type/group index rows parsed exactly");
  const ResourceKey rawKey{0x11111111u, 0x22222222u, 0x33333333u};
  const LookupResult located = store.lookup(rawKey);
  check(located.code == ContentErrorCode::ok && located.locator.offset == 156 &&
            located.locator.storedSize == 4 &&
            located.locator.memorySize == 4 &&
            located.locator.compression == 0 && located.locator.withinExtent(),
        "dbpf store: bounded locator metadata");
  const ReadResult raw = store.read(rawKey);
  const std::vector<uint8_t> rawBytes = {0xDE, 0xAD, 0xBE, 0xEF};
  check(raw.code == ContentErrorCode::ok && raw.bytes == rawBytes,
        "dbpf store: exact raw read");
  const ReadResult qfs = store.read({0x44444444u, 0x55555555u, 0x66666666u});
  check(qfs.code == ContentErrorCode::ok &&
            qfs.bytes == std::vector<uint8_t>({'A', 'B', 'C', 'D'}),
        "dbpf store: exact QFS read");
  check(store.read(rawKey).bytes == rawBytes,
        "dbpf store: repeated read deterministic");
  check(store.lookup({1, 2, 3}).code == ContentErrorCode::not_found,
        "dbpf store: missing record explicit");
  check(store.lookup({ResourceKey::kWildcard, 2, 3}).code ==
            ContentErrorCode::invalid_key,
        "dbpf store: wildcard lookup rejected");

  std::vector<uint8_t> unsupported = buildPackage(0x1234u);
  DbpfContentStore unsupportedStore(unsupported.data(), unsupported.size());
  check(unsupportedStore.lookup(rawKey).code ==
            ContentErrorCode::unsupported_compression,
        "dbpf store: unsupported compression explicit");
  std::vector<DbpfEntry> unsupportedEntries;
  std::vector<uint8_t> unsupportedBytes;
  std::string parseError;
  check(parseDbpfIndex(unsupported.data(), unsupported.size(),
                       unsupportedEntries, parseError) &&
            !extractDbpfRecord(unsupported.data(), unsupported.size(),
                               unsupportedEntries[0], unsupportedBytes,
                               parseError),
        "dbpf store: direct extraction rejects unsupported compression");

  std::vector<uint8_t> badExtent = buildPackage();
  setU32(badExtent, 112, static_cast<uint32_t>(badExtent.size() - 2u));
  DbpfContentStore badExtentStore(badExtent.data(), badExtent.size());
  check(badExtentStore.lookup(rawKey).code == ContentErrorCode::invalid_extent,
        "dbpf store: out-of-bounds extent explicit");

  std::vector<uint8_t> badSize = buildPackage(0, 3);
  DbpfContentStore badSizeStore(badSize.data(), badSize.size());
  check(badSizeStore.read(rawKey).code == ContentErrorCode::size_mismatch,
        "dbpf store: raw memSize mismatch explicit");

  std::vector<uint8_t> badQfsSize = buildPackage(0, 4, 5);
  DbpfContentStore badQfsSizeStore(badQfsSize.data(), badQfsSize.size());
  check(badQfsSizeStore.read({0x44444444u, 0x55555555u, 0x66666666u}).code ==
            ContentErrorCode::size_mismatch,
        "dbpf store: QFS memSize mismatch explicit");

  DbpfContentStore emptyStore(nullptr, 0);
  check(emptyStore.read(rawKey).code == ContentErrorCode::invalid_input,
        "dbpf store: empty image invalid input explicit");

  std::vector<uint8_t> truncated(package.begin(), package.begin() + 100);
  DbpfContentStore truncatedStore(truncated.data(), truncated.size());
  check(truncatedStore.lookup(rawKey).code == ContentErrorCode::malformed_index,
        "dbpf store: truncated index explicit");

  std::vector<uint8_t> dbbf(96, 0);
  std::memcpy(dbbf.data(), "DBBF", 4);
  DbpfContentStore dbbfStore(dbbf.data(), dbbf.size());
  check(dbbfStore.lookup(rawKey).code == ContentErrorCode::unsupported_format,
        "dbpf store: DBBF unsupported explicit");

  std::vector<uint8_t> badMagic(96, 0);
  std::memcpy(badMagic.data(), "NOPE", 4);
  DbpfContentStore badMagicStore(badMagic.data(), badMagic.size());
  check(
      badMagicStore.lookup(rawKey).code == ContentErrorCode::unsupported_format,
      "dbpf store: bad magic unsupported format explicit");

  std::vector<uint8_t> headerIndex = buildPackage();
  setU32(headerIndex, 0x40, 0);
  DbpfContentStore headerIndexStore(headerIndex.data(), headerIndex.size());
  check(
      headerIndexStore.lookup(rawKey).code == ContentErrorCode::malformed_index,
      "dbpf store: index offset overlapping header explicit");
}

void testFixtureStore(const char* path) {
  using namespace openspore::assets;
  const std::vector<uint8_t> package = readFile(path);
  check(!package.empty(), "fixture: mini_package.dbpf loads");
  if (package.empty()) {
    return;
  }
  DbpfContentStore store(package.data(), package.size());
  check(store.valid() && store.entryCount() == 3,
        "fixture: committed DBPF index has three entries");
  const LookupResult qfs =
      store.lookup({0x31534651u, 0x33333333u, 0x44444444u});
  check(qfs && qfs.locator.storedSize == 421 && qfs.locator.memorySize == 412 &&
            qfs.locator.compressed(),
        "fixture: QFS locator matches Python oracle");
  std::vector<uint8_t> expectedQfs(412, 0);
  for (size_t index = 0; index < 112; ++index) {
    expectedQfs[index] = static_cast<uint8_t>(index);
  }
  check(
      store.read({0x31534651u, 0x33333333u, 0x44444444u}).bytes == expectedQfs,
      "fixture: QFS bytes match Python oracle");
  std::vector<uint8_t> expectedRaw(64, 0);
  for (size_t index = 0; index < expectedRaw.size(); ++index) {
    expectedRaw[index] = static_cast<uint8_t>(index * 7u);
  }
  check(
      store.read({0x42574152u, 0x55555555u, 0x66666666u}).bytes == expectedRaw,
      "fixture: raw bytes match Python oracle");

  openspore::compat::DbpfResourceProvider provider(package.data(),
                                                   package.size());
  ResourceProviderContentStore adapter(provider);
  check(
      adapter.lookup({1, 2, 3}).code == ContentErrorCode::unsupported_operation,
      "provider adapter: locator lookup explicitly unsupported");
  check(adapter.read({0x42574152u, 0x55555555u, 0x66666666u}).bytes ==
            expectedRaw,
        "provider adapter: existing IResourceProvider fetch reused");
}

struct DecodedRecord {
  uint32_t value = 0;
  size_t size = 0;
};

class TestCodec final : public openspore::assets::IRecordCodec {
 public:
  openspore::assets::RecordCodecResult decode(uint32_t typeId,
                                              const uint8_t* data,
                                              size_t size) override {
    using openspore::assets::RecordCodecErrorCode;
    using openspore::assets::RecordCodecResult;
    if (typeId != 0x100u) {
      return {
          RecordCodecErrorCode::unsupported_type, {}, "test codec: wrong type"};
    }
    if (size != 4u) {
      return {RecordCodecErrorCode::decode_failed,
              {},
              "test codec: expected four bytes"};
    }
    const uint32_t value = static_cast<uint32_t>(data[0]) |
                           (static_cast<uint32_t>(data[1]) << 8u) |
                           (static_cast<uint32_t>(data[2]) << 16u) |
                           (static_cast<uint32_t>(data[3]) << 24u);
    return {RecordCodecErrorCode::ok, DecodedRecord{value, size}, {}};
  }
};

class FailingCodec final : public openspore::assets::IRecordCodec {
 public:
  openspore::assets::RecordCodecResult decode(uint32_t, const uint8_t*,
                                              size_t) override {
    return {openspore::assets::RecordCodecErrorCode::decode_failed,
            DecodedRecord{0, 0}, "test codec: forced failure"};
  }
};

void testRecordCodecs() {
  using namespace openspore::assets;
  RecordCodecRegistry codecs;
  auto codec = std::make_shared<TestCodec>();
  check(codecs.registerCodec(0x100u, codec),
        "record codec: registration works");
  check(!codecs.registerCodec(0x100u, std::make_shared<FailingCodec>()),
        "record codec: duplicate registration rejected");
  const std::vector<uint8_t> bytes = {0x78, 0x56, 0x34, 0x12};
  const RecordCodecResult decoded =
      codecs.decode(0x100u, bytes.data(), bytes.size());
  const auto* record = std::any_cast<DecodedRecord>(&decoded.record);
  check(decoded.code == RecordCodecErrorCode::ok && record != nullptr &&
            record->value == 0x12345678u && record->size == 4,
        "record codec: typed result preserved");
  check(codecs.decode(0x101u, bytes.data(), bytes.size()).code ==
            RecordCodecErrorCode::unsupported_type,
        "record codec: unsupported type explicit");
  check(codecs.decode(0x100u, nullptr, 1).code ==
            RecordCodecErrorCode::invalid_input,
        "record codec: invalid input explicit");
  check(codecs.decode(0x100u, bytes.data(), 3).code ==
            RecordCodecErrorCode::decode_failed,
        "record codec: decoder failure explicit");
  check(codecs.registerCodec(0x200u, std::make_shared<FailingCodec>()),
        "record codec: second codec registration works");
  const RecordCodecResult failed =
      codecs.decode(0x200u, bytes.data(), bytes.size());
  check(failed.code == RecordCodecErrorCode::decode_failed &&
            !failed.record.has_value(),
        "record codec: failed decode cannot expose an untyped record");
}

class StalledOutputStream final : public openspore::assets::IStream {
 protected:
  openspore::assets::StreamResult read_some(void*, size_t) override {
    return {openspore::assets::StreamStatus::unsupported, 0,
            "stalled stream: read unsupported"};
  }
  openspore::assets::StreamResult write_some(const void*, size_t) override {
    return {openspore::assets::StreamStatus::short_write, 0,
            "stalled stream: no progress"};
  }
};

class StalledInputStream final : public openspore::assets::IStream {
 protected:
  openspore::assets::StreamResult read_some(void*, size_t) override {
    return {openspore::assets::StreamStatus::ok, 0,
            "stalled stream: no progress"};
  }
  openspore::assets::StreamResult write_some(const void*, size_t) override {
    return {openspore::assets::StreamStatus::unsupported, 0,
            "stalled stream: write unsupported"};
  }
};

class OverReportingInputStream final : public openspore::assets::IStream {
 protected:
  openspore::assets::StreamResult read_some(void*, size_t size) override {
    return {openspore::assets::StreamStatus::ok, size + 1u,
            "over-reporting stream"};
  }
  openspore::assets::StreamResult write_some(const void*, size_t) override {
    return {openspore::assets::StreamStatus::unsupported, 0,
            "over-reporting stream: write unsupported"};
  }
};

class CloseFailureStream final : public openspore::assets::IStream {
 public:
  bool fail = true;

 protected:
  openspore::assets::StreamResult read_some(void*, size_t) override {
    return {openspore::assets::StreamStatus::unsupported, 0,
            "close failure stream: read unsupported"};
  }
  openspore::assets::StreamResult write_some(const void*, size_t) override {
    return {openspore::assets::StreamStatus::unsupported, 0,
            "close failure stream: write unsupported"};
  }
  openspore::assets::StreamResult do_close() override {
    if (fail) {
      return {openspore::assets::StreamStatus::io_error, 0,
              "close failure stream: injected failure"};
    }
    return {};
  }
};

void testStreams() {
  using namespace openspore::assets;
  const std::vector<uint8_t> inputBytes = {1, 2, 3};
  MemoryInputStream input(inputBytes);
  uint8_t first[2] = {};
  check(input.read_exact(first, 2) && first[0] == 1 && first[1] == 2 &&
            input.position() == 2,
        "stream: exact read consumes requested bytes");
  uint8_t rest[3] = {};
  const StreamResult shortRead = input.read_exact(rest, 3);
  check(shortRead.status == StreamStatus::short_read &&
            shortRead.bytesTransferred == 1 && rest[0] == 3,
        "stream: short read reports exact transferred prefix");
  check(input.write_all(first, 1).status == StreamStatus::unsupported,
        "stream: write to input explicit unsupported");
  check(input.close() && input.close().status == StreamStatus::already_closed,
        "stream: close is explicit and idempotently reported");
  check(input.read_exact(first, 0).status == StreamStatus::closed,
        "stream: operation after close rejected");
  check(input.read_exact(nullptr, 1).status == StreamStatus::invalid_argument,
        "stream: null read pointer explicit");
  check(input.write_all(nullptr, 1).status == StreamStatus::invalid_argument,
        "stream: null write pointer explicit");
  MemoryInputStream missingInput(nullptr, 1);
  check(missingInput.read_exact(first, 1).status ==
            StreamStatus::invalid_argument,
        "stream: missing input backing data explicit");

  const std::vector<uint8_t> outputBytes = {0, 1, 2, 3, 4};
  MemoryOutputStream output({}, 2);
  const StreamResult written =
      output.write_all(outputBytes.data(), outputBytes.size());
  check(written && written.bytesTransferred == outputBytes.size() &&
            output.bytes() == outputBytes,
        "stream: write_all retries short writes");
  StalledOutputStream stalled;
  check(stalled.write_all(outputBytes.data(), outputBytes.size()).status ==
            StreamStatus::short_write,
        "stream: zero-progress write explicit");

  StalledInputStream stalledInput;
  uint8_t oneByte = 0;
  check(stalledInput.read_exact(&oneByte, 1).status == StreamStatus::short_read,
        "stream: zero-progress read explicit");
  OverReportingInputStream overReporting;
  const StreamResult overReported = overReporting.read_exact(&oneByte, 1);
  check(overReported.status == StreamStatus::io_error &&
            overReported.bytesTransferred == 0,
        "stream: over-reported read rejected without transfer");
  CloseFailureStream closeFailure;
  const StreamResult failedClose = closeFailure.close();
  closeFailure.fail = false;
  check(failedClose.status == StreamStatus::io_error && closeFailure.close() &&
            closeFailure.close().status == StreamStatus::already_closed,
        "stream: failed close remains retryable");
  Reader nullReader(nullptr, 0);
  const uint8_t* view = reinterpret_cast<const uint8_t*>(0x1);
  check(nullReader.readView(0, view) && view == nullptr,
        "stream: empty reader view has null origin");
}

void appendPropertyHeader(std::vector<uint8_t>& bytes, uint32_t count) {
  bytes.insert(bytes.end(), {'O', 'P', 'R', 'P', 1, 0, 0, 0});
  pushU32(bytes, count);
}

void testPropertyStore() {
  using namespace openspore::assets;
  LocalPropertyStore parent;
  check(parent.set_local(1, uint32_t{11}) && parent.set_local(2, false),
        "property store: local writes succeed");
  LocalPropertyStore child(&parent);
  check(child.set_local(1, uint32_t{22}) && parent.operationCount() == 2 &&
            child.operationCount() == 1,
        "property store: mutation counter is local");
  PropertyValue value = false;
  check(child.get_local(1, value) && std::get<uint32_t>(value) == 22u &&
            child.get(1, value) && std::get<uint32_t>(value) == 22u,
        "property store: local value overrides parent");
  check(child.get(2, value) && !std::get<bool>(value),
        "property store: parent fallback is read-only");

  LocalPropertyStore cycleA;
  LocalPropertyStore cycleB;
  cycleA.setParent(&cycleB);
  cycleB.setParent(&cycleA);
  check(cycleA.get(99, value).code == PropertyErrorCode::parent_cycle,
        "property store: parent cycle explicit");
  std::vector<std::unique_ptr<LocalPropertyStore>> chain;
  for (size_t index = 0; index <= LocalPropertyStore::kMaxParentDepth + 1u;
       ++index) {
    const IPropertyStore* parent = chain.empty() ? nullptr : chain.back().get();
    chain.push_back(std::make_unique<LocalPropertyStore>(parent));
  }
  check(chain.back()->get(99, value).code ==
            PropertyErrorCode::parent_depth_exceeded,
        "property store: parent fallback depth bounded");

  const openspore::assets::ResourceKey key{0xAABBCCDDu, 0x11223344u,
                                           0x55667788u};
  const std::vector<PropertyEntry> source = {
      {40, key},  {10, int32_t{-7}},           {30, 1.25F},
      {20, true}, {50, uint32_t{0x12345678u}},
  };
  MemoryOutputStream encoded({}, 2);
  check(static_cast<bool>(child.write_local(encoded, source)),
        "property store: local entries write through chunked stream");
  const std::vector<uint8_t> wire = encoded.take();
  check(wire.size() > 8 && wire[0] == 'O' && wire[1] == 'P' && wire[2] == 'R' &&
            wire[3] == 'P' && wire[4] == 1,
        "PROVISIONAL property store: versioned host-local wire header");
  MemoryInputStream input(wire);
  LocalPropertyStore decoded;
  check(static_cast<bool>(decoded.read_local(input)),
        "property store: local entries read back");
  const std::vector<PropertyEntry> roundTrip = decoded.entries();
  check(roundTrip.size() == source.size() && roundTrip[0].id == 10 &&
            roundTrip[1].id == 20 && roundTrip[2].id == 30 &&
            roundTrip[3].id == 40 && roundTrip[4].id == 50,
        "property store: deterministic property-id order");
  check(std::get<int32_t>(roundTrip[0].value) == -7 &&
            std::get<bool>(roundTrip[1].value) &&
            std::get<float>(roundTrip[2].value) == 1.25F &&
            std::get<ResourceKey>(roundTrip[3].value) == key &&
            std::get<uint32_t>(roundTrip[4].value) == 0x12345678u,
        "property store: typed value round-trip exact");

  std::vector<uint8_t> unsupported;
  appendPropertyHeader(unsupported, 2);
  pushU32(unsupported, 1);
  unsupported.push_back(static_cast<uint8_t>(PropertyType::boolean));
  unsupported.push_back(1);
  pushU32(unsupported, 2);
  unsupported.push_back(static_cast<uint8_t>(PropertyType::string8));
  LocalPropertyStore partial;
  check(static_cast<bool>(partial.set_local(99, uint32_t{9})),
        "property store: unsupported setup");
  MemoryInputStream unsupportedInput(unsupported);
  check(partial.read_local(unsupportedInput).code ==
                PropertyErrorCode::unsupported_property &&
            partial.size() == 1 && partial.get_local(1, value) &&
            std::get<bool>(value),
        "property store: unsupported property stops after prior entry");

  std::vector<uint8_t> duplicate;
  appendPropertyHeader(duplicate, 2);
  pushU32(duplicate, 7);
  duplicate.push_back(static_cast<uint8_t>(PropertyType::boolean));
  duplicate.push_back(0);
  pushU32(duplicate, 7);
  duplicate.push_back(static_cast<uint8_t>(PropertyType::boolean));
  duplicate.push_back(1);
  MemoryInputStream duplicateInput(duplicate);
  LocalPropertyStore duplicateStore;
  check(duplicateStore.read_local(duplicateInput).code ==
                PropertyErrorCode::duplicate_id &&
            duplicateStore.size() == 1,
        "property store: duplicate id stops after prior entry");

  std::vector<uint8_t> version = {'O', 'P', 'R', 'P', 2, 0, 0, 0, 0, 0, 0, 0};
  MemoryInputStream versionInput(version);
  check(partial.read_local(versionInput).code ==
                PropertyErrorCode::unsupported_version &&
            partial.size() == 1,
        "property store: unsupported version preserves local state");

  std::vector<uint8_t> truncated = {'O', 'P', 'R', 'P', 1, 0, 0, 0, 1, 0, 0, 0};
  MemoryInputStream truncatedInput(truncated);
  check(partial.read_local(truncatedInput).code ==
                PropertyErrorCode::stream_failure &&
            partial.size() == 0,
        "property store: short local read fails after accepted framing");

  std::vector<uint8_t> malformedBool;
  appendPropertyHeader(malformedBool, 1);
  pushU32(malformedBool, 9);
  malformedBool.push_back(static_cast<uint8_t>(PropertyType::boolean));
  malformedBool.push_back(2);
  MemoryInputStream malformedBoolInput(malformedBool);
  LocalPropertyStore malformedBoolStore;
  check(malformedBoolStore.read_local(malformedBoolInput).code ==
            PropertyErrorCode::malformed_data,
        "BLUEPRINT_BACKED property store: malformed bool explicit");

  const std::vector<uint8_t> empty;
  MemoryInputStream emptyInput(empty);
  LocalPropertyStore emptyStore;
  check(emptyStore.read_local(emptyInput).code ==
            PropertyErrorCode::stream_failure,
        "EXISTING_OPENSPORE_BEHAVIOR property store: empty stream failure");

  LocalPropertyStore limitedRead(nullptr, PropertyLimits{1});
  std::vector<uint8_t> overLimit;
  appendPropertyHeader(overLimit, 2);
  MemoryInputStream overLimitInput(overLimit);
  check(limitedRead.read_local(overLimitInput).code ==
            PropertyErrorCode::limit_exceeded,
        "BOUNDED_INFERENCE property store: decoded count limit explicit");

  LocalPropertyStore stalledWriteStore;
  StalledOutputStream stalledWrite;
  check(stalledWriteStore.write_local(stalledWrite, {{1, true}}).code ==
            PropertyErrorCode::stream_failure,
        "BOUNDED_INFERENCE property store: stream write failure explicit");

  LocalPropertyStore limits({});
  check(static_cast<bool>(limits.set_local(1, true)),
        "property store: limit setup");
  LocalPropertyStore zeroLimit(nullptr, PropertyLimits{0});
  check(zeroLimit.set_local(1, true).code == PropertyErrorCode::limit_exceeded,
        "property store: local entry limit explicit");

  LocalPropertyStore outputStore;
  MemoryOutputStream rejectedOutput;
  check(outputStore.write_local(rejectedOutput, {{1, true}, {1, false}}).code ==
                PropertyErrorCode::duplicate_id &&
            rejectedOutput.bytes().empty(),
        "property store: duplicate write rejected before stream write");
}

}  // namespace

int main(int argc, char** argv) {
  if (argc != 2) {
    std::printf("FAIL: resource_io_test requires mini_package.dbpf path\n");
    return 1;
  }
  testResourceKey();
  testDbpfStore();
  testFixtureStore(argv[1]);
  testRecordCodecs();
  testStreams();
  testPropertyStore();
  if (failures == 0) {
    std::printf("resource io contract: ALL PASS\n");
    return 0;
  }
  std::printf("resource io contract: %d FAILURES\n", failures);
  return 1;
}
