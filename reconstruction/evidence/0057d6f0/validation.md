# Validation 0x0057d6f0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-editor-w1-0057d6f0/editor_w1_0057d6f0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 11-instruction listing name the same 2 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x0057d6f0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 11-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 11-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (11 of 11 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 11-instruction listing lie inside the recovered body span 0x0057d6f0..0x0057d70b, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 11-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'Receiver*' and the machine return state is WIDTH_4_IN_EAX: the complete 11-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d517f88a7bd13c7441a255bfada0c7fdcfd1a971da67c4ee6d6aec42748a62c3`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `bc738f10de057d84d17f5ef933afeb0a8e0891b4143f5ea9e26cf9acc016100c`
- Pack digest quoted by the briefing: `d517f88a7bd13c7441a255bfada0c7fdcfd1a971da67c4ee6d6aec42748a62c3`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `runtime validation not run: no original-process trace exists in this repository, so nothing about the original game has been observed for this VA`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Runtime. No original-process trace exists in this repository for this target, so nothing is claimed there. The gate is open, nothing was attempted, and nothing failed.
- The decompiler did not run for this target: the collector recorded ghidra_rest_error 'decompile 0x0057d6f0 failed: Decompilation did not complete', and 0x00579e20 and 0x00f47380 also fail to decompile through the bridge. Every claim above is therefore from the disassembly, the raw bytes and the xref export, never from pseudocode.
- The option word's meaning, and the 31 bits this body never reads. Bit 0 selects the dispose; nothing in these 11 instructions says what a set bit 0 means, and no caller is statically visible (all four references are a table slot and three stubs), so no call site supplies a value to read the meaning from.
- The receiver's identity. Whether the incoming ECX points at the head of an object or at one of at least three interior sub-objects is not determinable from this body: it neither dereferences the pointer nor adjusts it, and the stubs that reach it adjust by 0x10, 0x14 and 0x4, so at least three base-subobject displacements are in play for the same virtual. Which class, and whether the three stubs are one class's three bases or three classes' thunks, is not decided here and this binary carries no MSVC RTTI to decide it.
- Whether the INFERRED convention is the right one in an absolute sense. The derived record DETERMINES __thiscall (rule R1-VFT for the receiver, rule C6B for the convention) and this package carries that determination verbatim; it does not claim more than the record. What is not settled is anything the record itself does not cover: no caller dispatching through the table at 0x013f57f8 has been observed in this repository, so the confidence stays INFERRED and is carried as such in observed_original_abi.calling_convention_confidence. A concrete caller-side observation (a run-time trace, or a caller other than the three this-adjusting stubs) would move this from inferred to observed, and nothing here pretends otherwise.
- Whether the class this body belongs to has a name in the SDK. The triage record associates the table vtable:0x013f57f8 with six other addresses in package PKG-EDITOR-INPUT-WAVE6, and ghidra_function reports sdk_name null and sdk_associations []. No name is asserted.
- Whether the receiver record can ever enumerate an offset for this body. abi_derived.receiver is now present and names ECX, so the validator CAN scan the listing under that register -- and the scan finds nothing, because the eleven instructions contain no displacement through ECX at all. That absence is the honest answer and is now adjudicated (FIELDS/OFFSETS passes on the register-agnostic absence arm, over the complete 11-instruction parse). What remains open is the other direction: this body can never GROW a field claim from its own bytes, and any offset a future reader wants to attribute to the receiver has to come from a callee or from a class analysis, neither of which is imported here. Note also that the body's one memory operand, the stack-argument byte read at [ESP + 0x8], is based on ESP and is not a receiver access at all.
- runtime validation not run: no original-process trace exists in this repository, so nothing about the original game has been observed for this VA
