# Validation 0x00c70380

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
| GLOBALS | `PASS` | `complete` | the complete 53-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (53 of 53 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 53-instruction listing lie inside the recovered body span 0x00c70380..0x00c70418, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 53-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0ce16415da47e252787ccb4c6ce8ed68c66cf9926376bb3a6930188899e0630e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `436c303dc67345723b246f237efed3714a68a4d533702b238d33efbe2744eef3`
- Pack digest quoted by the briefing: `0ce16415da47e252787ccb4c6ce8ed68c66cf9926376bb3a6930188899e0630e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
