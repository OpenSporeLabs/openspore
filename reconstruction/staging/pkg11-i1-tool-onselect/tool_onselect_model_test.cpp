#include <cassert>
#include <cstdint>

#include "tool_onselect.hpp"

namespace {

using openspore::reconstruction::pkg11_i1_tool_onselect::
    g_pkg11_i1_tool_onselect_ports;
using openspore::reconstruction::pkg11_i1_tool_onselect::kVftable_01403934;
using openspore::reconstruction::pkg11_i1_tool_onselect::on_select_01053790;
using openspore::reconstruction::pkg11_i1_tool_onselect::
    OpaqueBaseSubobject01403934;
using openspore::reconstruction::pkg11_i1_tool_onselect::
    pkg11_i1_on_select_arg_bit0;
using openspore::reconstruction::pkg11_i1_tool_onselect::Vftable01403934;

struct ReleaseRecord {
  int calls;
  void* last_block;
  const Vftable01403934* vftable_seen_at_call;
};

ReleaseRecord g_release_record{};

void record_release(void* block) {
  ++g_release_record.calls;
  g_release_record.last_block = block;
  g_release_record.vftable_seen_at_call =
      reinterpret_cast<OpaqueBaseSubobject01403934*>(block)->vftable;
}

void reset_ports() {
  g_pkg11_i1_tool_onselect_ports.pool_release_00f47380 = &record_release;
  g_release_record = ReleaseRecord{};
}

void test_vftable_image_matches_observed_rdata_slots() {
  assert(kVftable_01403934->slot0_va == 0x01053790u);
  assert(kVftable_01403934->slot1_va == 0x011e06d0u);
  assert(kVftable_01403934->slot2_va == 0x011e06d0u);
  assert(kVftable_01403934->slot3_va == 0x011e06d0u);
  assert(kVftable_01403934->slot4_va == 0x012c6625u);
  assert(kVftable_01403934->slot5_va == 0x012c6625u);
}

void test_guard_is_bit0_not_non_null() {
  assert(pkg11_i1_on_select_arg_bit0(0x00000000u) == false);
  assert(pkg11_i1_on_select_arg_bit0(0x00000001u) == true);
  assert(pkg11_i1_on_select_arg_bit0(0x00000002u) == false);
  assert(pkg11_i1_on_select_arg_bit0(0x00000003u) == true);
  assert(pkg11_i1_on_select_arg_bit0(0x12345678u) == false);
  assert(pkg11_i1_on_select_arg_bit0(0xffffffffu) == true);
}

void test_bit0_clear_skips_release_but_still_restamps_vptr() {
  reset_ports();

  OpaqueBaseSubobject01403934 strategy{};
  strategy.vftable = nullptr;

  assert(on_select_01053790(&strategy, 0x00000000u) == true);
  assert(strategy.vftable == kVftable_01403934);
  assert(g_release_record.calls == 0);
}

void test_aligned_non_null_pointer_word_skips_release() {
  reset_ports();

  OpaqueBaseSubobject01403934 strategy{};
  strategy.vftable = nullptr;

  const std::uint32_t aligned_pointer_word = 0x00401234u;
  assert(on_select_01053790(&strategy, aligned_pointer_word) == true);
  assert(g_release_record.calls == 0);
  assert(strategy.vftable == kVftable_01403934);
}

void test_bit0_set_releases_the_receiver() {
  reset_ports();

  OpaqueBaseSubobject01403934 strategy{};
  strategy.vftable = nullptr;

  assert(on_select_01053790(&strategy, 0x00000001u) == true);
  assert(g_release_record.calls == 1);
  assert(g_release_record.last_block == &strategy);
}

void test_vptr_stamp_precedes_the_release_call() {
  reset_ports();

  OpaqueBaseSubobject01403934 strategy{};

  on_select_01053790(&strategy, 0x00000003u);

  assert(g_release_record.vftable_seen_at_call == kVftable_01403934);
  assert(strategy.vftable == kVftable_01403934);
}

void test_already_stamped_receiver_repeats_the_same_write() {
  reset_ports();

  OpaqueBaseSubobject01403934 strategy{};
  strategy.vftable = kVftable_01403934;

  assert(on_select_01053790(&strategy, 0x00000001u) == true);
  assert(g_release_record.calls == 1);
  assert(g_release_record.last_block == &strategy);
  assert(strategy.vftable == kVftable_01403934);
}

}

int main() {
  test_vftable_image_matches_observed_rdata_slots();
  test_guard_is_bit0_not_non_null();
  test_bit0_clear_skips_release_but_still_restamps_vptr();
  test_aligned_non_null_pointer_word_skips_release();
  test_bit0_set_releases_the_receiver();
  test_vptr_stamp_precedes_the_release_call();
  test_already_stamped_receiver_repeats_the_same_write();
  return 0;
}
