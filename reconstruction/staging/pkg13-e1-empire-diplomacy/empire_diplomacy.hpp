#pragma once

#include <cstddef>
#include <cstdint>

namespace openspore::reconstruction::pkg13_e1_empire_diplomacy {

using OpaqueWord = std::uint32_t;

struct Opaque;
struct OpaqueRoot;
struct OpaqueCurrentEmpire;
struct OpaqueStarManager;
struct OpaqueStar;
struct OpaqueMetric;
struct OpaqueEventProfile {
  std::uint8_t opaque[4];
};
struct OpaqueAppSystem;

struct OpaqueRelationshipPolicy {
  std::uint8_t prefix[0x10];
  float first;
  float second;
  float third;
  float fourth;
};

struct OpaqueDirectedEmpire {
  std::uint8_t prefix[0x89];
  std::uint8_t relationship_gate;
  std::uint8_t middle[0x3e2];
  OpaqueWord relationship_owner_id;
};

struct OpaqueRelationshipPairNode {
  OpaqueRelationshipPairNode* left;
  OpaqueRelationshipPairNode* right;
  OpaqueRelationshipPairNode* parent;
  OpaqueWord parent_tag;
  OpaqueWord key_a;
  OpaqueWord key_b;
  Opaque* payload;
};

struct OpaqueRelationshipPairMap {
  OpaqueWord prefix;
  OpaqueRelationshipPairNode* anchor;
  OpaqueWord root_prefix;
  OpaqueRelationshipPairNode* root;
  OpaqueWord size;
  OpaqueWord allocator;
};

struct OpaqueRelationshipEventNode {
  OpaqueRelationshipEventNode* left;
  OpaqueRelationshipEventNode* right;
  OpaqueRelationshipEventNode* parent;
  OpaqueWord parent_tag;
  OpaqueWord key;
  float value;
  OpaqueWord tail;
};

struct OpaqueRelationshipEventMap {
  OpaqueWord prefix;
  OpaqueRelationshipEventNode* anchor;
  OpaqueRelationshipEventNode* root;
  OpaqueWord size;
  OpaqueWord allocator;
};

struct OpaqueRelationshipEntry {
  float value;
  OpaqueWord flags;
  OpaqueRelationshipEventMap events;
};

struct OpaqueRelationshipManager {
  std::uint8_t prefix[0x10];
  float thresholds[4];
  std::uint8_t opaque[0xe0];
};

struct OpaquePropertyValue {
  std::uint8_t prefix[0x12];
  std::uint16_t type;
};

struct OpaqueFloatProperty {
  std::uint8_t prefix[0x12];
  std::uint16_t type;
};

struct OpaqueEventKey {
  OpaqueWord base;
  OpaqueWord modifier;
};

static_assert(sizeof(void*) == 4, "PKG-13-E1 pointers are 32-bit");
static_assert(offsetof(OpaqueRelationshipPolicy, first) == 0x10,
              "relationship policy threshold offset");
static_assert(offsetof(OpaqueRelationshipPolicy, fourth) == 0x1c,
              "relationship policy final threshold offset");
static_assert(offsetof(OpaqueDirectedEmpire, relationship_gate) == 0x89,
              "directed empire gate offset");
static_assert(offsetof(OpaqueDirectedEmpire, relationship_owner_id) == 0x46c,
              "directed empire owner identity offset");
static_assert(offsetof(OpaqueRelationshipPairMap, anchor) == 0x04,
              "relationship map sentinel offset");
static_assert(offsetof(OpaqueRelationshipPairMap, root) == 0x0c,
              "relationship map root offset");
static_assert(offsetof(OpaqueRelationshipPairNode, key_a) == 0x10,
              "relationship pair key offset");
static_assert(offsetof(OpaqueRelationshipPairNode, payload) == 0x18,
              "relationship pair payload offset");
static_assert(offsetof(OpaqueRelationshipEventNode, value) == 0x14,
              "relationship event value offset");
static_assert(offsetof(OpaqueRelationshipEntry, events) == 0x08,
              "relationship event map offset");
static_assert(offsetof(OpaqueRelationshipManager, thresholds) == 0x10,
              "relationship manager threshold offset");
static_assert(offsetof(OpaquePropertyValue, type) == 0x12,
              "property type offset");
static_assert(offsetof(OpaqueFloatProperty, type) == 0x12,
              "float property type offset");

#if defined(_MSC_VER)
#define PKG13_E1_THISCALL __thiscall
#define PKG13_E1_FASTCALL __fastcall
#define PKG13_E1_STDCALL __stdcall
#define PKG13_E1_CDECL __cdecl
#else
#define PKG13_E1_THISCALL __attribute__((thiscall))
#define PKG13_E1_FASTCALL __attribute__((fastcall))
#define PKG13_E1_STDCALL __attribute__((stdcall))
#define PKG13_E1_CDECL __attribute__((cdecl))
#endif

using RelationshipScorePort = float(PKG13_E1_THISCALL*)(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord);
using RelationshipStagePort = std::int32_t(PKG13_E1_FASTCALL*)(
    OpaqueDirectedEmpire*);
using RootPort = OpaqueRoot*(PKG13_E1_CDECL*)();
using RootFollowupPort = OpaqueRoot*(PKG13_E1_THISCALL*)(OpaqueRoot*);
using RootStagePort = std::int32_t(PKG13_E1_FASTCALL*)(OpaqueRoot*);
using ResolveCurrentEmpirePort = OpaqueDirectedEmpire*(PKG13_E1_CDECL*)(
    OpaqueRoot*);
using DirectedIdentityPort = OpaqueWord(PKG13_E1_THISCALL*)(
    OpaqueDirectedEmpire*);
using RelationshipClassifierPort = OpaqueWord(PKG13_E1_THISCALL*)(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord);
using PropertyServicePort = Opaque*(PKG13_E1_CDECL*)();
using PropertyObjectPort = std::uint8_t(PKG13_E1_THISCALL*)(
    Opaque*, OpaqueWord, OpaquePropertyValue**);
using PropertyReadPort = std::uint8_t(PKG13_E1_THISCALL*)(
    OpaquePropertyValue*, OpaqueWord, OpaqueFloatProperty**);
using PropertyNumberPort = const float*(PKG13_E1_CDECL*)();
using PropertyReleasePort = void(PKG13_E1_THISCALL*)(OpaquePropertyValue*);
using RelationshipLookupPort = OpaqueRelationshipEntry*(
    PKG13_E1_STDCALL*)(OpaqueRelationshipPairMap*, OpaqueWord, OpaqueWord);
using RelationshipEnsurePort = OpaqueRelationshipEntry*(
    PKG13_E1_THISCALL*)(OpaqueRelationshipManager*, OpaqueRelationshipPairMap*,
                        OpaqueWord, OpaqueWord);
using RuntimeModePort = OpaqueWord(PKG13_E1_CDECL*)();
using StarManagerPort = OpaqueStarManager*(PKG13_E1_CDECL*)();
using StarLookupPort = OpaqueStar*(PKG13_E1_CDECL*)(OpaqueStarManager*,
                                                     OpaqueWord);
using StarKeyPort = OpaqueWord(PKG13_E1_CDECL*)(OpaqueStarManager*);
using EventProfilePort = OpaqueEventProfile*(PKG13_E1_THISCALL*)(
    OpaqueRelationshipManager*, OpaqueEventKey*);
using EventLowerBoundPort = OpaqueRelationshipEventNode*(PKG13_E1_CDECL*)(
    OpaqueRelationshipEventMap*, OpaqueWord);
using EventInsertPort = OpaqueRelationshipEventNode*(PKG13_E1_THISCALL*)(
    OpaqueRelationshipEventMap*, OpaqueWord);
using EventRemovePort = void(PKG13_E1_THISCALL*)(
    OpaqueRelationshipEventMap*, OpaqueRelationshipEventNode*);
using RelationshipValuePort = float(PKG13_E1_THISCALL*)(
    OpaqueRelationshipManager*, OpaqueRelationshipPairMap*, OpaqueWord,
    OpaqueWord, OpaqueWord, OpaqueEventProfile*);
using ResetRelationshipPort = void(PKG13_E1_THISCALL*)(OpaqueWord);
using AggregateRelationshipPort = void(PKG13_E1_THISCALL*)(
    OpaqueRelationshipManager*, OpaqueWord, OpaqueWord, OpaqueWord);
using AppSystemPort = OpaqueAppSystem*(PKG13_E1_CDECL*)();
using EventDispatchPort = void(PKG13_E1_THISCALL*)(
    OpaqueAppSystem*, OpaqueWord, OpaqueWord, OpaqueWord);
using CurrentPlayerIdPort = OpaqueWord(PKG13_E1_CDECL*)();
using DirectedEmpireObjectPort = OpaqueDirectedEmpire*(PKG13_E1_CDECL*)(
    OpaqueWord);
using DirectedEmpireKindPort = std::int32_t(PKG13_E1_CDECL*)(OpaqueWord);
using MetricOwnerPort = OpaqueMetric*(PKG13_E1_CDECL*)();
using MetricValuePort = float(PKG13_E1_THISCALL*)(OpaqueMetric*);

struct EmpireDiplomacyPorts {
  RelationshipScorePort relationship_score;
  RelationshipStagePort relationship_stage;
  RootPort noun_root;
  RootFollowupPort root_followup;
  RootStagePort root_stage;
  ResolveCurrentEmpirePort resolve_current_empire;
  DirectedIdentityPort directed_identity;
  RelationshipClassifierPort relationship_classifier;
  PropertyServicePort property_service;
  PropertyObjectPort property_object;
  PropertyReadPort property_read;
  PropertyNumberPort property_number;
  PropertyReleasePort property_release;
  RelationshipLookupPort relationship_lookup;
  RelationshipEnsurePort relationship_ensure;
  RuntimeModePort runtime_mode;
  StarManagerPort star_manager;
  StarLookupPort star_lookup;
  StarKeyPort star_key;
  EventProfilePort event_profile;
  EventLowerBoundPort event_lower_bound;
  EventInsertPort event_insert;
  EventRemovePort event_remove;
  RelationshipValuePort relationship_value;
  ResetRelationshipPort reset_relationship;
  AggregateRelationshipPort aggregate_relationship;
  AppSystemPort app_system;
  EventDispatchPort event_dispatch;
  CurrentPlayerIdPort current_player_id;
  DirectedEmpireObjectPort directed_empire_object;
  DirectedEmpireKindPort directed_empire_kind;
  MetricOwnerPort metric_owner;
  MetricValuePort metric_value;
};

EmpireDiplomacyPorts& empire_diplomacy_ports();

extern "C" OpaqueWord PKG13_E1_THISCALL RelationshipClassify_00d00a70(
    OpaqueRelationshipPolicy*, OpaqueWord, OpaqueWord, OpaqueWord);

extern "C" float PKG13_E1_STDCALL RelationshipOwnerAdjustment_00d00b40(
    OpaqueWord, OpaqueDirectedEmpire*);

extern "C" void PKG13_E1_FASTCALL RelationshipLoadThresholds_00d00db0(
    OpaqueRelationshipManager*);

extern "C" float PKG13_E1_THISCALL DirectedEmpirePenalty_00d00ee0(
    OpaqueDirectedEmpire*, OpaqueDirectedEmpire*);

extern "C" void PKG13_E1_THISCALL RelationshipMapLowerBound_00d00f80(
    OpaqueRelationshipPairMap*, OpaqueRelationshipPairNode**,
    OpaqueRelationshipPairNode*);

extern "C" float PKG13_E1_THISCALL RelationshipApply_00d05d90(
    OpaqueRelationshipManager*, OpaqueRelationshipPairMap*, OpaqueWord,
    OpaqueWord, OpaqueWord, float);

}
