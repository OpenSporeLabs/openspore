// Body of FUN_00c487d0 @ 0x00c487d0.  See the header for the evidence basis,
// the GLOBALS sidecar reading, the frame derivation and the one derived step
// (the two dispatch arities).

#include "slot41_scope_exchange_00c487d0.hpp"

namespace openspore::reconstruction::pkg_00c487d0_slot41_scope_exchange {
namespace {

// The receiver is published into ScopeState::field_18 as a raw word, exactly as
// `MOV dword ptr [ECX + 0x18],ESI` does - the listing never dereferences it.
Word as_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

// `MOV EAX,dword ptr [ESI + 0x17c] / TEST EAX,EAX / JZ / MOV ESI,EAX`
// 00c48835..00c4883f: the receiver word is used only when it is non-zero, and it
// is the substituted word that both dispatches receive as their last argument.
const void* substitute_receiver(const Receiver* self, bool* replaced) {
  *replaced = self->field_17c != 0;
  return *replaced ? reinterpret_cast<const void*>(self->field_17c) : self;
}

// 00c4889c..00c488bd: advance by two bytes per unit until the word at the cursor
// is zero, then divide the byte distance by two and rebuild the end pointer as
// begin + units.  The count below is the machine's own `units`.
std::size_t scan_wide_code_units(const std::uint16_t* begin) {
  std::size_t units = 0;
  while (begin[units] != 0) {
    ++units;
  }
  return units;
}

}  // namespace

void Simulator_Slot41ScopeExchangeAndDispatch_00c487d0(
    const Receiver* self, Word stack_arg1, Word stack_arg2,
    ScopeState* const* scope_state_cell, Hooks& hooks, Trace& trace) {
  // 00c487d0..00c487d6: SUB ESP,0x40 and the four callee-saved pushes.
  // 00c487d6: MOV ESI,ECX - the receiver alias the artifact records as R-ALIAS.
  // `stack_arg1` / `stack_arg2` correspond to entry ESP+0x4 / entry ESP+0x8.
  // They are accepted because RET 0x8 pops them, and they are never read
  // because the listing never reads them.  Both facts are OBSERVED.
  (void)stack_arg1;
  (void)stack_arg2;

  // 00c487d8 / 00c487da / 00c487e1.
  trace.slot41_result = hooks.dispatch_slot41(self);

  // 00c487e3..00c48804.  The pointer cell 0x016e0d08 is re-read at 00c487e3,
  // 00c487ef, 00c488cb and 00c488d8 - the four GLOBALS rows, all mode `read`.
  // The scope words are read through ECX, saved into the frame, and immediately
  // overwritten; they are restored verbatim at 00c488d5 / 00c488e2.
  ScopeState* scope = reinterpret_cast<ScopeState*>(*scope_state_cell);
  const Word saved_field_18 = scope->field_18;
  const Word saved_field_48 = scope->field_48;
  scope->field_18 = as_word(self);
  trace.published_field_18 = scope->field_18;
  ++trace.published_field_18_argv;
  scope->field_48 = trace.slot41_result;
  trace.published_field_48 = scope->field_48;
  ++trace.published_field_48_argv;

  // 00c48807..00c48818.  The null case is the EAX=0 branch at 00c48818 and
  // zeroes the word; the non-null case loads displacement 0x13c.
  const Word player_data = hooks.read_player_data();
  trace.player_data_was_null = player_data == 0;
  // `MOV EBP,dword ptr [EAX + 0x13c]` when non-zero, `XOR EBP,EBP` when zero.
  // Only the displacement 0x13c is observed; the value itself is carried
  // through Hooks so no object is fabricated here.
  trace.player_data_word_13c =
      player_data == 0 ? Word(0)
                       : hooks.read_player_data_word_13c(
                             reinterpret_cast<const void*>(
                                 static_cast<std::uintptr_t>(player_data)));

  // 00c4881c / 00c48821 / 00c48823: two __thiscall callees on the receiver; the
  // first result is discarded, the second lands in the frame at entry ESP-0x40.
  (void)hooks.sub_00c452a0(self);
  trace.sub_00c451e0_result = hooks.sub_00c451e0(self);

  // 00c48828..00c48830: LEA ECX,[ESP + 0x28] / CALL 0x006b5060.  The receiver of
  // the constructor, of the 00c48893 accessor and of the 00c488e5 destructor are
  // the same address, so one object is modelled for all three.
  LocalWrapper wrapper{};
  hooks.construct_wrapper(&wrapper);
  trace.wrapper_constructed = true;

  // 00c48835..00c4883f.
  const void* dispatch_receiver =
      substitute_receiver(self, &trace.receiver_replaced_by_field_17c);

  // 00c48841..00c48854: two identical argument-free accessors; the first result
  // is kept in EDI, the second in EBX, and each object's word 0 is spilled to the
  // frame (entry ESP-0x3c and entry ESP-0x34).
  const Accessor* accessor1 = hooks.acquire_accessor();
  const Accessor* accessor2 = hooks.acquire_accessor();
  trace.dispatch1_receiver = reinterpret_cast<CodeAddress>(
      reinterpret_cast<std::uintptr_t>(accessor1));
  trace.dispatch2_receiver = reinterpret_cast<CodeAddress>(
      reinterpret_cast<std::uintptr_t>(accessor2));

  // 00c48862: nullary cdecl, no arguments and no stack effect.
  trace.empire_result = hooks.read_empire();

  // 00c4886d..00c4887b.  The five arguments of the first dispatch are the five
  // pushes emitted in reverse source order; the sixth push (the wrapper
  // address, prepared at 00c48851) is deliberately left for the second dispatch.
  // The target address is entry ESP-0x14, sixteen bytes into the 0x40-byte
  // frame, inside the frame and ahead of the wide descriptor at entry ESP-0x08.
  unsigned char frame[kFrameBytes] = {};
  Word* const frame_local_14 = reinterpret_cast<Word*>(frame + (kFrameBytes - 0x14));
  trace.dispatch_accessor1_args[0] = as_word(frame_local_14);
  trace.dispatch_accessor1_args[1] = trace.sub_00c451e0_result;
  trace.dispatch_accessor1_args[2] = trace.empire_result;
  trace.dispatch_accessor1_args[3] = trace.player_data_word_13c;
  trace.dispatch_accessor1_args[4] = as_word(dispatch_receiver);

  trace.dispatch_accessor1_result = hooks.dispatch_accessor1(
      accessor1, trace.dispatch_accessor1_args[0], trace.dispatch_accessor1_args[1],
      trace.dispatch_accessor1_args[2], trace.dispatch_accessor1_args[3],
      trace.dispatch_accessor1_args[4]);

  // 00c4887d..00c48891.  Second dispatch: four stack arguments, the last of them
  // the wrapper address pushed back at 00c48851.  Its receiver is accessor #2
  // and its callee word is the one at displacement 0x0c of that table.
  WideDescriptor descriptor{};
  descriptor.end = descriptor.begin;  // the listing never initialises these two
  trace.dispatch_accessor2_args[0] = trace.slot41_result;
  trace.dispatch_accessor2_args[1] = descriptor.end;
  trace.dispatch_accessor2_args[2] = trace.dispatch_accessor1_result;
  trace.dispatch_accessor2_args[3] = as_word(&wrapper);

  trace.dispatch_accessor2_result = hooks.dispatch_accessor2(
      accessor2, trace.dispatch_accessor2_args[0], trace.dispatch_accessor2_args[1],
      trace.dispatch_accessor2_args[2], trace.dispatch_accessor2_args[3]);

  // 00c48893..00c488bd: LEA ECX,[ESP + 0x28] / CALL 0x006b55c0 hands back the
  // wide pointer stored at wrapper+0x08; the scan counts 16-bit code units.
  const std::uint16_t* data = hooks.wrapper_data(&wrapper);
  const std::size_t units = scan_wide_code_units(data);
  trace.wide_code_units = units;

  // 00c488c0..00c488c6: the end pointer is pushed first, the begin pointer
  // second, so the call receives (this = descriptor, begin = data, end = data +
  // units).  0x00423650 pops its two words, which is what lands ESP on
  // entry ESP-0x40 for the epilogue.
  hooks.assign_range(&descriptor, data, data + units);

  // 00c488cb..00c488e2: both scope words are restored from the frame words
  // written at 00c487f5 and 00c48800, in the same order they were stashed.
  ScopeState* scope_again = reinterpret_cast<ScopeState*>(*scope_state_cell);
  scope_again->field_18 = saved_field_18;
  scope_again->field_48 = saved_field_48;

  // 00c488e5..00x00c488e9: LEA ECX,[ESP + 0x18] / CALL 0x006b5240 on the same
  // wrapper the constructor built.  00c488ee ADD ESP,0x40 and 00c488f1 RET 0x8
  // close the frame; nothing is computed into EAX on the way out.
  hooks.destroy_wrapper(&wrapper);
  trace.wrapper_destroyed = true;
}

}  // namespace openspore::reconstruction::pkg_00c487d0_slot41_scope_exchange
