#!/usr/bin/env bash
# Mutation test for reconstruction/staging/pkg-00d38840-global-singleton-getter.
#
# Each mutation below is ONE surgical edit to a COPY of the reconstruction: the
# kind of single-token slip a wrong model would contain. The committed sources
# are never modified -- every mutant is built in its own self-contained directory
# under $WORK, and BOTH translation units are compiled from THAT directory.
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
WORK="$(mktemp -d /tmp/opencode/mut-00d38840-XXXXXX)"
trap 'rm -rf "$WORK"' EXIT

CPP_REL="global_singleton_00d38840.cpp"
HPP_REL="global_singleton_00d38840.hpp"
TEST_REL="global_singleton_00d38840_model_test.cpp"
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

# M1: the LEA form - return the ADDRESS of the slot instead of the stored word.
#     This is the load/LEA distinction, and opcode 0x8d is what a LEA
#     reconstruction of 0x00d38840 would look like.
mutate_src "M1 returns the address of the slot (LEA form)" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  return reinterpret_cast<void*>(
      reinterpret_cast<std::uintptr_t>(&g_creature_mode_strategy_slot));'
# M2: the slot word masked down to 16 bits.
mutate_src "M2 the slot word masked to 16 bits" \
  '      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot & 0xffffu));'
# M3: the slot word shifted right instead of copied.
mutate_src "M3 the slot word shifted right by two" \
  '      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot >> 2));'
# M4: a neighbour step - reading one word below the slot.
mutate_src "M4 reads one word below the slot" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  return reinterpret_cast<void*>(reinterpret_cast<std::uintptr_t>(
      &g_creature_mode_strategy_slot) - kSlotWidth);'
# M5: a store-through the body never makes. The machine opcode is 0xa1, the
#     LOAD direction; 0xa3 is the store. A reconstruction that also published
#     the slot would trip the guard words in group 3.
mutate_src "M5 writes the slot as well as reading it" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  g_creature_mode_strategy_slot += 1u;
  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));'
# M6: a null guard the body has no branch for - the machine returns whatever is
#     stored, so a stored null must come back as a stored null.
mutate_src "M6 substitutes a default for a null slot" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  if (g_creature_mode_strategy_slot == 0u) {
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(0xdeadbeefu));
  }
  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));'
# M7: the slot read through a receiver-shaped access whose displacement is one
#     word too high - the hazard a `[ECX + disp]` family has and an absolute
#     `moffs32` load does not. The base is put 0x40 below the slot so the shape
#     is genuinely register-shaped, and the index is one word past the correct
#     one, so it reads a DIFFERENT address than the baseline does. (An earlier
#     draft of this mutation used index 16 against a 0x40 base, which lands back
#     on the slot itself and is therefore algebraically identical to the
#     baseline - it passed, and passing was the bug.)
mutate_src "M7 the receiver-shaped access off by one word" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  const std::uintptr_t base =
      reinterpret_cast<std::uintptr_t>(&g_creature_mode_strategy_slot) - 0x40u;
  return reinterpret_cast<void*>(reinterpret_cast<std::uint32_t*>(base)[17]);'
# M8: a cached / once-only accessor. The machine has no branch and no static
#     storage - it re-reads the slot on every entry - so a reconstruction that
#     remembered the first value would keep answering with a stale pointer. Both
#     locals are genuinely used, so the mutant is judged on behaviour rather than
#     dying in the build on -Wunused-but-set-variable.
mutate_src "M8 a cached, once-only accessor" \
  '  return reinterpret_cast<void*>(
      static_cast<std::uintptr_t>(g_creature_mode_strategy_slot));' \
  '  static SlotWord cached = 0u;
  static bool primed = false;
  if (!primed) {
    cached = g_creature_mode_strategy_slot;
    primed = true;
  }
  return reinterpret_cast<void*>(static_cast<std::uintptr_t>(cached));'

echo
echo "=== mutations of the stated encoding / constants in the header ==="

# H1: the absolute-move opcode restated as the STORE direction (0xa3), which is
#     the machine-level statement of "this body writes the slot".
mutate_hdr "H1 opcode restated as the store direction 0xa3" \
  '    0xa1,                          // MOV EAX, moffs32 (absolute, no ModRM)' \
  '    0xa3,                          // MOV moffs32, EAX (absolute, no ModRM)'
# H2: the absolute opcode restated as the register-relative MOV r32,r/m32 form.
mutate_hdr "H2 opcode restated as register-relative 0x8b" \
  '    0xa1,                          // MOV EAX, moffs32 (absolute, no ModRM)' \
  '    0x8b,                          // MOV r32, r/m32 (register-relative)'
# H3: the slot address restated one byte lower, so +0x0169e294 becomes
#     +0x0169e290.
mutate_hdr "H3 slot address restated as 0x0169e290" \
  '    0x94, 0xe2, 0x69, 0x01,        // moffs32 = 0x0169e294, little endian' \
  '    0x90, 0xe2, 0x69, 0x01,        // moffs32 = 0x0169e290, little endian'
# H4: the terminator restated as RET imm16, i.e. the callee pops 4 bytes the
#     machine does not pop. The imm16 operand is deliberately NOT appended:
#     adding it would overflow the six-byte encoding array and kill the build on
#     "excess elements", which the harness cannot tell apart from an unrelated
#     build break. Restating the single terminator byte keeps the mutant
#     buildable and lets the package's `!= 0xc2u` static_assert catch the claim.
mutate_hdr "H4 terminator restated as RET imm16" \
  '    0xc3,                          // RET' \
  '    0xc2,                          // RET imm16 (callee would pop)'
# H5: the ABI typedef given a stack argument. The test's std::is_same
#     static_assert against the entry's own declaration stops the build.
mutate_hdr "H5 the ABI typedef given a stack argument" \
  'using AbiGlobalSlotGetter00d38840 = void* (*)();' \
  'using AbiGlobalSlotGetter00d38840 = void* (*)(SlotWord);'
# H6: the ABI typedef restated as void. The same is_same static_assert stops it.
mutate_hdr "H6 the ABI typedef restated as void" \
  'using AbiGlobalSlotGetter00d38840 = void* (*)();' \
  'using AbiGlobalSlotGetter00d38840 = void (*)();'
# H7: the recorded access mode restated as a write, i.e. the reconstruction
#     claiming this body is the constructor's store.
mutate_hdr "H7 the access mode restated as a write" \
  "constexpr char kSlotAccessMode = 'r';" \
  "constexpr char kSlotAccessMode = 'w';"
# H8: the recorded single-writer count restated as several writers.
mutate_hdr "H8 the recorded writer count restated as two" \
  'constexpr std::size_t kSlotRecordedWriteRows = 1;' \
  'constexpr std::size_t kSlotRecordedWriteRows = 2;'
# H9: the recorded direct-call fan-in restated. It must still exceed the
#     distinct-caller count, so this is caught by the shape assertion rather
#     than by the value check alone.
mutate_hdr "H9 the recorded call count restated below the caller count" \
  'constexpr std::size_t kRecordedDirectCallEdges = 59;' \
  'constexpr std::size_t kRecordedDirectCallEdges = 38;'
# H10: the model's slot width restated as 2 bytes, so the load could not be the
#     dword load the machine performs.
mutate_hdr "H10 the slot width restated as two bytes" \
  'using SlotWord = std::uint32_t;' \
  'using SlotWord = std::uint16_t;'

echo
echo "=== summary ==="
echo "refuted: $pass   (by value: $clean, at compile time: $compile_time, by fault: $faulted)"
echo "not refuted or inconclusive: $fail"
if [ "$fail" -ne 0 ]; then
  for m in "${FAILED[@]}"; do echo "  - $m"; done
  exit 1
fi
echo "ALL MUTATIONS REFUTED"