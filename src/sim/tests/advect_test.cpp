// CS-20: the advect system (GetCurrentAdvectInfo / GetNextAdvectID).
// Verifies the scale -> bucket-key table (from the binary) and the entry
// lookup (exact bucket, then the -1 default fallback).
#include <cmath>
#include <cstdio>
#include <vector>

#include "Advect.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const char *label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

using openspore::sim::AdvectEntry;
using openspore::sim::bucketKeyForScale;
using openspore::sim::getCurrentAdvectInfo;
using openspore::sim::getNextAdvectID;

void testBucketKeyTable() {
  // Matches the DAT_01483c14 threshold table (VERIFIED from SporeApp.exe).
  check(bucketKeyForScale(0) == 1, "bucket: scale 0 -> key 1");
  check(bucketKeyForScale(10) == 1, "bucket: scale 10 -> key 1");
  check(bucketKeyForScale(99) == 1, "bucket: scale 99 -> key 1");
  check(bucketKeyForScale(100) == 2, "bucket: scale 100 -> key 2");
  check(bucketKeyForScale(120) == 2, "bucket: scale 120 -> key 2");
  check(bucketKeyForScale(500) == 6, "bucket: scale 500 -> key 6");
  check(bucketKeyForScale(950) == 10, "bucket: scale 950 -> key 10");
  check(bucketKeyForScale(1000) == 10, "bucket: scale 1000 (_1K) -> key 10");
}

// A world with one advect entry per bucket key (1..10) plus a -1 default.
std::vector<AdvectEntry> makeFullWorld() {
  std::vector<AdvectEntry> w;
  for (int32_t k = 1; k <= 10; ++k) {
    AdvectEntry e;
    e.field_0 = k;
    e.playerSize = k;
    e.strength = 10.0F * k;
    e.variance = 2.0F * k;
    e.period = 4.0F * k;
    e.advectID = 100 + k;
    w.push_back(e);
  }
  AdvectEntry def;
  def.field_0 = 1;
  def.playerSize = -1;
  def.strength = 1.0F;
  def.variance = 0.5F;
  def.period = 8.0F;
  def.advectID = 999;
  w.push_back(def);
  return w;
}

void testCurrentInfoExact() {
  auto w = makeFullWorld();
  auto info = openspore::sim::getCurrentAdvectInfo(w, 120);  // key 2
  check(info.scaleLevel == 2, "current: scale 120 -> bucket 2 record");
  check(info.value == 102, "current: advectID 102");
  check(std::fabs(info.strength - 20.0F) < 1e-3, "current: strength 20");
  check(std::fabs(info.period - 8.0F) < 1e-3, "current: period 8");
}

void testNextID() {
  auto w = makeFullWorld();
  uint32_t id = openspore::sim::getNextAdvectID(w, 120);  // key 2 -> key 3
  check(id == 103, "next: scale 120 -> bucket 3 advectID 103");
  uint32_t id9 = openspore::sim::getNextAdvectID(w, 950);  // key 10 -> key 11 (none)
  check(id9 == 999, "next: at the top bucket, falls back to the default ID");
}

void testDefaultFallback() {
  // A world with ONLY the -1 default entry.
  std::vector<AdvectEntry> w;
  AdvectEntry def;
  def.playerSize = -1;
  def.strength = 7.0F;
  def.advectID = 42;
  w.push_back(def);
  auto info = openspore::sim::getCurrentAdvectInfo(w, 350);
  check(info.value == 42, "current: only a default entry -> returned");
  check(std::fabs(info.strength - 7.0F) < 1e-3, "current: default strength");
}

} // namespace

int main() {
  testBucketKeyTable();
  testCurrentInfoExact();
  testNextID();
  testDefaultFallback();
  if (g_failures == 0) {
    std::printf("advect_test: ALL PASS\n");
    return 0;
  }
  std::printf("advect_test: %d FAILURES\n", g_failures);
  return 1;
}
