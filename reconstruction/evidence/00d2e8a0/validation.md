# Validation 0x00d2e8a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_c3_creature_progression_wave2/creature_progression_wave2.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 51-instruction listing name the same 7 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 8 outgoing call edge row(s) over 7 distinct address(es) for 0x00d2e8a0; 11 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 51-instruction listing names 4 data address(es) (0x1485378, 0x1582e54, 0x1654c10, 0x169e398) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field transition_receiver) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (51 of 51 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 51-instruction listing lie inside the recovered body span 0x00d2e8a0..0x00d2e970, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 51-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the ABI record names ST0 as the return register; the x87 stack top: the machine fixes where the value travels and not whether the source said float or double, so the machine fixes where the value travels and not the C type, and no width can be claimed. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d6fa7e4a804ce3784d0155053a2f2e88cbb5933e0d27998f427770e52aeffb0c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `fbd77954b9a3324a52fb37c3c377773f697fcf16d82c1599f585df70bbad455e`
- Pack digest quoted by the briefing: `d6fa7e4a804ce3784d0155053a2f2e88cbb5933e0d27998f427770e52aeffb0c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process event trace or runtime validation has been run.`, `Observe 0x0169e398, 0x01582e54, 0x01654c10, the returned player, the strategy +0x68 receiver, and the +0x54 avatar word in an original process.`, `Resolve concrete manager, player, avatar, strategy, event, and action ownership before assigning semantic names beyond the raw offsets.`, `gate-add-evolution-points-00d2e8a0`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process event trace or runtime validation has been run.
- Observe 0x0169e398, 0x01582e54, 0x01654c10, the returned player, the strategy +0x68 receiver, and the +0x54 avatar word in an original process.
- Resolve concrete manager, player, avatar, strategy, event, and action ownership before assigning semantic names beyond the raw offsets.
- gate-add-evolution-points-00d2e8a0
- runtime validation not run
