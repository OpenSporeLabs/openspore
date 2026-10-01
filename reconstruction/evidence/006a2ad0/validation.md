# Validation 0x006a2ad0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-direct-property-copyfrom-wave14/direct_property_list_copyfrom_006a2ad0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 33-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x006a2ad0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 33-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 5 displacement(s) (0x4, 0x14, 0x18, 0x1c, 0x30) and every one of them is a displacement the complete 33-instruction listing shows: 2 attributed to the receiver ECX as proven (0x18, 0x30); 3 more (0x4, 0x14, 0x1c) are shown by the listing under a base that is not the receiver -- 0x4 under ESI; 0x14 under EAX; 0x1c under EBX -- so the body does use those displacements, on an object this check cannot identify; that is a limit of the attribution here and not a disagreement with the receiver, and no receiver contradiction is claimed for them; the 33-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=33, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x18, 0x30) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x30), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x18), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (33 of 33 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 33-instruction listing lie inside the recovered body span 0x006a2ad0..0x006a2b15, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 33-instruction body names 1 indirect transfer(s): 0x006a2afe dispatches slot 0x14 through the table word in EAX; the machine parse consumed 33 of 33 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x14, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b15e35e5c91141036babdea74291b39015d0026aee642e877d07f3e588366523`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `73e287596603cfa5f34a787c8c427679e9d9ed70166f48a906e5c9faa6339e15`
- Pack digest quoted by the briefing: `b15e35e5c91141036babdea74291b39015d0026aee642e877d07f3e588366523`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists in this repository, so nothing about this body's runtime behaviour is validated: the slot target, the resize contract of 0x006a28f0 and the parent publication at displacement 0x30 are static claims only.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the derived ABI record's inability to classify the last EAX write (return.register_class aggregate_unknown) a real second return value, or only EAX being live across the indirect call? The void claim rests on the decompiler and on the exit paths, not on the derived record.
- Is the receiver's word at displacement 0x0 really a vtable pointer, and if so which slot index does displacement 0x14 correspond to in vtable:0x01408870? The association and the single xref from 0x0140889c support it, but the derived ABI record's vtable_shaped_loads count is 0, so the reading is INFERRED.
- No original-process trace exists in this repository, so nothing about this body's runtime behaviour is validated: the slot target, the resize contract of 0x006a28f0 and the parent publication at displacement 0x30 are static claims only.
- The derived ABI record abstained on flow ('the linear ESP walk ends at +12'), and the derived record's calling-convention confidence is INFERRED rather than proven; no live cross-validation of the convention exists in this repository.
- The machine-derived receiver record for this body is bounds_only and enumerates 0x0 and 0x30. bounds_only means it states where the body was SEEN REACHING and nothing more: it is an observation of the inference's own access, not an enumeration of the receiver's words, and it is not a statement about the object. This body addresses receiver displacement 0x18 (LEA ECX,[EDI + 0x18] at 0x006a2add) and the record does not list it, so 0x18 is UNCORROBORATED BY the record, not contradicted by it -- a bounds_only record cannot refute anything, and the absence of 0x18 from its list carries no information about whether the receiver has a word there. The record's observation criteria are not documented in this repository, so it is not established here that a bounds_only record would have listed 0x18 had it been reached identically to 0x0 and 0x30; all three are reached through the same EDI alias, which is the one thing that makes the omission worth a question rather than a shrug. The receiver's layout is therefore unresolved in both directions: neither confirmed nor denied at 0x18, and confirmed nowhere else either. Separately, of the five displacements this source declares (0x4, 0x14, 0x18, 0x1c, 0x30), only 0x18 and 0x30 are receiver displacements at all -- 0x4 is on the element, 0x14 is on the receiver's table word, and 0x1c is on the argument object -- so a receiver record's silence about those three is not a statement about the receiver.
- What does 0x006a28f0 do with the range it is given beyond sizing it -- 0x00612b20 and 0x00685a30 are called inside it and are not characterised by this package.
- What is the exact element type of the 0x18-stride range? The stride and the two pushed words (element + 0x0 and the address element + 0x4) are observed, but nothing here establishes the fields between them.
- Which function does the receiver's slot at displacement 0x14 point at? No machine record in this package names it, so the indirect call is reconstructed as a call through a function-pointer local and its target is left unresolved.
- Why does the body form the address receiver + 0x18 and hand it to 0x006a28f0 before reading the source range at 0x18/0x1c of the argument, when the argument word at 0x18 is itself a range begin pointer? Sizing the destination before measuring the source is observable in the ordering, but whether 0x006a28f0 derives the element count from the destination's own state or from something the caller set up earlier is not established by this body.
