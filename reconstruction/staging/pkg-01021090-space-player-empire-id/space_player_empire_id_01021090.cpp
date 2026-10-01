#include "space_player_empire_id_01021090.hpp"

namespace openspore::reconstruction::pkg_01021090_space_player_empire_id {

// The global this entry publishes nothing to and only reads. Modelled as a
// definition here so the model test can install a fixture; the promoted
// pkg01_roots package declares the same global under its own name, so the two
// packages can be linked together without a duplicate definition.
SpacePlayerDataEmpireIdFixture* g_016dda8c = nullptr;

// 0x01021090  a1 8c da 6d 01  MOV EAX,dword ptr [0x016dda8c]
// 0x01021095  8b 40 18        MOV EAX,dword ptr [EAX + 0x18]
// 0x01021098  c3              RET
extern "C" std::uint32_t space_player_empire_id_01021090() {
  // Two loads and a return, and nothing else. The first load re-reads the
  // global on every call, so a republished global is observed immediately and
  // nothing is cached in EAX across entries. There is no null test anywhere on
  // this path: a global of zero is dereferenced at the displacement below, and
  // the model test measures that with a forked child instead of asserting it.
  //
  // The displacement is taken from the header rather than spelled here so the
  // literal set this body states is exactly the literal set the machine
  // listing carries, and so a single edit cannot make the two disagree. The
  // word is read as a 32-bit unsigned scalar; the ABI record's
  // `pointer_like` classification of the EAX value is a heuristic on "the last
  // value written to EAX" and is recorded as a disagreement in the header
  // rather than adopted.
  return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);
}

}  // namespace openspore::reconstruction::pkg_01021090_space_player_empire_id