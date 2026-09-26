#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-editor-wave11
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

if command -v clang-format >/dev/null 2>&1; then
  for source in editor_wave11.hpp editor_wave11.cpp \
                editor_wave11_model_test.cpp; do
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
    -I "$package_dir" "$package_dir/editor_wave11.cpp" \
    "$package_dir/editor_wave11_model_test.cpp" -o "$binary"
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
# return width, expected 32-bit return register usage.
TARGETS = {
    "editor_paint_commit_0043ac40": (0x0043ac40, {0x0C}, "byte"),
    "editor_entry_expand_004ad6f0": (0x004ad6f0, {0x04}, "none"),
    "editor_bake_probe_004bf770": (0x004bf770, {0x00}, "byte"),
    "editor_bake_select_004c4a30": (0x004c4a30, {0x2C}, "byte"),
    "editor_pair_retain_004c5910": (0x004c5910, {0x08}, "none"),
    "editor_species_resolve_004df550": (0x004df550, {0x04}, "dword"),
}
ALIASES = {
    0x0043ac40: ["editor_paint_commit_0043ac40"],
    0x004ad6f0: ["editor_entry_expand_004ad6f0"],
    0x004bf770: ["editor_bake_probe_004bf770"],
    0x004c4a30: ["editor_bake_select_004c4a30"],
    0x004c5910: ["editor_pair_retain_004c5910"],
    0x004df550: ["editor_species_resolve_004df550"],
}
# Ports the reconstruction is allowed to dispatch, and the ones it must never
# dispatch because the target keeps them inline.
PORTS = {
    0x00f473a0,
    0x00526430,
    0x004b1cc0,
    0x004aff80,
    0x0044ae00,
    0x0041dba0,
    0x00409930,
    0x00409dd0,
    0x004bf0a0,
    0x004ccae0,
    0x004da3a0,
    0x004df6d0,
    0x004e0560,
    0x004d3dd0,
}
WIDTH_MOVES = {
    "byte": (r"\bal\b", r"\beax\b", r"\bax\b", r"\b[abcd]x\b"),
    "dword": (r"\beax\b",),
    "none": (),
}


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
        value = 0 if not operands else int(operands, 16)
        found.add(value)
    if found != expected:
        raise SystemExit(
            f"{path}: {name} releases "
            f"{sorted(hex(v) for v in found)} instead of "
            f"{sorted(hex(v) for v in expected)}"
        )


def return_width(body, path, name, width):
    forbidden = WIDTH_MOVES[width]
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("mov", "movl", "xor", "movzx", "setg", "seta"):
            continue
        parts = [part.strip() for part in operands.split(",")]
        if not parts or parts[0] not in forbidden:
            continue
        raise SystemExit(
            f"{path}: {name} writes {parts[0]} but the observed return width is"
            f" {width}"
        )


def dispatches(body):
    found = set()
    for mnemonic, operands in instructions(body):
        if mnemonic == "call":
            found.add(operands.strip())
    return found


def unresolved_name(operand):
    match = re.fullmatch(r"unresolved_([0-9a-f]{8})", operand)
    return None if match is None else int(match.group(1), 16)


for path in sys.argv[1:]:
    text = open(path, encoding="utf-8").read()
    for name, (va, release, width) in TARGETS.items():
        body = body_of(path, name)
        releases(body, path, name, release)
        return_width(body, path, name, width)
        for operand in dispatches(body):
            port = unresolved_name(operand)
            if port is not None and port not in PORTS:
                raise SystemExit(f"{path}: {name} dispatches unknown port {operand}")
        if not re.search(r"\bcall\b", body) and name != "editor_pair_retain_004c5910":
            raise SystemExit(f"{path}: {name} dispatches no port at all")
    if "editor_pair_retain_004c5910" in text:
        body = body_of(path, "editor_pair_retain_004c5910")
        reachable = [body]
        for mnemonic, operands in instructions(body):
            if mnemonic != "call":
                continue
            match = re.search(r"<([^>+]+)", operands)
            if match is None:
                continue
            selector = re.compile(
                BODY % re.escape(match.group(1).strip()), re.S | re.M
            ).search(text)
            if selector is not None:
                reachable.append(selector.group("body"))
        if not any(re.search(r"lock (?:inc|xadd)", chunk) for chunk in reachable):
            raise SystemExit(
                f"{path}: 004c5910 lost the inline atomic reference bump"
            )
    if "editor_paint_commit_0043ac40" in text:
        body = body_of(path, "editor_paint_commit_0043ac40")
        if "call" not in body:
            raise SystemExit(f"{path}: 0043ac40 never dispatches its vtable slot")
    print(
        f"{path}: ret widths and stack cleanup match the target for"
        " 0x0043ac40, 0x004ad6f0, 0x004bf770, 0x004c4a30, 0x004c5910,"
        " 0x004df550"
    )
PY

echo "boundary: all four configurations built, ran and matched"
