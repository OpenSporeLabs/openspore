// CS-19: the cell position query (cCellQueryLinkedPool / cCellQueryEntry).
// Fixture-driven: build a query from cells with known positions/sizes and check
// the near predicate (|C-P| <= C.size + radius; touching counts as in-range).
#include "CellQuery.hpp"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>

namespace {

int g_failures = 0;

void check(bool cond, const char* label) {
  if (!cond) {
    std::printf("FAIL: %s\n", label);
    ++g_failures;
  } else {
    std::printf("ok: %s\n", label);
  }
}

using openspore::sim::CellQuery;

bool contains(const std::vector<uint32_t>& v, uint32_t x) {
  return std::find(v.begin(), v.end(), x) != v.end();
}

void testSelfInclusive() {
  CellQuery q;
  q.reserve(8);
  const float here[3] = {2.0F, -1.0F, 4.0F};
  q.addCell(7, here, 1.0F);
  auto r = q.queryNear(here, 0.0F);  // dist 0 <= size + 0
  check(r.size() == 1 && contains(r, 7),
        "query: a cell at the query point is in range");
}

void testTouchingBorder() {
  CellQuery q;
  q.reserve(8);
  const float p[3] = {0.0F, 0.0F, 0.0F};
  const float c1[3] = {1.0F, 0.0F, 0.0F};  // distance 1.0: touching
  const float c2[3] = {2.0F, 0.0F, 0.0F};  // distance 2.0: out
  q.addCell(1, c1, 1.0F);
  q.addCell(2, c2, 1.0F);
  auto r = q.queryNear(p, 0.0F);
  check(contains(r, 1) && !contains(r, 2),
        "query: touching cell in, beyond cell out");
}

void testRadiusExpands() {
  CellQuery q;
  q.reserve(8);
  const float p[3] = {0.0F, 0.0F, 0.0F};
  const float c3[3] = {1.2F, 0.0F, 0.0F};
  const float c4[3] = {1.9F, 0.0F, 0.0F};
  q.addCell(3, c3, 0.5F);
  q.addCell(4, c4, 0.5F);
  auto r = q.queryNear(p, 1.0F);
  check(contains(r, 3) && !contains(r, 4),
        "query: radius extends the reach (1.2 in, 1.9 out)");
}

void testCluster() {
  // Fixture world: a 3-cell cluster; only the two nearest cells reach the
  // query.
  CellQuery q;
  q.reserve(16);
  const float p[3] = {0.0F, 0.0F, 0.0F};
  const float a101[3] = {0.3F, 0.0F, 0.0F};  // dist 0.3, reach 0.4 -> in
  const float a102[3] = {0.3F, 0.2F, 0.0F};  // dist ~0.36, reach 0.5 -> in
  const float a103[3] = {5.0F, 0.0F, 0.0F};  // dist 5.0 -> out
  q.addCell(101, a101, 0.4F);
  q.addCell(102, a102, 0.5F);
  q.addCell(103, a103, 0.4F);
  auto r = q.queryNear(p, 0.0F);
  auto repeated = q.queryNear(p, 0.0F);
  check(r == repeated, "query: repeated calls preserve deterministic order");
  auto ordered = q.queryNearResult(p, 0.0F);
  check(ordered.status == openspore::sim::CellQueryStatus::success &&
            ordered.indices == r,
        "query: result preserves LIFO insertion order");
  std::sort(r.begin(), r.end());
  check(r.size() == 2 && r[0] == 101 && r[1] == 102,
        "query: cluster returns exactly the two nearest cells");
  check(!contains(r, 103), "query: the distant cell is excluded");
  check(q.queryNearResult(p, -1.0F).status ==
            openspore::sim::CellQueryStatus::failure,
        "query: invalid radius fails explicitly");
}

}  // namespace

int main() {
  testSelfInclusive();
  testTouchingBorder();
  testRadiusExpands();
  testCluster();
  if (g_failures == 0) {
    std::printf("cellquery_test: ALL PASS\n");
    return 0;
  }
  std::printf("cellquery_test: %d FAILURES\n", g_failures);
  return 1;
}
