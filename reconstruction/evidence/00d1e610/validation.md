# Validation 0x00d1e610

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
| GLOBALS | `WARN` | `partial` | the complete 24-instruction listing names 1 data address(es) (0x1654c01) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 24-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=24, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (24 of 24 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 24-instruction listing lie inside the recovered body span 0x00d1e610..0x00d1e64d, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 24-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4a25dffbf1598994b449a0c571880a9e7b818237b6907c126523906ba4fc5ac4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `419f9f177e9cd4fe39340c230f4dba914303cfcf6f5fd0be6465605245287d01`
- Pack digest quoted by the briefing: `4a25dffbf1598994b449a0c571880a9e7b818237b6907c126523906ba4fc5ac4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
