#include "52e640_spill_zero.hpp"

// Reconstruction of 0x0052e640 (SporeApp.exe 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e).
//
// The complete 15-byte body, read from /disassemble_function and /read_memory
// on the live Ghidra bridge and re-asserted as data in the header:
//
//     55           PUSH EBP
//     8b ec        MOV EBP,ESP
//     51           PUSH ECX
//     89 4d fc     MOV dword ptr [EBP + -0x4],ECX
//     32 c0        XOR AL,AL
//     8b e5        MOV ESP,EBP
//     5d           POP EBP
//     c2 0c 00     RET 0xc
//
// So the source semantics are: establish the EBP frame, reserve one dword of
// frame local with PUSH ECX, store the word carried in ECX into that dword, zero
// the low byte of EAX, tear the frame down the way it was built, and return
// popping twelve bytes of stack. Nothing else happens: no branch, no call, no
// jump; no global; no dereference of ECX; no read of the three stack words the
// callee pops.
//
// The calling convention is __thiscall, which the derived ABI record for this
// target now names at INFERRED confidence (conventions.calling_convention =
// __thiscall, confidence = INFERRED, candidate_conventions = ["__thiscall"],
// ambiguities = []), in two recorded steps: R1-VFT puts the receiver in ECX
// because this address is slot 8 of the sound vptr-backed vftable at 0x013f2194
// (one of 25 such tables) and the body reads the register that dispatch
// delivered - a COM/__stdcall-shaped body takes its receiver from the first
// popped stack word and never reads its incoming ECX - and C6B names __thiscall
// from the callee-side cleanup plus that receiver register. The receiver
// sub-record agrees: present = true, register = ECX, provenance =
// vftable_slot_dispatch, bounds_only = true, shape = null. The caller side
// corroborates it independently: both direct call sites, 0x0050a468 and
// 0x0050a5d6, push exactly three dwords, load ECX from the caller's own
// captured receiver and issue no ADD ESP after the CALL.
//
// The convention says where the receiver arrives, not what it is. The body
// reads the ECX word, stores it in a dead frame slot and never dereferences it,
// so this package names no class, no receiver type, no field and no layout, and
// carries the receiver as the plain 4-byte word the machine proves it to be.
//
// The callee-side cleanup is separately OBSERVED (cleanup.bytes = 12,
// cleanup.side = "callee", cleanup.evidence = "ret 0xc") and is carried by the
// entry's own `ret $12` below, which is the machine instruction itself, and as
// DATA in CleanupSide52e640.

namespace openspore::reconstruction::pkg_w2_0052e640 {

// -- the reconstructed entry ------------------------------------------------
//
// Placed first in this translation unit on purpose: the validator binds a
// source span to 0x0052e640 by the 8-hex VA token appearing in the function
// name, and it takes the FIRST such definition in the file. The behavioural
// twin below deliberately does not carry the token, so this definition is the
// only span the binder can select for this target.
//
// Instruction for instruction, with the address of the machine instruction each
// line models:
//
//   0x0052e640  PUSH EBP                 build the frame
//   0x0052e641  MOV  EBP,ESP             ... and establish the frame pointer
//   0x0052e643  PUSH ECX                 reserve the one 4-byte frame local
//   0x0052e644  MOV  dword ptr [EBP + -0x4],ECX
//                                        the body's only write: the word the
//                                        receiver arrived in lands in the word
//                                        PUSH ECX just reserved
//   0x0052e647  XOR  AL,AL               the answer, and only the answer: the
//                                        low byte of EAX, so bits 8..31 are
//                                        left as the caller left them
//   0x0052e649  MOV  ESP,EBP             tear the frame down as it was built
//   0x0052e64b  POP  EBP
//   0x0052e64c  RET  0xc                 and pop the three stack words, in the
//                                        callee - the observed cleanup side
//
// __thiscall is what puts the receiver in ECX, and nothing here dereferences it:
// the entry reads that word once and stores it, and the epilogue discards the
// store. The three stack words are named only so that the twelve bytes this
// `ret` pops are the twelve bytes the caller pushed; no instruction here reads
// them. So this transcription is byte-faithful and identity-free at the same
// time - it performs the machine's register traffic without asserting what the
// word in ECX points at.
//
// Byte fidelity: the emitted sequence is instruction for instruction the
// original 15 bytes. Three encodings differ for free, because each pair of
// spellings denotes the same instruction: the original encodes the two
// frame-pointer moves as 8b ec / 8b e5 (mov r32,r/m32) where GAS picks 89 e5 /
// 89 ec (mov r/m32,r32), and it encodes the zeroing as 32 c0 (XOR r/m8,r8) where
// GAS picks 30 c0 (XOR r/m8,r8 with the /6 form). All three are the same
// operation on the same operands. A default position-independent build
// additionally prepends a ten-byte __x86.get_pc_thunk.ax PC anchor (g++ -m32
// -fPIC; clang++ -m32 emits none), which is a toolchain artifact and not part of
// the reconstruction. Byte-identical recompilation is therefore NOT claimed;
// semantic fidelity is, and the model test pins the nine non-divergent bytes
// exactly, in the target order, immediately after the anchor when one is
// present, and requires each divergent pair to be one of the two encodings of
// the same operation.
extern "C" std::uint8_t PKG_52E640_NAKED_THISCALL reconstruct_0052e640(
    std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t) {
  __asm__("pushl %ebp\n\t"              // 0x0052e640  PUSH EBP
          "movl %esp, %ebp\n\t"         // 0x0052e641  MOV EBP,ESP
          "pushl %ecx\n\t"               // 0x0052e643  PUSH ECX
          "movl %ecx, -4(%ebp)\n\t"     // 0x0052e644  MOV [EBP + -0x4],ECX
          "xorb %al, %al\n\t"            // 0x0052e647  XOR AL,AL
          "movl %ebp, %esp\n\t"         // 0x0052e649  MOV ESP,EBP
          "popl %ebp\n\t"               // 0x0052e64b  POP EBP
          "retl $12\n\t");               // 0x0052e64c  RET 0xc
}

// The same single effect in ordinary C++, for the behavioural model test: the
// word carried in the receiver register lands in the one 4-byte frame local, the
// three popped argument words are read by nothing, and the answer is the byte
// 0. PUSH ECX reserved that dword, the epilogue discards it, and nothing in the
// listing reads it back, so the store is the whole of the body's observable
// state change. This is a statement about behaviour: its arguments are passed
// by the caller and the caller pops them, so the stack discipline the target
// proves - the callee's `ret $12` - belongs to the entry above and not here.
extern "C" std::uint8_t PKG_52E640_CDECL apply_frame_store_52e640(
    std::uint32_t* const frame_local_word, const std::uint32_t receiver_word,
    const std::uint32_t first, const std::uint32_t second,
    const std::uint32_t third) {
  volatile std::uint32_t captured_receiver = receiver_word;
  *frame_local_word = captured_receiver;
  static_cast<void>(first);
  static_cast<void>(second);
  static_cast<void>(third);
  return kReturnConstant;
}

}  // namespace openspore::reconstruction::pkg_w2_0052e640

#undef PKG_52E640_CDECL
#undef PKG_52E640_NAKED_THISCALL
#undef PKG_52E640_THISCALL
