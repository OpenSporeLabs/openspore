# Validation 0x0098f4d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_misc_engine/misc_engine.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 29-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 1 intra-procedural jump(s) target inside the recovered body span 0x0098f4d0..0x0098f533 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0098f50e; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0098f4d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 29-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 29-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0xac), all of which the record accounts for or the listing is the better witness on; the 29-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=29, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0xac) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 6 displacement(s) (0x-208, 0x-18c, 0xac, 0xb0, 0xb4, 0xb8), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 5 of those (0x-208, 0x-18c, 0xb0, 0xb4, 0xb8) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (29 of 29 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 29-instruction listing lie inside the recovered body span 0x0098f4d0..0x0098f533, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 29-instruction body names 3 indirect transfer(s): 0x0098f4d9 is INDIRECT_NON_VTABLE; 0x0098f524 dispatches slot 0x7c through the table word in EAX; 0x0098f530 dispatches slot 0x90 through the table word in EAX; the machine parse consumed 29 of 29 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3, so the dispatch is visible in the machine listing but is not proven: 1 of the 3 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x0098f4d9), so the dispatch's identity is not established: the target is the memory operand [EAX*0x4 + 0x98f538], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'TargetWord': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 29-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `98ba9d62bbb65e2aa21fb03cb8ae1534b777064f562606390c6823eb7e3109c3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `33d99d543a88b18350442629774596512504828fb83fbd36dc609aa7b4390a55`
- Pack digest quoted by the briefing: `98ba9d62bbb65e2aa21fb03cb8ae1534b777064f562606390c6823eb7e3109c3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-message-queue-service-vtable-and-ownership`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can a selector above 3 occur at runtime and what side effects follow?
- Does the +0x90 result represent a queue pointer, count, or another word?
- What are the complete cMessageManager offsets and queue ownership rules?
- What are the implementations and return widths of service slots +0x7c and +0x90?
- What concrete object is stored at manager-0x208 and how is it published?
- gate-message-queue-service-vtable-and-ownership
- meaning of returned EAX
- queue-pointer ownership
- service owner at manager-0x208
- slot +0x7c and +0x90 meanings
