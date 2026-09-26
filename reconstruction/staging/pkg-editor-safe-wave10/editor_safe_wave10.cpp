#include "editor_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_SAFE_THISCALL __thiscall
#else
#define PKG_EDITOR_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_editor_safe_wave10 {

void PKG_EDITOR_SAFE_THISCALL
editor_row_publish_005a2010(OpaqueRowPublisher* self, Real row_x, Real row_y,
                            Real row_z, Word also_previous) {
  self->row_next_80 = row_x;
  self->row_next_84 = row_y;
  self->row_next_88 = row_z;
  if ((also_previous & 0xffu) != 0u) {
    self->row_prev_74 = row_x;
    self->row_prev_78 = row_y;
    self->row_prev_7c = row_z;
  }
}

}

#undef PKG_EDITOR_SAFE_THISCALL
