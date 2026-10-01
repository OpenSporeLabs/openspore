# Validation 0x00b5b800

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b5b800-forwarded-state-sentinel/forwarded_state_00b5b800.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `WARN` | `partial` | the source span names no address-suffixed callee, so its 2 call(s) cannot be compared with the machine; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 2 outgoing call edge row(s) over 2 distinct address(es) for 0x00b5b800; 701 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 2 outgoing call edge row(s) and 2 distinct callee(s) the export records; 2 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00a42730, 0x00b3d320; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 2 outgoing call edge row(s) for this target, which is the count that bounds a callee set |
| GLOBALS | `NOT_AVAILABLE` | `none` | no independent data-reference evidence establishes a global for this target and no complete listing is availablethe data-reference artifact at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/datarefs-2540f2ca.tsv is read whole and records no data reference out of 0x00b5b800; that is a recorded absence, not a missing read;  |
| FIELDS/OFFSETS | `NOT_AVAILABLE` | `none` | the source span declares no field offset, and no machine-derived receiver evidence is collected for this target (the listing is absent or the ABI record names no receiver register); the record names 0 type(s) |
| CONSTANTS | `NOT_AVAILABLE` | `none` | no constant evidence available |
| CONTROL FLOW | `NOT_AVAILABLE` | `none` | no machine control-flow evidence exists for this target: the bridge never populates the dispatch field and no complete listing is collected |
| VIRTUAL DISPATCH | `NOT_AVAILABLE` | `none` | no machine dispatch evidence is collected for this target; the xref export records 0 vtable reference(s) and the record associates 0 vtable(s), which are not independent of each other |
| RETURN SEMANTICS | `WARN` | `partial` | return type differs or is semantically renamed; review required |

Static evidence basis: 3 of 8 static checks evaluated, 0 passed, 5 had no evidence to evaluate; 6 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 6 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `PERSISTED`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `0ae1461f14c73fa9b348ea046737c01b057d24f5ec543cac06ad2569a2f3780f`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `10dd99dd8dfcd84053bae1c53c75f06410f807480ad7013d7405d92d2a7a4019`
- Pack digest quoted by the briefing: `0ae1461f14c73fa9b348ea046737c01b057d24f5ec543cac06ad2569a2f3780f`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Calling convention. Derived as UNDETERMINED from the disassembly: zero parameters, zero register receiver, bare RET -- byte-identical under __cdecl, __stdcall, __thiscall and __fastcall, so no token is asserted. The briefing also lists ABI as a missing category; there is no persisted abi record for this target and none was synthesised.
- Concrete receiver class behind the borrowed global 0x0167eaec. No consumer or writer evidence in this run identifies it; deliberately left open per the prior-art stopping condition.
- Mode or strategy identity of the returned word, and whether it can ever legitimately be a pointer. The sampled consumers treat it as a scalar, which is a fact about them, not a proof.
- Physical storage type and layout of receiver+0x20. Modelled as an opaque byte run with a displacement; the first-writer search for 0x0167eaec named in prior art's 'opaque-forwarded-state-corpus' package was NOT run by me.
- Receiver initialization, ownership, allocator and teardown. Nothing in these 20 bytes touches any of them, and the datarefs snapshot has no first-writer row for the global.
- Relationship between the 0x01654c00..06 consumer sentinel family and the root's 0xffffffff null sentinel. Both are scalars; no aliasing, no conversion and no shared encoding is proven.
- Whether the 459 direct callers / 701 direct-call edges (80 gameplay callers, per root-closure-f0e310e0.json) are all semantically consistent with the single contract modelled here. This run confirmed the export row set for outgoing edges and read 16 caller sites, not all 459; the corpus-level claim is not re-verified.
