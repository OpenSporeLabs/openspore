# Validation 0x00b3d630

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
| GLOBALS | `PASS` | `complete` | the complete 36-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 36-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x18), all of which the record accounts for or the listing is the better witness on; the 36-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=36, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x4, 0x10, 0x18, 0x40), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x4, 0x10, 0x40) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 36-instruction listing lie inside the recovered body span 0x00b3d630..0x00b3d695, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 36-instruction body names 1 indirect transfer(s): 0x00b3d68c dispatches slot 0x70 through the table word in EDX; the machine parse consumed 36 of 36 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5d6f70e1a5c4a1d063fab1536e11f071c228efe436d583fce8d7c3e6d8a0f6e8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5c3e9098f1266dcc94db6814330292faa58dc59cb1c896668e3b908f8c524def`
- Pack digest quoted by the briefing: `5d6f70e1a5c4a1d063fab1536e11f071c228efe436d583fce8d7c3e6d8a0f6e8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture would need a constructed owner with a concrete sub-object instance, which static evidence alone cannot supply.`, `No original-process trace exists for this address, so the value returned by the +0x70 slot, the runtime contents of the sub-object and the real distribution of selector values are all unverified.`, `The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture would need a constructed owner with a concrete sub-object instance, which static evidence alone cannot supply.
- Is the +0x14 float, initialised to 1.0f next to the +0x10 multiplier, a second factor this function does not use? No read of +0x14 was found in this body.
- Is the FLT_MAX comparison in the constructor a saturating guard or a validity flag? The two instructions observed do not distinguish those readings.
- No original-process trace exists for this address, so the value returned by the +0x70 slot, the runtime contents of the sub-object and the real distribution of selector values are all unverified.
- No original-process trace exists, so none of the above can be closed statically and the runtime values of the sub-object are unverified.
- The Cell stage has never been entered in any recorded run, so nothing here is runtime observed.
- What class owns this function? The address has 10 references, all UNCONDITIONAL_CALL, and no DATA reference, so it is not a vtable slot and no owner can be named.
- What do selector values 0 and 1 mean, and why are they the same here? The distinction must live in 0x00b3d9c0 or elsewhere; the enum has no name.
- What is the concrete callee at vtable slot +0x70 of the sub-object, and which vtable is it? No instance of the sub-object was ever observed at a callsite, so no table address could be read.
- What is the separate enum at receiver+0x0c, compared against 2 at 0x00b42630 and against 0 at 0x00b4780b? It is not the selector this body switches on.
- What is the sub-object at receiver+0x40? Only two virtual slots (+0x6c, +0x70) and a cached 3-float point at +0x40 are observed. The +0x6c slot writes a 6-float block that 0x00b3d9c0 averages pairwise and halves, which is consistent with a bounding pair of 3D points, but that is an inference and is not claimed as identity.
