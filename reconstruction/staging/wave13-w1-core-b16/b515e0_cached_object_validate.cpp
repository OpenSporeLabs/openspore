#include "b515e0_cached_object_validate.hpp"

namespace openspore::reconstruction::wave13_w1_core_b16 {

// Storage backing the two observed globals so the translation unit is
// self-contained. Both read as zero in the shipped image; the model test
// drives their values.
static std::uint32_t g_guard_0167ecd0 = 0;
static std::uint32_t g_cached_0167ecd4 = 0;

std::uint32_t* const kGuardGlobal_0167ecd0 = &g_guard_0167ecd0;
std::uint32_t* const kCachedObjectGlobal_0167ecd4 = &g_cached_0167ecd4;

// The four call ports plus the unused singleton accessor stay undefined here on
// purpose: they are the opaque boundary of this reconstruction, and the model
// test supplies counting doubles for them.

// 0x00b515e0 - validate the process-wide cached object, rebuilding it when it
// is absent or stale, and latch the rebuild on the receiver.
//
// Exact instruction listing, from the live 94-byte read at 0x00b515e0 followed
// by the usual cc pad:
//
//   0x00b515e0  83 3d d0 ec 67 01 00   cmp dword ptr [0x0167ecd0], 0
//   0x00b515e7  57                     push edi
//   0x00b515e8  8b f9                  mov edi, ecx
//   0x00b515ea  74 50                  jz  0x00b5163c
//   0x00b515ec  a1 d4 ec 67 01         mov eax, dword ptr [0x0167ecd4]
//   0x00b515f1  85 c0                  test eax, eax
//   0x00b515f3  74 3e                  jz  0x00b51633
//   0x00b515f5  56                     push esi
//   0x00b515f6  8b 70 1c               mov esi, dword ptr [eax + 0x1c]
//   0x00b515f9  e8 52 bd fe ff         call 0x00b3d350
//   0x00b515fe  39 46 34               cmp dword ptr [esi + 0x34], eax
//   0x00b51601  0f 95 c0               setnz al
//   0x00b51604  84 c0                  test al, al
//   0x00b51606  75 1c                  jnz 0x00b51624
//   0x00b51608  e8 43 bd fe ff         call 0x00b3d350
//   0x00b5160d  8b 48 24               mov ecx, dword ptr [eax + 0x24]
//   0x00b51610  8b 01                  mov eax, dword ptr [ecx]
//   0x00b51612  8b 50 0c               mov edx, dword ptr [eax + 0xc]
//   0x00b51615  ff d2                  call edx
//   0x00b51617  8b 4e 3c               mov ecx, dword ptr [esi + 0x3c]
//   0x00b5161a  3b 48 08               cmp ecx, dword ptr [eax + 0x8]
//   0x00b5161d  0f 95 c0               setnz al
//   0x00b51620  84 c0                  test al, al
//   0x00b51622  74 05                  jz  0x00b51629
//   0x00b51624  e8 c7 e1 ff ff         call 0x00b4f7f0
//   0x00b51629  83 3d d4 ec 67 01 00   cmp dword ptr [0x0167ecd4], 0
//   0x00b51630  5e                     pop esi
//   0x00b51631  75 09                  jnz 0x00b5163c
//   0x00b51633  e8 b8 fc ff ff         call 0x00b512f0
//   0x00b51638  c6 47 30 01            mov byte ptr [edi + 0x30], 1
//   0x00b5163c  5f                     pop edi
//   0x00b5163d  c3                     ret
//
// Invariants the reconstruction preserves:
//
//  1. Global 0x0167ecd0 is a master guard. Null means the whole call is a
//     no-op, and the +0x30 latch is deliberately not written on that path.
//  2. Global 0x0167ecd4 null means "not built": the lazy builder runs and the
//     +0x30 latch is set. The two identity checks are skipped entirely.
//  3. First identity check: raw pointer comparison of [ESI + 0x34] against the
//     cGameInputManager accessor result. The field is the LEFT operand, which
//     is the reverse of the second check.
//  4. Second identity check: runs only when the first passed. It enters
//     vtable slot +0x0c of [cGameInputManager + 0x24] with ECX as that
//     sub-object and no stack argument, then compares [ESI + 0x3c] against
//     [+0x08] of the returned pointer.
//  5. Either mismatch funnels into the release port, which unconditionally
//     leaves global 0x0167ecd4 null. The three instructions after it re-test
//     that global, so a release is always followed by a rebuild inside the same
//     call, which in turn always sets the +0x30 latch.
//  6. When both checks pass the latch is not written at all. There is no other
//     side effect on the receiver.
//
// Both conditional jumps that reach the release port therefore have the same
// polarity: stale, not fresh, invalidates.
//
// The one detail the C++ cannot spell literally is that the two comparisons
// are pointer-identity tests on values read through the cached object's +0x1c
// sub-object pointer. The struct above models that indirection explicitly
// rather than folding it into a flat layout, so the model test can drive each
// of the two identity fields independently.

extern "C" void SimCachedObjectValidate_00b515e0(ObservedReceiverB515e0* self) {
  if (*kGuardGlobal_0167ecd0 == 0) {
    // 0x00b515ea JZ 0x00b5163c -> POP EDI / RET.
    return;
  }

  std::uint32_t* const cached = reinterpret_cast<std::uint32_t*>(
      *kCachedObjectGlobal_0167ecd4);
  if (cached == nullptr) {
    // 0x00b515f3 JZ 0x00b51633 -> build on demand, latch, return.
    port_00b512f0_ensureCachedObjectBuilt();
    self->field_30_rebuilt_latch = 1;
    return;
  }

  // 0x00b515f6: MOV ESI, dword ptr [EAX + 0x1c].
  const ObservedCachedObjectB515e0* const obj =
      reinterpret_cast<const ObservedCachedObjectB515e0*>(cached);
  const ObservedCachedSubobjectB515e0* const tracked = obj->field_1c_subobject;

  // 0x00b515f9 CMP ... / SETNZ AL / TEST AL,AL / JNZ 0x00b51624.
  const std::uint32_t current_manager =
      reinterpret_cast<std::uintptr_t>(port_00b3d350_gameInputManagerGet());
  const bool manager_mismatch =
      tracked->field_34_recorded_manager != current_manager;

  bool subid_mismatch = false;
  if (!manager_mismatch) {
    // 0x00b51608..0x00b5161d. The vtable is re-read from the accessor result on
    // every call, so the dispatch is not hoisted out of the loop in any caller.
    const std::uint32_t* const gim = port_00b3d350_gameInputManagerGet();
    const std::uint32_t* const subobject =
        reinterpret_cast<const std::uint32_t*>(gim[0x24 / 4]);
    const std::uint32_t* const result =
        port_virtualSlot0C_of_gameInputManagerSubobject(
            const_cast<std::uint32_t*>(subobject));
    subid_mismatch = tracked->field_3c_recorded_subid != result[0x08 / 4];
  }

  if (manager_mismatch || subid_mismatch) {
    // 0x00b51624: single shared release path for both mismatch kinds.
    port_00b4f7f0_releaseCachedObject();
  }

  // 0x00b51629..0x00b51631: the release port nulls the global, so a release
  // always falls through into the rebuild. A surviving cache returns here.
  if (*kCachedObjectGlobal_0167ecd4 != 0) {
    return;
  }

  port_00b512f0_ensureCachedObjectBuilt();
  self->field_30_rebuilt_latch = 1;
}

}  // namespace openspore::reconstruction::wave13_w1_core_b16
