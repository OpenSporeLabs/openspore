# sim-singleton-accessors — FUN_00b3d300

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b3d300 / 0x0073d300 |
| symbol | FUN_00b3d300 (sdk: —) |
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
return DAT_0167eae0;  - one of a 15-member block of 4-byte global accessors at 0x40 spacing (0x00b3d240..0x00b3d380 observed: 0x167eac4, 0x167eae0, 0x167eae4, 0x167eb04).
```

## Callers

- 00ac1190
- 00ac7790
- 00ac79a0
- 00ac79e0
- 00ac7a40
- 00ac7ab0
- 00acd4a0
- 00ace4e0
- 00ace5a0
- 00acf3e0

## Key callees

- (none recorded)

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

One member of a 15-member block of singleton accessors: each is a one-instruction function returning a 4-byte global at 0x167eac0+ (observed offsets +0x04, +0x20, +0x24, +0x44; 0x40 function spacing). 10 callers in the 00ac1190..00acf3e0 region. The block almost certainly exposes one pointer per member of a contiguous struct of Simulator singletons - which singleton sits at each offset is not established. Replacement partial (trivial accessors once the global layout is named).

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b3d300 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b3d300.c (session artifact, not committed)
