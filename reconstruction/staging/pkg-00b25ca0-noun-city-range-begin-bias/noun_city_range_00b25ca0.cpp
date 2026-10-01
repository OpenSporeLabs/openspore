#include "noun_city_range_00b25ca0.hpp"

// The header undefines its convention macro, so it is respelled here; this is
// the same thiscall the entry declares.
#if defined(_MSC_VER)
#define PKG_00B25CA0_THISCALL __thiscall
#else
#define PKG_00B25CA0_THISCALL __attribute__((thiscall))
#endif

// 0x00b25ca0 FUN_00b25ca0 - a five-argument forwarder onto the noun projection
// callee 0x00b21340 whose only computation is a +4 bias on the returned
// pointer.
//
// Raw bytes 0x00b25ca0..0x00b25cc2 (34 bytes, eight instructions):
//     68 6a 81 8c 01     PUSH 0x018c816a
//     68 00 e5 b1 00     PUSH 0x00b1e500
//     68 c0 36 b2 00     PUSH 0x00b236c0
//     68 20 d4 d3 00     PUSH 0x00d3d420
//     68 80 10 b2 00     PUSH 0x00b21080
//     e8 82 b6 ff ff     CALL 0x00b21340
//     83 c0 04           ADD EAX,0x4
//     c3                 RET
//
// What the body does, in the order it does it:
//
//   1. It pushes five words and calls 0x00b21340. The five are IMMEDIATES
//      (opcode 0x68 on all five), not memory reads; four of them land on
//      instruction bytes in the image and the callee CALLs through them, and
//      the fifth is the key operand the callee compares against the
//      receiver's +0x9c word. Nothing here loads a value to push - that is why
//      the reconstruction passes the constants themselves and not
//      `*reinterpret_cast<...>(kArg1)` at each site.
//   2. It forwards ECX. The callee is thiscall (`MOV ESI,ECX` at 0x00b21346,
//      `RET 0x14` at 0x00b21407), and this body contains no write to ECX, so
//      the receiver arrives untouched. Two callers load it in explicitly
//      (0x00bf99bb and 0x00bf0b0b, both `MOV ECX,EAX` after a call to the
//      noun-manager accessor 0x00b3d300). The derived ABI record's
//      `receiver: false` describes this body alone - ECX is never READ here -
//      and is superseded, not silently dropped; see header note 3.
//   3. It biases the callee's pointer by +4 and returns it.
//
// The +4 IS A FIELD BIAS, NOT AN ARITHMETIC ACCIDENT. The callee returns a
// pointer to its own NounProjectionVector, whose `begin` member sits at +0x04
// (src/reconstruction/pkg11_sim_core/noun_projection.hpp pins that offset by
// static_assert). Adding 4 therefore yields the ADDRESS OF `begin`, so what
// comes back is a {begin, end} pair pointer and not a vector pointer. The
// callers read it that way: 0x00bf99c2/0x00bf99c4 load [EAX] and [EAX+4] and
// compare them, FUN_00bf0b00 walks `*piVar2` to `piVar2[1]` with a +4 stride,
// and the unbaised sibling FUN_00b25f40 reads the vector's own `+4`/`+8` for
// the same two words. That is why this function returns `NounRange*` and not
// the vector type.
//
// The bias is written as pointer arithmetic on the callee's result, which is
// what the machine's `ADD EAX,0x4` is: an unconditional add with no test. A
// null callee result therefore leaves 0x00000004 in EAX, and this
// reconstruction publishes that value rather than inventing a null check the
// body does not contain.
//
// NOT done here, and each omission is a boundary rather than an oversight:
//   * no null check on the receiver, on the callee result, or on the biased
//     pointer - the body has no branch with which to check any of them;
//   * no AddRef, no store, no release: the returned range is the callee's
//     borrowed storage and this body only moves the pointer;
//   * no name for the five immediates beyond their callee argument roles,
//     and no name for the receiver beyond an opaque 0xa0-byte extent - this
//     body's eight instructions establish neither;
//   * no SDK name for the function itself.

namespace openspore::reconstruction::pkg_00b25ca0_noun_city_range {

namespace detail {

// The noun projection callee 0x00b21340, as this body calls it: a hidden ECX
// receiver plus five stack words.
//
// A NOTE ON WHO POPS THE TWENTY BYTES, because it is a place where a compiler
// convention and the machine disagree in attribution but not in effect.
// Observed: the callee's last instruction is `RET 0x14` at 0x00b21407, so on
// the machine the CALLEE pops all twenty bytes of its arguments, and this
// body's own trailing `RET` at 0x00b25cc1 pops nothing but the return address.
// GCC's `__attribute__((thiscall))` on i386 attributes those same five pops to
// the CALLER instead, so the compiler-emitted sequence is `call; add $0x14,%esp;
// ret` where the machine has `call; ret`. The two agree on what ESP is when
// control reaches the instruction after this function, which is the only thing
// observable across this body's boundary; they differ only in which function's
// listing contains the `add`. This reconstruction therefore declares the
// callee thiscall and lets the toolchain make its own legal attribution - it
// does NOT hand-pop five words after the call to force the machine's split,
// because that would make the code depend on a convention detail and would
// double-pop under MSVC `__thiscall`, which pops callee-side like the binary.
// The model test measures ESP across the wrapper (group 4) precisely so that
// the choice of attribution is checked by measurement rather than trusted.
//
// The five words are typed as opaque 32-bit values rather than as the callee's
// callback signatures because establishing WHICH callback is the create, clear,
// add or filter role is the callee package's evidence, not this body's: all
// this body witnesses is that it passes five words and that the callee calls
// four of them and compares the fifth against the receiver's +0x9c word.
//
// Declared here, defined by the caller's link (src/, the promoted
// pkg11_sim_core noun projection) and by the model test, which substitutes a
// recording stub so the argument vector can be observed directly. Keeping the
// declaration local to this package is what lets the model test measure the
// five words instead of assuming them.
extern "C" NounRange* PKG_00B25CA0_THISCALL noun_projection_callee_00b21340(
    OpaqueNounProjection* receiver, std::uint32_t arg0, std::uint32_t arg1,
    std::uint32_t arg2, std::uint32_t arg3, std::uint32_t arg4);

}

NounRange* PKG_00B25CA0_THISCALL noun_city_range_00b25ca0(
    OpaqueNounProjection* receiver) {
  // 0x00b25ca0..0x00b25cb4 - five PUSH imm32, in the order the machine emits
  // them. A call pushes arguments right to left, so the order written here is
  // the REVERSE of the callee's argument order and each argument below names
  // its own slot: kArg1 is pushed last and lands in the first stack slot.
  //
  // The values are the immediates themselves. The body does not read through
  // them, so neither does this - dereferencing a constant here would be a
  // reconstruction that reads five words of memory the machine never touches.
  //
  // Nothing is read from `receiver` in this function. It is passed through to
  // the callee, which is the only thing that touches it; the parameter exists
  // because ECX is forwarded, not because this body uses it.
  // 0x00b25cbe  ADD EAX,0x4
  //
  // The callee returned a NounProjectionVector*; the machine adds 4 to the
  // pointer, landing on that vector's `begin` member at +0x04. What leaves this
  // function is therefore the address of a {begin, end} pair, which is the
  // shape every sampled caller reads.
  //
  // The bias is added in BYTES, by casting to a byte pointer first. `ADD
  // EAX,0x4` is a raw address add of four bytes; writing the same 4 as an
  // element index on an eight-byte struct would move the pointer by 32 bytes
  // and land nowhere near `begin`, so the cast is what makes this expression
  // mean what the instruction means.
  const std::uintptr_t biased =
      reinterpret_cast<std::uintptr_t>(
          detail::noun_projection_callee_00b21340(
              receiver,
              // 0x00b25cb4  PUSH 0x00b21080   -> callee argument slot 0
              kArg1CreateCallback,
              // 0x00b25caf  PUSH 0x00d3d420   -> callee argument slot 1
              kArg2ClearCallback,
              // 0x00b25caa  PUSH 0x00b236c0   -> callee argument slot 2
              kArg3FilterCallback,
              // 0x00b25ca5  PUSH 0x00b1e500   -> callee argument slot 3
              kArg4AddCallback,
              // 0x00b25ca0  PUSH 0x018c816a   -> callee argument slot 4
              kArg5KeyOperand)) +
      kBeginFieldBias;

  // kBeginFieldBias is the only claim about WHICH field that 4 reaches - see
  // the header's evidence note 5. The add is unconditional: with no branch in
  // the body there is nothing here that could decline to apply it.
  return reinterpret_cast<NounRange*>(biased);
}

}

#undef PKG_00B25CA0_THISCALL
