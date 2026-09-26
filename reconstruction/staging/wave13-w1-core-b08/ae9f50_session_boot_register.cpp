// 0x00ae9f50 — SimCore_00ae9f50_session_boot_register
//
// 169 instructions, 535 bytes, 23 direct callees, 1 indirect call through a
// vtable slot +0x20, 2 calls through App::IAppSystem slot +0x14.
//
// ABI: ECX is the receiver, no stack arguments, frame is
// `SUB ESP,0x80 ; PUSH ESI ; PUSH EBX ; PUSH EBP ; PUSH EDI` and the epilogue
// is `POP ESI ; ADD ESP,0x80 ; RET`, a bare RET, so the caller owns cleanup.
// Every callee ret form was read live before the stack reconstruction below
// was accepted: 0x00BA9370/0x00B20750/0x00B32250/0x00E14C10/0x00BA6D80 end in
// RET 0x4, 0x00C03260 in a bare RET, 0x00F31500 in RET 0x8, 0x00AE0930 in
// RET 0x18, and 0x00435ED0/0x00C35240/0x0067DCC0/0x00421CF0 in a bare RET.
// That is what makes the two `PUSH`es at 0x00AE9F81 and 0x00AE9FD1 land as the
// stack arguments of the following RET 0x4 callees rather than leaking.
//
// Three things the pseudocode alone does not show:
//   1. The whole body is guarded on `this->f_20 != 0` (0x00AE9F68 JZ 0x00AEA15F).
//      With a null sub-object only the epilogue runs.
//   2. The first dword of each 0x34-byte stack record is a CODE pointer, not a
//      data vtable. 0x013EB844 holds 0x004230E0 and 0x013EB90C holds 0x0040FDC0;
//      both are Ghidra function entries. 0x00AE9F9C stores 0x013EB90C and
//      0x00AE9FAF overwrites it with 0x013EB844 before the record is used, so
//      the first store is dead.
//   3. f_64 and f_68 are compared as two pointers and the compare is repeated
//      after port_00ae0930_release; only if it still differs is the byte at
//      *f_64 cleared and f_68 refreshed from f_64.
//
// Nothing here is named beyond what the immediates prove. 0x3AC86B5 and
// 0x43F2590 are the two record ids; 0x4D02E35 and 0x1E5E7302 are the two
// published values. All four are read as immediates and none is resolved to a
// property, key or enum name.

#include "wave13_w1_core_b08.hpp"

namespace openspore {
namespace wave13_w1_core_b08 {

extern "C" void SimCore_00ae9f50_session_boot_register(OpaqueAe9f50Session* self);

extern "C" void SimCore_00ae9f50_session_boot_register(OpaqueAe9f50Session* self) {
    // 0x00AE9F59 CALL 0x00DD1CA0 ; MOV ECX,EAX ; CALL 0x00DD30D0
    void* first = port_00dd1ca0_get();
    port_00dd30d0_apply(first);

    // 0x00AE9F65 MOV EAX,[ESI + 0x20] ; TEST EAX,EAX ; JZ 0x00AEA15F
    OpaqueAe9f50SubObject* sub = self->f_20;
    if (sub == nullptr) {
        return;
    }

    // 0x00AE9F70 CMP dword [EAX + 0xC],0 ; SETZ BL  -- BL = (sub->f_0C == 0)
    const bool sub_c_is_null = sub->f_0C == 0u;

    // 0x00AE9F7E MOV EAX,[EAX + 0x18] ; PUSH EAX ; CALL 0x00B3D2A0 (bare RET,
    // the word survives) ; MOV ECX,EAX ; CALL 0x00BA9370 (RET 0x4)
    // 0x00AE9F92 XOR EBP,EBP on the other branch
    void* profile = nullptr;
    if (!sub_c_is_null) {
        profile = port_00ba9370_map_lookup(port_00b3d2a0_manager_get(), sub->f_18);
    }

    // 0x00AE9F94 MOV [ESP+0x40],0x3AC86B5
    // 0x00AE9F9C MOV [ESP+0x10],0x13EB90C   (dead: overwritten at 0x00AE9FAF)
    // 0x00AE9FA6 LEA ECX,[ESP+0x14] ; XOR EAX,EAX ; XCHG [ECX],EAX
    // 0x00AE9FAF MOV [ESP+0x10],0x13EB844
    // 0x00AE9FB7 MOV [ESP+0x48],0
    // 0x00AE9FBF MOV EDX,[EDI + 0xC] ; 0x00AE9FC2 MOV [ESP+0x18],EDX
    Ae9f50BootRecord record;
    record.code_00 = nullptr;
    record.dword_04 = 0u;
    record.sub_f_0C = sub->f_0C;
    record.dword_0C = 0u;  // the original never writes this word
    record.profile = nullptr;
    record.sub_f_20 = nullptr;
    record.sub_f_24 = nullptr;
    record.dword_28 = 0u;  // nor this one
    record.dword_2C = 0u;  // nor this one
    record.dword_30 = 0x3AC86B5u;
    record.dword_34 = 0u;  // nor this one
    record.dword_38 = 0u;

    // 0x00AE9FC6 TEST BL,BL ; JZ 0x00AE9FCE ; 0x00AE9FCA MOV EAX,EBP
    if (!sub_c_is_null) {
        record.profile = profile;
    } else {
        // 0x00AE9FCE MOV EAX,[EDI + 0x18] ; PUSH EAX ; CALL 0x00B3D300
        // (bare RET: the word survives) ; MOV ECX,EAX ; CALL 0x00B20750 (RET 0x4).
        // The 0x00B20750 result lands in EAX and is then never read: the next
        // instruction reloads EAX from [EDI + 0x28]. Reproduced, not tidied.
        port_00b20750_map_lookup(port_00b3d300_lookup(), sub->f_18);
        // 0x00AE9FDE MOV EAX,[EDI + 0x28] ; TEST EAX,EAX ; JNZ 0x00AE9FED
        // 0x00AE9FE5 MOV ECX,[EDI + 0x20] ; CALL 0x00BD9BF0
        record.profile =
            sub->f_28 != nullptr ? sub->f_28 : port_00bd9bf0_default();
    }

    // MOV EAX,[ESI + 0x20] ; MOV ECX,EAX ; TEST BL,BL ; JNZ 0x00AE9FFD ;
    // MOV ECX,[EAX + 0x20] ; MOV [ESP + 0x28],ECX
    record.sub_f_20 = sub_c_is_null ? static_cast<void*>(sub) : sub->f_20;

    // TEST BL,BL ; JZ take ; XOR EAX,EAX ; JMP store ; MOV EAX,[EAX + 0x24] ;
    // MOV [ESP + 0x30],EAX
    record.sub_f_24 = sub_c_is_null ? nullptr
                                     : reinterpret_cast<void*>(
                                           static_cast<std::uintptr_t>(sub->f_24));

    // 0x00AE9FF4 CALL 0x0067DCC0 ; MOV EDX,[EAX] ; MOV EDX,[EDX + 0x14] ;
    // PUSH 0 ; LEA ECX,[ESP+0x14] ; PUSH ECX ; MOV ECX,[ESP+0x48] ; PUSH ECX ;
    // MOV ECX,EAX ; CALL EDX
    port_0067dcc0_vslot_14(port_0067dcc0_app_system(), record.dword_30, &record, 0u);

    // 0x00AE9FFA MOV EAX,[ESI + 0x20] ; CMP byte [EAX + 0x30],0 ; JNZ skip ;
    // 0x00AE9FF1 CALL 0x01021300 ; CMP EBP,EAX ; JZ skip
    if (sub->f_30 == 0u && profile != port_01021300_current()) {
        // 0x00AE9FFB..0x00AE9FE9 build the second 0x34-byte record with id
        // 0x43F2590, dword_08 left unwritten, dword_10 = EBP.
        Ae9f50BootRecord second;
        second.code_00 = nullptr;
        second.dword_04 = 0u;
        second.sub_f_0C = 0u;
        second.dword_0C = 0u;
        second.profile = profile;
        second.sub_f_20 = nullptr;
        second.sub_f_24 = nullptr;
        second.dword_28 = 0u;
        second.dword_2C = 0u;
        second.dword_30 = 0x43F2590u;
        second.dword_34 = 0u;
        second.dword_38 = 0u;
        // 0x00AE9FF9 CALL 0x0067DCC0 ; slot +0x14 with (0x43F2590, &second, 0)
        port_0067dcc0_vslot_14(port_0067dcc0_app_system(), second.dword_30, &second, 0u);
        // 0x00AE9F8F LEA ECX,[ESP + 0x50] ; CALL 0x00421CF0
        port_00421cf0_destroy_record(&second);
    }

    // 0x00AE9F94 CALL 0x00B3D380 ; TEST EAX,EAX ; JZ ;
    // PUSH 0x4D02E35 ; MOV ECX,EAX ; CALL 0x00B32250 (RET 0x4)
    void* flag_holder = port_00b3d380_get();
    if (flag_holder != nullptr) {
        port_00b32250_set_flag(flag_holder, 0x4D02E35u);
    }

    // 0x00AE9FA9 CALL 0x00A206F0 ; TEST EAX,EAX ; JZ 0x00AE9FBD ;
    // MOV EDX,[EAX] ; MOV ECX,EAX ; MOV EAX,[EDX + 0x20] ; CALL EAX ; JMP
    std::uint32_t published = 0u;
    void* published_obj = port_00a206f0_get();
    if (published_obj != nullptr) {
        published = port_a206f0_vslot_20(published_obj);
    }
    // PUSH EAX ; PUSH 0x1E5E7302 ; CALL 0x00435ED0 ; ADD ESP,8
    port_00435ed0_publish(0x1E5E7302u, published);

    // 0x00AE9FCD CALL 0x00B3D490 ; TEST EAX,EAX ; JZ ;
    // CALL 0x00B3D490 ; MOV ECX,EAX ; CALL 0x00AE8EA0
    void* tools = port_00b3d490_tool_manager();
    if (tools != nullptr) {
        port_00ae8ea0_reset(tools);
    }

    // PUSH 1 ; CALL 0x00B3D400 (bare RET, the word survives) ;
    // MOV ECX,EAX ; CALL 0x00E14C10 (RET 0x4)
    port_00e14c10_configure(port_00b3d400_noun_manager(), 1u);

    // 0x00AE9FF0 MOV EAX,[ESI + 0x74] ; CMP EAX,-1 ; JZ 0x00AEA121
    if (self->f_74 != -1) {
        // PUSH EAX ; CALL 0x00B3D2A0 (bare RET) ; MOV ECX,EAX ;
        // CALL 0x00BA6D80 (RET 0x4)
        void* entry = port_00ba6d80_lookup(port_00b3d2a0_manager_get(),
                                          static_cast<std::uint32_t>(self->f_74));
        if (entry != nullptr) {
            // CALL 0x01021090 ; PUSH EAX ; PUSH EDI ; CALL 0x00C35240 ; ADD ESP,8
            port_00c35240_bind(entry, port_01021090_get());
        }
        // 0x00AE9F1A MOV [ESI + 0x74],0xFFFFFFFF
        self->f_74 = -1;
    }

    // 0x00AE9F21 MOV ECX,[ESI + 0x64] ; POP EDI ; POP EBP ; POP EBX ;
    // 0x00AE9F27 CMP ECX,[ESI + 0x68] ; JZ 0x00AEA156
    char* slot64 = self->f_64;
    if (slot64 != self->f_68) {
        // PUSH 0 x4 ; MOV EAX,ECX ; PUSH 1 ; PUSH EAX ; CALL 0x00B3D4D0 ;
        // MOV ECX,EAX ; CALL 0x00AE0930 (RET 0x18)
        port_00ae0930_release(port_00b3d4d0_space_trading(), slot64, 1u, 0u, 0u, 0u, 0u);
        // 0x00AE9F45 MOV EAX,[ESI + 0x64] ; CMP EAX,[ESI + 0x68] ; JZ
        if (slot64 != self->f_68) {
            // MOV byte [EAX],0 ; MOV EDX,[ESI + 0x64] ; MOV [ESI + 0x68],EDX
            *slot64 = 0;
            self->f_68 = slot64;
        }
    }

    // 0x00AE9F56 LEA ECX,[ESP + 0x4] ; CALL 0x00421CF0
    port_00421cf0_destroy_record(&record);
}

}  // namespace wave13_w1_core_b08
}  // namespace openspore
