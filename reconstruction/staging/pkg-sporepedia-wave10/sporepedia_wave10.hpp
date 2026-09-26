#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_WAVE10_THISCALL __thiscall
#define PKG_SPOREPEDIA_WAVE10_CDECL __cdecl
#define PKG_SPOREPEDIA_WAVE10_NAKED __declspec(naked)
#else
#define PKG_SPOREPEDIA_WAVE10_THISCALL __attribute__((thiscall))
#define PKG_SPOREPEDIA_WAVE10_CDECL __attribute__((cdecl))
#define PKG_SPOREPEDIA_WAVE10_NAKED __attribute__((naked))
#endif

namespace openspore::reconstruction::pkg_sporepedia_wave10 {

using OpaqueWord = std::uint32_t;

struct alignas(4) OpaqueKey16 {
  std::array<OpaqueWord, 4> words;
};

struct alignas(4) OpaqueWordVector {
  OpaqueWord* first;
  OpaqueWord* last;
  OpaqueWord* end_of_storage;
};

struct alignas(4) OpaqueInlineWordVector {
  OpaqueWord* first;
  OpaqueWord* last;
  OpaqueWord* end_of_storage;
  OpaqueWord opaque_0c;
  OpaqueWord inline_first;
};

struct alignas(4) OpaqueGlobalRecord {
  std::array<OpaqueWord, 3> words;
};

struct alignas(4) OpaqueGlobalRecordRange {
  OpaqueWord first;
  OpaqueWord last;
};

struct alignas(4) OpaqueLookupEntry {
  OpaqueWord key_00;
  OpaqueWord value_04;
};

struct OpaqueLookup;

#if !defined(_MSC_VER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

using RefRetainSlot =
    void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(struct OpaqueAssetRef*);
using RefReleaseSlot =
    void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(struct OpaqueAssetRef*);
using SourceLookupSlot = struct OpaqueAssetRef*(
    PKG_SPOREPEDIA_WAVE10_THISCALL*)(struct OpaqueLookupSource*, OpaqueWord);
using ApplyPropertySlot = void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(
    struct OpaqueSporepediaAsset*, const OpaqueGlobalRecord*);

struct alignas(4) OpaqueAssetRefVtable {
  RefRetainSlot retain_00;
  RefReleaseSlot release_04;
};

struct alignas(4) OpaqueAssetRef {
  OpaqueAssetRefVtable* vtable;
};

struct alignas(4) OpaqueLookupSourceVtable {
  std::array<void*, 3> slots_00;
  SourceLookupSlot lookup_0c;
};

struct alignas(4) OpaqueLookupSource {
  OpaqueLookupSourceVtable* vtable;
};

struct alignas(4) OpaqueKeyedSet {
  OpaqueAssetRefVtable* vtable;
  std::array<OpaqueWord, 5> opaque_04;
  OpaqueWord word_18;
};

struct alignas(4) OpaqueAssetVtable {
  std::array<void*, 45> slots_00;
  ApplyPropertySlot apply_property_b4;
};

struct alignas(4) OpaqueSporepediaAsset {
  OpaqueAssetVtable* vtable;
  std::array<OpaqueWord, 3> opaque_04;
  OpaqueWord secondary_10;
  OpaqueWord secondary_14;
  OpaqueWord opaque_18;
  OpaqueAssetRef* access_1c;
  OpaqueAssetRef* access_20;
  std::uint8_t flag_24;
  std::uint8_t flag_25;
  std::uint8_t flag_26;
  std::uint8_t opaque_27;
  OpaqueWord word_28;
  OpaqueWord word_2c;
  std::array<OpaqueWord, 3> opaque_30;
  OpaqueAssetRef* access_3c;
  OpaqueInlineWordVector entries_40;
  OpaqueWord opaque_54;
  std::array<OpaqueWord, 5> inline_58;
  OpaqueWord max_6c;
  OpaqueAssetRef* access_70;
  OpaqueAssetRef* access_74;
};

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

static_assert(sizeof(void*) == 4, "pkg-sporepedia-wave10 pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4,
              "pkg-sporepedia-wave10 words are 32-bit");
static_assert(sizeof(OpaqueKey16) == 0x10, "opaque key size");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "word vector size");
static_assert(offsetof(OpaqueWordVector, end_of_storage) == 0x08,
              "word vector capacity offset");
static_assert(sizeof(OpaqueInlineWordVector) == 0x14, "inline vector size");
static_assert(offsetof(OpaqueInlineWordVector, opaque_0c) == 0x0c,
              "inline vector filler offset");
static_assert(offsetof(OpaqueInlineWordVector, inline_first) == 0x10,
              "inline vector sentinel offset");
static_assert(sizeof(OpaqueGlobalRecord) == 0x0c, "global record stride");
static_assert(sizeof(OpaqueGlobalRecordRange) == 0x08,
              "global record range size");
static_assert(offsetof(OpaqueLookupEntry, value_04) == 0x04,
              "lookup entry value offset");
static_assert(sizeof(OpaqueAssetRefVtable) == 0x08, "ref vtable size");
static_assert(sizeof(OpaqueAssetRef) == 0x04, "ref header size");
static_assert(offsetof(OpaqueLookupSourceVtable, lookup_0c) == 0x0c,
              "source lookup slot offset");
static_assert(sizeof(OpaqueLookupSource) == 0x04, "source header size");
static_assert(offsetof(OpaqueKeyedSet, word_18) == 0x18, "tag set word offset");
static_assert(offsetof(OpaqueAssetVtable, apply_property_b4) == 0xb4,
              "asset apply property slot offset");
static_assert(sizeof(OpaqueAssetVtable) == 0xb8, "asset vtable size");
static_assert(offsetof(OpaqueSporepediaAsset, vtable) == 0x00,
              "asset primary vtable offset");
static_assert(offsetof(OpaqueSporepediaAsset, secondary_10) == 0x10,
              "asset secondary vtable offset");
static_assert(offsetof(OpaqueSporepediaAsset, secondary_14) == 0x14,
              "asset secondary tail vtable offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_1c) == 0x1c,
              "asset first accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_20) == 0x20,
              "asset second accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, flag_24) == 0x24,
              "asset first flag offset");
static_assert(offsetof(OpaqueSporepediaAsset, flag_25) == 0x25,
              "asset second flag offset");
static_assert(offsetof(OpaqueSporepediaAsset, flag_26) == 0x26,
              "asset third flag offset");
static_assert(offsetof(OpaqueSporepediaAsset, word_28) == 0x28,
              "asset source word offset");
static_assert(offsetof(OpaqueSporepediaAsset, word_2c) == 0x2c,
              "asset selector offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_3c) == 0x3c,
              "asset third accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, entries_40) == 0x40,
              "asset entry vector offset");
static_assert(offsetof(OpaqueSporepediaAsset, opaque_54) == 0x54,
              "asset filler word offset");
static_assert(offsetof(OpaqueSporepediaAsset, inline_58) == 0x58,
              "asset inline storage offset");
static_assert(offsetof(OpaqueSporepediaAsset, max_6c) == 0x6c,
              "asset maximum offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_70) == 0x70,
              "asset fourth accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_74) == 0x74,
              "asset fifth accessor offset");
static_assert(sizeof(OpaqueSporepediaAsset) == 0x78, "asset size");

using FreePort = void(PKG_SPOREPEDIA_WAVE10_CDECL*)(OpaqueWord);
using BaseDestroyPort =
    void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(OpaqueSporepediaAsset*);
using KeyFillPort = OpaqueKey16*(
    PKG_SPOREPEDIA_WAVE10_THISCALL*)(OpaqueKeyedSet*, OpaqueKey16*, OpaqueWord);
using MaskTestPort = std::uint8_t(PKG_SPOREPEDIA_WAVE10_CDECL*)(OpaqueKey16,
                                                                OpaqueKey16);
using KeyCollectPort = bool(PKG_SPOREPEDIA_WAVE10_CDECL*)(OpaqueKeyedSet*,
                                                          OpaqueWordVector*);
using WordVectorReservePort =
    void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(OpaqueInlineWordVector*, OpaqueWord);
using WordVectorInsertPort = void(PKG_SPOREPEDIA_WAVE10_THISCALL*)(
    OpaqueInlineWordVector*, OpaqueWord*, const OpaqueWord*);
using GlobalRecordRangePort =
    const OpaqueGlobalRecordRange*(PKG_SPOREPEDIA_WAVE10_CDECL*)();
using GateLookupPort = OpaqueLookup*(PKG_SPOREPEDIA_WAVE10_CDECL*)();
using EntryLookupPort = const OpaqueLookupEntry*(
    PKG_SPOREPEDIA_WAVE10_THISCALL*)(OpaqueLookup*, OpaqueWord);

struct SporepediaRuntime {
  FreePort free_00f47380;
  BaseDestroyPort base_destroy_006412a0;
  KeyFillPort key_fill_004babe0;
  MaskTestPort mask_test_004f3d60;
  KeyCollectPort key_collect_004f5720;
  WordVectorReservePort word_vector_reserve_00642070;
  WordVectorInsertPort word_vector_insert_0060a600;
  GlobalRecordRangePort global_record_range_005507a0;
  GateLookupPort gate_lookup_0067dea0;
  EntryLookupPort entry_lookup_007db5e0;
};

SporepediaRuntime& sporepedia_runtime();

extern OpaqueKey16 g_key_015da8e0;
extern OpaqueKey16 g_key_015dab18;
extern OpaqueKey16 g_key_015da80c;

extern "C" void PKG_SPOREPEDIA_WAVE10_NAKED PKG_SPOREPEDIA_WAVE10_THISCALL
sporepedia_asset_destroy_00642190(OpaqueSporepediaAsset* asset);

extern "C" void PKG_SPOREPEDIA_WAVE10_THISCALL sporepedia_asset_load_00642230(
    OpaqueSporepediaAsset* asset, OpaqueLookupSource* source);

}

extern "C" void PKG_SPOREPEDIA_WAVE10_CDECL
sporepedia_free_00f47380(std::uint32_t address);

extern "C" void PKG_SPOREPEDIA_WAVE10_THISCALL sporepedia_base_destroy_006412a0(
    openspore::reconstruction::pkg_sporepedia_wave10::OpaqueSporepediaAsset*
        asset);

#undef PKG_SPOREPEDIA_WAVE10_NAKED
#undef PKG_SPOREPEDIA_WAVE10_CDECL
#undef PKG_SPOREPEDIA_WAVE10_THISCALL
