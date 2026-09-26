#include "utfwin_layout_wave6.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_utfwin_layout_wave6 {
namespace {

#if defined(_MSC_VER)
#define LOCAL_THISCALL __thiscall
#define LOCAL_CDECL __cdecl
#else
#define LOCAL_THISCALL __attribute__((thiscall))
#define LOCAL_CDECL __attribute__((cdecl))
#endif

namespace unresolved_contracts {

extern "C" Opaque* LOCAL_THISCALL pkg_re_00951240(Opaque object, Opaque type);
extern "C" void LOCAL_CDECL pkg_re_008fe6d0(IntrusiveNode* position,
                                            IntrusiveNode* unused,
                                            IntrusiveNode* node);
extern "C" void LOCAL_THISCALL pkg_re_00958110(LayoutManager* manager);
extern "C" Opaque* LOCAL_THISCALL pkg_re_00962bc0(Opaque* object, Opaque flags);
extern "C" Opaque* LOCAL_THISCALL pkg_re_0096f240(Opaque* object, Opaque type);

}

Opaque load_opaque(const void* address, std::size_t offset) {
  Opaque value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(address) + offset,
              sizeof(value));
  return value;
}

void store_opaque(void* address, std::size_t offset, Opaque value) {
  std::memcpy(static_cast<std::uint8_t*>(address) + offset, &value,
              sizeof(value));
}

Opaque pointer_value(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

}

void LOCAL_THISCALL pkg_utfwin_layout_wave6_009601e0(OpaqueCastObject* object,
                                                     Opaque* output,
                                                     Opaque*& candidate_word) {
  Opaque* candidate = candidate_word;
  if (candidate != nullptr) {
    --candidate;
  }
  const Opaque expected = pointer_value(object) - 4u;
  if (load_opaque(candidate, 0x38) == expected) {
    candidate_word =
        reinterpret_cast<Opaque*>(pointer_value(candidate_word) + 4u);
    *output = pointer_value(candidate_word);
    return;
  }
  Opaque** returned = object->vtable->slot_d0(object, &candidate_word);
  *output = reinterpret_cast<Opaque>(*returned);
}

void LOCAL_THISCALL pkg_utfwin_layout_wave6_00961260(OpaqueCastObject* object,
                                                     Opaque* output) {
  *output = load_opaque(object, 0x38);
}

void LOCAL_THISCALL pkg_utfwin_layout_wave6_00961300(LayoutWindow* object,
                                                     LayoutWindow* child) {
  if (child == nullptr) {
    return;
  }
  LayoutWindow* expected_parent =
      pointer_value(object) == 4u ? nullptr : object;
  if (child->vtable->slot_10(child) != expected_parent) {
    return;
  }
  IntrusiveNode* node = &child->sibling_04;
  if ((child->flags_28 & 0x40u) == 0) {
    unresolved_contracts::pkg_re_008fe6d0(&object->children_38,
                                          &object->children_38, node);
  } else {
    IntrusiveNode* position = &object->children_38;
    IntrusiveNode* current = position->next;
    while (current != position) {
      LayoutWindow* candidate = reinterpret_cast<LayoutWindow*>(
          reinterpret_cast<std::uint8_t*>(current) -
          offsetof(LayoutWindow, sibling_04));
      if ((candidate->flags_28 & 0x40u) == 0) {
        position = current;
        break;
      }
      current = current->next;
    }
    if (position != node) {
      IntrusiveNode* node_next = node->next;
      IntrusiveNode* node_previous = node->previous;
      node_previous->next = node_next;
      node_next->previous = node_previous;
      IntrusiveNode* position_previous = position->previous;
      position_previous->next = node;
      node->previous = position_previous;
      node->next = position;
      position->previous = node;
    }
  }
  if (object->manager_30 != nullptr) {
    unresolved_contracts::pkg_re_00958110(object->manager_30);
  }
}

Opaque* LOCAL_THISCALL pkg_utfwin_layout_wave6_00962830(Opaque* object,
                                                        Opaque flags) {
  Opaque* adjusted = reinterpret_cast<Opaque*>(pointer_value(object) - 4u);
  return unresolved_contracts::pkg_re_00962bc0(adjusted, flags);
}

Opaque* LOCAL_THISCALL pkg_utfwin_layout_wave6_009646d0(Opaque object,
                                                        Opaque type) {
  if (type == 0x2f02135cu) {
    if (object == 0) {
      return nullptr;
    }
    return reinterpret_cast<Opaque*>(object + 0x0cu);
  }
  if (type == 0xeec58382u) {
    if (object == 0) {
      return nullptr;
    }
    return reinterpret_cast<Opaque*>(object + 4u);
  }
  return unresolved_contracts::pkg_re_00951240(object, type);
}

void LOCAL_THISCALL pkg_utfwin_layout_wave6_00967e20(OpaqueIndexCarrier* object,
                                                     Opaque index,
                                                     Opaque* value) {
  if (index < 6u) {
    object->values_14[static_cast<std::size_t>(index)] = value;
  }
}

Opaque* LOCAL_THISCALL
pkg_utfwin_layout_wave6_00967e60(OpaqueImageCarrier* object, Opaque* value) {
  object->value_2c = value;
  return value;
}

Opaque LOCAL_THISCALL pkg_utfwin_layout_wave6_00967e80(Opaque* object,
                                                       Opaque value) {
  Opaque* base = reinterpret_cast<Opaque*>(pointer_value(object) - 0x20cu);
  OpaqueTailVtable* vtable = *reinterpret_cast<OpaqueTailVtable* const*>(base);
  store_opaque(object, 0x34, value);
  return vtable->slot_8c(base, 1u);
}

Opaque* LOCAL_THISCALL pkg_utfwin_layout_wave6_0096feb0(Opaque* object,
                                                        Opaque type) {
  Opaque* adjusted = reinterpret_cast<Opaque*>(pointer_value(object) - 4u);
  return unresolved_contracts::pkg_re_0096f240(adjusted, type);
}

}

#undef LOCAL_CDECL
#undef LOCAL_THISCALL
