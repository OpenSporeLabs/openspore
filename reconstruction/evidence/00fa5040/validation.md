# Validation 0x00fa5040

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-sporepedia-dual-00fa5040/sporepedia_dual_00fa5040.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 297-instruction listing name the same 5 direct transfer target(s); 3 intra-procedural jump(s) target inside the recovered body span 0x00fa5040..0x00fa542e are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00fa5140, 0x00fa51bd, 0x00fa53b2; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 7 outgoing call edge row(s) over 5 distinct address(es) for 0x00fa5040; the source span names 5 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 297-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00fa5040; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 297-instruction listing nevertheless reaches 4 receiver displacement(s) through ECX (0x770, 0x774, 0x784, 0x788), all of which the record accounts for or the listing is the better witness on; the 297-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=297, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 4 displacement(s) to the receiver as proven (0x770, 0x774, 0x784, 0x788) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x770, 0x774, 0x784, 0x788), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (297 of 297 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 39 conditional branch target(s) in the complete 297-instruction listing lie inside the recovered body span 0x00fa5040..0x00fa542e, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 297-instruction body names 1 indirect transfer(s): 0x00fa536a dispatches slot 0x0 through the table word in EAX; the machine parse consumed 297 of 297 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9c7ae2db35920bfe2429685c030caf956eb2c1b1ffb7b93b39dbf11aa3a368d8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `aadf2609edbbf6efda59b6941354f4a4607f91140a854a2b55397611cf241f07`
- Pack digest quoted by the briefing: `9c7ae2db35920bfe2429685c030caf956eb2c1b1ffb7b93b39dbf11aa3a368d8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none for this target. Every claim in this package is from the disassembly listing, the machine-derived ABI record and the bytes the listing quotes.
- NO RUNTIME EVIDENCE. No trace of 0x00fa5040 running in the original binary exists in this repository, so nothing here is differentially validated and nothing here claims to be.
- THE CALLING CONVENTION. The record determines none: null, UNKNOWN, four candidates, ABI_UNKNOWN, three abstentions. __thiscall is the shape the receiver in ECX plus a callee that pops 8 bytes would suggest, and it is exactly the claim this package declines to make, because the record does not make it and the C11 abstention is specifically about the offsets that would settle it. The reconstruction therefore declares no convention token, and its own C++ linkage is a property of the model and not a claim about the original.
- THE PACK/UNPACK LOSSY ROUND TRIP ON THE SECOND-ARRAY PATH. 0x00fa5313..0x00fa531a packs (group << 0x18) | slot into one word and 0x00fa531e..0x00fa5332 unpacks it with SHR 0x18 and AND 0xffffff. If a slot index ever reached 0x1000000 the OR would corrupt the group half, and the machine would then compare against the wrong sub-table. The reconstruction models the round trip as lossless, which is right for every slot index a 32-bit object array can actually hold in practice and is not claimed to be a proof about the machine's behaviour at that boundary.
- THE RECEIVER WRITTEN-THROUGH CONTRADICTION. receiver.written_through is 0, but the complete listing stores to the receiver's own words at 0x00fa5227 and 0x00fa541b. The record attributes the reaches to ECX while the body addresses them through EBP after MOV EBP,ECX, so the record's zero is very likely an artefact of that alias rather than a statement about the body. The listing is the better witness and this package follows it; the record is not edited.
- THE RECEIVER'S IDENTITY AND LAYOUT. ECX carries a receiver at INFERRED confidence and the body reaches 0x770, 0x774, 0x784 and 0x788 through it and 0x218, 0x268, 0x38, 0x4, 0x8, 0xc, 0xac and 0xb8 inside it. The machine supplies NO name, class, type, field, size or member for any of them, the record's bounds_only says its own enumeration is open, and this binary carries no MSVC RTTI. None is claimed. Whether the receiver is a pointer at all, whether the two arrays are two arrays of one type, and what a 0xac-byte element is, are all open.
- THE RETURN REGISTER CONTRADICTION. abi_derived.return names XMM0 at APPROXIMATION confidence and RT1 justifies it by the mere presence of an SSE instruction in the body; the complete listing shows XMM0 is scratch for eight COMISS comparisons and that the last write before each of the two terminators is a one-byte write to AL. This package reads the listing and says so, and the contradiction is left visible: a reader who trusts RT1 will get a different answer and should know which of the two is contradicted by which evidence.
- THE SECOND STACK SLOT. This package calibrates two ordinary stack words; the record enumerates one. The calibration is the frame arithmetic and it agrees with the record on the slot the record can name, and the observed two-word pop is consistent with it, but the record's own instrument declined to calibrate and its single-slot entry is kept visible in the header (kRecordObservedStackArgumentSlots). What the second word IS -- a separate argument, a flag, the low byte of something wider -- is not determined, and only its low byte is read.
- WHAT 0x00f9f620's ARGUMENT CLEANUP IS. The body pushes a cursor word and never adjusts the stack for it, so the word is dropped by the callee or by whatever the callee does; the machine's own cleanup observation for THIS target is about this body's own terminator and says nothing about that call's. Not determined.
- WHAT THE 0x00fa536a DISPATCH IS. The body performs a two-level table load through an object's own first word and calls it with the immediate 1. Whether that word is a vptr, a function pointer to a table, or something else is not established here; the machine classifies the site as a vtable-slot-shaped two-level load and that is all that is claimed. No class, no table type and no slot identity is named.
- WHAT THE FIVE DIRECT CALLEES ARE. 0x00fad140 (writes a four-float scratch and has its result read as a single byte, whose zero-ness is all that is used), 0x00fa29b0 (one word, no result read), 0x00f9f620 (base plus cursor, no result read), 0x00fadac0 (one register, no result read) and 0x004558a0 (two words, no result read) are all unnamed in the image, all modelled here as observers, and none of them is owned by this package. Their internals are outside these 297 instructions and are not guessed.
- WHAT THE TWO ARRAYS ARE. Same shape, same stride, same key displacement, same six-record block, and two completely different payloads on a hit. Nothing in this body says what an element is, what the key identifies, what the four floats are, or why one array notifies and the other releases.
- WHETHER THE SUB-TABLE ENDS AND THE ARRAY ENDS CAN DISAGREE. The array tails stop the cursor walk on EQUALITY against the end word and the sub-table walks use a signed shift of (end - begin); both are read exactly as the machine reads them, and both assume the two ends are consistent with the stride. A receiver whose end word is off the stride grid makes the machine's own tail loop non-terminating, and this reconstruction reproduces that rather than guarding it -- the fixtures keep every end on the grid and say so.
- WHY THE FRAME POINTER ABSTENTION BLOCKS THE ABI ARM. The validator's ABI arm returns WARN on a derived record whose verdict is ABI_UNKNOWN, before it reads anything about the source. That verdict is a property of the pack, not of this package: no source can turn it into a PASS, and the only ways to do so would be to edit the evidence pack, edit tools/reconstruction_tooling/abi_infer.py, or weaken the check. None was done. The seven other structural checks are adjudicated against the source and the machine and are reported by the validation report in full.
