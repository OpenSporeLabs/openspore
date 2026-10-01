# Validation 0x0102d1b0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_functions.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 451-instruction listing name the same 53 direct transfer target(s); 5 intra-procedural jump(s) target inside the recovered body span 0x0102d1b0..0x0102d7cc are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0102d242, 0x0102d3f0, 0x0102d5aa, 0x0102d69f, 0x0102d6c0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 74 outgoing call edge row(s) over 53 distinct address(es) for 0x0102d1b0; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 16 address-named callee(s), against the 74 outgoing call edge row(s) and 53 distinct callee(s) the export records; 37 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00ba9370, 0x00bb59b0, 0x00bba990, 0x00bbaa60, 0x00bfc5f0, 0x00c31a00, 0x00c705c0, 0x00c70c00, 0x00c70e00, 0x00c71e70, 0x00c8b770, 0x00c8ce40 and 25 more; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 74 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 49 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 8 source field-offset declaration(s) (displacement 0x24, displacement 0x25, displacement 0x26, displacement 0x34) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (451 of 451 instruction(s), 0 unparsed) and all 23 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 23 conditional branch target(s) in the complete 451-instruction listing lie inside the recovered body span 0x0102d1b0..0x0102d7cc, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 451-instruction body names 9 indirect transfer(s): 0x0102d3b7 dispatches slot 0x2c through the table word in EAX; 0x0102d409 dispatches slot 0x2c through the table word in EDX; 0x0102d46e dispatches slot 0x2c through the table word in EDX; 0x0102d497 dispatches slot 0x30 through the table word in EDX; 0x0102d4e1 dispatches slot 0x70 through the table word in EAX; 0x0102d4f1 dispatches slot 0x74 through the table word in EAX; 0x0102d62f dispatches slot 0x14 through the table word in EDX; 0x0102d656 dispatches slot 0x4 through the table word in EAX; 0x0102d74a dispatches slot 0x14 through the table word in EDX; the machine parse consumed 451 of 451 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9, so the dispatch is visible in the machine listing but is not proven: the source span states slot displacement(s) 0x678a3ef and the machine reads 0x4, 0x14, 0x2c, 0x30, 0x70, 0x74, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `805fab7debe8838cde35010688fabd02ce94760054850db9aea736242563cde2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `070cd1d5aac09ccd5f746a9cd5c93abdbf036812cfc57ef4c2946b2a8d1795d0`
- Pack digest quoted by the briefing: `805fab7debe8838cde35010688fabd02ce94760054850db9aea736242563cde2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `space_communication_state_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- achievement side effects
- distance/visual values
- object identity
- service and event results
- space_communication_state_observation
