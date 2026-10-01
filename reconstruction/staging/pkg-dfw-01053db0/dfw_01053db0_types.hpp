// PKG-DFW-01053DB0 -- VA 0x01053db0
// SporeApp.exe 3.1.0.22, image base 0x00400000, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// Ghidra name: Simulator::cDefaultBeamTool::func4Ch
// Body: last instruction at 0x01053df9; the 23 instructions occupy
// 0x01053db0..0x01053dfb inclusive (76 bytes, `RET 0x4` = C2 04 00 ends at
// 0x01053dfb), and the 0xCC int3 padding starts at 0x01053dfc. Clean-room:
// analysis only.
//
// ---------------------------------------------------------------------------
// MACHINE LISTING (GhidraMCP /disassemble_function @ 0x01053db0, 23/23 parsed,
// and /read_memory @ 0x01053db0 len 80; the 76 body bytes below are the first
// 76 bytes of that 80-byte read, and the trailing CCCCCCCC is padding at
// 0x01053dfc and is not part of the body. Both sources agree byte for byte.)
//   568b7424088b8e2401000085c97420e8acfec5ff8b8e2401000085c97411c786240100000000
//   00008b018b5004ffd28bcee86a8fffff5e84c0740ce8d095aeff8bc8e8694ab2ffb001c20400
// ---------------------------------------------------------------------------
//   01053db0  PUSH ESI
//   01053db1  MOV ESI,dword ptr [ESP + 0x8]
//   01053db5  MOV ECX,dword ptr [ESI + 0x124]
//   01053dbb  TEST ECX,ECX
//   01053dbd  JZ 0x01053ddf
//   01053dbf  CALL 0x00cb3c70
//   01053dc4  MOV ECX,dword ptr [ESI + 0x124]
//   01053dca  TEST ECX,ECX
//   01053dcc  JZ 0x01053ddf
//   01053dce  MOV dword ptr [ESI + 0x124],0x0
//   01053dd8  MOV EAX,dword ptr [ECX]
//   01053dda  MOV EDX,dword ptr [EAX + 0x4]
//   01053ddd  CALL EDX
//   01053ddf  MOV ECX,ESI
//   01053de1  CALL 0x0104cd50
//   01053de6  POP ESI
//   01053de7  TEST AL,AL
//   01053de9  JZ 0x01053df7
//   01053deb  CALL 0x00b3d3c0
//   01053df0  MOV ECX,EAX
//   01053df2  CALL 0x00b78860
//   01053df7  MOV AL,0x1
//   01053df9  RET 0x4
//
// ---------------------------------------------------------------------------
// CALLING CONVENTION -- derived from the bytes, and it is NOT __thiscall
// ---------------------------------------------------------------------------
// 1. The receiver is the FIRST STACK ARGUMENT, not ECX.
//
//    PUSH ESI at 01053db0 lowers ESP by four, so the operand of
//    `MOV ESI,dword ptr [ESP + 0x8]` at 01053db1 is entry-ESP + 4: the single
//    ordinary stack slot. The machine-derived record agrees on the slot -- its
//    own observation obs-0003 is `STACK_SLOT_READ base=ESP disp=8 key=4
//    resolved=true size=4`, i.e. its resolver already computed key 4 -- and
//    then contradicts itself by projecting that same slot as `read: false` in
//    abi_derived.stack_arguments.slots[0]. The bytes are what is modelled.
//
// 2. The incoming ECX is DEAD. The record's own observation list shows ECX
//    appearing first as REG_READ at index 10, after a definite REG_WRITE
//    (mem_load) at index 2. Nothing between entry and index 2 reads ECX, so
//    whatever arrived there is discarded at 01053db5. A __thiscall receiver
//    would have to be read before it could be dereferenced, and this one is
//    never dereferenced. __thiscall is therefore refuted by the listing, and
//    the record's abstention reason "ecx_reassigned_before_deref" names the
//    symptom (ECX is reassigned) while missing the cause (ECX was never the
//    receiver).
//
// 3. The callee pops. `RET 0x4` at 01053df9 is `C2 04 00` in the raw bytes:
//    an immediate of four. That is callee-side cleanup of exactly one 4-byte
//    slot, so the body takes one stack argument and no more. Nothing in the
//    body reads entry-ESP + 8 or entry-ESP + 0xC, so there is no second or
//    third argument for it to pop.
//
//    This refutes the live prototype `bool Simulator::cDefaultBeamTool::
//    func4Ch(cDefaultBeamTool *this, cSpaceToolData *pTool, Vector3 *
//    param_3)`. That prototype is emitted by Ghidra under a literal
//    "WARNING: Unknown calling convention" banner and its parameter_count is
//    3; the listing supports one. The deriver's own candidate_conventions are
//    ["__stdcall", "__thiscall"], of which the bytes keep the first.
//
// 4. Consequently the entry is declared __stdcall here, not __thiscall. The
//    distinction matters on GCC -m32: __attribute__((stdcall)) on a
//    one-pointer prototype emits `ret $4`, which is the machine's own
//    terminator, while __attribute__((thiscall)) would additionally define a
//    hidden ECX parameter and change the modelled arity to two. Verified:
//    objdump of the compiled entry below shows `c2 04 00  ret $0x4`.
//
// 5. The 0x01053dbf call passes the loaded owned-target pointer in ECX and
//    pushes nothing, and the 0x01053ddd dispatch calls with ECX still holding
//    that same pointer, and the 0x0104cd50 / 0x00b78860 calls pass their
//    receivers in ECX with nothing pushed. Those four callees are therefore
//    ECX-receiver member calls even though this entry is not one; each is
//    declared with the THISCALL macro below and is owned by another package.
//
// ---------------------------------------------------------------------------
// TYPES
// ---------------------------------------------------------------------------
// The persisted record's `types` category for this VA names exactly six types:
// OpaqueBeamTarget *, OpaqueBeamToolState *, const OpaqueBeamTargetVTable *,
// std::uint32_t, std::uint8_t and void (__thiscall *)(OpaqueBeamTarget *).
// Those names are used below and nothing else is invented. No member of
// OpaqueBeamToolState, OpaqueBeamTarget or OpaqueBeamTargetVTable is named
// anywhere in this package: no record for this target says which member any
// displacement is, and the machine-derived receiver record abstains
// (receiver.offsets == [], receiver.register == null). Every access is
// therefore spelled as an opaque 4-byte word at a stated machine displacement,
// which is what the bytes license and no more.
//
// Sizes are deliberately not asserted. The largest displacement this body's
// OWN listing reads or writes on the receiver is 0x124, so 0x128 is the
// smallest extent covering this body's accesses -- but that is a floor, not a
// size, and no record gives the object's total size. The same holds for the
// owned target (largest observed displacement 0x4 through the table word) and
// for the table (0x4).

#ifndef PKG_DFW_01053DB0_TYPES_HPP
#define PKG_DFW_01053DB0_TYPES_HPP

#include <cstdint>

// Portable convention macros. GCC 16 rejects raw __thiscall/__cdecl/__stdcall
// spellings, so the token is selected once here and every declaration in the
// package names the macro instead of the attribute.
#if defined(_MSC_VER)
#define PKG_DFW_01053DB0_THISCALL __thiscall
#define PKG_DFW_01053DB0_CDECL __cdecl
#define PKG_DFW_01053DB0_STDCALL __stdcall
#else
#define PKG_DFW_01053DB0_THISCALL __attribute__((thiscall))
#define PKG_DFW_01053DB0_CDECL __attribute__((cdecl))
#define PKG_DFW_01053DB0_STDCALL __attribute__((stdcall))
#endif

namespace openspore::reconstruction::pkg_dfw_01053db0 {

// The three record-named pointee types. Each is an incomplete type on purpose:
// this package never names a member of any of them, so completing them here
// would assert a layout nothing grounds.
struct OpaqueBeamTarget;
struct OpaqueBeamToolState;
struct OpaqueBeamTargetVTable;

// The type the persisted record gives the vtable word at displacement 0x4 of
// the owned target's table: void (__thiscall *)(OpaqueBeamTarget *). The
// ECX-receiver shape is not a guess -- ECX still holds the owned target at the
// dispatch site (01053dc4 loaded it and nothing wrote ECX between), and nothing
// is pushed for that call.
using BeamTargetSlotFn = void(PKG_DFW_01053DB0_THISCALL*)(OpaqueBeamTarget*);

// -- the entry ----------------------------------------------------------------
//
// Name carries both the VA token and the last component of the record's name
// (Simulator::cDefaultBeamTool::func4Ch) so the span binds deterministically.
//
// One 4-byte stack argument, callee-popped. The return is the single byte the
// body writes into AL at 01053df7; see the .cpp for why the type is uint8_t
// and not bool.
extern "C" std::uint8_t PKG_DFW_01053DB0_STDCALL
dfw_01053db0_func4Ch_release(void* receiver);

// -- callees this package does not own ---------------------------------------
//
// Each is the exact register/stack shape the listing gives it. Each is defined
// as a recording observer in dfw_01053db0_model_test.cpp; none is defined here,
// and no header of the owning package is included.

// 01053dbf. Two instructions in the original (MOV byte ptr [ECX + 0x155],0x1 /
// RET), read live from the bridge. It is an ECX-receiver member call on the
// owned target: nothing is pushed and ECX still holds the pointer loaded at
// 01053db5. The +0x155 byte it writes belongs to the target's own body, not to
// this listing, so this package neither declares that displacement nor asserts
// what the byte means.
extern "C" void PKG_DFW_01053DB0_THISCALL beam_mark_00cb3c70(OpaqueBeamTarget* target);

// 01053de1. Four instructions in the original (MOV EAX,[ECX + 0x174] / SHR
// EAX,0x4 / AND AL,0x1 / RET), read live from the bridge. ECX-receiver, no
// push. Its result is one byte in AL. The word it reads at +0x174 is inside
// that callee's listing and not inside this one, so this package does not
// declare a +0x174 field on the receiver and does not name the bit's meaning.
extern "C" std::uint8_t PKG_DFW_01053DB0_THISCALL
beam_gate_0104cd50(const OpaqueBeamToolState* tool);

// 01053deb. Two instructions in the original (MOV EAX,[0x0167eb14] / RET), read
// live from the bridge. No argument, no push, and its EAX result becomes the
// ECX receiver of the next call at 01053df0. No record for this target names a
// type for the word it returns, so the return is an untyped void* here.
extern "C" void* PKG_DFW_01053DB0_CDECL beam_singleton_00b3d3c0();

// 01053df2. Three instructions in the original (AND dword ptr [ECX + 0x20],
// 0xfffffffb / MOV dword ptr [ECX + 0x55a0],0x0 / JMP 0x00b77aa0), read live
// from the bridge. ECX-receiver, no push, and the tail jump leaves ECX
// unchanged. Its two displacements are inside that callee's listing, not this
// one, so neither is declared on any type here.
extern "C" void PKG_DFW_01053DB0_THISCALL beam_reset_00b78860(void* relationship);

}  // namespace openspore::reconstruction::pkg_dfw_01053db0

#endif  // PKG_DFW_01053DB0_TYPES_HPP
