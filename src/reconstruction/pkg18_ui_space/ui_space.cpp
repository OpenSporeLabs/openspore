#include "ui_space.hpp"

#include <cmath>
#include <cstring>

namespace openspore::reconstruction::pkg18_ui_space {
namespace {

constexpr Opaque kDefaultResource0 = 0x0164f240u;
constexpr Opaque kDefaultResource1 = 0x0164f244u;
constexpr Opaque kDefaultResource2 = 0x0164f248u;
constexpr Opaque kAlternateResource0 = 0x0164f234u;
constexpr Opaque kAlternateResource1 = 0x0164f238u;
constexpr Opaque kAlternateResource2 = 0x0164f23cu;
constexpr Opaque kDomain = 0x013f6b3cu;
constexpr Opaque kMinimapResource = 0x00190722eu;
constexpr Opaque kOneBits = 0x3f800000u;
constexpr Opaque kNegativeOneBits = 0xbf800000u;

template <typename T>
Opaque object_word(T* object) {
  return reinterpret_cast<Opaque>(object);
}

SpaceUiObject* object_from(Opaque value) {
  return reinterpret_cast<SpaceUiObject*>(value);
}

template <typename Value>
Value load_word(const void* base, std::size_t offset) {
  Value value{};
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

template <typename Value>
void store_word(void* base, std::size_t offset, Value value) {
  std::memcpy(static_cast<unsigned char*>(base) + offset, &value,
              sizeof(value));
}

SpaceUiObject* load_object(void* base, std::size_t offset) {
  return object_from(load_word<Opaque>(base, offset));
}

using Slot0 = Opaque(PKG18_THISCALL*)(SpaceUiObject*);
using Slot1 = Opaque(PKG18_THISCALL*)(SpaceUiObject*, Opaque);
using Slot2 = Opaque(PKG18_THISCALL*)(SpaceUiObject*, Opaque, Opaque);
using Slot4 = Opaque(PKG18_THISCALL*)(SpaceUiObject*, Opaque, Opaque, Opaque,
                                      Opaque);

template <typename Target>
Opaque invoke_slot(SpaceUiObject* object, std::size_t slot) {
  const Target target = reinterpret_cast<Target>(object->vtable->slots[slot]);
  return target(object);
}

template <typename Target>
Opaque invoke_slot(SpaceUiObject* object, std::size_t slot, Opaque first) {
  const Target target = reinterpret_cast<Target>(object->vtable->slots[slot]);
  return target(object, first);
}

template <typename Target>
Opaque invoke_slot(SpaceUiObject* object, std::size_t slot, Opaque first,
                   Opaque second) {
  const Target target = reinterpret_cast<Target>(object->vtable->slots[slot]);
  return target(object, first, second);
}

template <typename Target>
Opaque invoke_slot(SpaceUiObject* object, std::size_t slot, Opaque first,
                   Opaque second, Opaque third, Opaque fourth) {
  const Target target = reinterpret_cast<Target>(object->vtable->slots[slot]);
  return target(object, first, second, third, fourth);
}

Opaque call_slot(SpaceUiObject* object, std::size_t slot) {
  return invoke_slot<Slot0>(object, slot);
}

Opaque call_slot(SpaceUiObject* object, std::size_t slot, Opaque first) {
  return invoke_slot<Slot1>(object, slot, first);
}

Opaque call_slot(SpaceUiObject* object, std::size_t slot, Opaque first,
                 Opaque second) {
  return invoke_slot<Slot2>(object, slot, first, second);
}

Opaque call_slot(SpaceUiObject* object, std::size_t slot, Opaque first,
                 Opaque second, Opaque third, Opaque fourth) {
  return invoke_slot<Slot4>(object, slot, first, second, third, fourth);
}

void replace_slot0_slot4(SpaceUiObject** field, SpaceUiObject* next) {
  SpaceUiObject* previous = *field;
  if (previous == next) {
    return;
  }
  if (next != nullptr) {
    call_slot(next, 0);
  }
  *field = next;
  if (previous != nullptr) {
    call_slot(previous, 1);
  }
}

void store_state_word(SpaceUiState* state, std::size_t offset, Opaque value) {
  store_word(state->bytes.data(), offset, value);
}

Opaque load_state_word(SpaceUiState* state, std::size_t offset) {
  return load_word<Opaque>(state->bytes.data(), offset);
}

SpaceUiObject* load_state_object(SpaceUiState* state, std::size_t offset) {
  return object_from(load_state_word(state, offset));
}

void store_state_object(SpaceUiState* state, std::size_t offset,
                        SpaceUiObject* object) {
  store_state_word(state, offset, object_word(object));
}

Opaque context_word(SpaceUiState* state) {
  return load_state_word(state, 0x0c);
}

int rounded_dimension(float value) {
  return static_cast<int>(std::floor(value + 0.5f));
}

void replace_state_object(SpaceUiState* state, std::size_t offset,
                          SpaceUiObject* next) {
  SpaceUiObject* previous = load_state_object(state, offset);
  if (previous == next) {
    return;
  }
  if (next != nullptr) {
    call_slot(next, 0);
  }
  store_state_object(state, offset, next);
  if (previous != nullptr) {
    call_slot(previous, 1);
  }
}

void replace_state_slot4_slot8(SpaceUiState* state, std::size_t offset,
                               SpaceUiObject* next) {
  SpaceUiObject* previous = load_state_object(state, offset);
  if (previous == next) {
    return;
  }
  if (next != nullptr) {
    call_slot(next, 1);
  }
  store_state_object(state, offset, next);
  if (previous != nullptr) {
    call_slot(previous, 2);
  }
}

void replace_state_refcounted(SpaceUiState* state, std::size_t offset,
                              SpaceUiObject* next) {
  SpaceUiObject* previous = load_state_object(state, offset);
  if (previous == next) {
    return;
  }
  if (next != nullptr) {
    ++next->refcount;
  }
  store_state_object(state, offset, next);
  if (previous != nullptr) {
    --previous->refcount;
    if (previous->refcount == 0) {
      previous->refcount = 1;
      call_slot(previous, 0, 1);
    }
  }
}

void clear_state_slot4(SpaceUiState* state, std::size_t offset) {
  SpaceUiObject* previous = load_state_object(state, offset);
  store_state_object(state, offset, nullptr);
  if (previous != nullptr) {
    call_slot(previous, 1);
  }
}

void clear_state_slot8(SpaceUiState* state, std::size_t offset) {
  SpaceUiObject* previous = load_state_object(state, offset);
  store_state_object(state, offset, nullptr);
  if (previous != nullptr) {
    call_slot(previous, 2);
  }
}

}

namespace unresolved_contracts {

extern "C" std::uint8_t pkg18_re_004eb930(const Opaque* installed_key,
                                          const Opaque* requested_key);
extern "C" void __thiscall pkg18_re_00834e30(TextZoomOwner* owner);
extern "C" Opaque pkg18_re_009512c0();
extern "C" Opaque pkg18_re_009512d0(Opaque size, Opaque alignment, Opaque name,
                                    Opaque context);
extern "C" Opaque __thiscall pkg18_re_00989000(Opaque owner);
extern "C" Opaque pkg18_re_0080fee0(Opaque id);
extern "C" Opaque __thiscall pkg18_re_00810620(Opaque object);
extern "C" Opaque __thiscall pkg18_re_00b5f950(Opaque owner, Opaque object);
extern "C" std::uint8_t __thiscall pkg18_re_008120d0(Opaque owner,
                                                     Opaque resource,
                                                     Opaque one, Opaque id);
extern "C" void __thiscall pkg18_re_008121b0(Opaque owner, Opaque object,
                                             Opaque one, Opaque id);
extern "C" Opaque __thiscall pkg18_re_008105b0(Opaque owner, Opaque id,
                                               Opaque flag);
extern "C" Opaque pkg18_re_00f473a0(Opaque size, Opaque domain, Opaque value_3,
                                    Opaque value_4, Opaque allocator,
                                    Opaque line);
extern "C" void pkg18_re_00806320(Opaque resource_key, Opaque key, Opaque name,
                                  SpaceUiObject** output, Opaque flag,
                                  Opaque minus_one, Opaque minus_one_again);
extern "C" Opaque __thiscall pkg18_re_00e03ab0(Opaque allocation);
extern "C" Opaque __thiscall pkg18_re_01066880(Opaque allocation);
extern "C" Opaque __thiscall pkg18_re_00810000(Opaque allocation);
extern "C" void __thiscall pkg18_re_00812160(Opaque owner, Opaque name,
                                             Opaque type, Opaque one,
                                             Opaque id);
extern "C" void __thiscall pkg18_re_00810590(Opaque owner, Opaque flag);
extern "C" Opaque __thiscall pkg18_re_00e2c920(Opaque allocation);
extern "C" Opaque __thiscall pkg18_re_00e36480(Opaque allocation);
extern "C" void __thiscall pkg18_re_00e36b30(Opaque owner, Opaque data_0,
                                             Opaque data_1, Opaque data_2,
                                             Opaque code, Opaque value_0,
                                             Opaque value_1);
extern "C" Opaque pkg18_re_00e012b0(Opaque id);
extern "C" Opaque __thiscall pkg18_re_00e0fc90(Opaque factory, Opaque width,
                                               Opaque height, Opaque colors,
                                               Opaque context, Opaque zero_0,
                                               Opaque zero_1);
extern "C" void __thiscall pkg18_re_00e0c1f0(Opaque colors);
extern "C" Opaque __thiscall pkg18_re_0093b6c0(Opaque owner);
extern "C" Opaque __thiscall pkg18_re_00e28a10(Opaque allocation,
                                               Opaque resource_key,
                                               Opaque resource);
extern "C" void __thiscall pkg18_re_00e29c80(Opaque owner);
extern "C" Opaque pkg18_re_00b3d230();
extern "C" Opaque pkg18_re_0067dcc0();
extern "C" Opaque __thiscall pkg18_re_0083c800(Opaque allocation);
extern "C" Opaque pkg18_re_0067de20();
extern "C" void __thiscall pkg18_re_01068f70(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_01070290(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_01071a00(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_0106a280(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_010666b0(SpaceUiState* state);
extern "C" Opaque __thiscall pkg18_re_01046fc0(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_01048ce0(Opaque object);
extern "C" void __thiscall pkg18_re_0106a4e0(SpaceUiState* state);
extern "C" Opaque pkg18_re_01021300();
extern "C" Opaque __thiscall pkg18_re_00c326b0(Opaque object);
extern "C" Opaque pkg18_re_01002bd0();
extern "C" void pkg18_re_00807bb0(Opaque object, Opaque resource, Opaque id);
extern "C" Opaque __thiscall pkg18_re_00e25710(Opaque allocation);
extern "C" void __thiscall pkg18_re_006b5060(Opaque context);
extern "C" void __thiscall pkg18_re_006b54b0(Opaque context, Opaque first,
                                             Opaque second, Opaque third);
extern "C" Opaque __thiscall pkg18_re_006b55c0(Opaque context);
extern "C" Opaque pkg18_re_00b3d300();
extern "C" Opaque __thiscall pkg18_re_00b21340(Opaque owner, Opaque first,
                                               Opaque second, Opaque third,
                                               Opaque fourth, Opaque fifth);
extern "C" void __thiscall pkg18_re_0106b500(SpaceUiState* state,
                                             Opaque object);
extern "C" void __thiscall pkg18_re_01072680(SpaceUiState* state);
extern "C" void __thiscall pkg18_re_006b5240(Opaque context);
extern "C" void pkg18_re_00806de0(Opaque object, Opaque value);
extern "C" void __thiscall pkg18_re_0106e020(SpaceUiState* state);
extern "C" Opaque __thiscall pkg18_re_00e31050(Opaque allocation);
extern "C" void __thiscall pkg18_re_00e2f370(Opaque owner);
extern "C" std::uint8_t pkg18_re_00685520(Opaque mode);
extern "C" Opaque __thiscall pkg18_re_00fe75d0(Opaque allocation);
extern "C" Opaque pkg18_re_table_word_0149c158(Opaque offset);
extern "C" Opaque pkg18_re_table_word_0149c418(Opaque offset);

extern "C" Opaque pkg18_re_global_016e2234;
}

bool PKG18_THISCALL pkg18_text_zoom_rebind_00834fa0(
    TextZoomOwner* owner, SpaceUiObject* source, SpaceUiObject* target,
    Opaque mode, Opaque state, Opaque resource_key_0, Opaque resource_key_1,
    Opaque resource_key_2) {
  if (source == nullptr) {
    return false;
  }

  SpaceUiObject* source_parent = object_from(call_slot(source, 0x10 / 4));
  SpaceUiObject* selected = object_from(call_slot(source_parent, 0x10 / 4));
  if (call_slot(selected, 0x30 / 4) == 0) {
    return false;
  }

  const bool same_source = load_object(owner->bytes.data(), 0x68) == source;
  const bool default_keys = resource_key_0 == kDefaultResource0 &&
                            resource_key_1 == kDefaultResource1 &&
                            resource_key_2 == kDefaultResource2;
  if (same_source && !default_keys) {
    if (unresolved_contracts::pkg18_re_004eb930(
            reinterpret_cast<const Opaque*>(owner->bytes.data() + 0x48),
            &resource_key_0) != 0 &&
        load_object(owner->bytes.data(), 0x6c) == target) {
      return true;
    }
  }

  unresolved_contracts::pkg18_re_00834e30(owner);

  SpaceUiObject** source_field =
      reinterpret_cast<SpaceUiObject**>(owner->bytes.data() + 0x68);
  replace_slot0_slot4(source_field, source);
  SpaceUiObject* source_view =
      object_from(call_slot(load_object(owner->bytes.data(), 0x68), 0x10 / 4));
  store_word(owner->bytes.data(), 0x74,
             static_cast<std::uint32_t>(call_slot(source_view, 0x30 / 4)));

  const Opaque factory_context = unresolved_contracts::pkg18_re_009512c0();
  const Opaque factory = unresolved_contracts::pkg18_re_009512d0(
      0x834, 4, 0x014007f8u, factory_context);
  SpaceUiObject* created = nullptr;
  if (factory != 0) {
    const Opaque owner_object =
        unresolved_contracts::pkg18_re_00989000(factory);
    if (owner_object != 0) {
      created = object_from(owner_object + 0x20c);
    }
  }

  SpaceUiObject** zoom_field =
      reinterpret_cast<SpaceUiObject**>(owner->bytes.data() + 0x64);
  replace_slot0_slot4(zoom_field, created);
  SpaceUiObject* installed_zoom = load_object(owner->bytes.data(), 0x64);
  SpaceUiObject* zoom_view =
      installed_zoom == nullptr
          ? nullptr
          : object_from(call_slot(installed_zoom, 0x10 / 4));

  SpaceUiObject** target_field =
      reinterpret_cast<SpaceUiObject**>(owner->bytes.data() + 0x6c);
  replace_slot0_slot4(target_field, target);
  if (*target_field == nullptr) {
    const Opaque error = unresolved_contracts::pkg18_re_0080fee0(0x5b598f6u);
    const Opaque error_object = unresolved_contracts::pkg18_re_00810620(error);
    unresolved_contracts::pkg18_re_00b5f950(object_word(target_field),
                                            error_object);
  }
  SpaceUiObject* installed_target = *target_field;
  if (installed_target != nullptr && zoom_view != nullptr) {
    call_slot(installed_target, 0xd8 / 4, object_word(zoom_view));
  }
  if (zoom_view != nullptr) {
    call_slot(zoom_view, 0x7c / 4, 1, 0);
    call_slot(zoom_view, 0x7c / 4, 0x10, 1);
  }
  SpaceUiObject* prior = load_object(owner->bytes.data(), 0x70);
  if (prior != nullptr) {
    call_slot(prior, 0x108 / 4, load_word<Opaque>(owner->bytes.data(), 0x0c));
  }
  replace_slot0_slot4(
      reinterpret_cast<SpaceUiObject**>(owner->bytes.data() + 0x70),
      object_from(mode));
  store_word(owner->bytes.data(), 0x54, state);
  if (load_object(owner->bytes.data(), 0x70) != nullptr) {
    call_slot(load_object(owner->bytes.data(), 0x70), 0x104 / 4,
              load_word<Opaque>(owner->bytes.data(), 0x0c));
  }

  Opaque normalized0 = resource_key_0;
  Opaque normalized1 = resource_key_1;
  Opaque normalized2 = resource_key_2;
  if (default_keys) {
    normalized0 = kAlternateResource0;
    normalized1 = kAlternateResource1;
    normalized2 = kAlternateResource2;
  }
  Opaque normalized_keys[3]{normalized0, normalized1, normalized2};
  const bool key_lookup =
      unresolved_contracts::pkg18_re_008120d0(
          reinterpret_cast<Opaque>(owner->bytes.data() + 0x30),
          reinterpret_cast<Opaque>(normalized_keys), 1, 0x5b598fau) != 0;
  if (key_lookup) {
    store_word(owner->bytes.data(), 0x48, normalized0);
    store_word(owner->bytes.data(), 0x4c, normalized1);
  } else {
    store_word(owner->bytes.data(), 0x48, kDefaultResource0);
    store_word(owner->bytes.data(), 0x4c, kDefaultResource1);
    normalized2 = kDefaultResource2;
  }
  store_word(owner->bytes.data(), 0x50, normalized2);
  if (load_word<Opaque>(owner->bytes.data(), 0x48) != kDefaultResource0 ||
      load_word<Opaque>(owner->bytes.data(), 0x4c) != kDefaultResource1 ||
      load_word<Opaque>(owner->bytes.data(), 0x50) != kDefaultResource2) {
    unresolved_contracts::pkg18_re_008121b0(
        reinterpret_cast<Opaque>(owner->bytes.data() + 0x30),
        object_word(installed_target), 1, 0x5b598fau);
  }

  const Opaque resource_object = unresolved_contracts::pkg18_re_008105b0(
      object_word(owner->bytes.data() + 0x30), 0x0626e3b8u, 0);
  if (resource_object != 0) {
    call_slot(object_from(resource_object), 0x7c / 4, 1, 0);
  }
  return true;
}

void PKG18_FASTCALL pkg18_space_ui_initialize_01073700(SpaceUiState* state) {
  using namespace unresolved_contracts;

  SpaceUiObject* saved_image = load_state_object(state, 0x580);
  if (saved_image != nullptr) {
    store_state_object(state, 0x580, nullptr);
    call_slot(saved_image, 1);
  }
  SpaceUiObject* image = nullptr;
  pkg18_re_00806320(0x2f7d0004u, 0x106c7116u, 0x149c538u, &image, 0,
                    static_cast<Opaque>(-1), static_cast<Opaque>(-1));
  store_state_object(state, 0x580, image);

  if (load_state_object(state, 0x224) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x68, kDomain, 0, 0, 0, 0);
    store_state_object(
        state, 0x224,
        allocation == 0 ? nullptr : object_from(pkg18_re_00e03ab0(allocation)));
  }
  if (load_state_object(state, 0x224) != nullptr) {
    call_slot(load_state_object(state, 0x224), 2, 0x15b9294u);
  }

  if (load_state_object(state, 0x22c) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x18, kDomain, 0, 0, 0, 0);
    replace_state_slot4_slot8(
        state, 0x22c,
        allocation == 0 ? nullptr : object_from(pkg18_re_00810000(allocation)));
  }
  SpaceUiObject* rollover = load_state_object(state, 0x22c);
  if (rollover != nullptr) {
    pkg18_re_00812160(object_word(rollover), 0x0149c514u, 0x40464100u, 1,
                      0xe9f70df9u);
    pkg18_re_00810590(object_word(rollover), 0);
  }
  replace_state_object(
      state, 0x598,
      object_from(pkg18_re_008105b0(object_word(rollover), 0x1c22440u, 1)));

  if (load_state_object(state, 0x230) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x18, kDomain, 0, 0, 0, 0);
    replace_state_slot4_slot8(
        state, 0x230,
        allocation == 0 ? nullptr : object_from(pkg18_re_00810000(allocation)));
  }
  SpaceUiObject* tooltip = load_state_object(state, 0x230);
  if (tooltip != nullptr) {
    pkg18_re_00812160(object_word(tooltip), 0x0149c4f0u, 0x40464100u, 1,
                      0xe9f70df9u);
    pkg18_re_00810590(object_word(tooltip), 0);
  }
  replace_state_object(
      state, 0x59c,
      object_from(pkg18_re_008105b0(object_word(tooltip), 0x1c22500u, 1)));

  const Opaque cursor_allocation =
      pkg18_re_00f473a0(0x100, 0x01481c18u, 0, 0, 0, 0);
  replace_state_object(state, 0x5a4,
                       cursor_allocation == 0
                           ? nullptr
                           : object_from(pkg18_re_00e2c920(cursor_allocation)));

  if (load_state_object(state, 0x234) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x18, kDomain, 0, 0, 0, 0);
    replace_state_slot4_slot8(
        state, 0x234,
        allocation == 0 ? nullptr : object_from(pkg18_re_00810000(allocation)));
  }
  SpaceUiObject* planet_tooltip = load_state_object(state, 0x234);
  if (planet_tooltip != nullptr) {
    pkg18_re_00812160(object_word(planet_tooltip), 0x0149c4c8u, 0x40464100u, 1,
                      0xe9f70df9u);
    pkg18_re_00810590(object_word(planet_tooltip), 0);
  }
  replace_state_object(state, 0x5a0,
                       object_from(pkg18_re_008105b0(
                           object_word(planet_tooltip), 0x1c23500u, 1)));
  store_state_word(state, 0x2f8, static_cast<Opaque>(-1));

  if (load_state_object(state, 0x5a8) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x60, 0x0149c4b4u, 0, 0, 0, 0);
    SpaceUiObject* timed =
        allocation == 0 ? nullptr : object_from(pkg18_re_00e36480(allocation));
    replace_state_refcounted(state, 0x5a8, timed);
    if (load_state_object(state, 0x5a8) != nullptr) {
      pkg18_re_00e36b30(object_word(load_state_object(state, 0x5a8)),
                        0x015b92a0u, 0x015b92a4u, 0x015b92a8u, 0x711bb33cu, 200,
                        250);
    }
  }

  if (load_state_object(state, 0x31c) == nullptr) {
    SpaceUiObject* minimap_source =
        object_from(pkg18_re_00e012b0(kMinimapResource));
    if (minimap_source != nullptr) {
      const Opaque bounds = call_slot(minimap_source, 0x38 / 4);
      const float* rectangle = reinterpret_cast<const float*>(bounds);
      const int width = rounded_dimension(rectangle[2] - rectangle[0]);
      const int height = rounded_dimension(rectangle[3] - rectangle[1]);
      const Opaque factory_context = pkg18_re_009512c0();
      const Opaque factory =
          pkg18_re_009512d0(0x9a8, 8, 0x0149c4a4u, factory_context);
      SpaceUiObject* minimap = nullptr;
      if (factory != 0) {
        Opaque colors[4]{0, 0, kOneBits, kNegativeOneBits};
        Opaque context[2]{};
        minimap = object_from(pkg18_re_00e0fc90(
            factory, static_cast<Opaque>(width), static_cast<Opaque>(height),
            reinterpret_cast<Opaque>(colors), reinterpret_cast<Opaque>(context),
            0, 0));
      }
      replace_state_object(state, 0x31c, minimap);
      const Opaque minimap_colors[3]{0, kOneBits, 0};
      pkg18_re_00e0c1f0(reinterpret_cast<Opaque>(minimap_colors));
      SpaceUiObject* installed = load_state_object(state, 0x31c);
      if (installed != nullptr) {
        store_word(installed, 0x344, 0u);
        store_word(installed, 0x348, 0u);
        store_word(installed, 0x34c, 0x3f800000u);
      }
      call_slot(minimap_source, 0xd8 / 4,
                installed == nullptr ? 0 : object_word(installed) + 4);
    }
  }

  const Opaque space_ui_allocation =
      pkg18_re_00f473a0(0x38, 0x0149c490u, 0, 0, 0, 0);
  SpaceUiObject* space_ui = nullptr;
  if (space_ui_allocation != 0) {
    const Opaque resource =
        pkg18_re_0093b6c0(object_word(load_state_object(state, 0x224)));
    space_ui = object_from(
        pkg18_re_00e28a10(space_ui_allocation, 0x149c47cu, resource));
  }
  replace_state_refcounted(state, 0x228, space_ui);
  if (load_state_object(state, 0x228) != nullptr) {
    pkg18_re_00e29c80(object_word(load_state_object(state, 0x228)));
  }

  SpaceUiObject* default_link =
      object_from(pkg18_re_00e012b0(static_cast<Opaque>(-1)));
  if (default_link != nullptr) {
    call_slot(default_link, 0);
    call_slot(default_link, 0x104 / 4, object_word(state));
  }
  const Opaque links[] = {0x052339c0u, 0x052339a8u, 0x05233980u, 0xb2001000u,
                          0x036c0957u};
  for (Opaque id : links) {
    SpaceUiObject* link = object_from(pkg18_re_00e012b0(id));
    if (link != nullptr) {
      call_slot(link, 0x104 / 4, object_word(state));
    }
  }

  if (pkg18_re_global_016e2234 == 0) {
    const Opaque allocation = pkg18_re_00f473a0(0x10, kDomain, 0, 0, 0, 0);
    pkg18_re_global_016e2234 =
        allocation == 0 ? 0 : pkg18_re_01066880(allocation);
    if (pkg18_re_global_016e2234 != 0) {
      call_slot(object_from(pkg18_re_global_016e2234), 1);
    }
  }
  SpaceUiObject* link_manager = object_from(pkg18_re_00b3d230());
  if (link_manager != nullptr) {
    call_slot(link_manager, 0x38 / 4, pkg18_re_global_016e2234, 1);
  }

  const Opaque first_app = pkg18_re_0067dcc0();
  if (first_app != 0) {
    const Opaque app_context = context_word(state);
    const Opaque app_system = pkg18_re_0067dcc0();
    store_state_word(state, 0x56c, app_system);
    store_state_word(state, 0x570, app_context);
    store_state_word(state, 0x574, 0x149c418u);
    store_state_word(state, 0x578, 0x19u);
    store_state_word(state, 0x57c, 0);
    if (app_system != 0 && app_context != 0) {
      for (std::uint32_t index = 0; index < 25; ++index) {
        const Opaque entry = pkg18_re_table_word_0149c418(index * 4);
        call_slot(object_from(app_system), 0x24 / 4, entry, app_context);
      }
    }
  }

  const Opaque flash_allocation = pkg18_re_00f473a0(0x10, kDomain, 0, 0, 0, 0);
  SpaceUiObject* flash = nullptr;
  if (flash_allocation != 0) {
    flash = object_from(pkg18_re_0083c800(flash_allocation));
    flash->vtable = reinterpret_cast<SpaceUiVtable*>(0x149c1d8u);
  }
  (void)flash;
  pkg18_re_0067de20();
  pkg18_re_01068f70(state);
  pkg18_re_01070290(state);
  pkg18_re_01071a00(state);
  pkg18_re_0106a280(state);
  pkg18_re_010666b0(state);
  const Opaque lighting = pkg18_re_01046fc0(state);
  pkg18_re_01048ce0(lighting);
  pkg18_re_0106a4e0(state);
  const Opaque space_service = pkg18_re_01021300();
  const Opaque service_state = pkg18_re_00c326b0(space_service);
  if (service_state != 0) {
    const Opaque service_words[] = {
        load_word<Opaque>(reinterpret_cast<const void*>(service_state), 0),
        load_word<Opaque>(reinterpret_cast<const void*>(service_state), 4),
        load_word<Opaque>(reinterpret_cast<const void*>(service_state), 8)};
    (void)service_words;
  }
  const Opaque mode_state = pkg18_re_01002bd0();
  const Opaque mode_context =
      mode_state == 0
          ? 0
          : load_word<Opaque>(reinterpret_cast<const void*>(mode_state), 0x14);
  const Opaque posse_resource =
      mode_context == 0 ? 0 : pkg18_re_0093b6c0(mode_context + 0x224);
  const Opaque posse_object = pkg18_re_008105b0(posse_resource, 0xb0b00000u, 1);
  pkg18_re_00807bb0(posse_object, 0x2f7d0004u, static_cast<Opaque>(-1));
  const Opaque posse_context = pkg18_re_009512c0();
  const Opaque posse_factory =
      pkg18_re_009512d0(0x20c, 4, 0x0149c408u, posse_context);
  replace_state_object(state, 0x5c4,
                       posse_factory == 0
                           ? nullptr
                           : object_from(pkg18_re_00e25710(posse_factory)));
  SpaceUiObject* posse = load_state_object(state, 0x5c4);
  if (posse != nullptr) {
    const bool initialized =
        call_slot(posse, 0x80 / 4, 0x01476aa4u, 0x40464100u) != 0;
    if (!initialized) {
      clear_state_slot4(state, 0x5c4);
    } else {
      call_slot(posse, 0x90 / 4, 0x41200000u, 0x437a0000u, 0, 0);
      std::array<unsigned char, 0x20> link_context{};
      const Opaque link_context_word =
          reinterpret_cast<Opaque>(link_context.data());
      pkg18_re_006b5060(link_context_word);
      pkg18_re_006b54b0(link_context_word + 0x0c, 0x2db6dad3u, 0x5baafc0u, 0);
      const Opaque posse_link = pkg18_re_006b55c0(link_context_word);
      call_slot(posse, 0xb8 / 4, posse_link);
      const Opaque mode_owner = pkg18_re_00b3d300();
      const Opaque mode_list =
          pkg18_re_00b21340(mode_owner, 0x00cd7d10u, 0x00d3d420u, 0x00ad48b0u,
                            0x00b1e500u, 0x018ebadcu);
      if (mode_list != 0) {
        const Opaque begin =
            load_word<Opaque>(reinterpret_cast<const void*>(mode_list), 4);
        const Opaque end =
            load_word<Opaque>(reinterpret_cast<const void*>(mode_list), 8);
        for (Opaque cursor = begin; cursor != end; cursor += 4) {
          SpaceUiObject* candidate = object_from(
              load_word<Opaque>(reinterpret_cast<const void*>(cursor), 0));
          if (candidate != nullptr &&
              load_word<std::uint32_t>(candidate, 0x714) == 3) {
            pkg18_re_0106b500(state, object_word(candidate));
          }
        }
      }
      pkg18_re_01072680(state);
      call_slot(posse, 0xc0 / 4, 0);
      if (posse != nullptr && (load_word<std::uint32_t>(posse, 0xa8) -
                               load_word<std::uint32_t>(posse, 0xa4)) &
                                  0xfffffff8u) {
        call_slot(posse, 0xc0 / 4, 1);
      }
      pkg18_re_006b5240(link_context_word);
    }
  }

  for (Opaque offset = 0; offset < 0x14; offset += 4) {
    SpaceUiObject* object =
        object_from(pkg18_re_00e012b0(pkg18_re_table_word_0149c158(offset)));
    if (object != nullptr) {
      SpaceUiObject* child =
          object_from(call_slot(object, 0x0c / 4, 0x0106f146u));
      SpaceUiObject* child_base = reinterpret_cast<SpaceUiObject*>(
          reinterpret_cast<unsigned char*>(child) + 0x20c);
      call_slot(child_base, 0x14 / 4, 0);
      call_slot(object, 0x7c / 4, 1, 0);
    }
  }
  const Opaque late_link_ids[] = {0x06567050u, 0x06567051u};
  const Opaque late_link_receivers[] = {
      reinterpret_cast<Opaque>(state->bytes.data() + 0x10c),
      reinterpret_cast<Opaque>(state->bytes.data() + 0x120)};
  for (std::size_t index = 0; index < 2; ++index) {
    SpaceUiObject* object =
        object_from(pkg18_re_00e012b0(late_link_ids[index]));
    if (object != nullptr) {
      const Opaque value = pkg18_re_006b55c0(late_link_receivers[index]);
      pkg18_re_00806de0(object_word(object), value);
    }
  }
  pkg18_re_0106e020(state);
  store_word(state->bytes.data(), 0x5d5, std::uint8_t{1});

  if (load_state_object(state, 0x61c) == nullptr) {
    const Opaque allocation = pkg18_re_00f473a0(0x58, 0x014801e0u, 0, 0, 0, 0);
    replace_state_slot4_slot8(
        state, 0x61c,
        allocation == 0 ? nullptr : object_from(pkg18_re_00e31050(allocation)));
  }
  if (load_state_object(state, 0x61c) != nullptr) {
    pkg18_re_00e2f370(object_word(load_state_object(state, 0x61c)));
  }

  if (pkg18_re_00685520(2) == 0) {
    clear_state_slot4(state, 0x694);
    clear_state_slot8(state, 0x258);
  } else {
    const Opaque simulator_allocation =
        pkg18_re_00f473a0(0x18, 0x013f09b4u, 0, 0, 0, 0);
    replace_state_slot4_slot8(
        state, 0x258,
        simulator_allocation == 0
            ? nullptr
            : object_from(pkg18_re_00810000(simulator_allocation)));
    const Opaque local_keys[3]{0x09831b38fu, 0x0510a95bu, 0x40464100u};
    pkg18_re_008120d0(object_word(load_state_object(state, 0x258)),
                      reinterpret_cast<Opaque>(local_keys), 1, 0x5b598fau);
    pkg18_re_00810590(object_word(load_state_object(state, 0x258)), 1);
    store_state_word(state, 0x690, 0);
    const Opaque service_link = pkg18_re_008105b0(
        object_word(load_state_object(state, 0x258)), 0x07cf8048u, 1);
    if (service_link != 0) {
      const Opaque service_value =
          call_slot(object_from(service_link), 0x38 / 4);
      store_word(
          state->bytes.data(), 0x690,
          load_word<float>(reinterpret_cast<const void*>(service_value), 0x0c));
    }
    const Opaque simulator_ui_allocation =
        pkg18_re_00f473a0(0xc0, 0x013f09b4u, 0, 0, 0, 0);
    replace_state_object(
        state, 0x694,
        simulator_ui_allocation == 0
            ? nullptr
            : object_from(pkg18_re_00fe75d0(simulator_ui_allocation)));
    const Opaque simulator_links[] = {0x075dd108u, 0x075dd100u, 0x05e4f770u,
                                      0x0770996au, 0x05e4f788u, 0x07ce3cb0u,
                                      0x07ce1750u, 0x07bb9fc8u, 0x0755e358u};
    for (Opaque id : simulator_links) {
      SpaceUiObject* link = object_from(pkg18_re_008105b0(
          object_word(load_state_object(state, 0x258)), id, 1));
      if (link != nullptr) {
        call_slot(link, 0x104 / 4,
                  object_word(load_state_object(state, 0x694)));
      }
    }
  }
  if (saved_image != nullptr) {
    call_slot(saved_image, 1);
  }
}

}
