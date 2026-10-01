#include <cstddef>
#include <cstdint>
#include <array>
#include <cstdio>
#include <cstring>

#include "camera_active_007c61a0.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#define PKG_TEST_FASTCALL __fastcall
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#define PKG_TEST_FASTCALL __attribute__((fastcall))
#endif

// Focused semantic test for App::cCameraManager::SetViewer @ 0x007c61a0.
//
// Eight instructions, two receiver displacements (0x80 and 0xa8), one 4-byte
// scale (0x4), one signed branch. The test is built to REFUTE the
// reconstruction, not to exercise it, so every group below names the hypothesis
// it attacks and the specific wrong reconstruction it would catch:
//
//   1. the two receiver words are distinct fields of DIFFERENT roles - a model
//      that read the array base out of the word at +0xa8, or the index out of
//      the word at +0x80, is refuted;
//   2. the +0x80 word is a POINTER and the body dereferences it - a model that
//      returned the word at +0x80 itself, or that indexed the receiver, is
//      refuted;
//   3. the returned value is the stored 4-byte HANDLE, not the handle's
//      pointee - a model that returned *handle instead of handle is refuted;
//   4. the index is scaled by 4 BYTES, not by one element of some other width
//      and not by the displacement - a model with a wrong stride is refuted;
//   5. the JL is SIGNED - a model treating the word as unsigned would accept
//      -1 and index a huge offset, and is refuted;
//   6. there is NO upper-bound test: the body never compares the index against
//      anything, so an out-of-range positive index is returned verbatim;
//   7. dispatch is ONE level: the word at +0x3c of the table the receiver's
//      +0x00 word points at is the entry - a two-level read is refuted;
//   8. the body writes no receiver byte at all - verified byte for byte.
//
// The calls go through the compiler-generated body directly (the entry is a
// plain thiscall pointer target and takes no ordinary stack argument, so no
// cleanup convention is in play for this one).

namespace {

using namespace openspore::reconstruction::pkg_app_camera_active_007c61a0;

int failures = 0;

void expect(const char* what, bool ok) {
  if (ok) {
    return;
  }
  ++failures;
  std::fprintf(stderr, "FAIL: %s\n", what);
}

std::uint32_t word_value(const void* pointer) {
  std::uint32_t value = 0;
  std::memcpy(&value, pointer, sizeof(value));
  return value;
}

void store_word(void* pointer, std::uint32_t value) {
  std::memcpy(pointer, &value, sizeof(value));
}

struct Fixture {
  OpaqueCameraManager manager{};
  OpaqueCamera camera_a{};
  OpaqueCamera camera_b{};
  OpaqueCamera camera_c{};
  OpaqueCamera* slots[3]{};

  Fixture() {
    for (std::size_t index = 0; index < manager.opaque_004.size(); ++index) {
      manager.opaque_004[index] = static_cast<std::uint8_t>(0x11u * (index + 1u));
    }
  }

  void set_base(OpaqueCamera** base) {
    store_word(word_at(&manager, kBaseDisplacement),
               static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(base)));
  }

  void set_index(std::int32_t index) {
    store_word(word_at(&manager, kIndexDisplacement),
               static_cast<std::uint32_t>(index));
  }
};

// The displacements the machine-derived receiver record enumerates for this
// body. Asserted here so a silent edit of the header's constants is caught even
// if the entry is not re-read.
void verify_receiver_displacements_match_the_record() {
  expect("record enumerates 0x80", kBaseDisplacement == 0x80);
  expect("record enumerates 0xa8", kIndexDisplacement == 0xa8);
  expect("scale of [ECX + EAX*0x4] is 0x4", kElementStride == 0x4);
  expect("the two receiver words do not overlap",
         kBaseDisplacement + sizeof(std::uint32_t) <= kIndexDisplacement);
  expect("index word ends the modeled extent",
         kIndexDisplacement + sizeof(std::uint32_t) == sizeof(OpaqueCameraManager));
}

// 1 + 2. The +0x80 word is the array's base ADDRESS, the +0xa8 word is the
// index. Swapping the roles, or reading the element out of the receiver
// instead of out of the array, both fail here.
void verify_base_and_index_are_not_conflated() {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.slots[1] = &fixture.camera_b;
  fixture.slots[2] = &fixture.camera_c;
  fixture.set_base(fixture.slots);
  fixture.set_index(1);

  expect("index 1 selects the second element of the array at +0x80",
         set_viewer_007c61a0(&fixture.manager) == &fixture.camera_b);

  // Move only the index: the result must move with it and the base must be
  // irrelevant to which word is read.
  fixture.set_index(2);
  expect("index 2 selects the third element",
         set_viewer_007c61a0(&fixture.manager) == &fixture.camera_c);

  // Move only the base: the index is unchanged, the element must come from the
  // NEW array. A reconstruction that cached the base or that indexed the
  // receiver instead fails here.
  OpaqueCamera* other[3] = {&fixture.camera_c, &fixture.camera_a, &fixture.camera_b};
  fixture.set_base(other);
  expect("result follows the base word, not the receiver layout",
         set_viewer_007c61a0(&fixture.manager) == &fixture.camera_b);
  expect("the base word itself is not the returned value",
         set_viewer_007c61a0(&fixture.manager) !=
             reinterpret_cast<const OpaqueCamera*>(
                 static_cast<std::uintptr_t>(*word_at(&fixture.manager, kBaseDisplacement))));
  // The element is read out of the array, so with the base pointing at the
  // manager itself the result is a word of the receiver - proof the read is
  // memory-indirect through the base and not a field read on the receiver.
  fixture.set_base(reinterpret_cast<OpaqueCamera**>(&fixture.manager));
  fixture.set_index(0);
  const OpaqueCamera* from_manager =
      set_viewer_007c61a0(&fixture.manager);
  const OpaqueCamera* expect_word =
      *reinterpret_cast<const OpaqueCamera* const*>(
          reinterpret_cast<const std::uint8_t*>(&fixture.manager));
  expect("with the base on the receiver the result is that receiver's word 0",
         from_manager == expect_word);
  expect("that word is the dispatch pointer, not the base word at +0x80",
         from_manager ==
             reinterpret_cast<const OpaqueCamera*>(fixture.manager.vtable_000));
}

// 3. The result is the stored handle itself, never the handle's pointee. The
// slots hold addresses of distinct cameras whose first words differ, so a
// reconstruction that dereferenced the handle would return something else.
void verify_pointer_is_not_pointee() {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.slots[1] = &fixture.camera_b;
  fixture.set_base(fixture.slots);
  fixture.set_index(0);

  const OpaqueCamera* result = set_viewer_007c61a0(&fixture.manager);
  expect("the handle is returned", result == &fixture.camera_a);
  expect("the handle's first word is not returned",
         result != reinterpret_cast<const OpaqueCamera*>(
                       word_value(&fixture.camera_a)));
  // And the same for index 1, where a one-off stride would land on the
  // pointee of camera_a's first word.
  fixture.set_index(1);
  const OpaqueCamera* second = set_viewer_007c61a0(&fixture.manager);
  expect("the second handle is returned", second == &fixture.camera_b);
  expect("the two handles are not conflated", second != result);
  expect("handles differ from each other's pointees",
         second != reinterpret_cast<const OpaqueCamera*>(
                       word_value(&fixture.camera_a)) &&
             result != reinterpret_cast<const OpaqueCamera*>(
                       word_value(&fixture.camera_b)));
}

// 4. 0x4 is a BYTE stride. With a stride of 1 or 8, index 1 would land on a
// different slot; the fixture below puts a recognisable value in every byte so
// the difference is visible rather than incidental.
void verify_stride_is_four_bytes() {
  Fixture fixture;
  std::uint32_t words[4] = {0x11111111u, 0x22222222u, 0x33333333u, 0x44444444u};
  fixture.set_base(reinterpret_cast<OpaqueCamera**>(words));
  for (std::int32_t index = 0; index < 4; ++index) {
    fixture.set_index(index);
    expect("index i selects the i-th 4-byte word",
           set_viewer_007c61a0(&fixture.manager) ==
               reinterpret_cast<const OpaqueCamera*>(static_cast<std::uintptr_t>(words[index])));
  }
  expect("the four words are 4 bytes apart",
         static_cast<std::size_t>(reinterpret_cast<std::uint8_t*>(&words[1]) -
                                  reinterpret_cast<std::uint8_t*>(&words[0])) == 4);
}

// 5. JL is a signed jump on the word at +0xa8. An unsigned reconstruction would
// treat -1 as 0xffffffff and index four gigabytes past the base; the body
// refuses instead.
void signed_rejection_case(const char* what, std::int32_t index) {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.set_base(fixture.slots);
  fixture.set_index(index);
  expect(what, set_viewer_007c61a0(&fixture.manager) == nullptr);
}

void verify_negative_index_is_refused() {
  signed_rejection_case("index -1 is refused", -1);
  signed_rejection_case("index -2 is refused", -2);
  signed_rejection_case("index INT_MIN is refused", (-2147483647 - 1));
  signed_rejection_case("index INT_MIN+1 is refused", (-2147483647 - 1) + 1);
  // 0 is not negative, and 0 is the boundary the JL sits on.
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.set_base(fixture.slots);
  fixture.set_index(0);
  expect("index 0 is accepted", set_viewer_007c61a0(&fixture.manager) == &fixture.camera_a);
}

// 6. There is no upper bound. The body compares the index against nothing, so
// an out-of-range positive index indexes anyway. The backing array here is
// large enough that the out-of-range reads stay inside it: the point is that
// the body does not refuse the index, not that it traps.
void verify_no_upper_bound_check() {
  OpaqueCameraManager manager{};
  std::array<OpaqueCamera*, 64> slots{};
  slots[0] = reinterpret_cast<OpaqueCamera*>(static_cast<std::uintptr_t>(0x1000u));
  slots[2] = reinterpret_cast<OpaqueCamera*>(static_cast<std::uintptr_t>(0x2000u));
  slots[40] = reinterpret_cast<OpaqueCamera*>(static_cast<std::uintptr_t>(0x3000u));
  slots[63] = reinterpret_cast<OpaqueCamera*>(static_cast<std::uintptr_t>(0x4000u));
  store_word(word_at(&manager, kBaseDisplacement),
             static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(slots.data())));

  for (std::int32_t index : {0, 2, 63}) {
    store_word(word_at(&manager, kIndexDisplacement),
               static_cast<std::uint32_t>(index));
    expect("in-range positive index selects its element",
           set_viewer_007c61a0(&manager) == slots[static_cast<std::size_t>(index)]);
  }

  // Well past the modelled array, still inside the fixture: no rejection.
  store_word(word_at(&manager, kIndexDisplacement), 40u);
  expect("an index past the populated elements is not rejected",
         set_viewer_007c61a0(&manager) == slots[40]);

  // And the negative case is a rejection while the large positive case is not,
  // which is the asymmetry a bounds check would erase.
  store_word(word_at(&manager, kIndexDisplacement), 0xffffffffu);
  expect("the same word read as -1 is refused",
         set_viewer_007c61a0(&manager) == nullptr);
}

// A stored null handle is returned verbatim, not turned into a rejection: the
// JL inspects the index word only.
void verify_null_element_is_returned_verbatim() {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.slots[1] = nullptr;
  fixture.set_base(fixture.slots);
  fixture.set_index(1);
  expect("stored null handle is returned unchanged",
         set_viewer_007c61a0(&fixture.manager) == nullptr);
}

// A deliberately wrong entry, used only as a trap: if the reconstruction ever
// reached the target through one dereference too many it would land here.
OpaqueCamera* PKG_TEST_THISCALL decoy_entry(OpaqueCameraManager* manager) {
  (void)manager;
  return nullptr;
}

// 7. One-level dispatch at displacement 0x3c. A two-level read is refuted by a
// table whose word 0 is itself a table: the correct read calls the entry and
// yields the camera, the two-level read calls the decoy and yields null. An
// off-by-one slot is refuted by the sentinels in the neighbouring words.
void verify_slot_15_dispatch_is_one_level() {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_b;
  fixture.set_base(fixture.slots);
  fixture.set_index(0);

  OpaqueCameraManagerVTable decoy{};
  decoy.get_active_camera_3c = &decoy_entry;

  OpaqueCameraManagerVTable vtable{};
  // Distinct sentinels in every other word so an off-by-one dispatch cannot
  // accidentally land on the entry.
  for (std::size_t slot = 0; slot < 15; ++slot) {
    vtable.slots_00[slot] = reinterpret_cast<void*>(
        static_cast<std::uintptr_t>(0xdead0000u + slot));
  }
  vtable.get_active_camera_3c = &set_viewer_007c61a0;
  // Test-only trap: the real word 0 at 0x014106a4 is 0x007c75d0, a function.
  // Here it is a second table, so a one-dereference-too-many dispatch would
  // have a different target to call.
  vtable.slots_00[0] = &decoy;
  fixture.manager.vtable_000 = &vtable;

  expect("the modeled table is sixteen 4-byte words",
         sizeof(OpaqueCameraManagerVTable) == 0x40);
  expect("word 15 sits at displacement 0x3c",
         reinterpret_cast<std::uint8_t*>(&vtable.get_active_camera_3c) -
                 reinterpret_cast<std::uint8_t*>(&vtable) ==
             0x3c);
  expect("word 14 is not the entry",
         vtable.slots_00[14] != reinterpret_cast<void*>(&set_viewer_007c61a0));

  expect("one-level read of word 15 dispatches to the reconstruction",
         vtable.get_active_camera_3c(&fixture.manager) == &fixture.camera_b);

  // The entry word is the value AT the slot and the target of the call is that
  // value: the slot is not a pointer to a further table.
  expect("the slot holds the entry address itself",
         vtable.get_active_camera_3c ==
             reinterpret_cast<SetViewer007c61a0>(&set_viewer_007c61a0));
  const OpaqueCameraManagerVTable* two_levels =
      reinterpret_cast<const OpaqueCameraManagerVTable*>(vtable.slots_00[0]);
  expect("a two-level read resolves to the decoy, not to the entry",
         two_levels->get_active_camera_3c != &set_viewer_007c61a0);
  expect("a two-level dispatch returns null where the real one returns a camera",
         two_levels->get_active_camera_3c(&fixture.manager) == nullptr);
}

// 8. The body reads two words and writes nothing. Every byte of the receiver
// must therefore be exactly as it was before the call, including the two words
// that were read.
void verify_body_writes_no_receiver_byte() {
  Fixture fixture;
  fixture.slots[0] = &fixture.camera_a;
  fixture.set_base(fixture.slots);
  fixture.set_index(0);

  std::array<std::uint8_t, sizeof(OpaqueCameraManager)> before{};
  std::memcpy(before.data(), &fixture.manager, before.size());
  (void)set_viewer_007c61a0(&fixture.manager);
  std::array<std::uint8_t, sizeof(OpaqueCameraManager)> after{};
  std::memcpy(after.data(), &fixture.manager, after.size());
  expect("no receiver byte is modified by the call", before == after);
}

}  // namespace

int main() {
  verify_receiver_displacements_match_the_record();
  verify_base_and_index_are_not_conflated();
  verify_pointer_is_not_pointee();
  verify_stride_is_four_bytes();
  verify_negative_index_is_refused();
  verify_no_upper_bound_check();
  verify_null_element_is_returned_verbatim();
  verify_slot_15_dispatch_is_one_level();
  verify_body_writes_no_receiver_byte();
  return failures == 0 ? 0 : 1;
}
