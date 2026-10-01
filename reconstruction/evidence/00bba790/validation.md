# Validation 0x00bba790

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg_sim_f00bba790/sim_f00bba790.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 76-instruction listing name the same 5 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00bba790..0x00bba861 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00bba84d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 5 distinct address(es) for 0x00bba790; 52 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 5 outgoing call edge row(s) and 5 distinct callee(s) the export records; 5 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00aea5d0, 0x00b8d970, 0x00bba640, 0x00d01790, 0x00e25bd0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 5 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 76-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 76-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x5c, 0x84), all of which the record accounts for or the listing is the better witness on; the 76-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=76, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x5c, 0x84) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x5c, 0x84, 0x88, 0x98, 0x9c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x88, 0x98, 0x9c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (76 of 76 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 76-instruction listing lie inside the recovered body span 0x00bba790..0x00bba861, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 76-instruction body names 1 indirect transfer(s): 0x00bba840 dispatches slot 0x0 through the table word in EAX; the machine parse consumed 76 of 76 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is WIDTH_4_IN_EAX and the source span declares return type 'SimPorts&', whose width cannot be computed from the declaration (a typedef, a class, a template or an alias); the machine width is a fact and the C type is a source-side choice, so there is nothing to compare |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d1f62b7d0c1fc0e21b509e88e837d90d12fb0ab30ab2f2b4f6412564b7abf248`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3a1d9333c8ff6a19bc302249e094e4b878035bff9036b3c74a0c15dc09f739da`
- Pack digest quoted by the briefing: `d1f62b7d0c1fc0e21b509e88e837d90d12fb0ab30ab2f2b4f6412564b7abf248`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00e25bd0 and 0x00d01790 are inferred to clean their own 8 and 4 bytes because the stack is not adjusted after either call; their actual ret forms are not observed from this listing.
- The bodies of 0x00bba640, 0x00e25bd0, 0x00d01790, 0x00b8d970 and 0x00aea5d0 are unresolved; each is declared as a port carrying only its observed call shape and is never given a fabricated body.
- The class identity of the receiver and the concrete type behind the vector words are unresolved; only element+0x00 and its first table word are observed, so the node and its dispatch table stay opaque.
- The element dispatch is only observed as MOV EAX,[ECX]; MOV EDX,[EAX]; CALL EDX. Reading element+0x00 as a table pointer is an inference from that shape, not a confirmed vtable.
- The exact element stride beyond the 4-byte word implied by SAR 2 is fixed by the listing, but the semantic width of a pending element is not stated by the evidence.
- The meaning of the two words 0x00e25bd0 receives (the active vector's own begin and end at the call) is not observable here; the port carries both verbatim.
- The pending vector at +0x84 is read-only here, so the transferred elements are still listed after a flush; whether another function clears it is not observable from this listing.
- The predicate implemented by 0x00b8d970 is unknown; only its effect is observed, that a non-zero AL leaves the element in the pending vector.
- The receiver fields below +0x5c, the range +0x60..+0x83, the word at +0x8c and the range +0x90..+0x97 are never touched by this function, so they stay opaque; only the six observed displacements are named.
- The semantics of 0x00aea5d0 are not observable here beyond the argument surface; note that this path does not dispatch the moved element, so whether the callee dispatches it is unknown.
- Whether 0x00bba640 consumes ECX as a receiver or merely ignores it cannot be decided from this listing, because no instruction clears ECX between 0x00bba792 and the call at 0x00bba794. The port is declared with the receiver in ECX on that basis alone.
- abi_derived classifies the EAX return as register_class aggregate_unknown; the listing shows two plain address computations. The divergence is recorded rather than resolved against the derived projection.
