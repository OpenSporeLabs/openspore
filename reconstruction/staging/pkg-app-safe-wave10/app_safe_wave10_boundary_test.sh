#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-app-safe-wave10
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/app_safe_wave10.cpp $package_dir/app_safe_wave10_model_test.cpp"
headers="$package_dir/app_safe_wave10.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/app_safe_wave10.cpp" \
  "$package_dir/app_safe_wave10_model_test.cpp"
echo "format: clean"

clang++ -m32 -std=c++17 -Wall -Wextra -Wpedantic -Werror -fsyntax-only \
  -I "$package_dir" $sources
echo "syntax: -m32 c++17 clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/app_safe_wave10.cpp" -o "$work/$tag.o"
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
RET = re.compile(r"^\s*[0-9a-f]+:\s+ret(?:\s+(?P<pops>0x[0-9a-f]+))?\s*$", re.M)
STEP = re.compile(r"^\s*[0-9a-f]+:\s", re.M)
RELOC = re.compile(r"R_386_(?:PC32|PLT32|32S)\s+(?P<name>\S+)")
INDIRECT = re.compile(r"^\s*[0-9a-f]+:\s+call\s+(?!.*<)", re.M | re.I)
UNSIGNED_GATE = re.compile(r"^\s*[0-9a-f]+:\s+j(?:ae|nb)\s", re.M | re.I)
SIGNED_GATE = re.compile(r"^\s*[0-9a-f]+:\s+j(?:l|ng|g|le)\s", re.M | re.I)
FADD = re.compile(r"^\s*[0-9a-f]+:\s+add(?:ss|ps|sd)\s", re.M | re.I)
X87 = re.compile(r"^\s*[0-9a-f]+:\s+f(?:ld|st|add|mul|sub|div|chs|abs|ild|com|"
                 r"ucomi|nst)\w*\s", re.M | re.I)
DEST_STORE = re.compile(
    r"^\s*[0-9a-f]+:\s+mov\w*\s+(?P<width>DWORD|QWORD|XMMWORD) PTR "
    r"\[(?P<mem>[^\]]+)\]",
    re.M | re.I,
)
LANES = {"dword": 1, "qword": 2, "xmmword": 4}

EXPECTED = {
    "vector3_add_0041dc10": "0x0",
    "cursor_buffer_emit_0041e8b0": "0x4",
    "property_value_resolve_0041e920": "0x0",
}

DIRECT = ("cursor_runtime", "property_sentinel_015d115d")

CLOSURE = "pkg_app_safe_wave10"

LANE_TARGET = 3

EXCLUSIONS = ("0040fe00", "005300d0")

PORTS_NAMED = ("copy_element_00511140", "grow_and_emit_00424010")

GATE_OWNER = "cursor_buffer_emit_0041e8b0"
INDIRECT_OWNER = "cursor_buffer_emit_0041e8b0"
INDIRECT_COUNT = 2


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def lines_of(body):
    return [line for line in body.splitlines() if re.match(r"^\s*[0-9a-f]+:\s", line)]


def last_ret(body):
    found = RET.findall(body)
    if not found:
        return None
    return found[-1] or "0x0"


def offset_of(body, pattern):
    for line in lines_of(body):
        if pattern.search(line):
            return line
    return None


def relocation_names(text):
    return {name for name in RELOC.findall(text) if "GOT" not in name}


reference = None
sizes = {}
helpers = {}
indirect_counts = {}
for tag in ("o0", "o2", "o0n", "o2n"):
    table = bodies(work / f"{tag}.obj.dis")
    for symbol, pops in EXPECTED.items():
        if symbol not in table:
            fail(f"{tag}: {symbol} missing from the object file")
        got = last_ret(table[symbol])
        if got != pops:
            fail(f"{tag}: {symbol} releases {got} instead of {pops}")
        widths = {found or "0x0" for found in RET.findall(table[symbol])}
        if widths != {pops}:
            fail(f"{tag}: {symbol} mixes ret widths {sorted(widths)}")
    linked = bodies(work / f"{tag}.dis")
    for symbol, pops in EXPECTED.items():
        if symbol not in linked:
            fail(f"{tag}: {symbol} missing from the linked image")
        if last_ret(linked[symbol]) != pops:
            fail(f"{tag}: linked {symbol} releases the wrong width")

    add_body = table["vector3_add_0041dc10"]
    if X87.search(add_body):
        fail(f"{tag}: 0041dc10 leaves the x87 stack in play")
    add_lines = [line for line in lines_of(add_body) if FADD.search(line)]
    store_lines = [
        line
        for line in lines_of(add_body)
        if DEST_STORE.search(line)
        and not DEST_STORE.search(line).group("mem").startswith("ebp")
    ]
    if not add_lines:
        fail(f"{tag}: 0041dc10 has no packed or scalar float add")
    if not store_lines:
        fail(f"{tag}: 0041dc10 never stores to the destination")
    lanes = sum(LANES[DEST_STORE.search(line).group("width").lower()]
                for line in store_lines)
    if lanes != LANE_TARGET:
        fail(f"{tag}: 0041dc10 stores {lanes} lanes instead of {LANE_TARGET}")
    if add_lines[-1] > store_lines[0]:
        fail(f"{tag}: 0041dc10 stores before the last float add")

    gate_body = table[GATE_OWNER]
    if not UNSIGNED_GATE.search(gate_body):
        fail(f"{tag}: {GATE_OWNER} has no unsigned above-or-equal branch")
    if SIGNED_GATE.search(gate_body):
        fail(f"{tag}: {GATE_OWNER} gates on a signed comparison")
    if "0x18" not in gate_body:
        fail(f"{tag}: {GATE_OWNER} does not advance by the 0x18 stride")

    port_body = table[INDIRECT_OWNER]
    indirect_counts[tag] = len(INDIRECT.findall(port_body))
    if indirect_counts[tag] != INDIRECT_COUNT:
        fail(
            f"{tag}: {INDIRECT_OWNER} crosses {indirect_counts[tag]} ports"
            f" instead of {INDIRECT_COUNT}"
        )

    kind_read = offset_of(table["property_value_resolve_0041e920"],
                          re.compile(r"WORD PTR \[e?[abcd]x\+0x12\]", re.I))
    if kind_read is None:
        fail(f"{tag}: 0041e920 does not read the kind at +0x12 as a word")
    if "0x30" not in table["property_value_resolve_0041e920"]:
        fail(f"{tag}: 0041e920 drops the 0x30 storage mask")

    text = (work / f"{tag}.obj.dis").read_text()
    whole = relocation_names(text)
    foreign = sorted(name for name in whole if CLOSURE not in name)
    if foreign:
        fail(f"{tag}: direct calls leave the package: {foreign}")
    helpers[tag] = sorted(
        wanted for wanted in DIRECT if any(wanted in name for name in whole)
    )
    for excluded in EXCLUSIONS:
        if excluded in text:
            fail(f"{tag}: excluded address {excluded} leaked into the object")
    for named in PORTS_NAMED:
        if named not in text:
            fail(f"{tag}: the va-suffixed port {named} is missing")
    if reference is None:
        reference = whole
    else:
        grew = whole - reference
        if grew:
            fail(f"{tag}: optimization introduced direct calls {sorted(grew)}")
    sizes[tag] = {name: len(STEP.findall(table[name])) for name in EXPECTED}

for pair in (("o0", "o0n"), ("o2", "o2n")):
    left = (work / f"{pair[0]}.o").read_bytes()
    right = (work / f"{pair[1]}.o").read_bytes()
    if left != right:
        fail(f"{pair[0]} and {pair[1]} emit different object code")

touched = collections.Counter()
for tag in ("o0", "o2", "o0n", "o2n"):
    table = bodies(work / f"{tag}.obj.dis")
    for symbol in EXPECTED:
        for name in relocation_names(table[symbol]):
            for helper in DIRECT:
                if helper in name:
                    touched[helper] += 1

print("boundary: 0041dc10 releases 0x0, 0041e8b0 releases 0x4, 0041e920 releases 0x0")
print("boundary: ret widths hold in o0, o2, o0n and o2n")
print(f"boundary: 0041dc10 keeps every float add ahead of {LANE_TARGET} destination lanes")
print("boundary: 0041dc10 never touches the x87 stack")
print("boundary: 0041e8b0 gates on an unsigned compare and the 0x18 stride")
print(f"boundary: 0041e8b0 crosses {INDIRECT_COUNT} ports in every configuration")
print("boundary: 0041e920 reads the kind word and keeps the 0x30 mask")
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: every direct call stays inside the package closure")
for tag in ("o0", "o2", "o0n", "o2n"):
    print(f"boundary:   {tag} keeps the helpers {helpers[tag] or ['none, inlined']}")
print("boundary: 0x0040fe00 and 0x005300d0 stay out of the object")
print("boundary: both va-suffixed callee ports are named and called indirectly")
for symbol in EXPECTED:
    print(
        f"boundary: {symbol} has {sizes['o0'][symbol]} instructions at o0"
        f" and {sizes['o2'][symbol]} at o2"
    )
for name, total in sorted(touched.items()):
    print(f"boundary:   {name} is called from {total} target bodies")
PY

echo "boundary: pkg-app-safe-wave10 validated"
