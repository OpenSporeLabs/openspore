#pragma once

#include <cstddef>
#include <cstdint>

#include "../pkg06a_cell_ai_selection/cell_ai_selection.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-06D reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-06D target pointers are 32-bit");
static_assert(sizeof(std::int32_t) == 4, "PKG-06D target words are 32-bit");
static_assert(sizeof(float) == 4, "PKG-06D target floats are 32-bit");

namespace openspore::reconstruction::pkg06d_cell_behavior_timer {

using openspore::reconstruction::pkg06a_cell_ai_selection::g_cell_game_016b3c04;

struct alignas(4) OpaqueBehaviorTimerRecord {
  std::byte opaque[0x80];
};

using OpaqueBehaviorTimerEntryEcx = std::byte*;

static_assert(
    sizeof(OpaqueBehaviorTimerRecord) == 0x80,
    "PKG-06D record is model fixture storage; live stride unresolved");

struct GateCallContext {
  OpaqueBehaviorTimerRecord* record = nullptr;
  OpaqueBehaviorTimerEntryEcx opaque_entry_ecx = nullptr;
  float delta = 0.0F;
};

struct ExpireCallContext {
  OpaqueBehaviorTimerRecord* record = nullptr;
  float delta = 0.0F;
  std::uint32_t slot = 0;
};

struct AdvanceCallContext {
  OpaqueBehaviorTimerRecord* record = nullptr;
  float delta = 0.0F;
};

struct FallbackCallContext {
  OpaqueBehaviorTimerRecord* record = nullptr;
  float delta = 0.0F;
  std::uint32_t first_zero = 0;
  std::uint32_t second_zero = 0;
};

using GateCallback = bool (*)(const GateCallContext&);
using ExpireCallback = bool (*)(const ExpireCallContext&);
using AdvanceCallback = bool (*)(const AdvanceCallContext&);
using FallbackCallback = void (*)(const FallbackCallContext&);

struct NativePorts {
  static constexpr char boundary_metadata[] =
      "normalized callback boundary: "
      "00e59c10: EAX record, ECX entry-ECX residue (not a pool), stack "
      "record/delta, AL; "
      "00e7b540: ECX record, EDX slot, stack delta, AL, EAX unresolved "
      "residue; "
      "00e7ba30: EAX record, ECX unresolved prior-call residue, stack delta, "
      "AL; "
      "00e7e130: EDI record, stack delta/zero/zero, void; "
      "00e7e6c0: EAX record, ECX entry-ECX residue (not a pool), "
      "caller-cleaned stack float, "
      "void plain RET, no target-local pool release";

  GateCallback gate_00e59c10 = nullptr;
  ExpireCallback expire_00e7b540 = nullptr;
  AdvanceCallback advance_00e7ba30 = nullptr;
  FallbackCallback fallback_00e7e130 = nullptr;
};

inline constexpr char shared_game_global_metadata[] =
    "selector reads PKG-06A g_cell_game_016b3c04 + 0x5198";

void cell_behavior_timer_update_00e7e6c0(
    OpaqueBehaviorTimerRecord* record,
    OpaqueBehaviorTimerEntryEcx opaque_entry_ecx, float delta,
    NativePorts& ports);

}
