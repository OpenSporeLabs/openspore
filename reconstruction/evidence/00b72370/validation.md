# Validation 0x00b72370

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-orchestrate-dogfood-00b72370/dogfood_00b72370.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00b72370; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 31-instruction listing names 1 data address(es) (0x1465004) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 31-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4, 0x20), all of which the record accounts for or the listing is the better witness on; the 31-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=31, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4, 0x20) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x20, 0x24, 0x28, 0x2c, 0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 4 of those (0x24, 0x28, 0x2c, 0x30) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 31-instruction listing lie inside the recovered body span 0x00b72370..0x00b723c0, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names 1 indirect transfer(s): 0x00b723b3 dispatches slot 0x24 through the table word in EAX; the machine parse consumed 31 of 31 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `cf82b7c6de125b8efdec09a23114e738439644ca170417e45d82ec4f2ddf43ee`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cc76f283d878ad8d2f3ec4ca02a9f14be05ead4b7a8a6d6220cc5a7116bffeb3`
- Pack digest quoted by the briefing: `cf82b7c6de125b8efdec09a23114e738439644ca170417e45d82ec4f2ddf43ee`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Observe a real dispatch through the vtable word at 0x014650f0 and record the receiver instance state before and after the five stores.`, `Observe initialization and write ordering of the global word 0x016514cc through 0x00883870.`, `Observe whether any later consumer reads the receiver words at +0x28 and +0x2c published here; 0x00b79a60 is the only such consumer found statically.`, `Record the concrete target of the vtable slot at displacement 0x24 and observe its argument use and return-value handling.`, `Record the live values of the eight words at 0x01465004 and the concrete class of the object returned by 0x00883860.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x014650e8 the true base of the containing vtable, or is it a word inside a larger class-registration table? The run is contiguous but sits next to class-name strings and a NULL separator, and the class owner is unknown.
- Is the receiver-minus-four word (LEA EBX,[ESI + -0x4]) a cObjectPoolIndex as the SDK decompilation names it, an adjusted this, or an unrelated token? The disassembly pushes no stack argument, so the SDK's second formal cannot be a parameter and the word is never dereferenced by this body.
- Observe a real dispatch through the vtable word at 0x014650f0 and record the receiver instance state before and after the five stores.
- Observe initialization and write ordering of the global word 0x016514cc through 0x00883870.
- Observe whether any later consumer reads the receiver words at +0x28 and +0x2c published here; 0x00b79a60 is the only such consumer found statically.
- Record the concrete target of the vtable slot at displacement 0x24 and observe its argument use and return-value handling.
- Record the live values of the eight words at 0x01465004 and the concrete class of the object returned by 0x00883860.
- The conflict ledger entry U-008-scenario-respawner lists this address among state-event anchors but reports the transition policy, consumer order, and runtime reachability as unresolved; that ledger entry is unchanged by this reconstruction.
- What concrete class carries the vtable whose slot at displacement 0x24 is dispatched here, and what is the meaning of the (token, source word) argument pair? No RTTI, no vtable label, and no SDK name for the dispatch target is recovered.
- What is the relationship, if any, between the immediate slot-0x24 dispatch in this body and the slot-0x2c dispatch that 0x00b79a60 performs over the same five published words? The arity and the slot differ, and no call path between the two functions was recovered.
- Why is the source window at 0x01465004 a fixed eight-word global table rather than data owned by the receiver? No writer, no owner, and no SDK name for those eight words is recovered.
