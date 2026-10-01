# Validation 0x00de9fc0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_inventory_entry.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 193-instruction listing name the same 9 direct transfer target(s); 4 intra-procedural jump(s) target inside the recovered body span 0x00de9fc0..0x00dea1fb are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00dea018, 0x00dea07f, 0x00dea0e3, 0x00dea160; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 22 outgoing call edge row(s) over 9 distinct address(es) for 0x00de9fc0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 193-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 13 source field-offset declaration(s) (field allocation, field anchor, field begin, field behavior) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (193 of 193 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 19 conditional branch target(s) in the complete 193-instruction listing lie inside the recovered body span 0x00de9fc0..0x00dea1fb, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 193-instruction body names 1 indirect transfer(s): 0x00dea12e dispatches slot 0x38 through the table word in EDX; the machine parse consumed 193 of 193 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7098e37377db20f239f9f8ab5c7a985bd6965006c312db180014dd4657a138b9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `504c8ada2e5117de595ad9365e623f1654c34fef1c82f83294c38dc3fede16f8`
- Pack digest quoted by the briefing: `7098e37377db20f239f9f8ab5c7a985bd6965006c312db180014dd4657a138b9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-inventory-entry`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Galaxy/game-entry service owner
- The behavior/cache list at context+0x40 and the secondary record range ownership remain opaque.
- The concrete Galaxy/game-entry service owner type and the vtable +0x38 return contract are not named by Ghidra.
- The game-mode initialization and behavior cleanup services are separate dependencies; no event lifecycle is inferred here.
- The live body has no explicit null or reversed-range guard; the staging descriptor_count guard is a model safety boundary and not a recovered source branch.
- The three descriptor words and their relationship to Galaxy coordinates, game IDs, and game-mode selection remain unknown.
- The three property records' opaque words and the exact ownership of their allocated buffers are not closed by this body.
- behavior/cache ownership
- descriptor word semantics
- gate-space-inventory-entry
- property record allocator ownership
