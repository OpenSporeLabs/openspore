# Validation 0x00e7e6c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06d_cell_behavior_timer/cell_behavior_timer.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 77-instruction listing name the same 4 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00e7e6c0..0x00e7e799 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e7e710, 0x00e7e782; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 4 distinct address(es) for 0x00e7e6c0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 4 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 77-instruction listing names 1 data address(es) (0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 11 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (77 of 77 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 77-instruction listing lie inside the recovered body span 0x00e7e6c0..0x00e7e799, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 77-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 6 of 8 static checks evaluated, 4 passed, 2 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1fa5b50641a86a390d9a6a58e37ed1c884051850dbe0b73cbdec2360cf604d0a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c07f07ff39533d96c8789a9fd514008548e1b10da2f9b03b49ac58126a7592f3`
- Pack digest quoted by the briefing: `1fa5b50641a86a390d9a6a58e37ed1c884051850dbe0b73cbdec2360cf604d0a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-cell-behavior-timer`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What exact native bodies, mutation contracts, and return widths belong to 0x00e59c10, 0x00e7b540, and 0x00e7ba30?
- What is the live queued-interaction record type, true size, and pool stride?
- What stable meaning and runtime values belong to PKG-06A g_cell_game_016b3c04+0x5198?
- What stable semantic meaning, if any, belongs to the original entry ECX pointer?
- What stable semantic names belong to record offsets 0x00 and 0x0c through 0x1c?
- Which separate package and adapter should own the unresolved 0x00e7e130 fallback body and any release behavior?
- body and release behavior of unresolved 0x00e7e130
- gate-cell-behavior-timer
- live queued-interaction record type and stride
- runtime selector and timer values
- semantics of 0x00e59c10, 0x00e7b540, and 0x00e7ba30
