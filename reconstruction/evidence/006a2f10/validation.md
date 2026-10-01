# Validation 0x006a2f10

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-app-proplist-wave13/app_property_list_add_from_006a2f10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 30-instruction listing name the same 2 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x006a2f10..0x006a2f51 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a2f30; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x006a2f10; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 30-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x34) and the 0 the complete 30-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x34), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (30 of 30 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 30-instruction listing lie inside the recovered body span 0x006a2f10..0x006a2f51, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 30-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 30-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f3f37d2d9217c01f9168687ccb1d0164b2081eae05f8b8577f4b56e45a77a0a0`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d49a51ecc3d534ccaaadc6b577be5bff3d71f37eeef983f8eb04eb11246544fd`
- Pack digest quoted by the briefing: `f3f37d2d9217c01f9168687ccb1d0164b2081eae05f8b8577f4b56e45a77a0a0`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- RESOLVED (no longer open) -- CALLS oracle disagreement. The xref export (dependencies.edges) records 2 callees -- 0x006a2d30 from callsite 0x006a2f37 and 0x00542b80 from callsite 0x006a2f3e, both reference_type direct-call -- while the complete 30-instruction listing holds 3 direct transfers: those same 2 CALLs plus 0x006a2f2b JMP 0x006a2f30. extra was {0x006a2f30}, absent {}. The briefing called the extra transfer a tail call; the machine says otherwise and the source follows the machine. The validator's reader has since been fixed to exclude a JMP immediate landing inside the recovered body span, so CALLS now reports PASS with this reconstruction naming only the two real callees.
- Return-type evidence conflict: the machine-derived ABI record classifies the return as unclassified_in_EAX / aggregate_unknown with void_possible false, while the live Ghidra prototype and the decompiled body say void. The source encodes void, which is why RETURN SEMANTICS is WARN. The record's abstained_because attributes the gap to unmodelled flow rather than to an observed aggregate return, but no positive machine fact closes it.
- SETTLED BY THE MACHINE, recorded because it is the load-bearing claim: 0x006a2f30 is not a callee. It is LEA EAX,[ESI+0x4], the first instruction of the loop body block; it lies inside the body span 0x006a2f10..0x006a2f51; control enters it from the preheader at 0x006a2f2b and re-enters it from the back edge 0x006a2f48 (JNZ 0x006a2f30), and it falls out of the loop at 0x006a2f4a (POP EBX). A tail call would transfer control out of the body and this one does not, so naming a callee at 0x006a2f30 would have been a false callee. This is now also the validator's own exclusion rule; the fix still treats a JMP outside the span as a genuine tail call.
- STILL OPEN (unchanged by the fix): the export side of the disagreement is not independently checkable here. Nothing in the evidence pack records the export's own transfer extraction, so whether the export deliberately records calls only (and would therefore also miss a genuine tail call at some other target) or missed this one transfer specifically cannot be settled from the pack.
- The meaning of the word at receiver+0x34. It is incremented once per non-refused call, including for an empty range. It is consistent with a completed-copy counter (the decompiler names it mnOperationsDone) but the body alone cannot distinguish a counter from a generation or version field.
- What 0x00542b80 does. It takes the pointer returned by 0x006a2d30 in ECX and the element pointer on the stack, and its result is discarded. Whether it copies, initialises or releases the element is not established.
- What 0x006a2d30 does. It takes the receiver's storage word (receiver+0x18) in ECX and one stack dword (element+0x4) and returns a pointer that becomes the next call's receiver. Whether that is a vector-style insert, an element factory, or a reallocator is not established; the Ghidra name is FUN_006a2d30 and no persisted decompilation for it was collected in this package.
- Whether the decompiler's mProperties.mpBegin/mpEnd and mnOperationsDone names carry real SDK field identity. The binary has no MSVC RTTI, so those names are the decompiler's inference from the offsets and are not used as evidence anywhere in this package.
- Whether the two calls are a copy or a move: the stride walk reads the argument's range while writing through the receiver's storage word, and the body does not test for overlap between the two ranges, so whether a same-object or overlapping-range call is safe is decided by the callees and is not established here.
