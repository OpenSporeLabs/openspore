# Validation 0x0093c0c0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_serialization_persistence/stream_lifecycle.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 45-instruction listing name the same 1 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x0093c0c0..0x0093c129 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0093c0f4, 0x0093c0f7; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x0093c0c0; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 45-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field position, resize_enabled, size and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (45 of 45 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 45-instruction listing lie inside the recovered body span 0x0093c0c0..0x0093c129, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 45-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `667cf7643e88d67b949d25494536fcea864b4fb6786759f414a9588553693712`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5420cc7bc4895522f0e9cb9c7d33087f887026c6bb579988d27999538db5ba08`
- Pack digest quoted by the briefing: `667cf7643e88d67b949d25494536fcea864b4fb6786759f414a9588553693712`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-memory-stream-position-growth-and-allocation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- capacity and clear-memory behavior
- gate-memory-stream-position-growth-and-allocation
- growth allocator identity
- maximum size and overflow policy
