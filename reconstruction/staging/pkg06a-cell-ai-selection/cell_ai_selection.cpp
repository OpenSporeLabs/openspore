#include "cell_ai_selection.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg06a_cell_ai_selection {

std::byte* g_cell_game_016b3c04 = nullptr;

extern "C" ObservedCellAiData* cell_ai_select_profile_00e52910(
    ObservedCellCellResource* resource) {
  std::uintptr_t serializable_address = 0;
  std::memcpy(&serializable_address, g_cell_game_016b3c04 + 0x5190U,
              sizeof(serializable_address));
  std::byte* serializable = reinterpret_cast<std::byte*>(serializable_address);
  std::int32_t difficulty = 0;
  std::memcpy(&difficulty, serializable + 0x7cU, sizeof(difficulty));

  ObservedCellAiData* selected;
  if (difficulty == 0) {
    selected = &resource->ai_easy;
  } else {
    if ((difficulty == 1) || (difficulty != 2)) {
      return &resource->normal;
    }
    selected = &resource->ai_hard;
  }

  if (selected->type == -1) {
    return &resource->normal;
  }
  return selected;
}

}
