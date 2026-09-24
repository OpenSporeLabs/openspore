#include "sporepedia_access.hpp"

namespace openspore::reconstruction::pkg16_sporepedia {

extern "C" const float g_get_asset_id_float_013eb1bc = -1.0F;

extern "C" __thiscall __attribute__((naked)) bool
sporepedia_is_editable_00641400(AssetData *) {
  __asm__("movl (%ecx), %eax\n\t"
          "movl 0x60(%eax), %edx\n\t"
          "jmp *%edx\n\t");
}

extern "C" __thiscall __attribute__((naked)) bool
sporepedia_has_name_00641770(AssetData *) {
  __asm__("movl 0x28(%ecx), %eax\n\t"
          "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) float
sporepedia_get_asset_id_006417c0(AssetData *, std::uint64_t *) {
  __asm__("fldl g_get_asset_id_float_013eb1bc\n\t"
          "ret\n\t");
}

}
