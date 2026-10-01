# Validation 0x00d00a70

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00d00a70-scalar-threshold-band/scalar_threshold_band_00d00a70.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 58-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00d00a70; 58 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00d05a20; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 58-instruction listing names 2 data address(es) (0x01478d5c, 0x01478d60); the data-reference artifact is read whole and records 2 reference row(s) out of this body covering every address under review, with access mode(s) read=2 |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 58-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either; the machine-derived receiver record does enumerate 4 displacement(s) (0x10, 0x14, 0x18, 0x1c), which it observed through a register alias rather than through that register's own operands, so the scan is the narrower of the two witnesses here |
| CONSTANTS | `WARN` | `partial` | the machine listing is not fully parsed: 58 of 58 instruction(s) consumed, degraded=True, unparsed=2 |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 58-instruction listing lie inside the recovered body span 0x00d00a70..0x00d00b35, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 58-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `31b7dad7c244051b7cd22d740f3c33a360f33f344cfaad54d15495b9d29ce7f1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `bb89f6bb8d778783e4dd3beaafb2393eb88e31dae41dfd460d564075bbfd2bd2`
- Pack digest quoted by the briefing: `31b7dad7c244051b7cd22d740f3c33a360f33f344cfaad54d15495b9d29ce7f1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `establish whether the two clamp bounds at 0x01478d5c/0x01478d60 are constants for the whole subsystem or are shadowed per instance at run time`, `observe a write to receiver+0x10..0x1c to establish what calibrates the four edges, and whether the calibration is per-receiver or shared`, `read enough of the 42 call sites to find the index's consumer: a site that stores the result to a word and later compares that word against a small constant would identify what the five bands mean`, `run the original under a trace with the four receiver edges set to distinct, recorded values and confirm the five band answers, which would turn the arithmetic partition from a transcription into an observation`, `run the original with one of the four edges set to a NaN and confirm the band answer, which is the case this package can only trace from COMISS's documented flag behaviour`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- NO RUNTIME EVIDENCE EXISTS. Nothing in this repository has run the original process for this target, so the model test is a static model of the listing and not a differential test against the game.
- THE CALIBRATION OF THE FOUR EDGES IS NOT OBSERVED. Nothing shows what sets 0x10..0x1c, whether they can be re-tuned at runtime, and whether they are per-receiver or shared. The clamp bounds at 0x01478d5c/0x01478d60 ARE constants in the data section, but that says nothing about the four edges.
- THE DERIVED ABI RECORD'S RETURN_REGISTER IS WRONG AND THE PACK DOES NOT SAY SO. It says ST0. The listing says EAX, and this package's header documents the disagreement, but the persisted `conflicts` array in evidence.json is empty and `records/0x00d00a70` in reconstruction/knowledge/index.json still carries the ST0 claim. An integrator reading the index rather than the header would inherit it.
- THE UNORDERED CASES ARE TRACED, NOT MEASURED. The five band answers under an unordered receiver float are derived from COMISS's documented flag behaviour and are asserted against the reconstruction's helpers, not against the original process. A trace of the original under a NaN edge would settle them.
- WHAT THE FOUR RECEIVER FLOATS ARE IS UNKNOWN, AND IT IS THE QUESTION THAT WOULD NAME THE FUNCTION. They are four compared edges on a receiver this body shares with 42 call sites, and nothing in this package's evidence writes them or shows a caller reading the answer back into them. The band partition in `semantic_findings` is therefore a description of the arithmetic, not a claim about a domain.
- WHY THE RESULT IS AN INDEX RATHER THAN A VALUE IS NOT SETTLED HERE. Five ordered bands over a clamped scalar is a natural shape for a quantiser, a difficulty band or a simulation-state selector, and this evidence distinguishes none of them. The 42 call sites would: a site that stores the result to a word and later compares that word against a small constant would identify the index's consumer. This package reads two call sites and does not claim the rest.
- establish whether the two clamp bounds at 0x01478d5c/0x01478d60 are constants for the whole subsystem or are shadowed per instance at run time
- observe a write to receiver+0x10..0x1c to establish what calibrates the four edges, and whether the calibration is per-receiver or shared
- read enough of the 42 call sites to find the index's consumer: a site that stores the result to a word and later compares that word against a small constant would identify what the five bands mean
- run the original under a trace with the four receiver edges set to distinct, recorded values and confirm the five band answers, which would turn the arithmetic partition from a transcription into an observation
- run the original with one of the four edges set to a NaN and confirm the band answer, which is the case this package can only trace from COMISS's documented flag behaviour
