// Clean-room reconstruction of SporeApp.exe 0x00451e50 (sha256 25d42a7a...9d914e).
//
// Evidence: live Ghidra (decompile + disassembly + read_memory + 12 callsite
// windows) on program SporeApp.exe. No proprietary EA source was consulted.
//
// The whole body is 17 instructions / 51 bytes. Every offset, immediate and
// branch polarity below is transcribed from the disassembly listing.

#pragma once

#include <cstdint>

namespace openspore {
namespace dispatch_b05 {

// ---------------------------------------------------------------------------
// Opaque receiver.
//
// Two of the four offsets this function's callers touch are documented in
// Spore/Editors/EditorRigblock.h at exactly the observed positions:
//     /* 33Ch */ EditorRigblockPtr mpParent;
//     /* 3E0h */ EditorRigblockPtr mpSymmetricRigblock;
// and both are used as receivers of THIS function at 0x0048d1e0's caller
// (0x004a6893) and by 0x004956b0, which additionally reads
// `local_280[0xcf]` == +0x33C. That is strong evidence for the class, but no
// vtable containing 0x00451e50 exists in .rdata/.data and the SDK's own
// +0x18/+0x1C fields are mpModelWorld / mInstanceID rather than a vector, so the
// class name is recorded as a CANDIDATE and only the observed offsets are
// modelled here.
// ---------------------------------------------------------------------------
struct Rigblock00451e50 {
    std::uint32_t pad_0000[0x18c / 4];
    void* field_18c;  // 0x00451e68: MOV EDX,dword ptr [ECX + 0x18c]
    // +0x33C mpParent        (0x0048d1a0: CMP dword ptr [ESI + 0x33c],-1 style
    //                         null test, then this function is called on it)
    // +0x3E0 mpSymmetricRigblock (0x004a6893: receiver loaded from [ESI + 0x3e0])
};

// ---------------------------------------------------------------------------
// Opaque nested object reached through +0x18C.
//
// The body computes (char*)field_18c + 0x1c and then stores/loads at +0x1c of
// that, i.e. a full 32-bit store at (char*)field_18c + 0x38. The class of
// field_18C is NOT established: at 0x00495d5x the same pointer is used as
// `field_18C + 0x1c` for a transform-style call and at 0x0048d010
// `*(field_18C + 0x1c)` is dereferenced as a vtable. Only the +0x38 dword is
// claimed here.
// ---------------------------------------------------------------------------
struct NestedRigblockValue00451e50 {
    std::uint32_t pad_0000[0x38 / 4];
    std::int32_t field_38;  // 0x00451e7a: MOV dword ptr [EAX + 0x1c],ECX
};

// Reconstructed symbol. The receiver read, the null guard, the +0x38 store and
// the callee-cleaned single stack argument are all directly observed.
extern "C" void EditorRigblock_00451e50_SetNestedValue(
    Rigblock00451e50* self, std::int32_t value);

}  // namespace dispatch_b05
}  // namespace openspore
