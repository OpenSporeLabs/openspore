#include "editor_00573c00.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b00 {
namespace {

// Field offsets of the receiver, each one read or written by a named
// instruction in 0x00573c00 (see the address comments in the body).
constexpr std::size_t kActivePart = 0xcc;      // 0x00573c04  mov eax,[esi+0xcc]
constexpr std::size_t kActiveHandle = 0xe4;    // 0x00573c50  mov ecx,[esi+0xe4]
constexpr std::size_t kMode = 0x31c;           // 0x00573cf1  cmp [esi+0x31c],1
constexpr std::size_t kFlags3c = 0x3c;         // 0x00573d47  test [esi+0x3c],0x100
constexpr std::size_t kHasActive = 0x398;      // 0x00573d61  mov [esi+0x398],cl
constexpr std::size_t kHoveredRegion = 0x3b0;  // 0x00573c31  mov [esi+0x3b0],ecx
constexpr std::size_t kRegion3b4 = 0x3b4;      // 0x00573c37  mov [esi+0x3b4],ecx
constexpr std::size_t kPaintPaletteUi = 0x3c4;  // 0x00573cfa
constexpr std::size_t kSlot498 = 0x498;        // 0x00573cac  mov ecx,[esi+0x498]

constexpr std::size_t kPartFlags = 0xdc8;  // 0x00573c86  mov edx,[ecx+0xdc8]

inline std::uint8_t* at(void* base, std::size_t off) {
  return static_cast<std::uint8_t*>(base) + off;
}

}  // namespace

// 0x00573c00 -- 364 bytes, 115 instructions, read live in full.
//
// Contract, in the order the binary performs it:
//
//   (1) If the incoming part is the current part and the region is unchanged
//       (or both are null / the part is null), do nothing but refresh the
//       "has active part" byte.
//   (2) Otherwise latch the region into +0x3b0 and +0x3b4 unconditionally,
//       then bail out early if the part did not actually change.
//   (3) If there was a previous part, run the same-kind comparison against it
//       (0x004a60a0, which returns true only when both sides answer true to
//       0x004a6120 and their 0x004a5e10 values match). If an active handle
//       exists at +0xe4 and the comparison failed, re-run the comparison
//       between the handle's query result and the old part, then run
//       0x0043a830(0) unconditionally.
//   (4) Deselect path (part == null): test bit 3 of the OLD part's +0xdc8
//       and call 0x0043e2b0 when set; null the +0xcc slot and, if it was
//       non-null, immediately make a virtual call through vtable slot +0x8
//       on the object that was just dropped; then call 0x005cc690 when
//       +0x498 is non-null.
//   (5) Select path: if bit 1 of the NEW part's +0xdc8 is set the whole
//       attach block is skipped. Otherwise push into the +0xcc slot via
//       0x004b09b0, evaluate 0x004a2060 (true only when bits 7, 20 and 1 of
//       +0xdc8 are all clear) and call 0x005cc690 when it answers false and
//       +0x498 is non-null.
//   (6) Then the marker: when mMode (+0x31c) == 1 the marker runs only if
//       +0x3c4 is non-null and 0x005ca920 answers non-zero; in every other
//       mMode it runs unless bits 10 AND 11 of the new part's +0xdc8 are both
//       set. The marker itself is port_004a88d0(0xbb58117e) followed by
//       0x0043a830(1).
//   (7) If mMode == 0 and bit 8 of +0x3c is set, call 0x00573520 with the
//       new part.
//   (8) Finally +0x398 = (the +0xcc slot is non-null), on every path
//       including both early exits.
//
// Receiver provenance: 0x00573ea1 in the immediate neighbour
// FUN_00573d70 does `mov ecx, esi` where ESI came from ECX, and reads
// [esi+0xe4], [esi+0xf4], [esi+0x140], [esi+0x141]. The ModAPI header
// Spore/Editors/Editor.h records cEditor +0xcch as `mpActivePart`
// (EditorRigblockPtr), +0xe4 as `mpActiveHandle`, +0x31c as `Mode mMode`,
// +0x398 as a bool, +0x3b0 as `mHoveredPaintRegion`, +0x3b4 as a second
// paint region, +0x3c4 as `mpPaintPaletteUI` and +0x498 as an int tied to
// the RolloverEditorSellBack layout. Those offsets are recorded as SDK
// correspondence; the binary, which has no RTTI, is what proves the offsets.
//
// The virtual call in step (4) is the only dispatch in this body:
//   0x00573ca5  8b01          mov eax, dword ptr [ecx]      ; vtable
//   0x00573ca7  8b5008        mov edx, dword ptr [eax + 8]  ; slot +0x8
//   0x00573caa  ffd2          call edx
// with ECX still holding the dropped rigblock, and the +0xcc slot already
// zeroed at 0x00573c9f. The same object graph shows slot +0x0 used as a
// destructor (0x0045adef) and slot +0x4 on a value entering a container slot
// (0x005c1dc0) while slot +0x8 runs on the value leaving one, so +0x8 is
// recorded as "detach/release-shaped" and NOT named.

extern "C" void __thiscall FUN_00573c00_reconstruct(
    Opaque573c00Editor* self,
    Opaque573c00Rigblock* part,
    std::uint32_t paint_region) {
  auto* const old_slot = reinterpret_cast<Opaque573c00Rigblock**>(
      at(self, kActivePart));
  Opaque573c00Rigblock* const old_part = *old_slot;  // 0x00573c04

  // 0x00573c19..0x00573c2b: same part and same region is a no-op; a null
  // part short-circuits before the region compare, and a null part with a
  // null old part is also a no-op.
  const bool part_unchanged = (part == old_part);
  if (part_unchanged) {
    if (part == nullptr) {
      goto refresh_has_active;  // 0x00573c1f  jz 0x00573d5a
    }
    if (paint_region == *reinterpret_cast<std::uint32_t*>(at(self, kHoveredRegion))) {
      goto refresh_has_active;  // 0x00573c2b  jz 0x00573d5a
    }
  }

  // 0x00573c31 / 0x00573c37: the region pair is latched before the change test.
  *reinterpret_cast<std::uint32_t*>(at(self, kHoveredRegion)) = paint_region;
  *reinterpret_cast<std::uint32_t*>(at(self, kRegion3b4)) = paint_region;

  // 0x00573c3d..0x00573c3f: identical part pointer after the latch is also a
  // no-op; the byte at +0x398 is still refreshed by the shared tail.
  if (part == old_part) {
    goto refresh_has_active;  // 0x00573c3f  jz 0x00573d5a
  }

  // 0x00573c45..0x00573c7b: only when there was a previous part.
  if (old_part != nullptr) {
    // 0x00573c4b: pushed (part, old_part) -- the decompiler shows the
    // argument order as (new, old) after the two PUSHes.
    const std::uint8_t same_kind =
        port_004a60a0_same_kind(part, old_part);

    // 0x00573c50 / 0x00573c5e: an active handle must exist AND the kinds must
    // have differed before the handle is re-bound.
    const bool has_handle =
        *reinterpret_cast<void**>(at(self, kActiveHandle)) != nullptr;
    if (has_handle && same_kind == 0) {
      // 0x00573c66 / 0x00573c6f: re-run the same comparison against whatever
      // 0x0047e6c0 resolves for the current handle.
      void* resolved = port_0047e6c0_query();
      port_004a60a0_same_kind(resolved, *old_slot);
    }
    // 0x00573c79: unconditional inside the had-an-old-part arm.
    port_0043a830(0);
  }

  if (part == nullptr) {
    // ---- deselect arm, 0x00573c80..0x00573cbf ----
    // 0x00573c86..0x00573c94: bit 3 of the OLD part's flag dword.
    const std::uint32_t old_flags = *reinterpret_cast<std::uint32_t*>(
        at(old_part, kPartFlags));
    if (((old_flags >> 3) & 1u) != 0u) {
      port_0043e2b0();
    }

    // 0x00573c99..0x00573caa: null the slot first, then dispatch slot +0x8
    // on the object that is being dropped.
    if (*old_slot != nullptr) {
      Opaque573c00Rigblock* dropped = *old_slot;
      *old_slot = nullptr;
      auto* const vtable = *reinterpret_cast<void***>(dropped);
      if (vtable != nullptr) {
        auto detach = reinterpret_cast<void (*)()>(vtable[2]);  // slot +0x8
        detach();
      }
    }

    // 0x00573cac..0x00573cba
    if (*reinterpret_cast<void**>(at(self, kSlot498)) != nullptr) {
      port_005cc690(*reinterpret_cast<void**>(at(self, kSlot498)));
    }
  } else if ((((*reinterpret_cast<std::uint32_t*>(at(part, kPartFlags)) >> 1) &
               1u) == 0u)) {
    // ---- select arm, 0x00573cc1..0x00573d39 ----
    // 0x00573ccd / 0x00573cd0: the receiver of 0x004b09b0 is the ADDRESS of
    // the +0xcc slot, not the editor.
    port_004b09b0(old_slot, part);

    // 0x00573cd6 / 0x00573ce0
    const std::uint8_t plain = port_004a2060_is_plain_part(part);
    if (plain == 0) {
      if (*reinterpret_cast<void**>(at(self, kSlot498)) != nullptr) {
        port_005cc690(*reinterpret_cast<void**>(at(self, kSlot498)));
      }
    }

    // 0x00573cf1..0x00573d3e: the marker gate. Polarity matters -- the jump
    // at 0x00573d1f is taken (marker skipped) when bit 11 is CLEAR, and the
    // jump at 0x00573d26 is taken (marker skipped) when bit 10 is SET, so the
    // marker runs unless BOTH bits are set.
    const std::uint32_t new_flags = *reinterpret_cast<std::uint32_t*>(
        at(part, kPartFlags));
    bool run_marker;
    if (*reinterpret_cast<std::uint32_t*>(at(self, kMode)) == 1u) {
      // 0x00573cfa..0x00573d0b
      run_marker =
          *reinterpret_cast<void**>(at(self, kPaintPaletteUi)) != nullptr &&
          port_005ca920(self) != 0;
    } else {
      run_marker = ((new_flags >> 11) & 1u) == 0u || ((new_flags >> 10) & 1u) == 0u;
    }

    if (run_marker) {
      // 0x00573d28 / 0x00573d2d / 0x00573d39
      port_004a88d0(0xbb58117eu);
      port_0043a830(1);
    }
  }

  // 0x00573d3e..0x00573d55: paint path, only in mode 0 with bit 8 of +0x3c.
  if (*reinterpret_cast<std::uint32_t*>(at(self, kMode)) == 0u &&
      (*reinterpret_cast<std::uint32_t*>(at(self, kFlags3c)) & 0x100u) != 0u) {
    port_00573520(self, *old_slot);
  }

refresh_has_active:
  // 0x00573d5a..0x00573d61: the single result of the whole function, on every
  // path including both early exits.
  *reinterpret_cast<std::uint8_t*>(at(self, kHasActive)) =
      (*old_slot != nullptr) ? 1u : 0u;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b00
