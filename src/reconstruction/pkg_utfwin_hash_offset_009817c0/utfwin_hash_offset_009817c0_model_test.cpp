// Focused semantic test for 0x009817c0
// (UTFWin hash -> member-offset resolver) and its tail-call target 0x00951240.
//
// Every assertion below is derived from the observed disassembly recorded in
// utfwin_hash_offset_009817c0.cpp. Nothing here asserts a field name or a
// declared type: the receiver is only ever tested and offset.

#include <cstdio>
#include <cstring>
#include <initializer_list>

#include "utfwin_hash_offset_009817c0.hpp"

namespace {

using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::kHash_6ec581fd;
using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::kHash_ee3f516e;
using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::kHash_eec58382;
using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::kHash_eef3af8cu;
using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::set_image_009817c0;
using openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::
    sibling_hash_offset_00951240;

int g_failures = 0;

void check(bool ok, const char* what) {
  if (!ok) {
    std::printf("FAIL: %s\n", what);
    ++g_failures;
  } else {
    std::printf("ok:   %s\n", what);
  }
}

// A receiver large enough that every offset the model can return is inside it.
// The model only ever offsets the address, so the test drives it through a
// char* alias and keeps a separate byte view for the write-detection check.
alignas(16) unsigned char g_receiver_bytes[64];
char* const g_receiver = reinterpret_cast<char*>(g_receiver_bytes);

void* expected(void* self, std::ptrdiff_t offset) {
  return static_cast<char*>(self) + offset;
}

// Locally handled keys, 0x009817c0 CMP immediates with their LEA displacements.
void test_local_offsets() {
  check(set_image_009817c0(g_receiver, kHash_eec58382) ==
            expected(g_receiver, 0x04),
        "0xeec58382 resolves to receiver + 0x04");
  check(set_image_009817c0(g_receiver, kHash_eef3af8cu) ==
            expected(g_receiver, 0x0c),
        "0xeef3af8c resolves to receiver + 0x0c");
}

// Both locally handled arms are preceded by TEST ECX,ECX, so a null receiver
// must produce the XOR EAX,EAX result rather than a wrapped offset.
void test_null_receiver_is_rejected_locally() {
  check(set_image_009817c0(nullptr, kHash_eec58382) == nullptr,
        "null receiver with 0xeec58382 yields null");
  check(set_image_009817c0(nullptr, kHash_eef3af8cu) == nullptr,
        "null receiver with 0xeef3af8c yields null");
}

// The tail call at 0x009817d6 keeps the receiver in ECX, so the sibling's
// null-handling is what a caller observes for the delegated keys.
void test_delegated_keys() {
  check(set_image_009817c0(g_receiver, kHash_ee3f516e) ==
            expected(g_receiver, 0x04),
        "0xee3f516e delegates to the sibling and resolves to + 0x04");
  check(set_image_009817c0(g_receiver, kHash_6ec581fd) ==
            expected(g_receiver, 0x00),
        "0x6ec581fd delegates to the sibling and returns the bare receiver");
  check(set_image_009817c0(nullptr, kHash_ee3f516e) == nullptr,
        "null receiver with 0xee3f516e yields null");
  check(set_image_009817c0(nullptr, kHash_6ec581fd) == nullptr,
        "null receiver with 0x6ec581fd yields the bare null receiver");
}

// An unrecognised key falls off both comparison chains into XOR EAX,EAX.
void test_unknown_key_returns_null() {
  check(set_image_009817c0(g_receiver, 0x00000000u) == nullptr,
        "hash 0 is not a key and yields null");
  check(set_image_009817c0(g_receiver, 0xffffffffu) == nullptr,
        "hash 0xffffffff is not a key and yields null");
  check(set_image_009817c0(g_receiver, 0xeec58383u) == nullptr,
        "a key one above 0xeec58382 is not a key and yields null");
  check(set_image_009817c0(g_receiver, 0xeef3af8du) == nullptr,
        "a key one above 0xeef3af8c is not a key and yields null");
}

// 0x00951240 is only reachable through the tail call, so the table it completes
// is asserted directly against the sibling entry point as well.
void test_sibling_table_directly() {
  check(sibling_hash_offset_00951240(g_receiver, kHash_6ec581fd) ==
            expected(g_receiver, 0x00),
        "sibling: 0x6ec581fd returns the bare receiver");
  check(sibling_hash_offset_00951240(g_receiver, kHash_ee3f516e) ==
            expected(g_receiver, 0x04),
        "sibling: 0xee3f516e resolves to + 0x04");
  check(sibling_hash_offset_00951240(g_receiver, kHash_eec58382) ==
            expected(g_receiver, 0x04),
        "sibling: 0xeec58382 shares the +0x04 block with 0xee3f516e");
  check(sibling_hash_offset_00951240(g_receiver, 0x12345678u) == nullptr,
        "sibling: an unrecognised key yields null");
  check(sibling_hash_offset_00951240(nullptr, kHash_eec58382) == nullptr,
        "sibling: null receiver is rejected for +0x04 keys");
  check(sibling_hash_offset_00951240(nullptr, kHash_6ec581fd) == nullptr,
        "sibling: the +0x00 key has no null guard and returns the bare null");
}

// The body only performs TEST and LEA on the receiver, so it must not write.
void test_receiver_is_never_written() {
  for (std::size_t i = 0; i < sizeof(g_receiver_bytes); ++i) {
    g_receiver_bytes[i] = static_cast<unsigned char>(0xa0 + (i & 0x0f));
  }
  unsigned char before[sizeof(g_receiver_bytes)];
  std::memcpy(before, g_receiver_bytes, sizeof(before));

  const std::uint32_t keys[] = {kHash_6ec581fd,  kHash_ee3f516e, kHash_eec58382,
                                kHash_eef3af8cu, 0x00000000u,    0xdeadbeefu};
  for (std::uint32_t key : keys) {
    (void)set_image_009817c0(g_receiver, key);
    (void)sibling_hash_offset_00951240(g_receiver, key);
  }

  check(std::memcmp(before, g_receiver_bytes, sizeof(before)) == 0,
        "no receiver word is written by any key on either entry point");
}

// The result must always be one of: null, the receiver, or receiver + a proven
// offset. Anything else would mean an invented offset crept into the model.
void test_results_are_null_or_proven_offsets() {
  const std::ptrdiff_t allowed[] = {0x00, 0x04, 0x0c};
  for (std::uint32_t i = 0; i < 64u; ++i) {
    const std::uint32_t key = 0xeec58300u + i;
    char* got = static_cast<char*>(set_image_009817c0(g_receiver, key));
    if (got == nullptr) {
      continue;
    }
    const std::ptrdiff_t delta = got - g_receiver;
    bool ok = false;
    for (std::ptrdiff_t candidate : allowed) {
      ok = ok || (delta == candidate);
    }
    if (!ok) {
      std::printf("FAIL: key 0x%08x produced offset %td\n", key, delta);
      ++g_failures;
      return;
    }
  }
  std::printf(
      "ok:   every non-null result is the receiver or a proven offset\n");
}

// An independent transcription of 0x009817c0 straight from the disassembly
// listing, deliberately written as a flat if-chain with no shared code and no
// helper, so it shares no structure with the reconstruction under test.
//
//   MOV EAX,[ESP+4] ; CMP EAX,0xeec58382 ; JZ L_4
//                   ; CMP EAX,0xeef3af8c ; JZ L_c
//                   ; JMP 0x00951240
//   L_c: TEST ECX,ECX ; JZ L_null ; LEA EAX,[ECX+0xc] ; RET 0x4
//   L_4: TEST ECX,ECX ; JZ L_null ; LEA EAX,[ECX+0x4] ; RET 0x4
//   L_null: XOR EAX,EAX ; RET 0x4
void* reference_009817c0(void* self, std::uint32_t hash) {
  if (hash == 0xeec58382u) {
    if (self == nullptr) {
      return nullptr;
    }
    return static_cast<char*>(self) + 4;
  }
  if (hash == 0xeef3af8cu) {
    if (self == nullptr) {
      return nullptr;
    }
    return static_cast<char*>(self) + 0xc;
  }
  // Tail call to 0x00951240, transcribed inline:
  //   CMP ECX,0x6ec581fd ; JZ -> RET with EAX = the bare receiver
  //   CMP ECX,0xee3f516e ; JZ -> +4 if receiver non-null
  //   CMP ECX,0xeec58382 ; JNZ -> null
  //   -> +4 if receiver non-null
  if (hash == 0x6ec581fdu) {
    return self;
  }
  if (hash == 0xee3f516eu || hash == 0xeec58382u) {
    if (self == nullptr) {
      return nullptr;
    }
    return static_cast<char*>(self) + 4;
  }
  return nullptr;
}

// Differential sweep: the model must agree with the transcription on every key
// in a range that brackets all four constants, on both a live and a null
// receiver. The four keys and their immediate neighbours are covered
// explicitly, because a one-off boundary error in a comparison would hide in a
// random sweep.
void test_differential_against_transcription() {
  const std::uint32_t keys[] = {0x6ec581fd, 0x6ec581fc, 0x6ec581fe, 0xee3f516e,
                                0xee3f516d, 0xee3f516f, 0xeec58382, 0xeec58381,
                                0xeec58383, 0xeef3af8c, 0xeef3af8b, 0xeef3af8d,
                                0x00000000, 0xffffffff};
  for (std::uint32_t key : keys) {
    if (set_image_009817c0(g_receiver, key) !=
        reference_009817c0(g_receiver, key)) {
      std::printf("FAIL: live receiver, key 0x%08x\n", key);
      ++g_failures;
      return;
    }
    if (set_image_009817c0(nullptr, key) != reference_009817c0(nullptr, key)) {
      std::printf("FAIL: null receiver, key 0x%08x\n", key);
      ++g_failures;
      return;
    }
  }
  // Dense sweep across the whole neighbourhood of every constant.
  for (std::uint32_t base :
       {0x6ec581fdu, 0xee3f516eu, 0xeec58382u, 0xeef3af8cu}) {
    for (std::uint32_t delta = 0; delta < 32u; ++delta) {
      const std::uint32_t key = base - 16u + delta;
      if (set_image_009817c0(g_receiver, key) !=
              reference_009817c0(g_receiver, key) ||
          set_image_009817c0(nullptr, key) !=
              reference_009817c0(nullptr, key)) {
        std::printf("FAIL: sweep key 0x%08x\n", key);
        ++g_failures;
        return;
      }
    }
  }
  std::printf(
      "ok:   model matches the independent transcription on 142 keys\n");
}

}  // namespace

int main() {
  static_assert(sizeof(void*) == 4, "x86-32 pointer width is required");
  static_assert(sizeof(std::uint32_t) == 4, "hash key is a 32-bit word");
  static_assert(
      sizeof(openspore::reconstruction::pkg_utfwin_hash_offset_009817c0::HashWord) == 4,
      "modelled hash key width matches the 32-bit CMP immediates");

  test_local_offsets();
  test_null_receiver_is_rejected_locally();
  test_delegated_keys();
  test_unknown_key_returns_null();
  test_sibling_table_directly();
  test_receiver_is_never_written();
  test_results_are_null_or_proven_offsets();
  test_differential_against_transcription();

  if (g_failures != 0) {
    std::printf("\n%d check(s) FAILED\n", g_failures);
    return 1;
  }
  std::printf("\nall checks passed\n");
  return 0;
}
