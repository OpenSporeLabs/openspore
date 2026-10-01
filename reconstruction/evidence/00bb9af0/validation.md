# Validation 0x00bb9af0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b06/bb9af0_star_record_flag_test.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 6-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 6-instruction listing names through ECX (0x5c) are all within the machine-derived receiver bounds (0x5c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (6 of 6 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 6-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 6-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9fa070f257b6fe2f09515e86de29e96a175ce1b8ae0af49c7fd025edc8246b7d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ba98e809b4a4ddc83594f76e1fa1a0690be70b3f58fd9d6bac34f6d447db8ad3`
- Pack digest quoted by the briefing: `9fa070f257b6fe2f09515e86de29e96a175ce1b8ae0af49c7fd025edc8246b7d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would have to confirm the flag word's value for a known star system, which is the only way to attach a meaning to individual bits.`, `Because the function dereferences ECX with no null check, a runtime test that passes a null receiver would fault; that is a property of the original and must be preserved, not defended against.`, `No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would have to confirm the flag word's value for a known star system, which is the only way to attach a meaning to individual bits.
- Because the function dereferences ECX with no null check, a runtime test that passes a null receiver would fault; that is a property of the original and must be preserved, not defended against.
- Does any caller pass a multi-bit mask? The AND would handle it as ANY, but all five inspected callsites pass a single bit, so multi-bit use is supported by the body and unconfirmed by any caller.
- Is this function reachable through a vtable? Every observed call is a direct CALL and no table slot was located for 0x00bb9af0, so its interface status, if any, is unestablished.
- No original-process trace has ever been captured for this function; the original Cell stage has never been entered in any recorded run. Every claim here is static.
- The briefing's canonical ledger recorded caller_count 20; the live query also returns 20 caller functions but 25 call sites, because 0x00ba6f20, 0x00b96d40 and 0x00bb2070/0x00bb21b0 call it more than once. The fan-in figure is not a contradiction, only a different counting convention.
- What does each individual bit of mFlags mean? Bits 0, 1, 2, 8, 13, 17 and 31 were observed at callsites, but no flag name was established for any of them. Spore-ModAPI's own comment on this field ('TODO 1 << 4 (16) is visited?') shows the upstream project has not settled the bit assignment either.
- Why is the return value computed with NEG/SBB/NEG rather than a SETNE? Both produce 0/1, so the behaviour is identical; the choice is a codegen artefact and carries no semantic content. Recorded so the byte sequence is not mistaken for three meaningful operations.
