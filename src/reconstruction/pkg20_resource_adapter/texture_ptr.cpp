#include "texture_ptr.hpp"

#if defined(_MSC_VER)
#define PKG20_RESOURCE_THISCALL __thiscall
#else
#define PKG20_RESOURCE_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg20_resource_adapter {

void PKG20_RESOURCE_THISCALL TexturePtr_Set(TexturePtr* slot,
                                            OpaqueTexture* rhs) {
  OpaqueTexture* old = slot->value;
  if (old == rhs) {
    return;
  }
  if (rhs != nullptr) {
    (void)__sync_fetch_and_add(&rhs->refcount, 1);
  }
  slot->value = rhs;
  if (old == nullptr) {
    return;
  }
  (void)__sync_fetch_and_add(&old->refcount, -1);
  const std::int32_t observed = __sync_fetch_and_add(&old->refcount, 0);
  if (observed < 1) {
    (void)__sync_fetch_and_add(&old->refcount, 1);
  }
}

#undef PKG20_RESOURCE_THISCALL

}
