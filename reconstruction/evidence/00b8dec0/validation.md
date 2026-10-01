# Validation 0x00b8dec0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/00b8dec0_indexed_element_accessor.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 2 the complete 11-instruction listing names through ECX (0x15c, 0x160) are all within the machine-derived receiver bounds (0x15c, 0x160), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00b8dec0..0x00b8dee5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d39399214c42e3dc282b008eb528b7335d500cf3f9d44c76470f31d06dcbaa50`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7e8d4888dbeab03b86fe9945903b027932c24a5bfe86f24fa5e9761922c14e94`
- Pack digest quoted by the briefing: `d39399214c42e3dc282b008eb528b7335d500cf3f9d44c76470f31d06dcbaa50`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this address.`, `The element type and the owning class can only be settled with a receiver trace or by inspecting the 22 remaining call sites.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do any of the 22 uninspected callers pass a negative index? The one caller that was disassembled does not; the others are unknown.
- Is the +0x164 word (a capacity pointer in a three-pointer vector layout) also maintained by the container? It is never read here, so the reconstruction does not model it.
- Is the zero out-of-range answer relied upon as a sentinel by the callers, or is it merely a discarded value? Not established.
- No original-process trace exists for this address.
- The element type and the owning class can only be settled with a receiver trace or by inspecting the 22 remaining call sites.
- What is the element type? A single caller dereferences it and reads +0x14; the other 22 callsites were not inspected and no common type was established.
- Which class owns the block? The one disassembled thunk shows owner+0x13c, but no vtable or SDK type was located for that owner.
