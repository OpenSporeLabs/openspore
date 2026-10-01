// PKG-SWARM-W1-00641FD0 -- VA 0x00641fd0
// FUN_00641fd0, the unnamed Sporepedia member function
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 62 instructions, 0x00641fd0..0x0064206c inclusive, 157
// bytes (ghidra_function.body_start 0x00641fd0, body_end 0x0064206c,
// body_span_bytes 157, size_bytes 157; abi_derived.parse.declared_count 62,
// unparsed 0, degraded false). Every group of lines below is annotated with the
// instructions it comes from, and the listing it was written against was
// re-decoded from the 157 image bytes for this package rather than taken on
// trust -- the byte string is in the header, it decodes to these 62
// instructions, and it ends exactly at 0x0064206c + 1.
//
// SHAPE: a fast path on top, a four-gate early-out chain under it, and a
// duplicated two-level acquire at the bottom. The gate order is fixed by the
// listing and each gate's failure target is named in its own annotation below.
// There are SEVEN conditional branches -- the validator's own branch count for
// this body agrees at 7 -- and every one of their targets lies inside the body:
//
//   0x00641fdb JNZ 0x00642068   the cached word at the receiver's +0x3c
//   0x00642000 JZ  0x00642065   the slot +0x90 dispatch returned zero
//   0x0064200c JZ  0x00642065   the service word is null
//   0x0064201b JZ  0x00642065   0x00613860 returned zero
//   0x00642043 JZ  0x0064205a   0x00612f50 returned zero  (the NEAR arm)
//   0x00642049 JZ  0x00642052   the far arm's handle is null
//   0x0064205c JZ  0x00642065   the near arm's handle is null
//
// Four of those seven reach the shared null exit 0x00642065, one splits the tail
// in two, one skips the far arm's acquire, and one takes the fast path. The
// branch graph is a tree: there is no unconditional jump, no loop and no branch
// backwards, so no state is carried between two visits of any instruction.

// FRAME, walked instruction by instruction with each callee's own RET immediate
// settling the stack. Entry ESP is written E below.
//
//   00641fd0  SUB  ESP,0xc      E-12   three frame words: E-12, E-8, E-4
//   00641fd3  PUSH ESI          E-16   saved ESI
//   00641fe4  PUSH EDI          E-20   saved EDI
//   00641ffc  CALL EDX          E-24 -> E-20   the callee pops its one word
//   00642014  CALL 0x613860     E-24 -> E-20   RET 0x4, from 0x6138a1
//   00642038  CALL 0x612f50     E-36 -> E-20   RET 0x10, from 0x61300f
//   00642067  POP  EDI / 0x00642068 POP ESI / 0x00642069 ADD ESP,0xc   -> E
//
// Three independent checks say those three pops are right, and each is stated
// where it is used below. What the frame fixes, as values:
//
//   entry-4    the SECOND word of the 8-byte frame object
//   entry-8    the FIRST word of it, and the address the slot +0x90 dispatch is
//              handed
//   entry-12   the out-slot: zeroed at 0x00642030, handed to 0x00612f50 as its
//              third argument, read back at 0x0064203d
//
// VIRTUAL DISPATCH: three indirect calls, and all three are TWO-LEVEL. 0x00641fed
// loads the table word out of the receiver's own +0x00 and 0x00641fef loads the
// slot word out of THAT at +0x90 (0x00641ffc calls it). 0x0064204b and 0x0064205e
// each load a handle's own leading word and 0x0064204d and 0x00642060 each load
// the slot word out of that at +0x04. Neither level is optional and neither may
// be collapsed: reading `*(receiver + 0x90)` instead of `*(*(receiver + 0x00) +
// 0x90)` is a different address on every live object, and the model test plants
// a valid slot pointer at the wrong depth precisely to make that mistake
// observable rather than fatal.
//
// The machine-derived ABI record agrees on the count: dispatch.indirect_calls 3,
// which is also the number of indirect transfers the complete listing names.
// dispatch.call_offsets is empty and dispatch.vtable_shaped_loads is 0 -- the
// second of those is the record saying the loads are plain dword loads at a
// displacement, with no shape it could recognise as a vtable access, which is
// why nothing below relies on the record for the slots and the listing supplies
// them.
//
// ABI: __thiscall, receiver in ECX, no ordinary stack argument, bare `RET` on
// both exits, saved registers ESI and EDI. The record agrees on all of it:
// abi.calling_convention __thiscall, abi.saved_registers ["EDI", "ESI"],
// abi.ret_form "RET", abi.stack_cleanup_bytes 0, abi.stack_cleanup_owner
// "caller", abi.receiver_register "ECX", and receiver.offsets [0, 8, 60] with
// receiver.register "ECX" and shape R-ALIAS -- exactly the three receiver
// displacements this body reaches.
//
// GLOBALS: none. No instruction in the 62 names a data-segment address. The
// nearest thing to a global is the object 0x0067cb30 returns, which it reads
// out of one in ITS OWN six bytes; the address is recorded in the header and in
// the metadata sidecar and is deliberately not written in this body.
//
// WRITES: three stores, all to the body's own frame -- 0x00641fe5 and
// 0x00641fe9 (the two words of the 8-byte object) and 0x00642030 (the out-slot,
// zero). There is NO store to the receiver anywhere in the 62, and the model
// test byte-compares the receiver before and after every call to keep that
// falsifiable. The other writes in the body are the two indirect calls' own
// effects, which this body does not control and the model test observes only.
//
// The decompiler disagrees in four places and the listing wins all four. Ghidra
// prints `__fastcall FUN_00641fd0(int *param_1)`: there is no use of EDX
// anywhere in the 62 instructions except as a scratch for a table word and a
// stack argument, and the receiver demonstrably arrives in ECX (0x00641fd4, and
// 0x00641ffa reloading it for the slot +0x90 dispatch), so the convention is
// __thiscall with no stack argument at all -- Ghidra's own parameter count for
// this VA is 0. Ghidra prints `cVar1 = (**(code **)(*param_1 + 0x90))(&local_8)`,
// which is the same two-level dispatch and the same address (its `local_8` is
// this body's entry-8 word), but as a value it infers where the machine forms
// an address. Ghidra prints `FUN_00612f50(uStack_c, local_8, &stack0xfffffff0,
// 0)`: the first argument is the receiver's own uninitialised `uStack_c` -- the
// frame word at entry-12, which this body ZEROES at 0x00642030 and never reads
// before handing its address over -- so the printout both passes a value the
// machine passes by address and gets the two data arguments in the wrong order
// (the machine's first data argument is the entry-8 word, its second is the
// entry-4 word). And Ghidra's decompilation returns 0 on every path, while the
// listing returns three different words: see the exit annotations.

#include "sw1_00641fd0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00641fd0 {

extern "C" void* PKG_SW1_00641FD0_THISCALL sporepedia_cached_handle_00641fd0(
    SporepediaAssetDataOtdb* receiver) {
  // 00641fd0  SUB  ESP,0xc
  // 00641fd3  PUSH ESI
  // 00641fd4  MOV  ESI,ECX
  //
  // ESI becomes the receiver alias and every receiver access in the body goes
  // through it, including the ECX reload for the slot +0x90 dispatch at
  // 0x00641ffa. The two pushes are the save halves of the two callee-saved
  // registers the body touches, and both exits pop both of them. The model does
  // not reproduce the pushes -- the compiler saves whatever it uses -- but they
  // are why ESI is on the record's saved_registers list and why the record
  // reports the receiver with shape R-ALIAS rather than naming one register.
  //
  // The receiver is taken as a byte run and every access below is a DISPLACEMENT
  // into it. The record enumerates offsets [0x00, 0x08, 0x3c] and is
  // bounds_only, so no member name is written for any of the three.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00641fd6  MOV  EAX,DWORD PTR [ESI+0x3c]
  // 00641fd9  TEST EAX,EAX
  // 00641fdb  JNZ  0x00642068
  //
  // Gate zero, and the only gate that SKIPS work rather than failing: a nonzero
  // word at the receiver's own +0x3c leaves the body immediately, and the value
  // left in EAX is that very word -- the target of the jump is 0x00642068, which
  // is the shared epilogue and which never overwrites EAX. So the cached word is
  // the return value, unconverted and untouched, and the four gates below do not
  // run at all.
  //
  // The word is a WORD here and not a pointer: the body compares it against zero
  // and returns it, and it never dereferences it. The model returns it as the
  // same machine word the function's return type carries, so the declaration
  // says void* while this path is a plain value pass-through. The two readings
  // that are NOT this one, and which the model test drives against, are a
  // pointer-null test on what the word POINTS at (a nonzero word pointing at a
  // zero is a true to that reading and is a return-value here) and a one-byte
  // test (a word of 0x00000100 is a return value here and a false to that one).
  const Word cached = *word_at(self, kReceiverCachedWordDisplacement);
  if (cached != 0u) {
    // 00642068  POP  ESI
    // 00642069  ADD  ESP,0xc
    // 0064206c  RET
    //
    // EAX still holds the word 0x00641fd6 loaded. Note the target 0x00642068 is
    // INSIDE the shared tail, not at 0x00642065: this path skips the
    // `XOR EAX,EAX` that every failing gate falls into, which is the whole
    // observable difference between the five exits below and this one.
    return reinterpret_cast<void*>(cached);
  }

  // 00641fe1  OR  EAX,0xffffffff
  //
  // Materialises the sentinel 0xffffffff. The OR ITSELF is dead: EAX is the
  // receiver's +0x3c word and 0x00641fd9 proved it is zero on this path, and
  // `OR EAX,0xffffffff` is a register-to-register operation. What survives is the
  // constant, which the next two instructions copy into the frame.
  //
  // 00641fe5  MOV  DWORD PTR [ESP+0xc],EAX    with ESP = entry-20, so entry-8
  // 00641fe9  MOV  DWORD PTR [ESP+0x10],EAX   with ESP = entry-20, so entry-4
  //
  // The 8-byte frame object is seeded with the sentinel in BOTH words before
  // anything is called, and both words are written unconditionally -- there is no
  // path that seeds one and not the other. What the sentinel MEANS is not fixed
  // by any record: it is the value the body hands the dispatch below, and the
  // dispatch is free to overwrite either word.
  HandlePair pair;
  word_ref(&pair, kHandlePairFirstDisplacement) = kUnsetHandleWord;
  word_ref(&pair, kHandlePairSecondDisplacement) = kUnsetHandleWord;

  // 00641fed  MOV  EAX,DWORD PTR [ESI]
  //
  // The FIRST level of the first dispatch. The word at the receiver's own +0x00
  // IS a table pointer -- the receiver's leading word is its table -- which is
  // why the second level below reads through EAX and never through ESI. The model
  // test plants a decoy word at the receiver's +0x04 that also looks like a
  // table, so a reconstruction that collapsed the two levels would dispatch into
  // it and be caught.
  void* const table = *reinterpret_cast<void* const*>(word_at(self, kReceiverTableDisplacement));

  // 00641fef  MOV  EDX,DWORD PTR [EAX+0x90]
  //
  // The SECOND level: one slot word out of the table, at displacement 0x90, index
  // 36. It is not the index this body itself sits at in the table its own xrefs
  // name -- reading 0x013ff6e4 in the image gives 0x00641fd0, which is
  // 0x013ff6ac + 0x38, index 14 -- and the word at 0x01462764 + 0x90 is
  // 0x00641fd0 itself, so the dispatch can re-enter this body. Nothing here may
  // assume the slot target is a different function.
  //
  // 00641ff5  LEA  ECX,[ESP+0xc]     with ESP = entry-20, so the ADDRESS of the
  //                                     first word of the frame object
  // 00641ff9  PUSH ECX
  // 00641ffa  MOV  ECX,ESI            the receiver is the receiver ITSELF: not
  //                                   the table word, not the frame object
  // 00641ffc  CALL EDX
  //
  // One stack word, by address, and the receiver in ECX. The callee is a
  // __thiscall member function (it pops its own word, which is the only reading
  // under which the two frame reads at 0x0064201d and 0x00642021 resolve to the
  // two words of the object -- see the re-read annotation below).
  const ResolveSlot90 resolve =
      *reinterpret_cast<ResolveSlot90 const*>(load_slot(table, kResolveSlotDisplacement));
  if (resolve(receiver, &pair) == 0u) {
    // 00641ffe  TEST AL,AL
    // 00642000  JE   0x642065
    //
    // The test is of the whole of AL against zero, so the fall-through covers
    // every nonzero byte, 0x01 through 0xff alike, and it is emphatically not a
    // comparison against 1. The jump target 0x00642065 is the `XOR EAX,EAX`
    // exit, so a zero here returns null with no further call.
    return nullptr;
  }

  // 00642002  CALL 0x67cb30
  //
  // The one direct call that takes no receiver and no argument: 0x0067cb30 is
  // six bytes of `MOV EAX,ds:0x15fcc70; RET`. It hands back one global's value
  // and the body uses it as the base of the next read, so the address of that
  // global is the callee's business and not this body's -- which is why it is
  // named in the header's declaration and not here.
  ServiceRoot* const root = static_cast<ServiceRoot*>(service_root_global_0067cb30());

  // 00642007  MOV  EDI,DWORD PTR [EAX+0x5c]
  // 0064200a  TEST EDI,EDI
  // 0064200c  JE   0x642065
  //
  // Gate two. One word at +0x5c of the object just fetched, compared against
  // zero as a POINTER: the word is the service, it is null-tested, and it becomes
  // the receiver of the next two calls. This is the read that decides where the
  // +0x5c lives -- on the object 0x0067cb30 returned, and on nothing else. The
  // model test plants a decoy service word at the receiver's own +0x5c to keep
  // that straight.
  Service* const service =
      *reinterpret_cast<Service* const*>(word_at(root, kServiceRootServiceDisplacement));
  if (service == nullptr) {
    return nullptr;
  }

  // 0064200e  MOV  EAX,DWORD PTR [ESI+0x8]
  // 00642011  PUSH EAX
  // 00642012  MOV  ECX,EDI
  // 00642014  CALL 0x613860
  //
  // Gate three. The one word the receiver has at +0x08 goes over the stack as the
  // callee's FIRST argument -- the callee reads it at its own entry+4
  // (0x613885) -- and the service is the receiver. The callee pops the word
  // (`RET 0x4` at 0x6138a1), which is the only reading under which the two
  // frame re-reads below resolve to the frame object. The word is passed BY
  // VALUE: the body loads it and pushes the loaded value, and never
  // dereferences it.
  if (service_key_present_00613860(service, *word_at(self, kReceiverArgumentDisplacement)) == 0u) {
    // 00642019  TEST AL,AL
    // 0064201b  JE   0x642065
    //
    // The same byte test as gate one, with the same consequence: nonzero falls
    // through and zero returns null. The upper three bytes of EAX are the
    // callee's leftovers and are not modelled; the model test drives 0x80 here,
    // which is a true to this body and a false to any `== 1` reconstruction.
    return nullptr;
  }

  // 0064201d  MOV  EDX,DWORD PTR [ESP+0x10]
  // 00642021  MOV  EAX,DWORD PTR [ESP+0xc]
  //
  // The two words of the frame object are RE-READ here, with ESP = entry-20 in
  // both cases, so entry-4 into EDX and entry-8 into EAX. This is the step that
  // makes the dispatch above an out-parameter rather than an in-parameter: the
  // values passed on are whatever the dispatch WROTE into the object, not the
  // sentinel it was seeded with. A reconstruction that cached the sentinel in a
  // register across the call would pass 0xffffffff here and the model test kills
  // it, because the dispatch in the test writes two distinctive words.
  const Word first = *word_at(&pair, kHandlePairFirstDisplacement);
  const Word second = *word_at(&pair, kHandlePairSecondDisplacement);

  // 00642025  PUSH 0x0
  // 00642027  LEA  ECX,[ESP+0xc]     with ESP = entry-24, so entry-12
  // 0064202b  PUSH ECX
  // 0064202c  PUSH EDX
  // 0064202d  PUSH EAX
  // 0064202e  MOV  ECX,EDI
  // 00642030  MOV  DWORD PTR [ESP+0x18],0x0    with ESP = entry-36, so entry-12
  // 00642038  CALL 0x612f50
  //
  // Gate four, the widest call in the body: four words, pushed right to left, so
  // the callee's first argument is EAX (the frame object's first word), its
  // second is EDX (its second word), its third is the ADDRESS of the frame word
  // at entry-12, and its fourth is the literal zero. The last store is not part
  // of the call: it zeroes the frame word AFTER all four arguments are on the
  // stack and immediately BEFORE the call, and the address it uses, entry-12, is
  // the same address 0x00642027 formed -- which is what pins the two together.
  //
  // The callee pops all sixteen bytes (`RET 0x10` at 0x61300f), and that is what
  // makes 0x0064203d's read below resolve to entry-12 rather than to one of the
  // four argument words.
  void* resolved = kFrameSeedMarker;  // instrumentation: see the header
  resolved = nullptr;                 // 00642030
  if (service_handle_resolve_00612f50(service, first, second, &resolved, 0) == 0u) {
    // 00642041  TEST AL,AL
    // 00642043  JE   0x64205a
    //
    // 0064203d  MOV ECX,DWORD PTR [ESP+0x8]   ran BEFORE this test, with
    // ESP = entry-20, so it reads entry-12: the word the callee left behind. The
    // test that follows is of the callee's BYTE, and the word it loaded is
    // unrelated to it -- two different things, both of which the model below
    // keeps apart. A reconstruction that returned the callee's own byte as the
    // result, or that treated the byte as the handle, is refuted by the two cases
    // in the model test that separate them.

    // 0064205a  TEST ECX,ECX
    // 0064205c  JE   0x642065
    //
    // The FALSE arm still acquires. This is the arm most easily reconstructed
    // wrongly, because it looks like the error path: the same two-level acquire
    // below runs here before the body returns null, so a resolution that fails
    // but still produced a handle STILL takes the reference and throws the
    // handle away.
    if (resolved != nullptr) {
      // 0064205e  MOV  EDX,DWORD PTR [ECX]
      // 00642060  MOV  EAX,DWORD PTR [EDX+0x4]
      // 00642063  CALL EAX
      Acquired* const handle = static_cast<Acquired*>(resolved);
      void* const handle_table =
          *reinterpret_cast<void* const*>(word_at(handle, kReceiverTableDisplacement));
      const AcquireSlot04 acquire =
          *reinterpret_cast<AcquireSlot04 const*>(load_slot(handle_table, kAcquireSlotDisplacement));
      acquire(handle);
    }
    // 00642065  XOR  EAX,EAX
    // 00642067  POP  EDI
    // 00642068  POP  ESI
    // 00642069  ADD  ESP,0xc
    // 0064206c  RET
    //
    // The shared null exit. Note 0x00642065 is reached by four different gates
    // and by this arm, and it is the one exit that is not the fast path: it
    // zeroes EAX, so every failing gate returns the same null.
    return nullptr;
  }

  // 00642045  MOV  ESI,ECX
  //
  // The TRUE arm. ESI -- the receiver alias -- is OVERWRITTEN with the resolved
  // handle, and the body never uses ESI as the receiver again, so the receiver is
  // not read after this point on any path.
  //
  // 00642047  TEST ECX,ECX
  // 00642049  JE   0x642052
  //
  // The handle is null-checked, and the check is meaningful: the word at entry-12
  // can be either value, and the callee's return byte and that word are
  // independent. A true arm with a null handle skips the acquire AND still
  // returns null, because 0x00642053 moves the same null into EAX.
  if (resolved != nullptr) {
    // 0064204b  MOV  EDX,DWORD PTR [ECX]
    // 0064204d  MOV  EAX,DWORD PTR [EDX+0x4]
    // 00642050  CALL EAX
    //
    // The acquire, at displacement 0x04, index 1, off the HANDLE's own leading
    // word. This is the same pair of instructions as 0x0064205e and 0x00642060
    // on the other arm -- the original carries the duplication, and this model
    // carries it too rather than factoring it into a helper the listing does not
    // have. The callee takes the handle in ECX and no stack word; its return
    // value is dead, because 0x00642053 overwrites EAX.
    Acquired* const handle = static_cast<Acquired*>(resolved);
    void* const handle_table =
        *reinterpret_cast<void* const*>(word_at(handle, kReceiverTableDisplacement));
    const AcquireSlot04 acquire =
        *reinterpret_cast<AcquireSlot04 const*>(load_slot(handle_table, kAcquireSlotDisplacement));
    acquire(handle);
  }
  // 00642052  POP  EDI
  // 00642053  MOV  EAX,ESI
  // 00642055  POP  ESI
  // 00642056  ADD  ESP,0xc
  // 00642059  RET
  //
  // The return is ESI, which 0x00642045 loaded with the handle -- not the
  // callee's return byte, and not a dereference of the handle. So the observable
  // result of the whole function is: the receiver's cached word if it was
  // nonzero, else the handle the resolution produced, else null. The handle is
  // acquired once on the way out, and the reference is never released here.
  return resolved;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00641fd0
