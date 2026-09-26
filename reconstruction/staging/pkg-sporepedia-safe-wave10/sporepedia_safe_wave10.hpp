#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-sporepedia-safe-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_SPOREPEDIA_SAFE_WAVE10_CDECL __cdecl
#define PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL __thiscall
#else
#define PKG_SPOREPEDIA_SAFE_WAVE10_CDECL __attribute__((cdecl))
#define PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_sporepedia_safe_wave10 {

using Word = std::uint32_t;
using SignedWord = std::int32_t;

struct OpaqueKey16 {
  Word words[4];
};

struct OpaqueWordVector {
  Word *first;
  Word *last;
  Word *capacity;
};

struct OpaqueInlineWordVector {
  Word *first;
  Word *last;
  Word *capacity;
  Word filler_0c;
  Word inline_marker_10;
};

struct OpaqueGlobalRecord {
  Word words[3];
};

struct OpaqueGlobalRecordRange {
  Word first;
  Word last;
};

struct OpaqueLookupEntry {
  Word key_00;
  Word value_04;
};

struct OpaqueLookup;
struct OpaqueAssetRef;
struct OpaqueLookupSource;
struct OpaqueSporepediaAsset;

using RetainSlot =
    void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueAssetRef *);
using ReleaseSlot =
    void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueAssetRef *);

struct OpaqueAssetRefVtable {
  RetainSlot retain_00;
  ReleaseSlot release_04;
};

struct OpaqueAssetRef {
  OpaqueAssetRefVtable *vtable;
};

using SourceLookupSlot = OpaqueAssetRef *(
    PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueLookupSource *, Word);

struct OpaqueLookupSourceVtable {
  void *slots_00_08[3];
  SourceLookupSlot lookup_0c;
};

struct OpaqueLookupSource {
  OpaqueLookupSourceVtable *vtable;
};

struct OpaqueKeyedSet {
  OpaqueAssetRefVtable *vtable;
  Word body_04[5];
  Word word_18;
};

using ApplyPropertySlot = void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(
    OpaqueSporepediaAsset *, const OpaqueGlobalRecord *);

struct OpaqueAssetVtable {
  void *slots_00_ac[45];
  ApplyPropertySlot apply_property_b4;
};

struct OpaqueSporepediaAsset {
  OpaqueAssetVtable *vtable_00;
  Word body_04[3];
  void *vtable_10;
  void *vtable_14;
  Word body_18;
  OpaqueAssetRef *access_1c;
  OpaqueAssetRef *access_20;
  std::uint8_t flag_24;
  std::uint8_t flag_25;
  std::uint8_t flag_26;
  std::uint8_t body_27;
  Word source_word_28;
  Word state_2c;
  Word body_30[3];
  OpaqueAssetRef *access_3c;
  OpaqueInlineWordVector entries_40;
  Word body_54;
  Word inline_58[5];
  Word max_6c;
  OpaqueAssetRef *access_70;
  OpaqueAssetRef *access_74;
};

static_assert(sizeof(void *) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(SignedWord) == 4, "target signed words are four bytes");
static_assert(sizeof(OpaqueKey16) == 0x10, "tag key size");
static_assert(sizeof(OpaqueWordVector) == 0x0c, "word vector size");
static_assert(offsetof(OpaqueWordVector, last) == 0x04,
              "word vector end offset");
static_assert(offsetof(OpaqueWordVector, capacity) == 0x08,
              "word vector capacity offset");
static_assert(sizeof(OpaqueInlineWordVector) == 0x14, "inline vector size");
static_assert(offsetof(OpaqueInlineWordVector, filler_0c) == 0x0c,
              "inline vector filler offset");
static_assert(offsetof(OpaqueInlineWordVector, inline_marker_10) == 0x10,
              "inline vector compared word offset");
static_assert(sizeof(OpaqueGlobalRecord) == 0x0c, "global record stride");
static_assert(sizeof(OpaqueGlobalRecordRange) == 0x08,
              "global record range size");
static_assert(offsetof(OpaqueGlobalRecordRange, last) == 0x04,
              "global record range end offset");
static_assert(offsetof(OpaqueLookupEntry, value_04) == 0x04,
              "lookup entry value offset");
static_assert(sizeof(OpaqueAssetRefVtable) == 0x08, "reference vtable size");
static_assert(offsetof(OpaqueAssetRefVtable, retain_00) == 0x00,
              "reference retain slot offset");
static_assert(offsetof(OpaqueAssetRefVtable, release_04) == 0x04,
              "reference release slot offset");
static_assert(sizeof(OpaqueAssetRef) == 0x04, "reference header size");
static_assert(offsetof(OpaqueLookupSourceVtable, lookup_0c) == 0x0c,
              "source lookup slot offset");
static_assert(sizeof(OpaqueLookupSource) == 0x04, "source header size");
static_assert(offsetof(OpaqueKeyedSet, word_18) == 0x18,
              "keyed set word offset");
static_assert(offsetof(OpaqueAssetVtable, apply_property_b4) == 0xb4,
              "asset apply property slot offset");
static_assert(sizeof(OpaqueAssetVtable) == 0xb8, "asset vtable size");
static_assert(offsetof(OpaqueSporepediaAsset, vtable_00) == 0x00,
              "asset primary vtable offset");
static_assert(offsetof(OpaqueSporepediaAsset, vtable_10) == 0x10,
              "asset secondary vtable offset");
static_assert(offsetof(OpaqueSporepediaAsset, vtable_14) == 0x14,
              "asset tertiary vtable offset");
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
static_assert(offsetof(OpaqueSporepediaAsset, source_word_28) == 0x28,
              "asset source word offset");
static_assert(offsetof(OpaqueSporepediaAsset, state_2c) == 0x2c,
              "asset state word offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_3c) == 0x3c,
              "asset third accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, entries_40) == 0x40,
              "asset inline entry vector offset");
static_assert(offsetof(OpaqueSporepediaAsset, inline_58) == 0x58,
              "asset inline storage offset");
static_assert(offsetof(OpaqueSporepediaAsset, max_6c) == 0x6c,
              "asset maximum word offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_70) == 0x70,
              "asset fourth accessor offset");
static_assert(offsetof(OpaqueSporepediaAsset, access_74) == 0x74,
              "asset fifth accessor offset");
static_assert(sizeof(OpaqueSporepediaAsset) == 0x78, "asset size");

using FreePort = void(PKG_SPOREPEDIA_SAFE_WAVE10_CDECL *)(Word);
using ClearPort = void(PKG_SPOREPEDIA_SAFE_WAVE10_CDECL *)(void *first,
                                                           const void *last,
                                                           std::size_t count);
using BaseDestroyPort =
    void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueSporepediaAsset *);
using KeyFillPort =
    OpaqueKey16 *(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueKeyedSet *,
                                                         OpaqueKey16 *, Word);
using MaskTestPort =
    std::uint8_t(PKG_SPOREPEDIA_SAFE_WAVE10_CDECL *)(OpaqueKey16, OpaqueKey16);
using KeyCollectPort = bool(PKG_SPOREPEDIA_SAFE_WAVE10_CDECL *)(
    OpaqueKeyedSet *, OpaqueWordVector *);
using InlineReservePort =
    void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueInlineWordVector *, Word);
using InlineInsertPort = void(PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(
    OpaqueInlineWordVector *, Word *, const Word *);

constexpr std::uintptr_t kGlobalRecordRangeOffset = 0x18u;

using GlobalRecordRangePort = const OpaqueGlobalRecordRange *(
    PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueAssetRef *);
using GateLookupPort = OpaqueLookup *(PKG_SPOREPEDIA_SAFE_WAVE10_CDECL *)();
using EntryLookupPort = const OpaqueLookupEntry *(
    PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL *)(OpaqueLookup *, Word);

struct OpaqueVtableWords {
  Word primary_00;
  Word secondary_10;
  Word tertiary_14;
};

struct SporepediaSafeBindings {
  OpaqueVtableWords vtable_words;
  const OpaqueKey16 *tag_015da8e0;
  const OpaqueKey16 *tag_015dab18;
  const OpaqueKey16 *tag_015da80c;
  FreePort free_00f47380;
  ClearPort clear_011e0744;
  BaseDestroyPort base_destroy_006412a0;
  KeyFillPort key_fill_004babe0;
  MaskTestPort mask_test_004f3d60;
  KeyCollectPort key_collect_004f5720;
  InlineReservePort inline_reserve_00642070;
  InlineInsertPort inline_insert_0060a600;
  GlobalRecordRangePort global_record_range_005507a0;
  GateLookupPort gate_lookup_0067dea0;
  EntryLookupPort entry_lookup_007db5e0;
};

SporepediaSafeBindings &sporepedia_safe_bindings();
void sporepedia_safe_publish_bindings(const SporepediaSafeBindings &bindings);
void sporepedia_safe_reset_bindings();

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
sporepedia_asset_destroy_00642190(OpaqueSporepediaAsset *asset);

void PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL sporepedia_asset_load_00642230(
    OpaqueSporepediaAsset *asset, OpaqueLookupSource *source);

}

#undef PKG_SPOREPEDIA_SAFE_WAVE10_CDECL
#undef PKG_SPOREPEDIA_SAFE_WAVE10_THISCALL
