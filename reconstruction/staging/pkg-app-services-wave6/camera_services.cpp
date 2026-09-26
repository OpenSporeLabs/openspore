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

#if defined(_MSC_VER)
#define PKG_CAM_NOINLINE __declspec(noinline)
#else
#define PKG_CAM_NOINLINE __attribute__((noinline))
#endif

namespace openspore::reconstruction::pkg_app_services_wave6 {

CameraCommandPorts* g_camera_command_ports = nullptr;

namespace detail {

template <typename Function>
PKG_CAM_NOINLINE OpaqueWord call_noargs_word(Function function,
                                             void* receiver) {
  OpaqueWord result = 0;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "call *%2"
      : "=&a"(result)
      : "r"(receiver), "r"(function)
      : "cc", "ecx", "edx", "memory");
  return result;
}

template <typename Function, typename Arg>
PKG_CAM_NOINLINE OpaqueWord call_one_word(Function function, void* receiver,
                                          Arg value) {
  OpaqueWord result = 0;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "pushl %3\n\t"
      "call *%2"
      : "=&a"(result)
      : "r"(receiver), "r"(function), "r"(value)
      : "cc", "ecx", "edx", "memory");
  return result;
}

template <typename Function, typename Arg1, typename Arg2>
PKG_CAM_NOINLINE OpaqueWord call_two_word(Function function, void* receiver,
                                          Arg1 first, Arg2 second) {
  OpaqueWord result = 0;
  __asm__ volatile(
      "movl %2, %%edx\n\t"
      "movl %1, %%ecx\n\t"
      "pushl %4\n\t"
      "pushl %3\n\t"
      "call *%%edx"
      : "=&a"(result)
      : "r"(receiver), "m"(function), "r"(first), "r"(second)
      : "cc", "ecx", "edx", "memory");
  return result;
}

template <typename Return>
PKG_CAM_NOINLINE Return call_lookup_ret8(Return (*function)(OpaqueWord,
                                                            OpaqueWord),
                                         OpaqueWord first, OpaqueWord second) {
  Return result = Return{};
  __asm__ volatile(
      "pushl %3\n\t"
      "pushl %2\n\t"
      "call *%1"
      : "=&a"(result)
      : "r"(function), "r"(first), "r"(second)
      : "ecx", "edx", "cc", "memory");
  return result;
}

PKG_CAM_NOINLINE OpaqueWord
call_parse_default(CameraCommandPorts::ParseDefault function, void* receiver,
                   OpaqueWord* status, OpaqueWord minimum, OpaqueWord maximum) {
  struct Arguments {
    OpaqueWord* status;
    OpaqueWord minimum;
    OpaqueWord maximum;
  } arguments{status, minimum, maximum};
  OpaqueWord result = 0;
  __asm__ volatile(
      "movl %1, %%edx\n\t"
      "movl %2, %%ecx\n\t"
      "movl %3, %%esi\n\t"
      "pushl 8(%%esi)\n\t"
      "pushl 4(%%esi)\n\t"
      "pushl (%%esi)\n\t"
      "call *%%edx"
      : "=&a"(result)
      : "m"(function), "r"(receiver), "r"(&arguments)
      : "cc", "ecx", "edx", "esi", "memory");
  return result;
}

template <typename Function, typename Arg>
PKG_CAM_NOINLINE void call_void_one(Function function, void* receiver,
                                    Arg value) {
  __asm__ volatile(
      "movl %1, %%eax\n\t"
      "movl %0, %%ecx\n\t"
      "pushl %2\n\t"
      "call *%%eax"
      :
      : "r"(receiver), "m"(function), "r"(value)
      : "eax", "cc", "ecx", "edx", "memory");
}

template <typename Function, typename Arg1, typename Arg2>
PKG_CAM_NOINLINE void call_void_two(Function function, void* receiver,
                                    Arg1 first, Arg2 second) {
  __asm__ volatile(
      "movl %1, %%eax\n\t"
      "movl %0, %%ecx\n\t"
      "pushl %3\n\t"
      "pushl %2\n\t"
      "call *%%eax"
      :
      : "r"(receiver), "m"(function), "r"(first), "r"(second)
      : "eax", "cc", "ecx", "edx", "memory");
}

OpaqueMessageNode* lookup_message(OpaqueMessageRegistry& registry,
                                  OpaqueWord key) {
  OpaqueMessageNode** slot =
      &registry.buckets_004[key % registry.bucket_count_008];
  OpaqueMessageNode* node = *slot;
  while (node != nullptr) {
    if (node->key == key) {
      return node;
    }
    node = node->next;
  }
  return registry.buckets_004[registry.bucket_count_008];
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
  const int index = static_cast<int>(
      call_noargs_word(collection.vtable->active_58, &collection));
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

OpaqueWord read_first_word(const void* value) {
  OpaqueWord word = 0;
  std::memcpy(&word, value, sizeof(word));
  return word;
}

OpaqueWord property_log_value(OpaquePropertyValue* value,
                              CameraCommandPorts& ports) {
  if (value->type_012 == 0x13u || value->type_012 == 0x10u) {
    const void* category =
        (value->flags_010 & 0x30u) != 0u ? value->payload : value;
    return read_first_word(category);
  }
  return read_first_word(ports.default_category_007c65a0());
}

void list_cameras(OpaqueCameraCommandOwner* owner, CameraCommandPorts& ports) {
  OpaqueCommandCollection* collection = owner->collection_010;
  OpaqueCommandCollectionVTable* collection_vtable = collection->vtable;
  OpaqueCommandSecondary* secondary = owner->secondary_004;
  int index = 0;
  int count = static_cast<int>(
      call_noargs_word(collection_vtable->count_48, collection));
  if (count <= 0) {
    return;
  }
  do {
    const int active = static_cast<int>(
        call_noargs_word(collection_vtable->active_58, collection));
    const OpaqueWide* category =
        index == active ? reinterpret_cast<const OpaqueWide*>(0x01401b58u)
                        : reinterpret_cast<const OpaqueWide*>(0x013ed024u);
    OpaqueCommandCamera* camera = reinterpret_cast<OpaqueCommandCamera*>(
        call_one_word(collection_vtable->camera_at_4c, collection, index));
    OpaquePropertyList* properties =
        reinterpret_cast<OpaquePropertyList*>(reinterpret_cast<void*>(
            call_noargs_word(camera->vtable->get_property_list_4c, camera)));
    OpaqueWord log_value = 0x013ec468u;
    if (properties != nullptr && call_one_word(properties->vtable->has_1c,
                                               properties, 0x0b2cccau) != 0u) {
      OpaquePropertyValue* value = reinterpret_cast<OpaquePropertyValue*>(
          call_one_word(properties->vtable->get_28, properties, 0x0b2cccau));
      log_value = property_log_value(value, ports);
    }
    const OpaqueWide* name =
        static_cast<const OpaqueWide*>(command_name(*collection, index));
    if (name != nullptr) {
      ports.log_named_00841000(
          secondary, reinterpret_cast<const char*>(0x01410648u),
          reinterpret_cast<const char*>(category), name, log_value);
    } else {
      const OpaqueWord description =
          collection_vtable->describe_50(index, 0x013ec47cu);
      ports.log_described_00841000(
          secondary, reinterpret_cast<const char*>(0x01410628u), log_value,
          description, static_cast<OpaqueWord>(index), 0x013ec47cu);
    }
    index += 1;
    count = static_cast<int>(
        call_noargs_word(collection_vtable->count_48, collection));
  } while (index < count);
}

}

using namespace detail;

extern "C" OpaqueCamera* PKG_CAM_THISCALL
service_007c61a0(OpaqueCameraManager* manager) {
  const int index = manager->active_index_0a8;
  if (index < 0) {
    return nullptr;
  }
  return manager->cameras_080[index];
}

extern "C" bool PKG_CAM_THISCALL service_007c66b0(OpaqueCameraManager* manager,
                                                  OpaqueWord message_id) {
  OpaqueMessageRegistry& registry = manager->messages_060;
  OpaqueMessageNode* found = lookup_message(registry, message_id);
  OpaqueMessageNode* sentinel = registry.buckets_004[registry.bucket_count_008];
  if (found == sentinel) {
    return false;
  }
  OpaqueCameraManagerVTable* vtable = manager->vtable_000;
  static_cast<void>(
      call_one_word(vtable->set_active_by_id_54, manager, found->value));
  return true;
}

extern "C" bool PKG_CAM_THISCALL
service_007c6750(OpaqueCameraCommandOwner* owner, OpaqueWord argument) {
  CameraCommandPorts& ports = *g_camera_command_ports;
  OpaqueCommandSecondary* secondary = owner->secondary_004;
  OpaqueCommandCollection* collection = owner->collection_010;
  OpaqueCommandCollectionVTable* collection_vtable = collection->vtable;

  if (call_noargs_word(ports.parse_mode_00837f30,
                       reinterpret_cast<void*>(
                           static_cast<std::uintptr_t>(argument))) == 1) {
    void* const result = current_camera(*collection);
    const OpaqueWord log_result = ports.log_current_00841000(
        secondary, reinterpret_cast<const char*>(0x0141067cu),
        static_cast<const OpaqueWide*>(result));
    return log_result != 0u;
  }

  OpaqueWord parse_status = 0;
  const char** candidate = reinterpret_cast<const char**>(
      static_cast<std::uintptr_t>(call_parse_default(
          ports.parse_default_00838020,
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(argument)),
          &parse_status, 0u, 1u)));
  if (parse_status != 1u) {
    candidate = call_lookup_ret8(ports.lookup_switch_00838330,
                                 static_cast<OpaqueWord>(0x013f2ce4u), 1u);
  }
  bool result = false;
  if (candidate != nullptr) {
    if (ports.is_digit(static_cast<unsigned char>(**candidate)) == 0) {
      OpaqueWideRange wide_range{};
      ports.widen_0093c5a0(&wide_range, *candidate, 0xffffffffu);
      const int count = static_cast<int>(
          call_noargs_word(collection_vtable->count_48, collection));
      bool matched = false;
      for (int index = 0; index < count; index += 1) {
        auto* name =
            static_cast<const OpaqueWide*>(command_name(*collection, index));
        if (name == nullptr) {
          continue;
        }
        if (ports.wide_compare(wide_range.begin, name) == 0) {
          call_void_one(collection_vtable->set_active_54, collection, index);
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
      const OpaqueWord resolved = static_cast<OpaqueWord>(call_one_word(
          secondary->vtable->resolve_digit_a0, secondary, *candidate));
      call_void_one(collection_vtable->activate_34, collection, resolved);
    }
  }

  result = false;
  if (call_one_word(
          ports.list_enabled_008380b0,
          reinterpret_cast<void*>(static_cast<std::uintptr_t>(argument)),
          0x01409070u) != 0u) {
    list_cameras(owner, ports);
  }

  volatile OpaqueRect rect_storage;
  rect_storage.values[0] = 0.0f;
  rect_storage.values[1] = 0.0f;
  rect_storage.values[2] = 0.0f;
  rect_storage.values[3] = 0.0f;
  OpaqueRect* rect = const_cast<OpaqueRect*>(&rect_storage);
  const char** target = call_lookup_ret8(
      ports.lookup_target_00838330, static_cast<OpaqueWord>(0x01410624u), 1u);
  if (target != nullptr) {
    const OpaqueWord value =
        static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(*target));
    static_cast<void>(call_two_word(secondary->vtable->resolve_target_b4,
                                    secondary, rect, value));
    OpaqueRenderer* renderer = ports.renderer_get_0067dd10();
    OpaqueViewer* viewer = reinterpret_cast<OpaqueViewer*>(
        call_one_word(renderer->vtable->layer_58.one, renderer, rect));
    call_void_one(ports.viewer_update_007c3c20, viewer, rect);
  }

  const char** render_type =
      call_lookup_ret8(ports.lookup_render_type_00838330,
                       static_cast<OpaqueWord>(0x01410618u), 1u);
  if (render_type != nullptr) {
    OpaqueViewer* viewer = reinterpret_cast<OpaqueViewer*>(
        call_one_word(secondary->vtable->resolve_render_type_9c, secondary,
                      static_cast<OpaqueWord>(
                          reinterpret_cast<std::uintptr_t>(*render_type))));
    OpaqueRenderer* renderer = ports.renderer_get_0067dd10();
    OpaqueViewer* updated = reinterpret_cast<OpaqueViewer*>(
        call_two_word(renderer->vtable->layer_58.two, renderer, viewer, 0u));
    result =
        call_two_word(
            ports.end_update_007c3ce0, updated,
            static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(viewer)),
            0u) != 0u;
  }
  return result;
}

}

#undef PKG_CAM_CDECL
#undef PKG_CAM_THISCALL
#undef PKG_CAM_NOINLINE
