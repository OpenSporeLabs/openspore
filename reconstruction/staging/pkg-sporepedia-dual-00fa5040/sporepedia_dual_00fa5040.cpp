// PKG-SPOREpedia-DUAL-00fa5040 -- VA 0x00fa5040
// FUN_00fa5040 (SPORE/SporeBin/SporeApp.exe 3.1.0.22)
//
// A structural transcription of the 297-instruction body at
// 0x00fa5040..0x00fa542e, with every line annotated by the address it comes
// from. The machine parse consumed the whole listing (parse
// {declared_count 297, unparsed 0, degraded false}) and every conditional
// branch target in it lies inside the span, so the body IS these 297
// instructions and nothing else.
//
// WHAT IS CLAIMED AND WHAT IS NOT.
//
//   Claimed, and checkable against the machine by the validator: the control
//   flow, the call set, the argument surface, the memory displacements reached
//   through the receiver, the terminator, and the width of the returned value.
//   Every hexadecimal constant this body needs is transcribed into the package
//   header and referred to by name, so the FIELDS/OFFSETS check reads the
//   machine's own displacements rather than this package's spelling of them;
//   the header says so in as many words, and the model test checks every one
//   of those constants against a literal written separately in the test file.
//
//   Not claimed: what any of the data MEANS. No class, no vtable identity, no
//   receiver type, no field name, no member layout, no object size, no
//   semantics for any of the five callees or the one indirect transfer, and --
//   because reconstruction/evidence/00fa5040/evidence.json records
//   conventions.calling_convention null with confidence UNKNOWN, four
//   candidate conventions and verdict ABI_UNKNOWN -- no calling-convention
//   token anywhere in this package.
//
//   Not claimed either: byte-for-byte equivalence. This is a C++ restatement
//   of the body's semantics, not a transcription of its bytes, and the three
//   no-op LEA ESP,[ESP] at 0x00fa50bc, 0x00fa510c and 0x00fa5259, the NOP at
//   0x00fa520f and the MOV EDI,EDI at 0x00fa529e are alignment padding that
//   carries no semantics and appears nowhere below.
//
// FRAME. SUB ESP,0x1c at 0x00fa5040, then PUSH EBX, PUSH EBP, PUSH ESI and
// PUSH EDI, all restored in reverse order before each of the two terminators
// (0x00fa5231..0x00fa5237 and 0x00fa5425..0x00fa542b). EBP is in that set
// because MOV EBP,ECX at 0x00fa5045 puts the receiver there: this body has no
// frame pointer, EBP is a general register for its whole length, and that is
// exactly the fact the ABI record gives as its first abstention reason. The
// frame is 0x2c bytes in total, so [ESP+0x30] is entry_ESP+0x4 and [ESP+0x34]
// is entry_ESP+0x8 -- the two ordinary stack words the two key scans compare
// against and the two flag tests read.
//
// THE DIVISION. Both element counts come from the same eight-instruction
// sequence (0x00fa5053..0x00fa5067 and 0x00fa509b..0x00fa50ac): a signed
// 64-bit multiply by 0x2fa0be83, an arithmetic shift of the high half by 5,
// and a sign fold of the form (x >> 31 as unsigned) + x. The machine states
// no divisor. The sequence is written out instruction for instruction in
// element_count() rather than replaced by a division, and the model test
// proves over a wide sample that it equals C signed truncated division by
// 0xac -- the stride the very loops that consume the count step by. That
// identity is a property of the constants, asserted as arithmetic and claimed
// as nothing else.

#include "sporepedia_dual_00fa5040.hpp"

namespace openspore {
namespace reconstruction {
namespace pkg_sporepedia_dual_00fa5040 {

// Placed first in this translation unit on purpose: the validator binds a
// source span to 0x00fa5040 by the 8-hex VA token appearing in the function
// name and takes the FIRST such definition in the file. No other function in
// this package carries that token, and the two helpers below are named so
// that none of them does.
extern "C" bool re_00fa5040(Receiver* receiver, Word key, Word second) {
  std::uint8_t* const self = image_of(receiver);

  // The inner six-record walk, shared verbatim by the two halves of the body:
  // 0x00fa5137..0x00fa51aa on the first-array path and 0x00fa529a..0x00fa530e
  // on the second-array path, which are the same instructions against the same
  // four query floats. It answers one question: does any of the six 0x10-byte
  // records inside this candidate object beat the query the caller's helper
  // produced, in the pairing the listing fixes.
  const auto walk_inner_records = [self](const std::uint8_t* object,
                                     std::size_t array_base,
                                     std::size_t element) {
    for (std::size_t record = 0; record < kInnerRecordCount; ++record) {
      // 0x00fa5140..0x00fa514d  the object's own word goes in the first
      // register, the four-float scratch at the bottom of this frame goes on
      // the stack, and the constant zero goes on top of it (XOR EDI,EDI at
      // 0x00fa5137, PUSH EDI at 0x00fa514c). The scratch is the same address
      // on every one of the twelve iterations: LEA ECX,[ESP + 0x1c].
      Real query[kQueryFloatCount];
      probe_00fad140(const_cast<std::uint8_t*>(object), query,
                     kProbeThirdArgument);
      // 0x00fa515e / 0x00fa5164 / 0x00fa5170  the element under test:
      // array base + element index * stride. kRecordFieldOffsets already
      // carries the 0x38 record displacement, because the four displacements
      // the COMISS operands name are 0x38, 0x40, 0x3c and 0x44 -- all four of
      // them relative to the ELEMENT, which is what LEA EAX,[EDX + EAX*0x1 +
      // 0x38] at 0x00fa5177 computes the record base FROM.
      const std::size_t element_address =
          read_word(self, array_base) + element * kElementStride;
      // 0x00fa5172..0x00fa519f  four COMISS, each followed by JBE, so each
      // query float must be STRICTLY greater than its record field. An
      // unordered compare sets CF and ZF on x86 and therefore takes the skip,
      // which is what a C++ `>` on a NaN does too. The pairing is NOT the
      // identity order: query[1] against field 0, query[0] against field 1,
      // query[3] against field 2, query[2] against field 3.
      bool beats = true;
      for (std::size_t slot = 0; slot < kQueryFloatCount && beats; ++slot) {
        // 0x00fa51a1 / 0x00fa5305 step to the next record by 0x10, so the six
        // records a candidate object is walked over are 0x10 bytes apart and
        // each carries its own four fields.
        beats = read_real(self, element_address + record * kInnerRecordStride +
                                  kRecordFieldOffsets[slot]) <
                query[kQueryFieldOrder[slot]];
      }
      if (beats) {
        return true;  // 0x00fa519f JA 0x00fa51ac / 0x00fa5303 JA 0x00fa5313
      }
    }
    // 0x00fa51a1..0x00fa51aa  record exhausted: step on by 0x10, count the
    // pass, and stop at 0x60 -- six records.
    return false;
  };

  // The shared tail, 0x00fa51eb..0x00fa5227 and 0x00fa53e0..0x00fa541b, which
  // are the same instructions against the two arrays.
  const auto release_tail = [self](std::size_t array_base,
                                   std::size_t array_end,
                                   std::size_t element) {
    // 0x00fa51ef / 0x00fa51f5  the found element's own address.
    const std::size_t start =
        read_word(self, array_base) + element * kElementStride;
    // 0x00fa51fb  the array's end word, which is a live cursor, not a count.
    const Word limit = read_word(self, array_end);
    // 0x00fa5201..0x00fa5221  walk from one stride past the found element to
    // the end word, EXACTLY equality on the cursor (JNZ at 0x00fa5221, not a
    // signed or unsigned bound), handing each cursor to 0x00f9f620 together
    // with the array's base address -- SUB EBP,ESI at 0x00fa520d turns the
    // running cursor back into that fixed base at 0x00fa5211.
    for (std::size_t cursor = start + kElementStride; cursor != limit;
         cursor += kElementStride) {
      probe_00f9f620(reinterpret_cast<void*>(start),
                     static_cast<Word>(cursor));
    }
    // 0x00fa5223..0x00fa5227  pull the end word back by one stride, which is
    // the only write this body makes to the receiver's own four words.
    write_word(self, array_end,
               read_word(self, array_end) + kElementDecrement);
    return true;  // 0x00fa5234 MOV AL,0x1
  };

  // 0x00fa5047..0x00fa5067  the first array's element count.
  const Word first_total = element_count(
      read_word(self, kOffArrayOneEnd) - read_word(self, kOffArrayOneBase));

  // 0x00fa5063 / 0x00fa5065 / 0x00fa5074..0x00fa508d  the first key scan. The
  // cursor starts at base + 0xa8 (ADD ECX,0xa8 at 0x00fa507a) and steps by the
  // element stride (ADD ECX,0xac at 0x00fa5085); CMP dword ptr [ECX],EDI at
  // 0x00fa5080 is a full 32-bit equality against the word the caller left at
  // entry_ESP+0x4, and JC at 0x00fa508d stops the walk at the count. The JZ
  // at 0x00fa5072 skips the whole scan when the count is zero, which a
  // zero-trip loop reproduces without a separate test.
  bool hit_one = false;
  std::size_t found_one = 0;
  for (Word scan = 0; scan < first_total; ++scan) {
    if (read_word(self, read_word(self, kOffArrayOneBase) + kOffElementKey +
                            scan * kElementStride) == key) {
      hit_one = true;
      found_one = scan;
      break;
    }
  }

  if (!hit_one) {
    // 0x00fa508f..0x00fa50d1  the second key scan, over the array whose base
    // and end words are at 0x770 and 0x774, with the same count sequence, the
    // same 0xa8 key displacement and the same stride.
    const Word second_total = element_count(
        read_word(self, kOffArrayTwoEnd) - read_word(self, kOffArrayTwoBase));
    bool hit_two = false;
    std::size_t found_two = 0;
    for (Word scan = 0; scan < second_total; ++scan) {
      if (read_word(self, read_word(self, kOffArrayTwoBase) + kOffElementKey +
                              scan * kElementStride) == key) {
        hit_two = true;
        found_two = scan;
        break;
      }
    }

    // 0x00fa50d3..0x00fa50dc  neither array holds the key: the four saved
    // registers come back, AL is zeroed at 0x00fa50d6, and the terminator
    // pops the two argument words. Nothing else in the receiver is touched on
    // this path.
    if (!hit_two) {
      return false;
    }

    // ---- SECOND-ARRAY PATH, entered at 0x00fa523d ----
    //
    // 0x00fa5241 CMP byte ptr [ESP + 0x34],BL / JZ 0x00fa53e0. BL holds zero,
    // so this is "is the low BYTE of entry_ESP+0x8 zero", and only that one
    // byte of that word is ever read.
    if ((second & kSecondSlotByteMask) != 0) {
      // 0x00fa524b..0x00fa53d6  the four sub-tables, at rcv + 0x218 + k*0x14.
      for (std::size_t group = 0; group < kSubTableCount; ++group) {
        const std::size_t table = kOffSubTableGroup + group * kSubTableStride;
        // 0x00fa5260..0x00fa526b  (end - begin) shifted right by two, minus
        // one; the JS at 0x00fa526b skips the group outright when the table
        // is empty, which is what the zero test below reproduces.
        const Word slots = word_span_count(
            read_word(self, table + kOffVectorEnd) -
            read_word(self, table + kOffVectorBegin));
        if (slots == 0) {
          continue;
        }
        // 0x00fa5271..0x00fa53b9  the element walk, DESCENDING: the index
        // starts at count-1 and 0x00fa53b2 decrements it, so the machine
        // visits the last slot first and slot zero last.
        for (Word slot = slots; slot-- > 0;) {
          // 0x00fa5271 / 0x00fa527a / 0x00fa527e  the slot's own word, and
          // 0x00fa5281 skips a null one.
          std::uint8_t* const object =
              image_of(read_pointer(self, read_word(self, table + kOffVectorBegin) +
                                              slot * kVectorWordSize));
          if (object == nullptr) {
            continue;
          }
          // 0x00fa5287..0x00fa5294  bit 3 of the word at object + 0xb8, tested
          // for SET with SHR 3 and TEST 1.
          if (((read_word(object, kOffObjectGateWord) >> kGateWordShift) &
               kGateWordMask) == 0) {
            continue;
          }
          if (!walk_inner_records(object, kOffArrayTwoBase, found_two)) {
            continue;
          }
          // ---- the hit, at 0x00fa5313 ----
          //
          // 0x00fa5313..0x00fa531a packs the group index and the slot index
          // into one word, and 0x00fa531c..0x00fa5332 immediately unpacks
          // it again (SHR 0x18, AND 0xffffff) to recover the two, so the round
          // trip through the register carries no information this
          // reconstruction has to model. What 0x00fa5324..0x00fa533d then
          // does with the unpacked pair is to re-derive this same sub-table's
          // address and bounds the slot against the element count; JNC skips
          // the rest when it is out of range.
          const std::size_t begin = read_word(self, table + kOffVectorBegin);
          const Word count =
              (read_word(self, table + kOffVectorEnd) - begin) / kVectorWordSize;
          if (slot >= count) {
            continue;  // 0x00fa533d JNC 0x00fa53b2
          }
          // 0x00fa533f..0x00fa5346  the slot's word again, and its null test.
          std::uint8_t* const victim =
              image_of(read_pointer(self, begin + slot * kVectorWordSize));
          if (victim == nullptr) {
            continue;  // 0x00fa5346 JZ 0x00fa53b2
          }
          // 0x00fa5348 / 0x00fa534a  one register, nothing on the stack.
          probe_00fadac0(victim);
          // 0x00fa534f..0x00fa5358  decrement the word at +0x4, and skip the
          // rest unless it reached zero.
          const Word remaining = read_word(victim, kOffRefCount) - kUnitWord;
          write_word(victim, kOffRefCount, remaining);
          if (remaining == 0) {
            // 0x00fa535a resets that word to 1, and 0x00fa5361..0x00fa536a is
            // this body's one indirect transfer: the destination is the SECOND
            // word of the object's own first word, the object goes in the
            // first register, and the immediate 1 goes on the stack. The
            // machine dispatch record counts exactly one indirect transfer in
            // all 297 instructions, and classifies this site as a two-level
            // table load at displacement zero.
            write_word(victim, kOffRefCount, kRefCountReset);
            void** const transfers = reinterpret_cast<void**>(
                read_pointer(victim, kOffObjectFirstWord));
            (reinterpret_cast<void (*)(void*, Word)>(
                transfers[kIndirectEntryIndex]))(victim, kIndirectArgument);
          }
          // 0x00fa5386  the taken slot is cleared to zero whatever the
          // refcount did, and the slot index is spilled to a frame word at
          // 0x00fa5390 for the grow call below.
          write_word(self, begin + slot * kVectorWordSize, kClearedWord);
          // 0x00fa5370..0x00fa5380  the pending vector hanging off this
          // sub-table: rcv + group*0x14 + 0x268, which is the sub-table at
          // rcv + 0x218 + group*0x14 plus kPendingVectorOffsetFromSubTable.
          const std::size_t pending = table + kPendingVectorOffsetFromSubTable;
          const Word carried = slot;
          const std::size_t end = read_word(self, pending + kOffVectorEnd);
          if (end >= read_word(self, pending + kOffVectorCapacity)) {
            // 0x00fa53a7..0x00fa53ad  grow, with the slot index by value and
            // the cursor by pointer. 0x00fa53b2 follows the call, so no
            // result of any width is read.
            probe_004558a0(reinterpret_cast<void*>(end), &carried);
          } else {
            // 0x00fa5399..0x00fa53a5  make room and store -- but only when the
            // cursor is not the null word, which TEST EAX,EAX / JZ at
            // 0x00fa539f..0x00fa53a1 turns into a real condition.
            write_word(self, pending + kOffVectorEnd, end + kVectorWordSize);
            if (end != 0) {
              write_word_at(image_of(reinterpret_cast<void*>(end)), carried);
            }
          }
        }
      }
    }

    // 0x00fa53e0..0x00fa542e  the second-array tail: the same walk and the
    // same one-stride pull-back as the first-array tail, over the array at
    // 0x770 whose end word is at 0x774. AL is set at 0x00fa5428.
    return release_tail(kOffArrayTwoBase, kOffArrayTwoEnd, found_two);
  }

  // ---- FIRST-ARRAY PATH, entered at 0x00fa50df ----
  //
  // 0x00fa50e3 CMP byte ptr [ESP + 0x34],BL / JZ 0x00fa51eb -- the same
  // one-byte test of the same stack word as on the second-array path, with the
  // same "skip the sub-tables" outcome when it is zero.
  if ((second & kSecondSlotByteMask) != 0) {
    // 0x00fa50ed..0x00fa51e5  the same four sub-tables, walked from
    // rcv + 0x218 in steps of 0x14, and inside each one from the last slot
    // down to slot zero.
    for (std::size_t group = 0; group < kSubTableCount; ++group) {
      const std::size_t table = kOffSubTableGroup + group * kSubTableStride;
      // 0x00fa50f7..0x00fa5106  (end - begin) >> 2, minus one, and a JS that
      // leaves the group when the table is empty.
      const Word slots = word_span_count(
          read_word(self, table + kOffVectorEnd) -
          read_word(self, table + kOffVectorBegin));
      if (slots == 0) {
        continue;
      }
      for (Word slot = slots; slot-- > 0;) {
        // 0x00fa5110..0x00fa511e  the slot's own word, and its null test.
        std::uint8_t* const object =
            image_of(read_pointer(self, read_word(self, table + kOffVectorBegin) +
                                            slot * kVectorWordSize));
        if (object == nullptr) {
          continue;
        }
        // 0x00fa5124..0x00fa5131  bit 3 of the word at object + 0xb8.
        if (((read_word(object, kOffObjectGateWord) >> kGateWordShift) &
             kGateWordMask) == 0) {
          continue;
        }
        if (!walk_inner_records(object, kOffArrayOneBase, found_one)) {
          continue;
        }
        // 0x00fa51ac..0x00fa51b8  the ONLY thing the first-array path does on
        // a hit: pack the group index and the slot index into one word and
        // hand it to 0x00fa29b0. There is no refcount, no indirect transfer
        // and no pending vector here -- those exist only on the second-array
        // path, and that difference is the sharpest structural fact separating
        // the two halves of this body.
        probe_00fa29b0(static_cast<Word>((group << kGroupIndexShift) |
                                         (slot & kGroupIndexMask)));
      }
    }
  }

  // 0x00fa51eb..0x00fa523a  the first-array tail. AL is set at 0x00fa5234.
  return release_tail(kOffArrayOneBase, kOffArrayOneEnd, found_one);
}

}  // namespace pkg_sporepedia_dual_00fa5040
}  // namespace reconstruction
}  // namespace openspore
