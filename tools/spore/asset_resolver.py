#!/usr/bin/env python3
"""Spore DBPF asset resolver.

Maps every record in a .package to (type_id, type_name, group_id, group_name,
instance_id, size) using canonical type names from types/typenames.json and
SDK group names from types/groupnames.json.

Usage:
  asset_resolver.py <file> [--type 0x...] [--group 0x...] [--record T:G:I]
                     [--near G:I N] [--typeinfo] [--map] [--json]
"""
import argparse
import json
import os
import struct
import sys
from collections import Counter

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), 'dbpf'))
from dbpf import read  # noqa: E402

_HERE = os.path.dirname(os.path.abspath(__file__))
_TYPE_F = os.path.join(_HERE, 'types', 'typenames.json')
_GROUP_F = os.path.join(_HERE, 'types', 'groupnames.json')

TYPES: dict[int, str] = {}
GROUPS: dict[int, str] = {}


def _load_maps():
    global TYPES, GROUPS
    if os.path.exists(_TYPE_F):
        with open(_TYPE_F) as f:
            raw = json.load(f)
        TYPES = {int(k): v for k, v in raw.items()}
    if os.path.exists(_GROUP_F):
        with open(_GROUP_F) as f:
            raw = json.load(f)
        GROUPS = {int(k): v for k, v in raw.items()}


def type4cc(t: int) -> str:
    return struct.pack('<I', t).decode('latin1', 'replace')


def type_name(t: int) -> str:
    if t in TYPES:
        return TYPES[t]
    return type4cc(t).replace('\x00', '_') or f"0x{t:08x}"


def group_name(g: int) -> str:
    if g in GROUPS:
        return GROUPS[g]
    return ''


def stage_byte(g: int) -> int:
    return (g >> 8) & 0xFF


def category_byte(g: int) -> int:
    return (g >> 16) & 0xFF


def fmt_rec(idx: int, rec: dict) -> str:
    t, g, i = rec['type'], rec['group'], rec['inst']
    tn = type_name(t)
    gn = group_name(g)
    label = f" {gn}" if gn else ''
    return (f"  {idx:6d}  {type4cc(t):4s} 0x{t:08x} {tn:<20s}"
            f"g=0x{g:08x} {label:<16s} i=0x{i:08x}"
            f" size={rec['msize']:<8d} off=0x{rec['off']:08x}")


def cmd_typeinfo(items: list[dict]) -> None:
    c = Counter(it['type'] for it in items)
    print(f"{'count':>7}  typeID      4CC    name")
    for t, n in c.most_common(100):
        print(f"{n:7d}  0x{t:08x}  {type4cc(t):4s}  {type_name(t)}")


def cmd_map() -> None:
    print("Type names:")
    for t in sorted(TYPES):
        print(f"  0x{t:08x}  {type4cc(t):4s}  {TYPES[t]}")
    print("Group names:")
    for g in sorted(GROUPS):
        print(f"  0x{g:08x}  {GROUPS[g]}")


def cmd_type(items: list[dict], type_id: int) -> None:
    matches = [(i, rec) for i, rec in enumerate(items) if rec['type'] == type_id]
    print(f"Type 0x{type_id:08x} ({type_name(type_id)}): {len(matches)} records")
    for idx, rec in matches:
        print(fmt_rec(idx, rec))


def cmd_group(items: list[dict], group_id: int) -> None:
    matches = [(i, rec) for i, rec in enumerate(items) if rec['group'] == group_id]
    gn = group_name(group_id)
    label = f" ({gn})" if gn else ''
    print(f"Group 0x{group_id:08x}{label}: {len(matches)} records")
    for idx, rec in matches:
        print(fmt_rec(idx, rec))


def cmd_record(items: list[dict], type_id: int, group_id: int, inst_id: int) -> None:
    for i, rec in enumerate(items):
        if rec['type'] == type_id and rec['group'] == group_id and rec['inst'] == inst_id:
            print(fmt_rec(i, rec))
            print(f"  stage=0x{stage_byte(group_id):02x} category=0x{category_byte(group_id):02x}")
            return
    print(f"Record 0x{type_id:08x}:0x{group_id:08x}:0x{inst_id:08x} not found")


def cmd_near(items: list[dict], group_id: int, inst_id: int, count: int) -> None:
    """Find records with the same group and nearby instance IDs."""
    same_group = [(i, rec) for i, rec in enumerate(items) if rec['group'] == group_id]
    same_group.sort(key=lambda x: abs(x[1]['inst'] - inst_id))
    print(f"Records near 0x{group_id:08x}:0x{inst_id:08x} (same group, {count} closest):")
    for idx, rec in same_group[:count]:
        print(fmt_rec(idx, rec))
    # Also find records with nearby group IDs (same type as any in this group)
    types_in_group = set(rec['type'] for _, rec in same_group)
    if types_in_group:
        t = next(iter(types_in_group))
        near_group = [(i, rec) for i, rec in enumerate(items)
                      if rec['type'] == t and rec['group'] != group_id
                      and abs(rec['group'] - group_id) <= 0x10000]
        near_group.sort(key=lambda x: abs(x[1]['group'] - group_id))
        if near_group:
            print(f"\nSame type 0x{t:08x}, nearby groups (within 0x10000):")
            for idx, rec in near_group[:count]:
                print(fmt_rec(idx, rec))


def main(argv=None) -> int:
    _load_maps()
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('file', help='path to a .package file')
    ap.add_argument('--type', dest='type_id', type=lambda s: int(s, 0), help='filter by type ID (hex)')
    ap.add_argument('--group', dest='group_id', type=lambda s: int(s, 0), help='filter by group ID (hex)')
    ap.add_argument('--record', type=lambda s: tuple(int(x, 0) for x in s.split(':')),
                    metavar='T:G:I', help='look up specific record T:G:I (all hex)')
    ap.add_argument('--near', nargs=2, type=lambda s: int(s, 0), metavar=('GROUP', 'INST'),
                    help='find records near GROUP:INST')
    ap.add_argument('--near-count', type=int, default=20, help='max results for --near')
    ap.add_argument('--typeinfo', action='store_true', help='show type histogram')
    ap.add_argument('--map', action='store_true', help='dump type+group name maps')
    ap.add_argument('--json', action='store_true', help='output as JSON')
    a = ap.parse_args(argv)

    data, items = read(a.file)

    if a.map:
        cmd_map()
        return 0

    if a.typeinfo:
        if a.json:
            c = Counter(it['type'] for it in items)
            print(json.dumps({f"0x{t:08x}": {'name': type_name(t), 'count': n}
                              for t, n in c.most_common(100)}, indent=2))
        else:
            cmd_typeinfo(items)
        return 0

    if a.record:
        t, g, i = a.record
        if a.json:
            for idx, rec in enumerate(items):
                if rec['type'] == t and rec['group'] == g and rec['inst'] == i:
                    print(json.dumps({
                        'index': idx, 'type': f"0x{t:08x}", 'type_name': type_name(t),
                        'group': f"0x{g:08x}", 'group_name': group_name(g),
                        'instance': f"0x{i:08x}", 'size': rec['msize'],
                        'offset': f"0x{rec['off']:08x}", 'compressed': rec['comp'],
                        'stage': f"0x{stage_byte(g):02x}", 'category': f"0x{category_byte(g):02x}",
                    }, indent=2))
                    return 0
            print(json.dumps({'error': 'not found'}))
            return 1
        cmd_record(items, t, g, i)
        return 0

    if a.near:
        g, i = a.near
        cmd_near(items, g, i, a.near_count)
        return 0

    if a.type_id is not None:
        if a.json:
            rows = []
            for idx, rec in enumerate(items):
                if rec['type'] == a.type_id:
                    rows.append({'index': idx, 'group': f"0x{rec['group']:08x}",
                                 'group_name': group_name(rec['group']),
                                 'instance': f"0x{rec['inst']:08x}", 'size': rec['msize']})
            print(json.dumps(rows, indent=2))
        else:
            cmd_type(items, a.type_id)
        return 0

    if a.group_id is not None:
        if a.json:
            rows = []
            for idx, rec in enumerate(items):
                if rec['group'] == a.group_id:
                    rows.append({'index': idx, 'type': f"0x{rec['type']:08x}",
                                 'type_name': type_name(rec['type']),
                                 'instance': f"0x{rec['inst']:08x}", 'size': rec['msize']})
            print(json.dumps(rows, indent=2))
        else:
            cmd_group(items, a.group_id)
        return 0

    # Default: show summary
    print(f"{os.path.basename(a.file)}: {len(items)} records")
    cmd_typeinfo(items)
    return 0


if __name__ == '__main__':
    sys.exit(main())
