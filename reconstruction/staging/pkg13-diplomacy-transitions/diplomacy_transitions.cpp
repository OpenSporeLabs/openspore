#include "diplomacy_transitions.hpp"

#if defined(_MSC_VER)
#define PKG13_DT_CDECL __cdecl
#define PKG13_DT_STDCALL __stdcall
#define PKG13_DT_THISCALL __thiscall
#else
#define PKG13_DT_CDECL __attribute__((cdecl))
#define PKG13_DT_STDCALL __attribute__((stdcall))
#define PKG13_DT_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg13_diplomacy_transitions {
namespace {

OpaqueTransitionRecord* default_current_player() { return nullptr; }
OpaqueRelationshipMap* PKG13_DT_THISCALL
default_select_map(OpaqueRelationshipManager*, OpaqueWord, OpaqueWord) {
  return nullptr;
}
OpaqueRelationshipEntry* PKG13_DT_STDCALL default_lookup(OpaqueRelationshipMap*,
                                                         OpaqueWord,
                                                         OpaqueWord) {
  return nullptr;
}
std::uint8_t PKG13_DT_THISCALL default_predicate(OpaqueRelationshipManager*,
                                                 OpaqueTransitionRecord*,
                                                 OpaqueTransitionRecord*) {
  return 0;
}
void PKG13_DT_THISCALL default_pair(OpaqueTransitionRecord*,
                                    OpaqueTransitionRecord*) {}
void PKG13_DT_THISCALL default_cleanup(OpaqueTransitionRecord*) {}
OpaqueWord default_root(OpaqueTransitionRecord*) { return 0; }
OpaqueWord PKG13_DT_THISCALL default_root_followup(OpaqueWord) { return 0; }
void PKG13_DT_THISCALL default_root_callback_c78450(OpaqueWord,
                                                    OpaqueTransitionRecord*) {}
void PKG13_DT_THISCALL default_root_callback_c7bd40(OpaqueWord,
                                                    OpaqueTransitionRecord*) {}
OpaqueEventFactory* default_event_factory() { return nullptr; }
void PKG13_DT_THISCALL default_event_dispatch(OpaqueEventFactory*, OpaqueWord,
                                              OpaqueEventRecord*, OpaqueWord) {}
void PKG13_DT_THISCALL default_event_cleanup(OpaqueEventRecord*) {}
void PKG13_DT_THISCALL default_apply(OpaqueRelationshipManager*,
                                     OpaqueRelationshipMap*, OpaqueWord,
                                     OpaqueWord, OpaqueWord, float) {}
OpaqueWord PKG13_DT_THISCALL default_array_root(OpaqueTransitionRecord*) {
  return 0;
}
OpaqueWord default_array_lookup(OpaqueWord, OpaqueWord) { return 0; }
void PKG13_DT_THISCALL default_array_apply(OpaqueWord, OpaqueWord, OpaqueWord) {
}
OpaqueCurrentRoot* default_current_root() { return nullptr; }
OpaqueWord PKG13_DT_THISCALL default_current_empire_key(OpaqueCurrentRoot*) {
  return 0;
}
void PKG13_DT_THISCALL default_post_transition(OpaqueRelationshipManager*,
                                               OpaqueWord, OpaqueWord, float) {}

OpaqueWord read_key(const OpaqueTransitionRecord* record) {
  return record->key;
}

OpaqueWord read_flags(const OpaqueRelationshipEntry* entry) {
  return entry->flags;
}

void clear_entry_flag(OpaqueRelationshipEntry* entry, OpaqueWord mask) {
  if (entry != nullptr) {
    entry->flags = read_flags(entry) & ~mask;
  }
}

void fused_array_lookup_apply(ArrayLookupPort lookup, ArrayApplyPort apply,
                              OpaqueWord selector, OpaqueWord object) {
  OpaqueWord result;
  __asm__ __volatile__(
      "pushl %[object]\n\t"
      "pushl %[selector]\n\t"
      "call *%[lookup]\n\t"
      "movl %%eax, %%ecx\n\t"
      "call *%[apply]"
      : [result] "=a"(result)
      : [lookup] "r"(lookup), [apply] "r"(apply), [selector] "r"(selector),
        [object] "r"(object)
      : "ecx", "edx", "memory", "cc");
}

void emit_event(TransitionPorts& ports, OpaqueTransitionRecord* first,
                OpaqueTransitionRecord* second, OpaqueWord event_id) {
  OpaqueEventRecord event{};
  event.vtable = ports.event_vtable;
  event.zero = 0;
  event.first = first;
  event.second = second;
  event.cleanup_bitmask = 0;
  OpaqueEventFactory* factory = ports.event_factory();
  ports.event_dispatch(factory, event_id, &event, 0);
  ports.event_cleanup(&event);
}

}

TransitionPorts& diplomacy_transition_ports() {
  static TransitionPorts ports{default_current_player,
                               default_select_map,
                               default_lookup,
                               default_predicate,
                               default_pair,
                               default_pair,
                               default_pair,
                               default_pair,
                               default_cleanup,
                               default_root,
                               default_root_followup,
                               default_root_callback_c78450,
                               default_root_callback_c7bd40,
                               default_event_factory,
                               default_event_dispatch,
                               default_event_cleanup,
                               default_apply,
                               default_array_root,
                               default_array_lookup,
                               default_array_apply,
                               default_current_root,
                               default_current_empire_key,
                               default_post_transition,
                               nullptr};
  return ports;
}

void PKG13_DT_THISCALL DiplomacyTransition_00d01e30(
    OpaqueRelationshipManager* manager, OpaqueTransitionRecord* first,
    OpaqueTransitionRecord* second) {
  TransitionPorts& ports = diplomacy_transition_ports();
  OpaqueTransitionRecord* current = ports.current_player();
  if (second == nullptr) {
    second = current;
  }
  const OpaqueWord first_key = read_key(first);
  const OpaqueWord second_key = read_key(second);
  OpaqueRelationshipMap* map = ports.select_map(manager, first_key, second_key);
  clear_entry_flag(ports.lookup(map, first_key, second_key), 0x2u);
  if (second != current) {
    map = ports.select_map(manager, second_key, first_key);
    clear_entry_flag(ports.lookup(map, second_key, first_key), 0x2u);
  }
  ports.pair_c32830(first, second);
  ports.pair_c32830(second, first);
  if (second == current) {
    emit_event(ports, first, second, 0x4445d44u);
  }
  ports.cleanup(first);
  ports.cleanup(second);
}

void PKG13_DT_THISCALL DiplomacyTransition_00d038e0(
    OpaqueRelationshipManager* manager, OpaqueTransitionRecord* first,
    OpaqueTransitionRecord* second) {
  TransitionPorts& ports = diplomacy_transition_ports();
  OpaqueTransitionRecord* current = ports.current_player();
  if (second == nullptr) {
    second = current;
  }
  if (ports.transition_predicate(manager, first, second) == 0) {
    ports.cleanup(first);
    ports.cleanup(second);
    return;
  }
  const OpaqueWord first_key = read_key(first);
  const OpaqueWord second_key = read_key(second);
  OpaqueRelationshipMap* map = ports.select_map(manager, first_key, second_key);
  clear_entry_flag(ports.lookup(map, first_key, second_key), 0x1u);
  if (second != current) {
    map = ports.select_map(manager, second_key, first_key);
    clear_entry_flag(ports.lookup(map, second_key, first_key), 0x1u);
  }
  ports.pair_c327a0(first, second);
  ports.pair_c327a0(second, first);
  if (second == current) {
    const OpaqueWord root = ports.root(first);
    const OpaqueWord owner = ports.root_followup(root);
    ports.root_callback_c78450(owner, first);
  }
  ports.cleanup(first);
  ports.cleanup(second);
}

void PKG13_DT_THISCALL DiplomacyTransition_00d065a0(
    OpaqueRelationshipManager* manager, OpaqueTransitionRecord* first,
    OpaqueTransitionRecord* second) {
  TransitionPorts& ports = diplomacy_transition_ports();
  OpaqueTransitionRecord* current = ports.current_player();
  if (second == nullptr) {
    second = current;
  }
  if (ports.transition_predicate(manager, first, second) != 0) {
    return;
  }
  const OpaqueWord first_key = read_key(first);
  const OpaqueWord second_key = read_key(second);
  OpaqueRelationshipMap* map = ports.select_map(manager, first_key, second_key);
  OpaqueRelationshipEntry* entry = ports.lookup(map, first_key, second_key);
  if (entry != nullptr) {
    entry->flags |= 0x1u;
  }
  entry = ports.lookup(map, first_key, second_key);
  clear_entry_flag(entry, 0x2u);
  if (second != current) {
    map = ports.select_map(manager, second_key, first_key);
    entry = ports.lookup(map, second_key, first_key);
    if (entry != nullptr) {
      entry->flags |= 0x1u;
    }
    entry = ports.lookup(map, second_key, first_key);
    clear_entry_flag(entry, 0x2u);
  }
  ports.pair_c345f0(first, second);
  ports.pair_c345f0(second, first);
  ports.cleanup(first);
  ports.cleanup(second);
  if (second == current) {
    const OpaqueWord root = ports.root(first);
    const OpaqueWord owner = ports.root_followup(root);
    ports.root_callback_c7bd40(owner, first);
  } else {
    map = ports.select_map(manager, second_key, first_key);
    ports.apply_transition(manager, map, second_key, first_key, 0x5f8a1adu,
                           1.0f);
  }
  if (first == current) {
    const OpaqueWord object = ports.array_root(first) + 0x504u;
    fused_array_lookup_apply(ports.array_lookup, ports.array_apply, 0xc09edaacu,
                             object);
  }
  map = ports.select_map(manager, first_key, second_key);
  ports.apply_transition(manager, map, first_key, second_key, 0x5f8a1adu, 1.0f);
}

void PKG13_DT_THISCALL DiplomacyTransition_00d06920(
    OpaqueRelationshipManager* manager, OpaqueTransitionRecord* first,
    OpaqueTransitionRecord* second) {
  TransitionPorts& ports = diplomacy_transition_ports();
  OpaqueTransitionRecord* current = ports.current_player();
  if (second == nullptr) {
    second = current;
  }
  DiplomacyTransition_00d038e0(manager, first, second);
  const OpaqueWord first_key = read_key(first);
  const OpaqueWord second_key = read_key(second);
  OpaqueRelationshipMap* map = ports.select_map(manager, first_key, second_key);
  OpaqueRelationshipEntry* entry = ports.lookup(map, first_key, second_key);
  if (entry != nullptr) {
    entry->flags |= 0x2u;
  }
  if (second != current) {
    map = ports.select_map(manager, second_key, first_key);
    entry = ports.lookup(map, second_key, first_key);
    if (entry != nullptr) {
      entry->flags |= 0x2u;
    }
  }
  ports.pair_c34680(first, second);
  ports.pair_c34680(second, first);
  if (second == current) {
    emit_event(ports, first, second, 0x4445d43u);
  }
  ports.cleanup(first);
  ports.cleanup(second);
  OpaqueCurrentRoot* current_root = ports.current_root();
  const OpaqueWord first_current_key = ports.current_empire_key(current_root);
  if (read_key(first) == first_current_key) {
    ports.post_transition(manager, read_key(current), 0x68b2938u, 1.0f);
  }
}

#undef PKG13_DT_CDECL
#undef PKG13_DT_STDCALL
#undef PKG13_DT_THISCALL

}
