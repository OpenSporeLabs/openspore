// wave13-w1-core-b06 — test-only models of the opaque ports.
//
// These bodies are NOT reconstructions.  They are minimal stand-ins that make
// the six reconstructed functions executable so their observable contract can
// be exercised.  Anything a port does that the port declaration in
// sim_core_b06_opaque.hpp does not state is a modelling choice of the test, not
// a claim about the original binary.

#include "sim_core_b06_opaque.hpp"

#include <cstdint>
#include <cstring>

namespace sim_core_b06 {

// The .bss slots the two trivial original accessors read.  Both read 0 in the
// on-disk image (ghidra_read_memory 0x0167EAD4 and 0x0167EAE4), so they start
// at 0 here too and the tests install values explicitly.
static std::uint32_t g_slot_EAD4 = 0;
static std::uint32_t g_slot_EAE4 = 0;
static std::uint32_t g_slot_DAC64 = 0;
static std::uint32_t g_slot_015FD8A8 = 0;

std::uint32_t getGlobalEAD4() { return g_slot_EAD4; }
std::uint32_t getGlobalEAE4() { return g_slot_EAE4; }
std::uint32_t getGlobalDAC64() { return g_slot_DAC64; }
std::uint32_t getGlobal_015FD8A8() { return g_slot_015FD8A8; }

// 0x0156C61C.  Live bytes: 00000000 0156C620 0156C620 00000000.
static OrderedKeyMapNode g_endNode{};
OrderedKeyMap g_internedObjectTable = {0u, &g_endNode, 0u, nullptr};

// The flat node list the model ports index into.
static OrderedKeyMapNode g_nodes[8] = {};
static int g_nodeCount = 0;

void resetInternedObjectTable() {
    g_internedObjectTable.rootOrEnd = 0u;
    g_internedObjectTable.endNode = &g_endNode;
    g_internedObjectTable.count = 0u;
    g_internedObjectTable.rightmost = nullptr;
    std::memset(&g_endNode, 0, sizeof(g_endNode));
    std::memset(g_nodes, 0, sizeof(g_nodes));
    g_nodeCount = 0;
}

static OrderedKeyMapNode* findNode(const OrderedKeyMap* base, std::uint32_t key) {
    for (int i = 0; i < g_nodeCount; ++i) {
        if ((g_nodes[i].key & 0xFFFFFF00u) == (key & 0xFFFFFF00u)) {
            return &g_nodes[i];
        }
    }
    (void)base;
    return nullptr;
}

void port_00e5c780_lookup(OrderedKeyMap* base, const std::uint32_t* key, OrderedKeyMapNode** out) {
    // Models 0x00e5c780's non-inserting walk: exact match wins, otherwise the
    // end sentinel.
    OrderedKeyMapNode* n = findNode(base, *key);
    *out = n ? n : base->endNode;
}

std::uint32_t* port_00dd85c0_at(OrderedKeyMap* base, const std::uint32_t* key) {
    // Models 0x00dd85c0: insert when absent, return &node->value.
    OrderedKeyMapNode* n = findNode(base, *key);
    if (!n) {
        if (g_nodeCount >= 8) {
            return &g_endNode.value;
        }
        n = &g_nodes[g_nodeCount++];
        std::memset(n, 0, sizeof(*n));
        n->key = *key & 0xFFFFFF00u;
        ++base->count;
    }
    return &n->value;
}

std::uint32_t port_00c30e80_selectHashedName(OpaqueReceiver_B3D290* receiver) {
    // Models 0x00c30cc0's two-level switch as a stable function of the token
    // that the caller placed in ECX.  The token is used as an opaque VALUE and
    // is deliberately not dereferenced: whether 0x00baf700's ECX at the
    // 0x00baf706 call site is the incoming stack argument or the preserved
    // register value is unresolved, so the model refuses to commit to either.
    return 0xACB9635Du ^ static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(receiver));
}

// --- 0x00b8d9b0 ports ------------------------------------------------------

std::uint32_t port_00bb99e0_resolveByPlanetId(OpaqueManager_EAE4* manager, PlanetRecord* record) {
    if (!manager || !manager->registry || !record) {
        return 0u;
    }
    OrderedKeyMapNode* n = findNode(manager->registry, record->mKey);
    return n ? n->value : 0u;
}

std::uint32_t port_00fee220_findActiveMissionContext(std::uint32_t global_DAC64,
                                                     PlanetRecord* record) {
    (void)global_DAC64;
    (void)record;
    return 0u;
}

std::uint32_t port_00c4b220_resolveSlot1F4(std::uint32_t context) {
    (void)context;
    return 0u;
}

// --- 0x00baf700 factory host ----------------------------------------------

static std::uint32_t g_releaseCount = 0;
static std::uint32_t g_createCount = 0;
static std::uint32_t g_lastFactoryKey = 0;

std::uint32_t releasedCount() { return g_releaseCount; }
std::uint32_t createdCount() { return g_createCount; }
std::uint32_t lastFactoryKey() { return g_lastFactoryKey; }
void resetFactory() {
    g_releaseCount = 0;
    g_createCount = 0;
    g_lastFactoryKey = 0;
}

// Slot +0x04 in the original is reached as CALL EDX with ECX = the value, and
// returns are not observed by 0x00baf700, so the model is a void thunk.
extern "C" void modelFactoryRelease(void* p) {
    (void)p;
    ++g_releaseCount;
}

// Slot +0x2C in the original is called with (this, hashedName, 0x0568DE14, slot).
extern "C" void modelFactoryCreate(void* host, std::uint32_t hashedName, std::uint32_t factoryKey,
                                   std::uint32_t* slot) {
    (void)host;
    ++g_createCount;
    g_lastFactoryKey = factoryKey;
    *slot = hashedName ^ factoryKey;
}

static OpaqueFactoryVftable g_vftable = {};
static OpaqueFactoryHost g_host = {&g_vftable};

void installFactoryVtable() {
    g_vftable.release = reinterpret_cast<std::uint32_t>(&modelFactoryRelease);
    g_vftable.createOrStore = reinterpret_cast<std::uint32_t>(&modelFactoryCreate);
    g_slot_015FD8A8 = reinterpret_cast<std::uint32_t>(&g_host);
}

// --- 0x00c446d0 vector ports ----------------------------------------------

void port_00c43cc0_insertAt(EastlVector16* vec, TaggedVector3* pos, const TaggedVector3* value) {
    // Models 0x00c43cc0: capacity becomes max(1, 2*count) elements of 0x10
    // bytes; the element is placed at `pos` and mpCur is advanced.
    const std::ptrdiff_t count = (vec->mpCur - vec->mpFirst);
    std::ptrdiff_t capacity = count >> 4;
    if (capacity == 0) {
        capacity = 1;
    } else {
        capacity *= 2;
    }
    if (vec->mpEnd - vec->mpFirst < capacity * 0x10) {
        vec->mpEnd = vec->mpFirst + capacity;
    }
    *pos = *value;
    vec->mpCur = pos + 1;
}

TaggedVector3* port_00c43f20_insertAtFront(EastlVector16* vec, TaggedVector3* pos,
                                           const TaggedVector3* value) {
    // Models 0x00c43f20: shift the tail up by one element, place the value at
    // `pos`, advance mpCur, and return mpFirst + index*0x10.
    const std::ptrdiff_t index = (pos - vec->mpFirst) >> 4;
    for (TaggedVector3* p = vec->mpCur; p > pos; --p) {
        p[0] = p[-1];
    }
    *pos = *value;
    vec->mpCur = vec->mpCur + 1;
    return vec->mpFirst + index;
}

// --- 0x00b3d290 slot installation ----------------------------------------

void installGlobal(std::uint32_t* slot, std::uint32_t value) { *slot = value; }
std::uint32_t* globalEAD4Slot() { return &g_slot_EAD4; }
std::uint32_t* globalEAE4Slot() { return &g_slot_EAE4; }

}  // namespace sim_core_b06
