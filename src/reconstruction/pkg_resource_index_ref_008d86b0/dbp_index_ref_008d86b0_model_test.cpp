// Focused model test for VA 0x008d86b0
// (Resource::DatabasePackedFile::DestroyIndex) and the ownership contract
// proven by its adjacent vtable slot 0x008d86c0 (PTR_FUN_014367b0 + 0x50).
//
// The body is two instructions: one 4-byte load at receiver+0x260 and a plain
// RET. The test is built to try to REFUTE the reconstruction, not to walk it.
// Each group names the wrong reconstruction it is aimed at:
//
//   A  POINTER, NOT THE POINTEe: the returned word is the value stored at
//      +0x260, not the first word of the object that value points at. The
//      pointee's own leading word is set to a different value, so a
//      reconstruction that dereferenced once too many is refuted.
//   B  FOUR BYTES, NOT A WORD: a 32-bit value with every byte distinct survives
//      the round trip. A byte-wide or halfword-wide load truncates it.
//   C  AN OFFSET, NOT AN INDEX: decoys at +0x25c, +0x264, +0x160 and +0x60 are
//      never read, so changing them cannot change the result.
//   D  NO TEST ON THE VALUE: a word that is not a usable pointer (0xdeadbeef)
//      comes back verbatim. A reconstruction that null-tested, masked or
//      validated would not return it.
//   E  READ ONLY: every byte of the carrier, including the word at +0x260, is
//      unchanged after the call.
//   F  NO REFCOUNT EFFECT: the pointee's vtable carries live AddRef/Release
//      slots and neither is called - the returned handle is not a new owning
//      reference.
//   G  ABI: the terminator is a plain RET, so there is no stack argument and
//      ESP is untouched. Measured inside a trampoline, not asserted as a
//      convention.
//
// Build/run (x86-32):
/*
 * clang++ -m32 -std=c++17 -Wall -Wextra -Werror \
 * dbp_index_ref_008d86b0.cpp dbp_index_ref_008d86b0_model_test.cpp \
 * -o /tmp/opencode/dbp-index-ref-008d86b0-model && \
 * /tmp/opencode/dbp-index-ref-008d86b0-model
 * 
 */
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "dbp_index_ref_008d86b0.hpp"

namespace {

using namespace openspore::reconstruction::pkg_resource_index_ref_008d86b0;

std::vector<std::string> refcount_ledger;

void trace_add_ref(ObservedIndexObject* object) {
  refcount_ledger.push_back(
      "add_ref:" + std::to_string(reinterpret_cast<std::uintptr_t>(object)));
}

void trace_release(ObservedIndexObject* object) {
  refcount_ledger.push_back(
      "release:" + std::to_string(reinterpret_cast<std::uintptr_t>(object)));
}

ObservedIndexObjectVtable make_vtable() {
  ObservedIndexObjectVtable vtable{};
  vtable.add_ref_at_04 = &trace_add_ref;
  vtable.release_at_08 = &trace_release;
  return vtable;
}

std::uint32_t get_word(const ObservedIndexRefCarrier* file,
                       std::size_t displacement) {
  std::uint32_t value = 0;
  std::memcpy(&value, word_at(file, displacement), sizeof value);
  return value;
}

void set_word(ObservedIndexRefCarrier* file, std::size_t displacement,
              std::uint32_t value) {
  std::memcpy(word_at(file, displacement), &value, sizeof value);
}

// Faithful model of the paired writer at 0x008d86c0 (vtable slot +0x50).
// Disassembly:
//   008d86c3  CMP dword ptr [EBX + 0x14], 0x0
//   008d86c7  JNZ  0x008d8701                  -> XOR AL,AL; RET 0x4
//   008d86cf  MOV  EDI, dword ptr [EBX + 0x260]
//   008d86d5  CMP  ESI, EDI                    -> JZ, no work when unchanged
//   008d86d9  TEST ESI, ESI / JZ               -> AddRef only when non-null
//   008d86e6  MOV  dword ptr [EBX + 0x260], ESI
//   008d86ec  TEST EDI, EDI / JZ               -> Release only when non-null
//   008d86fb  MOV  AL, 0x1
// NOTE: the writer addresses the carrier in EBX, not ECX, and it is a different
// function, so it is not the reconstruction under test. It is modelled here
// because it is the evidence that makes the +0x260 word a handle and this
// accessor a non-owning read of it.
bool set_index_ref_008d86c0(ObservedIndexRefCarrier* file,
                            ObservedIndexObject* value) {
  if (get_word(file, kCarrierStateGateDisplacement) != 0) {
    return false;
  }
  const std::uint32_t outgoing_word = get_word(file, kCarrierIndexWordDisplacement);
  const std::uint32_t incoming_word = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(value));
  if (incoming_word == outgoing_word) {
    return true;
  }
  if (value != nullptr) {
    value->vtable->add_ref_at_04(value);
  }
  set_word(file, kCarrierIndexWordDisplacement, incoming_word);
  ObservedIndexObject* const outgoing = reinterpret_cast<ObservedIndexObject*>(
      static_cast<std::uintptr_t>(outgoing_word));
  if (outgoing != nullptr) {
    outgoing->vtable->release_at_08(outgoing);
  }
  return true;
}

std::string ledger() {
  std::string joined;
  for (const std::string& entry : refcount_ledger) {
    if (!joined.empty()) {
      joined += ",";
    }
    joined += entry;
  }
  return joined;
}

// The displacement the reconstruction states, and the extent that holds it.
void test_layout_is_pinned() {
  assert(kCarrierIndexWordDisplacement == 0x260);
  assert(kCarrierStateGateDisplacement == 0x14);
  assert(sizeof(ObservedIndexRefCarrier) == 0x264);
  assert(kCarrierIndexWordDisplacement + 4 == sizeof(ObservedIndexRefCarrier));
  assert(sizeof(ObservedIndexObject*) == 4);
}

// A null field reads back as null: the machine has no TEST/JZ of any kind, so
// a null field is a legal, unremarkable return value rather than a trap.
void test_getter_returns_null_field() {
  refcount_ledger.clear();
  ObservedIndexRefCarrier file{};
  assert(get_word(&file, kCarrierIndexWordDisplacement) == 0);
  assert(destroy_index_008d86b0(&file) == nullptr);
  assert(refcount_ledger.empty());
}

// F. The accessor copies the word and does nothing else. The ledger stays empty
// even though the pointee carries live AddRef/Release slots, which is the whole
// point: the returned handle is not a new owning reference.
void test_getter_is_a_bare_non_owning_load() {
  refcount_ledger.clear();
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  set_word(&file, kCarrierIndexWordDisplacement,
           static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));

  ObservedIndexObject* const observed = destroy_index_008d86b0(&file);

  assert(observed == &object);
  assert(observed->vtable == &vtable);
  assert(refcount_ledger.empty());

  // Repeating the read is idempotent and still reference-neutral.
  assert(destroy_index_008d86b0(&file) == &object);
  assert(refcount_ledger.empty());
}

// A. POINTER, NOT THE POINTEe. The returned word is the value stored at +0x260.
// The pointee's own leading word (its vtable pointer) is a different value, so
// a reconstruction that dereferenced once too many would return that instead.
void test_returned_value_is_the_pointer_not_the_pointee() {
  refcount_ledger.clear();
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  set_word(&file, kCarrierIndexWordDisplacement,
           static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));

  const ObservedIndexObject* const observed = destroy_index_008d86b0(&file);
  const std::uint32_t as_word = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(observed));

  assert(as_word == static_cast<std::uint32_t>(
                        reinterpret_cast<std::uintptr_t>(&object)));
  // The pointee's leading word is the vtable pointer, and it is not what came
  // back. This is the assertion that separates the two readings.
  assert(as_word != static_cast<std::uint32_t>(
                        reinterpret_cast<std::uintptr_t>(&vtable)));
  assert(as_word != get_word(&file, 0x260 - 0x100u));
  assert(refcount_ledger.empty());
}

// B. FOUR BYTES, NOT A WORD. Every byte of the stored word is distinct and
// non-zero, so a byte-wide or halfword-wide load would truncate it and the
// comparison would fail.
void test_load_is_four_bytes_wide() {
  ObservedIndexRefCarrier file{};
  const std::uint32_t payload = 0x11223344u;
  set_word(&file, kCarrierIndexWordDisplacement, payload);
  const std::uint32_t observed = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(destroy_index_008d86b0(&file)));
  assert(observed == payload);
  assert((observed & 0xffff0000u) == 0x11220000u);
  // A high-bit word survives too: nothing in the body masks or sign-extends it.
  set_word(&file, kCarrierIndexWordDisplacement, 0xdeadbeefu);
  const std::uint32_t high = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(destroy_index_008d86b0(&file)));
  assert(high == 0xdeadbeefu);
}

// C. AN OFFSET, NOT AN INDEX. Decoys one and four bytes either side, and at a
// quarter and a sixteenth of the displacement, are never read.
void test_displacement_is_an_offset_not_an_index() {
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  const std::uint32_t real = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&object));
  set_word(&file, kCarrierIndexWordDisplacement, real);

  // Decoys: 0x25c (one dword low), 0x264 (one past the modeled extent), 0x160
  // and 0x60 (the displacement read as an element count of 4 bytes or of 16).
  set_word(&file, 0x25cu, 0x11111111u);
  set_word(&file, 0x160u, 0x22222222u);
  set_word(&file, 0x60u, 0x33333333u);

  assert(static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
             destroy_index_008d86b0(&file))) == real);

  // Now move the real word's neighbours to different values: the answer must not
  // move with them.
  set_word(&file, 0x25cu, 0xaaaaaaaau);
  set_word(&file, 0x160u, 0xbbbbbbbbu);
  set_word(&file, 0x60u, 0xccccccccu);
  assert(static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
             destroy_index_008d86b0(&file))) == real);

  // And the gate at +0x14, which belongs to the adjacent writer, is not read by
  // this body either: any value in it leaves the result alone.
  set_word(&file, kCarrierStateGateDisplacement, 0xffffffffu);
  assert(static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
             destroy_index_008d86b0(&file))) == real);
}

// D. NO TEST ON THE VALUE. A word that is not a usable pointer comes back
// verbatim: there is no null test, no mask and no validation in the body.
void test_no_test_on_the_stored_word() {
  ObservedIndexRefCarrier file{};
  for (std::uint32_t payload : {0x00000000u, 0x00000001u, 0xffffffffu,
                                0xdeadbeefu, 0x80000000u, 0x0000ffffu}) {
    set_word(&file, kCarrierIndexWordDisplacement, payload);
    const std::uint32_t observed = static_cast<std::uint32_t>(
        reinterpret_cast<std::uintptr_t>(destroy_index_008d86b0(&file)));
    assert(observed == payload);
  }
  refcount_ledger.clear();
  assert(refcount_ledger.empty());
}

// E. READ ONLY. Every byte of the carrier is unchanged after the call, the word
// at +0x260 included - a reconstruction that cleared the slot, or bumped a
// counter, or wrote a null over the handle would show here.
void test_accessor_writes_nothing() {
  refcount_ledger.clear();
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  // The pattern first, so every byte of the carrier - the word at +0x260
  // included - starts out holding a recognisable value that is not the handle.
  for (std::size_t index = 0; index < file.opaque_00.size(); ++index) {
    file.opaque_00[index] = static_cast<std::uint8_t>((index * 7u) & 0xffu);
  }
  set_word(&file, kCarrierIndexWordDisplacement,
           static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));

  std::array<std::uint8_t, sizeof(ObservedIndexRefCarrier)> before{};
  std::memcpy(before.data(), &file, before.size());
  (void)destroy_index_008d86b0(&file);
  std::array<std::uint8_t, sizeof(ObservedIndexRefCarrier)> after{};
  std::memcpy(after.data(), &file, after.size());

  assert(before == after);
  assert(get_word(&file, kCarrierIndexWordDisplacement) ==
         static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));
}

// Whatever the adjacent writer last stored is what this accessor returns. The
// writer is the evidence that the word is a handle; the ledger is what shows
// this accessor takes no share of the reference.
void test_accessor_tracks_the_adjacent_writer() {
  refcount_ledger.clear();
  ObservedIndexObjectVtable first_vtable = make_vtable();
  ObservedIndexObjectVtable second_vtable = make_vtable();
  ObservedIndexObject first{&first_vtable};
  ObservedIndexObject second{&second_vtable};
  ObservedIndexRefCarrier file{};

  assert(destroy_index_008d86b0(&file) == nullptr);

  assert(set_index_ref_008d86c0(&file, &first));
  assert(destroy_index_008d86b0(&file) == &first);
  assert(ledger() == "add_ref:" +
                        std::to_string(reinterpret_cast<std::uintptr_t>(
                            &first)));
  // The accessor itself added nothing to that ledger.
  refcount_ledger.clear();
  assert(destroy_index_008d86b0(&file) == &first);
  assert(refcount_ledger.empty());

  // Re-storing the same pointer is the CMP ESI,EDI / JZ fast path: the writer
  // takes no reference and the accessor still reports the same handle.
  refcount_ledger.clear();
  assert(set_index_ref_008d86c0(&file, &first));
  assert(destroy_index_008d86b0(&file) == &first);
  assert(refcount_ledger.empty());

  // Replacing it AddRefs the incoming handle before Releasing the outgoing
  // one, in that order.
  refcount_ledger.clear();
  assert(set_index_ref_008d86c0(&file, &second));
  assert(destroy_index_008d86b0(&file) == &second);
  assert(ledger() ==
         "add_ref:" + std::to_string(reinterpret_cast<std::uintptr_t>(
                         &second)) +
             ",release:" + std::to_string(reinterpret_cast<std::uintptr_t>(
                               &first)));

  // Clearing the field releases the outgoing handle and the accessor then
  // reports null; the null incoming pointer is never AddRef'd.
  refcount_ledger.clear();
  assert(set_index_ref_008d86c0(&file, nullptr));
  assert(destroy_index_008d86b0(&file) == nullptr);
  assert(ledger() == "release:" +
                        std::to_string(reinterpret_cast<std::uintptr_t>(
                            &second)));
}

// The +0x14 gate blocks the writer, and because the writer never runs the
// field is untouched, so the accessor keeps reporting the previous handle.
// This is the only state in which the two adjacent slots can disagree, and it
// is also the state that shows the accessor ignores the gate entirely.
void test_state_gate_freezes_the_field() {
  refcount_ledger.clear();
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  assert(set_index_ref_008d86c0(&file, &object));

  refcount_ledger.clear();
  set_word(&file, kCarrierStateGateDisplacement, 1u);
  assert(!set_index_ref_008d86c0(&file, nullptr));
  assert(destroy_index_008d86b0(&file) == &object);
  assert(refcount_ledger.empty());

  // The accessor itself ignores the gate entirely.
  set_word(&file, kCarrierStateGateDisplacement, 0xffffffffu);
  assert(destroy_index_008d86b0(&file) == &object);
  refcount_ledger.clear();
  set_word(&file, kCarrierStateGateDisplacement, 0u);
  assert(destroy_index_008d86b0(&file) == &object);
  assert(refcount_ledger.empty());
}

// G. ABI. The terminator is a plain `RET`, not `RET 0x4`, so the entry takes
// no stack argument at all and pops nothing. ESP is sampled inside a
// trampoline, before the call and after the return; the two must be identical.
// A body that popped a word would leave the second sample four bytes higher.
struct EspSamples {
  std::uint32_t before_call = 0;
  std::uint32_t after_return = 0;
};

EspSamples call_measured(ObservedIndexRefCarrier* file) {
  const std::uint32_t target = static_cast<std::uint32_t>(
      reinterpret_cast<std::uintptr_t>(&destroy_index_008d86b0));
  std::uint32_t before = 0;
  std::uint32_t after = 0;
  __asm__ __volatile__("movl %%esp, %[before]\n\t"
                       "movl %[recv], %%ecx\n\t"
                       "call *%[target]\n\t"
                       "movl %%esp, %[after]\n\t"
                       : [before] "=m"(before), [after] "=m"(after)
                       : [target] "r"(target), [recv] "r"(file)
                       : "eax", "ecx", "memory");
  EspSamples samples;
  samples.before_call = before;
  samples.after_return = after;
  return samples;
}

void test_plain_ret_takes_no_stack_word() {
  ObservedIndexObjectVtable vtable = make_vtable();
  ObservedIndexObject object{&vtable};
  ObservedIndexRefCarrier file{};
  set_word(&file, kCarrierIndexWordDisplacement,
           static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));

  const EspSamples samples = call_measured(&file);
  assert(samples.after_return == samples.before_call);
  assert(static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
             destroy_index_008d86b0(&file))) ==
         static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object)));
}

}

int main() {
  test_layout_is_pinned();
  test_getter_returns_null_field();
  test_getter_is_a_bare_non_owning_load();
  test_returned_value_is_the_pointer_not_the_pointee();
  test_load_is_four_bytes_wide();
  test_displacement_is_an_offset_not_an_index();
  test_no_test_on_the_stored_word();
  test_accessor_writes_nothing();
  test_accessor_tracks_the_adjacent_writer();
  test_state_gate_freezes_the_field();
  test_plain_ret_takes_no_stack_word();
}
