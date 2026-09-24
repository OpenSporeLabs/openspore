# empire-idcolor-pick — FUN_00c32cd0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00c32cd0 / 0x00832cd0 |
| symbol | FUN_00c32cd0 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | 1357 B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

ID-color pick: choose most-distinguishable of 12 palette colors vs other empires' cached colors; writes mIDColorID+mCachedColor

## Inputs / outputs

- in: this (cEmpire: +0x10 mIDColorID, +0x30 mCachedColor[12B], +0x50 mFlags, +0x84 mPoliticalID, +0xb0 mHomeStar)
- out: selected color (float3 via buffer)

## State (read / write)

- read: DAT_0168de78 (empire list source)
- read: 12-color palette table @0x156b0b8
- write: this+0x10 mIDColorID
- write: this+0x30..0x3c mCachedColor

## Structs / fields

- cEmpire (344B)

## Decompilation evidence

```
this=cEmpire; reads 12-color palette RB-tree @0x156b0b8 (20B nodes: float3 RGB + int key; flag @0x168795c) via 00b6f0c0/00b6ee40 BST-search wrappers; per-color nearest search over other empires' cached colors; sentinels -11/-10; writes mIDColorID(+0x10)+mCachedColor(+0x30..3C).
```

## Callers

- 00c24280
- 00c242b0
- 00c24330
- 00c33580
- 00c33690
- 00c34ee0
- 00c38d00
- 00c39110
- 00c417d0
- 00c42b50
- 00c46a90
- 00c47e20
- 00c4a410
- 00c4f130
- 00c50780
- 00c523a0
- 00c52680
- 00c52c20
- 00c59240
- 00c59540
- 00c5d780
- 00c68060
- 01011120
- 01036c30

## Key callees

- 004232c0
- 005c65e0
- 00b6f0c0
- 00b6ee40
- 00b6f140
- 00b6f180
- 00c30c80
- 00885c90
- 01021300
- 00b1fdb0
- 00b3d2a0
- 00ba6d80
- 00bb9ae0
- 00f47380

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

This is cEmpire's ID-color picker: for each of the 12 palette colors it finds the nearest color already cached by other empires (empire list from DAT_0168de78) and selects the most distinguishable one, writing mIDColorID and the cached float3 into the 344B cEmpire. 19 callers all sit in the cEmpire region (00c24280..00c52c20). The palette table is runtime-initialized (RB-tree), so the 12 exact RGB values are not statically recoverable - the one real gap. Replacement is partial: the algorithm is fully readable from decompilation; the palette constants need a runtime capture.

## Uncertainty / open questions

- palette table is runtime-initialized (RB-tree @0x156b0b8); exact 12 RGB values not recoverable statically

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00c32cd0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00c32cd0.c (session artifact, not committed)
