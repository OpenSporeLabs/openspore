#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "utfwin_safe_wave11.hpp"

#if defined(_MSC_VER)
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __thiscall
#else
#define PKG_UTFWIN_SAFE_WAVE11_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_utfwin_safe_wave11 {
namespace model {

enum class Kind : std::uint8_t {
  base_construct,
};

struct Event {
  Kind kind;
  Opaque object;
  Opaque value;
};

constexpr std::size_t kEventCapacity = 8;

void check(bool condition) {
  if (!condition) {
    std::abort();
  }
}

Event events[kEventCapacity];
std::size_t event_count;

Opaque base_field_08;
Opaque base_byte_05;
Opaque base_field_0c;
Opaque base_field_10;
Opaque base_vtable_00;

const OpaqueVTable4 observed_abstract_013ec458 = {0x0055bf80u, 0x005454f0u,
                                                  0x00453540u, 0x004535b0u};

const OpaqueVTable4 observed_name_input_secondary_013f7214 = {
    0x005aca60u, 0x005b8550u, 0x005ac9b0u, 0x004535b0u};

const OpaqueVTable15 observed_name_input_primary_013f7224 = {
    {0x005b2490u, 0x005ba0d0u, 0x005acd60u, 0x005ac9c0u, 0x005aca70u,
     0x005b0fd0u, 0x005acdb0u, 0x005b1010u, 0x005acc30u, 0x005acec0u,
     0x00985e40u, 0x005bdc80u, 0x005acc90u, 0x00950230u, 0x005aa470u},
    addresses::terminator_00800000};

void add(Kind kind, Opaque object, Opaque value) {
  check(event_count < kEventCapacity);
  events[event_count].kind = kind;
  events[event_count].object = object;
  events[event_count].value = value;
  ++event_count;
}

void reset() {
  event_count = 0;
  base_field_08 = 0x40000000u;
  base_byte_05 = 1u;
  base_field_0c = 0u;
  base_field_10 = 0u;
  base_vtable_00 = addresses::vtable_013f73e4;
}

Opaque pointer_word(const void* pointer) {
  return static_cast<Opaque>(reinterpret_cast<std::uintptr_t>(pointer));
}

float float_from(Opaque word) {
  float value = 0.0f;
  std::memcpy(&value, &word, sizeof(word));
  return value;
}

Opaque word_from_float(float value) {
  Opaque word = 0;
  std::memcpy(&word, &value, sizeof(word));
  return word;
}

}  // namespace model

extern "C" void PKG_UTFWIN_SAFE_WAVE11_THISCALL
utfwin_safe_wave11_base_construct_005b0f80(OpaqueNameInput* object) {
  model::add(model::Kind::base_construct, model::pointer_word(object), 0);
  object->vtable_00 = model::base_vtable_00;
  object->byte_04 = 0;
  object->byte_05 = static_cast<std::uint8_t>(model::base_byte_05);
  object->byte_06 = 0;
  object->field_08 = model::float_from(model::base_field_08);
  object->field_0c = model::base_field_0c;
  object->field_10 = model::base_field_10;
}

namespace model {

void test_name_input_store_image() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto* object = reinterpret_cast<OpaqueNameInput*>(storage);
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
  OpaqueNameInput* result = utfwin_safe_wave11_005ac9f0(object);

  check(result == object);
  check(event_count == 1);
  check(events[0].kind == Kind::base_construct);
  check(events[0].object == pointer_word(object));
  check(std::memcmp(storage, expected, sizeof(expected)) == 0);
}

void test_name_input_field_widths() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto* object = reinterpret_cast<OpaqueNameInput*>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  utfwin_safe_wave11_005ac9f0(object);

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
  auto* object = reinterpret_cast<OpaqueNameInput*>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  utfwin_safe_wave11_scale_01485720 = 0x3f800000u;
  utfwin_safe_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x3f800000u);

  utfwin_safe_wave11_scale_01485720 = 0x40490fdbu;
  utfwin_safe_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x40490fdbu);

  utfwin_safe_wave11_scale_01485720 = 0x00000000u;
  utfwin_safe_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x00000000u);

  utfwin_safe_wave11_scale_01485720 = 0x80000000u;
  utfwin_safe_wave11_005ac9f0(object);
  check(word_from_float(object->field_54) == 0x80000000u);

  utfwin_safe_wave11_scale_01485720 = 0x3f800000u;
}

void test_name_input_base_overlay() {
  std::uint8_t storage[sizeof(OpaqueNameInput)];
  auto* object = reinterpret_cast<OpaqueNameInput*>(storage);
  std::memset(storage, 0, sizeof(storage));

  reset();
  base_field_08 = 0x41200000u;
  base_byte_05 = 0x7fu;
  base_field_0c = 0xdeadbeefu;
  base_field_10 = 0x0badf00du;
  base_vtable_00 = addresses::vtable_013f73e4;
  utfwin_safe_wave11_005ac9f0(object);

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
  check(sizeof(observed_abstract_013ec458) == 0x10u);
  check(sizeof(observed_name_input_primary_013f7224) == 0x40u);
  check(sizeof(observed_name_input_secondary_013f7214) == 0x10u);
  check(observed_name_input_primary_013f7224.terminator_3c ==
        addresses::terminator_00800000);
  check(observed_name_input_primary_013f7224.slots_00[0] == 0x005b2490u);
  check(observed_name_input_primary_013f7224.slots_00[14] == 0x005aa470u);
  check(observed_name_input_secondary_013f7214.slot_00 == 0x005aca60u);
  check(observed_name_input_secondary_013f7214.slot_0c == 0x004535b0u);
  check(observed_abstract_013ec458.slot_00 == 0x0055bf80u);
  check(observed_abstract_013ec458.slot_0c == 0x004535b0u);
  check(addresses::terminator_00800000 == 0x00800000u);
  check(addresses::scalar_01485720 == 0x01485720u);
}

int run_tests() {
  test_name_input_store_image();
  test_name_input_field_widths();
  test_name_input_scale_word();
  test_name_input_base_overlay();
  test_observed_table_shapes();
  return 0;
}

}  // namespace model

}  // namespace openspore::reconstruction::pkg_utfwin_safe_wave11

int main() {
  return openspore::reconstruction::pkg_utfwin_safe_wave11::model::run_tests();
}
