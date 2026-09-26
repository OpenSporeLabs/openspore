// reconstruction/staging/wave13-w1-core-b11/00c308b0_field_equals_manager_field.cpp
//
// Clean-room reconstruction of SporeApp.exe 0x00c308b0 (image base
// 0x00400000). Body 0x00c308b0..0x00c308ce, 11 instructions, 30 bytes.
//
// Observed contract: return (receiver->field84 == dword at +0x1d8 of the object
// whose handle lives in the global 0x0167eae4) as a byte boolean, 1 on
// equality and 0 otherwise.
//
// Evidence, instruction by instruction:
//   0x00c308b0: 56                PUSH ESI
//   0x00c308b1: 8b f1             MOV ESI,ECX
//   0x00c308b3: e8 e8 c9 f0 ff    CALL 0x00b3d2a0        -> EAX = [0x0167eae4]
//   0x00c308b8: 8b c8             MOV ECX,EAX
//   0x00c308ba: e8 d1 53 c5 ff    CALL 0x00885c90        -> EAX = [EAX + 0x1d8]
//   0x00c308bf: 33 c9             XOR ECX,ECX
//   0x00c308c1: 3b 86 84 00 00 00 CMP EAX,dword ptr [ESI + 0x84]
//   0x00c308c7: 5e                POP ESI
//   0x00c308c8: 0f 94 c1          SETZ CL
//   0x00c308cb: 8a c1             MOV AL,CL
//   0x00c308cd: c3                RET
//
// Both callees were read: 0x00b3d2a0 is exactly
// "MOV EAX,dword ptr [0x0167eae4] ; RET" and 0x00885c90 is exactly
// "MOV EAX,dword ptr [ECX + 0x1d8] ; RET". Neither reads a register beyond its
// own documented operand and neither pops anything, so both are effectively
// register-agnostic; they are declared as plain function pointers here.
//
// Branch polarity: SETZ, so the answer is 1 exactly when the two dwords are
// equal. XOR ECX,ECX before SETZ CL means the upper three bytes of ECX are
// zeroed, and MOV AL,CL means only the low byte of the return register is
// written - the upper 24 bits of EAX stay as the callee of 0x00885c90 left
// them. 0x00be7bf0 at 0x00be85fb consumes the answer with TEST AL,AL.
//
// Analogue: 0x00c30860, 0x30 bytes earlier in the same code block, uses the very
// same receiver field [ECX + 0x84] as a pushed argument to 0x00c7bbc0 reached
// through 0x00b3d300()/0x00f67d90().
//
// Not claimed: the owning class of the receiver, and what either dword denotes.
// reconstruction/metadata/pkg11-sim-core/00ba9370.json records the 0x0167eae4
// slot as a star-manager root, and
// reconstruction/metadata/wave13-w1-core-b07/00c30c80.json records the same slot
// as a handle table; neither re-derivation was performed here beyond confirming
// the two-instruction getter, so those stay INFERRED.

#include "b11_opaque_types.hpp"

namespace openspore {
namespace b11 {
namespace t00c308b0 {

// Observed receiver offset compared against the manager's +0x1d8 word.
inline constexpr std::size_t kReceiverFieldOffset = 0x84;
// Observed offset inside the object reached through the global 0x0167eae4.
inline constexpr std::size_t kManagerFieldOffset = 0x1d8;

// True when the receiver's +0x84 word equals the manager's +0x1d8 word.
Bool field_84_equals_manager_1d8(Dword84Owner* self, GlobalGetterEae4Fn manager,
                                 Word1d8GetterFn managerField) {
    // 0x00c308b0 PUSH ESI / 0x00c308b1 MOV ESI,ECX - the receiver is only saved,
    // never written, so the frame exists solely to free ECX for the second call.
    Dword* const savedSelf = &self->field84;

    // 0x00c308b3 CALL 0x00b3d2a0 - reads the global handle slot only.
    const Dword managerHandle = manager();
    // 0x00c308ba CALL 0x00885c90 - reads the manager's +0x1d8 word.
    const Dword managerValue = managerField(reinterpret_cast<Ptr>(managerHandle));

    // 0x00c308bf XOR ECX,ECX / 0x00c308c8 SETZ CL / 0x00c308cb MOV AL,CL.
    // Equality is 1, inequality is 0, and only AL is defined on return.
    const bool equal = (managerValue == *savedSelf);
    return equal ? static_cast<Bool>(1) : static_cast<Bool>(0);
    // 0x00c308cd RET - bare, so the callee pops no stack words.
}

}  // namespace t00c308b0
}  // namespace b11
}  // namespace openspore
