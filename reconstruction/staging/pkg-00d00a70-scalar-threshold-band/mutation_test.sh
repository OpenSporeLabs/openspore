#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00d00a70-scalar-threshold-band.
#
# Each mutation below is one surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model of 0x00d00a70 would contain (a wrong
# band edge, a band number off by one, a flipped comparator, the clamp bounds
# transposed, MAXSS and MINSS swapped, a boundary made half-open that the
# listing has closed). The committed sources are never modified.
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
# SELF-CONTAINED DIRECTORY note: each mutant directory holds the impl .cpp, the
# .hpp AND the model test, and the test is compiled from that directory. A test
# built from $PKG_DIR would resolve `#include "x.hpp"` relative to the package
# and silently pick up the ORIGINAL header, so a header mutation would appear to
# pass while nothing had changed.
#
# Usage: ./mutation_test.sh          (CXX=clang++ by default)

set -u

PKG_DIR="$(cd "$(dirname "$0")" && pwd)"
WORK="$(mktemp -d /tmp/opencode/mut-00d00a70-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="scalar_threshold_band_00d00a70.cpp"
HPP_REL="scalar_threshold_band_00d00a70.hpp"
TEST_REL="scalar_threshold_band_00d00a70_model_test.cpp"
CPP="$PKG_DIR/$CPP_REL"
HPP="$PKG_DIR/$HPP_REL"
TEST="$PKG_DIR/$TEST_REL"

CXX="${CXX:-clang++}"
CXXFLAGS="-m32 -std=c++17 -O2"

pass=0
fail=0
FAILED=()

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
  "$WORK/run" >"$WORK/out.log" 2>&1
  return $?
}

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
    echo "  refuted (caught by a compile-time static_assert in the package)"
    pass=$((pass+1))
  else
    echo "  INCONCLUSIVE (rc=$rc, build/link problem - not a refutation)"
    fail=$((fail+1)); FAILED+=("$label rc=$rc")
  fi
}

mutate_dir() {
  local label="$1" target_rel="$2" from="$3" to="$4"
  echo "== $label"
  local dir="$WORK/d_$(printf '%s' "$label" | tr -c 'A-Za-z0-9' '_')"
  mkdir -p "$dir"
  cp "$CPP" "$dir/$CPP_REL"
  cp "$HPP" "$dir/$HPP_REL"
  cp "$TEST" "$dir/$TEST_REL"
  # The anchor is located in Python, not with `grep -F`: grep matches line by
  # line, so a multi-line anchor silently reports "not found" and the mutant is
  # never built -- which would read as a pass rather than as a broken mutation.
  # One Python invocation does both the search and the edit, and exits 2 when the
  # anchor is absent so the shell can tell that apart from a build failure.
  local edit_rc=0
  FROM="$from" TO="$to" FILE="$dir/$target_rel" python3 - <<'PY' || edit_rc=$?
import os, sys
path, frm, to = os.environ['FILE'], os.environ['FROM'], os.environ['TO']
s = open(path).read()
i = s.find(frm)                      # first occurrence only: keep it surgical
if i < 0:
    sys.exit(2)
open(path, 'w').write(s[:i] + to + s[i + len(frm):])
PY
  if [ "$edit_rc" -ne 0 ]; then
    echo "  ANCHOR-NOT-FOUND in $target_rel"
    fail=$((fail+1)); FAILED+=("$label (anchor missing)"); return
  fi
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
echo "  baseline passes: $(grep -o 'checks=[0-9]*' "$WORK/out.log" | head -1)"
echo

echo "=== mutations of the band arithmetic in the .cpp ==="
# M1: band 2's lower edge read from the wrong slot (+0x10 instead of +0x14).
mutate_src "M1 band-2 lower edge from +0x10 instead of +0x14" \
  'const float edge14 = band_edge(receiver, kEdgeDisplacement14);' \
  'const float edge14 = band_edge(receiver, kEdgeDisplacement10);'
# M2: band 2's upper edge read from the wrong slot (+0x1c instead of +0x18).
mutate_src "M2 band-2 upper edge from +0x1c instead of +0x18" \
  '!comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)' \
  '!comiss_jbe(band_edge(receiver, kEdgeDisplacement1c), clamped)'
# M3: band 2's lower half made non-strict -- the listing has it open.
mutate_src "M3 band-2 lower edge made inclusive" \
  '!comiss_jbe(clamped, edge14)' \
  '!comiss_jc(clamped, edge14)'
# M4: band 2's upper half made non-strict -- the listing has it open.
mutate_src "M4 band-2 upper edge made inclusive" \
  '!comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)' \
  '!comiss_jc(band_edge(receiver, kEdgeDisplacement18), clamped)'
# M5: band 1's upper half flipped -- the listing has v <= f14 (JC on the
# reversed compare), which includes f14 itself.
mutate_src "M5 band-1 upper edge made exclusive" \
  '!comiss_jc(edge14, clamped)' \
  '!comiss_jbe(edge14, clamped)'
# M6: band 1's lower half dropped, so the band swallows everything below f14.
mutate_src "M6 band-1 lower edge check dropped" \
  '  if (!comiss_jc(edge14, clamped) &&
      !comiss_jbe(clamped, band_edge(receiver, kEdgeDisplacement10))) {' \
  '  if (!comiss_jc(edge14, clamped)) {'
# M7: band 4's edge read from +0x18 instead of +0x1c.
mutate_src "M7 band-4 edge from +0x18 instead of +0x1c" \
  'if (!comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement1c))) {
    // 00d00b0c MOV EAX,0x4' \
  'if (!comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement18))) {
    // 00d00b0c MOV EAX,0x4'
# M8: a band number off by one (band 3 becomes 2).
mutate_src "M8 band 3 renumbered to 2" \
  '    // 00d00afa MOV EAX,0x3
    return 3;' \
  '    // 00d00afa MOV EAX,0x3
    return 2;'
# M9: the band chain reordered -- band 1 tested before band 2.
mutate_src "M9 band 1 tested before band 2" \
  '  if (!comiss_jbe(clamped, edge14) && !comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)) {
    // 00d00ade MOV EAX,0x2
    return 2;
  }' \
  '  if (!comiss_jc(edge14, clamped) &&
      !comiss_jbe(clamped, band_edge(receiver, kEdgeDisplacement10))) {
    return 1;
  }
  if (!comiss_jbe(clamped, edge14) && !comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)) {
    // 00d00ade MOV EAX,0x2
    return 2;
  }'
# M10: the clamp's two operations transposed, which sends a NaN out the UPPER
# bound instead of the lower one.
mutate_src "M10 clamp order transposed (min before max)" \
  'const float clamped = minss(maxss(value, kClampLowerBound), kClampUpperBound);' \
  'const float clamped = maxss(minss(value, kClampUpperBound), kClampLowerBound);'
# M11: the clamp dropped entirely, so the raw callee value reaches the bands.
mutate_src "M11 clamp dropped" \
  'const float clamped = minss(maxss(value, kClampLowerBound), kClampUpperBound);' \
  'const float clamped = value;'
# M12: MAXSS taken to keep the FIRST source on an unordered pair, so the NaN
# leaves the clamp unchanged and lands in the fall-through band 0 instead of
# being folded onto the lower bound.
mutate_hdr "M12 maxss keeps the first source on unordered" \
  '  return (unordered_self(dst) || unordered_self(src)) ? src' \
  '  return (unordered_self(dst) || unordered_self(src)) ? dst'
# M13: a JBE guard loses its negation -- the branch is read as TAKEN rather than
# NOT taken, which inverts that band. (Degrading the HELPER to `a <= b` would be
# an equivalent mutation: the guards are all negated, and `!(a <= b || unordered)`
# is exactly `a > b`, so no runtime case could separate them. That is why this
# mutation changes the guard, not the helper.)
mutate_src "M13 band-2 lower JBE guard loses its negation" \
  'if (!comiss_jbe(clamped, edge14) && !comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)) {' \
  'if (comiss_jbe(clamped, edge14) && comiss_jbe(band_edge(receiver, kEdgeDisplacement18), clamped)) {'
# M14: a JC guard loses its negation.
mutate_src "M14 band-4 JC guard loses its negation" \
  'if (!comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement1c))) {' \
  'if (comiss_jc(clamped, band_edge(receiver, kEdgeDisplacement1c))) {'
# M15: the three forwarded words are reordered on their way to the callee.
mutate_src "M15 forwarded words reordered" \
  'const float value = evaluate_scalar_00d05a20(receiver, first, second, third);' \
  'const float value = evaluate_scalar_00d05a20(receiver, third, second, first);'
# M16: the receiver written through, which the listing never does.
mutate_src "M16 receiver written through" \
  '  // 00d00ac4 MOVSS XMM1,dword ptr [ESI+0x14]' \
  '  *reinterpret_cast<float*>(reinterpret_cast<std::uintptr_t>(receiver) + kEdgeDisplacement14) = 0.0F;
  // 00d00ac4 MOVSS XMM1,dword ptr [ESI+0x14]'

echo
echo "=== mutations of the stated constants in the .hpp ==="
# H1: the +0x14 displacement constant restated as +0x10.
mutate_hdr "H1 kEdgeDisplacement14 restated as 0x10" \
  'inline constexpr std::size_t kEdgeDisplacement14 = 0x14;' \
  'inline constexpr std::size_t kEdgeDisplacement14 = 0x10;'
# H2: the +0x18 displacement constant restated as +0x14.
mutate_hdr "H2 kEdgeDisplacement18 restated as 0x14" \
  'inline constexpr std::size_t kEdgeDisplacement18 = 0x18;' \
  'inline constexpr std::size_t kEdgeDisplacement18 = 0x14;'
# H3: the +0x1c displacement constant restated as +0x18.
mutate_hdr "H3 kEdgeDisplacement1c restated as 0x18" \
  'inline constexpr std::size_t kEdgeDisplacement1c = 0x1c;' \
  'inline constexpr std::size_t kEdgeDisplacement1c = 0x18;'
# H4: the +0x10 displacement constant restated as +0x14.
mutate_hdr "H4 kEdgeDisplacement10 restated as 0x14" \
  'inline constexpr std::size_t kEdgeDisplacement10 = 0x10;' \
  'inline constexpr std::size_t kEdgeDisplacement10 = 0x14;'
# H5: the lower clamp bound given the upper bound's value.
mutate_hdr "H5 lower clamp bound restated as +10.0" \
  'inline constexpr float kClampLowerBound = -10.0F;  // [0x01478d5c] @ 0x00d00ab2' \
  'inline constexpr float kClampLowerBound = 10.0F;   // [0x01478d5c] @ 0x00d00ab2'
# H6: the upper clamp bound given the lower bound's value.
mutate_hdr "H6 upper clamp bound restated as -10.0" \
  'inline constexpr float kClampUpperBound = 10.0F;   // [0x01478d60] @ 0x00d00ab8' \
  'inline constexpr float kClampUpperBound = -10.0F;  // [0x01478d60] @ 0x00d00ab8'
# H7: the modelled receiver extent shortened, which the body's +0x1c read needs.
# Caught by the package's own sizeof static_assert at compile time.
mutate_hdr "H7 modelled receiver extent restated as 0x18" \
  'static_assert(sizeof(OpaqueReceiver) == 0x20,' \
  'static_assert(sizeof(OpaqueReceiver) == 0x18,'
# H8: the entry's return type restated as a float, which the five integer
# immediates in EAX refute. The declared function-pointer type still has to
# line up, so this is caught at compile time.
mutate_hdr "H8 entry return type restated as float" \
  'using AbiScalarThresholdBand00d00a70 =
    std::int32_t(PKG_00D00A70_THISCALL*)(OpaqueReceiver*, ForwardedWord,
                                         ForwardedWord, ForwardedWord);' \
  'using AbiScalarThresholdBand00d00a70 =
    float(PKG_00D00A70_THISCALL*)(OpaqueReceiver*, ForwardedWord,
                                  ForwardedWord, ForwardedWord);'

echo
echo "=== summary ==="
echo "refuted: $pass   not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"
