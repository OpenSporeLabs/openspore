#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13-E2 diplomacy alt staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG13_E2_THISCALL __thiscall
#define PKG13_E2_CDECL __cdecl
#else
#define PKG13_E2_THISCALL __attribute__((thiscall))
#define PKG13_E2_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg13_e2_diplomacy_alt {

using OpaqueWord = std::uint32_t;

struct OpaqueRelationshipPolicy;
struct OpaqueIdentityObject;

using IdentityMethod = OpaqueWord(PKG13_E2_THISCALL*)(OpaqueIdentityObject*);

struct OpaqueIdentityVtable {
  std::array<IdentityMethod, 20> slots;
};

struct OpaqueIdentityObject {
  OpaqueIdentityVtable* vtable;
};

static_assert(sizeof(void*) == 4, "PKG-13-E2 target pointers are 32-bit");
static_assert(sizeof(IdentityMethod) == 4,
              "PKG-13-E2 virtual slots are 32-bit");
static_assert(offsetof(OpaqueIdentityVtable, slots) +
                      19 * sizeof(IdentityMethod) ==
                  0x4c,
              "PKG-13-E2 identity dispatch is at vtable offset 0x4c");

using PolicyResolverPort = OpaqueRelationshipPolicy*(
    PKG13_E2_CDECL*)(OpaqueWord, OpaqueWord, OpaqueWord);
using RelationshipStagePort = OpaqueWord(PKG13_E2_THISCALL*)(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord);
using RawRelationshipScorePort = float(PKG13_E2_THISCALL*)(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord);

struct DiplomacyAltPorts {
  PolicyResolverPort policy_resolver;
  RelationshipStagePort relationship_stage;
  RawRelationshipScorePort raw_relationship_score;
};

DiplomacyAltPorts& diplomacy_alt_ports();

extern "C" float PKG13_E2_CDECL
RelationshipScoreBand_00d00d00(OpaqueWord source, OpaqueWord target);

extern "C" float PKG13_E2_THISCALL RelationshipScoreObjects_00d00d60(
    OpaqueRelationshipPolicy* policy, OpaqueIdentityObject* first,
    OpaqueIdentityObject* second, OpaqueWord mode);

}
