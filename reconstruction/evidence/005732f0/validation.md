# Validation 0x005732f0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-005732f0/swarm_w1_005732f0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 19-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x005732f0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 19-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0x308, 0x30c) and the 0 the complete 19-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x308, 0x30c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (19 of 19 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 19-instruction listing lie inside the recovered body span 0x005732f0..0x0057332b, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 19-instruction body names 2 indirect transfer(s): 0x0057330c dispatches slot 0x4 through the table word in EAX; 0x00573328 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 19 of 19 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'Word': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 19-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7398611fad17fac49a15a590f679ca676876a84c9050d432dbfbf58ccb0c83d4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `14ba4c67c927d000c5a44d2a590260319e836e8d3b54cc19741adefb3bff0ad8`
- Pack digest quoted by the briefing: `7398611fad17fac49a15a590f679ca676876a84c9050d432dbfbf58ccb0c83d4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the two members the same kind of thing? The two halves of the body are the same shape and the same slot displacement, which is suggestive and is not a claim; nothing in the listing relates the two words to each other.
- Is the receiver refilled after the transfer? Both members are 0 when the body returns, and whether the object is re-armed afterwards is a question about the callee and about the owner of the receiver, neither of which is in this listing.
- What class owns the receiver, and what are the two members? The image carries no MSVC RTTI (the word below the table at 0x013f57f8 is 0), the record has no SDK name for this VA, and no decompilation exists, so this package names nothing and asserts no member role.
- What is at table displacement 0x4 of those member objects -- how many slots their tables have, and what the callee does. The slot word is loaded from memory at run time and no body on the far side of it is in evidence, so the callee's argument count, return type and effect are all unobserved.
- What is the ESP the callee sees on the tail path? The machine pops the frame word at 0x00573327 before jumping, so the callee resumes on this body's caller's stack; the model expresses the same transfer as a return, so its callee is entered with the model's frame still live. Nothing in the listing fixes the callee's stack, and no check in the model test pretends to.
- What is the return type? The width is fixed (EAX, 32 bits) and the record classifies the value as pointer-like, but the C type is a source-side choice and the no-member path's EAX is never written by this body at all.
- Why does abi_derived.dispatch record vtable_shaped_loads 0 for a body with two textbook two-level loads? The count disagrees with the listing's own bytes; the listing governs and the model depends on nothing in that record, but the detector's miss is unexplained.
