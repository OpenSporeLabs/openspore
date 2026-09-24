#pragma once

#include <cstdint>
#include <tuple>

namespace openspore::assets {

struct ResourceKey {
  uint32_t type = 0;
  uint32_t group = 0;
  uint32_t instance = 0;

  constexpr bool isComplete() const {
    return type != kWildcard && group != kWildcard && instance != kWildcard;
  }

  static constexpr uint32_t kWildcard = 0xFFFFFFFFu;
};

bool operator==(const ResourceKey& lhs, const ResourceKey& rhs) noexcept;
bool operator!=(const ResourceKey& lhs, const ResourceKey& rhs) noexcept;
bool operator<(const ResourceKey& lhs, const ResourceKey& rhs) noexcept;

}  // namespace openspore::assets
