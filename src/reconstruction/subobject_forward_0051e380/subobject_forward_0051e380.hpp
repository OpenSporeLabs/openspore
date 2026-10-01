#pragma once

// Bounded clean-room reconstruction of SporeApp.exe 0x0051e380, build
// 3.1.0.22, image base 0x00400000.
//
// Scope. Ten instructions, 0x0051e380..0x0051e397 (24 body bytes, then CC
// padding). The body establishes a frame, spills and reloads the receiver,
// adjusts the receiver by a fixed displacement, makes one direct call, and
// returns with a bare RET. It reads no stack word as an argument and writes
// no memory at all: the only register it consumes is the incoming ECX, and the
// only value that comes back is whatever the callee leaves in EAX.
//
// Machine transcript (live Ghidra 12.1.2 /disassemble_function at 0x0051e380):
//
//   0x0051e380  55              PUSH EBP
//   0x0051e381  8B EC           MOV EBP,ESP
//   0x0051e383  83 EC 10        SUB ESP,0x10
//   0x0051e386  89 4D F0        MOV dword ptr [EBP-0x10],ECX
//   0x0051e389  8B 4D F0        MOV ECX,dword ptr [EBP-0x10]
//   0x0051e38c  83 C1 04        ADD ECX,0x4
//   0x0051e38f  E8 AF 81 F3 FF  CALL 0x00453540
//   0x0051e394  8B E5           MOV ESP,EBP
//   0x0051e396  5D              POP EBP
//   0x0051e397  C3              RET
//
// ABI. The V1-VFT rule (docs/tooling/abi-inference-vftable-extension.md) proves
// this address is a slot of a vptr-backed vftable, the callee pops nothing
// (bare RET at 0x0051e397), and no stack word is read as an argument. It is
// therefore a non-static virtual member function: receiver in ECX,
// __thiscall, caller cleans, zero ordinary stack arguments. The receiver is
// spilled to [EBP-0x10] and reloaded only so the adjustor can be applied; the
// spill slot is never dereferenced.
//
// The adjustor. 0x0051e38c adds 0x4 to the receiver before the call, so the
// callee's receiver is the subobject at receiver+0x4, not the receiver itself.
// This is the standard MSVC shape for invoking a member of a base subobject
// that begins at a fixed displacement inside the derived object.
//
// The callee. 0x00453540 is a __thiscall member of that subobject: it spills
// ECX, reads the word at its own receiver+0x4, decrements it, stores the
// decremented value back, and returns it in EAX; when the decremented value is
// zero it instead stores 1, invokes slot 0 of the subobject's first word with
// the argument 1, and returns 0. Its full body is out of scope here; only its
// entry shape (ECX receiver, no stack argument, bare RET) and the fact that it
// leaves a 32-bit word in EAX on every path are used.
//
// Return. The body never writes EAX itself. The callee does, on every path,
// and the bare RET at 0x0051e397 hands that word back unchanged. The
// reconstruction therefore declares the target with the callee's return width
// (a 32-bit word) and forwards it, which is the literal reading of a body whose
// only exit is call-then-RET. The adjacent slot 0x0051e340 (the pre-increment
// of the same subobject word) returns its value the same way, which corroborates
// the reading; it is not, by itself, proof, and the alternative (a void wrapper
// that discards the callee's EAX) is recorded as an open question in the
// metadata sidecar.
//
// Deliberately absent: any class name, any struct with named members, any
// field layout. Co-membership in a vftable establishes only "virtual member of
// some class"; SporeApp.exe carries no MSVC RTTI, and the machine-derived
// receiver record for this target is absent (the persisted evidence pack holds
// no listing), so no displacement is corroborated by a receiver bounds record.
// The receiver and the subobject are carried as opaque types and the one
// displacement the body states is a constexpr pinned to its instruction.

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "subobject_forward_0051e380 reconstruction requires an x86-32 target"
#endif

// The one convention this body uses, spelled per compiler. MSVC has __thiscall
// as a keyword; gcc and clang only have the attribute form.
#if defined(_MSC_VER)
#define PKG_SUBFWD_THISCALL __thiscall
#else
#define PKG_SUBFWD_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::subobject_forward_0051e380 {

static_assert(sizeof(void*) == 4, "this reconstruction is 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "machine words are 32-bit");

// The receiver (ECX at entry) and the subobject the callee is invoked on. Both
// are opaque: no member of either is named anywhere in this package.
struct OpaqueReceiver;
struct OpaqueSubobject;

// 0x0051e38c ADD ECX,0x4 -- the byte displacement from the receiver to the
// subobject whose method is called. This is the only displacement the body
// states, and it is a this-pointer adjustment, not a field access: no
// instruction in the body reads or writes the four bytes at receiver+0x4.
constexpr std::size_t kSubobjectAdjustor = 0x04;
static_assert(kSubobjectAdjustor == 0x04,
              "ADD ECX,imm8 at the receiver-to-subobject adjustor");

// 0x00453540 -- the callee. ECX is its receiver (the subobject at
// receiver+0x4), it takes no stack argument, and it ends in a bare RET, so it
// is __thiscall with a zero-byte ordinary argument area. It leaves a 32-bit
// word in EAX on every path. Its body is not reconstructed in this package.
extern "C" std::uint32_t PKG_SUBFWD_THISCALL decrement_00453540(
    OpaqueSubobject* self);

// The machine transfer at 0x0051e38f is a direct CALL to 0x00453540. It is
// reached through a port so the model test can substitute a stub; the port is
// a test seam, not a change to the transfer, and production wiring points it
// at the real callee address. The field name carries the callee's VA so the
// call set stays comparable with the xref export.
struct Ports {
  std::uint32_t (PKG_SUBFWD_THISCALL* decrement_00453540)(OpaqueSubobject* self);
};

extern Ports* g_subobject_forward_ports;

// 0x0051e38c: the subobject base the callee is invoked on. Byte arithmetic on
// the receiver, then a reinterpret to the subobject type; no member of the
// receiver is accessed.
inline OpaqueSubobject* adjusted_this(OpaqueReceiver* self) {
  return reinterpret_cast<OpaqueSubobject*>(
      reinterpret_cast<unsigned char*>(self) + kSubobjectAdjustor);
}

// The target. ECX is the receiver, the function is a __thiscall member with
// zero ordinary stack arguments, and the only value it produces is the word
// the callee leaves in EAX.
extern "C" std::uint32_t PKG_SUBFWD_THISCALL subobject_forward_0051e380(
    OpaqueReceiver* self);

}  // namespace openspore::reconstruction::subobject_forward_0051e380

#undef PKG_SUBFWD_THISCALL
