#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
o0_binary=/tmp/opencode/pkg13-e4-empire-wave3-boundary-o0
o2_binary=/tmp/opencode/pkg13-e4-empire-wave3-boundary-o2
ndebug_binary=/tmp/opencode/pkg13-e4-empire-wave3-boundary-ndebug
o0_disassembly=/tmp/opencode/pkg13-e4-empire-wave3-boundary-o0.dis
o2_disassembly=/tmp/opencode/pkg13-e4-empire-wave3-boundary-o2.dis

trap 'rm -f "$o0_binary" "$o2_binary" "$ndebug_binary" "$o0_disassembly" "$o2_disassembly"' EXIT

clang++ -m32 -std=c++17 -O0 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/empire_wave3.cpp" \
  "$package_dir/empire_wave3_model_test.cpp" -o "$o0_binary"
clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/empire_wave3.cpp" \
  "$package_dir/empire_wave3_model_test.cpp" -o "$o2_binary"
clang++ -m32 -std=c++17 -O2 -DNDEBUG -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/empire_wave3.cpp" \
  "$package_dir/empire_wave3_model_test.cpp" -o "$ndebug_binary"
objdump -dr "$o0_binary" >"$o0_disassembly"
objdump -dr "$o2_binary" >"$o2_disassembly"
python3 - "$o0_disassembly" "$o2_disassembly" <<'PY'
import re
import sys

for path in sys.argv[1:]:
    text = open(path, encoding="utf-8").read()
    color = re.search(
        r"<EmpirePoliticalColor_00c32cd0>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
        text,
        re.S,
    )
    ownership = re.search(
        r"<PoliticalOwnershipScan_00c8d060>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
        text,
        re.S,
    )
    if color is None or ownership is None:
        raise SystemExit("target symbol missing")
    if re.search(r"ret[l]?\s+\$0x4", color.group("body")) is None:
        raise SystemExit("color target does not clean one stack word")
    if re.search(r"ret[l]?\s+\$0x4", ownership.group("body")) is not None:
        raise SystemExit("ownership target unexpectedly cleans a stack word")
    if re.search(r"ret[l]?\s*$", ownership.group("body"), re.M) is None:
        raise SystemExit("ownership target has no plain return")
PY
"$o0_binary"
"$o2_binary"
"$ndebug_binary"
