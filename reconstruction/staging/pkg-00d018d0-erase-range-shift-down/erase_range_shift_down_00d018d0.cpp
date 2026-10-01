#include "erase_range_shift_down_00d018d0.hpp"

namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down {
namespace {

// 0x00d018fe is `SAR EDI,0x3`: an ARITHMETIC shift, which rounds toward
// negative infinity rather than toward zero. C++ leaves `>>` on a negative
// signed value implementation-defined before C++20, so the floor is computed
// explicitly instead of leaning on that. Written as a division so the intent is
// visible, and the doubling shift reproduces the instruction's own arithmetic
// exactly for every input a 32-bit difference can take.
std::int32_t floor_divide_by_two_to_the_third(std::int32_t value) {
  return static_cast<std::int32_t>(value / kElementStride) -
         ((value % kElementStride != 0 && (value < 0)) ? 1 : 0);
}

}  // namespace

// Each literal below is pinned to the instruction it was read from, so the
// constant and the machine text cannot drift apart unnoticed. The assertions are
// deliberately placed BEFORE the reconstructed definition rather than inside it:
// a hexadecimal literal inside a static_assert message is a live expression
// operand, not a comment, and this package states no hexadecimal constant in the
// function body for the machine listing to corroborate.
//
//   MOV EBX,dword ptr [ECX + 0x4]   @ 0x00d018d5
//   ADD dword ptr [ECX + 0x4],EDI   @ 0x00d01909
//   ADD EDX,0x8   @ 0x00d018f1      ADD ESI,0x8   @ 0x00d018f4
//   SAR EDI,0x3   @ 0x00d018fe
static_assert(kTailDisplacement == 4, "the ECX displacement both tail accesses name");
static_assert(kElementStride == 8, "the stride of both cursors in the shift loop");
static_assert(kCountShift == 3, "the immediate of the arithmetic shift");
static_assert((1 << kCountShift) == kElementStride,
              "the removal count is the range length divided by the element stride");

// 0x00d018d0..0x00d0190f, 31 instructions.
//
// Read the whole body once, in order:
//
//   0x00d018d0  MOV EAX,[ESP+0x4]        arg1 (first) -> EAX
//   0x00d018d5  MOV EBX,[ECX+0x4]        receiver word at displacement 4 -> EBX
//   0x00d018da  MOV EDI,[ESP+0x14]       arg2 (last), entry ESP+8 after 3 pushes
//   0x00d018de  MOV ESI,EAX              first -> ESI, the write cursor
//   0x00d018e0  MOV EDX,EDI              last  -> EDX, the read cursor
//   0x00d018e2  CMP EDI,EBX / JZ         empty range: skip the loop
//   0x00d018e7  MOV EBP,[EDX] / [ESI]        first word of the element
//   0x00d018eb  MOV EBP,[EDX+0x4] / [ESI+0x4]  second word of the element
//   0x00d018f1  ADD EDX,8 / ADD ESI,8    both cursors advance one element
//   0x00d018f7  CMP EDX,EBX / JNZ        until the read cursor reaches the tail
//   0x00d018fc  SUB EDI,EAX              byte length of the erased range
//   0x00d018fe  SAR EDI,3                element count, arithmetic
//   0x00d01901  NEG EDI                  negated
//   0x00d01903  ADD EDI,EDI  x3          back to a byte count
//   0x00d01909  ADD [ECX+0x4],EDI        tail shrinks by exactly that many bytes
//   0x00d0190f  RET 8
//
// So: the elements from `last` up to the receiver's tail are moved down over
// the erased range, and the receiver's tail word then moves back by the byte
// length of that range. EAX is written once, at 0x00d018d0, and never again, so
// what the terminator returns is arg1 -- `first` -- which is why the declared
// return type is a pointer and not void.
extern "C" OpaqueElement* PKG_00D018D0_THISCALL erase_range_shift_down_00d018d0(
    OpaqueReceiver* self, OpaqueElement* first, OpaqueElement* last) {
  auto* const self_bytes = reinterpret_cast<std::uint8_t*>(self);
  auto* const tail_slot = reinterpret_cast<OpaqueElement**>(
      self_bytes + kTailDisplacement);
  const OpaqueElement* const tail = *tail_slot;

  // The two cursors start at `first` and `last` respectively and both step by
  // one element, so the loop copies the half-open range [last, tail) onto
  // [first, ...). It compares the READ cursor against the tail, not the write
  // cursor and not `first`, so the trip count is fixed by the tail alone.
  OpaqueElement* write_cursor = first;
  const OpaqueElement* read_cursor = last;
  while (read_cursor != tail) {
    std::uint32_t* const destination =
        reinterpret_cast<std::uint32_t*>(write_cursor);
    const std::uint32_t* const source =
        reinterpret_cast<const std::uint32_t*>(read_cursor);
    destination[0] = source[0];
    destination[1] = source[1];
    read_cursor = reinterpret_cast<const OpaqueElement*>(
        reinterpret_cast<const std::uint8_t*>(read_cursor) + kElementStride);
    write_cursor = reinterpret_cast<OpaqueElement*>(
        reinterpret_cast<std::uint8_t*>(write_cursor) + kElementStride);
  }

  // The tail word is decreased by the byte length of the erased range. The body
  // gets there by counting elements, negating, and doubling three times, which
  // is the same value only because the length is a whole number of elements; the
  // arithmetic shift rounds toward negative infinity, so a length that is not a
  // multiple of the stride would shorten the tail by a rounded amount rather
  // than by the exact length.
  //
  // The rounding is reproduced rather than smoothed into a plain subtraction,
  // because it is what these six instructions do. It is also worth saying
  // plainly what it is NOT: no well-formed call can observe it. The loop
  // terminates on `read_cursor == tail` with a stride of 8, so it terminates
  // only when `last - tail` is a multiple of 8, and since `first` and `tail`
  // are element-aligned that forces `last - first` to be a whole number of
  // elements too. The rounding therefore only ever fires on an input the loop
  // walks off the end of the sequence over -- see `not_claimed` in the metadata
  // sidecar. The model test does not exercise it, because doing so would hang
  // rather than fail.
  const std::int32_t byte_length = static_cast<std::int32_t>(
      reinterpret_cast<const std::uint8_t*>(last) -
      reinterpret_cast<const std::uint8_t*>(first));
  std::int32_t removal = floor_divide_by_two_to_the_third(byte_length);
  removal = -removal;
  removal = removal + removal;
  removal = removal + removal;
  removal = removal + removal;

  *tail_slot = reinterpret_cast<OpaqueElement*>(
      reinterpret_cast<std::uint8_t*>(*tail_slot) + removal);

  return first;
}

}  // namespace openspore::reconstruction::pkg_00d018d0_erase_range_shift_down