# Validation 0x00be2440

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c4_civ_wave3/civ_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 428-instruction listing name the same 10 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00be2440..0x00be2b0b are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00be2775; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 13 outgoing call edge row(s) over 10 distinct address(es) for 0x00be2440; 13 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 428-instruction listing names 6 data address(es) (0x13ec4d0, 0x1473c70, 0x18ea1eb, 0x18ea2cc, 0x18eb106, 0x1a56aba) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 9 source field-offset declaration(s) (displacement 0x3ec, field active, field adjacency, field adjacency_total) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 428 of 428 instruction(s) consumed, degraded=True, unparsed=2 |
| CONTROL FLOW | `PASS` | `complete` | all 73 conditional branch target(s) in the complete 428-instruction listing lie inside the recovered body span 0x00be2440..0x00be2b0b, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 428-instruction body names 5 indirect transfer(s): 0x00be264e dispatches slot 0x6c through the table word in EDX; 0x00be2696 dispatches slot 0xc through the table word in EDX; 0x00be26cb dispatches slot 0x20 through the table word in EDX; 0x00be26e8 dispatches slot 0x6c through the table word in EDX; 0x00be2a23 dispatches slot 0xc through the table word in EDX; the machine parse consumed 428 of 428 instruction(s) with 2 unparsed and degraded=True, and the machine dispatch record independently counts 5, so the dispatch is visible in the machine listing but is not proven: the machine parse is degraded and 2 instruction(s) were left unparsed |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 3 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a86e1e473bbefc677e19b988d58849bf82d22dd0fe4631ecc3913e743311976d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1c1186398ea3da28beed7669ab422568bf17ec6d79b8eb9e9f0fb99fc1015c8b`
- Pack digest quoted by the briefing: `a86e1e473bbefc677e19b988d58849bf82d22dd0fe4631ecc3913e743311976d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
