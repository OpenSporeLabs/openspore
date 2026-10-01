# Validation 0x00643a40

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/00643a40_eastl_map_find_or_insert.cpp`

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
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 51-instruction listing lie inside the recovered body span 0x00643a40..0x00643aba, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 51-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d6ed523f85d2764e60515a053d4f5648c6b6534ae0be40e702a671755a48fe79`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `2b203dc1e8530dfc973ba695e3e578aba617b1c7d617f2d309bf3799236b306c`
- Pack digest quoted by the briefing: `d6ed523f85d2764e60515a053d4f5648c6b6534ae0be40e702a671755a48fe79`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test would be needed to confirm that the reserved-key rejection in 0x00643db0 and the registration in cEditor::Initialize are reproduced, and that no runtime patch retargets the container.`, `No original-process trace exists for this address; every claim is static.`, `The identity of the owning class can only be settled with a receiver trace or a located vtable.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test would be needed to confirm that the reserved-key rejection in 0x00643db0 and the registration in cEditor::Initialize are reproduced, and that no runtime patch retargets the container.
- In the 0x006432d0 path that reaches 0x00579bd0 instead of 0x00579b50, the published node appears to be written into the value pair rather than the argument word, which would leave the 0x00643aa1 reload reading the zeroed word. Static stack arithmetic does not settle which write the compiler contracted for; the primary path is settled, this one is not.
- No original-process trace exists for this address; every claim is static.
- The container word at +0x00 and the node word at +0x0c are unobserved here, so their identity (comparator, allocator, colour) is inferred from the EASTL header rather than read.
- The identity of the owning class can only be settled with a receiver trace or a located vtable.
- What do the 4-byte keys and mapped values denote? The observed values look like class-name hashes but nothing in the binary names the registry.
- Whether the 0xffffff00 masking the decompiler shows on the argument pointer (an artefact of the byte-sized zeroing at 0x00643a7b) has any effect on keys whose address is not 256-byte aligned. Every inspected callsite passes a stack address, which is not 256-byte aligned in general, so the port keeps the observed behaviour of zeroing the low byte of the argument word.
- Which class owns each container? Four different sub-offsets (+0x10, +0x2c, +0x5c, +0x1b0) are used by different callers and no vtable was located for any of the owners.
- Why does 0x00643db0 treat the six keys that cEditor::Initialize registers as assert-failures? The relationship between the registration and the rejection is not established.
