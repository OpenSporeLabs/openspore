#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG13-C2 tribe civilization staging requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg13_c2_tribe_civilization {

#if defined(_MSC_VER)
#define PKG13_C2_THISCALL __thiscall
#else
#define PKG13_C2_THISCALL __attribute__((thiscall))
#endif

struct NounProjection;
struct NounObject;

struct NounProjectionVector;
struct NounListNode {
  std::uint8_t prefix[0x0c];
  NounListNode* next_link;
};

using NounCreateCallback = NounProjectionVector* (*)();
using NounClearCallback = void (*)(NounProjectionVector*);
using NounAddCallback = void (*)(NounProjectionVector*, NounListNode*);
using NounFilterCallback = std::uint8_t (*)(NounListNode*, std::uint32_t);

struct NounProjectionVector {
  std::uint8_t needs_update;
  std::uint8_t padding[3];
  NounObject** begin;
  NounObject** end;
  NounObject** capacity;
  std::int32_t garbage;
  void* allocator;
};

using NounIdentityProbe = std::uint32_t(PKG13_C2_THISCALL*)(NounObject*);

struct NounObjectVtable {
  void* slots[19];
  NounIdentityProbe identity;
};

struct NounObject {
  NounObjectVtable* vtable;
  std::uint8_t opaque[0x4c];
};

struct CurrentPlayerStateAccessWindow {
  std::uint8_t opaque[0x84];
  std::uint32_t identity;
  std::uint8_t trailing[4];
};

using CurrentPlayerPort = CurrentPlayerStateAccessWindow* (*)();
using NounProjectionLookupPort = NounProjectionVector*(
    PKG13_C2_THISCALL*)(NounProjection*, std::uint32_t, std::uint32_t,
                        std::uint32_t, std::uint32_t, std::uint32_t);

struct NativePorts {
  CurrentPlayerPort current_player;
  NounProjectionLookupPort noun_projection_lookup;
};

extern NativePorts g_native_ports;

static_assert(sizeof(void*) == 4, "PKG13-C2 pointers are 32-bit");
static_assert(sizeof(NounProjectionVector) == 0x18,
              "PKG13-C2 noun projection vector size");
static_assert(offsetof(NounProjectionVector, begin) == 0x04,
              "PKG13-C2 noun vector begin offset");
static_assert(offsetof(NounProjectionVector, end) == 0x08,
              "PKG13-C2 noun vector end offset");
static_assert(offsetof(NounProjectionVector, capacity) == 0x0c,
              "PKG13-C2 noun vector capacity offset");
static_assert(offsetof(NounObjectVtable, identity) == 0x4c,
              "PKG13-C2 identity vtable slot offset");
static_assert(offsetof(CurrentPlayerStateAccessWindow, identity) == 0x84,
              "PKG13-C2 current-player identity offset");
static_assert(sizeof(CurrentPlayerPort) == 4,
              "PKG13-C2 current-player port width");
static_assert(sizeof(NounProjectionLookupPort) == 4,
              "PKG13-C2 projection port width");

extern "C" NounObject* PKG13_C2_THISCALL
tribe_civilization_bridge_00b25fb0(NounProjection* receiver);

extern "C" NounObject* PKG13_C2_THISCALL tribe_civilization_resolver_00b25f40(
    NounProjection* receiver, std::uint32_t identity);

}

#undef PKG13_C2_THISCALL
