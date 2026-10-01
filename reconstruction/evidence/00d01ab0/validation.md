# Validation 0x00d01ab0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_diplomacy_primitives/diplomacy_primitives.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 59-instruction listing name the same 5 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 6 outgoing call edge row(s) over 5 distinct address(es) for 0x00d01ab0; 32 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 6 outgoing call edge row(s) and 5 distinct callee(s) the export records; 5 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00ba6650, 0x00ce6950, 0x00d009a0, 0x00d01210, 0x010212a0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 6 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 5 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 59-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 3 displacement(s) (0x4, 0x20, 0x24) lie outside the machine-derived receiver bounds (0x9c, 0xa0, 0xb0) for ECX, so the source and the body disagree with the receiver record; the source span declares 0x4, 0x20, 0x24, and the complete 59-instruction listing names none through that register |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (59 of 59 instruction(s), 0 unparsed) and all 6 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 59-instruction listing lie inside the recovered body span 0x00d01ab0..0x00d01b47, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 59-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueRelationshipMap*' and the machine return state is WIDTH_4_IN_EAX: the complete 59-instruction listing writes EAX at a determinate 4-byte width before all 2 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d5cc11b7f3f6526b09cc74d4060614aad30a9b5592e5cea6d38b14adbae5f2fe`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8ed10e20faf2f859a4b2c58e364c0c7e7cc5466ceaeb38ff8fb7fcd7e19f8426`
- Pack digest quoted by the briefing: `d5cc11b7f3f6526b09cc74d4060614aad30a9b5592e5cea6d38b14adbae5f2fe`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-diplomacy-map-selector`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 00ce6950 concrete context
- 010212a0 context owner
- 0x00ce6950 concrete context type
- 0x00d009a0 context-dependent key normalization
- 0x00d01210 record lower-bound implementation
- 0x010212a0 context ownership
- d009a0 normalization
- d01210 lower-bound records
- gate-diplomacy-map-selector
- runtime manager publication
- runtime map/record values
