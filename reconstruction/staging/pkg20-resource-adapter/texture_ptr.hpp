#pragma once

#include <cstddef>
#include <cstdint>

#if !defined(__i386__) && !defined(_M_IX86)
#error "PKG-20 resource adapter requires an x86-32 target"
#endif

namespace openspore::reconstruction::pkg20_resource_adapter {

struct OpaqueTexture {
  std::uint8_t prefix[8];
  std::int32_t refcount;
};

struct TexturePtr {
  OpaqueTexture* value;
};

static_assert(sizeof(void*) == 4,
              "PKG-20 resource adapter pointers are 32-bit");
static_assert(offsetof(OpaqueTexture, refcount) == 0x08,
              "texture refcount offset");
static_assert(offsetof(TexturePtr, value) == 0x00,
              "texture pointer slot offset");

#if defined(_MSC_VER)
#define PKG20_RESOURCE_THISCALL __thiscall
#else
#define PKG20_RESOURCE_THISCALL __attribute__((thiscall))
#endif

void PKG20_RESOURCE_THISCALL TexturePtr_Set(TexturePtr* slot,
                                            OpaqueTexture* rhs);

#undef PKG20_RESOURCE_THISCALL

}
