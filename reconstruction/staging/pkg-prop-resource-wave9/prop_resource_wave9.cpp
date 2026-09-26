#include "prop_resource_wave9.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_PROP_THISCALL __thiscall
#else
#define PKG_PROP_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_wave9 {
namespace {

OpaqueResource* default_allocate(std::size_t, const char*, void*, void*, void*,
                                 void*) {
  return nullptr;
}

OpaqueResourceVtable* const kDefaultResourceVtable =
    reinterpret_cast<OpaqueResourceVtable*>(0x1408820u);

ResourceCreationPorts ports{default_allocate, kDefaultResourceVtable};

}

void resource_creation_set_ports(ResourceCreationPorts new_ports) {
  if (new_ports.allocate == nullptr) {
    new_ports.allocate = default_allocate;
  }
  if (new_ports.resource_vtable == nullptr) {
    new_ports.resource_vtable = kDefaultResourceVtable;
  }
  ports = new_ports;
}

void PKG_PROP_THISCALL prop_manager_set_mode_byte_006a3300(
    OpaqueManager* manager, std::uint8_t value) {
  manager->dev_mode_15 = value;
}

OpaqueResource* PKG_PROP_THISCALL
resource_construct_006a1b90(OpaqueResource* resource, Word tag) {
  static_cast<void>(tag);
  std::memset(reinterpret_cast<std::uint8_t*>(resource) + 0x04, 0, 0x20);
  resource->cleared_30 = 0;
  resource->cleared_34 = 0;
  resource->vtable = ports.resource_vtable;
  return resource;
}

bool PKG_PROP_THISCALL prop_manager_create_resource_006a3330(
    OpaqueManager* manager, OpaqueRecord* record, OpaqueResource** destination,
    Word key_word, Word type_id) {
  OpaqueResource* resource =
      ports.allocate(0x38, reinterpret_cast<const char*>(0x1408b44u), nullptr,
                     nullptr, nullptr, nullptr);
  if (resource != nullptr) {
    resource = resource_construct_006a1b90(resource, 0x1408b34u);
  }

  const OpaqueResourceKey* key = record->vtable->get_key_10(record);
  std::memcpy(resource->key_bytes.data(), key, resource->key_bytes.size());

  const std::uint8_t accepted = manager->vtable->dispatch_24(
      manager, record, resource, key_word, type_id);
  if (accepted == 0) {
    resource->vtable->destroy_08(resource, 1);
    return false;
  }

  *destination = resource;
  resource->vtable->retain_00(resource);
  return true;
}

bool PKG_PROP_THISCALL record_write_flush_006c0550(OpaqueStream* receiver,
                                                   const void* data,
                                                   Word size) {
  auto* receiver_bytes = reinterpret_cast<std::uint8_t*>(receiver);
  Word owner_reference_count = 0;
  std::memcpy(&owner_reference_count, receiver_bytes - 0x04,
              sizeof(owner_reference_count));
  if (owner_reference_count == 0) {
    return false;
  }

  OpaqueStream* const embedded_file =
      reinterpret_cast<OpaqueStream*>(receiver_bytes + 0x28);
  OpaqueStream* const embedded_memory =
      reinterpret_cast<OpaqueStream*>(receiver_bytes + 0x04);

  if (embedded_file->vtable->get_access_flags_10(embedded_file) != 0) {
    return static_cast<std::uint8_t>(
               embedded_file->vtable->write_38(embedded_file, data, size)) != 0;
  }
  return static_cast<std::uint8_t>(embedded_memory->vtable->write_38(
             embedded_memory, data, size)) != 0;
}

}

#undef PKG_PROP_THISCALL
