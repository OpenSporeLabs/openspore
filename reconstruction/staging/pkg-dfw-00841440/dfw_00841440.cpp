// PKG-DFW-00841440 -- model of SporeApp.exe 0x00841440
// (ArgScript::FormatParser::CreateDefinitionSafe), 11 instructions,
// body 0x00841440..0x00841464 inclusive (37 bytes), two basic blocks.
//
// The listing this models, re-read from the live bridge and corroborated by raw
// bytes at 0x00841440:
//
//   00841440  8b 54 24 08        MOV EDX,dword ptr [ESP + 0x8]
//   00841444  85 d2              TEST EDX,EDX
//   00841446  74 0f              JZ 0x00841457
//   00841448  8d 42 fc           LEA EAX,[EDX + -0x4]
//   0084144b  89 41 30           MOV dword ptr [ECX + 0x30],EAX
//   0084144e  89 54 24 08        MOV dword ptr [ESP + 0x8],EDX
//   00841452  e9 29 b3 ff ff     JMP 0x0083c780
//   00841457  33 c0              XOR EAX,EAX
//   00841459  89 41 30           MOV dword ptr [ECX + 0x30],EAX
//   0084145c  89 54 24 08        MOV dword ptr [ESP + 0x8],EDX
//   00841460  e9 1b b3 ff ff     JMP 0x0083c780
//
// and the shared tail it jumps to, 0x0083c780, 5 instructions, 15 bytes:
//
//   0083c780  8b 44 24 04        MOV EAX,dword ptr [ESP + 0x4]
//   0083c784  8b 54 24 08        MOV EDX,dword ptr [ESP + 0x8]
//   0083c788  89 41 04           MOV dword ptr [ECX + 0x4],EAX
//   0083c78b  89 51 0c           MOV dword ptr [ECX + 0xc],EDX
//   0083c78e  c2 08 00           RET 0x8
//
// Structure, and nothing below claims more than it can show:
//
//   * ECX is the receiver and is never written. The body stores only through
//     ECX + 0x30 and reads only the incoming stack words.
//   * Two ordinary stack arguments, entry [ESP+0x4] and entry [ESP+0x8]. The
//     body has no prologue, no push, no pop and no stack adjustment, so entry
//     ESP is still ESP at both JMPs and the tail reads the very slots the caller
//     filled.
//   * Both exits are JMP to the same tail. The epilogue that pops the two
//     argument words is the tail's RET 0x8; 0x00841440 contains no RET of its
//     own, so this is a tail call and the model calls the tail rather than
//     returning a value of its own. The model does not claim to emit the JMP:
//     it performs an ordinary call to a thiscall callee with the same two
//     callee-cleaned arguments, which is the same observable contract.
//   * EAX is written on both paths and is dead on both. The tail's first
//     instruction reloads EAX from the first stack word, so the word a caller
//     observes is the first stack word, never the biased word and never the
//     zero this body produces on the null path.
//
// The second stack word is the one the body acts on, and no semantic meaning is
// attached to it here. The body reads the word, biases it, stores the bias, and
// passes the word on. The SDK prototype names that parameter argumentsLine, the
// exported decompilation calls it pName, and record unresolved_questions records
// the disagreement; the header states the whole of that. The model keys on the
// machine fact, the SECOND ordinary stack word.

#include "dfw_00841440_types.hpp"

namespace openspore::reconstruction::pkg_dfw_00841440 {

bool PKG_DFW_00841440_THISCALL dfw_00841440_CreateDefinitionSafe(
    OpaqueFormatParser* receiver, char* pName, OpaqueLine* argumentsLine) {
  // 0x00841440  MOV EDX,dword ptr [ESP + 0x8]
  //
  // The one load in the body, of the SECOND ordinary stack word. EDX holds it
  // for the rest of the body; the body never writes EDX again, and no other
  // instruction in the body reads any stack word.
  const MachineWord second_word = static_cast<MachineWord>(
      reinterpret_cast<std::uintptr_t>(argumentsLine));

  // 0x00841440..0x00841460 -- the content of the frame slot at [ESP+0x8] as
  // the machine sees it. The body makes no stack adjustment of any kind, so
  // this local stands for the caller's own second argument slot: the machine
  // reads it at 0x00841440, rewrites it at 0x0084144e / 0x0084145c, and the
  // tail at 0x0083c784 reads that same slot again. Modelling the slot as a
  // value is what makes the two rewrites below observable instead of lost: what
  // the tail is handed is the slot's content, not the parameter.
  MachineWord frame_slot_08 = second_word;

  // The receiver is addressed only through machine displacement, and only at
  // 0x30, which is the single receiver displacement the complete listing names
  // and the single one the machine-derived receiver record enumerates
  // (register ECX, offsets [48], bounds_only true).
  unsigned char *const base = reinterpret_cast<unsigned char *>(receiver);

  // 0x00841444  TEST EDX,EDX
  // 0x00841446  JZ 0x00841457
  //
  // One conditional branch, taken when the second stack word is zero. The
  // target 0x00841457 is inside the body span, so both arms below are part of
  // this function and the tail is reached from exactly one of them per call.
  // Nothing else in the body branches, and nothing in the body changes the
  // first stack word -- so the first argument cannot affect which arm runs.
  if (second_word != 0u) {
    // 0x00841448  LEA EAX,[EDX + -0x4]
    //
    // An address computation on the word, one dword below it. The bias is the
    // whole content of this arm; no record for this target says what the
    // resulting address denotes, and this package does not guess.
    const MachineWord biased_word = second_word - 0x4u;

    // 0x0084144b  MOV dword ptr [ECX + 0x30],EAX
    //
    // The body's one definite receiver store on this path, the biased word at
    // displacement 0x30. The body reads no receiver word at all, so whatever
    // the object held there before is discarded.
    store_word(base, kReceiverWord_30, biased_word);

    // 0x0084144e  MOV dword ptr [ESP + 0x8],EDX
    //
    // EDX has not been modified since 0x00841440, so this store rewrites the
    // slot with the value the slot already holds. It is reproduced because it
    // is an observable store in the listing, not because it changes anything.
    frame_slot_08 = second_word;

    // 0x00841452  JMP 0x0083c780
    //
    // Control leaves here with ECX, the first stack word and the second stack
    // word all unchanged from entry, and the EAX the LEA produced is about to
    // be overwritten by the tail's first instruction.
  } else {
    // 0x00841457  XOR EAX,EAX
    //
    // The zero is produced in EAX, not read from anywhere: the arm is reached
    // only when the second stack word is already zero, so the two agree.

    // 0x00841459  MOV dword ptr [ECX + 0x30],EAX
    //
    // The same displacement, a zero word this time. So the body always writes
    // displacement 0x30 on every call, and never reads it.
    store_word(base, kReceiverWord_30, 0u);

    // 0x0084145c  MOV dword ptr [ESP + 0x8],EDX
    //
    // The same value-preserving rewrite as 0x0084144e: EDX is zero here and so
    // is the slot.
    frame_slot_08 = second_word;

    // 0x00841460  JMP 0x0083c780
  }

  // 0x00841452 / 0x00841460  JMP 0x0083c780
  //
  // The single transfer out of the body, reached once per call from exactly one
  // of the two arms above. 0x0083c780 reads [ESP+0x4] into EAX and [ESP+0x8]
  // into EDX, stores them at receiver displacements 0x4 and 0xc, and pops both
  // argument words with RET 0x8. The receiver reaches it still in ECX.
  //
  // The second argument handed over is the CONTENT OF THE SLOT, not the
  // parameter: that is what the tail's [ESP+0x8] load reads, and it is what
  // makes the two stores at 0x0084144e / 0x0084145c part of the model instead
  // of dead code. The first argument is the parameter itself, because the body
  // performs no store to [ESP+0x4] -- the listing has no such instruction.
  //
  // The tail's return value is returned verbatim. EAX is not this body's to
  // report: on the non-null arm it holds second_word - 0x4 and on the null arm
  // it holds zero, and 0x0083c780 overwrites both with the first stack word.
  return dfw_00841440_shared_tail_0083c780(
      receiver, pName,
      reinterpret_cast<OpaqueLine *>(static_cast<std::uintptr_t>(frame_slot_08)));
}

}  // namespace openspore::reconstruction::pkg_dfw_00841440
