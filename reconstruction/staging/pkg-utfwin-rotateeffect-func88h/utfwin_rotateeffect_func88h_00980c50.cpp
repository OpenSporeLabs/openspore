#include "utfwin_rotateeffect_func88h_00980c50.hpp"

namespace openspore::reconstruction::pkg_utfwin_rotateeffect_func88h {

namespace unresolved_contracts {

// 0x00980C80 .. 0x00980C9B is a different address and is NOT claimed as
// reconstructed here -- Ghidra has no function at or containing 0x00980c80, so
// its real entry point and owning class are unknown. The model test supplies
// this oracle so the constant pairing can be exercised. Observed bytes:
//
//   00980c80  8B 44 24 04          MOV  EAX,[ESP+4]
//   00980c84  85 C0                TEST EAX,EAX
//   00980c86  74 0D                JZ    0x00980c95
//   00980c88  83 7C 24 08 00       CMP  dword [ESP+8],0
//   00980c8d  74 06                JZ    0x00980c95
//   00980c8f  C7 00 D5 2A 2B CF    MOV  dword [EAX],0xCF2B2AD5
//   00980c95  B8 01 00 00 00       MOV  EAX,1
//   00980c99  C2 08 00             RET  0x8
extern "C" Opaque pkg_r8_re_00980c80(RotateEffectTokenWord* self,
                                     std::uint32_t word);

}

const Func88hAbi kFunc88hAbi = {
    /*receiver_register=*/-1,  // ECX, the x86 thiscall receiver
    /*ordinary_stack_words=*/3,
    /*stack_cleanup_bytes=*/0,  // bare RET: the caller pops
    /*return_type=*/"std::uint32_t",
    /*return_type_rationale=*/
    "The machine is unambiguous: 0x00980c50 is MOV EAX,0xCF2B2AD5 / RET, so "
    "the frame materialises a 32-bit value in EAX and the observed return is "
    "that word. The SDK and the Ghidra import instead spell the return type "
    "void, which is the usual placeholder for a virtual the SDK generator "
    "could not name. This span is modelled as returning std::uint32_t because "
    "that is what the instructions do; the SDK/void disagreement is reported "
    "rather than resolved. Confidence: high for the EAX immediate, low for "
    "the semantic type of the value, which is not documented anywhere in the "
    "SDK."};

const Func88hConstants kFunc88hConstants = {
    /*token=*/0xcf2b2ad5u,
    /*entry=*/0x00980c50u,
    /*body_end_inclusive=*/0x00980c55u,
    /*int3_pad_end=*/0x00980c5fu,
    /*sole_data_xref=*/0x01444364u,
    /*vtable_run_base=*/0x01444364u,
    /*pairing_store_block=*/0x00980c80u,
    /*pairing_store_end=*/0x00980c9cu,
    /*adjustor_thunk_04=*/0x00980c60u,
    /*adjustor_thunk_0c=*/0x00980c70u,
    /*adjustor_jump_target=*/0x00980cb0u,
    /*vector_delete_entry=*/0x0096ff20u,
    /*vector_delete_magic=*/0xef2b293bu,
    /*objecttype_iperspective=*/0xef2b293bu,
};

// Transcribed verbatim from the .rdata dump at 0x01444364.
const RotateEffectVTableRun kRotateEffectVTableRun = {
    /*slot_00=*/0x00980c50u,
    /*slot_04=*/0x00980320u,
    /*slot_08=*/0x009800e0u,
    /*slot_0c=*/0x00980cb0u,
    /*slot_10=*/0x0096ff20u,
    /*slot_14=*/0x00e31100u,
    /*slot_18=*/0x009634c0u,
    /*slot_1c=*/0x00963780u,
    /*slot_20=*/0x006f2f20u,
    /*slot_24=*/0x006f2f20u,
    /*slot_28=*/0x006f2f20u,
    /*slot_2c=*/0x006f2f20u,
};

// 0x00980c50 .. 0x00980c55:
//
//   B8 D5 2A 2B CF    MOV EAX,0xCF2B2AD5
//   C3                RET
//
// The only observable effects of this frame are the immediate written to EAX
// and the return. It never reads ECX, never reads or writes memory, never
// consults a flag, and never branches, so no argument value -- and no receiver
// -- can influence the result. The bare RET (rather than RET 4 or RET 8)
// proves the caller performs the stack cleanup, so a caller that pushes the
// three words the SDK method header declares must pop them itself; the
// call_three_argument helper in the model test does exactly that.
//
// The body is reproduced as inline assembly rather than as `return 0xcf2b2ad5;`
// so that the naked-frame property and the caller-cleanup property are the
// ones actually under test, and so the emitted code is the two instructions
// the image holds rather than whatever the optimiser would choose.
extern "C" std::uint32_t PKG_R8_NAKED PKG_R8_THISCALL func88h_00980c50(Opaque,
                                                                       Opaque,
                                                                       Opaque,
                                                                       Opaque) {
  __asm__(
      "movl $0xcf2b2ad5, %eax\n\t"
      "ret\n\t");
}

}
