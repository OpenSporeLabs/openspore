// See CellResource.hpp. Clean-room implementation, independently authored.
#include "CellResource.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>

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

namespace {

// Canonical, byte-stable scalars for dump(): floats as raw bits so two
// decodes of the same record always produce identical strings.
std::string u32hex(uint32_t v) {
  char b[12];
  std::snprintf(b, sizeof(b), "0x%08x", v);
  return b;
}

std::string f32hex(float v) {
  uint32_t bits;
  std::memcpy(&bits, &v, 4);
  char b[12];
  std::snprintf(b, sizeof(b), "f0x%08x", bits);
  return b;
}

std::string i32d(int v) {
  char b[16];
  std::snprintf(b, sizeof(b), "i%d", v);
  return b;
}

std::string b8(bool v) { return v ? "1" : "0"; }

// wchar16[80] (zero-padded, NUL-terminated) -> UTF-8; BMP chars only.
std::string wideToUtf8(const uint16_t *w, size_t n) {
  std::string s;
  for (size_t i = 0; i < n && w[i] != 0; ++i) {
    const uint16_t c = w[i];
    if (c < 0x80) {
      s += static_cast<char>(c);
    } else if (c < 0x800) {
      s += static_cast<char>(0xC0 | (c >> 6));
      s += static_cast<char>(0x80 | (c & 0x3F));
    } else {
      s += static_cast<char>(0xE0 | (c >> 12));
      s += static_cast<char>(0x80 | ((c >> 6) & 0x3F));
      s += static_cast<char>(0x80 | (c & 0x3F));
    }
  }
  return s;
}

CellAI readCellAI(Reader &r) {
  CellAI a;
  a.type = r.readU32();
  a.awarenessRadius = r.readF32();
  a.awarenessRadiusFood = r.readF32();
  a.awarenessRadiusPredator = r.readF32();
  a.movementStyle = r.readU32();
  a.flocking = r.readU8() != 0;
  r.skip(3);
  a.speed = r.readF32();
  a.chaseSpeed = r.readF32();
  a.wanderSpeed = r.readF32();
  a.fleeSpeed = r.readF32();
  a.fearsNearbyDamageRadius = r.readF32();
  a.fearsNearbyDeathRadius = r.readF32();
  a.fearsNearbyDamageTime = r.readF32();
  a.fearsNearbyDeathTime = r.readF32();
  a.protectRadius = r.readF32();
  a.protectTime = r.readF32();
  a.turnFactor = r.readF32();
  a.axialMovement = r.readU8() != 0;
  r.skip(3);
  a.spawnTime = r.readF32();
  a.spawnRestTime = r.readF32();
  a.spawnOutput = r.readU32();
  a.arcLength = r.readF32();
  a.arcLengthSecondary = r.readF32();
  a.numArcs = static_cast<int>(r.readU32());
  a.keyTransformation = r.readU32();
  a.keyProjectile = r.readU32();
  a.food = r.readU32();
  a.growCount = static_cast<int>(r.readU32());
  a.digestionCount = static_cast<int>(r.readU32());
  a.digestionTime = r.readF32();
  a.digestionOutput = r.readU32();
  a.fleeTime = r.readF32();
  a.fleeRestTime = r.readF32();
  a.chaseTime = r.readF32();
  a.chaseRestTime = r.readF32();
  a.chasesDamage = r.readU8() != 0;
  a.fearsMouths = r.readU8() != 0;
  a.fearsWeapons = r.readU8() != 0;
  a.fearsElectric = r.readU8() != 0;
  a.fearsPoison = r.readU8() != 0;
  a.fearsDamage = r.readU8() != 0;
  a.ignoresFood = r.readU8() != 0;
  r.skip(1);
  a.awakeTime = r.readF32();
  a.sleepTime = r.readF32();
  a.growAmount = static_cast<int>(r.readU32());
  a.hatchDuration = r.readF32();
  a.poisonRecharge = r.readF32();
  a.electricRecharge = r.readF32();
  a.electricRechargeVsSmall = r.readF32();
  a.electricDischarge = r.readF32();
  return a;
}

CellEat readCellEat(Reader &r) {
  CellEat e;
  e.foodValue = static_cast<int>(r.readU32());
  e.hpValue = static_cast<int>(r.readU32());
  e.bomb = r.readU8() != 0;
  e.poisonNova = r.readU8() != 0;
  r.skip(2);
  return e;
}

void checkAi(const CellAI &a, const char *which, std::vector<std::string> &out) {
  if (a.type != 0 && a.type != CellAI::kEmpty &&
      (a.type < 0x1000 || a.type > 0x10FF)) {
    out.push_back(std::string(which) + ".type=" + u32hex(a.type));
  }
  if (a.movementStyle & ~0xFu) {
    out.push_back(std::string(which) + ".movementStyle=" +
                  u32hex(a.movementStyle));
  }
  if (a.food != 0 && a.food != 3) {
    out.push_back(std::string(which) + ".food=" + u32hex(a.food));
  }
  if (a.numArcs < 0 || a.numArcs >= 64) {
    out.push_back(std::string(which) + ".numArcs=" + i32d(a.numArcs));
  }
  const float fs[] = {
      a.awarenessRadius,     a.awarenessRadiusFood,
      a.awarenessRadiusPredator, a.speed,
      a.chaseSpeed,          a.wanderSpeed,
      a.fleeSpeed,           a.fearsNearbyDamageRadius,
      a.fearsNearbyDeathRadius, a.fearsNearbyDamageTime,
      a.fearsNearbyDeathTime,   a.protectRadius,
      a.protectTime,         a.turnFactor,
      a.spawnTime,           a.spawnRestTime,
      a.arcLength,           a.arcLengthSecondary,
      a.digestionTime,       a.fleeTime,
      a.fleeRestTime,        a.chaseTime,
      a.chaseRestTime,       a.awakeTime,
      a.sleepTime,           a.hatchDuration,
      a.poisonRecharge,      a.electricRecharge,
      a.electricRechargeVsSmall, a.electricDischarge};
  for (float v : fs) {
    if (!std::isfinite(v) || std::abs(v) > 1e4F) {
      out.push_back(std::string(which) + ".float=" + f32hex(v));
    }
  }
}

} // namespace

std::string CellAI::dump() const {
  std::string s;
  s += "type=" + u32hex(type) +
       " awarenessRadius=" + f32hex(awarenessRadius) +
       " awarenessRadiusFood=" + f32hex(awarenessRadiusFood) +
       " awarenessRadiusPredator=" + f32hex(awarenessRadiusPredator) +
       " movementStyle=" + u32hex(movementStyle) + " flocking=" +
       b8(flocking) + " speed=" + f32hex(speed) + " chaseSpeed=" +
       f32hex(chaseSpeed) + " wanderSpeed=" + f32hex(wanderSpeed) +
       " fleeSpeed=" + f32hex(fleeSpeed) +
       " fearsNearbyDamageRadius=" + f32hex(fearsNearbyDamageRadius) +
       " fearsNearbyDeathRadius=" + f32hex(fearsNearbyDeathRadius) +
       " fearsNearbyDamageTime=" + f32hex(fearsNearbyDamageTime) +
       " fearsNearbyDeathTime=" + f32hex(fearsNearbyDeathTime) +
       " protectRadius=" + f32hex(protectRadius) + " protectTime=" +
       f32hex(protectTime) + " turnFactor=" + f32hex(turnFactor) +
       " axialMovement=" + b8(axialMovement) + " spawnTime=" +
       f32hex(spawnTime) + " spawnRestTime=" + f32hex(spawnRestTime) +
       " spawnOutput=" + u32hex(spawnOutput) + " arcLength=" +
       f32hex(arcLength) + " arcLengthSecondary=" +
       f32hex(arcLengthSecondary) + " numArcs=" + i32d(numArcs) +
       " keyTransformation=" + u32hex(keyTransformation) +
       " keyProjectile=" + u32hex(keyProjectile) + " food=" +
       u32hex(food) + " growCount=" + i32d(growCount) +
       " digestionCount=" + i32d(digestionCount) + " digestionTime=" +
       f32hex(digestionTime) + " digestionOutput=" +
       u32hex(digestionOutput) + " fleeTime=" + f32hex(fleeTime) +
       " fleeRestTime=" + f32hex(fleeRestTime) + " chaseTime=" +
       f32hex(chaseTime) + " chaseRestTime=" + f32hex(chaseRestTime) +
       " chasesDamage=" + b8(chasesDamage) + " fearsMouths=" +
       b8(fearsMouths) + " fearsWeapons=" + b8(fearsWeapons) +
       " fearsElectric=" + b8(fearsElectric) + " fearsPoison=" +
       b8(fearsPoison) + " fearsDamage=" + b8(fearsDamage) +
       " ignoresFood=" + b8(ignoresFood) + " awakeTime=" +
       f32hex(awakeTime) + " sleepTime=" + f32hex(sleepTime) +
       " growAmount=" + i32d(growAmount) + " hatchDuration=" +
       f32hex(hatchDuration) + " poisonRecharge=" +
       f32hex(poisonRecharge) + " electricRecharge=" +
       f32hex(electricRecharge) + " electricRechargeVsSmall=" +
       f32hex(electricRechargeVsSmall) + " electricDischarge=" +
       f32hex(electricDischarge);
  return s;
}

std::string CellCell::dump() const {
  std::string s;
  s += "structure=" + u32hex(structure) + " name='" + name + "'" +
       " localeInstanceID=" + u32hex(localeInstanceID) + " hp=" +
       i32d(hp) + " fixedOrientation=" + b8(fixedOrientation) + " flags=" +
       u32hex(flags) + " cellType=" + u32hex(cellType) + " unlockType=" +
       u32hex(unlockType) + " density=" + u32hex(density) + " sound=" +
       u32hex(sound) + " break=" + u32hex(break_) + " pieces=" +
       u32hex(pieces) + " leak=" + u32hex(leak) + " expel=" +
       u32hex(expel) + " explosionTable=" + u32hex(explosionTable) +
       " loot=" + u32hex(loot) + " poison=" + u32hex(poison) + " ai={" +
       ai.dump() + "} aiHard={" + aiHard.dump() + "} aiEasy={" +
       aiEasy.dump() + "} friendGroup=" + i32d(friendGroup) +
       " wontAttackPlayer=" + b8(wontAttackPlayer) +
       " wontAttackPlayerWhenSmall=" + b8(wontAttackPlayerWhenSmall) +
       " sizeMin=" + f32hex(sizeMin) + " sizeMax=" + f32hex(sizeMax) +
       " eat{foodValue=" + i32d(eat.foodValue) + " hpValue=" +
       i32d(eat.hpValue) + " bomb=" + b8(eat.bomb) + " poisonNova=" +
       b8(eat.poisonNova) + "} triggersEscapeMission=" +
       b8(triggersEscapeMission);
  return s;
}

std::string CellEffectMap::dump() const {
  std::string s = "nE=" + i32d(numEntries);
  for (const CellEffectMapEntry &e : entries) {
    s += " entry{id=0x" + u32hex(e.effectID) + " type=" + u32hex(e.type) +
         " f8=" + f32hex(e.field_8) + " fC=" + f32hex(e.field_C) + " f10=" +
         f32hex(e.field_10) + " f14=" + f32hex(e.field_14) + " i18=" +
         i32d(e.field_18) + "}";
  }
  return s;
}

std::string CellBackgroundMap::dump() const {
  std::string s = "nE=" + i32d(numEntries);
  for (const CellBackgroundMapEntry &e : entries) {
    s += " entry{rgb=(" + f32hex(e.r) + "," + f32hex(e.g) + "," +
         f32hex(e.b) + ") fC=" + f32hex(e.field_C) + "}";
  }
  return s;
}

bool parseCellEffectMap(const uint8_t *data, size_t size, CellEffectMap &out,
                        std::string &error) {
  if (size < 8) {
    error = "record size " + std::to_string(size) + " < 8";
    return false;
  }
  out = CellEffectMap{};
  Reader r(data, size);
  out.numEntries = static_cast<int>(r.readU32());
  out.entriesPtr = r.readU32();
  if (r.offset() + 28 * out.numEntries != size) {
    error = "header count span " +
            std::to_string(8 + 28 * out.numEntries) + " != size " +
            std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellEffectMapEntry e;
    e.effectID = r.readU32();
    e.type = r.readU32();
    e.field_8 = r.readF32();
    e.field_C = r.readF32();
    e.field_10 = r.readF32();
    e.field_14 = r.readF32();
    e.field_18 = static_cast<int>(r.readU32());
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated effect-map record";
    return false;
  }
  return true;
}

bool parseCellBackgroundMap(const uint8_t *data, size_t size,
                            CellBackgroundMap &out, std::string &error) {
  if (size < 8) {
    error = "record size " + std::to_string(size) + " < 8";
    return false;
  }
  out = CellBackgroundMap{};
  Reader r(data, size);
  out.numEntries = static_cast<int>(r.readU32());
  out.entriesPtr = r.readU32();
  if (r.offset() + 16 * out.numEntries != size) {
    error = "header count span " +
            std::to_string(8 + 16 * out.numEntries) + " != size " +
            std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellBackgroundMapEntry e;
    e.r = r.readF32();
    e.g = r.readF32();
    e.b = r.readF32();
    e.field_C = r.readF32();
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated background-map record";
    return false;
  }
  return true;
}

std::vector<std::string> cellEffectMapIssues(const CellEffectMap &em,
                                            const CellBackgroundMap &bm) {
  std::vector<std::string> out;
  for (const CellEffectMapEntry &e : em.entries) {
    if (e.type > 31) {
      out.push_back("type=" + u32hex(e.type));
    }
    auto fok = [](float v, float lo, float hi, bool sentinel) {
      if (!std::isfinite(v)) {
        return false;
      }
      if (sentinel && v == -1.0F) {
        return true;
      }
      return v >= lo && v <= hi;
    };
    if (!fok(e.field_8, -100.0F, 100000.0F, true)) {
      out.push_back("f8=" + f32hex(e.field_8));
    }
    if (!fok(e.field_C, -100.0F, 100000.0F, true)) {
      out.push_back("fC=" + f32hex(e.field_C));
    }
    if (!fok(e.field_10, 0.0F, 100000.0F, false)) {
      out.push_back("f10=" + f32hex(e.field_10));
    }
    if (!fok(e.field_14, 0.0F, 100000.0F, false)) {
      out.push_back("f14=" + f32hex(e.field_14));
    }
    if (e.field_18 < -16 || e.field_18 > 64) {
      out.push_back("i18=" + i32d(e.field_18));
    }
  }
  for (const CellBackgroundMapEntry &e : bm.entries) {
    const float rgb[] = {e.r, e.g, e.b};
    for (float v : rgb) {
      if (!std::isfinite(v) || v < 0.0F || v > 1.0F) {
        out.push_back("rgb=" + f32hex(v));
      }
    }
    if (!std::isfinite(e.field_C) || e.field_C < 0.0F ||
        e.field_C > 100000.0F) {
      out.push_back("bgfC=" + f32hex(e.field_C));
    }
  }
  return out;
}

std::string CellRandomCreature::dump() const {
  std::string s = "nE=" + i32d(numEntries);
  for (const CellRandomCreatureEntry &e : entries) {
    s += " entry{type=" + u32hex(e.type) + " cid=0x" + u32hex(e.creatureID) +
         " w=" + f32hex(e.weight) + " sMin=" + i32d(e.speedMin) + " sMax=" +
         i32d(e.speedMax) + " dMin=" + i32d(e.dangerMin) + " dMax=" +
         i32d(e.dangerMax) + "}";
  }
  return s;
}

std::string CellPowers::dump() const {
  return "cost=" + i32d(teleportCost) + " range=" + f32hex(teleportRange);
}

bool parseCellRandomCreature(const uint8_t *data, size_t size,
                             CellRandomCreature &out, std::string &error) {
  if (size < 8) {
    error = "record size " + std::to_string(size) + " < 8";
    return false;
  }
  out = CellRandomCreature{};
  Reader r(data, size);
  out.numEntries = static_cast<int>(r.readU32());
  out.entriesPtr = r.readU32();
  if (r.offset() + 28 * out.numEntries != size) {
    error = "header count span " +
            std::to_string(8 + 28 * out.numEntries) + " != size " +
            std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellRandomCreatureEntry e;
    e.type = r.readU32();
    e.creatureID = r.readU32();
    e.weight = r.readF32();
    e.speedMin = static_cast<int>(r.readU32());
    e.speedMax = static_cast<int>(r.readU32());
    e.dangerMin = static_cast<int>(r.readU32());
    e.dangerMax = static_cast<int>(r.readU32());
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated random-creature record";
    return false;
  }
  return true;
}

bool parseCellPowers(const uint8_t *data, size_t size, CellPowers &out,
                     std::string &error) {
  if (size != 8) {
    error = "powers record size " + std::to_string(size) + " != 8";
    return false;
  }
  out = CellPowers{};
  Reader r(data, size);
  out.teleportCost = static_cast<int>(r.readU32());
  out.teleportRange = r.readF32();
  if (!r.ok()) {
    error = "truncated powers record";
    return false;
  }
  return true;
}

std::vector<std::string> cellRandomCreatureIssues(const CellRandomCreature &rc,
                                                 const CellPowers &pw) {
  std::vector<std::string> out;
  for (const CellRandomCreatureEntry &e : rc.entries) {
    if (e.type != 0 && e.type != 1) {
      out.push_back("type=" + u32hex(e.type));
    }
    if (!std::isfinite(e.weight) || e.weight < 0.0F || e.weight > 100.0F) {
      out.push_back("weight=" + f32hex(e.weight));
    }
    const int is[] = {e.speedMin, e.speedMax, e.dangerMin, e.dangerMax};
    for (int v : is) {
      if (v < -16 || v > 64) {
        out.push_back("stat=" + i32d(v));
      }
    }
    if (e.speedMin != -1 && e.speedMax != -1 && e.speedMin > e.speedMax) {
      out.push_back("speedMin>speedMax");
    }
    if (e.dangerMin != -1 && e.dangerMax != -1 && e.dangerMin > e.dangerMax) {
      out.push_back("dangerMin>dangerMax");
    }
  }
  if (pw.teleportCost < 0 || pw.teleportCost > 10000) {
    out.push_back("teleportCost=" + i32d(pw.teleportCost));
  }
  if (!std::isfinite(pw.teleportRange) || pw.teleportRange < 0.0F ||
      pw.teleportRange > 1000.0F) {
    out.push_back("teleportRange=" + f32hex(pw.teleportRange));
  }
  return out;
}

std::string CellLookTable::dump() const {
  std::string s = "nE=" + i32d(numEntries);
  for (const CellLookEntry &e : entries) {
    s += " entry{type=" + i32d(e.type) + " value=" + f32hex(e.value) + "}";
  }
  return s;
}

std::string CellLookAlgorithm::dump() const {
  std::string s = "nE=" + i32d(numEntries);
  for (const CellLookAlgoEntry &e : entries) {
    s += " entry{type=" + u32hex(e.type) + " action=" + u32hex(e.action) +
         " p=" + u32hex(e.player) + " n=" + u32hex(e.npc) + " e=" +
         u32hex(e.epic) + "}";
  }
  return s;
}

bool parseCellLookTable(const uint8_t *data, size_t size, CellLookTable &out,
                        std::string &error) {
  if (size < 8) {
    error = "record size " + std::to_string(size) + " < 8";
    return false;
  }
  out = CellLookTable{};
  Reader r(data, size);
  out.entriesPtr = r.readU32();
  out.numEntries = static_cast<int>(r.readU32());
  if (r.offset() + 8 * out.numEntries != size) {
    error = "header count span " + std::to_string(8 + 8 * out.numEntries) +
            " != size " + std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellLookEntry e;
    e.type = static_cast<int>(r.readU32());
    e.value = r.readF32();
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated look-table record";
    return false;
  }
  return true;
}

bool parseCellLookAlgorithm(const uint8_t *data, size_t size,
                            CellLookAlgorithm &out, std::string &error) {
  if (size < 8) {
    error = "record size " + std::to_string(size) + " < 8";
    return false;
  }
  out = CellLookAlgorithm{};
  Reader r(data, size);
  out.entriesPtr = r.readU32();
  out.numEntries = static_cast<int>(r.readU32());
  if (r.offset() + 20 * out.numEntries != size) {
    error = "header count span " + std::to_string(8 + 20 * out.numEntries) +
            " != size " + std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellLookAlgoEntry e;
    e.type = r.readU32();
    e.action = r.readU32();
    e.player = r.readU32();
    e.npc = r.readU32();
    e.epic = r.readU32();
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated look-algorithm record";
    return false;
  }
  return true;
}

std::vector<std::string> cellLookIssues(
    const CellLookTable &t, const CellLookAlgorithm &a,
    const std::unordered_set<uint32_t> &lookTableInsts) {
  std::vector<std::string> out;
  for (const CellLookEntry &e : t.entries) {
    if (e.type < 0 || e.type > 31) {
      out.push_back("look.type=" + i32d(e.type));
    }
    if (!std::isfinite(e.value) || e.value < 0.0F || e.value > 100.0F) {
      out.push_back("look.value=" + f32hex(e.value));
    }
  }
  for (const CellLookAlgoEntry &e : a.entries) {
    if (e.type > 5) {
      out.push_back("algo.type=" + u32hex(e.type));
    }
    if (e.action > 60 && e.action != 0xFFFFFFFF) {
      out.push_back(std::string("algo.action=0x") + u32hex(e.action));
    }
    const uint32_t refs[] = {e.player, e.npc, e.epic};
    for (uint32_t v : refs) {
      if (v && lookTableInsts.find(v) == lookTableInsts.end()) {
        out.push_back("algo ref=" + u32hex(v));
      }
    }
  }
  return out;
}

std::string CellLootTable::dump() const {
  std::string s;
  s += "minR=" + f32hex(minRadius) + " maxR=" + f32hex(maxRadius) +
       " initA=" + f32hex(initialAlpha) + " expelF=" + f32hex(expelForce) +
       " effect=" + i32d(effect) + " mhp=" + u32hex(mustHavePart) +
       " delay=" + f32hex(delay) + " nE=" + i32d(numEntries);
  for (const CellLootEntry &e : entries) {
    s += " entry{type=" + u32hex(e.type) + " cell=" + u32hex(e.cell) +
         " table=" + u32hex(e.table) + " w=" + f32hex(e.weight) + " n=" +
         i32d(e.count) + " dn=" + i32d(e.countDelta) + " lo=" +
         i32d(e.levelOffset) + "}";
  }
  return s;
}

bool parseCellLootTable(const uint8_t *data, size_t size, CellLootTable &out,
                        std::string &error) {
  if (size < 36) {
    error = "record size " + std::to_string(size) + " < 36";
    return false;
  }
  out = CellLootTable{};
  Reader r(data, size);
  out.entriesPtr = r.readU32();
  out.numEntries = static_cast<int>(r.readU32());
  out.minRadius = r.readF32();
  out.maxRadius = r.readF32();
  out.initialAlpha = r.readF32();
  out.expelForce = r.readF32();
  out.effect = static_cast<int>(r.readU32());
  out.mustHavePart = r.readU8();
  r.skip(3);
  out.delay = r.readF32();
  if (r.offset() + 28 * out.numEntries != size) {
    error = "header count span " +
            std::to_string(36 + 28 * out.numEntries) + " != size " +
            std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numEntries; ++i) {
    CellLootEntry e;
    e.type = r.readU32();
    e.cell = r.readU32();
    e.table = r.readU32();
    e.weight = r.readF32();
    e.count = static_cast<int>(r.readU32());
    e.countDelta = static_cast<int>(r.readU32());
    e.levelOffset = static_cast<int>(r.readU32());
    out.entries.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated loot-table record";
    return false;
  }
  return true;
}

std::vector<std::string> cellLootTableIssues(
    const CellLootTable &t, const std::unordered_set<uint32_t> &cellInsts,
    const std::unordered_set<uint32_t> &lootInsts) {
  std::vector<std::string> out;
  if (t.effect != 0) {
    out.push_back("effect=" + i32d(t.effect));
  }
  if (t.mustHavePart > 1) {
    out.push_back("mustHavePart=" + u32hex(t.mustHavePart));
  }
  if (t.numEntries < 0 || t.numEntries > 64) {
    out.push_back("numEntries=" + i32d(t.numEntries));
  }
  const float fs[] = {t.minRadius, t.maxRadius, t.initialAlpha, t.expelForce,
                      t.delay};
  for (float v : fs) {
    if (!std::isfinite(v) || v < 0.0F || v > 1000.0F) {
      out.push_back("header float=" + f32hex(v));
    }
  }
  for (const CellLootEntry &e : t.entries) {
    if (e.type > 5) {
      out.push_back("entry.type=" + u32hex(e.type));
    }
    if (e.cell && cellInsts.find(e.cell) == cellInsts.end()) {
      out.push_back("cell=" + u32hex(e.cell));
    }
    if (e.table && lootInsts.find(e.table) == lootInsts.end()) {
      out.push_back("table=" + u32hex(e.table));
    }
    if (!std::isfinite(e.weight) || e.weight < 0.0F || e.weight > 1000.0F) {
      out.push_back("weight=" + f32hex(e.weight));
    }
    if (e.count < -10 || e.count > 64) {
      out.push_back("count=" + i32d(e.count));
    }
    if (e.countDelta < -10 || e.countDelta > 64) {
      out.push_back("countDelta=" + i32d(e.countDelta));
    }
    if (e.levelOffset < -16 || e.levelOffset > 16) {
      out.push_back("levelOffset=" + i32d(e.levelOffset));
    }
  }
  return out;
}

std::string CellStructure::dump() const {
  std::string s;
  s += "onDeath=" + u32hex(onDeath) + " onDeathSmall=" + u32hex(onDeathSmall) +
       " onDeathLarge=" + u32hex(onDeathLarge) + " onHatch=" +
       u32hex(onHatch) + " onStartHatch=" + u32hex(onStartHatch) +
       " nAtt=" + i32d(numAttachments);
  for (const CellStructureAtt &a : atts) {
    s += " att{bone=" + i32d(a.bone) + " type=" + u32hex(a.type) +
         " struct=" + u32hex(a.structure) + " rand=" + u32hex(a.randomCreature) +
         " effect=" + i32d(a.effectID) + " lmin=" + i32d(a.levelMin) +
         " lmax=" + i32d(a.levelMax) + " color=(" + f32hex(a.color[0]) + "," +
         f32hex(a.color[1]) + "," + f32hex(a.color[2]) + ")}";
  }
  return s;
}

bool parseCellStructure(const uint8_t *data, size_t size, CellStructure &out,
                        std::string &error) {
  if (size < 28) {
    error = "record size " + std::to_string(size) + " < 28";
    return false;
  }
  out = CellStructure{};
  Reader r(data, size);
  out.onDeath = r.readU32();
  out.onDeathSmall = r.readU32();
  out.onDeathLarge = r.readU32();
  out.onHatch = r.readU32();
  out.onStartHatch = r.readU32();
  out.attachmentsPtr = r.readU32();
  out.numAttachments = static_cast<int>(r.readU32());
  if (r.offset() + 40 * out.numAttachments != size) {
    error = "header count span " +
            std::to_string(28 + 40 * out.numAttachments) + " != size " +
            std::to_string(size);
    return false;
  }
  for (int i = 0; i < out.numAttachments; ++i) {
    CellStructureAtt a;
    a.bone = static_cast<int>(r.readU32());
    a.type = r.readU32();
    a.structure = r.readU32();
    a.randomCreature = r.readU32();
    a.effectID = static_cast<int>(r.readU32());
    a.levelMin = static_cast<int>(r.readU32());
    a.levelMax = static_cast<int>(r.readU32());
    for (int c = 0; c < 3; ++c) {
      a.color[c] = r.readF32();
    }
    out.atts.push_back(a);
  }
  if (!r.ok()) {
    error = "truncated structure record";
    return false;
  }
  return true;
}

std::vector<std::string> cellStructureIssues(const CellStructure &s) {
  std::vector<std::string> out;
  if (s.onStartHatch != 0) {
    out.push_back("onStartHatch=" + u32hex(s.onStartHatch));
  }
  if (s.numAttachments < 0 || s.numAttachments > 16) {
    out.push_back("numAttachments=" + i32d(s.numAttachments));
  }
  for (const CellStructureAtt &a : s.atts) {
    if (a.bone != 0 && a.bone != 3 && a.bone != -1) {
      out.push_back("bone=" + i32d(a.bone));
    }
    if (a.type > 10) {
      out.push_back("type=" + u32hex(a.type));
    }
    if (a.structure != 0) {
      out.push_back("structure=" + u32hex(a.structure));
    }
    if (a.levelMin != 0 && a.levelMin != -1) {
      out.push_back("levelMin=" + i32d(a.levelMin));
    }
    if (a.levelMax != 0 && a.levelMax != 10 && a.levelMax != -1) {
      out.push_back("levelMax=" + i32d(a.levelMax));
    }
    for (int c = 0; c < 3; ++c) {
      if (!std::isfinite(a.color[c]) || a.color[c] < 0.0F ||
          a.color[c] > 2.0F) {
        out.push_back("color=" + f32hex(a.color[c]));
      }
    }
  }
  return out;
}

std::string CellPopulate::dump() const {
  std::string s;
  s += "scale=" + u32hex(scale) + " maskTexture=" + u32hex(maskTexture) +
       " numMarkers=" + i32d(static_cast<int>(numMarkers)) + " markersPtr=" +
       u32hex(markersPtr);
  for (const CellMarker &m : markers) {
    s += " marker{dist=" + u32hex(m.distributeCell) + " clust=" +
         u32hex(m.clusterCell) + " enc=" + u32hex(m.encounterPopulate) +
         " plant=" + u32hex(m.plantType) + " type=" + u32hex(m.type) +
         " count=" + f32hex(m.count) + " cE=" + f32hex(m.countEasy) +
         " cM=" + f32hex(m.countMed) + " cH=" + f32hex(m.countHard) +
         " size=" + i32d(m.size) + " parts=" + i32d(m.parts) + " lin=" +
         i32d(m.linear) + " zOff=" + f32hex(m.zOffset) + " zOffMax=" +
         f32hex(m.zOffsetMax) + " encScale=" + i32d(m.encounterScale) + "}";
  }
  return s;
}

bool parseCellPopulate(const uint8_t *data, size_t size, CellPopulate &out,
                       std::string &error) {
  if (size < 16) {
    error = "record size " + std::to_string(size) + " < 16";
    return false;
  }
  out = CellPopulate{};
  Reader r(data, size);
  out.scale = r.readU32();
  out.maskTexture = r.readU32();
  out.numMarkers = r.readU32();
  out.markersPtr = r.readU32();
  if (r.offset() + 76 * out.numMarkers != size) {
    error = "header count span " +
            std::to_string(16 + 76 * out.numMarkers) + " != size " +
            std::to_string(size);
    return false;
  }
  for (uint32_t i = 0; i < out.numMarkers; ++i) {
    CellMarker m;
    m.field_0 = r.readU32();
    m.field_4 = r.readU32();
    m.field_8 = r.readU32();
    m.zOffset = r.readF32();
    m.zOffsetMax = r.readF32();
    m.field_14 = r.readU32();
    m.distributeCell = r.readU32();
    m.clusterCell = r.readU32();
    m.encounterPopulate = r.readU32();
    m.plantType = r.readU32();
    m.type = r.readU32();
    m.count = r.readF32();
    m.countEasy = r.readF32();
    m.countMed = r.readF32();
    m.countHard = r.readF32();
    m.size = static_cast<int>(r.readU32());
    m.parts = static_cast<int>(r.readU32());
    m.linear = static_cast<int>(r.readU32());
    m.encounterScale = static_cast<int>(r.readU32());
    out.markers.push_back(m);
  }
  if (!r.ok()) {
    error = "truncated populate record";
    return false;
  }
  return true;
}

std::vector<std::string> cellPopulateIssues(
    const CellPopulate &p, const std::unordered_set<uint32_t> &cellInsts) {
  std::vector<std::string> out;
  if (p.scale > 10) {
    out.push_back("scale=" + u32hex(p.scale));
  }
  if (p.maskTexture != 0) {
    out.push_back("maskTexture=" + u32hex(p.maskTexture));
  }
  if (p.numMarkers > 64) {
    out.push_back("numMarkers=" + i32d(static_cast<int>(p.numMarkers)));
  }
  for (const CellMarker &m : p.markers) {
    if (m.field_0 || m.field_4 || m.field_8 || m.field_14) {
      out.push_back("dead field nonzero");
    }
    if (m.encounterPopulate != 0) {
      out.push_back("encounterPopulate=" + u32hex(m.encounterPopulate));
    }
    if (m.distributeCell &&
        cellInsts.find(m.distributeCell) == cellInsts.end()) {
      out.push_back("distributeCell=" + u32hex(m.distributeCell));
    }
    if (m.clusterCell && cellInsts.find(m.clusterCell) == cellInsts.end()) {
      out.push_back("clusterCell=" + u32hex(m.clusterCell));
    }
    if (m.plantType > 10) {
      out.push_back("plantType=" + u32hex(m.plantType));
    }
    if (m.type > 10) {
      out.push_back("type=" + u32hex(m.type));
    }
    const float fs[] = {m.count, m.countEasy, m.countMed, m.countHard};
    for (float v : fs) {
      if (!std::isfinite(v) || v < -1.0F || v > 1000.0F) {
        out.push_back("count=" + f32hex(v));
      }
    }
    if (m.size < 0 || m.size > 30) {
      out.push_back("size=" + i32d(m.size));
    }
    if (m.parts < 0 || m.parts > 30) {
      out.push_back("parts=" + i32d(m.parts));
    }
    if (m.linear != 0 && m.linear != 1) {
      out.push_back("linear=" + i32d(m.linear));
    }
    if (!std::isfinite(m.zOffset) || m.zOffset < 0.0F ||
        m.zOffset > 100.0F) {
      out.push_back("zOffset=" + f32hex(m.zOffset));
    }
    if (!std::isfinite(m.zOffsetMax) || m.zOffsetMax < 0.0F ||
        m.zOffsetMax > 100.0F) {
      out.push_back("zOffsetMax=" + f32hex(m.zOffsetMax));
    }
  }
  return out;
}

std::string CellWorld::dump() const {
  std::string s;
  s += "numPopulate=" + i32d(static_cast<int>(numPopulate)) +
       " populatePtr=" + u32hex(populatePtr) + " numAdvect=" +
       i32d(static_cast<int>(numAdvect)) + " advectPtr=" + u32hex(advectPtr);
  for (const CellLevelEntry &e : populate) {
    s += " level{populate=" + u32hex(e.populate) + " startTile=" +
         b8(e.startTile != 0) + " playerSize=" + u32hex(e.playerSize) + "}";
  }
  for (const CellAdvectEntry &e : advect) {
    s += " advect{stageScale=" + u32hex(e.stageScale) + " playerSize=" +
         i32d(e.playerSize) + " strength=" + f32hex(e.strength) +
         " variance=" + f32hex(e.variance) + " period=" + f32hex(e.period) +
         " advectID=" + u32hex(e.advectID) + "}";
  }
  return s;
}

bool parseCellWorld(const uint8_t *data, size_t size, CellWorld &out,
                    std::string &error) {
  if (size < 16) {
    error = "record size " + std::to_string(size) + " < 16";
    return false;
  }
  out = CellWorld{};
  Reader r(data, size);
  out.numPopulate = r.readU32();
  out.populatePtr = r.readU32();
  out.numAdvect = r.readU32();
  out.advectPtr = r.readU32();
  if (r.offset() + 12 * out.numPopulate + 24 * out.numAdvect != size) {
    error = "header counts span " +
            std::to_string(16 + 12 * out.numPopulate + 24 * out.numAdvect) +
            " != size " + std::to_string(size);
    return false;
  }
  for (uint32_t i = 0; i < out.numPopulate; ++i) {
    CellLevelEntry e;
    e.populate = r.readU32();
    e.startTile = r.readU8();
    r.skip(3);
    e.playerSize = r.readU32();
    out.populate.push_back(e);
  }
  for (uint32_t i = 0; i < out.numAdvect; ++i) {
    CellAdvectEntry e;
    e.stageScale = r.readU32();
    e.playerSize = static_cast<int>(r.readU32());
    e.strength = r.readF32();
    e.variance = r.readF32();
    e.period = r.readF32();
    e.advectID = r.readU32();
    out.advect.push_back(e);
  }
  if (!r.ok()) {
    error = "truncated cell-world record";
    return false;
  }
  return true;
}

std::vector<std::string> cellWorldIssues(const CellWorld &w) {
  std::vector<std::string> out;
  if (w.numPopulate > 64) {
    out.push_back("numPopulate=" + i32d(static_cast<int>(w.numPopulate)));
  }
  if (w.numAdvect > 64) {
    out.push_back("numAdvect=" + i32d(static_cast<int>(w.numAdvect)));
  }
  for (const CellLevelEntry &e : w.populate) {
    if (e.startTile > 1) {
      out.push_back("level.startTile=" + i32d(e.startTile));
    }
    if (e.playerSize != 0xFFFFFFFFu && (e.playerSize == 0 || e.playerSize > 10)) {
      out.push_back("level.playerSize=" + u32hex(e.playerSize));
    }
  }
  for (const CellAdvectEntry &e : w.advect) {
    if (e.stageScale > 30) {
      out.push_back("advect.stageScale=" + u32hex(e.stageScale));
    }
    if (e.playerSize < -1 || e.playerSize > 30) {
      out.push_back("advect.playerSize=" + i32d(e.playerSize));
    }
    const float fs[] = {e.strength, e.variance, e.period};
    for (float v : fs) {
      if (!std::isfinite(v) || std::abs(v) > 10.0F) {
        out.push_back("advect.float=" + f32hex(v));
      }
    }
  }
  return out;
}

bool parseCellCell(const uint8_t *data, size_t size, CellCell &out,
                   std::string &error) {
  if (size != CellCell::kSize) {
    error = "record size " + std::to_string(size) + " != " +
            std::to_string(CellCell::kSize);
    return false;
  }
  out = CellCell{};
  Reader r(data, size);
  out.structure = r.readU32();
  uint16_t wide[80];
  for (size_t i = 0; i < 80; ++i) {
    wide[i] = r.readU16();
  }
  out.name = wideToUtf8(wide, 80);
  out.localeInstanceID = r.readU32();
  out.hp = static_cast<int>(r.readU32());
  out.fixedOrientation = r.readU8() != 0;
  r.skip(3);
  out.flags = r.readU32();
  out.cellType = r.readU32();
  out.unlockType = r.readU32();
  out.density = r.readU32();
  out.sound = r.readU32();
  out.break_ = r.readU32();
  out.pieces = r.readU32();
  out.leak = r.readU32();
  out.expel = r.readU32();
  out.explosionTable = r.readU32();
  out.loot = r.readU32();
  out.poison = r.readU32();
  out.ai = readCellAI(r);
  out.aiHard = readCellAI(r);
  out.aiEasy = readCellAI(r);
  out.friendGroup = static_cast<int>(r.readU32());
  out.wontAttackPlayer = r.readU8() != 0;
  out.wontAttackPlayerWhenSmall = r.readU8() != 0;
  r.skip(2);
  out.sizeMin = r.readF32();
  out.sizeMax = r.readF32();
  out.eat = readCellEat(r);
  out.triggersEscapeMission = r.readU8() != 0;
  r.skip(3);
  if (!r.ok()) {
    error = "truncated cell record";
    return false;
  }
  if (r.offset() != CellCell::kSize) {
    error = "field span " + std::to_string(r.offset()) + " != " +
            std::to_string(CellCell::kSize);
    return false;
  }
  return true;
}

std::vector<std::string> cellCellIssues(const CellCell &c) {
  std::vector<std::string> out;
  if (c.cellType > 7) {
    out.push_back("cellType=" + u32hex(c.cellType));
  }
  const uint32_t allowedUnlock[] = {0, 2, 4, 5, 6, 7, 8, 10};
  bool unlockOk = false;
  for (uint32_t v : allowedUnlock) {
    if (c.unlockType == v) {
      unlockOk = true;
    }
  }
  if (!unlockOk) {
    out.push_back("unlockType=" + u32hex(c.unlockType));
  }
  const uint32_t allowedDensity[] = {0, 1, 3, 4};
  bool densityOk = false;
  for (uint32_t v : allowedDensity) {
    if (c.density == v) {
      densityOk = true;
    }
  }
  if (!densityOk) {
    out.push_back("density=" + u32hex(c.density));
  }
  if (c.hp < 1 || c.hp > 4) {
    out.push_back("hp=" + i32d(c.hp));
  }
  if (c.sizeMin < 0.0F || c.sizeMin > 10.0F || c.sizeMin > c.sizeMax ||
      c.sizeMax > 10.0F) {
    out.push_back("size=[" + f32hex(c.sizeMin) + " " + f32hex(c.sizeMax) +
                  "]");
  }
  if (c.eat.foodValue < 0 || c.eat.hpValue < 0) {
    out.push_back("eat.foodValue=" + i32d(c.eat.foodValue));
    out.push_back("eat.hpValue=" + i32d(c.eat.hpValue));
  }
  checkAi(c.ai, "ai", out);
  checkAi(c.aiHard, "aiHard", out);
  checkAi(c.aiEasy, "aiEasy", out);
  return out;
}

namespace {
// Linear blend of two ramp entries by a 0..1 t.
void lerpEntry(const CellBackgroundMapEntry &a, const CellBackgroundMapEntry &b,
               float t, float out[3]) {
  out[0] = a.r + (b.r - a.r) * t;
  out[1] = a.g + (b.g - a.g) * t;
  out[2] = a.b + (b.b - a.b) * t;
}
} // namespace

bool sampleBackgroundMapColor(const CellBackgroundMap &bm, float ladder,
                              float out[3]) {
  if (bm.entries.empty()) {
    return false;
  }
  const auto &first = bm.entries.front();
  const auto &last = bm.entries.back();
  if (ladder <= first.field_C) {
    lerpEntry(first, first, 0.0F, out);
    return true;
  }
  if (ladder >= last.field_C) {
    lerpEntry(last, last, 0.0F, out);
    return true;
  }
  for (size_t i = 0; i + 1 < bm.entries.size(); ++i) {
    const CellBackgroundMapEntry &a = bm.entries[i];
    const CellBackgroundMapEntry &b = bm.entries[i + 1];
    if (ladder < a.field_C || ladder > b.field_C) {
      continue;
    }
    float t;
    if (a.field_C <= 0.0F) {
      t = b.field_C > a.field_C
              ? (ladder - a.field_C) / (b.field_C - a.field_C)
              : 0.0F;
    } else {
      const float la = std::log2(a.field_C);
      const float lb = std::log2(b.field_C);
      t = lb > la ? (std::log2(ladder) - la) / (lb - la) : 0.0F;
    }
    if (t < 0.0F) t = 0.0F;
    if (t > 1.0F) t = 1.0F;
    lerpEntry(a, b, t, out);
    return true;
  }
  lerpEntry(last, last, 0.0F, out);
  return true;
}

bool backgroundMapColorEnvelope(const CellBackgroundMap &bm, float out[6]) {
  if (bm.entries.empty()) {
    return false;
  }
  float min[3] = {bm.entries[0].r, bm.entries[0].g, bm.entries[0].b};
  float max[3] = {bm.entries[0].r, bm.entries[0].g, bm.entries[0].b};
  for (const CellBackgroundMapEntry &e : bm.entries) {
    min[0] = std::min(min[0], e.r);
    min[1] = std::min(min[1], e.g);
    min[2] = std::min(min[2], e.b);
    max[0] = std::max(max[0], e.r);
    max[1] = std::max(max[1], e.g);
    max[2] = std::max(max[2], e.b);
  }
  out[0] = min[0];
  out[1] = min[1];
  out[2] = min[2];
  out[3] = max[0];
  out[4] = max[1];
  out[5] = max[2];
  return true;
}

} // namespace openspore::assets
