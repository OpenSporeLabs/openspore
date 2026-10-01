#include "sim_tool_event_01053d50.hpp"

#if defined(_MSC_VER)
#define PKG_SIM_TOOLEVENT_01053D50_THISCALL __thiscall
#define PKG_SIM_TOOLEVENT_01053D50_CDECL __cdecl
#else
#define PKG_SIM_TOOLEVENT_01053D50_THISCALL __attribute__((thiscall))
#define PKG_SIM_TOOLEVENT_01053D50_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_sim_toolevent_01053d50 {

NativePorts g_sim_toolevent_01053d50_ports{};

// 0x01053d50, the complete 30-instruction body:
//
//   01053d50  SUB ESP,0x40
//   01053d53  PUSH ESI
//   01053d54  PUSH EDI
//   01053d55  MOV EDI,dword ptr [ESP + 0x50]    -> entry+0x08, second stack word
//   01053d59  LEA EAX,[ESP + 0x8]              -> entry-0x40, the frame's base
//   01053d5d  PUSH EAX
//   01053d5e  MOV ESI,ECX                      the receiver
//   01053d60  PUSH EDI
//   01053d61  LEA ECX,[ESP + 0x20]             -> entry-0x30, ECX for the init
//   01053d65  CALL 0x00ad79d0
//   01053d6a  PUSH 0x0
//   01053d6c  LEA ECX,[ESP + 0x1c]             -> entry-0x30, the second word
//   01053d70  PUSH ECX
//   01053d71  PUSH 0x5dce504a
//   01053d76  CALL 0x00b3d4d0
//   01053d7b  MOV ECX,EAX
//   01053d7d  CALL 0x00ae09b0
//   01053d82  MOV EDX,dword ptr [ESI]          the receiver word at +0x00
//   01053d84  MOV EAX,dword ptr [ESP + 0x4c]   -> entry+0x04, first stack word
//   01053d88  MOV EDX,dword ptr [EDX + 0x4c]    the table's word at +0x4c
//   01053d8b  PUSH EDI
//   01053d8c  PUSH EAX
//   01053d8d  MOV ECX,ESI
//   01053d8f  CALL EDX
//   01053d91  LEA ECX,[ESP + 0x18]             -> entry-0x30, the release
//   01053d95  CALL 0x00ad7ad0
//   01053d9a  POP EDI
//   01053d9b  POP ESI
//   01053d9c  ADD ESP,0x40
//   01053d9f  RET 0x8
//
// Two things about the frame are worth stating because they are easy to get
// wrong and both are visible in the listing:
//
//   * the 0x40 the prologue reserves holds the transform at entry-0x30, and
//     0x30 + 0x10 lands exactly on entry-0x08, the bottom of the reservation -
//     the transform's 48 bytes fit with the frame base 16 bytes below them and
//     nothing to spare;
//   * the init call is handed entry-0x30 as its hidden receiver and entry-0x40
//     as its SECOND stack word, so the two are not the same address and not
//     unrelated either: the second is 0x10 below the first. The post call and
//     the release call both reuse entry-0x30.
//
// The receiver is read once, at displacement 0, and it is written as a
// displacement: the record is offsets=[0], bounds_only, and it says where the
// body reached, not which member it found. Nothing is named.
extern "C" void PKG_SIM_TOOLEVENT_01053D50_THISCALL
sim_toolevent_slot8_fun_01053d50(OpaqueToolEventReceiver* receiver,
                                 void* event_argument,
                                 const OpaqueVector3* position) {
  // 01053d50 SUB ESP,0x40 / 01053d53 PUSH ESI / 01053d54 PUSH EDI
  //
  // The 0x40-byte reservation the three callees are given addresses inside. It
  // is modelled as a byte run because nothing in this body interprets it: the
  // body only ever forms addresses into it and hands them on.
  alignas(4) std::uint8_t frame[kFrameReserveBytes]{};

  // 01053d59 LEA EAX,[ESP + 0x8]  -> entry-0x40, pushed as the init's second word
  // 01053d61 LEA ECX,[ESP + 0x20] -> entry-0x30, the init's hidden receiver
  //
  // entry-0x30 is 0x10 above the frame base, and the transform this body talks
  // about is 0x30 bytes wide, so the transform sits at frame+0x10 and ends
  // exactly at the bottom of the 0x40 reservation.
  OpaqueTransform48* const transform = reinterpret_cast<OpaqueTransform48*>(
      frame + kTransformFrameOffset);

  // 01053d5d PUSH EAX / 01053d60 PUSH EDI / 01053d65 CALL 0x00ad79d0
  g_sim_toolevent_01053d50_ports.transform_init_00ad79d0(
      transform, position,
      reinterpret_cast<const OpaqueQuaternion16*>(frame));

  // 01053d6a PUSH 0x0 / 01053d6c LEA ECX,[ESP + 0x1c] -> entry-0x30
  // 01053d70 PUSH ECX / 01053d71 PUSH 0x5dce504a / 01053d76 CALL 0x00b3d4d0
  // 01053d7b MOV ECX,EAX / 01053d7d CALL 0x00ae09b0
  //
  // The group hash and the instance are the two immediates the listing prints,
  // 0x5dce504a and 0x0. The transform handed to the post is the SAME address
  // the init was given, not the frame base.
  g_sim_toolevent_01053d50_ports.object_context_post_00ae09b0(
      g_sim_toolevent_01053d50_ports.cspace_trading_get_00b3d4d0(), 0x5dce504a,
      transform, kObjectContextInstance);

  // 01053d5e MOV ESI,ECX
  // 01053d82 MOV EDX,dword ptr [ESI]
  // 01053d88 MOV EDX,dword ptr [EDX + 0x4c]
  // 01053d8b PUSH EDI / 01053d8c PUSH EAX / 01053d8d MOV ECX,ESI
  // 01053d8f CALL EDX
  //
  // One level, then one word at displacement 0x4c of the table, then the call.
  // `ESI + 0x4c` would be a receiver displacement if the base were the
  // receiver; it is not - the base here is the table the receiver's word 0
  // points at, and 0x4c is 19 pointers into it, which is the slot the SDK label
  // and the neighbouring slot 0x008d86c0's own table both agree on. Pushed
  // right to left: the first stack word is the entry's first argument (EAX,
  // re-read at 0x01053d84), the second is its second (EDI).
  OpaqueToolEventVTable* const table = *reinterpret_cast<
      OpaqueToolEventVTable* const*>(
      reinterpret_cast<const std::uint8_t*>(receiver) + 0x0);
  table->forward_4c(receiver, event_argument, position);

  // 01053d91 LEA ECX,[ESP + 0x18] -> entry-0x30 / 01053d95 CALL 0x00ad7ad0
  //
  // The release is unconditional and its result is discarded: the forward call
  // above returns a word in EAX and the body never reads it, so nothing about
  // the forward's outcome can change whether the release runs.
  g_sim_toolevent_01053d50_ports.transform_release_00ad7ad0(transform);
}

}

#undef PKG_SIM_TOOLEVENT_01053D50_THISCALL
#undef PKG_SIM_TOOLEVENT_01053D50_CDECL
