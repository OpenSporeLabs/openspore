# Validation 0x00b25f40

- Static reconstruction: `FAIL`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b25f40-noun-identity-resolver/noun_identity_resolver_00b25f40.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `FAIL` | `partial` | unresolved ABI conflict derived_vs_persisted; the validator will not pick a winner |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 41-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00b25f40; 80 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b21340; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `PASS` | `complete` | the machine-vs-machine rule: all 1 data address(es) the source span names are recorded as Ghidra data references out of this body, and the complete 41-instruction listing corroborates 1 of them; the artifact records 1 address-taken across 1 reference row(s)the data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole: 1 data reference row(s) out of 0x00b25f40 over 1 distinct address(es); segment breakdown: .reloc=1; access modes recorded: 1 other;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 8 type(s) |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (41 of 41 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 41-instruction listing lie inside the recovered body span 0x00b25f40..0x00b25f9e, so the branch graph is closed inside it; the source span declares for, if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 41-instruction body names 1 indirect transfer(s): 0x00b25f82 dispatches slot 0x4c through the table word in EDX; the machine parse consumed 41 of 41 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 1 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 7 of 8 static checks evaluated, 6 passed, 1 had no evidence to evaluate; 13 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 13 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `fa248bdf753c73bf31de3d21a6cab79b7e9d5b2305fa11c4a468de9d78a84d4d`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `e95e50bde56a2452f83c80aa3dca0d1a04fa747c7a3e65d191781c59414e4611`
- Pack digest quoted by the briefing: `fa248bdf753c73bf31de3d21a6cab79b7e9d5b2305fa11c4a468de9d78a84d4d`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `Each candidate pointer and vtable must be readable, and vtable+0x4c must point to a callable identity probe.`, `Every candidate reached must have a readable function table whose +0x4c word is a callable probe; the body has no guard on any of these.`, `The container returned by 0x00b21340 must have readable +0x04 and +0x08 words and a span whose arithmetic shift by two yields a usable count.`, `The five pushed words and 0x00b21340's own behaviour require original-process observation; nothing about them is established statically here.`, `The fixed callback words and 0x00b21340's map/list behavior require original-process observation.`, `The hidden receiver word must be valid for whatever 0x00b21340 does with it; this body does not read it, so nothing here constrains it.`, `The lifetime of a returned candidate is owned by the container and its callees, not by this body, which performs no AddRef, Release, allocation or store.`, `The ownership and lifetime of returned candidate objects remain external to this function.`, `The receiver must be valid for the existing 0x00b21340 projection/list layout.`, `The returned vector must have readable +0x04 and +0x08 words and a valid positive or nonpositive span.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Can the container be mutated between the count being computed and the loop finishing, in a way that makes the frozen count wrong rather than merely re-read? The listing fixes that the count is computed once and the begin word is re-read; whether any caller or the callee does so at runtime is unobserved.
- Does any caller rely on a null vector, negative span, or UINT32_MAX match as a special condition?
- Does the container's +0x4/+0x8 pair belong to a known SDK container, and what is its element type beyond 'a pointer to something with a function table at +0x00'? No capacity, size, allocator or owning-class claim is made, because the body reads neither.
- Each candidate pointer and vtable must be readable, and vtable+0x4c must point to a callable identity probe.
- Every candidate reached must have a readable function table whose +0x4c word is a callable probe; the body has no guard on any of these.
- Is the persisted __thiscall claim or the derived __stdcall claim the right SDK identity? Both name callee cleanup and the listing discriminates neither, and the pack records the conflict as unresolved. This package claims only the cleanup.
- The container returned by 0x00b21340 must have readable +0x04 and +0x08 words and a span whose arithmetic shift by two yields a usable count.
- The five pushed words and 0x00b21340's own behaviour require original-process observation; nothing about them is established statically here.
- The fixed callback words and 0x00b21340's map/list behavior require original-process observation.
- The hidden receiver word must be valid for whatever 0x00b21340 does with it; this body does not read it, so nothing here constrains it.
- The lifetime of a returned candidate is owned by the container and its callees, not by this body, which performs no AddRef, Release, allocation or store.
- The ownership and lifetime of returned candidate objects remain external to this function.
- The receiver must be valid for the existing 0x00b21340 projection/list layout.
- The returned vector must have readable +0x04 and +0x08 words and a valid positive or nonpositive span.
- What are the five pushed words 0x00b21080, 0x00d3d420, 0x00b236c0, 0x00b1e500 and the address 0x018c816a? They are code addresses except the last, and nothing in this body says what any of them denotes or how 0x00b21340 uses them.
- What class owns the candidate's function table, and what does the method at +0x4c mean? It is called with the candidate as its only argument and returns a raw 32-bit word that this body compares against its caller's word; no name is claimed.
- What concrete noun projection and object owner implement the receiver and vector?
- What concrete type is the hidden ECX receiver? The body neither reads nor writes ECX, so this package declares NounProjection as an opaque forwarded word and claims no layout, no owner and no SDK identity for it.
- What concrete vtable owner and identity method implement vtable+0x4c?
- What ownership and event effects occur inside 0x00b21340's callbacks?
- What semantic fields or callbacks are represented by the four fixed callback words?
- What stable meaning, if any, belongs to projection identity 0x018c816a?
