#pragma once

// Target VA    : 0x0067dc80
// Ghidra symbol: App::IMessageManager::Get   (see "NAMING" below -- not
//                                            corroborated by the machine code)
// Body         : 0x0067dc80 .. 0x0067dc9b inclusive, 11 instructions, 30
//                bytes, a single RET site at 0x0067dc9b.
//
// ---------------------------------------------------------------------------
// THE MACHINE FACTS THIS PACKAGE IS BUILT ON
// ---------------------------------------------------------------------------
// 30 bytes read live from SporeApp.exe 3.1.0.22 at 0x0067dc80:
//
//   56 8b f1 e8 88 fe ff ff f6 44 24 08 01 74 09 56
//   e8 eb 96 8c 00 83 c4 04 8b c6 5e c2 04 00
//
//   0067dc80  PUSH ESI
//   0067dc81  MOV  ESI,ECX
//   0067dc83  CALL 0x0067db10
//   0067dc88  TEST byte ptr [ESP + 0x8],0x1
//   0067dc8d  JZ   0x0067dc98
//   0067dc8f  PUSH ESI
//   0067dc90  CALL 0x00f47380
//   0067dc95  ADD  ESP,0x4
//   0067dc98  MOV  EAX,ESI
//   0067dc9a  POP  ESI
//   0067dc9b  RET  0x4
//
// The four facts every line of the .cpp rests on, each traceable to the bytes:
//
//   1. The complete-object destructor at 0x0067db10 runs UNCONDITIONALLY, at
//      0x0067dc83, before the flag is read at all.
//   2. The flag is read as a BYTE at [ESP+0x8] -- not [ESP+0x4] -- because the
//      CALL at 0x0067dc83 has already pushed a return address onto this frame.
//      The frame at 0x0067dc88 is: saved ESI, return address, argument.
//   3. Exactly ONE bit of that byte is examined: bit 0 (TEST ... ,0x1 ->
//      encoding f6 44 24 08 01, TEST r/m8,imm8). The other 31 bits of the
//      4-byte argument slot are never read by this body.
//   4. On the bit-0-set path only, the receiver is passed to 0x00f47380 and
//      then MOV EAX,ESI runs on BOTH paths, so the receiver is returned in EAX
//      whether or not the release happened.
//
// ---------------------------------------------------------------------------
// ABI (all of it read off the bytes above)
// ---------------------------------------------------------------------------
//   architecture        x86-32
//   calling convention  __thiscall, callee stack cleanup
//   hidden receiver     ECX (a dword pointer; MOV ESI,ECX spills it to ESI and
//                       leaves ECX intact so the following call is still thiscall
//                       on the same object)
//   stack argument 0    4 bytes, callee-cleaned. RET 0x4 pops exactly one dword
//                       and the same slot is the one tested at 0x0067dc88.
//   return              EAX, the receiver itself (MOV EAX,ESI at 0x0067dc98)
//   saved registers     ESI
//
// The Ghidra decompilation of this address reports "return in_ECX" and
// "WARNING: Unknown calling convention". That is a decompiler artifact and the
// disassembly is authoritative: there is an explicit MOV EAX,ESI immediately
// before POP ESI / RET 0x4.
//
// ---------------------------------------------------------------------------
// NAMING: why this package does not call itself "Get"
// ---------------------------------------------------------------------------
// The SDK symbol table labels 0x0067dc80 "App::IMessageManager::Get". The
// machine body is the MSVC scalar deleting-destructor wrapper
//
//     void* __thiscall T::~T(int deleting_destructor_flag)
//     { T::~T(); if (flag & 1) release(this); return this; }
//
// and nothing in it reads like a getter. Supporting observations, all live:
//   * RET 0x4 -- exactly one callee-cleaned dword argument;
//   * TEST byte [ESP+8],1 -- the deleting-destructor flag;
//   * CALL 0x0067db10 unconditionally, then a release of `this` on bit 0, then
//     `this` in EAX;
//   * 0x0067db10 is unambiguously a destructor: it installs an SEH frame
//     (handler 0x0120bf8e via FS:[0]), writes the owning class's vptrs
//     0x01401798 / 0x01401790 into [ESI] / [ESI+0x4], tears down the members at
//     [ESI+0x14] and [ESI+0x20], invokes slot +8 of the base subobject at
//     [ESI+0xc], then downshifts the vptrs to 0x013f3a68 / 0x013ef094 and
//     returns;
//   * 0x00f47380 is a null-guarded release: MOV EAX,[ESP+4]; TEST EAX,EAX; JZ;
//     MOV ECX,[0x016c8b44]; PUSH EAX; CALL 0x009276c0; RET -- it loads the
//     process-global manager 0x016c8b44 and tail-calls 0x009276c0, so it is the
//     process memory manager and NOT the CRT operator delete;
//   * reading 0x01401790..0x014017bf (48 bytes) returns 80 dc 67 00 at 0x01401798,
//     i.e. this address sits in that vftable at +0x8 from 0x01401790, which is
//     where MSVC places a class's first virtual entry.
//
// So the reconstruction models the OBSERVED BODY, not the SDK label. Whether
// the SDK name is simply wrong, or the symbol table conflated the slot-0
// destructor with a separate "Get", is NOT settled by anything in this
// repository and is carried as an open question, not decided here.
//
// ---------------------------------------------------------------------------
// WHAT IS NOT CLAIMED
// ---------------------------------------------------------------------------
//   * No class name. The owner type below is opaque and is named only so the
//     receiver has a type; it is not a recovered class definition.
//   * No field identity. The offsets it is sized from (>= 0x24) were observed
//     through the CALLEE 0x0067db10, never through this body, which reads no
//     field of its own.
//   * No caller. The xref export records no incoming call edge; the only
//     reference to this address is the data entry at 0x01401798. Under what
//     conditions a caller passes 1 rather than 0 for the flag is unestablished.
//   * No runtime validation. No original-process trace exists in this
//     repository, so nothing here has been observed executing.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-app-imessage-manager-dtor requires an x86-32 target"
#endif

#if !defined(__GNUC__) && !defined(__clang__)
#error "pkg-app-imessage-manager-dtor's naked transcription is written for the GNU/Clang i386 attribute syntax"
#endif

// The convention macros. PKG_IMSG_NAKED_THISCALL is the one the reconstructed
// entry point carries: it is the single token that lets the entry point be both
// a byte-faithful naked body and a normally declarable prototype.
#define PKG_IMSG_THISCALL __attribute__((thiscall))
#define PKG_IMSG_CDECL __attribute__((cdecl))
#define PKG_IMSG_NAKED_THISCALL __attribute__((naked, thiscall))

namespace openspore::reconstruction::pkg_app_imessage_manager_dtor {

using OpaqueWord = std::uint32_t;

// Extent of the owned object, sized only so the receiver has a type. The
// highest member offset observed anywhere in its teardown path is 0x20 (read
// and nulled by 0x0067db10), so the object is at least 0x24 bytes. Every byte
// below 0x20 is opaque: this package names no member and recovers no layout.
struct alignas(4) OpaqueMessageManagerOwner {
  std::uint8_t opaque[0x20];
  OpaqueWord highest_observed_member_offset_20;
};

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(OpaqueWord) == 4, "target words are 32-bit");
static_assert(sizeof(OpaqueMessageManagerOwner) == 0x24,
              "owner covers the highest member offset observed through 0x0067db10");

// 0x0067db10 -- the callee at 0x0067dc83. thiscall, NO stack arguments, NO
// return value, terminates with a plain RET. Installs an SEH frame, tears the
// owning class down and forwards to the base subobject.
using CompleteDtorPort = void(PKG_IMSG_THISCALL*)(OpaqueMessageManagerOwner*);

// 0x00f47380 -- the callee at 0x0067dc90. cdecl, ONE stack argument, no return
// value, CALLER-cleaned (the call site drops it with ADD ESP,4). Null-guards its
// own argument, then loads the process-global manager 0x016c8b44 and tail-calls
// 0x009276c0.
using GlobalFreePort = void(PKG_IMSG_CDECL*)(const void*);

struct MessageManagerDtorPorts {
  CompleteDtorPort complete_dtor_0067db10 = nullptr;
  GlobalFreePort global_free_00f47380 = nullptr;
};

extern MessageManagerDtorPorts g_imessage_manager_dtor_ports;

// The reconstructed entry point: the instruction sequence of 0x0067dc80 ..
// 0x0067dc9b, one instruction per machine instruction, with the two call
// targets routed through the injectable ports.
extern "C" void* PKG_IMSG_THISCALL
get_0067dc80(OpaqueMessageManagerOwner* self, OpaqueWord deleting_flag);

// The same semantics in ordinary C++, for the behavioural model test. The
// arguments are passed on the stack by the caller rather than popped by the
// callee, so this is a statement about behaviour, not about the stack
// discipline; `get_0067dc80` is what carries the RET 0x4.
extern "C" void* PKG_IMSG_CDECL
app_imessage_manager_delete_dispatch_0067dc80(OpaqueMessageManagerOwner* self,
                                              OpaqueWord deleting_flag);

}  // namespace openspore::reconstruction::pkg_app_imessage_manager_dtor
