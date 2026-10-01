# Validation 0x00926140

- Static reconstruction: `WARN`
- Runtime (original process): `GATED`
- Source: `src/reconstruction/wave6_containers_memory/containers_memory.cpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `WARN` | `partial` | target ABI is not deterministically extractable from the available source |
| CALLS | `PASS` | `complete` | the machine-vs-machine rule: the xref export and the complete 9-instruction listing each record no outgoing transfer, which is evidence that this target makes no call; the source span names none either; the xref export at /home/juanr/Proyectos/OpenSpore/knowledgegraph/triage/xrefs-2540f2ca.tsv is read whole: 1 outgoing call edge row(s) over 0 distinct address(es) for 0x00926140; 1 incoming call edge row(s) reach it, which the record's bounded projection counts against the same 30-row window but which are not callees; 1 of those rows name an external import rather than an address and are not address-comparable, as in the projection |
| GLOBALS | `WARN` | `partial` | the complete 9-instruction listing names 1 data address(es) (0x13cc2dc) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `WARN` | `partial` | 1 source field-offset declaration(s) (field field_18) are reconstruction-declared and no machine-derived struct layout exists to corroborate them: this target has no complete listing, or its ABI record names no receiver register to check them against |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (9 of 9 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | the complete 9-instruction listing contains no conditional branch, which is itself the evidence that the body is straight-line; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 9-instruction body names 1 indirect transfer(s): 0x0092614c is INDIRECT_NON_VTABLE; the machine parse consumed 9 of 9 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 1, so the dispatch is visible in the machine listing but is not proven: 1 of the 1 indirect transfer(s) classify as INDIRECT_NON_VTABLE (0x0092614c), so the dispatch's identity is not established: the target is the memory operand [0x013cc2dc], so no register chain exists to read; a scaled operand such as [EAX*0x4 + 0x5dd840] is a jump table and a plain [ESP + 0x30] is a frame slot, and neither is a virtual dispatch |
| RETURN SEMANTICS | `PASS` | `partial` | return type agrees with the bounded ABI record |

Static evidence basis: 8 of 8 static checks evaluated, 4 passed, 0 had no evidence to evaluate; 11 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 11 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `bed56068a18f2422d1d42c3db56c613c6daf00bb33352a7ccb161351f6191b1e`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `b2c2cf2cd8da7c84b27bd5e7dc9ac1ad9f46306f807d46ec6c5143194e6ddb7e`
- Pack digest quoted by the briefing: `bed56068a18f2422d1d42c3db56c613c6daf00bb33352a7ccb161351f6191b1e`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `gate-fixed-pool-allocator-critical-section-release`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- The concrete critical-section object and runtime caller pairing remain opaque.
- The imported Free label and source-level allocator ownership semantics are not independently established.
- The later 0x00926340 call in the teardown caller is outside this function.
- concrete allocator owner
- gate-fixed-pool-allocator-critical-section-release
- imported Free label identity
- runtime critical-section pairing
