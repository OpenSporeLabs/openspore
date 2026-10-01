// PKG-SWARM-W1-00EC4280 -- VA 0x00ec4280
// reconstruction/staging/pkg-swarm-w1-00ec4280/sw1_00ec4280_model_test.cpp
//
// A falsification test for re_00ec4280. Its job is to try to BREAK the
// reconstruction, not to walk it.
//
// SHAPE OF THE ARGUMENT
// ----------------------
//  1. Both direct callees are defined here as OBSERVERS. Each records which
//     pointer it received, in what order, and what the receiver's three vptr
//     words looked like AT THE MOMENT OF THE CALL -- which is how this test sees
//     the write ordering rather than only the end state. (The end state alone is
//     not enough: 0x00642190 overwrites the same three words, so a wrong
//     constant in the body under reconstruction is invisible at the end and only
//     shows up as what the callee saw on entry.)
//  2. An INDEPENDENT ORACLE decodes the 14 instruction bytes of the body opcode
//     by opcode over a flat byte image. The oracle was written from the byte
//     string, not from the .cpp, so a mistake in the .cpp surfaces as a
//     disagreement instead of agreeing with it.
//  3. The ORACLE IS ITSELF MUTATION-TESTED. Seven deliberately corrupted copies
//     of the body are run through it and each must produce a different
//     observable. A checker that cannot fail is not a checker, and this proves
//     the comparisons have teeth before they are used to convict the
//     reconstruction.
//  4. The reconstruction and the oracle are then run over the same initial
//     memory for all 256 flag values and several fills; their full memory images,
//     call traces and return values must agree exactly.
//
// WHAT IS ASSERTED, AND WHAT IS DELIBERATELY NOT ASSERTED
// -------------------------------------------------------
// ASSERTED, because the listing fixes it: the three vptr displacements
// (0x00 / 0x10 / 0x14) and their exact immediates; the order the three stores
// run in; that the destroy callee is called with the receiver and with nothing
// pushed; that the flag byte is read AFTER that call returns; that the branch is
// JZ on mask 0x01 over a BYTE; that the free receives the receiver itself; that
// the return value is the receiver on both arms; and that no byte outside
// +0x00 / +0x10 / +0x14 moves.
//
// NOT ASSERTED, and why:
//  * The FINAL vptr values in the running program. They are written by
//    0x00642190 and by the 0x006412A0 it tail-transfers to, both other
//    packages' targets. The observers here EMULATE those stores, so this test
//    proves the reconstruction passes the right receiver and does not re-apply
//    its own vptrs afterwards; it does NOT claim the real callee writes exactly
//    what the observer writes. The three constants are instead checked against
//    the callee's own bytes in T1.
//  * Anything about the other seven bits of the flag byte. Only bit 0 is tested
//    by this body, so the test only asserts that bit 0 selects the free.
//  * The three bytes at entry_ESP+0x5..0x7. RET 0x4 proves the slot is four
//    bytes wide; the BYTE read at 0x00ec429C proves only the low byte is used.
//    The C++ signature takes std::uint8_t, so this file cannot hand the model a
//    dirty upper half the way the machine could see one, and a model that wrongly
//    read all four bytes would slip past it. The single-byte read is asserted
//    structurally instead: the 0xF6 /0 opcode form in the oracle decoder, in T1.
//  * The class name. No MSVC RTTI survives in this binary, so nothing here names
//    the class; the type name is for readability only.
//  * Any runtime behaviour. Nothing in this repository contains a trace of the
//    original process, and no run was attempted.

#include "sw1_00ec4280_types.hpp"

#include <array>
#include <cstdint>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

namespace {

using openspore::reconstruction::pkg_swarm_w1_00ec4280::kDeleteFlagMask;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kThisBodyEntryPoint;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrDisplacementPrimary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrDisplacementSecondary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrDisplacementTertiary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrPrimary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrSecondary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::kVptrTertiary;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::re_00ec4280;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::SporepediaOnlineAsset;
using openspore::reconstruction::pkg_swarm_w1_00ec4280::word_at;
namespace sw1 = openspore::reconstruction::pkg_swarm_w1_00ec4280;

int g_failures = 0;

void check(bool ok, const std::string& what) {
  if (!ok) {
    std::printf("  FAIL  %s\n", what.c_str());
    ++g_failures;
  }
}

void check_word(std::uint32_t got, std::uint32_t want, const std::string& what) {
  if (got != want) {
    std::printf("  FAIL  %s: got 0x%08x want 0x%08x\n", what.c_str(), got, want);
    ++g_failures;
  }
}

std::string hex2(std::uint32_t v) {
  char buf[16];
  std::snprintf(buf, sizeof(buf), "0x%02x", v & 0xFFu);
  return std::string(buf);
}

// ---------------------------------------------------------------------------
// The bytes this package is transcribed from, re-read from
// SPORE/SporeBin/SporeApp.exe 3.1.0.22 (sha256 25d42a7a...9d914e). They are
// embedded so a reviewer can diff the oracle's decoder against the artifact
// directly, and so the test fails loudly if the transcription ever drifts.
// ---------------------------------------------------------------------------
// 568bf1c7 0690904801 c74610 7c904801 c74614 6c904801 e8f4de77ff f6442408
// 01 7409 56 e8d7300800 83c404 8bc6 5e c20400
const std::array<std::uint8_t, 50> kBodyBytes = {
    0x56, 0x8b, 0xf1, 0xc7, 0x06, 0x90, 0x90, 0x48, 0x01, 0xc7, 0x46, 0x10, 0x7c,
    0x90, 0x48, 0x01, 0xc7, 0x46, 0x14, 0x6c, 0x90, 0x48, 0x01, 0xe8, 0xf4, 0xde,
    0x77, 0xff, 0xf6, 0x44, 0x24, 0x08, 0x01, 0x74, 0x09, 0x56, 0xe8, 0xd7, 0x30,
    0x08, 0x00, 0x83, 0xc4, 0x04, 0x8b, 0xc6, 0x5e, 0xc2, 0x04, 0x00};

// The first 23 bytes of 0x00642190: enough to fix the three vptr stores that body
// performs before anything else. No claim is made here about the rest of it.
const std::array<std::uint8_t, 23> kDestroyBytes = {
    0x56, 0x8b, 0xf1, 0xc7, 0x06, 0x48, 0xf6, 0x3f, 0x01, 0xc7, 0x46, 0x10, 0x48,
    0x27, 0x46, 0x01, 0xc7, 0x46, 0x14, 0x38, 0x27, 0x46, 0x01};

// 0x00F47380 in full: MOV EAX,[ESP+4] / TEST EAX,EAX / JZ +0x0C /
// MOV ECX,[0x016C8B44] / PUSH EAX / CALL 0x009376C0 / RET.
const std::array<std::uint8_t, 21> kFreeBytes = {
    0x8b, 0x44, 0x24, 0x04, 0x85, 0xc0, 0x74, 0x0c, 0x8b, 0x0d, 0x44,
    0x8b, 0x6c, 0x01, 0x50, 0xe8, 0x2c, 0x03, 0x9e, 0xff, 0xc3};

constexpr std::uint32_t kEntryPoint = 0x00EC4280u;
constexpr std::uint32_t kDestroyEntry = 0x00642190u;
constexpr std::uint32_t kFreeEntry = 0x00F47380u;

std::uint32_t read_le32(const std::uint8_t* p) {
  return static_cast<std::uint32_t>(p[0]) | (static_cast<std::uint32_t>(p[1]) << 8) |
         (static_cast<std::uint32_t>(p[2]) << 16) | (static_cast<std::uint32_t>(p[3]) << 24);
}

std::uint32_t g_destroy_vptr_primary = 0;
std::uint32_t g_destroy_vptr_secondary = 0;
std::uint32_t g_destroy_vptr_tertiary = 0;

// Pull the three (displacement, immediate) pairs out of the C7 06 / C7 46 forms in
// the callee's own prologue. A pure decoder: it assumes nothing about what the
// stores MEAN, only where the bytes put them.
void decode_destroy_vptrs() {
  g_destroy_vptr_primary = 0;
  g_destroy_vptr_secondary = 0;
  g_destroy_vptr_tertiary = 0;
  std::size_t i = 0;
  int seen = 0;
  while (i + 6 <= kDestroyBytes.size() && seen < 3) {
    std::uint32_t imm = 0;
    if (kDestroyBytes[i] == 0xc7 && kDestroyBytes[i + 1] == 0x06) {
      imm = read_le32(&kDestroyBytes[i + 2]);
      i += 6;
    } else if (kDestroyBytes[i] == 0xc7 && kDestroyBytes[i + 1] == 0x46) {
      imm = read_le32(&kDestroyBytes[i + 3]);
      i += 7;
    } else {
      ++i;
      continue;
    }
    if (seen == 0) g_destroy_vptr_primary = imm;
    if (seen == 1) g_destroy_vptr_secondary = imm;
    if (seen == 2) g_destroy_vptr_tertiary = imm;
    ++seen;
  }
}

// ---------------------------------------------------------------------------
// A trace entry. `arg_offset` is the callee's argument as a byte offset from the
// start of the buffer, so a real pointer from the model and an index from the
// oracle compare directly.
// ---------------------------------------------------------------------------
struct Event {
  enum class Kind { kDestroy, kFree, kUnresolved };
  Kind kind = Kind::kUnresolved;
  std::size_t arg_offset = 0;
  std::uint32_t vptr_at_call[3] = {0, 0, 0};
  std::size_t pc_at_call = 0;
};

bool operator==(const Event& a, const Event& b) {
  if (a.kind != b.kind || a.arg_offset != b.arg_offset || a.pc_at_call != b.pc_at_call) {
    return false;
  }
  for (int i = 0; i < 3; ++i) {
    if (a.vptr_at_call[i] != b.vptr_at_call[i]) return false;
  }
  return true;
}

std::string describe(const Event& e) {
  const char* k = e.kind == Event::Kind::kDestroy
                      ? "destroy"
                      : (e.kind == Event::Kind::kFree ? "free" : "UNRESOLVED-CALL");
  char buf[192];
  std::snprintf(buf, sizeof(buf), "%s(arg=+0x%zx) saw vptrs [%08x %08x %08x]", k,
                e.arg_offset, e.vptr_at_call[0], e.vptr_at_call[1], e.vptr_at_call[2]);
  return std::string(buf);
}

// ===========================================================================
// The independent oracle: a tiny interpreter for exactly the opcodes the body
// uses. It decodes kBodyBytes (or a mutated copy) and steps until RET. It shares
// no code with sw1_00ec4280.cpp.
// ===========================================================================
constexpr std::size_t kImageBytes = 0x200;
constexpr std::size_t kObjectOffset = 0x20;  // leaves guard bytes below the object

struct OracleResult {
  bool decoded = false;
  std::string stop_reason;
  std::array<std::uint8_t, kImageBytes> image{};
  std::vector<Event> trace;
  std::uint32_t returned = 0;
  bool returned_valid = false;
};

struct Oracle {
  const std::uint8_t* code = nullptr;
  std::size_t code_len = 0;
  std::uint32_t base_pc = 0;
  std::size_t pc = 0;
  std::array<std::uint32_t, 8> regs{};  // 0=EAX 1=ECX 2=EDX 3=EBX 4=(esp) 5=EBP 6=ESI
  bool zf = false;
  int sp = 8;  // ESP as a word index into `stack`; [ESP+n] is stack[sp+n]
  std::array<std::uint32_t, 64> stack{};
  OracleResult out{};

  void push(std::uint32_t v) { stack[static_cast<std::size_t>(--sp)] = v; }
  std::uint32_t pop() { return stack[static_cast<std::size_t>(sp++)]; }

  std::uint32_t load32(std::size_t addr) const {
    std::uint32_t v = 0;
    for (int i = 0; i < 4; ++i) v |= static_cast<std::uint32_t>(out.image[addr + i]) << (8 * i);
    return v;
  }
  void store32(std::size_t addr, std::uint32_t v) {
    for (int i = 0; i < 4; ++i) out.image[addr + i] = static_cast<std::uint8_t>(v >> (8 * i));
  }
  std::size_t esi_addr() const { return kObjectOffset + static_cast<std::size_t>(regs[6]); }

  void fail(const char* why) {
    out.stop_reason = why;
    out.decoded = false;
  }

  void run() {
    out.trace.clear();
    out.decoded = true;
    out.returned_valid = false;
    int steps = 0;
    while (steps++ < 200) {
      if (pc >= code_len) {
        fail("ran off the end of the body without a RET");
        return;
      }
      const std::uint8_t op = code[pc];
      switch (op) {
        case 0x56:  // PUSH ESI
          push(regs[6]);
          pc += 1;
          break;
        case 0x5e:  // POP ESI
          regs[6] = pop();
          pc += 1;
          break;
        case 0x8b: {  // MOV r32, r/m32 -- the two register forms the body uses
          const std::uint8_t modrm = code[pc + 1];
          if ((modrm >> 6) != 3u) {
            fail("0x8B with a memory source is not in this body");
            return;
          }
          const unsigned dst = (modrm >> 3) & 7u;
          const unsigned src = modrm & 7u;
          if (dst == 4u || src == 4u) {
            fail("0x8B touching ESP is not in this body");
            return;
          }
          regs[dst] = regs[src];
          pc += 2;
          break;
        }
        case 0xc7: {  // MOV r/m32, imm32
          const std::uint8_t modrm = code[pc + 1];
          const unsigned mod = modrm >> 6;
          const unsigned rm = modrm & 7u;
          if (rm != 6u) {
            fail("0xC7 with an unexpected r/m");
            return;
          }
          if (mod == 0u) {
            store32(esi_addr(), read_le32(&code[pc + 2]));
            pc += 6;
          } else if (mod == 1u) {
            store32(esi_addr() + code[pc + 2], read_le32(&code[pc + 3]));
            pc += 7;
          } else {
            fail("0xC7 with an unsupported mod");
            return;
          }
          break;
        }
        case 0xe8: {  // CALL rel32
          const std::int32_t rel = static_cast<std::int32_t>(read_le32(&code[pc + 1]));
          const std::uint32_t target =
              base_pc + static_cast<std::uint32_t>(pc + 5) + static_cast<std::uint32_t>(rel);
          Event ev{};
          ev.arg_offset = esi_addr();
          ev.vptr_at_call[0] = load32(kObjectOffset + kVptrDisplacementPrimary);
          ev.vptr_at_call[1] = load32(kObjectOffset + kVptrDisplacementSecondary);
          ev.vptr_at_call[2] = load32(kObjectOffset + kVptrDisplacementTertiary);
          ev.pc_at_call = pc;
          const int sp_before = sp;
          if (target == kDestroyEntry) {
            ev.kind = Event::Kind::kDestroy;
            // 0x00642190's first three actions, from its own bytes: the same three
            // vptr displacements carrying ITS immediates. Both callees push a
            // return address and pop it, so sp is unchanged across each call --
            // asserted here rather than assumed.
            store32(kObjectOffset + kVptrDisplacementPrimary, g_destroy_vptr_primary);
            store32(kObjectOffset + kVptrDisplacementSecondary, g_destroy_vptr_secondary);
            store32(kObjectOffset + kVptrDisplacementTertiary, g_destroy_vptr_tertiary);
          } else if (target == kFreeEntry) {
            ev.kind = Event::Kind::kFree;
            // 0x00F47380 writes nothing to the block it frees.
          } else {
            ev.kind = Event::Kind::kUnresolved;
          }
          if (sp_before != sp) {
            fail("callee left ESP unbalanced");
            return;
          }
          out.trace.push_back(ev);
          pc += 5;
          break;
        }
        case 0xf6: {  // TEST r/m8, imm8 -- the only 0xF6 form here is 44 24 d8 imm,
                      // a BYTE at [ESP+disp8]. (0xF7 would be the r/m32 form.)
          if (code[pc + 1] != 0x44 || code[pc + 2] != 0x24) {
            fail("0xF6 with an unexpected ModRM/SIB");
            return;
          }
          // The disp8 is in BYTES; `sp` indexes 32-bit words, so it divides by 4.
          // The machine's operand is a BYTE, so only the low half of that word is
          // examined -- which is what makes bits 1..7 of the slot irrelevant.
          const std::size_t slot = static_cast<std::size_t>(sp) + code[pc + 3] / 4u;
          const std::uint8_t at_slot = static_cast<std::uint8_t>(stack[slot] & 0xFFu);
          zf = ((at_slot & code[pc + 4]) == 0);
          pc += 5;
          break;
        }
        case 0x74: {  // JZ rel8
          const std::int8_t rel = static_cast<std::int8_t>(code[pc + 1]);
          pc += 2;
          if (zf) pc = static_cast<std::size_t>(static_cast<std::int64_t>(pc) + rel);
          break;
        }
        case 0x83: {  // ADD r/m32, imm8 -- only 83 C4 (mod=11, rm=100 == ESP)
          if (code[pc + 1] != 0xc4) {
            fail("0x83 with an unexpected ModRM");
            return;
          }
          sp += static_cast<int>(code[pc + 2]) / 4;
          pc += 3;
          break;
        }
        case 0xc2: {  // RET imm16
          const std::uint32_t bytes_to_pop =
              static_cast<std::uint32_t>(code[pc + 1]) |
              (static_cast<std::uint32_t>(code[pc + 2]) << 8);
          (void)pop();  // the return address
          sp += static_cast<int>(bytes_to_pop / 4);
          out.returned = regs[0];
          out.returned_valid = true;
          out.stop_reason = "RET";
          return;
        }
        default: {
          char buf[64];
          std::snprintf(buf, sizeof(buf), "unhandled opcode 0x%02x at body offset 0x%zx",
                        static_cast<unsigned>(op), pc);
          fail(buf);
          return;
        }
      }
    }
    fail("step limit");
  }
};

OracleResult run_oracle(const std::uint8_t* code, std::size_t len, std::uint32_t flag_word,
                        const std::array<std::uint8_t, kImageBytes>& initial) {
  Oracle o{};
  o.code = code;
  o.code_len = len;
  o.base_pc = kEntryPoint;
  o.regs.fill(0);
  o.regs[0] = 0xDEADBEEFu;  // a value the body must overwrite before returning
  o.sp = 8;
  o.stack.fill(0);
  o.stack[8] = 0x00BEEF00u;        // the caller's return address
  o.stack[9] = flag_word & 0xFFu;  // the argument slot; only its low byte is read
  o.out.image = initial;
  o.run();
  return o.out;
}

// ===========================================================================
// The real model, driven through real memory, with both callees as observers.
// ===========================================================================
struct ObserverState {
  std::vector<Event> trace;
  int destroy_calls = 0;
  int free_calls = 0;
  // The real 0x00F47380 writes nothing to the block it frees. The scribble is a
  // test hook used only in T7, to catch a reconstruction that returned the
  // object's current first word instead of the receiver.
  bool free_scribbles = false;
  std::uint32_t hook_calls = 0;
  std::uint32_t hook_vptrs[3] = {0, 0, 0};
  int hook_seen_events = 0;
  std::uint8_t hook_override = 0;
  bool hook_active = false;
};

ObserverState g_obs;
std::size_t g_buffer_base = 0;
std::size_t g_object_offset = 0;

std::size_t offset_of(const void* p) {
  return reinterpret_cast<std::size_t>(p) - g_buffer_base;
}

// The observers snapshot the receiver's vptrs from the CANONICAL object the test
// set up, never from the pointer they were handed. That is deliberate: the fact
// under test is "which pointer did the callee receive", and a reconstruction that
// hands a callee a wild pointer (a field of the object, say) must produce a clean
// FAILED ASSERTION naming the bad argument, not a segmentation fault inside the
// instrumentation. The argument itself is recorded in arg_offset and compared
// against the oracle's, and the writes are skipped when it is not the canonical
// object.
bool is_canonical(const void* p) {
  return p == reinterpret_cast<const void*>(g_buffer_base + g_object_offset);
}

extern "C" void SW1_00EC4280_THISCALL sporepedia_asset_destroy_00642190(
    SporepediaOnlineAsset* asset) {
  auto* canonical = reinterpret_cast<SporepediaOnlineAsset*>(g_buffer_base + g_object_offset);
  Event ev{};
  ev.kind = Event::Kind::kDestroy;
  ev.arg_offset = offset_of(asset);
  ev.pc_at_call = 0x17;  // the CALL's offset in the body
  ev.vptr_at_call[0] = *word_at(canonical, kVptrDisplacementPrimary);
  ev.vptr_at_call[1] = *word_at(canonical, kVptrDisplacementSecondary);
  ev.vptr_at_call[2] = *word_at(canonical, kVptrDisplacementTertiary);
  g_obs.trace.push_back(ev);
  ++g_obs.destroy_calls;
  if (!is_canonical(asset)) return;
  // The three vptr stores 0x00642190 performs first, from its own bytes.
  *word_at(canonical, kVptrDisplacementPrimary) = g_destroy_vptr_primary;
  *word_at(canonical, kVptrDisplacementSecondary) = g_destroy_vptr_secondary;
  *word_at(canonical, kVptrDisplacementTertiary) = g_destroy_vptr_tertiary;
}

extern "C" void SW1_00EC4280_CDECL deallocate_00f47380(void* block) {
  auto* canonical = reinterpret_cast<SporepediaOnlineAsset*>(g_buffer_base + g_object_offset);
  Event ev{};
  ev.kind = Event::Kind::kFree;
  ev.arg_offset = offset_of(block);
  ev.pc_at_call = 0x24;  // the CALL's offset in the body
  ev.vptr_at_call[0] = *word_at(canonical, kVptrDisplacementPrimary);
  ev.vptr_at_call[1] = *word_at(canonical, kVptrDisplacementSecondary);
  ev.vptr_at_call[2] = *word_at(canonical, kVptrDisplacementTertiary);
  g_obs.trace.push_back(ev);
  ++g_obs.free_calls;
  if (g_obs.free_scribbles && is_canonical(block)) {
    *word_at(canonical, kVptrDisplacementPrimary) = 0xA5A5A5A5u;
  }
}

std::uint8_t delete_flag_hook(std::uint8_t incoming) {
  ++g_obs.hook_calls;
  auto* asset = reinterpret_cast<SporepediaOnlineAsset*>(g_buffer_base + g_object_offset);
  g_obs.hook_vptrs[0] = *word_at(asset, kVptrDisplacementPrimary);
  g_obs.hook_vptrs[1] = *word_at(asset, kVptrDisplacementSecondary);
  g_obs.hook_vptrs[2] = *word_at(asset, kVptrDisplacementTertiary);
  g_obs.hook_seen_events = static_cast<int>(g_obs.trace.size());
  return g_obs.hook_active ? g_obs.hook_override : incoming;
}

void reset_observers() { g_obs = ObserverState{}; }

struct Bed {
  alignas(16) std::array<std::uint8_t, kImageBytes> bytes;
  SporepediaOnlineAsset* object() {
    return reinterpret_cast<SporepediaOnlineAsset*>(bytes.data() + kObjectOffset);
  }
};

struct ModelRun {
  std::array<std::uint8_t, kImageBytes> bytes{};
  std::size_t object_offset = 0;
  std::size_t return_offset = 0;
  bool return_valid = false;
};

std::array<std::uint8_t, kImageBytes> make_initial_fill(std::uint8_t pattern) {
  std::array<std::uint8_t, kImageBytes> f{};
  f.fill(pattern);
  // Distinct sentinels in the gaps the body must NOT touch, so a wrong
  // displacement (0x0C instead of 0x10, 0x18 instead of 0x14) shows up as a moved
  // byte rather than as a plausible-looking duplicate.
  const std::size_t gaps[] = {0x04, 0x08, 0x0c, 0x18, 0x1c, 0x20, 0x24};
  const std::uint32_t guards[] = {0xDEADC0DEu, 0x0BADF00Du, 0xFEEDFACEu, 0x0C0FFEE0u,
                                  0xAAAAAAAAu, 0x55555555u, 0x13572468u};
  for (std::size_t i = 0; i < sizeof(gaps) / sizeof(gaps[0]); ++i) {
    for (int b = 0; b < 4; ++b) {
      const std::size_t at = kObjectOffset + gaps[i] + static_cast<std::size_t>(b);
      if (at + 1 < kImageBytes) f[at] = static_cast<std::uint8_t>(guards[i] >> (8 * b));
    }
  }
  for (std::size_t i = 0x28; i < 0x30; ++i) {
    f[kObjectOffset + i] = static_cast<std::uint8_t>(0x5A + i);
  }
  return f;
}

// One complete run of the real reconstruction over real memory.
ModelRun run_model(std::uint8_t flags, const std::array<std::uint8_t, kImageBytes>& initial) {
  ModelRun r{};
  Bed bed{};
  bed.bytes = initial;
  auto* obj = bed.object();
  g_buffer_base = reinterpret_cast<std::size_t>(bed.bytes.data());
  g_object_offset = kObjectOffset;
  r.object_offset = offset_of(obj);
  SporepediaOnlineAsset* ret = re_00ec4280(obj, flags);
  r.return_offset = offset_of(ret);
  r.return_valid = true;
  r.bytes = bed.bytes;
  return r;
}

std::string trace_equal(const std::vector<Event>& a, const std::vector<Event>& b) {
  if (a.size() != b.size()) {
    char buf[96];
    std::snprintf(buf, sizeof(buf), "trace length %zu vs %zu", a.size(), b.size());
    return std::string(buf);
  }
  for (std::size_t i = 0; i < a.size(); ++i) {
    if (!(a[i] == b[i])) {
      return std::string("entry ") + std::to_string(i) + ": " + describe(a[i]) + " vs " +
             describe(b[i]);
    }
  }
  return std::string();
}

std::string image_diff(const std::array<std::uint8_t, kImageBytes>& a,
                       const std::array<std::uint8_t, kImageBytes>& b) {
  for (std::size_t i = 0; i < kImageBytes; ++i) {
    if (a[i] != b[i]) {
      char buf[160];
      std::snprintf(buf, sizeof(buf), "byte +0x%zx: model 0x%02x oracle 0x%02x", i, a[i], b[i]);
      return std::string(buf);
    }
  }
  return std::string();
}

// ===========================================================================
// T1. The transcription must match the image. Decode kBodyBytes and assert the
//     three vptr immediates, the tested mask and its BYTE operand, the JZ
//     polarity and target, the two call targets, and the terminator -- all out of
//     the bytes, so the header's constants are checked against the artifact and
//     not against prose.
// ===========================================================================
void test_transcription_matches_bytes() {
  std::printf("T1 transcription decoded from the body bytes\n");
  decode_destroy_vptrs();

  std::uint32_t prim = 0, sec = 0, ter = 0;
  int stores = 0, jz = 0, tests = 0, calls = 0;
  std::uint32_t call_target[2] = {0, 0};
  std::uint32_t mask = 0, ret_imm = 0, test_disp = 0xFF;
  bool byte_operand = false;
  bool jz_lands_on_shared_exit = false;
  std::size_t store_displacements[3] = {0, 0, 0};

  for (std::size_t i = 0; i + 2 < kBodyBytes.size();) {
    const std::uint8_t op = kBodyBytes[i];
    if (op == 0xc7 && kBodyBytes[i + 1] == 0x06 && stores < 3) {
      if (stores == 0) prim = read_le32(&kBodyBytes[i + 2]);
      store_displacements[stores] = 0;
      ++stores;
      i += 6;
    } else if (op == 0xc7 && kBodyBytes[i + 1] == 0x46 && stores < 3) {
      if (stores == 1) sec = read_le32(&kBodyBytes[i + 3]);
      if (stores == 2) ter = read_le32(&kBodyBytes[i + 3]);
      store_displacements[stores] = kBodyBytes[i + 2];
      ++stores;
      i += 7;
    } else if (op == 0xf6 && kBodyBytes[i + 1] == 0x44 && kBodyBytes[i + 2] == 0x24) {
      byte_operand = true;  // 0xF6 /0 is the r/m8 form; 0xF7 would be r/m32
      test_disp = kBodyBytes[i + 3];
      mask = kBodyBytes[i + 4];
      ++tests;
      i += 5;
    } else if (op == 0x74) {
      const std::int8_t rel = static_cast<std::int8_t>(kBodyBytes[i + 1]);
      ++jz;
      jz_lands_on_shared_exit = ((i + 2 + static_cast<std::size_t>(rel)) == 0x2c);
      i += 2;
    } else if (op == 0xe8) {
      if (calls < 2) {
        // rel32 is signed and the addition is 32-bit wraparound, exactly as the
        // CPU forms a call target.
        const std::int32_t rel = static_cast<std::int32_t>(read_le32(&kBodyBytes[i + 1]));
        call_target[calls] = kEntryPoint + static_cast<std::uint32_t>(i) + 5u +
                             static_cast<std::uint32_t>(rel);
      }
      ++calls;
      i += 5;
    } else if (op == 0xc2) {
      ret_imm = static_cast<std::uint32_t>(kBodyBytes[i + 1]) |
                (static_cast<std::uint32_t>(kBodyBytes[i + 2]) << 8);
      i += 3;
      break;
    } else {
      ++i;
    }
  }

  check_word(prim, kVptrPrimary, "primary vptr immediate out of the bytes");
  check_word(sec, kVptrSecondary, "secondary vptr immediate out of the bytes");
  check_word(ter, kVptrTertiary, "tertiary vptr immediate out of the bytes");
  check(stores == 3, "exactly three C7 vptr stores in the body");
  check(store_displacements[0] == kVptrDisplacementPrimary, "store 1 is at displacement +0x00");
  check(store_displacements[1] == kVptrDisplacementSecondary, "store 2 is at displacement +0x10");
  check(store_displacements[2] == kVptrDisplacementTertiary, "store 3 is at displacement +0x14");
  check(calls == 2, "exactly two direct calls");
  check_word(call_target[0], kDestroyEntry, "first call target is 0x00642190");
  check_word(call_target[1], kFreeEntry, "second call target is 0x00F47380");
  check(tests == 1, "exactly one TEST");
  check(byte_operand, "the TEST reads a BYTE (opcode 0xF6, not 0xF7)");
  check_word(test_disp, 0x08, "the TEST operand is [ESP+0x8]");
  check_word(mask, kDeleteFlagMask, "the tested mask is 0x01");
  check(jz == 1, "exactly one conditional branch");
  check(jz_lands_on_shared_exit, "the JZ lands on 0x00ec42AC, the shared exit");
  check_word(ret_imm, 0x0004, "terminator is RET 0x4 (callee-owned cleanup)");
  check_word(kThisBodyEntryPoint, kEntryPoint, "the header's entry-point constant");

  // The callee's own bytes, so the observers' constants are evidence-backed too.
  check_word(g_destroy_vptr_primary, 0x013FF648u, "0x00642190's own first vptr store");
  check_word(g_destroy_vptr_secondary, 0x01462748u, "0x00642190's own second vptr store");
  check_word(g_destroy_vptr_tertiary, 0x01462738u, "0x00642190's own third vptr store");
  check(g_destroy_vptr_primary != kVptrPrimary,
        "the callee's triple differs from this body's, which is why the three stores "
        "here are transient");

  // 0x00F47380 must be a bare-RET cdecl one-argument port, or the model's cdecl
  // declaration is unfounded.
  check(kFreeBytes[0] == 0x8b && kFreeBytes[1] == 0x44 && kFreeBytes[2] == 0x24 &&
            kFreeBytes[3] == 0x04,
        "0x00F47380 reads its argument at [ESP+0x4]");
  check(kFreeBytes[kFreeBytes.size() - 1] == 0xc3, "0x00F47380 ends in a bare RET");

  // The modelled receiver must be able to hold every word the body writes.
  static_assert(sizeof(SporepediaOnlineAsset) == 0x18, "modelled receiver size");
  static_assert(kVptrDisplacementTertiary + sizeof(std::uint32_t) ==
                    sizeof(SporepediaOnlineAsset),
                "the highest vptr word ends the modelled receiver");
  static_assert(sizeof(std::uint8_t) == 1, "the flag argument is one byte wide");
}

// ===========================================================================
// T2. THE ORACLE HAS TEETH. Seven corrupted copies of the body must NOT look
//     like this one. Without this, T3 could pass for the wrong reasons.
// ===========================================================================
void test_oracle_rejects_mutations() {
  std::printf("T2 mutation check: a corrupted body must NOT look like this one\n");
  const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(0x11);

  struct Mutation {
    const char* name;
    std::vector<std::pair<std::size_t, std::uint8_t>> edits;
  };
  // Byte offsets are into kBodyBytes. The "retarget" edit recomputes the rel32 so
  // the first call really does land on 0x00F47380:
  // 0x00F47380 - (0x00EC4280 + 0x17 + 5) = 0x000830D8.
  const std::vector<Mutation> mutations = {
      {"wrong primary constant (0x01489091)", {{5, 0x91}}},
      {"wrong secondary displacement (+0x0c)", {{11, 0x0c}}},
      {"wrong tertiary displacement (+0x18)", {{18, 0x18}}},
      {"branch polarity JZ -> JNZ", {{33, 0x75}}},
      {"wrong test mask (0x02)", {{32, 0x02}}},
      {"PUSH ESI -> PUSH EBX before the free", {{35, 0x5b}}},
      {"first call retargeted to the free", {{24, 0xd8}, {25, 0x30}, {26, 0x08}, {27, 0x00}}},
  };

  // Each mutation is scanned across ALL 256 flag values and must be detected for
  // at least one of them. A single flag is not enough: some mutations are
  // provably EQUIVALENT for particular inputs (mask 0x02 behaves identically to
  // mask 0x01 when the flag byte is 0x00, and the PUSH before the free is dead
  // code when the free is not taken), and demanding detection on those inputs
  // would be demanding that the checker detect a difference that is not there.
  const OracleResult probe = run_oracle(kBodyBytes.data(), kBodyBytes.size(), 0x00, initial);
  check(probe.decoded && probe.stop_reason == "RET", "the unmutated body decodes and reaches its RET");

  for (const Mutation& m : mutations) {
    std::vector<std::uint8_t> mutated(kBodyBytes.begin(), kBodyBytes.end());
    for (const auto& e : m.edits) mutated[e.first] = e.second;
    int detected_at = -1;
    for (int flag = 0; flag < 256 && detected_at < 0; ++flag) {
      const OracleResult good =
          run_oracle(kBodyBytes.data(), kBodyBytes.size(), static_cast<std::uint32_t>(flag), initial);
      const OracleResult bad =
          run_oracle(mutated.data(), mutated.size(), static_cast<std::uint32_t>(flag), initial);
      bool differs = !bad.decoded || bad.image != good.image ||
                     bad.trace.size() != good.trace.size() || bad.returned != good.returned;
      if (!differs) {
        for (std::size_t i = 0; i < bad.trace.size(); ++i) {
          if (!(bad.trace[i] == good.trace[i])) differs = true;
        }
      }
      if (differs) detected_at = flag;
    }
    char buf[224];
    std::snprintf(buf, sizeof(buf), "mutation detected: %s (first at flags=%s)",
                  m.name, detected_at < 0 ? "NEVER" : hex2(static_cast<std::uint32_t>(detected_at)).c_str());
    check(detected_at >= 0, buf);
  }
}

// ===========================================================================
// T3. THE MAIN CHECK. The reconstruction must agree with the independent oracle
//     on the entire memory image, the entire call trace (including what each
//     callee saw on entry) and the return value, for all 256 flag values and
//     three initial fills.
// ===========================================================================
void test_model_agrees_with_oracle() {
  std::printf("T3 reconstruction vs the byte-level oracle, 256 flags x 3 fills\n");
  decode_destroy_vptrs();
  for (std::uint8_t fill : {std::uint8_t{0x00}, std::uint8_t{0x11}, std::uint8_t{0xCD}}) {
    const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(fill);
    for (int flag = 0; flag < 256; ++flag) {
      reset_observers();
      const ModelRun m = run_model(static_cast<std::uint8_t>(flag), initial);
      const OracleResult o =
          run_oracle(kBodyBytes.data(), kBodyBytes.size(), static_cast<std::uint32_t>(flag), initial);
      const std::string tag = " [fill=" + hex2(fill) + " flags=" + hex2(static_cast<std::uint32_t>(flag)) + "]";

      if (!o.decoded) {
        check(false, std::string("oracle failed on the real body") + tag);
        continue;
      }
      const std::string di = image_diff(m.bytes, o.image);
      check(di.empty(), std::string("memory image agrees with the oracle") + tag +
                             (di.empty() ? "" : " -- " + di));
      const std::string dt = trace_equal(g_obs.trace, o.trace);
      check(dt.empty(), std::string("call trace agrees with the oracle") + tag +
                             (dt.empty() ? "" : " -- " + dt));
      check_word(static_cast<std::uint32_t>(m.return_offset),
                 static_cast<std::uint32_t>(kObjectOffset),
                 std::string("return value is the receiver") + tag);
      // Coordinate note: in the oracle the receiver's address is held in a
      // REGISTER as the offset 0 (the image base is added only on access), so
      // EAX is 0 there and kObjectOffset once expressed as a buffer offset. The
      // one comparison that matters is between the two forms.
      check(o.returned_valid && o.returned + static_cast<std::uint32_t>(kObjectOffset) ==
                                     m.return_offset,
            std::string("oracle EAX agrees with the model's returned receiver") + tag);
    }
  }
}

// ===========================================================================
// T4. BRANCH POLARITY AND THE MASK, exhaustively and by name. Bit 0 and ONLY bit
//     0 selects the free. The decoys are the flag values a "non-zero", "any high
//     bit", "any bit at all" or "~1" reading would get wrong.
// ===========================================================================
void test_only_bit_zero_selects_the_free() {
  std::printf("T4 branch polarity and mask, exhaustive over the flag byte\n");
  decode_destroy_vptrs();
  const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(0x33);
  int free_when_set = 0, free_when_clear = 0;
  for (int flag = 0; flag < 256; ++flag) {
    reset_observers();
    (void)run_model(static_cast<std::uint8_t>(flag), initial);
    const bool expect_free = ((flag & 0x01) != 0);
    if (expect_free) ++free_when_set;
    else ++free_when_clear;
    if ((g_obs.free_calls == 1) != expect_free) {
      check(false, "free flag mismatch at " + hex2(static_cast<std::uint32_t>(flag)));
    }
  }
  check(free_when_set == 128, "exactly 128 of 256 flag values take the free arm");
  check(free_when_clear == 128, "the other 128 do not");

  struct Decoy {
    std::uint8_t flags;
    bool expect_free;
    const char* hypothesis_it_kills;
  };
  const std::vector<Decoy> decoys = {
      {0x00, false, "'any non-zero'"},
      {0x01, true, "'never frees'"},
      {0x02, false, "mask 0x02"},
      {0x04, false, "mask 0x04"},
      {0x03, true, "mask 0x03"},
      {0x05, true, "mask 0x05"},
      {0x06, false, "mask 0x06"},
      {0x80, false, "'signed negative counts as set'"},
      {0x81, true, "'signed negative counts as clear'"},
      {0xFE, false, "mask ~1"},
      {0xFF, true, "mask ~1e"},
      {0x40, false, "the high half of the argument slot"},
      {0x10, false, "byte 1 of the argument slot"},
      {0x7E, false, "'any bit at all'"},
      {0x7F, true, "'bit 0 is not the one that matters'"},
  };
  for (const Decoy& d : decoys) {
    reset_observers();
    (void)run_model(d.flags, initial);
    char buf[192];
    std::snprintf(buf, sizeof(buf), "flags=%s free=%d (kills: %s)", hex2(d.flags).c_str(),
                  g_obs.free_calls, d.hypothesis_it_kills);
    check((g_obs.free_calls == 1) == d.expect_free, buf);
  }
}

// ===========================================================================
// T5. WRONG CONSTANT, WRONG DISPLACEMENT, WRONG RECEIVER LEVEL. Sample the
//     receiver from INSIDE the body, at the machine's own flag-read point, so the
//     three immediates are observed rather than inferred, and check every
//     neighbouring offset for a decoy write.
// ===========================================================================
void test_vptr_writes_are_exact_and_in_place() {
  std::printf("T5 exact vptr immediates, displacements, untouched neighbours\n");
  decode_destroy_vptrs();
  const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(0x44);

  sw1::sw1_delete_flag_read_hook = &delete_flag_hook;
  reset_observers();
  const ModelRun m = run_model(0x00, initial);

  check(g_obs.hook_calls == 1, "the flag read point is reached exactly once");

  // The three immediates are visible ONLY on entry to the destroy callee, because
  // 0x00642190 overwrites the same three words before this body's flag read. Two
  // observations, two different facts:
  //   trace[0].vptr_at_call  == this body's immediates  (the three stores ran)
  //   hook_vptrs             == the callee's immediates (the call already returned)
  // Asserting the wrong one of these would be asserting nothing, and asserting
  // only the end state would not notice a wrong constant at all.
  check(g_obs.trace.size() == 1 && g_obs.trace[0].kind == Event::Kind::kDestroy,
        "the only call before the flag read is the destroy");
  if (!g_obs.trace.empty()) {
    check_word(g_obs.trace[0].vptr_at_call[0], kVptrPrimary,
               "on entry to the destroy, +0x00 already holds 0x01489090");
    check_word(g_obs.trace[0].vptr_at_call[1], kVptrSecondary,
               "on entry to the destroy, +0x10 already holds 0x0148907C");
    check_word(g_obs.trace[0].vptr_at_call[2], kVptrTertiary,
               "on entry to the destroy, +0x14 already holds 0x0148906C");
  }
  // The read point must already show the CALLEE's triple: the CALL at 0x00ec4297
  // precedes the TEST at 0x00ec429C.
  check_word(g_obs.hook_vptrs[0], g_destroy_vptr_primary,
             "at the flag read, +0x00 already holds the callee's 0x013FF648: the read "
             "is after the call");
  check_word(g_obs.hook_vptrs[1], g_destroy_vptr_secondary,
             "at the flag read, +0x10 already holds the callee's 0x01462748");
  check_word(g_obs.hook_vptrs[2], g_destroy_vptr_tertiary,
             "at the flag read, +0x14 already holds the callee's 0x01462738");
  check(g_obs.hook_seen_events == 1, "exactly one call is on the trace when the flag is read");

  // No neighbouring byte may move. Sentinels from make_initial_fill cover
  // +0x04..+0x0f, +0x18..+0x1f and +0x28..+0x2f.
  for (std::size_t off : {0x04, 0x08, 0x0c, 0x18, 0x1c, 0x20, 0x24}) {
    for (int b = 0; b < 4; ++b) {
      const std::size_t at = kObjectOffset + off + static_cast<std::size_t>(b);
      check_word(m.bytes[at], initial[at],
                 "sentinel at +" + std::to_string(off + static_cast<std::size_t>(b)) +
                     " must not move");
    }
  }
  for (std::size_t off = 0x28; off < 0x30; ++off) {
    check_word(m.bytes[kObjectOffset + off], initial[kObjectOffset + off],
               "sentinel at +" + std::to_string(off) + " must not move");
  }
  // And below the object, for a store that walked backwards off the base.
  for (std::size_t i = 0; i < kObjectOffset; ++i) {
    check_word(m.bytes[i], initial[i], "byte at buffer -" + std::to_string(kObjectOffset - i) +
                                           " of the object must not move");
  }

  // The three words that DID move carry the callee's values, not this body's:
  // the three stores here are transient.
  check_word(read_le32(&m.bytes[kObjectOffset + 0x00]), g_destroy_vptr_primary,
             "final +0x00 is the callee's value");
  check_word(read_le32(&m.bytes[kObjectOffset + 0x10]), g_destroy_vptr_secondary,
             "final +0x10 is the callee's value, not 0x0148907C: the store is transient");
  check_word(read_le32(&m.bytes[kObjectOffset + 0x14]), g_destroy_vptr_tertiary,
             "final +0x14 is the callee's value, not 0x0148906C: the store is transient");

  // Wrong receiver level: the receiver IS the object, not a pointer to it. Plant a
  // pointer to a decoy object in the receiver's own first word; a body that
  // dereferenced once more would write the vptrs into the decoy.
  reset_observers();
  {
    Bed bed{};
    Bed decoy{};
    bed.bytes.fill(0x5B);
    decoy.bytes.fill(0xA7);
    auto* decoy_obj = decoy.object();
    *reinterpret_cast<std::uint32_t*>(bed.object()) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(decoy_obj));
    g_buffer_base = reinterpret_cast<std::size_t>(bed.bytes.data());
    g_object_offset = kObjectOffset;
    (void)re_00ec4280(bed.object(), 0x00);
    check_word(*word_at(decoy_obj, kVptrDisplacementPrimary), 0xA7A7A7A7u,
               "a second-level object is never written: the receiver is the object");
    check_word(*word_at(decoy_obj, kVptrDisplacementSecondary), 0xA7A7A7A7u,
               "a second-level object is never written at +0x10 either");
  }

  // Wrong base object: two objects, the second one must be untouched.
  reset_observers();
  {
    Bed bed{};
    bed.bytes.fill(0x99);
    g_buffer_base = reinterpret_cast<std::size_t>(bed.bytes.data());
    g_object_offset = kObjectOffset;
    const auto before = bed.bytes;
    (void)re_00ec4280(bed.object(), 0x01);
    for (std::size_t off = 0x18; off < 0x58; ++off) {
      check_word(bed.bytes[kObjectOffset + off], before[kObjectOffset + off],
                 "the neighbouring object is untouched at +" + std::to_string(off));
    }
  }

  sw1::sw1_delete_flag_read_hook = nullptr;
}

// ===========================================================================
// T6. WRONG CALLEE, WRONG ARGUMENT, WRONG ORDER, WRONG ADJUSTMENT. The observers
//     measure all of it.
// ===========================================================================
void test_callee_arguments_and_ordering() {
  std::printf("T6 callee identity, argument and ordering\n");
  decode_destroy_vptrs();
  const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(0x66);

  for (std::uint8_t flag : {std::uint8_t{0x00}, std::uint8_t{0x01}, std::uint8_t{0x03}}) {
    reset_observers();
    (void)run_model(flag, initial);
    const std::string tag = " [flags=" + hex2(flag) + "]";

    check(g_obs.destroy_calls == 1,
          std::string("the destroy callee runs exactly once, unconditionally") + tag);
    check(g_obs.free_calls == ((flag & 1) ? 1 : 0),
          std::string("the free callee runs once, on the deleting arm only") + tag);
    check(!g_obs.trace.empty(), std::string("at least one call is traced") + tag);
    if (!g_obs.trace.empty()) {
      check(g_obs.trace[0].kind == Event::Kind::kDestroy,
            std::string("the FIRST call is the destroy, not the free") + tag);
      check_word(static_cast<std::uint32_t>(g_obs.trace[0].arg_offset),
                 static_cast<std::uint32_t>(kObjectOffset),
                 std::string("the destroy receives the receiver itself, never +0x10, +0x14 "
                             "or a pointee") +
                     tag);
    }
    if (g_obs.free_calls == 1) {
      check(g_obs.trace.size() == 2, std::string("exactly two calls on the deleting arm") + tag);
      if (g_obs.trace.size() == 2) {
        check(g_obs.trace[1].kind == Event::Kind::kFree,
              std::string("the SECOND call is the free") + tag);
        check_word(static_cast<std::uint32_t>(g_obs.trace[1].arg_offset),
                   static_cast<std::uint32_t>(kObjectOffset),
                   std::string("the free receives the receiver itself, never the receiver's "
                               "first word and never a subobject") +
                       tag);
        check_word(g_obs.trace[1].vptr_at_call[0], g_destroy_vptr_primary,
                   std::string("this body's vptrs are not re-applied after the destroy") + tag);
      }
    } else {
      check(g_obs.trace.size() == 1, std::string("exactly one call on the non-deleting arm") + tag);
    }
  }

  // A receiver that is a subobject of a larger allocation: the free must get the
  // receiver AS PASSED, never an adjusted base. This is the check that would catch
  // a model which copied one of the 0x10/0x14 subobject adjustments that live in
  // the thunks at 0x00ec4230 and 0x00ec4240.
  reset_observers();
  {
    alignas(16) std::array<std::uint8_t, 0x80> region{};
    region.fill(0x77);
    auto* sub = reinterpret_cast<SporepediaOnlineAsset*>(region.data() + 0x10);
    g_buffer_base = reinterpret_cast<std::size_t>(region.data());
    g_object_offset = 0x10;
    (void)re_00ec4280(sub, 0x01);
    check(g_obs.trace.size() == 2, "subobject receiver: two calls");
    if (g_obs.trace.size() == 2) {
      check_word(static_cast<std::uint32_t>(g_obs.trace[0].arg_offset), 0x10,
                 "the destroy is given the receiver as passed, never adjusted by -0x10");
      check_word(static_cast<std::uint32_t>(g_obs.trace[1].arg_offset), 0x10,
                 "the free is given the receiver as passed, never adjusted by -0x14");
    }
  }
}

// ===========================================================================
// T7. WRITE ORDERING, falsified directly. The flag byte is read from the
//     caller's stack slot AFTER the destroy call. The hook is the only place the
//     model exposes that, so the test uses it to prove the ordering is real, then
//     uses its override to prove the arm follows the read and not the entry
//     value. Finally it makes the free scribble, to catch a reconstruction that
//     returned the object's current first word instead of the receiver.
// ===========================================================================
void test_flag_is_read_after_the_callee() {
  std::printf("T7 the flag read happens after the destroy call, on the slot\n");
  decode_destroy_vptrs();
  const std::array<std::uint8_t, kImageBytes> initial = make_initial_fill(0x88);
  sw1::sw1_delete_flag_read_hook = &delete_flag_hook;

  // 7a. Ordering: the destroy has already run when the flag is read.
  reset_observers();
  g_obs.hook_active = false;
  (void)run_model(0x00, initial);
  check(g_obs.hook_calls == 1, "the read point is reached even when the flag is clear");
  check(g_obs.hook_seen_events == 1, "the destroy call is already on the trace");
  check_word(g_obs.hook_vptrs[0], g_destroy_vptr_primary,
             "the object already carries the callee's vptr when the flag is read");

  // 7b. The hook's value, not the incoming parameter, decides the arm. This is
  //     the sharpest available test of "read at 0x00ec429C" versus "tested the
  //     parameter on entry": a clear parameter with an overriding hook must take
  //     the deleting arm.
  reset_observers();
  g_obs.hook_active = true;
  g_obs.hook_override = 0x01;
  (void)run_model(0x00, initial);
  check(g_obs.free_calls == 1,
        "an override of 0x01 with an incoming 0x00 takes the free: the arm follows the "
        "read point, not the entry value");

  reset_observers();
  g_obs.hook_active = true;
  g_obs.hook_override = 0x00;
  (void)run_model(0x01, initial);
  check(g_obs.free_calls == 0, "an override of 0x00 with an incoming 0x01 does not take the free");

  reset_observers();
  g_obs.hook_active = true;
  g_obs.hook_override = 0x02;
  (void)run_model(0x03, initial);
  check(g_obs.free_calls == 0, "an override of 0x02 does not take the free: mask 0x01");

  // 7c. The destroy is unconditional.
  reset_observers();
  g_obs.hook_active = false;
  (void)run_model(0xFF, initial);
  check(g_obs.destroy_calls == 1, "the destroy is unconditional even with the flag set");

  // 7d. The return value is the receiver on BOTH arms, and survives a free that
  //     overwrites the object's first word.
  for (std::uint8_t flag : {std::uint8_t{0x00}, std::uint8_t{0x01}}) {
    reset_observers();
    g_obs.free_scribbles = true;
    const ModelRun r = run_model(flag, initial);
    check_word(static_cast<std::uint32_t>(r.return_offset),
               static_cast<std::uint32_t>(kObjectOffset),
               std::string("the return value is the receiver on both arms, even when the "
                           "free scribbles over +0x00"));
  }
  reset_observers();
  sw1::sw1_delete_flag_read_hook = nullptr;
}

}  // namespace

int main() {
  std::printf("PKG-SWARM-W1-00EC4280 model test -- VA 0x00ec4280, re_00ec4280\n");
  std::printf("not asserted: class identity (no MSVC RTTI), bits 1..7 of the flag byte,\n");
  std::printf("             the 3 high bytes of the argument slot, the interior of\n");
  std::printf("             0x00642190, and anything at runtime.\n\n");
  test_transcription_matches_bytes();
  test_oracle_rejects_mutations();
  test_model_agrees_with_oracle();
  test_only_bit_zero_selects_the_free();
  test_vptr_writes_are_exact_and_in_place();
  test_callee_arguments_and_ordering();
  test_flag_is_read_after_the_callee();
  std::printf("\n%s (%d failure%s)\n", g_failures == 0 ? "PASS" : "FAIL", g_failures,
              g_failures == 1 ? "" : "s");
  return g_failures == 0 ? 0 : 1;
}
