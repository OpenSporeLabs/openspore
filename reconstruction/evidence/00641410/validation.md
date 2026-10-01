# Validation 0x00641410

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00641410/swarm_w1_00641410.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00641410; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 31-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x0, 0x26), all of which the record accounts for or the listing is the better witness on; the 31-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=31, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x26) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x26), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 31-instruction listing lie inside the recovered body span 0x00641410..0x00641459, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names 4 indirect transfer(s): 0x00641418 dispatches slot 0x24 through the table word in EAX; 0x00641428 dispatches slot 0x24 through the table word in EAX; 0x00641438 dispatches slot 0x24 through the table word in EAX; 0x00641448 dispatches slot 0x24 through the table word in EAX; the machine parse consumed 31 of 31 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 7 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b15caeba844c0e73fcc38be6714403a48f1076836326fac44891bce6b187f188`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `552058c2df5351e1df8fea4cf2fc043870d7a713496dad602b02e9a2c96725b3`
- Pack digest quoted by the briefing: `b15caeba844c0e73fcc38be6714403a48f1076836326fac44891bce6b187f188`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.`, `An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.`, `The trace confirms or refutes that the four literals ever occur in practice, and if so with which receiver class -- this is the only way to name them.`, `The trace shows a second call site whose use of the result (mask, compare, forward) would settle the bool-versus-raw-byte question in the unresolved list.`, `The trace shows whether the dispatch word ever differs between two consecutive reads; if it never does, the three re-reads are confirmed redundant on every observed path and this package's D3 case remains a synthetic refutation only.`, `not_required_for_the_structural_claims_but_unavailable`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace records the dispatch word at each of 0x00641413 / 0x00641421 / 0x00641431 / 0x00641441, the slot-9 target loaded at each of the four following instructions, and the full 32-bit EAX each callee returns.
- An object whose dispatch word points at one of the six tables listed in mechanics.vtable_installations is constructed and FUN_00641410 is entered.
- Does Ghidra have an SDK name for this member? It is FUN_00641410, it carries no namespace, and the live SDK-derived cSPAssetDataOTDB set that sibling packages enumerate does not reach this VA. A name from the ModAPI headers or a vtable-detector pass would settle it; neither was available to this worker.
- Does any real callee in this image ever change the receiver's dispatch word? The four independent `MOV EAX,[ESI]` prove the model must re-read it; whether the re-read ever matters at run time needs a trace. The model test proves only that the model is written to re-read it, which is a synthetic refutation.
- Is the canonical return-type token a C type or a register-class label? The machine-derived record's own vocabulary for this target is 'integral_in_EAX' (reconstruction/evidence/00641410: both the abi and abi_derived layers carry abi.return_semantics = 'integral_in_EAX', and the nested `return` sub-record carries register EAX, register_class 'integral', type null). That token is a REGISTER-CLASS CLASSIFICATION -- it says the value travels in EAX and is integral -- and it is NOT a C or C++ type name, so it can never string-agree with a C++ declaration and is not a width. It is recorded verbatim in observed_original_abi.machine_return_semantics rather than in return_type, and the one-byte width is stated separately in machine_return_width, so the classification is kept without being adopted. What is settled by this package is the WIDTH (one byte, proven over the complete listing) and the C TYPE's agreement with the canonical claim; what is still not settled is whether the ORIGINAL source declared `unsigned char` or `bool` -- see the next-but-one entry -- which no machine evidence here can distinguish because the machine only forwards the byte.
- Is the intended source-level return a bool, or the raw byte at +0x26? The machine forwards the byte unchanged, so a booleanised source is possible and a raw-byte source is possible. The one caller found (0x00ec3ba1) tests AL, which is consistent with either. Settling it needs a second call site or the original source conventions; this package asserts the machine behaviour and reports the ambiguity rather than choosing.
- The trace confirms or refutes that the four literals ever occur in practice, and if so with which receiver class -- this is the only way to name them.
- The trace shows a second call site whose use of the result (mask, compare, forward) would settle the bool-versus-raw-byte question in the unresolved list.
- The trace shows whether the dispatch word ever differs between two consecutive reads; if it never does, the three re-reads are confirmed redundant on every observed path and this package's D3 case remains a synthetic refutation only.
- What do the four literals 0xbcd73e89 / 0xb8669ec9 / 0x37148141 / 0x04f684a4 name? They are compared for full 32-bit equality against the value slot 9 returns, and nothing in this body -- no string, no import, no call -- resolves them. The nearest context is the adjacent predicate at 0x00ec3b60, which makes the same slot-9 dispatch and compares against a fifth literal 0x24720859; and in one table slot 9 is 0x00641770, whose whole body is `MOV EAX,[ECX+0x28]; RET`, i.e. a 32-bit identity word taken from the receiver. That suggests an identity or type tag, but it is a property of one table and one callee, and is recorded as context rather than as the answer. A vtable-detector pass plus the Sporepedia type tables, or a trace of a live object, would settle it; none was available to this worker.
- What is the class of the receiver and what are its other members? Only +0x00 and +0x26 are reachable from this body. Two neighbouring facts are recorded and deliberately NOT modelled as members: the accessor at 0x00641460 reads the byte at +0x25, and 0x00641770 (one candidate slot-9 implementation) reads the dword at +0x28. The +0x28 sub-object is read off a CALLEE's body, not this one.
- Which concrete function is reached at table slot 9? This body names no callee, so the answer is a property of the dispatch word the object carries at run time, and it is additionally unsettled by construction: the six tables that install 0x00641410 name four DIFFERENT functions in slot 9 (0x00641770, 0x00e31100, 0x00641850, 0x00b1e4d0, 0x00dd0e10, 0x00641770), so no single answer can be right for all six. A trace that records the loaded slot-9 address at 0x00641415 and the receiver's class at that moment would settle it.
- not_required_for_the_structural_claims_but_unavailable
