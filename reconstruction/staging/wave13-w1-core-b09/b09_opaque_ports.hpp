#pragma once

// Opaque port declarations for wave13-w1-core-b09.
//
// Every type below is a PORCELAIN stand-in for something whose real layout or
// identity was NOT established by static evidence. Nothing here may be treated
// as a recovered Spore class: SporeApp.exe carries no MSVC RTTI and none of the
// six batch targets has a single DATA reference, so no vtable membership and no
// owning class could be proven for any of them.
//
// Naming rule used throughout: <role>_<evidence>, where the suffix records how
// the shape is known (observed offsets, decompiler label, immediate constant).

#include <cstdint>

#include "b09_abi.hpp"

// ---------------------------------------------------------------------------
// Ports shared by 0x00b25c30 (registry scan)
// ---------------------------------------------------------------------------

// 0x00b21340, the only callee of 0x00b25c30. __thiscall, ECX forwarded
// unchanged from the caller, RET 0x14 (five stack dwords), returns a pointer
// whose +4 and +8 hold a begin/end pair of 4-byte-stride elements.
// The five arguments observed at the 0x00b25c30 call site, in push order
// (rightmost PUSH = first stack argument):
//   arg1 = 0x018c43e8   .bss dword, reads 0 in the file image
//   arg2 = 0x00b1e500   code, defined at that address
//   arg3 = 0x00acdff0   code, defined at that address
//   arg4 = 0x00d3d420   code, defined at that address
//   arg5 = 0x00cd7d10   code, defined at that address
// The callee internally uses a map at this+0x98 and a singly linked list at
// this+0x78; neither container's element type was established.
struct OpaqueRegistryLookup5Args {
    void* arg1_key_bss_dword;   // 0x018c43e8
    void* arg2_code_00b1e500;
    void* arg3_code_00acdff0;
    void* arg4_code_00d3d420;
    void* arg5_code_00cd7d10;
};

// Layout as observed by 0x00b25c30: +0 unknown, +4 element array begin,
// +8 element array end. 0x00b25c30 also dereferences +0 and indexes the
// resulting pointer, so at least one further level of indirection exists.
struct OpaqueRegistryContainerObserved {
    std::uint32_t field_00;
    void* element_array_begin;  // +0x04
    void* element_array_end;    // +0x08
};

// Element of that array, as observed: an object whose embedded interface at
// +0x120 carries a vtable. Slot +0x58 is called with ECX = element + 0x120.
struct OpaqueRegistryElementObserved {
    std::uint8_t opaque[0x120];
};

// ---------------------------------------------------------------------------
// Ports shared by 0x00c47cc0 (state setter, phase == 3 tail)
// ---------------------------------------------------------------------------

// 0x0067dcc0, symbol-named by the imported SDK list as
// App::IAppSystem::Get. Body is a single MOV EAX,[0x015fd890] ; RET.
// The global 0x015fd890 reads 0 in the file image, so the returned pointer is
// runtime state and was NOT observed.
extern "C" void* opaque_AppSystem_Get_0067dcc0(void);

// The stack temporary built by 0x00c47cc0 on the phase == 3 path. Forward
// declared here because the app-system port below takes it by reference.
struct OpaqueBakeQueueTemporary;

// The interface returned by opaque_AppSystem_Get_0067dcc0. Only one slot was
// observed, +0x14. Five leading virtuals are declared as opaque padding purely
// so that the modelled method lands on vtable index 5, i.e. byte offset +0x14,
// which is the offset the body actually reads. The owning interface is NOT
// identified and the leading five entries are NOT observed.
struct OpaqueAppSystemIfcObserved {
    virtual void slot_00() {}
    virtual void slot_04() {}
    virtual void slot_08() {}
    virtual void slot_0c() {}
    virtual void slot_10() {}
    // +0x14, read at 0x00c47d51 and called with ECX = the app system and three
    // stack arguments: 0x038cf2fd, &temporary, 0.
    virtual void slot_14(std::uint32_t, OpaqueBakeQueueTemporary&, std::uint32_t) {}
    virtual ~OpaqueAppSystemIfcObserved() {}
};

// The stack temporary built by 0x00c47cc0 on the phase == 3 path.
// 0x00421cf0 walks it as 32 eight-byte pairs starting at +0x08 and uses the
// FIRST dword of pair 6 (byte offset +0x38) as a 32-bit selector mask, so the
// mask aliases the pair array rather than sitting after it.
//
// Observed stores by 0x00c47cc0, in program order:
//   +0x00 = 0x013eb90c   (immediately overwritten; dead store)
//   +0x04 = 0x00000000
//   +0x00 = 0x013eb844
//   +0x08 = ECX (the receiver)  -> pair[0].first
//   +0x30 = 0x038cf2fd          -> pair[5].first
//   +0x38 = 0x00000000          -> pair[6].first, the destructor's selector mask
// Nothing else in the 0x40-byte frame is initialised by this function.
//
// 0x00421cf0 then stores 0x013eb844 at +0, walks the 32 pairs calling slot +4 of
// each pair whose mask bit is set and whose first dword is non-null, then stores
// 0x013eb90c at +0 and finally 0x013eb918 at +0. The mask written here is 0, so
// the walk body never executes.
//
// NOTE: the Ghidra decompiler labels this local "CommandLine"; that label is a
// decompiler guess and is REJECTED - Spore ModAPI's App::CommandLine is
// ASSERT_SIZE 0x38 with an eastl::vector at +0x04, while this temporary needs a
// pair array reaching byte offset +0x108.
struct OpaqueBakeQueueTemporary {
    std::uint32_t vtable_a;  // +0x00
    std::uint32_t field_04;  // +0x04
    struct Pair {
        std::uint32_t first;
        std::uint32_t second;
    };
    Pair pairs[32];  // +0x08 .. +0x107, stride 8
};

// 0x00421cf0. __thiscall, ECX = address of the temporary, bare RET.
// Emulates exactly: the two vtable stores and the mask-gated 32-slot walk.
extern "C" void opaque_TemporaryDtor_00421cf0(OpaqueBakeQueueTemporary* self);
