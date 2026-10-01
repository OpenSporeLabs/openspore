// PKG-SWARM-W1-00FA6EC0 -- VA 0x00fa6ec0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body: 40 instructions, 0x00fa6ec0..0x00fa6f37 inclusive
// (ghidra_function.body_start 0x00fa6ec0, body_end 0x00fa6f37, size_bytes 120).
// The listing was re-read from the image for this package -- GhidraMCP
// /read_memory over the 120 bytes at 0x00fa6ec0 -- and the 40 instruction
// encodings below are the ones those bytes actually hold, so the instruction
// lengths, the two relative call displacements and the terminator are all
// confirmed against the image rather than taken on trust:
//
//   00fa6ec0  53                    PUSH EBX
//   00fa6ec1  56                    PUSH ESI
//   00fa6ec2  8b f1                 MOV ESI,ECX
//   00fa6ec4  8b 9e 70 07 00 00     MOV EBX,dword ptr [ESI + 0x770]
//   00fa6eca  57                    PUSH EDI
//   00fa6ecb  8b be 74 07 00 00     MOV EDI,dword ptr [ESI + 0x774]
//   00fa6ed1  53                    PUSH EBX
//   00fa6ed2  57                    PUSH EDI
//   00fa6ed3  57                    PUSH EDI
//   00fa6ed4  e8 97 88 ff ff        CALL 0x00f9f770
//   00fa6ed9  2b fb                 SUB EDI,EBX
//   00fa6edb  b8 7d 41 5f d0        MOV EAX,0xd05f417d
//   00fa6ee0  f7 ef                 IMUL EDI
//   00fa6ee2  c1 fa 05              SAR EDX,0x5
//   00fa6ee5  8b c2                 MOV EAX,EDX
//   00fa6ee7  c1 e8 1f              SHR EAX,0x1f
//   00fa6eea  03 c2                 ADD EAX,EDX
//   00fa6eec  69 c0 ac 00 00 00     IMUL EAX,EAX,0xac
//   00fa6ef2  01 86 74 07 00 00     ADD dword ptr [ESI + 0x774],EAX
//   00fa6ef8  8b 9e 84 07 00 00     MOV EBX,dword ptr [ESI + 0x784]
//   00fa6efe  8b be 88 07 00 00     MOV EDI,dword ptr [ESI + 0x788]
//   00fa6f04  53                    PUSH EBX
//   00fa6f05  57                    PUSH EDI
//   00fa6f06  57                    PUSH EDI
//   00fa6f07  e8 64 88 ff ff        CALL 0x00f9f770
//   00fa6f0c  2b fb                 SUB EDI,EBX
//   00fa6f0e  b8 7d 41 5f d0        MOV EAX,0xd05f417d
//   00fa6f13  f7 ef                 IMUL EDI
//   00fa6f15  c1 fa 05              SAR EDX,0x5
//   00fa6f18  8b ca                 MOV ECX,EDX
//   00fa6f1a  c1 e9 1f              SHR ECX,0x1f
//   00fa6f1d  03 ca                 ADD ECX,EDX
//   00fa6f1f  69 c9 ac 00 00 00     IMUL ECX,ECX,0xac
//   00fa6f25  01 8e 88 07 00 00     ADD dword ptr [ESI + 0x788],ECX
//   00fa6f2b  ff 86 14 08 00 00     INC dword ptr [ESI + 0x814]
//   00fa6f31  83 c4 18              ADD ESP,0x18
//   00fa6f34  5f                    POP EDI
//   00fa6f35  5e                    POP ESI
//   00fa6f36  5b                    POP EBX
//   00fa6f37  c3                    RET
//
// The two call displacements resolve to the same target from their two
// sites, which is the first of the two facts this reconstruction turns on.
// From 0x00fa6ed4 the rel32 is 0xffff8897, i.e. 0x00fa6ed9 - 0x7769 =
// 0x00f9f770; from 0x00fa6f07 the rel32 is 0xffff8864, i.e. 0x00fa6f0c - 0x779c
// = 0x00f9f770. One callee, called twice.
//
// WHAT THE BODY IS, in the order the machine does it:
//
//   1. Alias the receiver: ECX -> ESI (0x00fa6ec2), and every one of the seven
//      receiver accesses below goes through ESI. ECX is dead from there on.
//   2. Read two words (0x770 then 0x774) into EBX and EDI.
//   3. Call 0x00f9f770 with, right to left, EBX, EDI, EDI -- that is
//      (0x770's word, 0x774's word, 0x774's word). In the callee's own frame
//      that is (arg1, arg2, arg3) = (0x774's word, 0x774's word, 0x770's word):
//      0x00f9f771 reads arg2, 0x00f9f776 reads arg1, 0x00f9f77f reads arg3.
//      So the callee's source range is [arg1, arg2) and arg1 == arg2 HERE, by
//      construction: both words pushed at 0x00fa6ed2 and 0x00fa6ed3 came from
//      the single 0x00fa6ecb read, and nothing writes memory between that read
//      and the call. The callee's loop condition (0x00f9f77a CMP ESI,EBX) is
//      therefore false on entry, it takes the equal-range exit at 0x00f9f7a1,
//      and it moves no element and writes no memory. The call is REAL and the
//      model makes it, but it is observationally dead: the callee's only output
//      is EAX, and 0x00fa6edb overwrites EAX two instructions later.
//   4. Compute the byte span (0x00fa6ed9 SUB EDI,EBX = the 0x774 word minus the
//      0x770 word), run it through a signed magic-multiply division by 0xAC, and
//      multiply the quotient back out by 0xAC (0x00fa6eec). The 32-bit product
//      stored at 0x00fa6ef2 is added to the word at +0x774 AS IT STANDS IN
//      MEMORY -- the instruction is a read-modify-write on memory, not a store
//      of a register copy, and the model reads the word at the point of the add.
//   5. Steps 2 to 4 again, byte for byte, on the pair at +0x784 / +0x788. The
//      second block carries the quotient in ECX rather than EAX; the only
//      difference that survives is which register the intermediate lives in,
//      which no observer can see, and which block ran last, which EAX can.
//   6. Increment the word at +0x814 (0x00fa6f2b). That is the last memory
//      write in the body.
//   7. Epilogue, unmodelled: ADD ESP,0x18 drops the six argument words the two
//      cdecl calls pushed (3 pushes + 3 pushes = 0x18, popped once), the three
//      POPs undo the prologue's three pushes, and a bare RET. Nothing here
//      produces a value.
//
// FRAME, resolved once so every displacement above is a fact. Entry ESP is 0 in
// the walk. The prologue pushes three words (0x00fa6ec0, 0x00fa6ec1, 0x00fa6eca)
// so the body runs at ESP = entry-12; each call pushes three more and 0x00f9f770
// pops none of them, so after the first call ESP = entry-24 and after the second
// ESP = entry-36; 0x00fa6f31's ADD ESP,0x18 and the three POPs land back on entry
// ESP exactly, and the bare RET consumes only the return address. So:
//
//   entry+0    the return address
//   entry+4    first ordinary argument slot -- NEVER READ by any of the 40
//              instructions, and never written by the callee either
//   entry+8    second ordinary argument slot -- likewise never read
//
// That pair of rows is the whole ABI argument surface: zero ordinary arguments.
// It is also why the body cannot be shown to be __thiscall rather than
// __fastcall by argument passing alone -- nothing reads a stack slot -- and the
// sidecar keeps that open rather than closing it. What the listing does fix is
// the receiver: 0x00fa6ec2 moves ECX into ESI and the seven accesses above are
// all displacements from that alias, with the machine-derived receiver record
// agreeing at register ECX, offsets [0x770, 0x774, 0x784, 0x788, 0x814].
//
// THE DIVISION, spelled out because it is the only arithmetic in the body and
// the one place a reconstruction is most likely to be wrong in a way that
// survives a casual look. The sequence at 0x00fa6edb..0x00fa6eec is the standard
// signed-division-by-constant expansion, and the constant is NEGATIVE:
//
//   * 0xd05f417d as a signed 32-bit integer is -799063683, and
//     0x2FA0BE83 = floor(2^37 / 172) = 799063682 with the value 799063683 one
//     above it. 0x00fa6ee0 is a SIGNED IMUL (F7 EF, the /5 form), so the
//     multiplier goes into the product as -799063683.
//   * for a POSITIVE span that makes the product negative, so EDX after
//     0x00fa6ee2 (SAR EDX,0x5, an arithmetic shift) is a NEGATIVE floor, and
//     the two instructions 0x00fa6ee7/0x00fa6eea (SHR EAX,0x1f then ADD EAX,EDX)
//     add 1 back, which is a truncation toward zero.
//   * net effect: the quotient is -(span / 0xAC) with C++ truncating division,
//     and 0x00fa6eec's multiply by 0xAC makes the value stored at 0x00fa6ef2
//     equal to -(span / 0xAC) * 0xAC. The sign is the whole story here, and it is
//     the opposite of the span's for a well-formed range.
//
// WHAT THE ADJUSTMENT DOES TO A RANGE, stated as arithmetic and not as a story.
// With span = last - first the store at 0x00fa6ef2 is
//
//     last  +=  -(span / 0xAC) * 0xAC
//
// which, for a well-formed range, is the same as
//
//     last   =  first + (span mod 0xAC)
//
// because span - trunc(span/0xAC)*0xAC is the remainder. Two consequences follow
// directly and neither of them is inferred:
//
//   * a range that already ends on an element boundary (span a multiple of 0xAC)
//     ends up with last == first -- the range reads as EMPTY. For example a
//     five-element range (span 860) stores -860 and last lands exactly on first.
//   * a range whose last word has drifted off the boundary (span 5*0xAC + 0x37)
//     also lands on first + 0x37, i.e. it shrinks by five WHOLE elements and
//     keeps the sub-element residue. That is not a normalisation: first + 0x37
//     is not a position any element occupies.
//
// Whether the original author meant a truncate-to-boundary, a clear, or something
// else entirely is NOT recoverable from these 40 instructions, and nothing in the
// image says. The two sibling methods of the same table make the neighbouring
// shapes legible -- 0x00fa7220 does copy(begin+0xAC, last, begin); last -= 0xAC,
// which is erase(0), and 0x00fa5040 does copy(begin+i+1, last, begin+i); last -=
// 0xAC, which is erase(i) -- but neither is the same expression, so they bound
// the idiom without deciding it. The model therefore computes the machine's
// exact instruction sequence and states the arithmetic, and the sidecar carries
// the intent as an open question rather than an answer.
//
// RETURN SEMANTICS. The last write to EAX in the whole body is 0x00fa6f13
// IMUL EDI -- the low half of the SECOND block's 64-bit product. Nothing after
// it touches EAX: the second block's quotient is computed in ECX, the counter
// increment is a memory RMW, and the epilogue moves no register. So EAX at the
// RET holds the low 32 bits of (span of the 0x784/0x788 pair) * -799063683, and
// the first block's identical product is gone. The model returns exactly those
// bits. Their MEANING is not established by anything: the only reference to this
// body in the image is its own pointer in the table at 0x01490be8, no code in
// the image calls it, and abi_derived records the return as
// unclassified_in_EAX / aggregate_unknown. Declaring Word states the width and
// the bits; it asserts nothing about what they count.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the 40
// instructions contain no register- or memory-operand transfer. The data
// reference from 0x01490c48 is this body at slot +0x60 of the table at
// 0x01490be8 (read off that table's own bytes: the dword at +0x60 is
// 0x00fa6ec0), but the body itself never reads a dispatch word, so no slot
// boundary is declared in this model and nothing at the receiver's +0x00 is
// named.
//
// GLOBALS: none. Not one of the 40 instructions names a data-segment address;
// the only absolute operand outside the body is the relative displacement of the
// two calls.

#include "w22_00fa6ec0_types.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0 {
namespace {

// A 32-bit bit pattern read back as a signed value, through memcpy so that no
// step depends on an implementation-defined out-of-range conversion. The
// machine's SUB, IMUL and ADD all wrap at 32 bits and the model must too.
std::int32_t as_signed(Word bits) {
  std::int32_t value = 0;
  std::memcpy(&value, &bits, sizeof value);
  return value;
}

// The span the machine's SUB EDI,EBX produces, from the two pointer values it
// held. A pointer difference is computed on the 32-bit values the machine would
// have subtracted, so the subtraction wraps at 32 bits exactly as SUB does.
std::int32_t byte_span(Element* last, Element* first) {
  return as_signed(static_cast<Word>(reinterpret_cast<std::uintptr_t>(last) -
                                     reinterpret_cast<std::uintptr_t>(first)));
}

// The machine's arithmetic right shift, done on the raw bit pattern: the dropped
// top bits are replicated rather than zero-filled, which is what SAR does and
// what SHR does not. Kept as a separate step because 0x00fa6ee2 is a SAR and
// 0x00fa6ee7 is a SHR, and getting the second one wrong is exactly the defect
// that turns a truncated quotient into a floored one for negative spans.
Word sar32(Word bits, unsigned shift) {
  // The top `shift` bits are replicated down over the bits the shift dropped,
  // which is what makes the result arithmetic. Replicating them by OR-ing in an
  // all-ones word would be wrong: it would set all 32 bits, not the 5 that were
  // lost, and the quotient would collapse to 0 or to -1.
  const Word fill = (bits >> 31u) != 0u ? (~Word(0) << (32u - shift)) : Word(0);
  return (bits >> shift) | fill;
}

// One of the two blocks, arithmetic only, in the machine's exact order, and it
// produces the TWO values the block ends up holding rather than one. Keeping
// them apart matters: the adjustment is what the block stores back and the
// product's low word is what survives into EAX, and the two are NOT the same
// number -- one is a whole number of strides, the other is a 32-bit residue of a
// multiply. They are written through pointers rather than returned in a struct
// because the two are separate machine registers, and a struct would hide that.
//
// span is what SUB EDI,EBX produced, so it can be negative for a malformed
// vector, and the model must not normalise it first.
void snap_to_whole_elements(std::int32_t span, Word* adjustment, Word* low_product) {
  // 00fa6edb  MOV EAX,0xd05f417d
  // 00fa6f0e  MOV EAX,0xd05f417d           (second block, identical)
  // 00fa6ee0  IMUL EDI              -> EDX:EAX = span * (-799063683)
  // 00fa6f13  IMUL EDI              (second block, identical)
  const std::int64_t product = static_cast<std::int64_t>(span) *
                               static_cast<std::int64_t>(as_signed(kQuotientMagic));
  // 00fa6ee2  SAR EDX,0x5           -> shift the high word right, arithmetic
  // 00fa6f15  SAR EDX,0x5           (second block, identical)
  const Word shifted = sar32(static_cast<Word>(static_cast<std::uint64_t>(product) >> 32), 5u);
  // 00fa6ee5  MOV EAX,EDX
  // 00fa6ee7  SHR EAX,0x1f          -> 1 exactly when the shifted value is negative
  // 00fa6eea  ADD EAX,EDX           -> quotient, truncated toward zero
  // 00fa6f18  MOV ECX,EDX / 00fa6f1a  SHR ECX,0x1f / 00fa6f1d  ADD ECX,EDX
  const Word quotient = shifted + (shifted >> 0x1fu);
  // 00fa6eec  IMUL EAX,EAX,0xac
  // 00fa6f1f  IMUL ECX,ECX,0xac    (second block, identical, carried in ECX)
  *adjustment = quotient * kElementStride;
  // EAX is left holding the product's low half, because 00fa6ee5 MOV EAX,EDX
  // consumed the high half and nothing wrote EAX again.
  *low_product = static_cast<Word>(product);
}

}  // namespace

extern "C" Word PKG_SWARM_W1_00FA6EC0_THISCALL re_00fa6ec0(Owner* receiver) {
  // 00fa6ec2  MOV ESI,ECX
  //
  // The receiver alias. Every access below is a displacement from it, which is
  // why the machine-derived receiver record reports register ECX with shape
  // R-ALIAS and why this model reaches the receiver as a byte run rather than
  // through named members: the record is bounds_only, so it says where the body
  // reached and nothing about which member is which.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00fa6ec4  MOV EBX,dword ptr [ESI + 0x770]
  // 00fa6ecb  MOV EDI,dword ptr [ESI + 0x774]
  //
  // Two words of the receiver, read once each, into EBX and EDI. Which of them
  // is the first of the range and which is the last is not this body's business
  // and is not decided here: the two sibling methods of the same table that DO
  // walk the range (0x00fa5040 at slot +0x58, 0x00fa7220 at slot +0x64) index
  // elements forward from the 0x770 word and stop at the 0x774 word, which is
  // what fixes the order. The names below carry that finding; the two reads do
  // not depend on it.
  Element* const pair_a_first = *pointer_at(self, kFirstPairFirstDisplacement);
  Element* const pair_a_last = *pointer_at(self, kFirstPairLastDisplacement);

  // 00fa6ed1  PUSH EBX          arg3
  // 00fa6ed2  PUSH EDI          arg2
  // 00fa6ed3  PUSH EDI          arg1
  // 00fa6ed4  CALL 0x00f9f770
  //
  // Three words, right to left, and the two middle pushes carry the SAME value
  // because both come from the single 0x00fa6ecb read. Read in the callee's own
  // frame (0x00f9f771 takes arg2, 0x00f9f776 takes arg1, 0x00f9f77f takes arg3)
  // the call is (arg1 = the 0x774 word, arg2 = the 0x774 word, arg3 = the 0x770
  // word), and 0x00f9f770's loop condition is `arg1 == arg2` -> take the exit
  // that copies nothing.
  //
  // This is the single most fragile call in the body, because a reconstruction
  // that pushes the 0x770 word in the middle instead of the third place would
  // produce a callee whose source range is non-empty and would MOVE ELEMENTS.
  // The model keeps the machine's order and the model test measures the order.
  element_range_move_00f9f770(pair_a_last, pair_a_last, pair_a_first);

  // 00fa6ed9  SUB EDI,EBX
  //   ... 00fa6eec ...
  // 00fa6ef2  ADD dword ptr [ESI + 0x774],EAX
  //
  // The byte span comes from the two values loaded BEFORE the call, not from
  // anything the callee returned: EAX from the callee is dead, and EDI and EBX
  // are this body's own registers. So the span is the register difference, and
  // the store is a read-modify-write against memory -- the word it adds to is
  // re-read here rather than taken from a cached copy of 0x00fa6ecb. The two are
  // indistinguishable for the real callee, which writes nothing, and the model
  // test makes them distinguishable with an adversarial observer.
  Word adjustment_a = 0;
  Word product_a = 0;
  snap_to_whole_elements(byte_span(pair_a_last, pair_a_first), &adjustment_a, &product_a);
  *word_at(self, kFirstPairLastDisplacement) =
      *word_at(self, kFirstPairLastDisplacement) + adjustment_a;

  // 00fa6ef8  MOV EBX,dword ptr [ESI + 0x784]
  // 00fa6efe  MOV EDI,dword ptr [ESI + 0x788]
  //
  // The second pair, read after the first pair's store has already landed, so
  // nothing here can be hoisted above the 0x00fa6ef2 write. If it were, and if
  // the pair overlapped, the reads would see a stale word.
  Element* const pair_b_first = *pointer_at(self, kSecondPairFirstDisplacement);
  Element* const pair_b_last = *pointer_at(self, kSecondPairLastDisplacement);

  // 00fa6f04  PUSH EBX          arg3
  // 00fa6f05  PUSH EDI          arg2
  // 00fa6f06  PUSH EDI          arg1
  // 00fa6f07  CALL 0x00f9f770
  //
  // The same call, the same argument order and the same equal-range deadness,
  // for the same structural reason. The model's second call is what a test can
  // use to see whether the reconstruction re-reads the receiver at the right
  // moment, because by now the word at +0x774 has been rewritten by the
  // 0x00fa6ef2 store and a reconstruction holding a stale copy of the first
  // pair would pass something else.
  element_range_move_00f9f770(pair_b_last, pair_b_last, pair_b_first);

  // 00fa6f0c  SUB EDI,EBX
  //   ... 00fa6f1f, with the quotient carried in ECX instead of EAX ...
  // 00fa6f25  ADD dword ptr [ESI + 0x788],ECX
  //
  // Identical arithmetic, identical read-modify-write, one register different.
  // The register difference is invisible to any observer, so the model reuses
  // the one helper; what is NOT invisible is that this block, not the first,
  // decides the value left in EAX, and the model returns this block's product
  // low word below.
  Word adjustment_b = 0;
  Word product_b = 0;
  snap_to_whole_elements(byte_span(pair_b_last, pair_b_first), &adjustment_b, &product_b);
  *word_at(self, kSecondPairLastDisplacement) =
      *word_at(self, kSecondPairLastDisplacement) + adjustment_b;

  // 00fa6f2b  INC dword ptr [ESI + 0x814]
  //
  // The last memory write in the body, unconditional, on every path (there is
  // only one path). It comes after both pairs have been snapped and after both
  // calls have returned, which the model test checks by having the second
  // call's observer read the counter.
  ++*word_at(self, kCounterDisplacement);

  // 00fa6f0e  MOV EAX,0xd05f417d
  // 00fa6f13  IMUL EDI
  //
  // EAX, not ECX: the second block's quotient went to ECX and left EAX holding
  // the low half of the multiply, which is the value product_b already carries.
  // It is the last write to EAX before the 0x00fa6f2b memory RMW and the
  // 00fa6f31 epilogue, so it is what the machine returns in EAX -- and it is the
  // SECOND block's, because the first block's identical product was overwritten
  // by 0x00fa6f0e. product_a is the dead one and is deliberately unused.
  //
  // 00fa6f31  ADD ESP,0x18
  // 00fa6f34  POP EDI / 00fa6f35  POP ESI / 00fa6f36  POP EBX
  // 00fa6f37  RET
  //
  // The epilogue, unmodelled: it drops the six argument words of the two cdecl
  // calls, restores EBX/ESI/EDI and returns with a bare RET, producing nothing.
  return product_b;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa6ec0
