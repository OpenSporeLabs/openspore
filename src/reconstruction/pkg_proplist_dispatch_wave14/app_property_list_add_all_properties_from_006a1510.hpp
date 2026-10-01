// PKG-PROLIST-DISPATCH-WAVE14 -- VA 0x006a1510
// App::PropertyList::AddAllPropertiesFrom
// SPORE/SporeBin/SporeApp.exe, 3.1.0.22, sha256
// 25d42a7a5c4d438fb155233230f57d29e2849bfdff5c889a5d0847f0469d914e
//
// This body dispatches virtually and nothing else: two indirect transfers
// through a register, no direct CALL or JMP immediate anywhere in the 19
// instructions, and no data-segment address. No slot member is named here
// because no machine record names one; the slots are addressed by the byte
// displacement the listing shows and read into a function-pointer local.

#pragma once

#include <cstdint>

#if defined(_MSC_VER)
#define PKG_PROPLIST_DISPATCH_WAVE14_THISCALL __thiscall
#else
#define PKG_PROPLIST_DISPATCH_WAVE14_THISCALL __attribute__((thiscall))
#endif

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-PROLIST-DISPATCH-WAVE14 requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg_proplist_dispatch_wave14 {

using TargetWord = std::uint32_t;

// The return word is named after the machine-derived ABI record's own
// classification, which is what that record says and no more:
//   categories.abi_derived.value.abi.return_semantics = "unclassified_in_EAX"
//   categories.abi_derived.value.return.register      = "EAX"
//   categories.abi_derived.value.return.register_class = "aggregate_unknown"
//   categories.abi_derived.value.return.type          = null
// `return.void_possible` is false here only because the inference raises that
// flag when EAX is never written and no call can clobber it (RT3); this body's
// last EAX write is the indirect CALL at 0x006a152f, so the flag is not
// evidence against a void return. Ghidra's live record types the same function
// "void" (ghidra_function.return_type, return_type_resolved true). The two
// records are reported, not merged: the disagreement is an open question in
// reconstruction/metadata/pkg-proplist-dispatch-wave14/006a1510.json.
using unclassified_in_EAX = TargetWord;

struct OpaquePropertyList;

// 0x006a1521  PUSH EAX   one stack word
// 0x006a1522  MOV EAX,dword ptr [EDX + 0x38]   the slot word
// 0x006a1525  CALL EAX   ECX is not rewritten, so the receiver stays in ECX
using SlotAt38 = unclassified_in_EAX(PKG_PROPLIST_DISPATCH_WAVE14_THISCALL*)(OpaquePropertyList*,
                                                  TargetWord);

// 0x006a152c  PUSH EDI   one stack word
// 0x006a152d  MOV ECX,ESI
// 0x006a1529  MOV EAX,dword ptr [EDX + 0x30]   the slot word
// 0x006a152f  CALL EAX
using SlotAt30 = unclassified_in_EAX(PKG_PROPLIST_DISPATCH_WAVE14_THISCALL*)(OpaquePropertyList*,
                                                  OpaquePropertyList*);

extern "C" unclassified_in_EAX PKG_PROPLIST_DISPATCH_WAVE14_THISCALL
app_property_list_add_all_properties_from_006a1510(OpaquePropertyList* receiver,
                                                  OpaquePropertyList* other);

}  // namespace openspore::reconstruction::pkg_proplist_dispatch_wave14
