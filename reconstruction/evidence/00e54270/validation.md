# Validation 0x00e54270

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellUI__Load.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 73 data reference row(s) out of 0x00e54270 over 18 distinct address(es); 65 of them name writable storage (0x015a7d3c, 0x015a7d40, 0x015a7d44, 0x015a8418, 0x015a8530, 0x015a8534, 0x015fd928, 0x016b3c08, 0x016b3c0c, 0x016b3c28, 0x016b3c2c, 0x016b3c30), which is where a mutable global can live; segment breakdown: .data=65, .rdata=8; access modes recorded: 65 read, 8 other;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 0 of 8 static checks evaluated, 0 passed, 8 had no evidence to evaluate; 5 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 5 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `51436358ad2dc3ba8a96f09347409c0be6a26f02ee2c47b4524271a118d522a0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6faaa08d3d24dec9183ec30afae4a3ade2bd430e54e19870c6ca7364e589148b`
- Pack digest quoted by the briefing: `51436358ad2dc3ba8a96f09347409c0be6a26f02ee2c47b4524271a118d522a0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
