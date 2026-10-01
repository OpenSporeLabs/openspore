#include "argscript_get_current_scope.hpp"

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_WAVE9_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_wave9 {

// 00d1dcd0  MOV EAX,dword ptr [ECX + 0x130]
// 00d1dcd6  RET
//
// The canonical ABI record types the result `char *`, so that is what this
// declares; the machine fixes the width -- one dword in EAX across a plain
// `RET` -- and not the element type.
//
// The read is written as the displacement the listing prints, because the
// receiver record behind it is `bounds_only` and names no member.  Note what
// the body does NOT do: the word it loads is the value that comes back.  There
// is no second dereference, no length load, no vtable hop and no store, so a
// reconstruction that followed the loaded word, or that read a neighbouring
// member, or that wrote anything, would be describing a body that is not this
// one.
char* PKG_ARGSCRIPT_WAVE9_THIS_CALL
pkg_argscript_get_current_scope_00d1dcd0(ParserExtent* parser) {
  const std::uint8_t* const reach =
      reinterpret_cast<const std::uint8_t*>(parser);
  return reinterpret_cast<char*>(
      *reinterpret_cast<const std::uint32_t*>(reach + 0x130));
}

}

#undef PKG_ARGSCRIPT_WAVE9_THIS_CALL
