# Validation 0x00c30c80

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b07/00c30c80_resolve_record_by_field.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 13-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the 0 displacement(s) the source span declares (none) and the 1 the complete 13-instruction listing names through ECX (0xb0) are all within the machine-derived receiver bounds (0xb0), so the offsets are grounded within the machine-derived receiver bounds; the record states where the body was seen reaching and not which member is which, so it identifies no field by name |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (13 of 13 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 2 conditional branch target(s) in the complete 13-instruction listing lie inside the recovered body span 0x00c30c80..0x00c30ca5, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 13-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `813bf079e8f18cd580794966a7efe4c3ebe86a53d210426b5f6a06ef66713ad8`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `d36598e824cdddf24225b8184fbeb08374f4196974f4a6e9c5223c09fc28ac36`
- Pack digest quoted by the briefing: `813bf079e8f18cd580794966a7efe4c3ebe86a53d210426b5f6a06ef66713ad8`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `No original-process trace exists for this address.`, `The record type, the handle table and the meaning of the +0xb0 id can only be settled with a runtime trace that shows the resolved record in use.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- No original-process trace exists for this address.
- The handle table's page stride of 20 bytes for 4096-entry pages is unusual (five pointers per outer entry); whether the outer table is really indexed by page was not cross-checked against a writer of that table.
- The record type, the handle table and the meaning of the +0xb0 id can only be settled with a runtime trace that shows the resolved record in use.
- What are the semantics of the 0x00bba2a0 call in the zero-id and failed-lookup paths? Its body was not decompiled in this batch.
- What does the id denote, and what is the record type? The returned record is read at +0x4ec as a 3-float vector by one caller and at +0x504 as an id by 0x00bba500, but no name for it is established.
- Whether the value at 0x0167eae4 is a singleton or is re-assigned during play is unobserved: the file image holds zero.
- Which class owns the +0xb0 id? All 15 callers pass a different receiver and none of them identifies the owner in a way that can be checked statically.
