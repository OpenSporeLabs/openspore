# Validation 0x006a3400

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `FAIL` | `partial` | unresolved ABI conflict derived_vs_persisted; the validator will not pick a winner |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 10-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006a3400; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 10-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 4 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (10 of 10 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 10-instruction listing lie inside the recovered body span 0x006a3400..0x006a341f, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 10-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is SRET_SUSPECTED and the source span declares return type 'TargetWord': the ABI envelope records a hidden-pointer return hypothesis (suspected), so the return register holds an address rather than the value and no width read off it would be a claim about the wrong value. No verdict is available on this state and none is claimed. |

Static evidence basis: 6 of 8 static checks evaluated, 5 passed, 2 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `609a338921fd044a2eac3e91b7c3fdcde31fadedda1c8f1271f3682b883a0700`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `05355aea3bafbf9b14b523a563a3be3820eb21cd9f0e2f81f98fd7ccce15ca57`
- Pack digest quoted by the briefing: `609a338921fd044a2eac3e91b7c3fdcde31fadedda1c8f1271f3682b883a0700`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do callers rely on a particular count return convention beyond one?
- What does the constant 0x00b1b104 represent?
- Why is the imported function named IResourceFactory in the Ghidra signature?
- required
