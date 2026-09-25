#include "mission_progression.hpp"

#include <algorithm>
#include <cstring>

namespace openspore::reconstruction::pkg11_a1_mission_progression {
namespace {

void initialize_map(MapWire& map) {
  map.compare = 0;
  map.anchor_left = reinterpret_cast<Word>(&map.anchor_left);
  map.anchor_right = reinterpret_cast<Word>(&map.anchor_left);
  map.anchor_parent = 0;
  map.anchor_color = 0;
  map.size = 0;
  map.allocator = 0;
}

BadgeEvent* find_event(BadgeManagerModel& model, Word key) {
  for (BadgeEvent& event : model.events) {
    if (event.key == key) {
      return &event;
    }
  }
  return nullptr;
}

const MissionStatusNode* find_status(const MissionSelectionState& state,
                                     Word key) {
  for (const MissionStatusNode& node : state.status_nodes) {
    if (node.key == key) {
      return &node;
    }
  }
  return nullptr;
}

}

BadgeManagerWire* badge_manager_construct_00fe4fa0(
    BadgeManagerModel& model, BadgeManagerPorts& ports) {
  if (ports.base_00b5b6c0 != nullptr) {
    ports.base_00b5b6c0(&model);
  }

  model.wire.vtable0 = 0x00149429cU;
  model.wire.refcount = 0;
  model.wire.vtable1 = 0x001494278U;
  model.wire.base_flags[0] = 0;
  model.wire.base_flags[1] = 0;
  model.wire.base_flags[2] = 0;
  model.wire.base_flags[3] = 0;
  initialize_map(model.wire.m_badges);
  initialize_map(model.wire.m_badge_map);
  initialize_map(model.wire.m_stage_map);
  initialize_map(model.wire.m_event_counts);
  std::memset(model.wire.event_state, 0, sizeof(model.wire.event_state));
  model.wire.current_badge_flag = 0;
  std::memset(model.wire.current_badge_padding, 0,
              sizeof(model.wire.current_badge_padding));
  model.wire.current_badge_card = 0;
  model.wire.field_a8 = 0;
  std::memset(model.wire.field_ac, 0, sizeof(model.wire.field_ac));
  std::memcpy(model.wire.event_state + 4, &model.wire.current_badge_card,
              sizeof(model.wire.current_badge_card));
  const Word event_state_base = 0x00154df28U;
  const Word event_state_count = 1;
  std::memcpy(model.wire.event_state, &event_state_base,
              sizeof(event_state_base));
  std::memcpy(model.wire.event_state + 4, &event_state_count,
              sizeof(event_state_count));
  const float event_state_one = 1.0F;
  const float event_state_two = 2.0F;
  std::memcpy(model.wire.event_state + 0x10, &event_state_one,
              sizeof(event_state_one));
  std::memcpy(model.wire.event_state + 0x14, &event_state_two,
              sizeof(event_state_two));
  model.wire.current_badge_flag = 0;

  if (ports.register_00932e80 != nullptr) {
    ports.register_00932e80(&model);
  }
  if (ports.register_006b5770 != nullptr) {
    ports.register_006b5770(&model);
  }

  model.source_release_order.clear();
  for (BadgeSource& source : model.sources) {
    if (ports.release_00dd85c0 != nullptr) {
      ports.release_00dd85c0(&model, &source);
    }
    model.source_release_order.push_back(source.key);
    if (ports.remove_source != nullptr) {
      ports.remove_source(&model, &source);
    }
  }

  for (const BadgeSource& source : model.sources) {
    bool has_instance = source.has_instance;
    Word instance_id = source.instance_id;
    Word property_type = source.property_type;
    std::uint8_t property_flags = source.property_flags;
    std::uint8_t property_value = source.property_value;
    if (ports.property_lookup != nullptr) {
      ports.property_lookup(&model, &source, &has_instance, &instance_id,
                            &property_type, &property_flags,
                            &property_value);
    }

    Word event_id = source.event_id;
    std::uint8_t event_state = 2U;
    if (has_instance) {
      event_state = 4U;
    } else if (property_type == 1U) {
      event_state = property_value != 0U ? 3U : 2U;
    }
    BadgeEvent* event = find_event(model, event_id);
    if (event == nullptr) {
      if (ports.event_lookup_00fe4300 != nullptr) {
        ports.event_lookup_00fe4300(&model, event_id);
      }
      if (ports.event_create_00badea0 != nullptr) {
        ports.event_create_00badea0(&model, &source, event_state, &event_state);
      }
      model.events.push_back(BadgeEvent{event_id, 1, event_state});
      model.wire.m_event_counts.size =
          static_cast<Word>(model.events.size());
    } else {
      event->count = 1;
      event->state = event_state;
      if (has_instance) {
        event->state = 1;
      }
    }
  }

  for (std::size_t index = 0; index < model.events.size(); ++index) {
    if (ports.event_advance_00921580 != nullptr) {
      ports.event_advance_00921580(&model);
    }
  }
  return &model.wire;
}

float mission_event_metric_00fedfe0(
    MissionManagerWire* manager, const std::vector<PlanetMissionRef>& recent,
    Word planet_id, MissionProjectionPorts& ports) {
  const float base = 0.001F;
  const float step = 0.1F;
  for (std::size_t index = 0; index < recent.size(); ++index) {
    if (recent[index].planet_id == planet_id) {
      return base + static_cast<float>(index) * step;
    }
  }

  std::vector<MissionProjectionEntry> projection;
  if (ports.load_projection != nullptr) {
    ports.load_projection(manager, projection);
  }
  for (const MissionProjectionEntry& entry : projection) {
    if (ports.entry_matches != nullptr &&
        ports.entry_matches(manager, entry, planet_id)) {
      return base;
    }
  }
  return 1.0F;
}

Word mission_lookup_00fee220(MissionManagerWire* manager, Word planet_id,
                              MissionLookupPorts& ports) {
  const bool first_communication = read_mission_manager_byte(manager, 0x15) != 0;
  for (const MissionProjectionEntry& entry : ports.projection) {
    bool has_mission = entry.valid;
    Word mission = 0;
    if (ports.resolve_entry != nullptr) {
      mission = ports.resolve_entry(manager, entry, &has_mission);
    } else {
      mission = entry.mission_id;
    }
    if (!has_mission || mission == 0) {
      continue;
    }
    bool has_planet = entry.active;
    Word planet = 0;
    if (ports.planet_from_mission != nullptr) {
      planet = ports.planet_from_mission(manager, mission, &has_planet);
    } else {
      planet = entry.planet_id;
    }
    if (!has_planet) {
      continue;
    }
    if (first_communication || planet == planet_id) {
      return mission;
    }
  }
  return 0;
}

bool mission_choose_00feebb0(MissionManagerWire* manager,
                             MissionSelectionState& state,
                             MissionSelectionPorts& ports) {
  for (Word candidate : state.candidates) {
    const MissionStatusNode* status = find_status(state, candidate);
    if (status != nullptr && status->state == 1U) {
      continue;
    }
    if (ports.candidate_allowed_00fee930 == nullptr ||
        !ports.candidate_allowed_00fee930(manager, candidate)) {
      return true;
    }
  }
  return false;
}

void mission_manager_operation_00feb770(
    MissionManagerWire* manager, Word mode, const MissionRunSeed* seed,
    Word event_word, MissionRunState& state, MissionRunPorts& ports) {
  if (mode != 0x17U) {
    return;
  }
  if (ports.enter_007c50b0 != nullptr) {
    ports.enter_007c50b0(manager, seed, 0, 0);
  }
  if (ports.ready_007c4fd0 == nullptr ||
      !ports.ready_007c4fd0(manager)) {
    return;
  }

  if ((state.initialization_flags & 1U) == 0U) {
    state.initialization_flags |= 1U;
    state.source_ids.clear();
    state.ordered_ids.clear();
    if (ports.initialize_013ca260 != nullptr) {
      ports.initialize_013ca260(&state);
    }
  }
  if (ports.collect_00ffbe50 != nullptr) {
    ports.collect_00ffbe50(manager, &state);
  }
  if ((state.initialization_flags & 2U) == 0U) {
    state.initialization_flags |= 2U;
    state.ordered_ids.clear();
    if (ports.initialize_013ca240 != nullptr) {
      ports.initialize_013ca240(&state);
    }
  }
  if (ports.build_order != nullptr) {
    ports.build_order(manager, &state);
  }

  for (Word id : state.ordered_ids) {
    state.visited_ids.push_back(id);
    Word empire = id;
    if (ports.resolve_empire_00ba9370 != nullptr) {
      empire = ports.resolve_empire_00ba9370(manager, id);
    }
    bool state_one = false;
    if (ports.set_state_01046fc0 != nullptr) {
      state_one = ports.set_state_01046fc0(manager, 1);
    }
    bool dispatch = false;
    if (state_one) {
      dispatch = ports.should_dispatch_00e18c70 != nullptr &&
                 ports.should_dispatch_00e18c70(manager, empire, event_word);
    } else {
      bool state_zero = false;
      if (ports.set_state_01046fc0 != nullptr) {
        state_zero = ports.set_state_01046fc0(manager, 0);
      }
      Word current = 0;
      if (state_zero && ports.current_empire_01021300 != nullptr) {
        current = ports.current_empire_01021300(manager);
      }
      dispatch = state_zero && current == empire &&
                 ports.should_dispatch_00e18c70 != nullptr &&
                 ports.should_dispatch_00e18c70(manager, empire, event_word);
    }
    if (dispatch && ports.dispatch_00feb510 != nullptr) {
      ports.dispatch_00feb510(&state, empire, event_word);
      state.emitted_ids.push_back(id);
    }
  }
  if (ports.cleanup_007c3c10 != nullptr) {
    ports.cleanup_007c3c10(manager);
  }
}

Word read_mission_manager_word(const MissionManagerWire* manager, Word offset) {
  Word value = 0;
  std::memcpy(&value, manager->storage + offset, sizeof(value));
  return value;
}

void write_mission_manager_word(MissionManagerWire* manager, Word offset,
                                Word value) {
  std::memcpy(manager->storage + offset, &value, sizeof(value));
}

std::uint8_t read_mission_manager_byte(const MissionManagerWire* manager,
                                        Word offset) {
  return manager->storage[offset];
}

void write_mission_manager_byte(MissionManagerWire* manager, Word offset,
                                std::uint8_t value) {
  manager->storage[offset] = value;
}

}
