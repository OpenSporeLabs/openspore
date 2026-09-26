#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-app-wave11
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

if command -v clang-format >/dev/null 2>&1; then
  for source in app_wave11.hpp app_wave11.cpp app_wave11_model_test.cpp; do
    clang-format --dry-run -Werror "$package_dir/$source"
  done
  echo "format: clang-format clean over the header, the source and the model test"
else
  echo "format: clang-format unavailable, skipped" >&2
  exit 1
fi

for config in $binaries; do
  case "$config" in
    o0) flags="-O0" ;;
    o2) flags="-O2" ;;
    o0-ndebug) flags="-O0 -DNDEBUG" ;;
    o2-ndebug) flags="-O2 -DNDEBUG" ;;
  esac
  binary="$work_dir/$config"
  clang++ -m32 -std=c++17 $flags -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/app_wave11.cpp" \
    "$package_dir/app_wave11_model_test.cpp" -o "$binary"
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
BODY = r"^[0-9a-f]+ <[^>]*%s[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"

# Virtual address, expected stack words released by every return, expected
# return width, minimum number of indirect port dispatches the seam must keep.
TARGETS = {
    "property_record_assign_pair_004279d0": (0x004279d0, {0x04}, "dword", 1),
    "property_record_assign_scalar_00428060": (0x00428060, {0x04}, "dword", 1),
    "model_parts_apply_properties_00447150": (0x00447150, {0x04}, "none", 2),
    "pair_vector_insert_004786e0": (0x004786e0, {0x08}, "none", 0),
    "model_stage_serialize_004af260": (0x004af260, {0x04}, "byte", 1),
    "pair_vector_construct_004b62a0": (0x004b62a0, {0x04}, "dword", 1),
    "stream_probe_dispatch_004bc540": (0x004bc540, {0x10}, "byte", 1),
}
WIDTH_MOVES = {
    "byte": (r"\beax\b", r"\bax\b", r"\b[abcd]x\b"),
    "dword": (r"\bax\b",),
    "none": (),
}
INDIRECT = re.compile(r"^\s*[0-9a-f]+:\s+call\s+(?!.*<)", re.M | re.I)


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


def releases(body, path, name, expected):
    found = set()
    for mnemonic, operands in instructions(body):
        if mnemonic != "ret":
            continue
        found.add(int(operands, 16) if operands else 0)
    if found != expected:
        raise SystemExit(
            f"{path}: {name} releases "
            f"{sorted(hex(v) for v in found)} instead of "
            f"{sorted(hex(v) for v in expected)}"
        )


def return_width(body, path, name, width):
    forbidden = WIDTH_MOVES[width]
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("mov", "movl", "xor", "movzx", "setg", "sete",
                            "setnz", "setge", "seta"):
            continue
        parts = [part.strip() for part in operands.split(",")]
        if not parts or parts[0] not in forbidden:
            continue
        raise SystemExit(
            f"{path}: {name} writes {parts[0]} but the observed return width is"
            f" {width}"
        )


def indirect_seam(body, path, name, floor):
    got = len(INDIRECT.findall(body))
    if got < floor:
        raise SystemExit(
            f"{path}: {name} keeps {got} indirect port calls, needs {floor}"
        )


for path in sys.argv[1:]:
    for name, (_, release, width, floor) in TARGETS.items():
        body = body_of(path, name)
        releases(body, path, name, release)
        return_width(body, path, name, width)
        indirect_seam(body, path, name, floor)
    # 0x00447150 reaches the tree insert and then the argumentless node append,
    # so the insert must always be followed by an append.
    body = body_of(path, "model_parts_apply_properties_00447150")
    calls = [
        operands
        for mnemonic, operands in instructions(body)
        if mnemonic == "call"
    ]
    if len(calls) < 2:
        raise SystemExit(
            f"{path}: 00447150 no longer calls the insert and the append"
        )
    print(
        f"{path}: ret widths and stack cleanup match the target for 0x004279d0,"
        " 0x00428060, 0x00447150, 0x004786e0, 0x004af260, 0x004b62a0 and"
        " 0x004bc540"
    )
PY

echo "boundary: all four configurations built, ran and matched"
