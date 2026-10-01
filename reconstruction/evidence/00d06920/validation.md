# Validation 0x00d06920

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_diplomacy_transitions/diplomacy_transitions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 99-instruction listing name the same 11 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 15 outgoing call edge row(s) over 11 distinct address(es) for 0x00d06920; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 99-instruction listing names 2 data address(es) (0x13eb844, 0x13eb90c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field flags) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 99 of 99 instruction(s) consumed, degraded=True, unparsed=1 |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 99-instruction listing lie inside the recovered body span 0x00d06920..0x00d06a3e, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 99-instruction body names 1 indirect transfer(s): 0x00d069eb dispatches slot 0x14 through the table word in EDX; the machine parse consumed 99 of 99 instruction(s) with 1 unparsed and degraded=True, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 1 instruction(s) were left unparsed |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 8 of 8 static checks evaluated, 2 passed, 0 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3ad546e3ca88ff640d094238b378cbb245a35f887a42c6404542edf53a4d744a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a9bce2ec5fdee504bd17e242f7159111e49a0403b6006c31e1a1981144b4333c`
- Pack digest quoted by the briefing: `3ad546e3ca88ff640d094238b378cbb245a35f887a42c6404542edf53a4d744a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-diplomacy-transition-00d06920`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00d038e0 nested side effects
- concrete event and post-transition owners
- concrete event, relationship, root, and post-transition owners
- current-root and empire-key runtime identity
- gate-diplomacy-transition-00d06920
- nested relationship side effects
- runtime callback side effects
- runtime current-player key and relationship state
