# sim-singleton-accessors-4 — FUN_00b3d240

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b3d240 / 0x0073d240 |
| symbol | FUN_00b3d240 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_SUPPORT |
| priority | P3 |
| evidence | SUPPORTED |
| size | n/a (no annotated header) B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

Simulator global singleton accessors (15 members)

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
return DAT_0167eac4;
```

## Callers

- 00ae00d0
- 00b08670
- 00b0a6f0
- 00b19290
- 00b19440
- 00b195f0
- 00b197b0
- 00b19810
- 00b303e0
- 00b30550

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

First-observed member of the 15-member singleton accessor block (0x167eac0+; +0x04). 10 callers in the 00ae00d0..00b30550 region. Same open item as the other block members. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b3d240 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b3d240.c (session artifact, not committed)
