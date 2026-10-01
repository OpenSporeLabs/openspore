# Validation 0x00641fd0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00641fd0/sw1_00641fd0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 62-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00641fd0; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 62-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 62-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x8, 0x3c), all of which the record accounts for or the listing is the better witness on; the 62-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=62, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x8, 0x3c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x0, 0x8, 0x3c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (62 of 62 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 62-instruction listing lie inside the recovered body span 0x00641fd0..0x0064206c, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 62-instruction body names 3 indirect transfer(s): 0x00641ffc dispatches slot 0x90 through the table word in EAX; 0x00642050 dispatches slot 0x4 through the table word in EDX; 0x00642063 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 62 of 62 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 13 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `af445398eff5c5adfde5079a89d326a38e81fa5fb4d934bd1aa4090ce1103373`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `873b6dda48cd92c8dbbba653e7cd69796ae124ba6c8308c2b48a83d3575afab1`
- Pack digest quoted by the briefing: `af445398eff5c5adfde5079a89d326a38e81fa5fb4d934bd1aa4090ce1103373`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No ordinary caller is named. The record's callers list is empty and the xref export has no inbound call edge; the only inbound references are the seven vtable slots. So the contract of the return value -- whether a caller releases what it is handed, or only inspects it -- is unestablished, and the reconstruction asserts the reference is taken and never released, which is all the body shows.
- The 0x0067cb30 global's identity is not established. The callee returns the dword at 0x015fcc70 and the body reads the service out of that object's +0x5c; whether 0x015fcc70 holds a manager, a registry or a singleton pointer is not fixed by anything in this set, and the address is deliberately kept out of the reconstruction's function span.
- The RETURN SEMANTICS pass is partly self-referential and a reader should know it. The index record's abi was an empty object before this sidecar existed, so the only canonical return claim the validator could find is the one THIS SIDECAR contributes (observed_original_abi.return_type = "void*"), and the check compares that against the span's own declaration. The machine contributes the width and nothing more: abi_derived.return says register EAX, register_class "integral", type null. Before this sidecar existed the check would have compared the evidence pack's prose claim "integral_in_EAX" with the declaration and reported WARN. The integrator should treat the machine-fixed part (a 32-bit word in EAX, three exits, no sret) as the finding and the C spelling as a source-side choice, and should re-check this if the record's return_type is later replaced by a machine-derived one.
- The class name SporepediaAssetDataOtdb is INFERRED from vtable co-membership with the nine sibling functions the repository research queue names Sporepedia::cSPAssetDataOTDB::*, and from nothing in this body's own bytes. It is a type name, not a claim about behaviour, and the model asserts nothing that depends on it.
- What the 8-byte object means, and what the sentinel 0xffffffff means, is not established. The body seeds both words with it, hands the pair to the slot +0x90 dispatch by address, and re-reads whatever came back. A pair of handles initialised to 'unset' and a pair of sentinel-tagged ids are both consistent with the 62 instructions. That the dispatch is given the pair's ADDRESS (so it fills an out-parameter) is machine-fixed; what the pair denotes is not.
- What the receiver's +0x3c word IS is not established. The body tests it against zero, returns it unchanged and never dereferences it, so a cached pointer and a cached integer are indistinguishable here. It is the fastest path in the function, which is a shape a cache or a memoised handle would have, and the +0x3c displacement is consistent with a pointer-sized field -- but no record names it and this package claims nothing beyond the word.
- Whether 0x00613860's key and 0x00612f50's pair are the same kind of identifier is not established. 0x00613860 compares its argument unsigned against an array element's leading word, and 0x00612f50 takes a PAIR and walks elements on a 0x10 stride, so the two callees walk differently-shaped tables. The body passes the receiver's +0x08 to the first and the dispatch's output pair to the second, and nothing here says the two identifiers are related.
- Whether the slot +0x04 call is an acquire, a retain, a copy-assign or a validation probe is not established. It sits at index 1 of the resolved handle's own table, it takes the handle in ECX with no stack word, its return value is dead, and the body never releases. 'Acquire' is the reading this package's naming uses and the model test's log strings use, and it is a reading, not a fact.
- Which of 0x00612f50's pointer arguments it treats as the out-pointer is not settled from the callee's own frame, and this is reported rather than resolved. The callee reads its first argument as a dword (0x612f7c) and takes its address (0x612f69), and at 0x612fd5 it reads [ESP+0x1c] with its own PUSH EBP -- entry+8, its SECOND argument -- into EBP and stores through it at 0x612fec, while this body reads back the THIRD argument's pointee. Those can both be true only if the callee treats more than one of its pointer arguments as writable, or if the walk of the callee's own frame is wrong. It does not affect this reconstruction: what THIS body does -- pass the address of its third frame word as the third argument, zero that word immediately before the call, and read it back afterwards -- is fixed by this body's own bytes at 0x00642027, 0x00642030 and 0x0064203d, and that is the claim the model asserts.
