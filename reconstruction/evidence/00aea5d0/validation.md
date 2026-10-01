# Validation 0x00aea5d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg12_space/space_comm_event_lifecycle.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 133-instruction listing name the same 4 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00aea5d0..0x00aea719 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00aea660, 0x00aea69c; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 4 distinct address(es) for 0x00aea5d0; 157 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 5 outgoing call edge row(s) and 4 distinct callee(s) the export records; 4 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00ac97a0, 0x00f47380, 0x00f473a0, 0x011e0744; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 5 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 4 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 133-instruction listing names 2 data address(es) (0x13ebb38, 0x13f09b4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field begin, capacity, end, h and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x0, 0x4, 0x8), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (133 of 133 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 14 conditional branch target(s) in the complete 133-instruction listing lie inside the recovered body span 0x00aea5d0..0x00aea719, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 133-instruction body names 4 indirect transfer(s): 0x00aea607 dispatches slot 0x0 through the table word in EAX; 0x00aea62d dispatches slot 0x0 through the table word in EAX; 0x00aea63d dispatches slot 0x4 through the table word in EAX; 0x00aea6cf dispatches slot 0x0 through the table word in EAX; the machine parse consumed 133 of 133 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b866c20afa539321bae4eab7be9118118e94338450f2d73611873977ddfaacbc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `643d15bacbad2b1da8259f23a8a62e9e3938516cf81d1591abcaca5ebe169f81`
- Pack digest quoted by the briefing: `b866c20afa539321bae4eab7be9118118e94338450f2d73611873977ddfaacbc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-space-comm-event-lifecycle`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The SDK manager field name for the +0x24 vector remains unresolved.
- The exact ownership contract of the allocator's prefix word is not promoted beyond the observed conditional release.
- allocator failure behavior
- gate-space-comm-event-lifecycle
- manager vector field name
- move helper ownership
