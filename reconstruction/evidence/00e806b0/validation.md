# Validation 0x00e806b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_frame_runtime_wave8/frame_runtime_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 189-instruction listing name the same 16 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 22 outgoing call edge row(s) over 16 distinct address(es) for 0x00e806b0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 16 of them and no others |
| GLOBALS | `WARN` | `partial` | 3 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 17 source field-offset declaration(s) (field cell, field cell_game, field counter_5160, field gate_515c) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (189 of 189 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 10 conditional branch target(s) in the complete 189-instruction listing lie inside the recovered body span 0x00e806b0..0x00e80970, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 189-instruction body names 6 indirect transfer(s): 0x00e8070d dispatches slot 0x20 through the table word in EDX; 0x00e8072f dispatches slot 0x40 through the table word in EDX; 0x00e807d7 dispatches slot 0x38 through the table word in ESI; 0x00e8080e dispatches slot 0x38 through the table word in ESI; 0x00e80918 dispatches slot 0x38 through the table word in EDX; 0x00e8093b dispatches slot 0x38 through the table word in EDX; the machine parse consumed 189 of 189 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x20, 0x38, 0x40, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 4 reachable return(s) in the complete 189-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2afe9e34c38e0266b262e35e748d749f31753be7964f14446d4e25992c2c0771`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5e6eb5a4e40a43d19d4c1123295efe53924c8b2821d89b7ea3e00e5051c9ede3`
- Pack digest quoted by the briefing: `2afe9e34c38e0266b262e35e748d749f31753be7964f14446d4e25992c2c0771`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- concrete runtime owners and values remain unresolved
- required
