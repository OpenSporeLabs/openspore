# Validation 0x00d00a10

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00d00a10-clamp-scalar-to-range/clamp_scalar_to_range_00d00a10.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `FAIL` | `partial` | source convention ['thiscall'] conflicts with persisted stdcall |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 20-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00d00a10; 43 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00d05a20; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 20-instruction listing names 2 data address(es) (0x01478d5c, 0x01478d60); the data-reference artifact is read whole and records 2 reference row(s) out of this body covering every address under review, with access mode(s) read=2 |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 20 of 20 instruction(s) consumed, degraded=True, unparsed=2 |
| CONTROL FLOW | `PASS` | `complete` | the complete 20-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 20-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `72205718477ce65c0b860e162b4f013f03c1c38d8bb36c7bddbb94037e7893ab`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `bf542ba9df98ace2a73724f197d33eba5231d24073ef9d8157e913271fd51000`
- Pack digest quoted by the briefing: `72205718477ce65c0b860e162b4f013f03c1c38d8bb36c7bddbb94037e7893ab`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `confirm whether the two .rdata bounds are patched at run time, which would make the clamp range dynamic and would justify reading them per call rather than as constants`, `execute the wrapper under a real evaluator (0x00d05a20) rather than the model test's stub, which is the only way to see the clamp engage on values the game actually produces`, `observe one real caller long enough to record what the three forwarded words carry and what the clamped quantity represents, which would settle the undefined4 typing this package declines to guess`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- NO RUNTIME EVIDENCE EXISTS. Nothing in this repository has run the original process for this target, so the model test is a static model of the listing and not a differential test against the game. The runtime gate is open and nothing was attempted.
- THE CALLEE IS A SEPARATE TARGET AND IS NOT RECONSTRUCTED. 0x00d05a20 is 279 instructions and this package models only its ABI. In particular the model test SUPPLIES the evaluated value rather than deriving it, so the clamp is measured against a controlled input and not against the real evaluator. Any claim about what the clamped quantity represents -- a distance, a ratio, a score -- would have to come from that target.
- THE GLOBAL CHECK IS WARN, NOT PASS, AND THAT IS CORRECT. validation.md reports GLOBALS at partial coverage because the data-reference artifact records 2 reference rows for this body against the 2 addresses the listing names, which is complete for the body; the residual WARN reflects that the artifact is read whole rather than sliced to this span. The CONSTANTS check is likewise WARN with degraded=True and unparsed=2, while the disassembly category itself lists all 20 instructions with no parse failure -- the two unparsed lines are counted against the ABI grammar, not against the listing, and the 85 bytes were re-read from memory to confirm the listing is complete.
- THE RECEIVER CONVENTION IS NOT SETTLED BY THE CALLEE UNDER RECONSTRUCTION. The derived ABI record's inference R2 says ECX is never read in any form, and abi_derived.receiver is null, so the machine-derived receiver evidence is EMPTY. This package does not override that abstention with a class name; it declares an opaque first parameter on the strength of three other observations (the callee's `MOV EDI,ECX` prologue, and two call sites that load ECX immediately before the call) and records the limitation in observed_original_abi.calling_convention_alternatives. A reviewer who wants the weaker reading can restate the prototype as __stdcall plus an unnamed ECX passthrough without changing the body.
- THE THREE FORWARDED WORDS ARE UNTYPED, AND THEIR ORDER IS CLAIMED ONLY AS AN ORDER. The evidence gives them size 4 and nothing else, so this package types them uint32 and asserts ordinal-to-ordinal forwarding. Whether ordinal 1 is a count, an index, a handle or a bitfield is not determined here, and the model test's distinct sentinels deliberately test only the mapping.
- confirm whether the two .rdata bounds are patched at run time, which would make the clamp range dynamic and would justify reading them per call rather than as constants
- execute the wrapper under a real evaluator (0x00d05a20) rather than the model test's stub, which is the only way to see the clamp engage on values the game actually produces
- observe one real caller long enough to record what the three forwarded words carry and what the clamped quantity represents, which would settle the undefined4 typing this package declines to guess
