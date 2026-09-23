#include "CellUI.hpp"

namespace openspore::cellui {

void CellUI::load() {
  globalUi = "GlobalUICell-3";
  layoutA = 20.0F;
  layoutB = 1.0F;
  loaded = true;
}

int CellUI::showHealthRollover(std::uint32_t gfxObjectIndex,
                               std::uint32_t cellPoolIndex, int initialHealth) {
  // ShowHealthRollover (00e62340) early-outs when the cell has no GFX object.
  if (gfxObjectIndex == 0) {
    return -1;
  }
  UIRollover r;
  r.mObjectPoolIndex = cellPoolIndex;
  r.mCellIndex = cellPoolIndex;
  r.field_8 = static_cast<float>(initialHealth) * 0.16666667F;  // initialHealth / 6
  r.mDisappearTime = 0.5F;  // *(+0x24) = 0x3f000000
  rollovers.push_back(r);
  return static_cast<int>(rollovers.size() - 1);
}

} // namespace openspore::cellui
