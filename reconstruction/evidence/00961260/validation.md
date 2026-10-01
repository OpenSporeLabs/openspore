# Validation 0x00961260

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_layout_wave6/utfwin_layout_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 4-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00961260; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 4-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 4-instruction listing names through ECX (0x38) are all within the machine-derived receiver bounds (0x38), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (4 of 4 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 4-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 4-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `71ef016b86442683bc34f767d24b61b8a989ad776ac81a42f9febfafd5a51a54`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `17704f107e68ff6bd442a37e2c988da5a8c5e36c18d128c9f57d810bfebf73d3`
- Pack digest quoted by the briefing: `71ef016b86442683bc34f767d24b61b8a989ad776ac81a42f9febfafd5a51a54`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `cast field semantics and output ownership remain gated`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- cast field semantics and output ownership remain gated
- runtime validation not run
