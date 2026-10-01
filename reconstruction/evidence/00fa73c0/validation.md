# Validation 0x00fa73c0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00fa73c0/sw1_00fa73c0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 46-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00fa73c0; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 46-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 46-instruction listing nevertheless reaches 5 receiver displacement(s) through ECX (0x28, 0x20c, 0x798, 0x79c, 0x814), all of which the record accounts for or the listing is the better witness on; the 46-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=46, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 5 displacement(s) to the receiver as proven (0x28, 0x20c, 0x798, 0x79c, 0x814) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 5 displacement(s) (0x28, 0x20c, 0x798, 0x79c, 0x814), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (46 of 46 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 46-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 46-instruction body names 3 indirect transfer(s): 0x00fa7408 dispatches slot 0x18 through the table word in EDX; 0x00fa7417 dispatches slot 0x18 through the table word in EDX; 0x00fa7426 dispatches slot 0x18 through the table word in EDX; the machine parse consumed 46 of 46 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 3. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `a192d5012ba262232cd756dda90fd6bb9a494179d71cb9828d3f77eff1a0ea34`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6554538c6cc725ca787200e9fe3d4568563dbbd43c95f6cdb778aa213a0ea6d9`
- Pack digest quoted by the briefing: `a192d5012ba262232cd756dda90fd6bb9a494179d71cb9828d3f77eff1a0ea34`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the words at receiver+0x798 and +0x79c pointers, indices or counts? This body only ever forms their difference and hands them to 0x00f9f770 as opaque words, and 0x00f9f770 never dereferences them on the path this caller forces. 0xac appears both as that callee's stride and as this body's multiplier, which is suggestive of a 172-byte element size, but nothing here fixes what the words point AT. The model deliberately plants non-dereferenceable values so that any reconstruction which invents a dereference fails its own test.
- Is 0x00f9f770's degenerate call dead source, a debug leftover, or a call that was meant to be non-degenerate? This caller provably passes the same word as both range ends, so the callee's loop and its 0x00f9f620 call never run. Whether that is a bug, an intentional no-op, or the residue of a refactor is not determinable from the bytes, and the model reproduces the call exactly as the listing has it rather than deleting it.
- No record establishes who calls this body. ghidra_function.xref_count is 1 and that single xref is the vtable slot's storage at 0x01490c58; callers_dependencies is unavailable and dependencies.callers is empty. So the return value's fate and the expected receiver state are both unconstrained by anything in this repository, and the runtime gate below is written without assuming either.
- The three records disagree about the return type, and the disagreement is not fully resolvable from the bytes. abi.return_semantics is 'unclassified_in_EAX', abi_derived.return.void_possible is false with register_class aggregate_unknown, and ghidra_function.return_type is the unresolved string 'undefined'. The listing shows no write of EAX for the caller after 0x00fa741e, so this package declares void and records the EAX residue explicitly rather than picking one record silently. If the parent validator's RETURN SEMANTICS check compares against 'unclassified_in_EAX' rather than against a concrete type, a WARN there is expected and is a statement about the records rather than a defect in the source.
- What class is this, and what are its members? The table at 0x01490be8 has this body at its displacement +0x70, and the target's own analogue record names the function at that table's slot +0x08 (0x00641770) Sporepedia_cSPAssetDataOTDB_HasName_raw_00641770 from package PKG-16-SPOREPEDIA-ONLINE. That is suggestive of a cSPAssetDataOTDB-shaped class, but a name read off a sibling slot is not a name this body's evidence carries, so no class is declared and the model names no member. Settling it needs a body that reads a word at the receiver's own +0x00; this one does not.
- What do the three dispatched immediates mean, and is the sub-object's one-argument callee-cleaned slot a setter, a log call or a notification? The immediates 0x0536250c, 0x0536250d and 0x03a23f9a are used at five, five and three other sites in .text, so they are shared IDs, but nothing in this repository names any of them. The callee's own shape -- one stack word, callee-cleaned, thiscall on the sub-object -- is fixed; its meaning is not.
- What is the object at receiver+0x28, and what is its table? The body resolves *(*(receiver+0x28)) + 0x18 three times and never looks inside. It is NOT the table at 0x01490be8 -- see mechanics.virtual_dispatch.not_this_table, where the slot +0x18 entry of that table is shown to be a zero-argument getter that could not survive the call site's stack balance. Establishing the real table needs a body elsewhere that constructs that sub-object.
- abi_derived.abstained_because records 'flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path', and abi_derived.parse.flow_complete is false. That is a limitation of the tool's walker across the three indirect calls, not a property of the body: the explicit ledger in mechanics.frame_ledger walks all 46 instructions and balances exactly. The tool's abstention is reported so the parent can see that the two are not in conflict.
- abi_derived.dispatch.vtable_shaped_loads is 0 while the listing plainly contains a two-level load-and-index chain and three indirect calls. This package follows the listing. If the validator's VIRTUAL DISPATCH check is driven by that field rather than by the listing, the detail text may understate what the source claims; the model declares the slot displacement as a named constant and names no class, table or member, so the source side is the narrower one.
