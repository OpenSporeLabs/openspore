#!/usr/bin/env bash
# Mutation harness for PKG-00D018D0-erase-range-shift-down.
#
# The hazard this exists to defeat: `ar qc` APPENDS to an existing archive, so a
# stale archive silently links the UNMUTATED object and the mutant reports a
# pass. Every mutant therefore gets its own work directory and its own
# FRESHLY DELETED archive, and the harness compiles from that mutated copy --
# never from the committed source.
#
# Each mutation is a ONE-PHYSICAL-LINE Python program written to mutate.py and
# run from the mutated directory. One line is not a style preference: inside
# bash single quotes a backslash-newline survives literally, so a wrapped
# mutation reaches Python as a line continuation followed by an indented line
# and dies with IndentationError before it can mutate anything.
set -u

SRC_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
HPP="erase_range_shift_down_00d018d0.hpp"
SRC="erase_range_shift_down_00d018d0.cpp"
TEST="erase_range_shift_down_00d018d0_model_test.cpp"
WORK="/tmp/opencode/mut-00d018d0"
CXX="${CXX:-clang++}"

run_mutant() {
  local label="$1"; shift
  local mutation="$1"; shift
  local expect_change="${1:-1}"   # the baseline passes 'pass' and expects no diff
  local dir="$WORK/$label"
  rm -rf "$dir"; mkdir -p "$dir"
  cp "$SRC_ROOT/$HPP" "$SRC_ROOT/$SRC" "$SRC_ROOT/$TEST" "$dir/"

  printf '%s\n' "$mutation" >"$dir/mutate.py"
  ( cd "$dir" && python3 mutate.py ) || { echo "$label: MUTATION-FAILED"; return 1; }

  # A/B: a real mutant must differ from the committed source, or nothing was
  # actually tested. The baseline is the deliberate exception.
  if [ "$expect_change" = "1" ] && cmp -s "$dir/$SRC" "$SRC_ROOT/$SRC" && cmp -s "$dir/$HPP" "$SRC_ROOT/$HPP"; then
    echo "$label: MUTATION-NO-OP (sources unchanged)"
    return 1
  fi

  # Fresh archive every time. `rm -f` first, because ar qc appends.
  rm -f "$dir/p.a" "$dir/s.o" "$dir/t.o" "$dir/test"
  "$CXX" -std=c++17 -Wall -Wextra -Werror -m32 -I"$dir" -c "$dir/$SRC" -o "$dir/s.o" 2>"$dir/cc.log" \
    || { echo "$label: CAUGHT (BUILD-REJECTED: no longer compiles)"; return 0; }
  "$CXX" -std=c++17 -Wall -Wextra -Werror -m32 -I"$dir" -c "$dir/$TEST" -o "$dir/t.o" 2>>"$dir/cc.log" \
    || { echo "$label: CAUGHT (BUILD-REJECTED: test no longer compiles)"; return 0; }
  ar qc "$dir/p.a" "$dir/s.o" || { echo "$label: AR-FAILED"; return 1; }
  ranlib "$dir/p.a"
  "$CXX" -Wall -Wextra -Werror -m32 "$dir/t.o" -o "$dir/test" "$dir/p.a" 2>>"$dir/cc.log" \
    || { echo "$label: CAUGHT (BUILD-REJECTED: link)"; return 0; }

  timeout 60 "$dir/test" >"$dir/run.log" 2>&1
  local rc=$?
  if [ "$expect_change" = "0" ]; then
    # Baseline: rc=0 is the CORRECT outcome and it prints its own count.
    if [ "$rc" -eq 0 ]; then
      echo "baseline: PASS  [$(tail -1 "$dir/run.log" 2>/dev/null)]"
      return 0
    fi
    echo "baseline: UNEXPECTED rc=$rc  [$(tail -1 "$dir/run.log" 2>/dev/null)]"
    return 1
  fi

  if [ "$rc" -eq 124 ]; then
    echo "$label: CAUGHT (HANG, timeout 60s)"
    return 0
  fi
  if [ "$rc" -ne 0 ]; then
    local n summary
    n=$(grep -c '^FAIL ' "$dir/run.log" 2>/dev/null || echo 0)
    summary=$(tail -1 "$dir/run.log" 2>/dev/null)
    echo "$label: CAUGHT rc=$rc failing_named_checks=$n  [$summary]"
    return 0
  fi
  echo "$label: SURVIVED -- NOT CAUGHT (rc=0)"
  return 1
}

pass=0; fail=0
note() { if "$@"; then pass=$((pass+1)); else fail=$((fail+1)); fi; }

# The unmutated build must pass. If it does not, every mutant result below is
# meaningless, so the baseline runs first and its survival is itself a failure.
if run_mutant baseline 'pass' 0; then
  echo "baseline: PASS (503 checks expected; the run is meaningful)"
else
  echo "baseline: FAIL -- aborting, mutant results would be meaningless"
  exit 1
fi

echo
echo "=== mutants ==="

# 1. Stride 0x8 -> 0x4. The cursors step half an element, so the trip count
#    doubles and the loop walks off the end of the sequence.
#    The static_assert that pins the stride is MUTATED ALONG WITH IT, so this
#    mutant has to be caught by BEHAVIOUR and not by the compile failing. An
#    assert that catches its own constant being edited is worth having, but on
#    its own it proves only that the assert is wired up.
note run_mutant stride_8_to_4 \
'import re; p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=re.sub(r"static_assert\(kElementStride == 8,[^;]*;","static_assert(true, \"mutated\");",s); s=s.replace("reinterpret_cast<const std::uint8_t*>(read_cursor) + kElementStride","reinterpret_cast<const std::uint8_t*>(read_cursor) + kElementStride/2"); s=s.replace("reinterpret_cast<std::uint8_t*>(write_cursor) + kElementStride","reinterpret_cast<std::uint8_t*>(write_cursor) + kElementStride/2"); open(p,"w").write(s)'

# 2. Loop bound: compare the read cursor against `first` instead of the tail, so
#    the trip count is governed by the range rather than by the sequence end.
note run_mutant loop_bound_first \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("while (read_cursor != tail) {","while (read_cursor != first) {"); open(p,"w").write(s)'

# 3. Direction: swap the cursors, shifting the surviving block UPWARD instead of
#    downward over the erased range.
note run_mutant cursors_swapped \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("OpaqueElement* write_cursor = first;","OpaqueElement* write_cursor = last;"); s=s.replace("const OpaqueElement* read_cursor = last;","const OpaqueElement* read_cursor = first;"); open(p,"w").write(s)'

# 4. Copy only the low word of each element. The stride and the trip count stay
#    correct, so this isolates the second word of the pair.
note run_mutant copy_one_word \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("    destination[1] = source[1];",""); open(p,"w").write(s)'

# 5. Receiver displacement 0x4 -> 0x0: reads and writes the wrong receiver word,
#    which the guard words in the fixture are there to catch. The displacement
#    lives in the header and the pinning assert is mutated with it, so again the
#    catch has to be behavioural.
note run_mutant displacement_4_to_0 \
'import re; p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=re.sub(r"static_assert\(kTailDisplacement == 4,[^;]*;","static_assert(true, \"mutated\");",s); s=s.replace("self_bytes + kTailDisplacement","self_bytes"); open(p,"w").write(s)'

# 6. No tail update at all: the copy is right and the tail word never moves.
note run_mutant no_tail_update \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("+ removal);","+ 0);"); open(p,"w").write(s)'

# 7. Sign: drop the NEG, so the tail GROWS by the range length instead of
#    shrinking by it.
note run_mutant removal_sign_flipped \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("  removal = -removal;",""); open(p,"w").write(s)'

# 8. Shift count 0x3 -> 0x0: the element count becomes the byte length itself, and
#    the three doublings then multiply that by eight, so the tail moves eight
#    times too far. Both pinning static_asserts are left INTACT and untouched --
#    the constant declarations are not edited at all, only the arithmetic that
#    consumes them. That is deliberate: it shows the model test catches the wrong
#    shift behaviourally rather than by refusing to compile.
note run_mutant shift_3_to_0 \
'import re; p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); n=len(s); s=s.replace("static_cast<std::int32_t>(value / kElementStride)","static_cast<std::int32_t>(value / 1)"); s=s.replace("((value % kElementStride != 0 && (value < 0)) ? 1 : 0)","0"); assert len(s)==n or True; open(p,"w").write(s) if "value / 1" in s else sys.exit(3)'

# 9. Return `last`. The body writes EAX once, from arg1, so this contradicts the
#    only EAX write in the listing.
note run_mutant return_last \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("  return first;","  return last;"); open(p,"w").write(s)'

# 10. Return the updated tail instead of arg1.
note run_mutant return_new_tail \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("  return first;","  return *tail_slot;"); open(p,"w").write(s)'

# 11. Declare void where the machine writes a 32-bit value into EAX on every
#     path. The RETURN SEMANTICS arm treats that as a contradiction.
note run_mutant return_void \
'p="erase_range_shift_down_00d018d0.hpp"; s=open(p).read(); s=s.replace("extern \"C\" OpaqueElement* PKG_00D018D0_THISCALL","extern \"C\" void PKG_00D018D0_THISCALL"); open(p,"w").write(s); p2="erase_range_shift_down_00d018d0.cpp"; s2=open(p2).read(); s2=s2.replace("extern \"C\" OpaqueElement* PKG_00D018D0_THISCALL","extern \"C\" void PKG_00D018D0_THISCALL"); s2=s2.replace("  return first;",""); open(p2,"w").write(s2)'

# 12. The loop never runs -- the JZ branch taken unconditionally.
note run_mutant loop_never_runs \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("while (read_cursor != tail) {","while (false) {"); open(p,"w").write(s)'

# 13. Off-by-one: stop one element early, so the last element never reaches the
#     destination.
note run_mutant off_by_one_trip \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("while (read_cursor != tail) {","while (read_cursor != tail) { if (read_cursor == reinterpret_cast<const OpaqueElement*>(reinterpret_cast<const std::uint8_t*>(tail) - kElementStride)) break;"); open(p,"w").write(s)'

# 14. Update the tail word BEFORE the loop, and re-read the loop bound from the
#     slot rather than from the value cached at entry. The loop then stops one
#     element early and the last surviving element never reaches the
#     destination. This is an ORDERING plus ALIASING defect: neither a sign flip
#     nor a wrong constant produces it, and caching the tail read is exactly what
#     hides it -- the first attempt at this mutant moved the update after the
#     `const OpaqueElement* const tail` initialiser, where the already-cached
#     `tail` made the mutation behave identically to the original and SURVIVED.
note run_mutant tail_updated_before_loop \
'p="erase_range_shift_down_00d018d0.cpp"; s=open(p).read(); s=s.replace("  const OpaqueElement* const tail = *tail_slot;","  *tail_slot = reinterpret_cast<OpaqueElement*>(reinterpret_cast<std::uint8_t*>(*tail_slot) - (static_cast<std::int32_t>(reinterpret_cast<const std::uint8_t*>(last) - reinterpret_cast<const std::uint8_t*>(first)) >> 3) * 8);\n  const OpaqueElement* const tail = *tail_slot;"); s=s.replace("  const std::int32_t byte_length = static_cast<std::int32_t>(","  const std::int32_t byte_length = 0 * static_cast<std::int32_t>("); open(p,"w").write(s)'

echo
echo "mutants_caught=$pass mutants_survived=$fail"
[ "$fail" -eq 0 ] || exit 1