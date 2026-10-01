# Validation 0x004adb40

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/004adb40_get_field44.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 9-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 9-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x44), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
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
- Content SHA-256: `6577999590d7c7e646f3dd83338a321fccb679711ed80e621897ef3f12f22b26`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a2f193ebf9a6e7ba39628d60904ca4ec2481e5935e2589902803fe4e31b75b6b`
- Pack digest quoted by the briefing: `6577999590d7c7e646f3dd83338a321fccb679711ed80e621897ef3f12f22b26`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime pass would need to sample the field at a known call site, for example around 0x00586f10, to see the value the original actually compares against.`, `No original-process trace exists, so the claim that the field holds a live float in the shipping build is static only.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime pass would need to sample the field at a known call site, for example around 0x00586f10, to see the value the original actually compares against.
- Is +0x40 / +0x44 / +0x48 a vector, a bound or a centre? Three consecutive floats exist and are read together at 0x0049ad1e-0x0049ad3c, which is suggestive but does not fix the axes or the order.
- Is the PUSH ECX / spill / reload sequence in all ten family members an artefact of a debug build, a /Zi-style build, or a compiler that emits frames for trivially small functions? Nothing in the observed evidence distinguishes these, and it does not affect semantics.
- No original-process trace exists, so the claim that the field holds a live float in the shipping build is static only.
- Seven of the eleven reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.
- What class owns this sub-object? Its proven parent contexts are cEditor+0x98 and rigblock+0x28, and no vtable was located for it.
- What does the float at +0x44 mean? The only site that gives it a role compares it against a computed float, which is consistent with a distance, a scale or a threshold. None of those is asserted.
- Why do +0x48 and +0x4e have setters but no getters in this family? Either they are read by inlined code elsewhere or the getters were never emitted out of line. Not resolved.
- Why does the float run start at +0x38? The float at +0x3c has no accessor in the 0x004adaa0..0x004adc40 range, so either it is accessed elsewhere or the run is not contiguous. Not resolved.
