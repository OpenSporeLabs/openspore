# Validation 0x005a2ed0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-005a2ed0/sw2_005a2ed0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 22-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x005a2ed0; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 22-instruction listing names 6 data address(es) (0x13eb394, 0x13eb938, 0x13ef094, 0x13f69b4, 0x13f69b8, 0x13f69c8) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 22-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 22-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=22, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x0, 0x4, 0x8, 0x10), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 3 of those (0x4, 0x8, 0x10) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (22 of 22 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 22-instruction listing lie inside the recovered body span 0x005a2ed0..0x005a2f1c, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 22-instruction body names 1 indirect transfer(s): 0x005a2ef3 dispatches slot 0x4 through the table word in EAX; the machine parse consumed 22 of 22 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 6 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x4, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ae7b18925be93d0121c00719d869992e4ea0f0df21c10797b1b63cfb21afa8b9`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `a64d4f52658336ca53cca8bd1f987780e9099d3e6adb3c8b26ff3a0880f4eef1`
- Pack digest quoted by the briefing: `ae7b18925be93d0121c00719d869992e4ea0f0df21c10797b1b63cfb21afa8b9`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `RUNTIME is GATED: the OpenSpore original has never been executed in this repository, so no runtime claim of any kind is made for 0x005a2ed0. A differential test would need a driver, and the single recorded caller (0x005a2320) is a two-instruction receiver-adjustor thunk that tail-jumps here rather than calling it.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- RETURN SEMANTICS: the machine ABI envelope's own return token is the machine phrase `unclassified_in_EAX` with register_class `aggregate_unknown`, and no C++ type can equal it. The listing independently fixes the returned value as the receiver pointer (MOV EAX,ESI at 0x005a2f19, unconditional, the last write to EAX before the sole RET 0x4 at 0x005a2f1c, with ESI the entry ECX since 0x005a2ed1), and the sidecar publishes that as observed_original_abi.return_type. So the canonical record and the source agree, but that agreement is between a LISTING-DERIVED claim and a source declaration, not between two machine observations: the machine envelope classifies nothing here. The claim to review is the envelope's, and this package did not override it -- it published its own reading beside it.
- RUNTIME is GATED: the OpenSpore original has never been executed in this repository, so no runtime claim of any kind is made for 0x005a2ed0. A differential test would need a driver, and the single recorded caller (0x005a2320) is a two-instruction receiver-adjustor thunk that tail-jumps here rather than calling it.
- The class of the object the word at receiver+0x10 points to is not established, and neither is the class of the table its +0x00 names. The single recorded caller, 0x005a2320, is a two-instruction receiver-adjustor thunk (SUB ECX,0x4 / JMP 0x005a2ed0), so the receiver here is a subobject pointer rather than a complete-object pointer, but the subobject's own layout past its +0x00 word is not observable from these twenty-two instructions and none is declared.
- The indirect callee at the table's slot 0x04 is not identified. It is reached only through a table word, its own bytes are not in this package, and the body establishes no stack word for it, so neither its signature beyond the receiver nor its callee-cleanup obligation can be read from here.
- The meaning of bit 0 of the stack argument is not established. The body tests it and branches on it, and the shape (install two vtable triples, conditionally free the object, return the receiver) is the MSVC deleting-destructor idiom, but that is an INFERENCE from the shape and not a symbol, a string or a type in this image. What is asserted is only the machine behaviour: bit 0 set means the deallocation call is made.
- What the six .rdata immediates ARE is not established. The record associates this VA with vtable:0x013f69b4, which is the third of them, and the image corroborates the other three as table heads (the word at 0x013eb938 is 0x011e06d0, named `purecall` by Ghidra; the words at 0x013eb394 and 0x013ef094 are the code addresses 0x00404430 and 0x0041d780). No class is identified, because SporeApp.exe carries no MSVC RTTI, and no member is named for any of the three receiver displacements those addresses land in.
- Whether 0x00f47380 is the C++ `operator delete` is INFERRED from its own seven bytes (read one word, null-test it, forward through the global at 0x016c8b44 to 0x009276c0) and from this body's shape. The package names its extern `deallocate_00f47380` rather than claiming the language symbol, and no string or symbol in this image establishes the identity.
