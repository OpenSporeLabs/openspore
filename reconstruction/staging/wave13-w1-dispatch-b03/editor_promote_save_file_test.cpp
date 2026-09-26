#include "editor_promote_save_file.hpp"

#include <cstdio>
#include <string>
#include <vector>

namespace {

using openspore::reconstruction::wave13_w1_dispatch_b03::OpaqueString16;

struct Call {
  std::string op;
  std::vector<std::string> args;
};

std::vector<Call> g_calls;
std::vector<char16_t*> g_heap;

void record(const char* op, const std::string& a, const std::string& b = "",
            int c = -1) {
  Call call;
  call.op = op;
  call.args.push_back(a);
  if (c >= 0) {
    call.args.push_back(b);
    call.args.push_back(std::to_string(c));
  } else if (!b.empty()) {
    call.args.push_back(b);
  }
  g_calls.push_back(call);
}

std::string flatten(const char16_t* text) {
  std::string out;
  for (const char16_t* p = text; *p != u'\0'; ++p) {
    out.push_back(static_cast<char>(*p & 0x7f));
  }
  return out;
}

std::string line_of(const Call& call) {
  std::string out = call.op;
  for (const auto& arg : call.args) {
    out += " " + arg;
  }
  return out;
}

}  // namespace

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// The literal is defined once in the reconstruction unit; the model test
// only needs the operation trace, so it is not duplicated here.
extern const char16_t kOldSuffix[];

namespace unresolved_ports {

void __thiscall string16_reserve(OpaqueString16* dst, unsigned int count) {
  if (count < 2) {
    dst->begin = dst->end = dst->capacity = const_cast<char16_t*>(u"");
    return;
  }
  auto* buffer = new char16_t[count];
  g_heap.push_back(buffer);
  buffer[0] = u'\0';
  dst->begin = buffer;
  dst->end = buffer;
  dst->capacity = buffer + count;
}

void __thiscall string16_assign(OpaqueString16* dst, const char16_t* src) {
  unsigned int length = 0;
  while (src[length] != u'\0') {
    ++length;
  }
  string16_reserve(dst, length + 1u);
  for (unsigned int i = 0; i < length; ++i) {
    dst->begin[i] = src[i];
  }
  dst->end = dst->begin + length;
  *dst->end = u'\0';
}

OpaqueString16* __thiscall string16_concat(OpaqueString16* dst,
                                          const OpaqueString16* a,
                                          const OpaqueString16* b) {
  const auto len_a = static_cast<unsigned int>(
      (reinterpret_cast<const char*>(a->end) -
       reinterpret_cast<const char*>(a->begin)) >>
      1);
  const auto len_b = static_cast<unsigned int>(
      (reinterpret_cast<const char*>(b->end) -
       reinterpret_cast<const char*>(b->begin)) >>
      1);
  dst->begin = dst->end = dst->capacity = nullptr;
  string16_reserve(dst, len_a + len_b + 1u);
  for (unsigned int i = 0; i < len_a; ++i) {
    dst->begin[i] = a->begin[i];
  }
  for (unsigned int i = 0; i < len_b; ++i) {
    dst->begin[len_a + i] = b->begin[i];
  }
  dst->end = dst->begin + len_a + len_b;
  *dst->end = u'\0';
  return dst;
}

namespace {

// The base path the fake save area reports. It ends with a separator because
// the observed concatenation inserts none.
const char16_t* __thiscall fake_save_area_path_28(void*) {
  static char16_t buffer[] = u"C:/Save/Game0/";
  return buffer;
}

int g_save_area = 0;
int g_vtable[0x2c / 4 + 1] = {0};

}  // namespace

void* __cdecl lookup_save_area_by_id(unsigned int id) {
  if (id != 0x4729a47u) {
    return nullptr;
  }
  g_vtable[0] = reinterpret_cast<int>(&g_save_area);
  g_vtable[0x28 / 4] = reinterpret_cast<int>(&fake_save_area_path_28);
  g_save_area = reinterpret_cast<int>(&g_vtable[0]);
  return &g_save_area;
}

unsigned char __cdecl file_exists(const char16_t* path) {
  record("exists", flatten(path));
  return 0;
}

unsigned int __cdecl move_file(const char16_t* src, const char16_t* dst,
                               char allow_overwrite) {
  record("move", flatten(src), flatten(dst),
         static_cast<int>(allow_overwrite));
  return 1;
}

bool __cdecl delete_file(const char16_t* path) {
  record("delete", flatten(path));
  return true;
}

unsigned int __cdecl delete_path_recursive(const char16_t* path) {
  record("delete_tree", flatten(path));
  return 1;
}

void* __cdecl memcpy(void* dst, const void* src, unsigned long size) {
  auto* out = static_cast<unsigned char*>(dst);
  const auto in = static_cast<const unsigned char*>(src);
  for (unsigned long i = 0; i < size; ++i) {
    out[i] = in[i];
  }
  return dst;
}

void __cdecl eastl_deallocate(void* p) {
  record("free", std::to_string(reinterpret_cast<unsigned long>(p)));
}

}  // namespace unresolved_ports
}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03

int main() {
  using namespace openspore::reconstruction::wave13_w1_dispatch_b03;

  g_calls.clear();
  g_heap.clear();

  // The literals and the argument order are the ones read live at 0x0147e040
  // and 0x0145fb88 and pushed by the caller at 0x00de48e1/0x00de48e6.
  editor_promote_save_file_006891f0(u"GGEUserData.dat.tmp",
                                    u"GGEUserData.dat");

  int failures = 0;
  std::printf("observed operation sequence (%zu calls):\n", g_calls.size());
  for (std::size_t i = 0; i < g_calls.size(); ++i) {
    std::printf("  %2zu %s\n", i, line_of(g_calls[i]).c_str());
  }

  // file_exists returns 0 in this harness, so neither conditional branch fires
  // and exactly one move - the unconditional promotion - must be observed.
  std::size_t moves = 0;
  for (const auto& call : g_calls) {
    if (call.op == "move") {
      ++moves;
    }
    if (call.op == "delete") {
      ++failures;
      std::printf("FAIL unexpected delete (guard should have been false)\n");
    }
  }
  if (moves != 1) {
    ++failures;
    std::printf("FAIL expected exactly 1 move, got %zu\n", moves);
  }
  if (g_calls.empty() || g_calls.front().op != "delete_tree") {
    ++failures;
    std::printf("FAIL the base-path delete_tree is not the first operation\n");
  }

  const char* expected[] = {
      "delete_tree C:/Save/Game0/",
      "move C:/Save/Game0/GGEUserData.dat.tmp C:/Save/Game0/GGEUserData.dat 1",
      "exists C:/Save/Game0/GGEUserData.dat",
      "exists C:/Save/Game0/GGEUserData.dat.old",
  };
  for (const char* want : expected) {
    bool found = false;
    for (const auto& call : g_calls) {
      if (line_of(call) == want) {
        found = true;
      }
    }
    if (!found) {
      ++failures;
      std::printf("FAIL missing operation: %s\n", want);
    }
  }

  if (failures == 0) {
    std::printf("006891f0 model test: all cases passed\n");
    return 0;
  }
  std::printf("006891f0 model test: %d failure(s)\n", failures);
  return 1;
}
