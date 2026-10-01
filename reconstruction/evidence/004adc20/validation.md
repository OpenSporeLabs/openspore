# Validation 0x004adc20

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/004adc20_set_flag4f.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 10-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 10-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x4f), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (10 of 10 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 10-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 10-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `43c31d026ff92d7fa374cd6e167ba27f54844916b8b11810ab945093465c49d2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e5995d7e1b734ed6321c8d35ecf959171729602b2d044f4dc82f9a563753eba7`
- Pack digest quoted by the briefing: `43c31d026ff92d7fa374cd6e167ba27f54844916b8b11810ab945093465c49d2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime pass would need to set the flag through a known call site and observe the paired 0x004adc40 read, to confirm the pairing and to see which values are stored.`, `No original-process trace exists, so the claim that this flag is written and later read with a meaning is static only.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime pass would need to set the flag through a known call site and observe the paired 0x004adc40 read, to confirm the pairing and to see which values are stored.
- Do all seventeen callers pass the same concrete receiver type? Their receiver provenances were not disassembled window-by-window in this batch, so only the fan-in of 17 is independently confirmed.
- Is the byte a bool, a small enum or a bitfield-style flag? Callers only ever store whole bytes and the paired getter is only ever tested for zero, so the evidence cannot separate these.
- Is the redundant spill in all ten family members an artefact of a specific build configuration? It affects no semantics and is not worth further investigation, but it is unexplained.
- No original-process trace exists, so the claim that this flag is written and later read with a meaning is static only.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.
- What class owns this sub-object? Two proven provenances (cEditor+0x98 through the +0x44 getter's callers, and rigblock+0x28 through 0x00438700) do not converge on a named type, and no vtable was located.
- What does the byte at +0x4f mean, and what are the other three flags in the block for? Seventeen call sites were found and none of them was interpreted, so the value's role is unestablished.
- Why does +0x4e have a setter but no getter in this family, and why does +0x48 have a setter but no float getter? Either they are read by inlined code elsewhere or the getters were never emitted out of line. Not resolved.
