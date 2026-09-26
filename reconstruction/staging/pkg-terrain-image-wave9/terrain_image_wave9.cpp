#include "terrain_image_wave9.hpp"

namespace openspore::reconstruction::pkg_terrain_image_wave9 {

namespace {

OpaqueWord default_opaque_word_port() { return 0u; }

OpaqueWord default_opaque_word_first_use_port() { return 0u; }

OpaqueWordPort g_opaque_word_port = default_opaque_word_port;
OpaqueWordFirstUsePort g_opaque_word_first_use_port =
    default_opaque_word_first_use_port;
bool g_opaque_word_initialized = false;

}

void set_opaque_word_port(OpaqueWordPort port) {
  g_opaque_word_port = port == nullptr ? default_opaque_word_port : port;
}

void set_opaque_word_first_use_port(OpaqueWordFirstUsePort port) {
  g_opaque_word_first_use_port =
      port == nullptr ? default_opaque_word_first_use_port : port;
}

extern "C" OpaqueWord opaque_word_first_use_011e5870() {
  return g_opaque_word_first_use_port();
}

extern "C" OpaqueWord opaque_word_port_011e58c0() {
  if (!g_opaque_word_initialized) {
    g_opaque_word_initialized = true;
    static_cast<void>(opaque_word_first_use_011e5870());
  }
  return g_opaque_word_port();
}

extern "C" OpaqueWord terrain_probe_00f968b0(OpaqueSimulationData*,
                                             OpaqueSimulationProbe*) {
  __asm__ volatile(
      "pushl %ebx\n\t"
      "pushl %esi\n\t"
      "movl %ecx, %esi\n\t"
      "pushl %edi\n\t"
      "testl %esi, %esi\n\t"
      "jz 1f\n\t"
      "leal 0x4(%esi), %edi\n\t"
      "jmp 2f\n\t"
      "1:\n\t"
      "xorl %edi, %edi\n\t"
      "2:\n\t"
      "movl 0x10(%esp), %ebx\n\t"
      "movl (%ebx), %eax\n\t"
      "movl 0x58(%eax), %edx\n\t"
      "pushl $0x8\n\t"
      "movl %ebx, %ecx\n\t"
      "call *%edx\n\t"
      "cmpl %eax, %edi\n\t"
      "jnz 3f\n\t"
      "testl %esi, %esi\n\t"
      "jz 4f\n\t"
      "addl $0x4, %esi\n\t"
      "jmp 5f\n\t"
      "4:\n\t"
      "xorl %esi, %esi\n\t"
      "5:\n\t"
      "movl (%ebx), %eax\n\t"
      "movl 0x58(%eax), %edx\n\t"
      "pushl $0x7\n\t"
      "movl %ebx, %ecx\n\t"
      "call *%edx\n\t"
      "cmpl %eax, %esi\n\t"
      "jnz 3f\n\t"
      "popl %edi\n\t"
      "popl %esi\n\t"
      "movl $0x1, %eax\n\t"
      "popl %ebx\n\t"
      "ret $0x4\n\t"
      "3:\n\t"
      "popl %edi\n\t"
      "popl %esi\n\t"
      "xorl %eax, %eax\n\t"
      "popl %ebx\n\t"
      "ret $0x4\n\t");
}

extern "C" OpaqueWord image_write_pair_00fc7e10(OpaquePairDestination*,
                                                OpaqueWord, OpaqueWord) {
  __asm__ volatile(
      "movl 0x4(%esp), %eax\n\t"
      "movl 0x8(%esp), %edx\n\t"
      "movl %eax, 0x8(%ecx)\n\t"
      "movl %edx, 0x10(%ecx)\n\t"
      "ret $0x8\n\t");
}

extern "C" void image_write_fields_00fd9460(OpaqueImageReceiver*, OpaqueWord) {
  __asm__ volatile(
      "movl 0x4(%esp), %eax\n\t"
      "pushl %esi\n\t"
      "movl %ecx, %esi\n\t"
      "movl %eax, 0x4(%esi)\n\t"
      "call opaque_word_port_011e58c0\n\t"
      "movl %eax, 0x8(%esi)\n\t"
      "popl %esi\n\t"
      "ret $0x4\n\t");
}

}
