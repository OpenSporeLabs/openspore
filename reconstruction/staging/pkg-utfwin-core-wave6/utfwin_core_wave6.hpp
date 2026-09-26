#pragma once

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_UTFWIN_CORE_THISCALL __thiscall
#define PKG_UTFWIN_CORE_CDECL __cdecl
#define PKG_UTFWIN_CORE_STDCALL __stdcall
#else
#define PKG_UTFWIN_CORE_THISCALL __attribute__((thiscall))
#define PKG_UTFWIN_CORE_CDECL __attribute__((cdecl))
#define PKG_UTFWIN_CORE_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_utfwin_core_wave6 {

using OpaqueWord = std::uint32_t;

struct DropIconObject;
struct ResourceFactory;
struct CursorManager;
struct WindowCore;
struct Drawable;
struct TooltipCore;
struct RefObject;

using DropIconDispatch = void(PKG_UTFWIN_CORE_THISCALL*)(DropIconObject*);
using ResourceFactoryRead =
    OpaqueWord*(PKG_UTFWIN_CORE_THISCALL*)(ResourceFactory*);
using CursorManagerDispatch = bool(PKG_UTFWIN_CORE_THISCALL*)(
    CursorManager*, ResourceFactory*, DropIconObject*, OpaqueWord, OpaqueWord);
using CursorAllocate = void*(PKG_UTFWIN_CORE_CDECL*)(OpaqueWord, const char*,
                                                     OpaqueWord, OpaqueWord,
                                                     OpaqueWord, OpaqueWord);

struct DropIconObjectVTable {
  DropIconDispatch dispatch_00 = nullptr;
};

struct DropIconObject {
  DropIconObjectVTable* vtable_00 = nullptr;
  OpaqueWord field_04 = 0;
  OpaqueWord field_08 = 0;
  OpaqueWord field_0c = 0;
  OpaqueWord field_10 = 0;
  OpaqueWord field_14 = 0;
};

struct ResourceFactoryVTable {
  void* slots_00[4]{};
  ResourceFactoryRead read_10 = nullptr;
};

struct ResourceFactory {
  ResourceFactoryVTable* vtable_00 = nullptr;
};

struct CursorManagerVTable {
  void* slots_00[9]{};
  CursorManagerDispatch dispatch_24 = nullptr;
};

struct CursorManager {
  CursorManagerVTable* vtable_00 = nullptr;
  std::int32_t field_04 = 0;
};

struct CursorRuntime {
  CursorAllocate allocate = nullptr;
  DropIconDispatch icon_dispatch = nullptr;
};

struct DrawableVTable {
  std::int32_t(PKG_UTFWIN_CORE_THISCALL* add_ref_00)(Drawable*) = nullptr;
  std::int32_t(PKG_UTFWIN_CORE_THISCALL* release_04)(Drawable*) = nullptr;
};

struct Drawable {
  DrawableVTable* vtable_00 = nullptr;
};

using WindowDestroy = void(PKG_UTFWIN_CORE_THISCALL*)(WindowCore*, OpaqueWord);
using WindowGetDrawable = Drawable*(PKG_UTFWIN_CORE_THISCALL*)(WindowCore*);

struct WindowVTable {
  void* add_ref_00 = nullptr;
  void* release_04 = nullptr;
  WindowDestroy destroy_08 = nullptr;
  void* slots_0c[33]{};
  WindowGetDrawable get_drawable_90 = nullptr;
};

struct WindowCore {
  WindowVTable* vtable_00 = nullptr;
  void* vtable_04 = nullptr;
  std::uint8_t opaque_08[0x20]{};
  std::int32_t ref_count_28 = 0;
  std::uint8_t opaque_2c[0x78]{};
  OpaqueWord cursor_id_a4 = 0;
  std::uint8_t opaque_a8[0x13c]{};
  Drawable* drawable_1e4 = nullptr;
  std::uint8_t opaque_1e8[8]{};
};

using TooltipRelease = void(PKG_UTFWIN_CORE_THISCALL*)(RefObject*);
using TooltipDestroy = void(PKG_UTFWIN_CORE_THISCALL*)(RefObject*);

struct RefObjectVTable {
  void* add_ref_00 = nullptr;
  TooltipRelease release_04 = nullptr;
  TooltipDestroy destroy_08 = nullptr;
};

struct RefObject {
  RefObjectVTable* vtable_00 = nullptr;
};

struct TooltipCoreVTable {
  OpaqueWord slots_00[1]{};
};

struct TooltipCore {
  TooltipCoreVTable* vtable_00 = nullptr;
  void* vtable_04 = nullptr;
  RefObject* field_08 = nullptr;
  RefObject* field_0c = nullptr;
  RefObject* field_10 = nullptr;
  RefObject* field_14 = nullptr;
  std::uint8_t opaque_18[0x50]{};
};

struct ImageCore {
  void* vtable_00 = nullptr;
};

struct TooltipRuntime {
  void(PKG_UTFWIN_CORE_CDECL* deallocate)(void*) = nullptr;
};

extern OpaqueWord tooltip_sentinel_0164f328;

CursorRuntime& cursor_runtime();
TooltipRuntime& tooltip_runtime();

extern "C" OpaqueWord PKG_UTFWIN_CORE_THISCALL re_00575ea0(WindowCore*);
extern "C" std::uint8_t PKG_UTFWIN_CORE_THISCALL re_00801ac0(
    CursorManager*, ResourceFactory*, DropIconObject**, OpaqueWord, OpaqueWord);
extern "C" void* PKG_UTFWIN_CORE_THISCALL re_00835380(TooltipCore*, OpaqueWord);
extern "C" void* PKG_UTFWIN_CORE_STDCALL re_00951220(OpaqueWord, OpaqueWord,
                                                     OpaqueWord, OpaqueWord,
                                                     OpaqueWord);
extern "C" void* PKG_UTFWIN_CORE_STDCALL re_00951230(OpaqueWord, OpaqueWord,
                                                     OpaqueWord);
extern "C" void* PKG_UTFWIN_CORE_THISCALL re_00957510(ImageCore*, OpaqueWord);
extern "C" void* PKG_UTFWIN_CORE_THISCALL re_0095f960(WindowCore*, OpaqueWord);
extern "C" std::int32_t PKG_UTFWIN_CORE_THISCALL re_0095f990(WindowCore*);
extern "C" std::int32_t PKG_UTFWIN_CORE_THISCALL re_0095f9a0(WindowCore*);
extern "C" Drawable* PKG_UTFWIN_CORE_THISCALL re_00960050(WindowCore*,
                                                          Drawable*);

static_assert(sizeof(void*) == 4, "UTFWin core pointers are 32-bit");
static_assert(offsetof(WindowCore, ref_count_28) == 0x28,
              "UTFWin reference count offset");
static_assert(offsetof(WindowCore, cursor_id_a4) == 0xa4,
              "UTFWin cursor identifier offset");
static_assert(offsetof(WindowCore, drawable_1e4) == 0x1e4,
              "UTFWin drawable offset");
static_assert(offsetof(WindowVTable, destroy_08) == 0x08,
              "UTFWin destructor slot");
static_assert(offsetof(WindowVTable, get_drawable_90) == 0x90,
              "UTFWin drawable slot");
static_assert(offsetof(CursorManagerVTable, dispatch_24) == 0x24,
              "UTFWin cursor dispatch slot");
static_assert(offsetof(ResourceFactoryVTable, read_10) == 0x10,
              "UTFWin resource read slot");
static_assert(offsetof(TooltipCore, field_08) == 0x08,
              "UTFWin tooltip field offset");
static_assert(sizeof(TooltipCore) == 0x68, "UTFWin tooltip object size");
static_assert(sizeof(DropIconObject) == 0x18, "UTFWin drop icon object size");

}
