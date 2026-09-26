#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "app_services.hpp"
#include "camera_services.hpp"

#if defined(_MSC_VER)
#define PKG_TEST_CDECL __cdecl
#define PKG_TEST_THISCALL __thiscall
#define PKG_TEST_NOINLINE __declspec(noinline)
#define PKG_TEST_NAKED __declspec(naked)
#else
#define PKG_TEST_CDECL __attribute__((cdecl))
#define PKG_TEST_THISCALL __attribute__((thiscall))
#define PKG_TEST_NOINLINE __attribute__((noinline))
#define PKG_TEST_NAKED __attribute__((naked))
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
OpaqueWord parse_mode_receiver = 0;
OpaqueWord parse_default_receiver = 0;
OpaqueWord parse_default_status = 1;
const char* candidate_value = nullptr;
const char** candidate_result = nullptr;
OpaqueWide* widened_value = nullptr;
bool free_result = true;
int renderer_layer_calls = 0;
OpaqueViewer* renderer_layer_result = nullptr;
bool end_update_result = false;
OpaqueViewer* end_update_receiver = nullptr;
OpaqueWord resolved_digit = 0;
OpaqueViewer* resolved_viewer = nullptr;
OpaqueWord target_value = 0;
OpaqueWord render_type_value = 0;
const char** target_result = nullptr;
const char** render_type_result = nullptr;
bool list_enabled_result = false;
OpaqueWord list_enabled_receiver = 0;
int camera_count = 0;
int active_index = 0;
int selected_index = -1;
int activated_value = -1;
OpaqueCommandEntry command_entries[2]{};
OpaqueCommandCamera command_cameras[2]{};
OpaquePropertyList property_lists[2]{};
OpaquePropertyValue property_value{};
OpaqueWide default_category[2]{};
OpaquePropertyValue* listed_property = &property_value;
OpaqueWord list_enabled_argument = 0;
OpaqueWideRange* widened_range = nullptr;
const char* widened_source = nullptr;
OpaqueWord widened_length = 0;
OpaqueWord current_log_return = 0;
std::vector<OpaqueWord> list_log_values;
std::vector<std::uintptr_t> list_categories;
std::vector<std::uintptr_t> list_names;
std::vector<OpaqueWord> list_described_ids;
std::vector<OpaqueWord> list_described_indexes;
std::vector<OpaqueWord> list_descriptions;
OpaqueWord end_update_words[2]{};

void record(const char* value) { trace.emplace_back(value); }

template <typename Function>
PKG_TEST_NOINLINE std::uintptr_t invoke_thiscall_noargs(Function function,
                                                        void* receiver) {
  std::uintptr_t result = 0;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "call *%2"
      : "=&a"(result)
      : "r"(receiver), "r"(function)
      : "cc", "ecx", "edx", "memory");
  return result;
}

template <typename Function, typename Arg>
PKG_TEST_NOINLINE std::uintptr_t invoke_thiscall_word(Function function,
                                                      void* receiver,
                                                      Arg value) {
  std::uintptr_t result = 0;
  __asm__ volatile(
      "movl %1, %%ecx\n\t"
      "pushl %3\n\t"
      "call *%2"
      : "=&a"(result)
      : "r"(receiver), "r"(function), "r"(value)
      : "cc", "ecx", "edx", "memory");
  return result;
}

template <typename Function, typename Arg>
PKG_TEST_NOINLINE void invoke_thiscall_void(Function function, void* receiver,
                                            Arg value) {
  __asm__ volatile(
      "movl %1, %%eax\n\t"
      "movl %0, %%ecx\n\t"
      "pushl %2\n\t"
      "call *%%eax"
      :
      : "r"(receiver), "m"(function), "r"(value)
      : "eax", "cc", "ecx", "edx", "memory");
}

[[maybe_unused]] OpaqueMessageService* invoke_service_0067dc80(
    OpaqueMessageService* service, OpaqueWord ownership) {
  return reinterpret_cast<OpaqueMessageService*>(
      invoke_thiscall_word(&service_0067dc80, service, ownership));
}

[[maybe_unused]] OpaqueCheatService* invoke_service_0067e6b0(
    OpaqueCheatService* service, OpaqueWord ownership) {
  return reinterpret_cast<OpaqueCheatService*>(
      invoke_thiscall_word(&service_0067e6b0, service, ownership));
}

[[maybe_unused]] void invoke_service_0067e6f0(OpaqueCheatService* service,
                                              OpaqueWord event_argument) {
  invoke_thiscall_void(&service_0067e6f0, service, event_argument);
}

[[maybe_unused]] void invoke_service_0067e730(OpaqueCheatService* service,
                                              OpaqueWord event_argument) {
  invoke_thiscall_void(&service_0067e730, service, event_argument);
}

[[maybe_unused]] void invoke_service_0068f9b0(ContinuationOwner* owner,
                                              ContinuationPort* continuation) {
  invoke_thiscall_void(&service_0068f9b0, owner, continuation);
}

[[maybe_unused]] OpaqueMouseCameraBase* invoke_service_007d9410(
    OpaqueMouseCameraTail* tail, OpaqueWord ownership) {
  return reinterpret_cast<OpaqueMouseCameraBase*>(
      invoke_thiscall_word(&service_007d9410, tail, ownership));
}

[[maybe_unused]] OpaqueCamera* invoke_service_007c61a0(
    OpaqueCameraManager* manager) {
  return reinterpret_cast<OpaqueCamera*>(
      invoke_thiscall_noargs(&service_007c61a0, manager));
}

[[maybe_unused]] bool invoke_service_007c66b0(OpaqueCameraManager* manager,
                                              OpaqueWord message_id) {
  return (invoke_thiscall_word(&service_007c66b0, manager, message_id) & 1u) !=
         0u;
}

[[maybe_unused]] PKG_TEST_NOINLINE bool invoke_service_007c6750(
    OpaqueCameraCommandOwner* owner, OpaqueWord argument) {
  return (invoke_thiscall_word(&service_007c6750, owner, argument) & 1u) != 0u;
}

void PKG_TEST_THISCALL dispose_message(OpaqueMessageService* value) {
  static_cast<void>(value);
  record("message-dispose");
}

void PKG_TEST_CDECL deallocate_message(OpaqueMessageService* value) {
  static_cast<void>(value);
  assert(value == message_service);
  record("message-free");
}

void PKG_TEST_THISCALL dispose_cheat(OpaqueCheatService* value) {
  static_cast<void>(value);
  record("cheat-dispose");
}

void PKG_TEST_CDECL deallocate_cheat(OpaqueCheatService* value) {
  static_cast<void>(value);
  assert(value == cheat_service);
  record("cheat-free");
}

void PKG_TEST_THISCALL dispatch_observer(OpaqueObserver* value, bool enabled,
                                         OpaqueWord event) {
  static_cast<void>(value);
  observed_argument = event;
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

void PKG_TEST_THISCALL install_continuation(ContinuationPort* value) {
  static_cast<void>(value);
  record("continuation-install");
}

void PKG_TEST_THISCALL remove_continuation(ContinuationPort* value) {
  static_cast<void>(value);
  record("continuation-remove");
}

void PKG_TEST_THISCALL remove_owner(OpaqueOwnedObject* value) {
  static_cast<void>(value);
  record("mouse-owner-remove");
}

void PKG_TEST_CDECL deallocate_mouse(OpaqueMouseCameraBase* value) {
  static_cast<void>(value);
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
  assert(invoke_service_0067dc80(message_service, 0u) == message_service);
  assert(trace.size() == 1u && trace[0] == "message-dispose");
  trace.clear();
  assert(invoke_service_0067dc80(message_service, 3u) == message_service);
  assert((trace.size() == 2u && trace[0] == "message-dispose" &&
          trace[1] == "message-free"));

  trace.clear();
  assert(invoke_service_0067e6b0(cheat_service, 2u) == cheat_service);
  assert(trace.size() == 1u && trace[0] == "cheat-dispose");
  trace.clear();
  assert(invoke_service_0067e6b0(cheat_service, 1u) == cheat_service);
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
  invoke_service_0067e6f0(cheat_service, 0x1234u);
  assert(trace.empty());
  invoke_service_0067e730(cheat_service, 0x5678u);
  assert(observer_disable_count == 2 && observed_argument == 0x5678u);
  assert((trace.size() == 4u && trace[0] == "observer-disable" &&
          trace[1] == "next-first" && trace[2] == "observer-disable" &&
          trace[3] == "next-second"));

  trace.clear();
  observer_disable_count = 0;
  cheat_service->gate_064 = 1u;
  invoke_service_0067e6f0(cheat_service, 0x9abcu);
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
  continuation_vtable.install_00 = install_continuation;
  continuation_vtable.remove_04 = remove_continuation;
  ContinuationPort previous{};
  previous.vtable = &continuation_vtable;
  ContinuationPort next{};
  next.vtable = &new_vtable;
  ContinuationOwner owner{};
  owner.current_008 = &previous;

  invoke_service_0068f9b0(&owner, &previous);
  assert(trace.empty() && owner.current_008 == &previous);
  invoke_service_0068f9b0(&owner, &next);
  assert(owner.current_008 == &next);
  assert((trace.size() == 2u && trace[0] == "continuation-install" &&
          trace[1] == "continuation-remove"));

  trace.clear();
  invoke_service_0068f9b0(&owner, nullptr);
  assert(owner.current_008 == nullptr);
  assert((trace.size() == 1u && trace[0] == "continuation-remove"));
  trace.clear();
  invoke_service_0068f9b0(&owner, nullptr);
  assert(trace.empty());
}

void verify_mouse_tail_disposal() {
  trace.clear();
  alignas(OpaqueMouseCameraBase)
      std::uint8_t storage[sizeof(OpaqueMouseCameraBase) + 4u]{};
  mouse_base = reinterpret_cast<OpaqueMouseCameraBase*>(storage);
  auto* tail = reinterpret_cast<OpaqueMouseCameraTail*>(storage + 4u);
  static_cast<void>(tail);
  static OpaqueOwnedObject owner{};
  owner.vtable = &object_vtable;
  object_vtable.remove_04 = remove_owner;
  mouse_base->owner_024 = &owner;
  auto* original_vtable = reinterpret_cast<void*>(0x01234567u);
  mouse_base->vtable_000 = original_vtable;
  assert(invoke_service_007d9410(tail, 1u) == mouse_base);
  assert((trace.size() == 2u && trace[0] == "mouse-owner-remove" &&
          trace[1] == "mouse-free"));
  assert(mouse_base->owner_024 == &owner);
  assert(reinterpret_cast<std::uintptr_t>(mouse_base->vtable_000) ==
         0x013eb938u);
  assert(reinterpret_cast<std::uintptr_t>(mouse_base->listener_vtable_004) ==
         0x013eb394u);
  assert(reinterpret_cast<std::uintptr_t>(mouse_base->virtual_vtable_008) ==
         0x013ef094u);

  trace.clear();
  mouse_base->owner_024 = &owner;
  assert(invoke_service_007d9410(tail, 0u) == mouse_base);
  assert((trace.size() == 1u && trace[0] == "mouse-owner-remove"));
}

bool PKG_TEST_THISCALL set_active_by_id(OpaqueCameraManager* value,
                                        OpaqueWord id) {
  static_cast<void>(value);
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
  OpaqueMessageNode live_node{};
  live_node.key = 0x1234u;
  live_node.value = 0x33u;
  OpaqueMessageNode sentinel{};
  OpaqueMessageNode* buckets[2]{&live_node, &sentinel};
  OpaqueCameraManager manager{};
  manager.vtable_000 = &camera_manager_vtable;
  manager.cameras_080 = cameras;
  manager.messages_060.buckets_004 = buckets;
  manager.messages_060.bucket_count_008 = 1u;
  manager.active_index_0a8 = -1;

  assert(invoke_service_007c61a0(&manager) == nullptr);
  manager.active_index_0a8 = 1;
  assert(invoke_service_007c61a0(&manager) == &camera_b);
  assert(!invoke_service_007c66b0(&manager, 0x9999u));
  assert(trace.empty());
  assert(invoke_service_007c66b0(&manager, 0x1234u));
  assert(selected_index == 0x33);
  assert((trace.size() == 1u && trace[0] == "camera-set-active-id"));
}

int PKG_TEST_THISCALL parse_mode(OpaqueWord receiver) {
  parse_mode_receiver = receiver;
  return parse_mode_result;
}

OpaqueWord PKG_TEST_CDECL log_current(OpaqueCommandSecondary*,
                                      const char* format,
                                      const OpaqueWide* value) {
  static_cast<void>(format);
  current_log_return = value == nullptr ? 0u : 0xa5u;
  return current_log_return;
}

const char** PKG_TEST_THISCALL parse_default(OpaqueWord receiver,
                                             OpaqueWord* status,
                                             OpaqueWord minimum,
                                             OpaqueWord maximum) {
  parse_default_receiver = receiver;
  static_cast<void>(minimum);
  static_cast<void>(maximum);
  assert(minimum == 0u && maximum == 1u);
  *status = parse_default_status;
  return candidate_result;
}

extern "C" const char** lookup_switch_body(OpaqueWord, OpaqueWord) {
  record("command-switch");
  return candidate_result;
}

extern "C" PKG_TEST_NAKED const char** lookup_switch(OpaqueWord, OpaqueWord) {
  __asm__ volatile(
      "movl 4(%esp), %eax\n\t"
      "movl 8(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "pushl %eax\n\t"
      "call lookup_switch_body\n\t"
      "addl $8, %esp\n\t"
      "ret $8");
}

int PKG_TEST_CDECL is_digit(unsigned char value) {
  return value >= static_cast<unsigned char>('0') &&
         value <= static_cast<unsigned char>('9');
}

void PKG_TEST_CDECL widen(OpaqueWideRange* range, const char* value,
                          OpaqueWord length) {
  widened_range = range;
  widened_source = value;
  widened_length = length;
  std::size_t index = 0;
  while (value[index] != '\0' && index < 7u) {
    widened_value[index] =
        static_cast<OpaqueWide>(static_cast<unsigned char>(value[index]));
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
  static_cast<void>(value);
  assert(value == widened_value);
  record("command-free");
  return free_result;
}

bool PKG_TEST_THISCALL list_enabled(OpaqueWord receiver, OpaqueWord value) {
  list_enabled_receiver = receiver;
  list_enabled_argument = value;
  return list_enabled_result;
}

OpaqueWord PKG_TEST_CDECL log_named(OpaqueCommandSecondary*, const char* format,
                                    const char* category,
                                    const OpaqueWide* name, OpaqueWord value) {
  static_cast<void>(format);
  assert(format == reinterpret_cast<const char*>(0x01410648u));
  record("command-list-named");
  list_log_values.push_back(value);
  list_categories.push_back(reinterpret_cast<std::uintptr_t>(category));
  list_names.push_back(reinterpret_cast<std::uintptr_t>(name));
  return 0xc001cafeu;
}

OpaqueWord PKG_TEST_CDECL log_described(OpaqueCommandSecondary*,
                                        const char* format, OpaqueWord value,
                                        OpaqueWord description,
                                        OpaqueWord index, OpaqueWord id) {
  static_cast<void>(format);
  assert(format == reinterpret_cast<const char*>(0x01410628u));
  record("command-list-described");
  list_log_values.push_back(value);
  list_described_ids.push_back(id);
  list_described_indexes.push_back(index);
  list_descriptions.push_back(description);
  return 0xc001cafeu;
}

extern "C" const char** lookup_target_body(OpaqueWord key, OpaqueWord mode) {
  static_cast<void>(key);
  static_cast<void>(mode);
  assert(key == 0x01410624u && mode == 1u);
  return target_result;
}

extern "C" PKG_TEST_NAKED const char** lookup_target(OpaqueWord, OpaqueWord) {
  __asm__ volatile(
      "movl 4(%esp), %eax\n\t"
      "movl 8(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "pushl %eax\n\t"
      "call lookup_target_body\n\t"
      "addl $8, %esp\n\t"
      "ret $8");
}

extern "C" const char** lookup_render_type_body(OpaqueWord key,
                                                OpaqueWord mode) {
  static_cast<void>(key);
  static_cast<void>(mode);
  assert(key == 0x01410618u && mode == 1u);
  return render_type_result;
}

extern "C" PKG_TEST_NAKED const char** lookup_render_type(OpaqueWord,
                                                          OpaqueWord) {
  __asm__ volatile(
      "movl 4(%esp), %eax\n\t"
      "movl 8(%esp), %edx\n\t"
      "pushl %edx\n\t"
      "pushl %eax\n\t"
      "call lookup_render_type_body\n\t"
      "addl $8, %esp\n\t"
      "ret $8");
}

OpaqueRenderer* PKG_TEST_CDECL renderer_get() {
  static OpaqueRenderer renderer{};
  renderer.vtable = &renderer_vtable;
  return &renderer;
}

void PKG_TEST_THISCALL viewer_update(OpaqueViewer* value,
                                     const OpaqueRect* rect) {
  static_cast<void>(value);
  static_cast<void>(rect);
  assert(rect != nullptr);
  record("command-viewer-update");
}

const OpaqueWide* PKG_TEST_CDECL get_default_category() {
  return default_category;
}

bool PKG_TEST_THISCALL end_update(OpaqueViewer* receiver, OpaqueWord first,
                                  OpaqueWord second) {
  end_update_receiver = receiver;
  end_update_words[0] = first;
  end_update_words[1] = second;
  record("command-end-update");
  return end_update_result;
}

int PKG_TEST_THISCALL command_count(OpaqueCommandCollection* value) {
  static_cast<void>(value);
  return camera_count;
}

OpaqueCommandCamera* PKG_TEST_THISCALL
command_camera_at(OpaqueCommandCollection* value, int index) {
  static_cast<void>(value);
  return &command_cameras[index];
}

OpaqueWord PKG_TEST_CDECL command_describe(int index, OpaqueWord id) {
  static_cast<void>(id);
  assert(id == 0x013ec47cu);
  return 0x00800000u | static_cast<OpaqueWord>(index);
}

void PKG_TEST_THISCALL command_set_active(OpaqueCommandCollection* value,
                                          int index) {
  static_cast<void>(value);
  selected_index = index;
  record("command-set-active");
}

int PKG_TEST_THISCALL command_active(OpaqueCommandCollection* value) {
  static_cast<void>(value);
  return active_index;
}

void PKG_TEST_THISCALL command_activate(OpaqueCommandCollection* value,
                                        OpaqueWord argument) {
  static_cast<void>(value);
  activated_value = static_cast<int>(argument);
  record("command-activate");
}

void* PKG_TEST_THISCALL command_get_properties(OpaqueCommandCamera* value) {
  assert(value == &command_cameras[0] || value == &command_cameras[1]);
  const auto index = static_cast<std::size_t>(value - command_cameras);
  return index == 0u ? &property_lists[0] : nullptr;
}

bool PKG_TEST_THISCALL property_has(OpaquePropertyList* value, OpaqueWord id) {
  static_cast<void>(value);
  static_cast<void>(id);
  assert(value == &property_lists[0] || value == &property_lists[1]);
  assert(id == 0x0b2cccau);
  return listed_property != nullptr;
}

void* PKG_TEST_THISCALL property_get(OpaquePropertyList* value, OpaqueWord id) {
  static_cast<void>(value);
  static_cast<void>(id);
  assert(value == &property_lists[0] || value == &property_lists[1]);
  assert(id == 0x0b2cccau);
  return listed_property;
}

OpaqueWord PKG_TEST_THISCALL resolve_digit(OpaqueCommandSecondary* value,
                                           const char* argument) {
  static_cast<void>(value);
  static_cast<void>(argument);
  record("command-resolve-digit");
  return resolved_digit;
}

OpaqueViewer* PKG_TEST_THISCALL
resolve_render_type(OpaqueCommandSecondary* value, OpaqueWord argument) {
  static_cast<void>(value);
  static_cast<void>(argument);
  assert(argument == render_type_value);
  record("command-resolve-render-type");
  return resolved_viewer;
}

const OpaqueRect* PKG_TEST_THISCALL resolve_target(
    OpaqueCommandSecondary* value, OpaqueRect* rect, OpaqueWord argument) {
  static_cast<void>(value);
  static_cast<void>(argument);
  assert(argument == target_value);
  const OpaqueWord words[2]{0x12345678u, 0x9abcdef0u};
  std::memcpy(rect, words, sizeof(words));
  record("command-resolve-target");
  return rect;
}

OpaqueViewer* PKG_TEST_THISCALL renderer_layer_one(OpaqueRenderer* value,
                                                   const void* argument) {
  static_cast<void>(value);
  static_cast<void>(argument);
  renderer_layer_calls += 1;
  record("command-renderer-layer");
  return renderer_layer_result;
}

OpaqueViewer* PKG_TEST_THISCALL renderer_layer(OpaqueRenderer* value,
                                               OpaqueViewer* argument,
                                               OpaqueWord tag) {
  static_cast<void>(value);
  static_cast<void>(argument);
  static_cast<void>(tag);
  assert(tag == 0u);
  renderer_layer_calls += 1;
  record("command-renderer-layer");
  return renderer_layer_result;
}

void setup_command_ports() {
  trace.clear();
  list_log_values.clear();
  list_categories.clear();
  list_names.clear();
  list_described_ids.clear();
  list_described_indexes.clear();
  list_descriptions.clear();
  list_enabled_argument = 0;
  list_enabled_receiver = 0;
  widened_range = nullptr;
  widened_source = nullptr;
  widened_length = 0;
  parse_mode_receiver = 0;
  parse_default_receiver = 0;
  end_update_receiver = nullptr;
  end_update_words[0] = 0;
  end_update_words[1] = 0;
  command_ports.parse_mode_00837f30 = parse_mode;
  command_ports.log_current_00841000 = log_current;
  command_ports.parse_default_00838020 = parse_default;
  command_ports.lookup_switch_00838330 = lookup_switch;
  command_ports.is_digit = is_digit;
  command_ports.widen_0093c5a0 = widen;
  command_ports.wide_compare = wide_compare;
  command_ports.free_00f47380 = free_value;
  command_ports.list_enabled_008380b0 = list_enabled;
  command_ports.log_named_00841000 = log_named;
  command_ports.log_described_00841000 = log_described;
  command_ports.lookup_target_00838330 = lookup_target;
  command_ports.lookup_render_type_00838330 = lookup_render_type;
  command_ports.renderer_get_0067dd10 = renderer_get;
  command_ports.viewer_update_007c3c20 = viewer_update;
  command_ports.default_category_007c65a0 = get_default_category;
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
  renderer_vtable.layer_58.one = renderer_layer_one;

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

  assert(invoke_service_007c6750(&owner, 0x10u));
  assert(parse_mode_receiver == 0x10u);
  assert(current_log_return == 0xa5u);
  assert(trace.empty());
  command_entries[0].first = command_entries + 1;
  assert(!invoke_service_007c6750(&owner, 0x10u));
  assert(current_log_return == 0u);
  assert(trace.empty());
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
  command_entries[0].first = command_entries + 1;
  command_entries[0].second = command_entries + 1;
  command_entries[1].first = widened_value;
  command_entries[1].second = command_entries + 1;

  assert(invoke_service_007c6750(&owner, 0x20u));
  assert(parse_default_receiver == 0x20u);
  assert(selected_index == 1);
  assert(widened_range != nullptr && widened_source == candidate &&
         widened_length == 0xffffffffu);
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

  assert(!invoke_service_007c6750(&owner, 0x30u));
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

  assert(!invoke_service_007c6750(&owner, 0x40u));
  assert(list_enabled_receiver == 0x40u);
  assert(list_enabled_argument == 0x01409070u);
  assert(trace.size() == 2u && trace[0] == "command-list-named" &&
         trace[1] == "command-list-described");
  assert(list_log_values.size() == 2u && list_log_values[0] == 2u &&
         list_log_values[1] == 0x013ec468u);
  assert(list_categories.size() == 1u && list_categories[0] == 0x01401b58u);
  assert(list_names.size() == 1u &&
         list_names[0] == reinterpret_cast<std::uintptr_t>(widened_value));
  assert(list_described_ids.size() == 1u &&
         list_described_ids[0] == 0x013ec47cu);
  assert(list_described_indexes.size() == 1u &&
         list_described_indexes[0] == 1u);
  assert(list_descriptions.size() == 1u && list_descriptions[0] == 0x00800001u);

  trace.clear();
  list_log_values.clear();
  list_categories.clear();
  list_names.clear();
  list_described_ids.clear();
  list_described_indexes.clear();
  list_descriptions.clear();
  active_index = 1;
  assert(!invoke_service_007c6750(&owner, 0x401u));
  assert(list_log_values.size() == 2u && list_log_values[0] == 2u &&
         list_log_values[1] == 0x013ec468u);
  assert(list_categories.size() == 1u && list_categories[0] == 0x013ed024u);
}

void verify_camera_command_property_categories() {
  setup_command_ports();
  command_cameras[0].vtable = &command_camera_vtable;
  command_cameras[1].vtable = &command_camera_vtable;
  property_lists[0].vtable = &property_list_vtable;
  property_lists[1].vtable = &property_list_vtable;
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
  listed_property = &property_value;

  const auto clear_list_records = [] {
    trace.clear();
    list_log_values.clear();
    list_categories.clear();
    list_names.clear();
    list_described_ids.clear();
    list_described_indexes.clear();
    list_descriptions.clear();
  };

  OpaqueWide payload_category[2]{0x55u, 0u};
  property_value.type_012 = 0x10u;
  property_value.flags_010 = 0x30u;
  property_value.payload = payload_category;
  assert(!invoke_service_007c6750(&owner, 0x41u));
  assert(list_log_values.size() == 2u && list_log_values[0] == 0x55u &&
         list_log_values[1] == 0x013ec468u);
  assert(list_categories.size() == 1u && list_categories[0] == 0x01401b58u);

  clear_list_records();
  property_value.type_012 = 0x13u;
  property_value.flags_010 = 0u;
  property_value.payload =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x12345678u));
  assert(!invoke_service_007c6750(&owner, 0x42u));
  assert(list_log_values.size() == 2u && list_log_values[0] == 0x12345678u &&
         list_log_values[1] == 0x013ec468u);

  clear_list_records();
  property_value.type_012 = 0x10u;
  assert(!invoke_service_007c6750(&owner, 0x43u));
  assert(list_log_values.size() == 2u && list_log_values[0] == 0x12345678u &&
         list_log_values[1] == 0x013ec468u);

  clear_list_records();
  property_value.type_012 = 0x13u;
  property_value.payload = nullptr;
  assert(!invoke_service_007c6750(&owner, 0x44u));
  assert(list_log_values.size() == 2u && list_log_values[0] == 0u &&
         list_log_values[1] == 0x013ec468u);
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
  render_type_result = reinterpret_cast<const char**>(&render_type_value);
  resolved_viewer = reinterpret_cast<OpaqueViewer*>(0x1000u);
  renderer_layer_result = reinterpret_cast<OpaqueViewer*>(0x2000u);
  renderer_layer_calls = 0;
  end_update_result = true;
  renderer_vtable.layer_58.two = renderer_layer;

  assert(invoke_service_007c6750(&owner, 0x50u));
  assert(renderer_layer_calls == 1);
  assert(end_update_receiver == renderer_layer_result);
  assert(end_update_words[0] == 0x1000u && end_update_words[1] == 0u);
  assert((trace.size() == 3u && trace[0] == "command-resolve-render-type" &&
          trace[1] == "command-renderer-layer" &&
          trace[2] == "command-end-update"));
}

void verify_camera_command_end_update_arguments() {
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
  target_value = 0x1234u;
  target_result = nullptr;
  render_type_value = 0x5678u;
  render_type_result = reinterpret_cast<const char**>(&render_type_value);
  resolved_viewer = reinterpret_cast<OpaqueViewer*>(0x1000u);
  renderer_layer_result = reinterpret_cast<OpaqueViewer*>(0x2000u);
  renderer_layer_calls = 0;
  end_update_result = true;
  renderer_vtable.layer_58.two = renderer_layer;

  assert(invoke_service_007c6750(&owner, 0x51u));
  assert(renderer_layer_calls == 1);
  assert(end_update_receiver == renderer_layer_result);
  assert(end_update_words[0] == 0x1000u && end_update_words[1] == 0u);
  assert((trace.size() == 3u && trace[0] == "command-resolve-render-type" &&
          trace[1] == "command-renderer-layer" &&
          trace[2] == "command-end-update"));
}

void verify_camera_command_target() {
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
  target_value = 0x1234u;
  target_result = reinterpret_cast<const char**>(&target_value);
  render_type_result = nullptr;
  renderer_layer_result = reinterpret_cast<OpaqueViewer*>(0x2000u);
  renderer_layer_calls = 0;

  assert(!invoke_service_007c6750(&owner, 0x55u));
  assert(renderer_layer_calls == 1);
  assert((trace.size() == 3u && trace[0] == "command-resolve-target" &&
          trace[1] == "command-renderer-layer" &&
          trace[2] == "command-viewer-update"));
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
  static_cast<void>(threw);
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
  verify_camera_command_property_categories();
  verify_camera_command_target();
  verify_camera_command_render_type();
  verify_camera_command_end_update_arguments();
  verify_camera_command_missing_name();
  return 0;
}

#undef PKG_TEST_CDECL
#undef PKG_TEST_THISCALL
#undef PKG_TEST_NOINLINE
#undef PKG_TEST_NAKED
