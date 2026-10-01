# Validation 0x00e63560

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__cCellGFX__LoadEffectMap.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 35 data reference row(s) out of 0x00e63560 over 18 distinct address(es); 27 of them name writable storage (0x016b3c04, 0x016b3c08, 0x016b3c0c, 0x016b3c54, 0x016b3c58, 0x016b3c5c, 0x016b3c60, 0x016b3c88, 0x016b3c8c, 0x016b3c90, 0x016b3c94, 0x016b3c98 and 1 more), which is where a mutable global can live; segment breakdown: .data=27, .rdata=7, .text=1; access modes recorded: 30 read, 5 other;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 0 of 8 static checks evaluated, 0 passed, 8 had no evidence to evaluate; 7 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 7 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `eef22ae37ae84fc5fd25f3e4f810395c35e77b80f327d6d53c9079f152c58d79`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `45ae67eff101ca367bbfc8738e66d81f719d96d03450b9e1baaf9cc777ae0097`
- Pack digest quoted by the briefing: `eef22ae37ae84fc5fd25f3e4f810395c35e77b80f327d6d53c9079f152c58d79`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
