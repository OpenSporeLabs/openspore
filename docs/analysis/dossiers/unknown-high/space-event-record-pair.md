# space-event-record-pair — FUN_00e39ab0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00e39ab0 / 0x00a39ab0 |
| symbol | FUN_00e39ab0 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | INFERRED |
| size | 1679 B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

Space event record pair builder: allocates 2 records {object, cellIDs, ms timestamp, slot sentinel -10, IDs, float3s, +0x64/68}; positions from cTribe or args

## Inputs / outputs

- in: object ref, int3 positions, slot/ID params
- out: 2 allocated event records

## State (read / write)

- read: global cTribe (field_504/508/50C int3)
- read: DAT_0168de78
- write: record fields incl. cellIDs via 00e39450/00e39420

## Structs / fields

- cTribe (6624B)

## Decompilation evidence

```
allocates two records (27-field / 24-field structs): {object, cellIDs via pos->GetCellID, timestamp=ms (b316c0/1000), slot (default 0x53dbcf2=-10 sentinel), IDs, float3s, +0x64/68}; positions from global cTribe (field_504/508/50C int3) or args.
```

## Callers

- 00c4b310
- 00c830f0
- 00f17f70
- 00fda750
- 00fe2ab0
- 00e36210
- 00e36370
- 00e36440
- 00e36600
- 00e36690
- 00e37670
- 00e38b60
- 00e38f90
- 00e3a110
- 00e3a400
- 00e3a720

## Key callees

- 00e39450
- 00e39420
- 007eb820
- 00b316c0

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Builds a PAIR of space event records (27- and 24-field structs) carrying object ref, cell IDs, a millisecond timestamp, a -10 slot sentinel, IDs and float3 positions; positions come from the global cTribe (6624B, int3 at +0x504/508/50C) or from arguments. Callers include cSpaceTrading::ObtainTradingObject and cDefaultBeamTool::WhileFiring plus 14 functions in the 00e36210..00e3a720 region - this is shared space-mode event plumbing. Evidence is INFERRED: the record struct layout (27/24 fields) is not in the SDK TSV, so field meaning beyond the observed offsets is inferred. Replacement partial.

## Uncertainty / open questions

- record struct layout (27/24 fields) not in SDK TSV

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00e39ab0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00e39ab0.c (session artifact, not committed)
