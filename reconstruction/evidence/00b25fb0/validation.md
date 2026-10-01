# Validation 0x00b25fb0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `missing`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x00b25fb0..0x00b25fd4, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e9dd71476cac84f3058f7b227c819b060b6358223b6b141279f3de050788546e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ed01c27ed19e921e2d32e45e7299fcecc7c7cb34ba5a75de1c4a55d7d053503a`
- Pack digest quoted by the briefing: `e9dd71476cac84f3058f7b227c819b060b6358223b6b141279f3de050788546e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The current-player provider must return a valid state window before +0x84 is read.`, `The null-current receiver fallback must not be treated as a valid noun-object result by downstream callers without runtime evidence.`, `The receiver must be a valid noun-projection-compatible object for 0x00b25f40.`, `The resolver vector, object pointers, object vtables, and vtable+0x4c targets must be valid.`, `The resolver's 0x00b21340 map/list callbacks and their ownership effects require original-process observation.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The current-player provider must return a valid state window before +0x84 is read.
- The null-current receiver fallback must not be treated as a valid noun-object result by downstream callers without runtime evidence.
- The receiver must be a valid noun-projection-compatible object for 0x00b25f40.
- The resolver vector, object pointers, object vtables, and vtable+0x4c targets must be valid.
- The resolver's 0x00b21340 map/list callbacks and their ownership effects require original-process observation.
- What concrete noun-projection receiver type and vtable family does 0x00b21340 require?
- What concrete object type and vtable owner implement vtable+0x4c?
- What concrete state owner and semantic role belong to current-player+0x84?
- What do the fixed callback words 0x00b21080, 0x00d3d420, 0x00b236c0, and 0x00b1e500 represent?
- What downstream callers assume when the null-current path returns the receiver word?
- What runtime values and validity windows apply to the current-player and resolver objects?
