#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "shared_zero_result_00e31100.hpp"

// Focused semantic test for the shared zero-result stub @ 0x00e31100.
//
// The machine body is two instructions (33 c0 / c3: XOR EAX,EAX; RET), so the
// observable facts are few and each test below pins one of them, written to
// try to REFUTE the reconstruction rather than to walk it:
//
//   1. all 32 bits of EAX are zero at the RET - and EAX is deliberately
//      pre-loaded with a non-zero garbage pattern before every call, so a
//      one-byte-only write (XOR AL,AL, the 0x00b1e4d0 shape) is refuted rather
//      than passing by accident on an already-zero register. A reference stub
//      returning 0x12345678 through the same channel is what makes the
//      assertion capable of failing at all;
//   2. the callee pops nothing: ESP is identical before and after the call
//      (a frame-allocating or callee-popping mutant fails here);
//   3. the receiver in ECX is never read: different receivers, including a null
//      one, all give the same answer (a receiver-reading mutant fails here);
//   4. virtual dispatch is a TWO-LEVEL load, receiver -> vtable -> slot: two
//      carriers whose first word points at different tables reach two different
//      functions. A model that collapsed the load into receiver -> slot would
//      call the carrier's first word - a data pointer - as code and crash; a
//      wrong slot index swaps the two results;
//   5. the pkg08_cell_mode port spelling (no explicit arguments) and the
//      vftable spelling (receiver in ECX) are the same machine call here;
//   6. the observed vtable image word and the target bytes are the ones this
//      package claims, and the 0xcc fill after the body is padding, not body.
//
// The calls go through inline-asm trampolines that reproduce the observed
// shapes exactly. The reconstruction's own compiler-generated body is not
// relied on for the ABI facts; the trampoline pins them.

#if !defined(__i386__) && !defined(_M_IX86)
#error "shared zero-result stub 0x00e31100 model test requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_00e31100_shared_zero_result_stub {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

std::uint32_t entry_address() {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&shared_zero_result_00e31100));
}

// A carrier whose first word is the vtable pointer: the layout every
// vptr-backed object has, and the first level of the dispatch load.
struct VtableCarrier {
  const SharedZeroResultVTable* vtable;
};

struct EspSamples {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
};

// ECX = receiver, EAX pre-loaded with garbage, zero stack words, indirect call,
// bare RET: the observed __thiscall shape with caller cleanup.
//
// The EAX pre-load is what turns check 1 into a real refutation instead of a
// tautology. A `xor eax, eax` body overwrites the garbage and every one of the
// 32 bits is then zero; a body that writes only AL leaves the three garbage
// bytes visible in the full 32-bit read below.
std::uint32_t eax_after_call(void* receiver) {
  const std::uint32_t target = entry_address();
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl $0x12345678, %%eax\n\t"
                       "movl %[target], %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ebx", "ecx", "memory");
  return eax_after;
}

// The pkg08_cell_mode port shape: no explicit arguments, ECX left alone by the
// caller. Same channel, same pre-load.
std::uint32_t eax_after_call_no_args() {
  const std::uint32_t target = entry_address();
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl $0x12345678, %%eax\n\t"
                       "movl %[target], %%ebx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [target] "r"(target)
                       : "eax", "ebx", "memory");
  return eax_after;
}

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

// The two-level load, spelled as the machine does it: level 1 reads the vtable
// pointer from the receiver's first word, level 2 reads slot index 8 from that
// table, then the receiver goes into ECX and the slot is called.
std::uint32_t eax_after_slot_8(VtableCarrier* carrier) {
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl $0x12345678, %%eax\n\t"
                       "movl (%[recv]), %%eax\n\t"
                       "movl 32(%%eax), %%ebx\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [recv] "r"(carrier)
                       : "eax", "ebx", "ecx", "memory");
  return eax_after;
}

// A reference stub returning a distinctive 32-bit value, so the checks that
// assert 0 can fail. No address in the name.
std::int32_t PKG_00E31100_SHARED_ZERO_RESULT_THISCALL
reference_nonzero_stub(void*) {
  return static_cast<std::int32_t>(0x12345678u);
}

std::uint32_t nonzero_stub_address() {
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&reference_nonzero_stub));
}

std::uint32_t eax_after_nonzero_stub() {
  const std::uint32_t target = nonzero_stub_address();
  std::uint32_t eax_after = 0;
  __asm__ __volatile__("movl $0x12345678, %%eax\n\t"
                       "movl %[target], %%ebx\n\t"
                       "xorl %%ecx, %%ecx\n\t"
                       "call *%%ebx\n\t"
                       "movl %%eax, %[out]\n\t"
                       : [out] "=r"(eax_after)
                       : [target] "r"(target)
                       : "eax", "ebx", "ecx", "memory");
  return eax_after;
}

static_assert(sizeof(kTargetBytes) == 3, "the target body is three bytes");
static_assert(sizeof(std::int32_t) == 4,
              "the declared return is the 32 bits the machine writes");
static_assert(sizeof(SharedZeroResultVTable) == 0x24,
              "slot index 8 is byte offset 32 in the image");

}  // namespace model

}  // namespace openspore::reconstruction::pkg_00e31100_shared_zero_result_stub

namespace {

using namespace openspore::reconstruction::pkg_00e31100_shared_zero_result_stub;
using model::call_entry_measured;
using model::check;
using model::eax_after_call;
using model::eax_after_call_no_args;
using model::eax_after_nonzero_stub;
using model::eax_after_slot_8;
using model::entry_address;
using model::EspSamples;
using model::nonzero_stub_address;
using model::VtableCarrier;

// 1. All 32 bits of EAX are zero at the RET, over a garbage pre-load. The
//    nonzero reference stub reading 0x12345678 through the same channel is what
//    makes this assertion capable of failing; a body writing only AL would leave
//    0x12345600 here and fail.
void test_all_thirty_two_bits_of_eax_are_zero() {
  int dummy = 0;
  check(eax_after_nonzero_stub() == 0x12345678u);
  check(eax_after_call(&dummy) == 0u);
  check(eax_after_call(&dummy) != 0x12345600u);
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
//    one, all give the same answer. A receiver-reading mutant gives different
//    answers and fails here.
void test_receiver_is_never_read() {
  int dummy = 0;
  int other = 0;
  check(eax_after_call(&dummy) == 0u);
  check(eax_after_call(&other) == 0u);
  check(eax_after_call(nullptr) == 0u);
}

// 4a. Two-level dispatch reaches the reconstruction: the carrier's first word
//     is a vtable pointer, slot index 8 of that table is the stub, and the call
//     through both levels returns zero.
void test_dispatch_reaches_the_stub_through_two_levels() {
  SharedZeroResultVTable relocated{};
  relocated.slot_8_shared_zero_result = entry_address();
  VtableCarrier carrier{&relocated};
  check(relocated.slot_8_shared_zero_result == entry_address());
  check(eax_after_slot_8(&carrier) == 0u);
}

// 4b. The dispatch reads the SLOT, not the receiver: two carriers whose first
//     words point at different tables reach two different functions. This is the
//     assertion that the load is receiver -> vtable -> slot and not
//     receiver -> slot - the collapsed form would call the carrier's first word
//     (a data pointer) as code and crash, and a wrong slot index would swap the
//     two results.
void test_dispatch_reads_the_slot_not_the_receiver() {
  SharedZeroResultVTable stub_table{};
  stub_table.slot_8_shared_zero_result = entry_address();
  SharedZeroResultVTable nonzero_table{};
  nonzero_table.slot_8_shared_zero_result = nonzero_stub_address();
  VtableCarrier stub_carrier{&stub_table};
  VtableCarrier nonzero_carrier{&nonzero_table};
  check(eax_after_slot_8(&stub_carrier) == 0u);
  check(eax_after_slot_8(&nonzero_carrier) == 0x12345678u);
}

// 5. The two port spellings src/reconstruction/pkg08_cell_mode and this package
//    use are the same machine call here, because the body reads ECX in no form.
//    Both trampolines reach the same three bytes and both read zero.
void test_pkg08_port_spelling_and_thiscall_spelling_agree() {
  int dummy = 0;
  check(eax_after_call(&dummy) == eax_after_call_no_args());
  check(eax_after_call_no_args() == 0u);
}

// 6. The observed image word and the target bytes are the ones this package
//    claims: slot index 8 of the vftable image at 0x013f6364 holds 0x00e31100,
//    the body is 33 c0 c3, and the 0xcc fill after it is padding.
void test_observed_image_word_and_target_bytes() {
  const SharedZeroResultVTable image{};
  check(image.slot_8_shared_zero_result == 0x00e31100u);
  check(kTargetBytes[0] == 0x33);
  check(kTargetBytes[1] == 0xc0);
  check(kTargetBytes[2] == 0xc3);
  check(kPaddingByte == 0xcc);
}

int run_tests() {
  test_all_thirty_two_bits_of_eax_are_zero();
  test_esp_is_unchanged_by_the_call();
  test_receiver_is_never_read();
  test_dispatch_reaches_the_stub_through_two_levels();
  test_dispatch_reads_the_slot_not_the_receiver();
  test_pkg08_port_spelling_and_thiscall_spelling_agree();
  test_observed_image_word_and_target_bytes();
  return 0;
}

}  // namespace

int main() { return ::run_tests(); }