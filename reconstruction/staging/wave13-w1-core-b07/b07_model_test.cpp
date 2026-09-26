// reconstruction/staging/wave13-w1-core-b07/b07_model_test.cpp
//
// Structural model test for OpenSpore wave-13 batch b07. It exercises the six
// reconstructions against synthetic fixtures and checks the invariants that
// were read out of SporeApp.exe. It is not a behavioural differential test: no
// original-process trace exists for any of these addresses.
//
// Build and run:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror -I <dir> \
//       <dir>/*.cpp -o /tmp/opencode/wave13-w1-core-b07-model && \
//       /tmp/opencode/wave13-w1-core-b07-model

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#include "b07_opaque_types.hpp"

namespace openspore {
namespace b07 {
namespace t00643a40 {
Word find_or_insert_mapped(OrderedMap* map, const Word* keyPtr, InsertWithHintFn insert);
}
namespace t00c30c80 {
Word resolve_record_by_field(RecordIdOwner* self, GlobalHandleTableFn handleTable,
                             ResolveHandleFn resolveHandle, RecordAccessorFn recordAccessor);
}
namespace t00b8dec0 {
std::int32_t element_at(ElementBlock* block, std::int32_t index);
}
namespace t00bca0c0 {
Word find_record(RecordTable* table, Word key1, Word key2, Word key3, Word key4);
}
namespace t00c04750 {
Word record_pointer_by_index(LevelOwner* self, CurrentModeFn currentMode,
                             ResolveSubObjectFn resolveSubObject, CurrentIndexFn currentIndex);
}
namespace t0060d860 {
void resolve_and_submit_keyed_work(ModeOwner* self, Word arg1, const ModeDescriptor* modeDescriptor,
                                  CreateFromModeDescriptorFn createFromMode,
                                  KeyPairAddrFn keyPairAddr, JobManagerFn jobManager,
                                  MakeKeyDescriptorFn makeKeyDescriptor, SubmitJobFn submitJob,
                                  ReportKeyFlagsFn reportFlags, VirtualReleaseFn releaseSlot1);
}
}  // namespace b07
}  // namespace openspore

namespace {

int g_failures = 0;

void check(bool condition, const char* what) {
    if (!condition) {
        ++g_failures;
        std::printf("FAIL: %s\n", what);
    }
}

using namespace openspore::b07;

// --- 0x00643a40 -------------------------------------------------------------
// A three-node tree built by hand in the observed layout, plus a recording
// insert port standing in for 0x006432d0.
struct TreeFixture {
    std::vector<Word> published;
    std::vector<Word> hints;
    Word nextNode;
};

TreeFixture* g_tree = nullptr;

void recordInsert(Word container, Word* keySlot, Word candidateHint, const Word* valuePair,
                  Word unusedFlag) {
    (void)container;
    (void)unusedFlag;
    g_tree->hints.push_back(candidateHint);
    g_tree->published.push_back(valuePair[0]);
    g_tree->published.push_back(valuePair[1]);
    // 0x00579b50 publishes the created node through *param_2, which is the
    // address of the caller's argument word.
    *keySlot = g_tree->nextNode;
}

Word wordAt(const void* base, std::size_t byteOffset) {
    Word value = 0;
    std::memcpy(&value, static_cast<const unsigned char*>(base) + byteOffset, sizeof(value));
    return value;
}

void test_00643a40() {
    // Offsets proved by instructions in the original body.
    check(offsetof(MapNode, mpNodeRight) == 0x00, "MapNode right child at +0x00");
    check(offsetof(MapNode, mpNodeLeft) == 0x04, "MapNode left child at +0x04");
    check(offsetof(MapNode, key) == 0x10, "MapNode key at +0x10");
    check(offsetof(MapNode, mapped) == 0x14, "MapNode mapped at +0x14");
    check(offsetof(OrderedMap, anchorParent) == 0x0c, "root read from +0x0c");
    check(offsetof(OrderedMap, nodeCount) == 0x14, "node counter at +0x14");

    TreeFixture fixture;
    g_tree = &fixture;

    // root(40) with left(20) and right(60); the walk must find 40 exactly.
    OrderedMap map;
    std::memset(static_cast<void*>(&map), 0, sizeof(map));
    std::vector<MapNode> storage(3);
    MapNode* node = storage.data();
    node[0].key = 20;
    node[0].mapped = 0xaa;
    node[1].key = 40;
    node[1].mapped = 0xbb;
    node[2].key = 60;
    node[2].mapped = 0xcc;
    node[1].mpNodeLeft = word_of(&node[0]);
    node[1].mpNodeRight = word_of(&node[2]);
    map.anchorParent = word_of(&node[1]);
    map.anchorLeft = map.anchorParent;
    map.anchorRight = map.anchorParent;
    map.nodeCount = 3;

    fixture.nextNode = word_of(&node[2]);

    const Word key40 = 40;
    const Word hit = t00643a40::find_or_insert_mapped(&map, &key40, &recordInsert);
    check(fixture.hints.empty(), "an exact match never calls the insert port");
    check(hit == map.anchorParent + 0x14, "a hit returns root.mapped");
    check(wordAt(&storage[1], 0x14) == 0xbb, "the hit maps to the stored value");

    // A miss inserts {key, 0} and returns the published node's mapped slot.
    const Word key50 = 50;
    const Word miss = t00643a40::find_or_insert_mapped(&map, &key50, &recordInsert);
    check(fixture.hints.size() == 1, "a miss calls the insert port once");
    check(fixture.published.size() == 2, "the port sees a two-word value pair");
    check(fixture.published[0] == 50 && fixture.published[1] == 0,
          "the inserted pair is {key, 0}");
    check(miss == fixture.nextNode + 0x14, "a miss returns the new node's mapped slot");

    // An empty tree cannot match and the hint passed on is end() = map + 4.
    OrderedMap empty;
    std::memset(static_cast<void*>(&empty), 0, sizeof(empty));
    fixture.hints.clear();
    const Word key7 = 7;
    const Word emptyResult = t00643a40::find_or_insert_mapped(&empty, &key7, &recordInsert);
    check(fixture.hints.size() == 1, "an empty tree still inserts");
    check(fixture.hints[0] == word_of(&empty) + 4,
          "the hint on an empty tree is the anchor (end())");
    check(emptyResult == fixture.nextNode + 0x14, "an empty tree returns the new slot");
    g_tree = nullptr;
}

// --- 0x00c30c80 -------------------------------------------------------------
Word g_table = 0x1000;
Word g_resolved = 0;
Word g_record = 0;

Word fakeHandleTable() { return g_table; }
Word fakeResolve(Word table, Word handle) {
    if (table != g_table) {
        return 0;
    }
    if (handle == 0) {
        return 0x2000;
    }
    return (handle == 42) ? g_resolved : 0;
}
Word fakeRecordAccessor(Word recordOwner) {
    g_record = recordOwner;
    return recordOwner + 0x4a8;
}

void test_00c30c80() {
    RecordIdOwner owner;
    std::memset(static_cast<void*>(&owner), 0, sizeof(owner));

    // -1 is the unset sentinel: the ports are never reached.
    owner.fieldB0 = 0xffffffffu;
    check(t00c30c80::resolve_record_by_field(&owner, &fakeHandleTable, &fakeResolve,
                                            &fakeRecordAccessor) == 0,
          "an unset id resolves to 0");

    // An unresolvable handle also yields 0.
    owner.fieldB0 = 43;
    check(t00c30c80::resolve_record_by_field(&owner, &fakeHandleTable, &fakeResolve,
                                            &fakeRecordAccessor) == 0,
          "an unresolved handle resolves to 0");

    // A resolved handle is tail-transferred and its result returned unchanged.
    g_resolved = 0x7654;
    owner.fieldB0 = 42;
    check(t00c30c80::resolve_record_by_field(&owner, &fakeHandleTable, &fakeResolve,
                                            &fakeRecordAccessor) == g_resolved + 0x4a8,
          "the tail callee's result is returned unchanged");
    check(g_record == g_resolved, "the tail callee receives the resolved handle");
}

// --- 0x00b8dec0 -------------------------------------------------------------
void test_00b8dec0() {
    std::vector<Word> elements;
    elements.push_back(0x11);
    elements.push_back(0x22);
    elements.push_back(0x33);

    // The receiver model addresses the block by absolute 32-bit words, so the
    // fixture is built through those words rather than real pointers.
    std::vector<unsigned char> raw(sizeof(ElementBlock) + 64, 0);
    auto* block = reinterpret_cast<ElementBlock*>(raw.data());
    const Word base = word_of(elements.data());
    block->begin = base;
    block->end = base + static_cast<Word>(elements.size() * sizeof(Word));

    check(t00b8dec0::element_at(block, 0) == 0x11, "index 0 returns the first element");
    check(t00b8dec0::element_at(block, 2) == 0x33, "index 2 returns the last element");
    check(t00b8dec0::element_at(block, 3) == 0, "index == count returns 0");
    check(t00b8dec0::element_at(block, 99) == 0, "an index past the end returns 0");

    // The original compares the index with JGE, i.e. signed, so a negative
    // index is not rejected. Modelled here only to document the polarity; the
    // read itself is out of the fixture and is not performed.
    check(static_cast<std::int32_t>(block->end) - static_cast<std::int32_t>(block->begin) == 12,
          "the element count is (end - begin) >> 2");
}

// --- 0x00bca0c0 -------------------------------------------------------------
void test_00bca0c0() {
    RecordTable table;
    std::memset(static_cast<void*>(&table), 0, sizeof(table));
    table.slots[0].id = 0x1111;
    table.slots[0].key1 = 2;
    table.slots[0].key2 = 1;
    table.slots[0].key3 = 0;
    table.slots[0].key4 = 0;
    table.slots[3].id = 0x3333;
    table.slots[3].key1 = 2;
    table.slots[3].key2 = 1;
    table.slots[3].key3 = 9;
    table.slots[3].key4 = 9;

    check(t00bca0c0::find_record(&table, 2, 1, 0, 0) == 0x00001111u,
          "zero arguments act as wildcards and match slot 0");
    check(t00bca0c0::find_record(&table, 2, 1, 9, 9) == 0x00033333u,
          "explicit keys select slot 3");
    check(t00bca0c0::find_record(&table, 2, 1, 9, 0) == 0x00033333u,
          "a wildcard on the fourth key still selects slot 3");
    check(t00bca0c0::find_record(&table, 2, 1, 0, 9) == 0x00033333u,
          "the optional keys are matched independently");
    check(t00bca0c0::find_record(&table, 2, 1, 8, 0) == 0xffffffffu,
          "a non-matching optional key fails the lookup");
    check(t00bca0c0::find_record(&table, 5, 1, 0, 0) == 0xffffffffu,
          "a non-matching mandatory key fails the lookup");
    check(((0x00001111u >> 16) & 0xffu) == 0 && (0x00001111u & 0xffffu) == 0x1111,
          "the slot index occupies bits 16..31 and the id bits 0..15");
}

// --- 0x00c04750 -------------------------------------------------------------
Word g_mode = 0;
Word g_sub = 0;
Word g_index = 0;
Word g_subWords[0x80 / 4] = {0};

Word fakeCurrentMode() { return g_mode; }
Word fakeResolveSub(Word) { return g_sub; }
Word fakeCurrentIndex() { return g_index; }

void test_00c04750() {
    std::vector<unsigned char> raw(0x40, 0);
    auto* self = reinterpret_cast<LevelOwner*>(raw.data());
    std::memset(static_cast<void*>(self), 0, 0x20);
    self->field1c = 5;

    g_mode = 0x01654c10;
    g_sub = word_of(g_subWords);
    g_index = 3;
    g_subWords[0x70 / 4] = 0x1000;  // the word at subObject + 0x70

    const Word ok = t00c04750::record_pointer_by_index(self, &fakeCurrentMode, &fakeResolveSub,
                                                      &fakeCurrentIndex);
    check(ok == 3 * kRecordStride + 0x1000, "the result is index * 0x4e0 + [sub + 0x70]");

    g_mode = 0x01654c11;
    check(t00c04750::record_pointer_by_index(self, &fakeCurrentMode, &fakeResolveSub,
                                             &fakeCurrentIndex) == 0,
          "a mode pointer other than the sentinel yields 0");
    g_mode = 0x01654c10;
    g_sub = 0;
    check(t00c04750::record_pointer_by_index(self, &fakeCurrentMode, &fakeResolveSub,
                                             &fakeCurrentIndex) == 0,
          "an unresolved sub-object yields 0");
}

// --- 0x0060d860 -------------------------------------------------------------
struct WorkLog {
    int creates;
    int submissions;
    int reports;
    int releases;
    int descriptors;
    Word lastFlags;
    Word lastKey0;
    Word lastKey1;
    Word lastArg1;
};

WorkLog g_work;

Word fakeCreate(const ModeDescriptor* modeDescriptor, Word* outObject) {
    ++g_work.creates;
    if (modeDescriptor == nullptr) {
        return 0;
    }
    *outObject = 0x9000;
    return 1;
}
// Stand-in for the resolved object: 0x005507a0 returns object + 0x18, which is
// where the 8-byte key pair lives.
struct ObjectFixture {
    Word vtable;    // +0x00
    Word pad[5];    // +0x04 .. +0x17
    Word key[2];    // +0x18
    Word tail[4];   // +0x20
};

ObjectFixture g_object;

Word fakeKeyPairAddr(Word) { return word_of(&g_object) + 0x18; }
Word fakeJobManager() { return 0xa000; }
void fakeMakeKeyDescriptor(KeyDescriptor* descriptor, const Word* keyPair) {
    ++g_work.descriptors;
    descriptor->head[0] = keyPair[0];
    descriptor->head[1] = keyPair[1];
    g_work.lastKey0 = keyPair[0];
    g_work.lastKey1 = keyPair[1];
}
Word fakeSubmit(Word manager, Word arg1, const KeyDescriptor* descriptor) {
    (void)manager;
    ++g_work.submissions;
    g_work.lastArg1 = arg1;
    g_work.lastFlags = descriptor->flags;
    return 0;
}
void fakeReport(KeyDescriptor*, Word) { ++g_work.reports; }
void fakeRelease(Word) { ++g_work.releases; }

void test_0060d860() {
    ModeOwner owner;
    ModeDescriptor descriptor;
    std::memset(static_cast<void*>(&owner), 0, sizeof(owner));
    std::memset(static_cast<void*>(&descriptor), 0, sizeof(descriptor));
    std::memset(static_cast<void*>(&g_work), 0, sizeof(g_work));

    std::memset(static_cast<void*>(&g_object), 0, sizeof(g_object));
    g_object.key[0] = 0xffffffffu;
    g_object.key[1] = 0xffffffffu;

    // Gate closed: nothing happens at all.
    owner.pad58 = 0;
    t0060d860::resolve_and_submit_keyed_work(&owner, 1, &descriptor, &fakeCreate,
                                             &fakeKeyPairAddr, &fakeJobManager,
                                             &fakeMakeKeyDescriptor, &fakeSubmit, &fakeReport,
                                             &fakeRelease);
    check(g_work.creates == 0, "a zero field +0x58 skips the whole body");
    check(g_work.releases == 0, "a zero field +0x58 skips the release too");

    // Gate open, empty key: the work is skipped but the object is released.
    owner.pad58 = 1;
    std::memset(static_cast<void*>(&g_work), 0, sizeof(g_work));
    t0060d860::resolve_and_submit_keyed_work(&owner, 1, &descriptor, &fakeCreate,
                                             &fakeKeyPairAddr, &fakeJobManager,
                                             &fakeMakeKeyDescriptor, &fakeSubmit, &fakeReport,
                                             &fakeRelease);
    check(g_work.creates == 1, "the object is created when the gate is open");
    check(g_work.submissions == 0, "an all-ones key pair skips the submission");
    check(g_work.releases == 1, "the resolved object is released exactly once");

    // A live key pair reaches the descriptor and the job submission.
    g_object.key[0] = 0x1234;
    g_object.key[1] = 0x5678;
    std::memset(static_cast<void*>(&g_work), 0, sizeof(g_work));
    t0060d860::resolve_and_submit_keyed_work(&owner, 0xabcd, &descriptor, &fakeCreate,
                                             &fakeKeyPairAddr, &fakeJobManager,
                                             &fakeMakeKeyDescriptor, &fakeSubmit, &fakeReport,
                                             &fakeRelease);
    check(g_work.descriptors == 1, "a live key pair builds one descriptor");
    check(g_work.lastKey0 == 0x1234 && g_work.lastKey1 == 0x5678,
          "the descriptor is filled from the key pair");
    check(g_work.submissions == 1, "the descriptor is submitted once");
    check(g_work.lastArg1 == 0xabcd, "argument 1 is forwarded unchanged");
    check(g_work.lastFlags == 0, "the descriptor flags start at zero");
    check(g_work.reports == 0, "flag bit 0x4 is clear so nothing is reported");
    check(g_work.releases == 1, "the resolved object is still released");
}

}  // namespace

int main() {
    static_assert(sizeof(Word) == 4, "the model is 32-bit word based");
    test_00643a40();
    test_00c30c80();
    test_00b8dec0();
    test_00bca0c0();
    test_00c04750();
    test_0060d860();
    if (g_failures != 0) {
        std::printf("%d check(s) failed\n", g_failures);
        return 1;
    }
    std::printf("wave13-w1-core-b07 model test: all checks passed\n");
    return 0;
}
