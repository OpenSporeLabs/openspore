#ifndef OPENSPORE_RECONSTRUCTION_PKG06_CELL_STATE_ABI_HPP
#define OPENSPORE_RECONSTRUCTION_PKG06_CELL_STATE_ABI_HPP

#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-06 staging requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-06 staging requires 32-bit pointers");
static_assert(sizeof(std::uintptr_t) == 4,
              "PKG-06 staging requires 32-bit target addresses");

namespace openspore::reconstruction::pkg06_cell_state {

struct CellObjectData;
struct OpaqueCellDirectionPayload;
struct CellResourceRef;

struct CellPoolIndex {
  std::int32_t value;
};

extern "C" std::uint8_t cell_state_apply_damage_00e7a7c0(
    CellObjectData* target, CellObjectData* source,
    const OpaqueCellDirectionPayload* direction, std::uint32_t damage_kind,
    std::uint32_t effect_kind, float effect_scale);

extern "C" std::uint8_t cell_state_remove_or_kill_00e7a4a0(
    CellObjectData* target, CellPoolIndex source_index,
    CellResourceRef* resource_ref, std::uint8_t player_related,
    std::uint32_t effect_kind, float effect_scale);

extern "C" void cell_state_reset_or_initialize_00e7fd00(
    std::int32_t mode, std::uint32_t value_2, std::uint32_t value_3,
    std::uint32_t value_4, std::uint8_t flag_5, std::uint32_t value_6,
    std::uint8_t flag_7);

extern "C" void cell_state_remove_object_00e780a0(std::int32_t object_index,
                                                  std::uint8_t apply_effect,
                                                  float effect_scale,
                                                  std::uint32_t effect_kind);

}  // namespace openspore::reconstruction::pkg06_cell_state

#endif
