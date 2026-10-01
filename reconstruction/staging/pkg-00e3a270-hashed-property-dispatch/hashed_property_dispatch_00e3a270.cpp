// PKG-00E3A270-HASHED-PROPERTY-DISPATCH -- VA 0x00e3a270
// FUN_00e3a270 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22): a hashed-property
// dispatcher over twenty-seven 32-bit selector ids.
//
// THE COMPLETE BODY: 172 instructions, 0x00e3a270..0x00e3a56a inclusive, 763
// bytes. The listing was read back from the committed Ghidra program for this
// package and is reproduced here instruction for instruction, at the same
// addresses and with the same lengths, so nothing below rests on a re-parse.
// The six bytes after 0x00e3a56a are INT3 padding, not part of the body.
//
// WHAT THE BODY IS. It is handed a 32-bit selector and a pointer to a property
// record, matches the selector against twenty-seven hashed ids through a SIGNED
// binary search tree, and on a match writes words read out of the record's
// value block into nineteen receiver displacements. Ten distinct arms exist:
// seven of them only store, and three of them additionally hand the record to
// one helper at 0x00e39420 together with the constant 3 and a computed receiver
// address, which the helper fills with three dwords. Six arms write a value
// unconditionally, three write a "primary" receiver word only while it is still
// zero, and five of the arms first write one of five consecutive tag immediates
// into the receiver word at +0x32c -- but four of those only if that word still
// holds -1. Ten selectors reach the arm that stores nothing but three block
// words, nine reach one of the three calling arms, and every selector matching
// no case returns having touched nothing at all.
//
// THE DISPATCH IS SIGNED, and that is the most fragile thing in the body. All
// seven ordering branches are JG -- 0x0F 8F at 0x00e3a279, 0x00e3a28a,
// 0x00e3a297, 0x00e3a3a8, 0x00e3a3b9 and 0x00e3a4c3, and 0x7F in its short form
// at 0x00e3a33c -- and fifteen of the twenty-seven selector values have the high
// bit set, so they are negative when read signed. A C++ `>` on a
// std::uint32_t is UNSIGNED, and the two readings agree only where both operands
// share the sign bit. The root pivot 0xf278934a is itself negative, so the
// fifteen negative selectors compare against it identically either way and a
// wrong reconstruction routes them correctly by luck; the twelve POSITIVE
// selectors do not, and unsigned they fall BELOW the root into the low half,
// whose seven leaf tests are all negative values. So twelve arms become
// unreachable and those twelve selectors write nothing and call nothing. The
// model therefore spells every ordering compare signed_greater(), and the
// model test drives all twenty-seven selectors specifically to separate the two
// readings.
//
// The arms are NOT a chain and the tree shape is reproduced: the root pivot is
// 0xf278934a, and the two halves are themselves pivoted (0xaaf6aaac, 0x9f792b4c
// on the low side; 0x3e2a3040, 0x279c4e55, 0x6cd9ec7b and 0xd832b059 on the
// high side). Several arms are reached from more than one place and the model
// shares them exactly as the bytes do: 0x00e3a2c0 is the target of four
// different JZ instructions plus two fall-throughs, 0x00e3a3e2 of three,
// 0x00e3a517 of nine JZ plus one fall-through, 0x00e3a546 of three, and
// 0x00e3a4e4 of two JZ plus one fall-through. That is why the arms are lambdas:
// a duplicated body would be a reconstruction that can disagree with itself,
// which is the opposite of what this package is for.
//
// THE ORDER OF THE TWO STORES IN THE THREE LAZY ARMS IS LOAD-BEARING and is
// easy to get backwards. In each of them the machine compares the primary
// receiver word against zero at 0x00e3a2f8 / 0x00e3a42c / 0x00e3a47b, but the
// JNZ that acts on that comparison is three or four instructions LATER, at
// 0x00e3a30f / 0x00e3a443 / 0x00e3a492, AFTER the secondary word has already
// been stored. So the secondary store is UNCONDITIONAL and the primary store is
// the conditional one. The MOVs in between do not touch the flags, so the flag
// tested at 0x00e3a30f is the one 0x00e3a2f8 set. The model takes that
// comparison into a named bool for exactly that reason: in C++ an `if` written
// from the obvious reading would be attached to the wrong read.
//
// VIRTUAL DISPATCH: none, and none declared. None of the 172 instructions is a
// register- or memory-operand transfer, the xref export records 0 vtable
// references for this function, and the body never reads the receiver's +0x00,
// so it names no slot boundary and no member there. No slot table is modelled
// anywhere in this package.
//
// GLOBALS: the body's own listing names no data-segment address. The five
// immediates 0x1654c00..0x1654c05 fall inside the validator's crude
// 0x1300000..0x02000000 data range even though they are immediate operands and
// not addresses -- they are runtime-populated tag cells, which is why their
// contents read as zero in the image. The values are reproduced because
// reproducing them is the body; what they denote is not claimed.

#include "hashed_property_dispatch_00e3a270.hpp"

namespace openspore::reconstruction::pkg_00e3a270_dispatch {

extern "C" Word PKG_00E3A270_THISCALL hashed_property_dispatch_00e3a270(
    Simulator* receiver, Word selector, const PropertyRecord* record) {
  // 0x00e3a270  8B 44 24 04        MOV EAX,[ESP+0x4]
  //
  // The selector, read as a VALUE out of the one ordinary stack word at
  // entry_ESP+0x4. The body never writes it and never sets up a frame: the 172
  // instructions contain no PUSH other than the three argument pushes before the
  // calls, no POP, no SUB ESP and no MOV EBP,ESP. So [ESP+0x4] and [ESP+0x8] are
  // the only two stack words the body can name, and the machine parse reports
  // local_extent 0 with esp_unresolved false.
  const Word key = selector;

  // The receiver, addressed through ECX on every one of its nineteen accesses.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // == the ten arms, each one a block of the machine listing ================
  //
  // They are declared before the tree because five of them are targets of more
  // than one branch. The machine has exactly ten blocks and this model has
  // exactly ten.

  // -- 0x00e3a2c0 .. 0x00e3a2e2 : store the block's first word, then copy -----
  // Reached by selector 0xaaf6aaac (0x00e3a290), 0xdca976d0 (0x00e3a38f), and by
  // the two fall-throughs at 0x00e3a2ba and 0x00e3a3dc -- four ways in.
  const auto arm_copy_into_2c0 = [&]() {
    // 0x00e3a2c0  MOV EAX,[ESP+0x8]              the record, entry_ESP+0x8
    // 0x00e3a2c4  MOV EDX,[EAX+0xc]              record[+0x0c] -- a POINTER
    // 0x00e3a2c7  MOV EDX,[EDX+0x8]              q[+0x08]
    // 0x00e3a2ca  MOV [ECX+0x324],EDX
    // 0x00e3a2d0  ADD ECX,0x2c0                  the destination is COMPUTED
    // 0x00e3a2d6  PUSH ECX
    // 0x00e3a2d7  PUSH 0x3
    // 0x00e3a2d9  PUSH EAX                       EAX still holds the record
    // 0x00e3a2da  CALL 0x00e39420
    // 0x00e3a2df  ADD ESP,0xc                    the callee is cdecl
    // 0x00e3a2e2  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x324) = *word_at(block, 0x8);
    // `ADD ECX,0x2c0` is arithmetic on the receiver pointer, not a store: the
    // listing shows no memory operand under +0x2c0, so this body never writes
    // the twelve bytes there and the callee is what fills them.
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x2c0));
  };

  // -- 0x00e3a4e4 .. 0x00e3a506 : the same shape, two different displacements -
  // Reached by selector 0x8133fb2e (0x00e3a2a4), 0x2cfa39dd (0x00e3a457) and
  // 0x6a9f2620 (the fall-through at 0x00e3a4de).
  const auto arm_copy_into_2b4 = [&]() {
    // 0x00e3a4e4  MOV EAX,[ESP+0x8]
    // 0x00e3a4e8  MOV EDX,[EAX+0xc]
    // 0x00e3a4eb  MOV EDX,[EDX+0x8]
    // 0x00e3a4ee  MOV [ECX+0x31c],EDX
    // 0x00e3a4f4  ADD ECX,0x2b4
    // 0x00e3a4fa  PUSH ECX
    // 0x00e3a4fb  PUSH 0x3
    // 0x00e3a4fd  PUSH EAX
    // 0x00e3a4fe  CALL 0x00e39420
    // 0x00e3a503  ADD ESP,0xc
    // 0x00e3a506  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x31c) = *word_at(block, 0x8);
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x2b4));
  };

  // -- 0x00e3a546 .. 0x00e3a565/e3a568 : the same shape again, and the arm that -
  // -- owns the body's final RET, so the default return is its fall-through ----
  // Reached by selector 0xf967827c (0x00e3a3c6), 0x13df9c1c (0x00e3a3d1) and
  // 0x7115ede5 (0x00e3a50e). The selector that falls through at 0x00e3a515
  // (0x7bceaa86) goes to the NEXT block instead, which is the kind of
  // off-by-one-block a dropped fall-through in a reconstruction produces.
  const auto arm_copy_into_29c = [&]() {
    // 0x00e3a546  MOV EAX,[ESP+0x8]
    // 0x00e3a54a  MOV EDX,[EAX+0xc]
    // 0x00e3a54d  MOV EDX,[EDX+0x8]
    // 0x00e3a550  MOV [ECX+0x30c],EDX
    // 0x00e3a556  ADD ECX,0x29c
    // 0x00e3a55c  PUSH ECX
    // 0x00e3a55d  PUSH 0x3
    // 0x00e3a55f  PUSH EAX
    // 0x00e3a560  CALL 0x00e39420
    // 0x00e3a565  ADD ESP,0xc
    // 0x00e3a568  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x30c) = *word_at(block, 0x8);
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x29c));
  };

  // -- 0x00e3a3e2 .. 0x00e3a416 : four unconditional stores, NON-source order --
  // Reached by selector 0xf278934a (0x00e3a27f), 0x25ca9233 (the fall-through at
  // 0x00e3a3dc) and 0x5c51063f (0x00e3a4cc).
  const auto arm_write_four = [&]() {
    // 0x00e3a3e2  MOV EAX,[ESP+0x8]
    // 0x00e3a3e6  MOV EDX,[EAX+0xc]
    // 0x00e3a3e9  MOV EDX,[EDX+0x8]
    // 0x00e3a3ec  MOV [ECX+0x314],EDX          q[+0x08] -> +0x314
    // 0x00e3a3f2  MOV EDX,[EAX+0xc]
    // 0x00e3a3f5  MOV EDX,[EDX+0xc]            q[+0x0c] -> +0x2ac
    // 0x00e3a3f8  MOV [ECX+0x2ac],EDX
    // 0x00e3a3fe  MOV EDX,[EAX+0xc]
    // 0x00e3a401  MOV EDX,[EDX+0x10]           q[+0x10] -> +0x2a8
    // 0x00e3a404  MOV [ECX+0x2a8],EDX
    // 0x00e3a40a  MOV EAX,[EAX+0xc]            EAX leaves holding the BLOCK
    // 0x00e3a40d  MOV EDX,[EAX+0x14]           q[+0x14] -> +0x2b0
    // 0x00e3a410  MOV [ECX+0x2b0],EDX
    // 0x00e3a416  RET 0x8
    //
    // Note the second and third destinations are SWAPPED with respect to the
    // source order: q[+0x0c] lands at +0x2ac and q[+0x10] lands at +0x2a8, so
    // writing them in ascending source order is a refutation, not a style. There
    // is NO null test on the record on this path, unlike arm_write_three.
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x314) = *word_at(block, 0x8);
    *word_at(self, 0x2ac) = *word_at(block, 0xc);
    *word_at(self, 0x2a8) = *word_at(block, 0x10);
    *word_at(self, 0x2b0) = *word_at(block, 0x14);
    return address_word(block);  // 0x00e3a40a left the block pointer in EAX
  };

  // -- 0x00e3a517 .. 0x00e3a543 : three stores, and the body's ONLY null test --
  // Reached by TEN selectors: 0x980e43f2 (0x00e3a2af), 0xa0973374 (0x00e3a323),
  // 0xa6cb4c9f (0x00e3a32e), 0xd832b059 (0x00e3a33e), 0xcdb3696f (0x00e3a350),
  // 0xd536c91d (0x00e3a35b), 0xe0bc9d45 (0x00e3a39a), 0x6cd9ec7b (0x00e3a4c5),
  // 0x5fcf28d0 (0x00e3a4d7) and 0x7bceaa86 (the fall-through at 0x00e3a515).
  const auto arm_write_three = [&]() {
    // 0x00e3a517  MOV EAX,[ESP+0x8]
    // 0x00e3a51b  TEST EAX,EAX
    // 0x00e3a51d  JZ 0x00e3a568                  a null record returns having
    //                                            written NOTHING -- no tag either
    // 0x00e3a51f  MOV EDX,[EAX+0xc]
    // 0x00e3a522  MOV EDX,[EDX+0xc]              q[+0x0c] -> +0x2d0
    // 0x00e3a525  MOV [ECX+0x2d0],EDX
    // 0x00e3a52b  MOV EDX,[EAX+0xc]
    // 0x00e3a52e  MOV EDX,[EDX+0x10]             q[+0x10] -> +0x2cc
    // 0x00e3a531  MOV [ECX+0x2cc],EDX
    // 0x00e3a537  MOV EAX,[EAX+0xc]
    // 0x00e3a53a  MOV EDX,[EAX+0x14]             q[+0x14] -> +0x2d4
    // 0x00e3a53d  MOV [ECX+0x2d4],EDX
    // 0x00e3a543  RET 0x8
    //
    // In ASCENDING source order here, unlike arm_write_four, and the
    // destinations are +0x2d0, +0x2cc, +0x2d4. So the two arms disagree about
    // order and neither is the other's typo. This is the ONLY arm of the ten
    // with a null test.
    if (record == nullptr) {
      return 0u;  // 0x00e3a51d jumps to the shared RET with EAX still zero
    }
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x2d0) = *word_at(block, 0xc);
    *word_at(self, 0x2cc) = *word_at(block, 0x10);
    *word_at(self, 0x2d4) = *word_at(block, 0x14);
    return address_word(block);
  };

  // -- 0x00e3a4a1 .. 0x00e3a4bb : the one UNGUARDED tag write ------------------
  // Reached by selector 0x3e2a3040 (0x00e3a3ae).
  const auto arm_tag_init = [&]() {
    // 0x00e3a4a1  MOV EAX,[ESP+0x8]
    // 0x00e3a4a5  MOV [ECX+0x32c],0x1654c00      NO CMP against -1 first: the
    //                                            only tag store in the body
    //                                            that is not conditional
    // 0x00e3a4af  MOV EDX,[EAX+0xc]
    // 0x00e3a4b2  MOV EAX,[EDX+0x8]
    // 0x00e3a4b5  MOV [ECX+0x308],EAX
    // 0x00e3a4bb  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x32c) = kTag_1654c00;
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x308) = loaded;
    return loaded;
  };

  // -- 0x00e3a364 .. 0x00e3a387 : guarded tag, then one store ------------------
  // Reached by selector 0xade76cce (0x00e3a349).
  const auto arm_tag_then_310 = [&]() {
    // 0x00e3a364  CMP [ECX+0x32c],-0x1
    // 0x00e3a36b  JNZ 0x00e3a377
    // 0x00e3a36d  MOV [ECX+0x32c],0x1654c01
    // 0x00e3a377  MOV EAX,[ESP+0x8]
    // 0x00e3a37b  MOV EDX,[EAX+0xc]
    // 0x00e3a37e  MOV EAX,[EDX+0x8]
    // 0x00e3a381  MOV [ECX+0x310],EAX
    // 0x00e3a387  RET 0x8
    //
    // The guard is a "write only out of the unset state" test, and it is a
    // comparison against -1 (`CMP DWORD PTR [ECX+0x32c],0xffffffff`), NOT a
    // truth test: a receiver whose +0x32c already holds 0 is LEFT ALONE here,
    // because 0 is not -1. The test drives exactly that case, and the inverse
    // mistake -- treating the guard as "if zero" -- is refuted by driving -1.
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = kTag_1654c01;
    }
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x310) = loaded;
    return loaded;
  };

  // -- 0x00e3a2e5 .. 0x00e3a31b : guarded tag, then the lazy 324/328 pair ------
  // Reached by selector 0x9f792b4c (0x00e3a29d).
  const auto arm_lazy_324 = [&]() {
    // 0x00e3a2e5  CMP [ECX+0x32c],-0x1
    // 0x00e3a2ec  JNZ 0x00e3a2f8
    // 0x00e3a2ee  MOV [ECX+0x32c],0x1654c05
    // 0x00e3a2f8  CMP [ECX+0x324],0x0            the flag acted on FOUR
    // 0x00e3a2ff  MOV EAX,[ESP+0x8]                instructions later
    // 0x00e3a303  MOV EDX,[EAX+0xc]
    // 0x00e3a306  MOV EAX,[EDX+0x8]
    // 0x00e3a309  MOV [ECX+0x328],EAX            UNCONDITIONAL: +0x328 always
    // 0x00e3a30f  JNZ 0x00e3a568
    // 0x00e3a315  MOV [ECX+0x324],EAX            +0x324 only when it was zero
    // 0x00e3a31b  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = kTag_1654c05;
    }
    const bool primary_already_set = *word_at(self, 0x324) != 0u;
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x328) = loaded;
    if (primary_already_set) {
      return loaded;  // 0x00e3a30f leaves EAX exactly as 0x00e3a306 set it
    }
    *word_at(self, 0x324) = loaded;
    return loaded;
  };

  // -- 0x00e3a419 .. 0x00e3a44f : the same lazy pair on +0x314/+0x318 ----------
  // Reached by selector 0x279c4e55 (0x00e3a3bf).
  const auto arm_lazy_314 = [&]() {
    // 0x00e3a419  CMP [ECX+0x32c],-0x1
    // 0x00e3a420  JNZ 0x00e3a42c
    // 0x00e3a422  MOV [ECX+0x32c],0x1654c02
    // 0x00e3a42c  CMP [ECX+0x314],0x0
    // 0x00e3a433  MOV EAX,[ESP+0x8]
    // 0x00e3a437  MOV EDX,[EAX+0xc]
    // 0x00e3a43a  MOV EAX,[EDX+0x8]
    // 0x00e3a43d  MOV [ECX+0x318],EAX
    // 0x00e3a443  JNZ 0x00e3a568
    // 0x00e3a449  MOV [ECX+0x314],EAX
    // 0x00e3a44f  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = kTag_1654c02;
    }
    const bool primary_already_set = *word_at(self, 0x314) != 0u;
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x318) = loaded;
    if (primary_already_set) {
      return loaded;
    }
    *word_at(self, 0x314) = loaded;
    return loaded;
  };

  // -- 0x00e3a468 .. 0x00e3a49e : the same lazy pair on +0x31c/+0x320 ----------
  // Reached by selector 0x3b38f92a (the fall-through at 0x00e3a462). Note that
  // the PRIMARY here, +0x31c, is the one arm_copy_into_2b4 writes
  // unconditionally -- the two arms are an eager setter and a lazy default of
  // the same word. LABELLLED INFERRED: the byte listing does not prove the
  // pairing, and nothing else here does either.
  const auto arm_lazy_31c = [&]() {
    // 0x00e3a468  CMP [ECX+0x32c],-0x1
    // 0x00e3a46f  JNZ 0x00e3a47b
    // 0x00e3a471  MOV [ECX+0x32c],0x1654c04
    // 0x00e3a47b  CMP [ECX+0x31c],0x0
    // 0x00e3a482  MOV EAX,[ESP+0x8]
    // 0x00e3a486  MOV EDX,[EAX+0xc]
    // 0x00e3a489  MOV EAX,[EDX+0x8]
    // 0x00e3a48c  MOV [ECX+0x320],EAX
    // 0x00e3a492  JNZ 0x00e3a568
    // 0x00e3a498  MOV [ECX+0x31c],EAX
    // 0x00e3a49e  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = kTag_1654c04;
    }
    const bool primary_already_set = *word_at(self, 0x31c) != 0u;
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x320) = loaded;
    if (primary_already_set) {
      return loaded;
    }
    *word_at(self, 0x31c) = loaded;
    return loaded;
  };

  // == the dispatch: a signed binary search tree, in machine order =============
  //
  // `signed_greater`, not `>`. The root pivot 0xf278934a is a negative value and
  // a `>` on a std::uint32_t is UNSIGNED, which would send the twelve positive
  // selectors BELOW it instead of above, into a half whose leaf tests are all
  // negative. The three positive pivots further down (0x3e2a3040, 0x279c4e55,
  // 0x6cd9ec7b) have the same shape.

  if (signed_greater(key, kSelector_f278934a)) {  // 0x00e3a274 / 0x00e3a279 JG
    if (signed_greater(key, kSelector_3e2a3040)) {  // 0x00e3a3a3 / e3a3a8 JG
      if (signed_greater(key, kSelector_6cd9ec7b)) {  // e3a4be / e3a4c3 (7F JG)
        if (key == kSelector_7115ede5) {  // 0x00e3a509 / 0x00e3a50e
          return arm_copy_into_29c();
        }
        if (key == kSelector_7bceaa86) {  // 0x00e3a510 / 0x00e3a515
          return arm_write_three();
        }
        return key;  // 0x00e3a515 JNZ to the shared RET: nothing written at all
      }
      if (key == kSelector_6cd9ec7b) {  // 0x00e3a4c5
        return arm_write_three();
      }
      if (key == kSelector_5c51063f) {  // e3a4c7 / e3a4cc, a BACKWARD jump
        return arm_write_four();
      }
      if (key == kSelector_5fcf28d0) {  // 0x00e3a4d2 / 0x00e3a4d7
        return arm_write_three();
      }
      if (key == kSelector_6a9f2620) {  // 0x00e3a4d9, then the fall-through
        return arm_copy_into_2b4();
      }
      return key;  // 0x00e3a4de JNZ
    }
    if (key == kSelector_3e2a3040) {  // 0x00e3a3ae
      return arm_tag_init();
    }
    if (signed_greater(key, kSelector_279c4e55)) {  // e3a3b4 CMP / e3a3b9 JG
      if (key == kSelector_2cfa39dd) {  // 0x00e3a452 / 0x00e3a457
        return arm_copy_into_2b4();
      }
      if (key == kSelector_3b38f92a) {  // 0x00e3a45d, then the fall-through
        return arm_lazy_31c();
      }
      return key;  // 0x00e3a462 JNZ
    }
    if (key == kSelector_279c4e55) {  // 0x00e3a3bf
      return arm_lazy_314();
    }
    if (key == kSelector_f967827c) {  // 0x00e3a3c1 / 0x00e3a3c6
      return arm_copy_into_29c();
    }
    if (key == kSelector_13df9c1c) {  // 0x00e3a3cc / 0x00e3a3d1
      return arm_copy_into_29c();
    }
    if (key == kSelector_25ca9233) {  // 0x00e3a3d7, then the fall-through
      return arm_write_four();
    }
    return key;  // 0x00e3a3dc JNZ
  }
  if (key == kSelector_f278934a) {  // 0x00e3a27f
    return arm_write_four();
  }
  if (signed_greater(key, kSelector_aaf6aaac)) {  // e3a285 / e3a28a JG
    if (signed_greater(key, kSelector_d832b059)) {  // e3a337 / e3a33c (7F JG)
      if (key == kSelector_dca976d0) {  // e3a38a / e3a38f, a BACKWARD jump
        return arm_copy_into_2c0();
      }
      if (key == kSelector_e0bc9d45) {  // 0x00e3a395 / 0x00e3a39a
        return arm_write_three();
      }
      return key;  // 0x00e3a3a0
    }
    if (key == kSelector_d832b059) {  // 0x00e3a33e
      return arm_write_three();
    }
    if (key == kSelector_ade76cce) {  // 0x00e3a344 / 0x00e3a349
      return arm_tag_then_310();
    }
    if (key == kSelector_cdb3696f) {  // 0x00e3a34b / 0x00e3a350
      return arm_write_three();
    }
    if (key == kSelector_d536c91d) {  // 0x00e3a356 / 0x00e3a35b
      return arm_write_three();
    }
    return key;  // 0x00e3a361
  }
  if (key == kSelector_aaf6aaac) {  // 0x00e3a290
    return arm_copy_into_2c0();
  }
  if (signed_greater(key, kSelector_9f792b4c)) {  // e3a292 / e3a297 JG
    if (key == kSelector_a0973374) {  // 0x00e3a31e / 0x00e3a323
      return arm_write_three();
    }
    if (key == kSelector_a6cb4c9f) {  // 0x00e3a329 / 0x00e3a32e
      return arm_write_three();
    }
    return key;  // 0x00e3a334
  }
  if (key == kSelector_9f792b4c) {  // 0x00e3a29d
    return arm_lazy_324();
  }
  if (key == kSelector_8133fb2e) {  // 0x00e3a29f / 0x00e3a2a4
    return arm_copy_into_2b4();
  }
  if (key == kSelector_980e43f2) {  // 0x00e3a2aa / 0x00e3a2af
    return arm_write_three();
  }
  if (key == kSelector_99f0d1da) {  // 0x00e3a2b5, then the fall-through
    return arm_copy_into_2c0();
  }
  return key;  // 0x00e3a2ba JNZ to the shared RET at 0x00e3a568: EAX is still the
               // selector, because no arm has run
}

}  // namespace openspore::reconstruction::pkg_00e3a270_dispatch
