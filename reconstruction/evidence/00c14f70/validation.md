# Validation 0x00c14f70

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
| GLOBALS | `WARN` | `partial` | the complete 147-instruction listing names 2 data address(es) (0x13ef74c, 0x157174c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 147-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0xc0, 0xb54), all of which the record accounts for or the listing is the better witness on; the 147-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=147, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0xc0, 0xb54) and 1 more only on one arm of a branch, which is a may and grounds nothing (0xc0); the machine-derived receiver record enumerates 2 displacement(s) (0xc0, 0xb54), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (147 of 147 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 147-instruction listing lie inside the recovered body span 0x00c14f70..0x00c15141, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 147-instruction body names 9 indirect transfer(s): 0x00c14fa4 dispatches slot 0x4 through the table word in EAX; 0x00c14fb8 dispatches slot 0x2c through the table word in EAX; 0x00c14ff3 dispatches slot 0x2c through the table word in EDX; 0x00c1501b dispatches slot 0x30 through the table word in EDX; 0x00c15053 dispatches slot 0x18 through the table word in EDX; 0x00c15060 dispatches slot 0x8 through the table word in EAX; 0x00c1510a dispatches slot 0x4 through the table word in EAX; 0x00c1511b dispatches slot 0x4 through the table word in EAX; 0x00c15136 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 147 of 147 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `869f9a4ec78dec640768a73f07feb126be4f46cf857d622f113833ed2fb87259`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `27307f7b6119fb50b91df40e024d64f0cec60631622de2ae43497377f1d339df`
- Pack digest quoted by the briefing: `869f9a4ec78dec640768a73f07feb126be4f46cf857d622f113833ed2fb87259`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
