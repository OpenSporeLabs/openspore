# Validation 0x00e6d200

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__Cell__PlayAnimation.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 3 data reference row(s) out of 0x00e6d200 over 3 distinct address(es); 1 of them name writable storage (0x016b3c08), which is where a mutable global can live; segment breakdown: .data=1, .rdata=2; access modes recorded: 3 read;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 0 of 8 static checks evaluated, 0 passed, 8 had no evidence to evaluate; 6 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 6 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b829551f9d00d344d9261f25d4c67d61e9c8d9360fa4da800cfa5dfed00f695a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9a5e69313cd823e96a0af17c20784b4094fe56ae8845a10d7d45f417e5b5c139`
- Pack digest quoted by the briefing: `b829551f9d00d344d9261f25d4c67d61e9c8d9360fa4da800cfa5dfed00f695a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
