#include "pf_record_read.hpp"

#include <cstring>

namespace openspore::reconstruction::wave6_resources {

#if defined(_MSC_VER)
#define WAVE6_PF_RECORD_THISCALL __thiscall
#else
#define WAVE6_PF_RECORD_THISCALL __attribute__((thiscall))
#endif

namespace {

void default_construct_memory_stream(MemoryStream*, TargetWord) {}

TargetWord default_reset_memory_stream(MemoryStream*) { return 0; }

const PFRecordReadServices kDefaultServices{
    default_construct_memory_stream, default_reset_memory_stream};

void* observed_pointer(TargetWord address) {
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(address));
}

}

PFRecordReadServices& pf_record_read_services() {
  static PFRecordReadServices services = kDefaultServices;
  return services;
}

void set_pf_record_read_services(const PFRecordReadServices* services) {
  pf_record_read_services() =
      services == nullptr ? kDefaultServices : *services;
}

PFRecordRead* WAVE6_PF_RECORD_THISCALL pf_record_read_set_position_008dcdc0(
    PFRecordRead* record, RecordInfo* info, ResourceKey* name_key,
    void* parent_dbp) {
  PFRecordReadServices& services = pf_record_read_services();
  record->vftable0 = observed_pointer(0x13effa8u);
  record->ref_count = 0;
  record->vftable0 = observed_pointer(0x140a2e0u);
  record->type = 0x12e4a891u;
  record->name_key = *name_key;
  record->parent_dbp = parent_dbp;
  record->file_access = 1;
  record->stream_vtable = observed_pointer(0x13f3a68u);
  record->field_24 = 0;
  record->field_28 = -1;
  services.construct_memory_stream(&record->internal_buffer, 0x140a30cu);
  std::memcpy(&record->dbpf_item, info, sizeof(record->dbpf_item));
  record->offset = 0;
  record->size = 0;
  record->flags = 0;
  record->stream_ref_count = 1;
  services.reset_memory_stream(&record->internal_buffer);

  if (info->flags != 0) {
    record->size = info->memory_size;
    record->flags = 1;
    return record;
  }

  record->size = info->compressed_size;
  if (record->size <= 0x200u) {
    record->flags = 1;
  }
  return record;
}

#undef WAVE6_PF_RECORD_THISCALL

}
