#include "sporepedia_access.hpp"

extern "C" const float pkg16_g_get_asset_id_float_013eb1bc = -1.0F;

extern "C" __thiscall __attribute__((naked)) std::uint8_t
sporepedia_is_editable_00641400(Pkg16AssetData*) {
  __asm__(
      "movl (%ecx), %eax\n\t"
      "movl 0x60(%eax), %edx\n\t"
      "jmp *%edx\n\t");
}

extern "C" __thiscall __attribute__((naked)) Pkg16MetadataWord
sporepedia_has_name_00641770(Pkg16AssetData*) {
  __asm__(
      "movl 0x28(%ecx), %eax\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) long double
sporepedia_get_asset_id_006417c0(Pkg16AssetData*, std::uint64_t*) {
  __asm__(
      "flds pkg16_g_get_asset_id_float_013eb1bc\n\t"
      "ret\n\t");
}
