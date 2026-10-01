# Validation 0x00c042e0

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
| GLOBALS | `WARN` | `partial` | the complete 179-instruction listing names 15 data address(es) (0x1485378, 0x15906f0, 0x1590778, 0x1590800, 0x1590888, 0x1590910, 0x1590998, 0x1590a20, 0x1590aa8, 0x1590b30, 0x15aa9e8, 0x1654c01, 0x1654c02, 0x1654c04, 0x1654c05) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 179-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x58, 0xb58, 0xeac), all of which the record accounts for or the listing is the better witness on; the 179-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=179, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x58, 0xb58, 0xeac) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 7 displacement(s) (0x0, 0x58, 0xb20, 0xb4c, 0xb58, 0xeac, 0x1674), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 4 of those (0x0, 0xb20, 0xb4c, 0x1674) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (179 of 179 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 16 conditional branch target(s) in the complete 179-instruction listing lie inside the recovered body span 0x00c042e0..0x00c04589, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 179-instruction body names 2 indirect transfer(s): 0x00c042ee dispatches slot 0x14 through the table word in EAX; 0x00c04571 dispatches slot 0xd8 through the table word in EDX; the machine parse consumed 179 of 179 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c7a02937eaafa4dfca3abbd75d9bcbfa006f2948f608ca642aa9cea02e3e825f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `661d55c82453c374d6eb62cafa36cd0ae079251429dfacf16b1f1060f589105a`
- Pack digest quoted by the briefing: `c7a02937eaafa4dfca3abbd75d9bcbfa006f2948f608ca642aa9cea02e3e825f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
