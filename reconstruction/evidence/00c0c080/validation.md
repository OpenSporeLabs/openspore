# Validation 0x00c0c080

- Static reconstruction: `NOT_AVAILABLE`
- Runtime (original process): `GATED`
- Source: `reconstruction/staging/wave13-w1-core-b10/b10_observed_types.hpp`

The two axes are independent. A static verdict says the reconstruction agrees with the
binary; it says nothing about the original process, and is never a runtime claim.

## Static checks

| Check | Status | Coverage | Detail |
|---|---|---|---|
| ABI | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| CALLS | `NOT_AVAILABLE` | `none` | target source span is not deterministically available |
| GLOBALS | `PASS` | `complete` | the complete 36-instruction listing names no data-segment address and the source span names none, which is positive evidence that this target touches no global; the xref export carries no data-reference edge type to corroborate against, and none is needed for an absence |
| FIELDS/OFFSETS | `PASS` | `complete` | the source span declares no field offset, so there is nothing of its own to ground and nothing ungrounded either; the complete 36-instruction listing nevertheless reaches 1 receiver displacement(s) through ECX (0x0), all of which the record accounts for or the listing is the better witness on; the 36-instruction listing is the governing witness for what this body reaches -- it was consumed in full by the machine parse (declared_count=36, degraded=false, unparsed=0) -- and it is read alias-aware over receiver register ECX, so that a copy, an XCHG, an address chain and a push/pop pair all keep the receiver attribution; the scan attributes 1 displacement(s) to the receiver as proven (0x0) and 0 more only on one arm of a branch, which is a may and grounds nothing (none); the machine-derived receiver record enumerates 1 displacement(s) (0x0), which is its own observation of where the body was seen reaching; its bounds_only flag is its own statement that the enumeration is open, so it widens what a claim may be grounded in and refutes nothing |
| CONSTANTS | `PASS` | `complete` | the machine listing is fully parsed (36 of 36 instruction(s), 0 unparsed) and the source span states no hexadecimal constant for it to lack |
| CONTROL FLOW | `PASS` | `complete` | all 3 conditional branch target(s) in the complete 36-instruction listing lie inside the recovered body span 0x00c0c080..0x00c0c0c7, so the branch graph is closed inside it; the source span declares no branch keyword, and keyword shape is a source-side signal that is not part of this verdict |
| VIRTUAL DISPATCH | `PASS` | `complete` | the complete 36-instruction body names 2 indirect transfer(s): 0x00c0c08e dispatches slot 0xb0 through the table word in EAX; 0x00c0c0ab dispatches slot 0xb4 through the table word in EAX; the machine parse consumed 36 of 36 instruction(s) with 0 unparsed and degraded=False, and the machine dispatch record independently counts 2. Every site is a two-level table load, so the machine dispatch is proven against the original binary: the reconstruction dispatches, and it dispatches through the slots the machine reads at those displacements. Neither the record's own association with 0 vtable(s) nor the xref export's 0 vtable reference(s) was read: they are not independent of each other, so agreement with them would prove nothing. No canonical source span is bound to this target, so nothing is claimed about a reconstruction's slot naming; this verdict is about the machine alone |
| RETURN SEMANTICS | `NOT_AVAILABLE` | `none` | return evidence is not deterministically available |

Static evidence basis: 5 of 8 static checks evaluated, 5 passed, 3 had no evidence to evaluate; 10 of 17 static evidence categories available.

Evidence coverage is a measurement, not a verdict: `WARN` -- 10 of 17 static evidence categories are available

## Binary evidence

- Evidence state: `LIVE`
- Pack source: `persisted_pack`
- Pack integrity: `verified`
- Content SHA-256: `9e14bab0662713a5dd8a9bea209869184b21d4a49db5c8a7569fbd81330a89e1`

## Worker briefing

- Source: `built_from_judged_pack`
- Briefing status: `partial`
- Content SHA-256: `3ecb1f497813065dd701cb9476a05913bba8b47ed2652d818f7ae844b67c94b3`
- Pack digest quoted by the briefing: `9e14bab0662713a5dd8a9bea209869184b21d4a49db5c8a7569fbd81330a89e1`

## Runtime

- Status: `GATED`
- Original-process observations validated: `0`
- Reason: no original-process trace exists in this repository; the gate is open, nothing was attempted, and nothing failed
- Open runtime gates: `A runtime differential test must observe a concrete receiver and resolve what virtual slots +0xb0 and +0xb4 dispatch to, which is the only way to name the owning class.`, `No original-process trace has been captured for 0x00c0c080, so the claim that subclasses never change the vtable mid-scan is static-only.`, `The count values returned by slot +0xb0 must be captured live, because the unsigned JBE guard and the signed JC bound disagree for counts above 0x7fffffff and no live count is known.`

A gated runtime is an open capability gate on the original process. Nothing was
attempted and nothing failed.

## Unresolved questions

- A runtime differential test must observe a concrete receiver and resolve what virtual slots +0xb0 and +0xb4 dispatch to, which is the only way to name the owning class.
- Do any of the eleven sibling accessors in 0x00c0c0d0..0x00c0c1c0 belong to a different class? They share the receiver and are contiguous in the binary, which is strong but circumstantial.
- Is 0xffffffff ever a valid index? It would require a collection of more than 0x7ffffffe elements, so in practice the sentinel is unambiguous; the code does not rely on that.
- No original-process trace exists for any function in this batch. Every statement here is static.
- No original-process trace has been captured for 0x00c0c080, so the claim that subclasses never change the vtable mid-scan is static-only.
- The binary carries no MSVC RTTI, so no class identity can be read from typeinfo; class claims in this record rest only on observed vtable data and SDK header text.
- The count values returned by slot +0xb0 must be captured live, because the unsigned JBE guard and the signed JC bound disagree for counts above 0x7fffffff and no live count is known.
- Twenty-eight of the thirty-one observed call sites were not disassembled, so only three call sites have a verified use of the return value.
- What are virtual slots +0xb0 and +0xb4? Their behaviour is pinned (a no-argument count and an indexed accessor) but their SDK names, if any, are not established.
- What class owns 0x00c0c080? The receiver's offset signature is known (+0xa60, +0xb34, +0xb74, +0xbb0, +0xbb1, +0xe80, +0xe84) but no vtable was located and no ModAPI header matches.
- What does the element dword at +0x8 denote? Every caller passes a small constant (0x0d, 0x27, 0x50, 0x52) so it is an enumeration or tag, but the enumeration is not in any ModAPI header and the writer of the field was not located.
- Why does 0x00c0c140 search for 0x0d and then 0x52 while 0x00c0c160 searches for 0x27 and then 0x50? The pairs look like primary and fallback ids, but no evidence names either member of either pair.
