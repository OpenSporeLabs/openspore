# Validation 0x004ad450

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/004ad450_related_pointer_getter.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x30), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 11-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cb5caafdc8e52e2c1c8f82c3eccf56cdf7ee54208caaac5877a333400d3d1ed2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f9eb350a517133cef87d38bd829fd2595f1bf827b21c7d175f8b6cc8c24abcc7`
- Pack digest quoted by the briefing: `cb5caafdc8e52e2c1c8f82c3eccf56cdf7ee54208caaac5877a333400d3d1ed2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured. Whether the +0x30 pointer is ever null at a callsite is a runtime fact; statically the getter propagates whatever is there.`, `The 26 uninspected callsites need at least a sample disassembled before the uniform 'result is the next receiver' reading can be generalised.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the 26 uninspected callsites all shaped like the three inspected ones, i.e. moving the result into ECX? If some test the result, the null contract would differ per caller.
- No original-process trace has been captured. Whether the +0x30 pointer is ever null at a callsite is a runtime fact; statically the getter propagates whatever is there.
- The 26 uninspected callsites need at least a sample disassembled before the uniform 'result is the next receiver' reading can be generalised.
- The receiver's +0x00 vtable is dispatched by a sibling with the address of the global DAT_013ec468 as its argument. What that global holds, and what those two slots do, was not established.
- What class is the receiver? Nothing in the binary names it, and this binary has no RTTI, so the vtable at +0x00 that 0x004ad280 dispatches could not be tied to a declaration.
- What do 0x004b9440 and 0x004b9420 do? 0x004b9440's body writes its stack argument into [*(this+0xC)+0x1C], which is enough to prove the returned pointer has a +0xC sub-object and nothing more.
- What is the relationship between the receiver and the object at +0x30 - owner, child, observer? 0x004b9570 takes both, which shows the receiver matters to the callee, but the direction was not established.
- Why do five sites in FUN_005bb5a0 and four in FUN_005bccc0 call this getter? A one-word accessor with that much fan-in is either a hot shared sub-object or a vtable-like dispatch that Ghidra has not recognised. Neither was investigated.
