#include "editor_model_union_bounds.hpp"

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

namespace {

using unresolved_ports::bounding_box_make_empty;
using unresolved_ports::bounding_box_union_in_place;
using unresolved_ports::copy_six_dwords;
using unresolved_ports::rigblock_get_bounds;
using unresolved_ports::rigblock_is_hidden_or_filtered;

// 0x004ad575 ADD EAX,0x18 with EAX = the receiver, and the same +0x18 read
// repeated at 0x004ad616 and 0x004ad61c: the loop re-reads the vector on every
// test, so the count is not hoisted.
const OpaqueRigblockVector& rigblocks(const OpaqueEditorModel* model) {
  return model->mRigblocks;
}

// 0x004ad58a MOV EAX,[ECX+0x4] / 0x004ad58d SUB EAX,[EDX] / 0x004ad58f
// SAR EAX,0x2 - an arithmetic shift of a byte difference, so a negative
// difference yields a negative count and the unsigned JBE at 0x004ad599 does
// not fire.
int element_count(const OpaqueRigblockVector& v) {
  const auto span = reinterpret_cast<const char*>(v.end) -
                    reinterpret_cast<const char*>(v.begin);
  return span >> 2;
}

}  // namespace

// Reconstructed body of 0x004ad550 (413 bytes, 112 instructions, image base
// 0x00400000). See
// reconstruction/metadata/wave13-w1-dispatch-b03/004ad550.json.
//
// Invariants, in the order the body performs them:
//   1. the 24-byte accumulator is set to the empty-box sentinel TWICE
//      (0x004ad562 and 0x004ad56a, the same address)
//   2. count = (end - begin) >> 2; if count == 0 the loop is skipped entirely
//      and the EMPTY box is written to the out parameter
//   3. element 0's bounds REPLACE the accumulator, and element 0 is NOT subject
//      to the filter flag
//   4. elements 1..count-1 are unioned in, and when the filter flag is non-zero
//      an element is skipped unless the hidden/filtered predicate returns 1
//   5. the accumulator is copied to the out parameter and the out parameter is
//      returned in EAX
BoundingBox* __thiscall editor_model_union_bounds_004ad550(
    OpaqueEditorModel* model, BoundingBox* out_bounds, char filter_hidden) {
  BoundingBox accumulator;

  // 0x004ad55f LEA ECX,[EBP-0x1c] / 0x004ad562 CALL 0x00409c00
  bounding_box_make_empty(&accumulator);
  // 0x004ad567 LEA ECX,[EBP-0x1c] / 0x004ad56a CALL 0x00409c00
  // The same object is initialised a second time. The second call is redundant
  // in the observed build - it writes the same six constants over the same six
  // slots - and it is preserved here because deleting it would be a
  // reconstruction that differs from the original for no semantic reason.
  bounding_box_make_empty(&accumulator);

  const int count = element_count(rigblocks(model));

  // 0x004ad595 CMP dword ptr [EBP-0x4],0x0 / 0x004ad599 JBE 0x004ad6d8
  if (static_cast<unsigned int>(count) <= 0u) {
    // 0x004ad6d8 LEA EDX,[EBP-0x1c] / 0x004ad6db PUSH EDX
    // 0x004ad6dc MOV ECX,[EBP+0x8] / 0x004ad6df CALL 0x00511140
    // An empty rigblock list therefore yields the empty box, not a zero box.
    copy_six_dwords(out_bounds, &accumulator);
    return out_bounds;
  }

  // 0x004ad59f..0x004ad5b3: element 0 is read outside the loop and is not
  // gated by the filter flag.
  // 0x004ad5c1..0x004ad5cb: PUSH 0 / PUSH 0 / PUSH 0 / LEA EDX,[EBP-0x3c] /
  // PUSH EDX with ECX = the rigblock, i.e. mode 0 and both flags clear.
  // 0x004ad5d6 stores the returned out pointer, and 0x004ad5e2..0x004ad60c copy
  // all six floats out of it into the accumulator in two 12-byte halves.
  BoundingBox element_zero;
  {
    auto* const element_zero_rigblock =
        reinterpret_cast<EditorRigblockPtrSlot*>(rigblocks(model).begin)->ptr;
    const BoundingBox* const produced =
        rigblock_get_bounds(element_zero_rigblock, &element_zero, 0, 0, 0);
    accumulator.lower[0] = produced->lower[0];
    accumulator.lower[1] = produced->lower[1];
    accumulator.lower[2] = produced->lower[2];
    accumulator.upper[0] = produced->upper[0];
    accumulator.upper[1] = produced->upper[1];
    accumulator.upper[2] = produced->upper[2];
  }

  // 0x004ad60f MOV dword ptr [EBP-0x24],0x1 - the loop starts at index 1, not
  // at 0, because element 0 was already consumed above.
  for (int index = 1; index < count; ++index) {
    // 0x004ad653 MOVZX EDX,byte ptr [EBP+0xc] / 0x004ad657 TEST EDX,EDX
    // 0x004ad659 JZ 0x004ad692 - with the flag clear the predicate is skipped
    // entirely and the element is always processed.
    if (filter_hidden != 0) {
      // 0x004ad661..0x004ad67e: element[index] is loaded and passed to the
      // predicate. 0x004ad68c TEST EAX,EAX / 0x004ad68e JNZ 0x004ad692 /
      // 0x004ad690 JMP 0x004ad63e - a false predicate advances the index
      // without touching the accumulator.
      auto* const element =
          reinterpret_cast<EditorRigblockPtrSlot*>(rigblocks(model).begin)[index]
              .ptr;
      if (rigblock_is_hidden_or_filtered(element) == 0) {
        continue;
      }
    }

    // 0x004ad692..0x004ad6c5: the same bounds call with the second scratch
    // buffer at [EBP-0x54], then 0x004ad6ca PUSH EAX / 0x004ad6cb LEA ECX,
    // [EBP-0x1c] / 0x004ad6ce CALL 0x0043f050 merges it into the accumulator.
    BoundingBox element_bounds;
    const BoundingBox* const produced =
        rigblock_get_bounds(
            reinterpret_cast<EditorRigblockPtrSlot*>(rigblocks(model).begin)[index]
                .ptr,
            &element_bounds, 0, 0, 0);
    bounding_box_union_in_place(&accumulator, produced);
  }

  // 0x004ad6d8..0x004ad6df, then 0x004ad6e4 MOV EAX,[EBP+0x8] - the out
  // parameter is both written and returned.
  copy_six_dwords(out_bounds, &accumulator);
  return out_bounds;
}

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
