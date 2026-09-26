#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <string>
#include <type_traits>
#include <vector>

#include "prop_resource_wave9.hpp"

#if defined(_MSC_VER)
#define PKG_PROP_TEST_CDECL __cdecl
#define PKG_PROP_TEST_THISCALL __thiscall
#else
#define PKG_PROP_TEST_CDECL __attribute__((cdecl))
#define PKG_PROP_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_prop_resource_wave9 {
namespace {

std::vector<std::string> events;

using ConstructSignature =
    OpaqueResource*(PKG_PROP_TEST_THISCALL*)(OpaqueResource*, Word);
using FlushSignature = bool(PKG_PROP_TEST_THISCALL*)(OpaqueStream*, const void*,
                                                     Word);
using CreateSignature = bool(PKG_PROP_TEST_THISCALL*)(OpaqueManager*,
                                                      OpaqueRecord*,
                                                      OpaqueResource**, Word,
                                                      Word);
using DispatchSlot = std::uint8_t(PKG_PROP_TEST_THISCALL*)(OpaqueManager*,
                                                           OpaqueRecord*,
                                                           OpaqueResource*,
                                                           Word, Word);
using WriteSlot = std::int32_t(PKG_PROP_TEST_THISCALL*)(OpaqueStream*,
                                                        const void*,
                                                        std::size_t);

static_assert(
    std::is_same<decltype(&resource_construct_006a1b90),
                 ConstructSignature>::value,
    "006a1b90 takes this plus one explicit stack word popped by RET 4");
static_assert(
    std::is_same<decltype(&record_write_flush_006c0550), FlushSignature>::value,
    "006c0550 takes this plus two explicit stack words popped by RET 8");
static_assert(
    std::is_same<decltype(&prop_manager_create_resource_006a3330),
                 CreateSignature>::value,
    "006a3330 takes this plus four explicit stack words popped by RET 0x10");
static_assert(
    std::is_same<decltype(OpaqueManagerVtable::dispatch_24),
                 DispatchSlot>::value,
    "006a3330 dispatches through the +0x24 slot with four explicit words");
static_assert(
    std::is_same<decltype(OpaqueStreamVtable::write_38), WriteSlot>::value,
    "the 0x38 slot returns a 32-bit int, so 006c0550 keeps its low byte");
static_assert(
    sizeof(OpaqueManagerVtable) == 0x28,
    "manager vtable prefix covers slots 0x00-0x23 with dispatch at 0x24");
static_assert(
    sizeof(OpaqueManager) == 0x1ec && offsetof(OpaqueManager, vtable) == 0x00 &&
        offsetof(OpaqueManager, dev_mode_15) == 0x15,
    "manager carries its vtable pointer at +0x00 and the dev mode byte "
    "at +0x15");
static_assert(
    sizeof(decltype(OpaqueResource::cleared_30)) == 4 &&
        sizeof(decltype(OpaqueResource::cleared_34)) == 4,
    "006a1b90 clears dword fields at +0x30 and +0x34, not single bytes");
static_assert(offsetof(OpaqueResource, cleared_30) == 0x30 &&
                  offsetof(OpaqueResource, cleared_34) == 0x34,
              "the two cleared dwords sit at +0x30 and +0x34");

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

OpaqueResourceKey key{};
OpaqueResource* allocation_result = nullptr;
std::size_t allocation_size = 0;
const char* allocation_arg2 = nullptr;
void* allocation_arg3 = nullptr;
void* allocation_arg4 = nullptr;
void* allocation_arg5 = nullptr;
void* allocation_arg6 = nullptr;
std::size_t allocation_arg_slots[6] = {0, 0, 0, 0, 0, 0};
OpaqueResourceVtable resource_vtable{};
OpaqueResource** destination_slot = nullptr;
bool destination_published_before_retain = false;
std::uint8_t dispatch_result = 0;
std::uint8_t destroy_deleting_flag = 0xff;
std::uint32_t retain_calls = 0;
std::uint32_t destroy_calls = 0;
std::uint32_t dispatch_calls = 0;
OpaqueManager* dispatch_manager_arg = nullptr;
OpaqueRecord* dispatch_record_arg = nullptr;
OpaqueResource* dispatch_resource_arg = nullptr;
Word dispatch_key_word_arg = 0;
Word dispatch_type_id_arg = 0;
bool dispatch_saw_constructed_resource = false;

OpaqueResource* PKG_PROP_TEST_CDECL allocate_resource(std::size_t size,
                                                      const char* arg2,
                                                      void* arg3, void* arg4,
                                                      void* arg5, void* arg6) {
  events.emplace_back("allocate");
  allocation_size = size;
  allocation_arg2 = arg2;
  allocation_arg3 = arg3;
  allocation_arg4 = arg4;
  allocation_arg5 = arg5;
  allocation_arg6 = arg6;
  allocation_arg_slots[0] = size;
  allocation_arg_slots[1] = reinterpret_cast<std::uintptr_t>(arg2);
  allocation_arg_slots[2] = reinterpret_cast<std::uintptr_t>(arg3);
  allocation_arg_slots[3] = reinterpret_cast<std::uintptr_t>(arg4);
  allocation_arg_slots[4] = reinterpret_cast<std::uintptr_t>(arg5);
  allocation_arg_slots[5] = reinterpret_cast<std::uintptr_t>(arg6);
  return allocation_result;
}

const OpaqueResourceKey* PKG_PROP_TEST_THISCALL
get_record_key(OpaqueRecord* record) {
  static_cast<void>(record);
  events.emplace_back("record-key");
  return &key;
}

std::uint8_t PKG_PROP_TEST_THISCALL dispatch_manager(OpaqueManager* manager,
                                                     OpaqueRecord* record,
                                                     OpaqueResource* resource,
                                                     Word key_word,
                                                     Word type_id) {
  events.emplace_back("dispatch");
  dispatch_manager_arg = manager;
  dispatch_record_arg = record;
  dispatch_resource_arg = resource;
  dispatch_key_word_arg = key_word;
  dispatch_type_id_arg = type_id;
  dispatch_saw_constructed_resource =
      resource->vtable == &resource_vtable && resource->reference_count == 0;
  ++dispatch_calls;
  return dispatch_result;
}

std::int32_t PKG_PROP_TEST_THISCALL retain_resource(OpaqueResource* resource) {
  events.emplace_back("retain");
  check(std::memcmp(resource->key_bytes.data(), key.words.data(),
                    resource->key_bytes.size()) == 0);
  destination_published_before_retain =
      destination_slot != nullptr && *destination_slot == resource;
  resource->reference_count += 2;
  ++retain_calls;
  return resource->reference_count >> 1;
}

void PKG_PROP_TEST_THISCALL destroy_resource(OpaqueResource* resource,
                                             std::uint8_t deleting) {
  static_cast<void>(resource);
  events.emplace_back("destroy");
  destroy_deleting_flag = deleting;
  ++destroy_calls;
}

void reset_creation(OpaqueResource& resource, OpaqueManager& manager,
                    OpaqueRecord& record) {
  events.clear();
  key.words = {{0x11111111u, 0x22222222u, 0x33333333u}};
  allocation_result = &resource;
  allocation_size = 0;
  allocation_arg2 = nullptr;
  allocation_arg3 = nullptr;
  allocation_arg4 = nullptr;
  allocation_arg5 = nullptr;
  allocation_arg6 = nullptr;
  for (std::size_t& slot : allocation_arg_slots) {
    slot = 0;
  }
  resource_vtable.retain_00 = retain_resource;
  resource_vtable.release_04 = nullptr;
  resource_vtable.destroy_08 = destroy_resource;
  resource = OpaqueResource{};
  manager = OpaqueManager{};
  record = OpaqueRecord{};
  destination_slot = nullptr;
  destination_published_before_retain = false;
  dispatch_result = 0;
  destroy_deleting_flag = 0xff;
  retain_calls = 0;
  destroy_calls = 0;
  dispatch_calls = 0;
  dispatch_manager_arg = nullptr;
  dispatch_record_arg = nullptr;
  dispatch_resource_arg = nullptr;
  dispatch_key_word_arg = 0;
  dispatch_type_id_arg = 0;
  dispatch_saw_constructed_resource = false;
}

void install_creation_ports() {
  resource_creation_set_ports(
      ResourceCreationPorts{allocate_resource, &resource_vtable});
}

void test_resource_construct_exact_bytes() {
  OpaqueResource resource{};
  std::memset(reinterpret_cast<std::uint8_t*>(&resource), 0xee,
              sizeof(resource));
  resource_vtable.retain_00 = retain_resource;
  resource_vtable.release_04 = nullptr;
  resource_vtable.destroy_08 = destroy_resource;
  resource_creation_set_ports(
      ResourceCreationPorts{allocate_resource, &resource_vtable});

  OpaqueResource* returned = resource_construct_006a1b90(&resource, 0x1408b34u);
  check(returned == &resource);

  const std::uint8_t* const bytes =
      reinterpret_cast<const std::uint8_t*>(&resource);
  for (std::size_t offset = 0x04; offset < 0x24; ++offset) {
    check(bytes[offset] == 0);
  }
  for (std::size_t offset = 0x30; offset < 0x38; ++offset) {
    check(bytes[offset] == 0);
  }
  for (std::size_t offset = 0x24; offset < 0x30; ++offset) {
    check(bytes[offset] == 0xee);
  }

  check(resource.vtable == &resource_vtable);
  check(resource.reference_count == 0);
  for (std::uint8_t byte : resource.key_bytes) {
    check(byte == 0);
  }
  for (std::uint8_t byte : resource.cleared_14_23) {
    check(byte == 0);
  }
  for (std::uint8_t byte : resource.opaque_24_2f) {
    check(byte == 0xee);
  }
  check(resource.cleared_30 == 0);
  check(resource.cleared_34 == 0);
}

void test_mode_byte() {
  OpaqueManager manager{};
  manager.bytes_04_14.fill(0xa5);
  manager.dev_mode_15 = 0xa5;
  manager.bytes_16_1eb.fill(0xa5);
  prop_manager_set_mode_byte_006a3300(&manager, 0x5c);
  check(manager.dev_mode_15 == 0x5c);
  check(manager.bytes_04_14.back() == 0xa5);
  check(manager.bytes_16_1eb.front() == 0xa5);
  prop_manager_set_mode_byte_006a3300(&manager, 0);
  check(manager.dev_mode_15 == 0);
  prop_manager_set_mode_byte_006a3300(&manager, 0xff);
  check(manager.dev_mode_15 == 0xff);
}

void test_manager_vtable_pointer() {
  OpaqueManager manager{};
  OpaqueManagerVtable manager_vtable{};
  check(manager.vtable == nullptr);

  manager.vtable = &manager_vtable;
  check(manager.vtable == &manager_vtable);

  OpaqueManagerVtable* stored = nullptr;
  std::memcpy(&stored, reinterpret_cast<std::uint8_t*>(&manager),
              sizeof(stored));
  check(stored == &manager_vtable);

  prop_manager_set_mode_byte_006a3300(&manager, 0x77);
  check(reinterpret_cast<std::uint8_t*>(&manager)[0x15] == 0x77);
  check(manager.vtable == &manager_vtable);
}

void test_allocator_argument_order() {
  OpaqueResource resource{};
  OpaqueManager manager{};
  OpaqueRecord record{};
  reset_creation(resource, manager, record);

  OpaqueManagerVtable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_manager;
  manager.vtable = &manager_vtable;
  OpaqueRecordVtable record_vtable{};
  record_vtable.get_key_10 = get_record_key;
  record.vtable = &record_vtable;
  install_creation_ports();

  OpaqueResource* destination = nullptr;
  static_cast<void>(prop_manager_create_resource_006a3330(&manager, &record,
                                                          &destination, 0, 0));

  const std::size_t expected[6] = {0x38u, 0x1408b44u, 0u, 0u, 0u, 0u};
  for (std::size_t slot = 0; slot < 6; ++slot) {
    check(allocation_arg_slots[slot] == expected[slot]);
  }
}

void test_create_success_order() {
  OpaqueResource resource{};
  OpaqueManager manager{};
  OpaqueRecord record{};
  reset_creation(resource, manager, record);

  OpaqueManagerVtable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_manager;
  manager.vtable = &manager_vtable;
  OpaqueRecordVtable record_vtable{};
  record_vtable.get_key_10 = get_record_key;
  record.vtable = &record_vtable;
  install_creation_ports();

  OpaqueResource* destination = reinterpret_cast<OpaqueResource*>(0x12345678u);
  destination_slot = &destination;
  dispatch_result = 0xa5;
  check(prop_manager_create_resource_006a3330(&manager, &record, &destination,
                                              0x0badc0deu, 0x89abcdefu));
  expect({"allocate", "record-key", "dispatch", "retain"});
  check(destination == &resource);
  check(destination_published_before_retain);
  check(dispatch_calls == 1);
  check(dispatch_saw_constructed_resource);
  check(dispatch_manager_arg == &manager);
  check(dispatch_record_arg == &record);
  check(dispatch_resource_arg == &resource);
  check(dispatch_key_word_arg == 0x0badc0deu);
  check(dispatch_type_id_arg == 0x89abcdefu);
  check(allocation_size == 0x38);
  check(allocation_arg2 == reinterpret_cast<const char*>(0x1408b44u));
  check(allocation_arg3 == nullptr);
  check(allocation_arg4 == nullptr);
  check(allocation_arg5 == nullptr);
  check(allocation_arg6 == nullptr);
  check(std::memcmp(resource.key_bytes.data(), key.words.data(),
                    resource.key_bytes.size()) == 0);
  check(resource.reference_count == 2);
  check(retain_calls == 1);
  check(destroy_calls == 0);
}

void test_create_failure_ownership() {
  OpaqueResource resource{};
  OpaqueManager manager{};
  OpaqueRecord record{};
  reset_creation(resource, manager, record);

  OpaqueManagerVtable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_manager;
  manager.vtable = &manager_vtable;
  OpaqueRecordVtable record_vtable{};
  record_vtable.get_key_10 = get_record_key;
  record.vtable = &record_vtable;
  install_creation_ports();

  OpaqueResource* sentinel = reinterpret_cast<OpaqueResource*>(0x1f2e3d4cu);
  OpaqueResource* destination = sentinel;
  destination_slot = &destination;
  dispatch_result = 0;
  check(!prop_manager_create_resource_006a3330(&manager, &record, &destination,
                                               0x11112222u, 7));
  expect({"allocate", "record-key", "dispatch", "destroy"});
  check(destination == sentinel);
  check(dispatch_calls == 1);
  check(dispatch_saw_constructed_resource);
  check(dispatch_record_arg == &record);
  check(dispatch_resource_arg == &resource);
  check(dispatch_key_word_arg == 0x11112222u);
  check(dispatch_type_id_arg == 7);
  check(destroy_deleting_flag == 1);
  check(retain_calls == 0);
  check(destroy_calls == 1);
}

void test_create_null_allocation_faults() {
  OpaqueResource resource{};
  OpaqueManager manager{};
  OpaqueRecord record{};
  reset_creation(resource, manager, record);

  OpaqueManagerVtable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_manager;
  manager.vtable = &manager_vtable;
  OpaqueRecordVtable record_vtable{};
  record_vtable.get_key_10 = get_record_key;
  record.vtable = &record_vtable;
  allocation_result = nullptr;
  install_creation_ports();

  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    OpaqueResource* destination = nullptr;
    static_cast<void>(prop_manager_create_resource_006a3330(
        &manager, &record, &destination, 0, 0));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

void test_create_null_destination_faults() {
  OpaqueResource resource{};
  OpaqueManager manager{};
  OpaqueRecord record{};
  reset_creation(resource, manager, record);

  OpaqueManagerVtable manager_vtable{};
  manager_vtable.dispatch_24 = dispatch_manager;
  manager.vtable = &manager_vtable;
  OpaqueRecordVtable record_vtable{};
  record_vtable.get_key_10 = get_record_key;
  record.vtable = &record_vtable;
  install_creation_ports();
  destination_slot = nullptr;
  dispatch_result = 1;

  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(prop_manager_create_resource_006a3330(&manager, &record,
                                                            nullptr, 0, 0));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

OpaqueStreamVtable file_vtable{};
OpaqueStreamVtable memory_vtable{};
Word access_flags = 0;
std::int32_t write_result = 0;
const void* write_data = nullptr;
std::size_t write_size = 0;
std::uint32_t access_calls = 0;
std::uint32_t file_write_calls = 0;
std::uint32_t memory_write_calls = 0;
OpaqueStream* expected_file_object = nullptr;
OpaqueStream* expected_memory_object = nullptr;

Word PKG_PROP_TEST_THISCALL get_access_flags(OpaqueStream* stream) {
  events.emplace_back("access");
  check(stream == expected_file_object);
  ++access_calls;
  return access_flags;
}

std::int32_t PKG_PROP_TEST_THISCALL write_file(OpaqueStream* stream,
                                               const void* data,
                                               std::size_t size) {
  events.emplace_back("file-write");
  check(stream == expected_file_object);
  write_data = data;
  write_size = size;
  ++file_write_calls;
  return write_result;
}

std::int32_t PKG_PROP_TEST_THISCALL write_memory(OpaqueStream* stream,
                                                 const void* data,
                                                 std::size_t size) {
  events.emplace_back("memory-write");
  check(stream == expected_memory_object);
  write_data = data;
  write_size = size;
  ++memory_write_calls;
  return write_result;
}

OpaqueStream* record_write_receiver(OpaqueRecordWrite& record) {
  return reinterpret_cast<OpaqueStream*>(record.bytes.data() + 0x20);
}

OpaqueStream* embedded_memory_object(OpaqueRecordWrite& record) {
  return reinterpret_cast<OpaqueStream*>(record.bytes.data() + 0x24);
}

OpaqueStream* embedded_file_object(OpaqueRecordWrite& record) {
  return reinterpret_cast<OpaqueStream*>(record.bytes.data() + 0x48);
}

void reset_flush(OpaqueRecordWrite& record, Word reference_count) {
  events.clear();
  file_vtable = OpaqueStreamVtable{};
  memory_vtable = OpaqueStreamVtable{};
  file_vtable.get_access_flags_10 = get_access_flags;
  file_vtable.write_38 = write_file;
  memory_vtable.get_access_flags_10 = get_access_flags;
  memory_vtable.write_38 = write_memory;
  record = OpaqueRecordWrite{};
  std::memcpy(record.bytes.data() + 0x1c, &reference_count,
              sizeof(reference_count));
  *reinterpret_cast<OpaqueStreamVtable**>(record.bytes.data() + 0x24) =
      &memory_vtable;
  *reinterpret_cast<OpaqueStreamVtable**>(record.bytes.data() + 0x48) =
      &file_vtable;
  expected_file_object = embedded_file_object(record);
  expected_memory_object = embedded_memory_object(record);
  access_flags = 0;
  write_result = 0;
  write_data = nullptr;
  write_size = 0;
  access_calls = 0;
  file_write_calls = 0;
  memory_write_calls = 0;
}

void test_flush_file_path() {
  OpaqueRecordWrite record{};
  reset_flush(record, 1);
  std::uint8_t data[] = {1, 2, 3, 4};
  access_flags = 0xffffffffu;
  write_result = 9;
  check(record_write_flush_006c0550(record_write_receiver(record), data, 4));
  expect({"access", "file-write"});
  check(write_data == data);
  check(write_size == 4);
  check(access_calls == 1);
  check(file_write_calls == 1);
  check(memory_write_calls == 0);
}

void test_flush_memory_path_and_error() {
  OpaqueRecordWrite record{};
  reset_flush(record, 1);
  std::uint8_t data[] = {5, 6, 7};
  write_result = -16;
  check(record_write_flush_006c0550(record_write_receiver(record), data, 3));
  expect({"access", "memory-write"});
  check(write_data == data);
  check(write_size == 3);
  check(file_write_calls == 0);
  check(memory_write_calls == 1);

  events.clear();
  write_result = 0;
  check(!record_write_flush_006c0550(record_write_receiver(record), data, 3));
  expect({"access", "memory-write"});
  check(memory_write_calls == 2);
}

void test_flush_low_byte_result() {
  OpaqueRecordWrite record{};
  reset_flush(record, 1);
  std::uint8_t data[] = {0xa1, 0xb2, 0xc3};
  OpaqueStream* const receiver = record_write_receiver(record);

  const std::int32_t high_bits_only[] = {0x00000100, 0x0000ff00, 0x01000000,
                                         -0x00000100};
  for (std::int32_t value : high_bits_only) {
    access_flags = 0xffffffffu;
    write_result = value;
    check(!record_write_flush_006c0550(receiver, data, 3));

    access_flags = 0;
    write_result = value;
    check(!record_write_flush_006c0550(receiver, data, 3));
  }

  const std::int32_t low_byte_set[] = {0x00000001, 0x000000ff, 0x00000101, -1};
  for (std::int32_t value : low_byte_set) {
    access_flags = 0xffffffffu;
    write_result = value;
    check(record_write_flush_006c0550(receiver, data, 3));

    access_flags = 0;
    write_result = value;
    check(record_write_flush_006c0550(receiver, data, 3));
  }

  check(access_calls == 16);
  check(file_write_calls == 8);
  check(memory_write_calls == 8);
}

void test_flush_zero_reference() {
  OpaqueRecordWrite record{};
  reset_flush(record, 0);
  check(
      !record_write_flush_006c0550(record_write_receiver(record), nullptr, 9));
  check(events.empty());
  check(access_calls == 0);
  check(file_write_calls == 0);
  check(memory_write_calls == 0);
}

void test_flush_null_vtable_faults() {
  OpaqueRecordWrite record{};
  reset_flush(record, 1);
  std::memset(record.bytes.data() + 0x24, 0, sizeof(std::uint32_t));
  access_flags = 0;

  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(
        record_write_flush_006c0550(record_write_receiver(record), nullptr, 0));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
}

void test_flush_null_file_vtable_faults() {
  OpaqueRecordWrite record{};
  reset_flush(record, 1);
  std::memset(record.bytes.data() + 0x48, 0, sizeof(std::uint32_t));

  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(
        record_write_flush_006c0550(record_write_receiver(record), nullptr, 0));
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
  using namespace openspore::reconstruction::pkg_prop_resource_wave9;
  test_mode_byte();
  test_manager_vtable_pointer();
  test_resource_construct_exact_bytes();
  test_allocator_argument_order();
  test_create_success_order();
  test_create_failure_ownership();
  test_create_null_allocation_faults();
  test_create_null_destination_faults();
  test_flush_file_path();
  test_flush_memory_path_and_error();
  test_flush_low_byte_result();
  test_flush_zero_reference();
  test_flush_null_vtable_faults();
  test_flush_null_file_vtable_faults();
  return 0;
}

#undef PKG_PROP_TEST_CDECL
#undef PKG_PROP_TEST_THISCALL
