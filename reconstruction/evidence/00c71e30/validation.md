# Validation 0x00c71e30

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00c71e30-empire5/empire5_00c71e30.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 21-instruction listing name the same 3 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 3 distinct address(es) for 0x00c71e30; 40 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 3 outgoing call edge row(s) and 3 distinct callee(s) the export records; 3 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b3d2a0, 0x00b8dab0, 0x00ba9370; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 3 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 3 of them and no others |
| GLOBALS | `PASS` | `complete` | the complete 21-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no globalthe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00c71e30; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `PASS` | `complete` | the 2 displacement(s) the source span declares (0xd4, 0x13c) and the 0 the complete 21-instruction listing names through ECX (none) are all within the machine-derived receiver bounds (0xd4, 0x13c), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (21 of 21 instruction(s), 0 unparsed) and all 4 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 21-instruction listing lie inside the recovered body span 0x00c71e30..0x00c71e6a, so the branch graph is closed inside it; the source span declares if, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 21-instruction body names 1 indirect transfer(s): 0x00c71e56 dispatches slot 0x4c through the table word in EAX; the machine parse consumed 21 of 21 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares no slot boundary, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `partial` | the machine return state is UNCLASSIFIED and the source span declares return type 'SlotWord': the return register EAX is written at a width this module cannot bound on at least one of the 2 reachable return(s) in the complete 21-instruction listing (a call result, a conditional destination, or two returns reached with different widths), so no width is determinable. No verdict is available on this state and none is claimed. |

Static evidence basis: 7 of 8 static checks evaluated, 7 passed, 1 had no evidence to evaluate; 12 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 12 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0ce5ec82a81cd77cf3d0d5c81aa204ac5f614f59ca5e74688f21388dc2b3f75f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `complete`
- Content SHA-256: `1e83f1e5b2900b33c90a49f52d384b79739f5c461b25fbc0d679f8fb4bfa33b2`
- Pack digest quoted by the briefing: `0ce5ec82a81cd77cf3d0d5c81aa204ac5f614f59ca5e74688f21388dc2b3f75f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Is the register argument a C++ `this`? The bytes eliminate __cdecl and eliminate nothing else; deciding __thiscall from __fastcall needs a class name, and no pack layer carries one.
- Is the return a pointer or a scalar? One sampled caller dereferences it at +0x84 and one null-tests it; both readings are consistent with everything observed.
- What class implements the table reached through receiver+0xd4? The shape is a two-level load and the classifier calls it VTABLE_SLOT, but the pack carries zero data references out of this VA and `vtable_at: []`.
- What does the constant 5 name, if anything? `CMP EAX,0x5` is an equality against an immediate and no evidence attaches a concept to it.
- What does the word at receiver+0x13c mean, and what class is the object it points at? Three sites read the displacement and none of them names a member.
- Why does the derived dispatch record count one indirect call and zero vtable-shaped loads for the same listing the repository's VIRTUAL DISPATCH dimension classifies as VTABLE_SLOT at 0x4c? Both numbers are pinned in the source and neither is reconciled here.
