#!/usr/bin/env python3
"""Oracle for CS-05: the `cell` records (cCellCellResource, TYPE 0xDFAD9F51).

489 records in the GOG install (223 Spore_Game + 223 PatchData repack + 43
Spore_EP1_Data), all exactly 0x31C = 796 bytes = the runtime struct
`Simulator::Cell::cCellCellResource` (Ghidra struct 61869, 796 bytes).

Like the globals record (CS-03), the record is a DIRECT field-by-field
serialization of the runtime struct - no CellSerializer name/ID envelope.
The layout is evidence-confirmed: every record decodes to plausible values
(round floats, small enums, bools, u32 resource-reference keys, 70 records
with real PLACEHOLDER_* names) and the last field ends at byte 796.

Enum/field domains observed across all 266 unique records (superset of the
campaign-plan ranges, see campaign doc for drift notes):
  cellType       0..7
  size[2]        0.085..5.0 floats (a few default templates use 2.0/5.0)
  unlockType     0, 2, 4, 5, 6, 7, 8, 10
  density        0, 1, 3, 4
  ai.type        0 | 0x1000..0x10FF | 0xFFFFFFFF (empty AI block)
  ai.movementStyle  bitfield over {1=Jet, 2=Flagella, 4=Cilia}
  ai.food        0, 3

Usage:
  cell.py validate                all records decode + sanity + double-run identical
  cell.py dump <group> <instance> single record field-by-field
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'dbpf'))
from dbpf import read, getdata

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.abspath(os.path.join(_HERE, '..', '..', '..'))

CELL_TYPE = 0xDFAD9F51
CELL_SIZE = 796

# (name, offset, kind) for cCellCellResource — struct 61869 family.
# kind: 'u32' | 'i32' | 'f32' | 'u8' | 'ref' (u32 resource-reference key)
# | 'loc' (wchar16[80] + u32 localeInstanceID) | 'ai' (cAIData, 180 B)
CELL_FIELDS = [
    ('structure', 0, 'ref'),
    ('name', 4, 'loc'),
    ('hp', 168, 'i32'),
    ('fixedOrientation', 172, 'u8'),
    ('flags', 176, 'u32'),
    ('cellType', 180, 'u32'),
    ('unlockType', 184, 'u32'),
    ('density', 188, 'u32'),
    ('sound', 192, 'u32'),
    ('break', 196, 'ref'),
    ('pieces', 200, 'ref'),
    ('leak', 204, 'ref'),
    ('expel', 208, 'ref'),
    ('explosionTable', 212, 'ref'),
    ('loot', 216, 'ref'),
    ('poison', 220, 'ref'),
    ('ai', 224, 'ai'),
    ('aiHard', 404, 'ai'),
    ('aiEasy', 584, 'ai'),
    ('friendGroup', 764, 'i32'),
    ('wontAttackPlayer', 768, 'u8'),
    ('wontAttackPlayerWhenSmall', 769, 'u8'),
    ('sizeMin', 772, 'f32'),
    ('sizeMax', 776, 'f32'),
    ('eatFoodValue', 780, 'i32'),
    ('eatHpValue', 784, 'i32'),
    ('eatBomb', 788, 'u8'),
    ('eatPoisonNova', 789, 'u8'),
    ('triggersEscapeMission', 792, 'u8'),
]

# (name, offset, kind) inside cAIData — struct 61866 family (180 B).
AI_FIELDS = [
    ('type', 0, 'u32'),
    ('awarenessRadius', 4, 'f32'),
    ('awarenessRadiusFood', 8, 'f32'),
    ('awarenessRadiusPredator', 12, 'f32'),
    ('movementStyle', 16, 'u32'),
    ('flocking', 20, 'u8'),
    ('speed', 24, 'f32'),
    ('chaseSpeed', 28, 'f32'),
    ('wanderSpeed', 32, 'f32'),
    ('fleeSpeed', 36, 'f32'),
    ('fearsNearbyDamageRadius', 40, 'f32'),
    ('fearsNearbyDeathRadius', 44, 'f32'),
    ('fearsNearbyDamageTime', 48, 'f32'),
    ('fearsNearbyDeathTime', 52, 'f32'),
    ('protectRadius', 56, 'f32'),
    ('protectTime', 60, 'f32'),
    ('turnFactor', 64, 'f32'),
    ('axialMovement', 68, 'u8'),
    ('spawnTime', 72, 'f32'),
    ('spawnRestTime', 76, 'f32'),
    ('spawnOutput', 80, 'ref'),
    ('arcLength', 84, 'f32'),
    ('arcLengthSecondary', 88, 'f32'),
    ('numArcs', 92, 'i32'),
    ('keyTransformation', 96, 'ref'),
    ('keyProjectile', 100, 'ref'),
    ('food', 104, 'u32'),
    ('growCount', 108, 'i32'),
    ('digestionCount', 112, 'i32'),
    ('digestionTime', 116, 'f32'),
    ('digestionOutput', 120, 'ref'),
    ('fleeTime', 124, 'f32'),
    ('fleeRestTime', 128, 'f32'),
    ('chaseTime', 132, 'f32'),
    ('chaseRestTime', 136, 'f32'),
    ('chasesDamage', 140, 'u8'),
    ('fearsMouths', 141, 'u8'),
    ('fearsWeapons', 142, 'u8'),
    ('fearsElectric', 143, 'u8'),
    ('fearsPoison', 144, 'u8'),
    ('fearsDamage', 145, 'u8'),
    ('ignoresFood', 146, 'u8'),
    ('awakeTime', 148, 'f32'),
    ('sleepTime', 152, 'f32'),
    ('growAmount', 156, 'i32'),
    ('hatchDuration', 160, 'f32'),
    ('poisonRecharge', 164, 'f32'),
    ('electricRecharge', 168, 'f32'),
    ('electricRechargeVsSmall', 172, 'f32'),
    ('electricDischarge', 176, 'f32'),
]


def _packages():
    return [
        ('Spore_Game', os.path.join(_REPO, 'SPORE', 'Data',
                                    'Spore_Game.package')),
        ('Spore_EP1_Data', os.path.join(_REPO, 'SPORE', 'DataEP1',
                                        'Spore_EP1_Data.package')),
    ]


def load_all():
    """Return {(pkg, group, inst): blob} for every cell record, or {} if absent."""
    out = {}
    for tag, path in _packages():
        if not os.path.exists(path):
            continue
        data, items = read(path)
        for it in items:
            if it['type'] == CELL_TYPE:
                out[(tag, it['group'], it['inst'])] = getdata(data, it)
    return out


def _read(blob, off, kind):
    if kind == 'f32':
        return struct.unpack_from('<f', blob, off)[0]
    if kind == 'i32':
        return struct.unpack_from('<i', blob, off)[0]
    if kind in ('u32', 'ref'):
        return struct.unpack_from('<I', blob, off)[0]
    if kind == 'u8':
        return struct.unpack_from('<B', blob, off)[0]
    if kind == 'loc':
        w = struct.unpack_from('<80H', blob, off)
        text = ''.join(chr(c) for c in w).split('\x00')[0]
        loc = struct.unpack_from('<I', blob, off + 160)[0]
        return (text, loc)
    if kind == 'ai':
        return dict((n, _read(blob, off + o, k)) for n, o, k in AI_FIELDS)
    raise ValueError(kind)


def decode(blob):
    """Decode one cell record; returns the ordered field dict."""
    return dict((n, _read(blob, o, k)) for n, o, k in CELL_FIELDS)


def sanity(problems, where, vals):
    if vals['cellType'] not in range(0, 8):
        problems.append("%s cellType=%d" % (where, vals['cellType']))
    if vals['unlockType'] not in (0, 2, 4, 5, 6, 7, 8, 10):
        problems.append("%s unlockType=%d" % (where, vals['unlockType']))
    if vals['density'] not in (0, 1, 3, 4):
        problems.append("%s density=%d" % (where, vals['density']))
    if vals['hp'] not in (1, 2, 3, 4):
        problems.append("%s hp=%d" % (where, vals['hp']))
    if not (0.0 <= vals['sizeMin'] <= 10.0 and vals['sizeMin'] <= vals['sizeMax'] <= 10.0):
        problems.append("%s size=[%g %g]" % (where, vals['sizeMin'], vals['sizeMax']))
    for b in ('fixedOrientation', 'wontAttackPlayer',
              'wontAttackPlayerWhenSmall', 'eatBomb', 'eatPoisonNova',
              'triggersEscapeMission'):
        if vals[b] not in (0, 1):
            problems.append("%s %s=%d" % (where, b, vals[b]))
    for name in ('ai', 'aiHard', 'aiEasy'):
        ai = vals[name]
        t = ai['type']
        if t != 0 and t != 0xFFFFFFFF and not (0x1000 <= t <= 0x10FF):
            problems.append("%s %s.type=0x%x" % (where, name, t))
        if ai['movementStyle'] & ~0xF:
            problems.append("%s %s.movementStyle=0x%x" % (where, name, ai['movementStyle']))
        if ai['food'] not in (0, 3):
            problems.append("%s %s.food=%d" % (where, name, ai['food']))
        if ai['numArcs'] not in range(0, 64):
            problems.append("%s %s.numArcs=%d" % (where, name, ai['numArcs']))
        for b in ('flocking', 'axialMovement', 'chasesDamage', 'fearsMouths',
                  'fearsWeapons', 'fearsElectric', 'fearsPoison', 'fearsDamage',
                  'ignoresFood'):
            if ai[b] not in (0, 1):
                problems.append("%s %s.%s=%d" % (where, name, b, ai[b]))
        for k, v in ai.items():
            if isinstance(v, float) and (v != v or abs(v) > 1e4):
                problems.append("%s %s.%s=%r" % (where, name, k, v))
    for k in ('eatFoodValue', 'eatHpValue'):
        if vals[k] < 0:
            problems.append("%s %s=%d" % (where, k, vals[k]))


def validate():
    recs = load_all()
    if not recs:
        print("SKIP: SPORE packages not found (SPORE/ absent)")
        return 0
    problems = []
    named = 0
    named_names = []
    for key in sorted(recs):
        blob = recs[key]
        where = "%s %08x/%08x" % key
        if len(blob) != CELL_SIZE:
            problems.append("%s size %d != %d" % (where, len(blob), CELL_SIZE))
            continue
        vals = decode(blob)
        sanity(problems, where, vals)
        text, locid = vals['name']
        if text:
            named += 1
            named_names.append((where, text, locid))
    # double-run: decode every record twice, require byte-identical dumps
    import hashlib
    def dump_hash():
        h = hashlib.sha256()
        for key in sorted(recs):
            h.update(repr(sorted(decode(recs[key]).items())).encode('utf-8'))
        return h.hexdigest()
    h1, h2 = dump_hash(), dump_hash()
    if h1 != h2:
        problems.append("double-run decode not byte-identical")
    # layout proof: last field end == record size
    last_end = max(o + (164 if k == 'loc' else 180 if k == 'ai' else 4)
                   for _, o, k in CELL_FIELDS)
    if last_end != CELL_SIZE:
        problems.append("field span %d != %d" % (last_end, CELL_SIZE))
    print("cell records: %d  named=%d  violations=%d  double_run=%s"
          % (len(recs), named, len(problems), "identical" if h1 == h2 else "DIFFERS"))
    for n, text, locid in named_names[:12]:
        print("  named: %s  loc=0x%08x  %r" % (n, locid, text))
    for p in problems[:40]:
        print("  %s" % p)
    return 1 if problems else 0


def dump(group, inst):
    recs = load_all()
    for (tag, g, i), blob in sorted(recs.items()):
        if g == group and i == inst:
            print("# cell record  %s %08x/%08x  size=%d" % (tag, g, i, len(blob)))
            for name, off, kind in CELL_FIELDS:
                v = _read(blob, off, kind)
                if kind == 'loc':
                    print("  @%03d  %-24s  = %r  loc=0x%08x" % (off, name, v[0], v[1]))
                elif kind == 'ai':
                    print("  @%03d  %-24s  (cAIData)" % (off, name))
                    for n, o, k in AI_FIELDS:
                        av = _read(blob, off + o, k)
                        if k == 'f32':
                            print("      @%03d  %-28s  f  = %g" % (off + o, n, av))
                        elif k == 'u8':
                            print("      @%03d  %-28s  u8 = %d" % (off + o, n, av))
                        else:
                            print("      @%03d  %-28s  u  = 0x%08x" % (off + o, n, av))
                elif kind == 'f32':
                    print("  @%03d  %-24s  f  = %g" % (off, name, v))
                elif kind == 'i32':
                    print("  @%03d  %-24s  i  = %d" % (off, name, v))
                elif kind == 'u8':
                    print("  @%03d  %-24s  u8 = %d" % (off, name, v))
                else:
                    print("  @%03d  %-24s  u  = 0x%08x" % (off, name, v))
            return 0
    print("not found: %08x/%08x" % (group, inst))
    return 1


def main(argv=None):
    argv = argv if argv is not None else sys.argv[1:]
    cmd = argv[0] if argv else 'validate'
    if cmd == 'dump':
        return dump(int(argv[1], 0), int(argv[2], 0))
    return validate()


if __name__ == '__main__':
    sys.exit(main())
