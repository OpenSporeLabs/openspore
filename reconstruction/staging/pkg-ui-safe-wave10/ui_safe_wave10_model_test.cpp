#include <sys/wait.h>
#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "ui_safe_wave10.hpp"

namespace openspore::reconstruction::pkg_ui_safe_wave10 {
namespace {

#if defined(_MSC_VER)
#define PKG_UI_SAFE_TEST_CDECL __cdecl
#define PKG_UI_SAFE_TEST_THISCALL __thiscall
#else
#define PKG_UI_SAFE_TEST_CDECL __attribute__((cdecl))
#define PKG_UI_SAFE_TEST_THISCALL __attribute__((thiscall))
#endif

using DestructorSignature = OpaqueImageArchive*(
    PKG_UI_SAFE_TEST_THISCALL*)(OpaqueImageArchive*, TargetWord);

static_assert(
    std::is_same<decltype(&image_archive_scalar_deleting_destructor_00635700),
                 DestructorSignature>::value,
    "00635700 is thiscall with one explicit word popped by RET 4");
static_assert(std::is_same<decltype(OpaqueSlotVtablePort::release_04),
                           SlotReleasePort>::value,
              "the +0x04 handle port takes this only and returns void");
static_assert(std::is_same<decltype(ImageArchivePorts::service_destroy),
                           ServiceDestroyPort>::value,
              "the service port takes this only and returns void");
static_assert(std::is_same<decltype(ImageArchivePorts::deallocate),
                           DeallocatePort>::value,
              "the deallocation port takes one explicit word and returns void");
static_assert(sizeof(void*) == 4 && sizeof(TargetWord) == 4,
              "the destructor body is a 32-bit image archive");
static_assert(sizeof(OpaqueImageArchive) == 0x6c &&
                  offsetof(OpaqueImageArchive, service_14) == 0x14 &&
                  offsetof(OpaqueImageArchive, service_2c) == 0x2c &&
                  offsetof(OpaqueImageArchive, slot_64) == 0x64 &&
                  offsetof(OpaqueImageArchive, slot_68) == 0x68,
              "the torn handles and services keep their target offsets");
static_assert(offsetof(OpaqueSlotVtablePort, release_04) == 0x04,
              "the handle release port sits at handle vtable +0x04");
static_assert(kDerivedPrimaryVtable == 0x013fe728u &&
                  kDerivedSecondaryVtable == 0x013fe718u &&
                  kBaseSecondaryVtable == 0x013ec458u &&
                  kBasePrimaryVtable == 0x013eb938u,
              "the derived and base vtables keep their target addresses");

struct Event {
  const char* kind;
  const void* self;
};

std::vector<Event> events;
OpaqueImageArchive archive{};
OpaqueSlot late_slot{};
OpaqueSlot early_slot{};
OpaqueSlotVtablePort late_vtable{};
OpaqueSlotVtablePort early_vtable{};
int primary_seen_at_first_release = 0;
int secondary_seen_at_first_release = 0;
TargetWord primary_at_deallocate = 0;
TargetWord secondary_at_deallocate = 0;
std::uint32_t probe_result = 0;

void check(bool condition) {
  if (condition) {
    return;
  }
  std::fputs("check failed", stderr);
  for (const Event& event : events) {
    std::fprintf(stderr, " %s(%p)", event.kind,
                 static_cast<const void*>(event.self));
  }
  std::fputc('\n', stderr);
  std::abort();
}

void expect(std::initializer_list<const char*> expected) {
  check(events.size() == expected.size());
  std::size_t index = 0;
  for (const char* kind : expected) {
    check(std::strcmp(events[index].kind, kind) == 0);
    ++index;
  }
}

TargetWord word_of(const void* pointer) {
  return static_cast<TargetWord>(reinterpret_cast<std::uintptr_t>(pointer) &
                                 0xffffffffu);
}

OpaqueImageArchive* current_archive() { return &archive; }

void PKG_UI_SAFE_TEST_THISCALL record_release(OpaqueSlot* slot) {
  if (events.empty()) {
    primary_seen_at_first_release =
        static_cast<int>(word_of(archive.vtable_00));
    secondary_seen_at_first_release =
        static_cast<int>(word_of(archive.vtable_04));
  }
  events.push_back(Event{"release", slot});
}

void PKG_UI_SAFE_TEST_THISCALL record_destroy(OpaqueService24* service) {
  events.push_back(Event{"destroy", service});
}

void PKG_UI_SAFE_TEST_CDECL record_deallocate(void* pointer) {
  const OpaqueImageArchive* const victim =
      static_cast<const OpaqueImageArchive*>(pointer);
  primary_at_deallocate = word_of(victim->vtable_00);
  secondary_at_deallocate = word_of(victim->vtable_04);
  events.push_back(Event{"deallocate", pointer});
}

void reset_archive(bool with_late, bool with_early) {
  events.clear();
  primary_seen_at_first_release = 0;
  secondary_seen_at_first_release = 0;
  primary_at_deallocate = 0;
  secondary_at_deallocate = 0;
  std::memset(&archive, 0x5a, sizeof(archive));
  late_vtable = OpaqueSlotVtablePort{};
  early_vtable = OpaqueSlotVtablePort{};
  late_vtable.slot_00 = &late_slot;
  late_vtable.release_04 = record_release;
  early_vtable.slot_00 = &early_slot;
  early_vtable.release_04 = record_release;
  late_slot = OpaqueSlot{&late_vtable};
  early_slot = OpaqueSlot{&early_vtable};
  archive.vtable_00 = &late_slot;
  archive.vtable_04 = &early_slot;
  archive.slot_68 = with_late ? &late_slot : nullptr;
  archive.slot_64 = with_early ? &early_slot : nullptr;
  image_archive_set_ports(ImageArchivePorts{record_destroy, record_deallocate});
}

void test_release_and_destroy_order() {
  reset_archive(true, true);
  check(image_archive_scalar_deleting_destructor_00635700(&archive, 0u) ==
        &archive);
  expect({"release", "release", "destroy", "destroy"});
  check(events[0].self == &late_slot);
  check(events[1].self == &early_slot);
  check(events[2].self == &archive.service_2c);
  check(events[3].self == &archive.service_14);
  check(primary_seen_at_first_release == static_cast<int>(0x013fe728u));
  check(secondary_seen_at_first_release == static_cast<int>(0x013fe718u));
}

void test_vptr_teardown() {
  reset_archive(true, true);
  static_cast<void>(
      image_archive_scalar_deleting_destructor_00635700(&archive, 0u));
  check(word_of(archive.vtable_00) == 0x013eb938u);
  check(word_of(archive.vtable_04) == 0x013ec458u);
}

void test_null_handles_are_skipped() {
  reset_archive(true, false);
  static_cast<void>(
      image_archive_scalar_deleting_destructor_00635700(&archive, 0u));
  expect({"release", "destroy", "destroy"});
  check(events[0].self == &late_slot);

  reset_archive(false, true);
  static_cast<void>(
      image_archive_scalar_deleting_destructor_00635700(&archive, 0u));
  expect({"release", "destroy", "destroy"});
  check(events[0].self == &early_slot);

  reset_archive(false, false);
  check(image_archive_scalar_deleting_destructor_00635700(&archive, 0u) ==
        &archive);
  expect({"destroy", "destroy"});
  check(events[0].self == &archive.service_2c);
  check(events[1].self == &archive.service_14);
}

void test_bit_zero_delete_gate() {
  const TargetWord cases[] = {0x0u,  0x1u,  0x2u,       0x3u,
                              0x10u, 0x11u, 0xffffffffu};
  for (const TargetWord deleting : cases) {
    reset_archive(true, true);
    check(image_archive_scalar_deleting_destructor_00635700(
              &archive, deleting) == &archive);
    const bool expected = (deleting & 0x01u) != 0u;
    check(events.size() == (expected ? 5u : 4u));
    if (expected) {
      check(std::strcmp(events[4].kind, "deallocate") == 0);
      check(events[4].self == &archive);
      check(primary_at_deallocate == 0x013eb938u);
      check(secondary_at_deallocate == 0x013ec458u);
    }
  }
}

void test_returns_self_on_every_gate() {
  const TargetWord cases[] = {0x0u, 0x1u, 0x2u, 0x3u, 0xffffffffu};
  for (const TargetWord deleting : cases) {
    reset_archive(true, true);
    check(image_archive_scalar_deleting_destructor_00635700(
              &archive, deleting) == &archive);
  }
}

void test_body_outside_the_vptrs_is_untouched() {
  reset_archive(true, true);
  std::uint8_t before[sizeof(archive)];
  std::memcpy(before, &archive, sizeof(archive));
  static_cast<void>(
      image_archive_scalar_deleting_destructor_00635700(&archive, 0u));
  const std::uint8_t* const after =
      reinterpret_cast<const std::uint8_t*>(&archive);
  for (std::size_t offset = 0x08; offset < sizeof(archive); ++offset) {
    check(after[offset] == before[offset]);
  }
}

void test_default_ports_are_callable() {
  reset_archive(false, false);
  image_archive_reset_ports();
  check(image_archive_scalar_deleting_destructor_00635700(&archive, 0u) ==
        &archive);
  check(image_archive_scalar_deleting_destructor_00635700(&archive, 1u) ==
        &archive);
  check(events.size() == 0u);
  check(word_of(archive.vtable_00) == 0x013eb938u);
  image_archive_set_ports(ImageArchivePorts{record_destroy, record_deallocate});
}

void PKG_UI_SAFE_TEST_CDECL stack_probe(OpaqueImageArchive* target,
                                        TargetWord deleting,
                                        TargetWord guard_low,
                                        TargetWord guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const DestructorSignature entry =
      &image_archive_scalar_deleting_destructor_00635700;
  check(entry(target, deleting) == target);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_stack_discipline() {
  reset_archive(true, true);
  stack_probe(current_archive(), 1u, 0x11223344u, 0x55667788u);
  check(probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"release", "release", "destroy", "destroy", "deallocate"});
  check(word_of(archive.vtable_00) == 0x013eb938u);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_ui_safe_wave10;
  test_release_and_destroy_order();
  test_vptr_teardown();
  test_null_handles_are_skipped();
  test_bit_zero_delete_gate();
  test_returns_self_on_every_gate();
  test_body_outside_the_vptrs_is_untouched();
  test_default_ports_are_callable();
  test_stack_discipline();
  return 0;
}

#undef PKG_UI_SAFE_TEST_CDECL
#undef PKG_UI_SAFE_TEST_THISCALL
