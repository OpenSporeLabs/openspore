# cell-object-pool-lifecycle — FUN_00e780a0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00e780a0 / 0x00a780a0 |
| symbol | FUN_00e780a0 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | 1144 B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

Cell object pool lifecycle: clear avatar ref if matching, release old GFX+assoc object, rebuild if stage scale changed, cObjectPool_::CreateObject

## Inputs / outputs

- in: cObjectPoolIndex, stage/scale params
- out: recreated pooled cell object

## State (read / write)

- read: sCellGame+0x411c mAvatarCellIndex
- read: cCellObjectData fields
- write: sCellGame+0x411c (cleared)
- write: pooled object slots

## Structs / fields

- cCellObjectData (920B)
- cCellGame (20964B)

## Decompilation evidence

```
param_1=cObjectPoolIndex; iVar1=cCellObjectData (920B: mModelKey@0xfc, mCellResource@0x108, mGFXObjectIndex@0x248, mScale@0x358, mpQuery@0x35c); sCellGame->mAvatarCellIndex(+0x411c) cleared if matching; releases old GFX object, destroys assoc object, rebuilds if stage scale changed, then cObjectPool_::CreateObject.
```

## Callers

- 00e771d0
- 00e77450
- 00e77620
- 00e77980
- 00e77b10
- 00e77d50
- 00e78230
- 00e7b6c0
- 00e7c700
- 00e7d1d0
- 00e7d2c0
- 00e7d3b0
- 00e7d860
- 00e7d940
- 00e7db20
- 00e7dc30
- 00e7df40

## Key callees

- 00743b50
- 00e51650
- 00e59a70
- 00e66010
- 00e671c0
- 00e67890
- 00e86980

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Pool-object lifecycle for cell graphics: given a cObjectPoolIndex it detaches the avatar reference if it points at this index, releases the old GFX object and its associated object, rebuilds when the stage scale changed, and recreates the pooled object via cObjectPool_::CreateObject. Field layout of cCellObjectData (920B) and the 20964B cCellGame (mAvatarCellIndex @ +0x411c) are decomp-confirmed. 17 callers sit in the 00e771d0..00e7df40 cell region. Replacement is partial: structure and sequence are known; the GFX release/rebuild callees (00e51650..00e86980) still need their own dossiers before a drop-in is possible.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00e780a0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00e780a0.c (session artifact, not committed)
