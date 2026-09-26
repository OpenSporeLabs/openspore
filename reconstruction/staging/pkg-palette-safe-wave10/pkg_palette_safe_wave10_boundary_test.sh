#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-palette-safe-wave10
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/pkg_palette_safe_wave10.cpp $package_dir/pkg_palette_safe_wave10_model_test.cpp"
headers="$package_dir/pkg_palette_safe_wave10.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/pkg_palette_safe_wave10.cpp" \
  "$package_dir/pkg_palette_safe_wave10_model_test.cpp"
echo "format: clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/pkg_palette_safe_wave10.cpp" -o "$work/$tag.o"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.bin" >"$work/$tag.dis"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.o" >"$work/$tag.obj.dis"
  echo "build: $tag ok"
done

for tag in o0 o2 o0n o2n; do
  "$work/$tag.bin"
done

python3 - "$work" <<'PY'
import collections
import pathlib
import re
import sys

work = pathlib.Path(sys.argv[1])

BODY = re.compile(
    r"^[0-9a-f]+ <(?P<name>[^>]+)>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
    re.S | re.M,
)
STEP = re.compile(r"^\s*[0-9a-f]+:\s", re.M)
RET = re.compile(r"^\s*[0-9a-f]+:\s+ret\s*(?P<pops>0x[0-9a-f]+)?\s*$", re.M)
MEMORY = re.compile(r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]")
INDIRECT = re.compile(
    r"^\s*[0-9a-f]+:\s+(?:call|jmp)\s+(?![0-9a-f]+ <)(?P<operand>\S+)", re.M
)
LINE = re.compile(
    r"^\s*[0-9a-f]+:\s+(?P<mnemonic>\S+)(?P<rest>.*)$", re.M
)
PORT = re.compile(r"R_386_\S+\s+(?P<name>unresolved_\S+)")

SKIP_BASES = ("esp", "ebp", "ebx")
TOOLCHAIN = ("__stack_chk_fail",)

PAGE = "page_visible_slots_refresh_005c0a60"
PALETTE = "palette_row_layout_005c3000"

RETURNS = {PAGE: {"0x4"}, PALETTE: {""}}

SLOT_OFFSETS = {PAGE: {0x7C, 0x80}, PALETTE: {0x38, 0x6C}}

OFFSETS = {
    PAGE: {0x00, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x7C, 0x80, 0x88, 0x8C, 0xA0},
    PALETTE: {
        0x00, 0x04, 0x08, 0x0C, 0x10, 0x118, 0x1C, 0x20, 0x24, 0x28, 0x2C,
        0x38, 0x3C, 0x6C, 0x70, 0x74, 0x78,
    },
}

PORTS = {
    PAGE: {
        "unresolved_005c29c0",
        "unresolved_0041e050",
        "unresolved_00f47380",
    },
    PALETTE: {
        "unresolved_008105b0",
        "unresolved_005c2aa0",
    },
}

LITERALS = {
    PAGE: ("g_format_013f7c30",),
    PALETTE: ("0x5d3f56b", "g_row_gap_01486110", "g_table_015fd918"),
}
ENTRY = (PAGE, PALETTE)


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def returns(body, path, name):
    found = {m.group("pops") or "" for m in RET.finditer(body)}
    if not found:
        fail(f"{path}: {name} has no return")
    return found


def dispatches(body):
    return [m.group("operand") for m in INDIRECT.finditer(body)]


def field_offsets(body):
    found = set()
    for line in LINE.finditer(body):
        if line.group("mnemonic").startswith("lea"):
            continue
        for match in MEMORY.finditer(line.group("rest")):
            if match.group("base") in SKIP_BASES:
                continue
            value = match.group("disp")
            found.add(int(value, 16) if value else 0)
    return found


def ports(body):
    return {m.group("name") for m in PORT.finditer(body)} - set(TOOLCHAIN)


def show(values):
    return "{" + ", ".join(hex(value) for value in sorted(values)) + "}"


reference = None
sizes = {}
for tag in ("o0", "o2", "o0n", "o2n"):
    path = work / f"{tag}.obj.dis"
    table = bodies(path)
    for name in ENTRY:
        if name not in table:
            fail(f"{tag}: {name} is missing from the object file")
        body = table[name]
        found_returns = returns(body, path, name)
        if found_returns != RETURNS[name]:
            fail(
                f"{tag}: {name} returns {sorted(found_returns)}"
                f" instead of {sorted(RETURNS[name])}"
            )
        if not SLOT_OFFSETS[name] <= OFFSETS[name]:
            fail(f"{tag}: {name} does not pin its slot offsets")
        found_dispatch = dispatches(body)
        if not found_dispatch:
            fail(f"{tag}: {name} performs no indirect dispatch")
        found_offsets = field_offsets(body)
        if found_offsets != OFFSETS[name]:
            missing = sorted(OFFSETS[name] - found_offsets)
            extra = sorted(found_offsets - OFFSETS[name])
            fail(
                f"{tag}: {name} reads {show(found_offsets)};"
                f" missing {show(set(missing))}, unexpected {show(set(extra))}"
            )
        found_ports = ports(body)
        if found_ports != PORTS[name]:
            fail(
                f"{tag}: {name} crosses {sorted(found_ports)}"
                f" instead of {sorted(PORTS[name])}"
            )
        for literal in LITERALS[name]:
            if literal not in body:
                fail(f"{tag}: {name} does not reference {literal}")
    if PAGE in table and "sar" not in table[PAGE]:
        fail(f"{tag}: {PAGE} lost the arithmetic eight byte slot shift")
    whole = ports(path.read_text()) - set(TOOLCHAIN)
    if reference is None:
        reference = whole
    elif whole != reference:
        fail(f"{tag}: the port set diverges from o0: {sorted(whole ^ reference)}")
    sizes[tag] = {
        name: (len(STEP.findall(table[name])), len(dispatches(table[name])))
        for name in ENTRY
    }

for pair in (("o0", "o0n"), ("o2", "o2n")):
    left = (work / f"{pair[0]}.o").read_bytes()
    right = (work / f"{pair[1]}.o").read_bytes()
    if left != right:
        fail(f"{pair[0]} and {pair[1]} emit different object code")

for tag in ("o0", "o2"):
    table = bodies(work / f"{tag}.dis")
    for name in ENTRY:
        if name not in table:
            fail(f"{tag}: {name} is missing from the linked image")
        found_returns = returns(table[name], work / f"{tag}.dis", name)
        if found_returns != RETURNS[name]:
            fail(f"{tag}: the linked {name} releases the wrong width")

touched = collections.Counter()
for name in ENTRY:
    for port in PORTS[name]:
        touched[port] += 1

print(
    "boundary: 005c0a60 releases 0x4 and 005c3000 releases nothing"
    " in o0, o2, o0n and o2n"
)
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: the unresolved port set is identical at o0 and o2")
for name in ENTRY:
    print(
        f"boundary: {name} pins {show(SLOT_OFFSETS[name])} through indirect"
        f" dispatch, reads {len(OFFSETS[name])} field offsets,"
        f" crosses {len(PORTS[name])} ports,"
        f" {sizes['o0'][name][0]} instructions and {sizes['o0'][name][1]}"
        f" indirect dispatches at o0,"
        f" {sizes['o2'][name][0]} and {sizes['o2'][name][1]} at o2"
    )
for port, total in sorted(touched.items()):
    print(f"boundary:   {port} crossed by {total} of 2 entries")
PY

echo "boundary: pkg-palette-safe-wave10 validated"
