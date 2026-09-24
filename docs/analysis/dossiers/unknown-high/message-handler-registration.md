# message-handler-registration — FUN_00b21340

UNKNOWN-HIGH investigation (snapshot f0e310e0, binary sha256 25d42a7a…d914e; image base 0x400000).

## Classification (adjudicated)

| field | value |
|---|---|
| VA / RVA | 0x00b21340 / 0x00721340 |
| symbol | FUN_00b21340 (sdk: —) |
| subsystem | Simulator |
| category | GAMEPLAY_LOGIC |
| priority | P3 |
| evidence | SUPPORTED |
| size | n/a (no annotated header) B |
| replacement candidate | partial (recon-relevant: 1) |

## Purpose

message-handler registration (5 code pointers)

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
map_int_whatever_find lookup; if found at param_1+0x9c: register via 00ba8420; else take name at +0x14; if name non-empty: (*param_3)(name) then walk a linked list (param_1+0x6c..+0x78, 0xC-stride items) calling (*param_5)(item,id) and (*param_4)(name,item); clears the name; returns the name buffer.
```

## Callers

- 00acd9a0
- 00acd9d0
- 00acda00
- 00ace2c0
- 00ace2f0
- 00ace4e0
- 00ace5a0
- 00ad12a0
- 00ad49b0
- 00ad49e0

## Key callees

- 00ba8420
- 00e5c780

## Vtable relationship

none (not a vtable member)

## External / engine deps

- (none)

## Analysis

Message-handler registration with 5 code pointers: looks up an id in a map (map_int_whatever_find), registers a handler when present (00ba8420), otherwise resolves a name and walks a 0xC-stride linked list of items, invoking the per-item predicate (param_5) and the name/item pair handler (param_4). 10 callers in the 00acd9a0..00ad49e0 region. The 5 code pointers are observed; their contract is inferred from call shape. Replacement partial.

## Uncertainty / open questions

- (none recorded beyond the gaps above)

## Replacement feasibility

partial — see `replacement_readiness` in the JSON; nothing here is marked implemented, replacement-tested, or runtime-validated.

## Sources

- Ghidra function 0x00b21340 (SporeProject, snapshot f0e310e0)
- knowledgegraph/triage/unknown-high-investigation-f0e310e0.json
- decomp cache /tmp/opencode/uh/decomp/00b21340.c (session artifact, not committed)
