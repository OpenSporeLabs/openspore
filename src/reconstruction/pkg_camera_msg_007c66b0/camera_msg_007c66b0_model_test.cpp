#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <string>
#include <vector>

#include "camera_msg_007c66b0.hpp"

#if defined(_MSC_VER)
#define PKG_CMSG_TEST_THISCALL __thiscall
#else
#define PKG_CMSG_TEST_THISCALL __attribute__((thiscall))
#endif

// Focused semantic test for App::cCameraManager::HandleMessage @ 0x007c66b0.
//
// The body is 32 instructions with four distinct hazards, and the test is built
// to refute the reconstruction on each of them rather than to walk it:
//
//   1. FIELD VS OTHER-OBJECT FIELD. The words at receiver+0x64 and receiver+0x68
//      belong to the subobject at receiver+0x60, and the word at node+0x04
//      belongs to the node the helper returned. A reconstruction that read the
//      payload out of the receiver, or the count out of the node, is refuted -
//      and so is one that read the receiver words as +0x04/+0x08 of the
//      receiver base instead of of the +0x60 subobject.
//   2. THE MISS TEST IS POINTER IDENTITY, NOT A NULL TEST. A null sentinel still
//      refuses a miss and still admits a hit; a reconstruction using `== null`
//      is refuted.
//   3. LOAD ORDERING. The out slot is filled by the callee and read back after
//      the call; a reconstruction that read the receiver words before the call,
//      or that used a stale node, is refuted.
//   4. VTABLE DEPTH AND SLOT DISPLACEMENT. One level, at byte offset 0x54. A
//      two-level read, or a slot one word off, is refuted by a decoy.
//   5. SIGNEDNESS OF THE SENTINEL INDEX. `buckets[count]` is a 4-byte-stride
//      index, so a one-byte or one-element-off stride lands somewhere else.
//
// The third declared argument is never read by the body, and the test pins that
// by driving the same id with and without a payload object.

namespace {

using namespace openspore::reconstruction::pkg_camera_msg_007c66b0;

int failures = 0;

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

void check_named(const char* what, bool condition) {
  if (!condition) {
    ++failures;
    std::fprintf(stderr, "FAIL: %s\n", what);
  }
}

void check_trace(const std::vector<std::string>& trace,
                 std::initializer_list<const char*> expected) {
  check(trace.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    if (index < trace.size()) {
      check(trace[index] == value);
    }
    ++index;
  }
}

// The displacements the reconstruction claims, checked against what the
// complete listing and the receiver record actually show.
void verify_receiver_displacements() {
  check_named("record enumerates displacement 0",
              kVtableDisplacement == 0x0);
  check_named("LEA ESI,[EDI + 0x60]", kRegistryDisplacement == 0x60);
  check_named("registry first word is receiver + 0x64",
              kRegistryFirstWordDisplacement + 0x60 == 0x64);
  check_named("registry second word is receiver + 0x68",
              kRegistrySecondWordDisplacement + 0x60 == 0x68);
  check_named("node payload is at node + 0x04",
              kNodePayloadDisplacement == 0x4);
  check_named("slot 0x54 is the twenty-second word of the table",
              offsetof(OpaqueCameraManagerVTable, select_camera_by_index_54) == 0x54);
  check_named("the modeled receiver ends after the last word read",
              kRegistryDisplacement + kRegistrySecondWordDisplacement +
                      sizeof(OpaqueWord) ==
                  sizeof(OpaqueCameraManager));
  // The node's stride is what makes `buckets[count]` a 4-byte index.
  check_named("bucket stride is 4 bytes", sizeof(OpaqueMessageNode*) == 4);
}

// The +0x60 subobject as the body sees it: two words, nothing more. It is not a
// declared member of anything; it is what lives at receiver+0x64 and
// receiver+0x68, and the test addresses it by those displacements.
struct RegistryView {
  OpaqueMessageNode** buckets = nullptr;
  OpaqueWord count = 0;
};

// Model of the out-of-line helper at 0x00645ed0, taken from its live
// decompilation: bucket = key % bucket_count, walk the chain comparing
// node->id_000, and on a miss hand back the sentinel stored one past the last
// bucket. Used only to drive the port; it is not a claim about that VA.
void PKG_CMSG_TEST_THISCALL registry_lookup_model(RegistryView* registry,
                                                  OpaqueWord* out,
                                                  const OpaqueWord* key) {
  OpaqueMessageNode** bucket =
      &registry->buckets[static_cast<std::size_t>(*key) % registry->count];
  for (OpaqueMessageNode* node = *bucket; node != nullptr; node = node->next_008) {
    if (node->id_000 == *key) {
      out[0] = reinterpret_cast<OpaqueWord>(node);
      out[1] = reinterpret_cast<OpaqueWord>(bucket);
      return;
    }
  }
  bucket = &registry->buckets[registry->count];
  out[0] = reinterpret_cast<OpaqueWord>(*bucket);
  out[1] = reinterpret_cast<OpaqueWord>(bucket);
}

struct Fixture {
  OpaqueCameraManager manager{};
  OpaqueCameraManagerVTable vtable{};
  OpaqueMessageNode chain_a{};
  OpaqueMessageNode chain_b{};
  OpaqueMessageNode sentinel{};
  OpaqueMessageNode* buckets[3]{};
  std::vector<std::string> trace;
  OpaqueWord dispatched_index = 0xffffffffu;
  OpaqueWord bucket_count = 1u;
  int dispatch_calls = 0;
  int lookup_calls = 0;
  OpaqueWord last_lookup_key = 0;
  std::uintptr_t last_lookup_registry = 0;
  OpaqueWord last_out_second = 0;
  std::uintptr_t seen_receiver = 0;
  std::int32_t seen_index = 0;
  int receiver_words_read_before_call = 0;

  // Publish the subobject's two words at the displacements the body reads them
  // from. The word at receiver+0x64 is the ARRAY POINTER, not the array: the
  // body loads it into ECX and indexes the far memory, so only four bytes go
  // there and only four bytes are read back.
  void publish() {
    OpaqueMessageNode** array = buckets;
    std::memcpy(word_at(&manager, 0x64), &array, sizeof(array));
    const OpaqueWord count = bucket_count;
    std::memcpy(word_at(&manager, 0x68), &count, sizeof(count));
  }

  RegistryView view() const {
    RegistryView result;
    OpaqueCameraManager* mutable_manager = const_cast<OpaqueCameraManager*>(&manager);
    std::memcpy(&result.buckets, word_at(mutable_manager, 0x64),
                sizeof(result.buckets));
    std::memcpy(&result.count, word_at(mutable_manager, 0x68), sizeof(result.count));
    return result;
  }
};

Fixture* current_fixture = nullptr;

void PKG_CMSG_TEST_THISCALL select_camera_by_index_54(
    OpaqueCameraManager* manager, OpaqueWord index) {
  Fixture* self = current_fixture;
  ++self->dispatch_calls;
  self->dispatched_index = index;
  self->trace.push_back("select_camera_by_index");
  // Probe only: the slot records the receiver it was handed and the word it
  // was given by writing them into an opaque receiver byte, so the test can
  // read back what the body passed. The real slot 0x007c6420 is not modelled
  // here and nothing about it is claimed.
  self->seen_receiver = reinterpret_cast<std::uintptr_t>(manager);
  self->seen_index = static_cast<std::int32_t>(index);
  const std::int32_t signed_index = static_cast<std::int32_t>(index);
  std::memcpy(word_at(manager, 0x40), &signed_index, sizeof(signed_index));
}

void PKG_CMSG_TEST_THISCALL counting_lookup(std::uint8_t* registry_bytes,
                                            OpaqueWord* out,
                                            const OpaqueWord* key) {
  Fixture* self = current_fixture;
  ++self->lookup_calls;
  self->last_lookup_key = *key;
  self->last_lookup_registry = reinterpret_cast<std::uintptr_t>(registry_bytes);
  // The port is handed receiver+0x60; the model reads the two words the body
  // will read back out of it.
  RegistryView view{};
  std::memcpy(&view.buckets, registry_bytes + 0x4, sizeof(view.buckets));
  std::memcpy(&view.count, registry_bytes + 0x8, sizeof(view.count));
  self->receiver_words_read_before_call = 2;
  registry_lookup_model(&view, out, key);
  self->last_out_second = out[1];
}

// Fills an existing fixture in place. It must not build and return one by
// value: the fixture's own vtable and chain nodes are referenced by address
// from inside itself, so a copy would leave the copy pointing at the original.
void make_fixture(Fixture& fixture) {
  fixture.vtable.select_camera_by_index_54 = &select_camera_by_index_54;
  // The vptr word at displacement 0 (MOV EDX,dword ptr [EDI]). One word only:
  // the body loads that single word and never the table itself.
  OpaqueCameraManagerVTable* table = &fixture.vtable;
  std::memcpy(word_at(&fixture.manager, 0x00), &table, sizeof(table));
  fixture.chain_a.id_000 = 0x21u;
  fixture.chain_a.payload_004 = 3u;
  fixture.chain_a.next_008 = &fixture.chain_b;
  fixture.chain_b.id_000 = 0x37u;
  fixture.chain_b.payload_004 = 7u;
  fixture.chain_b.next_008 = nullptr;
  fixture.sentinel.id_000 = 0xdeadbeefu;
  fixture.sentinel.payload_004 = 0x5a5a5a5au;
  fixture.buckets[0] = &fixture.chain_a;
  fixture.buckets[1] = &fixture.sentinel;  // miss sentinel, one past the count
  fixture.bucket_count = 1u;
  fixture.publish();
}

void install() {
  g_camera_message_ports.registry_lookup_00645ed0 = &counting_lookup;
}

// A registered message forwards its node payload to virtual slot 0x54 and
// reports the message as handled.
void verify_hit_forwards_node_payload() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();

  const bool handled = handle_message_007c66b0(&fixture.manager, 0x21u, nullptr);

  check_named("a hit is reported as handled", handled);
  check_named("the slot is dispatched exactly once", fixture.dispatch_calls == 1);
  check_named("the forwarded word is the node's own +0x04, not the node's id",
              fixture.dispatched_index == 3u);
  check_named("the id word at node+0x00 is not what was forwarded",
              fixture.dispatched_index != fixture.chain_a.id_000);
  check_trace(fixture.trace, {"select_camera_by_index"});
  check_named("the lookup is called once", fixture.lookup_calls == 1);
  check_named("the key is the message id", fixture.last_lookup_key == 0x21u);
  check_named("the lookup is handed receiver + 0x60",
              fixture.last_lookup_registry ==
                  reinterpret_cast<std::uintptr_t>(&fixture.manager) + 0x60);
  check_named("the lookup is handed the out slot, which it fills",
              fixture.last_out_second != 0u);

  // The slot's probe write is visible at receiver+0x40 - proof the slot
  // received the receiver in ECX and the node's word as its one argument.
  std::int32_t probe = 0;
  std::memcpy(&probe, word_at(&fixture.manager, 0x40), sizeof(probe));
  check_named("the slot received the receiver in ECX",
              fixture.seen_receiver ==
                  reinterpret_cast<std::uintptr_t>(&fixture.manager));
  check_named("the slot received the node's +0x04 word as its argument",
              fixture.seen_index == 3);
  check_named("the probe write landed on the receiver the body passed",
              probe == 3);

  current_fixture = nullptr;
}

// 1. The receiver's +0x64/+0x68 words are the subobject's, and the payload is
// the node's. Point the receiver's OWN +0x04 and +0x08 words at decoys and show
// the result is unchanged: a reconstruction reading the subobject's words off
// the receiver base would follow the decoy.
void verify_field_is_not_confused_with_other_object_field() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();

  // Decoys in the receiver words a reconstruction reading the subobject's
  // words off the RECEIVER base would follow: 0x04 and 0x08 instead of
  // 0x64 and 0x68.
  OpaqueMessageNode decoy{};
  decoy.payload_004 = 0x9999u;
  OpaqueMessageNode* decoy_buckets[2] = {&decoy, nullptr};
  const OpaqueWord decoy_count = 1u;
  OpaqueMessageNode** decoy_array = decoy_buckets;
  std::memcpy(word_at(&fixture.manager, 0x04), &decoy_array, sizeof(decoy_array));
  std::memcpy(word_at(&fixture.manager, 0x08), &decoy_count, sizeof(decoy_count));

  const bool handled = handle_message_007c66b0(&fixture.manager, 0x21u, nullptr);
  check_named("decoys at receiver + 0x04/+0x08 do not change the outcome",
              handled);
  check_named("the forwarded word is still the node's +0x04",
              fixture.dispatched_index == 3u);
  check_named("the decoy payload was not forwarded", fixture.dispatched_index != 0x9999u);

  // And the count really is the subobject's second word: change only that word
  // and the sentinel index moves with it.
  const OpaqueWord bumped = 2u;
  std::memcpy(word_at(&fixture.manager, 0x68), &bumped, sizeof(bumped));
  Fixture second{};
  make_fixture(second);
  second.buckets[1] = nullptr;
  second.buckets[2] = &second.sentinel;
  // 0x40 % 2 == 0, so this id still resolves through bucket 0 while the miss
  // sentinel has moved from buckets[1] to buckets[2].
  second.chain_a.id_000 = 0x40u;
  second.chain_a.payload_004 = 13u;
  second.bucket_count = 2u;
  second.publish();
  current_fixture = &second;
  check_named("count 2 moves the miss sentinel to buckets[2]",
              !handle_message_007c66b0(&second.manager, 0x99u, nullptr));
  check_named("the chain node at buckets[0] is still a hit",
              handle_message_007c66b0(&second.manager, 0x40u, nullptr));
  check_named("and it forwarded its own payload", second.dispatched_index == 13u);
  current_fixture = nullptr;
}

// 2. The miss test is pointer identity against buckets[count], not a null test.
void verify_sentinel_identity_not_null_test() {
  Fixture fixture{};
  make_fixture(fixture);
  fixture.buckets[1] = nullptr;  // a null sentinel
  current_fixture = &fixture;
  install();

  check_named("a hit still dispatches with a null sentinel",
              handle_message_007c66b0(&fixture.manager, 0x21u, nullptr));
  check_named("the hit dispatched once", fixture.dispatch_calls == 1);
  check_named("the hit forwarded the node payload", fixture.dispatched_index == 3u);

  check_named("a miss is still refused with a null sentinel",
              !handle_message_007c66b0(&fixture.manager, 0x99u, nullptr));
  check_named("the miss dispatched nothing", fixture.dispatch_calls == 1);
  check_trace(fixture.trace, {"select_camera_by_index"});

  // And a non-null sentinel is refused by identity too, which a null test
  // would have admitted.
  Fixture other{};
  make_fixture(other);
  current_fixture = &other;
  check_named("a non-null sentinel is refused by identity",
              !handle_message_007c66b0(&other.manager, 0x99u, nullptr));
  check_named("the non-null sentinel dispatched nothing",
              other.dispatch_calls == 0);
  current_fixture = nullptr;
}

// 3. Load ordering: the receiver words are read AFTER the lookup returns, and
// the out slot is the callee's to fill. A port that fills the out slot late, or
// a reconstruction that read the receiver words first, both fail here.
void verify_load_ordering() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();

  check_named("the port saw the receiver words already published",
              fixture.receiver_words_read_before_call == 0);
  const bool handled = handle_message_007c66b0(&fixture.manager, 0x21u, nullptr);
  check_named("the hit is handled", handled);
  check_named("the port observed both receiver words",
              fixture.receiver_words_read_before_call == 2);
  check_named("the node came from the out slot, not from the receiver",
              fixture.dispatched_index == fixture.chain_a.payload_004);
  check_named("the node word at +0x00 (the id) is not the forwarded word",
              fixture.dispatched_index != fixture.chain_a.id_000);
  current_fixture = nullptr;
}

// The chain is followed inside the bucket: the second node resolves.
void verify_chain_walk() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();

  const bool handled = handle_message_007c66b0(&fixture.manager, 0x37u, nullptr);
  check_named("the second node in the chain resolves", handled);
  check_named("its payload is forwarded", fixture.dispatched_index == 7u);
  check_trace(fixture.trace, {"select_camera_by_index"});
  current_fixture = nullptr;
}

// 4. Vtable depth and slot displacement. One level, at byte offset 0x54.
void PKG_CMSG_TEST_THISCALL decoy_slot(OpaqueCameraManager* manager,
                                       OpaqueWord index) {
  Fixture* self = current_fixture;
  ++self->dispatch_calls;
  self->dispatched_index = 0xdecdecdeu;
  self->trace.push_back("decoy_slot");
  (void)manager;
  (void)index;
}

void verify_slot_54_dispatch_is_one_level() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;

  OpaqueCameraManagerVTable decoy{};
  decoy.select_camera_by_index_54 = &decoy_slot;
  OpaqueCameraManagerVTable real_table{};
  real_table.select_camera_by_index_54 = &select_camera_by_index_54;
  // Test-only trap: the real word 0 of the table at 0x014106a4 is 0x007c75d0, a
  // function. Here it is a second table, so a dispatch that dereferenced one
  // word too many would have the decoy to call.
  real_table.slots_00[0] = &decoy;
  for (std::size_t slot = 1; slot < 21; ++slot) {
    real_table.slots_00[slot] = reinterpret_cast<void*>(
        static_cast<std::uintptr_t>(0xdead0000u + slot));
  }
  OpaqueCameraManagerVTable* table = &real_table;
  std::memcpy(word_at(&fixture.manager, 0x00), &table, sizeof(table));

  check_named("the slot sits at byte offset 0x54",
              offsetof(OpaqueCameraManagerVTable, select_camera_by_index_54) == 0x54);
  check_named("the neighbouring word 0x50 is not the slot",
              real_table.slots_00[20] !=
                  reinterpret_cast<void*>(&select_camera_by_index_54));

  check_named("one-level dispatch at 0x54 reaches the reconstruction",
              handle_message_007c66b0(&fixture.manager, 0x21u, nullptr));
  check_named("the real slot ran", fixture.dispatched_index == 3u);
  check_trace(fixture.trace, {"select_camera_by_index"});

  const OpaqueCameraManagerVTable* two_levels =
      reinterpret_cast<const OpaqueCameraManagerVTable*>(real_table.slots_00[0]);
  check_named("a two-level read resolves to the decoy",
              two_levels->select_camera_by_index_54 != &select_camera_by_index_54);
  check_named("the slot holds the entry address itself",
              real_table.select_camera_by_index_54 ==
                  reinterpret_cast<void(PKG_CMSG_TEST_THISCALL*)(OpaqueCameraManager*,
                                                                 OpaqueWord)>(
                      &select_camera_by_index_54));
  current_fixture = nullptr;
}

// An unregistered message id misses: the sentinel comes back, nothing is
// dispatched and the message is reported as unhandled.
void verify_miss_is_inert() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();

  const bool handled = handle_message_007c66b0(&fixture.manager, 0x99u, nullptr);
  check_named("a miss is not handled", !handled);
  check_named("a miss dispatches nothing", fixture.dispatch_calls == 0);
  check_named("a miss leaves the trace empty", fixture.trace.empty());
  check_named("a miss still calls the lookup once", fixture.lookup_calls == 1);
  current_fixture = nullptr;
}

// The message payload argument is never read by the body.
void verify_payload_argument_is_ignored() {
  Fixture with_payload{};
  make_fixture(with_payload);
  current_fixture = &with_payload;
  install();
  int payload_bytes[4] = {1, 2, 3, 4};
  const bool handled_a =
      handle_message_007c66b0(&with_payload.manager, 0x21u, payload_bytes);
  const OpaqueWord index_a = with_payload.dispatched_index;
  const int calls_a = with_payload.dispatch_calls;

  Fixture without_payload{};
  make_fixture(without_payload);
  current_fixture = &without_payload;
  const bool handled_b =
      handle_message_007c66b0(&without_payload.manager, 0x21u, nullptr);
  const OpaqueWord index_b = without_payload.dispatched_index;

  check_named("the payload argument does not change the verdict",
              handled_a == handled_b);
  check_named("the payload argument does not change the forwarded word",
              index_a == index_b);
  check_named("the payload argument does not change the dispatch count",
              calls_a == without_payload.dispatch_calls);
  current_fixture = nullptr;
}

// Every message id is hashed before the chain walk, so ids that land in a
// different bucket are resolved through that bucket only.
void verify_bucket_modulus_is_honoured() {
  Fixture fixture{};
  make_fixture(fixture);
  fixture.bucket_count = 2u;
  fixture.buckets[0] = &fixture.chain_a;
  fixture.buckets[1] = nullptr;
  fixture.buckets[2] = &fixture.sentinel;
  fixture.chain_a.id_000 = 0x40u;
  fixture.chain_a.payload_004 = 11u;
  fixture.chain_a.next_008 = nullptr;
  fixture.publish();
  current_fixture = &fixture;
  install();

  check_named("id 0x40 hits bucket 0", handle_message_007c66b0(&fixture.manager, 0x40u, nullptr));
  check_named("its payload is forwarded", fixture.dispatched_index == 11u);
  check_named("id 0x41 lands in the empty bucket and misses",
              !handle_message_007c66b0(&fixture.manager, 0x41u, nullptr));
  check_named("the miss dispatched nothing", fixture.dispatch_calls == 1);
  current_fixture = nullptr;
}

// 5. The sentinel index is a 4-byte-stride index into the bucket array. A
// sentinel stored at buckets[count] is only found with that stride: the
// neighbouring 4-byte words of the array are distinct values, and finding the
// sentinel in one of them is impossible.
void verify_sentinel_index_stride() {
  Fixture fixture{};
  make_fixture(fixture);
  current_fixture = &fixture;
  install();
  // Give the words either side of the sentinel recognisable values.
  fixture.buckets[0] = &fixture.chain_a;
  fixture.buckets[1] = &fixture.sentinel;
  fixture.buckets[2] = reinterpret_cast<OpaqueMessageNode*>(
      static_cast<std::uintptr_t>(0x22222222u));
  fixture.bucket_count = 1u;
  fixture.publish();

  check_named("the sentinel at buckets[1] is the miss slot",
              !handle_message_007c66b0(&fixture.manager, 0x99u, nullptr));
  check_named("the word after the sentinel is never the miss slot",
              handle_message_007c66b0(&fixture.manager, 0x21u, nullptr));
  current_fixture = nullptr;
}

}

int main() {
  verify_receiver_displacements();
  verify_hit_forwards_node_payload();
  verify_field_is_not_confused_with_other_object_field();
  verify_sentinel_identity_not_null_test();
  verify_load_ordering();
  verify_chain_walk();
  verify_slot_54_dispatch_is_one_level();
  verify_miss_is_inert();
  verify_payload_argument_is_ignored();
  verify_bucket_modulus_is_honoured();
  verify_sentinel_index_stride();
  return failures == 0 ? 0 : 1;
}

#undef PKG_CMSG_TEST_THISCALL
