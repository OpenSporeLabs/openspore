# Validation 0x00642700

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00642700/sw2_00642700.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 114-instruction listing name the same 2 direct transfer target(s); 4 intra-procedural jump(s) target inside the recovered body span 0x00642700..0x00642831 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x0064274c, 0x00642781, 0x006427b6, 0x006427eb; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 10 outgoing call edge row(s) over 2 distinct address(es) for 0x00642700; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 114-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 114-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x4, 0x8), all of which the record accounts for or the listing is the better witness on; the 114-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=114, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x4, 0x8) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x8), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (114 of 114 instruction(s), 0 unparsed) and all 5 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 11 conditional branch target(s) in the complete 114-instruction listing lie inside the recovered body span 0x00642700..0x00642831, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 114-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `d1c819729714e0d6ce4b877b59e960b75d60dcb74a9262cc5e107096cbab8fcc`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f8a2ef8cf86797088cff885858b6042ea7506a8b0f90e854753237c6ac852d3a`
- Pack digest quoted by the briefing: `d1c819729714e0d6ce4b877b59e960b75d60dcb74a9262cc5e107096cbab8fcc`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is 0x00642700 a virtual function with any DIRECT caller at all? The record carries seven data-side xrefs, all of which are this body's own address inside twelve tables, so the entry is a virtual function; no direct-call xref is recorded in either direction. Whether some other image, a mod, or a vtable reached only at run time calls it directly is not established here.
- Is the caller-visible destruction of the argument slot load-bearing? On any path that reaches 0x0064275d this body overwrites the caller's own argument word (entry+4) with a lookup result -- the vector pointer the caller pushed is destroyed. The argument is dead to the body, but a caller that read its own argument slot back would see a lookup result. No record establishes whether any caller does, and the model does not assert the machine's slot aliasing at all (see mechanics.frame_resolution.value_slot_is_not_constant).
- The canonical ABI record's return claim is the machine-vocabulary string 'integral_in_EAX' (abi.return_semantics; abi_derived inference RT2 register_class 'integral'), and the ghidra_function record says return_type 'undefined' with return_type_resolved false. The listing writes only AL, so this package declares bool -- the width the machine fixes -- which is option (a) of the wave-1 guidance. The consequence is that RETURN SEMANTICS compares the strings 'bool' and 'integral_in_EAX' and WARNs, and no honest declaration can make that comparison succeed. Declaring void is not available (three instructions produce a value) and inventing a typedef named after the machine phrase would be a validator hack, so the WARN is reported and not chased. This is the package's only structural WARN.
- The committed record annotates its single stack argument 'read: false'. The byte walk puts the read at 0x0064271e, MOV ESI,[ESP+0x18] with ESP = entry-20, i.e. entry+4, which is the record's own slot. So the slot is right and the read flag is what a linear walk could not see. If a downstream tool relies on that flag it will conclude the body never touches its argument, which is false.
- The committed record's abi.abstained_because gives two reasons not to trust its own argument analysis -- 'flow_not_modelled: the linear ESP walk ends at +24, so the listing is not one path' and 'sret_vs_out_param: entry slot 0 is written through a pointer' -- and the byte walk here resolves both. It is worth recording that they are resolved by WALKING each callee's own terminator rather than by the listing alone: with 0x004558a0's `RET 0x8` counted as 12 bytes net (return address plus two words) rather than 8, the frame drifts four bytes per reallocation and never balances, which reproduces the record's +24. Anyone re-deriving this frame should use mechanics.frame_resolution.settled_callee_effects, which is the part that is easy to get wrong.
- The three appends' and five appends' frame slots mean the body reuses its own argument word as a scratch register, which is legal for the callee but is a fact about the CALLER's stack that a caller with a live argument slot would notice. Combined with the previous item this is the one place where a faithful reconstruction of the body could differ observably from the original in a way a caller could observe, and it is left unmodelled on purpose.
- What 0x2b978c46 IS, is not established. It is the word at the receiver's +0x08, the second word of the two-word descriptor at the receiver's +0x04, and 0x00556140 checks it (0x00556150) before doing anything. That 0x00556140 accepts a SECOND identity, 0x3d97a8e4 (0x0055615c), which this body never tests, means the receiver is one of at least two flavours and this body is flavour-specific -- but no record in this repository says what either literal denotes, and nothing is claimed.
- What the ARGUMENT OBJECT is is not established beyond its two reached words. This body reads a cursor at +0x04 and a capacity at +0x08 and advances the cursor by 4 bytes; 0x004558a0's own body reads and writes +0x00, +0x04 and +0x08 of it and rebuilds the capacity from a 0x14 divide. That is the layout of a growable sequence of 4-byte elements and it is very likely a std::vector<unsigned int>, but the model deliberately does not say so: this binary has no MSVC RTTI, the record's types category is unavailable, and naming a container would be a claim no record carries. The stride is fixed as 'the amount 0x00642731 adds', which is 4 bytes; the element-count arithmetic that corroborates a 4-byte ELEMENT is the callee's, not this body's.
- What the class actually is. The Sporepedia association is real (twelve tables, and the tables at 0x013ff648, 0x013ff6ac and 0x01462764 are the same ones the record names as the match basis for eight reconstructed neighbours the research queue names Sporepedia::cSPAssetDataOTDB::*) but the record's own class_type is null and the name is not written anywhere in this package. The header spells the types Sporepedia* and stops there.
- What the five literals are is not established either. They are passed one per call to 0x00556140, which uses the second argument in a linear search (0x005561b9..0x005561ef) comparing each candidate against it (0x005561e2), so they behave as lookup KEYS. Whether they are Sporepedia type-property ids, hash values, or the low 32 bits of string ids is not established, and the model claims only that five distinct 32-bit literals are passed in a fixed order.
