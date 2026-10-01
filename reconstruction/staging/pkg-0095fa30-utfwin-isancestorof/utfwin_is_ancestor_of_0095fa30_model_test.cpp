#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "utfwin_is_ancestor_of_0095fa30.hpp"

// Focused semantic test for UTFWin::Window::IsAncestorOf @ 0x0095fa30.
//
// It pins the behaviours the three-instruction body fixes, and it is written to
// try to REFUTE the reconstruction rather than to walk it. Each group below
// names the risky hypothesis it attacks:
//   1. the single stack word is stored verbatim at receiver+0x80 - asserted as a
//      value, so a model that stored the *pointee* instead of the pointer fails;
//   2. the store is unconditional - a null argument still overwrites the slot,
//      and the prior value is never read, compared or preserved (so a model
//      with a read-modify-write or a null guard fails);
//   3. 0x80 is an OFFSET and not an index - the slot is shown not to alias
//      0x00, 0x08, 0x7c or 0x84, and the receiver's own 4-byte-aligned prefixes
//      are shown untouched;
//   4. the entry's literal `+ 0x80` and the header's `kSlotDisplacement` are
//      shown to name one and the same 4 bytes, so the two statements of the
//      displacement cannot drift apart;
//   5. the ABI is ECX receiver / [ESP+4] argument / callee cleanup - measured,
//      by sampling ESP inside the trampoline, not asserted as a convention;
//   6. the entry is reached only as a virtual call through vtable slot +0x00,
//      and the four slot words are the ones read out of the image.
//
// The calls go through an inline-asm trampoline instead of a thiscall function
// pointer on purpose. GCC's __attribute__((thiscall)) on a *function pointer
// type* allocates the argument with caller-side stack cleanup, which is not the
// convention the target uses (0x0095fa3a is RET 0x4, callee cleanup), so a
// plain pointer call would drift the stack by 8 bytes per call. The trampoline
// reproduces the observed sequence exactly:
//     MOV  EAX,[ESP+0x4] / MOV  [ECX+0x80],EAX / RET 0x4
// and the compiler-generated body of the reconstruction is byte-identical to
// it (g++ -m32 -O1 emits `movl 4(%esp),%eax; movl %eax,128(%ecx); ret $4`,
// i.e. 8b 44 24 04 89 81 80 00 00 00 c2 04 00).

#if !defined(__i386__) && !defined(_M_IX86)
#error "UTFWin IsAncestorOf 0x0095fa30 model test requires an x86-32 target"
#endif

// The header undefines its convention macro, so the modelled ABI type is
// respelled here; it is the same thiscall pointer type the entry declares.
#if defined(_MSC_VER)
#define PKG_0095FA30_THISCALL __thiscall
#else
#define PKG_0095FA30_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof {
namespace model {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

// The raw bytes read from 0x0095fa30..0x0095fa3b, kept so the reconstruction's
// instruction sequence is stated in the test and not only in prose.
constexpr std::uint8_t kTargetBytes[13] = {
    0x8b, 0x44, 0x24, 0x04,              // MOV EAX,dword ptr [ESP + 0x4]
    0x89, 0x81, 0x80, 0x00, 0x00, 0x00,  // MOV dword ptr [ECX + 0x80],EAX
    0xc2, 0x04, 0x00,                    // RET 0x4
};

Opaque entry_address() {
  return pointer_word(reinterpret_cast<const void*>(&is_ancestor_of_0095fa30));
}

// ESP sampled inside the trampoline, immediately before the argument word is
// pushed and again the instant the callee has returned. `call` puts a return
// address on the stack and `RET 0x4` takes it back plus the four bytes of the
// argument, so the two samples are equal only when the callee owns that
// cleanup; a plain `RET` would leave the second four bytes lower. The model
// test therefore MEASURES the cleanup instead of asserting a calling
// convention it cannot derive from the body.
struct EspSamples {
  std::uint32_t before_push = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_entry_measured(OpaqueWindow* receiver, OpaqueWindow* argument) {
  const Opaque target = entry_address();
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "pushl %[arg]\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(receiver),
                         [arg] "r"(argument)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_push = before;
  samples.after_return = after;
  return samples;
}

// ECX = receiver, one stack word pushed, callee pops it through RET 0x4.
void call_entry(OpaqueWindow* receiver, OpaqueWindow* argument) {
  const Opaque target = entry_address();
  __asm__ __volatile__("movl %1, %%ecx\n\t"
                       "pushl %2\n\t"
                       "call *%0\n\t"
                       :
                       : "r"(target), "r"(receiver), "r"(argument)
                       : "eax", "ecx", "memory");
}

// A virtual call through vtable slot +0x00: load the slot word, receiver in
// ECX, one stack word pushed, callee pops it.
void call_slot_00(const OpaqueWindowVTable* vtable, OpaqueWindow* receiver,
                  OpaqueWindow* argument) {
  __asm__ __volatile__("movl %0, %%eax\n\t"
                       "movl %1, %%ecx\n\t"
                       "pushl %2\n\t"
                       "call *%%eax\n\t"
                       :
                       : "m"(vtable->slot_00_is_ancestor_of), "r"(receiver),
                         "r"(argument)
                       : "eax", "ecx", "memory");
}

static_assert(sizeof(kTargetBytes) == 13, "target body is 13 bytes");
static_assert(kTargetBytes[0] == 0x8b && kTargetBytes[3] == 0x04,
              "0x0095fa30 loads the first stack word");
static_assert(kTargetBytes[4] == 0x89 && kTargetBytes[5] == 0x81 &&
                  kTargetBytes[6] == 0x80 && kTargetBytes[9] == 0x00,
              "0x0095fa34 is MOV dword ptr [ECX + 0x80],EAX");
static_assert(kTargetBytes[10] == 0xc2 && kTargetBytes[11] == 0x04,
              "0x0095fa3a is RET 0x4 (callee cleanup of one word)");

// The displacement of the one access, taken from the store encoding itself:
// 0x0095fa34 is `89 81 80 00 00 00`, and the little-endian immediate after the
// ModRM byte 0x81 is 0x00000080. This ties the header's kSlotDisplacement to
// the instruction rather than to prose.
static_assert(kTargetBytes[6] == 0x80, "store immediate low byte is 0x80");
static_assert((kTargetBytes[7] | (kTargetBytes[8] << 8) |
               (kTargetBytes[9] << 16)) == 0,
              "store immediate is 32-bit wide and zero above 0x80");
static_assert(kSlotDisplacement == 0x80,
              "the header's displacement is the store's immediate");
static_assert(kSlotDisplacement == (128u),
              "0x80 is the value 128, compared semantically not by spelling");

}

}

namespace {

using namespace openspore::reconstruction::pkg_0095fa30_utfwin_isancestorof;
using model::call_entry;
using model::call_entry_measured;
using model::call_slot_00;
using model::check;
using model::entry_address;
using model::pointer_word;
using model::EspSamples;

static_assert(sizeof(pointer_word(nullptr)) == 4,
              "the modelled entry slot is one 32-bit word");
static_assert(std::is_same<AbiIsAncestorOf0095fa30,
                           void(PKG_0095FA30_THISCALL*)(OpaqueWindow*,
                                                        OpaqueWindow*)>::value,
              "modelled ABI is thiscall with one stack word");

// Fill the whole modeled extent with a non-zero pattern so an access to any
// part of it is visible afterwards.
OpaqueWindow patterned_window() {
  OpaqueWindow window{};
  for (std::size_t index = 0; index < window.opaque_bytes.size(); ++index) {
    window.opaque_bytes[index] = static_cast<std::uint8_t>(index + 1u);
  }
  return window;
}

void test_argument_word_lands_at_plus_0x80() {
  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();

  call_entry(&window, &child);

  // The store holds the ARGUMENT'S ADDRESS, not the first word at that address.
  // A model that dereferenced the argument, or that stored the receiver, fails
  // here even though both would put *something* at 0x80.
  check(*word_at(&window, 0x80) == pointer_word(&child));
  check(*word_at(&window, 0x80) != *word_at(&child, 0));
  check(*word_at(&window, 0x80) != pointer_word(&window));
  check(*word_at(&window, 0x80) != kSlotDisplacement);
}

void test_store_is_unconditional() {
  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();

  // A prior value in the slot must be gone afterwards: the body holds no null
  // check and performs no read-modify-write on the destination.
  *word_at(&window, 0x80) = pointer_word(&window);
  call_entry(&window, nullptr);  // the body holds no null check
  check(*word_at(&window, 0x80) == 0u);

  // Self-assignment and a fresh receiver both store too: the body never loads
  // receiver+0x80 to decide anything.
  *word_at(&window, 0x80) = 0u;
  call_entry(&window, &window);
  check(*word_at(&window, 0x80) == pointer_word(&window));

  OpaqueWindow fresh = patterned_window();
  check(*word_at(&fresh, 0x80) != 0u);  // pattern, not a zeroed pointer
  call_entry(&fresh, &child);
  check(*word_at(&fresh, 0x80) == pointer_word(&child));
}

// 0x80 is an offset into the receiver, not an index into it. If the
// reconstruction had (wrongly) treated the displacement as a scale or an
// element number, these neighbours would move too.
void test_displacement_is_an_offset_not_an_index() {
  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();

  const Opaque at_00_before = *word_at(&window, 0x00);
  const Opaque at_08_before = *word_at(&window, 0x08);
  const Opaque at_7c_before = *word_at(&window, 0x7c);

  call_entry(&window, &child);

  check(*word_at(&window, 0x80) == pointer_word(&child));
  check(*word_at(&window, 0x00) == at_00_before);
  check(*word_at(&window, 0x08) == at_08_before);
  check(*word_at(&window, 0x7c) == at_7c_before);
  // 0x80 + 4 is the first byte past the modeled extent, and is not addressable
  // through the receiver: reading it would be a claim the listing does not
  // support, so the test only pins that the extent ends there.
  check(kSlotDisplacement + sizeof(Opaque) == sizeof(OpaqueWindow));
}

// Only the four bytes of the slot at 0x80 change; every other byte of the
// modeled receiver keeps its pattern. This is the byte-level statement of
// "no byte outside receiver+0x80 is touched".
void test_no_other_receiver_byte_is_touched() {
  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();

  call_entry(&window, &child);

  for (std::size_t index = 0; index < window.opaque_bytes.size(); ++index) {
    const bool inside_slot = index >= kSlotDisplacement &&
                             index < kSlotDisplacement + sizeof(Opaque);
    if (inside_slot) {
      continue;  // rewritten by the store, value pinned by the tests above
    }
    check(window.opaque_bytes[index] == static_cast<std::uint8_t>(index + 1u));
  }
  // And the slot really did change, so the loop above is not vacuous.
  check(window.opaque_bytes[kSlotDisplacement] !=
        static_cast<std::uint8_t>(kSlotDisplacement + 1u));
}

// The entry writes `reinterpret_cast<uintptr_t>(window) + 0x80` literally; the
// header exposes the same slot as word_at(window, kSlotDisplacement). The two
// statements of the displacement must name the same four bytes, or one of them
// is a lie.
void test_entry_literal_and_header_displacement_agree() {
  OpaqueWindow window = patterned_window();
  const Opaque* literal =
      reinterpret_cast<const Opaque*>(reinterpret_cast<std::uintptr_t>(&window) + 0x80);
  const Opaque* declared = word_at(&window, kSlotDisplacement);
  check(literal == declared);
  // The gap is measured in BYTES, not in 4-byte words: a model that read the
  // displacement as an element count would land 32 elements out, 0x80 bytes.
  check(reinterpret_cast<std::uintptr_t>(declared) -
            reinterpret_cast<std::uintptr_t>(&window) ==
        0x80u);
}

void test_slot_words_match_the_vtable_image() {
  // Words read at the 33 DATA reference addresses (0x013fdb6c, 0x01414c14,
  // 0x014195dc, 0x01479314, 0x0144324c and the rest all carry the same four).
  const OpaqueWindowVTable image{};
  check(image.slot_00_is_ancestor_of == 0x0095fa30u);
  check(image.slot_04_func35 == 0x0095fd60u);
  check(image.slot_08 == 0x0095fdc0u);
  check(image.slot_0c == 0x0095fe40u);
}

// 0x0095fd60 (SDK label UTFWin::Window::func35) is the slot +0x04 word; it is
// not mapped here either and stays the raw image value.
Opaque image_func35_word() { return 0x0095fd60u; }

void test_slot_00_dispatch_reaches_the_reconstruction() {
  // 0x0095fa30 is not mapped in this process, so the image word is relocated to
  // the reconstruction before dispatching; everything else about the call - the
  // slot loaded, ECX as receiver, one pushed argument, callee cleanup - is the
  // observed sequence.
  OpaqueWindowVTable relocated{};
  relocated.slot_00_is_ancestor_of = entry_address();
  relocated.slot_04_func35 = image_func35_word();
  check(relocated.slot_00_is_ancestor_of == entry_address());
  check(relocated.slot_04_func35 == 0x0095fd60u);

  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();
  call_slot_00(&relocated, &window, &child);
  check(*word_at(&window, 0x80) == pointer_word(&child));
  // A virtual dispatch through slot +0x00 must reach the same 4-byte slot as a
  // direct entry call: dispatch changes the call site, not the effect.
  check(*word_at(&window, 0x80) != *word_at(&window, 0x00));
}

// The body ends in `RET 0x4`, so the callee - not the caller - owns the four
// bytes of the argument word. That is measured here, not assumed: ESP is
// sampled after the push and after the return, and the two must be equal.
void test_argument_word_is_popped_by_the_callee() {
  OpaqueWindow window = patterned_window();
  OpaqueWindow child = patterned_window();

  const EspSamples samples = call_entry_measured(&window, &child);
  check(samples.after_return == samples.before_push);
  check(*word_at(&window, 0x80) == pointer_word(&child));

  // The return materialises no result: no instruction after the load writes
  // EAX, so nothing here claims the residue as a returned value. What the body
  // does leave behind is exactly the stored word - asserted through memory,
  // not through a return register, because the modelled entry returns void.
  check(sizeof(AbiIsAncestorOf0095fa30) == sizeof(void*));
}

int run_tests() {
  test_argument_word_lands_at_plus_0x80();
  test_store_is_unconditional();
  test_displacement_is_an_offset_not_an_index();
  test_no_other_receiver_byte_is_touched();
  test_entry_literal_and_header_displacement_agree();
  test_slot_words_match_the_vtable_image();
  test_slot_00_dispatch_reaches_the_reconstruction();
  test_argument_word_is_popped_by_the_callee();
  return 0;
}

}

int main() { return ::run_tests(); }

#undef PKG_0095FA30_THISCALL
