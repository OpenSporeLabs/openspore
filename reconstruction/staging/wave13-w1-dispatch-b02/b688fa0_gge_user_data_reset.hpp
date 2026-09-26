// Wave-13 worker batch b02 -- target 0x00688fa0
// Clean-room reconstruction from SporeApp.exe 3.1.0.22.
//
// Observed shape: 203 instructions, 0x00688fa0..0x006891e5, 582 bytes.
// A __cdecl function taking one wide-string pointer and returning a pointer.
//
//   1. SEH frame installed, scope record 0x0120c84c
//   2. string A   <- the argument
//   3. base path  <- 0x006b1f90(0x04729a47) then virtual slot +0x28
//   4. string C   <- a copy of the base path
//   5. 0x00932ae0(C)   -- "is this a directory?", GetFileAttributesW + bit 0x10
//   6. string D   <- C concatenated with A  (0x00688f00)
//   7. 0x00931fd0(C)   -- DeleteFileW(C)
//   8. big   = registry-allocate 0x388 bytes under the name "Simulator", construct
//   9. small = registry-allocate 0x24  bytes under the name "Simulator",
//               0x0069fa60(small, big) wires big into small+0x18
//  10. six virtual calls, then four length-guarded frees
//  11. return small
//
// The class behind the registry name "Simulator" is NOT resolved: the only
// writer of that name is the allocator, and no SDK type is named "Simulator".
// See reconstruction/metadata/wave13-w1-dispatch-b02/00688fa0.json.

#pragma once

#include <cstdint>

namespace openspore::wave13::b02 {

// An EASTL::basic_string<wchar_t> header, three pointers. The allocator at
// 0x00429760 installs the inline sentinel &DAT_01667bac with
// {base, base, base + 2} whenever the requested capacity is below 2, and
// otherwise calls the block allocator with the literal type name "Editor" and
// the EASTL source path "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\
// SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h".
struct String16Header {
    wchar_t** begin;
    wchar_t** end;
    wchar_t** capacity;
};

// ---------------------------------------------------------------------------
// Opaque ports. Declared, never implemented.
// ---------------------------------------------------------------------------

// 0x006b1f90 -- a keyed service-locator lookup: map_int_whatever_find, then
// local_4[5] on a hit and null on a miss.
struct ServiceEntryPort;
ServiceEntryPort* service_locator_find_port(std::uint32_t key);

// 0x00579a90 -- __thiscall(header, const wchar_t*), RET 4. Measures the source
// in 16-bit units, allocates length + 1 through 0x00429760, memcpy's
// length * 2 bytes, sets header->end and writes a 16-bit NUL terminator.
void string16_assign_port(String16Header* out, const wchar_t* source);

// 0x00429760 -- __thiscall(header, capacity). Installs the inline sentinel for
// capacity < 2, otherwise allocates capacity * 2 bytes.
void string16_reserve_port(String16Header* header, std::uint32_t capacity);
// 0x00429580 -- the append primitive used by 0x00688f00; not read.
void string16_append_port(String16Header* header, const wchar_t* begin, const wchar_t* end);
// 0x00423650 -- __thiscall(dst, src_begin, src_end): an EASTL string assign.
void string16_assign_range_port(String16Header* dst, const wchar_t* src_begin, const wchar_t* src_end);

// 0x00688f00 -- cdecl(out, lhs, rhs). Allocates
// ((lhs.end - lhs.begin) >> 1) + ((rhs.end - rhs.begin) >> 1) + 1 elements,
// writes a 16-bit NUL, then appends lhs and rhs in that order. Returns out.
String16Header* string16_concat_port(String16Header* out, const String16Header* lhs,
                                     const String16Header* rhs);

// 0x00932ae0 -- returns 1 when GetFileAttributesW succeeds and the DIRECTORY
// bit (0x10) is set, 0 for an empty path, and otherwise defers to 0x00932960.
bool path_is_directory_port(const wchar_t* path);
// 0x00931fd0 -- DeleteFileW, returning its success as a bool.
bool path_delete_file_port(const wchar_t* path);

// 0x00926020 -- cdecl, six arguments. Allocates an object of `size` bytes
// registered under the class name at `name`, via the allocator's virtual slot
// +0x04, and returns the payload pointer (the block header plus 8). Returns
// null on a failed allocation.
void* registry_allocate_port(std::uint32_t size, const char* class_name, std::uint32_t a3,
                             std::uint32_t a4, std::uint32_t a5, std::uint32_t a6);

// 0x008d9f80 -- __thiscall(obj, 0, 0): the 0x388-byte object's constructor. It
// installs vtables PTR_FUN_014367b0 at +0 and PTR_FUN_0143679c at +4, sets
// 0x3f733333 at +0x2dc, 0x13 at +0x334 and 0x3e19999a at +0x338, links a
// self-referential list at +0x1c0, and calls vtable slot +0x04 of +0x0c.
void* construct_big_object_port(void* obj, std::uint32_t a2, std::uint32_t a3);
// 0x0069fa60 -- __thiscall(small, big): the 0x24-byte object's constructor.
// Installs vtable 0x014086e8 at +0 and 0x01408698 at +4, allocates a 0x68-byte
// "App" object and derives an 8-byte sub-object from it into +0x1c, and stores
// `big` into +0x18 with a virtual call on the old occupant.
void* construct_small_object_port(void* small, void* big);
// 0x0069f840 -- nested inside 0x0069fa60; not read.
void* derive_sub_object_port(void* small);

// 0x00f47380 -- free when non-null, via 0x009276c0.
void heap_free_port(void* block);

// The class-name string handed to the registry allocator.
extern const char g_simulator_class_name_013f09b4[];  // "Simulator"
// The scope record pushed at 0x00688fa2.
extern const unsigned char g_seh_scope_record_0120c84c[8];
// The service-locator key.
constexpr std::uint32_t kServiceKey = 0x04729a47;

}  // namespace openspore::wave13::b02
