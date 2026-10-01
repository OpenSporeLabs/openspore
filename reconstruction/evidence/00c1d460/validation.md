# Validation 0x00c1d460

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c4_creature_wave3/creature_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): flow_not_modelled: the linear ESP walk ends at +28, so the listing is not one path |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 121-instruction listing name the same 4 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 4 distinct address(es) for 0x00c1d460; 7 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 2 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 121-instruction listing names 5 data address(es) (0x1485720, 0x168d964, 0x168d988, 0x168d98c, 0x168d990) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field m, property_count, property_flags, rotation and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (121 of 121 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 121-instruction listing lie inside the recovered body span 0x00c1d460..0x00c1d5d3, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 121-instruction body names 9 indirect transfer(s): 0x00c1d486 dispatches slot 0x4 through the table word in EAX; 0x00c1d49a dispatches slot 0x2c through the table word in EAX; 0x00c1d4cb dispatches slot 0x0 through the table word in EDX; 0x00c1d4da dispatches slot 0x4 through the table word in EDX; 0x00c1d541 dispatches slot 0x2c through the table word in EAX; 0x00c1d56e dispatches slot 0x30 through the table word in EDX; 0x00c1d5a6 dispatches slot 0x18 through the table word in EDX; 0x00c1d5b8 dispatches slot 0x8 through the table word in EAX; 0x00c1d5c9 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 121 of 121 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is SRET_SUSPECTED and the source span declares return type 'OpaqueVisualEffect*': the ABI envelope records a hidden-pointer return hypothesis (suspected), so the return register holds an address rather than the value and no width read off it would be a claim about the wrong value. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1476e8b00e79aabac2001c7be6d3503affb827a19dc931c6ed6ad2f4b89ceead`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `19669a15ef2858c2a8c33aa79a2a4b137b3c071cccfbc44da899bdaffe28f7cb`
- Pack digest quoted by the briefing: `1476e8b00e79aabac2001c7be6d3503affb827a19dc931c6ed6ad2f4b89ceead`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Confirm the handle reference-count pair on a live effect, including whether Start with argument 0 can clear the out slot that the cleanup reloads.`, `Exercise the failure path with a service that returns false while writing a non-null handle, to confirm the Start and Release still run.`, `No original-process trace, differential run under Wine, or runtime validation has been performed.`, `Observe a real service create in an original process to confirm the instance id and group id contract and whether the group id is ever non-zero.`, `Observe a real vtable slot +0x18 submission to learn the concrete property block layout and whether the pointer escapes.`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Confirm the handle reference-count pair on a live effect, including whether Start with argument 0 can clear the out slot that the cleanup reloads.
- Exercise the failure path with a service that returns false while writing a non-null handle, to confirm the Start and Release still run.
- No original-process trace, differential run under Wine, or runtime validation has been performed.
- Observe a real service create in an original process to confirm the instance id and group id contract and whether the group id is ever non-zero.
- Observe a real vtable slot +0x18 submission to learn the concrete property block layout and whether the pointer escapes.
- runtime validation not run
