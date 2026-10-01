# Validation 0x00841540

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-argscript-formatparser-setflag/argscript_formatparser_setflag.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x00841540; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 0 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field field_04c) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 31-instruction listing lie inside the recovered body span 0x00841540..0x00841588, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `be28a8aff2cf25e8584c27614b93700ea2dcef5049ea14781c2fc3d996da74bc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `2d7f93133718028de799c0fd314ccdd8b0e29acd4f1f65fa54dda7261455974d`
- Pack digest quoted by the briefing: `be28a8aff2cf25e8584c27614b93700ea2dcef5049ea14781c2fc3d996da74bc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation, no differential trace and no indirect-caller trace was captured, so runtime_validated remains 0.`, `The exact numeric type of the destination pair is modelled as two floats on the strength of the x87 store/pop pair and of the caller packing the result as a two-element float array; the decompiler independently typed them float10.`, `The identity, type and width of the FormatParser sub-object at this+0x4c are unresolved. Only its address is observable; the model holds a single opaque word and SetFlag never dereferences it.`, `The x87 instruction forms are resolved and are no longer a gate: three independent decoders and a hand ModRM decode all give FSTP, FSTP, FLD. The remaining gates below are unchanged.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- ABI CHECK STILL WARNS, AND THIS PACKAGE CANNOT CLEAR IT. The callsite_contract section now proves __thiscall from the call edge, but the machine ABI record still reads conventions.confidence = UNKNOWN with candidate_conventions [__stdcall, __thiscall], because the tooling deriver judges the target's own listing alone and its LEA ESI,[ECX+0x4c] performs no memory access through the receiver. The confidence field is produced by tools/reconstruction_tooling and mirrored into reconstruction/knowledge/index.json (where records["0x00841540"]["abi"] is {}), neither of which this package may edit. The observation is recorded and the convention is stated as __thiscall, but the record is not relabelled to a confidence this package has not earned at the machine layer.
- Both vtables the briefing associates with this VA, 0x0141c97c and 0x0141c9d4, were not shown to contain 0x00841540. Reading the 88 bytes at 0x0141c97c yields 0x00841290, 0x00841300, 0x00841370, 0x008414c0, 0x008414d0, 0x00843240, 0x00843280, 0x008432d0, 0x00846b00, 0x00843320, 0x00846280, 0x00841500, 0x00845260, 0x00841c90, 0x00846420, 0x00d1dcd0, 0x008452e0 and 0x00835320 - 0x00841540 is absent. Whether SetFlag is virtual at all is unconfirmed, though it takes an ECX receiver like a virtual thunk would.
- EVIDENCE COVERAGE remains WARN and is not improvable from this package: static categories are unavailable because this function has no globals, no external callees, no recorded contradictions, no semantic hypotheses, and no original-process trace exists anywhere in the repository. These are true absences, not collection gaps.
- Identity of the FormatParser sub-object at this+0x4c. It is the receiver of the scanner methods 0x0083e470, 0x0083d290 and 0x0083e1c0 and of the siblings 0x00841590, 0x00841610 and 0x008416b0, but no class name, type or width was established for it and it is deliberately left opaque.
- No FormatParser field below the +0x4c sub-object was recovered and the total object size is unknown. The caller at 0x0082f9a0 reaches at least +0x188 through EBX, which bounds one object shape from below but is a different object from the stack sub-object this call site passes, so it was not used as a layout.
- No original-process invocation, no differential trace and no indirect-caller trace was captured, so runtime_validated remains 0.
- Runtime remains correctly GATED. No original-process invocation, no differential trace and no indirect-caller trace was captured, so runtime_validated stays 0. The single call site at 0x0082fde0 is a direct call and the return value is used immediately, which is machine evidence that the ABI is not merely inferred, but it is not a runtime observation.
- SETTLED IN ATTEMPT 2 (was the top open question): the x87 instruction-form anomaly at 0x00841557, 0x00841575 and 0x0084157f is RESOLVED, and the 'FSTCW' reading recorded by attempt 1 was a decode error. d9 1f is opcode D9 with ModRM 0b00_011_111, i.e. mod=00, reg=/3, rm=111; d9 5f 04 is mod=01, reg=/3, disp8=0x04; d9 07 is mod=00, reg=/0, rm=111. In the x86 opcode map D9 /3 is FSTP m32fp and D9 /0 is FLD m32fp, whereas FSTCW is D9 /7 (FNSTCW) and D9 /5 is FLDCW. Three independent decoders agree on FSTP, FSTP and FLD: the live Ghidra listing, GNU objdump -D -b binary -m i386 -M intel over the extracted 73 bytes, and llvm-objdump --x86-asm-syntax=intel over the same bytes re-linked at 0x00841540. The FSTCW reading is independently impossible on this body: it would write only 2 of each 4-byte word, leak the x87 stack, and leave the 0x0084157f FLD never popped. The attempt-1 reconstruction already modelled the float-store reading and was therefore correct; the open question it raised against itself is withdrawn.
- The +0x4c member NAME is reconstruction-asserted and not machine-corroborated, exactly as the validator flagged. The DISPLACEMENT is machine-observed twice, but no struct layout exists anywhere to corroborate a name: the index carries types["FormatParser"] with an empty fields array, Ghidra reports class_namespace_exists=false for FormatParser, and neither the Spore-ModAPI SDK nor the knowledge index supplies a Lexer, Scanner or ScanContext layout. Until such a layout is recovered the sub-object can only be named opaquely.
- The exact numeric type of the destination pair is modelled as two floats on the strength of the x87 store/pop pair and of the caller packing the result as a two-element float array; the decompiler independently typed them float10.
- The identity, type and width of the FormatParser sub-object at this+0x4c are unresolved. Only its address is observable; the model holds a single opaque word and SetFlag never dereferences it.
- The x87 instruction forms are resolved and are no longer a gate: three independent decoders and a hand ModRM decode all give FSTP, FSTP, FLD. The remaining gates below are unchanged.
- Whether the branch predicate is a comma test or a more general one-character consume. The 0x2c pushed at 0x00841555 is read as a byte by 0x0083d290 and consumed unconditionally there, so a non-comma input is still consumed and merely reported through a diagnostic call at 0x0083d2b8. This target's own body does not distinguish the two readings.
- Whether the two destination words are a (min,max) range, two independent values, or a value plus a derived bound. Only the collapse-on-missing-comma behaviour is observed. The caller packs them as a 2-element float array for 0x0082e380, which fixes the width and not the meaning; the meaning was not traced past that call.
