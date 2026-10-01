# Validation 0x005c5ee0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-orchestrate-dogfood-005c5ee0/dogfood_005c5ee0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x005c5ee0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x005c5ee0..0x005c5efb, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a50c758fe8c544353e6ac7f6daad2b209c0e0a2ba806aa21923b0684ed18f565`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a954aa6cb4d39cdcd150f33d61f1a6725c078ea19f32df620082086be87862f5`
- Pack digest quoted by the briefing: `a50c758fe8c544353e6ac7f6daad2b209c0e0a2ba806aa21923b0684ed18f565`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.`, `Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.`, `Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.`, `Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.`, `Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.`, `Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.`, `Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the returned EAX be a released pointer in the original program, and does any caller use it after the release?
- Capture both stack-word polarities at a real call site and confirm that only bit 0 decides the release.
- Confirm the returned EAX is the receiver word on the release path, where the receiver has just been handed to the release wrapper.
- Determine the class and base-subobject binding of the vtables at 0x013f7fd4 and 0x013f7fc4, and the role of the word at 0x013f7fd8.
- Is the entry a deleting destructor, a hand-written release wrapper, or an accessor that the SDK symbol importer mislabeled? The machine mechanics are identical in all three cases, so the classification is unresolved.
- Observe 0x005c5e90 live: its loop, the callees it invokes, and the values of the words it reads at receiver+0x04 and receiver+0x0c.
- Observe a real virtual dispatch through the word at 0x013f7fd4 and through the subobject slot at 0x013f7fcc, and record which of the two produced the entry call and with which receiver word.
- Record the receiver words at +0x00, +0x04 and +0x08 before and after the call and confirm that the entry itself leaves all three unchanged.
- Resolve whether the original source identifier, argument name, and return type match the imported SDK label or the destructor-shaped reading of the body.
- The briefing carried no ABI section (evidence.missing_sections listed ABI), so the recorded ABI is derived from the eleven-instruction disassembly plus read-only live Ghidra queries; a repaired calling convention in Ghidra should confirm it.
- The briefing vtables evidence recorded vtable:0x013f7fc4 while the live file image stores 0x005c5ee0 at 0x013f7fd4. Which of the two records is authoritative for the triage ledger, and does 0x013f7fc4 need a correction?
- The live Ghidra signature is (PaletteMain * this, uint32_t categoryID) returning PaletteCategory*, but the decompilation carries the warning 'Unknown calling convention' and renders the return as a synthetic in_ECX. The disassembly proves the return register is EAX and that EAX holds the receiver, so the recorded return type is the receiver word rather than the imported PaletteCategory*.
- What class owns the vtable at 0x013f7fd4, what does the adjacent word 0x013f7fd8 = 0x00804901 represent, and why is it one byte into the 0x00804900 thunk?
- What do the words at receiver+0x04 and receiver+0x0c that 0x005c5e90 reads and subtracts represent, and what type do they hold?
- What is the argument really named and typed in the original source, given that only its low byte is read?
- What is the receiver's full layout and allocation size, and can a null receiver ever reach this entry in the original program?
- Which base subobject does the table at 0x013f7fc4 belong to, and what do its four thunk words do besides the -8 adjustment?
