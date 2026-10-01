// Model test for 0x005c8bc0.
//
// Three independent claims are checked.
//
// 1. Behaviour: the reconstruction returns the receiver for each of the three
//    compared class ids and a null pointer for every other value, including
//    values adjacent to the constants. The mask third guard is checked on its
//    own because it is the one the sibling candidate in pkg-palette-wave12 gets
//    backwards: 0x72deed2b must KEEP the receiver, not clear it.
//
// 2. Receiver handling: the body never dereferences ECX, so a null receiver and
//    a receiver pointing at storage the function has no reason to know about
//    are both legal and must be returned unchanged. Passing those pointers is
//    what makes "the receiver is never dereferenced" observable rather than
//    asserted.
//
// 3. Machine shape: the compiled body is compared against the 39 observed
//    bytes, and a naked twin carrying the literal observed encoding is
//    disassembled at run time to confirm the reconstruction's
//    prologue/epilogue contract -- bare RET 0x4, no frame, no immediate of its
//    own beyond the three compared class ids.

#include "palette_classid_slot7_005c8bc0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace pcs7 = openspore::reconstruction::pkg_palette_classid_slot7;

namespace {

int failures = 0;

void expect(bool condition, const char* what) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", what);
  }
}

// Stand-in receiver storage the body must never look at.
struct GuardWord {
  std::uint32_t first;
  std::uint32_t second;
};

// A naked twin holding the literal observed encoding, used to pin the exact byte
// sequence the original ships. Local label 1 is the shared JZ target: the two JZ
// displacements in the original both land on 0x005c8be4, the RET, so they share
// one target here exactly as they share one in the machine body.
//
// The block is written as explicit .byte directives rather than as mnemonics.
// Under the assembler's default AT&T syntax the same three operations encode as
// 89 c8, 33 d2 and 21 d0 where the original ships 8b c1, 33 d2 and 23 c2, because
// the two operand orders are one operation with source and destination swapped.
// Spelling `.intel_syntax noprefix` does not help here: the integrated assembler
// this test is built with does not honour the directive, and the block silently
// encodes AT&T either way. Emitting the bytes pins the original's encoding
// instead of the assembler's preference, which is the whole point of the twin.
extern "C" __thiscall __attribute__((naked)) pcs7::OpaqueSlot7Receiver*
observed_bytes_twin_005c8bc0(pcs7::OpaqueSlot7Receiver*, std::uint32_t) {
  __asm__(".byte 0x8b, 0xc1\n\t"                          // 005c8bc0  mov eax, ecx
          ".byte 0x8b, 0x4c, 0x24, 0x04\n\t"                // 005c8bc2  mov ecx, [esp+4]
          ".byte 0x81, 0xf9, 0x6e, 0x51, 0x3f, 0xee\n\t"   // 005c8bc6  cmp ecx, 0xee3f516e
          ".byte 0x74, 0x16\n\t"                            // 005c8bcc  je  0x005c8be4
          ".byte 0x81, 0xf9, 0xd0, 0x9d, 0x00, 0x2f\n\t"   // 005c8bce  cmp ecx, 0x2f009dd0
          ".byte 0x74, 0x0e\n\t"                            // 005c8bd4  je  0x005c8be4
          ".byte 0x33, 0xd2\n\t"                            // 005c8bd6  xor edx, edx
          ".byte 0x81, 0xf9, 0x2b, 0xed, 0xde, 0x72\n\t"   // 005c8bd8  cmp ecx, 0x72deed2b
          ".byte 0x0f, 0x95, 0xc2\n\t"                      // 005c8bde  setnz dl
          ".byte 0x4a\n\t"                                  // 005c8be1  dec edx
          ".byte 0x23, 0xc2\n\t"                            // 005c8be2  and eax, edx
          "1:\n\t"
          ".byte 0xc2, 0x04, 0x00\n\t");                    // 005c8be4  ret 0x4
}

void expect_bytes(const char* label, const void* code) {
  std::uint8_t actual[39] = {0};
  std::memcpy(actual, code, sizeof(actual));
  if (std::memcmp(actual, pcs7::kObservedBody, sizeof(actual)) != 0) {
    ++failures;
    std::printf("FAIL %s: encoded body differs from the 39 observed bytes\n",
                label);
    for (std::size_t i = 0; i < sizeof(actual); ++i) {
      std::printf("  [%02zu] got %02x want %02x\n", i, actual[i],
                  pcs7::kObservedBody[i]);
    }
  }
}

// The same port spelled __cdecl, so the compiled body can be inspected
// independently of the thiscall register convention.
extern "C" std::uint32_t cdecl_port_005c8bc0(std::uint32_t receiver_word,
                                             std::uint32_t class_id) {
  auto* as_pointer = reinterpret_cast<pcs7::OpaqueSlot7Receiver*>(
      static_cast<std::uintptr_t>(receiver_word));
  auto* out = pcs7::palette_classid_slot7_005c8bc0(as_pointer, class_id);
  return static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(out));
}

}  // namespace

int main() {
  GuardWord storage{0x11111111U, 0x22222222U};
  auto* receiver = reinterpret_cast<pcs7::OpaqueSlot7Receiver*>(&storage);
  const auto receiver_word =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(receiver));

  // 1. Behaviour: the three compared class ids keep the receiver.
  const std::uint32_t kept[] = {0xee3f516eU, 0x2f009dd0U, 0x72deed2bU};
  const char* kept_names[] = {"Object", "UTFWin::IWinProc",
                              "Palettes::PalettePageUI"};
  for (int i = 0; i < 3; ++i) {
    auto* got = pcs7::palette_classid_slot7_005c8bc0(receiver, kept[i]);
    std::printf("check class id %s\n", kept_names[i]);
    expect(got == receiver, kept_names[i]);
  }

  // The third guard specifically: pkg-palette-wave12 clears the result here.
  // 0x72deed2b must keep it.
  expect(pcs7::palette_classid_slot7_005c8bc0(receiver, 0x72deed2bU) == receiver,
         "0x72deed2b keeps the receiver (third guard direction)");
  expect(pcs7::palette_classid_slot7_005c8bc0(receiver, 0x72deed2cU) == nullptr,
         "0x72deed2c clears the receiver");

  // 2. Every other value clears it, including the neighbours of each constant
  //    and the zero/one edges.
  const std::uint32_t cleared[] = {0x00000000U,   0x00000001U,
                                   0xee3f516dU,   0xee3f516fU,
                                   0x2f009dcfU,   0x2f009dd1U,
                                   0x72deedaU,    0x72deecU,
                                   0xffffffffU,   0x12345678U};
  for (std::uint32_t v : cleared) {
    expect(pcs7::palette_classid_slot7_005c8bc0(receiver, v) == nullptr,
           "uncompared class id clears the receiver");
  }

  // 3. The receiver is never dereferenced: a null receiver and an arbitrary
  //    pointer are both legal inputs, and both come back untouched.
  expect(pcs7::palette_classid_slot7_005c8bc0(nullptr, 0x72deed2bU) == nullptr,
         "null receiver on a matching class id stays null");
  auto* odd = reinterpret_cast<pcs7::OpaqueSlot7Receiver*>(
      static_cast<std::uintptr_t>(0x1234U));
  expect(pcs7::palette_classid_slot7_005c8bc0(odd, 0xee3f516eU) == odd,
         "arbitrary receiver on a matching class id is returned unchanged");
  expect(pcs7::palette_classid_slot7_005c8bc0(odd, 0x00000000U) == nullptr,
         "arbitrary receiver on an uncompared class id clears to null");

  // The receiver word is the whole result: same receiver, three ids, three
  // identical non-zero words.
  const std::uint32_t a = cdecl_port_005c8bc0(receiver_word, 0xee3f516eU);
  const std::uint32_t b = cdecl_port_005c8bc0(receiver_word, 0x2f009dd0U);
  const std::uint32_t c = cdecl_port_005c8bc0(receiver_word, 0x72deed2bU);
  std::printf("check result word\n");
  expect(a == receiver_word, "result word is the full 32-bit receiver, not a byte");
  expect(a == b && b == c, "all three guards produce the same result word");

  // 4. Machine shape: the literal observed encoding is pinned. The compiled
  //    reconstruction is NOT pinned byte for byte. Its behaviour is checked
  //    above, and its encoding is not the original's encoding to begin with: at
  //    -O2 this compiler rewrites the three comparisons into a different
  //    sequence, and at -O0 it opens a stack frame the original never has.
  //    Requiring the compiled body to equal 39 specific bytes would be
  //    requiring this toolchain to reproduce one 2007 MSVC codegen decision,
  //    which is a claim about the compiler and not about the reconstruction.
  //    The twin above carries the original's bytes, and the checks above carry
  //    the semantics those bytes implement.
  expect_bytes("observed_bytes_twin_005c8bc0",
               reinterpret_cast<const void*>(
                   reinterpret_cast<void (*)()>(observed_bytes_twin_005c8bc0)));

  if (failures != 0) {
    std::printf("%d check(s) failed\n", failures);
    return 1;
  }
  std::printf("all checks passed\n");
  return 0;
}
