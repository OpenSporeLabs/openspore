// PKG-DFW-009817C0 -- VA 0x009817c0
// UTFWin cluster (SPORE/SporeBin/SporeApp.exe, 3.1.0.22)
//
// Machine listing, 17 instructions, body 0x009817c0..0x009817f3 inclusive
// (Ghidra body_start 0x009817c0, body_end 0x009817f3, body_span_bytes 52;
// the last RET is 3 bytes at 0x009817f1, so the recovered span runs to 0x009817f3).
// Every line of the model below is annotated with the instruction it comes from.
//
//   009817c0  MOV EAX,dword ptr [ESP + 0x4]
//   009817c4  CMP EAX,0xeec58382
//   009817c9  JZ 0x009817e5
//   009817cb  CMP EAX,0xeef3af8c
//   009817d0  JZ 0x009817db
//   009817d2  MOV dword ptr [ESP + 0x4],EAX
//   009817d6  JMP 0x00951240
//   009817db  TEST ECX,ECX
//   009817dd  JZ 0x009817ef
//   009817df  LEA EAX,[ECX + 0xc]
//   009817e2  RET 0x4
//   009817e5  TEST ECX,ECX
//   009817e7  JZ 0x009817ef
//   009817e9  LEA EAX,[ECX + 0x4]
//   009817ec  RET 0x4
//   009817ef  XOR EAX,EAX
//   009817f1  RET 0x4
//
// WHAT THE RECORD CALLS THIS, AND WHAT IT IS
//
// The queue record and the Spore-ModAPI import both name this address
// UTFWin::ScrollbarDrawable::SetImage. The body is not a setter. It takes one
// 32-bit comparison key and a receiver address, and returns the address of one
// of that receiver's words or null. It writes nothing, it never dereferences the
// receiver, and it is never passed an image pointer. A setter that stored an
// image into a scrollbar would have to write through the receiver, and no
// reading of these 17 instructions does. The entry symbol below therefore embeds
// the record's last name component purely so the source span binds to this VA,
// and the contradiction is carried in the sidecar as
// sdk-name-is-not-the-observed-behaviour. No semantic claim is made that this
// function is a SetImage.
//
// The Ghidra decompilation of this address is also wrong about the same thing and
// is not used: it renders the argument as `IScrollbarDrawable *this`, compares
// THAT pointer against 0xeec58382 and 0xeef3af8c, and discards the EAX results of
// both LEAs and the XOR. Everything below is read from the disassembly.
//
// CALLING CONVENTION -- which half the machine proves and which half it does not
//
// The persisted abi record for this target says __thiscall, and this model uses
// it. Two separate facts support it and one is weaker than the other, so they are
// stated apart rather than merged:
//
//   PROVEN. All three exits are RET 0x4, so four bytes of stack are popped by the
//   callee, and the body reads exactly one ordinary word, at entry_ESP+0x4. The
//   machine-derived record agrees on that half with confidence SUPPORTED:
//   cleanup.bytes 4, cleanup.side "callee", evidence "ret 0x4", bytes 4. A
//   caller-cleaned reading would need RET 0x0 or RET 0x8 and is excluded.
//
//   NOT PROVEN. The machine-derived record ABSTAINED on the receiver. Its own
//   words: "receiver_not_determinable: ecx_address_taken_without_memory_access",
//   "ecx_address_taken_without_memory_access: LEA takes ECX's address without any
//   memory access through it", verdict PARTIAL, candidate_conventions
//   [__stdcall, __thiscall], calling_convention null, confidence UNKNOWN. That
//   is correct of the tool and true of this body: the only two uses of ECX here
//   are the TEST ECX,ECX null guards and the two LEA address computations, so no
//   memory is ever accessed through the receiver and there is nothing for a
//   receiver rule to key on. __stdcall and __thiscall are indistinguishable on
//   the stack-cleanup evidence alone.
//
//   FOLLOWED. __thiscall is the persisted record's own claim, and ECX is used as
//   the object pointer throughout: it is compared against zero as a whole object
//   (0x009817db, 0x009817e5) and offset by whole-object displacements (0x009817df,
//   0x009817e9), never as a stack address or a value. Two this-adjusting thunks
//   outside this body, 0x00969b40 (SUB ECX,0x4; JMP 0x009817c0) and 0x00969b50
//   (SUB ECX,0xc; JMP 0x009817c0), reach it with ECX already biased by exactly
//   these displacements, which is what a member-address resolver over a base
//   class would look like. That corroborates the shape; it does not name a class.
//
// RETURN WORD -- an unresolved tension between the two machine records, stated
//
// Both machine records agree EAX is written on every path and that the word is 4
// bytes wide. They disagree about its CATEGORY. The persisted abi record says
// return_type "void*"; the machine-derived record says return_semantics
// "integral_in_EAX". The header declares void* because that is the token the
// queue record publishes and because the values EAX holds on this body are
// addresses -- the receiver itself, the receiver offset by a proven displacement,
// or zero. The disagreement is real and is not resolved here; it is recorded in
// the sidecar as return-type-category-conflict.
//
// The body performs no memory access through the receiver on any path: the two
// LEAs take its address and add a constant, and nothing is loaded or stored
// through it. So no member name, no member type and no pointee type is declared
// anywhere in this package, and the displacements are written in decimal so that
// they cannot be misread as declared field offsets.

#include "dfw_009817c0_types.hpp"

namespace openspore::reconstruction::pkg_dfw_009817c0 {
namespace {

// The argument slot, as the listing sees it: one 4-byte cell at entry_ESP+0x4.
//
// The body reads that cell once and writes it back once, so the model keeps a
// named local standing for the cell and a second local standing for the EAX copy
// of it, rather than folding the round trip into a plain parameter read. It is a
// model of a stack slot, not a claim that the original had a struct, and nothing
// in it is a declared field: no record for this target enumerates any layout.

// 0x009817df  LEA EAX,[ECX + 0xc]   and   0x009817e9  LEA EAX,[ECX + 0x4]
//
// The only pointer arithmetic in the body. LEA takes an address; it does not
// dereference, so no member is read, written or named, which is exactly what the
// machine-derived record reports when it abstains on the receiver
// ("LEA takes ECX's address without any memory access through it"). Nothing here
// types the words these addresses point at.
//
// The displacements are decimal on purpose. A hexadecimal displacement written
// in the source reads as a declared field offset, and no record for this target
// enumerates a receiver layout or names a member, so there is nothing to declare
// an offset against.
void* offset_address(void* base, std::size_t displacement) {
  return static_cast<void*>(static_cast<unsigned char*>(base) + displacement);
}

// 0x009817ef  XOR EAX,EAX
//
// The one shared null result, reached from both null guards. Declared once so
// the single instruction is stated once and both arms name it.
void* null_word() { return nullptr; }

}  // namespace

PKG_DFW_009817C0_MODEL_BEGIN
extern "C" void* PKG_DFW_009817C0_THISCALL dfw_009817c0_SetImage(void* receiver, Word key) {
  // 0x009817c0  MOV EAX,dword ptr [ESP + 0x4]
  //
  // The only argument the body reads, and the only word it ever writes (see
  // 0x009817d2 below). It goes into EAX and is used from there as a comparison
  // key -- never masked, never widened, never used as an index.
  Word slot_word = key;
  const Word observed = slot_word;

  // 0x009817c4  CMP EAX,0xeec58382
  // 0x009817c9  JZ 0x009817e5
  //
  // First key tested, and the branch leaves the flat comparison chain for the
  // arm at 0x009817e5. The immediate is written literally rather than through a
  // named constant so that a source constant and the machine listing are
  // compared against each other rather than being the same object twice.
  if (observed == 0xeec58382u) {
    // 0x009817e5  TEST ECX,ECX
    // 0x009817e7  JZ 0x009817ef
    //
    // The receiver is null-guarded as a whole object, not as a field, and the
    // guard is what turns a null receiver into the shared null result instead of
    // the address 0x00000004.
    if (receiver == nullptr) {
      // 0x009817ef  XOR EAX,EAX
      // 0x009817f1  RET 0x4
      return null_word();
    }
    // 0x009817e9  LEA EAX,[ECX + 0x4]
    // 0x009817ec  RET 0x4
    //
    // The address receiver + 4. It is returned, never dereferenced, and the
    // 0x009817ec terminator pops the same four bytes the 0x009817c0 read
    // belongs to.
    return offset_address(receiver, 4);
  }

  // 0x009817cb  CMP EAX,0xeef3af8c
  // 0x009817d0  JZ 0x009817db
  //
  // Second key tested, branching to the arm at 0x009817db. It is the only key
  // and the only displacement 0x0c that exist in this body: the tail-call target
  // 0x00951240 knows neither, which is why the tail call cannot be treated as an
  // opaque fallback here.
  if (observed == 0xeef3af8cu) {
    // 0x009817db  TEST ECX,ECX
    // 0x009817dd  JZ 0x009817ef
    if (receiver == nullptr) {
      // 0x009817ef  XOR EAX,EAX
      // 0x009817f1  RET 0x4
      return null_word();
    }
    // 0x009817df  LEA EAX,[ECX + 0xc]
    // 0x009817e2  RET 0x4
    //
    // The address receiver + 12.
    return offset_address(receiver, 12);
  }

  // 0x009817d2  MOV dword ptr [ESP + 0x4],EAX
  //
  // The only store in the body, and it writes EAX into the very slot EAX was
  // loaded from at 0x009817c0. Nothing on this path writes EAX between the load
  // and this store, so the value stored equals the value read: the word the tail
  // callee reads at its own entry_ESP+0x4 is the key, unchanged, and the
  // receiver is untouched in ECX.
  //
  // Honest limit, stated rather than hidden: this store targets the CALLER's
  // argument slot, which lies outside the interface this model exposes, so the
  // test cannot watch the slot itself. What the test can watch, and does, is the
  // value the callee receives -- the store's only observable consequence.
  slot_word = observed;

  // 0x009817d6  JMP 0x00951240
  //
  // A tail call, not a CALL: no return address is pushed, no stack is adjusted,
  // and the argument slot is left exactly as the callee-cleaned RET 0x4 at
  // 0x009817ec and 0x009817e2 expect it. This is the only outgoing transfer the
  // body has, and the xref export records it (0x009817d6 -> 0x00951240,
  // direct-call), so the two machine sources agree on the callee set.
  //
  // Every key this body does not handle locally is delegated with the same
  // receiver and the same key. That is the whole of the third path; the callee's
  // own table is stated in this package's header, transcribed from its live
  // listing, and is exercised directly by the test.
  return dfw_009817c0_resolve_00951240(receiver, slot_word);
}
PKG_DFW_009817C0_MODEL_END

}  // namespace openspore::reconstruction::pkg_dfw_009817c0
