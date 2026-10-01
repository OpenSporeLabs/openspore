# Validation 0x00641fa0

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-00641fa0/sw1_00641fa0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 22-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00641fa0; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 22-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 22-instruction listing nevertheless reaches 3 receiver displacement(s) through ECX (0x0, 0x4, 0x1c), all of which the record accounts for or the listing is the better witness on; the 22-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=22, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 3 displacement(s) to the receiver as proven (0x0, 0x4, 0x1c) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x1c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (22 of 22 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 22-instruction listing lie inside the recovered body span 0x00641fa0..0x00641fcd, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 22-instruction body names 1 indirect transfer(s): 0x00641fc0 dispatches slot 0x68 through the table word in EDX; the machine parse consumed 22 of 22 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 13 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary but states no slot displacement this parser can read, so the two claims are reported separately: the machine dispatch is proven, and the source's own slot naming is NOT verified by this check |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `ddd80a7ac65579f7ff69ad624589f3ea13a9facb5070475cd17318ef7a89107b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `c5c79510c73ae1429c2bbb5b661624fce26037f2ab189d37f56b85391329dfe5`
- Pack digest quoted by the briefing: `ddd80a7ac65579f7ff69ad624589f3ea13a9facb5070475cd17318ef7a89107b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The semantic name of the predicate. The shape -- three inputs, one direct callee, one virtual slot, a null-ness gate -- is fully reconstructed, but nothing in the evidence says what question the boolean answers. 'IsEditable' is the name the repository gives the neighbour at 0x00641400 and the shapes differ; it is deliberately NOT borrowed here.
- What the 0x0c sub-object at receiver+0x04 is, and what 0x00641900 decides. This package fixes only that the callee is handed its address, reads the dwords at +0x00 and +0x08 through it, and returns a byte. 0x00641900's own body is 88 instructions long, has one direct call of its own (0x0067dcd0) and two levels of virtual dispatch, and is not this worker's target; it is unowned here.
- What the dword at receiver+0x1c IS. The body compares it against zero and never dereferences it, so it is a null-ness gate on a word whose type, ownership and producer no record for this VA establishes. It is modelled as an opaque Word and nothing more. Naming it (a handle, a flag word, a version) would be a member story the listing does not carry.
- Whether a live receiver is ever dispatched through the four-slot table at 0x013ff6ac, in which this body is index 3. If it is, the index-0x68 word this body loads is data past that table rather than one of its slots. The two larger tables show real content at index 26, so the two-level load is not in doubt; what is open is which table a given receiver carries.
- Whether the class name Sporepedia::cSPAssetDataOTDB applies to THIS virtual. It applies to the eight neighbours that share the vtable family and to the family as a whole, but this body is one of seven xref'd slots in seven different tables and a virtual's declaring class is fixed by the table it is called through, which is not established here. The type name in the header is labelled INFERRED for that reason.
- Whether the machine's own return classification should ever be spelled as a type, and the answer for this VA is NO. The record's register-class phrase is 'byte boolean, normalised to {0, 1}' (kept verbatim in observed_original_abi.return_type_machine_classification and as return_semantics.kind). That is a CLASSIFICATION of the value the machine leaves in EAX -- it says which bytes are written and what the value set is -- and it is not a C or C++ type: no declaration can be spelled to match it, which is why it sat in return_type and produced a permanent 'return type differs or is semantically renamed' against a span that was correct. It is now recorded in its own field instead. The width that the type DOES rest on is independent of the phrase and is read off the instructions: both exits write AL and not EAX (MOV AL,0x1 at 0x00641fc6, XOR AL,AL at 0x00641fca), so exactly one byte of the result is this body's own and a one-byte type is what the bytes support. What remains open is only whether the integrator prefers some other one-byte spelling (uint8_t against unsigned char against bool-with-a-cast); the span and this record agree on std::uint8_t and no evidence distinguishes the three.
- Which concrete function the slot at table+0x68 holds. It is a per-vtable choice: 0x00b1fbf0 in the table at 0x01462764, 0x006418b0 in the table at 0x01489090. The slot's own signature is taken from the CALL SITE (receiver in ECX, no stack word, byte in AL) and nothing fixes what the implementations do or whether they agree with each other.
