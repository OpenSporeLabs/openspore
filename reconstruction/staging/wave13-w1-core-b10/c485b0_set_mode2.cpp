#include "c485b0_set_mode2.hpp"

namespace openspore::reconstruction::wave13_w1_core_b10 {

void SimTokenOwner_SetMode2_00c485b0(OpaqueSimTokenOwner* owner) {
  Port_00c47cc0_SetMode(owner, 2u);
}

}  // namespace openspore::reconstruction::wave13_w1_core_b10
