# Validation 0x006a3180

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_direct_property_wave6/direct_property_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 110-instruction listing name the same 4 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x006a3180..0x006a3296 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a31f9, 0x006a326c, 0x006a3280; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 4 distinct address(es) for 0x006a3180; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 110-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field field_00, field_04, field_12, field_18 and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (110 of 110 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 8 conditional branch target(s) in the complete 110-instruction listing lie inside the recovered body span 0x006a3180..0x006a3296, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 110-instruction body names 1 indirect transfer(s): 0x006a31c9 dispatches slot 0x50 through the table word in EDX; the machine parse consumed 110 of 110 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `537b615e936c5d4851871ffb6bc25c4d86411513912a5c41af7413f49e547dd7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cd582e1a9927a36152d0ce6fa2f15f0bfdfaa98d8e9d312444e495ff90f3a735`
- Pack digest quoted by the briefing: `537b615e936c5d4851871ffb6bc25c4d86411513912a5c41af7413f49e547dd7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`, `vector allocation, service metadata, map lifetime, and destination ownership remain gated`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
- vector allocation, service metadata, map lifetime, and destination ownership remain gated
