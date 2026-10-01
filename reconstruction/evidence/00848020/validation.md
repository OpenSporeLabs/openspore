# Validation 0x00848020

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 78-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 9 outgoing call edge row(s) over 1 distinct address(es) for 0x00848020; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; 8 of those rows name an external import rather than an address and are not address-comparable, as in the projection; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 11 member(s) (field_10, field_4d, field_4e, field_4f) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 78-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=78, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x74) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x4d, 0x4e, 0x4f, 0x70, 0x74, 0x80, 0x8c, 0x90, 0x94), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 8 of those (0x4d, 0x4e, 0x4f, 0x70, 0x80, 0x8c, 0x90, 0x94) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (78 of 78 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 78-instruction listing lie inside the recovered body span 0x00848020..0x008480fa, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 78-instruction body names 8 indirect transfer(s): 0x00848055 is INDIRECT_NON_VTABLE; 0x00848068 is INDIRECT_NON_VTABLE; 0x00848078 is INDIRECT_NON_VTABLE; 0x00848084 is INDIRECT_NON_VTABLE; 0x0084809b is INDIRECT_NON_VTABLE; 0x008480c1 is FUNCTION_POINTER; 0x008480d3 is FUNCTION_POINTER; 0x008480e8 is FUNCTION_POINTER; the machine parse consumed 78 of 78 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 8, so the dispatch is visible in the machine listing but is not proven: 3 of the 8 indirect transfer(s) classify as FUNCTION_POINTER (0x008480c1, 0x008480d3, 0x008480e8), so the dispatch's identity is not established: EDI is loaded straight from the absolute address of the operand, with no base register, so the listing shows a data-segment function pointer and no object and 5 of the 8 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00848055, 0x00848068, 0x00848078, 0x00848084, 0x0084809b), so the dispatch's identity is not established: the target is the memory operand [0x013cc638], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1f437f003f5d77997de52764091e0112f1be70397e53d297fe62fc2581f1369f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5b1d053619cfe1df782050c1594686ad96ea96cbf0033349dd2cd283dd1136cc`
- Pack digest quoted by the briefing: `1f437f003f5d77997de52764091e0112f1be70397e53d297fe62fc2581f1369f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `platform handles, dispatch records, global state, and teardown ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- platform handles, dispatch records, global state, and teardown ownership remain gated
- runtime validation not run
