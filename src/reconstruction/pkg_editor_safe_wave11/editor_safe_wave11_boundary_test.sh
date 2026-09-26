#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-editor-safe-wave11
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

if command -v clang-format >/dev/null 2>&1; then
  for source in editor_safe_wave11.hpp editor_safe_wave11.cpp \
                editor_safe_wave11_model_test.cpp; do
    clang-format --dry-run -Werror \
      --style='{BasedOnStyle: Google, FixNamespaceComments: false}' \
      "$package_dir/$source"
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
    -I "$package_dir" "$package_dir/editor_safe_wave11.cpp" \
    "$package_dir/editor_safe_wave11_model_test.cpp" -o "$binary"
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

# Virtual address, expected stack words released by every return, and the
# expected return width. 0x004c5910, 0x004df550 and 0x004c73f0 are excluded
# from this tranche and are asserted absent below.
TARGETS = {
    "editor_paint_commit_0043ac40": (0x0043ac40, {0x0C}, "byte"),
    "editor_entry_expand_004ad6f0": (0x004ad6f0, {0x04}, "none"),
    "editor_bake_probe_004bf770": (0x004bf770, {0x00}, "byte"),
    "editor_bake_select_004c4a30": (0x004c4a30, {0x2C}, "byte"),
}
EXCLUDED = (
    "editor_pair_retain_004c5910",
    "editor_species_resolve_004df550",
    "unresolved_00f473a0",
    "unresolved_004da3a0",
    "unresolved_004df6d0",
    "unresolved_004e0560",
    "unresolved_004d3dd0",
    "atomic_bump",
    "OpaqueHandle",
    "OpaquePairRoot",
    "OpaqueSpeciesKey",
    "OpaqueLinkCell",
    "OpaqueLinkRoot",
)
# Ports the reconstruction is allowed to dispatch, and the ones it must never
# dispatch because the target keeps them inline.
PORTS = {
    0x00526430,
    0x004b1cc0,
    0x004aff80,
    0x0044ae00,
    0x0041dba0,
    0x00409930,
    0x00409dd0,
    0x004bf0a0,
    0x004ccae0,
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


def closure(path, name):
    """Every in-file body reachable from name through direct calls."""
    text = open(path, encoding="utf-8").read()
    bodies = {
        found.group("name"): found.group("body")
        for found in re.finditer(
            r"^[0-9a-f]+ <(?P<name>[^>]+)>:\n(?P<body>.*?)"
            r"(?=\n[0-9a-f]+ <|\Z)",
            text,
            re.S | re.M,
        )
    }
    seen = []
    pending = [name]
    while pending:
        current = pending.pop()
        if current in seen or current not in bodies:
            continue
        seen.append(current)
        for mnemonic, operands in instructions(bodies[current]):
            if mnemonic != "call":
                continue
            match = re.search(r"<([^>+]+)", operands)
            if match is None:
                continue
            target = match.group(1).strip()
            if target in bodies and target not in seen:
                pending.append(target)
    return [bodies[entry] for entry in seen]


def unresolved_name(operand):
    match = re.fullmatch(r"unresolved_([0-9a-f]{8})", operand)
    return None if match is None else int(match.group(1), 16)


for path in sys.argv[1:]:
    text = open(path, encoding="utf-8").read()
    for absent in EXCLUDED:
        if absent in text:
            raise SystemExit(
                f"{path}: unpromoted surface {absent} is still present"
            )
    for name, (va, release, width) in TARGETS.items():
        body = body_of(path, name)
        releases(body, path, name, release)
        return_width(body, path, name, width)
        for operand in dispatches(body):
            port = unresolved_name(operand)
            if port is not None and port not in PORTS:
                raise SystemExit(f"{path}: {name} dispatches unknown port {operand}")
        if not re.search(r"\bcall\b", body):
            raise SystemExit(f"{path}: {name} dispatches no port at all")
    body = body_of(path, "editor_paint_commit_0043ac40")
    if "call" not in body:
        raise SystemExit(f"{path}: 0043ac40 never dispatches its vtable slot")
    # 0x0043ac40 raises node bit three through an OR and clears it exactly
    # once, in the case zero neither-mark arm. The NOT and AND pair that the
    # Ghidra decompilation shows for case five is the dead arm behind the
    # MOV EAX,1 / TEST EAX,EAX / JZ sequence at 0x0043ba37..0x0043ba3e and
    # 0x0043bb0a..0x0043bb11, so a single clear against several raises is
    # what separates the live OR form from the dead one. The raise and the
    # clear live in the anonymous namespace helpers at -O0 and are folded into
    # the body at -O2, so the whole in-file call closure is counted; the clear
    # mask appears as 0xfffffff7 in a dword OR and as 0xf7 in a byte one.
    raises = 0
    clears = 0
    for chunk in closure(path, "editor_paint_commit_0043ac40"):
        raises += len(re.findall(r"\bor\s+[^,]+,0x8\b", chunk))
        clears += len(re.findall(r"\band\s+[^,]+,0x(?:f{7}|f)7\b", chunk))
    if raises < 2 or clears != 1:
        raise SystemExit(
            f"{path}: 0043ac40 emits {raises} bit three raises and {clears}"
            " clears; the live case five arm is the OR form and the case zero"
            " clear is the only AND"
        )
    print(
        f"{path}: ret widths and stack cleanup match the target for"
        " 0x0043ac40, 0x004ad6f0, 0x004bf770 and 0x004c4a30"
    )
PY

echo "boundary: all four configurations built, ran and matched"
echo "boundary: pkg-editor-safe-wave11 validated"
