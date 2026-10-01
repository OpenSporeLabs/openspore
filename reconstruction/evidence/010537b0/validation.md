# Validation 0x010537b0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-swarm-w1-010537b0/sw1_010537b0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 12-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x010537b0; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | 2 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 1 displacement(s) the source span declares (0x4) and the 0 the complete 12-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0x0, 0x4), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 1 conditional branch target(s) in the complete 12-instruction listing lie inside the recovered body span 0x010537b0..0x010537d3, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'TableWordPair*' and the machine return state is WIDTH_4_IN_EAX: the complete 12-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 7 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `7f9be69214207112f8b9e95062e08df6c7b01618ade96d04a358d7eb7ea874d6`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `dbcbb7de77293b1538d5e5b16ff20ef58764245889b360c25a065e576ee08c95`
- Pack digest quoted by the briefing: `7f9be69214207112f8b9e95062e08df6c7b01618ade96d04a358d7eb7ea874d6`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A trace captures the pointer 0x00f47380 receives and the pointer the body returns in EAX, so the two are shown to be the same address.`, `A trace captures the two words before and after 0x010537b8 and 0x010537bf, confirming the immediates 0x013eb938 and 0x013ec458 and the order the two stores happen in.`, `A trace enters through the adjustor 0x01053780, so the -4 bias is observed arriving already applied.`, `A trace records the value in the entry stack word at 0x010537b0 and the ZF it produces, and which arm 0x010537c5 takes.`, `The original process is driven to an object whose +0x00 and +0x04 words hold a most-derived table pair, once with the deleting-destructor flag clear and once with it set.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A trace captures the pointer 0x00f47380 receives and the pointer the body returns in EAX, so the two are shown to be the same address.
- A trace captures the two words before and after 0x010537b8 and 0x010537bf, confirming the immediates 0x013eb938 and 0x013ec458 and the order the two stores happen in.
- A trace enters through the adjustor 0x01053780, so the -4 bias is observed arriving already applied.
- A trace records the value in the entry stack word at 0x010537b0 and the ZF it produces, and which arm 0x010537c5 takes.
- Ghidra's decompilation of the ADJACENT creator at 0x01053740 shows `ret 0x8`, i.e. it believes it takes two stack arguments, while the creator's own bytes push six words and its caller-side cleanup is `ADD ESP,0x18` at 0x01053754. That is another function's decompilation error and it is recorded only because it was read while establishing the class name above; nothing in this reconstruction depends on it.
- Is the receiver's size 0x08? The body writes displacements 0x00 and 0x04 and the adjustor proves a sub-object at +0x04, so 0x08 is the smallest size consistent with this evidence and is what the model declares. The size of the BASE sub-object beyond the eight bytes the body touches is not established: 0x01053740 shows a MORE DERIVED object of 0x0c bytes, which says nothing about the base's own extent. No total size is claimed beyond the two words this body rewrites.
- The original process is driven to an object whose +0x00 and +0x04 words hold a most-derived table pair, once with the deleting-destructor flag clear and once with it set.
- The xref export carries no data-reference edge type, so the 20 .rdata references to this address (39 xrefs in all, across 16 recorded vtable ids) cannot be used to corroborate anything about this body, and the record's vtable association is a transitive classifier artefact rather than an independent witness. The table at 0x0149b2e0 was read directly to place this body at slot +0x08; nothing else about the 20 sites was established, and none of it is modelled.
- What class does this destructor belong to? No name is claimed and none is invented. What is established: the object carries two table words at +0x00 and +0x04; the most-derived pair seen in the image for an object destroyed through this body is (0x0149b2e0, 0x0149bad8), set by the creator at 0x01053740, which allocates 0x0c bytes and hands the string at 0x0149b338 -- 'SP_Simulator/cToolStrategy/COM' -- to the allocator at 0x00f473a0; this body sits at slot +0x08 of 0x0149b2e0 and is reached from slot +0x00 of 0x0149bad8 through the -4 adjustor. That name belongs to the MORE DERIVED class the creator at 0x01053740 builds, and this body is a destructor of one of its bases (it rewrites both words to the base pair 0x013eb938 / 0x013ec458 and frees), so the string is recorded here as adjacent-body evidence and is NOT asserted as this target's class name. Settling it needs the class of the 0x013eb938 / 0x013ec458 pair, which this body does not name and which the SDK export does not carry for this VA (ghidra_function.sdk_name is null).
- What is 0x00f47380 by name? Its own bytes fix a null check, a .data word at 0x016c8b44 and a call to 0x009276c0, which is the guarded one-argument release shape the C runtime uses. It is named heap_release_00f47380 here for that shape. It is not established by these bytes that it is a particular named CRT entry point, and no such name is claimed.
- Why does the table at 0x013eb938 consist of two _purecall entries? The two-entry, both-`_purecall` shape is read straight out of .rdata and the import resolution is verified, so the FACT is fixed; what it means -- two unimplemented virtuals on a base, or an empty table kept only so the +0x00 word is never null -- is not established by anything in this package.
