// PKG-SWARM-W1-00641410 -- VA 0x00641410
// Sporepedia table family, unnamed virtual of an asset-data class
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000)
//
// The complete body: 31 instructions, 0x00641410..0x00641459 inclusive
// (ghidra_function.body_start 0x00641410, body_end 0x00641459, size_bytes 74;
// 0x0064145a..0x0064145f are INT3 padding and are NOT part of the body). Every
// line of the model below is annotated with the instruction it comes from. The
// full listing is reproduced in the header.
//
// FRAME. There is no frame: the only stack effect in the body is the one PUSH ESI
// at 0x00641410 and its two matching POP ESI at 0x00641454 and 0x00641458. No
// argument is ever pushed (there is no PUSH other than ESI), no ADD ESP appears,
// and both returns are the one-byte `C3` with no immediate. So the body takes
// ZERO ordinary stack arguments and leaves ESP exactly where it found it. That is
// the machine half of the ABI record's cleanup side (stack_cleanup_bytes 0, side
// "caller"), and it is corroborated from outside: the single call site in the
// image is 0x00ec3b9c, a bare `E8` relative call with no argument setup, and the
// instruction after it (0x00ec3ba1) is `TEST AL,AL`.
//
//   entry-4   the saved ESI, parked by 0x00641410 and restored at 0x00641454 on
//             the true path and at 0x00641458 on the false path. It is not a
//             parameter and not a return value: both returns are `C3`, and the
//             restored value is the caller's ESI by construction.
//
// VIRTUAL DISPATCH: four indirect calls, and they are the whole body. The
// machine-derived dispatch record agrees on the count (abi_derived.dispatch
// indirect_calls 4) and is silent on the rest (call_offsets [], vtable_shaped
// _loads 0), so the slot number below is taken from the displacement the listing
// shows four times -- 0x24, dword index 9 -- and from nowhere else.
//
//   00641413/0x00641415  slot 9 (+0x24) -- dispatch 1, no ECX reload before it
//   00641421/0x00641423  slot 9 (+0x24) -- dispatch 2, after 0x00641426 MOV ECX,ESI
//   00641431/0x00641433  slot 9 (+0x24) -- dispatch 3, after 0x00641436 MOV ECX,ESI
//   00641441/0x00641443  slot 9 (+0x24) -- dispatch 4, after 0x00641446 MOV ECX,ESI
//
// All four reads of the dispatch word are one level out of the receiver and one
// level into the table, which is two dereferences: `MOV EAX,[ESI]` then
// `MOV EDX,[EAX + 0x24]`. A one-level reading of the same bytes would be
// `MOV EDX,[ESI + 0x24]`, which is not an instruction in this body. The model
// therefore loads the pointer and then indexes through it, and the model test
// plants live observer addresses where a one-level model would look so that
// mistake cannot survive.
//
// All four reads of the dispatch word are also INDEPENDENT: between each pair
// there is a CALL and nothing else, so dispatch N+1 is decided by the value the
// word holds after callee N returned. The model performs four separate loads
// rather than reusing one pointer, and the model test proves the difference by
// having a callee overwrite the word mid-body.
//
// THE FOUR COMPARES are a short-circuiting four-way OR. Each is a full 32-bit
// equality test (`CMP EAX,imm32` + `JZ`), each sends control to the same shared
// false block at 0x00641456, and each is reached only if every earlier one failed.
// So the number of calls is itself an observable of the body: 1, 2, 3 or 4
// depending on which literal matched first, and the model test asserts that count
// on every path.
//
// NOT ASSERTED HERE, deliberately:
//
//  * Which function slot 9 dispatches to. Six tables install this body and they
//    disagree about slot 9 (0x00641770, 0x00e31100, 0x00641850, 0x00b1e4d0,
//    0x00dd0e10, 0x00641770), so no single callee can be right for all six. See
//    the sidecar's mechanics.vtable_installations.
//  * What the four literals name. They are 32-bit identity-shaped values compared
//    for equality and nothing in this body resolves them. A neighbouring predicate
//    at 0x00ec3b60 makes the same slot-9 dispatch and compares against a fifth
//    literal, which is reported as context, not as an answer.
//  * That any real callee in the game ever changes the dispatch word. The listing
//    proves the model must re-read it; whether the re-read ever matters at run
//    time is a runtime question. The model test proves only that the model is
//    written to re-read it.
//  * Any receiver field other than the dispatch word and the +0x26 byte. The body
//    reads no other displacement and writes none, so the rest is an opaque run.
//    No member is named for either the receiver or the table: the machine
//    receiver record is `bounds_only: true` and settles displacements, not member
//    identities, so every access below goes through a displacement-named
//    accessor whose displacement is a constexpr pinned by a static_assert to the
//    instruction it came from.
//  * The 24 high bits of the result as a SOURCE-level fact. They are reproduced
//    here because the instructions fix them and the model test asserts them, but
//    they are a register artefact rather than anything the C++ author wrote: both
//    return sites write AL only, and the sole known caller consumes AL only
//    (0x00ec3ba1 `TEST AL,AL`). The declared return type is therefore the ONE BYTE
//    the machine writes, and the residue travels out through the model-
//    instrumentation word model_returned_eax() rather than through the signature.
//
// GLOBALS: none. No instruction in the body names a data-segment address.

#include "swarm_w1_00641410_types.hpp"

#include <cstdint>

namespace openspore::reconstruction::pkg_swarm_w1_00641410 {
namespace {

// Model instrumentation, not machine globals. Each is a value a specific pair of
// instructions produces, exposed so the model test can observe it. The header
// explains at length why none of this is a real-register probe.
Word g_saved_esi = 0;
Word g_restored_esi = 0;
Word g_esi_at_entry = 0;
Word g_dispatch_esp[4] = {0, 0, 0, 0};

// The complete 32-bit EAX the return that just happened leaves behind. Both exit
// sites write AL only, so this is the C return value's low byte carried over the
// upper 24 bits of the last callee's own return word. It is a REGISTER fact, not
// a second return value: the declared type is the one byte the machine writes,
// and this word exists so the residue -- which the instructions fully determine on
// all five exits -- is still published and still asserted.
Word g_returned_eax = 0;

// Record the register the machine leaves behind and hand back the one byte the
// caller consumes. `static_cast<std::uint8_t>` is the truncation, and it is
// exactly what `MOV AL,...` and `XOR AL,AL` do: the upper 24 bits are not
// cleared, they are simply not part of the value this function produces.
std::uint8_t publish_eax(Word eax) {
  g_returned_eax = eax;
  return static_cast<std::uint8_t>(eax);
}

// 0xdeadbeef is the poison both ESI words are filled with between runs. A model
// that popped ESI on only one of the two return paths leaves the other word
// poisoned, which is visible; a model that never popped leaves both poisoned.
constexpr Word kEsiPoison = 0xdeadbeefu;

// One dispatch, performed the way `CALL EDX` performs it.
//
// The ESP publication and the transfer are ONE asm block on purpose. A
// standalone ESP read immediately before the call is not a witness: at -O0 the
// compiler inserts outgoing-argument and register-save space between the read and
// the call, so the published value would not be the ESP the callee is entered
// with. Inside the block `movl %%esp,%0` and `call *%2` are adjacent, so the model
// publishes exactly the stack the callee is entered on, minus the return address,
// and the model test's trampoline samples the same quantity and asserts the
// difference is 4.
//
// The receiver is placed in ECX inside the block, because there is no C++ call
// here for the __thiscall convention to carry it: the machine transfer is
// `CALL EDX`, a call through a register, and 0x00641426 / 0x00641436 /
// 0x00641446 MOV ECX,ESI are the machine's way of re-establishing that. For the
// first dispatch there is no such reload and none is added here, because ECX
// still holds the entry receiver and the machine relies on exactly that.
//
// The register constraints are fixed rather than "r" because this block needs
// three registers while clobbering two more, and EBX is the GOT base in a PIE:
// EAX carries the result out, EBX the target, EDI the receiver, and ECX and EDX
// are free to be destroyed by the callee.
#define P_DISPATCH(target_name, esp_cell, out_value)                                        \
  do {                                                                         \
    __asm__ __volatile__("movl %%esp, %0\n\t"                                 \
                         "movl %3, %%ecx\n\t"                                 \
                         "call *%2\n\t"                                       \
                         "movl %%eax, %1\n\t"                                 \
                         : "=m"(esp_cell), "=a"(out_value)                    \
                         : "b"(reinterpret_cast<std::uintptr_t>(target_name)),      \
                           "D"(reinterpret_cast<std::uintptr_t>(receiver))     \
                         : "ecx", "edx", "cc", "memory");                     \
  } while (false)

}  // namespace

Word model_esi_at_entry() { return g_esi_at_entry; }

void model_set_esi_at_entry(Word value) { g_esi_at_entry = value; }

Word saved_esi_frame_word() { return g_saved_esi; }

Word restored_esi_word() { return g_restored_esi; }
Word model_esi_poison() { return kEsiPoison; }

void model_reset_esi_probes() {
  g_saved_esi = kEsiPoison;
  g_restored_esi = kEsiPoison;
  g_dispatch_esp[0] = kEsiPoison;
  g_dispatch_esp[1] = kEsiPoison;
  g_dispatch_esp[2] = kEsiPoison;
  g_dispatch_esp[3] = kEsiPoison;
}

Word dispatch_esp_call1() { return g_dispatch_esp[0]; }
Word dispatch_esp_call2() { return g_dispatch_esp[1]; }
Word dispatch_esp_call3() { return g_dispatch_esp[2]; }
Word dispatch_esp_call4() { return g_dispatch_esp[3]; }

Word model_returned_eax() { return g_returned_eax; }

extern "C" std::uint8_t PKG_SWARM_W1_00641410_THISCALL re_00641410(
    AssetData* receiver) {
  // 00641410  PUSH ESI
  //
  // The body's only stack effect. It is here because the body makes four calls
  // and ESI is call-clobbered; the machine parks the CALLER's ESI and gives it
  // back at 0x00641454 / 0x00641458.
  //
  // The model parks it in a frame WORD, not in the real register, and that is a
  // concession to the toolchain rather than a choice. The prescribed build is a
  // PIE, and GCC's i386 PIE sequence for this function is
  // `call __x86.get_pc_thunk.si; addl $_GLOBAL_OFFSET_TABLE_,%esi`: ESI holds the
  // GOT base for the whole body, so a real-register version would read the module
  // address instead of the caller's ESI and a write would break the addressing
  // the compiler is still about to emit. The header records this; the model test
  // lists it as deliberately not asserted and carries the PUSH/POP pair as the
  // two poisoned value words below instead, so a model that pops on only one of
  // the two return paths is still visible.
  g_saved_esi = model_esi_at_entry();

  // 00641411  MOV ESI,ECX
  //
  // ESI becomes the receiver alias. Three consequences, two of them
  // load-bearing:
  //
  //  (a) ECX is NOT changed by this move, and nothing between 0x00641411 and
  //      0x00641418 writes ECX, so the FIRST dispatch still receives the entry
  //      receiver in ECX even though the body never reloads it there. The model
  //      therefore hands `receiver` -- not a register variable -- to the first
  //      callee, and adds no reload the machine does not have.
  //  (b) ESI is overwritten with the receiver, so the caller's ESI is GONE from
  //      the register for the duration of all four calls, and a callee sampling
  //      ESI would see the receiver rather than the entry value. This is a MACHINE
  //      fact and the model annotates it, but the model cannot perform it and the
  //      model test cannot assert it, for the PIE reason given above.
  //  (c) ESI, not ECX, is what 0x00641426/0x00641436/0x00641446 reload ECX from,
  //      which is why the reloads are needed at all: a __thiscall callee may
  //      destroy ECX.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00641413  MOV EAX,[ESI]
  //
  // Read #1 of the dispatch word. It is a load of the receiver's own LEADING word:
  // there is no LEA, ADD or displacement on ESI anywhere in the 31 instructions,
  // so the object whose word is read is the entry receiver itself and not a
  // sub-object of it.
  //
  // The `kReceiverDispatchWordDisplacement` below therefore adds nothing to the
  // address: the operand the machine prints at 0x00641413 is a bare `[ESI]` with
  // NO displacement field, and the header's constant is the named record of that
  // absence rather than a displacement the instruction carries. It is written as
  // the named constant instead of a literal because a zero written here is a
  // constant the machine listing does not contain: the listing has no operand to
  // corroborate one, and stating it as a literal asserted a machine value that
  // the body does not state. The header's static_assert pins that constant to
  // this instruction.
  //
  // The result is carried as a raw word rather than as a `Vtable*`: nothing about
  // the table's layout is claimed, and the second dereference below is where the
  // 0x24 displacement is applied.
  Word const table1 = word_at(self, kReceiverDispatchWordDisplacement);

  // 00641415  MOV EDX,[EAX + 0x24]
  //
  // Slot 9, the model's kSlotDispatched. The displacement is read straight out of
  // the instruction. This is the second dereference of the pair.
  SlotFn const target1 = dispatch_target_at(table1, kSlotDispatchedByteDisplacement);

  // 00641418  CALL EDX
  //
  // No argument is pushed, so the callee takes nothing from the stack; the
  // receiver travels in ECX, unchanged since entry. The model's slot prototype is
  // single-receiver __thiscall for that reason and no other.
  Word call1 = 0;
  P_DISPATCH(target1, g_dispatch_esp[0], call1);

  // 0064141a  CMP EAX,0xbcd73e89
  // 0064141f  JZ 0x00641456
  //
  // A full 32-bit EQUALITY test, not a null test, not a `== 1` test and not a
  // signed or magnitude comparison: `CMP` sets ZF exactly on bitwise equality, so
  // signedness cannot affect it and the two literals whose sign bit is set match
  // just as the two below 0x80000000 do. Polarity is taken-when-equal and is
  // fixed by `JZ`.
  if (call1 == kDenyLiteral1) {
    // 00641456  XOR AL,AL
    // 00641458  POP ESI
    // 00641459  RET
    //
    // `XOR AL,AL` is bytes 32 c0 -- the LOW BYTE only, and NOT `XOR EAX,EAX`
    // (33 c0). The upper 24 bits of EAX are therefore still the upper 24 bits of
    // callee 1's return word, and because the CMP on the way in proved that word
    // equals 0xbcd73e89 exactly, the EAX this body leaves is 0xbcd73e00. A model
    // that returns 0 here is wrong, and this is the first of the four exits where
    // that is provable from the literals alone rather than from a chosen callee
    // result.
    //
    // Reaching 0x00641456 from 0x0064141f means dispatches 2, 3 and 4 never
    // happen: slot 9 is not re-loaded and not called again, and the model test
    // asserts the call count is exactly 1 on this path.
    g_restored_esi = g_saved_esi;  // 00641458 POP ESI
    return publish_eax(with_low_byte_cleared(call1));
  }

  // 00641421  MOV EAX,[ESI]
  //
  // Read #2 of the same word. This is not a redundant copy of read #1: a CALL sits
  // between them and this body does nothing else, so dispatch 2 is decided by the
  // value the word holds after callee 1 ran. The model performs a second load
  // rather than reusing `table1`, and the model test proves the difference by
  // having the first callee overwrite the word.
  Word const table2 = word_at(self, kReceiverDispatchWordDisplacement);

  // 00641423  MOV EDX,[EAX + 0x24]
  //
  // Slot 9 again. Same displacement, re-read from whichever table the word holds
  // now.
  SlotFn const target2 = dispatch_target_at(table2, kSlotDispatchedByteDisplacement);

  // 00641426  MOV ECX,ESI
  //
  // The machine's way of re-establishing the receiver for callee 2, because
  // callee 1 is free to destroy ECX. In the model `receiver` is passed directly
  // and this instruction is a no-op at the source level; it is annotated rather
  // than emulated because its only machine-level content is "the second callee
  // gets the same receiver as the first".
  //
  // 00641428  CALL EDX
  Word call2 = 0;
  P_DISPATCH(target2, g_dispatch_esp[1], call2);

  // 0064142a  CMP EAX,0xb8669ec9
  // 0064142f  JZ 0x00641456
  //
  // Same shape, same shared false block, same short-circuit. The literal is this
  // CMP's own immediate and is paired with this CMP, so a model that permutes the
  // literals is refuted both by the returned word and by which call count it
  // produced.
  if (call2 == kDenyLiteral2) {
    g_restored_esi = g_saved_esi;  // 00641458 POP ESI
    return publish_eax(with_low_byte_cleared(call2));  // 0xb8669e00
  }

  // 00641431  MOV EAX,[ESI]   -- read #3, independent again
  // 00641433  MOV EDX,[EAX + 0x24]
  Word const table3 = word_at(self, kReceiverDispatchWordDisplacement);
  SlotFn const target3 = dispatch_target_at(table3, kSlotDispatchedByteDisplacement);

  // 00641436  MOV ECX,ESI
  // 00641438  CALL EDX
  Word call3 = 0;
  P_DISPATCH(target3, g_dispatch_esp[2], call3);

  // 0064143a  CMP EAX,0x37148141
  // 0064143f  JZ 0x00641456
  if (call3 == kDenyLiteral3) {
    g_restored_esi = g_saved_esi;  // 00641458 POP ESI
    return publish_eax(with_low_byte_cleared(call3));  // 0x37148100
  }

  // 00641441  MOV EAX,[ESI]   -- read #4, independent again
  // 00641443  MOV EDX,[EAX + 0x24]
  Word const table4 = word_at(self, kReceiverDispatchWordDisplacement);
  SlotFn const target4 = dispatch_target_at(table4, kSlotDispatchedByteDisplacement);

  // 00641446  MOV ECX,ESI
  // 00641448  CALL EDX
  Word call4 = 0;
  P_DISPATCH(target4, g_dispatch_esp[3], call4);

  // 0064144a  CMP EAX,0x4f684a4
  // 0064144f  JZ 0x00641456
  //
  // The last of the four, and the only one on a path that continues either way.
  if (call4 == kDenyLiteral4) {
    g_restored_esi = g_saved_esi;  // 00641458 POP ESI
    return publish_eax(with_low_byte_cleared(call4));  // 0x04f68400
  }

  // 00641451  MOV AL,BYTE PTR [ESI+0x26]
  //
  // The one byte of the receiver this body ever touches by displacement, read
  // through ESI with the byte-size prefix that fixes the width. It is READ, not
  // written, and nothing at +0x24, +0x25 or +0x27 is touched. The receiver is an
  // opaque run, so the byte is reached by displacement and the accessor's own
  // type fixes the width the BYTE PTR prefix fixes.
  //
  // The store into EAX is EIGHT bits wide. EAX still holds callee 4's return word
  // at this point -- nothing wrote EAX between 0x00641448 and here -- so the word
  // this body leaves is that return with its low byte replaced by the receiver's
  // byte. It is NOT a zero-extended byte and NOT a bool, which is why the value
  // published by publish_eax() is the whole register while what this function
  // returns is its low byte alone.
  //
  // 00641454  POP ESI
  // 00641455  RET
  g_restored_esi = g_saved_esi;  // 00641454 POP ESI
  return publish_eax(with_low_byte_replaced(call4, byte_at(self, kReceiverResultByteDisplacement)));
}

#undef P_DISPATCH

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641410
