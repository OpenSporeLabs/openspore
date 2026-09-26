// Model test for reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp
//
// The ports are stubbed so the reconstruction can run standalone. The test
// asserts the invariants that the original body establishes, all of them read
// from the disassembly at 0x005a9200.
//
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//       -I reconstruction/staging/wave13-w1-dispatch-b02 \
//       reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit.cpp \
//       reconstruction/staging/wave13-w1-dispatch-b02/a9200_editor_request_submit_model_test.cpp \
//       -o /tmp/opencode/005a9200-model && /tmp/opencode/005a9200-model

#include "a9200_editor_request_submit.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace openspore::wave13::b02 {
namespace {

int g_failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}

// ---- recorded port traffic -------------------------------------------------

std::uint32_t g_renderer_slot38_result = 0xdeadbeefu;
std::vector<std::uint32_t> g_notifications;   // message ids, in call order
std::vector<void*> g_notify_payloads;
std::uint32_t g_notify_arg3 = 1;              // must stay 1: the target never writes it
std::uint32_t g_probe_key = 0;                // 0x1003 pushed before 0x0067cab0
std::uint32_t g_progress_flags_arg1 = 0;      // 0x00d082675a, popped unread
std::uint32_t g_progress_mask = 0;            // the OR-ed mask
int g_progress_set_calls = 0;                 // -1 when the block is skipped
std::uint32_t g_alloc_size = 0;
int g_alloc_fail = 0;
std::int32_t g_resolved_editor_name = 0;
int g_resolver_calls = 0;
int g_addref_calls = 0;
int g_release_calls = 0;
std::uint32_t g_properties_0x118 = 0;

// The gate performs two dependent loads: [0x015fd918] then [+0x3c], then a
// byte test at [+0x118] of the second result. One zeroed page serves both.
std::uint8_t g_props_page[0x400];

void reset_props_page() {
    std::memset(g_props_page, 0, sizeof(g_props_page));
    *reinterpret_cast<void**>(g_props_page + 0x3c) = g_props_page + 0x100;
    g_app_properties_015fd918 = g_props_page;
}

void set_property_0x118(std::uint8_t value) {
    g_props_page[0x100 + 0x118] = value;
    g_properties_0x118 = value;
}

struct FakeRenderer {};
struct FakeAppSingleton {};

std::uint32_t fake_addref(void* self) {
    (void)self;
    ++g_addref_calls;
    return 1;
}
std::uint32_t fake_release(void* self) {
    (void)self;
    ++g_release_calls;
    return 0;
}

// vtable slot 0 is never reached; 1 and 2 are AddRef/Release.
void* g_fake_message_vtable_storage[3] = {
    reinterpret_cast<void*>(&fake_release), reinterpret_cast<void*>(&fake_addref),
    reinterpret_cast<void*>(&fake_release)};
alignas(16) std::uint8_t g_message_object[0x40] = {};

}  // namespace

// ---- port implementations --------------------------------------------------

const std::int32_t g_content_validation_s_illegal_characters[4] = {0x11111111, 0x22222222,
                                                                   0x33333333, 0x44444444};
void* g_app_properties_015fd918 = nullptr;

IRenderer* graphics_renderer_get_port() { return reinterpret_cast<IRenderer*>(&g_message_object[0]); }
std::uint32_t IRenderer_func38h_via_slot_38(IRenderer*) { return g_renderer_slot38_result; }

AppSingletonPort* app_singleton_get_port() { return reinterpret_cast<AppSingletonPort*>(&g_message_object[0]); }
void app_singleton_notify_slot_18(AppSingletonPort*, std::uint32_t message_id, void* payload, void* arg3,
                                 void* arg4) {
    g_notifications.push_back(message_id);
    g_notify_payloads.push_back(payload);
    if (arg3 != nullptr || arg4 != nullptr) {
        g_notify_arg3 = 0;
    }
}

void* app_object_allocate_port(std::uint32_t size, const char*, std::uint32_t, std::uint32_t, std::uint32_t,
                               std::uint32_t) {
    g_alloc_size = size;
    if (g_alloc_fail) {
        return nullptr;
    }
    std::memset(g_message_object, 0, sizeof(g_message_object));
    *reinterpret_cast<void**>(g_message_object) = g_fake_message_vtable_storage;
    return g_message_object;
}

std::int32_t resolve_editor_name_from_model_key(ResourceKey*) {
    ++g_resolver_calls;
    return g_resolved_editor_name;
}

void* global_015fcc50_get_port() { return reinterpret_cast<void*>(&g_message_object[0]); }
bool global_015fcc50_probe_1003(void*, std::uint32_t key) {
    g_probe_key = key;
    return false;  // discarded by the target
}

void* global_015fc250_get_port() { return reinterpret_cast<void*>(&g_message_object[0]); }
void set_progress_flags_slot(void*, std::uint32_t arg1_unused, std::uint32_t progress_flags, bool set_flag) {
    g_progress_flags_arg1 = arg1_unused;
    g_progress_mask = progress_flags;
    g_progress_set_calls = set_flag ? 1 : -1;
}

}  // namespace openspore::wave13::b02

// The reconstruction and its helper are declared in the .cpp; re-declare the
// entry point here so the test can drive it.
namespace openspore::wave13::b02 {
std::uint8_t FUN_005a9200_reconstruct(EditorRequest* request);
}

namespace openspore::wave13::b02 {
namespace {

// A second .cpp-visible entry point so the id table can be probed without
// driving the whole body: the observable effect is the mask handed to the
// progress-flags port, which is 1 << bit for the mapped ids.
std::uint32_t mask_for(std::int32_t editor_id) {
    EditorRequest req;
    std::memset(&req, 0, sizeof(req));
    req.mEditorName = editor_id;
    g_notifications.clear();
    g_progress_set_calls = 0;
    g_progress_mask = 0;
    g_resolver_calls = 0;
    g_addref_calls = 0;
    g_release_calls = 0;
    g_alloc_fail = 0;
    g_alloc_size = 0;
    g_probe_key = 0;
    g_properties_0x118 = 0;

    reset_props_page();

    const std::uint8_t rc = FUN_005a9200_reconstruct(&req);
    check(rc == 1, "return value is the byte 1");
    return g_progress_set_calls == 1 ? g_progress_mask : 0u;
}

}  // namespace
}  // namespace openspore::wave13::b02

int main() {
    using namespace openspore::wave13::b02;

    // --- the 34-way table, read off the original's CMP/JZ arms -------------
    // Every one of these is a single MOV ECX,<bit> in the listing.
    check(mask_for(0x96b24187) == 0x8000u, "0x96b24187 -> bit 0xf -> mask 0x8000");
    check(mask_for(0x9adf00a9) == 0x0100u, "0x9adf00a9 -> bit 0x8 -> mask 0x0100");
    check(mask_for(0x1d2ec0a0) == 0x0020u, "0x1d2ec0a0 -> bit 0x5 -> mask 0x0020");
    check(mask_for(0x1d2ec0a4) == 0x0020u, "0x1d2ec0a4 -> range low bound -> bit 0x5");
    check(mask_for(0x1d2ec0a7) == 0x0020u, "0x1d2ec0a7 -> range high bound -> bit 0x5");
    check(mask_for(0x1d2ec0a8) == 0u, "0x1d2ec0a8 is above the range and unmapped");
    check(mask_for(0x465c50ba) == 0x0040u, "0x465c50ba -> bit 0x6 -> mask 0x0040 (creature editor)");
    check(mask_for(0x247e2615) == 0x0080u, "0x247e2615 -> bit 0x7 -> mask 0x0080");
    check(mask_for(0x8707be7d) == 0x0200u, "0x8707be7d -> bit 0x9 -> mask 0x0200");
    check(mask_for(0x7d433fad) == 0x0400u, "0x7d433fad -> bit 0xa -> mask 0x0400");
    check(mask_for(0x8f963dcb) == 0x0800u, "0x8f963dcb -> bit 0xb -> mask 0x0800");
    check(mask_for(0x1a4e0708) == 0x1000u, "0x1a4e0708 -> bit 0xc -> mask 0x1000");
    check(mask_for(0xc15695da) == 0x2000u, "0xc15695da -> bit 0xd -> mask 0x2000");
    check(mask_for(0xa56567f7) == 0x4000u, "0xa56567f7 -> bit 0xe -> mask 0x4000");
    // Unmatched ids leave ECX at 0 and the block is skipped by TEST ECX,ECX.
    check(mask_for(0x00000000) == 0u, "id 0 is unmapped, no mask is set");
    check(mask_for(-1) == 0u, "a request whose name stayed -1 sets no mask");

    // --- the surrounding body ------------------------------------------------
    EditorRequest req;
    std::memset(&req, 0, sizeof(req));
    req.mEditorName = 0x465c50ba;  // not the -1 sentinel
    req.mEditableTests.flags[0] = 0x5a5a5a5a;
    g_resolver_calls = 0;
    g_notifications.clear();
    g_notify_payloads.clear();
    g_notify_arg3 = 1;
    g_progress_set_calls = 0;
    g_progress_mask = 0;
    g_progress_flags_arg1 = 0;
    g_probe_key = 0;
    g_alloc_size = 0;
    g_addref_calls = 0;
    g_release_calls = 0;
    g_renderer_slot38_result = 0x01654c10u;
    reset_props_page();

    check(FUN_005a9200_reconstruct(&req) == 1, "returns the byte 1");
    check(req.mCallingGameModeID == 0x01654c10u,
          "IRenderer slot +0x38 result is stored at mCallingGameModeID (+0x1c)");
    check(g_resolver_calls == 0, "a non -1 mEditorName is not re-resolved");
    check(req.mEditableTests.flags[0] == 0x5a5a5a5a,
          "a non-zero mEditableTests is left untouched");
    check(g_alloc_size == 0x40u, "the App message object is allocated with size 0x40");
    check(g_addref_calls == 1, "the message object's vtable slot +4 runs exactly once");
    check(g_release_calls == 1, "the message object's vtable slot +8 runs exactly once");
    check(g_probe_key == 0x1003u, "the 0x1003 pushed before 0x0067cab0 reaches 0x00801bb0");
    check(g_notifications.size() == 2, "two notifications are emitted");
    if (g_notifications.size() == 2) {
        check(g_notifications[0] == 0xb03bc30cu, "the first notification id is 0xb03bc30c");
        check(g_notify_payloads[0] == &req, "the first notification carries the request");
        check(g_notifications[1] == 0x00e11332u, "the second notification id is 0x00e11332");
        check(g_notify_payloads[1] == g_message_object, "the second carries the App message object");
    }
    check(g_notify_arg3 == 1, "the trailing two arguments are both null at every site");
    check(g_progress_flags_arg1 == 0x00d082675au, "the progress-flags first argument is 0x00d082675a");
    check(g_progress_set_calls == 1, "the progress-flag bit is set, not cleared");

    // --- the -1 sentinel and the four-dword seed ---------------------------
    std::memset(&req, 0, sizeof(req));
    req.mEditorName = -1;
    g_resolved_editor_name = 0x1a4e0708;
    g_resolver_calls = 0;
    g_notifications.clear();
    g_progress_set_calls = 0;
    g_progress_mask = 0;
    reset_props_page();

    check(FUN_005a9200_reconstruct(&req) == 1, "returns the byte 1 with the sentinel path");
    check(g_resolver_calls == 1, "the -1 sentinel triggers exactly one resolver call");
    check(req.mEditorName == 0x1a4e0708, "the resolved id is written back to +0x0c");
    check(req.mEditableTests.flags[0] == 0x11111111 && req.mEditableTests.flags[1] == 0x22222222 &&
              req.mEditableTests.flags[2] == 0x33333333 && req.mEditableTests.flags[3] == 0x44444444,
          "an all-zero mEditableTests is seeded from sIllegalCharacters");
    check(g_progress_mask == 0x1000u, "0x1a4e0708 then yields mask 0x1000");

    // --- the property gate suppresses the whole block ----------------------
    std::memset(&req, 0, sizeof(req));
    req.mEditorName = 0x465c50ba;
    g_progress_set_calls = 0;
    g_progress_mask = 0;
    set_property_0x118(1);
    check(FUN_005a9200_reconstruct(&req) == 1, "returns 1 even when the gate is closed");
    check(g_progress_set_calls == 0, "a non-zero App property at +0x118 skips the mask write");
    set_property_0x118(0);

    if (g_failures == 0) {
        std::printf("005a9200 model test: all checks passed\n");
        return 0;
    }
    std::printf("005a9200 model test: %d failure(s)\n", g_failures);
    return 1;
}
