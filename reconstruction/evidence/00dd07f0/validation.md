# Validation 0x00dd07f0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00dd07f0/sw2_00dd07f0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 68-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00dd07f0; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 68-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares 3 displacement(s) (0x84, 0x88, 0x8c) and every one of them is a displacement the complete 68-instruction listing shows: 1 attributed to the receiver ECX as proven (0x8c); 2 more (0x84, 0x88) are grounded in the machine-derived receiver record rather than in the scan; the 68-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=68, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x8c, 0x98) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x84, 0x88, 0x8c, 0x98), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x84, 0x88) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (68 of 68 instruction(s), 0 unparsed) and all 8 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 68-instruction listing lie inside the recovered body span 0x00dd07f0..0x00dd08f1, so the branch graph is closed inside it; the source span declares if, switch, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 68-instruction body names 3 indirect transfer(s): 0x00dd084b is INDIRECT_NON_VTABLE; 0x00dd085b is INDIRECT_NON_VTABLE; 0x00dd08a3 is INDIRECT_NON_VTABLE; the machine parse consumed 68 of 68 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3, so the dispatch is visible in the machine listing but is not proven: 3 of the 3 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x00dd084b, 0x00dd085b, 0x00dd08a3), so the dispatch's identity is not established: the target is the memory operand [ECX*0x4 + 0xdd08f4], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d8f785e6a65eadd3240748c2a2f94c3d310c7574c5aeb3a9adcc0dd32080136e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `292c9198387b1323beb28edef90887f8aeda3029ca8a0341ed2703d92a7c39c5`
- Pack digest quoted by the briefing: `d8f785e6a65eadd3240748c2a2f94c3d310c7574c5aeb3a9adcc0dd32080136e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00401090's identity. Ghidra names it Editors::cSpeciesManager::Get, whose SDK signature takes an editor pointer, but its four instructions read no stack slot and no argument register and simply return the data word at 0x015d0c24. Either the thunk at 0x00401090 is not the SDK function of that name, or the SDK function was specialised to a no-argument accessor. Nothing in the 68 instructions or the 10 callee bytes settles it, and this package models only the signature.
- 0x00dd0801 and 0x00dd0820 load the SAME dword of the SAME level-1 object, and the model reads it once. No branch, call or store lies between the two loads on any path, so a reconstruction that loaded it twice is not distinguishable from this one on any input this function can be given -- there is no observable difference to assert, and the two reads are reported here rather than resolved.
- Nothing in the 68 instructions says what any of the words MEANS. The seven stored values are not named, the three receiver words are not named, 0x53dbcf1 is not called a tag, and 0x00dd0816's 3 is not called progress. The bounds_only receiver record is the direct reason no member is declared, and the two-level chain plus the two table families are the reason the shape is what it is -- but a name for any of them would be a story the listing does not carry.
- RETURN SEMANTICS: the record's return_semantics is 'unclassified_in_EAX' and RT2 classifies the last EAX write as aggregate_unknown. This package declares void, which is what the LISTING says and what Ghidra's own decompilation emits, and it records the disagreement here rather than declaring a typedef named after the machine phrase. There is no C++ type that equals 'unclassified_in_EAX'.
- There is NO null test on the level-2 pointer. 0x00dd07f9 tests the level-1 word at receiver+0x98 and 0x00dd07fb leaves on it being zero, but nothing tests [level1+0xc]. A caller that hands this body a non-null link whose +0xc word is null faults at 0x00dd0804. The model reproduces that (it does not test it either) and the model test does not construct the case, because doing so would fault rather than refute. Whether the original relied on a caller-side invariant is not in the listing.
