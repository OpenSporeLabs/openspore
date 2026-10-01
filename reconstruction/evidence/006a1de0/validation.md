# Validation 0x006a1de0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-orchestrate-dogfood-006a1de0/dogfood_006a1de0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 47-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a1de0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 47-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 displacement(s) (0x4) lie outside the machine-derived receiver bounds (0x18, 0x1c, 0x2c, 0x30) for ECX, so the source and the body disagree with the receiver record; the source span declares 0x4, 0x18, and the complete 47-instruction listing names none through that register |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (47 of 47 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 47-instruction listing lie inside the recovered body span 0x006a1de0..0x006a1e44, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 47-instruction body names 1 indirect transfer(s): 0x006a1e39 dispatches slot 0x20 through the table word in EAX; the machine parse consumed 47 of 47 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x20, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f4946786c2443caabc9a07a9a0dbb76ece8e26ef2bde370f87d2abf6f01d20c1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4f560facb9f5dc3f568cdeb3cebdc679a3de436863f13bdcd6b0e9b2672434d3`
- Pack digest quoted by the briefing: `f4946786c2443caabc9a07a9a0dbb76ece8e26ef2bde370f87d2abf6f01d20c1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation and no indirect-caller trace were captured for this record.`, `The concrete implementation behind +0x20 (0x006a1de0 in the table read here, but the runtime table of the +0x30 object was not captured) is a runtime gate.`, `The pointee type and ownership of the word at entry+0x04 are unresolved; no runtime observation of the returned address was captured.`, `The runtime object that supplies the +0x30 word and its class identity are unobserved; the chain depth and its termination condition are data dependent.`, `Whether the entry span is sorted at runtime, and therefore whether the unsigned lower bound is a valid search, is a runtime property of the data.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No ABI projection was published in the worker briefing (evidence.missing_sections = [ABI]); the whole ABI block above is derived from the 47-instruction body, from the RET 0x8 exits and from the tail-jump caller record 0x006a1e50.
- No original-process invocation and no indirect-caller trace were captured for this record.
- The concrete class of the object at +0x30 is inferred, not proved: it answers slots +0x1c and +0x20 with the shapes this table provides, and the in-repo analogue calls that field 'parent'.
- The concrete implementation behind +0x20 (0x006a1de0 in the table read here, but the runtime table of the +0x30 object was not captured) is a runtime gate.
- The pointee type and ownership of the word at entry+0x04 are unresolved; no runtime observation of the returned address was captured.
- The recovered class size of PropertyList; 0x34 is only this body's read frontier, while the analogue record reports a 56-byte gtype.
- The runtime object that supplies the +0x30 word and its class identity are unobserved; the chain depth and its termination condition are data dependent.
- The runtime value range and meaning of the mode byte at +0x2c, which is dead in this body.
- The type, size and ownership of the word at entry+0x04; only its address is observable.
- Whether the 'parent' relation is inheritance, aggregation or an override chain, and how the chain terminates.
- Whether the entry span is sorted at runtime, and therefore whether the unsigned lower bound is a valid search, is a runtime property of the data.
- Why the table word at +0x48 is null and whether 0x4c starts a second related table.
