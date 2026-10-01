// Bounded reconstruction of Resource::DatabaseDirectoryFiles::GetRefCount
// (VA 0x0069d3f0, SporeApp.exe 3.1.0.22).
//
// The body is four instructions and the machine ABI record for it abstained
// (ABI_UNKNOWN), so nothing here is promoted past what the listing shows:
//   0069d3f0  XOR EAX,EAX
//   0069d3f2  ADD ECX,0x8
//   0069d3f5  XADD.LOCK dword ptr [ECX],EAX
//   0069d3f9  RET
// Byte-level confirmation (GhidraMCP /read_memory, 10 bytes, same binary
// sha256 as the evidence pack): 33c083c108f00fc101c3.
//
// The __thiscall spelling below is a SOURCE-SIDE OBSERVATION of those four
// instructions, not a derived fact: ECX has no definition before its use as a
// memory-operand base, the body reads no stack slot, and Ghidra's own
// decompilation dereferences its in_ECX local while leaving the Stack[0x4]
// `this` parameter unread. The machine ABI record nevertheless abstained
// (ecx_reassigned_before_deref) and names no receiver register, so the
// convention is NOT established and this declaration cannot and does not move
// the ABI check off WARN. It is also not forced: a plain __cdecl reading of the
// same bytes is byte-identical, which is why the record listed all four
// conventions as candidates.
//
// ECX is never loaded from the stack and is only ever modified in place, so the
// dereference base is the entry ECX. The zero addend leaves the word unchanged
// and yields the prior value in EAX, which is what RET hands back.
//
// The receiver is an opaque pointer on purpose: abi_derived.receiver names no
// register and no displacement bounds, so no member is named and no struct
// layout is claimed here.

#ifndef OPENSPORE_RECONSTRUCTION_RESOURCE_DDF_GET_REF_COUNT_HPP
#define OPENSPORE_RECONSTRUCTION_RESOURCE_DDF_GET_REF_COUNT_HPP

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_RESOURCE_DDF_THISCALL __thiscall
#else
#define PKG_RESOURCE_DDF_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_ddf_refcount {

// Reads the 32-bit word at receiver+0x8 under the machine's LOCK XADD and
// returns the value that word held, leaving the word itself unchanged.
extern "C" std::int32_t PKG_RESOURCE_DDF_THISCALL
Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(void* receiver);

}  // namespace openspore::reconstruction::pkg_resource_ddf_refcount

#endif  // OPENSPORE_RECONSTRUCTION_RESOURCE_DDF_GET_REF_COUNT_HPP
