#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-app-lifecycle-wave8 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __thiscall
#define PKG_APP_LIFECYCLE_WAVE8_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_APP_LIFECYCLE_WAVE8_THISCALL __attribute__((thiscall))
#define PKG_APP_LIFECYCLE_WAVE8_CDECL __attribute__((cdecl))
#else
#error "pkg-app-lifecycle-wave8 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_app_lifecycle_wave8 {

using OpaqueWord = std::uint32_t;

struct OpaqueAppEvent;
struct OpaqueService;
struct OpaqueAppSystem;
struct OpaqueCellModeStrategy;

struct alignas(4) OpaqueCellGame {
  std::uint8_t opaque_000[0x4121]{};
  std::uint8_t flag_4121;
  std::uint8_t opaque_4122[0x107a]{};
  OpaqueWord range_begin_519c;
  OpaqueWord range_end_51a0;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaqueCellGame, flag_4121) == 0x4121,
              "cell game flag offset");
static_assert(offsetof(OpaqueCellGame, range_begin_519c) == 0x519c,
              "cell game range offset");
static_assert(offsetof(OpaqueCellGame, range_end_51a0) == 0x51a0,
              "cell game range end offset");
static_assert(sizeof(OpaqueCellGame) == 0x51a4, "cell game prefix size");

struct OpaqueCellGfx {
  std::uint8_t opaque_00[0x40]{};
};

struct alignas(4) OpaqueCellUi {
  std::uint8_t opaque_00[1]{};
};

struct alignas(4) OpaqueCellModeStrategy {
  std::uint8_t opaque_00[8]{};
};

static_assert(sizeof(OpaqueCellGfx) == 0x40, "cell gfx prefix size");
static_assert(sizeof(OpaqueCellModeStrategy) == 8, "mode prefix size");

struct OpaqueServiceVtable {
  std::uintptr_t slot_words_00[34]{};
  void(PKG_APP_LIFECYCLE_WAVE8_THISCALL* operation_88)(OpaqueService*,
                                                       OpaqueWord, OpaqueWord,
                                                       OpaqueWord);
  std::uintptr_t slot_words_8c[3]{};
  void(PKG_APP_LIFECYCLE_WAVE8_THISCALL* operation_98)(OpaqueService*,
                                                       OpaqueWord, OpaqueWord);
};

static_assert(offsetof(OpaqueServiceVtable, operation_88) == 0x88,
              "service vtable operation offset");
static_assert(offsetof(OpaqueServiceVtable, operation_98) == 0x98,
              "service vtable operation offset");

struct OpaqueService {
  OpaqueServiceVtable* vtable;
};

struct OpaqueAppSystemVtable {
  std::uintptr_t slot_words_00[11]{};
  void(PKG_APP_LIFECYCLE_WAVE8_THISCALL* operation_2c)(OpaqueAppSystem*, void*,
                                                       OpaqueWord,
                                                       std::int32_t);
  void(PKG_APP_LIFECYCLE_WAVE8_THISCALL* operation_30)(OpaqueAppSystem*,
                                                       OpaqueAppEvent*,
                                                       OpaqueWord,
                                                       std::int32_t);
};

static_assert(offsetof(OpaqueAppSystemVtable, operation_2c) == 0x2c,
              "app system vtable operation offset");
static_assert(offsetof(OpaqueAppSystemVtable, operation_30) == 0x30,
              "app system vtable operation offset");

struct OpaqueAppSystem {
  OpaqueAppSystemVtable* vtable;
};

using DisposeNoArg = void(PKG_APP_LIFECYCLE_WAVE8_CDECL*)();
using DisposeRangeBuild = OpaqueWord(PKG_APP_LIFECYCLE_WAVE8_CDECL*)(
    OpaqueWord, OpaqueWord, OpaqueWord);
using DisposeRangeStore = void(PKG_APP_LIFECYCLE_WAVE8_THISCALL*)(OpaqueWord*,
                                                                  OpaqueWord,
                                                                  OpaqueWord);
using DisposePointer = void(PKG_APP_LIFECYCLE_WAVE8_CDECL*)(void*);
using DisposeGameDestructor =
    void(PKG_APP_LIFECYCLE_WAVE8_THISCALL*)(OpaqueCellGame*);
using DisposeGfxDestructor =
    void(PKG_APP_LIFECYCLE_WAVE8_THISCALL*)(OpaqueCellGfx*);
using DisposeUiDestructor =
    void(PKG_APP_LIFECYCLE_WAVE8_THISCALL*)(OpaqueCellUi*);
using DisposeServiceGet = OpaqueService*(PKG_APP_LIFECYCLE_WAVE8_CDECL*)();
using DisposeAppSystemGet = OpaqueAppSystem*(PKG_APP_LIFECYCLE_WAVE8_CDECL*)();

struct DisposePorts {
  DisposeNoArg conditional_cleanup = nullptr;
  DisposeRangeBuild range_build = nullptr;
  DisposeRangeStore range_store = nullptr;
  DisposeNoArg reset_first = nullptr;
  DisposeNoArg reset_second = nullptr;
  DisposePointer gfx_world_cleanup = nullptr;
  DisposeServiceGet service_get = nullptr;
  DisposeAppSystemGet app_system_get = nullptr;
  DisposeGameDestructor game_destructor = nullptr;
  DisposeGfxDestructor gfx_destructor = nullptr;
  DisposeUiDestructor ui_destructor = nullptr;
  DisposePointer free_memory = nullptr;
};

struct DisposeGlobals {
  OpaqueCellGame* cell_game = nullptr;
  OpaqueCellGfx* cell_gfx = nullptr;
  OpaqueCellUi* cell_ui = nullptr;
  OpaqueWord source_snapshot[8]{};
  OpaqueWord destination[8]{};
};

extern DisposePorts g_app_lifecycle_wave8_ports;
extern DisposeGlobals g_app_lifecycle_wave8_globals;

extern "C" bool PKG_APP_LIFECYCLE_WAVE8_THISCALL
app_cCellModeStrategy_Dispose_00e81f30(OpaqueCellModeStrategy* strategy);

}

#undef PKG_APP_LIFECYCLE_WAVE8_CDECL
#undef PKG_APP_LIFECYCLE_WAVE8_THISCALL
