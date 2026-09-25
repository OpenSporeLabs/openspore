#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "resource_index.hpp"

#if !defined(__i386__) && !defined(_M_IX86)
#error "wave6 resource reconstruction requires an x86-32 target"
#endif

namespace openspore::reconstruction::wave6_resources {

struct IndexObjectAllocator;

using OpenIndexObject = void* (*)(IndexObjectAllocator*, TargetWord,
                                  TargetWord, TargetWord);
using CloseIndexObject = void (*)(IndexObjectAllocator*, void*, TargetWord);

struct IndexObjectAllocatorVtable {
  void* slots_00_04[2];
  OpenIndexObject open_at_08;
  CloseIndexObject close_at_0c;
};

struct IndexObjectAllocator {
  IndexObjectAllocatorVtable* vtable;
};

struct ObservedDatabasePackedFile {
  void* vftable0;
  void* vftable1;
  std::int32_t ref_count;
  std::uint8_t initialized;
  std::array<std::uint8_t, 3> opaque_0d_0f;
  IndexObjectAllocator* allocator;
};

using ValidateIndexRecord = bool (*)(ObservedDatabasePackedFile*, void*,
                                     void*, void*);
using RepairIndexRecord = bool (*)(ObservedDatabasePackedFile*, void*, void*,
                                   void*, void*);

struct DBPFIntegrityServices {
  ValidateIndexRecord validate;
  RepairIndexRecord repair;
};

#if defined(_MSC_VER)
#define WAVE6_DBPF_THISCALL __thiscall
#else
#define WAVE6_DBPF_THISCALL __attribute__((thiscall))
#endif

DBPFIntegrityServices& dbpf_integrity_services();
void set_dBPF_integrity_services(const DBPFIntegrityServices* services);
bool WAVE6_DBPF_THISCALL database_packed_file_verify_index_008d9320(
    ObservedDatabasePackedFile* file, void* arg1, void* record, void* arg3,
    void* arg4, void* arg5);

#undef WAVE6_DBPF_THISCALL

static_assert(sizeof(void*) == 4, "wave6 pointers are 32-bit");
static_assert(offsetof(IndexObjectAllocatorVtable, open_at_08) == 0x08,
              "DBPF open slot offset");
static_assert(offsetof(IndexObjectAllocatorVtable, close_at_0c) == 0x0c,
              "DBPF close slot offset");
static_assert(offsetof(ObservedDatabasePackedFile, allocator) == 0x10,
              "DBPF allocator offset");
static_assert(sizeof(ObservedDatabasePackedFile) == 0x14,
              "observed DBPF carrier extent");

}
