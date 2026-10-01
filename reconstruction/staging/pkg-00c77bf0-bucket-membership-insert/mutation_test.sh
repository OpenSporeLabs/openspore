#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00c77bf0-bucket-membership-insert.
#
# Each mutation below is ONE surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain. The committed sources
# are never modified -- every mutant is built in its own self-contained directory
# under $WORK, and both translation units are compiled from THAT directory.
#
# A mutation PASSES only when the rebuilt model test does NOT exit 0, i.e. when
# the test actually refutes the mutant. Exit 0 from a mutant is a hole in the
# test and fails this harness. Any nonzero exit counts as refuted, and the exit
# code is reported so the three kinds stay distinguishable:
#
#   1  the battery rejected the mutant on a VALUE
#   2  the mutant tripped one of the package's compile-time static_asserts, so
#      it cannot be built at all
#   >128  the mutant faulted; a body that faults has still failed to behave like
#      the reconstruction
#   anything else  the mutant did not compile for an unrelated reason, which is
#      NOT a refutation and is reported as inconclusive
#
# `ar` note: this harness deletes the archive before every link and uses `ar rc`.
# `ar qc` APPENDS to an existing archive, so without the `rm -f` a stale object
# from the previous mutant would silently win the link and every later mutation
# would report a bogus pass.
#
# Usage: ./mutation_test.sh          (CXX=clang++ by default)

set -u

PKG_DIR="$(cd "$(dirname "$0")" && pwd)"
WORK="$(mktemp -d /tmp/opencode/mut-00c77bf0-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="bucket_membership_insert_00c77bf0.cpp"
HPP_REL="bucket_membership_insert_00c77bf0.hpp"
TEST_REL="bucket_membership_insert_00c77bf0_model_test.cpp"
CPP="$PKG_DIR/$CPP_REL"
HPP="$PKG_DIR/$HPP_REL"
TEST="$PKG_DIR/$TEST_REL"

CXX="${CXX:-clang++}"
CXXFLAGS="-m32 -std=c++17 -O2 -Wall -Wextra -Werror"

pass=0
fail=0
clean=0
compile_time=0
faulted=0
FAILED=()

# build_and_run <dir>
#
# <dir> must be SELF-CONTAINED: it holds the impl .cpp, the .hpp under test and
# the model test. That matters because `#include "x.hpp"` resolves relative to
# the directory of the INCLUDING file first, ahead of any -I path. Copying only
# the header into a side directory would therefore silently keep the ORIGINAL
# header and the mutation would never be compiled.
build_and_run() {
  local dir="$1"
  rm -f "$WORK/libmut.a" "$WORK"/impl.o "$WORK"/test.o "$WORK"/run
  if ! $CXX $CXXFLAGS -c "$dir/$CPP_REL" -o "$WORK/impl.o" 2>"$WORK/cc.log"; then
    return 3
  fi
  # Compile the mutant's OWN copy of the test, not $TEST: the test includes the
  # header by relative path, so a test built from $PKG_DIR would pull in the
  # ORIGINAL header and the header mutations would never be exercised.
  if ! $CXX $CXXFLAGS -c "$dir/$TEST_REL" -o "$WORK/test.o" 2>"$WORK/cc2.log"; then
    return 3
  fi
  ar rc "$WORK/libmut.a" "$WORK/impl.o"          # rc, not qc: create, not append
  if ! $CXX $CXXFLAGS -o "$WORK/run" "$WORK/test.o" "$WORK/libmut.a" 2>"$WORK/ld.log"; then
    return 3
  fi
  "$WORK/run" >"$WORK/out.log" 2>&1
  return $?
}

# record <label> <rc>
record() {
  local label="$1" rc="$2"
  if [ "$rc" -eq 0 ]; then
    echo "  *** NOT REFUTED (exit 0) - HOLE IN THE TEST"
    fail=$((fail+1)); FAILED+=("$label")
  elif [ "$rc" -eq 1 ]; then
    echo "  refuted (exit 1: the battery rejected it on a value)"
    pass=$((pass+1)); clean=$((clean+1))
  elif [ "$rc" -eq 3 ]; then
    if grep -q "static assertion failed" "$WORK/cc.log" "$WORK/cc2.log" 2>/dev/null; then
      # Caught by a compile-time invariant in the package rather than by a
      # runtime check. That is still a refutation -- the mutant cannot be built
      # -- but the mechanism is named so the two kinds do not get conflated.
      echo "  refuted (compile time: a static_assert in the package)"
      pass=$((pass+1)); compile_time=$((compile_time+1))
    else
      echo "  INCONCLUSIVE (build problem - not a refutation)"
      sed 's/^/    /' "$WORK/cc.log" 2>/dev/null | head -4
      sed 's/^/    /' "$WORK/cc2.log" 2>/dev/null | head -4
      fail=$((fail+1)); FAILED+=("$label (build)")
    fi
  elif [ "$rc" -gt 128 ]; then
    echo "  refuted (the mutant faulted: signal $((rc-128)) - it misbehaved)"
    pass=$((pass+1)); faulted=$((faulted+1))
  else
    echo "  INCONCLUSIVE (rc=$rc - not a refutation)"
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

echo "=== mutations of the reconstruction source ==="

# M1: mask the index down to a power-of-two bound instead of taking the remainder.
mutate_src "M1 index masked instead of the remainder" \
  'static_cast<std::size_t>(key % bucket_count) *' \
  'static_cast<std::size_t>(key & (bucket_count - 1u)) *'
# M2: the DIV's quotient instead of its remainder.
mutate_src "M2 quotient instead of remainder" \
  'static_cast<std::size_t>(key % bucket_count) *' \
  'static_cast<std::size_t>(key / bucket_count) *'
# M3: the two receiver words swapped.
mutate_src "M3 the two receiver words swapped" \
  'word_at(bytes, kBucketCountDisplacement)' \
  'word_at(bytes, kBucketArrayDisplacement)'
# M4: the array read one word too high.
mutate_src "M4 array displacement off by four" \
  'word_at(bytes, kBucketArrayDisplacement)' \
  'word_at(bytes, kBucketCountDisplacement)'
# M5: the bucket index used as a byte offset, dropping the SIB scale of four.
mutate_src "M5 bucket indexed by bytes" \
  'static_cast<std::size_t>(key % bucket_count) *
                               kBucketSlotBytes' \
  'static_cast<std::size_t>(key % bucket_count)'
# M6: compare the link word instead of the key word.
mutate_src "M6 compares the link word, not the key" \
  'if (node_word(link, kNodeKeyDisplacement) == key) {' \
  'if (node_word(link, kNodeNextDisplacement) == key) {'
# M7: follow the key word instead of the link word.
mutate_src "M7 follows the key word, not the link" \
  'link = node_word(link, kNodeNextDisplacement);' \
  'link = node_word(link, kNodeKeyDisplacement);'
# M8: the byte store at 0x00c77c28 treated as a no-op, so the whole key is passed.
mutate_src "M8 third argument is the key unchanged" \
  'FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);' \
  'FUN_00de5df0(container, &value, key);'
# M9: Ghidra's reading of the third argument taken literally.
mutate_src "M9 third argument is a literal zero" \
  'FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);' \
  'FUN_00de5df0(container, &value, 0u);'
# M10: the first two arguments handed over in the wrong order.
mutate_src "M10 the two pointer arguments swapped" \
  'FUN_00de5df0(container, &value, key & kArgumentSlotLowByteMask);' \
  'FUN_00de5df0(&value, reinterpret_cast<const Word*>(container), key & kArgumentSlotLowByteMask);'
# M11: the insert runs on a hit as well as on a miss.
mutate_src "M11 inserts even on a hit" \
  '  if (!present) {' \
  '  if (true) {'
# M12: the flag inverted.
mutate_src "M12 returns the inverted flag" \
  '  return present;
}' \
  '  return !present;
}'
# M13: a store into the receiver the machine never makes. The body's one store
#      is a single byte into its own incoming argument slot.
mutate_src "M13 writes a word into the receiver" \
  '      ++matches;' \
  '      ++matches;
      *const_cast<Word*>(reinterpret_cast<const Word*>(bytes)) = key;'
# M14: the insert never happens.
mutate_src "M14 never inserts on a miss" \
  '  if (!present) {' \
  '  if (false) {'

echo
echo "=== mutations of the stated encoding / constants in the header ==="

# H1: the terminator restated as a bare RET, i.e. the entry pops nothing.
mutate_hdr "H1 terminator restated as a bare RET" \
  '    0xc2, 0x04, 0x00,                    // 0x00c77c4c RET 0x4' \
  '    0xc3,                                // 0x00c77c4c RET'
# H2: the ECX bias restated one word lower.
mutate_hdr "H2 receiver bias restated as 0x1118" \
  '    0x81, 0xc1, 0x1c, 0x11, 0x00, 0x00,  // 0x00c77bfa ADD ECX,0x111c' \
  '    0x81, 0xc1, 0x18, 0x11, 0x00, 0x00,  // 0x00c77bfa ADD ECX,0x111c'
# H3: the divisor's disp8 restated, so +0x1120 becomes +0x1121.
mutate_hdr "H3 divisor disp8 restated as 0x05" \
  '    0xf7, 0x71, 0x08,                    // 0x00c77c04 DIV [ECX+0x8]' \
  '    0xf7, 0x71, 0x05,                    // 0x00c77c04 DIV [ECX+0x8]'
# H4: the SIB scale restated as x1 instead of x4.
mutate_hdr "H4 SIB scale restated as x1" \
  '    0x8b, 0x14, 0x90,                    // 0x00c77c0c MOV EDX,[EAX+EDX*0x4]' \
  '    0x8b, 0x14, 0x80,                    // 0x00c77c0c MOV EDX,[EAX+EDX*0x4]'
# H5: the one-byte store at 0x00c77c28 restated as a four-byte one.
mutate_hdr "H5 argument-slot store restated as four bytes" \
  '    0x88, 0x5c, 0x24, 0x20,              // 0x00c77c28 MOV [ESP+0x20],BL' \
  '    0x89, 0x5c, 0x24, 0x20,              // 0x00c77c28 MOV [ESP+0x20],BL'
# H6: the callee's rel32 repointed somewhere else.
mutate_hdr "H6 the call's rel32 repointed" \
  '    0xe8, 0xac, 0xe1, 0x16, 0x00,        // 0x00c77c3f CALL 0x00de5df0' \
  '    0xe8, 0xad, 0xe1, 0x16, 0x00,        // 0x00c77c3f CALL 0x00de5df0'
# H7: the node's link displacement restated as 0.
mutate_hdr "H7 node link displacement restated as 0" \
  'constexpr std::size_t kNodeNextDisplacement =
    static_cast<std::size_t>(kTargetBytes[42]);' \
  'constexpr std::size_t kNodeNextDisplacement = 0u;'
# H8: the ABI typedef given a second stack argument. The test's std::is_same
#     static_assert against the entry's own declaration stops the build.
mutate_hdr "H8 the ABI typedef given a second stack argument" \
  '    bool(PKG_00C77BF0_CALL*)(BucketTable*, Word);' \
  '    bool(PKG_00C77BF0_CALL*)(BucketTable*, Word, Word);'
# H9: the entry declared to return void. The same is_same static_assert stops it.
mutate_hdr "H9 the ABI typedef restated as void" \
  '    bool(PKG_00C77BF0_CALL*)(BucketTable*, Word);' \
  '    void(PKG_00C77BF0_CALL*)(BucketTable*, Word);'
# H10: the low-byte mask restated as the identity, i.e. the byte store ignored.
mutate_hdr "H10 the low-byte mask restated as the identity" \
  '    ~static_cast<Word>((Word(1) << (8u * kArgumentSlotStoreWidthBytes)) - Word(1));' \
  '    ~static_cast<Word>(0u);'

echo
echo "=== summary ==="
echo "refuted: $pass   (by value: $clean, at compile time: $compile_time, by fault: $faulted)"
echo "not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"
