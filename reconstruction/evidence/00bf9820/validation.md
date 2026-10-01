# Validation 0x00bf9820

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 480-instruction listing name the same 28 direct transfer target(s), including a target reached only by a jump; 5 intra-procedural jump(s) target inside the recovered body span 0x00bf9820..0x00bf9e6d are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00bf99d0, 0x00bf99ed, 0x00bf9b00, 0x00bf9c44, 0x00bf9d25; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 63 outgoing call edge row(s) over 28 distinct address(es) for 0x00bf9820; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 9 address-named callee(s), against the 63 outgoing call edge row(s) and 28 distinct callee(s) the export records; 19 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00bc3130, 0x00bc3190, 0x00bd81d0, 0x00bd8210, 0x00bdb930, 0x00bddda0, 0x00bef710, 0x00beff90, 0x00bf00a0, 0x00bf0c60, 0x00bf2100, 0x00bf2170 and 7 more; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 63 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 480-instruction listing names 9 data address(es) (0x13ec4d0, 0x13eeda0, 0x1470f1c, 0x1477fbc, 0x156f89c, 0x1654c05, 0x168c514, 0x168c518, 0x168c51c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 3 member(s) (begin, end, ptr) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 480-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=480, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x9c, 0xa0, 0x468) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x89, 0x93, 0x98, 0x9c, 0xa0, 0x298, 0x468, 0x4ac, 0x4b0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 6 of those (0x89, 0x93, 0x98, 0x298, 0x4ac, 0x4b0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0xffffffff |
| CONTROL FLOW | `PASS` | `complete` | all 53 conditional branch target(s) in the complete 480-instruction listing lie inside the recovered body span 0x00bf9820..0x00bf9e6d, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 480-instruction body names 14 indirect transfer(s): 0x00bf98a8 dispatches slot 0x4 through the table word in EDX; 0x00bf996d dispatches slot 0x2c through the table word in EDX; 0x00bf99a2 dispatches slot 0x2c through the table word in EDX; 0x00bf9a32 dispatches slot 0x2c through the table word in EDX; 0x00bf9a3d dispatches slot 0x2c through the table word in EDX; 0x00bf9b21 dispatches slot 0x2c through the table word in EAX; 0x00bf9ba7 dispatches slot 0x2c through the table word in EAX; 0x00bf9bdd dispatches slot 0x2c through the table word in EAX; 0x00bf9be7 dispatches slot 0x2c through the table word in EAX; 0x00bf9cb7 dispatches slot 0x2c through the table word in EAX; 0x00bf9d03 dispatches slot 0x2c through the table word in EAX; 0x00bf9d30 dispatches slot 0x2c through the table word in EAX; 0x00bf9e3f dispatches slot 0x0 through the table word in EAX; 0x00bf9e52 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 480 of 480 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 14. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e0020591ecc33923c8111f5d0291fd9505381fe6f12f8171f582f3a2f562a845`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6ccc1cf27c944fbbac12d2d919a6bbe133d3b776688338c0fb5dac02e63af467`
- Pack digest quoted by the briefing: `e0020591ecc33923c8111f5d0291fd9505381fe6f12f8171f582f3a2f562a845`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
