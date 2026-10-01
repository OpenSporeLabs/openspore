# Validation 0x00980c50

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-dfw-00980c50/dfw_00980c50.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 2-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00980c50; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 2-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 2-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (2 of 2 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 2-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 2-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `488b8329a85997cd80d79a0d2d4701e1d424535feec10d344df159390c6d31ce`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e4cbda8cf6a53b3f102c03da3757b13b032b615fa75cbd90594e946d865a3044`
- Pack digest quoted by the briefing: `488b8329a85997cd80d79a0d2d4701e1d424535feec10d344df159390c6d31ce`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No runtime validation has been run; every claim here is static.`, `The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.`, `Whether slot +0x00 of the run is genuinely a getter of the word the block at 0x00980c80 stores is unproven; the adjacency is a byte-level argument only.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the SDK return type void or is it a 32-bit value? The machine writes EAX with an immediate, but a void-returning SDK placeholder is equally consistent with the vtable generator's naming. The span is modelled as returning std::uint32_t; a human reviewer with vftable context may prefer void.
- Is the SDK return type void, or is it a 32-bit value? The machine writes EAX with an immediate; the SDK header, the Ghidra import and the live decompilation all say void. The span is modelled as returning std::uint32_t because that is what the two instructions do, and the void reading is left open rather than refuted. Carried forward unchanged from the pack.
- No runtime validation has been run; every claim here is static.
- Nothing else was investigated and nothing else is claimed. The adjustor thunks at 0x00980c60 and 0x00980c70, the INT3 padding their jumps target at 0x00980cb0, the four identical 0x006f2f20 entries at slots +0x20..+0x2c of the run, and the 0x0096ff70 sibling are all outside this six-byte span; they are named here only to record that they were left alone.
- The dispatching caller of the run's slot +0x00 is unknown, so the circumstances under which this getter is invoked -- and whether its result is compared against anything -- are unknown.
- What conventions is the frame compatible with? The derived record lists [__cdecl, __stdcall, __thiscall, __fastcall] with confidence UNKNOWN, and its own inference C10 notes the function is byte-identical under all four. This package picks __thiscall because the persisted record asserts an ECX receiver from the SDK method header, and states plainly that the instruction bytes do not discriminate: a body that reads no register and pops no stack word is the same six bytes under every convention on the list.
- What is 0xCF2B2AD5 semantically? It is stored by the block at 0x00980c80 and returned by this target, but it appears in no SDK enum, structure or function signature, so it is left as a literal.
- What is 0xcf2b2ad5 semantically? The pack records that it appears in no SDK enum, structure or function signature, so it is left as a literal here. The neighbouring block at 0x00980c80 stores the same immediate into its first argument, which makes a getter/setter pair over one object word a plausible reading -- and the pack is equally explicit that it is unproven: 'What is the true entry point and owner of the constant-storing block at 0x00980c80? Ghidra finds no function there, so the getter/setter pairing is unproven.' This package claims no pairing and says nothing about 0x00980c80, which is a different address outside this body.
- What is the true entry point and owner of the constant-storing block at 0x00980c80? Ghidra finds no function there, so the getter/setter pairing is unproven.
- Whether slot +0x00 of the run is genuinely a getter of the word the block at 0x00980c80 stores is unproven; the adjacency is a byte-level argument only.
- Which of the four identical 0x006f2f20 entries at slots +0x20..+0x2c of the run is meaningful, and what does 0x006f2f20 contain? Not investigated; it is outside this target's span.
- Which vftable actually owns slot +0x00 of the run at 0x01444364, and what is its offset? The SDK name func88h implies offset 0x88, but the only DATA reference is at +0x00, and the same conflict is unresolved for the sibling 0x0096ff70.
- Which vftable owns this slot and at what offset? The SDK name func88h implies offset 0x88, while the only DATA reference to this address is at +0x00 of the run based at 0x01444364. Unresolved for this address and, per the pack, identically unresolved for the sibling at 0x0096ff70.
- Why do the adjustors at 0x00980c60 and 0x00980c70 branch into the 0xCC padding at 0x00980cb0 when real code starts at 0x00980cb4? Is the SDK symbol for 0x00980cb0 four bytes low, or is Ghidra's FUN_00980cb0 a mis-created function?
- Why does the SDK declare three int parameters for a frame that reads no stack word and pops nothing? The extra words are most likely artefacts of the SDK method-header generator.
- Why does the SDK method header declare three int parameters for a frame that reads no stack word and pops nothing? The pack calls the extra words most likely artefacts of the SDK method-header generator. This package's model test can show that a caller which pushes three words and cleans up after the call works and that the callee removes none of them; it cannot show what the real game pushes, because the body provides no evidence either way.
