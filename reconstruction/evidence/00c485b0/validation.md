# Validation 0x00c485b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 3-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 3-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=3, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (3 of 3 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 3-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 3-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2e13b78386b9988fa84051f38952907bc359288735896b09b4891672e2c85ecf`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `76d10d6525dc3e6ea5ce3d6233c2dff6c8da881d7f4cc3c1e6ad4c7c626087ff`
- Pack digest quoted by the briefing: `2e13b78386b9988fa84051f38952907bc359288735896b09b4891672e2c85ecf`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test must confirm that 0x00c47cc0's RET 4 still matches in the shipping build, since the whole tail-call reading depends on it.`, `No original-process trace has been captured for 0x00c485b0, so the claim that the +0x84 write is the only persistent effect is static-only.`, `The value stored at +0x84 before and after each of the 16 call sites must be observed to confirm the idempotence guard is exercised rather than always false.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test must confirm that 0x00c47cc0's RET 4 still matches in the shipping build, since the whole tail-call reading depends on it.
- Fifteen of the sixteen observed call sites were not disassembled, so the context in which mode 2 is selected is unverified.
- Is 0x00c47d80 the same operation without the mode guard? Its body clears both buffers and then always runs the Init transition, with no comparison against the incoming value, which suggests the pair is 'transition unconditionally' versus 'transition if the mode actually changes'.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00c485b0, so the claim that the +0x84 write is the only persistent effect is static-only.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- The value stored at +0x84 before and after each of the 16 call sites must be observed to confirm the idempotence guard is exercised rather than always false.
- What class owns 0x00c485b0? The offset signature (+0x84 mode, +0x14c/+0x150 and +0x15c/+0x160 wchar cursors, +0x194 kind) matches no ModAPI declaration, and no vtable for the receiver was located.
- What is the value 3 that unlocks the App::IAppSystem::Init(0x13eb844) transition, and which caller performs it? Only 0x00c485b0 (value 2) and 0x00c47d80 (unconditional variant) were located in this session; a caller of 0x00c47cc0 with 3 was not found.
- Why do the two buffers get truncated on every mode change? The evidence shows that it happens; it does not show whether the old contents are meant to be discarded or re-derived.
