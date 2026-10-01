# Validation 0x00d065a0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 136-instruction listing name the same 13 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00d065a0..0x00d066ff are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00d066bc; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 24 outgoing call edge row(s) over 13 distinct address(es) for 0x00d065a0; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 136-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 4 source field-offset declaration(s) (displacement 0x504, field array_apply, field array_lookup, field flags) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x2 |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 136-instruction listing lie inside the recovered body span 0x00d065a0..0x00d066ff, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 136-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1fe4a44d7e57cb1b94c9deb5fb5a7a945d3da9397c804f0980b85bba75b8d433`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `668cd01d8bbf834189ac6c734a1d5361cfccd5c2a8bc01b7e318cf2afedc84e8`
- Pack digest quoted by the briefing: `1fe4a44d7e57cb1b94c9deb5fb5a7a945d3da9397c804f0980b85bba75b8d433`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-diplomacy-transition-00d065a0`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00b3d300 root and 0x01021300 cache contracts
- 0x00d01f50 and 0x00d05d90 semantics
- concrete transition and array owners
- concrete transition service and array owner
- gate-diplomacy-transition-00d065a0
- root follow-up owner identity
- runtime callback and relationship state
- runtime relationship state
