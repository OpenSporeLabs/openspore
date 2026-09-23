// Contract test for the canonical Cell simulation (Obj35,
// docs/CELL-CONTRACT.md, version cell-sim-contract/2).
//
// Replays every FROZEN fixture from tests/fixtures/cell/fixtures.json through
// CellSim and asserts, per frame:
//   - player pos/heading/vel/growMeter match the frozen expected values
//     EXACTLY (bit-exact float32; the fixture's %.9g decimals round-trip the
//     emitted bits)
//   - per-frame events (type + entity) match exactly, in order
//   - per-frame entity alive-flags match exactly
// plus: determinism (run each fixture twice -> identical state + events) and
// the contract version string. This is the baseline Obj36 will diff against.
//
// Pure C++ + stdlib; the fixture path is passed at build time (CMake define
// CELL_FIXTURES_PATH). No SPORE/ package, no GPU — CI-safe.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Sim.hpp"
#include "contract_scenarios.hpp"

namespace {

using openspore::sim::CellSim;
using openspore::sim::Entity;
using openspore::sim::FrameSnapshot;
using openspore::sim::InputFrame;
using openspore::sim::makeSim;
using openspore::sim::MovementParams;
using openspore::sim::MovementPlane;
using openspore::sim::PlayerState;
using openspore::sim::Scenario;
using openspore::sim::scenarios;
using openspore::sim::SimEvent;

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

void checkMsg(bool cond, const std::string &msg) { check(cond, msg.c_str()); }

// ---- minimal recursive-descent JSON parser (object/array/string/number/
// boolean/null; the fixture file uses no other syntax) --------------------

struct Json {
  enum class T { Null, Bool, Num, Str, Arr, Obj };
  T t = T::Null;
  bool b = false;
  double num = 0.0;
  std::string str;
  std::vector<Json> arr;
  std::vector<std::pair<std::string, Json>> obj;

  const Json *find(const char *key) const {
    for (const auto &kv : obj) {
      if (kv.first == key) {
        return &kv.second;
      }
    }
    return nullptr;
  }
};

struct JsonParser {
  const std::string &s;
  std::size_t p = 0;
  std::string err;

  explicit JsonParser(const std::string &text) : s(text) {}

  void ws() {
    while (p < s.size() &&
           (s[p] == ' ' || s[p] == '\t' || s[p] == '\n' || s[p] == '\r')) {
      ++p;
    }
  }

  bool parseValue(Json &out) {
    ws();
    if (p >= s.size()) {
      err = "truncated input";
      return false;
    }
    const char c = s[p];
    if (c == '{') {
      return parseObj(out);
    }
    if (c == '[') {
      return parseArr(out);
    }
    if (c == '"') {
      out.t = Json::T::Str;
      return parseStr(out.str);
    }
    if (c == 't' && s.compare(p, 4, "true") == 0) {
      out.t = Json::T::Bool;
      out.b = true;
      p += 4;
      return true;
    }
    if (c == 'f' && s.compare(p, 5, "false") == 0) {
      out.t = Json::T::Bool;
      out.b = false;
      p += 5;
      return true;
    }
    if (c == 'n' && s.compare(p, 4, "null") == 0) {
      out.t = Json::T::Null;
      p += 4;
      return true;
    }
    out.t = Json::T::Num;
    const char *end = nullptr;
    out.num = std::strtod(s.c_str() + p, const_cast<char **>(&end));
    if (end == s.c_str() + p) {
      err = "bad number at " + std::to_string(p);
      return false;
    }
    p = static_cast<std::size_t>(end - s.c_str());
    return true;
  }

  bool parseStr(std::string &out) {
    ++p; // opening quote
    out.clear();
    while (p < s.size()) {
      const char c = s[p++];
      if (c == '"') {
        return true;
      }
      if (c != '\\') {
        out += c;
        continue;
      }
      if (p >= s.size()) {
        err = "dangling escape";
        return false;
      }
      const char e = s[p++];
      switch (e) {
      case '"':
        out += '"';
        break;
      case '\\':
        out += '\\';
        break;
      case '/':
        out += '/';
        break;
      case 'n':
        out += '\n';
        break;
      case 't':
        out += '\t';
        break;
      case 'r':
        out += '\r';
        break;
      case 'b':
        out += '\b';
        break;
      case 'f':
        out += '\f';
        break;
      default:
        err = "bad escape";
        return false;
      }
    }
    err = "unterminated string";
    return false;
  }

  bool parseArr(Json &out) {
    out.t = Json::T::Arr;
    ++p;
    ws();
    if (p < s.size() && s[p] == ']') {
      ++p;
      return true;
    }
    for (;;) {
      Json item;
      if (!parseValue(item)) {
        return false;
      }
      out.arr.push_back(std::move(item));
      ws();
      if (p >= s.size()) {
        err = "unterminated array";
        return false;
      }
      if (s[p] == ',') {
        ++p;
        continue;
      }
      if (s[p] == ']') {
        ++p;
        return true;
      }
      err = "expected ',' or ']'";
      return false;
    }
  }

  bool parseObj(Json &out) {
    out.t = Json::T::Obj;
    ++p;
    ws();
    if (p < s.size() && s[p] == '}') {
      ++p;
      return true;
    }
    for (;;) {
      ws();
      std::string key;
      if (!parseStr(key)) {
        return false;
      }
      ws();
      if (p >= s.size() || s[p] != ':') {
        err = "expected ':'";
        return false;
      }
      ++p;
      Json val;
      if (!parseValue(val)) {
        return false;
      }
      out.obj.emplace_back(std::move(key), std::move(val));
      ws();
      if (p >= s.size()) {
        err = "unterminated object";
        return false;
      }
      if (s[p] == ',') {
        ++p;
        continue;
      }
      if (s[p] == '}') {
        ++p;
        return true;
      }
      err = "expected ',' or '}'";
      return false;
    }
  }
};

// ---- fixture -> Scenario ---------------------------------------------------

float jf(const Json *o, const char *key, float def) {
  const Json *v = o != nullptr ? o->find(key) : nullptr;
  return v != nullptr && v->t == Json::T::Num ? static_cast<float>(v->num)
                                              : def;
}

std::vector<float> jvec3(const Json *o, const char *key) {
  std::vector<float> v(3, 0.0F);
  const Json *a = o != nullptr ? o->find(key) : nullptr;
  if (a != nullptr && a->t == Json::T::Arr && a->arr.size() == 3) {
    for (int i = 0; i < 3; ++i) {
      v[i] = static_cast<float>(a->arr[i].num);
    }
  }
  return v;
}

InputFrame parseFrame(const Json *fr) {
  InputFrame f;
  const Json *keys = fr->find("keys");
  if (keys != nullptr && keys->t == Json::T::Arr) {
    for (const Json &k : keys->arr) {
      if (k.t != Json::T::Str) {
        continue;
      }
      if (k.str == "left") {
        f.thrustLeft = true;
      } else if (k.str == "right") {
        f.thrustRight = true;
      } else if (k.str == "forward") {
        f.thrustForward = true;
      } else if (k.str == "back") {
        f.thrustBack = true;
      } else if (k.str == "boost") {
        f.boost = true;
      }
    }
  }
  const Json *cam = fr->find("camera");
  if (cam != nullptr) {
    f.hasCamera = true;
    f.cameraYaw = jf(cam, "yaw", 0.0F);
    f.cameraPitch = jf(cam, "pitch", 0.0F);
    f.cameraZoom = jf(cam, "zoom", 1.0F);
  }
  const Json *mouse = fr->find("mouse");
  if (mouse != nullptr && mouse->t == Json::T::Arr && mouse->arr.size() == 2) {
    f.hasMouse = true;
    f.mouseX = static_cast<float>(mouse->arr[0].num);
    f.mouseY = static_cast<float>(mouse->arr[1].num);
  }
  return f;
}

Scenario parseScenario(const Json &js, std::string &err) {
  Scenario s;
  const Json *name = js.find("name");
  const Json *desc = js.find("description");
  s.name = name != nullptr && name->t == Json::T::Str ? name->str : "";
  s.description = desc != nullptr && desc->t == Json::T::Str ? desc->str : "";

  const Json *ents = js.find("entities");
  if (ents != nullptr && ents->t == Json::T::Arr) {
    for (const Json &je : ents->arr) {
      Entity e;
      const Json *role = je.find("role");
      if (role == nullptr || role->t != Json::T::Str) {
        err = "entity without role in scenario " + s.name;
        return s;
      }
      e.role = role->str;
      const std::vector<float> pos = jvec3(&je, "pos");
      for (int i = 0; i < 3; ++i) {
        e.pos[i] = pos[i];
      }
      s.entities.push_back(e);
    }
  }

  const Json *cam = js.find("camera");
  s.camera.yaw = jf(cam, "yaw", 0.0F);
  s.camera.pitch = jf(cam, "pitch", 0.0F);
  s.camera.zoom = jf(cam, "zoom", 1.0F);
  s.camera.baseDist = jf(cam, "baseDist", 16.0F);
  s.camera.fov = jf(cam, "fov", 60.0F * 3.14159265358979F / 180.0F);

  const Json *plane = js.find("plane");
  const std::vector<float> n = jvec3(plane, "normal");
  const std::vector<float> pt = jvec3(plane, "point");
  for (int i = 0; i < 3; ++i) {
    s.plane.normal[i] = n[i];
    s.plane.point[i] = pt[i];
  }

  const Json *frames = js.find("frames");
  if (frames == nullptr || frames->t != Json::T::Arr) {
    err = "scenario " + s.name + " has no frames";
    return s;
  }
  for (const Json &jf : frames->arr) {
    s.frames.push_back(parseFrame(&jf));
  }
  return s;
}

// ---- per-frame exact comparison --------------------------------------------

bool snapMatches(const FrameSnapshot &got, const Json &exp,
                 const std::string &what) {
  const Json *pos = exp.find("pos");
  if (pos == nullptr || pos->t != Json::T::Arr || pos->arr.size() != 3) {
    std::printf("FAIL: %s: expected pos missing\n", what.c_str());
    ++g_failures;
    return false;
  }
  bool ok = true;
  for (int i = 0; i < 3; ++i) {
    if (got.pos[i] != static_cast<float>(pos->arr[i].num)) {
      ok = false;
      std::printf("FAIL: %s: pos[%d] got %.9g want %.9g\n", what.c_str(), i,
                  got.pos[i], static_cast<float>(pos->arr[i].num));
    }
  }
  const Json *heading = exp.find("heading");
  if (heading == nullptr || heading->t != Json::T::Num ||
      got.heading != static_cast<float>(heading->num)) {
    ok = false;
    std::printf("FAIL: %s: heading got %.9g want %.9g\n", what.c_str(),
                got.heading,
                heading != nullptr ? static_cast<float>(heading->num) : 0.0F);
  }
  const Json *vel = exp.find("vel");
  if (vel == nullptr || vel->t != Json::T::Arr || vel->arr.size() != 3) {
    std::printf("FAIL: %s: expected vel missing\n", what.c_str());
    ++g_failures;
    return false;
  }
  for (int i = 0; i < 3; ++i) {
    if (got.vel[i] != static_cast<float>(vel->arr[i].num)) {
      ok = false;
      std::printf("FAIL: %s: vel[%d] got %.9g want %.9g\n", what.c_str(), i,
                  got.vel[i], static_cast<float>(vel->arr[i].num));
    }
  }
  const Json *grow = exp.find("growMeter");
  if (grow == nullptr || grow->t != Json::T::Num ||
      got.growMeter != static_cast<int>(grow->num)) {
    ok = false;
    std::printf("FAIL: %s: growMeter got %d want %d\n", what.c_str(),
                got.growMeter,
                grow != nullptr ? static_cast<int>(grow->num) : -1);
  }
  const Json *events = exp.find("events");
  std::vector<std::pair<std::string, std::string>> wantEvents;
  if (events != nullptr && events->t == Json::T::Arr) {
    for (const Json &je : events->arr) {
      if (je.t != Json::T::Arr || je.arr.size() != 2 ||
          je.arr[0].t != Json::T::Str || je.arr[1].t != Json::T::Str) {
        ok = false;
        std::printf("FAIL: %s: malformed event entry\n", what.c_str());
        ++g_failures;
        return false;
      }
      wantEvents.emplace_back(je.arr[0].str, je.arr[1].str);
    }
  }
  if (wantEvents.size() != got.eventTypes.size()) {
    ok = false;
    std::printf("FAIL: %s: event count got %zu want %zu\n", what.c_str(),
                got.eventTypes.size(), wantEvents.size());
  } else {
    for (size_t e = 0; e < wantEvents.size(); ++e) {
      if (got.eventTypes[e] != wantEvents[e].first ||
          got.eventEntities[e] != wantEvents[e].second) {
        ok = false;
        std::printf("FAIL: %s: event %d got [%s,%s] want [%s,%s]\n",
                    what.c_str(), static_cast<int>(e),
                    got.eventTypes[e].c_str(), got.eventEntities[e].c_str(),
                    wantEvents[e].first.c_str(), wantEvents[e].second.c_str());
      }
    }
  }
  const Json *alive = exp.find("alive");
  if (alive == nullptr || alive->t != Json::T::Arr) {
    std::printf("FAIL: %s: expected alive missing\n", what.c_str());
    ++g_failures;
    return false;
  }
  if (alive->arr.size() != got.alive.size()) {
    ok = false;
    std::printf("FAIL: %s: alive count got %zu want %zu\n", what.c_str(),
                got.alive.size(), alive->arr.size());
  } else {
    for (size_t a = 0; a < got.alive.size(); ++a) {
      if (got.alive[a] != alive->arr[a].b) {
        ok = false;
        std::printf("FAIL: %s: alive[%zu] got %d want %d\n", what.c_str(), a,
                    got.alive[a] ? 1 : 0, alive->arr[a].b ? 1 : 0);
      }
    }
  }
  return ok;
}

// Replays a scenario live and compares every frame against the frozen
// expected values.
void replayAndCompare(const Scenario &sc, const Json &js) {
  const Json *expected = js.find("expected");
  const Json *frames = js.find("frames");
  if (expected == nullptr || expected->t != Json::T::Obj ||
      expected->find("frames") == nullptr ||
      expected->find("frames")->t != Json::T::Arr) {
    std::printf("FAIL: %s: missing expected.frames\n", sc.name.c_str());
    ++g_failures;
    return;
  }
  const std::vector<Json> &want = expected->find("frames")->arr;
  if (frames == nullptr || frames->t != Json::T::Arr ||
      frames->arr.size() != sc.frames.size() ||
      want.size() != sc.frames.size()) {
    std::printf(
        "FAIL: %s: frame count mismatch (fixture %zu, scenario %zu, "
        "expected %zu)\n",
        sc.name.c_str(),
        frames != nullptr && frames->t == Json::T::Arr ? frames->arr.size() : 0,
        sc.frames.size(), want.size());
    ++g_failures;
    return;
  }

  // (b) determinism: two fresh replays must be bit-identical.
  CellSim a = makeSim(sc);
  CellSim b = makeSim(sc);
  for (const InputFrame &fr : sc.frames) {
    a.update(fr);
    b.update(fr);
  }
  const std::string stateA = a.stateString();
  const std::string stateB = b.stateString();
  checkMsg(stateA == stateB, sc.name + ": two runs of the same fixture -> "
                                       "identical stateString");
  checkMsg(a.events() == b.events(), sc.name + ": two runs -> identical event "
                                               "log");

  // (a) exact match against the frozen oracle, frame by frame.
  const std::vector<FrameSnapshot> got = [sc]() {
    CellSim sim = makeSim(sc);
    std::vector<FrameSnapshot> out;
    for (const InputFrame &fr : sc.frames) {
      const std::vector<SimEvent> ev = sim.update(fr);
      FrameSnapshot sn;
      const PlayerState &p = sim.player();
      for (int i = 0; i < 3; ++i) {
        sn.pos[i] = p.pos[i];
        sn.vel[i] = p.vel[i];
      }
      sn.heading = p.heading;
      sn.growMeter = p.growMeter;
      for (const SimEvent &e : ev) {
        sn.eventTypes.push_back(e.type != nullptr ? e.type : "");
        sn.eventEntities.push_back(e.entity);
      }
      for (const Entity &e : sim.entities()) {
        sn.alive.push_back(e.alive);
      }
      out.push_back(std::move(sn));
    }
    return out;
  }();

  int badFrames = 0;
  for (size_t i = 0; i < want.size(); ++i) {
    const std::string what = sc.name + " frame " + std::to_string(i);
    if (!snapMatches(got[i], want[i], what)) {
      ++badFrames;
    }
  }
  checkMsg(badFrames == 0, sc.name + ": all " + std::to_string(want.size()) +
                               " frames match the frozen expected values "
                               "exactly");
}

} // namespace

#ifndef CELL_FIXTURES_PATH
#define CELL_FIXTURES_PATH "tests/fixtures/cell/fixtures.json"
#endif

int main() {
  const char *path = CELL_FIXTURES_PATH;
  std::ifstream f(path, std::ios::binary);
  if (!f) {
    std::printf("FAIL: cannot open fixture file %s\n", path);
    return 1;
  }
  std::ostringstream ss;
  ss << f.rdbuf();
  const std::string text = ss.str();

  Json root;
  JsonParser parser(text);
  if (!parser.parseValue(root) || root.t != Json::T::Obj) {
    std::printf("FAIL: fixture file does not parse (%s)\n", parser.err.c_str());
    return 1;
  }

  // (c) the contract version string must be present and pinned.
  const Json *contract = root.find("contract");
  const std::string version =
      contract != nullptr && contract->t == Json::T::Str ? contract->str : "";
  checkMsg(version == openspore::sim::kContractVersion,
           std::string("contract version in fixtures: ") + version +
               " == " + openspore::sim::kContractVersion);

  const Json *scens = root.find("scenarios");
  checkMsg(scens != nullptr && scens->t == Json::T::Arr && !scens->arr.empty(),
           "fixtures: scenarios array present and non-empty");
  if (scens == nullptr || scens->t != Json::T::Arr) {
    if (g_failures == 0) {
      std::printf("sim_contract_test: ALL PASS\n");
      return 0;
    }
    std::printf("sim_contract_test: %d FAILURES\n", g_failures);
    return 1;
  }

  // Every fixture scenario must map 1:1 onto the defined scenario set (names
  // in the same order — the fixture file is generated from scenarios()).
  const std::vector<Scenario> &defined = scenarios();
  checkMsg(defined.size() == scens->arr.size(),
           std::string("fixture scenario count ") +
               std::to_string(scens->arr.size()) +
               " == defined scenario count " + std::to_string(defined.size()));

  for (size_t i = 0; i < scens->arr.size(); ++i) {
    const Json &js = scens->arr[i];
    std::string err;
    const Scenario sc = parseScenario(js, err);
    if (!err.empty()) {
      checkMsg(false, "fixture scenario " + std::to_string(i) + ": " + err);
      continue;
    }
    const bool nameMatch = i < defined.size() && sc.name == defined[i].name;
    checkMsg(nameMatch,
             "fixture scenario " + std::to_string(i) + " name " + sc.name +
                 (nameMatch ? " matches the defined scenario"
                            : " does NOT match the defined scenario"));
    if (!nameMatch) {
      continue;
    }
    // Stale-fixture guard: the frozen frame count must equal the defined
    // scenario's frame count. A trimmed/dropped-frames fixture (e.g. a
    // scenario defined with 30 frames but frozen with 0) must FAIL LOUDLY
    // here instead of passing silently with 0 frames compared.
    const bool frameCountMatch = sc.frames.size() == defined[i].frames.size();
    checkMsg(frameCountMatch, "fixture scenario " + std::to_string(i) + " (" +
                                  sc.name + ") frame " + "count " +
                                  std::to_string(sc.frames.size()) +
                                  " == defined frame "
                                  "count " +
                                  std::to_string(defined[i].frames.size()));
    if (!frameCountMatch) {
      continue; // don't compare a mismatched frame sequence
    }
    replayAndCompare(sc, js);
  }

  if (g_failures == 0) {
    std::printf("sim_contract_test: ALL PASS (%zu fixtures, %s)\n",
                scens->arr.size(), openspore::sim::kContractVersion);
    return 0;
  }
  std::printf("sim_contract_test: %d FAILURES\n", g_failures);
  return 1;
}
