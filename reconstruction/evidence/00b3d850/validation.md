# Validation 0x00b3d850

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-pilot-core-b01/b3d850_cursor_advance.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 15-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 15-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x4, 0x8), all of which the record accounts for or the listing is the better witness on; the 15-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=15, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x4, 0x8) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x4), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x8), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (15 of 15 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 15-instruction listing lie inside the recovered body span 0x00b3d850..0x00b3d86f, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 15-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `2c8f51a803f69d4c2db519750b2898bc1efff9561b559a9e7039f8cc79e2d839`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e07dfa2a6549e35d9cec8b9ac54ab5082c83e57c881edc06af1378c5db4368f6`
- Pack digest quoted by the briefing: `2c8f51a803f69d4c2db519750b2898bc1efff9561b559a9e7039f8cc79e2d839`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime trace would be needed to observe the element type, to see which of the port's four conditions actually rejects elements in play, and to check whether any caller ever presents a cursor equal to its end.`, `No original-process trace exists for 0x00b3d850; every claim is static.`, `The identity of the ctx object and of its vtable slot +0x2c can only be resolved with a receiver whose vtable base is known at run time.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime trace would be needed to observe the element type, to see which of the port's four conditions actually rejects elements in play, and to check whether any caller ever presents a cursor equal to its end.
- Do all 18 callers maintain cursor < end on entry? Only the two inspected callers were checked, and both do. The other 16 were not, and the function has no guard.
- Is the range [cursor, end) guaranteed to be non-empty? If a caller presents cursor == end the function walks off the buffer. Whether that ever happens in the shipping game is not determinable statically.
- No original-process trace exists for 0x00b3d850; every claim is static.
- The identity of the ctx object and of its vtable slot +0x2c can only be resolved with a receiver whose vtable base is known at run time.
- What class does the ctx object belong to? The four field offsets (+0xb58, +0x135, +0x110) and a vtable slot at +0x2c describe a large Simulator object, but no vtable was located for it and the SDK offers no candidate, so the port's subject is unresolved.
- What do the port's four conditions mean? ctx->vslot_0x2c() must be zero, bit 9 of the dword at +0xb58 must be zero, the byte at +0x135 must be non-zero, and bit 4 of the byte at +0x110 must be zero. None of these is named in the SDK, and the four are read from an object this function never identifies.
- What is the element type? The handle's stride of four bytes and the unconditional dereference prove the elements are 4-byte values, but whether they are pointers, handles or indices is not established. The port treats its argument as a pointer to something with a field at +0x08, which is the only structural clue.
- What is the owner at +0x08 for? It is loaded into ECX before the port call and the port never reads ECX. Either the port was inlined from something that did, or the owner is genuinely vestigial here. Not resolvable statically.
- Why is the function at 0x00b3d850 rather than inlined everywhere? The 19 service accessors immediately below it suggest a different translation-unit or optimisation boundary, but the reason is not established.
