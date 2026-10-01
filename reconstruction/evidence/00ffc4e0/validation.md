# Validation 0x00ffc4e0

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
| GLOBALS | `WARN` | `partial` | the complete 64-instruction listing names 1 data address(es) (0x1485720) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (64 of 64 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 64-instruction listing lie inside the recovered body span 0x00ffc4e0..0x00ffc5a7, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 64-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `934ca4c686dab68c3cd9f16f612bb2111425c9cf12e4c1776aa9f39310b5a012`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d0a9532ccd41e1b2dfd3a58af8332b2aaf7501910820c7f1e62432a44d360cf1`
- Pack digest quoted by the briefing: `934ca4c686dab68c3cd9f16f612bb2111425c9cf12e4c1776aa9f39310b5a012`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
