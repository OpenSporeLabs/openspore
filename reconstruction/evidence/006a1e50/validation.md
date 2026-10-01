# Validation 0x006a1e50

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x006a1e50; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x28, 0x38) and the 1 the complete 13-instruction listing names through ECX (0x38) are all within the machine-derived receiver bounds (0x0, 0x28, 0x38), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 13-instruction listing lie inside the recovered body span 0x006a1e50..0x006a1e70, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names 1 indirect transfer(s): 0x006a1e5f dispatches slot 0x28 through the table word in EDX; the machine parse consumed 13 of 13 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x28, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ed9ee13e79578c80ab0532b3a1c03b2b4ce6604f6361984caca62649fd08ba50`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `19b5cadc69d4283cc782f87870b83eb77200b466f09692a5391dd37e06a287a9`
- Pack digest quoted by the briefing: `ed9ee13e79578c80ab0532b3a1c03b2b4ce6604f6361984caca62649fd08ba50`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The base routine's parent-chain termination and inheritance policy are runtime behavior.`, `The concrete vtable owner behind slots +0x28 and +0x20 is unresolved.`, `gate-property-list-get-alt-parent-chain-and-vtable-ownership`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete vtable owners behind slots +0x28 and +0x20
- No original-process invocation or indirect-caller trace was captured.
- Ownership of the returned property pointer
- Runtime meaning of the fast_count word at +0x38
- The base routine's parent-chain termination and inheritance policy are runtime behavior.
- The concrete vtable owner behind slots +0x28 and +0x20 is unresolved.
- Whether the base routine walks a parent chain and how deep
- gate-property-list-get-alt-parent-chain-and-vtable-ownership
