# Validation 0x007d85b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 111-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x007d85b0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 111-instruction listing names 2 data address(es) (0x13eb844, 0x13eb90c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 7 member(s) (active_index, entries_begin, kind, mode) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 111-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=111, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x14, 0x18, 0x28) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x14, 0x18, 0x28), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (111 of 111 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 111-instruction listing lie inside the recovered body span 0x007d85b0..0x007d8732, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 111-instruction body names 4 indirect transfer(s): 0x007d8614 dispatches slot 0x1c through the table word in EAX; 0x007d867f dispatches slot 0x14 through the table word in EDX; 0x007d86a6 dispatches slot 0x18 through the table word in EDX; 0x007d8704 dispatches slot 0x14 through the table word in EAX; the machine parse consumed 111 of 111 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 2 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a184ba502b2c5a1eaf1c82bcda16be6e2b61edf02a8293e348e045454f055326`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d11bff9fc486e7d2050818661cd612e94d5513e29ed7255e9f5056437c9f145f`
- Pack digest quoted by the briefing: `a184ba502b2c5a1eaf1c82bcda16be6e2b61edf02a8293e348e045454f055326`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe concrete mode identities, notification manager publication, vtable targets, and runtime transition reachability; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe concrete mode identities, notification manager publication, vtable targets, and runtime transition reachability; runtime validation is not run.
- concrete runtime owners and values remain unresolved
