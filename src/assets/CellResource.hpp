// Clean-room decoder for the cell-stage `cCellGlobalsResource` record.
//
// Independently authored for OpenSpore. The single stage-wide globals record
// (TYPE 0x2A3CE5B7, 276 bytes) lives in SPORE/DataEP1/Spore_EP1_Data.package
// (group 0, instance 0xa426730b). It is a DIRECT field-by-field serialization
// of the runtime struct `Simulator::Cell::cCellGlobalsResource` (Ghidra struct
// 61843 family, 276 bytes) — not wrapped in a CellSerializer name/ID envelope.
//
// The layout is evidence-confirmed: all 69 fields decode to clean hand-authored
// tuning values (round floats, small enums, u32 resource-reference keys), and
// the last field ends exactly at byte 276.
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

namespace openspore::assets {

// One decoded globals field. `u` is meaningful for u32/ref fields, `f` for
// float fields.
struct CellField {
  std::string name;
  size_t offset = 0; // byte offset from record start
  bool isFloat = false;
  uint32_t u = 0;
  float f = 0.0F;
};

// The decoded cCellGlobalsResource.
struct CellGlobals {
  static constexpr uint32_t kType = 0x2A3CE5B7;
  static constexpr size_t kSize = 276;
  static constexpr size_t kFieldCount = 69;

  size_t size = 0;
  std::vector<CellField> fields;

  // Convenience accessors (index into `fields`, safe when complete).
  uint32_t gameMode() const;
  float flowMultiplier() const;

  // True when every byte is accounted (size == kSize and field span == size).
  bool complete() const;
  size_t accounted() const; // end offset of the last field
};

// Parses a globals record. True + populated on a complete decode. False +
// error when the blob is not exactly kSize bytes.
bool parseCellGlobals(const uint8_t *data, size_t size, CellGlobals &out,
                      std::string &error);

// cAIData (180 B) — the AI tuning block embedded three times in every cell
// record (normal / hard / easy). A zeroed block (type 0xFFFFFFFF) marks the
// "no AI" default; real blocks use type 0x1000..0x10FF.
struct CellAI {
  static constexpr uint32_t kEmpty = 0xFFFFFFFFu;

  uint32_t type = kEmpty;
  float awarenessRadius = 0.0F;
  float awarenessRadiusFood = 0.0F;
  float awarenessRadiusPredator = 0.0F;
  uint32_t movementStyle = 0; // bitfield: 1=Jet, 2=Flagella, 4=Cilia
  bool flocking = false;
  float speed = 0.0F;
  float chaseSpeed = 0.0F;
  float wanderSpeed = 0.0F;
  float fleeSpeed = 0.0F;
  float fearsNearbyDamageRadius = 0.0F;
  float fearsNearbyDeathRadius = 0.0F;
  float fearsNearbyDamageTime = 0.0F;
  float fearsNearbyDeathTime = 0.0F;
  float protectRadius = 0.0F;
  float protectTime = 0.0F;
  float turnFactor = 0.0F;
  bool axialMovement = false;
  float spawnTime = 0.0F;
  float spawnRestTime = 0.0F;
  uint32_t spawnOutput = 0;
  float arcLength = 0.0F;
  float arcLengthSecondary = 0.0F;
  int numArcs = 0;
  uint32_t keyTransformation = 0;
  uint32_t keyProjectile = 0;
  uint32_t food = 0; // FoodType
  int growCount = 0;
  int digestionCount = 0;
  float digestionTime = 0.0F;
  uint32_t digestionOutput = 0;
  float fleeTime = 0.0F;
  float fleeRestTime = 0.0F;
  float chaseTime = 0.0F;
  float chaseRestTime = 0.0F;
  bool chasesDamage = false;
  bool fearsMouths = false;
  bool fearsWeapons = false;
  bool fearsElectric = false;
  bool fearsPoison = false;
  bool fearsDamage = false;
  bool ignoresFood = false;
  float awakeTime = 0.0F;
  float sleepTime = 0.0F;
  int growAmount = 0;
  float hatchDuration = 0.0F;
  float poisonRecharge = 0.0F;
  float electricRecharge = 0.0F;
  float electricRechargeVsSmall = 0.0F;
  float electricDischarge = 0.0F;

  bool empty() const { return type == kEmpty; }
  std::string dump() const; // canonical, byte-stable serialization
};

// cEatData (12 B) — what eating this cell yields.
struct CellEat {
  int foodValue = 0;
  int hpValue = 0;
  bool bomb = false;
  bool poisonNova = false;
};

// cCellCellResource (796 B) — the `cell` records (TYPE 0xDFAD9F51, 489 in
// the GOG install; 266 unique across Spore_Game + Spore_EP1_Data). DIRECT
// field-by-field serialization of the runtime struct (Ghidra 61869 family);
// no CellSerializer envelope. 70 records carry real PLACEHOLDER_* names.
struct CellCell {
  static constexpr uint32_t kType = 0xDFAD9F51;
  static constexpr size_t kSize = 796;

  uint32_t structure = 0;
  std::string name; // wchar16[80] decoded to UTF-8 ("" when unnamed)
  uint32_t localeInstanceID = 0;
  int hp = 0;
  bool fixedOrientation = false;
  uint32_t flags = 0;
  uint32_t cellType = 0;
  uint32_t unlockType = 0;
  uint32_t density = 0;
  uint32_t sound = 0;
  uint32_t break_ = 0;
  uint32_t pieces = 0;
  uint32_t leak = 0;
  uint32_t expel = 0;
  uint32_t explosionTable = 0;
  uint32_t loot = 0;
  uint32_t poison = 0;
  CellAI ai;
  CellAI aiHard;
  CellAI aiEasy;
  int friendGroup = 0;
  bool wontAttackPlayer = false;
  bool wontAttackPlayerWhenSmall = false;
  float sizeMin = 0.0F;
  float sizeMax = 0.0F;
  CellEat eat;
  bool triggersEscapeMission = false;

  // Canonical serialization of every field; two decodes of the same record
  // must produce identical strings (floats as raw bit patterns).
  std::string dump() const;
};

// cLevelEntry (12 B) — one cell to populate, at a player scale.
struct CellLevelEntry {
  uint32_t populate = 0; // cCellDataReference key (cell resource ref)
  uint8_t startTile = 0; // 0/1
  uint32_t playerSize = 0; // 1..10, or 0xFFFFFFFF = "any"
};

// cAdvectEntry (24 B) — current advect tuning. DRIFT: the SDK types
// strength/variance/period as int, but the file stores them as f32.
struct CellAdvectEntry {
  uint32_t stageScale = 0; // 1..13 observed
  int playerSize = -1; // -1 = "any"
  float strength = 0.0F; // 0.5..3.5 observed
  float variance = 0.0F; // 0.0
  float period = 0.0F; // 1.0
  uint32_t advectID = 0; // flow-field resource ref
};

// cCellWorldResource — variable length: 16 B header (two counts + two dead
// serialized pointer slots; observed ptr values 0 / 0x10 / 0x28 / 0x100) +
// numPopulate * 12 B + numAdvect * 24 B. 37 records (13 unique).
struct CellWorld {
  static constexpr uint32_t kType = 0x9B8E862F;

  uint32_t numPopulate = 0;
  uint32_t populatePtr = 0;
  uint32_t numAdvect = 0;
  uint32_t advectPtr = 0;
  std::vector<CellLevelEntry> populate;
  std::vector<CellAdvectEntry> advect;

  std::string dump() const;
};

// cEffectMapEntry (28 B) — one effect-map row.
struct CellEffectMapEntry {
  uint32_t effectID = 0; // soft effect id (mostly absent from these pkgs)
  uint32_t type = 0; // 2 / 3 / 5
  float field_8 = 0.0F; // -1.0 sentinel or 0.42 .. 5700
  float field_C = 0.0F; // -1.0 sentinel or 0.7 .. 14950
  float field_10 = 0.0F; // 0.75 .. 20000
  float field_14 = 0.0F; // 0.9 .. 20000
  int field_18 = 0; // 0 / 3 / 11
};

// cCellEffectMapResource — variable length: 8 B header +
// numEntries * 28 B. 1 instance (EP1 adds none).
struct CellEffectMap {
  static constexpr uint32_t kType = 0x433FB70C;

  int numEntries = 0; // 24
  uint32_t entriesPtr = 0; // dead ptr slot
  std::vector<CellEffectMapEntry> entries;

  std::string dump() const;
};

// cBackgroundMapEntry (16 B) — one background-map row.
struct CellBackgroundMapEntry {
  float r = 0.0F; // 0 .. 1
  float g = 0.0F; // 0 .. 1
  float b = 0.0F; // 0 .. 1
  float field_C = 0.0F; // geometric ladder 0.0 .. 100000
};

// cCellBackgroundMapResource — variable length: 8 B header +
// numEntries * 16 B. 1 instance (EP1 adds none).
struct CellBackgroundMap {
  static constexpr uint32_t kType = 0x612B3191;

  int numEntries = 0; // 12
  uint32_t entriesPtr = 0; // dead ptr slot
  std::vector<CellBackgroundMapEntry> entries;

  std::string dump() const;
};

// Parses an effect-map record (any size that matches its header count).
bool parseCellEffectMap(const uint8_t *data, size_t size, CellEffectMap &out,
                        std::string &error);

// Parses a background-map record (any size that matches its header count).
bool parseCellBackgroundMap(const uint8_t *data, size_t size,
                            CellBackgroundMap &out, std::string &error);

// Domain violations across a decoded effect-map + background-map pair.
// Empty = sane.
std::vector<std::string> cellEffectMapIssues(const CellEffectMap &em,
                                            const CellBackgroundMap &bm);

// Samples the background color ramp at a point on the geometric scale ladder.
// Each background-map entry is (r, g, b) keyed by field_C; field_C is a
// ~x3.33 geometric ladder (0, 0.5, 1.5, 5, 15, 50, 150, 500, 1500, 5000,
// 15000, 100000) that tracks the cell's world scale. `ladder` is sampled in
// log2 space between the surrounding stops (linear between the 0 stop and its
// successor); values outside the ramp clamp to the end stops. Writes r, g, b
// (each 0..1) into out[3]. False if the ramp has no usable entries.
bool sampleBackgroundMapColor(const CellBackgroundMap &bm, float ladder,
                              float out[3]);

// Per-channel min/max envelope of the ramp (out[0..2]=min, out[3..5]=max).
// False if the ramp has no usable entries.
bool backgroundMapColorEnvelope(const CellBackgroundMap &bm, float out[6]);

// cRandomCreatureEntry (28 B) — one spawnable-creature row.
struct CellRandomCreatureEntry {
  uint32_t type = 0; // 0 / 1
  uint32_t creatureID = 0; // soft creature id (not a cell-record ref)
  float weight = 0.0F; // 1.0
  int speedMin = 0; // -1 / 0 / 2
  int speedMax = 0; // -1 / 0 / 1 / 2 / 4
  int dangerMin = 0; // -1 / 0 / 1 / 2 / 3
  int dangerMax = 0; // -1 / 0 / 2 / 4 / 5 / 8
};

// cCellRandomCreatureResource — variable length: 8 B header +
// numEntries * 28 B. 10 instances (EP1 adds 3).
struct CellRandomCreature {
  static constexpr uint32_t kType = 0xF9C3D770;

  int numEntries = 0; // 1 / 4
  uint32_t entriesPtr = 0; // dead ptr slot
  std::vector<CellRandomCreatureEntry> entries;

  std::string dump() const;
};

// cCellPowersResource — fixed 8 B. 1 instance.
struct CellPowers {
  static constexpr uint32_t kType = 0x754BE343;

  int teleportCost = 0; // 10
  float teleportRange = 0.0F; // 10.0

  std::string dump() const;
};

// Parses a random-creature record (any size that matches its header count).
bool parseCellRandomCreature(const uint8_t *data, size_t size,
                             CellRandomCreature &out, std::string &error);

// Parses a powers record (must be exactly 8 B).
bool parseCellPowers(const uint8_t *data, size_t size, CellPowers &out,
                     std::string &error);

// Domain violations across a decoded random-creature + powers pair. Empty = sane.
std::vector<std::string> cellRandomCreatureIssues(const CellRandomCreature &rc,
                                                 const CellPowers &pw);

// cLookTableEntry (8 B) — one look/variant value row.
struct CellLookEntry {
  int type = 0; // 0..11
  float value = 0.0F; // 1 / 5 / 10
};

// cCellLookTableResource — variable length: 8 B header + numEntries * 8 B.
// 10 instances (9 unique; EP1 adds none).
struct CellLookTable {
  static constexpr uint32_t kType = 0x8C042499;

  uint32_t entriesPtr = 0; // dead ptr slot
  int numEntries = 0;
  std::vector<CellLookEntry> entries;

  std::string dump() const;
};

// cLookAlgorithmEntry (20 B) — one look-algorithm row.
struct CellLookAlgoEntry {
  uint32_t type = 0; // 0 / 1 / 2
  uint32_t action = 0; // 0 / 18..22 / 0xFFFFFFFF
  uint32_t player = 0; // look-table ref
  uint32_t npc = 0; // look-table ref
  uint32_t epic = 0; // look-table ref
};

// cCellLookAlgorithmResource — variable length: 8 B header + numEntries * 20 B.
// 1 instance.
struct CellLookAlgorithm {
  static constexpr uint32_t kType = 0xDBA35AE2;

  uint32_t entriesPtr = 0; // dead ptr slot
  int numEntries = 0;
  std::vector<CellLookAlgoEntry> entries;

  std::string dump() const;
};

// Parses a look-table record (any size that matches its header count).
bool parseCellLookTable(const uint8_t *data, size_t size, CellLookTable &out,
                        std::string &error);

// Parses a look-algorithm record (any size that matches its header count).
bool parseCellLookAlgorithm(const uint8_t *data, size_t size,
                            CellLookAlgorithm &out, std::string &error);

// Domain violations; non-null algorithm table refs must be in lookTableInsts.
std::vector<std::string> cellLookIssues(const CellLookTable &t,
                                        const CellLookAlgorithm &a,
                                        const std::unordered_set<uint32_t> &lookTableInsts);

// cLootTableEntry (28 B) — one reward row in a loot table.
struct CellLootEntry {
  uint32_t type = 0; // 0 Nothing / 1 Cell / 2 Table
  uint32_t cell = 0; // 0 or a cell record ref
  uint32_t table = 0; // 0 or a loot-table record ref
  float weight = 0.0F; // percent-ish, ~0.01..90
  int count = 0; // 0..4
  int countDelta = 0; // 0 / 1
  int levelOffset = 0; // -3..1
};

// cCellLootTableResource — variable length: 36 B header + numEntries * 28 B.
// 45 unique records (53+53+9 instances; EP1 adds 9).
struct CellLootTable {
  static constexpr uint32_t kType = 0xD92AF091;

  uint32_t entriesPtr = 0; // dead ptr slot
  int numEntries = 0; // 0..9
  float minRadius = 0.0F; // all 0
  float maxRadius = 0.0F; // all 0
  float initialAlpha = 1.0F; // all 1
  float expelForce = 0.0F; // 0 / 1 / 4
  int effect = 0; // all 0
  uint8_t mustHavePart = 0; // 0 / 1
  float delay = 0.0F; // 0 / 1
  std::vector<CellLootEntry> entries;

  std::string dump() const;
};

// Parses a loot-table record (any size that matches its header count).
bool parseCellLootTable(const uint8_t *data, size_t size, CellLootTable &out,
                        std::string &error);

// Domain violations; non-null entry cell/table refs must be in the given sets.
// Empty = sane.
std::vector<std::string> cellLootTableIssues(
    const CellLootTable &t, const std::unordered_set<uint32_t> &cellInsts,
    const std::unordered_set<uint32_t> &lootInsts);

// cSPAttachment (40 B) — one attachable effect on a structure bone.
struct CellStructureAtt {
  int bone = 0; // 0 / 3 / -1
  uint32_t type = 0; // 0 / 1 / 3 / 4 / 5 / 6
  uint32_t structure = 0; // all 0
  uint32_t randomCreature = 0; // 0 or a random-creature ref
  int effectID = 0; // 128 distinct, negative ok
  int levelMin = 0; // 0 / -1
  int levelMax = 0; // 0 / 10 / -1
  float color[3] = {0.0F, 0.0F, 0.0F}; // RGB, 0..1.5
};

// cCellStructureResource — variable length: 28 B header + numAttachments * 40 B.
// 149 unique records (170 distinct instance ids; EP1 adds 38).
struct CellStructure {
  static constexpr uint32_t kType = 0x4B9EF6DC;

  uint32_t onDeath = 0; // effect ref (21 distinct)
  uint32_t onDeathSmall = 0; // mostly 0
  uint32_t onDeathLarge = 0; // mostly 0
  uint32_t onHatch = 0; // mostly 0
  uint32_t onStartHatch = 0; // all 0
  uint32_t attachmentsPtr = 0; // dead ptr slot
  int numAttachments = 0; // 1..3
  std::vector<CellStructureAtt> atts;

  std::string dump() const;
};

// Parses a structure record (any size that matches its header count).
bool parseCellStructure(const uint8_t *data, size_t size, CellStructure &out,
                        std::string &error);

// Domain violations. Empty = sane.
std::vector<std::string> cellStructureIssues(const CellStructure &s);

// cMarker (76 B) — one scene spawner. Several fields are dead zero slots.
struct CellMarker {
  uint32_t field_0 = 0, field_4 = 0, field_8 = 0;
  float zOffset = 0.0F; // 0..25
  float zOffsetMax = 0.0F; // 0..35
  uint32_t field_14 = 0;
  uint32_t distributeCell = 0; // 0 (null) or a cell record ref
  uint32_t clusterCell = 0; // 0 or a cell record ref
  uint32_t encounterPopulate = 0; // all 0
  uint32_t plantType = 0; // 0..2
  uint32_t type = 0; // 0..2
  float count = 0.0F; // -1 (any) .. 800
  float countEasy = 0.0F; // -1 .. 8
  float countMed = 0.0F; // -1 .. 8
  float countHard = 0.0F; // -1 .. 7
  int size = 0; // 0..12
  int parts = 0; // 0 / 3 / 4 / 5
  int linear = 0; // 0 / 1
  int encounterScale = 0; // 0
};

// cCellPopulateResource — variable length: 16 B header + numMarkers * 76 B.
// 21 unique records (20 in Spore_Game, 1 EP1-only).
struct CellPopulate {
  static constexpr uint32_t kType = 0xDA141C1B;

  uint32_t scale = 0; // 0 = any; 3 / 4 observed
  uint32_t maskTexture = 0; // all 0
  uint32_t numMarkers = 0;
  uint32_t markersPtr = 0; // dead ptr slot; 0 / 16 observed
  std::vector<CellMarker> markers;

  std::string dump() const;
};

// Parses a populate record (any size that matches its header count).
bool parseCellPopulate(const uint8_t *data, size_t size, CellPopulate &out,
                       std::string &error);

// Domain violations; non-null distributeCell/clusterCell refs must be in
// cellInsts (the 0xDFAD9F51 instance ids). Empty = sane.
std::vector<std::string> cellPopulateIssues(const CellPopulate &p,
                                           const std::unordered_set<uint32_t> &cellInsts);

// Parses a cell-world record (any size that matches its header counts).
bool parseCellWorld(const uint8_t *data, size_t size, CellWorld &out,
                    std::string &error);

// Returns the list of field-domain violations (empty = sane).
std::vector<std::string> cellWorldIssues(const CellWorld &w);

// Parses a cell record. True + populated on success; false + error when the
// blob is not exactly kSize bytes.
bool parseCellCell(const uint8_t *data, size_t size, CellCell &out,
                   std::string &error);

// Returns the list of field-domain violations (empty = sane). Domains are the
// observed superset across all 266 unique records.
std::vector<std::string> cellCellIssues(const CellCell &c);

} // namespace openspore::assets
