// Model test for 0x004adc40 (PKG-EDITOR-ADC40-FLAG).
//
// What the binary evidence fixes, and what this test therefore pins:
//
//   004adc4a  8a 40 4f   mov al, byte ptr [eax+0x4f]   one BYTE at +0x4f
//   004adc50  c3         ret                            caller owns cleanup
//
// so: the value is the single byte at receiver+0x4f; the load is byte-wide and
// no neighbouring byte participates; nothing is written back; the receiver is
// never null-checked, so a null or near-null receiver faults.
//
// Deliberately NOT asserted: that the upper 24 bits of EAX come back equal to
// the receiver address bits 8..31. The original only writes AL, but a C++
// function returning std::uint8_t is free to zero-extend, and that register
// detail is recorded in the source comment rather than pinned by a test.
//
// Build (x86-32):
//   g++ -m32 -std=c++17 -Wall -Wextra -O2 adc40_flag.cpp
//       adc40_flag_model_test.cpp -o adc40_flag_model_test
//   ./adc40_flag_model_test && echo PASS

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "adc40_flag.hpp"

namespace {

using openspore::reconstruction::pkg_editor_adc40_flag::Byte;
using openspore::reconstruction::pkg_editor_adc40_flag::Field;
using openspore::reconstruction::pkg_editor_adc40_flag::FUN_004adc40;
using openspore::reconstruction::pkg_editor_adc40_flag::OpaqueEditorFlag;

static_assert(sizeof(OpaqueEditorFlag) >= 0x50,
              "the observed load requires a 0x50-byte receiver prefix");

enum class InvalidReceiver { null_receiver, near_null_receiver };

void store_field(OpaqueEditorFlag& receiver, Field value) {
  receiver.byte_04f = value;
}

// -- the byte at receiver+0x4f is returned, exhaustively, and the receiver is
// left byte-for-byte identical
void expect_returned_bytes() {
  OpaqueEditorFlag receiver{};
  for (std::size_t index = 0; index < sizeof(receiver.opaque_000); ++index) {
    receiver.opaque_000[index] = static_cast<Byte>(index * 7U + 3U);
  }

  for (std::uint32_t raw = 0; raw <= 0xffU; ++raw) {
    store_field(receiver, static_cast<Field>(raw));
    assert(FUN_004adc40(&receiver) == static_cast<Field>(raw));
  }

  // 0x80 and 0xff are the values a signed reading of the byte would get wrong.
  store_field(receiver, 0x80U);
  assert(FUN_004adc40(&receiver) == 0x80U);
  store_field(receiver, 0xffU);
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
  expect_segmentation_fault(InvalidReceiver::null_receiver);
  expect_segmentation_fault(InvalidReceiver::near_null_receiver);
}

}  // namespace

int main() { run(); }
