#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-ui-safe-wave10
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

for tool in clang++ clang-format objdump python3 git; do
  command -v "$tool" >/dev/null 2>&1 || {
    echo "missing required tool: $tool" >&2
    exit 127
  }
done

rm -rf "$work_dir"
mkdir -p "$work_dir"

for config in $binaries; do
  case "$config" in
    o0) flags="-O0" ;;
    o2) flags="-O2" ;;
    o0-ndebug) flags="-O0 -DNDEBUG" ;;
    o2-ndebug) flags="-O2 -DNDEBUG" ;;
  esac
  binary="$work_dir/$config"
  clang++ -m32 -std=c++17 $flags -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/ui_safe_wave10.cpp" \
    "$package_dir/ui_safe_wave10_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done

python3 - $disassembly <<'PY'
import re
import sys

TARGET = "00635700"
EXCLUDED = ("005bfd40", "00603650")
INSN = re.compile(
    r"^\s*(?P<addr>[0-9a-f]+):\s+(?P<mnemonic>\S+)\s*(?P<operands>.*)$", re.M
)
BODY = r"^[0-9a-f]+ <[^>]*%s[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
HEADER = re.compile(r"^[0-9a-f]+ <(?P<name>.*)>:$", re.M)
MEMORY = re.compile(r"\[(?P<base>[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]")
FRAME = ("esp", "ebp")
INDIRECT = re.compile(r"^(?:call|jmp)\s+(?![0-9a-f]+ <)")
IMMEDIATE = re.compile(r"^0x[0-9a-f]+$")
ENTRY_VTABLES = (0x13FE728, 0x13FE718)
EXIT_VTABLES = (0x13EC458, 0x013EB938)
HANDLE_SLOTS = (0x64, 0x68)
SERVICE_SLOTS = (0x14, 0x2C)


def fail(path, reason):
    raise SystemExit(f"{path}: {reason}")


def body_of(text, path, needle):
    selector = re.compile(BODY % re.escape(needle), re.M | re.S).search(text)
    if selector is None:
        fail(path, f"{needle} symbol missing")
    return selector.group("body")


def instructions(body):
    found = []
    for entry in INSN.finditer(body):
        mnemonic = entry.group("mnemonic")
        if mnemonic.startswith("data") or mnemonic.startswith("nop"):
            continue
        if mnemonic in ("int3", "xchg"):
            continue
        found.append((mnemonic, entry.group("operands").strip()))
    return found


def reached(code):
    found = set()
    for _, operands in code:
        for memory in MEMORY.finditer(operands):
            if memory.group("base") in FRAME:
                continue
            value = memory.group("disp")
            found.add(int(value, 16) if value else 0)
        for part in operands.split(","):
            token = part.strip()
            if IMMEDIATE.match(token):
                found.add(int(token, 16))
    return found


def load_offsets(code):
    found = set()
    for mnemonic, operands in code:
        if mnemonic != "mov" or "," not in operands:
            continue
        _source, _, destination = operands.partition(",")
        for memory in MEMORY.finditer(destination):
            if memory.group("base") in FRAME:
                continue
            found.add(int(memory.group("disp"), 16) if memory.group("disp") else 0)
    return found


def after_last_call(code):
    for index in range(len(code) - 1, -1, -1):
        if code[index][0] in ("call", "jmp"):
            return code[index + 1:]
    return []


for path in sys.argv[1:]:
    text = open(path, encoding="utf-8").read()
    for excluded in EXCLUDED:
        if excluded in text:
            fail(path, f"excluded target {excluded} reached the package")
        for header in HEADER.finditer(text):
            if excluded in header.group("name"):
                fail(path, f"excluded target {excluded} was reconstructed")

    code = instructions(body_of(text, path, TARGET))
    if not code:
        fail(path, f"{TARGET} has no instructions")

    returns = [operands for mnemonic, operands in code if mnemonic == "ret"]
    if len(returns) != 1:
        fail(path, f"{TARGET} has {len(returns)} returns instead of one")
    if returns[0] != "0x4":
        fail(path, f"{TARGET} exits with 'ret {returns[0]}' instead of 'ret 0x4'")
    if int(returns[0], 16) // 4 != 1:
        fail(path, f"{TARGET} releases {int(returns[0], 16) // 4} stack words")

    gate = [
        operands
        for mnemonic, operands in code
        if mnemonic in ("test", "and") and re.search(r",0x1$", operands)
    ]
    if not gate:
        fail(path, f"{TARGET} never gates the deallocation on bit zero")

    words = reached(code)
    for required in ENTRY_VTABLES + EXIT_VTABLES + HANDLE_SLOTS + SERVICE_SLOTS:
        if required not in words:
            fail(path, f"{TARGET} never reaches 0x{required:02x}")

    dispatches = [
        operands
        for mnemonic, operands in code
        if INDIRECT.match(mnemonic + " " + operands)
    ]
    if len(dispatches) < 5:
        fail(
            path,
            f"{TARGET} performs {len(dispatches)} indirect dispatches instead of"
            " five",
        )
    releases = [operands for operands in dispatches
                if re.search(r"\+(?:0x)?4\]$", operands)]
    handles = load_offsets(code)
    for required in HANDLE_SLOTS:
        if required not in handles:
            fail(path, f"{TARGET} never loads the handle at 0x{required:02x}")
    if 0x04 not in handles and len(releases) < 2:
        fail(
            path,
            f"{TARGET} never dispatches the handle vtable +0x4 release port",
        )

    tail = after_last_call(code)
    if not tail or tail[0][0] != "mov" or tail[0][1].split(",")[0].strip() != "eax":
        fail(path, f"{TARGET} never stages the receiver in eax before the exit")
    for mnemonic, _ in tail[1:]:
        if mnemonic not in ("add", "sub", "pop", "mov", "lea", "test", "and",
                            "ret"):
            fail(path, f"{TARGET} tail performs an unexpected {mnemonic}")
PY

format_style='{BasedOnStyle: Google, FixNamespaceComments: false}'
clang-format --dry-run --Werror --style="$format_style" \
  "$package_dir/ui_safe_wave10.hpp" \
  "$package_dir/ui_safe_wave10.cpp" \
  "$package_dir/ui_safe_wave10_model_test.cpp"

comment_scan=0
excluded_scan=0
for source in ui_safe_wave10.hpp ui_safe_wave10.cpp \
              ui_safe_wave10_model_test.cpp; do
  found=$(grep -c -e '//' -e '/\*' "$package_dir/$source" || true)
  comment_scan=$((comment_scan + found))
  stale=$(grep -c -e '005bfd40' -e '00603650' "$package_dir/$source" || true)
  excluded_scan=$((excluded_scan + stale))
done
if [ "$comment_scan" -ne 0 ]; then
  echo "comment-free invariant broken: $comment_scan comment markers" >&2
  exit 1
fi
if [ "$excluded_scan" -ne 0 ]; then
  echo "excluded target invariant broken: $excluded_scan references" >&2
  exit 1
fi

whitespace=0
for source in ui_safe_wave10.hpp ui_safe_wave10.cpp \
              ui_safe_wave10_model_test.cpp ui_safe_wave10_boundary_test.sh; do
  report=$(git diff --no-index --check -- /dev/null "$package_dir/$source" || true)
  if [ -n "$report" ]; then
    echo "$report" >&2
    whitespace=1
  fi
done
if [ "$whitespace" -ne 0 ]; then
  echo "whitespace diff check failed" >&2
  exit 1
fi

echo "pkg-ui-safe-wave10 boundary validation passed"
