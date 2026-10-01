# Validation 0x00a850d0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00a850d0/sw2_00a850d0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 81-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; 1 intra-procedural jump(s) target inside the recovered body span 0x00a850d0..0x00a851bf are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00a8512d; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00a850d0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `WARN` | `partial` | the complete 81-instruction listing names 2 data address(es) (0x1485378, 0x1485720) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 81-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0x10, 0x14), all of which the record accounts for or the listing is the better witness on; the 81-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=81, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x10, 0x14) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 7 displacement(s) (0xc, 0x10, 0x14, 0x18, 0x1c, 0x20, 0x68), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 5 of those (0xc, 0x18, 0x1c, 0x20, 0x68) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (81 of 81 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 9 conditional branch target(s) in the complete 81-instruction listing lie inside the recovered body span 0x00a850d0..0x00a851bf, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 81-instruction body names 4 indirect transfer(s): 0x00a850fc dispatches slot 0x18 through the table word in EAX; 0x00a8512e dispatches slot 0x1c through the table word in EDX; 0x00a8515a dispatches slot 0xc through the table word in EDX; 0x00a851b0 dispatches slot 0x10 through the table word in EDX; the machine parse consumed 81 of 81 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 4. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0xc, 0x10, 0x18, 0x1c, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'float': the ABI record names XMM0 as the return register; an SSE register: the machine fixes where the value travels and not whether the source said float, double or a vector, so the machine fixes where the value travels and not the C type, and no width can be claimed. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `07322b6b3027bf90502d1e926720bf29f90b76ea8ef1f83a7fce3343defc6679`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d18823b46b60ff6aa0e27803b186b6d0ccf7366bb1501f867fe2961ff0f77261`
- Pack digest quoted by the briefing: `07322b6b3027bf90502d1e926720bf29f90b76ea8ef1f83a7fce3343defc6679`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Are the three two-argument callees callee-cleanup? The body never adjusts ESP after 00a8512e, 00a8515a or 00a851b0, so a callee that did NOT pop its two words would leave the stack inconsistent for the rest of the function. That is an inference from an absence, not an observation of any callee, and it is recorded in the header at the typedefs rather than presented as a fact.
- Does the transfer at 00a851b0 clobber XMM0? On the early-return path at 00a851b7 the value the caller receives is whatever XMM0 held after that transfer, and 00a8518c is the last write the listing shows. Whether a callee preserves XMM0 across the call is a property of the CALLEE's signature, which this listing cannot show, so the model returns the pre-call value (the carrier's float) and the model test asserts only that. The clobber case is deliberately left unasserted in either direction.
- EVIDENCE COVERAGE is a WARN and is a property of the pack, not of the reconstruction: 9 of 17 static evidence categories are available for this target. The missing ones are callees_dependencies, callers_dependencies, contradictions, decompilation, external_callees, globals, runtime, semantic_hypotheses and types.
- GLOBALS is a WARN and is an evidence ceiling, not a defect. The complete 81-instruction listing names two data-segment addresses (0x01485720 and 0x01485378) and the xref export carries no data-reference edge type at all -- every edge in it is direct-call, computed-call, thunk or external -- so there is no second machine side to corroborate a read/write mode against. The listing's own text fixes the mode for both: both are the source operand of a MOVSS, and neither address is ever a destination. The constants are declared in the header with their addresses and their transcribed values, and the model test overwrites both to show they are reads rather than baked-in literals. Omitting the stores was not an option, because that would be a falsification of the body.
- RETURN SEMANTICS is a WARN and cannot be made a PASS from the source side. The canonical ABI record's own token is the machine phrase float_or_x87_in_XMM0 (abi_derived.value.abi.return_semantics, with abi.value.return.type = null and abi.value.return.void_possible = false at confidence APPROXIMATION). No C++ spelling can equal that string, so the string-agreement arm reports a rename however the return type is written. The declaration made here is float, which is TRUE OF THE LISTING: XMM0 is the recorded return register and the body writes it with a four-byte MOVSS at 00a8516c and 00a8518c and a four-byte DIVSS at 00a8517e, all single-precision four-byte scalars. Option (b) of the wave-1 rule -- declaring void -- was rejected because the bytes demonstrably produce a value on every path that writes XMM0. No typedef was invented after the machine phrase, because that is a validator hack and not a claim.
- What are the four callees, semantically? Three of the four results are discarded by the body and the fourth is stored and signed-tested, so this target constrains their signatures and nothing else. No claim is made about what they compute.
- What is the semantic role of the receiver, the carrier, the flag word's four bits, the guard byte, the three receiver floats and the word at receiver+0x68? This listing names none of them, the Spore-ModAPI SDK resolves no symbol for 0x00a850d0 (function_identity.types is empty, ghidra_function.sdk_name is null), and the binary carries no MSVC RTTI, so the class this function is slot 2 of cannot be named from this evidence. The Editor cluster label on this target comes from the triage queue and is NOT a claim made here.
- What owns the dispatch table? The four targets are four-byte words at displacements 0x18, 0x1c, 0x0c and 0x10 of a table reached by reading the dispatch object's lead dword, and the machine's own dispatch classifier calls all four sites VTABLE_SLOT. Nothing in this body fixes whether that table is a vtable, a callback array, or a dispatch record of some other kind, and the same instruction sequence would be produced by any of them. The displacements are claimed; the ownership is not, and the model test asserts only the addresses, the order and the argument order.
