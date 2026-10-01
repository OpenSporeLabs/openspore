# Validation 0x0095fa30

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-0095fa30-utfwin-isancestorof/utfwin_is_ancestor_of_0095fa30.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 3-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x0095fa30; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `PASS` | `complete` | the complete 3-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x80) and the 1 the complete 3-instruction listing names through ECX (0x80) are all within the machine-derived receiver bounds (0x80), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (3 of 3 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 3-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 3-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `f435e179d3d83770459b2de12b537146a60b60775f34e557eb085c73c5d14ccd`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `8350864c8c3487aa19a6d90df310b9c572bda9481c813a8a0b9de02c4507407c`
- Pack digest quoted by the briefing: `f435e179d3d83770459b2de12b537146a60b60775f34e557eb085c73c5d14ccd`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.`, `Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.`, `Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.`, `Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.`, `Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.`, `confirm the class identity behind the 33 vtable images; the binary has no MSVC RTTI`, `observe one real virtual call through a slot +0x00 word and record whether the caller consumes AL, which would settle the void-vs-bool return type`, `record the receiver allocation size at runtime; the 0x84 byte modelled extent is only the prefix through the written slot`, `record the value stored at receiver+0x80 and find its consumer, to establish whether the SDK name IsAncestorOf is misassigned`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Confirm the containing table base and slot displacement of at least one of the 33 references so the shared-vtable analogue chain can be grounded.
- Is the EAX residue at the RET meaningful to any caller, and does any of the 33 virtual slots get its result from AL?
- Is the stored word a window pointer, a vtable-adjacent pointer, or a reference-counted handle? The decompiler types it as IWindow * but nothing here proves that.
- Observe a real virtual call through one of the 33 function words and record the receiver instance state before and after the store at receiver+0x80.
- Observe whether any caller consumes AL after the RET 0x4, which would give the EAX residue a real contract the static body cannot prove.
- Record the real receiver allocation size, because the 0x84 byte modeled extent is only the prefix through the written slot.
- Record the runtime value stored at receiver+0x80 and whether the same word is later consumed as a window pointer, a vtable-adjacent field or a reference count carrier.
- Return type: the SDK symbol table and the Ghidra signature say bool, but the machine writes no AL and no upper EAX bytes on any path, so the reconstruction models void. Settling this needs a runtime trace of one virtual call through slot +0x00, recording whether the caller reads AL.
- Semantics of the word stored at receiver+0x80: whether it is a window pointer, a registration record, a cached argument or a reference-count carrier. No instruction in this body dereferences or compares it, and no consumer is reachable from here.
- The briefing carried no ABI section (evidence.missing_sections listed ABI), so the recorded ABI is derived from the three-instruction disassembly and the live raw bytes; a repaired Ghidra calling convention should confirm the thiscall receiver and the RET 0x4 cleanup.
- The real allocation size of the receiver object; 0x84 is only the modelled prefix through the written slot.
- What is the field at receiver+0x80 in the real UTFWin::Window layout, what writes it besides this function, and what reads it afterwards?
- What receiver vtable displacement do the containing tables imply for the receiver, and is the receiver polymorphic at offset 0x00?
- Whether the SDK name IsAncestorOf is misassigned to this slot, or whether the slot really is an ancestor query whose decision was optimised away / supplied elsewhere. The body cannot distinguish the two.
- Which concrete classes and runtime windows reach this slot, given that no direct caller exists?
- Which table owns each of the 33 function words, at which slot index, and are the 0x30 and 0x54 displacements real slot positions or an artifact of the triage scan?
- Why 33 distinct vtable images point at the same slot, and whether they belong to one class or to several related types; SporeApp.exe has no MSVC RTTI to settle it.
- Why does the SDK name IsAncestorOf and a bool return contradict a body that only stores its argument? The ModAPI import may be offset, and sibling exports show the same pattern, but the correct name and signature are unresolved.
- confirm the class identity behind the 33 vtable images; the binary has no MSVC RTTI
- observe one real virtual call through a slot +0x00 word and record whether the caller consumes AL, which would settle the void-vs-bool return type
- record the receiver allocation size at runtime; the 0x84 byte modelled extent is only the prefix through the written slot
- record the value stored at receiver+0x80 and find its consumer, to establish whether the SDK name IsAncestorOf is misassigned
