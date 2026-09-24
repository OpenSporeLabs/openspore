# space-player-data-accessors-2 — FUN_01021300

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x01021300 / 0x00c21300 |
| symbol | FUN_01021300 (sdk: —) |
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
reads sSpacePlayerData+0x18 (id, -1 sentinel) and +0x1c (cached pointer); if cached object's +0x84 != stored id: re-lookup via 00ba9370 (map GetByID) + 00b3d2a0, swap pointer, call dtor (slot +4) on the old object; returns cached pointer.
```

## Callers

- 00ae9590
- 00ae9930
- 00ae9f50
- 00aeb3e0
- 00aebe90
- 00b25fb0
- 00b262c0
- 00b28ec0
- 00b6d3c0
- 00ba0080

## Key callees

- 00b3d2a0
- 00ba9370

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

A cached-object validator on Simulator::sSpacePlayerData: it keeps +0x18 (an id, -1 = unset) alongside +0x1c (a cached object pointer) and re-validates that the cached object's +0x84 field (the cEmpire mPoliticalID offset) matches the stored id; on mismatch it re-looks the object up through 00ba9370 (map GetByID) and swaps the pointer, destructing the old one via vtable slot +4. 10 callers in the 00ae9590..00ba0080 region. This is the most structurally informative of the accessor family - it pins down the +0x18/+0x1c id+pointer cache pattern. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x01021300 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/01021300.c (session artifact, not committed)
