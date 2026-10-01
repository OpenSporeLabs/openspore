#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00c772c0-hashset-contains-key.
#
# Each mutation below is one surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain. The committed sources
# are never modified.
#
# A mutation PASSES only when the rebuilt model test does NOT exit 0, i.e. when
# the test actually refutes the mutant. Exit 0 from a mutant is a hole in the
# test and fails this harness. Any nonzero exit counts as refuted: a mutant that
# crashes has still failed to behave like the reconstruction, and the harness
# reports the exit code so the distinction stays visible.
#
# `ar` note: this harness deletes the archive before every link and uses `ar rc`.
# `ar qc` APPENDS to an existing archive, so without the `rm -f` a stale object
# from the previous mutant would silently win the link and every later mutation
# would report a bogus pass.
#
# Self-containment note: the mutant directory holds the impl .cpp, the .hpp and
# the model test together, and the TEST is compiled from that directory. Both
# matter: `#include "x.hpp"` resolves relative to the directory of the INCLUDING
# file first, ahead of any -I path, so a test built from $PKG_DIR would pull in
# the ORIGINAL header and the header mutations would never be exercised.
#
# Usage: ./mutation_test.sh          (CXX=clang++ by default)

set -u

PKG_DIR="$(cd "$(dirname "$0")" && pwd)"
WORK="$(mktemp -d /tmp/opencode/mut-00c772c0-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="hashset_contains_key_00c772c0.cpp"
HPP_REL="hashset_contains_key_00c772c0.hpp"
TEST_REL="hashset_contains_key_00c772c0_model_test.cpp"
CPP="$PKG_DIR/$CPP_REL"
HPP="$PKG_DIR/$HPP_REL"
TEST="$PKG_DIR/$TEST_REL"

CXX="${CXX:-clang++}"
CXXFLAGS="-m32 -std=c++17 -O2"

# No core dumps: several mutants dereference a wild pointer on purpose, and the
# system core handler is slow enough to dominate the run. The exit signal is
# what `record` judges, and a core file tells us nothing extra.
ulimit -c 0 2>/dev/null || true

pass=0
fail=0
FAILED=()

# build_and_run <dir> -- <dir> must be self-contained (impl + header + test).
build_and_run() {
  local dir="$1"
  rm -f "$WORK/libmut.a" "$WORK"/impl.o "$WORK"/test.o "$WORK"/run
  if ! $CXX $CXXFLAGS -I"$dir" -c "$dir/$CPP_REL" -o "$WORK/impl.o" 2>"$WORK/cc.log"; then
    echo "  BUILD-ERROR"; sed 's/^/    /' "$WORK/cc.log" | head -6; return 3
  fi
  if ! $CXX $CXXFLAGS -I"$dir" -c "$dir/$TEST_REL" -o "$WORK/test.o" 2>"$WORK/cc2.log"; then
    echo "  TEST-BUILD-ERROR"; sed 's/^/    /' "$WORK/cc2.log" | head -6; return 3
  fi
  ar rc "$WORK/libmut.a" "$WORK/impl.o"          # rc, not qc: create, not append
  if ! $CXX $CXXFLAGS -o "$WORK/run" "$WORK/test.o" "$WORK/libmut.a" 2>"$WORK/ld.log"; then
    echo "  LINK-ERROR"; sed 's/^/    /' "$WORK/ld.log" | head -6; return 3
  fi
  # `timeout` so a mutant that never terminates is reported as an inconclusive
  # build/run problem instead of hanging the whole harness.
  timeout 20 "$WORK/run" >"$WORK/out.log" 2>&1
  return $?
}

# record <label> <rc>
record() {
  local label="$1" rc="$2"
  if [ "$rc" -eq 0 ]; then
    echo "  *** NOT REFUTED (exit 0) - HOLE IN THE TEST"
    fail=$((fail+1)); FAILED+=("$label")
  elif [ "$rc" -eq 1 ]; then
    echo "  refuted (exit 1, clean diagnostic)"
    pass=$((pass+1))
    sed 's/^/    /' "$WORK/out.log" | head -4
  elif [ "$rc" -gt 128 ]; then
    echo "  refuted (crashed, signal $((rc-128)) - mutant misbehaved)"
    pass=$((pass+1))
  elif [ "$rc" -eq 124 ]; then
    # `timeout` fired: the mutant looped forever. A hang means the mutant never
    # produced the observed value, but it is not a diagnostic, so it is reported
    # as inconclusive rather than counted as a clean refutation.
    echo "  INCONCLUSIVE (timed out - the mutant never returned)"
    fail=$((fail+1)); FAILED+=("$label (timeout)")
  elif grep -q "static assertion failed" "$WORK/cc.log" "$WORK/cc2.log" 2>/dev/null; then
    # Caught by a compile-time invariant in the package rather than by a runtime
    # check. That is still a refutation - the mutant cannot be built - so it
    # counts, but the mechanism is named so the distinction stays visible.
    echo "  refuted (caught by a compile-time static_assert in the package)"
    pass=$((pass+1))
  else
    # Any other build or link error: the mutant did not compile for an
    # unrelated reason and the test could not judge it. NOT a refutation.
    echo "  INCONCLUSIVE (rc=$rc, build/link problem - not a refutation)"
    fail=$((fail+1)); FAILED+=("$label rc=$rc")
  fi
}

# mutate_dir <label> <file-to-edit> <from> <to>
mutate_dir() {
  local label="$1" target_rel="$2" from="$3" to="$4"
  echo "== $label"
  local dir="$WORK/d_$(printf '%s' "$label" | tr -c 'A-Za-z0-9' '_')"
  mkdir -p "$dir"
  cp "$CPP" "$dir/$CPP_REL"
  cp "$HPP" "$dir/$HPP_REL"
  cp "$TEST" "$dir/$TEST_REL"
  if ! grep -qF -- "$from" "$dir/$target_rel"; then
    echo "  ANCHOR-NOT-FOUND in $target_rel: $from"
    fail=$((fail+1)); FAILED+=("$label (anchor missing)"); return
  fi
  FROM="$from" TO="$to" FILE="$dir/$target_rel" python3 - <<'PY'
import os, sys
path, frm, to = os.environ['FILE'], os.environ['FROM'], os.environ['TO']
s = open(path).read()
i = s.find(frm)                      # first occurrence only: keep it surgical
if i < 0:
    sys.exit("anchor absent")
open(path, 'w').write(s[:i] + to + s[i+len(frm):])
PY
  build_and_run "$dir"; record "$label" $?
}

mutate_src() { mutate_dir "$1" "$CPP_REL" "$2" "$3"; }
mutate_hdr() { mutate_dir "$1" "$HPP_REL" "$2" "$3"; }

echo "=== baseline: unmutated sources must PASS (exit 0) ==="
build_and_run "$PKG_DIR"
rc=$?
if [ "$rc" -ne 0 ]; then
  echo "  *** BASELINE FAILS (rc=$rc); the harness cannot judge the mutants"
  sed 's/^/    /' "$WORK/out.log" 2>/dev/null | head -20
  exit 1
fi
echo "  baseline passes"
echo

echo "=== mutations of the bucket index: the DIV remainder ==="
# M1: signed modulo. The unsigned remainder of 0x80000000 by 3 is 2, which is
# where the fixture puts the chain; a signed modulo yields -2, i.e. a read
# before the table, and the key is missed.
mutate_src "M1 signed modulo instead of unsigned" \
  'const std::uint32_t bucket_index = key % bucket_count;' \
  'const std::uint32_t bucket_index = static_cast<std::uint32_t>(static_cast<std::int32_t>(key) % static_cast<std::int32_t>(bucket_count));'
# M2: the quotient instead of the remainder. DIV leaves the quotient in EAX and
# the remainder in EDX; keeping the wrong half is the classic register slip.
mutate_src "M2 quotient instead of remainder" \
  'const std::uint32_t bucket_index = key % bucket_count;' \
  'const std::uint32_t bucket_index = key / bucket_count;'
# M3: a power-of-two mask instead of a modulo. The fixture count of 5 is not a
# power of two, so the two cannot coincide.
mutate_src "M3 mask instead of modulo" \
  'const std::uint32_t bucket_index = key % bucket_count;' \
  'const std::uint32_t bucket_index = key & (bucket_count - 1u);'
# M4: no modulo at all - the key used directly as the index.
mutate_src "M4 key used directly as the bucket index" \
  'const std::uint32_t bucket_index = key % bucket_count;' \
  'const std::uint32_t bucket_index = key;'

echo
echo "=== mutations of the bucket load ==="
# M5: a scale of 8 instead of the SIB scale of 4. The fixture installs the key
# in exactly the bucket a scale-of-8 model would reach, so the mutant finds it
# and the real body must not.
mutate_src "M5 bucket index scaled by 8 instead of 4" \
  'OpaqueBucketLink* link = buckets[bucket_index];' \
  'OpaqueBucketLink* link = buckets[bucket_index * 2u];'
# M6: the base word read from the count displacement instead of the base
# displacement, i.e. +0x1124 read as a pointer.
mutate_src "M6 bucket base read from the count word" \
  'reinterpret_cast<OpaqueBucketLink* const*>(container->bucket_base_1120)' \
  'reinterpret_cast<OpaqueBucketLink* const*>(reinterpret_cast<std::uintptr_t>(container) + kBucketCountDisplacement)'

echo
echo "=== mutations of the chain walk ==="
# M7: the comparison inverted. Every positive hit fixture fails.
mutate_src "M7 comparison inverted" \
  'if (link->key_00 == key) {' \
  'if (link->key_00 != key) {'
# M8: the loop-carried link taken from the +0x0 word instead of +0x4. The
# fixture plants a valid link ADDRESS in the +0x0 word and a null in +0x4, so a
# +0x0-following model reaches the key and the real body does not.
mutate_src "M8 next link taken from +0x0 instead of +0x4" \
  'link = link->next_04;' \
  'link = reinterpret_cast<OpaqueBucketLink*>(static_cast<std::uintptr_t>(link->key_00));'
# M9: the null-head guard dropped, so an empty bucket dereferences a null link.
# The body has TEST/JZ exactly here; a model without it cannot survive the
# empty-container fixture.
mutate_src "M9 null-head guard dropped" \
  'while (link != nullptr) {' \
  'while (true) {'
# M10: the walk advances TWO links at a time, i.e. it visits the head and the
# tail and skips every link in between. The three-link fixture puts a match at
# the middle link, which this mutant never reads. The replacement stays
# null-safe so the mutant terminates: a self-referential `link = link` would
# spin forever, and a hang is inconclusive rather than a refutation.
mutate_src "M10 walk skips every second link" \
  'link = link->next_04;' \
  'link = link->next_04 == nullptr ? nullptr : link->next_04->next_04;'

echo
echo "=== mutations of the return value ==="
# M11: the count compared for equality with one rather than tested for
# non-zeroness. A chain holding the key twice must still answer 1, and this
# mutant answers 0 there.
mutate_src "M11 count compared == 1 instead of != 0" \
  'const bool found = (match_count != 0u);' \
  'const bool found = (match_count == 1u);'
# M12: the counter incremented unconditionally - the guard on the match is
# effectively dropped, so the answer becomes "is the chain non-empty" rather
# than "is the key in the chain". An absent-key query against a populated chain
# is a hit here and a miss in the real body.
#
# A first attempt at this slot returned `(match_count & 0xff) != 0`, which is
# NOT a wrong model at all: for any chain shorter than 256 links it is
# identical to the observed `TEST ESI,ESI / SETNZ AL`, and the harness correctly
# reported the mutant as unrefuted. That was a defect in the MUTATION rather
# than a hole in the test, and it is recorded here so the substitution is not
# later mistaken for a silently dropped case.
mutate_src "M12 counter incremented unconditionally" \
  'if (link->key_00 == key) {' \
  'if (link->key_00 == key || true) {'
# M13: the flag inverted, i.e. a miss reported as a hit.
mutate_src "M13 result flag inverted" \
  'const bool found = (match_count != 0u);' \
  'const bool found = (match_count == 0u);'

echo
echo "=== mutations of the stated encoding in the header ==="
# H1: the SIB scale byte restated as scale 8.
mutate_hdr "H1 SIB byte restated with scale 8" \
  '0x8b, 0x14, 0x90, 0x85, 0xd2, 0x74, 0x0d, 0x90, 0x3b, 0x3a, 0x75, 0x01,' \
  '0x8b, 0x14, 0x98, 0x85, 0xd2, 0x74, 0x0d, 0x90, 0x3b, 0x3a, 0x75, 0x01,'
# H2: the DIV divisor displacement restated as 0x1120.
mutate_hdr "H2 divisor displacement restated as 0x1120" \
  '0x24, 0x11, 0x00, 0x00, 0x8b, 0x81, 0x20, 0x11, 0x00, 0x00, 0x33, 0xf6,' \
  '0x20, 0x11, 0x00, 0x00, 0x8b, 0x81, 0x20, 0x11, 0x00, 0x00, 0x33, 0xf6,'
# H3: the terminator stated as RET 0, i.e. caller cleanup.
mutate_hdr "H3 terminator restated as RET 0 (caller cleanup)" \
  '0x5f, 0x0f, 0x95, 0xc0, 0x5e, 0xc2, 0x04, 0x00,' \
  '0x5f, 0x0f, 0x95, 0xc0, 0x5e, 0xc3, 0x00, 0x00,'
# H4: SETNZ restated as SETZ, which inverts the result.
mutate_hdr "H4 SETNZ restated as SETZ" \
  '0x5f, 0x0f, 0x95, 0xc0, 0x5e, 0xc2, 0x04, 0x00,' \
  '0x5f, 0x0f, 0x94, 0xc0, 0x5e, 0xc2, 0x04, 0x00,'
# H5: the EAX clear restated as something else, so the upper 24 bits of the
# result are no longer provably zero. The anchor is confined to ONE line of the
# header's constant table: a hand-written anchor that spans the table's line
# break matches nothing, and the harness reports that as a missing anchor rather
# than as a refutation.
mutate_hdr "H5 EAX clear restated as MOV EAX,ECX" \
  '0x75, 0xf4, 0x33, 0xc0, 0x85, 0xf6,' \
  '0x75, 0xf4, 0x89, 0xc1, 0x85, 0xf6,'
# H6: the next-link displacement restated as +0x0. Caught by the package's
# offsetof assert at compile time; the mechanism is named by `record`.
mutate_hdr "H6 kLinkNextDisplacement restated as 0x0" \
  'constexpr std::size_t kLinkNextDisplacement = 0x4;' \
  'constexpr std::size_t kLinkNextDisplacement = 0x0;'
# H7: the bucket scale restated as 8. Caught by the package's scale assert at
# compile time.
mutate_hdr "H7 kBucketScale restated as 8" \
  'constexpr std::size_t kBucketScale = 4;' \
  'constexpr std::size_t kBucketScale = 8;'
# H8: the receiver extent restated so the count no longer ends it. Caught by
# the package's sizeof assert at compile time.
mutate_hdr "H8 modeled receiver extent restated as 0x1130" \
  'static_assert(sizeof(OpaqueBucketContainer) == 0x1128,' \
  'static_assert(sizeof(OpaqueBucketContainer) == 0x1130,'

echo
echo "=== summary ==="
echo "refuted: $pass   not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"
