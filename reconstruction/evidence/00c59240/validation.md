# Validation 0x00c59240

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
| GLOBALS | `WARN` | `partial` | the complete 228-instruction listing names 6 data address(es) (0x13eb1bc, 0x1485378, 0x1601760, 0x16919b8, 0x16919bc, 0x16919c0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 228-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x9c, 0x208, 0x20c), all of which the record accounts for or the listing is the better witness on; the 228-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=228, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x9c, 0x208, 0x20c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x9c, 0x20c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x208), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (228 of 228 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 20 conditional branch target(s) in the complete 228-instruction listing lie inside the recovered body span 0x00c59240..0x00c5953b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 228-instruction body names 4 indirect transfer(s): 0x00c59479 dispatches slot 0xc0 through the table word in EDX; 0x00c594a9 dispatches slot 0xc0 through the table word in EDX; 0x00c594da dispatches slot 0xc0 through the table word in EDX; 0x00c59512 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 228 of 228 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d3703caa663a2662362551e5aca726fbed28fb0b10e815a954e782e1c344a75b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8c23effd010f32adeabb613a97a063b5246cd1705973d09c7d3d39cdeb722e00`
- Pack digest quoted by the briefing: `d3703caa663a2662362551e5aca726fbed28fb0b10e815a954e782e1c344a75b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
