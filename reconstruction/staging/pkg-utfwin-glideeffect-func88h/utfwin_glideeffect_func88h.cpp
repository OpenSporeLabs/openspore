#include "utfwin_glideeffect_func88h.hpp"

namespace openspore::reconstruction::pkg_utfwin_glideeffect_func88h {
namespace unresolved_contracts {

// 0x0096FFD0 .. 0x00970008. Not this target; declared so the model test can
// supply an oracle. Live listing:
//
//   PUSH ESI / MOV ESI,ECX
//   MOV [ESI],0x14425D8 / MOV [ESI+4],0x14425C0 / MOV [ESI+0xC],0x1442584
//   MOV [ESI+0x60],0x13EB938
//   CALL 0x00980420
//   TEST byte [ESP+0x8],0x1 / JZ skip
//   PUSH ESI / CALL 0x00951330 / ADD ESP,4
// skip: MOV EAX,ESI / POP ESI / RET 0x4
extern "C" Opaque PKG_G8_THISCALL
pkg_g8_re_0096ffd0(GlideEffect* object, std::uint32_t deleting_flag);

// 0x0096FF20 .. 0x0096FF40. The vector-deleting sibling reached through the
// thunk at 0x0096ff90. Tests the 0xEF2B293B vector-delete magic and tail
// transfers to 0x00963490; ends in RET 0x4.
extern "C" Opaque PKG_G8_THISCALL
pkg_g8_re_0096ff20(GlideEffect* object, std::uint32_t vector_delete_flag);

}

const Func88hAbi kFunc88hAbi = {
    /*receiver_register=*/-1,       // ECX, encoded as the x86 thiscall reg
    /*receiver_shift_bytes=*/0x0c,  // SUB ECX,0x0C
    /*ordinary_stack_words=*/1,     // [ESP+0x08] at the tail target
    /*stack_cleanup_bytes=*/4,      // RET 0x4 in the tail target
    /*return_type=*/"void",
    /*return_type_rationale=*/
    "The SDK and the Ghidra import both declare UTFWin::GlideEffect::func88h "
    "as "
    "returning void, and the two-instruction thunk never writes EAX. The tail "
    "target 0x0096FFD0 does materialise its receiver in EAX (MOV EAX,ESI at "
    "0x00970003) before RET 0x4, but the transfer is a tail jump, so that "
    "value belongs to the callee's frame and is modelled as unobservable "
    "here."};

const Func88hConstants kFunc88hConstants = {
    /*receiver_adjustment=*/0x0cu,
    /*tail_target=*/0x0096ffd0u,
    /*body_end_inclusive=*/0x0096ff77u,
    /*int3_pad_end=*/0x0096ff7fu,
    /*sole_data_xref=*/0x0144258cu,
    /*vtable_run_base=*/0x01442584u,
    /*dtor_primary_vtable=*/0x014425d8u,
    /*dtor_layout_vtable=*/0x014425c0u,
    /*dtor_bistate_vtable=*/0x01442584u,
    /*dtor_field_60_value=*/0x013eb938u,
    /*delete_flag_mask=*/0x01u,
};

// Transcribed from the .rdata dump at 0x01442584.
const GlideEffectVTableRun kGlideEffectVTableRun = {
    /*slot_00=*/0x00e246c0u,
    /*slot_04=*/0x00805630u,
    /*slot_08=*/0x0096ff70u,
    /*slot_0c=*/0x0096ff90u,
};

// SUB ECX,0x0C at 0x0096ff70: the most-derived object the tail target
// operates on sits this far below the receiver the thunk was handed.
GlideEffect* most_derived_below(const GlideEffectBiStateSubobject* self) {
  auto* bytes = reinterpret_cast<unsigned char*>(
      const_cast<GlideEffectBiStateSubobject*>(self));
  return reinterpret_cast<GlideEffect*>(bytes - kFunc88hReceiverAdjustment);
}

// 0x0096FF70 .. 0x0096FF77:
//
//   SUB ECX,0x0C
//   JMP 0x0096FFD0
//
// The only observable effects of this frame are the -0x0C rewrite of the
// hidden ECX receiver and the forwarding of the single stack word, which the
// tail target consumes with its own RET 0x4. The thunk writes no register
// other than ECX, reads no stack slot, and consults no flag, so nothing else
// can be attributed to this address.
extern "C" void PKG_G8_THISCALL func88h_0096ff70(
    GlideEffectBiStateSubobject* self, std::uint32_t deleting_flag) {
  static_cast<void>(unresolved_contracts::pkg_g8_re_0096ffd0(
      most_derived_below(self), deleting_flag));
}

// 0x0096FF90 .. 0x0096FF97: SUB ECX,0x0C / JMP 0x0096FF20. Present so the
// leaf block 0x0096ff20..0x00970008 is modelled as a whole.
extern "C" Opaque PKG_G8_THISCALL func88h_vector_0096ff90(
    GlideEffectBiStateSubobject* self, std::uint32_t vector_delete_flag) {
  return unresolved_contracts::pkg_g8_re_0096ff20(most_derived_below(self),
                                                  vector_delete_flag);
}

}
