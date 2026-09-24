# sim-singleton-accessors-3 — FUN_00b3d380

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b3d380 / 0x0073d380 |
| symbol | FUN_00b3d380 (sdk: —) |
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
return DAT_0167eb04;
```

## Callers

- 00adf840
- 00ae00d0
- 00ae37c0
- 00ae6240
- 00ae9f50
- 00aebe90
- 00b19290
- 00b1dee0
- 00b26af0
- 00b26c90

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Fourth-observed member of the 15-member singleton accessor block (0x167eac0+; +0x44). 10 callers in the 00adf840..00b26c90 region. Same open item as the other block members. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b3d380 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b3d380.c (session artifact, not committed)
