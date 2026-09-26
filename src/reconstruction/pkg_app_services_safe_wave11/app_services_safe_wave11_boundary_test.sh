#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-app-services-wave11
style='{BasedOnStyle: Google, FixNamespaceComments: false}'
sources="$package_dir/app_services_safe_wave11.cpp $package_dir/app_services_safe_wave11_model_test.cpp"
headers="$package_dir/app_services_safe_wave11.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/app_services_safe_wave11.cpp" \
  "$package_dir/app_services_safe_wave11_model_test.cpp"
echo "format: clean"

clang++ -m32 -std=c++17 $warnings -fsyntax-only -I "$package_dir" $sources
echo "syntax: -m32 c++17 clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/app_services_safe_wave11.cpp" -o "$work/$tag.o"
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
DIRECT = re.compile(r"^\s*[0-9a-f]+:\s+call\s+.*<(?P<name>[^>]+)>", re.M)
TAILJUMP = re.compile(r"^\s*[0-9a-f]+:\s+jmp\s+\*", re.M)
PUSH = re.compile(r"^\s*[0-9a-f]+:\s+push\s+(?P<reg>%e[a-z]{2})\s*$", re.M)
KEYSTORE = re.compile(
    r"^\s*[0-9a-f]+:\s+mov\s+DWORD PTR \[[^]]*0x(?:f8|fc|100)\]", re.M
)
ADDOFF = re.compile(r"add\s+\$(?P<off>0x[0-9a-f]+),")
SAR = re.compile(r"^\s*[0-9a-f]+:\s+sar\s+%?e[a-z]{2},1\b", re.M)
KEYCLEAR = re.compile(r"mov\s+DWORD PTR \[[^]]+\],0xffffffff", re.M)
RORWORD = re.compile(r"^\s*[0-9a-f]+:\s+ror\s+\$(?P<rot>0x[0-9a-f]+),%?eax", re.M)
SETZ = re.compile(r"^\s*[0-9a-f]+:\s+sete?\s+%?al", re.M)
XOREAX = re.compile(r"^\s*[0-9a-f]+:\s+xor\s+%?eax,%?eax", re.M)
ANDCX = re.compile(r"^\s*[0-9a-f]+:\s+and\s+%?eax,0x[0-9a-f]+", re.M)

EXPECTED = {
    "service_005f9230": "0x8",
    "service_005f9310": "0xc",
    "service_005fa8d0": "0x14",
    "service_005fc330": "0x8",
    "service_0060ee90": "0xc",
}

FIELDS = {
    "service_005fa8d0": ("0x88", "0xf8", "0xfc", "0x100", "0x4", "0x24",
                         "0x48", "0x68"),
    "service_005fc330": ("0x44", "0x48", "0x68", "0xf8", "0xfc", "0x100"),
    "service_0060ee90": ("0x8", "0x10", "0x14", "0x58", "0x60", "0x64"),
}

DISPATCH = "0x366a930d"
INTERNAL = re.compile(r"^service_[0-9a-f]+\+0x")
CLOSURE = "pkg_app_services_safe_wave11"
ALLOWED = re.compile(
    r"^(?:__stack_chk_fail|memset|memcpy|memmove|wcslen)$"
)
LANES = 3


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def lines_of(body):
    return [line for line in body.splitlines() if STEP.match(line)]


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
indirect_counts = {}
rotated = set()
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
        if TAILJUMP.search(table[symbol]):
            fail(f"{tag}: {symbol} ends in a tail jump")
    linked = bodies(work / f"{tag}.dis")
    for symbol, pops in EXPECTED.items():
        if symbol not in linked:
            fail(f"{tag}: {symbol} missing from the linked image")
        if last_ret(linked[symbol]) != pops:
            fail(f"{tag}: linked {symbol} releases the wrong width")

    for symbol, offsets in FIELDS.items():
        body = table[symbol]
        for off in offsets:
            if not re.search(r"[+,\[]" + off + r"\b", body):
                fail(f"{tag}: {symbol} never touches field {off}")
        if "0xf8" in offsets:
            stored = [
                line
                for line in lines_of(body)
                if KEYSTORE.search(line)
            ]
            if len(stored) < 3:
                fail(f"{tag}: {symbol} stores fewer than three key words")

    fold = table["service_005f9230"]
    if len(SETZ.findall(fold)) and not offset_of(fold, RORWORD):
        fail("005f9230 normalises the dispatch key without a rotate")
    if "0x366a930d" not in fold and "0x1b99" not in fold:
        fail(f"{tag}: 005f9230 lost the scenarios dispatch constant")
    wide = table["service_005f9310"]
    if "0xffffffff" not in wide or "0x19f76d11" not in wide:
        fail(f"{tag}: 005f9310 lost the table default compare")
    if "0xff0f" not in wide or not re.search(r",0x2f\b", wide):
        fail(f"{tag}: 005f9310 lost the terminator or separator compare")
    for rot in RORWORD.findall(table["service_005f9230"]):
        rotated.add(rot)

    tag_indirect = {}
    for symbol in EXPECTED:
        tag_indirect[symbol] = len(INDIRECT.findall(table[symbol]))
        if tag_indirect[symbol] == 0:
            fail(f"{tag}: {symbol} makes no indirect port call")
    indirect_counts[tag] = tag_indirect

    if ANDCX.search(table["service_0060ee90"]):
        fail(f"{tag}: 0060ee90 keeps the pair test inlined as a single compare")
    if not SAR.search(wide):
        fail(f"{tag}: 005f9310 drops the byte length shift")
    cleared = [
        line
        for line in lines_of(table["service_005fc330"])
        if KEYCLEAR.search(line)
    ]
    if len(cleared) < 3:
        fail(f"{tag}: 005fc330 clears fewer than three key words")

    text = (work / f"{tag}.obj.dis").read_text()
    whole = relocation_names(text)
    foreign = sorted(
        name
        for name in whole
        if CLOSURE not in name and not ALLOWED.search(name)
    )
    if foreign:
        fail(f"{tag}: direct calls leave the package: {foreign}")
    package_calls = {name for name in whole if CLOSURE in name}
    if reference is None:
        reference = package_calls
    elif package_calls != reference:
        fail(
            f"{tag}: package call set drifted"
            f" +{sorted(package_calls - reference)}"
            f" -{sorted(reference - package_calls)}"
        )
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
        for line in DIRECT.findall(table[symbol]):
            if not INTERNAL.search(line):
                touched[line] += 1

print("boundary: 005f9230 releases 0x8, 005f9310 releases 0xc, "
      "005fa8d0 releases 0x14")
print("boundary: 005fc330 releases 0x8 and 0060ee90 releases 0xc")
print("boundary: ret widths hold in o0, o2, o0n and o2n")
print("boundary: every target ends in its own ret, never a tail jump")
print("boundary: field offsets 0x88, 0xf8, 0xfc, 0x100 survive every pass")
print("boundary: 0060ee90 keeps the 0x08/0x10/0x14/0x58/0x60/0x64 slots")
print("boundary: 005f9230 keeps the scenarios dispatch constant")
print("boundary: 005f9310 keeps the 0xffffffff table default compare")
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: every direct call stays inside the package closure")
for tag in ("o0", "o2", "o0n", "o2n"):
    parts = ", ".join(
        f"{name}={indirect_counts[tag][name]}"
        for name in sorted(EXPECTED)
    )
    print(f"boundary:   {tag} indirect port calls: {parts}")
for name, total in sorted(touched.items()):
    print(f"boundary:   {name} is called from {total} target bodies")
for symbol in EXPECTED:
    print(
        f"boundary: {symbol} has {sizes['o0'][symbol]} instructions at o0"
        f" and {sizes['o2'][symbol]} at o2"
    )
print("boundary: the dispatch key reaches the switch without a rotate"
      if not rotated else
      f"boundary: the dispatch key is normalised with {sorted(rotated)}")
PY

echo "boundary: pkg-app-services-wave11 validated"
