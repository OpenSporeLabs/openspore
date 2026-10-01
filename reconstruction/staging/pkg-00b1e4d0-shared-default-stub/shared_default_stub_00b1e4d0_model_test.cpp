#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "shared_default_stub_00b1e4d0.hpp"

// Focused semantic test for the shared default stub @ 0x00b1e4d0.
//
// The machine body is two instructions (30 c0 / c3: XOR AL,AL; RET), so the
// observable facts are few and each test below pins one of them, written to
// try to REFUTE the reconstruction rather than to walk it:
//
//   1. the return is false in AL - and a true-returning function reads as 1
//      through the same channel, so the check is not vacuous (this is the
//      mutation the return-semantics check exists to catch);
//   2. the callee pops nothing: ESP is identical before and after the call
//      (a frame-allocating or callee-popping mutant fails here);
//   3. the receiver in ECX is never read: different receivers, including a
//      null one, all give the same answer (a receiver-reading mutant such as
//      `return r != nullptr` gives different answers and fails);
//   4. virtual dispatch is a TWO-LEVEL load, receiver -> vtable -> slot: two
//      carriers whose first word points at different tables reach two
//      different functions. A model that collapsed the load into
//      receiver -> slot would call the carrier's first word - a data pointer
//      - as code and crash; a wrong slot index swaps the two results.
//   5. the observed vtable image word and the target bytes are the ones this
//      package claims.
//
// The calls go through inline-asm trampolines that reproduce the observed
// __thiscall shape exactly: receiver in ECX, no stack words, indirect call,
// bare RET. The reconstruction's own compiler-generated body is not relied on
// for the ABI facts; the trampoline pins them.

#if !defined(__i386__) && !defined(_M_IX86)
#error "shared default stub 0x00b1e4d0 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00b1e4d0_shared_default_stub {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t entry_address() {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&shared_default_stub_00b1e4d0));
}

// ECX = receiver, zero stack words, indirect call, bare RET: the observed
// __thiscall shape with caller cleanup.
void call_entry(void* receiver) {
  const std::uint32_t target = entry_address();
  __asm__ __volatile__("movl %[target], %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       :
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "ebx", "ecx", "memory");
}

struct EspSamples {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
};

EspSamples call_entry_measured(void* receiver) {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  const std::uint32_t target = entry_address();
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[target], %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "ebx", "ecx", "memory");
  EspSamples samples;
  samples.before = before;
  samples.after = after;
  return samples;
}

// The low byte of EAX after a call. The body defines exactly one byte (AL);
// the upper 24 bits are indeterminate at the RET and are deliberately not
// read here - masking them out is the width-1 claim, not an oversight.
std::uint8_t al_after_call(void* receiver) {
  const std::uint32_t target = entry_address();
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl %[target], %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ebx", "ecx", "memory");
  return static_cast<std::uint8_t>(eax_after & 0xffu);
}

// A carrier whose first word is the vtable pointer: the layout every
// vptr-backed object has, and the first level of the dispatch load.
struct VtableCarrier {
  const SharedDefaultVTable* vtable;
};

// The two-level load, spelled as the machine does it: level 1 reads the
// vtable pointer from the receiver's first word, level 2 reads slot index 10
// from that table, then the receiver goes into ECX and the slot is called.
void call_slot_10(VtableCarrier* carrier) {
  __asm__ __volatile__("movl (%[recv]), %%eax\n\t"
                       "movl 40(%%eax), %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       :
                       : [recv] "r"(carrier)
                       : "eax", "ebx", "ecx", "memory");
}

std::uint8_t al_after_slot_10(VtableCarrier* carrier) {
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl (%[recv]), %%eax\n\t"
                       "movl 40(%%eax), %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [recv] "r"(carrier)
                       : "eax", "ebx", "ecx", "memory");
  return static_cast<std::uint8_t>(eax_after & 0xffu);
}

// A reference stub that returns true, so the tests above can prove the
// channel discriminates: the same trampoline against this function must read
// 1, or the checks that assert 0 cannot fail. No address in the name.
bool PKG_00B1E4D0_SHARED_DEFAULT_STUB_THISCALL reference_true_stub(void*) {
  return true;
}

std::uint32_t true_stub_address() {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&reference_true_stub));
}

std::uint8_t al_after_true_stub() {
  const std::uint32_t target = true_stub_address();
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl %[target], %%ebx\n\t"
                       "xorl %%ecx, %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [target] "r"(target)
                       : "eax", "ebx", "ecx", "memory");
  return static_cast<std::uint8_t>(eax_after & 0xffu);
}

static_assert(sizeof(kTargetBytes) == 3, "the target body is three bytes");
static_assert(kTargetBytes[0] == 0x30 && kTargetBytes[1] == 0xc0,
              "0x00b1e4d0 is XOR AL,AL (30 c0)");
static_assert(kTargetBytes[2] == 0xc3, "0x00b1e4d2 is a bare RET (c3)");
static_assert(sizeof(SharedDefaultVTable) == 0x2c,
              "slot index 10 is byte offset 40 in the image");
static_assert(sizeof(AbiSharedDefaultStub00b1e4d0) == sizeof(void*),
              "the modelled entry is one 32-bit code pointer");
static_assert(sizeof(bool) == 1,
              "the declared return is one byte, the width the machine writes");

}  // namespace model

}  // namespace openspore::reconstruction::pkg_00b1e4d0_shared_default_stub

namespace {

using namespace openspore::reconstruction::pkg_00b1e4d0_shared_default_stub;
using model::al_after_call;
using model::al_after_slot_10;
using model::al_after_true_stub;
using model::call_entry_measured;
using model::check;
using model::entry_address;
using model::EspSamples;
using model::true_stub_address;
using model::VtableCarrier;

// 1. The stub returns false in AL. The reference true stub returning 1 through
//    the same channel is what makes this assertion capable of failing.
void test_returns_false_in_al() {
  int dummy = 0;
  check(al_after_call(&dummy) == 0u);
  check(al_after_call(&dummy) != 1u);
  check(al_after_true_stub() == 1u);
}

// 2. The terminal is a bare RET: the callee pops nothing, so ESP is identical
//    before and after the call. A frame-allocating or callee-popping mutant
//    (RET N, or a PUSH the body does not balance) fails here.
void test_esp_is_unchanged_by_the_call() {
  int dummy = 0;
  const EspSamples samples = call_entry_measured(&dummy);
  check(samples.before == samples.after);
  check(samples.before != 0);  // the sample is a real stack address
}

// 3. The receiver in ECX is never read: different receivers, including a null
//    one, all give the same answer. A receiver-reading mutant such as
//    `return r != nullptr` gives different answers and fails here.
void test_receiver_is_never_read() {
  int dummy = 0;
  int other = 0;
  check(al_after_call(&dummy) == 0u);
  check(al_after_call(&other) == 0u);
  check(al_after_call(nullptr) == 0u);
}

// 4. Two-level dispatch reaches the reconstruction: the carrier's first word
//    is a vtable pointer, slot index 10 of that table is the stub, and the
//    call through both levels returns false.
void test_dispatch_reaches_the_stub_through_two_levels() {
  SharedDefaultVTable relocated{};
  relocated.slot_10_shared_default = entry_address();
  VtableCarrier carrier{&relocated};
  check(relocated.slot_10_shared_default == entry_address());
  check(al_after_slot_10(&carrier) == 0u);
}

// 5. The dispatch reads the SLOT, not the receiver: two carriers whose first
//    words point at different tables reach two different functions. This is
//    the assertion that the load is receiver -> vtable -> slot and not
//    receiver -> slot - the collapsed form would call the carrier's first
//    word (a data pointer) as code and crash, and a wrong slot index would
//    swap the two results.
void test_dispatch_reads_the_slot_not_the_receiver() {
  SharedDefaultVTable stub_table{};
  stub_table.slot_10_shared_default = entry_address();
  SharedDefaultVTable true_table{};
  true_table.slot_10_shared_default = true_stub_address();
  VtableCarrier stub_carrier{&stub_table};
  VtableCarrier true_carrier{&true_table};
  check(al_after_slot_10(&stub_carrier) == 0u);
  check(al_after_slot_10(&true_carrier) == 1u);
}

// 6. The observed image word and the target bytes are the ones this package
//    claims: slot index 10 of the vftable image holds 0x00b1e4d0, and the
//    body is 30 c0 c3.
void test_observed_image_word_and_target_bytes() {
  const SharedDefaultVTable image{};
  check(image.slot_10_shared_default == 0x00b1e4d0u);
  check(kTargetBytes[0] == 0x30);
  check(kTargetBytes[1] == 0xc0);
  check(kTargetBytes[2] == 0xc3);
}

int run_tests() {
  test_returns_false_in_al();
  test_esp_is_unchanged_by_the_call();
  test_receiver_is_never_read();
  test_dispatch_reaches_the_stub_through_two_levels();
  test_dispatch_reads_the_slot_not_the_receiver();
  test_observed_image_word_and_target_bytes();
  return 0;
}

}  // namespace

int main() { return ::run_tests(); }
