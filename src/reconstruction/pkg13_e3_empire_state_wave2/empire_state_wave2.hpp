#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(_M_IX86) && !defined(__i386__)
#error "PKG-13-E3-E2 empire state staging requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG13_E3_THISCALL __thiscall
#define PKG13_E3_CDECL __cdecl
#else
#define PKG13_E3_THISCALL __attribute__((thiscall))
#define PKG13_E3_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg13_e3_empire_state_wave2 {

using OpaqueWord = std::uint32_t;
using OpaqueTextWord = std::uint16_t;

struct OpaqueCurrentEmpire;
struct OpaqueStarManager;
struct OpaqueMetricValue;
struct OpaqueMetricContext;
struct OpaqueVectorElement;

struct OpaqueMetricSource {};

struct OpaqueText {
  OpaqueTextWord* begin;
  OpaqueTextWord* end;
};

struct OpaqueNameNode {
  OpaqueNameNode* left;
  OpaqueNameNode* right;
  std::uint8_t opaque[8];
  OpaqueWord rank;
  OpaqueTextWord* name;
};

struct OpaqueProfileNameState {
  OpaqueWord first;
  OpaqueWord second;
  OpaqueWord third;
  OpaqueNameNode* root;
  OpaqueWord reserved;
  OpaqueNameNode* leaf;
  std::uint8_t suffix[0x18];
};

struct OpaqueLocalRecord {
  OpaqueWord first;
  OpaqueWord second;
  OpaqueWord third;
};

struct OpaqueVectorElement {
  std::uint8_t prefix[0x74];
  OpaqueWord words[3];
};

struct OpaqueSpeciesProfile {
  std::uint8_t prefix[0x0c];
  OpaqueProfileNameState name_state;
  OpaqueText name;
  std::uint8_t vector_prefix[0x44];
  OpaqueVectorElement** vector_begin;
  OpaqueVectorElement** vector_end;
  OpaqueVectorElement** vector_capacity;
};

struct OpaqueProfile {
  std::uint8_t prefix[0x504];
  OpaqueWord color[3];
  std::uint8_t padding[0x0c];
  OpaqueText text;
};

struct OpaqueEmpireMetricState {
  std::uint8_t prefix[0xe0];
  float home_world_metric;
};

static_assert(sizeof(void*) == 4, "PKG-13-E3-E2 target pointers are 32-bit");
static_assert(sizeof(OpaqueText) == 8, "text range is two 32-bit pointers");
static_assert(offsetof(OpaqueNameNode, rank) == 0x10, "name node rank offset");
static_assert(offsetof(OpaqueNameNode, name) == 0x14, "name node text offset");
static_assert(offsetof(OpaqueProfileNameState, root) == 0x0c,
              "profile name root offset");
static_assert(offsetof(OpaqueProfileNameState, leaf) == 0x14,
              "profile name leaf offset");
static_assert(sizeof(OpaqueProfileNameState) == 0x30,
              "profile name state size");
static_assert(offsetof(OpaqueSpeciesProfile, name_state) == 0x0c,
              "species name-state offset");
static_assert(offsetof(OpaqueSpeciesProfile, name) == 0x3c,
              "species name offset");
static_assert(offsetof(OpaqueSpeciesProfile, vector_begin) == 0x88,
              "species vector begin offset");
static_assert(offsetof(OpaqueSpeciesProfile, vector_end) == 0x8c,
              "species vector end offset");
static_assert(offsetof(OpaqueVectorElement, words) == 0x74,
              "vector element word offset");
static_assert(offsetof(OpaqueProfile, color) == 0x504, "profile color offset");
static_assert(offsetof(OpaqueProfile, text) == 0x51c, "profile text offset");
static_assert(offsetof(OpaqueEmpireMetricState, home_world_metric) == 0xe0,
              "home-world metric cache offset");

using CurrentEmpirePort = OpaqueCurrentEmpire*(PKG13_E3_CDECL*)();
using MetricSourcePort =
    OpaqueMetricValue*(PKG13_E3_THISCALL*)(OpaqueEmpireMetricState*);
using MetricContextPort = OpaqueMetricContext*(PKG13_E3_CDECL*)();
using MetricValuePort = float(PKG13_E3_THISCALL*)(OpaqueMetricContext*,
                                                  OpaqueMetricValue*);
using ProfilePreparePort = void(PKG13_E3_THISCALL*)(OpaqueProfile*,
                                                    OpaqueWord*);
using StarManagerPort = OpaqueStarManager*(PKG13_E3_CDECL*)();
using RecordToPlanetPort = void(PKG13_E3_THISCALL*)(OpaqueStarManager*,
                                                    OpaqueLocalRecord*);
using ProfileApplyPort = void(PKG13_E3_THISCALL*)(OpaqueSpeciesProfile*,
                                                  OpaqueLocalRecord*);
using VectorColorPort = void(PKG13_E3_THISCALL*)(OpaqueVectorElement*,
                                                 OpaqueWord*);
using NameStatePort = void(PKG13_E3_THISCALL*)(OpaqueProfileNameState*,
                                               OpaqueLocalRecord*);
using NameAssignPort = void(PKG13_E3_THISCALL*)(OpaqueText*, OpaqueTextWord*,
                                                OpaqueTextWord*);
using RecordCleanupPort = void(PKG13_E3_CDECL*)(OpaqueLocalRecord*);

struct EmpireStatePorts {
  CurrentEmpirePort current_empire;
  MetricSourcePort metric_source;
  MetricContextPort metric_context;
  MetricValuePort metric_value;
  ProfilePreparePort profile_prepare;
  StarManagerPort star_manager;
  RecordToPlanetPort record_to_planet;
  ProfileApplyPort profile_apply;
  VectorColorPort vector_color;
  NameStatePort name_state;
  NameAssignPort name_assign;
  RecordCleanupPort record_cleanup;
};

EmpireStatePorts& empire_state_ports();

extern "C" OpaqueWord PKG13_E3_CDECL
SpeciesProfileSelector_00c30cc0(OpaqueWord archetype, OpaqueWord difficulty);

extern "C" OpaqueWord PKG13_E3_CDECL
ArchetypeRelationshipsID_00c30e20(OpaqueWord archetype, OpaqueWord difficulty);

extern "C" float PKG13_E3_THISCALL
HomeWorldMetricLazy_00c31890(OpaqueEmpireMetricState* state);

extern "C" void PKG13_E3_THISCALL
ProfileSetter_00c33690(OpaqueSpeciesProfile* species, OpaqueProfile* profile);

}
