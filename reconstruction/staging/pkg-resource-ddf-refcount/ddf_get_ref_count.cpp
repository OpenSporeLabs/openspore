#include "ddf_get_ref_count.hpp"

namespace openspore::reconstruction::pkg_resource_ddf_refcount {

extern "C" std::int32_t PKG_RESOURCE_DDF_THISCALL
Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(void* receiver) {
  auto* const base = static_cast<unsigned char*>(receiver);
  return __sync_fetch_and_add(reinterpret_cast<std::int32_t*>(base + 0x8), 0);
}

}  // namespace openspore::reconstruction::pkg_resource_ddf_refcount
