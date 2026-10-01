# Validation 0x0096ff70

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-0096ff70/dfw_0096ff70.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing name the same 1 direct transfer target(s), including a target reached only by a jump; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x0096ff70; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 2-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=2, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `85a52ad47b3ffcd7a156e021601b1687080f15327093211646d4878565cdc8fa`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e845442066b1d0373dfc154ce0f0b1bdd578f5b434bd28a9fdfcf9421aec51ab`
- Pack digest quoted by the briefing: `85a52ad47b3ffcd7a156e021601b1687080f15327093211646d4878565cdc8fa`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No runtime validation has been run; every claim here is static.`, `The concrete caller that dispatches through the vftable entry at 0x0144258c is unknown, so the values of the deleting flag in real use are unknown.`, `Whether the -0x0C receiver is a GlideEffect IBiStateEffect subobject or the analogous subobject of a sibling class (the same two-instruction shape is shared by UTFWin::InflateEffect::func88h at 0x0097e550 and by 0x0096ff80 with -0x04) is not settled by the static image.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the -0x0C receiver the subobject the vptr was reached through, or an unrelated pointer the caller happened to hold? Deciding it needs a runtime trace of the value in ECX at 0x0096ff70, which this repository has never run.
- Is the receiver a UTFWin::GlideEffect IBiStateEffect subobject, or the same-offset subobject of a sibling effect class? The SDK places IBiStateEffect at +0x0c and the adjustment is 0x0C, but the byte-for-byte identical shape at 0x0097e550 (UTFWin::InflateEffect::func88h) and the -0x04 shape at 0x0096ff80 make the two-instruction form non-distinguishing, and the static image does not settle it. The model therefore names no class at all.
- Is the receiver of 0x0096ff70 a UTFWin::GlideEffect IBiStateEffect subobject, or the same-offset subobject of a sibling effect class? The identical SUB ECX,0x0C/JMP shape at 0x0097e550 (UTFWin::InflateEffect::func88h) makes the shapes non-distinguishing.
- No runtime validation has been run; every claim here is static.
- The calling convention is an inference, not a record. The machine-derived ABI record abstains outright (verdict ABI_UNKNOWN, confidence UNKNOWN) because the body has no terminal RET, and the live decompilation carries 'WARNING: Unknown calling convention'. thiscall is the best-supported reading -- the tail target's own RET 0x4 pops the one forwarded word, and the receiver travels in ECX -- and it is what the model declares, but nothing in the target's own two instructions proves it. This is the sole reason the ABI check is a WARN rather than a PASS, and no source change can move it.
- The concrete caller that dispatches through the vftable entry at 0x0144258c is unknown, so the values of the deleting flag in real use are unknown.
- What is the lifetime and ownership meaning of the 0x013EB938 store at [this+0x60], and is it a vptr or a plain field? 0x0096ffd0 was not a target of this run, so no claim is made here.
- Whether the -0x0C receiver is a GlideEffect IBiStateEffect subobject or the analogous subobject of a sibling class (the same two-instruction shape is shared by UTFWin::InflateEffect::func88h at 0x0097e550 and by 0x0096ff80 with -0x04) is not settled by the static image.
- Which of 0x0096ff70 and 0x0096ff90 is the scalar-deleting versus vector-deleting entry in the unknown owning vftable, given the Ghidra run order places the scalar-flag thunk first?
- Which vftable in the binary actually places 0x0096ff70 in the destructor slot, given that the SDK's func88h convention implies offset 0x88 while the only DATA reference is at +0x08 of the run based at 0x01442584?
- Which vftable, if any, places 0x0096ff70 in a destructor slot? Ghidra's vtable detection never ran on this program, so the only evidence is a DATA pointer at +0x08 of a run based at 0x01442584 whose length exceeds any single vftable, while the SDK's func88h naming convention implies offset 0x88 (whose slot in that run holds 0x00951220, UTFWin::GetAllocator). The destructor reading stays a hypothesis and is not used.
- Who calls this, and with what deleting flag? There is no code caller; the only reference is the DATA pointer at 0x0144258c. Nothing in the static image establishes the values the word takes in real use.
- Why does the SDK declare three int parameters when the machine forwards one stack word? The extra words may be unused register-class artefacts of the SDK method-header generator.
- Why does the SDK declare three int parameters when the machine forwards one stack word? The extra words may be unused register-class artefacts of the SDK method-header generator. The model declares the one word the machine shows.
