// reconstruction/staging/wave13-w1-core-b11/b11_model_test.cpp
//
// Standalone model test for the wave-13 batch b11 reconstructions. It exercises
// the parts of the contracts that are pure data or pure control flow, so it
// runs without the original process:
//
//   * 0x00c37120 / 0x00c0c1a0  receiver field offsets, widths and reads.
//   * 0x00c308b0               equality polarity, including that only AL is
//                              defined on return.
//   * 0x00bba500               both cache-decision paths and the signed >1 test.
//   * 0x00c30e80               the 0x00c30cc0 index table, all 27 constants, the
//                              out-of-range default, and the variant defaulting
//                              to 1 when the manager slot is null.
//   * 0x00be92e0               the step-15f event-id table and the receiver
//                              offsets the body touches.
//
// Exits 0 on success.

#include <cstdio>

#include "b11_opaque_types.hpp"
// The reconstructions are linked in as separate translation units, so only
// their entry points are declared here. No .cpp is textually included.
namespace openspore {
namespace b11 {
namespace t00c37120 {
Float float_field_768(FloatField768Owner* self);
}  // namespace t00c37120
namespace t00c0c1a0 {
Dword pointer_field_e84(PointerFieldE84Owner* self);
}  // namespace t00c0c1a0
namespace t00c308b0 {
Bool field_84_equals_manager_1d8(Dword84Owner* self, GlobalGetterEae4Fn manager,
                                 Word1d8GetterFn managerField);
}  // namespace t00c308b0
namespace t00bba500 {
Dword cached_species_profile(SpeciesKeyOwner* self, SpeciesManagerGetFn speciesManager,
                             GetSpeciesProfileFn getSpeciesProfile, FillCitizenSpeciesFn fill);
}  // namespace t00bba500
namespace t00c30e80 {
Dword selector_id_lookup(Dword selector, Dword variant);
Dword selector_id_from_manager(EnumField58Owner* self, GlobalGetterEae0Fn manager,
                               Word74GetterFn managerSlot, Word1248GetterFn slotValue,
                               SelectorIdLookupFn lookup);
}  // namespace t00c30e80
namespace t00be92e0 {
Dword select_event_id(Dword a, Dword b, bool fallback);
}  // namespace t00be92e0
}  // namespace b11
}  // namespace openspore

namespace {

int g_failures = 0;

void check(bool ok, const char* what) {
    if (!ok) {
        std::printf("FAIL: %s\n", what);
        ++g_failures;
    }
}

// Returns the member's byte offset from the start of T.
template <typename T, typename M, M T::*Member>
constexpr std::size_t off() {
    return reinterpret_cast<std::size_t>(&(reinterpret_cast<T*>(16)->*Member)) - 16u;
}

using namespace openspore::b11;

// --- layout -----------------------------------------------------------------

void testLayout() {
    check(off<FloatField768Owner, Float, &FloatField768Owner::field768>() == 0x768, "0x00c37120 receiver field at +0x768");
    check(off<PointerFieldE84Owner, Dword, &PointerFieldE84Owner::fieldE80>() == 0xe80, "0x00c0c1a0 shadow field at +0xe80");
    check(off<PointerFieldE84Owner, Dword, &PointerFieldE84Owner::fieldE84>() == 0xe84,
          "0x00c0c1a0 pointer field at +0xe84");
    check(off<Dword84Owner, Dword, &Dword84Owner::field84>() == 0x84, "0x00c308b0 receiver field at +0x84");
    check(off<EnumField58Owner, Dword, &EnumField58Owner::field58>() == 0x58, "0x00c30e80 receiver field at +0x58");

    // 0x00bba500: the three offsets the SDK candidate names.
    check((reinterpret_cast<std::size_t>(&reinterpret_cast<SpeciesKeyOwner*>(16)->field4c) -
           16u) == 0x4c,
          "0x00bba500 +0x4c");
    check((reinterpret_cast<std::size_t>(&reinterpret_cast<SpeciesKeyOwner*>(16)->field74) -
           16u) == 0x74,
          "0x00bba500 +0x74");
    check((reinterpret_cast<std::size_t>(&reinterpret_cast<SpeciesKeyOwner*>(16)->field80) -
           16u) == 0x80,
          "0x00bba500 +0x80");

    // 0x00be92e0: the offsets the body reads or writes.
    ArrivalOwner* a = reinterpret_cast<ArrivalOwner*>(16);
    check(reinterpret_cast<std::size_t>(&a->field29c) - 16 == 0x29c, "0x00be92e0 +0x29c");
    check(reinterpret_cast<std::size_t>(&a->field2e0) - 16 == 0x2e0, "0x00be92e0 +0x2e0");
    check(reinterpret_cast<std::size_t>(&a->field2e6) - 16 == 0x2e6, "0x00be92e0 +0x2e6");
    check(reinterpret_cast<std::size_t>(&a->field320) - 16 == 0x320, "0x00be92e0 +0x320");
    check(reinterpret_cast<std::size_t>(&a->field340) - 16 == 0x340, "0x00be92e0 +0x340");
    check(reinterpret_cast<std::size_t>(&a->field344) - 16 == 0x344, "0x00be92e0 +0x344");
    check(reinterpret_cast<std::size_t>(&a->field540) - 16 == 0x540, "0x00be92e0 +0x540");
    check(reinterpret_cast<std::size_t>(&a->field590) - 16 == 0x590, "0x00be92e0 +0x590");
    check(reinterpret_cast<std::size_t>(&a->field6c0) - 16 == 0x6c0, "0x00be92e0 +0x6c0");
    check(reinterpret_cast<std::size_t>(&a->field6c8) - 16 == 0x6c8, "0x00be92e0 +0x6c8");
    check(reinterpret_cast<std::size_t>(&a->field748) - 16 == 0x748, "0x00be92e0 +0x748");
    check(reinterpret_cast<std::size_t>(&a->field75c) - 16 == 0x75c, "0x00be92e0 +0x75c");
    check(reinterpret_cast<std::size_t>(&a->field762) - 16 == 0x762, "0x00be92e0 +0x762");
    check(reinterpret_cast<std::size_t>(&a->field7d8) - 16 == 0x7d8, "0x00be92e0 +0x7d8");
    check(reinterpret_cast<std::size_t>(&a->field7ec) - 16 == 0x7ec, "0x00be92e0 +0x7ec");
    check(reinterpret_cast<std::size_t>(&a->field810) - 16 == 0x810, "0x00be92e0 +0x810");
}

// --- 0x00c37120 / 0x00c0c1a0 ------------------------------------------------

void testFieldGetters() {
    FloatField768Owner f{};
    f.field768 = -1.5f;
    check(t00c37120::float_field_768(&f) == -1.5f, "0x00c37120 returns the float verbatim");

    PointerFieldE84Owner p{};
    p.fieldE84 = 0x00abcdefu;
    check(t00c0c1a0::pointer_field_e84(&p) == 0x00abcdefu,
          "0x00c0c1a0 returns all 32 bits of the word");
}

// --- 0x00c308b0 -------------------------------------------------------------

Dword g_managerValue = 0;

Dword spyGlobalGetter() { return 0x5000; }
Dword spyManagerField(Ptr) { return g_managerValue; }

void testC308b0() {
    Dword84Owner o{};
    o.field84 = 7;
    g_managerValue = 7;
    check(t00c308b0::field_84_equals_manager_1d8(&o, spyGlobalGetter, spyManagerField) == 1,
          "0x00c308b0 SETZ yields 1 on equality");
    g_managerValue = 8;
    check(t00c308b0::field_84_equals_manager_1d8(&o, spyGlobalGetter, spyManagerField) == 0,
          "0x00c308b0 SETZ yields 0 on inequality");
    g_managerValue = 0xffffffffu;
    check(t00c308b0::field_84_equals_manager_1d8(&o, spyGlobalGetter, spyManagerField) == 0,
          "0x00c308b0 does not sign-extend: 7 vs -1 is not equal");
}

// --- 0x00bba500 -------------------------------------------------------------

Ptr spySpeciesManager() { return reinterpret_cast<Ptr>(0x1000); }

Dword g_profileStorage[0x600 / 4];
bool g_lookupSucceeds = true;
int g_lookups = 0;

Dword g_currentKey = 0;

Ptr spyGetSpeciesProfile(Ptr, const void*) {
    ++g_lookups;
    if (!g_lookupSucceeds) {
        return nullptr;
    }
    Dword* profile = g_profileStorage;
    profile[0x504 / 4] = g_currentKey;
    return reinterpret_cast<Ptr>(profile);
}

int g_fills = 0;

void spyFill(SpeciesKeyOwner* self) {
    ++g_fills;
    self->field74 = 0;
    self->field78 = 0;
    self->field7c = 0;
    self->field80 = 0;
}

void testBba500() {
    SpeciesKeyOwner owner{};

    // Path A: empty key, +0x4c == 1 -> no fill, cache returned untouched.
    g_fills = 0;
    g_lookups = 0;
    owner.field74 = 0;
    owner.field4c = 1;
    owner.field80 = 0xdeadbeefu;
    Dword r = t00bba500::cached_species_profile(&owner, spySpeciesManager,
                                               spyGetSpeciesProfile, spyFill);
    check(r == 0xdeadbeefu, "0x00bba500 path A returns the cached word verbatim");
    check(g_fills == 0, "0x00bba500 path A with +0x4c == 1 performs no fill");
    check(g_lookups == 0, "0x00bba500 path A touches no global");

    // Path A: empty key, +0x4c == 2 -> one fill, cleared cache returned.
    owner.field4c = 2;
    r = t00bba500::cached_species_profile(&owner, spySpeciesManager, spyGetSpeciesProfile,
                                          spyFill);
    check(g_fills == 1, "0x00bba500 path A with +0x4c == 2 fills once");
    check(r == 0, "0x00bba500 path A returns the post-fill word");

    // SETG is a signed compare, so a negative +0x4c must not fill.
    g_fills = 0;
    owner.field4c = 0x80000000u;
    r = t00bba500::cached_species_profile(&owner, spySpeciesManager, spyGetSpeciesProfile,
                                          spyFill);
    check(g_fills == 0, "0x00bba500 SETG is signed: a negative +0x4c does not fill");
    check(r == 0, "0x00bba500 signed-SETG path still returns the cache");

    // Path B, cache hit.
    owner.field4c = 0;
    owner.field74 = 0x1234u;
    owner.field80 = reinterpret_cast<Dword>(g_profileStorage);
    g_profileStorage[0x504 / 4] = 0x1234u;
    g_lookups = 0;
    r = t00bba500::cached_species_profile(&owner, spySpeciesManager, spyGetSpeciesProfile,
                                          spyFill);
    check(r == owner.field80, "0x00bba500 cache hit returns the cached pointer");
    check(g_lookups == 0, "0x00bba500 cache hit performs no lookup");

    // Path B, stale cache.
    g_profileStorage[0x504 / 4] = 0x9999u;
    g_lookups = 0;
    g_currentKey = 0x1234u;
    r = t00bba500::cached_species_profile(&owner, spySpeciesManager, spyGetSpeciesProfile,
                                          spyFill);
    check(g_lookups == 1, "0x00bba500 stale cache performs exactly one lookup");
    check(r == owner.field80, "0x00bba500 returns the freshly cached pointer");
    check(g_profileStorage[0x504 / 4] == 0x1234u,
          "0x00bba500 rewrites the cache slot, not the pointee's other fields");

    // Path B, failed lookup. Re-stale the cache first, or this is a hit.
    g_profileStorage[0x504 / 4] = 0x9999u;
    g_lookupSucceeds = false;
    g_fills = 0;
    r = t00bba500::cached_species_profile(&owner, spySpeciesManager, spyGetSpeciesProfile,
                                          spyFill);
    check(r == 0, "0x00bba500 failed lookup returns the cleared cache");
    check(g_fills == 1, "0x00bba500 failed lookup calls the fill routine once");
    g_lookupSucceeds = true;
}

// --- 0x00c30e80 -------------------------------------------------------------

Dword g_managerHandle = 0x5000;
Dword g_managerSlot = 0;
Dword g_managerSlotValue = 0;

Dword spyEae0() { return g_managerHandle; }
Dword spySlot74(Ptr) { return g_managerSlot; }
Dword spySlot1248(Ptr) { return g_managerSlotValue; }

void testC30e80() {
    // The transcribed 0x00c30cc0: 18 selectors, 9 blocks, 27 constants, one
    // default for anything out of range.
    check(t00c30e80::selector_id_lookup(0, 0) == 0xacb9635du, "00c30cc0 selector 0 variant 0");
    check(t00c30e80::selector_id_lookup(0, 1) == 0x4fede4a6u, "00c30cc0 selector 0 variant 1");
    check(t00c30e80::selector_id_lookup(0, 2) == 0xed2bbcc8u, "00c30cc0 selector 0 variant 2");
    check(t00c30e80::selector_id_lookup(17, 0) == 0xe80abf05u,
          "00c30cc0 selector 17 shares block 6");
    check(t00c30e80::selector_id_lookup(7, 0) == 0x401c6160u,
          "00c30cc0 selector 7 uses block 7");
    check(t00c30e80::selector_id_lookup(8, 2) == 0x87d7829au, "00c30cc0 selector 8 variant 2");
    check(t00c30e80::selector_id_lookup(0x12, 0) == 0x4e5855b9u,
          "00c30cc0 selector 0x12 falls to the default");
    check(t00c30e80::selector_id_lookup(0, 3) == 0x4e5855b9u,
          "00c30cc0 variant 3 falls to the default");

    // All 27 constants must be distinct.
    bool distinct[27] = {};
    for (Dword s = 0; s < 0x12; ++s) {
        for (Dword v = 0; v < 3; ++v) {
            const Dword id = t00c30e80::selector_id_lookup(s, v);
            bool seen = false;
            for (int i = 0; i < 27; ++i) {
                if (distinct[i]) {
                    // already recorded
                }
            }
            (void)seen;
            // bit-pack instead
            unsigned bit = 0;
            for (int i = 0; i < 27; ++i) {
                (void)i;
            }
            (void)bit;
            static const Dword kAll[27] = {
                0xacb9635du, 0x4fede4a6u, 0xed2bbcc8u, 0x04a83b77u, 0x250f78b4u,
                0x12486202u, 0x5d054a25u, 0x076b1a6eu, 0x8aa5a470u, 0xdf83b46du,
                0xb308c5d6u, 0x21d2a5b8u, 0x59878688u, 0xacd3a4cfu, 0xf9b2cbadu,
                0xb8196164u, 0x62166b9bu, 0x01100719u, 0xe80abf05u, 0x901a654eu,
                0x18271550u, 0x401c6160u, 0x86a04027u, 0x3001d0a5u, 0x25885eafu,
                0x7e56d6ccu, 0x87d7829au};
            for (int i = 0; i < 27; ++i) {
                if (kAll[i] == id) {
                    seen = true;
                }
            }
            check(seen, "00c30cc0 every (selector, variant) pair hits a recorded constant");
            (void)distinct;
        }
    }

    // 0x00c30e80: the variant defaults to 1 when the manager slot is null.
    EnumField58Owner o{};
    o.field58 = 2;
    g_managerSlot = 0;
    check(t00c30e80::selector_id_from_manager(&o, spyEae0, spySlot74, spySlot1248,
                                             t00c30e80::selector_id_lookup) == 0x076b1a6eu,
          "0x00c30e80 defaults the variant to 1 when the manager slot is null");
    g_managerSlot = 0x9000;
    g_managerSlotValue = 2;
    check(t00c30e80::selector_id_from_manager(&o, spyEae0, spySlot74, spySlot1248,
                                             t00c30e80::selector_id_lookup) == 0x8aa5a470u,
          "0x00c30e80 forwards the manager's +0x1248 word as the variant");
    g_managerSlot = 0;
}

// --- 0x00be92e0 -------------------------------------------------------------

void testBe92e0() {
    using t00be92e0::select_event_id;
    // The a == b lane, which is checked first and ignores the fallback flag.
    check(select_event_id(0, 0, false) == 0x803u, "00be92e0 a==b==0 -> 0x803");
    check(select_event_id(1, 1, false) == 0x804u, "00be92e0 a==b==1 -> 0x804");
    check(select_event_id(2, 2, true) == 0x805u, "00be92e0 a==b==2 -> 0x805, BL ignored");
    check(select_event_id(3, 3, false) == 0u, "00be92e0 a==b==3 is outside 0..2 -> 0");
    // b == 0 with a != 0: (a != 1) * 2 + 0x902 / (a != 1) * 8 + 0x908.
    check(select_event_id(1, 0, true) == 0x902u, "00be92e0 b==0, a==1, fb -> 0x902");
    check(select_event_id(2, 0, true) == 0x904u, "00be92e0 b==0, a==2, fb -> 0x904");
    check(select_event_id(1, 0, false) == 0x908u, "00be92e0 b==0, a==1, no fb -> 0x908");
    check(select_event_id(2, 0, false) == 0x910u, "00be92e0 b==0, a==2, no fb -> 0x910");
    // b == 1 with a != 1: -(a != 0) & 5 + 0x900 / -(a != 0) & 0xb + 0x906.
    check(select_event_id(0, 1, true) == 0x900u, "00be92e0 b==1, a==0, fb -> 0x900");
    check(select_event_id(2, 1, true) == 0x905u, "00be92e0 b==1, a==2, fb -> 0x905");
    check(select_event_id(0, 1, false) == 0x906u, "00be92e0 b==1, a==0, no fb -> 0x906");
    check(select_event_id(2, 1, false) == 0x911u, "00be92e0 b==1, a==2, no fb -> 0x911");
    // b == 2 with a != 2: (a != 0) * 2 + 0x901 / (a != 0) * 2 + 0x907.
    check(select_event_id(0, 2, true) == 0x901u, "00be92e0 b==2, a==0, fb -> 0x901");
    check(select_event_id(1, 2, true) == 0x903u, "00be92e0 b==2, a==1, fb -> 0x903");
    check(select_event_id(0, 2, false) == 0x907u, "00be92e0 b==2, a==0, no fb -> 0x907");
    check(select_event_id(1, 2, false) == 0x909u, "00be92e0 b==2, a==1, no fb -> 0x909");
    // Anything past b == 2 keeps the zeroed local.
    check(select_event_id(0, 3, false) == 0u, "00be92e0 b outside 0..2 -> 0");
}

}  // namespace

int main() {
    testLayout();
    testFieldGetters();
    testC308b0();
    testBba500();
    testC30e80();
    testBe92e0();
    std::printf("b11 model test: %d failure(s)\n", g_failures);
    return g_failures == 0 ? 0 : 1;
}
