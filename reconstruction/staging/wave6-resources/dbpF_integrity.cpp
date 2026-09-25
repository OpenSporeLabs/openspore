#include "dbpF_integrity.hpp"

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_DBPF_THISCALL __thiscall
#else
#define WAVE6_DBPF_THISCALL __attribute__((thiscall))
#endif

namespace {

bool default_validate(ObservedDatabasePackedFile*, void*, void*, void*) {
  return false;
}

bool default_repair(ObservedDatabasePackedFile*, void*, void*, void*, void*) {
  return false;
}

const DBPFIntegrityServices kDefaultServices{default_validate, default_repair};

}

DBPFIntegrityServices& dbpf_integrity_services() {
  static DBPFIntegrityServices services = kDefaultServices;
  return services;
}

void set_dBPF_integrity_services(const DBPFIntegrityServices* services) {
  dbpf_integrity_services() =
      services == nullptr ? kDefaultServices : *services;
}

bool WAVE6_DBPF_THISCALL database_packed_file_verify_index_008d9320(
    ObservedDatabasePackedFile* file, void* arg1, void* record, void* arg3,
    void* arg4, void* arg5) {
  (void)arg1;
  if (record == nullptr) {
    return false;
  }

  void* object = file->allocator->vtable->open_at_08(
      file->allocator, 0, 0x140a0fcu, reinterpret_cast<TargetWord>(arg3));
  if (object == nullptr) {
    return false;
  }

  DBPFIntegrityServices& services = dbpf_integrity_services();
  bool result = services.validate(file, object, record, arg3);
  if (result) {
    result = services.repair(file, object, arg3, arg4, arg5);
  }
  file->allocator->vtable->close_at_0c(file->allocator, object, 0);
  return result;
}

#undef WAVE6_DBPF_THISCALL

}
