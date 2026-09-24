# space-player-data-accessors — FUN_01021260

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x01021260 / 0x00c21260 |
| symbol | FUN_01021260 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_SUPPORT |
| priority | P3 |
| evidence | SUPPORTED |
| size | n/a (no annotated header) B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

Simulator__sSpacePlayerData accessors

## Inputs / outputs

- in: (none recorded)
- out: (none recorded)

## State (read / write)

- read: (none recorded)
- write: (none recorded)

## Structs / fields

- (none named)

## Decompilation evidence

```
null-guarded read of Simulator__sSpacePlayerData + 4 (+0x4); returns 0 when the global is null.
```

## Callers

- 00acc390
- 00acc800
- 00acd790
- 00acf3e0
- 00acf4c0
- 00ad4a10
- 00aeb240
- 00aeb890
- 00b2a110
- 00b2bbe0

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Accesses +0x4 of the Simulator::sSpacePlayerData global, null-guarded. 10 callers in the 00acc390..00b2bbe0 region. Part of a small family of sSpacePlayerData accessors (+0x4, +0x10, +0x18/-1 sentinel, +0x1c cached pointer). Field meanings inferred; the global is SDK-named. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x01021260 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/01021260.c (session artifact, not committed)
