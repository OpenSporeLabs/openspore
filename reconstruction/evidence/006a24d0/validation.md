# Validation 0x006a24d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_resources/property_list_variants.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 41-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a24d0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field entries_end, key, parent, properties and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (41 of 41 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 41-instruction listing lie inside the recovered body span 0x006a24d0..0x006a252a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 41-instruction body names 1 indirect transfer(s): 0x006a2521 dispatches slot 0x28 through the table word in EAX; the machine parse consumed 41 of 41 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d564388736e129d972b595b20418e7f337bb0e5c11ecf8f7048be2ca5107e1e9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c82efabc58822dbaa01a15ed8e62b17e559e961fe11c5c6d9848de08881c2675`
- Pack digest quoted by the briefing: `d564388736e129d972b595b20418e7f337bb0e5c11ecf8f7048be2ca5107e1e9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-property-list-parent-dispatch-sentinel-and-lifetime`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete parent PropertyList subtype and vtable +0x28 implementation
- Runtime contents and ownership of the global 0x016027d0 sentinel object
- Whether callers distinguish the no-parent sentinel from a valid property pointer
- gate-property-list-parent-dispatch-sentinel-and-lifetime
- global 0x016027d0 sentinel contents
- parent subtype and slot +0x28 implementation
- returned property ownership
