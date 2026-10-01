# Validation 0x00a85070

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00a85070/sw1_00a85070.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 13-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00a85070; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 13-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x10), all of which the record accounts for or the listing is the better witness on; the 13-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=13, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x10), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 13-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names 2 indirect transfer(s): 0x00a8507c dispatches slot 0x20 through the table word in EAX; 0x00a85085 dispatches slot 0x60 through the table word in EDX; the machine parse consumed 13 of 13 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `1d2cbd679e0c193366b63cec796fe74e13377f59e0706da69066d11ec17f531f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `ae8bf09bd9b85df018387e5d67767bdaf5ac06d9a7dc7caa70ff8f77a5d43788`
- Pack digest quoted by the briefing: `1d2cbd679e0c193366b63cec796fe74e13377f59e0706da69066d11ec17f531f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the real callee at the +0x20 fetch preserve EAX? The body depends on it -- 0x00a8507e and 0x00a85080 both read the post-call EAX rather than reloading [ECX] -- and nothing in this body can show it. The model reproduces the machine either way and the model test drives both behaviours; what is missing is evidence about the actual callee, which lives outside this body.
- Is the returned/stored word a pointer? Two sibling entries of the same vtable treat the receiver's +0x10 as a pointer to a polymorphic object, which makes it very likely -- but this body never reads that word, so its type is not fixed by this listing and the model leaves the slot opaque.
- Is the word at the dispatch object's +0x20 a vtable slot of the owner (making site 1 an ordinary virtual call on the owner) or a callback word stored in a callback-holder object and invoked with the owner as its single argument? Both readings execute the identical three instructions at 0x00a85079, 0x00a8507c and the surrounding frame, so the listing cannot separate them and the model asserts neither.
- No decompilation exists for this VA in this session (three decompiler calls all failed), so no decompiler disagreement could be recorded and no decompiler observation backs the reconstruction.
- The receiver's layout above the single +0x10 store is taken from the constructor 0x00a853b0, not from this body. On its own this body bounds the object at 0x14 only. Any claim about a member beyond +0x10 rests on that second listing.
- Two of the vtable's later entries (0x0082e650, x4, and 0x0051e340 / 0x0051e380) were not disassembled, so whether the table is one homogeneous interface list or a mix of the class's own and inherited methods is not established. It does not affect this body, which is slot 0.
- What are the C++ types, and what is the class? The vtable 0x01458024, its 15 entries and the constructor's member set fix the receiver's SHAPE but not its name, and no SDK association was corroborated for this VA. In particular 0x004ae250, which shares the table, is a 7-instruction no-op, so the name another package attached to it is not supported by its bytes.
- What is the second stack word? It exists only because the terminator is RET 0xc. No instruction reads entry_ESP + 0x8, there is no call site to inspect (the body has no direct callers), and no record constrains it, so its type and its value are unconstrained here.
