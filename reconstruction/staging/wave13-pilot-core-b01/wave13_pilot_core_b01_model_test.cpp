// Standalone model test for package wave13-pilot-core-b01.
//
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//           -I reconstruction/staging/wave13-pilot-core-b01 \
//           reconstruction/staging/wave13-pilot-core-b01/*.cpp -o /tmp/b01-model
//
// It supplies recording stubs for every unresolved port and asserts the
// invariants that were read out of the original bytes. It claims no runtime
// equivalence with the shipped build: no differential trace exists.

#include "wave13_pilot_core_b01_types.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace openspore::reconstruction::wave13_pilot_core_b01 {
namespace {

int g_failures = 0;

void check(bool condition, const char* what) {
    if (!condition) {
        std::printf("FAIL %s\n", what);
        ++g_failures;
    }
}

// --- recording port state ---------------------------------------------------

struct ServiceCall {
    void* service;
    Dword arg[7];
    int count;
};

ServiceCall g_service_call{};
Dword* g_service_slot = nullptr;
Dword g_field_184 = 0;
const void* g_cached_object = nullptr;
Dword g_cached_field_84 = 0;
int g_simulator_service_queries = 0;
int g_flush_calls = 0;
int g_sync_calls = 0;
std::vector<void*> g_accepted_query_order;
std::uint8_t g_accept_next = 0;

OpaqueMission* g_mission = nullptr;
OpaqueCombatant* g_combatant = nullptr;
OpaqueStarRecord* g_star = nullptr;
OpaqueCursor* g_cursor = nullptr;

// Slot spies. Each records the receiver and arguments it was handed.
struct MissionSlotSpy {
    Dword slot_0f8_result = 0;
    Dword slot_0fc_result = 0;
    int slot_0f8_calls = 0;
    int slot_0fc_calls = 0;
    int slot_198_calls = 0;
    int slot_19c_calls = 0;
    Dword last_198_arg = 0xdeadbeef;
    const OpaqueMission* last_10c_arg1 = nullptr;
    Dword last_10c_arg2 = 0xffffffffu;
    Dword last_10c_arg3 = 0xffffffffu;
    Dword last_10c_result = 0x11111111u;
    Dword last_0a4_result = 0x22222222u;
    int slot_10c_calls = 0;
    int slot_0a4_calls = 0;
};

MissionSlotSpy g_spy;

Dword W13_THISCALL spy_0f8(OpaqueMission* self) {
    (void)self;
    ++g_spy.slot_0f8_calls;
    return g_spy.slot_0f8_result;
}

Dword W13_THISCALL spy_0fc(OpaqueMission* self) {
    (void)self;
    ++g_spy.slot_0fc_calls;
    return g_spy.slot_0fc_result;
}

Dword W13_THISCALL spy_198(OpaqueMission* self, std::uint8_t value) {
    (void)self;
    ++g_spy.slot_198_calls;
    g_spy.last_198_arg = value;
    return 0;
}

void W13_THISCALL spy_19c(OpaqueMission* self) {
    (void)self;
    ++g_spy.slot_19c_calls;
}

Dword W13_THISCALL spy_10c(OpaqueMission* self, const OpaqueMission* arg1,
                           Dword arg2, Dword arg3) {
    (void)self;
    ++g_spy.slot_10c_calls;
    g_spy.last_10c_arg1 = arg1;
    g_spy.last_10c_arg2 = arg2;
    g_spy.last_10c_arg3 = arg3;
    return g_spy.last_10c_result;
}

Dword W13_THISCALL spy_0a4(OpaqueMission* self) {
    (void)self;
    ++g_spy.slot_0a4_calls;
    return g_spy.last_0a4_result;
}

float W13_THISCALL spy_58(OpaqueCombatant* self) {
    (void)self;
    return 4.0f;
}

}  // namespace

// --- port implementations ---------------------------------------------------
// These must have external linkage: the reconstruction translation units
// reference them through the declarations in the package header.

Dword* W13_STDCALL port_00b3d4a0_read_service_slot_0167eb44() {
    return g_service_slot;
}

const void* W13_THISCALL port_00c451e0_get_cached_sub_object(OpaqueMission*) {
    return g_cached_object;
}

Dword port_00ce6950_read_field_184(const void*) {
    return g_field_184;
}

void* W13_THISCALL port_00aeb7a0_register_record(void* service, Dword arg1,
                                                 Dword arg2, Dword arg3,
                                                 Dword arg4, Dword arg5,
                                                 Dword arg6, Dword arg7) {
    g_service_call.service = service;
    g_service_call.arg[0] = arg1;
    g_service_call.arg[1] = arg2;
    g_service_call.arg[2] = arg3;
    g_service_call.arg[3] = arg4;
    g_service_call.arg[4] = arg5;
    g_service_call.arg[5] = arg6;
    g_service_call.arg[6] = arg7;
    g_service_call.count = 1;
    return nullptr;
}

void* port_01046fc0_get_simulator_service() {
    ++g_simulator_service_queries;
    return g_service_slot;
}

void W13_THISCALL port_01048ce0_flush_pending(void*) {
    ++g_flush_calls;
}

void W13_THISCALL port_00bba640_sync_planet_vector(OpaqueStarRecord*) {
    ++g_sync_calls;
}

std::uint8_t W13_STDCALL port_00c02600_is_accepted_element(void* element) {
    g_accepted_query_order.push_back(element);
    return g_accept_next;
}

namespace {

// --- fixtures ---------------------------------------------------------------

void install_mission_vtable(const void** table) {
    for (int i = 0; i < 0x1a4 / 4; ++i) {
        table[i] = nullptr;
    }
    table[0xf8 / 4] = reinterpret_cast<const void*>(&spy_0f8);
    table[0xfc / 4] = reinterpret_cast<const void*>(&spy_0fc);
    table[0x198 / 4] = reinterpret_cast<const void*>(&spy_198);
    table[0x19c / 4] = reinterpret_cast<const void*>(&spy_19c);
    table[0x10c / 4] = reinterpret_cast<const void*>(&spy_10c);
    table[0xa4 / 4] = reinterpret_cast<const void*>(&spy_0a4);
}

void test_00c471c0() {
    const void* table[0x1a4 / 4];
    install_mission_vtable(table);

    std::uint8_t storage[0x184] = {};
    auto* mission = reinterpret_cast<OpaqueMission*>(storage);
    mission->vftable = table;
    g_mission = mission;

    // Both predicates false, hide flag clear -> slot +0x198 receives 0.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 0;
    g_spy.slot_0fc_result = 0;
    g_flush_calls = 0;
    g_simulator_service_queries = 0;
    mission->field_130 = 0;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_0f8_calls == 1, "0x00c471c0 queries slot +0xf8 once");
    check(g_spy.slot_0fc_calls == 1, "0x00c471c0 queries slot +0xfc once");
    check(g_spy.slot_198_calls == 1, "0x00c471c0 takes the +0x198 exit");
    check(g_spy.slot_19c_calls == 0, "0x00c471c0 does not take the +0x19c exit");
    check(g_spy.last_198_arg == 0, "0x00c471c0 passes predicate 0 to +0x198");
    check(g_flush_calls == 1, "0x00c471c0 flushes exactly once");
    check(g_simulator_service_queries == 1,
          "0x00c471c0 queries the service accessor exactly once");

    // Slot +0xf8 true short-circuits: +0xfc is never consulted.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 1;
    g_spy.slot_0fc_result = 0;
    g_flush_calls = 0;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_0f8_calls == 1, "0x00c471c0 slot +0xf8 queried");
    check(g_spy.slot_0fc_calls == 0, "0x00c471c0 short-circuits slot +0xfc");
    check(g_spy.slot_198_calls == 1, "0x00c471c0 still exits through +0x198");
    check(g_spy.last_198_arg == 1, "0x00c471c0 passes predicate 1 to +0x198");

    // Slot +0xf8 false, slot +0xfc true -> predicate 1, no short circuit gap.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 0;
    g_spy.slot_0fc_result = 1;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_0fc_calls == 1, "0x00c471c0 consults +0xfc when +0xf8 is 0");
    check(g_spy.last_198_arg == 1, "0x00c471c0 ORs the two predicates");

    // Hide flag (bit 1 of +0x130) set and predicate 0 -> slot +0x19c, no +0x198.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 0;
    g_spy.slot_0fc_result = 0;
    g_flush_calls = 0;
    mission->field_130 = 0x2;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_19c_calls == 1, "0x00c471c0 takes the +0x19c exit");
    check(g_spy.slot_198_calls == 0, "0x00c471c0 skips +0x198 on that exit");
    check(g_flush_calls == 1, "0x00c471c0 flushes on the +0x19c exit too");

    // Hide flag set but predicate 1 -> back to +0x198.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 1;
    mission->field_130 = 0x2;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_198_calls == 1,
          "0x00c471c0 prefers +0x198 when the predicate is already set");
    check(g_spy.slot_19c_calls == 0, "0x00c471c0 skips +0x19c then");

    // Only bit 1 of the dword matters.
    g_spy = MissionSlotSpy{};
    g_spy.slot_0f8_result = 0;
    g_spy.slot_0fc_result = 0;
    mission->field_130 = 0x1;
    SimMission_00c471c0_settleStateArtifacts(mission);
    check(g_spy.slot_198_calls == 1, "0x00c471c0 ignores bit 0 of +0x130");
    mission->field_130 = 0;
}

void test_00c472e0() {
    const void* table[0x1a4 / 4];
    install_mission_vtable(table);

    std::uint8_t mission_storage[0x184] = {};
    std::uint8_t parent_storage[0x184] = {};
    std::uint8_t planet_storage[0x140] = {};
    std::uint8_t cached_storage[0x88] = {};

    auto* mission = reinterpret_cast<OpaqueMission*>(mission_storage);
    auto* parent = reinterpret_cast<OpaqueMission*>(parent_storage);
    auto* planet = reinterpret_cast<Dword*>(planet_storage);
    auto* cached = reinterpret_cast<Dword*>(cached_storage);

    mission->vftable = table;
    parent->vftable = table;
    planet[0x13c / 4] = reinterpret_cast<Dword>(0x00c0ffeeu);
    mission->field_09c = planet;
    cached[0x84 / 4] = 0x0badf00du;
    g_cached_object = cached;
    g_cached_field_84 = 0x0badf00du;
    g_field_184 = 0x00c0ffeeu;
    g_spy = MissionSlotSpy{};
    g_spy.last_10c_result = 0x00abcdefu;
    g_spy.last_0a4_result = 0x00112233u;
    static Dword service_storage = 0;
    g_service_slot = &service_storage;
    g_service_call = ServiceCall{};

    mission->field_17c = nullptr;
    SimMission_00c472e0_publishStateArtifacts(mission);
    check(g_spy.slot_10c_calls == 1, "0x00c472e0 calls slot +0x10c once");
    check(g_spy.slot_0a4_calls == 1, "0x00c472e0 calls slot +0xa4 once");
    check(g_spy.last_10c_arg1 == mission,
          "0x00c472e0 self-substitutes a null sub-object at +0x17c");
    check(g_spy.last_10c_arg2 == 0 && g_spy.last_10c_arg3 == 0,
          "0x00c472e0 passes two zero words to slot +0x10c");
    check(g_service_call.count == 1, "0x00c472e0 reaches the registry port");
    check(g_service_call.service == &service_storage,
          "0x00c472e0 passes the 0x0167eb44 slot as the port receiver");
    check(g_service_call.arg[0] == 0x0badf00du,
          "0x00c472e0 arg1 is the cached sub-object dword at +0x84");
    check(g_service_call.arg[1] == 0x00c0ffeeu,
          "0x00c472e0 arg2 is the +0x184 read of the planet record");
    check(g_service_call.arg[2] == 0x00112233u,
          "0x00c472e0 arg3 is the slot +0xa4 result");
    check(g_service_call.arg[3] == 0x00abcdefu,
          "0x00c472e0 arg4 is the slot +0x10c result");
    check(g_service_call.arg[4] == reinterpret_cast<Dword>(mission),
          "0x00c472e0 arg5 is the self-substituted sub-object");
    check(g_service_call.arg[5] == 0 && g_service_call.arg[6] == 0,
          "0x00c472e0 args 6 and 7 are zero");

    mission->field_17c = parent;
    g_service_call = ServiceCall{};
    g_spy = MissionSlotSpy{};
    g_spy.last_10c_result = 0x00abcdefu;
    g_spy.last_0a4_result = 0x00112233u;
    SimMission_00c472e0_publishStateArtifacts(mission);
    check(g_spy.last_10c_arg1 == parent,
          "0x00c472e0 uses the +0x17c sub-object when it is non-null");
    check(g_service_call.arg[4] == reinterpret_cast<Dword>(parent),
          "0x00c472e0 arg5 follows the same sub-object");
}

void test_00bfc490() {
    const void* table[0x58 / 4 + 1];
    for (int i = 0; i <= 0x58 / 4; ++i) {
        table[i] = nullptr;
    }
    table[0x58 / 4] = reinterpret_cast<const void*>(&spy_58);

    std::uint8_t storage[0xc8] = {};
    auto* combatant = reinterpret_cast<OpaqueCombatant*>(storage);
    combatant->vftable = table;
    g_combatant = combatant;

    combatant->field_038 = 10.0f;
    check(Combatant_00bfc490_healthFraction(combatant) == 2.5f,
          "0x00bfc490 divides field +0x38 by the slot +0x58 result");

    combatant->field_038 = 0.0f;
    check(Combatant_00bfc490_healthFraction(combatant) == 0.0f,
          "0x00bfc490 returns zero for a zero numerator");
}

void test_00bbaa60() {
    static void* slots[4] = {nullptr, nullptr, nullptr, nullptr};
    std::uint8_t storage[0xb0] = {};
    auto* star = reinterpret_cast<OpaqueStarRecord*>(storage);
    g_star = star;
    star->field_084.begin = slots;
    star->field_0ac = 4;

    g_sync_calls = 0;
    void* got = StarRecord_00bbaa60_getPlanetRecordByIndex(star, 2);
    check(g_sync_calls == 1, "0x00bbaa60 syncs the vector before indexing");
    check(got == slots[2], "0x00bbaa60 returns mPlanets[index]");

    got = StarRecord_00bbaa60_getPlanetRecordByIndex(star, 0);
    check(got == slots[0], "0x00bbaa60 honours index 0");
}

void test_00bb9b00() {
    std::uint8_t storage[0xb0] = {};
    auto* star = reinterpret_cast<OpaqueStarRecord*>(storage);
    g_star = star;
    star->field_05c = 0x00000005u;

    StarRecord_00bb9b00_setFlagsMask(star, 0x2u, 1);
    check(star->field_05c == 0x00000007u, "0x00bb9b00 ORs the mask when setting");
    StarRecord_00bb9b00_setFlagsMask(star, 0x2u, 0);
    check(star->field_05c == 0x00000005u, "0x00bb9b00 clears the mask");
    StarRecord_00bb9b00_setFlagsMask(star, 0xffffffffu, 1);
    check(star->field_05c == 0xffffffffu, "0x00bb9b00 sets every bit");
    StarRecord_00bb9b00_setFlagsMask(star, 0xffffffffu, 0);
    check(star->field_05c == 0x00000000u, "0x00bb9b00 clears every bit");
    StarRecord_00bb9b00_setFlagsMask(star, 0u, 1);
    check(star->field_05c == 0x00000000u, "0x00bb9b00 with a zero mask is a no-op");
}

void test_00b3d850() {
    static void* elements[8] = {};
    OpaqueCursor cursor{};
    g_cursor = &cursor;

    cursor.cursor = elements;
    cursor.end = elements + 4;
    cursor.owner = nullptr;
    g_accept_next = 0;
    g_accepted_query_order.clear();
    OpaqueCursor* ret = Cursor_00b3d850_advanceToAccepted(&cursor);
    check(ret == &cursor, "0x00b3d850 returns the receiver handle");
    check(cursor.cursor == elements + 4, "0x00b3d850 stops at the end pointer");
    check(g_accepted_query_order.size() == 3,
          "0x00b3d850 never re-tests the slot it started on");

    cursor.cursor = elements;
    g_accept_next = 0;
    g_accepted_query_order.clear();
    Cursor_00b3d850_advanceToAccepted(&cursor);
    // Ask for the third visited element to be accepted.
    g_accept_next = 1;
    cursor.cursor = elements;
    g_accepted_query_order.clear();
    g_accept_next = 0;
    Cursor_00b3d850_advanceToAccepted(&cursor);
    check(cursor.cursor == elements + 4, "0x00b3d850 exhausts when nothing matches");

    cursor.cursor = elements;
    g_accept_next = 1;
    g_accepted_query_order.clear();
    Cursor_00b3d850_advanceToAccepted(&cursor);
    check(cursor.cursor == elements + 1, "0x00b3d850 stops on the first accepted slot");
    check(g_accepted_query_order.size() == 1, "0x00b3d850 asks the port once");
    check(g_accepted_query_order[0] == elements[1],
          "0x00b3d850 asks about the slot it advanced onto, not the previous one");

    // The body advances before it tests and never compares the incoming
    // cursor against the end pointer, so a handle whose cursor already equals
    // its end still steps one slot forward and queries that slot. Accepted on
    // the first query here, otherwise the original loop would not terminate.
    cursor.cursor = elements + 4;
    cursor.end = elements + 4;
    g_accept_next = 1;
    g_accepted_query_order.clear();
    Cursor_00b3d850_advanceToAccepted(&cursor);
    check(cursor.cursor == elements + 5,
          "0x00b3d850 steps past a handle that starts already exhausted");
    check(g_accepted_query_order.size() == 1,
          "0x00b3d850 queries the slot it stepped onto, past a stale end pointer");
    check(g_accepted_query_order[0] == elements[5],
          "0x00b3d850 reads the element of the advanced slot");
    cursor.cursor = elements;
    cursor.end = elements + 4;
}

}  // namespace
}  // namespace openspore::reconstruction::wave13_pilot_core_b01

int main() {
    using namespace openspore::reconstruction::wave13_pilot_core_b01;
    (void)g_mission;
    (void)g_combatant;
    (void)g_star;
    (void)g_cursor;
    (void)g_cached_field_84;

    test_00c471c0();
    test_00c472e0();
    test_00bfc490();
    test_00bbaa60();
    test_00bb9b00();
    test_00b3d850();

    if (g_failures != 0) {
        std::printf("%d check(s) failed\n", g_failures);
        return 1;
    }
    std::printf("wave13-pilot-core-b01 model test: all checks passed\n");
    return 0;
}
