# Validation 0x00bb4ba0

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
| GLOBALS | `WARN` | `partial` | the complete 251-instruction listing names 18 data address(es) (0x13cc3e0, 0x13cc55c, 0x145f8d4, 0x145f8d8, 0x145f8dc, 0x145fba8, 0x14661d0, 0x14661dc, 0x14661f8, 0x156c64c, 0x156c668, 0x1667bac, 0x1667bae, 0x1689640, 0x1689644, 0x1689c50, 0x1897c18, 0x1a80d26) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 251-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 251-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=251, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0x68, 0xdc, 0xe0, 0x1dc, 0x204, 0x21c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 6 of those (0x68, 0xdc, 0xe0, 0x1dc, 0x204, 0x21c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (251 of 251 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 16 conditional branch target(s) in the complete 251-instruction listing lie inside the recovered body span 0x00bb4ba0..0x00bb4f2d, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 251-instruction body names 10 indirect transfer(s): 0x00bb4be3 dispatches slot 0x20 through the table word in EDX; 0x00bb4c01 is INDIRECT_NON_VTABLE; 0x00bb4c14 is INDIRECT_NON_VTABLE; 0x00bb4d08 dispatches slot 0x0 through the table word in EAX; 0x00bb4dd6 is INDIRECT_NON_VTABLE; 0x00bb4de9 is INDIRECT_NON_VTABLE; 0x00bb4ee8 dispatches slot 0x2c through the table word in EAX; 0x00bb4ef5 dispatches slot 0x1c through the table word in EAX; 0x00bb4efe dispatches slot 0x8 through the table word in EAX; 0x00bb4f24 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 251 of 251 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 10, so the dispatch is visible in the machine listing but is not proven: 4 of the 10 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00bb4c01, 0x00bb4c14, 0x00bb4dd6, 0x00bb4de9), so the dispatch's identity is not established: the target is the memory operand [0x013cc55c], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 3 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2c89c49bc5d5b586a9f7d65b22576b5c001112b6169402ce62958328f3c8ffd1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `99a0ab718e2b978e3f5025698a17ad380f36188c80cdf488a0ed7f45b3a17c45`
- Pack digest quoted by the briefing: `2c89c49bc5d5b586a9f7d65b22576b5c001112b6169402ce62958328f3c8ffd1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
