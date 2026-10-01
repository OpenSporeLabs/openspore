// PKG-PROLIST-DISPATCH-WAVE14 -- VA 0x006a1510
// App::PropertyList::AddAllPropertiesFrom
// SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Machine listing: 19 instructions, body 0x006a1510..0x006a1533 inclusive
// (ghidra_function body_start 0x006a1510, body_end 0x006a1535,
// body_span_bytes 38). Every statement below carries the instruction it comes
// from, so the source and the listing can be compared line by line.
//
// ABI, machine-derived (categories.abi_derived): __thiscall. The receiver
// arrives in ECX (obs-0007, receiver register ECX, offsets [0], bounds_only)
// and is copied to ESI at 0x006a1519; every later access goes through that
// alias, which is why the literal-operand scan the validator runs over the
// listing finds no displacement under ECX itself. One ordinary stack dword at
// entry_ESP+0x4, read once at 0x006a1512 and never written. The terminator is
// RET 0x4 at 0x006a1533, so the callee owns the four bytes: that rules cdecl
// and fastcall out and makes __thiscall the only convention consistent with
// the epilogue.
//
// Control flow: one conditional branch, JZ 0x006a1527 at 0x006a151d, whose
// target is inside this body. The listing is closed.
//
// Calls: there are none in the direct sense. Both transfers are
//   0x006a1525  CALL EAX   (register indirect)
//   0x006a152f  CALL EAX   (register indirect)
// so the xref export records no call edge out of this function and the
// reconstruction names no callee by address. What the two slots hold is not
// established by any record in this repository; they are read into
// function-pointer locals and called through those, which is the honest shape
// of a body whose dispatch targets are unknown.
//
// Callee-cleanup for the two indirect calls is an INFERENCE, not an
// observation: the frame is balanced at 0x006a1531/0x006a1532 with no ADD ESP
// after either CALL, so each callee must have popped the single word it was
// handed. The two slot function-pointer types below are therefore declared
// __thiscall with one stack argument. If a slot target turns out to clean up
// in cdecl, these two types are what has to change -- nothing else in the body
// does.

#include "app_property_list_add_all_properties_from_006a1510.hpp"

#if defined(_MSC_VER)
#define PKG_PROPLIST_DISPATCH_WAVE14_THISCALL __thiscall
#else
#define PKG_PROPLIST_DISPATCH_WAVE14_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_proplist_dispatch_wave14 {

namespace {

// Byte-wise word load at a machine displacement. Displacements are passed in
// as values rather than written inline as `object + n` so that this body
// asserts no member layout: the machine-derived receiver record is a set of
// displacements observed through ECX, not a field list, and no record in this
// repository names a member for either word this body touches.
template <typename Value>
Value load_word(const void* object, TargetWord offset) {
  const auto* base = static_cast<const unsigned char*>(object);
  unsigned char bytes[sizeof(Value)];
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    bytes[index] = base[index + offset];
  }
  Value value;
  auto* destination = reinterpret_cast<unsigned char*>(&value);
  for (unsigned int index = 0; index < sizeof(Value); ++index) {
    destination[index] = bytes[index];
  }
  return value;
}

// The table word is read as a table, and the slot is read out of the table --
// two separate machine steps (0x006a151f then 0x006a1522), kept as two.
template <typename Function>
Function load_slot(const void* table, TargetWord offset) {
  return load_word<Function>(table, offset);
}

}  // namespace

extern "C" unclassified_in_EAX PKG_PROPLIST_DISPATCH_WAVE14_THISCALL
app_property_list_add_all_properties_from_006a1510(OpaquePropertyList* receiver,
                                                  OpaquePropertyList* other) {
  // 0x006a1510  PUSH ESI
  // 0x006a1511  PUSH EDI
  //   A saved-register pair with no frame pointer and no locals: the matching
  //   POP EDI / POP ESI sit at 0x006a1531 / 0x006a1532. Nothing in the body
  //   allocates stack, so the two pushes are all the frame there is.
  //
  // 0x006a1512  MOV EDI,dword ptr [ESP + 0xc]
  //   entry ESP + 0x4 after those two pushes: the single ordinary stack
  //   argument, `other`. Read once, never written, popped by RET 0x4.
  //
  // 0x006a1516  MOV EAX,dword ptr [EDI + 0x30]
  //   One word out of the ARGUMENT object, not the receiver: EDI holds the
  //   stack argument read at 0x006a1512, and the receiver is in ECX until
  //   0x006a1519. The machine-derived receiver record is about ECX, enumerates
  //   only 0x0, and is bounds_only, so it neither corroborates nor refutes a
  //   displacement on this operand. Nothing names what the word means; it is
  //   called a plain word and is passed on unchanged. It is also the only
  //   argument the first transfer takes.
  const TargetWord word_at_other_30 = load_word<TargetWord>(other, 0x30);

  // 0x006a1519  MOV ESI,ECX
  //   The receiver alias. Every receiver access below goes through it, which is
  //   also why the literal-operand scan over the listing finds no displacement
  //   under ECX itself: the only receiver word this body reads is [ESI] at
  //   displacement 0, which is what the record enumerates.
  OpaquePropertyList* const self = receiver;

  // 0x006a151b  TEST EAX,EAX
  // 0x006a151d  JZ 0x006a1527
  //   A null word skips the whole first transfer and lands on the second
  //   block's table load; the second transfer runs on both paths.
  if (word_at_other_30 != 0) {
    // 0x006a151f  MOV EDX,dword ptr [ESI]
    //   The table word, at displacement 0 -- the shape a vtable pointer has,
    //   but the record names no table type, so it is read as a word.
    void* const table = load_word<void*>(self, 0);

    // 0x006a1521  PUSH EAX
    //   The word read at 0x006a1516 is this transfer's only stack argument, and
    //   it is pushed BEFORE the slot word is loaded into EAX -- so the argument
    //   is the word from the argument object, not the slot address. ECX is not
    //   rewritten on this path, so the callee's receiver is the receiver of this
    //   function.
    //
    // 0x006a1522  MOV EAX,dword ptr [EDX + 0x38]
    //   The slot word, and only afterwards. No record names the member behind
    //   it; the target is whatever the receiver's table holds at this
    //   displacement.
    const SlotAt38 slot_at_38 = load_slot<SlotAt38>(table, 0x38);

    // 0x006a1525  CALL EAX
    //   Register-indirect. Its result is dead: 0x006a1529 overwrites EAX
    //   before anything can observe it, so the declared return word of the slot
    //   type is never read on this path.
    slot_at_38(self, word_at_other_30);
  }

  // 0x006a1527  MOV EDX,dword ptr [ESI]
  //   The table word is read again on this path -- the JZ at 0x006a151d falls
  //   straight into it, so both paths execute this load.
  void* const table = load_word<void*>(self, 0);

  // 0x006a1529  MOV EAX,dword ptr [EDX + 0x30]
  //   The second slot word. No record names the member behind it either.
  const SlotAt30 slot_at_30 = load_slot<SlotAt30>(table, 0x30);

  // 0x006a152c  PUSH EDI
  //   `other` is this transfer's only stack argument.
  // 0x006a152d  MOV ECX,ESI
  //   The receiver alias becomes the callee's ECX, so the callee is dispatched
  //   on the same receiver this function was called with.
  //
  // 0x006a152f  CALL EAX
  //   Register-indirect, and the last write to EAX in the body: whatever this
  //   returns is what the body returns.
  return slot_at_30(self, other);

  // 0x006a1531  POP EDI
  // 0x006a1532  POP ESI
  // 0x006a1533  RET 0x4
  //   RET 0x4 pops the single stack argument, so this callee owns the cleanup.
}

}  // namespace openspore::reconstruction::pkg_proplist_dispatch_wave14
