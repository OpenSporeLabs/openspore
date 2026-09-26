#include "civ_wave3.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG13_C4_THISCALL __thiscall
#else
#define PKG13_C4_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg13_c4_civ_wave3 {

CityBuildingUpdatePorts g_city_update_ports{};
CultureWave3Ports g_culture_wave3_ports{};

namespace {

constexpr std::uint32_t kCommonType = 0x018ea1ebu;
constexpr std::uint32_t kAlternativeCommonType = 0x018eb106u;
constexpr std::uint32_t kPositiveType = 0x01a56abau;
constexpr std::uint32_t kNegativeType = 0x018ea2ccu;
constexpr std::uint32_t kCandidateArg1 = 0x00cd7d10u;
constexpr std::uint32_t kCandidateArg2 = 0x00d3d420u;
constexpr std::uint32_t kCandidateArg3 = 0x00ae5ea0u;
constexpr std::uint32_t kCandidateArg4 = 0x00b1e500u;
constexpr std::uint32_t kCandidateArg5 = 0x0403df5cu;

void* offset(void* base, std::size_t distance) {
  return static_cast<std::uint8_t*>(base) + distance;
}

const void* offset(const void* base, std::size_t distance) {
  return static_cast<const std::uint8_t*>(base) + distance;
}

std::uint32_t load_u32(const void* base, std::size_t distance) {
  std::uint32_t value = 0;
  std::memcpy(&value, offset(base, distance), sizeof(value));
  return value;
}

std::int32_t load_i32(const void* base, std::size_t distance) {
  std::int32_t value = 0;
  std::memcpy(&value, offset(base, distance), sizeof(value));
  return value;
}

std::uint8_t load_u8(const void* base, std::size_t distance) {
  return *static_cast<const std::uint8_t*>(offset(base, distance));
}

void store_u32(void* base, std::size_t distance, std::uint32_t value) {
  std::memcpy(offset(base, distance), &value, sizeof(value));
}

void store_i32(void* base, std::size_t distance, std::int32_t value) {
  std::memcpy(offset(base, distance), &value, sizeof(value));
}

void store_u8(void* base, std::size_t distance, std::uint8_t value) {
  *static_cast<std::uint8_t*>(offset(base, distance)) = value;
}

void store_f32(void* base, std::size_t distance, float value) {
  std::memcpy(offset(base, distance), &value, sizeof(value));
}

template <typename T>
T* load_pointer(std::uint32_t address) {
  return reinterpret_cast<T*>(static_cast<std::uintptr_t>(load_u32(
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(address)), 0)));
}

std::uint32_t pointer_word(const void* pointer) {
  return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(pointer));
}

CultureIntrusivePtr load_culture_pointer(const void* base,
                                         std::size_t distance) {
  return CultureIntrusivePtr{reinterpret_cast<OpaqueCultureCandidate*>(
      static_cast<std::uintptr_t>(load_u32(base, distance)))};
}

void store_culture_pointer(void* base, std::size_t distance,
                           OpaqueCultureCandidate* pointer) {
  store_u32(base, distance, pointer_word(pointer));
}

OpaqueCultureSelection* selection_context(OpaqueCultureSelection* selection) {
  return reinterpret_cast<OpaqueCultureSelection*>(
      reinterpret_cast<std::uint8_t*>(selection) + 0x1c8);
}

CultureCandidateVtable* culture_vtable(OpaqueCultureCandidate* candidate) {
  return *reinterpret_cast<CultureCandidateVtable**>(candidate->bytes.data());
}

OpaqueCultureCandidate* culture_candidate_receiver(
    OpaqueCultureCandidate* candidate) {
  return reinterpret_cast<OpaqueCultureCandidate*>(
      reinterpret_cast<std::uint8_t*>(candidate) + 0x34);
}

void collect_city_slots(
    OpaqueCity* city, OpaqueCityRoot* root,
    std::array<std::uint32_t, kSlotCount>& types,
    std::array<std::uint8_t, kSlotCount * kSlotCount>& adjacency) {
  if (root == nullptr) {
    return;
  }
  for (std::uint32_t slot = 0; slot < kSlotCount; ++slot) {
    OpaqueCityBuilding* const building = g_city_update_ports.get_city_building(
        reinterpret_cast<OpaqueCity*>(reinterpret_cast<std::uint8_t*>(city) +
                                      0x3ec),
        slot);
    if (building == nullptr) {
      continue;
    }
    OpaqueCityData* const data = g_city_update_ports.get_city_data(building);
    if (data == nullptr) {
      continue;
    }
    OpaqueCityData* const data_receiver = reinterpret_cast<OpaqueCityData*>(
        reinterpret_cast<std::uint8_t*>(data) + 0x120);
    if (g_city_update_ports.get_city_data_state(data_receiver) == 2 ||
        load_i32(data, 0x290) > 0 ||
        g_city_update_ports.city_data_filter(data_receiver)) {
      continue;
    }
    types[slot] = g_city_update_ports.get_city_building_id(data);
    for (std::uint32_t neighbor = 0; neighbor < kSlotCount; ++neighbor) {
      OpaqueCityRoot* const row_root = g_city_update_ports.get_city_root(city);
      if (row_root != nullptr) {
        adjacency[slot * kSlotCount + neighbor] =
            g_city_update_ports.get_city_adjacency(row_root, slot, neighbor);
      }
    }
  }
}

void collect_live_slots(
    OpaqueLiveStateContext* live_state,
    std::array<std::uint32_t, kSlotCount>& types,
    std::array<std::uint8_t, kSlotCount * kSlotCount>& adjacency) {
  for (std::uint32_t index = 0; index < kSlotCount; ++index) {
    OpaqueLiveState* const state =
        g_city_update_ports.get_live_state(live_state, index);
    if (state == nullptr || load_i32(state, 0x20) == 2 ||
        load_i32(state, 0x2c) <= 0) {
      continue;
    }
    const auto slot = static_cast<std::size_t>(load_i32(state, 0x30));
    types[slot] = load_u32(state, 0x34);
    for (std::uint32_t neighbor = 0; neighbor < kSlotCount; ++neighbor) {
      adjacency[slot * kSlotCount + neighbor] =
          g_city_update_ports.get_live_adjacency(live_state, slot, neighbor);
    }
  }
}

struct SlotEffects {
  std::array<std::int32_t, kSlotCount> positive{};
  std::array<std::int32_t, kSlotCount> negative{};
  std::array<std::int32_t, kSlotCount> adjacency{};
  std::array<std::uint8_t, kSlotCount> active{};
  std::array<std::int32_t, kSlotCount> live{};
  std::int32_t positive_total = 0;
  std::int32_t negative_total = 0;
  std::int32_t adjacency_total = 0;
};

void mark_neighbors(
    SlotEffects& effects, const std::array<std::uint32_t, kSlotCount>& types,
    const std::array<std::uint8_t, kSlotCount * kSlotCount>& adjacency,
    std::size_t current, std::size_t neighbor) {
  if (neighbor == current || types[neighbor] == 0) {
    return;
  }
  const bool adjacent = adjacency[current * kSlotCount + neighbor] != 0;
  if (!adjacent) {
    return;
  }
  if (types[current] == kNegativeType) {
    if (types[neighbor] == kCommonType ||
        types[neighbor] == kAlternativeCommonType) {
      effects.adjacency[current] += 400;
      effects.adjacency_total += 400;
    }
    if (types[neighbor] == kPositiveType) {
      effects.negative[current]++;
      effects.negative_total++;
    }
  }
  if (types[current] == kPositiveType &&
      (types[neighbor] == kCommonType ||
       types[neighbor] == kAlternativeCommonType)) {
    effects.positive[current]++;
    effects.positive_total++;
  }
}

SlotEffects calculate_effects(
    const std::array<std::uint32_t, kSlotCount>& types,
    const std::array<std::uint8_t, kSlotCount * kSlotCount>& adjacency) {
  std::array<std::uint8_t, kSlotCount> active{};
  for (std::size_t slot = 0; slot < kSlotCount; ++slot) {
    if (types[slot] == kCommonType) {
      active[slot] = 1;
    }
  }
  bool changed = false;
  do {
    changed = false;
    for (std::size_t current = 0; current < kSlotCount; ++current) {
      if (types[current] == 0 || active[current] != 0) {
        continue;
      }
      for (std::size_t pair = 0; pair < kSlotCount; pair += 2) {
        for (std::size_t neighbor = pair; neighbor <= pair + 1; ++neighbor) {
          if (neighbor < kSlotCount && types[neighbor] != 0 &&
              active[neighbor] != 0 &&
              adjacency[current * kSlotCount + neighbor] != 0) {
            active[current] = 1;
            changed = true;
          }
        }
      }
    }
  } while (changed);

  SlotEffects effects;
  effects.active = active;
  for (std::size_t current = 0; current < kSlotCount; ++current) {
    if (types[current] == 0 || active[current] == 0) {
      continue;
    }
    if (types[current] == kPositiveType) {
      effects.positive[current]++;
      effects.positive_total++;
    }
    if (types[current] == kNegativeType) {
      effects.negative[current]++;
      effects.negative_total++;
    }
    for (std::size_t pair = 0; pair < kSlotCount; pair += 2) {
      mark_neighbors(effects, types, adjacency, current, pair);
      mark_neighbors(effects, types, adjacency, current, pair + 1);
    }
  }
  return effects;
}

float clamp_effectiveness(SlotEffects effects) {
  float value =
      static_cast<float>(effects.positive_total - effects.negative_total + 5) *
      10.0f;
  if (value <= 0.0f) {
    value = 0.0f;
  }
  if (value >= 100.0f) {
    value = 100.0f;
  }
  return value;
}

void clear_culture(OpaqueCultureSelection* selection,
                   CultureIntrusivePtr old_culture) {
  store_culture_pointer(selection, 0x468, nullptr);
  if (old_culture.ptr != nullptr) {
    culture_vtable(old_culture.ptr)->release(old_culture.ptr);
  }
}

}

extern "C" void city_building_economy_update_00be2440(
    OpaqueCity* city, OpaqueLiveStateContext* live_state,
    std::uint32_t update_word) {
  std::array<std::uint32_t, kSlotCount> types{};
  std::array<std::uint8_t, kSlotCount * kSlotCount> adjacency{};

  if (city != nullptr) {
    OpaqueCityRoot* const root = g_city_update_ports.get_city_root(city);
    if (root == nullptr) {
      return;
    }
    collect_city_slots(city, root, types, adjacency);
  } else {
    if (live_state == nullptr) {
      return;
    }
    collect_live_slots(live_state, types, adjacency);
  }

  const SlotEffects effects = calculate_effects(types, adjacency);
  const float effectiveness = clamp_effectiveness(effects);

  if (city != nullptr) {
    for (std::uint32_t slot = 0; slot < kSlotCount; ++slot) {
      OpaqueCityBuilding* const building =
          g_city_update_ports.get_city_building(
              reinterpret_cast<OpaqueCity*>(
                  reinterpret_cast<std::uint8_t*>(city) + 0x3ec),
              slot);
      if (building == nullptr) {
        continue;
      }
      OpaqueCityData* const data = g_city_update_ports.get_city_data(building);
      if (data == nullptr) {
        continue;
      }
      g_city_update_ports.mark_city_data(data, effects.active[slot]);
      store_u32(data, 0x28c, static_cast<std::uint32_t>(effects.live[slot]));
      store_u32(data, 0x294,
                static_cast<std::uint32_t>(effects.adjacency[slot]));
      store_u32(data, 0x298,
                static_cast<std::uint32_t>(effects.positive[slot]));
      store_u32(data, 0x29c,
                static_cast<std::uint32_t>(effects.negative[slot]));
    }
  }

  if (live_state != nullptr) {
    for (std::uint32_t index = 0; index < kSlotCount; ++index) {
      OpaqueLiveState* const state =
          g_city_update_ports.get_live_state(live_state, index);
      if (state == nullptr) {
        continue;
      }
      const auto slot = static_cast<std::size_t>(load_i32(state, 0x30));
      store_u8(state, 0x24, effects.active[slot]);
      store_u32(state, 0x28, static_cast<std::uint32_t>(effects.live[slot]));
    }
  }

  if (city != nullptr) {
    store_f32(city, 0x304, effectiveness);
    store_u32(city, 0x664, static_cast<std::uint32_t>(effects.adjacency_total));
    store_u32(city, 0x668, static_cast<std::uint32_t>(effects.positive_total));
    store_u32(city, 0x66c, static_cast<std::uint32_t>(effects.negative_total));
    store_u32(city, 0x678, static_cast<std::uint32_t>(effects.adjacency_total));
    g_city_update_ports.commit_city(city);
  }

  if (live_state != nullptr) {
    g_city_update_ports.notify_live_state(live_state, effectiveness,
                                          update_word);
    store_i32(live_state, 0x2c, effects.adjacency_total);
  }
}

extern "C" void PKG13_C4_THISCALL
culture_selection_00bf9820(OpaqueCultureSelection* selection) {
  const std::uint32_t city_begin = load_u32(selection, 0x9c);
  const std::uint32_t city_end = load_u32(selection, 0xa0);
  const std::uint32_t city_span = city_end - city_begin;
  if ((city_span & 0xfffffffcu) == 0u) {
    return;
  }

  OpaqueCultureCity* const reference_city =
      load_pointer<OpaqueCultureCity>(city_begin);
  if (reference_city == nullptr) {
    return;
  }

  void* const first_root = g_culture_wave3_ports.current_root();
  OpaqueCulturePlayer* const player =
      g_culture_wave3_ports.current_player(first_root);
  if (player != nullptr) {
    void* const phase_root = g_culture_wave3_ports.current_root();
    void* const phase_owner = g_culture_wave3_ports.phase_source(phase_root);
    if (g_culture_wave3_ports.phase_score(phase_owner) < 1 &&
        g_culture_wave3_ports.current_score(player) <=
            g_culture_wave3_ports.selection_score(selection)) {
      clear_culture(selection, load_culture_pointer(selection, 0x468));
      g_culture_wave3_ports.finish(selection_context(selection));
      return;
    }
  }

  CultureIntrusivePtr old_culture = load_culture_pointer(selection, 0x468);
  if ((old_culture.ptr == nullptr ||
       !g_culture_wave3_ports.candidate_available(old_culture.ptr)) &&
      load_u8(selection, 0x93) == 0u) {
    const std::uint64_t wait =
        g_culture_wave3_ports.selection_wait(selection_context(selection));
    if ((wait >> 32u) == 0u && (wait & 0xffffffffu) <= 0x2710u) {
      return;
    }
  }
  store_u8(selection, 0x93, 0u);

  void* const root = g_culture_wave3_ports.current_root();
  const std::int32_t mode = load_i32(selection, 0x298);
  const CultureCandidateRangeStorage* const candidates =
      g_culture_wave3_ports.enumerate_candidates(
          root, kCandidateArg1, kCandidateArg2, kCandidateArg3, kCandidateArg4,
          kCandidateArg5);
  OpaqueCultureCandidate* selected_culture = nullptr;
  float selected_culture_score = 0.0f;
  for (std::uint32_t cursor = pointer_word(candidates->begin);
       cursor != pointer_word(candidates->end); cursor += sizeof(void*)) {
    OpaqueCultureCandidate* const candidate =
        load_pointer<OpaqueCultureCandidate>(cursor);
    if (candidate == nullptr ||
        g_culture_wave3_ports.candidate_available(candidate)) {
      continue;
    }
    bool passes = false;
    if (mode >= 1) {
      const CultureVectorResult* const candidate_result =
          g_culture_wave3_ports.candidate_result(
              culture_candidate_receiver(candidate), 0xffffffffu, 0u, false);
      void* const input_manager = g_culture_wave3_ports.input_manager();
      const std::uint16_t normalized_result =
          g_culture_wave3_ports.vector_result(input_manager, candidate_result);
      passes = g_culture_wave3_ports.candidate_primary(
          selection, candidate_result, normalized_result);
    }
    if (!passes && mode >= 2) {
      const CultureVectorResult* const candidate_result =
          g_culture_wave3_ports.candidate_result(
              culture_candidate_receiver(candidate), 0xffffffffu, 0u, false);
      passes = g_culture_wave3_ports.candidate_secondary(
          selection, candidate_result, 0xffffffffu);
    }
    if (!passes) {
      continue;
    }

    const CultureCityRangeStorage* const cities =
        g_culture_wave3_ports.enumerate_cities(root);
    std::uint32_t matching_cities = 0;
    for (std::uint32_t city_cursor = pointer_word(cities->begin);
         city_cursor != pointer_word(cities->end);
         city_cursor += sizeof(void*)) {
      OpaqueCultureCity* const city =
          load_pointer<OpaqueCultureCity>(city_cursor);
      if (city == nullptr ||
          g_culture_wave3_ports.city_is_self(city, selection)) {
        continue;
      }
      if (load_culture_pointer(city, 0x468).ptr != candidate) {
        continue;
      }
      matching_cities += load_u8(city, 0x8a) == 0u ? 2u : 1u;
    }
    if (matching_cities >= 3u) {
      continue;
    }
    const std::uint32_t multiplier = candidate == old_culture.ptr ? 200u : 100u;
    const float score = g_culture_wave3_ports.candidate_score(
        selection, reference_city, candidate, multiplier, matching_cities);
    if (selected_culture_score < score) {
      selected_culture = candidate;
      selected_culture_score = score;
    }
  }

  if (selected_culture != nullptr) {
    OpaqueCultureCity* selected_city = nullptr;
    float selected_city_score = 0.0f;
    const std::int32_t city_count =
        static_cast<std::int32_t>(city_end - city_begin) >> 2;
    for (std::int32_t index = 0; index < city_count; ++index) {
      OpaqueCultureCity* const city = load_pointer<OpaqueCultureCity>(
          city_begin + static_cast<std::uint32_t>(index * 4));
      if (city == nullptr) {
        continue;
      }
      bool matches = false;
      if (mode >= 1) {
        matches = g_culture_wave3_ports.city_matches_current(selection, city,
                                                             selected_culture);
      }
      if (!matches && mode >= 2) {
        matches = g_culture_wave3_ports.city_matches_position(selection, city,
                                                              selected_culture);
      }
      if (!matches) {
        continue;
      }
      const float score =
          g_culture_wave3_ports.city_score(selection, city, selected_culture);
      if (selected_city_score < score) {
        selected_city = city;
        selected_city_score = score;
      }
    }

    if (selected_city != nullptr) {
      std::int32_t switch_mode = 0;
      bool final_match = false;
      if (mode >= 2 && g_culture_wave3_ports.city_matches_position(
                           selection, selected_city, selected_culture)) {
        final_match = true;
        switch_mode = 1;
      } else {
        final_match =
            mode >= 1 && g_culture_wave3_ports.city_matches_current(
                             selection, selected_city, selected_culture);
      }
      if (final_match) {
        const CultureVectorResult* const candidate_result =
            g_culture_wave3_ports.candidate_result(
                culture_candidate_receiver(selected_culture), 0u,
                static_cast<std::uint32_t>(switch_mode), true);
        void* const input_manager = g_culture_wave3_ports.input_manager();
        const std::uint16_t normalized_result =
            g_culture_wave3_ports.vector_result(input_manager,
                                                candidate_result);
        const std::uint32_t city_result =
            g_culture_wave3_ports.city_context(selected_city);
        g_culture_wave3_ports.try_commit(selection, 0u, candidate_result,
                                         normalized_result, city_result);
      }
    }
  }

  CultureIntrusivePtr const previous = load_culture_pointer(selection, 0x468);
  if (previous.ptr != selected_culture) {
    if (selected_culture != nullptr) {
      culture_vtable(selected_culture)->add_ref(selected_culture);
    }
    store_culture_pointer(selection, 0x468, selected_culture);
    if (previous.ptr != nullptr) {
      culture_vtable(previous.ptr)->release(previous.ptr);
    }
  }
  g_culture_wave3_ports.finish(selection_context(selection));
}

}

#undef PKG13_C4_THISCALL
