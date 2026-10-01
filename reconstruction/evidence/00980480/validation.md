# Validation 0x00980480

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-00980480/dfw_00980480.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00980480; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ee7894d03ba772093098709cade4c4c954cb4ec4b28a2663e3d728157cf5d52f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `f10f9792a4938c4f8f789c000a08f8deb53f252b61dae06c7b7db42e41a8cf09`
- Pack digest quoted by the briefing: `ee7894d03ba772093098709cade4c4c954cb4ec4b28a2663e3d728157cf5d52f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- 0x00950eb0 returns receiver+0x04 for the class ids of Object and ILayoutElement but null for IWinProc, which is the primary base of PerspectiveEffect at +0x00. That ordering is unexplained by the observed instructions alone and is the strongest single reason the type-id reading above stays a hypothesis.
- Duplicate coverage: reconstruction/staging/pkg-utfwin-perspective-wave12/ still reconstructs this same VA and is RETAINED, deliberately. The earlier version of this question also claimed the validator 'can only see the one the index record names' and therefore could not see this package; that consequence was wrong and is withdrawn. The index record lists this package's .cpp before the wave12 one, so the validator grades this package, as the 2026-09-29 run confirms. What remains open is an integrator decision only: two staging candidates for one VA cannot both be the source of truth, and which one is promoted to src/ is not a worker's call. Neither package was modified to resolve it.
- The SDK and Ghidra both type this symbol as `bool HandleUIMessage(IWindow *pWindow, Message *message)`, but the tail callee pops exactly one stack word (RET 0x4 at 0x0098034b and 0x00980350) and answers with a pointer or with null rather than a normalised byte. Either the SDK signature is a documentation-only entry or the Ghidra symbol at 0x00980480 is attached to the wrong body; the machine cannot distinguish a two-word caller that also reclaims the second word from a one-word signature. The machine cannot distinguish these, so the model follows the machine and the reconstruction is a PARTIAL claim, not IMPLEMENTED. This worker did not resolve it and did not paper over it.
- The SDK symbol table types this virtual as `bool HandleUIMessage(IWindow *pWindow, Message *message)` while the tail callee pops exactly one stack word (RET 0x4 at 0x0098034b and 0x00980350) and returns a pointer or null rather than a normalised byte. Either the SDK signature is a documentation-only entry or the Ghidra symbol at 0x00980480 is attached to the wrong body; the machine cannot distinguish a 2-word caller that also reclaims the second word from a 1-word signature. The reconstruction follows the machine and is therefore a PARTIAL, not an IMPLEMENTED, claim.
- The class id 0xef865d7e, the one word 0x00980330 answers with receiver+0x0c, has no entry in the SDK ObjectTYPE enum, so the interface it selects is unidentified.
- The class id 0xef865d7e, the one word the tail callee compares and the one word it answers, has no entry in the SDK ObjectTYPE enum, so the interface that value selects is unidentified. It is a property of the callee, not of this body, and no claim is made about it here.
- The vtable slot that reaches this thunk is unverified. The briefing associates vtable 0x01443f2c with the target and the address is stored in .rdata at VA 0x01443f68, but this worker did not establish a vtable start or a slot index, so no slot offset is claimed.
- What are the four bytes at 0x00980480? The body is a cross-vtable adjustor thunk by shape, and the sibling thunk at 0x00980470 subtracts a different amount, but no record for this target says what the four bytes address. They are modelled as a machine displacement on the address, with no class, no sub-object name and no interface name attached to them.
- What is the returned word? The tail callee answers with receiver+0x0c or zero. Nothing in any record for this target names the object at that displacement, so the model returns the word under the record's own opaque type and says nothing further about it.
- Which virtual reaches this thunk, and through which slot? The address is stored as a dword at 0x01443f68, and the triage classifier associates the target with vtable:0x01443f2c, but the same record reports vtable_reference_count 0 while the body has no indirect transfer of any kind. No vtable start and no slot index were established, so no slot offset is claimed and none appears in the model. This question is carried forward unchanged from the pre-existing record rather than answered here.
