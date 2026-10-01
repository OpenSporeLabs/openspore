# Validation 0x00c8b6b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg11_sim_core/sim_core.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
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
- Content SHA-256: `cc341d836abd91570837a13e0a09ad8dca26aa14278e54c75668a09bea983f72`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `48ee74cbc3a66e83fc66d7f9f1b8de26f45c81575bd065fb7b72336fa2a72d77`
- Pack digest quoted by the briefing: `cc341d836abd91570837a13e0a09ad8dca26aa14278e54c75668a09bea983f72`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-star-predicate-function-table`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No pointer formal exists at this VA, so null-pointer behavior is outside the recovered ABI; only zero and arbitrary raw enum words can be tested.
- The exact producer and consumer of the 0x014739b0 function-pointer slot are unresolved because the target has no direct call xrefs.
- The relationship between this constant body and the intended IsNotStarOrBinaryStar name is unresolved.
- Whether the source-level return was semantically bool while the executable intentionally or incidentally returned a nonzero noncanonical EAX word is unresolved.
- Why the live function is stored in a function-pointer table at 0x014739b0 despite having no direct callers is unresolved.
- function-table producer and consumer
- gate-star-predicate-function-table
- noncanonical true word intent
- relationship to imported symbol name
