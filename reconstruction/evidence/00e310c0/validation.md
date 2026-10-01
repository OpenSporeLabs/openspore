# Validation 0x00e310c0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_resource_state_safe_wave10/resource_state_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00e310c0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00e310c0..0x00e310db, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'OpaqueRecordWrite*' and the machine return state is WIDTH_4_IN_EAX: the complete 11-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ad8f38df76f02321f542b432365608071bf88bbaa6048ac403f245a618fe5f32`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5451c52394b2e27c010c36ed0e7afdb4a9b9a56e218d11436e37b2898b447bbb`
- Pack digest quoted by the briefing: `ad8f38df76f02321f542b432365608071bf88bbaa6048ac403f245a618fe5f32`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.`, `No original-process invocation was captured.`, `The published entry is reached only through the 0x01481948 vtable slot and the 0x00e31020 thunk that rebases ECX by -0x8.`, `The receiver class identity is unresolved; the target never dereferences the receiver so no field evidence exists.`, `gate-record-write-get-state-runtime-receiver-identity`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00e30f90 and 0x00f47380 remain dependency-only, so the release and untrack effects are unverified in this package.
- No original-process invocation was captured.
- The published entry is reached only through the 0x01481948 vtable slot and the 0x00e31020 thunk that rebases ECX by -0x8.
- The receiver class identity is unresolved; the target never dereferences the receiver so no field evidence exists.
- What 0x00e30f90 and 0x00f47380 actually release, and in what order relative to the untrack
- What class owns the receiver that the 0x01481948 vtable slot publishes
- Whether the -0x8 receiver rebase performed by the 0x00e31020 thunk changes what the caller observes
- Which caller supplies the release flag, given the only caller is the 0x00e31020 thunk
- gate-record-write-get-state-runtime-receiver-identity
