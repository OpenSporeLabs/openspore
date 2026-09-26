#include "argscript_get_current_scope.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave9 {

char* PKG_ARGSCRIPT_WAVE9_THIS_CALL
pkg_argscript_get_current_scope_00d1dcd0(OpaqueFormatParser* parser) {
  return parser->field_130.begin;
}

}
