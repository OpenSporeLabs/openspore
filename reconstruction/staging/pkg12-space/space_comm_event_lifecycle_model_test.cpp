#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "space_comm_event_lifecycle.hpp"

namespace openspore::reconstruction::pkg12_space {
namespace {

using Event = cCommEvent;
using Manager = cCommManager;
using Vector = cCommVector;
using StringRange = cCommStringRange;
using Word = OpaqueWord;

struct RefCall {
  bool add;
  Event* event;
};

struct Allocation {
  std::size_t size;
  const char* domain;
  const char* source;
  Word value2;
};

std::vector<RefCall> ref_calls;
std::vector<Allocation> allocations;
std::vector<std::uintptr_t> allocated_pointers;
bool fail_next_allocation;
bool override_move_result;
Word move_result_override;
bool return_null_from_move;
bool return_null_from_string;
void* last_string_target;
Word last_string_begin;
Word last_string_end;

std::uint32_t read_word(const void* base, std::size_t offset) {
  std::uint32_t value = 0;
  std::memcpy(&value, static_cast<const unsigned char*>(base) + offset,
              sizeof(value));
  return value;
}

void clear_state() {
  ref_calls.clear();
  fail_next_allocation = false;
  override_move_result = false;
  move_result_override = 0;
  return_null_from_move = false;
  return_null_from_string = false;
  last_string_target = nullptr;
  last_string_begin = 0;
  last_string_end = 0;
}

Vector* vector_at(std::uint8_t* manager) {
  return reinterpret_cast<Vector*>(manager + 0x24);
}

Event* event_at(std::uintptr_t slot) {
  return *reinterpret_cast<Event**>(slot);
}

void store_event(std::uintptr_t slot, Event* event) {
  *reinterpret_cast<Event**>(slot) = event;
}

void expect_signal(void (*body)()) {
  const pid_t child = fork();
  assert(child >= 0);
  if (child == 0) {
    body();
    _exit(0);
  }
  int status = 0;
  assert(waitpid(child, &status, 0) == child);
  assert(WIFSIGNALED(status));
  assert(WTERMSIG(status) == SIGSEGV);
}

void verify_constructor() {
  Event event;
  std::memset(event.opaque, 0xa5, sizeof(event.opaque));
  pkg12_re_00aea250(&event);

  struct Expectation {
    std::size_t offset;
    std::uint32_t value;
  };
  const Expectation expectations[] = {
      {0x00, 0x0145bed8u}, {0x04, 0x0145bed4u}, {0x08, 0u},
      {0x0c, UINT32_MAX},  {0x10, 0u},          {0x14, 0u},
      {0x18, UINT32_MAX},  {0x1c, UINT32_MAX},  {0x20, 0u},
      {0x24, 0u},          {0x28, 0u},          {0x2c, 0u},
      {0x34, UINT32_MAX},  {0x38, UINT32_MAX},  {0x3c, UINT32_MAX},
      {0x40, 0u},          {0x44, UINT32_MAX},  {0x48, 0u},
      {0x4c, 0u},          {0x50, 0u},          {0x54, 0u},
      {0x58, 0u},          {0x64, 0u},          {0x68, 0u},
      {0x6c, 0u},          {0x78, 0u},          {0x7c, 0u},
      {0x80, 0u},          {0x8c, 0u},          {0x90, 0u},
      {0x94, 0u},
  };
  for (const auto& expectation : expectations) {
    assert(read_word(&event, expectation.offset) == expectation.value);
  }
  assert(event.opaque[0x30] == 0u);
  for (const std::size_t offset :
       {0x31u, 0x32u, 0x33u, 0x60u, 0x70u, 0x74u, 0x84u, 0x88u, 0x98u, 0x9cu}) {
    assert(event.opaque[offset] == 0xa5u);
  }
}

void verify_event_creation_and_append() {
  alignas(std::uintptr_t) std::uint8_t manager[0x80]{};
  Event old_event{};
  std::uintptr_t slots[3]{};
  slots[0] = reinterpret_cast<Word>(&old_event);
  Vector* vector = vector_at(manager);
  vector->begin = reinterpret_cast<Word>(slots);
  vector->end = reinterpret_cast<Word>(slots + 1);
  vector->capacity = reinterpret_cast<Word>(slots + 2);

  clear_state();
  Event payload{};
  const Word payload0 = 0x11111111u;
  const Word payload1 = 0x22222222u;
  const Word payload2 = 0x33333333u;
  const Word payload3 = 0x44444444u;
  const Word payload5 = 0x55555555u;
  const Word payload6 = 0x66666666u;
  Event* event = pkg12_re_00aeb160(
      reinterpret_cast<Manager*>(manager), payload0, payload1, payload2,
      payload3, reinterpret_cast<Word>(&payload), payload5, payload6);

  assert(event != nullptr);
  assert(read_word(event, 0x18) == payload0);
  assert(read_word(event, 0x0c) == 0u);
  assert(read_word(event, 0x34) == payload1);
  assert(read_word(event, 0x38) == payload2);
  assert(read_word(event, 0x3c) == payload3);
  assert(read_word(event, 0x40) == reinterpret_cast<Word>(&payload));
  assert(read_word(event, 0x44) == payload5);
  assert(read_word(event, 0x48) == payload6);
  assert(event_at(vector->begin) == &old_event);
  assert(event_at(vector->end - sizeof(Event*)) == event);
  assert(vector->end == vector->begin + 2 * sizeof(Event*));
  assert(ref_calls.size() == 4u);
  assert(ref_calls[0].add && ref_calls[0].event == &payload);
  assert(ref_calls[1].add && ref_calls[1].event == event);
  assert(ref_calls[2].add && ref_calls[2].event == event);
  assert(!ref_calls[3].add && ref_calls[3].event == event);
  assert(allocations.size() == 1u);
  assert(allocations[0].size == 0xa0u);
  assert(std::strcmp(allocations[0].domain, "Simulator") == 0);
  assert(allocations[0].source == nullptr);
}

void verify_insertion_and_growth() {
  Event first{};
  Event second{};
  Event inserted{};
  std::uintptr_t slots[3]{};
  slots[0] = reinterpret_cast<Word>(&first);
  slots[1] = reinterpret_cast<Word>(&second);
  Vector vector{reinterpret_cast<Word>(slots),
                reinterpret_cast<Word>(slots + 2),
                reinterpret_cast<Word>(slots + 3)};
  assert(vector.end == reinterpret_cast<Word>(slots + 2));
  assert(reinterpret_cast<Word>(slots + 1) != vector.end);
  Event* value = &inserted;
  clear_state();
  override_move_result = true;
  move_result_override = reinterpret_cast<Word>(slots + 3);
  pkg12_re_00aea5d0(&vector, reinterpret_cast<Event**>(slots + 1), &value);
  assert(event_at(reinterpret_cast<Word>(slots)) == &first);
  assert(event_at(reinterpret_cast<Word>(slots) + sizeof(Event*)) == &inserted);
  assert(event_at(reinterpret_cast<Word>(slots) + 2 * sizeof(Event*)) ==
         &second);
  assert(vector.end == vector.begin + 3 * sizeof(Event*));
  assert(ref_calls.size() == 3u);
  assert(ref_calls[0].add && ref_calls[0].event == &second);
  assert(ref_calls[1].add && ref_calls[1].event == &inserted);
  assert(!ref_calls[2].add && ref_calls[2].event == &second);

  clear_state();
  Vector empty_vector{};
  value = &inserted;
  pkg12_re_00aea5d0(&empty_vector, nullptr, &value);
  assert(empty_vector.begin != 0u);
  assert(empty_vector.end == empty_vector.begin + sizeof(Event*));
  assert(empty_vector.capacity == empty_vector.begin + sizeof(Event*));
  assert(event_at(empty_vector.begin) == &inserted);
  assert(ref_calls.size() == 1u);
  assert(ref_calls[0].add && ref_calls[0].event == &inserted);
}

void verify_beginning_insertion_regression() {
  Event first{};
  Event second{};
  Event inserted{};
  std::uintptr_t slots[4]{};
  slots[0] = reinterpret_cast<Word>(&first);
  slots[1] = reinterpret_cast<Word>(&second);
  Vector vector{reinterpret_cast<Word>(slots),
                reinterpret_cast<Word>(slots + 2),
                reinterpret_cast<Word>(slots + 4)};
  Event* value = &inserted;
  clear_state();
  override_move_result = true;
  move_result_override = reinterpret_cast<Word>(slots + 3);
  pkg12_re_00aea5d0(&vector, reinterpret_cast<Event**>(slots), &value);
  assert(event_at(reinterpret_cast<Word>(slots)) == &inserted);
  assert(event_at(reinterpret_cast<Word>(slots) + sizeof(Event*)) == &first);
  assert(event_at(reinterpret_cast<Word>(slots) + 2 * sizeof(Event*)) ==
         &second);
  assert(vector.end == reinterpret_cast<Word>(slots + 3));
}

void verify_string_assignment() {
  alignas(std::uintptr_t) std::uint8_t manager[0x80]{};
  const std::uint16_t source[] = {0x0053, 0x0070, 0x006f,
                                  0x0072, 0x0065, 0x0000};
  const StringRange range{reinterpret_cast<Word>(source),
                          reinterpret_cast<Word>(source + 5)};
  clear_state();
  void* result = pkg12_re_00aea230(reinterpret_cast<Manager*>(manager),
                                   const_cast<StringRange*>(&range));
  assert(result == manager + 0x64u);
  assert(last_string_target == manager + 0x64u);
  assert(last_string_begin == range.begin);
  assert(last_string_end == range.end);
  const std::uint16_t* target =
      reinterpret_cast<const std::uint16_t*>(manager + 0x64u);
  for (std::size_t index = 0; index < 5u; ++index) {
    assert(target[index] == source[index]);
  }

  clear_state();
  StringRange* self_range = reinterpret_cast<StringRange*>(manager + 0x64u);
  result = pkg12_re_00aea230(reinterpret_cast<Manager*>(manager), self_range);
  assert(result == self_range);
  assert(last_string_target == nullptr);
  assert(last_string_begin == 0u);
  assert(last_string_end == 0u);
}

void verify_return_boundaries() {
  Event inserted{};
  std::uintptr_t slots[4]{};
  Vector vector{reinterpret_cast<Word>(slots),
                reinterpret_cast<Word>(slots + 2),
                reinterpret_cast<Word>(slots + 4)};
  Event* value = &inserted;

  clear_state();
  override_move_result = true;
  move_result_override = reinterpret_cast<Word>(slots + 3);
  pkg12_re_00aea5d0(&vector, reinterpret_cast<Event**>(slots + 1), &value);
  assert(vector.end == reinterpret_cast<Word>(slots + 3));

  clear_state();
  vector.end = reinterpret_cast<Word>(slots + 2);
  vector.capacity = reinterpret_cast<Word>(slots + 4);
  return_null_from_move = true;
  value = &inserted;
  pkg12_re_00aea5d0(&vector, reinterpret_cast<Event**>(slots + 1), &value);
  assert(vector.end == reinterpret_cast<Word>(slots + 3));

  alignas(std::uintptr_t) std::uint8_t manager[0x80]{};
  const std::uint16_t source[] = {0x0058, 0x0000};
  const StringRange range{reinterpret_cast<Word>(source),
                          reinterpret_cast<Word>(source + 2)};
  clear_state();
  return_null_from_string = true;
  void* result = pkg12_re_00aea230(reinterpret_cast<Manager*>(manager),
                                   const_cast<StringRange*>(&range));
  assert(result == nullptr);
}

[[noreturn]] void fail_event_allocation() {
  alignas(std::uintptr_t) std::uint8_t manager[0x80]{};
  fail_next_allocation = true;
  pkg12_re_00aeb160(reinterpret_cast<Manager*>(manager), 1u, 2u, 3u, 4u, 0u, 5u,
                    6u);
  _exit(0);
}

[[noreturn]] void fail_vector_growth() {
  Event old_event{};
  std::uintptr_t slots[1]{};
  slots[0] = reinterpret_cast<Word>(&old_event);
  Vector vector{reinterpret_cast<Word>(slots),
                reinterpret_cast<Word>(slots + 1),
                reinterpret_cast<Word>(slots + 1)};
  Event value{};
  Event* inserted = &value;
  fail_next_allocation = true;
  pkg12_re_00aea5d0(&vector, reinterpret_cast<Event**>(slots + 1), &inserted);
  _exit(0);
}

[[noreturn]] void fail_string_range() {
  alignas(std::uintptr_t) std::uint8_t manager[0x80]{};
  pkg12_re_00aea230(reinterpret_cast<Manager*>(manager), nullptr);
  _exit(0);
}

}

}

namespace openspore::reconstruction::pkg12_space {

extern "C" void __thiscall pkg12_re_event_add_ref(Event* event) {
  ref_calls.push_back({true, event});
}

extern "C" void __thiscall pkg12_re_event_release(Event* event) {
  ref_calls.push_back({false, event});
}

extern "C" Word __cdecl pkg12_re_00f473a0(std::size_t size, const char* domain,
                                          Word value0, Word value1,
                                          const char* source, Word value2) {
  (void)value0;
  (void)value1;
  allocations.push_back({size, domain, source, value2});
  if (fail_next_allocation) {
    fail_next_allocation = false;
    return 0u;
  }
  void* pointer = std::malloc(size);
  if (pointer != nullptr) {
    allocated_pointers.push_back(reinterpret_cast<Word>(pointer));
  }
  return reinterpret_cast<Word>(pointer);
}

extern "C" void __cdecl pkg12_re_00f47380(Word pointer) {
  for (std::size_t index = 0; index < allocated_pointers.size(); ++index) {
    if (allocated_pointers[index] == pointer) {
      allocated_pointers[index] = allocated_pointers.back();
      allocated_pointers.pop_back();
      break;
    }
  }
  std::free(reinterpret_cast<void*>(pointer));
}

extern "C" Event** __cdecl pkg12_re_00ac97a0(Event** position, Event** source,
                                             Event** end) {
  if (source == position) {
    if (return_null_from_move) {
      return nullptr;
    }
    if (override_move_result) {
      return reinterpret_cast<Event**>(move_result_override);
    }
    return reinterpret_cast<Event**>(reinterpret_cast<Word>(end));
  }
  Word source_word = reinterpret_cast<Word>(source);
  Word end_word = reinterpret_cast<Word>(end);
  const Word position_word = reinterpret_cast<Word>(position);
  while (source_word != position_word) {
    Event* source_previous = event_at(source_word - sizeof(Event*));
    Event* destination_previous = event_at(end_word - sizeof(Event*));
    source_word -= sizeof(Event*);
    end_word -= sizeof(Event*);
    if (source_previous != destination_previous) {
      pkg12_re_event_add_ref(source_previous);
      store_event(end_word, source_previous);
      pkg12_re_event_release(destination_previous);
    }
  }
  if (return_null_from_move) {
    return nullptr;
  }
  if (override_move_result) {
    return reinterpret_cast<Event**>(move_result_override);
  }
  return reinterpret_cast<Event**>(end_word);
}

extern "C" void* __cdecl pkg12_re_011e0744(void* destination,
                                           const void* source,
                                           std::size_t size) {
  if (size == 0u) {
    return destination;
  }
  return std::memcpy(destination, source, size);
}

extern "C" void* __thiscall pkg12_re_00454cb0(void* target, Word begin,
                                              Word end) {
  last_string_target = target;
  last_string_begin = begin;
  last_string_end = end;
  if (return_null_from_string) {
    return nullptr;
  }
  std::memcpy(target, reinterpret_cast<const void*>(begin),
              static_cast<std::size_t>(end - begin));
  return target;
}

}

using namespace openspore::reconstruction::pkg12_space;

int main() {
  verify_constructor();
  verify_event_creation_and_append();
  verify_insertion_and_growth();
  verify_beginning_insertion_regression();
  verify_string_assignment();
  verify_return_boundaries();
  expect_signal(fail_event_allocation);
  expect_signal(fail_vector_growth);
  expect_signal(fail_string_range);

  for (const Word pointer : allocated_pointers) {
    std::free(reinterpret_cast<void*>(pointer));
  }
  allocated_pointers.clear();
}
