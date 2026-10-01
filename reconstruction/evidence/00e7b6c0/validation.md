# Validation 0x00e7b6c0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00e7b6c0/w2_00e7b6c0_entry.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 105-instruction listing names 8 data address(es) (0x15a7c4c, 0x15a7c50, 0x15a7c54, 0x15a7c58, 0x16b3c04, 0x16b3c28, 0x16b3c2c, 0x16b3c30) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 8 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (105 of 105 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 5 conditional branch target(s) in the complete 105-instruction listing lie inside the recovered body span 0x00e7b630..0x00e7b7b1, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 105-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 4 of 8 static checks evaluated, 3 passed, 4 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `824938b17aec7864cd546469a45d1fc6320b4dbdfd2735b7e74d031ef8ca7873`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `7407e49988aa0210e1a9868ff17d3cdf63d3d20a1c4ae19b0872b1fef2da282e`
- Pack digest quoted by the briefing: `824938b17aec7864cd546469a45d1fc6320b4dbdfd2735b7e74d031ef8ca7873`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- How many x87 registers does 0x00e6d200 leave, and with what values? The FSTP at 0x00e7b69b pops one this body never pushed, so its value is whatever ST0 held on entry. The model test therefore takes the ST0 content as a PARAMETER and pins only the ORDER of the two stores, which are the same value because FST does not pop.
- Is the machine record's ST0/float_or_x87_in_ST0 return claim wrong, or does this body leave a value in ST0 that the listing does not show? The body pops three x87 registers and pushes two, which is the opposite of leaving a return value, and this package adopts void on the listing's own evidence. The divergence is recorded, not resolved.
- What is 0x00e6d200's ECX, held in the callee's hidden register, and what does it do? Its own body WAS decompiled (Simulator::Cell::PlayAnimation) but this package claims nothing about it beyond the four stack words the listing pushes and the stack discipline the listing shows.
- What is 0x016b3c04, and what are 0x016b3c28, 0x016b3c2c, 0x016b3c30, 0x015a7c4c, 0x015a7c50, 0x015a7c54 and 0x015a7c58? Thirteen loads and no store; the model test plants words in both pages and checks each reaches the record, but nothing names them.
- What is at the base EAX, and what do the twenty-six written displacements mean? Offsets 0x04..0x78 are located, two of the writes are single-byte, and the run 0x0c..0x1b is untouched -- but no type, member, size or layout is claimed, because the base is 0x00b72210's result and nothing in evidence describes it.
- What is the relationship between the pool base 0x016b3c04, the record EAX fills, and the object 0x00b72160 allocates from? 0x016b3c04+0x1c and +0x54 are used as hidden registers and 0x00b72160's own body shows a free-list allocator; whether the +0x1c and +0x54 regions are two pools, two generations of one pool, or something else is not in evidence.
- What is the value at ESI+0x112, +0x113, +0x178, +0x17f, +0, and at the stack argument's +0x00, +0x108 and +0x17b? Five single-byte guards and three dwords are located exactly; what they MEAN is not in evidence.
- Which exit does 0x00e6d200 take when called from 0x00e7b696, and which does 0x00e780a0 take when called from 0x00e7b793? Ghidra reports ADD ESP,0x14;RET and ADD ESP,0x10;RET as their highest-addressed instruction pairs, and neither can be the exit these sites take without unbalancing the epilogue.
- Why does the g++ -O2 build of the MODEL TEST segfault inside its own harness while the same sources pass at -O0, -O1, -O3 and under clang++ at every level? The reconstruction's emitted body is byte-identical at -O2 and the failing symbol's machine code is complete in both the object and the linked binary.
- Why does the xref export carry no outgoing edge for 0x00e7b6c0 when it carries ten for 0x00e7b630? The export appears to be keyed on function entries and this target is not one. Until that is settled the validator's CALLS check compares a source's call set against an empty machine set and cannot reach an agreement.
