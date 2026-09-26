// Focused model test for 0x004adc40.
//
// It pins the claims this package makes and nothing more. In particular it
// pins the low byte of the result and the read-only property; it deliberately
// does NOT pin EAX bits 8..31, because a C++ std::uint8_t return zero-extends
// while the original left those bits equal to receiver address bits 8..31.

#include "adc40_smoke01.hpp"

#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace osr = openspore::reconstruction::pkg_editor_adc40_smoke01;

namespace {

int g_failures = 0;

void report(const char* name, bool ok, const char* detail) {
  std::printf("[%s] %s%s%s\n", ok ? "PASS" : "FAIL", name,
              detail ? " -- " : "", detail ? detail : "");
  if (!ok) ++g_failures;
}

// Builds a receiver whose field byte is `field` and whose every other declared
// byte is the poison value, so any read outside the declared field shows up.
osr::OpaqueEditorFlag make_receiver(osr::Byte field, osr::Byte poison) {
  osr::OpaqueEditorFlag object;
  std::memset(&object, poison, sizeof(object));
  object.byte_04f = field;
  return object;
}

void test_all_256_values_round_trip() {
  int bad = 0;
  osr::Byte first_bad = 0;
  for (unsigned value = 0; value <= 0xffu; ++value) {
    osr::OpaqueEditorFlag object = make_receiver(
        static_cast<osr::Byte>(value), static_cast<osr::Byte>(0xa5u));
    const osr::Byte got = osr::FUN_004adc40(&object);
    if (got != static_cast<osr::Byte>(value)) {
      if (bad == 0) first_bad = static_cast<osr::Byte>(value);
      ++bad;
    }
  }
  char detail[96];
  std::snprintf(detail, sizeof(detail), "%d of 256 mismatched", bad);
  (void)first_bad;
  report("exhaustive_byte_sweep_all_256_values", bad == 0, detail);
}

// 0x80 and 0xff must come back unchanged: a signed or narrowed read would
// report them as negative or truncated.
void test_high_bit_values_are_unsigned() {
  osr::OpaqueEditorFlag object = make_receiver(0xffu, 0x00u);
  const osr::Byte got = osr::FUN_004adc40(&object);
  report("high_bit_0xff_returned_unsigned", got == 0xffu, "expect 0xff");
}

void test_call_is_read_only() {
  osr::OpaqueEditorFlag object = make_receiver(0x3cu, 0x5au);
  osr::OpaqueEditorFlag before = object;
  (void)osr::FUN_004adc40(&object);
  report("call_does_not_mutate_receiver",
         std::memcmp(&before, &object, sizeof(object)) == 0, "byte-for-byte");
}

// With every byte below 0x4f poisoned and the field zeroed, the result must be
// 0x00: the body must read offset 0x4f and nothing else.
void test_reads_only_offset_0x4f() {
  osr::OpaqueEditorFlag object = make_receiver(0x00u, 0xffu);
  const osr::Byte got = osr::FUN_004adc40(&object);
  report("offset_isolation_below_0x4f_poisoned",
         got == 0x00u, "expect 0x00 with 0xff padding");
}

// A larger arena proves the result tracks only byte 0x4f and does not depend on
// bytes past the declared extent of 0x50.
void test_ignores_bytes_past_declared_extent() {
  alignas(4) std::uint8_t arena[0x200];
  std::memset(arena, 0xff, sizeof(arena));
  osr::OpaqueEditorFlag* object = reinterpret_cast<osr::OpaqueEditorFlag*>(arena);
  object->byte_04f = 0x11u;
  const osr::Byte got = osr::FUN_004adc40(object);
  report("bytes_past_declared_extent_ignored", got == 0x11u, "expect 0x11");
}

void test_offset_assertion_holds() {
  report("offsetof_byte_04f_is_0x4f",
         offsetof(osr::OpaqueEditorFlag, byte_04f) == 0x4fu, "static_assert");
}

// No guard exists in the body, so a null receiver faults. Run in a child so the
// SIGSEGV does not take the test process with it.
void test_null_receiver_faults() {
  std::fflush(stdout);
  const pid_t pid = fork();
  if (pid == 0) {
    // The fault is the expected result, so the call is made for its side effect
    // of dereferencing rather than for a value.
    osr::OpaqueEditorFlag* receiver = nullptr;
    (void)osr::FUN_004adc40(receiver);
    _exit(0);
  }
  int status = 0;
  waitpid(pid, &status, 0);
  const bool signalled = WIFSIGNALED(status);
  report("null_receiver_faults_no_guard", signalled,
         signalled ? "child died on a signal" : "child exited normally");
}

}  // namespace

int main() {
  test_offset_assertion_holds();
  test_all_256_values_round_trip();
  test_high_bit_values_are_unsigned();
  test_call_is_read_only();
  test_reads_only_offset_0x4f();
  test_ignores_bytes_past_declared_extent();
  test_null_receiver_faults();

  std::printf("%s: %d failure(s)\n", g_failures == 0 ? "OK" : "NOT OK",
              g_failures);
  return g_failures == 0 ? 0 : 1;
}
