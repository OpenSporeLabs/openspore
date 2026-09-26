#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode/pkg-skinner-wave11
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
sources="$package_dir/skinner_wave11.cpp $package_dir/skinner_wave11_model_test.cpp"
header="$package_dir/skinner_wave11.hpp"
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
  "$package_dir/skinner_wave11.cpp" \
  "$package_dir/skinner_wave11_model_test.cpp"
echo "format: clean"

for spec in o0:'-O0' o2:'-O2' o0n:'-O0 -DNDEBUG' o2n:'-O2 -DNDEBUG'; do
  tag=${spec%%:*}
  flags=${spec#*:}
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    $sources -o "$work/$tag.bin"
  clang++ -m32 -std=c++17 $flags $warnings -I "$package_dir" \
    -c "$package_dir/skinner_wave11.cpp" -o "$work/$tag.o"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.bin" >"$work/$tag.dis"
  objdump -dr --no-show-raw-insn -M intel "$work/$tag.o" >"$work/$tag.obj.dis"
  echo "build: $tag ok"
done

for tag in o0 o2 o0n o2n; do
  "$work/$tag.bin"
done

python3 - "$work" "$header" <<'PY'
import pathlib
import re
import sys

work = pathlib.Path(sys.argv[1])
header = pathlib.Path(sys.argv[2]).read_text()

TARGETS = {
    "skin_paint_slot_pass_005183c0": "0x0",
    "skin_tex0_full_region_00518bf0": "0x0",
    "skin_tex2_uv_region_00518cf0": "0x0",
    "skin_rig_block_draw_00518f10": "0x0",
    "skin_rig_pass_state_00519640": "0x0",
    "skin_rig_index_pass_0051a350": "0x0",
    "skin_job_setup_0051a9a0": "0x28",
    "skin_job_collect_0051ab50": "0x4",
    "skin_job_state_step_0051afd0": "0x0",
}

# every target must keep at least this many indirect port dispatches, so a
# seam can never be folded into a direct call by the optimiser
PORT_MIN = {
    "skin_paint_slot_pass_005183c0": 4,
    "skin_tex0_full_region_00518bf0": 2,
    "skin_tex2_uv_region_00518cf0": 1,
    "skin_rig_block_draw_00518f10": 4,
    "skin_rig_pass_state_00519640": 6,
    "skin_rig_index_pass_0051a350": 4,
    "skin_job_setup_0051a9a0": 1,
    "skin_job_collect_0051ab50": 5,
    "skin_job_state_step_0051afd0": 0,
}

BODY = re.compile(
    r"^[0-9a-f]+ <(?P<name>[^>]+)>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
    re.S | re.M,
)
RET = re.compile(r"^\s*[0-9a-f]+:\s+ret(?:\s+(0x[0-9a-f]+))?\s*$", re.M)
INDIRECT = re.compile(r"call\s+DWORD PTR \[[^\]]+\]")
ECX_READ = re.compile(r"mov\s+DWORD PTR \[e[a-z]{2}-0x[0-9a-f]+\],ecx")

REQUIRED_HEADER_OFFSETS = [
    "offsetof(OpaqueTexturePainter, count_044) == 0x44",
    "offsetof(OpaqueTexturePainter, rasters_03c) == 0x3c",
    "offsetof(OpaqueTexturePainter, field_060) == 0x60",
    "offsetof(OpaqueTexturePainter, params_02c) == 0x2c",
    "offsetof(OpaqueSkinPainter, textures_010) == 0x10",
    "offsetof(OpaqueSkinPainter, scale_02c) == 0x2c",
    "offsetof(OpaqueSkinPainter, field_040) == 0x40",
    "offsetof(OpaqueMesh, field_008) == 0x08",
    "offsetof(OpaqueMesh, slots_090) == 0x90",
    "offsetof(OpaqueMeshBlock, rigblocks_098) == 0x98",
    "offsetof(OpaqueBatch, index_080) == 0x80",
    "offsetof(OpaqueBatch, slots_begin_0e4) == 0xe4",
    "offsetof(OpaquePaintSystem, mesh_020) == 0x20",
    "offsetof(OpaquePaintSystem, byte_07c) == 0x7c",
    "offsetof(OpaqueSkinJob, handle_330) == 0x330",
    "offsetof(OpaqueSkinJob, state_33c) == 0x33c",
    "offsetof(OpaqueSkinJob, flag_34e) == 0x34e",
    "offsetof(OpaqueElementVTable, has_01c) == 0x1c",
    "offsetof(OpaqueElementVTable, get_028) == 0x28",
    "offsetof(OpaqueRenderTargetManagerVTable, prepare_034) == 0x34",
    "offsetof(OpaqueGraphicsProbeVTable, query_044) == 0x44",
    "offsetof(OpaqueRefObject, refcount_008) == 0x08",
    "offsetof(OpaqueRefVTable, step_010) == 0x10",
    "sizeof(OpaqueRigblock) == 0x8c",
    "sizeof(OpaqueTexturePainter) == 0x68",
    "sizeof(OpaqueSkinJob) == 0x350",
]

problems = []

for needle in REQUIRED_HEADER_OFFSETS:
    if needle not in header:
        problems.append(f"header lost the layout assertion: {needle}")


def bodies(text):
    out = {}
    for match in BODY.finditer(text):
        out.setdefault(match.group("name"), "")
        out[match.group("name")] += match.group("body")
    return out


image = bodies((work / "o2.dis").read_text())
objects = {tag: bodies((work / f"{tag}.obj.dis").read_text())
           for tag in ("o0", "o2", "o0n", "o2n")}

# 1. ret width per target, in the object and in the linked image
for name, want in TARGETS.items():
    listings = [("image", image.get(name))]
    listings += [(tag, objects[tag].get(name)) for tag in objects]
    for source, body in listings:
        if body is None:
            problems.append(f"{name} missing from the {source} listing")
            continue
        rets = RET.findall(body)
        if not rets:
            problems.append(f"{name} ({source}) has no ret")
            continue
        got = rets[-1] or "0x0"
        if got != want:
            problems.append(f"{name} ({source}) ret {got} != {want}")

# 2. the thiscall receiver reaches the frame; at -O0 the spill is
# deterministic, at -O2 the register may be folded away entirely
for name in TARGETS:
    for tag in ("o0", "o0n"):
        body = objects[tag].get(name) or ""
        if not ECX_READ.search(body):
            problems.append(f"{name} ({tag}) does not spill ECX")

# 3. the port seam survives every configuration
for name, floor in PORT_MIN.items():
    for tag in objects:
        body = objects[tag].get(name) or ""
        got = len(INDIRECT.findall(body))
        if got < floor:
            problems.append(
                f"{name} ({tag}) has {got} indirect port calls, need {floor}")

# 4. NDEBUG must not change the emitted code
for a, b in (("o0", "o0n"), ("o2", "o2n")):
    if (work / f"{a}.o").read_bytes() != (work / f"{b}.o").read_bytes():
        problems.append(f"{a}.o and {b}.o differ under NDEBUG")

# 5. the nine targets must be exported unmangled
symbols = (work / "o2.dis").read_text()
for name in TARGETS:
    if f"<{name}>:" not in symbols:
        problems.append(f"{name} is not an unmangled external symbol")

# 6. the nine addresses the package claims must be unique in the header
declared = re.findall(r"skin_[a-z0-9_]+_0051[0-9a-f]{4}|"
                      r"skin_[a-z0-9_]+_00518[0-9a-f]{3}", header)
if len(set(declared)) != 9:
    problems.append(f"header declares {len(set(declared))} targets, need 9")

if problems:
    for line in problems:
        print("problem:", line)
    raise SystemExit(1)

print("ret widths: 9 targets x 5 listings ok")
print("receiver spilled from ecx: 9 targets in the unoptimised builds")
print("port seam: indirect dispatch floors met in every configuration")
print("ndebug: objects byte identical")
print("symbols: 9 unmangled externs present")
print("layout assertions: present in the header")
PY

echo "boundary: all checks passed"
