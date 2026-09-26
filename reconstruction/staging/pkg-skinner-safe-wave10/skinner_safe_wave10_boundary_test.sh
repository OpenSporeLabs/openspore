#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-skinner-safe-wave10
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/skinner_safe_wave10.cpp $package_dir/skinner_safe_wave10_model_test.cpp"
header="$package_dir/skinner_safe_wave10.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

for tool in clang++ clang-format objdump python3; do
  command -v "$tool" >/dev/null 2>&1 || {
    echo "missing required tool: $tool" >&2
    exit 127
  }
done

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$header" \
  "$package_dir/skinner_safe_wave10.cpp" \
  "$package_dir/skinner_safe_wave10_model_test.cpp"
echo "format: clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/skinner_safe_wave10.cpp" -o "$work/$tag.o"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.bin" >"$work/$tag.dis"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.o" >"$work/$tag.obj.dis"
  echo "build: $tag ok"
done

for tag in o0 o2 o0n o2n; do
  "$work/$tag.bin"
done

python3 - "$work" <<'PY'
import pathlib
import re
import sys

work = pathlib.Path(sys.argv[1])

BODY = re.compile(
    r"^[0-9a-f]+ <(?P<name>[^>]+)>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
    re.S | re.M,
)
RET = re.compile(r"^\s*[0-9a-f]+:\s+ret(?:\s+(?P<pops>0x[0-9a-f]+))?\s*$", re.M)
STEP = re.compile(r"^\s*[0-9a-f]+:\s", re.M)
INDIRECT = re.compile(
    r"(?i)^\s*[0-9a-f]+:\s+call\s+(?:DWORD PTR\s+\[[^\]]+\]|[a-z]+)\s*$",
    re.M,
)
PORT = re.compile(r"R_386_(?:PC32|PLT32|32S)\s+(?P<name>unresolved_\S+)")
DISP = re.compile(
    r"(?i)^\s*[0-9a-f]+:\s+(?:mov\s+eax,\s*DWORD PTR \[[a-z]+\+0x44\]"
    r"|call\s+DWORD PTR \[[a-z]+\+0x44\])",
    re.M,
)
SSESTORE = re.compile(
    r"(?i)^\s*[0-9a-f]+:\s+movss\s+DWORD PTR \[[a-z]+\+(?P<off>0x[0-9a-f]+)\],xmm\d",
    re.M,
)
FLOATRELOC = re.compile(r"R_386_GOTOFF\s+\S*g_float_(?P<word>[0-9a-f]+)E")

TOOLCHAIN = {
    "__stack_chk_fail",
    "memset",
    "memcpy",
    "___stack_chk_fail_local",
}

SETUP = "skin_painter_state_setup_00506590"
BRUSH = "skin_painter_job_brush_pass_005182f0"

EXPECTED_RET = {
    SETUP: "0x4",
    BRUSH: "0x0",
}

PORT_EXACT = {
    "unresolved_0067dd00": 1,
}

PORT_MIN = {
    "unresolved_00f473a0": 1,
    "unresolved_005288f0": 1,
    "unresolved_0067dd00": 1,
    "unresolved_00517430": 1,
}

OPTIMIZED_PORTS = {
    SETUP: {"unresolved_00f473a0", "unresolved_005288f0"},
    BRUSH: {"unresolved_0067dd00", "unresolved_00517430"},
}

FLOAT_FIELD_OFFSETS = ["0x20", "0x24", "0x28", "0x2c", "0x30"]

FLOAT_READ_ORDER = [
    "01471064",
    "01485720",
    "013eecd8",
    "01485720",
    "01485720",
]


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def last_ret(body):
    found = RET.findall(body)
    if not found:
        return None
    return found[-1] or "0x0"


def instruction_count(body):
    return len(STEP.findall(body))


def indirect_calls(body):
    return len(INDIRECT.findall(body))


reference = None
sizes = {}
for tag in ("o0", "o2", "o0n", "o2n"):
    table = bodies(work / f"{tag}.obj.dis")
    for symbol, pops in EXPECTED_RET.items():
        if symbol not in table:
            fail(f"{tag}: {symbol} missing from the object file")
        got = last_ret(table[symbol])
        if got != pops:
            fail(f"{tag}: {symbol} releases {got} instead of {pops}")
    whole = {}
    text = (work / f"{tag}.obj.dis").read_text()
    for name in PORT.findall(text):
        if name not in TOOLCHAIN:
            whole[name] = whole.get(name, 0) + 1
    for name, low in PORT_MIN.items():
        if whole.get(name, 0) < low:
            fail(f"{tag}: the object file no longer reaches {name}")
    for name, exact in PORT_EXACT.items():
        if whole.get(name, 0) != exact:
            fail(f"{tag}: {name} has {whole.get(name, 0)} call sites, want {exact}")
    if tag in ("o2", "o2n"):
        for symbol, wanted in OPTIMIZED_PORTS.items():
            reached = set(PORT.findall(table[symbol]))
            if reached != wanted:
                fail(f"{tag}: {symbol} reaches {sorted(reached)}, want {sorted(wanted)}")
    setup_body = table[SETUP]
    stores = [m.group("off") for m in SSESTORE.finditer(setup_body)]
    if stores != FLOAT_FIELD_OFFSETS:
        fail(f"{tag}: {SETUP} writes the float fields {stores}")
    reads = [m.group("word") for m in FLOATRELOC.finditer(setup_body)]
    if sorted(set(reads)) != sorted(set(FLOAT_READ_ORDER)):
        fail(f"{tag}: {SETUP} reads the globals {sorted(set(reads))}")
    if tag in ("o0", "o0n") and reads != FLOAT_READ_ORDER:
        fail(f"{tag}: {SETUP} reads the globals in the order {reads}")
    brush_body = table[BRUSH]
    if indirect_calls(brush_body) < 1:
        fail(f"{tag}: {BRUSH} has no indirect call, the vtable port is gone")
    if not DISP.search(brush_body):
        fail(f"{tag}: {BRUSH} no longer loads the 0x44 vtable slot")
    if reference is None:
        reference = set(whole)
    elif set(whole) != reference:
        fail(f"{tag}: the port set diverges from o0: {sorted(set(whole) ^ reference)}")
    sizes[tag] = {
        name: instruction_count(table[name]) for name in EXPECTED_RET
    }

for pair in (("o0", "o0n"), ("o2", "o2n")):
    left = (work / f"{pair[0]}.o").read_bytes()
    right = (work / f"{pair[1]}.o").read_bytes()
    if left != right:
        fail(f"{pair[0]} and {pair[1]} emit different object code")

for tag in ("o0", "o2"):
    table = bodies(work / f"{tag}.dis")
    for symbol, pops in EXPECTED_RET.items():
        if symbol not in table:
            fail(f"{tag}: {symbol} missing from the linked image")
        if last_ret(table[symbol]) != pops:
            fail(f"{tag}: linked {symbol} releases the wrong width")

print("boundary: ret widths 0x4 and 0x0 hold in o0, o2, o0n and o2n")
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: the unresolved port set is identical in o0, o2, o0n and o2n")
print("boundary: the five float stores land at 0x20 0x24 0x28 0x2c 0x30 in order")
print("boundary: the float sources are the globals 0x01471064 0x01485720 0x013eecd8")
print("boundary: the vtable slot 0x44 indirect call survives every build")
for symbol in EXPECTED_RET:
    print(
        f"boundary: {symbol} releases {EXPECTED_RET[symbol]},"
        f" {sizes['o0'][symbol]} instructions at o0"
        f" and {sizes['o2'][symbol]} at o2"
    )
for name in sorted(PORT_MIN):
    print(f"boundary:   {name} is still an unresolved port")
PY

echo "boundary: pkg-skinner-safe-wave10 validated"
