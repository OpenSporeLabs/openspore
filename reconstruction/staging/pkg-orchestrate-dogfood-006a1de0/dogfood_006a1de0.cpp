#include "dogfood_006a1de0.hpp"

#include <cstddef>
#include <cstdint>

#if defined(_MSC_VER)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __thiscall
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL __attribute__((thiscall))
#define PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL __attribute__((cdecl))
#else
#error \
    "pkg-orchestrate-dogfood-006a1de0 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_orchestrate_dogfood_006a1de0 {

GetPropertyAltPorts g_dogfood_006a1de0_ports{};

namespace {

std::uintptr_t entry_address(const OpaquePropertyEntry* entry) {
  return reinterpret_cast<std::uintptr_t>(entry);
}

}

// 0x006a1de0 App::PropertyList::GetPropertyAlt, 47 instructions to 0x006a1e44.
//
// Prologue: PUSH ESI, MOV ESI,ECX, so the receiver is the ECX hidden this and
// ESI. 0x006a1de3 loads the zero extended byte at +0x2c, 0x006a1de7 loads the
// +0x18 word and 0x006a1deb loads the +0x1c word. Four words are pushed and
// 0x00612db0 is called at 0x006a1df6: the key byte, the address of this
// frame's own id slot (LEA ECX,[ESP+0x10] with four words still pushed), the
// +0x1c word and the +0x18 word. ADD ESP,0x10 at 0x006a1dff pops them again.
//
// Miss refinement, in this exact order: CMP EAX,EDI / JZ 0x006a1e11 treats a
// returned end pointer as a miss; CMP EDX,[EAX] with JC 0x006a1e11 treats an
// unsigned id below the entry key as a miss; LEA ECX,[EAX+0x18] with
// CMP EAX,ECX / JNZ 0x006a1e13 maps the self-offset sentinel onto the end
// pointer. All three converge on 0x006a1e11, which stores the end pointer in
// EAX.
//
// Hit path 0x006a1e17-0x006a1e24: reload the out pointer from ESP+0x10, form
// EAX+4, store that address through the out pointer, set AL to 0x1, restore
// the saved registers and return with RET 0x8.
//
// Parent path 0x006a1e27-0x006a1e3d: load the +0x30 word; when it is null,
// 0x006a1e40 clears AL and returns. Otherwise the body loads [ECX] as a
// vtable, pushes the out pointer then the id word, loads the slot word at
// displacement 0x20 and calls it with the +0x30 object still in ECX. The
// epilogue does not touch AL, so the callee's AL is the returned value.
extern "C" bool PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
property_list_get_property_alt_006a1de0(OpaquePropertyList* list,
                                        OpaqueWord property_id,
                                        OpaqueProperty** result) {
  GetPropertyAltPorts& ports = g_dogfood_006a1de0_ports;

  OpaquePropertyEntry* const entries_end = list->entries_end_1c;
  OpaquePropertyEntry* entry = ports.lower_bound_00612db0(
      static_cast<void*>(list->entries_begin_18),
      static_cast<void*>(entries_end), &property_id, list->lookup_mode_2c);

  if (entry != entries_end) {
    const std::uintptr_t address = entry_address(entry);
    if (property_id < entry->key_00 || address == address + 0x18u) {
      entry = entries_end;
    }
  }

  if (entry != entries_end) {
    *result = reinterpret_cast<OpaqueProperty*>(
        reinterpret_cast<std::uint8_t*>(entry) + 0x04u);
    return true;
  }

  OpaquePropertyList* const parent = list->parent_30;
  if (parent != nullptr) {
    return parent->vtable->operation_20(parent, property_id, result);
  }
  return false;
}

}

#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_CDECL
#undef PKG_ORCHESTRATE_DOGFOOD_006A1DE0_THISCALL
