// PKG-W2-00E7D2C0 -- VA 0x00e7d2c0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The body: the 73-byte basic block at 0x00e7d2b7..0x00e7d2fe, which contains
// the target byte 0x00e7d2c0 in the moffs32 operand of its fifth instruction.
// bounded_block_00e7d2c0.hpp carries the full transcription, the evidence each
// line is tied to, the machine record transcribed field for field, and the list
// of what is NOT claimed: no class, no vtable identity, no receiver type, no
// field, no member, no object size, no calling convention, and no instruction
// outside this one block.
//
// WHAT THIS BODY IS, IN ONE PARAGRAPH.
//
// It takes the value the absolute word at 0x016b3c04 holds, takes the 32-bit
// word 0x5190 bytes into whatever that value points at, adds 0x10 to it, and
// hands five words to the shared tail at 0x00e7d348: three addresses of its own
// stack frame, that adjusted word, and the immediate 0x9ef61113. On the way it
// overwrites nine consecutive dwords of its own frame with the register it was
// given -- and all three of the frame addresses it just pushed point into those
// nine dwords.
//
// The frame displacements below are written the way the machine spells them:
// relative to the ESP that existed at that instruction, with the count of PUSHes
// already executed carried next to them instead of folded into the constant.
// Folding is where this block would go wrong, because the three LEA
// displacements (0x1c, 0x2c, 0x3c) are not three frame slots -- at the moment
// each is read ESP has already moved by 0, 4 and 8 bytes respectively, so they
// are F+0x1c, F+0x28 and F+0x34, and the nine stores at 0x24..0x44 are
// F+0x1c..F+0x3f. The model test checks that spread independently.

#include "bounded_block_00e7d2c0.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_w2_00e7d2c0 {
namespace {

// The block's own frame arithmetic, in bytes from the frame window's base.
//
// `pushes` is the number of PUSH instructions already executed at the instant
// the displacement beside it is read, and kReturnAddressBytes is the width of
// one pushed dword. A PUSH moves ESP DOWN by that width, so a displacement read
// `pushes` words into the block names a frame slot that much LOWER than the
// literal: frame_offset = displacement - pushes * 4. The subtraction is spelled
// out rather than folded into the constants above, because the folded form is a
// different program -- it is the mistake this whole package is about.
inline std::size_t slot_offset(int pushes, std::size_t displacement) {
  return displacement - static_cast<std::size_t>(pushes) * kReturnAddressBytes;
}

// Loads and stores go through memcpy on purpose: the frame displacements are
// not multiples of four from an aligned object, so a typed access would be
// undefined behaviour, and the machine is unaligned-tolerant. memcpy keeps the
// width claim (four bytes) and drops the alignment claim.
inline Word get_word(const void* address) {
  Word value = 0;
  std::memcpy(&value, address, sizeof(value));
  return value;
}

inline void put_word(void* address, Word value) {
  std::memcpy(address, &value, sizeof(value));
}

// A frame address, as the 32-bit value the machine's PUSH would put on the
// stack. It is an address and nothing more: no object is named, no pointer is
// dereferenced through it here, and the test is what checks where it lands.
inline Word frame_address(const StackWindow* window, std::size_t offset) {
  return static_cast<Word>(
      reinterpret_cast<std::uintptr_t>(window->byte + offset));
}

}  // namespace

// Placed first among the definitions that carry the target's 8-hex VA, and the
// only one that carries it: the validator binds a source span to 0x00e7d2c0 by
// the VA token in the function name and takes the first such definition.
BlockOutcome reconstruct_00e7d2c0(StackWindow* window, const void* root, Word stored_word) {
  BlockOutcome outcome{};

  // 0x00e7d2b7  LEA EAX,[ESP + 0x1c]   no PUSH has run yet, so this is F+0x1c
  // 0x00e7d2bb  PUSH EAX
  const std::size_t first_offset = slot_offset(kPushesAtFirstLea, 0x1c);

  // 0x00e7d2c1  LEA ECX,[ESP + 0x2c]   read with one PUSH done, so this is
  //                                        F-4+0x2c = F+0x28
  // 0x00e7d2c5  PUSH ECX
  const std::size_t second_offset = slot_offset(kPushesAtSecondLea, 0x2c);

  // 0x00e7d2c6 .. 0x00e7d2e6  nine `MOV dword ptr [ESP + 0x24 + 4k],ESI`, read
  // with two PUSHes done, so they cover F+0x1c .. F+0x3c inclusive: nine
  // consecutive dwords, thirty-six bytes, and the value stored is the register
  // the block was handed. The block never writes that register itself, so it is
  // a parameter and not a constant.
  for (int index = 0; index < kZeroedWordCount; ++index) {
    put_word(window->byte + slot_offset(kPushesAtStores,
                                          0x24 + kReturnAddressBytes *
                                                      static_cast<std::size_t>(index)),
               stored_word);
  }

  // 0x00e7d2ea  MOV ECX,dword ptr [EAX + 0x5190]   EAX holds the value the
  // absolute word at 0x016b3c04 held, so this is a load 0x5190 bytes into the
  // object that value names. What lives there is not known and is not named: a
  // four-byte read is claimed and no field is.
  const Word owner_word = get_word(static_cast<const Byte*>(root) + 0x5190u);

  // 0x00e7d2f0  LEA EDX,[ESP + 0x3c]   read with two PUSHes done, so this is
  //                                        F-8+0x3c = F+0x34
  // 0x00e7d2f4  PUSH EDX
  const std::size_t third_offset = slot_offset(kPushesAtThirdLea, 0x3c);

  // 0x00e7d2f5  ADD ECX,0x10   an adjustment of the loaded VALUE, not a memory
  // displacement, and it is reported as one distinction in the metadata
  // sidecar: the validator reads every `+ 0x..` in this span as a declared
  // displacement, and this one is arithmetic on a word.
  // 0x00e7d2f8  PUSH ECX
  // 0x00e7d2f9  PUSH 0x9ef61113   this block's selector; the sibling arm at
  //                              0x00e7d300 pushes 0xac7161b5 instead
  // 0x00e7d2fe  JMP 0x00e7d348      the shared tail, which pushes none of its
  //                              own before `CALL 0x00e394f0` and then
  //                              `ADD ESP,0x14` pops the five words back off
  outcome.tail.first = frame_address(window, first_offset);
  outcome.tail.second = frame_address(window, second_offset);
  outcome.tail.third = frame_address(window, third_offset);
  outcome.tail.fourth = owner_word + 0x10u;
  outcome.tail.fifth = kTailSelector;

  // Read the nine words BACK rather than echoing the parameter into the result,
  // so that what this function reports is what it left in memory. A model that
  // reported the parameter would pass the same tests while writing the wrong
  // nine dwords, and that is the whole class of mistake this read-back exists to
  // make impossible.
  for (int index = 0; index < kZeroedWordCount; ++index) {
    outcome.zeroed[index] = get_word(window->byte + slot_offset(kPushesAtStores,
                                                                 0x24 + kReturnAddressBytes *
                                                                         static_cast<std::size_t>(index)));
  }
  return outcome;
}

}  // namespace openspore::reconstruction::pkg_w2_00e7d2c0
