#!/usr/bin/env python3
"""Print per-package type histogram with decoded names from the 0x1C7AC81 prop map
and the canonical types/typenames.json (when present)."""
import sys
import os
import json
import re

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'dbpf'))
from dbpf import read, getdata

_HERE = os.path.dirname(os.path.abspath(__file__))
_CANON = {}
_nf = os.path.join(_HERE, 'types', 'typenames.json')
if os.path.exists(_nf):
    _CANON = {int(k): v for k, v in json.load(open(_nf)).items()}


def decode(data, items):
    from collections import Counter
    c = Counter(it['type'] for it in items)
    names = dict(_CANON)
    blob = b''
    for it in items:
        if it['group'] == 0x1C7AC81 and it['inst'] == 0x1C7AC81:
            blob = getdata(data, it)
            break
    if blob:
        text = ''.join(ch for ch in blob.decode('latin1', 'replace') if ch.isprintable() or ch == ' ')
        for m in re.finditer(r'0x([0-9a-f]{8})([A-Za-z0-9_]+?)(?=0x|$)', text):
            names[int(m.group(1), 16)] = m.group(2)
    print(f"{'count':>7}  typeID      name")
    for t, n in c.most_common(60):
        print(f"{n:7d}  0x{t:08x}  {names.get(t, '?')}")


for pkg in sys.argv[1:]:
    print(f"### {pkg}")
    data, items = read(pkg)
    decode(data, items)
