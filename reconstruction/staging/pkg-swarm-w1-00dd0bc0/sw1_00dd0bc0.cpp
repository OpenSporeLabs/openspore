// PKG-SWARM-W1-00DD0BC0 -- VA 0x00dd0bc0
// The scalar deleting destructor at 0x00dd0bc0
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// The complete body: 14 instructions, 0x00dd0bc0..0x00dd0bf1 inclusive
// (ghidra_function.body_start 0x00dd0bc0, body_end 0x00dd0bf1, size_bytes 50), and
// ten 0xcc bytes of INT3 padding after it, so nothing falls through out of it.
//
//   00dd0bc0  PUSH ESI
//   00dd0bc1  MOV ESI,ECX
//   00dd0bc3  MOV dword ptr [ESI],0x147c9f8
//   00dd0bc9  MOV dword ptr [ESI + 0x10],0x147c9e8
//   00dd0bd0  MOV dword ptr [ESI + 0x14],0x147cc78
//   00dd0bd7  CALL 0x00642190
//   00dd0bdc  TEST byte ptr [ESP + 0x8],0x1
//   00dd0be1  JZ 0x00dd0bec
//   00dd0be3  PUSH ESI
//   00dd0be4  CALL 0x00f47380
//   00dd0be9  ADD ESP,0x4
//   00dd0bec  MOV EAX,ESI
//   00dd0bee  POP ESI
//   00dd0bef  RET 0x4
//
// The listing above was re-derived from the image bytes for this package -- objdump
// over the 0x32 bytes at file offset 0x9cffc0 (RVA 0x9d0bc0) -- rather than taken
// on trust. It reproduces the 14 committed instructions at the same addresses with
// the same lengths, the same two call targets, the same branch target and the same
// operand displacements, so nothing in the model below rests on a difference.
//
// The whole body in one sentence: store three dispatch words into the receiver at
// 0x00, 0x10 and 0x14, run the base destructor, and if the low bit of the flag word
// is set hand the receiver to the deallocation port -- then return the receiver.
//
// FRAME, resolved once against the entry ESP so that the one displacement below is a
// fact and not a guess. Entry ESP is 0 in the walk. 0x00dd0bc0's `PUSH ESI` makes it
// -4 and nothing else touches ESP until the 0x00f47380 call, so 0x00dd0bdc's
// `[ESP + 0x8]` is -4 + 8 = entry+4, which is the first ordinary argument slot;
// `RET 0x4` then consumes the return address plus that one four-byte word and the
// walk ends at +4, which balances. Two independent agreements: the machine-derived
// ABI record enumerates exactly one ordinary stack slot at "entry_ESP+0x4" and
// reports `stack_cleanup_bytes: 4` with the callee as owner, and Ghidra types the
// same slot `Stack[0x4]:1`. The zero of the walk is corroborated a third time by
// 0x00642210, whose flag test carries the identical `[esp+0x8]` displacement from an
// identical one-instruction prologue (see the header).
//
// VIRTUAL DISPATCH: none, and none declared. abi_derived.dispatch records
// indirect_calls 0, call_offsets [] and vtable_shaped_loads 0, and all 14
// instructions are direct immediates or register moves. The three words this body
// stores ARE the object's dispatch words -- the table read at 0x0147c9f8 has this
// body at its own slot +0x00, and the tables read at 0x0147c9e8 and 0x0147cc78
// hold adjust-and-jump thunks that subtract exactly 0x10 and 0x14 and land here --
// but the body never READS one, so it performs no dispatch and this model declares
// no slot boundary and no member for any of the three.
//
// GLOBALS: three. The three immediates 0x147c9f8, 0x147c9e8 and 0x147cc78 are all
// data-segment addresses in this image (0x01300000..0x02000000), and they are the
// only data addresses the body names. No instruction reads any of them, and the
// body reads no data-segment location at all.

#include "sw1_00dd0bc0_types.hpp"

namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0 {
namespace {

// The three stored immediates, restated at namespace scope so the header's literals
// can be checked against the ones the instructions give, once, with a compile-time
// assertion instead of by eye. The three stores in the body below write the
// immediates as literals rather than by name, so that each store line reads exactly
// like the instruction it comes from; these three are what those literals are
// asserted equal to. 0x00dd0bc3, 0x00dd0bc9 and 0x00dd0bd0 are the instructions.
constexpr Word kStore00Value = 0x0147c9f8u;
constexpr Word kStore10Value = 0x0147c9e8u;
constexpr Word kStore14Value = 0x0147cc78u;

static_assert(kStore00Value == kObjectTableAt00, "0x00dd0bc3 stores 0x147c9f8 at +0x00");
static_assert(kStore10Value == kObjectTableAt10, "0x00dd0bc9 stores 0x147c9e8 at +0x10");
static_assert(kStore14Value == kObjectTableAt14, "0x00dd0bd0 stores 0x147cc78 at +0x14");

}  // namespace

extern "C" OpaqueSporepediaAsset* PKG_SWARM_W1_00DD0BC0_THISCALL re_00dd0bc0(
    OpaqueSporepediaAsset* receiver, std::uint8_t deleting_flag) {
  // 00dd0bc0  PUSH ESI
  // 00dd0bc1  MOV ESI,ECX
  //
  // ESI becomes the receiver alias and every one of the five remaining receiver
  // accesses in the body goes through it -- the three stores, the argument to the
  // deallocation port, and the returned word. ECX is not used again after this, which
  // is why the machine-derived receiver record reports register ECX with shape
  // R-ALIAS: the base register it saw the receiver in is not the base register the
  // listing's own memory operands name.
  //
  // The receiver is taken as a byte run and reached by displacement throughout. The
  // receiver record enumerates offsets [0, 16, 20] with bounds_only true, which says
  // where the body was seen reaching and not which member is which; three stores and
  // no reads cannot do better than that, so no member is named. Note also that this
  // body READS NOTHING from the receiver: there is no load in the 14 instructions.
  std::uint8_t* const self = reinterpret_cast<std::uint8_t*>(receiver);

  // 00dd0bc3  MOV dword ptr [ESI],0x147c9f8
  //
  // The first store. The table read at that address has this body's own address
  // (0x00dd0bc0) in its slot +0x00 and 0x00641340 in its slot +0x04, which is the
  // pair MSVC emits for a class's own destructor, so the word written here is the
  // receiver's primary dispatch word. That is a reading of the image, not a record.
  //
  // The displacement is written as NO offset at all, and that is deliberate: the
  // machine's own form for this store is `C7 06`, a zero displacement with no
  // `+0x00` operand to transcribe, so a `+ 0x00` written here would be a literal
  // the listing does not contain. The static_assert above ties the header's
  // kReceiverWord00Displacement to the immediate instead, and the header's
  // kReceiverWord00Displacement is 0x00.
  *word_at(self) = 0x0147c9f8u;

  // 00dd0bc9  MOV dword ptr [ESI + 0x10],0x147c9e8
  //
  // The second store, four bytes below the third. The table read at 0x0147c9e8 has
  // 0x00dd0bb0 at its slot +0x08, and 0x00dd0bb0 is `SUB ECX,0x10; JMP 0x00dd0bc0`
  // -- an adjust-and-jump thunk that subtracts exactly this displacement from the
  // receiver and lands on this body. So this is the dispatch word of a subobject at
  // receiver+0x10, and the two are related by the thunk's own immediate rather than
  // by anything this body does.
  *word_at(self + 0x10) = 0x0147c9e8u;

  // 00dd0bd0  MOV dword ptr [ESI + 0x14],0x147cc78
  //
  // The third store. The table read at 0x0147cc78 has 0x00dd0b40 at its slot +0x00,
  // and 0x00dd0b40 is `SUB ECX,0x14; JMP 0x00dd0bc0` -- the same adjusting thunk for
  // the subobject at receiver+0x14. 0x10 and 0x14 are adjacent dwords, one after the
  // other with nothing between them, which is why the static_assert above requires
  // them not to overlap.
  *word_at(self + 0x14) = 0x0147cc78u;

  // 00dd0bd7  CALL 0x00642190
  //
  // The base destructor, with the receiver left in ECX from 0x00dd0bc1 and no stack
  // argument pushed -- the instruction before it is a store, not a push. It is
  // __thiscall with nothing to clean up, which its own bytes fix: its last two
  // instructions are `POP ESI` (0x00642204) and `JMP 0x006412a0` (0x00642205), a
  // tail jump that cannot be popping a caller's argument. It returns to 0x00dd0bdc
  // and its return word is never looked at: the next instruction tests memory, and
  // the only register this body reads afterwards is ESI, which the callee does not
  // define.
  //
  // It runs on BOTH arms of the branch below, so the base destruction is not
  // conditional on the flag. That ordering is the machine's: stores first, then the
  // base destructor, then the deallocation -- the reverse of a source-level
  // destructor that calls the base first and then re-installs its own vptr.
  sporepedia_asset_destroy_00642190(receiver);

  // 00dd0bdc  TEST byte ptr [ESP + 0x8],0x1
  // 00dd0be1  JZ 0x00dd0bec
  //
  // The branch, and the only decision in the body. ESP is entry-4 here (the one
  // PUSH ESI and nothing else), so the operand is entry+4: the flag word, the single
  // ordinary argument. The test is a BYTE test against the immediate 0x01, so bit 0
  // of that byte is the only thing examined and every other bit of the four-byte slot
  // is ignored. Both facts are load-bearing for the model and both are tested against
  // inputs on which the alternatives disagree: 0x02, 0x100 and 0xfe must all take the
  // no-deallocation arm, and 0x03 and 0x101 must take the deallocation arm. A
  // reconstruction that tested the byte for non-zero, or that masked with 0x2, inverts
  // the answer on those inputs.
  if ((deleting_flag & kDeletingFlagMask) != 0) {
    // 00dd0be3  PUSH ESI
    // 00dd0be4  CALL 0x00f47380
    //
    // The receiver's own address, pushed as the single stack word. Not a pointer to
    // a member of it and not a pointer to a pointer: the machine pushes the aliased
    // receiver register itself, so the callee receives the object address and the
    // model's test asserts the address is exactly the receiver the caller handed in.
    //
    // 0x00f47380 is cdecl -- its terminator is a bare C3 at 0x00f47394 with no
    // immediate -- so the following instruction has to drop the word. Its own first
    // act is `MOV EAX,[esp+4]` and it null-checks that word, so passing a null
    // receiver is a no-op for the callee rather than a fault; that is a fact about
    // the callee and is asserted by nothing here.
    sporepedia_free_00f47380(reinterpret_cast<Word>(receiver));

    // 00dd0be9  ADD ESP,0x4
    //
    // The caller-side cleanup, four bytes for the word just pushed. It sits on the
    // deallocation arm only, which is what makes the branch at 0x00dd0be1 a real
    // stack-discipline branch and not merely a test.
  }
  // 00dd0be1's jump lands here when the bit is clear, and the deallocation arm falls
  // through into the same place. Both arms converge, so nothing after this point is
  // conditional.

  // 00dd0bec  MOV EAX,ESI
  //
  // The returned word is the receiver, on both arms, and this is the join point of
  // the body. ESI has not been written since 0x00dd0bc1 and the two calls cannot
  // define it, so the value is the receiver on every path out of this function. It
  // is not an accident of the deallocation arm: the instruction is after the label
  // both arms reach, so the non-deallocating arm returns the same pointer.
  return receiver;

  // 00dd0bee  POP ESI
  // 00dd0bef  RET 0x4
  //
  // The epilogue, expressed by the compiler rather than by hand: `return self` above
  // becomes MOV EAX,ESI / POP ESI / RET 0x4 under
  // __attribute__((thiscall)) on a function with one four-byte stack argument, and
  // the 0x4 is the flag word this body is required to pop. The model test measures
  // the stack balance across a raw call rather than asserting the convention.
}

}  // namespace openspore::reconstruction::pkg_swarm_w1_00dd0bc0
