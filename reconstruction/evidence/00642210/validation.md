# Validation 0x00642210

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-00642210/w2_00642210.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00642210; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x00642210..0x0064222b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d0b37290fe61bf35cb5f4e3f6853e810445887c73b210048c741aae281c77fb2`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6b0acce8ad5b68315fb33ace506d8a8319e030b32cc926f46a3afe4eb8d25647`
- Pack digest quoted by the briefing: `d0b37290fe61bf35cb5f4e3f6853e810445887c73b210048c741aae281c77fb2`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none (04_decompilation state: missing; live attempt ghidra_rest_error, "Decompilation did not complete"). Every claim here is from the disassembly listing, the ABI envelope and bytes read back out of the image.
- THE CLASS THAT OWNS THE TABLE 0x013ff648, AND WHETHER IT IS A vptr-BACKED VTABLE AT ALL. R1-VFT calls the table it reasons about a sound vptr-backed vftable, and GhidraMCP /read_memory at 0x013ff640 for 24 bytes shows a table whose first slot is this body, but this binary carries no MSVC RTTI and no SDK name is recorded for the table. The receiver determination does not need a class and none is claimed.
- THE RECEIVER'S IDENTITY. __thiscall says the receiver arrives in ECX; it does not say what the receiver IS. This body never dereferences it and never adjusts it, and the two entry stubs adjust ECX by 0x10 and 0x14 before arriving, so at least two different base relationships reach 0x00642210. No class, no vtable identity, no receiver type, no object size, no vtable-pointer offset and no field are claimed, and the base relationships are not guessed.
- THE RETURNED VALUE'S C TYPE. The machine fixes the WIDTH (4 bytes; MOV EAX,ESI at 0x00642228 is the last write before the sole return on both paths) and the FACT that the value is the receiver. It does not fix the type: Receiver *, uint32_t or any other four-byte spelling are all consistent with it. Receiver * is the declared source-side choice, not a recovered fact.
- WHAT 0x00642190 DOES. Owned by pkg-swarm-w1 as sporepedia_asset_destroy_00642190. This package reads none of that package's source and asserts only that its call here is unconditional, passes nothing on the stack, and hands over the receiver in ECX. The two packages' claims are independent.
- WHAT 0x00f47380 IS. Unnamed in the image (FUN_00f47380), owned by no package, and given a semantic name by nothing here. It is an observer in this package's model test. The one machine fact this package holds about it is the call shape: one cdecl dword, dropped by the body at 0x00642225.
- WHETHER THE ENTRY STUBS 0x00642170 AND 0x00642180 BELONG TO THIS BODY'S OWN CLASS OR TO A DERIVED ONE. Two caller-side this-adjustors is the shape of multiple inheritance adjustment, but the object model behind them is not in evidence here and is not assumed.
- WHETHER THE OPTION WORD'S UPPER 24 BITS CARRY MEANING. The machine reads one byte and tests one bit. The other three bytes of the four-byte slot are untouched here, but a caller may have put something in them, and nothing in this body constrains them.
- WHETHER THE RECEIVER IS A POINTER AT ALL. It is a 32-bit word that is copied, passed in a register, pushed and returned. Nothing in these 30 bytes inspects it, so nothing here can say whether it addresses an object. The type is left undefined (struct Receiver;) and no pointee is named.
