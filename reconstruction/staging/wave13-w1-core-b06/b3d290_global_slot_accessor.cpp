// 0x00b3d290 — Simulator static-slot accessor.
//
// Original bytes (ghidra_read_memory 0x00b3d290,16 = a1 d4 ea 67 01 c3 cc ...):
//   0x00b3d290  a1 d4ea6701   MOV EAX, dword ptr [0x0167EAD4]
//   0x00b3d295  c3            RET
//
// Two instructions, six bytes, no frame, no callee, no ECX read.  The value is
// returned verbatim; there is no null check, no lazy construction and no
// fallback.  The slot lives in .bss and reads 0 in the on-disk image
// (ghidra_read_memory 0x0167EAD4,16 -> all zero), and it has no static writer:
// ghidra_get_xrefs_to 0x0167EAD4 returns exactly one reference, the READ at
// 0x00b3d290, so the slot is filled at runtime.
//
// Every one of the 32 direct callsites uses the result as a receiver, in the
// shape CALL 0x00b3d290 ; MOV ECX,EAX ; CALL <method>:
//   0x00b32aac / 0x00b32ab8 (FUN_00b32aa0), 0x00b32c7b / 0x00b32c87,
//   0x00b8ca55, 0x00c43ead, 0x00ac5333, ...
// and 0x00ac5333 null-checks it first (0x00ac533e TEST EAX,EAX ;
// 0x00ac5340 JZ 0x00ac534a).  The pointee type is therefore a runtime-installed
// singleton whose identity this batch could not establish; see the metadata
// sidecar's unresolved_questions.

#include "sim_core_b06_opaque.hpp"

namespace sim_core_b06 {

// Returns the raw 32-bit contents of the .bss dword at 0x0167EAD4.
//
// Bound: 0x0167EAD4 sits in the run of consecutive singleton slots
// 0x0167EAC0..0x0167EAEC that the neighbouring zero-argument accessors
// 0x00b3d220..0x00b3d320 read one dword at a time (ghidra_disassemble_bytes
// 0x00b3d200-0x00b3d330).  0x00b3d220 returns the ADDRESS 0x0167EAC0 rather
// than its contents, and 0x00b3d2c0 is a type-id demultiplexer rather than a
// slot reader, so the run is not homogeneous.  The SDK attributes
// 0xB3D2A0..0xB3D440 to Simulator::cGamePersistenceManager
// (Spore ModAPI/Spore/Simulator/SubSystem/GamePersistenceManager.h:65), but
// 0x00b3d2a0 demonstrably returns an object with fields at +0x184 and +0x1F4
// while cGamePersistenceManager is ASSERT_SIZE 0x4C, so that attribution is
// recorded as a CONFLICT and is not adopted here.
std::uint32_t SimCore_00b3d290_getGlobalEAD4() {
    // 0x00b3d290: MOV EAX,[0x0167EAD4] ; 0x00b3d295: RET
    // The literal address is not dereferenced here: in the shipping image the
    // slot is .bss (reads 0) and is only populated at runtime, so the model
    // routes the load through the accessor port instead of faulting.
    return getGlobalEAD4();
}

}  // namespace sim_core_b06
