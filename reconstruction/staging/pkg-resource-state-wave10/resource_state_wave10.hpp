#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-resource-state-wave10 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_RS_CDECL __cdecl
#define PKG_RS_THISCALL __thiscall
#else
#define PKG_RS_CDECL __attribute__((cdecl))
#define PKG_RS_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_wave10 {

using Word = std::uint32_t;

struct OpaqueOwner;

struct OpaqueRecordWrite;

using DestroyPort = void(PKG_RS_THISCALL*)(OpaqueRecordWrite*);
using UntrackPort = void(PKG_RS_CDECL*)(void*);
using DropHandlePort = void(PKG_RS_CDECL*)(void*, Word, Word, Word, Word);
using ChunkSweepPort = void(PKG_RS_THISCALL*)(void*, void* const*, Word);
using OwnerUntrackPort = void(PKG_RS_THISCALL*)(OpaqueOwner*, void*);

struct OpaqueRecordWrite {
  void* vtable_00 = nullptr;
  Word reserved_04 = 0;
  void* secondary_vtable_08 = nullptr;
  Word sentinel_guard_0c = 0;
  void* sentinel_10 = nullptr;
  std::uint8_t body_14_23[0x10]{};
  void* stream_vtable_24 = nullptr;
  void* chunk_base_28 = nullptr;
  Word chunk_count_2c = 0;
  Word cursor_30 = 0;
  std::uint8_t body_34_43[0x10]{};
  void* handle_44 = nullptr;
  Word handle_arg_48 = 0;
  Word handle_arg_4c = 0;
  Word handle_arg_50 = 0;
  Word handle_arg_54 = 0;
  std::uint8_t body_58_27b[0x224]{};
};

struct ResourceStatePorts {
  DestroyPort destroy_00e30f90 = nullptr;
  UntrackPort untrack_00f47380 = nullptr;
  DropHandlePort drop_handle_00571db0 = nullptr;
  ChunkSweepPort chunk_sweep_00e308d0 = nullptr;
  OwnerUntrackPort owner_untrack_009276c0 = nullptr;
  void* owner_instance_016c8b44 = nullptr;
};

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(OpaqueRecordWrite) == 0x27c, "record write size");
static_assert(offsetof(OpaqueRecordWrite, vtable_00) == 0x00,
              "primary vtable at +0x00");
static_assert(offsetof(OpaqueRecordWrite, reserved_04) == 0x04,
              "reserved word at +0x04");
static_assert(offsetof(OpaqueRecordWrite, secondary_vtable_08) == 0x08,
              "secondary vtable at +0x08");
static_assert(offsetof(OpaqueRecordWrite, sentinel_guard_0c) == 0x0c,
              "sentinel guard word at +0x0c");
static_assert(offsetof(OpaqueRecordWrite, sentinel_10) == 0x10,
              "sentinel pointer at +0x10");
static_assert(offsetof(OpaqueRecordWrite, body_14_23) == 0x14,
              "body run starts at +0x14");
static_assert(offsetof(OpaqueRecordWrite, stream_vtable_24) == 0x24,
              "embedded stream vtable at +0x24");
static_assert(offsetof(OpaqueRecordWrite, chunk_base_28) == 0x28,
              "chunk base at +0x28");
static_assert(offsetof(OpaqueRecordWrite, chunk_count_2c) == 0x2c,
              "chunk count at +0x2c");
static_assert(offsetof(OpaqueRecordWrite, cursor_30) == 0x30,
              "cursor at +0x30");
static_assert(offsetof(OpaqueRecordWrite, body_34_43) == 0x34,
              "body run resumes at +0x34");
static_assert(offsetof(OpaqueRecordWrite, handle_44) == 0x44,
              "handle at +0x44");
static_assert(offsetof(OpaqueRecordWrite, handle_arg_48) == 0x48,
              "handle argument at +0x48");
static_assert(offsetof(OpaqueRecordWrite, handle_arg_4c) == 0x4c,
              "handle argument at +0x4c");
static_assert(offsetof(OpaqueRecordWrite, handle_arg_50) == 0x50,
              "handle argument at +0x50");
static_assert(offsetof(OpaqueRecordWrite, handle_arg_54) == 0x54,
              "handle argument at +0x54");
static_assert(offsetof(OpaqueRecordWrite, body_58_27b) == 0x58,
              "tail run starts at +0x58");

static_assert(0x01481948u > 0x01481940u, "the two vtable slots are distinct");
static_assert(0x013ec458u != 0x01481948u, "base and derived differ");
static_assert(0x013eb394u != 0x01481940u, "base and derived differ");
static_assert(0x016c8b44u > 0x00400000u, "owner instance lies above the image");

const void* kVtableDerivedPrimary_01481948();
const void* kVtableDerivedSecondary_01481940();
const void* kVtableBasePrimary_013ec458();
const void* kVtableBaseSecondary_013eb394();
const void* kOwnerInstanceDefault_016c8b44();

Word state_load_word(const void* base, std::size_t offset);
void* state_load_pointer(const void* base, std::size_t offset);
void state_store_word(void* base, std::size_t offset, Word value);
void state_store_pointer(void* base, std::size_t offset, const void* value);

void resource_state_set_ports(ResourceStatePorts new_ports);
void resource_state_reset_ports();

OpaqueRecordWrite* PKG_RS_THISCALL record_write_get_state_00e310c0(
    OpaqueRecordWrite* receiver, Word state_release_flag);

void PKG_RS_THISCALL record_write_destroy_00e30f90(OpaqueRecordWrite* receiver);
void PKG_RS_CDECL record_write_untrack_00f47380(void* target);
void PKG_RS_CDECL record_write_drop_handle_00571db0(void* handle, Word arg_48,
                                                    Word arg_4c, Word arg_50,
                                                    Word arg_54);
void PKG_RS_THISCALL record_write_chunk_sweep_00e308d0(void* receiver,
                                                       void* const* chunks,
                                                       Word count);

}

#undef PKG_RS_CDECL
#undef PKG_RS_THISCALL
