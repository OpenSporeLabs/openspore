# Validation 0x00641e10

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sporepedia-slot-release/sporepedia_slot_release.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 19-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00641e10; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 19-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x20) and the 0 the complete 19-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x20), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (19 of 19 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 19-instruction listing lie inside the recovered body span 0x00641e10..0x00641e3a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 19-instruction body names 1 indirect transfer(s): 0x00641e29 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 19 of 19 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 8 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8ed82f9430e6582eb58f0e75e6c526eb4173a607d37f7817e87c1955c66d362a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `06f28a0cc4b7bcb3044b994c09f45ef1c1ffab10a369c84d4d6fd6cda16e169d`
- Pack digest quoted by the briefing: `8ed82f9430e6582eb58f0e75e6c526eb4173a607d37f7817e87c1955c66d362a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the slot's return value or side effect matter to this body? EAX is overwritten by the direct call at 0x00641e30, so the body itself discards whatever the slot leaves there.
- Is 0x00641e10 the only implementation of this shape, or an override of a shared base helper? No RTTI and no vtable pass exist for this binary, and the record's association is transitive.
- Is the dispatch word at [pointee+0x0] a class vtable, and which class and vtable is it? The record associates eight vtables with this target transitively, which does not identify the one the body reads.
- The machine-derived receiver record is bounds_only and enumerates 0x20 and nothing else, so it states where the body was seen reaching and is not an enumeration of the receiver's words: it corroborates the 0x20 displacement and cannot refute any other receiver word. Displacement 0x4 is formed at 0x00641e2c but never dereferenced, so its absence from the record is consistent with a dereference-based observation rather than a disagreement -- but the record's own observation criteria are not documented, so it is not established here that a bounds_only record would have listed it.
- What contract does 0x005bf0e0 implement? It is a shared two-pointer helper that itself dispatches to a service slot at displacement 0x2c, but this body does not identify the service it reaches.
- What does the slot at displacement 4 of the pointee's dispatch word resolve to? No record for this target names the table, the slot or the callee, so the one indirect transfer in the body has no identified target.
- What is the receiver's word at displacement 0x20? The receiver record enumerates the displacement and nothing about the member: not whether it is owned, borrowed or a smart handle, and not its type.
- Why is the word cleared before the slot runs rather than after? The ordering is observable in the listing, but its purpose (re-entrancy guard, ownership transfer to the callee) is not established.
