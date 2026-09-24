#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Dxt5.hpp"
#include "MaterialRegistry.hpp"
#include "ModelStore.hpp"
#include "TextureStore.hpp"
#include "compat/MeshSource.hpp"

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

bool readFile(const char* path, std::vector<uint8_t>& bytes) {
  std::ifstream input(path, std::ios::binary);
  if (!input) {
    return false;
  }
  input.seekg(0, std::ios::end);
  const std::streamoff length = input.tellg();
  if (length <= 0) {
    return false;
  }
  input.seekg(0, std::ios::beg);
  bytes.resize(static_cast<size_t>(length));
  input.read(reinterpret_cast<char*>(bytes.data()), length);
  return static_cast<bool>(input);
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

void pushF32(std::vector<uint8_t>& bytes, float value) {
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  pushU32(bytes, bits);
}

std::vector<uint8_t> buildGmdl() {
  std::vector<uint8_t> bytes;
  pushU32(bytes, 8);
  pushU32(bytes, 0);
  pushU32(bytes, 1);
  for (int i = 0; i < 3; ++i) {
    pushF32(bytes, 0.0F);
  }
  for (int i = 0; i < 3; ++i) {
    pushF32(bytes, 1.0F);
  }
  pushF32(bytes, 0.7071F);
  pushU32(bytes, 1);
  pushU32(bytes, 4);
  pushU32(bytes, 3);
  pushU32(bytes, 16);
  pushU32(bytes, 6);
  pushU16(bytes, 0);
  pushU16(bytes, 1);
  pushU16(bytes, 2);
  pushU32(bytes, 1);
  pushU32(bytes, 1);
  pushU16(bytes, 0);
  pushU16(bytes, 0);
  bytes.push_back(2);
  bytes.push_back(0);
  bytes.push_back(0);
  bytes.push_back(0);
  pushU32(bytes, 0);
  pushU32(bytes, 1);
  pushU32(bytes, 0);
  pushU32(bytes, 3);
  pushU32(bytes, 36);
  const float vertices[] = {0, 0, 0, 1, 0, 0, 0, 1, 0};
  for (float value : vertices) {
    pushF32(bytes, value);
  }
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0x12345678u);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  pushU32(bytes, 0);
  return bytes;
}

std::vector<uint8_t> buildRw4() {
  std::vector<uint8_t> bytes(0xB4, 0);
  const uint8_t magic[] = {0x89, 0x52, 0x57, 0x34, 0x77, 0x33, 0x32,
                           0x00, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x20,
                           0x04, 0x00, 0x34, 0x35, 0x34, 0x00, 0x30,
                           0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00};
  std::memcpy(bytes.data(), magic, sizeof(magic));
  setU32(bytes, 0x1C, 1);
  setU32(bytes, 0x20, 0);
  setU32(bytes, 0x24, 0);
  setU32(bytes, 0x30, 0xB4);
  setU32(bytes, 0x44, 0);
  setU32(bytes, 0x4C, 0);
  setU32(bytes, 0x98, 0x10004);
  setU32(bytes, 0xA4, 0x10);
  setU32(bytes, 0xA8, 0x10005);
  setU32(bytes, 0xAC, 0);
  return bytes;
}

std::vector<uint8_t> buildRaster() {
  std::vector<uint8_t> bytes;
  pushU32(bytes, 1);
  pushU32(bytes, 2);
  pushU32(bytes, 2);
  pushU32(bytes, 1);
  pushU32(bytes, 0x11111111u);
  pushU32(bytes, 0x35545844u);
  pushU32(bytes, 0x22222222u);
  pushU32(bytes, 0x33333333u);
  bytes.resize(bytes.size() + 16, 0);
  bytes.insert(bytes.end(), {255, 255, 0, 0, 0, 0, 0, 0});
  return bytes;
}

class MemoryContentStore final : public openspore::assets::IContentStore {
 public:
  void add(const openspore::assets::ResourceKey& key,
           std::vector<uint8_t> bytes) {
    bytes_.emplace(key, std::move(bytes));
  }

  openspore::assets::LookupResult lookup(
      const openspore::assets::ResourceKey&) const override {
    return {openspore::assets::ContentErrorCode::unsupported_operation,
            {},
            "test store: lookup is unavailable"};
  }

  openspore::assets::ReadResult read(
      const openspore::assets::ResourceKey& key) const override {
    if (!key.isComplete()) {
      return {openspore::assets::ContentErrorCode::invalid_key,
              {},
              "test store: incomplete key"};
    }
    const auto found = bytes_.find(key);
    if (found == bytes_.end()) {
      return {openspore::assets::ContentErrorCode::not_found,
              {},
              "test store: record not found"};
    }
    return {openspore::assets::ContentErrorCode::ok, found->second, {}};
  }

 private:
  std::map<openspore::assets::ResourceKey, std::vector<uint8_t>> bytes_;
};

class RecordingRenderer final : public openspore::IRenderer {
 public:
  bool init(uint32_t, uint32_t) override { return true; }
  void shutdown() override {}
  openspore::MeshHandle createMesh(const openspore::Vertex*, size_t,
                                   const uint32_t*, size_t) override {
    return 1;
  }
  void destroyMesh(openspore::MeshHandle) override {}
  openspore::TextureHandle createTexture(
      const openspore::ImageRGBA& image) override {
    uploaded = image;
    ++uploads;
    return 7;
  }
  void destroyTexture(openspore::TextureHandle handle) override {
    if (handle == 7) {
      ++destroys;
    }
  }
  openspore::MeshHandle createTexMesh(const openspore::TexVertex*, size_t,
                                      const uint32_t*, size_t) override {
    return 2;
  }
  void beginFrame(float, float, float, float) override {}
  void drawMesh(openspore::MeshHandle) override {}
  void drawTextured(openspore::MeshHandle, openspore::TextureHandle,
                    const openspore::MaterialState&) override {}
  void endFrame() override {}
  openspore::ImageRGBA readbackPixels() override { return {}; }

  openspore::ImageRGBA uploaded;
  size_t uploads = 0;
  size_t destroys = 0;
};

void testDeterministicAndAtomicDecodes() {
  using namespace openspore::assets;
  std::vector<uint8_t> dxt5 = {255, 255, 0, 0, 0, 0, 0, 0};
  std::vector<uint8_t> first;
  std::vector<uint8_t> second;
  std::string error;
  check(decodeDxt5Mip(dxt5.data(), dxt5.size(), 4, 4, first, error) &&
            decodeDxt5Mip(dxt5.data(), dxt5.size(), 4, 4, second, error) &&
            first == second && first.size() == 64,
        "deterministic unit: DXT5 mip decodes identically");
  bool pixelsValid = !first.empty();
  for (size_t offset = 0; offset < first.size(); offset += 4) {
    pixelsValid = pixelsValid && first[offset] == 0 && first[offset + 1] == 0 &&
                  first[offset + 2] == 0 && first[offset + 3] == 255;
  }
  check(pixelsValid, "deterministic unit: DXT5 RGBA8 output is exact");

  std::vector<uint8_t> gmdl = buildGmdl();
  setU32(gmdl, 60, 9);
  GmdlModel model;
  check(parseGmdl(gmdl.data(), gmdl.size(), model, error),
        "atomic setup: malformed-index GMDL prefix parses");
  Mesh mesh;
  mesh.positions.push_back({9, 9, 9});
  check(!meshFromGmdl(model, 0, mesh, error) && mesh.positions.empty(),
        "atomic mesh: failure publishes no partial vertices");

  std::vector<uint8_t> version9 = buildGmdl();
  version9[0] = 9;
  model.meshes.push_back({});
  check(!parseGmdl(version9.data(), version9.size(), model, error) &&
            model.meshes.empty() &&
            error.find("unsupported version") != std::string::npos,
        "atomic GMDL: v9 publishes no partial model");

  RasterEnvelope envelope;
  envelope.width = 7;
  const std::vector<uint8_t> shortEnvelope(16, 0);
  check(!parseRasterEnvelope(shortEnvelope.data(), shortEnvelope.size(),
                             envelope, error) &&
            envelope.width == 0,
        "atomic raster: truncated envelope publishes no partial header");

  std::vector<uint8_t> raster = buildRaster();
  setU32(raster, 12, 0);
  std::vector<openspore::ImageRGBA> mips;
  mips.push_back({});
  envelope.width = 9;
  check(
      !decodeRasterMips(raster.data(), raster.size(), mips, envelope, error) &&
          mips.empty() && envelope.width == 0,
      "atomic raster: invalid mip chain publishes no partial image");

  std::vector<uint8_t> rw4 = buildRw4();
  setU32(rw4, 0x44, 0xFFFFu);
  Rw4 container;
  container.sections.push_back({});
  check(!parseRw4(rw4.data(), rw4.size(), container, error) &&
            container.sections.empty(),
        "atomic RW4: invalid arena publishes no partial manifest");
}

void testFixtureComparison(const char* gmdlPath, const char* rw4Path) {
  using namespace openspore::assets;
  std::vector<uint8_t> gmdlBytes;
  std::vector<uint8_t> rw4Bytes;
  check(readFile(gmdlPath, gmdlBytes) && readFile(rw4Path, rw4Bytes),
        "fixture comparison: committed fixtures load");
  if (gmdlBytes.empty() || rw4Bytes.empty()) {
    return;
  }

  GmdlModel model;
  Rw4 container;
  std::string error;
  check(parseGmdl(gmdlBytes.data(), gmdlBytes.size(), model, error) &&
            model.version == 8 && model.meshCount == 1 &&
            model.consumed == gmdlBytes.size() && model.meshes.size() == 1 &&
            model.indexBuffers.size() == 1 &&
            model.indexBuffers[0].indexCount == 153 &&
            model.indexBuffers[0].indexBits == 16 &&
            model.vertexBuffers.size() == 1 &&
            model.vertexBuffers[0].vertexCount == 50 &&
            model.materialIds == std::vector<uint32_t>{0x12345678u},
        "fixture comparison: mini.gmdl bounded fields match");

  check(parseRw4(rw4Bytes.data(), rw4Bytes.size(), container, error) &&
            container.complete() && container.ftype == Rw4::kTypeModel &&
            container.objCount == 1 && container.sectionCount == 3 &&
            container.pBufferData == 0x138 && container.bufSize == 80 &&
            container.typecodes ==
                std::vector<uint32_t>{0x10030u, 0x20003u, 0x40001u} &&
            container.sections.size() == 3 &&
            container.sections[0].data == 0x138 &&
            container.sections[1].data == 0x144 &&
            container.sections[2].data == 0x170 &&
            container.unknownTypeCodes() == 1,
        "fixture comparison: mini_rw4.rw4 manifest and sections match");

  Rw4 repeated;
  check(parseRw4(rw4Bytes.data(), rw4Bytes.size(), repeated, error) &&
            repeated.describe() == container.describe(),
        "deterministic RW4: repeated structural walks are identical");

  std::vector<uint8_t> malformed = rw4Bytes;
  setU32(malformed, 0xF8, 0xFFFFFFFFu);
  check(!parseRw4(malformed.data(), malformed.size(), repeated, error) &&
            repeated.sections.empty(),
        "malformed RW4: negative section size is rejected atomically");
}

void testModelStore() {
  using namespace openspore::assets;
  MemoryContentStore store;
  const ResourceKey modelKey{kGmdlType, 1, 2};
  const std::vector<uint8_t> gmdl = buildGmdl();
  store.add(modelKey, gmdl);
  ModelStore models(store);
  const ModelLoadResult loaded = models.load(modelKey);
  check(loaded && loaded.record.hasGmdl && loaded.record.gmdl.version == 8 &&
            loaded.record.gmdl.meshes.size() == 1,
        "model store: GMDL decodes through content store");
  check(loaded.record.animation == AnimationStatus::opaque_trailer,
        "model store: GMDL animation trailer is explicit");
  check(models.loadAnimation(modelKey).code ==
            ModelLoadCode::unsupported_animation,
        "model store: animation execution is explicit unsupported");
  check(models.load({kGmdlType, 1, ResourceKey::kWildcard}).code ==
            ModelLoadCode::invalid_key,
        "model store: incomplete key explicit");
  check(models.load({1, 1, 2}).code == ModelLoadCode::unsupported_type,
        "model store: unsupported type explicit");

  std::vector<uint8_t> invalid = gmdl;
  invalid[0] = 9;
  const ResourceKey invalidKey{kGmdlType, 1, 3};
  store.add(invalidKey, std::move(invalid));
  check(models.load(invalidKey).code == ModelLoadCode::unsupported_version,
        "model store: GMDL v9 explicit unsupported");

  const ResourceKey rw4Key{kRw4Type, 1, 4};
  store.add(rw4Key, buildRw4());
  const ModelLoadResult rw4 = models.load(rw4Key);
  check(rw4 && rw4.record.hasRw4 && !rw4.record.hasGmdl,
        "model store: RW4 structural walk succeeds");
  check(rw4.record.animation == AnimationStatus::none,
        "model store: empty RW4 animation status is bounded");
  check(models.load({kGmdlType, 1, 99}).code == ModelLoadCode::not_found,
        "model store: missing record is explicit not found");
  std::vector<uint8_t> malformedRw4 = buildRw4();
  setU32(malformedRw4, 0x44, 0xFFFFu);
  const ResourceKey malformedRw4Key{kRw4Type, 1, 6};
  store.add(malformedRw4Key, std::move(malformedRw4));
  check(models.load(malformedRw4Key).code == ModelLoadCode::malformed_record,
        "model store: malformed RW4 is explicit failure");

  openspore::compat::GmdlMeshSource source(loaded.record.gmdl);
  openspore::assets::Mesh mesh;
  std::string error;
  check(source.build(loaded.record, 0, mesh, error) &&
            mesh.positions.size() == 3 && mesh.indices.size() == 3,
        "mesh source: builds a model record");
  openspore::compat::ModelStoreMeshSource modelSource(models, modelKey);
  check(modelSource.loadMesh(0, mesh, error) && mesh.positions.size() == 3,
        "mesh source: model store adapter builds the first mesh");
  openspore::compat::ModelStoreMeshSource rw4Source(models, rw4Key);
  check(!rw4Source.loadMesh(0, mesh, error) &&
            error.find("GMDL") != std::string::npos,
        "mesh source: RW4 payload build remains unsupported");
}

void testMaterialRegistry() {
  using namespace openspore::assets;
  GmdlModel model;
  model.materialIds = {3, 4};
  const std::vector<MaterialSlot> slots = materialSlotsFromGmdl(model);
  check(
      slots.size() == 2 && slots[0].materialId == 3 && slots[1].materialId == 4,
      "material registry: GMDL material IDs become ordered slots");
  MaterialRegistry registry;
  check(
      registry.resolve(slots).code == MaterialResolveCode::unsupported_material,
      "material registry: unregistered material explicit unsupported");
  MaterialDefinition definition;
  definition.materialId = 3;
  definition.textureSlots = {{kRasterType, 5, 6}};
  check(registry.registerMaterial(definition) &&
            !registry.registerMaterial(definition),
        "material registry: deterministic definition registration");
  const MaterialResolveResult resolved = registry.resolve({slots[0]});
  check(resolved && resolved.materials.size() == 1 &&
            resolved.materials[0].definition.materialId == 3,
        "material registry: registered material resolves");
  check(registry.resolve({{0, {{ResourceKey::kWildcard, 1, 1}}}}).code ==
            MaterialResolveCode::invalid_slot,
        "material registry: incomplete texture slot explicit");
  check(registry.resolve({slots[1]}).code ==
            MaterialResolveCode::unsupported_material,
        "material registry: missing material does not partially resolve");
  MaterialDefinition invalidDefinition;
  invalidDefinition.materialId = 5;
  invalidDefinition.textureSlots = {{ResourceKey::kWildcard, 1, 1}};
  check(!registry.registerMaterial(invalidDefinition) &&
            registry.resolve({{5, {}}}).code ==
                MaterialResolveCode::unsupported_material,
        "material registry: incomplete definition is not published");
  check(registry.resolve({}).code == MaterialResolveCode::ok,
        "material registry: empty slot set resolves deterministically");
}

void testTextureStore() {
  using namespace openspore::assets;
  MemoryContentStore store;
  RecordingRenderer renderer;
  const ResourceKey key{kRasterType, 2, 3};
  store.add(key, buildRaster());
  TextureStore textures(store, renderer);
  const TextureLoadResult loaded = textures.load(key);
  check(loaded && loaded.record.mips.size() == 1 &&
            loaded.record.mips[0].width == 2 &&
            loaded.record.mips[0].height == 2 &&
            loaded.record.envelope.field10 == 0x11111111u &&
            loaded.record.envelope.field18 == 0x22222222u &&
            loaded.record.envelope.field1c == 0x33333333u,
        "texture store: DXT5 raster decodes mips and retains unknown words");
  const TextureUploadResult uploaded = textures.upload(loaded.record);
  check(uploaded && uploaded.handle == 7 && uploaded.mipCount == 1 &&
            renderer.uploads == 1 && renderer.uploaded.width == 2,
        "texture store: uploads mip zero through renderer host type");
  textures.release(uploaded.handle);
  check(renderer.destroys == 1, "texture store: releases uploaded handle");
  ImageRecord mismatched = loaded.record;
  mismatched.mips[0].width = 1;
  check(textures.upload(mismatched).code == TextureCode::invalid_image &&
            renderer.uploads == 1,
        "texture store: mip dimensions must match the envelope");

  std::vector<uint8_t> badRaster = buildRaster();
  setU32(badRaster, 20, 0x12345678u);
  const ResourceKey badKey{kRasterType, 2, 4};
  store.add(badKey, std::move(badRaster));
  check(textures.load(badKey).code == TextureCode::unsupported_format,
        "texture store: unsupported FourCC explicit");
  ImageRecord invalid;
  invalid.mips.push_back({});
  check(textures.upload(invalid).code == TextureCode::invalid_image,
        "texture store: invalid image explicit");
  check(textures.load({kRasterType, 2, ResourceKey::kWildcard}).code ==
            TextureCode::invalid_key,
        "texture store: incomplete key explicit");
}

}  // namespace

int main(int argc, char** argv) {
  const char* gmdlPath = argc > 1 ? argv[1] : "tests/fixtures/mini.gmdl";
  const char* rw4Path = argc > 2 ? argv[2] : "tests/fixtures/mini_rw4.rw4";
  testDeterministicAndAtomicDecodes();
  testFixtureComparison(gmdlPath, rw4Path);
  testModelStore();
  testMaterialRegistry();
  testTextureStore();
  if (failures == 0) {
    std::printf("pkg04 asset geometry texture: ALL PASS\n");
    return 0;
  }
  std::printf("pkg04 asset geometry texture: %d FAILURES\n", failures);
  return 1;
}
