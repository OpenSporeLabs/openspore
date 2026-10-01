# Validation 0x00f999e0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00f999e0/sw2_00f999e0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 80-instruction listing name the same 2 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00f999e0..0x00f99ab3 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00f99a40; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00f999e0; the source span names 2 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 80-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 80-instruction listing nevertheless reaches 0 receiver displacement(s) through ECX (none), all of which the record accounts for or the listing is the better witness on; the 80-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=80, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 0 displacement(s) to the receiver as proven (none) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 11 displacement(s) (0x0, 0x370, 0x434, 0x438, 0x43c, 0x440, 0x494, 0x498, 0x49c, 0x4a0, 0x4f4), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 11 of those (0x0, 0x370, 0x434, 0x438, 0x43c, 0x440, 0x494, 0x498, 0x49c, 0x4a0, 0x4f4) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (80 of 80 instruction(s), 0 unparsed) and all 2 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 13 conditional branch target(s) in the complete 80-instruction listing lie inside the recovered body span 0x00f999e0..0x00f99ab3, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 80-instruction body names 2 indirect transfer(s): 0x00f99a00 dispatches slot 0x4c through the table word in EAX; 0x00f99a15 dispatches slot 0x30 through the table word in EAX; the machine parse consumed 80 of 80 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x30, 0x4c, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `28680085b963bcd947bc5968062de1c305202bd3e1849a3a553a8d3715799404`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `308d1121a3072a3a4c79bcce6332493b71c6f6c13ea6865e57a406056b7be699`
- Pack digest quoted by the briefing: `28680085b963bcd947bc5968062de1c305202bd3e1849a3a553a8d3715799404`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- DUPLICATE-OWNERSHIP CHECK NOT PERFORMED WITHIN BUDGET: I did not sweep reconstruction/metadata/ for another sidecar claiming 0x00f999e0. The existing_reconstruction block of my briefing reported files [], handoffs [] and metadata [], which is the pack's own view and is not the same as a directory sweep. The integrator should confirm this VA is singly owned before promotion, the way pkg-dfw-006a2e20 records for 0x006a2e20.
- RETURN SEMANTICS: the machine record and the listing still disagree, and this package cannot settle it -- it can only say which of the two is wrong. abi.return_register is "XMM0" with return_semantics "float_or_x87_in_XMM0" (APPROXIMATION, inference RT1: "an x87 or SSE instruction appears in the body"), and that is a REGISTER-CLASS CLASSIFICATION, not a C type. The listing refutes it on every count: XMM0 is written by the six MOVSS and read by the six UCOMISS and holds nothing on any exit; the three exits write AL only (XOR AL,AL at 0x00f999f3, MOV AL,0x1 at 0x00f99aab, XOR AL,AL at 0x00f99ab0); and no instruction in the 80 writes the other three bytes of the return register. So RT1 is a PRESENCE test over an SSE mnemonic firing on a body that uses SSE only to compare, and whether that rule should be narrowed is a question for the ABI layer, not for a reconstruction. This is why the machine-evidenced width route cannot arbitrate either: evidence_returns.classify over this body's own record returns state UNCLASSIFIED with the reason "the ABI record names XMM0 as the return register; an SSE register: the machine fixes where the value travels and not whether the source said float, double or a vector, so no width can be claimed" -- so the strict route would have reported NOT_AVAILABLE, which says less than the one-byte width the listing actually proves. The repair (rp10) therefore did the only honest thing available: abi.return_type states the type the source span declares and the listing proves, std::uint8_t, and the phrase is preserved verbatim in abi.return_semantics with the refutation in abi.return_note. It relocated the claim; it did not resolve it. A reader who wants the machine layer corrected rather than relocated should take this item to abi_infer's RT1 rule, and a reader who wants the record amended should take it to whoever owns the persisted abi for this VA. No typedef named after the phrase was written and none may be added.
- The two float compare flags depend on the FPU/SSE control state, which this body never writes but does not read either. It contains no LDMXCSR and no MXCSR read, so the default state (denormals-are-significants, exceptions masked) is what its UCOMISS results assume. Whether the process running this code had changed MXCSR beforehand is not determinable from this body and is not claimed. The model test's two discriminating cases (+0.0f against -0.0f, and a quiet NaN against its own bits) are both independent of that state, which is why they are the two that are driven.
- What the twenty-four groups MEAN is not established and is not claimed. The receiver record is bounds_only, no member is named, and nothing in this body or in any record for this target says what a four-float group at receiver + 0x374 + 0x10k is for. The layout, the stride, the two-pair shape and the ordered-equality test are all fixed by the listing; the meaning is not. The 0x00f699b0 listing in mechanics.group_layout_corroboration shows the same layout on a different object, which is a fact about the layout and not about the meaning.
- What the two flag bytes at the receiver's +0x370 and +0x4f4 represent is not established. The record enumerates their displacements and bounds_only forbids naming them, and this body only tests them for zero. 0x00f699b0's own per-iteration flag gate has the same shape at its receiver's +0x78, which suggests a family of flag bytes across related objects, but that is a different listing and it is corroboration of SHAPE and not of meaning.
- Whether the +0x4c selector is read as a BYTE or as a full DWORD at run time is not established. This body pushes 0x7 as a dword, and the table's own +0x4c entry reads it as a byte with `MOV DL,[ESP+0x4]`; an override could read all four. The model declares it `std::uint8_t` because that is what the entry in this class's table does, and because nothing above 0x7 is observable through it in any case.
- Whether the RUNTIME object holds 0x00fa0e60 at slot +0x4c and 0x00fa0d80 at +0x30 is not established. Those are the entries the class table at 0x01490be8 holds in this image, and they are what the two `RET` forms were read from, but a derived class may override either slot and nothing in this body or its record says which class the runtime object is. The reconstruction calls through the receiver's own +0x00 for exactly this reason. Consequently the WIDTH of either slot's return value is not statically knowable: 0x00fa0e60 zeroes EAX before its SETNE so its high bytes are 0, while an override is unbounded -- which is why the model treats the slot's return as a full word and masks the high 24 bits for the dead-word channel rather than asserting a width.
