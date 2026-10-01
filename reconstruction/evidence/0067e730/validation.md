# Validation 0x0067e730

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/cheat-func44h-0067e730/cheat_dispatch_func44h_0067e730.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 24-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x0067e730; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 24-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 24-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4c, 0x50), all of which the record accounts for or the listing is the better witness on; the 24-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=24, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4c, 0x50) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x50, 0x60), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x60) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x4c), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (24 of 24 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 24-instruction listing lie inside the recovered body span 0x0067e730..0x0067e760, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 24-instruction body names 1 indirect transfer(s): 0x0067e74c dispatches slot 0x1c through the table word in EAX; the machine parse consumed 24 of 24 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cbbf502298789e89dce51bbadf02210388735877617df66d2a892cb9a7b31b75`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `058f1cf515ec01897e39dae4e474682acc734663d7f042f06e0f2465461c61bb`
- Pack digest quoted by the briefing: `cbbf502298789e89dce51bbadf02210388735877617df66d2a892cb9a7b31b75`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c, or the body exits at 0x0067e73a without making any call.`, `A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c.`, `The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning, and before a stub with the right stack discipline can be confirmed.`, `The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning.`, `The function is reachable only through vtable 0x01401b74 slot 17, so a differential run must construct that exact table and dispatch the slot.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c, or the body exits at 0x0067e73a without making any call.
- A live cCheatManager with a populated observer chain is required to observe the dispatch at all; the chain head at +0x50 must differ from the embedded terminator at +0x4c.
- Does the dispatch observe the chain as it is being mutated, since a successor is fetched after each call?
- Does the manager's own word at +0x4c ever hold a value another function uses, given that this body only address-takes it?
- Is the callee-cleaned eight-byte stack of the +0x1c entry confirmed anywhere, or is it only forced by the requirement that ESP stay constant across iterations?
- The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning, and before a stub with the right stack discipline can be confirmed.
- The concrete receiver type must be identified before the +0x1c entry can be attributed a meaning.
- The function is reachable only through vtable 0x01401b74 slot 17, so a differential run must construct that exact table and dispatch the slot.
- What does the +0x64 byte mean, and is the sibling pair an enable/disable or a register/unregister traversal?
- What does the +0x64 byte that the sibling gates on mean, and is the pair an enable/disable or a register/unregister traversal?
- What is 0x00921580 semantically, beyond taking a node and returning its successor?
- What is 0x00921580 semantically? The listing shows two walks -- a +0x4 chain to its last element, and a +0x8 structure -- but nothing names it, and it is not this target.
- What is the concrete type behind the +0x10 receiver word, and what does its table entry at +0x1c do with the flag and the event word?
- What is the concrete type behind the node's +0x10 receiver word, and what does its table entry at +0x1c do with the leading zero and the event word?
- What is the intended meaning of the flag argument, given only that this entry passes 0 and its sibling passes 1?
- What is the intended meaning of the leading argument, given only that this entry passes 0 and its sibling 0x0067e6f0 passes 1 from the same walk?
- Which concrete subtype dispatches through vtable 0x01401b74, and who calls slot 17? There is no direct caller and the executable carries no RTTI.
- Which vtable entries are 0x0067e6f0 and 0x0067e730 called through at runtime, and from which concrete subtype?
