#include "space_player_cache.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg12_space {

SpacePlayerCache* g_simulator_space_player_data = nullptr;
const EmpireLookup* g_simulator_empire_lookup = nullptr;

namespace {

std::int32_t read_empire_identity(const Empire* empire) {
  std::int32_t identity = 0;
  std::memcpy(&identity, reinterpret_cast<const std::uint8_t*>(empire) + 0x84u,
              sizeof(identity));
  return identity;
}

}

Empire* refresh_player_empire_staged(SpacePlayerCache& cache,
                                     const EmpireLookup& lookup) {
  const StagedIdWord staged_id{cache.empire_id};
  if (staged_id.value == kInvalidEmpireId) {
    return nullptr;
  }

  Empire* old_empire = cache.cached_empire;
  if (old_empire == nullptr ||
      read_empire_identity(old_empire) != staged_id.value) {
    void* root = lookup.root(staged_id);
    Empire* new_empire = lookup.find(root, staged_id);
    if (new_empire != old_empire) {
      if (new_empire != nullptr) {
        new_empire->add_ref(new_empire);
      }
      cache.cached_empire = new_empire;
      if (old_empire != nullptr) {
        old_empire->release(old_empire);
      }
    }
  }

  return cache.cached_empire;
}

Empire* pkg12_space_01021300() {
  return refresh_player_empire_staged(*g_simulator_space_player_data,
                                      *g_simulator_empire_lookup);
}

}
