// See CellResource.hpp. Clean-room implementation, independently authored.
#include "CellResource.hpp"

#include <cmath>

#include "Stream.hpp"

namespace openspore::assets {

namespace {

// The cCellGlobalsResource field layout in declaration order. `kind`:
// 'u' = u32 (enum / int / reference key), 'f' = float. Offsets are implicit:
// field i starts at 4*i. This mirrors the runtime struct (Ghidra 61843 family).
struct FieldSpec {
  const char *name;
  char kind;
};

constexpr FieldSpec kFields[] = {
    {"gameMode", 'u'},
    {"world_1", 'u'}, {"world_2", 'u'}, {"world_3", 'u'}, {"world_4", 'u'},
    {"world_5", 'u'},
    {"worldBackground_1", 'u'}, {"worldBackground_2", 'u'},
    {"worldBackground_3", 'u'}, {"worldBackground_4", 'u'},
    {"worldBackground_5", 'u'},
    {"worldRandom", 'u'},
    {"worldRandomBg", 'u'},
    {"startCell", 'u'},
    {"startingCellKey", 'u'},
    {"effectMapEntry", 'u'},
    {"backgroundMapEntry", 'u'},
    {"flowMultiplier", 'f'},
    {"npcSpeedMultiplier", 'f'},
    {"npcTurnSpeedMultiplier_Jet", 'f'},
    {"npcTurnSpeedMultiplier_Flagella", 'f'},
    {"npcTurnSpeedMultiplier_Cilia", 'f'},
    {"densityRock", 'f'},
    {"densitySolid", 'f'},
    {"densityLiquid", 'f'},
    {"densityAir", 'f'},
    {"backgroundDistance", 'f'},
    {"minDragCollisionSpeed", 'f'},
    {"minImpactCollisionSpeed", 'f'},
    {"ciliaSpeedAsJet", 'f'},
    {"flagellaSpeedAsJet", 'f'},
    {"flagellaSpeedAsCilia", 'f'},
    {"ciliaSpeedAsFlagella", 'f'},
    {"keyLookAlgorithm", 'u'},
    {"beachDistance", 'f'},
    {"finishLineDistance", 'f'},
    {"noPartSpeed", 'f'},
    {"flagellaRampMinFactor", 'f'},
    {"flagellaRampTime", 'f'},
    {"flagellaRampResetAngle", 'f'},
    {"flagellaTurnSpeedRampStart", 'f'},
    {"flagellaTurnSpeedRampEnd", 'f'},
    {"flagellaTurnSpeedMin", 'f'},
    {"flagellaTurnSpeedMax", 'f'},
    {"ciliaTurnSpeed", 'f'},
    {"jetTurnSpeed", 'f'},
    {"startLevelNoCreatureRadius", 'f'},
    {"startLevelNoAnythingRadius", 'f'},
    {"numHighLOD_FG", 'u'},
    {"numHighLOD_BG", 'u'},
    {"percentAnimalFood", 'f'},
    {"percentPlantFood", 'f'},
    {"field_208", 'u'},
    {"controlMethod", 'u'},
    {"editorMethod", 'u'},
    {"tutorialMethod", 'u'},
    {"endingMethod", 'u'},
    {"eyeMethod", 'u'},
    {"timeToGoldyCinematic", 'f'},
    {"missionTime", 'f'},
    {"missionResetTime", 'f'},
    {"escapeMinDistance", 'f'},
    {"escapeMaxDistance", 'f'},
    {"escapeDelayMedium", 'f'},
    {"escapeTimerHard", 'f'},
    {"nonAnimatingCiliaMovementFactor", 'f'},
    {"nonAnimatingJetMovementFactor", 'f'},
    {"mateTriggerDistance", 'f'},
    {"mateSpawnDistance", 'f'},
};

static_assert(std::size(kFields) == CellGlobals::kFieldCount,
              "field table must match kFieldCount");

} // namespace

uint32_t CellGlobals::gameMode() const {
  for (const CellField &field : fields) {
    if (field.name == "gameMode") {
      return field.u;
    }
  }
  return 0;
}

float CellGlobals::flowMultiplier() const {
  for (const CellField &field : fields) {
    if (field.name == "flowMultiplier") {
      return field.f;
    }
  }
  return 0.0F;
}

bool CellGlobals::complete() const {
  return size == kSize && fields.size() == kFieldCount && accounted() == size;
}

size_t CellGlobals::accounted() const {
  size_t end = 0;
  for (const CellField &field : fields) {
    end = std::max(end, field.offset + 4);
  }
  return end;
}

bool parseCellGlobals(const uint8_t *data, size_t size, CellGlobals &out,
                      std::string &error) {
  if (size != CellGlobals::kSize) {
    error = "record size " + std::to_string(size) + " != " +
            std::to_string(CellGlobals::kSize);
    return false;
  }
  out = CellGlobals{};
  out.size = size;
  Reader r(data, size);
  for (size_t i = 0; i < std::size(kFields); ++i) {
    CellField field;
    field.name = kFields[i].name;
    field.offset = i * 4;
    field.isFloat = kFields[i].kind == 'f';
    if (field.isFloat) {
      field.f = r.readF32();
      field.u = 0;
    } else {
      field.u = r.readU32();
      field.f = 0.0F;
    }
    out.fields.push_back(field);
  }
  if (!r.ok()) {
    error = "truncated globals record";
    return false;
  }
  return true;
}

} // namespace openspore::assets
