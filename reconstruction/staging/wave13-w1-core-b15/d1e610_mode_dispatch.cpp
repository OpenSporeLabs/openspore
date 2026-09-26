// 0x00d1e610 — 0x00d1e610..0x00d1e64d, 24 instructions, 66 bytes.
//
//   0x00d1e610 PUSH ESI
//   0x00d1e611 XOR ESI,ESI
//   0x00d1e613 CALL 0x00b5b800              selector
//   0x00d1e618 SUB EAX,0x1654c01   0x00d1e61d JZ 0x00d1e645
//   0x00d1e61f SUB EAX,0x1         0x00d1e622 JZ 0x00d1e62d
//   0x00d1e624 SUB EAX,0xe         0x00d1e627 JZ 0x00d1e645
//   0x00d1e629 MOV EAX,ESI / 0x00d1e62b POP ESI / 0x00d1e62c RET
//   0x00d1e62d CALL 0x00b3d300
//   0x00d1e632 MOV ECX,EAX
//   0x00d1e634 CALL 0x00bfc5f0             [handle + 0x70]
//   0x00d1e639 TEST EAX,EAX  0x00d1e63b JZ 0x00d1e629
//   0x00d1e63d MOV ECX,EAX
//   0x00d1e63f POP ESI
//   0x00d1e640 JMP 0x00c00650              [handle + 0x11c]
//   0x00d1e645 CALL 0x00b3d300
//   0x00d1e64a MOV ECX,EAX
//   0x00d1e64c POP ESI
//   0x00d1e64d JMP 0x00b1fdb0              [subsystem + 0x54]
//
// __cdecl with no arguments and no receiver: ECX is never read on entry, it is
// only loaded as the `this`/first argument of the tail-transferred callees.
// Zero stack arguments, and the two long paths end in a near JMP after POP ESI,
// so the callee itself never returns through this frame — the frame is a pure
// trampoline. The answer is a 32-bit value in EAX; the default path returns the
// zero that XOR ESI,ESI materialised.
//
// The switch is a subtract-and-test chain, not a jump table. The three selector
// values are 0x01654c01, 0x01654c02 and 0x01654c01 + 1 + 0x0e = 0x01654c10.
// A byte-pattern scan for 0x01654c01 finds 180 sites across the binary, all
// sharing the same high 24 bits, so these are tokens from one identifier family
// rather than arbitrary numbers. The family was NOT resolved to a table, so
// the three selectors are left as raw constants.
//
// The selector source 0x00b5b800 is itself two loads:
//   if (*[0x0167eaec] != 0) return *(*[0x0167eaec] + 0x20);
//   return 0xffffffff;
// so when the singleton at 0x0167eaec is absent the selector is the all-ones
// value, which matches none of the three cases and therefore returns 0.
//
// 0x00b3d300 and 0x00b3d320 are the first two entries of a 22-entry table at
// 0x00b3d300..0x00b3d4d5 in which every entry is exactly
// `MOV EAX,[0x0167XXXX] ; RET`. The SDK import named several of them, which is
// what establishes the family as `Simulator::cXxxManager::Get()` singletons:
//   0x00b3d330 Simulator::cSimulatorSystem::Get        -> [0x0167eaf0]
//   0x00b3d340 Simulator::cGameViewManager::Get        -> [0x0167eaf4]
//   0x00b3d350 Simulator::cGameInputManager::Get       -> [0x0167eaf8]
//   0x00b3d360 Simulator::cGameBehaviorManager::Get    -> [0x0167eafc]
//   0x00b3d400 Simulator::cGameNounManager::Get        -> [0x0167eb60]
//   0x00b3d420 Simulator::cGameModeManager::Get        -> [0x0167eb2c]
//   0x00b3d430 Simulator::cPlanetModel::Get            -> [0x0167eb30]
//   0x00b3d440 Simulator::cGamePersistenceManager::Get -> [0x0167eb34]
//   0x00b3d480 Simulator::cGameTimeManager::Get        -> [0x0167eb3c]
// but NOT 0x00b3d300 -> [0x0167eae0] and NOT 0x00b3d320 -> [0x0167eaec], which
// are the two this target needs. Their owning classes are therefore unnamed.
//
// The returned value is a polymorphic object pointer, not a scalar: caller
// 0x00d1e830 at 0x00d1e84b does `MOV EAX,dword ptr [EDI] ; MOV EDX,dword ptr
// [EAX + 0xb0] ; MOV ECX,EDI ; CALL EDX` on it, and 0x00d200a0 at 0x00d200d6
// dereferences its vtable. Neither call site's vtable was located, so the
// concrete type of the returned object is NOT named.

#include "b15_opaque_types.hpp"

namespace openspore::wave13_w1_core_b15 {

std::uint32_t dispatch_active_object_00d1e610() noexcept {
    const std::uint32_t selector = selector_port();
    const OpaqueSimSubsystem* const owner = subsystem_a_port();

    switch (selector) {
        case 0x01654c01u:
        case 0x01654c10u:
            // 0x00d1e645 -> JMP 0x00b1fdb0, which is `return [x + 0x54]`.
            return owner->object_54;

        case 0x01654c02u: {
            // 0x00d1e62d: the intermediate handle is null-checked before use.
            const std::uint32_t handle = owner->handle_70;
            if (handle == 0) {
                return 0;
            }
            // 0x00d1e640 -> JMP 0x00c00650, which is `return [x + 0x11c]`.
            const auto* second = reinterpret_cast<const OpaqueSimHolder*>(
                static_cast<std::uintptr_t>(handle));
            return second->value_11c;
        }

        default:
            // 0x00d1e629: MOV EAX,ESI with ESI zeroed at 0x00d1e611.
            return 0;
    }
}

}  // namespace openspore::wave13_w1_core_b15
