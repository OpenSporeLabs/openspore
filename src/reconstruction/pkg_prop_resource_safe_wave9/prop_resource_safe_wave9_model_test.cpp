#include <sys/wait.h>
#include <unistd.h>

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "prop_resource_safe_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_PROP_SAFE_TEST_CDECL __cdecl
#define PKG_PROP_SAFE_TEST_THISCALL __thiscall
#else
#define PKG_PROP_SAFE_TEST_CDECL __attribute__((cdecl))
#define PKG_PROP_SAFE_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_safe_wave9 {
namespace {

using SetDevModeSignature =
    void(PKG_PROP_SAFE_TEST_THISCALL*)(OpaquePropManager*, std::uint8_t);
using FlushSignature = std::uint8_t(PKG_PROP_SAFE_TEST_THISCALL*)(OpaqueStream*,
                                                                  const void*,
                                                                  Word);
using GetAccessFlagsSlot = Word(PKG_PROP_SAFE_TEST_THISCALL*)(OpaqueStream*);
using WriteSlot = std::int32_t(PKG_PROP_SAFE_TEST_THISCALL*)(OpaqueStream*,
                                                             const void*,
                                                             std::size_t);

static_assert(
    std::is_same<decltype(&prop_manager_set_dev_mode_006a3300),
                 SetDevModeSignature>::value,
    "006a3300 takes this plus one explicit stack byte popped by RET 4");
static_assert(
    std::is_same<decltype(&record_write_flush_006c0550), FlushSignature>::value,
    "006c0550 takes this plus two explicit stack words popped by RET 8");
static_assert(
    std::is_same<decltype(OpaqueStreamVtablePort::get_access_flags_10),
                 GetAccessFlagsSlot>::value,
    "the +0x10 port takes this only and yields a full word");
static_assert(
    std::is_same<decltype(OpaqueStreamVtablePort::write_38), WriteSlot>::value,
    "the +0x38 port takes this plus two stack words and returns int32");
static_assert(
    sizeof(std::uint8_t) == 1 && sizeof(std::size_t) == 4,
    "the dev mode slot is one byte and the port size argument is one word");
static_assert(sizeof(OpaquePropManager) == 0x1ec &&
                  offsetof(OpaquePropManager, initialized_14) == 0x14 &&
                  offsetof(OpaquePropManager, dev_mode_15) == 0x15,
              "the prop manager carries its dev mode byte at +0x15");
static_assert(offsetof(OpaqueRecordWrite, file_access_1c) == 0x1c &&
                  offsetof(OpaqueRecordWrite, stream_vtable_20) == 0x20 &&
                  offsetof(OpaqueRecordWrite, memory_stream_24) == 0x24 &&
                  offsetof(OpaqueRecordWrite, file_stream_48) == 0x48,
              "the flush receiver is the record stream subobject at +0x20");
static_assert(sizeof(OpaqueStreamVtablePort) == 0x3c &&
                  offsetof(OpaqueStreamVtablePort, get_access_flags_10) ==
                      0x10 &&
                  offsetof(OpaqueStreamVtablePort, write_38) == 0x38,
              "the access and write ports keep their vtable slots");

std::vector<std::string> events;

void check(bool condition) {
  if (condition) {
    return;
  }
  std::fputs("check failed", stderr);
  for (const std::string& event : events) {
    std::fprintf(stderr, " %s", event.c_str());
  }
  std::fputc('\n', stderr);
  std::abort();
}

void expect(std::initializer_list<const char*> expected) {
  check(events.size() == expected.size());
  std::size_t index = 0;
  for (const char* value : expected) {
    check(events[index] == value);
    ++index;
  }
}

void poison(void* target, std::size_t size, std::uint8_t value) {
  std::memset(target, value, size);
}

struct PortState {
  Word access_flags = 0;
  std::int32_t write_result = 0;
  const void* write_data = nullptr;
  std::size_t write_size = 0;
  std::uint32_t access_calls = 0;
  std::uint32_t file_write_calls = 0;
  std::uint32_t memory_write_calls = 0;
  OpaqueStream* expected_file = nullptr;
  OpaqueStream* expected_memory = nullptr;
};

PortState state;
OpaqueStreamVtablePort file_vtable{};
OpaqueStreamVtablePort memory_vtable{};
OpaqueRecordWrite record{};

Word PKG_PROP_SAFE_TEST_THISCALL get_access_flags(OpaqueStream* stream) {
  events.emplace_back("access");
  check(stream == state.expected_file);
  ++state.access_calls;
  return state.access_flags;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_file(OpaqueStream* stream,
                                                    const void* data,
                                                    std::size_t size) {
  events.emplace_back("file-write");
  check(stream == state.expected_file);
  state.write_data = data;
  state.write_size = size;
  ++state.file_write_calls;
  return state.write_result;
}

std::int32_t PKG_PROP_SAFE_TEST_THISCALL write_memory(OpaqueStream* stream,
                                                      const void* data,
                                                      std::size_t size) {
  events.emplace_back("memory-write");
  check(stream == state.expected_memory);
  state.write_data = data;
  state.write_size = size;
  ++state.memory_write_calls;
  return state.write_result;
}

void reset_record(Word file_access) {
  events.clear();
  file_vtable = OpaqueStreamVtablePort{};
  memory_vtable = OpaqueStreamVtablePort{};
  file_vtable.get_access_flags_10 = get_access_flags;
  file_vtable.write_38 = write_file;
  memory_vtable.get_access_flags_10 = get_access_flags;
  memory_vtable.write_38 = write_memory;
  poison(&record, sizeof(record), 0x00);
  record.file_access_1c = file_access;
  stream_publish_ports(&record, StreamPorts{&memory_vtable, &file_vtable});
  state = PortState{};
  state.expected_file = &record.file_stream_48;
  state.expected_memory = &record.memory_stream_24;
}

void test_set_dev_mode_stores_single_byte() {
  OpaquePropManager manager{};
  poison(&manager, sizeof(manager), 0xee);
  int vtable_sentinel = 0;
  manager.vtable_00 = &vtable_sentinel;
  manager.initialized_14 = 0x11;

  prop_manager_set_dev_mode_006a3300(&manager, 0x5c);
  check(manager.dev_mode_15 == 0x5c);
  check(manager.initialized_14 == 0x11);
  check(manager.body_04_13[sizeof(manager.body_04_13) - 1] == 0xee);
  check(manager.body_16_1eb[0] == 0xee);
  check(manager.vtable_00 == &vtable_sentinel);
  check(reinterpret_cast<const std::uint8_t*>(&manager)[0x15] == 0x5c);
  check(reinterpret_cast<const std::uint8_t*>(&manager)[0x14] == 0x11);

  prop_manager_set_dev_mode_006a3300(&manager, 0xff);
  check(manager.dev_mode_15 == 0xff);
  prop_manager_set_dev_mode_006a3300(&manager, 0x00);
  check(manager.dev_mode_15 == 0x00);
  prop_manager_set_dev_mode_006a3300(&manager, 0x01);
  check(manager.dev_mode_15 == 0x01);
  check(manager.initialized_14 == 0x11);
  check(reinterpret_cast<const std::uint8_t*>(&manager)[0x15] == 0x01);
}

void test_flush_zero_gate_consults_nothing() {
  reset_record(0);
  state.access_flags = 0xffffffffu;
  state.write_result = 0xff;
  check(record_write_flush_006c0550(record_write_stream(&record), nullptr,
                                    0x40) == 0);
  check(events.empty());
  check(state.access_calls == 0);
  check(state.file_write_calls == 0);
  check(state.memory_write_calls == 0);
}

void test_flush_gate_is_a_full_word() {
  reset_record(0x00000100u);
  std::uint8_t payload[] = {1};
  state.access_flags = 0xffffffffu;
  state.write_result = 1;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 1) ==
        1);
  expect({"access", "file-write"});

  reset_record(0x01000000u);
  events.clear();
  state.access_flags = 0;
  state.write_result = 1;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 1) ==
        1);
  expect({"access", "memory-write"});
}

void test_flush_gate_reads_only_plus_0x1c() {
  reset_record(1);
  record.type_08 = 0xffffffffu;
  record.parent_18 = &state;
  record.stream_vtable_20 = nullptr;
  std::uint8_t payload[] = {1, 2, 3};
  state.access_flags = 0x00000002u;
  state.write_result = 3;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 3) ==
        3);
  expect({"access", "file-write"});
  check(state.file_write_calls == 1);
  check(state.write_data == payload);
  check(state.write_size == 3);
}

void test_flush_file_path() {
  reset_record(7);
  std::uint8_t payload[] = {9, 8, 7, 6, 5};
  state.access_flags = 0xffffffffu;
  state.write_result = 0x000000c3;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 5) ==
        0xc3);
  expect({"access", "file-write"});
  check(state.write_data == payload);
  check(state.write_size == 5);
  check(state.access_calls == 1);
  check(state.file_write_calls == 1);
  check(state.memory_write_calls == 0);
}

void test_flush_memory_path() {
  reset_record(7);
  std::uint8_t payload[] = {0xa0};
  state.access_flags = 0;
  state.write_result = 0x00000007;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 1) ==
        7);
  expect({"access", "memory-write"});
  check(state.write_data == payload);
  check(state.write_size == 1);
  check(state.file_write_calls == 0);
  check(state.memory_write_calls == 1);
}

void test_flush_low_byte_result() {
  struct Case {
    std::int32_t port_result;
    std::uint8_t expected;
  };
  const Case cases[] = {
      {0, 0x00},     {1, 0x01},      {0x7f, 0x7f},       {0xff, 0xff},
      {0x100, 0x00}, {0x1234, 0x34}, {0x00ff00, 0x00},   {0x00000101, 0x01},
      {-1, 0xff},    {-256, 0x00},   {0x0000ffff, 0xff},
  };
  std::uint8_t payload[] = {0x5a, 0xa5};
  reset_record(1);
  OpaqueStream* const receiver = record_write_stream(&record);
  for (const Case& item : cases) {
    state.access_flags = 0xffffffffu;
    state.write_result = item.port_result;
    check(record_write_flush_006c0550(receiver, payload, 2) == item.expected);

    state.access_flags = 0;
    state.write_result = item.port_result;
    check(record_write_flush_006c0550(receiver, payload, 2) == item.expected);
  }
  check(state.access_calls == 2 * (sizeof(cases) / sizeof(cases[0])));
  check(state.file_write_calls == sizeof(cases) / sizeof(cases[0]));
  check(state.memory_write_calls == sizeof(cases) / sizeof(cases[0]));
}

std::uint32_t stack_probe_result = 0;

void test_flush_leaves_record_untouched() {
  std::uint8_t payload[] = {0x31, 0x32};
  reset_record(0x0f);
  for (std::size_t index = 0; index < sizeof(record.name_key_0c); ++index) {
    record.name_key_0c[index] = static_cast<std::uint8_t>(0xa0 + index);
  }
  for (std::size_t index = 0; index < sizeof(record.memory_body_28_47);
       ++index) {
    record.memory_body_28_47[index] = 0x33;
  }
  for (std::size_t index = 0; index < sizeof(record.file_body_4c_27b);
       ++index) {
    record.file_body_4c_27b[index] = 0x44;
  }
  OpaqueRecordWrite before = record;
  state.write_result = 0x5a;

  state.access_flags = 0xffffffffu;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 2) ==
        0x5a);
  state.access_flags = 0;
  check(record_write_flush_006c0550(record_write_stream(&record), payload, 2) ==
        0x5a);
  check(std::memcmp(&record, &before, sizeof(record)) == 0);
  expect({"access", "file-write", "access", "memory-write"});
}

void PKG_PROP_SAFE_TEST_CDECL flush_stack_probe(OpaqueStream* receiver,
                                                const void* data, Word size,
                                                Word guard_low,
                                                Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const FlushSignature flush = &record_write_flush_006c0550;
  flush(receiver, data, size);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  stack_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_flush_stack_discipline() {
  reset_record(1);
  std::uint8_t payload[] = {0x11, 0x22, 0x33, 0x44};
  state.access_flags = 0xffffffffu;
  state.write_result = 0x2a;
  flush_stack_probe(record_write_stream(&record), payload, 4, 0x11223344u,
                    0x55667788u);
  check(stack_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"access", "file-write"});
  check(state.write_data == payload);
  check(state.write_size == 4);
}

void test_flush_null_file_vtable_faults() {
  reset_record(1);
  record.file_stream_48.vtable = nullptr;
  state.access_flags = 0;
  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(
        record_write_flush_006c0550(record_write_stream(&record), nullptr, 0));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

void test_flush_null_memory_vtable_faults() {
  reset_record(1);
  record.memory_stream_24.vtable = nullptr;
  state.access_flags = 0;
  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(
        record_write_flush_006c0550(record_write_stream(&record), nullptr, 0));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_prop_resource_safe_wave9;
  test_set_dev_mode_stores_single_byte();
  test_flush_zero_gate_consults_nothing();
  test_flush_gate_is_a_full_word();
  test_flush_gate_reads_only_plus_0x1c();
  test_flush_file_path();
  test_flush_memory_path();
  test_flush_low_byte_result();
  test_flush_leaves_record_untouched();
  test_flush_stack_discipline();
  test_flush_null_file_vtable_faults();
  test_flush_null_memory_vtable_faults();
  return 0;
}

#undef PKG_PROP_SAFE_TEST_CDECL
#undef PKG_PROP_SAFE_TEST_THISCALL
