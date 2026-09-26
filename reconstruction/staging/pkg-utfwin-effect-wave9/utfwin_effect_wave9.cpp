#include "utfwin_effect_wave9.hpp"

namespace openspore::reconstruction::pkg_utfwin_effect_wave9 {

namespace unresolved_contracts {

extern "C" Opaque PKG_W9_THISCALL wave9_fallback_00951240(Opaque, Opaque);
extern "C" Opaque PKG_W9_THISCALL wave9_fallback_00950eb0(Opaque, Opaque);
extern "C" Opaque PKG_W9_THISCALL wave9_dispatch_00980330(Opaque, Opaque);

}

extern "C" PKG_W9_NAKED PKG_W9_THISCALL Opaque utfwin_wave9_00980480(Opaque,
                                                                     Opaque) {
  __asm__(
      "subl $4, %ecx\n\t"
      "jmp wave9_dispatch_00980330");
}

extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_009804e0(Opaque object,
                                                        Opaque token) {
  if (token != 0xef2b293bu) {
    return unresolved_contracts::wave9_fallback_00950eb0(object, token);
  }
  if (object != 0u) {
    return object + 0x0cu;
  }
  return 0u;
}

extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_00980510(Opaque) {
  return 0x202u;
}

extern "C" PKG_W9_NAKED PKG_W9_THISCALL Opaque utfwin_wave9_00980c50(Opaque,
                                                                     Opaque,
                                                                     Opaque,
                                                                     Opaque) {
  __asm__(
      "movl $0xcf2b2ad5, %eax\n\t"
      "ret\n\t");
}

extern "C" Opaque PKG_W9_THISCALL utfwin_wave9_009817c0(Opaque object,
                                                        Opaque token) {
  if (token == 0xeec58382u) {
    return object != 0u ? object + 0x04u : 0u;
  }
  if (token == 0xeef3af8cu) {
    return object != 0u ? object + 0x0cu : 0u;
  }
  return unresolved_contracts::wave9_fallback_00951240(object, token);
}

}
