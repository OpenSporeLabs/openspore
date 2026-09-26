#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-11-H3 helper wave 2 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg11_h3_helper_wave2 {

struct OpaqueNoun;

using NounAddRef = void(__attribute__((thiscall)) *)(OpaqueNoun*);
using NounRelease = void(__attribute__((thiscall)) *)(OpaqueNoun*);

struct OpaqueNounVtable {
  NounAddRef add_ref;
  NounRelease release;
};

struct OpaqueNoun {
  OpaqueNounVtable* vtable;
  std::uint8_t opaque_04[0x1c];
  std::uint8_t destruction_pending;
};

struct PendingVectorWire {
  OpaqueNoun** begin;
  OpaqueNoun** end;
  OpaqueNoun** capacity;
};

struct OpaqueNounManager {
  std::uint8_t opaque_00[0x80];
  PendingVectorWire pending;
};

struct OpaqueEmbeddedObject {
  std::uint32_t first_word;
  std::uint32_t trailing_words[3];
};

struct StrategyBaseWrite {
  std::uint8_t offset;
  std::uint32_t value;
};

inline bool operator==(const StrategyBaseWrite& left,
                       const StrategyBaseWrite& right) {
  return left.offset == right.offset && left.value == right.value;
}

struct OpaqueStrategyBaseWire {
  std::uint32_t word_00;
  std::uint32_t word_04;
  std::uint32_t word_08;
  std::uint32_t word_0c;
  std::uint32_t word_10;
  std::uint32_t word_14;
  std::uint32_t word_18;
};

struct PendingGrowthPorts {
  OpaqueNoun** (*allocate)(std::size_t bytes);
  void (*deallocate)(OpaqueNoun** entries);
};

inline constexpr std::uint32_t kPurecallVtable_013ef094 = 0x013ef094U;
inline constexpr std::uint32_t kPrimaryVtable_01461580 = 0x01461580U;
inline constexpr std::uint32_t kSecondaryVtable_01461578 = 0x01461578U;
inline constexpr std::uint32_t kDisabledSentinel = 0xffffffffU;

inline constexpr std::array<StrategyBaseWrite, 8> kStrategyBaseWrites_00b5b960 =
    {{
        {0x04, kPurecallVtable_013ef094},
        {0x08, 0U},
        {0x00, kPrimaryVtable_01461580},
        {0x04, kSecondaryVtable_01461578},
        {0x0c, kDisabledSentinel},
        {0x10, kDisabledSentinel},
        {0x14, kDisabledSentinel},
        {0x18, 0U},
    }};

extern "C" PendingGrowthPorts g_pending_growth_ports_00aea5d0;

using NounManagerBridgeAbi =
    void(__attribute__((thiscall)) *)(OpaqueNounManager*, OpaqueNoun*);
using EmbeddedInitializerAbi =
    void(__attribute__((fastcall)) *)(OpaqueEmbeddedObject*);
using StrategyBaseConstructorAbi =
    void(__attribute__((fastcall)) *)(OpaqueStrategyBaseWire*);

extern "C" void __attribute__((thiscall)) noun_manager_logical_destroy_00b225d0(
    OpaqueNounManager* manager, OpaqueNoun* noun);
extern "C" void __attribute__((thiscall)) pending_vector_insert_00aea5d0(
    PendingVectorWire* pending, OpaqueNoun** position, OpaqueNoun** source);
extern "C" void __attribute__((thiscall)) noun_manager_teardown_00b20d30(
    OpaqueNounManager* manager, OpaqueNoun* noun);
extern "C" void __attribute__((thiscall)) noun_manager_dependencies_00b201a0(
    OpaqueNounManager* manager, OpaqueNoun* noun);
extern "C" void __attribute__((fastcall))
embedded_object_first_word_init_00743b50(OpaqueEmbeddedObject* receiver);
extern "C" void __attribute__((fastcall)) strategy_base_constructor_00b5b960(
    OpaqueStrategyBaseWire* receiver);

static_assert(sizeof(void*) == 4, "PKG-11-H3 target pointers are 32-bit");
static_assert(sizeof(OpaqueNounVtable) == 8, "noun vtable access window");
static_assert(offsetof(OpaqueNoun, destruction_pending) == 0x20,
              "noun pending flag offset");
static_assert(sizeof(OpaqueNoun) >= 0x21, "noun modeled access extent");
static_assert(offsetof(OpaqueNounManager, pending) == 0x80,
              "noun manager pending vector offset");
static_assert(sizeof(PendingVectorWire) == 12, "pending vector wire size");
static_assert(sizeof(OpaqueEmbeddedObject) == 16,
              "embedded initializer test object size");
static_assert(sizeof(OpaqueStrategyBaseWire) == 0x1c,
              "strategy constructor write extent");
static_assert(std::is_same_v<decltype(&noun_manager_logical_destroy_00b225d0),
                             NounManagerBridgeAbi>,
              "noun manager bridge ABI");
static_assert(
    std::is_same_v<decltype(&embedded_object_first_word_init_00743b50),
                   EmbeddedInitializerAbi>,
    "embedded initializer ABI");
static_assert(std::is_same_v<decltype(&strategy_base_constructor_00b5b960),
                             StrategyBaseConstructorAbi>,
              "strategy base constructor ABI");

}
