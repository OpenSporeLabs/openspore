#include "refcount_increment_00c6a960.hpp"

#if defined(_MSC_VER)
#define PKG_00C6A960_THISCALL __thiscall
#else
#define PKG_00C6A960_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_00c6a960_refcount_increment {

extern "C" std::int32_t PKG_00C6A960_THISCALL refcount_increment_00c6a960(
    OpaqueRefCountedReceiver* receiver) {
  // 0x00c6a960  8b 41 08    MOV EAX,dword ptr [ECX + 0x8]
  // 0x00c6a963  40          INC EAX
  // 0x00c6a964  89 41 08    MOV dword ptr [ECX + 0x8],EAX
  // 0x00c6a967  c3          RET
  //
  // One receiver word, at displacement 0x8, read and written. The displacement
  // is stated as an address computation rather than as a member access, because
  // the receiver record is bounds_only and names a displacement, not a member:
  // a reference count, a generation counter and a use count all increment the
  // same way. kCounterDisplacement is the header's spelling of that 0x8 and its
  // static_assert ties it to offsetof(OpaqueRefCountedReceiver, counter_008).
  //
  // The read-modify-write goes through a named local rather than a bare
  // `++` so that the order of the two memory operations is exactly what the
  // listing shows - load once, add once, store once - and so the increment is a
  // full 32-bit add with no truncation. Signed overflow is undefined behaviour
  // in C++, and the body has no compare, branch or clamp that would give
  // defined behaviour at the boundary, so the wrap case is exercised through
  // the unsigned alias below rather than through this signed path. The unsigned
  // alias is the same 32 bits the machine adds, and the file comment records
  // that the machine's behaviour at 0x7fffffff is to wrap.
  std::int32_t* const counter = word_at(receiver, kCounterDisplacement);
  *counter = static_cast<std::int32_t>(
      static_cast<std::uint32_t>(*counter) +
      static_cast<std::uint32_t>(kCounterIncrement));
  // EAX holds the post-increment value at the RET: INC EAX is the last write to
  // EAX and the store back through ECX does not touch it.
  return *counter;
}

extern "C" std::int32_t PKG_00C6A960_THISCALL thunk_00801220_jmp_00c6a960(
    OpaqueRefCountedReceiver* receiver) {
  // 0x00801220  e9 ..      JMP 0x00c6a960
  //
  // The observed thunk is a bare jump with no register fixup and no stack
  // adjustment, so the receiver reaching this wrapper is the receiver reaching
  // 0x00c6a960 and the returned word is that entry's EAX.
  return refcount_increment_00c6a960(receiver);
}

}