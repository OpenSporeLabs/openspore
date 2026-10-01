# Validation 0x004df420

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dogfood-004df420-a1/dogfood_004df420_a1.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 12-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x004df420; 58 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x004df550; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 12-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field key_0a4) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 12-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c287a69a4d1c461bbdde2e5f48fb3fb9d9e3c95f9858f16d0ecac425a6198bad`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `062ce039e56e3724f4525795450a884257cffaacf90cbccb436c381862b0685c`
- Pack digest quoted by the briefing: `c287a69a4d1c461bbdde2e5f48fb3fb9d9e3c95f9858f16d0ecac425a6198bad`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation was captured, so no live receiver value, no live argument value and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.`, `The call sites were counted and classified from a static xref export. Which of them execute in a given play session, and with what receiver and key contents, is a runtime question this repository has no instrument for.`, `The unreachability result for the callee's key-substitution branch is static. Confirming it as an execution count needs an instrumented run of the original, which was not performed.`, `runtime validation not run`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the offsets the resolve family uses, +0x04 in 0x004df550, +0x44 in 0x004df440 and +0xa4 here, three fields of one object or anchors of three different sub-objects? The two resolve bodies are near-clones differing only in those offsets and in the constant passed to 0x004d3dd0, consistent with one template instantiated at several offsets, but no evidence here decides it.
- Are the three receiver-relative offsets the resolve family uses, +0x04 in 0x004df550, +0x44 in 0x004df440 and +0xa4 here, three fields of one object or anchors of three different sub-objects? The two resolve bodies are near-clones differing only in those offsets and in the constant passed to 0x004d3dd0, which is consistent with one template instantiated at several offsets, but no evidence here decides it.
- At 0x00d5d074 the returned dword is not consumed on the traced path while the other 57 direct call sites consume it. Is that call site a genuine discard of a value the original treated as void there, or is the value consumed on a path this listing window did not reach?
- How large is the real receiver object? The model covers receiver +0x00..+0xaf because that is all this body can touch. Nothing here bounds the object, and two callers of this target dereference the returned word at offsets far beyond 0xb0, so the object is certainly larger than the covered prefix. Where it ends is unresolved.
- How large is the real receiver object? The model covers receiver +0x00..+0xaf because that is all this body can touch. Nothing here bounds the object. This is a question about the RECEIVER, which is distinct from the value object behind the port's result: that one is bounded below at 0x80e bytes by 0x004d3dd0, and its upper bound is unresolved.
- Is the dead key-substitution branch reported for this caller really dead at run time, or is there a path into 0x004df550 that re-enters it after the entry test? The static proof covers the fall-through path from 0x004df550's entry to the gate, and 0x004df550 contains no loop and no second call to itself, but no original-process run was performed to confirm the execution count.
- No original-process invocation was captured, so no live receiver value, no live argument value and no live return value was observed. Every statement in this record is a static reading of the 3.1.0.22 image.
- The call sites were counted and classified from a static xref export. Which of them execute in a given play session, and with what receiver and key contents, is a runtime question this repository has no instrument for.
- The unreachability result for the callee's key-substitution branch is static. Confirming it as an execution count needs an instrumented run of the original, which was not performed.
- What is the chain-node layout of the callee's hash container? 0x004df6d0 and 0x004e0f80 agree on key at +0/+4/+8, value at +0xc and link at +0x10, while the insert path's 20 byte payload in 0x004e0560 is initialised two dwords later than the probe reads it. One of those two readings is wrong and resolving it needs 0x004e0560 reimplemented, which is outside this package's scope.
- What is the declared return type? The machine contract is a 4-byte value in EAX, and 0x00c02734 and 0x00aec396 dereference it at offsets 0x5b0 and 0x51c, which is consistent with a pointer, but no declared type is proven, so the model returns an opaque 32-bit word.
- What is the declared return type? The machine contract is a 4-byte value in EAX, the callee's hit path returns a container's mapped-value pointer and its miss path returns a freshly constructed object, and both observed dereference sites sit behind a null test. Pointer is consistent with all of that and none of it proves a declared type, so the model returns an opaque 32-bit word.
- What is the declared type, field name and role of the three words at receiver + 0xa4? The callee reads the block as three dwords, copies all twelve, null-tests word zero, and hashes words zero and two together while comparing all three. That fixes the width, the order and the identity role of word zero, and fixes no name and no declared type.
- What is the declared type, field name and role of the twelve bytes at receiver + 0xa4? 0x004df550 reads them as three dwords and copies all twelve, which fixes their width and order and nothing else. PKG-EDITOR-WAVE11 calls the same block fallback_0a4, but that is a sibling package's choice and is not evidence for this target.
- What role does the vtable slot at +0x0c of the object returned by 0x0067dcd0 play, and what is that object's type? Ghidra names the slot Initialize via a type guess against IGameModeManager; with no RTTI in the binary, no name is asserted, and the slot is recorded only as an unnamed predicate that gates the create path.
- Which C++ class owns the receiver, and is +0xa4 a member of that class or of a sub-object? SporeApp.exe carries no MSVC RTTI, so no class name is readable from the binary. The nearest preceding call at 55 of 58 direct call sites is the SDK-named accessor Editors::cSpeciesManager::Get at 0x00401090, which names the accessor and not the class of the object it returns.
- Which C++ class owns the receiver, and is +0xa4 a member of that class or of a sub-object? SporeApp.exe carries no MSVC RTTI. The nearest preceding call at 55 of 58 direct call sites is the SDK-named accessor 0x00401090, which names the accessor and not the class of the object it returns.
- Which parameter of 0x00f473a0 is the allocation size? 0x004df550 passes 0x13f0e00 and 0xa18; the forwarder reorders them and the allocator pair 0x009289f0/0x00927be0 was not read far enough to say. Until that is settled, 0xa18 is only consistent with the 0x80e lower bound and is not asserted as a size.
- Why do 0x004df420 and 0x004df400 each recompute receiver + 0xa4 rather than 0x004df420 calling 0x004df400? Both are separate functions in the image and neither references the other, so the original source most likely inlined the accessor at each site. That is a codegen reading, not an observed fact about the source.
- runtime validation not run
