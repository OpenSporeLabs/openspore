# Validation 0x00c04750

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/00c04750_record_pointer_by_index.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 20-instruction listing names 2 data address(es) (0x1654c10, 0x16c7aa4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 1 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (20 of 20 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 20-instruction listing lie inside the recovered body span 0x00c04750..0x00c04787, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 20-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `082f87eeaa83fa92eee8c71d27b6a4d13c2889ac48d1fe7cc1570c359566a855`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b68e9be5eaab5ebbe9cec6c2af33de619f98025f215f7e1a70639429470dae2b`
- Pack digest quoted by the briefing: `082f87eeaa83fa92eee8c71d27b6a4d13c2889ac48d1fe7cc1570c359566a855`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this address.`, `The record type, the index semantics and the mode guard's intent can only be settled with a runtime trace that exercises the accessor in its live mode.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is index * 0x4e0 + base ever used as an offset rather than an address? The one inspected caller dereferences the result, which favours the address reading, but 12 callers were not inspected.
- No original-process trace exists for this address.
- The record type, the index semantics and the mode guard's intent can only be settled with a runtime trace that exercises the accessor in its live mode.
- What does 0x00f3c0e0 compute? Its two branches (a field of App::sScenarioMode and 0x00efc520) were not followed, so the index semantics are unknown.
- What does the +0xb8 flag word in the adjacent caller gate, and why does it return the constant 2 rather than a pointer?
- What is the 0x4e0-stride record type? Three field offsets are read by neighbouring code (0x4a8, 0x4ec, 0x504) but no declaration matches.
- What is the receiver class, and what is the +0x1c id?
