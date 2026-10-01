# Validation 0x0043eed0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/0043eed0_editor_part_blend_getter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 9-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x1d4), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `de6eab32bf5408adb66d4ac46b4cfedba5ad29217da782455e5c1ffbb2cf992c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a71baa8ef686faae38022c637ee5bfaaa9c34b061854fbf6331e1f748b5407af`
- Pack digest quoted by the briefing: `de6eab32bf5408adb66d4ac46b4cfedba5ad29217da782455e5c1ffbb2cf992c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured. The value actually stored at +0x1D4 in the shipping build, and its range, are runtime facts that static analysis cannot supply.`, `Whether the getter is ever reached through a pointer stored in a table, which would explain its out-of-line form, needs a reference scan beyond the 29 direct calls.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the +0x218/+0x21C clamp range per-object or per-class? It is read from the receiver, so per-object, but what sets it was not established.
- Is the value guaranteed to lie in [0,1]? The caller clamps it into [+0x218, +0x21C] before normalising, which suggests it may not, but nothing in the getter or its 29 callers establishes a range.
- No original-process trace has been captured. The value actually stored at +0x1D4 in the shipping build, and its range, are runtime facts that static analysis cannot supply.
- The 16 code references that were not disassembled could include a caller that treats the value as something other than a weight.
- What does the float at +0x1D4 represent? The 'normalised blend weight' reading comes from FUN_0043ecb0's arithmetic and is labelled INFERRED; the SDK does not name the field and no string or property reference ties it to a concept.
- Whether the getter is ever reached through a pointer stored in a table, which would explain its out-of-line form, needs a reference scan beyond the 29 direct calls.
- Why is the getter out of line at all? It is nine instructions and would inline; a shipped build that kept it out of line may indicate it is a virtual override, an address taken somewhere, or simply an unoptimised translation unit. The 0 data references argue against the vtable case but do not exclude an address being taken.
