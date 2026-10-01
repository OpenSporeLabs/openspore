# Validation 0x0059b2f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_runtime_wave8/editor_runtime_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 35-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0059b2f0; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `WARN` | `partial` | the complete 35-instruction listing names 4 data address(es) (0x1471064, 0x15e5a0c, 0x15e5a10, 0x15e5a14) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field angle_48, creature_08, half_angle_01471064, orientation_10 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 3 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x8, 0x18, 0x1c, 0x20, 0x24, 0x44, 0x48), so it is the name alone that is uncorroborated |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 35 of 35 instruction(s) consumed, degraded=True, unparsed=1 |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 35-instruction listing lie inside the recovered body span 0x0059b2f0..0x0059b380, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 35-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `986f014f9791d0271d74cdb29e04688acd50d24b0bd93b02b2a2ceec31a3f151`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f09aaffff07a7a378390ad84b65bff991b44da26065e46de4c2f8c535d512353`
- Pack digest quoted by the briefing: `986f014f9791d0271d74cdb29e04688acd50d24b0bd93b02b2a2ceec31a3f151`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- concrete runtime owners and values remain unresolved
- required
