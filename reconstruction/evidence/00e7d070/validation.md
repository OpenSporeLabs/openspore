# Validation 0x00e7d070

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00e7d2c0/bounded_block_00e7d2c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `FAIL` | `partial` | the source-vs-xref rule: 1 address-named source call(s) have no call edge in the xref export: 0x00e7d2c0; the xref export at knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 13 outgoing call edge row(s) over 11 distinct address(es) for 0x00e7d070; 4 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 11 data reference row(s) out of 0x00e7d070 over 3 distinct address(es); 10 of them name writable storage (0x016b3c04, 0x016b3c14), which is where a mutable global can live; segment breakdown: .data=10, .rdata=1; access modes recorded: 11 read;  |
| FIELDS/OFFSETS | `WARN` | `partial` | 10 source field-offset declaration(s) (displacement 0x10, displacement 0x5190, field byte, field fifth) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `WARN` | `partial` | source constants are present and no machine listing is collected for this target, so they cannot be corroborated |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 0 passed, 4 had no evidence to evaluate; 8 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 8 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `fb7ca69d50279cbf3720e24b0c0f0f7e1f6146dd76081852786e97bf57ebf503`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `43db28b31980995eda84164149b39fea4a5df06439058912398c013ba8dac248`
- Pack digest quoted by the briefing: `fb7ca69d50279cbf3720e24b0c0f0f7e1f6146dd76081852786e97bf57ebf503`

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
