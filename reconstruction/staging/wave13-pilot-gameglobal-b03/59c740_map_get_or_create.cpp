#include "59c740_map_get_or_create.hpp"

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

namespace {

inline Opaque59c740TreeNode* AsNode(std::uint32_t raw) {
  return reinterpret_cast<Opaque59c740TreeNode*>(raw);
}

}  // namespace

// 0x0059c740, read in full from program="SporeApp.exe":
// 0x0059c740..0x0059c7ba plus the 3-byte RET, 51 instructions, 125 bytes,
// then cc padding from 0x0059c7bd.
//
//   0x0059c740  mov  eax,[ecx+0xc]        ; node = container.anchor_parent
//   0x0059c743  sub  esp,0x8
//   0x0059c746  push ebp
//   0x0059c747  push esi
//   0x0059c748  lea  esi,[ecx+0x4]        ; candidate = &container.anchor_left
//   0x0059c74b  push edi
//   0x0059c74c  mov  edi,[esp+0x18]       ; edi = the key pointer (stack arg)
//   0x0059c750  mov  edx,esi              ; edx = candidate
//   0x0059c752  test eax,eax
//   0x0059c754  jz   0x0059c76a          ; empty tree: no descent at all
//   0x0059c756  mov  ebp,[edi]            ; ebp = *key
//   0x0059c758  cmp  dword ptr [eax+0x10],ebp
//   0x0059c75b  jc   0x0059c764           ; node.key < *key -> left
//   0x0059c75d  mov  edx,eax              ; else candidate = node
//   0x0059c75f  mov  eax,dword ptr [eax+0x4]
//   0x0059c762  jmp  0x0059c766
//   0x0059c764  mov  eax,dword ptr [eax]  ; left child
//   0x0059c766  test eax,eax
//   0x0059c768  jnz  0x0059c758
//   0x0059c76a  cmp  edx,esi
//   0x0059c76c  jz   0x0059c775          ; candidate is the anchor: absent
//   0x0059c76e  mov  eax,[edi]
//   0x0059c770  cmp  eax,dword ptr [edx+0x10]
//   0x0059c773  jnc  0x0059c7b1          ; *key >= candidate.key: present
//   0x0059c775  ... miss path, 0x0059c79c CALL 0x0059c520 ...
//   0x0059c7b1  pop  edi / pop esi
//   0x0059c7b3  lea  eax,[edx+0x14]
//   0x0059c7b6  pop  ebp
//   0x0059c7b7  add  esp,0x8
//   0x0059c7ba  ret  0x4
//
// The descent is an ascending lower_bound: the left subtree holds larger keys
// and the right subtree smaller ones, because the "node.key < *key" polarity at
// 0x0059c75b sends the search left for larger keys and right, updating the
// candidate, for smaller-or-equal ones. The polarity is the same one
// 0x0059c380 uses at 0x0059c398/0x0059c39d for the same container, which is
// what rules out a descending comparator here.
//
// The key is compared as an unsigned 32-bit value (JC / JNC, no sign
// extension), and the same key value is reloaded from the caller's pointer at
// 0x0059c756, 0x0059c76e and 0x0059c775 rather than kept in a register, so the
// pointer is read three times on the hit path.
extern "C" __attribute__((thiscall)) std::uint32_t*
GameGlobal_0059c740_map_get_or_create(Opaque59c740MapHeader* self,
                                      const std::uint32_t* key) {
  Opaque59c740TreeNode* node = AsNode(self->anchor_parent);
  Opaque59c740TreeNode* candidate =
      reinterpret_cast<Opaque59c740TreeNode*>(&self->anchor_left);

  if (node != nullptr) {  // 0x0059c752 TEST EAX,EAX / JZ 0x0059c76a
    const std::uint32_t wanted = *key;  // 0x0059c756
    for (;;) {
      if (node->key < wanted) {  // 0x0059c758 / 0x0059c75b (unsigned)
        node = AsNode(node->left);
      } else {  // 0x0059c75d MOV EDX,EAX
        candidate = node;
        node = AsNode(node->right);
      }
      if (node == nullptr) {  // 0x0059c766 / 0x0059c768
        break;
      }
    }
  }

  // 0x0059c76a: the candidate is still the anchor, or it is a real node whose
  // key is strictly greater than the searched one.
  if (candidate !=
          reinterpret_cast<Opaque59c740TreeNode*>(&self->anchor_left) &&
      *key >= candidate->key) {  // 0x0059c770 CMP / 0x0059c773 JNC
    // 0x0059c7b3 LEA EAX,[EDX+0x14] - the address of the mapped value.
    return &candidate->value;
  }

  // Miss path, 0x0059c775..0x0059c7ae.
  //
  // 0x0059c777  MOV [ESP+0xc],EAX      keep a private copy of *key
  // 0x0059c77b  MOV byte [ESP+0x18],0  the compiler reuses its own incoming
  //                                    argument slot as scratch and clears the
  //                                    low byte of the stored key pointer
  // 0x0059c780  MOV EAX,[ESP+0x18]
  // 0x0059c784  PUSH EAX               arg4: the masked key pointer
  // 0x0059c785  LEA EAX,[ESP+0x10]     arg3: &key_copy
  // 0x0059c789  PUSH EAX
  // 0x0059c78a  PUSH ECX               arg2 slot, overwritten with the hint
  // 0x0059c78d  MOV [EAX],EDX          0x0059c78b MOV EAX,ESP
  // 0x0059c78f  LEA EDX,[ESP+0x24]     arg1: address of that same slot
  // 0x0059c793  PUSH EDX
  // 0x0059c794  MOV [ESP+0x20],0       a second scratch word, unused after
  // 0x0059c79c  CALL 0x0059c520
  // 0x0059c7a1  MOV EAX,[ESP+0x18]     read the node back out of the slot
  // 0x0059c7a5  ADD EAX,0x14
  const std::uint32_t key_copy = *key;  // 0x0059c775/0x0059c777
  std::uintptr_t slot =
      reinterpret_cast<std::uintptr_t>(key) & ~std::uintptr_t(0xff);
  Opaque59c740TreeNode** out_node =
      reinterpret_cast<Opaque59c740TreeNode**>(&slot);
  OpaquePort_0059c520_insert_with_hint(
      out_node, candidate, &key_copy,
      static_cast<std::uint32_t>(slot) /* 0x0059c780 */);
  Opaque59c740TreeNode* inserted = AsNode(static_cast<std::uint32_t>(slot));
  return &inserted->value;
}

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03
