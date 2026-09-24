# sim-object-lookup-strategy — FUN_00b5b800

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b5b800 / 0x0075b800 |
| symbol | FUN_00b5b800 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | n/a (no annotated header) B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

Simulator object lookup + abstract strategy vtable init (purecall ptrs)

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
iVar1 = FUN_00b3d320(); if (iVar1 != 0) return FUN_00a42730(); return 0xffffffff;
```

## Callers

- 00aca360
- 00acc800
- 00acd790
- 00ace5a0
- 00acf4c0
- 00ad12a0
- 00ad20e0
- 00ad2200
- 00ad25e0
- 00ad7b90

## Key callees

- 00a42730
- 00b3d320

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Simulator object lookup with a -1 sentinel: asks the singleton-accessor block (00b3d320) for a pointer; if set, returns the result of FUN_00a42730 (an object/strategy lookup), else 0xffffffff. 10 callers in the 00aca360..00ad7b90 region. The 00a42730 body is outside the 862, so what is looked up is inferred. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b5b800 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b5b800.c (session artifact, not committed)
