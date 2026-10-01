# Validation 0x00c86760

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg14_a3_world_wave3/world_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 259-instruction listing name the same 20 direct transfer target(s); 7 intra-procedural jump(s) target inside the recovered body span 0x00c86760..0x00c86a95 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c867c1, 0x00c8680e, 0x00c8688f, 0x00c868d2, 0x00c86947, 0x00c869ab, 0x00c86a1f; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 28 outgoing call edge row(s) over 20 distinct address(es) for 0x00c86760; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 259-instruction listing names 7 data address(es) (0x145e06c, 0x1473470, 0x1473474, 0x1579d10, 0x1694c10, 0x1694c14, 0x1694c18) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 14 member(s) (angular_scale_ac, begin, body_kind_38, data_00) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 259-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=259, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xc) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0xc, 0x28, 0x2c, 0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x28, 0x2c, 0x38) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (259 of 259 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 26 conditional branch target(s) in the complete 259-instruction listing lie inside the recovered body span 0x00c86760..0x00c86a95, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 259-instruction body names 7 indirect transfer(s): 0x00c867d1 dispatches slot 0x0 through the table word in EAX; 0x00c867e0 dispatches slot 0x4 through the table word in EAX; 0x00c86803 dispatches slot 0x0 through the table word in EAX; 0x00c869e5 dispatches slot 0xbc through the table word in EAX; 0x00c86a0c dispatches slot 0xbc through the table word in EAX; 0x00c86a2d dispatches slot 0xc0 through the table word in EAX; 0x00c86a83 dispatches slot 0xc0 through the table word in EAX; the machine parse consumed 259 of 259 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `245dcfc1b3111a730bc567bb5af96eb78560896780f50df7f192bb817c2115fa`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5f8357a2dcbb9dfeedbe785c1f3b867be2bec032ccf222f2e6b2aa68b3c2108f`
- Pack digest quoted by the briefing: `245dcfc1b3111a730bc567bb5af96eb78560896780f50df7f192bb817c2115fa`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Runtime population of the three transform words and indexed star-radius table remains outside this worker boundary.
- The binary-or-asteroid and asteroid-belt services are preserved as separate unresolved ports.
- The concrete owner and domain meaning of the system, star, planet, and materialization services remain opaque.
- runtime validation not run
