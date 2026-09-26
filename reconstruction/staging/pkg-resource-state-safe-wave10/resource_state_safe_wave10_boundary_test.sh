#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-resource-state-safe-wave10
binaries="o0 o2 o0-ndebug o2-ndebug"
disassembly=""

trap 'rm -rf "$work_dir"' EXIT

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
    -I "$package_dir" "$package_dir/resource_state_safe_wave10.cpp" \
    "$package_dir/resource_state_safe_wave10_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  disassembly="$disassembly $binary.dis"
done

python3 - $disassembly <<'PY'
import re
import sys

INSN = re.compile(
    r"^\s*(?P<addr>[0-9a-f]+):\s+(?P<mnemonic>\S+)\s*(?P<operands>.*)$", re.M
)
BODY = (
    r"^[0-9a-f]+ <[^>]*%s[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
)
MEMORY = re.compile(
    r"(?:(?P<width>BYTE|WORD|DWORD) PTR )?"
    r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]"
)
DIRECT = re.compile(r"^(?:[0-9a-f]+ <|[0-9a-f]+$|\S+@plt)")
SELF = re.compile(r"\+0x[0-9a-f]+>$")
INDIRECT = re.compile(r"^(?:DWORD PTR )?(?:\[|[a-z][a-z0-9]*$)")
BRANCH = re.compile(r"^j(?!mp$)[a-z]+$")
ENTRY = "record_write_get_state_00e310c0"
RELEASE_MASK = 0x01
FRAME = ("esp", "ebp")
CALLEE_CLOBBER = ("eax", "ecx", "edx")
TRACKED = ("eax", "ebx", "ecx", "edx", "esi", "edi")


def require(condition, message):
    if not condition:
        raise SystemExit(message)


def body_of(path, name):
    selector = re.compile(BODY % re.escape(name), re.S | re.M).search(
        open(path, encoding="utf-8").read()
    )
    if selector is None:
        raise SystemExit(f"{path}: {name} symbol missing")
    return selector.group("body")


def instructions(body):
    return [
        (found.group("mnemonic"), found.group("operands").strip())
        for found in INSN.finditer(body)
    ]


def split_operands(operands):
    return [part.strip() for part in operands.split(",")] if operands else []


def memory_slots(operands):
    return [
        (
            found.group("base"),
            int(found.group("disp"), 16) if found.group("disp") else 0,
            found.group("width"),
        )
        for found in MEMORY.finditer(operands)
    ]


def strip_prefix(token):
    for prefix in ("DWORD PTR ", "WORD PTR ", "BYTE PTR "):
        if token.startswith(prefix):
            return token[len(prefix) :]
    return token


def is_self_transfer(operands):
    return bool(SELF.search(operands))


def check_returns(steps, path):
    found = set()
    for mnemonic, operands in steps:
        if mnemonic != "ret":
            continue
        require(
            re.fullmatch(r"0x[0-9a-f]+", operands),
            f"{path}: entry releases {operands or 'nothing'} instead of a callee"
            " cleaned stack word",
        )
        found.add(int(operands, 16))
    require(
        found == {0x04},
        f"{path}: entry releases {sorted(found)} instead of exactly one callee"
        " cleaned stack word",
    )
    require(
        len([mnemonic for mnemonic, _ in steps if mnemonic == "ret"]) == 1,
        f"{path}: entry does not end on a single return",
    )


def check_dispatches(steps, path):
    indirect = [
        index
        for index, (mnemonic, operands) in enumerate(steps)
        if mnemonic in ("call", "jmp")
        and not DIRECT.match(operands)
        and INDIRECT.match(operands)
    ]
    direct = [
        (mnemonic, operands)
        for mnemonic, operands in steps
        if mnemonic in ("call", "jmp")
        and DIRECT.match(operands)
        and not is_self_transfer(operands)
    ]
    require(
        not direct,
        f"{path}: entry performs the direct transfer {direct} where a port dispatch"
        " is required",
    )
    require(
        len(indirect) == 2,
        f"{path}: entry performs {len(indirect)} port dispatches instead of two",
    )
    return indirect


def check_port_record(steps, indirect, path):
    foreign = []
    for index, (mnemonic, operands) in enumerate(steps):
        for base, slot, _ in memory_slots(operands):
            if base not in FRAME:
                foreign.append((index, base, slot))
    require(foreign, f"{path}: entry never reaches a dependency port slot")
    bases = {base for _, base, _ in foreign}
    require(
        len(bases) == 1,
        f"{path}: entry reaches non frame memory through {sorted(bases)} instead of a"
        " single dependency port record",
    )
    base = bases.pop()
    slots = {slot for _, record_base, slot in foreign if record_base == base}
    require(
        len(slots) == 2,
        f"{path}: entry reaches {len(slots)} port slots {sorted(slots)} instead of two",
    )
    require(
        len(foreign) == 2,
        f"{path}: entry reads the port record {len(foreign)} times instead of once per"
        f" dispatch through {sorted(slots)}",
    )
    reads = sorted(index for index, _, _ in foreign)
    require(
        reads[0] <= indirect[0] and reads[1] <= indirect[1],
        f"{path}: entry dispatches through a port slot it never read",
    )
    require(
        reads[0] <= indirect[0] < indirect[1] and reads[1] <= indirect[1],
        f"{path}: entry does not read each port slot before its own dispatch",
    )
    return base, slots


def check_flag_read(steps, path):
    byte_reads = [
        (mnemonic, operands)
        for mnemonic, operands in steps
        if mnemonic in ("mov", "movzx", "test", "cmp", "and")
        for read_base, _, width in memory_slots(operands)
        if width == "BYTE" and read_base in FRAME
    ]
    require(
        byte_reads,
        f"{path}: entry never reads the release flag one byte at a time",
    )
    narrowed = [
        operands
        for mnemonic, operands in steps
        if mnemonic in ("test", "and") and re.search(r",\s*0x0?1$", operands)
    ]
    require(
        len(narrowed) == 1,
        f"{path}: entry narrows the release flag with {RELEASE_MASK:#x} in"
        f" {len(narrowed)} places instead of exactly one",
    )


def check_release_branch(steps, indirect, path):
    branches = [
        (index, operands)
        for index, (mnemonic, operands) in enumerate(steps)
        if BRANCH.match(mnemonic)
    ]
    require(
        len(branches) == 1,
        f"{path}: entry gates its release dispatch with {branches} instead of a single"
        " forward conditional branch",
    )
    index = branches[0][0]
    require(
        indirect[0] < index < indirect[1],
        f"{path}: entry does not read the release flag between its destroy and release"
        " dispatches",
    )


def read_origin(source, origin, slot_origin, port_base, port_slots):
    memory = memory_slots(source)
    if memory:
        base, slot, _ = memory[0]
        if base == port_base:
            return f"port:{slot:#04x}" if slot in port_slots else None
        return slot_origin.get((base, slot))
    plain = strip_prefix(source)
    if plain in origin:
        return origin[plain]
    return None


def check_return_origin(steps, port_base, port_slots, path):
    origin = {"ecx": "receiver"}
    slot_origin = {}
    for mnemonic, operands in steps:
        parts = split_operands(operands)
        if mnemonic == "mov" and len(parts) == 2:
            target, source = parts
            value = read_origin(source, origin, slot_origin, port_base, port_slots)
            memory = memory_slots(target)
            if memory and memory[0][0] in FRAME:
                slot_origin[(memory[0][0], memory[0][1])] = value
            elif target in TRACKED:
                origin[target] = value
        elif mnemonic in ("call", "jmp"):
            if not DIRECT.match(operands) and INDIRECT.match(operands):
                for register in CALLEE_CLOBBER:
                    origin[register] = None
        elif mnemonic == "pop" and parts and parts[0] in TRACKED:
            origin[parts[0]] = None
    require(
        origin.get("eax") == "receiver",
        f"{path}: entry returns {origin.get('eax')} in eax instead of its incoming"
        " receiver",
    )


for path in sys.argv[1:]:
    body = body_of(path, ENTRY)
    steps = instructions(body)
    require(bool(steps), f"{path}: entry body is empty")
    check_returns(steps, path)
    indirect = check_dispatches(steps, path)
    port_base, port_slots = check_port_record(steps, indirect, path)
    check_flag_read(steps, path)
    check_release_branch(steps, indirect, path)
    check_return_origin(steps, port_base, port_slots, path)
PY
