#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
o0_binary=/tmp/opencode/pkg-cheat-wave9-boundary-o0
o2_binary=/tmp/opencode/pkg-cheat-wave9-boundary-o2
o0_disassembly=/tmp/opencode/pkg-cheat-wave9-boundary-o0.dis
o2_disassembly=/tmp/opencode/pkg-cheat-wave9-boundary-o2.dis

trap 'rm -f "$o0_binary" "$o2_binary" "$o0_disassembly" "$o2_disassembly"' EXIT

clang++ -m32 -std=c++17 -O0 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/cheat_wave9.cpp" \
  "$package_dir/cheat_wave9_model_test.cpp" -o "$o0_binary"
clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/cheat_wave9.cpp" \
  "$package_dir/cheat_wave9_model_test.cpp" -o "$o2_binary"
objdump -dr --no-show-raw-insn -M intel "$o0_binary" >"$o0_disassembly"
objdump -dr --no-show-raw-insn -M intel "$o2_binary" >"$o2_disassembly"
python3 - "$o0_disassembly" "$o2_disassembly" <<'PY'
import re
import sys

INSN = re.compile(
    r"^\s*(?P<addr>[0-9a-f]+):\s+(?P<mnemonic>\S+)\s*(?P<operands>.*)$", re.M
)
OPERAND = re.compile(
    r"^(?:DWORD PTR )?\[(?P<base>e?[a-z]+)(?P<disp>[+-]0x[0-9a-f]+)?\]$"
)
CALLEE_STACK = ("first", "manager", "second", "third")
CALLEE_CLEAN = 0x10


def is_thunk(addr, operands):
    token = operands.split()[0] if operands else ""
    if not re.fullmatch(r"[0-9a-f]+", token):
        return False
    return int(token, 16) == int(addr, 16) + 5


class Forward:
    def __init__(self, path, body):
        self.path = path
        self.sp = 0
        self.bp = None
        self.regs = {"ecx": "manager"}
        self.mem = {4: "first", 8: "second", 12: "third"}
        self.writes = []
        self.calls = []
        self.retained = None
        self.dispatch = None
        self.ret = None
        for match in INSN.finditer(body):
            self.step(
                match.group("addr"),
                match.group("mnemonic"),
                match.group("operands").strip(),
            )

    def fail(self, reason):
        raise SystemExit(f"{self.path}: {reason}")

    def offset(self, operand):
        match = OPERAND.match(operand)
        if match is None:
            return None
        disp = int(match.group("disp"), 16) if match.group("disp") else 0
        if match.group("base") == "esp":
            return self.sp + disp
        if match.group("base") == "ebp":
            return None if self.bp is None else self.bp + disp
        return None

    def read(self, operand):
        target = self.offset(operand)
        if target is not None:
            return self.mem.get(target)
        return self.regs.get(operand)

    def write(self, target, value):
        if target is None:
            return
        self.mem[target] = value
        self.writes.append((target, value, len(self.calls)))

    def step(self, addr, mnemonic, operands):
        parts = [part.strip() for part in operands.split(",")] if operands else []
        if mnemonic == "push" and parts:
            self.write(self.sp - 4, self.read(parts[0]))
            self.sp -= 4
        elif mnemonic == "pop" and parts:
            self.regs[parts[0]] = self.mem.get(self.sp)
            self.sp += 4
        elif mnemonic == "mov" and len(parts) == 2:
            if parts == ["esp", "ebp"]:
                self.sp = self.bp
            elif parts == ["ebp", "esp"]:
                self.bp = self.sp
            elif OPERAND.match(parts[0]) is not None:
                self.write(self.offset(parts[0]), self.read(parts[1]))
            else:
                self.regs[parts[0]] = self.read(parts[1])
        elif (
            mnemonic in ("add", "sub")
            and len(parts) == 2
            and parts[0] == "esp"
        ):
            delta = int(parts[1], 16)
            self.sp += delta if mnemonic == "add" else -delta
        elif mnemonic == "call":
            self.call(addr, operands)
        elif mnemonic == "ret":
            self.ret = (self.sp, operands)
            self.sp += 4 + (int(operands, 16) if operands else 0)

    def call(self, addr, operands):
        if is_thunk(addr, operands):
            self.sp -= 4
            return
        self.calls.append(addr)
        if len(self.calls) == 1:
            self.retained = set(self.regs.values()) | set(self.mem.values())
            self.regs["eax"] = "service"
            return
        self.dispatch = (
            self.sp,
            self.regs.get("ecx"),
            [self.mem.get(self.sp + 4 * slot) for slot in range(4)],
        )
        self.sp += CALLEE_CLEAN

    def slots(self, phase, low, high):
        return sorted(target for target, _, stage in self.writes
                      if stage == phase and low <= target < high)

    def verify(self):
        if self.ret is None or self.ret[1] != "0xc":
            self.fail("forward does not release three stack words")
        if self.sp != 16:
            self.fail("forward leaves the caller stack unbalanced")
        if self.ret[0] != 0:
            self.fail("forward does not restore the incoming frame")
        if len(self.calls) != 2:
            self.fail(
                f"expected one receiver fetch and one dispatch, got"
                f" {len(self.calls)}"
            )
        if "manager" not in self.retained:
            self.fail("incoming manager receiver is not retained across the fetch")
        if self.dispatch[1] != "service":
            self.fail("fetched receiver is not loaded into ECX")
        if tuple(self.dispatch[2]) != CALLEE_STACK:
            self.fail(
                f"dispatch stack is {self.dispatch[2]} instead of"
                f" {list(CALLEE_STACK)}"
            )
        staged = self.slots(1, self.dispatch[0], self.dispatch[0] + 0x10)
        if staged != [self.dispatch[0] + 4 * slot for slot in range(4)]:
            self.fail(
                f"dispatch stages {len(staged)} argument words into"
                f" {len(set(staged))} slots instead of four"
            )


for path in sys.argv[1:]:
    selector = re.search(
        r"<opaque_service_forward_00abf790>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
        open(path, encoding="utf-8").read(),
        re.S,
    )
    if selector is None:
        raise SystemExit(f"{path}: forward symbol missing")
    Forward(path, selector.group("body")).verify()
PY
"$o0_binary"
"$o2_binary"
