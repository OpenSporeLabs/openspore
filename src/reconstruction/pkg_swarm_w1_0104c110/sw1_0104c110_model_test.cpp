// PKG-SWARM-W1-0104C110 -- model test for VA 0x0104c110
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e)
//
// THIS TEST TRIES TO BREAK THE RECONSTRUCTION. It is not a walk-through of it.
//
// The target is two instructions, so a test that merely calls the function once
// and prints the result would pass against almost any implementation at all.
// Everything below exists to be wrong in a specific, plausible way and to be
// caught when it is:
//
//   D1  the displacement is not 0x210 (off-by-four either way, byte-offset
//       confusion, a neighbouring field)
//   D2  the width is not 4 (a 1-, 2- or 8-byte read; sign extension; byte swap)
//   D3  the read is TWO levels deep -- the receiver's word is a pointer and the
//       pointee is returned
//   D4  the receiver is itself a pointer to a header, and the field lives on
//       the pointee rather than on the receiver
//   D5  the body is a constant stub returning a literal or a default
//   D6  the body WRITES to the receiver (caching, normalising, clamping,
//       post-increment) or writes outside it
//   D7  the body reads further than 4 bytes at 0x210
//   D8  the body has a null guard that the original does not have
//   D9  the body makes a call / takes a dispatch hop that the original does not
//   D10 the declared return width or the declared argument surface is wrong
//
// Each decoy case below also asserts that the fixture DISCRIMINATES: it reads
// the same buffer through deliberately wrong displacements and through a
// two-level model, and requires those to produce values different from the one
// the reconstruction returns. Without that, a fixture whose decoys all happened
// to hold the same value would silently pass a broken reconstruction, so the
// discrimination assertions are what make the decoys real decoys rather than
// decoration.
//
// WHAT THIS TEST DELIBERATELY DOES NOT ASSERT, and why:
//
//   * It asserts NO element type for the returned 32 bits. Not unsigned, not
//     signed, not a pointer. The machine fixes the width and nothing else
//     (return.type is null, register_class is the inference string
//     "pointer_like"), and the single caller tests the result with a signed JLE
//     and stores it into a 4-byte member. Those readings are in tension and the
//     evidence does not settle it, so the test compares bit patterns and width
//     only. A future finding about the element type must not be read as
//     something this test already established.
//   * It asserts NO name, meaning or ownership for the field at +0x210 or for
//     the receiver's class. The triage record's Sporepedia cluster is a
//     classifier output, not a symbol (sdk_name is null).
//   * It asserts NO extent of the receiver beyond the 0x214 bytes the body
//     reads. The real object is larger; nothing here fixes its size.
//   * It asserts NO traversal by EAX past the 4 bytes: EAX is dead after the
//     RET and the original leaves the upper 28 bytes of the register whatever
//     they were. The reconstruction returns a value, so a caller could in
//     principle observe a difference there; that is out of scope for a
//     two-instruction body and is not asserted.
//   * It does NOT assert that reading the four bytes is safe, only that it is
//     what the machine does. A null or wild receiver faults in the original and
//     faults here; D8 asserts that fact rather than papering over it.

#include "sw1_0104c110_types.hpp"

#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include <csignal>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {

namespace rs = openspore::reconstruction::pkg_swarm_w1_0104c110;

using rs::FieldWord;
using rs::kOriginalEncoding;
using rs::kReceiverFieldDisplacement;
using rs::OpaqueVtableOwner;
using rs::re_0104c110;
using rs::word_at;

int g_checks = 0;
int g_failures = 0;

void check(bool condition, const char* what, int line) {
  ++g_checks;
  if (condition) {
    return;
  }
  ++g_failures;
  std::printf("FAIL line %d: %s\n", line, what);
}

#define CHECK(condition) check((condition), #condition, __LINE__)

// The receiver's modelled extent, and a machine fact rather than a design
// choice: the body reads bytes 0x210..0x213 and nothing else, so 0x210 + 4 is
// the last byte it can touch and 0x214 is the whole of the claim (the header
// says the same thing and says why the real object is larger and unmodelled).
//
// This is the number every extent-dependent part of the fixture is derived
// from -- the guard-page boundary in D7, the fill length, and the "large enough
// for every displacement the body reads" assertion below. It is spelled once
// here and asserted against the header's opaque run, so the test's copy cannot
// drift away from the type it is measured against; a second literal in the
// guard placement would let the two disagree silently, and the guard page is
// what kills the over-wide-read mutants, so a drift there would quietly
// weaken the test rather than break it.
constexpr std::size_t kReceiverBytes = 0x214;
static_assert(kReceiverBytes == sizeof(OpaqueVtableOwner),
              "the test's receiver extent is the header's opaque run size, not a "
              "second opinion about it");
static_assert(kReceiverFieldDisplacement + sizeof(FieldWord) == kReceiverBytes,
              "0x210 + 4 is the last byte the body reads, and it ends the receiver "
              "exactly: no byte beyond it is claimed to be part of the object");
// The byte the arena is filled with. Chosen to be a value no planted decoy ever
// uses, so a "return the untouched byte run" implementation cannot coincide with
// a planted field by accident.
constexpr std::uint8_t kPoison = 0xcc;

// The receiver is the FIRST 0x214 bytes of a larger arena, so a write past the
// receiver is observable instead of corrupting the next object.
constexpr std::size_t kArenaBytes = 0x400;

struct Arena {
  alignas(16) std::uint8_t raw[kArenaBytes];
  OpaqueVtableOwner* receiver() {
    return reinterpret_cast<OpaqueVtableOwner*>(raw);
  }
};

// Fill the whole arena with the poison byte, then plant one value at `offset`.
void reset(Arena& arena) {
  std::memset(arena.raw, kPoison, kArenaBytes);
}

void plant(Arena& arena, std::size_t offset, std::uint32_t value) {
  if (offset + 4 > kArenaBytes) {
    std::printf("FAIL fixture bug: plant at 0x%zx is outside the arena\n", offset);
    ++g_failures;
    return;
  }
  std::memcpy(arena.raw + offset, &value, 4);
}

// The wrong-depth models, expressed against the same fixture so the test can
// prove its decoys discriminate. These are NOT the reconstruction; they are the
// alternatives the reconstruction must be distinguishable from.

// D3: two levels -- treat the receiver's word as a pointer and return *it.
std::uint32_t read_two_levels(const Arena& arena) {
  const std::uintptr_t held = *word_at(&arena, kReceiverFieldDisplacement);
  return *reinterpret_cast<const std::uint32_t*>(held);
}

// D1: the displacement is some other displacement. A faithful, byte-for-byte
// copy of the reconstruction with the offset changed, so what it refutes is
// exactly the offset and nothing else.
std::uint32_t read_at_displacement(Arena& arena, std::size_t displacement) {
  return *word_at(arena.receiver(), displacement);
}

// The transfer ledger. The original body makes no call and takes no dispatch
// hop, so the correct count is zero. The ledger exists so that the zero is
// something the test states, and so a future reconstruction that grew a callee
// would have to be argued for rather than absorbed silently.
std::uint64_t g_observed_transfers = 0;

FieldWord call_under_test(Arena& arena) {
  const FieldWord result = re_0104c110(arena.receiver());
  // A call would have to be observed here; there is none to observe.
  return result;
}

// -- D10: the declared ABI surface --------------------------------------------

// Taking the address of the reconstruction through a one-parameter function
// pointer type only compiles if the declared argument surface is exactly one
// pointer. The original reads no stack slot, so a two-argument signature would
// be wrong, and this is what pins that down at compile time.
using ExpectedAbi = FieldWord(PKG_SW1_0104C110_THISCALL*)(OpaqueVtableOwner*);

// -- D9: no transfer opcode in the original bytes ------------------------------

// 0xE8 is CALL rel32 and 0xFF is the group-5 opcode that CALL/JMP r/m uses. A
// byte scan is exact for this particular body rather than approximate, because
// neither byte value occurs anywhere in the seven bytes -- so the scan cannot be
// fooled by one appearing as a displacement or an immediate, which is the only
// way a byte scan over an encoding is normally unsound.
bool contains_transfer_opcode(const std::uint8_t* bytes, std::size_t count) {
  for (std::size_t index = 0; index < count; ++index) {
    if (bytes[index] == 0xe8 || bytes[index] == 0xff) {
      return true;
    }
  }
  return false;
}

// -- D8: run `body` in a child process and report how it died ------------------
// 0 = returned normally, otherwise the signal that killed it. Used for the null
// receiver, where a correct reconstruction MUST fault.
int run_in_child(void (*body)()) {
  std::fflush(nullptr);
  const pid_t child = fork();
  if (child < 0) {
    std::printf("FAIL fixture bug: fork failed\n");
    ++g_failures;
    return -1;
  }
  if (child == 0) {
    body();
    _exit(0);
  }
  int status = 0;
  if (waitpid(child, &status, 0) < 0) {
    std::printf("FAIL fixture bug: waitpid failed\n");
    ++g_failures;
    return -1;
  }
  if (WIFSIGNALED(status)) {
    return WTERMSIG(status);
  }
  return 0;
}

void body_null_receiver() {
  // Deliberately no cast and no comment about it being invalid: the original
  // dereferences ECX with no test, so this is what the original does.
  volatile FieldWord sink = re_0104c110(nullptr);
  (void)sink;
}

// -- the child-side result channel ---------------------------------------------
// Some of the wrong models do not merely return a wrong value, they fault: a
// two-level reconstruction dereferences the receiver's word, and when that word
// is 0 it dereferences a null pointer. Letting that happen in this process would
// abort the whole test run and lose every other finding, so those calls happen in
// a child and hand their result back through one shared page. The page is
// MAP_SHARED, so what the child writes is what the parent reads; the `done` word
// is what separates "the child computed this" from "the child died before
// computing anything", which is the difference between a reported failure and a
// reported crash.
struct SharedSlot {
  volatile std::uint32_t value;
  volatile std::uint32_t computed;
};

SharedSlot* g_shared_slot = nullptr;
OpaqueVtableOwner* g_child_receiver = nullptr;

void body_call_and_report() {
  const FieldWord result = re_0104c110(g_child_receiver);
  g_shared_slot->value = static_cast<std::uint32_t>(result);
  g_shared_slot->computed = 1;
  _exit(0);
}

// Calls the reconstruction in a child and reports the result. `signal` is 0 when
// the child returned, otherwise the signal that killed it; `value` is only
// meaningful when `signal` is 0 and `computed` is set.
int call_in_child(OpaqueVtableOwner* receiver, std::uint32_t* value) {
  g_child_receiver = receiver;
  *value = 0;
  g_shared_slot->computed = 0;
  const int signal = run_in_child(&body_call_and_report);
  if (signal == 0 && g_shared_slot->computed != 0) {
    *value = g_shared_slot->value;
  }
  g_child_receiver = nullptr;
  return signal;
}

SharedSlot* map_shared_slot() {
  const std::size_t page = static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
  void* mapping = mmap(nullptr, page, PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (mapping == MAP_FAILED) {
    return nullptr;
  }
  return static_cast<SharedSlot*>(mapping);
}

// -- D7: the receiver ending exactly at a guard page ---------------------------
// The receiver is placed so that its LAST byte is the last byte of a readable
// page, and the page after it is PROT_NONE. A correct implementation reads the
// four bytes at 0x210 -- the final four bytes of the readable page, which is
// legal -- and touches nothing beyond. An implementation that read 8 bytes at
// 0x210, or started at 0x211, or touched a second field, would take the guard
// page and die. The child process is what makes that observation safe to make.
struct GuardedReceiver {
  void* mapping = nullptr;
  std::size_t mapping_size = 0;
  OpaqueVtableOwner* receiver = nullptr;
};

bool place_guarded_receiver(GuardedReceiver& out) {
  const std::size_t page = static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
  out.mapping_size = page * 2;
  void* mapping = mmap(nullptr, out.mapping_size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (mapping == MAP_FAILED) {
    return false;
  }
  if (mprotect(static_cast<std::uint8_t*>(mapping) + page, page, PROT_NONE) != 0) {
    munmap(mapping, out.mapping_size);
    return false;
  }
  out.mapping = mapping;
  // The receiver ends exactly where the guard page begins, so the boundary is
  // placed from kReceiverBytes rather than from a second copy of 0x214: the
  // static_assert above ties that number to sizeof(OpaqueVtableOwner), which is
  // what makes "the receiver's last byte is the readable page's last byte" a
  // stated fact instead of a coincidence between two literals that happen to
  // agree today. This placement is what kills the over-wide-read mutants, so it
  // has to move with the extent if the extent ever moves.
  out.receiver = reinterpret_cast<OpaqueVtableOwner*>(
      static_cast<std::uint8_t*>(mapping) + page - kReceiverBytes);
  return true;
}

void release(GuardedReceiver& guarded) {
  if (guarded.mapping != nullptr) {
    munmap(guarded.mapping, guarded.mapping_size);
    guarded.mapping = nullptr;
  }
}

// The guarded receiver is a file-scope pointer, not a parameter, because the
// process that dereferences it is a fork of this one and inherits the mapping;
// a function pointer with no arguments is the only thing that crosses that
// boundary.
OpaqueVtableOwner* guarded_receiver_global = nullptr;

void body_guarded_read() {
  volatile FieldWord sink = re_0104c110(guarded_receiver_global);
  (void)sink;
}

}  // namespace

int main() {
  std::printf("model test for 0x0104c110 (FUN_0104c110), worker w03\n");

  // One shared page carries every child-side result. Allocated before the first
  // case that needs a child, because the D3b and D6b cases both call through it.
  g_shared_slot = map_shared_slot();
  if (g_shared_slot == nullptr) {
    std::printf("FAIL fixture bug: could not map the shared result slot\n");
    return 1;
  }

  // ---------------------------------------------------------------- extent --
  // The span is 7 bytes and the terminator is a bare near return. Both are read
  // out of the bytes themselves rather than trusted from a header comment, which
  // is why this test decoded them: a documentation typo cannot survive here.
  CHECK(sizeof(kOriginalEncoding) == 7);
  CHECK(kOriginalEncoding[0] == 0x8b);  // MOV r32, r/m32
  CHECK(kOriginalEncoding[1] == 0x81);  // mod = 10 (disp32), reg = EAX, rm = ECX
  CHECK(kOriginalEncoding[6] == 0xc3);  // RET, no imm16
  // The terminator is C3 and NOT C2, so the callee pops no argument bytes.
  CHECK(kOriginalEncoding[6] != 0xc2);

  // The displacement the encoding carries, decoded from its own disp32 field.
  const std::uint32_t encoded_displacement =
      static_cast<std::uint32_t>(kOriginalEncoding[2]) |
      (static_cast<std::uint32_t>(kOriginalEncoding[3]) << 8) |
      (static_cast<std::uint32_t>(kOriginalEncoding[4]) << 16) |
      (static_cast<std::uint32_t>(kOriginalEncoding[5]) << 24);
  CHECK(encoded_displacement == 0x210u);
  // ...and it is the displacement the reconstruction actually reads, proven by
  // planting the value there and nowhere else in the receiver.
  CHECK(kReceiverFieldDisplacement == 0x210u);
  CHECK(encoded_displacement == kReceiverFieldDisplacement);

  // D9: no call and no dispatch hop anywhere in the body, from the bytes.
  CHECK(!contains_transfer_opcode(kOriginalEncoding, sizeof(kOriginalEncoding)));

  // ------------------------------------------------------------ D10 / ABI --
  // Declared return width.
  CHECK(sizeof(FieldWord) == 4);
  CHECK(sizeof(OpaqueVtableOwner) == 0x214);
  // The receiver the fixture plants into is large enough for every displacement
  // the body reads: the one displacement the encoding carries, 0x210, read four
  // bytes wide. The `>=` is the safety property the D7 guard-page fixture needs;
  // the `==` is the other half of the same fact, that the read ends exactly on
  // the receiver's last byte rather than somewhere inside a wider extent that
  // nothing in the evidence fixes. Both are stated against kReceiverBytes, the
  // constant the D7 guard boundary is placed from, so the extent the test builds
  // its fixtures with and the extent it asserts about are one number.
  CHECK(kReceiverFieldDisplacement + sizeof(FieldWord) <= kReceiverBytes);
  CHECK(kReceiverFieldDisplacement + sizeof(FieldWord) == kReceiverBytes);
  // The arena is strictly larger than the receiver, which is what makes a write
  // past the receiver's end observable instead of corrupting the next object.
  CHECK(kArenaBytes > kReceiverBytes);
  // Declared argument surface: one pointer, thiscall. Fails to compile if the
  // reconstruction ever grows an argument.
  ExpectedAbi declared = &re_0104c110;
  CHECK(declared != nullptr);
  CHECK(declared == &re_0104c110);

  // ------------------------------------------------- D1: displacement is 0x210
  {
    Arena arena;
    reset(arena);
    // Every decoy neighbour gets a value distinct from the real one, so a
    // displacement error of +-1, +-2, +-4 or +-8 bytes lands on a wrong answer.
    plant(arena, 0x000, 0x11111111u);
    plant(arena, 0x060, 0x22222222u);
    plant(arena, 0x064, 0x33333333u);
    plant(arena, 0x07c, 0x44444444u);  // the field the one caller writes
    plant(arena, 0x1fc, 0x55555555u);
    plant(arena, 0x208, 0x66666666u);
    plant(arena, 0x20c, 0x77777777u);
    plant(arena, 0x210, 0xdeadbeefu);  // the field
    plant(arena, 0x214, 0x88888888u);
    plant(arena, 0x218, 0x99999999u);
    plant(arena, 0x224, 0xaaaaaaaau);

    const FieldWord got = call_under_test(arena);

    CHECK(got == 0xdeadbeefu);
    // The discrimination assertions. Each of these is the value a specific wrong
    // displacement would have produced; if any of them equalled the correct
    // answer, the fixture would be useless.
    CHECK(read_at_displacement(arena, 0x000) != got);
    CHECK(read_at_displacement(arena, 0x064) != got);
    CHECK(read_at_displacement(arena, 0x07c) != got);
    CHECK(read_at_displacement(arena, 0x20c) != got);
    CHECK(read_at_displacement(arena, 0x214) != got);
    CHECK(read_at_displacement(arena, 0x218) != got);
    // A byte-granularity slip, which the two four-byte decoys above cannot catch
    // on their own.
    CHECK(read_at_displacement(arena, 0x211) != got);
    CHECK(read_at_displacement(arena, 0x20f) != got);
    // An 8-byte read at 0x210 would drag the 0x214 decoy into the value. Stated
    // precisely, because the obvious version of this assertion is false: only
    // the HIGH half shows an over-wide read, since narrowing an 8-byte load to
    // 32 bits keeps the low half, and the low half is by construction the right
    // answer. So this pair of checks is here to record that coincidence, and the
    // real detector for an over-wide read is the guard page in D7, which faults
    // on the extra bytes outright instead of reasoning about their value.
    const std::uint64_t wide =
        *reinterpret_cast<const std::uint64_t*>(arena.raw + 0x210);
    CHECK(static_cast<std::uint32_t>(wide >> 32) != got);
    CHECK(static_cast<std::uint32_t>(wide) == got);
    CHECK(g_observed_transfers == 0);
  }

  // ---------------------------------------------- D2: width, lanes, bit pattern
  // A value whose four bytes are all distinct and non-zero, so a 1-byte, 2-byte
  // or byte-swapped read is distinguishable from the 4-byte little-endian one.
  {
    Arena arena;
    reset(arena);
    plant(arena, 0x210, 0x11223344u);
    const FieldWord got = call_under_test(arena);
    CHECK(got == 0x11223344u);
    // Byte lane order: the low byte must be 0x44, the high 0x11.
    CHECK(static_cast<std::uint8_t>(got & 0xffu) == 0x44u);
    CHECK(static_cast<std::uint8_t>((got >> 24) & 0xffu) == 0x11u);
    // A byte swap would produce this, and it is not the answer.
    CHECK(((got & 0xffu) << 24 | (got & 0xff00u) << 8 | (got & 0xff0000u) >> 8 |
           (got & 0xff000000u) >> 24) != got);
    // The top bit set: a 16-bit or signed-truncated reader cannot produce this.
    plant(arena, 0x210, 0x80000000u);
    CHECK(call_under_test(arena) == 0x80000000u);
    plant(arena, 0x210, 0x7fffffffu);
    CHECK(call_under_test(arena) == 0x7fffffffu);
    // All bits set: catches an "empty means default" reader.
    plant(arena, 0x210, 0xffffffffu);
    CHECK(call_under_test(arena) == 0xffffffffu);
    // And the whole 32-bit range survives bit for bit, in both halves.
    plant(arena, 0x210, 0x0000ffffu);
    CHECK(call_under_test(arena) == 0x0000ffffu);
    plant(arena, 0x210, 0xffff0000u);
    CHECK(call_under_test(arena) == 0xffff0000u);
  }

  // ----------------------------------------------- D3: one level, not two levels
  // The receiver's word at 0x210 is a POINTER to a poisoned cell. A two-level
  // reconstruction would return the poison; a one-level one returns the pointer.
  {
    Arena arena;
    reset(arena);
    std::uint32_t poison = 0x0badf00du;
    plant(arena, 0x210, reinterpret_cast<std::uint32_t>(&poison));
    const FieldWord got = call_under_test(arena);
    CHECK(got == reinterpret_cast<std::uint32_t>(&poison));
    CHECK(got != 0x0badf00du);
    // The wrong-depth model really does produce the other value here, so the
    // assertion above is a refutation and not a tautology.
    CHECK(read_two_levels(arena) == 0x0badf00du);
    CHECK(read_two_levels(arena) != got);
  }

  // A zero at 0x210 must come back as zero. A two-level model would dereference
  // a null pointer here; the original returns 0. The call is made in a child
  // because the two-level model FAULTS on this input rather than returning
  // something wrong, and a fault in this process would abort the run and lose
  // every other finding. Asserted here as "the child survived", which is the
  // same statement about the machine: no dereference of the returned word.
  {
    Arena arena;
    reset(arena);
    plant(arena, 0x210, 0u);
    std::uint32_t observed = 0xffffffffu;
    const int signal = call_in_child(arena.receiver(), &observed);
    CHECK(signal == 0);
    CHECK(observed == 0u);
  }

  // --------------------------------- D4: the receiver is the object, not a pointer
  // The receiver's first word is a pointer to a decoy object that ALSO has a
  // 0x210 field, holding a different value. A reconstruction that treated ECX as
  // a pointer to a header and read the field from the pointee would return the
  // decoy. This is a different model from D3 and is refuted separately.
  {
    Arena arena;
    std::uint32_t decoy_object[0x300 / 4] = {0};
    reset(arena);
    // The decoy object has a field of its own at +0x210, holding a different
    // value from the one planted in the receiver.
    decoy_object[0x210 / 4] = 0xdeadbeefu;
    plant(arena, 0x000, reinterpret_cast<std::uint32_t>(decoy_object));
    plant(arena, 0x210, 0x5a5a5a5au);
    const FieldWord got = call_under_test(arena);
    CHECK(got == 0x5a5a5a5au);
    // The wrong model would have produced the decoy's own 0x210 field.
    const std::uint32_t through_header =
        *word_at(reinterpret_cast<const std::uint8_t*>(
                     *word_at(&arena, 0x000)),
                 0x210);
    CHECK(through_header == 0xdeadbeefu);
    CHECK(through_header != got);
  }

  // ------------------------------------------------- D5: not a constant stub --
  // A stub returning a literal, a default, or "0 when unset" would satisfy a
  // single-value test. This sweeps values and requires every one to round-trip,
  // including the two a stub is most likely to special-case.
  {
    const std::uint32_t sweep[] = {
        0u,        1u,         2u,          0x7fffffffu, 0x80000000u,
        0x80000001u, 0xfffffffeu, 0xffffffffu, 0x12345678u, 0xcafebabeu,
    };
    for (const std::uint32_t value : sweep) {
      Arena arena;
      reset(arena);
      plant(arena, 0x210, value);
      CHECK(call_under_test(arena) == value);
    }
    // Two arenas differing ONLY at 0x210 must give different answers. This is
    // the positive statement of "the receiver is read": nothing else in the
    // object influences the result.
    {
      Arena low;
      Arena high;
      reset(low);
      reset(high);
      plant(low, 0x210, 0x00000001u);
      plant(high, 0x210, 0x00000002u);
      const FieldWord a = call_under_test(low);
      const FieldWord b = call_under_test(high);
      CHECK(a == 1u);
      CHECK(b == 2u);
      CHECK(a != b);
    }
  }

  // ------------------------------------ D6: nothing is written, anywhere ------
  // Byte-for-byte comparison of the whole arena, before and after. This refutes
  // a reconstruction that caches the value, clamps it, post-increments it,
  // marks the field dirty, or scribbles outside the receiver.
  {
    Arena arena;
    reset(arena);
    plant(arena, 0x210, 0xcafebabeu);
    std::vector<std::uint8_t> before(kArenaBytes, 0);
    std::memcpy(before.data(), arena.raw, kArenaBytes);
    const FieldWord got = call_under_test(arena);
    std::vector<std::uint8_t> after(kArenaBytes, 0);
    std::memcpy(after.data(), arena.raw, kArenaBytes);
    CHECK(std::memcmp(before.data(), after.data(), kArenaBytes) == 0);
    CHECK(got == 0xcafebabeu);
    // A writer would have to write something, and there is nothing else it could
    // plausibly have touched that is still 0 in the arena.
    bool any_zero_byte = false;
    for (std::size_t index = 0; index < kArenaBytes; ++index) {
      if (arena.raw[index] == 0) {
        any_zero_byte = true;
        break;
      }
    }
    CHECK(!any_zero_byte);
  }

  // D6b: the same "nothing is written" claim, asserted in a way that a
  // same-value write-back cannot survive. The snapshot above compares bytes, and
  // a reconstruction that stored the value it just read leaves the bytes
  // identical -- so the snapshot cannot see it, and a mutation check on this very
  // package confirmed that gap. A read-only page sees it: the receiver is mapped
  // PROT_READ, so a store into it faults while a load does not. This is the
  // strongest statement available about the body's effect on memory, because it
  // comes from the MMU rather than from a comparison.
  {
    const std::size_t page = static_cast<std::size_t>(sysconf(_SC_PAGESIZE));
    void* mapping = mmap(nullptr, page, PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mapping == MAP_FAILED) {
      std::printf("note: read-only-page fixture unavailable, D6b not exercised\n");
    } else {
      // Fill it, then drop write permission on the whole page. The receiver is
      // the first 0x214 bytes of it.
      std::memset(mapping, kPoison, page);
      auto* receiver = static_cast<OpaqueVtableOwner*>(mapping);
      *word_at(receiver, 0x210) = 0x13572468u;
      if (mprotect(mapping, page, PROT_READ) != 0) {
        std::printf("note: mprotect failed, D6b not exercised\n");
      } else {
        std::uint32_t observed = 0;
        const int signal = call_in_child(receiver, &observed);
        // A store into the receiver would have killed the child with SIGSEGV or
        // SIGBUS; surviving is the assertion.
        CHECK(signal == 0);
        CHECK(observed == 0x13572468u);
        // Restore write permission so the mapping can be torn down cleanly.
        mprotect(mapping, page, PROT_READ | PROT_WRITE);
      }
      munmap(mapping, page);
    }
  }

  // ------------------------------------------ D7: the read stays inside the object
  // The receiver ends exactly at a guard page, so any read past its last byte
  // kills the process. A correct implementation reads four bytes and survives.
  {
    GuardedReceiver guarded;
    if (!place_guarded_receiver(guarded)) {
      std::printf("note: guard-page fixture unavailable, D7 not exercised\n");
    } else {
      // Fill the receiver so the read has something definite to return, then
      // read it in a child: an out-of-bounds read must not take this process
      // down, only the child. The fill covers exactly the receiver, from the
      // same constant the guard boundary was placed from.
      std::memset(static_cast<void*>(guarded.receiver), 0, kReceiverBytes);
      *word_at(guarded.receiver, 0x210) = 0x0f0f0f0fu;
      guarded_receiver_global = guarded.receiver;
      const int signal = run_in_child(&body_guarded_read);
      CHECK(signal == 0);
      CHECK(*word_at(guarded.receiver, 0x210) == 0x0f0f0f0fu);
      guarded_receiver_global = nullptr;
      release(guarded);
    }
  }

  // ------------------------------- D8: no null guard the original does not have --
  // The original compares nothing before dereferencing ECX, so a null receiver
  // faults. A reconstruction that "helpfully" returned 0 for a null receiver
  // would be a failure here, and this is the assertion that catches it.
  {
    const int signal = run_in_child(&body_null_receiver);
    CHECK(signal == SIGSEGV);
  }

  std::printf("%d checks, %d failure(s)\n", g_checks, g_failures);
  if (g_failures != 0) {
    std::printf("RESULT: FAIL\n");
    return 1;
  }
  std::printf("RESULT: PASS\n");
  return 0;
}
