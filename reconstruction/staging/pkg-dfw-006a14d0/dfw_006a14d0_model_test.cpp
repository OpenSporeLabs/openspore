// PKG-DFW-006A14D0 -- VA 0x006a14d0
// Behavioural model test for app_property_list_CopyAllPropertiesFrom_006a14d0.
//
// The body under test makes exactly three indirect transfers and all three are
// reached through the two bridges declared in dfw_006a14d0_types.hpp. Those bridges
// are defined here as observers, so this test sees every transfer the
// reconstruction makes and can check: which object the transfer is dispatched ON,
// which of the three table displacements the target address came from, how many
// arguments it carried, and in what order.
//
// The objects are fabricated as byte blocks with a table image planted inside them,
// because the body reaches the table by reading a dword out of the object rather
// than by any typed member. The test therefore also pins down where the table
// pointer is read FROM: a decoy table pointer is planted at receiver+0x04, and the
// transfers must not go through it.
//
// What is asserted here is exactly what the 25-instruction listing fixes. Nothing
// is asserted about what any dispatched callee does internally, about what the
// three displacements are called, or about what the word at receiver+0x30 means.

#include "dfw_006a14d0_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::pkg_dfw_006a14d0 {

// 0x006a14d0, defined in the package's own translation unit. The header declares
// only the two bridges, so the reconstructed body is declared here with the same
// portable calling-convention spelling the package uses.
extern "C" void PKG_DFW_006A14D0_THISCALL
app_property_list_CopyAllPropertiesFrom_006a14d0(OpaquePropertyList *receiver,
                                                 OpaquePropertyList *other);

namespace {

// Machine displacements, as the listing writes them.
constexpr std::size_t kTablePointerOffset = 0x00u;  // 0x006a14f1  MOV EAX,dword ptr [ESI]
constexpr std::size_t kHeldWordOffset = 0x30u;      // 0x006a14dc  MOV ECX,dword ptr [ESI + 0x30]
constexpr std::size_t kDecoyTableOffset = 0x04u;    // never read by the listing
constexpr std::size_t kSlotOfHeldWord = 0x4;        // 0x006a14ec
constexpr std::size_t kSlotOfThirdCall = 0x38;      // 0x006a14fc
constexpr std::size_t kSlotOfSecondCall = 0x48;     // 0x006a14f3

// A block big enough to hold the table pointer at +0x00, the decoy at +0x04 and
// the held word at +0x30. Zero-filled, so a word nobody plants reads as null --
// which is the state the listing's TEST at 0x006a14df tests for.
constexpr std::size_t kBlockBytes = 0x40u;

// A table image: the body reads exactly one 4-byte word out of it per transfer, so
// the rest can stay zero and the test can still tell the three apart.
struct TableImage {
  unsigned char bytes[0x50u] = {};
};

// Stands in for any object the body dispatches on or holds a word pointing at.
// Incomplete types cannot be instantiated, so the fabrications are byte blocks and
// the conversion happens once, at the call.
struct Block {
  unsigned char bytes[kBlockBytes] = {};
};

int g_failures = 0;

void check(bool ok, const char *what) {
  if (!ok) {
    std::fprintf(stderr, "FAILED: %s\n", what);
    ++g_failures;
  }
}

void plant_word(void *address, void *value) {
  std::memcpy(address, &value, sizeof value);
}

void *load_word(const void *address) {
  void *word = nullptr;
  std::memcpy(&word, address, sizeof word);
  return word;
}

void plant_slot(TableImage &table, std::size_t slot, void *target) {
  plant_word(table.bytes + slot, target);
}

void plant_table(Block &block, TableImage &table) {
  plant_word(block.bytes + kTablePointerOffset, table.bytes);
}

// Four distinct addresses, so a transfer can be identified by the address the body
// chose rather than by the order it happened in.
extern "C" void marker_slot_04() {}
extern "C" void marker_slot_38() {}
extern "C" void marker_slot_48() {}
extern "C" void marker_held_slot_04() {}
extern "C" void marker_decoy() {}
// A second address for displacement 0x38, so a transfer that reads a swapped-in
// table can be told from one that reused the table it read earlier.
extern "C" void marker_slot_38_after_swap() {}

void *address_of(void (*function)()) {
  return reinterpret_cast<void *>(reinterpret_cast<std::uintptr_t>(function));
}

void *const kTargetHeldSlot = address_of(marker_held_slot_04);
void *const kTargetSecondCall = address_of(marker_slot_48);
void *const kTargetThirdCall = address_of(marker_slot_38);
void *const kTargetThirdCallAfterSwap = address_of(marker_slot_38_after_swap);
void *const kDecoyTarget = address_of(marker_decoy);

constexpr std::size_t kMaxTransfers = 4;

struct Transfer {
  void *target = nullptr;
  void *receiver = nullptr;
  void *argument = nullptr;
  std::size_t arguments = 0;
};

struct Observation {
  Transfer transfers[kMaxTransfers];
  std::size_t count = 0;
  // The block the body is working on, so an observer can look at the receiver's
  // word at the moment it is called.
  Block *receiver = nullptr;
  // Armed by the test: when set, the observer for kTargetSecondCall installs this
  // as the receiver's table pointer before returning. The listing re-reads the
  // receiver's table at 0x006a14fa for the third transfer, so a reconstruction
  // that cached the pointer would transfer to the old table's slot instead.
  void *replacement_table = nullptr;
  // What the kTargetHeldSlot observer saw in the receiver's word at 0x30. The
  // listing stores null there at 0x006a14e3 before it transfers, so this is the
  // check that the detach precedes the transfer rather than following it.
  void *held_word_seen_by_release = nullptr;
  // Whether the kTargetHeldSlot observer ran at all.
  bool release_happened = false;
  bool second_call_happened = false;
  bool third_call_happened = false;
};

Observation g_obs;

Transfer &record(void *target, void *receiver) {
  if (g_obs.count < kMaxTransfers) {
    Transfer &transfer = g_obs.transfers[g_obs.count];
    transfer.target = target;
    transfer.receiver = receiver;
  }
  ++g_obs.count;
  return g_obs.transfers[g_obs.count - 1 < kMaxTransfers ? g_obs.count - 1 : 0];
}

}  // namespace

// 0x006a14ef and 0x006a14f8 -- the two transfers the listing gives no stack word
// to. Whatever target address the body chose arrives here, and so does the object
// it chose to dispatch on; the argument count stays zero, which is the check that
// this body pushed nothing for these two.
extern "C" void PKG_DFW_006A14D0_CDECL
dispatch_through_slot_0(void *target_address, void *receiver) {
  Transfer &transfer = record(target_address, receiver);

  if (target_address == kTargetHeldSlot) {
    g_obs.release_happened = true;
    g_obs.held_word_seen_by_release =
        load_word(g_obs.receiver->bytes + kHeldWordOffset);
  }

  if (target_address == kTargetSecondCall) {
    g_obs.second_call_happened = true;
    if (g_obs.replacement_table != nullptr) {
      plant_word(g_obs.receiver->bytes + kTablePointerOffset,
                 g_obs.replacement_table);
    }
  }

  (void)transfer;
}

// 0x006a1502 -- the only transfer the listing gives a stack word to, the single
// PUSH EDI at 0x006a14ff. The word pushed is the source, so that is what must
// arrive here.
extern "C" void PKG_DFW_006A14D0_CDECL
dispatch_through_slot_1(void *target_address, void *receiver, void *argument) {
  Transfer &transfer = record(target_address, receiver);
  transfer.argument = argument;
  transfer.arguments = 1;

  if (target_address == kTargetThirdCall) {
    g_obs.third_call_happened = true;
  }
}

namespace {

// Everything the body touches, wired up: a receiver whose table is `table`, a
// source with its own table (the body never dispatches on the source, so the
// source's table is a decoy too), and an object the receiver's word can point at
// whose table carries a different address at displacement 0x04.
struct Scene {
  Block receiver;
  TableImage receiver_table;
  Block source;
  TableImage source_table;
  Block held;
  TableImage held_table;
  TableImage decoy_table;
};

void build(Scene &scene) {
  plant_slot(scene.receiver_table, kSlotOfSecondCall, kTargetSecondCall);
  plant_slot(scene.receiver_table, kSlotOfThirdCall, kTargetThirdCall);
  // A decoy at the displacement the listing reads for the held word's transfer,
  // so a reconstruction that dispatched on the receiver instead of on the held
  // object would pick this up.
  plant_slot(scene.receiver_table, kSlotOfHeldWord, kDecoyTarget);
  plant_table(scene.receiver, scene.receiver_table);

  plant_slot(scene.source_table, kSlotOfSecondCall, kDecoyTarget);
  plant_slot(scene.source_table, kSlotOfThirdCall, kDecoyTarget);
  plant_table(scene.source, scene.source_table);

  plant_slot(scene.held_table, kSlotOfHeldWord, kTargetHeldSlot);
  plant_slot(scene.held_table, kSlotOfSecondCall, kDecoyTarget);
  plant_slot(scene.held_table, kSlotOfThirdCall, kDecoyTarget);
  plant_table(scene.held, scene.held_table);

  plant_slot(scene.decoy_table, kSlotOfSecondCall, kDecoyTarget);
  plant_slot(scene.decoy_table, kSlotOfThirdCall, kDecoyTarget);
  plant_slot(scene.decoy_table, kSlotOfHeldWord, kDecoyTarget);
  plant_word(scene.receiver.bytes + kDecoyTableOffset, scene.decoy_table.bytes);
}

OpaquePropertyList *as_property_list(Block &block) {
  return reinterpret_cast<OpaquePropertyList *>(block.bytes);
}

OpaqueVtableObject *as_vtable_object(Block &block) {
  return reinterpret_cast<OpaqueVtableObject *>(block.bytes);
}

void run(Scene &scene, OpaquePropertyList *other) {
  g_obs = Observation();
  g_obs.receiver = &scene.receiver;
  app_property_list_CopyAllPropertiesFrom_006a14d0(as_property_list(scene.receiver),
                                                    other);
}

const Transfer &transfer_at(std::size_t index) {
  return g_obs.transfers[index];
}

// 0x006a14d8/0x006a14da: the guard compares the receiver against the source and
// jumps straight to the epilogue. A self-reference dispatches nothing at all, and
// writes nothing, so every byte of the receiver survives untouched.
void test_self_reference_dispatches_nothing() {
  Scene scene;
  build(scene);
  run(scene, as_property_list(scene.receiver));

  check(g_obs.count == 0,
        "0x006a14da refuses the whole operation when the source is the receiver");
  check(!g_obs.release_happened && !g_obs.second_call_happened &&
            !g_obs.third_call_happened,
        "a self-reference reaches none of the three transfers");
  check(load_word(scene.receiver.bytes + kHeldWordOffset) == nullptr,
        "a self-reference writes no word to the receiver");
}

// 0x006a14df/0x006a14e1: a null word at 0x30 jumps to 0x006a14f1, so the store at
// 0x006a14e3 AND the transfer at 0x006a14ef are both skipped, and only the two
// receiver transfers happen, in the listing's order.
void test_null_word_skips_the_detach_and_the_held_transfer() {
  Scene scene;
  build(scene);
  run(scene, as_property_list(scene.source));

  check(!g_obs.release_happened,
        "0x006a14ef is skipped when the receiver's word at 0x30 is null");
  check(g_obs.count == 2,
        "only the two receiver transfers happen on the null-word path");
  check(g_obs.second_call_happened && g_obs.third_call_happened,
        "both receiver transfers are reached on the null-word path");
  check(transfer_at(0).target == kTargetSecondCall,
        "the first transfer is the one through table displacement 0x48");
  check(transfer_at(1).target == kTargetThirdCall,
        "the second transfer is the one through table displacement 0x38");
  check(load_word(scene.receiver.bytes + kHeldWordOffset) == nullptr,
        "the word at 0x30 is left as it was found on the null-word path");
}

// The full path, with all three transfers. This is the check that pins down which
// OBJECT each transfer is dispatched on, which displacement its address came from,
// and how many arguments it carried.
void test_full_path_transfers_in_listing_order() {
  Scene scene;
  build(scene);
  plant_word(scene.receiver.bytes + kHeldWordOffset, as_vtable_object(scene.held));
  run(scene, as_property_list(scene.source));

  check(g_obs.count == 3, "a non-self-reference with a non-null word makes three transfers");
  check(g_obs.release_happened && g_obs.second_call_happened &&
            g_obs.third_call_happened,
        "all three transfers are reached");

  // 0x006a14ea/0x006a14ec/0x006a14ef -- dispatched on the HELD OBJECT, through
  // the HELD OBJECT's own table, with nothing pushed.
  check(transfer_at(0).target == kTargetHeldSlot,
        "the first transfer targets displacement 0x04 of the held object's table");
  check(transfer_at(0).receiver == static_cast<void *>(as_vtable_object(scene.held)),
        "0x006a14ef is dispatched on the held object, not on the receiver");
  check(transfer_at(0).arguments == 0,
        "0x006a14ef is given no stack word");

  // 0x006a14f1/0x006a14f3/0x006a14f8 -- on the RECEIVER, through the receiver's
  // own table, with nothing pushed.
  check(transfer_at(1).target == kTargetSecondCall,
        "the second transfer targets displacement 0x48 of the receiver's table");
  check(transfer_at(1).receiver == static_cast<void *>(as_property_list(scene.receiver)),
        "0x006a14f8 is dispatched on the receiver");
  check(transfer_at(1).arguments == 0, "0x006a14f8 is given no stack word");

  // 0x006a14fa/0x006a14fc/0x006a14ff/0x006a1502 -- on the RECEIVER, and the one
  // transfer with a stack word, which is the source.
  check(transfer_at(2).target == kTargetThirdCall,
        "the third transfer targets displacement 0x38 of the receiver's table");
  check(transfer_at(2).receiver == static_cast<void *>(as_property_list(scene.receiver)),
        "0x006a1502 is dispatched on the receiver");
  check(transfer_at(2).arguments == 1, "0x006a14ff pushes exactly one word");
  check(transfer_at(2).argument == static_cast<void *>(as_property_list(scene.source)),
        "the word pushed at 0x006a14ff is the source");
}

// 0x006a14e3 precedes 0x006a14ef. The observer for the held-object transfer reads
// the receiver's word at 0x30, and it must already be null -- and it must have been
// non-null on entry, or the block would not have been entered at all.
void test_the_detach_precedes_the_held_object_transfer() {
  Scene scene;
  build(scene);
  plant_word(scene.receiver.bytes + kHeldWordOffset, as_vtable_object(scene.held));
  check(load_word(scene.receiver.bytes + kHeldWordOffset) != nullptr,
        "the receiver's word at 0x30 is non-null going in, as the test set it");
  run(scene, as_property_list(scene.source));

  check(g_obs.held_word_seen_by_release == nullptr,
        "0x006a14e3 stores null at 0x30 before 0x006a14ef transfers");
  check(load_word(scene.receiver.bytes + kHeldWordOffset) == nullptr,
        "the receiver's word at 0x30 is left detached after the body returns");
}

// 0x006a14f1 and 0x006a14fa are two separate reads of the receiver's table
// pointer. The observer for the 0x48 transfer swaps that pointer for a table
// carrying a DIFFERENT address at displacement 0x38, so a body that reused the
// pointer it read at 0x006a14f1 would transfer to the old table's word and be
// caught here.
void test_the_receiver_table_is_read_again_for_the_third_transfer() {
  Scene scene;
  build(scene);
  plant_word(scene.receiver.bytes + kHeldWordOffset, as_vtable_object(scene.held));

  TableImage replacement;
  plant_slot(replacement, kSlotOfThirdCall, kTargetThirdCallAfterSwap);
  g_obs = Observation();
  g_obs.receiver = &scene.receiver;
  g_obs.replacement_table = replacement.bytes;

  app_property_list_CopyAllPropertiesFrom_006a14d0(as_property_list(scene.receiver),
                                                    as_property_list(scene.source));

  check(g_obs.count == 3, "all three transfers still happen with the table swapped");
  check(transfer_at(1).target == kTargetSecondCall,
        "the 0x48 target was taken from the table in place at 0x006a14f1");
  check(transfer_at(2).target == kTargetThirdCallAfterSwap,
        "0x006a14fa re-reads the receiver's table, so the 0x38 target is the one in the table in place at that moment");
  check(transfer_at(2).target != kTargetThirdCall,
        "the 0x38 target is not the one from the table read earlier at 0x006a14f1");
}

// The table pointer is read from the receiver at displacement 0x00. A decoy table
// is planted at receiver+0x04 -- the same displacement the listing reads for the
// HELD object's table -- and nothing may go through it.
void test_the_table_pointer_is_read_at_displacement_zero() {
  Scene scene;
  build(scene);
  plant_word(scene.receiver.bytes + kHeldWordOffset, as_vtable_object(scene.held));
  run(scene, as_property_list(scene.source));

  check(g_obs.count == 3, "the decoy table at receiver+0x04 changes no transfer count");
  check(transfer_at(0).target == kTargetHeldSlot &&
            transfer_at(1).target == kTargetSecondCall &&
            transfer_at(2).target == kTargetThirdCall,
        "no transfer goes through the decoy table planted at receiver+0x04");
}

// The body's only write is the four bytes at receiver+0x30. Every other byte of the
// receiver, of the source and of the held object must survive unchanged -- the
// table pointer at +0x00 included, since the body only reads it.
void test_no_displacement_other_than_0x30_is_written() {
  Scene scene;
  build(scene);
  plant_word(scene.receiver.bytes + kHeldWordOffset, as_vtable_object(scene.held));

  unsigned char receiver_before[kBlockBytes];
  unsigned char source_before[kBlockBytes];
  unsigned char held_before[kBlockBytes];
  std::memcpy(receiver_before, scene.receiver.bytes, kBlockBytes);
  std::memcpy(source_before, scene.source.bytes, kBlockBytes);
  std::memcpy(held_before, scene.held.bytes, kBlockBytes);

  run(scene, as_property_list(scene.source));

  unsigned char receiver_after[kBlockBytes];
  unsigned char source_after[kBlockBytes];
  unsigned char held_after[kBlockBytes];
  std::memcpy(receiver_after, scene.receiver.bytes, kBlockBytes);
  std::memcpy(source_after, scene.source.bytes, kBlockBytes);
  std::memcpy(held_after, scene.held.bytes, kBlockBytes);

  check(std::memcmp(source_before, source_after, kBlockBytes) == 0,
        "the source is never written");
  check(std::memcmp(held_before, held_after, kBlockBytes) == 0,
        "the object the receiver's word pointed at is never written");

  std::size_t differing = 0;
  for (std::size_t index = 0; index < kBlockBytes; ++index) {
    if (receiver_before[index] != receiver_after[index]) {
      ++differing;
    }
  }
  check(differing == 4,
        "exactly the four bytes of the word at 0x30 change in the receiver");
  check(load_word(scene.receiver.bytes + kHeldWordOffset) == nullptr,
        "the four changed bytes are the word at 0x30, now null");
  check(load_word(scene.receiver.bytes + kTablePointerOffset) ==
            scene.receiver_table.bytes,
        "the receiver's table pointer at 0x00 is untouched by a plain call");

  // One limit stated plainly: a store that wrote back the value it had just read
  // would leave the bytes identical and pass the comparison above. That store is
  // not observable through this interface and is not claimed to be excluded. Every
  // store that changes a byte is excluded.
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dfw_006a14d0

int main() {
  using namespace openspore::reconstruction::pkg_dfw_006a14d0;
  test_self_reference_dispatches_nothing();
  test_null_word_skips_the_detach_and_the_held_transfer();
  test_full_path_transfers_in_listing_order();
  test_the_detach_precedes_the_held_object_transfer();
  test_the_receiver_table_is_read_again_for_the_third_transfer();
  test_the_table_pointer_is_read_at_displacement_zero();
  test_no_displacement_other_than_0x30_is_written();
  if (g_failures != 0) {
    std::fprintf(stderr, "%d check(s) failed\n", g_failures);
    return 1;
  }
  std::fprintf(stderr, "all checks passed\n");
  return 0;
}
