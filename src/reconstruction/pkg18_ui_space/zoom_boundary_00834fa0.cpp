#include "zoom_boundary_00834fa0.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg18_ui_space {
namespace {

constexpr Opaque kDefaultResource0 = 0x0164f240u;
constexpr Opaque kDefaultResource1 = 0x0164f244u;
constexpr Opaque kDefaultResource2 = 0x0164f248u;
constexpr Opaque kAlternateResource0 = 0x0164f234u;
constexpr Opaque kAlternateResource1 = 0x0164f238u;
constexpr Opaque kAlternateResource2 = 0x0164f23cu;
constexpr Opaque kFactoryName = 0x014007f8u;
constexpr Opaque kErrorLookupId = 0x05b598f6u;
constexpr Opaque kResourceApplyId = 0x05b598fau;
constexpr Opaque kFinalResourceId = 0x0626e3b8u;

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

Opaque object_word(const void* object) {
  return reinterpret_cast<Opaque>(object);
}

ZoomObject* object_from(Opaque value) {
  return reinterpret_cast<ZoomObject*>(value);
}

ZoomObject* load_object(const ZoomOwner* owner, std::size_t offset) {
  return object_from(load_word<Opaque>(owner->bytes.data(), offset));
}

void store_object(ZoomOwner* owner, std::size_t offset, ZoomObject* object) {
  store_word(owner->bytes.data(), offset, object_word(object));
}

template <typename To, typename From>
To copy_function(From value) {
  static_assert(sizeof(To) == sizeof(From), "function pointer width mismatch");
  To result{};
  std::memcpy(&result, &value, sizeof(result));
  return result;
}

template <typename Function>
Function load_slot(ZoomObject* object, std::size_t offset) {
  return copy_function<Function>(
      object->vtable->slots[offset / sizeof(Opaque)]);
}

template <typename Result, typename... Args>
Result call_slot(ZoomObject* object, std::size_t offset, Args... args) {
  using Function = Result(PKG18_VTABLECALL*)(ZoomObject*, Args...);
  const Function function = load_slot<Function>(object, offset);
  return function(object, args...);
}

void replace_field(ZoomOwner* owner, std::size_t offset, ZoomObject* next) {
  ZoomObject* previous = load_object(owner, offset);
  if (previous == next) {
    return;
  }
  if (next != nullptr) {
    call_slot<Opaque>(next, 0x00);
  }
  store_object(owner, offset, next);
  if (previous != nullptr) {
    call_slot<Opaque>(previous, 0x04);
  }
}

}

namespace unresolved_contracts {

extern "C" std::uint8_t __cdecl pkg18_re_004eb930(const Opaque* installed_key,
                                                  const Opaque* requested_key);
extern "C" void __fastcall pkg18_re_00834e30(Opaque owner);
extern "C" Opaque pkg18_re_009512c0();
extern "C" Opaque __cdecl pkg18_re_009512d0(Opaque size, Opaque alignment,
                                            Opaque name, Opaque context);
extern "C" Opaque __fastcall pkg18_re_00989000(Opaque owner);
extern "C" Opaque pkg18_re_0080fee0();
extern "C" Opaque __fastcall pkg18_re_00810620(Opaque object, Opaque id);
extern "C" Opaque __fastcall pkg18_re_00b5f950(Opaque field, Opaque object);
extern "C" std::uint8_t __fastcall pkg18_re_008120d0(Opaque owner,
                                                     Opaque resource,
                                                     Opaque one, Opaque id);
extern "C" void __fastcall pkg18_re_008121b0(Opaque owner, Opaque target,
                                             Opaque one, Opaque id);
extern "C" Opaque __fastcall pkg18_re_008105b0(Opaque owner, Opaque id,
                                               Opaque flag);

}

bool PKG18_THISCALL pkg18_text_zoom_rebind_00834fa0(
    ZoomOwner* owner, ZoomObject* source, ZoomObject* target, Opaque mode,
    Opaque state, Opaque resource_key_0, Opaque resource_key_1,
    Opaque resource_key_2) {
  using namespace unresolved_contracts;

  if (source == nullptr) {
    return false;
  }

  ZoomObject* source_parent = object_from(call_slot<Opaque>(source, 0x10));
  ZoomObject* selected = object_from(call_slot<Opaque>(source_parent, 0x10));
  if (call_slot<Opaque>(selected, 0x30) == 0) {
    return false;
  }

  const bool same_source = load_object(owner, 0x68) == source;
  const bool default_keys = resource_key_0 == kDefaultResource0 &&
                            resource_key_1 == kDefaultResource1 &&
                            resource_key_2 == kDefaultResource2;
  if (same_source && !default_keys) {
    if (pkg18_re_004eb930(
            reinterpret_cast<const Opaque*>(owner->bytes.data() + 0x48),
            &resource_key_0) != 0 &&
        load_object(owner, 0x6c) == target) {
      return true;
    }
  }

  pkg18_re_00834e30(object_word(owner));

  replace_field(owner, 0x68, source);
  ZoomObject* source_view =
      object_from(call_slot<Opaque>(load_object(owner, 0x68), 0x10));
  store_word(owner->bytes.data(), 0x74, call_slot<Opaque>(source_view, 0x30));

  const Opaque factory_context = pkg18_re_009512c0();
  const Opaque factory =
      pkg18_re_009512d0(0x834u, 4u, kFactoryName, factory_context);
  ZoomObject* created = nullptr;
  if (factory != 0) {
    const Opaque factory_owner = pkg18_re_00989000(factory);
    if (factory_owner != 0) {
      created = object_from(factory_owner + 0x20cu);
    }
  }
  replace_field(owner, 0x64, created);

  ZoomObject* installed_zoom = load_object(owner, 0x64);
  ZoomObject* zoom_view = object_from(call_slot<Opaque>(installed_zoom, 0x10));

  replace_field(owner, 0x6c, target);
  if (load_object(owner, 0x6c) == nullptr) {
    const Opaque error = pkg18_re_0080fee0();
    const Opaque error_object = pkg18_re_00810620(error, kErrorLookupId);
    pkg18_re_00b5f950(object_word(owner->bytes.data() + 0x6c), error_object);
  }

  ZoomObject* installed_target = load_object(owner, 0x6c);
  call_slot<Opaque>(installed_target, 0xd8, object_word(zoom_view));
  call_slot<Opaque>(zoom_view, 0x7c, static_cast<Opaque>(1),
                    static_cast<Opaque>(0));
  call_slot<Opaque>(zoom_view, 0x7c, static_cast<Opaque>(0x10),
                    static_cast<Opaque>(1));

  ZoomObject* prior_mode = load_object(owner, 0x70);
  if (prior_mode != nullptr) {
    call_slot<Opaque>(prior_mode, 0x108,
                      load_word<Opaque>(owner->bytes.data(), 0x0c));
  }
  replace_field(owner, 0x70, object_from(mode));
  store_word(owner->bytes.data(), 0x54, state);
  ZoomObject* installed_mode = load_object(owner, 0x70);
  if (installed_mode != nullptr) {
    call_slot<Opaque>(installed_mode, 0x104,
                      load_word<Opaque>(owner->bytes.data(), 0x0c));
  }

  Opaque normalized_keys[3]{resource_key_0, resource_key_1, resource_key_2};
  if (default_keys) {
    normalized_keys[0] = kAlternateResource0;
    normalized_keys[1] = kAlternateResource1;
    normalized_keys[2] = kAlternateResource2;
  }

  const bool key_lookup =
      pkg18_re_008120d0(object_word(owner->bytes.data() + 0x30),
                        reinterpret_cast<Opaque>(normalized_keys),
                        static_cast<Opaque>(1), kResourceApplyId) != 0;
  if (key_lookup) {
    store_word(owner->bytes.data(), 0x48, normalized_keys[0]);
    store_word(owner->bytes.data(), 0x4c, normalized_keys[1]);
  } else {
    normalized_keys[0] = kDefaultResource0;
    normalized_keys[1] = kDefaultResource1;
    normalized_keys[2] = kDefaultResource2;
    store_word(owner->bytes.data(), 0x48, normalized_keys[0]);
    store_word(owner->bytes.data(), 0x4c, normalized_keys[1]);
  }
  store_word(owner->bytes.data(), 0x50, normalized_keys[2]);

  if (load_word<Opaque>(owner->bytes.data(), 0x48) != kDefaultResource0 ||
      load_word<Opaque>(owner->bytes.data(), 0x4c) != kDefaultResource1 ||
      load_word<Opaque>(owner->bytes.data(), 0x50) != kDefaultResource2) {
    pkg18_re_008121b0(object_word(owner->bytes.data() + 0x30),
                      object_word(installed_target), static_cast<Opaque>(1),
                      kResourceApplyId);
  }

  const Opaque resource_object =
      pkg18_re_008105b0(object_word(owner->bytes.data() + 0x30),
                        kFinalResourceId, static_cast<Opaque>(0));
  if (resource_object != 0) {
    call_slot<Opaque>(object_from(resource_object), 0x7c,
                      static_cast<Opaque>(1), static_cast<Opaque>(0));
  }
  return true;
}

}
