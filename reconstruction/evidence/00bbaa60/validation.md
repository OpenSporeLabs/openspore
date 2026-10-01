# Validation 0x00bbaa60

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-core-b01/bbaa60_star_record_planet.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 8-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 8-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x84), all of which the record accounts for or the listing is the better witness on; the 8-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=8, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x84) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x84), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 8-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cdad127cda2844190154a67c4d4a00ba6d2ac27946d16d4236291b727efc5549`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `128362c5168c829410859dcacfa703c35ce8c05619dce4b776b4411f7b040484`
- Pack digest quoted by the briefing: `cdad127cda2844190154a67c4d4a00ba6d2ac27946d16d4236291b727efc5549`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace would be needed to observe the actual StarIDs the sync requests, to confirm that the vector is repopulated rather than merely reallocated on the second call, and to see whether any caller ever passes an out-of-range index.`, `No original-process trace exists for 0x00bbaa60; every claim is static.`, `The runtime value of mPlanetCount and of the vector's capacity for a real star is not recoverable statically.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace would be needed to observe the actual StarIDs the sync requests, to confirm that the vector is repopulated rather than merely reallocated on the second call, and to see whether any caller ever passes an out-of-range index.
- Is 0x00bbaa60 ever called with the intent to trigger the load only, ignoring the result? The 20 canonical callers include several whose names suggest other subsystems, and none of the uninspected ones was checked for result use.
- No original-process trace exists for 0x00bbaa60; every claim is static.
- The runtime value of mPlanetCount and of the vector's capacity for a real star is not recoverable statically.
- What are the valid index bounds, and who guarantees them? Nothing here checks, so the contract is entirely on the callers; the 19 other canonical callers were not disassembled and might not all be well-behaved.
- What does the literal 0x5220cb8 in the per-iteration request mean? It has no SDK name and appears as a constant in the request word adjacent to the StarID.
- What is 0x00bba900 really? The SDK calls it GetPlanetRecords but the body is a boolean predicate over mPlanetCount and mFlags bit 12, and its JNZ leaves the function. Left unclassified; resolving it would sharpen the naming of this whole cluster.
- Which class and method is this, strictly? The evidence supports cStarRecord::GetPlanetRecord(size_t), but the SDK gives no address for that declaration and the function is in no vtable.
- Why does the sync advance the StarID by 0x1000000 per element instead of populating from a list? mPlanetCount is a plain byte with no accompanying table of ids in the object, so the ids must be derived. The derivation rule is observed but its intent is not.
