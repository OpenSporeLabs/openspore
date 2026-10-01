// PKG-SPOREPEDIA-NOP-SLOT -- VA 0x00c2e4e0
// Behavioural model test for FUN_00c2e4e0.
// (SPORE/SporeBin/SporeApp.exe, 3.1.0.22, x86-32)
//
// The body is a single bare RET, so the whole of its observable behaviour is
// an absence: it writes no byte of the receiver, it transfers control nowhere,
// it pops nothing off the stack, and it produces no value. Each test below is
// one of those absences read positively, and each is stated so that the
// mutation its check exists to catch would fail it:
//
//   receiver bytes unchanged     catches a body that reads or writes a receiver
//                                field -- the FIELDS/OFFSETS mutation
//   ESP unchanged across a call  catches a body that pops the stack -- the
//                                ABI mutation (a callee-cleanup convention)
//   void return, compile-time    catches a body that produces a value -- the
//                                RETURN SEMANTICS mutation (the machine state
//                                is VOID_PROVEN)
//   the call returns             catches a body that does not return -- the
//                                CONTROL FLOW mutation (a loop hangs the test
//                                binary and the harness fails it)
//   dispatch through a slot      catches a convention that is not the vtable
//                                slot shape V1-VFT derived: receiver in ECX,
//                                no stack argument, caller cleans
//
// Two mutations are caught outside this file, and are recorded here rather
// than tested: a named callee fails to link (the package defines no callee, so
// any external call the body made would be an undefined symbol at the archive
// step), and a hexadecimal literal, a field-offset declaration, a data address
// or a slot-boundary token in the source span is a source-text fact the
// validator's CONSTANTS, FIELDS/OFFSETS, GLOBALS and VIRTUAL DISPATCH checks
// read directly.
//
// One absence is deliberately NOT tested: a pure read of the receiver with no
// effect. For a leaf body a read that writes nothing and branches on nothing
// is indistinguishable from no read, in the original as much as in the model,
// so a test for it could not fail. The listing shows no read and the source
// declares none; that is the whole of the evidence.

#include "sporepedia_nop_slot.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <type_traits>

namespace openspore::reconstruction::pkg_sporepedia_nop_slot {

namespace {

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

// The machine stack pointer, read directly. The gate is clang++ -m32, where
// this GCC-style inline assembler is available and the register named is the
// machine's own ESP. The read is volatile, so the two calls below bracket the
// reconstructed body at two distinct program points and the compiler cannot
// move either across the call between them.
std::uintptr_t stack_pointer() {
  std::uintptr_t sp = 0;
  __asm__ volatile("movl %%esp, %0" : "=r"(sp));
  return sp;
}

// A receiver block filled with a non-zero poison byte, so a write the body
// makes to any displacement -- at any offset, through any register -- is
// visible in the comparison afterwards. 256 bytes is far more than any
// receiver this body could reach; the point is that the body reaches none.
struct Receiver {
  unsigned char bytes[256];
};

void fill_receiver(Receiver &receiver) {
  std::memset(receiver.bytes, 0xa5, sizeof receiver.bytes);
}

// 0x00c2e4e0 is a bare RET: the body performs no memory operand at all, so no
// byte of the receiver moves. The mutation this catches is a body that clears,
// sets or re-reads a receiver word -- the shape every other reconstructed
// vftable slot in this cluster has and this one does not.
void test_the_receiver_comes_back_byte_for_byte() {
  Receiver receiver;
  fill_receiver(receiver);
  Receiver before;
  std::memcpy(&before, &receiver, sizeof before);

  sporepedia_nop_slot_FUN_00c2e4e0(receiver.bytes);

  check(std::memcmp(&before, &receiver, sizeof receiver) == 0,
        "0x00c2e4e0 is a bare RET: the body writes no byte of the receiver at "
        "any displacement, so the block comes back byte for byte");
}

// The terminator is a bare RET with no immediate: the callee pops nothing, so
// the caller's stack pointer is the same after the call as before it. The
// mutation this catches is a body that pops -- a RET N, or a callee-cleanup
// convention -- which would leave ESP lower than it found it. A pop that also
// corrupts the return address does not survive to fail here; it fails by
// crashing, which is the same verdict.
void test_the_stack_pointer_is_unchanged_across_the_call() {
  Receiver receiver;
  fill_receiver(receiver);
  const std::uintptr_t before = stack_pointer();

  sporepedia_nop_slot_FUN_00c2e4e0(receiver.bytes);

  const std::uintptr_t after = stack_pointer();
  check(after == before,
        "the callee pops nothing: ESP after the call equals ESP before it, "
        "which is the caller-cleans half of the __thiscall ABI");
}

// Rule V1-VFT derived the ABI from vtable slot membership: 0x00c2e4e0 is a
// slot of a vptr-backed vftable, so its convention is the slot shape -- the
// receiver arrives in ECX, no word is pushed, and the caller owns the stack.
// Dispatching through a slot-typed pointer is that shape end to end: the
// pointer carries the same convention the vtable dispatch in the original
// would have used, so a function whose ABI did not match the slot would not
// survive the dispatch. The mutation this catches is a convention mismatch.
void test_the_function_is_dispatchable_as_a_virtual_slot() {
  Receiver receiver;
  fill_receiver(receiver);
  Receiver before;
  std::memcpy(&before, &receiver, sizeof before);
  const std::uintptr_t sp_before = stack_pointer();

  void (PKG_SPOREPEDIA_NOP_SLOT_THISCALL *const slot)(void *) =
      &sporepedia_nop_slot_FUN_00c2e4e0;
  slot(receiver.bytes);

  const std::uintptr_t sp_after = stack_pointer();
  check(sp_after == sp_before,
        "a slot-typed dispatch leaves the stack as it found it: the receiver "
        "arrives in ECX and no word is pushed");
  check(std::memcmp(&before, &receiver, sizeof receiver) == 0,
        "a slot-typed dispatch hands the receiver over unread");
}

// The body is one unconditional RET, so the call returns. The mutation this
// catches is a body that does not return -- a loop, or a transfer away -- which
// would hang the test binary and be failed by the harness timeout. The
// sentinel is the in-process half of the same check: control reaches it.
void test_the_call_returns() {
  Receiver receiver;
  fill_receiver(receiver);
  bool returned = false;

  sporepedia_nop_slot_FUN_00c2e4e0(receiver.bytes);
  returned = true;

  check(returned,
        "the body returns: 0x00c2e4e0 is a single unconditional RET");
}

// The machine return state is VOID_PROVEN: the complete 1-instruction listing
// writes EAX on no path before the single reachable return, and the body makes
// no call that could clobber it, so the function returns nothing. The source
// span declares void, and this is the compile-time half of that claim -- a
// source that declared a value the machine does not produce would not
// compile. The mutation this catches is a non-void return type.
static_assert(std::is_void_v<std::invoke_result_t<decltype(&sporepedia_nop_slot_FUN_00c2e4e0), void *>>,
              "the machine proves the return is empty: the source span declares "
              "void, and a declared value would contradict VOID_PROVEN");

}  // namespace
}  // namespace openspore::reconstruction::pkg_sporepedia_nop_slot

int main() {
  using namespace openspore::reconstruction::pkg_sporepedia_nop_slot;
  test_the_receiver_comes_back_byte_for_byte();
  test_the_stack_pointer_is_unchanged_across_the_call();
  test_the_function_is_dispatchable_as_a_virtual_slot();
  test_the_call_returns();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
