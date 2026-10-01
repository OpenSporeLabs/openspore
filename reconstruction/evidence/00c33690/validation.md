# Validation 0x00c33690

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_e3_empire_state_wave2/empire_state_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 130-instruction listing name the same 9 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00c33690..0x00c33812 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c33701, 0x00c337b7; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 11 outgoing call edge row(s) over 9 distinct address(es) for 0x00c33690; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 130-instruction listing names 2 data address(es) (0x1667bac, 0x1667bae) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 11 member(s) (color, leaf, left, name) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 130-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=130, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 6 displacement(s) to the receiver as proven (0xc, 0x18, 0x20, 0x3c, 0x88, 0x8c) and 1 more only on one arm of a branch, which is a may and grounds nothing (0x2c); the machine-derived receiver record enumerates 3 displacement(s) (0x20, 0x88, 0x8c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 3 displacement(s) the record does not enumerate (0xc, 0x18, 0x3c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (130 of 130 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 17 conditional branch target(s) in the complete 130-instruction listing lie inside the recovered body span 0x00c33690..0x00c33812, so the branch graph is closed inside it; the source span declares for, if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 130-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1fe237e753cb553c93edd6b6e33d873974040f57e6e17ebebfd4bd71a4ff041a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9f26c03d3012f9480ab87b1ec3437d38159974af22bd4b2c962c4b1e49f3d2ee`
- Pack digest quoted by the briefing: `1fe237e753cb553c93edd6b6e33d873974040f57e6e17ebebfd4bd71a4ff041a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-profile-setter-00c33690`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- gate-profile-setter-00c33690
- runtime validation not run
