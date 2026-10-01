# Validation 0x00577310

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00577310/w2_00577310.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 147-instruction listing name the same 5 direct transfer target(s); 2 intra-procedural jump(s) target inside the recovered body span 0x00577310..0x005774e6 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0057734f, 0x0057745d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 10 outgoing call edge row(s) over 5 distinct address(es) for 0x00577310; the source span names 5 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 147-instruction listing names 2 data address(es) (0x13eb430, 0x150cdd4) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 147-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x308), all of which the record accounts for or the listing is the better witness on; the 147-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=147, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x308) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x308, 0x30c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x30c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (147 of 147 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 14 conditional branch target(s) in the complete 147-instruction listing lie inside the recovered body span 0x00577310..0x005774e6, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 147-instruction body names 7 indirect transfer(s): 0x00577363 dispatches slot 0x0 through the table word in EAX; 0x00577376 dispatches slot 0x4 through the table word in EAX; 0x00577413 dispatches slot 0x4 through the table word in EAX; 0x00577429 dispatches slot 0x2c through the table word in EAX; 0x00577471 dispatches slot 0x0 through the table word in EDX; 0x00577484 dispatches slot 0x4 through the table word in EDX; 0x005774de dispatches slot 0x4 through the table word in EDX; the machine parse consumed 147 of 147 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 7. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `8d5d44cf78322155e3cd9f7d19dcec7d0b1f639a947634ba924703871a26869c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `76082de687fb9630dfaeba8b87779c6cc2e0d90a10ff39bc36454fafb5d71ecb`
- Pack digest quoted by the briefing: `8d5d44cf78322155e3cd9f7d19dcec7d0b1f639a947634ba924703871a26869c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No direct caller of this body is named anywhere. Its only reference in the binary is the data word at 0x013f5840, so the argument at entry_ESP+0x4 and the 0xffffffff sentinel are fixed by the body's own comparison and by nothing that calls it. What the sentinel means to the caller -- "no subject", "destroy", "reset" -- is not established.
- The block at 0x00577406..0x00577413 is dead in this body and this record explains why, but WHY the compiler emitted it is not settled. 0x007b1e90 contains the identical idiom in the identical order, which makes it a template artefact rather than a mistake; whether some sibling in the table at 0x013f57f8 reaches it is not known, because none of those bodies was read.
- What the receiver's two members ARE is not established. 0x308 is guarded for null and carries three registrations; 0x30c is unguarded and carries one, only on a yes answer. Nothing read here says what either points at, and the record is bounds_only so no member may be named. Whether they are the same kind of object that the factory happens to return, and whether the +0x308 guard is a deliberate one-shot initialisation or an accident of a template, is not settled.
- What the record's middle word, 0x510a95b, is for. It is written on all four registrations and 0x007b1e90 never reads it, so it is consumed by something further downstream (0x007b1e90's own follow-up call at 0x007b1f11 to 0x007b1de0 receives the same record pointer and is the obvious candidate) that was not read here. The model treats it as opaque and claims nothing.
- What the three record ids 0x8104e4b0, 0x9d1fcc2f and 0x7d708f46 are. They are 32-bit hashed strings, the standard shape for this binary's property vocabulary, and the factory is handed the class name "Editor" -- but no record in this repository maps any of the three to a name, and the preimages were not searched for.
- Whether the query's second argument is meant as a float. The cell at 0x0150cdd4 holds 0x3f800000, which is exactly the IEEE-754 single 1.0f, and 0x007b1e90's own record handling compares a record word against a value in the same neighbourhood. That is suggestive and is NOT a claim: nothing read here declares the parameter's type, and the model forwards the word as a word.
- Whether the return value is genuinely void. The decompiler says void, the persisted Ghidra record says undefined, and the machine-derived record says unclassified_in_EAX. This package declares void on the strength of the three inconsistent EAX values at the three epilogue entries, and that inference is a reading of the listing rather than a record. A caller that consumed the EAX word would make the reconstruction wrong, and no caller is named by any record for this VA.
- Why the second member is not guarded the way the first is. The two swaps are byte-for-byte the same sequence apart from the displacement, yet the first is entered on a null test and the second is entered on the query's answer. Something outside this body must decide whether the second swap is ever needed twice; nothing in this body does.
