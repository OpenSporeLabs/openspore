# Validation 0x00bca0c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/00bca0c0_fixed_table_lookup.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 37-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (37 of 37 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 37-instruction listing lie inside the recovered body span 0x00bca0c0..0x00bca111, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 37-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7e1063a25438f0ddf4a033b1507f5f79626e8414d96703f1e369ce33e59ede8a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `608cd59ef8d74bf102a09a1d810e4d29ebb49c4137574de97941b328496b130b`
- Pack digest quoted by the briefing: `7e1063a25438f0ddf4a033b1507f5f79626e8414d96703f1e369ce33e59ede8a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this address.`, `The record semantics and the owning class can only be settled with a receiver trace or by locating a writer of the eight records.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do the remaining 15 callers use the identifier and slot index, or only the found/not-found bit like 0x00ba48b0? Not established.
- Is the table ever mutated after construction (so that the linear search and the fixed count stay valid)? No writer was located in this batch.
- No original-process trace exists for this address.
- The record semantics and the owning class can only be settled with a receiver trace or by locating a writer of the eight records.
- What are the four key fields and the 16-bit identifier? Nothing in the body or in the one inspected caller names them.
- What lives in the unobserved 0x10 bytes at record+0x0c..+0x1b and the 0x20 bytes at record+0x24..+0x43? The body never reads them.
- Which class owns the table? The one caller passes a sub-object pointer found at its own +0xb48; no vtable was located.
