#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00e31100-shared-zero-result-stub.
#
# Each mutation below is one surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain (one-byte write instead
# of four, a non-zero result, a callee-popping terminator, wrong slot index,
# misstating the encoding). The committed sources are never modified.
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
WORK="$(mktemp -d /tmp/opencode/mut-00e31100-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="shared_zero_result_00e31100.cpp"
HPP_REL="shared_zero_result_00e31100.hpp"
TEST_REL="shared_zero_result_00e31100_model_test.cpp"
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
# M1: return one instead of zero. The classic "near enough" slip.
mutate_src "M1 returns 1 instead of 0" \
  '  return 0;
}' \
  '  return 1;
}'
# M2: return -1. A mutant that differs from 0 only in sign must still be refuted,
# which pins that the test reads the value and not merely its zero-ness.
mutate_src "M2 returns -1" \
  '  return 0;
}' \
  '  return -1;
}'
# M3: return a non-zero pattern, exercising the full 32-bit read.
mutate_src "M3 returns 0x12345678" \
  '  return 0;
}' \
  '  return static_cast<std::int32_t>(0x12345678u);
}'
# M4: read the receiver and answer from it - the mutant a wrong model of a
# "default value from this" member function would contain.
mutate_src "M4 returns the receiver pointer" \
  'shared_zero_result_00e31100(void*) {' \
  'shared_zero_result_00e31100(void* receiver) {
  return static_cast<std::int32_t>(reinterpret_cast<std::uintptr_t>(receiver));'
# M5: read one byte of the receiver - a narrower receiver read, still a read the
# body does not make.
mutate_src "M5 reads the receiver's first byte" \
  'shared_zero_result_00e31100(void*) {' \
  'shared_zero_result_00e31100(void* receiver) {
  return receiver != nullptr ? 1 : 0;'
# M6: turn the entry into a DISPATCHER - load the receiver's vtable, read slot 8
# and return that function pointer. This is the mutation the VIRTUAL DISPATCH
# check exists to catch: 0x00e31100 is a dispatch TARGET (508 vftables hold it
# as a slot value) and its two-instruction body names no indirect transfer
# through a register or a memory operand. Reachable here because the model test
# hands it a carrier whose slot 8 holds the nonzero reference stub.
#
# Note on what is deliberately NOT mutated: a C++ body that returns 0 cannot be
# "narrowed" at the source level, so there is no source mutation for the
# one-byte-vs-four-byte width claim - a mutant writing a zero byte and a mutant
# writing a zero word compile to the same thing. That claim is a DECLARATION
# claim and is exercised where it lives: H1 (the encoding names the full
# register) and H5 (the entry's own return width, checked against the entry's
# own declaration rather than a restatement of it).
mutate_src "M6 entry turned into a vtable dispatcher" \
  'shared_zero_result_00e31100(void*) {' \
  'shared_zero_result_00e31100(void* receiver) {
  const SharedZeroResultVTable* table =
      *reinterpret_cast<const SharedZeroResultVTable* const*>(receiver);
  return static_cast<std::int32_t>(
      reinterpret_cast<std::uintptr_t>(table->slot_8_shared_zero_result));'

echo
echo "=== mutations of the stated encoding / constants in the header ==="
# H1: the first encoding byte is restated as the 0x00b1e4d0 XOR AL,AL opcode.
mutate_hdr "H1 encoding is XOR AL,AL (30 c0), not XOR EAX,EAX" \
  '0x33,  // 0x00e31100 XOR EAX,EAX' \
  '0x30,  // 0x00e31100 XOR AL,AL'
# H2: the ModRM byte is restated as something other than c0.
mutate_hdr "H2 ModRM byte is not 0xc0" \
  '0xc0,  //   XOR EAX,EAX, ModRM c0' \
  '0xc8,  //   XOR EAX,EAX, ModRM c8'
# H3: the terminator is stated as RET 4 (callee cleanup) rather than a bare RET.
mutate_hdr "H3 terminator stated as RET 4, not bare RET" \
  '0xc3,  // 0x00e31102 RET' \
  '0xc2,  // 0x00e31102 RET 4'
# H4: the slot index in the modelled image moves from 8 to 9. The two-level
# dispatch test reads offset 32, so a table whose slot-8 field no longer holds
# the entry address is reachable only through the wrong offset and the
# discrimination check fails.
mutate_hdr "H4 slot index restated as 9 (offset 36)" \
  'std::array<std::uint32_t, 8> leading_slots{};       // slots 0..7 unobserved
  std::uint32_t slot_8_shared_zero_result = 0x00e31100u;  // this table'"'"'s slot 8' \
  'std::array<std::uint32_t, 9> leading_slots{};       // slots 0..8 unobserved
  std::uint32_t slot_8_shared_zero_result = 0x00e31100u;  // this table'"'"'s slot 8'
# H5: the ENTRY's own declared return width is narrowed to a byte. The anchor is
# the entry declaration, not the AbiSharedZeroResult00e31100 typedef: an earlier
# version of this harness mutated the typedef and was NOT REFUTED, because the
# header then asserted only sizeof(std::int32_t) == 4, which the typedef
# satisfied regardless of what the entry declared. The header now checks the
# width off decltype(shared_zero_result_00e31100), so narrowing the entry cannot
# pass silently.
mutate_hdr "H5 entry declared return narrowed to a byte" \
  'std::int32_t PKG_00E31100_SHARED_ZERO_RESULT_THISCALL
shared_zero_result_00e31100(void*);' \
  'std::uint8_t PKG_00E31100_SHARED_ZERO_RESULT_THISCALL
shared_zero_result_00e31100(void*);'
# H6: the padding byte is restated as NOP, misstating what follows the body.
mutate_hdr "H6 padding byte restated as 0x90 (NOP)" \
  'constexpr std::uint8_t kPaddingByte = 0xcc;' \
  'constexpr std::uint8_t kPaddingByte = 0x90;'

echo
echo "=== summary ==="
echo "refuted: $pass   not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"