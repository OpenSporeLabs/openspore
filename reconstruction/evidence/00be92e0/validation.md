# Validation 0x00be92e0

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
| GLOBALS | `WARN` | `partial` | the complete 386-instruction listing names 3 data address(es) (0x14688e8, 0x14688f4, 0x1654c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 386-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x29c, 0x590), all of which the record accounts for or the listing is the better witness on; the 386-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=386, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x29c, 0x590) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 29 displacement(s) (0x120, 0x29c, 0x2e0, 0x2e1, 0x2e2, 0x2e3, 0x2e4, 0x2e5, 0x2e6, 0x320, 0x340, 0x344, 0x540, 0x590, 0x6c0, 0x748, 0x74c, 0x750, 0x754, 0x758, 0x75c, 0x762, 0x7d8, 0x7dc, 0x7e0, 0x7e4, 0x7e8, 0x7ec, 0x810), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 27 of those (0x120, 0x2e0, 0x2e1, 0x2e2, 0x2e3, 0x2e4, 0x2e5, 0x2e6, 0x320, 0x340, 0x344, 0x540, 0x6c0, 0x748, 0x74c, 0x750, 0x754, 0x758, 0x75c, 0x762, 0x7d8, 0x7dc, 0x7e0, 0x7e4, 0x7e8, 0x7ec, 0x810) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (386 of 386 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 38 conditional branch target(s) in the complete 386-instruction listing lie inside the recovered body span 0x00be92e0..0x00be984c, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 386-instruction body names 9 indirect transfer(s): 0x00be92ff dispatches slot 0x4c through the table word in EDX; 0x00be9325 dispatches slot 0x0 through the table word in EDX; 0x00be934a dispatches slot 0x4 through the table word in EDX; 0x00be9368 dispatches slot 0x58 through the table word in EDX; 0x00be94b2 dispatches slot 0x18 through the table word in EDX; 0x00be94e2 dispatches slot 0x10 through the table word in EDX; 0x00be94f1 dispatches slot 0xc through the table word in EDX; 0x00be97d6 dispatches slot 0x18 through the table word in EDX; 0x00be9840 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 386 of 386 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d353713bfd0d5a58ca6ff20422ad3b41ff0d707d15a730c2ff19e400909ad5cf`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e39a19a27b67f81c875e0c05f8dc064c3e778f0849cb95ce5e4503dc6e9e474d`
- Pack digest quoted by the briefing: `d353713bfd0d5a58ca6ff20422ad3b41ff0d707d15a730c2ff19e400909ad5cf`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
