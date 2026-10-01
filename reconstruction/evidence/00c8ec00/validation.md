# Validation 0x00c8ec00

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg13_creature_state/creature_state.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 10-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00c8ec00; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 10-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x19d8) and the 0 the complete 10-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x19d8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `FAIL` | `partial` | the source-vs-listing rule: 2 source constant(s) are absent from the machine listing: 0x1f, 0xff |
| CONTROL FLOW | `PASS` | `complete` | the complete 10-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 10-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'std::uint32_t' and the machine return state is WIDTH_4_IN_EAX: the complete 10-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `109ea4499c450defc575ecaee3f332b7bd56471abaa6a7dbdd1b8dcb50f05d0f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `672fcff41bb4e5cc496a68492cfa1ac084696986ec9eeeb51c20af443fd979a0`
- Pack digest quoted by the briefing: `109ea4499c450defc575ecaee3f332b7bd56471abaa6a7dbdd1b8dcb50f05d0f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `tribe_purchased_tools_mask_observation`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process mask value or caller outcome has been observed.
- The exact concrete state owner at ECX is not fully reconstructed, although the persisted layout and caller flow identify a tribe-state-shaped receiver.
- The semantic producer and complete meaning of all 32 purchased-tool bits remain unresolved.
- concrete state owner
- mask producer
- runtime mask value
- tool-index producer semantics
- tribe_purchased_tools_mask_observation
