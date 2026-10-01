// PKG-SWARM-W1-00FA5580 -- VA 0x00fa5580
// FUN_00fa5580 (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// The complete body: 46 instructions, 0x00fa5580..0x00fa5601 inclusive
// (ghidra_function.body_start 0x00fa5580, body_end 0x00fa5603, size_bytes 132). The
// listing below is re-derived from the image bytes with
// `objdump -d -M intel --start-address=0x00fa5580 --stop-address=0x00fa5604`, which
// reproduces the committed 46 instructions at the same addresses with identical
// mnemonics, operands, call targets and branch targets; the two ret forms
// (`C2 04 00` at 0x00fa55cc and at 0x00fa5601) and the 11-byte
// `ADD dword ptr [ESI+0x79c],0xffffff54` at 0x00fa55f2 are confirmed from the same
// bytes. Nothing in this model depends on the decompilation, and the one place the
// decompilation is worth quoting is the count, which it renders as a division.
//
//   00fa5580  PUSH EBX
//   00fa5581  PUSH ESI
//   00fa5582  MOV ESI,ECX                       receiver alias
//   00fa5584  MOV EDX,dword ptr [ESI + 0x79c]   end
//   00fa558a  SUB EDX,dword ptr [ESI + 0x798]   end - begin
//   00fa5590  MOV EAX,0x2fa0be83
//   00fa5595  IMUL EDX
//   00fa5597  SAR EDX,0x5
//   00fa559a  MOV EAX,EDX
//   00fa559c  SHR EAX,0x1f
//   00fa559f  ADD EAX,EDX                       count
//   00fa55a1  XOR ECX,ECX                       index = 0
//   00fa55a3  PUSH EDI
//   00fa55a4  TEST EAX,EAX
//   00fa55a6  JLE 0x00fa55c7                     count <= 0 -> not found
//   00fa55a8  MOV EDI,dword ptr [ESI + 0x798]   begin
//   00fa55ae  MOV EBX,dword ptr [ESP + 0x10]    the argument word, entry+4
//   00fa55b2  LEA EDX,[EDI + 0xa8]              first candidate's key word
//   00fa55b8  CMP dword ptr [EDX],EBX
//   00fa55ba  JZ 0x00fa55cf
//   00fa55bc  INC ECX
//   00fa55bd  ADD EDX,0xac
//   00fa55c3  CMP ECX,EAX
//   00fa55c5  JL 0x00fa55b8
//   00fa55c7  POP EDI
//   00fa55c8  POP ESI
//   00fa55c9  XOR AL,AL                         return 0
//   00fa55cb  POP EBX
//   00fa55cc  RET 0x4
//   00fa55cf  MOV EDX,dword ptr [ESI + 0x79c]   end, read a second time
//   00fa55d5  IMUL ECX,ECX,0xac
//   00fa55db  ADD ECX,EDI                       the found element
//   00fa55dd  LEA EAX,[ECX + 0xac]              the element after it
//   00fa55e3  CMP EAX,EDX
//   00fa55e5  JNC 0x00fa55f2                    UNSIGNED: skip the shift
//   00fa55e7  PUSH ECX
//   00fa55e8  PUSH EDX
//   00fa55e9  PUSH EAX
//   00fa55ea  CALL 0x00f9f770
//   00fa55ef  ADD ESP,0xc
//   00fa55f2  ADD dword ptr [ESI + 0x79c],0xffffff54
//   00fa55fc  POP EDI
//   00fa55fd  POP ESI
//   00fa55fe  MOV AL,0x1                        return 1
//   00fa5600  POP EBX
//   00fa5601  RET 0x4
//
// FRAME, resolved once against the entry ESP so every displacement below is a fact.
// Entry ESP is 0 in the walk. The prologue pushes three words (entry-4 EBX, entry-8
// ESI, entry-12 EDI); the single call is cdecl and the body drops its three words
// itself at 0x00fa55ef; each epilogue pops the same three in reverse. So at
// 0x00fa55ae the ESP in effect is entry-12 and `MOV EBX,[ESP+0x10]` reads
// entry-12+0x10 = entry+4, which is the one ordinary argument slot, and the
// `RET 0x4` on both return sites consumes the return address plus that word. The
// frame therefore balances with exactly one stack argument, and the walk is
// corroborated by the two return sites agreeing on `C2 04 00` and by nothing in the
// 46 instructions ever touching a displacement that would be a second slot.
//
//   entry+4   the key word. Compared as a full 32-bit value against each element's
//             +0xa8 at 0x00fa55b8, and nowhere else.
//
// WHAT THE COUNT IS, and why it is not written as a division. 0x2fa0be83 is 799063683
// and 0x2fa0be83 * 0xac == 2^37 + 4 exactly, so the six instructions at
// 0x00fa5590..0x00fa559f are the compiler's signed-division expansion for a divisor
// of 0xac, correction included. For a non-negative span they equal span / 0xac; for a
// NEGATIVE span they do not, and the difference is not subtle: `SHR EAX,0x1f` puts
// 0xffffffff in EAX for a negative quotient and `ADD EAX,EDX` then subtracts one
// more, so the sequence returns floor(0x2fa0be83*span/2^37) - 1. Span -0xac yields
// -3 where C yields -1; span -0xac*256 yields -258 where C yields -256. The helper
// in the header transcribes the six instructions rather than the division, and the
// model test drives both a negative span and a table of positive ones. Ghidra's
// decompilation of this VA writes the whole thing as `(end - begin) / 0xac` with
// `iVar3` as the loop bound, which agrees for every non-negative span and disagrees
// for every negative one; the listing is followed here.
//
// GLOBALS: none. No instruction in the 46 names a data-segment address, and the
// model declares none.
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and the listing has no
// register- or memory-operand transfer. This body sits at slot +0x68 of the class
// table whose address is in the header, read out of the image and matching the xref
// from 0x01490c50; that association is recorded for the integrator and is not
// modelled, because the body never reads a word at the receiver's +0x00 and no slot
// boundary is declared anywhere in this package.
//
// RETURN WORD. The two exits write AL only -- `XOR AL,AL` at 0x00fa55c9 and
// `MOV AL,0x1` at 0x00fa55fe -- and no path writes the other three bytes of EAX, so
// the returned value is one byte wide and the declared type is std::uint8_t. What
// those three dead bytes hold is still machine fact, and it is the only place the
// count's negative-domain behaviour can escape into the caller, so it is modelled as
// instrumentation rather than as the return value:
//
//   not found          EAX = count, then XOR AL,AL  ->  count & 0xffffff00
//   found, no shift    EAX = found + 0xac, then MOV AL,0x1
//   found, shift       EAX = 0x00f9f770's return word, then MOV AL,0x1
//
// The model's own return value is the low byte, which is the whole of what the
// declared 1-byte type promises, and dead_return_high_bits() publishes the rest for
// the model test to assert. It is not a machine global and it is not part of the
// machine's observable surface; it is the same kind of instrumentation the
// reference package used for a try-level word, and the header says so.

#include "swarm_w1_00fa5580_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00fa5580 {
namespace {

// Model instrumentation: bits 8..31 of EAX at the last return, and the low byte
// alongside it so the test can read the whole word the machine leaves. See the
// RETURN WORD note above. It has to live at namespace scope rather than as a local
// because the value is published to the test and nothing else reads it, and a local
// that is written and never read is a warning under -Wall.
std::uint32_t g_dead_return_word = 0;

}  // namespace

std::uint32_t dead_return_word() { return g_dead_return_word; }

extern "C" std::uint8_t PKG_SWARM_W1_00FA5580_THISCALL re_00fa5580(Receiver* receiver,
                                                                  Word key) {
  // 00fa5582  MOV ESI,ECX
  //
  // ESI is the receiver alias and every receiver access below goes through it; ECX
  // is then reused as the loop index, which is why the machine-derived receiver
  // record names register ECX with shape R-ALIAS. The two receiver words are reached
  // as DISPLACEMENTS into an opaque byte run: the record enumerates offsets
  // [0x798, 0x79c] and is bounds_only, so it says where the body was seen reaching
  // and not which member is which, and no member is named for either of them.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00fa5584  MOV EDX,dword ptr [ESI + 0x79c]
  // 00fa558a  SUB EDX,dword ptr [ESI + 0x798]
  //
  // Two independent loads, and their 32-bit difference. Both are re-read below; the
  // model reads each once, which is not a claim that the machine reads each once but
  // a statement that the second reads are not separable from inside the body: nothing
  // this body calls writes the receiver, so no interleaving can be observed between
  // the two reads. The subtraction is done on the addresses, which is the same
  // 32-bit arithmetic as the machine's SUB on the two loaded words.
  Element* const upper = *reinterpret_cast<Element* const*>(self + 0x79c);
  Element* const lower = *reinterpret_cast<Element* const*>(self + 0x798);
  const std::int32_t span = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(upper)) -
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(lower)));

  // 00fa5590..00fa559f -- the count, transcribed instruction by instruction in the
  // header. This is a signed result and it is NOT (upper - lower) / 0xac; see the
  // note above the model.
  const std::int32_t count = element_count_from_span(span);

  // 00fa55a1  XOR ECX,ECX
  std::int32_t index = 0;

  // 00fa55a4  TEST EAX,EAX
  // 00fa55a6  JLE 0x00fa55c7
  //
  // A signed `<= 0` test on the count, not `== 0` and not unsigned. It is what keeps
  // the search from touching a single element when the array is empty, and it is
  // also the whole of the negative-span story: a negative count cannot be produced
  // by a well-formed pair of pointers, but the two words are independent loads, so
  // the model keeps the guard the machine has rather than assuming it cannot fire.
  bool found = false;
  if (count > 0) {
    // 00fa55a8  MOV EDI,dword ptr [ESI + 0x798]
    //
    // begin, loaded a second time (0x00fa558a read the same word to form the span).
    //
    // 00fa55ae  MOV EBX,dword ptr [ESP + 0x10]
    //
    // The key word, the single ordinary argument at entry+4.
    //
    // 00fa55b2  LEA EDX,[EDI + 0xa8]
    // 00fa55b8  CMP dword ptr [EDX],EBX
    // 00fa55ba  JZ 0x00fa55cf
    //
    // The compared word is at the ELEMENT's own displacement 0xa8, one past the
    // element's first 0xa8 bytes. It is read through a pointer: the model reads
    // `*(word_at(element_at(begin, index), 0xa8))`, two levels down from the
    // receiver, and a model that read the same offset on the receiver, or on the
    // element's first word, would be reading a different object. The compare is a
    // full 32-bit equality on the argument word, so no widening or masking happens
    // anywhere on this path.
    //
    // 00fa55bc  INC ECX
    // 00fa55bd  ADD EDX,0xac
    // 00fa55c3  CMP ECX,EAX
    // 00fa55c5  JL 0x00fa55b8
    //
    // The loop bound is a SIGNED `JL` against the same count, and it is tested after
    // the increment, so the scan visits indices 0 .. count-1 and no further. The
    // cursor advance by 0xac and the index advance by one are two views of the same
    // step: the machine keeps the element address in EDX and the count of steps in
    // ECX, and the model keeps the index and recomputes the address.
    for (;;) {
      if (*word_at(element_at(lower, index), 0xa8) == key) {
        found = true;
        break;
      }
      ++index;
      if (index >= count) {
        break;
      }
    }
  }

  if (!found) {
    // 00fa55c7  POP EDI
    // 00fa55c8  POP ESI
    // 00fa55c9  XOR AL,AL
    // 00fa55cb  POP EBX
    // 00fa55cc  RET 0x4
    //
    // EAX holds the count here, and only AL is cleared, so the machine leaves
    // count & 0xffffff00 in the return register. That is the one observable
    // difference between the six count instructions and a C division, and the model
    // records it; the returned byte is 0 either way.
    g_dead_return_word = static_cast<std::uint32_t>(count) & kReturnHighBytesMask;
    return 0;
  }

  // 00fa55cf  MOV EDX,dword ptr [ESI + 0x79c]
  //
  // The upper word, read again. It is the array's limit for the shift below and it
  // is re-loaded rather than reused, so the model re-loads it too; see the note at
  // the top of the body on why the two reads are not separable here.
  Element* const limit = *reinterpret_cast<Element* const*>(self + 0x79c);

  // 00fa55d5  IMUL ECX,ECX,0xac
  // 00fa55db  ADD ECX,EDI
  //
  // The matched element: the loop index scaled by the 0xac stride, added to begin.
  Element* const source = element_at(lower, index);

  // 00fa55dd  LEA EAX,[ECX + 0xac]
  //
  // Its successor, and the shift's destination. The address is formed, never
  // dereferenced, on this path.
  Element* const destination = reinterpret_cast<Element*>(
      reinterpret_cast<std::uintptr_t>(source) + 0xac);

  // 00fa55e3  CMP EAX,EDX
  // 00fa55e5  JNC 0x00fa55f2
  //
  // An UNSIGNED `>=` on two addresses, i.e. "skip the shift when the successor is
  // not strictly below the limit". Equality is the case that matters: erasing the
  // LAST live element leaves destination == limit, there is nothing after it to move
  // down, and the call must not run -- but the decrement below still happens. The
  // model compares the addresses as std::uint32_t so the comparison is the machine's
  // JNC and not a signed one, which is the distinction a reconstruction that wrote
  // `destination < limit` on pointers would lose only above 0x80000000 and which is
  // therefore reproduced rather than argued.
  if (static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(destination)) <
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(limit))) {
    // 00fa55e7  PUSH ECX
    // 00fa55e8  PUSH EDX
    // 00fa55e9  PUSH EAX
    // 00fa55ea  CALL 0x00f9f770
    // 00fa55ef  ADD ESP,0xc
    //
    // Three words, right to left, so the callee sees (successor, limit, matched) --
    // the element after the match, the array's limit, and the matched element. That
    // order is not a guess: it is fixed by 0x00f9f770's own three frame reads, which
    // the header transcribes instruction by instruction (0x00f9f771 takes the second
    // word, 0x00f9f776 the first, 0x00f9f77f the third), and so is the copy
    // direction, which 0x00f9f620's own body fixes as "the stack word is read, the
    // ECX receiver is written". The callee therefore copies the element after the
    // match onto the matched element, then the one after that onto the next, and so
    // on up to the limit: the tail moves down by one 0xac slot and the gap closes.
    // The callee is cdecl and the body drops the three words itself at 0x00fa55ef.
    //
    // The EAX the callee returns is dead for the array but not for the return word:
    // nothing writes EAX between the call and 0x00fa55fe, so the callee's own return
    // value is what the caller sees in bits 8..31. The model records it and the test
    // poisons it, which is how a reconstruction that ignored the return value
    // entirely would be caught.
    g_dead_return_word = static_cast<std::uint32_t>(
                            reinterpret_cast<std::uintptr_t>(
                                array_shift_tail_down_00f9f770(destination, limit, source))) &
                        kReturnHighBytesMask;
  } else {
    // No call: EAX is still the successor's address from 0x00fa55dd.
    g_dead_return_word = static_cast<std::uint32_t>(
                             reinterpret_cast<std::uintptr_t>(destination)) &
                         kReturnHighBytesMask;
  }

  // 00fa55f2  ADD dword ptr [ESI + 0x79c],0xffffff54
  //
  // The upper word minus 0xac, in 32-bit arithmetic on the loaded word, and it runs
  // on BOTH arms -- including the arm where the shift was skipped, where it is the
  // only mutation of the array this body makes. It also runs after the call, so the
  // callee is handed the limit as it stood before the removal; the model test has
  // the callee's observer read the receiver and assert exactly that.
  *reinterpret_cast<Word*>(self + 0x79c) += static_cast<Word>(-0xac);

  // 00fa55fc  POP EDI
  // 00fa55fd  POP ESI
  // 00fa55fe  MOV AL,0x1
  // 00fa5600  POP EBX
  // 00fa5601  RET 0x4
  //
  // Again only AL is written. The high half recorded above is left in place, so the
  // published dead word has bit 0 clear; the test reads both halves from one place.
  g_dead_return_word |= 1u;
  return 1;
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00fa5580
