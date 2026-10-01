# Validation 0x00e52910

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06a_cell_ai_selection/cell_ai_selection.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): receiver_not_determinable: ecx_reassigned_before_deref |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 21-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 1 intra-procedural jump(s) target inside the recovered body span 0x00e52910..0x00e52958 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e5294d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00e52910; 90 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 0 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 21-instruction listing names 1 data address(es) (0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 6 source field-offset declaration(s) (displacement 0x5190, displacement 0x7c, field ai_easy, field ai_hard) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (21 of 21 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 21-instruction listing lie inside the recovered body span 0x00e52910..0x00e52958, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 21-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'ObservedCellAiData*' and the machine return state is WIDTH_4_IN_EAX: the complete 21-instruction listing writes EAX at a determinate 4-byte width before all 2 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8b4b62e89e3f77b631f388ab51686195d9d54008d56edcf37157ee6da541a1b8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `047947d4c6e55e2811a6357d6c773efb9497c4b27f5009cac9c608cce8d3c2d1`
- Pack digest quoted by the briefing: `8b4b62e89e3f77b631f388ab51686195d9d54008d56edcf37157ee6da541a1b8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-cell-ai-selection`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does any caller violate the assumed valid game, serializable, resource, or selected profile pointer chain?
- What are the exact identities and field layouts of all 23 direct callers' resource and profile objects?
- What concrete runtime values use the type -1 sentinel in normal, easy, and hard profiles?
- What is the canonical concrete type and ownership of ObservedCellCellResource?
- What runtime values produce difficulty 0, 2, or another value in the original Cell state?
- difficulty values in the original Cell state
- gate-cell-ai-selection
- profile ownership and canonical concrete type promotion
- runtime pointer chain
