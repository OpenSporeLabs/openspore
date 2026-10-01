# Validation 0x00641e40

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
| GLOBALS | `PASS` | `complete` | the complete 145-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 145-instruction listing nevertheless reaches 4 receiver displacement(s) through ECX (0x4, 0x8, 0xc, 0x74), all of which the record accounts for or the listing is the better witness on; the 145-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=145, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 4 displacement(s) to the receiver as proven (0x4, 0x8, 0xc, 0x74) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x74), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 3 displacement(s) the record does not enumerate (0x4, 0x8, 0xc), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (145 of 145 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 145-instruction listing lie inside the recovered body span 0x00641e40..0x00641f9a, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 145-instruction body names 12 indirect transfer(s): 0x00641e9e dispatches slot 0x4 through the table word in EAX; 0x00641eb1 dispatches slot 0x4 through the table word in EAX; 0x00641eca dispatches slot 0x10 through the table word in EAX; 0x00641eec dispatches slot 0x4 through the table word in EAX; 0x00641efb dispatches slot 0x4 through the table word in EAX; 0x00641f10 dispatches slot 0x10 through the table word in EAX; 0x00641f23 dispatches slot 0x4 through the table word in EDX; 0x00641f3a dispatches slot 0xc through the table word in EDX; 0x00641f58 dispatches slot 0x4 through the table word in EAX; 0x00641f6b dispatches slot 0xc through the table word in EAX; 0x00641f83 dispatches slot 0xb0 through the table word in EDX; 0x00641f92 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 145 of 145 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 12. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 8 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3b2d65c26c63578b85fd558db11058ed60e7fedb3473e675d5c550d3b4d8f414`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4d07908d4c960abda0f913e5e995d86495b80e1f53aff4d2460ffb90fba6ccbc`
- Pack digest quoted by the briefing: `3b2d65c26c63578b85fd558db11058ed60e7fedb3473e675d5c550d3b4d8f414`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
