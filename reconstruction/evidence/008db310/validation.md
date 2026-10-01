# Validation 0x008db310

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-orchestrate-dogfood-008db310/dogfood_008db310.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 57-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 1 intra-procedural jump(s) target inside the recovered body span 0x008db310..0x008db38d are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x008db370; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x008db310; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 57-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 5 displacement(s) (0xc, 0x10, 0x1c, 0x2c, 0x30) and every one of them is a displacement the complete 57-instruction listing shows: 2 attributed to the receiver ECX as proven (0x2c, 0x30); 3 more (0xc, 0x10, 0x1c) are shown by the listing under a base that is not the receiver -- 0xc under EAX; 0x10 under EAX; 0x1c under EAX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 57-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=57, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x2c, 0x30) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x2c, 0x30, 0x34, 0x38), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x34, 0x38) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (57 of 57 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 57-instruction listing lie inside the recovered body span 0x008db310..0x008db38d, so the branch graph is closed inside it; the source span declares for, if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 57-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `6895e4f7d428b10969d95e8fe8ac3079dc5080314985df808258a94d19ba1831`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `995484d538363e5519f1f047d62787cedd87cf28bca2ef40610689d77a4fe64f`
- Pack digest quoted by the briefing: `6895e4f7d428b10969d95e8fe8ac3079dc5080314985df808258a94d19ba1831`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.`, `No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.`, `The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.`, `The owner of the pointer run around 0x01436878 that stores 0x008db310 at 0x014368bc is unknown, so the class that reaches this function and the slot index it occupies are unproved.`, `The record interval values at node+0x0c and node+0x10 are treated as opaque 32-bit offsets; the buffer they index is not identified from this function.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete ItemsMap node and bucket ownership semantics
- Does the word at carrier+0x30 always equal the live bucket count, or can it be an independent end index? The body only uses it to scale an index into the slot array.
- How is the chain at node+0x1c maintained, and can a null link with an exhausted slot run occur in a real index instance? The machine body would read past the array in that case; the model bounds the cursor at the end sentinel instead.
- Is the second stack word a byte count of the destination buffer or a count of index entries? The body only proves that it is added to the destination pointer and compared against node record offsets in the same units as node+0x10.
- No direct caller xref exists, so the producer of the destination pointer and the meaning of the extent word in bytes versus an index count are unconfirmed.
- No original-process invocation or indirect-caller trace was captured; runtime_validation stays 0.
- The end sentinel at slots[carrier+0x30] is proven as a terminating value but its construction and lifetime are unresolved.
- The owner of the pointer run around 0x01436878 that stores 0x008db310 at 0x014368bc is unknown, so the class that reaches this function and the slot index it occupies are unproved.
- The record interval values at node+0x0c and node+0x10 are treated as opaque 32-bit offsets; the buffer they index is not identified from this function.
- The vtable/data-table owner that reaches this otherwise uncalled function
- What is the owner and slot index of the pointer table that references 0x008db310 at 0x014368bc, and is 0x01436878 that table's base?
- Whether destination_size is a byte count or a target index extent in all callers
- Why does the imported prototype expose four explicit parameters while the machine reads two and returns RET 0x8? The decompiler banner reports an unknown calling convention for this function.
