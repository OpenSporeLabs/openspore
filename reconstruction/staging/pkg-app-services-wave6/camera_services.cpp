#include "camera_services.hpp"

#include <cstdint>
#include <cstring>

#if defined(_MSC_VER)
#define PKG_CAM_CDECL __cdecl
#define PKG_CAM_THISCALL __thiscall
#else
#define PKG_CAM_CDECL __attribute__((cdecl))
#define PKG_CAM_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

CameraCommandPorts* g_camera_command_ports = nullptr;

namespace {

OpaqueMessageNode** lookup_message(OpaqueMessageRegistry& registry,
                                  OpaqueWord key) {
  OpaqueMessageNode** slot =
      &registry.buckets_004[key % registry.bucket_count_008];
  OpaqueMessageNode* node = *slot;
  while (node != nullptr) {
    if (node->key == key) {
      break;
    }
    node = node->next;
  }
  return slot;
}

std::size_t command_entry_count(OpaqueCommandCollection& collection) {
  const auto begin = reinterpret_cast<std::uintptr_t>(collection.entries_094);
  const auto end = reinterpret_cast<std::uintptr_t>(collection.entries_098);
  return (end - begin) >> 4u;
}

OpaqueCommandEntry* command_entry(OpaqueCommandCollection& collection,
                                  int index) {
  return collection.entries_094 + index;
}

void* current_camera(OpaqueCommandCollection& collection) {
  const int index = collection.vtable->active_58(collection.vtable);
  const int count = static_cast<int>(command_entry_count(collection));
  if (index < 0 || index >= count) {
    return nullptr;
  }
  OpaqueCommandEntry* entry = command_entry(collection, index);
  if (entry->first == entry->second) {
    return nullptr;
  }
  return entry->first;
}

void* command_name(OpaqueCommandCollection& collection, int index) {
  const int count = static_cast<int>(command_entry_count(collection));
  if (index < 0 || index >= count) {
    return nullptr;
  }
  OpaqueCommandEntry* entry = command_entry(collection, index);
  if (entry->first == entry->second) {
    return nullptr;
  }
  return entry->first;
}

const OpaqueWide* property_category(OpaquePropertyValue* value,
                                   CameraCommandPorts& ports) {
  if (value->type_012 == 0x13u || value->type_012 == 0x10u) {
    const OpaqueWide* category = nullptr;
    if ((value->flags_010 & 0x30u) != 0u) {
      category = *reinterpret_cast<const OpaqueWide**>(value->payload);
    }
    return category;
  }
  return ports.default_category_007c65a0();
}

void list_cameras(OpaqueCameraCommandOwner* owner,
                  CameraCommandPorts& ports) {
  OpaqueCommandCollection* collection = owner->collection_010;
  OpaqueCommandCollectionVTable* collection_vtable = collection->vtable;
  OpaqueCommandSecondary* secondary = owner->secondary_004;
  int index = 0;
  int count = collection_vtable->count_48(collection_vtable);
  if (count <= 0) {
    return;
  }
  do {
    const int active = collection_vtable->active_58(collection_vtable);
    const OpaqueWide* category = index == active
                                     ? ports.active_category_013ec468()
                                     : ports.inactive_category_013ed024();
    OpaqueCommandCamera* camera =
        collection_vtable->camera_at_4c(collection_vtable, index);
    OpaquePropertyList* properties = reinterpret_cast<OpaquePropertyList*>(
        camera->vtable->get_property_list_4c(camera));
    if (properties != nullptr &&
        properties->vtable->has_1c(properties->vtable, 0x0b2cccau)) {
      OpaquePropertyValue* value = reinterpret_cast<OpaquePropertyValue*>(
          properties->vtable->get_28(properties->vtable, 0x0b2cccau));
      category = property_category(value, ports);
    }
    const OpaqueWord description = collection_vtable->describe_50(
        collection_vtable, index, 0x013ec47cu,
        static_cast<OpaqueWord>(*reinterpret_cast<const OpaqueWord*>(category)));
    ports.log_list_00841000(secondary, index, 0x013ec47cu, description,
                            *reinterpret_cast<const OpaqueWord*>(category));
    index += 1;
    count = collection_vtable->count_48(collection_vtable);
  } while (index < count);
}

}

extern "C" OpaqueCamera* PKG_CAM_THISCALL service_007c61a0(
    OpaqueCameraManager* manager) {
  const int index = manager->active_index_0a8;
  if (index < 0) {
    return nullptr;
  }
  return manager->cameras_080[index];
}

extern "C" bool PKG_CAM_THISCALL service_007c66b0(
    OpaqueCameraManager* manager, OpaqueMessageRecord* message) {
  static_cast<void>(lookup_message(manager->messages_060, message->key));
  OpaqueMessageRegistry& registry = manager->messages_060;
  OpaqueMessageNode* sentinel = registry.buckets_004[registry.bucket_count_008];
  if (reinterpret_cast<std::uintptr_t>(message) ==
      reinterpret_cast<std::uintptr_t>(sentinel)) {
    return false;
  }
  OpaqueCameraManagerVTable* vtable = manager->vtable_000;
  static_cast<void>(vtable->set_active_by_id_54(manager, message->value));
  return true;
}

extern "C" bool PKG_CAM_THISCALL service_007c6750(
    OpaqueCameraCommandOwner* owner, OpaqueWord argument) {
  CameraCommandPorts& ports = *g_camera_command_ports;
  OpaqueCommandSecondary* secondary = owner->secondary_004;
  OpaqueCommandCollection* collection = owner->collection_010;
  OpaqueCommandCollectionVTable* collection_vtable = collection->vtable;

  if (ports.parse_mode_00837f30(argument) == 1) {
    return ports.log_current_00841000(secondary, current_camera(*collection));
  }

  OpaqueWord parse_status = 0;
  const char** candidate =
      ports.parse_default_00838020(argument, &parse_status, 1u);
  if (parse_status != 1u) {
    candidate = ports.lookup_switch_00838330(argument, 1u);
  }
  bool result = false;
  if (candidate != nullptr) {
    if (ports.is_digit(static_cast<unsigned char>(**candidate)) == 0) {
      OpaqueWideRange wide_range{};
      ports.widen_0093c5a0(*candidate, -1, &wide_range);
      const int count = collection_vtable->count_48(collection_vtable);
      bool matched = false;
      for (int index = 0; index < count; index += 1) {
        auto* name = static_cast<const OpaqueWide*>(
            command_name(*collection, index));
        if (ports.wide_compare(wide_range.begin, name) == 0) {
          collection_vtable->set_active_54(collection_vtable, index);
          matched = true;
          const std::size_t byte_count = static_cast<std::size_t>(
              reinterpret_cast<std::uintptr_t>(wide_range.end) -
              reinterpret_cast<std::uintptr_t>(wide_range.begin));
          if ((byte_count & ~std::size_t{1}) > 2u &&
              wide_range.begin != nullptr) {
            return ports.free_00f47380(wide_range.begin);
          }
          break;
        }
      }
      if (!matched) {
        throw OpaqueCameraCommandError{};
      }
    } else {
      const OpaqueWord resolved =
          secondary->vtable->resolve_digit_a0(secondary->vtable, *candidate);
      collection_vtable->activate_34(collection_vtable, resolved);
    }
  }

  result = false;
  if (ports.list_enabled_008380b0(argument)) {
    list_cameras(owner, ports);
  }

  const char** target = ports.lookup_target_00838330(argument);
  if (target != nullptr) {
    OpaqueRect rect{};
    const OpaqueWord value =
        static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(*target));
    static_cast<void>(secondary->vtable->resolve_target_b4(
        secondary->vtable, &rect, value));
    OpaqueRenderer* renderer = ports.renderer_get_0067dd10();
    static_cast<void>(renderer->vtable->layer_00.one(renderer, &rect));
    ports.viewer_update_007c3c20(value);
  }

  const char** render_type = ports.lookup_render_type_00838330(argument);
  if (render_type != nullptr) {
    OpaqueViewer* viewer =
        secondary->vtable->resolve_render_type_9c(
            secondary->vtable,
            static_cast<OpaqueWord>(
                reinterpret_cast<std::uintptr_t>(*render_type)));
    OpaqueRenderer* renderer = ports.renderer_get_0067dd10();
    OpaqueViewer* updated = renderer->vtable->layer_00.two(renderer, viewer, 0u);
    result = ports.end_update_007c3ce0(updated);
  }
  return result;
}

}

#undef PKG_CAM_CDECL
#undef PKG_CAM_THISCALL
