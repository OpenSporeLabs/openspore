# Validation 0x00ad1000

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
| GLOBALS | `WARN` | `partial` | the complete 177-instruction listing names 1 data address(es) (0x167a390) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (177 of 177 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 19 conditional branch target(s) in the complete 177-instruction listing lie inside the recovered body span 0x00ad1000..0x00ad11e8, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 177-instruction body names 8 indirect transfer(s): 0x00ad108e dispatches slot 0x0 through the table word in EDX; 0x00ad10a4 dispatches slot 0x4 through the table word in EDX; 0x00ad1103 dispatches slot 0xc through the table word in EDX; 0x00ad1148 dispatches slot 0xc through the table word in EAX; 0x00ad1160 dispatches slot 0x38 through the table word in EAX; 0x00ad1183 dispatches slot 0xc through the table word in EDX; 0x00ad11a0 dispatches slot 0xc through the table word in EDX; 0x00ad11ca dispatches slot 0xc through the table word in EDX; the machine parse consumed 177 of 177 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 8. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f15e5ca9a6f47e88596603fb2a2eccd8fc3ff23710578095c460bb7f066e287b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a246dc10bc43314fcd1676e9691d4a223fe8b832a294976844070108dff08e62`
- Pack digest quoted by the briefing: `f15e5ca9a6f47e88596603fb2a2eccd8fc3ff23710578095c460bb7f066e287b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
