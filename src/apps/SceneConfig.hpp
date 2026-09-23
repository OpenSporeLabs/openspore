// CS-23: declarative Cell Stage scene config (roadmap §3.2).
//
// The scene is data, not C++: src/apps/scene.json lists the named assets and
// their transforms. cell_stage loads it at startup; nothing about the scene is
// hard-coded in the source.
//
// Provenance is carried per value (the whole point of CS-23): the original
// cell stage places entities PROCEDURALLY — the cell `world` record (cLevelEntry)
// carries populate refs + scale and the `populate` record (cMarker) carries
// zOffset/distribution, but NO record stores a per-entity x/y. The 0x0F43029A
// world-object records are model part-definitions, not scene placement. So the
// config records, for each entity, whether its identity and position are
// VERIFIED (record-confirmed) or INFERRED (no record source).
#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace openspore::apps {

// One scene entity — mirrors the record key + transform the renderer needs.
struct SceneEntity {
  std::string role;          // scene role id (e.g. "player_cell", "food_a")
  uint32_t group = 0;        // DBPF group of the gmdl record
  uint32_t inst = 0;         // DBPF instance of the gmdl record
  float pos[3] = {0.0F, 0.0F, 0.0F};
  float targetSpan = 1.0F;
  size_t expectVerts = 0;
  bool textured = false;

  // Per-value provenance (see file header). Values: "VERIFIED" / "INFERRED".
  std::string identity = "INFERRED";
  std::string posProvenance = "INFERRED";
};

struct SceneConfig {
  std::string schema;
  std::string provenanceNote;
  std::vector<SceneEntity> entities;
};

// Parses `path` into `out`. Returns true on success; on failure returns false
// and sets `err` (missing file, parse error, or a malformed entity).
bool loadSceneConfig(const std::string &path, SceneConfig &out,
                     std::string &err);

} // namespace openspore::apps
