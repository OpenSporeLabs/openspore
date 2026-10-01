# Validation 0x00b63510

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 282-instruction listing name the same 24 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 37 outgoing call edge row(s) over 24 distinct address(es) for 0x00b63510; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 17 address-named callee(s), against the 37 outgoing call edge row(s) and 24 distinct callee(s) the export records; 7 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00d100b0, 0x00e00ac0, 0x00f473a0, 0x00fd9c60, 0x00fde3e0, 0x01002bd0, 0x01021080; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 37 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 19 of them and no others |
| GLOBALS | `WARN` | `partial` | 4 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 8 source field-offset declaration(s) (displacement 0x20, field counter_30, field field_308, field flag_01686af1) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x12a93f06 |
| CONTROL FLOW | `PASS` | `complete` | all 39 conditional branch target(s) in the complete 282-instruction listing lie inside the recovered body span 0x00b63510..0x00b63871, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 282-instruction body names 5 indirect transfer(s): 0x00b636d7 dispatches slot 0x14 through the table word in EDX; 0x00b63727 dispatches slot 0x18 through the table word in EDX; 0x00b63792 dispatches slot 0x14 through the table word in EDX; 0x00b637a0 dispatches slot 0x40 through the table word in EDX; 0x00b6382f dispatches slot 0x7c through the table word in EDX; the machine parse consumed 282 of 282 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5, so the dispatch is visible in the machine listing but is not proven: the source span states slot displacement(s) 0x4715068, 0x64eb18e, 0x689c9b9 and the machine reads 0x14, 0x18, 0x40, 0x7c, so the two disagree about which slot is dispatched |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'bool': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 2 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `036541804307665cd5cfc2a435f0b206e2dfff9c15c5848196b97a6e693fd68a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6ff51473c3fc2284fe7abbae6ae9ef6a9064c7037bc24bfbd3b0ba43592898d0`
- Pack digest quoted by the briefing: `036541804307665cd5cfc2a435f0b206e2dfff9c15c5848196b97a6e693fd68a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe receiver validity, all message-id reachability, service identities, mode-object fields, payload validity, and all unresolved native port results; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe receiver validity, all message-id reachability, service identities, mode-object fields, payload validity, and all unresolved native port results; runtime validation is not run.
- concrete runtime owners and values remain unresolved
