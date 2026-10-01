# Validation 0x00c0c130

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
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 2-instruction listing names through ECX (0xbb1) are all within the machine-derived receiver bounds (0xbb1), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
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
- Content SHA-256: `a0c5c4514123c5fe68578645fe91e0a3c20091a23c11c7aa63b8006466265bf9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6b8fe04a9c73d5ed53fb220127da34b837d37987336228c7d96e0cf049970baa`
- Pack digest quoted by the briefing: `a0c5c4514123c5fe68578645fe91e0a3c20091a23c11c7aa63b8006466265bf9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime check must confirm the upper bits of EAX are genuinely ignored by all twenty-one callers, which is inferred from the two inspected sites only.`, `A runtime differential test must record writes to receiver + 0xbb1, since no static writer was found and the field's lifecycle is entirely unobserved.`, `No original-process trace has been captured for 0x00c0c130, so the claim that the field is only ever 0 or non-zero is unverified; the value's range is unknown.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime check must confirm the upper bits of EAX are genuinely ignored by all twenty-one callers, which is inferred from the two inspected sites only.
- A runtime differential test must record writes to receiver + 0xbb1, since no static writer was found and the field's lifecycle is entirely unobserved.
- How does the flag at +0xbb0 (read by 0x00c0c120) relate to the one at +0xbb1? They are adjacent and independently read, but no code in this batch writes either, so no relationship is established.
- Is the byte a boolean at all, or a small counter or enum whose only observed values are 0 and non-zero? No writer was found, so the range is unknown.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00c0c130, so the claim that the field is only ever 0 or non-zero is unverified; the value's range is unknown.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- The second inspected caller, at 0x00c03b17, has no owning function in the xref record; its enclosing function was not identified.
- Twelve of the fourteen observed caller functions were not disassembled, so only two call sites have a verified use of the return value.
- What class owns 0x00c0c130? The receiver's offset signature is known but no vtable was located and no ModAPI declaration matches.
- What does the byte at +0xbb1 mean? It gates an early return in one caller and a float comparison in another, so it is some enable or suppression state, but no writer of the field was located and no ModAPI header names it.
