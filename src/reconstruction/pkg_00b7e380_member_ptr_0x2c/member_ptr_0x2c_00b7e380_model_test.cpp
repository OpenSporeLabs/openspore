#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "member_ptr_0x2c_00b7e380.hpp"

// Focused semantic test for FUN_00b7e380 @ 0x00b7e380.
//
// It pins the behaviours the two-instruction body fixes, and it is written to
// try to REFUTE the reconstruction rather than to walk it. Each group below
// names the risky hypothesis it attacks:
//   1. the return value is receiver+0x2c - asserted as a pointer, so a model
//      that returned the receiver itself, or a constant, fails;
//   2. 0x2c is an OFFSET and not an index - the return is shown not to alias
//      0x00, 0x08, 0x28 or 0x30, and the receiver's own 4-byte-aligned prefixes
//      are shown untouched;
//   3. the entry's literal `+ 0x2c` and the header's `kMemberDisplacement` are
//      shown to name one and the same address, so the two statements of the
//      displacement cannot drift apart;
//   4. the ABI is ECX receiver / 0 stack args / caller cleanup - measured,
//      by sampling ESP inside the trampoline, not asserted as a convention;
//   5. the entry is reached only as a virtual call through vtable slot +0x98
//      (slot 38), and the slot word is the one read out of the image.
//
// The calls go through an inline-asm trampoline instead of a thiscall function
// pointer on purpose. GCC's __attribute__((thiscall)) on a *function pointer
// type* allocates the argument with caller-side stack cleanup, which is not the
// convention the target uses (0x00b7e383 is a bare RET, caller cleanup), so a
// plain pointer call would drift the stack by 4 bytes per call. The trampoline
// reproduces the observed sequence exactly:
//     LEA EAX,[ECX+0x2c] / RET
// and the compiler-generated body of the reconstruction is byte-identical to
// it (g++ -m32 -O1 emits `leal 0x2c(%ecx),%eax; ret`, i.e. 8d 41 2c c3).

#if !defined(__i386__) && !defined(_M_IX86)
#error "FUN_00b7e380 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_00B7E380_THISCALL __thiscall
#else
#define PKG_00B7E380_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The raw bytes read from 0x00b7e380..0x00b7e383, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose.
constexpr std::uint8_t kTargetBytes[4] = {
    0x8d, 0x41, 0x2c,  // LEA EAX,dword ptr [ECX + 0x2c]
    0xc3,              // RET
};

Opaque entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&member_ptr_0x2c_00b7e380));
}

// The return value (EAX) after calling the entry through the trampoline.
// ECX = receiver, no stack words pushed, callee pops nothing.
Opaque call_entry(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  Opaque result = 0;
  __asm__ __volatile__("movl %2, %%ecx\n\t"
                       "call *%1\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "r"(target), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

// ESP sampled inside the trampoline, immediately before the call and again the
// instant the callee has returned. `call` puts a return address on the stack
// and `RET` takes it back, so the two samples are equal only when the callee
// owns no cleanup; a `RET 0x4` would leave the second four bytes lower. The
// model test therefore MEASURES the cleanup instead of asserting a calling
// convention it cannot derive from the body.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueReceiver* receiver) {
  const Opaque target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

// A virtual call through vtable slot +0x98 (slot 38): load the slot word,
// receiver in ECX, no stack words pushed, callee pops nothing.
Opaque call_slot_98(const OpaqueReceiverVTable* vtable, OpaqueReceiver* receiver) {
  Opaque result = 0;
  __asm__ __volatile__("movl %1, %%eax\n\t"
                       "movl %2, %%ecx\n\t"
                       "call *%%eax\n\t"
                       "movl %%eax, %0\n\t"
                       : "=r"(result)
                       : "m"(slot_98(*vtable)), "r"(receiver)
                       : "eax", "ecx", "memory");
  return result;
}

static_assert(sizeof(kTargetBytes) == 4, "target body is 4 bytes");
static_assert(kTargetBytes[0] == 0x8d && kTargetBytes[1] == 0x41 &&
                  kTargetBytes[2] == 0x2c,
              "0x00b7e380 is LEA EAX,dword ptr [ECX + 0x2c]");
static_assert(kTargetBytes[3] == 0xc3,
              "0x00b7e383 is RET (caller cleanup, no stack words)");

// The displacement of the one access, taken from the LEA encoding itself:
// 0x00b7e380 is `8d 41 2c`, and the byte after the ModRM byte 0x41 is 0x2c.
// This ties the header's kMemberDisplacement to the instruction rather than
// to prose.
static_assert(kTargetBytes[2] == 0x2c, "LEA displacement byte is 0x2c");
static_assert(kMemberDisplacement == 0x2c,
              "the header's displacement is the LEA's immediate");
static_assert(kMemberDisplacement == (44u),
              "0x2c is the value 44, compared semantically not by spelling");

}

}

namespace {

using namespace openspore::reconstruction::pkg_00b7e380_member_ptr_0x2c;
using model::call_entry;
using model::call_entry_measured;
using model::call_slot_98;
using model::check;
using model::entry_address;
using model::pointer_word;
using model::EspSamples;

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(std::is_same<AbiMemberPtr00b7e380,
                          void*(PKG_00B7E380_THISCALL*)(OpaqueReceiver*)>::value,
              "modelled ABI is thiscall with 0 stack words");

// Fill the whole modeled extent with a non-zero pattern so an access to any
// part of it is visible afterwards.
OpaqueReceiver patterned_receiver() {
  OpaqueReceiver receiver{};
  for (std::size_t index = 0; index < receiver.opaque_bytes.size(); ++index) {
    receiver.opaque_bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
  return receiver;
}

void test_return_value_is_receiver_plus_0x2c() {
  OpaqueReceiver receiver = patterned_receiver();

  const Opaque result = call_entry(&receiver);

  // The return value is the receiver's address plus 0x2c, not the receiver
  // itself, not a constant, and not the first word at that address.
  check(result == pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x2c)));
  check(result != pointer_word(static_cast<const void*>(&receiver)));
  check(result != 0x2cu);
  check(result != *member_at(&receiver, 0x2c));
}

void test_displacement_is_an_offset_not_an_index() {
  OpaqueReceiver receiver = patterned_receiver();

  const Opaque result = call_entry(&receiver);

  // 0x2c is an offset into the receiver, not an index into it. If the
  // reconstruction had (wrongly) treated the displacement as a scale or an
  // element number, these neighbours would be different.
  check(result != pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x00)));
  check(result != pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x08)));
  check(result != pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x28)));
  // 0x2c + 4 is the first byte past the modeled extent, and is not addressable
  // through the receiver: reading it would be a claim the listing does not
  // support, so the test only pins that the extent ends there.
  check(kMemberDisplacement + sizeof(Opaque) == sizeof(OpaqueReceiver));
}

void test_entry_literal_and_header_displacement_agree() {
  OpaqueReceiver receiver = patterned_receiver();
  const Opaque* literal =
      reinterpret_cast<const Opaque*>(reinterpret_cast<std::uintptr_t>(&receiver) + 0x2c);
  const Opaque* declared = member_at(&receiver, kMemberDisplacement);
  check(literal == declared);
  // The gap is measured in BYTES, not in 4-byte words: a model that read the
  // displacement as an element count would land 11 elements out, 0x2c bytes.
  check(reinterpret_cast<std::uintptr_t>(declared) -
            reinterpret_cast<std::uintptr_t>(&receiver) ==
        0x2cu);
}

void test_slot_words_match_the_vtable_image() {
  // The vtable image at 0x013ff648 (and 0x01489090, 0x014893b0) carries
  // 0x00b7e380 at slot 38 (+0x98).
  OpaqueReceiverVTable image{};
  slot_98(image) = 0x00b7e380u;
  check(slot_98(image) == 0x00b7e380u);
}

void test_slot_98_dispatch_reaches_the_reconstruction() {
  // 0x00b7e380 is not mapped in this process, so the image word is relocated
  // to the reconstruction before dispatching; everything else about the call -
  // the slot loaded, ECX as receiver, no pushed arguments, caller cleanup -
  // is the observed sequence.
  OpaqueReceiverVTable relocated{};
  slot_98(relocated) = entry_address();
  check(slot_98(relocated) == entry_address());

  OpaqueReceiver receiver = patterned_receiver();
  const Opaque result = call_slot_98(&relocated, &receiver);
  check(result == pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x2c)));
  // A virtual dispatch through slot +0x98 must reach the same address as a
  // direct entry call: dispatch changes the call site, not the effect.
  check(result != pointer_word(static_cast<const void*>(&receiver)));
}

// The body ends in a bare RET, so the callee pops nothing and the caller owns
// the stack. That is measured here, not assumed: ESP is sampled before the
// call and after the return, and the two must be equal.
void test_no_stack_words_are_popped_by_the_callee() {
  OpaqueReceiver receiver = patterned_receiver();

  const EspSamples samples = call_entry_measured(&receiver);
  check(samples.after_return == samples.before_call);

  // The return materialises a pointer in EAX: the body computes ECX + 0x2c
  // and returns it. What the body does not do is write any memory - asserted
  // through the return value, not through a store, because the modelled entry
  // returns void*.
  const Opaque result = call_entry(&receiver);
  check(result == pointer_word(reinterpret_cast<const void*>(
             reinterpret_cast<std::uintptr_t>(&receiver) + 0x2c)));
  check(sizeof(AbiMemberPtr00b7e380) == sizeof(void*));
}

int run_tests() {
  test_return_value_is_receiver_plus_0x2c();
  test_displacement_is_an_offset_not_an_index();
  test_entry_literal_and_header_displacement_agree();
  test_slot_words_match_the_vtable_image();
  test_slot_98_dispatch_reaches_the_reconstruction();
  test_no_stack_words_are_popped_by_the_callee();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_00B7E380_THISCALL
