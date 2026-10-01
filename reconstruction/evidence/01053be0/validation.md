# Validation 0x01053be0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-01053be0/sim_prefix_01053be0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 95-instruction listing name the same 6 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x01053be0..0x01053cfd are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x01053c96; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 10 outgoing call edge row(s) over 6 distinct address(es) for 0x01053be0; the source span names 6 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 95-instruction listing names 2 data address(es) (0x013f1cac, 0x01477fbc); the data-reference artifact is read whole and records 2 reference row(s) out of this body covering every address under review, with access mode(s) read=2 |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 95-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 95-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=95, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (95 of 95 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `WARN` | `partial` | 1 of 6 conditional branch target(s) fall outside the recovered body span 0x01053be0..0x01053cfd, so the listing is a slice and flow continues past it; the source span declares for, if |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 95-instruction body names 2 indirect transfer(s): 0x01053c19 dispatches slot 0x2c through the table word in EDX; 0x01053cac dispatches slot 0x24 through the table word in EAX; the machine parse consumed 95 of 95 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 7 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is SRET_SUSPECTED and the source span declares return type 'void': the ABI envelope records a hidden-pointer return hypothesis (suspected), so the return register holds an address rather than the value and no width read off it would be a claim about the wrong value. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 4 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `509ecc2517bb9ed74934688a790a8aa3e1931371ba1bb98d3c1a8f2a98b292fa`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `7b0c8fe1036ff09e47d568fcb497adfa0f26f62ab0ee59acb589ff9e36c9494c`
- Pack digest quoted by the briefing: `509ecc2517bb9ed74934688a790a8aa3e1931371ba1bb98d3c1a8f2a98b292fa`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- RUNTIME. No original-process trace exists in this repository, none was attempted, and the runtime axis remains GATED at 0. Every claim here is from the disassembly listing, the machine-derived ABI sub-records, and bytes read back out of the image.
- THE CONVENTION. conventions.calling_convention is null with four candidates and confidence UNKNOWN, and cleanup is UNKNOWN with side null. __thiscall is the shape the receiver suggests and is NOT asserted; neither is any other candidate. Which side of each of the six direct callees restores ESP is likewise undetermined.
- THE DISPATCH SITE COUNT. The machine dispatch record counts indirect_calls 2; the 95-instruction listing shows one indirect transfer site (CALL EAX). Both computed transfers are present in the bytes (ff d0 and ff d2) and the model test checks both, so the disagreement is most likely the record counting the loop's CALL EDX separately -- but that is an explanation, not a determination, and it is not used to change any claim.
- THE EXIT AND THE RETURN. Both ways out of the recovered span leave it (the JLE at 0x01053cf9 to 0x01053d3b, and the fall-through at 0x01053d00) and neither is inside it, so the recovered 288 bytes cannot say what this function returns. Reading past the span shows MOV EAX,ESI ... ADD ESP,0x18; RET 0x8 at 0x01053d3b, which would return the caller's word and pop eight bytes of arguments -- but that is outside the recovered span, is not modelled, and is not claimed. The true return type, its width, and the callee-side cleanup of 0x8 are all unresolved.
- THE RECEIVER'S IDENTITY. No class, no vtable identity, no receiver type, no object size, no vtable-pointer offset, no member and no layout. Seven classifier vtable associations and 24 xrefs, all at 0x0149b..., are a transitive classifier result, not a class identity, and one address named by several tables is also what table merging looks like. This binary carries no MSVC RTTI.
- THE ST0 RETURN CLAIM. The record's return sub-record names ST0 at APPROXIMATION confidence on the stated basis that an x87 or SSE instruction appears in the body. The byte transcript shows the x87 stack balanced (each FLD has its FSTP) and every SSE use a MOVSS pair through XMM0, so the basis does not hold inside the recovered span, while void_possible is false. This package reports the disagreement and claims neither reading.
- THE UNDETERMINED ADDRESS AT 0x01053cbf. LEA EAX,[ESP+0x24] resolves to entry_ESP-0x18 or entry_ESP-0x24 depending on whether the computed call at 0x01053cac pops its three stack words itself. The model's ESP arithmetic across loop iterations is not reproduced for the same reason, and the two cases' agreement (the manager opens on the first call, the loop's own manager call is never gated) is a property of the listing, not of the ESP.
- WHAT THE SIX CALLEES ARE. The evidence pack carries NO decompilation for this target (categories.decompilation is missing, and the briefing's DECOMPILATION section says so). The names here carry addresses and nothing else. A cached decompilation exists under tools/mcp/cache/decompiled/, but it is not part of the pack, no claim in this package rests on it, and none of its type names are used. 0x00b3d350 additionally carries a Ghidra name from the SDK surface (Simulator::cGameInputManager::Get) that this package does not adopt as a class, a type or a meaning.
- WHAT THE WORD AT entry_ESP-0x0c IS. Two LEA sites hand its address to 0x00b3d350 and the span never writes it, so its content is whatever the caller left. It is passed on in the model and never read back, which is the machine's behaviour, and no claim is made about what 0x00b3d350 does with it.
- WHETHER THE RECORD'S SLOT LIST IS COMPLETE. It enumerates one slot while the listing reads two words of the incoming argument area, and parse.esp_unresolved is true. Whether entry_ESP+0x8 is a parameter, a reserved word, or an argument the caller does not use is unresolved; the listing shows only that the body loads it and pushes it.
- WHETHER entry_ESP+0x4 IS A HIDDEN STRUCT-RETURN POINTER OR AN OUT-PARAMETER. The record cannot decide it (ambiguity sret_vs_out_param, present null, candidates [hidden_sret, out_parameter]) and the listing agrees: the word is loaded into a register and then written through as a twelve-byte destination, which both forms compile to. The entry's second parameter is named for the address it resolves to.
- WHY GHIDRA'S RECOVERED BODY ENDS AT 0x01053cff. Ghidra holds the JLE edge at 0x01053cf9 as leaving the body, so the body stops one instruction before the code that follows 0x01053cfd. A fresh collection of the evidence pack therefore yields the same 95 instructions, and the abstention is not a stale-pack artefact.
