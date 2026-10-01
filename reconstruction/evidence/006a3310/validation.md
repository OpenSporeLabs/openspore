# Validation 0x006a3310

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_runtime_services_wave7/runtime_services_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006a3310; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field vtable and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names 1 indirect transfer(s): 0x006a3321 dispatches slot 0x2c through the table word in EAX; the machine parse consumed 9 of 9 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x2c, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'bool': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 9-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ef6106f7ed8ee4eb2adc6207bfd1abc812a1f999da2c35d208f58aaf526b7b09`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5bde37d1f8ce8a10163bf6d92ab58b8d9f44d620e9545cb3c92a4b84ad8cd261`
- Pack digest quoted by the briefing: `ef6106f7ed8ee4eb2adc6207bfd1abc812a1f999da2c35d208f58aaf526b7b09`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `required`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the virtual result require an additional release by callers?
- What is the exact intrusive_ptr layout and ownership transition?
- Which concrete virtual implementation is installed at +0x2c?
- required
