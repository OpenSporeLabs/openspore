# space-player-data-accessors-3 — FUN_01021080

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x01021080 / 0x00c21080 |
| symbol | FUN_01021080 (sdk: —) |
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
return *(Simulator__sSpacePlayerData + 0x10);
```

## Callers

- 00ad23c0
- 00adbca0
- 00ae73e0
- 00ae9c90
- 00aeb3e0
- 00b28ec0
- 00b33130
- 00b35300
- 00b444c0
- 00b4a720

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Reads +0x10 of Simulator::sSpacePlayerData. 10 callers in the 00ad23c0..00b4a720 region. Field meaning inferred; part of the sSpacePlayerData accessor family. Replacement partial (trivial accessor).

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x01021080 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/01021080.c (session artifact, not committed)
