#include <cassert>
#include <cstring>
#include <type_traits>

#include "argscript_get_current_scope.hpp"

namespace openspore::reconstruction::pkg_argscript_wave9 {
namespace {

int test_return_and_immutability() {
  OpaqueFormatParser parser{};
  char scope[] = "scope";
  parser.field_130.begin = scope;
  parser.field_130.end = scope + 5;
  parser.field_130.capacity = scope + 5;
  parser.field_140[0] = 0xa5;
  parser.field_154.begin = scope;
  parser.field_164 = 1;
  parser.field_168 = 0x12345678U;
  const OpaqueFormatParser before = parser;

  char* result = pkg_argscript_get_current_scope_00d1dcd0(&parser);

  if (result != scope) {
    return 1;
  }
  if (std::memcmp(&parser, &before, sizeof(parser)) != 0) {
    return 1;
  }
  return 0;
}

int test_empty_scope() {
  OpaqueFormatParser parser{};
  parser.field_130.end = parser.field_130.begin;
  parser.field_130.capacity = parser.field_130.begin;

  char* result = pkg_argscript_get_current_scope_00d1dcd0(&parser);

  if (result != nullptr) {
    return 1;
  }
  return 0;
}

void test_return_width() {
  using Return = decltype(pkg_argscript_get_current_scope_00d1dcd0(
      static_cast<OpaqueFormatParser*>(nullptr)));
  static_assert(std::is_same<Return, char*>::value, "pointer return type");
  static_assert(sizeof(Return) == sizeof(char*), "pointer return width");
}

}

int run() {
  if (test_return_and_immutability() != 0) {
    return 1;
  }
  if (test_empty_scope() != 0) {
    return 1;
  }
  test_return_width();
  return 0;
}

}

int main() { return openspore::reconstruction::pkg_argscript_wave9::run(); }
