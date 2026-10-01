# Validation 0x005ba0d0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-005ba0d0/sw1_005ba0d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 12-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x005ba0d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 12-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 12-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x18), all of which the record accounts for or the listing is the better witness on; the 12-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=12, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x18), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 12-instruction listing lie inside the recovered body span 0x005ba0d0..0x005ba0ef, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names 1 indirect transfer(s): 0x005ba0eb dispatches slot 0x0 through the table word in EAX; the machine parse consumed 12 of 12 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 15 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `fdf9b84c74605d7ae30f4908914f17794e7bf8740621397aafbeb28b30823ac0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `55d10ba6447e4bc8248a18f9173117819faf818d19b7c4f1eb5d2cb0a3d13914`
- Pack digest quoted by the briefing: `fdf9b84c74605d7ae30f4908914f17794e7bf8740621397aafbeb28b30823ac0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Duplicate ownership: none at the time of writing. reconstruction/metadata had no 005ba0d0.json before this one and the evidence pack's existing_reconstruction lists no files, handoffs or metadata, so this package is the only claimant of this VA as of 2026-09-28. The integrator's call, not this worker's: whether the two are in fact the same function and should be reconciled.
- The class of the receiver and the class of the object at receiver+0x14 are not established. SporeApp.exe carries no MSVC RTTI, the body itself has no SDK-derived name (ghidra_function.sdk_name and sdk_type are both null), and nothing in the fifteen table regions identifies its owner. The extern is therefore named after the call site, and no member of the receiver is named for a role.
- The derived receiver record enumerates offsets [24] only and does not see 0x14. This package follows the listing and treats the record as incomplete, on the record's own abstention ('flow_not_modelled'). If the record is ever corrected, its 0x14 entry would be new information about a record this package already treats as authoritative for register and written_through.
- What the word at +0x18 is FOR is not established. The listing says only that it is a 32-bit word that is decremented, restored to 1 when the decrement reaches zero, and zeroed by a constructor. A countdown, a cooldown, a latch, a reference count and a queue depth all fit those twelve instructions equally, and the package names it for its offset only.
- Whether EAX is an intended result. The body returns a different word on each path and the two disagree about the field's own value, which is exactly what a deliberate result looks like -- but no caller in this image consumes it, because the only non-data references are three thunks. It is equally consistent with a dead register that the compiler happened not to overwrite.
- Whether the indirect callee really owns the four bytes it is handed is INFERRED, not confirmed. The inference is strong (no POP and no ADD ESP anywhere in the body, so the shared RET at 0x005ba0ef would otherwise pop the argument as a return address), but the callee is reached through a vtable word and its own bytes are outside this package.
- Whether the transient 0 left at +0x18 between 0x005ba0d9 and 0x005ba0de has any external observer is unknown and probably unanswerable: the window contains no call, no branch target and no exit. The package records the two stores in a model-side write log so its own test can assert the count and the order, and states plainly in the test header that the log is instrumentation and not a machine global.
- Why the same function sits at +0x04 of two of the fifteen regions and at +0x14 of the other thirteen is not settled. The verified case (0x013f76c4, where +0x08 holds the -0x14 thunk and +0x14 holds the raw address) is the multiple-inheritance signature, but the two +0x04 regions hold a constructor in the slot before, which does not fit the same story and is not explained here.
