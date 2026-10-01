# Validation 0x00d2e830

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg13-c1-creature-progression/creature_progression.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 32-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 2 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (32 of 32 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 32-instruction listing lie inside the recovered body span 0x00d2e830..0x00d2e893, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 32-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a85ad59f17219a57b4fd74b820271ff28fff1fb63026804e0794a8b28428f0e5`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0cbbe79dd14577a96281a5c7c1007f18fe3473c4395ef50f2ef47398617e35b2`
- Pack digest quoted by the briefing: `a85ad59f17219a57b4fd74b820271ff28fff1fb63026804e0794a8b28428f0e5`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process level-selection trace has been run.`, `Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.`, `Resolve concrete progression-player and noun-manager ownership and threshold writers.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process level-selection trace has been run.
- Observe 0x0167eae0, the +0x74 returned object, the +0x10f0 float, and the four threshold globals in an original process.
- Resolve concrete progression-player and noun-manager ownership and threshold writers.
- The SDK semantic name for this selector is unresolved; the normalized symbol remains opaque.
- The later virtual action selected by the caller after sentinel 4 is outside this target.
- The runtime relationship between the progression-player +0x10f0 field and DAT_0169e398 is not established by this body.
