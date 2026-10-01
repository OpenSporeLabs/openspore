# Validation 0x004b09b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b04/004b09b0_intrusive_ref_assign.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 32-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 32-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 1 displacement(s) (0x0), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (32 of 32 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 32-instruction listing lie inside the recovered body span 0x004b09b0..0x004b09ff, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 32-instruction body names 2 indirect transfer(s): 0x004b09dc dispatches slot 0x4 through the table word in EDX; 0x004b09f7 dispatches slot 0x8 through the table word in EDX; the machine parse consumed 32 of 32 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0034d4ded0add813607a7eef36549a4523a97c54848085110f10770de6f7faf1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `54253bbe0d31e21c5df06fa3d1081332815f0c360be4933da4232ca8916293a3`
- Pack digest quoted by the briefing: `0034d4ded0add813607a7eef36549a4523a97c54848085110f10770de6f7faf1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.`, `The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the slot +0x04 and +0x08 callees really AddRef and Release, or two differently-named methods that happen to be called in these directions? Only the direction is proved by the binary; the names come from the SDK's DefaultRefCounted declaration.
- Is the argument always a raw pointer, or is there a second overload taking a pointer-to-pointer that was folded into this one? No such overload was found among the 11 code references.
- No original-process trace exists for this function. The acquire/store/release order is proved statically but its purpose - which re-entrant write-back it defends against - has not been observed.
- The +0x04 and +0x08 callees have never been resolved on a concrete receiver, so the reference-count names remain inferred.
- Which pointee type is the template argument? EditorRigblock is the best-supported candidate from the two cEditor field offsets, but the 9 undisassembled callsites were not checked and could name a different instantiation.
- Why does the erase loop at 0x004b06a0 walk the array assigning each cell its own value? Every iteration takes the early exit, so the loop is a no-op in the observed build. Its source-level intent is not recoverable from the code.
