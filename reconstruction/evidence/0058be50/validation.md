# Validation 0x0058be50

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Editors__cEditor__Update.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 26 data reference row(s) out of 0x0058be50 over 20 distinct address(es); 19 of them name writable storage (0x0150cd50, 0x0150cd54, 0x0150cd58, 0x0150cea8, 0x015e4f18, 0x015e4f1c, 0x015e4f20, 0x015e4fd4, 0x015e4fd8, 0x015e4fdc, 0x015e5114, 0x015fd918 and 1 more), which is where a mutable global can live; segment breakdown: .data=19, .rdata=7; access modes recorded: 20 read, 6 other;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 2 vtable reference(s) and the record associates 1 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 0 of 8 static checks evaluated, 0 passed, 8 had no evidence to evaluate; 7 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 7 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0c05259336d481db5c21aacdd57e4f529945d8a0055d2b9c05a35d470c618e7a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `11dbd48aa5c940f97e162288f190623987b2709fff308ee0610f9e436dec802c`
- Pack digest quoted by the briefing: `0c05259336d481db5c21aacdd57e4f529945d8a0055d2b9c05a35d470c618e7a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
