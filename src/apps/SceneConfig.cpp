// CS-23: loader for src/apps/scene.json. Self-contained minimal JSON parser
// (the repo has no shared JSON lib; Sim.cpp keeps its own private JSON-lines
// helpers for input scripts). Only the subset the scene schema needs.
#include "SceneConfig.hpp"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>

namespace openspore::apps {
namespace {

struct JVal {
  enum Type { Null, Bool, Num, Str, Arr, Obj } t = Null;
  bool b = false;
  double num = 0.0;
  std::string str;
  std::vector<JVal> arr;
  std::map<std::string, JVal> obj;
};

class Json {
 public:
  explicit Json(const std::string &s) : s_(s) {}

  JVal parse(std::string &err) {
    JVal v = value(err);
    if (!err.empty()) {
      return JVal{};
    }
    skipWs();
    if (pos_ != s_.size()) {
      err = "trailing characters at offset " + std::to_string(pos_);
      return JVal{};
    }
    return v;
  }

 private:
  const std::string &s_;
  size_t pos_ = 0;

  void skipWs() {
    while (pos_ < s_.size() &&
           (s_[pos_] == ' ' || s_[pos_] == '\t' || s_[pos_] == '\n' ||
            s_[pos_] == '\r')) {
      ++pos_;
    }
  }

  bool next(char c, std::string &err) {
    skipWs();
    if (pos_ < s_.size() && s_[pos_] == c) {
      ++pos_;
      return true;
    }
    err = "expected '" + std::string(1, c) + "' at offset " +
          std::to_string(pos_);
    return false;
  }

  JVal value(std::string &err) {
    skipWs();
    if (pos_ >= s_.size()) {
      err = "unexpected end of input";
      return JVal{};
    }
    const char c = s_[pos_];
    if (c == '{') return object(err);
    if (c == '[') return array(err);
    if (c == '"') {
      JVal v;
      v.t = JVal::Str;
      v.str = string();
      return v;
    }
    if (c == 't' || c == 'f') return boolean();
    if (c == 'n') {
      if (s_.compare(pos_, 4, "null") == 0) {
        pos_ += 4;
        JVal v;
        v.t = JVal::Null;
        return v;
      }
      err = "invalid literal at " + std::to_string(pos_);
      return JVal{};
    }
    return number(err);
  }

  JVal boolean() {
    if (s_.compare(pos_, 4, "true") == 0) {
      pos_ += 4;
      JVal v;
      v.t = JVal::Bool;
      v.b = true;
      return v;
    }
    if (s_.compare(pos_, 5, "false") == 0) {
      pos_ += 5;
      JVal v;
      v.t = JVal::Bool;
      v.b = false;
      return v;
    }
    JVal v;
    v.t = JVal::Null;
    return v;
  }

  JVal number(std::string &err) {
    const size_t start = pos_;
    while (pos_ < s_.size() &&
           (std::isdigit(static_cast<unsigned char>(s_[pos_])) ||
            s_[pos_] == '-' || s_[pos_] == '+' || s_[pos_] == '.' ||
            s_[pos_] == 'e' || s_[pos_] == 'E')) {
      ++pos_;
    }
    if (start == pos_) {
      err = "invalid number at offset " + std::to_string(pos_);
      return JVal{};
    }
    JVal v;
    v.t = JVal::Num;
    v.num = std::strtod(s_.c_str() + start, nullptr);
    return v;
  }

  std::string string() {
    ++pos_; // opening quote
    std::string out;
    while (pos_ < s_.size() && s_[pos_] != '"') {
      const char c = s_[pos_++];
      if (c == '\\' && pos_ < s_.size()) {
        const char e = s_[pos_++];
        switch (e) {
          case 'n': out.push_back('\n'); break;
          case 't': out.push_back('\t'); break;
          case 'r': out.push_back('\r'); break;
          case '"': out.push_back('"'); break;
          case '\\': out.push_back('\\'); break;
          case '/': out.push_back('/'); break;
          default: out.push_back(e); break;
        }
      } else {
        out.push_back(c);
      }
    }
    if (pos_ < s_.size()) {
      ++pos_; // closing quote
    }
    return out;
  }

  JVal array(std::string &err) {
    JVal v;
    v.t = JVal::Arr;
    if (!next('[', err)) return JVal{};
    skipWs();
    if (pos_ < s_.size() && s_[pos_] == ']') {
      ++pos_;
      return v;
    }
    for (;;) {
      JVal item = value(err);
      if (!err.empty()) return JVal{};
      v.arr.push_back(std::move(item));
      skipWs();
      if (pos_ >= s_.size()) {
        err = "unterminated array at offset " + std::to_string(pos_);
        return JVal{};
      }
      if (s_[pos_] == ',') {
        ++pos_;
        continue;
      }
      if (s_[pos_] == ']') {
        ++pos_;
        break;
      }
      err = "expected ',' or ']' in array at offset " + std::to_string(pos_);
      return JVal{};
    }
    return v;
  }

  JVal object(std::string &err) {
    JVal v;
    v.t = JVal::Obj;
    if (!next('{', err)) return JVal{};
    skipWs();
    if (pos_ < s_.size() && s_[pos_] == '}') {
      ++pos_;
      return v;
    }
    for (;;) {
      skipWs();
      if (pos_ >= s_.size() || s_[pos_] != '"') {
        err = "expected string key at offset " + std::to_string(pos_);
        return JVal{};
      }
      std::string key = string();
      if (!next(':', err)) return JVal{};
      JVal child = value(err);
      if (!err.empty()) return JVal{};
      v.obj[std::move(key)] = std::move(child);
      skipWs();
      if (pos_ >= s_.size()) {
        err = "unterminated object at offset " + std::to_string(pos_);
        return JVal{};
      }
      if (s_[pos_] == ',') {
        ++pos_;
        continue;
      }
      if (s_[pos_] == '}') {
        ++pos_;
        break;
      }
      err = "expected ',' or '}' in object at offset " + std::to_string(pos_);
      return JVal{};
    }
    return v;
  }
};

const JVal *get(const std::map<std::string, JVal> &o, const char *k) {
  auto it = o.find(k);
  return it == o.end() ? nullptr : &it->second;
}

std::string getStr(const std::map<std::string, JVal> &o, const char *k,
                   const std::string &d) {
  const JVal *v = get(o, k);
  return (v && v->t == JVal::Str) ? v->str : d;
}

double getNum(const std::map<std::string, JVal> &o, const char *k, double d) {
  const JVal *v = get(o, k);
  return (v && v->t == JVal::Num) ? v->num : d;
}

bool getBool(const std::map<std::string, JVal> &o, const char *k, bool d) {
  const JVal *v = get(o, k);
  return (v && v->t == JVal::Bool) ? v->b : d;
}

uint32_t getHex(const std::map<std::string, JVal> &o, const char *k,
                uint32_t d, std::string &err) {
  const JVal *v = get(o, k);
  if (!v || v->t != JVal::Str) {
    err = std::string(k) + " must be a hex string";
    return d;
  }
  char *end = nullptr;
  const uint32_t val =
      static_cast<uint32_t>(std::strtoul(v->str.c_str(), &end, 16));
  if (end == v->str.c_str()) {
    err = std::string(k) + " is not a number: " + v->str;
    return d;
  }
  return val;
}

SceneEntity entityFrom(const std::map<std::string, JVal> &o,
                       std::string &err) {
  SceneEntity e;
  e.role = getStr(o, "role", "");
  if (e.role.empty()) {
    err = "entity missing role";
    return e;
  }
  e.group = getHex(o, "group", 0, err);
  if (!err.empty()) return e;
  e.inst = getHex(o, "inst", 0, err);
  if (!err.empty()) return e;
  const JVal *p = get(o, "pos");
  if (!p || p->t != JVal::Arr || p->arr.size() != 3) {
    err = "entity " + e.role + " pos must be [x, y, z]";
    return e;
  }
  e.pos[0] = p->arr[0].num;
  e.pos[1] = p->arr[1].num;
  e.pos[2] = p->arr[2].num;
  e.targetSpan = static_cast<float>(getNum(o, "targetSpan", 1.0));
  e.expectVerts = static_cast<size_t>(std::llround(getNum(o, "expectVerts", 0.0)));
  e.textured = getBool(o, "textured", false);
  e.identity = getStr(o, "identity", "INFERRED");
  e.posProvenance = getStr(o, "pos_provenance", "INFERRED");
  return e;
}

} // namespace

bool loadSceneConfig(const std::string &path, SceneConfig &out,
                     std::string &err) {
  std::ifstream f(path);
  if (!f) {
    err = "cannot open scene config: " + path;
    return false;
  }
  std::string text((std::istreambuf_iterator<char>(f)),
                   std::istreambuf_iterator<char>());

  Json j(text);
  JVal root = j.parse(err);
  if (!err.empty()) return false;
  if (root.t != JVal::Obj) {
    err = "scene root must be a JSON object";
    return false;
  }

  out.schema = getStr(root.obj, "schema", "");
  out.provenanceNote = getStr(root.obj, "provenance_note", "");
  const JVal *ents = get(root.obj, "entities");
  if (!ents || ents->t != JVal::Arr) {
    err = "scene is missing the entities array";
    return false;
  }
  for (const JVal &e : ents->arr) {
    if (e.t != JVal::Obj) {
      err = "each entity must be a JSON object";
      return false;
    }
    SceneEntity se = entityFrom(e.obj, err);
    if (!err.empty()) return false;
    out.entities.push_back(std::move(se));
  }
  if (out.entities.empty()) {
    err = "scene has no entities";
    return false;
  }
  return true;
}

} // namespace openspore::apps
