# Validation 0x008841f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_app_managers/service_accessors_cleanup.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 45-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 45-instruction listing nevertheless reaches 6 receiver displacement(s) through ECX (0x0, 0x8, 0x10, 0x14, 0x18, 0x24), all of which the record accounts for or the listing is the better witness on; the 45-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=45, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 6 displacement(s) to the receiver as proven (0x0, 0x8, 0x10, 0x14, 0x18, 0x24) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0x0, 0x8, 0x10, 0x14, 0x18, 0x24), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (45 of 45 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 45-instruction listing lie inside the recovered body span 0x008841f0..0x00884258, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 45-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `67dbf795e261cd51cb2c73848247bdd2d454a50ad1c2c8411340d14147dc66e8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e04a9343fea81ef40851bfb3cf297a45f7a58781c74e9bf88e9d6854e339473b`
- Pack digest quoted by the briefing: `67dbf795e261cd51cb2c73848247bdd2d454a50ad1c2c8411340d14147dc66e8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-message-cleanup-storage-and-release-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x18-stride record owner
- Can malformed cursor, link, or end pointers reach the same path through SEH?
- What are the meanings of the four-byte words in the cMessageManager+0x08 cleanup window?
- What concrete queue or block object owns the 0x18-stride records and the +0xc0 next-block limit?
- What concrete root, storage, or allocator owns the opaque pointer released after the array loop?
- What runtime teardown ordering reaches this walker from the cMessageManager owner?
- gate-message-cleanup-storage-and-release-lifecycle
- pointer-array and root storage identity
- release callback semantics
- teardown reachability
