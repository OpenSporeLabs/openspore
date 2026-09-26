#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11-A4 progression wave3 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-11-A4 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG-11-A4 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG11_A4_THISCALL __thiscall
#else
#define PKG11_A4_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg11_a4_progression_wave3 {

using Word = std::uint32_t;
using Opaque = std::uint32_t;

inline constexpr std::size_t kDefaultEligibilityOffset = 0x000cU;
inline constexpr std::size_t kConfiguredContainerOffset = 0x148cU;
inline constexpr std::size_t kStatusContainerOffset = 0x4d00U;
inline constexpr std::size_t kPointsOffset = 0x6d70U;
inline constexpr std::size_t kUnlockedListOffset = 0x6d80U;
inline constexpr std::uint8_t kUnlockedMask = 0x01U;
inline constexpr std::uint8_t kNotUnlockableMask = 0x04U;
inline constexpr std::uint8_t kUnlockStateMask = 0x03U;
inline constexpr std::uint8_t kUnlockStateClearMask = 0xfcU;

struct OpaqueKey {
  Word instance_id;
  Word group_id;
};

struct ProgressionManagerWire {
  std::uint8_t storage[0x6dac]{};
};

struct ProgressionPorts {
  using FindStatus = bool(PKG11_A4_THISCALL*)(Opaque container,
                                              const OpaqueKey* key,
                                              std::uint8_t* status);
  using FindConfigured = bool(PKG11_A4_THISCALL*)(Opaque container,
                                                  const OpaqueKey* key);
  using StatusOperatorBracket =
      std::uint8_t*(PKG11_A4_THISCALL*)(Opaque container, const OpaqueKey* key);
  using AppendUnlocked = void(PKG11_A4_THISCALL*)(Opaque container,
                                                  const OpaqueKey* key);
  using RemoveUnlocked = void(PKG11_A4_THISCALL*)(Opaque container,
                                                  const OpaqueKey* key);

  FindStatus find_status = nullptr;
  FindConfigured find_configured = nullptr;
  StatusOperatorBracket status_operator_bracket = nullptr;
  AppendUnlocked append_unlocked = nullptr;
  RemoveUnlocked remove_unlocked = nullptr;
};

ProgressionPorts& progression_ports();
void set_progression_ports(const ProgressionPorts* ports);

using CollectableUnlockAbi =
    bool(PKG11_A4_THISCALL*)(ProgressionManagerWire* manager, Word instance_id,
                             Word group_id, std::int32_t cost);
using CollectableLockAbi = bool(PKG11_A4_THISCALL*)(
    ProgressionManagerWire* manager, Word instance_id, Word group_id);

bool PKG11_A4_THISCALL
collectable_unlock_00596da0(ProgressionManagerWire* manager, Word instance_id,
                            Word group_id, std::int32_t cost);
bool PKG11_A4_THISCALL collectable_lock_00596e10(
    ProgressionManagerWire* manager, Word instance_id, Word group_id);

#undef PKG11_A4_THISCALL

static_assert(sizeof(OpaqueKey) == 8, "PKG-11-A4 key is two words");
static_assert(offsetof(OpaqueKey, instance_id) == 0,
              "PKG-11-A4 instance ID offset");
static_assert(offsetof(OpaqueKey, group_id) == 4, "PKG-11-A4 group ID offset");
static_assert(sizeof(ProgressionManagerWire) == 0x6dac,
              "PKG-11-A4 progression manager extent");
static_assert(std::is_same<decltype(&collectable_unlock_00596da0),
                           CollectableUnlockAbi>::value,
              "PKG-11-A4 collectable unlock ABI");
static_assert(std::is_same<decltype(&collectable_lock_00596e10),
                           CollectableLockAbi>::value,
              "PKG-11-A4 collectable lock ABI");

}
