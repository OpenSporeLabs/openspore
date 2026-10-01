# Validation 0x00580cb0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dogfood-00580cb0-a1/dogfood_00580cb0_a1.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 91-instruction listing name the same 11 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 12 outgoing call edge row(s) over 11 distinct address(es) for 0x00580cb0; the source span names 10 of them and no others |
| GLOBALS | `WARN` | `partial` | 5 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names field base_path, context, db_path, db_tmp_path and the machine evidence is the receiver's displacement bounds only, so the field's identity is not corroborated by it |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (91 of 91 instruction(s), 0 unparsed) and all 8 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 91-instruction listing lie inside the recovered body span 0x00580cb0..0x00580de2, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 91-instruction body names 6 indirect transfer(s): 0x00580d20 dispatches slot 0x0 through the table word in EAX; 0x00580d4d dispatches slot 0x20 through the table word in EAX; 0x00580d5e dispatches slot 0x18 through the table word in EDX; 0x00580dae dispatches slot 0x1c through the table word in EAX; 0x00580db7 dispatches slot 0x8 through the table word in EAX; 0x00580dd8 dispatches slot 0x4 through the table word in EDX; the machine parse consumed 91 of 91 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x0, 0x4, 0x8, 0x18, 0x1c, 0x20, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9100b51750e334d3d546eee5e841fb77ff418148bb7d001b67efaa2ba32c7451`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5e0fd32fa6ac033d548f09203936fb40d76f92403aca027254ef60050e95b654`
- Pack digest quoted by the briefing: `9100b51750e334d3d546eee5e841fb77ff418148bb7d001b67efaa2ba32c7451`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.`, `The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.`, `The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the element width of the three path buffers really 16 bits? The two formats are written with the count 0x100 and the buffers are measured exactly 0x200 apart, so each holds at most 0x100 elements of some width. Sixteen-bit units agree with the UTF-16 literals and with 0x00580c10's own 0x100, but this body does not prove the width independently.
- No original-process invocation was captured, so no live handle, no live path buffer contents and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.
- SETTLED in this attempt, removed from the open list: the frame reconciles exactly. See frame_geometry.unreconciled and frame_geometry.reconciliation. No runtime trace was needed; the prologue's two pushes had been left uncounted against the epilogue's two pops.
- The body is reached only through the table entry at 0x013f57f8 + 0x54, so its callers are indirect and cannot be enumerated from the binary. Whether it runs in a given play session, and with what receiver, is a runtime question.
- The narrow string "Casual" sits at 0x013f586c, immediately after the table's twenty-eight pointer slots. Is it a string constant the linker happened to place there, or is one of the slots a pointer that this analysis has misread? The four bytes at +0x74 are 43 61 73 75, which is "Casu" and not a plausible address, so the first reading is better supported, but the placement is unexplained.
- The null-handle path cannot be exercised without a filesystem that refuses the open, and the observable it would produce is a fault rather than a value.
- The table entry at +0x58 is 0x00580df0 and Ghidra reports no function there. Is that an entry this analysis has not yet created a function for, or something else? The other twenty-seven entries are code addresses, so the first reading is more likely, but it is unconfirmed.
- The three structural WARNs cannot be cleared by any source change. FIELDS/OFFSETS has no machine-derived struct layout to corroborate the 15 declared offsets; CONTROL FLOW states that CFG shape comparison is unbounded; EVIDENCE COVERAGE counts 12 of 16 because callers_dependencies, external_callees and contradictions are empty sets, which evidence.py:829 grades as unavailable. For this target the empty sets are the finding: it has no direct callers, no external callees and no recorded contradictions. The fourth, semantic_hypotheses, reads knowledgegraph/research/semantic-decomp.json, a shared canonical file this worker does not own, so it was left alone.
- What do 0x00692f90 and 0x00692900 do with the three arguments this body gives the first of them, the original receiver, the address 0x0150d100 and the constant 0x1a80d26? 0x00692900 walks a 0x14 byte element array at receiver +0x10 with a count at +0xa00 and a cursor at +0xa04, and it contains an INT3 at 0x00692ae5 on one error path, so the sink is a substantial object whose semantics belong to its own reconstruction.
- What is 0x0150d100? The body pushes the address once and never dereferences it, and the twenty-four bytes read there are zero. Which section it lies in was not determined, so whether it is a zero-initialised global that some other code fills is open.
- What is 0x01897c18? The body pushes the address three times and never dereferences it. The twenty-four bytes read there are a dword table whose entries rise in a constant stride of eight, which fixes an entry width and nothing else. It is passed as three of the constructor's four arguments, so it is plausibly a property descriptor rather than a data table, but the binary does not say.
- What is the declared return type? The machine forwards a 4-byte dword, and there are no direct call sites to measure how the indirect callers consume it, so the model returns an opaque 32-bit word.
- Whether the four data addresses should be link-time objects rather than literals. This attempt chose literals because the machine pushes addresses and the image cannot be linked, and because the choice is what lets the validator corroborate the constants. A relocation-based encoding is equally defensible and would restore the previous boundary-test rule at the cost of CONSTANTS and GLOBALS abstaining again. This is a modelling-preference question, not an evidence gap.
- Which C++ class owns the receiver, and is the body a method of it or of something it holds? The word below the table at 0x013f57f8 is zero, so there is no RTTI, and the body never dereferences its receiver. The six sibling entries that other packages have reconstructed and the entry at +0x1c are consistent with one class's virtual set, which is evidence about the table and not a class name.
- Why does the guard cover the commit block but not the tail? The bytes are unambiguous, so this is not a question about the reading. Whether a null result from 0x00688fa0 is reachable in a shipping session, and whether the unguarded dereference is a latent defect or a path that never runs, is a runtime question this repository has no instrument for.
- runtime validation not run
