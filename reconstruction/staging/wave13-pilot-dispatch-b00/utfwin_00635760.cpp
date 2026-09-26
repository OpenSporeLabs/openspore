#include "utfwin_00635760.hpp"

namespace openspore::reconstruction::wave13_pilot_dispatch_b00 {

// Byte-exact transcription of the 34 bytes read live at 0x00635760:
//   8b442404 50 e856f6ffff 85c0 7411 8b10 8b527c
//   c7442404 01000000 8bc8 ffe2 c20800
// The tail transfer is preserved: the frame built by the two stack arguments is
// handed to the +0x7C callee, which is itself RET 0x8.
#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
extern "C" __attribute__((naked)) void
UtfWin_00635760_set_flag_by_control_id_raw(OpaqueUtfWinRootRegistry *,
                                           std::uint32_t, bool) {
  __asm__("movl 4(%esp), %eax\n\t" // 0x00635760 control id
          "pushl %eax\n\t"         // 0x00635764
          "call utfwin_registry_find_window_by_control_id\n\t" // 0x00635765
          "testl %eax, %eax\n\t"                               // 0x0063576a
          "jz 1f\n\t"                 // 0x0063576c  no window -> RET 0x8
          "movl (%eax), %edx\n\t"     // 0x0063576e
          "movl 0x7c(%edx), %edx\n\t" // 0x00635770  IWindow::SetFlag
          "movl $1, 4(%esp)\n\t" // 0x00635773  first arg := kWinFlagVisible
          "movl %eax, %ecx\n\t"  // 0x0063577b  this := window
          "jmp *%edx\n\t"        // 0x0063577d  tail transfer
          "1:\n\t"               // 0x0063577f
          "ret $8\n\t");         // 0x0063577f  callee pops both arguments
}
#else
extern "C" void
UtfWin_00635760_set_flag_by_control_id_raw(OpaqueUtfWinRootRegistry *,
                                           std::uint32_t, bool) {}
#endif

#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
extern "C" __attribute__((naked)) void
UtfWin_00635760_host_bridge(OpaqueUtfWinRootRegistry *, std::uint32_t, bool) {
  // Entry: [esp]=return address, [esp+4]=registry, [esp+8]=control id,
  // [esp+12]=flag value. This rebuilds exactly the frame the byte-exact body
  // expects to be entered with, then transfers control into it. It never
  // returns through its own epilogue: both the body's null exit (RET 8) and
  // the tail transfer land on the caller's return address.
  __asm__("movl 4(%esp), %ecx\n\t" // receiver
          "subl $8, %esp\n\t"
          "movl 8(%esp), %eax\n\t" // return address
          "movl %eax, (%esp)\n\t"
          "movl 16(%esp), %eax\n\t" // control id
          "movl %eax, 4(%esp)\n\t"
          "movl 20(%esp), %eax\n\t" // flag value
          "movl %eax, 8(%esp)\n\t"
          "jmp UtfWin_00635760_set_flag_by_control_id_raw\n\t");
}
#else
extern "C" void UtfWin_00635760_host_bridge(OpaqueUtfWinRootRegistry *,
                                            std::uint32_t, bool) {}
#endif

void UtfWin_00635760_set_flag_by_control_id(OpaqueUtfWinRootRegistry *registry,
                                            std::uint32_t control_id,
                                            bool visible) {
#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
  // Enter the byte-exact body through the host bridge, which rebuilds the
  // original __thiscall frame (receiver in ECX, two arguments on the stack).
  // Routing through it keeps a single execution path on this host.
  UtfWin_00635760_host_bridge(registry, control_id, visible);
#else
  OpaqueUtfWinWindow *window =
      utfwin_registry_find_window_by_control_id(registry, control_id);
  if (window != nullptr) {
    window->vtable->set_flag(window, kWinFlagVisible, visible);
  }
#endif
}

void UtfWin_00635760_set_visible_by_control_id(
    OpaqueUtfWinRootRegistry *registry, std::uint32_t control_id,
    bool visible) {
  UtfWin_00635760_set_flag_by_control_id(registry, control_id, visible);
}

} // namespace openspore::reconstruction::wave13_pilot_dispatch_b00
