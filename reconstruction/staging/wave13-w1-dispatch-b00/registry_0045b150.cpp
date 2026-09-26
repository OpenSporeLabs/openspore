#include "registry_0045b150.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {
namespace {

// Receiver field offsets, each proven by a named instruction of this body.
constexpr std::size_t kMap = 0x8;           // 0x0045b164  add ecx, 8
constexpr std::size_t kBuckets = 0xc;       // 0x0045b17e  mov eax, [edx + 4]
constexpr std::size_t kBucketCount = 0x10;  // 0x0045b178  mov ecx, [eax + 8]

// Offsets that belong to the two opaque ports rather than to this body. They
// are recorded here so the port contracts in the comment block below are
// checkable against the same constants this file uses.
[[maybe_unused]] constexpr std::size_t kSize = 0x14;  // 0x0045b48c in 0x0045b3e0
[[maybe_unused]] constexpr std::size_t kNodeKey = 0x0;  // 0x0042199f
[[maybe_unused]] constexpr std::size_t kNodeNext = 0x8;  // 0x0042198c

constexpr std::size_t kNodeValue = 0x4;  // 0x0045b1b6  mov edx, [ecx + 4]

constexpr std::size_t kSlotVtable = 0x0;
constexpr std::size_t kSlotPreErase = 0xc;  // 0x0045b1c6  mov eax, [edx + 0xc]
constexpr std::uint32_t kPreEraseFlag = 1;  // 0x0045b1bc  push 0x1

}  // namespace

// 0x0045b150 -- 179 bytes, 65 instructions, read live in full.
//
//   0x0045b150  55              push ebp
//   0x0045b151  8bec            mov  ebp, esp
//   0x0045b153  83ec 78         sub  esp, 0x78
//   0x0045b156  894d 88         mov  dword ptr [ebp - 0x78], ecx
//   0x0045b159  8d45 08         lea  eax, dword ptr [ebp + 8]
//   0x0045b15c  50              push eax
//   0x0045b15d  8d4d f8         lea  ecx, dword ptr [ebp - 8]
//   0x0045b160  50              push ecx
//   0x0045b161  8b4d 88         mov  ecx, dword ptr [ebp - 0x78]
//   0x0045b164  83c1 08         add  ecx, 8
//   0x0045b167  e8e4fcffff     call 0x00421950
//   0x0045b16c..0x0045b19b     rebuild the bucket-array end pointer and the
//                               free-list head it points at
//   0x0045b19b  8b45 f8         mov  eax, dword ptr [ebp - 8]
//   0x0045b19e  33c9           xor  ecx, ecx
//   0x0045b1a0  3b45 ec         cmp  eax, dword ptr [ebp - 0x14]
//   0x0045b1a3  0f94c1         setnz cl
//   0x0045b1a6  0fb6d1         movzx edx, cl
//   0x0045b1a9  85d2           test edx, edx
//   0x0045b1ab  0f84 30        jz 0x0045b1fd
//   ...                           pre-erase hook, then the erase call
//   0x0045b1fd  8be5           mov  esp, ebp
//   0x0045b1ff  5d             pop  ebp
//   0x0045b200  c2 0400        ret 4
//
// Contract: look the key up in the hash map embedded at receiver + 0x8; if
// and only if the key was actually present, run vtable slot +0xc with the
// literal 1 on the value stored at node + 0x4, then erase the node.
//
// The "was it present" test is the interesting part and it is exact.
// 0x00421950 returns {node, bucket_slot} on a hit and, on a miss,
// {*(buckets + bucketCount), buckets + bucketCount} -- the sentinel slot one
// past the bucket array, whose content is the free-list head. This function
// recomputes that same sentinel at 0x0045b181 (LEA ECX,[EAX + ECX*4] over
// buckets and bucket count) and dereferences it at 0x0045b18a, then compares
// the lookup's first word against it at 0x0045b1a0. A miss therefore compares
// the free-list head with itself and skips; a hit compares a live node against
// the free-list head, which cannot be equal, and proceeds.
//
// The three callees are opaque ports, but their contracts were read:
//   0x00421950  __thiscall(map, out, keyPtr), RET 0x8. Divides *keyPtr by the
//               bucket count at map + 0x8, indexes the bucket array at
//               map + 0x4, then walks node + 0x8 until *keyPtr == node + 0x0.
//   0x0045b3e0  __thiscall(map, out, node, bucketSlot), RET 0xc. Scans forward
//               from bucketSlot for the next non-empty bucket, unlinks node
//               from that chain, calls 0x0045b6f0(node), decrements map + 0xc,
//               and returns {nextHead, nextSlot}.
//   the value hook at 0x0045b1c6 is a vtable slot +0xc call with ECX = node's
//               value and the literal 1 pushed. Its concrete callee is NOT
//               resolved: the node's vtable is only reachable at runtime.
//
// The eight bytes written through the `sub esp, 8` at 0x0045b1cb are the two
// trailing outgoing arguments of the 0x0045b3e0 call, not exception-handling
// scaffolding: 0x0045b3e0 reads [EBP + 0xc] as the node and [EBP + 0x10] as
// the bucket slot, and at the call site (ESP + 8) and (ESP + 0xc) hold exactly
// the pair produced by 0x00421950. Ghidra renders this as a `__try` scope
// record with a handler at 0x0045b16c; that reading is not supported by the
// callee's own argument reads and is not used here.
//
// Receiver provenance: 0x005872f4 in Editors::cEditor::SetActiveMode does
// `call 0x00401050; mov ecx, eax; call 0x0045b150` and 0x00401050 is
// `mov eax, [0x015d0c14]; ret`. The receiver is therefore that global, whose
// file-image dword reads 00000000, and the argument is the value the caller
// pushed, e.g. cEditor + 0x278 at 0x005872dc (the ModAPI header records
// cEditor +0x278 as `mPlayModeEntryEffectID`). 0x0045ac20 walks the same
// map at the same +0x8 offset, so the two share one registry.

extern "C" void __thiscall FUN_0045b150_reconstruct(
    Opaque45b150Registry* self,
    std::uint32_t key) {
  // 0x0045b159..0x0045b167: the address of the stack argument doubles as the
  // key, which 0x00421950 dereferences (0x0042199b  mov ecx, [edx]).
  Lookup45b150Pair hit{};
  const Lookup45b150Pair found = port_00421950_find(
      reinterpret_cast<Opaque45b150Registry*>(
          reinterpret_cast<std::uint8_t*>(self) + kMap),
      &hit, &key);

  // 0x0045b178..0x0045b18c: buckets + bucketCount * 4, then the free-list
  // head stored in that sentinel slot.
  auto* const buckets = *reinterpret_cast<void**>(
      reinterpret_cast<std::uint8_t*>(self) + kBuckets);
  const auto bucket_count = *reinterpret_cast<std::uint32_t*>(
      reinterpret_cast<std::uint8_t*>(self) + kBucketCount);
  void* const sentinel_slot = static_cast<std::uint8_t*>(buckets) +
                              bucket_count * sizeof(std::uint32_t);
  void* const free_list_head = *reinterpret_cast<void**>(sentinel_slot);

  // 0x0045b1a0..0x0045b1ab: only a real hit passes this test.
  if (found.node == free_list_head) {
    return;  // 0x0045b1ab  jz 0x0045b1fd
  }

  // 0x0045b1ad..0x0045b1b9: the value dword of the hit node.
  auto* const payload = *reinterpret_cast<Opaque45b150Payload**>(
      reinterpret_cast<std::uint8_t*>(found.node) + kNodeValue);

  // 0x0045b1bc..0x0045b1c9: PUSH 1; MOV EAX,[payload]; MOV EDX,[EAX + 0xc];
  // MOV ECX, payload; CALL EAX. The slot is loaded by hand in the binary; the
  // port keeps the same shape so the unresolved callee stays visible.
  auto* const payload_vtable =
      *reinterpret_cast<void***>(reinterpret_cast<std::uint8_t*>(payload) +
                                 kSlotVtable);
  if (payload_vtable != nullptr) {
    auto pre_erase = reinterpret_cast<void (*)(std::uint32_t)>(
        payload_vtable[kSlotPreErase / sizeof(void*)]);
    pre_erase(kPreEraseFlag);
  }

  // 0x0045b1cb..0x0045b1f8: the two trailing arguments of the erase call are
  // materialised in the outgoing-args area and the first argument is pushed
  // last, so the callee sees (out, node, bucketSlot) with ECX = receiver + 8.
  Lookup45b150Pair out{};
  port_0045b3e0_erase(
      reinterpret_cast<Opaque45b150Registry*>(
          reinterpret_cast<std::uint8_t*>(self) + kMap),
      &out, found.node, found.bucket_slot);
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
