#include "ResourceKey.hpp"

namespace openspore::assets {

bool operator==(const ResourceKey& lhs, const ResourceKey& rhs) noexcept {
  return lhs.type == rhs.type && lhs.group == rhs.group &&
         lhs.instance == rhs.instance;
}

bool operator!=(const ResourceKey& lhs, const ResourceKey& rhs) noexcept {
  return !(lhs == rhs);
}

bool operator<(const ResourceKey& lhs, const ResourceKey& rhs) noexcept {
  return std::tie(lhs.type, lhs.group, lhs.instance) <
         std::tie(rhs.type, rhs.group, rhs.instance);
}

}  // namespace openspore::assets
