#include "ui_safe_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_UI_SAFE_CDECL __cdecl
#define PKG_UI_SAFE_THISCALL __thiscall
#else
#define PKG_UI_SAFE_CDECL __attribute__((cdecl))
#define PKG_UI_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_ui_safe_wave10 {
namespace {

void PKG_UI_SAFE_THISCALL default_service_destroy_port(OpaqueService24*) {}

void PKG_UI_SAFE_CDECL default_deallocate_port(void*) {}

constexpr ImageArchivePorts kDefaultPorts{default_service_destroy_port,
                                          default_deallocate_port};

ImageArchivePorts published_ports = kDefaultPorts;

}

ImageArchivePorts& image_archive_ports() { return published_ports; }

void image_archive_set_ports(const ImageArchivePorts& ports) {
  published_ports = ports;
}

void image_archive_reset_ports() { published_ports = kDefaultPorts; }

OpaqueImageArchive* PKG_UI_SAFE_THISCALL
image_archive_scalar_deleting_destructor_00635700(OpaqueImageArchive* archive,
                                                  TargetWord deleting) {
  archive->vtable_00 = reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(kDerivedPrimaryVtable));
  archive->vtable_04 = reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(kDerivedSecondaryVtable));

  OpaqueSlot* const late = archive->slot_68;
  if (late != nullptr) {
    late->vtable->release_04(late);
  }
  OpaqueSlot* const early = archive->slot_64;
  if (early != nullptr) {
    early->vtable->release_04(early);
  }

  const ImageArchivePorts& ports = image_archive_ports();
  ports.service_destroy(&archive->service_2c);
  ports.service_destroy(&archive->service_14);

  archive->vtable_04 = reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(kBaseSecondaryVtable));
  archive->vtable_00 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(kBasePrimaryVtable));

  if ((deleting & 0x01u) != 0u) {
    ports.deallocate(archive);
  }
  return archive;
}

}

#undef PKG_UI_SAFE_CDECL
#undef PKG_UI_SAFE_THISCALL
