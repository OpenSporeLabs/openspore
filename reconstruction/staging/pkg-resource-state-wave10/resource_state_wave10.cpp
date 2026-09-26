#include "resource_state_wave10.hpp"

#include <cstring>

#if defined(_MSC_VER)
#define PKG_RS_CDECL __cdecl
#define PKG_RS_THISCALL __thiscall
#else
#define PKG_RS_CDECL __attribute__((cdecl))
#define PKG_RS_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_wave10 {
namespace {

void PKG_RS_CDECL default_drop_handle_00571db0(void*, Word, Word, Word, Word) {}

void PKG_RS_THISCALL default_chunk_sweep_00e308d0(void*, void* const*, Word) {}

void PKG_RS_THISCALL default_owner_untrack_009276c0(OpaqueOwner*, void*) {}

ResourceStatePorts make_default_ports() {
  ResourceStatePorts defaults{};
  defaults.destroy_00e30f90 = &record_write_destroy_00e30f90;
  defaults.untrack_00f47380 = &record_write_untrack_00f47380;
  defaults.drop_handle_00571db0 = &default_drop_handle_00571db0;
  defaults.chunk_sweep_00e308d0 = &default_chunk_sweep_00e308d0;
  defaults.owner_untrack_009276c0 = &default_owner_untrack_009276c0;
  defaults.owner_instance_016c8b44 = reinterpret_cast<void*>(0x016c8b44u);
  return defaults;
}

ResourceStatePorts ports = make_default_ports();

}

const void* kVtableDerivedPrimary_01481948() {
  return reinterpret_cast<const void*>(0x01481948u);
}

const void* kVtableDerivedSecondary_01481940() {
  return reinterpret_cast<const void*>(0x01481940u);
}

const void* kVtableBasePrimary_013ec458() {
  return reinterpret_cast<const void*>(0x013ec458u);
}

const void* kVtableBaseSecondary_013eb394() {
  return reinterpret_cast<const void*>(0x013eb394u);
}

const void* kOwnerInstanceDefault_016c8b44() {
  return reinterpret_cast<const void*>(0x016c8b44u);
}

Word state_load_word(const void* base, std::size_t offset) {
  Word value = 0;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

void* state_load_pointer(const void* base, std::size_t offset) {
  void* value = nullptr;
  std::memcpy(&value, static_cast<const std::uint8_t*>(base) + offset,
              sizeof(value));
  return value;
}

void state_store_word(void* base, std::size_t offset, Word value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

void state_store_pointer(void* base, std::size_t offset, const void* value) {
  std::memcpy(static_cast<std::uint8_t*>(base) + offset, &value, sizeof(value));
}

void resource_state_set_ports(ResourceStatePorts new_ports) {
  if (new_ports.destroy_00e30f90 == nullptr) {
    new_ports.destroy_00e30f90 = &record_write_destroy_00e30f90;
  }
  if (new_ports.untrack_00f47380 == nullptr) {
    new_ports.untrack_00f47380 = &record_write_untrack_00f47380;
  }
  if (new_ports.drop_handle_00571db0 == nullptr) {
    new_ports.drop_handle_00571db0 = &default_drop_handle_00571db0;
  }
  if (new_ports.chunk_sweep_00e308d0 == nullptr) {
    new_ports.chunk_sweep_00e308d0 = &default_chunk_sweep_00e308d0;
  }
  if (new_ports.owner_untrack_009276c0 == nullptr) {
    new_ports.owner_untrack_009276c0 = &default_owner_untrack_009276c0;
  }
  if (new_ports.owner_instance_016c8b44 == nullptr) {
    new_ports.owner_instance_016c8b44 = reinterpret_cast<void*>(0x016c8b44u);
  }
  ports = new_ports;
}

void resource_state_reset_ports() { ports = make_default_ports(); }

void PKG_RS_CDECL record_write_untrack_00f47380(void* target) {
  if (target == nullptr) {
    return;
  }
  ports.owner_untrack_009276c0(
      static_cast<OpaqueOwner*>(ports.owner_instance_016c8b44), target);
}

void PKG_RS_CDECL record_write_drop_handle_00571db0(void* handle, Word arg_48,
                                                    Word arg_4c, Word arg_50,
                                                    Word arg_54) {
  ports.drop_handle_00571db0(handle, arg_48, arg_4c, arg_50, arg_54);
}

void PKG_RS_THISCALL record_write_chunk_sweep_00e308d0(void* receiver,
                                                       void* const* chunks,
                                                       Word count) {
  ports.chunk_sweep_00e308d0(receiver, chunks, count);
}

void PKG_RS_THISCALL
record_write_destroy_00e30f90(OpaqueRecordWrite* receiver) {
  std::uint8_t* const bytes = reinterpret_cast<std::uint8_t*>(receiver);

  state_store_pointer(bytes, 0x00, kVtableDerivedPrimary_01481948());
  state_store_pointer(bytes, 0x08, kVtableDerivedSecondary_01481940());

  const Word handle = state_load_word(receiver, 0x44);
  if (handle != 0) {
    const Word arg_48 = state_load_word(receiver, 0x48);
    const Word arg_4c = state_load_word(receiver, 0x4c);
    const Word arg_50 = state_load_word(receiver, 0x50);
    const Word arg_54 = state_load_word(receiver, 0x54);
    state_store_word(receiver, 0x44, 0);
    record_write_drop_handle_00571db0(
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(handle)), arg_48,
        arg_4c, arg_50, arg_54);
  }

  const Word chunk_count = state_load_word(receiver, 0x2c);
  void* const chunk_base = state_load_pointer(receiver, 0x28);
  record_write_chunk_sweep_00e308d0(bytes + 0x24, &chunk_base, chunk_count);
  state_store_word(receiver, 0x30, 0);
  if (chunk_count > 1) {
    ports.untrack_00f47380(chunk_base);
  }

  void* const sentinel = state_load_pointer(receiver, 0x10);
  if (sentinel != nullptr && state_load_word(receiver, 0x0c) != 0) {
    ports.untrack_00f47380(sentinel);
  }

  state_store_pointer(bytes, 0x08, kVtableBaseSecondary_013eb394());
  state_store_pointer(bytes, 0x00, kVtableBasePrimary_013ec458());
}

OpaqueRecordWrite* PKG_RS_THISCALL record_write_get_state_00e310c0(
    OpaqueRecordWrite* receiver, Word state_release_flag) {
  ports.destroy_00e30f90(receiver);
  if ((state_release_flag & 0x01u) != 0) {
    ports.untrack_00f47380(receiver);
  }
  return receiver;
}

}

#undef PKG_RS_CDECL
#undef PKG_RS_THISCALL
