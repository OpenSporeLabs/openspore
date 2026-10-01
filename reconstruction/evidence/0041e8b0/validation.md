# Validation 0x0041e8b0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_app_safe_wave10/app_safe_wave10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 39-instruction listing name the same 2 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x0041e8b0..0x0041e91b are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0041e903, 0x0041e918; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x0041e8b0; 6 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 39-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 2 member(s) (cursor, limit) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 39-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=39, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x4), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x4) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (39 of 39 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 39-instruction listing lie inside the recovered body span 0x0041e8b0..0x0041e91b, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 39-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 39-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 5 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5b9251a237bf07b467fa67e8e6edeed39154cef50cff2cb6e02fffb89b450ce4`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `bb0f0c4b57c8ff33695765ebb56de7828fb16dd97685a4c0121c3b38f76ceb2a`
- Pack digest quoted by the briefing: `5b9251a237bf07b467fa67e8e6edeed39154cef50cff2cb6e02fffb89b450ce4`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The 0x18 element stride comes from the ADD EAX,0x18 immediate; the element size is not independently confirmed.`, `The argument is modelled as an opaque source pointer; its declared type is unresolved.`, `The cursor buffer base word at +0x00 is never read or written by this body.`, `The element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted.`, `gate-cursor-buffer-emit-runtime-port-semantics`, `runtime validation not performed; static decompilation and disassembly only`, `the 0x18 element stride is a static constant read from the ADD EAX,0x18 immediate; the element size is not independently confirmed`, `the argument is modelled as an opaque source pointer; its declared type is unresolved`, `the cursor buffer base word at +0x00 is never read or written by this body`, `the element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The 0x18 element stride comes from the ADD EAX,0x18 immediate; the element size is not independently confirmed.
- The argument is modelled as an opaque source pointer; its declared type is unresolved.
- The cursor buffer base word at +0x00 is never read or written by this body.
- The element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted.
- What 0x00424010 does with the unadvanced cursor and the limit when the buffer is full
- What 0x00511140 copies and whether it can fail
- What the argument word actually points to and who owns it
- Whether the base word at +0x00 is maintained by the grow port only
- Why a zero cursor skips the copy, since the cursor is advanced regardless
- gate-cursor-buffer-emit-runtime-port-semantics
- runtime validation not performed; static decompilation and disassembly only
- the 0x18 element stride is a static constant read from the ADD EAX,0x18 immediate; the element size is not independently confirmed
- the argument is modelled as an opaque source pointer; its declared type is unresolved
- the cursor buffer base word at +0x00 is never read or written by this body
- the element copy port 0x00511140 and the grow port 0x00424010 are opaque seams and are not promoted
