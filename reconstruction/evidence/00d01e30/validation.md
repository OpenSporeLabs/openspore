# Validation 0x00d01e30

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 80-instruction listing name the same 7 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 11 outgoing call edge row(s) over 7 distinct address(es) for 0x00d01e30; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 80-instruction listing names 2 data address(es) (0x13eb844, 0x13eb90c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 13 type(s) |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x2 |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 80-instruction listing lie inside the recovered body span 0x00d01e30..0x00d01f12, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 80-instruction body names 1 indirect transfer(s): 0x00d01ef2 dispatches slot 0x14 through the table word in EDX; the machine parse consumed 80 of 80 instruction(s) with 1 unparsed and degraded=True, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 1 instruction(s) were left unparsed |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 3 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9e0dfb5de2c7a72cd2abadcdd320d704142f3f0ce75b45e551cfcb59ce2f2ac3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b89e3904e38a3be3b36ff5b41ce5190ee19ab5d8784002c22f73e41f79e6b343`
- Pack digest quoted by the briefing: `9e0dfb5de2c7a72cd2abadcdd320d704142f3f0ce75b45e551cfcb59ce2f2ac3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-diplomacy-transition-00d01e30`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00c32830 and 0x00c31c50 semantics
- 0x00d01410 and 0x00d01ab0 map behavior
- concrete relationship manager and event owners
- concrete relationship manager and record owners
- gate-diplomacy-transition-00d01e30
- relationship and event lifetime
- runtime event service identity
- runtime relationship and event lifetime
