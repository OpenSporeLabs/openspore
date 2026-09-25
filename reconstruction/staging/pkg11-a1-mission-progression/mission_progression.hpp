#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11-A1 mission progression staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-11-A1 target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-11-A1 target words are 32-bit");

namespace openspore::reconstruction::pkg11_a1_mission_progression {

using Word = std::uint32_t;

struct MapWire {
  Word compare;
  Word anchor_left;
  Word anchor_right;
  Word anchor_parent;
  Word anchor_color;
  Word size;
  Word allocator;
};

static_assert(sizeof(MapWire) == 28, "PKG-11-A1 map wire is 28 bytes");

struct BadgeManagerWire {
  Word vtable0;
  Word refcount;
  Word vtable1;
  std::uint8_t base_flags[4];
  MapWire m_badges;
  MapWire m_badge_map;
  MapWire m_stage_map;
  MapWire m_event_counts;
  std::uint8_t event_state[32];
  std::uint8_t current_badge_flag;
  std::uint8_t current_badge_padding[3];
  Word current_badge_card;
  Word field_a8;
  std::uint8_t field_ac[20];
};

static_assert(sizeof(BadgeManagerWire) == 0xc0,
              "PKG-11-A1 badge manager wire is 0xc0 bytes");
static_assert(offsetof(BadgeManagerWire, m_badges) == 0x10,
              "PKG-11-A1 badge map offset is 0x10");
static_assert(offsetof(BadgeManagerWire, m_badge_map) == 0x2c,
              "PKG-11-A1 badge value map offset is 0x2c");
static_assert(offsetof(BadgeManagerWire, m_stage_map) == 0x48,
              "PKG-11-A1 stage map offset is 0x48");
static_assert(offsetof(BadgeManagerWire, m_event_counts) == 0x64,
              "PKG-11-A1 event map offset is 0x64");
static_assert(offsetof(BadgeManagerWire, current_badge_card) == 0xa4,
              "PKG-11-A1 current badge offset is 0xa4");

struct BadgeSource {
  Word key;
  Word instance_id;
  bool has_instance;
  bool has_property;
  Word property_type;
  std::uint8_t property_flags;
  std::uint8_t property_value;
  Word event_id;
};

struct BadgeEvent {
  Word key;
  Word count;
  std::uint8_t state;
};

struct BadgeManagerModel {
  BadgeManagerWire wire{};
  std::vector<BadgeSource> sources;
  std::vector<BadgeEvent> events;
  std::vector<Word> stage_keys;
  std::vector<Word> source_release_order;
};

struct BadgeManagerPorts {
  using BaseConstructor = void (*)(BadgeManagerModel*);
  using RegisterPoints = void (*)(BadgeManagerModel*);
  using RegisterProperty = void (*)(BadgeManagerModel*);
  using ReleaseSource = void (*)(BadgeManagerModel*, BadgeSource*);
  using RemoveSource = void (*)(BadgeManagerModel*, BadgeSource*);
  using PropertyLookup = void (*)(BadgeManagerModel*, const BadgeSource*,
                                  bool*, Word*, Word*, std::uint8_t*,
                                  std::uint8_t*);
  using EventCreate = void (*)(BadgeManagerModel*, const BadgeSource*, Word,
                               std::uint8_t*);
  using EventLookup = void (*)(BadgeManagerModel*, Word);
  using EventAdvance = void (*)(BadgeManagerModel*);
  using FreeBuffer = void (*)(BadgeManagerModel*, void*);

  BaseConstructor base_00b5b6c0 = nullptr;
  RegisterPoints register_00932e80 = nullptr;
  RegisterProperty register_006b5770 = nullptr;
  ReleaseSource release_00dd85c0 = nullptr;
  RemoveSource remove_source = nullptr;
  PropertyLookup property_lookup = nullptr;
  EventCreate event_create_00badea0 = nullptr;
  EventLookup event_lookup_00fe4300 = nullptr;
  EventAdvance event_advance_00921580 = nullptr;
  FreeBuffer free_00f47380 = nullptr;
};

BadgeManagerWire* badge_manager_construct_00fe4fa0(
    BadgeManagerModel& model, BadgeManagerPorts& ports);

struct MissionManagerWire {
  std::uint8_t storage[0x144]{};
};

struct PlanetMissionRef {
  Word planet_id;
  Word payload;
};

struct MissionProjectionEntry {
  Word mission_id;
  Word planet_id;
  bool valid;
  bool active;
};

struct MissionProjectionPorts {
  using LoadProjection = void (*)(MissionManagerWire*,
                                 std::vector<MissionProjectionEntry>&);
  using EntryMatches = bool (*)(MissionManagerWire*,
                                const MissionProjectionEntry&,
                                Word);
  using EntryPlanet = Word (*)(MissionManagerWire*,
                               const MissionProjectionEntry&);

  LoadProjection load_projection = nullptr;
  EntryMatches entry_matches = nullptr;
  EntryPlanet entry_planet = nullptr;
};

struct MissionLookupPorts {
  using ResolveEntry = Word (*)(MissionManagerWire*,
                               const MissionProjectionEntry&,
                               bool*);
  using PlanetFromMission = Word (*)(MissionManagerWire*, Word, bool*);

  ResolveEntry resolve_entry = nullptr;
  PlanetFromMission planet_from_mission = nullptr;
  std::vector<MissionProjectionEntry> projection;
};

struct MissionStatusNode {
  Word key;
  Word state;
};

struct MissionSelectionState {
  std::vector<Word> candidates;
  std::vector<MissionStatusNode> status_nodes;
};

struct MissionSelectionPorts {
  using CandidateAllowed = bool (*)(MissionManagerWire*, Word);

  CandidateAllowed candidate_allowed_00fee930 = nullptr;
};

float mission_event_metric_00fedfe0(
    MissionManagerWire* manager, const std::vector<PlanetMissionRef>& recent,
    Word planet_id, MissionProjectionPorts& ports);

Word mission_lookup_00fee220(MissionManagerWire* manager, Word planet_id,
                              MissionLookupPorts& ports);

bool mission_choose_00feebb0(MissionManagerWire* manager,
                             MissionSelectionState& state,
                             MissionSelectionPorts& ports);

struct MissionRunSeed {
  Word value;
  Word mode;
  Word event_word;
};

struct MissionRunState {
  Word initialization_flags = 0;
  std::vector<Word> source_ids;
  std::vector<Word> ordered_ids;
  std::vector<Word> emitted_ids;
  std::vector<Word> visited_ids;
};

struct MissionRunPorts {
  using Enter = void (*)(MissionManagerWire*, const MissionRunSeed*, Word, Word);
  using Ready = bool (*)(MissionManagerWire*);
  using InitializeGlobals = void (*)(MissionRunState*);
  using CollectSource = void (*)(MissionManagerWire*, MissionRunState*);
  using BuildOrder = void (*)(MissionManagerWire*, MissionRunState*);
  using ResolveEmpire = Word (*)(MissionManagerWire*, Word);
  using SetState = bool (*)(MissionManagerWire*, Word);
  using CurrentEmpire = Word (*)(MissionManagerWire*);
  using ShouldDispatch = bool (*)(MissionManagerWire*, Word, Word);
  using Dispatch = void (*)(MissionRunState*, Word, Word);
  using Cleanup = void (*)(MissionManagerWire*);

  Enter enter_007c50b0 = nullptr;
  Ready ready_007c4fd0 = nullptr;
  InitializeGlobals initialize_013ca260 = nullptr;
  InitializeGlobals initialize_013ca240 = nullptr;
  CollectSource collect_00ffbe50 = nullptr;
  BuildOrder build_order = nullptr;
  ResolveEmpire resolve_empire_00ba9370 = nullptr;
  SetState set_state_01046fc0 = nullptr;
  CurrentEmpire current_empire_01021300 = nullptr;
  ShouldDispatch should_dispatch_00e18c70 = nullptr;
  Dispatch dispatch_00feb510 = nullptr;
  Cleanup cleanup_007c3c10 = nullptr;
};

void mission_manager_operation_00feb770(
    MissionManagerWire* manager, Word mode, const MissionRunSeed* seed,
    Word event_word, MissionRunState& state, MissionRunPorts& ports);

Word read_mission_manager_word(const MissionManagerWire* manager, Word offset);
void write_mission_manager_word(MissionManagerWire* manager, Word offset,
                                Word value);
std::uint8_t read_mission_manager_byte(const MissionManagerWire* manager,
                                        Word offset);
void write_mission_manager_byte(MissionManagerWire* manager, Word offset,
                                std::uint8_t value);

}
