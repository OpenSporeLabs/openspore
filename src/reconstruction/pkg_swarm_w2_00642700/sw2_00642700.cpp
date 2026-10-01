// PKG-SWARM-W2-00642700 -- VA 0x00642700
// FUN_00642700, an unnamed Sporepedia member function
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// The complete body: 114 instructions, 0x00642700..0x00642833 inclusive, 308
// bytes. The committed record and the image agree on all four extent numbers
// (body_start 0x00642700, body_end 0x00642833, body_span_bytes 308, size_bytes
// 308) and the byte string in the header decodes to these 114 instructions and
// stops one byte into the INT3 padding at 0x00642834, so no listing correction
// is needed or claimed here.
//
// SHAPE: one gate, then FIVE unrolled copies of the same append. The gate is
// 0x00642708 `JNZ 0x0064282e`; the five appends start at 0x00642713, 0x0064274c,
// 0x00642781, 0x006427b6 and 0x006427eb. There is no loop and no backward
// branch: the original unrolled the append five times because the five calls
// carry five different literals, and this model carries the same duplication
// rather than factoring it into a helper the listing does not have. The
// consequence for a reader is that the transfer sequence of one call is five
// transfers long and a loop-shaped reconstruction would be a different body.
//
// BRANCHES: eleven conditional branches, every target inside the span. One gate
// and, per append, two:
//
//   0x00642708  JNZ 0x0064282e   the gate word at the receiver's +0x08
//   0x0064272f  JNC 0x0064273f   cursor >= capacity  -> grow
//   0x00642739  JZ  0x0064274c   cursor is null       -> skip the store
//   0x00642764  JNC 0x00642774
//   0x0064276e  JZ  0x00642781
//   0x00642799  JNC 0x006427a9
//   0x006427a3  JZ  0x006427b6
//   0x006427ce  JNC 0x006427de
//   0x006427d8  JZ  0x006427eb
//   0x00642803  JNC 0x00642819
//   0x0064280d  JZ  0x00642826
//
// plus five intra-procedural `JMP 0x00642...` (0x0064273d, 0x00642772,
// 0x006427a7, 0x006427dc) that skip a store and land back on the next append.
// No instruction is reached twice on any path, so no state is carried between
// two visits of any address and the model needs no loop invariant.
//
// JNC IS AN UNSIGNED COMPARE AND THE MARGIN IS EXACT. `CMP ECX,[ESI+0x8]` then
// `JNC` grows when cursor >= capacity, so the in-place arm needs
// cursor < capacity STRICTLY. cursor == capacity grows, and a signed reading of
// the same compare would take the in-place arm for a cursor above 0x7fffffff
// with a smaller capacity, writing through a pointer the machine never forms.
//
// FRAME, walked with each callee's OWN terminator settling the stack -- the
// callee's return-address pop included, which is what makes the walk balance.
// Entry ESP is E below and every offset is relative to it.
//
//   00642700  PUSH ECX          E-4   the receiver, and later the first value
//   0064270e  PUSH ESI          E-8   saved ESI
//   0064270f  PUSH EDI          E-12  saved EDI
//   00642719  CALL 0x00556140   E-20 -> E-24 -> E-20   bare RET at 0x0055620a
//                                        pops only the return address, so the
//                                        two words the call pushed are still
//                                        on the stack here
//   00642725  ADD ESP,0x8       E-20 -> E-12  the caller drops those two words
//   00642728  MOV [ESP+0x8],EAX E-12 -> E-4   the result goes into the slot
//                                        PUSH ECX filled: the receiver word is
//                                        overwritten and never read again
//   00642747  CALL 0x004558a0   E-12 -> E-20 -> E-12  RET 0x8 at 0x00455ad4 pops
//                                        the return address and both words
//   00642826  POP EDI / 0x00642829 POP ESI / 0x0064282a POP ECX   E-12 -> E
//   0064282b  RET 0x4           E -> E+4, i.e. the one argument word, callee side
//
// Two things fall out of that walk and both are load-bearing:
//
//  1. 0x0064271e `MOV ESI,[ESP+0x18]` runs with ESP = E-20, so the slot it
//     reads is E+4: the body's single ordinary stack argument, the vector. That
//     is the only reading of that displacement, and it is what makes the
//     argument count exactly one.
//  2. The per-append value slot is NOT the same address every time, and the
//     model does not pretend otherwise. Iterations two through five all compute
//     it as [ESP+0x10] with ESP = E-12, i.e. E+4 -- the CALLER'S OWN ARGUMENT
//     WORD, which the body has not read since 0x0064271e and which it therefore
//     overwrites. Iteration one computes it as [ESP+0x8] with ESP = E-12, i.e.
//     E-4, the slot the receiver was pushed into. The model uses one local for
//     the value in every iteration, because the incoming argument is dead after
//     0x0064271e and no address the body computes is ever passed back out in a
//     way a caller can observe. That is stated here rather than asserted in the
//     test: the machine's two addresses differ and the model's do not, and
//     nothing in the machine's observable behaviour distinguishes them.
//
// WRITE ORDER is fixed by the listing and is not the natural source order. The
// fast arm advances the cursor FIRST (0x00642731/0x00642734) and only then
// null-tests and stores (0x00642737/0x00642739/0x0064273b), so a cursor that is
// null still moves the cursor to +0x04. The slow arm touches neither word: at
// the moment 0x004558a0 is entered the cursor word still holds the value the
// append's own `MOV ECX,[ESI+0x4]` loaded, because 0x00642734/0x00642769/
// 0x0064279e/0x006427d3/0x00642808 are all on the fast arm only.
//
// DE-REGISTRATION CORROBORATION, which is why the receiver's +0x08 gate is not
// a guess about a magic number. 0x00556140's own body reads its first argument
// at 0x0055614d and compares the SECOND word of it against 0x2b978c46 at
// 0x00556150 -- the same literal this body compares the receiver's +0x08
// against at 0x00642701. Since this body hands 0x00556140 the receiver's +0x04
// (0x00642710), the two reads are the same address, and the descriptor the body
// forms is the receiver's own +0x04 .. +0x0b.
//
// The decompiler agrees with all of that and is quoted here only for its
// disagreements, of which there are two. Ghidra prints
// `__thiscall FUN_00642700(int param_1,int param_2)` and models the receiver as
// `param_1`; the machine takes the receiver in ECX and has exactly ONE ordinary
// argument, so Ghidra's second parameter is this body's receiver and its first is
// the vector. And Ghidra's `local_4` is this body's E-4 slot, which is the
// receiver's own word on the way in and the first lookup's result on the way
// out; Ghidra's `iVar1` is the receiver + 4, the descriptor; both of those are
// followed here. Ghidra also prints the capacity test as
// `if (piVar2 < *(int **)(param_2 + 8))`, which is the same unsigned condition
// as 0x0064272f/0x0064272c read a different way round, and Ghidra places the
// null cursor guard before the store, which the listing also does.

#include "sw2_00642700_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00642700 {

extern "C" bool PKG_SWARM_W2_00642700_THISCALL
sporepedia_append_five_lookups_00642700(SporepediaTypeKeySource* receiver,
                                        SporepediaTypeKeyVector* vector) {
  // 00642700  PUSH ECX
  //
  // The receiver is saved into the frame and the frame slot is reused twice
  // below: it becomes the first append's value slot at 0x00642728 and the
  // address handed to 0x004558a0 on the first slow arm at 0x0064273f. The
  // receiver is never recovered from it -- every later receiver access is a
  // displacement off EDI -- so the slot is dead to the body the moment the alias
  // is formed.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00642701  CMP  dword ptr [ECX + 0x8],0x2b978c46
  // 00642708  JNZ  0x0064282e
  //
  // The gate. One dword, compared EQUALITY against one literal, and the branch
  // is "not equal" -> the false exit. Nothing is read before it, so a receiver
  // that fails the gate has its argument object left completely untouched: the
  // model test asserts that byte for byte.
  //
  // The literal's MEANING is not fixed by this body. It is the same word
  // 0x00556140 checks at its own 0x00556150, and 0x00556140 accepts a second
  // literal there (0x3d97a8e4 at 0x0055615c) that this body never tests -- so
  // this is one of at least two accepted identities, and no record says what
  // either is. Nothing is claimed.
  if (*word_at(self, kSourceGateDisplacement) != kSourceGateWord) {
    // 0064282e  XOR  AL,AL
    // 00642830  POP  ECX
    // 00642831  RET 0x4
    //
    // The only exit that returns false, and it is reached by exactly one
    // instruction. Note the epilogue pops ECX only: the two callee-saved
    // registers were never pushed on this path, because the gate is tested
    // before 0x0064270e and 0x0064270f run. AL is written as a BYTE, so the
    // upper three bytes of EAX are whatever the compare left there.
    return false;
  }

  // 0064270e  PUSH ESI
  // 0064270f  PUSH EDI
  //
  // The two callee-saved registers the body uses, and both are popped on all
  // three exits. The model does not reproduce the pushes -- a compiler saves
  // whatever it uses -- but they are why ESI and EDI are on the record's
  // saved_registers list.
  //
  // 00642710  LEA  EDI,[ECX + 0x4]
  //
  // The receiver's +0x04, formed as an ADDRESS and never as a loaded word. It
  // is the first argument of all five lookups, so one LEA and five pushes serve
  // the whole body; nothing between them changes EDI, and the 0x00556140 calls
  // are cdecl and do not clobber it.
  SporepediaTypeDescriptor* const descriptor =
      reinterpret_cast<SporepediaTypeDescriptor*>(self + kSourceLookupBaseDisplacement);

  // 00642713  PUSH  0xa426730b
  // 00642718  PUSH  EDI
  // 00642719  CALL  0x00556140
  //
  // Lookup one. Two words pushed, so the FIRST argument is the descriptor and
  // the SECOND is the key -- which is the order the callee's own reads fix
  // (0x0055614d takes the descriptor at [EBP+0x8] and 0x005561e2 takes the key
  // at [EBP+0xc]). The callee pops nothing; see the frame walk above.
  const Word key_one = 0xa426730bu;
  // 0064271e  MOV  ESI,[ESP + 0x18]
  //
  // The one ordinary stack argument, at E+4. It is read here, once, and never
  // again -- the five appends all reach it through ESI.
  //
  // 00642722  MOV  ECX,[ESI + 0x4]
  // 00642725  ADD  ESP,0x8
  // 00642728  MOV  dword ptr [ESP+0x8],EAX
  //
  // The cursor is loaded and the two pushed words are dropped, and then the
  // lookup's result is parked in the frame. Note what the load is: a dword
  // READ AS A dword, which becomes the address the store at 0x0064273b writes
  // through. `value` is a Word for exactly that reason, not a pointer -- the
  // body never dereferences what the lookup returns.
  Word value = static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(sporepedia_type_lookup_00556140(descriptor, key_one)));
  {
    // 0064272c  CMP  ECX,dword ptr [ESI + 0x8]
    // 0064272f  JNC  0x0064273f
    //
    // The capacity test, UNSIGNED, and strict: the in-place arm is taken only
    // when cursor < capacity. The word at +0x08 is only ever compared, never
    // stored through, so it is a bound and not a pointer -- reading it as a
    // value and comparing it as a pointer would be the same bug at the other
    // end.
    Word* cursor = load_pointer(vector, kVectorCursorDisplacement);
    if (cursor >= load_pointer(vector, kVectorCapacityDisplacement)) {
      // 0064273f  LEA  EAX,[ESP + 0x8]
      // 00642743  PUSH EAX
      // 00642744  PUSH ECX
      // 00642745  MOV  ECX,ESI
      // 00642747  CALL  0x004558a0
      //
      // The slow arm, and the address handed over is the ADDRESS of the value
      // slot, not the value. The receiver in ECX is the ARGUMENT object, not
      // this body's receiver, and the first stack word is the cursor exactly as
      // 0x00642722 loaded it -- the slow arm does not advance anything, so at
      // the moment of the call the vector's own cursor word still holds the
      // value the load above put in a register.
      sporepedia_vector_insert_004558a0(vector, cursor, &value);
    } else {
      // 00642731  LEA  EDX,[ECX + 0x4]
      // 00642734  MOV  dword ptr [ESI + 0x4],EDX
      //
      // The cursor is advanced by exactly one element of 4 bytes and the vector
      // is told, BEFORE the store is attempted.
      // BYTE arithmetic, deliberately not `cursor + kVectorElementStride`: the
      // listing's `LEA EDX,[ECX + 0x4]` adds FOUR BYTES to the address, while
      // `Word* + 4` would advance four ELEMENTS and land sixteen bytes on. The
      // model's own first draft made exactly that mistake and the model test
      // caught it on the first run, which is what the stride assertion is for.
      word_ref(vector, kVectorCursorDisplacement) = static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
      // 00642737  TEST ECX,ECX
      // 00642739  JZ    0x0064274c
      //
      // The null guard on the STORE ONLY. A null cursor still advances the
      // cursor word to +0x04 and the element is simply not written, which is a
      // live case the body explicitly handles rather than an impossible one.
      if (cursor != nullptr) {
        // 0064273b  MOV  dword ptr [ECX],EAX
        //
        // The element write, and the only store this body makes into memory
        // that is not the vector's cursor word.
        *cursor = value;
      }
      // 0064273d  JMP  0x0064274c
      //
      // Both arms converge on the next lookup. The model keeps that as the end
      // of the block rather than as a branch, because the two arms are the two
      // arms of one `if` in the source and the jump is how the compiler spelled
      // it.
    }
  }

  // 0064274c  PUSH  0xad56080c
  // 00642751  PUSH  EDI
  // 00642752  CALL  0x00556140
  const Word key_two = 0xad56080cu;
  // 00642757  MOV  ECX,[ESI + 0x4]
  // 0064275a  ADD  ESP,0x8
  // 0064275d  MOV  dword ptr [ESP+0x10],EAX
  //
  // Lookup two, and the first one whose result lands in the caller's argument
  // word rather than in the frame; see the frame walk above. The cursor is
  // RE-READ from the vector here, not carried across the call -- which is what
  // makes the slow arm's effect on the cursor visible to the next append.
  value = static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(sporepedia_type_lookup_00556140(descriptor, key_two)));
  {
    // 00642761  CMP  ECX,dword ptr [ESI + 0x8]
    // 00642764  JNC  0x00642774
    Word* cursor = load_pointer(vector, kVectorCursorDisplacement);
    if (cursor >= load_pointer(vector, kVectorCapacityDisplacement)) {
      // 00642774  LEA  EAX,[ESP + 0x10]
      // 00642778  PUSH EAX
      // 00642779  PUSH ECX
      // 0064277a  MOV  ECX,ESI
      // 0064277c  CALL  0x004558a0
      sporepedia_vector_insert_004558a0(vector, cursor, &value);
    } else {
      // 00642766  LEA  EDX,[ECX + 0x4]
      // 00642769  MOV  dword ptr [ESI + 0x4],EDX
      // 0064276c  TEST ECX,ECX
      // 0064276e  JZ    0x00642781
      // 00642770  MOV  dword ptr [ECX],EAX
      // 00642772  JMP  0x00642781
      // BYTE arithmetic, deliberately not `cursor + kVectorElementStride`: the
      // listing's `LEA EDX,[ECX + 0x4]` adds FOUR BYTES to the address, while
      // `Word* + 4` would advance four ELEMENTS and land sixteen bytes on. The
      // model's own first draft made exactly that mistake and the model test
      // caught it on the first run, which is what the stride assertion is for.
      word_ref(vector, kVectorCursorDisplacement) = static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
      if (cursor != nullptr) {
        *cursor = value;
      }
    }
  }

  // 00642781  PUSH  0xf71fa311
  // 00642786  PUSH  EDI
  // 00642787  CALL  0x00556140
  const Word key_three = 0xf71fa311u;
  // 0064278c  MOV  ECX,[ESI + 0x4]
  // 0064278f  ADD  ESP,0x8
  // 00642792  MOV  dword ptr [ESP+0x10],EAX
  value = static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(sporepedia_type_lookup_00556140(descriptor, key_three)));
  {
    // 00642796  CMP  ECX,dword ptr [ESI + 0x8]
    // 00642799  JNC  0x006427a9
    Word* cursor = load_pointer(vector, kVectorCursorDisplacement);
    if (cursor >= load_pointer(vector, kVectorCapacityDisplacement)) {
      // 006427a9  LEA  EAX,[ESP + 0x10]
      // 006427ad  PUSH EAX
      // 006427ae  PUSH ECX
      // 006427af  MOV  ECX,ESI
      // 006427b1  CALL  0x004558a0
      sporepedia_vector_insert_004558a0(vector, cursor, &value);
    } else {
      // 0064279b  LEA  EDX,[ECX + 0x4]
      // 0064279e  MOV  dword ptr [ESI + 0x4],EDX
      // 006427a1  TEST ECX,ECX
      // 006427a3  JZ    0x006427b6
      // 006427a5  MOV  dword ptr [ECX],EAX
      // 006427a7  JMP  0x006427b6
      // BYTE arithmetic, deliberately not `cursor + kVectorElementStride`: the
      // listing's `LEA EDX,[ECX + 0x4]` adds FOUR BYTES to the address, while
      // `Word* + 4` would advance four ELEMENTS and land sixteen bytes on. The
      // model's own first draft made exactly that mistake and the model test
      // caught it on the first run, which is what the stride assertion is for.
      word_ref(vector, kVectorCursorDisplacement) = static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
      if (cursor != nullptr) {
        *cursor = value;
      }
    }
  }

  // 006427b6  PUSH  0xbeb528cb
  // 006427bb  PUSH  EDI
  // 006427bc  CALL  0x00556140
  const Word key_four = 0xbeb528cbu;
  // 006427c1  MOV  ECX,[ESI + 0x4]
  // 006427c4  ADD  ESP,0x8
  // 006427c7  MOV  dword ptr [ESP+0x10],EAX
  value = static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(sporepedia_type_lookup_00556140(descriptor, key_four)));
  {
    // 006427cb  CMP  ECX,dword ptr [ESI + 0x8]
    // 006427ce  JNC  0x006427de
    Word* cursor = load_pointer(vector, kVectorCursorDisplacement);
    if (cursor >= load_pointer(vector, kVectorCapacityDisplacement)) {
      // 006427de  LEA  EAX,[ESP + 0x10]
      // 006427e2  PUSH EAX
      // 006427e3  PUSH ECX
      // 006427e4  MOV  ECX,ESI
      // 006427e6  CALL  0x004558a0
      sporepedia_vector_insert_004558a0(vector, cursor, &value);
    } else {
      // 006427d0  LEA  EDX,[ECX + 0x4]
      // 006427d3  MOV  dword ptr [ESI + 0x4],EDX
      // 006427d6  TEST ECX,ECX
      // 006427d8  JZ    0x006427eb
      // 006427da  MOV  dword ptr [ECX],EAX
      // 006427dc  JMP  0x006427eb
      // BYTE arithmetic, deliberately not `cursor + kVectorElementStride`: the
      // listing's `LEA EDX,[ECX + 0x4]` adds FOUR BYTES to the address, while
      // `Word* + 4` would advance four ELEMENTS and land sixteen bytes on. The
      // model's own first draft made exactly that mistake and the model test
      // caught it on the first run, which is what the stride assertion is for.
      word_ref(vector, kVectorCursorDisplacement) = static_cast<Word>(
          reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
      if (cursor != nullptr) {
        *cursor = value;
      }
    }
  }

  // 006427eb  PUSH  0x2db6dad3
  // 006427f0  PUSH  EDI
  // 006427f1  CALL  0x00556140
  const Word key_five = 0x2db6dad3u;
  // 006427f6  MOV  ECX,[ESI + 0x4]
  // 006427f9  ADD  ESP,0x8
  // 006427fc  MOV  dword ptr [ESP+0x10],EAX
  value = static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(sporepedia_type_lookup_00556140(descriptor, key_five)));
  {
    // 00642800  CMP  ECX,dword ptr [ESI + 0x8]
    // 00642803  JNC  0x00642819
    //
    // The fifth capacity test. Its two arms do not converge on a sixth append:
    // the in-place arm RETURNS and the grow arm falls into the shared tail, so
    // this block is the only one whose two arms are two different exits. That is
    // why the model returns from inside it rather than falling out of the
    // function, and why the model's `true` is written twice below.
    Word* cursor = load_pointer(vector, kVectorCursorDisplacement);
    if (cursor >= load_pointer(vector, kVectorCapacityDisplacement)) {
      // 00642819  LEA  EAX,[ESP + 0x10]
      // 0064281d  PUSH EAX
      // 0064281e  PUSH ECX
      // 0064281f  MOV  ECX,ESI
      // 00642821  CALL  0x004558a0
      sporepedia_vector_insert_004558a0(vector, cursor, &value);
    } else {
      // 00642805  LEA  EDX,[ECX + 0x4]
      // 00642808  MOV  dword ptr [ESI + 0x4],EDX
      //
      // The fifth append advances the cursor exactly as the other four do, and
      // this line was MISSING from the model's first draft: the model test
      // caught it on the first run, because the arena held five results while
      // the cursor stopped on the fifth. It is written here, in the same byte
      // arithmetic as the other four, and before the null test.
      word_ref(vector, kVectorCursorDisplacement) =
          static_cast<Word>(reinterpret_cast<std::uintptr_t>(cursor) + kVectorElementStride);
      // 0064280b  TEST ECX,ECX
      //
      // 0064280d  JZ    0x00642826
      //
      // The fifth null guard jumps to the SHARED true tail rather than to a
      // sixth append, so a null cursor on the last append leaves the vector's
      // cursor advanced and skips the store, and still reports true.
      if (cursor != nullptr) {
        // 0064280f  POP  EDI
        // 00642810  MOV  dword ptr [ECX],EAX
        //
        // The store, with the first of the three epilogue pops hoisted into the
        // fast arm so that the machine can put the result byte in AL one
        // instruction sooner. The pop is not part of the store; the model
        // restores the saved registers conceptually and asserts nothing about
        // the frame, because nothing in the machine's observable behaviour
        // depends on where the pops sit relative to the store.
        *cursor = value;
      }
      // 00642812  MOV  AL,0x1
      // 00642814  POP  ESI
      // 00642815  POP  ECX
      // 00642816  RET  0x4
      //
      // The in-place exit: true. AL is written as a BYTE, so the upper three
      // bytes of EAX are the leftovers of whatever the last store or compare
      // produced, and the caller must not read them.
      return true;
    }
  }
  // 00642826  POP  EDI
  // 00642827  MOV  AL,0x1
  // 00642829  POP  ESI
  // 0064282a  POP  ECX
  // 0064282b  RET  0x4
  //
  // The shared true tail, reached from 0x0064280d and from the fifth append's
  // grow arm. So the body has exactly two exit values and three exits: false
  // only from 0x0064282e, and true from 0x00642816 and 0x0064282b.
  return true;
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00642700
