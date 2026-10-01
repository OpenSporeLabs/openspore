# Validation 0x005f4750

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Palettes__AdvancedItemViewer__func40h.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 5 data reference row(s) out of 0x005f4750 over 5 distinct address(es); segment breakdown: .rdata=5; access modes recorded: 4 read, 1 other;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 2 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 0 of 8 static checks evaluated, 0 passed, 8 had no evidence to evaluate; 7 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 7 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f388feca6fdacee6dce40da5ef2b613cdbdabc140eae7fc2f208ce7706eea125`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9ce45e4f815b975e5bd70ed537938a2680a6265a858ae4600da5472630010176`
- Pack digest quoted by the briefing: `f388feca6fdacee6dce40da5ef2b613cdbdabc140eae7fc2f208ce7706eea125`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
