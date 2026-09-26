#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-cheat-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_CHEAT_WAVE9_THISCALL __thiscall
#define PKG_CHEAT_WAVE9_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_CHEAT_WAVE9_THISCALL __attribute__((thiscall))
#define PKG_CHEAT_WAVE9_CDECL __attribute__((cdecl))
#else
#error "pkg-cheat-wave9 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_cheat_wave9 {

using OpaqueWord = std::uint32_t;

struct OpaqueManager;

struct OpaqueService;

using CheatManagerForward48 = bool(PKG_CHEAT_WAVE9_THISCALL*)(OpaqueManager*,
                                                              OpaqueWord,
                                                              OpaqueWord,
                                                              OpaqueWord);

struct alignas(4) OpaqueManagerVtable {
  std::uintptr_t slots_00[18]{};
  CheatManagerForward48 forward_48;
};

struct alignas(4) OpaqueManager {
  OpaqueManagerVtable* vtable;
  std::uint8_t opaque_04[0x64]{};
};

using ServiceOperation24 = bool(PKG_CHEAT_WAVE9_THISCALL*)(
    OpaqueService*, OpaqueWord, OpaqueManager*, OpaqueWord, OpaqueWord);

struct alignas(4) OpaqueServiceVtable {
  std::uintptr_t slots_00[9]{};
  ServiceOperation24 operation_24;
};

struct alignas(4) OpaqueService {
  OpaqueServiceVtable* vtable;
};

using OpaqueServiceGet00b3d260 = OpaqueService*(PKG_CHEAT_WAVE9_CDECL*)();

struct OpaquePorts {
  OpaqueServiceGet00b3d260 service_get_00b3d260 = nullptr;
};

extern OpaquePorts g_cheat_wave9_ports;

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueManagerVtable) == 0x4c, "manager vtable extent");
static_assert(offsetof(OpaqueManagerVtable, forward_48) == 0x48,
              "manager forward slot offset");
static_assert(sizeof(OpaqueManager) == 0x68, "manager size");
static_assert(offsetof(OpaqueManager, opaque_04) == 0x04,
              "manager data offset");
static_assert(sizeof(OpaqueServiceVtable) == 0x28, "service vtable extent");
static_assert(offsetof(OpaqueServiceVtable, operation_24) == 0x24,
              "service operation offset");
static_assert(sizeof(OpaqueService) == 4, "service header extent");
static_assert(sizeof(CheatManagerForward48) == 4, "manager forward slot width");
static_assert(sizeof(ServiceOperation24) == 4, "service operation slot width");
static_assert(sizeof(OpaqueServiceGet00b3d260) == 4, "service port width");
static_assert(
    std::is_same<CheatManagerForward48, bool(PKG_CHEAT_WAVE9_THISCALL*)(
                                            OpaqueManager*, OpaqueWord,
                                            OpaqueWord, OpaqueWord)>::value,
    "manager forward signature carries three stack words");
static_assert(std::is_same<ServiceOperation24,
                           bool(PKG_CHEAT_WAVE9_THISCALL*)(
                               OpaqueService*, OpaqueWord, OpaqueManager*,
                               OpaqueWord, OpaqueWord)>::value,
              "service operation carries first, manager, second, third");
static_assert(std::is_same<OpaqueServiceGet00b3d260,
                           OpaqueService*(PKG_CHEAT_WAVE9_CDECL*)()>::value,
              "port stays a bare cdecl accessor without a service word");

extern "C" bool PKG_CHEAT_WAVE9_THISCALL opaque_service_forward_00abf790(
    OpaqueManager*, OpaqueWord, OpaqueWord, OpaqueWord);

}

#undef PKG_CHEAT_WAVE9_CDECL
#undef PKG_CHEAT_WAVE9_THISCALL
