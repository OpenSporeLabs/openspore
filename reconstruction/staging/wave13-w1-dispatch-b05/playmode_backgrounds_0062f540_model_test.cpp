// Standalone model test for the 0x0062f540 reconstruction.
//
// Build (repo instruction form):
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       <this file> playmode_backgrounds_0062f540.cpp -o /tmp/opencode/0062f540-model
//   /tmp/opencode/0062f540-model
//
// The test provides bodies for the declared opaque ports and asserts the
// invariants that the disassembly proves.

#include "playmode_backgrounds_0062f540.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace openspore {
namespace dispatch_b05 {
namespace {

// --- observed test state ---------------------------------------------------

struct FakeWindow {
    void** vtable;                        // +0x00
    std::uint32_t pad_0004[0x1f];          // +0x04 .. +0x7f
    // slot +0x80 lives here
};

struct FakeWindowExtra {
    FakeWindow base;
    void (*slot_80)(const FakeWindow*, const char16_t*);  // +0x80
    std::uint32_t tail[0x0f];
};
static_assert(sizeof(FakeWindow) == 0x80, "slot +0x80 must be the 33rd dword");

// --- recorded effects ------------------------------------------------------

int g_ctor_calls = 0;
int g_dtor_calls = 0;
int g_set_localized_calls = 0;
std::uint32_t g_localized_id = 0;
std::uint32_t g_alternate_id = 0;
std::uint32_t g_debug_tag = 0;
int g_find_calls = 0;
void* g_find_receiver = nullptr;
std::uint32_t g_find_control_id = 0;
int g_caption_calls = 0;
std::uint32_t g_caption_count = 0;
const char16_t* g_last_caption = nullptr;

LocalizedArgTable0062f540 g_arg_table{};

IWindow0062f540* g_found_window = nullptr;
FakeWindowExtra g_window{};

void OnSlot80(const FakeWindow* self, const char16_t* caption) {
    assert(self != nullptr);
    ++g_caption_calls;
    g_caption_count += 1;
    g_last_caption = caption;
}

}  // namespace

// The global is a runtime-initialised pointer; the static image holds zero.
LocalizedArgTable0062f540* const g_localized_arg_table_015f7cf4 = &g_arg_table;

void LocalizedString0062f540_ctor006b5060(void* self) {
    assert(self != nullptr);
    std::memset(self, 0, 0x14);
    ++g_ctor_calls;
}

void LocalizedString0062f540_dtor006b5240(void* self) {
    assert(self != nullptr);
    std::memset(self, 0, 0x14);
    ++g_dtor_calls;
}

bool LocalizedString0062f540_set_localized006b54b0(
    void* self, std::uint32_t localization_id, std::uint32_t alternate_id,
    std::uint32_t debug_tag_wide_string) {
    assert(self != nullptr);
    ++g_set_localized_calls;
    g_localized_id = localization_id;
    g_alternate_id = alternate_id;
    g_debug_tag = debug_tag_wide_string;
    return true;
}

const char16_t* LocalizedString0062f540_resolve006b55c0(void* self) {
    assert(self != nullptr);
    return u"1/2";
}

IWindow0062f540* PlayModeUI0062f540_find_window_by_id00634dc0(
    void* play_mode_ui, std::uint32_t control_id) {
    ++g_find_calls;
    g_find_receiver = play_mode_ui;
    g_find_control_id = control_id;
    return reinterpret_cast<IWindow0062f540*>(g_found_window);
}

void IWindow0062f540_vslot80_set_caption(const IWindow0062f540* self,
                                         const char16_t* caption) {
    assert(self != nullptr);
    // Dispatch exactly through vtable slot +0x80, as 0x0062f59f/0x0062f5a8 do.
    void** const vtable = self->vtable;
    assert(vtable != nullptr);
    reinterpret_cast<void (*)(const FakeWindow*, const char16_t*)>(vtable[0x20])(
        reinterpret_cast<const FakeWindow*>(self), caption);
}

bool RunModelTest() {
    void* vtable[0x21] = {};
    vtable[0x20] = reinterpret_cast<void*>(&OnSlot80);
    g_window.base.vtable = vtable;
    g_window.slot_80 = &OnSlot80;
    g_found_window = reinterpret_cast<IWindow0062f540*>(&g_window);

    PlayModeBackgrounds0062f540 self{};
    self.field_34_play_mode_ui = reinterpret_cast<void*>(0x00c0ffeeu);
    self.field_38_page_index = 0;    // first page
    self.field_3c_page_count = 0;    // one page

    PlayModeBackgrounds_0062f540_UpdatePageNumbers(&self);

    // The lookup is always performed, and always with the receiver's +0x34 in ECX.
    assert(g_find_calls == 1);
    assert(g_find_receiver == self.field_34_play_mode_ui);
    assert(g_find_control_id == kControlIdBgPageCount);

    // Exactly one ctor/dtor pair, and the ctor precedes the dtor.
    assert(g_ctor_calls == 1);
    assert(g_dtor_calls == 1);

    // Both stores are the receiver's fields PLUS ONE (0x0062f584, 0x0062f590).
    assert(g_arg_table.field_20 == 1);
    assert(g_arg_table.field_24 == 1);

    // The three immediates are pushed in the observed order.
    assert(g_localized_id == kLocalizationIdPageCountFormat);
    assert(g_alternate_id == kAlternateIdPageCountFormat);
    assert(g_debug_tag == kDebugTagBgPageCount);

    // The resolved text reaches the window through slot +0x80 exactly once.
    assert(g_caption_calls == 1);
    assert(g_last_caption != nullptr);

    // A non-zero page index / count is forwarded with the same +1 bias.
    self.field_38_page_index = 4;
    self.field_3c_page_count = 9;
    PlayModeBackgrounds_0062f540_UpdatePageNumbers(&self);
    assert(g_arg_table.field_20 == 5);
    assert(g_arg_table.field_24 == 10);
    assert(g_ctor_calls == 2);
    assert(g_dtor_calls == 2);
    assert(g_caption_calls == 2);

    // Null lookup result: the guard at 0x0062f561 jumps to 0x0062f5aa, so the
    // localized-string setup, both global stores and the slot +0x80 call are all
    // skipped, while the ctor and dtor still run.
    g_found_window = nullptr;
    self.field_38_page_index = 7;
    self.field_3c_page_count = 7;
    g_arg_table.field_20 = 0x5a5a5a5a;
    g_arg_table.field_24 = 0x5a5a5a5a;
    PlayModeBackgrounds_0062f540_UpdatePageNumbers(&self);
    assert(g_ctor_calls == 3);
    assert(g_dtor_calls == 3);
    assert(g_set_localized_calls == 2);  // unchanged by the third call
    assert(g_caption_calls == 2);        // unchanged by the third call
    assert(g_arg_table.field_20 == 0x5a5a5a5a);
    assert(g_arg_table.field_24 == 0x5a5a5a5a);

    return true;
}

}  // namespace dispatch_b05
}  // namespace openspore

int main() {
    if (!openspore::dispatch_b05::RunModelTest()) {
        std::printf("0062f540 model test FAILED\n");
        return 1;
    }
    std::printf("0062f540 model test OK\n");
    return 0;
}
