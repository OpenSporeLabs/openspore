#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-prop-resource-safe-wave9
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
    -I "$package_dir" "$package_dir/prop_resource_safe_wave9.cpp" \
    "$package_dir/prop_resource_safe_wave9_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done

python3 - $disassembly <<'PY'
import re
import sys

INSN = re.compile(
    r"^\s*(?P<addr>[0-9a-f]+):\s+(?P<mnemonic>\S+)\s*(?P<operands>.*)$", re.M
)
BODY = (
    r"^[0-9a-f]+ <[^>]*%s[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
)
MEMORY = re.compile(
    r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]"
)
FRAME = ("esp", "ebp")
DIRECT = re.compile(r"^(?:[0-9a-f]+ <|[0-9a-f]+$|\S+@plt)")
DEV_MODE_SLOT = 0x15
GATE_SLOT = -0x04
MEMORY_STREAM_SLOT = 0x04
FILE_STREAM_SLOT = 0x28
ACCESS_PORT_SLOT = 0x10
WRITE_PORT_SLOT = 0x38
ALLOWED_SLOTS = {0x0, GATE_SLOT, ACCESS_PORT_SLOT, FILE_STREAM_SLOT, WRITE_PORT_SLOT}


def body_of(path, name):
    selector = re.compile(BODY % re.escape(name), re.S | re.M).search(
        open(path, encoding="utf-8").read()
    )
    if selector is None:
        raise SystemExit(f"{path}: {name} symbol missing")
    return selector.group("body")


def instructions(body):
    return [
        (found.group("mnemonic"), found.group("operands").strip())
        for found in INSN.finditer(body)
    ]


def displacements(operands):
    found = set()
    for memory in MEMORY.finditer(operands):
        if memory.group("base") in FRAME:
            continue
        value = memory.group("disp")
        found.add(int(value, 16) if value else 0)
    return found


def slots(body):
    found = set()
    for _, operands in instructions(body):
        found |= displacements(operands)
    return found


def offsets(body):
    found = set(slots(body))
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("add", "lea", "sub", "cmp", "test"):
            continue
        for part in operands.split(","):
            token = part.strip()
            if re.fullmatch(r"0x[0-9a-f]+", token):
                found.add(int(token, 16))
    return found


def returns(body):
    found = set()
    for mnemonic, operands in instructions(body):
        if mnemonic != "ret":
            continue
        if not re.fullmatch(r"0x[0-9a-f]+", operands):
            raise SystemExit(f"{path}: return releases {operands or 'nothing'}")
        found.add(int(operands, 16))
    if not found:
        raise SystemExit(f"{path}: no return in body")
    return found


def writes(body, slot):
    for mnemonic, operands in instructions(body):
        parts = [part.strip() for part in operands.split(",")] if operands else []
        if len(parts) != 2 or mnemonic not in ("mov", "and", "or", "xor", "add"):
            continue
        if slot in displacements(parts[0]):
            return True
    return False


def dispatches(body):
    found = []
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("call", "jmp") or DIRECT.match(operands):
            continue
        if re.match(r"^(?:DWORD PTR )?(?:\[|[a-z])", operands):
            found.append(operands)
    return found


for path in sys.argv[1:]:
    dev_mode = body_of(path, "prop_manager_set_dev_mode_006a3300")
    if returns(dev_mode) != {0x04}:
        raise SystemExit(
            f"{path}: dev mode setter releases {sorted(returns(dev_mode))} instead of"
            " [0x4] stack words"
        )
    if slots(dev_mode) != {DEV_MODE_SLOT}:
        raise SystemExit(
            f"{path}: dev mode setter reaches {sorted(slots(dev_mode))} instead of"
            f" {{0x{DEV_MODE_SLOT:x}}}"
        )
    if not writes(dev_mode, DEV_MODE_SLOT):
        raise SystemExit(f"{path}: dev mode setter never writes +0x15")
    if dispatches(dev_mode):
        raise SystemExit(f"{path}: dev mode setter calls out")

    flush = body_of(path, "record_write_flush_006c0550")
    if returns(flush) != {0x08}:
        raise SystemExit(
            f"{path}: flush releases {sorted(returns(flush))} instead of [0x8] stack"
            " words"
        )
    if not slots(flush) <= ALLOWED_SLOTS:
        raise SystemExit(
            f"{path}: flush reaches unexpected slots"
            f" {sorted(slots(flush) - ALLOWED_SLOTS)}"
        )
    reached = offsets(flush)
    for required in (
        GATE_SLOT,
        MEMORY_STREAM_SLOT,
        FILE_STREAM_SLOT,
        ACCESS_PORT_SLOT,
        WRITE_PORT_SLOT,
    ):
        if required not in reached:
            raise SystemExit(f"{path}: flush never reaches {required:+#x}")
    indirect = dispatches(flush)
    if len(indirect) < 2:
        raise SystemExit(
            f"{path}: flush performs {len(indirect)} vtable dispatches instead of at"
            " least two"
        )
    compared = [
        operands
        for mnemonic, operands in instructions(flush)
        if mnemonic in ("cmp", "test") and re.search(r",\s*0x0(?:\D|$)", operands)
    ]
    if not compared:
        raise SystemExit(f"{path}: flush never compares the gate word against zero")
PY
