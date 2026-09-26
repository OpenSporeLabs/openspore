// Wave-13 worker batch b02 -- target 0x004ad330
// Reconstructed from the live disassembly of 0x004ad330..0x004ad368
// (21 instructions). Every statement is anchored to an instruction address;
// see reconstruction/metadata/wave13-w1-dispatch-b02/004ad330.json.

#include "b4ad330_teardown_004ad330.hpp"

namespace openspore::wave13::b02 {

// 0x004ad330. Register-argument method: the receiver arrives in ECX, the return
// is void, there are no stack arguments, and the epilogue is
// MOV ESP,EBP; POP EBP; RET so any word pushed for a callee is discarded
// rather than popped.
void FUN_004ad330_reconstruct(TeardownTargetPartial* self) {
    // 0x004ad336: MOV dword ptr [EBP - 0xc],ECX -- the receiver is spilled
    // because the frame has no room in a register across both calls.
    // 0x004ad339/0x004ad33c: it is reloaded and 0x004ad280 is called
    // unconditionally, with no null check on the receiver.
    base_teardown_004ad280_port(self);

    // 0x004ad341/0x004ad344/0x004ad347: the receiver is reloaded a second time
    // from the spill slot and field_30 is copied to [EBP - 0x4].
    // 0x004ad34a/0x004ad34e: CMP dword ptr [EBP - 0x4],0x0 / JZ 0x004ad365 --
    // the only branch in the body, and it skips straight to the epilogue.
    if (self->field_30 == nullptr) {
        return;
    }

    // 0x004ad350/0x004ad353/0x004ad356: field_30 is loaded a second time and
    // stashed at [EBP - 0x8], so the null test and the call read it from two
    // different spill slots.
    // 0x004ad359/0x004ad35c: the receiver is pushed as the second argument.
    // 0x004ad35d/0x004ad360: ECX becomes field_30 and 0x004b9570 is called.
    // 0x004b9570 ends with RET 0x4, so it pops the pushed owner itself.
    finalise_member_004b9570_port(self->field_30, self);

    // 0x004ad365/0x004ad367/0x004ad368: MOV ESP,EBP; POP EBP; RET. The pushed
    // owner is discarded here rather than popped, which is consistent with the
    // callee having popped it.
}

}  // namespace openspore::wave13::b02
