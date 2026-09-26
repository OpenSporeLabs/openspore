#include <cstdint>
#include <type_traits>

#include "cheat_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_CHEAT_WAVE9_THISCALL __thiscall
#define PKG_CHEAT_WAVE9_CDECL __cdecl
#elif defined(__GNUC__) || defined(__clang__)
#define PKG_CHEAT_WAVE9_THISCALL __attribute__((thiscall))
#define PKG_CHEAT_WAVE9_CDECL __attribute__((cdecl))
#else
#error "pkg-cheat-wave9 requires an MSVC or GCC calling convention"
#endif

namespace openspore::reconstruction::pkg_cheat_wave9 {
namespace {

int failures = 0;
unsigned int port_calls = 0;
unsigned int operation_calls = 0;
unsigned int wrong_slot_calls = 0;
OpaqueService* port_service = nullptr;
bool operation_result = false;
std::uint8_t manager_mutation = 0;

struct ObservedCall {
  OpaqueService* receiver;
  OpaqueWord stack_00;
  OpaqueManager* stack_04;
  OpaqueWord stack_08;
  OpaqueWord stack_0c;
};

ObservedCall observed{};
ObservedCall observed_through_manager_slot{};

OpaqueWord word_of(const void* pointer) {
  return static_cast<OpaqueWord>(reinterpret_cast<std::uintptr_t>(pointer));
}

void check(bool condition) {
  if (!condition) {
    ++failures;
  }
}

bool PKG_CHEAT_WAVE9_THISCALL operation_24(OpaqueService* receiver,
                                           OpaqueWord stack_00,
                                           OpaqueManager* stack_04,
                                           OpaqueWord stack_08,
                                           OpaqueWord stack_0c) {
  observed.receiver = receiver;
  observed.stack_00 = stack_00;
  observed.stack_04 = stack_04;
  observed.stack_08 = stack_08;
  observed.stack_0c = stack_0c;
  ++operation_calls;
  if (stack_04 != nullptr) {
    stack_04->opaque_04[0] = manager_mutation;
  }
  return operation_result;
}

bool PKG_CHEAT_WAVE9_THISCALL wrong_slot(OpaqueService*, OpaqueWord,
                                         OpaqueManager*, OpaqueWord,
                                         OpaqueWord) {
  ++wrong_slot_calls;
  return false;
}

OpaqueService* PKG_CHEAT_WAVE9_CDECL service_get_00b3d260() {
  ++port_calls;
  return port_service;
}

struct OpaqueFixture {
  OpaqueManager manager{};
  OpaqueManagerVtable manager_vtable{};
  OpaqueService service{};
  OpaqueService alt_service{};
  OpaqueServiceVtable service_vtable{};
  OpaqueServiceVtable alt_service_vtable{};
  std::uint32_t scratch_first = 0;
  std::uint32_t scratch_second = 0;
  std::uint32_t scratch_third = 0;
};

void initialize(OpaqueFixture& fixture) {
  port_calls = 0u;
  operation_calls = 0u;
  wrong_slot_calls = 0u;
  port_service = nullptr;
  operation_result = false;
  manager_mutation = 0u;
  observed = ObservedCall{};
  observed_through_manager_slot = ObservedCall{};

  fixture.manager_vtable = OpaqueManagerVtable{};
  fixture.manager_vtable.slots_00[0] =
      reinterpret_cast<std::uintptr_t>(&fixture.service);
  fixture.manager_vtable.slots_00[8] = 0x01234567u;
  fixture.manager_vtable.forward_48 = &opaque_service_forward_00abf790;
  fixture.manager = OpaqueManager{};
  fixture.manager.vtable = &fixture.manager_vtable;

  fixture.service_vtable = OpaqueServiceVtable{};
  fixture.service_vtable.slots_00[0] =
      reinterpret_cast<std::uintptr_t>(&fixture.service);
  fixture.service_vtable.slots_00[1] = 0x89abcdefu;
  fixture.service_vtable.slots_00[2] = 0xfedcba98u;
  fixture.service_vtable.slots_00[3] = 0x80000000u;
  fixture.service_vtable.slots_00[4] = 0x7fffffffu;
  fixture.service_vtable.slots_00[5] = 0u;
  fixture.service_vtable.slots_00[6] = 0xffffffffu;
  fixture.service_vtable.slots_00[7] = 0x00c0ffeeu;
  fixture.service_vtable.slots_00[8] =
      reinterpret_cast<std::uintptr_t>(wrong_slot);
  fixture.service_vtable.operation_24 = operation_24;
  fixture.service = OpaqueService{};
  fixture.service.vtable = &fixture.service_vtable;

  fixture.alt_service_vtable = OpaqueServiceVtable{};
  fixture.alt_service_vtable.operation_24 = operation_24;
  fixture.alt_service = OpaqueService{};
  fixture.alt_service.vtable = &fixture.alt_service_vtable;

  fixture.scratch_first = 0x11111111u;
  fixture.scratch_second = 0x22222222u;
  fixture.scratch_third = 0x33333333u;

  port_service = &fixture.service;
  g_cheat_wave9_ports = OpaquePorts{};
  g_cheat_wave9_ports.service_get_00b3d260 = service_get_00b3d260;
}

void test_receiver_is_fetched_service_and_stack_order() {
  OpaqueFixture fixture{};
  initialize(fixture);
  operation_result = true;
  manager_mutation = 0xa7u;

  const bool result = opaque_service_forward_00abf790(
      &fixture.manager, fixture.scratch_first, fixture.scratch_second,
      fixture.scratch_third);

  check(result);
  check(port_calls == 1u);
  check(operation_calls == 1u);
  check(wrong_slot_calls == 0u);
  check(observed.receiver == &fixture.service);
  check(observed.stack_00 == fixture.scratch_first);
  check(observed.stack_04 == &fixture.manager);
  check(observed.stack_08 == fixture.scratch_second);
  check(observed.stack_0c == fixture.scratch_third);
  check(word_of(observed.stack_04) != word_of(observed.receiver));
  check(fixture.manager.opaque_04[0] == 0xa7u);
  check(fixture.service.vtable == &fixture.service_vtable);
}

void test_receiver_is_not_reused_as_a_stack_word() {
  OpaqueFixture fixture{};
  initialize(fixture);
  operation_result = true;
  manager_mutation = 0x11u;

  const OpaqueWord first = word_of(&fixture.scratch_first);
  const OpaqueWord second = word_of(&fixture.scratch_second);
  const OpaqueWord third = word_of(&fixture.scratch_third);

  const bool result =
      opaque_service_forward_00abf790(&fixture.manager, first, second, third);

  check(result);
  check(port_calls == 1u);
  check(operation_calls == 1u);
  check(observed.receiver == &fixture.service);
  check(observed.stack_00 == first);
  check(observed.stack_04 == &fixture.manager);
  check(observed.stack_08 == second);
  check(observed.stack_0c == third);
  check(observed.stack_00 != observed.stack_08);
  check(observed.stack_00 != observed.stack_0c);
  check(observed.stack_08 != observed.stack_0c);
  check(word_of(observed.receiver) != observed.stack_00);
  check(word_of(observed.receiver) != word_of(observed.stack_04));
  check(word_of(observed.receiver) != observed.stack_08);
  check(word_of(observed.receiver) != observed.stack_0c);
  check(fixture.manager.opaque_04[0] == 0x11u);
}

void test_null_manager_reaches_the_stack_in_second_position() {
  OpaqueFixture fixture{};
  initialize(fixture);
  operation_result = false;
  manager_mutation = 0x5cu;

  const bool result =
      opaque_service_forward_00abf790(nullptr, 0x80000000u, 0u, 0xffffffffu);

  check(!result);
  check(port_calls == 1u);
  check(operation_calls == 1u);
  check(observed.receiver == &fixture.service);
  check(observed.stack_00 == 0x80000000u);
  check(observed.stack_04 == nullptr);
  check(observed.stack_08 == 0u);
  check(observed.stack_0c == 0xffffffffu);
}

void test_port_gate_selects_the_receiver() {
  OpaqueFixture fixture{};
  initialize(fixture);
  operation_result = true;

  port_service = &fixture.alt_service;
  const bool alt_result =
      opaque_service_forward_00abf790(&fixture.manager, 1u, 2u, 3u);

  check(alt_result);
  check(port_calls == 1u);
  check(operation_calls == 1u);
  check(observed.receiver == &fixture.alt_service);
  check(observed.receiver != &fixture.service);
  check(observed.stack_00 == 1u);
  check(observed.stack_04 == &fixture.manager);
  check(observed.stack_08 == 2u);
  check(observed.stack_0c == 3u);

  port_service = &fixture.service;
  const bool service_result =
      opaque_service_forward_00abf790(&fixture.manager, 4u, 5u, 6u);

  check(service_result);
  check(port_calls == 2u);
  check(operation_calls == 2u);
  check(observed.receiver == &fixture.service);
  check(observed.stack_00 == 4u);
  check(observed.stack_04 == &fixture.manager);
  check(observed.stack_08 == 5u);
  check(observed.stack_0c == 6u);
}

void test_port_gate_is_closed_by_default() {
  OpaquePorts ports{};
  static_assert(std::is_same<decltype(&service_get_00b3d260),
                             OpaqueService*(PKG_CHEAT_WAVE9_CDECL*)()>::value,
                "port stub takes no service word");
  check(ports.service_get_00b3d260 == nullptr);
  check(sizeof(OpaquePorts) == 4);
}

void test_manager_forward_slot_dispatch() {
  OpaqueFixture fixture{};
  initialize(fixture);
  operation_result = true;
  manager_mutation = 0x3du;

  OpaqueManager* const manager = &fixture.manager;
  const OpaqueWord first = word_of(&fixture.scratch_first);
  const OpaqueWord second = word_of(&fixture.scratch_second);
  const OpaqueWord third = word_of(&fixture.scratch_third);

  const bool result =
      manager->vtable->forward_48(manager, first, second, third);

  check(result);
  check(port_calls == 1u);
  check(operation_calls == 1u);
  check(wrong_slot_calls == 0u);
  check(observed.receiver == &fixture.service);
  check(observed.stack_00 == first);
  check(observed.stack_04 == manager);
  check(observed.stack_08 == second);
  check(observed.stack_0c == third);
  check(observed_through_manager_slot.receiver == nullptr);
  check(fixture.manager.opaque_04[0] == 0x3du);
}

void test_modeled_signatures() {
  using ForwardSignature = bool(PKG_CHEAT_WAVE9_THISCALL*)(
      OpaqueManager*, OpaqueWord, OpaqueWord, OpaqueWord);
  using ServiceSignature = bool(PKG_CHEAT_WAVE9_THISCALL*)(
      OpaqueService*, OpaqueWord, OpaqueManager*, OpaqueWord, OpaqueWord);
  using PortSignature = OpaqueService*(PKG_CHEAT_WAVE9_CDECL*)();

  static_assert(std::is_same<decltype(&opaque_service_forward_00abf790),
                             ForwardSignature>::value,
                "forward is thiscall with three stack words");
  static_assert(std::is_same<CheatManagerForward48, ForwardSignature>::value,
                "manager slot matches the forward signature");
  static_assert(std::is_same<ServiceOperation24, ServiceSignature>::value,
                "service slot takes the receiver plus first, manager, second, "
                "third");
  static_assert(std::is_same<OpaqueServiceGet00b3d260, PortSignature>::value,
                "port is a cdecl zero-argument accessor");
  static_assert(sizeof(decltype(&opaque_service_forward_00abf790)) == 4,
                "forward width");
}

int run_model() {
  failures = 0;
  test_receiver_is_fetched_service_and_stack_order();
  test_receiver_is_not_reused_as_a_stack_word();
  test_null_manager_reaches_the_stack_in_second_position();
  test_port_gate_selects_the_receiver();
  test_port_gate_is_closed_by_default();
  test_manager_forward_slot_dispatch();
  test_modeled_signatures();
  return failures == 0 ? 0 : 1;
}

}

}

int main() { return openspore::reconstruction::pkg_cheat_wave9::run_model(); }

#undef PKG_CHEAT_WAVE9_CDECL
#undef PKG_CHEAT_WAVE9_THISCALL
