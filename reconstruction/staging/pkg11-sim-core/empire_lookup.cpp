#include "empire_lookup.hpp"

namespace openspore::reconstruction::pkg11_sim_core {

#if defined(_MSC_VER)
#define PKG11_THISCALL __thiscall
#else
#define PKG11_THISCALL __attribute__((thiscall))
#endif

OpaqueEmpire* PKG11_THISCALL Simulator_LookupEmpireByPoliticalId(
    OpaqueStarManager* manager, TargetWord political_id) {
  if (political_id == 0xffffffffU) {
    return nullptr;
  }

  pkg20_gameglobal::OrderedMapEntry* entry = nullptr;
  pkg20_gameglobal_00e5c780(&manager->mEmpires, &entry, &political_id);
  auto* anchor = reinterpret_cast<pkg20_gameglobal::OrderedMapEntry*>(
      &manager->mEmpires.anchor);
  if (entry == anchor) {
    return nullptr;
  }

  return reinterpret_cast<EmpireMapEntry*>(entry)->payload;
}

#undef PKG11_THISCALL

}
