# Validation 0x006a2e20

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-006a2e20/dfw_006a2e20.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 65-instruction listing name the same 4 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x006a2e20..0x006a2ee5 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x006a2ed1; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 5 outgoing call edge row(s) over 4 distinct address(es) for 0x006a2e20; 3 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 4 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 65-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 4 displacement(s) the source span declares (0x18, 0x1c, 0x2c, 0x34) and the 0 the complete 65-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x18, 0x1c, 0x2c, 0x34), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (65 of 65 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 65-instruction listing lie inside the recovered body span 0x006a2e20..0x006a2ee5, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 65-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 14 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 14 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7382047a39c1498ddd5c2dd960365ae3f8daf18a58b87210bd7ba95a12731c37`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `7b1ffa4788e50a155d046b9f2f332ab442a8376ab6cd623c36156f44d7189fb4`
- Pack digest quoted by the briefing: `7382047a39c1498ddd5c2dd960365ae3f8daf18a58b87210bd7ba95a12731c37`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x0093db80 is handed the seed entry at entry_esp-0x24 while that routine reads its receiver's words at +0x10 and +0x12, which inside a 0x18-byte entry address the Property's +0x0c and +0x0e words rather than its flags and type. With argument 0 the routine returns before using either, so nothing in this body distinguishes the two readings, but the receiver type does not match what the callee expects and the reason is not established.
- Behaviour of the slow assign path 0x00542c30 and of the unreconstructed callers 0x00bed460 and 0x00bed920 was not analysed.
- Is the search at 0x00612db0 always a lower_bound on the leading dword? Its body computes the count as (last-first)/0x18 and compares the leading dword unsigned, which is a lower_bound. Whether 0x006a2c50's copy of that call can dispatch to a different overload with a different comparator is not established by any record in this repository.
- No record names what the receiver's word at +0x34 counts. It is incremented exactly once per call on every path of this body, which makes it a call counter for THIS function at least; whether anything else in the class reads it, and whether the sibling bodies at 0x006a2ef0 and 0x006a2b80 increment the same word, is not established here.
- Semantics of the 8-byte {iterator, inserted} record are known but its value is discarded here, so no caller-visible use of it was found.
- The 4-byte slot at entry_esp-0x2c is written 0 before the 0x006a2c50 call and 0xffffffff after it, mirroring the SEH trylevel at entry_esp-0x04 from two frames away. It behaves like a compiler-kept active flag for the same __try scope, but nothing observable in this body reads it back, so its role is inferred rather than proven.
- The CONSTANTS WARN cannot be lifted by a reconstruction worker: the unparsed line is the toolchain listing grammar's missing JC synonym for JB, and that grammar lives in tools/**, which is out of scope. The instruction itself is reproduced in the source and its semantics are stated above.
- The exception filter at 0x0120d6b8 and the exact cleanup handler 0x006a2e20 relies on were not identified; only the frame install and teardown are observed.
- The frame disagrees with the one the prior session recorded. That session's validation.md places the 0x006a2c50 arguments at entry-0x30 and entry-0x24, the 4-byte state word at entry-0x2c, and 0x0093db80's receiver at entry-0x2c, and calls the state word a mirror 'two frames away' from the try level. The byte walk in this package puts the seed ENTRY at entry-36 and the OUT RECORD at entry-44 (the opposite assignment to the prior session's), the state word at entry-4 itself (the try level's own slot, which is what the MSVC trylevel encoding is), and 0x0093db80's receiver at entry-32. The two independent corroborations in mechanics.frame_resolution both only hold under this walk. I could not re-run the prior session's arithmetic and it is not my file, so this is reported as a disagreement rather than a correction.
- The map mode byte at receiver+0x2c is passed to 0x00612db0 and read by 0x006a2c50 at map+0x14, but the recovered 0x00612db0 overload does not vary its comparator on it, so what selects a different comparator is unresolved.
- This VA now has TWO metadata sidecars and TWO staging packages: this one and reconstruction/metadata/pkg-proplist-setprop-w15/006a2e20.json. reconstruction_knowledge.extract_metadata merges source_files per VA and sorted_unique()s them, and validate._source() returns the first existing staging path, so `pkg-dfw-006a2e20` sorts before `pkg-proplist-setprop-w15` and the validator now resolves THIS package's source for 0x006a2e20. The prior package's own recorded validation results therefore no longer describe what the validator reports for this VA. That is a property of the index, not an edit to either package, and it is the integrator's call which one to keep.
- What is the 4-byte word at entry-4? It is the slot `PUSH -0x1` fills and the body's only two writes to it (0 at 0x006a2eaa, 0xffffffff at 0x006a2ebc) bracket the 0x006a2c50 call, which is the standard MSVC try-level encoding for entering and leaving a __try scope. Nothing in this body reads it, and neither the handler at 0x0120d6b8 nor the cleanup body that must exist for the counter increment to be exception-safe has been identified.
- What selects a different comparator is not established. The byte at the receiver's +0x2c is passed to 0x00612db0 as its fourth word and 0x006a2c50 reads the same byte as its object's +0x14, but the recovered 0x00612db0 never reads its fourth slot. Either the word is for a different overload of that address or the comparator selection happens somewhere this body does not show.
- What the 8-byte out record is FOR is not established. Its semantics are known from 0x006a2c50 (iterator, inserted) but this body discards it, so no caller-visible use was found and the model keeps it as a write-only local.
- Why does 0x0093db80 get a receiver that this body has just tested and found flagged, and then get argument 0? With argument 0 the callee's clearing half does not run, so the call is a report whose result this body ignores. Whether the report is load-bearing (an out-of-line handler) or vestigial is not established here.
