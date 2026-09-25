#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-16 staging requires an x86-32 target"
#endif

struct Pkg16AssetData;

using Pkg16MetadataWord = std::uint32_t;
using Pkg16EditableSlot = std::uint8_t(__thiscall*)(Pkg16AssetData*);

extern "C" const float pkg16_g_get_asset_id_float_013eb1bc;

extern "C" __thiscall __attribute__((naked)) std::uint8_t
sporepedia_is_editable_00641400(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) Pkg16MetadataWord
sporepedia_has_name_00641770(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) long double
sporepedia_get_asset_id_006417c0(Pkg16AssetData* self,
                                 std::uint64_t* destination);
