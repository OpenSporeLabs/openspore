# star-system-regen — FUN_00bb4af0

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00bb4af0 / 0x007b4af0 |
| symbol | FUN_00bb4af0 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | 487 B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

cStarManager star-system regeneration: if star has no planets (mPlanetCount==0) and timing check passes, set mLastObservedTime (minutes), erase from pending list, reset manager state, cStarManager::GeneratePlanetsForStar

## Inputs / outputs

- in: cStarRecord*, flags
- out: regenerated star system

## State (read / write)

- read: cStarRecord +0xac mPlanetCount
- read: manager list/state
- write: cStarRecord +0xc mLastObservedTime
- write: manager state (bb3800/bb9ad0/bb9b00/bba500)

## Structs / fields

- cStarRecord
- cStarManager

## Decompilation evidence

```
this=cStarManager; param_2=cStarRecord (+0xac mPlanetCount, +0xc mLastObservedTime); if mPlanetCount==0 and a b316c0-based timing check (00c8b520) passes: set mLastObservedTime (minutes), erase star from manager list (00bf3420), reset state (00bb3800/00bb9ad0, 00bb9b00(1,0), 00bba500), then cStarManager::GeneratePlanetsForStar(star, flags, 0).
```

## Callers

- 00bb57b0
- 00c31730
- 00c34ee0
- 00c47e20
- 00c59240
- 00c5f770

## Key callees

- 00b316c0
- 00bf3420
- 00bb3800
- 00bb9ad0
- 00bb9b00
- 00bba500

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

cStarManager star-system regeneration: when a star has no planets (mPlanetCount==0) and a timing check passes, it records the observation time (minutes), erases the star from the pending list, resets manager state, and calls the SDK-confirmed cStarManager::GeneratePlanetsForStar. 6 callers. Small (487B), fully decomp-read, no unresolved items. Replacement partial: the regeneration policy is known; the planet-generation body itself (SDK-named, not in the 862) is the remaining piece.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00bb4af0 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00bb4af0.c (session artifact, not committed)
