#include <setjmp.h>

#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "dogfood_00580cb0_a1.hpp"

// The ports are declared in the header under macros that are undefined at the
// end of it, so the recording stubs below restate the conventions explicitly.
#if defined(_MSC_VER)
#define PKG_DF5_THISCALL __thiscall
#define PKG_DF5_CDECL __cdecl
#else
#define PKG_DF5_THISCALL __attribute__((thiscall))
#define PKG_DF5_CDECL __attribute__((cdecl))
#endif

namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1 {
namespace {

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

// The dispatch sequence the body performs, in order.
//
// The model test asserts the whole sequence and not only its endpoints, because
// the order is what separates this body from a plausible rearrangement of it.
// Four orderings in particular carry meaning and each has a test below: the
// store of 1 sits between the load of slot +0x18 and the call of it; the
// handle's slot +0x00 dispatch happens before the constructor while the peer's
// two dispatches happen after the destructor; the promote call sits between the
// peer's second dispatch and the final dispatch; and the final dispatch is last
// and is outside the guard.
enum class Step {
  FillBase,
  FormatTmp,
  FormatDb,
  Open,
  HandleSlot00,
  ContextCtor,
  ContextPredicate,
  Field08Slot20,
  Field08Slot18,
  PropertyWrite,
  SinkSetup,
  SinkCommit,
  ContextDtor,
  PeerSlot1c,
  PeerSlot08,
  Promote,
  HandleSlot04,
  step_count
};

constexpr unsigned kStepCount = static_cast<unsigned>(Step::step_count);

const char *step_name(Step step) {
  switch (step) {
    case Step::FillBase:
      return "fill base (0x00580cc3)";
    case Step::FormatTmp:
      return "format tmp (0x00580cdf)";
    case Step::FormatDb:
      return "format db (0x00580cfb)";
    case Step::Open:
      return "open (0x00580d08)";
    case Step::HandleSlot00:
      return "handle slot +0x00 (0x00580d20)";
    case Step::ContextCtor:
      return "context ctor (0x00580d36)";
    case Step::ContextPredicate:
      return "context predicate (0x00580d3f)";
    case Step::Field08Slot20:
      return "field08 slot +0x20 (0x00580d4d)";
    case Step::Field08Slot18:
      return "nested slot +0x18 (0x00580d5e)";
    case Step::PropertyWrite:
      return "property write (0x00580d6a)";
    case Step::SinkSetup:
      return "sink setup (0x00580d84)";
    case Step::SinkCommit:
      return "sink commit (0x00580d95)";
    case Step::ContextDtor:
      return "context dtor (0x00580d9e)";
    case Step::PeerSlot1c:
      return "peer slot +0x1c (0x00580dae)";
    case Step::PeerSlot08:
      return "peer slot +0x08 (0x00580db7)";
    case Step::Promote:
      return "promote (0x00580dc9)";
    case Step::HandleSlot04:
      return "handle slot +0x04 (0x00580dd8)";
    case Step::step_count:
      break;
  }
  return "?";
}

// Everything the model forwarded, captured by identity.
struct Trace {
  unsigned count = 0u;
  Step order[kStepCount] = {};

  const void *base_buffer = nullptr;
  const void *format_tmp_destination = nullptr;
  const void *format_tmp_source = nullptr;
  const void *format_db_destination = nullptr;
  const void *format_db_source = nullptr;
  std::size_t format_count = 0u;
  const void *open_name = nullptr;

  const void *ctor_receiver = nullptr;
  const void *ctor_handle = nullptr;
  const void *ctor_arg2 = nullptr;
  const void *ctor_arg3 = nullptr;
  const void *ctor_arg4 = nullptr;
  OpaqueWord ctor_installed_vtable = 0u;

  const void *predicate_receiver = nullptr;
  const void *slot20_receiver = nullptr;
  const void *slot18_receiver = nullptr;

  const void *write_target = nullptr;
  const void *write_source = nullptr;
  OpaqueWord write_count = 0u;
  OpaqueWord write_mode = 0u;
  OpaqueWord observed_one = 0u;

  const void *sink_setup_receiver = nullptr;
  const void *sink_setup_owner = nullptr;
  const void *sink_setup_global = nullptr;
  OpaqueWord sink_setup_tag = 0u;
  const void *sink_commit_receiver = nullptr;
  const void *sink_commit_field = nullptr;

  const void *dtor_receiver = nullptr;

  const void *peer1c_receiver = nullptr;
  const void *peer08_receiver = nullptr;

  const void *promote_source = nullptr;
  const void *promote_destination = nullptr;
  bool promote_ranges_disjoint = false;
  OpaqueChar destination_first_unit = 0;
  OpaqueChar source_first_unit = 0;

  const void *final_receiver = nullptr;

  bool contains(Step step) const {
    for (unsigned index = 0u; index < count; ++index) {
      if (order[index] == step) {
        return true;
      }
    }
    return false;
  }

  unsigned index_of(Step step) const {
    for (unsigned index = 0u; index < count; ++index) {
      if (order[index] == step) {
        return index;
      }
    }
    return count;
  }
};

Trace g_trace;

// The five tables the model dispatches through, and the objects the stubs hand
// back. install_tables() wires the stubs into the tables once, before any test.
OpaqueHandleVTable g_handle_vtable = {};
OpaqueHandlePeerVTable g_peer_vtable = {};
OpaqueContextField08VTable g_field08_vtable = {};
OpaqueSlot20ResultVTable g_slot20_vtable = {};
OpaqueSlot18ResultVTable g_slot18_vtable = {};

alignas(4) OpaqueByte g_field08_storage[0x40] = {};
alignas(4) OpaqueByte g_slot18_storage[0x40] = {};

OpaqueContextField08 *g_field08 = nullptr;
OpaqueSlot20Result *g_slot20 = nullptr;
OpaqueSlot18Result *g_slot18 = nullptr;
OpaqueHandle *g_open_result = nullptr;
OpaqueWord g_final_result = 0u;

void record(Step step) {
  check(g_trace.count < kStepCount);
  g_trace.order[g_trace.count] = step;
  ++g_trace.count;
}

// A whole object graph for one model call. Every test builds one of these, so
// no test can depend on state another left behind.
struct Scene {
  OpaqueHandle handle = {};
  OpaqueHandlePeer peer = {};
  OpaqueSlot20Result nested = {};
  OpaqueEditorCommitOwner owner = {};
};

void build_scene(Scene &scene, OpaqueWord final_result) {
  scene.handle.vtable_00 = &g_handle_vtable;
  scene.handle.peer_04 = &scene.peer;
  scene.peer.vtable_00 = &g_peer_vtable;
  scene.nested.vtable_00 = &g_slot20_vtable;
  g_slot20 = &scene.nested;
  g_field08 = reinterpret_cast<OpaqueContextField08 *>(g_field08_storage);
  g_field08->vtable_00 = &g_field08_vtable;
  g_slot18 = reinterpret_cast<OpaqueSlot18Result *>(g_slot18_storage);
  g_slot18->vtable_00 = &g_slot18_vtable;
  g_final_result = final_result;
  scene.owner.word_000 = 0xfeedfaceu;
}

// One model call. Passing null for handle_to_open models the failure path of
// 0x00688fa0, which faults inside the model by design; see the fault test.
OpaqueWord run_model(Scene &scene, OpaqueHandle *handle_to_open) {
  g_open_result = handle_to_open;
  g_trace = Trace{};
  return dogfood_editor_commit_fun_00580cb0(&scene.owner);
}

std::ptrdiff_t byte_distance(const void *higher, const void *lower) {
  return static_cast<const OpaqueByte *>(higher) -
         static_cast<const OpaqueByte *>(lower);
}

}  // namespace

// ---------------------------------------------------------------------------
// The six table slots the body dispatches through, as thiscall stubs.
//
// These are the six register-indirect calls of the original. Each is reached
// through the inline asm in the library source, which is what makes the emitted
// call a register-indirect one with the receiver in ECX.
// ---------------------------------------------------------------------------

extern "C" void PKG_DF5_THISCALL slot_handle_00(OpaqueHandle *self) {
  record(Step::HandleSlot00);
  (void)self;
}

extern "C" OpaqueWord PKG_DF5_THISCALL slot_handle_04(OpaqueHandle *self) {
  record(Step::HandleSlot04);
  g_trace.final_receiver = self;
  return g_final_result;
}

extern "C" void PKG_DF5_THISCALL slot_peer_1c(OpaqueHandlePeer *self) {
  record(Step::PeerSlot1c);
  g_trace.peer1c_receiver = self;
}

extern "C" void PKG_DF5_THISCALL slot_peer_08(OpaqueHandlePeer *self) {
  record(Step::PeerSlot08);
  g_trace.peer08_receiver = self;
}

extern "C" OpaqueSlot20Result *PKG_DF5_THISCALL
slot_field08_20(OpaqueContextField08 *self) {
  record(Step::Field08Slot20);
  g_trace.slot20_receiver = self;
  return g_slot20;
}

extern "C" OpaqueSlot18Result *PKG_DF5_THISCALL
slot_nested_18(OpaqueSlot20Result *self) {
  record(Step::Field08Slot18);
  g_trace.slot18_receiver = self;
  return g_slot18;
}

// ---------------------------------------------------------------------------
// The ten ports, as recording stand-ins.
//
// None of these VAs is promoted by this package and none of them is a real
// reconstruction. Each records what the model handed it and returns a value the
// test chooses, so the argument identities, the argument order and the dispatch
// sequence are all observable without a second reconstruction in the way.
// ---------------------------------------------------------------------------

extern "C" void PKG_DF5_CDECL unresolved_00580c10(OpaqueChar *buffer) {
  record(Step::FillBase);
  g_trace.base_buffer = buffer;
  // 0x00580c10 writes a base name, not a whole 0x200 byte buffer. Seeding the
  // first units makes the argument identity observable downstream through the
  // %s source of both format calls.
  buffer[0] = u'b';
  buffer[1] = u'a';
  buffer[2] = u's';
  buffer[3] = u'e';
  buffer[4] = u'\0';
}

// The original pushes the two format strings as absolute addresses
// (0x00580ccd pushes 0x013f5c74, 0x00580ce9 pushes 0x013f5c68), and the model
// reproduces those immediates literally, so the stand-in identifies a format by
// the address it was handed rather than by the identity of a local object. The
// contents at those addresses are checked separately against kFmtDbTmp/kFmtDb.
extern "C" OpaqueWord PKG_DF5_CDECL unresolved_00939a30(
    OpaqueChar *destination, std::size_t count, const OpaqueChar *format, ...) {
  std::va_list arguments;
  va_start(arguments, format);
  const OpaqueChar *source = va_arg(arguments, const OpaqueChar *);
  va_end(arguments);

  g_trace.format_count = count;
  if (format == reinterpret_cast<const OpaqueChar *>(0x013f5c74u)) {
    record(Step::FormatTmp);
    g_trace.format_tmp_destination = destination;
    g_trace.format_tmp_source = source;
  } else if (format == reinterpret_cast<const OpaqueChar *>(0x013f5c68u)) {
    record(Step::FormatDb);
    g_trace.format_db_destination = destination;
    g_trace.format_db_source = source;
  } else {
    check(false);
  }
  return 0u;
}

extern "C" OpaqueHandle *PKG_DF5_CDECL
unresolved_00688fa0(const OpaqueChar *name) {
  record(Step::Open);
  g_trace.open_name = name;
  return g_open_result;
}

extern "C" void PKG_DF5_THISCALL unresolved_00693d60(OpaqueCommitContext *self,
                                                     OpaqueHandle *handle,
                                                     const OpaqueWord *arg2,
                                                     const OpaqueWord *arg3,
                                                     const OpaqueWord *arg4) {
  record(Step::ContextCtor);
  g_trace.ctor_receiver = self;
  g_trace.ctor_handle = handle;
  g_trace.ctor_arg2 = arg2;
  g_trace.ctor_arg3 = arg3;
  g_trace.ctor_arg4 = arg4;
  // Reproduce what 0x00693d60 does to the object, so the model's own reads of
  // it read a real pointer rather than a null one:
  //   0x00693d7b MOV dword ptr [ESI],0x1403970
  //   0x00693d85 MOV dword ptr [ESI + 0x4],EAX
  //   0x00693d8c MOV dword ptr [ESI + 0x8],EAX
  self->vtable_00 = 0x01403970u;
  self->field_04 = 0u;
  self->field_08 = g_field08;
  g_trace.ctor_installed_vtable = self->vtable_00;
}

extern "C" OpaqueWord PKG_DF5_THISCALL
unresolved_00692ea0(OpaqueCommitContext *self) {
  record(Step::ContextPredicate);
  g_trace.predicate_receiver = self;
  // 0x00692ea0 returns 0 when field +0x08 is null and otherwise the truth of
  // that field's slot +0x18. The model discards the result, so the value here
  // does not affect the sequence; it is recorded so a model that branched on it
  // would show.
  return self->field_08 == nullptr ? 0u : 1u;
}

extern "C" OpaqueWord PKG_DF5_CDECL
unresolved_0093aa70(OpaqueSlot18Result *target, const OpaqueWord *source,
                    OpaqueWord count, OpaqueWord mode) {
  record(Step::PropertyWrite);
  g_trace.write_target = target;
  g_trace.write_source = source;
  g_trace.write_count = count;
  g_trace.write_mode = mode;
  // 0x0093aa70 reads the dword the model pointed at, so both the identity of
  // that address and the value stored into it are observable here.
  g_trace.observed_one = *source;
  return 0u;
}

extern "C" OpaqueCommitSink *PKG_DF5_THISCALL
unresolved_00692f90(OpaqueCommitSink *self, OpaqueEditorCommitOwner *owner,
                    const OpaqueWord *global, OpaqueWord tag) {
  record(Step::SinkSetup);
  g_trace.sink_setup_receiver = self;
  g_trace.sink_setup_owner = owner;
  g_trace.sink_setup_global = global;
  g_trace.sink_setup_tag = tag;
  // 0x00692f90 ends with MOV EAX,ECX, so it returns its own receiver.
  return self;
}

extern "C" OpaqueWord PKG_DF5_THISCALL
unresolved_00692900(OpaqueCommitSink *self, OpaqueContextField08 *field_08) {
  record(Step::SinkCommit);
  g_trace.sink_commit_receiver = self;
  g_trace.sink_commit_field = field_08;
  return 1u;
}

extern "C" void PKG_DF5_THISCALL
unresolved_00693900(OpaqueCommitContext *self) {
  record(Step::ContextDtor);
  g_trace.dtor_receiver = self;
  // 0x00693900 re-installs the table at +0x00 before releasing the two
  // sub-objects, the vtable-reset idiom.
  self->vtable_00 = 0x01403970u;
  self->field_04 = 0u;
  self->field_08 = nullptr;
}

extern "C" void PKG_DF5_CDECL
unresolved_006891f0(const OpaqueChar *source, const OpaqueChar *destination) {
  record(Step::Promote);
  g_trace.promote_source = source;
  g_trace.promote_destination = destination;
  // The two buffers are separate 0x200 byte objects, so their ranges do not
  // overlap. Proving it here rather than by pointer arithmetic alone: a marker
  // written into the source must not be readable in the destination.
  g_trace.promote_ranges_disjoint = (source + kPathUnits <= destination) ||
                                    (destination + kPathUnits <= source);
  const OpaqueChar marker = u'Z';
  const_cast<OpaqueChar *>(source)[0] = marker;
  g_trace.destination_first_unit = destination[0];
  g_trace.source_first_unit = marker;
}

namespace {

void install_tables() {
  g_handle_vtable.slot_00 = &slot_handle_00;
  g_handle_vtable.slot_04 = &slot_handle_04;
  g_peer_vtable.slot_1c = &slot_peer_1c;
  g_peer_vtable.slot_08 = &slot_peer_08;
  g_field08_vtable.slot_20 = &slot_field08_20;
  g_slot20_vtable.slot_18 = &slot_nested_18;
}

// ---------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------

// The whole dispatch sequence, in the order the 91 instructions perform it.
// Every step is pinned to the instruction that fixes it and the order is
// checked too.
void test_dispatch_sequence_matches_the_body() {
  Scene scene;
  build_scene(scene, 0u);

  const OpaqueWord returned = run_model(scene, &scene.handle);

  const Step expected[] = {Step::FillBase,         Step::FormatTmp,
                           Step::FormatDb,         Step::Open,
                           Step::HandleSlot00,     Step::ContextCtor,
                           Step::ContextPredicate, Step::Field08Slot20,
                           Step::Field08Slot18,    Step::PropertyWrite,
                           Step::SinkSetup,        Step::SinkCommit,
                           Step::ContextDtor,      Step::PeerSlot1c,
                           Step::PeerSlot08,       Step::Promote,
                           Step::HandleSlot04};
  const unsigned expected_count =
      static_cast<unsigned>(sizeof(expected) / sizeof(expected[0]));
  // Seventeen steps, which is kStepCount: the array is sized to hold them all.
  check(expected_count == kStepCount);
  check(g_trace.count == expected_count);
  for (unsigned index = 0u; index < expected_count; ++index) {
    if (g_trace.order[index] != expected[index]) {
      std::fprintf(stderr, "step %u: expected %s, got %s\n", index,
                   step_name(expected[index]), step_name(g_trace.order[index]));
      std::abort();
    }
  }
  check(returned == 0u);
  // Seventeen steps, of which ten are direct calls to ports and six are
  // register-indirect calls through table slots. The store of 1 is not a call,
  // so it is not a step.
  check(g_trace.count == 10u + 6u + 1u);
}

// The store of 1 lands between the load of slot +0x18 and the call of it. That
// is observable from one side only, as "the word already reads 1 when
// 0x0093aa70 reads it". A model that stored it after the call, or never stored
// it, fails here.
void test_one_is_stored_before_the_property_write() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.observed_one == 1u);
  check(g_trace.write_source != nullptr);
  // The word is at frame offset 0x000, one dword below the frame object's own
  // first word at 0x004. That relation is what fixes the frame base.
  check(byte_distance(g_trace.ctor_receiver, g_trace.write_source) == 4);
  // And the store is before the property write in the sequence, not after.
  check(g_trace.index_of(Step::Field08Slot18) <
        g_trace.index_of(Step::PropertyWrite));
}

// The constructor's four arguments: the frame object as receiver, the handle,
// and the address 0x01897c18 in all three remaining slots.
void test_constructor_arguments() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.ctor_receiver != nullptr);
  check(g_trace.ctor_handle == &scene.handle);
  check(g_trace.ctor_arg2 != nullptr);
  check(g_trace.ctor_arg2 == g_trace.ctor_arg3);
  check(g_trace.ctor_arg3 == g_trace.ctor_arg4);
  // All three are the same address, and it is neither the handle nor the
  // object. The address itself is the immediate 0x00580d22/0x00580d27/
  // 0x00580d2c push, so it is checked exactly rather than merely for
  // non-nullness.
  check(g_trace.ctor_arg2 == reinterpret_cast<const void *>(0x01897c18u));
  check(g_trace.ctor_arg2 != g_trace.ctor_handle);
  check(static_cast<const void *>(g_trace.ctor_arg2) != g_trace.ctor_receiver);
  // The table the constructor installs is the one 0x00693d7b stores.
  check(g_trace.ctor_installed_vtable == 0x01403970u);
  // The predicate and the destructor see the object the constructor did.
  check(g_trace.predicate_receiver == g_trace.ctor_receiver);
  check(g_trace.dtor_receiver == g_trace.ctor_receiver);
  // The frame object is the twelve byte one: 0x00693d60 writes +0x00, +0x04 and
  // +0x08 and nothing beyond.
  check(sizeof(OpaqueCommitContext) == 0x0c);
}

// The three path buffers are 0x200 bytes apart and both are formatted from the
// base buffer, never from each other. The identities come from the pointers the
// model passed and, for the variadic %s source, from what the recorder read
// back out of the va_list.
void test_path_buffers_are_distinct_and_both_formatted_from_the_base() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.base_buffer != nullptr);
  check(g_trace.format_tmp_destination != nullptr);
  check(g_trace.format_db_destination != nullptr);
  check(g_trace.format_tmp_destination != g_trace.format_db_destination);
  check(g_trace.format_tmp_destination != g_trace.base_buffer);
  check(g_trace.format_db_destination != g_trace.base_buffer);
  // 0x200 apart, which is the spacing the six LEA/MOV pairs measure. The final
  // name sits above the temporary one, at frame offset 0x410 against 0x210.
  check(byte_distance(g_trace.format_db_destination,
                      g_trace.format_tmp_destination) == 0x200);
  check(byte_distance(g_trace.format_tmp_destination, g_trace.base_buffer) ==
        0x200);
  check(byte_distance(g_trace.format_db_destination, g_trace.base_buffer) ==
        0x400);
  // Both read the base buffer.
  check(g_trace.format_tmp_source == g_trace.base_buffer);
  check(g_trace.format_db_source == g_trace.base_buffer);
  check(g_trace.format_count == 0x100);
  // The temporary is what gets opened.
  check(g_trace.open_name == g_trace.format_tmp_destination);
  // The promote call takes the temporary as its source and the final name as
  // its destination, in that order, and runs after the peer's second dispatch.
  check(g_trace.promote_source == g_trace.format_tmp_destination);
  check(g_trace.promote_destination == g_trace.format_db_destination);
  check(g_trace.index_of(Step::PeerSlot08) < g_trace.index_of(Step::Promote));
  check(g_trace.index_of(Step::Promote) < g_trace.index_of(Step::HandleSlot04));
}

// Both sink calls take the same receiver, the object at frame offset 0x610, and
// the setup call is the only place the original receiver is used at all.
void test_sink_receiver_and_the_single_use_of_this() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.sink_setup_receiver != nullptr);
  check(g_trace.sink_setup_receiver == g_trace.sink_commit_receiver);
  check(g_trace.sink_commit_field == g_field08);
  // The sink sits 0x60c bytes above the frame object's first word: 12 bytes of
  // object at +0x004, the base buffer at +0x010, two more 0x200 buffers, then
  // the sink at +0x610, with no untouched band between the last buffer and the
  // sink. 0x004 + 0x60c = 0x610, the offset 0x00580d7d and 0x00580d8e address.
  check(byte_distance(g_trace.sink_setup_receiver, g_trace.ctor_receiver) ==
        0x60c);
  check(offsetof(OpaqueCommitFrame, sink) -
            offsetof(OpaqueCommitFrame, context) ==
        0x60c);
  // The sink is 0xa10 bytes wide by 0x00692900's widest read at +0xa0c, so it
  // ends at 0x1020, inside the 0x1024 block the probe reserved.
  check(sizeof(OpaqueCommitSink) == 0xa10);
  check(offsetof(OpaqueCommitFrame, sink) + sizeof(OpaqueCommitSink) <= 0x1024);
  // The original receiver is forwarded unchanged, once, as the second argument.
  check(g_trace.sink_setup_owner == &scene.owner);
  check(g_trace.sink_setup_global != nullptr);
  // The second argument is the address 0x00580d77 pushes and the third is the
  // constant 0x00580d72 pushes; neither is dereferenced by this body.
  check(g_trace.sink_setup_global ==
        reinterpret_cast<const void *>(0x0150d100u));
  check(g_trace.sink_setup_tag == 0x1a80d26u);
  // The original never dereferences its receiver, so the one word the model
  // gave it keeps the value the test seeded. A model that read it would differ.
  check(scene.owner.word_000 == 0xfeedfaceu);
}

// The two peer dispatches both take the word at handle + 0x4 as their receiver,
// and the final dispatch takes the handle itself.
void test_peer_receivers_are_the_handles_second_word() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.peer1c_receiver == &scene.peer);
  check(g_trace.peer08_receiver == &scene.peer);
  check(g_trace.final_receiver == &scene.handle);
  // The receiver object the model was called with is neither handle, so a model
  // that confused them would be caught here.
  check(static_cast<const void *>(&scene.owner) !=
        static_cast<const void *>(&scene.handle));
  check(static_cast<const void *>(&scene.owner) !=
        static_cast<const void *>(&scene.peer));
}

// The field +0x08 chain: the model reads it out of the frame object, dispatches
// slot +0x20 on it, and dispatches slot +0x18 on what that returns.
void test_field08_chain() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.slot20_receiver == g_field08);
  check(g_trace.slot18_receiver == &scene.nested);
  check(g_trace.write_target == g_slot18);
  check(g_trace.write_count == 1u);
  check(g_trace.write_mode == 0u);
}

// The return value is the dword the final dispatch leaves in EAX, bit-exact
// over the whole 32-bit space's corners. Nothing after that dispatch touches
// EAX in the original, so the value is forwarded rather than recomputed.
void test_return_is_the_final_dispatch_dword() {
  const OpaqueWord seeds[] = {0x00000000u, 0x00000001u, 0x7fffffffu,
                              0x80000000u, 0xffffffffu, 0xcafebabeu};
  for (const OpaqueWord seed : seeds) {
    Scene scene;
    build_scene(scene, seed);
    check(run_model(scene, &scene.handle) == seed);
  }
}

// The final dispatch is last and is outside the guard, which is the structural
// consequence of the JZ targeting the first instruction of the tail rather than
// the end of the function.
void test_final_dispatch_is_last_and_outside_the_guard() {
  Scene scene;
  build_scene(scene, 0x12345678u);
  check(run_model(scene, &scene.handle) == 0x12345678u);
  check(g_trace.index_of(Step::HandleSlot04) == g_trace.count - 1u);
  // The handle's slot +0x00 dispatch is inside the guard, before the
  // constructor, and both peer dispatches are after the destructor, in the
  // tail.
  check(g_trace.index_of(Step::HandleSlot00) <
        g_trace.index_of(Step::ContextCtor));
  check(g_trace.index_of(Step::ContextDtor) <
        g_trace.index_of(Step::PeerSlot1c));
  check(g_trace.index_of(Step::PeerSlot1c) <
        g_trace.index_of(Step::PeerSlot08));
}

// The model writes nothing outside its own frame.
//
// The original never dereferences its receiver, and the only objects it reaches
// are the ones 0x00688fa0 returned, all of which it reads and dispatches
// through without writing. So a snapshot of the caller's object graph must be
// bit-identical after the call. A model that scribbled on the receiver, or on
// the handle, or on the sub-object, would fail here.
void test_model_writes_nothing_outside_its_own_frame() {
  Scene scene;
  build_scene(scene, 0u);

  OpaqueByte before[sizeof(Scene)];
  std::memcpy(before, &scene, sizeof(scene));
  OpaqueByte field08_before[sizeof(g_field08_storage)];
  std::memcpy(field08_before, g_field08_storage, sizeof(g_field08_storage));
  OpaqueByte slot18_before[sizeof(g_slot18_storage)];
  std::memcpy(slot18_before, g_slot18_storage, sizeof(g_slot18_storage));

  run_model(scene, &scene.handle);

  check(std::memcmp(before, &scene, sizeof(scene)) == 0);
  check(std::memcmp(field08_before, g_field08_storage,
                    sizeof(g_field08_storage)) == 0);
  check(std::memcmp(slot18_before, g_slot18_storage,
                    sizeof(g_slot18_storage)) == 0);
  // The receiver's one word is untouched in particular: the original copies ECX
  // to EDI and never reads it back.
  check(scene.owner.word_000 == 0xfeedfaceu);
}

// The two format destinations are separate 0x200 byte objects, so a marker
// written into the temporary name is not readable in the final name. A model
// that passed the same buffer twice, or two overlapping ones, would fail here.
void test_promote_operates_on_two_disjoint_buffers() {
  Scene scene;
  build_scene(scene, 0u);
  run_model(scene, &scene.handle);

  check(g_trace.promote_ranges_disjoint);
  check(g_trace.source_first_unit == u'Z');
  // The final name still holds whatever the format call left in it, which the
  // recorder did not touch, so it cannot read back as the marker.
  check(g_trace.destination_first_unit != u'Z');
  check(byte_distance(g_trace.promote_destination, g_trace.promote_source) ==
        0x200);
}

// The two format strings are the two the image carries, and the body pushes no
// other address.
void test_format_strings_and_constants_are_the_observed_ones() {
  check(sizeof(kFmtDbTmp) == 0x14);
  check(sizeof(kFmtDb) == 0x0c);
  check(std::memcmp(kFmtDbTmp, u"%s.db.tmp", sizeof(kFmtDbTmp)) == 0);
  check(std::memcmp(kFmtDb, u"%s.db", sizeof(kFmtDb)) == 0);
  // The gap between the two in the image is 0x0c, which is the width of the
  // first one: 0x013f5c74 - 0x013f5c68 == 0x0c.
  check(0x013f5c74 - 0x013f5c68 == sizeof(kFmtDb));
  // The immediate the body pushes is a constant, not an address.
  check(kCommitTag == 0x1a80d26u);
  // The table this body lives in: 0x013f57f8 + 0x54 is its only incoming xref.
  check(kVtableSlotOffset == 0x54);
  check(0x013f57f8 + kVtableSlotOffset == 0x013f584c);
}

// The reproduced defect, proved rather than asserted.
//
// When 0x00688fa0 returns null the original's JZ at 0x00580d14 jumps to
// 0x00580da3, whose first instruction is "MOV EAX,dword ptr [ESI + 4]". So the
// original dereferences null on the failure path. This test drives that path
// with a null handle inside a fault trap and requires the fault to happen, and
// requires the guarded block to have been skipped before it does.
//
// A model that quietly added a null guard would return normally here and the
// check would fail. That is the point: the model reproduces the bytes rather
// than repairing them.
sigjmp_buf g_fault_env;
volatile sig_atomic_t g_fault_taken = 0;

extern "C" void commit_fault_handler(int signal_number) {
  (void)signal_number;
  g_fault_taken = 1;
  siglongjmp(g_fault_env, 1);
}

void test_null_handle_reproduces_the_unguarded_dereference() {
  Scene scene;
  build_scene(scene, 0u);
  g_fault_taken = 0;

  void (*previous_segv)(int) = signal(SIGSEGV, &commit_fault_handler);
  void (*previous_bus)(int) = signal(SIGBUS, &commit_fault_handler);
  check(previous_segv != SIG_ERR);
  check(previous_bus != SIG_ERR);

  if (sigsetjmp(g_fault_env, 1) == 0) {
    (void)run_model(scene, nullptr);
    // Returning normally means the model guarded a dereference the original
    // does not guard. That is a different function.
    check(false);
  }

  check(signal(SIGSEGV, previous_segv) != SIG_ERR);
  check(signal(SIGBUS, previous_bus) != SIG_ERR);

  check(g_fault_taken == 1);
  // The fault has to come after the branch and not before it: the fill, both
  // formats and the open all ran, and nothing inside the guarded block did.
  check(g_trace.count == 4u);
  check(g_trace.order[0] == Step::FillBase);
  check(g_trace.order[1] == Step::FormatTmp);
  check(g_trace.order[2] == Step::FormatDb);
  check(g_trace.order[3] == Step::Open);
  check(!g_trace.contains(Step::ContextCtor));
  check(!g_trace.contains(Step::ContextPredicate));
  check(!g_trace.contains(Step::Field08Slot20));
  check(!g_trace.contains(Step::SinkSetup));
  check(!g_trace.contains(Step::SinkCommit));
  check(!g_trace.contains(Step::ContextDtor));
  check(!g_trace.contains(Step::PeerSlot08));
  check(!g_trace.contains(Step::Promote));
  check(!g_trace.contains(Step::HandleSlot04));
}

int run_tests() {
  install_tables();
  test_dispatch_sequence_matches_the_body();
  test_one_is_stored_before_the_property_write();
  test_constructor_arguments();
  test_path_buffers_are_distinct_and_both_formatted_from_the_base();
  test_sink_receiver_and_the_single_use_of_this();
  test_peer_receivers_are_the_handles_second_word();
  test_field08_chain();
  test_return_is_the_final_dispatch_dword();
  test_final_dispatch_is_last_and_outside_the_guard();
  test_model_writes_nothing_outside_its_own_frame();
  test_promote_operates_on_two_disjoint_buffers();
  test_format_strings_and_constants_are_the_observed_ones();
  test_null_handle_reproduces_the_unguarded_dereference();
  return 0;
}

}  // namespace
}  // namespace openspore::reconstruction::pkg_dogfood_00580cb0_a1

int main() {
  return openspore::reconstruction::pkg_dogfood_00580cb0_a1::run_tests();
}
