# Validation 0x00b25ca0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/pkg-00b25ca0-noun-city-range-begin-bias/noun_city_range_00b25ca0.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | the derived ABI record abstained (ABI_UNKNOWN): flow_not_modelled: the linear ESP walk ends at +20, so the listing is not one path |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 8-instruction listing name the same 1 direct transfer target(s); the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 1 distinct address(es) for 0x00b25ca0; 36 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; the record's dependency edge list is a scheduler projection of this export, not the export itself: it holds 30 row(s) and 0 address-named callee(s), against the 1 outgoing call edge row(s) and 1 distinct callee(s) the export records; 1 callee(s) the export records are absent from it, and the 30-row window capped at MAX_DEPENDENCY_EDGES=30 is why: 0x00b21340; the record's edges_truncated flag is set, and it is computed over this record's incoming and outgoing call rows together, so incoming edges alone can set it; the export records 1 outgoing call edge row(s) for this target, which is the count that bounds a callee set; the source span names 1 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 8-instruction listing names 1 data address(es) (0x018c816a); the data-reference artifact is read whole and records 1 reference row(s) out of this body covering every address under review, with access mode(s) other=1 |
| FIELDS/OFFSETS | `PASS` | `complete` | the machine-derived ABI record names no receiver register, so this pass claims nothing about the receiver: its identity and its layout are unclaimed in both directions and neither is established here; separately, the complete 8-instruction listing names no memory operand through any register at all and it was consumed in full by the machine parse (declared_count=8, degraded=false, unparsed=0), which is the evidence that this function performs no field access; the source span declares no field offset either, so there is no offset here to ground and none is claimed to exist |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (8 of 8 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 8-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 8-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `complete` | the source span declares return type 'NounRange*' and the machine return state is WIDTH_4_IN_EAX: the complete 8-instruction listing writes EAX at a determinate 4-byte width before all 1 reachable return(s); the width is a machine fact and the C type of that width is a source-side choice. The width is corroborated by the machine; the exact C type spelling remains a source-side choice among the types of that width and is not verified here. |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `964f5c5ead5df3461c054f08cf974f09c32222cb16569bb6cdf2553ce049d4f1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `abb1b7ca99478935430f7cc010c7899ba9b512378c6abb8d618201cab80b7582`
- Pack digest quoted by the briefing: `964f5c5ead5df3461c054f08cf974f09c32222cb16569bb6cdf2553ce049d4f1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Ownership of the returned range is unclaimed beyond 'borrowed': the body adds a bias and hands the pointer on, with no AddRef, no store and no release, and the callee's own ownership contract for its returned vector remains that package's open question.
- The SDK name of 0x00b25ca0 is unknown. It sits in the same address neighbourhood as 0x00b25f40 (a kCivilization scan over the same callee) and 0x00b25fb0, and 0xbf9820's committed metadata describes it as a 'city ownership enumeration wrapper' - but that is a CALLER's reading, not a witness, and it is deliberately not adopted. No naming claim is made beyond the witnessed facts that the callee is the noun projection and the return is that projection's element range.
- The value and role of the key operand 0x018c816a are open. It reads as eight zero bytes on this snapshot; whether it is a live global, a zero-initialised slot or a BSS cell is not established.
- Which function in the unpromoted callee link 0x00b21340 should satisfy this package's callee declaration is an integration decision, not a semantic one: the model test substitutes a recording stub with the callee's own ABI, and promotion must bind it to the promoted pkg11_sim_core noun projection.
- Which of the five immediates is the create callback, the clear callback, the add callback and the filter callback is not established by this body's eight instructions; those are the callee's parameter roles and belong to the callee package's evidence. They are carried as opaque 32-bit constants with the arity and the four-called/one-compared roles the callee's listing shows.
- openspore validate reports static NOT_AVAILABLE for this VA because reconstruction/knowledge/index.json carries an empty `source` record and the validator resolves the span from src/, not from reconstruction/staging/. Promoting the package and registering the source record is what would let the ABI, CALLS and RETURN SEMANTICS checks evaluate; this is a promotion-order artefact and not a disagreement with the binary.
