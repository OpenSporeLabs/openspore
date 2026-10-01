# Validation 0x00be1fb0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c3_tribe_civ_wave2/tribe_civilization_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 75-instruction listing name the same 4 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00be1fb0..0x00be206b are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00be2030; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 4 distinct address(es) for 0x00be1fb0; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 4 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 75-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 4 member(s) (bytes, capacity, end, vtable) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 3 displacement(s) declared alongside (0x34, 0x120, 0x354) are reported above with the witness each one rests on; the 75-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=75, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x354, 0x358, 0x35c) and 1 more only on one arm of a branch, which is a may and grounds nothing (0x358); the machine-derived receiver record enumerates 3 displacement(s) (0x120, 0x358, 0x35c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x120) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x354), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (75 of 75 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 75-instruction listing lie inside the recovered body span 0x00be1fb0..0x00be206b, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 75-instruction body names 6 indirect transfer(s): 0x00be1fd6 dispatches slot 0xc through the table word in EDX; 0x00be1ff0 dispatches slot 0x0 through the table word in EDX; 0x00be2018 dispatches slot 0x0 through the table word in EAX; 0x00be203b dispatches slot 0x4 through the table word in EAX; 0x00be205a dispatches slot 0x2c through the table word in EAX; 0x00be2062 dispatches slot 0x38 through the table word in EBP; the machine parse consumed 75 of 75 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x2c, 0x38, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4a5adc0c69ab672e42ce673d341ef2088843bbbf8a4378d6b367c45ba4915748`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6dbfea34e37915df6a5739727a63330957c6ed904f83c4e53e3fd9b70ab5cd39`
- Pack digest quoted by the briefing: `4a5adc0c69ab672e42ce673d341ef2088843bbbf8a4378d6b367c45ba4915748`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-city-add-building-00be1fb0`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No population, persistence, or tribe-state owner is inferred from the city/building offsets.
- The 0x00b20c60 service object and its internal linked-list/ref operations are not reclassified as city or building ownership by this target.
- The 0x00bd2310 helper's complete owner graph and runtime release behavior are outside this body.
- The concrete root, factory, building, city-owner, and building-owner types remain opaque.
- The native vector allocator's failure behavior is not replaced with a target-local error policy.
- gate-city-add-building-00be1fb0
- runtime validation not run
