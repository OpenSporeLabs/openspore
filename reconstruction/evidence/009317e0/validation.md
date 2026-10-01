# Validation 0x009317e0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_file_stream_wave6/file_stream_adapter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 14-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 0 distinct address(es) for 0x009317e0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; 1 of those rows name an external import rather than an address and are not address-comparable, as in the projection |
| GLOBALS | `WARN` | `partial` | the complete 14-instruction listing names 1 data address(es) (0x13cc220) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field handle, path and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 1 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x4), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (14 of 14 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 14-instruction listing lie inside the recovered body span 0x009317e0..0x00931807, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 14-instruction body names 1 indirect transfer(s): 0x00931801 is INDIRECT_NON_VTABLE; the machine parse consumed 14 of 14 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00931801), so the dispatch's identity is not established: the target is the memory operand [0x013cc220], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `01c9907d85bcea42fea9007e3bb7405055448d19fe9b04c3e6482ac38534027a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d112bd532b6ec8a31323be590ce4c02a8ffebe920ef53a461c316be97a15d438`
- Pack digest quoted by the briefing: `01c9907d85bcea42fea9007e3bb7405055448d19fe9b04c3e6482ac38534027a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `conversion boundary, path encoding, and file-handle lifecycle remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- conversion boundary, path encoding, and file-handle lifecycle remain gated
- runtime validation not run
