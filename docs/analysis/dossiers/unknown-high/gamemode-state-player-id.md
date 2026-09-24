# gamemode-state-player-id — FUN_00b1fdb0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b1fdb0 / 0x0071fdb0 |
| symbol | FUN_00b1fdb0 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | n/a (no annotated header) B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

game mode state -> player ID

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
return *(param_1 + 0x54);  (field accessor)
```

## Callers

- 00b0a6f0
- 00b19290
- 00b2dac0
- 00b2e940
- 00b31cc0
- 00b7a880
- 00b96d40
- 00ba1590
- 00ba9f80
- 00bb1340

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Field accessor reading +0x54 of a passed state object - adjudicated as game-mode-state -> player ID. 10 callers in the 00b0a6f0..00bb1340 region. The +0x54 offset is observed; the struct owning it is not named in the SDK, so the field meaning is inferred. Replacement partial (trivial accessor once the struct is named).

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b1fdb0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b1fdb0.c (session artifact, not committed)
