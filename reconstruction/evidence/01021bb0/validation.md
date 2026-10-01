# Validation 0x01021bb0

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
| GLOBALS | `PASS` | `complete` | the complete 93-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (93 of 93 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 93-instruction listing lie inside the recovered body span 0x01021bb0..0x01021c9c, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 93-instruction body names 7 indirect transfer(s): 0x01021bcf is INDIRECT_NON_VTABLE; 0x01021bf7 dispatches slot 0xbc through the table word in EAX; 0x01021c0c dispatches slot 0xc0 through the table word in EAX; 0x01021c39 dispatches slot 0xbc through the table word in EAX; 0x01021c4e dispatches slot 0xc0 through the table word in EAX; 0x01021c71 dispatches slot 0xbc through the table word in EDX; 0x01021c96 dispatches slot 0xc0 through the table word in EDX; the machine parse consumed 93 of 93 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7, so the dispatch is visible in the machine listing but is not proven: 1 of the 7 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x01021bcf), so the dispatch's identity is not established: the target is the memory operand [ESP + 0x30], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `90d6b5a0a9afa43b8893165cfd3505eb19d78d8e871c3cd86a48d8e7d04905db`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b900f1c3aa5540f51a6c93013f0b7cf1e4e2c7f3c2be45191134757f2cab3acd`
- Pack digest quoted by the briefing: `90d6b5a0a9afa43b8893165cfd3505eb19d78d8e871c3cd86a48d8e7d04905db`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
