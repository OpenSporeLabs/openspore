# Validation 0x00aeb160

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 87-instruction listing name the same 3 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00aeb160..0x00aeb23a are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00aeb191, 0x00aeb227; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00aeb160; 5 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 3 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 87-instruction listing names 1 data address(es) (0x13f09b4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 2 member(s) (capacity, end) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 87-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=87, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x24, 0x28, 0x2c) and 1 more only on one arm of a branch, which is a may and grounds nothing (0x28); the machine-derived receiver record enumerates 2 displacement(s) (0x28, 0x2c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x24), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (87 of 87 instruction(s), 0 unparsed) and all 10 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 87-instruction listing lie inside the recovered body span 0x00aeb160..0x00aeb23a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 87-instruction body names 5 indirect transfer(s): 0x00aeb1c9 dispatches slot 0x0 through the table word in EDX; 0x00aeb1d9 dispatches slot 0x4 through the table word in EDX; 0x00aeb1f5 dispatches slot 0x0 through the table word in EAX; 0x00aeb214 dispatches slot 0x0 through the table word in EAX; 0x00aeb232 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 87 of 87 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4c669a4a5458e4d0d1b10af269112b78c3bfb2d5813718513a490ef691e9e241`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `dd9cfa6477254252ecd5997cab00f59524066e972600457cc8a1a8de00226370`
- Pack digest quoted by the briefing: `4c669a4a5458e4d0d1b10af269112b78c3bfb2d5813718513a490ef691e9e241`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-comm-event-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The exact cCommManager field names for the vector at +0x24 remain unresolved because the imported layout conflicts with the live accesses.
- The semantic names of all seven opaque payload words are not asserted.
- event vtable implementations
- gate-space-comm-event-lifecycle
- manager vector field ownership
- payload word meanings
