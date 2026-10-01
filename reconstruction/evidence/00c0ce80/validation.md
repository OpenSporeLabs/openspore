# Validation 0x00c0ce80

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b08/ae9f50_session_boot_register.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 63-instruction listing names 5 data address(es) (0x1471064, 0x15d964c, 0x15d9650, 0x15d9654, 0x1654c10) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 63-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0xc0), all of which the record accounts for or the listing is the better witness on; the 63-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=63, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xc0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0xc0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (63 of 63 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 63-instruction listing lie inside the recovered body span 0x00c0ce80..0x00c0cf49, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 63-instruction body names 1 indirect transfer(s): 0x00c0cee7 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 63 of 63 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ad70ad7a0275ed2bb94be05ec967c0deba7cce623c513c70e2a90bb439322e80`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `71aa5cbcad3fbe27642bd14292c402ef36252addf64ec2b0555affdcc8952f2c`
- Pack digest quoted by the briefing: `ad70ad7a0275ed2bb94be05ec967c0deba7cce623c513c70e2a90bb439322e80`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists. A differential run must confirm the six table values at 0x015D9650 and the boolean behind slot +0x58 at the moment this function runs.`, `The concrete receiver behind the slot +0x58 dispatch must be observed before the owning class can be named.`, `The sentinel branch is only reachable once 0x01654C10 has been populated at runtime; in the file image it holds 0, so the branch cannot be exercised statically.`, `The value of the singleton's float vector at singleton+0x10 can only be observed at runtime, which also determines whether 0x00F31500 returns a real element or FLD1.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the sentinel test 0x00B5B800() == 0x01654C10 a type check or an instance check? The same constant is pushed to 0x00B3D320 inside 0x00F31500, which is consistent with either reading.
- No original-process trace exists. A differential run must confirm the six table values at 0x015D9650 and the boolean behind slot +0x58 at the moment this function runs.
- Ten of the fifteen recorded callsites were not individually disassembled.
- The concrete receiver behind the slot +0x58 dispatch must be observed before the owning class can be named.
- The sentinel branch is only reachable once 0x01654C10 has been populated at runtime; in the file image it holds 0, so the branch cannot be exercised statically.
- The value of the singleton's float vector at singleton+0x10 can only be observed at runtime, which also determines whether 0x00F31500 returns a real element or FLD1.
- What are the six runtime values of the float table at 0x015D9650? The shipped image carries zeros, so on the file image every path through this table returns 0.
- What is 0x0145F924, the type descriptor 0x00C03260 passes to the allocator? It is read as an immediate only.
- What is the boolean at slot +0x58? It is only ever consumed as a gate on whether the neighbour-averaged formula is applied.
- What is the name of the float at _DAT_0150C900 that 0x00C0CFA0 adds to this result? It was not read.
- What populates the singleton at 0x0168D824 and its float vector at +0x10? Only the lazy-allocation path of 0x00C03260 is read; the writer is not identified.
- Which class owns the sub-object at receiver+0xC0, and what is its slot +0x58? No vtable reachable from this function was located and the binary has no RTTI.
- Why does 0x00C0CE30 read receiver+0xFA0 and add it to the index? It is read only inside that callee and this worker did not reconstruct 0x00C0CE30's own inputs.
