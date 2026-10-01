# Validation 0x00438700

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b01/00438700_cascade.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 128-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 128-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 128-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=128, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x28, 0x3e0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 2 of those (0x28, 0x3e0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (128 of 128 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 128-instruction listing lie inside the recovered body span 0x00438700..0x004388a5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 128-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `68e7bf31bd5558bb097516e722ebece9ae48e9870473bd5cbf962cd6805c1d6a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `434f403f05c2b06f5bad9f5ec3d53e95f160f57d1c62d9eba1372295312cbba4`
- Pack digest quoted by the briefing: `68e7bf31bd5558bb097516e722ebece9ae48e9870473bd5cbf962cd6805c1d6a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential fixture would need to drive the editor with one rigblock whose bit 7 is set and one whose bit 11 is set, to see which branch actually fires.`, `No original-process trace exists. Every flag value, every +0x1c0 value and every 0x004a7e60 result in the contract above is a static reading of the code path, not an observation.`, `The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential fixture would need to drive the editor with one rigblock whose bit 7 is set and one whose bit 11 is set, to see which branch actually fires.
- Are self and other guaranteed distinct? 0x00437b00's own guard suggests not, and this function has none.
- Is the receiver really Editors::EditorRigblock? Three independent observations support it -- the 0x3c-bit attribute field, the 0xe08 'Editor' allocation with bit 0x14 set, and the shared +0x28 / +0x4f / +0x3e0 guard triple -- but no vtable was resolved and the binary has no RTTI, so this stays a candidate.
- No original-process trace exists. Every flag value, every +0x1c0 value and every 0x004a7e60 result in the contract above is a static reading of the code path, not an observation.
- Only three of the twenty-one call sites were disassembled window-by-window in this batch; the remaining eighteen receiver provenances were taken from the briefing's call graph and were not independently re-verified at the instruction level.
- The original Cell stage has never been entered in any recorded run, so no stage-level reachability claim is made.
- What does the dword at +0x1c0 mean, and why does a zero there permit the cascade? The field is named only as an offset.
- What is 0x004a7e60 deciding? It is a two-level byte predicate with an unknown name, and its result gates the entire second half of this function.
- What is attribute bit 11? The SDK enum has no enumerator at 0x0B and duplicates 0x0A, so no name is asserted.
- What is the +0x3e0 sub-object? It is a pointer to something with its own +0xdc8 attribute field, since 0x00435a10 applies the same bit writes to it. No type is established for it.
- What is the role of 0x004388b0? Its body is fully read, but release, detach and deferred-delete cannot be separated statically. It remains an opaque port in the reconstruction.
