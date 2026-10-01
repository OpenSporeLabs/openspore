# Validation 0x004c5200

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg20_persistence_boundary/paint_job_004c5200.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 449-instruction listing names 3 data address(es) (0x13eb430, 0x15d8de8, 0x15fd918) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 449-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 449-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=449, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x0, 0x4, 0x8, 0x1c, 0x5c, 0x64, 0x68, 0x6c, 0x84), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 9 of those (0x0, 0x4, 0x8, 0x1c, 0x5c, 0x64, 0x68, 0x6c, 0x84) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (449 of 449 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 31 conditional branch target(s) in the complete 449-instruction listing lie inside the recovered body span 0x004c5200..0x004c58a7, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 449-instruction body names 5 indirect transfer(s): 0x004c5650 dispatches slot 0x4 through the table word in EDX; 0x004c568a dispatches slot 0x2c through the table word in EDX; 0x004c57f1 dispatches slot 0x64 through the table word in EAX; 0x004c587e dispatches slot 0x4 through the table word in EDX; 0x004c589a dispatches slot 0x4 through the table word in EAX; the machine parse consumed 449 of 449 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 4 passed, 3 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dad0e521f424efcc7eda01009731196f231ca1a1c11f28855ab34a93b67b59f5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `badcc3fcb7cdfd9271319e06de0f2fef5ee47633e6fe3565412a81fe1482ff2e`
- Pack digest quoted by the briefing: `dad0e521f424efcc7eda01009731196f231ca1a1c11f28855ab34a93b67b59f5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-paint-bake-submission`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The exact class identity and semantic field names of the 0x84-byte allocation are unresolved.
- The exact service ownership of IBakeManager, PropertyList, paint-system, and property-service pointers is not inferred.
- The live cEditor, cEditorSkin, EditorModel, and Model layouts are not promoted into the opaque staging types.
- defensive invalid-handle guard is not an observed original failure return
- gate-paint-bake-submission
- paint job concrete class identity
- property-list query service ownership
- runtime allocator and bake-manager outcomes
