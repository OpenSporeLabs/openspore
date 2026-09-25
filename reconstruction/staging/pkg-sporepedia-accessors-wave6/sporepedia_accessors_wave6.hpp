#pragma once

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-16 accessor reconstruction requires an x86-32 target"
#endif

struct Pkg16AssetData;
struct Pkg16AssetMetadata;
struct Pkg16WideString;

extern "C" __thiscall __attribute__((naked)) std::uint8_t
sporepedia_func7ch_00641460(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) std::uint32_t
sporepedia_func3ch_006417b0(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) Pkg16WideString*
sporepedia_get_author_name_00641810(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) std::uint64_t
sporepedia_get_author_id_00641820(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) Pkg16WideString*
sporepedia_get_tags_00641850(Pkg16AssetData* self);

extern "C" __thiscall __attribute__((naked)) void
sporepedia_get_time_created_00641860(Pkg16AssetData* self,
                                     Pkg16WideString* destination);
