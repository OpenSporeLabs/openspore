# Validation 0x01021300

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_player_cache.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 43-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x01021300; 246 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 2 outgoing call edge row(s) and 2 distinct callee(s) the export records; 2 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b3d2a0, 0x00ba9370; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 2 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 43-instruction listing names 1 data address(es) (0x16dda8c) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 10 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (43 of 43 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 43-instruction listing lie inside the recovered body span 0x01021300..0x01021368, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 43-instruction body names 2 indirect transfer(s): 0x01021349 dispatches slot 0x0 through the table word in EAX; 0x01021358 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 43 of 43 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'Empire*' and the machine return state is WIDTH_4_IN_EAX: the complete 43-instruction listing writes EAX at a determinate 4-byte width before all 2 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 14 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 14 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `03cee8d99e5780867ab568da4ec294c147eb6f2c7382ffb6c8bca599bb5c7df4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e733cd43297ac8d7a9793ffddd0ea4d655b9dd773b50465dd16c5a7f4d462916`
- Pack digest quoted by the briefing: `03cee8d99e5780867ab568da4ec294c147eb6f2c7382ffb6c8bca599bb5c7df4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-player-data-and-empire-lookup`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The 182 callers establish broad use but do not by themselves establish a universal ownership contract beyond the observed cache AddRef/store/Release behavior.
- The host globals are explicit stand-ins for the live global at 0x016DDA8C and the lookup boundary; they are not linked to integrated PKG-12 source in this assignment.
- The live cache validates only the existing cached empire's +0x84 identity before refresh and does not validate a newly returned empire's +0x84 identity after 0x00ba9370. Because 0x00ba9370 is guarded-hybrid dependent, its result can be null/anchor or a nonmatching empire, so the live body may AddRef/store a nonmatching new pointer without an identity check.
- The live root getter has no formal staged-ID argument; RootWithStagedId is intentionally a host adapter that exposes the pre-existing stack word for the model.
- The semantic name of cEmpire+0x84 is unresolved; Ghidra labels it mTrait while the target treats it as the cache identity word.
- The shared map owner and concrete manager type behind DAT_0167EAE4 and FUN_00BA9370 remain outside this package.
- borrowed return lifetime
- concrete cEmpire vtable ownership
- gate-space-player-data-and-empire-lookup
- live global and manager publication
- new empire identity is not revalidated
