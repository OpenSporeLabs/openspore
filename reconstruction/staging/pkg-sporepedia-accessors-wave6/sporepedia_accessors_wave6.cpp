#include "sporepedia_accessors_wave6.hpp"

extern "C" __thiscall Pkg16WideString* pkg16_author_name_00414e10(
    Pkg16AssetMetadata* metadata);

extern "C" __thiscall std::uint32_t pkg16_author_id_00550880(
    Pkg16AssetMetadata* metadata);

extern "C" __thiscall Pkg16WideString* pkg16_tags_005508c0(
    Pkg16AssetMetadata* metadata);

extern "C" __thiscall void pkg16_time_helper_00550cf0(
    Pkg16AssetMetadata* metadata, Pkg16WideString* destination);

extern "C" __thiscall __attribute__((naked)) std::uint8_t
sporepedia_func7ch_00641460(Pkg16AssetData*) {
  __asm__(
      "movb 0x25(%ecx), %al\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) std::uint32_t
sporepedia_func3ch_006417b0(Pkg16AssetData*) {
  __asm__(
      "movl $0x80000001, %eax\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) Pkg16WideString*
sporepedia_get_author_name_00641810(Pkg16AssetData*) {
  __asm__(
      "movl 0x1c(%ecx), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 1f\n\t"
      "jmp pkg16_author_name_00414e10\n\t"
      "1:\n\t"
      "xorl %eax, %eax\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) std::uint64_t
sporepedia_get_author_id_00641820(Pkg16AssetData*) {
  __asm__(
      "movl 0x1c(%ecx), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 1f\n\t"
      "jmp pkg16_author_id_00550880\n\t"
      "1:\n\t"
      "xorl %eax, %eax\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) Pkg16WideString*
sporepedia_get_tags_00641850(Pkg16AssetData*) {
  __asm__(
      "movl 0x1c(%ecx), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 1f\n\t"
      "jmp pkg16_tags_005508c0\n\t"
      "1:\n\t"
      "xorl %eax, %eax\n\t"
      "ret\n\t");
}

extern "C" __thiscall __attribute__((naked)) void
sporepedia_get_time_created_00641860(Pkg16AssetData*, Pkg16WideString*) {
  __asm__(
      "movl 0x1c(%ecx), %ecx\n\t"
      "testl %ecx, %ecx\n\t"
      "jz 1f\n\t"
      "jmp pkg16_time_helper_00550cf0\n\t"
      "1:\n\t"
      "ret $4\n\t");
}
