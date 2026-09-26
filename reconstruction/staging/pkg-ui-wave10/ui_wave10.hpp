#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "UI wave 10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_UI_WAVE10_THISCALL __thiscall
#define PKG_UI_WAVE10_CDECL __cdecl
#else
#define PKG_UI_WAVE10_THISCALL __attribute__((thiscall))
#define PKG_UI_WAVE10_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_ui_wave10 {

using Opaque = std::uint32_t;

struct OpaqueService;
struct OpaqueService24;
struct OpaqueBinding;
struct OpaqueSettings;
struct OpaqueImageArchive;

struct OpaqueServiceVTable {
  std::array<Opaque, 4> slots_00{};
  Opaque slot_10 = 0;
  Opaque slot_14 = 0;
  std::array<Opaque, 2> slots_18{};
  Opaque slot_20 = 0;
  std::array<Opaque, 2> slots_24{};
  Opaque slot_2c = 0;
  std::array<Opaque, 19> slots_30{};
  Opaque slot_7c = 0;
  std::array<Opaque, 10> slots_80{};
  Opaque slot_a8 = 0;
  std::array<Opaque, 22> slots_ac{};
  Opaque slot_104 = 0;
};

struct OpaqueService {
  OpaqueServiceVTable* vtable_00 = nullptr;
};

struct OpaqueService24VTable {
  std::array<Opaque, 3> slots_00{};
  Opaque slot_0c = 0;
};

struct OpaqueService24 {
  OpaqueService24VTable* vtable_00 = nullptr;
  Opaque field_04 = 0;
  Opaque field_08 = 0;
  Opaque field_0c = 0;
  Opaque field_10 = 0;
  Opaque* slot_14 = nullptr;
};

struct OpaqueRegistryVTable {
  std::array<Opaque, 3> slots_00{};
  Opaque slot_0c = 0;
};

struct OpaqueRegistry {
  OpaqueRegistryVTable* vtable_00 = nullptr;
};

struct OpaqueBindingVTable {
  std::array<Opaque, 2> slots_00{};
};

struct OpaqueBinding {
  OpaqueBindingVTable* vtable_00 = nullptr;
  Opaque* vtable_04 = nullptr;
  Opaque field_08 = 0;
};
struct OpaqueCarrierVTable {
  std::array<Opaque, 4> slots_00{};
  Opaque slot_10 = 0;
  Opaque slot_14 = 0;
};

struct OpaqueCarrier {
  OpaqueCarrierVTable* vtable_00 = nullptr;
};

struct OpaqueNamePanel {
  std::array<std::uint8_t, 4> opaque_00{};
  Opaque* subobject_04 = nullptr;
  std::array<std::uint8_t, 8> opaque_08{};
  std::uint8_t byte_10 = 0;
  std::uint8_t byte_11 = 0;
  std::array<std::uint8_t, 2> opaque_12{};
  OpaqueBinding* slot_14 = nullptr;
  OpaqueService24* slot_18 = nullptr;
  Opaque field_1c = 0;
  Opaque field_20 = 0;
  std::array<std::uint8_t, 0x10> opaque_24{};
  Opaque field_34 = 0;
  std::array<std::uint8_t, 4> opaque_38{};
};

struct OpaquePropertyTriple {
  Opaque word_00 = 0;
  Opaque word_04 = 0;
  Opaque word_08 = 0;
};

struct OpaqueSettingsPair {
  Opaque hash = 0;
  Opaque* buffer = nullptr;
};

struct OpaqueSettingsVector {
  OpaqueSettingsPair* begin_00 = nullptr;
  OpaqueSettingsPair* end_04 = nullptr;
  OpaqueSettingsPair* cap_08 = nullptr;
};

struct OpaqueSettings {
  std::array<std::uint8_t, 0x40> opaque_00{};
  OpaqueSettingsVector vector_40{};
  std::array<std::uint8_t, 0x10> opaque_4c{};
};

struct OpaqueSlotVTable {
  std::array<Opaque, 2> slots_00{};
};

struct OpaqueSlot {
  OpaqueSlotVTable* vtable_00 = nullptr;
};

struct OpaqueImageArchiveVTable {
  std::array<Opaque, 7> slots_00{};
};

struct OpaqueImageArchiveBaseVTable {
  std::array<Opaque, 4> slots_00{};
};

struct OpaqueImageArchiveRefcountVTable {
  std::array<Opaque, 3> slots_00{};
};

struct OpaqueImageArchive {
  Opaque* vtable_00 = nullptr;
  Opaque* vtable_04 = nullptr;
  Opaque refcount_08 = 0;
  std::array<std::uint8_t, 8> opaque_0c{};
  OpaqueService24 service_14{};
  OpaqueService24 service_2c{};
  std::uint8_t byte_44 = 0;
  std::uint8_t byte_45 = 0;
  std::array<std::uint8_t, 2> opaque_46{};
  Opaque field_48 = 0;
  std::array<std::uint8_t, 0x18> opaque_4c{};
  OpaqueSlot* slot_64 = nullptr;
  OpaqueSlot* slot_68 = nullptr;
};

using ServiceRegisterSlot = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService*,
                                                            OpaqueNamePanel*,
                                                            Opaque);
using ServiceResolveSlot = OpaqueSlot*(PKG_UI_WAVE10_THISCALL*)(OpaqueService*,
                                                                Opaque, Opaque,
                                                                OpaqueSlot**);
using ServiceEnableSlot = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService*,
                                                          Opaque, Opaque);
using ServiceBindSlot = void(PKG_UI_WAVE10_THISCALL*)(OpaqueService*, Opaque);
using ServiceSlot04 = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*);
using ServiceSlot08 = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*);
using SlotReleaseSlot = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueSlot*);
using SlotFetchSlot = OpaqueRegistry*(PKG_UI_WAVE10_THISCALL*)(OpaqueService*);
using SlotRegistrySlot =
    OpaqueCarrier*(PKG_UI_WAVE10_THISCALL*)(OpaqueRegistry*, Opaque);
using CarrierSourceSlot = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueCarrier*,
                                                          Opaque);
using CarrierSinkSlot = void(PKG_UI_WAVE10_THISCALL*)(OpaqueCarrier*, Opaque,
                                                      Opaque);
using BindingSlot00 = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueBinding*);
using BindingSlot04 = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueBinding*);

using SettingsArraySlot = bool(PKG_UI_WAVE10_CDECL*)(OpaqueSlot*, Opaque,
                                                     Opaque*, Opaque**);
using SettingsHashSlot = Opaque(PKG_UI_WAVE10_CDECL*)(const std::uint16_t*,
                                                      Opaque, int);
using SettingsEraseSlot = void(PKG_UI_WAVE10_THISCALL*)(OpaqueSettingsVector*,
                                                        OpaqueSettingsPair*,
                                                        OpaqueSettingsPair*);
using SettingsInsertSlot = void(PKG_UI_WAVE10_THISCALL*)(
    OpaqueSettingsVector*, OpaqueSettingsPair*, const OpaqueSettingsPair*);
using SettingsAllocateSlot = Opaque*(PKG_UI_WAVE10_CDECL*)(Opaque, Opaque*,
                                                           Opaque);

using ServiceInitSlot = void(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*);
using ServiceMemberDestroySlot =
    void(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*);
using NamePanelEntitySlot = void(PKG_UI_WAVE10_THISCALL*)(OpaqueNamePanel*,
                                                          Opaque);
using NamePanelSetPropertySlot = Opaque(PKG_UI_WAVE10_THISCALL*)(
    OpaqueService24*, const OpaquePropertyTriple*, Opaque, Opaque);
using NamePanelCommitPropertySlot =
    Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*, Opaque, Opaque, Opaque);
using NamePanelLookupSlot = Opaque(PKG_UI_WAVE10_THISCALL*)(OpaqueService24*,
                                                            Opaque, Opaque);
using OpaqueAllocateSlot = Opaque*(PKG_UI_WAVE10_CDECL*)(Opaque, Opaque, Opaque,
                                                         Opaque, Opaque,
                                                         Opaque);
using OpaqueDeallocateSlot = void(PKG_UI_WAVE10_CDECL*)(Opaque*);
using OpaqueServiceProviderSlot = OpaqueService*(PKG_UI_WAVE10_CDECL*)();

static_assert(sizeof(void*) == 4, "UI wave 10 pointers are 32-bit");
static_assert(sizeof(Opaque) == 4, "UI wave 10 opaque words are 32-bit");

static_assert(offsetof(OpaqueServiceVTable, slot_10) == 0x10,
              "service slot_10 offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_14) == 0x14,
              "service slot_14 offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_20) == 0x20,
              "service slot_20 offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_2c) == 0x2c,
              "service slot_2c offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_7c) == 0x7c,
              "service slot_7c offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_a8) == 0xa8,
              "service slot_a8 offset drift");
static_assert(offsetof(OpaqueServiceVTable, slot_104) == 0x104,
              "service slot_104 offset drift");

static_assert(offsetof(OpaqueCarrierVTable, slot_10) == 0x10,
              "carrier slot_10 offset drift");
static_assert(offsetof(OpaqueCarrierVTable, slot_14) == 0x14,
              "carrier slot_14 offset drift");

static_assert(offsetof(OpaqueNamePanel, subobject_04) == 0x04,
              "name panel subobject_04 offset drift");
static_assert(offsetof(OpaqueNamePanel, byte_10) == 0x10,
              "name panel byte_10 offset drift");
static_assert(offsetof(OpaqueNamePanel, byte_11) == 0x11,
              "name panel byte_11 offset drift");
static_assert(offsetof(OpaqueNamePanel, slot_14) == 0x14,
              "name panel slot_14 offset drift");
static_assert(offsetof(OpaqueNamePanel, slot_18) == 0x18,
              "name panel slot_18 offset drift");
static_assert(offsetof(OpaqueNamePanel, field_20) == 0x20,
              "name panel field_20 offset drift");
static_assert(offsetof(OpaqueNamePanel, field_34) == 0x34,
              "name panel field_34 offset drift");

static_assert(sizeof(OpaquePropertyTriple) == 0x0c, "triple size drift");
static_assert(sizeof(OpaqueSettingsPair) == 0x08, "settings pair size drift");
static_assert(offsetof(OpaqueSettings, vector_40) == 0x40,
              "settings vector_40 offset drift");

static_assert(offsetof(OpaqueImageArchive, vtable_04) == 0x04,
              "image archive vtable_04 offset drift");
static_assert(offsetof(OpaqueImageArchive, refcount_08) == 0x08,
              "image archive refcount_08 offset drift");
static_assert(offsetof(OpaqueImageArchive, service_14) == 0x14,
              "image archive service_14 offset drift");
static_assert(offsetof(OpaqueImageArchive, service_2c) == 0x2c,
              "image archive service_2c offset drift");
static_assert(offsetof(OpaqueImageArchive, byte_44) == 0x44,
              "image archive byte_44 offset drift");
static_assert(offsetof(OpaqueImageArchive, byte_45) == 0x45,
              "image archive byte_45 offset drift");
static_assert(offsetof(OpaqueImageArchive, field_48) == 0x48,
              "image archive field_48 offset drift");
static_assert(offsetof(OpaqueImageArchive, slot_64) == 0x64,
              "image archive slot_64 offset drift");
static_assert(offsetof(OpaqueImageArchive, slot_68) == 0x68,
              "image archive slot_68 offset drift");

extern Opaque pkg_ui_wave10_alloc_tag_013eb430;
extern Opaque pkg_ui_wave10_vtable_013eb938;
extern Opaque pkg_ui_wave10_vtable_013ec458;
extern Opaque pkg_ui_wave10_vtable_013f7b54;
extern Opaque pkg_ui_wave10_vtable_013fe718;
extern Opaque pkg_ui_wave10_vtable_013fe728;
extern Opaque pkg_ui_wave10_vtable_0149bad8;

void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_005bfd40(OpaqueNamePanel* object,
                                                   Opaque arg_20, Opaque arg_24,
                                                   Opaque arg_28, Opaque arg_2c,
                                                   Opaque arg_30);
void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_00603650(OpaqueSettings* object);
OpaqueImageArchive* PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_00635700(OpaqueImageArchive* object, Opaque deleting);

}
