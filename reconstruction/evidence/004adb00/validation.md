# Validation 0x004adb00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_model_min_height_getter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 9-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x40), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 9-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a6d1c5055a608a9b2991cf2f5576ec2e0c28ec0e05557dca406d88c8a756a11b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `67658c5669aa8d85fc28e6a6697f1d1cd68d1f742c472ea316720c2a7c7cb8fc`
- Pack digest quoted by the briefing: `a6d1c5055a608a9b2991cf2f5576ec2e0c28ec0e05557dca406d88c8a756a11b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential test must confirm that the value is returned in ST0 and not in XMM0 in the shipping build. The static evidence for ST0 is strong - FLD with no FXCH and FSTP at every consumer - but it is static.`, `A trace with a concrete receiver is required before the owning class can be named, because no vtable could be located.`, `No original-process trace exists for this function. Static analysis cannot show the live value of the +0x40 float, so the SDK's documented -2.0 default is unverified for the shipping build.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential test must confirm that the value is returned in ST0 and not in XMM0 in the shipping build. The static evidence for ST0 is strong - FLD with no FXCH and FSTP at every consumer - but it is static.
- A trace with a concrete receiver is required before the owning class can be named, because no vtable could be located.
- Is +0x48 really a fourth float, i.e. mMinimumLeglessCreatureHeight? It is inferred from the type boundary at +0x4c and from the SDK ordering; no accessor for it was found in the disassembled range and no read or write of +0x48 was observed.
- No original-process trace exists for this function. Static analysis cannot show the live value of the +0x40 float, so the SDK's documented -2.0 default is unverified for the shipping build.
- What are the nine uninspected call sites doing with the value, and does the one at 0x005b49be belong to a function Ghidra could not attribute?
- What the field at +0x40 is called. mMinHeight is the SDK candidate; the independent binary evidence is only that it is the middle of a three-float run read together.
- Where is the getter for +0x3c (mFeetBounds) and the getter for +0x4e? Only setters were found in 0x004ada80..0x004adbe0, so the accessor family is incomplete and the field survey is bounded by the range that was disassembled.
- Which class owns the receiver. Seven offsets match Spore/Editors/EditorModel.h exactly and no other examined SDK struct does, but no vtable was located and this binary has no RTTI, so the class is recorded as a candidate and not claimed.
- Why do three of the eight resolved callers take the receiver from an outer object's vtable slot +0x28 rather than from a field? That indirection is observed at 0x00485ba5..0x00485bad but the outer object's class is not identified.
