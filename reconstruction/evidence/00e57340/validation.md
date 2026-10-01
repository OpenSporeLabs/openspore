# Validation 0x00e57340

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__GetScaleDifferenceWithPlayer.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 44-instruction listing names 4 data address(es) (0x01483c14, 0x01483c34, 0x01483e60, 0x016b3c04); the data-reference artifact is read whole and records 10 reference row(s) out of this body covering every address under review, with access mode(s) read=7, other=3 |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (44 of 44 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 44-instruction listing lie inside the recovered body span 0x00e57340..0x00e573db, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 44-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3b3b537bfc2b28dad5d76416de03d0b32e06dd3360d1e80ea4141021c90848f0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f17231170caa98013034fa0905e76b08753fc3a534ead4d398c176f4c23477b5`
- Pack digest quoted by the briefing: `3b3b537bfc2b28dad5d76416de03d0b32e06dd3360d1e80ea4141021c90848f0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
