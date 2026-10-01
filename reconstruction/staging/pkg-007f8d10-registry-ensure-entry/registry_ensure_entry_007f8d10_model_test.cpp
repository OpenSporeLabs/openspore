// Model test for 0x007f8d10 (registry_ensure_entry_007f8d10).
//
// It links the reconstruction against recording stubs for the six unresolved
// call targets and asserts the behaviour the 158-instruction listing pins down:
// both guards, the 0x88 stride and the count expression, the two-field match,
// the three ways a scan can end, the in-place append versus the grow route, the
// four-word prototype pre-initialisation, the prototype teardown order, the
// conditional key install with its displaced-handle release, the two constant
// words the new element ends up carrying, the callback argument tuples, and the
// final flag byte.
//
// The stubs are host models of UNRESOLVED call targets.  They are not
// reconstructions of the original callees; the observed contract of each is
// quoted in registry_ensure_entry_007f8d10.hpp.

#include "registry_ensure_entry_007f8d10.hpp"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace openspore::pkg_007f8d10 {
namespace {

int g_failures = 0;

struct Call {
    std::string name;
    std::uintptr_t a0;
    std::uintptr_t a1;
    double f2;
    double f3;
    std::uint32_t u4;
    std::uint32_t u5;
};

std::vector<Call> g_log;
std::vector<Proto> g_protos;
std::size_t g_place_calls = 0;
Handle* g_proto_after_00 = nullptr;
Handle* g_proto_after_14 = nullptr;

Handle* handle_at(std::uintptr_t v) {
    static std::uintptr_t slots[8];
    static Handle storage[8];
    for (std::size_t i = 0; i < 8; ++i) {
        if (slots[i] == v) {
            return &storage[i];
        }
        if (slots[i] == 0) {
            slots[i] = v;
            return &storage[i];
        }
    }
    return &storage[0];
}

void log(const char* name, std::uintptr_t a0 = 0, std::uintptr_t a1 = 0, double f2 = 0.0,
         double f3 = 0.0, std::uint32_t u4 = 0, std::uint32_t u5 = 0) {
    g_log.push_back(Call{name, a0, a1, f2, f3, u4, u5});
}

}  // namespace

// --- stubs: host models of the ports --------------------------------------

// 0x007f6d90.  Contract read back off its 34-instruction body.
void proto_copy_assign_007f6d90(void* dest, const void* src) noexcept {
    log("proto_copy_assign", reinterpret_cast<std::uintptr_t>(dest),
        reinterpret_cast<std::uintptr_t>(src));
    const auto* const proto = static_cast<const Proto*>(src);
    auto* const out = static_cast<Element*>(dest);
    out->key_00 = proto->handle_00;
    out->selector_04 = 0xccccccccu;  // stands in for the copied src+0x04
    out->sub_08.vtable_00 = kElementVtableA;
    out->sub_08.callback_04 = nullptr;  // stands in for the copied src+0x0c
    out->sub_08.vtable_08 = kElementVtableB;
    out->sub_08.handle_0c = proto->handle_14;
    std::memset(out->sub_08.body_10, 0x5a, sizeof out->sub_08.body_10);
    if (proto->handle_00 != nullptr) {
        handle_dispatch_slot0(proto->handle_00);
    }
    if (proto->handle_14 != nullptr) {
        handle_dispatch_slot0(proto->handle_14);
    }
}

// 0x007f8820.  The harness supplies a non-null sentinel in the slot so the
// install block's displaced-handle branch is exercised; that the grow route
// leaves a non-null key there is the open question recorded in the header, not
// a claim made here.
void registry_place_one_more_007f8820(Registry* self, const void* old_end,
                                      const void* proto) noexcept {
    log("registry_place_one_more", reinterpret_cast<std::uintptr_t>(self),
        reinterpret_cast<std::uintptr_t>(old_end));
    ++g_place_calls;
    g_protos.push_back(*static_cast<const Proto*>(proto));
    // 0x007f8820 hands &proto to 0x007f7920 with one argument and no visible
    // effect, so what that call leaves in the prototype is unresolved.  The
    // harness populates both handles so the teardown at 0x007f8e65/0x007f8e74
    // is exercised; that the handles can be non-null by then is the harness's
    // choice, not a claim about the original.
    auto* const live_proto = const_cast<Proto*>(static_cast<const Proto*>(proto));
    live_proto->handle_00 = handle_at(0x00aa0000u);
    live_proto->handle_14 = handle_at(0x00bb0000u);
    g_proto_after_00 = live_proto->handle_00;
    g_proto_after_14 = live_proto->handle_14;
    auto* const slot = static_cast<Element*>(const_cast<void*>(old_end));
    slot->key_00 = reinterpret_cast<void*>(0x00de0000u);  // harness sentinel
    self->end = static_cast<std::uint8_t*>(const_cast<void*>(old_end)) + kElementStride;
}

// 0x007f6ff0.  Contract read back off its body.
void element_assign_template_007f6ff0(ElementSub* self, const void* src) noexcept {
    log("element_assign_template", reinterpret_cast<std::uintptr_t>(self),
        reinterpret_cast<std::uintptr_t>(src));
    self->callback_04 = *reinterpret_cast<SubCallback const*>(
        static_cast<const std::uint8_t*>(src) + 0x04);
    auto* const incoming =
        *reinterpret_cast<Handle* const*>(static_cast<const std::uint8_t*>(src) + 0x0c);
    Handle* const displaced = self->handle_0c;
    if (incoming != displaced) {
        if (incoming != nullptr) {
            handle_dispatch_slot0(incoming);
        }
        self->handle_0c = incoming;
        if (displaced != nullptr) {
            handle_dispatch_slot1(displaced);
        }
    }
    std::memcpy(self->body_10, static_cast<const std::uint8_t*>(src) + 0x10, 0x70);
}

void handle_dispatch_slot0(Handle* self) noexcept {
    log("handle_slot0", reinterpret_cast<std::uintptr_t>(self));
}

void handle_dispatch_slot1(Handle* self) noexcept {
    log("handle_slot1", reinterpret_cast<std::uintptr_t>(self));
}

// The two dispatches at 0x007f8e35 and 0x007f8ed9 go through a data word the
// original loaded from the element; nothing in this repository names its
// callee, so the port is recorded rather than called.
void sub_dispatch_slot0(ElementSub* self, float arg2, float arg3, std::uint32_t arg4,
                        std::uint32_t arg5) noexcept {
    if (self->callback_04 == nullptr) {
        ++g_failures;
        std::printf("FAIL: dispatch through a null callback word\n");
        return;
    }
    log("sub_cb", reinterpret_cast<std::uintptr_t>(self),
        reinterpret_cast<std::uintptr_t>(self), static_cast<double>(arg2),
        static_cast<double>(arg3), arg4, arg5);
}

}  // namespace openspore::pkg_007f8d10

#include "registry_ensure_entry_007f8d10.cpp"

// ---------------------------------------------------------------------------

namespace {

using namespace openspore::pkg_007f8d10;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}

bool same(const std::vector<const char*>& want) {
    if (g_log.size() != want.size()) {
        std::printf("FAIL: call count %zu, expected %zu\n", g_log.size(), want.size());
        for (const auto& c : g_log) {
            std::printf("      got %s\n", c.name.c_str());
        }
        return false;
    }
    for (std::size_t i = 0; i < want.size(); ++i) {
        if (g_log[i].name != want[i]) {
            std::printf("FAIL: call %zu is %s, expected %s\n", i, g_log[i].name.c_str(),
                        want[i]);
            return false;
        }
    }
    return true;
}

constexpr std::size_t kSlots = 8;
alignas(16) std::uint8_t g_storage[kSlots * kElementStride];
Element* g_elements = nullptr;
Registry g_registry{};

void reset(std::size_t live, std::size_t capacity_slots) {
    g_log.clear();
    g_protos.clear();
    g_place_calls = 0;
    g_proto_after_00 = nullptr;
    g_proto_after_14 = nullptr;
    std::memset(g_storage, 0, sizeof g_storage);
    g_elements = reinterpret_cast<Element*>(g_storage);
    g_registry.alloc_base = g_storage;
    g_registry.begin = reinterpret_cast<std::uint8_t*>(g_elements);
    g_registry.end = g_registry.begin + live * kElementStride;
    g_registry.capacity = g_registry.begin + capacity_slots * kElementStride;
    g_registry.flag_1c = 0;
}

void put(std::size_t index, void* key, std::uint32_t selector) {
    g_elements[index].key_00 = key;
    g_elements[index].selector_04 = selector;
    g_elements[index].sub_08.callback_04 = reinterpret_cast<SubCallback>(0x00c0de00u);
}

// Argument 1.  0x007f6ff0 reads +0x04 and +0x0c and copies 0x70 bytes from
// +0x10, so it is at least 0x80 bytes.
struct Template {
    std::uint32_t pad_00;
    SubCallback callback_04;
    std::uint32_t pad_08;
    Handle* handle_0c;
    std::uint8_t body_10[0x70];
};
alignas(16) Template g_template{};

}  // namespace

int main() {
    g_template.callback_04 = reinterpret_cast<SubCallback>(0x00abc123u);
    g_template.handle_0c = handle_at(0x00c0ffeeu);
    std::memset(g_template.body_10, 0x3c, sizeof g_template.body_10);

    auto* const h0 = handle_at(0x1000u);
    auto* const h1 = handle_at(0x2000u);
    auto* const h2 = handle_at(0x3000u);

    // --- 1. struct geometry and constants ---------------------------------
    check(sizeof(Element) == 0x88, "element stride is 0x88");
    check(kElementStride == 136, "stride literal is 136");
    check(offsetof(Element, selector_04) == 0x04, "selector at +0x04");
    check(offsetof(Element, sub_08) == 0x08, "embedded object at +0x08");
    check(offsetof(ElementSub, callback_04) == 0x04, "dispatch word at sub+0x04");
    check(offsetof(ElementSub, handle_0c) == 0x0c, "retained word at sub+0x0c");
    check(offsetof(Registry, flag_1c) == 0x1c, "publish flag at receiver+0x1c");
    check(reinterpret_cast<std::uintptr_t>(kElementVtableA) == 0x013f6400u,
          "element vtable word +0x08 is 0x013f6400");
    check(reinterpret_cast<std::uintptr_t>(kElementVtableB) == 0x013f63fcu,
          "element vtable word +0x10 is 0x013f63fc");
    check(reinterpret_cast<std::uintptr_t>(kElementVtableA) ==
              reinterpret_cast<std::uintptr_t>(kElementVtableB) + 4u,
          "0x013f6400 is four bytes past the 0x013f63fc table");

    // --- 2. both guards are clean no-ops ----------------------------------
    reset(2, 4);
    put(0, h0, 7);
    put(1, h1, 8);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, nullptr, 8);
    check(same({}), "a null key dispatches nothing");
    check(g_registry.flag_1c == 0, "a null key does not publish");
    check(g_registry.end == g_registry.begin + 2 * kElementStride,
          "a null key does not grow");

    g_template.callback_04 = nullptr;
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h0, 7);
    check(same({}), "arg1->+4 == 0 dispatches nothing");
    check(g_registry.flag_1c == 0, "arg1->+4 == 0 does not publish");
    g_template.callback_04 = reinterpret_cast<SubCallback>(0x00abc123u);

    // --- 3. an allocated but empty container still clones -----------------
    // 0x007f8e0c tests the end POINTER against null, not end == begin, so an
    // empty-but-allocated buffer still runs the clone.
    reset(0, 4);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h0, 0x1234u);
    check(same({"proto_copy_assign", "handle_slot0", "element_assign_template", "handle_slot0",
                "sub_cb"}),
          "empty but allocated: clone, install, refresh (which retains the template "
          "handle), dispatch");
    check(g_place_calls == 0, "capacity was available, so the grow route was not taken");
    check(g_registry.end == g_registry.begin + kElementStride, "end advanced by one stride");
    check(g_elements[0].key_00 == h0, "the new element carries the key");
    check(g_elements[0].selector_04 == 0x1234u, "the new element carries the selector");
    check(g_registry.flag_1c == 1, "published");
    check(g_log[2].a0 == reinterpret_cast<std::uintptr_t>(&g_elements[0].sub_08),
          "the refresh targets element+0x08");
    check(g_log[2].a1 == reinterpret_cast<std::uintptr_t>(&g_template),
          "the refresh reads argument 1");
    check(g_log[3].a0 == reinterpret_cast<std::uintptr_t>(g_template.handle_0c),
          "0x007f6ff0 retained argument 1 + 0x0c into the slot");
    check(g_log[4].u4 == 0u && g_log[4].u5 == 0u, "the trailing callback passes (0, 0)");
    check(g_log[4].f2 == 0.0 && g_log[4].f3 == 0.0 && g_log[4].a1 == g_log[4].a0,
          "the trailing callback passes two 0.0f and the embedded object itself");

    // --- 4. the two constant words reach the element ----------------------
    check(reinterpret_cast<std::uintptr_t>(g_elements[0].sub_08.vtable_00) == 0x013f6400u,
          "element+0x08 holds 0x013f6400 after the in-place append");
    check(reinterpret_cast<std::uintptr_t>(g_elements[0].sub_08.vtable_08) == 0x013f63fcu,
          "element+0x10 holds 0x013f63fc after the in-place append");
    check(g_elements[0].sub_08.callback_04 == g_template.callback_04,
          "the dispatch word came from argument 1 + 0x04, not from the prototype");
    check(g_elements[0].sub_08.handle_0c == g_template.handle_0c,
          "the retained word came from argument 1 + 0x0c");
    check(std::memcmp(g_elements[0].sub_08.body_10, g_template.body_10, 0x70) == 0,
          "0x70 bytes were copied from argument 1 + 0x10");

    // --- 5. in-place append clones the prototype into the new slot --------
    reset(2, 4);
    put(0, h0, 7);
    put(1, h1, 8);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h2, 9);
    check(same({"proto_copy_assign", "handle_slot0", "element_assign_template", "handle_slot0",
                "sub_cb"}),
          "append with room: clone, install, refresh, dispatch");
    check(g_place_calls == 0, "the in-place route did not call the grow helper");
    check(g_elements[2].key_00 == h2, "the appended slot holds the new key");
    check(g_elements[2].selector_04 == 9, "the appended slot holds the selector");
    check(g_elements[0].key_00 == h0 && g_elements[1].key_00 == h1,
          "the two live slots are untouched");
    check(g_registry.end == g_registry.begin + 3 * kElementStride, "end advanced by 0x88");
    check(g_registry.flag_1c == 1, "published");

    // --- 6. the prototype carries exactly the four written words ----------
    reset(1, 1);  // end == capacity, so the grow route is taken
    put(0, h0, 7);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h1, 8);
    check(g_place_calls == 1, "end == capacity routed to the grow helper");
    check(g_protos.size() == 1, "the prototype reached the grow helper");
    if (g_protos.size() == 1) {
        check(g_protos[0].handle_00 == nullptr, "prototype +0x00 initialised to null");
        check(g_protos[0].handle_14 == nullptr, "prototype +0x14 initialised to null");
        check(reinterpret_cast<std::uintptr_t>(g_protos[0].vtable_08) == 0x013f6400u,
              "prototype +0x08 is 0x013f6400");
        check(reinterpret_cast<std::uintptr_t>(g_protos[0].vtable_10) == 0x013f63fcu,
              "prototype +0x10 is 0x013f63fc");
    }
    check(same({"registry_place_one_more", "handle_slot1", "handle_slot1", "handle_slot0",
                "handle_slot1", "element_assign_template", "handle_slot0", "sub_cb"}),
          "grow route: place, release the prototype at +0x14 then +0x00, retain the new "
          "key, release the displaced one, refresh, dispatch");
    check(g_log[1].a0 == reinterpret_cast<std::uintptr_t>(g_proto_after_14),
          "the prototype's +0x14 handle is released first");
    check(g_log[2].a0 == reinterpret_cast<std::uintptr_t>(g_proto_after_00),
          "the prototype's +0x00 handle is released second");

    // --- 7. a match on both fields refreshes in place ---------------------
    reset(3, 4);
    put(0, h0, 7);
    put(1, h1, 8);
    put(2, h2, 9);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h1, 8);
    // The install block is skipped entirely: the slot already holds this key, so
    // there is no retain and no release, only the refresh.
    check(same({"sub_cb", "element_assign_template", "handle_slot0", "sub_cb"}),
          "match: dispatch the element first, then refresh and dispatch again, with no "
          "key churn");
    check(g_log[0].u4 == 1u && g_log[0].u5 == 0u,
          "the matched dispatch passes (1, 0), not (0, 0)");
    check(g_log[0].f2 == 0.0 && g_log[0].f3 == 0.0,
          "both dispatches pass 0.0f twice");
    check(g_elements[1].key_00 == h1, "the matched slot keeps its key");
    check(g_elements[1].selector_04 == 8, "the matched slot keeps its selector");
    check(g_registry.end == g_registry.begin + 3 * kElementStride, "a match does not grow");
    check(g_elements[0].key_00 == h0 && g_elements[2].key_00 == h2,
          "the neighbouring slots are untouched");
    check(g_registry.flag_1c == 1, "a match publishes");

    // --- 8. the selector is part of the match -----------------------------
    reset(3, 4);
    put(0, h0, 7);
    put(1, h1, 8);
    put(2, h2, 9);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h1, 0x9999u);
    check(same({"proto_copy_assign", "handle_slot0", "element_assign_template", "handle_slot0",
                "sub_cb"}),
          "a key match with the wrong selector appends instead");
    check(g_elements[3].key_00 == h1, "the appended slot holds the key");
    check(g_elements[3].selector_04 == 0x9999u, "the appended slot took the new selector");
    check(g_elements[1].selector_04 == 8, "the old slot kept the old selector");
    check(g_elements[1].key_00 == h1, "the old slot kept the old key");

    // --- 9. a null key mid-scan reuses that slot, displacing nothing -------
    reset(3, 4);
    put(0, h0, 7);
    put(1, nullptr, 8);
    put(2, h2, 9);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h1, 8);
    check(same({"handle_slot0", "element_assign_template", "handle_slot0", "sub_cb"}),
          "a null key mid-scan reuses the slot with no clone and no key release");
    check(g_elements[1].key_00 == h1, "the null slot received the key");
    check(g_elements[2].key_00 == h2, "the scan did not run past the null slot");
    check(g_registry.end == g_registry.begin + 3 * kElementStride,
          "reusing a null slot does not grow");

    // --- 10. the in-place append displaces nothing ------------------------
    // The prototype's +0x00 is null, so the freshly cloned slot's key is null
    // and 0x007f8ea7 cannot fire on this route.  Assert that the sequence omits
    // the release, which is the observable consequence.
    reset(2, 4);
    put(0, h0, 7);
    put(1, h1, 8);
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h2, 8);
    bool released = false;
    for (const auto& c : g_log) {
        if (c.name == "handle_slot1") {
            released = true;
        }
    }
    check(!released, "the in-place append displaces no handle, so nothing is released");

    // --- 11. 0x007f6ff0 retains the incoming word and releases the old -----
    // Reuse the null-key slot, which is not cloned over, and give it a retained
    // word so the swap has something to displace.
    reset(3, 4);
    put(0, h0, 7);
    put(1, nullptr, 8);
    put(2, h2, 9);
    g_elements[1].sub_08.handle_0c = h2;
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h1, 11);
    check(same({"handle_slot0", "element_assign_template", "handle_slot0", "handle_slot1",
                "sub_cb"}),
          "0x007f6ff0 retains argument 1 + 0x0c and releases the word it displaced");
    check(g_log[2].a0 == reinterpret_cast<std::uintptr_t>(g_template.handle_0c),
          "the retained word is the template's");
    check(g_log[3].a0 == reinterpret_cast<std::uintptr_t>(h2),
          "the released word is the one already in the slot");
    check(g_elements[1].sub_08.handle_0c == g_template.handle_0c, "the slot holds the new one");

    // --- 12. the count is the raw (end - begin) / 0x88 --------------------
    // With end below begin the expression underflows to a huge unsigned count, so
    // the scan does NOT degenerate to zero and the install reuses slot 0 without
    // appending.  Reproduced because it is what the four magic divisions compute.
    reset(1, 1);
    g_registry.end = nullptr;
    g_registry.capacity = g_registry.begin + kElementStride;
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h0, 12);
    check(same({"handle_slot0", "element_assign_template", "handle_slot0", "sub_cb"}),
          "an end below begin underflows the count, so nothing is appended");
    check(g_registry.end == nullptr, "an end below begin is not repaired");
    check(g_elements[0].key_00 == h0, "slot 0 was reused instead");
    check(g_registry.flag_1c == 1, "still published");

    // --- 13. the count truncates rather than rounds or shifts -------------
    // 0x80 bytes is 0 elements by 0x88, and 1 by 0x80.  The machine listing
    // computes a truncating signed division, so the scan is skipped and the new
    // element lands at index 0.
    reset(0, 8);
    g_registry.end = g_registry.begin + 0x80;
    registry_ensure_entry_007f8d10(&g_registry, &g_template, h0, 13);
    check(same({"proto_copy_assign", "handle_slot0", "element_assign_template", "handle_slot0",
                "sub_cb"}),
          "0x80 bytes is zero elements of 0x88, so the element is appended at index 0");
    check(g_registry.end == g_registry.begin + 0x80 + kElementStride,
          "end advanced from the raw 0x80 offset by one stride");

    if (g_failures == 0) {
        std::printf("ok: 0x007f8d10 model test passed\n");
        return 0;
    }
    std::printf("%d failure(s)\n", g_failures);
    return 1;
}
