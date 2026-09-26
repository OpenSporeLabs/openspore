#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-orchestrate-dogfood-00b72370 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL __attribute__((cdecl))
#else
#error "pkg-orchestrate-dogfood-00b72370 requires MSVC or GCC CCs"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_00b72370 {

using OpaqueWord = std::uint32_t;

struct OpaqueDispatchTarget;

struct OpaqueDispatchTargetVtable;

// The only direct callee of the target body: 0x00883860, which the live
// decompilation renders as `undefined4 FUN_00883860(void) { return
// DAT_016514cc; }`. The call site pushes no argument and consumes EAX as an
// object pointer, so the port stays a bare cdecl accessor.
using OpaqueDispatchTargetGet00883860 =
    OpaqueDispatchTarget*(PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL*)();

// 0x00b723aa-0x00b723b3 loads the target vtable pointer, reads the slot word
// at displacement 0x24, pushes the source-table word and then the
// receiver-minus-four word, sets ECX to the target and calls the loaded slot.
// Callee-visible stack order is stack slot 0 = receiver-minus-four word and
// stack slot 1 = source-table word; the callee reclaims both words because the
// loop advances without any stack adjustment.
using OpaqueDispatchTargetOperation24 =
    void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(OpaqueDispatchTarget*,
                                                     OpaqueWord, OpaqueWord);

struct alignas(4) OpaqueDispatchTargetVtable {
  std::uintptr_t slots_00[9]{};
  OpaqueDispatchTargetOperation24 operation_24;
};

// Only offset +0x00 of the dispatch target is observed: the body reads
// dword ptr [EDI] and then dword ptr [EAX+0x24]. No other field is claimed.
struct alignas(4) OpaqueDispatchTarget {
  OpaqueDispatchTargetVtable* vtable;
};

// Receiver of the target function. The body writes offsets 0x20 through 0x30
// and reads no other receiver field; the prefix stays opaque. The trailing
// extent 0x34 is a modeling bound, not a recovered allocation size.
struct alignas(4) OpaqueObjectPoolReceiver {
  std::uint8_t opaque_00[0x20]{};
  OpaqueWord dispatch_target_20;
  OpaqueWord receiver_minus_four_24;
  OpaqueWord table_base_28;
  OpaqueWord table_word_count_2c;
  OpaqueWord zero_word_30;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(offsetof(OpaqueDispatchTargetVtable, operation_24) == 0x24,
              "dispatch vtable operation slot offset");
static_assert(sizeof(OpaqueDispatchTargetVtable) == 0x28,
              "dispatch vtable modeled window extent");
static_assert(offsetof(OpaqueDispatchTarget, vtable) == 0x00,
              "dispatch target vtable pointer offset");
static_assert(sizeof(OpaqueDispatchTarget) == 4,
              "dispatch target header extent");
static_assert(offsetof(OpaqueObjectPoolReceiver, dispatch_target_20) == 0x20,
              "receiver dispatch target offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, receiver_minus_four_24) ==
                  0x24,
              "receiver minus four offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, table_base_28) == 0x28,
              "receiver table base offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, table_word_count_2c) == 0x2c,
              "receiver table word count offset");
static_assert(offsetof(OpaqueObjectPoolReceiver, zero_word_30) == 0x30,
              "receiver zero word offset");
static_assert(sizeof(OpaqueDispatchTargetOperation24) == 4,
              "dispatch operation slot width");
static_assert(sizeof(OpaqueDispatchTargetGet00883860) == 4,
              "dispatch accessor port width");
static_assert(
    std::is_same<OpaqueDispatchTargetOperation24,
                 void(PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL*)(
                     OpaqueDispatchTarget*, OpaqueWord, OpaqueWord)>::value,
    "dispatch operation carries the receiver plus two stack words");
static_assert(
    std::is_same<OpaqueDispatchTargetGet00883860,
                 OpaqueDispatchTarget*(
                     PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL*)()>::value,
    "dispatch accessor stays a bare cdecl accessor with no argument "
    "word");

struct DeleteObjectPorts {
  OpaqueDispatchTargetGet00883860 acquire_dispatch_target_00883860 = nullptr;
};

// The loop reads 0x20 bytes from 0x01465004, that is eight 32-bit words.
struct DeleteObjectGlobals {
  OpaqueWord word_01465004[8]{};
};

static_assert(sizeof(DeleteObjectGlobals) == 0x20,
              "modeled source table window extent");

extern DeleteObjectPorts g_dogfood_00b72370_ports;
extern DeleteObjectGlobals g_dogfood_00b72370_globals;

extern "C" void PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
simulator_c_object_pool_delete_object_00b72370(OpaqueObjectPoolReceiver* pool);

}

#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_00B72370_THISCALL
