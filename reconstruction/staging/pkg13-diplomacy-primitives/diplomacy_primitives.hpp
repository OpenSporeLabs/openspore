#pragma once

#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13 diplomacy primitives require an x86-32 target"
#endif

static_assert(sizeof(void*) == 4, "PKG-13 target pointers are 32-bit");
static_assert(sizeof(std::uint32_t) == 4, "PKG-13 target words are 32-bit");

#if defined(_MSC_VER)
#define PKG13_PRIM_CDECL __cdecl
#define PKG13_PRIM_FASTCALL __fastcall
#define PKG13_PRIM_STDCALL __stdcall
#define PKG13_PRIM_THISCALL __thiscall
#else
#define PKG13_PRIM_CDECL __attribute__((cdecl))
#define PKG13_PRIM_FASTCALL __attribute__((fastcall))
#define PKG13_PRIM_STDCALL __attribute__((stdcall))
#define PKG13_PRIM_THISCALL __attribute__((thiscall))
#endif

struct OpaqueRelationshipManager;
struct OpaqueRelationshipMap;
struct OpaqueRelationshipNode;
struct OpaqueRelationshipRecord;
struct OpaqueRelationshipEntry;
struct OpaqueSpaceContext;

namespace openspore::reconstruction::pkg13_diplomacy_primitives {

extern "C" {
void PKG13_PRIM_CDECL pkg13_unresolved_00d009a0(std::uint32_t* key_a,
                                                std::uint32_t* key_b);
void PKG13_PRIM_THISCALL pkg13_unresolved_00d00f80(
    OpaqueRelationshipMap* map, OpaqueRelationshipNode** output,
    std::uint32_t* key_pair);
OpaqueSpaceContext* PKG13_PRIM_CDECL pkg13_unresolved_010212a0();
std::uint32_t PKG13_PRIM_CDECL pkg13_unresolved_00ba6650(std::uint32_t value);
std::uint32_t PKG13_PRIM_FASTCALL
pkg13_unresolved_00ce6950(OpaqueSpaceContext* context);
OpaqueRelationshipRecord* PKG13_PRIM_CDECL pkg13_unresolved_00d01210(
    OpaqueRelationshipRecord* begin, OpaqueRelationshipRecord* end,
    std::uint32_t* key, std::uint32_t ignored_word);
OpaqueRelationshipEntry* PKG13_PRIM_STDCALL RelationshipLookup_00d01410(
    OpaqueRelationshipMap* map, std::uint32_t key_a, std::uint32_t key_b);
OpaqueRelationshipMap* PKG13_PRIM_THISCALL
RelationshipMapSelect_00d01ab0(OpaqueRelationshipManager* receiver,
                               std::uint32_t key_a, std::uint32_t key_b);
}

}  // namespace openspore::reconstruction::pkg13_diplomacy_primitives
