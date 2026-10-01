# Validation 0x006a1510

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-proplist-dispatch-wave14/app_property_list_add_all_properties_from_006a1510.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 19-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x006a1510; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 19-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 19-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 19-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=19, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (19 of 19 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 19-instruction listing lie inside the recovered body span 0x006a1510..0x006a1533, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 19-instruction body names 2 indirect transfer(s): 0x006a1525 dispatches slot 0x38 through the table word in EDX; 0x006a152f dispatches slot 0x30 through the table word in EDX; the machine parse consumed 19 of 19 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x30, 0x38, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9338b2c1437f9092b37108d674b46c94054d34cbd8d671133903f1ad12d20f4c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9b26215ff4107c59ae46f9d6961ed1b3e6889bef49cad0e459a7c71744b9c2f1`
- Pack digest quoted by the briefing: `9338b2c1437f9092b37108d674b46c94054d34cbd8d671133903f1ad12d20f4c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Do the two slot callees really clean up their stack argument? Callee cleanup is inferred from a balanced frame with no ADD ESP; no callee is identified, so the __thiscall shape of the two slot function-pointer types is an inference that a target resolution would confirm or refute.
- Is the return type void or an unclassified word? The machine-derived record declines to classify it (register_class aggregate_unknown, type null) while Ghidra types it void. The reconstruction follows the machine record's own classification string and reports the disagreement rather than resolving it.
- The machine-derived receiver record is bounds_only and enumerates displacement 0 and nothing else, while a literal scan of the listing for ECX operands finds no displacement at all, because the body aliases the receiver into ESI at 0x006a1519 and reads it only as [ESI]. The record and the body therefore agree on the single receiver word this body touches, but that agreement is not evidence that 0x0 is the receiver's only word: a bounds_only record states where the body was seen reaching and is not an enumeration of the object, so it can neither confirm nor refute any receiver word this body happens not to touch. No record in this repository gives the receiver's layout.
- What does the table word at displacement 0x30 hold? It is read at 0x006a1529 and called at 0x006a152f with the receiver in ECX and the stack argument as its single stack argument, and its result is what this body returns. The SDK name makes a void mutator plausible, which is also what the Ghidra decompilation asserts, but no record identifies the slot.
- What does the table word at displacement 0x38 hold? It is read at 0x006a1522 and called at 0x006a1525 with this function's receiver in ECX and the +0x30 word of the argument as its single stack argument. No record in this repository names that target, and the two vtable associations of the function (0x01408820, 0x01408870) are classifier claims rather than slot identities.
- What is the +0x30 word of the argument object? The listing reads it once, tests it for null, and passes it as a stack argument. It is read from the argument, not from the receiver, so the receiver record does not cover it and no record names it; the decompiler's mpParent is one decompiler's guess and is not adopted.
