#!/usr/bin/env python3
"""Oracle for CS-03: the CellSerializer cell-resource records.

The `cCellGlobalsResource` (TYPE 0x2A3CE5B7) is the single stage-wide globals
record in SPORE/DataEP1/Spore_EP1_Data.package (group 0, inst 0xa426730b,
276 bytes decompressed). It is a DIRECT field-by-field serialization of the
runtime struct `Simulator::Cell::cCellGlobalsResource` (struct 61843 family,
276 bytes) — NOT wrapped in a name/ID envelope. Every field decodes to a
plausible hand-authored tuning value (round floats, small enums, u32 refs),
which is the evidence the layout is correct.

Usage:
  cellres.py dump        decode the globals record field-by-field
  cellres.py validate    prove every byte is accounted + values are plausible
"""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'dbpf'))
from dbpf import read, getdata

_HERE = os.path.dirname(os.path.abspath(__file__))
_REPO = os.path.abspath(os.path.join(_HERE, '..', '..', '..'))

GLOBALS_TYPE = 0x2A3CE5B7
GLOBALS_SIZE = 276

# (name, offset, kind) for cCellGlobalsResource — struct 61843 family.
# kind: 'u32' | 'f32' | 'ref' (u32 resource-reference key)
GLOBALS_FIELDS = [
    ('gameMode', 0, 'u32'),
    ('world_1', 4, 'ref'), ('world_2', 8, 'ref'), ('world_3', 12, 'ref'),
    ('world_4', 16, 'ref'), ('world_5', 20, 'ref'),
    ('worldBackground_1', 24, 'ref'), ('worldBackground_2', 28, 'ref'),
    ('worldBackground_3', 32, 'ref'), ('worldBackground_4', 36, 'ref'),
    ('worldBackground_5', 40, 'ref'),
    ('worldRandom', 44, 'ref'),
    ('worldRandomBg', 48, 'ref'),
    ('startCell', 52, 'ref'),
    ('startingCellKey', 56, 'u32'),
    ('effectMapEntry', 60, 'ref'),
    ('backgroundMapEntry', 64, 'ref'),
    ('flowMultiplier', 68, 'f32'),
    ('npcSpeedMultiplier', 72, 'f32'),
    ('npcTurnSpeedMultiplier_Jet', 76, 'f32'),
    ('npcTurnSpeedMultiplier_Flagella', 80, 'f32'),
    ('npcTurnSpeedMultiplier_Cilia', 84, 'f32'),
    ('densityRock', 88, 'f32'),
    ('densitySolid', 92, 'f32'),
    ('densityLiquid', 96, 'f32'),
    ('densityAir', 100, 'f32'),
    ('backgroundDistance', 104, 'f32'),
    ('minDragCollisionSpeed', 108, 'f32'),
    ('minImpactCollisionSpeed', 112, 'f32'),
    ('ciliaSpeedAsJet', 116, 'f32'),
    ('flagellaSpeedAsJet', 120, 'f32'),
    ('flagellaSpeedAsCilia', 124, 'f32'),
    ('ciliaSpeedAsFlagella', 128, 'f32'),
    ('keyLookAlgorithm', 132, 'ref'),
    ('beachDistance', 136, 'f32'),
    ('finishLineDistance', 140, 'f32'),
    ('noPartSpeed', 144, 'f32'),
    ('flagellaRampMinFactor', 148, 'f32'),
    ('flagellaRampTime', 152, 'f32'),
    ('flagellaRampResetAngle', 156, 'f32'),
    ('flagellaTurnSpeedRampStart', 160, 'f32'),
    ('flagellaTurnSpeedRampEnd', 164, 'f32'),
    ('flagellaTurnSpeedMin', 168, 'f32'),
    ('flagellaTurnSpeedMax', 172, 'f32'),
    ('ciliaTurnSpeed', 176, 'f32'),
    ('jetTurnSpeed', 180, 'f32'),
    ('startLevelNoCreatureRadius', 184, 'f32'),
    ('startLevelNoAnythingRadius', 188, 'f32'),
    ('numHighLOD_FG', 192, 'u32'),
    ('numHighLOD_BG', 196, 'u32'),
    ('percentAnimalFood', 200, 'f32'),
    ('percentPlantFood', 204, 'f32'),
    ('field_208', 208, 'u32'),
    ('controlMethod', 212, 'u32'),
    ('editorMethod', 216, 'u32'),
    ('tutorialMethod', 220, 'u32'),
    ('endingMethod', 224, 'u32'),
    ('eyeMethod', 228, 'u32'),
    ('timeToGoldyCinematic', 232, 'f32'),
    ('missionTime', 236, 'f32'),
    ('missionResetTime', 240, 'f32'),
    ('escapeMinDistance', 244, 'f32'),
    ('escapeMaxDistance', 248, 'f32'),
    ('escapeDelayMedium', 252, 'f32'),
    ('escapeTimerHard', 256, 'f32'),
    ('nonAnimatingCiliaMovementFactor', 260, 'f32'),
    ('nonAnimatingJetMovementFactor', 264, 'f32'),
    ('mateTriggerDistance', 268, 'f32'),
    ('mateSpawnDistance', 272, 'f32'),
]

# enum fields expected to hold small values (0..8)
_ENUMS = {'gameMode', 'controlMethod', 'editorMethod', 'tutorialMethod',
          'endingMethod', 'eyeMethod', 'field_208'}
# int fields expected to hold small counts (0..1024). startingCellKey is a
# ResourceKey reference (like startCell), so it is intentionally NOT checked.
_SMALLINT = {'numHighLOD_FG', 'numHighLOD_BG'}


def _globals_path():
    return os.path.join(_REPO, 'SPORE', 'DataEP1', 'Spore_EP1_Data.package')


def load_globals():
    """Return the decompressed globals record bytes, or None if absent."""
    if not os.path.exists(_globals_path()):
        return None
    data, items = read(_globals_path())
    hits = [it for it in items if it['type'] == GLOBALS_TYPE]
    if not hits:
        return None
    return getdata(data, hits[0])


def decode_globals(blob):
    """Decode the globals record field-by-field; returns an ordered dict."""
    out = {}
    for name, off, kind in GLOBALS_FIELDS:
        if kind == 'f32':
            out[name] = struct.unpack_from('<f', blob, off)[0]
        else:  # u32 / ref
            out[name] = struct.unpack_from('<I', blob, off)[0]
    return out


def validate(blob):
    """Prove the layout: size, full byte coverage, plausible values."""
    problems = []
    if len(blob) != GLOBALS_SIZE:
        problems.append("size %d != %d" % (len(blob), GLOBALS_SIZE))
    # full byte coverage: last field end == record size
    last_end = max(off + 4 for _, off, _ in GLOBALS_FIELDS)
    if last_end != len(blob):
        problems.append("field span %d != size %d" % (last_end, len(blob)))
    vals = decode_globals(blob)
    for name, off, kind in GLOBALS_FIELDS:
        v = vals[name]
        if kind == 'f32':
            if v != v or abs(v) > 1e6:
                problems.append("%s = %r not a plausible float" % (name, v))
        elif name in _ENUMS:
            if v > 8:
                problems.append("%s = %d not a small enum" % (name, v))
        elif name in _SMALLINT:
            if v > 1024:
                problems.append("%s = %d not a small int" % (name, v))
    return problems


def main(argv=None):
    argv = argv if argv is not None else sys.argv[1:]
    cmd = argv[0] if argv else 'validate'
    blob = load_globals()
    if blob is None:
        print("SKIP: Spore_EP1_Data.package not found (SPORE/ absent)")
        return 0
    if cmd == 'dump':
        print("# cCellGlobalsResource  type=0x%08x  size=%d" %
              (GLOBALS_TYPE, len(blob)))
        for name, off, kind in GLOBALS_FIELDS:
            v = struct.unpack_from('<%s' % ('f' if kind == 'f32' else 'I'),
                                   blob, off)[0]
            if kind == 'f32':
                print("  @%03d  %-32s  f  = %g" % (off, name, v))
            else:
                print("  @%03d  %-32s  u  = 0x%08x" % (off, name, v))
        return 0
    problems = validate(blob)
    print("globals record: size=%d  fields=%d  violations=%d"
          % (len(blob), len(GLOBALS_FIELDS), len(problems)))
    for p in problems[:40]:
        print("  %s" % p)
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
