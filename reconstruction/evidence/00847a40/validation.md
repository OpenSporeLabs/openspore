# Validation 0x00847a40

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00847a40; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `WARN` | `partial` | the complete 8-instruction listing names 1 data address(es) (0x13cc118) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field field_8 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x8), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 8-instruction listing lie inside the recovered body span 0x00847a40..0x00847a61, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 8-instruction body names 2 indirect transfer(s): 0x00847a53 is INDIRECT_NON_VTABLE; 0x00847a61 is INDIRECT_NON_VTABLE; the machine parse consumed 8 of 8 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2, so the dispatch is visible in the machine listing but is not proven: 2 of the 2 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00847a53, 0x00847a61), so the dispatch's identity is not established: the target is the memory operand [0x013cc118], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9b0d6421a0d15b8d0b438aae11f60184734aec1a95f67429a456b8933b6aa015`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a8a4cadf8e3053b75b954781e5dbcd783c82157dc914b431cfad900801fc61f5`
- Pack digest quoted by the briefing: `9b0d6421a0d15b8d0b438aae11f60184734aec1a95f67429a456b8933b6aa015`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `platform thread-state and canvas ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- platform thread-state and canvas ownership remain gated
- runtime validation not run
