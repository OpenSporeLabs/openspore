# Validation 0x011f9710

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_presentation/presentation_boundary.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 173-instruction listing name the same 3 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x011f9710..0x011f9914 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x011f97b3, 0x011f9830, 0x011f988e; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x011f9710; 6 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 173-instruction listing names 10 data address(es) (0x15d0934, 0x16f6568, 0x16f85a8, 0x16f89d0, 0x16f8afc, 0x16f9110, 0x16f913c, 0x1718610, 0x1718614, 0x1718618) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 12 member(s) (baseVertexIndex, firstIndex, firstVertex, pDXBuffer) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 2 displacement(s) declared alongside (0xf, 0xd4) are reported above with the witness each one rests on; the 173-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=173, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x10, 0x24) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x10, 0x24), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (173 of 173 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 17 conditional branch target(s) in the complete 173-instruction listing lie inside the recovered body span 0x011f9710..0x011f9914, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 173-instruction body names 6 indirect transfer(s): 0x011f9728 is FUNCTION_POINTER; 0x011f97d6 is INDIRECT_NON_VTABLE; 0x011f9840 is INDIRECT_NON_VTABLE; 0x011f98ad is INDIRECT_NON_VTABLE; 0x011f98e8 is INDIRECT_NON_VTABLE; 0x011f9907 is INDIRECT_NON_VTABLE; the machine parse consumed 173 of 173 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6, so the dispatch is visible in the machine listing but is not proven: 1 of the 6 indirect transfer(s) classify as FUNCTION_POINTER (0x011f9728), so the dispatch's identity is not established: EAX is loaded from [EAX + 0x14], but EAX is defined by load earlier in the listing, so the word it names is not shown to be a table word and 5 of the 6 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x011f97d6, 0x011f9840, 0x011f98ad, 0x011f98e8, 0x011f9907), so the dispatch's identity is not established: the target is the memory operand [EDI + 0x190], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3e7d9bd2d0fef2556e711e6b722b58fa8bbb260983dea4eb5c115c4ae6de1d03`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1de8b3643efbb192bf3ea1ba8108dbf8d78cdca707e88c939e03c8c6389bd6c3`
- Pack digest quoted by the briefing: `3e7d9bd2d0fef2556e711e6b722b58fa8bbb260983dea4eb5c115c4ae6de1d03`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-renderware-d3d-stream-draw-and-index-state`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- D3D runtime result behavior
- What are the concrete VertexBuffer description and native-buffer ownership rules?
- What concrete preparation does the callback at vtable slot +0x14 perform, and what does the active-state +0xd4 bit mean?
- What runtime invariant keeps mesh vertex-buffer counts within the verified four-triple capacity?
- active-state callback and +0xd4 flag meaning
- four-stream capacity invariant
- gate-renderware-d3d-stream-draw-and-index-state
- vertex and index buffer ownership
