# Validation 0x00961300

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 64-instruction listing name the same 2 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00961300..0x0096138f are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0096135b, 0x00961380; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00961300; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 64-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 7 member(s) (children_38, flags_28, manager_30, next) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 64-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=64, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x4, 0x30, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 2 displacement(s) the record does not enumerate (0x4, 0x38), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (64 of 64 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 9 conditional branch target(s) in the complete 64-instruction listing lie inside the recovered body span 0x00961300..0x0096138f, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 64-instruction body names 1 indirect transfer(s): 0x0096131d dispatches slot 0x10 through the table word in EAX; the machine parse consumed 64 of 64 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 64 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x10, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6156e38bfe31040cb5ae184c5b342f9ac5d34ae98eefcd8ca71f49990a91e8df`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `792c997f283563c84c45752f55846fea638bf91a8c35056c5f8a6a13915db6f4`
- Pack digest quoted by the briefing: `6156e38bfe31040cb5ae184c5b342f9ac5d34ae98eefcd8ca71f49990a91e8df`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `intrusive-list ownership, parent query, and manager port behavior remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- intrusive-list ownership, parent query, and manager port behavior remain gated
- runtime validation not run
