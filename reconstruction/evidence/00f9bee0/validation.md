# Validation 0x00f9bee0

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w2-00f9bee0/sw2_00f9bee0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 104-instruction listing name the same 5 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x00f9bee0..0x00f9c009 are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x00f9bef0; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 12 outgoing call edge row(s) over 5 distinct address(es) for 0x00f9bee0; the source span names 5 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 104-instruction listing names 1 data address(es) (0x16c9e68) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x8d8) and the 0 the complete 104-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x8d8), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (104 of 104 instruction(s), 0 unparsed) and all 16 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 4 conditional branch target(s) in the complete 104-instruction listing lie inside the recovered body span 0x00f9bee0..0x00f9c009, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 104-instruction body names 9 indirect transfer(s): 0x00f9befd dispatches slot 0x58 through the table word in EAX; 0x00f9bf36 dispatches slot 0x54 through the table word in EDX; 0x00f9bf41 dispatches slot 0xc through the table word in EDX; 0x00f9bf4c dispatches slot 0x50 through the table word in EDX; 0x00f9bf5f dispatches slot 0x1c through the table word in EDX; 0x00f9bf6d dispatches slot 0x134 through the table word in EDX; 0x00f9bf78 dispatches slot 0x50 through the table word in EDX; 0x00f9bf83 dispatches slot 0x50 through the table word in EDX; 0x00f9bf8e dispatches slot 0x50 through the table word in EDX; the machine parse consumed 104 of 104 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 9. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0xc, 0x1c, 0x50, 0x54, 0x58, 0x134, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'void': the return register EAX is written at a width this module cannot bound on at least one of the 1 reachable return(s) in the complete 104-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `891affcf2e7e48fa73ef13d6344277b6547221a56143bfee164a50d12382fe91`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `9e5a057027c38b376a27077fd587bb724d10c802ae28d2da3d6c3eaf6b52c609`
- Pack digest quoted by the briefing: `891affcf2e7e48fa73ef13d6344277b6547221a56143bfee164a50d12382fe91`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- DUPLICATE OWNERSHIP is not a risk on this VA at the time of writing: reconstruction/metadata carries no sidecar for 0x00f9bee0 other than this one, and reconstruction/evidence/00f9bee0/context.json lists no prior attempt. If a later package claims the same VA, note that reconstruction_knowledge.extract_metadata merges source_files per VA and sorts them, and validate._source() takes the first existing staging path, so two packages for one VA silently decide which source the validator judges. That is a property of the index and the integrator's call, not this worker's.
- GLOBALS is a WARN and it is a real evidence ceiling, not a defect. The xref export carries no data-reference edge type for this target (dependencies.data_reference_count is 0 and the pack's `globals` category is unavailable), so there is no second machine side to corroborate the one data address against, and validate's arm that reports agreement still WARNs because read/write mode needs per-access evidence. The mode WAS established independently, from GhidraMCP /get_xrefs_to, and is recorded under evidence.xref_modes_for_the_one_global; the check cannot read that source. Reported, not chased.
- RETURN SEMANTICS is a WARN and the disagreement is recorded rather than papered over. See validation.return_semantics_decision. No typedef named after the machine phrase was created to win the string comparison, and the sidecar states plainly which of the two honest options was taken and why.
- What the .data word at 0x016c9e68 is, beyond the read-then-call-then-cleared sequence. The name used here is Ghidra's (`Terrain__sTerrainRefractionBuffersRTTTexture`) and it is used so this package introduces no competing symbol; the reading that the word is a pending-work flag is INFERRED from 0x00f9bf07 testing it, 0x00f96c60 being called on the non-zero arm, and 0x00f96cb6 clearing it inside that callee. The word's value in the image file is 0x3efa3ee3, which is the static value and says nothing about the runtime value.
- What the eight 0x00777ae0 ids are. 0x301, 0x304, 0x305, 0x306, 0x24b, 0x23d, 0x24c and 0x24d, each with a zero value word and a zero flag byte. The callee indexes a .data table by its first word at 0x00777ae9 (`MOV EDX,[ECX*4 + 0x16f65a8]`) and compares that against the second, so the first word is a channel or handle id -- but which channels, and why these eight in this order, is not established here.
- What the immediate 0x3fbae24 is, and why it is passed twice. It is below the image base 0x400000, so it is a value and not a pointer into this image; a third such word, 0xd0a45522, appears at 0x00f99926 inside the 0x00f998f0 callee. This repository has no record that ties either value to a name, and the model passes the literal and nothing more.
- What the immediate 8 at 0x00f9bef9 means. It is the argument of the one call whose result the body gates on, and 8 is the kind of value this codebase uses for a type or class id, but no record for this target says so and the source asserts nothing about it. Settling it needs the callee behind the second argument's table slot +0x58, which is reached only through a dispatch this body does not resolve.
- What the receiver's word at 0x8d8 is. 0x00f998f0's own bytes make a release-and-null on a pointer member the natural reading (it calls the member's slot +0x0c with 2, stores 0 back, then calls slot +0x04 on it), and 0x00f998f0 also reads +0x8e0 and +0x8dc. No member is named for any of them here, and the model deliberately does not extend the receiver past 0x8db, so a reconstruction cannot be credited with a field this body never touches. The full sub-layout of the receiver is unknown: only that one word is read.
- What the two singletons are. 0x0067ddd0 over the global at 0x15fd8e8 and 0x0067dd80 over the global at 0x15fd8cc. Ghidra's SDK-derived symbol for the second is Graphics::IShadowWorld::Get, and the dispatch chain (slot +0x54 then +0x0c, slot +0x1c then +0x134) is what this body does with them. Neither the first object's identity nor the meaning of any of the four slot displacements inside either object is established, and the model names none of them.
- Whether any caller can reach this body with a null receiver. The body handles it (expected value 0) and then faults at 0x00f9bf15 if the gate matches, so the null arm is reachable in principle and fatal in practice. Whether the only real entry -- the dispatch table at 0x01490be8 -- can supply a null receiver is not established here.
- Whether the gate is a type check. The shape -- a call taking a small integer and returning an object address, compared against a known sub-object address -- is what a type query looks like, and self+0x04 would then be the receiver's embedded sub-object. That reading is consistent with every machine fact here and is recorded as semantic_findings INFERRED, but nothing in the body or in any record establishes it, and the model compares raw words rather than asserting a cast.
