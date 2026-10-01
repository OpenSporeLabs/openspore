# Validation 0x00c8d060

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_e4_empire_wave3/empire_wave3.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 196-instruction listing name the same 21 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00c8d060..0x00c8d2e1 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00c8d110, 0x00c8d257; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 26 outgoing call edge row(s) over 21 distinct address(es) for 0x00c8d060; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 196-instruction listing names 1 data address(es) (0x13ec4d0) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 9 source field-offset declaration(s) (field begin, field end, field field_15c, field field_160) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (196 of 196 instruction(s), 0 unparsed) and all 6 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 27 conditional branch target(s) in the complete 196-instruction listing lie inside the recovered body span 0x00c8d060..0x00c8d2e1, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 196-instruction body names 5 indirect transfer(s): 0x00c8d24f dispatches slot 0x20 through the table word in EDX; 0x00c8d26e dispatches slot 0x38 through the table word in EDX; 0x00c8d281 dispatches slot 0x40 through the table word in EDX; 0x00c8d290 dispatches slot 0x40 through the table word in EDX; 0x00c8d299 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 196 of 196 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5, so the dispatch is visible in the machine listing but is not proven: the source span states slot displacement(s) 0x20, 0x38, 0x40, 0x58, 0x3475365, 0x3475381, 0x3475385, 0xef7f5479 and the machine reads 0x20, 0x38, 0x40, 0x58, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ff0d76380b911d8e1ce59d0acf3f58229f63d62e23d1c69a88e57c526a6eba1a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3b44341d149a955a4a3783813701327992c96c41fdffd465ba968f1bce3a5ae7`
- Pack digest quoted by the briefing: `ff0d76380b911d8e1ce59d0acf3f58229f63d62e23d1c69a88e57c526a6eba1a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
