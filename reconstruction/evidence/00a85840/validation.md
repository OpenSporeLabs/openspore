# Validation 0x00a85840

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00a85840/w2_00a85840.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00a85840; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 31-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x24), all of which the record accounts for or the listing is the better witness on; the 31-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=31, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x24) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the listing shows 1 displacement(s) the record does not enumerate (0x24), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and all 12 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 31-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `4c177208f0bf564baa94b336bf3eb65c9523a36ebebb59cbed7d46b8a36cfc5a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f829e4b4223adf36106678455c59e0a695e60840fc83033f3e83e5554f9d2587`
- Pack digest quoted by the briefing: `4c177208f0bf564baa94b336bf3eb65c9523a36ebebb59cbed7d46b8a36cfc5a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- HOW FAR THE TABLE AT 0x01458024 RUNS. Seven words from 0x01458024 to 0x0145803f are transcribed, and the run of .text-looking words continues past the own slot (0x00951230, 0x0052e640 at 0x01458040..0x01458047). Nothing in the record or in a code reference fixes the table's end, so no length is claimed.
- NO DECOMPILATION EXISTS for this VA in this session: the evidence pack's decompilation category is absent and there is no second, independently-derived reading to cross-check the reconstruction against.
- THE 0x6c OBJECT SIZE AND EVERY RECEIVER MEMBER ABOVE +0x24. The +0x24 LEA and 0x00537dc0's own extent bound this body at 0x5c on its own. The 0x6c figure in this package's earlier revision came from 0x00a853b0, a DIFFERENT listing, and it is not used here.
- THE DECLARED RETURN TYPE IS A SOURCE-SIDE CHOICE THE MACHINE CANNOT SETTLE. The machine return state is UNCLASSIFIED: the ABI record names XMM0, and evidence_returns.classify returns UNCLASSIFIED on that alone -- "the machine fixes where the value travels and not the C type, and no width can be claimed". There is no width record, no return_semantics string that is a C type, and no incoming call edge to read a caller's use of EAX or XMM0. void and T* are byte-identical here because the body contains no instruction that places a value in a return register at the terminator. void was taken as the weaker claim. The disagreement with the record's XMM0 is recorded, not arbitrated.
- THE DOMAIN TYPES. ghidra_function.sdk_name is null for this VA, there is no MSVC RTTI in this binary, and the four listings read here fix offsets and widths but no names. Every member in this package is an immediate out of an instruction and nothing is named for a field.
- THE PROVENANCE OF BOTH STACK WORDS. Both are plain pointers the body only reads or only forwards, and neither has a call site to inspect, so the argument order and types of every caller are outside this evidence. The arity of two comes from the terminator alone.
- WHAT 0x00537dc0's FOUR CONDITIONAL ARMS DECIDE. 0x00537dd7, 0x00537df4, 0x00537e09 and 0x00537e31 choose whether receiver+0x24 is overwritten or kept, so whether the merge lands is decided by that callee and by the two before it. This body is indifferent: it passes and returns. The two helpers it calls internally, 0x0041dd30 and 0x0041dd90, are not modelled either.
- WHAT 0x00537f40 DOES beyond being called. Its own body was not read for this package; only its terminator (0x00537ff5 RET 0x4) was. So the +0x04..+0x0c region of the local and the 0x24 bytes the second callee writes at its receiver's +0x14 are uncharacterised, and the local's 0x38 extent is a requirement of that callee's own listing rather than a claim about the helpers.
- WHETHER THE FOUR BYTES AT ARGUMENT 2 + 0x14 ARE ONE OBJECT OR A POINTER. 0x0041cb40 copies them as three of its nine dwords; the bytes move verbatim either way, so the two readings are byte-identical in this package and what the value means is outside this body.
