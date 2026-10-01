#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00c6a960-refcount-increment.
#
# Each mutation below is one surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain (wrong displacement,
# wrong increment, saturating instead of wrapping, returning the pre-increment
# value, dropping the store, misstating the encoding). The committed sources are
# never modified.
#
# A mutation PASSES only when the rebuilt model test does NOT exit 0, i.e. when
# the test actually refutes the mutant. Exit 0 from a mutant is a hole in the
# test and fails this harness. Any nonzero exit counts as refuted: a mutant that
# crashes has still failed to behave like the reconstruction, and the harness
# reports the exit code so the distinction is visible.
#
# `ar` note: this harness deletes the archive before every link and uses `ar rc`.
# `ar qc` APPENDS to an existing archive, so without the `rm -f` a stale object
# from the previous mutant would silently win the link and every later mutation
# would report a bogus pass.
#
# Usage: ./mutation_test.sh          (CXX=clang++ by default)

set -u

PKG_DIR="$(cd "$(dirname "$0")" && pwd)"
WORK="$(mktemp -d /tmp/opencode/mut-00c6a960-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="refcount_increment_00c6a960.cpp"
HPP_REL="refcount_increment_00c6a960.hpp"
TEST_REL="refcount_increment_00c6a960_model_test.cpp"
CPP="$PKG_DIR/$CPP_REL"
HPP="$PKG_DIR/$HPP_REL"
TEST="$PKG_DIR/$TEST_REL"

CXX="${CXX:-clang++}"
CXXFLAGS="-m32 -std=c++17 -O2"

pass=0
fail=0
FAILED=()

# build_and_run <dir>
#
# <dir> must be SELF-CONTAINED: it holds the impl .cpp, the .hpp under test and
# the model test. That matters because `#include "x.hpp"` resolves relative to
# the directory of the INCLUDING file first, ahead of any -I path. Copying only
# the header into a side directory would therefore silently keep the ORIGINAL
# header and the mutation would never be compiled - the mutation would appear to
# "pass" while nothing had changed at all.
build_and_run() {
  local dir="$1"
  rm -f "$WORK/libmut.a" "$WORK"/impl.o "$WORK"/test.o "$WORK"/run
  if ! $CXX $CXXFLAGS -I"$dir" -c "$dir/$CPP_REL" -o "$WORK/impl.o" 2>"$WORK/cc.log"; then
    echo "  BUILD-ERROR"; sed 's/^/    /' "$WORK/cc.log" | head -6; return 3
  fi
  # Compile the mutant's OWN copy of the test, not $TEST: the test includes the
  # header by relative path, so a test built from $PKG_DIR would pull in the
  # ORIGINAL header and the header mutations would never be exercised.
  if ! $CXX $CXXFLAGS -I"$dir" -c "$dir/$TEST_REL" -o "$WORK/test.o" 2>"$WORK/cc2.log"; then
    echo "  TEST-BUILD-ERROR"; sed 's/^/    /' "$WORK/cc2.log" | head -6; return 3
  fi
  ar rc "$WORK/libmut.a" "$WORK/impl.o"          # rc, not qc: create, not append
  if ! $CXX $CXXFLAGS -o "$WORK/run" "$WORK/test.o" "$WORK/libmut.a" 2>"$WORK/ld.log"; then
    echo "  LINK-ERROR"; sed 's/^/    /' "$WORK/ld.log" | head -6; return 3
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
    echo "  refuted (exit 1, clean diagnostic)"
    pass=$((pass+1))
  elif [ "$rc" -gt 128 ]; then
    echo "  refuted (crashed, signal $((rc-128)) - mutant misbehaved)"
    pass=$((pass+1))
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
# Builds a self-contained mutant directory (impl + header + test), applies one
# surgical edit to <file-to-edit>, and runs the test against it.
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

# mutate_src <label> <from> <to>   -- mutates the .cpp, headers stay original
mutate_src() {
  mutate_dir "$1" "$CPP_REL" "$2" "$3"
}

# mutate_hdr <label> <from> <to>   -- mutates the .hpp, the .cpp stays original
mutate_hdr() {
  mutate_dir "$1" "$HPP_REL" "$2" "$3"
}

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
# M1: increment the word at +0x4 instead of +0x8.
mutate_src "M1 wrong displacement (+0x4 instead of +0x8)" \
  'word_at(receiver, kCounterDisplacement)' \
  'word_at(receiver, kCounterDisplacement - 4)'
# M2: add 2 rather than 1 (the classic double-increment slip).
mutate_src "M2 increment of 2 instead of 1" \
  'static_cast<std::uint32_t>(kCounterIncrement));' \
  'static_cast<std::uint32_t>(kCounterIncrement) + 1u);'
# M3: pre-increment return - return the value as it stood before the store.
mutate_src "M3 pre-increment return" \
  'return *counter;' \
  'return static_cast<std::int32_t>(static_cast<std::uint32_t>(*counter) - 1u);'
# M4: saturating increment instead of the observed wrap.
mutate_src "M4 saturating at 0x7fffffff" \
  '*counter = static_cast<std::int32_t>(' \
  '*counter = (*counter == 0x7fffffff) ? *counter : static_cast<std::int32_t>('
# M5: drop the write-through; read and add but never store.
mutate_src "M5 no write-back" \
  '*counter = static_cast<std::int32_t>(' \
  'static_cast<void>(counter), static_cast<std::int32_t>('
# M6: 16-bit truncation of the add.
mutate_src "M6 16-bit truncation of the add" \
  'static_cast<std::uint32_t>(*counter) +' \
  'static_cast<std::uint32_t>(static_cast<std::uint16_t>(*counter)) +'
# M7: return the receiver instead of the incremented word.
mutate_src "M7 returns the receiver" \
  'return *counter;' \
  'return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(receiver));'

echo
echo "=== mutations of the stated encoding / constants in the header ==="
# H1: the INC EAX opcode in kTargetBytes is changed to something else.
mutate_hdr "H1 encoding byte 3 is not INC EAX" \
  '0x8b, 0x41, 0x08, 0x40, 0x89, 0x41, 0x08, 0xc3,' \
  '0x8b, 0x41, 0x08, 0x41, 0x89, 0x41, 0x08, 0xc3,'
# H2: the displacement byte stated in kTargetBytes no longer matches +0x8.
mutate_hdr "H2 encoding displacement byte is not 0x8" \
  '0x8b, 0x41, 0x08, 0x40, 0x89, 0x41, 0x08, 0xc3,' \
  '0x8b, 0x41, 0x04, 0x40, 0x89, 0x44, 0x04, 0xc3,'
# H3: the terminator is stated as RET 4 (callee cleanup) rather than a bare RET.
mutate_hdr "H3 terminator stated as RET 4, not bare RET" \
  '0x8b, 0x41, 0x08, 0x40, 0x89, 0x41, 0x08, 0xc3,' \
  '0x8b, 0x41, 0x08, 0x40, 0x89, 0x41, 0x08, 0xc2,'
# H4: the header's displacement constant is restated as +0x4.
mutate_hdr "H4 kCounterDisplacement restated as 0x4" \
  'constexpr std::size_t kCounterDisplacement = 0x8;' \
  'constexpr std::size_t kCounterDisplacement = 0x4;'
# H5: the increment constant is restated as 2.
mutate_hdr "H5 kCounterIncrement restated as 2" \
  'constexpr std::int32_t kCounterIncrement = 1;' \
  'constexpr std::int32_t kCounterIncrement = 2;'
# H6: narrow the counted word to a byte and pad the struct so sizeof is
# unchanged. The package's own offsetof assert catches the layout change at
# compile time rather than at runtime; it is still a refutation, and `record`
# names that mechanism so the two kinds are not conflated.
mutate_hdr "H6 counted word narrowed to a byte with slack padding" \
  'std::int32_t counter_008 = 0;                  // +0x08, read and written' \
  'std::uint8_t counter_008 = 0;                  // +0x08, read and written
  std::uint8_t slack_009[3]{};                   // pad so sizeof stays 0x0c'
# H7: restate the modeled receiver extent. Caught by the package's sizeof
# assert at compile time. Kept because the extent claim is part of what this
# package asserts, and a silent change to it must not compile.
mutate_hdr "H7 modeled receiver extent restated as 0x10" \
  'static_assert(sizeof(OpaqueRefCountedReceiver) == 0x0c,' \
  'static_assert(sizeof(OpaqueRefCountedReceiver) == 0x10,'

echo
echo "=== summary ==="
echo "refuted: $pass   not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"