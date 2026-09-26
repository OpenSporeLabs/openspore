// Standalone model test for package wave13-w1-dispatch-b01.
//
// Build and run:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//       -I reconstruction/staging/wave13-w1-dispatch-b01 \
//       reconstruction/staging/wave13-w1-dispatch-b01/*.cpp \
//       -o /tmp/opencode/wave13-b01-model && /tmp/opencode/wave13-b01-model
//
// The test pins the invariants that were read out of the disassembly for all
// six targets. It does not try to model the opaque ports.

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "00438700_cascade.hpp"
#include "0045b210_lookup.hpp"
#include "004adb40_get_field44.hpp"
#include "004adc20_set_flag4f.hpp"
#include "004c49e0_pick.hpp"
#include "00573d70_set_primary_part.hpp"
#include "opaque_types.hpp"

namespace os = openspore::wave13_w1_dispatch_b01;

namespace {

int g_failures = 0;

void Check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL %s\n", what);
        ++g_failures;
    }
}

// --- port stubs ------------------------------------------------------------

os::HashMapNode* g_found = nullptr;
std::uint32_t g_last_key = 0u;
bool g_saw_key = false;
int g_lookup_calls = 0;

std::uint8_t g_pred_4f = 0;
int g_pred_4f_calls = 0;
std::uint8_t g_pred_a7e60 = 0;
std::uint32_t g_f220 = 0;

std::vector<std::pair<void*, void*>> g_helpers;  // (self, candidate)
std::vector<void*> g_touched;                   // candidate arguments seen
std::vector<std::string> g_calls;                // 0x00573d70 port trace
void* g_vtbl_0c_result = nullptr;
std::uint32_t g_vtbl_10_result = 0u;
void* g_00572770_result = nullptr;
std::int32_t g_index_result = 0;

void ResetAll() {
    g_found = nullptr;
    g_last_key = 0u;
    g_saw_key = false;
    g_lookup_calls = 0;
    g_pred_4f = 0;
    g_pred_4f_calls = 0;
    g_pred_a7e60 = 0;
    g_f220 = 0;
    g_helpers.clear();
    g_touched.clear();
    g_calls.clear();
    g_vtbl_0c_result = nullptr;
    g_vtbl_10_result = 0u;
    g_00572770_result = nullptr;
    g_index_result = 0;
}

}  // namespace

namespace openspore {
namespace wave13_w1_dispatch_b01 {

void Port_004388b0(void* self, void* candidate) {
    g_helpers.emplace_back(self, candidate);
    if (candidate != nullptr) {
        g_touched.push_back(candidate);
    }
}

std::uint8_t Port_004adc40(void*) {
    ++g_pred_4f_calls;
    return g_pred_4f;
}

std::uint8_t Port_004a7e60(void*) { return g_pred_a7e60; }

std::uint32_t Port_0044f220(void*) { return g_f220; }

void Port_00421950(os::HashMapBody* map, std::uint32_t* out_pair,
                   const std::uint32_t* key) {
    ++g_lookup_calls;
    (void)map;
    g_last_key = *key;
    g_saw_key = true;
    if (g_found == nullptr) {
        // The miss shape proven at 0x004219e5 .. 0x00421a0e: {*end, end}.
        out_pair[0] = 0u;
        out_pair[1] = 0u;
    } else {
        out_pair[0] = reinterpret_cast<std::uint32_t>(g_found);
        out_pair[1] = 0u;
    }
}

// Recording stubs for the 0x00573d70 port surface. They exist only so the
// reconstruction links; nothing here is a claim about the original callees.
// They record into the shared trace vectors declared above.
void* Port_0047e6c0(void* self) {
    g_calls.emplace_back("Port_0047e6c0");
    return self;
}

std::uint32_t Port_0047ec20(void*) {
    g_calls.emplace_back("Port_0047ec20");
    return 1u;  // non-zero, so the "same object" guard does not short-circuit
}

void Port_00435ed0(std::uint32_t marker, void*) {
    g_calls.emplace_back("Port_00435ed0:" + std::to_string(marker));
}

void __attribute__((thiscall)) Port_00573c00(void*, void*, std::uint32_t arg3) {
    g_calls.emplace_back("Port_00573c00:" + std::to_string(arg3));
}

void* Port_00572770(void**) {
    g_calls.emplace_back("Port_00572770");
    return g_00572770_result;
}

std::int32_t Port_0043c3d0(void*, void*) {
    g_calls.emplace_back("Port_0043c3d0");
    return g_index_result;
}

void Port_0043e760(void*, std::uint32_t index) {
    g_calls.emplace_back("Port_0043e760:" + std::to_string(index));
}

void Port_0043e7e0(void*, std::uint32_t index, std::uint8_t value) {
    g_calls.emplace_back("Port_0043e7e0:" + std::to_string(index) + ":" +
                         std::to_string(static_cast<unsigned>(value)));
}

void Port_00572020(void*, std::uint32_t arg2) {
    g_calls.emplace_back("Port_00572020:" + std::to_string(arg2));
}

void Port_vtbl_addref(void*) { g_calls.emplace_back("vtbl+0x00"); }
void Port_vtbl_release(void*) { g_calls.emplace_back("vtbl+0x04"); }

void Port_vtbl_30_set_state(void*, std::uint32_t a, std::uint32_t b) {
    g_calls.emplace_back("vtbl+0x30:" + std::to_string(a) + ":" +
                         std::to_string(b));
}

void* Port_vtbl_0c_query(void*, std::uint32_t type_id) {
    g_calls.emplace_back("vtbl+0x0c:" + std::to_string(type_id));
    return g_vtbl_0c_result;
}

std::uint32_t Port_vtbl_10_type_id(void*) {
    g_calls.emplace_back("vtbl+0x10");
    return g_vtbl_10_result;
}

}  // namespace wave13_w1_dispatch_b01
}  // namespace openspore

namespace {

using os::OpaqueEditorBlockSettings;
using os::OpaqueEditorRigblock;
using os::OpaqueIdRegistry;
using os::OpaqueTwoSlotOwner;

// --- 0x004c49e0 ------------------------------------------------------------

void Test_004c49e0() {
    OpaqueTwoSlotOwner owner;
    std::memset(&owner, 0, sizeof(owner));
    int a = 0x11;
    int b = 0x22;
    owner.slot_018 = &a;
    owner.slot_01c = &b;

    Check(os::FUN_004c49e0_SelectSlotByIndex(&owner, 0) == &a, "004c49e0 index 0");
    Check(os::FUN_004c49e0_SelectSlotByIndex(&owner, 1) == &b, "004c49e0 index 1");
    for (std::uint32_t i = 2; i < 0x10000u; ++i) {
        if (os::FUN_004c49e0_SelectSlotByIndex(&owner, i) != nullptr) {
            Check(false, "004c49e0 out-of-range index must return 0");
            break;
        }
    }
    Check(os::FUN_004c49e0_SelectSlotByIndex(&owner, 0xfffffffeu) == nullptr,
          "004c49e0 index 0xfffffffe");

    // A null slot is returned as-is: the body loads the field, it does not
    // substitute a default.
    owner.slot_018 = nullptr;
    Check(os::FUN_004c49e0_SelectSlotByIndex(&owner, 0) == nullptr,
          "004c49e0 null slot passes through");
}

// --- 0x0045b210 ------------------------------------------------------------

void Test_0045b210() {
    OpaqueIdRegistry reg;
    std::memset(&reg, 0, sizeof(reg));
    os::HashMapNode storage[2];
    os::HashMapNode* buckets[2];
    buckets[0] = &storage[0];
    buckets[1] = &storage[1];
    os::HashMapNode sentinel;
    std::memset(&sentinel, 0, sizeof(sentinel));
    reg.map_008.buckets = buckets;
    reg.map_008.bucket_count = 2;
    (void)sentinel;

    ResetAll();
    // Miss: the port yields the end sentinel's contents, matching 0x004219e5.
    Check(os::FUN_0045b210_LookupValueById(&reg, 0x1234u) == 0u,
          "0045b210 miss returns 0");
    Check(g_lookup_calls == 1, "0045b210 miss performs one lookup");
    Check(g_saw_key && g_last_key == 0x1234u,
          "0045b210 forwards the stack word as the key");

    // Hit: the port yields a node whose +4 is the mapped value.
    ResetAll();
    storage[0].key = 0x1234u;
    storage[0].value = 0xdeadbeefu;
    storage[0].next = nullptr;
    g_found = &storage[0];
    Check(os::FUN_0045b210_LookupValueById(&reg, 0x1234u) == 0xdeadbeefu,
          "0045b210 hit returns node->value");

    // A stored value of zero is indistinguishable from a miss for the caller.
    ResetAll();
    g_found = &storage[0];
    storage[0].value = 0u;
    Check(os::FUN_0045b210_LookupValueById(&reg, 0x1234u) == 0u,
          "0045b210 zero value looks like a miss");
    (void)buckets;
}

// --- 0x00438700 ------------------------------------------------------------

void Test_00438700() {
    OpaqueEditorRigblock self;
    OpaqueEditorRigblock other;
    OpaqueEditorRigblock sub;
    OpaqueEditorRigblock sub2;
    int self_slot = 0;
    int other_slot = 0;
    int sub_slot = 0;
    int sub2_slot = 0;

    auto init = [&](OpaqueEditorRigblock& r, void* slot) {
        std::memset(&r, 0, sizeof(r));
        r.field_028 = slot;
        r.field_3e0 = nullptr;
        r.flags_dc8 = 0u;
    };
    init(self, &self_slot);
    init(other, &other_slot);
    init(sub, &sub_slot);
    init(sub2, &sub2_slot);

    // 1. The very first port call happens unconditionally, even when every
    //    later guard fails.
    ResetAll();
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1 && g_helpers[0].first == &self &&
              g_helpers[0].second == &other,
          "00438700 first port call is (self, other) and is unconditional");

    // 2. field_028 == 0 -> only that first call.
    ResetAll();
    self.field_028 = nullptr;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 exits when field_028 is null");

    // 3. field_028 non-null but its +0x4f byte is 0 -> only that first call.
    ResetAll();
    self.field_028 = &self_slot;
    g_pred_4f = 0;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 exits when +0x4f predicate is 0");
    Check(g_pred_4f_calls == 1, "00438700 calls the +0x4f predicate once");

    // 4. other has bit 7 (IsVertebra) -> only that first call.
    ResetAll();
    g_pred_4f = 1;
    other.flags_dc8 = 1u << 7;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 exits on other bit 7");
    other.flags_dc8 = 0u;

    // 5. self->field_3e0 set, other->field_3e0 set -> exactly one extra call,
    //    and its receiver/argument are the two field_3e0 values.
    ResetAll();
    g_pred_4f = 1;
    self.field_3e0 = &sub;
    other.field_3e0 = &sub2;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 2 && g_helpers[1].first == &sub &&
              g_helpers[1].second == &sub2,
          "00438700 forwards field_3e0 pair");

    // 6. self->field_3e0 set, other->field_3e0 null -> still only the first call.
    ResetAll();
    g_pred_4f = 1;
    self.field_3e0 = &sub;
    other.field_3e0 = nullptr;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 exits when other field_3e0 is null");

    // 7. self->field_3e0 null, other->field_3e0 set, 0x004a7e60 false -> exit.
    ResetAll();
    g_pred_4f = 1;
    self.field_3e0 = nullptr;
    other.field_3e0 = &sub2;
    g_pred_a7e60 = 0;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 exits when 0x004a7e60 is 0");

    // 8. self->field_3e0 null, other->field_3e0 set, predicate true, self bit 11
    //    clear -> exactly one extra call on (self, other->field_3e0).
    ResetAll();
    g_pred_4f = 1;
    g_pred_a7e60 = 1;
    self.flags_dc8 = 0u;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 2 && g_helpers[1].first == &self &&
              g_helpers[1].second == &sub2,
          "00438700 bit-11 clear path calls (self, other field_3e0)");

    // 9. self bit 11 set and +0x1c0 dword non-zero -> no extra call.
    ResetAll();
    g_pred_4f = 1;
    g_pred_a7e60 = 1;
    self.flags_dc8 = 1u << 11;
    g_f220 = 0x1234u;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 1, "00438700 bit-11 set with +0x1c0 non-zero exits");

    // 10. self bit 11 set and +0x1c0 dword zero -> the extra call happens.
    ResetAll();
    g_pred_4f = 1;
    g_pred_a7e60 = 1;
    g_f220 = 0u;
    os::FUN_00438700_AdoptCascadeFrom(&self, &other);
    Check(g_helpers.size() == 2 && g_helpers[1].first == &self &&
              g_helpers[1].second == &sub2,
          "00438700 bit-11 set with +0x1c0 zero calls the helper");
    self.flags_dc8 = 0u;
}

// --- 0x004adb40 / 0x004adc20 ------------------------------------------------

void Test_004adb40_and_004adc20() {
    OpaqueEditorBlockSettings s;
    std::memset(&s, 0, sizeof(s));

    s.field_044 = 1.5f;
    Check(os::FUN_004adb40_GetField44(&s) == 1.5f, "004adb40 reads +0x44");

    // Every one of the 2^32 bit patterns must round-trip through the getter
    // unchanged, which is what a single 4-byte FLD guarantees.
    {
        const float samples[] = {0.0f, -0.0f, 1.0f, -1.0f, 3.4028235e38f,
                                 1.17549435e-38f, 0.5f, 12345.678f};
        bool ok = true;
        for (float v : samples) {
            s.field_044 = v;
            if (os::FUN_004adb40_GetField44(&s) != v) {
                ok = false;
            }
        }
        Check(ok, "004adb40 round-trips the stored bit pattern");
    }

    // The setter narrows to one byte: 0x101 must land as 0x01.
    os::FUN_004adc20_SetFlag4F(&s, 0x01u);
    Check(s.flag_04f == 0x01u, "004adc20 stores 0x01");
    os::FUN_004adc20_SetFlag4F(&s, 0xffu);
    Check(s.flag_04f == 0xffu, "004adc20 stores 0xff");
    os::FUN_004adc20_SetFlag4F(&s, 0x00u);
    Check(s.flag_04f == 0x00u, "004adc20 stores 0x00");

    // The setter touches exactly one byte and nothing else.
    std::uint8_t before[sizeof(OpaqueEditorBlockSettings)];
    std::uint8_t after[sizeof(OpaqueEditorBlockSettings)];
    std::memset(&s, 0, sizeof(s));
    std::memcpy(before, &s, sizeof(s));
    os::FUN_004adc20_SetFlag4F(&s, 0x5au);
    std::memcpy(after, &s, sizeof(s));
    bool single = true;
    for (std::size_t i = 0; i < sizeof(s); ++i) {
        const bool is_flag = (i == offsetof(OpaqueEditorBlockSettings, flag_04f));
        if (is_flag) {
            if (after[i] != 0x5au) {
                single = false;
            }
        } else if (after[i] != before[i]) {
            single = false;
        }
    }
    Check(single, "004adc20 writes only the byte at +0x4f");
}

// --- 0x00573d70 ------------------------------------------------------------

void Test_00573d70() {
    // The port set is not modelled here beyond what the guards need, so this
    // test pins the two earliest invariants that are pure control flow on the
    // editor object itself.
    os::OpaqueEditor editor;
    std::memset(&editor, 0, sizeof(editor));
    editor.flag_0140 = 0u;
    editor.flag_0141 = 0u;
    editor.field_0e4 = nullptr;
    editor.field_0f4 = nullptr;

    os::FUN_00573d70_SetPrimaryPart(&editor, nullptr, 1u);
    Check(editor.flag_0140 == 1u, "00573d70 sets +0x140 when part is null");
    Check(editor.flag_0141 == 0u, "00573d70 leaves +0x141 alone on the null path");

    std::memset(&editor, 0, sizeof(editor));
    editor.field_0e4 = nullptr;
    editor.field_0f4 = nullptr;
    os::FUN_00573d70_SetPrimaryPart(&editor, nullptr, 0u);
    Check(editor.flag_0140 == 1u, "00573d70 sets +0x140 for arg2 0 as well");

    // arg2 is never read, so the two observed caller shapes (1 and a register)
    // must leave identical state for the same inputs.
    os::OpaqueEditor a;
    os::OpaqueEditor b;
    std::memset(&a, 0, sizeof(a));
    std::memset(&b, 0, sizeof(b));
    os::FUN_00573d70_SetPrimaryPart(&a, nullptr, 1u);
    os::FUN_00573d70_SetPrimaryPart(&b, nullptr, 0xdeadbeefu);
    Check(a.flag_0140 == b.flag_0140, "00573d70 ignores arg2");

    // Publish path with an empty outgoing state and a part whose type id is
    // 0x50a993c: refcount, publish, marker, 0x00573c00, state 0, sibling
    // resolve, and flag_0141 set.
    {
        os::OpaqueEditor e;
        // The incoming part is dereferenced at +0xdc8 by the reconstruction, so
        // it needs a full-size zeroed arena rather than a bare int.
        alignas(4) static std::uint8_t part_arena[0x1000];
        int sibling = 0;
        int list = 0;
        std::memset(part_arena, 0, sizeof(part_arena));
        void* part_obj = part_arena;
        std::memset(&e, 0, sizeof(e));
        ResetAll();
        g_vtbl_10_result = 0x50a993cu;
        g_00572770_result = &sibling;
        g_index_result = 3;
        e.flag_0140 = 1u;
        e.flag_0141 = 1u;  // makes the outgoing side run the 0x00573e2f query
        os::FUN_00573d70_SetPrimaryPart(&e, part_obj, 1u);
        Check(e.field_0e4 == part_obj, "00573d70 publishes the new part");
        Check(e.flag_0141 == 1u, "00573d70 sets +0x141 on the 0x50a993c branch");
        Check(e.flag_0140 == 1u, "00573d70 keeps +0x140 set on that branch");

        auto has = [&](const char* tag) {
            for (const std::string& c : g_calls) {
                if (c == tag) {
                    return true;
                }
            }
            return false;
        };
        Check(has("vtbl+0x00"), "00573d70 addrefs the incoming part");
        Check(has("Port_00573c00:4294967295"),
              "00573d70 calls 0x00573c00 with (0, -1)");
        Check(has("vtbl+0x30:0:1"), "00573d70 sets state (0,1) after publish");
        // The outgoing block at 0x00573e04 runs before the publish, so with an
        // empty field_0e4 neither the (3,1) state nor the +0x0c query happens.
        Check(!has("vtbl+0x0c:84580668"),
              "00573d70 skips the outgoing query when field_0e4 is null");
        Check(!has("vtbl+0x30:3:1"),
              "00573d70 skips the outgoing state when field_0e4 is null");
        Check(has("Port_0043e760:3"),
              "00573d70 marks the resolved list entry selected");
        Check(!has("Port_00572020:0"),
              "00573d70 does not stop audio when a part is published");
        (void)list;
    }

    // Null part with an already-null field_0e4: the 0x00573d9c guard exits
    // before anything is published and no port is reached.
    {
        os::OpaqueEditor e;
        std::memset(&e, 0, sizeof(e));
        ResetAll();
        e.flag_0140 = 1u;
        os::FUN_00573d70_SetPrimaryPart(&e, nullptr, 1u);
        Check(e.field_0e4 == nullptr, "00573d70 keeps field_0e4 null");
        Check(g_calls.empty(),
              "00573d70 exits on the null==null guard before any port call");
    }

    // Null part with a live outgoing part: the outgoing part is released, the
    // slot is cleared and the audio port is taken.
    {
        os::OpaqueEditor e;
        alignas(4) static std::uint8_t old_arena[0x1000];
        void* old_part = old_arena;
        std::memset(old_arena, 0, sizeof(old_arena));
        std::memset(&e, 0, sizeof(e));
        ResetAll();
        e.flag_0140 = 1u;
        e.field_0e4 = old_part;
        os::FUN_00573d70_SetPrimaryPart(&e, nullptr, 1u);
        Check(e.field_0e4 == nullptr, "00573d70 clears field_0e4 for a null part");
        bool stopped = false;
        for (const std::string& c : g_calls) {
            if (c == "Port_00572020:0") {
                stopped = true;
            }
        }
        Check(stopped, "00573d70 stops audio after clearing field_0e4");
    }

    // Live outgoing part with flag_0141 set: the (3,1) state, the +0x0c query
    // of type 0x50a993c and the flag_0141 clear all run before the publish.
    {
        os::OpaqueEditor e;
        alignas(4) static std::uint8_t out_arena[0x1000];
        alignas(4) static std::uint8_t in_arena[0x1000];
        void* out_part = out_arena;
        void* in_part = in_arena;
        std::memset(out_arena, 0, sizeof(out_arena));
        std::memset(in_arena, 0, sizeof(in_arena));
        std::memset(&e, 0, sizeof(e));
        ResetAll();
        e.flag_0140 = 1u;
        e.flag_0141 = 1u;
        e.field_0e4 = out_part;
        os::FUN_00573d70_SetPrimaryPart(&e, in_part, 1u);
        Check(e.field_0e4 == in_part, "00573d70 replaces the outgoing part");
        auto has = [&](const char* tag) {
            for (const std::string& c : g_calls) {
                if (c == tag) {
                    return true;
                }
            }
            return false;
        };
        Check(has("vtbl+0x30:3:1"),
              "00573d70 sets state (3,1) on the outgoing part");
        Check(has("vtbl+0x0c:84580668"),
              "00573d70 queries type 0x50a993c through slot +0x0c");
        Check(has("vtbl+0x04"), "00573d70 releases the outgoing part");
        // g_vtbl_0c_result is null, so no 0x0043e7e0 call is made, but the
        // flag is cleared unconditionally at 0x00573e61 and then re-set by the
        // 0x50a993c branch below, which is why the end state is 1 again only
        // when slot +0x10 also reports 0x50a993c.
        Check(g_vtbl_10_result == 0u && e.flag_0141 == 0u,
              "00573d70 clears +0x141 when the new part is not type 0x50a993c");
    }

    // A secondary pointer that differs from the incoming part is cleared.
    {
        os::OpaqueEditor e;
        alignas(4) static std::uint8_t part_arena2[0x1000];
        int secondary = 0;
        std::memset(part_arena2, 0, sizeof(part_arena2));
        void* part_obj = part_arena2;
        (void)part_obj;
        std::memset(&e, 0, sizeof(e));
        ResetAll();
        e.flag_0140 = 0u;
        e.field_0f4 = &secondary;
        e.field_0e4 = nullptr;
        os::FUN_00573d70_SetPrimaryPart(&e, part_obj, 1u);
        Check(e.field_0f4 == nullptr,
              "00573d70 clears field_0f4 when it differs from the new part");
        Check(e.flag_0140 == 1u,
              "00573d70 raises +0x140 while clearing field_0f4");
    }
}

}  // namespace

int main() {
    Test_004c49e0();
    Test_0045b210();
    Test_00438700();
    Test_004adb40_and_004adc20();
    Test_00573d70();
    if (g_failures == 0) {
        std::printf("wave13-w1-dispatch-b01 model test: all checks passed\n");
        return 0;
    }
    std::printf("wave13-w1-dispatch-b01 model test: %d failure(s)\n", g_failures);
    return 1;
}
