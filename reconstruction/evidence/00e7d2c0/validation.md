# Validation 0x00e7d2c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 224-instruction listing names 3 data address(es) (0x147b9f0, 0x16b3c04, 0x16b3c14) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 5 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (224 of 224 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 31 conditional branch target(s) in the complete 224-instruction listing lie inside the recovered body span 0x00e7d070..0x00e7d360, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 224-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `06836bba98de9e29f0ac5f70b0cf038dbb60dbb3e30c9ceec2c8985d0c6fa3e2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `fbdf886ce56dcb8aff1d853f8f8a4718168307fea7a64807267190c8da21fcc0`
- Pack digest quoted by the briefing: `06836bba98de9e29f0ac5f70b0cf038dbb60dbb3e30c9ceec2c8985d0c6fa3e2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is ESI provably zero on every path that reaches 0x00e7d2b7? The listing has exactly one definition of ESI, `XOR ESI,ESI` at 0x00e7d23d, and it dominates this block by inspection, but no dominator computation was run and the model does not depend on it.
- Is the enclosing function variadic? The record lists variadic_suspected and variadic_not_decidable_from_listing and states that the suspicion removes any guarantee about the stack-argument extent. The block's own five words are accounted for; the function's are not.
- Is this body a virtual member of some class, and of which? The record declines to name a receiver and the body contains no indirect transfer, so nothing in this repository places it in a class or a slot.
- What do the two selector immediates 0x9ef61113 and 0xac7161b5 mean, and what does the callee at 0x00e394f0 do with them? The two-arm shape is established; the meaning of either arm is not.
- What is the enclosing function FUN_00e7d070 for? Its decompilation was never collected, eleven callees are unresolved, and 203 of its 224 instructions are untranscribed here.
- What is the word at the absolute address 0x016b3c04, and what object does it point at? The block reads it and then reads 0x5190 bytes into the result, but no type, size, class or lifetime for either is established here and none is guessed.
- Why does the CALLS oracle see no callee for this VA? The xref export keys rows on 0x00e7d070, the function's real entry, and carries no row for the interior address 0x00e7d2c0, while the evidence pack's listing is the whole 224-instruction body. The two machine oracles therefore disagree by construction for this target and the disagreement is not a property of any reconstruction.
