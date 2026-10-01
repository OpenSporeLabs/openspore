# Validation 0x007e6100

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_lifecycle_wave7/app_lifecycle_wave7.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 19-instruction listing names 1 data address(es) (0x143e9b4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (19 of 19 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `WARN` | `partial` | 2 of 4 conditional branch target(s) fall outside the recovered body span 0x007e6100..0x007e612e, so the listing is a slice and flow continues past it; the source span declares no branch keyword |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 19-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 2 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a972ed663ab0f4520fcf30e021944ee9754ef6f68985e6b8190aeaadf570fcbc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `4022e377d9efeeeb9f2b94e9be44986c9c6e0803b1f2919fc3171e8cd2feed2b`
- Pack digest quoted by the briefing: `a972ed663ab0f4520fcf30e021944ee9754ef6f68985e6b8190aeaadf570fcbc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe the input string values, the output buffer lifetime, and the concrete helper objects at the 0x0067xxxx service addresses before promoting collection identity semantics.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Actual vtable or indirect caller represented by the data reference at 0x007e9129
- Concrete ownership and identity of each service returned by the 16 helper calls
- Observe the input string values, the output buffer lifetime, and the concrete helper objects at the 0x0067xxxx service addresses before promoting collection identity semantics.
- Runtime contents of the output buffer and address 0x0153f864
