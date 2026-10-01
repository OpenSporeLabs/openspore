// Focused model test for the bounded reconstruction of
// Resource::DatabaseDirectoryFiles::GetRefCount (VA 0x0069d3f0).
//
// It pins the one behaviour the four-instruction body commits to: a locked
// 32-bit read of the word at receiver+0x8 that returns the prior value and
// leaves the word unchanged. It claims nothing about the surrounding layout --
// the test's own storage type is scaffolding, not a recovered struct.

#include <cassert>
#include <cstdint>

#include "ddf_get_ref_count.hpp"

namespace {

struct ModelStorage {
  unsigned char prefix[0x8];
  std::int32_t word;
};

}  // namespace

int main() {
  using openspore::reconstruction::pkg_resource_ddf_refcount::
      Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0;

  ModelStorage storage = {};
  storage.word = 1;

  assert(Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(&storage) == 1);
  assert(storage.word == 1);

  storage.word = 0;
  assert(Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(&storage) == 0);
  assert(storage.word == 0);

  storage.word = -7;
  assert(Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(&storage) ==
         -7);
  assert(storage.word == -7);

  storage.word = 2147483647;
  assert(Resource__DatabaseDirectoryFiles__GetRefCount_0069d3f0(&storage) ==
         2147483647);
  assert(storage.word == 2147483647);

  return 0;
}
