# Validation 0x0052e650

- Static reconstruction: `PASS`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-w2-0052e650/reconstruct_0052e650.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 7-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 0 outgoing call edge row(s) over 0 distinct address(es) for 0x0052e650; 2 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees |
| GLOBALS | `PASS` | `complete` | the complete 7-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the complete 7-instruction listing names no displacement through ECX, which is evidence that the body addresses no receiver field; the source span declares no field offset either |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (7 of 7 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 7-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 7-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares void, and the machine proves the return is empty: the ABI record names EAX as the return register, and no path through the complete 7-instruction listing writes it before any of the 1 reachable return(s), so the function returns nothing. This is proven from the complete listing and the parse record, not from the symbol's name. |

Static evidence basis: 8 of 8 static checks evaluated, 8 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `75490d58ea76d142019f7e12fbe6d17858c5c78d639f86c598e07b9d948cd16e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `6a84b59c2c4612b67817597d8884bd403ae8e856024b4165688fec7ba47da104`
- Pack digest quoted by the briefing: `75490d58ea76d142019f7e12fbe6d17858c5c78d639f86c598e07b9d948cd16e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `count the distinct classes whose vtable slot resolves to this address, and the slot index each uses. The derived record attributes one table and slot (0x013ef620, slot 5) out of 199 and leaves the other 198 unattributed; the binary has no MSVC RTTI. This is the only remaining blocker to naming a class, and it is the one the vftable_slot_dispatch rule works around rather than answers`, `observe whether the pushed 4-byte word is read by anything at all, which would place this body in a fold group whose remaining members give the argument a type`, `observe whether the receiver arriving in ECX is always an adjusted base pointer or whether some call site passes a subobject pointer directly, which would bound how many classes are folded onto this one address`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Does anything read the dead frame local? The listing shows no read inside this body, so a read can only come from outside the frame's lifetime - which no x86 code can do - or from an aliased frame this package cannot see. The store is dead in this body; whether it is a compiler artefact of a larger original statement is not observable from 13 bytes.
- What is the pushed 4-byte word for? It is a data address (0x013f4ac0) at one call site and a register (EDX) at the other, and this body never reads it, so its meaning belongs to the fold group this address is part of, not to this body. Under __thiscall the word is an ordinary stack argument of an unnamed type; the callee pops it and never looks at it.
- What is the receiver? __thiscall settles that ECX carries it and vftable_slot_dispatch settles why, but nothing settles what it is. The body reads the word, stores it in a dead frame slot and never dereferences it, and the record states bounds_only with shape null, so no type, no object size and no field offset is available from this target. Establishing it needs the class that owns one of the 199 referencing vftables - R1-VFT names 0x013ef620 slot 5 as the evidence but a slot is not a class - and not more analysis of these 13 bytes.
- Which classes are folded onto this address? The derived record counts 199 sound vptr-backed vftables holding it and attributes one of them (0x013ef620, slot 5) as its receiver evidence; the remaining 198 are named by neither table nor slot here, the binary has no MSVC RTTI, and so no owning class is recoverable from this package's evidence. This is the open question the vftable_slot_dispatch rule works around rather than answers.
- count the distinct classes whose vtable slot resolves to this address, and the slot index each uses. The derived record attributes one table and slot (0x013ef620, slot 5) out of 199 and leaves the other 198 unattributed; the binary has no MSVC RTTI. This is the only remaining blocker to naming a class, and it is the one the vftable_slot_dispatch rule works around rather than answers
- observe whether the pushed 4-byte word is read by anything at all, which would place this body in a fold group whose remaining members give the argument a type
- observe whether the receiver arriving in ECX is always an adjusted base pointer or whether some call site passes a subobject pointer directly, which would bound how many classes are folded onto this one address
