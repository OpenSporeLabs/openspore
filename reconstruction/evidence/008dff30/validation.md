# Validation 0x008dff30

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave6-resource-typename-map/typename_from_type.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | derived calling-convention confidence is UNKNOWN; the oracle is not proven |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 132-instruction listing name the same 2 direct transfer target(s); 1 intra-procedural jump(s) target inside the recovered body span 0x008dff30..0x008e00ab are excluded, because a jump that lands back in the body is control flow and not a transfer out of it: 0x008e0060; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 3 outgoing call edge row(s) over 2 distinct address(es) for 0x008dff30; the source span names 0 of them and no others |
| GLOBALS | `WARN` | `partial` | the complete 132-instruction listing names 2 data address(es) (0x13ebb38, 0x13f2150) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | the source span names 7 member(s) (bucket_count, buckets, chunk_first, chunk_last) and no machine record in this pack carries member names, so the identity of the member at a given displacement can be neither confirmed nor refuted by any machine evidence here and the name stays a review item: a displacement is a location claim and this pack settles those, a name is an identity claim and it settles none; the 0 displacement(s) declared alongside (none) are reported above with the witness each one rests on; the 132-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=132, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0x34, 0x38) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 3 displacement(s) (0x34, 0x38, 0x3c), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; 1 of those (0x3c) the scan does not attribute to the receiver, and the listing governs there |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (132 of 132 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 15 conditional branch target(s) in the complete 132-instruction listing lie inside the recovered body span 0x008dff30..0x008e00ab, so the branch graph is closed inside it; the source span declares if, while, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 132-instruction body names no indirect transfer through a register or a memory operand and the machine dispatch record agrees at 0, so neither the body nor the source span claims virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 5 passed, 0 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `5911645acd3a095b2320f349e37616c4a9aad997527a46fcf0940ee388e2701a`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `60f11dacb1826610800b96bb8e9248ff18fcb6645acc23775fb660b079e2eee1`
- Pack digest quoted by the briefing: `5911645acd3a095b2320f349e37616c4a9aad997527a46fcf0940ee388e2701a`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The literal value of the end sentinel is taken from resource_manager_initialize_008de530, not from this body.
- What the second word of each 8-byte chunk entry holds; the body never reads offset +0x04.
- Whether the collected 4-byte word at chunk entry +0x00 is a const char* typename pointer, a Resource type id or another handle: the listing only proves a 4-byte copy, and the pointee type is taken from the SDK name, not from evidence.
- Whether the insertion position is a list end() sentinel, a mid-list iterator, or a caller-owned anchor, since the function has no call xrefs and only the virtual slot at 0x01436ae8+0x4c is known.
- Why the map stores a half-open range of entries per key rather than a single value; the chunked representation is inferred from the +0x04/+0x08 pair and the 0x8 stride and is not confirmed by a writer in this package.
