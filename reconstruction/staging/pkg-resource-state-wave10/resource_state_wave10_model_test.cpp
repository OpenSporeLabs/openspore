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

#include "resource_state_wave10.hpp"

#if defined(_MSC_VER)
#define PKG_RS_TEST_CDECL __cdecl
#define PKG_RS_TEST_THISCALL __thiscall
#else
#define PKG_RS_TEST_CDECL __attribute__((cdecl))
#define PKG_RS_TEST_THISCALL __attribute__((thiscall))
#endif

namespace openspore::reconstruction::pkg_resource_state_wave10 {
namespace {

using GetStateSignature =
    OpaqueRecordWrite*(PKG_RS_TEST_THISCALL*)(OpaqueRecordWrite*, Word);
using DestroySignature = void(PKG_RS_TEST_THISCALL*)(OpaqueRecordWrite*);
using UntrackSignature = void(PKG_RS_TEST_CDECL*)(void*);
using DropHandleSignature = void(PKG_RS_TEST_CDECL*)(void*, Word, Word, Word,
                                                     Word);
using ChunkSweepSignature = void(PKG_RS_TEST_THISCALL*)(void*, void* const*,
                                                        Word);
using OwnerUntrackSignature = void(PKG_RS_TEST_THISCALL*)(OpaqueOwner*, void*);

static_assert(
    std::is_same<decltype(&record_write_get_state_00e310c0),
                 GetStateSignature>::value,
    "00e310c0 takes this plus one stack word released by RET 4 and returns a "
    "pointer");
static_assert(std::is_same<decltype(&record_write_destroy_00e30f90),
                           DestroySignature>::value,
              "00e30f90 takes this only and releases no stack words");
static_assert(std::is_same<decltype(&record_write_untrack_00f47380),
                           UntrackSignature>::value,
              "00f47380 takes one stack word and releases nothing");
static_assert(std::is_same<decltype(&record_write_drop_handle_00571db0),
                           DropHandleSignature>::value,
              "00571db0 takes five stack words and releases nothing");
static_assert(std::is_same<decltype(&record_write_chunk_sweep_00e308d0),
                           ChunkSweepSignature>::value,
              "00e308d0 takes this plus two stack words released by RET 8");
static_assert(
    std::is_same<decltype(OpaqueRecordWrite::sentinel_guard_0c), Word>::value,
    "the sentinel guard word is a full word");
static_assert(sizeof(OpaqueRecordWrite) == 0x27c &&
                  offsetof(OpaqueRecordWrite, vtable_00) == 0x00 &&
                  offsetof(OpaqueRecordWrite, secondary_vtable_08) == 0x08 &&
                  offsetof(OpaqueRecordWrite, sentinel_guard_0c) == 0x0c &&
                  offsetof(OpaqueRecordWrite, sentinel_10) == 0x10 &&
                  offsetof(OpaqueRecordWrite, chunk_base_28) == 0x28 &&
                  offsetof(OpaqueRecordWrite, chunk_count_2c) == 0x2c &&
                  offsetof(OpaqueRecordWrite, cursor_30) == 0x30 &&
                  offsetof(OpaqueRecordWrite, handle_44) == 0x44,
              "the observed record layout keeps every touched slot in place");

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

struct RecorderState {
  std::uint32_t destroy_calls = 0;
  std::uint32_t untrack_calls = 0;
  std::uint32_t drop_handle_calls = 0;
  std::uint32_t chunk_sweep_calls = 0;
  std::uint32_t owner_untrack_calls = 0;
  OpaqueRecordWrite* destroy_receiver = nullptr;
  void* destroy_flag = nullptr;
  std::int32_t destroy_flag_write = 0;
  std::vector<void*> untrack_targets;
  void* drop_handle_handle = nullptr;
  Word drop_handle_args[4] = {0, 0, 0, 0};
  Word drop_handle_handle_at_call = 0xffffffffu;
  Word drop_handle_cursor_at_call = 0xffffffffu;
  void* chunk_sweep_receiver = nullptr;
  void* const* chunk_sweep_chunks = nullptr;
  void* chunk_sweep_first = nullptr;
  Word chunk_sweep_count = 0;
  const void* chunk_sweep_primary = nullptr;
  const void* chunk_sweep_secondary = nullptr;
  OpaqueOwner* owner_untrack_receiver = nullptr;
  void* owner_untrack_target = nullptr;
  Word flag_at_destroy = 0xffffffffu;
};

RecorderState state;
OpaqueRecordWrite record;
void* chunk_storage[2];
int guard_word = 0;
int sentinel_owner = 0;

void PKG_RS_TEST_THISCALL record_destroy(OpaqueRecordWrite* receiver) {
  events.emplace_back("destroy");
  state.flag_at_destroy = state.destroy_flag == nullptr
                              ? 0xffffffffu
                              : *static_cast<Word*>(state.destroy_flag);
  if (state.destroy_flag != nullptr) {
    Word* const slot = static_cast<Word*>(state.destroy_flag);
    if (state.destroy_flag_write == 1) {
      *slot = 0x00000000u;
    } else if (state.destroy_flag_write == 2) {
      *slot = 0x00000001u;
    }
  }
  state.destroy_receiver = receiver;
  ++state.destroy_calls;
}

void PKG_RS_TEST_CDECL record_untrack(void* target) {
  events.emplace_back("untrack");
  state.untrack_targets.push_back(target);
  ++state.untrack_calls;
}

void PKG_RS_TEST_CDECL record_drop_handle(void* handle, Word arg_48,
                                          Word arg_4c, Word arg_50,
                                          Word arg_54) {
  events.emplace_back("drop-handle");
  state.drop_handle_handle = handle;
  state.drop_handle_args[0] = arg_48;
  state.drop_handle_args[1] = arg_4c;
  state.drop_handle_args[2] = arg_50;
  state.drop_handle_args[3] = arg_54;
  state.drop_handle_handle_at_call = state_load_word(&record, 0x44);
  state.drop_handle_cursor_at_call = state_load_word(&record, 0x30);
  ++state.drop_handle_calls;
}

void PKG_RS_TEST_THISCALL record_chunk_sweep(void* receiver,
                                             void* const* chunks, Word count) {
  events.emplace_back("chunk-sweep");
  state.chunk_sweep_receiver = receiver;
  state.chunk_sweep_chunks = chunks;
  check(chunks != nullptr);
  state.chunk_sweep_first = chunks[0];
  state.chunk_sweep_count = count;
  state.chunk_sweep_primary = record.vtable_00;
  state.chunk_sweep_secondary = record.secondary_vtable_08;
  ++state.chunk_sweep_calls;
}

void PKG_RS_TEST_THISCALL record_owner_untrack(OpaqueOwner* owner,
                                               void* target) {
  events.emplace_back("owner-untrack");
  state.owner_untrack_receiver = owner;
  state.owner_untrack_target = target;
  ++state.owner_untrack_calls;
}

void install_recorders() {
  events.clear();
  state = RecorderState{};
  ResourceStatePorts selected{};
  selected.destroy_00e30f90 = record_destroy;
  selected.untrack_00f47380 = record_untrack;
  selected.drop_handle_00571db0 = record_drop_handle;
  selected.chunk_sweep_00e308d0 = record_chunk_sweep;
  selected.owner_untrack_009276c0 = record_owner_untrack;
  selected.owner_instance_016c8b44 = reinterpret_cast<void*>(0x016c8b44u);
  resource_state_set_ports(selected);
}

void reset_record() {
  std::memset(&record, 0xcc, sizeof(record));
  std::memset(chunk_storage, 0xcc, sizeof(chunk_storage));
  record.vtable_00 = reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x11));
  record.secondary_vtable_08 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x22));
  record.sentinel_guard_0c = 0x33333333u;
  record.sentinel_10 = nullptr;
  record.stream_vtable_24 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x44));
  record.chunk_base_28 = nullptr;
  record.chunk_count_2c = 0;
  record.cursor_30 = 0x55555555u;
  record.handle_44 = nullptr;
  install_recorders();
}

void test_get_state_destroys_before_flag_test() {
  reset_record();
  OpaqueRecordWrite* const returned =
      record_write_get_state_00e310c0(&record, 0);
  check(returned == &record);
  expect({"destroy"});
  check(state.destroy_calls == 1);
  check(state.destroy_receiver == &record);
  check(state.untrack_calls == 0);
  check(state.drop_handle_calls == 0);
  check(state.chunk_sweep_calls == 0);
  check(state.owner_untrack_calls == 0);
}

void test_get_state_release_flag_bit0() {
  static const Word no_release[] = {0x00000000u, 0x00000002u, 0x00000004u,
                                    0x000000feu, 0xfffffffeu};
  static const Word release[] = {0x00000001u, 0x00000003u, 0x00000005u,
                                 0x000000ffu, 0xffffffffu};
  for (Word flag : no_release) {
    reset_record();
    check(record_write_get_state_00e310c0(&record, flag) == &record);
    expect({"destroy"});
    check(state.destroy_calls == 1);
    check(state.untrack_calls == 0);
  }
  for (Word flag : release) {
    reset_record();
    check(record_write_get_state_00e310c0(&record, flag) == &record);
    expect({"destroy", "untrack"});
    check(state.destroy_calls == 1);
    check(state.untrack_calls == 1);
    check(state.untrack_targets.size() == 1);
    check(state.untrack_targets[0] == &record);
  }
}

void test_get_state_release_flag_reads_low_byte_only() {
  struct Case {
    Word flag;
    bool releases;
  };
  static const Case cases[] = {
      {0x00000000u, false}, {0x00000100u, false}, {0x00010000u, false},
      {0x01000000u, false}, {0x80000000u, false}, {0x00000001u, true},
      {0x00000101u, true},  {0x00010001u, true},  {0x01000001u, true},
      {0x80000001u, true},  {0xffffff00u, false}, {0xffffff01u, true},
  };
  for (const Case& item : cases) {
    reset_record();
    check(record_write_get_state_00e310c0(&record, item.flag) == &record);
    check(state.untrack_calls == (item.releases ? 1u : 0u));
    check(state.destroy_calls == 1);
  }
}

void test_get_state_returns_receiver_for_every_flag() {
  static const Word flags[] = {0x00000000u, 0x00000001u, 0x00000101u,
                               0x80000000u, 0xffffffffu};
  for (Word flag : flags) {
    reset_record();
    OpaqueRecordWrite* const returned =
        record_write_get_state_00e310c0(&record, flag);
    check(returned == &record);
    check(returned == state.destroy_receiver);
  }
}

void test_get_state_returns_destroyed_object() {
  reset_record();
  resource_state_reset_ports();
  events.clear();
  OpaqueRecordWrite* const returned =
      record_write_get_state_00e310c0(&record, 0x00000000u);
  check(returned == &record);
  check(record.vtable_00 == kVtableBasePrimary_013ec458());
  check(record.secondary_vtable_08 == kVtableBaseSecondary_013eb394());
  check(record.cursor_30 == 0);
  check(state_load_pointer(&record, 0x00) ==
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x013ec458u)));
  check(state_load_pointer(&record, 0x08) ==
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x013eb394u)));
  check(record.reserved_04 == 0xccccccccu);
  check(record.sentinel_guard_0c == 0x33333333u);
  check(record.stream_vtable_24 ==
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x44)));
  check(record.body_58_27b[0] == 0xcc);
  check(record.body_58_27b[sizeof(record.body_58_27b) - 1] == 0xcc);
  check(record.body_14_23[0] == 0xcc);
  check(record.body_34_43[0] == 0xcc);
}

void test_get_state_flag_is_captured_at_entry() {
  reset_record();
  Word flag = 0x00000001u;
  state.destroy_flag = &flag;
  state.destroy_flag_write = 1;
  check(record_write_get_state_00e310c0(&record, flag) == &record);
  expect({"destroy", "untrack"});
  check(state.flag_at_destroy == 0x00000001u);
  check(flag == 0x00000000u);
  check(state.destroy_calls == 1);
  check(state.untrack_calls == 1);
  check(state.untrack_targets.size() == 1);
  check(state.untrack_targets[0] == &record);

  reset_record();
  Word release = 0x00000000u;
  state.destroy_flag = &release;
  state.destroy_flag_write = 2;
  check(record_write_get_state_00e310c0(&record, release) == &record);
  expect({"destroy"});
  check(state.flag_at_destroy == 0x00000000u);
  check(release == 0x00000001u);
  check(state.destroy_calls == 1);
  check(state.untrack_calls == 0);
}

std::uint32_t stack_probe_result = 0;

void PKG_RS_TEST_CDECL get_state_stack_probe(OpaqueRecordWrite* receiver,
                                             Word flag, Word guard_low,
                                             Word guard_high) {
  std::uint32_t* const canary =
      static_cast<std::uint32_t*>(__builtin_alloca(2 * sizeof(std::uint32_t)));
  canary[0] = 0xc0dec0deu;
  canary[1] = 0xfeedfaceu;
  const GetStateSignature entry = &record_write_get_state_00e310c0;
  check(entry(receiver, flag) == receiver);
  check(canary[0] == 0xc0dec0deu);
  check(canary[1] == 0xfeedfaceu);
  check(guard_low == 0x11223344u);
  check(guard_high == 0x55667788u);
  stack_probe_result = canary[0] ^ canary[1] ^ guard_low ^ guard_high;
}

void test_get_state_stack_discipline() {
  reset_record();
  get_state_stack_probe(&record, 0x00000001u, 0x11223344u, 0x55667788u);
  check(stack_probe_result ==
        (0xc0dec0deu ^ 0xfeedfaceu ^ 0x11223344u ^ 0x55667788u));
  expect({"destroy", "untrack"});
  check(state.untrack_targets.size() == 1);
  check(state.untrack_targets[0] == &record);
}

void test_get_state_null_receiver_faults() {
  reset_record();
  resource_state_reset_ports();
  const pid_t child = fork();
  check(child >= 0);
  if (child == 0) {
    static_cast<void>(record_write_get_state_00e310c0(nullptr, 0x00000000u));
    _exit(0);
  }
  int status = 0;
  check(waitpid(child, &status, 0) == child);
  check(WIFSIGNALED(status));
  check(WTERMSIG(status) == SIGSEGV);
  resource_state_reset_ports();
}

void test_destroy_handle_branch() {
  reset_record();
  record_write_destroy_00e30f90(&record);
  expect({"chunk-sweep"});
  check(state.drop_handle_calls == 0);
  check(state.untrack_calls == 0);
  check(record.handle_44 == nullptr);
  check(record.cursor_30 == 0);

  reset_record();
  record.handle_44 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x3000));
  record.handle_arg_48 = 0x40000001u;
  record.handle_arg_4c = 0x40000002u;
  record.handle_arg_50 = 0x40000003u;
  record.handle_arg_54 = 0x40000004u;
  record_write_destroy_00e30f90(&record);
  expect({"drop-handle", "chunk-sweep"});
  check(state.drop_handle_calls == 1);
  check(state.drop_handle_handle ==
        reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x3000)));
  check(state.drop_handle_args[0] == 0x40000001u);
  check(state.drop_handle_args[1] == 0x40000002u);
  check(state.drop_handle_args[2] == 0x40000003u);
  check(state.drop_handle_args[3] == 0x40000004u);
  check(state.drop_handle_handle_at_call == 0);
  check(state.drop_handle_cursor_at_call == 0x55555555u);
  check(record.handle_44 == nullptr);
  check(record.handle_arg_48 == 0x40000001u);
  check(record.handle_arg_4c == 0x40000002u);
  check(record.handle_arg_50 == 0x40000003u);
  check(record.handle_arg_54 == 0x40000004u);
}

void test_destroy_chunk_branch() {
  static const Word counts[] = {0, 1, 2, 3, 0xffffffffu};
  for (Word count : counts) {
    reset_record();
    record.chunk_base_28 = chunk_storage;
    record.chunk_count_2c = count;
    record_write_destroy_00e30f90(&record);
    if (count > 1) {
      expect({"chunk-sweep", "untrack"});
    } else {
      expect({"chunk-sweep"});
    }
    check(state.chunk_sweep_calls == 1);
    check(state.chunk_sweep_receiver ==
          reinterpret_cast<std::uint8_t*>(&record) + 0x24);
    check(state.chunk_sweep_chunks != nullptr);
    check(state.chunk_sweep_first == chunk_storage);
    check(state.chunk_sweep_count == count);
    check(state.untrack_calls == (count > 1 ? 1u : 0u));
    check(record.cursor_30 == 0);
    check(record.chunk_base_28 == chunk_storage);
    check(record.chunk_count_2c == count);
  }
}

void test_destroy_sentinel_branch() {
  reset_record();
  record.sentinel_10 = &sentinel_owner;
  record.sentinel_guard_0c = 0;
  record_write_destroy_00e30f90(&record);
  expect({"chunk-sweep"});
  check(state.untrack_calls == 0);
  check(record.sentinel_10 == &sentinel_owner);

  reset_record();
  record.sentinel_10 = &sentinel_owner;
  record.sentinel_guard_0c = 1;
  record_write_destroy_00e30f90(&record);
  expect({"chunk-sweep", "untrack"});
  check(state.untrack_calls == 1);
  check(state.untrack_targets.size() == 1);
  check(state.untrack_targets[0] == &sentinel_owner);

  reset_record();
  record.sentinel_10 = nullptr;
  record.sentinel_guard_0c = 1;
  record_write_destroy_00e30f90(&record);
  expect({"chunk-sweep"});
  check(state.untrack_calls == 0);
}

void test_untrack_null_sentinel() {
  reset_record();
  record_write_untrack_00f47380(nullptr);
  expect({});
  check(state.owner_untrack_calls == 0);

  reset_record();
  record_write_untrack_00f47380(&record);
  expect({"owner-untrack"});
  check(state.owner_untrack_calls == 1);
  check(state.owner_untrack_receiver ==
        reinterpret_cast<OpaqueOwner*>(
            reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x016c8b44u))));
  check(state.owner_untrack_target == &record);
  check(state.owner_untrack_receiver ==
        static_cast<OpaqueOwner*>(
            const_cast<void*>(kOwnerInstanceDefault_016c8b44())));
}

void install_real_destroy_recording_leaves() {
  events.clear();
  state = RecorderState{};
  ResourceStatePorts selected{};
  selected.destroy_00e30f90 = &record_write_destroy_00e30f90;
  selected.untrack_00f47380 = record_untrack;
  selected.drop_handle_00571db0 = record_drop_handle;
  selected.chunk_sweep_00e308d0 = record_chunk_sweep;
  selected.owner_untrack_009276c0 = record_owner_untrack;
  selected.owner_instance_016c8b44 = reinterpret_cast<void*>(0x016c8b44u);
  resource_state_set_ports(selected);
}

void test_destroy_full_order() {
  reset_record();
  record.handle_44 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x7000));
  record.handle_arg_48 = 0xaaaaaa01u;
  record.handle_arg_4c = 0xaaaaaa02u;
  record.handle_arg_50 = 0xaaaaaa03u;
  record.handle_arg_54 = 0xaaaaaa04u;
  record.chunk_base_28 = chunk_storage;
  record.chunk_count_2c = 4;
  record.sentinel_10 = &sentinel_owner;
  record.sentinel_guard_0c = 0x5a5a5a5au;
  guard_word = 0;
  install_real_destroy_recording_leaves();

  check(record_write_get_state_00e310c0(&record, 0x00000001u) == &record);
  expect({"drop-handle", "chunk-sweep", "untrack", "untrack", "untrack"});
  check(state.destroy_calls == 0);
  check(state.drop_handle_calls == 1);
  check(state.chunk_sweep_calls == 1);
  check(state.untrack_calls == 3);
  check(state.untrack_targets[0] == chunk_storage);
  check(state.untrack_targets[1] == &sentinel_owner);
  check(state.untrack_targets[2] == &record);
  check(state.chunk_sweep_primary == kVtableDerivedPrimary_01481948());
  check(state.chunk_sweep_secondary == kVtableDerivedSecondary_01481940());
  check(state.chunk_sweep_count == 4);
  check(state.chunk_sweep_receiver ==
        reinterpret_cast<std::uint8_t*>(&record) + 0x24);
  check(record.vtable_00 == kVtableBasePrimary_013ec458());
  check(record.secondary_vtable_08 == kVtableBaseSecondary_013eb394());
  check(record.handle_44 == nullptr);
  check(record.cursor_30 == 0);
  check(record.sentinel_10 == &sentinel_owner);
  check(guard_word == 0);

  reset_record();
  record.handle_44 =
      reinterpret_cast<void*>(static_cast<std::uintptr_t>(0x7000));
  record.chunk_base_28 = chunk_storage;
  record.chunk_count_2c = 4;
  record.sentinel_10 = &sentinel_owner;
  record.sentinel_guard_0c = 0x5a5a5a5au;
  install_real_destroy_recording_leaves();
  check(record_write_get_state_00e310c0(&record, 0x00000000u) == &record);
  expect({"drop-handle", "chunk-sweep", "untrack", "untrack"});
  check(state.untrack_calls == 2);
  check(state.untrack_targets[0] == chunk_storage);
  check(state.untrack_targets[1] == &sentinel_owner);
}

void test_port_defaulting() {
  reset_record();
  resource_state_set_ports(ResourceStatePorts{});
  events.clear();
  state = RecorderState{};
  check(record_write_get_state_00e310c0(&record, 0x00000001u) == &record);
  expect({});
  check(record.vtable_00 == kVtableBasePrimary_013ec458());
  check(record.secondary_vtable_08 == kVtableBaseSecondary_013eb394());
  check(record.cursor_30 == 0);
  check(record.handle_44 == nullptr);
  check(record.chunk_base_28 == nullptr);
  check(record.chunk_count_2c == 0);
  check(record.sentinel_10 == nullptr);
  check(record.reserved_04 == 0xccccccccu);
  check(kVtableDerivedPrimary_01481948() ==
        reinterpret_cast<const void*>(0x01481948u));
  check(kVtableDerivedSecondary_01481940() ==
        reinterpret_cast<const void*>(0x01481940u));
  check(kVtableBasePrimary_013ec458() ==
        reinterpret_cast<const void*>(0x013ec458u));
  check(kVtableBaseSecondary_013eb394() ==
        reinterpret_cast<const void*>(0x013eb394u));
  check(kOwnerInstanceDefault_016c8b44() ==
        reinterpret_cast<const void*>(0x016c8b44u));
  resource_state_reset_ports();
}

}

}

int main() {
  using namespace openspore::reconstruction::pkg_resource_state_wave10;
  test_get_state_destroys_before_flag_test();
  test_get_state_release_flag_bit0();
  test_get_state_release_flag_reads_low_byte_only();
  test_get_state_returns_receiver_for_every_flag();
  test_get_state_flag_is_captured_at_entry();
  test_get_state_returns_destroyed_object();
  test_get_state_stack_discipline();
  test_get_state_null_receiver_faults();
  test_destroy_handle_branch();
  test_destroy_chunk_branch();
  test_destroy_sentinel_branch();
  test_untrack_null_sentinel();
  test_destroy_full_order();
  test_port_defaulting();
  return 0;
}

#undef PKG_RS_TEST_CDECL
#undef PKG_RS_TEST_THISCALL
