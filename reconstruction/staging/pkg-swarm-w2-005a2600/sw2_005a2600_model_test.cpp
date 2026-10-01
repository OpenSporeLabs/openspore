// PKG-SWARM-W2-005A2600 -- model test for the reconstruction of FUN_005a2600
// (SPORE/SporeBin/SporeApp.exe 3.1.0.22, image base 0x400000)
//
// WHAT THIS TEST IS FOR. It is written to BREAK sw2_005a2600.cpp, not to walk it.
// Every callee the reconstruction reaches is defined here as an observer that records
// what it was handed, in what order, and can decide what the body then sees, so a
// wrong displacement, a wrong constant, a wrong branch polarity, a wrong pointer
// level, a wrong slot, a wrong argument order or a wrong write order all show up as a
// failure rather than as a plausible-looking store.
//
// Twelve decoy families, one per high-risk hypothesis, are listed under each case.
//
// NOT ASSERTED, AND WHY.
//   * Nothing about EAX, XMM0 or the x87 stack. The declared return type is void
//     because the five terminators produce nothing, and the machine leaves four
//     different dead words in EAX on the four arms of the last block. Asserting a
//     dead register would assert nothing about the body.
//   * Nothing about ECX at the terminators. The epilogue's POP ECX restores the frame
//     word at [ESP+0x8], which the two +0x24 blocks overwrote, so ECX's final value
//     is path-dependent and unobservable to this body's callers.
//   * Nothing about the object's class, its three slots' implementations, or what the
//     fifteen key ids mean. The listing fixes the three slot displacements and the two
//     argument shapes and nothing else.
//   * Nothing about the twenty-one float displacements beyond which key id writes
//     which of them. The 0x14 spacing and the three-wide block are observations about
//     the displacements, not a layout this package claims.
//   * Whether the null check on the parameter object in the two +0x24 blocks is
//     "meaningful" is not asserted; only that it is present there and absent from the
//     last block, which the trace can see.

#include "sw2_005a2600_types.hpp"

#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace openspore::reconstruction::pkg_swarm_w2_005a2600 {

// The header declares the parameter object's class without describing it. The test
// completes it, which is a statement about the TEST's own bookkeeping object and not
// about the game's class.
struct ParamSource {
  int test_only_tag;
};

// -- the three data addresses, from the image bytes quoted in the header ------
extern const float g_unmodelled_15d1168 = 0.0f;
extern const float g_unmodelled_013f6960 = 0.01745329238474369f;
extern const float g_unmodelled_013f6964 = 57.295780181884766f;

namespace {

int g_failures = 0;
int g_checks = 0;

void check(bool condition, const std::string& what) {
  ++g_checks;
  if (!condition) {
    ++g_failures;
    std::printf("FAIL: %s\n", what.c_str());
  }
}

std::uint32_t bits_of(float value) {
  std::uint32_t out = 0;
  std::memcpy(&out, &value, sizeof out);
  return out;
}

// -- the observers ------------------------------------------------------------
//
// `g_trace` is the machine's call order, written down: one entry per transfer, in the
// order the body made it. A reconstruction that asked the wrong slot, passed the wrong
// argument, or ran the blocks in the wrong order produces a different trace.
struct TraceEntry {
  std::string slot;
  Word id;
  const void* first;   // the object the callee was handed in ECX
  const void* second;  // the out-parameter address, for the +0x24 slot only
  Word flag_byte_at_entry;
  Word first_slot_value;  // +0x14's word at the moment of the call
};

std::vector<TraceEntry> g_trace;
std::map<Word, bool> g_present;
std::map<Word, const std::uint8_t*> g_record;
std::map<Word, bool> g_find_result;
std::map<Word, const std::uint8_t*> g_find_record;
std::map<const std::uint8_t*, const float*> g_loader;
std::map<const std::uint8_t*, int> g_loader_calls;
std::vector<Word> g_loader_argument;
const std::uint8_t* g_last_out_pointer = nullptr;
EditorTransform005a2600* g_observed_receiver = nullptr;

void record_entry(const char* slot, Word id, const void* first, const void* second) {
  TraceEntry entry;
  entry.slot = slot;
  entry.id = id;
  entry.first = first;
  entry.second = second;
  entry.flag_byte_at_entry = 0;
  entry.first_slot_value = 0;
  if (g_observed_receiver != nullptr) {
    const std::uint8_t* base = raw(g_observed_receiver);
    entry.flag_byte_at_entry = byte_at(base + 0x9c);
    entry.first_slot_value = word_at(base + 0x14);
  }
  g_trace.push_back(entry);
}

}  // namespace

// -- the three slots the body reaches indirectly ------------------------------
extern "C" bool PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_has_query(ParamSource* source,
                                                                     Word id) {
  record_entry("has", id, source, nullptr);
  std::map<Word, bool>::const_iterator it = g_present.find(id);
  return it != g_present.end() && it->second;
}

extern "C" const std::uint8_t* PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_get_query(
    ParamSource* source, Word id) {
  record_entry("get", id, source, nullptr);
  std::map<Word, const std::uint8_t*>::const_iterator it = g_record.find(id);
  return it == g_record.end() ? nullptr : it->second;
}

extern "C" bool PKG_SWARM_W2_005A2600_THISCALL sw2_obj_slot_find_query(
    ParamSource* source, Word id, const std::uint8_t** out) {
  record_entry("find", id, source, out);
  g_last_out_pointer = raw(*out);
  std::map<Word, bool>::const_iterator result = g_find_result.find(id);
  const bool ok = result != g_find_result.end() && result->second;
  std::map<Word, const std::uint8_t*>::const_iterator record = g_find_record.find(id);
  *out = (record == g_find_record.end()) ? nullptr : record->second;
  return ok;
}

// -- the one direct callee ----------------------------------------------------
extern "C" const float* PKG_SWARM_W2_005A2600_THISCALL unresolved_0041ea70(
    const std::uint8_t* record) {
  ++g_loader_calls[record];
  g_loader_argument.push_back(word_at(record + 0x00));
  std::map<const std::uint8_t*, const float*>::const_iterator it = g_loader.find(record);
  return it == g_loader.end() ? &g_unmodelled_15d1168 : it->second;
}

namespace {

// -- the record, built the way the body reads it ------------------------------
//
// A record is an opaque byte run here too. The body reads three displacements of it:
// the leading word (0x00, read as an ADDRESS on one arm and as a float on the other),
// a flag BYTE at 0x10 and a type WORD at 0x12.
struct Record {
  alignas(8) std::array<std::uint8_t, 0x20> bytes{};

  void put32(std::size_t at, std::uint32_t value) {
    std::memcpy(bytes.data() + at, &value, sizeof value);
  }
  void put16(std::size_t at, std::uint16_t value) {
    std::memcpy(bytes.data() + at, &value, sizeof value);
  }
  void put_float(std::size_t at, float value) {
    std::memcpy(bytes.data() + at, &value, sizeof value);
  }
  // The record's own leading word as a float: what the body reads when the flag byte
  // says "inline".
  float inline_float() const {
    float value = 0.0f;
    std::memcpy(&value, bytes.data() + 0x00, sizeof value);
    return value;
  }
  // The address the record's leading word names, and the float stored there.
  const std::uint8_t* pointed() const {
    std::uintptr_t address = 0;
    std::memcpy(&address, bytes.data() + 0x00, sizeof address);
    return reinterpret_cast<const std::uint8_t*>(address);
  }
  std::uint16_t type() const {
    std::uint16_t value = 0;
    std::memcpy(&value, bytes.data() + 0x12, sizeof value);
    return value;
  }
  std::uint8_t flag_byte() const { return bytes[0x10]; }
  std::uint8_t flag_byte_high() const { return bytes[0x11]; }
  // Set the flag WORD, so the high byte can be driven independently of the low one.
  void set_flags(std::uint16_t value) { put16(0x10, value); }
};

// A buffer the record can point at: a float at its +0 and, one level deeper, another
// buffer with a different float at its +0. The second level exists so that a
// reconstruction which dereferences twice reads something visibly wrong.
struct Target {
  alignas(8) std::array<std::uint8_t, 0x20> bytes{};
  void put_float(std::size_t at, float value) {
    std::memcpy(bytes.data() + at, &value, sizeof value);
  }
  float at(std::size_t offset) const {
    float value = 0.0f;
    std::memcpy(&value, bytes.data() + offset, sizeof value);
    return value;
  }
  std::uint8_t* base() { return bytes.data(); }
  const std::uint8_t* cbase() const { return bytes.data(); }
};

// -- an INDEPENDENT transcription of the block at 0x005a2621..0x005a265b --------
//
// Written from the listing, instruction by instruction, and deliberately NOT calling
// param_record_float(): the point is to check the .cpp's de-duplication of the twelve
// copies against a second, separate expression of the same 21 instructions. It is a
// consistency check on the factoring, not an independent oracle -- no oracle for this
// target exists -- and it is labelled as such.
float transcribe_block_0x005a2621(const Record& record) {
  const std::uint8_t* base;
  // 0x005a2630  MOVZX ECX,word ptr [EAX + 0x12]
  const std::uint16_t type = record.type();
  // 0x005a2634  CMP CX,0xd / 0x005a2638 JZ 0x005a2647
  if (type == 0x0du) {
    // 0x005a2647 reached
  } else {
    // 0x005a263a  CMP CX,0x10 / 0x005a263e JZ 0x005a2647
    if (type != 0x10u) {
      // 0x005a2640  MOV ECX,0x15d1168 / 0x005a2645 JMP 0x005a2659
      return g_unmodelled_15d1168;
    }
  }
  // 0x005a2647  TEST byte ptr [EAX + 0x10],BL   with BL = 0x30 from 0x005a261b
  if ((record.flag_byte() & 0x30u) != 0) {
    // 0x005a264c  MOV ECX,dword ptr [EAX] / 0x005a264e JMP 0x005a2659
    base = record.pointed();
  } else {
    // 0x005a2650  MOVZX ECX,CX / 0x005a2653 NEG ECX / 0x005a2655 SBB ECX,ECX
    // 0x005a2657  AND ECX,EAX
    //   (type != 0) ? record : 0, and this arm is only reached with 0xd or 0x10.
    base = record.bytes.data();
  }
  // 0x005a2659  FLD float ptr [ECX]
  float value = 0.0f;
  std::memcpy(&value, base, sizeof value);
  return value;  // 0x005a265b FSTP float ptr [ESI+0x14]
}

// -- the fixture --------------------------------------------------------------
struct Fixture {
  EditorTransform005a2600 receiver{};
  ParamSource object{0};
  std::map<Word, Record> records;
  std::map<Word, Record> find_records;
  std::map<Word, Target> targets;
  std::map<Word, Target> second_targets;
  std::map<Word, float> loader_values;
  std::map<Word, const float*> loader_floats;

  void reset() {
    g_trace.clear();
    g_present.clear();
    g_record.clear();
    g_find_result.clear();
    g_find_record.clear();
    g_loader.clear();
    g_loader_calls.clear();
    g_loader_argument.clear();
    g_last_out_pointer = nullptr;
    g_observed_receiver = &receiver;
    // A receiver whose every 4-byte window holds a distinct, recognisable bit
    // pattern, so a store that lands one dword off writes a pattern nothing else
    // writes and shows up in the changed-byte set.
    for (std::size_t at = 0; at < receiver.opaque_run.size(); at += 4) {
      const std::uint32_t pattern = 0xa5a50000u + static_cast<std::uint32_t>(at);
      std::memcpy(&receiver.opaque_run[at], &pattern, sizeof pattern);
    }
    receiver.opaque_run[0x9c] = 0xffu;  // the entry flag starts SET, so a model that
                                        // never clears it, or clears it late, shows
    // The parameter object is wired here, before any snapshot is taken, so the
    // changed-byte comparisons below are about the body and not about the fixture.
    word_at(raw(&receiver) + kOffSourceObject) =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&object));
  }

  // Make a record for `id` and wire its leading word the way the arm the flags select
  // requires, because the two arms are mutually exclusive in the machine: when the
  // flag byte says "indirect" the leading word IS an address, and when it says
  // "inline" the leading word IS the float.
  //
  // The indirect arm is built so that ONE, TWO and NO dereference all produce
  // different numbers:
  //
  //   no dereference   -> the record's own leading word, read as the inline float
  //   one dereference  -> the float stored at the address in the leading word, which
  //                      is shallow_of(id): a float whose bit pattern happens to BE
  //                      the address of the deeper buffer
  //   two dereferences -> the float at that address's own leading word, which is
  //                      `deep_value`
  //
  // So a model at the wrong depth reads a different number rather than crashing, and
  // the fixture is explicit about which of the three it is asserting.
  Record& make_record(Word id, std::uint16_t flags, std::uint16_t type, float inline_value,
                      float deep_value) {
    Target& shallow = targets[id];
    Target& deep = second_targets[id];
    deep.put_float(0x00, deep_value);
    deep.put_float(0x04, 0.0f);
    shallow.put_float(0x00, shallow_of(id));
    shallow.put_float(0x04, deep_value);
    Record& record = records[id];
    record.put_float(0x04, inline_value + 1000.0f);  // a decoy at the record's +0x04
    record.set_flags(flags);
    record.put16(0x12, type);
    const bool indirect = (flags & 0x30u) != 0;
    const bool accepted = (type == 0x0du || type == 0x0010u);
    if (indirect || !accepted) {
      record.put32(0x00, static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(
                             shallow.base())));
    } else {
      record.put32(0x00, bits_of(inline_value));
    }
    return record;
  }

  // The value ONE dereference of this record's leading word produces.
  float shallow_of(Word id) const {
    const std::uint32_t address =
        static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(second_targets.at(id).cbase()));
    float value = 0.0f;
    std::memcpy(&value, &address, sizeof value);
    return value;
  }

  Record& make_find_record(Word id, std::uint16_t type, float loader_value) {
    Record& record = find_records[id];
    const std::uintptr_t address = reinterpret_cast<std::uintptr_t>(record.bytes.data());
    record.put32(0x00, static_cast<std::uint32_t>(address));
    record.set_flags(0);
    record.put16(0x12, type);
    loader_floats[id] = &loader_values[id];
    loader_values[id] = loader_value;
    g_loader[record.bytes.data()] = &loader_values[id];
    return record;
  }

  void wire_all_present() {
    for (Word id : {kIdC7c4f8, kIdC7c4fa, kIdC7c4f9, kIdC7c4fb, kIdC7c4fc, kIdC7c4fd,
                    kId6fda2e1c, kId8fda2e23, kIdFe23b2, kIdFe2437, kIdFe243b, kIdFe243f,
                    kId44c6220}) {
      g_present[id] = true;
      g_record[id] = records[id].bytes.data();
    }
  }

  void run() { re_005a2600(&receiver); }
};

// -- the expected result, written out displacement by displacement ------------
struct Expectation {
  std::vector<std::size_t> displacements;  // 4-byte float windows the body must write
  std::set<std::size_t> changed_bytes;      // every byte the body may touch
};

Expectation expectation_for(const Fixture& fixture, bool expect_flag_byte_written) {
  Expectation out;
  const std::size_t scaled[] = {kDispForIdC7c4fc, kDisp2ForIdC7c4fc, kDispForIdC7c4fd,
                                kDisp2ForIdC7c4fd, kDispForIdFe243b, kDispForIdFe243f};
  const std::size_t all[] = {kDispForIdC7c4f8, kDispForIdC7c4fa, kDispForIdC7c4f9,
                             kDispForIdC7c4fb, kDisp2ForIdC7c4fb, kDisp3ForIdC7c4fb,
                             kDispForIdC7c4fc, kDisp2ForIdC7c4fc, kDispForIdC7c4fd,
                             kDisp2ForIdC7c4fd, kDispForId6fda2e1c, kDisp2ForId6fda2e1c,
                             kDispForId8fda2e23, kDisp2ForId8fda2e23, kDispForIdFe23b2,
                             kDispForIdFe2437, kDispForIdFe243b, kDispForIdFe243f,
                             kDispForId1102b20, kDispForId1102b2f, kDispForId44c6220};
  for (std::size_t displacement : all) {
    out.displacements.push_back(displacement);
    out.changed_bytes.insert(displacement);
    out.changed_bytes.insert(displacement + 1);
    out.changed_bytes.insert(displacement + 2);
    out.changed_bytes.insert(displacement + 3);
  }
  (void)scaled;
  (void)fixture;
  if (expect_flag_byte_written) {
    out.changed_bytes.insert(kOffEntryFlag);
  }
  return out;
}

std::set<std::size_t> changed_bytes_of(const Fixture& fixture,
                                       const std::array<std::uint8_t, 0xa0>& before) {
  std::set<std::size_t> changed;
  for (std::size_t at = 0; at < before.size(); ++at) {
    if (before[at] != fixture.receiver.opaque_run[at]) {
      changed.insert(at);
    }
  }
  return changed;
}

std::string hex_of(std::size_t value) {
  char buffer[16];
  std::snprintf(buffer, sizeof buffer, "0x%zx", value);
  return buffer;
}

std::string set_to_string(const std::set<std::size_t>& values) {
  std::string out = "{";
  for (std::size_t value : values) {
    char buffer[16];
    std::snprintf(buffer, sizeof buffer, "0x%zx,", value);
    out += buffer;
  }
  return out + "}";
}

float read_f32(const Fixture& fixture, std::size_t displacement) {
  float value = 0.0f;
  std::memcpy(&value, &fixture.receiver.opaque_run[displacement], sizeof value);
  return value;
}

void expect_f32(const Fixture& fixture, std::size_t displacement, float expected,
                const std::string& what) {
  const float actual = read_f32(fixture, displacement);
  ++g_checks;
  if (bits_of(actual) != bits_of(expected)) {
    ++g_failures;
    std::printf("FAIL: %s: +0x%zx holds 0x%08x, expected 0x%08x\n", what.c_str(), displacement,
                bits_of(actual), bits_of(expected));
  }
}

int count_trace(const char* slot) {
  int total = 0;
  for (std::size_t at = 0; at < g_trace.size(); ++at) {
    if (g_trace[at].slot == slot) {
      ++total;
    }
  }
  return total;
}

const TraceEntry* find_trace(const char* slot, Word id) {
  for (std::size_t at = 0; at < g_trace.size(); ++at) {
    if (g_trace[at].slot == slot && g_trace[at].id == id) {
      return &g_trace[at];
    }
  }
  return nullptr;
}

}  // namespace

// =============================================================================
// Case A -- every id present, every record type 0xd inline.
//   DECOYS: (1) the receiver is pre-filled with a distinct bit pattern in every
//   4-byte window, so a store one dword off writes a pattern nothing else writes;
//   (2) the two reciprocals are driven with the SAME source value for the scaled and
//   the unscaled blocks, so a model that multiplies by the wrong one, or scales a
//   block the listing does not scale, is caught by the value rather than by the
//   displacement; (3) the three-wide block (0x28/0x38/0x4c) gets one value and the
//   ten paired displacements get their own, so a store to 0x2c or 0x3c instead of
//   0x38 is caught by the changed-byte set; (4) the find ids are given type 0xd and a
//   loader float, so the two direct-callee blocks are exercised at all.
// =============================================================================
void case_a_all_present_inline() {
  Fixture fixture;
  fixture.reset();
  const float v1 = 1.0f, v2 = 2.0f, v3 = 3.0f, v4 = 4.0f;
  fixture.make_record(kIdC7c4f8, 0x00u, 0x0du, v1, 111.0f);
  fixture.make_record(kIdC7c4fa, 0x00u, 0x0du, v2, 112.0f);
  fixture.make_record(kIdC7c4f9, 0x00u, 0x0du, v3, 113.0f);
  fixture.make_record(kIdC7c4fb, 0x00u, 0x0du, v4, 114.0f);
  fixture.make_record(kIdC7c4fc, 0x00u, 0x0du, v1, 115.0f);
  fixture.make_record(kIdC7c4fd, 0x00u, 0x0du, v2, 116.0f);
  fixture.make_record(kId6fda2e1c, 0x00u, 0x0du, v3, 117.0f);
  fixture.make_record(kId8fda2e23, 0x00u, 0x0du, v4, 118.0f);
  fixture.make_record(kIdFe23b2, 0x00u, 0x0du, v1, 119.0f);
  fixture.make_record(kIdFe2437, 0x00u, 0x0du, v2, 120.0f);
  fixture.make_record(kIdFe243b, 0x00u, 0x0du, v3, 121.0f);
  fixture.make_record(kIdFe243f, 0x00u, 0x0du, v4, 122.0f);
  fixture.make_record(kId44c6220, 0x00u, 0x0du, v1, 123.0f);
  fixture.make_find_record(kId1102b20, 0x0du, 31.0f);
  fixture.make_find_record(kId1102b2f, 0x0du, 32.0f);
  fixture.wire_all_present();
  g_find_result[kId1102b20] = true;
  g_find_result[kId1102b2f] = true;
  g_find_record[kId1102b20] = fixture.find_records[kId1102b20].bytes.data();
  g_find_record[kId1102b2f] = fixture.find_records[kId1102b2f].bytes.data();

  const std::array<std::uint8_t, 0xa0> before = fixture.receiver.opaque_run;
  fixture.run();

  expect_f32(fixture, kDispForIdC7c4f8, v1, "A +0x14");
  expect_f32(fixture, kDispForIdC7c4fa, v2, "A +0x18");
  expect_f32(fixture, kDispForIdC7c4f9, v3, "A +0x1c");
  expect_f32(fixture, kDispForIdC7c4fb, v4, "A +0x28");
  expect_f32(fixture, kDisp2ForIdC7c4fb, v4, "A +0x38");
  expect_f32(fixture, kDisp3ForIdC7c4fb, v4, "A +0x4c");
  expect_f32(fixture, kDispForIdC7c4fc, v1 * g_unmodelled_013f6960, "A +0x34 scaled");
  expect_f32(fixture, kDisp2ForIdC7c4fc, v1 * g_unmodelled_013f6960, "A +0x48 scaled");
  expect_f32(fixture, kDispForIdC7c4fd, v2 * g_unmodelled_013f6960, "A +0x30 scaled");
  expect_f32(fixture, kDisp2ForIdC7c4fd, v2 * g_unmodelled_013f6960, "A +0x44 scaled");
  expect_f32(fixture, kDispForId6fda2e1c, v3, "A +0x3c");
  expect_f32(fixture, kDisp2ForId6fda2e1c, v3, "A +0x50");
  expect_f32(fixture, kDispForId8fda2e23, v4, "A +0x40");
  expect_f32(fixture, kDisp2ForId8fda2e23, v4, "A +0x54");
  expect_f32(fixture, kDispForIdFe23b2, v1, "A +0x58");
  expect_f32(fixture, kDispForIdFe2437, v2, "A +0x5c");
  expect_f32(fixture, kDispForIdFe243b, v3 * g_unmodelled_013f6960, "A +0x60 scaled");
  expect_f32(fixture, kDispForIdFe243f, v4 * g_unmodelled_013f6960, "A +0x64 scaled");
  expect_f32(fixture, kDispForId1102b20, 31.0f, "A +0x68 through 0x0041ea70");
  expect_f32(fixture, kDispForId1102b2f, 32.0f, "A +0x6c through 0x0041ea70");
  expect_f32(fixture, kDispForId44c6220, v1 * g_unmodelled_013f6964, "A +0x70 scaled");
  check(fixture.receiver.opaque_run[kOffEntryFlag] == 0, "A clears the +0x9c byte");

  // The two reciprocals must not be interchangeable: the same source value went to a
  // degrees-to-radians block and to the radians-to-degrees block.
  check(bits_of(read_f32(fixture, kDispForIdC7c4fc)) !=
            bits_of(read_f32(fixture, kDispForId44c6220)),
        "A the two reciprocals are not the same constant");

  // The store set, asserted as two halves rather than as set equality, because a
  // written float can coincidentally agree with a sentinel byte in one position of a
  // window: every expected window must have been touched, and no byte outside the
  // union of the expected windows may have been.
  const Expectation expected = expectation_for(fixture, true);
  const std::set<std::size_t> changed = changed_bytes_of(fixture, before);
  for (std::size_t index = 0; index < expected.displacements.size(); ++index) {
    const std::size_t base = expected.displacements[index];
    int touched = 0;
    for (std::size_t byte = 0; byte < 4; ++byte) {
      if (changed.count(base + byte) != 0) {
        ++touched;
      }
    }
    check(touched != 0, "A the window at +" + hex_of(base) + " was written");
  }
  std::set<std::size_t> outside;
  for (std::size_t byte : changed) {
    if (expected.changed_bytes.count(byte) == 0) {
      outside.insert(byte);
    }
  }
  check(outside.empty(), "A no byte outside the expected windows changed: got " +
                            set_to_string(outside));

  // The trace: twelve ids ask has then get, the two find ids ask only find, and the
  // last id asks has then get. A model that used the +0x1c slot to fetch, or that
  // fetched before asking, produces a different order.
  check(count_trace("has") == 13, "A thirteen +0x1c calls (twelve blocks plus the last)");
  check(count_trace("get") == 13, "A thirteen +0x28 calls");
  check(count_trace("find") == 2, "A two +0x24 calls");
  const TraceEntry* first_find = find_trace("find", kId1102b20);
  const TraceEntry* second_find = find_trace("find", kId1102b2f);
  check(first_find != nullptr && second_find != nullptr, "A both find calls present");
  if (first_find != nullptr && second_find != nullptr) {
    check(first_find->second == second_find->second,
          "A both +0x24 calls are handed the SAME out-parameter address");
    check(first_find->first == reinterpret_cast<const void*>(&fixture.object),
          "A the +0x24 callee is handed the parameter object, not the receiver");
  }
  check(g_loader_calls.size() == 2 && g_loader_argument.size() == 2,
        "A 0x0041ea70 is called exactly twice");
  // The direct callee's argument is the record read back out of the out-parameter,
  // whose leading word the find observer set to its own address -- and the body must
  // have passed THAT record, so the recorded argument is the address the observer
  // wrote. Any other value means the body passed the receiver, the object or nothing.
  if (g_loader_argument.size() == 2) {
    const std::uint32_t expected_first = word_at(fixture.find_records[kId1102b20].bytes.data());
    const std::uint32_t expected_second = word_at(fixture.find_records[kId1102b2f].bytes.data());
    check(g_loader_argument[0] == expected_first,
          "A 0x0041ea70 receives the first find record");
    check(g_loader_argument[1] == expected_second,
          "A 0x0041ea70 receives the second find record");
  }
  // Write ordering: the entry flag is already clear, and the first block's store has
  // already happened, at the moment of the first +0x24 call.
  if (first_find != nullptr) {
    check(first_find->flag_byte_at_entry == 0, "A the +0x9c byte is cleared before the first call");
    check(first_find->first_slot_value == bits_of(v1), "A +0x14 is written before the first +0x24 call");
  }
  // The receiver is never passed to a callee.
  for (std::size_t at = 0; at < g_trace.size(); ++at) {
    check(g_trace[at].first != reinterpret_cast<const void*>(&fixture.receiver),
          "A the receiver is never handed to a callee");
  }
}

// =============================================================================
// Case B -- the mask arm. Flag byte 0x20 and 0x10 separately, plus the high byte.
//   DECOYS: (1) a two-level dereference would read the SECOND target's float, which
//   is a different number; (2) reading the record's own leading word as a float (the
//   no-dereference bug) yields the pointer reinterpreted, also a different number;
// (3) 0x10 alone and 0x20 alone both satisfy 0x30, and a mask of 0x20 only would
//   accept 0x10 too, so driving both separately is what separates them; (4) the
//   WORD-vs-BYTE trap: the flag word is 0x1000, so the low byte the listing tests is
//   clear while the high byte has a mask bit set -- 0x0041ea94 tests the word and
//   would take the other arm, and this body must not.
// =============================================================================
void case_b_pointer_level_and_mask() {
  struct Arm {
    const char* name;
    std::uint16_t flags;
    bool indirect;
  };
  const Arm arms[] = {
      {"flag byte 0x20", 0x0020u, true},
      {"flag byte 0x10", 0x0010u, true},
      {"flag byte 0x30", 0x0030u, true},
      {"flag byte 0x31", 0x0031u, true},
      {"flag byte 0x11", 0x0011u, true},
      {"flag byte 0x21", 0x0021u, true},
      {"flag byte 0x01", 0x0001u, false},
      {"flag byte 0x02", 0x0002u, false},
  };
  for (std::size_t index = 0; index < sizeof arms / sizeof arms[0]; ++index) {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, arms[index].flags, 0x0du, 71.0f, 91.0f);
    g_present[kIdC7c4f8] = true;
    g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
    fixture.run();
    const float expected = arms[index].indirect ? fixture.shallow_of(kIdC7c4f8) : 71.0f;
    expect_f32(fixture, kDispForIdC7c4f8, expected,
               std::string("B ") + arms[index].name +
                   (arms[index].indirect ? " reads the address once" : " reads the record"));
    check(fixture.receiver.opaque_run[kOffEntryFlag] == 0,
          std::string("B ") + arms[index].name + ": +0x9c cleared");
  }

  // Every depth must produce a DIFFERENT number, or the decoy is not a decoy.
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, 0x0020u, 0x0du, 71.0f, 91.0f);
    check(bits_of(fixture.shallow_of(kIdC7c4f8)) != bits_of(71.0f),
          "B the one-dereference value differs from the inline value");
    check(bits_of(fixture.shallow_of(kIdC7c4f8)) != bits_of(91.0f),
          "B the one-dereference value differs from the two-dereference value");
    check(fixture.records[kIdC7c4f8].pointed() == fixture.targets[kIdC7c4f8].base(),
          "B the record's leading word names the shallow target");
  }

  // The byte/word trap on its own: the flag WORD is 0x1000, so the low byte the
  // listing tests at 0x005a2647 is clear while the high byte carries a mask bit.
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, 0x1000u, 0x0du, 81.0f, 83.0f);
    check(fixture.records[kIdC7c4f8].flag_byte() == 0x00u &&
              fixture.records[kIdC7c4f8].flag_byte_high() == 0x10u,
          "B the mask bit is in the record's +0x11, not its +0x10");
    g_present[kIdC7c4f8] = true;
    g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
    fixture.run();
    // 0x005a2647 is TEST BYTE PTR [EAX+0x10],BL. 0x0041ea94 is MOVZX EDX,WORD
    // [ECX+0x10] / AND EDX,0x30 and would take the other arm. Only the byte test is
    // this body's, so the float stored in the record itself is the one read.
    expect_f32(fixture, kDispForIdC7c4f8, 81.0f,
               "B a mask bit in the record's +0x11 does not make the value indirect");
  }
}

// =============================================================================
// Case C -- the type arm. Which tag words the body accepts, and what it does with
// the others.
//   DECOYS: the leading word of every record points at a target holding a plausible
//   number, so a model that reads the pointer on an unaccepted type writes that
//   number where the listing writes 0.0f; and 0x0c/0x0e/0x0f/0x11/0x20/0x8000/0x800d
//   are driven so that `<= 0x10`, `< 0x11`, `>= 0x0d` and a signed compare all differ
//   from the listing's two equality tests.
// =============================================================================
void case_c_type_tags() {
  // Every arm here is the INDIRECT one, so a record of an unaccepted tag still has a
  // perfectly readable address in its leading word: if the body took it, the written
  // value would be a plausible number instead of the 0.0f the listing produces.
  const std::uint16_t types[] = {0x0000u, 0x000cu, 0x000du, 0x000eu, 0x000fu, 0x0010u,
                                 0x0011u, 0x0020u, 0x7fffu, 0x8000u, 0x800du, 0xffffu};
  for (std::size_t index = 0; index < sizeof types / sizeof types[0]; ++index) {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, 0x0020u, types[index], 61.0f, 63.0f);
    g_present[kIdC7c4f8] = true;
    g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
    fixture.run();
    const bool accepted = (types[index] == 0x0du || types[index] == 0x0010u);
    char label[96];
    std::snprintf(label, sizeof label, "C type 0x%04x (accepted=%d)", types[index],
                  accepted ? 1 : 0);
    if (accepted) {
      expect_f32(fixture, kDispForIdC7c4f8, fixture.shallow_of(kIdC7c4f8), label);
    } else {
      expect_f32(fixture, kDispForIdC7c4f8, g_unmodelled_15d1168, label);
      check(bits_of(read_f32(fixture, kDispForIdC7c4f8)) == 0u,
            std::string(label) + ": the fallback is the 0.0f at 0x015d1168, exactly zero");
      check(bits_of(read_f32(fixture, kDispForIdC7c4f8)) !=
                bits_of(fixture.shallow_of(kIdC7c4f8)),
            std::string(label) + ": the record's own address is not read");
    }
  }
  // The inline arm of both accepted tags, so both halves of the composition are
  // covered: tag 0x0d inline, tag 0x10 inline, tag 0x10 indirect.
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, 0x0000u, 0x0010u, 64.0f, 66.0f);
    g_present[kIdC7c4f8] = true;
    g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
    fixture.run();
    expect_f32(fixture, kDispForIdC7c4f8, 64.0f, "C tag 0x10 with a clear flag byte is inline");
  }
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_record(kIdC7c4f8, 0x0020u, 0x0010u, 64.0f, 66.0f);
    g_present[kIdC7c4f8] = true;
    g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
    fixture.run();
    expect_f32(fixture, kDispForIdC7c4f8, fixture.shallow_of(kIdC7c4f8),
               "C tag 0x10 with the mask set is indirect");
  }
}

// =============================================================================
// Case D -- the presence arm. The +0x1c slot's answer gates every store, and its
// FALSE answer on the last id is the one that stores the multiplier itself.
//   DECOYS: (1) all twelve ids absent, so a model that stores a zero, or that ignores
//   the answer, writes twelve windows the listing never writes; (2) on the last id,
//   the fallback must be 57.29578f and NOT 0.0f (a multiply of a missing value), NOT
//   the record's value, and NOT degrees-to-radians.
// =============================================================================
void case_d_presence_and_fallback() {
  Fixture fixture;
  fixture.reset();
  // Give every id a record with a recognisable value, and then report all of them
  // absent: nothing but the entry flag may be touched.
  const Word ids[] = {kIdC7c4f8, kIdC7c4fa, kIdC7c4f9, kIdC7c4fb, kIdC7c4fc, kIdC7c4fd,
                      kId6fda2e1c, kId8fda2e23, kIdFe23b2, kIdFe2437, kIdFe243b, kIdFe243f,
                      kId44c6220};
  for (std::size_t index = 0; index < sizeof ids / sizeof ids[0]; ++index) {
    fixture.make_record(ids[index], 0x00u, 0x0du, 41.0f, 43.0f);
    g_present[ids[index]] = false;
    g_record[ids[index]] = fixture.records[ids[index]].bytes.data();
  }
  g_find_result[kId1102b20] = false;
  g_find_result[kId1102b2f] = false;

  const std::array<std::uint8_t, 0xa0> before = fixture.receiver.opaque_run;
  fixture.run();

  check(fixture.receiver.opaque_run[kOffEntryFlag] == 0, "D +0x9c cleared with nothing present");
  check(bits_of(read_f32(fixture, kDispForId44c6220)) == bits_of(g_unmodelled_013f6964),
        "D +0x70 holds the multiplier itself when the last id is absent");
  check(bits_of(read_f32(fixture, kDispForId44c6220)) == 0x42652ee1u,
        "D that value is 57.29578f (0x42652ee1) and not 0.0f");
  check(bits_of(read_f32(fixture, kDispForIdC7c4f8)) == 0xa5a50014u,
        "D +0x14 keeps its sentinel when the id is absent");
  check(bits_of(read_f32(fixture, kDispForId1102b20)) == 0xa5a50068u,
        "D +0x68 keeps its sentinel when the find answer is false");
  check(count_trace("get") == 0, "D the +0x28 slot is never asked once an id is absent");
  check(count_trace("find") == 2, "D the +0x24 slot is still asked twice");

  const std::set<std::size_t> changed = changed_bytes_of(fixture, before);
  std::set<std::size_t> allowed;
  allowed.insert(kOffEntryFlag);
  for (std::size_t byte = 0; byte < 4; ++byte) {
    allowed.insert(kDispForId44c6220 + byte);
  }
  std::set<std::size_t> outside;
  for (std::size_t byte : changed) {
    if (allowed.count(byte) == 0) {
      outside.insert(byte);
    }
  }
  check(outside.empty(),
        "D only the +0x70 window and the +0x9c byte may change: got " +
            set_to_string(outside));
  check(changed.count(kOffEntryFlag) != 0, "D the +0x9c byte did change");
  check(changed.count(kDispForId44c6220) != 0, "D the +0x70 window did change");
}

// =============================================================================
// Case E -- the +0x24 blocks: the null check, the exactly-0xd tag test, the shared
// out-parameter, and the argument order.
//   DECOYS: (1) with the parameter object null, the two find calls must not happen at
//   all while the last block's +0x1c call still does -- that is the only place the
//   listing's missing null check on the last block is observable; (2) a find record of
//   type 0x10 must be SKIPPED even though the twelve inline blocks accept 0x10, which
//   is the sharpest tag difference in the body; (3) the second find overwrites the
//   first's record in the same frame word, so a model that used two separate slots
//   would write a different +0x68; (4) the out-parameter is read back, so a model that
//   kept the record the callee returned (there is none -- it returns a bool) or that
//   reused the first call's record writes the wrong number.
// =============================================================================
void case_e_find_blocks() {
  // E1: a null parameter object.
  {
    Fixture fixture;
    fixture.reset();
    word_at(raw(&fixture.receiver) + 0x10) = 0u;
    g_observed_receiver = &fixture.receiver;
    re_005a2600(&fixture.receiver);
    check(count_trace("find") == 0,
          "E1 with a null parameter object neither +0x24 call is made");
    // The twelve inline blocks run FIRST and ask the +0x1c slot with that null object,
    // so all thirteen +0x1c calls are still made while both +0x24 calls vanish. That
    // difference localises the null check: it is inside the two +0x24 blocks, not at
    // the top of the body. It also means the check is unreachable in the machine,
    // which would fault at 0x005a260f (MOV EAX,[ECX]) before reaching it -- see the
    // metadata sidecar.
    check(count_trace("has") == 13,
          "E1 the twelve inline blocks and the last block still ask the +0x1c slot");
    check(bits_of(read_f32(fixture, kDispForId1102b20)) == 0xa5a50068u,
          "E1 +0x68 untouched");
    check(bits_of(read_f32(fixture, kDispForId44c6220)) == bits_of(g_unmodelled_013f6964),
          "E1 +0x70 still takes the fallback");
  }

  // E2: the find answer is true but the record's type is 0x10, which the inline
  // blocks accept and these do not.
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_find_record(kId1102b20, 0x0010u, 41.0f);
    fixture.make_find_record(kId1102b2f, 0x0010u, 42.0f);
    g_find_result[kId1102b20] = true;
    g_find_result[kId1102b2f] = true;
    g_find_record[kId1102b20] = fixture.find_records[kId1102b20].bytes.data();
    g_find_record[kId1102b2f] = fixture.find_records[kId1102b2f].bytes.data();
    fixture.run();
    check(bits_of(read_f32(fixture, kDispForId1102b20)) == 0xa5a50068u,
          "E2 a find record of type 0x10 is skipped (0x005a2a48 accepts only 0xd)");
    check(g_loader_argument.empty(),
          "E2 0x0041ea70 is not called for a record of type 0x10");
  }

  // E3: type 0xd, and the two calls share one out-parameter.
  {
    Fixture fixture;
    fixture.reset();
    fixture.make_find_record(kId1102b20, 0x0du, 51.0f);
    fixture.make_find_record(kId1102b2f, 0x0du, 52.0f);
    g_find_result[kId1102b20] = true;
    g_find_result[kId1102b2f] = true;
    g_find_record[kId1102b20] = fixture.find_records[kId1102b20].bytes.data();
    g_find_record[kId1102b2f] = fixture.find_records[kId1102b2f].bytes.data();
    // The receiver's +0x14 is a sentinel and the first find record's type is NOT
    // 0xd, so the first call writes nothing, which makes the second call's value the
    // only one in +0x6c and cannot be confused with the first's.
    fixture.find_records[kId1102b20].put16(0x12, 0x0001u);
    fixture.run();
    expect_f32(fixture, kDispForId1102b2f, 52.0f, "E3 +0x6c takes the second find record");
    check(bits_of(read_f32(fixture, kDispForId1102b20)) == 0xa5a50068u,
          "E3 +0x68 skipped when the first record's type is not 0xd");
    const TraceEntry* first = find_trace("find", kId1102b20);
    const TraceEntry* second = find_trace("find", kId1102b2f);
    check(first != nullptr && second != nullptr && first->second == second->second,
          "E3 both calls are handed one and the same out-parameter address");
    // The record the body passed on to 0x0041ea70 must be the one the SECOND find
    // call wrote through the shared out-parameter, and not the first call's.
    check(g_loader_argument.size() == 1,
          "E3 exactly one 0x0041ea70 call, for the record of type 0xd");
    if (g_loader_argument.size() == 1) {
      check(g_loader_argument[0] == word_at(fixture.find_records[kId1102b2f].bytes.data()),
            "E3 0x0041ea70 receives the SECOND call's record, read back through the "
            "shared out-parameter");
      check(g_loader_argument[0] != word_at(fixture.find_records[kId1102b20].bytes.data()),
            "E3 it is not the first call's record");
      check(g_loader_argument[0] !=
                static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(&fixture.receiver)),
            "E3 it is not the receiver");
    }
  }
}

// =============================================================================
// Case F -- the de-duplication check. The twelve inline copies are factored into one
// helper in the .cpp; this compares that helper against an instruction-by-
// instruction transcription of one of the copies.
// =============================================================================
void case_f_independent_transcription() {
  const std::uint16_t types[] = {0x0000u, 0x000du, 0x0010u, 0x0011u, 0x0020u};
  const std::uint8_t flags[] = {0x00u, 0x01u, 0x10u, 0x20u, 0x30u, 0x31u};
  const float values[] = {0.0f, 1.0f, -1.0f, 0.5f, 12345.678f};
  for (std::size_t t = 0; t < sizeof types / sizeof types[0]; ++t) {
    for (std::size_t f = 0; f < sizeof flags / sizeof flags[0]; ++f) {
      for (std::size_t v = 0; v < sizeof values / sizeof values[0]; ++v) {
        Record record;
        Target target;
        Target second;
        target.put_float(0x00, values[v] + 7.0f);
        second.put_float(0x00, values[v] + 9.0f);
        const std::uintptr_t address = reinterpret_cast<std::uintptr_t>(target.base());
        record.put32(0x00, static_cast<std::uint32_t>(address));
        record.set_flags(flags[f]);
        record.put16(0x12, types[t]);
        const float transcribed = transcribe_block_0x005a2621(record);
        const float modelled = param_record_float(record.bytes.data());
        ++g_checks;
        if (bits_of(transcribed) != bits_of(modelled)) {
          ++g_failures;
          std::printf("FAIL: F type 0x%04x flags 0x%02x: transcribed 0x%08x modelled 0x%08x\n",
                      types[t], flags[f], bits_of(transcribed), bits_of(modelled));
        }
      }
    }
  }
}

// =============================================================================
// Case G -- repeat invocation. The body keeps no state of its own, so calling it
// twice must produce the same bytes both times, and the entry flag must be cleared
// again on the second call even though the first left it clear.
//   DECOYS: a model that only clears the flag when some other condition holds, or that
// accumulates into a displacement, fails here.
// =============================================================================
void case_g_repeat() {
  Fixture fixture;
  fixture.reset();
  fixture.make_record(kIdC7c4f8, 0x00u, 0x0du, 5.0f, 7.0f);
  g_present[kIdC7c4f8] = true;
  g_record[kIdC7c4f8] = fixture.records[kIdC7c4f8].bytes.data();
  fixture.receiver.opaque_run[kOffEntryFlag] = 0xffu;
  fixture.run();
  const std::array<std::uint8_t, 0xa0> after_first = fixture.receiver.opaque_run;
  fixture.receiver.opaque_run[kOffEntryFlag] = 0xffu;
  fixture.run();
  check(fixture.receiver.opaque_run == after_first,
        "G two calls from the same inputs produce the same receiver bytes");
  check(after_first[kOffEntryFlag] == 0, "G the +0x9c byte is clear after the first call");
}

}  // namespace openspore::reconstruction::pkg_swarm_w2_005a2600

int main() {
  using namespace openspore::reconstruction::pkg_swarm_w2_005a2600;
  case_a_all_present_inline();
  case_b_pointer_level_and_mask();
  case_c_type_tags();
  case_d_presence_and_fallback();
  case_e_find_blocks();
  case_f_independent_transcription();
  case_g_repeat();
  std::printf("%d check(s), %d failure(s)\n", g_checks, g_failures);
  return g_failures == 0 ? 0 : 1;
}
