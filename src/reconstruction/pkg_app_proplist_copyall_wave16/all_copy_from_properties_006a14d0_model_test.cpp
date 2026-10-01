// PKG-APP-PROLIST-COPYALL-WAVE16 -- model test for VA 0x006a14d0,
// App::PropertyList::CopyAllPropertiesFrom.
//
// The three slots this body dispatches through are machine-observed but
// semantically unresolved, so this test supplies recording stubs with the
// observed calling surfaces and checks only what 0x006a14d0 ITSELF does:
//
//   1. the self-copy refusal (0x006a14d8 CMP / 0x006a14da JZ) -- nothing runs
//      at all, including no parent release;
//   2. the parent word is zeroed BEFORE the release is dispatched
//      (0x006a14e3 store, 0x006a14ef call), and the release's receiver is the
//      PARENT, not the child;
//   3. a null parent skips the store and the release entirely (0x006a14e1 JZ);
//   4. the three dispatches happen in the order release, clear, add -- and the
//      clear's receiver is the child;
//   5. the vtable word is re-read for the third dispatch, so a clear that
//      swaps the vtable changes which add-target is called
//      (0x006a14f1 vs 0x006a14fa);
//   6. the add dispatch passes `other` on the stack and the child in ECX.

#include "all_copy_from_properties_006a14d0.hpp"

#include <cstdio>
#include <cstring>

// The package's declarations now live in the namespace the promotion gate
// requires of the installed package. This test keeps its own definitions at
// global scope -- `main` is the process entry point and cannot be a member
// of a namespace -- and names the package's types through this directive,
// which is a lookup rule and changes no linkage.
using namespace openspore::reconstruction::pkg_app_proplist_copyall_wave16;

// The stubs below are free functions carrying an x86-32 thiscall convention
// (receiver in ECX), which is a non-class use of the attribute. GCC warns about
// exactly that; the warning is suppressed rather than the convention weakened.
// See the same guard in all_copy_from_properties_006a14d0.hpp.
#if !defined(_MSC_VER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#define PKG_TEST_THISCALL __attribute__((thiscall))
#else
#define PKG_TEST_THISCALL __thiscall
#endif

namespace {

// One entry per observed dispatch, recorded in order.
struct Event {
  // kAddA / kAddB are deliberately distinct: they stand for the two different
  // vtable images, whose slot +0x38 targets are the same address in the binary
  // but are separate function pointers here so the re-read can be observed.
  enum Kind { kRelease, kClear, kAddA, kAddB } kind;
  OpaquePropertyList *receiver;         // the ECX receiver of that call
  OpaquePropertyList *stack_arg;        // the pushed word, or null
  OpaquePropertyList *parent_at_call;   // receiver+0x30 as the callee saw it
  int vtable_generation;                // which vtable was live at the call
};

Event g_events[8];
int g_event_count = 0;
int g_vtable_generation = 0;

OpaquePropertyListVtable g_vtable_a;  // the "PropertyList" image
OpaquePropertyListVtable g_vtable_b;  // the "DirectPropertyList" image
OpaquePropertyListVtable g_vtable_swap; // same shape, but its clear rebinds

void record(Event::Kind kind, OpaquePropertyList *receiver,
            OpaquePropertyList *stack_arg) {
  if (g_event_count >= 8) {
    return;
  }
  Event &e = g_events[g_event_count++];
  e.kind = kind;
  e.receiver = receiver;
  e.stack_arg = stack_arg;
  // Snapshot the child's parent word at the moment of the call. This is what
  // distinguishes "detached before release" from "detached after".
  e.parent_at_call = receiver->parent_030;
  e.vtable_generation = g_vtable_generation;
}

// 0x00432b50 -- slot +0x04. Receiver only, no stack word. Returns a value the
// real body discards.
extern "C" void PKG_TEST_THISCALL release_stub(OpaquePropertyList *self) {
  record(Event::kRelease, self, nullptr);
  // The real 0x00432b50 decrements the dword at self+0x04 under LOCK/UNLOCK.
  // Reproduced so the test also shows the store lands on the PARENT.
  --self->opaque_004;
}

// 0x006a2a80 / 0x006a2b20 -- slot +0x48, the overridden Clear. Receiver only.
// Two distinct targets, because the two real vtable images put two different
// addresses in this slot.
extern "C" void PKG_TEST_THISCALL clear_stub_a(OpaquePropertyList *self) {
  record(Event::kClear, self, nullptr);
}

extern "C" void PKG_TEST_THISCALL clear_stub_b(OpaquePropertyList *self) {
  record(Event::kClear, self, nullptr);
}

// A third Clear that rebinds the receiver. The machine re-reads the receiver's
// vtable word at 0x006a14fa AFTER this call returns, so a clear that swaps the
// vtable must change which add-target is dispatched.
extern "C" void PKG_TEST_THISCALL clear_stub_swap(OpaquePropertyList *self) {
  record(Event::kClear, self, nullptr);
  self->vtable = &g_vtable_b;
  ++g_vtable_generation;
}

// 0x006a1510 -- slot +0x38, AddAllPropertiesFrom. One pushed word, child in ECX.
extern "C" void PKG_TEST_THISCALL add_stub_a(OpaquePropertyList *self,
                                                   OpaquePropertyList *other) {
  record(Event::kAddA, self, other);
}

extern "C" void PKG_TEST_THISCALL add_stub_b(OpaquePropertyList *self,
                                                   OpaquePropertyList *other) {
  record(Event::kAddB, self, other);
}

int g_failures = 0;

void check(bool condition, const char *what) {
  if (!condition) {
    ++g_failures;
    std::fprintf(stderr, "FAIL %s\n", what);
  }
}

void reset_events() {
  std::memset(g_events, 0, sizeof(g_events));
  g_event_count = 0;
  g_vtable_generation = 0;
}

void init_vtables() {
  std::memset(&g_vtable_a, 0, sizeof(g_vtable_a));
  std::memset(&g_vtable_b, 0, sizeof(g_vtable_b));
  std::memset(&g_vtable_swap, 0, sizeof(g_vtable_swap));
  g_vtable_a.release_04 = &release_stub;
  g_vtable_a.clear_048 = &clear_stub_a;
  g_vtable_a.add_all_properties_from_038 = &add_stub_a;
  g_vtable_b.release_04 = &release_stub;
  g_vtable_b.clear_048 = &clear_stub_b;
  g_vtable_b.add_all_properties_from_038 = &add_stub_b;
  g_vtable_swap.release_04 = &release_stub;
  g_vtable_swap.clear_048 = &clear_stub_swap;
  g_vtable_swap.add_all_properties_from_038 = &add_stub_a;
}

} // namespace

int main() {
  init_vtables();

  alignas(4) std::uint8_t child_bytes[sizeof(OpaquePropertyList)] = {};
  alignas(4) std::uint8_t other_bytes[sizeof(OpaquePropertyList)] = {};
  alignas(4) std::uint8_t parent_bytes[sizeof(OpaquePropertyList)] = {};

  auto *child = reinterpret_cast<OpaquePropertyList *>(child_bytes);
  auto *other = reinterpret_cast<OpaquePropertyList *>(other_bytes);
  auto *parent = reinterpret_cast<OpaquePropertyList *>(parent_bytes);

  parent->vtable = &g_vtable_a;
  child->vtable = &g_vtable_a;
  child->parent_030 = parent;
  // Distinct seeds, so "the release landed on the parent" is distinguishable
  // from "the release landed on the child".
  child->opaque_004 = 7U;
  parent->opaque_004 = 100U;

  // --- 1. self-copy: 0x006a14da JZ 0x006a1504 exits before anything. -------
  reset_events();
  all_copy_from_properties_006a14d0(child, child);
  check(g_event_count == 0, "self-copy must dispatch nothing at all");
  check(child->parent_030 == parent, "self-copy must not detach the parent");
  check(child->opaque_004 == 7U,
        "self-copy must not run the release on the parent");

  // --- 2. normal copy with a parent: detach, then release, then clear, add. -
  reset_events();
  all_copy_from_properties_006a14d0(child, other);
  check(g_event_count == 3, "a normal copy must dispatch exactly three times");

  if (g_event_count == 3) {
    check(g_events[0].kind == Event::kRelease,
          "0x006a14ef release must be dispatched first");
    check(g_events[1].kind == Event::kClear,
          "0x006a14f8 clear must be dispatched second");
    check(g_events[2].kind == Event::kAddA,
          "0x006a1502 add must be dispatched third");

    // The release's receiver is the PARENT (ECX still held the parent from
    // 0x006a14dc), not the child.
    check(g_events[0].receiver == parent,
          "slot +0x04 must be dispatched on the parent, not the child");
    check(g_events[0].stack_arg == nullptr,
          "slot +0x04 must push no stack word");
    // Ordering: the child was already detached when the release was entered.
    check(g_events[0].parent_at_call == nullptr,
          "the parent word must be zeroed BEFORE the release is dispatched");
  check(child->opaque_004 == 7U,
        "the release must land on the parent's word at +0x04, not the child's");
  check(parent->opaque_004 == 99U,
        "the release must decrement the parent's word at +0x04 by one");

    // The clear's receiver is the CHILD.
    check(g_events[1].receiver == child,
          "slot +0x48 must be dispatched on the child");
    check(g_events[1].stack_arg == nullptr,
          "slot +0x48 must push no stack word");
    check(g_events[1].parent_at_call == nullptr,
          "the child must still be detached when the clear is dispatched");

    // The add's receiver is the CHILD and its one stack word is `other`.
    check(g_events[2].receiver == child,
          "slot +0x38 must be dispatched on the child");
    check(g_events[2].stack_arg == other,
          "slot +0x38 must pass `other` as its single stack word");
  }
  check(child->parent_030 == nullptr,
        "the child must be left detached after the call");

  // --- 3. null parent: 0x006a14e1 JZ skips both the store and the release. --
  child->vtable = &g_vtable_a;
  child->parent_030 = nullptr;
  reset_events();
  all_copy_from_properties_006a14d0(child, other);
  check(g_event_count == 2, "a null parent must skip only the release");
  if (g_event_count == 2) {
    check(g_events[0].kind == Event::kClear,
          "with a null parent the clear is dispatched first");
    check(g_events[1].kind == Event::kAddA,
          "with a null parent the add is dispatched second");
  }
  check(child->parent_030 == nullptr, "a null parent leaves the word zeroed");

  // --- 4. the vtable is re-read: 0x006a14f1 vs 0x006a14fa. -----------------
  // The clear here is clear_stub_swap, which rebinds the child onto vtable B.
  // Because the body reads the vtable word a second time AFTER the clear
  // returns, the add must go to vtable B's add target (add_stub_b, kAddB),
  // not the one that was live on entry (add_stub_a, kAddA).
  child->vtable = &g_vtable_swap;
  child->parent_030 = nullptr;
  reset_events();
  all_copy_from_properties_006a14d0(child, other);
  check(g_event_count == 2, "the re-read case must still dispatch twice");
  if (g_event_count == 2) {
    check(g_events[0].kind == Event::kClear,
          "the clear must be bound from the vtable live on entry");
    check(g_events[0].vtable_generation == 0,
          "the clear must be dispatched before the vtable changes");
    check(g_events[1].kind == Event::kAddB,
          "the add must be bound from the vtable re-read after the clear "
          "returned, so a clear that swaps the vtable must retarget it");
    check(g_events[1].vtable_generation == 1,
          "the add must be dispatched after the vtable change");
  }

  // --- 5. overlapping-but-distinct arguments are not excluded by the body. --
  // The only refused case is exact identity. The body performs no alias or
  // range test, so a child and an `other` that share storage must still run
  // the full sequence rather than being refused.
  child->vtable = &g_vtable_a;
  child->parent_030 = nullptr;
  reset_events();
  auto *overlapping = reinterpret_cast<OpaquePropertyList *>(
      reinterpret_cast<unsigned char *>(child) + 4);
  all_copy_from_properties_006a14d0(child, overlapping);
  check(g_event_count == 2,
        "a non-identical but overlapping argument must not be refused");

  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::printf("006a14d0 model test: all checks passed\n");
  return 0;
}


#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

#undef PKG_TEST_THISCALL
