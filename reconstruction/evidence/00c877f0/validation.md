# Validation 0x00c877f0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_inventory_entry.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 57-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x00c877f0; 6 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 57-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 6 member(s) (description, detail_description, item_cost, property_list) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 57-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=57, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x30) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x24, 0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x0, 0x24) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (57 of 57 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 57-instruction listing lie inside the recovered body span 0x00c877f0..0x00c87879, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 57-instruction body names 4 indirect transfer(s): 0x00c8780a dispatches slot 0x0 through the table word in EAX; 0x00c8781a dispatches slot 0x4 through the table word in EAX; 0x00c87852 dispatches slot 0x24 through the table word in EDX; 0x00c87874 dispatches slot 0x4c through the table word in EDX; the machine parse consumed 57 of 57 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `efa7dc2b8e32c1c81d9a9e8d4cd5d4153e7e4f1ca7ced40f7acc699dc1f7cac9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ee96e5a67cfe1bb843684a460dddd6d434dc08c337ecee53f446b9013a1b5cc2`
- Pack digest quoted by the briefing: `efa7dc2b8e32c1c81d9a9e8d4cd5d4153e7e4f1ca7ced40f7acc699dc1f7cac9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-inventory-item`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- FUN_0041ea00's non-type-10 fallback and the complete property value layout are not assigned semantics.
- The concrete target of cSpaceInventoryItem vtable +0x4c and the exact post-property side effects are not named by Ghidra.
- The full PropertyList GetProperty and localized-string ownership contracts are preserved only at the observed call boundaries.
- The live function has no direct string or global references; no event-family or lifecycle ownership is inferred from its caller set.
- gate-space-inventory-item
- item vtable owner
- localized-string ownership
- notification side effects
- property value semantics
