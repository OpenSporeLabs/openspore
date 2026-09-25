#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13 diplomacy reconstruction requires an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-13 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG-13 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG13_DIPLOMACY_CDECL __cdecl
#define PKG13_DIPLOMACY_STDCALL __stdcall
#define PKG13_DIPLOMACY_THISCALL __thiscall
#else
#define PKG13_DIPLOMACY_CDECL __attribute__((cdecl))
#define PKG13_DIPLOMACY_STDCALL __attribute__((stdcall))
#define PKG13_DIPLOMACY_THISCALL __attribute__((thiscall))
#endif

struct OpaqueRelationshipManager;
struct OpaqueEmpire;
struct OpaqueRelationshipMap;
struct OpaqueRelationshipEntry;

namespace openspore::reconstruction::pkg12_space {

struct Empire;
Empire* pkg12_space_01021300();

}  // namespace openspore::reconstruction::pkg12_space

namespace openspore::reconstruction::pkg13_diplomacy_predicate {

extern "C" {
OpaqueRelationshipMap* PKG13_DIPLOMACY_THISCALL
pkg13_unresolved_00d01ab0(OpaqueRelationshipManager* receiver,
                          std::uint32_t key_a, std::uint32_t key_b);
OpaqueRelationshipEntry* PKG13_DIPLOMACY_STDCALL pkg13_unresolved_00d01410(
    OpaqueRelationshipMap* map, std::uint32_t key_a, std::uint32_t key_b);
std::uint8_t PKG13_DIPLOMACY_THISCALL RelationshipManager_IsAllied2_00d01ff0(
    OpaqueRelationshipManager* receiver, OpaqueEmpire* empire_a,
    OpaqueEmpire* empire_b);
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_predicate
