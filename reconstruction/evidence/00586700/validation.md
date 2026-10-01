# Validation 0x00586700

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00586700/sw2_00586700.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 89-instruction listing name the same 2 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00586700..0x005867f3 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00586752, 0x005867cf; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 4 outgoing call edge row(s) over 2 distinct address(es) for 0x00586700; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 89-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 3 displacement(s) the source span declares (0x4d8, 0x4ec, 0x50c) and the 0 the complete 89-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x4d8, 0x4ec, 0x508, 0x50c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (89 of 89 instruction(s), 0 unparsed) and all 3 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 89-instruction listing lie inside the recovered body span 0x00586700..0x005867f3, so the branch graph is closed inside it; the source span declares for, if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 89-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | the machine return state is NOT_AVAILABLE and the source span declares return type 'int': no ABI field records a return register, a return semantic or a return type for this target, so there is no machine record to read a return claim from. There is no state to compare the declaration against, and none is invented. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `79c77d444ca1657a5af6ce7b039074a7f2f5909d5106c4a6f4ae881ea0d7017c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9751cf1a38d3d5d1732c8e105eff4fe01b637620e0d73d52c91824e0ad382bec`
- Pack digest quoted by the briefing: `79c77d444ca1657a5af6ce7b039074a7f2f5909d5106c4a6f4ae881ea0d7017c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- EVIDENCE COVERAGE is a WARN because 10 of the 17 static categories in the pack are available: callees_dependencies, callers_dependencies, contradictions, external_callees, globals, semantic_hypotheses and types all report availability 'unavailable' / evidence_state 'MISSING'. This is a property of the committed evidence pack and is not fixable from a source file. Note that the missing 'types' category is why the FIELDS/OFFSETS arm falls back to the receiver's displacement bounds and why no member could be named even had one been wanted.
- RETURN SEMANTICS is a WARN by construction and this package does not pretend otherwise. The canonical ABI record's return_semantics is the machine phrase 'integral_in_EAX', so no C++ declaration can agree with it as a string and the dimension WARNs whatever is written. This package took section 7.1's option (a) and declared `int`, which is true of the listing (EAX = 0x23 at the single reachable return) and is the width evidence_returns.classify computes on its own (WIDTH_4_IN_EAX). It did NOT take option (b) and declare void, because the bytes do produce a four-byte value and void would be a claim the machine contradicts. It did NOT invent a typedef named after the phrase, which would be a validator hack. If a reviewer prefers void, the change is one token and the two alternatives are argued above.
- The class this entry point belongs to. The 29-word run at 0x013f57f8 is confirmed to be a class dispatch table by the sole DATA xref and by six of its slots being named independently in this target's analogue record, and this body is its word index 20. No class name, no slot meaning and no member identity is claimed, and none is derivable from this body: it contains no indirect transfer and never reads its receiver's +0x00.
- The identity of the dword at self+0x4ec and of the six dwords at self+0x4f0 + 4k. This body zeroes them (0x00586766 and 0x00586786) and never reads them on any path, so nothing here establishes what they are. Their stride of four and count of six are fixed; their meaning is not.
- The object's real size. This body writes no byte above self+0x573 and reads no byte of the receiver outside 0x4d8..0x573. The model test's fixture is 0x600 bytes so that the thunk's source argument, which is whatever the current word holds, can be pointed anywhere without leaving the fixture. 0x574 is a lower bound on the layout, not a claim about it.
- The reload of the start word in the two zeroing loops (0x00586754 and 0x005867d1) is reproduced in the source but is not independently observable: no instruction between the reload and the store can change that word on either path, so the test asserts the effect and not the reload. Stating it as a note rather than a test is deliberate.
- What 0x005151b0 does internally. Its call boundary is reconstructed from the four stack words, the ECX receiver and the callee's own 295 instructions, and the word 'buffer' is licensed by those bytes -- but its grow-and-copy internals, its allocator protocol through 0x0042dee0 and its fill semantics beyond 'advance the current word and zero up to start+35' are NOT reconstructed. This body is not required to depend on any of it, and the model test proves it does not: with a completely passive observer that writes nothing, the reconstruction's observable result is unchanged.
- Whether the 20-byte walker stride is a 16-byte element plus 4 bytes of padding, a 12-byte start/current/capacity triple plus 8 bytes, or something else. The stride and the two word displacements are fixed by 0x005867e2 and 0x0058678f/0x00586792; the element's size is not. 0x005151b0 reads its receiver's +0x0c (0x00515461), which puts a floor of sixteen bytes under it, and the remaining four are unaccounted for.
- Which side pops the arguments of 0x005151b0. The original is 0x005155ed RET 0xc, callee-owned twelve bytes; the GCC spelling of __thiscall used in this package's header is caller-owned. The model reproduces the RECEIVER REGISTER and the ARGUMENT ORDER and not the cleanup side, because the two cannot both be reproduced through one GCC attribute. The cdecl thunk's balance IS measured (ESP sampled around the call), and the observations' own frame addresses are compared with the caller's. This is stated in the header rather than hidden.
