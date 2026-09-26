#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-utfwin-wave11
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

if command -v clang-format >/dev/null 2>&1; then
  for source in utfwin_wave11.hpp utfwin_wave11.cpp \
                utfwin_wave11_model_test.cpp; do
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
    -I "$package_dir" "$package_dir/utfwin_wave11.cpp" \
    "$package_dir/utfwin_wave11_model_test.cpp" -o "$binary"
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
# return width, and the set of unresolved contracts the body must still reach.
TARGETS = {
    "pkg_utfwin_wave11_005ac9f0": (0x005ac9f0, {0x00}, "dword", 1),
    "pkg_utfwin_wave11_005c00e0": (0x005c00e0, {0x04}, "dword", 2),
}
WIDTH_MOVES = {
    "byte": (r"\beax\b", r"\bax\b", r"\b[abcd]x\b"),
    "dword": (r"\bax\b",),
    "none": (),
}
CONTRACTS = (
    "pkg_utfwin_wave11_re_005b0f80",
    "pkg_utfwin_wave11_re_005c0070",
    "pkg_utfwin_wave11_re_00f47380",
)


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
        if mnemonic not in ("mov", "movl", "xor", "movzx"):
            continue
        parts = [part.strip() for part in operands.split(",")]
        if not parts or parts[0] not in forbidden:
            continue
        raise SystemExit(
            f"{path}: {name} writes {parts[0]} but the observed return width is"
            f" {width}"
        )


def contract_seam(body, path, name, floor):
    reached = [operands for mnemonic, operands in instructions(body)
               if mnemonic == "call"]
    got = sum(1 for operands in reached
              if any(contract in operands for contract in CONTRACTS))
    if got < floor:
        raise SystemExit(
            f"{path}: {name} reaches {got} unresolved contracts, needs {floor}"
        )


for path in sys.argv[1:]:
    for name, (_, release, width, floor) in TARGETS.items():
        body = body_of(path, name)
        releases(body, path, name, release)
        return_width(body, path, name, width)
        contract_seam(body, path, name, floor)
    first = body_of(path, "pkg_utfwin_wave11_005ac9f0")
    if "pkg_utfwin_wave11_re_005b0f80" not in first:
        raise SystemExit(f"{path}: 005ac9f0 lost its base constructor call")
    second = body_of(path, "pkg_utfwin_wave11_005c00e0")
    if "pkg_utfwin_wave11_re_00f47380" not in second:
        raise SystemExit(f"{path}: 005c00e0 lost its conditional release call")
    if not re.search(r"\b(and|test)\w*\b", second):
        raise SystemExit(f"{path}: 005c00e0 lost the flag test")
    print(
        f"{path}: ret widths and stack cleanup match the target for 0x005ac9f0"
        " and 0x005c00e0"
    )
PY

echo "boundary: all four configurations built, ran and matched"
