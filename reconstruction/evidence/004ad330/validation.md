# Validation 0x004ad330

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b02/b4ad330_teardown_004ad330.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 21-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 21-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x30), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (21 of 21 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 21-instruction listing lie inside the recovered body span 0x004ad330..0x004ad368, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 21-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `43e63eefb29947cc370cc21b3824e6b66385e6a0e24312330d80191c70a18b5e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `0ac2d147bf41b04d4fcbfbc631ca41d4f5626a3ec40e130f2d2b375e2c1d7292`
- Pack digest quoted by the briefing: `43e63eefb29947cc370cc21b3824e6b66385e6a0e24312330d80191c70a18b5e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to determine whether the double base pass in OnExit is benign in the shipping build.`, `A runtime trace is required to observe the two virtual calls in 0x004ad280 and thereby resolve the receiver's class.`, `No original-process trace has ever been captured for 0x004ad330; every claim here is static. The original Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to determine whether the double base pass in OnExit is benign in the shipping build.
- A runtime trace is required to observe the two virtual calls in 0x004ad280 and thereby resolve the receiver's class.
- Is the double 0x004ad280 pass in Editors::cEditor::OnExit intentional, or does it rely on the base pass being tolerant of an already-emptied vector?
- Nine of the thirteen callsites were not disassembled, so their null-guard and refcount context is unverified.
- No original-process trace has ever been captured for 0x004ad330; every claim here is static. The original Cell stage has never been entered in any recorded run.
- What are the two virtual callees at receiver vtable slots +0x00 and +0x08 that 0x004ad280 invokes with the float-table address?
- What class is the member at +0x30?
- What class owns this method? There is no data reference at this address, so no vtable can be derived, and the binary has no MSVC RTTI.
- What does 0x004b98b0 and 0x004b97e0 do to the sub-object at member+0x18?
- What is the pointer vector at receiver+0x18, and what does 0x00451400 do to each element?
