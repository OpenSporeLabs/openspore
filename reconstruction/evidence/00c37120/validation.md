# Validation 0x00c37120

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b11/00c37120_float_field_getter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0x768) are all within the machine-derived receiver bounds (0x768), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d8d01cec02832f292ee04055b93a3b27a54a2b341b452c61c09c51b57766a8ca`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `33b7a2aa6b777ec101ecc722e1b4cebadf2ebb548804d2a2cf0ae7e5efd5165e`
- Pack digest quoted by the briefing: `d8d01cec02832f292ee04055b93a3b27a54a2b341b452c61c09c51b57766a8ca`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured for 0x00c37120. A differential test must confirm that the shipping build still loads the float from +0x768 and that no runtime patch retargets the address.`, `The domain of the returned float can only be established by observing one call site in the original process with a known receiver, which no recorded run has done.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x00c37120 reachable through a vtable slot anywhere? All 15 xrefs are direct CALLs; no dword equal to 0x00c37120 was searched for in this batch, so the accessor may also be a virtual method whose slot was not found.
- Is the field written by any function in the binary? No writer of +0x768 was located, so the value's provenance is unestablished; it is only read here and, as far as this batch saw, at the other 14 sites.
- No original-process trace has been captured for 0x00c37120. A differential test must confirm that the shipping build still loads the float from +0x768 and that no runtime patch retargets the address.
- The domain of the returned float can only be established by observing one call site in the original process with a known receiver, which no recorded run has done.
- What does the float represent? The sibling at 0x00c370e0 compares a float from a +0x34 sub-object against the constant 0x0146bb74 with COMISS, so the object participates in float comparisons, but nothing observed names the quantity.
- Which class owns the +0x768 float, and is the receiver in every call site the same type? 0x00dc0230 disproves the naive 'the receiver is the caller's this' assumption, and no vtable was located for the receiver in any caller.
- Why does the brief's canonical record list 12 callers while Ghidra reports 15 xref sites, and who owns the 0x0101715e callsite? Ghidra attributes no function to that address.
