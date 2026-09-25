#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-12 Space communication lifecycle requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg12_space {

struct cCommEvent {
  std::uint8_t opaque[0xa0];
};

struct cCommManager;

struct cCommVector {
  std::uintptr_t begin;
  std::uintptr_t end;
  std::uintptr_t capacity;
};

struct cCommStringRange {
  std::uintptr_t begin;
  std::uintptr_t end;
};

using OpaqueWord = std::uintptr_t;

extern "C" void __attribute__((fastcall)) pkg12_re_00aea250(cCommEvent* self);

extern "C" void __thiscall pkg12_re_00aea5d0(cCommVector* vector,
                                             cCommEvent** position,
                                             cCommEvent** value);

extern "C" void* __thiscall pkg12_re_00aea230(cCommManager* manager,
                                              cCommStringRange* range);

extern "C" cCommEvent* __thiscall pkg12_re_00aeb160(
    cCommManager* manager, OpaqueWord payload0, OpaqueWord payload1,
    OpaqueWord payload2, OpaqueWord payload3, OpaqueWord payload4,
    OpaqueWord payload5, OpaqueWord payload6);

extern "C" OpaqueWord __cdecl pkg12_re_00f473a0(
    std::size_t size, const char* domain, OpaqueWord value0, OpaqueWord value1,
    const char* source, OpaqueWord value2);

extern "C" void __cdecl pkg12_re_00f47380(OpaqueWord pointer);

extern "C" cCommEvent** __cdecl pkg12_re_00ac97a0(cCommEvent** position,
                                                  cCommEvent** source,
                                                  cCommEvent** end);

extern "C" void* __cdecl pkg12_re_011e0744(void* destination,
                                           const void* source,
                                           std::size_t size);

extern "C" void* __thiscall pkg12_re_00454cb0(void* target, OpaqueWord begin,
                                              OpaqueWord end);

extern "C" void __thiscall pkg12_re_event_add_ref(cCommEvent* event);

extern "C" void __thiscall pkg12_re_event_release(cCommEvent* event);

}

static_assert(sizeof(openspore::reconstruction::pkg12_space::cCommEvent) ==
                  0xa0,
              "cCommEvent must remain a separate 0xa0-byte event family");
