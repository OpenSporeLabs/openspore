// PKG-PROLIST-WRITE-WAVE16 -- VA 0x006a1540
// App::PropertyList::Write
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 74 instructions, body 0x006a1540..0x006a15f5 inclusive
// (live Ghidra disassemble_function, body_end 0x006a15f5). Every line of the
// reconstruction below carries the instruction it comes from, so the listing
// and this file can be compared without leaving it.
//
// ABI, machine-derived: __thiscall. The receiver arrives in ECX and is aliased
// into ESI at 0x006a1548 (MOV ESI,ECX). The single stack dword is read at
// 0x006a1543 with MOV EBP,dword ptr [ESP + 0x10]; three pushes precede it
// (PUSH ECX / PUSH EBX / PUSH EBP), so [ESP+0x10] is entry_ESP+0x4, the one
// ordinary argument. EBP is that argument, not a frame pointer: there is no
// MOV EBP,ESP in the body. The body ends in RET 0x4 at 0x006a15f3, so the
// callee pops that dword; cdecl and fastcall are both excluded by it.
//
// The direct transfers in the body are exactly three, and all three are calls:
//   0x006a156f  CALL 0x0093aa70   write one 4-byte word
//   0x006a15b8  CALL 0x0093aa70   write one 4-byte word (an entry id)
//   0x006a15d0  CALL 0x00693390   write one entry payload
// There is no tail call and no indirect transfer of any kind in the body.
//
// The three stack words that carry the count and the two words that carry the
// entry id are not locals in the abstract sense: the body stores them into its
// own spill slots and passes their addresses. The count word goes to the slot
// that held the saved ECX (entry_ESP-0x4) and the id word to the slot that held
// the saved ESI (entry_ESP-0x10). Both addresses are reproduced below by
// taking the address of an ordinary local; the address is unobservable, only
// the value read by the callee matters.
//
// The loop bound is evaluated TWICE, and that is load-bearing: the first
// quotient is what gets written to the stream, the second quotient is what
// bounds the loop, and the two are separated by the first call. This body keeps
// them separate rather than reusing one variable.

#include "proplist_write_006a1540.hpp"

namespace openspore::reconstruction::pkg_proplist_write_wave16 {

namespace {

// Defaults that make the reconstruction inert until a test installs ports.
bool default_write_words(OpaqueStream *, const Word *, Word, Word) {
  return false;
}

bool default_write_property(OpaqueStream *, std::uint8_t *, Word) {
  return false;
}

} // namespace

NativePorts &proplist_write_native_ports() {
  static NativePorts ports{default_write_words, default_write_property};
  return ports;
}

#if defined(_MSC_VER)
#define PROPLIST_WRITE_THISCALL __thiscall
#else
#define PROPLIST_WRITE_THISCALL __attribute__((thiscall))
#endif

extern "C" bool PROPLIST_WRITE_THISCALL
write_006a1540(OpaquePropertyList *list, OpaqueStream *stream) {
  // 0x006a1540  PUSH ECX
  // 0x006a1541  PUSH EBX
  // 0x006a1542  PUSH EBP
  // 0x006a1543  MOV EBP,dword ptr [ESP + 0x10]   -> entry_ESP+0x4, `stream`
  // 0x006a1547  PUSH ESI
  // 0x006a1548  MOV ESI,ECX                      -> the receiver alias
  //
  // The stream is never dereferenced anywhere in the 74 instructions; it is only
  // ever pushed as the first argument of the three calls.
  //
  // 0x006a154a  MOV ECX,dword ptr [ESI + 0x1c]
  // 0x006a154d  SUB ECX,dword ptr [ESI + 0x18]   -> signed byte span
  // 0x006a1550  MOV EAX,0x2aaaaaab
  // 0x006a1555  IMUL ECX
  // 0x006a1557  SAR EDX,0x2
  // 0x006a155c  MOV EAX,EDX
  // 0x006a1564  SHR EAX,0x1f
  // 0x006a1568  ADD EAX,EDX
  //
  // 0x2AAAAAAB with a two-bit arithmetic shift is the signed-division-by-0x18
  // sequence: one element per 0x18 bytes, matching the 0x006a15e2 stride. The
  // result is a signed 32-bit count and it is the value written to the stream.
  const std::int32_t written_count = property_list_entry_count(list);
  Word count_word = static_cast<Word>(written_count);

  // 0x006a155a  PUSH 0x0            fourth argument
  // 0x006a155e  PUSH 0x1            third argument, the element count
  // 0x006a1560  LEA ECX,[ESP + 0x14]
  // 0x006a1567  PUSH ECX             second argument, &count_word
  // 0x006a156a  PUSH EBP             first argument, `stream`
  // 0x006a156b  MOV dword ptr [ESP + 0x1c],EAX   final quotient -> count_word
  // 0x006a156f  CALL 0x0093aa70
  // 0x006a158d  ADD ESP,0x10
  //
  // Five dwords leave the stack accounting for the call (four pushed plus the
  // return address) and four are removed here, so 0x0093aa70 pops nothing. The
  // result is a one-byte bool; it is captured into the same byte the machine
  // keeps it in, BL.
  NativePorts &ports = proplist_write_native_ports();
  bool success = ports.write_words_0093aa70(stream, &count_word, 1, 0);

  // 0x006a1574  MOV ECX,dword ptr [ESI + 0x1c]
  // 0x006a1577  SUB ECX,dword ptr [ESI + 0x18]
  // 0x006a157a  MOV BL,AL                     BL now holds the count verdict
  // 0x006a157c..0x006a158b                       the same divide, recomputed
  // 0x006a1590  TEST EAX,EAX
  // 0x006a1592  JLE 0x006a15ed
  //
  // The span is re-read from the receiver after the count has been handed to
  // the stream, and re-divided. Nothing in this body can make the two quotients
  // differ -- the only call between them writes to a stream, not to the
  // receiver -- but the machine evaluates it twice and so does this body.
  //
  // 0x006a1594  PUSH EDI   and 0x006a1595  XOR EDI,EDI   the element offset
  // 0x006a1597  MOV dword ptr [ESP + 0x18],EAX            the loop counter
  // 0x006a159b  JMP 0x006a15a0                            loop preheader
  //
  // The loop carries TWO induction variables, and so does the machine: EDI is a
  // byte offset that steps by 0x18 (0x006a15e2) while the stack word is an
  // independent countdown (0x006a15e5 SUB dword ptr [ESP + 0x18],0x1, exited by
  // 0x006a15ea JNZ). They are not interchangeable: the countdown, not the
  // offset, decides when the loop ends, so a container mutated from inside the
  // loop would not change the iteration count. The JLE above is a SIGNED test,
  // so a negative quotient skips the loop just as a zero quotient does.
  const std::int32_t iterations = property_list_entry_count(list);
  if (iterations > 0) {
    for (std::int32_t remaining = iterations, offset = 0; remaining != 0;
         --remaining, offset += 0x18) {
      // 0x006a15a0  TEST BL,BL
      // 0x006a15a2  JZ 0x006a15e0
      //
      // The loop does NOT abort on failure. It jumps to the same block the
      // loop tail falls through to, zeroes BL again, and keeps counting down.
      // Once a write has failed, every remaining iteration performs no stream
      // traffic at all: the id of the next entry is not even read.
      if (!success) {
        // 0x006a15e0  XOR BL,BL   (already zero on this path)
        success = false;
        // 0x006a15e2  ADD EDI,0x18
        // 0x006a15e5  SUB dword ptr [ESP + 0x18],0x1
        // 0x006a15ea  JNZ 0x006a15a0
        continue;
      }

      // 0x006a15a4  MOV EDX,dword ptr [ESI + 0x18]   the range base, re-read
      // 0x006a15a7  MOV EAX,dword ptr [EDI + EDX]     the entry word at +0x00
      const OpaquePropertyEntry *const entry = property_list_entry_at(list, offset);
      Word id_word = entry->word_00;

      // 0x006a15aa  PUSH 0x0
      // 0x006a15ac  PUSH 0x1
      // 0x006a15ae  LEA ECX,[ESP + 0x18]
      // 0x006a15b2  PUSH ECX
      // 0x006a15b3  PUSH EBP
      // 0x006a15b4  MOV dword ptr [ESP + 0x20],EAX
      // 0x006a15b8  CALL 0x0093aa70
      // 0x006a15bd  ADD ESP,0x10
      success = ports.write_words_0093aa70(stream, &id_word, 1, 0);

      // 0x006a15c0  TEST AL,AL
      // 0x006a15c2  JZ 0x006a15e0
      //
      // A failed id write skips the payload write for this entry and moves on
      // to the next iteration, which will also do nothing because BL is now
      // zero.
      if (!success) {
        continue;
      }

      // 0x006a15c4  MOV EAX,dword ptr [ESI + 0x18]   the base, re-read again
      // 0x006a15c7  ADD EAX,EDI
      // 0x006a15c9  PUSH 0x0                          third argument
      // 0x006a15cb  ADD EAX,0x4                       entry + 0x4
      // 0x006a15ce  PUSH EAX                          second argument
      // 0x006a15cf  PUSH EBP                          first argument, `stream`
      // 0x006a15d0  CALL 0x00693390
      // 0x006a15d5  ADD ESP,0xc
      //
      // Four dwords leave the stack for this call (three pushed plus the return
      // address) and three are removed, so 0x00693390 pops exactly one dword.
      success = ports.write_property_00693390(
          stream, property_entry_payload(property_list_entry_at(list, offset)), 0);

      // 0x006a15d8  TEST AL,AL
      // 0x006a15da  JZ 0x006a15e0
      // 0x006a15dc  MOV BL,0x1                        the only place BL is set
      // 0x006a15de  JMP 0x006a15e2
      //
      // A payload failure lands on the same 0x006a15e0 block, so the remaining
      // entries are skipped and the verdict stays false.
    }
  }

  // 0x006a15ec  POP EDI                     only on the loop path
  // 0x006a15ed  POP ESI
  // 0x006a15ee  POP EBP
  // 0x006a15ef  MOV AL,BL                   the verdict, as a one-byte bool
  // 0x006a15f1  POP EBX
  // 0x006a15f2  POP ECX
  // 0x006a15f3  RET 0x4
  //
  // The count<=0 path (0x006a1592 JLE 0x006a15ed) joins here without having
  // pushed EDI, which is why the pop is inside the guarded block above. Only AL
  // is written on the way out; the upper three bytes of EAX are whatever the
  // last division left there, which is why the return type is a byte-wide bool.
  return success;
}

#undef PROPLIST_WRITE_THISCALL

} // namespace openspore::reconstruction::pkg_proplist_write_wave16
