# Validation 0x00835380

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_core_wave6/utfwin_core_wave6.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00835380; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 7 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00835380..0x0083539b, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1bc937f14b2d092b014948f0b6ae1176838c6f48a650bc4d015187904a591319`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a2ccbc172f6f090b07f2249a36032d7e51ec9dd42c24328b2f4e7d6683305ded`
- Pack digest quoted by the briefing: `1bc937f14b2d092b014948f0b6ae1176838c6f48a650bc4d015187904a591319`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run`, `tooltip reference owners, vtable identities, sentinel publication, and deallocator remain gated`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- runtime validation not run
- tooltip reference owners, vtable identities, sentinel publication, and deallocator remain gated
