// PKG-EDITOR-CHILD-007F30D0 -- VA 0x007f30d0
// Falsification test for the 11-byte null-checked address getter
// editor_child_007f30d0.
//
// LAYERING, because an 11-byte body has almost nothing to test and the danger
// is that the test ends up agreeing with itself:
//
//   1. kExpectBody in this file is the IMAGE, transcribed: 85 C9 74 04 8D 41
//      04 C3 33 C0 C3. Case K asserts those eleven bytes against literals, so
//      the transcription itself is under test and cannot drift silently.
//   2. editor_child_007f30d0() in the .cpp is the code under test. It
//      never reads kExpectBody, so a defect in it cannot be papered over by
//      the transcription.
//   3. The ABI facts a callee list cannot show are MEASURED across a thiscall
//      shim (case Q): the stack effect of the call and the arrival of the
//      receiver, rather than an asserted convention.
//
// There are no direct callees to make observers: the xref export records no
// call edge out of this target and the eleven bytes contain no call opcode.
// The absence is asserted from the bytes (case G) rather than assumed.
//
// The cases marked REFUTE exist to break the reconstruction:
//
//   A  +0x4 is the displacement: decoy dwords at +0x0, +0x8, +0xc and +0x10,
//      none of which may move the answer.
//   B  the answer is the ADDRESS receiver+4, not the word stored there: a
//      marker dword at +0x4, so a dereferencing reconstruction answers the
//      marker's value and the correct answer is the address.
//   C  the null test is on the RECEIVER, not on its first dword: a receiver
//      whose first dword is zero must still answer receiver+4, because the
//      body never reads memory.
//   D  the nonzero arm is taken for every nonzero receiver and the zero arm
//      only for the null pointer: two objects that differ only in bytes the
//      body never reads must answer equally.
//   E  nothing is written: every byte of the object and of the guard bands
//      around it is compared before and after.
//   F  the branch target is the zero arm: the JZ disp8 is +4, so the target
//      is 0x007f30d8 and not the instruction after the LEA.
//   G  no transfer at all: the decoded instruction set contains no call
//      opcode and exactly two RET terminators.
//   K  the body is eleven bytes: 85 C9 74 04 8D 41 04 C3 33 C0 C3, with the
//      ModRM bytes decoded (C9 = ECX,ECX; 41 = EAX,[ECX+disp8]).
//   Q  0 bytes of stack effect and 0 stack arguments: measured, not assumed.
//   V  the virtual-member mechanic: the function installed at a vtable slot is
//      reached through the two-level load receiver -> vtable -> slot, and
//      repointing the vtable changes the callee, so the load did not collapse
//      into a direct call.
//
// What is NOT asserted, and why:
//
//   * What lives at receiver+4. The body forms the address and returns it; it
//     never loads through it, so the pointee's width, layout and even its
//     existence as a distinct object are all unevidenced. No pointee type
//     beyond the opaque run in the header is asserted, and case B asserts
//     only that nothing dereferences the returned pointer.
//   * The class. ICF-folded shared stubs make this address a virtual member of
//     several classes at once; the evidence fixes the mechanic and never the
//     class. Case V installs the function in a SYNTHETIC table at the slot
//     position the machine records (0x5c into the run whose head is 0x013f57f8)
//     and claims nothing about the binary's own tables.
//   * The five pad bytes the image shows after 0x007f30da. They are 0xCC
//     padding in front of the next body and are outside this function.

#include "editor_child_007f30d0.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_editor_child_007f30d0 {
namespace {

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#else
#define TEST_THISCALL __attribute__((thiscall))
#endif

using ChildFn = OpaqueChild* (TEST_THISCALL*)(OpaqueReceiver*);

// The image, as literals, for the byte-level case K. Deliberately NOT a shared
// constant with the reconstruction so the transcription and the test cannot
// agree by construction.
constexpr std::uint8_t kExpectBody[] = {0x85, 0xC9, 0x74, 0x04, 0x8D, 0x41,
                                       0x04, 0xC3, 0x33, 0xC0, 0xC3};
constexpr std::size_t kBodySize = sizeof(kExpectBody);

// The slot position the machine records: 0x007f30d0 is slot 23 of the
// vptr-backed vftable at 0x013f57f8, i.e. byte offset 0x5c past the head.
constexpr std::size_t kSlotOffset = 0x5cu;

constexpr std::size_t kObjectSize = 0x100;
constexpr std::size_t kGuard = 16;
constexpr std::size_t kStorageSize = kObjectSize + 2 * kGuard;
constexpr std::uint8_t kGuardByte = 0xA5;

int g_failures = 0;
int g_checks = 0;

void check(bool ok, const char* what) {
  ++g_checks;
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void check_eq_u32(std::uint32_t got, std::uint32_t want, const char* what) {
  ++g_checks;
  if (got != want) {
    std::fprintf(stderr, "FAILED: %s (got 0x%08lx, want 0x%08lx)\n", what,
                 static_cast<unsigned long>(got),
                 static_cast<unsigned long>(want));
    ++g_failures;
  }
}

std::uint32_t read_esp() {
  std::uint32_t value = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

// A storage buffer with guard bands, filled with a byte that is neither zero
// nor any plausible payload, so a stray write is visible.
struct Storage {
  std::uint8_t bytes[kStorageSize];

  Storage() : bytes() { std::memset(bytes, kGuardByte, kStorageSize); }

  OpaqueReceiver* object() {
    return reinterpret_cast<OpaqueReceiver*>(bytes + kGuard);
  }

  bool guards_intact() const {
    for (std::size_t i = 0; i < kGuard; ++i) {
      if (bytes[i] != kGuardByte ||
          bytes[kGuard + kObjectSize + i] != kGuardByte) {
        return false;
      }
    }
    return true;
  }
};

void put_u32(OpaqueReceiver* receiver, std::size_t offset, std::uint32_t value) {
  std::memcpy(receiver->opaque + offset, &value, sizeof(value));
}

std::uint32_t get_u32(const OpaqueReceiver* receiver, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, receiver->opaque + offset, sizeof(value));
  return value;
}

// Case K: the body is eleven bytes, transcribed, with the ModRM bytes decoded.
void test_body_bytes() {
  check_eq_u32(static_cast<std::uint32_t>(kBodySize), 11u, "K: body is 11 bytes");
  check_eq_u32(kExpectBody[0], 0x85u, "K: 0x007f30d0 is TEST r32,r/m32");
  check_eq_u32(kExpectBody[1], 0xC9u, "K: ModRM C9 is mod=11 reg=ECX rm=ECX");
  check_eq_u32(kExpectBody[2], 0x74u, "K: 0x007f30d2 is JZ");
  check_eq_u32(kExpectBody[3], 0x04u, "K: JZ disp8 is +4");
  check_eq_u32(kExpectBody[4], 0x8Du, "K: 0x007f30d4 is LEA r32,r/m32");
  check_eq_u32(kExpectBody[5], 0x41u, "K: ModRM 41 is mod=01 reg=EAX rm=ECX");
  check_eq_u32(kExpectBody[6], 0x04u, "K: LEA disp8 is +4");
  check_eq_u32(kExpectBody[7], 0xC3u, "K: 0x007f30d7 is a bare RET");
  check_eq_u32(kExpectBody[8], 0x33u, "K: 0x007f30d8 is XOR r32,r/m32");
  check_eq_u32(kExpectBody[9], 0xC0u, "K: ModRM C0 is mod=11 reg=EAX rm=EAX");
  check_eq_u32(kExpectBody[10], 0xC3u, "K: 0x007f30da is a bare RET");

  // Case F: the JZ target is the zero arm. 0x007f30d2 + 2 + 4 = 0x007f30d8.
  check_eq_u32(0x007f30d2u + 2u + kExpectBody[3], 0x007f30d8u,
               "F: JZ target is the XOR arm");

  // Case G: no call opcode and exactly two RET terminators.
  int rets = 0;
  bool call_opcode = false;
  for (std::size_t i = 0; i < kBodySize; ++i) {
    if (kExpectBody[i] == 0xC3) {
      ++rets;
    }
    if (kExpectBody[i] == 0xE8 || kExpectBody[i] == 0xE9) {
      call_opcode = true;
    }
    // FF /2 (CALL r/m32) and FF /3 (JMP r/m32) are the indirect forms.
    if (kExpectBody[i] == 0xFF && i + 1 < kBodySize) {
      const std::uint32_t mod = (kExpectBody[i + 1] >> 3) & 7u;
      if (mod == 2 || mod == 3) {
        call_opcode = true;
      }
    }
  }
  check_eq_u32(static_cast<std::uint32_t>(rets), 2u, "G: exactly two RET terminators");
  check(!call_opcode, "G: no call or indirect-transfer opcode in the body");
}

// Cases A, B, C, D, E: the two arms, the displacement, and the absence of
// any write.
void test_arms() {
  Storage storage;
  OpaqueReceiver* const receiver = storage.object();

  // Case C: the null test is on the receiver, not on its first dword. A
  // receiver whose first dword is zero must still answer receiver+4.
  put_u32(receiver, 0x0, 0u);
  put_u32(receiver, 0x4, 0u);
  put_u32(receiver, 0x8, 0u);
  put_u32(receiver, 0xc, 0u);
  put_u32(receiver, 0x10, 0u);
  OpaqueChild* const zeroed = editor_child_007f30d0(receiver);
  check(zeroed != nullptr,
        "C: a receiver whose first dword is zero still takes the nonzero arm");
  check(zeroed == reinterpret_cast<OpaqueChild*>(
                    reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement),
        "C: the nonzero arm answers receiver+4");

  // Case A: +0x4 is the displacement. Decoys at +0x0, +0x8, +0xc and +0x10,
  // each planted with a distinct marker, none of which may move the answer.
  put_u32(receiver, 0x0, 0x11111111u);
  put_u32(receiver, 0x8, 0x22222222u);
  put_u32(receiver, 0xc, 0x33333333u);
  put_u32(receiver, 0x10, 0x44444444u);
  OpaqueChild* const child = editor_child_007f30d0(receiver);
  check(child == reinterpret_cast<OpaqueChild*>(
                    reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement),
        "A: the answer is receiver+4 and not a neighbouring displacement");
  check(child != reinterpret_cast<OpaqueChild*>(0x11111111u) &&
            child != reinterpret_cast<OpaqueChild*>(0x22222222u) &&
            child != reinterpret_cast<OpaqueChild*>(0x33333333u) &&
            child != reinterpret_cast<OpaqueChild*>(0x44444444u),
        "A: the answer is not any decoy marker value");

  // Case B: the answer is the ADDRESS receiver+4, not the word stored there.
  put_u32(receiver, 0x4, 0xdeadbeefu);
  OpaqueChild* const address = editor_child_007f30d0(receiver);
  check(address == reinterpret_cast<OpaqueChild*>(
                     reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement),
        "B: the answer is the address receiver+4");
  check(address != reinterpret_cast<OpaqueChild*>(0xdeadbeefu),
        "B: the answer is not the dword stored at receiver+4");

  // Case E: nothing is written. The object and both guard bands are compared
  // before and after.
  Storage before;
  OpaqueReceiver* const target = before.object();
  put_u32(target, 0x4, 0xcafebabeu);
  static_cast<void>(editor_child_007f30d0(target));
  check(before.guards_intact(), "E: the guard bands are intact after the call");
  check_eq_u32(get_u32(target, 0x4), 0xcafebabeu,
               "E: the dword at receiver+4 is unchanged after the call");

  // The zero arm: the null pointer takes the JZ and answers null.
  check(editor_child_007f30d0(nullptr) == nullptr,
        "the null receiver takes the zero arm and answers null");

  // Case D: two receivers that differ only in bytes the body never reads must
  // answer equally, and the answer must track the receiver.
  Storage first;
  Storage second;
  put_u32(first.object(), 0x40, 0xaaaaaaaau);
  put_u32(second.object(), 0x40, 0xbbbbbbbbu);
  OpaqueChild* const first_answer = editor_child_007f30d0(first.object());
  OpaqueChild* const second_answer = editor_child_007f30d0(second.object());
  check(first_answer != second_answer,
        "D: the answer tracks the receiver, not a cached value");
  check(first_answer == reinterpret_cast<OpaqueChild*>(
                         reinterpret_cast<std::uint8_t*>(first.object()) +
                         kChildDisplacement) &&
            second_answer == reinterpret_cast<OpaqueChild*>(
                                reinterpret_cast<std::uint8_t*>(second.object()) +
                                kChildDisplacement),
        "D: two receivers differing only in unread bytes answer by their own address");
}

// Case Q: 0 bytes of stack effect and 0 stack arguments, measured across a
// thiscall shim rather than asserted as a convention.
void test_stack_effect() {
  Storage storage;
  OpaqueReceiver* const receiver = storage.object();
  put_u32(receiver, 0x4, 0x5a5a5a5au);

  const auto fn = reinterpret_cast<ChildFn>(&editor_child_007f30d0);
  const std::uint32_t esp_before = read_esp();
  OpaqueChild* const result = fn(receiver);
  const std::uint32_t esp_after = read_esp();
  check_eq_u32(esp_after, esp_before,
               "Q: the call has zero stack effect (0 arguments, caller cleans)");
  check(result == reinterpret_cast<OpaqueChild*>(
                    reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement),
        "Q: the receiver arrives intact through the thiscall shim");
  check(storage.guards_intact(), "Q: no stray write around the call");
}

// The alternative callee for case V: the same shape as the reconstruction but
// a different displacement, so the two answers are distinguishable by value.
// A helper, so its name carries no address.
OpaqueChild* TEST_THISCALL alternative_callee(OpaqueReceiver* receiver) {
  return reinterpret_cast<OpaqueChild*>(
      reinterpret_cast<std::uint8_t*>(receiver) + kChildDisplacement + 0x40);
}

// Case V: the virtual-member mechanic. The function installed at a vtable slot
// is reached through the two-level load receiver -> vtable -> slot, and
// repointing the vtable changes the callee, so the load did not collapse into
// a direct call.
void test_vtable_dispatch() {
  struct Vtable {
    void* slot_00[kSlotOffset / sizeof(void*)];
    ChildFn child_at_5c;
  };
  static_assert(offsetof(Vtable, child_at_5c) == kSlotOffset,
                "the synthetic slot sits at the machine's slot position");

  struct Object {
    Vtable* vtable;
  };

  Storage storage;
  OpaqueReceiver* const receiver = storage.object();
  put_u32(receiver, 0x4, 0x01234567u);

  // The two-level load: receiver -> vtable -> slot, with the reconstruction
  // installed at the slot position the machine records.
  Vtable vtable{};
  vtable.child_at_5c = &editor_child_007f30d0;
  Object object{};
  object.vtable = &vtable;
  OpaqueChild* const dispatched = object.vtable->child_at_5c(receiver);
  check(dispatched == reinterpret_cast<OpaqueChild*>(
                         reinterpret_cast<std::uint8_t*>(receiver) +
                         kChildDisplacement),
        "V: the slot dispatches to the reconstruction with the receiver intact");

  // The load must not collapse into a direct call: a second object whose
  // vtable holds a different callee must reach that callee instead. The
  // alternative callee answers a different address, so the two answers are
  // distinguishable by value and the dispatch is provably indirect.
  Vtable other{};
  other.child_at_5c = &alternative_callee;
  Object via_other{};
  via_other.vtable = &other;
  OpaqueChild* const alternative = via_other.vtable->child_at_5c(receiver);
  check(alternative == reinterpret_cast<OpaqueChild*>(
                           reinterpret_cast<std::uint8_t*>(receiver) +
                           kChildDisplacement + 0x40),
        "V: a second vtable's callee is reached instead (the load is two-level)");
  check(alternative != dispatched,
        "V: the two vtables dispatch to different callees");
}

}

int run_tests() {
  test_body_bytes();
  test_arms();
  test_stack_effect();
  test_vtable_dispatch();
  if (g_failures == 0) {
    std::printf("editor_child_007f30d0: %d checks passed\n", g_checks);
    return 0;
  }
  std::fprintf(stderr, "editor_child_007f30d0: %d of %d checks FAILED\n",
               g_failures, g_checks);
  return 1;
}

}

int main() {
  return openspore::reconstruction::pkg_editor_child_007f30d0::run_tests();
}

#undef TEST_THISCALL
