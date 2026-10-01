# Validation 0x01053e00

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-01053e00/dfw_01053e00.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 65-instruction listing name the same 1 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x01053e00..0x01053ed3 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x01053e7f; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x01053e00; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; the data-reference artifact is read whole and records 0 reference row(s) out of this body, none of which is 1 of the address(es) under review (0x013f94d4), so those claims are unbacked by Ghidra's reference database rather than refuted by it |
| FIELDS/OFFSETS | `WARN` | `partial` | 7 source field-offset declaration(s) (displacement 0x114, displacement 0x124, displacement 0x34, field table_00) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (65 of 65 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 6 conditional branch target(s) in the complete 65-instruction listing lie inside the recovered body span 0x01053e00..0x01053ed3, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 65-instruction body names 6 indirect transfer(s): 0x01053e17 dispatches slot 0x2c through the table word in EAX; 0x01053e36 dispatches slot 0x4 through the table word in EAX; 0x01053e5c dispatches slot 0xb8 through the table word in EAX; 0x01053e6e dispatches slot 0x30 through the table word in EDX; 0x01053e7d dispatches slot 0x2c through the table word in EAX; 0x01053eb2 dispatches slot 0x38 through the table word in EAX; the machine parse consumed 65 of 65 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 6. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 5 vtable(s) nor the xref export's 1 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `b52c3ceda45e9fd3d9b0ebdd779161c4c18949cd88b8e3dc65b20ebf0f66fbe7`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `dd3bb4649c8edd4fae725792cf8be6ac729eadb1c04cd6cdd618530fd1907e15`
- Pack digest quoted by the briefing: `b52c3ceda45e9fd3d9b0ebdd779161c4c18949cd88b8e3dc65b20ebf0f66fbe7`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the 0x01053e27 store before 0x01053e36 an ownership transfer or a bug? The store zeroes the receiver's word while ECX still holds the pointer, so the release-shaped transfer at 0x01053e36 is reached through a receiver that no longer names the object. That is what the listing does and the model reproduces it. Whether it is intended cannot be settled from this body, and the sibling at 0x01053db0 was not consulted for intent -- only for the frame shape.
- Is the 0x01053e4d path -- a null word at 0x114 falling into a block that dereferences it with no test -- reachable in the original? The model reproduces the absence of the test and the model test does not enter that path. Whether any real caller can reach it needs a runtime observation, and this body has no recorded caller.
- The 12-byte buffer passed to the found object's vtable word at +0x30 is written by the callee but never read back by this body, which consumes the returned pointer instead. Whether that buffer is a genuine second output or a compiler artifact of the callee's prototype is not resolvable from this function alone.
- The commit helper 0x00cb5930 uses this function's own receiver word as a fallback pointer to three floats, which reads the first twelve bytes of the receiver object. That is what the listing does and it is staged verbatim, but it looks like an argument mix-up in the original; whether the caller ever reaches that fallback is unknown.
- The eight code pointers stored at 0x013f94d4 are recorded as observed bytes but are deliberately left unspecified in the staged table, so no constant is asserted that the listing for this VA does not contain.
- The function is unnamed in the image. FUN_01053e00 is the live Ghidra name, the Spore-ModAPI symbol table has no entry for this address, and the two SDK-named neighbours 0x01053d00 and 0x01053db0 are the only members carrying the cDefaultBeamTool this type. The class attribution is therefore evidence-based but the member or interface name is not recoverable and has not been invented.
- The semantic role of each dispatched slot is inferred from shape only: the +0x2c query on the owned target, the +0xb8 keyed lookup, the +0x30 and +0x2c position accessors and the +0x38 emitter setter. No slot body is resolved in this package.
- The slot index of this entry is not established. It sits five words after the SDK-named func4Ch word in the tables based at 0x0149b810, 0x0149b900 and 0x0149ba30, but those regions interleave non-code words and the image has no RTTI, so the deltas are reported rather than a slot number.
- What are the six dispatched slots? The record's own unresolved_questions says their roles are inferred from shape only. The model gives each a name built from its displacement and asserts nothing else.
- What are the three single-precision words copied at 0x01053e7f..0x01053ea2? MOVSS fixes that each is one 32-bit single-precision word at offsets 0, 4 and 8 of the pointer, and the model's type is named for that. Whether the three are a coordinate triple is not established by any record and is not claimed.
- What are the two receiver words at 0x114 and 0x124? No record for this target names a member at either displacement. The model reads 0x124 as a pointer because the body dereferences it, and 0x114 as a pointer for the same reason, and names neither.
- What does 0x00cb5930 do with the second callee-popped stack word? Its own listing reads three consecutive words from it and writes them at offsets 0x13c, 0x140 and 0x144 of its receiver, and only after first trying to replace the pointer through its receiver's word at 0x134. Reading a three-word block out of a stack word that this body reloads from its own frame looks like an argument mix-up in the original; the model test treats 0x00cb5930 as an observer, so nothing is asserted either way, and whether the caller ever reaches that fallback is unknown (this body has fan_in 0).
- What is the 12-byte frame buffer at [ESP+0x10] that 0x01053e67 forms and hands to the +0x30 slot? The body never reads it back -- it consumes the callee's EAX instead -- so whether it is a genuine second output or an artefact of the callee's prototype is not decidable from this body. The model passes it and does not look at it, and the model test proves the non-read by having the observer fill it with different words.
- What is the table at 0x013f94d4? The bridge reads eight consecutive words there and all eight are code-range addresses. They are recorded in this sidecar as observed bytes; no value is asserted in the model and no record names the table.
- Whether the second callee-popped stack word is a distinct 4-byte argument or the low half of a single 8-byte argument cannot be decided from `ret 8` alone. No instruction reads it, so it is staged as an opaque void* and never dereferenced.
- Which slot of the four associated tables does this entry occupy? It sits five words after the SDK-named func4Ch word in the tables based at 0x0149b810, 0x0149b900 and 0x0149ba30, but those regions interleave non-code words and the image has no RTTI, so the delta is reported and no slot number is claimed.
- Why does the derived ABI record call the return register XMM0? abi_derived.return names XMM0 with register_class float_or_x87 and confidence APPROXIMATION, on the strength of the MOVSS instructions in the body. Both return paths set AL explicitly and no path writes XMM0 after 0x01053ea2, so the byte in AL is the return value. The record's XMM0 is reported and not adopted; the persisted record's AL and bool are what the model returns, and the RETURN SEMANTICS check compares the source against the persisted record.
