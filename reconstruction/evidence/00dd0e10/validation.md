# Validation 0x00dd0e10

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
| GLOBALS | `WARN` | `partial` | the complete 191-instruction listing names 4 data address(es) (0x1464c3c, 0x1464c50, 0x1667bac, 0x1667bae) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 191-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x84, 0x88), all of which the record accounts for or the listing is the better witness on; the 191-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=191, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x84, 0x88) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x0, 0x84, 0x88, 0x9c, 0x124), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x9c, 0x124) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (191 of 191 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 191-instruction listing lie inside the recovered body span 0x00dd0e10..0x00dd105b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 191-instruction body names 9 indirect transfer(s): 0x00dd0e1c dispatches slot 0xc through the table word in EAX; 0x00dd0e38 is INDIRECT_NON_VTABLE; 0x00dd0eb4 dispatches slot 0x20 through the table word in EDX; 0x00dd0ec5 dispatches slot 0x30 through the table word in EDX; 0x00dd0f01 dispatches slot 0xc through the table word in EDX; 0x00dd0f39 dispatches slot 0xc through the table word in EDX; 0x00dd0f9a dispatches slot 0xc through the table word in EDX; 0x00dd0fd2 dispatches slot 0xc through the table word in EDX; 0x00dd100b dispatches slot 0xb8 through the table word in EAX; the machine parse consumed 191 of 191 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9, so the dispatch is visible in the machine listing but is not proven: 1 of the 9 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00dd0e38), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0xdd105c], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 3 passed, 3 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `452016d4a4e0451400c5ac3d6eb9a92e23dcbe3fbed02cec82a793d420bb68f7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b8b96567a7252415086f74720d7697db861c25c947ab678b49e7594fc3585584`
- Pack digest quoted by the briefing: `452016d4a4e0451400c5ac3d6eb9a92e23dcbe3fbed02cec82a793d420bb68f7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `indirect_dispatch_state_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- field meanings
- indirect_dispatch_state_observation
- owner type
- returned object identity
- vtable implementation
