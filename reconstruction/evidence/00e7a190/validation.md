# Validation 0x00e7a190

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06c_cell_behavior_dispatch/cell_behavior_dispatch.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 265-instruction listing name the same 18 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00e7a190..0x00e7a45b are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e7a1c5; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 21 outgoing call edge row(s) over 18 distinct address(es) for 0x00e7a190; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 18 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 265-instruction listing names 2 data address(es) (0x1485378, 0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 4 member(s) (ai_easy, ai_hard, game, normal) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 265-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=265, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x112, 0x18c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x0, 0x112, 0x16c, 0x18c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x16c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 13 source constant(s) are absent from the machine listing: 0x1001, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, 0x1008, 0x1009, 0x100a, 0x100b, 0x100c, 0x100d, 0x100e |
| CONTROL FLOW | `PASS` | `complete` | all 17 conditional branch target(s) in the complete 265-instruction listing lie inside the recovered body span 0x00e7a190..0x00e7a45b, so the branch graph is closed inside it; the source span declares if, switch, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 265-instruction body names 1 indirect transfer(s): 0x00e7a333 is INDIRECT_NON_VTABLE; the machine parse consumed 265 of 265 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00e7a333), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0xe7a45c], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 2 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `571109c7c062cb6ffade3be590535c737bc318cbf1bf8ed96876192098e0796e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `fd45cb2a6f3eb895a9e368fa360891e490f7126f8f81db45f24a752f2d422884`
- Pack digest quoted by the briefing: `571109c7c062cb6ffade3be590535c737bc318cbf1bf8ed96876192098e0796e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-cell-behavior-dispatch`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does any unresolved native callee invalidate the cell pointer or otherwise change later fields before the target returns?
- Should the incoming float remain an opaque update scalar, or can another package provide a stronger canonical type and name?
- What are the exact return, register, stack-cleanup, mutation, and failure contracts of the 17 unresolved native callees?
- What concrete canonical types and lifetime boundaries correspond to ObservedCellCellResource and CellObjectData?
- What exact machine arguments are consumed by 0x00e67c40 and 0x00e6f800 in the mode-3 special path?
- What runtime values reach each early gate, special branch, and dispatch selector?
- What stable meanings, if any, belong to difficulty, profile type, profile+0x18, profile+0x1c, profile+0x40, profile+0x44, and dispatch selector values?
- canonical meaning of the incoming four-byte float
- concrete canonical types and lifetime boundaries for ObservedCellCellResource and ObservedCellObjectData
- exact machine arguments consumed by 0x00e67c40 and 0x00e6f800 in the mode-3 special path
- exact return, register, stack-cleanup, mutation, and failure contracts of the 17 unresolved native callees
- gate-cell-behavior-dispatch
- runtime values reaching each early gate, special branch, and dispatch selector
- stable meanings for difficulty, profile type, profile offsets, and dispatch selectors
- whether any unresolved native callee invalidates the cell pointer or changes later fields
