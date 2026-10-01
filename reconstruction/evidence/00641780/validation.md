# Validation 0x00641780

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00641780/swarm_w1_00641780.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 19-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00641780; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 19-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 19-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 19-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=19, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (19 of 19 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 19-instruction listing lie inside the recovered body span 0x00641780..0x006417a5, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 19-instruction body names 2 indirect transfer(s): 0x00641788 dispatches slot 0x10 through the table word in EAX; 0x00641795 dispatches slot 0xc through the table word in EAX; the machine parse consumed 19 of 19 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 9 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a4f2c67221b88fa42108d63a543eb72bb18a4e8e3dab78a9d7230cda2e57109a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1f5aec6c0f1e939ff877381d863e132508281c2ac370d6eb7be8c9aebab26b6b`
- Pack digest quoted by the briefing: `a4f2c67221b88fa42108d63a543eb72bb18a4e8e3dab78a9d7230cda2e57109a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace records the dispatch word's value at 0x00641783 and again at 0x0064178e, the two target addresses loaded at 0x00641785 and 0x00641790, and the full 32-bit EAX each callee returns.`, `An object whose dispatch word points at one of the six tables listed above is constructed and FUN_00641780 is entered.`, `The trace is repeated with the +0x1c sub-object null and non-null, since both candidate accessors 0x00641810 and 0x00641820 return zero when it is null and tail-transfer when it is not.`, `The trace shows whether the dispatch word ever differs between the two reads; if it never does, the second load at 0x0064178e is confirmed redundant on every observed path and this package's case 7 remains a synthetic refutation only.`, `not_required_for_the_structural_claims_but_unavailable`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace records the dispatch word's value at 0x00641783 and again at 0x0064178e, the two target addresses loaded at 0x00641785 and 0x00641790, and the full 32-bit EAX each callee returns.
- An object whose dispatch word points at one of the six tables listed above is constructed and FUN_00641780 is entered.
- Does Ghidra have an SDK name for this member that the live cSPAssetDataOTDB this_type set does not list? The set has ten members and this VA is not among them, so the export name stays the canonical VA-embedding form. A name from the ModAPI headers or a vtable-detector pass would settle it; neither was available to this worker.
- Does any real callee in this image ever change the receiver's dispatch word? 0x0064178e proves the model must re-read it; whether the re-read ever matters at run time needs a trace. Static analysis of the candidate callees found no store to a dispatch word, but that is an absence of evidence.
- The C type of the value EAX carries, which no machine record for this VA states and which nothing in this image can settle. The reconstruction declares `Word` (this package's alias for std::uint32_t) because the body itself produces a full 32-bit word and nothing narrows it: 0x0064179b is `MOV EAX,0x1` (bytes B8 01 00 00 00) and 0x006417a2 is `XOR EAX,EAX`, and the two callees' results are consumed whole by `TEST EAX,EAX` and then discarded. The machine side of the record is a register-CLASS classification rather than a type: abi_derived.value.return is {register EAX, register_class integral, type null, void_possible false} and the pack's return_semantics field is null, so the phrase the ABI layer renders is `integral_in_EAX` (the same vocabulary renders `unclassified_in_EAX` for a register it cannot classify, which is not what this record carries). That phrase is recorded in observed_original_abi.return_semantics and is NOT declared as a type anywhere in the source, because it is a description of a register's content in one layer's vocabulary and a typedef named after it would be an artefact rather than a claim. Nothing here can decide the C type: the body has no direct callee, this VA has no outgoing xref row at all, and the two dispatched targets depend on the table the object carries at run time. What IS settled is the WIDTH -- WIDTH_4_IN_EAX over the complete 19-instruction listing -- and `Word` is 4 bytes, so the declaration is as wide as the machine proves the return to be. Whether the original's real signature said `int`, `unsigned int`, `BOOL` or something else remains unknown, and this package does not claim it.
- The trace is repeated with the +0x1c sub-object null and non-null, since both candidate accessors 0x00641810 and 0x00641820 return zero when it is null and tail-transfer when it is not.
- The trace shows whether the dispatch word ever differs between the two reads; if it never does, the second load at 0x0064178e is confirmed redundant on every observed path and this package's case 7 remains a synthetic refutation only.
- What are the class identity and full layout of the receiver? Only the dispatch word at +0x00 is reachable from this body. The candidate callees 0x00641810, 0x00641820 and 0x00641850 all open with MOV ECX,[ECX + 0x1c] and tail-transfer to a different function, so a +0x1c sub-object almost certainly exists -- but that is read off the CALLEES' bodies, not this one, and it is deliberately absent from the model.
- What do the two callees return, a small number or an address? The body tests all 32 bits with TEST EAX,EAX and then produces a fresh 1, so the representation is irrelevant to this reconstruction; the slot return type is modelled as uint32_t for that reason and the question is left to whoever reconstructs the callees.
- Which concrete functions are reached at table slots 3 and 4? This body names no callee, so the answer is a property of the dispatch word the object carries at run time. It is additionally unsettled by construction: the six tables that install this body do not agree on their slot 3 (0x00641810 in three of them, 0x00dd0b30 in two, 0x00ecc530 in one), so a single answer cannot be right for all six.
- not_required_for_the_structural_claims_but_unavailable
