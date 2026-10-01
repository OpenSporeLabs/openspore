#include "sim_record_lookup_chain_00b8de30.hpp"

#include <cstring>

// 0x00b8de30 -- read one receiver dword at +0x184, then four calls in a fixed
// order. Straight-line, no result, no stores.
//
//     0x00b8de30  8b 81 84 01 00 00   MOV EAX, dword ptr [ECX + 0x184]
//     0x00b8de36  50                  PUSH EAX
//     0x00b8de37  e8 64 f4 fa ff      CALL 0x00b3d2a0
//     0x00b8de3c  8b c8               MOV ECX, EAX
//     0x00b8de3e  e8 fd 85 01 00      CALL 0x00ba6440
//     0x00b8de43  50                  PUSH EAX
//     0x00b8de44  e8 57 f4 fa ff      CALL 0x00b3d2a0
//     0x00b8de49  8b c8               MOV ECX, EAX
//     0x00b8de4b  e8 30 8f 01 00      CALL 0x00ba6d80
//     0x00b8de50  c3                  RET
//
// The two PUSHes are consumed by the two thiscall calls that FOLLOW them, not by
// the argless accessor they precede; see the header for why the callee's own six
// bytes settle that. The receiver each thiscall callee gets is the ACCESSOR's
// return value -- the two `MOV ECX,EAX` at 0x00b8de3c and 0x00b8de49 -- and the
// argument 0x00ba6d80 gets is 0x00ba6440's return value.

namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain {

SimRecordImage g_sim_record_image{};

CallTraceEntry g_call_trace[kMaxCallDepth]{};
std::size_t g_call_depth = 0;

Word g_accessor_result = 0;
Word g_lookup_result = 0;
Word g_resolve_result = 0;

std::uint8_t* image_bytes() {
  return reinterpret_cast<std::uint8_t*>(&g_sim_record_image.words[0]);
}

Word word_at(const std::uint8_t* base, std::size_t displacement) {
  Word value = 0;
  std::memcpy(&value, base + displacement, sizeof(value));
  return value;
}

namespace {

void record(Word site, Word receiver, Word argument, Word stack_words) {
  if (g_call_depth >= kMaxCallDepth) {
    return;
  }
  g_call_trace[g_call_depth].site = site;
  g_call_trace[g_call_depth].receiver = receiver;
  g_call_trace[g_call_depth].argument = argument;
  g_call_trace[g_call_depth].stack_words = stack_words;
  ++g_call_depth;
}

Word pointer_word(const void* pointer) {
  return static_cast<Word>(reinterpret_cast<std::uintptr_t>(pointer));
}

}  // namespace

// 0x00b3d2a0 -- `A1 E4 EA 67 01 / C3`: reads a global dword and returns, taking
// no stack word and popping nothing. Modelled as a nullary entry so that a
// reconstruction which pushed an argument FOR it has nothing to push it into.
Word PKG_00B8DE30_CALL FUN_00b3d2a0() {
  record(kSiteAccessor, 0u, 0u, 0u);
  return g_accessor_result;
}

// 0x00ba6440 -- `MOV EAX,[ESP+4]` ... `RET 4`: one stack word, removed by the
// callee. ECX arrives but this body does not read it; that is a fact about
// 0x00ba6440, not a claim reconstructed here.
Word PKG_00B8DE30_CALL FUN_00ba6440(SimRecord* receiver, Word argument) {
  record(kSiteLookup, pointer_word(receiver), argument, 1u);
  return g_lookup_result;
}

// 0x00ba6d80 -- `MOV EDX,[ESP+4]` ... `RET 4`, and it does read two fields of
// ECX. Again: its semantics are not reconstructed here.
Word PKG_00B8DE30_CALL FUN_00ba6d80(SimRecord* receiver, Word argument) {
  record(kSiteResolve, pointer_word(receiver), argument, 1u);
  return g_resolve_result;
}

void PKG_00B8DE30_CALL sim_record_lookup_chain_00b8de30(SimRecord* self) {
  // 0x00b8de30  MOV EAX, dword ptr [ECX + 0x184]
  const Word field = word_at(reinterpret_cast<const std::uint8_t*>(self),
                             kFieldDisplacement);

  // 0x00b8de36  PUSH EAX        -- for the call at 0x00b8de3e, not this one
  // 0x00b8de37  CALL 0x00b3d2a0
  // 0x00b8de3c  MOV ECX, EAX
  // 0x00b8de3e  CALL 0x00ba6440
  const Word root = FUN_00b3d2a0();
  const Word lookup =
      FUN_00ba6440(reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root)),
                   field);

  // 0x00b8de43  PUSH EAX        -- for the call at 0x00b8de4b, not this one
  // 0x00b8de44  CALL 0x00b3d2a0
  // 0x00b8de49  MOV ECX, EAX
  // 0x00b8de4b  CALL 0x00ba6d80
  const Word root_again = FUN_00b3d2a0();
  (void)FUN_00ba6d80(
      reinterpret_cast<SimRecord*>(static_cast<std::uintptr_t>(root_again)),
      lookup);
}

}  // namespace openspore::reconstruction::pkg_00b8de30_sim_record_lookup_chain
