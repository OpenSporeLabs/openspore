# Validation 0x006a2a40

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_property_safe_wave9/property_safe_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 22-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x006a2a40; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 22-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 3 displacement(s) (0x14, 0x18, 0x30) and every one of them is a displacement the complete 22-instruction listing shows: 2 attributed to the receiver ECX as proven (0x18, 0x30); 1 more (0x14) are shown by the listing under a base that is not the receiver -- 0x14 under EBX, EDI -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 22-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=22, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x18, 0x30) and 1 more only on one arm of a branch, which is a may and grounds nothing (0x2c); the machine-derived receiver record enumerates 1 displacement(s) (0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x18), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (22 of 22 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 22-instruction listing lie inside the recovered body span 0x006a2a40..0x006a2a6f, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 22-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `21251651ca037c1cab9c23e4cb6d7df442392970ece5f3f000ff7b6946f193e4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d6a9074eb6313ed848695d4648309a2a04029a369e7cbaad0209d835ccb8d26e`
- Pack digest quoted by the briefing: `21251651ca037c1cab9c23e4cb6d7df442392970ece5f3f000ff7b6946f193e4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `SetParent's side effects on the parent word and the operation counter are unresolved.`, `The map-copy port's real allocation, growth, and partial-copy behavior are unresolved.`, `gate-property-list-map-copy-port-and-set-parent-runtime-behavior`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process invocation or indirect-caller trace was captured.
- Ownership transfer for copied property payloads
- Real map-copy semantics of 0x006a1e80 including growth and truncation
- SetParent side effects beyond its arguments
- SetParent's side effects on the parent word and the operation counter are unresolved.
- The map-copy port's real allocation, growth, and partial-copy behavior are unresolved.
- Whether the lookup-mode byte copy is ordered before or after map growth in the real port
- gate-property-list-map-copy-port-and-set-parent-runtime-behavior
