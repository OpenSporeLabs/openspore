# Validation 0x00a980b0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00a980b0/sw2_00a980b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 112-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00a980b0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 112-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 112-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x10), all of which the record accounts for or the listing is the better witness on; the 112-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=112, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x10) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0xc, 0x10, 0x14, 0x50), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0xc, 0x14, 0x50) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (112 of 112 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 112-instruction listing lie inside the recovered body span 0x00a980b0..0x00a981f2, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 112-instruction body names 4 indirect transfer(s): 0x00a9816a dispatches slot 0x14 through the table word in EDX; 0x00a9818f dispatches slot 0x14 through the table word in EDX; 0x00a981bc dispatches slot 0x14 through the table word in EDX; 0x00a981ea dispatches slot 0x14 through the table word in EDX; the machine parse consumed 112 of 112 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9e37133623f2ea5bfdcf1880d236510d085c871a464ab81f32b40462e3b349c1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8474bf96506b4127891aac5bbe39640db025662f0159b786cb2602931c8c805d`
- Pack digest quoted by the briefing: `9e37133623f2ea5bfdcf1880d236510d085c871a464ab81f32b40462e3b349c1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- RETURN SEMANTICS, the one place this reconstruction and the machine record disagree, and the disagreement is not resolvable from this evidence: the record names XMM0 as the return register with return_semantics float_or_x87_in_XMM0 and abi.return.void_possible false, while the body produces nothing a caller can read on both paths. The worker's position is that inference RT1 fired on the mere presence of the SSE store at 0x00a980c9, and that void is the byte-accurate answer. A reviewer who prefers the record's reading would have to say what the caller receives on the 0x00a980ba path, where XMM0 is never written. No typedef named after the machine phrase was created to make the string comparison agree.
- The abi inference record abstains with `flow_not_modelled: the linear ESP walk ends at +48, so the listing is not one path`. This package's frame resolution is the flow-aware replacement and it closes to the byte (0x10 + 0x40 == 0x50), so the abstention is not a gap in the reconstruction; it is recorded because the record itself declines to have an opinion and a reader comparing the two should know which one is doing the work.
- The receiver's +0x10 byte is a one-shot latch in this body. Whether any other body in the cluster clears it, and therefore whether this body is ever re-entered, was not determined: no listing other than 0x00883860, 0x00883870 and the vtable was read, and the constructor that would install vtable 0x01458788 was NOT found (the only byte-level hit for the immediate 0x01458788 is a false positive inside `movss dword ptr [ESI+0x18],xmm0` at 0x00a9775f). The receiver's own size therefore rests on this body's 0x54 bound alone and is not corroborated by a constructor.
- The service's slot-5 callee is not identified. The body dispatches to it four times with three different argument shapes and never uses what it returns, and the record's vtable_shaped_loads is 0, so nothing in this pack names it. Whether the receiver is the service or a peer of it -- which the fact that argument 3 is always zero and argument 1 is a 32-bit value does not settle -- is also open.
- What are the two pushed immediates 0x0e7a8471 and 0x0e7a8473? They differ by two and are passed as the first argument of a slot-5 call on a service, alongside a 0x10-byte buffer holding a small integer. They read as two adjacent enum values or property ids, but nothing in these 112 instructions says so, and no other listing was consulted to settle it.
- What does bit 4 of the flag word mean? The body never tests it -- the shift immediates are 3, 5, 6, 7, 8, 9 -- so a bit-4-only flag word provably changes nothing here, and the model test pins that. Which consumer does test it is outside this body.
- What is the 0x40-byte argument? Its eight dwords land at a uniform stride of 8, five of them from five consecutive dwords of the attribute object under five flag bits, and three of them unconditionally (a zero, the receiver's +0x50 word, and the address of the receiver's +0x18). The stride and the sizes are facts; whether each 8-byte slot is a pair of two dwords, or something else with a 4-byte-aligned first field, is INFERRED from the frame fitting exactly and is not settled by the listing.
- Why do the three unconditional slots (5, 6 and 7) hold values of a visibly different kind from the five flag-gated ones -- an address and a receiver word and a zero against five copied scalars? Nothing in this body says whether they share a type.
