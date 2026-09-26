// Standalone model test for reconstruction/staging/wave13-pilot-gameglobal-b03/
// 59c740_map_get_or_create.{hpp,cpp}.
//
// Build and run:
//   clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
//       -I reconstruction/staging/wave13-pilot-gameglobal-b03 \
//       reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.cpp
//       \
//       reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create_model_test.cpp
//       \ -o /tmp/opencode/59c740-model && /tmp/opencode/59c740-model
//
// The port below is a TEST DOUBLE for 0x0059c520. That function's body was read
// (a four-argument __thiscall insert that takes a hint node and writes the
// resulting node through its first argument) but it is not reconstructed here:
// it belongs to another package, so the double records the arguments the caller
// passes and returns a caller-chosen node.

#include "59c740_map_get_or_create.hpp"

#include <cstdio>
#include <cstring>

namespace openspore::reconstruction::wave13_pilot_gameglobal_b03 {

struct PortRecord {
  int calls;
  Opaque59c740TreeNode** out_node;
  Opaque59c740TreeNode* hint;
  std::uint32_t key_copy;
  std::uint32_t masked;
};

PortRecord g_port;
Opaque59c740TreeNode* g_port_result;

extern "C" void OpaquePort_0059c520_insert_with_hint(
    Opaque59c740TreeNode** out_node, Opaque59c740TreeNode* hint,
    const std::uint32_t* key_copy, std::uint32_t masked_key_pointer) {
  g_port.calls += 1;
  g_port.out_node = out_node;
  g_port.hint = hint;
  g_port.key_copy = *key_copy;
  g_port.masked = masked_key_pointer;
  *out_node = g_port_result;
}

}  // namespace openspore::reconstruction::wave13_pilot_gameglobal_b03

namespace {

using openspore::reconstruction::wave13_pilot_gameglobal_b03::g_port;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::g_port_result;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::
    GameGlobal_0059c740_map_get_or_create;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::
    Opaque59c740MapHeader;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::
    Opaque59c740TreeNode;
using openspore::reconstruction::wave13_pilot_gameglobal_b03::PortRecord;

int g_failures = 0;

void Expect(const char* what, bool ok) {
  if (!ok) {
    std::printf("FAIL %s\n", what);
    ++g_failures;
  }
}

// Wires a header around a hand-built ascending tree. 0x0059c740 only reads
// anchor_parent (+0x0c) and the address of the anchor (+0x04), the rest is set
// the way 0x0059c520 and 0x0059c380 expect it.
void BuildHeader(Opaque59c740MapHeader* h, Opaque59c740TreeNode* root,
                 Opaque59c740TreeNode* begin, Opaque59c740TreeNode* rbegin,
                 std::uint32_t size) {
  std::memset(h, 0, sizeof(*h));
  h->anchor_left = reinterpret_cast<std::uint32_t>(begin);
  h->anchor_right = reinterpret_cast<std::uint32_t>(rbegin);
  h->anchor_parent = reinterpret_cast<std::uint32_t>(root);
  h->size = size;
}

}  // namespace

int main() {
  Opaque59c740MapHeader header;

  Opaque59c740TreeNode n10 = {0, 0, 0, 0, 10, 0xAA10};
  Opaque59c740TreeNode n20 = {0, 0, 0, 0, 20, 0xAA20};
  Opaque59c740TreeNode n30 = {0, 0, 0, 0, 30, 0xAA30};
  // left subtree holds the larger key, right subtree the smaller one
  n20.left = reinterpret_cast<std::uint32_t>(&n30);
  n20.right = reinterpret_cast<std::uint32_t>(&n10);
  n30.parent = reinterpret_cast<std::uint32_t>(&n20);
  n10.parent = reinterpret_cast<std::uint32_t>(&n20);
  BuildHeader(&header, &n20, &n10, &n30, 3);

  // 1. Hit on the right child: the answer is the address of the mapped value,
  //    not the value, which is what 0x0059caf2 / 0x0059cb4a dereference.
  const std::uint32_t k10 = 10;
  std::uint32_t* hit = GameGlobal_0059c740_map_get_or_create(&header, &k10);
  Expect("hit-10-addr", hit == &n10.value);
  Expect("hit-10-deref", *hit == 0xAA10u);
  Expect("hit-10-no-insert", g_port.calls == 0);

  // 2. Hit on the root.
  const std::uint32_t k20 = 20;
  hit = GameGlobal_0059c740_map_get_or_create(&header, &k20);
  Expect("hit-20-addr", hit == &n20.value);

  // 3. Hit on the left child, which only an ascending comparison finds: an
  //    inverted comparator would return the root or the right child.
  const std::uint32_t k30 = 30;
  hit = GameGlobal_0059c740_map_get_or_create(&header, &k30);
  Expect("hit-30-addr", hit == &n30.value);

  // 4. Miss: 25 sits between 20 and 30, so the candidate ends on 30 whose key
  //    is greater than the searched one, and the out-of-line insert runs.
  //    Its fourth argument is the key pointer with the low byte cleared.
  Opaque59c740TreeNode fresh = {0, 0, 0, 0, 25, 0xBB25};
  g_port_result = &fresh;
  g_port = PortRecord();
  const std::uint32_t k25 = 25;
  hit = GameGlobal_0059c740_map_get_or_create(&header, &k25);
  Expect("miss-calls-port", g_port.calls == 1);
  Expect("miss-hint", g_port.hint == &n30);
  Expect("miss-key-copy", g_port.key_copy == 25u);
  Expect(
      "miss-masked",
      g_port.masked == (reinterpret_cast<std::uint32_t>(&k25) & 0xFFFFFF00u));
  Expect("miss-addr", hit == &fresh.value);
  Expect("miss-deref", *hit == 0xBB25u);

  // 5. Key below every entry: the walk runs to the leftmost node, whose key
  //    is still greater than the searched one, so this is a miss too.
  g_port = PortRecord();
  const std::uint32_t k1 = 1;
  GameGlobal_0059c740_map_get_or_create(&header, &k1);
  Expect("miss-low-hint", g_port.hint == &n10);

  // 6. Key above every entry: the walk runs left all the way to the leftmost
  //    node, which still has a key greater than the searched one, so the
  //    candidate is never replaced and the anchor reaches the port as hint.
  g_port = PortRecord();
  const std::uint32_t k99 = 99;
  GameGlobal_0059c740_map_get_or_create(&header, &k99);
  Expect("miss-high-hint",
         g_port.hint ==
             reinterpret_cast<Opaque59c740TreeNode*>(&header.anchor_left));

  // 7. Empty container: no descent at all, the candidate is the anchor node
  //    at receiver + 0x04, and that address is what reaches the port.
  BuildHeader(&header, nullptr, nullptr, nullptr, 0);
  g_port = PortRecord();
  const std::uint32_t k7 = 7;
  GameGlobal_0059c740_map_get_or_create(&header, &k7);
  Expect("empty-hint", g_port.hint == reinterpret_cast<Opaque59c740TreeNode*>(
                                          &header.anchor_left));
  Expect("empty-no-descent", g_port.calls == 1);

  // 8. The key compare is unsigned (JC/JNC, no sign extension). With the
  //    tree {root: 0, left: 0x80000000} an exact search for 0x80000000 can
  //    only reach the left child under an unsigned compare; a signed compare
  //    reads 0x80000000 as negative and settles on the root instead.
  Opaque59c740MapHeader header2;
  Opaque59c740TreeNode low = {0, 0, 0, 0, 0, 0xCC00};
  Opaque59c740TreeNode high = {0, 0, 0, 0, 0x80000000u, 0xCC01};
  low.left = reinterpret_cast<std::uint32_t>(&high);
  high.parent = reinterpret_cast<std::uint32_t>(&low);
  BuildHeader(&header2, &low, &low, &high, 2);

  g_port = PortRecord();
  const std::uint32_t kbig = 0x80000000u;
  std::uint32_t* big = GameGlobal_0059c740_map_get_or_create(&header2, &kbig);
  Expect("unsigned-cmp-hit", big == &high.value);
  Expect("unsigned-cmp-no-insert", g_port.calls == 0);

  //    And a key between the two leaves the left child as the lower-bound
  //    candidate, which is the value the port receives as its hint.
  g_port = PortRecord();
  const std::uint32_t kmid = 0x40000000u;
  GameGlobal_0059c740_map_get_or_create(&header2, &kmid);
  Expect("unsigned-cmp-miss-hint", g_port.hint == &high);

  if (g_failures == 0) {
    std::printf("59c740 model test: OK\n");
    return 0;
  }
  std::printf("59c740 model test: %d failure(s)\n", g_failures);
  return 1;
}
