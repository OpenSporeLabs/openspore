#pragma once

#include <cstddef>

namespace openspore::reconstruction::wave13_w1_dispatch_b03 {

// A three-pointer EASTL-style UTF-16 string, as observed: {begin, end, capacity}
// where capacity is a byte address. The layout is proven by 0x00429760, which
// writes all three dwords and computes the capacity as begin + count * 2.
// char16_t, not char32_t/wchar_t: the target is Windows x86-32 where wchar_t
// is a 16-bit code unit, and every offset and shift in the reconstruction is a
// byte computation over that 2-byte element. Using the host wchar_t would make
// the model 4 bytes per element and silently halve every length.
struct OpaqueString16 {
  char16_t* begin;
  char16_t* end;
  char16_t* capacity;
};

static_assert(sizeof(void*) == 4, "the target is x86-32");
static_assert(sizeof(OpaqueString16) == 12,
              "the observed string object is three consecutive pointers");

// Unresolved ports. Bodies are not reconstructed; only the call shapes that the
// disassembly proves are declared here.
namespace unresolved_ports {

// 0x00429760(OpaqueString16* dst, unsigned int count) __thiscall, callee-clean.
// Reserving allocator; writes the empty static string when count < 2.
extern void __thiscall string16_reserve(OpaqueString16*, unsigned int);

// 0x00579a90(OpaqueString16* dst, const char16_t* src) __thiscall, callee-clean.
// Assign from a NUL-terminated wide string.
extern void __thiscall string16_assign(OpaqueString16*, const char16_t*);

// 0x00688f00(OpaqueString16* dst, const OpaqueString16* a,
//            const OpaqueString16* b) __thiscall, callee-clean.
// Plain concatenation: reserve, NUL-terminate, append a, then append b. No
// separator is inserted by this function.
extern OpaqueString16* __thiscall string16_concat(OpaqueString16*,
                                                   const OpaqueString16*,
                                                   const OpaqueString16*);

// 0x006b1f90(unsigned int id) __cdecl. Service/type registry lookup; the
// decompiled body is a map find on the key followed by a load of entry[5].
extern void* __cdecl lookup_save_area_by_id(unsigned int);

// 0x00931fa0(const char16_t* path) __cdecl. Ghidra's name is IO_File_Remove but
// the body is GetFileAttributesW plus a not-a-directory test, i.e. an exists
// predicate for a regular file.
extern unsigned char __cdecl file_exists(const char16_t*);

// 0x00931ff0(const char16_t* src, const char16_t* dst,
//            char allow_overwrite) __cdecl.
// MoveFileExW(src, dst, 3) where 3 is MOVEFILE_REPLACE_EXISTING |
// MOVEFILE_COPY_ALLOWED, guarded by an early "destination exists" bail-out when
// allow_overwrite is 0.
extern unsigned int __cdecl move_file(const char16_t*, const char16_t*,
                                      char);

// 0x00931fd0(const char16_t* path) __cdecl. DeleteFileW wrapper.
extern bool __cdecl delete_file(const char16_t*);

// 0x00932ae0(const char16_t* path) __cdecl. GetFileAttributesW, returns 0 when
// absent, 1 when it is a directory, otherwise delegates to 0x00932960. Modelled
// as a delete-tree; the concrete recursion is not reconstructed.
extern unsigned int __cdecl delete_path_recursive(const char16_t*);

// 0x011e0744 - the CRT memcpy the disassembly names directly.
extern void* __cdecl memcpy(void*, const void*, unsigned long);

// 0x00f47380 - the EASTL deallocate the disassembly names directly.
extern void __cdecl eastl_deallocate(void*);

}  // namespace unresolved_ports

// 0x006891f0. __cdecl, two wide-string arguments, no return value, SEH frame.
// Argument order proven from the two observed call sites: the caller pushes the
// source name first and the destination name second, so arg1 is the temporary
// source and arg2 is the final destination.
void __cdecl editor_promote_save_file_006891f0(const char16_t* source_name,
                                               const char16_t* dest_name);

}  // namespace openspore::reconstruction::wave13_w1_dispatch_b03
