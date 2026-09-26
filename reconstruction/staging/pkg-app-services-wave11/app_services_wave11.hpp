#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "app services wave11 reconstruction requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_W11_CDECL __cdecl
#define PKG_W11_THISCALL __thiscall
#define PKG_W11_NOINLINE __declspec(noinline)
#else
#define PKG_W11_CDECL __attribute__((cdecl))
#define PKG_W11_THISCALL __attribute__((thiscall))
#define PKG_W11_NOINLINE __attribute__((noinline))
#endif

namespace openspore::reconstruction::pkg_app_services_wave11 {

static_assert(sizeof(void *) == 4, "app services wave11 pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "app services wave11 words are 32-bit");
static_assert(sizeof(std::uint16_t) == 2,
              "app services wave11 halves are 16-bit");

#if defined(_MSC_VER)
#define PKG_W11_BARRIER() __asm {}
#else
#define PKG_W11_BARRIER() __asm__ __volatile__("" ::: "memory")
#endif

using OpaqueWord = std::uint32_t;
using OpaqueHalf = std::uint16_t;
using OpaqueByte = std::uint8_t;
using OpaqueNarrow = std::int8_t;
using OpaqueBool = bool;
using OpaqueSigned = std::int32_t;

struct OpaqueWide {
  OpaqueWord *begin = nullptr;
  OpaqueWord *end = nullptr;
};

struct OpaqueWideField {
  OpaqueWord *begin = nullptr;
  OpaqueWord *end = nullptr;
  OpaqueWord capacity = 0;
  OpaqueWord reserved = 0;
};

struct OpaqueKey12 {
  OpaqueWord w0 = 0;
  OpaqueWord w1 = 0;
  OpaqueWord w2 = 0;
};

struct OpaqueSlot32 {
  OpaqueWord w0 = 0;
  OpaqueWord w1 = 0;
};

struct OpaqueBlock32 {
  OpaqueWord words[8]{};
};

struct OpaqueEncoder70 {
  OpaqueWord words[28]{};
};

struct OpaqueService {
  void *vtable_000 = nullptr;
  OpaqueBlock32 block_004{};
  OpaqueBlock32 block_024{};
  OpaqueWord field_044 = 0;
  OpaqueBlock32 block_048{};
  OpaqueBlock32 block_068{};
  OpaqueEncoder70 encoder_088{};
  OpaqueKey12 image_0f8{};
  OpaqueWideField path_104{};
  OpaqueWideField path_114{};
  OpaqueWideField path_124{};
  OpaqueWideField path_134{};
  OpaqueWideField path_144{};
  OpaqueWideField path_154{};
  OpaqueWideField path_164{};
  OpaqueWideField path_174{};
  OpaqueWord field_184 = 0;
};

static_assert(offsetof(OpaqueService, block_004) == 0x04, "service block 004");
static_assert(offsetof(OpaqueService, block_024) == 0x24, "service block 024");
static_assert(offsetof(OpaqueService, field_044) == 0x44, "service field 044");
static_assert(offsetof(OpaqueService, block_048) == 0x48, "service block 048");
static_assert(offsetof(OpaqueService, block_068) == 0x68, "service block 068");
static_assert(offsetof(OpaqueService, encoder_088) == 0x88,
              "service encoder 088");
static_assert(offsetof(OpaqueService, image_0f8) == 0xf8, "service image 0f8");
static_assert(offsetof(OpaqueService, path_104) == 0x104, "service path 104");
static_assert(offsetof(OpaqueService, path_114) == 0x114, "service path 114");
static_assert(offsetof(OpaqueService, path_124) == 0x124, "service path 124");
static_assert(offsetof(OpaqueService, path_134) == 0x134, "service path 134");
static_assert(offsetof(OpaqueService, path_144) == 0x144, "service path 144");
static_assert(offsetof(OpaqueService, path_154) == 0x154, "service path 154");
static_assert(offsetof(OpaqueService, path_164) == 0x164, "service path 164");
static_assert(offsetof(OpaqueService, path_174) == 0x174, "service path 174");
static_assert(offsetof(OpaqueService, field_184) == 0x184, "service field 184");
static_assert(sizeof(OpaqueService) == 0x188, "service size");

struct OpaqueOwner60ee90 {
  void *vtable_000 = nullptr;
  OpaqueWord opaque_004 = 0;
  OpaqueWord *base_008 = nullptr;
  OpaqueWord *base_00c = nullptr;
  OpaqueWord *end_010 = nullptr;
  OpaqueWord *capacity_014 = nullptr;
  OpaqueWord opaque_018[16]{};
  OpaqueWord tag_058 = 0;
  OpaqueWord opaque_05c = 0;
  OpaqueWord slot_060 = 0;
  OpaqueWord slot_064 = 0;
  OpaqueWord opaque_068 = 0;
  OpaqueWord counter_06c = 0;
};

static_assert(offsetof(OpaqueOwner60ee90, base_008) == 0x08, "owner base 008");
static_assert(offsetof(OpaqueOwner60ee90, end_010) == 0x10, "owner end 010");
static_assert(offsetof(OpaqueOwner60ee90, capacity_014) == 0x14,
              "owner capacity 014");
static_assert(offsetof(OpaqueOwner60ee90, tag_058) == 0x58, "owner tag 058");
static_assert(offsetof(OpaqueOwner60ee90, slot_060) == 0x60, "owner slot 060");
static_assert(offsetof(OpaqueOwner60ee90, slot_064) == 0x64, "owner slot 064");
static_assert(offsetof(OpaqueOwner60ee90, counter_06c) == 0x6c,
              "owner counter 06c");

struct OpaqueGlobal;
struct OpaqueHandle;
struct OpaqueDatabase;
struct OpaqueFactory;
struct OpaqueOwner;
struct OpaqueSide;
struct OpaqueGate;

struct OpaqueGlobalVTable {
  void *slots_00[3]{};
  OpaqueBool(PKG_W11_THISCALL *slot_0c)(OpaqueGlobal *, void *, void *,
                                        OpaqueWord, OpaqueWord, OpaqueWord,
                                        OpaqueWord) = nullptr;
  void *slots_10[1]{};
  void(PKG_W11_THISCALL *slot_14)(OpaqueGlobal *, OpaqueWord,
                                  OpaqueWord) = nullptr;
  void *slots_18[2]{};
  OpaqueBool(PKG_W11_THISCALL *slot_20)(OpaqueGlobal *, OpaqueWord, OpaqueWord,
                                        OpaqueWord, OpaqueWord,
                                        OpaqueWord) = nullptr;
  void *slots_24[4]{};
  OpaqueBool(PKG_W11_THISCALL *slot_34)(OpaqueGlobal *, void *, void *,
                                        OpaqueWord, OpaqueWord, OpaqueWord,
                                        OpaqueWord) = nullptr;
  void *slots_38[4]{};
  OpaqueBool(PKG_W11_THISCALL *slot_48)(OpaqueGlobal *, void *,
                                        OpaqueWord) = nullptr;
  void *slots_4c[8]{};
  OpaqueWord(PKG_W11_THISCALL *slot_6c)(OpaqueGlobal *, OpaqueWord,
                                        OpaqueWord) = nullptr;
};

struct OpaqueHandleVTable {
  void *slots_00[1]{};
  void(PKG_W11_THISCALL *slot_04)(OpaqueHandle *) = nullptr;
  void(PKG_W11_THISCALL *slot_08)(OpaqueHandle *) = nullptr;
  OpaqueWord(PKG_W11_THISCALL *slot_0c)(OpaqueHandle *, OpaqueWord) = nullptr;
};

struct OpaqueDatabaseVTable {
  void *slots_00[13]{};
  OpaqueBool(PKG_W11_THISCALL *slot_34)(OpaqueDatabase *, void *, void *,
                                        OpaqueWord, OpaqueWord, OpaqueWord,
                                        OpaqueWord) = nullptr;
};

struct OpaqueFactoryVTable {
  void *slots_00[7]{};
  OpaqueBool(PKG_W11_THISCALL *slot_1c)(OpaqueFactory *, void *, void *,
                                        OpaqueWord, OpaqueWord) = nullptr;
  void *slots_20[10]{};
  OpaqueBool(PKG_W11_THISCALL *slot_48)(OpaqueFactory *, OpaqueWord) = nullptr;
  void *slots_4c[3]{};
  OpaqueBool(PKG_W11_THISCALL *slot_58)(OpaqueFactory *, void *) = nullptr;
};

struct OpaqueOwnerVTable {
  void(PKG_W11_THISCALL *slot_00)(OpaqueOwner *) = nullptr;
  void(PKG_W11_THISCALL *slot_04)(OpaqueOwner *) = nullptr;
  void(PKG_W11_THISCALL *slot_08)(OpaqueOwner *) = nullptr;
  void *slots_0c[3]{};
  OpaqueWord(PKG_W11_THISCALL *slot_18)(OpaqueOwner *, OpaqueWord) = nullptr;
  void *slots_1c[2]{};
  void(PKG_W11_THISCALL *slot_24)(OpaqueOwner *) = nullptr;
};

struct OpaqueSideVTable {
  void *slots_00[2]{};
  OpaqueBool(PKG_W11_THISCALL *slot_08)(OpaqueSide *, void *, void *,
                                        OpaqueWord) = nullptr;
};

struct OpaqueGateVTable {
  void *slots_00[7]{};
  OpaqueBool(PKG_W11_THISCALL *slot_1c)(OpaqueGate *, OpaqueWord, void *,
                                        OpaqueWord, void *) = nullptr;
  void *slots_20[5]{};
  OpaqueBool(PKG_W11_THISCALL *slot_34)(OpaqueGate *, void *, void *,
                                        OpaqueWord, OpaqueWord, OpaqueWord,
                                        OpaqueWord) = nullptr;
};

struct OpaqueGlobal {
  OpaqueGlobalVTable *vtable = nullptr;
};

struct OpaqueHandle {
  OpaqueHandleVTable *vtable = nullptr;
};

struct OpaqueDatabase {
  OpaqueDatabaseVTable *vtable = nullptr;
};

struct OpaqueFactory {
  OpaqueFactoryVTable *vtable = nullptr;
};

struct OpaqueOwner {
  OpaqueOwnerVTable *vtable = nullptr;
};

struct OpaqueSide {
  OpaqueSideVTable *vtable = nullptr;
};

struct OpaqueGate {
  OpaqueGateVTable *vtable = nullptr;
};

static_assert(offsetof(OpaqueGlobalVTable, slot_0c) == 0x0c, "global slot 0c");
static_assert(offsetof(OpaqueGlobalVTable, slot_20) == 0x20, "global slot 20");
static_assert(offsetof(OpaqueGlobalVTable, slot_34) == 0x34, "global slot 34");
static_assert(offsetof(OpaqueGlobalVTable, slot_48) == 0x48, "global slot 48");
static_assert(offsetof(OpaqueGlobalVTable, slot_6c) == 0x6c, "global slot 6c");
static_assert(offsetof(OpaqueHandleVTable, slot_04) == 0x04, "handle slot 04");
static_assert(offsetof(OpaqueHandleVTable, slot_08) == 0x08, "handle slot 08");
static_assert(offsetof(OpaqueHandleVTable, slot_0c) == 0x0c, "handle slot 0c");
static_assert(offsetof(OpaqueDatabaseVTable, slot_34) == 0x34, "database slot");
static_assert(offsetof(OpaqueFactoryVTable, slot_48) == 0x48,
              "factory slot 48");
static_assert(offsetof(OpaqueFactoryVTable, slot_58) == 0x58,
              "factory slot 58");
static_assert(offsetof(OpaqueFactoryVTable, slot_1c) == 0x1c,
              "factory slot 1c");
static_assert(offsetof(OpaqueOwnerVTable, slot_18) == 0x18, "owner slot 18");
static_assert(offsetof(OpaqueOwnerVTable, slot_24) == 0x24, "owner slot 24");
static_assert(offsetof(OpaqueSideVTable, slot_08) == 0x08, "side slot 08");

extern const OpaqueWord OPAQUE_WIDE_SLASH[];
extern const OpaqueWord OPAQUE_WIDE_THUMBNAILS[];
extern const OpaqueWord OPAQUE_WIDE_DEFAULT_FOLDER[];

static const OpaqueWord OPAQUE_KEY_CREATURES = 0x2b978c46u;
static const OpaqueWord OPAQUE_KEY_BUILDINGS = 0x2399be55u;
static const OpaqueWord OPAQUE_KEY_PLANTS = 0x438f6347u;
static const OpaqueWord OPAQUE_KEY_VEHICLES = 0x24682294u;
static const OpaqueWord OPAQUE_KEY_UFOS = 0x476a98c7u;
static const OpaqueWord OPAQUE_KEY_CELLS = 0x3d97a8e4u;
static const OpaqueWord OPAQUE_KEY_CITY_MUSIC = 0x04f684a4u;
static const OpaqueWord OPAQUE_KEY_SCENARIOS = 0x366a930du;
static const OpaqueWord OPAQUE_TABLE_DEFAULT = 0xffffffffu;
static const OpaqueWord OPAQUE_TABLE_SUBSTITUTE = 0x19f76d11u;
static const OpaqueWord OPAQUE_PREPARE_00688830_KEY = 0x0a0214bu;
static const OpaqueWord OPAQUE_TERMINATOR_0ff0f = 0x0ff0fu;
static const OpaqueWord OPAQUE_SEPARATOR_SLASH = 0x0000002fu;
static const OpaqueWord OPAQUE_TAG_30bdee3 = 0x030bdee3u;
static const OpaqueWord OPAQUE_TAG_2f7d0004 = 0x2f7d0004u;
static const OpaqueWord OPAQUE_MARSHAL_5132ed1 = 0x05132ed1u;
static const OpaqueWord OPAQUE_RESOURCE_11ac19d = 0x11ac19du;
static const OpaqueWord OPAQUE_CLASS_0058 = 0x000000d8u;
static const OpaqueWord OPAQUE_CLASS_0024 = 0x00000024u;
static const OpaqueWord OPAQUE_NAME_013fa0a8 = 0x013fa0a8u;
static const OpaqueWord OPAQUE_NAME_013f9f38 = 0x013f9f38u;
static const OpaqueWord OPAQUE_ONE_BYTE_01667bae = 0x01667baeu;
static const OpaqueWord OPAQUE_TWO_BYTE_01667bac = 0x01667bacu;
static const OpaqueWord OPAQUE_FORMAT_PNG = 0x00000015u;
static const OpaqueWord OPAQUE_KEY12_INVALID = 0xffffffffu;

struct Ports005f9230 {
  using Assign = void(PKG_W11_THISCALL *)(OpaqueWide *,
                                          const OpaqueWideField *);
  using Copy = void(PKG_W11_THISCALL *)(OpaqueWide *, void *, void *);

  Assign assign_0057cb60 = nullptr;
  Copy copy_00423650 = nullptr;
};

struct Ports005f9310 {
  using Resolve = void(PKG_W11_THISCALL *)(OpaqueWide *, OpaqueWord, OpaqueWord,
                                           const void *);
  using Prepare = void(PKG_W11_CDECL *)(OpaqueWord, OpaqueWide *, OpaqueWord);
  using Append = void(PKG_W11_THISCALL *)(OpaqueWide *, const void *,
                                          const void *);
  using Emit = const void *(PKG_W11_THISCALL *)(OpaqueWide *);
  using Truncate = void(PKG_W11_THISCALL *)(OpaqueWide *, OpaqueWord,
                                            OpaqueWord, const void *);
  using Finalize = OpaqueByte(PKG_W11_CDECL *)(const void *);
  using Destroy = void(PKG_W11_THISCALL *)(OpaqueWide *);

  Resolve resolve_006b5770 = nullptr;
  Prepare prepare_00688830 = nullptr;
  Append append_00429580 = nullptr;
  Emit emit_006b55c0 = nullptr;
  Truncate truncate_005f8f80 = nullptr;
  Finalize finalize_00932ae0 = nullptr;
  Destroy destroy_006b5240 = nullptr;
};

struct Ports005fa8d0 {
  using Prepare = OpaqueWord *(PKG_W11_THISCALL *)(OpaqueEncoder70 *,
                                                   OpaqueHalf, OpaqueHalf,
                                                   OpaqueByte, OpaqueWord);
  using Fill = OpaqueBool(PKG_W11_THISCALL *)(void *, void *, OpaqueWord,
                                              OpaqueWord);
  using Global = OpaqueWord *(PKG_W11_CDECL *)();
  using Resolve = OpaqueBool(PKG_W11_THISCALL *)(OpaqueService *, OpaqueWord,
                                                 OpaqueWord, OpaqueWord);
  using Write = OpaqueBool(PKG_W11_THISCALL *)(OpaqueService *, void *);
  using Compose = OpaqueWord *(PKG_W11_THISCALL *)(OpaqueWord, void *, void *,
                                                   OpaqueWord, OpaqueWord);
  using Slot = void(PKG_W11_THISCALL *)(void *, void *);
  using OpenQuery = OpaqueBool(PKG_W11_THISCALL *)(void *, OpaqueWord,
                                                   OpaqueWord, OpaqueWord,
                                                   OpaqueWord);
  using Emit = void(PKG_W11_THISCALL *)(OpaqueEncoder70 *, OpaqueWord);
  using EmitPair = void(PKG_W11_THISCALL *)(OpaqueEncoder70 *, void *,
                                            OpaqueWord);
  using Open = void(PKG_W11_THISCALL *)(void *);
  using Destroy = void(PKG_W11_THISCALL *)(void *, void *);
  using Release = void(PKG_W11_CDECL *)(void *);
  using Build = OpaqueWord *(PKG_W11_THISCALL *)(void *, void *);
  using Store = void(PKG_W11_THISCALL *)(void *, void *);
  using Insert = void(PKG_W11_THISCALL *)(OpaqueBlock32 *, void *, void *);
  using Select = OpaqueWord *(PKG_W11_THISCALL *)(void *, void *, void *);
  using Record = void(PKG_W11_THISCALL *)(OpaqueBlock32 *, void *, void *);
  using Flush = void(PKG_W11_THISCALL *)(OpaqueService *);
  using Clear = void(PKG_W11_THISCALL *)(void *);

  Prepare prepare_0068e8f0 = nullptr;
  Fill fill_011f0440 = nullptr;
  Global global_0067dcd0 = nullptr;
  Resolve resolve_005f9920 = nullptr;
  Write write_005f97c0 = nullptr;
  Compose compose_00414e10 = nullptr;
  Slot push_00931e10 = nullptr;
  Open open_009317b0 = nullptr;
  OpenQuery open_009318f0 = nullptr;
  Emit emit_0068e1a0 = nullptr;
  EmitPair emit_pair_0068e1a0 = nullptr;
  Open close_00931a70 = nullptr;
  Destroy destroy_0056e2d0 = nullptr;
  Release release_005f7970 = nullptr;
  Build build_005f9080 = nullptr;
  Build build_005f90c0 = nullptr;
  Store store_005f8320 = nullptr;
  Store store_005f8390 = nullptr;
  Insert insert_005fa0a0 = nullptr;
  Insert insert_005fa0d0 = nullptr;
  Clear clear_00933960 = nullptr;
  Clear clear_00931e70 = nullptr;
  Clear clear_005f8d80 = nullptr;
  Select select_005f7940 = nullptr;
  Record record_005f8ed0 = nullptr;
  Record record_005f8f00 = nullptr;
  Flush flush_005f8ad0 = nullptr;
};

struct Ports005fc330 {
  using Slot = void(PKG_W11_THISCALL *)(void *, void *);
  using Open = void(PKG_W11_THISCALL *)(void *);
  using Query = OpaqueBool(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord,
                                               OpaqueWord, OpaqueWord);
  using Get = OpaqueWord *(PKG_W11_CDECL *)();
  using Probe = OpaqueBool(PKG_W11_THISCALL *)(OpaqueService *, void *, void *,
                                               void *);
  using Reset = void(PKG_W11_THISCALL *)(OpaqueBlock32 *, void *, void *);
  using Resolve = OpaqueBool(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord,
                                                 void *);
  using Mark = void(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord,
                                        OpaqueWord);
  using Lift = void(PKG_W11_THISCALL *)(void *, OpaqueWord, void *, void *);
  using BuildC = OpaqueWord *(PKG_W11_CDECL *)(OpaqueWord);
  using Factory = OpaqueWord *(PKG_W11_CDECL *)(OpaqueWord, OpaqueWord,
                                                OpaqueWord, OpaqueWord,
                                                OpaqueWord, OpaqueWord);
  using Build = OpaqueWord *(PKG_W11_THISCALL *)(void *);
  using Meta = void(PKG_W11_THISCALL *)(void *, void *, void *, void *, void *,
                                        void *, void *, void *, void *,
                                        OpaqueWord, OpaqueWord, OpaqueWord,
                                        OpaqueWord, OpaqueWord);
  using Meta2 = void(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord);
  using Flag = void(PKG_W11_THISCALL *)(void *, OpaqueWord);
  using NodeBuild = OpaqueWord *(PKG_W11_THISCALL *)(void *, OpaqueWord,
                                                     OpaqueWord, void *,
                                                     OpaqueWord);
  using Release = void(PKG_W11_THISCALL *)(void *);
  using ReleaseC = void(PKG_W11_CDECL *)(void *);
  using Toggle = void(PKG_W11_CDECL *)(void *, OpaqueWord);
  using SelectKey = void(PKG_W11_THISCALL *)(OpaqueBlock32 *, OpaqueWord,
                                             void *, void *);
  using Emit = void(PKG_W11_THISCALL *)(OpaqueEncoder70 *, OpaqueWord);

  Slot push_00931e10 = nullptr;
  Open state_009317b0 = nullptr;
  Query query_009318f0 = nullptr;
  Get get_0067cb30 = nullptr;
  Probe probe_005fbb00 = nullptr;
  Reset reset_005f8050 = nullptr;
  void(PKG_W11_THISCALL *close_005f8e40)(void *) = nullptr;
  Open close_00931a70 = nullptr;
  Open close_00931e70 = nullptr;
  Open close_005f8d80 = nullptr;
  Open close_00933960 = nullptr;
  Get global_0067dcd0 = nullptr;
  Get global_0067dcc0 = nullptr;
  Resolve resolve_0054e460 = nullptr;
  Mark mark_0054ed50 = nullptr;
  Lift lift_0054e250 = nullptr;
  BuildC build_006b1f90 = nullptr;
  Get side_0067de60 = nullptr;
  Factory factory_00f473a0 = nullptr;
  Factory node_00926020 = nullptr;
  Build build_00550450 = nullptr;
  Meta meta_00551620 = nullptr;
  Meta2 seal_00551b60 = nullptr;
  Flag flag_00550990 = nullptr;
  Flag drop_00550b00 = nullptr;
  ReleaseC toggle_006ad010 = nullptr;
  Toggle toggle_006ac0a0 = nullptr;
  NodeBuild node_008e2380 = nullptr;
  SelectKey record_005f8170 = nullptr;
  SelectKey record_005f8240 = nullptr;
  Emit emit_0068e1a0 = nullptr;
};

struct Ports0060ee90 {
  using Get = OpaqueWord *(PKG_W11_CDECL *)();
  using Global0c = OpaqueBool(PKG_W11_THISCALL *)(void *, void *, void *,
                                                  OpaqueWord, OpaqueWord,
                                                  OpaqueWord, OpaqueWord);
  using Global20 = OpaqueBool(PKG_W11_THISCALL *)(void *, OpaqueWord,
                                                  OpaqueWord, OpaqueWord);
  using Global6c = OpaqueWord(PKG_W11_THISCALL *)(void *, OpaqueWord,
                                                  OpaqueWord);
  using Probe = OpaqueWord *(PKG_W11_THISCALL *)(void *);
  using Drop = void(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord);
  using Owner = OpaqueWord *(PKG_W11_CDECL *)(void *);
  using Compose = OpaqueWord *(PKG_W11_THISCALL *)(void *);
  using Factory = OpaqueWord *(PKG_W11_CDECL *)(OpaqueWord);
  using Build = OpaqueWord *(PKG_W11_THISCALL *)(void *, OpaqueWord, OpaqueWord,
                                                 OpaqueWord, OpaqueWord,
                                                 OpaqueWord);
  using Grow = void(PKG_W11_THISCALL *)(void *, void *);
  using Place = void(PKG_W11_THISCALL *)(OpaqueOwner60ee90 *, void *);

  Get global_0067dcd0 = nullptr;
  Global0c global_0c = nullptr;
  Global20 global_20 = nullptr;
  Global6c global_6c = nullptr;
  Probe probe_005507a0 = nullptr;
  Drop drop_00551af0 = nullptr;
  Owner owner_005f7930 = nullptr;
  Compose compose_005fb430 = nullptr;
  Factory factory_00615810 = nullptr;
  Build build_00615d30 = nullptr;
  Grow grow_0060db40 = nullptr;
  Place place_0060cf30 = nullptr;
};

extern Ports005f9230 *g_ports_005f9230;
extern Ports005f9310 *g_ports_005f9310;
extern Ports005fa8d0 *g_ports_005fa8d0;
extern Ports005fc330 *g_ports_005fc330;
extern Ports0060ee90 *g_ports_0060ee90;

extern "C" OpaqueBool PKG_W11_THISCALL service_005f9230(OpaqueService *self,
                                                        OpaqueWord key,
                                                        OpaqueWide *dst);

extern "C" OpaqueBool PKG_W11_THISCALL service_005f9310(OpaqueService *self,
                                                        OpaqueWord instance,
                                                        OpaqueWide *dst,
                                                        OpaqueWord table);

extern "C" OpaqueBool PKG_W11_THISCALL service_005fa8d0(OpaqueService *self,
                                                        void *arg1, void *arg2,
                                                        void *arg3,
                                                        OpaqueWord arg4,
                                                        OpaqueWord arg5);

extern "C" OpaqueBool PKG_W11_THISCALL service_005fc330(OpaqueService *self,
                                                        const OpaqueWord *arg1,
                                                        OpaqueKey12 *arg2);

extern "C" void PKG_W11_THISCALL service_0060ee90(OpaqueOwner60ee90 *self,
                                                  void *arg1, void *arg2,
                                                  void *arg3);

}

#undef PKG_W11_BARRIER
#undef PKG_W11_CDECL
#undef PKG_W11_THISCALL
#undef PKG_W11_NOINLINE
