# Validation 0x0058b650

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_input_wave6/editor_input.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 332-instruction listing name the same 27 direct transfer target(s); 5 intra-procedural jump(s) target inside the recovered body span 0x0058b650..0x0058ba52 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0058b80d, 0x0058b814, 0x0058b88c, 0x0058b8b0, 0x0058b9a0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 33 outgoing call edge row(s) over 27 distinct address(es) for 0x0058b650; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 24 address-named callee(s), against the 33 outgoing call edge row(s) and 27 distinct callee(s) the export records; 3 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x0067cab0, 0x0067dcc0, 0x008013d0; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 33 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 332-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 1 source constant(s) are absent from the machine listing: 0x3ea |
| CONTROL FLOW | `PASS` | `complete` | all 45 conditional branch target(s) in the complete 332-instruction listing lie inside the recovered body span 0x0058b650..0x0058ba52, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 332-instruction body names 9 indirect transfer(s): 0x0058b6a3 dispatches slot 0x14 through the table word in EAX; 0x0058b6c3 dispatches slot 0x14 through the table word in EDX; 0x0058b784 dispatches slot 0x10 through the table word in EDX; 0x0058b795 dispatches slot 0x34 through the table word in EAX; 0x0058b8bb dispatches slot 0x30 through the table word in EAX; 0x0058b8d6 dispatches slot 0x4 through the table word in EAX; 0x0058b92e dispatches slot 0x10 through the table word in EDX; 0x0058b955 dispatches slot 0x10 through the table word in EDX; 0x0058b9ed dispatches slot 0x8 through the table word in EDX; the machine parse consumed 332 of 332 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, 0x10, 0x30, 0x34, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1787913b272cb8016413f441fe608495c09d9983a4a3decbdd163871965fbe14`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1d3151475ac74b0fdeb805b7e464e216c50c347d789b20bc61dc9a6808ec8af9`
- Pack digest quoted by the briefing: `1787913b272cb8016413f441fe608495c09d9983a4a3decbdd163871965fbe14`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`, `selection vtable, release ownership, and runtime button state remain gated`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
- selection vtable, release ownership, and runtime button state remain gated
