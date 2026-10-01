# Validation 0x004ad550

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-dispatch-b03/editor_model_union_bounds.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 112-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 112-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 112-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=112, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x18), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x18) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (112 of 112 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 112-instruction listing lie inside the recovered body span 0x004ad550..0x004ad6ea, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 112-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `24817a1be9118b006a0c58fd7635ecdfaf6930c62561caa5ee34954eadd54264`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `dedb87cf5e95866e1ae7cb5fee761473f0f73e0fd824a937b51d9b442c2803e6`
- Pack digest quoted by the briefing: `24817a1be9118b006a0c58fd7635ecdfaf6930c62561caa5ee34954eadd54264`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A differential test must confirm the box is written even when the list is empty, since that is the invariant a caller is most likely to depend on incorrectly.`, `A trace must confirm that the 100-level ceiling in 0x00435d40 is never reached, i.e. that no rigblock hierarchy in the shipping data is deeper than 100.`, `A trace must record the actual filter-flag values passed by callers, which is the only way to learn whether the ancestor-chain test is ever active in the shipping build.`, `No original-process trace exists for this function. Static analysis cannot show whether the rigblock vector is ever empty in a live editor session, which is the only path that produces the inverted sentinel in a caller's box.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A differential test must confirm the box is written even when the list is empty, since that is the invariant a caller is most likely to depend on incorrectly.
- A trace must confirm that the 100-level ceiling in 0x00435d40 is never reached, i.e. that no rigblock hierarchy in the shipping data is deeper than 100.
- A trace must record the actual filter-flag values passed by callers, which is the only way to learn whether the ancestor-chain test is ever active in the shipping build.
- No original-process trace exists for this function. Static analysis cannot show whether the rigblock vector is ever empty in a live editor session, which is the only path that produces the inverted sentinel in a caller's box.
- The five uninspected call sites at 0x00574bb4, 0x00583e94, 0x0058072b, 0x005addc6 and the pair at 0x005ae348/0x005ae35d.
- The method name. Nothing in the binary or the SDK names it; the reconstruction's name describes the operation, not a recovered identifier.
- The owning class. The +0x18 vector matches Spore/Editors/EditorModel.h's mRigblocks exactly and the code region matches, but no vtable was located and there is no RTTI, so the class is a candidate and not a claim.
- What the 24-byte box the caller at 0x00586ee8 receives is used for beyond the first float it reads at 0x00586eed; the rest of that caller's use was not followed.
- What the filter flag byte means to a caller. Observed only as 'non-zero enables the ancestor-chain test'; no caller's intent was established, and the three uninspected callers in the 0x0057/0x0058 region were not disassembled.
- Whether 0x0044ae00 with mode 0 is the right mode for every caller of this function, or whether some caller-visible behaviour depends on the mode this body hard-codes to 0.
- Which of the two count comparisons is intended for a malformed vector, and whether a negative count can occur in practice.
- Why the accumulator is default-initialised twice.
