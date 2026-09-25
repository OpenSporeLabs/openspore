#include "space_comm_event.hpp"

namespace openspore::reconstruction::pkg12_space {

extern "C" cCommEvent* __thiscall pkg12_re_00aeb160(
    cCommManager* manager, OpaquePayloadWord payload0,
    OpaquePayloadWord payload1, OpaquePayloadWord payload2,
    OpaquePayloadWord payload3, OpaquePayloadWord payload4,
    OpaquePayloadWord payload5, std::uint32_t duration);

extern "C" void __thiscall pkg12_re_00aebe90(cCommManager* manager,
                                             cCommEvent* event);

extern "C" __thiscall __attribute__((naked)) void
pkg12_space_comm_event_00aeb720(cCommManager*, OpaquePayloadWord,
                                OpaquePayloadWord, OpaquePayloadWord,
                                OpaquePayloadWord, OpaquePayloadWord,
                                OpaquePayloadWord) {
  __asm__(
      "movl 0x18(%esp), %eax\n\t"
      "movl 0x10(%esp), %edx\n\t"
      "pushl %esi\n\t"
      "pushl $0x0\n\t"
      "pushl %eax\n\t"
      "movl 0x18(%esp), %eax\n\t"
      "movl %ecx, %esi\n\t"
      "movl 0x20(%esp), %ecx\n\t"
      "pushl %ecx\n\t"
      "movl 0x18(%esp), %ecx\n\t"
      "pushl %edx\n\t"
      "movl 0x18(%esp), %edx\n\t"
      "pushl %eax\n\t"
      "pushl %ecx\n\t"
      "pushl %edx\n\t"
      "movl %esi, %ecx\n\t"
      "call pkg12_re_00aeb160\n\t"
      "pushl %eax\n\t"
      "movl %esi, %ecx\n\t"
      "call pkg12_re_00aebe90\n\t"
      "popl %esi\n\t"
      "ret $0x18\n\t");
}

}
