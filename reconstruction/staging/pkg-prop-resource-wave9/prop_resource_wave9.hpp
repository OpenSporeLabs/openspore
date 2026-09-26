#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "pkg-prop-resource-wave9 requires an x86-32 target"
#endif

#if defined(_MSC_VER)
#define PKG_PROP_CDECL __cdecl
#define PKG_PROP_THISCALL __thiscall
#else
#define PKG_PROP_CDECL __attribute__((cdecl))
#define PKG_PROP_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_wave9 {

using Word = std::uint32_t;

struct OpaqueResourceKey {
  std::array<Word, 3> words{};
};

struct OpaqueRecord;

struct OpaqueResource;

struct OpaqueManagerVtable;

struct OpaqueManager {
  OpaqueManagerVtable* vtable = nullptr;
  std::array<std::uint8_t, 0x11> bytes_04_14{};
  std::uint8_t dev_mode_15 = 0;
  std::array<std::uint8_t, 0x1d6> bytes_16_1eb{};
};

struct OpaqueResourceVtable {
  std::int32_t(PKG_PROP_THISCALL* retain_00)(OpaqueResource*) = nullptr;
  void(PKG_PROP_THISCALL* release_04)(OpaqueResource*) = nullptr;
  void(PKG_PROP_THISCALL* destroy_08)(OpaqueResource*, std::uint8_t) = nullptr;
};

struct OpaqueRecordVtable {
  void* slots_00_0c[4]{};
  const OpaqueResourceKey*(PKG_PROP_THISCALL* get_key_10)(OpaqueRecord*) =
      nullptr;
};

struct OpaqueRecord {
  OpaqueRecordVtable* vtable = nullptr;
};

struct OpaqueResource {
  OpaqueResourceVtable* vtable = nullptr;
  Word reference_count = 0;
  std::array<std::uint8_t, 12> key_bytes{};
  std::array<std::uint8_t, 0x10> cleared_14_23{};
  std::array<std::uint8_t, 0x0c> opaque_24_2f{};
  Word cleared_30 = 0;
  Word cleared_34 = 0;
};

struct OpaqueManagerVtable {
  void* slots_00_20[9]{};
  std::uint8_t(PKG_PROP_THISCALL* dispatch_24)(OpaqueManager*, OpaqueRecord*,
                                               OpaqueResource*, Word,
                                               Word) = nullptr;
};

struct ResourceCreationPorts {
  OpaqueResource*(PKG_PROP_CDECL* allocate)(std::size_t, const char*, void*,
                                            void*, void*, void*) = nullptr;
  OpaqueResourceVtable* resource_vtable = nullptr;
};

struct OpaqueStream;

struct OpaqueStreamVtable {
  void* slots_00_0c[4]{};
  Word(PKG_PROP_THISCALL* get_access_flags_10)(OpaqueStream*) = nullptr;
  void* slots_14_34[9]{};
  std::int32_t(PKG_PROP_THISCALL* write_38)(OpaqueStream*, const void*,
                                            std::size_t) = nullptr;
};

struct OpaqueStream {
  OpaqueStreamVtable* vtable = nullptr;
};

struct OpaqueRecordWrite {
  std::array<std::uint8_t, 0x27c> bytes{};
};

static_assert(sizeof(void*) == 4, "x86-32 pointers are four bytes");
static_assert(sizeof(Word) == 4, "target words are four bytes");
static_assert(sizeof(OpaqueResource) == 0x38, "opaque resource size");
static_assert(offsetof(OpaqueResource, vtable) == 0x00, "vtable at +0x00");
static_assert(offsetof(OpaqueResource, reference_count) == 0x04,
              "reference count at +0x04");
static_assert(offsetof(OpaqueResource, key_bytes) == 0x08, "key at +0x08");
static_assert(offsetof(OpaqueResource, cleared_14_23) == 0x14,
              "cleared dword run starts at +0x14");
static_assert(offsetof(OpaqueResource, opaque_24_2f) == 0x24,
              "untouched dwords start at +0x24");
static_assert(offsetof(OpaqueResource, cleared_30) == 0x30,
              "dword field cleared at +0x30");
static_assert(offsetof(OpaqueResource, cleared_34) == 0x34,
              "dword field cleared at +0x34");
static_assert(sizeof(decltype(OpaqueResource::cleared_30)) == 4,
              "+0x30 clears one four-byte word");
static_assert(sizeof(decltype(OpaqueResource::cleared_34)) == 4,
              "+0x34 clears one four-byte word");
static_assert(sizeof(OpaqueManager) == 0x1ec, "manager size");
static_assert(offsetof(OpaqueManager, vtable) == 0x00, "vtable at +0x00");
static_assert(offsetof(OpaqueManager, bytes_04_14) == 0x04,
              "manager body follows the vtable pointer");
static_assert(offsetof(OpaqueManager, dev_mode_15) == 0x15,
              "dev mode flag at +0x15");
static_assert(offsetof(OpaqueManager, bytes_16_1eb) == 0x16,
              "manager body resumes after the dev mode flag");
static_assert(sizeof(OpaqueManagerVtable) == 0x28, "manager vtable prefix");
static_assert(sizeof(OpaqueStreamVtable) == 0x3c, "stream vtable size");
static_assert(sizeof(OpaqueRecordWrite) == 0x27c, "opaque record write size");

void resource_creation_set_ports(ResourceCreationPorts ports);
void PKG_PROP_THISCALL prop_manager_set_mode_byte_006a3300(OpaqueManager*,
                                                           std::uint8_t);
OpaqueResource* PKG_PROP_THISCALL resource_construct_006a1b90(OpaqueResource*,
                                                              Word);
bool PKG_PROP_THISCALL prop_manager_create_resource_006a3330(OpaqueManager*,
                                                             OpaqueRecord*,
                                                             OpaqueResource**,
                                                             Word, Word);
bool PKG_PROP_THISCALL record_write_flush_006c0550(OpaqueStream*, const void*,
                                                   Word);

}

#undef PKG_PROP_CDECL
#undef PKG_PROP_THISCALL
