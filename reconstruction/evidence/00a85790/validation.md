# Validation 0x00a85790

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00a85790/sw2_00a85790.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 64-instruction listing name the same 1 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00a85790..0x00a85839 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00a8581f; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00a85790; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 64-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 64-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x10, 0x14), all of which the record accounts for or the listing is the better witness on; the 64-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=64, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x10, 0x14) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0xc, 0x10, 0x14, 0x68), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0xc, 0x68) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (64 of 64 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 9 conditional branch target(s) in the complete 64-instruction listing lie inside the recovered body span 0x00a85790..0x00a85839, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 64-instruction body names 4 indirect transfer(s): 0x00a857e6 dispatches slot 0x18 through the table word in EDX; 0x00a85815 dispatches slot 0x1c through the table word in EDX; 0x00a8581d is UNRESOLVED; 0x00a8582f dispatches slot 0x14 through the table word in EDX; the machine parse consumed 64 of 64 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4, so the dispatch is visible in the machine listing but is not proven: 1 of the 4 indirect transfer(s) classify as UNRESOLVED (0x00a8581d), so the dispatch's identity is not established: EDX is defined by a preceding CALL, so it holds that callee's return value before 0x00a8581d |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 64-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5395c2ce654727dd178e8c4cb6a48244933caa2e7299b2d79c6239539ffe4bc7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e9a0dd5f9a9c56784eb2c459399a24473321f22d32194ee5868939e9a646d04f`
- Pack digest quoted by the briefing: `5395c2ce654727dd178e8c4cb6a48244933caa2e7299b2d79c6239539ffe4bc7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does the pending-identifier half of the function ever depend on the notification half? The listing fixes that the notification block is skipped to the shared continuation at 0x00a8581f and that the two halves share no memory, but nothing says whether the callees reached from the notification block are the ones that would have to write receiver+0x68 for the second half to fire. The model test shows the halves are independent as far as this body's own writes go, which is a weaker statement.
- Is the 0x6c receiver bound the true object size? It is the minimum this body requires (its own dword store at 0x00a85831 ends at +0x6b). Nothing in this pack establishes an upper bound, and the constructor that would (0x00a853b0, cited by the sibling package for the same vtable) is not part of this target's evidence.
- What are the three dispatches for? The two-level shape and the three displacements are fixed, but whether they are virtual overrides of a known interface or plain callback words stored in the listener object is not settled by any evidence in this pack, and the two readings execute identical instructions. The same applies to the 0x14-dispatched word: it is called with a pushed 4-byte argument and its return value is discarded.
- What calls this body? The xref export records no incoming call edge; the single xref is the data reference from the table word at 0x01458030. So the callers are unknown and this package claims nothing about them.
- What is 0x00a85460? There is no evidence pack for it in this repository. Its callsite fixes a __thiscall shape with the receiver and no stack argument, and the fact that this body discards its EAX, and nothing else. Its own return type in particular is unclaimed: this package declares it void because the callsite gives no evidence of a return value, which is a statement about the callsite and not about the callee.
- What is the 16-bit value at +0xa8 of the same object, and what is the +0x28 receiver interior pointer for? The body zero-extends the halfword and passes it as the first argument with either the receiver's +0x28 address or a null word as the second, and the listing does not say what the callee does with either.
- What is the C++ class? The vtable export associates 0x00a85790 with vtable 0x01458024 (this function is that table's fourth word, i.e. slot 3), but the binary has no MSVC RTTI, the SDK association fields are empty, and the table's other entries are not enough to derive a name. The index's own labels for the record are cluster 'editor-core' and subsystem 'Editor'; those are the index's labels, not a name this package derived.
- What is the flag word? It is read at +0x08 of the object the receiver's +0x0c word addresses, and four of its bits (0, 3, 5, 6) are tested with three different gates. Nothing in this pack names the type it belongs to or says what any of the four bits means beyond 'this bit opens this call'.
