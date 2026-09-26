#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-11-A3 achievement mission wave2 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG11_A3_THISCALL __thiscall
#else
#define PKG11_A3_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg11_a3_achievement_mission_wave2 {

using Word = std::uint32_t;
using Opaque = std::uint32_t;

struct AchievementSortedSetWire {
  Opaque begin;
  Opaque end;
  Opaque capacity;
  Opaque allocator;
  std::uint8_t reserved[4];
  std::uint8_t tag;
  std::uint8_t tail[3];
};

struct AchievementSerializerWire {
  std::uint8_t header[0x24];
  AchievementSortedSetWire achievement_set;
  std::uint8_t tail[0x80];
};

struct AchievementManagerWire {
  const void* vftable;
  Opaque notifier_ui;
  Opaque serializer;
  std::uint8_t achievements[0x18];
  std::uint8_t gate;
  std::uint8_t tail[0x83];
};

struct AchievementDefinitionWire {
  Word flags;
  Word progress_flags;
  Word target;
};

struct AchievementLookupResultWire {
  Opaque position;
  std::uint8_t inserted;
  std::uint8_t tail[3];
};

struct AchievementEventArgumentWire {
  std::uint8_t storage[0x10];
  std::uint16_t flags;
  std::int16_t type_id;
  std::uint16_t reserved;
  std::uint16_t tail;
};

struct AchievementCompletionPorts {
  using SearchSortedRange = Opaque (*)(Opaque begin, Opaque end,
                                       const Word* key, std::uint8_t tag);
  using LookupOrCreate = const AchievementLookupResultWire*(
      PKG11_A3_THISCALL*)(Opaque container, AchievementLookupResultWire* out,
                          const Word* key);
  using AcquireNotifier = Opaque (*)();
  using NotifyCompletion = void(PKG11_A3_THISCALL*)(Opaque notifier, Word event,
                                                    const Word* key,
                                                    Opaque tail);
  using AcquireEventQueue = Opaque (*)();
  using ConstructEventArgument = AchievementEventArgumentWire*(
      PKG11_A3_THISCALL*)(AchievementEventArgumentWire * destination,
                          const Word* key);
  using PostCompletionEvent =
      Opaque(PKG11_A3_THISCALL*)(Opaque queue, Opaque type_descriptor,
                                 const AchievementEventArgumentWire* arguments);
  using ReleaseEventArgument = void(PKG11_A3_THISCALL*)(
      AchievementEventArgumentWire* arguments, Opaque tail);
  using PersistAchievements =
      Opaque(PKG11_A3_THISCALL*)(AchievementManagerWire*);

  SearchSortedRange search_sorted_set = nullptr;
  LookupOrCreate lookup_or_create = nullptr;
  AcquireNotifier acquire_notifier = nullptr;
  NotifyCompletion notify_completion = nullptr;
  AcquireEventQueue acquire_event_queue = nullptr;
  ConstructEventArgument construct_event_argument = nullptr;
  PostCompletionEvent post_completion_event = nullptr;
  ReleaseEventArgument release_event_argument = nullptr;
  PersistAchievements persist_achievements = nullptr;
};

AchievementCompletionPorts& achievement_completion_ports();
void set_achievement_completion_ports(const AchievementCompletionPorts* ports);

inline constexpr Word kCompletionNotifyEvent = 0x05c6930eU;
inline constexpr Word kCompletionPostType = 0x01edc82b0U;
inline constexpr std::uint8_t kCompletionEventReleaseFlag = 0x4U;
inline constexpr Word kCompletionForwardedTail = 0U;

struct AchievementFlagTransitionPorts {
  using LookupOrCreate = AchievementDefinitionWire*(
      PKG11_A3_THISCALL*)(AchievementManagerWire * manager, Word key);
  using CompareThreshold = bool (*)(const AchievementDefinitionWire* record);
  using ForwardCompletion =
      bool(PKG11_A3_THISCALL*)(AchievementManagerWire* manager, Word key);

  LookupOrCreate lookup_or_create = nullptr;
  CompareThreshold compare_threshold = nullptr;
  ForwardCompletion forward_completion = nullptr;
};

AchievementFlagTransitionPorts& achievement_flag_transition_ports();
void set_achievement_flag_transition_ports(
    const AchievementFlagTransitionPorts* ports);

struct MissionManagerWire {
  const void* vftable;
};

struct MissionRecordFlagWire {
  std::uint8_t value;
};

struct MissionRecordInitPorts {
  using AcquireManagerTarget = Opaque(PKG11_A3_THISCALL*)(MissionManagerWire*);
  using AcquireWriteStream = Opaque(PKG11_A3_THISCALL*)(Opaque target);
  using WriteRecordWord = Opaque(PKG11_A3_THISCALL*)(Opaque stream,
                                                     const Word* payload,
                                                     std::int32_t count,
                                                     Word mode);
  using WriteRecordByte = Word(PKG11_A3_THISCALL*)(Opaque stream,
                                                   const std::uint8_t* payload,
                                                   Word size);

  AcquireManagerTarget acquire_manager_target = nullptr;
  AcquireWriteStream acquire_write_stream = nullptr;
  WriteRecordWord write_record_word = nullptr;
  WriteRecordByte write_record_byte = nullptr;
};

MissionRecordInitPorts& mission_record_init_ports();
void set_mission_record_init_ports(const MissionRecordInitPorts* ports);

using AchievementCompletionAbi =
    bool(PKG11_A3_THISCALL*)(AchievementManagerWire* manager, Word key);
using AchievementFlagTransitionAbi = void(PKG11_A3_THISCALL*)(
    AchievementManagerWire* manager, Word key, Word mask, std::uint8_t set);
using MissionRecordInitAbi = MissionManagerWire* (*)(MissionManagerWire *
                                                         manager,
                                                     const std::uint8_t* flag);

bool PKG11_A3_THISCALL achievement_completion_boundary_00676710(
    AchievementManagerWire* manager, Word key);
void PKG11_A3_THISCALL achievement_progress_flag_transition_00676ed0(
    AchievementManagerWire* manager, Word key, Word mask, std::uint8_t set);
MissionManagerWire* mission_manager_record_init_00fec3c0(
    MissionManagerWire* manager, const std::uint8_t* flag);

#undef PKG11_A3_THISCALL

static_assert(sizeof(void*) == 4, "PKG-11-A3 target pointers are 32-bit");
static_assert(sizeof(Word) == 4, "PKG-11-A3 target words are 32-bit");
static_assert(sizeof(AchievementSortedSetWire) == 0x18,
              "PKG-11-A3 sorted set window extent");
static_assert(offsetof(AchievementSortedSetWire, tag) == 0x14,
              "PKG-11-A3 sorted set tag offset");
static_assert(sizeof(AchievementSerializerWire) == 0xbc,
              "PKG-11-A3 achievement serializer extent");
static_assert(offsetof(AchievementSerializerWire, achievement_set) == 0x24,
              "PKG-11-A3 achievement set window offset");
static_assert(sizeof(AchievementManagerWire) == 0xa8,
              "PKG-11-A3 achievement manager extent");
static_assert(offsetof(AchievementManagerWire, serializer) == 0x08,
              "PKG-11-A3 serializer intrusive pointer offset");
static_assert(offsetof(AchievementManagerWire, gate) == 0x24,
              "PKG-11-A3 achievement gate byte offset");
static_assert(sizeof(AchievementDefinitionWire) == 12,
              "PKG-11-A3 achievement definition extent");
static_assert(offsetof(AchievementDefinitionWire, progress_flags) == 0x04,
              "PKG-11-A3 progress flag word offset");
static_assert(sizeof(AchievementLookupResultWire) == 8,
              "PKG-11-A3 lookup result extent");
static_assert(offsetof(AchievementLookupResultWire, inserted) == 0x04,
              "PKG-11-A3 lookup inserted flag offset");
static_assert(sizeof(AchievementEventArgumentWire) == 0x18,
              "PKG-11-A3 event argument extent");
static_assert(offsetof(AchievementEventArgumentWire, flags) == 0x10,
              "PKG-11-A3 event argument flags offset");
static_assert(offsetof(AchievementEventArgumentWire, type_id) == 0x12,
              "PKG-11-A3 event argument type offset");
static_assert(offsetof(AchievementEventArgumentWire, reserved) == 0x14,
              "PKG-11-A3 event argument reserved offset");
static_assert(sizeof(MissionManagerWire) == 4,
              "PKG-11-A3 mission manager vtable window");
static_assert(sizeof(MissionRecordFlagWire) == 1,
              "PKG-11-A3 mission record flag extent");
static_assert(std::is_same<decltype(&achievement_completion_boundary_00676710),
                           AchievementCompletionAbi>::value,
              "PKG-11-A3 achievement completion ABI");
static_assert(
    std::is_same<decltype(&achievement_progress_flag_transition_00676ed0),
                 AchievementFlagTransitionAbi>::value,
    "PKG-11-A3 achievement flag transition ABI");
static_assert(std::is_same<decltype(&mission_manager_record_init_00fec3c0),
                           MissionRecordInitAbi>::value,
              "PKG-11-A3 mission record initializer ABI");

}
