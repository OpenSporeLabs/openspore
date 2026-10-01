# Validation 0x0059c740

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-gameglobal-b03/59c740_map_get_or_create.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 51-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 51-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4, 0xc), all of which the record accounts for or the listing is the better witness on; the 51-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=51, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4, 0xc) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0xc, 0x10, 0x1c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x10, 0x1c) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (51 of 51 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 51-instruction listing lie inside the recovered body span 0x0059c740..0x0059c7ba, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 51-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `c2b4ff5bdacde3a6cd95fb020a191c681022f52186ea7319d4ed1f7d3df6ce98`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `cc69eacf2da1e1f6aa7f08e46b9b20b7e568e45b8b2d40350989831a09fa5241`
- Pack digest quoted by the briefing: `c2b4ff5bdacde3a6cd95fb020a191c681022f52186ea7319d4ed1f7d3df6ce98`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential test must confirm the mapped handle the insert path produces, which no static evidence in this batch pins down.`, `A differential test must establish whether the key pointer is ever null in practice, because the miss path dereferences it at 0x0059c775.`, `A differential test must exercise the miss path and observe what 0x0059c520 writes into the caller's argument slot, since that value becomes the return value; a wrong node there would be an immediate fault in every caller.`, `No original-process trace exists for 0x0059c740. Every statement here is static.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential test must confirm the mapped handle the insert path produces, which no static evidence in this batch pins down.
- A differential test must establish whether the key pointer is ever null in practice, because the miss path dereferences it at 0x0059c775.
- A differential test must exercise the miss path and observe what 0x0059c520 writes into the caller's argument slot, since that value becomes the return value; a wrong node there would be an immediate fault in every caller.
- Are the 22 callers all operating on the same container instance, or does 0x0059c740 serve several containers of this instantiation? Only the four named editor callers were traced to cEditorAnimWorld+0x08.
- Call site 0x0059c981 can pass a null key pointer (0x0059c972 XOR EDI,EDI). On the miss path this body dereferences it unconditionally (0x0059c775), so that path would fault. Whether the container is guaranteed empty there, or whether the null never reaches this call, is not established statically.
- Can the insert fail or assert? 0x0059c520 has no visible failure return; EAX is set on every path, but no error path was identified.
- Does the container really use eastl::map with the default comparator? The 0x1c-byte header shape and the anchor convention match, but no vtable or typeinfo record was located and the allocator at +0x18 was never read.
- No original-process trace exists for 0x0059c740. Every statement here is static.
- The other 18 call sites (FUN_0059c830 .. FUN_0059d300) were not individually disassembled; their receiver and key setup is assumed to match the four that were read.
- What is the mapped element type? The binary shows a 4-byte handle whose target has a pointer at +0x08 whose vtable slot +0x04 is called (0x0059cb5a..0x0059cb6d). 'EditorCreatureControllerPtr' comes from the SDK header and is not proven.
- What value does 0x0059c520 give a freshly inserted node's mapped handle - null, or something else? The helper is an opaque port here, so operator[]-style default initialisation is assumed but not observed.
- Why is the low byte of the key pointer cleared (0x0059c77b) and the result passed as argument 4, and why does 0x0059c520 dereference it at 0x0059c59c? It is used only on a path that a non-empty container can reach, and the dereference reads the caller's own stack page, so the value compared there is not the searched key. This is unexplained and is the weakest part of the reconstruction.
