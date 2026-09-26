// Model test for 0x00c0b780, 0x00b8dad0, 0x00c47180 and 0x00ba61b0.
//
// Every assertion below is a fact read out of the live binary, not a
// prediction. The four bodies reconstructed here are total: no branch depends
// on anything the binary does not supply.

#include "wave13_w1_core_b08.hpp"
#include "wave13_w1_core_b08_reconstructed.hpp"
#include "wave13_w1_core_b08_test_stubs.hpp"

#include <cstdio>
#include <cstring>

namespace osb = openspore::wave13_w1_core_b08;

namespace {

using openspore::wave13_w1_core_b08::g_failures;
using openspore::wave13_w1_core_b08::note_check;
using openspore::wave13_w1_core_b08::note_check_u32;

void check(bool ok, const char* what) {
    note_check(ok, what);
}

void check_u32(std::uint32_t got, std::uint32_t want, const char* what) {
    note_check_u32(got, want, what);
}

// --- 0x00c0b780 ----------------------------------------------------------
// XOR ECX,ECX / CMP ECX,[EAX + 0x608] / SBB EAX,EAX / NEG EAX.
// Answer is a full dword 0 or 1, and the sub-object at +0xB20 is dereferenced
// with no null guard.

osb::OpaqueC0b780SubObject g_sub780;
osb::OpaqueC0b780Owner g_owner780;

void test_c0b780() {
    std::memset(&g_sub780, 0, sizeof(g_sub780));
    std::memset(&g_owner780, 0, sizeof(g_owner780));
    osb::OpaqueC0b780SubObject* sub_obj = &g_sub780;
    osb::OpaqueC0b780Owner& owner = g_owner780;
    owner.f_B20 = sub_obj;

    sub_obj->f_608 = 0u;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 0u,
              "0x00c0b780 f_608 == 0 returns 0");

    sub_obj->f_608 = 1u;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 1u,
              "0x00c0b780 f_608 == 1 returns 1");

    // Any non-zero dword answers 1: CMP 0,mem sets CF for unsigned > 0, so the
    // predicate is != 0 and not == 1.
    sub_obj->f_608 = 0x80000000u;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 1u,
              "0x00c0b780 f_608 == 0x80000000 returns 1");
    sub_obj->f_608 = 0xFFFFFFFFu;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 1u,
              "0x00c0b780 f_608 == 0xFFFFFFFF returns 1");

    // The two flag words are independent: writing 0x60C must not change the
    // answer, which is what makes 0x00c0b7a0 a distinct predicate.
    sub_obj->f_608 = 0u;
    sub_obj->f_60C = 0xDEADu;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 0u,
              "0x00c0b780 ignores the +0x60C flag");

    // The receiver's own +0xB88 field, which the sibling 0x00c0b8e0 reads, is
    // also untouched by this body.
    owner.f_B88 = 0x1234;
    sub_obj->f_608 = 1u;
    check_u32(osb::SimCore_00c0b780_sub_object_flag_608(&owner), 1u,
              "0x00c0b780 ignores the receiver +0xB88 field");
    check_u32(static_cast<std::uint32_t>(owner.f_B88), 0x1234u,
              "0x00c0b780 writes nothing");
    check_u32(sub_obj->f_60C, 0xDEADu, "0x00c0b780 writes nothing to the sub-object");
}

// --- 0x00b8dad0 ----------------------------------------------------------
// LEA EAX,[ECX + 0x198] ; RET. The address is formed, not loaded.

void test_b8dad0() {
    alignas(8) std::uint8_t raw[0x1B0];
    std::memset(raw, 0, sizeof(raw));
    osb::OpaqueCPlanetRecord* rec = reinterpret_cast<osb::OpaqueCPlanetRecord*>(raw);

    osb::ResourceKey3* p = osb::SimCore_00b8dad0_spice_gen_key_ptr(rec);
    check(reinterpret_cast<std::uint8_t*>(p) == raw + 0x198,
          "0x00b8dad0 returns receiver + 0x198");
    check(reinterpret_cast<std::uint8_t*>(&rec->f_198) == raw + 0x198,
          "0x00b8dad0 agrees with the +0x198 member");

    // The returned block aliases the receiver: writing through it is visible.
    p->dword_0 = 0x11111111u;
    p->dword_4 = 0x22222222u;
    p->dword_8 = 0x33333333u;
    check_u32(rec->f_198.dword_0, 0x11111111u, "0x00b8dad0 result aliases +0x198");
    check_u32(rec->f_198.dword_4, 0x22222222u, "0x00b8dad0 result aliases +0x19C");
    check_u32(rec->f_198.dword_8, 0x33333333u, "0x00b8dad0 result aliases +0x1A0");

    // Two receivers give two distinct blocks; the function is a pure offset.
    osb::OpaqueCPlanetRecord* rec2 =
        reinterpret_cast<osb::OpaqueCPlanetRecord*>(raw + 0x1B0);
    osb::ResourceKey3* q = osb::SimCore_00b8dad0_spice_gen_key_ptr(rec2);
    check(reinterpret_cast<std::uint8_t*>(q) ==
              reinterpret_cast<std::uint8_t*>(p) + 0x1B0,
          "0x00b8dad0 is a constant offset, not a stored pointer");
}

// --- 0x00c47180 ----------------------------------------------------------
// Evict-then-clear, then forward to the global manager. The incoming stack
// argument is dead.

void test_c47180() {
    osb::OpaqueManagerSlotOccupant occupant;
    occupant.vtable = osb::make_occupant_vtable();

    osb::OpaqueC47180Owner owner;
    std::memset(&owner, 0, sizeof(owner));

    osb::reset_log();
    osb::g_slot_c0_calls = 0;
    osb::g_manager_0167eae4 = reinterpret_cast<void*>(0x00C0FFEEu);
    osb::g_bb59b0_manager_arg = nullptr;
    osb::g_bb59b0_slot_arg = nullptr;

    // Empty slot: no virtual call, but the manager forward still happens.
    osb::SimCore_00c47180_manager_slot_replace(&owner, 0xDEADBEEFu);
    check_u32(static_cast<std::uint32_t>(osb::g_slot_c0_calls), 0u,
              "0x00c47180 with an empty slot makes no virtual call");
    check(osb::g_bb59b0_manager_arg == osb::g_manager_0167eae4,
          "0x00c47180 forwards the global manager from 0x0167EAE4");
    check(osb::g_bb59b0_slot_arg == &owner.f_1E8,
          "0x00c47180 forwards &receiver->f_1E8");

    // Occupied slot: detach through slot +0xC0, and the slot reads back null.
    owner.f_1E8 = &occupant;
    osb::reset_log();
    osb::g_slot_c0_calls = 0;
    osb::g_bb59b0_slot_arg = nullptr;
    osb::SimCore_00c47180_manager_slot_replace(&owner, 0xDEADBEEFu);
    check_u32(static_cast<std::uint32_t>(osb::g_slot_c0_calls), 1u,
              "0x00c47180 calls vtable slot +0xC0 once on the evicted occupant");
    check(owner.f_1E8 == nullptr,
          "0x00c47180 clears +0x1E8 before forwarding");
    check(osb::g_bb59b0_slot_arg == &owner.f_1E8,
          "0x00c47180 always forwards the same slot address");
}

// --- 0x00ba61b0 ----------------------------------------------------------
// Factory: allocate 0x1B0 bytes named "Simulator/cPlanetRecord", construct,
// publish, then write the three header dwords and notify.

void test_ba61b0() {
    alignas(8) std::uint8_t raw[0x1B0];
    std::memset(raw, 0, sizeof(raw));
    osb::OpaqueCPlanetRecord* rec = reinterpret_cast<osb::OpaqueCPlanetRecord*>(raw);
    rec->vtable = osb::make_record_vtable();

    osb::OpaqueCPlanetRecord* out = nullptr;
    osb::reset_log();
    osb::g_alloc_result = rec;
    osb::g_alloc_size = 0;
    osb::g_alloc_type_name = nullptr;
    osb::g_construct_calls = 0;
    osb::g_set_key_value = 0;
    osb::g_register_calls = 0;
    osb::g_notify_calls = 0;
    osb::g_vslot_0_calls = 0;

    osb::SimCore_00ba61b0_make_planet_record(0x00C0FFEEu, &out);

    check_u32(osb::g_alloc_size, 0x1B0u, "0x00ba61b0 allocates 0x1B0 bytes");
    check(osb::g_alloc_type_name != nullptr &&
              std::strcmp(osb::g_alloc_type_name, "Simulator/cPlanetRecord") == 0,
          "0x00ba61b0 passes the literal \"Simulator/cPlanetRecord\"");
    check_u32(static_cast<std::uint32_t>(osb::g_construct_calls), 1u,
              "0x00ba61b0 constructs exactly once");
    check_u32(osb::g_set_key_value, 0x00C0FFEEu,
              "0x00ba61b0 sets +0x184 from the first argument");
    check(out == rec, "0x00ba61b0 stores the record through the out-parameter");
    check_u32(rec->f_08, 0x00C0FFEEu, "0x00ba61b0 writes +0x08 = planet id");
    check_u32(rec->f_0C, 0x5220CB8u, "0x00ba61b0 writes +0x0C = 0x5220CB8");
    check_u32(rec->f_10, 1u, "0x00ba61b0 writes +0x10 = 1");
    check_u32(static_cast<std::uint32_t>(osb::g_vslot_0_calls), 1u,
              "0x00ba61b0 calls vtable slot +0x00 once");
    check_u32(static_cast<std::uint32_t>(osb::g_register_calls), 1u,
              "0x00ba61b0 calls 0x006AC040 once");
    check_u32(static_cast<std::uint32_t>(osb::g_notify_calls), 1u,
              "0x00ba61b0 calls 0x006AD010 once");

    // Call order, read off the disassembly: allocate, construct, out-pointer,
    // set +0x184, header triple, slot +0x00, 0x006AC040, 0x006AD010.
    check(osb::log_count() == 6, "0x00ba61b0 records the full call sequence");
    check(std::strstr(osb::log_entry(0), "f473a0") != nullptr,
          "0x00ba61b0 allocates first");
    check(std::strstr(osb::log_entry(1), "b8e180") != nullptr,
          "0x00ba61b0 constructs second");
    check(std::strstr(osb::log_entry(2), "b8da80") != nullptr,
          "0x00ba61b0 sets the key third");
    check(std::strstr(osb::log_entry(3), "record_vslot_0") != nullptr,
          "0x00ba61b0 calls the virtual slot +0x00 after the header triple");
    check(std::strstr(osb::log_entry(4), "6ac040") != nullptr,
          "0x00ba61b0 registers after the virtual slot +0x00 call");
    check(std::strstr(osb::log_entry(5), "6ad010") != nullptr,
          "0x00ba61b0 notifies last");

    // Allocation failure is NOT exercised: the original has no guard for it.
    // 0x00BA61D7 zeroes EAX, 0x00BA61E6 stores 0 through the out-pointer, and
    // 0x00BA61ED then reloads it and writes to [EAX + 8] -- a null write at
    // address 8. The reconstruction reproduces that unchecked dereference
    // rather than inventing a guard the binary does not have, so this path
    // cannot be asserted in a runnable test.
}

}  // namespace

int main() {
    test_c0b780();
    test_b8dad0();
    test_c47180();
    test_ba61b0();
    osb::run_tiers_and_session_model_tests();
    if (g_failures == 0) {
        std::printf("b08 model tests: all assertions passed\n");
        return 0;
    }
    std::printf("b08 model tests: %d failure(s)\n", g_failures);
    return 1;
}
