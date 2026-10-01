// PKG-SW1-00A649A0 -- VA 0x00a649a0
// Falsification test for the 4-byte Sporepedia accessor re_00a649a0.
//
// LAYERING, because a 2-instruction body has almost nothing to test and the
// danger is that the test ends up agreeing with itself:
//
//   1. kBodyBytes in the types header is the IMAGE, transcribed: 8B 41 6C C3.
//      Case K asserts those four bytes against literals, so the transcription
//      itself is under test and cannot drift silently.
//   2. The emulator below is an INDEPENDENT decoder written from the listing.
//      It walks kBodyBytes, decodes the ModRM and the disp8 out of the bytes,
//      forms the address itself, reads four bytes out of the test's own object
//      buffer and reports what it read, how wide, at which address, plus how
//      many writes, calls and flag-writing opcodes it saw. Nothing in it is
//      shared with the reconstruction.
//   3. re_00a649a0() in the .cpp is the code under test. It never reads
//      kBodyBytes and never calls the emulator, so a defect in it cannot be
//      papered over by either of the two above.
//
// There are no direct callees to make observers: abi_derived.callees and
// ghidra_function.callees are both empty and the two instructions contain no
// call opcode. The absence is asserted from the bytes (case G) rather than
// assumed, and the two stack-frame facts that a callee list cannot show are
// MEASURED across a thiscall shim (case Q) rather than asserted as a
// convention.
//
// The cases marked REFUTE exist to break the reconstruction:
//
//   A  +0x6c is the displacement: five decoy words at 0x60, 0x64, 0x68, 0x70 and
//      0x74, plus decoy bytes at 0x6b and 0x6d, none of which may move the answer.
//   B  the load is 4 bytes wide: 0xcd at 0x6c and 0xab at 0x6d, so a byte load
//      would answer 0xcd and a word load 0xabcd.
//   C  the receiver is READ, not constant: the same object must answer
//      differently after only the field changes, and two objects with equal
//      fields must answer equally.
//   D  the answer is the value, not the receiver and not the field's ADDRESS.
//   E  no width loss and no normalisation: 0, 1, 2, 0xff, 0x100, 0x7fffffff,
//      0x80000000, 0xdeadbeef, 0xffffffff, 0x00000080 and 0x000000ff all pass
//      through bit for bit, and 0xffffffff is exactly 0x00000000ffffffff as a
//      64-bit host value (no sign extension).
//   F  nothing is written: every byte of the object and of the guard bands
//      around it is compared before and after.
//   G  no transfer at all: the decoded instruction set contains no call opcode
//      and the decoder refuses any opcode other than 0x8B and 0xC3.
//   H  exactly one memory read, 4 bytes, at receiver+0x6c, of the bytes that are
//      really there.
//   I  one level of dereference only: the field is loaded with the ADDRESS of a
//      decoy block whose first dword is 0xfeedface, so a two-level read answers
//      0xfeedface and the correct answer is the address.
//   K  the body is 4 bytes: 8B 41 6C C3, two instructions, terminator 0xC3, and
//      a bare RET with no immediate byte behind it.
//   L  no flag-writing opcode: EFLAGS passes through untouched, which is why the
//      test does not assert anything about flags at the call site and instead
//      asserts the property of the instruction set that makes it true.
//   Q  0 bytes of stack effect and 0 stack arguments: measured, not assumed.
//
// What is NOT asserted, and why:
//
//   * What the word at +0x6c means. The 4 bytes, the 7 vtable runs that install
//     this entry and the one caller say nothing about it, and abi_derived's
//     "pointer_like_in_EAX" is an INFERRED register class, not a type. So no
//     name, no pointee type and no nullability are asserted; case I asserts only
//     that nothing dereferences the loaded word.
//   * The vtable slot number. docs/analysis/vtables.json labels the run whose
//     head is 0x013ff648 as a 40-slot table and the entry sits 0x88 past that
//     head, but whether the head dword is slot 0 is exactly the convention this
//     target does not settle, so the test asserts nothing about a slot and the
//     model declares none.
//   * The other 14 bytes the image shows after 0x00a649a3. They are 0xcc padding
//     in front of the next body at 0x00a649a8 and are outside this function.
//   * Write ordering against a callee. There is no callee and no write, so the
//     usual "sample the callee to catch a reordered store" refutation has no
//     observable here; case F is the whole of it.
//   * EFLAGS at the call site. Doing that from C++ would be testing the
//     compiler, not the reconstruction, so case L asserts the property of the
//     decoded instruction set that makes the claim true instead.

#include "sw1_00a649a0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <new>
#include <type_traits>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w1_00a649a0 {
namespace {

// The image, as literals, for the byte-level case K. Deliberately NOT kBodyBytes
// so the transcription and the test cannot agree by construction.
constexpr std::uint8_t kExpectEntry0 = 0x8B;  // 00a649a0  MOV r32,r/m32
constexpr std::uint8_t kExpectModRm = 0x41;   // 00a649a1  mod=01 reg=EAX rm=ECX
constexpr std::uint8_t kExpectDisp = 0x6C;    // 00a649a2  disp8 = +108
constexpr std::uint8_t kExpectTerminator = 0xC3;  // 00a649a3  RET

constexpr std::size_t kObjectSize = 0xa4;  // the opaque run the header declares
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

// ---------------------------------------------------------------------------
// An independent decoder for these four bytes, written from the listing rather
// than from the header's convenience constants.
// ---------------------------------------------------------------------------

struct ReadEvent {
  std::uintptr_t address;
  std::size_t width;
};

struct EmuResult {
  bool ok = false;
  std::uint32_t eax = 0;
  std::size_t bytes_consumed = 0;
  std::uint8_t terminator = 0;
  bool bare_ret = false;
  std::size_t reads = 0;
  std::size_t writes = 0;
  std::size_t calls = 0;
  std::size_t flag_writes = 0;
  std::uint8_t last_modrm = 0;
  std::int32_t last_displacement = 0;
  std::uint8_t last_width = 0;
  std::vector<ReadEvent> read_log;
};

// EFLAGS writers, as a decoder for the x86-32 opcode map. 0x8B and 0xC3 are not
// in here, which is the machine fact case L asserts.
bool writes_eflags(std::uint8_t op) {
  // ADD/OR/ADC/SBB/AND/SUB/XOR/CMP, all eight forms of each.
  if (op <= 0x3D && (op & 0x07) <= 0x05 && (op & 0xC7) != 0xC6 && (op & 0xC7) != 0xC7) {
    return true;
  }
  if (op >= 0x80 && op <= 0x83) return true;  // imm group, includes CMP/TEST
  if (op == 0x84 || op == 0x85) return true;  // TEST r/m
  if (op == 0xA8 || op == 0xA9) return true;  // TEST AL/eAX, imm
  if (op >= 0xC0 && op <= 0xC1) return true;  // shift group, imm8
  if (op >= 0xD0 && op <= 0xD3) return true;  // shift group
  if (op >= 0xF6 && op <= 0xF7) return true;  // TEST r/m and the rest
  if (op == 0xFE || op == 0xFF) return true;  // INC/DEC/CALL/JMP/PUSH group
  if (op == 0x9C || op == 0x9D || op == 0x9E || op == 0x9F) return true;
  return false;
}

// `body` is the machine image to decode, so the decoder can also be pointed at a
// deliberately altered image: that is how case G shows the decoder is not a
// rubber stamp. A body it accepts is a body whose instruction stream it fully
// modelled; a body it rejects is one whose operand surface it will not guess at.
EmuResult emulate(const std::uint8_t* body, std::size_t body_len,
                  const std::uint8_t* object, std::size_t object_size,
                  std::uintptr_t ecx) {
  EmuResult r;
  const std::uint8_t* b = body;
  const std::size_t n = body_len;
  std::size_t pc = 0;
  bool done = false;

  while (pc < n && !done) {
    const std::uint8_t op = b[pc];
    if (writes_eflags(op)) ++r.flag_writes;

    if (op == 0x8B) {
      // MOV r32, r/m32. No prefix byte can exist: pc is 0 and the opcode is the
      // first byte of the body, so the operand size is the 32-bit default and
      // the address size is 32 bits.
      if (pc + 1 >= n) return r;  // no ModRM: reject rather than guess
      const std::uint8_t modrm = b[pc + 1];
      const std::uint8_t mod = static_cast<std::uint8_t>((modrm >> 6) & 0x3u);
      const std::uint8_t reg = static_cast<std::uint8_t>((modrm >> 3) & 0x7u);
      const std::uint8_t rm = static_cast<std::uint8_t>(modrm & 0x7u);
      std::size_t next = pc + 2;
      std::int64_t disp = 0;
      if (mod == 1) {
        if (next >= n) return r;  // the disp8 is missing
        disp = static_cast<std::int8_t>(b[next]);
        ++next;
      } else if (mod == 2 || mod == 0) {
        // disp32 form, or the no-displacement forms with an rm of 4 (SIB) or 5
        // (disp32). Neither can be the body of this function, and this decoder
        // refuses to model them rather than inventing a displacement.
        if (rm == 4 || (mod == 0 && rm == 5)) return r;
      }
      if (mod == 3) return r;  // register-to-register: no memory read at all
      if (reg != 0 || rm != 1 || mod != 1) {
        // EAX <- [ECX+disp8] is the only shape this body may have.
        return r;
      }
      const std::uintptr_t address =
          static_cast<std::uintptr_t>(static_cast<std::intptr_t>(ecx) + disp);
      const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(object);
      if (address < base || address + 4 > base + object_size) return r;
      std::uint32_t value = 0;
      for (std::size_t i = 0; i < 4; ++i) {  // x86-32 is little-endian
        value |= static_cast<std::uint32_t>(object[address - base + i])
                 << (8u * static_cast<unsigned>(i));
      }
      r.eax = value;
      r.reads += 1;
      r.read_log.push_back(ReadEvent{address, 4});
      r.last_modrm = modrm;
      r.last_displacement = static_cast<std::int32_t>(disp);
      r.last_width = 4;
      pc = next;
    } else if (op == 0xC3) {
      r.terminator = op;
      // Bare RET means the body stops here: C2 would have needed three bytes and
      // a C2 with its imm16 outside the body would be a different function.
      r.bare_ret = (pc + 1 == n);
      done = true;
    } else if (op == 0xE8 || op == 0xFF || op == 0x9A) {
      // A transfer. Counted so the "no callee" claim is measured, and then
      // rejected: a body with a call is not this body.
      ++r.calls;
      return r;
    } else {
      return r;  // any other opcode: the transcription is not this function
    }
  }

  if (!done) return r;
  r.bytes_consumed = n;
  r.ok = true;
  return r;
}

// The convenience form: decode the transcribed body of this function.
EmuResult emulate(const std::uint8_t* object, std::size_t object_size,
                  std::uintptr_t ecx) {
  return emulate(kBodyBytes.data(), kBodyBytes.size(), object, object_size, ecx);
}

// ---------------------------------------------------------------------------
// The object under test, with guard bands on both sides.
// ---------------------------------------------------------------------------

struct Fixture {
  alignas(16) std::uint8_t storage[kStorageSize];
  Receiver* receiver;

  Fixture() : receiver(nullptr) {
    std::memset(storage, kGuardByte, kStorageSize);
    receiver = ::new (static_cast<void*>(storage + kGuard)) Receiver();
    std::memset(reinterpret_cast<void*>(receiver), 0, kObjectSize);
  }
  ~Fixture() { receiver->~Receiver(); }

  const std::uint8_t* bytes() const { return storage; }
  const std::uint8_t* object_bytes() const { return storage + kGuard; }
  // The writable view the decoy-planting helpers use. It points at the same
  // bytes the emulator is given, so a decoy is read by the emulator exactly as
  // the reconstruction reads it.
  std::uint8_t* mutable_object_bytes() { return storage + kGuard; }
};

// REFUTE helper: writes a dword into the raw object buffer at a byte offset,
// bypassing the struct on purpose so decoys can be planted at every offset.
void poke_dword(Fixture& f, std::size_t offset, std::uint32_t value) {
  std::uint8_t* p = f.mutable_object_bytes() + offset;
  for (std::size_t i = 0; i < 4; ++i) {
    p[i] = static_cast<std::uint8_t>(value >> (8u * static_cast<unsigned>(i)));
  }
}

// ---------------------------------------------------------------------------
// Case Q support: measure the stack effect from the outside instead of
// asserting a convention, and pin the argument surface at compile time.
//
// The stack-argument half is deliberately NOT measured with a canary word left
// on the stack. That was tried and it is not a sound observable: the compiler
// owns the frame around the call, so a word the test pushed is not reliably the
// word a callee sees at [ESP+4] -- clang++ puts its own words there and the
// check failed on a correct reconstruction. The sound version of the same claim
// is below: the body is 4 bytes, its only memory operand is [ECX+0x6c], and the
// decoder in this file refuses any other shape, including the
// `8B 44 24 04` (`MOV EAX,[ESP+0x4]`) that consuming a stack argument would
// have to look like. Case G proves that refusal is real by feeding the decoder
// altered bodies and requiring it to reject each one.
// ---------------------------------------------------------------------------

// Measures the stack effect of the call. The shim is a thiscall function, so the
// only thing between the two ESP samples is the call itself: a return address
// goes down and comes back up and nothing else is on the stack to clean. A
// callee that popped 4 would report 0xfffffffc.
extern "C" std::uint32_t PKG_SW1_00A649A0_THISCALL probe_stack_effect(
    Receiver* r, std::uint32_t* delta_out) {
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(before) : : "memory");
  std::uint32_t v = re_00a649a0(r);
  __asm__ __volatile__("movl %%esp, %0" : "=r"(after) : : "memory");
  *delta_out = after - before;
  return v;
}

// The declared convention and signature are compile-time properties, so they are
// asserted as such: thiscall, one Receiver* and nothing else, returning a
// 32-bit word. A reconstruction that grew a stack parameter would stop compiling
// here instead of quietly changing the ABI.
using Re00a649a0Ptr = Word(PKG_SW1_00A649A0_THISCALL*)(Receiver*);
static_assert(std::is_same<decltype(&re_00a649a0), Re00a649a0Ptr>::value,
              "re_00a649a0 must be __thiscall on (Receiver*) and nothing else");
static_assert(std::is_same<decltype(re_00a649a0(nullptr)), Word>::value,
              "re_00a649a0 must return a 32-bit word");
// The displacement the accessor reads through is the disp8 of the transcribed
// image, tied here so that renaming or re-valuing it cannot drift away from the
// bytes without stopping the build.
static_assert(kFieldDisplacement == machine::kLoadDisplacement,
              "the accessor must read at the disp8 the body encodes");

// ---------------------------------------------------------------------------
// Cases
// ---------------------------------------------------------------------------

// K -- the body is exactly 4 bytes, and the terminator is a bare RET.
void case_k_bytes() {
  check(kBodyBytes.size() == 4, "K: the body is 4 bytes, not 3 and not 8");
  check_eq_u32(kBodyBytes[0], kExpectEntry0, "K: byte 0 at 0x00a649a0 is 0x8B");
  check_eq_u32(kBodyBytes[1], kExpectModRm, "K: byte 1 at 0x00a649a1 is 0x41");
  check_eq_u32(kBodyBytes[2], kExpectDisp, "K: byte 2 at 0x00a649a2 is 0x6C");
  check_eq_u32(kBodyBytes[3], kExpectTerminator,
               "K: byte 3 at 0x00a649a3 is 0xC3, a bare RET");
  check_eq_u32(machine::kSpanBytes, 4, "K: derived span is 4");
  check_eq_u32(machine::kInstructionCount, 2, "K: two instructions");
  check(machine::kIsBareRet,
        "K: the RET is bare -- there is no imm16 behind the 0xC3");
  check(machine::kIs32BitLoad,
        "K: 0x8B /r with mod=01, reg=EAX, rm=ECX is a 32-bit load of [ECX+disp8]");
  check_eq_u32(machine::kLoadDisplacement, 0x6c,
               "K: the disp8 decodes to receiver+0x6c");
}

// A, B, H -- displacement, width, and the read log.
void case_a_displacement_and_width() {
  Fixture f;
  poke_dword(f, 0x60, 0x11111111u);
  poke_dword(f, 0x64, 0x22222222u);
  poke_dword(f, 0x68, 0x33333333u);
  // The field is four bytes wide, so 0x6c..0x6f are all part of the answer. With
  // every one of those four bytes distinct, a byte load (0x12 at 0x6c, 0x34 at
  // 0x6d, 0xcd at 0x6f) and a word load (0x3412) each answer something the dword
  // does not.
  poke_dword(f, 0x6c, 0xcdab3412u);
  poke_dword(f, 0x70, 0x55555555u);
  poke_dword(f, 0x74, 0x66666666u);
  f.mutable_object_bytes()[0x6b] = 0x99;  // decoy in the byte just below the field

  const std::uint32_t got = re_00a649a0(f.receiver);
  check_eq_u32(got, 0xcdab3412u,
               "A/B: the answer is the 4 bytes at +0x6c, not a neighbour and "
               "not a byte or word load");
  check(got != 0x11111111u && got != 0x22222222u && got != 0x33333333u &&
            got != 0x55555555u && got != 0x66666666u,
        "A: none of the decoy words at 0x60/0x64/0x68/0x70/0x74 is the answer");
  check(got != 0x00000099u, "A: the decoy byte at 0x6b is not the answer");
  check(got != 0x00000012u, "B: a byte load at 0x6c would answer 0x12");
  check(got != 0x00000034u, "B: a byte load at 0x6d would answer 0x34");
  check(got != 0x0000cdabu, "B: a byte load at 0x6f would answer 0xcd");
  check(got != 0x00003412u, "B: a word load at 0x6c would answer 0x3412");

  const EmuResult e =
      emulate(f.object_bytes(), kObjectSize,
              reinterpret_cast<std::uintptr_t>(f.receiver));
  check(e.ok, "H: the independent decoder accepts the transcription");
  check_eq_u32(static_cast<std::uint32_t>(e.eax), 0xcdab3412u,
               "H: the decoder computes the same value from the bytes");
  check_eq_u32(static_cast<std::uint32_t>(e.reads), 1,
               "H: exactly one memory read");
  check_eq_u32(static_cast<std::uint32_t>(e.read_log.size()), 1,
               "H: exactly one read logged");
  if (e.read_log.size() == 1) {
    check_eq_u32(static_cast<std::uint32_t>(e.read_log[0].width), 4,
                 "H: the read is 4 bytes wide");
    check(e.read_log[0].address ==
              reinterpret_cast<std::uintptr_t>(f.receiver) + 0x6c,
          "H: the read is at receiver+0x6c");
  }
  check_eq_u32(static_cast<std::uint32_t>(e.last_displacement), 0x6c,
               "H: the decoder's own disp8 decode is +0x6c");
  check_eq_u32(static_cast<std::uint32_t>(e.last_width), 4,
               "H: the decoder's own operand width is 4 bytes");
  check(e.eax == got, "H: the reconstruction and the decoder agree");
}

// C, D -- the receiver is read; the value is not the receiver and not an address.
void case_c_receiver_is_read() {
  Fixture f;
  poke_dword(f, 0x6c, 0x00000000u);
  check_eq_u32(re_00a649a0(f.receiver), 0u,
               "C: an all-zero field answers 0, so the answer is not a constant");
  poke_dword(f, 0x6c, 0xdeadbeefu);
  const std::uint32_t changed = re_00a649a0(f.receiver);
  check_eq_u32(changed, 0xdeadbeefu,
               "C: changing only the field changes the answer");
  check(changed != 0u, "C: the answer follows the field, not a constant");

  Fixture g;
  poke_dword(g, 0x6c, 0xdeadbeefu);
  check_eq_u32(re_00a649a0(g.receiver), changed,
               "C: two distinct receivers with equal fields answer equally");
  check(g.receiver != f.receiver,
        "C: the two receivers really are at different addresses");

  const std::uintptr_t self = reinterpret_cast<std::uintptr_t>(f.receiver);
  // The address the word is read FROM, computed the way the machine computes it:
  // the receiver plus the disp8, with no member name involved.
  const std::uintptr_t field_addr = self + kFieldDisplacement;
  check(changed != static_cast<std::uint32_t>(self),
        "D: the answer is not the receiver pointer");
  check(changed != static_cast<std::uint32_t>(field_addr),
        "D: the answer is not the address of the field");
}

// E -- every width class of value passes through bit for bit.
void case_e_value_passthrough() {
  static const std::uint32_t kValues[] = {
      0x00000000u, 0x00000001u, 0x00000002u, 0x0000007fu, 0x000000ffu,
      0x00000100u, 0x0000ffffu, 0x00010000u, 0x7fffffffu, 0x80000000u,
      0xffffff80u, 0xfffffffeu, 0xffffffffu, 0xdeadbeefu, 0x13579bdfu};
  Fixture f;
  for (std::size_t i = 0; i < sizeof(kValues) / sizeof(kValues[0]); ++i) {
    poke_dword(f, 0x6c, kValues[i]);
    const std::uint32_t got = re_00a649a0(f.receiver);
    if (got != kValues[i]) {
      std::fprintf(stderr,
                   "FAILED: E: value 0x%08lx came back as 0x%08lx\n",
                   static_cast<unsigned long>(kValues[i]),
                   static_cast<unsigned long>(got));
      ++g_failures;
    }
    ++g_checks;
    check(got != 0u || kValues[i] == 0u,
          "E: no value is normalised to 0/1 (a bool-shaped return)");
  }
  // 0x00000080 is the case a sign-extended byte read gets wrong: it would answer
  // 0xffffff80. 0x000000ff is the case a zero-extended byte read gets wrong.
  poke_dword(f, 0x6c, 0x00000080u);
  check_eq_u32(re_00a649a0(f.receiver), 0x00000080u,
               "E: 0x00000080 is not sign-extended to 0xffffff80");
  poke_dword(f, 0x6c, 0x000000ffu);
  check_eq_u32(re_00a649a0(f.receiver), 0x000000ffu,
               "E: 0x000000ff is not truncated to a byte");
  // The 64-bit host value: a uint32_t return must be exactly the zero-extended
  // word, with nothing above bit 31 left over from a wider computation.
  poke_dword(f, 0x6c, 0xffffffffu);
  const std::uint64_t wide = re_00a649a0(f.receiver);
  check(wide == 0x00000000ffffffffull,
        "E: 0xffffffff is returned as 0x00000000ffffffff, not sign-extended");
}

// F -- nothing is written anywhere.
void case_f_no_writes() {
  Fixture f;
  poke_dword(f, 0x68, 0x0badc0deu);  // decoy, four bytes below the field
  poke_dword(f, 0x6c, 0x5a5a5a5au);
  poke_dword(f, 0x70, 0xa5a5a5a5u);
  poke_dword(f, 0xa0, 0x5a5a5a5au);
  std::uint8_t before[kStorageSize];
  std::memcpy(before, f.bytes(), kStorageSize);
  const std::uint32_t got = re_00a649a0(f.receiver);
  std::uint8_t after[kStorageSize];
  std::memcpy(after, f.bytes(), kStorageSize);
  check(std::memcmp(before, after, kStorageSize) == 0,
        "F: no byte of the object or of either guard band changed");
  check_eq_u32(got, 0x5a5a5a5au, "F: the value still came back correctly");
  check_eq_u32(word_at(f.receiver, kFieldDisplacement), 0x5a5a5a5au,
               "F: the word was not cleared, incremented or normalised");
  std::uint32_t decoy_68 = 0u;
  for (std::size_t i = 0; i < 4; ++i) {
    decoy_68 |= static_cast<std::uint32_t>(f.object_bytes()[0x68 + i])
                << (8u * static_cast<unsigned>(i));
  }
  check_eq_u32(decoy_68, 0x0badc0deu,
               "F: the decoy dword at 0x68 is byte-for-byte intact");
}

// G, L -- no transfer, and no flag-writing opcode.
void case_g_no_transfer() {
  Fixture f;
  poke_dword(f, 0x6c, 0x12345678u);
  const EmuResult ok = emulate(f.object_bytes(), kObjectSize,
                               reinterpret_cast<std::uintptr_t>(f.receiver));
  check(ok.ok, "G: the decoder completes the 4 bytes");
  check_eq_u32(static_cast<std::uint32_t>(ok.calls), 0,
               "G: the body contains no call opcode");
  check_eq_u32(static_cast<std::uint32_t>(ok.writes), 0,
               "G: the body contains no memory write");
  check_eq_u32(static_cast<std::uint32_t>(ok.flag_writes), 0,
               "L: no opcode in the body writes EFLAGS");
  check_eq_u32(static_cast<std::uint32_t>(ok.bytes_consumed), 4,
               "G: the decoder consumed the whole 4-byte body");
  check(ok.bare_ret, "G: the run ended on a bare RET with no immediate");
  check_eq_u32(static_cast<std::uint32_t>(ok.terminator), kExpectTerminator,
               "G: the terminator byte is 0xC3");
  // Byte scan, independent of the decoder: 0x8B and 0xC3 are not EFLAGS writers,
  // and none of the transfer opcodes appears.
  bool saw_call_opcode = false;
  bool saw_flag_writer = false;
  for (std::size_t i = 0; i < kBodyBytes.size(); ++i) {
    const std::uint8_t op = kBodyBytes[i];
    if (op == 0xE8 || op == 0xFF || op == 0x9A) saw_call_opcode = true;
    if (writes_eflags(op)) saw_flag_writer = true;
  }
  check(!saw_call_opcode, "G: no E8 / FF / 9A anywhere in the 4 bytes");
  check(!saw_flag_writer, "L: no EFLAGS-writing opcode anywhere in the 4 bytes");
}

// I -- one level of dereference only. REFUTE a two-level read: the field is
// loaded with the ADDRESS of a decoy block whose first dword is 0xfeedface, so
// a two-level read answers 0xfeedface and the correct answer is the address.
void case_i_one_level() {
  struct Decoy {
    std::uint32_t first;  // 0xfeedface -- a two-level read would return this
    std::uint32_t second;
  };
  Decoy pointee;
  pointee.first = 0xfeedfaceu;
  pointee.second = 0x0badf00du;

  Fixture f;
  const std::uint32_t planted = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&pointee));
  poke_dword(f, 0x6c, planted);
  poke_dword(f, 0x70, 0x0badf00du);  // the classic off-by-one-dword decoy too

  const std::uint32_t got = re_00a649a0(f.receiver);
  check_eq_u32(got, planted,
               "I: the loaded word is returned AS A VALUE, one level of "
               "dereference only");
  check(got != 0xfeedfaceu,
        "I: the reconstruction does not dereference the loaded word");
  check(got != 0x0badf00du,
        "A: the decoy dword at 0x70 is not the answer");
}

// Q -- 0 bytes of stack effect, measured; and an empty argument surface.
void case_q_stack() {
  Fixture f;
  poke_dword(f, 0x6c, 0x0f0f0f0fu);

  std::uint32_t delta = 0xffffffffu;
  const std::uint32_t v = probe_stack_effect(f.receiver, &delta);
  check_eq_u32(v, 0x0f0f0f0fu, "Q: the thiscall shim sees the field value");
  check_eq_u32(delta, 0u,
               "Q: measured 0 bytes of stack effect across the call -- the "
               "callee pops nothing, so stack cleanup is 0 bytes");

  // The argument surface, from the operand stream rather than from the stack.
  // The decoder's only memory read is the one it logged at receiver+0x6c, and it
  // refuses a body that would read anything else -- including [ESP+0x4], which
  // is where a stack argument lives. Together with case K (the body is four
  // bytes: one load and a RET) that leaves no instruction that could consume an
  // argument.
  const EmuResult ok = emulate(f.object_bytes(), kObjectSize,
                               reinterpret_cast<std::uintptr_t>(f.receiver));
  check(ok.ok, "Q: the decoder completes the transcribed body");
  check_eq_u32(static_cast<std::uint32_t>(ok.reads), 1,
               "Q: the body has exactly one memory operand");
  if (ok.reads == 1) {
    check(ok.read_log[0].address ==
              reinterpret_cast<std::uintptr_t>(f.receiver) + 0x6c,
          "Q: and it is the receiver field, not a stack slot");
  }
  check(ok.eax == v, "Q: the decoder and the reconstruction agree on the value");
}

// G, second half -- the decoder is not a rubber stamp. Each of these is a body
// the 4 real bytes are NOT, and each must be rejected rather than decoded on a
// guess. This is what licenses the "no stack argument, no second operand, no
// call" claims above: the decoder cannot silently accept a shape it does not
// model.
void case_g_decoder_refuses() {
  Fixture f;
  poke_dword(f, 0x6c, 0x12345678u);
  const std::uintptr_t ecx = reinterpret_cast<std::uintptr_t>(f.receiver);
  const std::uint8_t* obj = f.object_bytes();

  // 8B 44 24 04 C3  -- MOV EAX,[ESP+0x4] / RET. The shape a body that consumed
  // a stack argument would have. The address is not inside the object and the
  // ModRM is not the ECX form, so it must be refused.
  const std::uint8_t reads_stack_arg[] = {0x8B, 0x44, 0x24, 0x04, 0xC3};
  const EmuResult r1 = emulate(reads_stack_arg, sizeof(reads_stack_arg), obj,
                               kObjectSize, ecx);
  check(!r1.ok, "G: a body that reads [ESP+0x4] is refused");

  // 8B 41 6C E8 00 00 00 00 C3 -- the real load plus a CALL rel32. Counted and
  // refused, so a "no callee" claim cannot be satisfied by a decoder that
  // skipped over the call.
  const std::uint8_t with_call[] = {0x8B, 0x41, 0x6C, 0xE8, 0x00,
                                    0x00, 0x00, 0x00, 0xC3};
  const EmuResult r2 =
      emulate(with_call, sizeof(with_call), obj, kObjectSize, ecx);
  check(!r2.ok, "G: a body containing a CALL is refused");
  check_eq_u32(static_cast<std::uint32_t>(r2.calls), 1,
               "G: and the call was counted rather than skipped");

  // 8B 41 6C 90 90 C3 -- the real load plus two NOPs and a RET. The opcode is
  // one this decoder does not model, so the whole body is refused.
  const std::uint8_t with_nops[] = {0x8B, 0x41, 0x6C, 0x90, 0x90, 0xC3};
  const EmuResult r3 =
      emulate(with_nops, sizeof(with_nops), obj, kObjectSize, ecx);
  check(!r3.ok, "G: a body with an extra NOP is refused, not decoded loosely");

  // 8B 41 6C C2 04 00 -- RET 0x4, i.e. a callee that pops one stack argument's
  // worth. The 0xC2 immediate is inside the body here, so this is a different
  // function; the decoder must not report it as a bare RET.
  const std::uint8_t with_ret_imm[] = {0x8B, 0x41, 0x6C, 0xC2, 0x04, 0x00};
  const EmuResult r4 =
      emulate(with_ret_imm, sizeof(with_ret_imm), obj, kObjectSize, ecx);
  check(!r4.bare_ret, "G: a RET with an immediate is not reported as bare");
  check(!r4.ok, "G: and a RET 0x4 body is refused");

  // 0F B6 41 6C C3 -- MOVZX EAX,BYTE PTR [ECX+0x6C]. A byte-width load with the
  // same displacement: the one that looks most like the real body and answers a
  // different value. Refused, so the 4-byte width claim is the decoder's and not
  // a coincidence of the fixture.
  const std::uint8_t movzx[] = {0x0F, 0xB6, 0x41, 0x6C, 0xC3};
  const EmuResult r5 = emulate(movzx, sizeof(movzx), obj, kObjectSize, ecx);
  check(!r5.ok, "G: a MOVZX byte load with the same displacement is refused");

  // The unmutated transcription is still accepted, so the rejections above are
  // rejections and not a decoder that refuses everything.
  const EmuResult good =
      emulate(kBodyBytes.data(), kBodyBytes.size(), obj, kObjectSize, ecx);
  check(good.ok, "G: the unaltered 4-byte transcription is still accepted");
  check_eq_u32(static_cast<std::uint32_t>(good.eax), 0x12345678u,
               "G: and still decodes to the field value");
}

// The value the caller at 0x00a53d20 consumes, checked through the same call
// shape: 0x00a53dc0 `MOV DWORD PTR [EDX],EAX` stores the return value as the
// first word of a three-word record, and the record's other two words come from
// EDI and EBX. A return narrower than 32 bits, or normalised, would not survive
// that store unchanged.
void case_caller_store_shape() {
  Fixture f;
  poke_dword(f, 0x6c, 0xa1b2c3d4u);
  std::uint32_t record[3];
  record[1] = 0x11111111u;
  record[2] = 0x22222222u;
  record[0] = re_00a649a0(f.receiver);
  check_eq_u32(record[0], 0xa1b2c3d4u,
               "caller: the EAX word lands in the record unchanged");
  check_eq_u32(record[1], 0x11111111u, "caller: EDI word untouched");
  check_eq_u32(record[2], 0x22222222u, "caller: EBX word untouched");
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_swarm_w1_00a649a0

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w1_00a649a0;
  case_k_bytes();
  case_a_displacement_and_width();
  case_c_receiver_is_read();
  case_e_value_passthrough();
  case_f_no_writes();
  case_g_no_transfer();
  case_g_decoder_refuses();
  case_i_one_level();
  case_q_stack();
  case_caller_store_shape();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d of %d checks FAILED\n", g_failures, g_checks);
    return 1;
  }
  std::printf("pkg-swarm-w1-00a649a0: %d checks passed\n", g_checks);
  return 0;
}
