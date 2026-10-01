# Validation 0x00834fa0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg18_ui_space/zoom_boundary_00834fa0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 259-instruction listing name the same 11 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00834fa0..0x0083527a are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00835089, 0x00835215; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 11 outgoing call edge row(s) over 11 distinct address(es) for 0x00834fa0; 8 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 11 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 259-instruction listing names 7 data address(es) (0x14007f8, 0x164f234, 0x164f238, 0x164f23c, 0x164f240, 0x164f244, 0x164f248) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 1 member(s) (bytes) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 4 displacement(s) declared alongside (0x30, 0x48, 0x6c, 0x20c) are reported above with the witness each one rests on; the 259-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=259, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x48, 0x68, 0x6c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x48, 0x4c, 0x50, 0x54, 0x64, 0x68, 0x6c, 0x70, 0x74), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 6 of those (0x4c, 0x50, 0x54, 0x64, 0x70, 0x74) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (259 of 259 instruction(s), 0 unparsed) and all 18 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 32 conditional branch target(s) in the complete 259-instruction listing lie inside the recovered body span 0x00834fa0..0x0083527a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 259-instruction body names 19 indirect transfer(s): 0x00834fba dispatches slot 0x10 through the table word in EAX; 0x00834fc3 dispatches slot 0x10 through the table word in EDX; 0x0083502e dispatches slot 0x0 through the table word in EDX; 0x0083503e dispatches slot 0x4 through the table word in EDX; 0x00835048 dispatches slot 0x10 through the table word in EDX; 0x00835051 dispatches slot 0x30 through the table word in EDX; 0x0083509a dispatches slot 0x0 through the table word in EDX; 0x008350aa dispatches slot 0x4 through the table word in EDX; 0x008350b4 dispatches slot 0x10 through the table word in EDX; 0x008350ce dispatches slot 0x0 through the table word in EDX; 0x008350e2 dispatches slot 0x4 through the table word in EDX; 0x0083510f dispatches slot 0xd8 through the table word in EDX; 0x0083511c dispatches slot 0x7c through the table word in EDX; 0x00835129 dispatches slot 0x7c through the table word in EDX; 0x0083513e dispatches slot 0x108 through the table word in EDX; 0x00835155 dispatches slot 0x0 through the table word in EDX; 0x00835165 dispatches slot 0x4 through the table word in EDX; 0x00835181 dispatches slot 0x104 through the table word in EDX; 0x00835267 dispatches slot 0x7c through the table word in EDX; the machine parse consumed 259 of 259 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 19. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `922c00fd037b45f64f30465a70c546ac2bed84e26cc7757ad6aa673c3b1438a1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c35512cf7d989935d9dfc0d1ffeee8bb53adf363da83b6a2c0d4cd480970c75f`
- Pack digest quoted by the briefing: `922c00fd037b45f64f30465a70c546ac2bed84e26cc7757ad6aa673c3b1438a1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-ui-space-text-zoom-rebind`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete owners and vtable targets for the UI objects remain unresolved.
- SpaceUiVtable callback and service ownership
- The exact behavior of a null factory result is a raw downstream dereference boundary, not a safe fallback contract.
- The semantic meanings of mode, state, and the three resource words remain opaque.
- gate-ui-space-text-zoom-rebind
- ownership contract of the +0x70 object
- runtime meaning of the three resource words
