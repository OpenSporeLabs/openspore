// PKG-DFW-01053E00 -- VA 0x01053e00
// Simulator, cluster sim-core-systems
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 65 instructions, entry 0x01053e00, last instruction
// 0x01053ed3 (`RET 0x8`). Every line of the model below is annotated with the
// instruction it comes from, in listing order, and the model asserts nothing the
// listing does not carry.
//
//   01053e00  SUB ESP,0x18
//   01053e03  PUSH ESI
//   01053e04  MOV ESI,dword ptr [ESP + 0x20]
//   01053e08  MOV ECX,dword ptr [ESI + 0x124]
//   01053e0e  TEST ECX,ECX
//   01053e10  JZ 0x01053e38
//   01053e12  MOV EAX,dword ptr [ECX]
//   01053e14  MOV EDX,dword ptr [EAX + 0x2c]
//   01053e17  CALL EDX
//   01053e19  TEST AL,AL
//   01053e1b  JZ 0x01053e38
//   01053e1d  MOV ECX,dword ptr [ESI + 0x124]
//   01053e23  TEST ECX,ECX
//   01053e25  JZ 0x01053e38
//   01053e27  MOV dword ptr [ESI + 0x124],0x0
//   01053e31  MOV EAX,dword ptr [ECX]
//   01053e33  MOV EDX,dword ptr [EAX + 0x4]
//   01053e36  CALL EDX
//   01053e38  CMP dword ptr [ESI + 0x124],0x0
//   01053e3f  JZ 0x01053ecd
//   01053e45  MOV ECX,dword ptr [ESI + 0x114]
//   01053e4b  TEST ECX,ECX
//   01053e4d  JZ 0x01053e72
//   01053e4f  MOV EAX,dword ptr [ECX]
//   01053e51  MOV EDX,dword ptr [EAX + 0xb8]
//   01053e57  PUSH 0x13f94d4
//   01053e5c  CALL EDX
//   01053e5e  TEST EAX,EAX
//   01053e60  JZ 0x01053e72
//   01053e62  MOV EDX,dword ptr [EAX]
//   01053e64  MOV EDX,dword ptr [EDX + 0x30]
//   01053e67  LEA ECX,dword ptr [ESP + 0x10]
//   01053e6b  PUSH ECX
//   01053e6c  MOV ECX,EAX
//   01053e6e  CALL EDX
//   01053e70  JMP 0x01053e7f
//   01053e72  MOV ECX,dword ptr [ESI + 0x114]
//   01053e78  MOV EAX,dword ptr [ECX]
//   01053e7a  MOV EDX,dword ptr [EAX + 0x2c]
//   01053e7d  CALL EDX
//   01053e7f  MOVSS XMM0,dword ptr [EAX]
//   01053e83  MOVSS dword ptr [ESP + 0x4],XMM0
//   01053e89  MOVSS XMM0,dword ptr [EAX + 0x4]
//   01053e8e  MOVSS dword ptr [ESP + 0x8],XMM0
//   01053e94  MOVSS XMM0,dword ptr [EAX + 0x8]
//   01053e99  MOV EAX,dword ptr [ESI + 0x124]
//   01053e9f  LEA ECX,dword ptr [EAX + 0x34]
//   01053ea2  MOVSS dword ptr [ESP + 0xc],XMM0
//   01053ea8  MOV EAX,dword ptr [ECX]
//   01053eaa  MOV EAX,dword ptr [EAX + 0x38]
//   01053ead  LEA EDX,dword ptr [ESP + 0x4]
//   01053eb1  PUSH EDX
//   01053eb2  CALL EAX
//   01053eb4  MOV ECX,dword ptr [ESP + 0x24]
//   01053eb8  PUSH ECX
//   01053eb9  MOV ECX,dword ptr [ESI + 0x124]
//   01053ebf  CALL 0x00cb5930
//   01053ec4  MOV AL,0x1
//   01053ec6  POP ESI
//   01053ec7  ADD ESP,0x18
//   01053eca  RET 0x8
//   01053ecd  XOR AL,AL
//   01053ecf  POP ESI
//   01053ed0  ADD ESP,0x18
//   01053ed3  RET 0x8
//
// ABI, machine-derived, and the two places the evidence does not settle it:
//
// * The two terminators are `RET 0x8`, so the callee owns eight bytes of stack.
//   Both stack words are plain dwords and neither is a hidden sret: the frame is
//   SUB ESP,0x18 and the body writes nothing through the address of either.
//   The reconstruction therefore declares the entry point `__attribute__((stdcall))`
//   with two dword parameters, which is the x86-32 shape that matches `RET 0x8`.
//   The knowledge record's `abi.calling_convention` is prose, not a token: it
//   says the receiver "is NOT in ECX but is the first callee-popped stack
//   argument", which is this same shape described in the record's own words. The
//   record's machine-derived `conventions` block abstains
//   (candidate_conventions ["__stdcall","__thiscall"], confidence UNKNOWN), and
//   this package does not claim to have resolved it.
// * Word 0 of the two is the receiver. At 0x01053e04, after SUB ESP,0x18 and
//   PUSH ESI, ESP is entry_ESP-0x1c and [ESP+0x20] is entry_ESP+0x4. Every later
//   read of the same word agrees: at 0x01053eb4, after the three callee-popped
//   pushes have been balanced by their callees, [ESP+0x24] is entry_ESP+0x8.
//   That arithmetic is the only reason this package calls word 1 the receiver and
//   not the other way round, and it is why the frame is balanced across the three
//   virtual calls: any of them leaving its pushed word behind would put
//   0x01053eb4's operand below the return address.
// * Word 1 is read. The record's `abi.stack_arguments[1].role` says it is "never
//   read by this body", and 0x01053eb4 is `MOV ECX,dword ptr [ESP + 0x24]`, which
//   is entry_ESP+0x8 on the arithmetic above, immediately pushed at 0x01053eb8
//   and passed to 0x00cb5930. The live decompilation agrees: it renders that call
//   as `FUN_00cb5930(unaff_retaddr)`, i.e. a value that came off the stack. The
//   record's "never read" and the machine's 0x01053eb4 are recorded as a
//   contradiction in the sidecar rather than reconciled here; the model reads it.
//
// The receiver is addressed only through machine displacements and no member is
// named, because no record for this target says which member any of them is.
// This body demonstrably performs field access -- six reads and one write
// through ESI, at displacements 0x114 and 0x124 -- so any earlier statement that
// it addresses no receiver field is refuted by the listing; see the sidecar.

#include "dfw_01053e00_types.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_dfw_01053e00 {
namespace {

// The listing's own dword read, written as a read rather than as a dereference
// so the model never depends on a type the machine does not give.
Word load_word(const void *address) {
  Word value = 0;
  std::memcpy(&value, address, sizeof value);
  return value;
}

// The listing's own dword write. The body has exactly one of them,
// 0x01053e27, and it stores zero.
void store_word(void *address, Word value) {
  std::memcpy(address, &value, sizeof value);
}

// The 12-byte frame buffer at [ESP+0x10] that 0x01053e67 forms and hands to the
// +0x30 slot at 0x01053e6b. The body never reads it back, so the model declares
// it and passes it and stops there.
using FrameBuffer = OpaqueSinglePrecisionTriple;

}  // namespace

extern "C" bool PKG_DFW_01053E00_STDCALL
dfw_FUN_01053e00(void *receiver, void *second_stack_word) {
  // 0x01053e00  SUB ESP,0x18
  // 0x01053e03  PUSH ESI
  // 0x01053e04  MOV ESI,dword ptr [ESP + 0x20]
  //
  // The receiver alias, and the only place the frame arithmetic is settled. ESP
  // is entry_ESP-0x1c here, so the operand names entry_ESP+0x4: the first of the
  // two callee-popped words the terminators clean.
  unsigned char *const base = static_cast<unsigned char *>(receiver);

  // 0x01053e08  MOV ECX,dword ptr [ESI + 0x124]
  //
  // The first of six reads of the receiver's word at displacement 0x124. It is
  // read as a pointer because the very next block loads through it
  // (0x01053e12) and dereferences the table word it points at; nothing in any
  // record says what the word points at, so the pointee is opaque and the
  // knowledge record's own name for the receiver's role is used
  // (OpaqueBeamTarget) without a claim about the object.
  OpaqueBeamTarget *target =
      reinterpret_cast<OpaqueBeamTarget *>(load_word(base + 0x124u));

  // 0x01053e0e  TEST ECX,ECX
  // 0x01053e10  JZ 0x01053e38
  //
  // The target 0x01053e38 is the gate, inside this body. A zero word skips the
  // whole block and arrives at the gate with 0x124 still zero.
  if (target != nullptr) {
    // 0x01053e12  MOV EAX,dword ptr [ECX]
    // 0x01053e14  MOV EDX,dword ptr [EAX + 0x2c]
    // 0x01053e17  CALL EDX
    //
    // The first of the six indirect transfers. It is a two-level table load --
    // the pointee's word at 0, then that word's slot at displacement 0x2c -- and
    // ECX still holds the object, so the callee receives it there. Nothing pushes
    // a stack word, which is why the model declares the slot with a single
    // parameter.
    //
    // 0x01053e19  TEST AL,AL
    // 0x01053e1b  JZ 0x01053e38
    //
    // The return is read as one byte. A zero byte skips to the gate with the
    // receiver's word at 0x124 untouched, which is the only way this body reaches
    // the position work with a non-zero word still in place.
    if (target->table_00->slot_2c(target)) {
      // 0x01053e1d  MOV ECX,dword ptr [ESI + 0x124]
      // 0x01053e23  TEST ECX,ECX
      // 0x01053e25  JZ 0x01053e38
      //
      // The word is re-read rather than reused, and the listing tests it again.
      // The call above can have written it, and if it did, the second test is
      // what catches that -- the model re-reads so the same thing is observable.
      target = reinterpret_cast<OpaqueBeamTarget *>(load_word(base + 0x124u));

      if (target != nullptr) {
        // 0x01053e27  MOV dword ptr [ESI + 0x124],0x0
        //
        // The body's one write, and it is ordered before the transfer below:
        // the receiver's word is zeroed while ECX still holds the old pointer,
        // so the callee at 0x01053e36 is reached through a receiver that no
        // longer names it. The order is the machine's and the model keeps it.
        store_word(base + 0x124u, 0x0u);

        // 0x01053e31  MOV EAX,dword ptr [ECX]
        // 0x01053e33  MOV EDX,dword ptr [EAX + 0x4]
        // 0x01053e36  CALL EDX
        //
        // The second indirect transfer, the same two-level shape one slot lower
        // at displacement 0x04, with the object in ECX and no stack word. Its
        // return is never read: the next write to EAX is the load inside the gate
        // compare at 0x01053e38, and both returns set AL explicitly.
        target->table_00->slot_04(target);
      }
    }
  }

  // 0x01053e38  CMP dword ptr [ESI + 0x124],0x0
  // 0x01053e3f  JZ 0x01053ecd
  //
  // The gate, and the second read of the same displacement in five
  // instructions. It is a fresh read, not the value the block above left in ECX,
  // so whatever 0x01053e36 did to the word decides the outcome.
  if (load_word(base + 0x124u) == 0x0u) {
    // 0x01053ecd  XOR AL,AL
    // 0x01053ecf  POP ESI
    // 0x01053ed0  ADD ESP,0x18
    // 0x01053ed3  RET 0x8
    //
    // The false exit. AL is zeroed explicitly, so the return word is false
    // regardless of what any callee left in EAX.
    return false;
  }

  // 0x01053e45  MOV ECX,dword ptr [ESI + 0x114]
  //
  // The receiver's other word, at displacement 0x114, read for the first time.
  OpaqueWordAt114 *const source =
      reinterpret_cast<OpaqueWordAt114 *>(load_word(base + 0x114u));

  // Where 0x01053e7f reads its three words from. EAX on both paths holds the
  // pointer one of the two transfers below returned.
  const OpaqueSinglePrecisionTriple *position = nullptr;

  // 0x01053e4b  TEST ECX,ECX
  // 0x01053e4d  JZ 0x01053e72
  if (source != nullptr) {
    // 0x01053e4f  MOV EAX,dword ptr [ECX]
    // 0x01053e51  MOV EDX,dword ptr [EAX + 0xb8]
    // 0x01053e57  PUSH 0x13f94d4
    // 0x01053e5c  CALL EDX
    //
    // The third indirect transfer. One stack word is pushed and the callee is
    // reached with it, and 0x13f94d4 is the only data-segment address in the
    // body. It is written as a literal here so the address is a claim in code and
    // not only in prose. The evidence pack's `globals` category names the same
    // address, and the eight words the bridge reads there are code-range
    // addresses; no record says what the table is, so the model forms the
    // address and asserts nothing about its contents.
    const Word *const keyed_table =
        reinterpret_cast<const Word *>(static_cast<std::uintptr_t>(0x13f94d4u));

    // 0x01053e5e  TEST EAX,EAX
    // 0x01053e60  JZ 0x01053e72
    OpaqueFoundAt_b8 *const found = source->table_00->slot_b8(source, keyed_table);
    if (found != nullptr) {
      // 0x01053e62  MOV EDX,dword ptr [EAX]
      // 0x01053e64  MOV EDX,dword ptr [EDX + 0x30]
      // 0x01053e67  LEA ECX,dword ptr [ESP + 0x10]
      // 0x01053e6b  PUSH ECX
      // 0x01053e6c  MOV ECX,EAX
      // 0x01053e6e  CALL EDX
      //
      // The fourth indirect transfer: the same two-level shape, slot at
      // displacement 0x30, with the object that the +0xb8 transfer returned in
      // ECX and the frame buffer at [ESP+0x10] pushed. The buffer is
      // uninitialised in the listing and the body never reads it back -- it
      // consumes the callee's EAX instead -- so the model passes it and does not
      // look at it, and the model test proves that by having the observer write
      // to it and checking the body still uses the returned pointer.
      FrameBuffer produced;
      position = found->table_00->slot_30(found, &produced);

      // 0x01053e70  JMP 0x01053e7f
      //
      // The jump lands on the instruction that follows the fallback block, so
      // the block at 0x01053e72..0x01053e7d is skipped on this path. That is
      // what the `else` below spells, and it is the only control-flow statement
      // in the model that a reader could mistake for a reordering: it is not
      // one, it is this jump.
    } else {
      // 0x01053e72  MOV ECX,dword ptr [ESI + 0x114]
      // 0x01053e78  MOV EAX,dword ptr [ECX]
      // 0x01053e7a  MOV EDX,dword ptr [EAX + 0x2c]
      // 0x01053e7d  CALL EDX
      //
      // The fallback, reached from 0x01053e60 with a non-zero word at 0x114. The
      // block re-reads the word it was reached for and dispatches the +0x2c slot
      // on it with no test of its own. The live decompilation shows the same
      // unconditional call.
      OpaqueWordAt114 *const reread =
          reinterpret_cast<OpaqueWordAt114 *>(load_word(base + 0x114u));
      position = reread->table_00->slot_2c(reread);
    }
  } else {
    // 0x01053e4d  JZ 0x01053e72 also reaches the fallback, and on that path the
    // word at 0x114 is the zero the test at 0x01053e4b just examined. The block
    // at 0x01053e72 re-reads it, tests nothing, and dereferences it at
    // 0x01053e78 -- so the original reads address 0 and faults there.
    //
    // The model reproduces the absence of the test rather than adding one, and
    // the read goes through the same load_word every other read in this body
    // goes through, so the fault is a property of the modelled machine and not
    // of a guard this package invented. Nothing in the model test enters this
    // path: entering it has the same consequence here that it has in the
    // original, and a test that could only observe a segmentation fault would
    // not be testing the reconstruction. The path is recorded in the sidecar's
    // unresolved_questions instead.
    OpaqueWordAt114 *const reread =
        reinterpret_cast<OpaqueWordAt114 *>(load_word(base + 0x114u));
    position = reread->table_00->slot_2c(reread);
  }

  // 0x01053e7f  MOVSS XMM0,dword ptr [EAX]
  // 0x01053e83  MOVSS dword ptr [ESP + 0x4],XMM0
  // 0x01053e89  MOVSS XMM0,dword ptr [EAX + 0x4]
  // 0x01053e8e  MOVSS dword ptr [ESP + 0x8],XMM0
  // 0x01053e94  MOVSS XMM0,dword ptr [EAX + 0x8]
  // 0x01053e9f  LEA ECX,dword ptr [EAX + 0x34]
  // 0x01053ea2  MOVSS dword ptr [ESP + 0xc],XMM0
  //
  // Three single-precision words are copied out of the returned pointer into the
  // frame at [ESP+0x4], [ESP+0x8] and [ESP+0xc] -- one contiguous twelve-byte
  // run, which is the argument the +0x38 transfer below is handed. The 0x01053e9f
  // LEA sits between the last load and its store in the listing, so the two
  // blocks are written in the order the listing has them.
  OpaqueSinglePrecisionTriple copied;
  copied.word_00 = position->word_00;
  copied.word_04 = position->word_04;
  copied.word_08 = position->word_08;

  // 0x01053e99  MOV EAX,dword ptr [ESI + 0x124]
  //
  // The receiver's word at 0x124, read for the third time and a third time
  // independently of what the gate compared. The gate is a load, not a kept
  // value, and so is this.
  OpaqueBeamTarget *const owned =
      reinterpret_cast<OpaqueBeamTarget *>(load_word(base + 0x124u));

  // 0x01053e9f  LEA ECX,dword ptr [EAX + 0x34]
  //
  // An address computation, not a read: the word at 0x34 of the owned target is
  // formed and not loaded.
  OpaqueWordAt34 *const emitter = reinterpret_cast<OpaqueWordAt34 *>(
      load_word(reinterpret_cast<const unsigned char *>(owned) + 0x34u));

  // 0x01053ea8  MOV EAX,dword ptr [ECX]
  // 0x01053eaa  MOV EAX,dword ptr [EAX + 0x38]
  //
  // The fifth indirect transfer's slot, at displacement 0x38 of the object just
  // dereferenced.
  //
  // 0x01053ead  LEA EDX,dword ptr [ESP + 0x4]
  // 0x01053eb1  PUSH EDX
  // 0x01053eb2  CALL EAX
  //
  // The fifth indirect transfer, with the object in ECX and the three copied
  // words pushed as the one stack word. Its return is never read.
  emitter->table_00->slot_38(emitter, &copied);

  // 0x01053eb4  MOV ECX,dword ptr [ESP + 0x24]
  //
  // The second callee-popped stack word, entry_ESP+0x8 on the frame arithmetic
  // settled at 0x01053e04 -- and this is the load that contradicts the record's
  // "never read by this body", noted at the head of this file.
  //
  // 0x01053eb8  PUSH ECX
  // 0x01053eb9  MOV ECX,dword ptr [ESI + 0x124]
  //
  // The receiver's word at 0x124, read for the fourth time, and the only
  // placement of ECX the body makes for a direct call.
  //
  // 0x01053ebf  CALL 0x00cb5930
  //
  // The body's one direct transfer, and the only address the xref export records
  // as an out-edge. The live decompilation of that callee is
  // `void __thiscall FUN_00cb5930(int param_1, undefined4 *param_2)`, which is
  // this call shape: ECX is the receiver, the pushed word is the one stack
  // argument. What the callee does with it is not modelled -- the model test
  // defines it as an observer -- but that callee's own listing reads three
  // consecutive words from that argument, which is recorded in the sidecar and
  // is not asserted here.
  dfw_commit_00cb5930(
      reinterpret_cast<OpaqueBeamTarget *>(load_word(base + 0x124u)),
      second_stack_word);

  // 0x01053ec4  MOV AL,0x1
  // 0x01053ec6  POP ESI
  // 0x01053ec7  ADD ESP,0x18
  // 0x01053eca  RET 0x8
  //
  // AL is set to one explicitly, so the return word is true regardless of what
  // any callee left behind. The frame teardown matches the prologue.
  return true;
}

}  // namespace openspore::reconstruction::pkg_dfw_01053e00
