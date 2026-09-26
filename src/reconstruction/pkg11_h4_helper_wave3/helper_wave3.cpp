#include "helper_wave3.hpp"

namespace openspore::reconstruction::pkg11_h4_helper_wave3 {

extern "C" __attribute__((naked)) OpaqueAddressWindow*
address_window_offset_005c65e0(OpaqueAddressWindow*) {
  __asm__ volatile(
      "leal 0x3c(%ecx), %eax\n\t"
      "ret\n\t");
}

extern "C" __attribute__((naked)) OpaqueContextWord
context_word_read_00ce6950(OpaqueContext*) {
  __asm__ volatile(
      "movl 0x184(%ecx), %eax\n\t"
      "ret\n\t");
}

}
