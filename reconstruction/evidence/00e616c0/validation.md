# Validation 0x00e616c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_mode_wave7/game_mode_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 23-instruction listing name the same 1 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00e616c0..0x00e61709 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e616f3; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00e616c0; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | 6 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 3 source field-offset declaration(s) (field primary_vtable, field secondary_vtable, field vtable) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (23 of 23 instruction(s), 0 unparsed) and all 7 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 23-instruction listing lie inside the recovered body span 0x00e616c0..0x00e61709, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 23-instruction body names 1 indirect transfer(s): 0x00e61707 dispatches slot 0x20 through the table word in EDX; the machine parse consumed 23 of 23 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 3 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9b7e24b7046f9d9cc79e816926d2954522e67bb2ee6308fff18b9513eba3de25`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ebfd5ce527ef97674de297c7a35434fd9c60ce3a9519e185d29152aa7546fb91`
- Pack digest quoted by the briefing: `9b7e24b7046f9d9cc79e816926d2954522e67bb2ee6308fff18b9513eba3de25`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe constructor reachability, allocator identity, object vtable publication, owner vtable +0x20 target, and null-allocation behavior; runtime validation is not run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe constructor reachability, allocator identity, object vtable publication, owner vtable +0x20 target, and null-allocation behavior; runtime validation is not run.
- concrete runtime owners and values remain unresolved
