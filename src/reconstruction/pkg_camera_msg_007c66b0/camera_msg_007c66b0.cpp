#include "camera_msg_007c66b0.hpp"

// Reconstructed body of 0x007c66b0 (App::cCameraManager::HandleMessage).
//
//   0x007c66b0  SUB ESP,0x8 / PUSH ESI / PUSH EDI
//   0x007c66b5  MOV EDI,ECX                      ; receiver
//   0x007c66b7  LEA EAX,[ESP + 0x14]               ; &message id at [ESP+4]
//   0x007c66bb  PUSH EAX
//   0x007c66bc  LEA ECX,[ESP + 0xc]                ; the two-word out slot
//   0x007c66c0  LEA ESI,[EDI+0x60]               ; receiver + 0x60
//   0x007c66c3  PUSH ECX
//   0x007c66c4  MOV ECX,ESI
//   0x007c66c6  CALL 0x00645ed0                  ; chained hash lookup, stdcall 2
//   0x007c66cb  MOV EDX,dword ptr [ESI+0x8]      ; -> receiver + 0x68
//   0x007c66ce  MOV ECX,dword ptr [ESI+0x4]      ; -> receiver + 0x64
//   0x007c66d1  MOV EAX,dword ptr [ESP + 0x8]    ; out slot, first word
//   0x007c66d5  CMP EAX,dword ptr [ECX+EDX*0x4]  ; node == miss sentinel?
//   0x007c66d8  JZ  0x007c66f1                   ; miss -> return false
//   0x007c66da  MOV EDX,dword ptr [EDI]          ; receiver + 0x00, the vptr
//   0x007c66dc  MOV EAX,dword ptr [EAX+0x4]      ; the node's own word
//   0x007c66df  MOV EDX,dword ptr [EDX+0x54]      ; virtual slot at byte 0x54
//   0x007c66e2  PUSH EAX
//   0x007c66e3  MOV ECX,EDI
//   0x007c66e5  CALL EDX
//   0x007c66e8  MOV AL,0x1 / POP EDI / POP ESI / ADD ESP,0x8 / RET 0x4
//   0x007c66f1  XOR AL,AL  / POP EDI / POP ESI / ADD ESP,0x8 / RET 0x4
//
// The third declared parameter is never read; the body only consumes the
// message id slot and RET 0x4 pops exactly one dword, so a second declared
// argument would be a caller-cleaned tail.
//
// Every receiver access below is a DISPLACEMENT and not a member access. The
// machine-derived receiver record for this target enumerates offsets=[0] and is
// bounds_only; the complete listing shows the rest through the EDI alias and the
// ESI chain. Neither witness names a member, so none is written: the subobject
// at receiver+0x60, its two words at receiver+0x64 and receiver+0x68, and the
// dispatch word at receiver+0x00 are all reached as offsets into an opaque
// receiver.

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_CMSG_CDECL __cdecl
#define PKG_CMSG_THISCALL __thiscall
#else
#define PKG_CMSG_CDECL __attribute__((cdecl))
#define PKG_CMSG_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_camera_msg_007c66b0 {

CameraMessagePorts g_camera_message_ports{};

extern "C" bool PKG_CMSG_THISCALL handle_message_007c66b0(
    OpaqueCameraManager* manager, OpaqueWord message_id, void* p_message) {
  (void)p_message;

  // 0x007c66c0 LEA ESI,[EDI + 0x60] - the subobject handed to the lookup.
  std::uint8_t* const registry = reinterpret_cast<std::uint8_t*>(
      reinterpret_cast<std::uintptr_t>(manager) + 0x60);

  // 0x007c66b7 LEA EAX,[ESP + 0x14] / PUSH EAX  -> &message_id, the key.
  // 0x007c66bc LEA ECX,[ESP + 0xc]  / PUSH ECX  -> the out slot, two words.
  // 0x007c66d1 MOV EAX,[ESP + 0x8]               -> its FIRST word, read back.
  // Only the first word is consumed; the out slot is modelled as a bare
  // two-word buffer because the machine fixes its size and this body's read,
  // not the names of its two halves.
  OpaqueWord found[2] = {0u, 0u};
  g_camera_message_ports.registry_lookup_00645ed0(registry, found, &message_id);
  OpaqueMessageNode* const node =
      reinterpret_cast<OpaqueMessageNode*>(found[0]);

  // 0x007c66cb MOV EDX,dword ptr [ESI + 0x8] - the second word of the
  // subobject. ESI is the receiver+0x60 address built at 0x007c66c0, so this
  // word is at receiver+0x68; the machine's own spelling of the read is the one
  // written here, and the header records the two readings of the same word.
  const OpaqueWord count = *reinterpret_cast<const OpaqueWord*>(registry + 0x8);
  // 0x007c66ce MOV ECX,dword ptr [ESI + 0x4] - the first word of the subobject,
  // at receiver+0x64. It holds the bucket array: 0x007c66b0 loads it into ECX
  // and 0x007c66d5 indexes it with a 4-byte scale.
  OpaqueMessageNode* const* const buckets =
      *reinterpret_cast<OpaqueMessageNode* const* const*>(registry + 0x4);

  // 0x007c66d5 CMP EAX,dword ptr [ECX + EDX*0x4] / 0x007c66d8 JZ 0x007c66f1.
  // The helper reports a miss by handing back the element stored one past the
  // count instead of a node, so the comparison is POINTER IDENTITY against
  // that slot and not a null test: a null sentinel still refuses a miss and
  // still admits a real hit.
  OpaqueMessageNode* const miss_sentinel = buckets[count];
  if (node == miss_sentinel) {
    return false;  // 0x007c66f2 XOR AL,AL
  }

  // 0x007c66dc MOV EAX,dword ptr [EAX + 0x4] - a word of the NODE, the object
  // the helper returned. It is not a receiver word, and it is written as the
  // displacement the instruction uses rather than as a member of that node.
  const OpaqueWord index = *reinterpret_cast<const OpaqueWord*>(
      reinterpret_cast<std::uintptr_t>(node) + 0x4);

  // 0x007c66da MOV EDX,dword ptr [EDI]     -> the receiver word at displacement 0
  // 0x007c66df MOV EDX,dword ptr [EDX+0x54] -> one-level read of slot 0x54
  // 0x007c66e2 PUSH EAX / 0x007c66e3 MOV ECX,EDI / 0x007c66e5 CALL EDX
  // The displacement of that word is zero, which the instruction encodes by
  // carrying no immediate at all; it is named rather than spelled as a literal
  // for that reason, and kVtableDisplacement is that zero.
  OpaqueCameraManagerVTable* const vtable = pointer_at(manager, kVtableDisplacement);
  vtable->select_camera_by_index_54(manager, index);
  return true;  // 0x007c66e8 MOV AL,0x1
}

}

#undef PKG_CMSG_CDECL
#undef PKG_CMSG_THISCALL
