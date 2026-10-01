# Validation 0x005dc310

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/editor_ui_005dc310.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 17-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 11 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (17 of 17 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 17-instruction listing lie inside the recovered body span 0x005dc310..0x005dc334, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 17-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 4 passed, 4 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5969882cb396c3adae2aafd53ff855e315911d5fb2e53757202bf776b8edea3f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5adcae2386c9e0d613f98639a8a9328f61bdb096d649df1bfc7babc04697d6a9`
- Pack digest quoted by the briefing: `5969882cb396c3adae2aafd53ff855e315911d5fb2e53757202bf776b8edea3f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test is required to resolve vtable slots +0x0c, +0x1c and +0xf0 on a live editor element, and to confirm that the +0x14 candidate really does shadow the +0x2c candidate in the shipping build.`, `No original-process trace exists for 0x005dc310; every claim is static and the Cell stage has never been entered in any recorded run.`, `The SDK's UILayoutObjects offsets must be re-derived before the +0x64/+0x68 scan bounds can be attributed to a named member.`, `Whether the +0x2c fallback is ever load-bearing cannot be settled statically; only a run with the main layout empty would show it.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test is required to resolve vtable slots +0x0c, +0x1c and +0xf0 on a live editor element, and to confirm that the +0x14 candidate really does shadow the +0x2c candidate in the shipping build.
- Are the two internal subobjects at this+0x14 and this+0x2c distinct registries or alternate lookup paths?
- Is 0x005dc310 itself an interface method or a vtable entry? No vtable was located for the EditorUI aggregate and no pointer scan for this address was performed.
- Is slot +0xf0 a recursive descent into children, or a lookup in a sibling container? Its (id, 1) shape is consistent with both.
- Is the flag argument ever 0 for this function? Both call sites here hard-code 1, and all 25 recorded callers route through those two sites, so the non-recursive path may be dead in this build. Not proven, because 0x008105b0 has other callers that were not enumerated.
- No original-process trace exists for 0x005dc310; every claim is static and the Cell stage has never been entered in any recorded run.
- The SDK's UILayoutObjects offsets must be re-derived before the +0x64/+0x68 scan bounds can be attributed to a named member.
- The element array scanned by 0x00810200 lives at +0x64..+0x68 of the layout-objects target, but the SDK declares UILayoutObjects::mRootComponents at +0x5c. Either the SDK offsets for that class are wrong, or the scanned array is a different member. Not reconciled.
- The other 14 of the 25 callers were not inspected, so the argument distribution across the fan-in is not established.
- What are the control ids 0x630c829, 0x578ec50, 0xf006efa5, 0xb006ef6e and 0x1140129d? None is named in the SDK. 0x578EC50 appears as a comment on an unrelated EditorUI field, which is suggestive and unproven.
- What concrete type, if any, owns the opaque void* lookup result?
- What do vtable slots +0x0c, +0x1c and +0xf0 do on a UTFWin element? The 0xEEEE8218 argument makes +0x0c a cast/filter, but neither the other two is named. The id compared at +0x1c is probably a control id, but that is an inference from the argument the callers pass.
- Whether the +0x2c fallback is ever load-bearing cannot be settled statically; only a run with the main layout empty would show it.
