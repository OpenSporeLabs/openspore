# Validation 0x0059cf00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_editor_runtime_wave7/editor_runtime_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 36-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 36-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x8, 0x38), all of which the record accounts for or the listing is the better witness on; the 36-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=36, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x8, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x8), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 36-instruction listing lie inside the recovered body span 0x0059cf00..0x0059cf57, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 36-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7f981d398e91fe5185b1e14be40a9e46bc0bd758fdb049ea911cec2a8f46fc7b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `29db93066400ccb4673b9a61f340cea69e5533bf84b5525e47cc48b7e29bba58`
- Pack digest quoted by the briefing: `7f981d398e91fe5185b1e14be40a9e46bc0bd758fdb049ea911cec2a8f46fc7b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Coordinate space and units of the forwarded Vector3`, `Coordinate space and units of the forwarded Vector3; Whether ignoreZ is ever set in practice by editor input paths; Interaction between applyNow and the ground-follow raycast in the target`, `Interaction between applyNow and the ground-follow raycast in the target`, `Whether ignoreZ is ever set in practice by editor input paths`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Coordinate space and units of the forwarded Vector3
- Coordinate space and units of the forwarded Vector3; Whether ignoreZ is ever set in practice by editor input paths; Interaction between applyNow and the ground-follow raycast in the target
- Interaction between applyNow and the ground-follow raycast in the target
- Whether ignoreZ is ever set in practice by editor input paths
- concrete runtime owners and values remain unresolved
