#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-13 diplomacy transitions require an x86-32 target"
#endif

namespace openspore::reconstruction::pkg13_diplomacy_transitions {

using OpaqueWord = std::uint32_t;

struct OpaqueRelationshipManager {
  std::uint8_t opaque[0x100];
};

struct OpaqueTransitionRecord {
  std::uint8_t prefix[0x84];
  OpaqueWord key;
};

struct OpaqueRelationshipEntry {
  std::uint8_t prefix[4];
  OpaqueWord flags;
};

struct OpaqueRelationshipMap {
  std::uint8_t opaque[0x20];
};

struct OpaqueEventFactory {
  std::uint8_t opaque[0x20];
};

struct OpaqueEventRecord {
  void* vtable;
  OpaqueWord zero;
  OpaqueTransitionRecord* first;
  std::uint8_t opaque[4];
  OpaqueTransitionRecord* second;
  std::uint8_t opaque_tail[0x24];
  OpaqueWord cleanup_bitmask;
};

struct OpaqueCurrentRoot {
  std::uint8_t opaque[0x1d8];
  OpaqueWord empire_key;
};

static_assert(sizeof(void*) == 4, "PKG-13 diplomacy pointers are 32-bit");
static_assert(offsetof(OpaqueTransitionRecord, key) == 0x84,
              "PKG-13 transition record key offset");
static_assert(offsetof(OpaqueRelationshipEntry, flags) == 0x04,
              "PKG-13 relationship entry flags offset");
static_assert(offsetof(OpaqueEventRecord, first) == 0x08,
              "PKG-13 event first offset");
static_assert(offsetof(OpaqueEventRecord, second) == 0x10,
              "PKG-13 event second offset");
static_assert(offsetof(OpaqueEventRecord, cleanup_bitmask) == 0x38,
              "PKG-13 event cleanup bitmask offset");
static_assert(sizeof(OpaqueEventRecord) == 0x3c, "PKG-13 event record size");
static_assert(offsetof(OpaqueCurrentRoot, empire_key) == 0x1d8,
              "PKG-13 current-root empire key offset");

#if defined(_MSC_VER)
#define PKG13_DT_CDECL __cdecl
#define PKG13_DT_STDCALL __stdcall
#define PKG13_DT_THISCALL __thiscall
#else
#define PKG13_DT_CDECL __attribute__((cdecl))
#define PKG13_DT_STDCALL __attribute__((stdcall))
#define PKG13_DT_THISCALL __attribute__((thiscall))
#endif

using CurrentPlayerPort = OpaqueTransitionRecord*(PKG13_DT_CDECL*)();
using SelectMapPort = OpaqueRelationshipMap*(
    PKG13_DT_THISCALL*)(OpaqueRelationshipManager*, OpaqueWord, OpaqueWord);
using LookupPort = OpaqueRelationshipEntry*(
    PKG13_DT_STDCALL*)(OpaqueRelationshipMap*, OpaqueWord, OpaqueWord);
using PredicatePort = std::uint8_t(PKG13_DT_THISCALL*)(
    OpaqueRelationshipManager*, OpaqueTransitionRecord*,
    OpaqueTransitionRecord*);
using PairPort = void(PKG13_DT_THISCALL*)(OpaqueTransitionRecord*,
                                          OpaqueTransitionRecord*);
using CleanupPort = void(PKG13_DT_THISCALL*)(OpaqueTransitionRecord*);
using RootPort = OpaqueWord(PKG13_DT_CDECL*)(OpaqueTransitionRecord*);
using RootFollowupPort = OpaqueWord(PKG13_DT_THISCALL*)(OpaqueWord);
using RootCallbackC78450Port =
    void(PKG13_DT_THISCALL*)(OpaqueWord, OpaqueTransitionRecord*);
using RootCallbackC7bd40Port =
    void(PKG13_DT_THISCALL*)(OpaqueWord, OpaqueTransitionRecord*);
using EventFactoryPort = OpaqueEventFactory*(PKG13_DT_CDECL*)();
using EventDispatchPort = void(PKG13_DT_THISCALL*)(OpaqueEventFactory*,
                                                   OpaqueWord,
                                                   OpaqueEventRecord*,
                                                   OpaqueWord);
using EventCleanupPort = void(PKG13_DT_THISCALL*)(OpaqueEventRecord*);
using ApplyPort = void(PKG13_DT_THISCALL*)(OpaqueRelationshipManager*,
                                           OpaqueRelationshipMap*, OpaqueWord,
                                           OpaqueWord, OpaqueWord, float);
using ArrayRootPort = OpaqueWord(PKG13_DT_THISCALL*)(OpaqueTransitionRecord*);
using ArrayLookupPort = OpaqueWord(PKG13_DT_CDECL*)(OpaqueWord, OpaqueWord);
using ArrayApplyPort = void(PKG13_DT_THISCALL*)(OpaqueWord, OpaqueWord,
                                                OpaqueWord);
using CurrentRootPort = OpaqueCurrentRoot*(PKG13_DT_CDECL*)();
using CurrentEmpireKeyPort = OpaqueWord(PKG13_DT_THISCALL*)(OpaqueCurrentRoot*);
using PostTransitionPort = void(PKG13_DT_THISCALL*)(OpaqueRelationshipManager*,
                                                    OpaqueWord, OpaqueWord,
                                                    float);

struct TransitionPorts {
  CurrentPlayerPort current_player;
  SelectMapPort select_map;
  LookupPort lookup;
  PredicatePort transition_predicate;
  PairPort pair_c32830;
  PairPort pair_c327a0;
  PairPort pair_c345f0;
  PairPort pair_c34680;
  CleanupPort cleanup;
  RootPort root;
  RootFollowupPort root_followup;
  RootCallbackC78450Port root_callback_c78450;
  RootCallbackC7bd40Port root_callback_c7bd40;
  EventFactoryPort event_factory;
  EventDispatchPort event_dispatch;
  EventCleanupPort event_cleanup;
  ApplyPort apply_transition;
  ArrayRootPort array_root;
  ArrayLookupPort array_lookup;
  ArrayApplyPort array_apply;
  CurrentRootPort current_root;
  CurrentEmpireKeyPort current_empire_key;
  PostTransitionPort post_transition;
  void* event_vtable;
};

TransitionPorts& diplomacy_transition_ports();

void PKG13_DT_THISCALL DiplomacyTransition_00d01e30(OpaqueRelationshipManager*,
                                                    OpaqueTransitionRecord*,
                                                    OpaqueTransitionRecord*);
void PKG13_DT_THISCALL DiplomacyTransition_00d038e0(OpaqueRelationshipManager*,
                                                    OpaqueTransitionRecord*,
                                                    OpaqueTransitionRecord*);
void PKG13_DT_THISCALL DiplomacyTransition_00d065a0(OpaqueRelationshipManager*,
                                                    OpaqueTransitionRecord*,
                                                    OpaqueTransitionRecord*);
void PKG13_DT_THISCALL DiplomacyTransition_00d06920(OpaqueRelationshipManager*,
                                                    OpaqueTransitionRecord*,
                                                    OpaqueTransitionRecord*);

#undef PKG13_DT_CDECL
#undef PKG13_DT_STDCALL
#undef PKG13_DT_THISCALL

}
