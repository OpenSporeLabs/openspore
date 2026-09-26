#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-resource-state-wave10
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

for config in $binaries; do
  case "$config" in
    o0) flags="-O0" ;;
    o2) flags="-O2" ;;
    o0-ndebug) flags="-O0 -DNDEBUG" ;;
    o2-ndebug) flags="-O2 -DNDEBUG" ;;
  esac
  binary="$work_dir/$config"
  clang++ -m32 -std=c++17 $flags -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/resource_state_wave10.cpp" \
    "$package_dir/resource_state_wave10_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done

python3 - $disassembly <<'PY'
import re
import sys

HEADER = re.compile(r"^[0-9a-f]+ <(?P<name>.+)>:$")
STEP = re.compile(
    r"^\s*[0-9a-f]+:\s+(?P<mnemonic>[a-z][a-z0-9.]*)\s*(?P<operands>.*)$"
)
MEMORY = re.compile(r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]")
FRAME = ("esp", "ebp")
DIRECT = re.compile(r"^(?:[0-9a-f]+ <|[0-9a-f]+$|\S+@plt)")
THUNK = re.compile(r"\+0x[0-9a-f]+>$")
BRANCH = re.compile(r"^j(?!mp$)[a-z]+$")

RELEASE_MASK = 0x01
OBSERVED_OFFSETS = (
    0x00,
    0x08,
    0x0C,
    0x10,
    0x24,
    0x28,
    0x2C,
    0x30,
    0x44,
    0x48,
)
OBSERVED_HANDLE_QUAD = (0x4C, 0x50, 0x54)

ENTRY = "record_write_get_state_00e310c0"
DESTROY = "record_write_destroy_00e30f90"
UNTRACK = "record_write_untrack_00f47380"
SWEEP = "record_write_chunk_sweep_00e308d0"
DROP = "record_write_drop_handle_00571db0"


def parse(path):
    bodies = {}
    current = None
    for line in open(path, encoding="utf-8"):
        header = HEADER.match(line.rstrip("\n"))
        if header is not None:
            name = header.group("name").split("(", 1)[0].rsplit("::", 1)[-1]
            current = bodies.setdefault(name, [])
            continue
        if current is None:
            continue
        step = STEP.match(line.rstrip("\n"))
        if step is not None:
            current.append(
                (step.group("mnemonic"), step.group("operands").strip())
            )
    return bodies


def body_of(bodies, path, name):
    if name not in bodies:
        raise SystemExit(f"{path}: {name} symbol missing")
    return bodies[name]


def returns(body, path, name):
    found = set()
    for mnemonic, operands in body:
        if mnemonic != "ret":
            continue
        if operands and not re.fullmatch(r"0x[0-9a-f]+", operands):
            raise SystemExit(f"{path}: {name} releases {operands}")
        found.add(int(operands, 16) if operands else 0)
    if not found:
        raise SystemExit(f"{path}: {name} has no return")
    return found


def calls(body):
    return [
        operands
        for mnemonic, operands in body
        if mnemonic == "call" and not THUNK.search(operands)
    ]


def call_sites(body):
    return [
        (index, operands)
        for index, (mnemonic, operands) in enumerate(body)
        if mnemonic == "call" and not THUNK.search(operands)
    ]


def indirect(body):
    return [operands for operands in calls(body) if not DIRECT.match(operands)]


def immediate_offsets(body):
    found = set()
    for mnemonic, operands in body:
        if mnemonic not in ("mov", "and", "or", "add", "sub", "cmp", "test"):
            continue
        for part in operands.split(","):
            token = part.strip()
            if re.fullmatch(r"0x[0-9a-f]+", token):
                found.add(int(token, 16))
    return found


def displacements(operands):
    found = set()
    for memory in MEMORY.finditer(operands):
        if memory.group("base") in FRAME:
            continue
        found.add(int(memory.group("disp"), 16) if memory.group("disp") else 0)
    return found


def all_displacements(body):
    found = set()
    for _, operands in body:
        found |= displacements(operands)
    return found


def compares_against_zero(body):
    zero = re.compile(r"(?:0x0+|0)")
    for mnemonic, operands in body:
        if mnemonic not in ("cmp", "test"):
            continue
        parts = [part.strip() for part in operands.split(",")]
        if len(parts) == 1 and zero.fullmatch(parts[0]):
            return True
        if len(parts) == 2 and (zero.fullmatch(parts[1]) or parts[0] == parts[1]):
            return True
    return False


for path in sys.argv[1:]:
    bodies = parse(path)

    entry = body_of(bodies, path, ENTRY)
    if returns(entry, path, ENTRY) != {0x04}:
        raise SystemExit(
            f"{path}: {ENTRY} releases {sorted(returns(entry, path, ENTRY))}"
            f" instead of one callee cleaned stack word"
        )
    if indirect(entry).__len__() != 2:
        raise SystemExit(
            f"{path}: {ENTRY} performs {len(indirect(entry))} port dispatches"
            " instead of two"
        )
    if len(calls(entry)) != len(indirect(entry)):
        raise SystemExit(
            f"{path}: {ENTRY} performs a direct call where a port dispatch is"
            " required"
        )
    if not any(
        re.search(r",\s*0x0?1$", operands)
        for mnemonic, operands in entry
        if mnemonic in ("and", "test")
    ):
        raise SystemExit(f"{path}: {ENTRY} never narrows the argument with 0x1")
    sites = call_sites(entry)
    guard = [
        index
        for index, (mnemonic, _) in enumerate(entry)
        if BRANCH.match(mnemonic) and index < sites[-1][0]
    ]
    if not guard:
        raise SystemExit(
            f"{path}: {ENTRY} reaches its second dispatch without a branch"
        )
    if not any(
        mnemonic == "mov" and operands.startswith("eax")
        for mnemonic, operands in reversed(entry)
    ):
        raise SystemExit(f"{path}: {ENTRY} never materialises its return value")

    destroy = body_of(bodies, path, DESTROY)
    if returns(destroy, path, DESTROY) != {0x00}:
        raise SystemExit(
            f"{path}: {DESTROY} releases"
            f" {sorted(returns(destroy, path, DESTROY))} instead of nothing"
        )
    reached = immediate_offsets(destroy) | all_displacements(destroy)
    for offset in OBSERVED_OFFSETS:
        if offset not in reached:
            raise SystemExit(
                f"{path}: {DESTROY} never reaches the observed offset {offset:#04x}"
            )
    vectorised = any(mnemonic.startswith("movups") for mnemonic, _ in destroy)
    for offset in OBSERVED_HANDLE_QUAD:
        if offset in reached:
            continue
        if vectorised:
            continue
        raise SystemExit(
            f"{path}: {DESTROY} never forwards the handle argument {offset:#04x}"
        )
    if not compares_against_zero(destroy):
        raise SystemExit(f"{path}: {DESTROY} never compares a field against zero")
    if indirect(destroy) and len(indirect(destroy)) < 2:
        raise SystemExit(
            f"{path}: {DESTROY} performs {len(indirect(destroy))} inline port"
            " dispatches instead of at least two"
        )
    reached_leaves = 0
    for leaf in ("record_write_drop_handle_00571db0",
                 "record_write_chunk_sweep_00e308d0",
                 "record_write_untrack_00f47380"):
        if any(leaf in operands for operands in calls(destroy)):
            reached_leaves += 1
    if indirect(destroy):
        reached_leaves += len(indirect(destroy))
    if reached_leaves < 3:
        raise SystemExit(
            f"{path}: {DESTROY} reaches {reached_leaves} leaves instead of three"
        )

    untrack = body_of(bodies, path, UNTRACK)
    if returns(untrack, path, UNTRACK) != {0x00}:
        raise SystemExit(
            f"{path}: {UNTRACK} releases"
            f" {sorted(returns(untrack, path, UNTRACK))} instead of nothing"
        )
    if len(indirect(untrack)) != 1:
        raise SystemExit(
            f"{path}: {UNTRACK} performs {len(indirect(untrack))} port dispatches"
            " instead of one"
        )
    if not compares_against_zero(untrack):
        raise SystemExit(f"{path}: {UNTRACK} never guards its null sentinel")

    sweep = body_of(bodies, path, SWEEP)
    if returns(sweep, path, SWEEP) != {0x08}:
        raise SystemExit(
            f"{path}: {SWEEP} releases {sorted(returns(sweep, path, SWEEP))}"
            " instead of two callee cleaned stack words"
        )
    if len(indirect(sweep)) != 1:
        raise SystemExit(
            f"{path}: {SWEEP} performs {len(indirect(sweep))} port dispatches"
            " instead of one"
        )

    drop = body_of(bodies, path, DROP)
    if returns(drop, path, DROP) != {0x00}:
        raise SystemExit(
            f"{path}: {DROP} releases {sorted(returns(drop, path, DROP))} instead"
            " of nothing"
        )
    if len(indirect(drop)) != 1:
        raise SystemExit(
            f"{path}: {DROP} performs {len(indirect(drop))} port dispatches"
            " instead of one"
        )
    incoming = False
    outgoing = False
    for mnemonic, operands in drop:
        for memory in MEMORY.finditer(operands):
            if memory.group("base") not in FRAME or not memory.group("disp"):
                continue
            if int(memory.group("disp"), 16) > 0:
                incoming = True
        if mnemonic.startswith("mov") and re.search(
            r"\[(?:esp|ebp)\](?:,|$)", operands
        ):
            outgoing = True
    if not incoming:
        raise SystemExit(f"{path}: {DROP} never reads its incoming stack arguments")
    if not outgoing:
        raise SystemExit(f"{path}: {DROP} never forwards its arguments")
PY
