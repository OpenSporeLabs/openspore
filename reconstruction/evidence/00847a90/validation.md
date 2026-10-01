# Validation 0x00847a90

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_canvas_wave6/app_canvas_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 7-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 1 intra-procedural jump(s) target inside the recovered body span 0x00847a90..0x00847aa2 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00847a9e; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00847a90; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `WARN` | `partial` | the complete 7-instruction listing names 1 data address(es) (0x13cc664) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field field_74 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x74), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (7 of 7 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 7-instruction listing lie inside the recovered body span 0x00847a90..0x00847aa2, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 7-instruction body names 1 indirect transfer(s): 0x00847aa2 is INDIRECT_NON_VTABLE; the machine parse consumed 7 of 7 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00847aa2), so the dispatch's identity is not established: the target is the memory operand [0x013cc664], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `de9ce066e7e6d9374c175aaf985fb8022d60c1514a720f3e9621a0496c0c1f2b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ec6f0f8299d851c182d51c53ae21f499f48f17e0daa06556a5ce91c5017c8af2`
- Pack digest quoted by the briefing: `de9ce066e7e6d9374c175aaf985fb8022d60c1514a720f3e9621a0496c0c1f2b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `platform active-handle and window lifetime remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- platform active-handle and window lifetime remain gated
- runtime validation not run
