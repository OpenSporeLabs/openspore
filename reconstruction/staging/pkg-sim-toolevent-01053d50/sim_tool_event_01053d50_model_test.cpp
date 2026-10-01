#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>
#include <vector>

#include "sim_tool_event_01053d50.hpp"

#if defined(_MSC_VER)
#define TEST_THISCALL __thiscall
#define TEST_CDECL __cdecl
#else
#define TEST_THISCALL __attribute__((thiscall))
#define TEST_CDECL __attribute__((cdecl))
#endif

// Behavioural model test for 0x01053d50
// (the receiver table's slot 8, PTR_FUN_014367b0 + 0x20).
//
// Four direct callees are defined here as observers, so the test sees every
// transfer the reconstruction makes, with which addresses and in which order.
//
// The test is built to try to REFUTE the reconstruction. Each group names the
// wrong reconstruction it is aimed at:
//
//   1  FRAME LAYOUT. The transform the init, the post and the release are given
//      is the SAME address, and it is 0x10 ABOVE the frame base the init is
//      handed as its second word. A reconstruction that passed the frame base
//      where the transform goes (or the transform where the base goes) is
//      refuted, and so is one that passed the caller's `position` as the
//      transform.
//   2  THE 0x40 RESERVATION IS EXACTLY FILLED: 0x10 + 0x30 == 0x40. A
//      reconstruction that placed the transform anywhere else would either
//      overhang the reservation or leave a hole, and both are refuted here.
//   3  VTABLE DEPTH. One level: the receiver's word at displacement 0 is the
//      table, and the word at displacement 0x4c of THAT is the target. A
//      two-level read is refuted by a decoy table planted at the table's word 0.
//   4  SLOT DISPLACEMENT. Exactly 0x4c. The neighbouring words 0x48 and 0x50
//      are loaded with decoys and must never be selected.
//   5  ARGUMENT IDENTITY AND ORDER. The forward receives (receiver, the entry's
//      FIRST stack word, the entry's SECOND), the post receives (singleton,
//      0x5dce504a, transform, 0x0), and the init receives (transform, the
//      entry's second stack word, the frame base) - the pushed order is
//      right-to-left and getting it backwards is refuted.
//   6  THE FORWARD'S RESULT IS DISCARDED. Two different return values produce
//      the same downstream behaviour, so a reconstruction that branched on it
//      is refuted.
//   7  ABI. `RET 0x8`: the callee owns the two argument words. Measured by
//      sampling ESP inside a trampoline, not asserted as a convention.
//
// What is NOT asserted: the four observers' own behaviour is a fixture, not a
// claim about 0x00ad79d0, 0x00ae09b0, 0x00b3d4d0 or 0x00ad7ad0. Where a check
// says what an observer wrote, it is describing the fixture.

namespace openspore::reconstruction::pkg_sim_toolevent_01053d50 {

struct alignas(4) OpaqueCSpaceTrading {
  Word tag;
};

namespace {

using ExpectedEntryAbi = void(TEST_THISCALL*)(OpaqueToolEventReceiver*, void*,
                                              const OpaqueVector3*);
using ExpectedInitAbi = void(TEST_THISCALL*)(OpaqueTransform48*,
                                             const OpaqueVector3*,
                                             const OpaqueQuaternion16*);
using ExpectedPostAbi = void(TEST_THISCALL*)(OpaqueCSpaceTrading*, Word,
                                             const OpaqueTransform48*, Word);
using ExpectedGetAbi = OpaqueCSpaceTrading*(TEST_CDECL*)();
using ExpectedReleaseAbi = void(TEST_THISCALL*)(OpaqueTransform48*);
using ExpectedForwardAbi = Word(TEST_THISCALL*)(OpaqueToolEventReceiver*, void*,
                                                const OpaqueVector3*);

static_assert(
    std::is_same<decltype(&sim_toolevent_slot8_fun_01053d50),
                 ExpectedEntryAbi>::value,
    "entry is a thiscall member-shaped function with two callee-popped words");
static_assert(std::is_same<decltype(NativePorts::transform_init_00ad79d0),
                           ExpectedInitAbi>::value,
              "init port ABI");
static_assert(std::is_same<decltype(NativePorts::object_context_post_00ae09b0),
                           ExpectedPostAbi>::value,
              "object-context post port ABI");
static_assert(std::is_same<decltype(NativePorts::cspace_trading_get_00b3d4d0),
                           ExpectedGetAbi>::value,
              "singleton accessor port ABI");
static_assert(std::is_same<decltype(NativePorts::transform_release_00ad7ad0),
                           ExpectedReleaseAbi>::value,
              "release port ABI");
static_assert(std::is_same<decltype(OpaqueToolEventVTable::forward_4c),
                           ExpectedForwardAbi>::value,
              "forward slot ABI");
static_assert(sizeof(decltype(&sim_toolevent_slot8_fun_01053d50)) == 4,
              "entry pointer width");
static_assert(kTargetVa == 0x01053d50u, "target VA constant");
static_assert(kForwardSlotOffset == 76u, "forward slot byte offset constant");
static_assert(kForwardSlotIndex * sizeof(void*) == kForwardSlotOffset,
              "the forward slot is the 20th word of the table");
static_assert(kTransformFrameOffset + kTransformBytes == kFrameReserveBytes,
              "the 48-byte transform fills the 0x40 reservation from +0x10");

int failures = 0;
std::vector<std::string> events;
OpaqueCSpaceTrading trading_singleton{0x0167eb50u};
OpaqueCSpaceTrading* trading_result = &trading_singleton;

// The magic the init observer paints over the 0x30 bytes it is given. The post
// and the release observers read it back, which is how the test shows all three
// were handed the same 48 bytes rather than three addresses that merely look
// alike.
constexpr std::uint8_t kTransformMagic = 0x5a;

OpaqueTransform48* init_this = nullptr;
OpaqueVector3 const* init_arg1 = nullptr;
OpaqueQuaternion16 const* init_arg2 = nullptr;
OpaqueCSpaceTrading* post_receiver = nullptr;
Word post_group = 0u;
OpaqueTransform48 const* post_frame_address = nullptr;
Word post_instance = 0u;
std::uint8_t post_first_byte = 0u;
OpaqueTransform48* release_frame_address = nullptr;
std::uint8_t release_first_byte = 0u;
OpaqueToolEventReceiver* forward_receiver = nullptr;
void* forward_argument = nullptr;
OpaqueVector3 const* forward_position_address = nullptr;
Word forward_result = 0u;
Word forward_result_mode = 0xffffffffu;
Word owner_release_count = 0u;

void TEST_THISCALL model_transform_init_00ad79d0(
    OpaqueTransform48* frame, const OpaqueVector3* position,
    const OpaqueQuaternion16* rotation) {
  events.push_back("init");
  init_this = frame;
  init_arg1 = position;
  init_arg2 = rotation;
  // The observer paints the 0x30 bytes it was handed. It does not read the
  // position or the rotation: the body only passes them on, and what it passes
  // is what the test checks.
  (void)position;
  (void)rotation;
  // Everything up to the owner word, which the release observer follows; the
  // owner word is left null, which is the state a fresh transform is in.
  std::memset(frame, kTransformMagic, kOwnerOffset);
  frame->owner_2c = nullptr;
}

void TEST_THISCALL model_transform_release_00ad7ad0(OpaqueTransform48* frame) {
  events.push_back("release");
  release_frame_address = frame;
  release_first_byte = *reinterpret_cast<const std::uint8_t*>(frame);
  auto* owner = static_cast<OpaqueOwner*>(frame->owner_2c);
  if (owner != nullptr) {
    owner->vtable_00->release_c0(owner);
    frame->owner_2c = nullptr;
  }
}

OpaqueCSpaceTrading* TEST_CDECL model_cspace_trading_get_00b3d4d0() {
  events.push_back("get");
  return trading_result;
}

void TEST_THISCALL model_object_context_post_00ae09b0(
    OpaqueCSpaceTrading* receiver, Word group, const OpaqueTransform48* frame,
    Word instance) {
  events.push_back("post");
  post_receiver = receiver;
  post_group = group;
  post_frame_address = frame;
  post_instance = instance;
  post_first_byte = *reinterpret_cast<const std::uint8_t*>(frame);
}

Word TEST_THISCALL record_forward(OpaqueToolEventReceiver* receiver,
                                  void* event_argument,
                                  const OpaqueVector3* position) {
  events.push_back("forward");
  forward_receiver = receiver;
  forward_argument = event_argument;
  forward_position_address = position;
  forward_result = forward_result_mode;
  return forward_result;
}

Word TEST_THISCALL other_forward(OpaqueToolEventReceiver*, void*,
                                 const OpaqueVector3*) {
  events.push_back("other_forward");
  return 7u;
}

void TEST_THISCALL record_owner_release(void* owner) {
  ++owner_release_count;
  auto* typed = static_cast<OpaqueOwner*>(owner);
  typed->refcount_08 = 1u;
}

OpaqueOwnerVTable owner_vtable{};
OpaqueToolEventVTable receiver_vtable{};
OpaqueToolEventVTable alternate_vtable{};
OpaqueToolEventVTable decoy_table{};
OpaqueToolEventReceiver receiver{};
OpaqueToolEventReceiver alternate_receiver{};
OpaqueVector3 position{};

void set_receiver_table(OpaqueToolEventReceiver* target,
                        const OpaqueToolEventVTable* table) {
  const std::uint32_t word =
      static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(table));
  std::memcpy(word_at(target, kReceiverTableDisplacement), &word, sizeof word);
}

void reset_state() {
  events.clear();
  init_this = nullptr;
  init_arg1 = nullptr;
  init_arg2 = nullptr;
  post_receiver = nullptr;
  post_group = 0u;
  post_frame_address = nullptr;
  post_instance = 0u;
  post_first_byte = 0u;
  release_frame_address = nullptr;
  release_first_byte = 0u;
  forward_receiver = nullptr;
  forward_argument = nullptr;
  forward_position_address = nullptr;
  forward_result = 0u;
  forward_result_mode = 0xffffffffu;
  owner_release_count = 0u;
  trading_result = &trading_singleton;
  position.x = 1.0f;
  position.y = 2.0f;
  position.z = 3.0f;
}

void check(bool condition, const std::string& label) {
  if (!condition) {
    ++failures;
    std::printf("FAIL %s\n", label.c_str());
  } else {
    std::printf("ok   %s\n", label.c_str());
  }
}

// ESP, sampled from inside a balanced call of its own. Two samples taken this
// way are at the same depth in the caller, so any difference between them is
// the callee's own doing.
__attribute__((noinline)) std::uint32_t sample_stack_pointer() {
  std::uint32_t value = 0;
  __asm__ __volatile__("movl %%esp, %0" : "=r"(value));
  return value;
}

bool same_events(const char* const* expected, std::size_t count) {
  if (events.size() != count) {
    return false;
  }
  for (std::size_t index = 0; index < count; ++index) {
    if (events[index] != expected[index]) {
      return false;
    }
  }
  return true;
}

const char* const kStraightLine[] = {"init", "get", "post", "forward", "release"};

}

int run_tests() {
  owner_vtable.slots_00[46] = nullptr;
  owner_vtable.add_ref_bc = nullptr;
  owner_vtable.release_c0 = &record_owner_release;
  receiver_vtable.forward_4c = &record_forward;
  alternate_vtable.forward_4c = &other_forward;
  set_receiver_table(&receiver, &receiver_vtable);
  set_receiver_table(&alternate_receiver, &alternate_vtable);

  g_sim_toolevent_01053d50_ports.transform_init_00ad79d0 =
      &model_transform_init_00ad79d0;
  g_sim_toolevent_01053d50_ports.transform_release_00ad7ad0 =
      &model_transform_release_00ad7ad0;
  g_sim_toolevent_01053d50_ports.cspace_trading_get_00b3d4d0 =
      &model_cspace_trading_get_00b3d4d0;
  g_sim_toolevent_01053d50_ports.object_context_post_00ae09b0 =
      &model_object_context_post_00ae09b0;

  // -- baseline: the call order and the argument identities ------------------
  {
    reset_state();
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);

    check(same_events(kStraightLine, 5),
          "1. call order is init, singleton get, post, forward, release");
    check(init_arg1 == &position,
          "2. init's first stack word is the entry's second argument unchanged");
    check(post_receiver == &trading_singleton,
          "3. post receives the singleton returned by the accessor");
    check(post_group == 0x5dce504au, "4. post group hash is the listed immediate");
    check(post_instance == 0u, "5. post instance argument is the listed zero");
    check(forward_receiver == &receiver, "6. forward runs on the receiver");
    check(forward_argument == &event_token,
          "7. forward's first stack word is the entry's first argument");
    check(forward_position_address == &position,
          "8. forward's second stack word is the entry's second argument");
    check(forward_result_mode == 0xffffffffu && forward_result == 0xffffffffu,
          "9. the forward's result is produced and never read by the body");
  }

  // -- 1/2. FRAME LAYOUT. The transform and the frame base are two addresses in
  // one 0x40 reservation, 0x10 apart, and all three of init/post/release are
  // handed the transform. ------------------------------------------------------
  {
    reset_state();
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);

    check(init_this != nullptr && init_arg2 != nullptr,
          "10. the init was handed two addresses");
    const std::uintptr_t transform = reinterpret_cast<std::uintptr_t>(init_this);
    const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(init_arg2);
    check(transform == base + kTransformFrameOffset,
          "11. the transform is 0x10 ABOVE the frame base the init is handed");
    check(transform != base,
          "12. the transform and the frame base are not the same address");
    check(static_cast<const void*>(init_this) !=
                  static_cast<const void*>(&position) &&
              static_cast<const void*>(init_arg2) !=
                  static_cast<const void*>(&position),
          "13. neither of them is the caller's position argument");
    check(transform + kTransformBytes == base + kFrameReserveBytes,
          "14. the 48-byte transform ends exactly at the bottom of the 0x40");
    check(base + kTransformFrameOffset >= base, "15. sanity: the offset is positive");

    check(post_frame_address == init_this,
          "16. the post was handed the same address the init received");
    check(release_frame_address == init_this,
          "17. and so was the release");
    check(post_frame_address != reinterpret_cast<const OpaqueTransform48*>(base),
          "18. none of the three was handed the frame base instead");
    // The init PAINTED those 48 bytes and the post and the release both read the
    // first one back, so the three really are looking at one object.
    check(post_first_byte == kTransformMagic,
          "19. the post read the bytes the init wrote");
    check(release_first_byte == kTransformMagic,
          "20. the release read the bytes the init wrote");
  }

  // -- 3. VTABLE DEPTH: one level. A decoy table sits at the real table's word
  // 0, so a reconstruction that dereferenced twice would call the decoy. -------
  {
    reset_state();
    decoy_table.forward_4c = &other_forward;
    receiver_vtable.slots_00[0] = &decoy_table;
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);
    check(same_events(kStraightLine, 5),
          "21. the dispatch is ONE level: the decoy table at word 0 is not used");
    check(forward_result_mode == 0xffffffffu && forward_result == 0xffffffffu,
          "22. and the real slot body ran, not the decoy's");
    receiver_vtable.slots_00[0] = nullptr;
  }

  // -- 4. SLOT DISPLACEMENT: exactly 0x4c. Its neighbours are loaded with
  // decoys that must never be selected. --------------------------------------
  {
    reset_state();
    // 0x48 is slot 18 and 0x50 is slot 20; the real slot is 19 at 0x4c.
    auto* at_48 = reinterpret_cast<Word*>(&receiver_vtable) + 18;
    auto* at_50 = reinterpret_cast<Word*>(&receiver_vtable) + 20;
    const Word saved_48 = *at_48;
    const Word saved_50 = *at_50;
    *at_48 = reinterpret_cast<Word>(&other_forward);
    *at_50 = reinterpret_cast<Word>(&other_forward);
    check(reinterpret_cast<Word*>(&receiver_vtable)[19] ==
              reinterpret_cast<Word>(&record_forward),
          "23. the real slot is word 19, at byte offset 0x4c");
    check(offsetof(OpaqueToolEventVTable, forward_4c) == 0x4c,
          "24. and the table's declared slot offset is 0x4c");

    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);
    check(same_events(kStraightLine, 5),
          "25. the neighbours at 0x48 and 0x50 are never dispatched to");
    *at_48 = saved_48;
    *at_50 = saved_50;
  }

  // -- 5. PUSH ORDER. The stack words are pushed right to left, so a
  // reconstruction that pushed them in the other order swaps the two. --------
  {
    reset_state();
    int first_token = 0;
    OpaqueVector3 other_position{9.0f, 9.0f, 9.0f};
    sim_toolevent_slot8_fun_01053d50(&receiver, &first_token, &other_position);
    check(forward_argument == &first_token,
          "26. forward's FIRST word is the entry's first argument, not the second");
    check(forward_position_address == &other_position,
          "27. forward's SECOND word is the entry's second argument, not the first");
    check(init_arg1 == &other_position,
          "28. the init's first stack word is the same second argument");
  }

  // -- 6. THE FORWARD'S RESULT IS DISCARDED. Two return values, one behaviour.
  {
    reset_state();
    forward_result_mode = 0u;
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);
    check(same_events(kStraightLine, 5),
          "29. a forward returning 0 still runs the release afterwards");
    check(forward_result == 0u, "30. and the forward really did return 0");

    reset_state();
    forward_result_mode = 0x5a5a5a5au;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);
    check(same_events(kStraightLine, 5),
          "31. a forward returning 0x5a5a5a5a runs the same five transfers");
    check(release_frame_address == init_this,
          "32. and reaches the same release address");
  }

  // -- a different receiver table selects a different slot body --------------
  {
    reset_state();
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&alternate_receiver, &event_token,
                                     &position);
    const char* const expected[] = {"init", "get", "post", "other_forward",
                                    "release"};
    check(same_events(expected, 5),
          "33. a different receiver table selects a different forward slot body");
  }

  // -- the body is straight-line: five calls, no branch on anything ----------
  {
    reset_state();
    int event_token = 0;
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &position);
    check(events.size() == 5u, "34. the body is straight-line with five calls");
  }

  // -- the observer fixtures, exercised directly -----------------------------
  {
    reset_state();
    OpaqueOwner owner{};
    std::memset(&owner, 0, sizeof(owner));
    owner.vtable_00 = &owner_vtable;
    owner.refcount_08 = 3u;
    OpaqueTransform48 frame{};
    std::memset(&frame, 0, sizeof(frame));
    frame.owner_2c = &owner;
    model_transform_release_00ad7ad0(&frame);
    check(events.size() == 1u && events[0] == "release",
          "35. release observer runs once");
    check(owner_release_count == 1u,
          "36. release observer dispatches owner slot 0xc0 exactly once");
    check(frame.owner_2c == nullptr, "37. release observer clears the owner word");
  }

  {
    reset_state();
    OpaqueTransform48 frame{};
    std::memset(&frame, 0, sizeof(frame));
    model_transform_release_00ad7ad0(&frame);
    check(events.size() == 1u, "38. release observer runs on a null owner");
    check(owner_release_count == 0u,
          "39. release observer suppresses the owner dispatch when the word is null");
  }

  {
    reset_state();
    OpaqueTransform48 frame{};
    std::memset(&frame, 0, sizeof(frame));
    model_transform_init_00ad79d0(&frame, &position, nullptr);
    check(init_this == &frame && init_arg1 == &position && init_arg2 == nullptr,
          "40. init observer records its three arguments verbatim");
    bool painted = true;
    const std::uint8_t* bytes = reinterpret_cast<const std::uint8_t*>(&frame);
    for (std::size_t index = 0; index < kOwnerOffset; ++index) {
      if (bytes[index] != kTransformMagic) {
        painted = false;
      }
    }
    check(painted,
          "41. init observer paints every byte up to the owner word");
    check(frame.owner_2c == nullptr,
          "41b. and leaves the owner word null, as a fresh transform is");
  }

  // -- 7. ABI: `RET 0x8`, so the callee owns the two argument words. ESP is
  // sampled either side of a DIRECT call, by a helper that is itself a balanced
  // call, so the two samples are taken at the same stack depth and can only
  // differ if the entry left the stack unbalanced. A hand-rolled `call *reg`
  // trampoline would measure the same thing but would enter the callee off the
  // 16-byte alignment the ABI mandates, which faults the first `movaps` the
  // compiler emits for the zeroed frame.
  {
    reset_state();
    int event_token = 0;
    OpaqueVector3 argument_position{4.0f, 5.0f, 6.0f};
    const std::uint32_t before = sample_stack_pointer();
    sim_toolevent_slot8_fun_01053d50(&receiver, &event_token, &argument_position);
    const std::uint32_t after = sample_stack_pointer();
    check(before == after,
          "42. the callee popped both argument words (RET 0x8)");
    check(forward_receiver == &receiver && forward_argument == &event_token &&
              forward_position_address == &argument_position,
          "43. and the call really did drive the body with those arguments");
    check(release_frame_address == init_this,
          "44. and the body ran to its end on the same frame");
  }

  if (failures != 0) {
    std::printf("%d failure(s)\n", failures);
    return 1;
  }
  std::printf("all 0x01053d50 model checks passed\n");
  return 0;
}

}

int main() {
  return openspore::reconstruction::pkg_sim_toolevent_01053d50::run_tests();
}

#undef TEST_THISCALL
#undef TEST_CDECL
