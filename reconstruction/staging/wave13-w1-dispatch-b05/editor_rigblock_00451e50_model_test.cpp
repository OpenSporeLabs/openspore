// Standalone model test for the 0x00451e50 reconstruction.
//
// Build (repo instruction form):
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       <this file> editor_rigblock_00451e50.cpp -o /tmp/opencode/00451e50-model
//   /tmp/opencode/00451e50-model

#include "editor_rigblock_00451e50.hpp"

#include <cstdio>

namespace openspore {
namespace dispatch_b05 {
namespace {

int RunModelTest() {
    alignas(4) std::uint8_t raw_nested[0x80] = {};

    NestedRigblockValue00451e50* const nested =
        reinterpret_cast<NestedRigblockValue00451e50*>(raw_nested);

    Rigblock00451e50 self{};
    self.field_18c = nested;

    // The paired getter at 0x00451e90 returns field +0x38, or 0 when the
    // pointer is null. The model test drives the setter and reads the byte at
    // the exact observed offset +0x38.
    nested->field_38 = 0x5a5a5a5a;

    EditorRigblock_00451e50_SetNestedValue(&self, 0);
    if (nested->field_38 != 0) return 1;

    // 0x004ad4e0 walks a vector and passes index+1, so 1..N is the value domain
    // actually exercised by the observed callers.
    for (std::int32_t i = 1; i <= 5; ++i) {
        EditorRigblock_00451e50_SetNestedValue(&self, i);
        if (nested->field_38 != i) return 1;
    }

    // The store is a full 32-bit dword at +0x38, not a byte and not a pair of
    // bytes: verify the neighbouring dwords are untouched. Byte offset 0x38 is
    // dword index 0x0e.
    auto* const words = reinterpret_cast<std::uint32_t*>(raw_nested);
    if (words[0x0d] != 0 || words[0x0f] != 0) return 1;
    if (words[0x0e] != 5u) return 1;

    // Negative values are stored verbatim; the function performs no range check.
    EditorRigblock_00451e50_SetNestedValue(&self, -1);
    if (nested->field_38 != -1) return 1;

    // Null nested pointer: the guard at 0x00451e63 makes the call a no-op, and
    // crucially it does NOT write 0 over a previously stored value, because the
    // store is inside the guard.
    self.field_18c = nullptr;
    EditorRigblock_00451e50_SetNestedValue(&self, 0x7fffffff);
    if (nested->field_38 != -1) return 1;

    return 0;
}

}  // namespace
}  // namespace dispatch_b05
}  // namespace openspore

int main() {
    if (openspore::dispatch_b05::RunModelTest() != 0) {
        std::printf("00451e50 model test FAILED\n");
        return 1;
    }
    std::printf("00451e50 model test OK\n");
    return 0;
}
