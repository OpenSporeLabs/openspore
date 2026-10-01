# Validation 0x00c35740

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
| GLOBALS | `WARN` | `partial` | the complete 61-instruction listing names 1 data address(es) (0x18ebadc) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 61-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0xb8, 0xbc, 0xc0), all of which the record accounts for or the listing is the better witness on; the 61-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=61, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0xb8, 0xbc, 0xc0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x84, 0xb8, 0xbc, 0xc0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x84) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (61 of 61 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 61-instruction listing lie inside the recovered body span 0x00c35740..0x00c357fe, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 61-instruction body names 2 indirect transfer(s): 0x00c35797 dispatches slot 0x58 through the table word in EDX; 0x00c357dc dispatches slot 0x4c through the table word in EDX; the machine parse consumed 61 of 61 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `596c01f3d9917033cb4a03a30ce5baf856578e6308e3197b65d025375977fd5d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `999f129215b22fd00d995aa98336c5b3765e5656f76c2ac26414e36b14fcf825`
- Pack digest quoted by the briefing: `596c01f3d9917033cb4a03a30ce5baf856578e6308e3197b65d025375977fd5d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
