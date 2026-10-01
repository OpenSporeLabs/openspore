# Validation 0x00ba8830

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
| GLOBALS | `WARN` | `partial` | the complete 309-instruction listing names 2 data address(es) (0x156c63c, 0x156c640) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (309 of 309 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 19 conditional branch target(s) in the complete 309-instruction listing lie inside the recovered body span 0x00ba8830..0x00ba8c2f, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 309-instruction body names 6 indirect transfer(s): 0x00ba8962 is FUNCTION_POINTER; 0x00ba89a4 dispatches slot 0x4 through the table word in EAX; 0x00ba8a48 dispatches slot 0x4 through the table word in EDX; 0x00ba8af6 dispatches slot 0x4 through the table word in EDX; 0x00ba8b92 dispatches slot 0x4 through the table word in EDX; 0x00ba8c26 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 309 of 309 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6, so the dispatch is visible in the machine listing but is not proven: 1 of the 6 indirect transfer(s) classify as FUNCTION_POINTER (0x00ba8962), so the dispatch's identity is not established: EDX is loaded from [EBP], but EBP is defined by an immediate or register assignment, not a memory load earlier in the listing, so the word it names is not shown to be a table word |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8f4be08be3d6150a2013b9cd71df50689b18321c7a252e4286f081f275c72b6a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d10c161c2d7f5e1dbb52e9d3aee6edeb7c628403d57bbd81817c39705d37cf4c`
- Pack digest quoted by the briefing: `8f4be08be3d6150a2013b9cd71df50689b18321c7a252e4286f081f275c72b6a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
