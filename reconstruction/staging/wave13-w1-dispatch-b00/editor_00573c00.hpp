#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-w1-dispatch-b00 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "wave13-w1-dispatch-b00 requires 32-bit pointers");

// Layout-only forward declarations. The offsets below are the ones the
// disassembly of 0x00573c00 actually touches; nothing else about these types
// is claimed.
struct Opaque573c00Editor;      // Editors::cEditor candidate
struct Opaque573c00Rigblock;    // EditorRigblock candidate
struct Opaque573c00Flagged;     // anything with a flags dword at +0xdc8

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {

// Opaque ports, declared only. Where a body was readable it is summarised in
// the .cpp; where it was not, it stays a port.
extern "C" std::uint8_t __fastcall port_004a60a0_same_kind(void* a, void* b);
extern "C" void* __cdecl port_0047e6c0_query();
extern "C" void __cdecl port_0043a830(int phase);
extern "C" void __cdecl port_0043e2b0();
extern "C" void __cdecl port_004b09b0(Opaque573c00Rigblock** slot,
                                      Opaque573c00Rigblock* value);
extern "C" std::uint8_t __cdecl port_004a2060_is_plain_part(void* part);
extern "C" void __thiscall port_005cc690(void* palette_ui);
extern "C" std::uint8_t __thiscall port_005ca920(Opaque573c00Editor* editor);
extern "C" void __cdecl port_004a88d0(std::uint32_t hashed_tag);
extern "C" void __thiscall port_00573520(Opaque573c00Editor* editor,
                                         Opaque573c00Rigblock* part);

// 0x00573c00
//
//   void __thiscall FUN_00573c00_reconstruct(Opaque573c00Editor* self,
//                                            Opaque573c00Rigblock* part,
//                                            std::uint32_t paint_region);
//
// Observed body, 115 instructions, 364 bytes, 0x00573c00..0x00573d69.
// Receiver is ECX; two dword stack arguments, popped by the callee
// (RET 0x8 at 0x00573d69). Void: the byte written to +0x398 is the only
// result and it lands in memory, not in a register.
extern "C" void __thiscall FUN_00573c00_reconstruct(
    Opaque573c00Editor* self,
    Opaque573c00Rigblock* part,
    std::uint32_t paint_region);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
