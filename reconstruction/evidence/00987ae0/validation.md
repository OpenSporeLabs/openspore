# Validation 0x00987ae0

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/pkg_utfwin_drawable_wave9/utfwin_drawable_wave9.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `PASS` | `partial` | calling convention is present in the target source span and canonical metadata |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 12-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv carries no outgoing call edge of any reference type for 0x00987ae0; it is read whole, so that is a recorded absence and not a missing read |
| GLOBALS | `WARN` | `partial` | 1 source data address(es) appear in the machine listing; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 5 member(s) (field_00, field_04, field_08, field_0c) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 12-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=12, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x0, 0x4) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 2 displacement(s) (0x0, 0x14), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x14) the scan does not attribute to the receiver, and the listing governs there; the listing shows 1 displacement(s) the record does not enumerate (0x4), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (12 of 12 instruction(s), 0 unparsed) and all 1 source constant(s) appear in it |
| CONTROL FLOW | `PASS` | `complete` | the complete 12-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 12-instruction body names 1 indirect transfer(s): 0x00987afd dispatches slot 0x14 through the table word in EDX; the machine parse consumed 12 of 12 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 2 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. The source span declares a slot boundary and states displacement(s) 0x14, all of which are among the machine slot displacement(s), so its slot naming agrees with the machine and is adjudicated here too |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 6 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9e1bc4d1190f0221a1becb533ea3779d82474a75cf4083f4dbd10b1976e94e4c`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d00d0c7a73590f465d9e07407bbafbce2ca23d2482a4d30d15ff98543fbfa8ea`
- Pack digest quoted by the briefing: `9e1bc4d1190f0221a1becb533ea3779d82474a75cf4083f4dbd10b1976e94e4c`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process invocation or indirect-caller trace was captured.`, `The 0x14451c4 tag is treated as an opaque published constant, not a decoded type id.`, `The concrete vtable owner and meaning of slot +0x14 are unresolved.`, `gate-utfwin-drawable-slot-14-and-tag-decoding`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- Concrete owner and semantics of vtable slot +0x14
- Decoded meaning of the 0x14451c4 published tag
- No original-process invocation or indirect-caller trace was captured.
- The 0x14451c4 tag is treated as an opaque published constant, not a decoded type id.
- The concrete vtable owner and meaning of slot +0x14 are unresolved.
- Whether the imported SetHitMask label is the true role of this body
- Why the hit-mask word at +0x4c is left untouched
- gate-utfwin-drawable-slot-14-and-tag-decoding
