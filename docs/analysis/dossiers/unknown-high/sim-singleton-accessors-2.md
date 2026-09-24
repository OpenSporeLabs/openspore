# sim-singleton-accessors-2 — FUN_00b3d2a0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b3d2a0 / 0x0073d2a0 |
| symbol | FUN_00b3d2a0 (sdk: —) |
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
return DAT_0167eae4;
```

## Callers

- 00ae9040
- 00ae9500
- 00ae9590
- 00ae9930
- 00ae9f50
- 00aeb3e0
- 00aebe90
- 00aecf90
- 00aed2c0
- 00b20790

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Second-observed member of the same 15-member singleton accessor block (0x167eac0+; +0x24). 10 callers in the 00ae9040..00b20790 region. Same gap as the other block members: the identity of the exposed global is not established. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b3d2a0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b3d2a0.c (session artifact, not committed)
