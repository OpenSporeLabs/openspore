# Validation 0x00573c00

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b00/editor_00573c00.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 115-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 115-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0xcc, 0x3b0), all of which the record accounts for or the listing is the better witness on; the 115-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=115, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0xcc, 0x3b0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 9 displacement(s) (0x3c, 0xcc, 0xe4, 0x31c, 0x398, 0x3b0, 0x3b4, 0x3c4, 0x498), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 7 of those (0x3c, 0xe4, 0x31c, 0x398, 0x3b4, 0x3c4, 0x498) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (115 of 115 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 21 conditional branch target(s) in the complete 115-instruction listing lie inside the recovered body span 0x00573c00..0x00573d69, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 115-instruction body names 1 indirect transfer(s): 0x00573caa dispatches slot 0x8 through the table word in EAX; the machine parse consumed 115 of 115 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `e24f97e2807336f8f07f06e4058f94c070dd91a4d5800f39d996fce38e64d8c6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5071e8e41207c57b18297b8f19500d8bb68173a16bc943b1e10ba491f4be3d65`
- Pack digest quoted by the briefing: `e24f97e2807336f8f07f06e4058f94c070dd91a4d5800f39d996fce38e64d8c6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `12 of the 13 recorded callsites were not disassembled. A full callsite sweep is static work and is listed in unresolved_questions rather than as a runtime gate.`, `No original-process trace exists for 0x00573c00; every claim is static and the Cell stage has never been entered in any recorded run.`, `The +0xdc8 bit semantics are the single largest gap and only a run can close it: each bit must be observed being set on a real rigblock together with the behaviour it gates.`, `The vtable slot +0x8 callee, and the concrete types of the +0x498 and +0x3c4 receivers, require a run with a real editor session.`, `Whether the discarded comparison at 0x00573c6f matters for its callee's side effects can only be settled by instrumenting 0x004a60a0 at runtime.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 12 of the 13 recorded callsites were not disassembled. A full callsite sweep is static work and is listed in unresolved_questions rather than as a runtime gate.
- Is 0x00573c00 a vtable entry of the editor or of the mode classes? No vtable for the editor was located and no pointer scan for this address was performed.
- Is the discarded comparison at 0x00573c6f a source-level dead store, or does 0x004a60a0 have a side effect that matters? If the latter, the reimplementation must still call it even though the answer is unused. Static evidence cannot separate these.
- No original-process trace exists for 0x00573c00; every claim is static and the Cell stage has never been entered in any recorded run.
- Only 1 of the 13 recorded callsites was disassembled. The argument distribution across the fan-in, and in particular whether the 0xffffffff region sentinel seen at 0x00573e9d is common, is not established.
- The +0xdc8 bit semantics are the single largest gap and only a run can close it: each bit must be observed being set on a real rigblock together with the behaviour it gates.
- The vtable slot +0x8 callee, and the concrete types of the +0x498 and +0x3c4 receivers, require a run with a real editor session.
- What do 0x004b09b0 (which receives the ADDRESS of the field as its this), 0x0043a830 with its 0/1 phases, and 0x0043e2b0 actually do? Only their call shapes and gates are observed.
- What do the +0xdc8 flag bits mean? Bits 1, 3, 7, 10, 11 and 20 are read across this function, 0x004a2060 and 0x00573520, and every one of them gates a distinct behaviour. No SDK header names them.
- What is the tag 0xbb58117e, and what are 0x3475365 / 0x3475381 / 0x3475385 in the marker emitter? They are hashed names; none is in the SDK.
- What is the type of the +0x498 and +0x3c4 fields? The SDK declares both as int/pointer mixtures; the binary passes their VALUES as thiscall receivers to 0x005cc690 and 0x005ca920, so they are objects, but which classes is unknown.
- Whether the discarded comparison at 0x00573c6f matters for its callee's side effects can only be settled by instrumenting 0x004a60a0 at runtime.
- Which vtable entry is at slot +0x8, and of which table? No vtable for the rigblock type was located and the receiver is a runtime value, so neither the table address nor the concrete callee is available statically.
