#include "editor_004a88d0.hpp"

namespace openspore::reconstruction::wave13_pilot_dispatch_b00 {

// Byte-exact transcription of the 28 bytes read live at 0x004a88d0:
//   55 8bec 83ec08 e8b5d5f8ff 50 8b4508 50 e8ebd5f8ff 83c408 8be5 5d c3
#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
__attribute__((naked, cdecl)) void
Editor_004a88d0_record_tagged_action_raw(std::uint32_t) {
  __asm__("pushl %ebp\n\t"                            // 0x004a88d0
          "movl %esp, %ebp\n\t"                       // 0x004a88d1
          "subl $8, %esp\n\t"                         // 0x004a88d3
          "call editor_record_current_value_port\n\t" // 0x004a88d6
          "pushl %eax\n\t"                            // 0x004a88db
          "movl 8(%ebp), %eax\n\t"                    // 0x004a88dc
          "pushl %eax\n\t"                            // 0x004a88df
          "call editor_record_emit_port\n\t"          // 0x004a88e0
          "addl $8, %esp\n\t"                         // 0x004a88e5
          "movl %ebp, %esp\n\t"                       // 0x004a88e8
          "popl %ebp\n\t"                             // 0x004a88ea
          "ret\n\t");                                 // 0x004a88eb
}
#else
void __cdecl Editor_004a88d0_record_tagged_action_raw(std::uint32_t) {}
#endif

void __cdecl Editor_004a88d0_record_tagged_action(std::uint32_t event_tag) {
  const std::uint32_t current = editor_record_current_value_port();
  editor_record_emit_port(event_tag, current);
}

} // namespace openspore::reconstruction::wave13_pilot_dispatch_b00
