# Validation 0x00febc90

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg11_a2_progression_alt/progression_alt.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 29-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00febc90; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 29-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 2 the complete 29-instruction listing names through ECX (0x34, 0x38) are all within the machine-derived receiver bounds (0x34, 0x38), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x4 |
| CONTROL FLOW | `WARN` | `partial` | 1 of 2 conditional branch target(s) fall outside the recovered body span 0x00febc90..0x00febcda, so the listing is a slice and flow continues past it; the source span declares for, if |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 29-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'bool' and the machine return state is WIDTH_1_IN_EAX: the complete 29-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1a2018faa28fdd4050d79bf09cc5edf66862ef2f0ea99225aeecfa0c9bb66277`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cc13b0441f5a624c193739a45e23e7a8c51e310de9c6440bd2bc837b19f43b60`
- Pack digest quoted by the briefing: `1a2018faa28fdd4050d79bf09cc5edf66862ef2f0ea99225aeecfa0c9bb66277`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-mission-track-decision-00febc90`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- gate-mission-track-decision-00febc90
- runtime validation not run
