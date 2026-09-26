// 0x00b25c30 - first-match linear scan over a registry element array.
//
// Body span 0x00b25c30..0x00b25c92, 99 bytes, 39 instructions, all read from
// the live disassembly. ABI: __thiscall. The receiver arrives in ECX and is
// forwarded unchanged to the single callee - the body never writes ECX, which
// is why 0x00b25c4c can CALL 0x00b21340 with no preceding MOV ECX. Frame is
// PUSH EBX/ESI/EDI with the mirror POP sequence and a bare RET, so there are no
// stack arguments and the caller owns cleanup.
//
// Order of operations, as observed:
//   1. push the five callee arguments, last-push-first:
//        arg1 = 0x018c43e8   (.bss dword, reads 0 in the file image)
//        arg2 = 0x00b1e500
//        arg3 = 0x00acdff0
//        arg4 = 0x00d3d420
//        arg5 = 0x00cd7d10
//   2. CALL 0x00b21340 with ECX still holding the receiver
//   3. ESI  = result
//      EDI  = [result + 0x08] - [result + 0x04]     ; byte span
//      ESI += 0x04                                    ; ESI now points at the
//                                                    ; first element slot
//      EDI = SAR(EDI, 2)                             ; signed element count
//   4. if (count <= 0) return 0                      ; TEST EDI,EDI / JBE
//   5. for (i = 0; i < count; ++i) {
//          EAX = ESI[i]                              ; the element pointer
//          EDX = [EAX + 0x120]                       ; its embedded vtable
//          ECX = EAX + 0x120                         ; the interface receiver
//          EAX = [EDX + 0x58]                        ; slot +0x58
//          if (EAX()) return ESI[i]                  ; TEST AL,AL / JNZ
//      }
//      return 0
//
// The JBE at 0x00b25c63 is a SIGNED comparison against the SARed count, so a
// negative span also exits early; the loop back-edge uses unsigned JC against a
// count already known to be positive, so the two agree.
//
// Classification BOUNDED_SEMANTIC: the body is complete and every offset and
// branch is observed, but the single callee 0x00b21340 stays an opaque port and
// the element type behind the +0x120 interface is not established.

#include "sim_findfirst_00b25c30.hpp"

#include "b09_opaque_ports.hpp"

extern "C" B09_THISCALL OpaqueRegistryElement* SimFindFirst_00b25c30_reconstruct(
    OpaqueRegistryOwnerObserved* self) {
    // 0x00b25c33..0x00b25c4c: the five immediates, in push order.
    OpaqueRegistryLookup5Args args;
    args.arg1_key_bss_dword = reinterpret_cast<void*>(0x018c43e8u);
    args.arg2_code_00b1e500 = reinterpret_cast<void*>(0x00b1e500u);
    args.arg3_code_00acdff0 = reinterpret_cast<void*>(0x00acdff0u);
    args.arg4_code_00d3d420 = reinterpret_cast<void*>(0x00d3d420u);
    args.arg5_code_00cd7d10 = reinterpret_cast<void*>(0x00cd7d10u);

    // 0x00b25c4c CALL 0x00b21340 ; 0x00b25c51 MOV ESI,EAX
    // ECX is forwarded untouched, exactly as the original does.
    // The original dereferences the result immediately and never null-checks
    // it; this reconstruction does not add a check either, to keep the failure
    // behaviour identical.
    OpaqueRegistryContainerObserved* container =
        opaque_RegistryLookup5Args_00b21340(self, args);

    // 0x00b25c53..0x00b25c5c
    const std::int32_t span = static_cast<std::int32_t>(
        reinterpret_cast<std::uintptr_t>(container->element_array_end) -
        reinterpret_cast<std::uintptr_t>(container->element_array_begin));
    const std::int32_t count = span >> 2;
    auto* const elements =
        reinterpret_cast<OpaqueRegistryElement**>(container->element_array_begin);

    // 0x00b25c61 TEST EDI,EDI ; 0x00b25c63 JBE 0x00b25c84 - signed, so a
    // negative count exits here too, and 0x00b25c86 XOR EAX,EAX returns null.
    if (count <= 0) {
        return nullptr;
    }

    // 0x00b25c65..0x00b25c82
    for (std::int32_t i = 0; i < count; ++i) {
        OpaqueRegistryElement* element = elements[i];
        // 0x00b25c6a MOV EDX,[EAX + 0x120] ; 0x00b25c70 LEA ECX,[EAX + 0x120]
        // 0x00b25c76 MOV EAX,[EDX + 0x58] ; 0x00b25c79 CALL EAX
        using Slot58 = bool (*)(OpaqueRegistryElementIfc120*);
        const OpaqueSlot58TableObserved* table = element->iface_120.vtable;
        Slot58 slot_58 = reinterpret_cast<Slot58>(table->slots[0x58 / sizeof(void*)]);
        if (slot_58(&element->iface_120)) {
            // 0x00b25c7d JNZ 0x00b25c8a ; 0x00b25c8a..0x00b25c8c re-read
            // elements[i] into EAX after restoring the saved registers.
            return element;
        }
    }

    // 0x00b25c84..0x00b25c89
    return nullptr;
}
