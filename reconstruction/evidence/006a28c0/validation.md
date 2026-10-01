# Validation 0x006a28c0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a28c0; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field field_00, field_38 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x0, 0x28, 0x38), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 13-instruction listing lie inside the recovered body span 0x006a28c0..0x006a28e0, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names 1 indirect transfer(s): 0x006a28cf dispatches slot 0x28 through the table word in EDX; the machine parse consumed 13 of 13 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c6fa38e372bfc53ab949777c0a4b2b08f01dff22a7e0b2f3f38c974738b2db47`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9b45a69c366aa9ed4b9e1acf10100857185cb1f824f5e8bc99cd52f2172ea4b3`
- Pack digest quoted by the briefing: `c6fa38e372bfc53ab949777c0a4b2b08f01dff22a7e0b2f3f38c974738b2db47`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `list and parent vtable implementations plus returned property lifetime remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- list and parent vtable implementations plus returned property lifetime remain gated
- runtime validation not run
