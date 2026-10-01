# Validation 0x00dd0550

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00dd0550/swarmw1_00dd0550.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 16-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00dd0550; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 16-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 16-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x80), all of which the record accounts for or the listing is the better witness on; the 16-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=16, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x80) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x80), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (16 of 16 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 16-instruction listing lie inside the recovered body span 0x00dd0550..0x00dd0573, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 16-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `da5e43ff75385b9e013559e771306ccadbb9c28fb36d046520cc00696d037658`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9665d149d2936e5b476c3e386c94f21d7b51900946af77d69a34fc01cbeeab3b`
- Pack digest quoted by the briefing: `da5e43ff75385b9e013559e771306ccadbb9c28fb36d046520cc00696d037658`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the -1 sentinel at 0x00ba6dc5 reachable from this body? It is not, because this body's own guard diverts a null key and 0xffffffff is not null -- so a -1 key DOES reach 0x00ba6dc0 and gets its 0 back. Whether 0xffffffff is a meaningful value at +0x80 is unresolved.
- RETURN SEMANTICS: the canonical claim is the string 'Word' and the source span declares 'Word', so the arm agrees -- but the agreement is between a SOURCE-SIDE SPELLING and a MACHINE-FIXED WIDTH, not between two machine observations. abi_derived.value.abi.return_semantics is the register-class phrase `integral_in_EAX` and abi_derived.return.type is null, so no record for this VA supplies a C type, and a width-based oracle could not adjudicate this body in any case: the last value-producing instruction before both terminators is 0x00dd0569 CALL 0x00ba6dc0, and a CALL inside the body defeats evidence_returns' WIDTH state by design, because whether a caller may read EAX after a call is the CALLEE's signature and this listing cannot show it. So the residual question is exactly the one the record leaves open: which of the integral types of that four-byte word the original was written as. `Word` is one honest spelling and not a recovery -- a 32-bit pointer, a handle and a count are all 4 bytes and all `integral` in EAX, and the callee's own return is INFERRED (see return_semantics.value_meaning) to be a planet-record-shaped pointer without this body establishing that. Nothing here distinguishes them, and the declaration does not claim to.
- The ghidra_function.locals array claims three locals (param_1, iVar1, uVar2) and ghidra_parameter_count is 0 while the decompilation shows one parameter. The listing has no frame at all beyond the single saved ESI, so the machine record is preferred and the decompiler's locals are not modelled. What the decompiler's register allocation was tracking is not recoverable from this body.
- What class owns this method? It is an entry in four vtable tables (0x0147ca30, 0x0147ca70, 0x0147caf8, 0x0147cc14) but this package's evidence does not attribute those tables to a class, and the Spore-ModAPI SDK tree is absent from this environment, so no header could be read. Every member and type name here is therefore spelled by address.
- What is the concrete type of the object 0x00b3d2a0 returns, and what does 0x00ba6dc0 do with its receiver's +0xc8? Both callees are modelled as black boxes here. pkg01-roots already leaves DAT_0167eae4's publisher and the returned manager's type open, and nothing here settles either.
- What is the receiver's +0x80 word? The body only loads it, tests it and pushes it. The packed-index reading is INFERRED from 0x00ba6dc0's body, not from this one, and its name, width semantics and valid range are unestablished.
- Which of the four referencing tables is the live one for a given instance, and what is this method's slot index? Only the byte offsets read out of the tables are stated; the vtable header this package's evidence does not show would fix the index.
