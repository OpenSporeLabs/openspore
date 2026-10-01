// Focused semantic test for read_006a2f60
// (App::PropertyList::Read @ 0x006a2f60).
//
// The four helpers the original reaches by direct CALL rel32 are bound here to
// models that reproduce the OBSERVED contracts of 0x0093a780, 0x0093a700,
// 0x00694440 and 0x006a2b80, so the reconstructed control flow can be exercised
// without the game runtime.
//
// Build (x86-32 required, see the #error in the header):
//   clang++ -m32 -std=c++17 -Wall -Wextra -Wpedantic \
//       property_list_read_006a2f60.cpp property_list_read_006a2f60_model_test.cpp \
//       -o /tmp/opencode/proplist-read-006a2f60-model

#include "property_list_read_006a2f60.hpp"

#include <cstdio>
#include <cstring>
#include <vector>

namespace ospr = openspore::reconstruction::pkg_app_proplist_read_wave17;

namespace {

int g_failures = 0;

void Check(bool condition, const char* what) {
  if (!condition) {
    std::printf("FAIL: %s\n", what);
    ++g_failures;
  }
}

// ---------------------------------------------------------------------------
// Model IStream: vtable slots +0x10 (index 4), +0x14 (index 5), +0x30 (index 12)
// ---------------------------------------------------------------------------

struct StreamModel : public ospr::IStream {
  std::vector<std::uint8_t> bytes;
  std::size_t cursor;
  std::uint32_t commit_result;  // slot +0x14 must return 0 for a short read
  std::uint32_t slot_10_calls;
  std::uint32_t slot_14_calls;
};

StreamModel* g_stream = nullptr;

void Slot_0x10() { ++g_stream->slot_10_calls; }
std::uint32_t Slot_0x14() {
  ++g_stream->slot_14_calls;
  return g_stream->commit_result;
}
std::uint32_t Slot_0x30(void* buffer, std::uint32_t byte_count) {
  const std::size_t available = g_stream->bytes.size() - g_stream->cursor;
  const std::size_t n = byte_count < available ? byte_count : available;
  std::memcpy(buffer, g_stream->bytes.data() + g_stream->cursor, n);
  g_stream->cursor += n;
  return static_cast<std::uint32_t>(n);
}

void BuildStream(ospr::IStream* stream) {
  stream->slot_00 = nullptr;
  stream->slot_04 = nullptr;
  stream->slot_08 = nullptr;
  stream->slot_0c = nullptr;
  stream->lock = reinterpret_cast<void*>(&Slot_0x10);
  stream->gate = &Slot_0x14;
  stream->slot_18 = nullptr;
  stream->slot_1c = nullptr;
  stream->slot_20 = nullptr;
  stream->slot_24 = nullptr;
  stream->slot_28 = nullptr;
  stream->read = &Slot_0x30;
}

std::uint32_t g_commit_calls = 0;

// Model of 0x0093a780.  Observed contract: slot +0x10 is invoked unless
// swap_flag == 1; slot +0x14 must return 0; slot +0x30 must transfer
// count*4 bytes; the count is in DWORDS; every dword is byte-swapped, so the
// serialized order is big-endian.
bool ModelReadDwords(ospr::IStream* stream, std::uint32_t* buffer,
                     std::uint32_t count, std::uint32_t swap_flag) {
  g_stream = static_cast<StreamModel*>(stream);
  if (swap_flag != 1) reinterpret_cast<void (*)()>(stream->lock)();
  if (stream->gate() != 0) return false;
  const std::uint32_t want = count * 4u;
  if (stream->read(buffer, want) != want) return false;
  for (std::uint32_t i = 0; i < count; ++i) {
    buffer[i] = ((buffer[i] & 0x000000ffu) << 24) |
                ((buffer[i] & 0x0000ff00u) << 8) |
                ((buffer[i] & 0x00ff0000u) >> 8) |
                ((buffer[i] & 0xff000000u) >> 24);
  }
  return true;
}

// Model of 0x0093a700: the 16-bit sibling, always called with count == 1 here.
bool ModelReadWords(ospr::IStream* stream, std::uint16_t* buffer,
                    std::uint32_t element_count, std::uint32_t) {
  g_stream = static_cast<StreamModel*>(stream);
  std::uint32_t scratch[4] = {0, 0, 0, 0};
  if (!ModelReadDwords(stream, scratch, element_count, 1)) return false;
  for (std::uint32_t i = 0; i < element_count; ++i) buffer[i] = scratch[i];
  return true;
}

// Model of 0x00694440.  The real helper dispatches on the ObjectTYPE at
// property+0x12 and on the flag bits at property+0x10; the model consumes one
// 32-bit word and parks it in the opaque prefix so the test can assert the
// per-record call count and ordering.
std::uint32_t g_value_reads = 0;
bool ModelReadPropertyValue(ospr::IStream* stream, ospr::Property* property,
                            std::uint32_t) {
  ++g_value_reads;
  std::uint32_t word = 0;
  if (!ModelReadDwords(stream, &word, 1, 0)) return false;
  std::memcpy(property->opaque_prefix, &word, sizeof(word));
  return true;
}

// Model of 0x006a2b80: set the entry count exactly.  The fixture owns the
// backing storage, so the test can inspect what the resize produced.
std::vector<ospr::PropertyMapEntry>* g_backing = nullptr;

void ModelResizeMap(ospr::PropertyMap* map, std::uint32_t count) {
  g_backing->resize(count);
  map->entries_begin = g_backing->data();
  map->entries_end = g_backing->data() + g_backing->size();
}

// ---------------------------------------------------------------------------
// Model of the DAT_015fd8a8 service, only slot +0x2c (index 11) is claimed.
// ---------------------------------------------------------------------------

std::uint32_t g_resolve_calls = 0;
std::uint32_t g_resolve_arg0 = 0;
std::uint32_t g_resolve_arg1 = 0;
ospr::DirectPropertyList* g_resolve_result = nullptr;
std::uint32_t g_parent_releases = 0;

void ServiceResolve(std::uint32_t a, std::uint32_t b,
                    ospr::DirectPropertyList** out) {
  ++g_resolve_calls;
  g_resolve_arg0 = a;
  g_resolve_arg1 = b;
  *out = g_resolve_result;
}

ospr::PropertyListService* ModelGetService() {
  static ospr::PropertyListService service = {};
  static bool once = false;
  if (!once) {
    service.resolve = &ServiceResolve;
    once = true;
  }
  return &service;
}

void ReleaseSlot1() { ++g_parent_releases; }

// ---------------------------------------------------------------------------
// Fixture
// ---------------------------------------------------------------------------

struct Fixture {
  std::vector<std::uint8_t> payload;
  StreamModel stream = {};
  ospr::DirectPropertyList receiver = {};
  ospr::DirectPropertyList* old_parent = nullptr;
  std::vector<ospr::PropertyMapEntry> backing;
};

void PushWord(Fixture& fx, std::uint32_t word) {
  fx.payload.push_back(static_cast<std::uint8_t>(word >> 24));
  fx.payload.push_back(static_cast<std::uint8_t>(word >> 16));
  fx.payload.push_back(static_cast<std::uint8_t>(word >> 8));
  fx.payload.push_back(static_cast<std::uint8_t>(word));
}

void Reset(Fixture& fx, std::size_t entries) {
  BuildStream(&fx.stream);
  fx.stream.bytes = fx.payload;
  fx.stream.cursor = 0;
  fx.stream.commit_result = 0;
  fx.stream.slot_10_calls = 0;
  fx.stream.slot_14_calls = 0;

  fx.backing.assign(entries, ospr::PropertyMapEntry{});
  g_backing = &fx.backing;
  std::memset(&fx.receiver, 0, sizeof(fx.receiver));
  fx.receiver.properties.entries_begin = fx.backing.data();
  fx.receiver.properties.entries_end = fx.backing.data() + fx.backing.size();
  fx.receiver.parent = nullptr;

  static ospr::PropertyListVtable parent_vtable = {};
  static bool once = false;
  if (!once) {
    parent_vtable.release = reinterpret_cast<void*>(&ReleaseSlot1);
    once = true;
  }
  static ospr::DirectPropertyList parent = {};
  parent.vftable = &parent_vtable;
  fx.old_parent = &parent;

  g_commit_calls = 0;
  g_value_reads = 0;
  g_resolve_calls = 0;
  g_resolve_arg0 = 0;
  g_resolve_arg1 = 0;
  g_resolve_result = &parent;
  g_parent_releases = 0;

  ospr::g_helpers.read_dwords_be = &ModelReadDwords;
  ospr::g_helpers.read_words_be = &ModelReadWords;
  ospr::g_helpers.read_property_value = &ModelReadPropertyValue;
  ospr::g_helpers.resize_map = &ModelResizeMap;
  ospr::g_helpers.get_service = &ModelGetService;
}

}  // namespace

int main() {
  // 1. Header sign bit clear: the stream carries no header, the receiver's
  //    existing map size drives the loop, and every record is consumed.
  {
    Fixture fx;
    PushWord(fx, 0x00000000u);
    PushWord(fx, 0x11111111u);
    PushWord(fx, 0xAAAA0001u);
    PushWord(fx, 0x22222222u);
    PushWord(fx, 0xBBBB0002u);
    Reset(fx, 2);

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(ok, "legacy path returns true");
    Check(fx.backing[0].key == 0x11111111u, "record 0 key is big-endian decoded");
    Check(fx.backing[1].key == 0x22222222u, "record 1 key is big-endian decoded");
    std::uint32_t v0 = 0;
    std::uint32_t v1 = 0;
    std::memcpy(&v0, fx.backing[0].property.opaque_prefix, 4);
    std::memcpy(&v1, fx.backing[1].property.opaque_prefix, 4);
    Check(v0 == 0xAAAA0001u, "record 0 value read at entry+0x04");
    Check(v1 == 0xBBBB0002u, "record 1 value read at entry+0x04");
    Check(g_value_reads == 2, "one value read per record");
    Check(fx.stream.cursor == fx.payload.size(), "legacy path consumes the stream");
    Check(g_resolve_calls == 0, "legacy path does not touch the service");
  }

  // 2. Header sign bit set: 3 more words, parent is released and replaced
  //    through service vtable +0x2c, then the map is resized from block[1].
  {
    Fixture fx;
    PushWord(fx, 0x80000000u);  // header, sign set
    PushWord(fx, 0x0BADF00Du);  // block[0] -> port arg 1
    PushWord(fx, 0x00000001u);  // block[1] -> new count
    PushWord(fx, 0x0D0D0D0Du);  // block[2] -> port arg 2
    PushWord(fx, 0x33333333u);  // record key
    PushWord(fx, 0xCCCC0003u);  // record value
    Reset(fx, 1);
    fx.receiver.parent = fx.old_parent;

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(ok, "extended header path returns true");
    Check(g_parent_releases == 1, "previous parent released exactly once");
    Check(fx.receiver.parent == fx.old_parent, "parent replaced by the port result");
    Check(g_resolve_calls == 1, "service slot +0x2c invoked once");
    Check(g_resolve_arg0 == 0x0BADF00Du, "port arg1 == block[0]");
    Check(g_resolve_arg1 == 0x0D0D0D0Du, "port arg2 == block[2]");
    Check(fx.stream.cursor == fx.payload.size(), "extended path consumes the stream");
  }

  // 3. block[1] is masked to 31 bits: 0x80000002 must resize to two entries,
  //    not to a negative count.
  {
    Fixture fx;
    PushWord(fx, 0xFFFFFFFFu);
    PushWord(fx, 0x00000000u);
    PushWord(fx, 0x80000002u);
    PushWord(fx, 0x00000000u);
    PushWord(fx, 0x44444444u);
    PushWord(fx, 0xDDDD0004u);
    PushWord(fx, 0x55555555u);
    PushWord(fx, 0xEEEE0005u);
    Reset(fx, 0);

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(ok, "masked count path returns true");
    Check(fx.backing.size() == 2, "count masked with 0x7fffffff");
    Check(fx.backing[0].key == 0x44444444u, "record 0 key after resize");
    Check(fx.backing[1].key == 0x55555555u, "record 1 key after resize");
  }

  // 4. Truncated record stream: the flag clears and Read reports false.  The
  //    loop still runs to the map bound without touching the stream again.
  {
    Fixture fx;
    PushWord(fx, 0x00000000u);
    PushWord(fx, 0x66666666u);  // record 0 key, no value word available
    Reset(fx, 2);

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(!ok, "truncated record stream returns false");
    Check(fx.backing[0].key == 0x66666666u, "record 0 key still decoded");
    Check(fx.backing[1].key == 0u, "record 1 untouched after the failure");
    Check(g_value_reads == 1, "value read attempted for record 0 only");
  }

  // 5. Truncated 3-word block.  0x0093a780 requires the full count*4 bytes, so
  //    the read fails, but the four bytes that did arrive are still sitting in
  //    the destination and 0x006a2fd1-0x006a2fe3 uses the block unconditionally:
  //    the parent is released and the service port is still invoked.  The
  //    record loop then starts from the failed read's flag, so nothing else is
  //    consumed and Read reports false.
  {
    Fixture fx;
    PushWord(fx, 0x80000000u);
    PushWord(fx, 0x00000001u);  // only 4 of the 12 block bytes are available
    Reset(fx, 1);
    fx.receiver.parent = fx.old_parent;

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(!ok, "truncated extended block returns false");
    Check(g_parent_releases == 1,
          "parent is still released even though the block read failed");
    Check(g_resolve_calls == 1, "service port is called despite the failed read");
    //    0x0093a780 byte-swaps only after the full count*4 arrives, so a short
    //    read leaves the RAW, still big-endian bytes in the destination:
    //    block[0] == 0x01000000, not the decoded 0x00000001.
    Check(g_resolve_arg0 == 0x01000000u,
          "short read leaves the un-swapped raw bytes in block[0]");
  }

  // 6. Empty map: the header result is returned untouched and no record is
  //    read.  (0x006a300f TEST EAX,EAX / JLE 0x006a3061)
  {
    Fixture fx;
    PushWord(fx, 0x00000000u);
    Reset(fx, 0);

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(ok, "empty map returns the header read result");
    Check(fx.stream.cursor == 4, "empty map reads only the header word");
    Check(g_value_reads == 0, "empty map reads no records");
  }

  // 7. Corrupt span (end below start): the signed count is negative, the loop is
  //    skipped, and the header result is returned.
  {
    Fixture fx;
    PushWord(fx, 0x00000000u);
    Reset(fx, 0);
    fx.receiver.properties.entries_end = fx.receiver.properties.entries_begin - 1;

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(ok, "negative record count skips the loop");
    Check(fx.stream.cursor == 4, "negative record count reads only the header");
  }

  // 8. Commit failure on the stream: the helper's slot +0x14 gate rejects the
  //    read before any bytes move.
  {
    Fixture fx;
    PushWord(fx, 0x00000000u);
    Reset(fx, 1);
    fx.stream.commit_result = 1;

    const bool ok = ospr::read_006a2f60(&fx.receiver,
                                        &fx.stream);
    Check(!ok, "stream slot +0x14 failure returns false");
    Check(fx.stream.cursor == 0, "no bytes consumed when the commit gate fails");
  }

  if (g_failures == 0) {
    std::printf("property_list_read_006a2f60: all model checks passed\n");
    return 0;
  }
  std::printf("property_list_read_006a2f60: %d check(s) failed\n", g_failures);
  return 1;
}
