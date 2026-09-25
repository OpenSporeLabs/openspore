#include "app_services.hpp"
#include "camera_services.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#endif

namespace {

using namespace openspore::reconstruction::pkg_app_services_wave6;

std::vector<std::string> trace;
OpaqueMessageService* message_service = nullptr;
OpaqueCheatService* cheat_service = nullptr;
OpaqueCheatNode* cheat_sentinel = nullptr;
OpaqueCheatNode* cheat_first = nullptr;
OpaqueCheatNode* cheat_second = nullptr;
OpaqueMouseCameraBase* mouse_base = nullptr;
OpaqueObserver* observed_first = nullptr;
OpaqueObserver* observed_second = nullptr;
OpaqueWord observed_argument = 0;
int observer_enable_count = 0;
int observer_disable_count = 0;
OpaqueObserverVTable observer_vtable{};
OpaqueObjectVTable object_vtable{};
ContinuationVTable continuation_vtable{};
OpaqueCommandCollectionVTable command_collection_vtable{};
OpaqueCommandSecondaryVTable command_secondary_vtable{};
OpaqueCommandCameraVTable command_camera_vtable{};
OpaquePropertyListVTable property_list_vtable{};
OpaqueRendererVTable renderer_vtable{};
OpaqueCameraManagerVTable camera_manager_vtable{};
OpaqueMessageServicePorts message_ports{};
OpaqueCheatServicePorts cheat_ports{};
MouseCameraServicePorts mouse_ports{};
CameraCommandPorts command_ports{};
int parse_mode_result = 0;
bool current_log_result = false;
OpaqueWord parse_default_status = 1;
const char* candidate_value = nullptr;
const char** candidate_result = nullptr;
OpaqueWide* widened_value = nullptr;
bool free_result = true;
int renderer_layer_calls = 0;
OpaqueViewer* renderer_layer_result = nullptr;
bool end_update_result = false;
OpaqueWord resolved_digit = 0;
OpaqueViewer* resolved_viewer = nullptr;
OpaqueWord target_value = 0;
OpaqueWord render_type_value = 0;
const char** target_result = nullptr;
const char** render_type_result = nullptr;
bool list_enabled_result = false;
int camera_count = 0;
int active_index = 0;
int selected_index = -1;
int activated_value = -1;
OpaqueCommandEntry command_entries[2]{};
OpaqueCommandCamera command_cameras[2]{};
OpaquePropertyList property_lists[2]{};
OpaquePropertyValue property_value{};
OpaqueWide active_category[2]{};
OpaqueWide inactive_category[2]{};
OpaqueWide default_category[2]{};
OpaquePropertyValue* listed_property = &property_value;
std::vector<OpaqueWord> list_categories;

void record(const char* value) { trace.emplace_back(value); }

void PKG_TEST_THISCALL dispose_message(OpaqueMessageService* value) {
  assert(value == message_service);
  record("message-dispose");
}

void PKG_TEST_CDECL deallocate_message(OpaqueMessageService* value) {
  assert(value == message_service);
  record("message-free");
}

void PKG_TEST_THISCALL dispose_cheat(OpaqueCheatService* value) {
  assert(value == cheat_service);
  record("cheat-dispose");
}

void PKG_TEST_CDECL deallocate_cheat(OpaqueCheatService* value) {
  assert(value == cheat_service);
  record("cheat-free");
}

void PKG_TEST_THISCALL dispatch_observer(void* value, OpaqueWord argument,
                                          bool enabled) {
  assert(value == observed_first || value == observed_second);
  observed_argument = argument;
  if (enabled) {
    observer_enable_count += 1;
    record("observer-enable");
  } else {
    observer_disable_count += 1;
    record("observer-disable");
  }
}

OpaqueCheatNode* PKG_TEST_CDECL next_cheat(OpaqueCheatNode* node) {
  if (node == cheat_first) {
    record("next-first");
    return cheat_second;
  }
  if (node == cheat_second) {
    record("next-second");
  }
  return cheat_sentinel;
}

void PKG_TEST_THISCALL install_continuation(void* value) {
  assert(value == &continuation_vtable || value != nullptr);
  record("continuation-install");
}

void PKG_TEST_THISCALL remove_continuation(void* value) {
  assert(value == &continuation_vtable || value != nullptr);
  record("continuation-remove");
}

void PKG_TEST_THISCALL remove_owner(void* value) {
  assert(value != nullptr);
  record("mouse-owner-remove");
}

void PKG_TEST_CDECL deallocate_mouse(OpaqueMouseCameraBase* value) {
  assert(value == mouse_base);
  record("mouse-free");
}

void setup_owned_services() {
  trace.clear();
  static OpaqueMessageService message{};
  static OpaqueCheatService cheat{};
  message_service = &message;
  cheat_service = &cheat;
  message_ports.dispose_0067db10 = dispose_message;
  message_ports.deallocate_00f47380 = deallocate_message;
  g_message_service_ports = &message_ports;
  cheat_ports.dispose_0067e2b0 = dispose_cheat;
  cheat_ports.deallocate_00f47380 = deallocate_cheat;
  cheat_ports.next_00921580 = next_cheat;
  g_cheat_service_ports = &cheat_ports;
  mouse_ports.deallocate_00f47380 = deallocate_mouse;
  g_mouse_camera_service_ports = &mouse_ports;
}

void verify_owned_adapters() {
  setup_owned_services();
  assert(service_0067dc80(message_service, 0u) == message_service);
  assert(trace.size() == 1u && trace[0] == "message-dispose");
  trace.clear();
  assert(service_0067dc80(message_service, 3u) == message_service);
  assert((trace.size() == 2u && trace[0] == "message-dispose" &&
          trace[1] == "message-free"));

  trace.clear();
  assert(service_0067e6b0(cheat_service, 2u) == cheat_service);
  assert(trace.size() == 1u && trace[0] == "cheat-dispose");
  trace.clear();
  assert(service_0067e6b0(cheat_service, 1u) == cheat_service);
  assert((trace.size() == 2u && trace[0] == "cheat-dispose" &&
          trace[1] == "cheat-free"));
}

void verify_cheat_dispatch() {
  setup_owned_services();
  observer_vtable.dispatch_1c = dispatch_observer;
  static OpaqueObserver first{};
  static OpaqueObserver second{};
  first.vtable = &observer_vtable;
  second.vtable = &observer_vtable;
  observed_first = &first;
  observed_second = &second;

  static OpaqueCheatNode first_node{};
  static OpaqueCheatNode second_node{};
  static OpaqueCheatNode sentinel_node{};
  first_node.observer = &first;
  second_node.observer = &second;
  cheat_sentinel = &sentinel_node;
  cheat_first = &first_node;
  cheat_second = &second_node;
  cheat_service->sentinel_04c = cheat_sentinel;
  cheat_service->first_050 = cheat_first;
  cheat_service->gate_064 = 0u;

  trace.clear();
  service_0067e6f0(cheat_service, 0x1234u);
  assert(trace.empty());
  service_0067e730(cheat_service, 0x5678u);
  assert(observer_disable_count == 2 && observed_argument == 0x5678u);
  assert((trace.size() == 4u && trace[0] == "observer-disable" &&
          trace[1] == "next-first" && trace[2] == "observer-disable" &&
          trace[3] == "next-second"));

  trace.clear();
  observer_disable_count = 0;
  cheat_service->gate_064 = 1u;
  service_0067e6f0(cheat_service, 0x9abcu);
  assert(observer_enable_count == 2 && observed_argument == 0x9abcu);
  assert((trace.size() == 4u && trace[0] == "observer-enable" &&
          trace[1] == "next-first" && trace[2] == "observer-enable" &&
          trace[3] == "next-second"));
}

void verify_continuation_replacement() {
  trace.clear();
  ContinuationVTable new_vtable{};
  new_vtable.install_00 = install_continuation;
  new_vtable.remove_04 = remove_continuation;
  ContinuationPort previous{};
  previous.vtable = &continuation_vtable;
  ContinuationPort next{};
  next.vtable = &new_vtable;
  ContinuationOwner owner{};
  owner.current_008 = &previous;

  service_0068f9b0(&owner, &previous);
  assert(trace.empty() && owner.current_008 == &previous);
  service_0068f9b0(&owner, &next);
  assert(owner.current_008 == &next);
  assert((trace.size() == 2u && trace[0] == "continuation-install" &&
          trace[1] == "continuation-remove"));

  trace.clear();
  service_0068f9b0(&owner, nullptr);
  assert(owner.current_008 == nullptr);
  assert((trace.size() == 1u && trace[0] == "continuation-remove"));
  trace.clear();
  service_0068f9b0(&owner, nullptr);
  assert(trace.empty());
}

void verify_mouse_tail_disposal() {
  trace.clear();
  alignas(OpaqueMouseCameraBase) std::uint8_t storage[sizeof(
      OpaqueMouseCameraBase) + 4u]{};
  mouse_base = reinterpret_cast<OpaqueMouseCameraBase*>(storage);
  auto* tail = reinterpret_cast<OpaqueMouseCameraTail*>(storage + 4u);
  static OpaqueOwnedObject owner{};
  owner.vtable = &object_vtable;
  object_vtable.remove_04 = remove_owner;
  mouse_base->owner_024 = &owner;
  assert(service_007d9410(tail, 1u) == mouse_base);
  assert((trace.size() == 2u && trace[0] == "mouse-owner-remove" &&
          trace[1] == "mouse-free"));
  assert(mouse_base->owner_024 == &owner);
  assert(reinterpret_cast<std::uintptr_t>(mouse_base->vtable_000) ==
         0x013eb938u);
}

bool PKG_TEST_THISCALL set_active_by_id(void* value, OpaqueWord id) {
  assert(value != nullptr);
  selected_index = static_cast<int>(id);
  record("camera-set-active-id");
  return false;
}

void verify_camera_getter_and_message() {
  trace.clear();
  selected_index = -1;
  camera_manager_vtable.set_active_by_id_54 = set_active_by_id;
  OpaqueCamera camera_a{};
  OpaqueCamera camera_b{};
  OpaqueCamera* cameras[2]{&camera_a, &camera_b};
  OpaqueMessageNode sentinel{};
  OpaqueMessageNode* buckets[2]{nullptr, &sentinel};
  OpaqueMessageRecord sentinel_message{};
  OpaqueMessageRecord camera_message{0x1234u, 0x22u};
  OpaqueCameraManager manager{};
  manager.vtable_000 = &camera_manager_vtable;
  manager.cameras_080 = cameras;
  manager.messages_060.buckets_004 = buckets;
  manager.messages_060.bucket_count_008 = 1u;
  manager.active_index_0a8 = -1;

  assert(service_007c61a0(&manager) == nullptr);
  manager.active_index_0a8 = 1;
  assert(service_007c61a0(&manager) == &camera_b);
  assert(!service_007c66b0(&manager, &sentinel_message));
  assert(trace.empty());
  assert(service_007c66b0(&manager, &camera_message));
  assert(selected_index == 0x22);
  assert((trace.size() == 1u && trace[0] == "camera-set-active-id"));
}

int PKG_TEST_CDECL parse_mode(OpaqueWord) { return parse_mode_result; }

bool PKG_TEST_CDECL log_current(OpaqueCommandSecondary*, void* value) {
  assert(value != nullptr);
  record("command-current");
  return current_log_result;
}

const char** PKG_TEST_CDECL parse_default(OpaqueWord, OpaqueWord* status,
                                          OpaqueWord) {
  *status = parse_default_status;
  return candidate_result;
}

const char** PKG_TEST_THISCALL lookup_switch(OpaqueWord, OpaqueWord) {
  record("command-switch");
  return candidate_result;
}

int PKG_TEST_CDECL is_digit(unsigned char value) {
  return value >= static_cast<unsigned char>('0') &&
         value <= static_cast<unsigned char>('9');
}

void PKG_TEST_CDECL widen(const char* value, int, OpaqueWideRange* range) {
  std::size_t index = 0;
  while (value[index] != '\0' && index < 7u) {
    widened_value[index] = static_cast<OpaqueWide>(
        static_cast<unsigned char>(value[index]));
    index += 1;
  }
  widened_value[index] = 0;
  range->begin = widened_value;
  range->end = widened_value + index;
}

int PKG_TEST_CDECL wide_compare(const OpaqueWide* left,
                                const OpaqueWide* right) {
  while (*left == *right) {
    if (*left == 0) {
      return 0;
    }
    left += 1;
    right += 1;
  }
  return 1;
}

bool PKG_TEST_CDECL free_value(void* value) {
  assert(value == widened_value);
  record("command-free");
  return free_result;
}

bool PKG_TEST_THISCALL list_enabled(OpaqueWord) {
  return list_enabled_result;
}

void PKG_TEST_CDECL log_list(OpaqueCommandSecondary*, int index, OpaqueWord id,
                             OpaqueWord description, OpaqueWord category) {
  record("command-list");
  assert(index == 0 || index == 1);
  assert(id == 0x013ec47cu);
  assert(description == static_cast<OpaqueWord>(index));
  list_categories.push_back(category);
}

const char** PKG_TEST_THISCALL lookup_target(OpaqueWord) {
  return target_result;
}

const char** PKG_TEST_THISCALL lookup_render_type(OpaqueWord) {
  return render_type_result;
}

OpaqueRenderer* PKG_TEST_CDECL renderer_get() {
  static OpaqueRenderer renderer{};
  renderer.vtable = &renderer_vtable;
  return &renderer;
}

void PKG_TEST_CDECL viewer_update(OpaqueWord value) {
  record("command-viewer-update");
  assert(value == target_value);
}

const OpaqueWide* PKG_TEST_CDECL get_default_category() {
  return default_category;
}

const OpaqueWide* PKG_TEST_CDECL active_category_value() {
  return active_category;
}

const OpaqueWide* PKG_TEST_CDECL inactive_category_value() {
  return inactive_category;
}

bool PKG_TEST_THISCALL end_update(OpaqueViewer* value) {
  assert(value == renderer_layer_result);
  record("command-end-update");
  return end_update_result;
}

int PKG_TEST_THISCALL command_count(void*) { return camera_count; }

OpaqueCommandCamera* PKG_TEST_THISCALL command_camera_at(void*, int index) {
  return &command_cameras[index];
}

OpaqueWord PKG_TEST_THISCALL command_describe(void*, int index, OpaqueWord id,
                                              OpaqueWord category) {
  assert(id == 0x013ec47cu);
  assert(category == static_cast<OpaqueWord>(index));
  return static_cast<OpaqueWord>(index);
}

void PKG_TEST_THISCALL command_set_active(void*, int index) {
  selected_index = index;
  record("command-set-active");
}

int PKG_TEST_THISCALL command_active(void*) { return active_index; }

void PKG_TEST_THISCALL command_activate(void*, OpaqueWord value) {
  activated_value = static_cast<int>(value);
  record("command-activate");
}

void* PKG_TEST_THISCALL command_get_properties(void* value) {
  assert(value == &command_cameras[0] || value == &command_cameras[1]);
  const auto index = static_cast<std::size_t>(
      reinterpret_cast<OpaqueCommandCamera*>(value) - command_cameras);
  return &property_lists[index];
}

bool PKG_TEST_THISCALL property_has(void* value, OpaqueWord id) {
  assert(id == 0x0b2cccau);
  return listed_property != nullptr && value == &property_lists[0];
}

void* PKG_TEST_THISCALL property_get(void*, OpaqueWord id) {
  assert(id == 0x0b2cccau);
  return listed_property;
}

OpaqueWord PKG_TEST_THISCALL resolve_digit(void*, const char*) {
  record("command-resolve-digit");
  return resolved_digit;
}

OpaqueViewer* PKG_TEST_THISCALL resolve_render_type(void*, OpaqueWord value) {
  assert(value == render_type_value);
  record("command-resolve-render-type");
  return resolved_viewer;
}

const OpaqueRect* PKG_TEST_THISCALL resolve_target(void*, OpaqueRect* rect,
                                                   OpaqueWord value) {
  assert(value == target_value);
  record("command-resolve-target");
  return rect;
}

OpaqueViewer* PKG_TEST_THISCALL renderer_layer(OpaqueRenderer*,
                                                OpaqueViewer*, OpaqueWord) {
  renderer_layer_calls += 1;
  record("command-renderer-layer");
  return renderer_layer_result;
}

void setup_command_ports() {
  trace.clear();
  list_categories.clear();
  command_ports.parse_mode_00837f30 = parse_mode;
  command_ports.log_current_00841000 = log_current;
  command_ports.parse_default_00838020 = parse_default;
  command_ports.lookup_switch_00838330 = lookup_switch;
  command_ports.is_digit = is_digit;
  command_ports.widen_0093c5a0 = widen;
  command_ports.wide_compare = wide_compare;
  command_ports.free_00f47380 = free_value;
  command_ports.list_enabled_008380b0 = list_enabled;
  command_ports.log_list_00841000 = log_list;
  command_ports.lookup_target_00838330 = lookup_target;
  command_ports.lookup_render_type_00838330 = lookup_render_type;
  command_ports.renderer_get_0067dd10 = renderer_get;
  command_ports.viewer_update_007c3c20 = viewer_update;
  command_ports.default_category_007c65a0 = get_default_category;
  command_ports.active_category_013ec468 = active_category_value;
  command_ports.inactive_category_013ed024 = inactive_category_value;
  command_ports.end_update_007c3ce0 = end_update;
  g_camera_command_ports = &command_ports;

  command_collection_vtable.count_48 = command_count;
  command_collection_vtable.camera_at_4c = command_camera_at;
  command_collection_vtable.describe_50 = command_describe;
  command_collection_vtable.set_active_54 = command_set_active;
  command_collection_vtable.active_58 = command_active;
  command_collection_vtable.activate_34 = command_activate;
  command_secondary_vtable.resolve_digit_a0 = resolve_digit;
  command_secondary_vtable.resolve_render_type_9c = resolve_render_type;
  command_secondary_vtable.resolve_target_b4 = resolve_target;
  command_camera_vtable.get_property_list_4c = command_get_properties;
  property_list_vtable.has_1c = property_has;
  property_list_vtable.get_28 = property_get;
  renderer_vtable.layer_00.two = renderer_layer;

  active_category[0] = 0u;
  inactive_category[0] = 1u;
  default_category[0] = 2u;
  static OpaqueWide name_storage[8]{};
  widened_value = name_storage;
  command_entries[0].first = widened_value;
  command_entries[0].second = command_entries + 1;
  command_entries[1].first = command_entries + 1;
  command_entries[1].second = command_entries + 1;
}

void verify_camera_command_current() {
  setup_command_ports();
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries + 2;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 2;
  active_index = 0;
  parse_mode_result = 1;
  current_log_result = true;

  assert(service_007c6750(&owner, 0x10u));
  assert((trace.size() == 1u && trace[0] == "command-current"));
}

void verify_camera_command_name() {
  setup_command_ports();
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries + 2;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 2;
  active_index = 0;
  parse_mode_result = 0;
  static const char candidate[] = "Alpha";
  candidate_value = candidate;
  candidate_result = &candidate_value;
  free_result = true;
  selected_index = -1;

  assert(service_007c6750(&owner, 0x20u));
  assert(selected_index == 0);
  assert((trace.size() == 2u && trace[0] == "command-set-active" &&
          trace[1] == "command-free"));
}

void verify_camera_command_digit() {
  setup_command_ports();
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries + 2;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 0;
  active_index = 0;
  parse_mode_result = 0;
  static const char candidate[] = "2";
  candidate_value = candidate;
  candidate_result = &candidate_value;
  resolved_digit = 0x44u;
  activated_value = -1;
  list_enabled_result = false;
  target_result = nullptr;
  render_type_result = nullptr;

  assert(!service_007c6750(&owner, 0x30u));
  assert(activated_value == 0x44);
  assert((trace.size() == 2u && trace[0] == "command-resolve-digit" &&
          trace[1] == "command-activate"));
}

void verify_camera_command_list() {
  setup_command_ports();
  command_cameras[0].vtable = &command_camera_vtable;
  command_cameras[1].vtable = &command_camera_vtable;
  property_lists[0].vtable = &property_list_vtable;
  property_lists[1].vtable = &property_list_vtable;
  property_value.type_012 = 1u;
  listed_property = &property_value;
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries + 2;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 2;
  active_index = 0;
  parse_mode_result = 0;
  candidate_result = nullptr;
  list_enabled_result = true;
  target_result = nullptr;
  render_type_result = nullptr;

  assert(!service_007c6750(&owner, 0x40u));
  assert(trace.size() == 2u && trace[0] == "command-list" &&
         trace[1] == "command-list");
  assert(list_categories.size() == 2u && list_categories[0] == 2u &&
         list_categories[1] == 1u);
}

void verify_camera_command_render_type() {
  setup_command_ports();
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 0;
  active_index = 0;
  parse_mode_result = 0;
  candidate_result = nullptr;
  list_enabled_result = false;
  target_result = nullptr;
  render_type_value = 0x1234u;
  render_type_result =
      reinterpret_cast<const char**>(&render_type_value);
  resolved_viewer = reinterpret_cast<OpaqueViewer*>(0x1000u);
  renderer_layer_result = reinterpret_cast<OpaqueViewer*>(0x2000u);
  renderer_layer_calls = 0;
  end_update_result = true;

  assert(service_007c6750(&owner, 0x50u));
  assert(renderer_layer_calls == 1);
  assert((trace.size() == 3u &&
          trace[0] == "command-resolve-render-type" &&
          trace[1] == "command-renderer-layer" &&
          trace[2] == "command-end-update"));
}

void verify_camera_command_missing_name() {
  setup_command_ports();
  OpaqueCommandCollection collection{};
  collection.vtable = &command_collection_vtable;
  collection.entries_094 = command_entries;
  collection.entries_098 = command_entries;
  OpaqueCommandSecondary secondary{};
  secondary.vtable = &command_secondary_vtable;
  OpaqueCameraCommandOwner owner{};
  owner.secondary_004 = &secondary;
  owner.collection_010 = &collection;
  camera_count = 0;
  active_index = 0;
  parse_mode_result = 0;
  static const char candidate[] = "Z";
  candidate_value = candidate;
  candidate_result = &candidate_value;

  bool threw = false;
  try {
    static_cast<void>(service_007c6750(&owner, 0x60u));
  } catch (const OpaqueCameraCommandError&) {
    threw = true;
  }
  assert(threw);
}

}

int main() {
  verify_owned_adapters();
  verify_cheat_dispatch();
  verify_continuation_replacement();
  verify_mouse_tail_disposal();
  verify_camera_getter_and_message();
  verify_camera_command_current();
  verify_camera_command_name();
  verify_camera_command_digit();
  verify_camera_command_list();
  verify_camera_command_render_type();
  verify_camera_command_missing_name();
  return 0;
}

#undef PKG_TEST_CDECL
#undef PKG_TEST_THISCALL
