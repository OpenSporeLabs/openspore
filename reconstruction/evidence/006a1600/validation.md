# Validation 0x006a1600

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 27-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006a1600; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 27-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 5 displacement(s) (0x4, 0x14, 0x18, 0x1c, 0x34) and every one of them is a displacement the complete 27-instruction listing shows: 1 attributed to the receiver ECX as proven (0x34); 4 more (0x4, 0x14, 0x18, 0x1c) are shown by the listing under a base that is not the receiver -- 0x4 under ESI, ESP; 0x14 under EAX; 0x18 under EAX; 0x1c under EAX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 27-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=27, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x34) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x34), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (27 of 27 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 27-instruction listing lie inside the recovered body span 0x006a1600..0x006a1634, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 27-instruction body names 1 indirect transfer(s): 0x006a1625 dispatches slot 0x14 through the table word in EAX; the machine parse consumed 27 of 27 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x14, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `012b53db50b478a4b4056df551d785b4777960f43a383c6b6885e3ad826c1bd9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ba2bdddec69208f74d7f8d6c360a70b5bf69c08d3b0b9b0d60761d260a61414c`
- Pack digest quoted by the briefing: `012b53db50b478a4b4056df551d785b4777960f43a383c6b6885e3ad826c1bd9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The concrete vtable target behind slot +0x14 is unresolved; the model keeps it an indirect port.`, `The source list is assumed to be a stable span between +0x18 and +0x1c; runtime layout is unverified.`, `gate-property-list-vtable-set-slot-ownership`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete vtable owner and per-property semantics of slot +0x14
- Meaning of the this+0x34 operation counter
- No original-process invocation or indirect-caller trace was captured.
- Runtime ordering guarantees of the source list span
- The concrete vtable target behind slot +0x14 is unresolved; the model keeps it an indirect port.
- The source list is assumed to be a stable span between +0x18 and +0x1c; runtime layout is unverified.
- Whether the callee takes ownership of the copied property payload
- gate-property-list-vtable-set-slot-ownership
