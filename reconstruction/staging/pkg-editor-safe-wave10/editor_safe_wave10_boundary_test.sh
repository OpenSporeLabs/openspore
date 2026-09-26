#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-editor-safe-wave10
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
    -I "$package_dir" "$package_dir/editor_safe_wave10.cpp" \
    "$package_dir/editor_safe_wave10_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done

python3 - $disassembly <<'PY'
import re
import sys

INSN = re.compile(
    r"^[ \t]*(?P<addr>[0-9a-f]+):[ \t]+(?P<mnemonic>\S+)[ \t]*"
    r"(?P<operands>[^\n]*)$",
    re.M,
)
BODY = (
    r"^[0-9a-f]+ <[^>]*%s[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
)
MEMORY = re.compile(
    r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]"
)
FRAME = ("esp", "ebp")
STORES = ("mov", "movss", "movl", "movd")
WRITE_ORDER = (0x80, 0x84, 0x88, 0x74, 0x78, 0x7C)
SLOTS = set(WRITE_ORDER)
DIRECT = re.compile(r"^(?:[0-9a-f]+ <|[0-9a-f]+$|\S+@plt)")


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


def receiver_displacements(operands):
    found = set()
    for memory in MEMORY.finditer(operands):
        if memory.group("base") in FRAME:
            continue
        value = memory.group("disp")
        found.add(int(value, 16) if value else 0)
    return found


def write_sequence(body):
    found = []
    for mnemonic, operands in instructions(body):
        if mnemonic not in STORES:
            continue
        parts = [part.strip() for part in operands.split(",")] if operands else []
        if len(parts) != 2:
            continue
        for memory in MEMORY.finditer(parts[0]):
            if memory.group("base") in FRAME:
                continue
            value = memory.group("disp")
            found.append(int(value, 16) if value else 0)
    return found


def returns(body, path):
    found = set()
    for mnemonic, operands in instructions(body):
        if mnemonic != "ret":
            continue
        if not re.fullmatch(r"0x[0-9a-f]+", operands):
            raise SystemExit(
                f"{path}: return releases {operands or 'nothing'} instead of four"
                " stack words"
            )
        found.add(int(operands, 16))
    if not found:
        raise SystemExit(f"{path}: no return in body")
    return found


def dispatches(body):
    found = []
    for mnemonic, operands in instructions(body):
        if mnemonic == "call":
            found.append(operands)
        elif mnemonic == "jmp" and not DIRECT.match(operands):
            found.append(operands)
    return found


def frameless(body):
    for mnemonic, operands in instructions(body):
        if mnemonic in ("push", "mov", "lea", "sub", "add") and "ebp" in operands:
            if mnemonic != "mov" or not operands.startswith("esp,"):
                return False
    return True


def gate_is_low_byte(body):
    masked = set()
    for mnemonic, operands in instructions(body):
        if mnemonic in ("and", "andb", "andl") and re.search(r",0xff$", operands):
            masked.add(operands.split(",")[0].strip())
        if mnemonic not in ("cmp", "test"):
            continue
        if re.search(
            r"^BYTE PTR \[[a-z0-9]+(?:\+0x[0-9a-f]+)?\],\s*0x0$", operands
        ):
            return True
        if re.search(r"^(?:DWORD|WORD|QWORD) PTR \[[^]]+\],\s*0x0$", operands):
            return False
        parts = [part.strip() for part in operands.split(",")]
        if parts[-1] == "0x0" and parts[0] in masked:
            return True
    return False


def gate_shape(body):
    for mnemonic, operands in instructions(body):
        if mnemonic != "cmp" or not operands.startswith("BYTE PTR"):
            continue
        memory = MEMORY.search(operands)
        if memory is None or not re.search(r",\s*0x0$", operands):
            continue
        value = memory.group("disp")
        return int(value, 16) if value else 0
    return None


for path in sys.argv[1:]:
    body = body_of(path, "editor_row_publish_005a2010")
    sequence = write_sequence(body)
    if tuple(sequence) != WRITE_ORDER:
        raise SystemExit(
            f"{path}: write sequence {[hex(value) for value in sequence]}"
            f" instead of {[hex(value) for value in WRITE_ORDER]}"
        )
    reached = set()
    for _, operands in instructions(body):
        reached |= receiver_displacements(operands)
    if reached != SLOTS:
        raise SystemExit(
            f"{path}: receiver reached {sorted(hex(value) for value in reached)}"
            f" instead of {sorted(hex(value) for value in SLOTS)}"
        )
    if returns(body, path) != {0x10}:
        raise SystemExit(
            f"{path}: released"
            f" {sorted(hex(value) for value in returns(body, path))} instead of"
            " [0x10]"
        )
    if dispatches(body):
        raise SystemExit(f"{path}: body dispatches {dispatches(body)}")
    if not gate_is_low_byte(body):
        raise SystemExit(f"{path}: no low-byte gate against zero")

    if frameless(body):
        shape = gate_shape(body)
        if shape != 0x10:
            raise SystemExit(
                f"{path}: frameless gate reads stack offset"
                f" {hex(shape) if shape is not None else 'none'} instead of +0x10"
            )
    print(f"{path}: order, slots, ret 0x10, leaf call-free, low-byte gate ok")
PY
