#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-01021090-space-player-empire-id.
#
# Each mutation below is one surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain (wrong displacement,
# displacement read as an element count, the LEA form instead of the MOV form,
# a substituted default, a null guard the machine does not have, a 16-bit
# truncate, a write-back, returning the pointer instead of the word). The
# committed sources are never modified.
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
WORK="$(mktemp -d /tmp/opencode/mut-01021090-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="space_player_empire_id_01021090.cpp"
HPP_REL="space_player_empire_id_01021090.hpp"
TEST_REL="space_player_empire_id_01021090_model_test.cpp"
CPP="$PKG_DIR/$CPP_REL"
HPP="$PKG_DIR/$HPP_REL"
TEST="$PKG_DIR/$TEST_REL"

CXX="${CXX:-clang++}"
# The default flags, deliberately: the model's inline-asm stack sampler needs a
# normal PIE link, and -fno-pie makes the 32-bit link emit a DT_TEXTREL that
# faults before main() is reached. The encoding cross-check below compiles its
# own object with -fno-pic, which is where the opcode shape actually matters.
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
    sed 's/^/    /' "$WORK/out.log" 2>/dev/null | head -4
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

echo "=== encoding cross-check: the entry must reproduce the nine observed bytes ==="
# Not a mutation: a positive check that the compiled body is instruction-for-
# instruction the body read live at 0x01021090. -fno-pic/-fno-pie matter here -
# under the default PIE the compiler reaches the global through a call/pop pair
# and the body stops resembling the original.
rm -f "$WORK/enc.o"
if $CXX -m32 -std=c++17 -O2 -fno-pic -fno-pie -c "$PKG_DIR/$CPP_REL" -o "$WORK/enc.o" 2>/dev/null; then
# Keep only the hex byte column of each instruction line, then concatenate.
  got=$(objdump -d -M intel "$WORK/enc.o" \
        | sed -n '/<space_player_empire_id_01021090>:/,/ret/p' \
        | sed -n 's/^ *[0-9a-f]*:\t\([0-9a-f ]*\)\t.*/\1/p' \
        | tr -d ' \n')
  # The relocation supplies the moffs32 immediate at link time, so the object's
  # own copy of those four bytes reads 00000000. Compare the OPCODES and the
  # ModRM/disp8 shape, which are what the source controls.
  shape=$(printf '%s' "$got" | sed -e 's/a100000000/A/' -e 's/8b4018/B/' -e 's/c3$/C/')
  if [ "$shape" = "ABC" ]; then
    echo "  opcodes a1 / 8b 40 18 / c3 match the body read at 0x01021090"
  else
    echo "  *** compiled opcode shape [$shape] does not match a1/8b4018/c3"
  fi
else
  echo "  SKIPPED (could not build the encoding object)"
fi
echo

echo "=== mutations of the reconstruction source ==="
# M1: read the neighbouring word one slot lower (+0x14 instead of +0x18).
mutate_src "M1 wrong displacement (+0x14 instead of +0x18)" \
  'empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement)' \
  'empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement - 4)'
# M2: read the displacement as an ELEMENT count, i.e. 0x18 * 4 = 0x60.
mutate_src "M2 displacement read as an element count (x4)" \
  'empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement)' \
  'empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement * 4)'
# M3: substitute a constant for the published word.
mutate_src "M3 constant instead of the published word" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return 0x5a5a5a5au;'
# M4: return the published POINTER instead of the word at the displacement -
# the LEA-shaped wrong answer.
mutate_src "M4 returns the published pointer, not the word" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(g_016dda8c));'
# M5: mask the word to 16 bits, keeping the displacement and the read shape.
mutate_src "M5 mask to 16 bits" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return static_cast<std::uint32_t>(static_cast<std::uint16_t>(*empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement)));'
# M6: write the loaded word back through the object before returning it.
mutate_src "M6 write the word back before returning it" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return *const_cast<std::uint32_t*>(empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement)) = 0u, 0u;'
# M7: add the null guard the machine does not have, returning a sentinel. The
# body has no compare and no branch, so this is a claim the listing refutes.
mutate_src "M7 null guard returning a sentinel" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return g_016dda8c == nullptr ? 0xffffffffu : *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);'
# M8: return the displacement itself.
mutate_src "M8 returns the displacement" \
  'return *empire_id_word(g_016dda8c, kPlayerEmpireIdDisplacement);' \
  'return static_cast<std::uint32_t>(kPlayerEmpireIdDisplacement);'

echo
echo "=== mutations of the stated encoding / layout in the header ==="
# H1: the disp8 byte in the stated encoding no longer matches +0x18.
mutate_hdr "H1 encoding disp8 byte is 0x14, not 0x18" \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x18, 0xc3,' \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x14, 0xc3,'
# H2: the second instruction restated as LEA (0x8d) instead of MOV (0x8b).
mutate_hdr "H2 encoding opcode 0x8b -> 0x8d (LEA)" \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x18, 0xc3,' \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8d, 0x40, 0x18, 0xc3,'
# H3: the terminator restated as RET 4 (callee cleanup) rather than a bare RET.
mutate_hdr "H3 encoding tail 0xc3 -> 0xc2 (RET imm16)" \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x18, 0xc3,' \
  '0xa1, 0x8c, 0xda, 0x6d, 0x01, 0x8b, 0x40, 0x18, 0xc2,'
# H4: the header's displacement constant restated as +0x14. The package ties it
# to offsetof() of the fixture member, so this cannot compile.
mutate_hdr "H4 kPlayerEmpireIdDisplacement restated as 0x14" \
  'constexpr std::size_t kPlayerEmpireIdDisplacement = 0x18u;' \
  'constexpr std::size_t kPlayerEmpireIdDisplacement = 0x14u;'
# H5: the global's address restated. Both the encoding table's immediate and the
# kGlobalAddress constant name it, and the two are tied by static_assert.
mutate_hdr "H5 global address restated (kGlobalAddress)" \
  'constexpr std::uint32_t kGlobalAddress = 0x016dda8cu;' \
  'constexpr std::uint32_t kGlobalAddress = 0x016dda90u;'
# H6: narrow the declared word to 16 bits. PlayerEmpireIdWord types BOTH the
# fixture member and the read, so this is a narrowing of the load itself, and
# the static_assert that pins the width rejects it at compile time.
mutate_hdr "H6 declared word narrowed to 16 bits" \
  'using PlayerEmpireIdWord = std::uint32_t;' \
  'using PlayerEmpireIdWord = std::uint16_t;'
# H7: widen the declared word to 64 bits. The width assert rejects it; the
# object-extent assert would reject it too if the width one were removed, so
# this mutant exercises both invariants at once.
mutate_hdr "H7 declared word widened to 64 bits" \
  'using PlayerEmpireIdWord = std::uint32_t;' \
  'using PlayerEmpireIdWord = std::uint64_t;'

echo
echo "=== summary ==="
echo "refuted: $pass   not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"