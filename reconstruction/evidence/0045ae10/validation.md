# Validation 0x0045ae10

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/registry_0045ae10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 3 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 17-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `eb0a845a31fed89921d3b0005cd60c6b081ed2281962c36fa09e3a909c9f1ea9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d312147d2943009ff44d45c60dc356f94677573ffd6fad7fbd8d2daa828ef4d2`
- Pack digest quoted by the briefing: `eb0a845a31fed89921d3b0005cd60c6b081ed2281962c36fa09e3a909c9f1ea9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test is required to (a) observe the real value of 0x015d0c14 and of 0x015d22f0/f4/f8, (b) resolve the four virtual slots, and (c) determine whether the fourth argument read by 0x0045ac20 is genuinely uninitialised in the shipping build.`, `No original-process trace exists for 0x0045ae10; every claim is static. The Cell stage has never been entered in any recorded run.`, `The identity of the 0x14-byte POD cannot be settled statically at all: every field it copies is zero in the image.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test is required to (a) observe the real value of 0x015d0c14 and of 0x015d22f0/f4/f8, (b) resolve the four virtual slots, and (c) determine whether the fourth argument read by 0x0045ac20 is genuinely uninitialised in the shipping build.
- Is 0x0045ae10 an inline expansion of a one-line source function, or a real out-of-line wrapper? Its 42-byte body and 13-call fan-in are consistent with either.
- No original-process trace exists for 0x0045ae10; every claim is static. The Cell stage has never been entered in any recorded run.
- The 13 callers are only 2 inspected. The other 11 pass their key and mode through registers whose provenance was not traced, so the argument distribution across the fan-in is not established.
- The identity of the 0x14-byte POD cannot be settled statically at all: every field it copies is zero in the image.
- What are the four virtual slots 0x0045ac20 uses (+0x2c on a manager, +0x18 and +0x08 on the created object, +0x00/+0x04 on the map-resident object)? Slot offsets are observed; names and owning interfaces are not.
- What do 0x015d22f0/f4/f8 hold at runtime, and what does 0x0041cb40(&0x015d2638) do with them?
- What is the 0x14-byte POD built by 0x00434040? Its bytes are known; its type, alignment intent and units are not. The 1.0f default suggests a scale but proves nothing.
- What is the type behind 0x015d0c14? The file image holds zero, no vtable was located, and the SDK has no matching global manager for this access pattern.
- Why does this wrapper pass three arguments to a four-argument callee? Either 0x0045ac20's fourth parameter is genuinely optional in practice, or the observed build reads an uninitialised slot. Static evidence cannot decide between those.
