# Validation 0x0093db80

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg10_editor_dispatch/editor_query_helpers.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `FAIL` | `partial` | the machine-vs-machine rule: the xref export records 1 callee(s) and the complete 22-instruction listing 0 direct transfer(s), and the two sets disagree; 1 export callee(s) the body does not show: 0x009415a0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x0093db80; 407 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x009415a0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `WARN` | `partial` | the complete 22-instruction listing names 1 data address(es) (0x154eb48) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field flags, trailing_flags and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (22 of 22 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 22-instruction listing lie inside the recovered body span 0x0093db80..0x0093dbb7, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 22-instruction body names 1 indirect transfer(s): 0x0093db94 is INDIRECT_NON_VTABLE; the machine parse consumed 22 of 22 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x0093db94), so the dispatch's identity is not established: the target is the memory operand [0x0154eb48], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9bad94e2b73f1f3c5ca5f6640022cb9119b91c809eef0371149ac9011f98d8de`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ca0b82090e2ea516b5f3baa357381fb9450a5726c9ef93b8d76073d756923ac4`
- Pack digest quoted by the briefing: `9bad94e2b73f1f3c5ca5f6640022cb9119b91c809eef0371149ac9011f98d8de`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-editor-query-global-callback`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What concrete service or property owner is installed at 0x0154eb48?
- What do the two flag bits mean beyond their observed callback and clear behavior?
- Which callers depend on callback timing or mutation of the query words?
- caller dependence on callback timing
- flag bit semantics
- gate-editor-query-global-callback
- global callback owner
