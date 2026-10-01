# Validation 0x01021180

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `missing`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 65-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (65 of 65 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 65-instruction listing lie inside the recovered body span 0x01021180..0x010211f5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 65-instruction body names 5 indirect transfer(s): 0x01021196 is FUNCTION_POINTER; 0x010211aa is FUNCTION_POINTER; 0x010211ba is FUNCTION_POINTER; 0x010211d4 is UNRESOLVED; 0x010211e4 is UNRESOLVED; the machine parse consumed 65 of 65 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 5, so the dispatch is visible in the machine listing but is not proven: 3 of the 5 indirect transfer(s) classify as FUNCTION_POINTER (0x01021196, 0x010211aa, 0x010211ba), so the dispatch's identity is not established: ESI is loaded from [ESP + 0x1c], but ESP is defined by an immediate or register assignment, not a memory load earlier in the listing, so the word it names is not shown to be a table word and 2 of the 5 indirect transfer(s) classify as UNRESOLVED (0x010211d4, 0x010211e4), so the dispatch's identity is not established: ESI is defined by an immediate or register assignment, not a memory load before 0x010211d4 |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9ab1c5ac2f928daed652a07598ce3230cf0ff04434ef6c96057fe2274e7fdc7d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `16434c99ff893c3c9c1bab49fde2960bd11eb60cde4c0df3659191cf3acd2372`
- Pack digest quoted by the briefing: `9ab1c5ac2f928daed652a07598ce3230cf0ff04434ef6c96057fe2274e7fdc7d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
