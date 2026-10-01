#!/usr/bin/env bash
# External perturbation gate for pkg-00e3a270-hashed-property-dispatch.
#
# The model test's own mutants live in the test file. That is not sufficient on
# its own: a battery can in principle be written to agree with a wrong body. So
# the reconstruction's OWN body is perturbed here, in a COPY of the package
# directory, and BOTH translation units are rebuilt FROM THE MUTATED DIRECTORY
# under the promotion gate. Every perturbation must be caught -- at RUN time by a
# failing model test, at COMPILE time by -Werror or a static_assert, or at LINK
# time.
#
# The archive is DELETED before each link and rebuilt with `ar rc`, so no link can
# silently pick up a stale object.
#
# A perturbation whose edit does not match, or which changes nothing, is a SETUP
# FAILURE and is counted as MISSED. That is deliberate: a gate that quietly
# perturbs nothing would otherwise report a clean run.
set -u
set -o pipefail

SRC=/home/juanr/Proyectos/OpenSpore/reconstruction/staging/pkg-00e3a270-hashed-property-dispatch
EDITS=/tmp/opencode/perturb-edits
WORK=/tmp/opencode/perturb-00e3a270
CPP=hashed_property_dispatch_00e3a270.cpp
HPP=hashed_property_dispatch_00e3a270.hpp
TEST=hashed_property_dispatch_00e3a270_model_test.cpp

GATE=(-std=c++17 -Wall -Wextra -Werror -m32)

pass=0
fail=0

build_and_run() {
  local dir="$1" out rc
  rm -f "$dir"/*.o "$dir"/libmut.a "$dir"/mut
  out=$( (cd "$dir" && clang++ "${GATE[@]}" -c "$CPP" -o mut.o) 2>&1 ); rc=$?
  if [ $rc -ne 0 ]; then printf 'COMPILE_CPP'; printf '%s' "$out" | head -2; return; fi
  out=$( (cd "$dir" && clang++ "${GATE[@]}" -c "$TEST" -o mut_test.o) 2>&1 ); rc=$?
  if [ $rc -ne 0 ]; then printf 'COMPILE_TEST'; printf '%s' "$out" | head -2; return; fi
  # The archive is deleted above and rebuilt with `ar rc`.
  (cd "$dir" && ar rc libmut.a mut.o mut_test.o && ranlib libmut.a) >/dev/null 2>&1 || { printf 'ARCHIVE'; return; }
  out=$( (cd "$dir" && clang++ -m32 libmut.a -o mut) 2>&1 ); rc=$?
  if [ $rc -ne 0 ]; then printf 'LINK'; printf '%s' "$out" | head -2; return; fi
  out=$( (cd "$dir" && ./mut 2>&1) ); rc=$?
  printf 'RUN:%d' "$rc"
  printf '%s' "$out" | grep -m2 '^FAIL' | sed 's/^/\n      /'
}

report() {
  local label="$1" dir="$2" verdict detail
  verdict=$(build_and_run "$dir")
  case "$verdict" in
    RUN:0) detail="*** NOT CAUGHT -- the model test PASSED a wrong body ***"; fail=$((fail+1));;
    RUN:*) detail="CAUGHT AT RUN TIME (exit ${verdict#RUN:})"; pass=$((pass+1));;
    *)    detail="CAUGHT AT ${verdict%%:*} TIME"; pass=$((pass+1));;
  esac
  echo "  $label: $detail"
}

perturb() {
  local label="$1" file="$2" edit="$3" dir="$WORK"
  rm -rf "$dir"; mkdir -p "$dir"
  cp "$SRC/$CPP" "$SRC/$HPP" "$SRC/$TEST" "$dir/"
  if ! (cd "$dir" && python3 "$EDITS/$edit" "$file" >/dev/null 2>&1); then
    echo "  $label: SETUP FAILED (edit did not match)"; fail=$((fail+1)); return
  fi
  if cmp -s "$SRC/$file" "$dir/$file"; then
    echo "  $label: SETUP FAILED (perturbation changed nothing)"; fail=$((fail+1)); return
  fi
  report "$label" "$dir"
}

echo "=== baseline: the unperturbed package must PASS ==="
rm -rf "$WORK"; mkdir -p "$WORK"
cp "$SRC/$CPP" "$SRC/$HPP" "$SRC/$TEST" "$WORK/"
(cd "$WORK" && clang++ "${GATE[@]}" -c "$CPP" -o mut.o \
  && clang++ "${GATE[@]}" -c "$TEST" -o mut_test.o \
  && ar rc libmut.a mut.o mut_test.o && ranlib libmut.a \
  && clang++ -m32 libmut.a -o mut && ./mut)
baseline_rc=$?
if [ $baseline_rc -ne 0 ]; then
  echo "BASELINE FAILED (exit $baseline_rc) -- the gate is meaningless"
  exit 1
fi
echo "  baseline: PASS (exit 0)"
echo
echo "=== perturbations of the reconstruction's own body ==="

perturb "unsigned dispatch (signed_greater -> unsigned >)"        "$HPP" e01.py
perturb "four-store arm writes +0x2a4 instead of +0x2ac"           "$CPP" e02.py
perturb "four-store arm's middle pair in SOURCE order (the swap)"  "$CPP" e03.py
perturb "lazy pair inverted (primary unconditional, sec. guarded)" "$CPP" e04.py
perturb "tag guard read as a truth test (== -1 becomes == 0)"      "$CPP" e05.py
perturb "callee given index 2 instead of 3"                        "$CPP" e06.py
perturb "copy destination +0x2c0 -> +0x2c4"                        "$CPP" e07.py
perturb "one level of indirection (pointer_at -> word address)"    "$HPP" e08.py
perturb "null guard added at the TOP of the body"                  "$CPP" e09.py
perturb "null guard removed from the three-store arm"              "$CPP" e10.py
perturb "return type narrowed to 16 bits"                          "$HPP" e11.py

echo
echo "=== summary ==="
echo "  caught: $pass"
echo "  missed: $fail"
[ "$fail" -eq 0 ]
