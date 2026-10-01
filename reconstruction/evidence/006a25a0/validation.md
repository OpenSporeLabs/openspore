# Validation 0x006a25a0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg20_property_adapter/direct_property_list.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 73-instruction listing name the same 3 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x006a25a0..0x006a2652 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a262d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x006a25a0; 144 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 3 outgoing call edge row(s) and 3 distinct callee(s) the export records; 3 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00612db0, 0x006a19b0, 0x0093db80; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 3 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 73-instruction listing names 1 data address(es) (0x15d115d) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field entries_end, fast_access_count, flags, key and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (73 of 73 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 9 conditional branch target(s) in the complete 73-instruction listing lie inside the recovered body span 0x006a25a0..0x006a2652, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 73-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6454812b2e7824dd5387d3240989f2f687931319223f8fe0cc9bb4e57670bd15`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3cb4e4d96be00de713d8c6c6324618f16d5d5f32fb424c6730f90171710aa61b`
- Pack digest quoted by the briefing: `6454812b2e7824dd5387d3240989f2f687931319223f8fe0cc9bb4e57670bd15`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-property-direct-bool`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00542c30 conversion result
- PTR_FUN_0154eb48 callback owner
- concrete Property owner
- gate-property-direct-bool
- runtime pointer-flag ownership
