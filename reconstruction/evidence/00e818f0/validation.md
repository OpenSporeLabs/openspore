# Validation 0x00e818f0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_input_wave7/game_input_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `FAIL` | `partial` | unresolved ABI conflict derived_vs_persisted; the validator will not pick a winner |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 68-instruction listing name the same 5 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 7 outgoing call edge row(s) over 5 distinct address(es) for 0x00e818f0; the source span names 5 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 68-instruction listing names 1 data address(es) (0x16b3c0c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 2 source field-offset declaration(s) (field input, field ui_flag_0937) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (68 of 68 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 12 conditional branch target(s) in the complete 68-instruction listing lie inside the recovered body span 0x00e818f0..0x00e819a3, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 68-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'bool': the return register EAX is written at a width this module cannot bound on at least one of the 3 reachable return(s) in the complete 68-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0a8d72d420db71c1333ea0920fe9592211f6387c48cfc65ece20dade55e72636`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9ea27f684d9ef868ada88af2923f293b5e893725764658360e759283489d5ccb`
- Pack digest quoted by the briefing: `0a8d72d420db71c1333ea0920fe9592211f6387c48cfc65ece20dade55e72636`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe Cell-mode vtable reachability, global receiver validity, route/UI/action return values, and all action side effects in the original process.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe Cell-mode vtable reachability, global receiver validity, route/UI/action return values, and all action side effects in the original process.
- concrete runtime owners and values remain unresolved
