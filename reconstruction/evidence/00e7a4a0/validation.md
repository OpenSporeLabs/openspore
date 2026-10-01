# Validation 0x00e7a4a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06_cell_state/cell_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 209-instruction listing name the same 17 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00e7a4a0..0x00e7a761 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e7a55d, 0x00e7a56c; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 22 outgoing call edge row(s) over 17 distinct address(es) for 0x00e7a4a0; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 7 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 209-instruction listing names 11 data address(es) (0x14857c0, 0x14857d4, 0x14857f0, 0x15a7c4c, 0x15a7c50, 0x15a7c54, 0x15a7c58, 0x16b3c04, 0x16b3c28, 0x16b3c2c, 0x16b3c30) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field value) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (209 of 209 instruction(s), 0 unparsed) and all 18 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 209-instruction listing lie inside the recovered body span 0x00e7a4a0..0x00e7a761, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 209-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'std::uint8_t': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1294c5007bcda6db51370023f17c431e764cd8b59a9b46985e45e114d7743867`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cb76eadc5ea787a5b9be7d465255cca3815b153e4cd6f1b90cd1be93f17b787f`
- Pack digest quoted by the briefing: `1294c5007bcda6db51370023f17c431e764cd8b59a9b46985e45e114d7743867`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cell_effect_and_scale_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- cell_effect_and_scale_observation
- five-argument meaning
- resource and effect resolution
- scale comparison inputs
- vtable subtypes
