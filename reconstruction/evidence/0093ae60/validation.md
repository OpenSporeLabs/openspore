# Validation 0x0093ae60

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 6-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0093ae60; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 6-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field stream and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x4), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (6 of 6 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `WARN` | `partial` | 1 of 1 conditional branch target(s) fall outside the recovered body span 0x0093ae60..0x0093ae6e, so the listing is a slice and flow continues past it; the source span declares if |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 6-instruction body names 1 indirect transfer(s): 0x0093ae6e dispatches slot 0x14 through the table word in EAX; the machine parse consumed 6 of 6 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1b3333ab1dc85eb33646713c9b20e2268058089299bd54d25d0b1721fc3368c3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ec572de26a69ea63a7adbe36b4440008d43c6d95d3654ec32e4b5059d844fc73`
- Pack digest quoted by the briefing: `1b3333ab1dc85eb33646713c9b20e2268058089299bd54d25d0b1721fc3368c3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`, `stream vtable and delegated result ownership remain gated`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
- stream vtable and delegated result ownership remain gated
