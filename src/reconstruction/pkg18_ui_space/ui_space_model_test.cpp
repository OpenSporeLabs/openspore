#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

#include "ui_space.hpp"

namespace openspore::reconstruction::pkg18_ui_space {
namespace {

using Opaque = openspore::reconstruction::pkg18_ui_space::Opaque;
using Object = openspore::reconstruction::pkg18_ui_space::SpaceUiObject;
using Vtable = openspore::reconstruction::pkg18_ui_space::SpaceUiVtable;
using State = openspore::reconstruction::pkg18_ui_space::SpaceUiState;
using Owner = openspore::reconstruction::pkg18_ui_space::TextZoomOwner;

std::vector<const char*> events;
std::array<Object, 96> objects{};
std::array<unsigned char, 0x560> factory_root{};
std::array<unsigned char, 0x230> mode_state_data{};
std::array<unsigned char, 0x20> mode_list{};
std::array<Opaque, 1> mode_entries{};
std::array<unsigned char, 0x10> service_value{};
Vtable vtable{};
Vtable argument_vtable{};
std::size_t object_index = 0;
Opaque next_allocation = 0x1000;
const Opaque* probed_key = nullptr;
Object* recovered_target = nullptr;
bool recover_null_target = false;
Opaque slot_d8_receiver = 0;
Opaque resource_apply_target = 0;
std::vector<Opaque> slot104_arguments;
Opaque resource_receiver = 0;
Opaque resource_id = 0;
Opaque global_constructor_receiver = 0;
Opaque app_system_object = 0;
unsigned app_system_lookups = 0;
Opaque app_system_receiver = 0;
std::vector<Opaque> app_system_arguments;
Opaque posse_init_result = 0;
Opaque posse_54b0_receiver = 0;
Opaque posse_55c0_receiver = 0;
Opaque posse_5240_receiver = 0;
Opaque mode_state = 0;
Opaque mode_context = 0;
Opaque mode_resource = 0;
Opaque mode_93_receiver = 0;
Opaque mode_owner = 0;
Opaque mode_list_receiver = 0;
std::vector<Opaque> mode_list_arguments;
Opaque mode_list_candidate = 0;
bool mode_list_enabled = false;
std::uint8_t simulator_enabled = 0;

void log(const char* event) { events.push_back(event); }

bool is_event(const char* actual, const char* expected) {
  return std::strcmp(actual, expected) == 0;
}

bool has_event(const char* expected) {
  for (const char* event : events) {
    if (is_event(event, expected)) {
      return true;
    }
  }
  return false;
}

Opaque load_opaque(const void* base, std::size_t offset) {
  Opaque value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

void store_opaque(void* base, std::size_t offset, Opaque value) {
  std::memcpy(static_cast<unsigned char*>(base) + offset, &value,
              sizeof(value));
}

Opaque slot_result(Object* object) {
  return load_opaque(object->opaque.data(), 4);
}

Opaque PKG18_THISCALL slot_acquire(Object* object) {
  log("acquire");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_release(Object* object) {
  log("release");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_release_with_argument(Object* object, Opaque) {
  log("release");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_owner(Object* object) {
  log("owner");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_value30(Object* object) {
  log("value30");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_value38(Object* object) {
  log("value38");
  return slot_result(object);
}

Opaque PKG18_THISCALL slot_value7c(Object*, Opaque first, Opaque second) {
  events.push_back(first == 1 && second == 0 ? "slot7c-1-0" : "slot7c-16-1");
  return 0;
}

Opaque PKG18_THISCALL slot_d8(Object* object, Opaque) {
  slot_d8_receiver = reinterpret_cast<Opaque>(object);
  log("slotd8");
  return 0;
}

Opaque PKG18_THISCALL slot_104(Object*, Opaque first) {
  slot104_arguments.push_back(first);
  log("slot104");
  return 0;
}

Opaque PKG18_THISCALL slot_108(Object*, Opaque) {
  log("slot108");
  return 0;
}

Opaque PKG18_THISCALL slot_80(Object*, Opaque, Opaque) {
  log("slot80");
  return posse_init_result;
}

Opaque PKG18_THISCALL slot_one(Object*, Opaque) {
  log("slot-one");
  return 0;
}

Opaque PKG18_THISCALL slot_two(Object* object, Opaque first, Opaque second) {
  app_system_receiver = reinterpret_cast<Opaque>(object);
  app_system_arguments.push_back(first);
  app_system_arguments.push_back(second);
  log("slot-two");
  return 0;
}

Opaque PKG18_THISCALL slot_four(Object*, Opaque, Opaque, Opaque, Opaque) {
  log("slot-four");
  return 0;
}

void initialize_vtable() {
  vtable.slots[0] = reinterpret_cast<Opaque>(slot_acquire);
  vtable.slots[1] = reinterpret_cast<Opaque>(slot_release);
  vtable.slots[2] = reinterpret_cast<Opaque>(slot_release);
  vtable.slots[4] = reinterpret_cast<Opaque>(slot_owner);
  vtable.slots[0x0c / 4] = reinterpret_cast<Opaque>(slot_one);
  vtable.slots[0x14 / 4] = reinterpret_cast<Opaque>(slot_one);
  vtable.slots[0x24 / 4] = reinterpret_cast<Opaque>(slot_two);
  vtable.slots[0x30 / 4] = reinterpret_cast<Opaque>(slot_value30);
  vtable.slots[0x38 / 4] = reinterpret_cast<Opaque>(slot_value38);
  vtable.slots[0x7c / 4] = reinterpret_cast<Opaque>(slot_value7c);
  vtable.slots[0x80 / 4] = reinterpret_cast<Opaque>(slot_80);
  vtable.slots[0x90 / 4] = reinterpret_cast<Opaque>(slot_four);
  vtable.slots[0xb8 / 4] = reinterpret_cast<Opaque>(slot_one);
  vtable.slots[0xc0 / 4] = reinterpret_cast<Opaque>(slot_one);
  vtable.slots[0xd8 / 4] = reinterpret_cast<Opaque>(slot_d8);
  vtable.slots[0x104 / 4] = reinterpret_cast<Opaque>(slot_104);
  vtable.slots[0x108 / 4] = reinterpret_cast<Opaque>(slot_108);
  argument_vtable = vtable;
  argument_vtable.slots[2] =
      reinterpret_cast<Opaque>(slot_release_with_argument);
}

Object* new_object(Opaque result = 0) {
  assert(object_index < objects.size());
  Object* object = &objects[object_index++];
  object->vtable = &vtable;
  object->refcount = 1;
  store_opaque(object->opaque.data(), 0, object_index);
  store_opaque(object->opaque.data(), 4, result);
  return object;
}

Object* factory_child() {
  Object* child = reinterpret_cast<Object*>(factory_root.data() + 0x20c);
  child->vtable = &vtable;
  child->refcount = 1;
  store_opaque(child->opaque.data(), 0, 0xffffffffu);
  store_opaque(child->opaque.data(), 4, 0);
  return child;
}

void reset_objects() {
  object_index = 0;
  events.clear();
  probed_key = nullptr;
  recovered_target = nullptr;
  recover_null_target = false;
  slot_d8_receiver = 0;
  resource_apply_target = 0;
  slot104_arguments.clear();
  resource_receiver = 0;
  resource_id = 0;
  global_constructor_receiver = 0;
  app_system_object = 0;
  app_system_lookups = 0;
  app_system_receiver = 0;
  app_system_arguments.clear();
  posse_init_result = 0;
  posse_54b0_receiver = 0;
  posse_55c0_receiver = 0;
  posse_5240_receiver = 0;
  mode_state = 0;
  mode_context = 0;
  mode_resource = 0;
  mode_93_receiver = 0;
  mode_owner = 0;
  mode_list_receiver = 0;
  mode_list_arguments.clear();
  mode_list_candidate = 0;
  mode_list_enabled = false;
  simulator_enabled = 0;
  std::memset(objects.data(), 0, sizeof(objects));
  std::memset(factory_root.data(), 0, sizeof(factory_root));
  std::memset(mode_state_data.data(), 0, sizeof(mode_state_data));
  std::memset(mode_list.data(), 0, sizeof(mode_list));
  std::memset(mode_entries.data(), 0, sizeof(mode_entries));
  std::memset(service_value.data(), 0, sizeof(service_value));
  initialize_vtable();
}
}

}

using namespace openspore::reconstruction::pkg18_ui_space;

extern "C" std::uint8_t pkg18_re_004eb930(
    const openspore::reconstruction::pkg18_ui_space::Opaque*,
    const openspore::reconstruction::pkg18_ui_space::Opaque* requested_key) {
  probed_key = requested_key;
  log("resource-probe");
  return 1;
}

extern "C" void __thiscall pkg18_re_00834e30(
    openspore::reconstruction::pkg18_ui_space::TextZoomOwner*) {
  log("zoom-prepare");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_009512c0() {
  log("factory-context");
  return 0x7000;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque pkg18_re_009512d0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("factory-create");
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      factory_root.data());
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00989000(openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("factory-object");
  Object* child = factory_child();
  store_opaque(child->opaque.data(), 4, reinterpret_cast<Opaque>(new_object()));
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      factory_root.data());
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque pkg18_re_0080fee0(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  return 0x7100;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00810620(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return 0x7200;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00b5f950(
    openspore::reconstruction::pkg18_ui_space::Opaque target_field,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  if (recover_null_target) {
    auto* owner = reinterpret_cast<
        openspore::reconstruction::pkg18_ui_space::TextZoomOwner*>(
        target_field - 0x6c);
    store_opaque(
        owner->bytes.data(), 0x6c,
        reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
            recovered_target));
  }
  log("null-target-recovery");
  return 0;
}

extern "C" std::uint8_t __thiscall pkg18_re_008120d0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("resource-register");
  return 1;
}

extern "C" void __thiscall pkg18_re_008121b0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque target,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  resource_apply_target = target;
  log("resource-apply");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_008105b0(openspore::reconstruction::pkg18_ui_space::Opaque receiver,
                  openspore::reconstruction::pkg18_ui_space::Opaque id,
                  openspore::reconstruction::pkg18_ui_space::Opaque) {
  resource_receiver = receiver;
  resource_id = id;
  log("resource-object");
  Object* object = new_object();
  if (id == 0x07cf8048u) {
    store_opaque(
        object->opaque.data(), 4,
        reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
            service_value.data()));
  }
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      object);
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque pkg18_re_00f473a0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  next_allocation += 0x10;
  return next_allocation;
}

extern "C" void pkg18_re_00806320(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::SpaceUiObject** output,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  *output = nullptr;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e03ab0(openspore::reconstruction::pkg18_ui_space::Opaque) {
  Object* object = new_object();
  object->vtable = &argument_vtable;
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      object);
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_01066880(
    openspore::reconstruction::pkg18_ui_space::Opaque allocation) {
  global_constructor_receiver = allocation;
  Object* object = new_object();
  object->vtable = &argument_vtable;
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      object);
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00810000(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" void __thiscall pkg18_re_00812160(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("resource-tooltip");
}

extern "C" void __thiscall pkg18_re_00810590(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("tooltip-state");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e2c920(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e36480(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" void __thiscall pkg18_re_00e36b30(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("timed-tooltip-setup");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque pkg18_re_00e012b0(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e0fc90(openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" void __thiscall pkg18_re_00e0c1f0(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("minimap-colors");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_0093b6c0(openspore::reconstruction::pkg18_ui_space::Opaque receiver) {
  mode_93_receiver = receiver;
  return mode_resource;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e28a10(openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque,
                  openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" void __thiscall pkg18_re_00e29c80(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("space-ui-setup");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_00b3d230() {
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_0067dcc0() {
  ++app_system_lookups;
  if (app_system_lookups == 1) {
    return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
        new_object());
  }
  return app_system_object;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_0083c800(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_0067de20() {
  return 0;
}

extern "C" void __thiscall pkg18_re_01068f70(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-01068f70");
}

extern "C" void __thiscall pkg18_re_01070290(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-01070290");
}

extern "C" void __thiscall pkg18_re_01071a00(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-01071a00");
}

extern "C" void __thiscall pkg18_re_0106a280(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-0106a280");
}

extern "C" void __thiscall pkg18_re_010666b0(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-010666b0");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_01046fc0(openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  return 0;
}

extern "C" void __thiscall pkg18_re_01048ce0(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("init-01048ce0");
}

extern "C" void __thiscall pkg18_re_0106a4e0(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("init-0106a4e0");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_01021300() {
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00c326b0(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_01002bd0() {
  return mode_state;
}

extern "C" void pkg18_re_00807bb0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("posse-resource");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e25710(openspore::reconstruction::pkg18_ui_space::Opaque) {
  Object* object = new_object();
  if (posse_init_result != 0) {
    store_opaque(object->opaque.data(), 0x9c, 0);
    store_opaque(object->opaque.data(), 0xa0, 8);
  }
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      object);
}

extern "C" void __thiscall pkg18_re_006b5060(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("posse-layout");
}

extern "C" void __thiscall pkg18_re_006b54b0(
    openspore::reconstruction::pkg18_ui_space::Opaque receiver,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  posse_54b0_receiver = receiver;
  log("posse-ids");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_006b55c0(openspore::reconstruction::pkg18_ui_space::Opaque receiver) {
  posse_55c0_receiver = receiver;
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_00b3d300() {
  return mode_owner;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00b21340(openspore::reconstruction::pkg18_ui_space::Opaque receiver,
                  openspore::reconstruction::pkg18_ui_space::Opaque first,
                  openspore::reconstruction::pkg18_ui_space::Opaque second,
                  openspore::reconstruction::pkg18_ui_space::Opaque third,
                  openspore::reconstruction::pkg18_ui_space::Opaque fourth,
                  openspore::reconstruction::pkg18_ui_space::Opaque fifth) {
  mode_list_receiver = receiver;
  mode_list_arguments = {first, second, third, fourth, fifth};
  if (!mode_list_enabled) {
    return 0;
  }
  store_opaque(mode_list.data(), 4, reinterpret_cast<Opaque>(&mode_entries[0]));
  store_opaque(mode_list.data(), 8,
               reinterpret_cast<Opaque>(&mode_entries[0] + 1));
  store_opaque(mode_entries.data(), 0, mode_list_candidate);
  return reinterpret_cast<Opaque>(mode_list.data());
}

extern "C" void __thiscall pkg18_re_0106b500(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("mode3");
}

extern "C" void __thiscall pkg18_re_01072680(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("modes");
}

extern "C" void __thiscall pkg18_re_006b5240(
    openspore::reconstruction::pkg18_ui_space::Opaque receiver) {
  posse_5240_receiver = receiver;
  log("posse-finish");
}

extern "C" void pkg18_re_00806de0(
    openspore::reconstruction::pkg18_ui_space::Opaque,
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("late-resource");
}

extern "C" void __thiscall pkg18_re_0106e020(
    openspore::reconstruction::pkg18_ui_space::SpaceUiState*) {
  log("ui-state");
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00e31050(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" void __thiscall pkg18_re_00e2f370(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  log("flash-setup");
}

extern "C" std::uint8_t pkg18_re_00685520(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  return simulator_enabled;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque __thiscall
pkg18_re_00fe75d0(openspore::reconstruction::pkg18_ui_space::Opaque) {
  return reinterpret_cast<openspore::reconstruction::pkg18_ui_space::Opaque>(
      new_object());
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_table_word_0149c158(
    openspore::reconstruction::pkg18_ui_space::Opaque) {
  return 0;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
pkg18_re_table_word_0149c418(
    openspore::reconstruction::pkg18_ui_space::Opaque offset) {
  return offset + 0x2000u;
}

extern "C" openspore::reconstruction::pkg18_ui_space::Opaque
    pkg18_re_global_016e2234 = 0;

namespace {

using namespace openspore::reconstruction::pkg18_ui_space;

void store_state(State& state, std::size_t offset, Opaque value) {
  std::memcpy(state.bytes.data() + offset, &value, sizeof(value));
}

Opaque load_state(const State& state, std::size_t offset) {
  Opaque value = 0;
  std::memcpy(&value, state.bytes.data() + offset, sizeof(value));
  return value;
}

void test_text_zoom_rebinding() {
  reset_objects();
  Owner owner{};
  Object* source = new_object();
  Object* parent = new_object();
  Object* selected = new_object(5);
  store_opaque(source->opaque.data(), 4, reinterpret_cast<Opaque>(parent));
  store_opaque(parent->opaque.data(), 4, reinterpret_cast<Opaque>(selected));
  Object* target = new_object();
  Object* old_target = new_object();
  Object* mode = new_object();
  store_opaque(owner.bytes.data(), 0x68, reinterpret_cast<Opaque>(source));
  store_opaque(owner.bytes.data(), 0x6c, reinterpret_cast<Opaque>(old_target));
  events.clear();

  const bool result = pkg18_text_zoom_rebind_00834fa0(
      &owner, source, target, reinterpret_cast<Opaque>(mode), 0x1234u, 1u, 2u,
      3u);

  assert(result);
  assert(events.size() > 4);
  assert(is_event(events[0], "owner"));
  assert(is_event(events[1], "owner"));
  assert(is_event(events[2], "value30"));
  assert(is_event(events[3], "resource-probe"));
  assert(is_event(events[4], "zoom-prepare"));
  assert(load_opaque(owner.bytes.data(), 0x54) == 0x1234u);
  assert(resource_receiver ==
         reinterpret_cast<Opaque>(owner.bytes.data() + 0x30));
  assert(resource_id == 0x0626e3b8u);
}

void test_text_zoom_probe_noop() {
  reset_objects();
  Owner owner{};
  Object* source = new_object();
  Object* parent = new_object();
  Object* selected = new_object(5);
  Object* target = new_object();
  store_opaque(source->opaque.data(), 4, reinterpret_cast<Opaque>(parent));
  store_opaque(parent->opaque.data(), 4, reinterpret_cast<Opaque>(selected));
  store_opaque(owner.bytes.data(), 0x68, reinterpret_cast<Opaque>(source));
  store_opaque(owner.bytes.data(), 0x6c, reinterpret_cast<Opaque>(target));
  events.clear();

  assert(pkg18_text_zoom_rebind_00834fa0(&owner, source, target, 0, 0, 1u, 2u,
                                         3u));
  assert(events.size() == 4);
  assert(is_event(events[3], "resource-probe"));
  assert(probed_key != nullptr);
  assert(probed_key[0] == 1);
}

void test_text_zoom_replacement_order() {
  reset_objects();
  Owner owner{};
  Object* source = new_object();
  Object* parent = new_object();
  Object* selected = new_object(5);
  store_opaque(source->opaque.data(), 4, reinterpret_cast<Opaque>(parent));
  store_opaque(parent->opaque.data(), 4, reinterpret_cast<Opaque>(selected));
  Object* old_source = new_object();
  Object* old_zoom = new_object();
  Object* old_target = new_object();
  Object* target = new_object();
  Object* mode = new_object();
  store_opaque(owner.bytes.data(), 0x68, reinterpret_cast<Opaque>(old_source));
  store_opaque(owner.bytes.data(), 0x64, reinterpret_cast<Opaque>(old_zoom));
  store_opaque(owner.bytes.data(), 0x6c, reinterpret_cast<Opaque>(old_target));
  events.clear();

  assert(pkg18_text_zoom_rebind_00834fa0(
      &owner, source, target, reinterpret_cast<Opaque>(mode), 7u, 0x0164f240u,
      0x0164f244u, 0x0164f248u));
  std::size_t replacement_pairs = 0;
  for (std::size_t index = 0; index + 1 < events.size(); ++index) {
    if (is_event(events[index], "acquire") &&
        is_event(events[index + 1], "release")) {
      ++replacement_pairs;
    }
  }
  assert(replacement_pairs == 3);
}

void test_text_zoom_null_target_recovery() {
  reset_objects();
  Owner owner{};
  Object* source = new_object();
  Object* parent = new_object();
  Object* selected = new_object(5);
  store_opaque(source->opaque.data(), 4, reinterpret_cast<Opaque>(parent));
  store_opaque(parent->opaque.data(), 4, reinterpret_cast<Opaque>(selected));
  Object* old_target = new_object();
  Object* mode = new_object();
  recovered_target = new_object();
  recover_null_target = true;
  store_opaque(owner.bytes.data(), 0x6c, reinterpret_cast<Opaque>(old_target));

  assert(pkg18_text_zoom_rebind_00834fa0(&owner, source, nullptr,
                                         reinterpret_cast<Opaque>(mode),
                                         0x1234u, 1u, 2u, 3u));
  assert(load_opaque(owner.bytes.data(), 0x6c) ==
         reinterpret_cast<Opaque>(recovered_target));
  assert(slot_d8_receiver == reinterpret_cast<Opaque>(recovered_target));
  assert(resource_apply_target == reinterpret_cast<Opaque>(recovered_target));
}

void test_space_ui_teardown() {
  reset_objects();
  State state{};
  Object* old_694 = new_object();
  Object* old_258 = new_object();
  store_state(state, 0x694, reinterpret_cast<Opaque>(old_694));
  store_state(state, 0x258, reinterpret_cast<Opaque>(old_258));
  events.clear();

  pkg18_space_ui_initialize_01073700(&state);

  assert(load_state(state, 0x2f8) == static_cast<Opaque>(-1));
  assert(state.bytes[0x5d5] == 1);
  assert(load_state(state, 0x694) == 0);
  assert(load_state(state, 0x258) == 0);
  assert(slot104_arguments.empty());
  assert(events.size() >= 2);
  assert(is_event(events[events.size() - 2], "release"));
  assert(is_event(events[events.size() - 1], "release"));
}

void test_space_ui_simulator_branch() {
  reset_objects();
  State state{};
  simulator_enabled = 1;

  pkg18_space_ui_initialize_01073700(&state);

  const Opaque simulator_ui = load_state(state, 0x694);
  const Opaque simulator_state = load_state(state, 0x258);
  assert(simulator_ui != 0);
  assert(simulator_state != 0);
  assert(slot104_arguments.size() == 9);
  for (Opaque argument : slot104_arguments) {
    assert(argument == simulator_ui);
  }
}

void test_space_ui_app_system_order() {
  reset_objects();
  State state{};
  const Opaque context = 0xc0deu;
  store_state(state, 0x0c, context);
  Object* app_system = new_object();
  app_system->vtable = &argument_vtable;
  app_system_object = reinterpret_cast<Opaque>(app_system);

  pkg18_space_ui_initialize_01073700(&state);

  assert(app_system_lookups == 2);
  assert(app_system_receiver == reinterpret_cast<Opaque>(app_system));
  assert(app_system_arguments.size() == 50);
  for (std::size_t index = 0; index < 25; ++index) {
    assert(app_system_arguments[index * 2] == index * 4 + 0x2000u);
    assert(app_system_arguments[index * 2 + 1] == context);
  }
}

void test_space_ui_global_constructor() {
  reset_objects();
  State state{};
  pkg18_re_global_016e2234 = 0;

  pkg18_space_ui_initialize_01073700(&state);

  assert(global_constructor_receiver != 0);
  assert(pkg18_re_global_016e2234 != 0);
}

void test_space_ui_mode_receiver() {
  reset_objects();
  State state{};
  mode_state = reinterpret_cast<Opaque>(mode_state_data.data());
  mode_context = 0x9000u;
  mode_resource = 0x9100u;
  store_opaque(mode_state_data.data(), 0x14, mode_context);

  pkg18_space_ui_initialize_01073700(&state);

  assert(mode_93_receiver == mode_context + 0x224u);
  assert(resource_receiver == mode_resource);
  assert(resource_id == 0xb0b00000u);
}

void test_space_ui_posse_success() {
  reset_objects();
  State state{};
  posse_init_result = 1;
  mode_owner = 0xb300u;
  mode_list_candidate = reinterpret_cast<Opaque>(new_object());
  store_opaque(reinterpret_cast<Object*>(mode_list_candidate)->opaque.data(),
               0x70c, 3u);
  mode_list_enabled = true;

  pkg18_space_ui_initialize_01073700(&state);

  assert(load_state(state, 0x5c4) != 0);
  assert(posse_54b0_receiver == posse_55c0_receiver + 0x0cu);
  assert(posse_55c0_receiver == posse_5240_receiver);
  assert(posse_55c0_receiver != 0);
  assert(mode_list_receiver == mode_owner);
  assert(mode_list_arguments ==
         std::vector<Opaque>({0x00cd7d10u, 0x00d3d420u, 0x00ad48b0u,
                              0x00b1e500u, 0x018ebadcu}));
  assert(has_event("mode3"));
}

}

int main() {
  test_text_zoom_rebinding();
  test_text_zoom_probe_noop();
  test_text_zoom_replacement_order();
  test_text_zoom_null_target_recovery();
  test_space_ui_teardown();
  test_space_ui_simulator_branch();
  test_space_ui_app_system_order();
  test_space_ui_global_constructor();
  test_space_ui_mode_receiver();
  test_space_ui_posse_success();
}
