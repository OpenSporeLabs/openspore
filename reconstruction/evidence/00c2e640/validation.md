# Validation 0x00c2e640

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_camera_wave8/camera_wave8.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00c2e640; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 9-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 9-instruction listing lie inside the recovered body span 0x00c2e640..0x00c2e65d, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'OpaqueEditorCamera*': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 9-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5a9d3c5909d51b71e429a8f28488b793de1d4423540abfefabe2ea3b967c7e69`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cf0dc35f4aed00c326629786f8b6ab75acdfbc410bd135568d5086fdc82e7e8b`
- Pack digest quoted by the briefing: `5a9d3c5909d51b71e429a8f28488b793de1d4423540abfefabe2ea3b967c7e69`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original runtime invocation or indirect caller trace was captured for this imported-name entry.`, `No original runtime invocation or indirect caller trace was captured for this imported-name entry.; The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.`, `The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original runtime invocation or indirect caller trace was captured for this imported-name entry.
- No original runtime invocation or indirect caller trace was captured for this imported-name entry.; The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.
- The 0x0146b420 family association is static xref evidence and requires runtime dispatch confirmation before promotion.
- concrete runtime owners and values remain unresolved
