# Validation 0x006a3070

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a3070; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x18, 0x1c) and the 0 the complete 31-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x18, 0x1c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 31-instruction listing lie inside the recovered body span 0x006a3070..0x006a30b7, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9ebeaa953b0abd3b6d7ea45930fb3640621c5cae0a824c96194a8779eaca1d5f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d56a900bc8777fe9176a34ca1dd13aa4e1dc47e8ca1b7e8e99380961e15bb613`
- Pack digest quoted by the briefing: `9ebeaa953b0abd3b6d7ea45930fb3640621c5cae0a824c96194a8779eaca1d5f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The raw signed quotient is forwarded without a negative clamp; runtime behavior for a malformed span is unverified.`, `The resize port's real allocator, capacity policy, and zero-fill are unresolved.`, `gate-property-list-word-vector-resize-port-behavior`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Behavior when the map span is inconsistent (negative quotient)
- Caller expectation for the resulting vector capacity
- No original-process invocation or indirect-caller trace was captured.
- Real resize port allocator and capacity policy
- The raw signed quotient is forwarded without a negative clamp; runtime behavior for a malformed span is unverified.
- The resize port's real allocator, capacity policy, and zero-fill are unresolved.
- Whether the destination vector is required to be empty on entry
- gate-property-list-word-vector-resize-port-behavior
