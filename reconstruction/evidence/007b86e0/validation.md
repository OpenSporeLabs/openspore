# Validation 0x007b86e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/007b86e0_object_release.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 12-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 12-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x8), all of which the record accounts for or the listing is the better witness on; the 12-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=12, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x8) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x8), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 12-instruction listing lie inside the recovered body span 0x007b86e0..0x007b86ff, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names 1 indirect transfer(s): 0x007b86fb dispatches slot 0x0 through the table word in EAX; the machine parse consumed 12 of 12 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 341 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `545a4d10d907946f14c6e267eee3397c222b3a78c14f7265361c23bc1c64064d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8fcfc97ca3970d7e86d6b0b644cdffd619788221837398cc4a94482949fb9bb1`
- Pack digest quoted by the briefing: `545a4d10d907946f14c6e267eee3397c222b3a78c14f7265361c23bc1c64064d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured for 0x007b86e0. A differential run must confirm that the decrement, the restore-to-1 and the destructor call happen in that order on a real receiver, and that no runtime patch retargets the address.`, `The 417 vtable slots need at least one resolved concrete receiver before any owning class can be named.`, `The zero arm has never been observed executing. Whether the delete-on-zero path is reachable in the shipping build, and what the caller does with the 0 return, needs a trace.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the SDK correspondence Spore::Object::Release an identity or only a slot-shape match? The declared order {AddRef, Release, ~Object, Cast} matches one sampled table exactly and 0x00e5cac0 at slot +0x0C does return its receiver unchanged as Cast would, but the SDK declares Object with no data members while the observed count lives at +0x08, so the two layouts are not the same declaration.
- No differential trace exists for any of the 63 code references, so it is unproven that every receiver reaching this body has the expected +0x04 sub-object and is not a null or a dangling pointer.
- No original-process trace has been captured for 0x007b86e0. A differential run must confirm that the decrement, the restore-to-1 and the destructor call happen in that order on a real receiver, and that no runtime patch retargets the address.
- The 417 vtable slots need at least one resolved concrete receiver before any owning class can be named.
- The zero arm has never been observed executing. Whether the delete-on-zero path is reachable in the shipping build, and what the caller does with the 0 return, needs a trace.
- What happens to the 8 data references whose slot-offset scan did not report +0x04? They were not individually inspected.
- What is the second base at +0x04? Its vtable is 0x013ef094 for the one class inspected and its slot +0x00 is a deleting destructor; the SDK's IVirtual, documented as an interface whose only virtual is a destructor, fits, but that is a candidate and no other slot of that base was ever reached.
- Which class, or which set of classes, owns the 417 slots that point here? No single owning type can be named, and this binary has no RTTI to recover it from.
- Why is the count restored to 1 rather than left at 0? The re-entrancy explanation fits the instruction order but no runtime observation confirms which re-entrant path actually occurs, if any.
