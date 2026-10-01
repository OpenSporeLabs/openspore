# Validation 0x00b8d970

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b09/b09_abi.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 4-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 4-instruction listing names through ECX (0x2c) are all within the machine-derived receiver bounds (0x2c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (4 of 4 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 4-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 4-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cfc73a529f07e8ffef59993f029bc4a3dd21787e96a4362b041b9eed856385f1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `916aa9fe9ed14a08e31e97a174131d5da9a47b00d133e7528b4be8e977ee7e66`
- Pack digest quoted by the briefing: `cfc73a529f07e8ffef59993f029bc4a3dd21787e96a4362b041b9eed856385f1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture is cheap but needs a receiver whose flag word is set by real game code, which static evidence does not supply.`, `No original-process trace exists for this address, so the runtime value of the flag word at +0x2c is unverified.`, `The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture is cheap but needs a receiver whose flag word is set by real game code, which static evidence does not supply.
- No original-process trace exists for this address, so the runtime value of the flag word at +0x2c is unverified.
- No original-process trace exists, so the runtime flag values are unverified.
- The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.
- What are the three unreported callsites at 0x00c56f3f, 0x00c56f95 and 0x01025ad7, which lie outside any Ghidra function body?
- What class owns this function? 31 live references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.
- What does flag bit 8 mean? That it is a flag is established; its game meaning is not, and no SDK field, global name or string ties it to a concept.
- What is 0x00b8d9b0, the chain of five calls that runs only when both bit 8 and bit 0x800 are clear? It was not resolved in this batch.
- What is the state enum at +0x28, and what are all its values beyond the observed 0, 1 and 2-or-greater?
- Which other bits of the word at +0x2c are in use? Only bit 8 (here) and bit 11 (0x00b8da12) were observed; the other 30 bits are unaccounted for.
- Who writes the flag word at +0x2c? No writer was found in this batch.
