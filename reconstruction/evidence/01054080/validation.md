# Validation 0x01054080

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `.spore-analysis/ghidra-exports/decompiled_sdk/Simulator__cGetOutOfUFOToolStrategy__OnSelect.c`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 14-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x01054080; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (14 of 14 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 14-instruction listing lie inside the recovered body span 0x01054080..0x010540a7, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 14-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `56aeb8e63f1ea6f8206c5b58d21aceb3cd7fef2313f411450f95e526d000e921`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ad04ac5552be5bda96c6bc9070a9fa5e31e0d7ddcc2dd3c89f06884a60fa090f`
- Pack digest quoted by the briefing: `56aeb8e63f1ea6f8206c5b58d21aceb3cd7fef2313f411450f95e526d000e921`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
