# Validation 0x00b3d3e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg11_h2_root_accessors/root_accessors.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 2-instruction listing names 1 data address(es) (0x167eb24) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 4 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `951d13488013b8e504ec40d02daf62aafb9222395200c5464c44d139f8303ab6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9ef1fd51cbe354e38142852ab182682ac94b8adcb5400ade6cbbcaae5a7a9655`
- Pack digest quoted by the briefing: `951d13488013b8e504ec40d02daf62aafb9222395200c5464c44d139f8303ab6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-root-slot-00b3d3e0`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What concrete object and vtable can the slot contain?
- What lifetime guarantee, if any, applies to a nonzero returned word?
- Which callers interpret the returned word as a pointer, and which treat it as a raw value?
- Which code publishes, replaces, or clears 0x0167eb24?
- gate-root-slot-00b3d3e0
- runtime validation not run
