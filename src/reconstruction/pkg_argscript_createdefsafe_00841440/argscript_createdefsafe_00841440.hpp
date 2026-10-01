#pragma once

// Clean-room reconstruction of SporeApp.exe 0x00841440
// (Ghidra/SDK import name: ArgScript::FormatParser::CreateDefinitionSafe).
//
// Evidence basis -- every claim below is one of these reads and nothing else.
// All are read-only Ghidra MCP reads of SporeApp.exe 3.1.0.22
// (x86:LE:32:default, cspec windows, image base 0x00400000,
//  sha256 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e):
//
//   * disassemble_function 0x00841440 -> 11 instructions, body
//     0x00841440..0x00841464, callees [FUN_0083c780], classification "wrapper".
//   * read_memory 0x00841440, 40 bytes -> the 36 body bytes and the 0xcc
//     padding after them:
//       8b542408 85d2 740f 8d42fc 894130 89542408 e929b3ffff
//       33c0 894130 89542408 e91bb3ffff                     (36 bytes)
//   * disassemble_function 0x0083c780 -> 5 instructions:
//       0x0083c780  8b 44 24 04        MOV EAX,dword ptr [ESP+0x4]
//       0x0083c784  8b 54 24 08        MOV EDX,dword ptr [ESP+0x8]
//       0x0083c788  89 41 04           MOV dword ptr [ECX+0x4],EAX
//       0x0083c78b  89 51 0c           MOV dword ptr [ECX+0xc],EDX
//       0x0083c78e  c2 08 00           RET 0x8
//   * read_memory 0x00841410, 48 bytes -> the adjacent thunk, not a Ghidra
//     function, 11 instructions of the same shape storing at [ECX+0x0c]:
//       8b542408 85d2 740f 8d42fc 89410c 89542408 e9c9b3ffff
//       33c0 89410c 89542408 e9bbb3ffff                     (36 bytes)
//     Both of its jumps decode to 0x0083c7f0, and disassemble_function
//     0x0083c7f0 returns the 3-instruction one-word sibling
//     (MOV EAX,[ESP+0x4] ; MOV [ECX+0x4],EAX ; RET 0x8). The bias idiom is
//     therefore a family-wide shape, not an artefact of this one body.
//   * disassemble_function 0x00844fb0 -> 231 instructions, the unsafe sibling
//     CreateDefinition, which is what fixes which stack slot carries the name
//     and which carries the line (see the parameter note in the .cpp).
//   * read_memory 0x0141c0e0, 64 bytes -> the bytes around the single incoming
//     DATA reference at 0x0141c100. The word at 0x0141c0f4 is 62 6c 65 00, the
//     NUL of the string "Sets a vector4 variable", so the briefing's
//     "vtable:0x0141c0f4" is a false positive and no vtable is claimed.
//
// No constant, offset, slot index, member name, vtable slot or class is
// inferred from anything but those reads. In particular:
//
//  * No FormatParser layout is adopted. The machine receiver record for this
//    target is `bounds_only` and enumerates the single displacement 0x30; it
//    states how far the body was seen reaching, never which member is which.
//    The SDK's own FormatParser structure places +0x30 inside a 0x20-byte
//    mParsers at +0x2c, which cannot be reconciled with one pointer store on
//    every call, so the SDK layout is treated as unconfirmed and the receiver
//    below is addressed by displacement alone.
//  * The word at +0x30 is given no member name. Naming it would be a layout
//    claim, and no read made here supports one.
//  * 0x0083c780 is not promoted to a function record. It is entered by tail
//    jump from this body and by direct call from many others, so it is a shared
//    two-field setter rather than a method of this class; its own name and
//    signature are unresolved.
//
// The only ABI fact this package asserts from the machine is the one the bytes
// above show directly: ECX is the receiver, the two ordinary stack words are
// read at [ESP+0x4] and [ESP+0x8], and the epilogue is the callee's RET 0x8.

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-argscript-createdefsafe-00841440 requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "target words are 32-bit");
static_assert(sizeof(std::uint8_t) == 1, "byte addressing is byte-wide");

#if defined(_MSC_VER)
#define PKG_ARGSCRIPT_CDS_THIS_CALL __thiscall
#else
#define PKG_ARGSCRIPT_CDS_THIS_CALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440 {

using OpaqueWord = std::uint32_t;

// The word a pointer argument contributes, read as its 32-bit address exactly
// as `MOV EDX,dword ptr [ESP + 0x8]` reads the slot. No object is dereferenced.
inline OpaqueWord word_of(void const* pointer) {
  return static_cast<OpaqueWord>(
      reinterpret_cast<std::uintptr_t>(pointer));
}

// The SDK declares the second argument ArgScript::Line*. Nothing collected for
// this target observes a Line layout: the body only ever reads the argument's
// own address. One opaque word stands in for the object so the type is
// pointer-shaped and nothing more; no interior offset is modelled or claimed.
struct OpaqueLine {
  OpaqueWord opaque_word = 0;
};

// Receiver.
//
// Three displacements are written on the path 0x00841440 takes, and no others
// appear in the body, in 0x0083c780, or in the adjacent thunk:
//
//   +0x04  0x0083c788  MOV dword ptr [ECX+0x4],EAX   (tail, from [ESP+0x4])
//   +0x0c  0x0083c78b  MOV dword ptr [ECX+0xc],EDX   (tail, from [ESP+0x8])
//   +0x30  0x0084144b  MOV dword ptr [ECX+0x30],EAX  (this body)
//        or 0x00841459  MOV dword ptr [ECX+0x30],EAX  (this body, null arm)
//
// The region below is sized to the largest of them plus its 4-byte word, 0x34,
// so it covers every offset this call writes and asserts nothing about the
// object's real extent, which is unresolved. The bytes are left as a byte array
// on purpose: a member name here would be a layout claim no read supports, and
// this package makes none.
inline constexpr std::size_t kReceiverCoveredBytes = 0x34;

struct OpaqueFormatParser {
  std::array<std::uint8_t, kReceiverCoveredBytes> bytes{};
};

static_assert(sizeof(OpaqueFormatParser) == kReceiverCoveredBytes,
              "receiver region covers every displacement this call writes");

inline std::uint8_t* receiver_bytes(OpaqueFormatParser* self) {
  return reinterpret_cast<std::uint8_t*>(self);
}

inline std::uint8_t const* receiver_bytes(OpaqueFormatParser const* self) {
  return reinterpret_cast<std::uint8_t const*>(self);
}

// Word access at a displacement. memcpy rather than a cast: the region is byte
// aligned by construction, so a `uint32_t*` store would be an unaligned access
// the original never performs.
inline OpaqueWord read_word_at(std::uint8_t const* base,
                               std::uint32_t displacement) {
  OpaqueWord value = 0;
  std::memcpy(&value, base + displacement, sizeof value);
  return value;
}

inline void write_word_at(std::uint8_t* base, std::uint32_t displacement,
                          OpaqueWord value) {
  std::memcpy(base + displacement, &value, sizeof value);
}

// The tail target 0x0083c780, observed exactly as quoted above: receiver words
// +0x4 and +0xc are overwritten from the two stack words, ECX is the receiver,
// the callee pops both argument words, and EAX still holds the first argument
// at the RET.
//
// Modelled here as an unresolved dependency port rather than a record: it is
// shared with many other call sites, so its own name and signature are not
// established by this target. The default binding reproduces its two stores
// and its EAX state so the observed tail site always has a callee.
using SharedTail0083c780 =
    bool (*)(OpaqueFormatParser* self, char* pName, OpaqueLine* argumentsLine);

extern SharedTail0083c780 g_tail_0083c780;

bool model_tail_0083c780(OpaqueFormatParser* self, char* pName,
                         OpaqueLine* argumentsLine);

// 0x00841440.
//
// ABI observed, not assumed: ECX carries the receiver, the two ordinary stack
// arguments are at [ESP+0x4] and [ESP+0x8], and this body contains no RET of
// its own and no stack adjustment -- the epilogue is the RET 0x8 inside
// 0x0083c780, so the callee pops 8 bytes. 11 instructions, 0x00841440..
// 0x00841463, two basic blocks, one forward branch to 0x00841457 and two
// unconditional tail jumps to 0x0083c780. The only registers written are EAX
// and EDX and the only register read is ECX, so nothing callee-saved is touched.
//
// The second parameter name follows the SDK prototype and the unsafe sibling,
// which strlen-scans [EBP+0x8] and formats it as a name while passing [EBP+0xc]
// onward as a line object. The exported decompilation labels the NULL-tested
// slot `pName`, which follows from that export placing the receiver at
// [ESP+0x4]; the tail's RET 0x8 refutes that placement. This package follows
// the persisted record and states the dispute; the model test asserts against
// the second stack word directly, so the naming question cannot change any
// modelled effect.
//
// EAX is never written by this body. The value a caller observes is whatever
// the shared tail leaves there, which its first instruction loaded from
// [ESP+0x4]. The declared return type bool is from the SDK and is consistent
// with that, so no success flag is invented here.
bool PKG_ARGSCRIPT_CDS_THIS_CALL
argscript_formatparser_create_definition_safe_00841440(
    OpaqueFormatParser* self, char* pName, OpaqueLine* argumentsLine);

}  // namespace openspore::reconstruction::pkg_argscript_createdefsafe_00841440

#undef PKG_ARGSCRIPT_CDS_THIS_CALL
