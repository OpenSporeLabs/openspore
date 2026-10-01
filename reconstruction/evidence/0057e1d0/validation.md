# Validation 0x0057e1d0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-0057e1d0/sw1_0057e1d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 23-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 1 distinct address(es) for 0x0057e1d0; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | 2 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 23-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x4, 0xc, 0x14), all of which the record accounts for or the listing is the better witness on; the 23-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=23, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x4, 0xc, 0x14) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 4 displacement(s) (0x0, 0x4, 0xc, 0x14), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x0) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (23 of 23 instruction(s), 0 unparsed) and all 8 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 23-instruction listing lie inside the recovered body span 0x0057e1d0..0x0057e210, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 23-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `53ca4e8d108b611a2b650240747a38643a31347d18d02821cbec50d4b2c648ff`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `194934289fe1a3bbb932b51cae21e48a3feeaffe2a25c3a47012a23f71e5a501`
- Pack digest quoted by the briefing: `53ca4e8d108b611a2b650240747a38643a31347d18d02821cbec50d4b2c648ff`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- CAN A NON-THUNK CALLER REACH THIS BODY. The xref export records exactly one reference and it is the 0x0057a703 jump. A class whose vtable lists 0x0057e1d0 at 0x013f5868 would reach it through an ordinary indirect call with `this` equal to whatever the vtable's owner offset says, and whether that equals the complete-object pointer or the same pointer-minus-four is a property of the class graph this repository cannot supply. The model reconstructs 0x0057e1d0 as entered, and the thunk relationship is stated as the one caller edge that is proven.
- HOW MANY SLOTS EACH STORED TABLE HAS, AND WHICH CLASS IT IS. Established: both are dispatch-table addresses (evidence.vtable_note). Not established: slot counts, owning classes, and whether 0x013ef094 is a base of 0x013eb938 or of something else. Both tables carry hundreds of destructor-shaped references, which is what a deep hierarchy looks like, and that is as far as the evidence in this repository goes.
- IS IT THE SCALAR DELETING DESTRUCTOR, AND OF WHAT. The shape -- two dispatch-table stores, a conditional release of the receiver, the receiver returned -- is the MSVC scalar deleting destructor idiom exactly, and the 0x0057a700 adjusting thunk is what a shared-base destructor entry looks like. But that is an INFERENCE from the shape. This binary has no MSVC RTTI (AGENTS.md records that, and the vtable pass never ran headless), so there is no complete-object-locator column to read, and no record names the class. What the model asserts is only the four instructions' observable effect.
- THE IDENTITY OF 0x00f47380. The bridge's decompilation of it FAILED ('Decompilation did not complete'), so nothing about it comes from a decompiler. Its own seven bytes fix one stack word, a null-tolerant early return, a global service pointer at 0x016c8b44 and a call to 0x009276c0. That it is a release operator is INFERRED from the shape and from this body using it on both a sub-buffer and the object itself; no record names it. Its callee 0x009276c0 and its global 0x016c8b44 were not investigated and are not claimed.
- WHAT CLASS IS THIS. Nothing in the machine identifies it. The record carries sdk_name null, sdk_type null, namespace null, subsystem null, and ghidra_name is the auto-generated FUN_0057e1d0. The six analogues are all named editor_input_* by their own packages, and this body shares their table at 0x013f57f8, so the family is EditorInput-shaped, but a shared table entry is not a class identity and this package asserts no class name. Settling it needs the ModAPI type that owns 0x013f57f8, which is not in this repository's evidence.
- WHAT THE PAIR AT +0x0c AND +0x14 MEASURES. The body takes their difference, clears bit 0, and compares it signed against 2. The mask is a rounding to even, which is the shape of a byte count, but nothing here divides the difference, no element size appears, and no record says what the pair holds. Calling it a count, a byte length, a pointer pair or a vector is all speculation; the model reproduces the arithmetic and stops.
- WHAT WRITES 0x01667BAC AND 0x01667BAE. The matching constructor at 0x0057a6d0 puts them at the receiver's +0x0c, +0x10 and +0x14 -- the very words this body compares and releases -- and they are adjacent bytes in .data (0x01667bac and 0x01667bae are two apart), so the pair looks like two bytes of one four-byte constant stored as two dwords. Nothing this body reads settles what they are, and this package models nothing from the constructor.
- WHY THE COMPARE IS SIGNED. The opcode settles that it is (0x7E), and the decompiler's unsigned C rendering is the discrepancy. Whether the ORIGINAL SOURCE wrote a signed comparison deliberately, or whether the compiler emitted JLE for a source-level `unsigned` test by sign-extending something first, cannot be recovered from three instructions -- and it matters, because on a wrapped negative span the two readings differ. The model follows the opcode, which is the only defensible reading, and flags the gap rather than resolving it.
