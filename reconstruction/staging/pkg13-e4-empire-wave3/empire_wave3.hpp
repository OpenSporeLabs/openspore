#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13-E4 empire wave 3 staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG13_E4_THISCALL __thiscall
#define PKG13_E4_CDECL __cdecl
#else
#define PKG13_E4_THISCALL __attribute__((thiscall))
#define PKG13_E4_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg13_e4_empire_wave3 {

using OpaqueWord = std::uint32_t;

struct OpaqueRegistry;
struct OpaqueRecord;
struct OpaqueResourceRecord;
struct OpaqueProfile;
struct OpaqueVectorSource;
struct OpaqueVectorItem;
struct OpaqueOwnershipChild;
struct OpaqueMessageService;
struct OpaqueMessageRoot;
struct OpaqueMessageState;
struct OpaquePersistenceTarget;

struct OpaqueFloatColor {
  float value[3];
};

struct OpaqueProfile {
  std::uint8_t prefix[0x4ec];
  OpaqueFloatColor color_4ec;
};

struct OpaqueResourceRecord {
  std::uint8_t prefix[0x4c];
  OpaqueWord field_4c;
  std::uint8_t suffix[0x30];
  OpaqueProfile* field_80;
};

struct OpaqueVectorItemVtable;

struct OpaqueVectorItem {
  OpaqueVectorItemVtable* vtable;
};

struct OpaqueVectorItemVtable {
  void(PKG13_E4_THISCALL* slot_00)(OpaqueVectorItem*);
  void(PKG13_E4_THISCALL* slot_04)(OpaqueVectorItem*);
};

struct OpaqueVectorQuery {
  OpaqueVectorItem** begin;
  OpaqueVectorItem** end;
  OpaqueVectorItem** capacity;
  OpaqueWord field_0c;
  OpaqueWord field_10;
  OpaqueWord field_14;
  OpaqueWord field_18;
  float field_1c;
  float field_20;
  OpaqueWord field_24;
  float field_28;
  OpaqueWord field_2c;
};

struct OpaqueOwnershipChild {
  std::uint8_t prefix[0x3c];
  OpaqueRecord** begin;
  OpaqueRecord** end;
};

struct OpaqueRecord {
  std::uint8_t prefix[0x10];
  OpaqueWord field_10;
  std::uint8_t prefix_14[0x14];
  OpaqueWord field_28;
  std::uint8_t prefix_2c[0x04];
  OpaqueFloatColor color_30;
  std::uint8_t prefix_3c[0x14];
  OpaqueWord field_50;
  std::uint8_t prefix_54[0x30];
  OpaqueWord field_84;
  OpaqueRecord** field_88;
  std::uint8_t prefix_8c[0x0c];
  OpaqueRecord** field_98;
  OpaqueRecord** field_9c;
  std::uint8_t prefix_a0[0x10];
  OpaqueWord field_b0;
  std::uint8_t prefix_b4[0xa8];
  OpaqueOwnershipChild** field_15c;
  OpaqueOwnershipChild** field_160;
  std::uint8_t prefix_164[0x20];
  OpaqueWord field_184;
  std::uint8_t prefix_188[0x0c];
  OpaqueWord field_194;
};

struct OpaqueRecordRange {
  OpaqueRecord** begin;
  OpaqueRecord** end;
};

struct OpaqueMessageVtable {
  std::uint8_t prefix[0x20];
  OpaqueWord(PKG13_E4_THISCALL* slot_20)(OpaqueMessageService*);
  std::uint8_t gap_24[0x14];
  void(PKG13_E4_THISCALL* slot_38)(OpaqueMessageService*, OpaqueWord);
  std::uint8_t gap_3c[0x04];
  void(PKG13_E4_THISCALL* slot_40)(OpaqueMessageService*, OpaqueWord,
                                   OpaqueWord);
  std::uint8_t gap_44[0x14];
  void(PKG13_E4_THISCALL* slot_58)(OpaqueMessageService*);
};

struct OpaqueMessageService {
  OpaqueMessageVtable* vtable;
};

static_assert(sizeof(void*) == 4, "PKG-13-E4 target pointers are 32-bit");
static_assert(offsetof(OpaqueProfile, color_4ec) == 0x4ec,
              "profile color offset");
static_assert(offsetof(OpaqueResourceRecord, field_4c) == 0x4c,
              "resource field offset");
static_assert(offsetof(OpaqueResourceRecord, field_80) == 0x80,
              "resource profile offset");
static_assert(sizeof(OpaqueVectorQuery) == 0x30, "vector query size");
static_assert(offsetof(OpaqueVectorQuery, field_14) == 0x14,
              "vector query mask offset");
static_assert(offsetof(OpaqueVectorQuery, field_1c) == 0x1c,
              "vector query radius offset");
static_assert(offsetof(OpaqueVectorQuery, field_28) == 0x28,
              "vector query coordinate offset");
static_assert(offsetof(OpaqueRecord, field_10) == 0x10, "record field 0x10");
static_assert(offsetof(OpaqueRecord, color_30) == 0x30, "record color offset");
static_assert(offsetof(OpaqueRecord, field_50) == 0x50, "record field 0x50");
static_assert(offsetof(OpaqueRecord, field_84) == 0x84, "record field 0x84");
static_assert(offsetof(OpaqueRecord, field_b0) == 0xb0, "record field 0xb0");
static_assert(offsetof(OpaqueRecord, field_15c) == 0x15c,
              "record child range begin");
static_assert(offsetof(OpaqueRecord, field_160) == 0x160,
              "record child range end");
static_assert(offsetof(OpaqueRecord, field_194) == 0x194, "record field 0x194");
static_assert(offsetof(OpaqueOwnershipChild, begin) == 0x3c,
              "child range begin offset");
static_assert(offsetof(OpaqueOwnershipChild, end) == 0x40,
              "child range end offset");
static_assert(sizeof(OpaqueMessageVtable) == 0x5c, "message vtable size");
static_assert(offsetof(OpaqueMessageVtable, slot_20) == 0x20,
              "message vtable offset 0x20");
static_assert(offsetof(OpaqueMessageVtable, slot_38) == 0x38,
              "message vtable offset 0x38");
static_assert(offsetof(OpaqueMessageVtable, slot_40) == 0x40,
              "message vtable offset 0x40");
static_assert(offsetof(OpaqueMessageVtable, slot_58) == 0x58,
              "message vtable offset 0x58");

using CurrentEmpirePort = OpaqueRecord*(PKG13_E4_CDECL*)();
using RegistryPort = OpaqueRegistry*(PKG13_E4_CDECL*)();
using RegistryRecordPort =
    OpaqueResourceRecord*(PKG13_E4_THISCALL*)(OpaqueRegistry*, OpaqueWord);
using ResourceTypePort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueResourceRecord*);
using ResourceProfilePort =
    OpaqueProfile*(PKG13_E4_THISCALL*)(OpaqueResourceRecord*);
using CurrentProfilePort = OpaqueProfile*(PKG13_E4_THISCALL*)(OpaqueRecord*);
using RegistryIdentityPort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueRegistry*);
using PalettePort = const OpaqueFloatColor*(PKG13_E4_CDECL*)(OpaqueWord);
using PaletteActivePort = std::uint8_t(PKG13_E4_CDECL*)(OpaqueWord);
using ColorEqualPort = bool(PKG13_E4_CDECL*)(const OpaqueFloatColor*,
                                             const OpaqueFloatColor*);
using ColorTransformPort = void(PKG13_E4_CDECL*)(const OpaqueFloatColor*,
                                                 OpaqueFloatColor*, float,
                                                 float);
using PaletteWritePort = void(PKG13_E4_CDECL*)(float, float, float);
using PaletteRebuildPort = void(PKG13_E4_CDECL*)();
using VectorSourcePort =
    const OpaqueFloatColor*(PKG13_E4_THISCALL*)(OpaqueResourceRecord*);
using VectorCollectPort = void(PKG13_E4_THISCALL*)(OpaqueRegistry*,
                                                   const OpaqueFloatColor*,
                                                   OpaqueVectorQuery*,
                                                   OpaqueVectorItem***);
using VectorItemWordPort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueVectorItem*);
using RegistryCandidatePort = OpaqueRecord*(PKG13_E4_THISCALL*)(OpaqueRegistry*,
                                                                OpaqueWord);
using VectorStorageCleanupPort = void(PKG13_E4_CDECL*)(OpaqueVectorItem**);

struct EmpireColorPorts {
  CurrentEmpirePort current_empire;
  RegistryPort registry;
  RegistryRecordPort registry_record;
  ResourceTypePort resource_type;
  ResourceProfilePort resource_profile;
  CurrentProfilePort current_profile;
  RegistryIdentityPort registry_identity;
  PalettePort palette;
  PaletteActivePort palette_active;
  ColorEqualPort color_equal;
  ColorTransformPort color_transform;
  PaletteWritePort palette_write;
  PaletteRebuildPort palette_rebuild;
  VectorSourcePort vector_source;
  VectorCollectPort vector_collect;
  VectorItemWordPort vector_item_word;
  RegistryCandidatePort registry_candidate;
  VectorStorageCleanupPort vector_storage_cleanup;
};

EmpireColorPorts& empire_color_ports();

extern "C" OpaqueFloatColor* PKG13_E4_THISCALL
EmpirePoliticalColor_00c32cd0(OpaqueRecord* record, OpaqueFloatColor* output);

using RootRangePort = OpaqueRecordRange*(PKG13_E4_THISCALL*)(OpaqueRecord*);
using RecordTypePort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueRecord*);
using RecordStatePort = std::uint8_t(PKG13_E4_THISCALL*)(OpaqueRecord*);
using StarMetricPort = float(PKG13_E4_THISCALL*)(OpaqueRecord*);
using StarIdentityPort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueRecord*);
using OwnershipApplyPort = void(PKG13_E4_CDECL*)(OpaqueRecord*, std::int32_t);
using CurrentIdentityPort = OpaqueWord(PKG13_E4_CDECL*)();
using CurrentStarPort = OpaqueRecord*(PKG13_E4_CDECL*)();
using CurrentModePort = OpaqueWord(PKG13_E4_CDECL*)();
using RecordReferencePort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueRecord*);
using CurrentStarCountPort = std::int32_t(PKG13_E4_CDECL*)(OpaqueRecord*);
using CleanupRootPort = OpaqueRecord*(PKG13_E4_CDECL*)();
using CleanupRecordWordPort = OpaqueWord(PKG13_E4_THISCALL*)(OpaqueRecord*);
using CleanupListPort = void(PKG13_E4_THISCALL*)(OpaqueWord);

struct StarOwnershipPorts {
  RootRangePort root_range;
  RecordTypePort record_type;
  RecordStatePort record_state;
  StarMetricPort star_metric;
  StarIdentityPort star_identity;
  OwnershipApplyPort ownership_apply;
  CurrentIdentityPort current_identity;
  CurrentStarPort current_star;
  CurrentModePort current_mode;
  RecordReferencePort record_reference;
  CurrentStarCountPort current_star_count;
  CleanupRootPort cleanup_root;
  CleanupRecordWordPort cleanup_record_word;
  CleanupListPort cleanup_list;
};

struct MessagePorts {
  OpaqueMessageService*(PKG13_E4_CDECL* service)();
  OpaqueMessageRoot*(PKG13_E4_CDECL* root)();
  OpaqueMessageState*(PKG13_E4_THISCALL* state)(OpaqueMessageRoot*);
  bool(PKG13_E4_THISCALL* contains)(OpaqueMessageState*, OpaqueWord);
  bool(PKG13_E4_THISCALL* insert)(OpaqueMessageState*, OpaqueWord);
};

struct PersistencePorts {
  OpaquePersistenceTarget*(PKG13_E4_CDECL* lookup)(OpaqueWord);
  void(PKG13_E4_THISCALL* append)(OpaquePersistenceTarget*, OpaqueWord);
};

struct PoliticalOwnershipPorts {
  StarOwnershipPorts ownership;
  MessagePorts messages;
  PersistencePorts persistence;
};

PoliticalOwnershipPorts& political_ownership_ports();

extern "C" void PKG13_E4_CDECL
PoliticalOwnershipScan_00c8d060(OpaqueRecord* record);

}
