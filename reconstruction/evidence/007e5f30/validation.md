# Validation 0x007e5f30

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_engine_runtime/engine_runtime.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x007e5f30; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field lifecycle_state_172, service_gate_16c and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it; the 2 displacement(s) in that same span are grounded within the machine-derived receiver bounds (0x16c, 0x172), so it is the name alone that is uncorroborated |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 13-instruction listing lie inside the recovered body span 0x007e5f30..0x007e5f59, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names 1 indirect transfer(s): 0x007e5f57 dispatches slot 0x18 through the table word in EDX; the machine parse consumed 13 of 13 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 3 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'std::uint32_t': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 13-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dd15dacd0f43b574187d15632a1abdf32481742991491678d01b852b7355a789`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `81655f6c9bbe5ee11dca22de43bb2c93a0f4c7f01ce296a2b21f952ee4a30487`
- Pack digest quoted by the briefing: `dd15dacd0f43b574187d15632a1abdf32481742991491678d01b852b7355a789`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-app-system-service-gate-and-vtable`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What EAX value is present on entry to the zero-gate path in real callers?
- What do selector 0x0462dde3 and the three zero words mean?
- What lifecycle or pause state is represented by receiver+0x16c and receiver+0x172?
- Which concrete vtable target occupies service+0x18 at runtime?
- Which table owner reaches the data pointer at 0x01413b48?
- concrete service vtable target
- gate-app-system-service-gate-and-vtable
- meanings of receiver +0x16c and +0x172
- selector and argument meanings
- zero-gate caller EAX residue
