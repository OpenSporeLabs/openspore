// Model test for 0x004adc40 (PKG-EDITOR-ADC40-FLAG).
//
// What the binary evidence fixes, and what this test therefore pins:
//
//   004adc4a  8a 40 4f   mov al, byte ptr [eax+0x4f]   one BYTE at displacement 0x4f
//   004adc50  c3         ret                            caller owns cleanup
//
// so: the value is the single byte at receiver+0x4f; the load is byte-wide and
// no neighbouring byte participates; nothing is written back; the receiver is
// never null-checked, so a null or near-null receiver faults.
//
// The riskiest readings this test attacks, one by one:
//
//   * pointer vs pointee -- the body reloads the spilled ECX into EAX and then
//     dereferences it, so a reconstruction that returned the receiver pointer
//     (or the address of the slot) instead of the byte would be plausible from
//     the shape of the listing alone. The seeded byte is chosen to differ from
//     the receiver's own low address byte, so those three answers are
//     distinguishable.
//   * byte vs word -- a dword read at 0x4f, or at 0x4c, would fold three
//     neighbouring bytes into the answer. The three bytes below 0x4f are set to
//     values that a word read would have to include.
//   * displacement vs member -- the reconstruction addresses the receiver by
//     displacement, so the test addresses it by displacement too and checks the
//     result against a raw arena rather than against a named field.
//   * guard vs no guard -- the absence of a null check is asserted by faulting.
//
// Deliberately NOT asserted: that the upper 24 bits of EAX come back equal to
// the receiver address bits 8..31. The original only writes AL, but a C++
// function returning std::uint8_t is free to zero-extend, and that register
// detail is recorded in the source comment rather than pinned by a test.
//
// Build (x86-32):
//   clang++ -m32 -std=c++17 -Wall -Wextra -Werror -O2 \
//       -I. adc40_flag.cpp adc40_flag_model_test.cpp
//   ./adc40_flag_model_test && echo PASS

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <type_traits>

#include "adc40_flag.hpp"

namespace {

using openspore::reconstruction::pkg_editor_adc40_flag::Byte;
using openspore::reconstruction::pkg_editor_adc40_flag::Field;
using openspore::reconstruction::pkg_editor_adc40_flag::FUN_004adc40;
using openspore::reconstruction::pkg_editor_adc40_flag::OpaqueEditorFlag;

// adc40_flag.hpp #undefs its convention token at the end of the file, so the
// test re-states the same token locally rather than depending on a macro that
// is deliberately not leaked.
#if defined(_MSC_VER)
#define PKG_EDITOR_ADC40_TEST_THISCALL __thiscall
#else
#define PKG_EDITOR_ADC40_TEST_THISCALL __attribute__((thiscall))
#endif

static_assert(sizeof(OpaqueEditorFlag) >= 0x50,
              "the observed load requires a 0x50-byte receiver prefix");

// The declared contract: receiver in ECX, no stack word, the result carried in
// AL. A change to the parameter list, the convention or the return type stops
// this file from compiling, which is the point -- each of those is a claim that
// would need the machine record re-checked rather than a free refactor.
static_assert(std::is_same<decltype(&FUN_004adc40),
                           Field(PKG_EDITOR_ADC40_TEST_THISCALL *)(
                               OpaqueEditorFlag *)>::value,
              "0x004adc40 takes the receiver in ECX and returns one byte");

// The displacement the listing shows, used by the test to seed and read the
// receiver without naming a member.
constexpr std::size_t kObservedDisplacement = 0x4f;

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

enum class InvalidReceiver { null_receiver, near_null_receiver };

// -- the byte at receiver+0x4f is returned, exhaustively, and the receiver is
// left byte-for-byte identical
void expect_returned_bytes() {
  OpaqueEditorFlag receiver{};
  for (std::size_t index = 0; index < sizeof(receiver.opaque_000); ++index) {
    receiver.opaque_000[index] = static_cast<Byte>(index * 7U + 3U);
  }

  for (std::uint32_t raw = 0; raw <= 0xffU; ++raw) {
    receiver.byte_04f = static_cast<Field>(raw);
    assert(FUN_004adc40(&receiver) == static_cast<Field>(raw));
  }

  // 0x80 and 0xff are the values a signed reading of the byte would get wrong.
  receiver.byte_04f = 0x80U;
  assert(FUN_004adc40(&receiver) == 0x80U);
  receiver.byte_04f = 0xffU;
  assert(FUN_004adc40(&receiver) == 0xffU);

  const auto before = receiver;
  assert(FUN_004adc40(&receiver) == 0xffU);
  assert(std::memcmp(&before, &receiver, sizeof(receiver)) == 0);
}

// -- the load is byte-wide: no byte before 0x4f and no byte after it can
// influence the result, so the body cannot be reading a wider word that
// happens to contain 0x4f
void expect_only_byte_04f_is_read() {
  OpaqueEditorFlag receiver{};
  receiver.byte_04f = 0x00U;
  for (std::size_t index = 0; index < sizeof(receiver.opaque_000); ++index) {
    receiver.opaque_000[index] = 0xffU;
  }
  assert(FUN_004adc40(&receiver) == 0x00U);

  // The declared extent ends at 0x4f, so the bytes past it are placed in a
  // larger buffer to confirm the body does not read them.
  std::array<Byte, sizeof(OpaqueEditorFlag) + 8> arena{};
  arena.fill(0xffU);
  auto* front = reinterpret_cast<OpaqueEditorFlag*>(arena.data());
  static_assert(alignof(OpaqueEditorFlag) <= alignof(std::max_align_t),
                "the arena must satisfy the receiver alignment");
  front->byte_04f = 0x00U;
  assert(FUN_004adc40(front) == 0x00U);
  front->byte_04f = 0xffU;
  assert(FUN_004adc40(front) == 0xffU);
}

// -- pointer vs pointee. The body reloads the spilled receiver into EAX and
// then dereferences it at +0x4f, so three different answers are available from
// the shape of the listing alone: the byte, the receiver pointer, or the address
// of the slot. The seeded byte is chosen so that it differs from the low byte of
// the receiver's own address, which makes all three distinguishable, and the
// little-endian dword that a word-wide read would produce is computed here so
// that answer is distinguishable too.
void expect_byte_and_not_pointer_or_word() {
  std::array<Byte, 0x60> arena{};
  for (std::size_t index = 0; index < arena.size(); ++index) {
    arena[index] = static_cast<Byte>(0x11u * (index + 1u));
  }
  auto* const receiver = reinterpret_cast<OpaqueEditorFlag*>(arena.data());
  const auto address_byte = static_cast<Field>(
      static_cast<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(receiver)) &
      0xffu);
  // A value that is neither the receiver's own low address byte nor zero.
  const Field planted = static_cast<Field>(address_byte ^ 0xffu);
  arena[kObservedDisplacement] = planted;

  // What a dword read at 0x4c..0x4f would have produced, little-endian.
  std::uint32_t word = 0;
  std::memcpy(&word, arena.data() + 0x4c, sizeof(word));
  const auto word_low = static_cast<Field>(word & 0xffu);
  check(arena[0x4c] != 0x00u && arena[0x4d] != 0x00u && arena[0x4e] != 0x00u,
        "precondition: the three bytes below the displacement are non-zero, so "
        "a word-wide read could not agree with a byte-wide one");

  const Field observed = FUN_004adc40(receiver);

  check(observed == planted, "the result is the byte stored at receiver+0x4f");
  check(observed != address_byte,
        "the result is not the receiver's own low address byte");
  check(observed != word_low || arena[0x4c] == 0x00u,
        "the result is the low byte alone, not a dword read folded down");
  check(observed != 0x00u, "a stored zero is the only way to get zero back");
}

// -- displacement, not a member and not a run: the same three bytes seeded at
// two different displacements of a wider arena must produce two different
// answers, and every byte outside the one displacement must be untouched.
void expect_displacement_is_one_byte_at_one_offset() {
  std::array<Byte, 0x80> arena{};
  arena.fill(0x00u);
  auto* const receiver = reinterpret_cast<OpaqueEditorFlag*>(arena.data());
  const std::array<Byte, 0x80> before = arena;

  arena[kObservedDisplacement] = 0x5au;
  check(FUN_004adc40(receiver) == 0x5au,
        "the byte planted at 0x4f comes back");
  arena[kObservedDisplacement] = 0xa5u;
  check(FUN_004adc40(receiver) == 0xa5u,
        "moving the planted byte within the same displacement moves the answer");

  std::size_t moved = 0;
  for (std::size_t index = 0; index < arena.size(); ++index) {
    if (index == kObservedDisplacement) {
      continue;
    }
    if (arena[index] != before[index]) {
      ++moved;
    }
  }
  check(moved == 0, "the body writes nothing: no other byte of the receiver may "
                    "change across repeated calls");
}

// -- there is no guard in the original, so the load faults
[[noreturn]] void run_invalid_access(InvalidReceiver invalid) {
  auto* receiver = invalid == InvalidReceiver::null_receiver
                       ? nullptr
                       : reinterpret_cast<OpaqueEditorFlag*>(std::uintptr_t{1});
  const volatile Field result = FUN_004adc40(receiver);
  _exit(result == 0 ? 2 : 3);
}

void expect_segmentation_fault(InvalidReceiver invalid) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    run_invalid_access(invalid);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void run() {
  expect_returned_bytes();
  expect_only_byte_04f_is_read();
  expect_byte_and_not_pointer_or_word();
  expect_displacement_is_one_byte_at_one_offset();
  expect_segmentation_fault(InvalidReceiver::null_receiver);
  expect_segmentation_fault(InvalidReceiver::near_null_receiver);

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    std::abort();
  }
}

}  // namespace

int main() { run(); }
