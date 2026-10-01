# Validation 0x0067e6b0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-cheat-func3ch-0067e6b0/cheat_func3ch_0067e6b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x0067e6b0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x0067e6b0..0x0067e6cb, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'CheatManager*' and the machine return state is WIDTH_4_IN_EAX: the complete 11-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d591fe6114dac04f7213080110838fdb675bdafdfd3343d4fedecb00e45c73b8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `5408de168604d77d154a6cf19e7f81042b322f124362da008bf5b41a7187b23b`
- Pack digest quoted by the briefing: `d591fe6114dac04f7213080110838fdb675bdafdfd3343d4fedecb00e45c73b8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `The branch is inert unless the gate word has bit 0 set; a differential run that passes an even word will exercise only the teardown path.`, `The function is only reachable through vtable slot 20, so observing it at all requires a live cCheatManager constructed by 0x0067e100 (which stores 0x014018b0) and a caller that dispatches that slot.`, `The teardown path requires receiver+0x14 to be non-null before the indirect call at 0x0067e2e1 can happen at all.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the branch ever be taken as not-taken in the original process? runtime_metadata.gates says the branch is inert for an even gate word and that the function is only reachable through vtable slot 20. No trace exists in this repository, so this is unresolved rather than answered.
- Is 0x0067e2b0 a destructor? It calls vtable slot +0x10 of the object at +0x14 and then writes &PTR_purecall_0141b5ac into the receiver, which is the MSVC vptr-reset shape a base destructor performs, but the listing names nothing and the only inbound reference is this call site.
- Is 0x0067e2b0 a destructor? It calls vtable slot displacement 0x10 of the object at receiver+0x14 and its tail target writes &PTR_purecall_0141b5ac into the receiver, which is the MSVC vptr-reset shape a base destructor performs. Nothing in the listing names it and this package does not claim it.
- Is the returned EAX consumed by anyone? The only inbound reference is the vtable slot at 0x01401900 and no call site of that slot is known.
- Is the returned EAX consumed by anyone? The only inbound reference to the function is the vtable slot at 0x01401900, and no call site of that slot is known.
- The branch is inert unless the gate word has bit 0 set; a differential run that passes an even word will exercise only the teardown path.
- The function is only reachable through vtable slot 20, so observing it at all requires a live cCheatManager constructed by 0x0067e100 (which stores 0x014018b0) and a caller that dispatches that slot.
- The teardown path requires receiver+0x14 to be non-null before the indirect call at 0x0067e2e1 can happen at all.
- What are the non-code words 0x00ff0420, 0x00fcc210 and 0x00ab30c0 doing in slots 7, 12 and 9 of that table?
- What are the two import slots 0x013cc2d8 and 0x013cc2dc? The database resolves no external location for either, so no API name is claimed.
- What are the two import slots that the third hop (0x009276c0, reached from 0x00f47380) calls around the INC/DEC of [lock+0x18]? The database resolves no external location for either, so no API name is claimed -- and this package does not model that hop at all.
- What does the gate word mean beyond bit 0? The listing tests one bit and says nothing about the other 31, and neither callee is handed the word, so its meaning cannot be read from this body at all. Only its producer could say.
- What does the gate word mean beyond bit 0? The listing tests one bit and says nothing about the other 31, and the two callees receive the receiver rather than the word, so the word's producer is the only place its meaning could be read.
- What is 0x00926fd0, the routine 0x009276c0 brackets with the lock at global+0x4e4, and what does it do with the receiver it is handed?
- What is the correct persisted return type? The machine writes the receiver into EAX on its only exit, and the SDK/Ghidra prototype declares void. This package follows the machine and records the contradiction; an integrator with a consumer in hand could settle which one the caller actually relies on.
- What is the object at receiver+0x14, and what does its vtable slot +0x10 do?
- Which class owns vtable 0x014018b0, and is it related to the 0x01401b74 table that holds the sibling entries 0x0067e6f0 and 0x0067e730? Nothing here establishes it: the table mixes code and non-code words and the binary has no RTTI.
- Which class owns vtable 0x014018b0, and is it related to the 0x01401b74 table that holds the sibling entries? The table mixes code and non-code words and SporeApp.exe has no RTTI, so the hierarchy is not established.
