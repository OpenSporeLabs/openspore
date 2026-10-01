# Validation 0x00695960

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `missing`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `WARN` | `partial` | the complete 136-instruction listing names 3 data address(es) (0x13f61cc, 0x1667bac, 0x1667bad) and the xref export carries no data-reference edge type, so there is nothing to corroborate them against; read/write mode still needs per-access evidence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 136-instruction listing nevertheless reaches 2 receiver displacement(s) through ECX (0xc, 0xa00), all of which the record accounts for or the listing is the better witness on; the 136-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=136, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 2 displacement(s) to the receiver as proven (0xc, 0xa00) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0xa00), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing; the listing shows 1 displacement(s) the record does not enumerate (0xc), and a complete listing outranks a record that declares itself incomplete |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (136 of 136 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 10 conditional branch target(s) in the complete 136-instruction listing lie inside the recovered body span 0x00695960..0x00695b30, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `WARN` | `partial` | the complete 136-instruction body names 2 indirect transfer(s): 0x00695a72 is FUNCTION_POINTER; 0x00695a7d is FUNCTION_POINTER; the machine parse consumed 136 of 136 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2, so the dispatch is visible in the machine listing but is not proven: 2 of the 2 indirect transfer(s) classify as FUNCTION_POINTER (0x00695a72, 0x00695a7d), so the dispatch's identity is not established: EAX is loaded from [EBP + 0x20], but EBP is defined by opaque earlier in the listing, so the word it names is not shown to be a table word |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | no canonical source artifact |

Static evidence basis: 5 of 8 static checks evaluated, 3 passed, 3 had no evidence to evaluate; 4 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 4 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `dd3462ee850e13a9e17edbccc78cf7b100badb7410a54ffe5d0652498a743d7b`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `f555b69ce9b2e1122e2bbd5aae81549f7bf836c548003654e53a094872145604`
- Pack digest quoted by the briefing: `dd3462ee850e13a9e17edbccc78cf7b100badb7410a54ffe5d0652498a743d7b`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: none recorded

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- None recorded in the canonical record.
