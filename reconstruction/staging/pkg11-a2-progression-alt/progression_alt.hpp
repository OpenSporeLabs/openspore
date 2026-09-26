#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11-A2 progression alternative requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG11_A2_THISCALL __thiscall
#else
#define PKG11_A2_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg11_a2_progression_alt {

using Word = std::uint32_t;
using Opaque = std::uint32_t;

struct MissionManagerWire {
  std::uint8_t storage[0x144]{};
};

struct MissionProjectionVectorWire {
  std::uint8_t needs_update;
  std::uint8_t padding[3];
  const Opaque* begin;
  const Opaque* end;
};

struct MissionManagerOperationPorts {
  using GetSimulatorSystem = Opaque (*)();
  using InitializeSubsystem = void(PKG11_A2_THISCALL*)(Opaque,
                                                       MissionManagerWire*);
  using PopulateManagerState = void(PKG11_A2_THISCALL*)(MissionManagerWire*);
  using GetRegistry = Opaque (*)();
  using PrepareRegistry = void(PKG11_A2_THISCALL*)(Opaque);
  using BuildRegistryEntry = void(PKG11_A2_THISCALL*)(Opaque, void*, Word);
  using RegisterFixedIdentifiers = void (*)();
  using GetNounManager = Opaque (*)();
  using ProjectNouns = const MissionProjectionVectorWire*(
      PKG11_A2_THISCALL*)(Opaque, Opaque, Opaque, Opaque, Opaque, Word);
  using DispatchProjectionEntry = void(PKG11_A2_THISCALL*)(Opaque);

  GetSimulatorSystem get_simulator_system = nullptr;
  InitializeSubsystem initialize_subsystem = nullptr;
  PopulateManagerState populate_manager_state = nullptr;
  GetRegistry get_registry = nullptr;
  PrepareRegistry prepare_registry = nullptr;
  BuildRegistryEntry build_registry_entry = nullptr;
  RegisterFixedIdentifiers register_fixed_identifiers = nullptr;
  GetNounManager get_noun_manager = nullptr;
  ProjectNouns project_nouns = nullptr;
  DispatchProjectionEntry dispatch_projection_entry = nullptr;
};

MissionManagerOperationPorts& mission_manager_operation_ports();
void set_mission_manager_operation_ports(
    const MissionManagerOperationPorts* ports);

struct MissionTrackRecordStorage {
  std::uint8_t storage[0x38]{};
};

struct MissionTrackPorts {
  using GetNounCarrier = Opaque (*)();
  using ReadCommandValue = Opaque(PKG11_A2_THISCALL*)(Opaque);
  using IsCommandValid = bool(PKG11_A2_THISCALL*)(Opaque, Word);
  using GetCurrentEmpire = Opaque (*)();
  using ComputeAndUpdateScore = std::int32_t(PKG11_A2_THISCALL*)(Opaque);

  GetNounCarrier get_noun_carrier = nullptr;
  ReadCommandValue read_command_value = nullptr;
  IsCommandValid is_command_valid = nullptr;
  GetCurrentEmpire get_current_empire = nullptr;
  ComputeAndUpdateScore compute_and_update_score = nullptr;
};

MissionTrackPorts& mission_track_ports();
void set_mission_track_ports(const MissionTrackPorts* ports);

struct AchievementManagerWire {
  std::uint8_t storage[0xa8]{};
};

struct AchievementRecordWire {
  Word flags;
  Word progress;
  Word target;
};

struct AchievementProgressPorts {
  using LookupOrCreate =
      AchievementRecordWire*(PKG11_A2_THISCALL*)(AchievementManagerWire*, Word);
  using ForwardProgressKey = bool(PKG11_A2_THISCALL*)(AchievementManagerWire*,
                                                      Word);

  LookupOrCreate lookup_or_create = nullptr;
  ForwardProgressKey forward_progress_key = nullptr;
};

AchievementProgressPorts& achievement_progress_ports();
void set_achievement_progress_ports(const AchievementProgressPorts* ports);

using MissionManagerOperationAbi =
    void(PKG11_A2_THISCALL*)(MissionManagerWire*);
using MissionTrackAbi = bool(PKG11_A2_THISCALL*)(MissionManagerWire*,
                                                 std::int32_t, Opaque);
using AchievementProgressAbi = void(PKG11_A2_THISCALL*)(AchievementManagerWire*,
                                                        Word, Word);

void PKG11_A2_THISCALL
mission_manager_operation_00fee310(MissionManagerWire* manager);
bool PKG11_A2_THISCALL mission_track_predicate_00febc90(
    MissionManagerWire* manager, std::int32_t index, Opaque identity);
void PKG11_A2_THISCALL achievement_progress_update_00676e90(
    AchievementManagerWire* manager, Word increment, Word key);

#undef PKG11_A2_THISCALL

static_assert(sizeof(void*) == 4, "PKG-11-A2 target pointers are 32-bit");
static_assert(sizeof(Word) == 4, "PKG-11-A2 target words are 32-bit");
static_assert(sizeof(MissionManagerWire) == 0x144,
              "PKG-11-A2 mission manager access window");
static_assert(sizeof(MissionProjectionVectorWire) == 12,
              "PKG-11-A2 projection vector result");
static_assert(sizeof(MissionTrackRecordStorage) == 0x38,
              "PKG-11-A2 mission track entry extent");
static_assert(sizeof(AchievementManagerWire) == 0xa8,
              "PKG-11-A2 achievement manager extent");
static_assert(sizeof(AchievementRecordWire) == 12,
              "PKG-11-A2 achievement record extent");
static_assert(std::is_same<decltype(&mission_manager_operation_00fee310),
                           MissionManagerOperationAbi>::value,
              "PKG-11-A2 mission operation ABI");
static_assert(std::is_same<decltype(&mission_track_predicate_00febc90),
                           MissionTrackAbi>::value,
              "PKG-11-A2 mission track ABI");
static_assert(std::is_same<decltype(&achievement_progress_update_00676e90),
                           AchievementProgressAbi>::value,
              "PKG-11-A2 achievement progress ABI");

}
