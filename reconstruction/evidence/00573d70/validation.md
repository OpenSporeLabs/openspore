# Validation 0x00573d70

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/00573d70_set_primary_part.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 148-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 148-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x140), all of which the record accounts for or the listing is the better witness on; the 148-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=148, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x140) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0xe4, 0xf4, 0x140, 0x141), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0xe4, 0xf4, 0x141) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (148 of 148 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 23 conditional branch target(s) in the complete 148-instruction listing lie inside the recovered body span 0x00573d70..0x00573f16, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 148-instruction body names 6 indirect transfer(s): 0x00573e14 dispatches slot 0x30 through the table word in EDX; 0x00573e2f dispatches slot 0xc through the table word in EDX; 0x00573e78 dispatches slot 0x0 through the table word in EDX; 0x00573e88 dispatches slot 0x4 through the table word in EDX; 0x00573eb3 dispatches slot 0x30 through the table word in EDX; 0x00573ebc dispatches slot 0x10 through the table word in EDX; the machine parse consumed 148 of 148 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a357f92a3d4a9f6414791903d552f7386f5ee98c849ef49d24c8bda8386df9c7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3afd43d4da551954baa64abc6e7e75d6263d66d433a9b0dfb817099edaf92d8d`
- Pack digest quoted by the briefing: `a357f92a3d4a9f6414791903d552f7386f5ee98c849ef49d24c8bda8386df9c7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture would need to drive the editor through at least four transitions -- null-to-part, part-to-part, part-to-null and a 0x50a993c part swap -- and record whether the +0x141 handshake fires and in what order.`, `No original-process trace exists. Every flag value, every attribute bit, every list index and both 0x50a993c comparisons in the contract above are static readings of the code path, not observations.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture would need to drive the editor through at least four transitions -- null-to-part, part-to-part, part-to-null and a 0x50a993c part swap -- and record whether the +0x141 handshake fires and in what order.
- Is 0x00572020 really Audio::StopAudio? The SDK lists its address and the argument shape matches, but the first argument passed here is the cEditor pointer rather than an AudioTrack and the callee tail-jumps into a service vtable.
- No original-process trace exists. Every flag value, every attribute bit, every list index and both 0x50a993c comparisons in the contract above are static readings of the code path, not observations.
- Six of the ten reported call sites were not disassembled window-by-window in this batch; their receiver provenances come from the briefing's call graph.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made for this Editor-subsystem function.
- What class implements the part's vtable? Six slot offsets were disassembled (+0x00, +0x04, +0x0c, +0x10, +0x30 and the two marker-service slots) but no table address was resolved, so the interface is unnamed.
- What do the flag bytes at +0x140 and +0x141 mean? Their complete read/write sets are established -- +0x140 is raised in three places, cleared in one and tested in one; +0x141 is set once, cleared once and tested once -- but nothing names either.
- What is editor+0xf4, and is it really unrefcounted? The body clears it with no Release call, which is either intentional or a latent leak; static evidence cannot distinguish those.
- What is the dword at part+0x1c, whose non-zero value is the only thing that lets a re-selection of the same part proceed past the guard at 0x00573dab?
- What is the role of 0x00435ed0? Its four-slot marker shape with ascending tag ids suggests a scope or checkpoint, but no SDK name covers it and the role is not established.
- What is the type id 0x50a993c? It is used consistently as a query key at 0x00573e2a and as a comparison value at 0x00573ebe, and 0x00572770 corroborates the same pair, but no SDK enumerator and no SDK TYPE constant matches it. No name is asserted.
- Why do callers 0x00587480 and 0x00587cef duplicate two of this function's own guards immediately before calling it? Either the guards are load-bearing for a caller-side invariant or the compiler failed to see through them; not resolved.
