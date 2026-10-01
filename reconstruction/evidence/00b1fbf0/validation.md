# Validation 0x00b1fbf0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-shared-default-true-wave12/b1fbf0_default_true.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x00b1fbf0; 17 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `99f94b431be6bf704c07e192b4fe404261e565d8c3d59f325f7753407f95afce`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `1016a723f590ab23a869696de3c1e430aed117d1b56feba7e217115a6b10fd09`
- Pack digest quoted by the briefing: `99f94b431be6bf704c07e192b4fe404261e565d8c3d59f325f7753407f95afce`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.`, `The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the address a compiler-folded COMDAT shared by many unrelated 'return true' defaults, or a single default deliberately emitted once? Both fit every observation.
- Is the always-true body a shipped default, a build-configuration stub, or a patch target at runtime? No differential trace has been captured for this function, so runtime patching cannot be excluded.
- No original-process trace has been captured for 0x00b1fbf0, so every claim here is static. A runtime differential test must confirm that the answer is still 1 in the shipping build and that no runtime patch retargets the address.
- The 0x00ee8860 virtual dispatch site must be observed with a concrete receiver before the slot's owning class can be named.
- The 356 and 20 vtable-reference counts are raw pointer-scan totals, not proven distinct vtables. The true count is unmeasured. A scan of the image's own .rdata for the little-endian dword of this address finds 521 occurrences, and .data finds 17; those are also raw totals and are not a table count.
- The Spore-ModAPI correspondence to IGameMode::func0Ch is a CANDIDATE for the 0x01485550 table only, recorded in sdk_correspondence and deliberately not asserted. Four offsets across three tables are why.
- The six ECX receipt sites establish that a value is in ECX at the transfer. They do NOT establish that the body reads it, and the record's R2 says it does not. Whether the six sites pass the same object or six different ones is not determinable from the call sites alone.
- What predicate is this? The body is a constant yes, but nothing in the observed evidence names the question it answers.
- Which class or classes own the slots that point here? Four distinct slot offsets across three distinct tables are recorded above and they cannot all describe one method.
- Why does caller 0x00a43050 and caller 0x0082c210 call the function and discard the answer? A constant with no side effects makes those calls no-ops in the observed build.
- __fastcall is a SECOND surviving candidate in the derived record (conventions.candidate_conventions names both it and __thiscall) and nothing observed here closes it. The reconstruction asserts __thiscall because that is what the record's calling_convention field says, not because the second candidate was refuted.
