#include "adc40_flag.hpp"

#if defined(_MSC_VER)
#define PKG_EDITOR_ADC40_THISCALL __thiscall
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_EDITOR_ADC40_THISCALL __attribute__((thiscall))
#else
#error "PKG-EDITOR-ADC40-FLAG requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_editor_adc40_flag {

// 0x004adc40, 17 bytes, 9 instructions, one basic block:
//
//   004adc40  55             push   ebp
//   004adc41  89 e5          mov    ebp, esp
//   004adc43  51             push   ecx
//   004adc44  89 4d fc       mov    dword ptr [ebp-0x4], ecx
//   004adc47  8b 45 fc       mov    eax, dword ptr [ebp-0x4]
//   004adc4a  8a 40 4f       mov    al, byte ptr [eax+0x4f]
//   004adc4d  89 e5          mov    esp, ebp
//   004adc4f  5d             pop    ebp
//   004adc50  c3             ret
//
// The reconstruction is the one statement below. It reads one byte at
// receiver+0x4f and returns it; it writes nothing, calls nothing, branches
// nowhere, allocates nothing and has no null guard, so a null or near-null
// receiver faults on the unchecked load -- the observed behaviour, and no
// check is added.
//
// Two properties of the original encoding are recorded rather than reproduced,
// because a C++ return type does not model either of them:
//
//  * The load writes only AL. EAX is reloaded from the spilled ECX
//    immediately beforehand, so the upper 24 bits of EAX come out equal to
//    receiver address bits 8..31 rather than zero. A C++ function returning
//    std::uint8_t is free to zero-extend instead, which is a strictly
//    stronger guarantee and is what this translation unit emits. Nothing
//    depends on the difference: the three sampled call sites (0x00435aa5,
//    0x0043ffd2, 0x00588ba6) all consume the result through MOVZX or a TEST
//    on AL alone.
//  * The frame itself. PUSH EBP / MOV EBP,ESP and the PUSH ECX / spill to
//    [ebp-0x4] / reload pair are redundant for a body this small -- no
//    instruction reads the spilled slot except the reload -- and a compiler
//    emits no frame for the statement below. The original encoding is
//    transcribed above and in the disassembly record rather than imitated,
//    because imitating it would mean shipping a function that cannot be
//    called: a naked body ending in a bare RET is not call-compatible with
//    GCC's i386 thiscall model, which reserves a callee-popped argument area
//    the bare RET never consumes.
extern "C" Field PKG_EDITOR_ADC40_THISCALL
FUN_004adc40(OpaqueEditorFlag* self) {
  return self->byte_04f;
}

}  // namespace openspore::reconstruction::pkg_editor_adc40_flag

#undef PKG_EDITOR_ADC40_THISCALL
