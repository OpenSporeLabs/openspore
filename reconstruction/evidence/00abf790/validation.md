# Validation 0x00abf790

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_cheat_wave9/cheat_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 16-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00abf790; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 16-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (16 of 16 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 16-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 16-instruction body names 1 indirect transfer(s): 0x00abf7af dispatches slot 0x24 through the table word in EDX; the machine parse consumed 16 of 16 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 12 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x24, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ef7c1b1318490c13ee67fe7895833bb44997d2419bec04e1a6625f841f82996f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3a75b1c1169e9f8e26deeb8819bb95f0ca664bb904625f6f327b70022dc0666a`
- Pack digest quoted by the briefing: `ef7c1b1318490c13ee67fe7895833bb44997d2419bec04e1a6625f841f82996f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The model's port is null by default, so an unconfigured call is a closed gate rather than a live fetch.`, `The service global at 0x0167ead8 and its lifetime are unresolved.`, `The service vtable owner behind slot +0x24 is unresolved.`, `The three forwarded words carry no decoded meaning at this level.`, `gate-cheat-service-global-and-slot-24-ownership`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete service type and vtable owner behind slot +0x24
- Decoded meaning of the three forwarded words
- No original-process invocation or indirect-caller trace was captured.
- Producer, lifetime, and reset of the service global at 0x0167ead8
- The model's port is null by default, so an unconfigured call is a closed gate rather than a live fetch.
- The service global at 0x0167ead8 and its lifetime are unresolved.
- The service vtable owner behind slot +0x24 is unresolved.
- The three forwarded words carry no decoded meaning at this level.
- Why the manager is forwarded as a data word rather than a receiver
- gate-cheat-service-global-and-slot-24-ownership
