#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-simulator-wave11
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/simulator_wave11.cpp $package_dir/simulator_wave11_model_test.cpp"
headers="$package_dir/simulator_wave11.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/simulator_wave11.cpp" \
  "$package_dir/simulator_wave11_model_test.cpp"
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
    -c "$package_dir/simulator_wave11.cpp" -o "$work/$tag.o"
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
TAIL = re.compile(r"^\s*[0-9a-f]+:\s+jmp\s+(?!.*<)", re.M | re.I)
SIGNED_GATE = re.compile(r"^\s*[0-9a-f]+:\s+j(?:g|le)\s", re.M | re.I)
UNSIGNED_ALT = re.compile(r"^\s*[0-9a-f]+:\s+j(?:a|be)\s", re.M | re.I)
BACKWARD = re.compile(
    r"^\s*(?P<at>[0-9a-f]+):\s+(?:j\w+|call)\s+(?P<addr>[0-9a-f]+)\b", re.M | re.I
)
UNSIGNED_GATE = re.compile(r"^\s*[0-9a-f]+:\s+ja\s", re.M | re.I)
X87 = re.compile(r"^\s*[0-9a-f]+:\s+f(?:ld|st|add|mul|sub|div|chs|abs|ild|com|"
                 r"ucomi|nst)\w*\s", re.M | re.I)
STORE = re.compile(
    r"^\s*[0-9a-f]+:\s+mov\w*\s+DWORD PTR \[(?P<mem>[^\]]+)\],(?P<val>0x[0-9a-f]+|\w+)",
    re.M | re.I,
)

EXPECTED = {
    "dispatch_key_00628450": "0x0",
    "cycle_key_006286a0": "0x0",
    "forward_key_00628af0": "0x8",
    "route_key_00628d50": "0x4",
    "release_child_0062c910": "0x0",
}

DIRECT = ("simulator_runtime_00628", "cycle_key_006286a0")

CLOSURE = "pkg_simulator_wave11"

INDIRECT_COUNT = 6

INLINE_ROUTE = ("0x445b018", "0x445b318", "0x445b340", "0x445b388",
                "0xa03e74b2", "0xfffffffe")

POOLED_ROUTE = ("0x4330667", "0x70842ef6")

PORTS_NAMED = (
    "provider_0067ddd0",
    "view_manager_0067caa0",
    "asset_view_00401030",
    "debug_service_00a206f0",
    "emit_debug_00435ed0",
    "resolve_00634e40",
    "random_00a68fb0",
    "submit_0062f7f0",
    "probe_0062f6c0",
    "release_0062c340",
    "apply_00628ca0",
    "post_event_00574110",
    "select_005dbbb0",
)

VTABLE_SLOTS = (
    ("0x04", ("release_child_0062c910",)),
    ("0x08", ("dispatch_key_00628450", "release_child_0062c910")),
    ("0x0c", ("route_key_00628d50", "blend_00628d50", "forward_key_00628af0")),
    ("0x20", ("route_key_00628d50",)),
    ("0x24", ("forward_key_00628af0",)),
    ("0x28", ("forward_key_00628af0",)),
    ("0x2c", ("route_key_00628d50",)),
    ("0x48", ("probe_select_00628af0", "forward_key_00628af0")),
    ("0x4c", ("forward_key_00628af0",)),
    ("0x5c", ("dispatch_key_00628450",)),
    ("0x84", ("forward_key_00628af0",)),
)

EXCLUSIONS = (
    "0062a7f0", "00628500", "00628570", "006285c0",
    "013fe120", "013fe128", "015d0c0c", "0166d9f4", "015fcc4c", "015fd8e8",
)

FIELD_OFFSETS = (
    ("0x36d4", ("cycle_key_006286a0",)),
    ("0x3614", ("route_key_00628d50",)),
    ("0x3618", ("route_key_00628d50",)),
    ("0x3588", ("blend_00628d50", "route_key_00628d50", "release_child_0062c910")),
    ("0x0c", ("forward_key_00628af0", "route_key_00628d50", "release_child_0062c910")),
    ("0x094", ("release_child_0062c910",)),
    ("0xcc", ("release_child_0062c910",)),
    ("0xac", ("route_key_00628d50",)),
    ("0x04", ("route_key_00628d50",)),
)


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())}


def lines_of(body):
    return [line for line in body.splitlines() if STEP.match(line)]


def address_of(line):
    match = re.match(r"^\s*([0-9a-f]+):", line)
    return int(match.group(1), 16) if match else 0


def last_ret(body):
    found = RET.findall(body)
    if not found:
        return None
    return found[-1] or "0x0"


def relocation_names(text):
    return {name for name in RELOC.findall(text) if "GOT" not in name}


def slot_reached(table, fragments, slot):
    value = slot[2:].lstrip("0") or "0"
    pattern = re.compile(r"\[(?!e?[bs]p)[a-z]{2,3}\+0x0*" + value + r"\]", re.I)
    for fragment in fragments:
        for name, body in table.items():
            if fragment in name and any(pattern.search(line)
                                        for line in lines_of(body)):
                return True
    return False


def fragment_bodies(table, fragment):
    return [body for name, body in table.items() if fragment in name]


def trailing_offset(memory):
    found = re.search(r"\+(?:0x)?0*([0-9a-f]+)$", memory, re.I)
    return int(found.group(1), 16) if found else None


def offset_reached(body, offset):
    value = offset[2:].lstrip("0") or "0"
    pattern = re.compile(
        r"(?:\+0x0*" + value + r"\]|\b0x0*" + value + r"\b)", re.I
    )
    return any(pattern.search(line) for line in lines_of(body))


reference = None
sizes = {}
indirect_counts = {}
tail_calls = {}
table_shape = {}
x87_seen = {}
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

    if tag == "o2":
        for offset, fragments in FIELD_OFFSETS:
            reachable = [
                body
                for fragment in fragments
                for body in fragment_bodies(table, fragment)
            ]
            if not reachable:
                fail(f"o2: no body matches {fragments}")
            if not any(offset_reached(body, offset) for body in reachable):
                fail(f"o2: {fragments[0]} never reaches the {offset} field")

    for slot, fragments in VTABLE_SLOTS:
        if not slot_reached(table, fragments, slot):
            fail(f"{tag}: {fragments[0]} never loads vtable slot {slot}")

    dispatch = table["dispatch_key_00628450"]
    for token in ("0xe18d6423",):
        if token not in dispatch:
            fail(f"{tag}: 00628450 drops the {token} literal")
    if len(INDIRECT.findall(dispatch)) < 2:
        fail(f"{tag}: 00628450 crosses fewer than two ports")
    cycle = table["cycle_key_006286a0"]
    candidates = ("0x431df93", "0x431df9a", "0x431df9f", "0x431dfa6",
                  "0x44d798c", "0x44d7999")
    inline = all(token in cycle for token in candidates)
    indexed = bool(re.search(r"DWORD PTR \[\w+\+eax\*4", cycle))
    if not inline and not indexed:
        fail(f"{tag}: 006286a0 loses the candidate table")
    table_shape[tag] = "inline" if inline else "indexed"
    if indexed and not UNSIGNED_GATE.search(cycle):
        fail(f"{tag}: 006286a0 drops the unsigned gate on the indexed table")
    body_lines = lines_of(cycle)
    branches = [BACKWARD.search(line) for line in body_lines]
    if not any(found and int(found.group("addr"), 16) < int(found.group("at"), 16)
               for found in branches):
        fail(f"{tag}: 006286a0 never branches back for a redraw")
    if tag == "o0" and not UNSIGNED_GATE.search(cycle):
        fail("o0: 006286a0 lost the unsigned range gate on the draw")

    forward = table["forward_key_00628af0"]
    for token in ("0x3f67620", "0x4581d50", "0x4581d78", "0x4581d90",
                  "0x3a8ede4", "0x43"):
        if token not in forward:
            fail(f"{tag}: 00628af0 drops the literal {token}")
    route = table["route_key_00628d50"]
    if not SIGNED_GATE.search(route):
        fail(f"{tag}: 00628d50 lost its signed greater-than gate")
    if tag == "o0" and UNSIGNED_ALT.search(route):
        fail("o0: 00628d50 gates its selection on an unsigned compare")
    for token in INLINE_ROUTE:
        if token not in route:
            fail(f"{tag}: 00628d50 drops the literal {token}")
    pooled_here = all(token in route for token in POOLED_ROUTE)
    if tag == "o0" and not pooled_here:
        fail("o0: 00628d50 pools one of its blend or post-event constants")
    if tag == "o2" and not pooled_here and ".rodata" not in route:
        fail("o2: 00628d50 pools its constants without a rodata reference")
    if "0xfffffffe" not in route:
        fail(f"{tag}: 00628d50 drops the 0xfffffffe flag mask")
    if "0x3614" not in route:
        fail(f"{tag}: 00628d50 never reads the owner at +0x3614")
    if "0xac" not in route:
        fail(f"{tag}: 00628d50 never reads the flag pointer at +0xac")

    release = table["release_child_0062c910"]
    indirect_counts[tag] = len(INDIRECT.findall(release))
    if indirect_counts[tag] != INDIRECT_COUNT:
        fail(
            f"{tag}: 0062c910 crosses {indirect_counts[tag]} ports"
            f" instead of {INDIRECT_COUNT}"
        )
    tail_calls[tag] = len(TAIL.findall(release))
    release_lines = lines_of(release)
    indirect_at = [index for index, line in enumerate(release_lines)
                   if INDIRECT.search(line) or TAIL.search(line)]
    if not indirect_at:
        fail(f"{tag}: 0062c910 crosses no ports at all")
    last_port = indirect_at[-1]
    if tag == "o2":
        cleared = 0
        for index, line in enumerate(release_lines):
            found = STORE.search(line)
            if not found:
                continue
            if trailing_offset(found.group("mem")) not in (0x0C, 0x94, 0xCC):
                continue
            if not re.fullmatch(r"(?:0|0x0+|esi|eax)", found.group("val")):
                continue
            cleared += 1
            if index > last_port:
                fail(f"o2: 0062c910 clears a slot at {address_of(line):#x}"
                     f" after its last port call"
                     f" at {address_of(release_lines[last_port]):#x}")
        if cleared != 3:
            fail(f"o2: 0062c910 clears {cleared} slots instead of 3")

    x87_seen[tag] = bool(X87.search(route))
    if x87_seen[tag] and "fstp" not in route.lower():
        fail(f"{tag}: 00628d50 leaves the x87 stack unbalanced")

    text = (work / f"{tag}.obj.dis").read_text()
    whole = relocation_names(text)
    foreign = sorted(
        name
        for name in whole
        if CLOSURE not in name and not any(entry in name for entry in EXPECTED)
    )
    if foreign:
        fail(f"{tag}: direct calls leave the package: {foreign}")
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

if indirect_counts["o0"] != indirect_counts["o2"]:
    fail("0062c910 changes its port count between o0 and o2")
if tail_calls["o0"] != tail_calls["o2"]:
    fail("0062c910 changes its tail-jump count between o0 and o2")
if any(tail_calls[tag] for tag in tail_calls):
    tail_note = "tail-jumps"
else:
    tail_note = "invokes the last port with call, not the original tail jmp"

print("boundary: 00628450 releases 0x0, 006286a0 releases 0x0, "
      "00628af0 releases 0x8")
print("boundary: 00628d50 releases 0x4, 0062c910 releases 0x0")
print("boundary: ret widths hold in o0, o2, o0n and o2n")
print("boundary: o2 keeps every state field at its original offset")
print("boundary: 00628450 keeps the 0xe18d6423 fallback key")
print("boundary: 00628af0 keeps its four select and probe constants")
print("boundary: 006286a0 keeps all six candidates and a backward redraw")
for tag in ("o0", "o2"):
    print(f"boundary:   {tag} realizes the candidate table {table_shape[tag]}")
print(f"boundary: all {len(VTABLE_SLOTS)} vtable slots load in every "
      f"configuration")
print(f"boundary: all {len(FIELD_OFFSETS)} state offsets hold at o2")
print("boundary: 00628d50 keeps its signed greater-than gate and flag mask")
print(f"boundary: 0062c910 crosses {indirect_counts['o0']} ports in every "
      f"configuration")
print(f"boundary: 0062c910 {tail_note}")
print("boundary: 0062c910 clears all three slots before its last port call")
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: every direct call stays inside the package closure")
print(f"boundary: all {len(PORTS_NAMED)} va-suffixed function ports are named")
print("boundary: the 0x015f7cf4 holder and the 0x01601760 lcg state are data")
for symbol in EXPECTED:
    print(
        f"boundary: {symbol} has {sizes['o0'][symbol]} instructions at o0"
        f" and {sizes['o2'][symbol]} at o2"
    )
PY

echo "boundary: pkg-simulator-wave11 validated"
