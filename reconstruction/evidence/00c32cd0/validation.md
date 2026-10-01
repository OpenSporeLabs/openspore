# Validation 0x00c32cd0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 404-instruction listing name the same 18 direct transfer target(s); 7 intra-procedural jump(s) target inside the recovered body span 0x00c32cd0..0x00c3328e are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c32ceb, 0x00c32d60, 0x00c32ec0, 0x00c3304a, 0x00c330b8, 0x00c3314d, 0x00c3316b; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 36 outgoing call edge row(s) over 18 distinct address(es) for 0x00c32cd0; 34 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 36 outgoing call edge row(s) and 18 distinct callee(s) the export records; 18 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x004232c0, 0x005c65e0, 0x00885c90, 0x00b1fdb0, 0x00b3d2a0, 0x00b6e1e0, 0x00b6e4b0, 0x00b6f0c0, 0x00b6f140, 0x00b6f180, 0x00ba6d80, 0x00ba9370 and 6 more; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 36 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 404-instruction listing names 10 data address(es) (0x13eb1bc, 0x13f1cac, 0x146b68c, 0x1471064, 0x1572b54, 0x1572b58, 0x1572b5c, 0x168de78, 0x168de7c, 0x168de80) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 17 member(s) (begin, capacity, color_30, color_4ec) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 404-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=404, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 7 displacement(s) (0x10, 0x30, 0x34, 0x38, 0x50, 0x84, 0xb0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 6 of those (0x30, 0x34, 0x38, 0x50, 0x84, 0xb0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0xffffffff |
| CONTROL FLOW | `PASS` | `complete` | all 33 conditional branch target(s) in the complete 404-instruction listing lie inside the recovered body span 0x00c32cd0..0x00c3328e, so the branch graph is closed inside it; the source span declares for, if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 404-instruction body names 1 indirect transfer(s): 0x00c33262 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 404 of 404 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e8f1ffd0e83fe67a5735f83642104c59a028cabf09512e05bd7298c6a0910c90`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `565d723b0c8ee355ddbd172f1978974f280831a76ce2421ec0b753aba998aabb`
- Pack digest quoted by the briefing: `e8f1ffd0e83fe67a5735f83642104c59a028cabf09512e05bd7298c6a0910c90`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
