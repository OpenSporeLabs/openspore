#include "utfwin_hash_offset_009817c0.hpp"

namespace openspore::reconstruction::pkg_utfwin_hash_offset_009817c0 {

namespace {

// Reproduces the observed "LEA EAX,[ECX + imm]" exit shape: the returned value
// is the receiver moved forward by a proven member offset.
inline void* add_offset(OpaqueReceiver self, std::ptrdiff_t offset) {
  return static_cast<char*>(self) + offset;
}

}  // namespace

// 0x00951240, 16 instructions, 0x00951240..0x0095126f inclusive.
//
// Observed body, in order:
//   MOV EAX, ECX                  ; EAX = receiver
//   MOV ECX, dword ptr [ESP + 0x4] ; ECX = hash
//   CMP ECX, 0x6ec581fd
//   JZ  0x0095126e                ; -> RET 0x4 with EAX still the bare receiver
//   CMP ECX, 0xee3f516e
//   JZ  0x00951268                ; -> TEST EAX,EAX
//   CMP ECX, 0xeec58382
//   JNZ 0x0095126c                ; -> XOR EAX,EAX ; RET 0x4
//   TEST EAX, EAX                ; hash == 0xeec58382
//   JZ   0x0095126c
//   ADD EAX, 0x4
//   RET  0x4
//   TEST EAX, EAX                ; hash == 0xee3f516e
//   JNZ  0x00951262
//   XOR EAX, EAX
//   RET  0x4
//
// Proven by the body, and therefore relied on by this reconstruction:
//   - receiver in ECX, hash as the single callee-cleaned stack word;
//   - the +0x00 case returns the receiver VERBATIM and is the one path with no
//     null guard, so a null receiver yields a null result there rather than
//     being rejected;
//   - the two +0x04 cases share one ADD EAX,0x4 block reached from two
//     different hash tests, so 0xee3f516e and 0xeec58382 resolve to the same
//     member offset;
//   - every other hash yields a null EAX via XOR EAX,EAX;
//   - leaf: no CALL, no absolute address, single-entry single-exit.
extern "C" void* PKG_UTFWIN_HASH_OFFSET_THISCALL
sibling_hash_offset_00951240(OpaqueReceiver self, HashWord hash) {
  if (hash == kHash_6ec581fd) {
    // Observed asymmetry: this arm jumps straight to the RET with EAX still
    // holding the receiver. There is deliberately no null test here.
    return self;
  }
  if (hash == kHash_ee3f516e) {
    return self != nullptr ? add_offset(self, kOffset_04) : nullptr;
  }
  if (hash == kHash_eec58382) {
    return self != nullptr ? add_offset(self, kOffset_04) : nullptr;
  }
  return nullptr;
}

// 0x009817c0, 17 instructions, 52 bytes,
// body 0x009817c0..0x009817f3 inclusive.
//
// Observed body, in order:
//   MOV EAX, dword ptr [ESP + 0x4] ; EAX = hash
//   CMP EAX, 0xeec58382
//   JZ  0x009817e5
//   CMP EAX, 0xeef3af8c
//   JZ  0x009817db
//   MOV dword ptr [ESP + 0x4], EAX ; no-op, the slot already holds EAX
//   JMP  0x00951240                ; tail call, receiver still in ECX
//   TEST ECX, ECX                  ; reached for hash 0xeef3af8c
//   JZ   0x009817ef
//   LEA EAX, [ECX + 0xc]
//   RET  0x4
//   TEST ECX, ECX                  ; reached for hash 0xeec58382
//   JZ   0x009817ef
//   LEA EAX, [ECX + 0x4]
//   RET  0x4
//   XOR EAX, EAX                   ; reached for a null receiver
//   RET  0x4
//
// Proven by the body, and therefore relied on by this reconstruction:
//   - receiver in ECX, hash as the single callee-cleaned stack word;
//   - this target extends the table of 0x00951240 by exactly one key
//     (0xeef3af8c) and one offset (+0x0c), and delegates every other key to
//     the sibling by tail call;
//   - the two locally handled keys 0xeec58382 -> +0x04 and 0xeef3af8c -> +0x0c
//     are both null-guarded, so a null receiver yields a null result;
//   - the receiver is only tested and offset, never written, so the call has
//     no effect on the object;
//   - the MOV dword ptr [ESP + 0x4], EAX at 0x009817d2 is a store of EAX into
//     the slot EAX was just loaded from and exists only to keep the argument
//     live across the tail call; it is modelled by the plain tail call.
//
// Combined key -> offset table reachable through this entry point:
//   0x6ec581fd -> +0x00   (via the tail call; not null-guarded)
//   0xee3f516e -> +0x04   (via the tail call)
//   0xeec58382 -> +0x04   (handled locally, null-guarded)
//   0xeef3af8c -> +0x0c   (handled locally, null-guarded)
//   anything else -> null
extern "C" void* PKG_UTFWIN_HASH_OFFSET_THISCALL
set_image_009817c0(OpaqueReceiver self, HashWord hash) {
  if (hash == kHash_eec58382) {
    return self != nullptr ? add_offset(self, kOffset_04) : nullptr;
  }
  if (hash == kHash_eef3af8cu) {
    return self != nullptr ? add_offset(self, kOffset_0c) : nullptr;
  }
  return sibling_hash_offset_00951240(self, hash);
}

}  // namespace openspore::reconstruction::pkg_utfwin_hash_offset_009817c0
