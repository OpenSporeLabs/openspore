# Validation 0x005dda30

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg10_editor_dispatch/editor_dispatch.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 281-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 281-instruction listing nevertheless reaches 8 receiver displacement(s) through ECX (0x44, 0x5c, 0x60, 0x64, 0x68, 0x6c, 0x80, 0x84), all of which the record accounts for or the listing is the better witness on; the 281-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=281, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 8 displacement(s) to the receiver as proven (0x44, 0x5c, 0x60, 0x64, 0x68, 0x6c, 0x80, 0x84) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 7 displacement(s) (0x5c, 0x60, 0x64, 0x68, 0x6c, 0x80, 0x84), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x44), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (281 of 281 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 31 conditional branch target(s) in the complete 281-instruction listing lie inside the recovered body span 0x005dda30..0x005ddd2f, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 281-instruction body names 19 indirect transfer(s): 0x005ddab1 dispatches slot 0x7c through the table word in EAX; 0x005ddace dispatches slot 0x7c through the table word in EDX; 0x005ddaeb dispatches slot 0x7c through the table word in EDX; 0x005ddb08 dispatches slot 0x7c through the table word in EDX; 0x005ddb46 dispatches slot 0x7c through the table word in EAX; 0x005ddb5b dispatches slot 0x7c through the table word in EAX; 0x005ddb70 dispatches slot 0x7c through the table word in EAX; 0x005ddb9f dispatches slot 0x7c through the table word in EAX; 0x005ddbbc dispatches slot 0x7c through the table word in EDX; 0x005ddbd9 dispatches slot 0x7c through the table word in EDX; 0x005ddbf6 dispatches slot 0x7c through the table word in EDX; 0x005ddc13 dispatches slot 0x7c through the table word in EDX; 0x005ddc39 dispatches slot 0x7c through the table word in EDX; 0x005ddc61 dispatches slot 0x7c through the table word in EDX; 0x005ddc7e dispatches slot 0x7c through the table word in EDX; 0x005ddc9b dispatches slot 0x7c through the table word in EDX; 0x005ddcb8 dispatches slot 0x7c through the table word in EDX; 0x005ddccd dispatches slot 0x7c through the table word in EDX; 0x005ddce2 dispatches slot 0x7c through the table word in EDX; the machine parse consumed 281 of 281 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 19. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 14 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 14 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `03a842e3746aa9e43e42ce8f279f199d0e001fe53ed46b08d662f21968a20edd`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7bd703a367762779866082fdb1ba67f313b281db2e5b939dd750ae33270469e0`
- Pack digest quoted by the briefing: `03a842e3746aa9e43e42ce8f279f199d0e001fe53ed46b08d662f21968a20edd`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `editor_mode_transition_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What are the two 0x7c arguments semantically beyond their observed numeric widths?
- What concrete pointer-like owner or return semantics, if any, can be recovered for 0x00574a20 without asserting a boolean?
- What concrete type owns the 0x7c vtable slot?
- What semantic names, if any, belong to mode values 0, 1, and 2?
- editor concrete type
- editor_mode_transition_observation
- event ordering
- manager lookup results
- mode-specific virtual implementations
