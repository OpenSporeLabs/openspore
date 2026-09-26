#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
work_dir=/tmp/opencode/pkg-sporepedia-safe-wave10
style='{BasedOnStyle: Google, ColumnLimit: 80, IndentWidth: 2, AccessModifierOffset: -1, DerivePointerAlignment: false, PointerAlignment: Right, AllowShortFunctionsOnASingleLine: None, SortIncludes: true, FixNamespaceComments: false}'
binaries="o0 o2 o0-ndebug o2-ndebug"
artifacts=""

trap 'rm -rf "$work_dir"' EXIT

rm -rf "$work_dir"
mkdir -p "$work_dir"

clang-format --style="$style" --dry-run -Werror \
  "$package_dir/sporepedia_safe_wave10.hpp" \
  "$package_dir/sporepedia_safe_wave10.cpp" \
  "$package_dir/sporepedia_safe_wave10_model_test.cpp"
echo "format: clean"

for config in $binaries; do
  case "$config" in
    o0) flags="-O0" ;;
    o2) flags="-O2" ;;
    o0-ndebug) flags="-O0 -DNDEBUG" ;;
    o2-ndebug) flags="-O2 -DNDEBUG" ;;
  esac
  binary="$work_dir/$config"
  clang++ -m32 -std=c++17 $flags -Wall -Wextra -Wpedantic -Werror \
    -I "$package_dir" "$package_dir/sporepedia_safe_wave10.cpp" \
    "$package_dir/sporepedia_safe_wave10_model_test.cpp" -o "$binary"
  "$binary"
  objdump -d -C --no-show-raw-insn -M intel "$binary" >"$binary.dis"
  objdump -s -j .data -j .data.rel.ro -j .rodata "$binary" >"$binary.data"
  artifacts="$artifacts $config:$binary.dis:$binary.data"
done

python3 - $artifacts <<'PY'
import re
import sys

INSN = re.compile(
    r"^[ \t]*(?P<addr>[0-9a-f]+):[ \t]+(?P<mnemonic>\S+)[ \t]*(?P<operands>.*)$",
    re.M,
)
BODY = (
    r"^[0-9a-f]+ <[^>]*%s(?!\.cold)[^>]*>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)"
)
MEMORY = re.compile(
    r"\[(?P<base>%?[a-z][a-z0-9]*)(?P<disp>[+-]0x[0-9a-f]+)?\]"
)
FRAME = ("esp", "ebp")
IMMEDIATE = re.compile(r"0x[0-9a-f]+")
DESTROY = "sporepedia_asset_destroy_00642190"
LOAD = "sporepedia_asset_load_00642230"
DEFAULT_BASE = "default_base_destroy_006412a0"
DEFAULT_RANGE = "default_global_record_range_005507a0"
VTABLE_00 = 0x00
VTABLE_10 = 0x10
VTABLE_14 = 0x14
BASE_STORE_ORDER = [VTABLE_14, VTABLE_10, VTABLE_00]
BASE_VTABLE_CONSTANTS = ("0x1403758", "0x13eb938", "0x13ec458")
DESTROY_VTABLE_WORDS = (0x013FF648, 0x01462748, 0x01462738)
RANGE_OFFSET = 0x18
ECX_TOKEN = re.compile(r"(?<![\w])ecx(?![\w])")
SPAN_GUARD_UNSIGNED = ("jbe",)
SPAN_GUARD_SIGNED = ("jle", "jg")
SPAN_BACK_EDGE_SIGNED = ("jge", "jl", "jg", "jle")
SPAN_GUARD_COUNTS = {
    "o0": {"jbe": 2, "jle": 0},
    "o2": {"jbe": 0, "jle": 0},
    "o0-ndebug": {"jbe": 2, "jle": 0},
    "o2-ndebug": {"jbe": 0, "jle": 0},
}
END_SLOT = 0x44
EPILOGUE = ("add", "pop", "lea", "mov", "ret")
CLEAR_ARGUMENT_SLOTS = (0x0, 0x4, 0x8)
CLEAR_COUNT_SLOT = 0x8
CLEAR_ZERO = "0x0"
RELEASE_SLOT = 0x04
RELEASE_FIELDS = (0x74, 0x70, 0x3C, 0x20, 0x1C)
FREE_FIELD = 0x40
FREE_MARKER_FIELD = 0x50
STATE_FIELD = 0x2C
STATE_VALUE = 0x2
APPLY_SLOT = 0xB4
GLOBAL_RECORD_STRIDE = 0x0C
KEY_ID_PRIMARY = 0x0670DA17
KEY_ID_SECONDARY = 0x03C609F8
KEY_FILL_SELECTOR = 0x1
WORD_SHIFT = 0x2


def is_padding(mnemonic, operands):
    if mnemonic.startswith(("nop", "data16", "cs")):
        return True
    if mnemonic == "int3":
        return True
    return mnemonic == "xchg" and operands.replace(" ", "") == "ax,ax"


def meaningful(rows):
    kept = list(rows)
    while kept and is_padding(*kept[-1]):
        kept.pop()
    return kept


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


def displacements(operands):
    found = set()
    for memory in MEMORY.finditer(operands):
        if memory.group("base") in FRAME:
            continue
        value = memory.group("disp")
        found.add(int(value, 16) if value else 0)
    return found


def returns(body):
    found = set()
    for mnemonic, operands in instructions(body):
        if mnemonic != "ret":
            continue
        if not IMMEDIATE.fullmatch(operands) and operands:
            raise SystemExit(f"return releases {operands}")
        found.add(int(operands, 16) if operands else 0)
    return found


def immediates(body):
    found = set()
    for _, operands in instructions(body):
        for token in re.findall(r"(?<![\w\]])(0x[0-9a-f]{1,8})\b", operands):
            found.add(int(token, 16))
    return found


WIDE = ("movsd", "movq")


def written_slots(body):
    found = []
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("mov", "movsd", "movq", "movd"):
            continue
        parts = [part.strip() for part in operands.split(",")] if operands else []
        if len(parts) != 2:
            continue
        slots = displacements(parts[0])
        if not slots:
            continue
        for slot in slots:
            found.append((slot, parts[1]))
            if mnemonic in WIDE:
                found.append((slot + 4, parts[1]))
    return found


def store_order(body, wanted):
    order = []
    for slot, source in written_slots(body):
        for expected in wanted:
            if slot == expected and expected not in order:
                order.append(expected)
    return order


def compares_field(body, field):
    for mnemonic, operands in instructions(body):
        if mnemonic not in ("cmp", "sub", "test"):
            continue
        for part in operands.split(","):
            if field in displacements(part.strip()):
                return True
    return False


DIRECT = re.compile(
    r"^(?:[0-9a-f]+ <|\S+@plt|DWORD PTR 0x[0-9a-f]+|DWORD PTR ds:0x[0-9a-f]+)$"
)


def indirect_calls(body):
    found = []
    for mnemonic, operands in instructions(body):
        if mnemonic != "call" or DIRECT.match(operands):
            continue
        found.append(operands)
    return found


REGISTER = re.compile(r"%?([a-z][a-z0-9]*)$")


def register_of(operand):
    found = REGISTER.fullmatch(operand)
    return found.group(1) if found else None


def all_displacements(body):
    found = set()
    for _, operands in instructions(body):
        found |= displacements(operands)
    return found


def rows_displacements(rows):
    found = set()
    for _, operands in rows:
        found |= displacements(operands)
    return found


def rows_returns(rows):
    found = set()
    for mnemonic, operands in rows:
        if mnemonic != "ret":
            continue
        if not IMMEDIATE.fullmatch(operands) and operands:
            raise SystemExit(f"return releases {operands}")
        found.add(int(operands, 16) if operands else 0)
    return found


def rows_stores(rows):
    found = []
    for mnemonic, operands in rows:
        if mnemonic not in ("mov", "movsd", "movq", "movd"):
            continue
        parts = [part.strip() for part in operands.split(",")] if operands else []
        if len(parts) != 2:
            continue
        slots = displacements(parts[0])
        if not slots:
            continue
        for slot in slots:
            found.append((slot, parts[1]))
            if mnemonic in WIDE:
                found.append((slot + 4, parts[1]))
    return found


def rows_store_order(rows, wanted):
    order = []
    for slot, _ in rows_stores(rows):
        for expected in wanted:
            if slot == expected and expected not in order:
                order.append(expected)
    return order


def first_store_index(body, slot):
    rows = instructions(body)
    for index, (mnemonic, operands) in enumerate(rows):
        if mnemonic not in ("mov", "movsd", "movq", "movd") or not operands:
            continue
        parts = [part.strip() for part in operands.split(",")]
        if len(parts) == 2 and slot in displacements(parts[0]):
            return index
    return None


def conditional_counts(rows):
    found = {}
    for mnemonic, _ in rows:
        if not mnemonic.startswith("j") or mnemonic == "jmp":
            continue
        found[mnemonic] = found.get(mnemonic, 0) + 1
    return found


def touches_ecx(rows):
    for _, operands in rows:
        if ECX_TOKEN.search(operands):
            return True
    return False


DATA_ROW = re.compile(
    r"^\s*(?P<address>[0-9a-f]+)\s+(?P<groups>(?:[0-9a-f]{2,8}\s+){1,4})"
    r"(?P<ascii>\S*)\s*$"
)


def section_bytes(path):
    found = {}
    for line in open(path, encoding="utf-8", errors="replace"):
        row = DATA_ROW.match(line)
        if row is None:
            continue
        address = int(row.group("address"), 16)
        for group in row.group("groups").split():
            for offset, byte in enumerate(bytes.fromhex(group)):
                found[address + offset] = byte
            address += len(bytes.fromhex(group))
    return found


def stored_word_run(found, words):
    if not found:
        return False
    pattern = b"".join(word.to_bytes(4, "little") for word in words)
    lowest = min(found)
    highest = max(found)
    start = lowest - lowest % 4
    for address in range(start, highest - len(pattern) + 1, 4):
        if address not in found:
            continue
        window = bytes(found.get(address + step, 0) for step in range(len(pattern)))
        if window == pattern:
            return True
    return False


def immediate_store_run(text, words):
    rows = instructions(text)
    for index in range(len(rows) - len(words) + 1):
        matched = True
        for position, (mnemonic, operands) in enumerate(
            rows[index:index + len(words)]
        ):
            if mnemonic not in ("mov", "movdqa") or not operands:
                matched = False
                break
            parts = [part.strip() for part in operands.split(",")]
            if len(parts) != 2 or displacements(parts[0]) != {position * 4}:
                matched = False
                break
            if not IMMEDIATE.fullmatch(parts[1]):
                matched = False
                break
            if int(parts[1], 16) != words[position]:
                matched = False
                break
        if matched:
            return True
    return False


def frame_slots(operands):
    found = set()
    for memory in MEMORY.finditer(operands):
        if memory.group("base") not in FRAME:
            continue
        value = memory.group("disp")
        offset = int(value, 16) if value else 0
        if offset >= 0:
            found.add(offset)
    return found


def argument_run(body, call_index):
    rows = instructions(body)
    found = {}
    index = call_index - 1
    while index >= 0:
        mnemonic, operands = rows[index]
        if mnemonic not in ("mov", "movd", "movq") or not operands:
            break
        parts = [part.strip() for part in operands.split(",")]
        if len(parts) != 2:
            break
        slots = frame_slots(parts[0])
        if len(slots) != 1:
            break
        found[next(iter(slots))] = parts[1]
        index -= 1
    return found


def zero_count_calls(body):
    rows = instructions(body)
    found = []
    for index, (mnemonic, operands) in enumerate(rows):
        if mnemonic != "call" or DIRECT.match(operands):
            continue
        if argument_run(body, index).get(CLEAR_COUNT_SLOT) == CLEAR_ZERO:
            found.append(index)
    return found


def dispatched_through(body, slot):
    loaded = None
    for mnemonic, operands in instructions(body):
        if mnemonic in ("mov", "movsd", "movq", "movd") and operands:
            parts = [part.strip() for part in operands.split(",")]
            if len(parts) == 2:
                destination = register_of(parts[0])
                source_slots = displacements(parts[1])
                if destination is not None and source_slots:
                    loaded = (
                        destination if slot in source_slots else None
                    )
                    continue
        if mnemonic not in ("call", "jmp"):
            continue
        if loaded is not None and register_of(operands.lstrip("*")) == loaded:
            return True
        for memory in MEMORY.finditer(operands):
            if memory.group("base") in FRAME:
                continue
            value = memory.group("disp")
            if (int(value, 16) if value else 0) == slot:
                return True
        loaded = None
    return False


for entry in sys.argv[1:]:
    config, path, data_path = entry.split(":")
    destroy = body_of(path, DESTROY)
    if returns(destroy) != {0x00}:
        raise SystemExit(
            f"{path}: {DESTROY} returns {sorted(returns(destroy))} instead of one"
            " plain return that lands after the base destroy port returns"
        )
    order = store_order(destroy, (VTABLE_00, VTABLE_10, VTABLE_14))
    if order != [VTABLE_00, VTABLE_10, VTABLE_14]:
        raise SystemExit(
            f"{path}: {DESTROY} writes vtable words in order {order} instead of"
            f" [{hex(VTABLE_00)}, {hex(VTABLE_10)}, {hex(VTABLE_14)}]"
        )
    for field in RELEASE_FIELDS:
        if field not in displacements(destroy):
            raise SystemExit(f"{path}: {DESTROY} never reaches {field:+#x}")
    if not dispatched_through(destroy, RELEASE_SLOT):
        raise SystemExit(
            f"{path}: {DESTROY} never dispatches through vtable slot"
            f" {hex(RELEASE_SLOT)}"
        )
    if FREE_FIELD not in all_displacements(destroy):
        raise SystemExit(
            f"{path}: {DESTROY} never reads the entry pointer at"
            f" {hex(FREE_FIELD)}"
        )
    if not compares_field(destroy, FREE_MARKER_FIELD):
        raise SystemExit(
            f"{path}: {DESTROY} never compares the entry pointer against the"
            f" inline marker word at {hex(FREE_MARKER_FIELD)}"
        )
    if len(indirect_calls(destroy)) < 6:
        raise SystemExit(
            f"{path}: {DESTROY} performs {len(indirect_calls(destroy))} indirect"
            " calls instead of five releases plus the free and base destroy ports"
        )
    destroy_rows = meaningful(instructions(destroy))
    if not destroy_rows:
        raise SystemExit(f"{path}: {DESTROY} body is empty")
    if destroy_rows[-1][0] != "ret":
        raise SystemExit(f"{path}: {DESTROY} ends on {destroy_rows[-1][0]}")
    transfers = [
        index
        for index, (mnemonic, _) in enumerate(destroy_rows)
        if mnemonic in ("call", "jmp")
    ]
    if not transfers:
        raise SystemExit(f"{path}: {DESTROY} never transfers to the base destroy")
    epilogue = [
        mnemonic
        for mnemonic, operands in destroy_rows[transfers[-1] + 1:]
        if not is_padding(mnemonic, operands)
    ]
    if any(mnemonic not in EPILOGUE for mnemonic in epilogue[:-1]):
        raise SystemExit(
            f"{path}: {DESTROY} keeps working after the base destroy port instead"
            f" of ending in {EPILOGUE} teardown"
        )

    base = meaningful(instructions(body_of(path, DEFAULT_BASE)))
    if not base:
        raise SystemExit(f"{path}: {DEFAULT_BASE} body is empty")
    base_returns = rows_returns(base)
    if base_returns != {0x00}:
        raise SystemExit(
            f"{path}: {DEFAULT_BASE} returns {sorted(base_returns)} instead of a"
            " single plain return"
        )
    if base[-1][0] != "ret":
        raise SystemExit(f"{path}: {DEFAULT_BASE} ends on {base[-1][0]}")
    if any(mnemonic in ("call", "ud2", "hlt") for mnemonic, _ in base):
        raise SystemExit(
            f"{path}: {DEFAULT_BASE} aborts or dispatches instead of only"
            " resetting the three base vtable words"
        )
    base_slots = rows_displacements(base)
    for slot in BASE_STORE_ORDER:
        if slot not in base_slots:
            raise SystemExit(
                f"{path}: {DEFAULT_BASE} never writes the base vtable word at"
                f" {hex(slot)}"
            )
    base_source = "\n".join(operands for _, operands in base)
    for constant in BASE_VTABLE_CONSTANTS:
        if constant not in base_source:
            raise SystemExit(
                f"{path}: {DEFAULT_BASE} never materialises {constant}"
            )
    base_order = rows_store_order(base, tuple(BASE_STORE_ORDER))
    if base_order != BASE_STORE_ORDER:
        raise SystemExit(
            f"{path}: {DEFAULT_BASE} writes the base vtable words in order"
            f" {[hex(slot) for slot in base_order]} instead of"
            f" {[hex(slot) for slot in BASE_STORE_ORDER]}"
        )

    published = section_bytes(data_path)
    if not stored_word_run(published, DESTROY_VTABLE_WORDS) and not (
        immediate_store_run(open(path, encoding="utf-8").read(), DESTROY_VTABLE_WORDS)
    ):
        raise SystemExit(
            f"{path}: no emitted run ever stores"
            f" {[hex(word) for word in DESTROY_VTABLE_WORDS]} in order, so"
            f" {DESTROY} cannot default its vtable immediates in {config}"
        )

    default_range = meaningful(instructions(body_of(path, DEFAULT_RANGE)))
    if not default_range:
        raise SystemExit(f"{path}: {DEFAULT_RANGE} body is empty")
    if rows_returns(default_range) != {0x00}:
        raise SystemExit(
            f"{path}: {DEFAULT_RANGE} returns"
            f" {sorted(rows_returns(default_range))} instead of a single plain"
            " return of the resolved range"
        )
    if default_range[-1][0] != "ret":
        raise SystemExit(
            f"{path}: {DEFAULT_RANGE} ends on {default_range[-1][0]}"
        )
    if any(mnemonic in ("call", "ud2", "hlt") for mnemonic, _ in default_range):
        raise SystemExit(
            f"{path}: {DEFAULT_RANGE} dispatches or aborts instead of resolving"
            " the range from its own primary reference"
        )
    if not touches_ecx(default_range):
        raise SystemExit(
            f"{path}: {DEFAULT_RANGE} never reads ecx, so it is not the"
            " thiscall port that takes the primary asset reference"
        )
    range_source = "\n".join(operands for _, operands in default_range)
    if f"0x{RANGE_OFFSET:x}" not in range_source:
        raise SystemExit(
            f"{path}: {DEFAULT_RANGE} never materialises the observed primary"
            f" plus {hex(RANGE_OFFSET)} range displacement"
        )

    load = body_of(path, LOAD)
    if returns(load) != {0x04}:
        raise SystemExit(
            f"{path}: {LOAD} returns {sorted(returns(load))} instead of"
            f" releasing one stack word"
        )
    load_immediates = immediates(load)
    for required in (STATE_VALUE, KEY_ID_PRIMARY, KEY_ID_SECONDARY):
        if required not in load_immediates:
            raise SystemExit(f"{path}: {LOAD} never materialises {required:#x}")
    load_slots = all_displacements(load)
    for required in (STATE_FIELD, FREE_FIELD, 0x44, 0x6C):
        if required not in load_slots:
            raise SystemExit(f"{path}: {LOAD} never reaches asset slot {required:#x}")
    if GLOBAL_RECORD_STRIDE not in load_immediates:
        raise SystemExit(
            f"{path}: {LOAD} never advances by the observed global record stride"
            f" {hex(GLOBAL_RECORD_STRIDE)}"
        )
    if KEY_FILL_SELECTOR not in load_immediates:
        raise SystemExit(f"{path}: {LOAD} never passes the key fill selector")
    if WORD_SHIFT not in load_immediates:
        raise SystemExit(f"{path}: {LOAD} never shifts the word stride by two")
    if not dispatched_through(load, APPLY_SLOT):
        raise SystemExit(
            f"{path}: {LOAD} never dispatches through the apply property slot"
            f" {hex(APPLY_SLOT)}"
        )
    if len(indirect_calls(load)) < 4:
        raise SystemExit(
            f"{path}: {LOAD} performs {len(indirect_calls(load))} indirect calls"
            " instead of resolving at least one source lookup, one apply and one"
            " release"
        )
    clear_calls = zero_count_calls(load)
    if not clear_calls:
        raise SystemExit(
            f"{path}: {LOAD} never calls a port with a zero length argument"
        )
    clear_index = clear_calls[0]
    clear_arguments = argument_run(load, clear_index)
    if tuple(sorted(clear_arguments)) != CLEAR_ARGUMENT_SLOTS:
        raise SystemExit(
            f"{path}: {LOAD} passes {len(clear_arguments)} arguments to the clear"
            f" port instead of three cdecl words at"
            f" {[hex(slot) for slot in CLEAR_ARGUMENT_SLOTS]}"
        )
    end_store = first_store_index(load, END_SLOT)
    if end_store is None:
        raise SystemExit(
            f"{path}: {LOAD} never writes the entry end word at {hex(END_SLOT)}"
        )
    if clear_index > end_store:
        raise SystemExit(
            f"{path}: {LOAD} adjusts the entry end at {hex(END_SLOT)} before"
            " calling the clear port with the unadjusted span"
        )

    load_rows = meaningful(instructions(load))
    load_conditions = conditional_counts(load_rows)
    expected_guards = SPAN_GUARD_COUNTS[config]
    for mnemonic, expected in expected_guards.items():
        found = load_conditions.get(mnemonic, 0)
        if found != expected:
            raise SystemExit(
                f"{path}: {LOAD} emits {found} {mnemonic} jumps in {config}"
                f" instead of {expected}, so the span guards are not the"
                " observed unsigned not-above tests"
            )
    for mnemonic in SPAN_GUARD_SIGNED:
        if load_conditions.get(mnemonic, 0):
            raise SystemExit(
                f"{path}: {LOAD} guards a span with the signed {mnemonic} jump"
                f" in {config} instead of the observed unsigned comparison"
            )
    if not any(
        load_conditions.get(mnemonic, 0) for mnemonic in SPAN_BACK_EDGE_SIGNED
    ):
        raise SystemExit(
            f"{path}: {LOAD} never walks a span with a signed back edge in"
            f" {config} instead of the observed signed index comparison"
        )
PY
