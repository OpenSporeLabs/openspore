#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PALETTE-WAVE11 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4,
              "PKG-PALETTE-WAVE11 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-PALETTE-WAVE11 target words are 32-bit");
static_assert(sizeof(std::uint16_t) == 2,
              "PKG-PALETTE-WAVE11 target text units are 16-bit");

#if defined(_MSC_VER)
#define PKG_PALETTE_W11_THISCALL __thiscall
#define PKG_PALETTE_W11_CDECL __cdecl
#else
#define PKG_PALETTE_W11_THISCALL __attribute__((thiscall))
#define PKG_PALETTE_W11_CDECL __attribute__((cdecl))
#endif

struct OpaqueTextBuffer {
  const std::uint16_t* begin;
  std::uint16_t* cursor;
  std::uint16_t* end;
};

struct OpaqueResourceKey {
  std::uint32_t word00;
  std::uint32_t word04;
  std::uint32_t word08;
};

struct OpaqueFloat2 {
  float field00;
  float field04;
};

struct OpaqueFloat4 {
  float field00;
  float field04;
  float field08;
  float field0c;
};

struct OpaquePropertyList {
  void* vtable;
};

struct OpaqueProperty {
  std::uint8_t opaque00[0x12];
  std::uint16_t field12;
  std::uint8_t opaque14[0x0c];
};

struct OpaqueGameModeManager {
  void* vtable;
};

struct OpaqueNode;

union OpaqueNodeSlot {
  float as_float;
  OpaqueNode* as_node;
};

union OpaqueFlagSlot {
  float as_float;
  OpaqueNode* as_node;
  struct {
    std::uint8_t byte48;
    std::uint8_t byte49;
    std::uint8_t byte4a;
    std::uint8_t byte4b;
  } bytes;
};

struct OpaqueNode {
  void* vtable;
  std::uint8_t opaque04[0x44];
  std::uint32_t field48;
  std::uint8_t opaque4c[0x08];
};

struct OpaqueModel {
  void* vtable;
  std::uint8_t opaque04[0x34];
};

struct OpaqueLinkInner {
  std::uint8_t opaque00[0x58];
  std::uint32_t field58;
};

struct OpaqueLink {
  std::uint8_t opaque00[0x14];
  std::int32_t field14;
  std::uint8_t opaque18[0x54];
  void* field6c;
  std::uint8_t opaque70[0x2c];
  void* field9c;
};

struct OpaquePageLead {
  void* vtable;
};

struct OpaquePageHost {
  std::uint8_t opaque00[0x08];
  void* field08;
  std::uint8_t opaque0c[0x08];
  OpaquePageLead* field14;
  OpaquePageLead* field18;
};

struct OpaqueCategoryList {
  std::uint8_t opaque00[0x0c];
  void* field0c;
  void* field10;
  std::uint8_t opaque14[0x20];
  void* field34;
  void* field38;
};

struct OpaqueRootList {
  std::uint8_t opaque00[0x0c];
  OpaqueCategoryList* field0c;
  OpaqueCategoryList* field10;
};

struct OpaquePageList {
  std::uint8_t opaque00[0x0c];
  void* field0c;
  void* field10;
};

struct OpaqueEntryList {
  std::uint8_t opaque00[0x70];
  void* field70;
  void* field74;
};

struct OpaqueWalkIndex {
  void* field00;
  std::uint8_t opaque04[0x08];
  OpaqueRootList* field0c;
  std::int32_t field10;
  std::int32_t field14;
  std::int32_t field18;
  std::int32_t field1c;
};

struct OpaqueAppProps {
  std::uint8_t opaque00[0x3c];
  void* field3c;
  std::uint8_t opaque40[0xd8];
  std::uint32_t field118;
};

struct OpaqueApp {
  void* vtable;
  std::uint8_t opaque04[0x38];
  OpaqueAppProps* field3c;
};

struct OpaquePageBuild {
  void* field00;
  std::uint8_t opaque04[0x08];
  std::uint32_t field0c;
  std::uint8_t opaque10[0x04];
  OpaqueNodeSlot field14;
  OpaqueNodeSlot field18;
  OpaqueNodeSlot field1c;
  OpaqueNodeSlot field20;
  float field24;
  float field28;
  std::uint8_t field2c;
  std::uint8_t field2d;
  std::uint8_t opaque2e[0x02];
  float field30;
  OpaqueNodeSlot field34;
  OpaqueNodeSlot field38;
  float field3c;
  float field40;
  float field44;
  OpaqueFlagSlot field48;
  OpaqueNodeSlot field4c;
  std::uint32_t field50;
  std::uint32_t field54;
  std::uint32_t field58;
  std::uint32_t field5c;
  std::uint32_t field60;
  OpaqueResourceKey field64;
  OpaqueNode** field70;
  OpaqueNode** field74;
  OpaqueNode** field78;
};

static_assert(sizeof(OpaqueTextBuffer) == 0x0c, "text buffer size");
static_assert(sizeof(OpaqueResourceKey) == 0x0c, "resource key size");
static_assert(sizeof(OpaqueFloat2) == 0x08, "float pair size");
static_assert(sizeof(OpaqueFloat4) == 0x10, "float quad size");
static_assert(offsetof(OpaqueProperty, field12) == 0x12, "property tag offset");
static_assert(sizeof(OpaqueProperty) == 0x20, "property size");
static_assert(sizeof(OpaqueNodeSlot) == 4, "node slot size");
static_assert(offsetof(OpaqueNode, field48) == 0x48, "node id offset");
static_assert(sizeof(OpaqueNode) == 0x54, "node size");
static_assert(offsetof(OpaqueLinkInner, field58) == 0x58, "link inner offset");
static_assert(offsetof(OpaqueLink, field14) == 0x14, "link cursor offset");
static_assert(offsetof(OpaqueLink, field6c) == 0x6c, "link inner slot offset");
static_assert(offsetof(OpaqueLink, field9c) == 0x9c, "link next offset");
static_assert(sizeof(OpaqueLink) == 0xa0, "link size");
static_assert(offsetof(OpaquePageHost, field08) == 0x08,
              "page host payload offset");
static_assert(offsetof(OpaquePageHost, field14) == 0x14,
              "page host hold offset");
static_assert(offsetof(OpaquePageHost, field18) == 0x18,
              "page host lead offset");
static_assert(sizeof(OpaquePageHost) == 0x1c, "page host size");
static_assert(offsetof(OpaqueRootList, field0c) == 0x0c,
              "root list slot offset");
static_assert(offsetof(OpaqueRootList, field10) == 0x10,
              "root list end offset");
static_assert(offsetof(OpaqueCategoryList, field0c) == 0x0c,
              "category inline offset");
static_assert(offsetof(OpaqueCategoryList, field10) == 0x10,
              "category inline end offset");
static_assert(offsetof(OpaqueCategoryList, field34) == 0x34,
              "category array begin offset");
static_assert(offsetof(OpaqueCategoryList, field38) == 0x38,
              "category array end offset");
static_assert(offsetof(OpaquePageList, field0c) == 0x0c,
              "page list slot offset");
static_assert(offsetof(OpaquePageList, field10) == 0x10,
              "page list end offset");
static_assert(offsetof(OpaqueEntryList, field70) == 0x70, "entry list begin");
static_assert(offsetof(OpaqueEntryList, field74) == 0x74, "entry list cursor");
static_assert(offsetof(OpaqueWalkIndex, field0c) == 0x0c, "walk root offset");
static_assert(offsetof(OpaqueWalkIndex, field10) == 0x10, "walk outer index");
static_assert(offsetof(OpaqueWalkIndex, field14) == 0x14, "walk middle index");
static_assert(offsetof(OpaqueWalkIndex, field18) == 0x18, "walk inner index");
static_assert(offsetof(OpaqueWalkIndex, field1c) == 0x1c, "walk leaf index");
static_assert(offsetof(OpaqueAppProps, field3c) == 0x3c,
              "app props head offset");
static_assert(offsetof(OpaqueAppProps, field118) == 0x118, "app props flag");
static_assert(offsetof(OpaqueApp, field3c) == 0x3c, "app props slot offset");
static_assert(offsetof(OpaquePageBuild, field0c) == 0x0c, "build instance id");
static_assert(offsetof(OpaquePageBuild, field14) == 0x14, "build first node");
static_assert(offsetof(OpaquePageBuild, field18) == 0x18, "build second node");
static_assert(offsetof(OpaquePageBuild, field1c) == 0x1c, "build third node");
static_assert(offsetof(OpaquePageBuild, field20) == 0x20, "build pair node");
static_assert(offsetof(OpaquePageBuild, field24) == 0x24, "build lead float");
static_assert(offsetof(OpaquePageBuild, field28) == 0x28, "build tail float");
static_assert(offsetof(OpaquePageBuild, field2c) == 0x2c, "build lead flag");
static_assert(offsetof(OpaquePageBuild, field2d) == 0x2d, "build tail flag");
static_assert(offsetof(OpaquePageBuild, field30) == 0x30, "build first extent");
static_assert(offsetof(OpaquePageBuild, field34) == 0x34,
              "build second extent");
static_assert(offsetof(OpaquePageBuild, field38) == 0x38, "build third extent");
static_assert(offsetof(OpaquePageBuild, field3c) == 0x3c,
              "build fourth extent");
static_assert(offsetof(OpaquePageBuild, field40) == 0x40, "build fifth float");
static_assert(offsetof(OpaquePageBuild, field44) == 0x44, "build sixth float");
static_assert(offsetof(OpaquePageBuild, field48) == 0x48, "build flag group");
static_assert(sizeof(OpaqueFlagSlot) == 4, "build flag group size");
static_assert(offsetof(OpaqueFlagSlot, bytes) == 0x00, "build flag bytes");
static_assert(offsetof(OpaquePageBuild, field4c) == 0x4c,
              "build seventh float");
static_assert(offsetof(OpaquePageBuild, field50) == 0x50, "build column count");
static_assert(offsetof(OpaquePageBuild, field54) == 0x54, "build row count");
static_assert(offsetof(OpaquePageBuild, field58) == 0x58, "build value a");
static_assert(offsetof(OpaquePageBuild, field5c) == 0x5c, "build value b");
static_assert(offsetof(OpaquePageBuild, field60) == 0x60, "build active page");
static_assert(offsetof(OpaquePageBuild, field64) == 0x64, "build selected key");
static_assert(offsetof(OpaquePageBuild, field70) == 0x70, "build node array");
static_assert(offsetof(OpaquePageBuild, field74) == 0x74, "build node cursor");
static_assert(offsetof(OpaquePageBuild, field78) == 0x78,
              "build node array end");
static_assert(sizeof(OpaquePageBuild) == 0x7c, "build size");

namespace openspore::reconstruction::pkg_palette_wave11 {

using ReleaseSlot01 PKG_PALETTE_W11_THISCALL = void (*)(void*);
using DropSlot02 PKG_PALETTE_W11_THISCALL = void (*)(void*);
using ModelSlot04 PKG_PALETTE_W11_THISCALL = OpaqueModel* (*)(OpaqueNode*);
using NodeSlot13 PKG_PALETTE_W11_THISCALL = const float* (*)(OpaqueNode*);
using NodeSlot24 PKG_PALETTE_W11_THISCALL = void (*)(OpaqueNode*, const float*);
using NodeSlot31 PKG_PALETTE_W11_THISCALL = void (*)(OpaqueNode*, std::uint32_t,
                                                     std::uint32_t);
using ModelSlot14 PKG_PALETTE_W11_THISCALL = const float* (*)(OpaqueModel*);
using ModelSlot48 PKG_PALETTE_W11_THISCALL = void (*)(OpaqueModel*, float,
                                                      float, float*);
using ModelSlot49 PKG_PALETTE_W11_THISCALL = void (*)(OpaqueModel*, float,
                                                      float, float*);
using ListSlot04 PKG_PALETTE_W11_THISCALL = void (*)(OpaquePropertyList*);
using ListSlot24 PKG_PALETTE_W11_THISCALL = bool (*)(OpaquePropertyList*,
                                                     std::uint32_t,
                                                     OpaqueProperty**);
using ListSlot2c PKG_PALETTE_W11_THISCALL =
    OpaquePropertyList* (*)(OpaquePropertyList*, std::uint32_t, std::uint32_t,
                            OpaquePropertyList**);
using PageSlot108 PKG_PALETTE_W11_THISCALL = void (*)(OpaquePageLead*, void*);
using ModelSlot31 PKG_PALETTE_W11_THISCALL = void (*)(OpaqueModel*,
                                                      std::uint32_t,
                                                      std::uint32_t);
using ModeSlot7c PKG_PALETTE_W11_THISCALL = void (*)(OpaqueGameModeManager*,
                                                     void*, OpaqueTextBuffer*);

extern "C" {

std::uint32_t PKG_PALETTE_W11_THISCALL
palette_w11_resolve_link_tail_005c2e00(OpaqueLink*);
void PKG_PALETTE_W11_THISCALL
palette_w11_release_page_hold_005c7320(OpaquePageHost*);
bool PKG_PALETTE_W11_THISCALL
palette_w11_walk_has_leaf_005c7c10(OpaqueWalkIndex*);
void PKG_PALETTE_W11_THISCALL palette_w11_fill_node_array_005c7ff0(
    OpaquePageBuild*, const std::uint32_t*, void*, void*);
bool PKG_PALETTE_W11_THISCALL palette_w11_load_page_state_005c85d0(
    OpaquePageBuild*, OpaqueProperty**, OpaqueProperty**);
std::uint32_t PKG_PALETTE_W11_THISCALL
palette_w11_place_page_nodes_005ca9f0(OpaquePageBuild*);

OpaqueLink* PKG_PALETTE_W11_THISCALL unresolved_005c9830(OpaqueLink*);
void* PKG_PALETTE_W11_CDECL unresolved_00401020();
void PKG_PALETTE_W11_THISCALL unresolved_005f0a60(void*, void*);

OpaqueCategoryList* PKG_PALETTE_W11_THISCALL
unresolved_005c5de0(OpaqueRootList*, std::int32_t);
OpaquePageList* PKG_PALETTE_W11_THISCALL
unresolved_005cae30(OpaqueCategoryList*, std::int32_t);
OpaqueEntryList* PKG_PALETTE_W11_THISCALL unresolved_005c1ce0(void*,
                                                              std::int32_t);

OpaquePropertyList* PKG_PALETTE_W11_CDECL unresolved_0067de30();
OpaqueGameModeManager* PKG_PALETTE_W11_CDECL unresolved_0067dcd0();
bool PKG_PALETTE_W11_CDECL unresolved_006a12a0(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*);
bool PKG_PALETTE_W11_CDECL unresolved_006a07d0(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*,
                                               std::uint32_t**);
bool PKG_PALETTE_W11_CDECL unresolved_006a0ae0(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*,
                                               OpaqueResourceKey*);
bool PKG_PALETTE_W11_CDECL unresolved_006a1160(OpaquePropertyList*,
                                               std::uint32_t, OpaqueFloat4*);
void PKG_PALETTE_W11_CDECL unresolved_006a1250(OpaquePropertyList*,
                                               std::uint32_t,
                                               OpaqueResourceKey*);
void PKG_PALETTE_W11_CDECL unresolved_00410370(OpaquePropertyList*,
                                               std::uint32_t, std::uint32_t*);
void PKG_PALETTE_W11_CDECL unresolved_00933960(OpaqueTextBuffer*);
void PKG_PALETTE_W11_CDECL unresolved_00f47380(void*);
void* PKG_PALETTE_W11_CDECL unresolved_00f473a0(std::uint32_t, std::uint32_t,
                                                std::uint32_t, std::uint32_t,
                                                std::uint32_t, std::uint32_t);

OpaqueNode* PKG_PALETTE_W11_THISCALL unresolved_005c66a0(OpaqueNode*);
bool PKG_PALETTE_W11_THISCALL unresolved_005c6810(OpaqueNode*, void*,
                                                  std::uint32_t, void*);
void* PKG_PALETTE_W11_THISCALL unresolved_005766e0(void*, OpaqueNode*);
void PKG_PALETTE_W11_THISCALL unresolved_005c8480(OpaqueNode**, OpaqueNode**,
                                                  OpaqueNode**);
std::int32_t PKG_PALETTE_W11_THISCALL unresolved_005ca9c0(OpaquePageBuild*);
std::uint32_t PKG_PALETTE_W11_THISCALL unresolved_005c2ec0(OpaqueNode*,
                                                           std::uint32_t);

const std::uint8_t* PKG_PALETTE_W11_THISCALL
unresolved_0041e920(OpaqueProperty*);
const std::uint32_t* PKG_PALETTE_W11_THISCALL
unresolved_0041e990(OpaqueProperty*);
const std::uint32_t* PKG_PALETTE_W11_THISCALL
unresolved_0041ea00(OpaqueProperty*);
const float* PKG_PALETTE_W11_THISCALL unresolved_0041ea70(OpaqueProperty*);

extern std::uint16_t g_text_01667bac[1];
extern std::uint16_t g_text_01667bae[1];
extern float g_float_013eb95c;
extern float g_float_014854c4;
extern float g_float_01485720;
extern OpaqueApp* g_dword_015fd918;
}

}
