#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-ADVANCED-PALETTE-WAVE11 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "PKG-ADVANCED-PALETTE-WAVE11 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4,
              "PKG-ADVANCED-PALETTE-WAVE11 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG_AP_THISCALL __thiscall
#define PKG_AP_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_AP_THISCALL __attribute__((thiscall))
#define PKG_AP_CDECL __attribute__((cdecl))
#else
#error "PKG-ADVANCED-PALETTE-WAVE11 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_advanced_palette_wave11 {

struct alignas(4) OpaqueIndexNode;
struct alignas(4) OpaqueIndex;
struct alignas(4) OpaqueItem;
struct alignas(4) OpaqueViewer;
struct alignas(4) OpaqueItemHostRoot;
struct alignas(4) OpaqueRect;
struct alignas(4) OpaqueBounds;
struct alignas(4) OpaqueLocalXf;
struct alignas(4) OpaqueKey3;
struct alignas(4) OpaqueFloatPair;
struct alignas(4) OpaqueTagPair;
struct alignas(4) OpaqueEvent;
struct alignas(4) OpaqueAddRef;
struct alignas(4) OpaqueRef;
struct alignas(4) OpaqueProbe;
struct alignas(4) OpaqueSource;
struct alignas(4) OpaqueItemHost;
struct alignas(4) OpaqueWindowHost;
struct alignas(4) OpaqueWindow;
struct alignas(4) OpaquePaletteHost;
struct alignas(4) OpaqueSub;
struct alignas(4) OpaqueTransform;
struct alignas(4) OpaqueFeature;
struct alignas(4) OpaqueRenderer;
struct alignas(4) OpaqueSwatch;
struct alignas(4) OpaqueSwatchHost;
struct alignas(4) OpaqueSwatchManager;
struct alignas(4) OpaqueManager;
struct alignas(4) OpaqueRegistry;
struct alignas(4) OpaqueService;
struct alignas(4) OpaqueProperty;
struct alignas(4) OpaqueApp;
struct alignas(4) OpaquePeer;

using Void00 = void(PKG_AP_THISCALL *)(void *);

struct alignas(4) OpaqueIndexNode {
  OpaqueIndexNode *field00;
  OpaqueIndexNode *field04;
  std::uint32_t field08;
  std::uint32_t field0c;
  std::uint32_t field10;
  std::uint32_t field14;
};

struct alignas(4) OpaqueIndex {
  OpaqueIndexNode *field00;
  OpaqueIndexNode *field04;
  OpaqueIndexNode *field08;
  OpaqueIndexNode *field0c;
};

struct alignas(4) OpaqueItemVtable {
  Void00 retain00;
  Void00 release04;
};

struct alignas(4) OpaqueItem {
  OpaqueItemVtable *vtable;
  std::uint8_t opaque04[0x174];
  std::uint32_t field178;
};

struct alignas(4) OpaqueRect {
  float field00;
  float field04;
  float field08;
  float field0c;
};

struct alignas(4) OpaqueBounds {
  float field00;
  float field04;
  float field08;
  float field0c;
  float field10;
  float field14;
};

struct alignas(4) OpaqueLocalXf {
  std::uintptr_t field00;
  std::uint16_t field04;
  std::uint16_t field06;
  float field08;
  float field0c;
  float field10;
  float field14;
};

struct alignas(4) OpaqueKey3 {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
};

struct alignas(4) OpaqueFloatPair {
  float field00;
  float field04;
};

struct alignas(4) OpaqueTagPair {
  std::uint8_t field00;
  std::uint8_t opaque01[3];
  std::uint32_t field04;
};

struct alignas(4) OpaqueEvent {
  std::uint32_t field00;
  std::uint32_t field04;
  std::uint32_t field08;
  float field0c;
  float field10;
  float field14;
  std::uint32_t field18;
};

struct alignas(4) OpaqueAddRefVtable {
  Void00 retain00;
  Void00 release04;
};

struct alignas(4) OpaqueAddRef {
  OpaqueAddRefVtable *vtable;
  std::uint8_t opaque04[0x1c];
};

struct alignas(4) OpaqueRefVtable {
  std::uintptr_t slot00;
  Void00 retain04;
  Void00 release08;
};

struct alignas(4) OpaqueRef {
  OpaqueRefVtable *vtable;
  std::uint8_t opaque04[0x08];
};

using ProbeSlot04 = std::uint32_t(PKG_AP_THISCALL *)(OpaqueProbe *,
                                                     std::uint32_t *,
                                                     std::uint32_t);
using ProbeSlot05 = bool(PKG_AP_THISCALL *)(OpaqueProbe *, std::uint32_t *);

struct alignas(4) OpaqueProbeVtable {
  std::uintptr_t slots00[0x04 / 4];
  ProbeSlot04 slot04;
  ProbeSlot05 slot05;
  std::uint8_t opaque0c[0x1c];
};

struct alignas(4) OpaqueProbe {
  OpaqueProbeVtable *vtable;
  std::uint8_t opaque04[0x24];
};

struct alignas(4) OpaqueSource {
  OpaqueRefVtable *vtable;
  std::uint32_t field04;
  OpaqueProbe *field08;
  std::uint32_t field0c;
  OpaqueItemHost *field10;
  OpaquePaletteHost *field14;
  std::uint32_t field18;
  std::uint32_t field1c;
  std::uint8_t opaque20[0x10];
  std::uint8_t field30;
  std::uint8_t opaque31[0x0b];
};

using ItemHostSlot0e = const float *(PKG_AP_THISCALL *)(OpaqueItemHost *);
using ItemHostSlot30 = void(PKG_AP_THISCALL *)(OpaqueItemHost *,
                                               OpaqueFloatPair *, float, float);

struct alignas(4) OpaqueItemHostVtable {
  std::uintptr_t slots00[0x04 / 4];
  Void00 retain04;
  Void00 release08;
  std::uintptr_t slots0c[0x38 / 4 - 0x0c / 4];
  ItemHostSlot0e slot38;
  std::uintptr_t slots3c[0xc0 / 4 - 0x3c / 4];
  ItemHostSlot30 slotc0;
  std::uint8_t opaquec4[0x3c];
};

struct alignas(4) OpaqueItemHost {
  OpaqueItemHostVtable *vtable;
  std::uint32_t field04;
  std::uint32_t field08;
  std::uint32_t field0c;
  std::uint8_t opaque10[0xfc];
};

using WindowRefSlot0c = std::uint32_t(PKG_AP_THISCALL *)(OpaqueViewer *,
                                                         std::uint32_t);

struct alignas(4) OpaqueWindowRefVtable {
  Void00 retain00;
  Void00 release04;
  std::uintptr_t slot08;
  std::uint8_t opaque0c[0x1c];
};

struct alignas(4) OpaqueWindowRef {
  OpaqueWindowRefVtable *vtable;
  OpaqueWindow *field04;
  std::uint8_t opaque08[0x1c];
};

using WindowSlot6c = void(PKG_AP_THISCALL *)(OpaqueWindow *, OpaqueRect *);
using WindowSlot7c = void(PKG_AP_THISCALL *)(OpaqueWindow *, std::uint32_t,
                                             std::uint32_t);
using WindowAttachec = void(PKG_AP_THISCALL *)(OpaqueWindow *, OpaqueWindow *);

struct alignas(4) OpaqueWindowVtable {
  Void00 retain00;
  Void00 release04;
  std::uintptr_t slots08[0x6c / 4 - 0x8 / 4];
  WindowSlot6c slot6c;
  std::uintptr_t slots70[0x7c / 4 - 0x70 / 4];
  WindowSlot7c slot7c;
  std::uintptr_t slots80[0xec / 4 - 0x80 / 4];
  WindowAttachec slotec;
  std::uint8_t opaqueF0[0x10];
};

struct alignas(4) OpaqueWindow {
  OpaqueWindowVtable *vtable;
  std::uint8_t opaque04[0xfc];
};

using PaletteSlot04 =
    OpaqueWindowHost *(PKG_AP_THISCALL *)(OpaquePaletteHost *);
using PaletteSlot0e = const float *(PKG_AP_THISCALL *)(OpaquePaletteHost *);
using WindowHostAttach = void(PKG_AP_THISCALL *)(OpaqueWindowHost *,
                                                 OpaqueWindow *);

struct alignas(4) OpaquePaletteHostVtable {
  std::uintptr_t slots00[0x10 / 4];
  PaletteSlot04 slot10;
  std::uintptr_t slots14[0x38 / 4 - 0x14 / 4];
  PaletteSlot0e slot38;
  std::uintptr_t slots3c[0x64 / 4 - 0x3c / 4];
  std::uint8_t opaque64[0x04];
};

struct alignas(4) OpaqueWindowHostVtable {
  std::uintptr_t slots00[0xec / 4];
  WindowHostAttach slotec;
  std::uint8_t opaqueF0[0x10];
};

struct alignas(4) OpaqueWindowHost {
  OpaqueWindowHostVtable *vtable;
  std::uint8_t opaque04[0xf4];
};

struct alignas(4) OpaquePaletteHost {
  OpaquePaletteHostVtable *vtable;
  std::uint8_t opaque04[0x64];
};

using SubSlot88 = void(PKG_AP_THISCALL *)(OpaqueSub *, std::uint32_t);

struct alignas(4) OpaqueSubVtable {
  std::uintptr_t slots00[0x88 / 4];
  SubSlot88 slot88;
  std::uint8_t opaque8c[0x2c];
};

struct alignas(4) OpaqueSub {
  OpaqueSubVtable *vtable;
  std::uint8_t opaque04[0xb8];
};

using TransformSlot24 = const float *(PKG_AP_THISCALL *)(OpaqueTransform *,
                                                         OpaqueTransform *);
using TransformSlot64 = std::int32_t(PKG_AP_THISCALL *)(OpaqueTransform *,
                                                        std::uint32_t,
                                                        std::uint32_t,
                                                        std::uint32_t);
using TransformSlot70 = void(PKG_AP_THISCALL *)(OpaqueTransform *,
                                                std::uint32_t, std::uint32_t,
                                                float, std::uint32_t);

struct alignas(4) OpaqueTransformVtable {
  std::uintptr_t slots00[0x24 / 4];
  TransformSlot24 slot24;
  std::uintptr_t slots28[0x64 / 4 - 0x28 / 4];
  TransformSlot64 slot64;
  std::uintptr_t slots68[0x70 / 4 - 0x68 / 4];
  TransformSlot70 slot70;
  std::uint8_t opaque74[0x1c];
};

struct alignas(4) OpaqueTransform {
  OpaqueTransformVtable *vtable;
  std::uint8_t opaque04[0x04];
  std::uint16_t field08;
  std::uint16_t field0a;
  float field0c;
  float field10;
  float field14;
  std::uint8_t opaque18[0x78];
  OpaqueFeature *field90;
  std::uint8_t opaque94[0x6c];
};

using FeatureSlot07 = bool(PKG_AP_THISCALL *)(OpaqueFeature *, std::uint32_t);
using FeatureSlot0a = void *(PKG_AP_THISCALL *)(OpaqueFeature *, std::uint32_t);

struct alignas(4) OpaqueFeatureVtable {
  std::uintptr_t slots00[0x1c / 4];
  FeatureSlot07 slot1c;
  std::uintptr_t slots20[0x28 / 4 - 0x20 / 4];
  FeatureSlot0a slot28;
  std::uint8_t opaque2c[0xd4];
};

struct alignas(4) OpaqueFeature {
  OpaqueFeatureVtable *vtable;
  std::uint8_t opaque04[0x108];
};

using RendererSlot03 = OpaqueSwatch *(PKG_AP_THISCALL *)(OpaqueRenderer *,
                                                         std::uint32_t);
using RendererSlot38 = const float *(PKG_AP_THISCALL *)(OpaqueRenderer *);

struct alignas(4) OpaqueRendererVtable {
  std::uintptr_t slots00[0x0c / 4];
  RendererSlot03 slot0c;
  std::uintptr_t slots10[0x38 / 4 - 0x10 / 4];
  RendererSlot38 slot38;
  std::uint8_t opaque3c[0x2c];
};

struct alignas(4) OpaqueRenderer {
  OpaqueRendererVtable *vtable;
  std::uint8_t opaque04[0x68];
};

using SwatchSlot06 = void(PKG_AP_THISCALL *)(OpaqueSwatch *, std::uint32_t);
using SwatchSlot0a = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, std::uint32_t,
                                             std::uint32_t);
using SwatchSlot0b = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, std::uint32_t,
                                             std::uint32_t);
using SwatchSlot0c = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, float, float,
                                             std::uint32_t);
using SwatchSlot0d = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, std::uint32_t,
                                             float, float, std::uint32_t);
using SwatchSlot0e = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, float, float,
                                             std::uint32_t);
using SwatchSlot0f = bool(PKG_AP_THISCALL *)(OpaqueSwatch *, std::uint32_t,
                                             float, float, std::uint32_t);

struct alignas(4) OpaqueSwatchVtable {
  std::uintptr_t slots00[0x24 / 4];
  SwatchSlot06 slot24;
  SwatchSlot0a slot28;
  SwatchSlot0b slot2c;
  SwatchSlot0c slot30;
  SwatchSlot0d slot34;
  SwatchSlot0e slot38;
  SwatchSlot0f slot3c;
  std::uint8_t opaque40[0x2c];
};

struct alignas(4) OpaqueSwatch {
  OpaqueSwatchVtable *vtable;
  std::uint8_t opaque04[0x6c];
};

using SwatchHostSlot38 =
    OpaqueRenderer *(PKG_AP_THISCALL *)(OpaqueSwatchHost *);

struct alignas(4) OpaqueSwatchHostVtable {
  std::uintptr_t slots00[0x38 / 4];
  SwatchHostSlot38 slot38;
  std::uint8_t opaque3c[0x28];
};

struct alignas(4) OpaqueSwatchHost {
  OpaqueSwatchHostVtable *vtable;
  std::uint8_t opaque04[0x40];
  std::uint32_t field44;
  std::uint8_t opaque48[0x18];
};

struct alignas(4) OpaqueSwatchManager {
  std::uint8_t opaque00[0x1c];
};

using ManagerSlot01 = std::uint32_t(PKG_AP_THISCALL *)(OpaqueManager *);
using ManagerSlot0f = void(PKG_AP_THISCALL *)(OpaqueManager *,
                                              OpaqueFloatPair *);
using ManagerSlot13 = void(PKG_AP_THISCALL *)(OpaqueManager *, std::uint32_t,
                                              std::uint32_t);
using ManagerSlot15 = std::uint32_t(PKG_AP_THISCALL *)(OpaqueManager *,
                                                       std::uint32_t);
using ManagerSlot16 = void(PKG_AP_THISCALL *)(OpaqueManager *, std::uint32_t,
                                              std::uint32_t);
using ManagerSlot17 = void(PKG_AP_THISCALL *)(OpaqueManager *, std::uint32_t,
                                              std::uint32_t);

struct alignas(4) OpaqueManagerVtable {
  std::uintptr_t slots00[0x04 / 4];
  ManagerSlot01 slot04;
  std::uintptr_t slots08[0x3c / 4 - 0x08 / 4];
  ManagerSlot0f slot3c;
  std::uintptr_t slots40[0x4c / 4 - 0x40 / 4];
  ManagerSlot13 slot4c;
  std::uintptr_t slots50[0x54 / 4 - 0x50 / 4];
  ManagerSlot15 slot54;
  ManagerSlot16 slot58;
  ManagerSlot17 slot5c;
  std::uint8_t opaque60[0x10];
};

struct alignas(4) OpaqueManager {
  OpaqueManagerVtable *vtable;
  std::uint8_t opaque04[0x60];
};

using RegistrySlot05 = void(PKG_AP_THISCALL *)(OpaqueRegistry *, OpaqueBounds *,
                                               std::uint32_t, std::uint32_t,
                                               float, std::uint32_t, float);

struct alignas(4) OpaqueRegistryVtable {
  std::uintptr_t slots00[0x14 / 4];
  RegistrySlot05 slot14;
  std::uint8_t opaque18[0x2c];
};

struct alignas(4) OpaqueRegistry {
  OpaqueRegistryVtable *vtable;
  std::uint8_t opaque04[0x44];
};

using ServiceSlot0b = bool(PKG_AP_THISCALL *)(OpaqueService *, std::uint32_t,
                                              std::uint32_t, OpaqueProperty **);

struct alignas(4) OpaqueServiceVtable {
  std::uintptr_t slots00[0x2c / 4];
  ServiceSlot0b slot2c;
  std::uint8_t opaque30[0x08];
};

struct alignas(4) OpaqueService {
  OpaqueServiceVtable *vtable;
  std::uint8_t opaque04[0x38];
};

using PropertySlot01 = void(PKG_AP_THISCALL *)(OpaqueProperty *);
using PropertySlot07 = bool(PKG_AP_THISCALL *)(OpaqueProperty *, std::uint32_t);

struct alignas(4) OpaquePropertyVtable {
  std::uintptr_t slots00[0x04 / 4];
  PropertySlot01 slot04;
  std::uintptr_t slots08[0x1c / 4 - 0x08 / 4];
  PropertySlot07 slot1c;
  std::uint8_t opaque20[0x2c];
};

struct alignas(4) OpaqueProperty {
  OpaquePropertyVtable *vtable;
  std::uint8_t opaque04[0x4c];
};

using AppSlot05 = void(PKG_AP_THISCALL *)(OpaqueApp *, std::uint32_t, void *,
                                          std::uint32_t);
using AppSlot09 = void(PKG_AP_THISCALL *)(OpaqueApp *, void *, std::uint32_t);

struct alignas(4) OpaqueAppVtable {
  std::uintptr_t slots00[0x14 / 4];
  AppSlot05 slot14;
  std::uintptr_t slots18[0x24 / 4 - 0x18 / 4];
  AppSlot09 slot24;
  std::uint8_t opaque28[0x2c];
};

using PeerSlot08 = std::uint32_t(PKG_AP_THISCALL *)(OpaquePeer *);

struct alignas(4) OpaquePeerVtable {
  std::uintptr_t slots00[0x20 / 4];
  PeerSlot08 slot20;
  std::uint8_t opaque24[0x1c];
};

struct alignas(4) OpaquePeer {
  OpaquePeerVtable *vtable;
  std::uint8_t opaque04[0x3c];
};

struct alignas(4) OpaqueApp {
  OpaqueAppVtable *vtable;
  std::uint8_t opaque04[0x58];
};

using ViewerSlot0c = std::uint32_t(PKG_AP_THISCALL *)(OpaqueViewer *,
                                                      std::uint32_t);
using ViewerSlot18 = bool(PKG_AP_THISCALL *)(OpaqueViewer *, OpaqueEvent *,
                                             std::uint32_t, std::uint32_t);
using ViewerSlot24 = void(PKG_AP_THISCALL *)(OpaqueViewer *,
                                             const OpaqueKey3 *);
using ViewerSlot34 = std::uint32_t(PKG_AP_THISCALL *)(OpaqueViewer *,
                                                      std::uint32_t,
                                                      std::uint32_t);
using ViewerSlot40 = void(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot44 = bool(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot48 = void(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot4c = void(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot50 = void(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot58 = void(PKG_AP_THISCALL *)(OpaqueViewer *);
using ViewerSlot60 = void(PKG_AP_THISCALL *)(OpaqueViewer *);

struct alignas(4) OpaqueViewerVtable {
  std::uintptr_t slots00[0x0c / 4];
  ViewerSlot0c slot0c;
  std::uintptr_t slots10[0x18 / 4 - 0x4];
  ViewerSlot18 slot18;
  std::uintptr_t slots1c[0x24 / 4 - 0x1c / 4];
  ViewerSlot24 slot24;
  std::uintptr_t slots28[0x34 / 4 - 0x28 / 4];
  ViewerSlot34 slot34;
  std::uintptr_t slots38[0x40 / 4 - 0x38 / 4];
  ViewerSlot40 slot40;
  ViewerSlot44 slot44;
  ViewerSlot48 slot48;
  ViewerSlot4c slot4c;
  ViewerSlot50 slot50;
  std::uintptr_t slots54[0x58 / 4 - 0x54 / 4];
  ViewerSlot58 slot58;
  std::uintptr_t slots5c[0x60 / 4 - 0x5c / 4];
  ViewerSlot60 slot60;
  std::uintptr_t slots64[0x6c / 4 - 0x64 / 4];
  std::uintptr_t slot6c;
  std::uintptr_t slots70[0xe4 / 4 - 0x70 / 4];
  std::uintptr_t slote4;
  std::uintptr_t slotsE8[1];
  std::uintptr_t slotec;
  std::uintptr_t slotsF0[2];
  std::uintptr_t slotf8;
};

struct alignas(4) OpaqueViewer {
  OpaqueViewerVtable *vtable;
  std::uint32_t field04;
  std::uint32_t field08;
  std::uint32_t field0c;
  std::uint32_t field10;
  OpaqueViewer *field14;
  OpaqueViewer *field18;
  OpaqueViewer *field1c;
  std::uint32_t field20;
  std::uint32_t field24;
  std::uint8_t opaque28[0x0c];
  OpaqueSub *field34;
  std::uint32_t field38;
  OpaqueViewer *field3c;
  std::uint32_t field40;
  std::uint32_t field44;
  std::uint32_t field48;
  std::uint32_t field4c;
  std::uint32_t field50;
  std::uint32_t field54;
  std::uint32_t field58;
  OpaquePaletteHost *field5c;
  OpaqueItemHost *field60;
  float field64;
  float field68;
  float field6c;
  float field70;
  float field74;
  float field78;
  float field7c;
  float field80;
  float field84;
  float field88;
  float field8c;
  float field90;
  float field94;
  float field98;
  float field9c;
  float fielda0;
  float fielda4;
  float fielda8;
  float fieldac;
  float fieldb0;
  float fieldb4;
  float fieldb8;
  float fieldbc;
  float fieldc0;
  float fieldc4;
  float fieldc8;
  float fieldcc;
  float fieldd0;
  float fieldd4;
  float fieldd8;
  std::uint8_t opaqueDC[0x0e];
  std::uint8_t fieldea;
  std::uint8_t fieldeb;
  std::uint8_t fieldec;
  std::uint8_t opaqueed[0x03];
  OpaqueSub *fieldf0;
  std::uint8_t opaquef4[0x0c];
  std::uint32_t field100;
  std::uint8_t opaque104[0x14];
  OpaqueTransform *field118;
  std::uint8_t opaque11c[0x44];
  std::uint8_t opaque160;
  std::uint8_t opaque161;
  std::uint8_t opaque162;
  std::uint8_t opaque163;
  std::uint8_t opaque164[0x02];
  std::uint8_t opaque166;
  std::uint8_t opaque167[0x02];
  std::uint8_t opaque169;
  std::uint8_t opaque16a;
  std::uint8_t opaque16b;
  std::uint8_t field16c;
  std::uint8_t field16d[5];
  std::uint8_t opaque172[2];
  std::uint32_t field174;
  std::uint32_t field178;
  OpaqueSource *field17c;
  OpaqueItemHost *field180;
  std::uint8_t opaque184;
  std::uint8_t opaque185[0x07];
  OpaqueAddRef *field18c;
  std::uint32_t field190;
  OpaqueItemHost *field194;
  std::uint8_t field198;
  std::uint8_t field199;
  std::uint8_t opaque19a[0x06];
  std::uint8_t field1a0[0x18];
  OpaqueWindow *field1b8;
  OpaqueWindow *field1bc;
  float field1c0;
  float field1c4;
};

struct alignas(4) OpaqueAnchor {
  std::uintptr_t field00;
  std::uintptr_t field04;
  std::uint32_t field08;
  std::uint32_t field0c;
  std::uint32_t field10;
  std::uint32_t field14;
  std::uint32_t field18;
  std::uint32_t field1c;
  std::uint32_t field20;
  OpaqueAddRef *field24;
};

struct alignas(4) OpaqueItemHostRoot {
  std::uintptr_t vtable;
  std::uint8_t opaque04[4];
  OpaqueIndex field08;
  std::uint8_t opaque18[0x0c];
  OpaqueIndex field24;
  std::uint8_t opaque34[0x0c];
  std::uint32_t field40;
  std::uint32_t field50;
};

static_assert(sizeof(OpaqueIndexNode) == 0x18, "index node size");
static_assert(offsetof(OpaqueIndexNode, field10) == 0x10, "index node key");
static_assert(offsetof(OpaqueIndexNode, field14) == 0x14, "index node value");
static_assert(sizeof(OpaqueIndex) == 0x10, "index header size");
static_assert(offsetof(OpaqueIndex, field0c) == 0x0c, "index header root");
static_assert(sizeof(OpaqueItem) == 0x17c, "item allocation size");
static_assert(offsetof(OpaqueItem, field178) == 0x178, "item sequence word");
static_assert(sizeof(OpaqueAddRef) == 0x20, "add ref object size");
static_assert(sizeof(OpaqueRect) == 0x10, "rect size");
static_assert(sizeof(OpaqueBounds) == 0x18, "bounds size");
static_assert(sizeof(OpaqueKey3) == 0x0c, "key size");
static_assert(sizeof(OpaqueFloatPair) == 0x08, "float pair size");
static_assert(sizeof(OpaqueTagPair) == 0x08, "tag pair size");
static_assert(sizeof(OpaqueLocalXf) == 0x18, "local transform size");
static_assert(sizeof(OpaqueAnchor) == 0x28, "anchor block size");
static_assert(offsetof(OpaqueAnchor, field0c) == 0x0c, "anchor payload word");
static_assert(offsetof(OpaqueAnchor, field24) == 0x24, "anchor window word");
static_assert(offsetof(OpaqueLocalXf, field0c) == 0x0c, "local centre x");
static_assert(sizeof(OpaqueEvent) == 0x1c, "event size");
static_assert(offsetof(OpaqueEvent, field0c) == 0x0c, "event mode word");
static_assert(offsetof(OpaqueEvent, field10) == 0x10, "event first float");
static_assert(offsetof(OpaqueEvent, field18) == 0x18, "event item index");
static_assert(offsetof(OpaqueSource, field08) == 0x08, "source probe");
static_assert(offsetof(OpaqueSource, field10) == 0x10, "source palette host");
static_assert(offsetof(OpaqueSource, field14) == 0x14, "source host word");
static_assert(offsetof(OpaqueSource, field1c) == 0x1c, "source instance");
static_assert(offsetof(OpaqueSource, field30) == 0x30, "source mirror byte");
static_assert(offsetof(OpaqueItemHostVtable, retain04) == 0x04,
              "item host retain index");
static_assert(offsetof(OpaqueItemHostVtable, release08) == 0x08,
              "item host release index");
static_assert(offsetof(OpaqueItemHostVtable, slot38) == 0x38,
              "item host rect slot index");
static_assert(offsetof(OpaqueItemHostVtable, slotc0) == 0xc0,
              "item host half extent slot index");
static_assert(offsetof(OpaqueWindowVtable, slotec) == 0xec,
              "window host attach slot index");
static_assert(offsetof(OpaqueWindowVtable, slot6c) == 0x6c,
              "window rect slot index");
static_assert(offsetof(OpaqueWindowVtable, slot7c) == 0x7c,
              "window pair slot index");
static_assert(offsetof(OpaqueWindowVtable, slotec) == 0xec,
              "window attach slot index");
static_assert(offsetof(OpaquePaletteHostVtable, slot10) == 0x10,
              "palette host key slot index");
static_assert(offsetof(OpaquePaletteHostVtable, slot38) == 0x38,
              "palette host rect slot index");
static_assert(offsetof(OpaqueWindowHostVtable, slotec) == 0xec,
              "window host attach slot index");
static_assert(offsetof(OpaqueManagerVtable, slot4c) == 0x4c,
              "manager slot fourty index");
static_assert(offsetof(OpaqueItemHost, field0c) == 0x0c,
              "item host probe word offset");
static_assert(offsetof(OpaqueSubVtable, slot88) == 0x88, "sub slot index");
static_assert(offsetof(OpaqueTransformVtable, slot24) == 0x24,
              "transform bounds slot index");
static_assert(offsetof(OpaqueTransformVtable, slot64) == 0x64,
              "transform count slot index");
static_assert(offsetof(OpaqueTransformVtable, slot70) == 0x70,
              "transform reset slot index");
static_assert(offsetof(OpaqueTransform, field08) == 0x08,
              "transform flag half word");
static_assert(offsetof(OpaqueTransform, field0c) == 0x0c, "transform centre x");
static_assert(offsetof(OpaqueTransform, field10) == 0x10, "transform centre y");
static_assert(offsetof(OpaqueTransform, field14) == 0x14, "transform centre z");
static_assert(offsetof(OpaqueTransform, field90) == 0x90,
              "transform feature offset");
static_assert(offsetof(OpaqueFeatureVtable, slot1c) == 0x1c,
              "feature probe slot index");
static_assert(offsetof(OpaqueFeatureVtable, slot28) == 0x28,
              "feature resolve slot index");
static_assert(offsetof(OpaqueRendererVtable, slot0c) == 0x0c,
              "renderer swatch slot index");
static_assert(offsetof(OpaqueRendererVtable, slot38) == 0x38,
              "renderer rect slot index");
static_assert(offsetof(OpaqueSwatchVtable, slot24) == 0x24,
              "swatch slot twenty four index");
static_assert(offsetof(OpaqueSwatchVtable, slot28) == 0x28,
              "swatch slot twenty eight index");
static_assert(offsetof(OpaqueSwatchVtable, slot2c) == 0x2c,
              "swatch slot two c index");
static_assert(offsetof(OpaqueSwatchVtable, slot30) == 0x30,
              "swatch slot thirty index");
static_assert(offsetof(OpaqueSwatchVtable, slot34) == 0x34,
              "swatch slot thirty four index");
static_assert(offsetof(OpaqueSwatchVtable, slot38) == 0x38,
              "swatch slot thirty eight index");
static_assert(offsetof(OpaqueSwatchVtable, slot3c) == 0x3c,
              "swatch slot three c index");
static_assert(offsetof(OpaqueSwatchHostVtable, slot38) == 0x38,
              "swatch host renderer slot index");
static_assert(offsetof(OpaqueSwatchHost, field44) == 0x44, "swatch host word");
static_assert(offsetof(OpaqueManagerVtable, slot04) == 0x04,
              "manager slot four index");
static_assert(offsetof(OpaqueManagerVtable, slot3c) == 0x3c,
              "manager slot three c index");
static_assert(offsetof(OpaqueManagerVtable, slot54) == 0x54,
              "manager slot fifty four index");
static_assert(offsetof(OpaqueManagerVtable, slot58) == 0x58,
              "manager slot fifty eight index");
static_assert(offsetof(OpaqueManagerVtable, slot5c) == 0x5c,
              "manager slot five c index");
static_assert(offsetof(OpaqueRegistryVtable, slot14) == 0x14,
              "registry slot fourteen index");
static_assert(offsetof(OpaqueServiceVtable, slot2c) == 0x2c,
              "service slot two c index");
static_assert(offsetof(OpaquePropertyVtable, slot04) == 0x04,
              "property release index");
static_assert(offsetof(OpaquePropertyVtable, slot1c) == 0x1c,
              "property probe index");
static_assert(offsetof(OpaqueAppVtable, slot14) == 0x14, "app post slot index");
static_assert(offsetof(OpaqueAppVtable, slot24) == 0x24,
              "app notify slot index");
static_assert(offsetof(OpaqueViewerVtable, slot0c) == 0x0c,
              "viewer host state slot index");
static_assert(offsetof(OpaqueViewerVtable, slot18) == 0x18,
              "viewer dispatcher slot index");
static_assert(offsetof(OpaqueViewerVtable, slot24) == 0x24,
              "viewer name slot index");
static_assert(offsetof(OpaqueViewerVtable, slot34) == 0x34,
              "viewer window slot index");
static_assert(offsetof(OpaqueViewerVtable, slot40) == 0x40,
              "viewer slot forty index");
static_assert(offsetof(OpaqueViewerVtable, slot44) == 0x44,
              "viewer slot forty four index");
static_assert(offsetof(OpaqueViewerVtable, slot48) == 0x48,
              "viewer slot forty eight index");
static_assert(offsetof(OpaqueViewerVtable, slot4c) == 0x4c,
              "viewer slot fourty index");
static_assert(offsetof(OpaqueViewerVtable, slot50) == 0x50,
              "viewer slot fifty index");
static_assert(offsetof(OpaqueViewerVtable, slot58) == 0x58,
              "viewer slot fifty eight index");
static_assert(offsetof(OpaqueViewerVtable, slot60) == 0x60,
              "viewer slot sixty index");
static_assert(offsetof(OpaqueViewerVtable, slot6c) == 0x6c,
              "viewer slot six c index");
static_assert(offsetof(OpaqueViewerVtable, slote4) == 0xe4,
              "viewer slot e4 index");
static_assert(offsetof(OpaqueViewerVtable, slotec) == 0xec,
              "viewer slot ec index");
static_assert(offsetof(OpaqueViewerVtable, slotf8) == 0xf8,
              "viewer slot f8 index");
static_assert(offsetof(OpaqueViewer, field04) == 0x04, "viewer word four");
static_assert(offsetof(OpaqueViewer, field10) == 0x10, "viewer word ten");
static_assert(offsetof(OpaqueViewer, field14) == 0x14, "viewer model slot a");
static_assert(offsetof(OpaqueViewer, field18) == 0x18, "viewer model slot b");
static_assert(offsetof(OpaqueViewer, field34) == 0x34, "viewer first index");
static_assert(offsetof(OpaqueViewer, field4c) == 0x4c, "viewer key head");
static_assert(offsetof(OpaqueViewer, field50) == 0x50, "viewer key word one");
static_assert(offsetof(OpaqueViewer, field54) == 0x54, "viewer key word two");
static_assert(offsetof(OpaqueViewer, field5c) == 0x5c, "viewer palette id");
static_assert(offsetof(OpaqueViewer, field60) == 0x60, "viewer item host");
static_assert(offsetof(OpaqueViewer, field84) == 0x84, "viewer half width");
static_assert(offsetof(OpaqueViewer, field88) == 0x88, "viewer half height");
static_assert(offsetof(OpaqueViewer, field8c) == 0x8c, "viewer half width two");
static_assert(offsetof(OpaqueViewer, field90) == 0x90,
              "viewer half height two");
static_assert(offsetof(OpaqueViewer, fieldc0) == 0xc0, "viewer zoom word");
static_assert(offsetof(OpaqueViewer, fieldd8) == 0xd8, "viewer scale word");
static_assert(offsetof(OpaqueViewer, fieldea) == 0xea, "viewer mirror byte");
static_assert(offsetof(OpaqueViewer, fieldeb) == 0xeb, "viewer gate byte");
static_assert(offsetof(OpaqueViewer, fieldec) == 0xec, "viewer action byte");
static_assert(offsetof(OpaqueViewer, fieldf0) == 0xf0, "viewer sub slot");
static_assert(offsetof(OpaqueViewer, field100) == 0x100, "viewer mode word");
static_assert(offsetof(OpaqueViewer, field118) == 0x118, "viewer transform");
static_assert(offsetof(OpaqueViewer, opaque160) == 0x160, "viewer built byte");
static_assert(offsetof(OpaqueViewer, opaque163) == 0x163, "viewer extra byte");
static_assert(offsetof(OpaqueViewer, opaque166) == 0x166,
              "viewer visible byte");
static_assert(offsetof(OpaqueViewer, opaque169) == 0x169, "viewer reset byte");
static_assert(offsetof(OpaqueViewer, opaque16b) == 0x16b, "viewer swatch byte");
static_assert(offsetof(OpaqueViewer, field16c) == 0x16c, "viewer live byte");
static_assert(offsetof(OpaqueViewer, field16d) == 0x16d, "viewer slot bytes");
static_assert(offsetof(OpaqueViewer, field174) == 0x174, "viewer model word");
static_assert(offsetof(OpaqueViewer, field178) == 0x178, "viewer sequence");
static_assert(offsetof(OpaqueViewer, field17c) == 0x17c, "viewer source");
static_assert(offsetof(OpaqueViewer, field180) == 0x180, "viewer entry");
static_assert(offsetof(OpaqueViewer, opaque184) == 0x184, "viewer locked byte");
static_assert(offsetof(OpaqueViewer, field18c) == 0x18c, "viewer window");
static_assert(offsetof(OpaqueViewer, field190) == 0x190, "viewer message id");
static_assert(offsetof(OpaqueViewer, field194) == 0x194, "viewer parent");
static_assert(offsetof(OpaqueViewer, field198) == 0x198, "viewer flag byte");
static_assert(offsetof(OpaqueViewer, field199) == 0x199,
              "viewer flag byte two");
static_assert(offsetof(OpaqueViewer, field1a0) == 0x1a0, "viewer clock");
static_assert(offsetof(OpaqueViewer, field1b8) == 0x1b8, "viewer first window");
static_assert(offsetof(OpaqueViewer, field1bc) == 0x1bc,
              "viewer second window");
static_assert(offsetof(OpaqueViewer, field1c0) == 0x1c0, "viewer pair x");
static_assert(offsetof(OpaqueViewer, field1c4) == 0x1c4, "viewer pair y");
static_assert(sizeof(OpaqueViewer) == 0x1c8, "viewer size");
static_assert(offsetof(OpaqueItemHostRoot, field08) == 0x08,
              "item host root first index offset");
static_assert(offsetof(OpaqueItemHostRoot, field24) == 0x24,
              "item host root second index offset");
static_assert(offsetof(OpaqueItemHostRoot, field40) == 0x40,
              "item host root counter offset");
static_assert(offsetof(OpaqueViewer, field34) == 0x34, "viewer sub holder");
static_assert(offsetof(OpaqueViewer, field40) == 0x40, "viewer name key");
static_assert(offsetof(OpaqueViewer, field48) == 0x48, "viewer name key tail");
static_assert(sizeof(decltype(OpaqueViewerVtable::slot18)) == 4,
              "viewer dispatcher slot is a single 32-bit pointer");
static_assert(sizeof(decltype(OpaqueSwatchVtable::slot30)) == 4,
              "swatch slot is a single 32-bit pointer");
static_assert(sizeof(decltype(OpaqueRegistryVtable::slot14)) == 4,
              "registry slot is a single 32-bit pointer");

extern std::uint32_t g_table_013f9bb0;
extern float g_table_01485720;
extern std::uint32_t g_table_0151c40c;
extern std::uint32_t g_table_0151c410;
extern float g_table_013f9d90;
extern float g_table_013f51ac;
extern float g_table_015f1ce4;
extern float g_table_015f1ce8;
extern float g_table_015f1cec;
extern float g_table_013eb1c0;
extern float g_table_0151c700;
extern float g_table_01471064;

extern "C" {

OpaqueItem *PKG_AP_THISCALL unresolved_005f0ca0(OpaqueItemHostRoot *,
                                                OpaqueItem *);

std::uint32_t PKG_AP_THISCALL unresolved_005f2350(OpaqueRect *,
                                                  const OpaqueRect *);

bool PKG_AP_THISCALL unresolved_005f27c0(OpaqueViewer *, std::uint32_t,
                                         OpaqueEvent *);

void PKG_AP_THISCALL unresolved_005f2e00(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f2ee0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f30b0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f3cf0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f4310(OpaqueViewer *, const OpaqueKey3 *,
                                         std::uint32_t, OpaqueAddRef *,
                                         std::uint32_t, OpaqueItemHost *,
                                         OpaqueSource *, std::uint8_t);

void PKG_AP_THISCALL unresolved_005f49f0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f4b80(OpaqueViewer *);

void *PKG_AP_CDECL unresolved_00f473a0(std::uint32_t, std::uint32_t,
                                       std::uint32_t, std::uint32_t,
                                       std::uint32_t, std::uint32_t);

OpaqueSwatchManager *PKG_AP_CDECL unresolved_00401020();

OpaqueSwatchHost *PKG_AP_THISCALL unresolved_01137690(OpaqueSwatchManager *);

std::uint32_t PKG_AP_THISCALL unresolved_0113ae10(OpaqueSwatchManager *);

void PKG_AP_THISCALL unresolved_005ed6c0(OpaqueSwatchHost *);

OpaqueManager *PKG_AP_CDECL unresolved_0067caa0();

void *PKG_AP_CDECL unresolved_0067cad0();

OpaqueApp *PKG_AP_CDECL unresolved_0067dcc0();

OpaqueService *PKG_AP_CDECL unresolved_0067de30();

OpaqueRegistry *PKG_AP_CDECL unresolved_0067ddb0();

std::uint32_t PKG_AP_CDECL unresolved_00435e90();

void PKG_AP_CDECL unresolved_00435ed0(std::uint32_t, std::uint32_t);

OpaquePeer *PKG_AP_CDECL unresolved_00a206f0();

OpaqueAddRef *PKG_AP_CDECL unresolved_00804500();

bool PKG_AP_THISCALL unresolved_006c1100(OpaqueAddRef *);

std::uint32_t PKG_AP_THISCALL unresolved_006c10e0(OpaqueAddRef *);

void PKG_AP_THISCALL unresolved_00803bd0(OpaqueAddRef *, std::uint32_t);

std::uint8_t PKG_AP_CDECL unresolved_008d2fb0(std::uint32_t);

void PKG_AP_CDECL unresolved_0040cf10(OpaqueProperty *, std::uint32_t, float *);

void *PKG_AP_CDECL unresolved_00807880(const OpaqueKey3 *, float, float,
                                       void *);

void PKG_AP_CDECL unresolved_00807d30(OpaqueSwatchHost *, void *,
                                      OpaqueTagPair);

void *PKG_AP_CDECL unresolved_005f3b20(const OpaqueKey3 *, const OpaqueKey3 *,
                                       std::uint32_t, std::uint32_t,
                                       std::uint32_t, std::uint32_t,
                                       const OpaqueKey3 *, std::uint32_t);

OpaqueItem *PKG_AP_THISCALL unresolved_005f6bd0(OpaqueItem *);

OpaqueIndexNode *PKG_AP_THISCALL unresolved_005f0b40(OpaqueIndex *,
                                                     std::uint32_t *);

OpaqueIndexNode *PKG_AP_THISCALL unresolved_005f0bc0(OpaqueIndex *,
                                                     OpaqueItem **);

void PKG_AP_THISCALL unresolved_005f2fd0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f3600(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_005f3400(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_0080d7c0(OpaqueViewer *, std::uint8_t);

std::uint32_t PKG_AP_THISCALL unresolved_0080d610(OpaqueViewer *);

std::uint32_t PKG_AP_THISCALL unresolved_0080d5f0(OpaqueViewer *);

std::uint32_t PKG_AP_THISCALL unresolved_0093b6c0(OpaqueViewer *);

void PKG_AP_THISCALL unresolved_0093a1a0(std::uint8_t *, std::uint32_t);

OpaqueLocalXf *PKG_AP_THISCALL unresolved_00409930(OpaqueLocalXf *);

void PKG_AP_THISCALL unresolved_00409dd0(OpaqueBounds *, OpaqueLocalXf *);

OpaqueBounds *PKG_AP_THISCALL unresolved_00511140(OpaqueBounds *,
                                                  const OpaqueBounds *);

void PKG_AP_THISCALL unresolved_00571d60(OpaqueBounds *, const OpaqueBounds *);

bool PKG_AP_THISCALL unresolved_005c6670(OpaqueItemHost *, OpaqueItemHost *);

OpaqueBounds *PKG_AP_THISCALL unresolved_005f2320(OpaqueFeature *);

float PKG_AP_CDECL unresolved_005f2390(OpaqueViewer *, std::uint32_t,
                                       OpaqueItemHost *, float, float, float);

void *PKG_AP_THISCALL unresolved_00b5f950(OpaqueWindow **, OpaqueWindow *);

void PKG_AP_THISCALL unresolved_0080d710(OpaqueSwatchHost *, std::uint32_t,
                                         std::uint32_t, std::uint8_t);

void PKG_AP_CDECL unresolved_00804fc0(OpaqueViewer *, float);
}

}
