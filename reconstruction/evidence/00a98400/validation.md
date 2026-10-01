# Validation 0x00a98400

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00a98400/sw2_00a98400_entry.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 31-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00a98400; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 31-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 31-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x18), all of which the record accounts for or the listing is the better witness on; the 31-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=31, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x18) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the listing shows 1 displacement(s) the record does not enumerate (0x18), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (31 of 31 instruction(s), 0 unparsed) and all 11 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 31-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 31-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 9 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 9 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `3d06dda746d820601d36ebdf344e4a909108b992195796b1be717e08d101c1ab`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `51d31632cc8588ed31f80fca071d99c6f838ce2346ef8fd59f666476d4bca872`
- Pack digest quoted by the briefing: `3d06dda746d820601d36ebdf344e4a909108b992195796b1be717e08d101c1ab`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- DECOMPILATION UNAVAILABLE. Both the persisted record and the live bridge report none (the evidence pack's decompilation category reports availability missing and no persisted or live decompilation for this target). Every claim here is from the disassembly listing, the ABI envelope, and bytes and terminators read back out of the image.
- THE CLASS THAT OWNS THE TABLE 0x01458788, AND WHETHER IT IS A vptr-BACKED VTABLE AT ALL. R1-VFT calls the table it reasons about a sound vptr-backed vftable, and GhidraMCP /read_memory at 0x01458770 for 48 bytes shows seven consecutive .text words of which this body is the seventh, but this binary carries no MSVC RTTI and no SDK name is recorded for the table. The receiver determination does not need a class and none is claimed. The other six words are transcribed in the staging header as bytes at an address, and nothing is inferred from them beyond their being code addresses.
- THE MACHINE RECORD'S STACK-ARGUMENT LIST IS INCOMPLETE, AND THIS PACKAGE COMPLETES IT RATHER THAN COPYING IT. abi_derived.stack_arguments enumerates one slot (entry_ESP+0x8, ordinal 2) with gaps 1 and abstains with "flow_not_modelled: the linear ESP walk ends at +12, so the listing is not one path". This package reads two stack arguments, at entry_ESP+0x4 and entry_ESP+0x8, on the evidence of the three callees' own RET 0x4 terminators and of the frame arithmetic closing at exactly the entry stack pointer. The reading is stated with its evidence in observed_original_abi.record_incompleteness and the record itself is left unedited. A reviewer who rejects the reading would have to also reject that those three functions end in RET 0x4, which is a fact about the image rather than about this body.
- THE MEANING OF ARGUMENT 1. It is read, pushed and handed on, and never dereferenced, so nothing in these 118 bytes constrains what it is. It is declared Word* because that is the width of the slot it occupies, not because anything here shows it points at a struct. The model test drives it over eight values, including unmapped ones, precisely because its value does not matter.
- THE MEANING OF THE TWENTY FRAME BYTES AT S+0x00 AND OF THE 0x24 BYTES AT S+0x14. Both are located, sized and, for the first, traced to their sources in argument 2. What they MEAN -- two 16-bit quantities and four single-precision values, or something else -- is not in evidence and is not claimed. The machine test checks them as bytes against the argument's own bytes and asserts no interpretation.
- THE RECEIVER'S IDENTITY. __thiscall says the receiver arrives in ECX; it does not say what the receiver IS. The body never dereferences it and never adjusts it, and the only code reference to this address is a word in a table rather than a this-adjusting stub, so no base relationship is observable from here at all. No class, no vtable identity, no receiver type, no object size, no vtable-pointer offset and no field are claimed, and none is guessed.
- THE RETURN REGISTER. The machine record names XMM0 at confidence APPROXIMATION under rule RT1, whose stated basis is "an x87 or SSE instruction appears in the body". The listing contains no instruction that places a value in a return register at the terminator, so this package declares void and records the machine's claim without adopting it. Nothing here settles what a caller of this body does read, and no return type beyond the source-side choice is claimed.
- WHAT 0x0041cb40, 0x00537f40 AND 0x00537dc0 ARE. None is named in the image, none is owned by a package, and this package gives none of them a semantic name. For 0x0041cb40 its own body was read (64 instructions) and it copies 0x24 bytes from its stack argument to its hidden receiver; that copy is modelled and nothing else about it is claimed. For the other two only the call shape is claimed: a hidden receiver in ECX and one callee-popped four-byte word.
- WHAT LIES AT RECEIVER+0x18. The body forms the address and hands it over; it never reads or writes there. The displacement is certain and the contents are not in evidence at all.
- WHETHER THE RECEIVER IS A POINTER AT ALL. It is a 32-bit word that is copied, added to and handed to a callee. Nothing in these 118 bytes inspects the value, so nothing here can say whether it addresses an object. The type is left undefined (struct Receiver;) and no pointee is named.
