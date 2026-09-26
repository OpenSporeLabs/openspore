#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-palette-wave11
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Left, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/pkg_palette_wave11.cpp $package_dir/pkg_palette_wave11_model_test.cpp"
headers="$package_dir/pkg_palette_wave11.hpp"
warnings='-Wall -Wextra -Wpedantic -Werror'

mkdir -p "$work"
trap 'rm -rf "$work"' EXIT

clang-format --style="$style" --dry-run -Werror \
  "$headers" \
  "$package_dir/pkg_palette_wave11.cpp" \
  "$package_dir/pkg_palette_wave11_model_test.cpp"
echo "format: clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/pkg_palette_wave11.cpp" -o "$work/$tag.o"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.bin" >"$work/$tag.dis"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.o" >"$work/$tag.obj.dis"
  echo "build: $tag ok"
done

# The model test reports "checks=N failures=M" and exits non-zero on any
# failure, so the all pass line below is only reached when every configuration
# reported zero failures. NDEBUG must not shrink N: the asserts are routed
# through g_checks and g_failures precisely so the two NDEBUG builds still
# verify the same 219 invariants.
for tag in o0 o2 o0n o2n; do
  report=$("$work/$tag.bin")
  echo "$report"
  case "$report" in
    *"failures=0"*) ;;
    *) echo "model: $tag did not report failures=0" >&2; exit 1 ;;
  esac
  checks=$(printf '%s\n' "$report" | sed -n 's/.*checks=\([0-9][0-9]*\).*/\1/p')
  if [ -z "$checks" ] || [ "$checks" -lt 219 ]; then
    echo "model: $tag ran only ${checks:-0} checks, expected at least 219" >&2
    exit 1
  fi
done
echo "model: o0, o2, o0n and o2n all pass"
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

LINK = "palette_w11_resolve_link_tail_005c2e00"
RELEASE = "palette_w11_release_page_hold_005c7320"
WALK = "palette_w11_walk_has_leaf_005c7c10"
FILL = "palette_w11_fill_node_array_005c7ff0"
LOAD = "palette_w11_load_page_state_005c85d0"
PLACE = "palette_w11_place_page_nodes_005ca9f0"

ENTRY = (LINK, RELEASE, WALK, FILL, LOAD, PLACE)

RETURNS = {
    LINK: {""},
    RELEASE: {""},
    WALK: {""},
    FILL: {"0xc"},
    LOAD: {"0x8"},
    PLACE: {""},
}

SLOT_OFFSETS = {
    LINK: set(),
    RELEASE: {0x4, 0x108},
    WALK: set(),
    FILL: {0x4, 0x8, 0x2C, 0x7C},
    LOAD: {0x4, 0xC, 0x24},
    PLACE: {0x4, 0x8, 0x10, 0x34, 0x38, 0x60, 0x7C, 0xC0, 0xC4},
}

DISPATCHES = {
    LINK: False,
    RELEASE: True,
    WALK: False,
    FILL: True,
    LOAD: True,
    PLACE: True,
}

OFFSETS = {
    LINK: {0x58, 0x6C, 0x9C},
    RELEASE: {0x00, 0x04, 0x14, 0x18, 0x108},
    WALK: {
        0x00, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x34, 0x38, 0x70, 0x74,
    },
    FILL: {
        0x00, 0x04, 0x08, 0x2C, 0x3C, 0x48, 0x50, 0x54, 0x70, 0x7C, 0x118,
    },
    LOAD: {
        0x00, 0x04, 0x08, 0x0C, 0x12, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28,
        0x2C, 0x2D, 0x30, 0x34, 0x38, 0x3C, 0x40, 0x44, 0x48, 0x49, 0x4A,
        0x4C, 0x50, 0x54, 0x58, 0x5C, 0x70, 0x74, 0x78, 0x24,
    },
    PLACE: {
        0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x34, 0x38,
        0x48, 0x4C, 0x60, 0x64, 0x7C, 0xC0, 0xC4,
    },
}

PORTS = {
    LINK: {"unresolved_005c9830"},
    RELEASE: {"unresolved_00401020", "unresolved_005f0a60"},
    WALK: {
        "unresolved_005c5de0",
        "unresolved_005cae30",
        "unresolved_005c1ce0",
    },
    FILL: {
        "unresolved_00410370",
        "unresolved_005766e0",
        "unresolved_005c66a0",
        "unresolved_005c6810",
        "unresolved_0067dcd0",
        "unresolved_0067de30",
        "unresolved_006a07d0",
        "unresolved_006a0ae0",
        "unresolved_006a12a0",
        "unresolved_00933960",
        "unresolved_00f47380",
        "unresolved_00f473a0",
    },
    LOAD: {
        "unresolved_0041e920",
        "unresolved_0041e990",
        "unresolved_0041ea00",
        "unresolved_0041ea70",
        "unresolved_005c8480",
        "unresolved_0067de30",
        "unresolved_006a1160",
        "unresolved_006a1250",
        "unresolved_006a12a0",
    },
    PLACE: {"unresolved_005c2ec0", "unresolved_005ca9c0"},
}

LITERALS = {
    LINK: (),
    RELEASE: (),
    WALK: (),
    FILL: ("g_dword_015fd918",),
    LOAD: ("g_float_01485720",),
    PLACE: ("g_float_013eb95c", "g_float_014854c4"),
}

DECLARED_PORTS = {
    "unresolved_00401020",
    "unresolved_00410370",
    "unresolved_0041e920",
    "unresolved_0041e990",
    "unresolved_0041ea00",
    "unresolved_0041ea70",
    "unresolved_005766e0",
    "unresolved_005c1ce0",
    "unresolved_005c2ec0",
    "unresolved_005c66a0",
    "unresolved_005c6810",
    "unresolved_005c8480",
    "unresolved_005c9830",
    "unresolved_005ca9c0",
    "unresolved_005cae30",
    "unresolved_005c5de0",
    "unresolved_005f0a60",
    "unresolved_0067dcd0",
    "unresolved_0067de30",
    "unresolved_006a07d0",
    "unresolved_006a0ae0",
    "unresolved_006a1160",
    "unresolved_006a1250",
    "unresolved_006a12a0",
    "unresolved_00933960",
    "unresolved_00f47380",
    "unresolved_00f473a0",
}

OWNED = {
    "0x005c2e00": LINK,
    "0x005c7320": RELEASE,
    "0x005c7c10": WALK,
    "0x005c7ff0": FILL,
    "0x005c85d0": LOAD,
    "0x005ca9f0": PLACE,
}


def fail(message):
    raise SystemExit(f"boundary: {message}")


def bodies(path):
    return {
        m.group("name"): m.group("body") for m in BODY.finditer(path.read_text())
    }


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
reached = {}
for tag in ("o0", "o2", "o0n", "o2n"):
    path = work / f"{tag}.obj.dis"
    text = path.read_text()
    table = bodies(path)
    flat = re.sub(r"\s+", "", text)
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
        if DISPATCHES[name] and not found_dispatch:
            fail(f"{tag}: {name} performs no indirect dispatch")
        if not DISPATCHES[name] and found_dispatch:
            fail(f"{tag}: {name} dispatches indirectly but owns no vtable")
        found_offsets = field_offsets(body)
        if not found_offsets <= OFFSETS[name]:
            extra = sorted(found_offsets - OFFSETS[name])
            fail(f"{tag}: {name} reads unexpected offsets {show(set(extra))}")
        found_ports = ports(body)
        if not found_ports <= PORTS[name]:
            extra = sorted(found_ports - PORTS[name])
            fail(f"{tag}: {name} crosses {sorted(set(extra))}")
        reached.setdefault(name, set()).update(found_offsets)
        reached[name].update(found_ports)
        for literal in LITERALS[name]:
            probe = re.sub(r"\s+", "", literal)
            if probe not in flat:
                fail(f"{tag}: {name} does not reference {literal}")
    if "sar" not in text:
        fail(f"{tag}: the eight byte slot shift is gone")
    if WALK not in table:
        fail(f"{tag}: {WALK} is missing from the object file")
    if "sar" not in text and "shr" not in text:
        fail(f"{tag}: the arithmetic shift is gone")
    if "mul" not in text:
        fail(f"{tag}: the nine way page division is gone")
    if "0x38e38e39" not in text:
        fail(f"{tag}: the nine way page magic divisor is gone")
    whole = ports(path.read_text()) - set(TOOLCHAIN)
    if reference is None:
        reference = whole
    elif whole != reference:
        fail(f"{tag}: the port set diverges from o0: {sorted(whole ^ reference)}")
    sizes[tag] = {
        name: (
            len(STEP.findall(table[name])),
            len(dispatches(table[name])),
        )
        for name in ENTRY
    }

for name in ENTRY:
    missing_offsets = OFFSETS[name] - reached[name]
    if missing_offsets:
        fail(f"{name} never reaches {show(missing_offsets)}")
    missing_ports = PORTS[name] - reached[name]
    if missing_ports:
        fail(f"{name} never crosses {sorted(missing_ports)}")

if reference != DECLARED_PORTS:
    fail(
        "the crossed port set differs from the declared one:"
        f" {sorted(reference ^ DECLARED_PORTS)}"
    )

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
    "boundary: 005c2e00, 005c7320 and 005c7c10 release nothing,"
    " 005c7ff0 releases 0xc and 005c85d0 releases 0x8"
    " in o0, o2, o0n and o2n"
)
print("boundary: NDEBUG leaves the emitted object byte for byte equal")
print("boundary: the crossed port set equals the 27 declared ports")
print("boundary: 005c7c10 keeps its arithmetic shift and 005ca9f0 its divide")
for va, name in sorted(OWNED.items()):
    print(
        f"boundary: {va} pins {show(SLOT_OFFSETS[name]) or '{} (no vtable)'}"
        f" through indirect"
        f" dispatch, reads {len(OFFSETS[name])} field offsets,"
        f" crosses {len(PORTS[name])} ports,"
        f" {sizes['o0'][name][0]} instructions and {sizes['o0'][name][1]}"
        f" indirect dispatches at o0,"
        f" {sizes['o2'][name][0]} and {sizes['o2'][name][1]} at o2"
    )
for port, total in sorted(touched.items()):
    print(f"boundary:   {port} crossed by {total} of 6 entries")
PY

echo "boundary: pkg-palette-wave11 validated"
