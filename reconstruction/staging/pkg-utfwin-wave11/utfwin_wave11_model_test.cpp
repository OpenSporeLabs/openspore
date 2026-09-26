#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_wave11.hpp"

extern "C" {
std::uint32_t pkg_utfwin_wave11_g_word_01485720 = 0x3f800000u;
}

namespace openspore::reconstruction::pkg_utfwin_wave11 {
namespace model {

enum class Kind : std::uint8_t {
  base_construct,
  base_destroy,
  release,
  reference_add,
  reference_release,
};

struct Event {
  Kind kind;
  Opaque object;
  Opaque value;
};

constexpr std::size_t kEventCapacity = 32;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Event events[kEventCapacity];
std::size_t event_count;
Opaque released_object;
std::size_t released_count;
bool base_destroy_writes_vtables;

Opaque base_field_08;
Opaque base_byte_05;
Opaque base_field_0c;
Opaque base_field_10;
Opaque base_vtable_00;

const OpaqueVTable8 observed_primary_013f7b90 = {
    {0x00671f50u, 0x00ae06a0u, 0x005c00e0u, 0x005bf920u, 0x00e31100u,
     0x00ad7590u, 0x005c0100u, 0x005c0380u},
    addresses::terminator_00800000};

const OpaqueVTable4 observed_secondary_013f7b80 = {0x005c0050u, 0x005bf9d0u,
                                                   0x0076e5b0u, 0x00b0bd00u};

const OpaqueVTable4 observed_tertiary_013f7b70 = {0x005c0060u, 0x0105d1f0u,
                                                  0x00d1bcb0u, 0x004535b0u};

const OpaqueVTable4 observed_abstract_013ec458 = {0x0055bf80u, 0x005454f0u,
                                                  0x00453540u, 0x004535b0u};

const OpaqueVTable4 observed_name_input_secondary_013f7214 = {
    0x005aca60u, 0x005b8550u, 0x005ac9b0u, 0x004535b0u};

const OpaqueVTable15 observed_name_input_primary_013f7224 = {
    {0x005b2490u, 0x005ba0d0u, 0x005acd60u, 0x005ac9c0u, 0x005aca70u,
     0x005b0fd0u, 0x005acdb0u, 0x005b1010u, 0x005acc30u, 0x005acec0u,
     0x00985e40u, 0x005bdc80u, 0x005acc90u, 0x00950230u, 0x005aa470u},
    addresses::terminator_00800000};

OpaqueVTable8 primary_013f7b90;
OpaqueVTable4 secondary_013f7b80;
OpaqueVTable4 tertiary_013f7b70;

void add(Kind kind, Opaque object, Opaque value) {
  check(event_count < kEventCapacity);
  events[event_count].kind = kind;
  events[event_count].object = object;
  events[event_count].value = value;
  ++event_count;
}

void reset() {
  event_count = 0;
  released_object = 0;
  released_count = 0;
  base_destroy_writes_vtables = true;
  base_field_08 = 0x40000000u;
  base_byte_05 = 1u;
  base_field_0c = 0u;
  base_field_10 = 0u;
  base_vtable_00 = addresses::vtable_013f73e4;
}

Opaque pointer_word(const void *pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

template <typename Function>
Opaque function_word(Function function) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UTFWin function pointer width mismatch");
  Opaque word = 0;
  std::memcpy(&word, &function, sizeof(word));
  return word;
}

template <typename Function>
Function function_from(Opaque word) {
  static_assert(sizeof(Opaque) == sizeof(Function),
                "UTFWin function pointer width mismatch");
  Function function = nullptr;
  std::memcpy(&function, &word, sizeof(function));
  return function;
}

float float_from(Opaque word) {
  float value = 0.0f;
  std::memcpy(&value, &word, sizeof(value));
  return value;
}

Opaque word_from_float(float value) {
  Opaque word = 0;
  std::memcpy(&word, &value, sizeof(word));
  return word;
}

}

extern "C" Opaque cdecl_caller_005c00e0(OpaqueNamePanel *object, Opaque flags,
                                        Opaque *out_result,
                                        Opaque *out_canary) {
  volatile Opaque canary = 0x5a5a5a5au;
  const Opaque observed =
      model::pointer_word(pkg_utfwin_wave11_005c00e0(object, flags));
  *out_result = observed;
  *out_canary = canary;
  return observed;
}

namespace model {

OpaqueNamePanel *PKG_UTFWIN_WAVE11_THISCALL
adjustor_005c0050(OpaqueNamePanel *object, Opaque flags) {
  const Opaque adjusted =
      static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(object)) -
      addresses::adjust_005c0050;
  return pkg_utfwin_wave11_005c00e0(reinterpret_cast<OpaqueNamePanel *>(
                                        static_cast<std::uintptr_t>(adjusted)),
                                    flags);
}

OpaqueNamePanel *PKG_UTFWIN_WAVE11_THISCALL
adjustor_005c0060(OpaqueNamePanel *object, Opaque flags) {
  const Opaque adjusted =
      static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(object)) -
      addresses::adjust_005c0060;
  return pkg_utfwin_wave11_005c00e0(reinterpret_cast<OpaqueNamePanel *>(
                                        static_cast<std::uintptr_t>(adjusted)),
                                    flags);
}

void PKG_UTFWIN_WAVE11_THISCALL
reference_add_00671f50(OpaqueNamePanel *object) {
  object->refcount_0c = object->refcount_0c + 1u;
  add(Kind::reference_add, pointer_word(object), object->refcount_0c);
}

Opaque PKG_UTFWIN_WAVE11_THISCALL
reference_release_00ae06a0(OpaqueNamePanel *object) {
  add(Kind::reference_release, pointer_word(object), object->refcount_0c);
  const Opaque next = object->refcount_0c - 1u;
  object->refcount_0c = next;
  if (next != 0u) {
    return next;
  }
  object->refcount_0c = 1u;
  const auto slot =
      function_from<NameInputPanelDestroySlot>(tertiary_013f7b70.slot_00);
  const Opaque interface_address =
      static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(object)) +
      addresses::adjust_005c0060;
  slot(reinterpret_cast<OpaqueNamePanel *>(
           static_cast<std::uintptr_t>(interface_address)),
       1u);
  return 0u;
}

OpaqueNamePanel *PKG_UTFWIN_WAVE11_THISCALL
destroy_through_primary(OpaqueNamePanel *object, Opaque flags) {
  const auto slot = function_from<NameInputPanelDestroySlot>(
      primary_013f7b90.slots_00[addresses::slot_005c00e0_panel_08]);
  return slot(object, flags);
}

void link_tables() {
  primary_013f7b90 = observed_primary_013f7b90;
  secondary_013f7b80 = observed_secondary_013f7b80;
  tertiary_013f7b70 = observed_tertiary_013f7b70;
  primary_013f7b90.slots_00[0] = function_word(&reference_add_00671f50);
  primary_013f7b90.slots_00[1] = function_word(&reference_release_00ae06a0);
  primary_013f7b90.slots_00[2] = function_word(&pkg_utfwin_wave11_005c00e0);
  secondary_013f7b80.slot_00 = function_word(&adjustor_005c0050);
  tertiary_013f7b70.slot_00 = function_word(&adjustor_005c0060);
}

void seed_panel(OpaqueNamePanel *panel) {
  std::memset(panel, 0, sizeof(*panel));
  panel->vtable_00 = pointer_word(&primary_013f7b90);
  panel->vtable_04 = pointer_word(&secondary_013f7b80);
  panel->vtable_08 = pointer_word(&tertiary_013f7b70);
}

}

namespace unresolved_contracts {

extern "C" void PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_re_005b0f80(OpaqueNameInput *object) {
  model::add(model::Kind::base_construct, model::pointer_word(object), 0);
  object->vtable_00 = model::base_vtable_00;
  object->byte_04 = 0;
  object->byte_05 = static_cast<std::uint8_t>(model::base_byte_05);
  object->byte_06 = 0;
  object->field_08 = model::float_from(model::base_field_08);
  object->field_0c = model::base_field_0c;
  object->field_10 = model::base_field_10;
}

extern "C" void PKG_UTFWIN_WAVE11_THISCALL
pkg_utfwin_wave11_re_005c0070(OpaqueNamePanel *object) {
  model::add(model::Kind::base_destroy, model::pointer_word(object), 0);
  if (!model::base_destroy_writes_vtables) {
    return;
  }
  object->vtable_00 = addresses::vtable_013f7b90;
  object->vtable_04 = addresses::vtable_013f7b80;
  object->vtable_08 = addresses::vtable_013f7b70;
}

extern "C" void pkg_utfwin_wave11_re_00f47380(Opaque *pointer) {
  model::add(model::Kind::release, model::pointer_word(pointer), 0);
  model::released_object = model::pointer_word(pointer);
  model::released_count = model::released_count + 1u;
}

}

namespace model {

void test_name_input_store_image() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto *object = reinterpret_cast<OpaqueNameInput *>(storage);
  std::memset(storage, 0xa5, sizeof(storage));

  std::uint8_t expected[sizeof(OpaqueNameInput)];
  std::memset(expected, 0xa5, sizeof(expected));
  const Opaque vtable_00 = addresses::vtable_013f7224;
  const Opaque vtable_14 = addresses::vtable_013f7214;
  const Opaque base_vtable = addresses::vtable_013f73e4;
  const Opaque base_scalar = 0x40000000u;
  const Opaque scale_scalar = 0x3f800000u;
  std::memset(expected + 0x00, 0x00, 0x07);
  std::memset(expected + 0x08, 0x00, 0x2c);
  std::memset(expected + 0x40, 0x00, 0x0c);
  std::memset(expected + 0x54, 0x00, 0x08);
  std::memcpy(expected + 0x00, &base_vtable, sizeof(base_vtable));
  expected[0x05] = 0x01u;
  std::memcpy(expected + 0x08, &base_scalar, sizeof(base_scalar));
  std::memcpy(expected + 0x14, &vtable_14, sizeof(vtable_14));
  std::memcpy(expected + 0x00, &vtable_00, sizeof(vtable_00));
  std::memcpy(expected + 0x54, &scale_scalar, sizeof(scale_scalar));

  reset();
  OpaqueNameInput *result = pkg_utfwin_wave11_005ac9f0(object);

  check(result == object);
  check(event_count == 1);
  check(events[0].kind == Kind::base_construct);
  check(events[0].object == pointer_word(object));
  check(std::memcmp(storage, expected, sizeof(expected)) == 0);
}

void test_name_input_field_widths() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto *object = reinterpret_cast<OpaqueNameInput *>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  pkg_utfwin_wave11_005ac9f0(object);

  check(sizeof(OpaqueNameInput) == 0x5cu);
  check(word_from_float(object->field_08) == 0x40000000u);
  check(word_from_float(object->field_28) == 0x00000000u);
  check(word_from_float(object->field_2c) == 0x00000000u);
  check(word_from_float(object->field_30) == 0x00000000u);
  check(word_from_float(object->field_40) == 0x00000000u);
  check(word_from_float(object->field_44) == 0x00000000u);
  check(word_from_float(object->field_54) == 0x3f800000u);
  check(word_from_float(object->field_58) == 0x00000000u);
  check(object->vtable_00 == addresses::vtable_013f7224);
  check(object->vtable_14 == addresses::vtable_013f7214);
  check(object->vtable_14 != addresses::vtable_013ec458);
  check(object->byte_04 == 0u);
  check(object->byte_05 == 1u);
  check(object->byte_06 == 0u);
  check(object->field_18 == 0u);
  check(object->field_1c == 0u);
  check(object->field_24 == 0u);
  check(object->field_48 == 0u);
}

void test_name_input_scale_word() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto *object = reinterpret_cast<OpaqueNameInput *>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  pkg_utfwin_wave11_g_word_01485720 = 0x3f800000u;
  pkg_utfwin_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x3f800000u);

  pkg_utfwin_wave11_g_word_01485720 = 0x40490fdbu;
  pkg_utfwin_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x40490fdbu);

  pkg_utfwin_wave11_g_word_01485720 = 0x00000000u;
  pkg_utfwin_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x00000000u);

  pkg_utfwin_wave11_g_word_01485720 = 0x80000000u;
  pkg_utfwin_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x80000000u);

  pkg_utfwin_wave11_g_word_01485720 = 0x3f800000u;
}

void test_name_input_base_overlay() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto *object = reinterpret_cast<OpaqueNameInput *>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  base_field_08 = 0x41200000u;
  base_byte_05 = 0x7fu;
  base_field_0c = 0xdeadbeefu;
  base_field_10 = 0x0badf00du;
  base_vtable_00 = addresses::vtable_013f73e4;
  pkg_utfwin_wave11_005ac9f0(object);

  check(word_from_float(object->field_08) == 0x41200000u);
  check(object->byte_05 == 0x7fu);
  check(object->field_0c == 0xdeadbeefu);
  check(object->field_10 == 0x0badf00du);
  check(object->byte_04 == 0u);
  check(object->byte_06 == 0u);
  check(object->vtable_00 == addresses::vtable_013f7224);
  check(object->vtable_14 == addresses::vtable_013f7214);

  reset();
}

void test_observed_table_shapes() {
  check(sizeof(observed_primary_013f7b90) == 0x24u);
  check(sizeof(observed_secondary_013f7b80) == 0x10u);
  check(sizeof(observed_tertiary_013f7b70) == 0x10u);
  check(sizeof(observed_abstract_013ec458) == 0x10u);
  check(sizeof(observed_name_input_primary_013f7224) == 0x40u);
  check(sizeof(observed_name_input_secondary_013f7214) == 0x10u);
  check(observed_primary_013f7b90.terminator_20 ==
        addresses::terminator_00800000);
  check(observed_name_input_primary_013f7224.terminator_3c ==
        addresses::terminator_00800000);
  check(observed_primary_013f7b90.slots_00[0] == 0x00671f50u);
  check(observed_primary_013f7b90.slots_00[1] == 0x00ae06a0u);
  check(observed_primary_013f7b90.slots_00[2] == 0x005c00e0u);
  check(observed_primary_013f7b90.slots_00[7] == 0x005c0380u);
  check(observed_secondary_013f7b80.slot_00 == 0x005c0050u);
  check(observed_tertiary_013f7b70.slot_00 == 0x005c0060u);
  check(observed_tertiary_013f7b70.slot_0c == 0x004535b0u);
  check(observed_abstract_013ec458.slot_00 == 0x0055bf80u);
  check(observed_abstract_013ec458.slot_0c == 0x004535b0u);
  check(observed_name_input_primary_013f7224.slots_00[0] == 0x005b2490u);
  check(observed_name_input_primary_013f7224.slots_00[14] == 0x005aa470u);
  check(observed_name_input_secondary_013f7214.slot_00 == 0x005aca60u);
  check(observed_name_input_secondary_013f7214.slot_0c == 0x004535b0u);
  check(addresses::slot_005c00e0_panel_08 == 2u);
  check(addresses::slot_005c00e0_panel_04 == 0u);
  check(addresses::slot_005c00e0_panel_08_00 == 0u);
  check(addresses::adjust_005c0050 == 0x04u);
  check(addresses::adjust_005c0060 == 0x08u);
  check(addresses::terminator_00800000 == 0x00800000u);
  check(addresses::scalar_01485720 == 0x01485720u);
}

void test_name_panel_flags_matrix() {
  link_tables();
  const Opaque cases[9] = {0u,     1u,     2u,          3u,         0x40u,
                           0x100u, 0x101u, 0xfffffffeu, 0xffffffffu};
  for (const Opaque flags : cases) {
    OpaqueNamePanel panel;
    seed_panel(&panel);
    panel.refcount_0c = 0x5au;

    reset();
    OpaqueNamePanel *result = pkg_utfwin_wave11_005c00e0(&panel, flags);

    check(result == &panel);
    check(event_count >= 1);
    check(events[0].kind == Kind::base_destroy);
    check(events[0].object == pointer_word(&panel));
    check(panel.vtable_00 == addresses::vtable_013f7b90);
    check(panel.vtable_04 == addresses::vtable_013f7b80);
    check(panel.vtable_08 == addresses::vtable_013f7b70);
    check(panel.refcount_0c == 0x5au);
    check(panel.byte_10 == 0u);
    check(panel.byte_11 == 0u);
    check(panel.buffer_24 == 0u);

    if ((flags & 0x1u) != 0u) {
      check(released_count == 1u);
      check(released_object == pointer_word(&panel));
      check(event_count == 2);
      check(events[1].kind == Kind::release);
      check(events[1].object == pointer_word(&panel));
    } else {
      check(released_count == 0u);
      check(event_count == 1);
    }
  }
}

void test_name_panel_receiver_passthrough() {
  link_tables();
  auto *low = reinterpret_cast<OpaqueNamePanel *>(
      static_cast<std::uintptr_t>(0x00c0ffeeu));
  auto *high = reinterpret_cast<OpaqueNamePanel *>(
      static_cast<std::uintptr_t>(0xf1000000u));

  reset();
  base_destroy_writes_vtables = false;
  OpaqueNamePanel *result = pkg_utfwin_wave11_005c00e0(low, 0u);
  check(result == low);
  check(pointer_word(result) == 0x00c0ffeeu);
  check(event_count == 1);
  check(events[0].kind == Kind::base_destroy);
  check(events[0].object == 0x00c0ffeeu);
  check(released_count == 0u);

  reset();
  base_destroy_writes_vtables = false;
  result = pkg_utfwin_wave11_005c00e0(high, 0x1u);
  check(result == high);
  check(pointer_word(result) == 0xf1000000u);
  check(event_count == 2);
  check(events[0].kind == Kind::base_destroy);
  check(events[0].object == 0xf1000000u);
  check(events[1].kind == Kind::release);
  check(events[1].object == 0xf1000000u);
  check(released_object == 0xf1000000u);
  check(released_count == 1u);
}

void test_name_panel_cdecl_caller_frame() {
  link_tables();
  OpaqueNamePanel panel;
  seed_panel(&panel);

  Opaque result = 0;
  Opaque canary = 0;

  reset();
  Opaque observed = cdecl_caller_005c00e0(&panel, 0x1u, &result, &canary);
  check(observed == pointer_word(&panel));
  check(result == pointer_word(&panel));
  check(canary == 0x5a5a5a5au);
  check(released_count == 1u);
  check(events[0].kind == Kind::base_destroy);
  check(events[1].kind == Kind::release);

  reset();
  observed = cdecl_caller_005c00e0(&panel, 0x0u, &result, &canary);
  check(observed == pointer_word(&panel));
  check(result == pointer_word(&panel));
  check(canary == 0x5a5a5a5au);
  check(released_count == 0u);
  check(event_count == 1);
}

void test_name_panel_return_width() {
  link_tables();
  auto *object = reinterpret_cast<OpaqueNamePanel *>(
      static_cast<std::uintptr_t>(0xdeadbeefu));

  static_assert(sizeof(decltype(pkg_utfwin_wave11_005c00e0(nullptr, 0u))) == 4,
                "UTFWin name panel return width");
  check(function_word(&pkg_utfwin_wave11_005c00e0) != 0u);

  reset();
  base_destroy_writes_vtables = false;
  OpaqueNamePanel *result = pkg_utfwin_wave11_005c00e0(object, 0u);
  check(pointer_word(result) == 0xdeadbeefu);
  check(result == object);
  check(events[0].object == 0xdeadbeefu);

  reset();
  base_destroy_writes_vtables = false;
  result = pkg_utfwin_wave11_005c00e0(object, 0x1u);
  check(pointer_word(result) == 0xdeadbeefu);
  check(released_object == 0xdeadbeefu);
  check(released_count == 1u);
}

void test_name_panel_primary_slot_dispatch() {
  link_tables();
  OpaqueNamePanel panel;
  seed_panel(&panel);
  panel.refcount_0c = 1u;

  const auto slot = function_from<NameInputPanelDestroySlot>(
      primary_013f7b90.slots_00[addresses::slot_005c00e0_panel_08]);

  reset();
  OpaqueNamePanel *result = slot(&panel, 0x0u);
  check(result == &panel);
  check(released_count == 0u);
  check(events[0].kind == Kind::base_destroy);

  reset();
  result = slot(&panel, 0x1u);
  check(result == &panel);
  check(released_count == 1u);
  check(released_object == pointer_word(&panel));

  reset();
  check(destroy_through_primary(&panel, 0x1u) == &panel);
  check(released_count == 1u);
  check(released_object == pointer_word(&panel));
}

void test_name_panel_adjustor_dispatch() {
  link_tables();
  std::uint8_t storage[sizeof(OpaqueNamePanel) * 4];
  std::memset(storage, 0, sizeof(storage));
  auto *object = reinterpret_cast<OpaqueNamePanel *>(storage);

  const auto slot_04 =
      function_from<NameInputPanelDestroySlot>(secondary_013f7b80.slot_00);
  const auto slot_08 =
      function_from<NameInputPanelDestroySlot>(tertiary_013f7b70.slot_00);

  auto *interface_04 = reinterpret_cast<OpaqueNamePanel *>(
      reinterpret_cast<std::uintptr_t>(object) + addresses::adjust_005c0050);
  auto *interface_08 = reinterpret_cast<OpaqueNamePanel *>(
      reinterpret_cast<std::uintptr_t>(object) + addresses::adjust_005c0060);

  reset();
  slot_04(interface_04, 0x0u);
  check(events[0].object == pointer_word(object));
  check(released_count == 0u);

  reset();
  slot_04(interface_04, 0x1u);
  check(events[0].object == pointer_word(object));
  check(released_object == pointer_word(object));
  check(released_count == 1u);

  reset();
  slot_08(interface_08, 0x1u);
  check(events[0].object == pointer_word(object));
  check(released_object == pointer_word(object));
  check(released_count == 1u);
}

void test_name_panel_reference_route() {
  link_tables();
  OpaqueNamePanel panel;
  seed_panel(&panel);
  panel.refcount_0c = 0u;

  check(sizeof(NameInputPanelRefAddSlot) == 4);
  check(sizeof(NameInputPanelRefReleaseSlot) == 4);
  check(sizeof(NameInputPanelDestroySlot) == 4);

  const auto add_slot =
      function_from<NameInputPanelRefAddSlot>(primary_013f7b90.slots_00[0]);
  const auto release_slot =
      function_from<NameInputPanelRefReleaseSlot>(primary_013f7b90.slots_00[1]);

  reset();
  add_slot(&panel);
  add_slot(&panel);
  check(panel.refcount_0c == 2u);
  check(released_count == 0u);
  check(event_count == 2);

  reset();
  Opaque remaining = release_slot(&panel);
  check(remaining == 1u);
  check(panel.refcount_0c == 1u);
  check(released_count == 0u);
  check(event_count == 1);
  check(events[0].kind == Kind::reference_release);

  reset();
  remaining = release_slot(&panel);
  check(remaining == 0u);
  check(panel.refcount_0c == 1u);
  check(event_count == 3);
  check(events[0].kind == Kind::reference_release);
  check(events[1].kind == Kind::base_destroy);
  check(events[1].object == pointer_word(&panel));
  check(events[2].kind == Kind::release);
  check(events[2].object == pointer_word(&panel));
  check(released_count == 1u);
}

int run_tests() {
  test_name_input_store_image();
  test_name_input_field_widths();
  test_name_input_scale_word();
  test_name_input_base_overlay();
  test_observed_table_shapes();
  test_name_panel_flags_matrix();
  test_name_panel_receiver_passthrough();
  test_name_panel_cdecl_caller_frame();
  test_name_panel_return_width();
  test_name_panel_primary_slot_dispatch();
  test_name_panel_adjustor_dispatch();
  test_name_panel_reference_route();
  return 0;
}

}

}

int main() {
  return openspore::reconstruction::pkg_utfwin_wave11::model::run_tests();
}
