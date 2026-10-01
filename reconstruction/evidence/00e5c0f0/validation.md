# Validation 0x00e5c0f0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_game_input_wave8/game_input_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 46-instruction listing name the same 4 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 4 distinct address(es) for 0x00e5c0f0; the source span names 4 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 46-instruction listing names 3 data address(es) (0x14851e8, 0x16b3c04, 0x16b3c0c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 7 source field-offset declaration(s) (field health_0900, field health_phase_0904, field input, field raycast_in_0) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (46 of 46 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 46-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 46-instruction body names 1 indirect transfer(s): 0x00e5c126 dispatches slot 0x58 through the table word in EDX; the machine parse consumed 46 of 46 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'bool' and the machine return state is WIDTH_1_IN_EAX: the complete 46-instruction listing writes EAX at a determinate 1-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dc0077aee1e717ae5bf027fbec17756fededd862b1839d74fb5a11ab6b5cfbc9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b6af784ffddd12e565f1b01dd4cabfc76fbeed52d144655f8b0d488231821791`
- Pack digest quoted by the briefing: `dc0077aee1e717ae5bf027fbec17756fededd862b1839d74fb5a11ab6b5cfbc9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe the concrete vtable call shape, the validity of the Cell game and Cell state globals, the 0x00e87200 return value, and the resulting words at Cell state offsets 0x900 and 0x904 in the original Cell mode.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Observe the concrete vtable call shape, the validity of the Cell game and Cell state globals, the 0x00e87200 return value, and the resulting words at Cell state offsets 0x900 and 0x904 in the original Cell mode.
- concrete runtime receiver identity and vtable dispatch reachability for slot 0x38
- the exact identity of renderer vtable offset 0x58, because the SDK header declares that slot as Layer(int) while the observed call passes no stack words
- the semantic meaning of the Cell state words at offsets 0x900 and 0x904 and of the persistent buffer at offset 0x100
- whether the 0x00e87200 return value is a hit count, a distance, or an index
- whether the two-frame-triple layout reversal relative to 0x00e6c860 is intentional or an artifact of this particular codegen
