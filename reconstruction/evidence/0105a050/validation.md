# Validation 0x0105a050

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg11-h5-update-gate-0105a050/tool_update_gate_0105a050.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 57-instruction listing name the same 7 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 8 outgoing call edge row(s) over 7 distinct address(es) for 0x0105a050; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 7 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 57-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 5 source field-offset declaration(s) (field first, field flag_16c, field flag_16d, field last) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (57 of 57 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 7 conditional branch target(s) in the complete 57-instruction listing lie inside the recovered body span 0x0105a050..0x0105a0f9, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 57-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7dd4eb8b8e69caf296ebe408dcc14085e51bbb0bafdc61ff43251344116c4767`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9217b6d8a974535975fb138c9a41fe44734175a283960cb77cbe0f2651c9fad5`
- Pack digest quoted by the briefing: `7dd4eb8b8e69caf296ebe408dcc14085e51bbb0bafdc61ff43251344116c4767`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `no original-process trace exists in this repository; the static reconstruction of 0x0105a050 is unvalidated at runtime`, `the committed evidence pack for this target has no disassembly and no decompilation, so no listing-dependent check can be adjudicated from committed evidence; every listing fact here was read from the live bridge`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- What class owns this function. The two DATA references place it at the same offset in two table runs 0x140 bytes apart and a third run holds the caller 0x0105a890 there, but the run's base address is unknown, so the function is named only by its address.
- What the receiver and the owned subject are. Three receiver words and three subject words are read, and nothing in this body or in the SDK says what any of them mean.
- What the third call site at 0x0105bd33 is, since Ghidra defines no function containing it.
- Whether 0x0104cd40's (word >> 3) & 0xffffff01 is a bit test or a range comparison; the mask keeps bit 3 and bits 11 through 31 of the word and clears the rest, and the body only asks whether the result is non-zero.
- Whether 0x010593e0 pops its four arguments or the caller cleans them, which decides whether the mode-update port is __stdcall or __cdecl; the port is declared caller-cleaned here because this body's listing does not show an ADD ESP after the call, and the callee's own epilogue was not disassembled.
- Whether the back trail point forwarded to 0x00bbec40 is the intended argument, given that the front point is computed into the adjacent frame slot and never read; the listing is unambiguous about which pointer is pushed, and this reconstruction follows the listing rather than the intuition.
- Whether the fourth entry stack slot, which RET 0x10 pops and no instruction reads, was an argument at the source level or padding; the body substitutes its own immediate zero for the callee's fourth word, so the slot's value cannot reach any callee.
- Why 0x00bbec40 leaves a value in x87 ST0 that its own caller ignores.
- no original-process trace exists in this repository; the static reconstruction of 0x0105a050 is unvalidated at runtime
- the committed evidence pack for this target has no disassembly and no decompilation, so no listing-dependent check can be adjudicated from committed evidence; every listing fact here was read from the live bridge
