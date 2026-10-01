# Validation 0x005766e0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b02/b5766e0_intrusive_ptr_assign.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 27-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 27-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 27-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=27, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (27 of 27 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 27-instruction listing lie inside the recovered body span 0x005766e0..0x00576712, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 27-instruction body names 2 indirect transfer(s): 0x005766fc dispatches slot 0x4 through the table word in EDX; 0x0057670b dispatches slot 0x8 through the table word in EDX; the machine parse consumed 27 of 27 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6b00b6875cc6e32505f1d8183a5147118484e9b4f951599079bb76f9da503f5d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `51104e87b5259bc9ce974426b960165477ea1b93444e9f3d202caed70b713b40`
- Pack digest quoted by the briefing: `6b00b6875cc6e32505f1d8183a5147118484e9b4f951599079bb76f9da503f5d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace is required to confirm that the concrete AddRef and Release at slots +0x04 and +0x08 of the actual pointee classes are the 0x00432a50 / 0x00404f90 pair, since the vtable was not located statically.`, `A runtime trace is required to observe whether a self-assignment ever occurs in practice, which is the only way to confirm the guard is exercised rather than dead.`, `No original-process trace has ever been captured for 0x005766e0; every claim here is static. The original Cell stage has never been entered in any recorded run.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace is required to confirm that the concrete AddRef and Release at slots +0x04 and +0x08 of the actual pointee classes are the 0x00432a50 / 0x00404f90 pair, since the vtable was not located statically.
- A runtime trace is required to observe whether a self-assignment ever occurs in practice, which is the only way to confirm the guard is exercised rather than dead.
- Are the two null checks on the pointee redundant with the callee's own behaviour? Not determinable without a runtime trace of a null pointee.
- Do the AddRef and Release at slots +0x04 and +0x08 return a count that any caller inspects? Every inspected callsite discards the result, and the other eight were not disassembled.
- No original-process trace has ever been captured for 0x005766e0; every claim here is static. The original Cell stage has never been entered in any recorded run.
- Seven of the thirteen callsites were not disassembled, so their receiver/argument shapes are inferred from the six that were.
- What is the C++ name and exact signature? The pointer-to-pointer argument does not match the usual intrusive_ptr assignment parameter, and the address has no data reference from which to recover the instantiation.
- What is the class of the pointee? The vtable is read but never identified; the three-slot refcounted shape matches App::IMessageRC and the 0x013eb844 family, but that is a shape match and not an identity.
