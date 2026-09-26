#include "prop_resource_safe_wave9.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {

void stream_publish_ports(OpaqueRecordWrite* record, StreamPorts ports) {
  record->memory_stream_24.vtable = ports.memory_stream;
  record->file_stream_48.vtable = ports.file_stream;
}

OpaqueStream* record_write_stream(OpaqueRecordWrite* record) {
  return reinterpret_cast<OpaqueStream*>(
      reinterpret_cast<std::uint8_t*>(record) + 0x20);
}

void PKG_PROP_SAFE_THISCALL prop_manager_set_dev_mode_006a3300(
    OpaquePropManager* manager, std::uint8_t value) {
  manager->dev_mode_15 = value;
}

std::uint8_t PKG_PROP_SAFE_THISCALL record_write_flush_006c0550(
    OpaqueStream* receiver, const void* data, Word size) {
  std::uint8_t* const receiver_bytes =
      reinterpret_cast<std::uint8_t*>(receiver);
  Word owner_file_access = 0;
  std::memcpy(&owner_file_access, receiver_bytes - 0x04,
              sizeof(owner_file_access));
  if (owner_file_access == 0) {
    return 0;
  }

  OpaqueStream* const file_stream =
      reinterpret_cast<OpaqueStream*>(receiver_bytes + 0x28);
  OpaqueStream* const memory_stream =
      reinterpret_cast<OpaqueStream*>(receiver_bytes + 0x04);

  if (file_stream->vtable->get_access_flags_10(file_stream) != 0) {
    return static_cast<std::uint8_t>(
        file_stream->vtable->write_38(file_stream, data, size));
  }
  return static_cast<std::uint8_t>(
      memory_stream->vtable->write_38(memory_stream, data, size));
}

}

#undef PKG_PROP_SAFE_THISCALL
