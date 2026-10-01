# Validation 0x00e7a7c0

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06_cell_state/cell_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 203-instruction listing name the same 16 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00e7a7c0..0x00e7aa0a are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00e7a8c1, 0x00e7a930, 0x00e7a9f5; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 16 outgoing call edge row(s) over 16 distinct address(es) for 0x00e7a7c0; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 11 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 203-instruction listing names 2 data address(es) (0x1485378, 0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 8 type(s) |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0xffffffff |
| CONTROL FLOW | `PASS` | `complete` | all 16 conditional branch target(s) in the complete 203-instruction listing lie inside the recovered body span 0x00e7a7c0..0x00e7aa0a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 203-instruction body names 1 indirect transfer(s): 0x00e7a916 is INDIRECT_NON_VTABLE; the machine parse consumed 203 of 203 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00e7a916), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0xe7aa0c], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'std::uint8_t': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 6 of 8 static checks evaluated, 2 passed, 2 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b172a87585df2590f47d5112a03c1d58f2e1bbe76d9f79fd2f88f70573039f82`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c6bfe4396b4a990d0737589d1844e53f8e08859e458c5f3957d764610369c889`
- Pack digest quoted by the briefing: `b172a87585df2590f47d5112a03c1d58f2e1bbe76d9f79fd2f88f70573039f82`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cell_damage_transition_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- actual damage and health values
- cell_damage_transition_observation
- field meanings
- global simulator state
- resource/effect availability
