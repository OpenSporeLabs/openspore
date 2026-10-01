#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "pkg-property-clear-wave12 requires an x86-32 target"
#endif

static_assert(sizeof(void *) == 4,
              "pkg-property-clear-wave12 requires 32-bit pointers");

namespace openspore::reconstruction::pkg_property_clear_wave12 {

using TargetWord = std::uint32_t;
using TargetSignedWord = std::int32_t;

struct OpaquePropertyList;
struct OpaqueProperty;
struct OpaquePropertyEntry;
struct OpaquePropertyMap;

// Observed callee ports. Names are derived from the disassembly of the callee
// bodies, not from any recovered symbol; both callees are unnamed in Ghidra
// (FUN_00612b20 / FUN_00685a30).
//
// 0x00612b20, cdecl, 3 stack args, caller cleans 3 dwords (ADD ESP,0xc at
// 0x006a2a9a). Signature recovered from its own body:
//   T* copy_entry_range(T* first, T* last, T* out)
// It walks [first,last) with a 0x18 stride, copying dword [e+0x00] and then the
// 0x14-byte tail [e+0x04] via the 0x00542b80 direct-copy routine, and returns
// the one-past-end destination. On the empty path (0x00612b53) it returns arg3
// verbatim, having copied nothing.
using CopyEntryRange = OpaquePropertyEntry* (*)(OpaquePropertyEntry* first,
                                                OpaquePropertyEntry* last,
                                                OpaquePropertyEntry* out);

// 0x00685a30, __thiscall, 2 stack args, RET 8. Signature recovered from its own
// body:
//   void release_entry_range(OpaquePropertyMap* self, Entry* first, Entry* last)
// It never writes first/last back, so it only releases elements; it does not
// itself rewind the range.
using ReleaseEntryRange = void (*)(OpaquePropertyMap* self,
                                   OpaquePropertyEntry* first,
                                   OpaquePropertyEntry* last);

// 0x0093db80, __thiscall, 1 stack arg (RET 4). Independent analysis in
// reconstruction/metadata/pkg10-editor-dispatch/0093db80.json records it as
// reading byte[receiver+0x10] bit 0x04 and clearing the words at +0x10 and
// +0x12. Here it is reached with ECX = &entry.property (entry+0x04) and a zero
// stack argument, gated on the same bit 0x04 of the same flags word.
using ResetPropertyValue = void (*)(OpaqueProperty* property,
                                    std::uint8_t clear_value);

struct OpaqueProperty {
  std::uint8_t value[0x10];
  std::uint16_t flags;  // +0x10
  std::uint16_t type;   // +0x12
};

struct OpaquePropertyEntry {
  TargetWord id;        // +0x00
  OpaqueProperty property;  // +0x04
};

// The 0x18-stride container reached through this+0x18. Only +0x18 (first) and
// +0x1c (last) are touched by this target; +0x20 and the rest are copied
// verbatim from the layout already recovered in
// reconstruction/staging/pkg-property-safe-wave9/property_safe_wave9.hpp.
struct OpaquePropertyMap {
  OpaquePropertyEntry* first;     // +0x18 of PropertyList
  OpaquePropertyEntry* last;      // +0x1c of PropertyList
  OpaquePropertyEntry* capacity;  // +0x20 of PropertyList
  std::uint8_t opaque_24_2f[0x0c];
};

struct OpaquePropertyList {
  void* vtable;                    // +0x00
  TargetWord ref_count;            // +0x04
  std::uint8_t name_key[0x0c];     // +0x08
  void* release_callback;          // +0x14
  OpaquePropertyMap properties;    // +0x18
  OpaquePropertyList* parent;      // +0x30
  TargetWord operations_done;      // +0x34
};

// App::PropertyList::Clear @ 0x006a2a80.
//
// ABI, derived from the disassembly (no ABI projection was persisted for this
// target): the body opens with PUSH EBX/EBP/ESI, copies ECX into EBX and never
// reads a stack argument; it ends with a bare RET (no immediate). That is
// __thiscall with ECX = this and no stack parameters. Its own frame is 16 bytes
// (four pushed registers) and it restores all four.
//
// Reachable only indirectly. The body has no direct call site in the binary and
// 0x006a2a80 is not present in the 18 dwords of vtable 0x01408820 as read at
// 0x01408820..0x01408867 (slot +0x48 there reads 0x00000000, the terminator).
extern "C" void App__PropertyList__Clear_006a2a80(OpaquePropertyList* list);

struct PropertyClearPorts {
  CopyEntryRange copy_entry_range;   // 0x00612b20
  ReleaseEntryRange release_entry_range;  // 0x00685a30
  ResetPropertyValue reset_property_value;  // 0x0093db80
};

// Emulates the recovered 0x18-stride release helper, 0x00685a30, including the
// flags-gated call into 0x0093db80.
void ReleaseEntryRange_00685a30(OpaquePropertyMap* self,
                                OpaquePropertyEntry* first,
                                OpaquePropertyEntry* last,
                                ResetPropertyValue reset_property_value);

// The magnitude of the multiply/shift block at 0x006a2a8f..0x006a2ac3,
// reproduced exactly: it yields -(last - first) for every well-formed span, so
// the ADD at 0x006a2ac3 rewinds last to first. Returns the value added to
// [list+0x1c].
TargetSignedWord ClearSpanDelta_006a2a80(TargetSignedWord span);

void App__PropertyList__Clear_006a2a80_impl(OpaquePropertyList* list,
                                            PropertyClearPorts ports);

}  // namespace openspore::reconstruction::pkg_property_clear_wave12
