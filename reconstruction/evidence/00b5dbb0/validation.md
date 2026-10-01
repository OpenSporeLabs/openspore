# Validation 0x00b5dbb0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave8/game_mode_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 269-instruction listing name the same 21 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00b5dbb0..0x00b5df04 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00b5dc6e, 0x00b5dda1, 0x00b5ded7; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 27 outgoing call edge row(s) over 21 distinct address(es) for 0x00b5dbb0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 20 of them and no others |
| GLOBALS | `WARN` | `partial` | 6 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 3 member(s) (begin, end, vtable) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 269-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=269, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x5c, 0x60) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x5c, 0x60), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (269 of 269 instruction(s), 0 unparsed) and all 12 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 34 conditional branch target(s) in the complete 269-instruction listing lie inside the recovered body span 0x00b5dbb0..0x00b5df04, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 269-instruction body names 11 indirect transfer(s): 0x00b5dbc5 dispatches slot 0x48 through the table word in EDX; 0x00b5dbdc dispatches slot 0x14 through the table word in EDX; 0x00b5dc9a dispatches slot 0x18 through the table word in EDX; 0x00b5dcac dispatches slot 0x18 through the table word in EDX; 0x00b5dcbe dispatches slot 0x18 through the table word in EDX; 0x00b5dcd0 dispatches slot 0x18 through the table word in EDX; 0x00b5dce2 dispatches slot 0x18 through the table word in EDX; 0x00b5dd0d dispatches slot 0x18 through the table word in EAX; 0x00b5dd54 is INDIRECT_NON_VTABLE; 0x00b5de01 dispatches slot 0x2c through the table word in EDX; 0x00b5dedf dispatches slot 0x58 through the table word in EAX; the machine parse consumed 269 of 269 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 11, so the dispatch is visible in the machine listing but is not proven: 1 of the 11 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00b5dd54), so the dispatch's identity is not established: the target is the memory operand [ECX*0x4 + 0xb5df08], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch and the source span states slot displacement(s) 0x14, 0x48, 0x58, 0x685f4af and the machine reads 0x14, 0x18, 0x2c, 0x48, 0x58, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c15fceed4b51625a43ad01bbc9cf17a22cfbd4b1bdd0547bcb023ce070ce7f00`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4d40fc3778c931c63a9c4658cb3caba28e463b3e0ad2d2d533497b95d0ba3c16`
- Pack digest quoted by the briefing: `c15fceed4b51625a43ad01bbc9cf17a22cfbd4b1bdd0547bcb023ce070ce7f00`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Bind the live transition, telemetry, renderer, species-manager, service, and text helper implementations before runtime validation; the model test is not an original-process trace.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Bind the live transition, telemetry, renderer, species-manager, service, and text helper implementations before runtime validation; the model test is not an original-process trace.
- concrete runtime owners and values remain unresolved
