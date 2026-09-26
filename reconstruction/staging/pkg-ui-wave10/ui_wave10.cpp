#include "ui_wave10.hpp"

#include <cstring>

namespace openspore::reconstruction::pkg_ui_wave10 {

Opaque pkg_ui_wave10_alloc_tag_013eb430 = 0x013eb430u;
Opaque pkg_ui_wave10_vtable_013eb938 = 0x013eb938u;
Opaque pkg_ui_wave10_vtable_013ec458 = 0x013ec458u;
Opaque pkg_ui_wave10_vtable_013f7b54 = 0x013f7b54u;
Opaque pkg_ui_wave10_vtable_013fe718 = 0x013fe718u;
Opaque pkg_ui_wave10_vtable_013fe728 = 0x013fe728u;
Opaque pkg_ui_wave10_vtable_0149bad8 = 0x0149bad8u;

namespace unresolved_contracts {

extern "C" Opaque* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_alloc_00f473a0(Opaque size, Opaque type_tag, Opaque arg_0c,
                             Opaque arg_10, Opaque arg_14, Opaque arg_18);
extern "C" void PKG_UI_WAVE10_CDECL
pkg_ui_wave10_free_00f47380(Opaque* pointer);
extern "C" void PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_service_init_00810000(OpaqueService24* service);
extern "C" void PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_service_destroy_00811fe0(OpaqueService24* service);
extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_name_panel_entity_005bfcc0(
    OpaqueNamePanel* object, Opaque entity);
extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_set_property_008120d0(
    OpaqueService24* service, const OpaquePropertyTriple* value, Opaque count,
    Opaque key);
extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_commit_008121b0(
    OpaqueService24* service, Opaque value, Opaque count, Opaque key);
extern "C" Opaque PKG_UI_WAVE10_THISCALL pkg_ui_wave10_lookup_008105b0(
    OpaqueService24* service, Opaque key, Opaque flag);
extern "C" OpaqueService* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_service_fetch_0067dcc0();
extern "C" OpaqueService* PKG_UI_WAVE10_CDECL
pkg_ui_wave10_service_provider_0067de30();
extern "C" Opaque PKG_UI_WAVE10_CDECL pkg_ui_wave10_string_hash_00932f30(
    const std::uint16_t* text, Opaque seed, int mode);
extern "C" bool PKG_UI_WAVE10_CDECL pkg_ui_wave10_get_array_006a0bc0(
    OpaqueSlot* list, Opaque property_id, Opaque* count, Opaque** entries);
extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_vector_erase_00d018d0(
    OpaqueSettingsVector* vector, OpaqueSettingsPair* first,
    OpaqueSettingsPair* last);
extern "C" void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_vector_insert_00601b40(
    OpaqueSettingsVector* vector, OpaqueSettingsPair* position,
    const OpaqueSettingsPair* value);

extern "C" OpaqueService* pkg_ui_wave10_g_provider_015fd8a8;
extern "C" Opaque pkg_ui_wave10_g_allocator_013cc4a8;

}

namespace {

template <typename To>
To slot_from(Opaque word) {
  static_assert(sizeof(To) == sizeof(Opaque), "UI wave 10 slot width mismatch");
  To result{};
  std::memcpy(&result, &word, sizeof(result));
  return result;
}

Opaque read_word(const Opaque* base, Opaque byte_offset) {
  Opaque result = 0;
  std::memcpy(&result,
              reinterpret_cast<const std::uint8_t*>(base) + byte_offset,
              sizeof(result));
  return result;
}

void release_handle(OpaqueSlot* handle) {
  if (handle == nullptr) {
    return;
  }
  const auto release =
      slot_from<SlotReleaseSlot>(handle->vtable_00->slots_00[1]);
  release(handle);
}

}

void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_005bfd40(OpaqueNamePanel* object,
                                                   Opaque arg_20, Opaque arg_24,
                                                   Opaque arg_28, Opaque arg_2c,
                                                   Opaque arg_30) {
  Opaque* fresh_raw = unresolved_contracts::pkg_ui_wave10_alloc_00f473a0(
      0x18u, pkg_ui_wave10_alloc_tag_013eb430, 0u, 0u, 0u, 0u);
  OpaqueService24* fresh = nullptr;
  if (fresh_raw != nullptr) {
    fresh = reinterpret_cast<OpaqueService24*>(fresh_raw);
    unresolved_contracts::pkg_ui_wave10_service_init_00810000(fresh);
  }

  OpaqueService24* previous_18 = object->slot_18;
  if (fresh != previous_18) {
    if (fresh != nullptr) {
      const auto detach =
          slot_from<ServiceSlot04>(fresh->vtable_00->slots_00[1]);
      detach(fresh);
    }
    object->slot_18 = fresh;
    if (previous_18 != nullptr) {
      const auto attach =
          slot_from<ServiceSlot08>(previous_18->vtable_00->slots_00[2]);
      attach(previous_18);
    }
  }

  OpaquePropertyTriple triple;
  triple.word_00 = arg_28;
  triple.word_04 = 0x510a95bu;
  triple.word_08 = 0x40464100u;
  unresolved_contracts::pkg_ui_wave10_set_property_008120d0(
      object->slot_18, &triple, 1u, 0x5b598fau);
  unresolved_contracts::pkg_ui_wave10_commit_008121b0(object->slot_18, arg_24,
                                                      1u, 0x5b598fau);

  const std::uint8_t mode = static_cast<std::uint8_t>(arg_2c);
  object->byte_11 = mode;
  object->field_20 = mode != 0u ? arg_30 : 0u;
  object->byte_10 = 0u;
  object->field_34 = arg_24;

  unresolved_contracts::pkg_ui_wave10_name_panel_entity_005bfcc0(object,
                                                                 arg_20);

  auto* subobject = reinterpret_cast<OpaqueNamePanel*>(
      reinterpret_cast<std::uintptr_t>(object) + 0x04u);
  auto register_id = [subobject](Opaque id) {
    OpaqueService* provider =
        unresolved_contracts::pkg_ui_wave10_service_fetch_0067dcc0();
    const auto register_slot =
        slot_from<ServiceRegisterSlot>(provider->vtable_00->slot_20);
    register_slot(provider, subobject, id);
  };
  register_id(0x7aa519dcu);
  register_id(0x14418c3fu);
  register_id(0x01ee1001u);

  if (unresolved_contracts::pkg_ui_wave10_lookup_008105b0(
          object->slot_18, 0x5415e48u, 1u) != 0u) {
    register_id(0x073127e6u);
  }

  auto* player = slot_from<OpaqueService*>(
      unresolved_contracts::pkg_ui_wave10_lookup_008105b0(object->slot_18,
                                                          0x272eb68eu, 1u));
  if (player != nullptr) {
    const auto enable =
        slot_from<ServiceEnableSlot>(player->vtable_00->slot_7c);
    enable(player, 1u, 1u);
    const auto bind = slot_from<ServiceBindSlot>(player->vtable_00->slot_104);
    bind(player, reinterpret_cast<Opaque>(object));
  }

  if (object->byte_11 == 0u) {
    auto* source_service = slot_from<OpaqueService*>(
        unresolved_contracts::pkg_ui_wave10_lookup_008105b0(object->slot_18,
                                                            0x272eb68eu, 1u));
    auto* target_service = slot_from<OpaqueService*>(
        unresolved_contracts::pkg_ui_wave10_lookup_008105b0(object->slot_18,
                                                            0x56c1e03u, 1u));
    if (source_service != nullptr && target_service != nullptr) {
      const auto acquire_source =
          slot_from<SlotFetchSlot>(source_service->vtable_00->slot_a8);
      const auto acquire_target =
          slot_from<SlotFetchSlot>(target_service->vtable_00->slot_a8);
      OpaqueRegistry* source_registry = acquire_source(source_service);
      OpaqueRegistry* target_registry = acquire_target(target_service);
      OpaqueCarrier* source_carrier = nullptr;
      OpaqueCarrier* target_carrier = nullptr;
      if (source_registry != nullptr) {
        const auto resolve_source =
            slot_from<SlotRegistrySlot>(source_registry->vtable_00->slot_0c);
        source_carrier = resolve_source(source_registry, 0x103c1908u);
      }
      if (target_registry != nullptr) {
        const auto resolve_target =
            slot_from<SlotRegistrySlot>(target_registry->vtable_00->slot_0c);
        target_carrier = resolve_target(target_registry, 0x103c1908u);
      }
      if (source_carrier != nullptr && target_carrier != nullptr) {
        for (Opaque index = 0u; index < 8u; index += 1u) {
          const auto produce =
              slot_from<CarrierSourceSlot>(target_carrier->vtable_00->slot_10);
          const auto consume =
              slot_from<CarrierSinkSlot>(source_carrier->vtable_00->slot_14);
          const Opaque carried = produce(target_carrier, index);
          consume(source_carrier, index, carried);
        }
      }
    }
  }

  auto* binder = slot_from<OpaqueService*>(
      unresolved_contracts::pkg_ui_wave10_lookup_008105b0(object->slot_18,
                                                          0xc7ceb1bdu, 1u));
  if (binder != nullptr) {
    OpaqueBinding* candidate = nullptr;
    Opaque* raw = unresolved_contracts::pkg_ui_wave10_alloc_00f473a0(
        0x0cu, pkg_ui_wave10_alloc_tag_013eb430, 0u, 0u, 0u, 0u);
    if (raw != nullptr) {
      candidate = reinterpret_cast<OpaqueBinding*>(raw);
      candidate->field_08 = 0u;
      candidate->vtable_04 = reinterpret_cast<Opaque*>(
          static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013ec458));
      candidate->vtable_00 = reinterpret_cast<OpaqueBindingVTable*>(
          static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013f7b54));
      candidate->vtable_04 = reinterpret_cast<Opaque*>(
          static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_0149bad8));
    }
    OpaqueBinding* previous_14 = object->slot_14;
    if (candidate != previous_14) {
      if (candidate != nullptr) {
        const auto drop =
            slot_from<BindingSlot00>(candidate->vtable_00->slots_00[0]);
        drop(candidate);
      }
      object->slot_14 = candidate;
      if (previous_14 != nullptr) {
        const auto retire =
            slot_from<BindingSlot04>(previous_14->vtable_00->slots_00[1]);
        retire(previous_14);
      }
    }
    const auto publish =
        slot_from<ServiceBindSlot>(binder->vtable_00->slot_104);
    publish(binder, reinterpret_cast<Opaque>(object->slot_14));
  }
}

void PKG_UI_WAVE10_THISCALL pkg_ui_wave10_00603650(OpaqueSettings* object) {
  OpaqueSlot* handle = nullptr;
  Opaque count = 0u;
  Opaque* entries = nullptr;
  Opaque cursor = 0u;
  Opaque stride = 0u;

  OpaqueSlot* stale = handle;
  if (stale != nullptr) {
    handle = nullptr;
    release_handle(stale);
  }

  OpaqueService* provider =
      unresolved_contracts::pkg_ui_wave10_service_provider_0067de30();
  const auto resolve =
      slot_from<ServiceResolveSlot>(provider->vtable_00->slot_2c);
  resolve(provider, 0xe280c622u, 0u, &handle);

  if (handle != nullptr) {
    const auto read_array =
        unresolved_contracts::pkg_ui_wave10_get_array_006a0bc0;
    count = 0u;
    entries = nullptr;
    if (read_array(handle, 0x9f9c97deu, &count, &entries) &&
        static_cast<int>(count) > 0) {
      unresolved_contracts::pkg_ui_wave10_vector_erase_00d018d0(
          &object->vector_40, object->vector_40.begin_00,
          object->vector_40.end_04);
      if (static_cast<int>(count) > 0) {
        const auto hash_text =
            unresolved_contracts::pkg_ui_wave10_string_hash_00932f30;
        const auto allocate = slot_from<SettingsAllocateSlot>(
            unresolved_contracts::pkg_ui_wave10_g_allocator_013cc4a8);
        for (;;) {
          const Opaque hashed = hash_text(
              reinterpret_cast<const std::uint16_t*>(entries + (stride >> 2)),
              0x811c9dc5u, 1);
          Opaque* buffer = allocate(read_word(entries, stride + 0x10u) + 0x04u,
                                    nullptr, 0x10u);
          OpaqueSettingsPair pair;
          pair.hash = hashed;
          pair.buffer = buffer;
          if (hashed != 0u && buffer != nullptr) {
            OpaqueSettingsPair* end = object->vector_40.end_04;
            if (end >= object->vector_40.cap_08) {
              unresolved_contracts::pkg_ui_wave10_vector_insert_00601b40(
                  &object->vector_40, end, &pair);
            } else {
              object->vector_40.end_04 = end + 1;
              if (end != nullptr) {
                *end = pair;
              }
            }
          }
          cursor += 2u;
          stride += 0x20u;
          if (cursor >= count) {
            break;
          }
        }
      }
    }
  }

  stride = 0u;
  release_handle(handle);
}

OpaqueImageArchive* PKG_UI_WAVE10_THISCALL
pkg_ui_wave10_00635700(OpaqueImageArchive* object, Opaque deleting) {
  object->vtable_00 = reinterpret_cast<Opaque*>(
      static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013fe728));
  object->vtable_04 = reinterpret_cast<Opaque*>(
      static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013fe718));

  OpaqueSlot* late = object->slot_68;
  if (late != nullptr) {
    const auto release =
        slot_from<SlotReleaseSlot>(late->vtable_00->slots_00[1]);
    release(late);
  }
  OpaqueSlot* early = object->slot_64;
  if (early != nullptr) {
    const auto release =
        slot_from<SlotReleaseSlot>(early->vtable_00->slots_00[1]);
    release(early);
  }

  unresolved_contracts::pkg_ui_wave10_service_destroy_00811fe0(
      &object->service_2c);
  unresolved_contracts::pkg_ui_wave10_service_destroy_00811fe0(
      &object->service_14);

  object->vtable_04 = reinterpret_cast<Opaque*>(
      static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013ec458));
  object->vtable_00 = reinterpret_cast<Opaque*>(
      static_cast<std::uintptr_t>(pkg_ui_wave10_vtable_013eb938));

  if ((deleting & 0x01u) != 0u) {
    unresolved_contracts::pkg_ui_wave10_free_00f47380(
        reinterpret_cast<Opaque*>(object));
  }
  return object;
}

}
