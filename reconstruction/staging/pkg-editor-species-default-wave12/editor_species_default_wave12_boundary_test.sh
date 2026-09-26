#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-editor-species-default-wave12
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

if command -v clang-format >/dev/null 2>&1; then
  for source in editor_species_default_wave12.hpp \
                editor_species_default_wave12.cpp \
                editor_species_default_wave12_model_test.cpp; do
    clang-format --dry-run -Werror "$package_dir/$source"
  done
  echo "format: clang-format clean over the header, the source and the model test"
else
  echo "format: clang-format unavailable, skipped" >&2
  exit 1
fi

for config in $binaries; do
  case "$config" in
    o0) flags="-O0" ;;
    o2) flags="-O2" ;;
    o0-ndebug) flags="-O0 -DNDEBUG" ;;
    o2-ndebug) flags="-O2 -DNDEBUG" ;;
  esac
  binary="$work_dir/$config"
  clang++ -m32 -std=c++17 $flags -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/editor_species_default_wave12.cpp" \
    "$package_dir/editor_species_default_wave12_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done
echo "build: all four configurations compiled clean and every model test passed"

python3 - $disassembly <<'PY'
import re
import sys

INSN = re.compile(
    r"^[ \t]*(?P<addr>[0-9a-f]+):[ \t]+(?P<mnemonic>\S+)[ \t]*"
    r"(?P<operands>[^\n]*)$",
    re.M,
)
# The body of one symbol, up to the next symbol header. re.S is required: the
# instruction lines are separated by newlines and "." must cross them.
BODY = r"^[0-9a-f]+ <%s>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
TARGET = "editor_species_resolve_fun_004df420"
BODY = BODY % re.escape(TARGET)
# Every stack word count this frame's return may release. The observed return at
# 0x004df43b is a bare RET, so the frame releases nothing; the one dword pushed at
# 0x004df42f belongs to 0x004df550, which pops it with its own RET 0x4.
EXPECTED_CLEANUP = {0x00}
# The one port the body may dispatch to, by emitted symbol name. The test binary
# links the recording stub at this address, so the VA is not the original one and
# the symbol is what carries the contract.
ALLOWED_PORTS = {"unresolved_004df550"}
# The displacement ADD EAX,0xa4 forms at 0x004df42a.
RECEIVER_DISPLACEMENT = 0xA4
# Any absolute operand in this range would be a reference into the image, i.e. a
# global. The original body has none: it names no absolute address.
IMAGE_LOW, IMAGE_HIGH = 0x00400000, 0x02000000

listing = []
for path in sys.argv[1:]:
    with open(path, encoding="utf-8") as handle:
        listing.append(handle.read())

for text in listing:
    match = re.search(BODY, text, re.S | re.M)
    if not match:
        raise SystemExit("FAIL: no disassembly for %s" % TARGET)
    body = match.group("body")
    instructions = [
        (m.group("mnemonic").lower(), (m.group("operands") or "").strip())
        for m in INSN.finditer(body)
    ]
    if not instructions:
        raise SystemExit("FAIL: empty body for %s" % TARGET)

    for mnemonic, operands in instructions:
        if re.match(r"^j(?!mp\b)[a-z]{1,3}\b", mnemonic):
            raise SystemExit(
                "FAIL: %s has a conditional branch: %s %s"
                % (TARGET, mnemonic, operands))
        if mnemonic in ("call", "jmp"):
            if operands.startswith(("eax", "ebx", "ecx", "edx", "esi", "edi",
                                    "e", "[", "*", "dword", "word")):
                raise SystemExit(
                    "FAIL: %s dispatches indirectly: %s %s"
                    % (TARGET, mnemonic, operands))
            # "call <this symbol + n>" is clang's get-EIP idiom for a
            # position-independent base register, not a dispatch. It targets an
            # address inside this very body, so it names no other symbol.
            if re.search(r"<%s(?:\+0x[0-9a-fA-F]+)?>" % re.escape(TARGET),
                         operands):
                continue
            # objdump annotates a direct call as "<address> <symbol>"; the
            # symbol is the part that carries the contract.
            named = re.search(r"<([^>+]+)", operands)
            port = named.group(1).strip() if named else operands.strip()
            if port not in ALLOWED_PORTS:
                raise SystemExit(
                    "FAIL: %s dispatches to unproven port: %s"
                    % (TARGET, port))
        for token in re.findall(r"0x[0-9a-fA-F]+", operands):
            if IMAGE_LOW <= int(token, 16) < IMAGE_HIGH:
                raise SystemExit(
                    "FAIL: %s references an absolute image address: %s %s"
                    % (TARGET, mnemonic, operands))

    returns = [(m, o) for m, o in instructions if m.startswith("ret")]
    if not returns:
        raise SystemExit("FAIL: %s has no return" % TARGET)
    for _, operands in returns:
        immediate = int(operands, 0) if operands else 0
        if immediate not in EXPECTED_CLEANUP:
            raise SystemExit(
                "FAIL: %s returns %r, expected one of %s"
                % (TARGET, operands, sorted(EXPECTED_CLEANUP)))

    calls = [(m, o) for m, o in instructions
             if m == "call" and not re.search(
                 r"<%s(?:\+0x[0-9a-fA-F]+)?>" % re.escape(TARGET), o)]
    if len(calls) != 1:
        raise SystemExit(
            "FAIL: %s makes %d calls, expected exactly 1" % (TARGET, len(calls)))

    # The receiver must be carried in ECX, which the original proves at
    # 0x004df430 ("MOV ECX,dword ptr [EBP - 0x4]") and 0x004df424 (its spill).
    if not any("ecx" in o for _, o in instructions):
        raise SystemExit("FAIL: %s never uses ECX as the receiver" % TARGET)

    # The one physical offset the body forms must be present as a displacement.
    if not any(
            re.search(r"(?:0x%x|\+%d)\b" % (RECEIVER_DISPLACEMENT,
                                            RECEIVER_DISPLACEMENT), o)
            for _, o in instructions):
        raise SystemExit(
            "FAIL: %s never forms the +0x%x receiver displacement"
            % (TARGET, RECEIVER_DISPLACEMENT))

    # Nothing may write EAX after the port returns: the original has no such
    # instruction, which is what makes the port's dword the returned value.
    last_call = max(i for i, (m, o) in enumerate(instructions)
                    if (m, o) in calls)
    for mnemonic, operands in instructions[last_call + 1:]:
        if re.match(r"^(mov|lea|pop|xor|or|and|add|sub|inc|dec|imul)\b",
                    mnemonic) and operands.split(",")[0].strip() in ("eax", "ax",
                                                                    "al"):
            raise SystemExit(
                "FAIL: %s writes the return register after the port call: "
                "%s %s" % (TARGET, mnemonic, operands))

    print("body: %d instruction(s), 1 call to %s, cleanup %s, no branch, "
          "no indirect dispatch, no absolute address, return register untouched "
          "after the call" % (len(instructions), calls[0][1],
                              sorted(EXPECTED_CLEANUP)))

print("PASS")
PY
