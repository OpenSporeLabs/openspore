#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "wave13-pilot-gameglobal-b03 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4,
              "wave13-pilot-gameglobal-b03 requires 32-bit pointers");

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

// Opaque node of the red-black tree that 0x0059c740 searches.
//
// Only the five fields this body and its immediate callees actually touch are
// declared, at the offsets the disassembly proves:
//
//   0x0059c764  MOV EAX,dword ptr [EAX]         left child
//   0x0059c75f  MOV EAX,dword ptr [EAX + 0x4]   right child
//   0x0059c758  CMP dword ptr [EAX + 0x10],EBP  key, unsigned 32-bit compare
//   0x0059c7b3  LEA EAX,[EDX + 0x14]            mapped value
//
// 0x0059c380 additionally reads +0x08 (parent) and +0x0c (colour) and compares
// a node against the container's +0x08, which fixes the anchor's identity. The
// declared struct stops there: no ownership, no allocator and no vtable is
// claimed, because SporeApp.exe carries no MSVC RTTI and no vtable for this
// container was located.
struct Opaque59c740TreeNode {
  std::uint32_t left;    // +0x00
  std::uint32_t right;   // +0x04
  std::uint32_t parent;  // +0x08
  std::uint32_t color;   // +0x0c
  std::uint32_t key;     // +0x10
  std::uint32_t value;   // +0x14, a 4-byte handle/intrusive pointer
};

// Receiver of 0x0059c740, laid out only as far as the three bodies that touch
// it prove. This is the shape of an eastl::map<int, T> header, and the field
// offsets and total size are cross-checked against cEditorAnimWorld by
// 0x0059cac0 and 0x0059cb10; the class NAMES are not claimed here.
//
//   0x0059c748  LEA ESI,[ECX + 0x4]      anchor node lives at receiver + 0x04
//   0x0059c740  MOV EAX,dword ptr [ECX + 0xc]   descent starts here
//   0x0059c38b  LEA EAX,[ESI + 0x4]
//   0x0059c520  MOV EAX,dword ptr [ESI + 0x4]
//   0x0059c520  CMP dword ptr [ESI + 0x14],0     element count
//   0x0059c3b5  CMP EAX,dword ptr [ESI + 0x8]    rbegin() node
struct Opaque59c740MapHeader {
  std::uint32_t compare_padding;  // +0x00, never read by these three bodies
  std::uint32_t anchor_left;      // +0x04, begin() node
  std::uint32_t anchor_right;     // +0x08, rbegin() node
  std::uint32_t anchor_parent;    // +0x0c, the tree root
  std::uint32_t anchor_color;     // +0x10
  std::uint32_t size;             // +0x14
  std::uint32_t allocator;        // +0x18, never read by these three bodies
};
static_assert(sizeof(Opaque59c740MapHeader) == 0x1c,
              "0x0059c740 receiver is a 0x1c-byte container header");

// Opaque port for 0x0059c520, the out-of-line insert step reached only when the
// key is absent.
//
// Observed call shape at 0x0059c79c (four stack words, callee cleanup, ECX
// unused by the caller):
//   arg1  &slot      the address of a caller-owned 4-byte cell that the callee
//                     writes with the resulting node pointer
//                     (0x0059c5d1 MOV EAX,[ESP+0x14]; 0x0059c5da MOV [EAX],EDX,
//                      where [ESP+0x14] is arg1 once 0x0059c380 has popped its
//                      0xc bytes)
//   arg2  hint       the lower-bound candidate node, 0x0059c750 MOV EDX,ESI
//   arg3  &key_copy  address of a caller-owned dword holding *pKey,
//                     0x0059c785 LEA EAX,[ESP+0x10]
//   arg4  masked     the key pointer with its low byte cleared,
//                     0x0059c77b MOV byte ptr [ESP+0x18],0x0
// The callee returns the node in EAX as well (0x0059c5d1/0x0059c5e0), and its
// body also reads arg4 as a pointer (0x0059c59c CMP EDX,[ECX]); what the mask
// is for is unresolved and is listed in the metadata sidecar.
extern "C" void OpaquePort_0059c520_insert_with_hint(
    Opaque59c740TreeNode** out_node, Opaque59c740TreeNode* hint,
    const std::uint32_t* key_copy, std::uint32_t masked_key_pointer);

// 0x0059c740 - find-or-create accessor of the container reached through
// ECX, keyed by the 32-bit value at the single callee-cleaned stack argument.
//
//   0x0059c74c  MOV EDI,dword ptr [ESP + 0x18]   the key pointer
//   0x0059c7ae  RET 0x4                          pops that one word
//   0x0059c7b3  LEA EAX,[EDX + 0x14]            hit path return
//   0x0059c7a5  ADD EAX,0x14                     miss path return
//
// The return is a pointer to the mapped value, not the value: 0x0059caf2
// (MOV EAX,dword ptr [EAX]) and 0x0059cb4a (MOV ESI,dword ptr [EAX]) both
// dereference it once, and 0x0059c986 passes it straight to 0x00572680 as ECX.
extern "C" __attribute__((thiscall)) std::uint32_t*
GameGlobal_0059c740_map_get_or_create(Opaque59c740MapHeader* self,
                                      const std::uint32_t* key);

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03
