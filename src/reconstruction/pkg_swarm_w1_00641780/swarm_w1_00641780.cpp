// PKG-SWARM-W1-00641780 -- VA 0x00641780
// Sporepedia, unnamed virtual of Sporepedia::cSPAssetDataOTDB
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, image base 0x400000)
//
// The complete body: 19 instructions, 0x00641780..0x006417a5 inclusive
// (ghidra_function.body_start 0x00641780, body_end 0x006417a5, size_bytes 38;
// 0x006417a6..0x006417af are INT3 padding and are NOT part of the body). Every
// line of the model below is annotated with the instruction it comes from.
//
// The listing this was written against was re-derived from the image bytes for
// this package (objdump -d -M intel over 0x641770..0x6417b0 of
// SPORE/SporeBin/SporeApp.exe) rather than taken on trust, and it agrees with
// the committed Ghidra listing instruction for instruction, including the two
// `MOV EDX,[EAX+disp]` lengths:
//
//   00641780  56           push   esi
//   00641781  8b f1        mov    esi,ecx
//   00641783  8b 06        mov    eax,DWORD PTR [esi]
//   00641785  8b 50 10     mov    edx,DWORD PTR [eax+0x10]
//   00641788  ff d2        call   edx
//   0064178a  85 c0        test   eax,eax
//   0064178c  74 14        je     0x6417a2
//   0064178e  8b 06        mov    eax,DWORD PTR [esi]
//   00641790  8b 50 0c     mov    edx,DWORD PTR [eax+0xc]
//   00641793  8b ce        mov    ecx,esi
//   00641795  ff d2        call   edx
//   00641797  85 c0        test   eax,eax
//   00641799  74 07        je     0x6417a2
//   0064179b  b8 01000000  mov    eax,0x1
//   006417a0  5e           pop    esi
//   006417a1  c3           ret
//   006417a2  33 c0        xor    eax,eax
//   006417a4  5e           pop    esi
//   006417a5  c3           ret
//
// FRAME. There is no frame: the only stack effect in the body is the one PUSH
// ESI at 0x00641780 and its two matching POP ESI at 0x006417a0 and 0x006417a4.
// No argument is ever pushed (there is no PUSH other than ESI), no ADD ESP
// appears, and both returns are the one-byte `C3` with no immediate. So the body
// takes ZERO ordinary stack arguments and leaves ESP exactly where it found it.
// That is the machine half of the ABI record's cleanup side (stack_cleanup_bytes
// 0, side "caller").
//
//   entry-4   the saved ESI, parked by 0x00641780 and restored at 0x006417a0 on
//             the true path and at 0x006417a4 on the false path. It is not a
//             parameter and not a return value: both returns are `C3`, and the
//             restored value is the caller's ESI by construction.
//
// VIRTUAL DISPATCH: two indirect calls, and they are the whole body. The
// machine-derived dispatch record agrees on the count (abi_derived.dispatch
// indirect_calls 2) and is silent on the rest (call_offsets [], vtable_shaped
// _loads 0), so both displacements below are taken from the listing itself, not
// from that record. Neither is reached as a struct member: the machine-derived
// receiver record is `bounds_only` (offsets [0], max_offset 0), so it states how
// far this body was seen reaching and says nothing about which member is which,
// and the model therefore declares no member anywhere and reaches every word
// through a displacement-named accessor with the displacement pinned by a
// static_assert in the header.
//
//   00641783/0x00641785  table displacement 0x10 (dword index 4) -- FIRST
//   0064178e/0x00641790  table displacement 0x0c (dword index 3) -- SECOND, out
//                        of the dispatch word as it stands AFTER the first
//                        callee ran
//
// Both reads of the dispatch word are one level out of the receiver and one
// level into the table, which is two dereferences:
// `MOV EAX,[ESI]` then `MOV EDX,[EAX + 0x10]`. A one-level reading of the same
// bytes would be `MOV EDX,[ESI + 0x10]`, which is not an instruction in this
// body. The model therefore loads the word and then indexes through it, and the
// accessor it indexes through takes its base as a `Word` -- not as a pointer --
// so the one-level form is not writable at all. The model test plants live
// observer addresses where a one-level model would look, so that mistake cannot
// survive even if the type were widened.
//
// NOT ASSERTED HERE, deliberately:
//
//  * What the two callees mean. Which concrete functions occupy the cells at
//    +0x10 and +0x0c depends on the table the object carries at run time; this
//    body has no direct callee, no string, no import and no constant that names
//    either one.
//  * That the second call sees the FIRST call's table. The listing shows the
//    second `MOV EAX,[ESI]` is an independent load, so the model re-reads the
//    word. Whether any real callee in this image ever changes that word is a
//    runtime question this package cannot settle; the model test proves only
//    that the model is written to re-read it.
//  * Any receiver word other than the dispatch word. The body reads no other
//    displacement, so the 0x0c bytes after it are an opaque run, and the +0x1c
//    sub-object that the two dispatched callees themselves read is their
//    property and not this body's.
//
// GLOBALS: none. No instruction in the body names a data-segment address.

#include "swarm_w1_00641780_types.hpp"

#include <cstdint>

namespace openspore::reconstruction::pkg_swarm_w1_00641780 {
namespace {

// Model instrumentation, not machine globals. Each is a value a specific pair of
// instructions produces, exposed so the model test can observe it. The header
// explains at length why none of this is a real-register probe.
Word g_saved_esi = 0;
Word g_restored_esi = 0;
Word g_esi_at_entry = 0;
Word g_dispatch_esp_first = 0;
Word g_dispatch_esp_second = 0;

// 0xdeadbeef is the poison both ESI words are filled with between runs. A model
// that popped ESI on only one of the two return paths leaves the other word
// poisoned, which is visible; a model that never popped leaves both poisoned.
constexpr Word kEsiPoison = 0xdeadbeefu;

}  // namespace

Word model_esi_at_entry() { return g_esi_at_entry; }

void model_set_esi_at_entry(Word value) { g_esi_at_entry = value; }

Word saved_esi_frame_word() { return g_saved_esi; }

Word restored_esi_word() { return g_restored_esi; }

void model_reset_esi_probes() {
  g_saved_esi = kEsiPoison;
  g_restored_esi = kEsiPoison;
}

Word dispatch_esp_first_call() { return g_dispatch_esp_first; }

Word dispatch_esp_second_call() { return g_dispatch_esp_second; }

extern "C" Word PKG_SWARM_W1_00641780_THISCALL re_00641780(
    AssetData* receiver) {
  // 00641780  PUSH ESI
  //
  // The body's only stack effect. It is here because the body makes two calls
  // and ESI is call-clobbered; the machine parks the CALLER's ESI and gives it
  // back at 0x006417a0 / 0x006417a4.
  //
  // The model parks it in a frame WORD, not in the real register, and that is a
  // concession to the toolchain rather than a choice. The prescribed build is a
  // PIE, and GCC's i386 PIE sequence for this function is
  // `call __x86.get_pc_thunk.si; addl $_GLOBAL_OFFSET_TABLE_,%esi`: ESI holds the
  // GOT base for the whole body, so a real-register version would read the module
  // address instead of the caller's ESI and a write would break the addressing
  // the compiler is about to emit. The header records this; the model test lists
  // it as deliberately not asserted and carries the PUSH/POP pair as the two
  // poisoned value words below instead, so a model that pops on only one of the
  // two return paths is still visible.
  g_saved_esi = model_esi_at_entry();

  // 00641781  MOV ESI,ECX
  //
  // ESI becomes the receiver alias. Two consequences, both load-bearing:
  //
  //  (a) ECX is NOT changed by this move, and nothing between 0x00641781 and
  //      0x00641788 writes ECX, so the FIRST dispatch still receives the entry
  //      receiver in ECX even though the body never reloads it there. The model
  //      must therefore hand `receiver` -- not a register variable -- to the
  //      first callee.
  //  (b) ESI is overwritten with the receiver, so the caller's ESI is GONE from
  //      the register for the duration of both calls, and a callee sampling ESI
  //      would see the receiver rather than the entry value. This is a MACHINE
  //      fact and the model annotates it, but the model cannot perform it and the
  //      model test cannot assert it, for the PIE reason given above: inside this
  //      translation unit ESI is the GOT base. What the model test does assert
  //      from the trampolines is the weaker and still real fact that nothing
  //      between 0x00641788 and 0x00641795 moves ESI.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00641783  MOV EAX,[ESI]
  //
  // First of the two reads of the dispatch word. It is a load of the receiver's
  // own LEADING word: there is no LEA, ADD or displacement on ESI anywhere in the
  // 19 instructions, so the object whose word is read is the entry receiver
  // itself and not a sub-object of it.
  //
  // The instruction carries no displacement at all -- the listing spells it
  // `MOV EAX,dword ptr [ESI]` with no `+ disp` -- so the zero is the machine's
  // and it is written as a bare base load through `self`, which is exactly what
  // the machine does and exactly what "the leading word" means. The zero is
  // carried by the ABSENCE of a displacement in the listing rather than by a
  // numeric offset written here, and no displacement literal is invented for it:
  // the encoding of 0x00641783 (bytes 8B 06) has no displacement byte at all, so
  // a literal offset in this span would be a constant the machine does not
  // contain. The access still goes through the displacement-named accessor, with
  // the zero named in the header as kDispatchWordDisplacement, so the access is
  // one displacement read and not a hard-wired pointer cast.
  Word const table_first = word_at(self, kDispatchWordDisplacement);

  // 00641785  MOV EDX,[EAX + 0x10]
  //
  // The first of the two table displacements, the model's kSlotCalledFirst. The
  // displacement is read straight out of the instruction and is named in the
  // header, where a static_assert ties it to 0x10. This is the second
  // dereference of the pair: `word_through` takes the base as a Word, so a
  // one-level reading is not writable.
  SlotFn const target_first = reinterpret_cast<SlotFn>(
      word_through(table_first, kSlotCalledFirst));

  // 00641788  CALL EDX
  //
  // No argument is pushed, so the callee takes nothing from the stack. The
  // receiver travels in ECX, unchanged since entry. The model's cell prototype is
  // single-receiver __thiscall for that reason and no other.
  //
  // The ESP publication and the transfer are ONE asm block on purpose. A
  // standalone ESP read immediately before the call is not a witness: at -O0 the
  // compiler inserts 24 bytes of outgoing-argument and register-save space
  // between the read and the call, so the published value would not be the ESP
  // the callee is entered with and could not settle whether an argument was
  // pushed. Inside the block, `movl %%esp,%0` and `call *%2` are adjacent, so the
  // model publishes exactly the stack the callee is entered on, minus the
  // return address. The model test's trampolines read the same quantity and the
  // difference is asserted to be 4.
  //
  // The receiver is placed in ECX inside the block, because there is no C++ call
  // here for the __thiscall convention to carry it: the machine transfer is
  // `CALL EDX`, a call through a register, and 0x00641793 MOV ECX,ESI is the
  // machine's way of re-establishing that. ESI is not written and not listed as
  // clobbered, so the block is not asserting anything about it -- the PIE reason
  // above is why the block cannot.
  // The register constraints are fixed rather than "r" because this block needs
  // three registers while clobbering two more, and EBX is the GOT base in a
  // PIE: EAX carries the result out, EBX the target, EDI the receiver, and ECX
  // and EDX are free to be destroyed by the callee.
  Word first = 0;
  __asm__ __volatile__("movl %%esp, %0\n\t"
                       "movl %3, %%ecx\n\t"
                       "call *%2\n\t"
                       "movl %%eax, %1\n\t"
                       : "=m"(g_dispatch_esp_first), "=a"(first)
                       : "b"(reinterpret_cast<std::uintptr_t>(target_first)),
                         "D"(reinterpret_cast<std::uintptr_t>(receiver))
                       : "ecx", "edx", "cc", "memory");

  // 0064178a  TEST EAX,EAX
  // 0064178c  JZ 0x006417a2
  //
  // The whole 32 bits of the callee's result are tested for zero -- it is a
  // null test, not a comparison against 1, and it is not signed. Every non-zero
  // pattern, 0x80000000 and 0xffffffff included, takes the fall-through. The
  // branch is a taken-when-zero: polarity is fixed by `JZ`, and the model test
  // drives 0, 1, 0x80000000 and 0xffffffff through it.
  if (first == 0) {
    // 006417a2  XOR EAX,EAX
    // 006417a4  POP ESI
    // 006417a5  RET
    //
    // A full 32-bit zero, not a cleared low byte, and the saved ESI is restored
    // on this path too. Reaching 0x006417a2 from 0x0064178c means the second
    // dispatch never happens: the +0x0c cell is not read, not called, and the
    // +0x10 callee's result is discarded rather than forwarded.
    g_restored_esi = g_saved_esi;  // 006417a4 POP ESI
    return 0;
  }

  // 0064178e  MOV EAX,[ESI]
  //
  // The SECOND, independent read of the same word. This is not a redundant copy
  // of the first read: between the two there is a CALL, and this body does
  // nothing else, so the second dispatch is decided by the value the dispatch
  // word holds after the first callee has returned. The model performs a second
  // load rather than reusing `table_first`, and the model test proves the
  // difference by having the first callee overwrite the word.
  //
  // Base load through `self`, with no displacement added, for the same reason as
  // the load at 0x00641783: the instruction states no displacement, so there is
  // none to state here either. The re-read is what is being modelled, and it is
  // visible in the source as a second independent load rather than as a reuse of
  // the first one.
  Word const table_second = word_at(self, kDispatchWordDisplacement);

  // 00641790  MOV EDX,[EAX + 0xc]
  //
  // The second table displacement, the model's kSlotCalledSecond, reached only
  // when the 0x10 callee returned non-zero. The displacement is again straight
  // out of the instruction and again named in the header, where a static_assert
  // ties it to 0x0c.
  SlotFn const target_second = reinterpret_cast<SlotFn>(
      word_through(table_second, kSlotCalledSecond));

  // 00641793  MOV ECX,ESI
  //
  // 00641795  CALL EDX -- same one-block discipline as the first dispatch, for
  // the same reason.
  //
  // The receiver goes back into ECX. The machine needs this because the first
  // callee is free to destroy ECX (it is not a callee-saved register), and
  // 0x00641781's copy in ESI is what survives. In the model `receiver` is passed
  // directly and this instruction is a no-op at the source level; it is
  // annotated rather than emulated because its only machine-level content is
  // "the second callee gets the same receiver as the first".
  //
  // 00641795  CALL EDX
  //
  // Again with no stack argument, and the model samples ESP here so the test can
  // assert that the two dispatches happen at the same stack depth.
  Word second = 0;
  __asm__ __volatile__("movl %%esp, %0\n\t"
                       "movl %3, %%ecx\n\t"
                       "call *%2\n\t"
                       "movl %%eax, %1\n\t"
                       : "=m"(g_dispatch_esp_second), "=a"(second)
                       : "b"(reinterpret_cast<std::uintptr_t>(target_second)),
                         "D"(reinterpret_cast<std::uintptr_t>(receiver))
                       : "ecx", "edx", "cc", "memory");

  // 00641797  TEST EAX,EAX
  // 00641799  JZ 0x006417a2
  //
  // Identical shape to the first test, same 32-bit null test, same taken-when-
  // zero polarity, and the same shared false block at 0x006417a2. Both arms
  // therefore leave through the SAME `XOR EAX,EAX / POP ESI / RET`, which is
  // why the model has one false return rather than two.
  if (second == 0) {
    // 006417a2 / 006417a4 / 006417a5
    g_restored_esi = g_saved_esi;  // 006417a4 POP ESI
    return 0;
  }

  // 0064179b  MOV EAX,0x1
  //
  // A literal 1 in all 32 bits, produced fresh. Nothing of either callee's
  // result is forwarded, masked or projected: the two EAX values that reached
  // the TEST instructions are gone, and the caller's only observable output is
  // "both were non-zero". This is why the return type is `Word` -- the 32-bit
  // word this immediate builds -- and not the callees' type.
  //
  // The 1 is spelled as a hexadecimal literal on purpose: it is the one constant
  // this span states, and 0x1 is the immediate the listing itself carries at
  // 0x0064179b, so the constant the model writes is the machine's own. The
  // false paths above return a plain decimal 0 because 0x006417a2 is
  // `XOR EAX,EAX`, which produces its zero from the register and states no
  // literal at all.
  //
  // `Word` is the alias the header declares for `std::uint32_t`, and it is the
  // spelling the return type of this function carries. The machine-derived ABI
  // record has no C type for EAX to compare it against -- abi_derived.value.return
  // is {register EAX, register_class integral, type null, void_possible false} --
  // so the sidecar states the declared type and records the machine's
  // register-class phrase, `unclassified_in_EAX`, separately rather than turning
  // the phrase into a typedef. Nothing in this body is typed by that phrase.
  //
  // 006417a0  POP ESI
  // 006417a1  RET
  g_restored_esi = g_saved_esi;  // 006417a0 POP ESI
  return 0x1;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641780
