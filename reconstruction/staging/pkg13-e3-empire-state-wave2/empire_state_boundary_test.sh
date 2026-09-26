#!/bin/sh
set -eu

package_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
o0_binary=/tmp/opencode/pkg13-e3-empire-state-wave2-boundary-o0
o2_binary=/tmp/opencode/pkg13-e3-empire-state-wave2-boundary-o2
o0_disassembly=/tmp/opencode/pkg13-e3-empire-state-wave2-boundary-o0.dis
o2_disassembly=/tmp/opencode/pkg13-e3-empire-state-wave2-boundary-o2.dis

trap 'rm -f "$o0_binary" "$o2_binary" "$o0_disassembly" "$o2_disassembly"' EXIT

clang++ -m32 -std=c++17 -O0 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/empire_state_wave2.cpp" \
  "$package_dir/empire_state_boundary.S" \
  "$package_dir/empire_state_wave2_model_test.cpp" -o "$o0_binary"
clang++ -m32 -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror \
  -I "$package_dir" "$package_dir/empire_state_wave2.cpp" \
  "$package_dir/empire_state_boundary.S" \
  "$package_dir/empire_state_wave2_model_test.cpp" -o "$o2_binary"
objdump -dr "$o0_binary" >"$o0_disassembly"
objdump -dr "$o2_binary" >"$o2_disassembly"
python3 - "$o0_disassembly" "$o2_disassembly" <<'PY'
import re
import sys

for path in sys.argv[1:]:
    text = open(path, encoding="utf-8").read()
    selector = re.search(
        r"<SpeciesProfileSelector_00c30cc0>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
        text,
        re.S,
    )
    standalone = re.search(
        r"<ArchetypeRelationshipsID_00c30e20>:\n(?P<body>.*?)(?=\n[0-9a-f]+ <|\Z)",
        text,
        re.S,
    )
    if selector is None:
        raise SystemExit("selector symbol missing")
    if standalone is None:
        raise SystemExit("standalone symbol missing")
    if re.search(
        r"mov\s+\$\s*0x4e5855b9\s*,\s*%eax",
        selector.group("body"),
    ) is None:
        raise SystemExit("selector does not initialize default EAX")
    if re.search(
        r"call.*<ArchetypeRelationshipsID_00c30e20(?:@plt)?>",
        selector.group("body"),
    ) is None:
        raise SystemExit("selector does not call standalone boundary")
    if re.search(r"\bcall\b", selector.group("body")) is None:
        raise SystemExit("selector has no call instruction")
    if "mov" not in standalone.group("body"):
        raise SystemExit("standalone body is not an independent function")
PY
"$o0_binary"
"$o2_binary"
