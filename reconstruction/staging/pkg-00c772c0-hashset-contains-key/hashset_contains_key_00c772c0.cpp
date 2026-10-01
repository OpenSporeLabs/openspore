#include "hashset_contains_key_00c772c0.hpp"

#if defined(_MSC_VER)
#define PKG_00C772C0_THISCALL __thiscall
#else
#define PKG_00C772C0_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c772c0_hashset_contains_key {

extern "C" bool PKG_00C772C0_THISCALL hashset_contains_key_00c772c0(
    OpaqueBucketContainer* container, std::uint32_t key) {
  // 0x00c772c0  56           PUSH ESI
  // 0x00c772c1  57           PUSH EDI
  //
  // Two callee-saved registers are pushed and popped around the body and the
  // frame is never otherwise used, so the whole of the work happens in EAX,
  // EDX, ECX and ESI. The two words the body needs from the receiver are read
  // through the header's displacement constants rather than through member
  // syntax, because the machine-derived receiver record is bounds_only: it
  // enumerates 0x1120 and 0x1124 and does not say which member of any type
  // occupies either of them.
  const std::uint32_t bucket_count =
      container->bucket_count_1124;  // DIV dword ptr [ECX + 0x1124]

  // 0x00c772c6  33 d2        XOR  EDX,EDX
  // 0x00c772c8  8b c7        MOV  EAX,EDI
  // 0x00c772ca  f7 b1 ...    DIV  dword ptr [ECX + 0x1124]
  //
  // EDX is zeroed first, so the 64-bit dividend is 0:key. DIV is the unsigned
  // 32-bit divide: EAX receives the quotient and EDX the remainder. The
  // quotient is discarded, because the next instruction overwrites EAX with the
  // bucket base. Only the remainder is used, which is what makes the index
  // `key % count` and not a mask, not the quotient, and not a mixed hash.
  //
  // The divisor comes straight out of the receiver and is never tested, so a
  // receiver whose count word is zero traps the machine with #DE. C++ unsigned
  // division by zero is undefined behaviour rather than a trap, so this line is
  // only faithful for a non-zero count - the observed precondition. The model
  // test never calls the entry with a zero count, and the header records the
  // divergence rather than papering over it.
  const std::uint32_t bucket_index = key % bucket_count;

  // 0x00c772d0  8b 81 ...    MOV  EAX,dword ptr [ECX + 0x1120]
  // 0x00c772d6  33 f6        XOR  ESI,ESI
  //
  // EAX becomes the base of the bucket array and ESI the match counter, zeroed
  // before the walk. The counter is a counter, not a flag: it is incremented
  // once per matching link and is not tested until after the loop, so a chain
  // that holds the same key twice counts two.
  // The word at +0x1120 is read as a 32-bit BASE ADDRESS and the remainder
  // scales it by four, so the model keeps it as a 32-bit word and casts once,
  // rather than declaring the field a typed pointer. On this target the two are
  // layout-identical, and the cast form is the one that mirrors the machine.
  auto* const buckets =
      reinterpret_cast<OpaqueBucketLink* const*>(container->bucket_base_1120);
  std::uint32_t match_count = 0;

  // 0x00c772d8  8b 14 90     MOV  EDX,dword ptr [EAX + EDX*0x4]
  //
  // The SIB scale of four is what makes the index a bucket index: each element
  // is one 4-byte head pointer, and the element read is the HEAD of a chain
  // rather than a node.
  OpaqueBucketLink* link = buckets[bucket_index];

  // 0x00c772db  85 d2        TEST EDX,EDX
  // 0x00c772dd  74 0d        JZ   0x00c772ec
  //
  // An empty bucket leaves the head pointer zero and the loop is skipped
  // entirely, so an empty chain is answered without a single compare.
  //
  // 0x00c772df  90           NOP
  // 0x00c772e0  3b 3a        CMP  EDI,dword ptr [EDX]
  // 0x00c772e2  75 01        JNZ  0x00c772e5
  // 0x00c772e4  46           INC  ESI
  // 0x00c772e5  8b 52 04     MOV  EDX,dword ptr [EDX + 0x4]
  // 0x00c772e8  85 d2        TEST EDX,EDX
  // 0x00c772ea  75 f4        JNZ  0x00c772e0
  //
  // The whole chain is walked to its end. There is no early exit on a match, no
  // iteration cap and no pointer-identity check, so a cyclic chain would spin
  // forever; whether one can exist is not established here and the model test
  // does not build one. The compare is a full 32-bit equality against the
  // argument, and the argument is the same value the bucket index was derived
  // from - the body applies no mixing function, so a key and its index come
  // from the same 32 bits.
  while (link != nullptr) {
    if (link->key_00 == key) {
      ++match_count;
    }
    link = link->next_04;
  }

  // 0x00c772ec  33 c0        XOR  EAX,EAX
  // 0x00c772ee  85 f6        TEST ESI,ESI
  // 0x00c772f0  5f           POP  EDI
  // 0x00c772f1  0f 95 c0     SETNZ AL
  // 0x00c772f4  5e           POP  ESI
  // 0x00c772f5  c2 04 00     RET  0x4
  //
  // EAX is zeroed and only AL is then written, so the upper 24 bits are
  // provably zero and the result is strictly 0 or 1. The count survives only
  // as its own non-zeroness: a chain holding the key three times answers 1,
  // not 3. The boolean conversion is written as a comparison rather than as
  // `match_count != 0` folded into a return type so that the discarded count
  // and the surviving flag are two distinct steps in the source, matching the
  // TEST/SETNZ pair in the listing.
  const bool found = (match_count != 0u);
  return found;
}

}  // namespace openspore::reconstruction::pkg_00c772c0_hashset_contains_key
