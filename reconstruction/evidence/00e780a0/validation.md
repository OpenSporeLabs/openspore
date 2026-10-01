# Validation 0x00e780a0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg06_cell_state/cell_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 116-instruction listing name the same 13 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 13 outgoing call edge row(s) over 13 distinct address(es) for 0x00e780a0; 27 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 3 address-named callee(s), against the 13 outgoing call edge row(s) and 13 distinct callee(s) the export records; 10 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b72260, 0x00bbbde0, 0x00e4cc40, 0x00e4ee60, 0x00e59200, 0x00e66010, 0x00e67890, 0x00e771d0, 0x00e82130, 0x00e86980; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 13 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 5 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 116-instruction listing names 1 data address(es) (0x16b3c04) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 9 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (116 of 116 instruction(s), 0 unparsed) and all 14 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 10 conditional branch target(s) in the complete 116-instruction listing lie inside the recovered body span 0x00e780a0..0x00e78226, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 116-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'void': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 6 of 8 static checks evaluated, 4 passed, 2 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c672d410d7e98cbb27e832f2f1060ffbf0a13aa5bc79fcb973c8c51bbb487b66`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3134872ebba1c86488f498ff3118e71ed04ec7f778e1aaaf91d47d1f5b8e9f2b`
- Pack digest quoted by the briefing: `c672d410d7e98cbb27e832f2f1060ffbf0a13aa5bc79fcb973c8c51bbb487b66`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cell_object_lifetime_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- callback ownership
- cell_object_lifetime_observation
- pool/object existence
- registry deletion timing
- resource state
