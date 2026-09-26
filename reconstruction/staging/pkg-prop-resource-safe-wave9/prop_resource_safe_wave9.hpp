#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-prop-resource-safe-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_CDECL __cdecl
#define PKG_PROP_SAFE_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_CDECL __attribute__((cdecl))
#define PKG_PROP_SAFE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {

using Word = std::uint32_t;

struct OpaquePropManager {
  void* vtable_00 = nullptr;
  std::uint8_t body_04_13[0x10]{};
  std::uint8_t initialized_14 = 0;
  std::uint8_t dev_mode_15 = 0;
  std::uint8_t body_16_1eb[0x1d6]{};
};

struct OpaqueStream;

using StreamGetAccessFlagsPort = Word(PKG_PROP_SAFE_THISCALL*)(OpaqueStream*);
using StreamWritePort = std::int32_t(PKG_PROP_SAFE_THISCALL*)(OpaqueStream*,
                                                              const void*,
                                                              std::size_t);

struct OpaqueStreamVtablePort {
  void* slots_00_0c[4]{};
  StreamGetAccessFlagsPort get_access_flags_10 = nullptr;
  void* slots_14_34[9]{};
  StreamWritePort write_38 = nullptr;
};

struct OpaqueStream {
  OpaqueStreamVtablePort* vtable = nullptr;
};

struct StreamPorts {
  OpaqueStreamVtablePort* memory_stream = nullptr;
  OpaqueStreamVtablePort* file_stream = nullptr;
};

struct OpaqueRecordWrite {
  void* vtable_00 = nullptr;
  Word reserved_04 = 0;
  Word type_08 = 0;
  std::uint8_t name_key_0c[0x0c]{};
  void* parent_18 = nullptr;
  Word file_access_1c = 0;
  OpaqueStreamVtablePort* stream_vtable_20 = nullptr;
  OpaqueStream memory_stream_24{};
  std::uint8_t memory_body_28_47[0x20]{};
  OpaqueStream file_stream_48{};
  std::uint8_t file_body_4c_27b[0x230]{};
};

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(OpaquePropManager) == 0x1ec, "prop manager size");
static_assert(offsetof(OpaquePropManager, vtable_00) == 0x00,
              "prop manager vtable at +0x00");
static_assert(offsetof(OpaquePropManager, body_04_13) == 0x04,
              "prop manager body follows the vtable pointer");
static_assert(offsetof(OpaquePropManager, initialized_14) == 0x14,
              "initialization flag at +0x14");
static_assert(offsetof(OpaquePropManager, dev_mode_15) == 0x15,
              "dev mode flag at +0x15");
static_assert(offsetof(OpaquePropManager, body_16_1eb) == 0x16,
              "prop manager body resumes after the dev mode flag");
static_assert(sizeof(OpaqueStream) == 4,
              "stream subobject head is one pointer");
static_assert(offsetof(OpaqueStream, vtable) == 0x00, "stream vtable at +0x00");
static_assert(sizeof(OpaqueStreamVtablePort) == 0x3c, "stream vtable size");
static_assert(offsetof(OpaqueStreamVtablePort, get_access_flags_10) == 0x10,
              "access flags port at +0x10");
static_assert(offsetof(OpaqueStreamVtablePort, write_38) == 0x38,
              "write port at +0x38");
static_assert(sizeof(OpaqueRecordWrite) == 0x27c, "record write size");
static_assert(offsetof(OpaqueRecordWrite, vtable_00) == 0x00,
              "record write vtable at +0x00");
static_assert(offsetof(OpaqueRecordWrite, reserved_04) == 0x04,
              "unnamed record word at +0x04");
static_assert(offsetof(OpaqueRecordWrite, type_08) == 0x08,
              "type word at +0x08");
static_assert(offsetof(OpaqueRecordWrite, name_key_0c) == 0x0c,
              "name key at +0x0c");
static_assert(offsetof(OpaqueRecordWrite, parent_18) == 0x18,
              "parent at +0x18");
static_assert(offsetof(OpaqueRecordWrite, file_access_1c) == 0x1c,
              "owner access gate word at +0x1c");
static_assert(offsetof(OpaqueRecordWrite, stream_vtable_20) == 0x20,
              "stream subobject vtable at +0x20");
static_assert(offsetof(OpaqueRecordWrite, memory_stream_24) == 0x24,
              "embedded memory stream at +0x24");
static_assert(offsetof(OpaqueRecordWrite, memory_body_28_47) == 0x28,
              "memory stream body ends at +0x48");
static_assert(offsetof(OpaqueRecordWrite, file_stream_48) == 0x48,
              "embedded file stream at +0x48");
static_assert(offsetof(OpaqueRecordWrite, file_body_4c_27b) == 0x4c,
              "file stream body ends at +0x27c");

void stream_publish_ports(OpaqueRecordWrite* record, StreamPorts ports);
OpaqueStream* record_write_stream(OpaqueRecordWrite* record);

void PKG_PROP_SAFE_THISCALL prop_manager_set_dev_mode_006a3300(
    OpaquePropManager* manager, std::uint8_t value);
std::uint8_t PKG_PROP_SAFE_THISCALL record_write_flush_006c0550(
    OpaqueStream* receiver, const void* data, Word size);

}

#undef PKG_PROP_SAFE_CDECL
#undef PKG_PROP_SAFE_THISCALL
