#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work=/tmp/opencode
o0_binary=$work/pkg-ui-wave10-boundary-o0
o2_binary=$work/pkg-ui-wave10-boundary-o2
nd_binary=$work/pkg-ui-wave10-boundary-ndebug
o0_disassembly=$work/pkg-ui-wave10-boundary-o0.dis
o2_disassembly=$work/pkg-ui-wave10-boundary-o2.dis

mkdir -p "$work"
trap 'rm -f "$o0_binary" "$o2_binary" "$nd_binary" "$o0_disassembly" "$o2_disassembly"' EXIT

for tool in clang++ clang-format objdump python3; do
  command -v "$tool" >/dev/null 2>&1 || {
    echo "missing required tool: $tool" >&2
    exit 127
  }
done

build() {
  out=$1
  shift
  clang++ -m32 -std=c++17 "$@" -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/ui_wave10.cpp" \
    "$package_dir/ui_wave10_model_test.cpp" -o "$out"
}

build "$o0_binary" -O0
build "$o2_binary" -O2
build "$nd_binary" -O2 -DNDEBUG

objdump -dr --no-show-raw-insn -M intel "$o0_binary" >"$o0_disassembly"
objdump -dr --no-show-raw-insn -M intel "$o2_binary" >"$o2_disassembly"

python3 - "$o0_disassembly" "$o2_disassembly" <<'PY'
import re
import sys

SYMBOLS = {
    "005bfd40": (
        "_ZN9openspore14reconstruction13pkg_ui_wave1022pkg_ui_wave10_005bfd40"
        "EPNS1_15OpaqueNamePanelEjjjjj",
        "0x14",
    ),
    "00603650": (
        "_ZN9openspore14reconstruction13pkg_ui_wave1022pkg_ui_wave10_00603650"
        "EPNS1_14OpaqueSettingsE",
        "",
    ),
    "00635700": (
        "_ZN9openspore14reconstruction13pkg_ui_wave1022pkg_ui_wave10_00635700"
        "EPNS1_18OpaqueImageArchiveEj",
        "0x4",
    ),
}

ARGS = {"005bfd40": 5, "00603650": 0, "00635700": 1}

INSN = re.compile(
    r"^[ \t]*(?P<addr>[0-9a-f]+):[ \t]+(?P<mnemonic>\S+)[ \t]*(?P<operands>.*)$",
    re.M,
)
BODY = r"^[0-9a-f]+ <%s>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\n\n|\Z)"


def fail(path, reason):
    raise SystemExit(f"{path}: {reason}")


def verify(path):
    text = open(path, encoding="utf-8").read()
    for va, (symbol, expected_ret) in SYMBOLS.items():
        selector = re.compile(BODY % re.escape(symbol), re.M | re.S)
        match = selector.search(text)
        if match is None:
            fail(path, f"{va} symbol missing")
        instructions = [
            entry
            for entry in INSN.finditer(match.group("body"))
            if not entry.group("mnemonic").startswith("data")
            and not entry.group("mnemonic").startswith("nop")
            and entry.group("mnemonic") not in ("int3", "xchg")
        ]
        if not instructions:
            fail(path, f"{va} has no instructions")
        returns = [
            entry
            for entry in instructions
            if entry.group("mnemonic") == "ret"
        ]
        if not returns:
            fail(path, f"{va} never returns")
        for entry in returns:
            operands = entry.group("operands").strip()
            if operands != expected_ret:
                fail(
                    path,
                    f"{va} exits with 'ret {operands}' instead of"
                    f" 'ret {expected_ret}'",
                )
        body = match.group("body")
        if not re.search(r"\bcall\b", body):
            fail(path, f"{va} performs no call")
        words = 0 if expected_ret == "" else int(expected_ret, 16) // 4
        expected_words = ARGS[va]
        if words != expected_words:
            fail(
                path,
                f"{va} releases {words} stack words instead of {expected_words}",
            )
    archive = re.compile(
        BODY % re.escape(SYMBOLS["00635700"][0]), re.M | re.S
    )
    archive_body = archive.search(text)
    if archive_body is None:
        fail(path, "00635700 body unavailable")
    archive_text = archive_body.group("body")
    if not re.search(r"(?:test|and)\s+e?[a-z0-9]+,0x1\b", archive_text):
        fail(path, "00635700 does not gate the deallocation on bit zero")
    if "pkg_ui_wave10_free_00f47380" not in archive_text:
        fail(path, "00635700 never reaches the deallocation contract")
    for offset in ("0x2c", "0x64", "0x68"):
        if not re.search(r"[,+]" + offset + r"\b", archive_text):
            fail(path, f"00635700 never touches object offset {offset}")


for path in sys.argv[1:]:
    verify(path)
PY

format_style='{BasedOnStyle: Google, FixNamespaceComments: false}'
clang-format --dry-run --Werror --style="$format_style" \
  "$package_dir/ui_wave10.hpp" \
  "$package_dir/ui_wave10.cpp" \
  "$package_dir/ui_wave10_model_test.cpp"

comment_scan=0
for source in ui_wave10.hpp ui_wave10.cpp ui_wave10_model_test.cpp; do
  found=$(grep -c -e '//' -e '/\*' "$package_dir/$source" || true)
  comment_scan=$((comment_scan + found))
done
if [ "$comment_scan" -ne 0 ]; then
  echo "comment-free invariant broken: $comment_scan comment markers" >&2
  exit 1
fi

"$o0_binary"
"$o2_binary"
"$nd_binary"
