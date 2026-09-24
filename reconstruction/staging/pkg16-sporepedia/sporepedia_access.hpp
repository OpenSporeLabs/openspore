#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-16 staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg16_sporepedia {

struct AssetData;

using EditableSlot = bool(__thiscall *)(AssetData *);

extern "C" const float g_get_asset_id_float_013eb1bc;

extern "C" __thiscall __attribute__((naked)) bool
sporepedia_is_editable_00641400(AssetData *self);

extern "C" __thiscall __attribute__((naked)) bool
sporepedia_has_name_00641770(AssetData *self);

extern "C" __thiscall __attribute__((naked)) float
sporepedia_get_asset_id_006417c0(AssetData *self, std::uint64_t *destination);

}
