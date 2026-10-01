# Validation 0x008dcab0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_record_io_wave6/pkg_record_io_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 69-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x008dcab0; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 69-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 1 member(s) (bytes) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 1 displacement(s) declared alongside (0x20) are reported above with the witness each one rests on; the 69-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=69, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 5 displacement(s) to the receiver as proven (0x4, 0x20, 0x40, 0x44, 0x48) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x-4, 0xc, 0x40, 0x44, 0x48), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x-4, 0xc) the scan does not attribute to the receiver, and the listing governs there; the listing shows 2 displacement(s) the record does not enumerate (0x4, 0x20), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (69 of 69 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 13 conditional branch target(s) in the complete 69-instruction listing lie inside the recovered body span 0x008dcab0..0x008dcb5f, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 69-instruction body names 1 indirect transfer(s): 0x008dcb5a dispatches slot 0x28 through the table word in EAX; the machine parse consumed 69 of 69 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x28, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a29bb2fdbc7c4f07005c5f0a1f4d3c5fd4c31e9b258ffdba5684096f5a38eec3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `18b3c8d7d5386572ae819cb2b6edfb88dcb6bb5b235badcdd2a5ceea7bb17fdf`
- Pack digest quoted by the briefing: `a29bb2fdbc7c4f07005c5f0a1f4d3c5fd4c31e9b258ffdba5684096f5a38eec3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- prepare/read ports, embedded stream, allocator, and runtime limit ownership remain gated
- runtime validation not run
