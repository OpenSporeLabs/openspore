// PKG-SWARM-W2-00E3A400 -- VA 0x00e3a400
// FUN_00e3a270 (SPORE/SporeBin/SporeApp.exe, 3.1.0.22): a hashed-property
// dispatcher over twenty-seven 32-bit selector ids.
//
// THE COMPLETE BODY: 172 instructions, 0x00e3a270..0x00e3a56a inclusive, 763
// bytes. It was re-derived from the image bytes for this package and reproduces
// the committed Ghidra listing instruction for instruction, at the same
// addresses and with the same lengths, so nothing below rests on a re-parse.
// The worker's target address 0x00e3a400 is the second byte of the instruction
// at 0x00e3a40a, which is why the symbol here embeds the target VA and the
// body's entry is quoted without the 0x prefix: the machine listing contains
// only its branch targets, its call target and its immediates as 0x-prefixed
// literals, and the entry address is not one of them.
//
// WHAT THE BODY IS. It is handed a 32-bit selector and a pointer to a property
// record, matches the selector against twenty-seven hashed ids through a
// SIGNED binary search tree, and on a match writes words read out of the
// record's value block into nineteen receiver displacements. Ten distinct arms
// exist; seven of them just store, and three of them additionally hand the
// record to one helper at 0x00e39420 together with the constant 3 and a
// computed receiver address, which the helper fills with three dwords. Six arms
// write a value unconditionally, three write a "primary" receiver word only when
// it is still zero, and four of the arms first write one of six consecutive
// tag immediates into the receiver word at +0x32c, but only if that word still
// holds -1. Nine selectors reach an arm that stores nothing at all but the tag,
// and every selector that matches no case returns having touched nothing.
//
// THE DISPATCH IS SIGNED, and that is the most fragile thing in the body. All
// seven ordering branches are JG -- 0x0F 8F at e3a279, e3a28a, e3a297, e3a3a8,
// e3a3b9 and 0x7F at e3a33c, e3a4c3 -- and fifteen of the twenty-seven selector
// values have the high bit set, so they are negative when read signed. A C++ `>`
// on a std::uint32_t is UNSIGNED, and the two readings agree only where both
// operands share the sign bit. The root pivot 0xf278934a is negative, so the
// fifteen negative selectors compare against it identically either way and a
// wrong reconstruction routes them correctly by luck; the twelve POSITIVE
// selectors do not, and unsigned they fall below the root into the low half,
// whose seven leaf tests are all negative values, so twelve arms become
// unreachable and those twelve selectors write nothing and call nothing. The
// model therefore spells every ordering compare signed_greater(), and the
// model's own test drives all twenty-seven selectors specifically to separate
// the two readings.
//
// The arms are NOT a chain and the tree shape is reproduced: the root pivot is
// 0xf278934a, and the two halves are themselves pivoted (0xaaf6aaac, 0x9f792b4c
// on the low side; 0x3e2a3040, 0x279c4e55, 0x6cd9ec7b and 0xd832b059 on the
// high side). Several arms are reached from more than one place and the model
// shares them exactly as the bytes do: 0x00e3a2c0 is the target of four
// different JZ/JE instructions (e3a290, e3a38f, and the two fall-throughs at
// e3a2ba and e3a3dc), 0x00e3a3e2 of three (e3a27f, e3a3dc, e3a4cc), 0x00e3a517
// of nine, 0x00e3a546 of four, and 0x00e3a4e4 of three. That is why the arms are
// lambdas: a duplicated body would be a reconstruction that can disagree with
// itself, which is the opposite of what this package is for.
//
// THE ORDER OF THE TWO STORES IN THE THREE LAZY ARMS IS LOAD-BEARING and is
// easy to get backwards. In each of them the machine compares the primary
// receiver word against zero at e3a2f8 / e3a42c / e3a47b, but the JNZ that acts
// on that comparison is three or four instructions LATER, at e3a30f / e3a443 /
// e3a492, AFTER the secondary word has already been stored. So the secondary
// store is unconditional and the primary store is the conditional one. The MOVs
// in between do not touch the flags, so the flag tested at e3a30f is the one
// e3a2f8 set. The model takes the comparison into a named bool for exactly that
// reason: in C++ the `if` would otherwise be attached to the wrong read.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and no one of the
// 172 instructions is a register- or memory-operand transfer. The body never
// reads the receiver's +0x00 either, so it names no slot boundary and no member
// at +0x00, and no slot table is modelled anywhere in this package.
//
// GLOBALS: the body's own listing names no data-segment address, and the source
// span names none. The five immediates 0x1654c00..0x1654c05 fall inside the
// validator's crude 0x1300000..0x02000000 data range even though they are
// immediate operands and not addresses, which is what fixes the GLOBALS verdict
// at WARN; the values are reproduced because reproducing them is the body, and
// the discrepancy is recorded in the sidecar's known_blockers.

#include "sw2_00e3a400_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w2_00e3a400 {

extern "C" Word SW2_00E3A400_THISCALL re_00e3a400(
    Simulator* receiver, Word selector, const PropertyRecord* record) {
  // e3a270  8B 44 24 04        MOV EAX,[ESP+0x4]
  //
  // The selector, read as a VALUE out of the one ordinary stack word at
  // entry_ESP+0x4. The body never writes it, and no frame is ever set up: the
  // 172 instructions contain no PUSH other than the three argument pushes
  // before the calls, no POP, no SUB ESP and no MOV EBP,ESP, which is why the
  // machine parse reports local_extent 0 with esp_unresolved false and why
  // [ESP+0x4] and [ESP+0x8] are the only two stack words the body can name.
  const Word key = selector;

  // The receiver, addressed through ECX on every one of the seventeen accesses.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // == the ten arms, each one a block of the machine listing ================
  //
  // They are declared before the tree because six of them are targets of more
  // than one branch; the machine has exactly ten blocks and this model has
  // exactly ten.

  // -- e3a2c0 .. e3a2e2 : store the block's first word, then copy a triple ----
  // Reached by selector 0xaaf6aaac (e3a290), 0xdca976d0 (e3a38f), and by the
  // two fall-throughs at e3a2ba and e3a3dc, which is four ways in.
  const auto arm_copy_into_2c0 = [&]() {
    // e3a2c0  MOV EAX,[ESP+0x8]              the record, entry_ESP+0x8
    // e3a2c4  MOV EDX,[EAX+0xc]              record[+0x0c] -- a POINTER
    // e3a2c7  MOV EDX,[EDX+0x8]              q[+0x08] -- the second level
    // e3a2ca  MOV [ECX+0x324],EDX
    // e3a2d0  ADD ECX,0x2c0                  the destination is COMPUTED
    // e3a2d6  PUSH ECX
    // e3a2d7  PUSH 0x3
    // e3a2d9  PUSH EAX                       EAX still holds the record
    // e3a2da  CALL 0x00e39420
    // e3a2df  ADD ESP,0xc                    the callee is cdecl
    // e3a2e2  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x324) = *word_at(block, 0x8);
    // `ADD ECX,0x2c0` is arithmetic on the receiver pointer, not a store: the
    // listing shows no memory operand under +0x2c0, so this body never writes
    // the twelve bytes there and the callee is what fills them.
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x2c0));
  };

  // -- e3a4e4 .. e3a506 : the same shape, two different displacements -------
  // Reached by selector 0x8133fb2e (e3a2a4), 0x2cfa39dd (e3a457) and 0x6a9f2620
  // (the fall-through at e3a4de).
  const auto arm_copy_into_2b4 = [&]() {
    // e3a4e4  MOV EAX,[ESP+0x8]
    // e3a4e8  MOV EDX,[EAX+0xc]
    // e3a4eb  MOV EDX,[EDX+0x8]
    // e3a4ee  MOV [ECX+0x31c],EDX
    // e3a4f4  ADD ECX,0x2b4
    // e3a4fa  PUSH ECX
    // e3a4fb  PUSH 0x3
    // e3a4fd  PUSH EAX
    // e3a4fe  CALL 0x00e39420
    // e3a503  ADD ESP,0xc
    // e3a506  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x31c) = *word_at(block, 0x8);
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x2b4));
  };

  // -- e3a546 .. e3a565/e3a568 : the same shape again, and the arm that owns --
  // -- the body's final RET, so the default return is its fall-through --------
  // Reached by selector 0xf967827c (e3a3c6), 0x13df9c1c (e3a3d1) and 0x7115ede5
  // (e3a50e) -- three, and the selector that falls through at e3a515
  // (0x7bceaa86) goes to the NEXT block instead, which is the kind of
  // off-by-one-block a fall-through dropped in a reconstruction produces.
  const auto arm_copy_into_29c = [&]() {
    // e3a546  MOV EAX,[ESP+0x8]
    // e3a54a  MOV EDX,[EAX+0xc]
    // e3a54d  MOV EDX,[EDX+0x8]
    // e3a550  MOV [ECX+0x30c],EDX
    // e3a556  ADD ECX,0x29c
    // e3a55c  PUSH ECX
    // e3a55d  PUSH 0x3
    // e3a55f  PUSH EAX
    // e3a560  CALL 0x00e39420
    // e3a565  ADD ESP,0xc
    // e3a568  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x30c) = *word_at(block, 0x8);
    return simulator_copy_block3_00e39420(record, 0x3, word_at(self, 0x29c));
  };

  // -- e3a3e2 .. e3a416 : four unconditional stores, in a NON-source order ---
  // Reached by selector 0xf278934a (e3a27f), 0x25ca9233 (the fall-through at
  // e3a3dc) and 0x5c51063f (e3a4cc).
  const auto arm_write_four = [&]() {
    // e3a3e2  MOV EAX,[ESP+0x8]
    // e3a3e6  MOV EDX,[EAX+0xc]
    // e3a3e9  MOV EDX,[EDX+0x8]
    // e3a3ec  MOV [ECX+0x314],EDX          q[+0x08] -> +0x314
    // e3a3f2  MOV EDX,[EAX+0xc]
    // e3a3f5  MOV EDX,[EDX+0xc]            q[+0x0c] -> +0x2ac
    // e3a3f8  MOV [ECX+0x2ac],EDX
    // e3a3fe  MOV EDX,[EAX+0xc]
    // e3a401  MOV EDX,[EDX+0x10]           q[+0x10] -> +0x2a8
    // e3a404  MOV [ECX+0x2a8],EDX
    // e3a40a  MOV EAX,[EAX+0xc]            <-- the worker's target VA, 0x00e3a400,
    // e3a40d  MOV EDX,[EAX+0x14]              is the SECOND BYTE of this
    // e3a410  MOV [ECX+0x2b0],EDX           q[+0x14] -> +0x2b0
    // e3a416  RET 0x8
    //
    // Note the second and third destinations are swapped with respect to the
    // source order: q[+0x0c] lands at +0x2ac and q[+0x10] lands at +0x2a8, so
    // writing them in ascending source order is a refutation, not a style.
    // There is NO null test on the record on this path, unlike arm_write_three.
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x314) = *word_at(block, 0x8);
    *word_at(self, 0x2ac) = *word_at(block, 0xc);
    *word_at(self, 0x2a8) = *word_at(block, 0x10);
    *word_at(self, 0x2b0) = *word_at(block, 0x14);
    return address_word(block);  // e3a40a left the block pointer in EAX
  };

  // -- e3a517 .. e3a543 : three stores, and the body's ONLY null test ---------
  // Reached by ten selectors: 0x980e43f2 (e3a2af), 0xa0973374 (e3a323),
  // 0xa6cb4c9f (e3a32e), 0xd832b059 (e3a33e), 0xcdb3696f (e3a350), 0xd536c91d
  // (e3a35b), 0xe0bc9d45 (e3a39a), 0x6cd9ec7b (e3a4c5), 0x5fcf28d0 (e3a4d7) and
  // 0x7bceaa86 (the fall-through at e3a515).
  const auto arm_write_three = [&]() {
    // e3a517  MOV EAX,[ESP+0x8]
    // e3a51b  TEST EAX,EAX
    // e3a51d  JZ 0x00e3a568                  a null record returns having
    //                                         written NOTHING -- no tag either
    // e3a51f  MOV EDX,[EAX+0xc]
    // e3a522  MOV EDX,[EDX+0xc]              q[+0x0c] -> +0x2d0
    // e3a525  MOV [ECX+0x2d0],EDX
    // e3a52b  MOV EDX,[EAX+0xc]
    // e3a52e  MOV EDX,[EDX+0x10]             q[+0x10] -> +0x2cc
    // e3a531  MOV [ECX+0x2cc],EDX
    // e3a537  MOV EAX,[EAX+0xc]
    // e3a53a  MOV EDX,[EAX+0x14]             q[+0x14] -> +0x2d4
    // e3a53d  MOV [ECX+0x2d4],EDX
    // e3a543  RET 0x8
    //
    // In ASCENDING source order here, unlike arm_write_four, and the
    // destinations are +0x2d0, +0x2cc, +0x2d4 -- so the two arms disagree about
    // order and neither of them is the other one's typo.
    if (record == nullptr) {
      return 0u;  // e3a51d jumps to the shared RET with EAX still zero
    }
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x2d0) = *word_at(block, 0xc);
    *word_at(self, 0x2cc) = *word_at(block, 0x10);
    *word_at(self, 0x2d4) = *word_at(block, 0x14);
    return address_word(block);
  };

  // -- e3a4a1 .. e3a4bb : the one UNGUARDED tag write ------------------------
  // Reached by selector 0x3e2a3040 (e3a3ae).
  const auto arm_tag_init = [&]() {
    // e3a4a1  MOV EAX,[ESP+0x8]
    // e3a4a5  MOV [ECX+0x32c],0x1654c00      NO CMP against -1 first: this is
    //                                         the only tag store in the body
    //                                         that is not conditional
    // e3a4af  MOV EDX,[EAX+0xc]
    // e3a4b2  MOV EAX,[EDX+0x8]
    // e3a4b5  MOV [ECX+0x308],EAX
    // e3a4bb  RET 0x8
    const void* const block = pointer_at(record, 0x0c);
    *word_at(self, 0x32c) = 0x1654c00u;
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x308) = loaded;
    return loaded;
  };

  // -- e3a364 .. e3a387 : guarded tag, then one store -------------------------
  // Reached by selector 0xade76cce (e3a349).
  const auto arm_tag_then_310 = [&]() {
    // e3a364  CMP [ECX+0x32c],-0x1
    // e3a36b  JNZ e3a377
    // e3a36d  MOV [ECX+0x32c],0x1654c01
    // e3a377  MOV EAX,[ESP+0x8]
    // e3a37b  MOV EDX,[EAX+0xc]
    // e3a37e  MOV EAX,[EDX+0x8]
    // e3a381  MOV [ECX+0x310],EAX
    // e3a387  RET 0x8
    //
    // The guard is a "write only out of the unset state" test, and it is a
    // comparison against -1 (`CMP DWORD PTR [ECX+0x32c],0xffffffff`), not a
    // truth test: a receiver whose +0x32c already holds 0 is LEFT ALONE here,
    // because 0 is not -1. The test drives exactly that case, and the inverse
    // mistake (treating the guard as "if zero") is refuted by driving -1.
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = 0x1654c01u;
    }
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x310) = loaded;
    return loaded;
  };

  // -- e3a2e5 .. e3a31b : guarded tag, then the lazy primary/secondary pair ---
  // Reached by selector 0x9f792b4c (e3a29d).
  const auto arm_lazy_324 = [&]() {
    // e3a2e5  CMP [ECX+0x32c],-0x1
    // e3a2ec  JNZ e3a2f8
    // e3a2ee  MOV [ECX+0x32c],0x1654c05
    // e3a2f8  CMP [ECX+0x324],0x0            the flag acted on FOUR
    // e3a2ff  MOV EAX,[ESP+0x8]                instructions later
    // e3a303  MOV EDX,[EAX+0xc]
    // e3a306  MOV EAX,[EDX+0x8]
    // e3a309  MOV [ECX+0x328],EAX            UNCONDITIONAL: +0x328 always
    // e3a30f  JNZ 0x00e3a568
    // e3a315  MOV [ECX+0x324],EAX            +0x324 only when it was zero
    // e3a31b  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = 0x1654c05u;
    }
    const bool primary_already_set = *word_at(self, 0x324) != 0u;
    const void* const block = pointer_at(record, 0x0c);
    const Word loaded = *word_at(block, 0x8);
    *word_at(self, 0x328) = loaded;
    if (primary_already_set) {
      return loaded;  // e3a30f leaves EAX exactly as e3a306 set it
    }
    *word_at(self, 0x324) = loaded;
    return loaded;
  };

  // -- e3a419 .. e3a44f : the same lazy pair on +0x314/+0x318 ----------------
  // Reached by selector 0x279c4e55 (e3a3bf).
  const auto arm_lazy_314 = [&]() {
    // e3a419  CMP [ECX+0x32c],-0x1
    // e3a420  JNZ e3a42c
    // e3a422  MOV [ECX+0x32c],0x1654c02
    // e3a42c  CMP [ECX+0x314],0x0
    // e3a433  MOV EAX,[ESP+0x8]
    // e3a437  MOV EDX,[EAX+0xc]
    // e3a43a  MOV EAX,[EDX+0x8]
    // e3a43d  MOV [ECX+0x318],EAX
    // e3a443  JNZ 0x00e3a568
    // e3a449  MOV [ECX+0x314],EAX
    // e3a44f  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = 0x1654c02u;
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

  // -- e3a468 .. e3a49e : the same lazy pair on +0x31c/+0x320 ----------------
  // Reached by selector 0x3b38f92a (the fall-through at e3a462). Note that the
  // PRIMARY here, +0x31c, is the one arm_copy_into_2b4 writes unconditionally
  // -- the two arms are the eager setter and the lazy default of one quantity.
  const auto arm_lazy_31c = [&]() {
    // e3a468  CMP [ECX+0x32c],-0x1
    // e3a46f  JNZ e3a47b
    // e3a471  MOV [ECX+0x32c],0x1654c04
    // e3a47b  CMP [ECX+0x31c],0x0
    // e3a482  MOV EAX,[ESP+0x8]
    // e3a486  MOV EDX,[EAX+0xc]
    // e3a489  MOV EAX,[EDX+0x8]
    // e3a48c  MOV [ECX+0x320],EAX
    // e3a492  JNZ 0x00e3a568
    // e3a498  MOV [ECX+0x31c],EAX
    // e3a49e  RET 0x8
    if (*word_at(self, 0x32c) == kTagUnset) {
      *word_at(self, 0x32c) = 0x1654c04u;
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

  // == the dispatch: a signed binary search tree, in machine order ===========
  //
  // `signed_greater`, not `>`. The root pivot 0xf278934a is a negative value and
  // a `>` on a std::uint32_t is UNSIGNED, which would send the twelve positive
  // selectors below it instead of above, into a half whose leaf tests are all
  // negative. The three positive pivots further down (0x3e2a3040, 0x279c4e55,
//  0x6cd9ec7b) have the same shape.

  if (signed_greater(key, kSelector_f278934a)) {  // e3a274 CMP / e3a279 JG
    if (signed_greater(key, kSelector_3e2a3040)) {  // e3a3a3 CMP / e3a3a8 JG
      if (signed_greater(key, kSelector_6cd9ec7b)) {  // e3a4be / e3a4c3 (7F JG)
        if (key == kSelector_7115ede5) {  // e3a509 / e3a50e
          return arm_copy_into_29c();
        }
        if (key == kSelector_7bceaa86) {  // e3a510 / e3a515
          return arm_write_three();
        }
        return key;  // e3a515 JNZ to the shared RET: nothing written at all
      }
      if (key == kSelector_6cd9ec7b) {  // e3a4c5
        return arm_write_three();
      }
      if (key == kSelector_5c51063f) {  // e3a4c7 / e3a4cc, a backward jump
        return arm_write_four();
      }
      if (key == kSelector_5fcf28d0) {  // e3a4d2 / e3a4d7
        return arm_write_three();
      }
      if (key == kSelector_6a9f2620) {  // e3a4d9, then the fall-through
        return arm_copy_into_2b4();
      }
      return key;  // e3a4de JNZ
    }
    if (key == kSelector_3e2a3040) {  // e3a3ae
      return arm_tag_init();
    }
    if (signed_greater(key, kSelector_279c4e55)) {  // e3a3b4 CMP / e3a3b9 JG
      if (key == kSelector_2cfa39dd) {  // e3a452 / e3a457
        return arm_copy_into_2b4();
      }
      if (key == kSelector_3b38f92a) {  // e3a45d, then the fall-through
        return arm_lazy_31c();
      }
      return key;  // e3a462 JNZ
    }
    if (key == kSelector_279c4e55) {  // e3a3bf
      return arm_lazy_314();
    }
    if (key == kSelector_f967827c) {  // e3a3c1 / e3a3c6
      return arm_copy_into_29c();
    }
    if (key == kSelector_13df9c1c) {  // e3a3cc / e3a3d1
      return arm_copy_into_29c();
    }
    if (key == kSelector_25ca9233) {  // e3a3d7, then the fall-through
      return arm_write_four();
    }
    return key;  // e3a3dc JNZ
  }
  if (key == kSelector_f278934a) {  // e3a27f
    return arm_write_four();
  }
  if (signed_greater(key, kSelector_aaf6aaac)) {  // e3a285 / e3a28a JG
    if (signed_greater(key, kSelector_d832b059)) {  // e3a337 / e3a33c (7F JG)
      if (key == kSelector_dca976d0) {  // e3a38a / e3a38f, a backward jump
        return arm_copy_into_2c0();
      }
      if (key == kSelector_e0bc9d45) {  // e3a395 / e3a39a
        return arm_write_three();
      }
      return key;  // e3a3a0
    }
    if (key == kSelector_d832b059) {  // e3a33e
      return arm_write_three();
    }
    if (key == kSelector_ade76cce) {  // e3a344 / e3a349
      return arm_tag_then_310();
    }
    if (key == kSelector_cdb3696f) {  // e3a34b / e3a350
      return arm_write_three();
    }
    if (key == kSelector_d536c91d) {  // e3a356 / e3a35b
      return arm_write_three();
    }
    return key;  // e3a361
  }
  if (key == kSelector_aaf6aaac) {  // e3a290
    return arm_copy_into_2c0();
  }
  if (signed_greater(key, kSelector_9f792b4c)) {  // e3a292 / e3a297 JG
    if (key == kSelector_a0973374) {  // e3a31e / e3a323
      return arm_write_three();
    }
    if (key == kSelector_a6cb4c9f) {  // e3a329 / e3a32e
      return arm_write_three();
    }
    return key;  // e3a334
  }
  if (key == kSelector_9f792b4c) {  // e3a29d
    return arm_lazy_324();
  }
  if (key == kSelector_8133fb2e) {  // e3a29f / e3a2a4
    return arm_copy_into_2b4();
  }
  if (key == kSelector_980e43f2) {  // e3a2aa / e3a2af
    return arm_write_three();
  }
  if (key == kSelector_99f0d1da) {  // e3a2b5, then the fall-through
    return arm_copy_into_2c0();
  }
  return key;  // e3a2ba JNZ to the shared RET at e3a568: EAX is still the
               // selector, because no arm has run
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_00e3a400
