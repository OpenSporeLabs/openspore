#include <cassert>
#include <cstddef>
#include <cstdint>

#include "space_comm_event.hpp"

namespace openspore::reconstruction::pkg12_space {

struct cCommEvent {
  std::uint32_t marker;
};

struct cCommManager {
  std::uint32_t marker;
};

}

namespace {

using Event = openspore::reconstruction::pkg12_space::cCommEvent;
using Manager = openspore::reconstruction::pkg12_space::cCommManager;
using Payload = openspore::reconstruction::pkg12_space::OpaquePayloadWord;

std::size_t call_count;
Manager* expected_manager;
Event* create_result;
Manager* create_manager;
Event* dispatch_event;
Manager* dispatch_manager;
Payload forwarded[7];

void reset(Manager* manager, Event* result) {
  call_count = 0;
  expected_manager = manager;
  create_result = result;
  create_manager = nullptr;
  dispatch_event = nullptr;
  dispatch_manager = nullptr;
  for (auto& value : forwarded) {
    value = 0;
  }
}

}

extern "C" Event* __thiscall pkg12_re_00aeb160(
    Manager* manager, Payload payload0, Payload payload1, Payload payload2,
    Payload payload3, Payload payload4, Payload payload5,
    std::uint32_t duration) {
  assert(call_count == 0);
  assert(manager == expected_manager);
  create_manager = manager;
  forwarded[0] = payload0;
  forwarded[1] = payload1;
  forwarded[2] = payload2;
  forwarded[3] = payload3;
  forwarded[4] = payload4;
  forwarded[5] = payload5;
  forwarded[6] = duration;
  ++call_count;
  return create_result;
}

extern "C" void __thiscall pkg12_re_00aebe90(Manager* manager, Event* event) {
  assert(call_count == 1);
  assert(manager == expected_manager);
  dispatch_manager = manager;
  dispatch_event = event;
  ++call_count;
}

namespace {

void verify_success() {
  Manager manager{0x13572468u};
  Event event{0x24681357u};
  const Payload payload[6] = {UINT32_C(0x00c0ffee), 0u,
                              UINT32_MAX,           UINT32_C(0xc8fbf7d7),
                              UINT32_C(0x80000000), 0u};
  reset(&manager, &event);

  openspore::reconstruction::pkg12_space::pkg12_space_comm_event_00aeb720(
      &manager, payload[0], payload[1], payload[2], payload[3], payload[4],
      payload[5]);

  assert(call_count == 2);
  assert(create_manager == &manager);
  for (std::size_t index = 0; index < 6; ++index) {
    assert(forwarded[index] == payload[index]);
  }
  assert(forwarded[6] == 0);
  assert(dispatch_manager == &manager);
  assert(dispatch_event == &event);
}

void verify_null_result() {
  Manager manager{1u};
  const Payload payload[6] = {1u, 2u, 3u, 4u, 5u, 6u};
  reset(&manager, nullptr);

  openspore::reconstruction::pkg12_space::pkg12_space_comm_event_00aeb720(
      &manager, payload[0], payload[1], payload[2], payload[3], payload[4],
      payload[5]);

  assert(call_count == 2);
  assert(create_manager == &manager);
  assert(dispatch_manager == &manager);
  assert(dispatch_event == nullptr);
}

void verify_null_manager() {
  Event event{7u};
  const Payload payload[6] = {8u, 9u, 10u, 11u, 12u, 13u};
  reset(nullptr, &event);

  openspore::reconstruction::pkg12_space::pkg12_space_comm_event_00aeb720(
      nullptr, payload[0], payload[1], payload[2], payload[3], payload[4],
      payload[5]);

  assert(call_count == 2);
  assert(create_manager == nullptr);
  assert(dispatch_manager == nullptr);
  assert(dispatch_event == &event);
}

}

int main() {
  verify_success();
  verify_null_result();
  verify_null_manager();
}
