#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-palette-support-wave10
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/pkg_palette_support_wave10.cpp $package_dir/pkg_palette_support_wave10_model_test.cpp"
headers="$package_dir/pkg_palette_support_wave10.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/pkg_palette_support_wave10.cpp" \
  "$package_dir/pkg_palette_support_wave10_model_test.cpp"
echo "format: clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/pkg_palette_support_wave10.cpp" -o "$work/$tag.o"
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
RET = re.compile(r"^\s*[0-9a-f]+:\s+ret\s+(?P<pops>0x[0-9a-f]+)?\s*$", re.M)
STEP = re.compile(r"^\s*[0-9a-f]+:\s", re.M)
PORT = re.compile(r"R_386_(?:PC32|PLT32|32S)\s+(?P<name>unresolved_\S+)")
INDIRECT = re.compile(r"^\s*[0-9a-f]+:\s+(?:call|jmp)\s+(?:DWORD PTR|e?[abcd]x|)")

TOOLCHAIN = {
    "__stack_chk_fail",
    "memset",
    "memcpy",
    "___stack_chk_fail_local",
}

EXPECTED = {
    "unresolved_005c5cc0": "0x8",
    "unresolved_005c6010": "0x4",
    "unresolved_005c6340": "0x1c",
}

PORTS = {
    "unresolved_005c5cc0": {
        "unresolved_005c7f00",
        "unresolved_005c1ce0",
        "unresolved_005c6810",
    },
    "unresolved_005c6010": {
        "unresolved_0067de30",
        "unresolved_006a0ae0",
        "unresolved_006a1250",
        "unresolved_00f473a0",
        "unresolved_005c7f50",
        "unresolved_005c8ad0",
        "unresolved_005c5df0",
        "unresolved_005c5f00",
        "unresolved_005c1e20",
        "unresolved_005c2020",
        "unresolved_005c1d40",
        "unresolved_005c22b0",
        "unresolved_005c5cc0",
        "unresolved_005c5c50",
        "unresolved_005c2390",
    },
    "unresolved_005c6340": {
        "unresolved_0067de30",
        "unresolved_006a12e0",
        "unresolved_006a12a0",
        "unresolved_0041e990",
        "unresolved_008de1a0",
        "unresolved_00f47380",
        "unresolved_005c6010",
    },
}


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def last_ret(body):
    found = RET.findall(body)
    if not found:
        return None
    return found[-1] or "0x0"


def port_set(text):
    return {name for name in PORT.findall(text) if name not in TOOLCHAIN}


def virtual_count(body):
    return len(INDIRECT.findall(body))


reference = None
sizes = {}
for tag in ("o0", "o2", "o0n", "o2n"):
    text = (work / f"{tag}.obj.dis").read_text()
    table = bodies(work / f"{tag}.obj.dis")
    for symbol, pops in EXPECTED.items():
        if symbol not in table:
            fail(f"{tag}: {symbol} missing from the object file")
        got = last_ret(table[symbol])
        if got != pops:
            fail(f"{tag}: {symbol} releases {got} instead of {pops}")
    whole = port_set(text)
    for symbol, wanted in PORTS.items():
        missing = wanted - whole
        if missing:
            fail(f"{tag}: {symbol} lost the ports {sorted(missing)}")
    if reference is None:
        reference = whole
    elif whole != reference:
        fail(
            f"{tag}: the port set diverges from o0: "
            f"{sorted(whole ^ reference)}"
        )
    sizes[tag] = {
        name: len(STEP.findall(table[name])) for name in EXPECTED
    }

for pair in (("o0", "o0n"), ("o2", "o2n")):
    left = (work / f"{pair[0]}.o").read_bytes()
    right = (work / f"{pair[1]}.o").read_bytes()
    if left != right:
        fail(f"{pair[0]} and {pair[1]} emit different object code")

for tag in ("o0", "o2"):
    table = bodies(work / f"{tag}.dis")
    for symbol, pops in EXPECTED.items():
        if symbol not in table:
            fail(f"{tag}: {symbol} missing from the linked image")
        if last_ret(table[symbol]) != pops:
            fail(f"{tag}: linked {symbol} releases the wrong width")

touched = collections.Counter()
for symbol, wanted in PORTS.items():
    for name in wanted:
        touched[name] += 1

print("boundary: ret widths 0x8 / 0x4 / 0x1c hold in o0, o2, o0n and o2n")
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: the unresolved port set is identical at o0 and o2")
for symbol in EXPECTED:
    print(
        f"boundary: {symbol} releases {EXPECTED[symbol]},"
        f" reaches {len(PORTS[symbol])} ports,"
        f" {sizes['o0'][symbol]} instructions at o0"
        f" and {sizes['o2'][symbol]} at o2"
    )
for name, total in sorted(touched.items()):
    print(f"boundary:   {name} crossed by {total} of 3 entries")
PY

echo "boundary: pkg-palette-support-wave10 validated"
