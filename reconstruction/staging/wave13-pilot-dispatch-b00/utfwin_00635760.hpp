#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::wave13_pilot_dispatch_b00 {

// ---------------------------------------------------------------------------
// Opaque types
// ---------------------------------------------------------------------------

// 0x00634dc0 (the single callee of the target) is __thiscall and starts with
// "ADD ECX,0x14" followed by "CALL 0x008100c0", i.e. the receiver owns a
// 32-bit-element vector at +0x14. The target forwards its own incoming ECX
// unchanged into that callee, so the target shares the receiver type. No other
// member of this type is observed anywhere in the target's body.
struct OpaqueUtfWinRootRegistry;

// The window interface whose vtable slot +0x7C the target dispatches through.
// Only the slots that were read out of SporeApp.exe are named; every other slot
// stays an opaque pointer. Offsets are asserted below.
struct OpaqueUtfWinWindow;

// ---------------------------------------------------------------------------
// UTFWin::WindowFlags (Spore-ModAPI Spore/UTFWin/IWindow.h)
// kWinFlagVisible=0x1, kWinFlagEnabled=0x2, kWinFlagIgnoreMouse=0x10.
// The three values are observed as the first argument of the +0x7C dispatch in
// 0x00635760 (1), 0x006357c0 (2) and 0x00635600/0x00635680/0x00635580 (0x10).
// ---------------------------------------------------------------------------
enum UtfWinWindowFlag : std::uint32_t {
  kWinFlagVisible = 0x1u,
  kWinFlagEnabled = 0x2u,
  kWinFlagIgnoreMouse = 0x10u,
};

// ---------------------------------------------------------------------------
// Vtable layout, cross-checked against the SDK slot comments in IWindow.h.
// ---------------------------------------------------------------------------
struct OpaqueUtfWinWindowVtable {
  void *slot_00; // +0x00
  void *slot_04; // +0x04
  void *slot_08; // +0x08

  // 0x00635810 / 0x00635850: vtable+0x0C is called with a single uint32 type
  // id (0x8ED27E7A there, IWindow::TYPE 0xEEEE8218 in the callee 0x00634dc0)
  // and its result is used as the receiver of further window slots.
  void *(*get_object_by_type)(void *, std::uint32_t); // +0x0C

  void *slot_10; // +0x10
  void *slot_14; // +0x14
  void *slot_18; // +0x18

  // 0x00634dc0 @ 0x00634dfe: vtable+0x1C, no argument, compared against the
  // requested control id. SDK: IWindow::GetControlID at 0x1Ch.
  std::uint32_t (*get_control_id)(const void *); // +0x1C

  // 0x00635850 @ (vtable+0x20) with no argument. SDK: GetCommandID at 0x20h.
  std::uint32_t (*get_command_id)(const void *); // +0x20

  void *slot_24; // +0x24

  // 0x006357c0 / 0x00635890: vtable+0x28, no argument, tested against bit 1.
  // SDK: GetFlags at 0x28h.
  std::uint32_t (*get_flags)(const void *); // +0x28

  void *slots_2c_58[12]; // +0x2C .. +0x58

  // 0x00635600/0x00635680/0x00635580: vtable+0x5C with one 32-bit colour
  // (0xFFFFFFFF or 0xA0A0A0A0). SDK: SetShadeColor at 0x5Ch.
  void (*set_shade_color)(void *, std::uint32_t); // +0x5C

  void *slots_60_78[7]; // +0x60 .. +0x78

  // THE SLOT THE TARGET DISPATCHES. 0x00635760 reads vtable+0x7C, overwrites
  // the first stack argument with 1 and tail-jumps with ECX = window.
  // 0x006357c0 calls it with (2, bool); 0x00635600 calls it with (2, v) and
  // (0x10, !v); 0x006358c0 calls it with (1,1) and (1,0).
  // SDK: IWindow::SetFlag(WindowFlags, bool) at 0x7Ch.
  void (*set_flag)(void *, UtfWinWindowFlag, bool); // +0x7C

  void *slots_80_8c[4]; // +0x80 .. +0x8C

  // 0x00635600/0x00635680/0x00635580: vtable+0x90, no argument, called last.
  // SDK: IWindow::Invalidate at 0x90h.
  std::int32_t (*invalidate)(void *); // +0x90

  void *slots_94_ec[23]; // +0x94 .. +0xEC

  // 0x00634dc0 @ 0x00634e0f: vtable+0xF0 called with (controlId, 1) and its
  // non-null result returned. SDK: IWindow::FindWindowByID at 0xF0h, whose
  // second parameter defaults to true.
  void *(*find_window_by_id)(void *, std::uint32_t, bool); // +0xF0
};

struct OpaqueUtfWinWindow {
  OpaqueUtfWinWindowVtable *vtable;
};

// The slot offsets below are evidence for the 32-bit layout, so they are only
// asserted on a 32-bit target. The struct itself is pointer-width agnostic.
#if defined(__i386__) || defined(_M_IX86)
static_assert(offsetof(OpaqueUtfWinWindowVtable, get_object_by_type) == 0x0C,
              "vtable+0x0C is the type query observed in 0x00635810");
static_assert(offsetof(OpaqueUtfWinWindowVtable, get_control_id) == 0x1C,
              "vtable+0x1C is GetControlID, compared in 0x00634dc0");
static_assert(offsetof(OpaqueUtfWinWindowVtable, get_flags) == 0x28,
              "vtable+0x28 is GetFlags, tested in 0x006357c0");
static_assert(offsetof(OpaqueUtfWinWindowVtable, set_shade_color) == 0x5C,
              "vtable+0x5C is SetShadeColor, used in 0x00635600");
static_assert(offsetof(OpaqueUtfWinWindowVtable, set_flag) == 0x7C,
              "vtable+0x7C is the slot the target dispatches through");
static_assert(offsetof(OpaqueUtfWinWindowVtable, invalidate) == 0x90,
              "vtable+0x90 is Invalidate, used in 0x00635600");
static_assert(offsetof(OpaqueUtfWinWindowVtable, find_window_by_id) == 0xF0,
              "vtable+0xF0 is FindWindowByID, used in 0x00634dc0");
static_assert(sizeof(void *) == 4, "the target is an x86-32 reconstruction");
#endif

// ---------------------------------------------------------------------------
// Opaque port: the target's single direct callee.
//   0x00634dc0  __thiscall, RET 0x4, ECX = registry
// Scans the vector at registry+0x14; for each non-null element it calls
// element->vtable[0x0C](0xEEEE8218) (UTFWin::IWindow::TYPE, read from
// Spore-ModAPI Spore/UTFWin/IWindow.h:91) and then either returns the element's
// own window when window->GetControlID() == controlId, or returns
// window->FindWindowByID(controlId, true) when that is non-null. Returns null
// when the vector is empty or nothing matches.
//
// C linkage so the byte-exact body below can call it by its literal name.
// ---------------------------------------------------------------------------
extern "C" OpaqueUtfWinWindow *
utfwin_registry_find_window_by_control_id(OpaqueUtfWinRootRegistry *registry,
                                          std::uint32_t control_id);

// ---------------------------------------------------------------------------
// Target: 0x00635760
//   11 instructions, 0x00635760..0x00635781, 34 bytes, no frame, no globals.
//   __thiscall (RET 0x8, this forwarded unchanged into ECX-only callee
//   0x00634dc0), void return, two 4-byte stack arguments.
//   Order of operations, exactly as emitted:
//     arg0 = [ESP+4]                     control id
//     arg1 = [ESP+8]                     flag value
//     EAX  = this->find_window(arg0)
//     if (EAX == 0) -> RET 0x8
//     EDX  = EAX->vtable[0x7C]
//     [ESP+4] = 1                        first argument replaced by kVisible
//     ECX  = EAX
//     JMP EDX                            tail transfer, no frame to unwind
// ---------------------------------------------------------------------------
// Original ABI: __thiscall, receiver in ECX, RET 0x8. The declaration below
// is plain cdecl because clang's i386 Linux __thiscall models the callee stack
// pop but not the ECX receiver, which makes any C++ caller of it unreliable.
// The emitted body is identical either way and host_bridge below stages the
// original register and stack layout before entering it.
extern "C" void
UtfWin_00635760_set_flag_by_control_id_raw(OpaqueUtfWinRootRegistry *,
                                           std::uint32_t, bool);

// Host bridge, not part of the original body. Linux i386 clang has no
// __thiscall, so a __thiscall function cannot be called from C++ there. This
// entry stages the exact __thiscall frame (receiver in ECX, two arguments on
// the stack) and calls the byte-exact body above, whose own RET 8 balances it.
extern "C" void UtfWin_00635760_host_bridge(OpaqueUtfWinRootRegistry *,
                                            std::uint32_t, bool);

// Original ABI: __thiscall.
void UtfWin_00635760_set_flag_by_control_id(OpaqueUtfWinRootRegistry *,
                                            std::uint32_t, bool);

// The recovered semantics: the flag argument of the target is always
// kWinFlagVisible; the second parameter is the boolean value written into it.
// Original ABI: __thiscall.
void UtfWin_00635760_set_visible_by_control_id(OpaqueUtfWinRootRegistry *,
                                               std::uint32_t, bool);

} // namespace openspore::reconstruction::wave13_pilot_dispatch_b00
